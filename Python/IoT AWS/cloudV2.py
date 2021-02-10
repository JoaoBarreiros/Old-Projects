#!/usr/bin/python

import requests
import json
import os
import paho.mqtt.client as mqtt
import ssl
import sys
import time

clear = lambda: os.system('cls' if os.name=='nt' else 'clear')

URL     = 'https://xk71rlq8jl.execute-api.eu-west-1.amazonaws.com/default/lambda-microservice'
PARAMS = {'TableName':'ZolertiaTable'} 
HEADERS = {'Content-Type': 'application/json','x-api-key': 'xxxxxxxxxx'}
CLOUD_MQTT_URL = "a1r1z8wjzmeyy5-ats.iot.eu-west-1.amazonaws.com"
CERTIFICATE_AUTH_FILE = "iot_certs/AmazonRootCA1.pem"
CERT_PEM_FILE = "xxxxxxxxxx"
PRIVATE_KEY_FILE = "xxxxxxxxxx"
MQTT_TOPIC = "refresh/topic"

refresh_rate = 5
y=0
max=0
media = 26
cont1 = 0
maxtimestamp=0
yco=0
maxco=0
minco=0
mediaco = 26
	

def get(URL,PARAMS,HEADERS):
	r = requests.get(url = URL, params = PARAMS, headers = HEADERS) 
	return r.json()

def display(data,x):
	if ((((data['Items'][x-1]['Temp'])> 33) or ((data['Items'][x-1]['CO'])> 350)) and ((data['Items'][x-1]['Temp'])<= 45 or ((data['Items'][x-1]['CO'])<= 700))):
		print ("Its to hot in this room! ")
		print ("Sugestion: You should try to ventilate the room, open a window or turn on the AC!")
		
	elif ((data['Items'][x-1]['Temp'])> 45) and ((data['Items'][x-1]['Temp'])<= 60):
		print ("Very Hot, there is risk of fire or dehydration!")
		print ("Sugestion: You should try to drink as much water as possible, and make sure there is no flammable materials in the room!")

	elif ((data['Items'][x-1]['Temp'])> 60):
		print ("Very high probability of Fire! ")
		print ("Sugestion: You should exit the room and call the Fire Department as soon as possible! Dont use the elevator in your exit!")

	if ((data['Items'][x-1]['CO'])> 700 and (data['Items'][x-1]['CO']) <= 1000):
		print ("Heavy risk of Sickness, Detected dangerous concentration of CO in the room! ")
		print ("Sugestion: You should try to ventilate, open a window or turn on the AC and exit the room!")

	elif((data['Items'][x-1]['CO'])> 1000):
		print ("Risk of Death, Detected dangerous concentration of CO in the room!")
		print ("Sugestion: You should exit the room as soon as possible! Call competent authorities")

def main():
	while (1):
		clear()
		cont1 = 0
		print("Welcome to IoT Solutions")
		print
		print("1 - Get all information from table")
		print("2 - Get Temperatures")
		print("3 - Get CO levels")
		print("4 - Get latest values")
		print("5 - Set Zolertia's Refresh rate")
		print("6 - Quit")
		print
		option = raw_input("Option:\n")

		if option.upper() == "1":
			clear()
			print("ZolertiaTable: ")
			print
			data = get(URL,PARAMS,HEADERS)
			print(json.dumps(data, indent=4, sort_keys=True));
			cont = raw_input( "Back")

		if option.upper() == "2":
			clear()
			y=0
			print("All Temperatures: ")
			print
			data = get(URL,PARAMS,HEADERS)
			min= data['Items'][0]['Temp']
			for i in range (0, len (data['Items'])):
				print("Temp[%s]:%s" % (i,data['Items'][i]['Temp']))
				global media,max,min
				if (max < (data['Items'][i]['Temp'])):
					max = (data['Items'][i]['Temp']);
				if (min > (data['Items'][i]['Temp'])):
					min = (data['Items'][i]['Temp']);
				print
				global y
				y += data['Items'][i]['Temp']
			
			media = y/i

			print("Media de Temperaturas:%s" % (media))
			print
			print("Max de Temperaturas:%s" % (max))
			print
			print("Min de Temperaturas:%s" % (min))
			print
			cont = raw_input( "Back")

		if option.upper() == "3":
			clear()
			yco=0
			print("All CO levels: ")
			print
			data = get(URL,PARAMS,HEADERS)
			for i in range (0, len (data['Items'])):
				print("CO[%s]:%s" % (i,data['Items'][i]['CO']))
				global mediaco,maxco,minco
				if (maxco < (data['Items'][i]['CO'])):
					maxco = (data['Items'][i]['CO']);
				if (minco > (data['Items'][i]['CO'])):
					minco = (data['Items'][i]['CO']);
				print
				global yco
				yco += data['Items'][i]['CO']
			
			mediaco = yco/i

			print("Media do Nivel de CO:%s" % (mediaco))
			print
			print("Max do Nivel de CO:%s" % (maxco))
			print
			print("Min do Nivel de CO:%s" % (minco))
			print
			cont = raw_input( "Back")
			
		if option.upper() == "4":
			global refresh_rate
			clear()
			print
			try: 
				while True:
					clear()
					print("Latest Values, next refresh in "+str(refresh_rate)+" seconds (press Ctrl-C to exit loop)")
					data = get(URL,PARAMS,HEADERS)
					for i in range (0, len (data['Items'])):
						if(maxtimestamp < (data['Items'][i]['Timestamp'])):
								maxtimestamp = (data['Items'][i]['Timestamp'])
								x=i
					print(json.dumps((data['Items'][x]), indent=4, sort_keys=True));
					display(data,x)
					time.sleep(int(refresh_rate))
			except KeyboardInterrupt:
				pass
		
		if option.upper() == "5":
			global refresh_rate
			global cont1
			global maxtimestamp
			print("Set a new refresh timer for the zolertia")
			print("Current is "+str(refresh_rate)+" seconds")
			refresh_rate = raw_input("New timer:\n")
			client=mqtt.Client() 
			client.tls_set(ca_certs=CERTIFICATE_AUTH_FILE, certfile=CERT_PEM_FILE, keyfile=PRIVATE_KEY_FILE, tls_version=ssl.PROTOCOL_TLSv1_2)
			client.tls_insecure_set(False)
			client.connect(CLOUD_MQTT_URL, 8883, 60)
			client.publish(MQTT_TOPIC,str(refresh_rate))

		if option.upper() == "6":
			break

if __name__== "__main__":
  main()

	
	