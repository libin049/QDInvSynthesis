#ifndef _UserSuppliedInstanceOfEquation_H
#define _UserSuppliedInstanceOfEquation_H
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
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
#include "FlowSet.h"
#include "ValueListSetWithUniversalSet.h"
#include "MemoryUtil.h"
#include "UserSupplied.h"
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace std;

//template <typename T>

class UserSuppliedInstanceOfEquation : public UserSupplied{
private:
	Z3Coding &z3coding;
	MemoryUtil &mu;
	C2Z3* c2z3Stmt;
	Formula * _simpleFormulaMeet(Formula * f1,Formula *f2){
			expr e1= f1->formula;
			expr e2= f2->formula;
			return new Formula(_simpleFormulaMeet(e1,e2));
		}
		expr _simpleFormulaMeet(expr e1,expr e2){
			if(e1.is_app()&&e2.is_app()){
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
			return z3coding._error;
		}
	bool isEquation(expr e,const clang::Stmt* stmt,int count){
		if(e.is_app()&&e.decl().name().str()=="="){
			expr left=e.arg(0);
			expr right=e.arg(1);
			if(!mu.mayMemoryUnitIsInFormula(z3coding.unprimedDecline(left),right,stmt,count)){
				return true;
			}
		}
		return false;
	}
	FlowSet* Pos(expr stmt,vector<Property*>* in,const clang::Stmt* clangStmt,int count){
		FlowSet* out=new ValueListSetWithUniversalSet();
		//cout<<"stmt is "<<stmt<<std::endl;
		//(_AS (= (def_pointer__prime (- dest 1)) (def_pointer (- src 1))))
		if(z3coding.isAssignment(stmt)){
			stmt=stmt.arg(0);
			expr left=stmt.arg(0);
			for(Property* p:*in){
				Formula* f=(Formula*)p;
				//cout<<"111 f->formula is "<<f->formula<<std::endl;
				if(!mu.mayMemoryUnitIsInFormula(z3coding.unprimedDecline(left),f->formula,clangStmt,count)){
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
		if(isEquation(stmt,clangStmt,count)){
			out->add(new Formula(z3coding.unprimedDecline(stmt)));
			out=closure(z3coding.unprimedDecline(stmt),out);
		}
		return out;
	}
	FlowSet* closure(expr eq,FlowSet* equations){
		auto equationFormulas=equations->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		for(Property* p:*equationFormulas){
			Formula* f=(Formula*)p;
			expr e=f->formula;
			expr eqleft=eq.arg(0);
			expr eqright=eq.arg(1);
			if(z3coding.isSimpleFormula(e)){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3coding.equal(eqleft,eleft)&&!z3coding.equal(eqright,eright)){
					out->add(new Formula(eqright==eright));
				}
				if(z3coding.equal(eqleft,eright)&&!z3coding.equal(eqright,eleft)){
					out->add(new Formula(eleft==eqright));
				}
				if(!z3coding.equal(eqleft,eleft)&&z3coding.equal(eqright,eright)){
					out->add(new Formula(eqleft==eleft));
				}
				if(!z3coding.equal(eqleft,eright)&&z3coding.equal(eqright,eleft)){
					out->add(new Formula(eqleft==eright));
				}
			}
		}
		out->Union(equations);
		return out;
	}
public:
	UserSuppliedInstanceOfEquation(Z3Coding &z3c,MemoryUtil &memoryUtil,C2Z3* c2z3)
	:z3coding(z3c),mu(memoryUtil),c2z3Stmt(c2z3){}
	~UserSuppliedInstanceOfEquation(){}
	
	FlowSet * newinitialFlow(){return new ValueListSetWithUniversalSet(true);}
	FlowSet * entryInitialFlow(){return new ValueListSetWithUniversalSet();}
	void merge(FlowSet  *&in1,FlowSet  *&in2,FlowSet *&out){
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
		else{
			auto in1vec=in1->toVector();
			auto in2vec=in2->toVector();
			for(Property * p1:*in1vec){
				for(Property * p2:*in2vec){
					Formula *f1=(Formula *)p1;
					Formula *f2=(Formula *)p2;
					Formula * r=_simpleFormulaMeet(f1,f2);
					if(!z3coding.equal(r->formula,z3coding._error)){
						out->add(r);
					}
				}
			}	
		}
	}
	/**
	 * @brief 
	 * @param stmt
	 * @param count
	 * @param in
	 * @param out
	 */
	void flowThrouth(const clang::Stmt* stmt,int count,FlowSet* &in,FlowSet*&out){
		/*vector<expr> * exprs=z3coding.clangStmtToZ3Expr(stmt);
		if(exprs==nullptr){
			out=new ValueListSetWithUniversalSet();
		}
		vector<expr> *stmtFormulas=z3coding.boolSortFiltering(exprs);*/
		
		vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
		if(exprs==nullptr||count==-1){
			out=new ValueListSetWithUniversalSet();
			return;
		}
		
		vector<expr> *stmtFormulas=new vector<expr>();
		z3coding.pushAToB(exprs,stmtFormulas);
		
		FlowSet* tmp=in;
		/*for(expr e:*stmtFormulas){
			tmp=Pos(e,tmp->toVector());
		}*/
		if(count>=0&&count<(int)stmtFormulas->size()){
			expr stmtF=stmtFormulas->at(count);
			auto ign=tmp->toVector();
			tmp=Pos(stmtF,ign.get(),stmt,count);
		}
		out->Union(tmp);
		
	}
	void flowThrouth(const clang::Stmt* stmt,int count,FlowSet* &in,FlowSet*&trueOut,FlowSet*&falseOut){
		vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
		if(exprs==nullptr||count==-1){
			trueOut=new ValueListSetWithUniversalSet();
			falseOut=new ValueListSetWithUniversalSet();
			return;
		}
		
		vector<expr> *stmtFormulas=new vector<expr>();
		z3coding.pushAToB(exprs,stmtFormulas);
		
		FlowSet* tmp=in;
		if(count>=0&&count<(int)stmtFormulas->size()){
			expr stmtF=stmtFormulas->at(count);
			auto ign=tmp->toVector();
			tmp=Pos(stmtF,ign.get(),stmt,count);
		}
		
		trueOut->Union(tmp->clone());falseOut->Union(tmp->clone());
	}
	bool isSimpleProperty(Formula* f){
		return z3coding.isSimpleFormula(f->formula);
	}
	bool partialOrderRelation(Formula* f1,Formula* f2){
		expr e1= f1->formula;
		expr e2= f2->formula;
		return z3coding.equal(e1,e2);
	}
};
#endif