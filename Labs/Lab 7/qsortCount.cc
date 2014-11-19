#include <iostream>
#include <ctime>
#include <cstdlib>

int comps;
int * x;

void swap(int & a, int & b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int randint(int a, int b) {
  return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
  if (a >= b) return;
  int p = randint(a,b); // pivot
  swap(x[a], x[p]);
  int m = a;
  int i;
  // in-place partition:
  for (i = a+1; i <= b; i++) {
    comps++;
    if (x[i] < x[a])
      swap(x[++m], x[i]);
  }
  swap(x[a],x[m]);
  quicksort(a, m-1);
  quicksort(m+1, b);
}

int qc(int n) {
  int a = 0;
  int b = n;
  if (a >= b) return 0;
  int sum = 0;
  int p = randint(a,b); // pivot
  int i;
  // in-place partition:
  for (i = a+1; i <= b; i++) {
    sum++;
  }
  sum += qc(p-1);
  sum += qc(b-p-1);
  return sum;
}

float c(int n) {
  if (n <= 1) return 0;
  float sum = 0.0;
  for (int m=1; m <= n; m++)
    sum += n-1 + c(m-1) + c(n-m);
  return sum / n;
}

float memo_c(int n) {
  float cache[n+1];
  for (int i = 0; i <= n; i++) {
    cache[i] = 0;
  }
  for (int i = 2; i <= n; i++) {
    for (int m = 1; m <= i; m++) {
      cache[i] += i-1 + cache[m-1] + cache[i-m];
    }
    cache[i] /= n;
  }
  return cache[n];
}

#define NN 8000

int main(int argc, char *argv[]) {
  int avg;
  srand(time(0));
  x = new int[NN];

  for (int div = 8; div >= 1; div /= 2) {
    avg = 0;
    for (int rep = 1; rep <= 1000; rep++) {
      comps = 0;
      for (int i=0; i<NN/div; ++i) {
        x[i] = rand() % NN;
      }
      quicksort(0, NN/div - 1);
      avg += (comps - avg) / rep;
    }
    std::cout << "QSort on array of size " << NN/div << ": ";
    std::cout << avg << " comparisons (on average)" << std::endl;
  }

  for (int div = 8; div >= 1; div /= 2) {
    avg = 0;
    for (int rep = 1; rep <= 1000; rep++) {
      avg += (qc(NN/div - 1) - avg) / rep;
    }
    std::cout << "qc on array of size " << NN/div << ": ";
    std::cout << avg << " comparisons (on average)" << std::endl;
  }

  std::cout << "c[10]: " << c(10) << std::endl;
  std::cout << "memo_c(10): " << memo_c(14) << std::endl;

  delete[] x;
  return 0;
}
