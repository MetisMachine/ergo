/**
 * Copyright (c) 2017 Wess Cope <me@wess.io>
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <functional>
#include <future>
#include <thread>
#include <atomic>
#include <ergo.h>

#include "action/action.h"

namespace Ergo {
class Task {
  private:
    Action *action;
    static Action *running;

  public:
    Task(std::function<void()> block);
    void resume();
    bool complete();

    static void yield();
  };  
}
