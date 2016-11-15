#ifndef _PointerAnalysis_H
#define _PointerAnalysis_H
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
class AliasProperty : public Property{
public:
	bool isAliasOthers;
	z3::expr variable;
	AliasProperty(bool isAlias, z3::expr v): isAliasOthers(isAlias),variable(v){}
	bool equal(Property *p){
		AliasProperty* f=(AliasProperty*)(p);
		return f->isAliasOthers==isAliasOthers&&z3::eq(variable,f->variable);
	}
	std::string toString(){
		std::string ret=Z3_ast_to_string(variable.ctx(),variable);
		if(isAliasOthers){
			ret+=" alias";
		}
		else{
			ret+=" non-alias";
		}
		return ret;
	}
	Property* clone(){
		return new AliasProperty(isAliasOthers,variable);
	}
}; 
class PointerAnalysis: public IntraDataFlowAnalysis{
	
private:
	/*context &c;*/
	Z3Coding &z3coding;
	C2Z3* c2z3Stmt;
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
		std::string ret="";
		for(Property* p:*S){
			ret+="["+p->toString()+"];";
		}
		return ret;
	}
	int getIndex(vector<Property*> * Pre,expr v){
		for(int i=0;i<(int)Pre->size();i++){
			AliasProperty* ap=(AliasProperty*)Pre->at(i);
			if(z3coding.equal(ap->variable,v)){
				return i;
			}
		}
		return -1;
	}
	vector<Property*> * Pos(const clang::Stmt* stmt,vector<Property*> * Pre,expr formulaStmt){
		vector<Property*> * ret=new vector<Property*>();
		if(z3coding.isAssignment(formulaStmt)){
			expr rhs=formulaStmt.arg(0).arg(1);
			if(z3coding.isAddrOfExpr(rhs)){
				int index=getIndex(Pre,rhs.arg(0));
				if(index<0){
				//e1=&e2, but e2 is complex,we do not find it on localVariable
				//we think e2 may is alias of any local variable
					for(Property* p:*Pre){
						AliasProperty* ap=(AliasProperty*)p;
						ret->push_back(new AliasProperty(true,ap->variable));
					}
				}
				else{
					for(int i=0;i<(int)Pre->size();i++){
						AliasProperty* ap=(AliasProperty*)Pre->at(i);
						if(i==index){
							ret->push_back(new AliasProperty(true,ap->variable));
						}
						else{
							ret->push_back(new AliasProperty(ap->isAliasOthers,ap->variable));
						}
					}
				}
			}
			else{
				pushAToB(Pre,ret);
			}
		}
		else{
			pushAToB(Pre,ret);
		}
		return ret;
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
	AliasProperty* getAliasProperty(FlowSet* S,expr e){
		unique_ptr<vector<Property *>> vs=S->toVector();
		for(Property* p:*vs){
			AliasProperty* ap=(AliasProperty*)p;
			if(z3coding.equal(ap->variable,e)){
				return ap;
			}
		}
		return nullptr;
	}
public:
	PointerAnalysis(FunctionDecl * functionDecl,clang::CFG* cfg,/*context &ctx,*/Z3Coding &coding,C2Z3* c2z3)
	:IntraDataFlowAnalysis(functionDecl,cfg),/*c(ctx),*/z3coding(coding),c2z3Stmt(c2z3){
			pre_init();
			pre_init_stmtExpr();
			doAnalysis();
	}
	
	bool isMemoryUnitIsInBefor(const clang::Stmt* stmt,unsigned count,expr memory1,expr memory2){
		//check type
		vector<FlowSet*>* ins= mapToStmtExprIn.at(stmt);
		FlowSet* in=ins->at(count);
		if(z3coding.isDer_PointerExpr(memory1)&&memory2.is_const()){
			AliasProperty* ap=getAliasProperty(in,memory2);
			if(ap==nullptr){
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
			}
			else{
				if(!ap->isAliasOthers){
					return false;
				}
				else{
					return true;
				}
			}
		}
		else if(z3coding.isDer_PointerExpr(memory1)&&z3coding.isArrayAcess(memory2)){
			#ifdef _WellTypeBehavior
				return pointerRelationBaseOnTypeInfo(memory1,memory2);
			#endif
			#ifndef _WellTypeBehavior
				return true;
			#endif
		}
		else if(memory1.is_const()&&z3coding.isDer_PointerExpr(memory2)){
			AliasProperty* ap=getAliasProperty(in,memory1);
			if(ap==nullptr){
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
			}
			else{
				if(!ap->isAliasOthers){
					return false;
				}
				else{
					return true;
				}
			}
		}
		else if(z3coding.isArrayAcess(memory1)&&z3coding.isDer_PointerExpr(memory2)){
			#ifdef _WellTypeBehavior
				return pointerRelationBaseOnTypeInfo(memory1,memory2);
			#endif
			#ifndef _WellTypeBehavior
				return true;
			#endif
		}
		else if(z3coding.isDer_PointerExpr(memory1)&&z3coding.isDer_PointerExpr(memory2)){
			expr pointer1 =memory1.arg(0);
			expr pointer2 =memory2.arg(0);
			expr assert=pointer1==pointer2;
			if(z3coding.satisfy(assert)==check_result::unsat){
				return false;
			}
			#ifdef _WellTypeBehavior
				return pointerRelationBaseOnTypeInfo(memory1,memory2);
			#endif
			#ifndef _WellTypeBehavior
				return true;
			#endif
		}
		else{
			cerr<<"PointerAnalysis::isMemoryUnitIsInBefor:something is wrong"<<std::endl;
			cerr<<"Error info::memory1:"<<memory1<<", memory2:"<<memory2<<std::endl;
			return true;
		}
	}
	
	
	
	bool pointerRelationBaseOnTypeInfo(expr memory1,expr memory2){
		const Type* ty1=z3coding.getTypeBy(memory1);
		const Type* ty2=z3coding.getTypeBy(memory2);
		if(ty1!=nullptr&&ty2!=nullptr){
			//cout<<memory1<<" type == "<<memory2<<" type?"<<(ty1->getCanonicalTypeInternal()==ty2->getCanonicalTypeInternal())<<std::endl;
			/*cout<<"ty1: "<<z3coding.toString(ty1->getCanonicalTypeInternal())<<std::endl;
			cout<<"ty2: "<<z3coding.toString(ty2->getCanonicalTypeInternal())<<std::endl;
			cout<<"ty1 is pointer?: "<<ty1->isPointerType()<<std::endl;
			cout<<"ty2 is pointer?: "<<ty2->isPointerType()<<std::endl;*/
			if(ty1->getCanonicalTypeInternal()!=ty2->getCanonicalTypeInternal()){
				return false;
			}
		}
		return true;
	}	
	/**
	 * @brief memory1 is pointermemory ,memory2 is pointed memory
	 * @param stmt
	 * @param count
	 * @param memory1
	 * @param memory2
	 * @return 
	 */
	
	bool isMemoryUnitIsInAfter(const clang::Stmt* stmt,unsigned count,expr memory1,expr memory2){
		//cout<<"memory1: "<<memory1<<" , memory2: "<<memory2<<std::endl;
		vector<vector<FlowSet*>*>* outs= mapToStmtExprOut.at(stmt);
		FlowSet* out=outs->at(0)->at(count);
		if(z3coding.isDer_PointerExpr(memory1)&&memory2.is_const()){
			AliasProperty* ap=getAliasProperty(out,memory2);
			if(ap==nullptr){
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
				
			}
			else{
				if(!ap->isAliasOthers){
					return false;
				}
				else{
					return true;
				}
			}
		}
		else if(z3coding.isDer_PointerExpr(memory1)&&z3coding.isArrayAcess(memory2)){
			#ifdef _WellTypeBehavior
				return pointerRelationBaseOnTypeInfo(memory1,memory2);
			#endif
			#ifndef _WellTypeBehavior
				return true;
			#endif
		}
		else if(memory1.is_const()&&z3coding.isDer_PointerExpr(memory2)){
			AliasProperty* ap=getAliasProperty(out,memory1);
			if(ap==nullptr){
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
			}
			else{
				if(!ap->isAliasOthers){
					return false;
				}
				else{
					return true;
				}
			}
		}
		else if(z3coding.isArrayAcess(memory1)&&z3coding.isDer_PointerExpr(memory2)){
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
		}
		else if(z3coding.isDer_PointerExpr(memory1)&&z3coding.isDer_PointerExpr(memory2)){
			expr pointer1 =memory1.arg(0);
			expr pointer2 =memory2.arg(0);
			expr assert=pointer1==pointer2;
			if(z3coding.satisfy(assert)==check_result::unsat){
				return false;
			}
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
		}
		else {
			AliasProperty* ap=getAliasProperty(out,memory2);
			if(ap==nullptr){
				#ifdef _WellTypeBehavior
					return pointerRelationBaseOnTypeInfo(memory1,memory2);
				#endif
				#ifndef _WellTypeBehavior
					return true;
				#endif
			
			}
			else{
				if(!ap->isAliasOthers){
					return false;
				}
				else{
					return true;
				}
			}
		}
//		else{
//			cerr<<"PointerAnalysis::isMemoryUnitIsInAfter:something is wrong"<<std::endl;
//			cerr<<"Error info::memory1:"<<memory1<<", memory2:"<<memory2<<std::endl;
//			return true;
//		}
	}
	
	map<const clang::Stmt*, FlowSet*> mapToStmtIn;
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtOut;
	
	map<const clang::Stmt*, vector<FlowSet*>*> mapToStmtExprIn;
	map<const clang::Stmt*, vector<vector<FlowSet*>*>*> mapToStmtExprOut; //first vector is succ
	
		
	vector<Property*> * GenAndKill(vector<Property*> * Pre,const clang::Stmt* stmt){
		
		#ifdef _DEBUG
		cout<<"stmt:: "<<z3coding.toString(stmt)<<std::endl;
		cout<<"Pre:: "<<toString(Pre)<<std::endl;
		#endif
		//------------stmt to  formulasStmt---------------------------------------------
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
		
		//------------init mapToStmtExprIn&init mapToStmtExprOut---------------------------------------------
		vector<Property*> * _Pre=Pre;
		for(unsigned i=0;i<stmtFormulas->size();i++){
			
			mapToStmtExprIn.at(stmt)->at(i)->clear();
			mapToStmtExprIn.at(stmt)->at(i)->Union(PropertySetToFlowSet(_Pre));
			
			expr stmtF=stmtFormulas->at(i);
			_Pre=Pos(stmt,_Pre,stmtF);
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
		
		
		vector<Property*> * _Pre=Pre;
		for(unsigned i=0;i<stmtFormulas->size();i++){
			//cout<<mapToStmtExprIn.at(T)->size()<<std::endl;
			//cout<<i<<std::endl;
			mapToStmtExprIn.at(T)->at(i)->clear();
			mapToStmtExprIn.at(T)->at(i)->Union(PropertySetToFlowSet(_Pre));
			
			expr stmtF=stmtFormulas->at(i);
			_Pre=Pos(T,_Pre,stmtF);
			
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
		
		
	void flowThrouth(CFGBlock*&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){
		//cout<<"processing ... "<<n->getBlockID()<<std::endl;
		for(auto it=outs->begin();it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*>* ele=*it;
			if(ele->second->isUniversalSet()){
				ele->second->setNonUniversalSetWhenIsUniversalSet();
			}
		}
		
		unique_ptr<vector<Property *>> PrePtr=in->toVector();			
		vector<Property *>* Pre=PrePtr.get();
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
	FlowSet * newinitialFlow(){
		FlowSet* ret=new ValueListSetWithUniversalSet();
		vector<expr>* localDeclVariables=c2z3Stmt->getLocalDeclVariables();
		//cout<<"it is 333"<<std::endl;
		for(expr l:*localDeclVariables){
			ret->add(new AliasProperty(false,l));
		}
		//cout<<"it is 444"<<std::endl;
		return ret;
		
	}
	FlowSet * entryInitialFlow(){
		FlowSet* ret=new ValueListSetWithUniversalSet();
		vector<expr>* localDeclVariables=c2z3Stmt->getLocalDeclVariables();
		for(expr l:*localDeclVariables){
			ret->add(new AliasProperty(false,l));
		}
		return ret;
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
	FlowSet * meet(vector<Property*>* in1,vector<Property*>* in2){
		FlowSet * ret=new ValueListSetWithUniversalSet();
		if(in1->size()!=in2->size()){
			cerr<<"PointerAnalysis::meet::something is wrong! in1->size()!=in2->size()"<<std::endl;
			return ret;
		}
		for(int i=0;i<(int)in1->size();i++){
			AliasProperty* ap1=(AliasProperty*)in1->at(i);
			AliasProperty* ap2=(AliasProperty*)in2->at(i);
			if(ap1->isAliasOthers||ap2->isAliasOthers){
				ret->add(new AliasProperty(true,ap1->variable));
			}
			else{
				ret->add(new AliasProperty(false,ap1->variable));
			}
		}
		return ret;
	}
	
};
#endif
	