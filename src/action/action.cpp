/**
 * Copyright (c) 2017 Wess Cope <me@wess.io>
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "action.h"
#include <unistd.h>
#include <chrono>

using namespace std;

namespace Ergo {

  void Action::init() {}

  void Action::setFunction(std::function<void()> function) {
    handler = function;
  }

  void Action::resume() {
    _enabled = true;

    if(!started) {
      _task = packaged_task<void()>([&] () {
        handler();
      });

      _future = _task.get_future();
      _thread = thread(move(_task));

      _thread.detach();

      started = true;
    }

    while(_enabled && !complete()) {}
  }

  void Action::yield() {
    _enabled = false;
    while(_enabled == false) {
      this_thread::sleep_for(chrono::milliseconds(500));
    }
  }

  bool Action::complete() {
    if(!started) { 
      return false; 
    }

    auto status = _future.wait_for(chrono::milliseconds(0));

    return status == future_status::ready;
  }
}
