
import socket			 
import sys
import json
import os

def prYellow(skk): print("\033[93m {}\033[00m" .format(skk)) 
def prCyan(skk): print("\033[96m {}\033[00m" .format(skk)) 
def prGreen(skk): print("\033[92m {}\033[00m" .format(skk))

s = socket.socket()		 

port = int(sys.argv[2])			

s.connect(('127.0.0.1', port)) 

os.system('clear') 
prGreen(s.recv(1024).decode())
s.send(sys.argv[1].encode())  #sending name
while(True):
   
    option = input('\n -Choose one of options: \n 1-Clients list 2-Send 3-Recieve 4-Exit \n')
    s.send(option.encode())
    if (option == '1'):
        data1 = s.recv(1024).decode()
        clients_list = json.loads(data1)
        prYellow((clients_list))
    elif (option == '2'):
        send_list = input('Enter your contcat name and message, like this: Name-Msg \n').split('-')
        data2 = json.dumps(send_list)
        s.send(data2.encode())
        prCyan(s.recv(1024).decode())
    elif (option == '3'):
        print('listening for Message...')
        data3 = s.recv(1024).decode()
        recv_list = json.loads(data3)
        prCyan('From: %s' %(recv_list[0]))
        prCyan('Message: %s' %recv_list[1])
    elif (option == '4'):
        s.close()
        break
    else:
        continue
	 

