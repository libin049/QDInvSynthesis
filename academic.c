/****************************************************************************/
/*     The following loops are extracted from different research papers of  */
/*A. Voronkov, L. Kovacs, I. Dillig, T.Dillig, K.L. McMillan and S. Gulwani */
/****************************************************************************/


void Initalization(){
  int a, m, *aa;
  while(a<m){
    aa[a]=0;
    a++;
  }
}

void Copy(){
  int a, m,*aa,*bb;
  while(a<m){
    bb[a] =aa[a];
    a++;
  }
}

void Partition(){
  int a, m,b,c, *aa,*bb,*cc;
  while(a<m){
    if(aa[a]>=0){
      bb[b]=aa[a];
      b++;
    }else{
      cc[c]=aa[a];
      c++;
    }
    a++;
  }
}

void Vararg(){
  int a, *aa;
  while(aa[a]>=0){
    a++;
  }
}

void Partition_Init(){
  int *aa, *bb, *cc;
  int a, b, size;
  while(a<size){
    if(aa[a]==cc[a]){
      bb[b]=a;
      b++;
    }
    a++;
  }
}
/*
 * Initializes all elements of a to a specified constant c.
 */
void init(int* a, int c, int size)
{
  int i;
  /*
  for(i=0; i<size; i++) 
  {
	a[i] = c;
  }
  */
  //transformed into while:
  //invariant would be: 
  // for all x : (0<= x < i) => a[x] = c  
  
  i = 0;
  while(i<size){
  	a[i]=c;
  	i=i+1;
  }

  /*
  for(i=0; i<size; i++)
  {
	static_assert(a[i] == c);
  }
  */
}

//=======================================

/*
 * Initializes all elements of a to a linear function of iteration number.
 */
void init_non_constant(int* a, int c, int size)
{
  /*
  int i;
  for(i=0; i<size; i++) 
  {
	a[i] =2*i+c;
  }
  */
  //transformed into while 
  int i = 0;
  //desired invariant 
  // for all x : 0 <=x<i => a[x] = 2*x + c;
  while(i< size){
  	a[i] = 2*i + c; 
  	i=i+1;
  }
  
/*
  for(i=0; i<size; i++)
  {
	static_assert(a[i] ==2*i+c);
  }
*/
}




/*
 * Initializes num_to_init number of elements of a to 0.
 */
void init_partial(int* a, int size, int num_to_init)
{
  /*
  assert(num_to_init <= size);
  int i;
  for(i=0; i<num_to_init; i++) 
  {
	a[i] = 0;
  }
  */
  //transformed into while 
  int i;
  i = 0;
  //desired invariant:
  // for all x : 0<=x<i => a[x]=0

  while(i<num_to_init){
  	a[i] = 0;
  	i = i+1;
  }

/*
  for(i=0; i<num_to_init; i++)
  {
	static_assert(a[i] == 0);
  }
*/
}


/*
 * Initializes num_to_init number of elements of a to 0, 
 * but asserts all elements up to size are initialized to 0.
 */
void init_partial_buggy(int* a, int size, int num_to_init)
{
  //assert(num_to_init <= size);
  /*
  int i;
  for(i=0; i<num_to_init; i++) 
  {
	a[i] = 0;
  }
  */
  //converted to while 
  int i;
  i = 0;
  //desired invariant 
  // for all x : 0 <= x < i => a[x] = 0

  while(i<num_to_init){
  	a[i] = 0;
  	i = i+1;
  }

  /*
  for(i=0; i<size; i++)
  {
	// should fail
	static_assert(a[i] == 0);
  }
  */
}

/*
 * Initializes all even elements of a to 1.
 */
void init_even(int* a,  int size)
{
  int i;
  /*
  for(i=0; i<size; i+=2) 
  {
	a[i] = 1;
  }
  */
  //converted into while 

  //desired invariant:
  //for all x: ( 0<=x<i & x%2 == 0) => a[x]=1
  //or 
  //for all x:  0<= x <i =>  ( x%2==0 & a[x] = 1) | a[x] = a0[x]
  while(i<size){
  	a[i] = 1;
  	i = i + 2;
  }
  /*
  for(i=0; i<size; i+=2)
  {
	static_assert(a[i] == 1);
  }
  */
}



/*
 * Initializes all even elements of a to 1,
 * but asserts all odd elements are 1.
 */
void init_even_buggy(int* a,  int size)
{
  int i;
  /*
  for(i=0; i<size; i+=2) 
  {
	a[i] = 1;
  }
  */
  //converted into while 
  i = 0 ; 
  //for all x : 0<= x < i => (x%2==0 & a[x]=1 )| (x%2!=0 & a[x]=a0[x])
  while(i<size){
  	a[i] = 1; 
  	i = i + 2; 
  }
  /*
  for(i=1; i<size; i+=2)
  {
	// should fail
	static_assert(a[i] == 1);
  }
  */
}

/*
 * Initializes a 2d array to 0 and asserts that 
 * any element in it is 0
 */
void _2Darray_init(int** a, int n, int m, int k, int l)
{
   int i;
   int j;
   /*
   for( i=0; i<n; i++)
   {
       for(j=0; j<m; j++)
           a[i][j] = 0;
   }
   */
   //converted into while 
   // we do not handle multiple whiles yet nor 2D arrays
   i = 0;
   /*
   while(i<n){
   	j = 0;
   	while(j<m){
   		a[i][j]=0;
   		j=j+1;
   	}
   	i=i+1;
   }
   */
   /*
   if(k>=0 && k<n && l>=0 && l<m)
     static_assert(a[k][l] == 0);
   */
} 




/*
 * Copies elements of b to a.
 */
void copy(int* a, int*b,  int size)
{
  int i;
  /*
  for(i=0; i<size; i++) 
  {
	a[i] = b[i];
  }
	*/
  //converted to while
  //desired invariant: 
  // for all x : 0<=x<i => a[x] = b[x]
  i = 0 ; 
  while(i<size){
  	a[i] = b[i];
  	i = i + 1; 
  }
  /*
  for(i=0; i<size; i++)
  {
	static_assert(a[i] == b[i]);
  }
  */
}


/*
 * Copies num_to_copy number of elements of b to a.
 */
void copy_partial(int* a, int*b,  int size, int num_to_copy)
{
  //assert(num_to_copy <= size);
  int i;
  /*
  for(i=0; i<num_to_copy; i++) 
  {
	a[i] = b[i];
  }
  */
  //converted to while 
  i = 0 ; 
  //desired invariant
  // for all x : 0<=x<i => a[x]=b[x]
  while(i < num_to_copy){
  	a[i] = b[i];
  	i = i + 1;
  }
  /*
  for(i=0; i<num_to_copy; i++)
  {
	static_assert(a[i] == b[i]);
  }
  */
}



/*
 * Copies odd numbered elements of b to a contiguously.
 */
void copy_odd(int* a, int*b,  int size)
{
  int i;
  int j;
  /*
  for(i=1, j=0; i<size; i+=2, j++) 
  {
	a[j] = b[i];
  }
  */
  //converted to while 

  i = 1 ; 
  j = 0 ; 
  //desired invariant, we should also specify a linear relation between x and y
  // for all x : 1<=x<i & (x%2==1) => there exists y : a[y] = b[x]
  // we can easy prove the following: 
  // for all x : 0<`
  while(i < size){
  	a[j] = b[i];
  	i = i + 2; 
  	j = j + 1;
  }

  /*
  for(i=1, j=0; i<size; i+=2, j++)
  {
	static_assert(a[j] == b[2*j+1]);
  }
  */
}


/*
 * Copies odd numbered elements of b to a contiguously,
 * but asserts all of their elements are equal.
 */
void copy_odd_buggy(int* a, int*b,  int size)
{
  int i;
  int j;
  /*
  for(i=1, j=0; i<size; i+=2, j++) 
  {
	a[j] = b[i];
  }
  */
//converted to while 

  i = 1 ; 
  j = 0 ; 
  //desired invariant
  //here it should be better to have also linear combination between y and x so that we can express the fact that a is contiguous
  // for all x : 1<=x<i & (x%2=1) => there exists y: a[y] = b[x] 
  while(i < size){
  	a[j] = b[i];
  	i = i + 2; 
  	j = j + 1;
  }

  /*
  for(i=0; i<size; i++)
  {
	// should fail
	static_assert(a[i] == b[i]);
  }
  */
}

/*
 * Reverses array a and checks it is reversed for 
 * any k between 0 and size-1.
 */
void reverse(int* a, int size, int k)
{	
	int i;
	int* a_copy;// = malloc(sizeof(int)*size);
	/*
	for(i=0; i<size; i++)
	{
		a_copy[i] = a[i];
	}
	*/
	//converted to while 
	// invariant : 
	// for all x : 0<=x<i => a_copy[x] = a[x]
	i = 0;
	while(i<size){
	  a_copy[i]=a[i];
	  i = i + 1; 
	}
	
	/*
	for(i=0; i<size; i++)
	{
		a[i] = a_copy[size-1-i];
	}
	*/
	//converted to while 
	//invariant : 
	// for all x : 0<=x<i => there exists y: (y=size-1-x) & a[x] = a_copy[y]
	i = 0;
	int j;
	while(i<size){

	  j = size-i-1;
	  a[i]= a_copy[j];
	  i = i + 1;
	}
	/*
	if(k>=0 && k<size)
	{
		static_assert(a[k] == a_copy[size-1-k]);
	}

	free(a_copy);	
	*/
}


/*
 * Reverses array a, but has an of--by-one error
 * in checking it is reversed.
 */
void reverse_buggy(int* a, int size, int k)
{	
	int i;
	int* a_copy;// = malloc(sizeof(int)*size);
	/*
	for(i=0; i<size; i++)
	{
		a_copy[i] = a[i];
	}
	*/
	//converted to while 
	// invariant : 
	// for all x : 0<=x<i => a_copy[x] = a[x]
	i = 0;
	while(i<size){
	  a_copy[i]=a[i];
	  i = i + 1; 
	}
	
	/*
	for(i=0; i<size; i++)
	{
		a[i] = a_copy[size-1-i];
	}
	*/
	//converted to while 
	//invariant : 
	// for all x : 0<=x<i => there exists y: (y=size-1-x) & a[x] = a_copy[y]
	i = 0;
	int j;
	while(i<size){

	  j = size-i-1;
	  a[i]= a_copy[j];
	  i = i + 1;
	}

	/*
	if(k>=0 && k<=size)
	{
		// should fail; the assertion does not hold if k==size.
		static_assert(a[k] == a_copy[size-1-k]);
	}

	free(a_copy);	
	*/
}



/*
 * Swaps a and b and checks they are swapped by first making 
 * copies of the original a and b.
 */

void swap1(int* a, int* b, int size)
{
	int i;
	/*
	for(i=0; i<size; i++)
	{
		int t = a[i];
		a[i] = b[i];
		b[i] = t;
	}
	*/
	//while conversion 
	i = 0 ;
	int t;
	//desired invariant 
	//considering a0[i] - initial value of a[i] and b0[i] initial value of b[i]
	// for all x : 0<=x<i => a[x] = b0[x] & b[x] = a0[x]
	while(i < size){

	  t = a[i]; 
	  a[i] = b[i];
	  b[i] = t; 
	  i = i + 1;
	}

}

void check_swap1(int size, int* a, int* b)
{
	int i;
	int* a_copy;// = malloc(sizeof(int)*size);
	
	//same as copy above
	for(i=0; i<size; i++)
	{
		a_copy[i] = a[i];
	}

	int* b_copy;// = malloc(sizeof(int)*size);
	//same as copy above
	for(i=0; i<size; i++)
	{
		b_copy[i] = b[i];
	}
	//function call not handled
	//swap(a, b, size);
	
	/*
	for(i=0; i<size; i++)
	{
		static_assert(a[i] == b_copy[i]);
		static_assert(b[i] == a_copy[i]);
	}
	
	free(a_copy);
	free(b_copy);
	*/
}


/*
 * Buggy version of swap; the assertion in check_swap should fail.
 */

void swap_buggy(int* a, int* b, int size)
{
	int i;
	/*
	for(i=0; i<size; i++)
	{
		int t = a[i];
		b[i] = a[i];
		a[i] = t;
	}
	*/
	//converted to while 
	//invariant
	// for all x : 0<= x < i => a[x] = a0[x] & b[x] = a[x]
	i = 0 ;
	int t;
	while(i<size){
		 t = a[i];
		b[i] = a[i];
		a[i] = t;
		i = i + 1;
	}
}

void check_swap(int size, int* a, int* b)
{
	int i;
	int* a_copy;// = malloc(sizeof(int)*size);
	
	//above copy 
	for(i=0; i<size; i++)
	{
		a_copy[i] = a[i];
	}

	int* b_copy;// = malloc(sizeof(int)*size);
	//above copy
	for(i=0; i<size; i++)
	{
		b_copy[i] = b[i];
	}
	//function call 
	//swap(a, b, size);

	/*
	for(i=0; i<size; i++)
	{
		static_assert(a[i] == b_copy[i]);
		static_assert(b[i] == a_copy[i]);
	}
	
	free(a_copy);
	free(b_copy);
	*/
}


/*
 * Swaps a and b twice and asserts that 
 * a is same as a_copy and b is same as b_copy.
 */
//same function as before annotated
void swap(int* a, int* b, int size)
{
	int i;
	int t;
	for(i=0; i<size; i++)
	{
		t = a[i];
		a[i] = b[i];
		//b[i] = t;
	}
}

void double_swap(int size, int* a, int* b)
{
	int i;
	int* a_copy;// = malloc(sizeof(int)*size);
	
	//array copy , the same as before
	for(i=0; i<size; i++)
	{
		a_copy[i] = a[i];
	}

	int* b_copy;// = malloc(sizeof(int)*size);
	//array copy, the same as before
	for(i=0; i<size; i++)
	{
		b_copy[i] = b[i];
	}
	//call the function swap
	//swap(a, b, size);
	//swap(a, b, size);
	
	/*
	for(i=0; i<size; i++)
	{
		static_assert(a[i] == a_copy[i]);
		static_assert(b[i] == b_copy[i]);
	}
	
	free(a_copy);
	free(b_copy);
	*/
}

/*
 * Copies source into dest and checks that dest has 
 * the same contents as source.
 */

//this works with chars, and we do not handle that. If it would work with ints, it would be similar to copy 
void strcpy(int* dest, int* source)
{
  /*
	for(; *source!='\0'; source++, dest++)
	{
		*dest = *source;
	}
  */
  int i = 0;
  // invariant: 
  // for all x : 0<= x < i => dest[x] = source[x]
  while( source[i] != 0 ){
    dest[i] = source[i];
    i = i + 1;
  }
}

/*
void check_strcpy(char* str1, char* str2)
{
	strcpy(str1, str2);
	for(; *str2!='\0'; str1++, str2++) {
		static_assert(*str1 == *str2);
	}

}
*/

/*
 * Checks strlen returns buffer_size(str)-1. 
 * It's not buffer_size(str) because buffer_size
 * includes the last '\0'.
 */
//unchanged header
//unsigned int strlen(char* str)

int strlen(int* str)
{
	int i=0;
	//invariant: 
	// for all x : 0<=x<i => str[i]!=0
	while(str[i] != 0)
	{
		i++;
	}
	return i;
	
}
/*
void check_strlen(char* str)
{
	unsigned int size;
	size = strlen(str);

	static_assert(size == buffer_size(str)-1);

}
*/

/*
 * Buggy version of strlen that has an off-by-one error.
 */
//unchanged header
//unsigned int strlen_buggy(char* str)

unsigned int strlen_buggy(int* str)
{
	int i=0;
	//original program, to obey the definition it should have been != '\0'
	//while(str[i++]=='\0');
	//invariant
	// for all x : 0<=x<i => str[x]=0
	while(str[i]==0){
	  i++;
	}
	return i;
	
}

//nothing to do here
/*
void check_strlen(char* str)
{
	unsigned int size = strlen_buggy(str);
	static_assert(size == buffer_size(str)-1);
}
*/

void memcpy(void*_dest, void* _source, int bytes)
{
  //WORK with int instead of char
  int* dest ; //= (char*) _dest;
  int* source;// = (char*) _source;
  int i;
  /*
    for(i=0; i<bytes; i++) 
    {
    dest[i] = source[i];
    }
  */
  //invariant 
  // for all x : 0<=x<i => dest[x] = source[x]
  while(i < bytes){
    dest[i] = source[i];
    i = i + 1;   
  }
}



/*
 * Looks for a certain element in array and sets
 * pos to the index of this element. 
 */
void find(int* a, int size, int elem)
{
	int i;
	int pos = -1;
	/*
	for(i=0; i<size; i++)
	{
		if(a[i] == elem) 
		{
			pos = i;
			break;
		}
	}
	*/
	i=0;
	//converted to while
	//desired invariant 
	// for all x : 0<= x < i => ( ( pos = -1) & a[x]!=elem ) | (pos = x & a[x] = elem) ). 
	while(i<size && pos ==-1){
	  if(a[i] == elem)
	    {
	      pos = i;
	    }
	  i=i+1;
	}
	//if(pos!= -1) static_assert(a[pos] == elem);	


}


void find_first_nonnull(int* a, int size)
{
	int pos = -1;
	int i;
	/*
	for(i=0; i<size; i++)
	{
		if(a[i] != NULL) {
			pos = i;
			break;
		}
	}
	*/
	i=0;
	//converted to while
	//desired invariant 
	// for all x : (0<= x <i ) =>  ((a[x] == NULL) & ( pos = -1 )) | (pos = x & a[x] != NULL) ). 

	while(i<size && pos ==-1){
	  if(a[i] != 0)
	    {
	      pos = i;
	    }
	  i=i+1;
	}
	//if(pos !=-1) static_assert(a[i] !=NULL);
}


void array_append(int* a,  int size_a, int* b, int size_b, int k)
{
	int i = size_a;
	/*
	for(; i < size_a+size_b; i++)
	{
		a[i] = b[i-size_a];
	}
	*/
	//translated to while 
	//invariant 
	//for all x : size_a <= x < i => a[x] = b[x-size_a]
	//the following one we can prove: 
	//for all x: 0<= x < i-size_a => a[x+size_a] = b[x]
	i = size_a;
	int j;
	while( i < size_a+size_b ){

	  j = i - size_a;
	  a[i] = b[j];
	  i = i + 1; 
	}
	/*
	if(k >=size_a && k < size_a+size_b)
		static_assert(a[k] == b[k-size_a]);
	*/
}



void merge_interleave(int* res, int* a, int*b, int size)
{
	int i;
	/*
	for(i=0; i < size; i+=2)
	{
		res[i] = a[i];
	}
	*/
	i = 0;
	//desired invariant 
	// for all x : 0 <= x <i & x%2 == 0 => res[x] = a[x]
	while(i < size){
	  res[i] = a[i];
	  i = i + 2;
	}
	/*
	for(i=1; i < size; i+=2)
	{
		res[i] = b[i];
	}
	*/
	i = 1; 
	//desired invariant 
	// for all x : 1 <= x <i & x%2 != 0 => res[x] = a[x]
	while(i < size){
	  res[i] = a[i];
	  i = i + 2;
	}
	/*
	int k;
	if( k>=0 && k<size) {
		if(k%2 == 0) static_assert(res[k] == a[k]);
		else static_assert(res[k] == b[k]);
	}
	*/
}



void merge_interleave_buggy(int* res, int* a, int*b, int size)
{
	int i;
	//same as above
	for(i=0; i < size; i+=2)
	{
		res[i] = a[i];
	}
	//same as above
	for(i=1; i < size; i+=2)
	{
		res[i] = b[i];
	}
	int k;
	//this is the buggy part
	/*
	if( k>=0 && k<size) {
		if(k%2 == 1) static_assert(res[k] == a[k]);
		else static_assert(res[k] == b[k]);
	}
	*/
}



void alloc_fixed_size(int* a, int size, int n, int k)
{
   int i;
   // if we look at this like at an assignmnet instead of malloc then we can convert as follows: 
   /*
     for( i=0; i<n; i++){
       a[i] = malloc(sizeof(int)*size);
       }
   */
   i = 0 ; 
   int value_representing_malloc;
   //invariant
   // for all x : 0<= x < n => a[x] = value_representing_malloc
   while(i < n){
     a[i] = value_representing_malloc;
     i = i + 1; 
   }
   /*
   if(n>=0 && k>=0 && k<n) {
       buffer_safe(a[k], size-1);
   }
   */
}

  //similar with the previous problem, 
void alloc_nonfixed_size(int* a, int* b, int n, int k)
{
   int i;
   int value_representing_malloc;
   for( i=0; i<n; i++){
       a[i] = value_representing_malloc;
   }
   /*
   if(n>=0 && k>=0 && k<n) {
       buffer_safe(a[k], b[k]-1);
   }*/
}



