#include <array>
#include <arpa/inet.h>
#include <cstdint>
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>
#include "engine_client.h"


using namespace engine_client;


EngineClient::EngineClient(std::string server_address, int port_number) {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("Socket creation error");
    }

    // Convert from human-readable IP address to ones that our computer 
    // overlords can understand.
    if (inet_pton(AF_INET, server_address.c_str(), &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address/address not supported");
    }

    // Now create and store the connection.
    int status;
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        throw std::runtime_error("Connection failed");
    }
}


int EngineClient::get_connection_fd() {
    return client_fd;
}


/**
 * Convert the provided number into network-order 8-character string. We can
 * now send up to 4GB of data at a time. Hopefully they won't ever need to 
 * transfer more than this at a time because this is stupid.
*/
std::array<unsigned char, 8> gross_htonll(uint64_t input) {
    // Network order is big-endian.
    unsigned char masker(0xff);
    std::array<unsigned char, 8> internal_array;
    internal_array[0] = static_cast<unsigned char>(input >> 56) & masker;
    internal_array[1] = static_cast<unsigned char>(input >> 48) & masker;
    internal_array[2] =  static_cast<unsigned char>(input >> 40) & masker;
    internal_array[3] =  static_cast<unsigned char>(input >> 32) & masker;
    internal_array[4] =  static_cast<unsigned char>(input >> 24) & masker;
    internal_array[5] =  static_cast<unsigned char>(input >> 16) & masker;
    internal_array[6] =  static_cast<unsigned char>(input >> 8) & masker;
    internal_array[7] =  static_cast<unsigned char>(input >> 0) & masker;

    return internal_array;
}

void EngineClient::send_data(std::string data) {
    auto length_as_bytes = gross_htonll(data.length());

    send(client_fd, length_as_bytes.begin(), 8, 0);
    send(client_fd, data.c_str(), data.length(), 0);
}

void EngineClient::close_connection() {
    close(client_fd);
}
