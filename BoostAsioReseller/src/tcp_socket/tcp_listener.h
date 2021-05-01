#ifndef TCP_LISTENER
#define TCP_LISTENER
#pragma once
#include "detail/tcp_server.h"
#include "tcp_server_states.h"
#include <atomic>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>

namespace tcp_socket {
using namespace tcp_server_base;
class tcp_listener : protected tcp_server {
private:
  const boost::asio::ip::address ip_address_;
  const unsigned short port_ = 1;
  std::thread listener_thread_;
  std::size_t buffer_size_in_bytes_ = 1024;

  void start_listen();

public:
  tcp_listener(boost::asio::ip::address &&ip_address, unsigned short port,
               size_t buffer_size_in_bytes);

  ~tcp_listener();

  server_states open() override;
  server_states close() override;
};
} // namespace tcp_socket
#endif // TCP_LISTENER
