import socket
import time

UDP_IN_IP = "127.0.0.1"
#UDP_IN__IP = "192.168.43.187"
UDP_IN_PORT = 5000



#def socketReceptionRun():
sock = socket.socket(socket.AF_INET, # Internet
             socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IN_IP, UDP_IN_PORT))
while True:
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	print(data.decode("UTF-8"))


