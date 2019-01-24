import socket

#UDP_IP = "192.168.43.254"
UDP_IP = "127.0.0.1"
UDP_PORT = 5001
MESSAGE = '{"sender_id": 500,"receiver_id": 500,"data": {"function": "orderRoadMap","payload": ["1","","","","","","",""]}}'
##print("UDP target IP:", UDP_IP)
##print("UDP target port:", UDP_PORT)
##print("message:", MESSAGE)



#def sendMessageOnSocket(messageToSend):
#messageToSend = messageToSend.encode('UTF-8')
sock = socket.socket(socket.AF_INET, # Internet
             socket.SOCK_DGRAM) # UDP
sock.sendto(MESSAGE.encode('UTF-8'), (UDP_IP, UDP_PORT))


##sendMessageOnSocket(MESSAGE)
