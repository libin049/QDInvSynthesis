 char *strcpy(char *dest, const char *src)
 {
	      //∀k.k ∈ [dest@pre,1,dest),phi
		  //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		 //tmp = dest;
		 //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
         while( 
			dest:=dest+1;
			//∀k.k ∈ [dest@pre,1,dest-1),phi
		    //∀k.k ∈ [src@pre,1,src),phi
			src:=src+1;
			//∀k.k ∈ [dest@pre,1,dest-1),phi
		    //∀k.k ∈ [src@pre,1,src-1),phi
			der_pointer(dest-1):=der_pointer(src-1);
			//∀k.k ∈ [dest@pre,1,dest-1),phi
		    //∀k.k ∈ [src@pre,1,src-1),phi
			//der_pointer(dest-1)=der_pointer(src-1);
			::note: der_pointer(dest-1)=der_pointer(src-1) always generates property:der_pointer(dest-1)=der_pointer(src-1)
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(src-1);
			//∀k.k ∈ [src@pre,1,src),der_pointer(dest-1)=der_pointer(k-1);
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(f(k));
			der_pointer(src-1)!=0;
			//∀k.k ∈ [dest@pre,1,dest-1),phi
		    //∀k.k ∈ [src@pre,1,src-1),phi
			//der_pointer(dest-1)=der_pointer(src-1);
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(src-1);
			//∀k.k ∈ [src@pre,1,src),der_pointer(dest-1)=der_pointer(k-1);
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(f(k));
			//der_pointer(src-1)!=0;
			//der_pointer(dest-1)!=0
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
			//∀k.k ∈ [src@pre,1,src),der_pointer(k-1)!=0;
			)
                 /* nothing */;
		 return tmp;
 }




char *strcpy(char *dest, const char *src)
 {
	      //∀k.k ∈ [dest@pre,1,dest),phi
		  //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		   //∀k.k ∈ [dest@pre,1,dest),phi
		   //∀k.k ∈ [src@pre,1,src),phi
		   //tmp = dest;
		//merge
		   //∀k.k ∈ [dest@pre,1,dest-1),phi
		    //∀k.k ∈ [src@pre,1,src-1),phi
			//der_pointer(dest-1)=der_pointer(src-1);
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(src-1);
			//∀k.k ∈ [src@pre,1,src),der_pointer(dest-1)=der_pointer(k-1);
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(f(k));
			//der_pointer(src-1)!=0;
			//der_pointer(dest-1)!=0
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
			//∀k.k ∈ [src@pre,1,src),der_pointer(k-1)!=0;
			
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(src-1);
		//∀k.k ∈ [src@pre,1,src),der_pointer(dest-1)=der_pointer(k-1);
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)=der_pointer(f(k));
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
		//∀k.k ∈ [src@pre,1,src),der_pointer(k-1)!=0;	
		 while( 
			dest:=dest+1;
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)=der_pointer(src-1);
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)=der_pointer(f(k));
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //∀k.k ∈ [src@pre,1,src),der_pointer(k-1)!=0;	
			src:=src+1;
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)=der_pointer(f(k));
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //∀k.k ∈ [src@pre,1,src-1),der_pointer(k-1)!=0;	
			der_pointer(dest-1):=der_pointer(src-1);
			::check der_pointer(dest-1) isin λk.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)   no 
			::check der_pointer(dest-1) isin λk.k ∈ [dest@pre,1,dest-1),der_pointer(f(k))  may
			::check der_pointer(dest-1) isin λk.k ∈ [src@pre,1,src-1),der_pointer(k-1)     may
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //der_pointer(dest-1)=der_pointer(src-1);
			der_pointer(src-1)!=0;
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //der_pointer(dest-1)=der_pointer(src-1);
		   //der_pointer(src-1)!=0
		   //der_pointer(src-1)!=0
		   //∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
			)
                 /* nothing */;
		 return tmp;
 }


char *strcpy(char *dest, const char *src)
 {
	      //∀k.k ∈ [dest@pre,1,dest),phi
		  //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
          //∀k.k ∈ [dest@pre,1,dest),phi
		   //∀k.k ∈ [src@pre,1,src),phi
		   //tmp = dest;
		//merge
		  //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //der_pointer(dest-1)=der_pointer(src-1);
		   //der_pointer(src-1)!=0
		   //der_pointer(src-1)!=0
		   //∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
			
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
		 while( 
			dest:=dest+1;
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
			src:=src+1;
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
			der_pointer(dest-1):=der_pointer(src-1);
			::check der_pointer(dest-1) isin λk.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)   no 
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //der_pointer(dest-1)=der_pointer(src-1);
			der_pointer(src-1)!=0;
		   //∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k-1)!=0;
		   //der_pointer(dest-1)=der_pointer(src-1);
		   //der_pointer(src-1)!=0
		   //der_pointer(src-1)!=0
		   //∀k.k ∈ [dest@pre,1,dest),der_pointer(k-1)!=0;
			)
                 /* nothing */;
		 return tmp;
 }



char *strncpy(char *dest, const char *src, size_t count)
 {
	     //∀k.k ∈ [count@pre,1,count),phi
		  //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		  //∀k.k ∈ [count@pre,1,count),phi
		  //∀k.k ∈ [src@pre,1,src),phi
		  //∀k.k ∈ [dest,1,tmp),phi
         while (count) {
			 //∀k.k ∈ [count@pre,1,count),phi
		     //∀k.k ∈ [src@pre,1,src),phi
		     //∀k.k ∈ [dest,1,tmp),phi
			 //count!=0
				   der_pointer(tmp):= der_pointer(src)
				    //∀k.k ∈ [count@pre,1,count),phi
					//∀k.k ∈ [src@pre,1,src),phi
					//∀k.k ∈ [dest,1,tmp),phi
					//count!=0
					//der_pointer(tmp)= der_pointer(src)
					//∀k.k ∈ [src@pre,1,src+1),der_pointer(tmp)= der_pointer(k)
					//∀k.k ∈ [dest,1,tmp+1),der_pointer(k)= der_pointer(src)
                 if ( der_pointer(src)!= 0)
						//∀k.k ∈ [count@pre,1,count),phi
						//∀k.k ∈ [src@pre,1,src),phi
						//∀k.k ∈ [dest,1,tmp),phi
						//count!=0
						//der_pointer(tmp)= der_pointer(src)
						//der_pointer(src)!= 0
						//der_pointer(tmp)!=0
						//∀k.k ∈ [src@pre,1,src+1),der_pointer(tmp)= der_pointer(k)
						//∀k.k ∈ [dest,1,tmp+1),der_pointer(k)= der_pointer(src)
						//∀k.k ∈ [src@pre,1,src+1),der_pointer(k)!= 0
						//∀k.k ∈ [dest,1,tmp+1),der_pointer(k)!=0
                         src++;
						//∀k.k ∈ [count@pre,1,count),phi
						//∀k.k ∈ [src@pre,1,src-1),phi
						//∀k.k ∈ [dest,1,tmp),phi
						//count!=0
						//der_pointer(tmp)!=0
						//∀k.k ∈ [src@pre,1,src),der_pointer(tmp)= der_pointer(k)
						//∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
						//∀k.k ∈ [dest,1,tmp+1),der_pointer(k)!=0
						
						
						 //∀k.k ∈ [count@pre,1,count),phi
						 //∀k.k ∈ [src@pre,1,src),phi
						 //∀k.k ∈ [dest,1,tmp),phi
						 //count!=0
						 //der_pointer(tmp)= der_pointer(src)
						//der_pointer(src)= 0
						//der_pointer(tmp)= 0
						//∀k.k ∈ [src@pre,1,src+1),der_pointer(tmp)= der_pointer(k)
						//∀k.k ∈ [dest,1,tmp+1),der_pointer(k)= der_pointer(src)
						//∀k.k ∈ [src@pre,1,src+1),der_pointer(k)=0
						//∀k.k ∈ [dest,1,tmp+1),der_pointer(k)=0
					//merge
						 //∀k.k ∈ [count@pre,1,count),phi
						 //∀k.k ∈ [src@pre,1,src-1),phi
						 //∀k.k ∈ [dest,1,tmp),phi
						 //count!=0
						 //der_pointer(tmp)!=0
						 //∀k.k ∈ [src@pre,1,src),der_pointer(tmp)= der_pointer(k)
						 //∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
						 //∀k.k ∈ [dest,1,tmp+1),der_pointer(k)!=0	
					 
					 //∀k.k ∈ [count@pre,1,count),phi
					 //∀k.k ∈ [dest,1,tmp),phi	
					 //count!=0
					 //∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
					 
                 tmp++;
						//∀k.k ∈ [count@pre,1,count),phi
						//∀k.k ∈ [dest,1,tmp-1),phi	
						//count!=0
						//∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
                 count--;
						//∀k.k ∈ [count@pre,1,count-1),phi
						//∀k.k ∈ [dest,1,tmp-1),phi	
						//∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
         }
         return dest;
 }



char *strncpy(char *dest, const char *src, size_t count)
 {
	     //∀k.k ∈ [count@pre,1,count),phi
		  //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		  //∀k.k ∈ [count@pre,1,count),phi
		  //∀k.k ∈ [src@pre,1,src),phi
		  //∀k.k ∈ [dest,1,tmp),phi
		//merge
			//∀k.k ∈ [count@pre,1,count-1),phi
			//∀k.k ∈ [dest,1,tmp-1),phi	
			//∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
		
		//∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
         while (count) {
			 //∀k.k ∈ [src@pre,1,src),der_pointer(k)!= 0
			 //count!=0
			 ::check der_pointer(tmp) isin λk.k ∈ [src@pre,1,src),der_pointer(k)   may 
				   der_pointer(tmp):= der_pointer(src)
				   //der_pointer(tmp)= der_pointer(src)
				   //count!=0
                 if ( der_pointer(src)!= 0)
					 //count!=0
					 //der_pointer(src)!= 0
					 //der_pointer(tmp)= der_pointer(src)
					      src++;
					//count!=0	
						
						 //count!=0
						 //der_pointer(tmp)= der_pointer(src)
						//der_pointer(src)= 0
						//der_pointer(tmp)= 0
					//merge
						 //count!=0
					 
					 //count!=0
                 tmp++;
						//count!=0
                 count--;
         }
         return dest;
 }
we get nothing from strncpy


char *strcat(char *dest, const char *src)
 {
	     //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		 //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
		 //tmp = dest
         while (der_pointer(dest)!=0)
			//∀k.k ∈ [dest@pre,1,dest),phi
			//∀k.k ∈ [src@pre,1,src),phi
			//tmp = dest
			//der_pointer(dest)!=0
			//∀k.k ∈ [dest@pre,1,dest+1),der_pointer(k)!=0
                 dest++;
			//∀k.k ∈ [dest@pre,1,dest-1),phi
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
		 while(
			dest=dest+1;
			src=src+1;
			der_pointer(dest-1)=der_pointer(src-1);
			der_pointer(src-1)!=0;
		 );
		 return tmp;
 }


char *strcat(char *dest, const char *src)
 {
	     //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		 //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
		 //tmp = dest
		//merge
		 //∀k.k ∈ [dest@pre,1,dest-1),phi
		 //∀k.k ∈ [src@pre,1,src),phi
		 //∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
		 
		//∀k.k ∈ [src@pre,1,src),phi
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
         while (der_pointer(dest)!=0)
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
			//der_pointer(dest)!=0
			//∀k.k ∈ [dest@pre,1,dest+1),der_pointer(k)!=0 
                 dest++;
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
		
		//∀k.k ∈ [src@pre,1,src),phi
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
		//der_pointer(dest)=0
		while(
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
			//der_pointer(dest)=0
			dest:=dest+1;
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			src:=src+1;
			//∀k.k ∈ [src@pre,1,src-1),phi
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			der_pointer(dest-1):=der_pointer(src-1);
			//∀k.k ∈ [src@pre,1,src-1),phi
			::check der_pointer(dest-1) isin λk.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0  no
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			//der_pointer(dest-1)=der_pointer(src-1);
			der_pointer(src-1)!=0;
			//∀k.k ∈ [src@pre,1,src-1),phi
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			//der_pointer(dest-1)=der_pointer(src-1);
			//der_pointer(src-1)!=0
			//der_pointer(dest-1)!=0
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
			//∀k.k ∈ [src@pre,1,src),der_pointer(k)!=0
			
		 );
		 return tmp;
 }


char *strcat(char *dest, const char *src)
 {
	     //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
         tmp = dest;
		 //∀k.k ∈ [dest@pre,1,dest),phi
		 //∀k.k ∈ [src@pre,1,src),phi
		 //tmp = dest
		//merge
		 //∀k.k ∈ [dest@pre,1,dest-1),phi
		 //∀k.k ∈ [src@pre,1,src),phi
		 //∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
		 
		//∀k.k ∈ [src@pre,1,src),phi
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
         while (der_pointer(dest)!=0)
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
			//der_pointer(dest)!=0
			//∀k.k ∈ [dest@pre,1,dest+1),der_pointer(k)!=0 
                 dest++;
			//∀k.k ∈ [src@pre,1,src),phi
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
		
		//∀k.k ∈ [src@pre,1,src),phi
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0 
		//der_pointer(dest)=0
	//merge
		//∀k.k ∈ [src@pre,1,src-1),phi
		//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
		//der_pointer(dest-1)=der_pointer(src-1);
		//der_pointer(src-1)!=0
		//der_pointer(dest-1)!=0
		//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
		//∀k.k ∈ [src@pre,1,src),der_pointer(k)!=0
	
	//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
	//∀k.k ∈ [src@pre,1,src),der_pointer(k)!=0
		while(
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
			//∀k.k ∈ [src@pre,1,src),der_pointer(k)!=0
			dest:=dest+1;
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			//∀k.k ∈ [src@pre,1,src),der_pointer(k)!=0
			src:=src+1;
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			//∀k.k ∈ [src@pre,1,src-1),der_pointer(k)!=0
			der_pointer(dest-1):=der_pointer(src-1);
			::check der_pointer(dest-1) isin λk.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0  no
			::check der_pointer(dest-1) isin λk.k ∈ [src@pre,1,src-1),der_pointer(k)!=0		may
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			//der_pointer(dest-1)=der_pointer(src-1);
			der_pointer(src-1)!=0;
			//∀k.k ∈ [dest@pre,1,dest-1),der_pointer(k)!=0
			//der_pointer(dest-1)=der_pointer(src-1);
			//der_pointer(src-1)!=0
			//der_pointer(dest-1)!=0
			//∀k.k ∈ [dest@pre,1,dest),der_pointer(k)!=0
		 );
		 return tmp;
 }



char *strncat(char *dest, const char *src, size_t count)
 {
         tmp = dest;
         if (count) {	 
                  while (der_pointer(dest)!=0)
                          dest++;
					 while (
						dest=dest+1;
						src=src+1;
						der_pointer(dest-1):=der_pointer(src-1);
						der_pointer(src-1)!=0;
					 ){
                         if (--count == 0) {
                                 der_pointer(dest)!='\0';
                                 break;
                         }
					 }
         }
         return tmp;
 }

for strncat, we may get the same thing as strcat

 
 
 int strcmp(const char *cs, const char *ct)
 {
		  //∀k.k ∈ [cs@pre,1,cs),phi
		  //∀k.k ∈ [ct@pre,1,ct),phi
         unsigned char c1, c2;
		  const char *cs, const char *ct;
		  //∀k.k ∈ [cs@pre,1,cs),phi
		  //∀k.k ∈ [ct@pre,1,ct),phi
         while (1) {
			 //∀k.k ∈ [cs@pre,1,cs),phi
			 //∀k.k ∈ [ct@pre,1,ct),phi
				  cs++;
			 //∀k.k ∈ [cs@pre,1,cs-1),phi
			 //∀k.k ∈ [ct@pre,1,ct),phi
				  c1=der_pointer(cs-1);
			 //∀k.k ∈ [cs@pre,1,cs-1),phi
			 //∀k.k ∈ [ct@pre,1,ct),phi
			 //c1=der_pointer(cs-1)
			 //∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
				  ct++;
			 //∀k.k ∈ [cs@pre,1,cs-1),phi
			 //∀k.k ∈ [ct@pre,1,ct-1),phi
			 //c1=der_pointer(cs-1)
			 //∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
				  c2=der_pointer(ct-1);
			 //∀k.k ∈ [cs@pre,1,cs-1),phi
			 //∀k.k ∈ [ct@pre,1,ct-1),phi
			 //c1=der_pointer(cs-1)
			 //∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
			 //c2=der_pointer(ct-1)
			 //∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
                 if (c1 != c2)
					//∀k.k ∈ [cs@pre,1,cs-1),phi
					//∀k.k ∈ [ct@pre,1,ct-1),phi
					//c1=der_pointer(cs-1)
					//∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
					//c2=der_pointer(ct-1)
					//∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
					//c1 != c2
					//der_pointer(ct-1)!=der_pointer(cs-1)
					//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(f(k))!=der_pointer(k-1)
                         return c1 < c2 ? -1 : 1;
                 //∀k.k ∈ [cs@pre,1,cs-1),phi
				  //∀k.k ∈ [ct@pre,1,ct-1),phi
				  //c1=der_pointer(cs-1)
				  //∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
				  //c2=der_pointer(ct-1)
				  //∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
				  //c1=c2
				  //der_pointer(ct-1)=der_pointer(cs-1)
					if (!c1)
						//∀k.k ∈ [cs@pre,1,cs-1),phi
						//∀k.k ∈ [ct@pre,1,ct-1),phi
						//c1=der_pointer(cs-1)
						//∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
						//c2=der_pointer(ct-1)
						//∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
						//c1=0
						//der_pointer(cs-1)=0
						//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)=0
						//c1=c2
						//der_pointer(ct-1)=der_pointer(cs-1)
						//der_pointer(ct-1)=0
						//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=0
						//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
                         break;
				  //∀k.k ∈ [cs@pre,1,cs-1),phi
				  //∀k.k ∈ [ct@pre,1,ct-1),phi
				  //c1=der_pointer(cs-1)
				  //∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
				  //c2=der_pointer(ct-1)
				  //∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
				  //c1!=0
				  //∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
				  //c1=c2
				  //c2!=0
				  //∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				  //der_pointer(ct-1)=der_pointer(cs-1)
				  //∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
         }
         return 0;
 }


 int strcmp(const char *cs, const char *ct)
 {
		  //∀k.k ∈ [cs@pre,1,cs),phi
		  //∀k.k ∈ [ct@pre,1,ct),phi
         unsigned char c1, c2;
		  const char *cs, const char *ct;
		  //∀k.k ∈ [cs@pre,1,cs),phi
		  //∀k.k ∈ [ct@pre,1,ct),phi
	//merge
		  //∀k.k ∈ [cs@pre,1,cs-1),phi
		  //∀k.k ∈ [ct@pre,1,ct-1),phi
		  //c1=der_pointer(cs-1)
		  //∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
		  //c2=der_pointer(ct-1)
		  //∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
		  //c1!=0
		  //∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
		  //c1=c2
		  //c2!=0
		  //∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
		  //der_pointer(ct-1)=der_pointer(cs-1)
		  //∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
	
	
	//∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
	//∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
	//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
	//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
	//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
         while (1) {
				//∀k.k ∈ [cs@pre,1,cs),c1=der_pointer(k-1)
				//∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
				//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				  cs++;
				//∀k.k ∈ [cs@pre,1,cs-1),c1=der_pointer(k-1)
				//∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				  c1=der_pointer(cs-1);
				  ::check::c1 isIn λk.k ∈ [cs@pre,1,cs),der_pointer(k-1)
				  ::check::c1 isIn λk.k ∈ [ct@pre,1,ct),der_pointer(k-1)
				//∀k.k ∈ [ct@pre,1,ct),c2=der_pointer(k-1)
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				  ct++;
				//∀k.k ∈ [ct@pre,1,ct-1),c2=der_pointer(k-1)
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				  c2=der_pointer(ct-1);
				  ::c1 isIn λk.k ∈ [cs@pre,1,cs),der_pointer(k-1)
				  ::....
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
                 if (c1 != c2)
					//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
					//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
					//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
					//c2=der_pointer(ct-1)
					//c1=der_pointer(cs-1)
					//c1 != c2
					//der_pointer(ct-1)!=der_pointer(cs-1)
                         return c1 < c2 ? -1 : 1;
					
					
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
				//c1=c2
				//der_pointer(ct-1)=der_pointer(cs-1)
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
					if (!c1)
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
				//c1=c2
				//der_pointer(ct-1)=der_pointer(cs-1)
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				//der_pointer(ct-1)=0
				//der_pointer(cs-1)=0
                         break;
				
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
				//c1=c2
				//der_pointer(ct-1)=der_pointer(cs-1)
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				//der_pointer(ct-1)!=0
				//der_pointer(cs-1)!=0
				//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				
         }
         return 0;
 }



int strcmp(const char *cs, const char *ct)
 {
		  //∀k.k ∈ [cs@pre,1,cs),phi
		  //∀k.k ∈ [ct@pre,1,ct),phi
         unsigned char c1, c2;
		  const char *cs, const char *ct;
		  //∀k.k ∈ [cs@pre,1,cs),phi
		  //∀k.k ∈ [ct@pre,1,ct),phi
	//merge
		 //∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
		 //∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
		//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
		//c2=der_pointer(ct-1)
		//c1=der_pointer(cs-1)
		//c1=c2
		//der_pointer(ct-1)=der_pointer(cs-1)
		//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
		//der_pointer(ct-1)!=0
		//der_pointer(cs-1)!=0
		//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
		//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
	
	
	//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
	//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
	//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
         while (1) {
				//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				  cs++;
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				  c1=der_pointer(cs-1);
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				  ct++;
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				  c2=der_pointer(ct-1);
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
                 if (c1 != c2)
					//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
					//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
					//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
					//c2=der_pointer(ct-1)
					//c1=der_pointer(cs-1)
					//c1 != c2
					//der_pointer(ct-1)!=der_pointer(cs-1)
                         return c1 < c2 ? -1 : 1;
					
					
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
				//c1=c2
				//der_pointer(ct-1)=der_pointer(cs-1)
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
					if (!c1)
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
				//c1=c2
				//der_pointer(ct-1)=der_pointer(cs-1)
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				//der_pointer(ct-1)=0
				//der_pointer(cs-1)=0
                         break;
				
				//∀k.k ∈ [cs@pre,1,cs-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct-1),der_pointer(k-1)=der_pointer(f(k))
				//c2=der_pointer(ct-1)
				//c1=der_pointer(cs-1)
				//c1=c2
				//der_pointer(ct-1)=der_pointer(cs-1)
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)=der_pointer(f(k))
				//der_pointer(ct-1)!=0
				//der_pointer(cs-1)!=0
				//∀k.k ∈ [cs@pre,1,cs),der_pointer(k-1)!=0
				//∀k.k ∈ [ct@pre,1,ct),der_pointer(k-1)!=0
				
         }
         return 0;
 }


int strncmp(const char *cs, const char *ct, size_t count)
 {
         unsigned char c1, c2;
			
         while (count) {
                 c1 = *cs++;
                 c2 = *ct++;
                 if (c1 != c2)
                         return c1 < c2 ? -1 : 1;//(= _ret (ite (< c1 c2) (- 1) 1));
                 if (!c1)
                         break;
                 count--;
         }
         return 0;
 }

for strncmp, we should get same properties as strcmp

char *strchrnul(const char *s, int c)
 {	
		  //∀k.k ∈ [s@pre,1,s),phi
         while (der_pointer(s)!=0 && der_pointer(s) != (char)c)
			 //∀k.k ∈ [s@pre,1,s),phi
			 //der_pointer(s)!=0
			 //der_pointer(s)!=c
			 //∀k.k ∈ [s@pre,1,s+1),der_pointer(k)!=0
			 //∀k.k ∈ [s@pre,1,s+1),der_pointer(k)!=c
                 s++;
			//∀k.k ∈ [s@pre,1,s-1),phi
			 //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=0
			 //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=c
         return (char *)s;
 }


char *strchrnul(const char *s, int c)
 {	
		  //∀k.k ∈ [s@pre,1,s),phi
	//merge
		  //∀k.k ∈ [s@pre,1,s-1),phi
		  //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=0
		  //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=c
	
	//∀k.k ∈ [s@pre,1,s),der_pointer(k)!=0
	//∀k.k ∈ [s@pre,1,s),der_pointer(k)!=c
         while (der_pointer(s)!=0 && der_pointer(s) != (char)c)
		  //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=0
		  //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=c
		  //der_pointer(s)!=0
		  //der_pointer(s)!=c
		  //∀k.k ∈ [s@pre,1,s+1),der_pointer(k)!=0
		  //∀k.k ∈ [s@pre,1,s+1),der_pointer(k)!=c
			        s++;
		  //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=0
		  //∀k.k ∈ [s@pre,1,s),der_pointer(k)!=c	
         return (char *)s;
 }





char *strrchr(const char *s, int c)
 {
		//∀k.k ∈ [s@pre,1,s),phi
         const char *last = 0;
		 //∀k.k ∈ [s@pre,1,s),phi
		 //last=0
		 
         do {
				   //∀k.k ∈ [s@pre,1,s),phi
					//last=0
                 if (der_pointer(s) == (char)c)
					//∀k.k ∈ [s@pre,1,s),phi
					//der_pointer(s)=c
					//∀k.k ∈ [s@pre,1,s+1),der_pointer(s)=c
                         last = s;
					//∀k.k ∈ [s@pre,1,s),phi
					//der_pointer(s)=c
					//∀k.k ∈ [s@pre,1,s+1),der_pointer(s)=c	
					//last=s
					
			//∀k.k ∈ [s@pre,1,s),phi		
         } while (
			s++;
			//∀k.k ∈ [s@pre,1,s-1),phi		
			der_pointer(s-1)!=0
			//∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
		   );
         return (char *)last;
 }
 


char *strrchr(const char *s, int c)
 {
		//∀k.k ∈ [s@pre,1,s),phi
         const char *last = 0;
		 //∀k.k ∈ [s@pre,1,s),phi
		 //last=0
		 
		 
		 //∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
         do {
				   //∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
                 if (der_pointer(s) == (char)c)
					 //∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
					//der_pointer(s)=c
                         last = s;
					 //∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
					//last=s
					
			 //∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
         } while (
			s++;
			 //∀k.k ∈ [s@pre,1,s-1),der_pointer(s-1)!=0				
			der_pointer(s-1)!=0
			//∀k.k ∈ [s@pre,1,s),der_pointer(s-1)!=0		
		   );
         return (char *)last;
 }


 
size_t strlen(const char *s)
 {
         const char *sc;
 
         for (sc = s; der_pointer(sc) != '\0'; ++sc)
                 /* nothing */;
         return sc - s;
 }
 
 
 
  char *strchr(const char *s, int c)
 {
         for (; *s != (char)c; ++s)
                 if (*s == '\0')
                         return NULL;
         return (char *)s;
 }
 
 
 
  char *strnchr(const char *s, size_t count, int c)
 {
         for (; count-- && *s != '\0'; ++s)
                 if (*s == (char)c)
                         return (char *)s;
         return NULL;
 }
 
 
  size_t strnlen(const char *s, size_t count)
 {
         const char *sc;
 
         for (sc = s; count-- && *sc != '\0'; ++sc)
                 /* nothing */;
         return sc - s;
 }
 
 
 
 
 
 
 char *strpbrk(const char *cs, const char *ct)
 {
         const char *sc1, *sc2;
		  sc1 = cs;
		  //∀k.k ∈ [sc1,1,cs),phi
         while(*sc1 != '\0') {
			 //∀k.k ∈ [sc1,1,cs),phi
			 //der_pointer(sc1)!= '\0'
			 sc2 = ct;
			 //∀k.k ∈ [sc1,1,cs),phi
			 //der_pointer(sc1)!= '\0'
			 //∀k.k ∈ [sc2,1,ct),phi
                 while (*sc2 != '\0') {
					 //∀k.k ∈ [cs,1,sc1),phi
					//der_pointer(sc1)!= '\0'
					//∀k.k ∈ [ct,1,sc2),phi
					//der_pointer(sc2)!= '\0'
                         if (*sc1 == *sc2)
								//∀k.k ∈ [cs,1,sc1),phi
								//der_pointer(sc1)!= '\0'
								//∀k.k ∈ [ct,1,sc2),phi
								//der_pointer(sc2)!= '\0'
								//der_pointer(sc1)==der_pointer(sc2)
                                 return (char *)sc1;
							//∀k.k ∈ [cs,1,sc1),phi
							//der_pointer(sc1)!= '\0'
							//∀k.k ∈ [ct,1,sc2),phi
							//der_pointer(sc2)!= '\0'
							//der_pointer(sc1)!=der_pointer(sc2)
							//∀k.k ∈ [ct,1,sc2),der_pointer(k)!= '\0'
							//∀k.k ∈ [ct,1,sc2),der_pointer(sc1)!=der_pointer(k)
							
							++sc2;
                 }
			 ++sc1;
         }
         return NULL;
 }
 
 
 for strpbrk, it need exist property
 
 
 
 /**
  * strspn - Calculate the length of the initial substring of @s which only contain letters in @accept
  * @s: The string to be searched
  * @accept: The string to search for
  */
 size_t strspn(const char *s, const char *accept)
 {
         const char *p;
         const char *a;
         size_t count = 0;
 
         for (p = s; *p != '\0'; ++p) {
                 for (a = accept; *a != '\0'; ++a) {
                         if (*p == *a)
                                 break;
                 }
                 if (*a == '\0')
                         return count;
                 ++count;
         }
         return count;
 }
 
 
 
 /**
  * strcspn - Calculate the length of the initial substring of @s which does not contain letters in @reject
  * @s: The string to be searched
  * @reject: The string to avoid
  */
 size_t strcspn(const char *s, const char *reject)
 {
         const char *p;
         const char *r;
         size_t count = 0;
 
         for (p = s; *p != '\0'; ++p) {
                 for (r = reject; *r != '\0'; ++r) {
                         if (*p == *r)
                                 return count;
                 }
                 ++count;
         }
         return count;
 }
 
 
 /**
  * strpbrk - Find the first occurrence of a set of characters
  * @cs: The string to be searched
  * @ct: The characters to search for
  */
 char *strpbrk(const char *cs, const char *ct)
 {
         const char *sc1, *sc2;
 
         for (sc1 = cs; *sc1 != '\0'; ++sc1) {
                 for (sc2 = ct; *sc2 != '\0'; ++sc2) {
                         if (*sc1 == *sc2)
                                 return (char *)sc1;
                 }
         }
         return NULL;
 }
 
 
  void *memset(void *s, int c, size_t count)
 {
         char *xs = s;
 
         while (count--)
                 *xs++ = c;
         return s;
 }
 
 
 int strncmp(const char *cs, const char *ct, size_t count)
 {
		  
         unsigned char c1, c2;
		  //[cs@pre,1,cs)*c1	
         while (count) {
			 //[cs@pre,1,cs)*c1
                 c1 = *cs++;
				 //[cs@pre,1,cs)*c1
                 c2 = *ct++;
				 //[cs@pre,1,cs)*c1
                 if (c1 != c2)
				 //[cs@pre,1,cs)*c1
                         return c1 < c2 ? -1 : 1;
                 if (!c1)
				//[cs@pre,1,cs)*c1
                         break;
				//[cs@pre,1,cs)*c1
                 count--;
				//[cs@pre,1,cs)*c1
         }
         return 0;
 }
 




int strncasecmp(const char *s1, const char *s2, unsigned len)
 {
         /* Yes, Virginia, it had better be unsigned */
         unsigned char c1, c2;
 
         if (!len)
                 return 0;
		 //forall 	x in [0,s1],phi
		 //meet
		 //forall 	x in [0,s1-1],phi
		//c2=*(s2-1);c1=*(s1-1);c1=c2;*(s1-1)=*(s2-1)
		//forall x in [0,s1]. *(x-1)=*(x-1)
		
		////forall x in [0,s1]. *(x-1)=*(x-1)
         do {
					//forall x in [0,s1]. *(x-1)=*(x-1)
                 c1 = *s1++;
				   //forall x in [0,s1-1]. *(x-1)=*(x-1) 
				   //c1=*(s1-1) 
                 c2 = *s2++;
				   //forall x in [0,s1-1]. *(x-1)=*(x-1) 
				   //c1=*(s1-1) 
				   //c2=*(s2-1)
                 if (!c1 || !c2)
					 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
                         break;
                 if (c1 == c2)
					 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
					 //*(s1-1)=*(s2-1) 
					 //forall x in [0,s1]. *(x-1)=*(x-1)
                         continue;
					//forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
					 //*(s1-1)!=*(s2-1)
                 if (c1 != c2)
					 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
					 //*(s1-1)!=*(s2-1)
                         break;
         } while (--len);
         return (int)c1 - (int)c2;
 }




int strncasecmp(const char *s1, const char *s2, unsigned len)
 {
         /* Yes, Virginia, it had better be unsigned */
         unsigned char c1, c2;
 
         if (!len)
                 return 0;
		 //forall 	x in [0,s1],phi
		 //meet
		//forall x in [0,s1-1]. *(x-1)=*(x-1) 
		//c1=*(s1-1) 
		//c2=*(s2-1)
		//*(s1-1)!=*(s2-1)
		 //forall x in [0,s1]. *(x-1)=*(x-1)
		////forall x in [0,s1]. *(x-1)=*(x-1)
         do {
					//forall x in [0,s1]. *(x-1)=*(x-1)
                 c1 = *s1++;
				   //forall x in [0,s1-1]. *(x-1)=*(x-1) 
				   //c1=*(s1-1) 
                 c2 = *s2++;
				   //forall x in [0,s1-1]. *(x-1)=*(x-1) 
				   //c1=*(s1-1) 
				   //c2=*(s2-1)
                 if (!c1 || !c2)
					 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
                         break;
                 if (c1 == c2)
					 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
					 //*(s1-1)=*(s2-1) 
					 //forall x in [0,s1]. *(x-1)=*(x-1)
                         continue;
					//forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
					 //*(s1-1)!=*(s2-1)
                 if (c1 != c2)
					 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
					 //c1=*(s1-1) 
				     //c2=*(s2-1)
					 //*(s1-1)!=*(s2-1)
                         break;
         } while (--len);
		 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
		 //c1=*(s1-1) 
		 //c2=*(s2-1)
		 //*(s1-1)!=*(s2-1)
		 //---meet---
		 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
		 //c1=*(s1-1) 
		 //c2=*(s2-1)
		 //----meet----
		 //forall x in [0,s1-1]. *(x-1)=*(x-1) 
		 //forall x in [0,s1]. *(x-1)=*(x-1)
         return (int)c1 - (int)c2;
 }



 void *memchr(const char *s, int c, int n)
 {
         const  char *p = s;
		  //forall x in [s,p),phi 
         while (n-- != 0) {
			 //forall x in [s,p),phi
				   p++;
			 //forall x in [s,p-1),phi
                 if ((unsigned char)c == *(p-1)) {
                         return (void *)(p - 1);
                 }
			//c!=*(p-1)
			//forall x in [s,p),c!=*(p-1)
			//forall x in [s,p-1),pji
	 
         }
         return 0;
 }
 
 
 
 void *memchr(const char *s, int c, int n)
 {
         const  char *p = s;
		  //forall x in [s,p),phi 
		  //meet
		  //forall x in [s,p),c!=*(p-1)
		  //////forall x in [s,p),c!=*(p-1)
         while (n-- != 0) {
			 //forall x in [s,p),c!=*(p-1)
				   p++;
			 //forall x in [s,p-1),c!=*(p-1)
                 if ((unsigned char)c == *(p-1)) {
                         return (void *)(p - 1);
                 }
			//c!=*(p-1)
			//forall x in [s,p-1),c!=*(p-1)
			//forall x in [s,p),c!=*(p-1)
         }
         return 0;
 }
 
 
 void *memchr(const char *s, int c, int n)
 {
         const  char *p = s;
		  //forall x in [s,p),phi 
		  //meet
		  //forall x in [s,p),c!=*(p-1)
		  //////forall x in [s,p),c!=*(p-1)
         while (n-- != 0) {
			 //forall x in [s,p),c!=*(p-1)
				   p++;
			 //forall x in [s,p-1),c!=*(p-1)
                 if ((unsigned char)c == *(p-1)) {
					 //forall x in [s,p-1),c!=*(p-1)
                         return (void *)(p - 1);
                 }
			//c!=*(p-1)
			//forall x in [s,p-1),c!=*(p-1)
			//forall x in [s,p),c!=*(p-1)
         }
		 
		 
         return 0;
		 
		 //forall x in [s,p-1),c!=*(p-1)
 }