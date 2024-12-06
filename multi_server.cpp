#include "Server.h"

int main(void) {
    TCP_Server s(PORT);

    s.bind_addr_info();

    s.start_listening();

    s.handle_with_client();

    return 0;
}