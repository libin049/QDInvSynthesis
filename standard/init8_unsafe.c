#define N

void main ( int a [N] ) {
  int i = 0;
  while ( i < N ) {
    a[i] = 42;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 43;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 44;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 45;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 46;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 47;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 48;
    i = i + 1;
  }
  i = 0;
  while ( i < N ) {
    a[i] = 49;
    i = i + 1;
  }

  assert( forall (int x) :: (0 <= x && x < N) ==> ( a[x] == 48 ) );
}
