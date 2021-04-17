#ifndef TCP_SERVER
#define TCP_SERVER
#pragma once
#include "../tcp_server_states.h"
#include <atomic>

namespace tcp_server_base {

class tcp_server {
protected:
  std::atomic<server_states> state_;
  virtual server_states open() = 0;
  virtual server_states close() = 0;
  virtual ~tcp_server() = 0;
};

inline tcp_server::~tcp_server() {}

} // namespace tcp_server_base

#endif // TCP_SERVER
