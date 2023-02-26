"""
This module contains the code required for starting up a local server that only
serves one application at a time. One can imagine a world where one server can
serve multiple instances concurrently, but that is for another time.
"""
import socket
import struct
from . import core


def receive_message(sock_connection):
    """Receive a single message and prep it for parsing"""
    message_len = struct.unpack("!Q", sock_connection[0].recv(8))[0]
    message = b""

    while len(message) < message_len:
        remaining_bytes = message_len - len(message)
        message += sock_connection[0].recv(remaining_bytes)
    
    return message


def create_server(public:bool, port:int) -> socket.socket:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    address = "0.0.0.0" if public else "127.0.0.1"
    sock.bind((address, port))
    sock.listen()

    return sock


def run_server(sock: socket.socket):
    """
    This version only allows for one connection, but one can imagine a world 
    that can handle multiple concurrent connections, but that's not for me.

    Actually, maybe this thing should be run inside a generator. That might 
    allow for some concurrerncy without needing to resort to threading.
    """
    connection = sock.accept()

    while True:
        message = receive_message(connection[0])
        action_spec = core.parse_argument_struct(message)
        outputs = core.run_action(action_spec)

        # These should then be serialized and sent back to c++ world.
        print(outputs)