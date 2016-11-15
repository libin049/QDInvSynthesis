#ifndef _UserSupplied_H
#define _UserSupplied_H
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
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace std;

//template <typename T>

class UserSupplied{
public: 
	virtual ~UserSupplied(){}
	virtual FlowSet * newinitialFlow(){return nullptr;}
	virtual FlowSet * entryInitialFlow(){return nullptr;}
	virtual void merge(FlowSet  *&in1,FlowSet  *&in2,FlowSet *&out){}
	virtual void flowThrouth(const clang::Stmt* stmt,int count,FlowSet* &in,FlowSet*&out){}
	virtual void flowThrouth(const clang::Stmt* stmt,int count,FlowSet* &in,FlowSet*&trueOut,FlowSet*&falseOut){}
	virtual bool isSimpleProperty(Formula* f){return false;}
	virtual bool partialOrderRelation(Formula* f1,Formula* f2){return false;}
};
#endif