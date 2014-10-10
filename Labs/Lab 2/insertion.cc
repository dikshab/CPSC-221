#include <iostream>
#include <cstdlib>
#include "insertion.h"

// insertion sort with several errors

void getArgs( int ac, char **av ) {
  int i;
  numInputs = ac - 1;
  for( i = 0; i < numInputs; i++ )
    x[i] = atoi( av[ i+1 ] );
}

void scootOver( int jj ) {
  int k;
  for( k = numY; k > jj; k-- )
    y[k] = y[ k-1 ];
}

void insert( int newY ) {
  int j;

  if( numY == 0 ) {
    y[0] = newY;
    return;
  }
  // Need to insert just before the first y element that newY is less than
  for( j=0; j< numY; j++ ) {
    if( newY < y[j] ) {
      // shift y[j], y[j+1], ... rightward before inserting newY
      scootOver( j );
      y[j] = newY;
      return;
    }
  }
  // otherwise, insert at end
  y[numY] = newY;
}

void processData() {
  for( numY = 0; numY < numInputs; numY++ ) 
    // insert new y in the proper place among y[0],....,y[numY-1]
    insert( x[ numY ] );
}

void printResults() {
  int i;
  for( i=0; i<numInputs; i++ )
    std::cout << y[i] << " ";
  std::cout << std::endl;
}

int main( int argc, char ** argv ) {
  getArgs( argc, argv );
  processData();
  printResults();
}
