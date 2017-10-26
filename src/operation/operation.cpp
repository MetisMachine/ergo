/**
 * Copyright (c) 2017 Wess Cope <me@wess.io>
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "operation.h"

using namespace std;

namespace Ergo {
  Task *Operation::running = nullptr;

  Operation::Operation(function<void()> block) {
    task = new Task();

    task->setFunction(block);
    task->init();
  }

  void Operation::resume() {
    if(!task->complete()) {
      running = task;
      task->resume();
    }
  }

  bool Operation::complete() {
    return task->complete();
  }

  void Operation::yield() {
    if(running != nullptr) {
      running->yield();
    }
  }
}
