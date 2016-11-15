#ifndef _MultiIndexesRelationAnalysis_H
#define _MultiIndexesRelationAnalysis_H
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
#include "AtomVariableAnalysis.h"
using namespace z3;

class ScalaVariabla : public Property{
public:
	expr scalaVariabla;
	ScalaVariabla(expr scalaVar):scalaVariabla(scalaVar){
	}
	bool equal(Property *p){
		ScalaVariabla * v=(ScalaVariabla *)p;
		return eq(this->scalaVariabla,v->scalaVariabla);
	}
	std::string toString(){
		std::string ret=Z3_ast_to_string(scalaVariabla.ctx(),scalaVariabla);
		return ret;
	}
	ScalaVariabla* clone(){
		return new ScalaVariabla(scalaVariabla);
	}
};
class FromInitToUpdateAnalysis:public IntraDataFlowAnalysis{
	Z3Coding &z3coding;
	C2Z3* c2z3Stmt;
	AtomVariablaAnalysis* indexAnalysis;
	
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
	map<const clang::Stmt*, FlowSet*> mapToStmtOut;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprIn;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprOut;
	void pre_init(){
		for(CFG::iterator it=cfg->begin();it!=cfg->end();++it){
			CFGBlock* n=*it;
			for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
				CFGElement element=(*iterblock);
				if(element.getKind()==CFGElement::Kind::Statement){
					const Stmt* it=((CFGStmt*)&element)->getStmt();
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSetWithUniversalSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSetWithUniversalSet()));
				}
			}
			/*if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtIn.count(T)<=0){
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSetWithUniversalSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSetWithUniversalSet()));
				}
			}*/
		}
	}
	void pre_init_stmtExpr(){
		for(CFG::iterator it=cfg->begin();it!=cfg->end();++it){
			CFGBlock* n=*it;
			for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
				CFGElement element=(*iterblock);
				if(element.getKind()==CFGElement::Kind::Statement){
					const Stmt* it=((CFGStmt*)&element)->getStmt();
					mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,new vector<FlowSet*>()));
					mapToStmtExprOut.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,new vector<FlowSet*>()));
				}
			}
			/*if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtExprIn.count(T)<=0){
					mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
					mapToStmtExprOut.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
				}
			}*/
		}
	}
	FromInitToUpdateAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,context &ctx,Z3Coding &coding,C2Z3* c2z3,
	AtomVariablaAnalysis* indexAna)
	:IntraDataFlowAnalysis(functionDecl,cfg),z3coding(coding),c2z3Stmt(c2z3),indexAnalysis(indexAna){
		pre_init();
		pre_init_stmtExpr();
		doAnalysis();
	}
	~FromInitToUpdateAnalysis(){}
	FlowSet * newinitialFlow(){
		return new ValueListSetWithUniversalSet(true); 
	}
	FlowSet * entryInitialFlow(){
		FlowSet * result=getIndexBefor(&cfg->getEntry());
		return result;
	}
	
	void merge(FlowSet  * &in1,FlowSet  *&in2,FlowSet  *&out){
		if(in1->isUniversalSet()&&in2->isUniversalSet()) {
		#ifdef _DEBUG
			std::cout<<"universalSet merge universalSet"<<std::endl;
		#endif
			out=in1->clone();
			return;
		}
		if(in1->isUniversalSet()){
		#ifdef _DEBUG
			std::cout<<"universalSet merge "<<in2->toString()<<std::endl;
		#endif
			out=in2->clone();
			return;
		}
		if(in2->isUniversalSet()) {
		#ifdef _DEBUG
			std::cout<<"universalSet merge "<<in1->toString()<<std::endl;
		#endif
			out=in1->clone();
			return;
		}
	#ifdef _DEBUG
		std::cout<<in1->toString()<<"--- merge---"<<in2->toString()<<std::endl;
	#endif
		out=in1->clone();
		out->intersection(in2);
		return;
	}
	
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
	FlowSet * GenAndKill(FlowSet * Pre,const Stmt* s){
		FlowSet * Pos=new ValueListSetWithUniversalSet();

		vector<expr> * tmp=new vector<expr>();
		vector<expr> * z3Stmts=c2z3Stmt->getZ3Stmts(s);
		if(z3Stmts==nullptr){
			return Pos;
		}
		
		if(z3Stmts->size()<=0){
			Pos->Union(Pre);
			return Pos;
		}
		z3coding.pushAToB(z3Stmts,tmp);
		//init stmtExpr
		if(mapToStmtExprIn.at(s)->size()!=tmp->size()){
			mapToStmtExprIn.at(s)->clear();
			for(unsigned i=0;i<tmp->size();i++){
				mapToStmtExprIn.at(s)->push_back(new ValueListSetWithUniversalSet());
			}
		}
		if(mapToStmtExprOut.at(s)->size()!=tmp->size()){
			mapToStmtExprOut.at(s)->clear();
			for(unsigned i=0;i<tmp->size();i++){
				mapToStmtExprOut.at(s)->push_back(new ValueListSetWithUniversalSet());
			}
		}
		ValueListSetWithUniversalSet* vlsPre=(ValueListSetWithUniversalSet*) Pre->clone();
		for(unsigned i=0;i<tmp->size();i++){
			#ifdef _DEBUG
			std::cout<<"Pre is: "<< vlsPre->toString()<<std::endl;
			cout<<"process::"<<tmp->at(i)<<"------------"<<std::endl;
			#endif
			
			Pos=vlsPre->clone();
						
			mapToStmtExprIn.at(s)->at(i)->clear();
			mapToStmtExprIn.at(s)->at(i)->Union(vlsPre);
			
			expr z3Stmt=tmp->at(i);
			//gen&kill
			
			if(z3coding.isScalaVariableInitStmt(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0).arg(0));
				if(isIndex(s,i,scalaVar)){
					if(!isIn(scalaVar,Pos)){
						Pos->add(new ScalaVariabla(scalaVar));
					}
				}
			}
			else if(z3coding.isScalaVariableUpdateStmt(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0).arg(0));
				Pos=remove(vlsPre,scalaVar);
			}
			
			vlsPre=(ValueListSetWithUniversalSet*)Pos->clone();
			
			mapToStmtExprOut.at(s)->at(i)->clear();
			mapToStmtExprOut.at(s)->at(i)->Union(vlsPre);
			
			#ifdef _DEBUG
			std::cout<<"Pos is: "<< vlsPre->toString()<<std::endl;
			#endif
		}
		return Pos;
	}
	
	void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
		for(auto it=outs->begin();it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*>* ele=*it;
			 if(ele->second->isUniversalSet()){
				 ele->second->setNonUniversalSetWhenIsUniversalSet();
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
			/*Stmt* T=n->getTerminatorCondition();
			FlowSet* pin=mapToStmtIn.at(T);
			pin->clear();
			pin->Union(Pre);
			FlowSet* pout=mapToStmtOut.at(T);
			pout->clear();
			pout->Union(Pre);*/
			
			pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
			ValueListSetWithUniversalSet *tureFlow=(ValueListSetWithUniversalSet*)tureBranch->second;
			pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
			ValueListSetWithUniversalSet *falseFlow=(ValueListSetWithUniversalSet*)falseBranch->second;
			tureFlow->Union(Pre->clone());
			falseFlow->Union(Pre->clone());
			
		}
		else if(outs->size()==1){
			pair<CFGBlock*,FlowSet*>* out=outs->front();
			ValueListSetWithUniversalSet *outFlow=(ValueListSetWithUniversalSet*)out->second;
			outFlow->Union(Pre->clone());
		}
				
	}
	void copy(FlowSet  *&from,FlowSet  *&to){
		to=from->clone();
	}
	bool equal(FlowSet  *&from,FlowSet  *&to){
		return from->equal(to);
	}

	void printStmtAnalysis(){
		for (map<const clang::Stmt*, FlowSet*>::iterator it=mapToStmtIn.begin(); it!=mapToStmtIn.end(); ++it){
			std::cout <<z3coding.toString(it->first) << " in :"; it->second->print();
			FlowSet * out=mapToStmtOut.at(it->first);
			std::cout <<z3coding.toString(it->first) << " out :";out->print();
		}

	}
	
	void printStmtExprAnalysis(){
		for (map<const clang::Stmt*, vector<FlowSet*>*>::iterator it=mapToStmtExprIn.begin(); it!=mapToStmtExprIn.end(); ++it){
			std::cout <<z3coding.toString(it->first) << " -----------in :-------------"<<std::endl;
			printFlowSets(it->second);
			
			vector<FlowSet*>* out=mapToStmtExprOut.at(it->first);
			std::cout <<z3coding.toString(it->first) << " ------------out :------------"<<std::endl;
			printFlowSets(out);
		}

	}
	FlowSet * getIndexBefor(CFGBlock* b){
		FlowSet * result=new ValueListSetWithUniversalSet();
		ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)indexAnalysis->getMapToBlockIn()->at(b);
		if(AtomVariables==nullptr){
			return result;
		}
		for(Property * p: AtomVariables->elements){
			AtomVariabla* av=(AtomVariabla*)p;
			if(av->hasStep()){
				result->add(new ScalaVariabla(av->scalaVarz3coding));
			}
		}
		return result;
	}
	FlowSet * getIndexBefor(const clang::Stmt* stmt,unsigned count,expr scalar){
		FlowSet * result=new ValueListSetWithUniversalSet();
		ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)indexAnalysis->mapToStmtExprIn[stmt]->at(count);
		if(AtomVariables==nullptr){
			return result;
		}
		for(Property * p: AtomVariables->elements){
			AtomVariabla* av=(AtomVariabla*)p;
			if(av->hasStep()){
				result->add(new ScalaVariabla(av->scalaVarz3coding));
			}
		}
		return result;
	}
	FlowSet * getIndexAfter(const clang::Stmt* stmt,unsigned count,expr scalar){
		FlowSet * result=new ValueListSetWithUniversalSet();
		ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)indexAnalysis->mapToStmtExprOut[stmt]->at(count);
		if(AtomVariables==nullptr){
			return result;
		}
		for(Property * p: AtomVariables->elements){
			AtomVariabla* av=(AtomVariabla*)p;
			if(av->hasStep()){
				result->add(new ScalaVariabla(av->scalaVarz3coding));
			}
		}
		return result;
	}
	
	bool isIndex(const clang::Stmt* stmt,unsigned count,expr scalar){
		ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)indexAnalysis->mapToStmtExprOut[stmt]->at(count);
		if(AtomVariables==nullptr){
			return false;
		}
		for(Property * p: AtomVariables->elements){
			AtomVariabla* av=(AtomVariabla*)p;
			if(av->hasStep()&&z3coding.equal(av->scalaVarz3coding,scalar)){
				return true;
			}
		}
		return false;
	}
	
	FlowSet * remove(FlowSet * S,expr v){
		FlowSet * result=new ValueListSetWithUniversalSet();
		ValueListSetWithUniversalSet* scalas=(ValueListSetWithUniversalSet*)S;
		for(Property * p: scalas->elements){
			ScalaVariabla* sv=(ScalaVariabla*)p;
			if(!z3coding.equal(sv->scalaVariabla,v)){
				result->add(new ScalaVariabla(sv->scalaVariabla));
			}
		}
		return result;
	}
	bool isIn(expr v,FlowSet * S){
		ValueListSetWithUniversalSet* scalas=(ValueListSetWithUniversalSet*)S;
		for(Property * p: scalas->elements){
			ScalaVariabla* sv=(ScalaVariabla*)p;
			if(z3coding.equal(sv->scalaVariabla,v)){
				return true;
			}
		}
		return false;
	}
};


class IndexesRelation : public Property{
public:
	expr scalaVariabla1;
	expr scalaVariabla2;
	int diff;
	IndexesRelation(expr scalaVar1,expr scalaVar2,int diff):scalaVariabla1(scalaVar1),scalaVariabla2(scalaVar2){
		this->diff=diff;
	}
	bool equal(Property *p){
		IndexesRelation * r=(IndexesRelation *)p;
		if((eq(this->scalaVariabla1,r->scalaVariabla1)&&eq(this->scalaVariabla2,r->scalaVariabla2)&&this->diff==r->diff)
		||(eq(this->scalaVariabla1,r->scalaVariabla2)&&eq(this->scalaVariabla2,r->scalaVariabla1)&&this->diff==-r->diff)){
			return true;
		}
		return false;
	}
	std::string toString(){
		std::string ret=Z3_ast_to_string(scalaVariabla1.ctx(),scalaVariabla1);
		ret+=" - ";
		ret+=Z3_ast_to_string(scalaVariabla2.ctx(),scalaVariabla2);
		ret+=" = ";
		ret+=std::to_string(diff);
		return ret;
	}
	IndexesRelation* clone(){
		return new IndexesRelation(scalaVariabla1,scalaVariabla2,diff);
	}
};

class MultiIndexesRelationAnalysis:public IntraDataFlowAnalysis{
	Z3Coding &z3coding;
	C2Z3* c2z3Stmt;
	AtomVariablaAnalysis* indexAnalysis;
	FromInitToUpdateAnalysis * itou;
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
			for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
				CFGElement element=(*iterblock);
				if(element.getKind()==CFGElement::Kind::Statement){
					const Stmt* it=((CFGStmt*)&element)->getStmt();
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSetWithUniversalSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(it,new ValueListSetWithUniversalSet()));
				}
			}
			/*if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtIn.count(T)<=0){
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSetWithUniversalSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSetWithUniversalSet()));
				}
			}*/
		}
	}
	void pre_init_stmtExpr(){
		for(CFG::iterator it=cfg->begin();it!=cfg->end();++it){
			CFGBlock* n=*it;
			for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
				CFGElement element=(*iterblock);
				if(element.getKind()==CFGElement::Kind::Statement){
					const Stmt* it=((CFGStmt*)&element)->getStmt();
					mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,new vector<FlowSet*>()));
					mapToStmtExprOut.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(it,new vector<FlowSet*>()));
				}
			}
			/*if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtExprIn.count(T)<=0){
					mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
					mapToStmtExprOut.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
				}
			}*/
		}
	}
	FlowSet * getIndexInitBefor(CFGBlock* b){
		return itou->getMapToBlockIn()->at(b);
	}
	FlowSet * getIndexInitBefor(const clang::Stmt* stmt,unsigned count){
		return itou->mapToStmtExprIn[stmt]->at(count);
	}
	FlowSet * getIndexInitAfter(const clang::Stmt* stmt,unsigned count){
		return itou->mapToStmtExprOut[stmt]->at(count);
	}
	FlowSet * initIndexRelation(FlowSet * scalas){
		FlowSet* result=new ValueListSetWithUniversalSet();
		ValueListSetWithUniversalSet* initScalas=(ValueListSetWithUniversalSet*)scalas;
		for(Property* v1:initScalas->elements){
			for(Property* v2:initScalas->elements){
				ScalaVariabla* sv1=(ScalaVariabla*)v1;
				ScalaVariabla* sv2=(ScalaVariabla*)v2;
				if(sv1==sv2) continue;
				result->add(new IndexesRelation(sv1->scalaVariabla,sv2->scalaVariabla,0));
			}
		}
		return result;
	}
	void add(FlowSet * S1,FlowSet * S2){
		ValueListSetWithUniversalSet* vS1=(ValueListSetWithUniversalSet*)S1;
		for(Property* p:vS1->elements){
			if(!isIn((IndexesRelation*)p,S2)){
				S2->add(p);
			}
		}
	}
	
	bool isIn(IndexesRelation* r,FlowSet * S){
		ValueListSetWithUniversalSet* rs=(ValueListSetWithUniversalSet*)S;
		for(Property * p: rs->elements){
			IndexesRelation* tmp=(IndexesRelation*)p;
			if(tmp->equal(r)){
				return true;
			}
		}
		return false;
	}
	FlowSet * GenAndKill(FlowSet * Pre,const Stmt* s){
		ValueListSetWithUniversalSet * Pos=new ValueListSetWithUniversalSet();

		vector<expr> * tmp=new vector<expr>();
		vector<expr> * z3Stmts=c2z3Stmt->getZ3Stmts(s);
		if(z3Stmts==nullptr){
			return Pos;
		}
		
		if(z3Stmts->size()<=0){
			Pos->Union(Pre);
			return Pos;
		}
		z3coding.pushAToB(z3Stmts,tmp);
		//init stmtExpr
		if(mapToStmtExprIn.at(s)->size()!=tmp->size()){
			mapToStmtExprIn.at(s)->clear();
			for(unsigned i=0;i<tmp->size();i++){
				mapToStmtExprIn.at(s)->push_back(new ValueListSetWithUniversalSet());
			}
		}
		if(mapToStmtExprOut.at(s)->size()!=tmp->size()){
			mapToStmtExprOut.at(s)->clear();
			for(unsigned i=0;i<tmp->size();i++){
				mapToStmtExprOut.at(s)->push_back(new ValueListSetWithUniversalSet());
			}
		}
		ValueListSetWithUniversalSet* vlsPre=(ValueListSetWithUniversalSet*) Pre->clone();
		for(unsigned i=0;i<tmp->size();i++){
			#ifdef _DEBUG
			std::cout<<"Pre is: "<< vlsPre->toString()<<std::endl;
			cout<<"process::"<<tmp->at(i)<<"------------"<<std::endl;
			#endif
			
			Pos=(ValueListSetWithUniversalSet*)vlsPre->clone();
						
			mapToStmtExprIn.at(s)->at(i)->clear();
			mapToStmtExprIn.at(s)->at(i)->Union(vlsPre);
			
			expr z3Stmt=tmp->at(i);
			//gen&kill
			
			FlowSet* inits=initIndexRelation(getIndexInitAfter(s,i));
			add(inits,Pos);
			
			if(z3coding.isScalaVariableUpdateStmt(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0).arg(0));
				FlowSet* tmp=new ValueListSetWithUniversalSet();
				for(Property* p:Pos->elements){
					IndexesRelation* r=(IndexesRelation*)p;
					if(z3coding.equal(r->scalaVariabla1,scalaVar)){
						tmp->add(new IndexesRelation(r->scalaVariabla1,r->scalaVariabla2,r->diff+1));
					}
					else if(z3coding.equal(r->scalaVariabla2,scalaVar)){
						tmp->add(new IndexesRelation(r->scalaVariabla1,r->scalaVariabla2,r->diff-1));
					}
					else{
						tmp->add(r->clone());
					}
				}
				Pos=(ValueListSetWithUniversalSet*)tmp;
			}
			
			vlsPre=(ValueListSetWithUniversalSet*)Pos->clone();
			
			mapToStmtExprOut.at(s)->at(i)->clear();
			mapToStmtExprOut.at(s)->at(i)->Union(vlsPre);
			
			#ifdef _DEBUG
			std::cout<<"Pos is: "<< vlsPre->toString()<<std::endl;
			#endif
		}
		return Pos;
	}
public:
	map<const clang::Stmt*, FlowSet*> mapToStmtIn;
	map<const clang::Stmt*, FlowSet*> mapToStmtOut;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprIn;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprOut;
	
	MultiIndexesRelationAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,context &ctx,Z3Coding &coding,C2Z3* c2z3
	,AtomVariablaAnalysis* indexAna)
	:IntraDataFlowAnalysis(functionDecl,cfg),z3coding(coding),c2z3Stmt(c2z3),indexAnalysis(indexAna){
		this->itou=new FromInitToUpdateAnalysis(functionDecl,cfg,ctx,z3coding,c2z3,indexAnalysis);
		pre_init();
		pre_init_stmtExpr();
		doAnalysis();
	}
	~MultiIndexesRelationAnalysis(){}
	FlowSet * newinitialFlow(){
		return new ValueListSetWithUniversalSet(true); 
	}
	FlowSet * entryInitialFlow(){
		FlowSet * result=initIndexRelation(getIndexInitBefor(&cfg->getEntry()));
		return result;
	}
	
	void merge(FlowSet  * &in1,FlowSet  *&in2,FlowSet  *&out){
		if(in1->isUniversalSet()&&in2->isUniversalSet()) {
		#ifdef _DEBUG
			std::cout<<"universalSet merge universalSet"<<std::endl;
		#endif
			out=in1->clone();
			return;
		}
		if(in1->isUniversalSet()){
		#ifdef _DEBUG
			std::cout<<"universalSet merge "<<in2->toString()<<std::endl;
		#endif
			out=in2->clone();
			return;
		}
		if(in2->isUniversalSet()) {
		#ifdef _DEBUG
			std::cout<<"universalSet merge "<<in1->toString()<<std::endl;
		#endif
			out=in1->clone();
			return;
		}
	#ifdef _DEBUG
		std::cout<<in1->toString()<<"--- merge---"<<in2->toString()<<std::endl;
	#endif
		out=in1->clone();
		out->intersection(in2);
		return;
	}
	
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
	
	
	void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
		for(auto it=outs->begin();it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*>* ele=*it;
			 if(ele->second->isUniversalSet()){
				 ele->second->setNonUniversalSetWhenIsUniversalSet();
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
			/*Stmt* T=n->getTerminatorCondition();
			FlowSet* pin=mapToStmtIn.at(T);
			pin->clear();
			pin->Union(Pre);
			FlowSet* pout=mapToStmtOut.at(T);
			pout->clear();
			pout->Union(Pre);*/
			
			pair<CFGBlock*,FlowSet*>* tureBranch=outs->front();
			ValueListSetWithUniversalSet *tureFlow=(ValueListSetWithUniversalSet*)tureBranch->second;
			pair<CFGBlock*,FlowSet*>* falseBranch=outs->back();
			ValueListSetWithUniversalSet *falseFlow=(ValueListSetWithUniversalSet*)falseBranch->second;
			tureFlow->Union(Pre->clone());
			falseFlow->Union(Pre->clone());
			
		}
		else if(outs->size()==1){
			pair<CFGBlock*,FlowSet*>* out=outs->front();
			ValueListSetWithUniversalSet *outFlow=(ValueListSetWithUniversalSet*)out->second;
			outFlow->Union(Pre->clone());
		}
				
	}
	void copy(FlowSet  *&from,FlowSet  *&to){
		to=from->clone();
	}
	bool equal(FlowSet  *&from,FlowSet  *&to){
		return from->equal(to);
	}

	void printStmtAnalysis(){
		for (map<const clang::Stmt*, FlowSet*>::iterator it=mapToStmtIn.begin(); it!=mapToStmtIn.end(); ++it){
			std::cout <<z3coding.toString(it->first) << " in :"; it->second->print();
			FlowSet * out=mapToStmtOut.at(it->first);
			std::cout <<z3coding.toString(it->first) << " out :";out->print();
		}

	}
	
	void printStmtExprAnalysis(){
		for (map<const clang::Stmt*, vector<FlowSet*>*>::iterator it=mapToStmtExprIn.begin(); it!=mapToStmtExprIn.end(); ++it){
			std::cout <<z3coding.toString(it->first) << " -----------in :-------------"<<std::endl;
			printFlowSets(it->second);
			
			vector<FlowSet*>* out=mapToStmtExprOut.at(it->first);
			std::cout <<z3coding.toString(it->first) << " ------------out :------------"<<std::endl;
			printFlowSets(out);
		}

	}
	
	FlowSet * getIndexRelationBefor(const clang::Stmt* stmt,unsigned count){
		if(mapToStmtExprIn.count(stmt)>0){
			if(mapToStmtExprIn.at(stmt)->size()>count){
				return mapToStmtExprIn.at(stmt)->at(count);
			}
		}
		return new ValueListSetWithUniversalSet();
	}
	FlowSet * getIndexRelationAfter(const clang::Stmt* stmt,unsigned count){
		if(mapToStmtExprOut.count(stmt)>0){
			if(mapToStmtExprOut.at(stmt)->size()>count){
				return mapToStmtExprOut.at(stmt)->at(count);
			}
		}
		return new ValueListSetWithUniversalSet();
	}
};

#endif 