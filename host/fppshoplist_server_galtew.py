from pynput.keyboard import Key, Controller, Listener
from datetime import datetime as dt # time
import re # regex
import os # path join
import socket # server-client
import time # sleep 
import threading # threads
import socket


# path=settings_server.SCRIPT_LOCATION
# location=""
# for l in path:
# 	location=os.path.join(location,l)

# lepsza opcja niż to wyżej: 
# PATH=os.path.dirname(os.path.abspath(__file__))
    
# FILES_LOCATION=location

# Tryb ( 0-FPP, 1-KLAWIATURA, 2-SILENT): 
MODE=2 

FN_KEY=Key.ctrl
FN_KEY_1=Key.ctrl_r
FN_KEY_2=Key.ctrl_l
START_KEY=Key.insert
EXIT_KEY=Key.esc

####################################################################
####	                   		HEADERS	                        ####
####################################################################

def getIp():
    # https://stackoverflow.com/questions/166506/finding-local-ip-addresses-using-pythons-stdlib
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(0)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except Exception:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP


# 

# client
HEADER=64 #  same as in server 
PORT=5050 # same as in server
FORMAT='utf-8' # same as in server
DISCONNECT_MSG="!DISCONNECT" # same as in server
VALIDATE_MSG="!VALIDATEFPP"
INCOMING_DATA_MSG="!INCOMING_DATA"

SERVER=getIp() #settings_server.COMPUTER_IP # server ip
ADDR=(SERVER,PORT)


items_list=[]
buttons=[]
bin_buttons=[]

keys_pressed=[]
keyboard_sym = Controller()

class item:
    def __init__(self, ID, N):
        self.id=ID
        self.n=N

####################################################################
####                            OTHERS                          ####
####################################################################

#print with timestamp
def printT(*args):
    print("{:02d}:{:02d}:{:02d}".format(dt.now().hour, dt.now().minute, dt.now().second), end=" ")
    for a in range(0,len(args)):
        print(args[a], end=" ")
    print("")

def getTime():
    return f"{dt.now().hour}:{dt.now().minute}:{dt.now().second}"

def closeApp():
    print("====================================")
    print("==    FPP SHOPLIST TRANSFER OFF  ===")
    print("====================================")


####################################################################
####                    SYMULATING KEYBOARD                     ####
####################################################################

def kb_printf_str(str):
    keyboard_sym.type(str)

def kb_print_k(k):
    keyboard_sym.press(k)
    keyboard_sym.release(k)

####################################################################
####                        PRINTING DATA                       ####
####################################################################

def printData(id,n,a):
    if MODE == 0: # fpp ready
        if a>0:
            kb_print_k(Key.insert)
        else:
            kb_print_k(Key.enter)
        kb_printf_str(id)
        kb_print_k(Key.enter)
        kb_printf_str(str(n)) # n - amount
        kb_print_k(Key.enter)
    else: # MODE == 2 # silent mode
        print(id,n)




####################################################################
####                       COMPILING DATA                       ####
####################################################################

def compileLine(data):
    id=data.split(':')[0]
    n=data.split(':')[1]
    if n[len(n)-1]=='0' and n[len(n)-2]=='.':
        n=n[0:len(n)-2]
        n=int(n)
    else:
        n=float(n)
    items_list.append(item(id, n))
    #print(len(items_list)) #

def compileAll():
    global accept_conn
    accept_conn=False
    #print(len(items_list)) #
    if MODE==2:
        kb_printf_str("--------------\n")
    n=0
    for itm in items_list:
        printData(itm.id, itm.n ,n)
        n+=1
    items_list.clear()
    printT(f"Printed {n} elements.")

    accept_conn=False
    printT("Done.")
    print("------------------------------------")
    keys_pressed.clear()

####################################################################
####                     CONNECTING TO CLIENT                   ####
####################################################################

server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(ADDR)

server_on=True
accept_conn=False
client_conn=False

def serverHandleClient(conn, addr):
    #print("Handling Client")
    global client_conn
    recieved_all=True

    while (1):
        n_l=conn.recv(HEADER).decode(FORMAT)
        n_l=int(n_l)
        message=conn.recv(n_l).decode(FORMAT)

        #print(message)
        time.sleep(0.5)

        if message == DISCONNECT_MSG:
            conn.close()
            break
        elif message == VALIDATE_MSG:
            # SECTION OF VALIDATING CONNECTION
            conn.send("Connection to FppShoplist host validated!".encode(FORMAT))
            #print("validation")
            time.sleep(1)
            if accept_conn:
                # print("conn accepted")
                conn.send("0".encode(FORMAT))
            elif not accept_conn and client_conn:
                # print("conn declined")
                conn.send("2".encode(FORMAT))
                conn.close()
                break
            else:
                # print("conn declined")
                conn.send("1".encode(FORMAT))
                conn.close()
                break
        elif message == INCOMING_DATA_MSG:
            client_conn=True
            if accept_conn:
                print(f"{getTime()} Connection acquired.")
                n_l=conn.recv(HEADER).decode(FORMAT)
                n_l=int(n_l)
                message=conn.recv(n_l).decode(FORMAT)
                if re.match(r'^n:[0-9]+$',message):
                    n=int(message.split(':')[1])
                    for itm in range(0,n):
                        n_l=conn.recv(HEADER).decode(FORMAT)
                        n_l=int(n_l)
                        recieved_data=conn.recv(n_l).decode(FORMAT)
                        #print(recieved_data)
                        compileLine(recieved_data)
                        # if recieved_data==r'^e:$':
                        #     recieved_all=False
                    e=conn.recv(1000).decode(FORMAT)
                    if re.match(r'^e:$',e):
                        recieved_all=False
                else:
                    recieved_all=False
                #ans
                if not recieved_all:
                    conn.send("1".encode(FORMAT))
                    print(f"{getTime()} ERROR: Data transfer corrupted!")
                    client_conn=False
                else:
                    conn.send("0".encode(FORMAT))
                    print(f"{getTime()} Data transfer done.")
                    threading.Thread(target=compileAll).start()
                    client_conn=False
                    conn.close()
                    break


def serverStart():
    server.listen()
    while server_on:
        conn, addr = server.accept()
        serverHandleClient(conn, addr)
        
####################################################################
####                    DETECTING KEY PRESS                     ####
####################################################################
# https://pythonhosted.org/pynput/keyboard.html 

def handleButton():
    global accept_conn
    global client_conn
    time_to_connect=10 # [s]
    if not accept_conn and not client_conn:
        accept_conn=True # akceptuj połączenia
        # interfejs:
        printT("Called out.")
        printT("Waiting for connection...")
        # czas oczekiwania na połączenie: 
        time.sleep(time_to_connect) 
        if accept_conn and not client_conn:
            accept_conn=False # przestań akceptować połączenia
            # interfejs:
            printT("Connection timeout!")
            printT("Done.")
            print("------------------------------------")
        if client_conn: 
            client_conn=False
            accept_conn=False

def on_press(key):
    if not key in keys_pressed:
        keys_pressed.append(key)

def on_release(key):
    if MODE==0 or MODE==1 or MODE==2:
        if len(keys_pressed)==2 and (FN_KEY_1 in keys_pressed or FN_KEY_2 in keys_pressed) and EXIT_KEY in keys_pressed:
            keys_pressed.remove(key)
            return False
        elif len(keys_pressed)==2 and (FN_KEY_1 in keys_pressed or FN_KEY_2 in keys_pressed) and START_KEY in keys_pressed:
            threading.Thread(target=handleButton).start()
    else:
        if len(keys_pressed)==2 and FN_KEY in keys_pressed and EXIT_KEY in keys_pressed:
            keys_pressed.remove(key)
            return False
        elif len(keys_pressed)==2 and FN_KEY in keys_pressed and START_KEY in keys_pressed:
            threading.Thread(target=handleButton).start()
        
    if key in keys_pressed:
        keys_pressed.remove(key)

def listenerStart():
    # Collect events until released
    with Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()
    closeApp()

####################################################################
####                   			MAIN        	                ####
####################################################################

print("====================================")
print("==    FPP SHOPLIST TRANSFER ON   ===")
print("====================================")

server_thread=threading.Thread(target=serverStart)
server_thread.start()
print(f"{getTime()} Server started.")

listener_thread=threading.Thread(target=listenerStart)
listener_thread.start()
print(f"{getTime()} Listener started.")

print("------------------------------------")
