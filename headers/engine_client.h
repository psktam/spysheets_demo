#ifndef ENGINE_CLIENT_H
#define ENGINE_CLIENT_H

#include <arpa/inet.h>
#include <string>

namespace engine_client {

class EngineClient {
    private:
        int client_fd;
        struct sockaddr_in serv_addr;

    public:
        EngineClient(std::string server_address, int port_number);
        int get_connection_fd();
        void send_data(std::string);
        void close_connection();
};

}

#endif  // ENGINE_CLIENT_H