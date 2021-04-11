#ifndef TCP_LISTENER
#define TCP_LISTENER
#pragma once
#include <atomic>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>

namespace tcp_socket {
class tcp_listener {
private:
  enum class listener_states { opening, opened, closing, closed };

  const boost::asio::ip::address ip_address_;
  const unsigned short port_;
  std::thread listener_thread_;
  std::atomic<listener_states> state_ = {listener_states::closed};
  std::size_t buffer_size_in_bytes_ = 1024;
  std::vector<std::uint8_t> buffer_;

  void start_listen();

public:
  tcp_listener(boost::asio::ip::address &&ip_address, unsigned short port,
               size_t buffer_size_in_bytes);

  ~tcp_listener();

  tcp_listener::listener_states open();
  tcp_listener::listener_states close();
};
} // namespace tcp_socket
#endif // TCP_LISTENER
