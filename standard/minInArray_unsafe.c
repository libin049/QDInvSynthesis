#define N

void main( int a[] ) {
  int min = 0;
  int i = 0;
  while ( i < N ) {
    if ( a[i] < min ) {
      min = a[i];
    }
    i = i + 1;
  }
  assert( forall (int x) :: (0 <= x && x < N) ==> a[x] > min );
}
