#ifndef _SimplePropertiesRelationAnalysis_H
#define _SimplePropertiesRelationAnalysis_H
#include <vector>
#include "clang/AST/Expr.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/Analysis/CFG.h"
#include "z3++.h"
#include "DataFlowAnalysis.h"
#include "ValueListSetWithUniversalSet.h"
#include "C2Z3.h"

using namespace z3;
/**
 * @class PointerAnalysis
 * @author ubuntu15.10_x64
 * @date 16/06/16
 * @file PointerAnalysis.h
 * @brief 
		分析局部变量是否被任何其他内存单元指向，即分析局部变量是否有别名
		性质：alias(v)：v有别名； non-alias(v)：v没有别名
 
 */
class SimplePropertiesRelationAnalysis: public IntraDataFlowAnalysis{
	
private:
	context &c;
	Z3Coding &z3coding;
	C2Z3* c2z3Stmt;
	map<const clang::Stmt*, FlowSet*> mapToStmtIn;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtOut;
	
	MemoryUtil & mu;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprIn;
	map<const clang::Stmt*, vector<vector<FlowSet*>*>*> mapToStmtExprOut;
	
	void pushAToB(vector<Property*>* &A,vector<Property*>* &B){
		for(Property* p1:*A){
			B->push_back(p1);
		}
	}
	FlowSet* PropertySetToFlowSet(vector<Property*>* S){
		FlowSet* ret=new ValueListSetWithUniversalSet();
		for(Property* p:*S){
			ret->add(p);
		}
		return ret;
	}
	std::string toString(vector<Property*>* S){
		return z3coding.toString(toExprs(S));
	}
	
	void printFlowSets(vector<FlowSet*>* vs){
		unsigned count=0;
		for(FlowSet* f:*vs){
			count++;
			cout<<"--------"<<count<<"---------"<<std::endl;
			f->print();
		}
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
	
	void initmapToStmtExprInAndOut(const clang::Stmt* stmt,vector<expr> * stmtFormulas){
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
	}

	vector<Property*> * GenAndKill(vector<Property*> * Pre,const clang::Stmt* stmt){
		#ifdef _DEBUG
		cout<<"stmt:: "<<z3coding.toString(stmt)<<std::endl;
		cout<<"Pre:: "<<toString(Pre)<<std::endl;
		#endif
		//------------stmt to formulasStmt---------------------------------------------
		vector<expr> *stmtFormulas=new vector<expr>();
		vector<expr> * tmp=c2z3Stmt->getZ3Stmts(stmt);
		if(tmp==nullptr){
			return new vector<Property*>();
		}
		if(tmp->size()<=0){
			vector<Property*> * ret=new vector<Property*>();
			pushAToB(Pre,ret);
			return ret;
		}
		z3coding.pushAToB(tmp,stmtFormulas);
		//------------init mapToStmtExprIn&init mapToStmtExprOut---------------------------------------------		
		initmapToStmtExprInAndOut(stmt,stmtFormulas);
		//process
		vector<Property*> * _Pre=Pre;
		for(unsigned i=0;i<stmtFormulas->size();i++){
			mapToStmtExprIn.at(stmt)->at(i)->clear();
			mapToStmtExprIn.at(stmt)->at(i)->Union(PropertySetToFlowSet(_Pre));
			expr stmtF=stmtFormulas->at(i);
			
			_Pre=Pos(stmtF,_Pre,stmt,i);
			
			if(mapToStmtExprOut.at(stmt)->size()==1){
				mapToStmtExprOut.at(stmt)->at(0)->at(i)->clear();
				mapToStmtExprOut.at(stmt)->at(0)->at(i)->Union(PropertySetToFlowSet(_Pre));
			}
			if(mapToStmtExprOut.at(stmt)->size()==2){
				mapToStmtExprOut.at(stmt)->at(0)->at(i)->clear();
				mapToStmtExprOut.at(stmt)->at(0)->at(i)->Union(PropertySetToFlowSet(_Pre));
				mapToStmtExprOut.at(stmt)->at(1)->at(i)->clear();
				mapToStmtExprOut.at(stmt)->at(1)->at(i)->Union(PropertySetToFlowSet(_Pre));
			}
		}
		#ifdef _DEBUG
			cout<<"Pos:: "<<toString(_Pre)<<std::endl;
		#endif
		return _Pre;
	}

	vector<Property*> * GenAndKillTerminator(vector<Property*> * Pre,const clang::Stmt* T, bool trueOrFalse){
		#ifdef _DEBUG
		cout<<"stmt:: "<<z3coding.toString(T)<<std::endl;
		cout<<"Pre:: "<<toString(Pre)<<std::endl;
		#endif
		//------------stmt to  formulasStmt---------------------------------------------
		vector<expr> *stmtFormulas=new vector<expr>();
		vector<expr> * tmp=c2z3Stmt->getZ3Stmts(T);
		if(tmp==nullptr){
			return new vector<Property*>();
		}
		if(tmp->size()<=0){
			vector<Property*> * ret=new vector<Property*>();
			pushAToB(Pre,ret);
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
		//------------init mapToStmtExprIn&init mapToStmtExprOut---------------------------------------------
		initmapToStmtExprInAndOut(T,tmp);
		
		vector<Property*> * _Pre=Pre;
		for(unsigned i=0;i<stmtFormulas->size();i++){
			mapToStmtExprIn.at(T)->at(i)->clear();
			mapToStmtExprIn.at(T)->at(i)->Union(PropertySetToFlowSet(_Pre));
			expr stmtF=stmtFormulas->at(i);
			
			_Pre=Pos(stmtF,_Pre,T,i);
			
			if(trueOrFalse==true){
				mapToStmtExprOut.at(T)->at(0)->at(i)->clear();
				mapToStmtExprOut.at(T)->at(0)->at(i)->Union(PropertySetToFlowSet(_Pre));
			}
			else{
				mapToStmtExprOut.at(T)->at(1)->at(i)->clear();
				mapToStmtExprOut.at(T)->at(1)->at(i)->Union(PropertySetToFlowSet(_Pre));
			}
		}
		#ifdef _DEBUG
			cout<<"Pos:: "<<toString(_Pre)<<std::endl;
		#endif
		return _Pre;
	}
	
public:
	SimplePropertiesRelationAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,context &ctx,Z3Coding &coding,C2Z3* c2z3,
	MemoryUtil & memoryUtil)
	:IntraDataFlowAnalysis(functionDecl,cfg),c(ctx),z3coding(coding),c2z3Stmt(c2z3),mu(memoryUtil){
		pre_init();
		pre_init_stmtExpr();
		doAnalysis();
	}


	void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
		//cout<<"processing ... "<<n->getBlockID()<<std::endl;
		for(auto it=outs->begin();it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*>* ele=*it;
			if(ele->second->isUniversalSet()){
				ele->second->setNonUniversalSetWhenIsUniversalSet();
			}
		}
		
		auto PrePtr=in->toVector();			
		auto Pre=PrePtr.get();
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
					if(n->size()>0&&count==n->size()-1){
						T=it;
						break;
					}
					//cout<<toString(it)<<std::endl;
					FlowSet* pin=mapToStmtIn.at(it);
					pin->clear();
					pin->Union(PropertySetToFlowSet(Pre));
					
					Pre=GenAndKill(Pre,it);
					
					vector<FlowSet*>* pout=mapToStmtOut.at(it);
					pout->at(0)->clear();
					pout->at(0)->Union(PropertySetToFlowSet(Pre));
					
					count++;
				}
			}
			FlowSet* pin=mapToStmtIn.at(T);
			pin->clear();
			pin->Union(PropertySetToFlowSet(Pre));
			
			vector<Property*> * truePos=GenAndKillTerminator(Pre,T,true);
			vector<Property*> * falsePos=GenAndKillTerminator(Pre,T,false);
			
			vector<FlowSet*>* pout=mapToStmtOut.at(T);
			pout->at(0)->clear();pout->at(1)->clear();
			pout->at(0)->Union(PropertySetToFlowSet(truePos));
			pout->at(1)->Union(PropertySetToFlowSet(falsePos));
			
			pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
			ValueListSetWithUniversalSet *tureFlow=(ValueListSetWithUniversalSet*)tureBranch->second;
			pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
			ValueListSetWithUniversalSet *falseFlow=(ValueListSetWithUniversalSet*)falseBranch->second;
			
			FlowSet * trueFlowSet=PropertySetToFlowSet(truePos);
			tureFlow->Union(trueFlowSet);
			
			FlowSet * falseFlowSet=PropertySetToFlowSet(falsePos);
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
					FlowSet* pin=mapToStmtIn.at(it);
					pin->clear();
					pin->Union(PropertySetToFlowSet(Pre));
					
					Pre=GenAndKill(Pre,it);
					
					vector<FlowSet*>* pout=mapToStmtOut.at(it);
					pout->at(0)->clear();
					pout->at(0)->Union(PropertySetToFlowSet(Pre));
				}
			}
			pair<CFGBlock*,FlowSet*>* out=outs->front();
			ValueListSetWithUniversalSet *outFlow=(ValueListSetWithUniversalSet*)out->second;

			FlowSet * flowSet=PropertySetToFlowSet(Pre);
			outFlow->Union(flowSet);
		}
	}

	void print(){
		for (std::map<CFGBlock*, FlowSet*>::iterator it=mapToBlockIn.begin(); it!=mapToBlockIn.end(); ++it){
			std::cout <<"--------[B"<< it->first->getBlockID ()<<"]" << " in :--------"<<std::endl;
			auto ign1=it->second->toVector(); 
			cout<<toString(ign1.get())<<std::endl;
			list<pair<CFGBlock*,FlowSet*>*> * outs=mapToBlockOut.at(it->first);
			for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator outsIt = outs->begin(); 
									outsIt != outs->end(); outsIt++){
				pair<CFGBlock*,FlowSet*> *ele=*outsIt;
				if(ele->first==nullptr) continue;
				std::cout <<"----------[B"<< it->first->getBlockID()<<"]"<<"-> [B" <<ele->first->getBlockID()<<"]"<<" out -------:"<<std::endl; 
				auto ign2=ele->second->toVector();
				cout<<toString(ign2.get())<<std::endl;
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
		auto ign1=in1->toVector();
		auto ign2=in2->toVector();
		out=meet(ign1.get(),ign2.get());
		return;
	}
	
	FlowSet * newinitialFlow(){return new ValueListSetWithUniversalSet(true);}
	FlowSet * entryInitialFlow(){return new ValueListSetWithUniversalSet();}
	
	virtual FlowSet * meet(vector<Property*>* in1,vector<Property*>* in2){
		FlowSet * ret=new ValueListSetWithUniversalSet();
		for(Property * p1:*in1){
			for(Property * p2:*in2){
				Formula *f1=(Formula *)p1;
				Formula *f2=(Formula *)p2;
				Formula * r=_simpleFormulaMeet(f1,f2);
				if(!z3coding.equal(r->formula,z3coding._error)){
					ret->add(r);
				}
			}
		}	
		return ret;
	}
	Formula * _simpleFormulaMeet(Formula * f1,Formula *f2){
			expr e1= f1->formula;
			expr e2= f2->formula;
			return new Formula(_simpleFormulaMeet(e1,e2));
		}
		expr _simpleFormulaMeet(expr e1,expr e2){
			/*if(e1.is_app()&&e2.is_app()){
				if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
						return e1l==e1r;
					}
					else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
						return e1l==e1r;
					}
					else{
						return z3coding._error;
					}
				}
			}
			return z3coding._error;*/
			return meet(e1,e2);
		}
		expr meet(expr e1,expr e2){
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.EqDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l==e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l==e1r;
						}
						else{
							return z3coding._error;
						}

					}
					
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1r<=e1l;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1r<=e1l;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						return z3coding._error;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LtDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l<=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LeDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l<=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						return z3coding._error;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				else if(z3coding.isNe(e1)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return z3coding._error;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return z3coding._error;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.DistinctDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
			}
			return z3coding._error;
		}
	
	vector<Property*> * Pos(expr stmt,vector<Property*>* in,const clang::Stmt* clangStmt,int count){
		FlowSet* out=new ValueListSetWithUniversalSet();
		//cout<<"stmt is "<<stmt<<std::endl;
		//(_AS (= (def_pointer__prime (- dest 1)) (def_pointer (- src 1))))
		//kill 
		if(z3coding.isAssignment(stmt)){
			expr tmpstmt=stmt.arg(0);
			expr left=tmpstmt.arg(0);
			//cerr<<"111 left is "<<left<<std::endl;
			for(Property* p:*in){
				Formula* f=(Formula*)p;
				if(!mu.mayMemoryUnitIsInFormula(toExprs(in),z3coding.unprimedDecline(left),f->formula,clangStmt,count)){
					out->add(new Formula(f->formula));
				}
			}
		}
		else{
			for(Property* p:*in){
				Formula* f=(Formula*)p;
				//cout<<"222 f->formula is "<<f->formula<<std::endl;
				out->add(new Formula(f->formula));
			}
		}
		//gen
		expr stmtP=genProperty(stmt,in,clangStmt,count);
		if(!z3coding.checkError(stmtP)){
			out->add(new Formula(z3coding.unprimedDecline(stmtP)));
			out=powerClosure(z3coding.unprimedDecline(stmtP),out);
		}
		vector<Property*> * ret=new vector<Property*>();
		for(Property* p:*out->toVector()){
			ret->push_back(p);
		}
		return ret;
	}
	bool closureEqOptimizingStrategy(expr eq,expr formula){
		expr eqleft=eq.arg(0);
		expr eqright=eq.arg(1);
		if(eqleft.is_numeral()||eqright.is_numeral()){
			return true;
		}
		return false;
	}
	vector<expr> * closureEq(expr eq,expr formula){
		vector<expr>* result=new vector<expr>();
		expr eqleft=eq.arg(0);
		expr eqright=eq.arg(1);
		expr eleft(c);
		expr eright(c);
		expr tmp=formula;
		if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
			tmp=formula.arg(0);
		}
		else if(Z3_is_eq_func_decl(c,tmp.decl(),z3coding.LtDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.LeDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.EqDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.GtDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.GeDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.DistinctDecl)){
			eleft=tmp.arg(0);
			eright=tmp.arg(1);
		}
		else{
			return result;
		}
		
		
		if(z3coding.equal(eqleft,eleft)&&!z3coding.equal(eqright,eright)){
			//expr newe=z3coding.substitute(formula,eqleft,eqright);
			/*when eq is a=e, formula is a< a+a+a+a, e+e+e+e will occur,however, e+e+e+e is not in properExpr
			 *e< e+e+e+e is not a proper property*/
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eqright<eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eqright<=eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eqright==eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eqright>eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eqright>=eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eqright!=eright;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
		if(z3coding.equal(eqleft,eright)&&!z3coding.equal(eqright,eleft)){
			//expr newe=z3coding.substitute(formula,eqleft,eqright);
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eleft<eqright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eleft<=eqright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eleft==eqright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eleft>eqright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eleft>=eqright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eleft!=eqright;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
		if(!z3coding.equal(eqleft,eleft)&&z3coding.equal(eqright,eright)){
			//expr newe=z3coding.substitute(formula,eqright,eqleft);
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eleft<eqleft;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eleft<=eqleft;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eleft==eqleft;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eleft>eqleft;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eleft>=eqleft;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eleft!=eqleft;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
		if(!z3coding.equal(eqleft,eright)&&z3coding.equal(eqright,eleft)){
			//expr newe=z3coding.substitute(formula,eqright,eqleft);
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eqleft<eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eqleft<=eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eqleft==eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eqleft>eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eqleft>=eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eqleft!=eright;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
			
		return result;
	}
	vector<expr> * closureLtLet(expr lt1,expr ltOrLe2){
		vector<expr>* result=new vector<expr>();
		expr lt1left=lt1.arg(0);
		expr lt1right=lt1.arg(1);
		expr lt2left=ltOrLe2.arg(0);
		expr lt2right=ltOrLe2.arg(1);
		if(z3coding.equal(lt1right,lt2left)){
			result->push_back(lt1left<lt2right);
		}
		if(z3coding.equal(lt1left,lt2right)){
			result->push_back(lt2left<lt1right);
		}
		return result;
	}
	vector<expr> * closureLeLe(expr le1,expr le2){
		vector<expr>* result=new vector<expr>();
		expr le1left=le1.arg(0);
		expr le1right=le1.arg(1);
		expr le2left=le2.arg(0);
		expr le2right=le2.arg(1);
		if(z3coding.equal(le1right,le2left)){
			result->push_back(le1left<=le2right);
		}
		if(z3coding.equal(le1left,le2right)){
			result->push_back(le2left<=le1right);
		}
		return result;
	}
	
	vector<expr> * closure(expr e1,expr e2){
		e1=z3coding.eliminateNotInSimpleFormula(e1);
		e2=z3coding.eliminateNotInSimpleFormula(e2);
		e1=z3coding.eliminateGtAndGe(e1);
		e2=z3coding.eliminateGtAndGe(e2);
		//cout<<e1<<"::"<<e2<<std::endl;
		vector<expr>* result=new vector<expr>();
		if(!e1.is_app()||!e2.is_app()) {
			std::cerr<<"UserSuppliedInstancOfRelation:closure: something is wrong!"<<std::endl;
			std::cerr<<"error info: e1 is: "<<e1<<", e2 is: "<<e2<<std::endl;
			return result;
		}
		
		if(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.EqDecl)){
			if(closureEqOptimizingStrategy(e1,e2)) return result;
			vector<expr>* tmp=closureEq(e1,e2);
			z3coding.pushAToB(tmp,result);
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.EqDecl)){
			if(closureEqOptimizingStrategy(e2,e1)) return result;
			vector<expr>* tmp=closureEq(e2,e1);
			z3coding.pushAToB(tmp,result);
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LtDecl)
		&&(Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LeDecl))){
			vector<expr>* tmp=closureLtLet(e1,e2);
			z3coding.pushAToB(tmp,result);
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LtDecl)
		&&(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LeDecl))){
			vector<expr>* tmp=closureLtLet(e2,e1);
			z3coding.pushAToB(tmp,result);
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LeDecl)&&Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LeDecl)){
			vector<expr>* tmp=closureLeLe(e1,e2);
			z3coding.pushAToB(tmp,result);
		}
		return result;
	}
	
	/**
	 * @brief return formulas closure about Lt
	 * @param Lt
	 * @param formulas
	 * @return 
	 */
	/*FlowSet* closureLt(expr lt,FlowSet* formulas){
		if(!(lt.is_app()&&Z3_is_eq_func_decl(c,lt.decl(),z3coding.LtDecl))) {
			std::cerr<<"UserSuppliedInstancOfRelation:closureLt: something is wrong!"<<std::endl;
			return nullptr;
		}
		expr left=lt.arg(0);
		expr right=lt.arg(1);
		vector<Property*>* formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		expr ltleft=eq.arg(0);
		expr ltright=eq.arg(1);
		for(Property* p:*formulasVector){
			Formula* f=(Formula*)p;
			expr e=f->formula;
			if(z3coding.isSimpleFormula(e)){
				vector<expr> * tmp=closure(lt,e);
				add(tmp,out);
			}
		}
		out->Union(formulas);
		return out;
	}*/
	FlowSet* closure(expr e,FlowSet* formulas){
		if(!e.is_app()) {
			std::cerr<<"UserSuppliedInstancOfRelation:closure: something is wrong!"<<std::endl;
			std::cerr<<"error info: e is: "<<e<<std::endl;
			return nullptr;
		}
		auto formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		for(Property* p:*formulasVector){
			Formula* f=(Formula*)p;
			expr t=f->formula;
			if(z3coding.isSimpleFormula(t)){
				vector<expr> * tmp=closure(e,t);
				add(tmp,out);
			}
		}
		out->Union(formulas);
		return out;
	}
//	FlowSet* _closure(expr e,FlowSet* formulas){
//		if(!e.is_app()) {
//			std::cerr<<"UserSuppliedInstancOfRelation:closure: something is wrong!"<<std::endl;
//			std::cerr<<"error info: e is: "<<e<<std::endl;
//			return nullptr;
//		}
//		vector<Property*>* formulasVector=formulas->toVector();
//		FlowSet* out=new ValueListSetWithUniversalSet();
//		for(Property* p:*formulasVector){
//			Formula* f=(Formula*)p;
//			expr t=f->formula;
//			if(z3coding.isSimpleFormula(t)){
//				vector<expr> * tmp=closure(e,t);
//				add(tmp,out);
//			}
//		}
//		return out;
//	}
	FlowSet* powerClosure(expr e,FlowSet* formulas){
		if(!e.is_app()) {
			std::cerr<<"UserSuppliedInstancOfRelation:powerClosure: something is wrong!"<<std::endl;
			std::cerr<<"error info: e is: "<<e<<std::endl;
			return nullptr;
		}
		auto formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		vector<expr>* queue=new vector<expr>();
		queue->push_back(e);
		while(queue->size()!=0){
			expr cur=queue->back();queue->pop_back();
			//cout<<"cur is: "<<cur<<std::endl;
			for(Property* p:*formulasVector){
				Formula* f=(Formula*)p;
				expr t=f->formula;
				if(z3coding.isSimpleFormula(t)){
					vector<expr> * tmp=closure(cur,t);
					for(expr t:*tmp){
						if(!isIn(t,queue)&&!isIn(t,out)&&!isIn(t,formulas)&&!z3coding.equal(t,cur)){
							queue->push_back(t);
						}
					}
					add(tmp,out);
				}
			}		
		}
		out->Union(formulas);
		return out;
	}
	bool isIn(expr f,vector<expr>* vs){
		return z3coding.isIn(f,vs);
	}
	bool isIn(expr f,FlowSet* B){
		auto BVector=B->toVector();
		vector<expr>* vs=toExprs(BVector.get());
		return z3coding.isIn(f,vs);
	}
	/**
	 * @brief add A to B
	 * @param A
	 * @param B
	 * @return 
	 */
	void add(vector<expr> * A,FlowSet* B){
		for(expr e:*A){
			B->add(new Formula(e));
		}
	}
	void add(vector<expr> * A,vector<expr> *B){
		for(expr e:*A){
			if(!isIn(e,B)){
				B->push_back(e);
			}
		}
	}
		bool isEquation(vector<Property*>* env,expr e,const clang::Stmt* clangStmt,int count){
		if(e.is_app()&&e.decl().name().str()=="="){
			expr left=e.arg(0);
			expr right=e.arg(1);
			//cout<<"left is "<<left<<std::endl;
			//cout<<"right is "<<right<<std::endl;
			if(mu.mayMemoryUnitIsInFormula(toExprs(env),z3coding.unprimedDecline(left),right,clangStmt,count)){
				return false;
			}
		}
		return true;
	}
	vector<expr>* toExprs(vector<Property*>* env){
		vector<expr>* ret=new vector<expr>();
		for(Property * p:*env){
			Formula* f =(Formula*)p;
			ret->push_back(f->formula);
		}
		
		return ret;
	}
	expr genProperty(expr stmt,vector<Property*>* env,const clang::Stmt* clangStmt,int count){
		if(z3coding.isAssignment(stmt)){
			if(isEquation(env,stmt.arg(0),clangStmt,count)){
				return stmt.arg(0);
			}
			//if *e1:=*e2 or e1[e2]:=e3[e4], return *e1=*e2 or e1[e2]=e3[e4]
			expr lhs=stmt.arg(0).arg(0);
			expr rhs=stmt.arg(0).arg(1);
			if(z3coding.isArrayAcess(rhs)||z3coding.isDer_PointerExpr(rhs)){
				return stmt.arg(0);
			}
			
			return z3coding._error;
		}
		else{
			return stmt;
		}
	}
		bool isSimpleProperty(Formula* f){
		return z3coding.isSimpleFormula(f->formula);
	}
	bool partialOrderRelation(Formula* f1,Formula* f2){
		expr e1= f1->formula;
		expr e2= f2->formula;
		//return z3coding.equal(e1,e2);
		return partialOrderRelation_SimpleFormula_SimpleFormula(e1,e2);
	}
	//whether f1 can implies f2
	bool partialOrderRelation_SimpleFormula_SimpleFormula(expr f1,expr f2){
			expr e1=f1;
			expr e2=f2;
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.EqDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						return false;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LtDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LtDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LeDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(z3coding.isNe(e2)){
						return false;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				if(z3coding.isNe(e1)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.DistinctDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
			}

			return false;

	}
	
	/*bool _partialOrderRelation_SimpleFormula_SimpleFormula(expr f1,expr f2){
			expr e1=f1;
			expr e2=f2;
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			unsigned e1hash=e1.decl().hash();
			unsigned e2hash=e2.decl().hash();
			unsigned Eqhash=z3coding.EqDecl.hash();
			unsigned Lthash=z3coding.LtDecl.hash();
			unsigned Lehash=z3coding.LeDecl.hash();
			unsigned Distincthash=z3coding.DistinctDecl.hash();
			
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(e1hash==Eqhash){
					if(e2hash==Eqhash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						return false;
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						return false;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				if(e1hash==Lthash){
					if(e2hash==Eqhash){
						return false;
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(e1hash==Lehash){
					if(e2hash==Eqhash){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						return false;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				if(z3coding.isNe(e1)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.DistinctDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
			}

			return false;

	}*/
	std::string toString(FlowSet* in){
		if(in->isUniversalSet()){
			return "UniversalSet";
		}
		return z3coding.toString(flowSetToExprSet(in));
	}
	vector<expr> * flowSetToExprSet(FlowSet * flowSet){
		auto propertySet=flowSet->toVector();
		vector<expr> * exprSet=new vector<expr>();
		for(Property* p: *propertySet){
			Formula *f=(Formula *)p;
			exprSet->push_back(f->formula);
		}
		return exprSet;
	}
};
#endif
	