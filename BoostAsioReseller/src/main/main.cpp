#include "../tcp_socket/tcp_listener.h"
#include <iostream>

int main() {
  tcp_socket::tcp_listener listener(
      boost::asio::ip::address_v4({192, 168, 31, 6}), 1, 64);
  listener.open();
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  listener.close();

  return 0;
}
