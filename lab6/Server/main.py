import socket
serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv.bind(('0.0.0.0', 8081))
serv.listen(5)
while True:
  conn, addr = serv.accept()

  while True:
    from_client = ''
    data = conn.recv(4096)
    if not data: break
    from_client += data.decode('utf8')
    print (from_client)
    conn.send(from_client.upper().encode())
  conn.close()
print ('client disconnected and shutdown')