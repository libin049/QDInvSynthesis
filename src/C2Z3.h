#ifndef _C2Z3_H
#define _C2Z3_H
class C2Z3{
private:
	clang::CFG* cfg;
	Z3Coding &z3coding;
	vector<expr>* localDeclVariables;
	void translate(){
		list<CFGBlock*> queue;
		initAndSortWorkList(queue);
		while(!queue.empty()){
			CFGBlock* n=queue.front();queue.pop_front();
			vector<expr>* z3exprStmts=translate(n);
			mapToBlocks[n]=z3exprStmts;
		}
	}
	
	
	
	vector<expr>* translate(CFGBlock* n){
		vector<expr>* result=new vector<expr>();
		Stmt* T=nullptr;
		if(n->succ_size()==2){
			T=n->getTerminatorCondition();
		}
		#ifdef _DEBUG
//		cout<<"BlockID is:"<< n->getBlockID()<<std::endl;
		#endif
		unsigned count=0;
		for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
			CFGElement element=(*iterblock);
			if(element.getKind()==CFGElement::Kind::Statement){
				const Stmt* it=((CFGStmt*)&element)->getStmt();
				/*std::cout<<"it is "<<z3coding.toString(it)<<std::endl;
				if(z3coding.toString(it)=="bzerr"){
					std::cout<<"it is "<<z3coding.toString(it)<<std::endl;
				}*/
				stmtToZ3Exprs.insert({it,new vector<expr>()});
				vector<expr> * exprs=z3coding.clangStmtToZ3Expr(it);
				if(exprs==nullptr){
					std::cerr<<"C2Z3::translate(n): something is wrong 1! "<<std::endl;
					std::cerr<<"error info: it is "<<z3coding.toString(it)<<std::endl;
					return nullptr;
				}
				vector<expr> *stmtFormulas=z3coding.boolSortFiltering(exprs);
				#ifdef _DEBUG
//					cout<<"exprs size:"<< exprs->size()<<std::endl;
//					cout<<"T is null?"<< (T==nullptr)<<std::endl;
//					cout<<"it==T?"<< (it==T)<<std::endl;
//					cout<<"n->size():"<< n->size()<<std::endl;
//					cout<<"n->succ_size():"<< n->succ_size()<<std::endl;
				#endif
				if((n->succ_size()==2||T!=nullptr)&&exprs->size()>0&&(it==T||(n->size()>0&&count==n->size()-1))){
					if(exprs->at(exprs->size()-1).is_int()){
						if(exprs->size()>=1) {
							stmtFormulas->push_back(exprs->at(exprs->size()-1)!=0);
						}
						else{
							std::cerr<<"translate: something is wrong 2! "<<std::endl;	
							return nullptr;
						}
					}
				}
				z3coding.pushAToB(stmtFormulas,stmtToZ3Exprs[it]);
				z3coding.pushAToB(stmtFormulas,result);
				count++;
			}
		}
		return result;
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
	void initAndSortWorkList(list<CFGBlock*> &worklist){
		CFGBlock &entry=cfg->getEntry();
		list<CFGBlock*> queue;
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
public:
	map<CFGBlock*, vector<expr>*> mapToBlocks; // CGFBlock's In dataflow infomation
	map<const Stmt*, vector<expr>*> stmtToZ3Exprs; 
	C2Z3(clang::CFG* cfg,Z3Coding &z3code):z3coding(z3code){
		this->cfg=cfg;
		for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
			CFGBlock* block=*iter;
			mapToBlocks.insert({block,new vector<expr>()});
		}
		translate();
	}
	C2Z3(clang::CFG* cfg,Z3Coding &z3code,const map<CFGBlock*, vector<expr>* > newmapToBlocks,
	const map<const Stmt*, vector<expr>* > newstmtToZ3Exprs)
	:z3coding(z3code){
		localDeclVariables=nullptr;
		this->cfg=cfg;
		for(std::pair<CFGBlock*, vector<expr>*> p: newmapToBlocks){
			vector<expr>* nv=new vector<expr>();
			if(p.second==nullptr){
				nv=nullptr;
			}
			else{
				z3coding.pushAToB(p.second,nv);
			}
			this->mapToBlocks.insert({p.first,nv});
		}
		for(std::pair<const Stmt*, vector<expr>*> p: newstmtToZ3Exprs){
			vector<expr>* nv=new vector<expr>();
			if(p.second==nullptr){
				nv=nullptr;
			}
			else{
				z3coding.pushAToB(p.second,nv);
			}
			this->stmtToZ3Exprs.insert({p.first,nv});
		}
	}
	void print(){
		list<CFGBlock*> queue;
		initAndSortWorkList(queue);
		while(!queue.empty()){
			CFGBlock* n=queue.front();queue.pop_front();
			std::cout <<"--------[B"<< n->getBlockID ()<<"]" << ":--------"<<std::endl; 
			std::cout<<toString(mapToBlocks[n])<<std::endl;
		}
		/*//--------------------id order--------------
		for(CFG::iterator iter=cfg->begin();iter!=cfg->end();++iter){
			CFGBlock* n=*iter;
			std::cout <<"--------[B"<< n->getBlockID ()<<"]" << ":--------"<<std::endl; 
			std::cout<<toString(mapToBlocks[n])<<std::endl;
		}*/
	}
	vector<expr>* getZ3Stmts(const Stmt* stmt){
		if(stmtToZ3Exprs.count(stmt)>0){
			return stmtToZ3Exprs.at(stmt);
		}
		return nullptr;
	}
	vector<expr>* getLocalDeclVariables(){
		if(localDeclVariables==nullptr){
			localDeclVariables=new vector<expr>(); 
			list<CFGBlock*> queue;
			initAndSortWorkList(queue);
			z3coding.localDeclVariables_tmp=new vector<expr>();
			while(!queue.empty()){
				CFGBlock* n=queue.front();queue.pop_front();
				for(CFGBlock::iterator iterblock=n->begin();iterblock!=n->end();++iterblock){
					CFGElement element=(*iterblock);
					if(element.getKind()==CFGElement::Kind::Statement){
						const Stmt* it=((CFGStmt*)&element)->getStmt();
						z3coding.localDeclVariables_tmp->clear();
						//cout<<"it is 111:"<<z3coding.toString(it)<<std::endl;
						/*if(z3coding.toString(it)=="nIbuf = fread(ibuf, sizeof(UChar), 5000, stream)"){
							cout<<"it is 111:"<<z3coding.toString(it)<<std::endl;
						}*/
						z3coding.clangStmtToZ3Expr(it);
						//cout<<"it is 222:"<<z3coding.toString(it)<<std::endl;
						z3coding.pushAToB(z3coding.localDeclVariables_tmp,localDeclVariables);
					}
				}
			}
			z3coding.localDeclVariables_tmp=nullptr;
		}
		return localDeclVariables;
	}
};
#endif