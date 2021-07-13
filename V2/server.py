from threading import Thread
import socket			 
import sys
from Client_Handler import *
import global_vars
import os

os.system('clear')

global_vars.init()

s = socket.socket()		 
print ("Socket successfully created")

port = int(sys.argv[1])	
s.bind(('127.0.0.1', port))		 
print ("socket binded to %s" %(port) )

s.listen(5)	 
print ("socket is listening")			
while(True):
     conn, addr = s.accept()
     Thread(target=Client_Handler, args=(conn,addr)).start()


