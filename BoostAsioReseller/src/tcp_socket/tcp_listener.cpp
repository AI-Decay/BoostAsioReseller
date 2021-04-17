#include "tcp_listener.h"

#include <iostream>
using namespace tcp_socket;

tcp_listener::tcp_listener(boost::asio::ip::address &&ip_address,
                           unsigned short port, size_t buffer_size_in_bytes)
    : ip_address_(ip_address), port_(port),
      buffer_size_in_bytes_(buffer_size_in_bytes) {
  buffer_.resize(buffer_size_in_bytes_);
  state_ = server_states::closed;
}

tcp_socket::tcp_listener::~tcp_listener() {
  if (listener_thread_.joinable())
    listener_thread_.join();
}

server_states tcp_listener::open() {
  if (state_ == server_states::closed) {
    listener_thread_ = std::thread(&tcp_listener::start_listen, this);
    state_ = server_states::opening;
  }

  return state_;
}

server_states tcp_listener::close() {
  if (state_ == server_states::opened || state_ == server_states::opening) {
    state_ = server_states::closing;
    if (listener_thread_.joinable())
      listener_thread_.join();
  }

  return state_;
}

void tcp_listener::start_listen() {
  boost::asio::io_service service;
  boost::asio::ip::tcp::endpoint endpoint{ip_address_, port_};
  boost::asio::ip::tcp::acceptor acceptor(service, endpoint);
  std::unique_ptr<boost::asio::ip::tcp::socket> socket{
      std::make_unique<boost::asio::ip::tcp::socket>(service)};

  if (state_ == server_states::opening) {
    acceptor.accept(*socket);
    service.run();
    state_ = server_states::opened;
  }
  while (state_ == server_states::opened) {
    socket->read_some(boost::asio::buffer(buffer_));
  }

  service.stop();
}
