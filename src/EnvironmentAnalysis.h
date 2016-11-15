#ifndef _EnvironmentAnalysis_H
#define _EnvironmentAnalysis_H
#include "Formula.h"
#include "EnvironmentAnalysisUtil.h"
#include "DataFlowAnalysis.h"
#include "ValueListSetWithUniversalSet.h"
#include "PointerAnalysis.h"
#include "MultiIndexesRelationAnalysis.h"

class EnvironmentAnalysis: public IntraDataFlowAnalysis{
private:
		context &c;
		EnvironmentAnalysisUtil &emu;
		Z3Coding &z3coding;
		AtomVariablaAnalysis *indexAnalysis;
		C2Z3* c2z3Stmt;
		MultiIndexesRelationAnalysis* multiIndexesRelationAnalysis;
		/*PointerAnalysis* pointerAnalysis;*/
		std::string toString(vector<z3::expr>* exprs){
			std::string ret="";
			if(exprs==nullptr) return "";
			for(z3::expr e:*exprs){
				//cout<<e<<std::endl;
				std::string eName=z3coding.toString(e);
				ret+=eName+";\n ";
			}
			return ret;
		}
		
		std::string toString(FlowSet* in){
			return toString(flowSetToExprSet(in));
		}
		FlowSet * exprSetToFlowSet(vector<expr> * exprSet){
			FlowSet * flowSet=new ValueListSetWithUniversalSet();
			for(expr e: *exprSet){
				flowSet->add(new Formula(e));
			}
			return flowSet;
		}
		vector<expr> * flowSetToExprSet(FlowSet * flowSet){
			vector<expr> * exprSet=new vector<expr>();
			ValueListSetWithUniversalSet *listSet=(ValueListSetWithUniversalSet *)flowSet;
			for(Property* p: listSet->elements){
				Formula *f=(Formula *)p;
				exprSet->push_back(f->formula);
			}
			return exprSet;
		}
		std::string toString(const Stmt* stmt){
			std::string buffer1;

			LangOptions LO;
			LO.CPlusPlus=1; 
			llvm::raw_string_ostream strout1(buffer1);

			stmt->printPretty(strout1, nullptr, PrintingPolicy(LO));
			return strout1.str();
		}
		void pre_init(){
			for(CFG::iterator it=cfg->begin();it!=cfg->end();++it){
				CFGBlock* n=*it;
				unsigned count=0;
				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
					CFGElement element=(*iterblock);
					if(element.getKind()==CFGElement::Kind::Statement){
						const Stmt* it=((CFGStmt*)&element)->getStmt();
						//cout<<z3coding.toString(it)<<std::endl;
						mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSetWithUniversalSet()));
						vector<FlowSet*>* tmp=new vector<FlowSet*>();
						tmp->push_back(new ValueListSetWithUniversalSet());
						if(n->succ_size()==2){
							Stmt* T=n->getTerminatorCondition();
							if(it==T||(n->size()>0&&count==n->size()-1)){
								tmp->push_back(new ValueListSetWithUniversalSet());
							}
						}
						mapToStmtOut.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,tmp));
						count++;
					}
				}
			}
		}
		void pre_init_stmtExpr(){
			for(CFG::iterator it=cfg->begin();it!=cfg->end();++it){
				CFGBlock* n=*it;
				const Stmt* T=nullptr;
				if(n->succ_size()==2){
					unsigned count=0;
					for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
						CFGElement element=(*iterblock);
						if(element.getKind()==CFGElement::Kind::Statement){
							const Stmt* it=((CFGStmt*)&element)->getStmt();
							if(n->size()>0&&count==n->size()-1){
								T=it;
								break;
							}
							mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,new vector<FlowSet*>()));
							vector<vector<FlowSet*>*>* tmp=new vector<vector<FlowSet*>*>();
							tmp->push_back(new vector<FlowSet*>());
							mapToStmtExprOut.insert(std::pair<const clang::Stmt*,vector<vector<FlowSet*>*>*>(it,tmp));
							
						}
						count++;
					}
					if(mapToStmtExprIn.count(T)<=0){
						mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
						vector<vector<FlowSet*>*>* tmp=new vector<vector<FlowSet*>*>();
						tmp->push_back(new vector<FlowSet*>());
						tmp->push_back(new vector<FlowSet*>());
						mapToStmtExprOut.insert(std::pair<const clang::Stmt*,vector<vector<FlowSet*>*>*>(T,tmp));
					}
					
				}
				if(n->succ_size()==1){
					for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
						CFGElement element=(*iterblock);
						if(element.getKind()==CFGElement::Kind::Statement){
							const Stmt* it=((CFGStmt*)&element)->getStmt();
							mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,new vector<FlowSet*>()));
							vector<vector<FlowSet*>*>* tmp=new vector<vector<FlowSet*>*>();
							tmp->push_back(new vector<FlowSet*>());
							mapToStmtExprOut.insert(std::pair<const clang::Stmt*,vector<vector<FlowSet*>*>*>(it,tmp));
						}
					}
				}
			}
		}
		FlowSet* getIndexEnvironmentBeforStmt(const clang::Stmt *clangStmt){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* in=indexAnalysis->mapToStmtIn.at(clangStmt);
			return in;
		}
		FlowSet* getIndexEnvironmentBeforStmt(const clang::Stmt *clangStmt,int count){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* in=indexAnalysis->mapToStmtExprIn.at(clangStmt)->at(count);
			return in;
		}
		FlowSet* getIndexEnvironmentBeforBlock(CFGBlock*& n){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* in=indexAnalysis->getMapToBlockIn()->at(n);
			return in;
		}
		
		FlowSet* getMultiIndexEnvironmentBeforBlock(CFGBlock*& n){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			if(multiIndexesRelationAnalysis->getMapToBlockIn()->count(n)<=0){
				cerr<<"EnvironmentAnlysis::getMultiIndexEnvironmentBeforBlock::something is wrong!"<<std::endl;
				cerr<<"error info::"<<n->getBlockID()<<std::endl;
			}
			FlowSet* in=multiIndexesRelationAnalysis->getMapToBlockIn()->at(n);
			return in;
		}
		
		
		FlowSet* getIndexEnvironmentAfterStmt(const clang::Stmt *clangStmt){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* out=indexAnalysis->mapToStmtOut.at(clangStmt);
			return out;
		}
		FlowSet* getIndexEnvironmentAfterStmt(const clang::Stmt *clangStmt,int count){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* out=indexAnalysis->mapToStmtExprOut.at(clangStmt)->at(count);
			return out;
		}
		FlowSet* getMultiIndexEnvironmentAfterStmt(const clang::Stmt *clangStmt){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			if(multiIndexesRelationAnalysis->mapToStmtOut.count(clangStmt)<=0){
				cerr<<"EnvironmentAnlysis::getMultiIndexEnvironmentAfterStmt::something is wrong!"<<std::endl;
				cerr<<"error info::"<<z3coding.toString(clangStmt)<<std::endl;
			}
			FlowSet* out=multiIndexesRelationAnalysis->mapToStmtOut.at(clangStmt);
			return out;
		}
		FlowSet* getMultiIndexEnvironmentBeforStmt(const clang::Stmt *clangStmt){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			if(multiIndexesRelationAnalysis->mapToStmtIn.count(clangStmt)<=0){
				cerr<<"EnvironmentAnlysis::getMultiIndexEnvironmentBeforStmt::something is wrong!"<<std::endl;
				cerr<<"error info::"<<z3coding.toString(clangStmt)<<std::endl;
			}
			FlowSet* out=multiIndexesRelationAnalysis->mapToStmtIn.at(clangStmt);
			return out;
		}
		FlowSet* getMultiIndexEnvironmentAfterStmt(const clang::Stmt *clangStmt,int count){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* out=multiIndexesRelationAnalysis->mapToStmtExprOut.at(clangStmt)->at(count);
			return out;
		}
		FlowSet* getMultiIndexEnvironmentBeforStmt(const clang::Stmt *clangStmt,int count){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* in=multiIndexesRelationAnalysis->mapToStmtExprIn.at(clangStmt)->at(count);
			return in;
		}
		
		vector<expr>* generateIndexProperties(FlowSet* indexProperties){
			vector<expr>* result=new vector<expr>();
			
			ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)indexProperties;
			for(Property* p: vlsOut->elements){
				AtomVariabla * av=(AtomVariabla *)p;
				if(av->hasStep()){
					if(emu.isGtZero(av->stepz3coding)){
						result->push_back(av->initz3coding<=av->scalaVarz3coding);
						result->push_back(av->scalaVarModConstraint);
						index_mod_exprs->push_back(av->scalaVarModConstraint.arg(0));
					}
					else if(emu.isLtZero(av->stepz3coding)){
						result->push_back(av->scalaVarz3coding<=av->initz3coding);
						result->push_back(av->scalaVarModConstraint);
						index_mod_exprs->push_back(av->scalaVarModConstraint.arg(0));
					}
				}
			}
			return result;
		}
		
		void addIndexProperties(){
			//add to block in
			for(std::pair<CFGBlock*, FlowSet*> p:mapToBlockIn){
				add(generateIndexProperties(getIndexEnvironmentBeforBlock(p.first)),p.second);
			}
			/*//add to block out
			for(auto p:mapToBlockOut){
				add(generateIndexProperties(getIndexEnvironmentAfterBlock(p.first)),p.second);
			}*/
			//add to stmt in
			for(std::pair<const clang::Stmt*, FlowSet*> p:mapToStmtIn){
				add(generateIndexProperties(getIndexEnvironmentBeforStmt(p.first)),p.second);
			}
			//add to stmt out
			for(std::pair<const clang::Stmt*, vector<FlowSet*>*> p:mapToStmtOut){
				for(unsigned i=0;i<p.second->size();i++){
					add(generateIndexProperties(getIndexEnvironmentAfterStmt(p.first)),p.second->at(i));
				}
			}
			//add to stmt expr in
			for(std::pair<const clang::Stmt*, vector<FlowSet*>*> p:mapToStmtExprIn){
				unsigned count=p.second->size();
				for(unsigned i=0;i<count;i++){
					add(generateIndexProperties(getIndexEnvironmentBeforStmt(p.first,i)),p.second->at(i));
				}
			}
			//add to stmt out
			for(std::pair<const clang::Stmt*, vector<vector<FlowSet*>*>*> p:mapToStmtExprOut){
				unsigned count=p.second->size();
				for(unsigned i=0;i<count;i++){
					for(unsigned j=0;j<p.second->at(i)->size();j++){
						add(generateIndexProperties(getIndexEnvironmentAfterStmt(p.first,j)),p.second->at(i)->at(j));
					}
				}
			}
		}
		void addMultiIndexRalationProperties(){
			for(std::pair<CFGBlock*, FlowSet*> p:mapToBlockIn){
				add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentBeforBlock(p.first),getIndexEnvironmentBeforBlock(p.first))
						,p.second);
			}
			/*//add to block out
			for(auto p:mapToBlockOut){
				add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentAfterBlock(p.first),getIndexEnvironmentAfterBlock(p.first))
						,p.second);
			}*/
			//add to stmt in
			for(std::pair<const clang::Stmt*, FlowSet*> p:mapToStmtIn){
				add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentBeforStmt(p.first),getIndexEnvironmentBeforStmt(p.first))
					,p.second);
			}
			//add to stmt out
			for(std::pair<const clang::Stmt*, vector<FlowSet*>*> p:mapToStmtOut){
				unsigned count=p.second->size();
				for(unsigned i=0;i<count;i++){
					add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentAfterStmt(p.first),getIndexEnvironmentAfterStmt(p.first))
						,p.second->at(i));
				}
			}
			//add to stmt expr in
			for(std::pair<const clang::Stmt*, vector<FlowSet*>*> p:mapToStmtExprIn){
				unsigned count=p.second->size();
				for(unsigned i=0;i<count;i++){
					add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentBeforStmt(p.first,i),getIndexEnvironmentBeforStmt(p.first,i))
						,p.second->at(i));
				}
			}
			//add to stmt out
			for(std::pair<const clang::Stmt*, vector<vector<FlowSet*>*>*> p:mapToStmtExprOut){
				unsigned count=p.second->size();
				for(unsigned i=0;i<count;i++){
					for(unsigned j=0;j<p.second->at(i)->size();j++){
						add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentAfterStmt(p.first,j),getIndexEnvironmentAfterStmt(p.first,j))
							,p.second->at(i)->at(j));
					}
				}
			}
		}
		void add(vector<expr>* A,vector<expr>* B){
			for(expr e: *A){
				if(!z3coding.isIn(e,B)){
					B->push_back(e);
				}
			}
		}
		void add(vector<expr>* A,FlowSet* B){
			FlowSet* tmp=exprSetToFlowSet(A);
			B->Union(tmp);
		}
		vector<expr>* index_mod_exprs;
		vector<expr> * eliminateSillyFormulas(vector<expr> * in){
			vector<expr>* result=new vector<expr>();
			for(expr f:*in){
				f=z3coding.eliminateNotInSimpleFormula(f);
				f=emu.eliminateGtAndGe(f);
				if(f.is_app()&&(f.decl().name().str()=="<"||f.decl().name().str()=="<=")){
					if(z3coding.isIn(f.arg(0),index_mod_exprs)||z3coding.isIn(f.arg(1),index_mod_exprs)){
						continue;
					}
					if(f.arg(0).is_numeral()&&f.arg(1).is_numeral()){
						continue;
					}
				}
				if(f.is_app()&&f.decl().name().str()=="="){
					if(z3coding.isIn(f.arg(0),index_mod_exprs)&&!f.arg(1).is_numeral()){
						continue;
					}
					if(z3coding.isIn(f.arg(1),index_mod_exprs)&&!f.arg(0).is_numeral()){
						continue;
					}
				}
				result->push_back(f);
			}
			return result;
		}
		
		bool com(vector<expr>* a1,vector<expr>* a2){
			if(a1->size()!=a2->size()){
				return false;
			}
			for(unsigned i=0;i<a1->size();i++){
				if(!z3coding.equal(a1->at(i),a2->at(i))){
					return false;
				}
			}
			return true;
		}
	AtomVariabla* getAtomVariablaBy(FlowSet* indexEnv,expr index){
		ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)indexEnv;
		for(Property * p: AtomVariables->elements){
			AtomVariabla* av=(AtomVariabla*)p;
			if(av->hasStep()&&z3coding.equal(av->scalaVarz3coding,index)){
				return av;
			}
		}
		return nullptr;
	}
	vector<expr>* getMultiIndexesRelationAnalysis(FlowSet* multiIndexEnv,FlowSet* indexEnv){
		vector<expr>* result=new vector<expr>();
		ValueListSetWithUniversalSet* indexRelationsVls=(ValueListSetWithUniversalSet*)multiIndexEnv;
		if(indexRelationsVls==nullptr){
			cerr<<"EnvironmentAnalysis::getMultiIndexesRelationAnalysis::"<<"something is wrong!"<<std::endl;
			return result;
		}
		for(Property* rp:indexRelationsVls->elements){
			IndexesRelation* ir=(IndexesRelation*)rp;
			expr index1=ir->scalaVariabla1;
			expr index2=ir->scalaVariabla2;
			int diff=ir->diff;
			expr eqtion=getIndex2EqIndex1(index1,index2,diff,indexEnv);
			if(!z3coding.checkError(eqtion)){
				result->push_back(eqtion);
			}
		}
		return result;
	}
expr getIndex2EqIndex1(expr index1,expr index2,int diff,FlowSet* indexEnv){
	AtomVariabla* indexp1=getAtomVariablaBy(indexEnv,index1);
	AtomVariabla* indexp2=getAtomVariablaBy(indexEnv,index2);
	if(indexp1==nullptr||indexp2==nullptr){
		//in macro environment , it may be somt thing wrong
		//however, i thing the error is sound
		/*cerr<<"EnvironmentAnalysis::getIndex2EqIndex1:: something is wrong!"<<std::endl;
		cerr<<"error info::index1 is "<<index1<<std::endl;
		cerr<<"error info::index2 is "<<index2<<std::endl;
		cerr<<"error info::indexEnv is "<<indexEnv->toString()<<std::endl;*/
		return z3coding._error;
	}
	
	expr indexstep1=indexp1->stepz3coding;
	expr indexstep2=indexp2->stepz3coding;
	expr indexinit1=indexp1->initz3coding;
	expr indexinit2=indexp2->initz3coding;
	//(x1 − initx1)/c1 − (x2 − initx2)/c2 = d
	return (index1-indexinit1)/indexstep1-(index2-indexinit2)/indexstep2==diff;

}
	void printFlowSets(vector<FlowSet*>* vs){
		unsigned count=0;
		for(FlowSet* f:*vs){
			count++;
			cout<<"--------"<<count<<"---------"<<std::endl;
			f->print();
		}
	}
	public:
		map<const clang::Stmt*, FlowSet*> mapToStmtIn;
		map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtOut;
		
		map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprIn;
		map<const clang::Stmt*, vector<vector<FlowSet*>*>*> mapToStmtExprOut;
	
		EnvironmentAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,
		EnvironmentAnalysisUtil& environmentUtil,
		context &ctx,Z3Coding &z3c,AtomVariablaAnalysis *indexAna,C2Z3* c2z3/*,PointerAnalysis* pointerAna*/,
		MultiIndexesRelationAnalysis* multiIndexesRelationAna)
		:IntraDataFlowAnalysis(functionDecl,cfg),
		emu(environmentUtil),c(ctx),z3coding(z3c),indexAnalysis(indexAna),c2z3Stmt(c2z3)/*,pointerAnalysis(pointerAna)*/,
		multiIndexesRelationAnalysis(multiIndexesRelationAna){
			index_mod_exprs=new vector<expr>();
			pre_init();
			pre_init_stmtExpr();
			doAnalysis();
			addIndexProperties();
			addMultiIndexRalationProperties();
		}
		vector<expr> * GenAndKill(vector<expr> * Pre,const clang::Stmt* stmt){
			
			#ifdef _DEBUG
			cout<<"stmt:: "<<toString(stmt)<<std::endl;
			cout<<"Pre:: "<<toString(Pre)<<std::endl;
			#endif
			
			vector<expr> *stmtFormulas=new vector<expr>();
			vector<expr> * tmp=c2z3Stmt->getZ3Stmts(stmt);
			if(tmp==nullptr){
				return new vector<expr>();
			}
			if(tmp->size()<=0){
				vector<expr> * ret=new vector<expr>();
				z3coding.pushAToB(Pre,ret);
				return ret;
			}
			
			z3coding.pushAToB(tmp,stmtFormulas);
			
			
			//init stmtExpr
			if(mapToStmtExprIn.at(stmt)->size()!=stmtFormulas->size()){
				mapToStmtExprIn.at(stmt)->clear();
				for(unsigned i=0;i<stmtFormulas->size();i++){
					mapToStmtExprIn.at(stmt)->push_back(new ValueListSetWithUniversalSet());
				}
			}
			if(mapToStmtExprOut.at(stmt)->size()==1){
				if(mapToStmtExprOut.at(stmt)->at(0)->size()!=stmtFormulas->size()){
					mapToStmtExprOut.at(stmt)->at(0)->clear();
					for(unsigned i=0;i<stmtFormulas->size();i++){
						mapToStmtExprOut.at(stmt)->at(0)->push_back(new ValueListSetWithUniversalSet());
					}
				}
			}
			if(mapToStmtExprOut.at(stmt)->size()==2){
				if(mapToStmtExprOut.at(stmt)->at(0)->size()!=stmtFormulas->size()){
					mapToStmtExprOut.at(stmt)->at(0)->clear();
					for(unsigned i=0;i<stmtFormulas->size();i++){
						mapToStmtExprOut.at(stmt)->at(0)->push_back(new ValueListSetWithUniversalSet());
					}
				}
				if(mapToStmtExprOut.at(stmt)->at(1)->size()!=stmtFormulas->size()){
					mapToStmtExprOut.at(stmt)->at(1)->clear();
					for(unsigned i=0;i<stmtFormulas->size();i++){
						mapToStmtExprOut.at(stmt)->at(1)->push_back(new ValueListSetWithUniversalSet());
					}
				}
			}
			
			
			vector<expr> * _Pre=Pre;
			//add(generateIndexProperties(getIndexEnvironmentBeforStmt(stmt)),_Pre);
			//add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentAfterStmt(stmt),getIndexEnvironmentAfterStmt(stmt)),_Pre);
			_Pre=eliminateSillyFormulas(_Pre);
			for(unsigned i=0;i<stmtFormulas->size();i++){
				
				mapToStmtExprIn.at(stmt)->at(i)->clear();
				mapToStmtExprIn.at(stmt)->at(i)->Union(exprSetToFlowSet(_Pre));
				
				expr stmtF=stmtFormulas->at(i);
				//_Pre=emu.Pos(stmt,_Pre,stmtF,memoryUnitsMap);
				_Pre=emu.Pos(stmt,_Pre,stmtF,i);
				if(mapToStmtExprOut.at(stmt)->size()==1){
					mapToStmtExprOut.at(stmt)->at(0)->at(i)->clear();
					mapToStmtExprOut.at(stmt)->at(0)->at(i)->Union(exprSetToFlowSet(_Pre));
				}
				if(mapToStmtExprOut.at(stmt)->size()==2){
					mapToStmtExprOut.at(stmt)->at(0)->at(i)->clear();
					mapToStmtExprOut.at(stmt)->at(0)->at(i)->Union(exprSetToFlowSet(_Pre));
					mapToStmtExprOut.at(stmt)->at(1)->at(i)->clear();
					mapToStmtExprOut.at(stmt)->at(1)->at(i)->Union(exprSetToFlowSet(_Pre));
				}
			}
			
			//add(generateIndexProperties(getIndexEnvironmentAfterStmt(stmt)),_Pre);
			//add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentAfterStmt(stmt),getIndexEnvironmentAfterStmt(stmt)),_Pre);
			_Pre=eliminateSillyFormulas(_Pre);
			//_Pre=eliminateRetFormulas(_Pre);
			#ifdef _DEBUG
				cout<<"Pos:: "<<toString(_Pre)<<std::endl;
			#endif
			return _Pre;
		}

		vector<expr> * GenAndKillTerminator(vector<expr> * Pre,const clang::Stmt* T, bool trueOrFalse){
			#ifdef _DEBUG
			cout<<"stmt:: "<<toString(T)<<std::endl;
			/* std::size_t found = toString(T).find("(*dest++ = *src++) !=");
			if (found!=std::string::npos){
				cout<<"stmt:: "<<toString(T)<<std::endl;
			}*/
			cout<<"Pre:: "<<toString(Pre)<<std::endl;
			#endif
			
			vector<expr> *stmtFormulas=new vector<expr>();
			vector<expr> * tmp=c2z3Stmt->getZ3Stmts(T);
			if(tmp==nullptr){
				return new vector<expr>();
			}
			if(tmp->size()<=0){
				vector<expr> * ret=new vector<expr>();
				z3coding.pushAToB(Pre,ret);
				return ret;
			}
			
			
			z3coding.pushAToB(tmp,stmtFormulas);
			
			
			
			if(trueOrFalse==false){
				auto conditionFormulas=z3coding.splitLANDFormula(stmtFormulas->back());stmtFormulas->pop_back();
				expr ori_formula=conditionFormulas->at(0);
				for(unsigned i=1;i<conditionFormulas->size();i++){
					ori_formula=ori_formula&&conditionFormulas->at(i);
				}
				stmtFormulas->push_back(!ori_formula);
			}
			else{
				auto conditionFormulas=z3coding.splitLANDFormula(stmtFormulas->back());stmtFormulas->pop_back();
				z3coding.pushAToB(conditionFormulas.get(),stmtFormulas); 
			}
			
			
			//init stmtExpr
			if(mapToStmtExprIn.at(T)->size()!=stmtFormulas->size()){
				mapToStmtExprIn.at(T)->clear();
				for(unsigned i=0;i<stmtFormulas->size();i++){
					mapToStmtExprIn.at(T)->push_back(new ValueListSetWithUniversalSet());
				}
			}
			if(mapToStmtExprOut.at(T)->size()==1){
				if(mapToStmtExprOut.at(T)->at(0)->size()!=stmtFormulas->size()){
					mapToStmtExprOut.at(T)->at(0)->clear();
					for(unsigned i=0;i<stmtFormulas->size();i++){
						mapToStmtExprOut.at(T)->at(0)->push_back(new ValueListSetWithUniversalSet());
					}
				}
			}
			if(mapToStmtExprOut.at(T)->size()==2){
				if(mapToStmtExprOut.at(T)->at(0)->size()!=stmtFormulas->size()){
					mapToStmtExprOut.at(T)->at(0)->clear();
					for(unsigned i=0;i<stmtFormulas->size();i++){
						mapToStmtExprOut.at(T)->at(0)->push_back(new ValueListSetWithUniversalSet());
					}
				}
				if(mapToStmtExprOut.at(T)->at(1)->size()!=stmtFormulas->size()){
					mapToStmtExprOut.at(T)->at(1)->clear();
					for(unsigned i=0;i<stmtFormulas->size();i++){
						mapToStmtExprOut.at(T)->at(1)->push_back(new ValueListSetWithUniversalSet());
					}
				}
			}
			
			
			vector<expr> * _Pre=Pre;
			//add(generateIndexProperties(getIndexEnvironmentBeforStmt(T)),_Pre);
			//add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentBeforStmt(T),getIndexEnvironmentBeforStmt(T)),_Pre);
			_Pre=eliminateSillyFormulas(_Pre);
			for(unsigned i=0;i<stmtFormulas->size();i++){
				mapToStmtExprIn.at(T)->at(i)->clear();
				mapToStmtExprIn.at(T)->at(i)->Union(exprSetToFlowSet(_Pre));
				
				expr stmtF=stmtFormulas->at(i);
				//_Pre=emu.Pos(T,_Pre,stmtF,memoryUnitsMap);
				_Pre=emu.Pos(T,_Pre,stmtF,i);
				
				if(trueOrFalse==true){
					mapToStmtExprOut.at(T)->at(0)->at(i)->clear();
					mapToStmtExprOut.at(T)->at(0)->at(i)->Union(exprSetToFlowSet(_Pre));
				}
				else{
					mapToStmtExprOut.at(T)->at(1)->at(i)->clear();
					mapToStmtExprOut.at(T)->at(1)->at(i)->Union(exprSetToFlowSet(_Pre));
				}
			}
			//add(generateIndexProperties(getIndexEnvironmentAfterStmt(T)),_Pre);
			//add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentAfterStmt(T),getIndexEnvironmentAfterStmt(T)),_Pre);
			_Pre=eliminateSillyFormulas(_Pre);
			#ifdef _DEBUG
				cout<<"Pos:: "<<toString(_Pre)<<std::endl;
			#endif
			/*硬编码，用于做实验*/
			//cout<<"sjdjsajdasjdkjsds::::"<<z3coding.toString(T)<<std::endl;

			if(z3coding.toString(T).find("*p !=")!=std::string::npos){
				_Pre->push_back(hard_coded1(trueOrFalse));
			}
			if(z3coding.toString(T).find("*r !=")!=std::string::npos){
				_Pre->push_back(hard_coded2(trueOrFalse));
			}
			return _Pre;
		}
		
		expr hard_coded1(bool trueOrFalse){
			expr p=c.int_const("p");
			expr lens=c.int_const("len_s");
			if(trueOrFalse){
				return p<lens;
			}
			else{
				return p>=lens;
			}
		}
		expr hard_coded2(bool trueOrFalse){
			expr r=c.int_const("r");
			expr lenreject=c.int_const("len_reject");
			if(trueOrFalse){
				return r<lenreject;
			}
			else{
				return r>=lenreject;
			}
		}
		void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
			//cout<<"processing ... "<<n->getBlockID()<<std::endl;
			for(auto it=outs->begin();it != outs->end(); it++){
				pair<CFGBlock*,FlowSet*>* ele=*it;
				if(ele->second->isUniversalSet()){
					ele->second->setNonUniversalSetWhenIsUniversalSet();
				}
			}
			
			vector<expr> * Pre=flowSetToExprSet(in);
			//add(generateIndexProperties(getIndexEnvironmentBeforBlock(n)),Pre);
			//add(getMultiIndexesRelationAnalysis(getMultiIndexEnvironmentBeforBlock(n),getIndexEnvironmentBeforBlock(n)),Pre);
			Pre=eliminateSillyFormulas(Pre);
			if(outs->size()==2){
				const Stmt* T=n->getTerminatorCondition();
				if(T==nullptr){
					std::cerr<<"flowThrouth: TerminatorCondition can not be null! "<<std::endl;	
				}
				unsigned count=0;
				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
					CFGElement element=(*iterblock);	
					if(element.getKind()==CFGElement::Kind::Statement){
						const Stmt* it=((CFGStmt*)&element)->getStmt();
						//cout<<"processing ... "<<z3coding.toString(it)<<std::endl;
						/*if(it==T) break;*/
						//the condition expression will appear within the set of 
						//statements in the block (usually the last statement) 
						if(n->size()>0&&count==n->size()-1){
							T=it;
							break;
						}
						//cout<<toString(it)<<std::endl;
						FlowSet* pin=mapToStmtIn.at(it);
						pin->clear();
						pin->Union(exprSetToFlowSet(Pre));
						
						Pre=GenAndKill(Pre,it);
						
						vector<FlowSet*>* pout=mapToStmtOut.at(it);
						pout->at(0)->clear();
						pout->at(0)->Union(exprSetToFlowSet(Pre));
						
						count++;
					}
				}
				//cout<<toString(T)<<std::endl;
				FlowSet* pin=mapToStmtIn.at(T);
				pin->clear();
				pin->Union(exprSetToFlowSet(Pre));
				
				vector<expr> * truePos=GenAndKillTerminator(Pre,T,true);
				vector<expr> * falsePos=GenAndKillTerminator(Pre,T,false);
				
				vector<FlowSet*>* pout=mapToStmtOut.at(T);
				pout->at(0)->clear();pout->at(1)->clear();
				pout->at(0)->Union(exprSetToFlowSet(truePos));
				pout->at(1)->Union(exprSetToFlowSet(falsePos));
				
				pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
				ValueListSetWithUniversalSet *tureFlow=(ValueListSetWithUniversalSet*)tureBranch->second;
				pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
				ValueListSetWithUniversalSet *falseFlow=(ValueListSetWithUniversalSet*)falseBranch->second;
				
				FlowSet * trueFlowSet=exprSetToFlowSet(truePos);
				tureFlow->Union(trueFlowSet);
				
				FlowSet * falseFlowSet=exprSetToFlowSet(falsePos);
				falseFlow->Union(falseFlowSet);
				
			}
			else if(outs->size()==1){
				Stmt* T=n->getTerminatorCondition();
				if(T!=nullptr){
					std::cerr<<"flowThrouth: TerminatorCondition must be null! "<<std::endl;	
				}
				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
					CFGElement element=(*iterblock);
					if(element.getKind()==CFGElement::Kind::Statement){
						const Stmt* it=((CFGStmt*)&element)->getStmt();
						//cout<<"processing ... "<<z3coding.toString(it)<<std::endl;
						FlowSet* pin=mapToStmtIn.at(it);
						pin->clear();
						pin->Union(exprSetToFlowSet(Pre));
						
						Pre=GenAndKill(Pre,it);
						
						vector<FlowSet*>* pout=mapToStmtOut.at(it);
						pout->at(0)->clear();
						pout->at(0)->Union(exprSetToFlowSet(Pre));
					}
				}
				pair<CFGBlock*,FlowSet*>* out=outs->front();
				ValueListSetWithUniversalSet *outFlow=(ValueListSetWithUniversalSet*)out->second;

				FlowSet * flowSet=exprSetToFlowSet(Pre);
				outFlow->Union(flowSet);
			}
		}

		
		
		
		FlowSet * meet(vector<expr>* in1,vector<expr>* in2){
			vector<expr>* out=new vector<expr>();
			for(expr e1:*in1){
				for(expr e2:*in2){
					expr r=emu.meet(e1,e2);
					if(!z3coding.equal(r,z3coding._error)){
						out->push_back(r);
					}
				}
			}
			return exprSetToFlowSet(out);
		}
		
	void print(){
		for (std::map<CFGBlock*, FlowSet*>::iterator it=mapToBlockIn.begin(); it!=mapToBlockIn.end(); ++it){
			std::cout <<"--------[B"<< it->first->getBlockID ()<<"]" << " in :--------"<<std::endl; 
			std::cout<<toString(flowSetToExprSet(it->second))<<std::endl;
			list<pair<CFGBlock*,FlowSet*>*> * outs=mapToBlockOut.at(it->first);
			for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator outsIt = outs->begin(); 
									outsIt != outs->end(); outsIt++){
				pair<CFGBlock*,FlowSet*> *ele=*outsIt;
				if(ele->first==nullptr) continue;
				std::cout <<"----------[B"<< it->first->getBlockID()<<"]"<<"-> [B" <<ele->first->getBlockID()<<"]"<<" out -------:"<<std::endl; 
				std::cout<<toString(flowSetToExprSet(ele->second))<<std::endl;
			}
		}

	}
	void printStmtExprAnalysis(){
		for (map<const clang::Stmt*, vector<FlowSet*>*>::iterator it=mapToStmtExprIn.begin(); it!=mapToStmtExprIn.end(); ++it){
			std::cout <<z3coding.toString(it->first) << " -----------in :-------------"<<std::endl;
			printFlowSets(it->second);
			
			vector<vector<FlowSet*>*>* outs=mapToStmtExprOut.at(it->first);
			if(outs->size()==1){
				std::cout <<z3coding.toString(it->first) << " ------------out :------------"<<std::endl;
				printFlowSets(outs->at(0));
			}
			if(outs->size()==2){
				std::cout <<z3coding.toString(it->first) << " ------------true out :------------"<<std::endl;
				printFlowSets(outs->at(0));
				std::cout <<z3coding.toString(it->first) << " ------------false out :------------"<<std::endl;
				printFlowSets(outs->at(1));
			}
		}
	}
	
	void copy(FlowSet  *&from,FlowSet  *&to){
			to=from->clone();
	}
		//used in dataflow analysis
		bool equal(FlowSet  *&from,FlowSet  *&to){
			return from->equal(to);
		}
		FlowSet * newinitialFlow(){
			return new ValueListSetWithUniversalSet(true); 
		}
		FlowSet * entryInitialFlow(){return new ValueListSetWithUniversalSet();}

		void merge(FlowSet  * &in1,FlowSet  *&in2,FlowSet  *&out){
			if(in1->isUniversalSet()&&in2->isUniversalSet()) {
				out=in1->clone();
				return;
			}
			if(in1->isUniversalSet()){
				out=in2->clone();
				return;
			}
			if(in2->isUniversalSet()) {
				out=in1->clone();
				return;
			}
			out=meet(flowSetToExprSet(in1),flowSetToExprSet(in2));
			return;
		}
};
#endif
