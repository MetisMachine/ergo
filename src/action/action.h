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

using namespace std;

namespace Ergo {
  class Action {
  protected:
    function<void()> handler;

  private:
    packaged_task<void()> _task;
    future<void>          _future;
    thread                _thread;
    atomic<bool>          _enabled;

    bool started = false;
  public:
    void setFunction(function<void()> function);
    void init();
    void resume();
    void yield();
    bool complete();
  };
}
