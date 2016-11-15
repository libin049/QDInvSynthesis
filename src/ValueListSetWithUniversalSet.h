#ifndef _ValueListSetWithUniversalSet_H
#define _ValueListSetWithUniversalSet_H
#include "FlowSet.h"
#include <list>
using namespace std;
//template <typename T>
class ValueListSetWithUniversalSet: public FlowSet{
private:
	bool isUniversalSetFlag;
public:
	list<Property *> elements;
	ValueListSetWithUniversalSet(bool isUniversalSet){this->isUniversalSetFlag=isUniversalSet;}
	ValueListSetWithUniversalSet(){this->isUniversalSetFlag=false;}
	//static ConditionValueListSet *UniversalSet;
	~ValueListSetWithUniversalSet(){
		for(auto ref:elements){
			delete ref;
		}
	} 
	FlowSet* clone(){
		ValueListSetWithUniversalSet* newSet=new ValueListSetWithUniversalSet(this->isUniversalSetFlag);
		for(auto it=elements.begin();it != elements.end(); it++){
			Property *t=*it;
			newSet->elements.push_back(t->clone());
		}
		return newSet;
	}
	bool equal(FlowSet * flow){
		if(flow->size()!=this->size()) return false;
		if(this->isUniversalSet()!=flow->isUniversalSet()) return false;
		for(auto it=elements.begin();it != elements.end(); it++){
			Property *t=*it;
			if(!flow->isIn(t)){
				return false;
			}
		}
		return true;
	}
	bool isIn(Property *ele){
		if(this->isUniversalSet()) return true;
		for(auto it=elements.begin();it != elements.end(); it++){
			Property *t=*it;
			if(ele->equal(t)){
				return true;
			}
		}
		return false;
	}
	
	void intersection(FlowSet * flow){
		if(flow->isUniversalSet()) return;
		if(this->isUniversalSet()) {this->clear();this->Union(flow);return;}
		
		list<Property*> newelements;
		for(auto it=elements.begin();it != elements.end(); it++){
			Property *t=*it;
			if(flow->isIn(t)){
				newelements.push_back(t);
			}
		}
		this->elements.clear();
		for(auto it=newelements.begin();it != newelements.end(); it++){
			Property *t=*it;
			this->elements.push_back(t);
		}
	}
	void clear(){
		isUniversalSetFlag=false;
		elements.clear();
	}
	bool remove(Property *ele){
		if(this->isUniversalSet()) {
			cerr<<"remove one element from UniversalSet lead to UniversalSet being EmptySet!"<<std::endl;
			this->isUniversalSetFlag=false;
			return true;
		}
		for(auto it=elements.begin();it != elements.end(); it++){
			Property *t=*it;
			if(ele->equal(t)){
				elements.remove(t);
				return true;
			}
		}
		return false;
	}
	bool add(Property *ele){
		if(this->isUniversalSet()) {
			return true;
		}
		if(!isIn(ele)){
			elements.push_back(ele);
			return true;
		}
		return false;
	}
	std::string toString(){
		if(this->isUniversalSet()) {
			return "UniversalSet";
		}
		std::string ret="";
		for(auto it=elements.begin();it != elements.end(); it++){
			Property *t=*it;
			ret+="["+t->toString()+"] ";
		}
		return ret;
	}
	void print(){std::cout<<toString()<<std::endl;}
	int size(){
		return elements.size();
	}
	void Union(FlowSet *flow){
		if(flow->isUniversalSet()) {this->clear();this->isUniversalSetFlag=true;return;}
		if(this->isUniversalSet()) {return;}
		ValueListSetWithUniversalSet *listSet=(ValueListSetWithUniversalSet *)flow;
		for(auto it=listSet->elements.begin();it != listSet->elements.end(); it++){
			Property *t=*it;
			this->add(t);
		}
	}
	bool isUniversalSet(){return isUniversalSetFlag;}
	void setNonUniversalSetWhenIsUniversalSet(){if(isUniversalSet()) isUniversalSetFlag=false;}
	unique_ptr<vector<Property *>> toVector(){
		unique_ptr<vector<Property *>> result(new vector<Property*>);
		for(auto it=elements.begin();it !=elements.end(); it++){
			Property *t=*it;
			result->push_back(t);
		}
		return result;
	}
};

#endif