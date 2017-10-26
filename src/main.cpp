#include <iostream>
#include "ergo.h"

using namespace std;
using namespace Ergo;

void increment(int value) {
  cout << "Value In: " << value << endl;

  value++;
  Operation::yield();

  cout << "Value out: " << value << endl;
}

int main(int argc, char **argv) {
  cout << "Starting" << endl;

  Operation a([]() {
    increment(10);
  });

  Operation b([]{
    increment(20);
  });

  a.resume();
  b.resume();
  b.resume();
  a.resume();
  a.resume();

  // With a while loop
  Operation c([]{
    increment(30);
  });

  while(!c.complete()) {
    c.resume();
  }

  cout << "Complete" << endl;
}
