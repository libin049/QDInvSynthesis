#ifndef _C2Z3_amendment_H
#define _C2Z3_amendment_H
#include "C2Z3.h"
#include "AtomVariableAnalysis.h"
#include "Z3Coding.h"
class C2Z3_amendment{
	private:
	clang::CFG* cfg;
	map<CFGBlock*, vector<expr>*> mapToBlocks; // CGFBlock's In dataflow infomation
	map<const Stmt*, vector<expr>*> stmtToZ3Exprs; 
	C2Z3* c2z3Stmt;
	Z3Coding& z3coding;
	AtomVariablaAnalysis* indexAnalysis;
	
	std::string toString(vector<z3::expr>* exprs){
		std::string ret="";
		if(exprs==nullptr) return "";
		for(auto it=exprs->begin();it!=exprs->end();it++){
			z3::expr e=(z3::expr) *it;
			std::string eName=z3coding.toString(e);
			ret+=eName+";\n ";
		}
		return ret;
	}
	bool isAtomicScalar(const clang::Stmt* clangStmt,unsigned count, expr e){
		return indexAnalysis->getAtomVariableAfter(clangStmt,count,e)!=nullptr;
	}	
	expr getAtomicScalarStep(const clang::Stmt* clangStmt,unsigned count, expr e){
		AtomVariabla* av=indexAnalysis->getAtomVariableAfter(clangStmt,count,e);
		return av->stepz3coding;
	}	
	vector<expr>* amendment(const clang::Stmt* clangStmt){
		//cout<<"clangStmt is: "<<z3coding.toString(clangStmt)<<std::endl;
		vector<expr> *result=new vector<expr>();
		vector<expr> *	z3Stmts=c2z3Stmt->getZ3Stmts(clangStmt);
		
		if(z3Stmts==nullptr){
			cerr<<"C2Z3_amendment::amendment_stmt:z3Stmts is null!"<<std::endl;
			return nullptr;
		}
		//cout<<"z3Stmts is: "<<toString(z3Stmts)<<std::endl;
		if(z3Stmts->size()==0||z3Stmts->size()==1){
			z3coding.pushAToB(z3Stmts,result);
			return result;
		}
		else{
			vector<expr>* primeVariables=new vector<expr>();
			vector<expr>* unprimeVariables=new vector<expr>();
			unsigned count=0;
			for(expr stmt:*z3Stmts){
				auto stmtMemorys=z3coding.getMemoryUnits(stmt);
				expr newStmt=stmt;
				for(unsigned i=0;i<primeVariables->size();i++){
					if(z3coding.isIn(primeVariables->at(i),stmtMemorys.get())){
						//deg v' to v
						newStmt=z3coding.substitute(newStmt,primeVariables->at(i),unprimeVariables->at(i));
					}
					if(z3coding.isIn(unprimeVariables->at(i),stmtMemorys.get())){
						if(isAtomicScalar(clangStmt,count,unprimeVariables->at(i))){
							//replace v to f(v')
							//deg v' to v
							expr step=getAtomicScalarStep(clangStmt,count,unprimeVariables->at(i));
							newStmt=z3coding.substitute(newStmt,unprimeVariables->at(i),primeVariables->at(i)-step);
							newStmt=z3coding.substitute(newStmt,primeVariables->at(i),unprimeVariables->at(i));
						}
						else{
							cerr<<"C2Z3_amendment::amendment_stmt:We can not process, the statement is too complex!"<<std::endl;
							cerr<<"Error info::clangStmt is "<<z3coding.toString(clangStmt)<<std::endl;
							cerr<<"Error info::stmt is "<<stmt<<", "<<unprimeVariables->at(i) << " in that "<<std::endl;
							return nullptr;
						}
					}
				}
				
				if(z3coding.isAssignment(stmt)){
					expr pv=stmt.arg(0).arg(0);
					primeVariables->push_back(pv);
					expr upv=z3coding.unprime(pv);
					unprimeVariables->push_back(upv);
					if(z3coding.isPrimedVariable(upv)){
						cerr<<"C2Z3_amendment::amendment_stmt:something is wrong!"<<std::endl;
						cerr<<"Error info::stmt is "<<stmt<<", "<<upv<<","<<pv << std::endl;
						return nullptr;
					}
				}
				count++;
				result->push_back(newStmt);
			}
			return result;
		}
	}
	vector<expr>* amendment(CFGBlock* n){
		//cout<<"block id is: "<<n->getBlockID()<<std::endl;
		vector<expr>* result=new vector<expr>();
		for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
			CFGElement element=(*iterblock);
			if(element.getKind()==CFGElement::Kind::Statement){
				const Stmt* it=((CFGStmt*)&element)->getStmt();
				vector<expr>* stmts=amendment(it);
				
				stmtToZ3Exprs.insert({it,stmts});
				//result is null
				if(stmts==nullptr){
					result=nullptr;
				}
				else if(result!=nullptr){
					z3coding.pushAToB(stmts,result);
				}
				
			}
		}
		return result;
	}
	void amendment(){
		for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
			CFGBlock* block=*iter;
			vector<expr>* stmts=amendment(block);
			mapToBlocks.insert({block,stmts});
		}
	}
	void initAndSortWorkList(list<CFGBlock*> &worklist){
		CFGBlock &entry=cfg->getEntry();
		list<CFGBlock*> queue;
		queue.push_back(&entry);
		while(!queue.empty()){
			CFGBlock* n=queue.front();queue.pop_front();
			//get succ of n
			
			if(!isIn(worklist,n)){
				worklist.push_back(n);
				for(CFGBlock::succ_iterator succ_iter=n->succ_begin();succ_iter!=n->succ_end();++succ_iter){
					CFGBlock *succ=*succ_iter;
					if(succ!=nullptr){
						queue.push_back(succ);
					}
					
				}
			}			
		}
	}
	bool isIn(list<CFGBlock*> &lists, CFGBlock * n){
		for (std::list<CFGBlock*>::iterator it = lists.begin(); it != lists.end(); it++){
			CFGBlock *ele=*it;
			if(ele==n){
				return true;
			}
		}
		return false;
	}
public:	
	C2Z3_amendment(clang::CFG* cfg,Z3Coding &z3code,C2Z3* c2z3,AtomVariablaAnalysis* indexAna):
	c2z3Stmt(c2z3),z3coding(z3code),indexAnalysis(indexAna){
		this->cfg=cfg;
		amendment();
	}
	
	void print(){
		list<CFGBlock*> queue;
		initAndSortWorkList(queue);
		while(!queue.empty()){
			CFGBlock* n=queue.front();queue.pop_front();
			std::cout <<"--------[B"<< n->getBlockID ()<<"]" << ":--------"<<std::endl; 
			std::cout<<toString(mapToBlocks[n])<<std::endl;
		}
		/*//--------------------id order--------------
		for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
			CFGBlock* n=*iter;
			std::cout <<"--------[B"<< n->getBlockID ()<<"]" << ":--------"<<std::endl; 
			std::cout<<toString(mapToBlocks[n])<<std::endl;
		}*/
	}
	vector<expr>* getZ3Stmts(const Stmt* stmt){
		if(stmtToZ3Exprs.count(stmt)>0){
			return stmtToZ3Exprs.at(stmt);
		}
		return nullptr;
	}
	
	
	
	const map<CFGBlock*, vector<expr>* >& GetMapToBlocks() const {return mapToBlocks;}
	const map<const Stmt*, vector<expr>* >& GetStmtToZ3Exprs() const {return stmtToZ3Exprs;}
};
#endif
