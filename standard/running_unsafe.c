#define N

int main ( int a[] , bool b[] ) {
  int i = 0;
  while ( i < N ) {
    if ( a[i] >= 0 ) b[i] = true;
    else b[i] = false;
    i = i + 1;
  }
  bool f = true;
  i = 0;
  while ( i < N ) {
    if ( a[i] >= 0 && !b[i] ) f = false;
    if ( a[i] < 0 && !b[i] ) f = false;
    i = i + 1;
  }
  assert ( f ); 
}
