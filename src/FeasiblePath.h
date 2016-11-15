#ifndef _FeasiblePath_H
#define _FeasiblePath_H
#include "z3++.h"
#include "Z3Coding.h"
#include "Formula.h"
#include "EnvironmentAnalysis.h"
/**
 * @class FeasiblePath
 * @author ubuntu15.10_x64
 * @date 11/08/16
 * @file FeasiblePath.h
 * @brief for a cfg, for a node n, n has i precursors, o successors such that i>=2,o=2
 * {i1,i2,i3,....} n {o1,o2}
 * o1 is the true branch of n
 * o2 is the false branch of n
 * check whether i1,i2,i3 is feasible at o1 or o2
 * 
 */
class FeasiblePath{
	private:
		EnvironmentAnalysis *envAnalysis;
		Z3Coding &z3coding;
		clang::CFG* cfg;
		C2Z3* c2z3Stmt;
		map<CFGBlock*,vector<pair<CFGBlock*,vector<CFGBlock*>*>*>*>* feasiblePrecursors;
		void initFeasiblePrecursors() {
			feasiblePrecursors=new map<CFGBlock*,vector<pair<CFGBlock*,vector<CFGBlock*>*>*>*>();
			for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
				CFGBlock* block=*iter;
				vector<pair<CFGBlock*,vector<CFGBlock*>*>*>* outs=new vector<pair<CFGBlock*,vector<CFGBlock*>*>*>();
				for(CFGBlock::succ_iterator succ_iter=block->succ_begin();succ_iter!=block->succ_end();++succ_iter){
					CFGBlock* succ=*succ_iter;
					pair<CFGBlock*,vector<CFGBlock*>*>* tmp=new pair<CFGBlock*,vector<CFGBlock*>*>(succ,new vector<CFGBlock*>());
					outs->push_back(tmp);
				}
				feasiblePrecursors->insert({block,outs});
			}
		}
		void analysis(){
			for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
				CFGBlock* n=*iter;
				if(n->pred_size()>=2&&n->succ_size()==2){
					CFGBlock *trueSucc,*falseSucc;
					CFGBlock::succ_iterator succ_iter=n->succ_begin();
					trueSucc=*succ_iter;++succ_iter;	falseSucc=*succ_iter;
					
					vector<CFGBlock*>* trueFeasiblePreds=getFeasiblePrecursorsOfEdge(n,trueSucc);
					vector<CFGBlock*>* falseFeasiblePreds=getFeasiblePrecursorsOfEdge(n,falseSucc);
					if(trueFeasiblePreds==nullptr||falseFeasiblePreds==nullptr){
						cerr<<"FeasiblePath::analysis::something wrong! trueFeasiblePreds or falseFeasiblePreds is null!"<<std::endl;
						return;
					}
					for(CFGBlock::pred_iterator pred_iter=n->pred_begin();pred_iter!=n->pred_end();++pred_iter){
						CFGBlock *pred=*pred_iter;
						if(pred==nullptr) {
							continue;
						}
						list<pair<CFGBlock*,FlowSet*>*>* predOuts=envAnalysis->getMapToBlockOut()->at(pred);
						FlowSet* predToNout=getFlowSetOfEdge(predOuts,n);
						if(predToNout==nullptr){
							cerr<<"FeasiblePath::analysis::something wrong! predToNout is null!"<<std::endl;
							return;
						}
						expr cond=getConditon(n);
						if(z3coding.checkError(cond)){
							// conservatism
							trueFeasiblePreds->push_back(pred);
							falseFeasiblePreds->push_back(pred);
							continue;
						}
						if(!isSimpleConditonBlock(n)){
							trueFeasiblePreds->push_back(pred);
							falseFeasiblePreds->push_back(pred);
							continue;
						}
						
						if(isFeasible(predToNout,cond)){//true branch is feasible
							trueFeasiblePreds->push_back(pred);
						}
						if(isFeasible(predToNout,!cond)){//false branch is feasible
							falseFeasiblePreds->push_back(pred);
						}
					}				
				}
				else{
					for(CFGBlock::succ_iterator succ_iter=n->succ_begin();succ_iter!=n->succ_end();++succ_iter){
						CFGBlock* succ=*succ_iter;
						vector<CFGBlock*>* feasiblePreds=getFeasiblePrecursorsOfEdge(n,succ);
						for(CFGBlock::pred_iterator pred_iter=n->pred_begin();pred_iter!=n->pred_end();++pred_iter){
							CFGBlock *pred=*pred_iter;
							feasiblePreds->push_back(pred);
						}
					}
				}
			}
			
		}
		expr getConditon(CFGBlock* n){
			if(n->succ_size()!=2){
				cerr<<"FeasiblePath::getConditon::something wrong! block succ number must is 2!"<<std::endl;
				return z3coding._error;
			}
			if(n->size()==0){
				cerr<<"FeasiblePath::getConditon::something wrong! block size number must >= 1!"<<std::endl;
				return z3coding._error;
			}
		
			
			CFGElement element=n->operator[](n->size()-1);
			if(element.getKind()==CFGElement::Kind::Statement){
				const Stmt* T=((CFGStmt*)&element)->getStmt();
				vector<expr> * exprs=c2z3Stmt->getZ3Stmts(T);
				if(exprs==nullptr||exprs->size()==0){
					cerr<<"FeasiblePath::getConditon::something wrong! exprs is null or size is 0!"<<std::endl;
					cerr<<"error info::exprs is null? "<<(exprs==nullptr)<<std::endl;
					cerr<<"error info::T is: "<<z3coding.toString(T)<<std::endl;
					cerr<<"error info::n bolckId is : "<<n->getBlockID()<<std::endl;
					return z3coding._error;
				}
				expr cond=exprs->at(exprs->size()-1);
				return cond;
			}
			return z3coding._error;
		}
		bool isSimpleConditonBlock(CFGBlock* n){
			if(n->size()!=1){
				//for n->size()!=1, the procession is complex, so we need 
				return false;
			}
			CFGElement element=n->operator[](n->size()-1);
			if(element.getKind()==CFGElement::Kind::Statement){
				const Stmt* T=((CFGStmt*)&element)->getStmt();
				vector<expr> * exprs=c2z3Stmt->getZ3Stmts(T);
				if(exprs==nullptr||exprs->size()!=1){
					return false;
				}
				return true;
			}
			return false;
		}
		FlowSet* getFlowSetOfEdge(list<pair<CFGBlock*,FlowSet*>*>* predOuts,CFGBlock* n){
			for(pair<CFGBlock*,FlowSet*>* out:*predOuts){
				if(out->first==n){
					return out->second;
				}
			}
			return nullptr;
		}
		bool isFeasible(FlowSet* states,expr cond){
			auto statesVec=states->toVector();
			vector<expr> states_expr;
			for(Property* state:*statesVec){
				expr statef=((Formula*)state)->formula;
				states_expr.push_back(statef);
			}
			if(z3coding.satisfy(&states_expr,cond)==check_result::unsat){
				return false;
			}
			return true;
		}
		std::string toString(vector<CFGBlock*>* blocks){
			std::string ret="";
			if(0<blocks->size()){
				ret=std::to_string(blocks->at(0)->getBlockID());
			}
			for(int i=1;i<(int)blocks->size();i++){
				ret+=","+std::to_string(blocks->at(i)->getBlockID());
			}
			return ret;
		}
	public:
	FeasiblePath(clang::CFG* cfg,EnvironmentAnalysis* envAna,Z3Coding &z3c,C2Z3* c2z3):envAnalysis(envAna),z3coding(z3c),c2z3Stmt(c2z3){
		this->cfg=cfg;
		initFeasiblePrecursors();
		analysis();
	}
	void print(){
		for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
			CFGBlock* block=*iter;
			vector<pair<CFGBlock*,vector<CFGBlock*>*>*>* outs=feasiblePrecursors->at(block);
			for(pair<CFGBlock*,vector<CFGBlock*>*>* out:*outs){
				if(out->first==nullptr) continue;
				cout<<block->getBlockID()<<"-->"<<out->first->getBlockID()<<" feasible precursors is: ";
				cout<<toString(out->second)<<std::endl;
			}
		}
	}
	vector<CFGBlock*>* getFeasiblePrecursorsOfEdge(CFGBlock* from,CFGBlock* to){
		if(feasiblePrecursors->count(from)>0){
			vector<pair<CFGBlock*,vector<CFGBlock*>*>*>* precursors=feasiblePrecursors->at(from);
			for(pair<CFGBlock*,vector<CFGBlock*>*>* pred:*precursors){
				if(pred->first==to){
					return pred->second; 
				}
			}
			return nullptr;
		}
		return nullptr;
	}
	
};
#endif 