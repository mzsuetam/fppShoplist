#!/bin/bash
if [ ! -f "var/tmp/fpp_shoplist_running" ]
then
	touch "var/tmp/fpp_shoplist_running"
	return=`python3 /home/m_zsuetam/prog/python/fppshoplist/fppshoplist_client.py`
	rm "var/tmp/fpp_shoplist_running"
fi