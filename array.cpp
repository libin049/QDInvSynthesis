//****************************************************************************************

//#define size 100000
//int main( )
//{
//  int a[100000];
//  int b[100000];
//  int i = 1;
//  int j = 0;
//  while( i < 100000 ) 
//  {
//	a[j] = b[i];
//        i = i+4;
//        j = j+1;
//  }
//
//  i = 1;
//  j = 0;
//  while( i < 100000 )
//  {
//	//__VERIFIER_assert( a[j] == b[4*j+1] );
//        i = i+4;
//        j = j+1;
//  }
//  return 0;
//}
////---yes



void firstNotNull2(){
	unsigned size;
	int A[size];
	int s=size+1;
	for(int i=0;i<size;i++){
		if(s==size+1&&A[i]!=0){
			s=i;
		}
	}		 
}
////----yes


void firstNotNull(){
	unsigned size;
	int A[size];
	int s=size+1;;
	for(int i=0;i<size;i++){
		if(A[i]!=0){
			s=i;
			break;
		}
	}		
}
//// we can not get for all property
////but the result is OK
////----yes

void init00(){
	unsigned size;
	int A[size];
	int i=0;
    while(i<size){
		i++;
		A[i-1]=0;
	}
		 
}
////----yes




//

//void threeDarrayCopy(int* A,int* B,unsigned d1,unsigned d2,unsigned d3){
//	for(int i=0;i<d1;i++){
//		for(int j=0;j<d2;j++){			
//			for(int k=0;k<d3;k++){
//				A[i*d2+j*d3+k]=B[i*d2+j*d3+k];
//				//def_pointer_prime(A+i*d2+j*d3+k)=def_pointer(B+i*d2+j*d3+k)
//			}
//		}
//	}
//}
////because pointer relation, we can not get forall property, which is like strcpy
////howerer, it is so slow to compute it



void arrayCopy(){
	unsigned size;
	int A[size];
	int B[size];
	for(int i=0;i<size;i++){
		A[i]=B[i];		
	}
}
////----yes





bool arrayIf(){
	unsigned size;
	int A[size];int B[size];
	for(int i=0;i<size;i++){
		if(A[i]==0){
			return true;
		}
	}
	return false;
	
}
////----yes	





//////NFEASIBLEPATH can not process totally this, however FEASIBLEPATH can process this
//bool towDarrayIf(int** A,unsigned row,unsigned col){
//	bool flag=false;
//	for(int i=0;i<row;i++){
//		for(int j=0;j<col;j++){	
//			if(A[i][j]==0){
//				flag=true;
//				break;
//			}
//		}
//		if(flag==true){
//			break;
//		}
//	}
//	return flag;
//}
////----yes, we can get the exist properties

	 void towArrayInit(){
		 unsigned row;
		 unsigned col;
		 int A[row][col];        
		 for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                A[i][j]=0;
            }
        }
    }
////---yes
bool towarrayIf(){
	unsigned row,col;
	int A[row][col];
	bool flag=false;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){	
			if(A[i][j]==0){
				flag=true;
				break;
			}
		}
		if(flag==true){
			break;
		}
	}
	return flag;
}
////-----yes,we can get the exist properties

void arrayMax(){
	unsigned size;
	int A[size];
	int max=A[0];
	for(int i=0;i<size;i++){
         if(max<A[i]){
             max=A[i];
         }
    }
}
////-----yes



void arrayInit(){
	unsigned size;
	int A[size];
	A[0]=7;
	for(int i=1;i<size;i++){
         A[i]=A[i-1]+1;
    }
}
//// myabe ok bbecause we can not get properties: A[0]=7

//void arrayInit2(int A[],unsigned size){
//	A[0]=7;
//	for(int i=1;i<size;i++){
//         A[i-1]=A[i]+1;
//    }
//}
////---yes 
//void arrayInit2(){
//	unsigned size;
//	int A[size];
//	for(int i=1;i<size;i++){
//         A[i-1]=A[i]+1;
//    }
//}
////---yes 
//

void arrayInit3(){
	unsigned size;
	int A[size];
	for(int i=0;i<size;i++){
        A[i]=0;
    }
}
////----yes

  void arraySentinel(){
		unsigned size;
		int x;
		int A[size];
	    int i=0;
		while(i<size&&A[i]!=x){
			i=i+1;
		}
		
  }
//////---yes

//
//
//void arraySentinel2(){
//		 unsigned size;
//		 int x;
//		 int A[size];
//        A[size]=x; 
//		 int i=0;
//        while(i<size&&A[i]!=x){
//            i=i+1;
//        }
//  }
////---yes



  
    void arrayPartition(){
		unsigned size;int D;
		int A[size];int B[size]; int C[size];
        int i=0,j=0,k=0;
        while(i<size){
            if(A[i]<D){
                B[j]=A[i];
                j++;
            }
            else{
                C[k]=A[i];
                k++;
            }
            i++;
        }
    }
//----yes




//void threeDarrayCheck(){
//	unsigned d1;unsigned d2;unsigned d3;
//	int A[d1][d2][d3];int B[d1][d2][d3];
//	for(int i=0;i<d1;i++){
//		for(int j=0;j<d2;j++){			
//			for(int k=0;k<d3;k++){
//				if(A[i][j][k]==0){
//					goto L;
//				}
//			}
//		}
//	}
//	L:;	 
//}
////---yes
//
//
//	part of quick sort 
//    void find(int A[],unsigned size){
//        int x = A[0] ;
//        int i = 1;
//        int j =size-1;
//        while (i<=j){
//            if (A[i] < x){
//                A[i-1] = A[i] ;
//                i = i + 1;
//            }
//            else{
//                while(j>=i&&A[j]>=x){
//                    j = j-1;
//                }
//                if (j > i){
//                    A[i-1] = A[j];
//                    A[j] = A[i];
//                    i = i + 1 ;
//                    j = j-1;
//                }
//            }
//        }
//        A[i-1] = x ;
//    }
//------ yes, however we can not get froall formual 


 void find(){
	   unsigned size;
	   int A[size];
        int x = A[0] ;
        int i = 1;
        int j =size-1;
        while (i<=j){
            if (A[i] < x){
                A[i-1] = A[i] ;
                i = i + 1;
            }
            else{
                while(j>=i&&A[j]>=x){
                    j = j-1;
                }
                if (j > i){
                    A[i-1] = A[j];
                    A[j] = A[i];
                    i = i + 1 ;
                    j = j-1;
                }
            }
        }
        A[i-1] = x ;
    }
////---yes
//
//bool threeDarrayCheck2(){
//	unsigned d1;unsigned d2;unsigned d3;
//	int A[d1][d2][d3];int B[d1][d2][d3];
//	for(int i=0;i<d1;i++){
//		for(int j=0;j<d2;j++){			
//			for(int k=0;k<d3;k++){
//				if(A[i][j][k]==0){
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}
////---yes

//void insertSort(int *A,unsigned size){
//    for(int i=1;i<size;i++){
//        int x=A[i];
//        int j=i-1;
//        while(j>=0&&A[j]>x){ 
//            A[j+1]=A[j];
//            j--;
//        }
//        A[j+1]=x;
//    }
//}
////---yes, howerer we can not get forall property

void insertSort(){
	  unsigned size;
	  int A[size];
    for(int i=1;i<size;i++){
        int x=A[i];
        int j=i-1;
        while(j>=0&&A[j]>x){ 
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=x;
    }
}
///---yes, howerer we can not get forall property

//bool stringCompare1(int *src,int d1,int *sub,int d2){
//	for(int i=0;i<d1;i++){
//		bool flag=true;
//		for(int j=0;j<d2;j++){
//			if(src[i+j]!=sub[j]){
//				flag=false;
//				break;
//			}
//		}
//		if(flag==true){
//			return true;
//		}
//	}
//	return false;
//}
//----yes
//bool stringCompare2(int *src,int d1,int *sub,int d2){
//	bool flag=false;
//	for(int i=0;i<d1;i++){
//		flag=true;
//		for(int j=0;j<d2;j++){
//			if(src[i+j]!=sub[j]){
//				flag=false;
//				break;
//			}
//		}
//		if(flag==true){
//			break;
//		}
//	}
//	return flag;
//}
//-----yes




//int main2()
//{
//  int a[100000];
//  int b[100000];
//  int i = 0;
//  int j = 0;
//  while( i < 100000 ) 
//  {
//	a[j] = b[i];
//        i = i+1;
//        j = j+1;
//  }
//
//  i = 0;
//  j = 0;
//  while( i < 100000 )
//  {
//	//__VERIFIER_assert( a[j] == b[j] );
//        i = i+1;
//        j = j+1;
//  }
//  return 0;
//}
////---yes

//void copy2() {
//	int a1[100]; 
//	int a2[100];
//	int a3[100];
//  
//	int i; 
//	for ( i = 0 ; i < 100 ; i++ ) {
//		a2[i] = a1[i];
//	}
//	for ( i = 0 ; i < 100 ; i++ ) {
//		a3[i] = a2[i];
//	}
//  
//  //assert( forall (int x) :: (0 <= x && x < N) ==> (a1[x] == a3[x]) );
//}
//-----yes


//void threeDarrayCopy(){
//	unsigned d1;unsigned d2;unsigned d3;unsigned d4;
//	int A[d1][d2][d3];
//	for(int i=0;i<d1;i++){
//		for(int j=0;j<d2;j++){			
//			for(int k=0;k<d3;k++){
//					A[i][j][k]=0;
//				
//			}
//		}
//	}
//}



void towDarrayCopy(){
	unsigned row;
	unsigned col;
	int A[row][col];
	int B[row][col];
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){			
			A[i][j]=B[i][j];
		}
	}
}

//void fiveDarrayCopy(){
//	unsigned d1;unsigned d2;unsigned d3;unsigned d4;unsigned d5;
//	int A[d1][d2][d3][d4][d5];
//	for(int i=0;i<d1;i++){
//		for(int j=0;j<d2;j++){			
//			for(int k=0;k<d3;k++){
//				for(int h=0;h<d4;h++){
//					for(int l=0;l<d5;l++){
//						A[i][j][k][h][l]=0;
//					}
//				}
//			}
//		}
//	}
//}
// can not process , system kill it 


//void fourDarrayCopy(){
//	unsigned d1;unsigned d2;unsigned d3;unsigned d4;
//	int A[d1][d2][d3][d4];
//	for(int i=0;i<d1;i++){
//		for(int j=0;j<d2;j++){			
//			for(int k=0;k<d3;k++){
//				for(int h=0;h<d4;h++){
//					A[i][j][k][h]=0;
//				}
//			}
//		}
//	}
//}




//int main3()
//{
//  int a[100000];
//  int b[100000];
//  int i = 1;
//  int j = 0;
//  while( i < 100000 ) 
//  {
//	a[j] = b[i];
//        i = i+2;
//        j = j+1;
//  }
//
//  i = 1;
//  j = 0;
//  while( i < 100000 )
//  {
//	//__VERIFIER_assert( a[j] == b[2*j+1] );
//        i = i+2;
//        j = j+1;
//  }
//  return 0;
//}
////---yes


//int main4( )
//{
//  int a[100000];
//  int b[100000];
//  int i = 1;
//  int j = 0;
//  while( i < 100000 ) 
//  {
//	a[j] = b[i];
//        i = i+3;
//        j = j+1;
//  }
//
//  i = 1;
//  j = 0;
//  while( i < 100000 )
//  {
//	//__VERIFIER_assert( a[j] == b[3*j+1] );
//        i = i+3;
//        j = j+1;
//  }
//  return 0;
//}
//


//void main5( )
//{
//  int a[100000];
//  int b[100000];
//  int i = 0;
//  int j = 0;
//  while( i < 100000 ) 
//  {
//	a[j++] = b[i++];
//  }
//}
//
/*
 char *strcpy(char *dest, const char *src)
 {
         char *tmp = dest;
 
         while ((*dest++ = *src++) != '\0')
                 ;
         return tmp;
 }
////---yes
// 
 char *strncpy(char *dest, const char *src, int count)
 {
         char *tmp = dest;
 
         while (count) {
                 if ((*tmp = *src) != 0)
                         src++;
                 tmp++;
                 count--;
         }
         return dest;
 }
//-------yes we get nothing 
 
 char *strcat(char *dest, const char *src)
 {
         char *tmp = dest;
 
         while (*dest)
                 dest++;
         while ((*dest++ = *src++) != '\0')
                 ;
         return tmp;
 }
//-------yes


 char *strncat(char *dest, const char *src, int count)
 {
         char *tmp = dest;
 
         if (count) {
                 while (*dest)
                         dest++;
                 while ((*dest++ = *src++) != 0) {
                         if (--count == 0) {
                                 *dest = '\0';
                                 break;
                         }
                 }
         }
         return tmp;
 }
 //-------yes
 
 


  int strcmp(const char *cs, const char *ct)
 {
         unsigned char c1, c2;
 
         while (1) {
                 c1 = *cs++;
                 c2 = *ct++;
                 if (c1 != c2)
                         return c1 < c2 ? -1 : 1;
                 if (!c1)
                         break;
         }
         return 0;
 }
 
////---yes

//  forall _i1 in [cs@pre,1,(- cs 1)),(let ((a!1 (+ (div (- (+ _i1 1) cs@pre) 1) 0 ct@pre)))(= (def_pointer (- a!1 1)) (def_pointer (- (+ _i1 1) 1))));
//	forall _i1 in [cs@pre,1,(- cs 1)),(distinct (def_pointer _i1) 0);
//	forall _i1 in [ct@pre,1,(- ct 1)),(distinct (def_pointer _i1) 0);
//	{(not (distinct c1 0))} || {(distinct (def_pointer (- cs 1)) (def_pointer (- ct 1)))};
//	(= c1 (def_pointer (- cs 1)));
//	(= c2 (def_pointer (- ct 1)));
//	{(= _ret 0)} || {(distinct (def_pointer (- cs 1)) (def_pointer (- ct 1)))};
//	{(= _ret 0)} || {(= _ret (ite (< c1 c2) (- 1) 1))};   
//	{forall _i1 in [cs@pre,1,cs),*(_i1-cs@pre+ct@pre)=*(_i1)} 
//  || {(= _ret (ite (< c1 c2) (- 1) 1))};
//  * 
//  * 
//  * 
// * 
// *  i think may be yes
// * 
////-------yes


 int strncmp(const char *cs, const char *ct, int count)
 {
         unsigned char c1, c2;
 
         while (count) {
                 c1 = *cs++;
                 c2 = *ct++;
                 if (c1 != c2)
                         return c1 < c2 ? -1 : 1;
                 if (!c1)
                         break;
                 count--;
         }
         return 0;
 }
 
 

//-------yes

char *strchr(const char *s, int c)
 {
         for (; *s != (char)c; ++s)
                 if (*s == '\0')
                         return 0;
         return (char *)s;
 }
 //-------yes
 
 
  char *strchrnul(const char *s, int c)
 {
         while (*s && *s != (char)c)
                 s++;
         return (char *)s;
 }
 //-------yes
 
 
  char *strrchr(const char *s, int c)
 {
         const char *last = 0;
         do {
                 if (*s == (char)c)
                         last = s;
         } while (*s++);
         return (char *)last;
 }
 //-------yes
 
  char *strnchr(const char *s, int count, int c)
 {
         for (; count-- && *s != '\0'; ++s)
                 if (*s == (char)c)
                         return (char *)s;
         return 0;
 }
  //-------yes
  
  
   int strlen(const char *s)
 {
         const char *sc;
 
         for (sc = s; *sc != '\0'; ++sc)
				;
         return sc - s;
 }
   //-------yes
   
   
    int strnlen(const char *s, int count)
 {
         const char *sc;
 
         for (sc = s; count-- && *sc != '\0'; ++sc)
              ;
         return sc - s;
 }
  //-------yes
  
  
  
  int strspn(const char *s, const char *accept)
 {
         const char *p;
         const char *a;
         int count = 0;
 
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
//--------yes


int strcspn(const char *s, const char *reject)
 {
         const char *p;
         const char *r;
         int count = 0;
 
         for (p = s; *p != '\0'; ++p) {
                 for (r = reject; *r != '\0'; ++r) {
                         if (*p == *r)
                                 return count;
                 }
                 ++count;
         }
         return count;
 }
 ///--------yes
 
 char *strpbrk(const char *cs, const char *ct)
 {
         const char *sc1, *sc2;
 
         for (sc1 = cs; *sc1 != '\0'; ++sc1) {
                 for (sc2 = ct; *sc2 != '\0'; ++sc2) {
                         if (*sc1 == *sc2)
                                 return (char *)sc1;
                 }
         }
         return 0;
 }
  ///--------yes
 
 bool sysfs_streq(const char *s1, const char *s2)
 {
         while (*s1 && *s1 == *s2) {
                 s1++;
                 s2++;
         }
 
         if (*s1 == *s2)
                 return true;
         if (!*s1 && *s2 == '\n' && !s2[1])
                 return true;
         if (*s1 == '\n' && !s1[1] && !*s2)
                 return true;
         return false;
 }
//--------yes


 void *memset(char *s, int c, int count)
 {
         char *xs = s;
 
         while (count--)
                 *xs++ = c;
         return s;
 }
////---yes


 void *memcpy(char *dest, const char *src, int count)
 {
         char *tmp = dest;
         const char *s = src;
 
         while (count--)
                 *tmp++ = *s++;
         return dest;
 }
 ////---yes we get nothing
 
 
void *memscan(char *addr, int c, int size)
 {
          char *p = addr;
 
         while (size) {
                 if (*p == c)
                         return (void *)p;
                 p++;
                 size--;
         }
         return (void *)p;
 }
 ////---yes
 
 
  void *memchr(const char *s, int c, int n)
 {
         const  char *p = s;
         while (n-- != 0) {
                 if ((unsigned char)c == *p++) {
                         return (void *)(p - 1);
                 }
         }
         return 0;
 }
 ////---yes
 
 
  void *check_bytes8(const char *start, char value, unsigned int bytes)
 {
         while (bytes) {
                 if (*start != value)
                         return (void *)start;
                 start++;
                 bytes--;
         }
         return 0;
 }
  ////---yes
void existOne(){ 
	int size;
    int A[size];
    int i=0;
    bool flag=false;
	while(i<size){
		if(A[i]==0){
            flag=true;
            break;
        }
        i++;
    }
//	//assert (exist _i0 in [0,1,size),(not (= (select A _i0) 0))) || (= i 0);
  }
//----yes  
  */
  bool arraycmp(){ 
	 int d1,d2;
    int src[d1]; int sub[d2];
    bool flag=false;
    for(int i=0;i<d1;i++){
        flag=true;
        for(int j=0;j<d2;j++){
            if(src[i+j]!=sub[j]){
                flag=false;
                break;
            }
        }
        if(flag==true){
            break;
        }
    }
    return flag;
  }
//----yes 

// forall _i1 in [0,1,i),exist _i0 in [0,1,d2),(distinct (select src (+ _i1 _i0)) (select sub _i0));
// {(= flag 1)} || {forall _i1 in [0,1,d1),exist _i0 in [0,1,d2),(distinct (select src (+ _i1 _i0)) (select sub _i0))};
// {exist _i1 in [0,1,d1),forall _i0 in [0,1,j),(= (select src (+ _i1 _i0)) (select sub _i0))} || {(= flag 0)};
// {forall _i0 in [0,1,d2),(= (select src (+ i _i0)) (select sub _i0))} || {(= flag 0)};


void Merge()
{
	int N;
	int a[N]; int l; int m; int r;
    int i = l, j = m+1, k = l;
    int b[N];
    while(i <= m && j <= r)
    {
        if(a[i] <= a[j])
        {
            b[k++] = a[i++];
        }
        else
        {
            b[k++] = a[j++];
        }
    }

    if(i > m)
    {
        for(int p = j; p <= r; p ++)
        {
            b[k++] = a[p];
        }
    }
    else
    {
        for(int p = i; p <= m; p ++)
        {
            b[k++] = a[p];
        }
    }

    //把b[]中排好的元素copy到a[]中
    for(int q = l; q <= r; q ++)
    {
        a[q] = b[q];
    }
}