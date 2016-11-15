#ifndef _DATAFLOWANALYSIS_FEASIBLEPATH_H
#define _DATAFLOWANALYSIS_FEASIBLEPATH_H
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
#include "FeasiblePath.h"
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace std;

//template <typename T>

class IntraDataFlowAnalysis_FeasiblePath{
private:
	void generateParmVarDecl(){
		for(clang::FunctionDecl::param_iterator it=functionDecl->param_begin();it!=functionDecl->param_end();it++){
			ParmVarDecl * pd=*it;
			parms.push_back(pd);
			/*std::string buffer;
			llvm::raw_string_ostream strout(buffer);
			pd->printName(strout);
			std::string varName=strout.str();
			QualType declQT = pd->getType();
			std::cout<<"varName: "<<varName<<" type: "<<z3coding.toString(declQT)<<std::endl;*/
		}
	}
	FlowSet* computeTrueIn(CFGBlock * n){
		if(n->succ_size()!=2) return nullptr;
		CFGBlock::succ_iterator succ_iter=n->succ_begin();
		CFGBlock *trueSucc=*succ_iter;
		vector<CFGBlock*>* feasiblePred=feasiblePath->getFeasiblePrecursorsOfEdge(n,trueSucc);
		if(feasiblePred->size()==n->pred_size()){
			return nullptr;
		}
		vector<FlowSet *>* trueins=new vector<FlowSet *>();
		for(CFGBlock * pred:*feasiblePred){
			FlowSet  *pred_out=getFlowSetOfEdge(pred,n);
			FlowSet  *tmp=newinitialFlow();
			copy(pred_out,tmp);
			trueins->push_back(tmp);
		}
		return merge(trueins);
	}
	FlowSet* computeFalseIn(CFGBlock * n){
		if(n->succ_size()!=2) return nullptr;
		CFGBlock::succ_iterator succ_iter=n->succ_begin();
		++succ_iter;
		CFGBlock *falseSucc=*succ_iter;
		vector<CFGBlock*>* feasiblePred=feasiblePath->getFeasiblePrecursorsOfEdge(n,falseSucc);
		if(feasiblePred->size()==n->pred_size()){
			return nullptr;
		}
		vector<FlowSet *>* falseins=new vector<FlowSet *>();
		for(CFGBlock * pred:*feasiblePred){
			FlowSet  *pred_out=getFlowSetOfEdge(pred,n);
			FlowSet  *tmp=newinitialFlow();
			copy(pred_out,tmp);
			falseins->push_back(tmp);
		}
		return merge(falseins);
	}
	FlowSet * merge(vector<FlowSet *>* ins){
		if(ins->size()==0) {
			FlowSet * tmp=newinitialFlow();
			tmp->setNonUniversalSetWhenIsUniversalSet();
			return tmp;
		}
		FlowSet  *pred_out=ins->at(0);
		FlowSet  *merge_result=newinitialFlow();
		copy(pred_out,merge_result);
		for(unsigned i=1;i<ins->size();i++){
			pred_out=ins->at(i);
			FlowSet *newFlowSet=newinitialFlow();
			merge(merge_result,pred_out,newFlowSet);
			merge_result=newFlowSet;
		}
		return merge_result;
	}
protected :
	map<CFGBlock*, FlowSet*> mapToBlockIn; // CGFBlock's In dataflow infomation
	map<CFGBlock*, list<pair<CFGBlock*,FlowSet*>*>*> mapToBlockOut; // CFGBlock's Out dataflow infomation,every edge:CFGBlock*1->CFGBlock*2 has dataFlow infonmation FlowSet,CFGBlock*2 is the order of CFGBlock*1's suc.
	clang::CFG* cfg;
	FunctionDecl * functionDecl;
	vector<ParmVarDecl *> parms;
	FeasiblePath* feasiblePath;
public: 
	IntraDataFlowAnalysis_FeasiblePath(FunctionDecl * functionDecl, clang::CFG* cfg, FeasiblePath* fp){
		this->functionDecl=functionDecl;
		this->cfg=cfg;
		this->feasiblePath=fp;
		generateParmVarDecl();
	}	
	virtual ~IntraDataFlowAnalysis_FeasiblePath(){}
	map<CFGBlock*, FlowSet*>* getMapToBlockIn(){
		return &mapToBlockIn;
	}
	map<CFGBlock*, list<pair<CFGBlock*,FlowSet*>*>*>* getMapToBlockOut(){
		return &mapToBlockOut;
	}
	
	void doAnalysis(){
		//init init value and block to visit
		for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
			CFGBlock* block=*iter;
			mapToBlockIn.insert({block,newinitialFlow()});
			list<pair<CFGBlock*,FlowSet*>*>* outs=new list<pair<CFGBlock*,FlowSet*>*>();
			for(CFGBlock::succ_iterator succ_iter=block->succ_begin();succ_iter!=block->succ_end();++succ_iter){
				CFGBlock* succ=*succ_iter;
				pair<CFGBlock*,FlowSet*>* tmp=new pair<CFGBlock*,FlowSet*>(succ,newinitialFlow());
				outs->push_back(tmp);
			}
			mapToBlockOut.insert({block,outs});
		}
		//init entry node
		CFGBlock &entry=cfg->getEntry();
		
		mapToBlockIn[&entry]=entryInitialFlow();
		
		//init worklist
		list<CFGBlock*> worklist; 
		initAndSortWorkList(worklist);
		//print();
		//printWorkList(&worklist);
		while(!worklist.empty())
		{
			#if defined _DEBUG || defined _PERFORMANCE_DEBUG
			//printWorkList(&worklist);
			#endif
			CFGBlock* n=worklist.front();worklist.pop_front();
			#if  defined _DEBUG || defined _PERFORMANCE_DEBUG
			/*if(n->getBlockID()==0){
				std::cout <<"-----------process [B"<< n->getBlockID()<<"]-------------"<<std::endl;
			}*/
			std::cout <<"-----------process [B"<< n->getBlockID()<<"]-------------"<<std::endl;
			#endif
			
			
			list<pair<CFGBlock*,FlowSet*>*> * old=clone(mapToBlockOut.at(n));
			
			if(n!=&entry){
				CFGBlock::pred_iterator pred_iter=n->pred_begin();
				CFGBlock *pred=*pred_iter;
				if(pred==nullptr){
					while(pred_iter!=n->pred_end()) {
						++pred_iter;
						pred=*pred_iter;
						if(pred!=nullptr){
							break;
						}
					}
				}
				if(pred==nullptr){
					cerr<<"DataFlowAnalysis::doAnalysis::something is wrong! pred is null!"<<std::endl;
					return;
				}
				FlowSet  *pred_out=getFlowSetOfEdge(pred,n);
				//FlowSet  *merge_result=pred_out->clone();
				FlowSet  *merge_result=newinitialFlow();
				copy(pred_out,merge_result);
				//std::cout<<"pred_out is: ";pred_out->print();
				++pred_iter;
				while(pred_iter!=n->pred_end()){
					pred=*pred_iter;
					if(pred==nullptr) {
						++pred_iter;
						continue;
					}
					pred_out=getFlowSetOfEdge(pred,n);
					//std::cout<<"pred_out is: ";pred_out->print();
					FlowSet *newFlowSet=newinitialFlow();
					#if  defined _DEBUG 
					//merge_result->print();std::cout<<"-----merge-------";pred_out->print();
					#endif
					merge(merge_result,pred_out,newFlowSet);
					merge_result=newFlowSet;
					++pred_iter;
				}
				#if  defined _DEBUG 
				//std::cout<<"merge_result is: ";merge_result->print();
				#endif
				FlowSet* tmp=mapToBlockIn[n];
				if(tmp!=nullptr){
					delete tmp;
				}
				mapToBlockIn[n]=merge_result;
			}
			else{
				mapToBlockIn[n]=mapToBlockIn.at(&entry);
			}
			list<pair<CFGBlock*,FlowSet*>*> *outs=mapToBlockOut.at(n);
			clearFlowSet(outs);
			/*if(outs->size()==1||outs->size()==0||n->pred_size()==0||n->pred_size()==1){
				flowThrouth(n,mapToBlockIn.at(n),outs);
			}
			else{*/
				FlowSet  *trueIn=computeTrueIn(n);
				FlowSet  *falseIn=computeFalseIn(n);
				flowThrouth(n,mapToBlockIn.at(n),trueIn,falseIn,outs);
			/*}*/
			//printList(outs);
			//cout<<"-------------------"<<std::endl;
			//printList(old);
			if(!equal(outs,old)){
				for(CFGBlock::succ_reverse_iterator  succ_iter=n->succ_rbegin();succ_iter!=n->succ_rend();++succ_iter){
					CFGBlock *succ=*succ_iter;
					if(succ==nullptr) continue;
					//if n->a's out has no change, we will not push a in to worklist to traversal
					//this is also for traversal feasible path
					if(!isIn(worklist,succ)){
						//modify: depth-first Traversal,truebrance first, falsebrance second
						worklist.push_front(succ);/*worklist.push_back(succ);*/
					}
					else{
						worklist.remove(succ);
						worklist.push_front(succ);
					}
				}
			}
			
			
			#ifdef _DEBUG
			//std::cout <<"****************process end [B"<< n->getBlockID ()<<"]*******"<<std::endl;
			//printWorkList(&worklist);
			//print();
			#endif
		}
	}
	virtual FlowSet * newinitialFlow(){return nullptr;}
	virtual FlowSet * entryInitialFlow(){return nullptr;}
	virtual void merge(FlowSet  *&in1,FlowSet  *&in2,FlowSet *&out){}
	virtual void copy(FlowSet  *&from,FlowSet  *&to){return ;}
	virtual bool equal(FlowSet  *&from,FlowSet  *&to){return from->equal(to);}
	//virtual void flowThrouth(CFGBlock *&n, FlowSet *&in, list<pair<CFGBlock*,FlowSet*>*> *&outs){}
	virtual void flowThrouth(CFGBlock *&n, FlowSet *&in,FlowSet *&trueIn,FlowSet *&falseIn, list<pair<CFGBlock*,FlowSet*>*> *&outs){}

	void printWorkList(list<CFGBlock*> *worklist){
		std::cout <<"workList is :";
		for (std::list<CFGBlock*>::iterator it = worklist->begin(); it != worklist->end(); it++){
			CFGBlock* b=*it;
			std::cout <<"[B"<< b->getBlockID ()<<"]"<<" ";
		}
		std::cout <<std::endl;
	}
	virtual void print(){
		for (std::map<CFGBlock*, FlowSet*>::iterator it=mapToBlockIn.begin(); it!=mapToBlockIn.end(); ++it){
			std::cout <<"[B"<< it->first->getBlockID ()<<"]" << " in ::"; it->second->print();
			list<pair<CFGBlock*,FlowSet*>*> * outs=mapToBlockOut.at(it->first);
			for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator outsIt = outs->begin(); 
									outsIt != outs->end(); outsIt++){
				pair<CFGBlock*,FlowSet*> *ele=*outsIt;
				if(ele->first==nullptr) continue;
				std::cout <<"[B"<< it->first->getBlockID()<<"]"<<"-> [B" <<ele->first->getBlockID()<<"]"<<" out :"; ele->second->print();
			}
		}

	}
	void printList(list<pair<CFGBlock*,FlowSet*>*> * outs){
		for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator outsIt = outs->begin(); 
									outsIt != outs->end(); outsIt++){
			pair<CFGBlock*,FlowSet*> *ele=*outsIt;
			if(ele->first==nullptr) continue;
			std::cout <<"[B" <<ele->first->getBlockID()<<"]"<<" :"; ele->second->print();
		}
	}
private:
	void clearFlowSet(list<pair<CFGBlock*,FlowSet*>*> * &outs){
		for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator it = outs->begin(); it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*> *ele=*it;
			ele->second->clear();
		}
	}
	list<pair<CFGBlock*,FlowSet*>*> * clone(list<pair<CFGBlock*,FlowSet*>*> *outs){
		list<pair<CFGBlock*,FlowSet*>*> * ret=new list<pair<CFGBlock*,FlowSet*>*>();
		for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator it = outs->begin(); it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*> *ele=*it;
			pair<CFGBlock*,FlowSet*> *newEle=new pair<CFGBlock*,FlowSet*>();
			newEle->first=ele->first;
			//newEle->second=ele->second->clone();
			newEle->second=newinitialFlow();
			copy(ele->second,newEle->second);
			ret->push_back(newEle);
		}
		return ret;
	}
	bool isIn(list<CFGBlock*> &lists, CFGBlock * n){
		for (std::list<CFGBlock*>::iterator it = lists.begin(); it != lists.end(); it++){
			CFGBlock *ele=*it;
			if(ele==n){
				return true;
			}
		}
		return false;
	}
	bool equal(list<pair<CFGBlock*,FlowSet*>*> * outs1,list<pair<CFGBlock*,FlowSet*>*> * outs2){
		if(outs1->size()!=outs2->size()){
			return false;
		}
		std::list<pair<CFGBlock*,FlowSet*>*>::iterator it1 = outs1->begin();
		std::list<pair<CFGBlock*,FlowSet*>*>::iterator it2 = outs2->begin();
		while(it1 != outs1->end()){
			pair<CFGBlock*,FlowSet*> *ele1=*it1;
			pair<CFGBlock*,FlowSet*> *ele2=*it2;
			if(ele1->first!=ele2->first||!equal(ele1->second,ele2->second)){
				return false;
			}
			it1++;
			it2++;
		}
		return true;
	}
	bool equal(CFGBlock* b,list<pair<CFGBlock*,FlowSet*>*> * outs1,list<pair<CFGBlock*,FlowSet*>*> * outs2){
		if(outs1->size()!=outs2->size()){
			return false;
		}
		std::list<pair<CFGBlock*,FlowSet*>*>::iterator it1 = outs1->begin();
		std::list<pair<CFGBlock*,FlowSet*>*>::iterator it2 = outs2->begin();
		while(it1 != outs1->end()){
			
			pair<CFGBlock*,FlowSet*> *ele1=*it1;
			pair<CFGBlock*,FlowSet*> *ele2=*it2;
			if(ele1->first!=b){
				it1++;
				it2++;
				continue;
			}
			if(ele1->first!=ele2->first||!equal(ele1->second,ele2->second)){
				return false;
			}
			else{
				return true;
			}
			it1++;
			it2++;
		}
		std::cerr<<"equal: something is wrong! "<<std::endl;	
		return false;
	}
	/**
	 * @brief return flowSet of from "from" to "to"
	 * @param from
	 * @param to
	 * @return 
	 */
	FlowSet * getFlowSetOfEdge(CFGBlock* from,CFGBlock* to){
		//cout<<"from: "<<from->getBlockID()<<" to: "<<to->getBlockID()<<std::endl;
		list<pair<CFGBlock*,FlowSet*>*> *outs=mapToBlockOut.at(from);
		for (std::list<pair<CFGBlock*,FlowSet*>*>::iterator it = outs->begin(); it != outs->end(); it++){
			pair<CFGBlock*,FlowSet*> *ele=*it;
			if(ele->first==to){
				return ele->second;
			}
		}
		return nullptr;
	}
	void initAndSortWorkList(list<CFGBlock*> &worklist){
		CFGBlock &entry=cfg->getEntry();
		list<CFGBlock*> queue;
//		worklist.push_back(&entry);
//		for(CFGBlock::succ_iterator succ_iter=entry.succ_begin();succ_iter!=entry.succ_end();++succ_iter){
//				CFGBlock *succ=*succ_iter;
//				worklist.push_back(succ);
//		}
		
		queue.push_back(&entry);
		while(!queue.empty()){
			CFGBlock* n=queue.front();queue.pop_front();
			//get succ of n
			
			if(!isIn(worklist,n)){
				worklist.push_back(n);
				for(CFGBlock::succ_iterator succ_iter=n->succ_begin();succ_iter!=n->succ_end();++succ_iter){
					CFGBlock *succ=*succ_iter;
					if(succ!=nullptr){
						queue.push_back(succ);
					}
					
				}
			}
			
		}
	}
	
	
};
#endif