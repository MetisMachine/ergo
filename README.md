
Ergo
====
Ergo is an easy to use concurrent operation library for C++11 and up.


Usage
=====

```c++

// Function to call within the operation.
void plusplus(int value) {
  cout << "Value In: " << value << endl;

   // We increase the value.
  value++;
  
  // Let's return.
  Ergo::Operation::yield();

  cout << "Value out: " << value << endl;
}

int main(int argc, char **argv) {
  cout << "Starting" << endl;

  // Create a new operation
  Ergo::Operation a([]() {
    plusplus(10);
  });

  // Create another operation
  Ergo::Operation b([]{
    plusplus(20);
  });

  a.resume();
  b.resume();
  b.resume();
  a.resume();
  a.resume();

  // Create an operation to use With a while loop
  Ergo::Operation loopy([]{
    plusplus(30);
  });

  // Loop and wait for the _loopy_ operation to finish.
  while(!loopy.complete()) {
    loopy.resume();
  }

  cout << "Complete" << endl;
}

```