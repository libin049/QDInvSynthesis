#ifndef _UserSuppliedInstanceOfRelation_H
#define _UserSuppliedInstanceOfRelation_H
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

class UserSuppliedInstanceOfRelation : public UserSupplied{
private:
	context &c;
	Z3Coding &z3coding;
	MemoryUtil &mu;
	C2Z3* c2z3Stmt;
	Formula* _simpleFormulaMeet(Formula * f1,Formula *f2){
			expr e1= f1->formula;
			expr e2= f2->formula;
			return new Formula(_simpleFormulaMeet(e1,e2));
		}
		expr _simpleFormulaMeet(expr e1,expr e2){
			/*if(e1.is_app()&&e2.is_app()){
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
			return z3coding._error;*/
			return meet(e1,e2);
		}
		expr meet(expr e1,expr e2){
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.EqDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
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
					
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1r<=e1l;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1r<=e1l;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						return z3coding._error;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LtDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l<=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LeDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l<=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						return z3coding._error;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				else if(z3coding.isNe(e1)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return z3coding._error;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return z3coding._error;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.DistinctDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
			}
			return z3coding._error;
		}
	/*expr _meet(expr e1,expr e2){
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			unsigned e1hash=e1.decl().hash();
			unsigned e2hash=e2.decl().hash();
			unsigned Eqhash=z3coding.EqDecl.hash();
			unsigned Lthash=z3coding.LtDecl.hash();
			unsigned Lehash=z3coding.LeDecl.hash();
			unsigned Distincthash=z3coding.DistinctDecl.hash();
			
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(e1hash==Eqhash){
					if(e2hash==Eqhash){
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
					
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1r<=e1l;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1r<=e1l;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						return z3coding._error;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				else if(e1hash==Lthash){
					if(e2hash==Eqhash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l<=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(e1hash==Lehash){
					if(e2hash==Eqhash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l<=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l<=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return z3coding._error;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						return z3coding._error;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				else if(z3coding.isNe(e1)){
					if(e2hash==Eqhash){
						return z3coding._error;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						return z3coding._error;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				else if(e1hash==Distincthash){
					if(e2hash==Eqhash){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						return z3coding._error;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return e1l!=e1r;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return e1l!=e1r;
						}
						else{
							return z3coding._error;
						}
					}
				}
			}
			return z3coding._error;
		}*/
	bool isEquation(vector<Property*>* env,expr e,const clang::Stmt* clangStmt,int count){
		if(e.is_app()&&e.decl().name().str()=="="){
			expr left=e.arg(0);
			expr right=e.arg(1);
			//cout<<"left is "<<left<<std::endl;
			//cout<<"right is "<<right<<std::endl;
			auto ign=toExprs(env);
			if(mu.mayMemoryUnitIsInFormula(ign.get(),z3coding.unprimedDecline(left),right,clangStmt,count)){
				return false;
			}
		}
		return true;
	}
	unique_ptr<vector<expr>> toExprs(vector<Property*>* env){
		unique_ptr<vector<expr>> ret(new vector<expr>());
		for(Property * p:*env){
			Formula* f =(Formula*)p;
			ret->push_back(f->formula);
		}
		
		return ret;
	}
	expr genProperty(expr stmt,vector<Property*>* env,const clang::Stmt* clangStmt,int count){
		if(z3coding.isAssignment(stmt)){
			if(isEquation(env,stmt.arg(0),clangStmt,count)){
				return stmt.arg(0);
			}
			//if *e1:=*e2 or e1[e2]:=e3[e4], return *e1=*e2 or e1[e2]=e3[e4]
			expr lhs=stmt.arg(0).arg(0);
			expr rhs=stmt.arg(0).arg(1);
			if(z3coding.isArrayAcess(rhs)||z3coding.isDer_PointerExpr(rhs)){
				return stmt.arg(0);
			}
			
			return z3coding._error;
		}
		else{
			return stmt;
		}
	}
	FlowSet* Pos(expr stmt,vector<Property*>* in,const clang::Stmt* clangStmt,int count){
		FlowSet* out=new ValueListSetWithUniversalSet();
		//cout<<"stmt is "<<stmt<<std::endl;
		//(_AS (= (def_pointer__prime (- dest 1)) (def_pointer (- src 1))))
		//kill 
		if(z3coding.isAssignment(stmt)){
			expr tmpstmt=stmt.arg(0);
			expr left=tmpstmt.arg(0);
			//cerr<<"111 left is "<<left<<std::endl;
			for(Property* p:*in){
				Formula* f=(Formula*)p;
				auto ign=toExprs(in);
				if(!mu.mayMemoryUnitIsInFormula(ign.get(),z3coding.unprimedDecline(left),f->formula,clangStmt,count)){
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
		//gen
		expr stmtP=genProperty(stmt,in,clangStmt,count);
		if(!z3coding.checkError(stmtP)){
			out->add(new Formula(z3coding.unprimedDecline(stmtP)));
			out=powerClosure(z3coding.unprimedDecline(stmtP),out);
		}
//		/*硬编码，用于做实验*/
//		if(z3coding.toString(clangStmt)=="s = k"){
//			out->add(new Formula(hard_coded()));
//			out=powerClosure(z3coding.unprimedDecline(hard_coded()),out);
//		}
		
		return out;
	}
	expr hard_coded(){
		//a[k] = a[s]
		expr k=c.int_const("k");
		expr s=c.int_const("s");
		z3::sort arraysort=c.array_sort(c.int_sort(),c.int_sort());
		expr a=c.constant("a",arraysort);
		expr ret=select(a,k)==select(a,s);
		return ret;
	}
	/*FlowSet* closureEq(expr eq,FlowSet* formulas){
		if(!(eq.is_app()&&Z3_is_eq_func_decl(c,eq.decl(),z3coding.EqDecl))) {
			std::cerr<<"UserSuppliedInstancOfRelation:closureEq: something is wrong!"<<std::endl;
			return nullptr;
		}
		vector<Property*>* formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		expr eqleft=eq.arg(0);
		expr eqright=eq.arg(1);
		for(Property* p:*formulasVector){
			Formula* f=(Formula*)p;
			expr e=f->formula;
			if(z3coding.isSimpleFormula(e)){
				expr eleft=e.arg(0);
				expr eright=e.arg(1);
				if(z3coding.equal(eqleft,eleft)&&!z3coding.equal(eqright,eright)){
					expr newe=z3coding.substitute(e,eqleft,eqright);
					out->add(new Formula(newe));
				}
				if(z3coding.equal(eqleft,eright)&&!z3coding.equal(eqright,eleft)){
					expr newe=z3coding.substitute(e,eqleft,eqright);
					out->add(new Formula(newe));
				}
				if(!z3coding.equal(eqleft,eleft)&&z3coding.equal(eqright,eright)){
					expr newe=z3coding.substitute(e,eqright,eqleft);
					out->add(new Formula(newe));
				}
				if(!z3coding.equal(eqleft,eright)&&z3coding.equal(eqright,eleft)){
					expr newe=z3coding.substitute(e,eqright,eqleft);
					out->add(new Formula(newe));
				}
			}
		}
		out->Union(formulas);
		return out;
	}*/
	/**
	 * @brief if closureEqOptimizingStrategy is true, we do not do closureEq
	 * @param eq
	 * @param formula
	 * @return 
	 */
	bool closureEqOptimizingStrategy(expr eq,expr formula){
		expr eqleft=eq.arg(0);
		expr eqright=eq.arg(1);
		if(eqleft.is_numeral()||eqright.is_numeral()){
			return true;
		}
		return false;
	}
	unique_ptr<vector<expr>> closureEq(expr eq,expr formula){
		unique_ptr<vector<expr>> result(new vector<expr>());
		expr eqleft=eq.arg(0);
		expr eqright=eq.arg(1);
		expr eleft(c);
		expr eright(c);
		expr tmp=formula;
		if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
			tmp=formula.arg(0);
		}
		else if(Z3_is_eq_func_decl(c,tmp.decl(),z3coding.LtDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.LeDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.EqDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.GtDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.GeDecl)||
		Z3_is_eq_func_decl(c,tmp.decl(),z3coding.DistinctDecl)){
			eleft=tmp.arg(0);
			eright=tmp.arg(1);
		}
		else{
			return result;
		}
		
		
		if(z3coding.equal(eqleft,eleft)&&!z3coding.equal(eqright,eright)){
			//expr newe=z3coding.substitute(formula,eqleft,eqright);
			/*when eq is a=e, formula is a< a+a+a+a, e+e+e+e will occur,however, e+e+e+e is not in properExpr
			 *e< e+e+e+e is not a proper property*/
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eqright<eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eqright<=eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eqright==eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eqright>eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eqright>=eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eqright!=eright;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
		if(z3coding.equal(eqleft,eright)&&!z3coding.equal(eqright,eleft)){
			//expr newe=z3coding.substitute(formula,eqleft,eqright);
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eleft<eqright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eleft<=eqright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eleft==eqright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eleft>eqright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eleft>=eqright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eleft!=eqright;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
		if(!z3coding.equal(eqleft,eleft)&&z3coding.equal(eqright,eright)){
			//expr newe=z3coding.substitute(formula,eqright,eqleft);
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eleft<eqleft;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eleft<=eqleft;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eleft==eqleft;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eleft>eqleft;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eleft>=eqleft;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eleft!=eqleft;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
		if(!z3coding.equal(eqleft,eright)&&z3coding.equal(eqright,eleft)){
			//expr newe=z3coding.substitute(formula,eqright,eqleft);
			expr tmp1=formula;
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				tmp1=formula.arg(0);
			}
			expr newe(c);
			if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LtDecl)){
				newe=eqleft<eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.LeDecl)){
				newe=eqleft<=eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.EqDecl)){
				newe=eqleft==eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GtDecl)){
				newe=eqleft>eright;
			}
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.GeDecl)){
				newe=eqleft>=eright;
			}	
			else if(Z3_is_eq_func_decl(c,tmp1.decl(),z3coding.DistinctDecl)){
				newe=eqleft!=eright;
			}
			if(Z3_is_eq_func_decl(c,formula.decl(),z3coding.NotDecl)){
				newe=!newe;
			}
			result->push_back(newe);
		}
			
		return result;
	}
	unique_ptr<vector<expr>> closureLtLet(expr lt1,expr ltOrLe2){
		unique_ptr<vector<expr>> result(new vector<expr>());
		expr lt1left=lt1.arg(0);
		expr lt1right=lt1.arg(1);
		expr lt2left=ltOrLe2.arg(0);
		expr lt2right=ltOrLe2.arg(1);
		if(z3coding.equal(lt1right,lt2left)){
			result->push_back(lt1left<lt2right);
		}
		if(z3coding.equal(lt1left,lt2right)){
			result->push_back(lt2left<lt1right);
		}
		return result;
	}
	unique_ptr<vector<expr>> closureLeLe(expr le1,expr le2){
		unique_ptr<vector<expr>> result(new vector<expr>());
		expr le1left=le1.arg(0);
		expr le1right=le1.arg(1);
		expr le2left=le2.arg(0);
		expr le2right=le2.arg(1);
		if(z3coding.equal(le1right,le2left)){
			result->push_back(le1left<=le2right);
		}
		if(z3coding.equal(le1left,le2right)){
			result->push_back(le2left<=le1right);
		}
		return result;
	}
	
	unique_ptr<vector<expr>> closure(expr e1,expr e2){
		e1=z3coding.eliminateNotInSimpleFormula(e1);
		e2=z3coding.eliminateNotInSimpleFormula(e2);
		e1=z3coding.eliminateGtAndGe(e1);
		e2=z3coding.eliminateGtAndGe(e2);
		//cout<<e1<<"::"<<e2<<std::endl;
		unique_ptr<vector<expr>> result(new vector<expr>());
		if(!e1.is_app()||!e2.is_app()) {
			std::cerr<<"UserSuppliedInstancOfRelation:closure: something is wrong!"<<std::endl;
			std::cerr<<"error info: e1 is: "<<e1<<", e2 is: "<<e2<<std::endl;
			return result;
		}
		
		if(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.EqDecl)){
			if(closureEqOptimizingStrategy(e1,e2)) return result;
			unique_ptr<vector<expr>> tmp=closureEq(e1,e2);
			z3coding.pushAToB(tmp.get(),result.get());
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.EqDecl)){
			if(closureEqOptimizingStrategy(e2,e1)) return result;
			unique_ptr<vector<expr>> tmp=closureEq(e2,e1);
			z3coding.pushAToB(tmp.get(),result.get());
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LtDecl)
		&&(Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LeDecl))){
			auto tmp=closureLtLet(e1,e2);
			z3coding.pushAToB(tmp.get(),result.get());
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LtDecl)
		&&(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LtDecl)||Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LeDecl))){
			auto tmp=closureLtLet(e2,e1);
			z3coding.pushAToB(tmp.get(),result.get());
		}
		else if(Z3_is_eq_func_decl(e1.ctx(),e1.decl(),z3coding.LeDecl)&&Z3_is_eq_func_decl(e1.ctx(),e2.decl(),z3coding.LeDecl)){
			auto tmp=closureLeLe(e1,e2);
			z3coding.pushAToB(tmp.get(),result.get());
		}
		return result;
	}
	
	/**
	 * @brief return formulas closure about Lt
	 * @param Lt
	 * @param formulas
	 * @return 
	 */
	/*FlowSet* closureLt(expr lt,FlowSet* formulas){
		if(!(lt.is_app()&&Z3_is_eq_func_decl(c,lt.decl(),z3coding.LtDecl))) {
			std::cerr<<"UserSuppliedInstancOfRelation:closureLt: something is wrong!"<<std::endl;
			return nullptr;
		}
		expr left=lt.arg(0);
		expr right=lt.arg(1);
		vector<Property*>* formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		expr ltleft=eq.arg(0);
		expr ltright=eq.arg(1);
		for(Property* p:*formulasVector){
			Formula* f=(Formula*)p;
			expr e=f->formula;
			if(z3coding.isSimpleFormula(e)){
				vector<expr> * tmp=closure(lt,e);
				add(tmp,out);
			}
		}
		out->Union(formulas);
		return out;
	}*/
	FlowSet* closure(expr e,FlowSet* formulas){
		if(!e.is_app()) {
			std::cerr<<"UserSuppliedInstancOfRelation:closure: something is wrong!"<<std::endl;
			std::cerr<<"error info: e is: "<<e<<std::endl;
			return nullptr;
		}
		auto formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		for(Property* p:*formulasVector){
			Formula* f=(Formula*)p;
			expr t=f->formula;
			if(z3coding.isSimpleFormula(t)){
				auto tmp=closure(e,t);
				add(tmp.get(),out);
			}
		}
		out->Union(formulas);
		return out;
	}
//	FlowSet* _closure(expr e,FlowSet* formulas){
//		if(!e.is_app()) {
//			std::cerr<<"UserSuppliedInstancOfRelation:closure: something is wrong!"<<std::endl;
//			std::cerr<<"error info: e is: "<<e<<std::endl;
//			return nullptr;
//		}
//		vector<Property*>* formulasVector=formulas->toVector();
//		FlowSet* out=new ValueListSetWithUniversalSet();
//		for(Property* p:*formulasVector){
//			Formula* f=(Formula*)p;
//			expr t=f->formula;
//			if(z3coding.isSimpleFormula(t)){
//				vector<expr> * tmp=closure(e,t);
//				add(tmp,out);
//			}
//		}
//		return out;
//	}
	FlowSet* powerClosure(expr e,FlowSet* formulas){
		if(!e.is_app()) {
			std::cerr<<"UserSuppliedInstancOfRelation:powerClosure: something is wrong!"<<std::endl;
			std::cerr<<"error info: e is: "<<e<<std::endl;
			return nullptr;
		}
		auto formulasVector=formulas->toVector();
		FlowSet* out=new ValueListSetWithUniversalSet();
		vector<expr> queue;
		queue.push_back(e);
		while(queue.size()!=0){
			expr cur=queue.back();queue.pop_back();
			//cout<<"cur is: "<<cur<<std::endl;
			for(Property* p:*formulasVector){
				Formula* f=(Formula*)p;
				expr t=f->formula;
				if(z3coding.isSimpleFormula(t)){
					auto tmp=closure(cur,t);
					for(expr t:*tmp){
						if(!isIn(t,&queue)&&!isIn(t,out)&&!isIn(t,formulas)&&!z3coding.equal(t,cur)){
							queue.push_back(t);
						}
					}
					add(tmp.get(),out);
				}
			}		
		}
		out->Union(formulas);
		return out;
	}
	bool isIn(expr f,vector<expr>* vs){
		return z3coding.isIn(f,vs);
	}
	bool isIn(expr f,FlowSet* B){
		auto BVector=B->toVector();
		auto vs=toExprs(BVector.get());
		return z3coding.isIn(f,vs.get());
	}
	/**
	 * @brief add A to B
	 * @param A
	 * @param B
	 * @return 
	 */
	void add(vector<expr> * A,FlowSet* B){
		for(expr e:*A){
			B->add(new Formula(e));
		}
	}
	void add(vector<expr> * A,vector<expr> *B){
		for(expr e:*A){
			if(!isIn(e,B)){
				B->push_back(e);
			}
		}
	}
public:
	UserSuppliedInstanceOfRelation(context &ctx,Z3Coding &z3c,MemoryUtil &memoryUtil,C2Z3* c2z3)
	:c(ctx),z3coding(z3c),mu(memoryUtil),c2z3Stmt(c2z3){}
	~UserSuppliedInstanceOfRelation(){}
	
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
					auto r=_simpleFormulaMeet(f1,f2);
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
		#ifdef _DEBUG
		/*cout<<"****************************************************************"<<std::endl;
		cout<<"stmt:: "<<z3coding.toString(stmt)<<std::endl;
		cout<<"Pre:: "<<toString(in)<<std::endl;*/
		#endif
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
			#ifdef _DEBUG
			//cout<<"stmtF:: "<<stmtF<<std::endl;
			#endif
			auto ign=tmp->toVector();
			tmp=Pos(stmtF,ign.get(),stmt,count);
		}
		out->Union(tmp);
		#ifdef _DEBUG
		/*cout<<"Pos:: "<<toString(out)<<std::endl;
		cout<<"****************************************************************"<<std::endl;
		cout<<"****************************************************************"<<std::endl;*/
		#endif
	}
	void flowThrouth(const clang::Stmt* stmt,int count,FlowSet* &in,FlowSet*&trueOut,FlowSet*&falseOut){
		#ifdef _DEBUG
		/*cout<<"****************************************************************"<<std::endl;
		cout<<"stmt:: "<<z3coding.toString(stmt)<<std::endl;
		cout<<"Pre:: "<<toString(in)<<std::endl;*/
		#endif
		vector<expr> * exprs=c2z3Stmt->getZ3Stmts(stmt);
		if(exprs==nullptr||count==-1){
			trueOut=new ValueListSetWithUniversalSet();
			falseOut=new ValueListSetWithUniversalSet();
			return;
		}
		
		vector<expr> *stmtFormulas=new vector<expr>();
		z3coding.pushAToB(exprs,stmtFormulas);
		
		FlowSet* tmp=in;
		if(count>=0&&count<(int)stmtFormulas->size()-1){
			expr stmtF=stmtFormulas->at(count);
			#ifdef _DEBUG
			/*cout<<"stmtF:: "<<stmtF<<std::endl;*/
			#endif
			auto ign=tmp->toVector();
			tmp=Pos(stmtF,ign.get(),stmt,count);
			trueOut->Union(tmp->clone());falseOut->Union(tmp->clone());
		}
		else if(count==(int)stmtFormulas->size()-1){
			expr stmtF=stmtFormulas->at(count);
			expr notStmtF=z3coding.eliminateNotInSimpleFormula(!stmtF);
			#ifdef _DEBUG
			/*cout<<"stmtF:: "<<stmtF<<std::endl;
			cout<<"notStmtF:: "<<notStmtF<<std::endl;*/
			#endif
			/*
			 * 如果根据当前状态不能走当前路径，那么直接将递性质下来
				这样做会存在不精确的问题。实际应该是将数据流设置为全集
			 * */
			 auto ign1=tmp->toVector();
			 auto ign2=toExprs(ign1.get());
			if(z3coding.satisfy(ign2.get(),stmtF)==check_result::unsat){
				trueOut->Union(tmp->clone());
			}
			else{
				FlowSet* truetmp=Pos(stmtF,ign1.get(),stmt,count);
				trueOut->Union(truetmp->clone());
			}
			auto ign3=tmp->toVector();
			auto ign4=toExprs(ign3.get());
			if(z3coding.satisfy(ign4.get(),notStmtF)==check_result::unsat){
				falseOut->Union(tmp->clone());
			}
			else{
				FlowSet* falsetmp=Pos(notStmtF,ign3.get(),stmt,count);
				falseOut->Union(falsetmp->clone());
			}
			/*FlowSet* truetmp=Pos(stmtF,tmp->toVector(),stmt,count);
			trueOut->Union(truetmp->clone());
			FlowSet* falsetmp=Pos(notStmtF,tmp->toVector(),stmt,count);
			falseOut->Union(falsetmp->clone());*/
		}
		else{
			trueOut->Union(tmp->clone());falseOut->Union(tmp->clone());
		}
		#ifdef _DEBUG
		/*cout<<"truePos:: "<<toString(trueOut)<<std::endl;
		cout<<"falsePos:: "<<toString(falseOut)<<std::endl;
		cout<<"****************************************************************"<<std::endl;
		cout<<"****************************************************************"<<std::endl;*/
		#endif 
		
	}
	bool isSimpleProperty(Formula* f){
		return z3coding.isSimpleFormula(f->formula);
	}
	bool partialOrderRelation(Formula* f1,Formula* f2){
		expr e1= f1->formula;
		expr e2= f2->formula;
		//return z3coding.equal(e1,e2);
		return partialOrderRelation_SimpleFormula_SimpleFormula(e1,e2);
	}
	//whether f1 can implies f2
	bool partialOrderRelation_SimpleFormula_SimpleFormula(expr f1,expr f2){
			expr e1=f1;
			expr e2=f2;
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.EqDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						return false;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LtDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LtDecl)&&Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.LeDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(z3coding.isNe(e2)){
						return false;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				if(z3coding.isNe(e1)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.DistinctDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
			}

			return false;

	}
	
	/*bool _partialOrderRelation_SimpleFormula_SimpleFormula(expr f1,expr f2){
			expr e1=f1;
			expr e2=f2;
			e1=z3coding.eliminateNotInSimpleFormula(e1);
			e2=z3coding.eliminateNotInSimpleFormula(e2);
			e1=z3coding.eliminateGtAndGe(e1);
			e2=z3coding.eliminateGtAndGe(e2);
			unsigned e1hash=e1.decl().hash();
			unsigned e2hash=e2.decl().hash();
			unsigned Eqhash=z3coding.EqDecl.hash();
			unsigned Lthash=z3coding.LtDecl.hash();
			unsigned Lehash=z3coding.LeDecl.hash();
			unsigned Distincthash=z3coding.DistinctDecl.hash();
			
			if(e1.is_app()&&e2.is_app()){
				//if(e1.decl().name().str()=="="&&e2.decl().name().str()=="="){
				if(e1hash==Eqhash){
					if(e2hash==Eqhash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						return false;
					}
					//else if(e1.decl().name().str()=="="&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="=" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						return false;
					}
				}
				//if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="="){
				if(e1hash==Lthash){
					if(e2hash==Eqhash){
						return false;
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"&&e2.decl().name().str()=="<="){
					if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<"  && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="="){
				else if(e1hash==Lehash){
					if(e2hash==Eqhash){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<"){
					else if(e2hash==Lthash){
						return false;
					}
					//else if(e1.decl().name().str()=="<="&&e2.decl().name().str()=="<="){
					else if(e2hash==Lehash){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="<=" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						return false;
					}
					//else if(e1.decl().name().str()=="<=" && e2.decl().name().str()=="distinct"){
					else if(e2hash==Distincthash){
						return false;
					}
				}
				//if(isNe(e1)&&e2.decl().name().str()=="="){
				if(z3coding.isNe(e1)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(isNe(e1)&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(isNe(e1) && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(isNe(e1) && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0).arg(0);expr e1r=e1.arg(0).arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
				//if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="="){
				if(Z3_is_eq_func_decl(c,e1.decl(),z3coding.DistinctDecl)){
					if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.EqDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LtDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct"&&e2.decl().name().str()=="<="){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.LeDecl)){
						return false;
					}
					//else if(e1.decl().name().str()=="distinct" && isNe(e2)){
					else if(z3coding.isNe(e2)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0).arg(0);expr e2r=e2.arg(0).arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
					//else if(e1.decl().name().str()=="distinct" && e2.decl().name().str()=="distinct"){
					else if(Z3_is_eq_func_decl(c,e2.decl(),z3coding.DistinctDecl)){
						expr e1l=e1.arg(0);expr e1r=e1.arg(1);
						expr e2l=e2.arg(0);expr e2r=e2.arg(1);
						if(z3coding.equal(e1l,e2l)&&z3coding.equal(e1r,e2r)){
							return true;
						}
						else if(z3coding.equal(e1l,e2r)&&z3coding.equal(e1r,e2l)){
							return true;
						}
						else{
							return false;
						}
					}
				}
			}

			return false;

	}*/
	std::string toString(FlowSet* in){
		if(in->isUniversalSet()){
			return "UniversalSet";
		}
		auto ign=flowSetToExprSet(in);
		return z3coding.toString(ign.get());
	}
	unique_ptr<vector<expr>> flowSetToExprSet(FlowSet * flowSet){
		auto propertySet=flowSet->toVector();
		unique_ptr<vector<expr>> exprSet(new vector<expr>());
		for(Property* p: *propertySet){
			Formula *f=(Formula *)p;
			exprSet->push_back(f->formula);
		}
		return exprSet;
	}
};
#endif