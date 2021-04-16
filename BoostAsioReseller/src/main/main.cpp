#include "../tcp_socket/tcp_listener.h"
#include <iostream>

int main() {
  tcp_socket::tcp_listener listener(boost::asio::ip::address_v4::any(), 100,
                                    100000);
  listener.open();
  listener.close();

  return 0;
}
