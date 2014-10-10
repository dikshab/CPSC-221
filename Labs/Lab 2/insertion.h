#ifndef INSERTION_H
#define INSERTION_H

int  x[10];	// input array
int  y[10];	// workspace array
int  numInputs;	// length of input array
int  numY = 0;	// current number of elements in y[]

void getArgs( int ac, char** av );
void scootOver( int jj );
void insert( int newY );
void processData();
void printResults();

#endif
