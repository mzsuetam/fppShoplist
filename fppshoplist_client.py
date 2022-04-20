#!/usr/bin/python3
# FPPshoplist Mateusz Mazur 2022

from tkinter import *
from pynput.keyboard import Key, Controller, Listener
import os
import subprocess as sp
import socket
import errno
from socket import error as socket_error
import time

####################################################################
####                          SETTINGS	                        ####
####################################################################

import resources.settings_client as settings_client

# Pallete:
P_BLACK="#000000"
P_BLUE="#14213D"
P_ORANGE ="#FCA311"
P_GREY ="#E5E5E5"	
P_WHITE ="#FFFFFF"

TEXT_C=P_BLACK
LIST_BG_C=P_WHITE
LIST_EL_B=P_GREY
LIST_COVER=P_GREY
KB_BG_C=P_GREY
SCR_C=P_BLUE
HEADER_C=P_BLUE
KB_SEP_C=P_BLUE
BUT_ADD_C=P_ORANGE
BUT_C=P_BLUE
BUT_KB_C=P_WHITE

W_HEIGHT=settings_client.WINDOW_HEIGHT
W_WIDTH=settings_client.WINDOW_WIDTH
W_KB_WIDTH=settings_client.PANEL_WIDTH
SCR_WIDTH=W_KB_WIDTH/10
FULL_SCREEN=settings_client.FULL_SCREEN

PT_SCALE=W_KB_WIDTH/250

# path=settings_client.SCRIPT_LOCATION
# location=""
# for l in path:
# 	location=os.path.join(location,l)
# icon_path=os.path.join(location,"resources","icon.png")
# img_bin_path=os.path.join(location,"resources","imgs","bin.png")
# img_backspace_path=os.path.join(location, "resources","imgs","backspace.png")

PATH=os.path.dirname(os.path.abspath(__file__))
icon_path=os.path.join(PATH,"resources","icon.png")
img_bin_path=os.path.join(PATH,"resources","imgs","bin.png")
img_backspace_path=os.path.join(PATH, "resources","imgs","backspace.png")
backup_file_path=os.path.join(PATH, "backup", "backup.txt")

network_ssid=settings_client.NETWORK_SSID

####################################################################
####	                   		HEADERS	                        ####
####################################################################

# client
HEADER=64 #  same as in server 
PORT=settings_client.SERVER_PORT # same as in server
FORMAT='utf-8' # same as in server
DISCONNECT_MSG="!DISCONNECT" # same as in server
SERVER=settings_client.SERVER_IP # server ip
ADDR=(SERVER,PORT)

items_list=[]
buttons=[]
bin_buttons=[]

class item:
	def __init__(self, ID, N):
		self.id=ID
		self.n=N

keyboard_sym = Controller()

def kb_print_k_T(k):
    keyboard_sym.press(k)
    keyboard_sym.release(k)

####################################################################
####                   		WINDOW LAYOUT                       ####
####################################################################

root=Tk()
root.title("FPP SHOPLIST DEALER")
root.geometry("{}x{}".format(W_WIDTH, W_HEIGHT))
root.resizable(width=False, height=False)
root.attributes('-fullscreen',FULL_SCREEN)
icon = PhotoImage(file=icon_path)
root.iconphoto(False, icon)

w_ls=Frame(root, width=W_WIDTH-W_KB_WIDTH, height=W_HEIGHT, bg=LIST_BG_C)
w_ls.pack_propagate(False) 
w_ls.place(x=0, y=0)
w_kb=Frame(root, width=W_KB_WIDTH, height=W_HEIGHT, bg=KB_BG_C)
w_kb.pack_propagate(False) 
w_kb.place(x=W_WIDTH-W_KB_WIDTH, y=0)

####################################################################
####                       	 LIST SECTION                       ####
####################################################################

def refreshBattery():
	batt_level='acpi | head -1 | egrep -o [0-9]{2,3}% | egrep -o [0-9]{2,3}'
	batt_level=int(sp.getoutput(batt_level))
	text=f"Bat: {batt_level}%"
	if sp.getoutput('acpi | head -1 | egrep " (c|C)harging"'):
		text+=" ⚡"
	if  20 > batt_level:
		color="red"
	elif  False and batt_level > 90:
		color="green"
	else:
		color="white"
	batt_label.config(text=text, fg=color)
	root.after(10000, refreshBattery)

fr=Frame(w_ls, height=W_KB_WIDTH//5, width=W_WIDTH-W_KB_WIDTH, bg=HEADER_C, padx=W_KB_WIDTH//25, pady=W_KB_WIDTH//25)
fr.pack()
fr.pack_propagate(False)
#Label(fr, text="F.P.H.U. Galtew", bg=HEADER_C, fg=P_WHITE, font=f"none {int(18*PT_SCALE)}").place(x=0, y=0)
Label(fr, text="FPP Shoplist 1.0", bg=HEADER_C, fg=P_WHITE, font=f"none {int(18*PT_SCALE)} bold").place(x=0, y=0)
batt_label=Label(fr, text=f"Bat: -", bg=HEADER_C, fg=P_WHITE, anchor='e', font=f"none {int(18*PT_SCALE)}")
batt_label.place(x=W_WIDTH-W_KB_WIDTH-200-20, y=0, width=200)
refreshBattery()
# Label(fr, text="SYMBOL", bg=HEADER_C, fg=P_WHITE, font=f"none {int(18*PT_SCALE)}").place(x=0, y=0)
# Label(fr, text="ILOŚĆ", bg=HEADER_C, fg=P_WHITE, font=f"none {int(18*PT_SCALE)}).place(x=200, y=0)

scroll_box = Frame(w_ls) # scroll_box for scrollbar and its content
scroll_container = Canvas(scroll_box, width=W_WIDTH-W_KB_WIDTH-SCR_WIDTH, height=W_HEIGHT-W_KB_WIDTH//5, bg=LIST_BG_C) # scroll_container, so elements can be draw in a window
scrollbar = Scrollbar(scroll_box, orient="vertical", command=scroll_container.yview, width=SCR_WIDTH, bg=SCR_C, activebackground=SCR_C, troughcolor=LIST_BG_C, bd=0) #scrolbar
scroll_container_content = Frame(scroll_container, bg=LIST_BG_C) # conteiner for all the content

scroll_container_content.bind("<Configure>",lambda e: scroll_container.configure(scrollregion=scroll_container.bbox("all"))) # conteiner height depends on its elements
scroll_container.create_window((0, 0), window=scroll_container_content, anchor="nw")
scroll_container.configure(yscrollcommand=scrollbar.set)

img_bin=PhotoImage(file=img_bin_path)

def itmRemove(itm):
	items_list.remove(itm)
	printList()

def removeAll(ans, bey, ben):
	if ans:
		bin_buttons.clear()
		items_list.clear()
		printList()
	bey.destroy()
	ben.destroy()

def removeAllMenu(remove_all_fr):
	bey=Button(remove_all_fr, text="Usuń wszystkie!", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=lambda: removeAll(True, bey, ben), bg=BUT_C, activebackground=P_WHITE, bd=0)
	bey.place(x=0, y=0, width=(W_WIDTH-W_KB_WIDTH)//2, height=W_KB_WIDTH//5)
	ben=Button(remove_all_fr, text="Anuluj!", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=lambda: removeAll(False, bey, ben), bg=BUT_C, activebackground=P_WHITE, bd=0)
	ben.place(x=(W_WIDTH-W_KB_WIDTH)//2, y=0, width=(W_WIDTH-W_KB_WIDTH)//2, height=W_KB_WIDTH//5)

def restorePreviousList():
	try:
		with open(backup_file_path, "r") as backup_file:
			for line in backup_file:
				id=int(line.split(":")[0])
				n=float(line.split(":")[1])
				items_list.append(item(id,n))
		printList()
	except:
		input_error_l.config(text = "Błąd przywracania!")
		

def printList():
	for itm_fr in scroll_container_content.winfo_children():
		itm_fr.destroy()
	j=1
	i=1
	if len(items_list)%2==0:
		j=0
	for itm in items_list:
		if j%2==0:
			item_bg=LIST_BG_C
		else:
			item_bg=LIST_EL_B
		j+=1
		fr1=Frame(scroll_container_content, height=W_KB_WIDTH//5, width=W_WIDTH, bg=item_bg, padx=W_KB_WIDTH//25, pady=W_KB_WIDTH//25)
		fr1.pack()
		fr1.pack_propagate(False)
		Label(fr1, text="{:2d}: s. {}".format(i,itm.id), bg=item_bg, font=f"none {int(20*PT_SCALE)}").place(x=0, y=0)
		Label(fr1, text="{:g}".format(itm.n), bg=item_bg, font=f"none {int(20*PT_SCALE)}").place(x=(W_WIDTH-W_KB_WIDTH)//2-10, y=0)
		b1=Button(fr1, height=25, width=25, image=img_bin, command=lambda itm=itm: itmRemove(itm), bg=item_bg, bd=0)
		b1.place(x=W_WIDTH-W_KB_WIDTH-10-SCR_WIDTH-45, y=0)
		bin_buttons.append(b1)
		i+=1
	if len(items_list) > 0:
		remove_all_fr=Frame(scroll_container_content, height=W_KB_WIDTH//5, width=W_WIDTH, bg=HEADER_C, padx=0, pady=0)
		remove_all_fr.pack()
		b_ra=Button(remove_all_fr, height=25, width=25, text="Usuń wszystkie!", font=f"none {int(20*PT_SCALE)}", fg=P_BLACK, command=lambda: removeAllMenu(remove_all_fr), bd=0)
		b_ra.place(x=0, y=0, height=W_KB_WIDTH//5, width=W_WIDTH-W_KB_WIDTH-SCR_WIDTH)
	else:
		restore_previous_list=Frame(scroll_container_content, height=W_KB_WIDTH//5, width=W_WIDTH, bg=HEADER_C, padx=0, pady=0)
		restore_previous_list.pack()
		b_ra=Button(restore_previous_list, height=25, width=25, text="Przywróć poprzednią listę", font=f"none {int(20*PT_SCALE)}", fg=P_BLACK, command=lambda: restorePreviousList(), bd=0)
		b_ra.place(x=0, y=0, height=W_KB_WIDTH//5, width=W_WIDTH-W_KB_WIDTH-SCR_WIDTH)

	
	
scroll_box.pack()
scroll_container.pack(side=LEFT, fill=BOTH)
scrollbar.pack(side=RIGHT, fill=Y)


printList()

####################################################################
####                       KEYBOARD SECTION                     ####
####################################################################

def add_item():
	id=input_id.get()
	n=input_amount.get()
	input_id.delete(0, END)
	input_amount.delete(0, END)
	err=False
	try:
		id=int(id)
		n=float(n)
	except:
		err=True
		input_error_l.config(text = "Niepoprawne dane!")
	if err==False:
		newItem=item(id,n)
		items_list.append(newItem)
		printList()
		input_error_l.config(text = "")
		# print("s.{} {}".format(id,n))
	input_id.focus()

def clearInputs():
	input_id.delete(0, END)
	input_amount.delete(0, END)
	input_error_l.config(text = "")
	if not ask_transfer:
		transfer_error_l.config(text = "")

def exitApp(ans, bey, ben):
	if ans:
		root.destroy()
	else:
		bey.destroy()
		ben.destroy()
		#input_exit_l.config(text="")

def exitAppMenu():
	bey=Button(w_kb, text="Wyjdź!", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=lambda: exitApp(True, bey, ben), bg=BUT_C, activebackground=P_WHITE, bd=0)
	bey.place(x=0, y=0, width=W_KB_WIDTH//2, height=W_KB_WIDTH//5)
	ben=Button(w_kb, text="Anuluj!", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=lambda: exitApp(False, bey, ben), bg=BUT_C, activebackground=P_WHITE, bd=0)
	ben.place(x=W_KB_WIDTH//2, y=0, width=W_KB_WIDTH//2, height=W_KB_WIDTH//5)
	#input_exit_l.config(text="Na pewno?")
	
# def transfer data() is in DATA TRANSFER section

butt_rm=Button(w_kb, text="WYJDŹ", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=exitAppMenu, bg=BUT_C, activebackground=P_WHITE, bd=0)
butt_rm.place(x=0, y=0, width=W_KB_WIDTH, height=W_KB_WIDTH//5)
#input_exit_l=Label(w_kb, text="", fg=BUT_C, bg=KB_BG_C, font=f"none {int(18*PT_SCALE)}")
#input_exit_l.place(x=0,y=60,height=30, width=W_KB_WIDTH)

fr1=Frame(w_kb, bg=KB_BG_C) #KB_BG_C
fr1.place(x=0,y=W_KB_WIDTH//5+W_KB_WIDTH//5+25,height=W_KB_WIDTH, width=W_KB_WIDTH),

LAB_H=30
INP_H=42
BRE_H=8

lab_id=Label(fr1, text="Symbol:", bg=KB_BG_C, font=f"none {int(18*PT_SCALE)}")
lab_id.place(x=0,y=0,height=30, width=W_KB_WIDTH)
input_id=Entry(fr1, width=15, font=f"none {int(18*PT_SCALE)}", wrap=None, background="white")
input_id.place(x=0,y=LAB_H+BRE_H,height=42, width=W_KB_WIDTH)

lab_amount=Label(fr1, text="Ilość:", bg=KB_BG_C, font=f"none {int(18*PT_SCALE)}")
lab_amount.place(x=0,y=LAB_H+3*BRE_H+INP_H,height=30, width=W_KB_WIDTH)
input_amount=Entry(fr1, width=15, font=f"none {int(18*PT_SCALE)}", background="white")
input_amount.place(x=0,y=2*LAB_H+4*BRE_H+INP_H,height=42, width=W_KB_WIDTH)

input_error_l=Label(fr1, text="", fg="red", bg=KB_BG_C, font=f"none {int(18*PT_SCALE)}")
input_error_l.place(x=0,y=2*LAB_H+6*BRE_H+2*INP_H,height=30, width=W_KB_WIDTH)


img_backspace=PhotoImage(file=img_backspace_path)

kb_box=Frame(w_kb, bg=KB_BG_C)
kb_box.place(x=0,y=W_KB_WIDTH+130, height=W_KB_WIDTH*5//3, width=W_KB_WIDTH)
for i in range(9,0,-1):
	butt_kb=Button(kb_box, text=i, font=f"none {int(18*PT_SCALE)} bold", command=lambda i=i: kb_print_k_T('{}'.format(i)), bd=1)
	butt_kb.place(x=W_KB_WIDTH//3*(((i-1)%3))+1%3%3, y=W_KB_WIDTH//3*((9-i)//3)+1%3%3, width=W_KB_WIDTH//3, height=W_KB_WIDTH//3)
	buttons.append(butt_kb)
butt_kb=Button(kb_box, text=0, font=f"none {int(18*PT_SCALE)} bold", command=lambda: kb_print_k_T('0'), bd=1)
butt_kb.place(x=W_KB_WIDTH//3*(1)+1%3%3, y=W_KB_WIDTH//3*(3)+1%3%3, width=W_KB_WIDTH//3, height=W_KB_WIDTH//3)
buttons.append(butt_kb)
butt_kb=Button(kb_box, text=".",font=f"none {int(18*PT_SCALE)} bold", command=lambda: kb_print_k_T('.'), bd=1)
butt_kb.place(x=W_KB_WIDTH//3*(0)+1%3%3, y=W_KB_WIDTH//3*(3)+1%3%3, width=W_KB_WIDTH//3, height=W_KB_WIDTH//3)
buttons.append(butt_kb)
butt_kb=Button(kb_box, image=img_backspace, command=lambda: kb_print_k_T(Key.backspace), bd=1)
butt_kb.place(x=W_KB_WIDTH//3*(2)+1%3%3, y=W_KB_WIDTH//3*(3)+1%3%3, width=W_KB_WIDTH//3, height=W_KB_WIDTH//3)
buttons.append(butt_kb)
butt_kb=Button(kb_box, text="CE",font=f"none {int(18*PT_SCALE)} bold", command=lambda: clearInputs(), bd=1)
butt_kb.place(x=W_KB_WIDTH//3*(0)+1%3%3, y=W_KB_WIDTH//3*(4)+1%3%3, width=W_KB_WIDTH//3, height=W_KB_WIDTH//3)
buttons.append(butt_kb)
butt_kb=Button(kb_box, text="DODAJ", bg=BUT_ADD_C, font=f"none {int(18*PT_SCALE)} bold", command=add_item, bd=1)
butt_kb.place(x=W_KB_WIDTH//3*(1)+1%3%3, y=W_KB_WIDTH//3*(4)+1%3%3, width=W_KB_WIDTH//3*2, height=W_KB_WIDTH//3)
buttons.append(butt_kb)


transfer_error_l=Label(w_kb, text="", bg=KB_BG_C, font=f"none {int(18*PT_SCALE)}")
transfer_error_l.place(x=0, y=W_HEIGHT-W_KB_WIDTH//3-75, width=W_KB_WIDTH, height=75)
butt_tr=Button(w_kb, text="PRZEŚLIJ", font=f"none {int(20*PT_SCALE)} bold", command=lambda: transferDataButt(), bg=BUT_ADD_C, activebackground=P_WHITE, bd=0)
butt_tr.place(x=0, y=W_HEIGHT-W_KB_WIDTH//3, width=W_KB_WIDTH, height=W_KB_WIDTH//3)
buttons.append(butt_tr)


####################################################################
####                   		DATA TRANSFER        	            ####
####################################################################

def wifiConnect(ssid, passwd=None):
	status=sp.getoutput(f'nmcli | grep "connected to {ssid}"')
	if status!="":
		return 1
	passwd_command=""
	if passwd==True:
		passwd_command="--ask"
	elif passwd:
		passwd_command=f'password "{passwd}"'
	os.system(f'nmcli dev wifi connect "{ssid}" {passwd_command}')
	status=sp.getoutput(f'nmcli | grep "connected to {ssid}"')
	if status!="":
		return 1
	return 0

def initSocketConnection():
	global client
	client=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client.connect(ADDR)

def sendSocket(msg):
	message=msg.encode(FORMAT)
	msg_l=len(msg)
	send_msg_l=str(msg_l).encode(FORMAT)
	send_msg_l+=b' '*(HEADER-len(send_msg_l))
	client.send(send_msg_l)
	client.send(message)

def recieveSocket():
	return client.recv(2048).decode(FORMAT)

def disconnectSocket():
	sendSocket(DISCONNECT_MSG)

curtain=None
def lockInterface(state):
	global curtain
	if state:
		curtain = Label(w_ls, text="Czekaj...",fg=HEADER_C, font=f"none {int(20*PT_SCALE)} bold", bg=LIST_COVER)
		curtain.place(x=0,y=W_KB_WIDTH//5, width=W_WIDTH-W_KB_WIDTH-SCR_WIDTH, height=W_HEIGHT-W_KB_WIDTH//5)
		# for but in bin_buttons:
		#	but.config(state=DISABLED)
		for but in buttons:
			but.config(state=DISABLED)
		input_id.config(state=DISABLED)
		input_amount.config(state=DISABLED)
	elif not state:
		curtain.destroy()
		# for but in bin_buttons:
		# 	but.config(state=NORMAL)
		for but in buttons:
			but.config(state=NORMAL)
		input_id.config(state=NORMAL)
		input_amount.config(state=NORMAL)

def backupList():
	try:
		with open(backup_file_path, "w") as backup_file:
			for itm in items_list:
				backup_file.write(f"{itm.id}:{itm.n}\n")
	except:
		pass

def transferData():
	if len(items_list)!=0:	
		backupList()
		transfer_error_l.config(fg="black", text = "Łączenie...")
		lockInterface(True)
		Tk.update(root)
		if wifiConnect(network_ssid):
			transfer_error_l.config(fg="black", text = "Przesyłanie...")
			connected=True	
			try:
				initSocketConnection()
			# except socket_error as serr:
			# 	if serr.errno != errno.ECONNREFUSED:
			# 		raise serr
			# 	# błąd połączenia z serwerem:
			# 	connected=False	
			except:
				# błąd połączenia z serwerem:
				connected=False	
			if connected:
				server_ans=recieveSocket()
				if server_ans=="0": # 0 - ok 
					# poprawnie połączono z serwerem:
					sendSocket(f"n:{len(items_list)}") # ile będzie produktów?
					for i in items_list: #przesłanie wszystkich produktów 
						sendSocket(f"{i.id}:{i.n}") # w formacie symbol:ilość
					sendSocket("e:") # ile będzie produktów?
					if recieveSocket()=="1": # 1 - error 
						transfer_error_l.config(fg="red", text = "Błąd przesyłania!\nSpróbuj ponowić!")
					else: # czyszczenie listy jeżeli dane zostały otrzymane pomyślnie
						# bin_buttons.clear()
						# items_list.clear()
						# printList()
						transfer_error_l.config(fg="black", text = "Przesyłanie\nzakończone!")
				elif server_ans=="1":
					transfer_error_l.config(fg="red", text = "Serw. odm. poł.!\n(brak CTRL+INS)")
				elif server_ans=="2":
					transfer_error_l.config(fg="red", text = "Serwer zajęty!")
				#disconnectSocket()
			else:
				transfer_error_l.config(fg="red", text = "Błąd serwera!")
		else:
			transfer_error_l.config(fg="red", text = "Błąd sieci!")
		lockInterface(False)
	else:
		transfer_error_l.config(fg="red", text = "Lista jest pusta!")


def transferDataMenu(ans, bty, btn):
	if ans:
		transferData()
	else:
		transfer_error_l.config(fg="black", text = "")
	bty.destroy()
	btn.destroy()
	global ask_transfer
	ask_transfer=False

ask_transfer=False

def transferDataButt():
	global ask_transfer
	ask_transfer=True
	bty=Button(w_kb, text="Wyślij!", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=lambda: transferDataMenu(True, bty, btn), bg=BUT_C, activebackground=P_WHITE, bd=0)
	bty.place(x=0, y=W_HEIGHT-W_KB_WIDTH//3, width=W_KB_WIDTH//2, height=W_KB_WIDTH//3)
	btn=Button(w_kb, text="Anuluj!", font=f"none {int(18*PT_SCALE)}", fg=P_WHITE, command=lambda: transferDataMenu(False, bty, btn), bg=BUT_C, activebackground=P_WHITE, bd=0)
	btn.place(x=W_KB_WIDTH//2, y=W_HEIGHT-W_KB_WIDTH//3, width=W_KB_WIDTH//2, height=W_KB_WIDTH//3)
	#transfer_error_l.config(fg="black", text = "Na pewno?")



####################################################################
####                   			OTHERS        	                ####
####################################################################

input_id.focus()

root.mainloop()