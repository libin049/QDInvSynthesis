#ifndef _AtomVariableAnalysis_H
#define _AtomVariableAnalysis_H
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

class AtomVariabla : public Property{
public:
	context &c;
	Z3Coding &z3coding;
	const clang::Stmt *indexInitStmt;
	vector<const clang::Stmt*>* indexUpdateStmts; //may be more than one updateStatement, however step is same
	expr scalaVarz3coding;
	expr stepz3coding;
	expr indexInitStmtz3coding;
	expr initz3coding;
	expr indexUpdateStmtz3coding;
	expr scalaVarModConstraint;
	bool isIn(const clang::Stmt* s,vector<const clang::Stmt*>* vs){
		for(const clang::Stmt* ele:*vs){
			if(ele==s){
				return true;
			}
		}
		return false;
	}

	/*AtomVariabla(context &ctx,Z3Coding &coding, const clang::Stmt *indexInitStmt):c(ctx),z3coding(coding),scalaVarz3coding(c)
				,stepz3coding(c),indexInitStmtz3coding(c),initz3coding(c),indexUpdateStmtz3coding(c){
		this->indexInitStmt=indexInitStmt;
		indexUpdateStmts=new vector<const clang::Stmt*>();
		vector<expr> * tmp=z3coding.boolSortFiltering(z3coding.clangStmtToZ3Expr(indexInitStmt));
		indexInitStmtz3coding=tmp->front();
		scalaVarz3coding=z3coding.unprime(indexInitStmtz3coding.arg(0));
		initz3coding=indexInitStmtz3coding.arg(1);
		
	}*/
	AtomVariabla(context &ctx,Z3Coding &coding, const clang::Stmt *indexInitStmt,expr indexInitZ3code)
	:c(ctx),z3coding(coding),scalaVarz3coding(c)
				,stepz3coding(c),indexInitStmtz3coding(c),initz3coding(c),indexUpdateStmtz3coding(c),scalaVarModConstraint(c){
		this->indexInitStmt=indexInitStmt;
		indexUpdateStmts=new vector<const clang::Stmt*>();
		indexInitStmtz3coding=indexInitZ3code;
		//cout<<indexInitStmtz3coding.arg(0)<<std::endl;
		scalaVarz3coding=z3coding.unprime(indexInitStmtz3coding.arg(0));
		initz3coding=indexInitStmtz3coding.arg(1);
		
	}
	bool hasStep(){
		if(indexUpdateStmts->size()==0){
			return false;
		}
		return true;
	}
//	void addIndexUpdateStmt(const clang::Stmt* indexUpdateStmt){
//		if(indexUpdateStmts->size()!=0){
//			if(!isIn(indexUpdateStmt,indexUpdateStmts)){
//				indexUpdateStmts->push_back(indexUpdateStmt);
//			}
//		}
//		else{
//			indexUpdateStmts->push_back(indexUpdateStmt);
//			vector<expr> *tmp=z3coding.clangStmtToZ3Expr(indexUpdateStmt);
//			tmp=z3coding.boolSortFiltering(tmp);
//			this->indexUpdateStmtz3coding=tmp->at(0);
//			stepz3coding=getStepFromIndexUpdate(indexUpdateStmtz3coding);
//		}
//	}
	void addIndexUpdateStmt(const clang::Stmt* indexUpdateStmt,expr indexUpdateExpr){
		if(indexUpdateStmts->size()!=0){
			if(!isIn(indexUpdateStmt,indexUpdateStmts)){
				indexUpdateStmts->push_back(indexUpdateStmt);
			}
		}
		else{
			indexUpdateStmts->push_back(indexUpdateStmt);
			//vector<expr> *tmp=z3coding.clangStmtToZ3Expr(indexUpdateStmt);
			//tmp=z3coding.boolSortFiltering(tmp);
			this->indexUpdateStmtz3coding=indexUpdateExpr;
			stepz3coding=getStepFromIndexUpdate(indexUpdateStmtz3coding);
			scalaVarModConstraint=to_expr(c,Z3_mk_mod(c,scalaVarz3coding-initz3coding,stepz3coding))==0;
		}
	}
		expr getStepFromIndexUpdate(expr stmt){
			if(stmt.arg(1).decl().name().str()=="+"){
				return stmt.arg(1).arg(1);
			}
			else if(stmt.arg(1).decl().name().str()=="-"){
				return -stmt.arg(1).arg(1);
			}
			else{
				std::cerr<<"AtomVariabla::getStepFromIndexUpdate: something is wrong!"<<std::endl;
				std::cerr<<"Error Info: stmt is "<<stmt<<std::endl;
				return z3coding._error;
			}
		}
//	/**
//	 * @brief check weather stmt update step
//	 * @param stmt
//	 * @return 
//	 */
//	bool checkIndexUpdateStmt(const clang::Stmt* stmt){
//		if(isIn(stmt,indexUpdateStmts)){
//			return true;	
//		}
//		else{
//			
//		}
//	}
	bool checkScalaVaribale(expr scalaVaribale){
		return z3coding.equal(scalaVarz3coding,scalaVaribale);
	}
	bool checkUpdateStmt(expr updateStmt){
		expr scalaVar=z3coding.unprime(updateStmt.arg(0));
		if(checkScalaVaribale(scalaVar)){
			if(z3coding.equal(this->indexUpdateStmtz3coding,updateStmt)){
				return true;
			}
		}
		return false;
	}
	bool isStepEqual(const clang::Stmt *InitStmt){
		return indexInitStmt==InitStmt;
	}
	bool equal(Property *p){
		AtomVariabla * av=(AtomVariabla *)p;
		if(!z3coding.equal(this->scalaVarz3coding,av->scalaVarz3coding)){
			return false;
		}
		if(this->indexInitStmt!=av->indexInitStmt){
			return false;
		}
		if(hasStep()!=av->hasStep()){
			return false;
		}
		if(hasStep()){
			if(!z3coding.equal(this->stepz3coding,av->stepz3coding)){
				return false;
			}
		}
		return true;
		//return p==this;
	}
	std::string toString(){
		std::string ret="init Stmt: ";
		ret+=Z3_ast_to_string(c,indexInitStmtz3coding);
		if(hasStep()){
			std::string stepStr=Z3_ast_to_string(c,stepz3coding);
			ret+=", step: "+stepStr; 
		}
		return ret;
	}
	AtomVariabla* clone(){
		/*AtomVariabla* ret=new AtomVariabla(c,z3coding,indexInitStmt);
		for(const clang::Stmt* s: *this->indexUpdateStmts){
			ret->indexUpdateStmts->push_back(s);
		}
		ret->indexUpdateStmtz3coding=this->indexUpdateStmtz3coding;
		ret->stepz3coding=this->stepz3coding;
		return ret;*/
		return this;
	}
	
};

class AtomVariablaAnalysis: public IntraDataFlowAnalysis{
	
	context &c;
	Z3Coding &z3coding;
	C2Z3* c2z3Stmt;
	/*if exist atomic scalar at a point,then we backfill that, at init of the atom scalar, it's step is what */
	void backfill(){
		for (map<const clang::Stmt*, FlowSet*>::iterator it=mapToStmtOut.begin(); it!=mapToStmtOut.end(); ++it){
			FlowSet * out=it->second;
			ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
			for(Property* p: vlsOut->elements){
				AtomVariabla * av=(AtomVariabla *)p;
				if(av->hasStep()){
					if(mapToStmtOut.count(av->indexInitStmt)<=0){
						continue;
					}
					FlowSet* out=mapToStmtOut.at(av->indexInitStmt);
					ValueListSetWithUniversalSet* vlsOut=(ValueListSetWithUniversalSet*)out;
					for(Property* p: vlsOut->elements){
						AtomVariabla * avx=(AtomVariabla *)p;
						if(avx->indexInitStmt==av->indexInitStmt&&!avx->hasStep()){
							for(const clang::Stmt* updateStmt:*av->indexUpdateStmts){
								//avx->addIndexUpdateStmt(updateStmt,av->indexInitStmtz3coding);
								avx->addIndexUpdateStmt(updateStmt,av->indexUpdateStmtz3coding);
							}
						}
					}
				}
			}
		}

	}
	void printFlowSets(vector<FlowSet*>* vs){
		unsigned count=0;
		for(FlowSet* f:*vs){
			count++;
			cout<<"--------"<<count<<"---------"<<std::endl;
			f->print();
		}
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
	bool canGetStepFromIndexUpdate(expr stmt){
		if(stmt.arg(1).decl().name().str()=="+"){
			return true;
		}
		else if(stmt.arg(1).decl().name().str()=="-"){
			return true;
		}
		else{
			return false;
		}
	}
public:
	map<const clang::Stmt*, FlowSet*> mapToStmtIn;
	map<const clang::Stmt*, FlowSet*> mapToStmtOut;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprIn;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprOut;
	/*void pre_init(){
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
			if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtIn.count(T)<=0){
					mapToStmtIn.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSetWithUniversalSet()));
					mapToStmtOut.insert(std::pair<const clang::Stmt*, FlowSet*>(T,new ValueListSetWithUniversalSet()));
				}
			}
		}
	}*/
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
		}
	}
	/*void pre_init_stmtExpr(){
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
			if(n->succ_size()==2){
				Stmt* T=n->getTerminatorCondition();
				if(mapToStmtExprIn.count(T)<=0){
					mapToStmtExprIn.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
					mapToStmtExprOut.insert(std::pair<const clang::Stmt*, vector<FlowSet*>*>(T,new vector<FlowSet*>()));
				}
			}
		}
	}*/
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
		}
	}
	AtomVariablaAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,context &ctx,Z3Coding &coding,C2Z3* c2z3)
	:IntraDataFlowAnalysis(functionDecl,cfg),c(ctx),z3coding(coding),c2z3Stmt(c2z3){
		pre_init();
		pre_init_stmtExpr();
		doAnalysis();
		backfill();
	}
	~AtomVariablaAnalysis(){}
	FlowSet * newinitialFlow(){
		return new ValueListSetWithUniversalSet(true); 
	}
	FlowSet * entryInitialFlow(){
		//cout<<"entryInitialFlow"<<std::endl;
		FlowSet * result=new ValueListSetWithUniversalSet();
		for(unsigned i=0;i<parms.size();i++){
			ParmVarDecl * pd=parms[i];
			expr initZ3Stmt=processDeclStmt((const Decl*)pd);
			result->add(new AtomVariabla(c,z3coding,(const clang::Stmt *)pd,initZ3Stmt));
			//std::cout<<"varName: "<<varName<<" type: "<<z3coding.toString(declQT)<<std::endl;
		}
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
		out=new ValueListSetWithUniversalSet();
		ValueListSetWithUniversalSet* vlsIn1=(ValueListSetWithUniversalSet*)in1;
		ValueListSetWithUniversalSet* vlsIn2=(ValueListSetWithUniversalSet*)in2;
		for(Property * p1: vlsIn1->elements){
			for(Property * p2: vlsIn2->elements){
				AtomVariabla* r=meet((AtomVariabla*)p1,(AtomVariabla*)p2);
				if(r!=nullptr){
					out->add(r);
				}
			}
		}
		return;
	}
	AtomVariabla* meet(AtomVariabla* in1,AtomVariabla* in2){
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
	
	/*FlowSet * GenAndKill(FlowSet * Pre,const Stmt* s){
		FlowSet * ret=new ValueListSetWithUniversalSet();
		vector<expr> * tmp=z3coding.clangStmtToZ3Expr(s);
		if(tmp==nullptr){
			return ret;
		}
		tmp=z3coding.boolSortFiltering(tmp);
		if(tmp->size()<=0){
			ret->Union(Pre);
			return ret;
		}
		ValueListSetWithUniversalSet* vlsPre=(ValueListSetWithUniversalSet*) Pre;
		for(unsigned i=0;i<tmp->size();i++){
			ret->clear();
			expr z3Stmt=tmp->at(i);
			//kill
			
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
				ret=vlsPre->clone();
			}
		
			//gen
			if(isAssigndToScaleVariable(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0));
				if(isAtomInitStmt(z3Stmt)){
					AtomVariabla* av=new AtomVariabla(c,z3coding,s,z3Stmt);
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
			vlsPre=(ValueListSetWithUniversalSet*)ret->clone();
		}
		return ret;
	}*/
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

		//vector<expr> * tmp=z3coding.clangStmtToZ3Expr(s);
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
			
			Pos->clear();
						
			mapToStmtExprIn.at(s)->at(i)->clear();
			mapToStmtExprIn.at(s)->at(i)->Union(vlsPre);
			
			expr z3Stmt=tmp->at(i);
			//kill
			
			if(z3coding.isAssigndToScaleVariable(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0).arg(0));
				for(Property *p:vlsPre->elements){
					AtomVariabla * av=(AtomVariabla *)p;
				
					auto initStmtConsts=z3coding.getConsts(z3coding.unprimedDecline((av->indexInitStmtz3coding)));
					unique_ptr<vector<expr>> updateStmtConsts(new vector<expr>());
					if(av->hasStep()){
						updateStmtConsts=z3coding.getConsts(z3coding.unprimedDecline((av->indexUpdateStmtz3coding)));
					}
					if(z3coding.isIn(scalaVar,initStmtConsts.get())||z3coding.isIn(scalaVar,updateStmtConsts.get())){
						//kill p
						//do nothing
					}
					else{
						Pos->add(av->clone());
					}
				}
			}
			else{
				Pos=vlsPre->clone();
			}
		
			//gen
			if(z3coding.isAssigndToScaleVariable(z3Stmt)){
				expr scalaVar=z3coding.unprime(z3Stmt.arg(0).arg(0));
				if(z3coding.isScalaVariableInitStmt(z3Stmt)){
					AtomVariabla* av=new AtomVariabla(c,z3coding,s,z3Stmt.arg(0));
					
				#ifdef _DEBUG
					std::cout<<"gen: "<< av->toString()<<std::endl;
				#endif
				
					Pos->add(av);
				}
				else if(z3coding.isScalaVariableUpdateStmt(z3Stmt)){
					for(Property *p:vlsPre->elements){
						AtomVariabla *av=(AtomVariabla *)p;
						if(av->checkScalaVaribale(scalaVar)){
							if(av->hasStep()){
								if(av->checkUpdateStmt(z3Stmt.arg(0))){
									Pos->add(av->clone());
								#ifdef _DEBUG	
									std::cout<<"gen: "<< av->toString()<<std::endl;
								#endif
								
								}
							}
							else if(canGetStepFromIndexUpdate(z3Stmt.arg(0))){
								av=av->clone();
								av->addIndexUpdateStmt(s,z3Stmt.arg(0));
								Pos->add(av);
								#ifdef _DEBUG	
									std::cout<<"gen: "<< av->toString()<<std::endl;
								#endif
							}
						}
					}
				}
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
			/*std::cout<<"stmt is: "<< z3coding.toString(it)<<std::endl;
			if(z3coding.toString(it)=="BZ2_bzReadGetUnused(&bzerr, bzf, &unusedTmpV, &nUnused)"){
				std::cout<<"stmt is: "<< z3coding.toString(it)<<std::endl;
			}*/
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
	AtomVariabla* getAtomVariableBefor(const clang::Stmt* stmt,unsigned count,expr scalar){
		if(mapToStmtExprIn.count(stmt)>0&&mapToStmtExprIn[stmt]->size()>count){
			ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)mapToStmtExprIn[stmt]->at(count);
			for(Property * p: AtomVariables->elements){
				AtomVariabla* av=(AtomVariabla*)p;
				if(av->hasStep()&&z3coding.equal(av->scalaVarz3coding,scalar)){
					return av;
				}
			}
		}
		return nullptr;
	}
	AtomVariabla* getAtomVariableAfter(const clang::Stmt* stmt,unsigned count,expr scalar){
		if(mapToStmtExprOut.count(stmt)>0&&mapToStmtExprOut[stmt]->size()>count){
			ValueListSetWithUniversalSet* AtomVariables=(ValueListSetWithUniversalSet*)mapToStmtExprOut[stmt]->at(count);
			for(Property * p: AtomVariables->elements){
				AtomVariabla* av=(AtomVariabla*)p;
				if(av->hasStep()&&z3coding.equal(av->scalaVarz3coding,scalar)){
					return av;
				}
			}
		}
		return nullptr;
	}
	
};

#endif