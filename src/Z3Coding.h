#ifndef _Z3Coding_H
#define _Z3Coding_H
#include <vector>
#include "z3++.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "clang/AST/Expr.h"
using namespace z3;
using namespace std;
using namespace clang;

enum proved_result {
	proved, unproved,unknown
};
class Sort{
	public:
		z3::sort type; 
		Sort(z3::sort ty):type(ty){
		}

};
class Func_decl{
	public:
		z3::func_decl func; 
		Func_decl(z3::func_decl ff):func(ff){
		}
};
class Z3Coding{
	private:
		context &c;
		//map c++ name to z3 name
		//it is used to process nest scope
		//e.g. int i=1;...{int i=10;...}..
		//we map the second i to new name:i_varNameCount(i)
		map<const ValueDecl*,expr> varDeclToZ3Expr;
		map<std::string,const ValueDecl*> Z3ExprNameToVarDecl;
		//the Decl of var is dofferent, it record the same name of var but different decl 
		map<std::string,int> varNameCount;
		//all varDeclToZ3Expr.second is memoryUnit
		//all A([i])* ocurs in formula is memoryUnit
		map<std::string,expr> memoryUnits;
		map<std::string,const clang::Expr *> memoryUnitsToClangExpr;
		
		bool setRet=false;
		expr _ret;
		void addMemoryUnit(expr memoryUnit){
			std::string memoryUnitName=Z3_ast_to_string(c,memoryUnit);
			if(memoryUnits.count(memoryUnitName)<=0){
				memoryUnits.insert(std::pair<std::string,z3::expr>(memoryUnitName,memoryUnit));
			}
		}
		void addMemoryUnitClangExpr(expr memoryUnit,const clang::Expr * clangExpr){
			std::string memoryUnitName=Z3_ast_to_string(c,memoryUnit);
			if(memoryUnitsToClangExpr.count(memoryUnitName)<=0){
				memoryUnitsToClangExpr.insert(std::pair<std::string,const clang::Expr *>(memoryUnitName,clangExpr));
			}
		}
		unique_ptr<vector<expr>>  toSet(vector<expr> * exprs){
			unique_ptr<vector<expr>> set(new vector<expr>());
			for(expr e:*exprs){
				if(!isIn(e,set.get())){
					set->push_back(e);
				}
			}
			return set;
		}
		bool _isOrFormula(expr f){
			if(is_quantifier(f)){
				//std::cerr<<"I do not consider ForAll Formula!"<<std::endl;	
				return false;
			}
			if(isPhiFormula(f)){
				return false;
			}
			else if(f.is_app()){
				if(Z3_is_eq_func_decl(c,f.decl(),OrDecl)){
					return true;
				}
				for(unsigned i=0;i<f.num_args();i++){
					if(_isOrFormula(f.arg(i))){
						return true;
					}
				}
				return false;
			}
			return false;
		}
		
		unique_ptr<vector<expr>> _DNF(expr f){
			unique_ptr<vector<expr>> ret(new vector<expr>());
			goal g(c);
			g.add(f);
			tactic split_all = repeat(tactic(c, "split-clause") | tactic(c, "skip"));
			apply_result r = split_all(g);
			for (unsigned i = 0; i < r.size(); i++) {
				goal result_goal=r[i];
				ret->push_back(result_goal.as_expr());
			}
			return ret;
		}
	public:
		expr _error;
		expr TRUE;
		expr FALSE;
		expr _phi;
		func_decl _exist;
		func_decl _AS;
		
		func_decl LtDecl;
		func_decl LeDecl;
		func_decl GtDecl;
		func_decl GeDecl;
		func_decl EqDecl;
		func_decl AndDecl;
		func_decl OrDecl;
		func_decl ImplyDecl;
		func_decl NotDecl;
		func_decl ModDecl;
		func_decl MinDecl;
		func_decl DistinctDecl;
		
		func_decl _BAnd;
		func_decl _BOr;
		func_decl _LShift;
		func_decl _RShift;
		func_decl _BXor;
		func_decl _BNot;
		
		//tmp use for upper method,user do not need to care it
		vector<expr>* localDeclVariables_tmp=nullptr;
		
		vector<Func_decl*> * dereferenceFuncs;
		vector<Func_decl*> * typeCastFuncs;
		Z3Coding(context& ctx):c(ctx),_ret(c),_error(c),TRUE(c),FALSE(c),_phi(c),_exist(c),_AS(c),
		LtDecl(c),LeDecl(c),GtDecl(c),GeDecl(c),EqDecl(c),AndDecl(c),OrDecl(c),ImplyDecl(c),NotDecl(c),ModDecl(c),MinDecl(c),
		DistinctDecl(c),_BAnd(c),_BOr(c),_LShift(c),_RShift(c),_BXor(c),_BNot(c)
				       
	{
		_error=c.int_const("_error");
		TRUE=c.bool_val(true);
		FALSE=c.bool_val(false);
		_phi=c.bool_const("_phi");
		_exist=c.function("_exist",c.int_sort(),c.bool_sort(),c.bool_sort());
		_AS=c.function("_AS",c.bool_sort(),c.bool_sort());
		_BAnd=c.function("_band",c.int_sort(),c.int_sort(),c.int_sort());
		_BOr=c.function("_bor",c.int_sort(),c.int_sort(),c.int_sort());
		_LShift=c.function("_lshift",c.int_sort(),c.int_sort(),c.int_sort());
		_RShift=c.function("_rshift",c.int_sort(),c.int_sort(),c.int_sort());
		_BXor=c.function("_xor",c.int_sort(),c.int_sort(),c.int_sort());
		_BNot=c.function("_not",c.int_sort(),c.int_sort());
		
		dereferenceFuncs=new vector<Func_decl*>();
		typeCastFuncs=new vector<Func_decl*>();
		
		z3::sort intarray=c.array_sort(c.int_sort(),c.int_sort());
		expr i=c.int_const("i");
		expr le=i<=i;
		expr lt=i<i;
		expr ge=i>=i;
		expr gt=i>i;
		expr eq=i==i;
		expr notexpr=!gt;
		
		expr andexpr=le&&le;
		expr orexpr=le||le;
		expr implyexpr=implies(le,le);
		expr A=c.constant("A",intarray);
		expr selectexpr=select(A,i);
		expr modexpr=to_expr(c,Z3_mk_mod(c,i,i));
		expr minexpr=i-i;
		expr distinctexpr=i!=i;
		
		LeDecl=le.decl();
		LtDecl=lt.decl();
		GtDecl=gt.decl();
		GeDecl=ge.decl();
		EqDecl=eq.decl();
		AndDecl=andexpr.decl();
		OrDecl=orexpr.decl();
		NotDecl=notexpr.decl();
		ImplyDecl=implyexpr.decl();
		ModDecl=modexpr.decl();
		MinDecl=minexpr.decl();
		DistinctDecl=distinctexpr.decl();
				
	}
		map<std::string,expr> * getMemoryUnits(){
			addMemoryUnit(_phi);
			if(setRet==false){
				return &memoryUnits;
			}
			else{
				addMemoryUnit(_ret);
				return &memoryUnits;	
			}

		}
		std::string toStringMemoryUnits(){
			std::string ret="";
			for(auto it=memoryUnits.begin();it!=memoryUnits.end();it++){
				std::pair<std::string,z3::expr> p=(std::pair<std::string,z3::expr>) *it;
				std::string memoryUnitName=Z3_ast_to_string(c,p.second);
				ret+=memoryUnitName+";";
			}
			return ret;
		}
		/**
		 * @brief cons is const, if old isin cons, return new name ;else return old
		 * @param cons 
		 * @param old
		 * @return 
		 */
		expr rename(vector<expr> *cons,expr old){
			expr tmp=old;
			while(isIn(tmp,cons)){
				std::string oldname=tmp.decl().name().str();
				z3::sort ty=tmp.get_sort();
				std::string newname=oldname+"_new";
				tmp=c.constant(newname.c_str(),ty);
			}
			return tmp;
		}
		bool isIn(expr e,vector<expr> * exprs){
			for(expr ele: *exprs){
				if(equal(e,ele)){
					return true;
				}
			}
			return false;
		}
		/**
		  \brief Simple function that tries to prove the given conjecture using the following steps:
		  1- create a solver
		  2- assert the negation of the conjecture
		  3- checks if the result is unsat.
		  */
		proved_result prove(expr conjecture) {
			solver s(c);
			s.add(!conjecture);
			check_result r=s.check();
			if(r==check_result::unsat){
				return proved_result::proved;
			}
			else if(r==check_result::sat){
				return proved_result::unproved;
			}
			else{
				return proved_result::unknown;
			}
		}
		/**
		 * @brief tries to prove the given assert under the pre_state Pre
		 * you had better not make quantified properties in Pre, which make z3 solver in long time
		 * @param Pre
		 * @param assert
		 */
		proved_result prove(vector<expr> *Pre,expr assert) {
			expr conjecture(c);
			conjecture=!assert;
			for(auto it=Pre->begin();it!=Pre->end();it++){
				expr e=*it;
				conjecture=e&&conjecture;
			}
			solver s(c);
			s.add(conjecture);
			check_result r=s.check();

			if(r==check_result::unsat){
				return proved_result::proved;
			}
			else if(r==check_result::sat){
				return proved_result::unproved;
			}
			else{
				return proved_result::unknown;
			}
		}
		
		check_result satisfy(expr conjecture) {
			solver s(c);
			s.add(conjecture);
			return s.check();
		}
		/**
		 * @brief 
		 * @param Pre
		 * you had better not make quantified properties in Pre, which make z3 solver in long time
		 * @param assert
		 * @return 
		 */
		check_result satisfy(vector<expr> *Pre,expr assert) {
			expr conjecture(c);
			conjecture=assert;
			for(auto it=Pre->begin();it!=Pre->end();it++){
				expr e=*it;
				conjecture=e&&conjecture;
			}
			return satisfy(conjecture);
		}
		
		
		unique_ptr<vector<expr>> filteringNonSimpleFormula(vector<expr>* formulas){
			unique_ptr<vector<expr>> result(new vector<expr>());
			for(expr f:*formulas){
				if(isSimpleFormula(f)){
					result->push_back(f);
				}
			}
			return result;
		}
		expr substitute(expr e, expr from, expr to){
			expr new_e(c);
			Z3_ast _from[] = { from };
			Z3_ast _to[]   = { to };
			new_e = to_expr(c, Z3_substitute(c, e, 1, _from, _to));
			return new_e;
		}
		expr substitute_var(context &c,expr e, expr to){
			expr new_e(c);
			Z3_ast _to[]   = { to };
			new_e = to_expr(c, Z3_substitute_vars(c, e, 1, _to));
			return new_e;
		}

		
		bool power_equal(expr e1,expr e2){
			expr e=e1==e2;
			vector<expr> tmp;
			if(prove(&tmp,e)==proved_result::proved){
				return true;
			}
			return false;
		}
		

		bool allIsBoolSort(vector<expr> * formulas){
			for(expr f: *formulas){
				if(!f.is_bool()){
					return false;
				}
			}
			return true;
		}
		/**
		 * @brief pre: f and all element of formulas is bool sort
		 * @param f
		 * @param formulas
		 * @return 
		 */
		bool formulaIsIn(expr f, vector<expr> * formulas){
			if(isForAllFormula(f)||isExistFormula(f)){
				return isIn(f,formulas);
			}
			for(expr ele: * formulas){
				if(power_equal(f,ele)){
					return true;
				}
			}
			return false;
		}
		
		
		std::string toString(const clang::Stmt* clangStmt){
			LangOptions LO;
			LO.CPlusPlus=1; 
			std::string buffer;
			llvm::raw_string_ostream strout(buffer);
			clangStmt->printPretty(strout, nullptr, PrintingPolicy(LO));
			return strout.str();
		}
		
		std::string toString(const QualType qt){
			LangOptions LO;
			LO.CPlusPlus=1; 
			std::string buffer;
			llvm::raw_string_ostream strout(buffer);
			qt.print(strout,PrintingPolicy(LO));
			return strout.str();
		}


		/**
		 * @brief define the format of our quantifier_formula
		 * 			forall i, extendFormula&&begin<=i&&i<end&&end%step=0 => p(i) 
		 * 			p can be simple formula or quantifier_formula
		 * 			extendFormula may be nil
		 * @param forallFormula
		 * @return 
		 */
		bool check_ForAll_formula(expr forallFormula){
			if(!isForAllFormula(forallFormula)) return false;
			expr body=forallFormula.body();
			if(!(body.is_app()&&Z3_is_eq_func_decl(c,body.decl(),ImplyDecl))) return false;
			expr interval=body.arg(0);
			if(!(interval.is_app()&&Z3_is_eq_func_decl(c,interval.decl(),AndDecl))) return false;
			expr extendIndexAndbeginEndFormula=interval.arg(0);

			if(!(extendIndexAndbeginEndFormula.is_app()&&Z3_is_eq_func_decl(c,extendIndexAndbeginEndFormula.decl(),AndDecl))) return false;
			expr extendIndexAndbeginFormula=extendIndexAndbeginEndFormula.arg(0); 
			expr endFormula=extendIndexAndbeginEndFormula.arg(1);
			if(!(extendIndexAndbeginFormula.is_app()&&(Z3_is_eq_func_decl(c,extendIndexAndbeginFormula.decl(),LtDecl)||
			Z3_is_eq_func_decl(c,extendIndexAndbeginFormula.decl(),LeDecl))&&endFormula.is_app()
			&&(Z3_is_eq_func_decl(c,endFormula.decl(),LtDecl)||Z3_is_eq_func_decl(c,endFormula.decl(),LeDecl)))) return false;
			expr stepformula=interval.arg(1);
			if(!(Z3_is_eq_func_decl(c,stepformula.decl(),EqDecl)&&Z3_is_eq_func_decl(c,stepformula.arg(0).decl(),ModDecl))) return false;
			expr p=body.arg(1);
			if(isForAllFormula(p)){
				return check_ForAll_formula(p);
			}
			else{
				return true;
			}
			

		}
		bool isPhiFormula(expr f){// forall ... phi
			if(f.is_quantifier()){
				if(equal(f.body().arg(1),_phi)){
					return true;
				}
				if(equal(f.body().arg(1), prime(_phi))){
					return true;
				}
			}
			return false;
		}
		expr getPhiStep(expr f){// forall ... phi
			if(isPhiFormula(f)){
				expr body=f.body();
				expr interval=body.arg(0);
				expr stepformula=interval.arg(1);
				expr step=stepformula.arg(0).arg(1);
				return step;
			}
			return _error;
		}
		expr getPhiStepFormula(expr f){// forall ... phi
			if(isPhiFormula(f)){
				expr quantifier=getPhiQuantifier(f);
				expr body=substitute_var(c,f.body(),quantifier);
				expr interval=body.arg(0);
				expr stepformula=interval.arg(1);
				return stepformula;
			}
			return _error;
		}
		expr getPhiBegin(expr f){// forall ... phi
			if(isPhiFormula(f)){
				expr body=f.body();
				expr interval=body.arg(0);
				expr extendIndexAndbeginEndformula=interval.arg(0);
				expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
				if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
					expr beginFormula=extendIndexAndBeginFormula.arg(1);
					expr begin=beginFormula.arg(0);
					return begin;
				}
				else {
					expr begin=extendIndexAndBeginFormula.arg(0);
					return begin;
				}
			}
			return _error;
		}
		expr getPhiBody(expr f){// forall ... phi
			if(isPhiFormula(f)){
				return f.body().arg(1);
			}
			return _error;
		}
		expr getPhiBeginFormula(expr f){// forall ... phi
			if(isPhiFormula(f)){
				expr quantifier=getPhiQuantifier(f);
				expr body=substitute_var(c,f.body(),quantifier);
				expr interval=body.arg(0);
				expr extendIndexAndbeginEndformula=interval.arg(0);
				expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
				if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
					expr beginFormula=extendIndexAndBeginFormula.arg(1);
					return beginFormula;
				}
				else {
					return extendIndexAndBeginFormula;
				}
			}
			return _error;
		}
		expr getPhiEnd(expr f){// forall ... phi
			if(isPhiFormula(f)){
				expr body=f.body();
				expr interval=body.arg(0);
				expr extendIndexAndbeginEndformula=interval.arg(0);
				expr endFormula=extendIndexAndbeginEndformula.arg(1); 
				expr end=endFormula.arg(1);
				return end;
			}
			return _error;
		}
		expr getPhiQuantifier(expr f){// forall ... phi
			if(isPhiFormula(f)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,f,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,f,0));
				return c.constant(sym,s);
			}
			return _error;
		}
		expr getPhiEndFormula(expr f){// forall ... phi
			if(isPhiFormula(f)){
				expr quantifier=getPhiQuantifier(f);
				expr body=substitute_var(c,f.body(),quantifier);
				expr interval=body.arg(0);
				expr extendIndexAndbeginEndformula=interval.arg(0);
				expr endFormula=extendIndexAndbeginEndformula.arg(1); 
				return endFormula;
			}
			return _error;
		}
		expr constructPhiFormula(expr quantifier,expr beginFormula,expr endFormula,expr init,expr step){
			return constructForAllFormula_step(quantifier,beginFormula,endFormula,step,init,_phi);
		}
		expr constructPhiFormula(expr quantifier,expr beginFormula,expr endFormula,expr stepFormula){
			return constructForAllFormula(quantifier,beginFormula,endFormula,stepFormula,_phi);
		}
		expr constructForAllFormula(expr quantifier, expr beginFormula,expr endFormula, expr stepFormula, expr body){
			return forall(quantifier,implies(beginFormula&&endFormula&&stepFormula,body));
		}
		expr constructForAllFormula(expr quantifier, expr extendFormula,expr beginFormula,expr endFormula, expr stepFormula, expr body){

			return forall(quantifier,implies(extendFormula&&beginFormula&&endFormula&&stepFormula,body));
		}
		expr constructForAllFormula_step(expr quantifier, expr extendFormula,expr beginFormula,expr endFormula, expr step,expr indexinit, expr body){		
			return forall(quantifier,implies(extendFormula&&beginFormula&&endFormula&&to_expr(c,Z3_mk_mod(c,quantifier-indexinit,step))==0,body));
		}
		expr constructForAllFormula_step(expr quantifier,expr beginFormula,expr endFormula, expr step,expr indexinit, expr body){	
			expr im=implies(beginFormula&&endFormula&&to_expr(c,Z3_mk_mod(c,quantifier-indexinit,step))==0,body);
			return forall(quantifier,im);
		}



		expr getQuantifierFormulaBody(expr e){
			if(isForAllFormula(e)){
				return getForAllFormulaBodyFormula(e);
			}
			else if(isExistFormula(e)){
				expr mybody=e.arg(1).arg(1);
				return mybody;
			}
			else{
				std::cerr<<"Z3Coding:getQuantifierFormulaBody: can not get getQuantifierFormulaBody from " <<e<<std::endl;
				return _error;
			}
		}
		
		expr getQuantifierFormulaHead(expr e){
			if(isForAllFormula(e)){
				return getForAllFormulaHeadFormula(e);
			}
			else if(isExistFormula(e)){
				expr myhead=e.arg(1).arg(0);
				return myhead;
			}
			else if(isPhiFormula(e)){
				expr quantifier=getPhiQuantifier(e);
				expr body=substitute_var(c,e.body(),quantifier);
				expr myhead=body.arg(0);
				return myhead;
			}
			else{
				std::cerr<<"Z3Coding:getQuantifierFormulagetHead: can not get getQuantifierFormulaHead from " <<e<<std::endl;
				return _error;
			}
		}
		
		
		expr getForAllFormulaStep(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getQuantifierStep: can not get QuantifierForallStep from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr body=forallFormula.body();
			expr interval=body.arg(0);
			expr stepformula=interval.arg(1);
			expr step=stepformula.arg(0).arg(1);
			return step;
		}
		expr getForAllFormulaStepFormula(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaStepFormula: can not get QuantifierFprAllStepFormula from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr quantifier=getQuantifier(forallFormula);
			expr body=substitute_var(c,forallFormula.body(),quantifier);
			expr interval=body.arg(0);
			expr stepformula=interval.arg(1);
			return stepformula;
		}



		expr getForAllFormulaEnd(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaEnd: can not get End from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr body=forallFormula.body();
			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr endFormula=extendIndexAndbeginEndformula.arg(1); 
			expr end=endFormula.arg(1);
			return end;
		}
		expr getForAllFormulaEndFormula(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaEndFormula: can not get EndFormula from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr quantifier=getQuantifier(forallFormula);
			expr body=substitute_var(c,forallFormula.body(),quantifier);
			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr endFormula=extendIndexAndbeginEndformula.arg(1); 
			return endFormula;
		}


		expr getForAllFormulaBodyFormula(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaBodyFormula: can not get QuantifierBody from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr quantifier=getQuantifier(forallFormula);
			expr body=substitute_var(c,forallFormula.body(),quantifier);
			return body.arg(1);
		}
		expr getForAllFormulaHeadFormula(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaHeadFormula: can not get QuantifierHead from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr quantifier=getQuantifier(forallFormula);
			expr body=substitute_var(c,forallFormula.body(),quantifier);
			return body.arg(0);
		}

		expr getForAllFormulaBegin(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaBegin: can not get Begin from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr body=forallFormula.body();
			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
			if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
				expr beginFormula=extendIndexAndBeginFormula.arg(1);
				expr begin=beginFormula.arg(0);
				return begin;
			}
			else {
				expr begin=extendIndexAndBeginFormula.arg(0);
				return begin;
			}
		}
		expr getForAllFormulaBeginFormula(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getForAllFormulaBeginFormula: can not get BeginFormula from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr quantifier=getQuantifier(forallFormula);
			expr body=substitute_var(c,forallFormula.body(),quantifier);

			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
			if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
				expr beginFormula=extendIndexAndBeginFormula.arg(1);
				return beginFormula;
			}
			else {
				return extendIndexAndBeginFormula;
			}
		}

		expr getForAllFormulaExtendFormula(expr forallFormula){
			/*if(!check_ForAll_formula(forallFormula)){
				std::cerr<<"Z3Coding:getQuantifierExtendFormula: can not get ExtendFormula from " <<forallFormula<<std::endl;
				return _error;
			}*/
			expr quantifier=getQuantifier(forallFormula);
			expr body=substitute_var(c,forallFormula.body(),quantifier);

			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
			if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
				expr extendFormula=extendIndexAndBeginFormula.arg(0);
				return extendFormula;
			}
			else {
				//std::cerr<<"Z3Coding:getQuantifierExtendFormula: can not get ExtendFormula from " <<forallFormula<<std::endl;
				return _error;
			}
		}
		/**
		 * @brief check if e is valid
		 * @param e
		 * @return 
		 */
		bool checkError(expr e){
			return equal(_error,e);
		}

		z3::symbol getQuantifier_name(expr forallFormula){
			if(!is_quantifier(forallFormula)){
				std::cerr<<"Z3Coding:getQuantifier_name: can not get quantifier from " <<forallFormula<<std::endl;
				return c.str_symbol("_error");
			}
			if(isForAllFormula(forallFormula)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,forallFormula,0));
				return sym;
			}
			else{
				std::cerr<<"Z3Coding:getQuantifier_name: can not get quantifier from " <<forallFormula<<std::endl;
				return c.str_symbol("_error");
			}
		}

		z3::sort getQuantifier_sort(expr forallFormula){
			if(!is_quantifier(forallFormula)){
				std::cerr<<"Z3Coding:getQuantifier_sort: can not get quantifier from " <<forallFormula<<std::endl;
				return c.int_sort();
			}
			if(isForAllFormula(forallFormula)){
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,forallFormula,0));
				return s;
			}
			else{
				std::cerr<<"Z3Coding:getQuantifier_sort: can not get quantifier from " <<forallFormula<<std::endl;
				return c.int_sort();
			}
		}
		bool is_quantifier(expr e){
			return isExistFormula(e)||isForAllFormula(e);
		}
		expr getQuantifier(expr e){
			if(!is_quantifier(e)){
				std::cerr<<"Z3Coding:getQuantifier: can not get quantifier from " <<e<<std::endl;
				return _error;
			}
			if(isForAllFormula(e)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
				return c.constant(sym,s);
			}
			if(isExistFormula(e)){
				return e.arg(0);
			}
			return _error;
		}
		unique_ptr<vector<expr>> getAllQuantifier(expr forallFormula){
			unique_ptr<vector<expr>> quantifiers(new vector<expr>());
			expr tmp=forallFormula;
			while(is_quantifier(tmp)){
				expr quantifier=getQuantifier(tmp);
				quantifiers->push_back(quantifier);
				tmp=getQuantifierFormulaBody(tmp);
			}
			return quantifiers;
		}
		unsigned getQuantifierCount(expr forallFormula){
			unsigned result=0;
			expr tmp=forallFormula;
			while(is_quantifier(tmp)){
				result++;
				tmp=getQuantifierFormulaBody(tmp);
			}
			return result;
		}
		void maintainMemoryUnits(){
			for(auto it=varDeclToZ3Expr.begin();it!=varDeclToZ3Expr.end();it++){
				std::pair<const ValueDecl *,z3::expr> p=*it;
				std::string memoryUnitName=Z3_ast_to_string(c,p.second);
				if(memoryUnits.count(memoryUnitName)<=0){
					memoryUnits.insert(std::pair<std::string,z3::expr>(memoryUnitName,p.second));
				}
			}
		}
		/**
		 * @brief 
		 * @param e
		 * @return true if e is Array([exp])+
		 */
		 
		bool isArrayAcess(expr e){
			if(e.is_app()){
				return  e.decl().name().str()=="select";
			}
			return false;
		}


		bool isForAllFormula(expr formula){
			if(formula.is_quantifier()&&!isPhiFormula(formula)){
				if(Z3_is_quantifier_forall(c,formula)){
					return true;
				}
			}
			return false;
		}
		bool isExistFormula(expr formula){
			if(formula.is_app()){
				if(Z3_is_eq_func_decl(c,formula.decl(),_exist)){
					return true;
				}
			}
			return false;
		}

	
		bool isSimpleFormula(expr simpleFormula){
			return !isPhiFormula(simpleFormula)&&!isForAllFormula(simpleFormula)&&!isExistFormula(simpleFormula)
			&&!isOrFormula(simpleFormula);
		}
		
		/**
		 * @brief 
		 * @param e must be array acess e[][][]
		 * @return 
		 */
		expr getArrayBase(expr e){
			if(e.is_const()&&e.is_array()){
				return e;
			}
			if(!isArrayAcess(e)&&e.is_array()){
				return e;
			}
			else if(isArrayAcess(e)){
				expr arg0=e.arg(0);
				return getArrayBase(arg0);
			}
			else {
				std::cerr<<"Z3Coding:abstractArrayBase: can not abstract array base from " <<e<<std::endl;
				return _error;
			}
		}
		/**
		 * @brief abstract all MemoryUnits from formula
		 * @param formula
		 * @return 
		 */
//		vector<expr> * getMemoryUnits(expr e){
//			vector<expr> * memoryUnits=new vector<expr>();
//			if(e.is_const()){
//				memoryUnits->push_back(e);
//				return memoryUnits;
//			}
//			else if(isArrayAcess(e)){
//				memoryUnits->push_back(e);
//				vector<expr> * argmemoryUnits=getMemoryUnits(e.arg(0));
//				pushAToB(argmemoryUnits,memoryUnits);
//				argmemoryUnits=getMemoryUnits(e.arg(1));
//				pushAToB(argmemoryUnits,memoryUnits);
//				return memoryUnits;
//			}
//			else if(is_quantifier(e)){
//				std::cerr<<"Z3Coding:abstractMemoryUnits: we can not abstract memoryUnits from quantifier formula"<<std::endl;
//				return memoryUnits;
//			}
//			else if(isPhiFormula(e)){
//				std::cerr<<"Z3Coding:abstractMemoryUnits: we can not abstract memoryUnits from phi formula"<<std::endl;
//				return memoryUnits;
//			}
//			else if(e.is_var()){
//				return memoryUnits;
//			}
//			if(e.is_app()){
//				if(isDer_PointerExpr(e)){
//					memoryUnits->push_back(e);
//				}
//				else if(isDirectMemberExpr(e)){
//					memoryUnits->push_back(e);
//				}
//				else if(isIndirectMemberExpr(e)){
//					memoryUnits->push_back(e);
//				}	
//				for(unsigned i=0;i<e.num_args();i++){
//					vector<expr> * argmemoryUnits=getMemoryUnits(e.arg(i));
//					pushAToB(argmemoryUnits,memoryUnits);
//				}
//			}
//			return memoryUnits;
//		}

		// for A[exp], the memory unit is {A[exp],exp}
		unique_ptr<vector<expr>> getMemoryUnits(expr e){
			unique_ptr<vector<expr>> memoryUnits(new vector<expr>());
			if(e.is_const()){
				if(!isAtExpr(e)&&!e.is_numeral()){
					memoryUnits->push_back(e);
				}
				return memoryUnits;
			}
			else if(isArrayAcess(e)){
				memoryUnits->push_back(e);
				//vector<expr> * argmemoryUnits=getMemoryUnits(e.arg(0));
				//pushAToB(argmemoryUnits,memoryUnits);
				auto argmemoryUnits=getMemoryUnits(e.arg(1));
				pushAToB(argmemoryUnits.get(),memoryUnits.get());
				return memoryUnits;
			}
			else if(is_quantifier(e)){
				std::cerr<<"Z3Coding:abstractMemoryUnits: we can not abstract memoryUnits from quantifier formula"<<std::endl;
				return memoryUnits;
			}
			else if(isPhiFormula(e)){
				std::cerr<<"Z3Coding:abstractMemoryUnits: we can not abstract memoryUnits from phi formula"<<std::endl;
				return memoryUnits;
			}
			else if(e.is_var()){
				return memoryUnits;
			}
			if(e.is_app()){
				if(isDer_PointerExpr(e)){
					memoryUnits->push_back(e);
				}
				else if(isDirectMemberExpr(e)){
					memoryUnits->push_back(e);
				}
				else if(isIndirectMemberExpr(e)){
					memoryUnits->push_back(e);
				}	
				for(unsigned i=0;i<e.num_args();i++){
					auto argmemoryUnits=getMemoryUnits(e.arg(i));
					pushAToB(argmemoryUnits.get(),memoryUnits.get());
				}
			}
			return memoryUnits;
		}
		
		/**
		 * @brief for *e, return e;
		 * @param der_pointerExpr
		 * @return 
		 */
		expr getPointerExpr(expr der_pointerExpr){
			if(!isDer_PointerExpr(der_pointerExpr)){
				return _error;
			}
			return der_pointerExpr.arg(0);
		}
		
		/**
		 * @brief abstract all ArrayAcess from formula
		 * 			index of ArrayAcess may be var
		 * @param e
		 * @return 
		 */
		unique_ptr<vector<expr>> getArrayAcess(expr e){
			unique_ptr<vector<expr>> arrayAcesses(new vector<expr>());
			if(e.is_const()){
				return arrayAcesses;
			}
			else if(isArrayAcess(e)){
				arrayAcesses->push_back(e);
				auto argmemoryUnits=getArrayAcess(e.arg(0));
				pushAToB(argmemoryUnits.get(),arrayAcesses.get());
				argmemoryUnits=getArrayAcess(e.arg(1));
				pushAToB(argmemoryUnits.get(),arrayAcesses.get());
				return arrayAcesses;
			}
			else if(is_quantifier(e)){
				expr quantifier=getQuantifier(e);
				if(isForAllFormula(e)){
					expr body=e.body();
					expr newbody=substitute_var(c,body,quantifier);
					arrayAcesses=getArrayAcess(newbody);
					return arrayAcesses;
				}
				else{
					expr body=e.arg(1);//Quantifier is not arrayAcess
					arrayAcesses=getArrayAcess(body);
					return arrayAcesses;
				}
			}
			else if(isPhiFormula(e)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
				expr quantifier=c.constant(sym,s);
				expr body=substitute_var(c,e.body(),quantifier);
				arrayAcesses=getArrayAcess(body);
				return arrayAcesses;
			}
			else if(e.is_var()){
				return arrayAcesses;
			}
			if(e.is_app()){
				for(unsigned i=0;i<e.num_args();i++){
					auto argmemoryUnits=getArrayAcess(e.arg(i));
					pushAToB(argmemoryUnits.get(),arrayAcesses.get());
				}
			}
			return toSet(arrayAcesses.get());
		}
		/**
		 * @brief such as: A[A[i]]+B[i+j][k]>0, return A[A[i]],B[i+j][k]
		 * @param e
		 * @return 
		 */
		unique_ptr<vector<expr>> getArrayAcessMemoryUnits(expr e){
			unique_ptr<vector<expr>> arrayAcesses(new vector<expr>());
			if(e.is_const()){
				return arrayAcesses;
			}
			else if(isArrayAcess(e)){
				arrayAcesses->push_back(e);
				return arrayAcesses;
			}
			else if(is_quantifier(e)){
				expr quantifier=getQuantifier(e);
				if(isForAllFormula(e)){
					expr body=e.body();
					expr newbody=substitute_var(c,body,quantifier);
					arrayAcesses=getArrayAcessMemoryUnits(newbody);
					return arrayAcesses;
				}
				else{
					expr body=e.arg(1);
					arrayAcesses=getArrayAcessMemoryUnits(body);
					return arrayAcesses;
				}
			}
			else if(isPhiFormula(e)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
				expr quantifier=c.constant(sym,s);
				expr body=substitute_var(c,e.body(),quantifier);
				arrayAcesses=getArrayAcessMemoryUnits(body);
				return arrayAcesses;
			}
			else if(e.is_var()){
				return arrayAcesses;
			}
			if(e.is_app()){
				for(unsigned i=0;i<e.num_args();i++){
					auto argmemoryUnits=getArrayAcessMemoryUnits(e.arg(i));
					pushAToB(argmemoryUnits.get(),arrayAcesses.get());
				}
			}
			return toSet(arrayAcesses.get());
		}
		/**
		 * @brief get all e1.e2, e1->e2 in e
		 * @param e
		 * @return 
		 */
		unique_ptr<vector<expr>> getMemberMemoryUnits(expr e){
			unique_ptr<vector<expr>> membemAcesses(new vector<expr>());
			if(e.is_const()){
				return membemAcesses;
			}
			else if(isMemberExpr(e)){
				membemAcesses->push_back(e);
				return membemAcesses;
			}
			else if(is_quantifier(e)){
				expr quantifier=getQuantifier(e);
				if(isForAllFormula(e)){
					expr body=e.body();
					expr newbody=substitute_var(c,body,quantifier);
					membemAcesses=getMemberMemoryUnits(newbody);
					return membemAcesses;
				}
				else{
					expr body=e.arg(1);
					membemAcesses=getMemberMemoryUnits(body);
					return membemAcesses;
				}
			}
			else if(isPhiFormula(e)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
				expr quantifier=c.constant(sym,s);
				expr body=substitute_var(c,e.body(),quantifier);
				membemAcesses=getMemberMemoryUnits(body);
				return membemAcesses;
			}
			else if(e.is_var()){
				return membemAcesses;
			}
			if(e.is_app()){
				for(unsigned i=0;i<e.num_args();i++){
					auto argmemoryUnits=getMemberMemoryUnits(e.arg(i));
					pushAToB(argmemoryUnits.get(),membemAcesses.get());
				}
			}
			return toSet(membemAcesses.get());
		}
		unique_ptr<vector<expr>> getDerAcessMemoryUnits(expr e){
			unique_ptr<vector<expr>> defAcesses(new vector<expr>());
			if(e.is_const()){
				return defAcesses;
			}
			else if(isDer_PointerExpr(e)){
				defAcesses->push_back(e);
				return defAcesses;
			}
			else if(is_quantifier(e)){
				expr quantifier=getQuantifier(e);
				if(isForAllFormula(e)){
					expr body=e.body();
					expr newbody=substitute_var(c,body,quantifier);
					defAcesses=getDerAcessMemoryUnits(newbody);
					return defAcesses;
				}
				else{
					expr body=e.arg(1);
					defAcesses=getDerAcessMemoryUnits(body);
					return defAcesses;
				}
			}
			else if(isPhiFormula(e)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
				expr quantifier=c.constant(sym,s);
				expr body=substitute_var(c,e.body(),quantifier);
				defAcesses=getDerAcessMemoryUnits(body);
				return defAcesses;
			}
			else if(e.is_var()){
				return defAcesses;
			}
			if(e.is_app()){
				for(unsigned i=0;i<e.num_args();i++){
					auto argmemoryUnits=getDerAcessMemoryUnits(e.arg(i));
					pushAToB(argmemoryUnits.get(),defAcesses.get());
				}
			}
			return toSet(defAcesses.get());
		}
		/**
		 * @brief get consts and Quantifier
		 * @param f
		 * @return 
		 */
		unique_ptr<vector<expr>> getConstsWithQuantifier(expr e){
			unique_ptr<vector<expr>> consts(new vector<expr>());
			map<unsigned,expr> constsMap;
			if(e.is_const()){
				if(e.is_numeral()){
					return consts;
				}
				consts->push_back(e);
				//				std::string eName=Z3_ast_to_string(c,e);
				constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
				return consts;
			}
			else if(is_quantifier(e)){
				expr quantifier=getQuantifier(e);
				if(isForAllFormula(e)){
					expr body=substitute_var(c,e.body(),quantifier);
					consts=getConstsWithQuantifier(body);
				}
				else if(isExistFormula(e)){
					expr body=e.arg(1);
					consts=getConstsWithQuantifier(body);
				}
				return consts;
			}
			else if(isPhiFormula(e)){
				z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
				z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
				expr quantifier=c.constant(sym,s);
				expr body=substitute_var(c,e.body(),quantifier);
				consts=getConstsWithQuantifier(body);
				return consts;
			}
			if(e.is_var()){
				return consts;
			}
			if(e.is_app()){
				if(isDer_PointerExpr(e)){
					if(constsMap.count(e.hash())<=0){
						consts->push_back(e);
						constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
					}
				}
				else if(isDirectMemberExpr(e)){
					if(constsMap.count(e.hash())<=0){
						consts->push_back(e);
						constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
					}
				}
				else if(isIndirectMemberExpr(e)){
					if(constsMap.count(e.hash())<=0){
						consts->push_back(e);
						constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
					}
				}
				for(unsigned i=0;i<e.num_args();i++){
					auto argconsts=getConstsWithQuantifier(e.arg(i));
					for(auto it=argconsts->begin();it!=argconsts->end();it++){
						expr con=*it;
						if(constsMap.count(con.hash())<=0){
							consts->push_back(con);
							constsMap.insert(std::pair<unsigned,expr>(con.hash(),con));
						}
					}
				}
			}
			return consts;
		}

		
		/**
		 * @brief arrayAcess must be array acess
		 * @param arrayAcess
		 * @param k
		 * @return 
		 */
		expr getFormerKDimension(expr arrayAcess,int k){
			if(isArrayAcess(arrayAcess)){
				int d=getArrayAcessDimension(arrayAcess);
				if(d<k){
					std::cerr<<"Z3Coding:getArrayAcessKthIdx: can not get the former"<<k<<" dimension expr of "<<arrayAcess<<std::endl;
					return _error;
				}
				expr formerKDimExpr=arrayAcess;
				for(int i=0;i<d-k;i++){
					formerKDimExpr=arrayAcess.arg(0);
				}
				return formerKDimExpr;
			}
			else{
				std::cerr<<"Z3Coding:abstractFormerKDimension: "<<arrayAcess<<" must be arrayAcess"<<std::endl;
				return _error;
			}
		}

		/**
		 * @brief if e is not array acess,return 0;else return the Dimension of ArrayAcess e
		 * @param e
		 * @return 
		 */
		int getArrayAcessDimension(expr e){
			if(isArrayAcess(e)){
				return 1+getArrayAcessDimension(e.arg(0));	
			}
			else{
				return 0;
			}
		}
		unique_ptr<vector<expr>>  getArrayAcessIdxes(expr arrayAcess){
			unique_ptr<vector<expr>> idxes(new vector<expr>());
			int d=getArrayAcessDimension(arrayAcess);
			expr formerarrayAcess=arrayAcess;
			std::vector<expr>::iterator it;
			for(int i=0;i<d;i++){
				it = idxes->begin();
				idxes->insert(it,formerarrayAcess.arg(1));
				formerarrayAcess=formerarrayAcess.arg(0);
			}
			return idxes;
		}
		expr getArrayAcessKthIdx(expr arrayAcess,int kth){
			auto idxes=getArrayAcessIdxes(arrayAcess);
			if(idxes->size()<((unsigned long)kth)){
				std::cerr<<"Z3Coding:getArrayAcessKthIdx: can not get the "<<kth<<" dimension index of "<<arrayAcess<<std::endl;
				return _error;
			}
			return idxes->at(kth);
		}
		unique_ptr<vector<expr>> getConsts(expr e){
			unique_ptr<vector<expr>> consts(new vector<expr>());
			map<unsigned,expr> constsMap;
			if(e.is_const()){
				if(e.is_numeral()){
					return consts;
				}
				consts->push_back(e);
				constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
				return consts;
			}
			else if(is_quantifier(e)){
				if(isForAllFormula(e)){
					consts=getConsts(e.body());
				}
				else{
					auto tmp=getConsts(e.arg(1));
					expr quantifier= getQuantifier(e);
					for(expr t:*tmp){
						if(!equal(t,quantifier)){
							consts->push_back(t);
						}
					}
				}
				return consts;
			}
			else if(isPhiFormula(e)){
				consts=getConsts(e.body());
				return consts;
			}
			else if(e.is_var()){
				return consts;
			}
			else if(e.is_app()){
				if(isDer_PointerExpr(e)){
					if(constsMap.count(e.hash())<=0){
						consts->push_back(e);
						constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
					}
				}
				else if(isDirectMemberExpr(e)){
					if(constsMap.count(e.hash())<=0){
						consts->push_back(e);
						constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
					}
				}
				else if(isIndirectMemberExpr(e)){
					if(constsMap.count(e.hash())<=0){
						consts->push_back(e);
						constsMap.insert(std::pair<unsigned,expr>(e.hash(),e));
					}
				}
				for(unsigned i=0;i<e.num_args();i++){
					auto argconsts=getConsts(e.arg(i));
					for(auto it=argconsts->begin();it!=argconsts->end();it++){
						expr con=*it;
						if(constsMap.count(con.hash())<=0){
							consts->push_back(con);
							constsMap.insert(std::pair<unsigned,expr>(con.hash(),con));
						}
					}
				}
			}
			return consts;
		}
		unique_ptr<vector<expr>> getAllCons(vector<expr> *exprs){
			unique_ptr<vector<expr>> ret(new vector<expr>());
			for(expr e: *exprs){
				auto tmp=getConsts(e);
				pushAToB(tmp.get(),ret.get());
			}
			return toSet(ret.get());
		}
		
		void pushAToB(vector<expr> *  A,vector<expr> *  B){
			for(auto it=A->begin();it != A->end(); it++){
				expr t=*it;
				B->push_back(t);
			}
		}
		/**
		 * @brief if *e,return true
		 * @param e
		 * @return 
		 */
		bool isDer_PointerExpr(expr e){
			if(e.is_app()){
				std::string op=e.decl().name().str();
				std::string str="def";
				std::size_t found = op.find(str);
				if (found!=std::string::npos){
					return true;
				}
			}
			return false;
		}
		expr der_prime(expr e){
			if(!isDer_PointerExpr(e)){
				cerr<<"Z3Coding::def_prime:: something is wrong!"<<std::endl;
				cerr<<"error info:: e is: "<<e<<std::endl;
				return e;
			}
			std::string op=e.decl().name().str();
			std::string newOp=op+"__prime";
			switch(e.decl().arity()){
				case 1: {
					z3::sort dom=e.decl().domain(0);
					z3::sort ran=e.decl().range();
					func_decl ff=c.function(newOp.c_str(),dom,ran);
					return ff(e.arg(0));
				}
				case 2: {
					z3::sort dom0=e.decl().domain(0);
					z3::sort dom1=e.decl().domain(1);
					z3::sort ran=e.decl().range();
					func_decl ff=c.function(newOp.c_str(),dom0,dom1,ran);
					return ff(e.arg(0),e.arg(1));
				}
				default: {
					cerr<<"def_prime::something is wrong!"<<std::endl;
					return e;
				}
			}
			return e;
		}
		
		expr directAndIndirectAccess_prime(expr e){
			if(!e.is_app()){
				cerr<<"Z3Coding::directAndIndirectAccess_prime:: something is wrong!"<<std::endl;
				cerr<<"error info:: e is: "<<e<<std::endl;
				return e;
			}
			std::string op=e.decl().name().str();
			std::string newOp=op+"__prime";
			switch(e.decl().arity()){
				case 1: {
					z3::sort dom=e.decl().domain(0);
					z3::sort ran=e.decl().range();
					func_decl ff=c.function(newOp.c_str(),dom,ran);
					return ff(e.arg(0));
				}
				default: {
					cerr<<"directAndIndirectAccess_prime::something is wrong!"<<std::endl;
					return e;
				}
			}
			return e;
		}
		/**
		 * @brief 
		 * @param e
		 * @return if e is const: x, return x'; if e is ArrayAcess:(select A exp), return (select A' exp) 
		 */
		expr prime(expr e){
			//cout<<"e is:"<<e<<std::endl;
			if(e.is_numeral()){
				return e;
			}
			if(e.is_const()){
				std::string e_prime_name=e.decl().name().str()+"__prime";
				expr e_prime=c.constant(e_prime_name.c_str(),e.get_sort());
				return substitute(e,e,e_prime);
			}
			else if(isArrayAcess(e)){
				expr arrayBase=getArrayBase(e);
				std::string arrayBase_prime_name=arrayBase.decl().name().str()+"__prime";
				expr arrayBase_prime=c.constant(arrayBase_prime_name.c_str(),arrayBase.get_sort());
				return substitute(e,arrayBase,arrayBase_prime);
			}
			else if(isDer_PointerExpr(e)){
				return der_prime(e);
			}
			else if(isMemberExpr(e)){
				return directAndIndirectAccess_prime(e);
			}
			else {
				std::cerr<<"Z3Coding:prime: We do not consider prime: "<<e<<std::endl;
				return _error;
			}
		}
		/**
		 * @brief 
		 * @param e
		 * @return true if e is x__prime
		 */
		bool isPrimedVariable(expr e){
			if(e.is_const()){ 
				std::size_t found = e.decl().name().str().rfind("__prime");
				if (found!=std::string::npos){
					return true;
				}
			}
			if(isDer_PointerExpr(e)&&isPrimedName(e.decl().name().str())){
				return true;
			}
			if(isMemberExpr(e)&&isPrimedName(e.decl().name().str())){
				return true;
			}
			return false;
		}
		bool isPrimedName(std::string s){
			std::size_t found =s.rfind("__prime");
			if (found!=std::string::npos){
				return true;
			}
			return false;
		}
		bool hasUnPrimedVariable(expr e){
			if(e.is_numeral()){
				return false;
			}
			if(e.is_const()){
				return !isPrimedVariable(e);
			}
			if(is_quantifier(e)){//befor isapp
				if(isForAllFormula(e)){
					return hasUnPrimedVariable(e.body());
				}
				else{
					auto cons=getConsts(e);
					for(expr con:*cons){
						if(hasUnPrimedVariable(con)){
							return true;
						}
					}
					return false;
				}
			}
			if(isPhiFormula(e)){
				return hasUnPrimedVariable(e.body());
			}
			if(e.is_var()){
				return false;
			}
			if(e.is_app()){
				int atrgsNum=e.num_args();
				if(atrgsNum>0){
					for(int i=0;i<atrgsNum;i++){
						expr arg=e.arg(i);
						if(hasUnPrimedVariable(arg)){
							return true;
						}
					}
					return false;
				}
				return false;
			}
			else{
				std::cerr<<"Z3Coding:hasUnPrimedVariable: something is wrong! "<<std::endl;
				return false;
			}
		}
		expr unprime(expr e){
			if(e.is_const()){
				std::size_t found = e.decl().name().str().find("__prime");
				if (found!=std::string::npos){
					int size=e.decl().name().str().size();
					int length=size-7;
					std::string name=e.decl().name().str().substr(0,length);
					return c.constant(name.c_str(),e.get_sort());
				}
				return e;

			}
			else if(isArrayAcess(e)){
				expr ret=e;
				auto cons=getConsts(ret);
				for(expr con: *cons){
					if(isPrimedVariable(con)){
						ret=substitute(ret,con,unprime(con));
					}
				}
				return ret;
			}
			else if(isDer_PointerExpr(e)){
				return der_unprime(e);
			}
			else if(isMemberExpr(e)){
				return directAndIndirectAccess_unprime(e);
			}
			else {
				std::cerr<<"Z3Coding:unprime: We do not consider prime: "<<e<<std::endl;
				return _error;
			}
		}
		bool isMemberExpr(expr e){
			//_direct,_indirect
			return isDirectMemberExpr(e)||isIndirectMemberExpr(e);
		}
		bool isDirectMemberExpr(expr e){
			if(e.is_app()){
				std::size_t found = e.decl().name().str().find("_Direct");
				if (found!=std::string::npos){
					return true;
				}
			}
			return false;
		}
		bool isIndirectMemberExpr(expr e){
			if(e.is_app()){
				std::size_t found = e.decl().name().str().find("_Indirect");
				if (found!=std::string::npos){
					return true;
				}
			}
			return false;
		}
		expr der_unprime(expr e){
			if(!isDer_PointerExpr(e)||!isPrimedName(e.decl().name().str())){
				return e;
			}
			std::string newOp;
			std::size_t found = e.decl().name().str().find("__prime");
			if (found!=std::string::npos){
				int size=e.decl().name().str().size();
				int length=size-7;
				newOp=e.decl().name().str().substr(0,length);
			}
			
			switch(e.decl().arity()){
				case 1: {
					z3::sort dom=e.decl().domain(0);
					z3::sort ran=e.decl().range();
					func_decl ff=c.function(newOp.c_str(),dom,ran);
					return ff(e.arg(0));
				}
				case 2: {
					z3::sort dom0=e.decl().domain(0);
					z3::sort dom1=e.decl().domain(1);
					z3::sort ran=e.decl().range();
					func_decl ff=c.function(newOp.c_str(),dom0,dom1,ran);
					return ff(e.arg(0),e.arg(1));
				}
				default: {
					cerr<<"def_unprime::something is wrong!"<<std::endl;
					return e;
				}
			}
			return e;
		}
		expr directAndIndirectAccess_unprime(expr e){
			if(!e.is_app()){
				return e;
			}
			std::string newOp;
			std::size_t found = e.decl().name().str().find("__prime");
			if (found!=std::string::npos){
				int size=e.decl().name().str().size();
				int length=size-7;
				newOp=e.decl().name().str().substr(0,length);
			}
			
			switch(e.decl().arity()){
				case 1: {
					z3::sort dom=e.decl().domain(0);
					z3::sort ran=e.decl().range();
					func_decl ff=c.function(newOp.c_str(),dom,ran);
					return ff(e.arg(0));
				}
				default: {
					cerr<<"directAndIndirectAccess_unprime::something is wrong!"<<std::endl;
					return e;
				}
			}
			return e;
		}
		
		bool hasPrimedVariable(expr e){
			if(e.is_numeral()){
				return false;
			}
			if(e.is_const()){
				return isPrimedVariable(e);
			}
			if(is_quantifier(e)){
				if(isForAllFormula(e)){
					return hasPrimedVariable(e.body());
				}
				else{
					auto cons=getConsts(e);
					for(expr con:*cons){
						if(hasPrimedVariable(con)){
							return true;
						}
					}
					return false;
				}
			}
			if(isPhiFormula(e)){
				return hasPrimedVariable(e.body());
			}
			if(e.is_var()){
				return false;
			}
			if(e.is_app()){
				std::string op=e.decl().name().str();
				if(isDer_PointerExpr(e)&&isPrimedName(op)){
					return true;
				}
				else if(isMemberExpr(e)&&isPrimedName(op)){
					return true;
				}
				int atrgsNum=e.num_args();
				if(atrgsNum>0){
					for(int i=0;i<atrgsNum;i++){
						expr arg=e.arg(i);
						if(hasPrimedVariable(arg)){
							return true;
						}
					}
					return false;
				}
				return false;
			}
			else{
				std::cerr<<"Z3Coding:hasPrimedVariable: something is wrong! "<<std::endl;
				return false;
			}
		}
		vector<expr> * clangCompoundAssignOperatorToZ3Expr(clang::CompoundAssignOperator * compoundAssignOperator){
			vector<expr>* exprs=new vector<expr>();
			vector<expr>* lhss=clangExprToZ3Expr(compoundAssignOperator->getLHS());
			vector<expr>* rhss=clangExprToZ3Expr(compoundAssignOperator->getRHS());
			if(lhss==nullptr||rhss==nullptr||lhss->size()==0||rhss->size()==0){
				return nullptr;
			}

			expr lhs=lhss->back();lhss->pop_back();
			expr rhs=rhss->back();rhss->pop_back();
			if(!Z3_is_eq_sort(c,lhs.get_sort(),rhs.get_sort())){
				std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr: rhs and lhs type is not same"<<std::endl;
				return nullptr;
			}
			//memoryUnits,just add select memory unit
			if(isArrayAcess(lhs)){
				addMemoryUnit(lhs);
			}
			if(isArrayAcess(rhs)){
				addMemoryUnit(rhs);
			}
			pushAToB(lhss,exprs);
			pushAToB(rhss,exprs);
			expr tmp(c);
			//std::cout<<lhs<<":"<<lhs.get_sort()<<" , "<<rhs<<":"<<rhs.get_sort()<<std::endl;
			switch(compoundAssignOperator->getOpcode()){
				default:	
					std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr: We do not consider processing compoundAssignOperator: "<<compoundAssignOperator->getOpcodeStr().data()<<std::endl;
					return nullptr;
				case BO_MulAssign 	:{
					if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
						std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Mul: rhs and lhs is not int"<<std::endl;
						return nullptr;
					}
					tmp=lhs*rhs;
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
					
				}
				case BO_DivAssign 	:
					if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
						std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Mul: rhs and lhs is not int"<<std::endl;
						return nullptr;
					}
					tmp=lhs/rhs;
					exprs->push_back(_AS(prime(lhs)==tmp));
					exprs->push_back(tmp);
					break;
				case BO_ShlAssign 	:{
					tmp=_LShift(lhs,rhs);
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
					
				}
				case BO_ShrAssign 	:{
					tmp=_RShift(lhs,rhs);
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
					
				}
				case BO_RemAssign		:{
					if(!lhs.is_int()||!rhs.is_int()) return nullptr;
					tmp=to_expr(c,Z3_mk_mod(c,lhs,rhs));
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
					
				}
				case BO_AddAssign 	:{
					if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
						std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Mul: rhs and lhs is not int"<<std::endl;
						return nullptr;
					}
					tmp=lhs+rhs;
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
					
				}
				case BO_SubAssign 	:{
					if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
						std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Mul: rhs and lhs is not int"<<std::endl;
						return nullptr;
					}
					tmp=lhs-rhs;
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
					
				}
				case BO_AndAssign 	:{
					if(!lhs.is_int()||!rhs.is_int()) return nullptr;
					tmp=_BAnd(lhs,rhs);
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
				}
				case BO_OrAssign 	:{
					tmp=_BOr(lhs,rhs);
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
				}
				case BO_XorAssign :{
					if(!lhs.is_int()||!rhs.is_int()) return nullptr;
					tmp=_BXor(lhs,rhs);
					expr primedLhs=prime(lhs);
					if(checkError(primedLhs)) return nullptr;
					exprs->push_back(_AS(primedLhs==tmp));
					exprs->push_back(tmp);
					break;
				}
			}
			return exprs;
		}
		
		
		vector<expr> * clangBinaryOperatorToZ3Expr(clang::BinaryOperator * binaryOperator){
			vector<expr>* exprs=new vector<expr>();
			vector<expr>* lhss=clangExprToZ3Expr(binaryOperator->getLHS());
			vector<expr>* rhss=clangExprToZ3Expr(binaryOperator->getRHS());
			if(lhss==nullptr||rhss==nullptr||lhss->size()==0||rhss->size()==0){
				return nullptr;
			}
			
			expr lhs=lhss->back();lhss->pop_back();
			expr rhs=rhss->back();rhss->pop_back();
			/*if(!Z3_is_eq_sort(c,lhs.get_sort(),rhs.get_sort())){
				std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr: rhs and lhs type is not same"<<std::endl;
				return nullptr;
			}*/
			//memoryUnits,just add select memory unit
			if(isArrayAcess(lhs)){
				addMemoryUnit(lhs);
			}
			if(isArrayAcess(rhs)){
				addMemoryUnit(rhs);
			}
			pushAToB(lhss,exprs);
			pushAToB(rhss,exprs);
			expr tmp(c);
			try{
				//std::cout<<lhs<<":"<<lhs.get_sort()<<" , "<<rhs<<":"<<rhs.get_sort()<<std::endl;
				switch(binaryOperator->getOpcode()){
					default:	
						std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr: We do not consider processing binaryOperator: "<<binaryOperator->getOpcodeStr().data()<<std::endl;
						return nullptr;
					case BO_Mul 	://*
						if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
							std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Mul: rhs and lhs is not int"<<std::endl;
							return nullptr;
						}
						exprs->push_back(lhs*rhs);
						break;
					case BO_Div 	:
						if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
							std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Div: rhs and lhs is not int"<<std::endl;
							return nullptr;
						}
						exprs->push_back(lhs/rhs);
						break;
					case BO_Shl 	://<<
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(_LShift(lhs,rhs));
						break;
					case BO_Shr 	://>>
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(_RShift(lhs,rhs));
						break;
					case BO_Rem	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(to_expr(c,Z3_mk_mod(c,lhs,rhs)));
						break;
					case BO_Add 	:
						{
						
							if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
								//std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Add: rhs and lhs is not int"<<std::endl;
								//return nullptr;
								expr castlhs=lhs;
								expr castrhs=rhs;
								if(!Z3_is_eq_sort(c,lhs.get_sort(),c.int_sort())){
									Func_decl* castFunc=clangGenerateTypecastFunc(lhs.get_sort(),c.int_sort());
									if(castFunc!=nullptr){
										castlhs=castFunc->func(lhs);
									}
									else{
										return nullptr;
									}
								}
								if(!Z3_is_eq_sort(c,rhs.get_sort(),c.int_sort())){
									Func_decl* castFunc=clangGenerateTypecastFunc(rhs.get_sort(),c.int_sort());
									if(castFunc!=nullptr){
										castrhs=castFunc->func(rhs);
									}
									else{
										return nullptr;
									}
								}
								exprs->push_back(castlhs+castrhs);
							}
							else{
								exprs->push_back(lhs+rhs);
							}
						}
						break;
					case BO_Sub 	:
					{
						
						if(!(lhs.is_int()||lhs.is_real())||!(rhs.is_int()||rhs.is_real())){ 
							//std::cerr<<"Z3Coding:clangBinaryOperatorToZ3Expr BO_Sub: rhs and lhs is not int"<<std::endl;
							//return nullptr;
							expr castlhs=lhs;
							expr castrhs=rhs;
							if(!Z3_is_eq_sort(c,lhs.get_sort(),c.int_sort())){
								Func_decl* castFunc=clangGenerateTypecastFunc(lhs.get_sort(),c.int_sort());
								if(castFunc!=nullptr){
									castlhs=castFunc->func(lhs);
								}
								else{
									return nullptr;
								}
							}
							if(!Z3_is_eq_sort(c,rhs.get_sort(),c.int_sort())){
								Func_decl* castFunc=clangGenerateTypecastFunc(rhs.get_sort(),c.int_sort());
								if(castFunc!=nullptr){
									castrhs=castFunc->func(rhs);
								}
								else{
									return nullptr;
								}
							}
							exprs->push_back(castlhs-castrhs);
						}
						else{
							exprs->push_back(lhs-rhs);
						}
						
					}
						break;
					case BO_LT 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(lhs<rhs);
						break;
					case BO_GT 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(lhs>rhs);
						break;
					case BO_LE 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(lhs<=rhs);
						break;
					case BO_GE 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(lhs>=rhs);
						break;
					case BO_EQ 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(lhs==rhs);
						break;
					case BO_NE 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(lhs!=rhs);
						break;
					case BO_And 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(_BAnd(lhs,rhs));
						break;
					case BO_Or 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(_BOr(lhs,rhs));
						break;
					case BO_Xor 	:
						if(!lhs.is_int()||!rhs.is_int()) return nullptr;
						exprs->push_back(_BXor(lhs,rhs));
						break;
					case BO_LAnd 	:
						//exprs->push_back(lhs&&rhs);
						if(!(lhs.is_bool()||lhs.is_int())||!(rhs.is_bool()||rhs.is_int())) return nullptr;
						if(lhs.is_int()){
							lhs=lhs==0;
						}
						if(rhs.is_int()){
							rhs=rhs==0;
						}
						exprs->push_back(lhs&&rhs);
						break;
					case BO_LOr 	:
						if(!(lhs.is_bool()||lhs.is_int())||!(rhs.is_bool()||rhs.is_int())) return nullptr;
						if(lhs.is_int()){
							lhs=lhs==0;
						}
						if(rhs.is_int()){
							rhs=rhs==0;
						}
						exprs->push_back(lhs||rhs);
						break;
					case BO_Comma 	:
						//do nothing
						break;
					case BO_Assign 	:{
						expr primedLhs=prime(lhs);
						if(checkError(primedLhs)) return nullptr;
						//cout<<"primedLhs::"<<primedLhs<<",type::"<<primedLhs.get_sort()<<std::endl;
						//cout<<"rhs::"<<rhs<<",type::"<<rhs.get_sort()<<std::endl;
						if(!Z3_is_eq_sort(c,lhs.get_sort(),rhs.get_sort())){
							Func_decl* castFunc=clangGenerateTypecastFunc(rhs.get_sort(),lhs.get_sort());
							if(castFunc!=nullptr){
								expr castexpr=castFunc->func(rhs);
								exprs->push_back(_AS(primedLhs==castexpr));
								exprs->push_back(rhs);
							}
							else{
								cerr<<"Z3Coding::clangBinaryOperatorToZ3Expr:: something is wrong!"<<std::endl;
								cerr<<"error info::lhs is: "<<lhs<<", type is: "<<lhs.get_sort()<<std::endl;
								cerr<<"error info::rhs is: "<<rhs<<", type is: "<<rhs.get_sort()<<std::endl;
								return nullptr;
							}
						}
						else{
							exprs->push_back(_AS(primedLhs==rhs));
							exprs->push_back(rhs);
						}
						break;
						
					}
				}
			}
			catch(z3::exception e){
					cerr<<"Z3Coding::clangBinaryOperatorToZ3Expr:: something is wrong!"<<std::endl;
					cerr<<"binaryOperator is: "<<toString(binaryOperator)<<std::endl;
					cerr<<"error info::lhs is: "<<lhs<<", type is: "<<lhs.get_sort()<<std::endl;
					cerr<<"error info::rhs is: "<<rhs<<", type is: "<<rhs.get_sort()<<std::endl;
					cerr<<e.msg()<<std::endl;
					return nullptr;
			}
			return exprs;
		}
		bool isPointerType(QualType qt){
			QualType canonicalType=qt.getTypePtr()->getCanonicalTypeInternal();
			const Type * ty=canonicalType.getTypePtr();
			if(ty->isPointerType()) return true;
			return false;
		}
		Sort* clangTypeToZ3Sort(QualType qt){
			QualType canonicalType=qt.getTypePtr()->getCanonicalTypeInternal();
			if(canonicalType.getTypePtr()->isIntegerType()){
				return new Sort(c.int_sort());
			}
			if(canonicalType.getTypePtr()->isCharType()){
				return new Sort(c.int_sort());
			}
			else if(canonicalType.getTypePtr()->isBooleanType()){
				return new Sort(c.bool_sort());
			}
			else if(canonicalType.getTypePtr()->isArrayType()){
				const ArrayType * arraytype=(const ArrayType *)canonicalType.getTypePtr();

				Sort* tmp=clangTypeToZ3Sort(arraytype->getElementType());
				if(tmp!=nullptr){
					z3::sort elementSort=tmp->type;
					return new Sort(c.array_sort(c.int_sort(),elementSort));
				}
				return nullptr;
			}
			else if(canonicalType.getTypePtr()->isPointerType()){
				return new Sort(c.int_sort());
			}
			if(canonicalType.getTypePtr()->isVoidType()){
				return new Sort(c.int_sort());
			}
			if(canonicalType.getTypePtr()->isStructureType()){
				return new Sort(c.int_sort());
			}
			if(canonicalType.getTypePtr()->isFloatingType()){
				return new Sort(c.real_sort());
			}
			
			else {
				std::cerr<<"Z3Coding:clangTypeToZ3Sort: We do not process type : "<<toString(qt)<<std::endl;
				return nullptr;
			}
		}
		
		std::string clangTypeName(QualType qt){
			QualType canonicalType=qt.getTypePtr()->getCanonicalTypeInternal();
			if(canonicalType.getTypePtr()->isIntegerType()){
				return "int";
			}
			if(canonicalType.getTypePtr()->isCharType()){
				return "char";
			}
			else if(canonicalType.getTypePtr()->isBooleanType()){
				return "bool";
			}
			else if(canonicalType.getTypePtr()->isArrayType()){
				const ArrayType * arraytype=(const ArrayType *)canonicalType.getTypePtr();
				std::string eleTypeName=clangTypeName(arraytype->getElementType());
				if(eleTypeName!=""){
					return "array"+eleTypeName;
				}
				return "";
			}
			else if(canonicalType.getTypePtr()->isPointerType()){
				return "pointer";
			}
			else if(canonicalType.getTypePtr()->isStructureType()){
				return "struct";
			}
			else if(canonicalType.getTypePtr()->isFloatingType()){
				return "float";
			}
			else {
				std::cerr<<"Z3Coding:clangTypeName: We do not process type : "<<toString(qt)<<std::endl;
				return "";
			}
		}
		std::string sortTypeName(z3::sort ty){
			if(ty.is_bool()){
				return "bool";
			}
			else if(ty.is_int()){
				return "int";
			}
			else if(ty.is_real()){
				return "float";
			}
			else if(ty.is_array()){
				return "array";
			}
			else {
				cerr<<"Z3Coding::sortTypeName::something is wrong!"<<std::endl;
				cerr<<"error info::ty is: "<<ty<<std::endl;
				return "";
			}
		}
		unsigned getPointerCount(QualType qt){
			unsigned count=0;
			QualType t=qt;
			while(isPointerType(t)){
				const PointerType * pt =(const PointerType *)t.getTypePtr();
				t=pt->getPointeeType();
				count++;
			}
			return count;
		}
		
		/*void clangPointerTypeToZ3DereferenceFuncs(QualType declQT){
			if(isPointerType(declQT)){
				Func_decl* fd=clangPointerTypeToZ3Func(declQT);
				if(!isIn(fd,dereferenceFuncs)){
					dereferenceFuncs->push_back(fd);
				}
			}
		}*/
		
		Func_decl* getDereferenceFunc(QualType declQT){
			if(isPointerType(declQT)){
				Func_decl* fd=clangPointerTypeToZ3Func(declQT);
				if(!isIn(fd,dereferenceFuncs)){
					dereferenceFuncs->push_back(fd);
				}
				return fd;
			}
			return nullptr;
		}
		Func_decl* getAddrOfFunc(QualType declQT){
			QualType canonicalType=declQT.getTypePtr()->getCanonicalTypeInternal();
			Sort* ty=clangTypeToZ3Sort(canonicalType);
			if(ty==nullptr) return nullptr;
			std::string func_name="addrOf_"+clangTypeName(canonicalType);
			return new Func_decl(c.function(func_name.c_str(),ty->type,c.int_sort()));
		}
		bool isAddrOfExpr(expr e){
			if(e.is_app()){
				std::size_t found =e.decl().name().str().find("addrOf_");
				if (found!=std::string::npos){
					return true;
				}
			}
			return false;
		}
		/**
		 * @brief e.e,e->e
		 * e.g. tmp->link->link is link_Indirect(link_Indirect(tmp))
		 * @param memberExpr
		 * @return 
		 */
		Func_decl* getDirectAndIndirectFieldAcessFunc(clang::MemberExpr * memberExpr){
			Expr * base=memberExpr->getBase();
			ValueDecl * memdecl=memberExpr->getMemberDecl();
			LangOptions LO;
			LO.CPlusPlus=1; 
			const  ValueDecl * valueDecl=(const  ValueDecl *)memdecl;
			std::string buffer;
			llvm::raw_string_ostream strout(buffer);
			valueDecl->printName(strout);
			std::string funcName=strout.str();
			Sort* returnType = clangTypeToZ3Sort(valueDecl->getType());
			if(returnType==nullptr) return nullptr;
			/*Sort* parameterType= clangTypeToZ3Sort(base->getType());
			if(parameterType==nullptr) return nullptr;*/
			func_decl result(c);
			if(base->getType().getTypePtr()->isPointerType()){
				funcName+="_Indirect";
				result=c.function(funcName.c_str(),c.int_sort(),returnType->type);
			}
			else{
				funcName+="_Direct";
				result=c.function(funcName.c_str(),c.int_sort(),returnType->type);
			}
			return new Func_decl(result);
		}
		std::string getFieldAcessFuncName(z3::func_decl directAndIndirectFieldAcessFunc){
			
			std::size_t found = directAndIndirectFieldAcessFunc.name().str().find("_Direct");
			if (found!=std::string::npos){
				std::string name=directAndIndirectFieldAcessFunc.name().str().substr(0,found);
				return name;
			}
			return "";
		}
		
		//*p
		Func_decl* clangPointerTypeToZ3Func(QualType qt){
			func_decl result(c);
			QualType canonicalType=qt.getTypePtr()->getCanonicalTypeInternal();
			if(isPointerType(canonicalType)){
				std::string func_name="def_"+clangTypeName(canonicalType);
				const PointerType * pt =(const PointerType *)canonicalType.getTypePtr();
				Sort* pointeeType=clangTypeToZ3Sort(pt->getPointeeType());
				if(pointeeType!=nullptr){
					result=c.function(func_name.c_str(),c.int_sort(),pointeeType->type);
					return new Func_decl(result);
				}
			}
			else {
				std::cerr<<"Z3Coding:clangPointerTypeToZ3Func: some thing is wrong!"<<std::endl;
				return nullptr;
			}
			return nullptr;
		}
		std::string getAsString(DeclarationName &DeclName)
		{
			std::string Result;
			llvm::raw_string_ostream OS(Result);
			OS << DeclName;
			return OS.str();
		}
		
		Func_decl* genZ3Func_decl(clang::CallExpr * callexpr){
			FunctionDecl * calleef=callexpr->getDirectCallee();
			if(calleef==nullptr){
				cerr<<"Z3Coding::clangCallExprToZ3Expr:: something is wrong."<<std::endl;
				cerr<<"error info:: calleef is null"<<std::endl;
				return nullptr;
			}
			DeclarationName DeclName = calleef->getNameInfo().getName();
			std::string FuncName = getAsString(DeclName);
			Sort* returnType= clangTypeToZ3Sort(calleef->getReturnType());
			if(returnType==nullptr){
				return nullptr;
			}
			sort_vector parametersZ3Type(c);
			/*for(unsigned i=0;i<callexpr->getNumArgs();i++){
				Expr * argi=callexpr->getArg(i);
				Sort* type=clangTypeToZ3Sort(argi->getType());
				if(type==nullptr){
					return nullptr;
				}
				
				parametersZ3Type.push_back(type->type);
			}*/
			for(unsigned i=0;i<callexpr->getNumArgs();i++){
				Expr * argi=callexpr->getArg(i);
				vector<expr>* tmp=clangExprToZ3Expr(argi);
				if(tmp==nullptr){
					return nullptr;
				}
				expr argiExpr=tmp->back();tmp->pop_back();
				parametersZ3Type.push_back(argiExpr.get_sort());
			}
			return new Func_decl(c.function(FuncName.c_str(),parametersZ3Type,returnType->type));
		}
		Func_decl* genZ3Func_decl(FunctionDecl * f){
			DeclarationName DeclName = f->getNameInfo().getName();
			std::string FuncName = getAsString(DeclName);
			Sort* returnType= clangTypeToZ3Sort(f->getReturnType());
			if(returnType==nullptr){
				return nullptr;
			}
			sort_vector parametersZ3Type(c);
			for(clang::FunctionDecl::param_iterator it=f->param_begin();it!=f->param_end();it++){
				ParmVarDecl * pd=*it;
				QualType declQT = pd->getType();
				Sort* type=clangTypeToZ3Sort(declQT);
				if(type==nullptr){
					return nullptr;
				}
				parametersZ3Type.push_back(type->type);
			}
			return new Func_decl(c.function(FuncName.c_str(),parametersZ3Type,returnType->type));
		}
		vector<expr>* clangCallExprToZ3Expr(clang::CallExpr * callexpr){
			/*if(toString(callexpr)=="fprintf(stderr, \"\n\")"){
				cout<<"call expr is: "<<toString(callexpr)<<std::endl;
			}*/
			vector<expr>* ret=new vector<expr>();
			expr_vector argExprs(c);
			for(unsigned i=0;i<callexpr->getNumArgs();i++){
				Expr * argi=callexpr->getArg(i);
				vector<expr>* tmp=clangExprToZ3Expr(argi);
				if(tmp==nullptr){
					return nullptr;
				}
				expr argiExpr=tmp->back();tmp->pop_back();
				argExprs.push_back(argiExpr);
				pushAToB(tmp,ret);
			}
			Func_decl* tmp=genZ3Func_decl(callexpr); 	
			if(tmp==nullptr){
				cerr<<"Z3Coding::clangCallExprToZ3Expr:: something is wrong."<<std::endl;
				cerr<<"error info:: tmp is null "<<std::endl;
				cerr<<"error info:: callexpr is: "<<toString(callexpr)<<std::endl;
				return nullptr;
			}
			if(tmp->func.arity()!=argExprs.size()){
				cerr<<"Z3Coding::clangCallExprToZ3Expr:: something is wrong."<<std::endl;
				cerr<<"error info:: tmp->func.arity() is: "<<tmp->func.arity()<<std::endl;
				cerr<<"error info:: argExprs.size() is: "<<argExprs.size()<<std::endl;
				cerr<<"error info:: callexpr is: "<<toString(callexpr)<<std::endl;
				return nullptr;
			}
			/*cout<<toString(callexpr)<<std::endl;
			cout<<"tmp->func is: "<<tmp->func<<std::endl;
			cout<<"---------argExprs----------"<<std::endl;
			debugInfo(argExprs);
			cout<<"---------argExprs----------"<<std::endl;*/
			expr callZ3Expr=tmp->func(argExprs);
			/*cout<<"callExpr is: "<<callZ3Expr<<std::endl;*/
			ret->push_back(callZ3Expr);
			return ret;
			
		}
		
		void debugInfo(expr_vector ev){
			for(int i=0;i<(int)ev.size();i++){
				expr e=ev[i];
				cout<<e<<", type :"<<e.get_sort()<<std::endl;
			}
		}
		vector<expr>*  clangCastExprToZ3Expr(const clang::CastExpr * castExpr){
			vector<expr>* exprs=new vector<expr>();
			vector<expr>* subexprs=clangExprToZ3Expr(castExpr->getSubExpr());
			if(subexprs==nullptr){
				return nullptr;
			}
			expr subexpr=subexprs->back();subexprs->pop_back();
			pushAToB(subexprs,exprs);
			z3::sort fromtype=subexpr.get_sort();
			Sort* totype=clangTypeToZ3Sort(castExpr->getType());
			if(totype==nullptr){
				return nullptr;
			}
			//cout<<"castExpr is: "<<toString(castExpr)<<std::endl;
			//cout<<"cast sub expr is: "<<toString(castExpr->getSubExpr())<<std::endl;
			//cout<<"castExpr type is "<<toString(castExpr->getType())<<std::endl;
			//cout<<"cast sub expr type is "<<toString(castExpr->getSubExpr()->getType())<<std::endl;
			//cout<<"fromtype is:  "<<fromtype<<std::endl;
			//cout<<"to is:  "<<totype->type<<std::endl;
			if(Z3_is_eq_sort(c,fromtype,totype->type)){
				exprs->push_back(subexpr);
				return exprs;
			}
			
			/*std::string functionname="typecast_"+clangTypeName(castExpr->getSubExpr()->getType())+"_"+clangTypeName(castExpr->getType());
			z3::sort dom=fromtype;
			z3::sort ran=totype->type;
			func_decl ff=c.function(functionname.c_str(),dom,ran);
			Func_decl* castFunc=new Func_decl(ff);*/
			
			Func_decl* castFunc=clangGenerateTypecastFunc(fromtype,totype->type);
			if(castFunc==nullptr){
				return nullptr;
			}
			if(!isIn(castFunc,typeCastFuncs)){
				typeCastFuncs->push_back(castFunc);
			}
			//cout<<"castFunc is: "<<castFunc->func<<std::endl;
			//cout<<"arg is: "<<subexpr<<", type is: "<<subexpr.get_sort()<<std::endl;
			exprs->push_back(castFunc->func(subexpr));
			return exprs;
		}
		Func_decl* clangGenerateTypecastFunc(z3::sort fromtype,z3::sort totype){
			if(Z3_is_eq_sort(c,fromtype,totype)){
				return nullptr;
			}
			std::string functionname="typecast_"+sortTypeName(fromtype)+"_"+sortTypeName(totype);
			z3::sort dom=fromtype;
			z3::sort ran=totype;
			func_decl ff=c.function(functionname.c_str(),dom,ran);
			Func_decl* castFunc=new Func_decl(ff);
			if(!isIn(castFunc,typeCastFuncs)){
				typeCastFuncs->push_back(castFunc);
			}
			return castFunc;
		}
		expr clangDeclRefExprToZ3Expr(clang::DeclRefExpr* clangDeclRefExpr){
			const ValueDecl*  valueDecl=clangDeclRefExpr->getDecl();
			LangOptions LO;
			LO.CPlusPlus=1; 
			if (!valueDecl){
				std::string buffer;
				llvm::raw_string_ostream strout(buffer);
				clangDeclRefExpr->printPretty(strout, nullptr, PrintingPolicy(LO));
				std::cerr<<"Z3Coding:clangDeclRefExprToZ3Expr: We do not process clangDeclRefExpr: "<<strout.str()<<std::endl;
				return _error;
			}
			std::string buffer;
			llvm::raw_string_ostream strout(buffer);
			valueDecl->printName(strout);
			std::string varName=strout.str();

			QualType declQT = valueDecl->getType();
			std::string buffer2;
			llvm::raw_string_ostream strout2(buffer2);
			declQT.print(strout2,PrintingPolicy(LO));
			std::string typeName=strout2.str();

			//record the valueDecl
			if(varDeclToZ3Expr.count(valueDecl)>0){
				//alread exist
				//get varDecl's z3 name
				expr z3expr=varDeclToZ3Expr.at(valueDecl);
				addMemoryUnitClangExpr(z3expr,clangDeclRefExpr);
				return z3expr;
			}
			else{
				//not exists
				//set the z3Name
				//if varName exists? getThe count
				if(varNameCount.count(varName)<=0){
					std::string z3Name=varName;
					Sort* tmpTy=clangTypeToZ3Sort(declQT);

					if(tmpTy==nullptr) return _error;

					z3::sort ty=tmpTy->type;

					expr z3expr=c.constant(z3Name.c_str(),ty);
					varDeclToZ3Expr.insert(std::pair<const ValueDecl *,z3::expr>(valueDecl,z3expr));

					Z3ExprNameToVarDecl[z3Name]=valueDecl;
					varNameCount[varName]=1;
					addMemoryUnitClangExpr(z3expr,clangDeclRefExpr);
					return z3expr;
				}
				else{
					int count=varNameCount.at(varName);
					std::string z3Name=varName+std::to_string(count+1);
					Sort* tmpTy=clangTypeToZ3Sort(declQT);

					if(tmpTy==nullptr) return _error;

					z3::sort ty=tmpTy->type;

					expr z3expr=c.constant(z3Name.c_str(),ty);
					varDeclToZ3Expr.insert(std::pair<const ValueDecl *,z3::expr>(valueDecl,z3expr));

					Z3ExprNameToVarDecl[z3Name]=valueDecl;
					varNameCount[varName]=count+1;
					addMemoryUnitClangExpr(z3expr,clangDeclRefExpr);					
					return z3expr;
				}
			}
			return _error;
		}
		vector<expr>* clangArraySubscriptExprToZ3Expr(clang::ArraySubscriptExpr * arraySubscriptExpr){
			vector<expr>* exprs=new vector<expr>();
			const clang::Expr * base=arraySubscriptExpr->getBase();
			const clang::Expr * idx=arraySubscriptExpr->getIdx();			
			vector<expr>* baseZ3Exprs=clangExprToZ3Expr(base);
			vector<expr>* idxZ3Exprs=clangExprToZ3Expr(idx);
			if(baseZ3Exprs==nullptr||idxZ3Exprs==nullptr){
				return nullptr;
			}
			expr baseZ3Expr=baseZ3Exprs->back();baseZ3Exprs->pop_back();
			expr idxZ3Expr=idxZ3Exprs->back();idxZ3Exprs->pop_back();
			pushAToB(baseZ3Exprs,exprs);
			pushAToB(idxZ3Exprs,exprs);
			if(baseZ3Expr.is_array()){
				expr arrayAcess=select(baseZ3Expr,idxZ3Expr);
				exprs->push_back(arrayAcess);
				addMemoryUnitClangExpr(arrayAcess,arraySubscriptExpr);
			}
			else if(baseZ3Expr.is_int()&&isPointerType(base->getType())){
				Func_decl* fd=getDereferenceFunc(base->getType());
				expr dereferenceExpr=fd->func(baseZ3Expr+idxZ3Expr);
				exprs->push_back(dereferenceExpr);
				addMemoryUnitClangExpr(dereferenceExpr,arraySubscriptExpr);
			}
			return exprs;

		}
		expr  clangCharacterLiteralToZ3Expr(clang::CharacterLiteral * charLiteral){
			expr   e=c.int_val(charLiteral->getValue());
			return e;
		}
		expr  clangCXXBoolLiteralExprToZ3Expr(clang::CXXBoolLiteralExpr * boolLiteral){
			if(boolLiteral->getValue()){
				return c.int_val(1);
			}
			else {
				return c.int_val(0);
			}

		}
		expr  clangFloatingLiteralToZ3Expr(clang::FloatingLiteral * floatingLiteral){
			
			double d=floatingLiteral->getValue().convertToDouble();
			expr    e=c.real_val((__uint64)(d));
			return e;
		}
		expr  clangIntegerLiteralToZ3Expr(clang::IntegerLiteral * integerLiteral){
			expr   e=c.int_val((__uint64)(integerLiteral->getValue().getLimitedValue()));
			return e;
		}
		/*expr  clangOffsetOfExprToZ3Expr(clang::OffsetOfExpr * offsetOfExpr){

		  }
		*/
		expr  clangStringLiteralToZ3Expr(clang::StringLiteral * stringLiteral){
			std::string ss=stringLiteral->getString().data();
			ss+="_string";
			return c.int_const(ss.c_str());
		}
		vector<expr>*  clangConditionalOperatorToZ3Expr(clang::ConditionalOperator * conditionalOperator){
			vector<expr>* exprs=new vector<expr>();
			vector<expr>* condExprs=clangExprToZ3Expr(conditionalOperator->getCond());
			if(condExprs==nullptr){
				//std::cerr<<"Z3Coding:clangConditionalOperatorToZ3Expr: condExprs is null"<<std::endl;
				return nullptr;
			}
			vector<expr>* trueExprs=clangExprToZ3Expr(conditionalOperator->getTrueExpr());
			if(trueExprs==nullptr){
				//std::cerr<<"Z3Coding:clangConditionalOperatorToZ3Expr: trueExprs is null"<<std::endl;
				return nullptr;
			}
			vector<expr>* falseExprs=clangExprToZ3Expr(conditionalOperator->getFalseExpr());
			if(falseExprs==nullptr){
				//std::cerr<<"Z3Coding:clangConditionalOperatorToZ3Expr: falseExprs is null"<<std::endl;
				return nullptr;
			}
			expr condExpr=condExprs->back();condExprs->pop_back();
			expr trueExpr=trueExprs->back();trueExprs->pop_back();
			expr falseExpr=falseExprs->back();falseExprs->pop_back();
			pushAToB(condExprs,exprs);
			pushAToB(trueExprs,exprs);
			pushAToB(falseExprs,exprs);
			exprs->push_back(to_expr(c,Z3_mk_ite(c,condExpr,trueExpr,falseExpr)));
			return exprs;
		}
		vector<expr>*  clangUnaryOperatorToZ3Expr(clang::UnaryOperator * unaryOperator){
			vector<expr>* exprs=new vector<expr>();
			vector<expr>* subExprs=clangExprToZ3Expr(unaryOperator->getSubExpr());
			if(subExprs==nullptr){
				//std::cerr<<"Z3Coding:clangUnaryOperatorToZ3Expr: subExprs is null"<<std::endl;
				return nullptr;
			}
			expr subExpr=subExprs->back();subExprs->pop_back();

			//memoryUnits,just add select memory unit
			if(isArrayAcess(subExpr)){
				addMemoryUnit(subExpr);
			}
			pushAToB(subExprs,exprs);
			expr tmp(c);
			//std::cout<<subExpr<<":"<<subExpr.get_sort()<<std::endl;
			switch(unaryOperator->getOpcode()){
				default:	
					std::cerr<<"Z3Coding:clangUnaryOperatorToZ3Expr: We do not consider processing unaryOperator: "<<unaryOperator->getStmtClassName()<<": "<<unaryOperator->getOpcodeStr(unaryOperator->getOpcode()).str()<<std::endl;
					return nullptr;
				case UO_PostInc 	://i++
					if(checkError(subExpr)||!(subExpr.is_int())) return nullptr;
					tmp=subExpr;
					exprs->push_back(_AS(prime(subExpr)==subExpr+1));
					exprs->push_back(tmp);
					break;
				case UO_PostDec 	://i--;
					if(checkError(subExpr)||!(subExpr.is_int())) return nullptr;
					tmp=subExpr;
					exprs->push_back(_AS(prime(subExpr)==subExpr-1));
					exprs->push_back(tmp);
					break;
				case UO_PreInc 	://++i
					if(checkError(subExpr)||!(subExpr.is_int())) return nullptr;
					tmp=prime(subExpr);
					exprs->push_back(_AS(tmp==subExpr+1));
					exprs->push_back(tmp);
					break;
				case UO_PreDec 	://--i;
					if(checkError(subExpr)||!(subExpr.is_int())) return nullptr;
					tmp=prime(subExpr);
					exprs->push_back(_AS(tmp==subExpr-1));
					exprs->push_back(tmp);
					break;
				case UO_Plus 	://+i
					if(!subExpr.is_int()||checkError(subExpr)) return nullptr;
					exprs->push_back(subExpr);
					break;
				case UO_Minus 	://-i;
					if(!subExpr.is_int()||checkError(subExpr)) return nullptr;
					exprs->push_back(-subExpr);
					break;
				case UO_Not 	://~i;
					if(!subExpr.is_int()||checkError(subExpr)) return nullptr;
					exprs->push_back(_BNot(subExpr));
					break;
				case UO_LNot 	://!i
					if(!(subExpr.is_bool()||subExpr.is_int())||checkError(subExpr)) return nullptr;
					if(subExpr.is_int()){
						exprs->push_back(!(subExpr!=0));
					}
					else{
						exprs->push_back(!subExpr);
					}
					break;
				case UO_Deref 	://*
					if(!subExpr.is_int()||checkError(subExpr)||!isPointerType(unaryOperator->getSubExpr()->getType())) return nullptr;
					{
						Func_decl* fd=getDereferenceFunc(unaryOperator->getSubExpr()->getType());
						if(fd==nullptr) return nullptr;
						expr dereferenceExpr=fd->func(subExpr);
						exprs->push_back(dereferenceExpr);
						addMemoryUnitClangExpr(dereferenceExpr,unaryOperator);
					}
					break;
				case UO_AddrOf 	://&
					{
						Func_decl* fd=getAddrOfFunc(unaryOperator->getSubExpr()->getType());
						if(fd==nullptr) return nullptr;
						expr addrOfExpr=fd->func(subExpr);
						exprs->push_back(addrOfExpr);
					}
					break;
			}
			return exprs;
		}

		vector<expr>*  clangExprToZ3Expr(const clang::Expr * clangexpr){
			vector<expr>* exprs=new vector<expr>();
			expr tmp(c);
			switch (clangexpr->getStmtClass()) {
				default:
					std::cerr<<"Z3Coding:clangExprToZ3Expr: We do not consider processing "<<clangexpr->getStmtClassName()<<std::endl;
					std::cerr<<"error info:: clangexpr is: "<<toString(clangexpr)<<std::endl;
					return nullptr;
				case clang::Stmt::BinaryOperatorClass:
					exprs=clangBinaryOperatorToZ3Expr((clang::BinaryOperator*)clangexpr);
					break;
				case clang::Stmt::ArraySubscriptExprClass:
					exprs=clangArraySubscriptExprToZ3Expr((clang::ArraySubscriptExpr*)clangexpr);
					break;
				case clang::Stmt::CharacterLiteralClass:
					tmp=clangCharacterLiteralToZ3Expr((clang::CharacterLiteral*)clangexpr);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				case clang::Stmt::CXXBoolLiteralExprClass:
					tmp=clangCXXBoolLiteralExprToZ3Expr((clang::CXXBoolLiteralExpr*)clangexpr);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				case clang::Stmt::IntegerLiteralClass:
					tmp=clangIntegerLiteralToZ3Expr((clang::IntegerLiteral*)clangexpr);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				case clang::Stmt::FloatingLiteralClass:
					tmp=clangFloatingLiteralToZ3Expr((clang::FloatingLiteral*)clangexpr);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				case clang::Stmt::StringLiteralClass:
					tmp=clangStringLiteralToZ3Expr((clang::StringLiteral*)clangexpr);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				case clang::Stmt::DeclRefExprClass:
					tmp=clangDeclRefExprToZ3Expr((clang::DeclRefExpr*)clangexpr);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				case clang::Stmt::UnaryOperatorClass:
					exprs=clangUnaryOperatorToZ3Expr((clang::UnaryOperator*)clangexpr);
					break;
				case clang::Stmt::ImplicitCastExprClass:
					{
						const CastExpr * castExpr=(const CastExpr *)clangexpr;
						exprs=clangExprToZ3Expr(castExpr->getSubExpr());
						break;
						/*const CastExpr * castExpr=(const CastExpr *)clangexpr;
						exprs=clangCastExprToZ3Expr(castExpr);
						break;*/
					}
				case clang::Stmt::CStyleCastExprClass:
					{
						const CastExpr * castExpr=(const CastExpr *)clangexpr;
						/*exprs=clangExprToZ3Expr(castExpr->getSubExpr());
						break;*/
						exprs=clangCastExprToZ3Expr(castExpr);
						break;
					}
				case clang::Stmt::ParenExprClass:
					{
						const ParenExpr * parenExpr=(const ParenExpr *)clangexpr;
						exprs=clangExprToZ3Expr(parenExpr->getSubExpr());
						break;
					}
				case clang::Stmt::ConditionalOperatorClass:
					{
						ConditionalOperator * conditionalOperator=(ConditionalOperator *)clangexpr;
						exprs=clangConditionalOperatorToZ3Expr(conditionalOperator);
						break;
					}
				case clang::Stmt::CallExprClass:
					{
						CallExpr * callExpr=(CallExpr *)clangexpr;
						exprs=clangCallExprToZ3Expr(callExpr);
						break;
					}
				case clang::Stmt::MemberExprClass:
					{	
						MemberExpr * memberExpr=(MemberExpr *)clangexpr;
						exprs=clangMemberExprToZ3Expr(memberExpr);
						break;
					}
//				case clang::Stmt::UnaryExprOrTypeTraitExprClass:
//					{
//						/***
//						 * UETT_SizeOf 	
//							UETT_AlignOf 	
//							UETT_VecStep 	
//							UETT_OpenMPRequiredSimdAlign 
//						**/
//						UnaryExprOrTypeTraitExpr * unaryExprOrTypeTraitExpr=(UnaryExprOrTypeTraitExpr *)clangexpr;
//						unaryExprOrTypeTraitExpr->
//						exprs=clangMemberExprToZ3Expr(memberExpr);
//						break;
//					}
			}
			return  exprs;
		}
		
		bool isIn(Func_decl *fd,vector<Func_decl*>* vs){
			for(Func_decl* ele:*vs){
				if(Z3_is_eq_func_decl(c,ele->func,fd->func)){
					return true;
				}
			}
			return false;
		}
		
		bool isSingleDeclWithOutInit(const clang::Stmt * clangStmt){
			if(clangStmt->getStmtClass()==clang::Stmt::DeclStmtClass) {
				const clang::DeclStmt * clangDeclStmt=(const clang::DeclStmt *)clangStmt;
				if(!clangDeclStmt->isSingleDecl()){
					return false;
				}
				const Decl* decl=clangDeclStmt->getSingleDecl();
				if(!decl->classofKind(Decl::Kind::Var)){
					return false;
				}
				const  VarDecl * varDecl=(const  VarDecl *)decl;
				if(varDecl->hasInit()){
					return true;
				}
			}
			return false;
		}
		vector<expr>*  clangDeclStmtToZ3Expr(const clang::DeclStmt * clangDeclStmt){
			//cout<<"clangDeclStmt is: "<<toString(clangDeclStmt)<<std::endl;
			vector<expr>* exprs=new vector<expr>();
			if(!clangDeclStmt->isSingleDecl()){
				std::cerr<<"Z3Coding:clangDeclStmtToZ3Expr: We do not consider DeclGroup: "<<toString(clangDeclStmt)<<std::endl;
				return nullptr;
			}
			const Decl* decl=clangDeclStmt->getSingleDecl(); 
			if(!decl->classofKind(Decl::Kind::Var)){
				std::cerr<<"Z3Coding:clangDeclStmtToZ3Expr: We do not consider the DeclKind: "<<decl->getDeclKindName()<<std::endl;
				return nullptr;
			}
			LangOptions LO;
			LO.CPlusPlus=1; 
			const  VarDecl * varDecl=(const  VarDecl *)decl;
			const  ValueDecl * valueDecl=(const  ValueDecl *)decl;
			std::string buffer;
			llvm::raw_string_ostream strout(buffer);
			valueDecl->printName(strout);
			std::string varName=strout.str();
			//std::cout<<"varName: "<<varName;
			QualType declQT = valueDecl->getType();
			std::string buffer2;
			llvm::raw_string_ostream strout2(buffer2);
			declQT.print(strout2,PrintingPolicy(LO));
			std::string typeName=strout2.str();
			//std::cout<<", typeName: "<<typeName<<std::endl;

			expr varZ3Expr(c);
			
			//record the valueDecl
			if(varDeclToZ3Expr.count(valueDecl)>0){
				//alread exist
				//get varDecl's z3 name
				varZ3Expr=varDeclToZ3Expr.at(valueDecl);
				
			}
			else{
				//not exists
				//set the z3Name
				//if varName exists? get the count
				if(varNameCount.count(varName)<=0){
					std::string z3Name=varName;
					Sort* tmpTy=clangTypeToZ3Sort(declQT);
					if(tmpTy==nullptr) return nullptr;
					z3::sort ty=tmpTy->type;
					varZ3Expr=c.constant(z3Name.c_str(),ty);
					varDeclToZ3Expr.insert(std::pair<const ValueDecl *,z3::expr>(valueDecl,varZ3Expr));
					
					//std::cout<<varZ3Expr<<":"<<varZ3Expr.get_sort()<<std::endl;
					Z3ExprNameToVarDecl[z3Name]=valueDecl;
					varNameCount[varName]=1;
					//
					
				}
				else{
					int count=varNameCount.at(varName);
					std::string z3Name=varName+std::to_string(count+1);;
					Sort* tmpTy=clangTypeToZ3Sort(declQT);
					if(tmpTy==nullptr) return nullptr;
					z3::sort ty=tmpTy->type;
					varZ3Expr=c.constant(z3Name.c_str(),ty);
					varDeclToZ3Expr.insert(std::pair<const ValueDecl *,z3::expr>(valueDecl,varZ3Expr));
					
					Z3ExprNameToVarDecl[z3Name]=valueDecl;
					varNameCount[varName]=count+1;
				}
				
			}
			if(varDecl->hasInit()){
				vector<expr> * initZ3Exprs=clangExprToZ3Expr(varDecl->getInit()); 
				if(initZ3Exprs==nullptr) return nullptr;
				expr initZ3Expr=initZ3Exprs->back();initZ3Exprs->pop_back();
				pushAToB(initZ3Exprs,exprs);
				//std::cout<<varZ3Expr<<":"<<varZ3Expr.get_sort()<<"=="<<initZ3Expr<<":"<<initZ3Expr.get_sort()<<std::endl;
				if(!Z3_is_eq_sort(c,varZ3Expr.get_sort(),initZ3Expr.get_sort())) return nullptr;
				exprs->push_back(_AS(prime(varZ3Expr)==initZ3Expr));
			}
			if(localDeclVariables_tmp!=nullptr){
				localDeclVariables_tmp->push_back(varZ3Expr);
			}
			return exprs;
		}
		vector<expr> * clangMemberExprToZ3Expr(clang::MemberExpr * memberExpr){
			vector<expr> * result=new vector<expr>();
			Expr * base=memberExpr->getBase();
			vector<expr> * baseExprs=clangExprToZ3Expr(base);
			if(baseExprs==nullptr) return nullptr;
			expr baseExpr=baseExprs->back();baseExprs->pop_back();
			pushAToB(baseExprs,result);
		 	Func_decl* f=getDirectAndIndirectFieldAcessFunc(memberExpr);
			if(f==nullptr) return nullptr;
			expr memberZ3Expr=f->func(baseExpr);
			addMemoryUnitClangExpr(memberZ3Expr,memberExpr);
			result->push_back(memberZ3Expr);
			return result;
		}
		vector<expr> * clangStmtToZ3Expr(const clang::Stmt* stmt){
			//cout<<"stmt is: "<<toString(stmt)<<std::endl;
			vector<expr> * exprs=new vector<expr>();
			//cout<<"stmt is: "<<toString(stmt)<<std::endl;
			/*if(toString(stmt)=="split = outFileName"){
				cout<<"stmt is: "<<toString(stmt)<<std::endl;
			}*/
			switch (stmt->getStmtClass()) {
				case clang::Stmt::DeclStmtClass:
					exprs=clangDeclStmtToZ3Expr((const clang::DeclStmt*)stmt);
					break;
				case clang::Stmt::BinaryOperatorClass:
					exprs=clangBinaryOperatorToZ3Expr((clang::BinaryOperator*)stmt);
					break;
				case clang::Stmt::UnaryOperatorClass:
					exprs=clangUnaryOperatorToZ3Expr((clang::UnaryOperator*)stmt);
					break;
				case clang::Stmt::ImplicitCastExprClass:
					{
						const CastExpr * castExpr=(const CastExpr *)stmt;
						exprs=clangExprToZ3Expr(castExpr->getSubExpr());
						break;
					}
				case clang::Stmt::ReturnStmtClass:
					{
						const ReturnStmt * returnStmt=(const ReturnStmt *)stmt;
						const Expr* retValue=returnStmt->getRetValue();
						if(retValue!=nullptr){
							exprs=clangExprToZ3Expr(retValue);
							if(exprs==nullptr) return nullptr;
							expr returnExpr=exprs->back();exprs->pop_back();
							exprs->push_back(getRet(returnExpr)==returnExpr);
						}
						break;
					}
				case clang::Stmt::CompoundAssignOperatorClass:
					exprs=clangCompoundAssignOperatorToZ3Expr((clang::CompoundAssignOperator*)stmt);
					break;
				case clang::Stmt::IntegerLiteralClass:
				{
					expr tmp=clangIntegerLiteralToZ3Expr((clang::IntegerLiteral*)stmt);
					if(checkError(tmp)) return nullptr;
					exprs->push_back(tmp);
					break;
				}
				case clang::Stmt::ConditionalOperatorClass:
				{
					ConditionalOperator * conditionalOperatorExpr=(ConditionalOperator *)stmt;
					exprs=clangConditionalOperatorToZ3Expr(conditionalOperatorExpr);
					break;
				}
				case clang::Stmt::CallExprClass:
				{
					CallExpr * callExpr=(CallExpr *)stmt;
					exprs=clangCallExprToZ3Expr(callExpr);
					break;
				}
				case clang::Stmt::CStyleCastExprClass:
				{
					CStyleCastExpr * cstyleCastExpr=(CStyleCastExpr *)stmt;
					exprs=clangExprToZ3Expr(cstyleCastExpr->getSubExpr());
					break;
					/*in stmt, cast type is little ,so we omit it*/
					/*const CStyleCastExpr * castExpr=(const CStyleCastExpr *)stmt;
					exprs=clangCStyleCastExprToZ3Expr(castExpr);
					break;*/
				}
				case clang::Stmt::MemberExprClass:
				{	
					MemberExpr * memberExpr=(MemberExpr *)stmt;
					exprs=clangMemberExprToZ3Expr(memberExpr);
					break;
				}
				default:{
					std::cerr<<"Z3Coding:clangStmtToZ3Expr: We do not consider processing "<<stmt->getStmtClassName()<<std::endl;	
				}
			}
			//cout<<"exprs is: "<<toString(exprs)<<std::endl;
			return exprs;
		}
		std::string toString(vector<z3::expr>* exprs){
			if(exprs==nullptr) return "null";
			std::string ret="";
			if(exprs==nullptr) return "";
			for(auto it=exprs->begin();it!=exprs->end();it++){
				z3::expr e=(z3::expr) *it;
				//std::string eName=Z3_ast_to_string(e.ctx(),e);
				std::string eName=toString(e);
				ret+=eName+";\n ";
			}
			return ret;
		}
		vector<expr>* boolSortFiltering(vector<expr>* exprs){
			vector<expr> * formulas=new vector<expr>();
			for(expr e: *exprs){
				if(e.is_bool()){
					formulas->push_back(e);
				}
			}
			return formulas;
		}
		bool equal(expr e1,expr e2){
			if(eq(e1,e2)){
				return true;
			}
			return false;
		}
		bool formulaEqual(expr e1,expr e2){
			if(equal(e1,e2)){
				return true;
			}
			if(isSimpleFormula(e1)&&isSimpleFormula(e2)){
				//userdefined
			}
			if(isForAllFormula(e1)&&isForAllFormula(e2)){
				expr forallBody1=getQuantifierFormulaBody(e1);
				expr forallBody2=getQuantifierFormulaBody(e2);

				if(!formulaEqual(forallBody1,forallBody2)){
					return false;
				}

				expr quantifier1=getQuantifier(e1);
				expr step1=getForAllFormulaStep(e1);
				expr step1Formula=getForAllFormulaStepFormula(e1);
				expr quantifierBegin1=getForAllFormulaBegin(e1);
				expr quantifierEnd1=getForAllFormulaEnd(e1);
				expr quantifierBeginFormula1=getForAllFormulaBeginFormula(e1);
				expr quantifierEndFormula1=getForAllFormulaEndFormula(e1);
				expr quantifierExtendFormula1=getForAllFormulaExtendFormula(e1);

				expr quantifier2=getQuantifier(e2);
				expr step2=getForAllFormulaStep(e2);
				expr quantifierBegin2=getForAllFormulaBegin(e2);
				expr quantifierEnd2=getForAllFormulaEnd(e2);
				expr quantifierBeginFormula2=getForAllFormulaBeginFormula(e2);
				expr quantifierEndFormula2=getForAllFormulaEndFormula(e2);
				expr quantifierExtendFormula2=getForAllFormulaExtendFormula(e2);

				if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
						||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
					return false;
				}

				if(!checkError(quantifierExtendFormula1)||!checkError(quantifierExtendFormula2)){
					expr quantifierExtendFormula2To1=substitute(quantifierExtendFormula2,quantifier2,quantifier1);
					if(!equal(quantifierExtendFormula2To1,quantifierExtendFormula1)){
						return false;
					}
				}
				if(equal(step1,step2)
						&&Z3_is_eq_func_decl(c,quantifierBegin1.decl(),quantifierBegin2.decl())&& equal(quantifierBegin1,quantifierBegin2)
						&&Z3_is_eq_func_decl(c,quantifierEnd1.decl(),quantifierEnd2.decl())&& equal(quantifierEnd1,quantifierEnd2)){
					return true;
				}

				else{
					return false;
				}
			}
			if(isExistFormula(e1)&&isExistFormula(e2)){
				expr existBody1=getQuantifierFormulaBody(e1);
				expr existBody2=getQuantifierFormulaBody(e2);
				if(!formulaEqual(existBody1,existBody2)){
					return false;
				}


				expr quantifier1=getQuantifier(e1);
				expr step1=getExistFormulaStep(e1);
				expr step1Formula=getExistFormulaStepFormula(e1);
				expr quantifierBegin1=getExistFormulaBegin(e1);
				expr quantifierEnd1=getExistFormulaEnd(e1);
				expr quantifierBeginFormula1=getExistFormulaBeginFormula(e1);
				expr quantifierEndFormula1=getExistFormulaEndFormula(e1);
				expr quantifierExtendFormula1=getExistFormulaExtendFormula(e1);

				expr quantifier2=getQuantifier(e2);
				expr step2=getExistFormulaStep(e2);
				expr step2Formula=getExistFormulaStepFormula(e2);
				expr quantifierBegin2=getExistFormulaBegin(e2);
				expr quantifierEnd2=getExistFormulaEnd(e2);
				expr quantifierBeginFormula2=getExistFormulaBeginFormula(e2);
				expr quantifierEndFormula2=getExistFormulaEndFormula(e2);
				expr quantifierExtendFormula2=getExistFormulaExtendFormula(e2);

				if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
						||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
					return false;
				}


				if(!checkError(quantifierExtendFormula1)||!checkError(quantifierExtendFormula2)){
					expr quantifierExtendFormula2To1=substitute(quantifierExtendFormula2,quantifier2,quantifier1);
					if(!equal(quantifierExtendFormula2To1,quantifierExtendFormula1)){
						return false;
					}
				}
				if(!equal(step1,step2)){
					return false;
				}
				if(quantifierBegin1.decl().name().str()!=quantifierBegin2.decl().name().str()||!equal(quantifierBegin1,quantifierBegin2)
						||quantifierEnd1.decl().name().str()!=quantifierEnd2.decl().name().str()||!equal(quantifierEnd1,quantifierEnd2)){
					return false;
				}
				return true;
			}
			return false;
		}
		/**
		 * @brief check if every element of disjunctionForms is valid. return all valid elements  
		 * @param Pre
		 * @param disjunctionForms: every element is  conjunction Form
		 * @return 
		 */
		vector<expr>* reduction(vector<expr> *Pre,vector<expr> *disjunctionForms){
			vector<expr>* ret=new vector<expr>();
			for(expr conjunction:*disjunctionForms){
				if(satisfy(Pre,conjunction)!=check_result::unsat){
					ret->push_back(conjunction);
				}
			}
			return ret;
		}

		unique_ptr<vector<expr>> DNF(expr f){
			f=CNF(f);
			return _DNF(f);
		}
		/**
		 * @brief 获取f中or公式的个数
		 * @param f
		 * @return 
		 */
		int getOrCount(expr f){
			return splitOrFormulas(f)->size();
		}
		expr CNF(expr f){
			vector<expr>  tmp;
			goal g(c);
			g.add(f);
			tactic split_all = repeat(tactic(c, "tseitin-cnf") | tactic(c, "skip"));
			apply_result r = split_all(g);
			for (unsigned i = 0; i < r.size(); i++) {
				goal result_goal=r[i];
				tmp.push_back(result_goal.as_expr());
			}
			expr ret=tmp.at(0);
			for (unsigned i = 1; i < tmp.size(); i++) {
				ret=ret&&tmp.at(i);
			}
			return ret;
		}

		unique_ptr<vector<expr>>  filteringOrFormula(vector<expr>* formulas){
			unique_ptr<vector<expr>> ret(new vector<expr>());
			for(expr f:* formulas){
				if(!isOrFormula(f)){
					ret->push_back(f);
				}
			}
			return ret;
		}
		/*bool isOrFormula(expr f){
			return _isOrFormula(f)||_isOrFormula(CNF(f));
		}*/
		bool isOrFormula(expr f){
			return (int(splitOrFormulas(f)->size()))>1;
		}
		expr getRet(expr retValue){
			_ret=c.constant("_ret",retValue.get_sort());
			setRet=true;
			return _ret;
		}
		bool isContainRet(expr f){
			if(setRet==true){
				auto cons=getConsts(f);
				if(isIn(_ret,cons.get())){
					return true ;
				}
			}
			return false;
		}
		expr unprimedDecline(expr primedformula){
			auto cons=getConsts(primedformula);
			expr unprimedformula=primedformula;
			for(expr con:*cons){
				if(isPrimedVariable(con)){
					expr unprimedcon=unprime(con);
					unprimedformula=substitute(unprimedformula,con,unprimedcon);
				}
			}
			return unprimedformula;
		}
		
		expr primedLift(expr unprimedformula){
			auto cons=getConsts(unprimedformula);
			expr primedformula=unprimedformula;
			for(expr con:*cons){
				if(!isPrimedVariable(con)){
					expr primedcon=prime(con);
					primedformula=substitute(primedformula,con,primedcon);
				}
			}
			return primedformula;
		}
	
		unique_ptr<vector<expr>> primedLift(vector<expr> * unprimedformulas){
			unique_ptr<vector<expr>> primedLiftformulas(new vector<expr>());
			for(expr upf:*unprimedformulas){
				primedLiftformulas->push_back(primedLift(upf));
			}
			return primedLiftformulas;
		}
		unique_ptr<vector<expr>> primedFiltering(vector<expr> * formulas){
			unique_ptr<vector<expr>> primeds(new vector<expr>());
			for(expr f: *formulas){
				if(!hasUnPrimedVariable(f)){
					primeds->push_back(f);
				}
			}
			return primeds;
		}


		unique_ptr<vector<expr>> unprimedFiltering(vector<expr> * formulas){
			unique_ptr<vector<expr>> unprimeds(new vector<expr>());
			for(expr f: *formulas){
				if(!hasPrimedVariable(f)){
					unprimeds->push_back(f);
				}
			}
			return unprimeds;
		}
		unique_ptr<vector<expr>> unprimedDecline(vector<expr> * primedformulas){
			unique_ptr<vector<expr>> unprimedDeclineformulas(new vector<expr>());
			for(expr pf:*primedformulas){
				unprimedDeclineformulas->push_back(unprimedDecline(pf));
			}
			return unprimedDeclineformulas;
		}
		/*
		 * format: exists x. extendFormula && begin<x && x<end && (x-begin)%step=0 => body
		 */
		expr constructExistFormula(expr quantifier, expr beginFormula,expr endFormula, expr stepFormula, expr body){
			return _exist(quantifier,implies(beginFormula&&endFormula&&stepFormula,body));
		}
		expr constructExistFormula(expr quantifier, expr extendFormula,expr beginFormula,expr endFormula, expr stepFormula, expr body){
			return _exist(quantifier,implies(extendFormula&&beginFormula&&endFormula&&stepFormula,body));
		}
		expr constructExistFormula_step(expr quantifier, expr extendFormula,expr beginFormula,expr endFormula, expr step,expr indexinit, expr body){		
			return _exist(quantifier,implies(extendFormula&&beginFormula&&endFormula&&to_expr(c,Z3_mk_mod(c,quantifier-indexinit,step))==0,body));
		}
		expr constructExistFormula_step(expr quantifier,expr beginFormula,expr endFormula, expr step,expr indexinit, expr body){		
			return _exist(quantifier,implies(beginFormula&&endFormula&&to_expr(c,Z3_mk_mod(c,quantifier-indexinit,step))==0,body));
		}
		expr getExistFormulaBegin(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExsitFormulaBegin: can not get Begin from " <<existFormula<<std::endl;
				return _error;
			}
			expr body=existFormula.arg(1);
			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
			if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
				expr beginFormula=extendIndexAndBeginFormula.arg(1);
				expr begin=beginFormula.arg(0);
				return begin;
			}
			else {
				expr begin=extendIndexAndBeginFormula.arg(0);
				return begin;
			}
		}
		expr getExistFormulaBeginFormula(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExsitFormulaBeginFormula: can not get BeginFormula from " <<existFormula<<std::endl;
				return _error;
			}
			expr quantifier=getQuantifier(existFormula);
			expr body=existFormula.arg(1);

			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
			if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
				expr beginFormula=extendIndexAndBeginFormula.arg(1);
				return beginFormula;
			}
			else {
				return extendIndexAndBeginFormula;
			}
		}

		expr getExistFormulaExtendFormula(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExistFormulaExtendFormula: can not get ExtendFormula from " <<existFormula<<std::endl;
				return _error;
			}
			expr quantifier=getQuantifier(existFormula);
			expr body=existFormula.arg(1);

			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr extendIndexAndBeginFormula=extendIndexAndbeginEndformula.arg(0); 
			if(Z3_is_eq_func_decl(c,extendIndexAndBeginFormula.decl(),AndDecl)){
				expr extendFormula=extendIndexAndBeginFormula.arg(0);
				return extendFormula;
			}
			else {
				return _error;
			}
		}
		expr getExistFormulaEnd(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExsitFormulaEnd: can not get End from " <<existFormula<<std::endl;
				return _error;
			}
			expr body=existFormula.arg(1);
			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr endFormula=extendIndexAndbeginEndformula.arg(1); 
			expr end=endFormula.arg(1);
			return end;
		}
		expr getExistFormulaEndFormula(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExistFormulaEndFormula: can not get EndFormula from " <<existFormula<<std::endl;
				return _error;
			}
			expr quantifier=getQuantifier(existFormula);
			expr body=existFormula.arg(1);
			expr interval=body.arg(0);
			expr extendIndexAndbeginEndformula=interval.arg(0);
			expr endFormula=extendIndexAndbeginEndformula.arg(1); 
			return endFormula;
		}
		expr getExistFormulaStep(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExistFormulaStep: can not get QuantifierExistStep from " <<existFormula<<std::endl;
				return _error;
			}
			expr body=existFormula.arg(1);
			expr interval=body.arg(0);
			expr stepformula=interval.arg(1);
			expr step=stepformula.arg(0).arg(1);
			return step;
		}
		expr getExistFormulaStepFormula(expr existFormula){
			if(!isExistFormula(existFormula)){
				std::cerr<<"Z3Coding:getExistFormulaStepFormula: can not get QuantifierExistStepFormula from " <<existFormula<<std::endl;
				return _error;
			}
			expr quantifier=getQuantifier(existFormula);
			expr body=existFormula.arg(1);
			expr interval=body.arg(0);
			expr stepformula=interval.arg(1);
			return stepformula;
		}

		
		unique_ptr<vector<expr>> getAllQuantifierFormulaBeginFormula(expr quantifierFormula){
			unique_ptr<vector<expr>> beginFormulas(new vector<expr>());
			expr tmp=quantifierFormula;
			while(isForAllFormula(tmp)||isExistFormula(tmp)){
				expr beginFormula(c);
				if(isForAllFormula(tmp)){
					beginFormula=getForAllFormulaBeginFormula(tmp);

				}
				if(isExistFormula(tmp)) {
					beginFormula=getExistFormulaBeginFormula(tmp);
				}
				beginFormulas->push_back(beginFormula);
				tmp=getQuantifierFormulaBody(tmp);
			}
			return beginFormulas;
		}
		unique_ptr<vector<expr>> getAllQuantifierFormulaEndFormula(expr quantifierFormula){
			unique_ptr<vector<expr>> endformulas(new vector<expr>());
			expr tmp=quantifierFormula;
			while(isForAllFormula(tmp)||isExistFormula(tmp)){
				expr endformula(c);
				if(isForAllFormula(tmp)){
					endformula=getForAllFormulaEndFormula(tmp);
				}
				if(isExistFormula(tmp)) {
					endformula=getExistFormulaEndFormula(tmp);
				}
				endformulas->push_back(endformula);
				tmp=getQuantifierFormulaBody(tmp);
			}
			return endformulas;
		}
		unique_ptr<vector<expr>> getAllQuantifierFormulaStep(expr quantifierFormula){
			unique_ptr<vector<expr>> steps(new vector<expr>());
			expr tmp=quantifierFormula;
			while(isForAllFormula(tmp)||isExistFormula(tmp)){
				expr step(c);
				if(isForAllFormula(tmp)){
					step=getForAllFormulaStep(tmp);
				}
				if(isExistFormula(tmp)) {
					step=getExistFormulaStep(tmp);
				}
				steps->push_back(step);
				tmp=getQuantifierFormulaBody(tmp);
			}
			return steps;
		}
		unique_ptr<vector<expr>> getAllQuantifierFormulaStepFormulas(expr quantifierFormula){
			unique_ptr<vector<expr>> stepFormulas(new vector<expr>());
			expr tmp=quantifierFormula;
			while(isForAllFormula(tmp)||isExistFormula(tmp)){
				expr stepFormula(c);
				if(isForAllFormula(tmp)){
					stepFormula=getForAllFormulaStepFormula(tmp);
				}
				if(isExistFormula(tmp)) {
					stepFormula=getExistFormulaStepFormula(tmp);
				}
				stepFormulas->push_back(stepFormula);
				tmp=getQuantifierFormulaBody(tmp);
			}
			return stepFormulas;
		}
		expr forAllFormulaDegradeToExistFormula(expr forallFormula){
			expr quantifier=getQuantifier(forallFormula);
			expr beginFormula=getForAllFormulaBeginFormula(forallFormula);
			expr endFormula=getForAllFormulaEndFormula(forallFormula);
			expr stepFormula=getForAllFormulaStepFormula(forallFormula);
			expr extendFormula=getForAllFormulaExtendFormula(forallFormula);
			expr body=getQuantifierFormulaBody(forallFormula);
			if(checkError(extendFormula)){
				return constructExistFormula(quantifier,beginFormula,endFormula,stepFormula,body);
			}
			else{
				return constructExistFormula(quantifier,extendFormula,beginFormula,endFormula,stepFormula,body);
			}

		}
		/*//copy from ArrayInvAnalysis_FeasiblePath.h
		expr reduce(vector<expr> * Pre,expr f){
			auto disjunctionForms=DNF(f);
			vector<expr>* satDisjunctionForms=reduction(Pre,disjunctionForms);
			if(satDisjunctionForms->size()==0){
				return c.bool_val(false);
			}
			else{
				expr ret=satDisjunctionForms->at(0);
				for(unsigned i=1;i<satDisjunctionForms->size();i++){
					ret=ret||satDisjunctionForms->at(i);
				}
				return ret;
			}
		}*/
		expr existFormulaImprovedToForAllFormula(expr existFormula){
			expr quantifier=getQuantifier(existFormula);
			expr beginFormula=getExistFormulaBeginFormula(existFormula);
			expr endFormula=getExistFormulaEndFormula(existFormula);
			expr stepFormula=getExistFormulaStepFormula(existFormula);
			expr extendFormula=getExistFormulaExtendFormula(existFormula);
			expr body=getQuantifierFormulaBody(existFormula);
			if(checkError(extendFormula)){
				return constructForAllFormula(quantifier,beginFormula,endFormula,stepFormula,body);
			}
			else{
				return constructForAllFormula(quantifier,extendFormula,beginFormula,endFormula,stepFormula,body);
			}
		}
		
		unique_ptr<vector<expr>> filteringLeftSimpleFormula(vector<expr> * formulas){
			unique_ptr<vector<expr>> result(new vector<expr>());
			for(expr e:*formulas){
				if(isSimpleFormula(e)){
					result->push_back(e);
				}
			}
			return result;
		}
		unique_ptr<vector<expr>> splitLANDFormulas(vector<expr>* formulas){
			unique_ptr<vector<expr>> result(new vector<expr>());
			for(expr f:*formulas){
				auto tmp=splitLANDFormula(f);
				pushAToB(tmp.get(),result.get());
			}
			return result;
		}
		unique_ptr<vector<expr>> splitLANDFormula(expr f){
			unique_ptr<vector<expr>> result(new vector<expr>());
			if(f.is_app()&&Z3_is_eq_func_decl(c,f.decl(),AndDecl)){
				auto left=splitLANDFormula(f.arg(0));
				auto right=splitLANDFormula(f.arg(1));
				pushAToB(left.get(),result.get());
				pushAToB(right.get(),result.get());
			}
			else{
				result->push_back(f);
			}
			return result;
		}
		
		
		std::string toString(expr p){
			std::string ret;
			if(isSimpleFormula(p)){
				ret=Z3_ast_to_string(c,p);
				return ret;
			}
			else if(isForAllFormula(p)){
				std::string quantifierStr=Z3_ast_to_string(c,getQuantifier(p));
				std::string beginStr=Z3_ast_to_string(c,getForAllFormulaBegin(p));
				expr beginFormula=getForAllFormulaBeginFormula(p);
				std::string endStr=Z3_ast_to_string(c,getForAllFormulaEnd(p));
				expr endFormula=getForAllFormulaEndFormula(p);
				std::string stepStr=Z3_ast_to_string(c,getForAllFormulaStep(p));
				expr body=getQuantifierFormulaBody(p);

				std::string ret="forall "+quantifierStr+ " in ";
				if(Z3_is_eq_func_decl(c,beginFormula.decl(),LeDecl)){
					ret+="[";
				}
				else{
					ret+="(";
				}
				ret+=beginStr+","+stepStr+","+endStr;
				if(Z3_is_eq_func_decl(c,endFormula.decl(),LeDecl)){
					ret+="]";
				}
				else{
					ret+=")";
				}
				ret+=",";
				std::string bodyStr=toString(body);
				ret+=bodyStr;
				return ret;
			}
			else if(isExistFormula(p)){
				std::string quantifierStr=Z3_ast_to_string(c,getQuantifier(p));
				std::string beginStr=Z3_ast_to_string(c,getExistFormulaBegin(p));
				expr beginFormula=getExistFormulaBeginFormula(p);
				std::string endStr=Z3_ast_to_string(c,getExistFormulaEnd(p));
				expr endFormula=getExistFormulaEndFormula(p);
				std::string stepStr=Z3_ast_to_string(c,getExistFormulaStep(p));
				expr body=getQuantifierFormulaBody(p);

				std::string ret="exist "+quantifierStr +" in ";
				if(Z3_is_eq_func_decl(c,beginFormula.decl(),LeDecl)){
					ret+="[";
				}
				else{
					ret+="(";
				}
				ret+=beginStr+","+stepStr+","+endStr;
				if(Z3_is_eq_func_decl(c,endFormula.decl(),LeDecl)){
					ret+="]";
				}
				else{
					ret+=")";
				}
				ret+=",";
				std::string bodyStr=toString(body);
				ret+=bodyStr;
				return ret;
			}
			
			else if(isPhiFormula(p)){
				std::string quantifierStr=Z3_ast_to_string(c,getPhiQuantifier(p));
				std::string beginStr=Z3_ast_to_string(c,getPhiBegin(p));
				expr beginFormula=getPhiBeginFormula(p);
				std::string endStr=Z3_ast_to_string(c,getPhiEnd(p));
				expr endFormula=getPhiEndFormula(p);
				std::string stepStr=Z3_ast_to_string(c,getPhiStep(p));

				std::string ret="forall "+quantifierStr+'.'+quantifierStr+ " in ";
				if(Z3_is_eq_func_decl(c,beginFormula.decl(),LeDecl)){
					ret+="[";
				}
				else{
					ret+="(";
				}
				ret+=beginStr+","+stepStr+","+endStr;
				if(Z3_is_eq_func_decl(c,endFormula.decl(),LeDecl)){
					ret+="]";
				}
				else{
					ret+=")";
				}
				ret+=",";
				std::string bodyStr="phi";
				ret+=bodyStr;
				return ret;
			}
			else if(p.is_app()&&isOrFormula(p)){
				auto dnfs=splitOrFormulas(p);
				//cout<<toString(dnfs)<<std::endl;
				ret="{"+toString(dnfs->at(0))+"}";
				for(int i=1;i<(int)dnfs->size();i++){
					ret+=" || {"+toString(dnfs->at(i))+"}";
				}
				return ret;
			}
			else{
				cerr<<"Z3Coding::toString(expr)::something is wrong!"<<std::endl;
				cerr<<"error info:: p is : "<<p<<std::endl;
			}
			return "error";
		}
		bool partialOrderRelation_ForAllFormula_ForAllFormula(expr forAllFormula1,expr forAllFormula2){
			expr forallBody1=getQuantifierFormulaBody(forAllFormula1);
			expr forallBody2=getQuantifierFormulaBody(forAllFormula2);

			if(!partialOrderRelation(forallBody1,forallBody2)){
				return false;
			}

			expr quantifier1=getQuantifier(forAllFormula1);
			expr step1=getForAllFormulaStep(forAllFormula1);
			expr step1Formula=getForAllFormulaStepFormula(forAllFormula1);
			expr quantifierBegin1=getForAllFormulaBegin(forAllFormula1);
			expr quantifierEnd1=getForAllFormulaEnd(forAllFormula1);
			expr quantifierBeginFormula1=getForAllFormulaBeginFormula(forAllFormula1);
			expr quantifierEndFormula1=getForAllFormulaEndFormula(forAllFormula1);
			expr quantifierExtendFormula1=getForAllFormulaExtendFormula(forAllFormula1);

			expr quantifier2=getQuantifier(forAllFormula2);
			expr step2=getForAllFormulaStep(forAllFormula2);
			expr quantifierBegin2=getForAllFormulaBegin(forAllFormula2);
			expr quantifierEnd2=getForAllFormulaEnd(forAllFormula2);
			expr quantifierBeginFormula2=getForAllFormulaBeginFormula(forAllFormula2);
			expr quantifierEndFormula2=getForAllFormulaEndFormula(forAllFormula2);
			expr quantifierExtendFormula2=getForAllFormulaExtendFormula(forAllFormula2);

			if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
					||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
				return false;
			}

			if(!checkError(quantifierExtendFormula1)||!checkError(quantifierExtendFormula2)){
				expr quantifierExtendFormula2To1=substitute(quantifierExtendFormula2,quantifier2,quantifier1);
				if(!equal(quantifierExtendFormula2To1,quantifierExtendFormula1)){
					return false;
				}
			}
			if(equal(step1,step2)
					&&Z3_is_eq_func_decl(c,quantifierBegin1.decl(),quantifierBegin2.decl())
					&&equal(quantifierBegin1,quantifierBegin2)
					&&Z3_is_eq_func_decl(c,quantifierEnd1.decl(),quantifierEnd2.decl())
					&&equal(quantifierEnd1,quantifierEnd2)){
				if(!checkError(quantifierExtendFormula1)&&!checkError(quantifierExtendFormula2)){
					return true; 
				}
				else{
					return true;
				}
			}

			else{
				return false;
			}
		}
		bool partialOrderRelation_ForAllFormula_ExistFormula(expr forAllFormula,expr existFormula){
			expr forallBody=getQuantifierFormulaBody(forAllFormula);
			expr existBody=getQuantifierFormulaBody(existFormula);
			//12.30 body can not be or
			if(!partialOrderRelation(forallBody,existBody)){
				return false;
			}


			expr quantifier1=getQuantifier(forAllFormula);
			expr step1=getForAllFormulaStep(forAllFormula);
			expr step1Formula=getForAllFormulaStepFormula(forAllFormula);
			expr quantifierBegin1=getForAllFormulaBegin(forAllFormula);
			expr quantifierEnd1=getForAllFormulaEnd(forAllFormula);
			expr quantifierBeginFormula1=getForAllFormulaBeginFormula(forAllFormula);
			expr quantifierEndFormula1=getForAllFormulaEndFormula(forAllFormula);
			expr quantifierExtendFormula1=getForAllFormulaExtendFormula(forAllFormula);

			expr quantifier2=getQuantifier(existFormula);
			expr step2=getExistFormulaStep(existFormula);
			expr step2Formula=getExistFormulaStepFormula(existFormula);
			expr quantifierBegin2=getExistFormulaBegin(existFormula);
			expr quantifierEnd2=getExistFormulaEnd(existFormula);
			expr quantifierBeginFormula2=getExistFormulaBeginFormula(existFormula);
			expr quantifierEndFormula2=getExistFormulaEndFormula(existFormula);
			expr quantifierExtendFormula2=getExistFormulaExtendFormula(existFormula);

			if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
					||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
				return false;
			}


			if(!checkError(quantifierExtendFormula1)||!checkError(quantifierExtendFormula2)){
				expr quantifierExtendFormula2To1=substitute(quantifierExtendFormula2,quantifier2,quantifier1);
				if(!equal(quantifierExtendFormula2To1,quantifierExtendFormula1)){
					return false;
				}
			}
			if(!equal(step1,step2)){
				return false;
			}
			if(quantifierBegin1.decl().name().str()!=quantifierBegin2.decl().name().str()||!equal(quantifierBegin1,quantifierBegin2)
					||quantifierEnd1.decl().name().str()!=quantifierEnd2.decl().name().str()||!equal(quantifierEnd1,quantifierEnd2)){
				return false;
			}
			return true;
		}
		bool partialOrderRelation_PhiFormula_ForAllFormula(expr f1,expr f2){
			return false;
		}
		bool partialOrderRelation_PhiFormula_ExistFormula(expr f1,expr f2){
			return false;
		}
		bool partialOrderRelation_ExistFormula_ExistFormula(expr existFormula1,expr existFormula2){
			expr existBody1=getQuantifierFormulaBody(existFormula1);
			expr existBody2=getQuantifierFormulaBody(existFormula2);
			if(!partialOrderRelation(existBody1,existBody2)){
				return false;
			}


			expr quantifier1=getQuantifier(existFormula1);
			expr step1=getExistFormulaStep(existFormula1);
			expr step1Formula=getExistFormulaStepFormula(existFormula1);
			expr quantifierBegin1=getExistFormulaBegin(existFormula1);
			expr quantifierEnd1=getExistFormulaEnd(existFormula1);
			expr quantifierBeginFormula1=getExistFormulaBeginFormula(existFormula1);
			expr quantifierEndFormula1=getExistFormulaEndFormula(existFormula1);
			expr quantifierExtendFormula1=getExistFormulaExtendFormula(existFormula1);

			expr quantifier2=getQuantifier(existFormula2);
			expr step2=getExistFormulaStep(existFormula2);
			expr step2Formula=getExistFormulaStepFormula(existFormula2);
			expr quantifierBegin2=getExistFormulaBegin(existFormula2);
			expr quantifierEnd2=getExistFormulaEnd(existFormula2);
			expr quantifierBeginFormula2=getExistFormulaBeginFormula(existFormula2);
			expr quantifierEndFormula2=getExistFormulaEndFormula(existFormula2);
			expr quantifierExtendFormula2=getExistFormulaExtendFormula(existFormula2);

			if(quantifierBegin1.is_var()||quantifierBegin2.is_var()
					||quantifierEnd1.is_var()||quantifierEnd2.is_var()){
				return false;
			}


			if(!checkError(quantifierExtendFormula1)||!checkError(quantifierExtendFormula2)){
				expr quantifierExtendFormula2To1=substitute(quantifierExtendFormula2,quantifier2,quantifier1);
				if(!equal(quantifierExtendFormula2To1,quantifierExtendFormula1)){
					return false;
				}
			}
			if(!equal(step1,step2)){
				return false;
			}
			if(quantifierBegin1.decl().name().str()!=quantifierBegin2.decl().name().str()||!equal(quantifierBegin1,quantifierBegin2)
					||quantifierEnd1.decl().name().str()!=quantifierEnd2.decl().name().str()||!equal(quantifierEnd1,quantifierEnd2)){
				return false;
			}
			return true;
		}
		
		bool partialOrderRelation_SimpleFormula_SimpleFormula(expr f1,expr f2){
			return false;
		}
		bool partialOrderRelation(expr f1,expr f2){
			if(isPhiFormula(f1)&&isForAllFormula(f2)){
				return partialOrderRelation_PhiFormula_ForAllFormula(f1,f2);
			}
			else if(isSimpleFormula(f1)&&isSimpleFormula(f2)){
				return partialOrderRelation_SimpleFormula_SimpleFormula(f1,f2);
			}
			else if(isForAllFormula(f1)&&isForAllFormula(f2)){
				return partialOrderRelation_ForAllFormula_ForAllFormula(f1,f2);
			}

			else if(isExistFormula(f1)&&isExistFormula(f2)){
				return partialOrderRelation_ExistFormula_ExistFormula(f1,f2);
			}

			else if(isForAllFormula(f1)&&isExistFormula(f2)){
				return partialOrderRelation_ForAllFormula_ExistFormula(f1,f2);
			}
			return false;

		}
		expr eliminateNotInSimpleFormula(expr e){
			expr ret=_eliminateNotInSimpleFormula(e);
			return ret;
		}
		expr _eliminateNotInSimpleFormula(expr e){
			if(e.is_app()&&Z3_is_eq_func_decl(c,e.decl(),NotDecl)){
				if(e.arg(0).is_app()){
					if(Z3_is_eq_func_decl(c,e.arg(0).decl(),NotDecl)){
						return _eliminateNotInSimpleFormula(e.arg(0).arg(0));
					}
					if(Z3_is_eq_func_decl(c,e.arg(0).decl(),DistinctDecl)){
						expr tmp=e.arg(0).arg(0)==e.arg(0).arg(1);
						return _eliminateNotInSimpleFormula(tmp);
					}
					if(Z3_is_eq_func_decl(c,e.arg(0).decl(),LtDecl)){
						return e.arg(0).arg(0)>=e.arg(0).arg(1);
					}
					else if(Z3_is_eq_func_decl(c,e.arg(0).decl(),LeDecl)){
						return e.arg(0).arg(0)>e.arg(0).arg(1);
					}
					else if(Z3_is_eq_func_decl(c,e.arg(0).decl(),GtDecl)){
						return e.arg(0).arg(0)<=e.arg(0).arg(1);
					}
					else if(Z3_is_eq_func_decl(c,e.arg(0).decl(),GeDecl)){
						return e.arg(0).arg(0)<e.arg(0).arg(1);
					}
					else{
						return e;
					}
				}
				else{
					return e;
				}
			}
			else{
				return e;
			}
		}
		
	
	
	bool isAssignment(expr stmt){
		if(stmt.is_app()){
			return Z3_is_eq_func_decl(c,stmt.decl(),_AS);
		}
		return false;
	}
	
	bool isAssigndToArrayAcess(expr stmt){
		if(isAssignment(stmt)){
			expr lhs=stmt.arg(0).arg(0);
			if(lhs.decl().name().str()=="select"){
				return true;
			}
		}
		return false;
	}
	bool isAssigndToScaleVariable(expr stmt){
		if(isAssignment(stmt)){
			expr lhs=stmt.arg(0).arg(0);
			return isPrimedVariable(lhs);
		}
		return false;
	}
	bool isScalaVariableInitStmt(expr stmt){
		if(isAssigndToScaleVariable(stmt)){
			expr lhs=stmt.arg(0).arg(0);
			expr rhs=stmt.arg(0).arg(1);
			expr scalaVar=unprime(lhs);
			auto ign=getConsts(rhs);
			if(!isIn(scalaVar,ign.get())){
				return true;
			}
			return false;
		}
		return false;
	}
	bool isScalaVariableUpdateStmt(expr stmt){
		if(isAssigndToScaleVariable(stmt)){
			expr lhs=stmt.arg(0).arg(0);
			expr rhs=stmt.arg(0).arg(1);
			expr scalaVar=unprime(lhs);
			auto ign=getConsts(rhs);
			if(!isIn(scalaVar,ign.get())){
				return false;
			}
			return true;
		}
		return false;
	}
	expr eliminateGtAndGe(expr e){
		if(e.is_app()){
			//if(e.decl().name().str()==">"){
			if(Z3_is_eq_func_decl(c,e.decl(),GtDecl)){
				return e.arg(1)<e.arg(0);
			}
			//if(e.decl().name().str()==">="){
			if(Z3_is_eq_func_decl(c,e.decl(),GeDecl)){
				return e.arg(1)<=e.arg(0);
			}
		}
		return e;
	}
	bool isNe(expr e){
		if(e.is_app()){
			//if(e.decl().name().str()=="not"){
			if(Z3_is_eq_func_decl(c,e.decl(),NotDecl)){
				if(e.arg(0).is_app()){
					//if(e.arg(0).decl().name().str()=="="){
					if(Z3_is_eq_func_decl(c,e.arg(0).decl(),EqDecl)){
						return true;
					}
				}
			}
		}
		return false;
	}
	/**
	 * @brief get all QuantifierDerAccess from exist formula and forall formula
	 * 			e.g forall k. p(*(k+1),*(k)...), return *(k+1),*(k)
	 * @param formula is QuantifierFormula
	 * @return 
	 */
	unique_ptr<vector<expr>> getQuantifierFormulaQuantifierDerAccess(expr formula){
		unique_ptr<vector<expr>> ret(new vector<expr>());
		auto defAcessMemoryUnits=getDerAcessMemoryUnits(formula);
		auto quantifiers=getAllQuantifier(formula);
		for(expr q:*quantifiers){
			for(expr defAcessMemoryU:*defAcessMemoryUnits){
				auto consts=getConsts(defAcessMemoryU);
				if(isIn(q,consts.get())){
					ret->push_back(defAcessMemoryU);
				}
			}
		}
		return ret;
	}
	unique_ptr<vector<expr>> getQuantifierFormulaQuantifierMemoryAccess(expr formula){
		unique_ptr<vector<expr>> ret(new vector<expr>());
		auto memoryUnits=getMemoryUnitsWithQuantifierFormula(formula);
		auto quantifiers=getAllQuantifier(formula);
		for(expr q:*quantifiers){
			for(expr memoryU:*memoryUnits){
				auto consts=getConsts(memoryU);
				if(isIn(q,consts.get())){
					ret->push_back(memoryU);
				}
			}
		}
		return ret;
	}	
	/**
	 * @brief if e is e1@point, return true;
	 * @param e
	 * @return 
	 */
	bool isAtExpr(expr e){
		if(e.is_app()){
			std::string op=e.decl().name().str();
			std::string str="@";
			std::size_t found = op.find(str);
			if (found!=std::string::npos){
				return true;
			}
		}
		return false;
	}
	unique_ptr<vector<expr>> getMemoryUnitsWithQuantifierFormula(expr e){
		unique_ptr<vector<expr>> memoryUnits(new vector<expr>());
		if(e.is_const()){
			if(!isAtExpr(e)&&!e.is_numeral()){
				memoryUnits->push_back(e);
			}
			return memoryUnits;
		}
		else if(isArrayAcess(e)){
			memoryUnits->push_back(e);
			//vector<expr> * argmemoryUnits=getMemoryUnits(e.arg(0));
			//pushAToB(argmemoryUnits,memoryUnits);
			//vector<expr> * argmemoryUnits=getMemoryUnits(e.arg(1));
			//pushAToB(argmemoryUnits,memoryUnits);
			return memoryUnits;
		}
		else if(is_quantifier(e)){
			expr quantifier=getQuantifier(e);
			if(isForAllFormula(e)){
				/*expr body=e.body();
				expr newbody=substitute_var(c,body,quantifier);
				memoryUnits=getMemoryUnitsWithQuantifierFormula(newbody);
				return memoryUnits;*/
				expr begin=getForAllFormulaBegin(e);
				expr end=getForAllFormulaEnd(e);
				expr step=getForAllFormulaStep(e);
				expr body=getForAllFormulaBodyFormula(e);
				auto beginUnits=getMemoryUnitsWithQuantifierFormula(begin);
				auto endUnits=getMemoryUnitsWithQuantifierFormula(end);
				auto stepUnits=getMemoryUnitsWithQuantifierFormula(step);
				auto bodyUnits=getMemoryUnitsWithQuantifierFormula(body);
				pushAToB(beginUnits.get(),memoryUnits.get());
				pushAToB(endUnits.get(),memoryUnits.get());
				pushAToB(stepUnits.get(),memoryUnits.get());
				pushAToB(bodyUnits.get(),memoryUnits.get());
				return memoryUnits;
			}
			else{
				/*expr body=e.arg(1);
				memoryUnits=getMemoryUnitsWithQuantifierFormula(body);
				return memoryUnits;*/
				expr begin=getExistFormulaBegin(e);
				expr end=getExistFormulaEnd(e);
				expr step=getExistFormulaStep(e);
				expr body=getQuantifierFormulaBody(e);
				auto beginUnits=getMemoryUnitsWithQuantifierFormula(begin);
				auto endUnits=getMemoryUnitsWithQuantifierFormula(end);
				auto stepUnits=getMemoryUnitsWithQuantifierFormula(step);
				auto bodyUnits=getMemoryUnitsWithQuantifierFormula(body);
				pushAToB(beginUnits.get(),memoryUnits.get());
				pushAToB(endUnits.get(),memoryUnits.get());
				pushAToB(stepUnits.get(),memoryUnits.get());
				pushAToB(bodyUnits.get(),memoryUnits.get());
				return memoryUnits;
			}
			
		}
		else if(isPhiFormula(e)){
			/*z3::symbol sym(c,Z3_get_quantifier_bound_name(c,e,0));
			z3::sort s(c,Z3_get_quantifier_bound_sort(c,e,0));
			expr quantifier=c.constant(sym,s);
			expr body=substitute_var(c,e.body(),quantifier);
			memoryUnits=getMemoryUnitsWithQuantifierFormula(body);*/
			expr begin=getPhiBegin(e);
			expr end=getPhiEnd(e);
			expr step=getPhiStep(e);
			auto beginUnits=getMemoryUnitsWithQuantifierFormula(begin);
			auto endUnits=getMemoryUnitsWithQuantifierFormula(end);
			auto stepUnits=getMemoryUnitsWithQuantifierFormula(step);
			pushAToB(beginUnits.get(),memoryUnits.get());
			pushAToB(endUnits.get(),memoryUnits.get());
			pushAToB(stepUnits.get(),memoryUnits.get());
			return memoryUnits;
		}
		else if(e.is_var()){
			return memoryUnits;
		}
		if(e.is_app()){
			if(isDer_PointerExpr(e)){
				memoryUnits->push_back(e);
				return memoryUnits;
			}
			else if(isDirectMemberExpr(e)){
				memoryUnits->push_back(e);
				return memoryUnits;
			}
			else if(isIndirectMemberExpr(e)){
				memoryUnits->push_back(e);
				return memoryUnits;
			}
			else{
				for(unsigned i=0;i<e.num_args();i++){
					auto argmemoryUnits=getMemoryUnitsWithQuantifierFormula(e.arg(i));
					pushAToB(argmemoryUnits.get(),memoryUnits.get());
				}			
			}
		}
		return memoryUnits;
	}
	const Type* getTypeBy(expr memoryUnit){
		if(isArrayAcess(memoryUnit)||isDer_PointerExpr(memoryUnit)
		||isMemberExpr(memoryUnit)||memoryUnit.is_const()){
			std::string name=Z3_ast_to_string(c,memoryUnit);
			if(this->memoryUnitsToClangExpr.count(name)>0){
				const clang::Expr* clangexpr=this->memoryUnitsToClangExpr.at(name);
				return clangexpr->getType().getTypePtr();			
			}
			else{
				if(isDer_PointerExpr(memoryUnit)){
					auto cons=getConsts(memoryUnit.arg(0));
					if(cons->size()==1){
						std::string name=Z3_ast_to_string(c,cons->at(0));
						if(this->memoryUnitsToClangExpr.count(name)>0){
							const clang::Expr* clangexpr=this->memoryUnitsToClangExpr.at(name);
							return clangexpr->getType().getTypePtr()->getPointeeType().getTypePtr();
						}
					}
				}
				//cerr<<"something is wrong! we can not find it!"<<std::endl;
				//cerr<<"error info:: memoryUnit is: "<<memoryUnit<<std::endl;
				return nullptr;
			}
		}
		else{
			cerr<<"something is wrong!"<<std::endl;
			cerr<<"error info:: memoryUnit is: "<<memoryUnit<<std::endl;
			return nullptr;
		}
	}
	unique_ptr<vector<expr>> splitOrFormulas(expr f){
		unique_ptr<vector<expr>> ret(new vector<expr>());
		if(f.is_app()&&Z3_is_eq_func_decl(c,f.decl(),OrDecl)){
			auto t1=splitOrFormulas(f.arg(0));
			auto t2=splitOrFormulas(f.arg(1));
			pushAToB(t1.get(),ret.get());
			pushAToB(t2.get(),ret.get());
		}
		else{
			ret->push_back(f);
		}
		return ret;
	}
	
};

#endif
