#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # Standard loopback interface address(localhost)
PORT = 65432        # Port to listen on(non - privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(4)

            if not data:
                continue

            requestid = int.from_bytes(data, byteorder='little')
            data = conn.recv(5)
            name = str(data, encoding='utf-8', errors='replace')
            data = conn.recv(4)
            scores = int.from_bytes(data, byteorder='little')
            print('Player name: ', name, 'Player scores: ', scores)


