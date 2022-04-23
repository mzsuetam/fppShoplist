#==================================================================#
#==================================================================#
#===	              	   USTAWIENIA KLIENTA                   ===#
#==================================================================#
#==================================================================#

####################################################################
####	              	      LOKALIZACJA                       ####
####################################################################
# LOKALIZACJA SKRYPTU : 
#SCRIPT_LOCATION=["/","home","m_zsuetam","prog","python","fppshoplist"]

####################################################################
####	              	   USTAWIENIA EKRANU                    ####
####################################################################
# WYSOKOŚĆ I SZEROKOŚĆ EKRANU:
WINDOW_HEIGHT=960	
WINDOW_WIDTH=1280
# SZEROKOŚĆ PANELU:
PANEL_WIDTH=250
# PEŁNY EKRAN:
FULL_SCREEN=False

####################################################################
####	              	   USTAWIENIA SIECI                     ####
####################################################################

SSID_LIST={
	"mieszkanie":"Modem 5G test 400% mocy",
	"dom":"maz"
}
IP_LIST={
	"mieszkanie":"192.168.0.178",
	"dom":"192.168.1.216"
}
chosen_item="mieszkanie"

# SSID SIECI:
NETWORK_SSID=SSID_LIST[chosen_item]
# IP SERWERA
SERVER_IP=IP_LIST[chosen_item]
# PORT SERWERA
SERVER_PORT=5050