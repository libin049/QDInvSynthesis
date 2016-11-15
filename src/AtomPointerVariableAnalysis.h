#ifndef _AtomPointerVariableAnalysis_H
#define _AtomPointerVariableAnalysis_H
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
using namespace z3;

extern  bool occurError;

class AtomPointerVariabla : public Property{
public:
	context &c;
	Z3Coding &z3coding;
	const clang::Stmt *indexInitStmt;
	expr pointerVarz3coding;
	expr stepz3coding;
	expr initz3coding;
	bool isIn(const clang::Stmt* s,vector<const clang::Stmt*>* vs){
		for(const clang::Stmt* ele:*vs){
			if(ele==s){
				return true;
			}
		}
		return false;
	}

	AtomPointerVariabla(context &ctx,Z3Coding &coding, const clang::Stmt *indexInitStmt):c(ctx),z3coding(coding),pointerVarz3coding(c)
				,stepz3coding(c),initz3coding(c){
		this->indexInitStmt=indexInitStmt;
		vector<expr> * tmp=z3coding.boolSortFiltering(z3coding.clangStmtToZ3Expr(indexInitStmt));
		pointerVarz3coding=z3coding.unprime(indexInitStmtz3coding.arg(0));
		initz3coding=indexInitStmtz3coding.arg(1);
		stepz3coding=z3coding._error;
	}
	bool hasStep(){
		if(z3coding.checkError(stepz3coding)){
			return false;
		}
		return true;
	}
	void setStep(expr step){
		stepz3coding=step;
	}
	expr getStepFromIndexUpdate(expr stmt){
		if(stmt.arg(1).decl().name().str()=="+"){
			return stmt.arg(1).arg(1);
		}
		else if(stmt.arg(1).decl().name().str()=="-"){
			return -stmt.arg(1).arg(1);
		}
		else{
			std::cerr<<"getStepFromIndexUpdate: something is wrong!"<<std::endl;
			return z3coding._error;
		}
	}

	bool checkScalaVaribale(expr pointerVaribale){
		return z3coding.equal(pointerVarz3coding,pointerVaribale);
	}
	bool checkUpdateStmt(expr updateStmt){
		expr pointerVaribale=z3coding.unprime(updateStmt.arg(0));
		if(checkScalaVaribale(pointerVaribale)){
			if(z3coding.mostPower_equal(this->stepz3coding,getStepFromIndexUpdate(updateStmt))){
				return true;
			}
		}
		return false;
	}
	
	bool equal(Property *p){
		return p==this;
	}
	std::string toString(){
		std::string ret="init: ";
		ret+=Z3_ast_to_string(c,initz3coding);
		if(hasStep()){
			std::string stepStr=Z3_ast_to_string(c,stepz3coding);
			ret+=", step: "+stepStr; 
		}
		return ret;
	}
	AtomVariabla* clone(){
		return this;
	}
	
};

class AtomPointerVariableAnalysis: public IntraDataFlowAnalysis{
	ValueListSet universalSet;
	context &c;
	Z3Coding &z3coding;
	/*if exist atomic scalar at a point,then we backfill that, at init of the atom scalar, it's step is what */
	void backfill(){
		for (map<const clang::Stmt*, FlowSet*>::iterator it=mapToStmtOut.begin(); it!=mapToStmtOut.end(); ++it){
			FlowSet * out=it->second;
			ValueListSet* vlsOut=(ValueListSet*)out;
			for(Property* p: vlsOut->elements){
				AtomPointerVariabla * av=(AtomPointerVariabla *)p;
				if(av->hasStep()){
					if(mapToStmtOut.count(av->indexInitStmt)<=0){
						continue;
					}
					FlowSet* out=mapToStmtOut.at(av->indexInitStmt);
					ValueListSet* vlsOut=(ValueListSet*)out;
					for(Property* p: vlsOut->elements){
						AtomPointerVariabla * avx=(AtomPointerVariabla *)p;
						if(avx->indexInitStmt==av->indexInitStmt&&!avx->hasStep()){
								avx->setStep(av->stepz3coding);
						}
					}
				}
			}
		}

	}
	
public:
	map<const clang::Stmt*, FlowSet*> mapToStmtIn;
	map<const clang::Stmt*, FlowSet*> mapToStmtOut;
	
	void pre_init(){
		for(CFG::iterator it=cfg->begin();it!=cfg->end();++it){
			CFGBlock* n=*it;
			for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
				CFGElement element=(*iterblock);
				if(element.getKind()==CFGElement::Kind::Statement){
					const Stmt* it=((CFGStmt*)&element)->getStmt();
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSet()));
				}
			}
			if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtIn.count(T)<=0){
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSet()));
				}
			}
		}
	}
	AtomPointerVariableAnalysis(clang::CFG* cfg,context &ctx,Z3Coding &coding):IntraDataFlowAnalysis(cfg),c(ctx),z3coding(coding){
		pre_init();
		doAnalysis();
		backfill();
	}
	~AtomPointerVariableAnalysis(){}
	FlowSet * newinitialFlow(){
		return &universalSet; 
	}
	FlowSet * entryInitialFlow(){return new ValueListSet();}
	
	void merge(FlowSet  * &in1,FlowSet  *&in2,FlowSet  *&out){
		if(in1==&universalSet&&in2==&universalSet) {
		#ifdef _DEBUG
			std::cout<<"universalSet merge universalSet"<<std::endl;
		#endif
			out=&universalSet;
			return;
		}
		if(in1==&universalSet){
		#ifdef _DEBUG
			std::cout<<"universalSet merge "<<in2->toString()<<std::endl;
		#endif
			out=in2->clone();
			return;
		}
		if(in2==&universalSet) {
		#ifdef _DEBUG
			std::cout<<"universalSet merge "<<in1->toString()<<std::endl;
		#endif
			out=in1->clone();
			return;
		}
	#ifdef _DEBUG
		std::cout<<in1->toString()<<"--- merge---"<<in2->toString()<<std::endl;
	#endif
		out=new ValueListSet();
		ValueListSet* vlsIn1=(ValueListSet*)in1;
		ValueListSet* vlsIn2=(ValueListSet*)in2;
		for(Property * p1: vlsIn1->elements){
			for(Property * p2: vlsIn2->elements){
				AtomPointerVariabla* r=meet((AtomPointerVariabla*)p1,(AtomPointerVariabla*)p2);
				if(r!=nullptr){
					out->add(r);
				}
			}
		}
		return;
	}
	AtomPointerVariabla* meet(AtomPointerVariabla* in1,AtomPointerVariabla* in2){
		if(in1->indexInitStmt!=in2->indexInitStmt){
			return nullptr;
		}
		if(!in1->hasStep()){
			return in2->clone();
		}
		if(!in2->hasStep()){
			return in1->clone();
		}
		if(!z3coding.equal(in1->stepz3coding,in2->stepz3coding)){
			return nullptr;
		}
		else{
			return in1->clone();
		}
	}
	bool isAssigndStmt(expr stmt){
			if(stmt.is_app()){
				if(stmt.decl().name().str()=="="){
					expr lhs=stmt.arg(0);
					if(z3coding.isPrimedVariable(lhs)){
						return true;
					}
				}
			}
			return false;
	}
	bool isAtomPointerInitStmt(expr stmt){
		if(isAssigndStmt(stmt)){
			expr pointerVar=z3coding.unprime(stmt.arg(0));
			if(pointerVar.is_array()&&!z3coding.isIn(pointerVar,z3coding.getConsts(stmt.arg(1)))){
				return true;
			}
			return false;
		}
		return false;
	}
	//since we regard one-pointer type as one-array type
	//and regard p++ as p_i'=p_i+1
	//hence, clang stmt p++ is encoded to z3 expr: p_i'=p_i+1 
	//_i'=_i+c, _i mean pointer index
	bool isAtomPointerUpdateStmt(expr stmt){
		if(isAssigndStmt(stmt)){
			expr pointerindex=z3coding.unprime(stmt.arg(0));
			if(z3coding.isPointerIndex(pointerindex)&&z3coding.isIn(pointerindex,z3coding.getConsts(stmt.arg(1))))
				return true;
			}
		}
		return false;
	}
	
	//gen=
	//	<p,p@0,top> if n is decl p	
	//	<p,q,top> if n is p=q	
	//	<p,q,c>   if n is p_i=p_i+c and <p,init,c or T>  
	
	//kill=<p,q,*>   if n is v=e and v=p or p_i or v=q or v=q_i
	FlowSet * GenAndKill(FlowSet * Pre,const Stmt* s){
		FlowSet * ret=new ValueListSet();
		vector<expr> * tmp=z3coding.clangStmtToZ3Expr(s);
		if(tmp==nullptr){
			return ret;
		}
		tmp=z3coding.boolSortFiltering(tmp);
		if(tmp->size()<=0){
			ret->Union(Pre);
			return ret;
		}
		for(unsigned i=0;i<tmp->size();i++){
			expr z3Stmt=tmp->at(i);
			//kill
			ValueListSet* vlsPre=(ValueListSet*) Pre;
			if(isAssigndToScaleVariable(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0));
				for(Property *p:vlsPre->elements){
					AtomVariabla * av=(AtomVariabla *)p;
				
					vector<expr>* initStmtConsts=z3coding.getConsts(z3coding.unprimedDecline((av->indexInitStmtz3coding)));
					vector<expr>* updateStmtConsts=new vector<expr>();
					if(av->hasStep()){
						updateStmtConsts=z3coding.getConsts(z3coding.unprimedDecline((av->indexUpdateStmtz3coding)));
					}
					if(z3coding.isIn(scalaVar,initStmtConsts)||z3coding.isIn(scalaVar,updateStmtConsts)){
						//kill p
						//do nothing
					}
					else{
						ret->add(av->clone());
					}
				}
			}
			else{
				ret=Pre->clone();
			}
		
			//gen
			if(isAssigndToScaleVariable(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0));
				if(isAtomInitStmt(z3Stmt)){
					AtomVariabla* av=new AtomVariabla(c,z3coding,s);
				#ifdef _DEBUG	
					std::cout<<"gen: "<< av->toString()<<std::endl;
				#endif
					ret->add(av);
				}
				else if(isAtomUpdateStmt(z3Stmt)){
					for(Property *p:vlsPre->elements){
						AtomVariabla *av=(AtomVariabla *)p;
						if(av->checkScalaVaribale(scalaVar)){
							if(av->hasStep()){
								if(av->checkUpdateStmt(z3Stmt)){
									ret->add(av->clone());
								#ifdef _DEBUG	
									std::cout<<"gen: "<< av->toString()<<std::endl;
								#endif
								
								}
							}
							else{
								av=av->clone();
								av->addIndexUpdateStmt(s);
								ret->add(av);
							#ifdef _DEBUG	
								std::cout<<"gen: "<< av->toString()<<std::endl;
							#endif
							
							}
						}
					}
				}
			}
		}
		return ret;
	}
	
	void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
		for(auto it=outs->begin();it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*>* ele=*it;
			 if(ele->second==&universalSet){
				 ele->second=new ValueListSet();
			 }
		}
		FlowSet * Pre=in->clone();
		for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
			CFGElement element=(*iterblock);
			if(element.getKind()==CFGElement::Kind::Statement){
				const Stmt* it=((CFGStmt*)&element)->getStmt();
			#ifdef _DEBUG
				std::cout<<"Pre is: "<< Pre->toString()<<std::endl;
				std::cout<<"stmt is: "<< z3coding.toString(it)<<std::endl;
			#endif
				FlowSet* pin=mapToStmtIn.at(it);
				pin->clear();
				pin->Union(Pre);
				Pre=GenAndKill(Pre,it);
				FlowSet* pout=mapToStmtOut.at(it);
				pout->clear();
				pout->Union(Pre);
				
			#ifdef _DEBUG
				std::cout<<"Pos is: "<< Pre->toString()<<std::endl;
			#endif
			
			}
		}
		if(outs->size()==2){
			Stmt* T=n->getTerminatorCondition();
			FlowSet* pin=mapToStmtIn.at(T);
			pin->clear();
			pin->Union(Pre);
			FlowSet* pout=mapToStmtOut.at(T);
			pout->clear();
			pout->Union(Pre);
			
			pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
			ValueListSet *tureFlow=(ValueListSet*)tureBranch->second;
			pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
			ValueListSet *falseFlow=(ValueListSet*)falseBranch->second;
			tureFlow->Union(Pre->clone());
			falseFlow->Union(Pre->clone());
			
		}
		else if(outs->size()==1){
			pair<CFGBlock*,FlowSet*>* out=outs->front();
			ValueListSet *outFlow=(ValueListSet*)out->second;
			outFlow->Union(Pre->clone());
		}
				
	}
	void copy(FlowSet  *&from,FlowSet  *&to){
		if(from==&universalSet) {
			to=&universalSet;
		}
		else {
			to=from->clone();
		}
		
	}
	bool equal(FlowSet  *&from,FlowSet  *&to){
		if(from==&universalSet) {
			return to==&universalSet;
		}
		if(to==&universalSet) {
			return from==&universalSet;
		}
		return from->equal(to);
	}
//	FlowSet* clone(FlowSet  * from){
//		ValueListSet* vls=new ValueListSet();
//		ValueListSet* vlsFrom=(ValueListSet*)from;
//		for(Property* p: vlsFrom->elements){
//			
//			vls->add()
//		}
//	}
	void printStmtAnalysis(){
		for (map<const clang::Stmt*, FlowSet*>::iterator it=mapToStmtIn.begin(); it!=mapToStmtIn.end(); ++it){
			std::cout <<z3coding.toString(it->first) << " in :"; it->second->print();
			FlowSet * out=mapToStmtOut.at(it->first);
			std::cout <<z3coding.toString(it->first) << " out :";out->print();
		}

	}
};

#endif