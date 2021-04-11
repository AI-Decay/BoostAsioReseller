#include "tcp_listener.h"

#include <iostream>
using namespace tcp_socket;

tcp_listener::tcp_listener(boost::asio::ip::address &&ip_address,
                           unsigned short port, size_t buffer_size_in_bytes)
    : ip_address_(ip_address), port_(port),
      buffer_size_in_bytes_(buffer_size_in_bytes) {
  buffer_.resize(buffer_size_in_bytes_);
}

tcp_socket::tcp_listener::~tcp_listener() {
  if (listener_thread_.joinable())
    listener_thread_.join();
}

tcp_listener::listener_states tcp_listener::open() {
  if (state_ == listener_states::closed) {
    listener_thread_ = std::thread(&tcp_listener::start_listen, this);
    state_ = listener_states::opening;
  }

  return state_;
}

tcp_listener::listener_states tcp_listener::close() {
  if (state_ == listener_states::opened || state_ == listener_states::opening) {
    state_ = listener_states::closing;
    if (listener_thread_.joinable())
      listener_thread_.join();
  }

  return state_;
}

void tcp_listener::start_listen() {
  boost::asio::io_service service;
  boost::asio::ip::tcp::endpoint endpoint{ip_address_, port_};
  // boost::asio::ip::tcp::acceptor acceptor(service, endpoint);
  // std::unique_ptr<boost::asio::ip::tcp::socket> socket{
  //   std::make_unique<boost::asio::ip::tcp::socket>(service)};

  if (state_ == listener_states::opening) {
    //  acceptor.accept(*socket);
    //  socket->read_some(boost::asio::buffer(buffer_));
    state_ = listener_states::opened;
  }

  while (state_ == listener_states::opened) {
  }
}
