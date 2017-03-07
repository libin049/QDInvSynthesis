

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
