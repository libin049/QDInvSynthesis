#ifndef _LiftAnalysis_H
#define _LiftAnalysis_H
#include "Formula.h"
#include "EnvironmentAnalysisUtil.h"
#include "DataFlowAnalysis.h"
#include "UserSupplied.h"
#include "MemoryUtil.h"
#include "Z3Coding.h"
#include "MultiIndexesRelationAnalysis.h"
#include "AtomVariableAnalysis.h"

class LiftAnalysis: public IntraDataFlowAnalysis{
	private:
		context &c;
		EnvironmentAnalysis *envAnalysis;
		AtomVariablaAnalysis *indexAnalysis; 
		Z3Coding &z3coding;
		UserSupplied * userSupplied;
		MemoryUtil &mu;
		PointerAnalysis* pointerAnalysis;
		C2Z3* c2z3Stmt;
		MultiIndexesRelationAnalysis* multiIndexesRelationAnalysis;
		std::string toString(vector<z3::expr>* exprs){
			std::string ret="";
			if(exprs==nullptr) return "";
			for(auto it=exprs->begin();it!=exprs->end();it++){
				z3::expr e=(z3::expr) *it;
				//std::string eName=Z3_ast_to_string(e.ctx(),e);
				std::string eName=z3coding.toString(e);
				ret+=eName+";\n ";
			}
			return ret;
		}

		std::string toString(FlowSet* in){
			if(in->isUniversalSet()){
				return "UniversalSet";
			}
			return toString(flowSetToExprSet(in));
		}

		vector<expr> * flowSetToExprSet(FlowSet * flowSet){
			vector<Property*> * propertySet=flowSet->toVector();
			vector<expr> * exprSet=new vector<expr>();
			for(Property* p: *propertySet){
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
		void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
			for(auto it=outs->begin();it != outs->end(); it++){
				pair<CFGBlock*,FlowSet*>* ele=*it;
				if(ele->second->isUniversalSet()){
					ele->second->setNonUniversalSetWhenIsUniversalSet();
				}
			}
			
			FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(in),
				indexAnalysis->getMapToBlockIn()->at(n),multiIndexesRelationAnalysis->getMapToBlockIn()->at(n));
			FlowSet* tmpx2=in->clone();tmpx2->Union(tmpx1);
			in=reduce(genQ(indexAnalysis->getMapToBlockIn()->at(n),envAnalysis->getMapToBlockIn()->at(n),tmpx2));
			in=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->getMapToBlockIn()->at(n),in);
			FlowSet * Pre=in->clone();

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
						/*if(it==T) break;*/
						//the condition expression will appear within the set of 
						//statements in the block (usually the last statement) 
						if(n->size()>0&&count==n->size()-1){
							T=it;
							break;
						}

						FlowSet * Pos=userSupplied->newinitialFlow();
						flowThrouth(it,Pre,Pos);
						Pre=Pos->clone();
						count++;
					}
				}

				FlowSet * truePos=userSupplied->newinitialFlow();
				FlowSet * falsePos=userSupplied->newinitialFlow();
				flowThrouth(T,Pre,truePos,falsePos);
				pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
				FlowSet *tureFlow=(FlowSet*)tureBranch->second;
				pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
				FlowSet *falseFlow=(FlowSet*)falseBranch->second;

				tureFlow->Union(truePos);
				falseFlow->Union(falsePos);

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
						FlowSet * Pos=userSupplied->newinitialFlow();
						flowThrouth(it,Pre,Pos);
						Pre=Pos->clone();
					}
				}
				pair<CFGBlock*,FlowSet*>* out=outs->front();
				FlowSet *outFlow=(FlowSet*)out->second;

				outFlow->Union(Pre);
			}
		}
		FlowSet* _filterNonSimpleFormula(FlowSet  *from){
			FlowSet* result=userSupplied->entryInitialFlow();
			result->clear();
			vector<Property *>* invec=from->toVector();
			for(Property * p:*invec){
				if(!userSupplied->isSimpleProperty((Formula*)p)){
					result->add(p);
				}
			}
			return result;
		}
		bool _existNonSimpleFormula(FlowSet  *from){
			vector<Property *>* invec=from->toVector();
			for(Property * p:*invec){
				if(!userSupplied->isSimpleProperty((Formula*)p)){
					return true;
				}
			}
			return false;
		}
		FlowSet* _filterSimpleFormula(FlowSet  *from){
			FlowSet* result=userSupplied->entryInitialFlow();
			result->clear();
			vector<Property *>* invec=from->toVector();
			for(Property * p:*invec){
				if(userSupplied->isSimpleProperty((Formula*)p)){
					result->add(p);
				}
			}
			return result;
		}
		void _nonSimpleFormulasMerge(FlowSet  *&in1,FlowSet  *&in2,FlowSet *&out){
			vector<Property *>* in1vec=in1->toVector();
			vector<Property *>* in2vec=in2->toVector();
			for(Property * p1:*in1vec){
				for(Property * p2:*in2vec){
					Formula *f1=(Formula *)p1;
					Formula *f2=(Formula *)p2;
					Formula * r=_nonSimpleFormulaMeet(f1,f2);
					if(!z3coding.equal(r->formula,z3coding._error)){
						out->add(r);
					}
				}
			}
		}
		Formula * _nonSimpleFormulaMeet(Formula * f1,Formula *f2){
			expr e1= f1->formula;
			expr e2= f2->formula;
			return new Formula(_nonSimpleFormulaMeet(e1,e2));
		}
		expr _nonSimpleFormulaMeet(expr e1,expr e2){
			if(z3coding.isPhiFormula(e1)&&z3coding.isPhiFormula(e2)){
				if(z3coding.equal(e1,e2)){
					return e1;
				}
				//cerr<<"_nonSimpleFormulaMeet is wrong!"<<std::endl;
				return z3coding._error;
			}
			else if(z3coding.isPhiFormula(e1)&&z3coding.isForAllFormula(e2)){
				return meetPhiFormula_ForAllFormula(e1,e2);
			}

			else if(z3coding.isForAllFormula(e1)&&z3coding.isPhiFormula(e2)){
				return meetPhiFormula_ForAllFormula(e2,e1);
			}
			else if(z3coding.isForAllFormula(e1)&&z3coding.isForAllFormula(e2)){
				return meetForAllFormula_ForAllFormula(e1,e2);
			}
			//cerr<<"_nonSimpleFormulaMeet is wrong!"<<std::endl;
			return z3coding._error;
		}
		expr _merge(expr f1,expr f2){
			FlowSet* tmp1=userSupplied->newinitialFlow();tmp1->clear();
			FlowSet* tmp2=userSupplied->newinitialFlow();tmp2->clear();
			tmp1->add(new Formula(f1));
			tmp2->add(new Formula(f2));
			FlowSet* out=userSupplied->newinitialFlow();out->clear();
			merge(tmp1,tmp2,out);
			if(out->size()!=0){
				Formula* f=(Formula*)(out->toVector()->at(0));
				return f->formula;
			}
			else{
				//cerr<<"_merge is wrong!"<<std::endl;
				return z3coding._error;
			}
			
		}
		
		expr meetForAllFormula_ForAllFormula(expr forAllFormula1,expr forAllFormula2){
			//cout<<forAllFormula1<<"---meet---"<<forAllFormula1<<std::endl;
			expr forallBody1=z3coding.getQuantifierFormulaBody(forAllFormula1);
			expr forallBody2=z3coding.getQuantifierFormulaBody(forAllFormula2);
			//cout<<forallBody1<<"---meet---"<<forallBody2<<std::endl;
			expr bodyMeetResult=_merge(forallBody1,forallBody2);
			if(z3coding.checkError(bodyMeetResult)){
				return z3coding._error;
			}
			expr forallHead1=z3coding.getQuantifierFormulaHead(forAllFormula1);
			expr forallHead2=z3coding.getQuantifierFormulaHead(forAllFormula2);
			if(z3coding.equal(forallHead1,forallHead2)){
				expr quantifier1=z3coding.getQuantifier(forAllFormula1);
				expr step1=z3coding.getForAllFormulaStep(forAllFormula1);
				expr step1Formula=z3coding.getForAllFormulaStepFormula(forAllFormula1);
				expr quantifierBegin1=z3coding.getForAllFormulaBegin(forAllFormula1);
				expr quantifierEnd1=z3coding.getForAllFormulaEnd(forAllFormula1);
				expr quantifierBeginFormula1=z3coding.getForAllFormulaBeginFormula(forAllFormula1);
				expr quantifierEndFormula1=z3coding.getForAllFormulaEndFormula(forAllFormula1);
				expr quantifierExtendFormula1=z3coding.getForAllFormulaExtendFormula(forAllFormula1);
				
				if(z3coding.equal(quantifierExtendFormula1,z3coding._error)){
					return z3coding.constructForAllFormula(quantifier1,quantifierBeginFormula1,
						quantifierEndFormula1,step1Formula,bodyMeetResult);
				}
				else{
					return z3coding.constructForAllFormula(quantifier1,quantifierExtendFormula1,quantifierBeginFormula1,
						quantifierEndFormula1,step1Formula,bodyMeetResult);
				}
			}
			else{
				return z3coding._error;
			}

		}
		
		
		/*expr meetForAllFormula_ForAllFormula(expr forAllFormula1,expr forAllFormula2){
			expr forallBody1=z3coding.getQuantifierFormulaBody(forAllFormula1);
			expr forallBody2=z3coding.getQuantifierFormulaBody(forAllFormula2);
			//cout<<forallBody1<<"---meet---"<<forallBody2<<std::endl;
			expr bodyMeetResult=_merge(forallBody1,forallBody2);
			if(z3coding.checkError(bodyMeetResult)){
				return z3coding._error;
			}

			expr quantifier1=z3coding.getQuantifier(forAllFormula1);
			expr step1=z3coding.getForAllFormulaStep(forAllFormula1);
			expr step1Formula=z3coding.getForAllFormulaStepFormula(forAllFormula1);
			expr quantifierBegin1=z3coding.getForAllFormulaBegin(forAllFormula1);
			expr quantifierEnd1=z3coding.getForAllFormulaEnd(forAllFormula1);
			expr quantifierBeginFormula1=z3coding.getForAllFormulaBeginFormula(forAllFormula1);
			expr quantifierEndFormula1=z3coding.getForAllFormulaEndFormula(forAllFormula1);
			expr quantifierExtendFormula1=z3coding.getForAllFormulaExtendFormula(forAllFormula1);

			expr quantifier2=z3coding.getQuantifier(forAllFormula2);
			expr step2=z3coding.getForAllFormulaStep(forAllFormula2);
			expr quantifierBegin2=z3coding.getForAllFormulaBegin(forAllFormula2);
			expr quantifierEnd2=z3coding.getForAllFormulaEnd(forAllFormula2);
			expr quantifierBeginFormula2=z3coding.getForAllFormulaBeginFormula(forAllFormula2);
			expr quantifierEndFormula2=z3coding.getForAllFormulaEndFormula(forAllFormula2);
			expr quantifierExtendFormula2=z3coding.getForAllFormulaExtendFormula(forAllFormula2);

			if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
					||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
				return z3coding._error;
			}

			if(!z3coding.checkError(quantifierExtendFormula1)||!z3coding.checkError(quantifierExtendFormula2)){
				expr quantifierExtendFormula2To1=z3coding.substitute(quantifierExtendFormula2,quantifier2,quantifier1);
				if(!z3coding.equal(quantifierExtendFormula2To1,quantifierExtendFormula1)){
					return z3coding._error;
				}
			}
			
			
			if(z3coding.equal(step1,step2)
					&&Z3_is_eq_func_decl(c,quantifierBegin1.decl(),quantifierBegin2.decl())
					&&z3coding.equal(quantifierBegin1,quantifierBegin2)
					&&Z3_is_eq_func_decl(c,quantifierEnd1.decl(),quantifierEnd2.decl())
					&& z3coding.equal(quantifierEnd1,quantifierEnd2)){
				if(!z3coding.checkError(quantifierExtendFormula1)&&!z3coding.checkError(quantifierExtendFormula2)){
					return z3coding.constructForAllFormula(quantifier1,quantifierExtendFormula1,quantifierBeginFormula1,
							quantifierEndFormula1,step1Formula,bodyMeetResult);
				}
				else{
					return z3coding.constructForAllFormula(quantifier1,quantifierBeginFormula1,quantifierEndFormula1,
							step1Formula,bodyMeetResult);
				}
			}

			else{
				return z3coding._error;
			}

		}*/
		expr getStepFromIndex(const clang::Stmt *clangStmt,expr index){
			FlowSet* out=indexAnalysis->mapToStmtOut.at(clangStmt);
			ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
			for(Property* p: vlsOut->elements){
				AtomVariabla * av=(AtomVariabla *)p;
				if(z3coding.equal(av->scalaVarz3coding,index)){
					if(av->hasStep()){
						return av->stepz3coding;
					}
					else{
						return z3coding._error;
					}
				}
			}
			return z3coding._error;
		}
		expr getStepFromIndex(FlowSet* indexEnv,expr index){
			FlowSet* out=indexEnv;
			ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
			for(Property* p: vlsOut->elements){
				AtomVariabla * av=(AtomVariabla *)p;
				if(z3coding.equal(av->scalaVarz3coding,index)){
					if(av->hasStep()){
						return av->stepz3coding;
					}
					else{
						return z3coding._error;
					}
				}
			}
			return z3coding._error;
		}
		expr constructPhiFormula(expr index,expr init,expr step){
			//cout<<"step is "<<step<<std::endl;
			bool stepLtZeroFlag=mu.isLtZero(step);
			bool stepGtZeroFlag=mu.isGtZero(step);

			vector<expr> * cons=new vector<expr>();
			vector<expr> * initcons=z3coding.getConstsWithQuantifier(init);
			z3coding.pushAToB(initcons,cons);
			vector<expr> * stepcons=z3coding.getConstsWithQuantifier(step);
			z3coding.pushAToB(stepcons,cons);
			cons->push_back(index);
			expr quantifier=constructNewQuantifierName(cons);

			if(stepLtZeroFlag){
				return z3coding.constructPhiFormula(quantifier,index<quantifier,quantifier<=init,init,step);
			}
			else if(stepGtZeroFlag){
				return z3coding.constructPhiFormula(quantifier,init<=quantifier,quantifier<index,init,step);
			}
			//when step is not number, something is wrong!
			//e.g. i=i+h
			//however, we thing this can be processed, we will process that later! 
			//cerr<<"constructPhiFormula is wrong!"<<std::endl;
			return z3coding._error;
		}
		expr constructNewQuantifierName(vector<expr> * cons){
			int size=1000;
			for(int i=0;i<size;i++){
				std::string quantifierName="_i"+std::to_string(i);
				expr quantifier=c.int_const(quantifierName.c_str());
				if(!z3coding.isIn(quantifier,cons)){
					return quantifier;
				}
			}
			std::cerr<<"LiftAnalysis::constructNewQuantifierName: something is wrong!"<<std::endl;
			return z3coding._error;
		}
		
		expr meetPhiFormula_ForAllFormula(expr phiFormula,expr forAllFormula){
			
			expr phiHead=z3coding.getQuantifierFormulaHead(phiFormula);
			expr phiqualifier=z3coding.getPhiQuantifier(phiFormula);
			expr forallHead=z3coding.getQuantifierFormulaHead(forAllFormula);
			expr forallqualifier=z3coding.getQuantifier(forAllFormula);
			expr newPhiHead=z3coding.substitute(phiHead,phiqualifier,forallqualifier);
			if(z3coding.equal(newPhiHead,forallHead)){
				return forAllFormula;
			}
			return z3coding._error;
		}
		
		/*expr meetPhiFormula_ForAllFormula(expr phiFormula,expr forAllFormula){
			expr phiBegin=z3coding.getPhiBegin(phiFormula);
			expr phiEnd=z3coding.getPhiEnd(phiFormula);
			expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
			expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
			expr phiStep=z3coding.getPhiStep(phiFormula);

			expr forallStep=z3coding.getForAllFormulaStep(forAllFormula);
			expr forallBegin=z3coding.getForAllFormulaBegin(forAllFormula);
			expr forallEnd=z3coding.getForAllFormulaEnd(forAllFormula);
			expr forallBeginFormula=z3coding.getForAllFormulaBeginFormula(forAllFormula);
			expr forallEndFormula=z3coding.getForAllFormulaEndFormula(forAllFormula);

			if(z3coding.equal(phiStep,forallStep)
					&&Z3_is_eq_func_decl(c,forallBeginFormula.decl(),phiBeginFormula.decl())
					&& z3coding.equal(forallBegin,phiBegin)
					&&Z3_is_eq_func_decl(c,forallEndFormula.decl(),phiEndFormula.decl())
					&& z3coding.equal(forallEnd,phiEnd)){
				return forAllFormula;
			}
			return z3coding._error;
		}*/
		
		void flowThrouth(const clang::Stmt* stmt,FlowSet* &in,FlowSet*&out){
			
			#ifdef _DEBUG
			cout<<"stmt:: "<<toString(stmt)<<std::endl;
			cout<<"Pre:: "<<toString(in)<<std::endl;
			#endif

			FlowSet  * Pos=userSupplied->newinitialFlow();Pos->clear();
			/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);*/
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
			if(exprs==nullptr){//f'(a)
				FlowSet  * simpleFormulain=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				
				FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(in,stmt);
				simpleFormulain->Union(deqResult);
				
				userSupplied->flowThrouth(stmt,-1,simpleFormulain,simpleFormulaPos);
				Pos->Union(simpleFormulaPos);
			}
			else {
				vector<expr> *stmtFormulas=new vector<expr>();
				z3coding.pushAToB(exprs,stmtFormulas);
				/*vector<expr> *stmtFormulas=z3coding.boolSortFiltering(exprs);*/
				FlowSet  * nonSimpleFormulaPre=_filterNonSimpleFormula(in);
				FlowSet  * nonSimpleFormulaPos=in->clone();
				
				FlowSet * simpleFormulain=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				for(unsigned i=0;i<stmtFormulas->size();i++){
					expr stmtFormula=stmtFormulas->at(i);
					#ifdef _DEBUG
						//cout<<"stmtFormula:: "<<stmtFormula<<std::endl;
						//cout<<"nonSimpleFormulaPre:: "<<toString(nonSimpleFormulaPre)<<std::endl;
						//cout<<"simpleFormulain:: "<<toString(simpleFormulain)<<std::endl;
					#endif
					if(z3coding.isAssignment(stmtFormula)){
						nonSimpleFormulaPos=transferWithEnvironment(stmt,stmtFormula,nonSimpleFormulaPre);
						if(isIndexInitStmt(stmt,stmtFormula.arg(0))){
							Property* tmpp=genPhi(stmt,stmtFormula.arg(0));
							if(tmpp!=nullptr){
								nonSimpleFormulaPos->add(tmpp);
							}
						}
						else if(isIndexUpdate(stmt,stmtFormula.arg(0))){
							nonSimpleFormulaPos->Union(handleInterval(stmtFormula.arg(0),nonSimpleFormulaPre));
						}
					}
					else{
						nonSimpleFormulaPos=transferWithEnvironment(stmt,stmtFormula,nonSimpleFormulaPre);
					}
					
					
					FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(nonSimpleFormulaPre,stmt);
					simpleFormulain->Union(deqResult);
					userSupplied->flowThrouth(stmt,i,simpleFormulain,simpleFormulaPos);
					
					
					FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(nonSimpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					FlowSet* tmpx2=nonSimpleFormulaPos->clone();tmpx2->Union(tmpx1);
					FlowSet* tmp=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmpx2));
					tmp=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp); 
					nonSimpleFormulaPos=tmp->clone();
					
					//gen more forall properties according to simple properties
					FlowSet* posTmp=userSupplied->newinitialFlow();posTmp->clear();
					_generateForallFoumualBySimpleFormula(simpleFormulain,nonSimpleFormulaPre,stmt,i,posTmp);
					nonSimpleFormulaPos->Union(posTmp);
					
					
					tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(simpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					tmpx2=simpleFormulaPos->clone();tmpx2->Union(tmpx1);
					tmp=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmpx2));
					tmp=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp); 
					simpleFormulaPos=tmp->clone();
					
					nonSimpleFormulaPre=nonSimpleFormulaPos->clone();
					simpleFormulain=simpleFormulaPos->clone();
					#ifdef _DEBUG
						//cout<<"nonSimpleFormulaPos:: "<<toString(nonSimpleFormulaPos)<<std::endl;
						//cout<<"simpleFormulaPos:: "<<toString(simpleFormulaPos)<<std::endl;
					#endif
					
				}
				Pos->Union(simpleFormulaPos);
				Pos->Union(nonSimpleFormulaPos);
				
			}
			
			
			out->clear();
			FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(Pos),
				indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
			FlowSet* tmpx2=Pos->clone();tmpx2->Union(tmpx1);
			FlowSet* tmp=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),envAnalysis->mapToStmtOut.at(stmt)->at(0),tmpx2));
			tmp=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(0),tmp); 
			out->Union(tmp);

			#ifdef _DEBUG
			cout<<"Pos:: "<<toString(out)<<std::endl;
			#endif
		}
		void flowThrouth(const clang::Stmt* stmt,FlowSet* &in,FlowSet*&trueOut,FlowSet*&falseOut){
			#ifdef _DEBUG
			cout<<"stmt:: "<<toString(stmt)<<std::endl;
			cout<<"Pre:: "<<toString(in)<<std::endl;
			#endif


			FlowSet  * truePos=userSupplied->newinitialFlow();truePos->clear();
			FlowSet  * falsePos=userSupplied->newinitialFlow();falsePos->clear();
			/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);*/
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
			if(exprs==nullptr){//f'(a)
				FlowSet  * simpleFormulain=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaTruePos=userSupplied->newinitialFlow();simpleFormulaTruePos->clear();
				FlowSet  * simpleFormulaFalsePos=userSupplied->newinitialFlow();simpleFormulaFalsePos->clear();
				
				FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(in,stmt);
				simpleFormulain->Union(deqResult);
				
				userSupplied->flowThrouth(stmt,-1,simpleFormulain,simpleFormulaTruePos,simpleFormulaFalsePos);
				truePos->Union(simpleFormulaTruePos);
				falsePos->Union(simpleFormulaFalsePos);
				
				trueOut->clear();falseOut->clear();
				FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(truePos),
					indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
				FlowSet* tmpx2=truePos->clone();tmpx2->Union(tmpx1);
				FlowSet* tmp1=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),envAnalysis->mapToStmtOut.at(stmt)->at(0),tmpx2));
				tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(0),tmp1);
				trueOut->Union(tmp1);
				
				
				tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(falsePos),
					indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
				tmpx2=falsePos->clone();tmpx2->Union(tmpx1);
				FlowSet* tmp2=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),envAnalysis->mapToStmtOut.at(stmt)->at(1),tmpx2));
				tmp2=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(1),tmp2);
				falseOut->Union(tmp2);
			}
			else {
				vector<expr> *stmtFormulas=new vector<expr>();
				z3coding.pushAToB(exprs,stmtFormulas);
				/*vector<expr> *stmtFormulas=z3coding.boolSortFiltering(exprs);*/
				FlowSet  * nonSimpleFormulaIn=_filterNonSimpleFormula(in);
				FlowSet  * nonSimpleFormulaPos=in->clone();
				
				FlowSet  * simpleFormulaIn=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				unsigned i=0;
				while(stmtFormulas->size()>0&&i<stmtFormulas->size()-1){
					expr stmtFormula=stmtFormulas->at(i);
					#ifdef _DEBUG
						//cout<<"stmtFormula:: "<<stmtFormula<<std::endl;
						//cout<<"nonSimpleFormulaIn:: "<<toString(nonSimpleFormulaIn)<<std::endl;
						//cout<<"simpleFormulaIn:: "<<toString(simpleFormulaIn)<<std::endl;
					#endif
					if(z3coding.isAssignment(stmtFormula)){
						nonSimpleFormulaPos=transferWithEnvironment(stmt,stmtFormula,nonSimpleFormulaIn);
						if(isIndexInitStmt(stmt,stmtFormula.arg(0))){
							Property* tmpp=genPhi(stmt,stmtFormula.arg(0));
							if(tmpp!=nullptr){
								nonSimpleFormulaPos->add(tmpp);
							}
						}
						else if(isIndexUpdate(stmt,stmtFormula.arg(0))){
							nonSimpleFormulaPos->Union(handleInterval(stmtFormula.arg(0),nonSimpleFormulaIn));
						}
					}
					else{
						nonSimpleFormulaPos=transferWithEnvironment(stmt,stmtFormula,nonSimpleFormulaIn);
					}
					
				
					//process simpleFormulas
					
					FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(nonSimpleFormulaIn,stmt);
					simpleFormulaIn->Union(deqResult);
					userSupplied->flowThrouth(stmt,i,simpleFormulaIn,simpleFormulaPos);
					
					//gen more forall properties according to simple properties
					FlowSet* posTmp=userSupplied->newinitialFlow();posTmp->clear();
					_generateForallFoumualBySimpleFormula(simpleFormulaIn,nonSimpleFormulaIn,stmt,i,posTmp);
					nonSimpleFormulaPos->Union(posTmp);
					
					
					FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(simpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					FlowSet* tmpx2=simpleFormulaPos->clone();tmpx2->Union(tmpx1);
					FlowSet* tmp1=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmpx2));
					tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp1);
					simpleFormulaPos=tmp1->clone();
					
					tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(nonSimpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					tmpx2=nonSimpleFormulaPos->clone();tmpx2->Union(tmpx1);
					tmp1=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmpx2));
					tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp1);
					nonSimpleFormulaPos=tmp1->clone();
					
					
					simpleFormulaIn=simpleFormulaPos->clone();
					nonSimpleFormulaIn=nonSimpleFormulaPos->clone();
					i++;
					#ifdef _DEBUG
						//cout<<"nonSimpleFormulaPos:: "<<toString(nonSimpleFormulaPos)<<std::endl;
						//cout<<"simpleFormulaPos:: "<<toString(simpleFormulaPos)<<std::endl;
					#endif
				}
				
				FlowSet  * nonSimpleFormulaTruePos=nonSimpleFormulaIn->clone();
				FlowSet  * nonSimpleFormulaFalsePos=nonSimpleFormulaIn->clone();
				
				FlowSet  * simpleFormulaTruePos=simpleFormulaIn->clone();
				FlowSet  * simpleFormulaFalsePos=simpleFormulaIn->clone();
				if(stmtFormulas->size()>0&&i==stmtFormulas->size()-1){
					#ifdef _DEBUG
						//cout<<"stmtFormula:: "<<stmtFormulas->at(i)<<std::endl;
						//cout<<"nonSimpleFormulaIn:: "<<toString(nonSimpleFormulaIn)<<std::endl;
						//cout<<"simpleFormulaIn:: "<<toString(simpleFormulaIn)<<std::endl;
					#endif
					nonSimpleFormulaTruePos=transferWithEnvironment(stmt,stmtFormulas->at(i),nonSimpleFormulaIn);
					nonSimpleFormulaFalsePos=nonSimpleFormulaTruePos->clone();
					
					FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(nonSimpleFormulaIn,stmt);
					simpleFormulaIn->Union(deqResult);
					userSupplied->flowThrouth(stmt,i,simpleFormulaIn,simpleFormulaTruePos,simpleFormulaFalsePos);
					#ifdef _DEBUG
						/*cout<<"nonSimpleFormulaTruePos:: "<<toString(nonSimpleFormulaTruePos)<<std::endl;
						cout<<"nonSimpleFormulaFalsePos:: "<<toString(nonSimpleFormulaFalsePos)<<std::endl;
						cout<<"simpleFormulaTruePos:: "<<toString(simpleFormulaTruePos)<<std::endl;
						cout<<"simpleFormulaFalsePos:: "<<toString(simpleFormulaFalsePos)<<std::endl;*/
					#endif
					
					//gen more forall properties according to simple properties
					FlowSet* trueTmp=userSupplied->newinitialFlow();trueTmp->clear();
					FlowSet* falseTmp=userSupplied->newinitialFlow();falseTmp->clear();
					_generateForallFoumualBySimpleFormula(simpleFormulaIn,nonSimpleFormulaIn,stmt,i,trueTmp,falseTmp);
					
					nonSimpleFormulaTruePos->Union(trueTmp);
					nonSimpleFormulaFalsePos->Union(falseTmp);
				}
				truePos->Union(simpleFormulaTruePos);
				truePos->Union(nonSimpleFormulaTruePos);
				falsePos->Union(simpleFormulaFalsePos);
				falsePos->Union(nonSimpleFormulaFalsePos);
					
				trueOut->clear();falseOut->clear();
				
				FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(truePos),
						indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
				FlowSet* tmpx2=truePos->clone();tmpx2->Union(tmpx1);
				FlowSet* tmp1=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),
						envAnalysis->mapToStmtOut.at(stmt)->at(0),tmpx2));
				//cout<<"-----------true env--------------"<<std::endl;
				//cout<<toString(envAnalysis->mapToStmtOut.at(stmt)->at(0))<<std::endl;
				tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(0),tmp1);
				trueOut->Union(tmp1);
				
				
				tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(falsePos),
						indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
				tmpx2=falsePos->clone();tmpx2->Union(tmpx1);
				FlowSet* tmp2=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),
						envAnalysis->mapToStmtOut.at(stmt)->at(1),tmpx2));
				//cout<<"-----------false env--------------"<<std::endl;
				//cout<<toString(envAnalysis->mapToStmtOut.at(stmt)->at(1))<<std::endl;
				tmp2=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(1),tmp2);
				falseOut->Union(tmp2);
			}
			
			

#ifdef _DEBUG
			cout<<"truePos:: "<<toString(trueOut)<<std::endl;
			cout<<"falseOut:: "<<toString(falseOut)<<std::endl;
#endif
		}
	
		/**
		 * @brief sometimes, quantified property need generate more universal 
		 * 			quantifier properties according to simple property
		 * 		∀x.x ∈ [0,1,i),max>=A[x] and max<A[i] generates  implies ∀x.x ∈ [0,1,i),A[i]>=A[x]
		 * @param in
		 * @param stmt
		 * @return 
		 */
		vector<expr> * __forAllFormulaDegeneratedToSimpleFormula(expr forAllFormula,const clang::Stmt* clangstmt,int count){
			vector<expr> * result=new vector<expr>();
			vector<expr> * relatedMemoryUnits=new vector<expr>();
			vector<expr> * tmp;
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(clangstmt);
			if(exprs==nullptr||exprs->size()==0){
				return result;
			}
			expr stmt=exprs->at(count);
			if(stmt.is_bool()&&z3coding.isAssignment(stmt)){
				stmt=stmt.arg(0);
				tmp=z3coding.getMemoryUnits(stmt.arg(1));
			}
			else{
				tmp=z3coding.getMemoryUnits(stmt);
			}
			add(tmp,relatedMemoryUnits);
			expr simpleFormulaOfForAllFormula=getForallFormulaInnerSimpleFormula(forAllFormula);
			vector<expr>* simpleFormulaUnits=z3coding.getMemoryUnits(simpleFormulaOfForAllFormula);
			for(expr relatedMemoryUnit:*relatedMemoryUnits){
				if(z3coding.isIn(relatedMemoryUnit,simpleFormulaUnits)){
					result->push_back(simpleFormulaOfForAllFormula);
					break;
				}
			}
			#ifdef _DEBUG
//			cout<<"deq result::"<< toString(result)<<std::endl;
			#endif
			return result;
		}
		vector<expr>* __getQuantifierProperties(vector<expr>* quantifiers,vector<expr>* formulas){
			vector<expr>* result=new vector<expr>();
			for(expr f:*formulas){
				vector<expr>* cons=z3coding.getConsts(f);
				bool isInFlag=true;
				for(expr q:*quantifiers){
					if(!z3coding.isIn(q,cons)){
						isInFlag=false;
						break;
					}
				}
				if(isInFlag){
					result->push_back(f);
				}
			}
			return result;
		}
		vector<expr>* __diff(vector<expr>* A,vector<expr>* B){
			vector<expr>* result=new vector<expr>();
			for(expr a:*A){
				if(!z3coding.isIn(a,B)){
					result->push_back(a);
				}
			}
			return result;
		}
		vector<expr>* __genNewForAllFormula(expr forAllFormula,vector<expr>* newquantifierProperties){
			vector<expr>* result=new vector<expr>();
			vector<expr>* quantifiers=z3coding.getAllQuantifier(forAllFormula);
			vector<expr>* stepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
			vector<expr>* quantifierBeginFormulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
			vector<expr>* quantifierEndFormulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
			for(expr p:*newquantifierProperties){
				expr tmp=p;
				for(int i=quantifiers->size()-1;i>=0;i--){
					tmp=z3coding.constructForAllFormula(quantifiers->at(i),quantifierBeginFormulas->at(i),
						quantifierEndFormulas->at(i),stepFormulas->at(i),tmp);
				}
				result->push_back(tmp);
			}
			return result;
		}
		
		void _generateForallFoumualBySimpleFormula(FlowSet  * simpleFormulain,FlowSet* forAllFormulasIn, 
				const clang::Stmt* stmt,int count,FlowSet * &out){
			vector<expr>* result=new vector<expr>();
			vector<expr>* forAllFormulas=getAllForallFormulas(forAllFormulasIn);
			
			
			for(expr forallFormula:*forAllFormulas){
				vector<expr>* quantifiers=z3coding.getAllQuantifier(forallFormula);
				vector<expr>* deqResult=__forAllFormulaDegeneratedToSimpleFormula(forallFormula,stmt,count);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				FlowSet* tmpSimpleIn=simpleFormulain->clone();
				tmpSimpleIn->Union(toFlowSet(deqResult));
				userSupplied->flowThrouth(stmt,count,tmpSimpleIn,simpleFormulaPos);
				vector<expr>* quantifierProperties=__getQuantifierProperties(quantifiers,toExprs(simpleFormulaPos));
				vector<expr>* newquantifierProperties=__diff(quantifierProperties,deqResult);
				vector<expr>* newforallFormulas=__genNewForAllFormula(forallFormula,newquantifierProperties);
				z3coding.pushAToB(newforallFormulas,result);
			}
			out->Union(toFlowSet(result));
		}
		
		void _generateForallFoumualBySimpleFormula(FlowSet* simpleFormulain,FlowSet* forAllFormulasIn, 
				const clang::Stmt* stmt,int count,FlowSet* &truePos,FlowSet* &falsePos){
					
			vector<expr>* trueresult=new vector<expr>();
			vector<expr>* falseresult=new vector<expr>();
			vector<expr>* forAllFormulas=getAllForallFormulas(forAllFormulasIn);
			
			for(expr forallFormula:*forAllFormulas){
				vector<expr>* quantifiers=z3coding.getAllQuantifier(forallFormula);
				vector<expr>* deqResult=__forAllFormulaDegeneratedToSimpleFormula(forallFormula,stmt,count);
				FlowSet  * simpleTruePos=userSupplied->newinitialFlow();simpleTruePos->clear();
				FlowSet  * simpleFalsePos=userSupplied->newinitialFlow();simpleFalsePos->clear();
				FlowSet* tmpSimpleIn=simpleFormulain->clone();
				tmpSimpleIn->Union(toFlowSet(deqResult));
				userSupplied->flowThrouth(stmt,count,tmpSimpleIn,simpleTruePos,simpleFalsePos);
				vector<expr>* quantifierPropertiesInTruePos=__getQuantifierProperties(quantifiers,toExprs(simpleTruePos));
				vector<expr>* quantifierPropertiesInFalsePos=__getQuantifierProperties(quantifiers,toExprs(simpleFalsePos));
				vector<expr>* newquantifierPropertiesInTruePos=__diff(quantifierPropertiesInTruePos,deqResult);
				vector<expr>* newforallFormulasInTruePos=__genNewForAllFormula(forallFormula,newquantifierPropertiesInTruePos);
				vector<expr>* newquantifierPropertiesInFalsePos=__diff(quantifierPropertiesInFalsePos,deqResult);
				vector<expr>* newforallFormulasInFalsePos=__genNewForAllFormula(forallFormula,newquantifierPropertiesInFalsePos);
				z3coding.pushAToB(newforallFormulasInTruePos,trueresult);
				z3coding.pushAToB(newforallFormulasInFalsePos,falseresult);
			}
			truePos->Union(toFlowSet(trueresult));
			falsePos->Union(toFlowSet(falseresult));
		}
		
		
		/*
		 * Deg(n,a) = {p(e5 [e7]) | e5 [e7] ∈ Opd(n)∧ ∀x1.x1 ∈ [e1,c1 ,e2),∀x2.x2 ∈ [e3,c2,e4)...,p(e5[e6]) ∈ a∧ 
		 * 								e5 [e7] ∈ {e5[e6] | x1∈ [e1,c1,e2) ∧ x2∈ [e3,c2,e4)∧...}}
		 * deg limit
		 *		p: p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)],v1,...,vg)
		 *			量词x1,...,xn只出现在A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]中
		 *		或者f=x，A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]= A1[x1]...[xn]

		 *	1:实例化p(A1[e1]...[et],v1,...,vg)
		 *	2:如果x1=e1 ∧…∧ xn=en可满足 
		 *  实例化p(A1[f1(x1,...,xn)]...[f1m(x1,...,xn)], ...,Ak1[f1(x1,...,xn)] ...[fkh (x1,..., xn)], ff1(x1,...,xn),..., ffg(x1,...,xn))[(x1,…,xn)/(e1,…,en)]
		 */
		FlowSet * forAllFormulaInstantiatedToSimpleFormula(FlowSet * in,const clang::Stmt* stmt){
			vector<expr> * result=new vector<expr>();
			
			/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);*/
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
			
			if(exprs==nullptr||exprs->size()==0){
				return toFlowSet(result);
			}
			vector<expr> *stmtFormulas=new vector<expr>();
			z3coding.pushAToB(exprs,stmtFormulas);
			vector<expr>* forAllFormulas=getAllForallFormulas(in);
			vector<expr> * arrayAcesses=new vector<expr>();
			for(expr e:*stmtFormulas){
				vector<expr> * tmp;
				if(e.is_bool()&&z3coding.isAssignment(e)){
					e=e.arg(0);
					tmp=z3coding.getArrayAcessMemoryUnit(e.arg(1));
				}
				else{
					tmp=z3coding.getArrayAcessMemoryUnit(e);
				}
				add(tmp,arrayAcesses);
			}
//			cout<<"arrayAcesses::"<<toString(arrayAcesses)<<std::endl;
//			cout<<"arrayAcesses_size::"<<arrayAcesses->size()<<std::endl;
//			cout<<"forAllFormulas_size::"<<forAllFormulas->size()<<std::endl;
			for(expr arrayAcessMemoryUnit:*arrayAcesses){
				for(expr forAllFormula:*forAllFormulas){
					FlowSet* env=getEnvironmentBeforStmt(stmt);
//					cout<<"arrayAcessMemoryUnit::"<<arrayAcessMemoryUnit<<std::endl;
					vector<expr>* mustIsInExprs=mustMemoryUnitIsInForAllFormula(env,arrayAcessMemoryUnit,forAllFormula);
					if(mustIsInExprs->size()>0){
						expr simpleFormulaOfForAllFormula=getForallFormulaInnerSimpleFormula(forAllFormula);
						vector<expr>* insFormulas=instantiation(arrayAcessMemoryUnit,mustIsInExprs,forAllFormula);
						add(insFormulas,result);
					}
				}
			}
			
			#ifdef _DEBUG
//			cout<<"deq result::"<< toString(result)<<std::endl;
			#endif
			return toFlowSet(result);
		}
		void add(vector<expr>* &A,vector<expr>* &B){
			for(expr e: *A){
				if(!z3coding.isIn(e,B)){
					B->push_back(e);
				}
			}
		}
		vector<expr>* instantiation(expr arrayAcessMemoryUnit,vector<expr>* quantifierArrayAcesses,expr forAllFormula){
			vector<expr>* result=new vector<expr>();
			/*
			 * * deg limit
			 *	 p: p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)],v1,...,vg)
			 *			量词x1,...,xn只出现在A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]中
			 *		或者f=x，A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]= A1[x1]...[xn]
			 */
			vector<expr>* qualifiers=z3coding.getAllQuantifier(forAllFormula);
			expr simpleFormulaOfForAllFormula=getForallFormulaInnerSimpleFormula(forAllFormula);
			for(expr quantifierArrayAcess:*quantifierArrayAcesses){
				if(isDeqLimit1(qualifiers,simpleFormulaOfForAllFormula)){
					result->push_back(z3coding.substitute(simpleFormulaOfForAllFormula,quantifierArrayAcess,arrayAcessMemoryUnit));
				}
				else if(isDeqLimit2(quantifierArrayAcess)){
					vector<expr>* quantifierArrayAcessIdxes=z3coding.getArrayAcessIdxes(quantifierArrayAcess);
					vector<expr>* arrayAcessIdxes=z3coding.getArrayAcessIdxes(arrayAcessMemoryUnit);
					if(quantifierArrayAcessIdxes->size()!=arrayAcessIdxes->size()){
						cerr<<"LiftAnalysis::occurTime::something is wrong!"<<std::endl;
						return new vector<expr>(); 
					}
					expr insResult=simpleFormulaOfForAllFormula;
					for(unsigned i=0;i<quantifierArrayAcessIdxes->size();i++){
						expr quantifierKIdex=quantifierArrayAcessIdxes->at(i);
						expr arrayAcessKIdex=arrayAcessIdxes->at(i);
						insResult=z3coding.substitute(insResult,quantifierKIdex,arrayAcessKIdex);
					}
					if(!z3coding.isIn(insResult,result)){
						result->push_back(insResult);
					}
				}
			}
			return  result;
		}
		/**
		 * @brief simpleFormula:p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)],v1,...,vg)
		 * 			量词x1,...,xn只出现在A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]中
		 * @param quantifiers
		 * @param simpleFormula:p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)],v1,...,vg)
		 * @return 
		 */
		bool isDeqLimit1(vector<expr> * quantifiers,expr simpleFormula){
			vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(simpleFormula);
			if(arrayAcesses->size()==1){
				for(expr quantifier:*quantifiers){
					if(occurTime(quantifier,simpleFormula)!=occurTime(quantifier,arrayAcesses->at(0))){
						return false;
					}
				}
				return true;
			}
			else{
				return false;
			}
		}
		
		/**
		 * @brief A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]= A1[x1]...[xn], function fi map to simgle variable x
		 * @param quantifiers
		 * @param simpleFormula
		 * @return 
		 */
		bool isDeqLimit2(expr quantifierArrayAcess){
			vector<expr>* idxes=z3coding.getArrayAcessIdxes(quantifierArrayAcess);
			for(expr kIdx:*idxes){
				if(!kIdx.is_const()){
					return false;
				}
			}
			return true;
		}
		/**
		 * @brief if memoryunit must isIn forAllFormula,return which arrayacessexpr memoryunit must isIn
		 * @param env
		 * @param memoryunit: is arrayacessexpr
		 * @param forAllFormula:∀x1.x1 ∈ [e11,c1,e12),... ∀xn.xn ∈ [en1,cn,en2), 
		 * 		p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)], ...,Ak1[f1(x1,...,xn)] ...[fkh (x1,..., xn)], ff1(x1,...,xn),..., ffg(x1,...,xn))
		 * @return  
		 */
vector<expr> * mustMemoryUnitIsInForAllFormula(FlowSet* env,expr memoryunit,expr forAllFormula){
	/*
	 * ∀x1.x1 ∈ [e11,c1,e12),... ∀xn.xn ∈ [en1,cn,en2), 
	 * 	p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)], ...,Ak1[f1(x1,...,xn)] ...[fkh (x1,..., xn)], ff1(x1,...,xn),..., ffg(x1,...,xn))
	 * 
	 * 
	 * env ∧t=m ∧ e1=f1(x1,...,xn) ∧… ∧ em=f1m(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2) 
	 * ∨… ∨
	 * env ∧t=h ∧ e1=fk1(x1,...,xn) ∧… ∧ eh=fkm(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2)
	 */ 
	vector<expr> * result=new vector<expr>();
	expr memoryunitbase=z3coding.getArrayBase(memoryunit);
	unsigned  memoryunitDim=z3coding.getArrayAcessDimension(memoryunit);
	vector<expr> * allquantifiers=z3coding.getAllQuantifier(forAllFormula);
	vector<expr> * allstepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
	vector<expr> * allbeginformulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
	vector<expr> * allendformulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
	vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(forAllFormula);
	for(expr arrayAcess:*arrayAcesses){
		expr arrayAcessBase=z3coding.getArrayBase(arrayAcess);
		if(mayMemoryUnitIsIn(env,memoryunitbase,arrayAcessBase)){
		/*env ∧t=m ∧ e1=f1(x1,...,xn) ∧… ∧ em=f1m(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2) 
		*∨… ∨
		* env ∧t=h ∧ e1=fk1(x1,...,xn) ∧… ∧ eh=fkm(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2)
		*/ 
			unsigned arrayAcessDim=z3coding.getArrayAcessDimension(arrayAcess);
			if(arrayAcessDim!=memoryunitDim){return new vector<expr>();}
			vector<expr> * Pres=new vector<expr>();
			vector<expr> * memoryunitIdxes=z3coding.getArrayAcessIdxes(memoryunit);
			vector<expr> * arrayAcessIdxes=z3coding.getArrayAcessIdxes(arrayAcess);
			for(unsigned i=0;i<arrayAcessDim;i++){
				Pres->push_back(memoryunitIdxes->at(i)==arrayAcessIdxes->at(i));
			}
			expr quantifierFormulaAssert=c.bool_val(true);
			for(unsigned i=0;i<allquantifiers->size();i++){
				expr quantifier=allquantifiers->at(i);
				expr beginformula=allbeginformulas->at(i);
				expr begin=beginformula.arg(0);
				expr endformula=allendformulas->at(i);
				expr stepFormula=allstepFormulas->at(i);
				
				//beginformula&&endformula&&quantifier%step=0
				expr qi=beginformula&&endformula&&stepFormula;
				quantifierFormulaAssert=quantifierFormulaAssert&&qi;
			}
			vector<expr> * expr_env=toExprs(env);
			z3coding.pushAToB(expr_env,Pres);
//			cout<<"Pres::"<<toString(Pres)<<std::endl;
//			cout<<"quantifierFormulaAssert::"<<quantifierFormulaAssert<<std::endl;
			if(z3coding.satisfy(Pres,c.bool_val(true))==check_result::sat&&proved_result::proved==z3coding.prove(Pres,quantifierFormulaAssert)){
				result->push_back(arrayAcess); 
			}
		}
	}
	return result;
}
		expr getForallFormulaInnerSimpleFormula(expr forAllFormula){
			expr tmp=forAllFormula;
			while(z3coding.isForAllFormula(tmp)){
				tmp=z3coding.getQuantifierFormulaBody(tmp);
			}
			return tmp;
		}
		
		unsigned occurTime(expr con,expr e){
			if(e.is_const()){
				if(z3coding.equal(con,e)){
					return 1;
				}
				return 0;
			}
			else if(e.is_var()){
				return 0;
			}
			else if(e.is_app()){
				unsigned count=0;
				for(unsigned i=0;i<e.num_args();i++){
					count+=occurTime(con,e.arg(i));
				}
				return count;
			}
			else{
				cerr<<"LiftAnalysis::occurTime::something is wrong!"<<std::endl;
				return 0;
			}
			
		}
		
		FlowSet* getEnvironmentBeforStmt(const clang::Stmt *clangStmt){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* in=envAnalysis->mapToStmtIn.at(clangStmt);
			return in;
		}
		FlowSet* transfer(FlowSet  *Pre,expr stmt,FlowSet  *in){
			FlowSet* result=userSupplied->newinitialFlow();result->clear();
			vector<Property *>* invec=in->toVector();
			if(z3coding.isAssignment(stmt)){
				stmt=stmt.arg(0);
				expr left=stmt.arg(0);
				for(Property *p:*invec){
					Formula *f=(Formula *)p;
					if(!mayMemoryUnitIsInFormula(Pre,z3coding.unprimedDecline(left),f->formula)){
						result->add(new Formula(f->formula));
					}
				}
			}
			else{
				result->Union(in);
			}
			return result;
		}

		FlowSet* transferWithEnvironment(const clang::Stmt *clangStmt,expr stmt,FlowSet  *in){
			return transfer(getEnvironmentBeforStmt(clangStmt),stmt,in);
		}

		Property* genPhi(const clang::Stmt* clangStmt,expr initStmt){
			expr index=z3coding.unprimedDecline(initStmt.arg(0));
			expr init=initStmt.arg(1);
			expr step=getStepFromIndex(clangStmt,index);
			expr phi=constructPhiFormula(index,init,step);
			if(!z3coding.checkError(phi)){
				return new Formula(phi);
			}
			return nullptr;
		}
		Property* genPhi(FlowSet* indexEnv,expr initStmt){
			expr index=z3coding.unprimedDecline(initStmt.arg(0));
			expr init=initStmt.arg(1);
			expr step=getStepFromIndex(indexEnv,index);
			expr phi=constructPhiFormula(index,init,step);
			if(!z3coding.checkError(phi)){
				return new Formula(phi);
			}
			return nullptr;
		}
		FlowSet  * handleInterval(expr updateStmt,FlowSet * in){
			FlowSet * result=userSupplied->newinitialFlow();result->clear();
			expr left=updateStmt.arg(0);
			expr index=z3coding.unprimedDecline(left);
			vector<Property*>* invec=in->toVector();
			for(Property* p:*invec){
				Formula *f=(Formula*)p;
				if(z3coding.isForAllFormula(f->formula)){
					expr quantifier=z3coding.getQuantifier(f->formula);
					expr step=z3coding.getForAllFormulaStep(f->formula);
					expr stepFormula=z3coding.getForAllFormulaStepFormula(f->formula);
					expr quantifierBegin=z3coding.getForAllFormulaBegin(f->formula);
					expr quantifierEnd=z3coding.getForAllFormulaEnd(f->formula);
					expr quantifierBeginFormula=z3coding.getForAllFormulaBeginFormula(f->formula);
					expr quantifierEndFormula=z3coding.getForAllFormulaEndFormula(f->formula);
					expr quantifierExtendFormula=z3coding.getForAllFormulaExtendFormula(f->formula);
					expr body=z3coding.getQuantifierFormulaBody(f->formula);
					if(mu.isGtZero(step)){//>
						if(z3coding.equal(index+step,quantifierEnd)&&!mu.mayMemoryUnitIsInFormula(index,body)){
//							cout<<"handle interval before::"<<f->formula<<std::endl;
//							cout<<"quantifier::"<<quantifier<<std::endl;
//							cout<<"quantifierBeginFormula::"<<quantifierBeginFormula<<std::endl;
//							cout<<"body::"<<body<<std::endl;
							Formula* tmp=new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,quantifier<index,
											stepFormula,body));
//							cout<<"handle interval after"<<tmp->formula<<std::endl;
							result->add(tmp);
						}
						else if(z3coding.equal(index,quantifierEnd)&&!mu.mayMemoryUnitIsInFormula(index,body)){
							result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,
											quantifier<index-step,stepFormula,body)));
						}
					}
					else if(mu.isLtZero(step)){//<
						//cout<<"f->formula: "<<f->formula<<std::endl;
						//cout<<"index+step "<<index+step<<std::endl;
						//cout<<"quantifierBegin: "<<quantifierBegin<<std::endl;
						if(z3coding.equal(index+step,quantifierBegin)&&!mu.mayMemoryUnitIsInFormula(index,body)){
							result->add(new Formula(z3coding.constructForAllFormula(quantifier,index<quantifier,quantifierEndFormula,
											stepFormula,body)));
						}
						else if(z3coding.equal(index,quantifierBegin)&&!mu.mayMemoryUnitIsInFormula(index,body)){
							result->add(new Formula(z3coding.constructForAllFormula(quantifier,index-step<quantifier,quantifierEndFormula,
											stepFormula,body)));
						}
					}
				}
				else if(z3coding.isPhiFormula(f->formula)){
					expr quantifier=z3coding.getPhiQuantifier(f->formula);
					expr phiBegin=z3coding.getPhiBegin(f->formula);
					expr phiEnd=z3coding.getPhiEnd(f->formula);
					expr phiBeginFormula=z3coding.getPhiBeginFormula(f->formula);
					expr phiEndFormula=z3coding.getPhiEndFormula(f->formula);
					expr step=z3coding.getPhiStep(f->formula);
					expr stepFormula=z3coding.getPhiStepFormula(f->formula);
					if(mu.isGtZero(step)){//>
						if(z3coding.equal(index+step,phiEnd)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,quantifier<index,stepFormula)));
						}
						else if(z3coding.equal(index,phiEnd)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,quantifier<index-step,stepFormula)));
						}
					}
					else if(mu.isLtZero(step)){//<
						if(z3coding.equal(index+step,phiBegin)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,index<quantifier,phiEndFormula,stepFormula)));
						}
						else if(z3coding.equal(index,phiBegin)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,index-step<quantifier,phiEndFormula,stepFormula)));
						}
					}
				}
			}
			return result;
		}

		FlowSet * genQ(FlowSet* indexEnv,FlowSet* env,FlowSet  * in){
			FlowSet * result=userSupplied->newinitialFlow();result->clear();
			result->Union(genFQ(indexEnv,env,in));
			return result;
		}
		/*	
		 *  S ∪ {∀x.x ∈ [e1,c,e2),p 		if (3) or (4) holds
		 S ∪ {∀x.x ∈ [initi,c,i + c),ψ(e1[f1(x)])} 	if (5) or (6) holds
		 S ∪ {∀x.x ∈ [initi,c,i),ψ(e1[f1(x)])} 		if (7) or (8) holds
		 S 				otherwise


		 c > 0 ∧ (e4 < e1 ∨ e4 ≤ e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),p ∈ a 	(3)
		 c > 0 ∧ (e2 < e5 ∨ e2 ≤ e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),p ∈ a 	(4)
		 Note that, there are other conditions to generate universal quantifier properties. Thus, we just list some conditions here. Other conditions are similar to (3) and (4).
		 ∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(e1[f1(i)]) ∈ a 		(5)
		 ∀x.x ∈ [initi,c,i),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i)]) ∈ a 	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)])∏p ψ2(e1[f1(x)]) 		(6)
		 ∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(e1[f1(i − c)]) ∈ a	(7)
		 ∀x.x ∈ [initi,c,i − c),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i − c)]) ∈ a	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)]) ∏p ψ2(e1[f1(x)]) 		(8)

*/
FlowSet  * genFQ(FlowSet* indexEnv,FlowSet* env,FlowSet  * in){
	FlowSet* result=in->clone();
	result->Union(closureForAllWithEnvironment(env,result));
	result->Union(closurePhiWithEnvironment(env,result));
	result->Union(update(indexEnv,result));
	result->Union(updateDef(indexEnv,result));
	return result;
}
/*FlowSet * closureQ(FlowSet* env,FlowSet  * in){
	FlowSet * result=userSupplied->newinitialFlow();result->clear();
	result->Union(closureFQ(env,in));
	return result;
}
FlowSet  * closureFQ(FlowSet* env,FlowSet  * in){
	FlowSet* result=in->clone();
	result->Union(closureForAllWithEnvironment(env,result));
	result->Union(closurePhiWithEnvironment(env,result));
	return result;
}*/
FlowSet* closureForAllWithEnvironment(FlowSet* env,FlowSet* in){
	FlowSet* result=userSupplied->newinitialFlow();result->clear();
	vector<expr>* forallFormulas=getAllForallFormulas(in);
	for(expr forAllFormula:*forallFormulas){
		expr quantifier=z3coding.getQuantifier(forAllFormula);
		expr step=z3coding.getForAllFormulaStep(forAllFormula);
		expr stepFormula=z3coding.getForAllFormulaStepFormula(forAllFormula);
		expr quantifierBegin=z3coding.getForAllFormulaBegin(forAllFormula);
		expr quantifierEnd=z3coding.getForAllFormulaEnd(forAllFormula);
		expr quantifierBeginFormula=z3coding.getForAllFormulaBeginFormula(forAllFormula);
		expr quantifierEndFormula=z3coding.getForAllFormulaEndFormula(forAllFormula);
		expr quantifierExtendFormula=z3coding.getForAllFormulaExtendFormula(forAllFormula);
		expr body=z3coding.getQuantifierFormulaBody(forAllFormula);
		vector<Property*>* envVec=env->toVector();
		for(Property* envp:*envVec){
			expr envf=((Formula*)envp)->formula;
			if(envf.is_app()){
				if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)
				||Z3_is_eq_func_decl(c,envf.decl(),z3coding.LeDecl)){
					//c > 0 ∧ (e4 < e1 ∨ e4 ≤ e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),p ∈ a 	(3)
					//c > 0 ∧ (e2 < e5 ∨ e2 ≤ e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),p ∈ a 	(4)
					expr left=envf.arg(0);
					expr right=envf.arg(1);
					if(z3coding.equal(left,quantifierBegin)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(right,quantifierEnd)
								&&LEclosureFQTactics3(toExprs(env),right,quantifierEnd)
								&&LEQclosureFQTactics4(left,right)
								&&LEQclosureFQTactics5(left,right)){
						expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,left,right);
						result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,body)));
					}
					if(z3coding.equal(right,quantifierEnd)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(quantifierBegin,left)
								&&LEclosureFQTactics3(toExprs(env),quantifierBegin,left)
								&&LEQclosureFQTactics4(right,left)
								&&LEQclosureFQTactics5(right,left)){
						expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,right,left);
						result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,body)));
					}
				}
				if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.EqDecl)){
					//c > 0 ∧ (e4 = e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),p ∈ a 	(3)
					//c > 0 ∧ (e2 = e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),p ∈ a 	(4)
					expr left=envf.arg(0);
					expr right=envf.arg(1);

					if(z3coding.equal(left,quantifierBegin)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(right,quantifierEnd)
							&&LEQclosureFQTactics4(left,right)
							&&LEQclosureFQTactics5(left,right)){
						expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,left,right);
						result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,body)));
					}
					if(z3coding.equal(right,quantifierBegin)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(left,quantifierEnd)
							&&LEQclosureFQTactics4(right,left)
							&&LEQclosureFQTactics5(right,left)){
						expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,right,left);
						result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,body)));
					}
					if(z3coding.equal(left,quantifierEnd)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(quantifierBegin,right)
							&&LEQclosureFQTactics4(left,right)
							&&LEQclosureFQTactics5(left,right)){
						expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,left,right);
						result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,body)));
					}
					if(z3coding.equal(right,quantifierEnd)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(quantifierBegin,left)
							&&LEQclosureFQTactics4(right,left)
							&&LEQclosureFQTactics5(right,left)){
						expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,right,left);
						result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,body)));
					}
				}
			}
		}

	}
	return result;
}

bool LEQclosureFQTactics1(expr from,expr to){
	if(from.is_numeral()){
		return false;
	}
	return true;
}



bool LEQclosureFQTactics2(expr newbegin,expr newend){
	if(z3coding.equal(newbegin,newend)){
		return false;
	}
	return true;
}

bool LEclosureFQTactics3(vector<expr>* Pre, expr newbegin, expr newend){
	if(z3coding.isIn(newbegin>newend,Pre)||z3coding.isIn(newbegin>=newend,Pre)||
		z3coding.isIn(newend<newbegin,Pre)||z3coding.isIn(newend<=newbegin,Pre)){
		return false;
	}
	return true;
}

bool LEQclosureFQTactics4(expr from,expr to){
	if(to.is_app()&&Z3_is_eq_func_decl(c,to.decl(),z3coding.ModDecl)){
		return false;
	}
	return true;
}

bool LEQclosureFQTactics5(expr from,expr to){
	if(to.is_app()&&to.decl().name().str()=="select"){
		return false;
	}
	return true;
}
FlowSet* eliminateUnpossibleForAllOrPhiFormulas(FlowSet* env,FlowSet* in){
	FlowSet* out=userSupplied->newinitialFlow();out->clear();
	vector<expr>* inExprs=toExprs(in);
	vector<expr>* envExprs=toExprs(env);
	for(expr e:*inExprs){
		if(z3coding.isForAllFormula(e)||z3coding.isPhiFormula(e)){
			expr begin(c);
			expr end(c);
			if(z3coding.isForAllFormula(e)){
				begin=z3coding.getForAllFormulaBegin(e);
				end=z3coding.getForAllFormulaEnd(e);
			}
			if(z3coding.isPhiFormula(e)){
				begin=z3coding.getPhiBegin(e);
				end=z3coding.getPhiEnd(e);
			}
			
			if(z3coding.isIn(begin>end,envExprs)||z3coding.isIn(begin>=end,envExprs)||
				z3coding.isIn(end<begin,envExprs)||z3coding.isIn(end<=begin,envExprs)){
				continue;
			}
//			if(z3coding.prove(envExprs,end<begin)==proved_result::proved){
//				continue;
//			}
			if(isScaleVariable(begin)&&isScaleVariableOpStep(end)){
				continue;
			}
			if(isScaleVariable(end)&&isScaleVariableOpStep(begin)){
				continue;
			}
			
		}
		out->add(new Formula(e));
	}
	return out;
}
bool isScaleVariable(expr e){
	for(AtomVariabla* av:*indexVariables){
		if(z3coding.equal(av->scalaVarz3coding,e)){
			return true;
		}
	}
	return false;
}
bool isScaleVariableOpStep(expr e){
	for(AtomVariabla* av:*indexVariables){
		if(z3coding.equal(av->scalaVarz3coding+av->stepz3coding,e)){
			return true;
		}
		if(z3coding.equal(av->scalaVarz3coding-av->stepz3coding,e)){
			return true;
		}
	}
	return false;
}

/**
 * @brief gen more phi according to Environment
   e.g. (3)||(4) => {∀x.x ∈ [e1,c,e2),p 
 * c > 0 ∧ (e4 < e1 ∨ e4 ≤ e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),false ∈ a 	(3)
   c > 0 ∧ (e2 < e5 ∨ e2 ≤ e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),false ∈ a 	(4)
 * @param env
 * @param in
 * @return 
 */
FlowSet* closurePhiWithEnvironment(FlowSet* env,FlowSet* in){
	vector<expr>* phiFormulas=getAllPhiFormulas(in);
	FlowSet* result=userSupplied->newinitialFlow();result->clear();
	//cout<<"------------Environment-----------"<<std::endl;
	//cout<<toString(env)<<std::endl;
	//cout<<"------------phiFormulas-----------"<<std::endl;
	//cout<<toString(phiFormulas)<<std::endl;
	for(expr phiFormula:*phiFormulas){
		expr quantifier=z3coding.getPhiQuantifier(phiFormula);
		expr phiBegin=z3coding.getPhiBegin(phiFormula);
		expr phiEnd=z3coding.getPhiEnd(phiFormula);
		expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
		expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
		expr step=z3coding.getPhiStep(phiFormula);
		expr stepFormula=z3coding.getPhiStepFormula(phiFormula);
		vector<Property*>* envVec=env->toVector();
		for(Property* envp:*envVec){
			expr envf=((Formula*)envp)->formula;
			if(envf.is_app()){
				//if(mu.isGtZero(e)){
					
					if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(c,envf.decl(),z3coding.LeDecl)){
						//c > 0 ∧ (e4 < e1 ∨ e4 ≤ e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),false ∈ a 	
						//c > 0 ∧ (e2 < e5 ∨ e2 ≤ e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),false ∈ a 	
						expr left=envf.arg(0);
						expr right=envf.arg(1);
						if(z3coding.equal(left,phiBegin)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(right,phiEnd)
						&&LEclosureFQTactics3(toExprs(env),right,phiEnd)
						&&LEQclosureFQTactics4(left,right)
						&&LEQclosureFQTactics5(left,right)){
							//cout<<"phiFormula: "<<phiFormula<<", envf: "<<envf<<std::endl;
							expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,left,right);
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,newphiBeginFormula,phiEndFormula,stepFormula)));
						}
						if(z3coding.equal(right,phiEnd)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(phiBegin,left)&&LEclosureFQTactics3(toExprs(env),phiBegin,left)
						&&LEQclosureFQTactics4(right,left)
						&&LEQclosureFQTactics5(right,left)){
							//cout<<"phiFormula: "<<phiFormula<<", envf: "<<envf<<std::endl;
							expr newphiEndFormula=z3coding.substitute(phiEndFormula,right,left);
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,newphiEndFormula,stepFormula)));
						}
					}
					if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.EqDecl)){
						//c > 0 ∧ (e4 = e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),false ∈ a 	
						//c > 0 ∧ (e2 = e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),false ∈ a 	
						expr left=envf.arg(0);
						expr right=envf.arg(1);

						if(z3coding.equal(left,phiBegin)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(right,phiEnd)
						&&LEQclosureFQTactics4(left,right)
						&&LEQclosureFQTactics5(left,right)){
							expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,left,right);
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,newphiBeginFormula,phiEndFormula,stepFormula)));
						}
						if(z3coding.equal(right,phiBegin)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(left,phiEnd)
						&&LEQclosureFQTactics4(right,left)
						&&LEQclosureFQTactics5(right,left)){
							expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,right,left);
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,newphiBeginFormula,phiEndFormula,stepFormula)));
						}
						if(z3coding.equal(left,phiEnd)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(phiBegin,right)
						&&LEQclosureFQTactics4(left,right)
						&&LEQclosureFQTactics5(left,right)){
							expr newphiEndFormula=z3coding.substitute(phiEndFormula,left,right);
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,newphiEndFormula,stepFormula)));
						}
						if(z3coding.equal(right,phiEnd)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(phiBegin,left)
						&&LEQclosureFQTactics4(right,left)
						&&LEQclosureFQTactics5(right,left)){
							expr newphiEndFormula=z3coding.substitute(phiEndFormula,right,left);
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,newphiEndFormula,stepFormula)));
						}
					}
				//}
			}
		}
	}
	return result;
}
FlowSet* update(FlowSet* indexEnv,FlowSet* in){
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	/*
	 *	S ∪ {∀x.x ∈ [initi,c,i + c),ψ(e1[f1(x)])} 	if (5) or (6) holds
	 S ∪ {∀x.x ∈ [initi,c,i),ψ(e1[f1(x)])} 		if (7) or (8) holds 

	 ∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(e1[f1(i)]) ∈ a 		(5)
	 ∀x.x ∈ [initi,c,i),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i)]) ∈ a	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)])∏p ψ2(e1[f1(x)]) 		(6)
	 ∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(e1[f1(i − c)]) ∈ a	(7)
	 ∀x.x ∈ [initi,c,i − c),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i − c)]) ∈ a	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)]) ∏p ψ2(e1[f1(x)]) 		(8)
	 */

	//∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(e1[f1(i)]) ∈ a 		(5)
	//∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(e1[f1(i − c)]) ∈ a	(7)
	
	
	result->Union(updatePhi(indexEnv,in));
	//∀x.x ∈ [initi,c,i),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i)]) ∈ a 	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)])∏p ψ2(e1[f1(x)]) 				(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i − c)]) ∈ a	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)]) ∏p ψ2(e1[f1(x)]) 		(8)
	result->Union(updateForAll(indexEnv,in));
	return result;

}



vector<expr>* getPropertiesRelevantDefWithIndex(expr index,FlowSet* in){
	vector<expr>* result=new vector<expr>();
	vector<Property*>* invec=in->toVector();
	for(Property* p:*invec){
		Formula* f=(Formula*)p;
		//cout<<"p is :" <<f->formula <<std::endl;
		vector<expr> * defAcesses=z3coding.getDefAcessMemoryUnit(f->formula);
		for(expr defAcess:*defAcesses){
			if(z3coding.isIn(index,z3coding.getConsts(defAcess))){
				result->push_back(f->formula);
			}
		}
	}
	return result;
}
FlowSet* updateDef(FlowSet* indexEnv,FlowSet* in){
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	/*
	 *	∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(def(f1(i))) ∈ a 					(5)
		∀x.x ∈ [initi,c,i),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x)))∏p ψ2(def(f1(x))) 		(6)
		∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(def(f1(i − c))) ∈ a			(7)
		∀x.x ∈ [initi,c,i − c),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i − c))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x))) ∏p ψ2(def(f1(x))) 	(8)
	 */

	//∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(def(f1(i))) ∈ a 					(5)
	//∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(def(f1(i − c))) ∈ a			(7)
	
	
	result->Union(generalizeUpdatePhi(indexEnv,in,&LiftAnalysis::getPropertiesRelevantDefWithIndex));
	//∀x.x ∈ [initi,c,i),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x)))∏p ψ2(def(f1(x))) 		(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i − c))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x))) ∏p ψ2(def(f1(x))) 	(8)
	result->Union(generalizeUpdateForAll(indexEnv,in));
	return result;

}
/*expr ffff(){

  std::string func_name="def_pointer";
  z3::func_decl def=c.function(func_name.c_str(),c.int_sort(),c.int_sort());
  expr dest=c.int_const("dest");
  expr destpre=c.int_const("dest@pre");
  expr src=c.int_const("src");
  expr srcpre=c.int_const("src@pre");
  expr eeq=def(dest-1)==def((dest-destpre)/1+0+srcpre-1);
  return eeq;
}*/
FlowSet  *generalizeUpdatePhi(FlowSet* indexEnv,FlowSet  * in,vector<expr>* (LiftAnalysis::*pfun_GetPropertiesRelevantWithIndex)(expr, FlowSet*)){
	//∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(def(f1(i))) ∈ a 					(5)
	//∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(def(f1(i − c))) ∈ a			(7)
	#ifdef _DEBUG
	//cout<<"updateDefPhi::in::"<<toString(in)<<std::endl;
	#endif
	
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	vector<expr>* phiFormulas=getAllPhiFormulas(in);
	for(expr phiFormula:*phiFormulas){
		//cout<<"phiFormula:: "<<phiFormula<<std::endl;
		expr quantifier=z3coding.getPhiQuantifier(phiFormula);
		expr phiBegin=z3coding.getPhiBegin(phiFormula);
		expr phiEnd=z3coding.getPhiEnd(phiFormula);
		expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
		expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
		expr step=z3coding.getPhiStep(phiFormula);
		expr stepFormula=z3coding.getPhiStepFormula(phiFormula);
		if(checkAtomicScalar(indexEnv,phiBegin,step,phiEnd)){
			expr index(c);
			if(mu.isGtZero(step)){
				index=phiEnd;
			}
			else if(mu.isLtZero(step)){
				index=phiBegin;
			}
//			cout<<"index is: "<<index<<std::endl;
//			cout<<"in is: "<<toString(in)<<std::endl;
			vector<expr>* relevantProperties=(this->*pfun_GetPropertiesRelevantWithIndex)(index,in);
			for(expr property:*relevantProperties){
				//cout<<"property:: "<<property<<std::endl;
				if(z3coding.isPhiFormula(property)) continue;
				if(mu.isGtZero(step)){
					expr newphiEndFormula=z3coding.substitute(phiEndFormula,index,index+step);
					
					vector<expr> * cons=z3coding.getConstsWithQuantifier(property);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(phiBeginFormula.arg(0));
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(newphiEndFormula.arg(1));
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(step);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					expr newquantifier=constructNewQuantifierName(cons);
					//cout<<"property is: "<<property<<std::endl;
					expr newbody=z3coding.substitute(property,index,newquantifier);
					//cout<<"newbody is: "<<newbody<<std::endl;
					expr newQuantifierBeginFormula=phiBeginFormula;
					expr newQuantifierEndFormula=newphiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(phiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(newphiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					
					Formula* ttt=new Formula(z3coding.constructForAllFormula
					(newquantifier,newQuantifierBeginFormula,newQuantifierEndFormula,newQuantifierstepFormula,newbody));
					//cout<<phiFormula <<" --and--- "<<property<<"---genL10--- "<<ttt->formula<<std::endl;
					result->add(ttt);
				}
				else if(mu.isLtZero(step)){
					expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,index,index+step);
					
					vector<expr> * cons=z3coding.getConstsWithQuantifier(property);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula.arg(0));
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(phiEndFormula.arg(1));
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(step);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					
					expr newquantifier=constructNewQuantifierName(cons);
					//cout<<"property is: "<<property<<std::endl;	
					expr newbody=z3coding.substitute(property,index,newquantifier);
					//cout<<"newbody is: "<<newbody<<std::endl;
					expr newQuantifierBeginFormula=newphiBeginFormula;
					expr newQuantifierEndFormula=phiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(newphiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(phiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					Formula * ttt=new Formula(z3coding.constructForAllFormula(newquantifier,newQuantifierBeginFormula,
					newQuantifierEndFormula,newQuantifierstepFormula,newbody));
					//cout<<z3coding.toString(phiFormula) <<" and "<<z3coding.toString(property)<<" genL11: "<<z3coding.toString(ttt->formula)<<std::endl;
					result->add(ttt);
				}
			}
		}
		if(checkAtomicScalarSubStep(indexEnv,phiBegin,step,phiEnd)){
			expr index(c);
			if(mu.isGtZero(step)){
				index=phiEnd.arg(0);
			}
			else if(mu.isLtZero(step)){
				index=phiBegin.arg(0);
			}
			vector<expr>* relevantProperties=(this->*pfun_GetPropertiesRelevantWithIndex)(index,in);
			for(expr property:*relevantProperties){
				if(z3coding.isPhiFormula( property)) continue;
				if(mu.isGtZero(step)){
					expr newphiEndFormula=z3coding.substitute(phiEndFormula,phiEnd,index);
					vector<expr> * cons=z3coding.getConstsWithQuantifier(property);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(phiBeginFormula);
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(newphiEndFormula);
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(stepFormula);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					expr newquantifier=constructNewQuantifierName(cons);
					//cout<<"property is11: "<<property<<std::endl;
//					if(z3coding.equal(property,ffff())){
//						cout<<phiEnd<<std::endl;
//					}
					expr newbody=z3coding.substitute(property,phiEnd,newquantifier);
					if(z3coding.isIn(index,z3coding.getConsts(newbody))){
						newbody=z3coding.substitute(property,index,newquantifier+step);
					}
					//cout<<"newbody is11: "<<newbody<<std::endl;
					expr newQuantifierBeginFormula=phiBeginFormula;
					expr newQuantifierEndFormula=newphiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(phiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(newphiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					
					if(!z3coding.equal(newbody,property)){
						Formula* ttt=new Formula(z3coding.constructForAllFormula(newquantifier,newQuantifierBeginFormula,
						newQuantifierEndFormula,newQuantifierstepFormula,newbody));
						//cout<<z3coding.toString(phiFormula) <<" and "<<z3coding.toString(property)<<" genL12: "<<z3coding.toString(ttt->formula)<<std::endl;
						result->add(ttt);
					}
				}
				else if(mu.isLtZero(step)){
					expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,phiBegin,index);
					
					vector<expr> * cons=z3coding.getConstsWithQuantifier(property);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula);
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(phiEndFormula);
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(stepFormula);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					
					expr newquantifier=constructNewQuantifierName(cons);
					//cout<<"property is: "<<property<<std::endl;
					expr newbody=z3coding.substitute(property,phiBegin,newquantifier);
					if(z3coding.isIn(index,z3coding.getConsts(newbody))){
						newbody=z3coding.substitute(property,index,newquantifier+step);
					}
					//cout<<"newbody is: "<<newbody<<std::endl;
					expr newQuantifierBeginFormula=newphiBeginFormula;
					expr newQuantifierEndFormula=phiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(newphiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(phiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					
					if(!z3coding.equal(newbody,property)){
						Formula * ttt=new Formula(z3coding.constructForAllFormula(newquantifier,newQuantifierBeginFormula,
						newQuantifierEndFormula,newQuantifierstepFormula,newbody));
						//cout<<z3coding.toString(phiFormula) <<" and "<<z3coding.toString(property)<<" genL13: "<<z3coding.toString(ttt->formula)<<std::endl;
						result->add(ttt);
					}
				}
			}
		}
	}
	#ifdef _DEBUG
	//cout<<"updatePhi::out::"<<toString(result)<<std::endl;
	#endif
	return result;
}
FlowSet  *generalizeUpdateForAll(FlowSet* indexEnv,FlowSet  * in){
	//∀x.x ∈ [initi,c,i),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x)))∏p ψ2(def(f1(x))) 		(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i − c))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x))) ∏p ψ2(def(f1(x))) 	(8)
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	vector<expr>* forallFormulas=getAllForallFormulas(in);
	for(expr forAllFormula:*forallFormulas){
		expr quantifier=z3coding.getQuantifier(forAllFormula);
		expr step=z3coding.getForAllFormulaStep(forAllFormula);
		expr stepFormula=z3coding.getForAllFormulaStepFormula(forAllFormula);
		expr quantifierBegin=z3coding.getForAllFormulaBegin(forAllFormula);
		expr quantifierEnd=z3coding.getForAllFormulaEnd(forAllFormula);
		expr quantifierBeginFormula=z3coding.getForAllFormulaBeginFormula(forAllFormula);
		expr quantifierEndFormula=z3coding.getForAllFormulaEndFormula(forAllFormula);
		expr quantifierExtendFormula=z3coding.getForAllFormulaExtendFormula(forAllFormula);
		expr body=z3coding.getQuantifierFormulaBody(forAllFormula);
		if(checkAtomicScalar(indexEnv,quantifierBegin,step,quantifierEnd)){
			if(mu.isGtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierEnd);
				expr bodyresult=merge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd+step);
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
			else if(mu.isLtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
				expr bodyresult=merge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,quantifierEnd,quantifierEnd+step);
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
		}
		if(checkAtomicScalarSubStep(indexEnv,quantifierBegin,step,quantifierEnd)){
			if(mu.isGtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierEnd);
				expr bodyresult=merge_moreEqual(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd.arg(0));
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					if(z3coding.isIn(quantifierEnd.arg(0),z3coding.getConsts(newbodyresult))){
						newbodyresult=z3coding.substitute(bodyresult,quantifierEnd.arg(0),quantifier+step);
					}
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
			else if(mu.isLtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
				expr bodyresult=merge_moreEqual(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,quantifierBegin,quantifierBegin.arg(0));
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierBegin,quantifier);
					if(z3coding.isIn(quantifierBegin.arg(0),z3coding.getConsts(newbodyresult))){
						newbodyresult=z3coding.substitute(bodyresult,quantifierBegin.arg(0),quantifier+step);
					}
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
		}
	}
	return result;
}


FlowSet  *updatePhi(FlowSet* indexEnv,FlowSet  * in){
	//∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(e1[f1(i)]) ∈ a 			(5)
	//∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(e1[f1(i − c)]) ∈ a	(7)
	#ifdef _DEBUG
	//cout<<"updatePhi::in::"<<toString(in)<<std::endl;
	#endif
	
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	vector<expr>* phiFormulas=getAllPhiFormulas(in);
	for(expr phiFormula:*phiFormulas){
		expr quantifier=z3coding.getPhiQuantifier(phiFormula);
		expr phiBegin=z3coding.getPhiBegin(phiFormula);
		expr phiEnd=z3coding.getPhiEnd(phiFormula);
		expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
		expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
		expr step=z3coding.getPhiStep(phiFormula);
		expr stepFormula=z3coding.getPhiStepFormula(phiFormula);
		if(checkAtomicScalar(indexEnv,phiBegin,step,phiEnd)){
			expr index(c);
			if(mu.isGtZero(step)){
				index=phiEnd;
			}
			else if(mu.isLtZero(step)){
				index=phiBegin;
			}
			vector<expr>* relevantArrayAcessProperties=getPropertiesRelevantArrayAcessWithIndex(index,in);
			for(expr arrayAcessProperty:*relevantArrayAcessProperties){
				if(z3coding.isPhiFormula( arrayAcessProperty)) continue;
				if(mu.isGtZero(step)){
					expr newphiEndFormula=z3coding.substitute(phiEndFormula,index,index+step);
					
					vector<expr> * cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(phiBeginFormula.arg(0));
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(newphiEndFormula.arg(1));
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(step);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					expr newquantifier=constructNewQuantifierName(cons);
					expr newbody=z3coding.substitute(arrayAcessProperty,index,newquantifier);
					expr newQuantifierBeginFormula=phiBeginFormula;
					expr newQuantifierEndFormula=newphiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(phiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(newphiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					
					Formula* ttt=new Formula(z3coding.constructForAllFormula
					(newquantifier,newQuantifierBeginFormula,newQuantifierEndFormula,newQuantifierstepFormula,newbody));
					//cout<<phiFormula <<" --and--- "<<arrayAcessProperty<<"---genL--- "<<ttt->formula<<std::endl;
					result->add(ttt);
				}
				else if(mu.isLtZero(step)){
					expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,index,index+step);
					
					vector<expr> * cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula.arg(0));
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(phiEndFormula.arg(1));
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(step);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					
					expr newquantifier=constructNewQuantifierName(cons);
					expr newbody=z3coding.substitute(arrayAcessProperty,index,newquantifier);
					
					expr newQuantifierBeginFormula=newphiBeginFormula;
					expr newQuantifierEndFormula=phiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(newphiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(phiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					Formula * ttt=new Formula(z3coding.constructForAllFormula(newquantifier,newQuantifierBeginFormula,
					newQuantifierEndFormula,newQuantifierstepFormula,newbody));
					//cout<<z3coding.toString(phiFormula) <<" and "<<z3coding.toString(arrayAcessProperty)<<" genL: "<<z3coding.toString(ttt->formula)<<std::endl;
					result->add(ttt);
				}
			}
		}
		if(checkAtomicScalarSubStep(indexEnv,phiBegin,step,phiEnd)){
			expr index(c);
			if(mu.isGtZero(step)){
				index=phiEnd.arg(0);
			}
			else if(mu.isLtZero(step)){
				index=phiBegin.arg(0);
			}
			vector<expr>* relevantArrayAcessProperties=getPropertiesRelevantArrayAcessWithIndex(index,in);
			for(expr arrayAcessProperty:*relevantArrayAcessProperties){
				if(z3coding.isPhiFormula( arrayAcessProperty)) continue;
				if(mu.isGtZero(step)){
					expr newphiEndFormula=z3coding.substitute(phiEndFormula,phiEnd,index);
					vector<expr> * cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(phiBeginFormula);
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(newphiEndFormula);
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(stepFormula);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					expr newquantifier=constructNewQuantifierName(cons);
					expr newbody=z3coding.substitute(arrayAcessProperty,phiEnd,newquantifier);
					
					expr newQuantifierBeginFormula=phiBeginFormula;
					expr newQuantifierEndFormula=newphiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(phiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(newphiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					
					if(!z3coding.equal(newbody,arrayAcessProperty)){
						Formula* ttt=new Formula(z3coding.constructForAllFormula(newquantifier,newQuantifierBeginFormula,
						newQuantifierEndFormula,newQuantifierstepFormula,newbody));
						//cout<<z3coding.toString(phiFormula) <<" and "<<z3coding.toString(arrayAcessProperty)<<" genL: "<<z3coding.toString(ttt->formula)<<std::endl;
						result->add(ttt);
					}
				}
				else if(mu.isLtZero(step)){
					expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,phiBegin,index);
					
					vector<expr> * cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
					vector<expr> * initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula);
					vector<expr> * endcons=z3coding.getConstsWithQuantifier(phiEndFormula);
					vector<expr> * stepcons=z3coding.getConstsWithQuantifier(stepFormula);
					z3coding.pushAToB(initcons,cons);
					z3coding.pushAToB(endcons,cons);
					z3coding.pushAToB(stepcons,cons);
					
					expr newquantifier=constructNewQuantifierName(cons);
					expr newbody=z3coding.substitute(arrayAcessProperty,phiBegin,newquantifier);
					expr newQuantifierBeginFormula=newphiBeginFormula;
					expr newQuantifierEndFormula=phiEndFormula;
					expr newQuantifierstepFormula=stepFormula;
					if(!z3coding.equal(quantifier,newquantifier)){
						newQuantifierBeginFormula=z3coding.substitute(newphiBeginFormula,quantifier,newquantifier);
						newQuantifierEndFormula=z3coding.substitute(phiEndFormula,quantifier,newquantifier);
						newQuantifierstepFormula=z3coding.substitute(stepFormula,quantifier,newquantifier);
					}
					
					if(!z3coding.equal(newbody,arrayAcessProperty)){
						Formula * ttt=new Formula(z3coding.constructForAllFormula(newquantifier,newQuantifierBeginFormula,
						newQuantifierEndFormula,newQuantifierstepFormula,newbody));
						//cout<<z3coding.toString(phiFormula) <<" and "<<z3coding.toString(arrayAcessProperty)<<" genL: "<<z3coding.toString(ttt->formula)<<std::endl;
						result->add(ttt);
					}
				}
			}
		}
	}
	#ifdef _DEBUG
	//cout<<"updatePhi::out::"<<toString(result)<<std::endl;
	#endif
	return result;
}

FlowSet  *updateForAll(FlowSet* indexEnv,FlowSet  * in){
	//∀x.x ∈ [initi,c,i),ψ1(e1[f1(x)]) ∈ a ∧ ψ2(e1[f1(i)]) ∈ a ∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)])∏p ψ2(e1[f1(x)]) 				(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i − c)]) ∈ a ∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)]) ∏p ψ2(e1[f1(x)]) 	(8)
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	vector<expr>* forallFormulas=getAllForallFormulas(in);
	for(expr forAllFormula:*forallFormulas){
		expr quantifier=z3coding.getQuantifier(forAllFormula);
		expr step=z3coding.getForAllFormulaStep(forAllFormula);
		expr stepFormula=z3coding.getForAllFormulaStepFormula(forAllFormula);
		expr quantifierBegin=z3coding.getForAllFormulaBegin(forAllFormula);
		expr quantifierEnd=z3coding.getForAllFormulaEnd(forAllFormula);
		expr quantifierBeginFormula=z3coding.getForAllFormulaBeginFormula(forAllFormula);
		expr quantifierEndFormula=z3coding.getForAllFormulaEndFormula(forAllFormula);
		expr quantifierExtendFormula=z3coding.getForAllFormulaExtendFormula(forAllFormula);
		expr body=z3coding.getQuantifierFormulaBody(forAllFormula);
		if(checkAtomicScalar(indexEnv,quantifierBegin,step,quantifierEnd)){
			if(mu.isGtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierEnd);
				expr bodyresult=merge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd+step);
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
			else if(mu.isLtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
				expr bodyresult=merge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,quantifierBegin,quantifierBegin+step);
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierBegin,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
		}
		if(checkAtomicScalarSubStep(indexEnv,quantifierBegin,step,quantifierEnd)){
			if(mu.isGtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierEnd);
				expr bodyresult=merge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd.arg(0));
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
			else if(mu.isLtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
				expr bodyresult=merge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,quantifierBegin,quantifierBegin.arg(0));
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierBegin,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
		}
	}
	return result;
}

FlowSet* filteringLeftNonPhiFormula(FlowSet* in){
	return in;	
}
vector<expr>* getAllForallFormulas(FlowSet  * in){
	vector<expr>* result=new vector<expr>();
	vector<Property*>* tmp=in->toVector();
	for(Property* p:*tmp){
		Formula* f=(Formula*)p;
		if(z3coding.isForAllFormula(f->formula)){
			result->push_back(f->formula);
		}
	}
	return result;
}
vector<expr>* getAllPhiFormulas(FlowSet  * in){
	vector<expr>* result=new vector<expr>();
	vector<Property*>* tmp=in->toVector();
	for(Property* p:*tmp){
		Formula* f=(Formula*)p;
		if(z3coding.isPhiFormula(f->formula)){
			result->push_back(f->formula);
		}
	}
	return result;
}
bool checkAtomicScalar(FlowSet* indexEnv,expr begin,expr step,expr end){
	expr index(c);
	expr init(c);
	if(mu.isGtZero(step)){
		index=end;
		init=begin;
	}
	else if(mu.isLtZero(step)){
		index=begin;
		init=end;
	}
	else{
		return false;
	}
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)indexEnv;
	for(Property* p: vlsOut->elements){
		AtomVariabla * av=(AtomVariabla *)p;
		if(z3coding.equal(av->scalaVarz3coding,index)){
			if(av->hasStep()){
				if(z3coding.equal(av->stepz3coding,step)&&z3coding.equal(av->initz3coding,init)){
					return true;
				}
				return false;
			}
			else{
				return false;
			}
		}
	}
	return false;
}
bool checkAtomicScalarSubStep(FlowSet* indexEnv,expr begin,expr step,expr end){
	expr index(c);
	expr init(c);
	if(mu.isGtZero(step)){
		if(end.is_app()&&Z3_is_eq_func_decl(c,end.decl(),z3coding.MinDecl)&& z3coding.equal(end.arg(1),step)){
			index=end.arg(0);
			init=begin;
		}
		else{
			return false;
		}
	}
	else if(mu.isLtZero(step)){
		if(begin.is_app()&&Z3_is_eq_func_decl(c,begin.decl(),z3coding.MinDecl)&& z3coding.equal(begin.arg(1),step)){
			index=begin.arg(0);
			init=end;
		}
		else{
			return false;
		}

	}
	else{
		return false;
	}
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)indexEnv;
	for(Property* p: vlsOut->elements){
		AtomVariabla * av=(AtomVariabla *)p;
		if(z3coding.equal(av->scalaVarz3coding,index)){
			if(av->hasStep()){
				if(z3coding.equal(av->stepz3coding,step)&&z3coding.equal(av->initz3coding,init)){
					return true;
				}
				return false;
			}
			else{
				return false;
			}
		}
	}
	return false;
}
vector<expr>* getPropertiesRelevantArrayAcessWithIndex(expr index,FlowSet* in){
	vector<expr>* result=new vector<expr>();
	vector<Property*>* invec=in->toVector();
	for(Property* p:*invec){
		Formula* f=(Formula*)p;
		vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(f->formula);
		for(expr arrayAcess:*arrayAcesses){
			if(z3coding.isIn(index,z3coding.getConsts(arrayAcess))){
				result->push_back(f->formula);
			}
		}
	}
	return result;
}
FlowSet * reduce(FlowSet  * in){
	FlowSet * result=userSupplied->newinitialFlow();result->clear(); 
	bool flag;
	vector<Property*>* invec=in->toVector();
	for(Property* p1:* invec){
		Formula* f1=(Formula*)p1;
		flag=false;
		for(Property* p2:* invec){
			Formula* f2=(Formula*)p2;
			if(partialOrderRelation(f2,f1)&&!z3coding.equal(f1->formula,f2->formula)){
				flag=true;
			}
		}
		if(!flag){
			result->add(f1);
		}
	}
	return result;
}

bool isArrayProperty(expr e){
	vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(e);
	return arrayAcesses->size()!=0;
}
bool isDefProperty(expr e){
	vector<expr> * defAcesses=z3coding.getDefAcessMemoryUnit(e);
	return defAcesses->size()!=0;
}
bool isSubscriptContain(expr arrayProperty,expr index){
	vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(arrayProperty);
	for(expr arrayAcess:*arrayAcesses){
		if(z3coding.isIn(index,z3coding.getConsts(arrayAcess))){
			return true;
		}
	}
	return false;
}

bool isDefSubscriptContain(expr defProperty,expr index){
	vector<expr> * defAcesses=z3coding.getDefAcessMemoryUnit(defProperty);
	for(expr defAcess:*defAcesses){
		if(z3coding.isIn(index,z3coding.getConsts(defAcess))){
			return true;
		}
	}
	return false;
}


FlowSet * genSimPlePriopertyByMultiRelation(FlowSet* simpleProps_in, FlowSet* indexEnv,FlowSet* indexRelations){
	FlowSet * result=new ValueListSetWithUniversalSet();
	ValueListSetWithUniversalSet* indexRelationsVls=(ValueListSetWithUniversalSet*)indexRelations;
	vector<expr>* simpleProps_inexpr=flowSetToExprSet(simpleProps_in);
	for(expr e:*simpleProps_inexpr){
		//cout<<"property is: "<<e<<std::endl;
		if(!isArrayProperty(e)&&!isDefProperty(e)) continue;
		for(Property* p:indexRelationsVls->elements){
			//process p
			//cout<<"relation is: "<<p->toString()<<std::endl;
			IndexesRelation* ir=(IndexesRelation*)p;
			expr index1=ir->scalaVariabla1;
			expr index2=ir->scalaVariabla2;
			int diff=ir->diff;
			/*if(isStepEqOne(indexEnv,index1)||isStepEqNeOne(indexEnv,index1)){
				expr i1Eqf=getIndex2EqFIndex1(index1,index2,diff,indexEnv);
				cout<<"relation eqtion is: "<<i1Eqf<<std::endl;
				if(!isSubscriptContain(e,index1)&&!isSubscriptContain(e,index2)) continue;
				expr newe=z3coding.substitute(e,index1,i1Eqf);
				cout<<"new simple formula is: "<< newe<<std::endl;
				result->add(new Formula(newe));
			}
			else if(isStepEqOne(indexEnv,index2)||isStepEqNeOne(indexEnv,index2)){
				expr i2Eqf=getIndex2EqFIndex1(index2,index1,diff,indexEnv);
				cout<<"relation eqtion is: "<< i2Eqf<<std::endl;
				if(!isSubscriptContain(e,index1)&&!isSubscriptContain(e,index2)) continue;
				expr newe=z3coding.substitute(e,index2,i2Eqf);
				cout<<"new simple formula is: "<< newe<<std::endl;
				result->add(new Formula(newe));
			}
			else{
				expr i1Eqf=getIndex2EqFIndex1(index1,index2,diff,indexEnv);
				cout<<"relation eqtion is: "<<i1Eqf<<std::endl;
				if(!isSubscriptContain(e,index1)&&!isSubscriptContain(e,index2)) continue;
				expr newe=z3coding.substitute(e,index2,i1Eqf);
				cout<<"new simple formula is: "<< newe<<std::endl;
				result->add(new Formula(newe));
			}*/
			if((!isSubscriptContain(e,index1)||!isSubscriptContain(e,index2))
			&&(!isDefSubscriptContain(e,index1)||!isDefSubscriptContain(e,index2))
			) continue;
			expr i1Eqf=getIndex2EqFIndex1(index1,index2,diff,indexEnv);
			//cout<<"relation eqtion is: "<<i1Eqf<<std::endl;
			expr newe=z3coding.substitute(e,index1,i1Eqf);
			//cout<<"new simple formula is: "<< newe<<std::endl;
			result->add(new Formula(newe));
			expr i2Eqf=getIndex2EqFIndex1(index2,index1,diff,indexEnv);
			//cout<<"relation eqtion is: "<< i2Eqf<<std::endl;
			newe=z3coding.substitute(e,index2,i2Eqf);
			//cout<<"new simple formula is: "<< newe<<std::endl;
			result->add(new Formula(newe));
		}
	}
	return result;	
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

bool isStepEqOne(FlowSet* indexEnv,expr index){
	AtomVariabla* indexp=getAtomVariablaBy(indexEnv,index);
	if(indexp!=nullptr){
		return isEq(indexp->stepz3coding,1);
	}
	return false;
}

bool isStepEqNeOne(FlowSet* indexEnv,expr index){
	AtomVariabla* indexp=getAtomVariablaBy(indexEnv,index);
	if(indexp!=nullptr){
		return isEq(indexp->stepz3coding,-1);
	}
	return false;
}

bool isEq(expr e,int i){
	if(!e.is_int()){
		std::cerr<<"LiftAnalysis::isEq: "<< e <<" must be int type!"<<std::endl;	
		return false;
	}
	else{
		if(e.is_numeral()){
			std::string tmp=Z3_ast_to_string(e.ctx(),e);
			//cout<<"stoi arg is: "<<tmp<<std::endl;
			if(std::stoi(tmp)==i) return true;
		}
		return false;
	}
}

expr getIndex2EqFIndex1(expr index1,expr index2,int diff,FlowSet* indexEnv){
	AtomVariabla* indexp1=getAtomVariablaBy(indexEnv,index1);
	AtomVariabla* indexp2=getAtomVariablaBy(indexEnv,index2);
	if(indexp1==nullptr||indexp2==nullptr){
		cerr<<"LiftAnalysis::getIndex2EqFIndex1:: something is wrong!"<<std::endl;
		return z3coding._error;
	}
	
	expr indexstep1=indexp1->stepz3coding;
	expr indexstep2=indexp2->stepz3coding;
	expr indexinit1=indexp1->initz3coding;
	expr indexinit2=indexp2->initz3coding;
	//(x1 − initx1)/c1 − (x2 − initx2)/c2 = d
	//if c1=1,c2=1,initx1=0,initx2=0,d=0, return x2;
	//if c1=1,c2=1,initx1=0,initx2=0, return x2+d;
	//if c1=1,c2=1,initx1=0, return x2+d-initx2;
	//if c1=1,initx1=0, return (x2-intx2)/c2+d
	//if c1=1,return (x2-intx2)/c2+d+initx1;
	
	
	
	//(x1 − initx1)/c1 − (x2 − initx2)/c2 = d
	//if c1=-1,c2=-1,initx1=0,initx2=0,d=0, return x2;
	//if c1=-1,c2=-1,initx1=0,initx2=0, return x2+d;
	//if c1=-1,c2=-1,initx1=0, return x2+d-initx2;
	
	
	//if c1=-1,c2=1,initx1=0,initx2=0,d=0, return x2;
	//if c1=-1,c2=1,initx1=0,initx2=0, return x2+d;
	//if c1=-1,c2=1,initx1=0, return x2+d-initx2;
	
	
	//if c1=-1,initx1=0, return (intx2-x2)/c2-d
	//if c1=-1,return (intx2-x2)/c2-d+initx1;
	if(isEq(indexstep1,1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return index2;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return index2;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return -index2;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return -index2;	
	}
	
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return index2-diff;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return -index2-diff;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return index2+diff;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return diff-index2;	
	}
	
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)){
		return index2-diff-indexinit2;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)){
		return -index2-diff+indexinit2;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)){
		return index2+diff-indexinit2;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)){
		return diff+indexinit2-index2;	
	}
	
	else if(isEq(indexstep1,-1)&&isEq(indexinit1,0)){
		return (index2-indexinit2)/indexstep2-diff;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexinit1,0)){
		return (index2-indexinit2)/indexstep2+diff;	
	}
	else if(isEq(indexstep1,-1)){
		return (indexinit2-index2)/indexstep2-diff+indexinit1;	
	}
	else if(isEq(indexstep1,1)){
		return (((index2-indexinit2)/indexstep2)+diff)+indexinit1;	
	}
	//else return (((x2-initx2)/c2)+d)*c1+i1
	else{
		return ((index2-indexinit2)/indexstep2+diff)*indexstep1+indexinit1;	
	}
	
}

/*expr getIndex2EqFIndex1(expr index1,expr index2,int diff,const Stmt* s,unsigned count){
	AtomVariabla* indexp1=indexAnalysis->getAtomVariableBefor(s,count,index1);
	AtomVariabla* indexp2=indexAnalysis->getAtomVariableBefor(s,count,index2);
	expr indexstep1=indexp1->stepz3coding;
	expr indexstep2=indexp2->stepz3coding;
	expr indexinit1=indexp1->initz3coding;
	expr indexinit2=indexp2->initz3coding;
	//(x1 − initx1)/c1 − (x2 − initx2)/c2 = d
	//if c1=1,c2=1,initx1=0,initx2=0,d=0, return x2;
	//if c1=1,c2=1,initx1=0,initx2=0, return x2+d;
	//if c1=1,c2=1,initx1=0, return x2+d-initx2;
	//if c1=1,initx1=0, return (x2-intx2)/c2+d
	//if c1=1,return (x2-intx2)/c2+d+initx1;
	
	
	
	//(x1 − initx1)/c1 − (x2 − initx2)/c2 = d
	//if c1=-1,c2=-1,initx1=0,initx2=0,d=0, return x2;
	//if c1=-1,c2=-1,initx1=0,initx2=0, return x2+d;
	//if c1=-1,c2=-1,initx1=0, return x2+d-initx2;
	
	
	//if c1=-1,c2=1,initx1=0,initx2=0,d=0, return x2;
	//if c1=-1,c2=1,initx1=0,initx2=0, return x2+d;
	//if c1=-1,c2=1,initx1=0, return x2+d-initx2;
	
	
	//if c1=-1,initx1=0, return (intx2-x2)/c2-d
	//if c1=-1,return (intx2-x2)/c2-d+initx1;
	if(isEq(indexstep1,1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return index2;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return index2;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return -index2;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)&&diff==0){
		return -index2;	
	}
	
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return index2-diff;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return -index2-diff;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return index2+diff;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)&&isEq(indexinit2,0)){
		return diff-index2;	
	}
	
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)){
		return index2-diff-indexinit2;	
	}
	else if(isEq(indexstep1,-1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)){
		return -index2-diff+indexinit2;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,1)&&isEq(indexinit1,0)){
		return index2+diff-indexinit2;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexstep2,-1)&&isEq(indexinit1,0)){
		return diff+indexinit2-index2;	
	}
	
	else if(isEq(indexstep1,-1)&&isEq(indexinit1,0)){
		return (index2-indexinit2)/indexstep2-diff;	
	}
	else if(isEq(indexstep1,1)&&isEq(indexinit1,0)){
		return (index2-indexinit2)/indexstep2+diff;	
	}
	else if(isEq(indexstep1,-1)){
		return (indexinit2-index2)/indexstep2-diff+indexinit1;	
	}
	else if(isEq(indexstep1,1)){
		return (index2-indexinit2)/indexstep2+diff+indexinit1;	
	}
	//else return (((x2-initx2)/c2)+d)*c1+i1
	else{
		return ((index2-indexinit2)/indexstep2+diff)*indexstep1+indexinit1;	
	}
	
}*/
bool partialOrderRelation(Formula* f1,Formula* f2){
	if(userSupplied->isSimpleProperty(f1)&&userSupplied->isSimpleProperty(f2)){
		return userSupplied->partialOrderRelation(f1,f2);
	}
	else if(z3coding.isForAllFormula(f1->formula)&&z3coding.isForAllFormula(f2->formula)){
		return partialOrderRelation_forall_forall(f1->formula,f2->formula);
	}
	else if(z3coding.isPhiFormula(f1->formula)&&z3coding.isForAllFormula(f2->formula)){
		return partialOrderRelation_phi_forall(f1->formula,f2->formula);
	}
	return false;
}
/*bool partialOrderRelation_forall_forall(expr forallFormula1,expr forallFormula2){
	expr quantifier1=z3coding.getQuantifier(forallFormula1);
	expr step1=z3coding.getForAllFormulaStep(forallFormula1);
	expr stepFormula1=z3coding.getForAllFormulaStepFormula(forallFormula1);
	expr quantifierBegin1=z3coding.getForAllFormulaBegin(forallFormula1);
	expr quantifierEnd1=z3coding.getForAllFormulaEnd(forallFormula1);
	expr quantifierBeginFormula1=z3coding.getForAllFormulaBeginFormula(forallFormula1);
	expr quantifierEndFormula1=z3coding.getForAllFormulaEndFormula(forallFormula1);
	expr quantifierExtendFormula1=z3coding.getForAllFormulaExtendFormula(forallFormula1);
	expr body1=z3coding.getQuantifierFormulaBody(forallFormula1);

	expr quantifier2=z3coding.getQuantifier(forallFormula2);
	expr step2=z3coding.getForAllFormulaStep(forallFormula2);
	expr stepFormula2=z3coding.getForAllFormulaStepFormula(forallFormula2);
	expr quantifierBegin2=z3coding.getForAllFormulaBegin(forallFormula2);
	expr quantifierEnd2=z3coding.getForAllFormulaEnd(forallFormula2);
	expr quantifierBeginFormula2=z3coding.getForAllFormulaBeginFormula(forallFormula2);
	expr quantifierEndFormula2=z3coding.getForAllFormulaEndFormula(forallFormula2);
	expr quantifierExtendFormula2=z3coding.getForAllFormulaExtendFormula(forallFormula2);
	expr body2=z3coding.getQuantifierFormulaBody(forallFormula2);
	
	
	if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
			||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
		return false;
	}


	if(z3coding.equal(step1,step2)
			&&z3coding.equal(quantifierBegin1,quantifierBegin2)
			&&z3coding.equal(quantifierEnd1,quantifierEnd2)
			&&Z3_is_eq_func_decl(c,quantifierBegin1.decl(),quantifierBegin2.decl())
			&&Z3_is_eq_func_decl(c,quantifierEnd1.decl(),quantifierEnd2.decl())){
		return partialOrderRelation(new Formula(body1),new Formula(body2));
	}
	else{
		return false;
	}
}*/
bool partialOrderRelation_forall_forall(expr forAllFormula1,expr forAllFormula2){
	expr forallHead1=z3coding.getQuantifierFormulaHead(forAllFormula1);
	expr forallHead2=z3coding.getQuantifierFormulaHead(forAllFormula2);
	if(z3coding.equal(forallHead1,forallHead2)){
		expr body1=z3coding.getQuantifierFormulaBody(forAllFormula1);
		expr body2=z3coding.getQuantifierFormulaBody(forAllFormula2);
		return partialOrderRelation(new Formula(body1),new Formula(body2));
	}
	return false;
}
bool partialOrderRelation_phi_forall(expr phiFormula,expr forAllFormula){
		expr phiHead=z3coding.getQuantifierFormulaHead(phiFormula);
		expr phiqualifier=z3coding.getPhiQuantifier(phiFormula);
		expr forallHead=z3coding.getQuantifierFormulaHead(forAllFormula);
		expr forallqualifier=z3coding.getQuantifier(forAllFormula);
		expr newPhiHead=z3coding.substitute(phiHead,phiqualifier,forallqualifier);
		if(z3coding.equal(newPhiHead,forallHead)){
			return true;
		}
	return false;
}

/*bool partialOrderRelation_phi_forall(expr phiFormula,expr forAllFormula){
	expr phiBegin=z3coding.getPhiBegin(phiFormula);
	expr phiEnd=z3coding.getPhiEnd(phiFormula);
	expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
	expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
	expr phiStep=z3coding.getPhiStep(phiFormula);

	expr forallStep=z3coding.getForAllFormulaStep(forAllFormula);
	expr forallBegin=z3coding.getForAllFormulaBegin(forAllFormula);
	expr forallEnd=z3coding.getForAllFormulaEnd(forAllFormula);
	expr forallBeginFormula=z3coding.getForAllFormulaBeginFormula(forAllFormula);
	expr forallEndFormula=z3coding.getForAllFormulaEndFormula(forAllFormula);

	if(z3coding.equal(phiStep,forallStep)
			&& z3coding.equal(forallBegin,phiBegin)
			&& z3coding.equal(forallEnd,phiEnd)
			&&Z3_is_eq_func_decl(c,forallBeginFormula.decl(),phiBeginFormula.decl())
			&&Z3_is_eq_func_decl(c,forallEndFormula.decl(),phiEndFormula.decl())){
		return true;
	}
	return false;
}*/
vector<expr>* toExprs(FlowSet  * in){
	vector<expr>* result=new vector<expr>();
	vector<Property*>* invec=in->toVector();
	for(Property* p:*invec){
		Formula* f=(Formula*)p;
		result->push_back(f->formula);
	}
	return result;
}
FlowSet* toFlowSet(vector<expr>* in){
	FlowSet * flowSet=userSupplied->newinitialFlow();flowSet->clear();
	for(expr e: *in){
		flowSet->add(new Formula(e));
	}
	return flowSet;
}
expr merge(expr f,FlowSet  * in){
	vector<expr>* formulas=toExprs(in);
	if(z3coding.isIn(f,formulas)){
		return f;
	}
	Formula* formulaTmp1=new Formula(f);
	Formula* formulaTmp2=new Formula(f);
	FlowSet* in1=userSupplied->newinitialFlow();in1->clear();
	FlowSet* in2=userSupplied->newinitialFlow();in2->clear();
	FlowSet* out=userSupplied->newinitialFlow();out->clear();

	for(expr ele:*formulas){
		if(z3coding.isForAllFormula(f)&&z3coding.isForAllFormula(ele)){
			expr meet_result=_nonSimpleFormulaMeet(f,ele);
			if(!z3coding.checkError(meet_result)){	
				return meet_result;
			}
		}

		if(userSupplied->isSimpleProperty(formulaTmp1)&&userSupplied->isSimpleProperty(formulaTmp2)){
			formulaTmp2->formula=ele;
			in1->add(formulaTmp1);in2->add(formulaTmp2);
			userSupplied->merge(in1,in2,out);
			if(out->size()>0){	
				vector<Property*>* outvec=out->toVector();
				Formula* ret=(Formula*)(outvec->at(0));
				return ret->formula;
			}
		}
		in1->clear();in2->clear();out->clear();
	}
	//cerr<<"merge result is wrong!"<<std::endl;
	return z3coding._error;
}


expr merge_moreEqual(expr f,FlowSet  * in){
	vector<expr>* formulas=toExprs(in);
	if(z3coding.isIn(f,formulas)){
		return f;
	}
	Formula* formulaTmp1=new Formula(f);
	Formula* formulaTmp2=new Formula(f);
	FlowSet* in1=userSupplied->newinitialFlow();in1->clear();
	FlowSet* in2=userSupplied->newinitialFlow();in2->clear();
	FlowSet* out=userSupplied->newinitialFlow();out->clear();

	for(expr ele:*formulas){
		if(z3coding.isForAllFormula(f)&&z3coding.isForAllFormula(ele)){
			expr meet_result=_nonSimpleFormulaMeet(f,ele);
			if(!z3coding.checkError(meet_result)){	
				return meet_result;
			}
		}

		if(userSupplied->isSimpleProperty(formulaTmp1)&&userSupplied->isSimpleProperty(formulaTmp2)){
			formulaTmp2->formula=ele;
			in1->add(formulaTmp1);in2->add(formulaTmp2);
			userSupplied->merge(in1,in2,out);
			if(out->size()>0){	
				vector<Property*>* outvec=out->toVector();
				Formula* ret=(Formula*)(outvec->at(0));
				return ret->formula;
			}
		}
		in1->clear();in2->clear();out->clear();
	}
	for(expr ele:*formulas){
		formulaTmp2->formula=ele;
		if(userSupplied->isSimpleProperty(formulaTmp1)&&userSupplied->isSimpleProperty(formulaTmp2)){
			if(z3coding.power_equal(f,ele)){
				return ele;
			}
		}	
	}
	//cerr<<"merge_moreEqual is wrong!"<<std::endl;
	return z3coding._error;
}
bool isIndexUpdate(const clang::Stmt* clangStmt, expr stmt){
	if(indexAnalysis->mapToStmtOut.count(clangStmt)<=0){
		return false;
	}
	FlowSet* out=indexAnalysis->mapToStmtOut.at(clangStmt);
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
	for(Property* p: vlsOut->elements){
		AtomVariabla * av=(AtomVariabla *)p;
		if(z3coding.equal(av->indexUpdateStmtz3coding,stmt)){
			return true;
		}
	}
	return false;
}
bool isIn(AtomVariabla* av,vector<AtomVariabla*>* vs){
	for(AtomVariabla* ele:*vs){
		if(av->equal(ele)){
			return true;
		}
	}
	return false;
}
bool isIndexInitStmt(const clang::Stmt* clangStmt,expr stmt){
	if(indexAnalysis->mapToStmtOut.count(clangStmt)<=0){
		return false;
	}
	//cout<<"clangStmt:: "<<z3coding.toString(clangStmt)<<std::endl;
	FlowSet* out=indexAnalysis->mapToStmtOut.at(clangStmt);
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
	for(Property* p: vlsOut->elements){
		AtomVariabla * av=(AtomVariabla *)p;
		expr init=stmt.arg(1);
		if(av->indexInitStmt==clangStmt&&av->hasStep()
		&&z3coding.equal(av->initz3coding,init)){
			if(!isIn(av,indexVariables)){
				indexVariables->push_back(av);
			}
			return true;
		}
	}
	return false;
}

bool isIndexInitStmt(FlowSet* indexEnv,const clang::Stmt* clangStmt,expr stmt){
	FlowSet* out=indexEnv;
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
	for(Property* p: vlsOut->elements){
		AtomVariabla * av=(AtomVariabla *)p;
		expr init=stmt.arg(1);
		if(av->indexInitStmt==clangStmt&&av->hasStep()
		&&z3coding.equal(av->initz3coding,init)){
			if(!isIn(av,indexVariables)){
				indexVariables->push_back(av);
			}
			return true;
		}
	}
	return false;
}


/**
 * @brief check whether memoryUnit kill formula
 * @param Pre
 * @param memoryUnit
 * @param formula
 * @return 
 */
bool mayMemoryUnitIsInFormula(FlowSet* Pre,expr memoryunit,expr formula){
	if(memoryunit.is_const()){
		vector<expr>* consts=z3coding.getConsts(formula);
		for(auto it=consts->begin();it!=consts->end();it++){
			expr con=*it;
			if(z3coding.equal(memoryunit,con)){
				return true;
			}
		}
		return false;
	}
	else if(z3coding.isArrayAcess(memoryunit)){
		if(z3coding.isForAllFormula(formula)){
			return mayArrayAcessMemoryUnitIsInForAllFormula(Pre,memoryunit,formula);
		}
		if(z3coding.isPhiFormula(formula)){
			return mayArrayAcessMemoryUnitIsInPhiFormula(Pre,memoryunit,formula);
		}
		else{
			//cout<<"formula is: "<<formula<<std::endl;
			vector<expr> * formulaMemoryUnits=z3coding.getMemoryUnits(formula);
			for(expr formulamemoryunit: *formulaMemoryUnits){
				if(mayMemoryUnitIsIn(Pre,memoryunit,formulamemoryunit)){
					return true;
				}
			}
			return false;
		}
	}
	else if(z3coding.isDef_PointerExpr(memoryunit)){
		if(z3coding.isForAllFormula(formula)){
			return mayDefMemoryUnitIsInForAllFormula(Pre,memoryunit,formula);
			//return false;
		}
		if(z3coding.isPhiFormula(formula)){
			return mayDefMemoryUnitIsInPhiFormula(Pre,memoryunit,formula);
			//return false;
		}
		else{
			vector<expr> * formulaMemoryUnits=z3coding.getMemoryUnits(formula);
			for(expr formulamemoryunit: *formulaMemoryUnits){
				if(mayMemoryUnitIsIn(Pre,memoryunit,formulamemoryunit)){
					return true;
				}
			}
			return false;
		}
	}
	else if(z3coding.isMemberExpr(memoryunit)){
		if(z3coding.isForAllFormula(formula)){
			return mayMemberMemoryUnitIsInForAllFormula(Pre,memoryunit,formula);
			//return false;
		}
		if(z3coding.isPhiFormula(formula)){
			return mayMemberMemoryUnitIsInPhiFormula(Pre,memoryunit,formula);
			//return false;
		}
		else{
			vector<expr> * formulaMemoryUnits=z3coding.getMemoryUnits(formula);
			for(expr formulamemoryunit: *formulaMemoryUnits){
				if(mayMemoryUnitIsIn(Pre,memoryunit,formulamemoryunit)){
					return true;
				}
			}
			return false;
		}
	}
	else{
		std::cerr<<"LiftAnalysis::mayMemoryUnitIsInFormula:: we can not process "<<memoryunit<<std::endl;
		return true;
	}
}

bool mayDefMemoryUnitIsInForAllFormula(FlowSet* Pre,expr memoryunit,expr forAllFormula){
	return false;
}
bool mayDefMemoryUnitIsInPhiFormula(FlowSet* Pre,expr memoryunit,expr phiFormula){
	return false;
}
bool mayMemberMemoryUnitIsInForAllFormula(FlowSet* Pre,expr memoryunit,expr forAllFormula){
	return false;
}
bool mayMemberMemoryUnitIsInPhiFormula(FlowSet* Pre,expr memoryunit,expr phiFormula){
	return false;
}

bool mayMemoryUnitIsIn_DefPointer(FlowSet* Pre,expr memoryunit1,expr memoryunit2){
	if(z3coding.isDef_PointerExpr(memoryunit1)&&memoryunit2.is_const()){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
	else if(z3coding.isDef_PointerExpr(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
		
	else if(memoryunit1.is_const()&&z3coding.isDef_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isDef_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
	else if(z3coding.isDef_PointerExpr(memoryunit1)&&z3coding.isDef_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
	return true;
}
bool mayMemoryUnitIsIn(FlowSet* Pre,expr memoryunit1,expr memoryunit2){
	if(memoryunit1.is_const()&&memoryunit2.is_const()){
		return z3coding.equal(memoryunit1,memoryunit2);
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&memoryunit2.is_const()){
		//memoryunit1:A[i]  memoryunit2:A
		expr base1=z3coding.getArrayBase(memoryunit1);
		return z3coding.equal(base1,memoryunit2);
	}
	else if(memoryunit1.is_const()&&z3coding.isArrayAcess(memoryunit2)){
		vector<expr>* consts=z3coding.getConsts(memoryunit2);
		for(auto it=consts->begin();it!=consts->end();it++){
			expr con=*it;
			if(z3coding.equal(memoryunit1,con)){
				return true;
			}
		}
		return false;
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		//A[B[exp]][exp]
		expr base1=z3coding.getArrayBase(memoryunit1);
		expr base2=z3coding.getArrayBase(memoryunit2);
		if(!z3coding.equal(base1,base2)){
			return false;
		}
		else{
			int d1=z3coding.getArrayAcessDimension(memoryunit1);
			int d2=z3coding.getArrayAcessDimension(memoryunit2);
			expr idxEqualAssert(c);
			//A[e11][e21]..[en1]  A[e12][e22]..[en2]
			if(d1==d2){
				expr idx1k=z3coding.getArrayAcessKthIdx(memoryunit1,0);
				expr idx2k=z3coding.getArrayAcessKthIdx(memoryunit2,0);
				idxEqualAssert= (idx1k==idx2k);
				for(int i=1;i<d1;i++){
					idx1k=z3coding.getArrayAcessKthIdx(memoryunit1,i);
					idx2k=z3coding.getArrayAcessKthIdx(memoryunit2,i);
					idxEqualAssert= idxEqualAssert&&(idx1k==idx2k);
				}
				check_result r=z3coding.satisfy(toExprs(Pre),idxEqualAssert);
				if(r==check_result::sat||r==check_result::unknown){
					return true;	
				}
				else {
					return false;
				}
			}
			//A[e11][e21]..[en1]...e[m1]  A[e12][e22]..[en2]
			else if(d1>d2){
				expr formerKDimension=z3coding.getFormerKDimension(memoryunit1,d2);
				expr idx1k=z3coding.getArrayAcessKthIdx(formerKDimension,0);
				expr idx2k=z3coding.getArrayAcessKthIdx(memoryunit2,0);
				idxEqualAssert= (idx1k==idx2k);
				for(int i=1;i<d2;i++){
					idx1k=z3coding.getArrayAcessKthIdx(formerKDimension,i);
					idx2k=z3coding.getArrayAcessKthIdx(memoryunit2,i);
					idxEqualAssert= idxEqualAssert&&(idx1k==idx2k);
				}
				check_result r=z3coding.satisfy(toExprs(Pre),idxEqualAssert);
				if(r==check_result::sat||r==check_result::unknown){
					return true;	
				}
				else {
					return false;
				}
			}
			//A[e11][e21]..[en1]  A[e12][e22]..[en2]...e[m1]
			else{
				expr formerKDimension=z3coding.getFormerKDimension(memoryunit2,d1);
				expr idx1k=z3coding.getArrayAcessKthIdx(memoryunit1,0);
				expr idx2k=z3coding.getArrayAcessKthIdx(formerKDimension,0);
				idxEqualAssert= (idx1k==idx2k);
				for(int i=1;i<d1;i++){
					idx1k=z3coding.getArrayAcessKthIdx(memoryunit1,i);
					idx2k=z3coding.getArrayAcessKthIdx(formerKDimension,i);
					idxEqualAssert= idxEqualAssert&&(idx1k==idx2k);
				}
				check_result r=z3coding.satisfy(toExprs(Pre),idxEqualAssert);
				if(r==check_result::sat||r==check_result::unknown){
					return true;	
				}
				else {
					return false;
				}
			}
		}
	}
	else if(z3coding.isDef_PointerExpr(memoryunit1)&&memoryunit2.is_const()){
		return mayMemoryUnitIsIn_DefPointer(Pre,memoryunit1,memoryunit2);
	}
	else if(z3coding.isDef_PointerExpr(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		return mayMemoryUnitIsIn_DefPointer(Pre,memoryunit1,memoryunit2);
	}
		
	else if(memoryunit1.is_const()&&z3coding.isDef_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DefPointer(Pre,memoryunit1,memoryunit2);
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isDef_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DefPointer(Pre,memoryunit1,memoryunit2);
	}
	else if(z3coding.isDef_PointerExpr(memoryunit1)&&z3coding.isDef_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DefPointer(Pre,memoryunit1,memoryunit2);
	}
	else if(memoryunit1.is_const()&&z3coding.isMemberExpr(memoryunit2)){
		return false;
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&memoryunit2.is_const()){
		return false;
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isMemberExpr(memoryunit2)){
		return false;
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		return false;
	}
	else if(z3coding.isDef_PointerExpr(memoryunit1)&&z3coding.isMemberExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&z3coding.isDef_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,memoryunit1,memoryunit2);
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&z3coding.isMemberExpr(memoryunit2)){
		if(!Z3_is_eq_func_decl(c,memoryunit1.decl(),memoryunit2.decl())){
			return false;
		}
				
		expr access1=	memoryunit1.arg(0);
		expr access2=	memoryunit2.arg(0);
		if (z3coding.isIndirectMemberExpr(memoryunit1)){
			return pointerAnalysis->isMemoryUnitIsInAfter(nullptr,0,access1,access2);
		}
		else{
			return z3coding.equal(access1,access2);
		}
	}
	else{
		std::cerr<<"LiftAnalysis:mayMemoryUnitIsIn: something is wrong!"<<std::endl;
		std::cerr<<"error info:: memoryunit1: "<<memoryunit1<<", memoryunit2: "<<memoryunit2 <<std::endl;
		return true;
	}
	return true;
}
bool mayArrayAcessMemoryUnitIsInForAllFormula(FlowSet* Pre,expr memoryunit,expr forAllFormula){
	expr memoryunitbase=z3coding.getArrayBase(memoryunit);
	int  memoryunitDim=z3coding.getArrayAcessDimension(memoryunit);
	vector<expr> * allstepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
	vector<expr> * allbeginformulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
	vector<expr> * allendformulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
	vector<expr> * allquantifiers=z3coding.getAllQuantifier(forAllFormula);
	vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(forAllFormula);
	for(expr arrayAcess:*arrayAcesses){
		expr arrayAcessBase=z3coding.getArrayBase(arrayAcess);
		if(mayMemoryUnitIsIn(Pre,memoryunitbase,arrayAcessBase)){
			//if exist any quantifier is in arrayAcess
			vector<expr> * arrayAcessCons=z3coding.getConsts(arrayAcess);
			bool quantifierIsInArrayAcess=false;
			for(expr quantifier: *allquantifiers){
				if(z3coding.isIn(quantifier,arrayAcessCons)){
					quantifierIsInArrayAcess=true;
					break;
				}
			}
			if(quantifierIsInArrayAcess){
				// 	determine which dim of quantifier occur
				//	get the max and min
				//	determine the dim index of memoryunit1 is in the min..max
				int arrayAcessDim=z3coding.getArrayAcessDimension(arrayAcess);
				bool allArrayAcessDimMayEqual=true;
				for(int i=0;i<arrayAcessDim&&i<memoryunitDim;i++){
					expr arrayAcessKthIdx=z3coding.getArrayAcessKthIdx(arrayAcess,i);
					expr memoryunitKthIdx=z3coding.getArrayAcessKthIdx(memoryunit,i);
					vector<expr> *ithidxCons=z3coding.getConsts(arrayAcessKthIdx);
					vector<int> *isInQuantifierIndex=new vector<int>();
					for(unsigned i=0;i<allquantifiers->size();i++){
						expr quantifier=allquantifiers->at(i);
						if(z3coding.isIn(quantifier,ithidxCons)){
							isInQuantifierIndex->push_back(i);
						}
					}
					if(isInQuantifierIndex->size()>0){
						//get the max and min of index(x,y...), x and y is the quantifier
						//determine the dim index of memoryunit1 is in the min..max
						vector<expr> *quantifierFormulas= new vector<expr>();
						//expr *parrayAcessKthIdx=&arrayAcessKthIdx;
						for(int quantifierIndex:*isInQuantifierIndex){
							//quantifier is not in Pre
							expr quantifier=allquantifiers->at(quantifierIndex);
							expr beginformula=allbeginformulas->at(quantifierIndex);
							expr begin=beginformula.arg(0);
							expr endformula=allendformulas->at(quantifierIndex);
							expr stepFormula=allstepFormulas->at(quantifierIndex);
							if(!z3coding.isIn(quantifier,toExprs(Pre))){
								expr qi=beginformula&&endformula&&stepFormula;
								quantifierFormulas->push_back(qi);
							}
							else{
								std::cerr<<"LiftAnalysis::mayArrayAcessMemoryUnitIsInForAllFormula: something is wrong!"<<std::endl;

							}
						}
						expr satisfyFormula=arrayAcessKthIdx==memoryunitKthIdx;
						vector<expr> * Pres=new vector<expr>();
						vector<expr> * tmp=toExprs(Pre);
						z3coding.pushAToB(tmp,Pres);
						z3coding.pushAToB(quantifierFormulas,Pres);

						if(z3coding.satisfy(Pres,satisfyFormula)==check_result::unsat){
							//continue next arrayAcess
							allArrayAcessDimMayEqual=false;
							break;
						}
					}
					else{
						//quantifier not in kthidx
						expr satisfyFormula=arrayAcessKthIdx==memoryunitKthIdx;
						if(z3coding.satisfy(toExprs(Pre),satisfyFormula)==check_result::unsat){
							allArrayAcessDimMayEqual=false;
							break;
						}
					}
				}
				if(allArrayAcessDimMayEqual==true){
					return true;
				}
			}
			else{
				//else direct check whether arrayAcess is equal to memoryUnit
				if(mayMemoryUnitIsIn(Pre,memoryunit,arrayAcess)){
					return true;
				}
			}
		}
		else{
			//do nothing
			continue;
		}
	}
	return false;
}
bool mayArrayAcessMemoryUnitIsInPhiFormula(FlowSet* Pre,expr arrayAcessUnit,expr phiFormula){
	expr phiBegin=z3coding.getPhiBegin(phiFormula);
	expr phiEnd=z3coding.getPhiEnd(phiFormula);
	expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
	expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
	expr phiStep=z3coding.getPhiStep(phiFormula);
	vector<expr> * arrayAcesses=z3coding.getArrayAcessMemoryUnit(phiFormula);
	for(expr arrayAcess:*arrayAcesses){
		if(mayMemoryUnitIsIn(Pre,arrayAcessUnit,arrayAcess)){
			return true;
		}
	}
	return false;
	
}
vector<AtomVariabla*>* indexVariables; 
public:
LiftAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,context &ctx,EnvironmentAnalysis* envAna,AtomVariablaAnalysis* indexAna,
		Z3Coding &z3c,UserSupplied * userSup,MemoryUtil &memoryUtil,PointerAnalysis* pointerAna,C2Z3* c2z3,
		MultiIndexesRelationAnalysis* multiIndexesRelationAna):IntraDataFlowAnalysis(functionDecl,cfg),c(ctx),
	envAnalysis(envAna),indexAnalysis(indexAna),z3coding(z3c),userSupplied(userSup),mu(memoryUtil),pointerAnalysis(pointerAna),
	c2z3Stmt(c2z3),multiIndexesRelationAnalysis(multiIndexesRelationAna)
	{
		indexVariables=new vector<AtomVariabla*>();
		doAnalysis();
	}
void print(){
	for (std::map<CFGBlock*, FlowSet*>::iterator it=mapToBlockIn.begin(); it!=mapToBlockIn.end(); ++it){
		std::cout <<"--------[B"<< it->first->getBlockID ()<<"]" << " in :--------"<<std::endl; 
		std::cout<<toString(flowSetToExprSet(it->second))<<std::endl;
		list<pair<CFGBlock*,FlowSet*>*> * outs=mapToBlockOut.at(it->first);
		for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator outsIt = outs->begin(); outsIt != outs->end(); outsIt++){
			pair<CFGBlock*,FlowSet*> *ele=*outsIt;
			if(ele->first==nullptr) continue;
			std::cout <<"----------[B"<< it->first->getBlockID()<<"]"<<"-> [B" <<ele->first->getBlockID()<<"]"<<" out -------:"<<std::endl; 
			std::cout<<toString(flowSetToExprSet(ele->second))<<std::endl;
		}
	}
}
FlowSet * newinitialFlow(){
	return userSupplied->newinitialFlow();
}
expr processDeclStmt(const Decl* decl){
		const  ValueDecl * valueDecl=(const  ValueDecl *)decl;
		std::string buffer;
		llvm::raw_string_ostream strout(buffer);
		valueDecl->printName(strout);
		std::string varName=strout.str();
		QualType declQT = valueDecl->getType();
		z3::sort type=z3coding.clangTypeToZ3Sort(declQT)->type;
		std::string varNamePre=varName+"@pre";
		expr indexInitZ3expr= z3coding.prime(c.constant(varName.c_str(),type))==c.constant(varNamePre.c_str(),type);
		return indexInitZ3expr;	
}
FlowSet * entryInitialFlow(){
	FlowSet * result=userSupplied->entryInitialFlow();
	CFGBlock &entry=cfg->getEntry();
	FlowSet* entryIn=indexAnalysis->getMapToBlockIn()->at(&entry);
	for(unsigned i=0;i<parms.size();i++){
		ParmVarDecl * pd=parms[i];
		expr initZ3Stmt=processDeclStmt((const Decl*)pd);
		if(isIndexInitStmt(entryIn,(const clang::Stmt *)pd,initZ3Stmt)){
			cout<<"initZ3Stmt::"<<initZ3Stmt<<std::endl;
			Property* tmppp=genPhi(entryIn,initZ3Stmt);
			if(tmppp!=nullptr){
				result->add(tmppp);
			}
		}
		
	}
	return result;
}

void copy(FlowSet *&from,FlowSet  *&to){
	to=from->clone();
}

//used in dataflow analysis
bool equal(FlowSet  *&from,FlowSet  *&to){
	return from->equal(to);
}

void merge(FlowSet  * &in1,FlowSet  *&in2,FlowSet  *&out){
#ifdef _DEBUG
/*	cout<<toString(in1)<<std::endl;
	cout<<"--merge--"<<std::endl;
	cout<<toString(in2)<<std::endl;
	cout<<"--merge- result is ::------"<<std::endl;*/
#endif
	if(in1->isUniversalSet()&&in2->isUniversalSet()) {
		out=in1->clone();

	}
	else if(in1->isUniversalSet()){
		out=in2->clone();

	}
	else if(in2->isUniversalSet()) {
		out=in1->clone();

	}
	else{
		out->clear();
		if(_existNonSimpleFormula(in1)||_existNonSimpleFormula(in2)){
			FlowSet  * nonSimpleFormulain1=_filterNonSimpleFormula(in1);
			FlowSet  * nonSimpleFormulain2=_filterNonSimpleFormula(in2);
			FlowSet  * simpleFormulain1=_filterSimpleFormula(in1);
			FlowSet  * simpleFormulain2=_filterSimpleFormula(in2);
			FlowSet  * nonSimpleFormulaResult=out->clone();nonSimpleFormulaResult->clear();
			_nonSimpleFormulasMerge(nonSimpleFormulain1,nonSimpleFormulain2,nonSimpleFormulaResult);
			userSupplied->merge(simpleFormulain1,simpleFormulain2,out);
			out->Union(nonSimpleFormulaResult);

		}
		else {
			userSupplied->merge(in1,in2,out);
		}
	}
#ifdef _DEBUG
	/*cout<<toString(out)<<std::endl;
	cout<<"-------------------"<<std::endl;*/
#endif

}
};
#endif
