#include "../tcp_socket/tcp_listener.h"
#include <iostream>

int main() {
  tcp_socket::tcp_listener listener(
      boost::asio::ip::address::from_string("192.168.31.6"), 2000, 1024);
  listener.open();
  listener.close();

  return 0;
}
