#define N

void main ( int a [N] , int b [N] ) {
  int i = 0;
  while ( i < N ) {
    a[i] = 42;
    i = i + 1;
  }

  for ( i = 0 ; i < N ; i++ ) {
    b[i] = a[i];
  }
  
  for ( i = 0 ; i < N ; i++ ) {
    b[i] = b[i] + i;
  }

  for ( i = 0 ; i < N ; i++ ) {
    b[i] = b[i] - a[i];
  }

  assert( forall (int x) :: (0 <= x && x < N) ==> ( b[x] == x ) );
}
