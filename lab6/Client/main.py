import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('0.0.0.0', 8081))

command = ''
while command != "end":
    command = input()
    client.send(command.encode())
    from_server = client.recv(4096)

    print (from_server.decode())

client.close()