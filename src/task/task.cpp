/**
 * Copyright (c) 2017 Wess Cope <me@wess.io>
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "task.h"

using namespace std;

namespace Ergo {
    Action *Task::running = nullptr;

    Task::Task(function<void()> block) {
    action = new Action();

    action->setFunction(block);
    action->init();
  }

  void Task::resume() {
    if(!action->complete()) {
      running = action;
      action->resume();
    }
  }

  bool Task::complete() {
    return action->complete();
  }

  void Task::yield() {
    if(running != nullptr) {
      running->yield();
    }
  }
}
