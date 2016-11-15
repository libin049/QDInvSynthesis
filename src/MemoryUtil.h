#ifndef _MemoryUtil_H
#define _MemoryUtil_H
#include "z3++.h"
#include "Z3Coding.h"
#include "Formula.h"
/***
 * forany formula  that statement stmt generates, it is a simple formula
 * befor stmt, a set of formulas Pre holds
 * after stmt, we need computing Pos, which is a set of formulas holds after stmt
 * note that: we regard stmt as formula, it will generate formula about fresh value of 
 * 	variable(we call it primed varibale); there exists not primed varibale in Pre;
 * 	all varibales who exist in Pos is primed variable
 * 	then we substitute primed variable by unprimed variable in Pos, we call it unprimed(Pos)
 *  unprimed(Pos) as Pre of next statement, then repeat
 * 
 ***/

class MemoryUtil{
	private:
		Z3Coding &z3Coding;
		PointerAnalysis* pointerAnalysis;
		void pushAToB(vector<expr> * & A,vector<expr> * & B){
			for(auto it=A->begin();it != A->end(); it++){
				expr t=*it;
				B->push_back(t);
			}
		}
		vector<expr> * eliminateNotInSimpleFormulas(vector<expr> * formulas){
			vector<expr>* result=new  vector<expr>();
			for(expr f: *formulas){
				result->push_back(z3Coding.eliminateNotInSimpleFormula(f));
			}
			return result;
		}
		
		/**
		 * @brief memoryunit1's memory may isin constsMemory set of memoryunit2 
		 * @param memoryunit1
		 * @param memoryunit2
		 * @return  
		 */
		bool mayMemoryUnitIsIn(expr memoryunit1,expr memoryunit2,const clang::Stmt *clangStmt,int count){
			//cout<<"2222 "<<memoryunit1<<" is in "<<memoryunit2<<std::endl;
			if(memoryunit1.is_const()&&memoryunit2.is_const()){
				return z3Coding.equal(memoryunit1,memoryunit2);
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&memoryunit2.is_const()){
				//memoryunit1:A[i]  memoryunit2:A
				expr base1=z3Coding.getArrayBase(memoryunit1);
				return z3Coding.equal(base1,memoryunit2);
			}
			else if(memoryunit1.is_const()&&z3Coding.isArrayAcess(memoryunit2)){
				auto consts=z3Coding.getConsts(memoryunit2);
				for(auto it=consts->begin();it!=consts->end();it++){
					expr con=*it;
					if(z3Coding.equal(memoryunit1,con)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				//A[exp1][exp2]* B[exp1][exp2]*
				expr base1=z3Coding.getArrayBase(memoryunit1);
				expr base2=z3Coding.getArrayBase(memoryunit2);
				if(!z3Coding.equal(base1,base2)){
					return false;
				}
				auto indexes1=z3Coding.getArrayAcessIdxes(memoryunit1);
				auto indexes2=z3Coding.getArrayAcessIdxes(memoryunit2);
				expr assert=base1.ctx().bool_val(true);
				for(int i=0;i<(int)indexes1->size()&&i<(int)indexes2->size();i++){
					assert=assert&&(indexes1->at(i)==indexes2->at(i));
				}
				//cout<<assert<<std::endl;
				if(z3Coding.satisfy(assert)==check_result::unsat){
					return false;
				}
				return true;
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&memoryunit2.is_const()){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
		
			else if(memoryunit1.is_const()&&z3Coding.isDer_PointerExpr(memoryunit2)){
				//get memory unit of memoryunit2
				expr pointerExprOfmu2=z3Coding.getPointerExpr(memoryunit2);
				auto memoryUnitsOfPointerExprOfmu2=z3Coding.getMemoryUnits(pointerExprOfmu2);
				for(expr ele:*memoryUnitsOfPointerExprOfmu2){
					if(mayMemoryUnitIsIn(memoryunit1,ele,clangStmt,count)){
						return true;
					}
				}
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isDer_PointerExpr(memoryunit2)){
				expr pointerExprOfmu2=z3Coding.getPointerExpr(memoryunit2);
				auto memoryUnitsOfPointerExprOfmu2=z3Coding.getMemoryUnits(pointerExprOfmu2);
				for(expr ele:*memoryUnitsOfPointerExprOfmu2){
					if(mayMemoryUnitIsIn(memoryunit1,ele,clangStmt,count)){
						return true;
					}
				}
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&z3Coding.isDer_PointerExpr(memoryunit2)){
				expr pointerExprOfmu2=z3Coding.getPointerExpr(memoryunit2);
				auto memoryUnitsOfPointerExprOfmu2=z3Coding.getMemoryUnits(pointerExprOfmu2);
				for(expr ele:*memoryUnitsOfPointerExprOfmu2){
					if(mayMemoryUnitIsIn(memoryunit1,ele,clangStmt,count)){
						return true;
					}
				}
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(memoryunit1.is_const()&&z3Coding.isMemberExpr(memoryunit2)){
				return false;
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&memoryunit2.is_const()){
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isMemberExpr(memoryunit2)){
				return false;
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				return false;
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&z3Coding.isMemberExpr(memoryunit2)){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&z3Coding.isDer_PointerExpr(memoryunit2)){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&z3Coding.isMemberExpr(memoryunit2)){
				if(!Z3_is_eq_func_decl(memoryunit1.ctx(),memoryunit1.decl(),memoryunit2.decl())){
					return false;
				}
				
				expr access1=	memoryunit1.arg(0);
				expr access2=	memoryunit2.arg(0);
				if (z3Coding.isIndirectMemberExpr(memoryunit1)){
					return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,access1,access2);
				}
				else{
					return z3Coding.equal(access1,access2);
				}
			}
			else{
				std::cerr<<"MemoryUtil:mayMemoryUnitIsIn: something is wrong!"<<std::endl;
				std::cerr<<"error info:: memoryunit1: "<<memoryunit1<<", memoryunit2: "<<memoryunit2 <<std::endl;
				return true;
			}
			return true;
		}
		
		bool mayMemoryUnitIsIn(vector<expr>* Pre,expr memoryunit1,expr memoryunit2,const clang::Stmt *clangStmt,int count){
			//cout<<"2222 "<<memoryunit1<<" is in "<<memoryunit2<<std::endl;
			if(memoryunit1.is_const()&&memoryunit2.is_const()){
				return z3Coding.equal(memoryunit1,memoryunit2);
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&memoryunit2.is_const()){
				//memoryunit1:A[i]  memoryunit2:A
				expr base1=z3Coding.getArrayBase(memoryunit1);
				return z3Coding.equal(base1,memoryunit2);
			}
			else if(memoryunit1.is_const()&&z3Coding.isArrayAcess(memoryunit2)){
				auto consts=z3Coding.getConsts(memoryunit2);
				for(auto it=consts->begin();it!=consts->end();it++){
					expr con=*it;
					if(z3Coding.equal(memoryunit1,con)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				//A[exp1][exp2]* B[exp1][exp2]*
				expr base1=z3Coding.getArrayBase(memoryunit1);
				expr base2=z3Coding.getArrayBase(memoryunit2);
				if(!z3Coding.equal(base1,base2)){
					return false;
				}
				auto indexes1=z3Coding.getArrayAcessIdxes(memoryunit1);
				auto indexes2=z3Coding.getArrayAcessIdxes(memoryunit2);
				expr assert=base1.ctx().bool_val(true);
				for(int i=0;i<(int)indexes1->size()&&i<(int)indexes2->size();i++){
					assert=assert&&(indexes1->at(i)==indexes2->at(i));
				}
				//cout<<assert<<std::endl;
				if(z3Coding.satisfy(Pre,assert)==check_result::unsat){
					return false;
				}
				return true;
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&memoryunit2.is_const()){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
		
			else if(memoryunit1.is_const()&&z3Coding.isDer_PointerExpr(memoryunit2)){
				expr pointerExprOfmu2=z3Coding.getPointerExpr(memoryunit2);
				auto memoryUnitsOfPointerExprOfmu2=z3Coding.getMemoryUnits(pointerExprOfmu2);
				for(expr ele:*memoryUnitsOfPointerExprOfmu2){
					if(mayMemoryUnitIsIn(Pre,memoryunit1,ele,clangStmt,count)){
						return true;
					}
				}
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isDer_PointerExpr(memoryunit2)){
				expr pointerExprOfmu2=z3Coding.getPointerExpr(memoryunit2);
				auto memoryUnitsOfPointerExprOfmu2=z3Coding.getMemoryUnits(pointerExprOfmu2);
				for(expr ele:*memoryUnitsOfPointerExprOfmu2){
					if(mayMemoryUnitIsIn(Pre,memoryunit1,ele,clangStmt,count)){
						return true;
					}
				}
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&z3Coding.isDer_PointerExpr(memoryunit2)){
				expr pointerExprOfmu2=z3Coding.getPointerExpr(memoryunit2);
				auto memoryUnitsOfPointerExprOfmu2=z3Coding.getMemoryUnits(pointerExprOfmu2);
				for(expr ele:*memoryUnitsOfPointerExprOfmu2){
					if(mayMemoryUnitIsIn(Pre,memoryunit1,ele,clangStmt,count)){
						return true;
					}
				}
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(memoryunit1.is_const()&&z3Coding.isMemberExpr(memoryunit2)){
				return false;
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&memoryunit2.is_const()){
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isMemberExpr(memoryunit2)){
				return false;
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				return false;
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)&&z3Coding.isMemberExpr(memoryunit2)){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&z3Coding.isDer_PointerExpr(memoryunit2)){
				return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,memoryunit1,memoryunit2);
			}
			else if(z3Coding.isMemberExpr(memoryunit1)&&z3Coding.isMemberExpr(memoryunit2)){
				if(!Z3_is_eq_func_decl(memoryunit1.ctx(),memoryunit1.decl(),memoryunit2.decl())){
					return false;
				}
				
				expr access1=	memoryunit1.arg(0);
				expr access2=	memoryunit2.arg(0);
				if (z3Coding.isIndirectMemberExpr(memoryunit1)){
					return pointerAnalysis->isMemoryUnitIsInAfter(clangStmt,count,access1,access2);
				}
				else{
					return z3Coding.equal(access1,access2);
				}
			}
			else{
				std::cerr<<"MemoryUtil:mayMemoryUnitIsIn: something is wrong!"<<std::endl;
				std::cerr<<"error info:: memoryunit1: "<<memoryunit1<<", memoryunit2: "<<memoryunit2 <<std::endl;
				return true;
			}
			return true;
		}
		
		
		std::string toString(vector<z3::expr>* exprs){
			std::string ret="";
			if(exprs==nullptr) return "";
			for(auto it=exprs->begin();it!=exprs->end();it++){
				z3::expr e=(z3::expr) *it;
				std::string eName=z3Coding.toString(e);
				ret+=eName+";\n ";
			}
			return ret;
		}
		
	public:
		MemoryUtil(Z3Coding &coding,PointerAnalysis* pointerAna):z3Coding(coding),pointerAnalysis(pointerAna){
		}

		

		/**
		 * @brief memoryunit1 is unprimedexpr
		 * @param memoryunit1
		 * @param formula
		 * @return 
		 */
		bool mayMemoryUnitIsInFormula(expr memoryunit1,expr formula,const clang::Stmt *clangStmt,int count){
			//cout<<memoryunit1<<" is in "<<formula<<std::endl;
			if(memoryunit1.is_const()){
				auto consts=z3Coding.getConsts(formula);
				for(auto it=consts->begin();it!=consts->end();it++){
					expr con=*it;
					if(z3Coding.equal(memoryunit1,con)){//mayMemoryUnitIsIn(memoryunit1,con)
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)){
				auto formulaMemoryUnits=z3Coding.getMemoryUnits(formula);
				for(expr memoryUnit: *formulaMemoryUnits){
					//cout<<"debug::"<<memoryUnit<<std::endl;
					if(mayMemoryUnitIsIn(memoryunit1,memoryUnit,clangStmt,count)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)){
				auto formulaMemoryUnits=z3Coding.getMemoryUnits(formula);
				for(expr memoryUnit: *formulaMemoryUnits){
					if(mayMemoryUnitIsIn(memoryunit1,memoryUnit,clangStmt,count)){
						return true;
					}
				}
				return false;
			}
			
			else if(z3Coding.isDirectMemberExpr(memoryunit1)){
				auto formulaMemoryUnits=z3Coding.getMemoryUnits(formula);
				for(expr memoryUnit: *formulaMemoryUnits){
					if(mayMemoryUnitIsIn(memoryunit1,memoryUnit,clangStmt,count)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isIndirectMemberExpr(memoryunit1)){
				auto formulaMemberMemoryUnits=z3Coding.getMemberMemoryUnits(formula);
				for(expr memberMemoryUnit: *formulaMemberMemoryUnits){
					if(Z3_is_eq_func_decl(memoryunit1.ctx(),memoryunit1.decl(),memberMemoryUnit.decl())){
						return true;
					}
				}
				return false;
			}	
			else{
				std::cerr<<"MemoryUtil:mayMemoryUnitIsInFormula: we can not process "<<memoryunit1<<std::endl;
				std::cerr<<"Error info: memoryunit1 is: "<<memoryunit1<<std::endl;
				std::cerr<<"Error info: formula is: "<<formula<<std::endl;
				return true;
			}
		}
		bool mayMemoryUnitIsInFormula(vector<expr>* Pre, expr memoryunit1,expr formula,const clang::Stmt *clangStmt,int count){
			//cout<<memoryunit1<<" is in "<<formula<<std::endl;
			if(memoryunit1.is_const()){
				auto consts=z3Coding.getConsts(formula);
				for(auto it=consts->begin();it!=consts->end();it++){
					expr con=*it;
					if(z3Coding.equal(memoryunit1,con)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)){
				auto formulaMemoryUnits=z3Coding.getMemoryUnits(formula);
				for(expr memoryUnit: *formulaMemoryUnits){
					if(mayMemoryUnitIsIn(Pre,memoryunit1,memoryUnit,clangStmt,count)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)){
				auto formulaMemoryUnits=z3Coding.getMemoryUnits(formula);
				for(expr memoryUnit: *formulaMemoryUnits){
					if(mayMemoryUnitIsIn(Pre,memoryunit1,memoryUnit,clangStmt,count)){
						return true;
					}
				}
				return false;
			}
			
			else if(z3Coding.isDirectMemberExpr(memoryunit1)){
				auto formulaMemoryUnits=z3Coding.getMemoryUnits(formula);
				for(expr memoryUnit: *formulaMemoryUnits){
					if(mayMemoryUnitIsIn(Pre,memoryunit1,memoryUnit,clangStmt,count)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isIndirectMemberExpr(memoryunit1)){
				auto formulaMemberMemoryUnits=z3Coding.getMemberMemoryUnits(formula);
				for(expr memberMemoryUnit: *formulaMemberMemoryUnits){
					if(Z3_is_eq_func_decl(memoryunit1.ctx(),memoryunit1.decl(),memberMemoryUnit.decl())){
						return true;
					}
				}
				return false;
			}	
			else{
				std::cerr<<"MemoryUtil:mayMemoryUnitIsInFormula: we can not process "<<memoryunit1<<std::endl;
				std::cerr<<"Error info: memoryunit1 is: "<<memoryunit1<<std::endl;
				std::cerr<<"Error info: formula is: "<<formula<<std::endl;
				return true;
			}
		}
		
		bool mustMemoryUnitIsIn(expr memoryunit1,expr memoryunit2,const clang::Stmt *clangStmt,int count){
			if(memoryunit1.is_const()&&memoryunit2.is_const()){
				return z3Coding.equal(memoryunit1,memoryunit2);
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&memoryunit2.is_const()){
				//memoryunit1:A[i]  memoryunit2:A
				expr base1=z3Coding.getArrayBase(memoryunit1);
				return z3Coding.equal(base1,memoryunit2);
			}
			else if(memoryunit1.is_const()&&z3Coding.isArrayAcess(memoryunit2)){
				auto consts=z3Coding.getConsts(memoryunit2);
				for(auto it=consts->begin();it!=consts->end();it++){
					expr con=*it;
					if(z3Coding.equal(memoryunit1,con)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				return z3Coding.equal(memoryunit1,memoryunit2);
			}
			else if(z3Coding.isDer_PointerExpr(memoryunit1)||z3Coding.isDer_PointerExpr(memoryunit2)){
				return z3Coding.equal(memoryunit1,memoryunit2);
			}
			else if(z3Coding.isMemberExpr(memoryunit1)||z3Coding.isMemberExpr(memoryunit2)){
				return z3Coding.equal(memoryunit1,memoryunit2);
			}
			else{
				std::cerr<<"MemoryUtil:mustMemoryUnitIsIn: something is wrong!"<<std::endl;
				return false;
			}
			return false;
		}
		
		/*bool isLtZero(expr e){
			if(!e.is_int()){
				std::cerr<<"MemoryUtil::isLtZero::"<< e <<" must be int type!"<<std::endl;	
				return false;
			}
			else{
				if(e.is_numeral()){
					std::string tmp=Z3_ast_to_string(e.ctx(),e);
					if(std::stoi(tmp)<0) return true;
				}
				if(e.is_app()&&e.decl().name().str()=="-"){
					if(e.arg(0).is_numeral()){
						std::string tmp=Z3_ast_to_string(e.ctx(),e.arg(0));
						if(std::stoi(tmp)<0) return true;
					}
				}
				return false;
			}
		}
		
		bool isGtZero(expr e){
			if(!e.is_int()){
				std::cerr<<"MemoryUtil::isGtZero::"<< e <<" must be int type!"<<std::endl;	
				return false;
			}
			else{
				if(e.is_numeral()){
					std::string tmp=Z3_ast_to_string(e.ctx(),e);
					if(std::stoi(tmp)>0) return true;
				}
				if(e.is_app()&&e.decl().name().str()=="-"){
					if(e.arg(0).is_numeral()){
						std::string tmp=Z3_ast_to_string(e.ctx(),e.arg(0));
						if(std::stoi(tmp)>0) return true;
					}
				}
				return false;
			}
		}*/
		
		bool isLtZero(expr e){
			if(!e.is_int()&&!e.is_real()){
				std::cerr<<"MemoryUtil::isLtZero::"<< e <<" must be int or real type!"<<std::endl;	
				return false;
			}
			else{
				expr assert=e<0;
				if(z3Coding.prove(assert)==proved_result::proved){
					return true;
				}
				return false;
			}
		}
		
		bool isGtZero(expr e){
			if(!e.is_int()&&!e.is_real()){
				std::cerr<<"MemoryUtil::isGtZero::"<< e <<" must be int or real type!"<<std::endl;	
				return false;
			}
			else{
				expr assert=e>0;
				if(z3Coding.prove(assert)==proved_result::proved){
					return true;
				}
				return false;
			}
		}
};


#endif

