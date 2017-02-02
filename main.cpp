#include <iostream>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <fstream>
#include <list>

using namespace std;
mutex mtx;
list<int> primeList;


bool isPrime(int number) {
  if (number<2) return false;
  if (number == 2 || number == 3) return true;
  if (number%2 == 0 || number%3 == 0) return false;
  int sqrtNumber = (int) sqrt(number) + 1;
  for (int i = 6; i <= sqrtNumber; i += 6) {
    if (number%(i-1) == 0 || number%(i+1) == 0) return false;
  }
  return true;
}

void printPrimes(int begin, int end) {
  for (int i = begin; i <= end; i++) {
    if (isPrime(i)) {
      mtx.lock();
      std::cout << i << endl;
      primeList.push_back(i);
      mtx.unlock();
    }
  }
}

void printPrimesMultithread(int begin, int end, int numThreads) {
  vector<thread> threads;
  int each = end/numThreads;
  int start = begin;
  int finish = start + each - 1;
  
  for (int i = 0; i < numThreads; i++) {
    threads.emplace_back(printPrimes, start, finish);
    start += each;
    finish += each;
  }
  
  for (auto& thread : threads) {
    thread.join();
  }
  
  primeList.sort();
  for (int prime : primeList) {
    std::cout << prime << std::endl;
  }
}

int main() {
  std::cout << "Hello World!\n";
  printPrimesMultithread(1, 5000, 2);
  return 0;
}






