from time import sleep
import global_vars
import json

def  Client_Handler(conn,addr):
    print('Got connection from', addr )
    conn.send("welcome to my Chatroom...".encode())
    name = conn.recv(1024).decode()
    global_vars.clients_dic.update({name:conn})
    while True: 
 
        option = conn.recv(1024).decode()
        if(option == '1'):
            data1 = json.dumps(list(global_vars.clients_dic.keys()))
            conn.send(data1.encode())
        elif(option == '2'):
                
            data2 = conn.recv(1024).decode()
            send_list = json.loads(data2)
            print('from: '+ name + ' to ' + send_list[0] + ' :' + send_list[1])
            if(send_list[0] in global_vars.clients_dic.keys()):  ### cheking contact name
                send_conn = global_vars.clients_dic[send_list[0]]
                send_conn.send(data2.encode())      
                conn.send('sent'.encode())
            else:
                conn.send('Invalid Contact Name...'.encode()) 
                    

        elif(option == '4'):
            conn.close()
            del global_vars.clients_dic[name]    
            break
        else:
            continue

