//------------------------------------------------------------------------------
// Tooling sample. Demonstrates:
//
// * How to write a simple source tool using libTooling.
// * How to use RecursiveASTVisitor to find interesting AST nodes.
// * How to use the Rewriter API to rewrite the source code.
//
// Eli Bendersky (eliben@gmail.com)
// This code is in the public domain 
//------------------------------------------------------------------------------
//#define _PERFORMANCE_DEBUG  
//#define _DEBUG
#define _NON_PATHGUIDE_VERSION
#define _NON_QUICKSORT
#define _FEASIBLEPATH
#define _SIMPLEANLYSIS
#define _WellTypeBehavior
#define DISJUNCTIONK 2
//#define _PROPERTYCOLLECT
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "time.h"
#include <sys/time.h>
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
#include "clang/AST/DeclarationName.h"
#include "Property.h"
#include "Z3Coding.h"
#include "AtomVariableAnalysis.h"
#include "EnvironmentAnalysis.h"
#include "UserSuppliedInstanceOfEquation.h"
#include "MemoryUtil.h"
#include "C2Z3.h"
#include "C2Z3_amendment.h"
#include "PointerAnalysis.h"
#include "MultiIndexesRelationAnalysis.h"
#include "UserSuppliedInstanceOfRelation.h"
#include "FeasiblePath.h"
#include "LiftAnalysis_FeasiblePath.h"
#include "SimplePropertiesRelationAnalysis.h"
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace std;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");


// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods. 
int blockCount=0;
int forallFormulaCount=0;
int existFormulaCount=0;
int simpleFormulaCount=0;
int loopCount=0;
int hasForallloopCount=0;
int hasExistloopCount=0;
int hasForallOrExistloopCount=0;
class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
MyASTVisitor(Rewriter &R) : TheRewriter(R) {}
CFG::BuildOptions cfgBuildOptions;
bool VisitStmt(Stmt *s) {
	// Only care about If statements.
	//if (isa<IfStmt>(s)) {
	//IfStmt *IfStatement = cast<IfStmt>(s);
	//	Stmt *Then = IfStatement->getThen();
		//Stmt *Else = IfStatement->getElse();	
	//}
	return true;
}

void initCFGBuildOptions(){
	//init CFGBuildOptions;
}
std::string QualTypeToString(QualType qt){
	LangOptions LO;
	LO.CPlusPlus=1; 
	std::string buffer5;
	llvm::raw_string_ostream strout5(buffer5);
	qt.print(strout5,PrintingPolicy(LO));
	return strout5.str();
}
std::string ToString(const Type* ty){
	return QualTypeToString(ty-> getCanonicalTypeInternal());
}
std::string ToString(const Stmt* stmt){
	std::string buffer1;
	
	LangOptions LO;
	LO.CPlusPlus=1; 
	llvm::raw_string_ostream strout1(buffer1);
	
	stmt->printPretty(strout1, nullptr, PrintingPolicy(LO));
	return strout1.str();
}
z3::sort clangTypeToZ3Sort(z3::context &c,QualType qt){
	if(qt.getTypePtr()->isIntegerType()){
		return c.int_sort();
	}
	else if(qt.getTypePtr()->isBooleanType()){
		return c.bool_sort();
	}
	else if(qt.getTypePtr()->isArrayType()){
		const ArrayType * arraytype=(const ArrayType *)qt.getTypePtr();
		z3::sort elementSort=clangTypeToZ3Sort(c,arraytype->getElementType());
		return c.array_sort(c.int_sort(),elementSort);
	}
	else {
		LangOptions LO;
		LO.CPlusPlus=1; 
		std::string buffer;
		llvm::raw_string_ostream strout(buffer);
		qt.print(strout,PrintingPolicy(LO));
		std::string clangTypeName=strout.str();
		std::cerr<<"We do not process type : "<<clangTypeName<<std::endl;
		return c.int_sort();
	}
}

std::string toString(vector<expr>* vs,std::string split){
	std::string ret="";
	for(expr v:*vs){
		ret+=Z3_ast_to_string(v.ctx(),v)+split;
	}
    return ret;
}
		
std::string getAsString(DeclarationName &DeclName)
{
	std::string Result;
   llvm::raw_string_ostream OS(Result);
   OS << DeclName;
   return OS.str();
}
		
bool VisitFunctionDecl(FunctionDecl *f) {
	LangOptions LO;
	LO.CPlusPlus=1; 
	
	context c;
	Z3Coding z3coding(c);
	
	
	//vector<expr> * Pre=new vector<expr>();
	
	// Only function definitions (with bodies), not declarations.
	DeclarationName DeclName = f->getNameInfo().getName();
	std::string FuncName = getAsString(DeclName);
	if(f->hasBody()){
		std::cout<<"*******************process function::  "<<FuncName <<"***************"<<"\n";	
		//std::cerr<<"*******************process function::  "<<FuncName <<"***************"<<"\n";	
		std::unique_ptr<clang::CFG> myCFG=CFG::buildCFG(f, f->getBody(), &f->getASTContext(), cfgBuildOptions);
		myCFG->dump(LO,true);
		clang::CFG* cfg=myCFG.get();
		
		//std::cout<<"--------------------c2z3 analysis begin--------------------"<<std::endl;
		C2Z3 *c2z3=new C2Z3(cfg,z3coding);
		//std::cout<<"--------------------c2z3 analysis result--------------------"<<std::endl;
		//c2z3->print();
		
		AtomVariablaAnalysis* ava=new AtomVariablaAnalysis(f,cfg,c,z3coding,c2z3);
		//std::cout<<"--------------------index analysis result--------------------"<<std::endl;
		//ava->printStmtExprAnalysis();
		
		
		C2Z3_amendment* c2z3_amendment=new C2Z3_amendment(cfg,z3coding,c2z3,ava);
		//std::cout<<"--------------------c2z3_amendment analysis result--------------------"<<std::endl;
		//c2z3_amendment->print();
		//-------------------------------------------------------------------------------------------------
		
		//std::cout<<"--------------------newc2z3 Analysis begin--------------------"<<std::endl;
		C2Z3 *newc2z3=new C2Z3(cfg,z3coding,c2z3_amendment->GetMapToBlocks(),c2z3_amendment->GetStmtToZ3Exprs());
		//std::cout<<"--------------------final c2z3 analysis result--------------------"<<std::endl;
		//newc2z3->print();
		//std::cout<<"--------------------local declVariables--------------------"<<std::endl;
		//cout<<toString(newc2z3->getLocalDeclVariables(),",")<<std::endl;
		//std::cout<<"--------------------multiIndexesRelation Analysis begin--------------------"<<std::endl;
		MultiIndexesRelationAnalysis* multiIndexesRelationAnalysis=new MultiIndexesRelationAnalysis(f,cfg,c,z3coding,newc2z3,ava);
		//std::cout<<"--------------------multiIndexesRelation Analysis result--------------------"<<std::endl;
		//multiIndexesRelationAnalysis->printStmtExprAnalysis();
		//std::cout<<"--------------------pointerAnalysis begin--------------------"<<std::endl;
		//the class just is use to analysis *p:=e will kill which properties 
		PointerAnalysis* pointerAnalysis=new PointerAnalysis(f,cfg,z3coding,newc2z3);
		//std::cout<<"--------------------pointerAnalysis result--------------------"<<std::endl;
		//pointerAnalysis->printStmtExprAnalysis();
		
		EnvironmentAnalysisUtil emu(z3coding,c,pointerAnalysis);
		//std::cout<<"--------------------EnvironmentAnalysis begin--------------------"<<std::endl;
		EnvironmentAnalysis* env=new EnvironmentAnalysis(f,cfg,emu,z3coding,ava,newc2z3,multiIndexesRelationAnalysis);
		//std::cout<<"--------------------EnvironmentAnalysis result--------------------"<<std::endl;
		//env->print();
		//----------------------------FeasiblePath--------------------
		FeasiblePath* fp=new FeasiblePath(cfg,env,z3coding,newc2z3);
		//std::cout<<"--------------------FeasiblePath result--------------------"<<std::endl;
		//fp->print();
		
		struct timeval start, end;
		gettimeofday( &start, NULL );
		MemoryUtil mu(z3coding,pointerAnalysis);
		UserSupplied *userSuppliedInstance=new UserSuppliedInstanceOfRelation(c,z3coding,mu,newc2z3);
		//std::cout<<"*****************************************************************************************"<<std::endl;
		LiftAnalysis_FeasiblePath* liftAnalysis=new LiftAnalysis_FeasiblePath(f,cfg,c,env,ava,z3coding,userSuppliedInstance,mu,pointerAnalysis,newc2z3,multiIndexesRelationAnalysis,fp);
		//LiftAnalysis_FeasiblePath liftAnalysis(f,cfg,c,env,ava,z3coding,userSuppliedInstance,mu,pointerAnalysis,newc2z3,multiIndexesRelationAnalysis,fp);
		
		gettimeofday( &end, NULL );
		//double timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
		//if(liftAnalysis->forAllFormulaCount>0){
			//std::cout<<FuncName <<",";;	
			//std::cout<<"--------------------result--------------------"<<std::endl;
			blockCount+=liftAnalysis->blockCount;
			forallFormulaCount+=liftAnalysis->forAllFormulaCount;
			existFormulaCount+=liftAnalysis->existFormulaCount;
			simpleFormulaCount+=liftAnalysis->simpleFormulaCount;
			loopCount+=liftAnalysis->loopCount;
			hasForallloopCount+=liftAnalysis->hasForallFormulaLoopCount;
			hasExistloopCount+=liftAnalysis->hasExistFormulaLoopCount;
			hasForallOrExistloopCount+=liftAnalysis->hasForallOrExistFormulaLoopCount;
			//std::cout<<"------------- begin lift analysis-----------------------------------------------------"<<std::endl;
			liftAnalysis->print();
			//printf(" %f s,", timeuse/1000000);
			//std::cout<<" "<<liftAnalysis->forAllFormulaCount<<", "<<liftAnalysis->existFormulaCount<<std::endl;
		//}
	}
	
	
	return true;
}

	private:
		Rewriter &TheRewriter;
};

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public ASTConsumer {
	public:
		MyASTConsumer(Rewriter &R) : Visitor(R) {}
		// Override the method that gets called for each parsed top-level
		// declaration.
		bool HandleTopLevelDecl(DeclGroupRef DR) override {
			for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
				// Traverse the declaration using our AST visitor.
				Visitor.TraverseDecl(*b);
				//(*b)->dump();
			}
			return true;
		}

	private:
		MyASTVisitor Visitor;
};

// For each source file provided to the tool, a new FrontendAction is created.
class MyFrontendAction : public ASTFrontendAction {
	public:
		MyFrontendAction() {}
		void EndSourceFileAction() override {
		}

		std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
				StringRef file) override {
			return llvm::make_unique<MyASTConsumer>(TheRewriter);

		}

	private:
		Rewriter TheRewriter;
};


int main(int argc, const char **argv) {


	time_t start,stop;
	start = time(NULL);
	CommonOptionsParser op(argc, argv, ToolingSampleCategory);
	ClangTool Tool(op.getCompilations(), op.getSourcePathList());

	// ClangTool::run accepts a FrontendActionFactory, which is then used to
	// create new objects implementing the FrontendAction interface. Here we use
	// the helper newFrontendActionFactory to create a default factory that will
	// return a new MyFrontendAction object every time.
	// To further customize this, we could create our own factory class.
	Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
	stop = time(NULL);
	/*printf("%.0f ", difftime(stop,start)) ;
	printf("%d  ", loopCount) ;
	printf("%d  ", hasForallloopCount) ;
	printf("%d  ", hasExistloopCount) ;
	printf("%d  ", hasForallOrExistloopCount) ;
	printf("%d  ", blockCount) ;
	printf("%d  ", forallFormulaCount) ;
	printf("%d  ", existFormulaCount) ;
	printf("%d  \n", simpleFormulaCount) ;*/
  
	
	

}

