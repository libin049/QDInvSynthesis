#ifndef _EnvironmentAnalysisUtil_H
#define _EnvironmentAnalysisUtil_H

#include "Z3Coding.h"
#include "Formula.h"
#include "PointerAnalysis.h"
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

class EnvironmentAnalysisUtil{
	private:
		Z3Coding &z3Coding;
		context &c;
		//AtomVariablaAnalysis *indexAnalysis;
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
		 * for *pointer, 
		 * angelic hypothesis:
		 * 		we assume 
		 * the result offer unsopund result
		 *  
		 * @param memoryunit1
		 * @param memoryunit2
		 * @return  
		 */
		bool mayMemoryUnitIsIn(expr memoryunit1,expr memoryunit2,const clang::Stmt* clangStmt,int count){
			if(memoryunit1.is_const()&&memoryunit2.is_const()){
				return memoryunit1.decl().name().str()==memoryunit2.decl().name().str();
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&memoryunit2.is_const()){
				//memoryunit1:A[i]  memoryunit2:A
				expr base1=z3Coding.getArrayBase(memoryunit1);
				return z3Coding.equal(base1,memoryunit1);// base1.decl().name().str()==memoryunit2.decl().name().str();
			}
			else if(memoryunit1.is_const()&&z3Coding.isArrayAcess(memoryunit2)){
				auto consts=z3Coding.getConsts(memoryunit2);
				for(auto it=consts->begin();it!=consts->end();it++){
					expr con=*it;
					//if(memoryunit1.decl().name().str()==con.decl().name().str()){
					if(z3Coding.equal(memoryunit1,con)){
						return true;
					}
				}
				return false;
			}
			else if(z3Coding.isArrayAcess(memoryunit1)&&z3Coding.isArrayAcess(memoryunit2)){
				//A[exp]*, B[exp]*
				expr base1=z3Coding.getArrayBase(memoryunit1);
				expr base2=z3Coding.getArrayBase(memoryunit2);
				//if(base1.decl().name().str()!=base2.decl().name().str()){
				if(!z3Coding.equal(base1,base2)){
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
				if(!Z3_is_eq_func_decl(c,memoryunit1.decl(),memoryunit2.decl())){
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
				std::cerr<<"EnvironmentAnalysisUtil:mayMemoryUnitIsIn: something is wrong!"<<std::endl;
				std::cerr<<"Error Info::"<<"memoryunit1: "<<memoryunit1<<",memoryunit2: "<<memoryunit2<<std::endl;
				return true;
			}
			return true;
		}


		/**
		 * @brief 
		 * @param Pre: we need Pre to compute primed formulas
		 * @param stmt
		 * @param scopeMemoryUnits : MemoryUnits is unprimed variable
		 * @return primed formulas: primed=unprimed
		 */
	/*	vector<expr> * generatePrimed(vector<expr> * Pre,expr stmt, map<std::string,expr> * scopeMemoryUnits){
			vector<expr> * primedformulas=new vector<expr>();
			if(z3Coding.isAssignment(stmt)){
				stmt=stmt.arg(0);
				expr primedlhs=stmt.arg(0);
				expr lhs=z3Coding.unprime(primedlhs);

				map<std::string,expr> * differents=new map<std::string,expr>();
				for(auto it=scopeMemoryUnits->begin();it!=scopeMemoryUnits->end();it++){
					std::pair<std::string,expr> p=*it;
					if(!mayMemoryUnitIsIn(lhs,p.second)){
						differents->insert(p);
					}
				}
				// generate 
				for(auto it=differents->begin();it!=differents->end();it++){
					std::pair<std::string,expr> p=*it;
					expr memoryUnit=p.second;
					expr primedMemoryUnit=z3Coding.prime(memoryUnit);
					primedformulas->push_back(primedMemoryUnit==memoryUnit);
				}

			}
			else{
				// generate 
				for(auto it=scopeMemoryUnits->begin();it!=scopeMemoryUnits->end();it++){
					std::pair<std::string,expr> p=*it;
					expr memoryUnit=p.second;
					expr primedMemoryUnit=z3Coding.prime(memoryUnit);
					primedformulas->push_back(primedMemoryUnit==memoryUnit);
				}
			}
			return primedformulas;
		}*/
		/**
		 * @brief closure preprocess, call before function: closure(formulas)
		 * @param Pre
		 * @param primedformulas
		 * @param stmt
		 * @return  
		 */
		vector<expr> * closure_preprocess(vector<expr> * Pre,vector<expr> * primedformulas, expr stmt){
			vector<expr> * ret=new vector<expr>();
			vector<expr> * new_Pre=new vector<expr>();
			pushAToB(Pre,new_Pre);
			new_Pre->push_back(stmt);
			//cout<<new_Pre->size()<<"::"<<primedformulas->size()<<std::endl;
			for(expr e:*new_Pre){
				expr new_e=e;
				for(expr p: *primedformulas){
					new_e=z3Coding.substitute(new_e,p.arg(1),primedLift(p.arg(0)));
				}
				if(!z3Coding.hasUnPrimedVariable(new_e)){
					ret->push_back(new_e);
				}
			}
			return ret;
		}


		bool isIn(expr e,vector<expr> * exprs){
			
			/*for(expr ele: *exprs){
				if(formulaEqual(e,ele)){
					return true;
				}
			}
			return false;*/
			for(expr ele: *exprs){
				if(z3Coding.equal(e,ele)){
					return true;
				}
			}
			return false;
			
		}
		
		bool isNe(expr e){
			if(e.is_app()){
				if(/*Z3_is_eq_func_decl(c,e.decl(),z3Coding.NotDecl)*/
				e.decl().hash()==z3Coding.NotDecl.hash()
				){
					if(e.arg(0).is_app()){
						if(/*Z3_is_eq_func_decl(c,e.arg(0).decl(),z3Coding.EqDecl)*/
						/*e.arg(0).decl().name().str()=="="*/
						e.arg(0).decl().hash()==z3Coding.EqDecl.hash()){
							return true;
						}
					}
				}
			}
			return false;
		}
		bool formulaEqual(expr e1,expr e2){
			if(z3Coding.equal(e1,e2)){
				return true;
			}
			e1=z3Coding.eliminateNotInSimpleFormula(e1);
			e2=z3Coding.eliminateNotInSimpleFormula(e2);
			e1=eliminateGtAndGe(e1);
			e2=eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				if(
				/*Z3_is_eq_func_decl(c,e1.decl(),z3Coding.EqDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.EqDecl*/
				/*e1.decl().name().str()=="="&&e2.decl().name().str()=="="*/
				e1.decl().hash()==z3Coding.EqDecl.hash()&&e2.decl().hash()==z3Coding.EqDecl.hash()){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(eq(e1l,e2l)&&eq(e1r,e2r)){
						return true;
					}
					else if(eq(e1l,e2r)&&eq(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}

				else if(isNe(e1) && isNe(e2)){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(eq(e1l,e2l)&&eq(e1r,e2r)){
						return true;
					}
					else if(eq(e1l,e2r)&&eq(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(isNe(e1) && /*e2.decl().name().str()=="distinct"*//*Z3_is_eq_func_decl(c,e2.decl(),z3Coding.DistinctDecl)*/
				e2.decl()==z3Coding.DistinctDecl.hash()
				){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(eq(e1l,e2l)&&eq(e1r,e2r)){
						return true;
					}
					else if(eq(e1l,e2r)&&eq(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(/*Z3_is_eq_func_decl(c,e1.decl(),z3Coding.DistinctDecl)*//*e1.decl().name().str()=="distinct"*/
					e1.decl().hash()==z3Coding.DistinctDecl.hash()&& isNe(e2)){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(eq(e1l,e2l)&&eq(e1r,e2r)){
						return true;
					}
					else if(eq(e1l,e2r)&&eq(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(
				/*Z3_is_eq_func_decl(c,e1.decl(),z3Coding.DistinctDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.DistinctDecl)*/
				/*e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"*/
				e1.decl().hash()==z3Coding.DistinctDecl.hash()&&e2.decl()==z3Coding.DistinctDecl.hash()
				){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(eq(e1l,e2l)&&eq(e1r,e2r)){
						return true;
					}
					else if(eq(e1l,e2r)&&eq(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
			}
			return false;
		}
		bool isIdenticalEquation(expr e){
			e=z3Coding.eliminateNotInSimpleFormula(e);
			e=eliminateGtAndGe(e);
			if(e.is_app()){
				if(e.decl().name().str()=="="){
					expr e1l=e.arg(0);expr e1r=e.arg(1);
					if(eq(e1l,e1r)){
						return true;
					}
					else{
						return false;
					}
				}

				else if(isNe(e)){
					expr e1l=e.arg(0).arg(0);expr e1r=e.arg(0).arg(1);
					if(eq(e1l,e1r)){
						return true;
					}
					else{
						return false;
					}
				}

				else if(e.decl().name().str()=="distinct"){
					expr e1l=e.arg(0);expr e1r=e.arg(1);
					if(eq(e1l,e1r)){
						return true;
					}
					else{
						return false;
					}
				}
			}
			return false;
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
		
		bool isFormula(expr stmt,const clang::Stmt* clangStmt,int count){
			//cout<<"stmt is: "<<stmt<<std::endl;
			if(z3Coding.isAssignment(stmt)){
				stmt=stmt.arg(0);
				expr primedlhs=stmt.arg(0);
				expr lhs=z3Coding.unprime(primedlhs);
				expr rhs=stmt.arg(1);
				auto rhsMemoryunits=z3Coding.getMemoryUnits(rhs);
				for(expr rhsMU:* rhsMemoryunits){
					if(mayMemoryUnitIsIn(lhs,rhsMU,clangStmt,count)){
						return false;
					}
				}
				return true;
			}
			return true;
		}
		
		/**
		 * @brief 
		 * @param formulas
		 * @return 
		 */
		vector<expr> * closure(vector<expr> * formulas,const clang::Stmt *clangStmt){
			/*#ifdef _DEBUG
			cout<<"----------closure begin--------------"<<std::endl;
			cout<<toString(formulas);
			cout<<"------------------------"<<std::endl;
			#endif*/
			
			vector<expr> * canonicalformulas=new vector<expr>();
			pushAToB(formulas,canonicalformulas);
			vector<expr> * queue=new vector<expr>();
			vector<expr> * closureformulas=new vector<expr>();
			pushAToB(canonicalformulas,closureformulas);
			pushAToB(canonicalformulas,queue);
			vector<expr> * dequeue=new vector<expr>();
			int count=0;
			while(!queue->empty()){
				expr formula=queue->front(); queue->erase (queue->begin()); dequeue->push_back(formula);
				if(z3Coding.isSimpleFormula(formula)){
					if(formula.is_app()){
						if(formula.decl().name().str()=="="){
							vector<expr> * freshformulas=closureEq(formula,closureformulas/*,closureformulasMap*/);
							for(expr freshform: *freshformulas){
								queue->push_back(freshform);
								closureformulas->push_back(freshform);
							}
						}
						else if(formula.decl().name().str()==">="){
							vector<expr> * freshformulas=closureGe(formula,closureformulas/*,closureformulasMap*/,clangStmt);
							for(expr freshform: *freshformulas){
								queue->push_back(freshform);
								closureformulas->push_back(freshform);
							}
						}
						else if(formula.decl().name().str()=="<="){
							vector<expr> * freshformulas=closureLe(formula,closureformulas/*,closureformulasMap*/,clangStmt);
							for(expr freshform: *freshformulas){
								queue->push_back(freshform);
								closureformulas->push_back(freshform);
							}
						}
						else if(formula.decl().name().str()==">"){
							vector<expr> * freshformulas=closureGt(formula,closureformulas/*,closureformulasMap*/,clangStmt);
							for(expr freshform: *freshformulas){
								queue->push_back(freshform);
								closureformulas->push_back(freshform);
							}
						}
						else if(formula.decl().name().str()=="<"){
							vector<expr> * freshformulas=closureLt(formula,closureformulas/*,closureformulasMap*/,clangStmt);
							for(expr freshform: *freshformulas){
								queue->push_back(freshform);
								closureformulas->push_back(freshform);
							}
						}
					}
				}
				count++;
			}
			#ifdef _DEBUG
			//cout<<"count::--------"<<count<<std::endl;
			#endif
			
			return closureformulas;
		}




		expr closureEqSubstitute(expr e,expr from,expr to){
			expr Eq=from==to;
			if(e.is_app()&&e.decl().name().str()=="="){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3Coding.equal(eleft,from)){
					return to==eright;
				}
				if(z3Coding.equal(eright,from)){
					return eleft==to;
				}
			}
			else if(e.is_app()&&e.decl().name().str()=="<"){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3Coding.equal(eleft,from)){
					return to<eright;
				}
				if(z3Coding.equal(eright,from)){
					return eleft<to;
				}
			}
			else if(e.is_app()&&e.decl().name().str()=="<="){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3Coding.equal(eleft,from)){
					return to<=eright;
				}
				if(z3Coding.equal(eright,from)){
					return eleft<=to;
				}
			}
			else if(e.is_app()&&e.decl().name().str()==">"){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3Coding.equal(eleft,from)){
					return to>eright;
				}
				if(z3Coding.equal(eright,from)){
					return eleft>to;
				}
			}
			else if(e.is_app()&&e.decl().name().str()==">="){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3Coding.equal(eleft,from)){
					return to>=eright;
				}
				if(z3Coding.equal(eright,from)){
					return eleft>=to;
				}
			}
			return e;
		}




		/**
		 * @brief note: Eq may be in formulas, return new formulas that disjoint  (Eq+formulas) 
		 * 			closureEq(Eq,newformulas)==newformulas, that means closure 
		 * @param Eq
		 * @param formulas
		 * @return new formulas that disjoint  (Eq+formulas), and closureEq(Eq,newformulas)==newformulas
		 */
		vector<expr> * closureEq(expr Eq,vector<expr> * formulas/*,map<unsigned,expr> *formulasMap*/){
			if(!(Eq.is_app()&&Eq.decl().name().str()=="=")) {
				std::cerr<<"EnvironmentAnalysisUtil:closureEq: something is wrong!"<<std::endl;
				std::cerr<<"error info: Eq.decl() is: "<<Eq.decl()<<std::endl;
				std::cerr<<"error info: z3Coding.EqDecl is: "<<z3Coding.EqDecl<<std::endl;
				std::cerr<<"error info: Eq is: "<<Eq<<std::endl;
				return nullptr;
			}
			expr left=Eq.arg(0);
			expr right=Eq.arg(1);
			vector<expr> * oldformulas=new vector<expr>();
			pushAToB(formulas,oldformulas);
			oldformulas->push_back(Eq);
			vector<expr> * newFormulas=new vector<expr>();
			vector<expr> * queue=new vector<expr>();
			pushAToB(formulas,queue);

			while(!queue->empty()){
				expr f=queue->front(); queue->erase(queue->begin()); 
				expr newf=closureEqSubstitute(f,left,right);
				if(!isIn(newf,oldformulas)&&!isIn(newf,queue)&&!isIn(newf,newFormulas)){
					newFormulas->push_back(newf);
					queue->push_back(newf);

				}
				newf=closureEqSubstitute(f,right,left);
				if(!isIn(newf,oldformulas)&&!isIn(newf,queue)&&!isIn(newf,newFormulas)){
					newFormulas->push_back(newf);
					queue->push_back(newf);

				}
			}
			return newFormulas;
		}


		vector<expr> * closureLt(expr Lt,vector<expr> * formulas,const clang::Stmt *clangStmt){
			if(!(Lt.is_app()&&Z3_is_eq_func_decl(c,Lt.decl(),z3Coding.LtDecl))) {
				std::cerr<<"Z3Coding:closureLt: something is wrong!"<<std::endl;
				return nullptr;
			}
			expr left=Lt.arg(0);
			expr right=Lt.arg(1);
			vector<expr> * oldformulas=new vector<expr>();
			pushAToB(formulas,oldformulas);
			oldformulas->push_back(Lt);
			vector<expr> * newFormulas=new vector<expr>();
			vector<expr> * queue=new vector<expr>();
			pushAToB(formulas,queue);

			while(!queue->empty()){
				expr f=queue->front(); queue->erase (queue->begin());
				expr newf=f;

				if(f.is_app()&&Z3_is_eq_func_decl(c,f.decl(),z3Coding.LtDecl)){
					if(z3Coding.equal(f.arg(0),right)){
						newf=left<f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LeDecl)
				/*f.decl().name().str()=="<="*/){
					if(z3Coding.equal(f.arg(0),right)){
						newf=left<f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GtDecl)
				/*f.decl().name().str()==">"*/){
					if(z3Coding.equal(f.arg(1),right)){
						newf=right<f.arg(0);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GeDecl)
				/*f.decl().name().str()==">="*/){
					if(z3Coding.equal(f.arg(1),right)){
						newf=right<f.arg(0);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.EqDecl)
				/*f.decl().name().str()=="="*/){
					if(z3Coding.equal(f.arg(0),right)){
						newf=left<f.arg(1);
					}
					else if(z3Coding.equal(f.arg(1),right)){
						newf=left<f.arg(0);
					}
				}
				if(!z3Coding.equal(newf,f)){
					if(!isIn(newf,oldformulas)&&!isIn(newf,queue)&&!isIn(newf,newFormulas)){
						newFormulas->push_back(newf);
						queue->push_back(newf);
					}
				}

				if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LtDecl)
				/*f.decl().name().str()=="<"*/){
					if(z3Coding.equal(f.arg(1),left)){
						newf=f.arg(0)<right;
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LeDecl)
				/*f.decl().name().str()=="<="*/){

					if(z3Coding.equal(f.arg(1),left)){
						newf=f.arg(0)<right;
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GtDecl)
				/*f.decl().name().str()==">"*/){

					if(z3Coding.equal(f.arg(0),left)){
						newf=right>f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GeDecl)
				/*f.decl().name().str()==">="*/){
					if(z3Coding.equal(f.arg(0),left)){
						newf=right>f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.EqDecl)
				/*f.decl().name().str()=="="*/){

					if(z3Coding.equal(f.arg(0),left)){
						newf=f.arg(1)<right;
					}
					else if(z3Coding.equal(f.arg(1),left)){
						newf=f.arg(0)<right;
					}
				}
				if(!z3Coding.equal(newf,f)){
					if(!isIn(newf,oldformulas)&&!isIn(newf,queue)&&!isIn(newf,newFormulas)){
						newFormulas->push_back(newf);
						queue->push_back(newf);
					}
				}

			}
			return newFormulas;
		}





		vector<expr> * closureLe(expr Le,vector<expr> * formulas,const clang::Stmt *clangStmt){
			if(!(Le.is_app()&&
			Z3_is_eq_func_decl(c,Le.decl(),z3Coding.LeDecl)
			/*Le.decl().name().str()=="<="*/)) {
				std::cerr<<"Z3Coding:closureLe: something is wrong!"<<std::endl;
				return nullptr;
			}
			expr left=Le.arg(0);
			expr right=Le.arg(1);
			vector<expr> * oldformulas=new vector<expr>();
			pushAToB(formulas,oldformulas);
			oldformulas->push_back(Le);
			vector<expr> * newFormulas=new vector<expr>();
			vector<expr> * queue=new vector<expr>();
			pushAToB(formulas,queue);

			while(!queue->empty()){
				expr f=queue->front(); queue->erase (queue->begin()); 
				expr newf=f;
				if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LtDecl)
				/*f.decl().name().str()=="<"*/){
					if(z3Coding.equal(f.arg(0),right)){
						newf=left<f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LeDecl)
				/*f.decl().name().str()=="<="*/){
					if(z3Coding.equal(f.arg(0),right)){
						newf=left<=f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GtDecl)
				/*f.decl().name().str()==">"*/){
					if(z3Coding.equal(f.arg(1),right)){
						newf=right<f.arg(0);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GeDecl)
				/*f.decl().name().str()==">="*/){
					if(z3Coding.equal(f.arg(1),right)){
						newf=right<=f.arg(0);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.EqDecl)
				/*f.decl().name().str()=="="*/){
					if(z3Coding.equal(f.arg(0),right)){
						newf=left<=f.arg(1);
					}
					else if(z3Coding.equal(f.arg(1),right)){
						newf=left<=f.arg(0);
					}
				}

				if(!isIn(newf,oldformulas)&&!isIn(newf,queue)&&!isIn(newf,newFormulas)){
					newFormulas->push_back(newf);
					queue->push_back(newf);

				}

				if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LtDecl)
				/*f.decl().name().str()=="<"*/){
					if(z3Coding.equal(f.arg(1),left)){
						newf=f.arg(0)<right;
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.LeDecl)
				/*f.decl().name().str()=="<="*/){
					if(z3Coding.equal(f.arg(1),left)){
						newf=f.arg(0)<=right;
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GtDecl)
				/*f.decl().name().str()==">"*/){
					if(z3Coding.equal(f.arg(0),left)){
						newf=right>f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.GtDecl)
				/*f.decl().name().str()==">="*/){
					if(z3Coding.equal(f.arg(0),left)){
						newf=right>=f.arg(1);
					}
				}
				else if(f.is_app()&&
				Z3_is_eq_func_decl(c,f.decl(),z3Coding.EqDecl)
				/*f.decl().name().str()=="="*/){
					if(z3Coding.equal(f.arg(0),left)){
						newf=f.arg(1)<=right;
					}
					else if(z3Coding.equal(f.arg(1),left)){
						newf=f.arg(0)<=right;
					}
				}

				if(!isIn(newf,oldformulas)&&!isIn(newf,queue)&&!isIn(newf,newFormulas)){
					newFormulas->push_back(newf);
					queue->push_back(newf);
				}


			}
			return newFormulas;
		}


		vector<expr> * closureGt(expr Gt,vector<expr> * formulas,const clang::Stmt *clangStmt){
			if(!(Gt.is_app()&&
			Z3_is_eq_func_decl(c,Gt.decl(),z3Coding.GtDecl)
			/*Gt.decl().name().str()==">"*/)) {
				std::cerr<<"Z3Coding:closureGt: something is wrong!"<<std::endl;
				return nullptr;
			}
			expr left=Gt.arg(0);
			expr right=Gt.arg(1);
			expr newLt=right<left;
			return closureLt(newLt,formulas,clangStmt);
		}
		vector<expr> * closureGe(expr Ge,vector<expr> * formulas,const clang::Stmt *clangStmt){
			if(!(Ge.is_app()&&
			Z3_is_eq_func_decl(c,Ge.decl(),z3Coding.GeDecl)
			/*Ge.decl().name().str()==">="*/)) {
				std::cerr<<"Z3Coding:closureGe: something is wrong!"<<std::endl;
				return nullptr;
			}
			expr left=Ge.arg(0);
			expr right=Ge.arg(1);
			expr newLe=right<=left;
			return closureLe(newLe,formulas,/*formulasMap,*/clangStmt);
		}
		vector<expr> * primedFiltering(vector<expr> * formulas){
			vector<expr> * primeds=new vector<expr>();
			for(expr f: *formulas){
				if(!z3Coding.hasUnPrimedVariable(f)){
					primeds->push_back(f);
				}
			}
			return primeds;
		}


		vector<expr> * unprimedFiltering(vector<expr> * formulas){
			vector<expr> * unprimeds=new vector<expr>();
			for(expr f: *formulas){
				if(!z3Coding.hasPrimedVariable(f)){
					unprimeds->push_back(f);
				}
			}
			return unprimeds;
		}
		vector<expr> * unprimedDecline(vector<expr> * primedformulas){
			vector<expr> * unprimedDeclineformulas=new vector<expr>();
			for(expr pf:*primedformulas){
				unprimedDeclineformulas->push_back(unprimedDecline(pf));
			}
			return unprimedDeclineformulas;
		}
		expr unprimedDecline(expr primedformula){
			auto cons=z3Coding.getConsts(primedformula);
			expr unprimedformula=primedformula;
			for(expr con:*cons){
				if(z3Coding.isPrimedVariable(con)){
					expr unprimedcon=z3Coding.unprime(con);
					unprimedformula=z3Coding.substitute(unprimedformula,con,unprimedcon);
				}
			}
			return unprimedformula;
		}
		vector<expr> * primedLift(vector<expr> * unprimedformulas){
			vector<expr> * primedLiftformulas=new vector<expr>();
			for(expr upf:*unprimedformulas){
				primedLiftformulas->push_back(primedLift(upf));
			}
			return primedLiftformulas;
		}
		expr primedLift(expr unprimedformula){
			auto cons=z3Coding.getConsts(unprimedformula);
			expr primedformula=unprimedformula;
			for(expr con:*cons){
				if(!z3Coding.isPrimedVariable(con)){
					expr primedcon=z3Coding.prime(con);
					primedformula=z3Coding.substitute(primedformula,con,primedcon);
				}
			}
			return primedformula;
		}


		/**
		 * @brief A-B
		 * @param A
		 * @param B
		 * @return A-B
		 */
		vector<expr>* diff(vector<expr>* A,vector<expr>* B){
			vector<expr>* result=new vector<expr>();
			for(expr e:*A){
				if(!isIn(e,B)){
					result->push_back(e);
				}
			}
			return result;
		}

		vector<expr>* eliminateIdenticalEquation(vector<expr>* formulas){
			vector<expr>* result=new vector<expr>();
			for(expr f:*formulas){
				if(!isIdenticalEquation(f)){
					result->push_back(f);
				}
			}
			//cout<<"after eliminateIdenticalEquation"<<toString(result)<<std::endl;
			return result;
		}
		/*vector<expr>* reduce(vector<expr>* formulas){
			vector<expr>* result=new vector<expr>();
			bool flag;
			for(expr f1:* formulas){
				flag=false;
				for(expr f2: *formulas){
					if(partialOrderRelation(f2,f1)&&!z3Coding.equal(f1,f2)){
						flag=true;
					}
				}
				if(!flag){
					result->push_back(f1);
				}
			}
			cout<<"after reduce"<<toString(result)<<std::endl;
			return result;
		}*/
		
		vector<expr>* reduce(vector<expr>* formulas){
			vector<expr>* result=new vector<expr>();
			vector<expr>* tmp=new vector<expr>();
			z3Coding.pushAToB(formulas,result);
			for(expr filter:*formulas){
				if(!z3Coding.isIn(filter,result)) continue;
				for(expr ele:*result){
					if(z3Coding.equal(filter,ele)||!partialOrderRelation(filter,ele)) {
						tmp->push_back(ele);
					}
				}
				result->clear();
				z3Coding.pushAToB(tmp,result);
				tmp->clear();
			}
			//cout<<"after reduce"<<toString(result)<<std::endl;
			return result;
		}
		
		/**
		 * @brief return true means: f1=>f2
		 * @param f1
		 * @param f2
		 * @return 
		 */
		bool partialOrderRelation(expr f1,expr f2){
			return partialOrderRelation_SimpleFormula_SimpleFormula(f1,f2);
		}
		bool partialOrderRelation_SimpleFormula_SimpleFormula(expr f1,expr f2){
			expr e1=f1;
			expr e2=f2;
			e1=z3Coding.eliminateNotInSimpleFormula(e1);
			e2=z3Coding.eliminateNotInSimpleFormula(e2);
			e1=eliminateGtAndGe(e1);
			e2=eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3Coding.EqDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.EqDecl)
				/*e1.decl().name().str()=="="&&e2.decl().name().str()=="="*/){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}

				}
				else if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.EqDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LtDecl)
				/*e1.decl().name().str()=="="&&e2.decl().name().str()=="<"*/){
					return false;
				}
				else if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.EqDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LeDecl)
				/*e1.decl().name().str()=="="&&e2.decl().name().str()=="<="*/){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(/*e1.decl().name().str()=="="*/Z3_is_eq_func_decl(c,e1.decl(),z3Coding.EqDecl) && isNe(e2)){
					return false;
				}
				else if(/*e1.decl().name().str()=="="*/Z3_is_eq_func_decl(c,e1.decl(),z3Coding.EqDecl) && e2.decl().name().str()=="distinct"){
					return false;
				}
				if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LtDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.EqDecl)
				/*e1.decl().name().str()=="<"&&e2.decl().name().str()=="="*/){
					return false;
				}
				else if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LtDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LtDecl)
				/*e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"*/){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LtDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LeDecl)
				/*e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="*/){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(/*e1.decl().name().str()=="<"*/ Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LtDecl)&& isNe(e2)){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(/*e1.decl().name().str()=="<"*/Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LtDecl)  && e2.decl().name().str()=="distinct"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LeDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.EqDecl)
				/*e1.decl().name().str()=="<="&&e2.decl().name().str()=="="*/){
					return false;

				}
				else if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LeDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LtDecl)
				/*e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"*/){
					return false;
				}
				else if(
				Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LeDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LeDecl)
				/*e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="*/){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(/*e1.decl().name().str()=="<="*/Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LeDecl) && isNe(e2)){
					return false;
				}
				else if(/*e1.decl().name().str()=="<="*/Z3_is_eq_func_decl(c,e1.decl(),z3Coding.LeDecl) && e2.decl().name().str()=="distinct"){
					return false;
				}
				if(isNe(e1)&&/*e2.decl().name().str()=="="*/Z3_is_eq_func_decl(c,e2.decl(),z3Coding.EqDecl)){
					return false;
				}
				else if(isNe(e1)&&/*e2.decl().name().str()=="<"*/Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LtDecl)){
					return false;
				}
				else if(isNe(e1)&&/*e2.decl().name().str()=="<="*/Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LeDecl)){
					return false;
				}
				else if(isNe(e1) && isNe(e2)){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				if(e1.decl().name().str()=="distinct"&&/*e2.decl().name().str()=="="*/Z3_is_eq_func_decl(c,e2.decl(),z3Coding.EqDecl)){
					return false;
				}
				else if(e1.decl().name().str()=="distinct"&&/*e2.decl().name().str()=="<"*/Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LtDecl)){
					return false;
				}
				else if(e1.decl().name().str()=="distinct"&&/*e2.decl().name().str()=="<="*/Z3_is_eq_func_decl(c,e2.decl(),z3Coding.LeDecl)){
					return false;
				}
				else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
				else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return true;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return true;
					}
					else{
						return false;
					}
				}
			}

			return false;

		}
	vector<expr> * normalization(vector<expr> * formulas){
		vector<expr> * result=new vector<expr>();
		for(expr f:*formulas){
			f=z3Coding.eliminateNotInSimpleFormula(f);
			f=eliminateGtAndGe(f);
			result->push_back(f);
		}
		//cout<<"after normalization "<<toString(result)<<std::endl;
		return result;
	}
	
	
	public:
		
		EnvironmentAnalysisUtil(Z3Coding &coding,context &ctx/*,AtomVariablaAnalysis *indexAna*/,PointerAnalysis* pointerAna)
		:z3Coding(coding),c(ctx)/*,indexAnalysis(indexAna)*/,pointerAnalysis(pointerAna){
		}
		
		
		bool mayMemoryUnitIsInFormula(expr memoryUnit,expr formula,const clang::Stmt* clangStmt,int count){
			auto memoryUnits=z3Coding.getMemoryUnits(formula);
			for(expr ele:*memoryUnits){
				if(mayMemoryUnitIsIn(memoryUnit,ele,clangStmt,count)){
					return true;
				}
			}
			return false;
		}

		/**
		 * @brief 
		 * @param Pre: pre-state of stmt
		 * @param stmt  
		 * @param scopeMemoryUnits: the MemoryUnits of stmt can acess( or we can call it still live MemoryUnits)
		 * @return unprimed(pos-state of stmt) 
		 */
		//vector<expr> * Pos(const clang::Stmt* clangStmt,vector<expr> * Pre, expr stmt, map<std::string,expr> * scopeMemoryUnits){
		vector<expr> * Pos(const clang::Stmt* clangStmt,vector<expr> * Pre, expr stmt,int count){
			Pre=eliminateNotInSimpleFormulas(Pre);
			
			vector<expr> * posTmp=new vector<expr>();
			//kill
			if(z3Coding.isAssignment(stmt)){
				expr lhs=unprimedDecline(stmt.arg(0).arg(0));
				for(expr p:*Pre){
					if(!mayMemoryUnitIsInFormula(lhs,p,clangStmt,count)){
						posTmp->push_back(p);
					}
				}
			}
			else{
				z3Coding.pushAToB(Pre,posTmp);
			}
			//gen, check whecher stmt is a formula
			stmt=z3Coding.eliminateNotInSimpleFormula(stmt);
			
			if(isFormula(stmt,clangStmt,count)){
				if(z3Coding.isAssignment(stmt)){
					stmt=stmt.arg(0);
				}
				posTmp->push_back(unprimedDecline(stmt));
			}
			
			
			//vector<expr> *closureformulas=closure(closure_preprocess(Pre,primedformulas,stmt),clangStmt);
			//vector<expr> *result=unprimedDecline(primedFiltering(closureformulas));
			vector<expr> *result=closure(posTmp,clangStmt);
			//cout<<toString(result)<<std::endl;
			vector<expr> * ttt=normalization(reduce(eliminateIdenticalEquation(result)));
			//cout<<toString(ttt)<<std::endl;
			return ttt;
		}
		
		std::string toString(map<std::string,expr> * scopeMemoryUnits){
			std::string ret="";
			for(auto it=scopeMemoryUnits->begin();it!=scopeMemoryUnits->end();it++){
				std::pair<std::string,z3::expr> p=(std::pair<std::string,z3::expr>) *it;
				std::string memoryUnitName=Z3_ast_to_string(c,p.second);
				ret+=memoryUnitName+";";
			}
			return ret;
		}
	expr meet(expr e1,expr e2){
			e1=z3Coding.eliminateNotInSimpleFormula(e1);
			e2=z3Coding.eliminateNotInSimpleFormula(e2);
			e1=eliminateGtAndGe(e1);
			e2=eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l==e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l==e1r;
					}
					else{
						return z3Coding._error;
					}

				}
				else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1r<=e1l;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1r<=e1l;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="=" && isNe(e2)){
					return z3Coding._error;
				}
				else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					return z3Coding._error;
				}
				if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l<=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return z3Coding._error;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<" && isNe(e2)){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l<=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return z3Coding._error;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l<=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return z3Coding._error;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="<=" && isNe(e2)){
					return z3Coding._error;
				}
				else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					return z3Coding._error;
				}
				if(isNe(e1)&&e2.decl().name().str()=="="){
					return z3Coding._error;
				}
				else if(isNe(e1)&&e2.decl().name().str()=="<"){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(isNe(e1)&&e2.decl().name().str()=="<="){
					return z3Coding._error;
				}
				else if(isNe(e1) && isNe(e2)){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
					return z3Coding._error;
				}
				else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					return z3Coding._error;
				}
				else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
				else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					expr e1l=e1.arg(0);expr e1r=e1.arg(1);
					expr e2l=e2.arg(0);expr e2r=e2.arg(1);
					if(z3Coding.equal(e1l,e2l)&&z3Coding.equal(e1r,e2r)){
						return e1l!=e1r;
					}
					else if(z3Coding.equal(e1l,e2r)&&z3Coding.equal(e1r,e2l)){
						return e1l!=e1r;
					}
					else{
						return z3Coding._error;
					}
				}
			}

			return z3Coding._error;
		}
		bool isLtZero(expr e){
			if(!e.is_int()&&!e.is_real()){
				std::cerr<<"EnvironmentAnalysisUtil::isLtZero::"<< e <<" must be int or real type!"<<std::endl;	
				return false;
			}
			else{
				if(e.is_numeral()){
					std::string tmp=Z3_ast_to_string(c,e);
					if(std::stoi(tmp)<0) return true;
				}
				return false;
				
			}
		}
		bool isGtZero(expr e){
			if(!e.is_int()&&!e.is_real()){
				std::cerr<<"EnvironmentAnalysisUtil::isGtZero::"<< e <<" must be int or real type!"<<std::endl;	
				return false;
			}
			else{
				if(e.is_numeral()){
					std::string tmp=Z3_ast_to_string(c,e);
					if(std::stoi(tmp)>0) return true;
				}
				return false;
			}
		}
		expr eliminateGtAndGe(expr e){
			if(e.is_app()){
				if(Z3_is_eq_func_decl(c,e.decl(),z3Coding.GtDecl)
				/*e.decl().name().str()==">"*/){
					return e.arg(1)<e.arg(0);
				}
				if(Z3_is_eq_func_decl(c,e.decl(),z3Coding.GeDecl)
				/*e.decl().name().str()==">="*/){
					return e.arg(1)<=e.arg(0);
				}
			}
			return e;
		}

};


#endif

