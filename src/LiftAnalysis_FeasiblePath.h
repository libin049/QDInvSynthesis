#ifndef _LiftAnalysis_FeasiblePath_H
#define _LiftAnalysis_FeasiblePath_H
#include "Formula.h"
#include "EnvironmentAnalysisUtil.h"
#include "DataFlowAnalysis_FeasiblePath.h"
#include "UserSupplied.h"
#include "MemoryUtil.h"
#include "Z3Coding.h"
#include "MultiIndexesRelationAnalysis.h"
#include "AtomVariableAnalysis.h"

class LiftAnalysis_FeasiblePath: public IntraDataFlowAnalysis_FeasiblePath{
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
		std::string toString_final(vector<z3::expr>* exprs,bool isFinal){
			std::string ret="";
			if(exprs==nullptr) return "";
			for(auto it=exprs->begin();it!=exprs->end();it++){
				z3::expr e=(z3::expr) *it;
				//std::string eName=Z3_ast_to_string(e.ctx(),e);
				if(isFinal){
					if(z3coding.isPhiFormula(e)) continue;
				}
				std::string eName=z3coding.toString(e);
				ret+=eName+";\n ";
			}
			return ret;
		}

		unique_ptr<vector<expr>> flowSetToExprSet(FlowSet * flowSet){
			auto propertySet=flowSet->toVector();
			unique_ptr<vector<expr>> exprSet(new vector<expr>());//=;
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
//		void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
//			for(auto it=outs->begin();it != outs->end(); it++){
//				pair<CFGBlock*,FlowSet*>* ele=*it;
//				if(ele->second->isUniversalSet()){
//					ele->second->setNonUniversalSetWhenIsUniversalSet();
//				}
//			}
//			
//			FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(in),
//				indexAnalysis->getMapToBlockIn()->at(n),multiIndexesRelationAnalysis->getMapToBlockIn()->at(n));
//			FlowSet* tmpx2=in->clone();tmpx2->Union(tmpx1);
//			in=reduce(genQ(indexAnalysis->getMapToBlockIn()->at(n),envAnalysis->getMapToBlockIn()->at(n),tmpx2));
//			in=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->getMapToBlockIn()->at(n),in);
//			FlowSet * Pre=in->clone();
//
//			if(outs->size()==2){
//				const Stmt* T=n->getTerminatorCondition();
//				if(T==nullptr){
//					std::cerr<<"flowThrouth: TerminatorCondition can not be null! "<<std::endl;	
//				}
//				unsigned count=0;
//				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
//					CFGElement element=(*iterblock);
//					if(element.getKind()==CFGElement::Kind::Statement){
//						const Stmt* it=((CFGStmt*)&element)->getStmt();
//						/*if(it==T) break;*/
//						//the condition expression will appear within the set of 
//						//statements in the block (usually the last statement) 
//						if(n->size()>0&&count==n->size()-1){
//							T=it;
//							break;
//						}
//
//						FlowSet * Pos=userSupplied->newinitialFlow();
//						flowThrouth(it,Pre,Pos);
//						Pre=Pos->clone();
//						count++;
//					}
//				}
//
//				FlowSet * truePos=userSupplied->newinitialFlow();
//				FlowSet * falsePos=userSupplied->newinitialFlow();
//				flowThrouth(T,Pre,truePos,falsePos);
//				pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
//				FlowSet *tureFlow=(FlowSet*)tureBranch->second;
//				pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
//				FlowSet *falseFlow=(FlowSet*)falseBranch->second;
//
//				tureFlow->Union(truePos);
//				falseFlow->Union(falsePos);
//
//			}
//			else if(outs->size()==1){
//				Stmt* T=n->getTerminatorCondition();
//				if(T!=nullptr){
//					std::cerr<<"flowThrouth: TerminatorCondition must be null! "<<std::endl;	
//				}
//				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
//					CFGElement element=(*iterblock);
//					if(element.getKind()==CFGElement::Kind::Statement){
//						const Stmt* it=((CFGStmt*)&element)->getStmt();
//						FlowSet * Pos=userSupplied->newinitialFlow();
//						flowThrouth(it,Pre,Pos);
//						Pre=Pos->clone();
//					}
//				}
//				pair<CFGBlock*,FlowSet*>* out=outs->front();
//				FlowSet *outFlow=(FlowSet*)out->second;
//
//				outFlow->Union(Pre);
//			}
//		}
		
		
		/**
		 * @brief 输入参数分别是:输入，true分析的输入(如果有的话)，false分支的输入(如果有的话),需要被生成的输出结果
		 * @param n
		 * @param in
		 * @param trueIn
		 * @param falseIn
		 * @param outs
		 */
		void flowThrouth(CFGBlock*&n, FlowSet *&in,FlowSet *&trueIn,FlowSet *&falseIn, list<pair<CFGBlock*,FlowSet*>*> *&outs){
			//消除全集			
			for(auto it=outs->begin();it != outs->end(); it++){
				pair<CFGBlock*,FlowSet*>* ele=*it;
				if(ele->second->isUniversalSet()){
					ele->second->setNonUniversalSetWhenIsUniversalSet();
				}
			}
			//在基本快开始处，获取多索引性质，生成量词性质
			FlowSet* tmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(in),
				indexAnalysis->getMapToBlockIn()->at(n),
				multiIndexesRelationAnalysis->getMapToBlockIn()->at(n));
			FlowSet* tmpx2=in->clone();tmpx2->Union(tmpx1);
			in=reduce(genQ(indexAnalysis->getMapToBlockIn()->at(n),envAnalysis->getMapToBlockIn()->at(n),tmpx2));
			in=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->getMapToBlockIn()->at(n),in);
			FlowSet * Pre=in->clone();
			//如果输出结果是两个，说明是分支语句
			//如果有truein和falsein，分别交给true分支和false分支处理。作为它们各自的前置条件
			//如果truein不为空, truein可以传递到true分支
			//如果falsein不为空,falsein可以传递到false分支
			//
			//Pre1,Pre2,Pre3...Pren
			//in=merge(Pre1,Pre2,...Pren) 
			//T
			//truepos,falsepos
			//
			//如果Prei&&T不可满足,那么Prei不属于truepos
			//如果Prei&&!T不可满足,那么Prei不属于falsepos
			//truein=merge({prei|Prei&&T不是不可满足})
			//falsein=merge({prei|Prei&&!T不是不可满足})
			if(outs->size()==2){
				FlowSet * truePre=Pre->clone();
				FlowSet * falsePre=Pre->clone();
				if(trueIn!=nullptr){
					FlowSet* truetmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(trueIn),
						indexAnalysis->getMapToBlockIn()->at(n),
						multiIndexesRelationAnalysis->getMapToBlockIn()->at(n));
					FlowSet* truetmpx2=trueIn->clone();truetmpx2->Union(truetmpx1);
					trueIn=reduce(genQ(indexAnalysis->getMapToBlockIn()->at(n),
							envAnalysis->getMapToBlockIn()->at(n),truetmpx2));
					trueIn=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->getMapToBlockIn()->at(n),trueIn);
					truePre=trueIn->clone();
				}
				if(falseIn!=nullptr){
					FlowSet* falsetmpx1=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(falseIn),
							indexAnalysis->getMapToBlockIn()->at(n),
							multiIndexesRelationAnalysis->getMapToBlockIn()->at(n));
					FlowSet* falsetmpx2=falseIn->clone();falsetmpx2->Union(falsetmpx1);
					falseIn=reduce(genQ(indexAnalysis->getMapToBlockIn()->at(n),
						envAnalysis->getMapToBlockIn()->at(n),falsetmpx2));
					falseIn=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->getMapToBlockIn()->at(n),falseIn);
					falsePre=falseIn->clone();
				}
				const Stmt* T=n->getTerminatorCondition();
				if(T==nullptr){
					std::cerr<<"flowThrouth: TerminatorCondition can not be null! "<<std::endl;	
				}
				//process true branch and false branch
				//truein和falsein都为null，那么in是true分支和false分支的输入
				if(trueIn==nullptr&&falseIn==nullptr){
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

							FlowSet * Pos=userSupplied->newinitialFlow();Pos->clear();
							flowThrouth(it,Pre,Pos);
							Pre=Pos->clone();
							count++;
						}
					}

					FlowSet * truePos=userSupplied->newinitialFlow();truePos->clear();
					FlowSet * falsePos=userSupplied->newinitialFlow();falsePos->clear();
					flowThrouth(T,Pre,truePos,falsePos);
					pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
					FlowSet *tureFlow=(FlowSet*)tureBranch->second;
					pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
					FlowSet *falseFlow=(FlowSet*)falseBranch->second;
					tureFlow->Union(truePos);
					falseFlow->Union(falsePos);
				}
				else{
					//process true branch
					//生成true分支的后置条件 
					{
						#ifdef _DEBUG
						cout<<"--------------process true branch -----------"<<std::endl;
						#endif
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

								FlowSet * Pos=userSupplied->newinitialFlow();Pos->clear();
								flowThrouth(it,truePre,Pos);
								truePre=Pos->clone();
								count++;
							}
						}

						FlowSet * truePos=userSupplied->newinitialFlow();truePos->clear();
						FlowSet * falsePos=userSupplied->newinitialFlow();falsePos->clear();
						flowThrouth(T,truePre,truePos,falsePos);
						pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
						FlowSet *tureFlow=(FlowSet*)tureBranch->second;
						tureFlow->Union(truePos);
					}
					//process false branch 
					//生成false分支的后置条件 
					{
						#ifdef _DEBUG
						cout<<"--------------process false branch -----------"<<std::endl;
						#endif
						//process false branch
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

								FlowSet * Pos=userSupplied->newinitialFlow();Pos->clear();
								flowThrouth(it,falsePre,Pos);
								falsePre=Pos->clone();
								count++;
							}
						}
						
						FlowSet * truePos=userSupplied->newinitialFlow();truePos->clear();
						FlowSet * falsePos=userSupplied->newinitialFlow();falsePos->clear();
						flowThrouth(T,falsePre,truePos,falsePos);
						pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
						FlowSet *falseFlow=(FlowSet*)falseBranch->second;
						falseFlow->Union(falsePos); 
					}
				}
			}
			else if(outs->size()==1){
				Stmt* T=n->getTerminatorCondition();
				if(T!=nullptr){
					std::cerr<<"flowThrouth: TerminatorCondition must be null! "<<std::endl;	
				}
				//cout<<"block in: "<<toString(Pre)<<std::endl;
				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
					CFGElement element=(*iterblock);
					if(element.getKind()==CFGElement::Kind::Statement){
						const Stmt* it=((CFGStmt*)&element)->getStmt();
						FlowSet * Pos=userSupplied->newinitialFlow();Pos->clear();
						flowThrouth(it,Pre,Pos);
						Pre=Pos->clone();
					}
				}
				pair<CFGBlock*,FlowSet*>* out=outs->front();
				FlowSet *outFlow=(FlowSet*)out->second;
				//cout<<"block out: "<<toString(Pre)<<std::endl;
				outFlow->Union(Pre);
			}
		}
		
		
		
		FlowSet* _filterNonSimpleFormula(FlowSet  *from){
			FlowSet* result=userSupplied->entryInitialFlow();
			result->clear();
			auto invec=from->toVector();
			for(Property * p:*invec){
				if(!userSupplied->isSimpleProperty((Formula*)p)){
					result->add(p);
				}
			}
			return result;
		}
		bool _existNonSimpleFormula(FlowSet  *from){
			auto invec=from->toVector();
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
			auto invec=from->toVector();
			for(Property * p:*invec){
				if(userSupplied->isSimpleProperty((Formula*)p)){
					result->add(p);
				}
			}
			return result;
		}
		void _nonSimpleFormulasMerge(FlowSet  *&in1,FlowSet  *&in2,FlowSet *&out){
			auto in1vec=in1->toVector();
			auto in2vec=in2->toVector();
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
			else if(z3coding.isExistFormula(e1)&&z3coding.isExistFormula(e2)){
				return meetExistFormula_ExistFormula(e1,e2);
			}
			//cerr<<"_nonSimpleFormulaMeet is wrong!"<<std::endl;
			return z3coding._error;
		}
		expr _merge(expr f1,expr f2){
			FlowSet* tmp1=userSupplied->newinitialFlow();tmp1->clear();
			FlowSet* tmp2=userSupplied->newinitialFlow();tmp2->clear();
			Formula ff1(f1);
			Formula ff2(f2);
			tmp1->add(&ff1);
			tmp2->add(&ff2);
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

			vector<expr> cons;
			auto initcons=z3coding.getConstsWithQuantifier(init);
			z3coding.pushAToB(initcons.get(),&cons);
			auto stepcons=z3coding.getConstsWithQuantifier(step);
			z3coding.pushAToB(stepcons.get(),&cons);
			cons.push_back(index);
			expr quantifier=constructNewQuantifierName(&cons);

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
			std::cerr<<"LiftAnalysis_FeasiblePath::constructNewQuantifierName: something is wrong!"<<std::endl;
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
			if(toString(stmt)=="j--"){
				cout<<"stmt:: "<<toString(stmt)<<std::endl;
			}
			cout<<"Pre:: "<<toString(in)<<std::endl;
			#endif
			FlowSet  * Pos=userSupplied->newinitialFlow();Pos->clear();
			/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);*/
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
			//如果无法处理语句，那么不提升，直接交给用户提供的方法去处理
			if(exprs==nullptr){//f'(a)
				FlowSet  * simpleFormulain=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				
				FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(in,stmt,-1);
				simpleFormulain->Union(deqResult);
				
				userSupplied->flowThrouth(stmt,-1,simpleFormulain,simpleFormulaPos);
				Pos->Union(simpleFormulaPos);
			}
			//如果可以处理语句
			else {
				vector<expr> *stmtFormulas=new vector<expr>();
				z3coding.pushAToB(exprs,stmtFormulas);
				/*vector<expr> *stmtFormulas=z3coding.boolSortFiltering(exprs);*/
				FlowSet  * nonSimpleFormulaPre=_filterNonSimpleFormula(in);
				FlowSet  * allFormulaPos=in->clone();
				
				FlowSet * simpleFormulain=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				for(unsigned i=0;i<stmtFormulas->size();i++){
					/*
					 * 处理每一个语句
					 */
					expr stmtFormula=stmtFormulas->at(i);
					#ifdef _DEBUG
						cout<<"stmtFormula:: "<<stmtFormula<<std::endl;
						/*std::string ttt=Z3_ast_to_string(c,stmtFormula);
						if(ttt=="(_AS (= (select a__prime j) (select b i)))"){
							cout<<"stmtFormula:: "<<stmtFormula<<std::endl;
						}
						cout<<"nonSimpleFormulaPre:: "<<toString(nonSimpleFormulaPre)<<std::endl;
						cout<<"simpleFormulain:: "<<toString(simpleFormulain)<<std::endl;*/
					#endif
					/*首先处理非简单性质*/
					/*处理赋值语句,判断是否索引更新语句和索引初始化语句*/
					if(z3coding.isAssignment(stmtFormula)){
						/*判断哪些性质可以专递下去*/
						/*这里应该是判断所有性质，而不是非简单性质，但是无所谓，就这样吧*/
						allFormulaPos=transferWithEnvironment(stmt,i,stmtFormula,nonSimpleFormulaPre);
						/*索引初始化语句,生成 phi性质*/
						if(isIndexInitStmt(stmt,stmtFormula.arg(0))){
							Property* tmpp=genPhi(stmt,stmtFormula.arg(0));
							if(tmpp!=nullptr){
								allFormulaPos->add(tmpp);
							}
						}
						/*索引初始化语句,更新区间*/
						else if(isIndexUpdate(stmt,stmtFormula.arg(0))){
							allFormulaPos->Union(handleInterval(stmtFormula.arg(0),nonSimpleFormulaPre,stmt,i));
						}
					}
					/*如果不是赋值语句,直接传递下去*/
					else{
						allFormulaPos=transferWithEnvironment(stmt,i,stmtFormula,nonSimpleFormulaPre);
					}
					/*全称量词性质退化称为简单性质，交给用户去处理*/
					FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(nonSimpleFormulaPre,stmt,i);
					simpleFormulain->Union(deqResult);
					userSupplied->flowThrouth(stmt,i,simpleFormulain,simpleFormulaPos);
					/*获取多索引关系,交给非简单性质*/
					FlowSet* multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(allFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					FlowSet* nonSimpleFormulaPosPlusMultiLcvRelation=allFormulaPos->clone();
					nonSimpleFormulaPosPlusMultiLcvRelation->Union(multiLcvRelation);
					/*将非简单性质提升为量词性质*/
					FlowSet* tmp=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),nonSimpleFormulaPosPlusMultiLcvRelation));
					/*消除很蠢的量词性质*/
					tmp=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp); 
					allFormulaPos=tmp->clone();
					
					/*根据全称量词性质和简单性质生成量词性质，比如
						a<b && forall x. x in interval, x<a  => forall x. x in interval, x<b*/
					FlowSet* posTmp=userSupplied->newinitialFlow();posTmp->clear();
					_generateForallFoumualBySimpleFormula(simpleFormulain,nonSimpleFormulaPre,stmt,i,posTmp);
					allFormulaPos->Union(posTmp);
					
					/*获取多索引关系,交给简单性质*/
					multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(simpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					FlowSet* simpleFormulaPosPlusMultiLcvRelation=simpleFormulaPos->clone();
					simpleFormulaPosPlusMultiLcvRelation->Union(multiLcvRelation);
					/*将简单性质提升为量词性质*/
					tmp=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),simpleFormulaPosPlusMultiLcvRelation));
					/*消除很蠢的量词性质*/
					tmp=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp); 
					simpleFormulaPos=tmp->clone();
					
					nonSimpleFormulaPre=allFormulaPos->clone();
					simpleFormulain=simpleFormulaPos->clone();
					#ifdef _DEBUG
//						cout<<"nonSimpleFormulaPos:: "<<toString(nonSimpleFormulaPos)<<std::endl;
//						cout<<"simpleFormulaPos:: "<<toString(simpleFormulaPos)<<std::endl;
					#endif
					
				}
				Pos->Union(simpleFormulaPos);
				Pos->Union(allFormulaPos);
				
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
			cout<<"----------------------------------------------------------------------------------"<<std::endl;
			#endif
		}
		void flowThrouth(const clang::Stmt* stmt,FlowSet* &in,FlowSet*&trueOut,FlowSet*&falseOut){
			#ifdef _DEBUG
			cout<<"stmt:: "<<toString(stmt)<<std::endl;
			if(toString(stmt)=="a[i] == a[j]"){
				cout<<"stmt:: "<<toString(stmt)<<std::endl;
			}
			cout<<"Pre:: "<<toString(in)<<std::endl;
			#endif


			FlowSet  * truePos=userSupplied->newinitialFlow();truePos->clear();
			FlowSet  * falsePos=userSupplied->newinitialFlow();falsePos->clear();
			/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);*/
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
			//如果无法处理语句，那么不提升，直接交给用户提供的方法去处理
			if(exprs==nullptr){//f'(a)
				FlowSet  * simpleFormulain=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaTruePos=userSupplied->newinitialFlow();simpleFormulaTruePos->clear();
				FlowSet  * simpleFormulaFalsePos=userSupplied->newinitialFlow();simpleFormulaFalsePos->clear();
				//全称量词退化
				FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(in,stmt,-1);
				simpleFormulain->Union(deqResult);
				//用户处理
				userSupplied->flowThrouth(stmt,-1,simpleFormulain,simpleFormulaTruePos,simpleFormulaFalsePos);
				truePos->Union(simpleFormulaTruePos);
				falsePos->Union(simpleFormulaFalsePos);
				//因为是条件语句，所以假设条件语句不杀死性质,所以保留老的量词性质，生成新的量词性质
				trueOut->clear();falseOut->clear();
				FlowSet* multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(truePos),
					indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
				FlowSet* truePosPlusMultiLcvRelation=truePos->clone();truePosPlusMultiLcvRelation->Union(multiLcvRelation);
				FlowSet* tmp1=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),envAnalysis->mapToStmtOut.at(stmt)->at(0),truePosPlusMultiLcvRelation));
				tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(0),tmp1);
				trueOut->Union(tmp1);
				
				//因为是条件语句，所以假设条件语句不杀死性质,所以保留老的量词性质，生成新的量词性质
				multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(falsePos),
					indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
				FlowSet* falsePosPlusMultiLcvRelation=falsePos->clone();falsePosPlusMultiLcvRelation->Union(multiLcvRelation);
				FlowSet* tmp2=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),envAnalysis->mapToStmtOut.at(stmt)->at(1),falsePosPlusMultiLcvRelation));
				tmp2=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(1),tmp2);
				falseOut->Union(tmp2);
			}
			else {
				//能够处理	
				vector<expr> *stmtFormulas=new vector<expr>();
				z3coding.pushAToB(exprs,stmtFormulas);
				/*vector<expr> *stmtFormulas=z3coding.boolSortFiltering(exprs);*/
				FlowSet  * nonSimpleFormulaIn=_filterNonSimpleFormula(in);
				FlowSet  * nonSimpleFormulaPos=in->clone();
				
				FlowSet  * simpleFormulaIn=_filterSimpleFormula(in);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				unsigned i=0;
				//首先处理非条件语句的每一个语句
				while(stmtFormulas->size()>0&&i<stmtFormulas->size()-1){
					expr stmtFormula=stmtFormulas->at(i);
					#ifdef _DEBUG
//						cout<<"stmtFormula:: "<<stmtFormula<<std::endl;
//						cout<<"nonSimpleFormulaIn:: "<<toString(nonSimpleFormulaIn)<<std::endl;
//						cout<<"simpleFormulaIn:: "<<toString(simpleFormulaIn)<<std::endl;
					#endif
					/*首先处理非简单性质*/
					/*处理赋值语句,判断是否索引更新语句和索引初始化语句*/
					if(z3coding.isAssignment(stmtFormula)){
						nonSimpleFormulaPos=transferWithEnvironment(stmt,i,stmtFormula,nonSimpleFormulaIn);
						//cout<<"nonSimpleFormulaPos1:: "<<toString(nonSimpleFormulaPos)<<std::endl;
						if(isIndexInitStmt(stmt,stmtFormula.arg(0))){
							Property* tmpp=genPhi(stmt,stmtFormula.arg(0));
							if(tmpp!=nullptr){
								nonSimpleFormulaPos->add(tmpp);
							}
						}
						else if(isIndexUpdate(stmt,stmtFormula.arg(0))){
							nonSimpleFormulaPos->Union(handleInterval(stmtFormula.arg(0),nonSimpleFormulaIn,stmt,i));
						}
						//cout<<"nonSimpleFormulaPos2:: "<<toString(nonSimpleFormulaPos)<<std::endl;
					}
					/*如果不是赋值语句,直接传递下去*/
					else{
						nonSimpleFormulaPos=transferWithEnvironment(stmt,i,stmtFormula,nonSimpleFormulaIn);
					}
					
				
					//process simpleFormulas
					/*全称量词性质退化称为简单性质，交给用户去处理*/
					FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(nonSimpleFormulaIn,stmt,i);
					simpleFormulaIn->Union(deqResult);
					userSupplied->flowThrouth(stmt,i,simpleFormulaIn,simpleFormulaPos);
					
					//gen more forall properties according to simple properties
					/*根据全称量词性质和简单性质生成量词性质，比如
						a<b && forall x. x in interval, x<a  => forall x. x in interval, x<b*/
					FlowSet* posTmp=userSupplied->newinitialFlow();posTmp->clear();
					_generateForallFoumualBySimpleFormula(simpleFormulaIn,nonSimpleFormulaIn,stmt,i,posTmp);
					nonSimpleFormulaPos->Union(posTmp);
					//cout<<"nonSimpleFormulaPos3:: "<<toString(nonSimpleFormulaPos)<<std::endl;
					/*获取多索引关系,交给简单性质,提升简单性质到量词性质*/
					FlowSet* multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(simpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					FlowSet* simpleFormulaPosPlusMultiLcvRelation=simpleFormulaPos->clone();
					simpleFormulaPosPlusMultiLcvRelation->Union(multiLcvRelation);
					FlowSet* tmp1=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),simpleFormulaPosPlusMultiLcvRelation));
							
					tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp1);
					simpleFormulaPos=tmp1->clone();
					
					/*获取多索引关系,交给非简单性质,提升简单性质到量词性质*/
					multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(nonSimpleFormulaPos),
						indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),multiIndexesRelationAnalysis->mapToStmtExprOut.at(stmt)->at(i));
					FlowSet* nonSimpleFormulaPosPlusMultiLcvRelation=nonSimpleFormulaPos->clone();
					nonSimpleFormulaPosPlusMultiLcvRelation->Union(multiLcvRelation);
					tmp1=reduce(genQ(indexAnalysis->mapToStmtExprOut.at(stmt)->at(i),
							envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),nonSimpleFormulaPosPlusMultiLcvRelation));
					//消除很傻的结果
					tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtExprOut.at(stmt)->at(0)->at(i),tmp1);
					nonSimpleFormulaPos=tmp1->clone();
					//cout<<"nonSimpleFormulaPos4:: "<<toString(nonSimpleFormulaPos)<<std::endl;
					
					simpleFormulaIn=simpleFormulaPos->clone();
					nonSimpleFormulaIn=nonSimpleFormulaPos->clone();
					i++;
					#ifdef _DEBUG
//						cout<<"nonSimpleFormulaPos:: "<<toString(nonSimpleFormulaPos)<<std::endl;
//						cout<<"simpleFormulaPos:: "<<toString(simpleFormulaPos)<<std::endl;
					#endif
				}
				
				FlowSet  * nonSimpleFormulaTruePos=nonSimpleFormulaIn->clone();
				FlowSet  * nonSimpleFormulaFalsePos=nonSimpleFormulaIn->clone();
				
				FlowSet  * simpleFormulaTruePos=simpleFormulaIn->clone();
				FlowSet  * simpleFormulaFalsePos=simpleFormulaIn->clone();
				FlowSet  * simpleFormulaTruePostmp=simpleFormulaTruePos->clone();
				FlowSet  * simpleFormulaFalsePostmp=simpleFormulaFalsePos->clone();
				//处理条件语句,它是stmtStmts最后一个语句
				if(stmtFormulas->size()>0&&i==stmtFormulas->size()-1){
					#ifdef _DEBUG
						cout<<"stmtFormula:: "<<stmtFormulas->at(i)<<std::endl;
//						cout<<"nonSimpleFormulaIn:: "<<toString(nonSimpleFormulaIn)<<std::endl;
//						cout<<"simpleFormulaIn:: "<<toString(simpleFormulaIn)<<std::endl;
					#endif
					
					//性质传递下去
					nonSimpleFormulaTruePos=transferWithEnvironment(stmt,i,stmtFormulas->at(i),nonSimpleFormulaIn);
					nonSimpleFormulaFalsePos=nonSimpleFormulaTruePos->clone();
					//全称量词退化为简单性质，交给用户处理
					FlowSet  * deqResult=forAllFormulaInstantiatedToSimpleFormula(nonSimpleFormulaIn,stmt,i);
					simpleFormulaIn->Union(deqResult);
					userSupplied->flowThrouth(stmt,i,simpleFormulaIn,simpleFormulaTruePos,simpleFormulaFalsePos);
					#ifdef _DEBUG
//						cout<<"nonSimpleFormulaTruePos:: "<<toString(nonSimpleFormulaTruePos)<<std::endl;
//						cout<<"nonSimpleFormulaFalsePos:: "<<toString(nonSimpleFormulaFalsePos)<<std::endl;
//						cout<<"simpleFormulaTruePos:: "<<toString(simpleFormulaTruePos)<<std::endl;
//						cout<<"simpleFormulaFalsePos:: "<<toString(simpleFormulaFalsePos)<<std::endl;
					#endif
					
					//gen more forall properties according to simple properties
					/*根据全称量词性质和简单性质生成量词性质，比如
						a<b && forall x. x in interval, x<a  => forall x. x in interval, x<b*/
					FlowSet* trueTmp=userSupplied->newinitialFlow();trueTmp->clear();
					FlowSet* falseTmp=userSupplied->newinitialFlow();falseTmp->clear();
					_generateForallFoumualBySimpleFormula(simpleFormulaIn,nonSimpleFormulaIn,stmt,i,trueTmp,falseTmp);
					
					nonSimpleFormulaTruePos->Union(trueTmp);
					nonSimpleFormulaFalsePos->Union(falseTmp);										
				}
				//如果根据当前状态不能走当前路径，设置输出的数据流值为全集
				if(stmtFormulas->size()>0&&i==stmtFormulas->size()-1&&
					isFeasible(simpleFormulaTruePostmp,stmtFormulas->at(i))){
					trueOut=userSupplied->newinitialFlow();//全集
				}
				else{
					truePos->Union(simpleFormulaTruePos);
					//根据条件性质，精化nonSimpleFormulaTruePos中的or公式
					if(stmtFormulas->size()>0&&i==stmtFormulas->size()-1&&DISJUNCTIONK>0){
						nonSimpleFormulaTruePos=refine(nonSimpleFormulaTruePos,stmtFormulas->at(i));
					}
					truePos->Union(nonSimpleFormulaTruePos);
					trueOut->clear();
					/*获取多索引关系,在true分支中提升性质到量词性质*/
					FlowSet* multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(truePos),
							indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
					FlowSet* truePosPlusmultiLcvRelation=truePos->clone();truePosPlusmultiLcvRelation->Union(multiLcvRelation);
					FlowSet* tmp1=reduce(genQ(indexAnalysis->mapToStmtOut.at(stmt),
							envAnalysis->mapToStmtOut.at(stmt)->at(0),truePosPlusmultiLcvRelation));
					
					//cout<<toString(tmp1)<<std::endl;
					//消除很傻的结果
					tmp1=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(0),tmp1);
					//cout<<toString(tmp1)<<std::endl;
					trueOut->Union(tmp1);
				}
				if(stmtFormulas->size()>0&&i==stmtFormulas->size()-1&&
					isFeasible(simpleFormulaFalsePostmp,!stmtFormulas->at(i))){
					falseOut=userSupplied->newinitialFlow();//全集
				}
				else{
					falsePos->Union(simpleFormulaFalsePos);
					if(stmtFormulas->size()>0&&i==stmtFormulas->size()-1&&DISJUNCTIONK>0){
						nonSimpleFormulaFalsePos=refine(nonSimpleFormulaFalsePos,!stmtFormulas->at(i));
					}
					//根据条件性质，精化nonSimpleFormulaFalsePos中的or公式
					falsePos->Union(nonSimpleFormulaFalsePos);
					//cout<<"1111::"<<toString(nonSimpleFormulaFalsePos)<<std::endl;
					falseOut->clear();
					/*获取多索引关系,在false分支中提升性质到量词性质*/
					FlowSet* multiLcvRelation=genSimPlePriopertyByMultiRelation(_filterSimpleFormula(falsePos),
							indexAnalysis->mapToStmtOut.at(stmt),multiIndexesRelationAnalysis->mapToStmtOut.at(stmt));
					FlowSet* falsePosPlusMultiLcvRelation=falsePos->clone();falsePosPlusMultiLcvRelation->Union(multiLcvRelation);
					//cout<<"2222::"<<toString(falsePosPlusMultiLcvRelation)<<std::endl;
					FlowSet* ttttt=genQ(indexAnalysis->mapToStmtOut.at(stmt),
							envAnalysis->mapToStmtOut.at(stmt)->at(1),falsePosPlusMultiLcvRelation);
					//cout<<"3333::"<<toString(ttttt)<<std::endl;
					FlowSet* tmp2=reduce(ttttt);
					//cout<<"4444::"<<toString(tmp2)<<std::endl;
					/*cout<<"-----------false env--------------"<<std::endl;
					cout<<toString(envAnalysis->mapToStmtOut.at(stmt)->at(1))<<std::endl;
					*/
					//消除很傻的结果
					tmp2=eliminateUnpossibleForAllOrPhiFormulas(envAnalysis->mapToStmtOut.at(stmt)->at(1),tmp2);
					//cout<<"5555::"<<toString(tmp2)<<std::endl;
					falseOut->Union(tmp2);
				}
			}
			
			

#ifdef _DEBUG
			cout<<"truePos:: "<<toString(trueOut)<<std::endl;
			cout<<"falsePos:: "<<toString(falseOut)<<std::endl;
			cout<<"----------------------------------------------------------------------------------"<<std::endl;
#endif
		}
		bool isFeasible(FlowSet  * in, expr cond){
			auto ingore=toExprs(in);
			auto invec=getAllSimpleFormula(ingore.get());
			if(z3coding.satisfy(invec.get(),cond)==check_result::unsat){
				return false;
			}
			return false;
		}
		/**
		 * @brief sometimes, quantified property need generate more universal 
		 * 			quantifier properties according to simple property
		 * 		∀x.x ∈ [0,1,i),max>=A[x] and max<A[i] generates  implies ∀x.x ∈ [0,1,i),A[i]>=A[x]
		 * @param in
		 * @param stmt
		 * @return 
		 */
		unique_ptr<vector<expr>> __forAllFormulaDegeneratedToSimpleFormula(expr forAllFormula,const clang::Stmt* clangstmt,int count
					,FlowSet* simpleFormulas){
			unique_ptr<vector<expr>>  result(new vector<expr>());
			vector<expr>  relatedMemoryUnits;
			unique_ptr<vector<expr>> tmp;
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
			add(tmp.get(),&relatedMemoryUnits);
			/*auto simpleFormulasExprs=toExprs(simpleFormulas);
			for(expr e:*simpleFormulasExprs){
				tmp=z3coding.getMemoryUnits(e);
				add(tmp.get(),&relatedMemoryUnits);
			}*/
			
			expr simpleFormulaOfForAllFormula=getForallFormulaInnerSimpleFormula(forAllFormula);
			auto simpleFormulaUnits=z3coding.getMemoryUnits(simpleFormulaOfForAllFormula);
			//cout<<"forAllFormula:"<<forAllFormula<<std::endl;
			for(expr relatedMemoryUnit:relatedMemoryUnits){
				//cout<<"relatedMemoryUnit:"<<relatedMemoryUnit<<std::endl;
				if(z3coding.isIn(relatedMemoryUnit,simpleFormulaUnits.get())){
					result->push_back(simpleFormulaOfForAllFormula);
					break;
				}
			}
			#ifdef _DEBUG
//			cout<<"deq result::"<< toString(result)<<std::endl;
			#endif
			return result;
		}
		unique_ptr<vector<expr>> __getQuantifierProperties(vector<expr>* quantifiers,vector<expr>* formulas){
			unique_ptr<vector<expr>> result(new vector<expr>());
			for(expr f:*formulas){
				auto cons=z3coding.getConsts(f);
				bool isInFlag=true;
				for(expr q:*quantifiers){
					if(!z3coding.isIn(q,cons.get())){
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
		unique_ptr<vector<expr>> __diff(vector<expr>* A,vector<expr>* B){
			unique_ptr<vector<expr>> result(new vector<expr>());
			for(expr a:*A){
				if(!z3coding.isIn(a,B)){
					result->push_back(a);
				}
			}
			return result;
		}
		unique_ptr<vector<expr>> __genNewForAllFormula(expr forAllFormula,vector<expr>* newquantifierProperties){
			unique_ptr<vector<expr>> result(new vector<expr>());
			auto quantifiers=z3coding.getAllQuantifier(forAllFormula);
			auto stepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
			auto quantifierBeginFormulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
			auto quantifierEndFormulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
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
		
		//纯forall性质指，中间没有存在量词,全部是全称量词
		unique_ptr<vector<expr>> getAllPureForallFormulas(FlowSet* in){
			unique_ptr<vector<expr>> ret(new vector<expr>());
			auto invec=toExprs(in);
			for(expr e:*invec){
				if(isPureForallFormula(e)){
					ret->push_back(e);
				}
			}
			return ret;
		}
		void _generateForallFoumualBySimpleFormula(FlowSet  * simpleFormulain,FlowSet* forAllFormulasIn, 
				const clang::Stmt* stmt,int count,FlowSet * &out){
			vector<expr> result;
			//vector<expr>* forAllFormulas=getAllForallFormulas(forAllFormulasIn);
			auto forAllFormulas=getAllPureForallFormulas(forAllFormulasIn);
			
			//cout<<"simpleFormulain::"<<toString(simpleFormulain)<<std::endl;
			for(expr forallFormula:*forAllFormulas){
				//cout<<"forAllFormulasIn::"<<z3coding.toString(forallFormula)<<std::endl;
				auto quantifiers=z3coding.getAllQuantifier(forallFormula);
				
				auto deqResult=__forAllFormulaDegeneratedToSimpleFormula(forallFormula,stmt,count,simpleFormulain);
				FlowSet  * simpleFormulaPos=userSupplied->newinitialFlow();simpleFormulaPos->clear();
				FlowSet* tmpSimpleIn=simpleFormulain->clone();
				tmpSimpleIn->Union(toFlowSet(deqResult.get()));
				//cout<<toString(tmpSimpleIn)<<std::endl;
				userSupplied->flowThrouth(stmt,count,tmpSimpleIn,simpleFormulaPos);
				
				
				auto ingore=toExprs(simpleFormulaPos);
				auto quantifierProperties=__getQuantifierProperties(quantifiers.get(),ingore.get());
				auto newquantifierProperties=__diff(quantifierProperties.get(),deqResult.get());
				auto newforallFormulas=__genNewForAllFormula(forallFormula,newquantifierProperties.get());
				
				z3coding.pushAToB(newforallFormulas.get(),&result);
			}
			out->Union(toFlowSet(&result));
		}
		
		void _generateForallFoumualBySimpleFormula(FlowSet* simpleFormulain,FlowSet* forAllFormulasIn, 
				const clang::Stmt* stmt,int count,FlowSet* &truePos,FlowSet* &falsePos){
					
			vector<expr> trueresult;
			vector<expr> falseresult;
			//vector<expr>* forAllFormulas=getAllForallFormulas(forAllFormulasIn);
			auto forAllFormulas=getAllPureForallFormulas(forAllFormulasIn);
			for(expr forallFormula:*forAllFormulas){
				auto quantifiers=z3coding.getAllQuantifier(forallFormula);
				auto deqResult=__forAllFormulaDegeneratedToSimpleFormula(forallFormula,stmt,count,simpleFormulain);
				FlowSet  * simpleTruePos=userSupplied->newinitialFlow();simpleTruePos->clear();
				FlowSet  * simpleFalsePos=userSupplied->newinitialFlow();simpleFalsePos->clear();
				FlowSet* tmpSimpleIn=simpleFormulain->clone();
				tmpSimpleIn->Union(toFlowSet(deqResult.get()));
				userSupplied->flowThrouth(stmt,count,tmpSimpleIn,simpleTruePos,simpleFalsePos);
				auto ignore1=toExprs(simpleTruePos);
				auto quantifierPropertiesInTruePos=__getQuantifierProperties(quantifiers.get(),ignore1.get());
				auto ignore2=toExprs(simpleFalsePos);
				auto quantifierPropertiesInFalsePos=__getQuantifierProperties(quantifiers.get(),ignore2.get());
				auto newquantifierPropertiesInTruePos=__diff(quantifierPropertiesInTruePos.get(),deqResult.get());
				auto newforallFormulasInTruePos=__genNewForAllFormula(forallFormula,newquantifierPropertiesInTruePos.get());
				auto newquantifierPropertiesInFalsePos=__diff(quantifierPropertiesInFalsePos.get(),deqResult.get());
				auto newforallFormulasInFalsePos=__genNewForAllFormula(forallFormula,newquantifierPropertiesInFalsePos.get());
				z3coding.pushAToB(newforallFormulasInTruePos.get(),&trueresult);
				z3coding.pushAToB(newforallFormulasInFalsePos.get(),&falseresult);
			}
			truePos->Union(toFlowSet(&trueresult));
			falsePos->Union(toFlowSet(&falseresult));
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
		FlowSet * forAllFormulaInstantiatedToSimpleFormula(FlowSet * in,const clang::Stmt* stmt,int count){
			vector<expr>  result;
			
			/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);*/
			vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
			
			if(exprs==nullptr||exprs->size()==0){
				return toFlowSet(&result);
			}
			vector<expr> *stmtFormulas=new vector<expr>();
			z3coding.pushAToB(exprs,stmtFormulas);
			auto forAllFormulas=getAllPureForallFormulas(in);
			vector<expr>  arrayAcesses;
			for(expr e:*stmtFormulas){
				unique_ptr<vector<expr>> tmp;
				if(e.is_bool()&&z3coding.isAssignment(e)){
					e=e.arg(0);
					tmp=z3coding.getArrayAcessMemoryUnits(e.arg(1));
				}
				else{
					tmp=z3coding.getArrayAcessMemoryUnits(e);
				}
				add(tmp.get(),&arrayAcesses);
			}
//			cout<<"arrayAcesses::"<<toString(arrayAcesses)<<std::endl;
//			cout<<"arrayAcesses_size::"<<arrayAcesses->size()<<std::endl;
//			cout<<"forAllFormulas_size::"<<forAllFormulas->size()<<std::endl;
			for(expr arrayAcessMemoryUnit:arrayAcesses){
				for(expr forAllFormula:*forAllFormulas){
					FlowSet* env=getEnvironmentBeforStmt(stmt);
//					cout<<"arrayAcessMemoryUnit::"<<arrayAcessMemoryUnit<<std::endl;
					auto mustIsInExprs=mustMemoryUnitIsInForAllFormula(env,arrayAcessMemoryUnit,forAllFormula,stmt,count);
					if(mustIsInExprs->size()>0){
						expr simpleFormulaOfForAllFormula=getForallFormulaInnerSimpleFormula(forAllFormula);
						auto insFormulas=instantiation(arrayAcessMemoryUnit,mustIsInExprs.get(),forAllFormula);
						add(insFormulas.get(),&result);
					}
				}
			}
			
			#ifdef _DEBUG
//			cout<<"deq result::"<< toString(result)<<std::endl;
			#endif
			return toFlowSet(&result);
		}
		void add(vector<expr>* A,vector<expr>* B){
			for(expr e: *A){
				if(!z3coding.isIn(e,B)){
					B->push_back(e);
				}
			}
		}
		unique_ptr<vector<expr>> instantiation(expr arrayAcessMemoryUnit,vector<expr>* quantifierArrayAcesses,expr forAllFormula){
			unique_ptr<vector<expr>> result(new vector<expr>());
			/*
			 * * deg limit
			 *	 p: p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)],v1,...,vg)
			 *			量词x1,...,xn只出现在A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]中
			 *		或者f=x，A1[f1(x1,...,xn)]...[f1m (x1,...,xn)]= A1[x1]...[xn]
			 */
			auto qualifiers=z3coding.getAllQuantifier(forAllFormula);
			expr simpleFormulaOfForAllFormula=getForallFormulaInnerSimpleFormula(forAllFormula);
			for(expr quantifierArrayAcess:*quantifierArrayAcesses){
				if(isDeqLimit1(qualifiers.get(),simpleFormulaOfForAllFormula)){
					result->push_back(z3coding.substitute(simpleFormulaOfForAllFormula,quantifierArrayAcess,arrayAcessMemoryUnit));
				}
				else if(isDeqLimit2(quantifierArrayAcess)){
					auto quantifierArrayAcessIdxes=z3coding.getArrayAcessIdxes(quantifierArrayAcess);
					auto arrayAcessIdxes=z3coding.getArrayAcessIdxes(arrayAcessMemoryUnit);
					if(quantifierArrayAcessIdxes->size()!=arrayAcessIdxes->size()){
						cerr<<"LiftAnalysis_FeasiblePath::instantiation::something is wrong!"<<std::endl;
						return unique_ptr<vector<expr>>(new vector<expr>()); 
					}
					expr insResult=simpleFormulaOfForAllFormula;
					for(unsigned i=0;i<quantifierArrayAcessIdxes->size();i++){
						expr quantifierKIdex=quantifierArrayAcessIdxes->at(i);
						expr arrayAcessKIdex=arrayAcessIdxes->at(i);
						insResult=z3coding.substitute(insResult,quantifierKIdex,arrayAcessKIdex);
					}
					if(!z3coding.isIn(insResult,result.get())){
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
			auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(simpleFormula);
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
			auto idxes=z3coding.getArrayAcessIdxes(quantifierArrayAcess);
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
unique_ptr<vector<expr>> mustMemoryUnitIsInForAllFormula(FlowSet* env,expr memoryunit,expr forAllFormula,const clang::Stmt* clangStmt,int count){
	/*
	 * ∀x1.x1 ∈ [e11,c1,e12),... ∀xn.xn ∈ [en1,cn,en2), 
	 * 	p(A1[f1(x1,...,xn)]...[f1m (x1,...,xn)], ...,Ak1[f1(x1,...,xn)] ...[fkh (x1,..., xn)], ff1(x1,...,xn),..., ffg(x1,...,xn))
	 * 
	 * 
	 * env ∧t=m ∧ e1=f1(x1,...,xn) ∧… ∧ em=f1m(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2) 
	 * ∨… ∨
	 * env ∧t=h ∧ e1=fk1(x1,...,xn) ∧… ∧ eh=fkm(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2)
	 */ 
	unique_ptr<vector<expr>> result(new vector<expr>());
	expr memoryunitbase=z3coding.getArrayBase(memoryunit);
	unsigned  memoryunitDim=z3coding.getArrayAcessDimension(memoryunit);
	auto allquantifiers=z3coding.getAllQuantifier(forAllFormula);
	auto allstepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
	auto allbeginformulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
	auto allendformulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
	auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(forAllFormula);
	for(expr arrayAcess:*arrayAcesses){
		expr arrayAcessBase=z3coding.getArrayBase(arrayAcess);
		if(mayMemoryUnitIsIn(env,memoryunitbase,arrayAcessBase,clangStmt,count)){
		/*env ∧t=m ∧ e1=f1(x1,...,xn) ∧… ∧ em=f1m(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2) 
		*∨… ∨
		* env ∧t=h ∧ e1=fk1(x1,...,xn) ∧… ∧ eh=fkm(x1,...,xn) ⇒ x1 ∈ [e11,c1,e12),...,xn ∈ [en1,cn,en2)
		*/ 
			unsigned arrayAcessDim=z3coding.getArrayAcessDimension(arrayAcess);
			if(arrayAcessDim!=memoryunitDim){return unique_ptr<vector<expr>>();}
			vector<expr>  Pres;
			auto memoryunitIdxes=z3coding.getArrayAcessIdxes(memoryunit);
			auto arrayAcessIdxes=z3coding.getArrayAcessIdxes(arrayAcess);
			for(unsigned i=0;i<arrayAcessDim;i++){
				Pres.push_back(memoryunitIdxes->at(i)==arrayAcessIdxes->at(i));
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
			auto expr_env=toExprs(env);
			z3coding.pushAToB(expr_env.get(),&Pres);
//			cout<<"Pres::"<<toString(Pres)<<std::endl;
//			cout<<"quantifierFormulaAssert::"<<quantifierFormulaAssert<<std::endl;
			if(z3coding.satisfy(&Pres,c.bool_val(true))==check_result::sat
			&&proved_result::proved==z3coding.prove(&Pres,quantifierFormulaAssert)){
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
		bool isPureForallFormula(expr forallFormula){
			expr tmp=forallFormula;
			while(z3coding.isForAllFormula(tmp)){
				tmp=z3coding.getQuantifierFormulaBody(tmp);
			}
			Formula tmpf(tmp);
			if(userSupplied->isSimpleProperty(&tmpf)){
				return true;
			}
			return false;
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
				cerr<<"LiftAnalysis_FeasiblePath::occurTime::something is wrong!"<<std::endl;
				return 0;
			}
			
		}
		
		FlowSet* getEnvironmentBeforStmt(const clang::Stmt *clangStmt){
			//cout<<"map size::"<<envAnalysis->mapToStmtIn.size()<<std::endl;
			FlowSet* in=envAnalysis->mapToStmtIn.at(clangStmt);
			return in;
		}
		FlowSet* transfer(FlowSet  *Pre,expr stmt,FlowSet  *in,const clang::Stmt *clangStmt,int count){
			FlowSet* result=userSupplied->newinitialFlow();result->clear();
			auto invec=in->toVector();
			if(z3coding.isAssignment(stmt)){
				//cout<<stmt<<std::endl;
				stmt=stmt.arg(0);
				expr left=stmt.arg(0);
				for(Property *p:*invec){
					Formula *f=(Formula *)p;
					//cout<<"z3coding.unprimedDecline(left):"<<z3coding.unprimedDecline(left)<<", f->formula: "<<f->formula<<std::endl;
					if(!mayMemoryUnitIsInFormula(Pre,z3coding.unprimedDecline(left),f->formula,clangStmt,count)){
						result->add(new Formula(f->formula));
					}
				}
			}
			else{
				result->Union(in);
			}
			return result;
		}

		FlowSet* transferWithEnvironment(const clang::Stmt *clangStmt,int count,expr stmt,FlowSet  *in){
			return transfer(getEnvironmentBeforStmt(clangStmt),stmt,in,clangStmt,count);
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
		
		Formula* __handleIntervalProcess1(expr forallexpr,expr index,const clang::Stmt *clangStmt,int count){
			expr quantifier=z3coding.getQuantifier(forallexpr);
			expr step=z3coding.getForAllFormulaStep(forallexpr);
			expr stepFormula=z3coding.getForAllFormulaStepFormula(forallexpr);
			expr quantifierBegin=z3coding.getForAllFormulaBegin(forallexpr);
			expr quantifierEnd=z3coding.getForAllFormulaEnd(forallexpr);
			expr quantifierBeginFormula=z3coding.getForAllFormulaBeginFormula(forallexpr);
			expr quantifierEndFormula=z3coding.getForAllFormulaEndFormula(forallexpr);
			expr quantifierExtendFormula=z3coding.getForAllFormulaExtendFormula(forallexpr);
			expr body=z3coding.getQuantifierFormulaBody(forallexpr);
			if(mu.isGtZero(step)){//>
				if(z3coding.equal(index+step,quantifierEnd)&&!mu.mayMemoryUnitIsInFormula(index,body,clangStmt,count)
				 &&!mu.mayMemoryUnitIsInFormula(index,quantifierBegin,clangStmt,count)){
					Formula* tmp=new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,quantifier<index,
									stepFormula,body));
					return tmp;
				}
				else if(z3coding.equal(index,quantifierEnd)&&!mu.mayMemoryUnitIsInFormula(index,body,clangStmt,count)
					&&!mu.mayMemoryUnitIsInFormula(index,quantifierBegin,clangStmt,count)){
					return new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,
									quantifier<index-step,stepFormula,body));
				}
			}
			else if(mu.isLtZero(step)){//<
				if(z3coding.equal(index+step,quantifierBegin)&&!mu.mayMemoryUnitIsInFormula(index,body,clangStmt,count)
					&&!mu.mayMemoryUnitIsInFormula(index,quantifierEnd,clangStmt,count)){
					return new Formula(z3coding.constructForAllFormula(quantifier,index<quantifier,quantifierEndFormula,
									stepFormula,body));
				}
				else if(z3coding.equal(index,quantifierBegin)&&!mu.mayMemoryUnitIsInFormula(index,body,clangStmt,count)
					&&!mu.mayMemoryUnitIsInFormula(index,quantifierEnd,clangStmt,count)){
					return new Formula(z3coding.constructForAllFormula(quantifier,index-step<quantifier,quantifierEndFormula,
									stepFormula,body));
				}
			}
			return nullptr;
		}
		Formula* handleInterval_Process_OrForallFormula(expr orexpr,expr index,const clang::Stmt *clangStmt,int count){
			//split  
			//get lcv Relevant
			//lift
			auto orFormulas=z3coding.splitOrFormulas(orexpr);
			vector<expr> relevantOrFormulas;
			vector<expr> unrelevantOrFormulas;
			for(expr e:*orFormulas){
				auto cons=z3coding.getConsts(e);
				if(z3coding.isIn(index,cons.get())){
					if(z3coding.isForAllFormula(e)){
						relevantOrFormulas.push_back(e);
					}
					else{
						return nullptr;
					}
				}
				else{
					unrelevantOrFormulas.push_back(e);
				}
			}
			vector<expr> relevantOrFormulaRets;
			for(expr e:relevantOrFormulas){
				Formula* f= __handleIntervalProcess1(e,index,clangStmt,count);
				if(f==nullptr){
					return nullptr;
				}
				else{
					relevantOrFormulaRets.push_back(f->formula);
					delete f;
				}
			}
			expr unrelevantOrFormula=getOrFormulas(&unrelevantOrFormulas);
			expr relevantOrFormula=getOrFormulas(&relevantOrFormulaRets);
			if(z3coding.checkError(relevantOrFormula)){
				return nullptr;
			}
			else if(z3coding.checkError(unrelevantOrFormula)){
				return new Formula(relevantOrFormula);
			}
			else{
				return new Formula(unrelevantOrFormula||relevantOrFormula);
			}
		}
		FlowSet  * handleInterval(expr updateStmt,FlowSet * in,const clang::Stmt *clangStmt,int count){
			FlowSet * result=userSupplied->newinitialFlow();result->clear();
			expr left=updateStmt.arg(0);
			expr index=z3coding.unprimedDecline(left);
			auto invec=in->toVector();
			for(Property* p:*invec){
				Formula *f=(Formula*)p;
				//cout<<z3coding.toString(f->formula) <<std::endl;
				if(z3coding.isForAllFormula(f->formula)){
					Formula* r=__handleIntervalProcess1(f->formula,index,clangStmt,count);
					if(r!=nullptr){
						result->add(r);
					}
				}
				else if(containForallFormula(f->formula)){
					Formula* r=handleInterval_Process_OrForallFormula(f->formula,index,clangStmt,count);
					if(r!=nullptr){
						result->add(r);
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
						if(z3coding.equal(index+step,phiEnd)&&!mu.mayMemoryUnitIsInFormula(index,phiBegin,clangStmt,count)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,quantifier<index,stepFormula)));
						}
						else if(z3coding.equal(index,phiEnd)&&!mu.mayMemoryUnitIsInFormula(index,phiBegin,clangStmt,count)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,quantifier<index-step,stepFormula)));
						}
					}
					else if(mu.isLtZero(step)){//<
						if(z3coding.equal(index+step,phiBegin)&&!mu.mayMemoryUnitIsInFormula(index,phiEnd,clangStmt,count)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,index<quantifier,phiEndFormula,stepFormula)));
						}
						else if(z3coding.equal(index,phiBegin)&&!mu.mayMemoryUnitIsInFormula(index,phiEnd,clangStmt,count)){
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,index-step<quantifier,phiEndFormula,stepFormula)));
						}
					}
				}
			}
			return result;
		}

		FlowSet * genQ(FlowSet* indexEnv,FlowSet* env,FlowSet  * in){
			FlowSet * result=userSupplied->newinitialFlow();result->clear();
			//GenEQ在GenFQ之前，这会让生成的EQ性质在省城FQ性质，但是不会不会让FQ变成EQ，
			//这虽然会漏掉一些EQ性质，但是问题不大 
			result->Union(genEQ(indexEnv,env,in));
			result->Union(genFQ(indexEnv,env,result));
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
	//result->Union(closurePhiWithEnvironment(env,result));
	//cout<<"5555"<<toString(result)<<std::endl;
	result->Union(update(indexEnv,result));
	//cout<<"6666"<<toString(result)<<std::endl;
	result->Union(updateDef(indexEnv,result));
	//cout<<"7777"<<toString(result)<<std::endl;
	result->Union(generalizeUpdateForAll(indexEnv,result));
	return result;
}
unique_ptr<vector<AtomVariabla *>> getAllIndex(FlowSet* indexEnv){
	unique_ptr<vector<AtomVariabla *>> ret(new vector<AtomVariabla *>());
	FlowSet* out=indexEnv;
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
	for(Property* p: vlsOut->elements){
		AtomVariabla * av=(AtomVariabla *)p;
		if(av->hasStep()){
			ret->push_back(av);
		}
	}
	return ret;
}


/**
 * @brief for any S ∈ 2ProperP, GenEQ(S) =
			S ∪ {∃x.x ∈ [initi,c,e1),ψ(e2[f1(x)])} 		if (1) holds
			S ∪ {∃x.x ∈ [initi,c,e1],ψ(e2[f1(x)])} 		if (2) holds
			S 					otherwise


			i is index ∧ ψ(e2[f1(i)]) ∈ a ∧ i < e1 ∈ E	 	(1)
			i is index ∧ ψ(e2[f1(i)]) ∈ a ∧ i < e1 ∈ E	 	(2)
			寻找这样的索引i,索引i的步长大于0，并且i<e在环境中,或者i的步长小于0，并且i>e在环境中
			寻找索引i在数组表达式和解引用表达式中的性质p
			提升p为存在量词，
				如果步长大于0，并且i<e，存在量词为 forall k. k in [initi,c,e),p[k/i]
				如果步长大于0，并且i<=e，存在量词为 forall k. k in [initi,c,e],p[k/i]
				如果步长小于0，并且i>e，存在量词为 forall k. k in [initi,c,e),p[k/i]
				如果步长小于0，并且i>=e，存在量词为 forall k. k in [initi,c,e],p[k/i]
 * @param indexEnv
 * @param env
 * @param in
 * @return 
 */
 FlowSet  * genEQ(FlowSet* indexEnv,FlowSet* env,FlowSet  * in){
	FlowSet* result=in->clone();
	//寻找这样的索引i,索引i的步长大于0，并且i<e在环境中,或者i的步长小于0，并且i>e在环境中
	auto indexes=getAllIndex(indexEnv);
	for(AtomVariabla* indexVar:*indexes){
		auto indexEnvProperties=getIndexEnvProperties(indexVar,env);
		if(indexEnvProperties->size()>0){
			auto existProperties=generalize_liftToEQWithArrayAcess(indexEnvProperties.get(),indexVar,in,
				&LiftAnalysis_FeasiblePath::getPropertiesRelevantArrayAcessWithIndex);
			auto tmp=generalize_liftToEQWithArrayAcess(indexEnvProperties.get(),indexVar,in,
				&LiftAnalysis_FeasiblePath::getPropertiesRelevantDefWithIndex);
			z3coding.pushAToB(tmp.get(),existProperties.get());	
			result->Union(toFlowSet(existProperties.get()));
		}
	}
	return result;
}
unique_ptr<vector<expr>> generalize_liftToEQWithArrayAcess(vector<expr>* indexEnvProperties,AtomVariabla* indexVar,FlowSet  * in,
			unique_ptr<vector<expr>> (LiftAnalysis_FeasiblePath::*pfun_GetPropertiesRelevantWithIndex)(expr, FlowSet*)){
	try{
		unique_ptr<vector<expr>> ret(new vector<expr>());
		expr index=indexVar->scalaVarz3coding;
		expr init=indexVar->initz3coding;
		expr step=indexVar->stepz3coding;
		bool stepLe0=mu.isLtZero(indexVar->stepz3coding);
		bool stepGe0=mu.isGtZero(indexVar->stepz3coding);
		auto relevantProperties=(this->*pfun_GetPropertiesRelevantWithIndex)(index,in);
		for(expr p:*relevantProperties){
			//cout<<"lift "<< p <<" to EQ"<<std::endl;
			//当性质是or性质时，不允许量化它
			if(z3coding.isOrFormula(p)){
				continue;
			}
			for(expr indexEnv:*indexEnvProperties){
				expr end(c);
				if(stepGe0){
					end=indexEnv.arg(1);		
				}
				else if(stepLe0){
					end=indexEnv.arg(0);		
				}
				else{
					cerr<<"LiftAnalysis_FeasiblePath::liftToEQWithArrayAcess::something is wrong!"<<std::endl;
					return unique_ptr<vector<expr>>();
				}
				auto cons=z3coding.getConstsWithQuantifier(p);
				auto initcons=z3coding.getConstsWithQuantifier(init);
				auto endcons=z3coding.getConstsWithQuantifier(end);
				auto stepcons=z3coding.getConstsWithQuantifier(step);
				z3coding.pushAToB(initcons.get(),cons.get());
				z3coding.pushAToB(endcons.get(),cons.get());
				z3coding.pushAToB(stepcons.get(),cons.get());
				expr quantifier=constructNewQuantifierName(cons.get());
				expr body=z3coding.substitute(p,index,quantifier);
				expr quantifierBeginFormula(c);
				expr quantifierEndFormula(c);
				if(stepGe0){
					quantifierBeginFormula=init<=quantifier;
					if(Z3_is_eq_func_decl(c,indexEnv.decl(),z3coding.LtDecl)){
						quantifierEndFormula=quantifier<end;
					}
					else{
						quantifierEndFormula=quantifier<=end;
					}
					
				}
				else if(stepLe0){
					quantifierEndFormula=quantifier<=init;
					if(Z3_is_eq_func_decl(c,indexEnv.decl(),z3coding.LtDecl)){
						quantifierBeginFormula=end<quantifier;
					}
					else{
						quantifierBeginFormula=end<=quantifier;
					}
				}
				
				expr existFormula=z3coding.constructExistFormula_step(quantifier,quantifierBeginFormula,quantifierEndFormula,
						step,init,body);
				//cout<<"EQ is: "<<z3coding.toString(existFormula)<<std::endl;
				ret->push_back(existFormula);
			}			
			
		}
		return ret;
	}
	catch(z3::exception e){
		cout<<"something is wrong!"<<std::endl;
		cout<<e.msg()<<std::endl;
		throw(e);
	}
}

//寻找这样的索引i,索引i的步长大于0，并且i<e在环境中,或者i的步长小于0，并且i>e在环境中
unique_ptr<vector<expr>> getIndexEnvProperties(AtomVariabla* indexVar,FlowSet* env){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	FlowSet* out=env;
	bool stepLe0=mu.isLtZero(indexVar->stepz3coding);
	bool stepGe0=mu.isGtZero(indexVar->stepz3coding);
	ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
	for(Property* p: vlsOut->elements){
		Formula * f=(Formula *)p;
		expr envf=z3coding.eliminateNotInSimpleFormula(f->formula);
		envf=z3coding.eliminateGtAndGe(envf);
		if(stepGe0==true){
			if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(c,envf.decl(),z3coding.LeDecl)){
				if(z3coding.equal(envf.arg(0),indexVar->scalaVarz3coding)){
					ret->push_back(envf);
				}
			}
		}
		else if(stepLe0==true){
			if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(c,envf.decl(),z3coding.LeDecl)){
				if(z3coding.equal(envf.arg(1),indexVar->scalaVarz3coding)){
					ret->push_back(envf);
				}
			}
		}
	}
	return ret;
}
unique_ptr<vector<expr>> getContainForallFormula(FlowSet* in){
	unique_ptr<vector<expr>> result(new vector<expr>());
	auto tmp=in->toVector();
	for(Property* p:*tmp){
		Formula* f=(Formula*)p;
		if(containForallFormula(f->formula)){
			result->push_back(f->formula);
		}
	}
	return result;
}
FlowSet* __closureForAllWithEnvironment_process(expr forAllFormula,FlowSet* env){
	
	FlowSet* result=userSupplied->newinitialFlow();result->clear();
	expr quantifier=z3coding.getQuantifier(forAllFormula);
	expr step=z3coding.getForAllFormulaStep(forAllFormula);
	expr stepFormula=z3coding.getForAllFormulaStepFormula(forAllFormula);
	expr quantifierBegin=z3coding.getForAllFormulaBegin(forAllFormula);
	expr quantifierEnd=z3coding.getForAllFormulaEnd(forAllFormula);
	expr quantifierBeginFormula=z3coding.getForAllFormulaBeginFormula(forAllFormula);
	expr quantifierEndFormula=z3coding.getForAllFormulaEndFormula(forAllFormula);
	expr quantifierExtendFormula=z3coding.getForAllFormulaExtendFormula(forAllFormula);
	expr body=z3coding.getQuantifierFormulaBody(forAllFormula);
	auto envVec=env->toVector();
	for(Property* envp:*envVec){
		expr envf=((Formula*)envp)->formula;
		if(envf.is_app()){
			//不使用ret性质生成新的量词性质
			if(z3coding.isContainRet(envf)){
					continue;
			}
			if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)
			||Z3_is_eq_func_decl(c,envf.decl(),z3coding.LeDecl)){
				//(e4 < e1 ∨ e4 ≤ e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),p ∈ a 	(3)
				//(e2 < e5 ∨ e2 ≤ e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),p ∈ a 	(4)
				expr left=envf.arg(0);
				expr right=envf.arg(1);
				auto ign=toExprs(env);
				if(z3coding.equal(left,quantifierBegin)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(right,quantifierEnd)
							&&LEclosureFQTactics3(ign.get(),right,quantifierEnd)
							&&LEQclosureFQTactics4(left,right)
							&&LEQclosureFQTactics5(left,right)){
					expr newquantifierBeginFormula(c);
					if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)){
						newquantifierBeginFormula=right<=quantifier;
					}
					else{
						newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,left,right);
					}
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,body)));
				}
				if(z3coding.equal(right,quantifierEnd)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(quantifierBegin,left)
							&&LEclosureFQTactics3(ign.get(),quantifierBegin,left)
							&&LEQclosureFQTactics4(right,left)
							&&LEQclosureFQTactics5(right,left)){
					expr newquantifierEndFormula(c);
					if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)){
						newquantifierEndFormula=quantifier<=left;
					}
					else{
						newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,right,left);
					}
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,body)));
				}
			}
			if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.EqDecl)){
				//(e4 = e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),p ∈ a 	(3)
				//(e2 = e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),p ∈ a 	(4)
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
	return result;
}

unique_ptr<vector<expr>>  ____closureForAllWithEnvironment_getRelevantOrFormula(int currow,vector<vector<expr>>& relevantOrFormulas){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	if((int)relevantOrFormulas.size()==currow+1){
		z3coding.pushAToB(&(relevantOrFormulas[currow]),ret.get());
		return ret;
	}
	for(int j=0;j<(int)relevantOrFormulas[currow].size();j++){
		auto tmp=____closureForAllWithEnvironment_getRelevantOrFormula(currow+1,relevantOrFormulas);
		if(tmp==nullptr){
			return nullptr;
		}
		expr tmp1=getOrFormulas(tmp.get());
		if(!z3coding.checkError(tmp1)){
			ret->push_back(relevantOrFormulas[currow][j]||tmp1);
		}
		else{
			cerr<<"Lift_Analysis::____closureForAllWithEnvironment_getRelevantOrFormula::something is wrong!"<<std::endl;
			cerr<<"error info::tmp is "<< toString(tmp.get())<<std::endl;
			return nullptr;
		}
	}
	return ret;
}

FlowSet* __closureForAllWithEnvironment_orFormula_process(expr orFormula,FlowSet* env){
	//split  
	//process every forallformula
	//merge
	auto orFormulas=z3coding.splitOrFormulas(orFormula);
	vector<vector<expr>>  relevantOrFormulas;
	vector<expr> unrelevantOrFormulas;
	for(expr e:*orFormulas){
		if(z3coding.isForAllFormula(e)){
			FlowSet*  newforallFormulas=__closureForAllWithEnvironment_process(e,env);
			auto newforallexprs=toExprs(newforallFormulas);
			delete newforallFormulas;
			relevantOrFormulas.push_back(*(newforallexprs.get())); 
		}
		else{
			unrelevantOrFormulas.push_back(e);
		}
	}

	auto relevantOrFormula=____closureForAllWithEnvironment_getRelevantOrFormula(0,relevantOrFormulas);
	if(relevantOrFormula==nullptr){
		return nullptr;
	}
	expr unrelevantorFormula=getOrFormulas(&unrelevantOrFormulas);
	if(z3coding.checkError(unrelevantorFormula)){
		return toFlowSet(relevantOrFormula.get());
	}
	else{
		vector<expr> orFormulas;
		for(expr e:*relevantOrFormula){
			orFormulas.push_back(unrelevantorFormula||e);
		}
		return toFlowSet(&orFormulas);
	}
	
}
FlowSet* closureForAllWithEnvironment(FlowSet* env,FlowSet* in){
	FlowSet* result=userSupplied->newinitialFlow();result->clear();
	auto containforallFormulas=getContainForallFormula(in); //getAllForallFormulas(in);
	for(expr containforallFormula:*containforallFormulas){
		if(z3coding.isForAllFormula(containforallFormula)){
			FlowSet* fs=__closureForAllWithEnvironment_process(containforallFormula,env);
			if(fs!=nullptr){
				result->Union(fs);
			}
		}
		else {
			if(z3coding.toString(containforallFormula)=="{(= r 0)} || {forall _i0 in (j,(- 1),(- i 1)],(not (= (select a i) (select a _i0)))}"){
				int xxx=0;
			}
			FlowSet* fs=__closureForAllWithEnvironment_orFormula_process(containforallFormula,env);
			if(fs!=nullptr){
				result->Union(fs);
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
	auto inExprs=toExprs(in);
	auto envExprs=toExprs(env);
	for(expr e:*inExprs){
		if(z3coding.isForAllFormula(e)||z3coding.isPhiFormula(e)){
			//cout<<e<<std::endl;
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
			
			if(z3coding.isIn(begin>end,envExprs.get())||z3coding.isIn(begin>=end,envExprs.get())||
				z3coding.isIn(end<begin,envExprs.get())||z3coding.isIn(end<=begin,envExprs.get())){
				continue;
			}
//			if(z3coding.prove(envExprs,end<begin)==proved_result::proved){
//				continue;
//			}
			auto endCons=z3coding.getConsts(end);
			if(isScaleVariable(begin)&&isScaleVariableOpStep(end)&&z3coding.isIn(begin,endCons.get())){
				continue;
			}
			if(isScaleVariable(end)&&isScaleVariableOpStep(begin)&&z3coding.isIn(begin,endCons.get())){
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
	auto phiFormulas=getAllPhiFormulas(in);
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
		auto envVec=env->toVector();
		for(Property* envp:*envVec){
			expr envf=((Formula*)envp)->formula;
			if(envf.is_app()){
				//if(mu.isGtZero(e)){
					//不使用ret性质生成新的量词性质
					if(z3coding.isContainRet(envf)){
						continue;
					}
					auto ign=toExprs(env);
					if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(c,envf.decl(),z3coding.LeDecl)){
						//(e4 < e1 ∨ e4 ≤ e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),false ∈ a 	
						//(e2 < e5 ∨ e2 ≤ e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),false ∈ a 	
						expr left=envf.arg(0);
						expr right=envf.arg(1);
						if(z3coding.equal(left,phiBegin)&&LEQclosureFQTactics1(left,right)&&LEQclosureFQTactics2(right,phiEnd)
						&&LEclosureFQTactics3(ign.get(),right,phiEnd)
						&&LEQclosureFQTactics4(left,right)
						&&LEQclosureFQTactics5(left,right)){
							//cout<<"phiFormula: "<<phiFormula<<", envf: "<<envf<<std::endl;
							expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,left,right);
							if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)){
								newphiBeginFormula=right<=quantifier;
							}
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,newphiBeginFormula,phiEndFormula,stepFormula)));
						}
						if(z3coding.equal(right,phiEnd)&&LEQclosureFQTactics1(right,left)&&LEQclosureFQTactics2(phiBegin,left)
							&&LEclosureFQTactics3(ign.get(),phiBegin,left)
						&&LEQclosureFQTactics4(right,left)
						&&LEQclosureFQTactics5(right,left)){
							//cout<<"phiFormula: "<<phiFormula<<", envf: "<<envf<<std::endl;
							expr newphiEndFormula=z3coding.substitute(phiEndFormula,right,left);
							if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.LtDecl)){
								newphiEndFormula=quantifier<=left;
							}
							result->add(new Formula(z3coding.constructPhiFormula(quantifier,phiBeginFormula,newphiEndFormula,stepFormula)));
						}
					}
					if(Z3_is_eq_func_decl(c,envf.decl(),z3coding.EqDecl)){
						//(e4 = e1 ) ∈ E ∧ ∀x.x ∈ [e4,c,e2),false ∈ a 	
						//(e2 = e5 ) ∈ E ∧ ∀x.x ∈ [e1,c,e5),false ∈ a 	
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
	FlowSet* newForalls=updatePhi(indexEnv,in);
	result->Union(newForalls);
	//∀x.x ∈ [initi,c,i),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i)]) ∈ a 	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)])∏p ψ2(e1[f1(x)]) 				(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(e1[f1(x)]) ∈ a∧ ψ2(e1[f1(i − c)]) ∈ a	∧ ψ(e1[f1(x)])=ψ1(e1[f1(x)]) ∏p ψ2(e1[f1(x)]) 		(8)
	
	/*newForalls=updateForAll(indexEnv,result);
	result->Union(newForalls);*/
	return result;

}



unique_ptr<vector<expr>> getPropertiesRelevantDefWithIndex(expr index,FlowSet* in){
	unique_ptr<vector<expr>> result(new vector<expr>());
	auto invec=in->toVector();
	for(Property* p:*invec){
		Formula* f=(Formula*)p;
		//cout<<"p is :" <<f->formula <<std::endl;
		auto defAcesses=z3coding.getDerAcessMemoryUnits(f->formula);
		for(expr defAcess:*defAcesses){
			auto ign=z3coding.getConsts(defAcess);
			if(z3coding.isIn(index,ign.get())){
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
	
	//cout<<"8888::"<<toString(in)<<std::endl;
	result->Union(generalizeUpdatePhi(indexEnv,in,&LiftAnalysis_FeasiblePath::getPropertiesRelevantDefWithIndex));
	//∀x.x ∈ [initi,c,i),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x)))∏p ψ2(def(f1(x))) 		(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i − c))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x))) ∏p ψ2(def(f1(x))) 	(8)
	/*result->Union(generalizeUpdateForAll(indexEnv,in));*/
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
FlowSet  *generalizeUpdatePhi(FlowSet* indexEnv,FlowSet  * in,unique_ptr<vector<expr>> (LiftAnalysis_FeasiblePath::*pfun_GetPropertiesRelevantWithIndex)(expr, FlowSet*)){
	//∀x.x ∈ [initi,c,i), false ∈ a ∧ ψ(def(f1(i))) ∈ a 					(5)
	//∀x.x ∈ [initi,c,i − c), false ∈ a ∧ ψ(def(f1(i − c))) ∈ a			(7)
	#ifdef _DEBUG
	//cout<<"updateDefPhi::in::"<<toString(in)<<std::endl;
	#endif
	
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	auto phiFormulas=getAllPhiFormulas(in);
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
			auto relevantProperties=(this->*pfun_GetPropertiesRelevantWithIndex)(index,in);
			for(expr property:*relevantProperties){
				//cout<<"property:: "<<property<<std::endl;
				if(z3coding.isPhiFormula(property)) continue;
				//当性质时Or公式时，不提升为全称量词性质
				if(z3coding.isOrFormula(property)) continue;
				if(mu.isGtZero(step)){
					expr newphiEndFormula=z3coding.substitute(phiEndFormula,index,index+step);
					
					auto cons=z3coding.getConstsWithQuantifier(property);
					auto initcons=z3coding.getConstsWithQuantifier(phiBeginFormula.arg(0));
					auto endcons=z3coding.getConstsWithQuantifier(newphiEndFormula.arg(1));
					auto stepcons=z3coding.getConstsWithQuantifier(step);
					z3coding.pushAToB(initcons.get(),cons.get());
					z3coding.pushAToB(endcons.get(),cons.get());
					z3coding.pushAToB(stepcons.get(),cons.get());
					expr newquantifier=constructNewQuantifierName(cons.get());
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
					
					auto cons=z3coding.getConstsWithQuantifier(property);
					auto initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula.arg(0));
					auto endcons=z3coding.getConstsWithQuantifier(phiEndFormula.arg(1));
					auto stepcons=z3coding.getConstsWithQuantifier(step);
					z3coding.pushAToB(initcons.get(),cons.get());
					z3coding.pushAToB(endcons.get(),cons.get());
					z3coding.pushAToB(stepcons.get(),cons.get());
					
					expr newquantifier=constructNewQuantifierName(cons.get());
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
			auto relevantProperties=(this->*pfun_GetPropertiesRelevantWithIndex)(index,in);
			for(expr property:*relevantProperties){
				if(z3coding.isPhiFormula( property)) continue;
				//当性质时Or公式时，不提升为全称量词性质
				if(z3coding.isOrFormula(property)) continue;
				if(mu.isGtZero(step)){
					expr newphiEndFormula=z3coding.substitute(phiEndFormula,phiEnd,index);
					auto cons=z3coding.getConstsWithQuantifier(property);
					auto initcons=z3coding.getConstsWithQuantifier(phiBeginFormula);
					auto endcons=z3coding.getConstsWithQuantifier(newphiEndFormula);
					auto stepcons=z3coding.getConstsWithQuantifier(stepFormula);
					z3coding.pushAToB(initcons.get(),cons.get());
					z3coding.pushAToB(endcons.get(),cons.get());
					z3coding.pushAToB(stepcons.get(),cons.get());
					expr newquantifier=constructNewQuantifierName(cons.get());
					//cout<<"property is11: "<<property<<std::endl;
//					if(z3coding.equal(property,ffff())){
//						cout<<phiEnd<<std::endl;
//					}
					expr newbody=z3coding.substitute(property,phiEnd,newquantifier);
					auto ign=z3coding.getConsts(newbody);
					if(z3coding.isIn(index,ign.get())){
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
					
					auto cons=z3coding.getConstsWithQuantifier(property);
					auto initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula);
					auto endcons=z3coding.getConstsWithQuantifier(phiEndFormula);
					auto stepcons=z3coding.getConstsWithQuantifier(stepFormula);
					z3coding.pushAToB(initcons.get(),cons.get());
					z3coding.pushAToB(endcons.get(),cons.get());
					z3coding.pushAToB(stepcons.get(),cons.get());
					
					expr newquantifier=constructNewQuantifierName(cons.get());
					//cout<<"property is: "<<property<<std::endl;
					expr newbody=z3coding.substitute(property,phiBegin,newquantifier);
					auto ign=z3coding.getConsts(newbody);
					if(z3coding.isIn(index,ign.get())){
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


std::pair<expr,expr>  ___generalizeUpdateForAll_process_getBodyresult(expr bodyresult,expr index){
	auto orFormulas=z3coding.splitOrFormulas(bodyresult);
	vector<expr> relevantOrFormulas;
	vector<expr> unrelevantOrFormulas;
	for(expr e:*orFormulas){
		auto cons=z3coding.getConsts(e);
		if(z3coding.isIn(index,cons.get())){
			relevantOrFormulas.push_back(e);
		}
		else{
			unrelevantOrFormulas.push_back(e);
		}
	}
	std::pair<expr,expr> ret(getOrFormulas(&relevantOrFormulas),getOrFormulas(&unrelevantOrFormulas));
	return ret;
}

bool __generalizeUpdateForAll_process_tactics(expr body,expr index){
	return __updatePhi_OrFormua_tactics(body,index);
}
Formula* __generalizeUpdateForAll_process(expr forAllFormula,FlowSet* indexEnv,FlowSet  * in){
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
			expr bodyresult=partialMerge(newbody,filteringLeftNonPhiFormula(in));
			expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd+step);
			if(!z3coding.equal(bodyresult,z3coding._error)){
				if(!__generalizeUpdateForAll_process_tactics(bodyresult,quantifierEnd)) return nullptr;
				std::pair<expr,expr> tmp=___generalizeUpdateForAll_process_getBodyresult(bodyresult,quantifierEnd);
				if(z3coding.checkError(tmp.first)){
					return nullptr;
				}
				else if(z3coding.checkError(tmp.second)){
					expr newbodyresult=z3coding.substitute(tmp.first,quantifierEnd,quantifier);
					return new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult));
				}
				else{
					expr newbodyresult=z3coding.substitute(tmp.first,quantifierEnd,quantifier);
					return new Formula(tmp.second||z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult));
				}
				/*expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
				return new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult));*/
			}
		}
		else if(mu.isLtZero(step)){
			expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
			expr bodyresult=partialMerge(newbody,filteringLeftNonPhiFormula(in));
			expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,quantifierBegin,quantifierBegin+step);
			if(!z3coding.equal(bodyresult,z3coding._error)){
				if(!__generalizeUpdateForAll_process_tactics(bodyresult,quantifierBegin)) return nullptr;
				std::pair<expr,expr> tmp=___generalizeUpdateForAll_process_getBodyresult(bodyresult,quantifierBegin);
				if(z3coding.checkError(tmp.first)){
					return nullptr;
				}
				else if(z3coding.checkError(tmp.second)){
					expr newbodyresult=z3coding.substitute(tmp.first,quantifierBegin,quantifier);
					return new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult));
				}
				else{
					expr newbodyresult=z3coding.substitute(tmp.first,quantifierBegin,quantifier);
					return new Formula(tmp.second||z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult));
				}
				
				/*expr newbodyresult=z3coding.substitute(bodyresult,quantifierBegin,quantifier);
				return new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult));*/
			}
		}
	}
	if(checkAtomicScalarSubStep(indexEnv,quantifierBegin,step,quantifierEnd)){
		if(mu.isGtZero(step)){
			expr newbody=z3coding.substitute(body,quantifier,quantifierEnd);
			expr bodyresult=partialMerge_moreEqual(newbody,filteringLeftNonPhiFormula(in));
			if(z3coding.isOrFormula(bodyresult)){
				return nullptr;
			}
			expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd.arg(0));
			if(!z3coding.equal(bodyresult,z3coding._error)){
				expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
				auto ign=z3coding.getConsts(newbodyresult);
				if(z3coding.isIn(quantifierEnd.arg(0),ign.get())){
					newbodyresult=z3coding.substitute(bodyresult,quantifierEnd.arg(0),quantifier+step);
				}
				return new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult));
			}
		}
		else if(mu.isLtZero(step)){
			expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
			expr bodyresult=partialMerge_moreEqual(newbody,filteringLeftNonPhiFormula(in));
			if(z3coding.isOrFormula(bodyresult)){
				return nullptr;
			}
			expr newquantifierBeginFormula=z3coding.substitute(quantifierBeginFormula,quantifierBegin,quantifierBegin.arg(0));
			if(!z3coding.equal(bodyresult,z3coding._error)){
				expr newbodyresult=z3coding.substitute(bodyresult,quantifierBegin,quantifier);
				auto ign=z3coding.getConsts(newbodyresult);
				if(z3coding.isIn(quantifierBegin.arg(0),ign.get())){
					newbodyresult=z3coding.substitute(bodyresult,quantifierBegin.arg(0),quantifier+step);
				}
				return new Formula(z3coding.constructForAllFormula(quantifier,newquantifierBeginFormula,quantifierEndFormula,stepFormula,newbodyresult));
			}
		}
	}
	return nullptr;
}
Formula* __generalizeUpdateForAll_orFormula_process(expr orFormula,FlowSet* indexEnv,FlowSet  * in){
	//split
	//
	auto orFormulas=z3coding.splitOrFormulas(orFormula);
	vector<expr>  relevantOrFormulas;
	vector<expr>  unrelevantOrFormulas;
	vector<expr>  newrelevantOrFormulas;
	for(expr e:*orFormulas){
		if(z3coding.isForAllFormula(e)){
			Formula* f= __generalizeUpdateForAll_process(e,indexEnv,in);
			if(f!=nullptr){
				newrelevantOrFormulas.push_back(f->formula);
				delete f;
			}
			else{
				unrelevantOrFormulas.push_back(e);
			}
		}
		else{
			unrelevantOrFormulas.push_back(e);
		}
	}
	if(newrelevantOrFormulas.size()>0){
		expr unrelevantOrFormula=getOrFormulas(&unrelevantOrFormulas);
		expr relevantOrFormula=getOrFormulas(&newrelevantOrFormulas);
		if(z3coding.checkError(relevantOrFormula)){
			return nullptr;
		}
		else if(z3coding.checkError(unrelevantOrFormula)){
			if(z3coding.getOrCount(relevantOrFormula)>DISJUNCTIONK){
				return nullptr;
			}
			return new Formula(relevantOrFormula);
		}
		else{
			if(z3coding.getOrCount(relevantOrFormula)+z3coding.getOrCount(unrelevantOrFormula)>DISJUNCTIONK){
				return nullptr;
			}
			return new Formula(unrelevantOrFormula||relevantOrFormula);
		}
		
	}
	else{
		return nullptr;
	}
}
FlowSet  *generalizeUpdateForAll(FlowSet* indexEnv,FlowSet  * in){
	//∀x.x ∈ [initi,c,i),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x)))∏p ψ2(def(f1(x))) 		(6)
	//∀x.x ∈ [initi,c,i − c),ψ1(def(f1(x))) ∈ a∧ ψ2(def(f1(i − c))) ∈ a ∧ ψ(def(f1(x)))=ψ1(def(f1(x))) ∏p ψ2(def(f1(x))) 	(8)
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
	auto containforallFormulas= getContainForallFormula(in);//getAllForallFormulas(in);
	
	for(expr containforallFormula:*containforallFormulas){
		if(z3coding.isForAllFormula(containforallFormula)){
			Formula* f=__generalizeUpdateForAll_process(containforallFormula,indexEnv,in);
			if(f!=nullptr){
				result->add(f);
			}		
		}
		else{
			Formula* f=__generalizeUpdateForAll_orFormula_process(containforallFormula,indexEnv,in);
			if(f!=nullptr){
				result->add(f);
			}
		}
		
	}
	return result;
}


Formula* __updatePhiProcess1(expr arrayAcessProperty,expr index,expr quantifier, expr phiEndFormula,
																			expr phiBeginFormula,expr stepFormula,expr step){
	if(mu.isGtZero(step)){
		expr newphiEndFormula=z3coding.substitute(phiEndFormula,index,index+step);
		auto cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
		auto initcons=z3coding.getConstsWithQuantifier(phiBeginFormula.arg(0));
		auto endcons=z3coding.getConstsWithQuantifier(newphiEndFormula.arg(1));
		auto stepcons=z3coding.getConstsWithQuantifier(step);
		z3coding.pushAToB(initcons.get(),cons.get());
		z3coding.pushAToB(endcons.get(),cons.get());
		z3coding.pushAToB(stepcons.get(),cons.get());
		expr newquantifier=constructNewQuantifierName(cons.get());
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
		return ttt;
	}
	else if(mu.isLtZero(step)){
		expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,index,index+step);
		
		auto cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
		auto initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula.arg(0));
		auto endcons=z3coding.getConstsWithQuantifier(phiEndFormula.arg(1));
		auto stepcons=z3coding.getConstsWithQuantifier(step);
		z3coding.pushAToB(initcons.get(),cons.get());
		z3coding.pushAToB(endcons.get(),cons.get());
		z3coding.pushAToB(stepcons.get(),cons.get());
		
		expr newquantifier=constructNewQuantifierName(cons.get());
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
		return ttt;
	}
	return nullptr;
}
expr getOrFormulas(vector<expr>* orFormulas){
	expr ret=z3coding._error;
	if(orFormulas->size()>0){
		ret=orFormulas->at(0);
	}
	for(int i=1;i<(int)orFormulas->size();i++){
		ret=ret||orFormulas->at(i);
	}
	return ret;
}
Formula*  __updatePhi_OrFormula1(expr arrayAcessProperty,expr index,expr quantifier, expr phiEndFormula,
																			expr phiBeginFormula,expr stepFormula,expr step){
	//split  
	//get lcv Relevant
	//lift
	if(!__updatePhi_OrFormua_tactics(arrayAcessProperty,index)) return nullptr;
	auto orFormulas=z3coding.splitOrFormulas(arrayAcessProperty);
	vector<expr> relevantOrFormulas;
	vector<expr> unrelevantOrFormulas;
	for(expr e:*orFormulas){
		auto cons=z3coding.getConsts(e);
		if(z3coding.isIn(index,cons.get())){
			relevantOrFormulas.push_back(e);
		}
		else{
			unrelevantOrFormulas.push_back(e);
		}
	}
	expr relevantorFormula=getOrFormulas(&relevantOrFormulas);
	if(z3coding.checkError(relevantorFormula)){
		return nullptr;
	}
	Formula* f= __updatePhiProcess1(relevantorFormula,index,quantifier,phiEndFormula,phiBeginFormula,stepFormula,step);
	if(f!=nullptr){
		expr forallExpr=f->formula;
		expr unrelevantorFormula=getOrFormulas(&unrelevantOrFormulas);
		if(z3coding.checkError(unrelevantorFormula)){
			delete f;
			return new Formula(forallExpr);
		}
		else{
			return new Formula(unrelevantorFormula||forallExpr);
		}
	}
	else{
		return nullptr;
	}
}
Formula*  __updatePhiProcess2(expr arrayAcessProperty,expr index,expr quantifier, expr phiEndFormula,
																			expr phiBeginFormula,expr stepFormula,expr step,expr phiEnd,expr phiBegin){
	if(mu.isGtZero(step)){
		expr newphiEndFormula=z3coding.substitute(phiEndFormula,phiEnd,index);
		auto cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
		auto initcons=z3coding.getConstsWithQuantifier(phiBeginFormula);
		auto endcons=z3coding.getConstsWithQuantifier(newphiEndFormula);
		auto stepcons=z3coding.getConstsWithQuantifier(stepFormula);
		z3coding.pushAToB(initcons.get(),cons.get());
		z3coding.pushAToB(endcons.get(),cons.get());
		z3coding.pushAToB(stepcons.get(),cons.get());
		expr newquantifier=constructNewQuantifierName(cons.get());
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
			return ttt;
		}
	}
	else if(mu.isLtZero(step)){
		expr newphiBeginFormula=z3coding.substitute(phiBeginFormula,phiBegin,index);
		
		auto cons=z3coding.getConstsWithQuantifier(arrayAcessProperty);
		auto initcons=z3coding.getConstsWithQuantifier(newphiBeginFormula);
		auto endcons=z3coding.getConstsWithQuantifier(phiEndFormula);
		auto stepcons=z3coding.getConstsWithQuantifier(stepFormula);
		z3coding.pushAToB(initcons.get(),cons.get());
		z3coding.pushAToB(endcons.get(),cons.get());
		z3coding.pushAToB(stepcons.get(),cons.get());
		
		expr newquantifier=constructNewQuantifierName(cons.get());
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
			return ttt;
		}
	}
	return nullptr;
}
//if  f is (forall p or p2), not updatephi
bool __updatePhi_OrFormua_tactics(expr arrayAcessProperty,expr index){
	if(z3coding.toString(arrayAcessProperty)=="{(= (select a i) (select a j))} || {exist _i0 in [1,1,100),(not (= (select a _i0) (select a j)))}"){
		int yyy=1;
	}
	auto orFormulas=z3coding.splitOrFormulas(arrayAcessProperty);
	vector<expr> relevantOrFormulas;
	vector<expr> unrelevantOrFormulas;
	for(expr e:*orFormulas){
		auto cons=z3coding.getConsts(e);
		if(z3coding.isIn(index,cons.get())){
			relevantOrFormulas.push_back(e);
		}
		else{
			unrelevantOrFormulas.push_back(e);
		}
	}
	for(expr e:relevantOrFormulas){
		if((z3coding.isForAllFormula(e)||z3coding.isExistFormula(e))&&relevantOrFormulas.size()>1){
			return false;
		}
		/*if(relevantOrFormulas.size()>1){
			return false;
		}*/
	}
	return true;
}
Formula * __updatePhi_OrFormula2(expr arrayAcessProperty,expr index,expr quantifier, expr phiEndFormula, expr phiBeginFormula,expr stepFormula,expr step,expr phiEnd,expr phiBegin){
	if(!__updatePhi_OrFormua_tactics(arrayAcessProperty,index)) return nullptr;
	auto orFormulas=z3coding.splitOrFormulas(arrayAcessProperty);
	vector<expr> relevantOrFormulas;
	vector<expr> unrelevantOrFormulas;
	for(expr e:*orFormulas){
		auto cons=z3coding.getConsts(e);
		if(z3coding.isIn(index,cons.get())){
			relevantOrFormulas.push_back(e);
		}
		else{
			unrelevantOrFormulas.push_back(e);
		}
	}
	expr relevantorFormula=getOrFormulas(&relevantOrFormulas);
	if(z3coding.checkError(relevantorFormula)){
		return nullptr;
	}
	Formula* f= __updatePhiProcess2(relevantorFormula,index,quantifier,phiEndFormula,phiBeginFormula,stepFormula,step,phiEnd,phiBegin);
	if(f!=nullptr){
		expr forallExpr=f->formula;
		expr unrelevantorFormula=getOrFormulas(&unrelevantOrFormulas);
		if(z3coding.checkError(unrelevantorFormula)){
			delete f;
			return new Formula(forallExpr);
		}
		else{
			delete f;
			return new Formula(unrelevantorFormula||forallExpr);
		}
	}
	else{
		return nullptr;
	}
}
FlowSet  *__updatePhi(FlowSet* indexEnv,vector<expr>* phiFormulas,FlowSet  * in){
	FlowSet  * result=userSupplied->newinitialFlow();result->clear();
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
			auto relevantArrayAcessProperties=getPropertiesRelevantArrayAcessWithIndex(index,in);
			for(expr arrayAcessProperty:*relevantArrayAcessProperties){
				if(z3coding.isPhiFormula( arrayAcessProperty)) continue;
				//当性质时Or公式时，不提升为全称量词性质
				if(z3coding.isOrFormula(arrayAcessProperty)) {
					
					Formula* f= __updatePhi_OrFormula1(arrayAcessProperty,index,quantifier,phiEndFormula,phiBeginFormula,stepFormula,step);
					if(f!=nullptr){
						result->add(f);
					}
				}
				else {
					Formula* f=__updatePhiProcess1(arrayAcessProperty,index,quantifier,phiEndFormula,phiBeginFormula,stepFormula,step);
					if(f!=nullptr){
						result->add(f);
					}
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
			auto relevantArrayAcessProperties=getPropertiesRelevantArrayAcessWithIndex(index,in);
			for(expr arrayAcessProperty:*relevantArrayAcessProperties){
				if(z3coding.isPhiFormula( arrayAcessProperty)) continue;
				//当性质时Or公式时，不提升为全称量词性质
				if(z3coding.isOrFormula(arrayAcessProperty)) {
					Formula* f=__updatePhi_OrFormula2(arrayAcessProperty,index,quantifier,phiEndFormula,phiBeginFormula,stepFormula,step,phiEnd,phiBegin);
					if(f!=nullptr){
						result->add(f);
					}
				}
				else {
					Formula* f=__updatePhiProcess2(arrayAcessProperty,index,quantifier,phiEndFormula,phiBeginFormula,stepFormula,step,phiEnd,phiBegin);
					if(f!=nullptr){
						result->add(f);
					}
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
	auto phiFormulas=getAllPhiFormulas(in);
	
	auto newForallFormulas=in->clone();
	while(newForallFormulas->size()!=0){
		newForallFormulas=__updatePhi(indexEnv,phiFormulas.get(),newForallFormulas);
		//cout<<"new forall:: "<< toString(newForallFormulas)<<std::endl;
		if(newForallFormulas!=nullptr){
			result->Union(newForallFormulas);
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
	auto forallFormulas=getAllForallFormulas(in);
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
				expr bodyresult=partialMerge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd+step);
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
			else if(mu.isLtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
				expr bodyresult=partialMerge(newbody,filteringLeftNonPhiFormula(in));
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
				expr bodyresult=partialMerge(newbody,filteringLeftNonPhiFormula(in));
				expr newquantifierEndFormula=z3coding.substitute(quantifierEndFormula,quantifierEnd,quantifierEnd.arg(0));
				if(!z3coding.equal(bodyresult,z3coding._error)){
					expr newbodyresult=z3coding.substitute(bodyresult,quantifierEnd,quantifier);
					result->add(new Formula(z3coding.constructForAllFormula(quantifier,quantifierBeginFormula,newquantifierEndFormula,stepFormula,newbodyresult)));
				}
			}
			else if(mu.isLtZero(step)){
				expr newbody=z3coding.substitute(body,quantifier,quantifierBegin);
				expr bodyresult=partialMerge(newbody,filteringLeftNonPhiFormula(in));
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
unique_ptr<vector<expr>> getAllForallFormulas(FlowSet  * in){
	unique_ptr<vector<expr>> result(new vector<expr>());
	auto tmp=in->toVector();
	for(Property* p:*tmp){
		Formula* f=(Formula*)p;
		if(z3coding.isForAllFormula(f->formula)){
			result->push_back(f->formula);
		}
	}
	return result;
}
unique_ptr<vector<expr>> getAllPhiFormulas(FlowSet  * in){
	unique_ptr<vector<expr>> result(new vector<expr>());
	auto tmp=in->toVector();
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
unique_ptr<vector<expr>> getPropertiesRelevantArrayAcessWithIndex(expr index,FlowSet* in){
	unique_ptr<vector<expr>> result(new vector<expr>());
	auto invec=in->toVector();
	for(Property* p:*invec){
		Formula* f=(Formula*)p;
		auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(f->formula);
		for(expr arrayAcess:*arrayAcesses){
			auto ign=z3coding.getConsts(arrayAcess);
			if(z3coding.isIn(index,ign.get())){
				result->push_back(f->formula);
			}
		}
	}
	return result;
}


bool isArrayProperty(expr e){
	auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(e);
	return arrayAcesses->size()!=0;
}
bool isDefProperty(expr e){
	auto defAcesses=z3coding.getDerAcessMemoryUnits(e);
	return defAcesses->size()!=0;
}
bool isSubscriptContain(expr arrayProperty,expr index){
	auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(arrayProperty);
	for(expr arrayAcess:*arrayAcesses){
		auto ign=z3coding.getConsts(arrayAcess);
		if(z3coding.isIn(index,ign.get())){
			return true;
		}
	}
	return false;
}

bool isDefSubscriptContain(expr defProperty,expr index){
	auto defAcesses=z3coding.getDerAcessMemoryUnits(defProperty);
	for(expr defAcess:*defAcesses){
		auto ign=z3coding.getConsts(defAcess);
		if(z3coding.isIn(index,ign.get())){
			return true;
		}
	}
	return false;
}


FlowSet * genSimPlePriopertyByMultiRelation(FlowSet* simpleProps_in, FlowSet* indexEnv,FlowSet* indexRelations){
	FlowSet * result=new ValueListSetWithUniversalSet();
	ValueListSetWithUniversalSet* indexRelationsVls=(ValueListSetWithUniversalSet*)indexRelations;
	 unique_ptr<vector<expr>> simpleProps_inexpr=flowSetToExprSet(simpleProps_in);
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
		std::cerr<<"LiftAnalysis_FeasiblePath::isEq: "<< e <<" must be int type!"<<std::endl;	
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
		cerr<<"LiftAnalysis_FeasiblePath::getIndex2EqFIndex1:: something is wrong!"<<std::endl;
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

//whether f1 can implies f2
//判断f1能否推出f2
bool partialOrderRelation(Formula* f1,Formula* f2){
	if(DISJUNCTIONK<=0){
		if(userSupplied->isSimpleProperty(f1)&&userSupplied->isSimpleProperty(f2)){
			return userSupplied->partialOrderRelation(f1,f2);
		}
		else if(z3coding.isForAllFormula(f1->formula)&&z3coding.isForAllFormula(f2->formula)){
			return partialOrderRelation_forall_forall(f1->formula,f2->formula);
		}
		else if(z3coding.isPhiFormula(f1->formula)&&z3coding.isForAllFormula(f2->formula)){
			return partialOrderRelation_phi_forall(f1->formula,f2->formula);
		}
		else if(z3coding.isExistFormula(f1->formula)&&z3coding.isExistFormula(f2->formula)){
			return partialOrderRelation_exist_exist(f1->formula,f2->formula);
		}
	}
	else{
		if(userSupplied->isSimpleProperty(f1)&&userSupplied->isSimpleProperty(f2)){
			return userSupplied->partialOrderRelation(f1,f2);
		}
		else if(z3coding.isForAllFormula(f1->formula)&&z3coding.isForAllFormula(f2->formula)){
			return partialOrderRelation_forall_forall(f1->formula,f2->formula);
		}
		else if(z3coding.isPhiFormula(f1->formula)&&z3coding.isForAllFormula(f2->formula)){
			return partialOrderRelation_phi_forall(f1->formula,f2->formula);
		}
		else if(z3coding.isExistFormula(f1->formula)&&z3coding.isExistFormula(f2->formula)){
			return partialOrderRelation_exist_exist(f1->formula,f2->formula);
		}
		else if(z3coding.isOrFormula(f1->formula)||z3coding.isOrFormula(f2->formula)){
			int orcount1=z3coding.getOrCount(f1->formula);
			int orcount2=z3coding.getOrCount(f2->formula);
			if(orcount1<orcount2){
				return partialOrderRelation_other_or(f1->formula,f2->formula);
			}
			else{
				return false;
			}
		}
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
		Formula bf1(body1);
		Formula bf2(body2);
		return partialOrderRelation(&bf1,&bf2);
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
unique_ptr<vector<expr>> toExprs(FlowSet  * in){
	unique_ptr<vector<expr>> result(new vector<expr>());
	auto invec=in->toVector();
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

/*expr partialMerge(expr f,FlowSet  * in){
	auto formulas=toExprs(in);
	if(z3coding.isIn(f,formulas.get())){
		return f;
	}
	Formula formulaTmp1(f);
	FlowSet* in1=userSupplied->newinitialFlow();in1->clear();
	FlowSet* in2=userSupplied->newinitialFlow();in2->clear();
	FlowSet* out=userSupplied->newinitialFlow();out->clear();

	for(expr ele:*formulas){
		Formula formulaTmp2(ele);
		if(z3coding.isForAllFormula(f)&&z3coding.isForAllFormula(ele)){
			expr meet_result=_nonSimpleFormulaMeet(f,ele);
			//expr meet_result=_merge(f,ele);
			if(!z3coding.checkError(meet_result)){	
				return meet_result;
			}
		}
		if(z3coding.isExistFormula(f)&&z3coding.isExistFormula(ele)){
			expr meet_result=_nonSimpleFormulaMeet(f,ele);
			//expr meet_result=_merge(f,ele);
			if(!z3coding.checkError(meet_result)){	
				return meet_result;
			}
		}

		if(userSupplied->isSimpleProperty(&formulaTmp1)&&userSupplied->isSimpleProperty(&formulaTmp2)){
			in1->add(&formulaTmp1);in2->add(&formulaTmp2);
			userSupplied->merge(in1,in2,out);
			if(out->size()>0){	
				auto outvec=out->toVector();
				Formula* ret=(Formula*)(outvec->at(0));
				return ret->formula;
			}
		}
		in1->clear();in2->clear();out->clear();
	}
	//cerr<<"merge result is wrong!"<<std::endl;
	return z3coding._error;
}*/


expr partialMerge(expr f,FlowSet  * in){
	auto formulas=toExprs(in);
	if(z3coding.isIn(f,formulas.get())){
		return f;
	}
	Formula formulaTmp1(f);
	FlowSet* in1=userSupplied->newinitialFlow();in1->clear();
	FlowSet* in2=userSupplied->newinitialFlow();in2->clear();
	FlowSet* out=userSupplied->newinitialFlow();out->clear();

	for(expr ele:*formulas){
		Formula formulaTmp2(ele);
		if(userSupplied->isSimpleProperty(&formulaTmp1)&&userSupplied->isSimpleProperty(&formulaTmp2)){
			in1->add(&formulaTmp1);in2->add(&formulaTmp2);
			userSupplied->merge(in1,in2,out);
			if(out->size()>0){	
				auto outvec=out->toVector();
				Formula* ret=(Formula*)(outvec->at(0));
				return ret->formula;
			}
		}
		else{
			if(partialOrderRelation(&formulaTmp1,&formulaTmp2)){
				return formulaTmp2.formula;
			}
			else if(partialOrderRelation(&formulaTmp2,&formulaTmp1)){
				return formulaTmp1.formula;
			}				
		}
		in1->clear();in2->clear();out->clear();
	}
	//cerr<<"merge result is wrong!"<<std::endl;
	return z3coding._error;
}


/*expr partialMerge_moreEqual(expr f,FlowSet  * in){
	auto formulas=toExprs(in);
	if(z3coding.isIn(f,formulas.get())){
		return f;
	}
	Formula formulaTmp1(f);
	FlowSet* in1=userSupplied->newinitialFlow();in1->clear();
	FlowSet* in2=userSupplied->newinitialFlow();in2->clear();
	FlowSet* out=userSupplied->newinitialFlow();out->clear();

	for(expr ele:*formulas){
		Formula formulaTmp2(ele);
		if(z3coding.isForAllFormula(f)&&z3coding.isForAllFormula(ele)){
			expr meet_result=_nonSimpleFormulaMeet(f,ele);
			//expr meet_result=_merge(f,ele);
			if(!z3coding.checkError(meet_result)){	
				return meet_result;
			}
		}
		if(z3coding.isExistFormula(f)&&z3coding.isExistFormula(ele)){
			expr meet_result=_nonSimpleFormulaMeet(f,ele);
			//expr meet_result=_merge(f,ele);
			if(!z3coding.checkError(meet_result)){	
				return meet_result;
			}
		}
		if(userSupplied->isSimpleProperty(&formulaTmp1)&&userSupplied->isSimpleProperty(&formulaTmp2)){
			in1->add(&formulaTmp1);in2->add(&formulaTmp2);
			userSupplied->merge(in1,in2,out);
			if(out->size()>0){	
				auto outvec=out->toVector();
				Formula* ret=(Formula*)(outvec->at(0));
				return ret->formula;
			}
		}
		in1->clear();in2->clear();out->clear();
	}
	for(expr ele:*formulas){
		Formula formulaTmp2(ele);
		if(userSupplied->isSimpleProperty(&formulaTmp1)&&userSupplied->isSimpleProperty(&formulaTmp2)){
			if(z3coding.power_equal(f,ele)){
				return ele;
			}
		}	
	}
	//cerr<<"merge_moreEqual is wrong!"<<std::endl;
	return z3coding._error;
}*/


expr partialMerge_moreEqual(expr f,FlowSet  * in){
	auto formulas=toExprs(in);
	if(z3coding.isIn(f,formulas.get())){
		return f;
	}
	Formula formulaTmp1(f);
	FlowSet* in1=userSupplied->newinitialFlow();in1->clear();
	FlowSet* in2=userSupplied->newinitialFlow();in2->clear();
	FlowSet* out=userSupplied->newinitialFlow();out->clear();

	for(expr ele:*formulas){
		Formula formulaTmp2(ele);
		
		if(userSupplied->isSimpleProperty(&formulaTmp1)&&userSupplied->isSimpleProperty(&formulaTmp2)){
			in1->add(&formulaTmp1);in2->add(&formulaTmp2);
			userSupplied->merge(in1,in2,out);
			if(out->size()>0){	
				auto outvec=out->toVector();
				Formula* ret=(Formula*)(outvec->at(0));
				return ret->formula;
			}
		}
		else{
			if(partialOrderRelation(&formulaTmp1,&formulaTmp2)){
				return formulaTmp2.formula;
			}
			else if(partialOrderRelation(&formulaTmp2,&formulaTmp1)){
				return formulaTmp1.formula;
			}				
		}
		in1->clear();in2->clear();out->clear();
	}
	for(expr ele:*formulas){
		Formula formulaTmp2(ele);
		if(userSupplied->isSimpleProperty(&formulaTmp1)&&userSupplied->isSimpleProperty(&formulaTmp2)){
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
bool mayMemoryUnitIsInFormula(FlowSet* Pre,expr memoryunit,expr formula,const clang::Stmt* clangStmt,int count){
	if(memoryunit.is_const()){
		auto consts=z3coding.getConsts(formula);
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
			return mayArrayAcessMemoryUnitIsInQuantifierFormula(Pre,memoryunit,formula,clangStmt,count);
		}
		if(z3coding.isExistFormula(formula)){
			return mayArrayAcessMemoryUnitIsInQuantifierFormula(Pre,memoryunit,formula,clangStmt,count);
		}
		if(z3coding.isPhiFormula(formula)){
			return mayArrayAcessMemoryUnitIsInPhiFormula(Pre,memoryunit,formula,clangStmt,count);
		}
		else if(z3coding.isOrFormula(formula)){
			auto orformulas=z3coding.splitOrFormulas(formula);
			for(expr of:*orformulas){
				if(mayMemoryUnitIsInFormula(Pre,memoryunit,of,clangStmt,count)){
					return true;
				}
			}
			return false;
		}
		else{
			//cout<<"formula is: "<<formula<<std::endl;
			auto formulaMemoryUnits=z3coding.getMemoryUnits(formula);
			for(expr formulamemoryunit: *formulaMemoryUnits){
				if(mayMemoryUnitIsIn(Pre,memoryunit,formulamemoryunit,clangStmt,count)){
					return true;
				}
			}
			return false;
		}
	}
	else if(z3coding.isDer_PointerExpr(memoryunit)){
		if(z3coding.isForAllFormula(formula)){
			return mayDerMemoryUnitIsInQuantifierFormula(Pre,memoryunit,formula,clangStmt,count);
			//return false;
		}
		if(z3coding.isExistFormula(formula)){
			return mayDerMemoryUnitIsInQuantifierFormula(Pre,memoryunit,formula,clangStmt,count);
		}
		if(z3coding.isPhiFormula(formula)){
			return mayDerMemoryUnitIsInPhiFormula(Pre,memoryunit,formula,clangStmt,count);
			//return false;
		}
		else if(z3coding.isOrFormula(formula)){
			auto orformulas=z3coding.splitOrFormulas(formula);
			for(expr of:*orformulas){
				if(mayMemoryUnitIsInFormula(Pre,memoryunit,of,clangStmt,count)){
					return true;
				}
			}
			return false;
		}
		else{
			auto formulaMemoryUnits=z3coding.getMemoryUnits(formula);
			for(expr formulamemoryunit: *formulaMemoryUnits){
				if(mayMemoryUnitIsIn(Pre,memoryunit,formulamemoryunit,clangStmt,count)){
					return true;
				}
			}
			return false;
		}
	}
	//isMemberExpr a.b,a->b
	else if(z3coding.isMemberExpr(memoryunit)){
		if(z3coding.isForAllFormula(formula)){
			return mayMemberMemoryUnitIsInQuantifierFormula(Pre,memoryunit,formula,clangStmt,count);
			//return false;
		}
		if(z3coding.isExistFormula(formula)){
			return mayMemberMemoryUnitIsInQuantifierFormula(Pre,memoryunit,formula,clangStmt,count);
		}
		if(z3coding.isPhiFormula(formula)){
			return mayMemberMemoryUnitIsInPhiFormula(Pre,memoryunit,formula,clangStmt,count);
			//return false;
		}
		else if(z3coding.isOrFormula(formula)){
			auto orformulas=z3coding.splitOrFormulas(formula);
			for(expr of:*orformulas){
				if(mayMemoryUnitIsInFormula(Pre,memoryunit,of,clangStmt,count)){
					return true;
				}
			}
			return false;
		}
		else{
			auto formulaMemoryUnits=z3coding.getMemoryUnits(formula);
			for(expr formulamemoryunit: *formulaMemoryUnits){
				if(mayMemoryUnitIsIn(Pre,memoryunit,formulamemoryunit,clangStmt,count)){
					return true;
				}
			}
			return false;
		}
	}
	else{
		std::cerr<<"LiftAnalysis_FeasiblePath::mayMemoryUnitIsInFormula:: we can not process "<<memoryunit<<std::endl;
		return true;
	}
}

bool mayDerMemoryUnitIsInQuantifierFormula(FlowSet* Pre,expr memoryunit,expr forAllFormula,const clang::Stmt* clangStmt,int count){
	//memoryunit is derMemoryUnit
	//1. get all memoryUnits of forallFormula
	//2. check whether memoryunit kill any memoryUnits of forallFormula 
	expr pointerExprOfmemoryunit=z3coding.getPointerExpr(memoryunit);
	auto memoryUnitsOfForAllFormula=z3coding.getMemoryUnitsWithQuantifierFormula(forAllFormula);
	auto quantifiers=z3coding.getAllQuantifier(forAllFormula);
	auto quantifierBeginFormulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
	auto quantifierEndFormulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
	auto quantifierStepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
	
	/*for(expr memoryU:*memoryUnitsOfForAllFormula){
		vector<int>* quantifiersindexIsIn=quantifierIsIn(quantifiers,memoryU);
		if(quantifiersindexIsIn->size()!=0){
			//QuantifierMemoryAccess,*(e1) e2(q),q satisfy formula p
			//if e2(q) is *(e3(p)),check whether e3(p)==e2 under constraint p
			// if e2(q) is e3[f(p)], check whe whether e2 point to e3[f(p)] under constraint p
			vector<expr>* PreVector=toExprs(Pre);
			
			if(z3coding.isDer_PointerExpr(memoryU)){
				expr pointerExpr=z3coding.getPointerExpr(memoryU);
				expr assert= pointerExprOfmemoryunit==pointerExpr;
				if()		
			}
			else if(z3coding.isArrayAcess(memoryU)){
				
			}
			else{
				cerr<<"somthing is wrong!"<<std::endl;
				cerr<<"LiftAnalysis_Feasiblepath::mayDerMemoryUnitIsInForAllFormula::error info:memoryU is "<<memoryU<<std::endl;
			}
		}
			
	}*/
	//cout<<"memoryunit: "<<memoryunit<<std::endl;
	//cout<<"forAllFormula: "<<z3coding.toString(forAllFormula)<<std::endl;
	expr quantifiersconstraint=quantifierBeginFormulas->at(0)&&quantifierEndFormulas->at(0)&&quantifierStepFormulas->at(0);
	for(int i=1;i<(int)quantifiers->size();i++){
		quantifiersconstraint=quantifiersconstraint&&quantifierBeginFormulas->at(i)&&quantifierEndFormulas->at(i)
						&&quantifierStepFormulas->at(i);
	}
	auto PreVector=toExprs(Pre);
	PreVector->push_back(quantifiersconstraint);
	for(expr memoryU:*memoryUnitsOfForAllFormula){
		if(z3coding.isDer_PointerExpr(memoryU)){
			//cout<<"memoryU: "<<memoryU<<std::endl;
			expr pointerExpr=z3coding.getPointerExpr(memoryU);
			expr assert= pointerExprOfmemoryunit==pointerExpr;
			if(z3coding.satisfy(PreVector.get(),assert)!=check_result::unsat){
				return true;
			}
		}
		else {
			if(mayMemoryUnitIsIn(Pre,memoryunit,memoryU,clangStmt,count)){
				return true;
			}
		}
	}
	return false;
}
/*vector<int>* quantifierIsIn(vector<expr>* quantifiers,expr memoryU){
	vector<int>* ret=new vector<int>();
	for(int i=0;i<(int)quantifiers->size();i++){		
		vector<expr> consts=getConsts(memoryU);
		if(isIn(quantifiers->at(i),consts)){
			ret->push_back(i);
		}
	}
	return ret;	
}*/
bool mayDerMemoryUnitIsInPhiFormula(FlowSet* Pre,expr memoryunit,expr phiFormula,const clang::Stmt* clangStmt,int count){
	expr phiBegin=z3coding.getPhiBegin(phiFormula);
	expr phiEnd=z3coding.getPhiEnd(phiFormula);
	expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
	expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
	expr phiStep=z3coding.getPhiStep(phiFormula);
	auto memoryUnits=z3coding.getMemoryUnitsWithQuantifierFormula(phiFormula);
	for(expr memoryU:*memoryUnits){
		if(mayMemoryUnitIsIn(Pre,memoryunit,memoryU,clangStmt,count)){
			return true;
		}
	}
	return false;
}
bool mayMemberMemoryUnitIsInQuantifierFormula(FlowSet* Pre,expr memoryunit,expr forAllFormula,const clang::Stmt* clangStmt,int count){
	expr pointerExprOfmemoryunit=z3coding.getPointerExpr(memoryunit);
	auto memoryUnitsOfForAllFormula=z3coding.getMemoryUnitsWithQuantifierFormula(forAllFormula);
	auto quantifiers=z3coding.getAllQuantifier(forAllFormula);
	auto quantifierBeginFormulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
	auto quantifierEndFormulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
	auto quantifierStepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
	expr quantifiersconstraint=quantifierBeginFormulas->at(0)&&quantifierEndFormulas->at(0)&&quantifierStepFormulas->at(0);
	for(int i=1;i<(int)quantifiers->size();i++){
		quantifiersconstraint=quantifiersconstraint&&quantifierBeginFormulas->at(i)&&quantifierEndFormulas->at(i)
						&&quantifierStepFormulas->at(i);
	}
	FlowSet* NewPre=Pre->clone();
	Formula qff(quantifiersconstraint);
	NewPre->add(&qff);
	for(expr memoryU:*memoryUnitsOfForAllFormula){
		if(mayMemoryUnitIsIn(NewPre,memoryunit,memoryU,clangStmt,count)){
			return true;
		}
	}
	return false;
}
bool mayMemberMemoryUnitIsInPhiFormula(FlowSet* Pre,expr memoryunit,expr phiFormula,const clang::Stmt* clangStmt,int count){
	expr phiBegin=z3coding.getPhiBegin(phiFormula);
	expr phiEnd=z3coding.getPhiEnd(phiFormula);
	expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
	expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
	expr phiStep=z3coding.getPhiStep(phiFormula);
	auto memoryUnits=z3coding.getMemoryUnitsWithQuantifierFormula(phiFormula);
	for(expr memoryU:*memoryUnits){
		if(mayMemoryUnitIsIn(Pre,memoryunit,memoryU,clangStmt,count)){
			return true;
		}
	}
	return false;
}
/**
 * @brief 
 * @param Pre
 * @param memoryunit1
 * @param memoryunit2
 * @param clangStmt
 * @param count
 * @return 
 */
bool mayMemoryUnitIsIn_DerPointer(FlowSet* Pre,expr memoryunit1,expr memoryunit2,const clang::Stmt* clangStmt,int count){
	if(z3coding.isDer_PointerExpr(memoryunit1)&&memoryunit2.is_const()){
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
	}
	else if(memoryunit1.is_const()&&z3coding.isDer_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit2,memoryunit1);
	}
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isDer_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit2,memoryunit1);
	}
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&z3coding.isMemberExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&z3coding.isDer_PointerExpr(memoryunit2)){
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit2,memoryunit1);
	}
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&z3coding.isDer_PointerExpr(memoryunit2)){
		expr access1=memoryunit1.arg(0);
		expr access2=memoryunit2.arg(0);
		expr assert=access1==access2;
		auto ignore=flowSetToExprSet(Pre);
		if(z3coding.prove(ignore.get(),assert)==proved_result::unproved){
			return false;
		}
		return true;
	}
	else{
		cerr<<"LiftAnalysis_FeasiblePath::mayMemoryUnitIsIn_DefPointer,something is wrong!"<<std::endl;
		return true;
	}
	return true;
}
bool mayMemoryUnitIsIn_ArrayAcess_ArrayAcess(FlowSet* Pre,expr memoryunit1,expr memoryunit2){
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
			auto ignore=toExprs(Pre);
			check_result r=z3coding.satisfy(ignore.get(),idxEqualAssert);
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
			auto ingore=toExprs(Pre);
			check_result r=z3coding.satisfy(ingore.get(),idxEqualAssert);
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
			auto ingore=toExprs(Pre);
			check_result r=z3coding.satisfy(ingore.get(),idxEqualAssert);
			if(r==check_result::sat||r==check_result::unknown){
				return true;	
			}
			else {
				return false;
			}
		}
	}
}
/**
 * @brief e.g. link_Indirect(a), link_direct(b)
 * 			e.g. next_direct(a),next_Indirect(b)
 * @param Pre
 * @param memoryunit1
 * @param memoryunit2
 * @return 
 */
bool mayMemoryUnitIsIn_MemberExpr_MemberExpr(FlowSet* Pre,expr memoryunit1,expr memoryunit2,const clang::Stmt* clangStmt,int count){
	//if same Member_funciton,e.g. link(),next()
	
	if(z3coding.getFieldAcessFuncName(memoryunit1.decl())!=z3coding.getFieldAcessFuncName(memoryunit2.decl())){
		return false;
	}
	expr access1=	memoryunit1.arg(0);
	expr access2=	memoryunit2.arg(0);
	if (z3coding.isIndirectMemberExpr(memoryunit1)&&z3coding.isIndirectMemberExpr(memoryunit2)){
		//e1->b,e2->b
		expr assert=access1==access2;
		auto ignore=flowSetToExprSet(Pre);
		if(z3coding.prove(ignore.get(),assert)==proved_result::unproved){
			return false;
		}
		return true;
	}
	else if (z3coding.isIndirectMemberExpr(memoryunit1)&&z3coding.isDirectMemberExpr(memoryunit2)){
		//e1->b,e2.b
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,access1,access2);
	}
	if (z3coding.isDirectMemberExpr(memoryunit1)&&z3coding.isIndirectMemberExpr(memoryunit2)){
		//e1.b,e2->b
		return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,access2,access1);
	}
	else if (z3coding.isDirectMemberExpr(memoryunit1)&&z3coding.isDirectMemberExpr(memoryunit2)){
		//e1.b,e2.b
		return mayMemoryUnitIsIn(Pre,access1,access2,clangStmt,count);
	}
	else{
		cerr<<"LiftAnalysis_FeasiblePath::mayMemoryUnitIsIn_MemberExpr_MemberExpr,something is wrong!"<<std::endl;
		return true;
	}
}
bool mayMemoryUnitIsIn(FlowSet* Pre,expr memoryunit1,expr memoryunit2,const clang::Stmt* clangStmt,int count){
	if(memoryunit1.is_const()&&memoryunit2.is_const()){
		return z3coding.equal(memoryunit1,memoryunit2);
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&memoryunit2.is_const()){
		//memoryunit1:A[i]  memoryunit2:A
		expr base1=z3coding.getArrayBase(memoryunit1);
		return z3coding.equal(base1,memoryunit2);
	}
	else if(memoryunit1.is_const()&&z3coding.isArrayAcess(memoryunit2)){
		auto consts=z3coding.getConsts(memoryunit2);
		for(auto it=consts->begin();it!=consts->end();it++){
			expr con=*it;
			if(z3coding.equal(memoryunit1,con)){
				return true;
			}
		}
		return false;
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		//A[exp] B[exp]
		return mayMemoryUnitIsIn_ArrayAcess_ArrayAcess(Pre,memoryunit1,memoryunit2);
	}
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&memoryunit2.is_const()){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&z3coding.isArrayAcess(memoryunit2)){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else if(memoryunit1.is_const()&&z3coding.isDer_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else if(z3coding.isArrayAcess(memoryunit1)&&z3coding.isDer_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&z3coding.isDer_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
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
	else if(z3coding.isDer_PointerExpr(memoryunit1)&&z3coding.isMemberExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&z3coding.isDer_PointerExpr(memoryunit2)){
		return mayMemoryUnitIsIn_DerPointer(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else if(z3coding.isMemberExpr(memoryunit1)&&z3coding.isMemberExpr(memoryunit2)){
		return mayMemoryUnitIsIn_MemberExpr_MemberExpr(Pre,memoryunit1,memoryunit2,clangStmt,count);
	}
	else{
		std::cerr<<"LiftAnalysis_FeasiblePath:mayMemoryUnitIsIn: something is wrong!"<<std::endl;
		std::cerr<<"error info:: memoryunit1: "<<memoryunit1<<", memoryunit2: "<<memoryunit2 <<std::endl;
		return true;
	}
	return true;
}
bool mayArrayAcessMemoryUnitIsInQuantifierFormula(FlowSet* Pre,expr memoryunit,expr forAllFormula,const clang::Stmt* clangStmt,int count){
	expr memoryunitbase=z3coding.getArrayBase(memoryunit);
	int  memoryunitDim=z3coding.getArrayAcessDimension(memoryunit);
	auto allstepFormulas=z3coding.getAllQuantifierFormulaStepFormulas(forAllFormula);
	auto allbeginformulas=z3coding.getAllQuantifierFormulaBeginFormula(forAllFormula);
	auto allendformulas=z3coding.getAllQuantifierFormulaEndFormula(forAllFormula);
	auto allquantifiers=z3coding.getAllQuantifier(forAllFormula);
	auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(forAllFormula);
	for(expr arrayAcess:*arrayAcesses){
		expr arrayAcessBase=z3coding.getArrayBase(arrayAcess);
		if(mayMemoryUnitIsIn(Pre,memoryunitbase,arrayAcessBase,clangStmt,count)){
			//if exist any quantifier is in arrayAcess
			auto arrayAcessCons=z3coding.getConsts(arrayAcess);
			bool quantifierIsInArrayAcess=false;
			for(expr quantifier: *allquantifiers){
				if(z3coding.isIn(quantifier,arrayAcessCons.get())){
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
					auto ithidxCons=z3coding.getConsts(arrayAcessKthIdx);
					vector<int> isInQuantifierIndex;
					for(unsigned i=0;i<allquantifiers->size();i++){
						expr quantifier=allquantifiers->at(i);
						if(z3coding.isIn(quantifier,ithidxCons.get())){
							isInQuantifierIndex.push_back(i);
						}
					}
					if(isInQuantifierIndex.size()>0){
						//get the max and min of index(x,y...), x and y is the quantifier
						//determine the dim index of memoryunit1 is in the min..max
						vector<expr> quantifierFormulas;
						//expr *parrayAcessKthIdx=&arrayAcessKthIdx;
						for(int quantifierIndex:isInQuantifierIndex){
							//quantifier is not in Pre
							expr quantifier=allquantifiers->at(quantifierIndex);
							expr beginformula=allbeginformulas->at(quantifierIndex);
							expr begin=beginformula.arg(0);
							expr endformula=allendformulas->at(quantifierIndex);
							expr stepFormula=allstepFormulas->at(quantifierIndex);
							auto ingore=toExprs(Pre);
							if(!z3coding.isIn(quantifier,ingore.get())){
								expr qi=beginformula&&endformula&&stepFormula;
								quantifierFormulas.push_back(qi);
							}
							else{
								std::cerr<<"LiftAnalysis_FeasiblePath::mayArrayAcessMemoryUnitIsInQuantifierFormula: something is wrong!"<<std::endl;
							}
						}
						expr satisfyFormula=arrayAcessKthIdx==memoryunitKthIdx;
						vector<expr>  Pres;
						auto tmp=toExprs(Pre);
						z3coding.pushAToB(tmp.get(),&Pres);
						z3coding.pushAToB(&quantifierFormulas,&Pres);

						if(z3coding.satisfy(&Pres,satisfyFormula)==check_result::unsat){
							//continue next arrayAcess
							allArrayAcessDimMayEqual=false;
							break;
						}
					}
					else{
						//quantifier not in kthidx
						expr satisfyFormula=arrayAcessKthIdx==memoryunitKthIdx;
						auto ingore=toExprs(Pre);
						if(z3coding.satisfy(ingore.get(),satisfyFormula)==check_result::unsat){
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
				if(mayMemoryUnitIsIn(Pre,memoryunit,arrayAcess,clangStmt,count)){
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
bool mayArrayAcessMemoryUnitIsInPhiFormula(FlowSet* Pre,expr arrayAcessUnit,expr phiFormula,const clang::Stmt* clangStmt,int count){
	expr phiBegin=z3coding.getPhiBegin(phiFormula);
	expr phiEnd=z3coding.getPhiEnd(phiFormula);
	expr phiBeginFormula=z3coding.getPhiBeginFormula(phiFormula);
	expr phiEndFormula=z3coding.getPhiEndFormula(phiFormula);
	expr phiStep=z3coding.getPhiStep(phiFormula);
	auto arrayAcesses=z3coding.getArrayAcessMemoryUnits(phiFormula);
	for(expr arrayAcess:*arrayAcesses){
		if(mayMemoryUnitIsIn(Pre,arrayAcessUnit,arrayAcess,clangStmt,count)){
			return true;
		}
	}
	return false;
	
}
vector<AtomVariabla*>* indexVariables; 
public:
LiftAnalysis_FeasiblePath(FunctionDecl * functionDecl,clang::CFG* cfg,context &ctx,EnvironmentAnalysis* envAna,AtomVariablaAnalysis* indexAna,
		Z3Coding &z3c,UserSupplied * userSup,MemoryUtil &memoryUtil,PointerAnalysis* pointerAna,C2Z3* c2z3,
		MultiIndexesRelationAnalysis* multiIndexesRelationAna,FeasiblePath* fp):IntraDataFlowAnalysis_FeasiblePath(functionDecl,cfg,fp),c(ctx),
	envAnalysis(envAna),indexAnalysis(indexAna),z3coding(z3c),userSupplied(userSup),mu(memoryUtil),pointerAnalysis(pointerAna),
	c2z3Stmt(c2z3),multiIndexesRelationAnalysis(multiIndexesRelationAna)
	{
		indexVariables=new vector<AtomVariabla*>();
		doAnalysis();
		statistic();
	}
	int forAllFormulaCount=0;
	int existFormulaCount=0;
	int loopEntryforAllFormulaCount=0;
	int loopEntryexistFormulaCount=0;
	int simpleFormulaCount=0;
	int loopCount=0;
	int hasForallFormulaLoopCount=0;
	int hasExistFormulaLoopCount=0;
	int hasForallOrExistFormulaLoopCount=0;
	int hasOrFormulaLoopCount=0;
	vector<CFGBlock*> loopBlocks;
	int blockCount=0;
	void statistic(){
		loopCount=statisticLoops();
		for (std::map<CFGBlock*, FlowSet*>::iterator it=mapToBlockIn.begin(); it!=mapToBlockIn.end(); ++it){
			int fcount=statisticForAllFormula(it->second);
			int ecount=statisticExistFormula(it->second);
			int orcount=statisticOrFormula(it->second);
			for(int i=0;i<(int)loopBlocks.size();i++){
				if(loopBlocks[i]==it->first){
					if(fcount>0){
						hasForallFormulaLoopCount++;
						
					}
					if(ecount>0){
						hasExistFormulaLoopCount++;
						
					}
					if(orcount>0){
						hasOrFormulaLoopCount++;
						
					}
					if(ecount>0||fcount>0){
						hasForallOrExistFormulaLoopCount++;
						
					}
				}
			}
			forAllFormulaCount+=fcount;
			simpleFormulaCount+=statisticSimpleFormula(it->second);
			existFormulaCount+=ecount;
			blockCount++;
		}
	}
	int statisticForAllFormula(FlowSet* S){
		auto v=toExprs(S);
		int count=0;
		for(expr e:*v){
			if(containForallFormula(e)){
				count++;
			}
		}
		return count;
	}
	
	int statisticLoops(){
		for(clang::CFG::iterator it= cfg->begin();it!=cfg->end();it++){
			CFGBlock* b=*it;
			Stmt* s=b->getTerminator().getStmt();
			if(s!=nullptr&&s->getStmtClass()==clang::Stmt::WhileStmtClass) {
				loopBlocks.push_back(b);
			}
			else if(s!=nullptr&&s->getStmtClass()==clang::Stmt::ForStmtClass) {
				loopBlocks.push_back(b);
			}
		}
		return loopBlocks.size();
	}
	int statisticExistFormula(FlowSet* S){
		auto v=toExprs(S);
		int count=0;
		for(expr e:*v){
			if(containExistFormula(e)){
				count++;
			}
		}
		return count;
	}
	int statisticOrFormula(FlowSet* S){
		auto v=toExprs(S);
		int count=0;
		for(expr e:*v){
			if(containOrFormula(e)){
				count++;
			}
		}
		return count;
	}
	bool containForallFormula(expr e){
		if(z3coding.isForAllFormula(e)){
			return true;
		}
		if(z3coding.isOrFormula(e)){
			auto ors=z3coding.splitOrFormulas(e);
			for(expr o:*ors){
				if(z3coding.isForAllFormula(o)){
					return true;
				}
			}
		}
		return false;
	}
	bool containExistFormula(expr e){
		if(z3coding.isExistFormula(e)){
			return true;
		}
		if(z3coding.isOrFormula(e)){
			auto ors=z3coding.splitOrFormulas(e);
			for(expr o:*ors){
				if(z3coding.isExistFormula(o)){
					return true;
				}
			}
		}
		return false;
	}
	bool containOrFormula(expr e){
		if(z3coding.isOrFormula(e)){
			return true;
		}
		return false;
	}
	int statisticSimpleFormula(FlowSet* S){
		auto v=toExprs(S);
		int count=0;
		for(expr e:*v){
			Formula f(e);
			if(userSupplied->isSimpleProperty(&f)){
				count++;
			}
		}
		return count;
	}
void print(){
	for (std::map<CFGBlock*, FlowSet*>::iterator it=mapToBlockIn.begin(); it!=mapToBlockIn.end(); ++it){
		std::cout <<"--------[B"<< it->first->getBlockID ()<<"]" << " in ::--------"<<std::endl; 
		auto tmp=flowSetToExprSet(it->second);
		std::cout<<toString_final(tmp.get(),true)<<std::endl;
		list<pair<CFGBlock*,FlowSet*>*> * outs=mapToBlockOut.at(it->first);
		for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator outsIt = outs->begin(); outsIt != outs->end(); outsIt++){
			pair<CFGBlock*,FlowSet*> *ele=*outsIt;
			if(ele->first==nullptr) continue;
			std::cout <<"----------[B"<< it->first->getBlockID()<<"]"<<"-> [B" <<ele->first->getBlockID()<<"]"<<" out -------:"<<std::endl; 
			auto tmp=flowSetToExprSet(ele->second);
			std::cout<<toString_final(tmp.get(),true)<<std::endl;
		}
	}
}

std::string toString(FlowSet* in){
	if(in->isUniversalSet()){
		return "UniversalSet";
	}
	auto ignore=flowSetToExprSet(in);
	return toString(ignore.get());
}
/*FlowSet * reduce(FlowSet  * in){
	FlowSet * result=userSupplied->newinitialFlow();result->clear(); 
	bool flag;
	vector<Property*>* invec=in->toVector();
	for(Property* p1:* invec){
		Formula* f1=(Formula*)p1;
		flag=false;
		for(Property* p2:* invec){
			Formula* f2=(Formula*)p2;
			cout<<"f1:"<<f1->formula<<", f2:"<<f2->formula<<std::endl;
			if(partialOrderRelation(f2,f1)&&!z3coding.equal(f1->formula,f2->formula)){
				flag=true;
			}
		}
		if(!flag){
			result->add(f1);
		}
	}
	return result;
}*/

FlowSet * reduce(FlowSet  * in){
	FlowSet * result=userSupplied->newinitialFlow();result->clear(); 
	auto invec=in->toVector();
	for(Property* p1:* invec){
		//cout<<"000p1::"<<((Formula*)p1)->formula<<std::endl;
		if(existMoreThan(result,(Formula*)p1)){
			continue;
		}
		else{
			/*if(z3coding.toString(((Formula*)p1)->formula)=="forall _i0 in (j,(- 1),(- i 1)],(not (= (select a i) (select a j)))"){
				cout<<((Formula*)p1)->formula<<std::endl;
				cout<<toString(in)<<std::endl;
			}*/
			auto resultvec=result->toVector();
			vector<Property*> tmp; 
			for(Property* r:* resultvec){
				if(partialOrderRelation((Formula*)p1,(Formula*)r)){
					tmp.push_back(r);
				}
			}
			for(Property* t:tmp){
				result->remove(t);
			}
			//cout<<"add p1::"<<z3coding.toString(((Formula*)p1)->formula)<<std::endl;
			result->add(p1);
		}
	}
	return result;
}
bool existMoreThan(FlowSet * S,Formula* f){
	auto svec=S->toVector();
	for(Property* f2:* svec){
		if(partialOrderRelation((Formula*)f2,f)){
			return true;
		}
	}
	return false;
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
			//cout<<"initZ3Stmt::"<<initZ3Stmt<<std::endl;
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
	/*cout<<toString(in1)<<std::endl;
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
		if(DISJUNCTIONK<=0){
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
		else{
			auto ignore1=toExprs(in1);
			auto ignore2=toExprs(in2);
			unique_ptr<vector<expr>> ret=merge_orFormula(ignore1.get(),ignore2.get());
			out=toFlowSet(ret.get());
		}
	}
#ifdef _DEBUG
	/*cout<<toString(out)<<std::endl;
	cout<<"-------------------"<<std::endl;*/
#endif
}
private:
//当k>0时的merge方法
unique_ptr<vector<expr>> merge_orFormula(vector<expr>* in1,vector<expr>* in2){
	auto orFormulas1Ptr=getAllOrFormula(in1);
	auto orFormulas1=orFormulas1Ptr.get();
	auto orFormulas2Ptr=getAllOrFormula(in2);
	auto orFormulas2=orFormulas2Ptr.get();
	auto simpleFormulas1Ptr=getAllSimpleFormula(in1);
	auto simpleFormulas1=simpleFormulas1Ptr.get();
	auto simpleFormulas2Ptr=getAllSimpleFormula(in2);
	auto simpleFormulas2=simpleFormulas2Ptr.get();
	auto quantifiedFormulas1Ptr=getAllquantifiedFormula(in1);
	auto quantifiedFormulas1=quantifiedFormulas1Ptr.get();
	auto quantifiedFormulas2Ptr=getAllquantifiedFormula(in2);
	auto quantifiedFormulas2=quantifiedFormulas2Ptr.get();
	unique_ptr<vector<expr>> mergeResultPtr(new vector<expr>());
	vector<expr> * mergeResult=mergeResultPtr.get();
	for(expr sf:*simpleFormulas1){
		expr r=merge_orFormula_1(sf,simpleFormulas2);
		if(!z3coding.checkError(r)){
			mergeResult->push_back(r);
			continue;
		}
		auto rs=merge_orFormula_3(sf,orFormulas2);
		if(rs->size()>0){
			z3coding.pushAToB(rs.get(),mergeResult);
			continue;
		}
	}
	for(expr qf:*quantifiedFormulas1){
		auto rs=merge_orFormula_2(qf,quantifiedFormulas2);
		if(rs->size()>0){
			z3coding.pushAToB(rs.get(),mergeResult);
			if(!z3coding.isPhiFormula(qf)){
				continue;
			}
		}
		rs=merge_orFormula_3(qf,orFormulas2);
		if(rs->size()>0){
			z3coding.pushAToB(rs.get(),mergeResult);
			continue;
		}
	}
	for(expr orf:*orFormulas1){
		auto rs=merge_orFormula_4(orf,in2);
		if(rs->size()>0){
			z3coding.pushAToB(rs.get(),mergeResult);
			continue;
		}
	}
	auto ignore=diff(in1,mergeResult);
	auto orFormulaCandidate1=filteringOutPhiFormula(ignore.get());
	ignore=diff(in2,mergeResult);
	auto orFormulaCandidate2=filteringOutPhiFormula(ignore.get());
	auto newOrFormulaPtr=generateOrFormula(orFormulaCandidate1.get(),orFormulaCandidate2.get());
	vector<expr>* newOrFormula=newOrFormulaPtr.get();
	z3coding.pushAToB(newOrFormula,mergeResult);
	return mergeResultPtr;
}
//e1:A,如果e1对存在e2:B满足e1=e2,那么e1不在ret中
unique_ptr<vector<expr>> diff(vector<expr>* A,vector<expr>* B){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	bool flag=false;
	for(expr e1:*A){
		flag=false;
		for(expr e2:*B){
			if(z3coding.equal(e1,e2)){
				flag=true;
				break;
			}
		}
		if(flag!=true){
			ret->push_back(e1);
		}
	}
	return ret;
}

unique_ptr<vector<expr>> generateOrFormula(vector<expr>* in1,vector<expr>* in2){
	/*cout<<"-----------generateOrFormula-------------------"<<std::endl;
	cout<<"--------in1 is ------------"<<std::endl;
	cout<<toString(in1)<<std::endl;
	cout<<"--------in2 is ------------"<<std::endl;
	cout<<toString(in2)<<std::endl;
	if(in1->size()==4&&in2->size()==15){
		cout<<"--------------------"<<std::endl;
	}*/
	unique_ptr<vector<expr>> ret(new vector<expr>());
	for(expr e1:*in1){
		auto dnf1=z3coding.splitOrFormulas(e1);
		for(expr e2:*in2){
			/*cout<<"e1:"<< z3coding.toString(e1)<<std::endl;
			cout<<"e2:"<< z3coding.toString(e2)<<std::endl;*/
			auto dnf2=z3coding.splitOrFormulas(e2);
			/*cout<<"dnf1: "<<dnf1->size()<<std::endl;
			cout<<"dnf2: "<<dnf2->size()<<std::endl;*/
			auto rdnf=Union(dnf1.get(),dnf2.get());
			//cout<<"rdnf: "<<rdnf->size()<<std::endl;
			if(rdnf->size()>DISJUNCTIONK){
				continue;
			}
			else{
				expr orformula=_genOrFormula(rdnf.get());
				//cout<<"orformula:"<< z3coding.toString(orformula)<<std::endl;
				//cout<<"orformula:"<< orformula<<std::endl;
				if(!z3coding.checkError(orformula)){
					ret->push_back(orformula);
				}
			}
		}
	}
	/*cout<<"-----------result is-------------------"<<std::endl;
	cout<<toString(ret)<<std::endl;
	cout<<"--------------------------------------"<<std::endl;*/
	return ret;
}
unique_ptr<vector<expr>> Union(vector<expr>* A,vector<expr>* B){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	z3coding.pushAToB(A,ret.get());
	for(expr e2:*B){
		if(!z3coding.isIn(e2,A)){
			ret->push_back(e2);
		}
	}
	return ret;
}
expr  _genOrFormula(vector<expr>* dnf){
	/*cout<<"dnf is------------------"<<std::endl;
	cout<<z3coding.toString(dnf)<<std::endl;
	cout<<"------------------"<<std::endl;*/
	expr ret(c);
	if(dnf->size()==0){
		cerr<<"LiftAnalasis_FeasiblePath::_genOrFormula::something is wrong!"<<std::endl;
		return z3coding._error;
	}
	ret=dnf->at(0);
	for(int i=1;i<(int)dnf->size();i++){
		//cout<<"ret is: "<<ret<<std::endl;
		ret=ret||dnf->at(i);
	}
	//cout<<"ret is: "<<ret<<std::endl;
	return ret;
}
unique_ptr<vector<expr>> filteringOutPhiFormula(vector<expr>* in){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	for(expr e:*in){
		if(!z3coding.isPhiFormula(e)){
			ret->push_back(e);
		}
	}
	return ret;
}
unique_ptr<vector<expr>> getAllquantifiedFormula(vector<expr>* in){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	for(expr e:*in){
		if(z3coding.isPhiFormula(e)||z3coding.isExistFormula(e)||z3coding.isForAllFormula(e)){
			ret->push_back(e);
		}
	}
	return ret;
}
unique_ptr<vector<expr>> getAllSimpleFormula(vector<expr>* in){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	for(expr e:*in){
		unique_ptr<Formula> ignore(new Formula(e));
		if(userSupplied->isSimpleProperty(ignore.get())){
			ret->push_back(e);
		}
	}
	return ret;
}
unique_ptr<vector<expr>> getAllOrFormula(vector<expr>* in){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	for(expr e:*in){
		if(z3coding.isOrFormula(e)){
			ret->push_back(e);
		}
	}
	return ret;
}
//f是简单公式,in2是简单公式的集合
expr merge_orFormula_1(expr f,vector<expr>* in2){
/*	for(expr f2:*in2){
		if(z3coding.equal(f,f2)){
			return f;
		}
	}
	return z3coding._error;*/
	
	for(expr f2:*in2){
		unique_ptr<Formula> ignore1(new Formula(f));
		unique_ptr<Formula> ignore2(new Formula(f2));
		if(userSupplied->partialOrderRelation(ignore1.get(),ignore2.get())){
			return f2;
		}
		Formula ff1(f2);
		Formula ff(f);
		if(userSupplied->partialOrderRelation(&ff1,&ff)){
			return f;
		}
	}
	return z3coding._error;

}

//f是非or公式,in2是or公式的集合
unique_ptr<vector<expr>> merge_orFormula_3(expr f,vector<expr>* in2){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	Formula ff(f);
	for(expr f2:*in2){
		auto f2dnf=z3coding.splitOrFormulas(f2);
		for(expr d:*f2dnf){
			Formula fd(d);
			if(partialOrderRelation(&ff,&fd)){
				ret->push_back(f2);
			}
		}
	}
	return ret;
}
//f是量词公式,in2是是量词公式的集合
unique_ptr<vector<expr>>  merge_orFormula_2(expr f,vector<expr>* in2){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	if(z3coding.isPhiFormula(f)){
		for(expr f2:*in2){
			if(z3coding.isPhiFormula(f2)){
				if(z3coding.equal(f,f2)){
					ret->push_back(f);
				}
			}
			if(z3coding.isForAllFormula(f2)){
				if(partialOrderRelation_phi_forall(f,f2)){
					ret->push_back(f2);
				}
			}
		}
	}
	if(z3coding.isForAllFormula(f)){
		for(expr f2:*in2){
			if(z3coding.isPhiFormula(f2)){
				if(partialOrderRelation_phi_forall(f2,f)){
					ret->push_back(f);
					return ret;
				}
			}
			if(z3coding.isForAllFormula(f2)){
				if(partialOrderRelation_forall_forall(f,f2)){
					ret->push_back(f2);
					return ret;
				}
				else if(partialOrderRelation_forall_forall(f2,f)){
					ret->push_back(f);
					return ret;
				}
			}
		}
	}
	if(z3coding.isExistFormula(f)){
		for(expr f2:*in2){
			if(z3coding.isExistFormula(f2)){
				if(partialOrderRelation_exist_exist(f,f2)){
					ret->push_back(f2);
					return ret;
				}
				else if(partialOrderRelation_exist_exist(f2,f)){
					ret->push_back(f);
					return ret;
				}
			}
		}
	}
	return ret;
}

//f是or公式,in2是所有公式的集合
unique_ptr<vector<expr>> merge_orFormula_4(expr f,vector<expr>* in2){
	unique_ptr<vector<expr>> ret(new vector<expr>());
	//vector<expr>* fdnf=z3coding.splitOrFormulas(f);
	Formula ff(f);
	for(expr f2:*in2){
		/*vector<expr>* f2dnf=z3coding.splitOrFormulas(f2);
		if(issubseteq(fdnf,f2dnf)){
			ret->push_back(f2);
		}
		else if(issubseteq(f2dnf,fdnf)){
			ret->push_back(f);
			return ret;
		}*/
		Formula ff2(f2);
		if(partialOrderRelation(&ff,&ff2)){
			ret->push_back(f2);
		}
		if(partialOrderRelation(&ff2,&ff)){
			ret->push_back(f);
			return ret;
		}
	}
	return ret;
}
bool issubseteq(vector<expr>* s1,vector<expr>* s2){
	if(s1->size()>s2->size()){
		return false;
	}
	for(expr e1:*s1){
		if(!z3coding.isIn(e1,s2)){
			return false;
		}
	}
	return true;
}

/*
 * 	Refine: when k>0 and statement is cond, we need refine disjunction properties
	For any S ∈ 2ProperPa, Refine(n,S) =
	S ∪{q} 	 	if p∨q ∈S and cond ⇒ ¬p
	Checking &lhs notInE M(p) by using properties of environment analysis
	Example 
	a: {k=0, (∀x.x ∈ [0,1,i),A[x]=0)}
	n: a[j]:=0
	E: {j>i}
	Transfer(n,a)={k=0,(∀x.x ∈ [0,1,i),A[x]=0)}
 * */
	
	FlowSet* refine(FlowSet * in ,expr cond){
		unique_ptr<vector<expr>> ret(new vector<expr>());
		auto exprin=toExprs(in);
		//vector<expr>* orformulas=getAllOrFormula(exprin);
		
		for(expr e: *exprin){
			if(!z3coding.isOrFormula(e)){
				ret->push_back(e);
				continue;
			}
			auto dnfs=z3coding.splitOrFormulas(e);
			vector<expr> newdnfs;
			for(expr d:*dnfs){
				if(userSupplied->isSimpleProperty(new Formula(d))){
					if(z3coding.satisfy(d&&cond)==check_result::unsat){
						continue;
					}
				}
				newdnfs.push_back(d);
			}
			if(newdnfs.size()>0){
				ret->push_back(_genOrFormula(&newdnfs));
			}
		}
		return toFlowSet(ret.get());
		 /*
		 cout<<"######################refine#################"<<std::endl;
		 return in->clone();
		  */
	}
	
	expr meetExistFormula_ExistFormula(expr existFormula1,expr existFormula2){
		if(partialOrderRelation_exist_exist(existFormula1,existFormula2)){
			return existFormula2;
		}
		if(partialOrderRelation_exist_exist(existFormula2,existFormula1)){
			return existFormula1;
		}
		return z3coding._error;
	}
	bool partialOrderRelation_exist_exist(expr existFormula1,expr existFormula2){
		expr existHead1=z3coding.getQuantifierFormulaHead(existFormula1);
		expr existqualifier1=z3coding.getPhiQuantifier(existFormula1);
		expr existHead2=z3coding.getQuantifierFormulaHead(existFormula2);
		expr existqualifier2=z3coding.getQuantifier(existFormula2);
		if(z3coding.equal(existHead1,existHead2)){
			expr body1=z3coding.getQuantifierFormulaBody(existFormula1);
			expr body2=z3coding.getQuantifierFormulaBody(existFormula2);
			Formula fb1(body1);
			Formula fb2(body2);
			return partialOrderRelation(&fb1,&fb2);
		}
		return false;
	}
	bool partialOrderRelation_other_or(expr formula1,expr orFormula){
		int orcount1=z3coding.getOrCount(formula1);
		int orcount2=z3coding.getOrCount(orFormula);
		if(orcount1<orcount2){
			auto f1dnf=z3coding.splitOrFormulas(formula1);
			auto f2dnf=z3coding.splitOrFormulas(orFormula);
			for(expr e1:*f1dnf){
				bool isPhiFlag=z3coding.isPhiFormula(e1);
				bool flag=false;
				for(expr e2:*f2dnf){
					if(isPhiFlag){
						Formula fe1(e1);Formula fe2(e2);
						if(partialOrderRelation(&fe1,&fe2)){
							flag=true;
							break;
						}
					}
					else{
						if(z3coding.equal(e1,e2)){
							flag=true;
							break;
						}
					}
				}
				if(flag==false){
					return false;
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
};
#endif

