/*
* ATmega16_WIFI
* http://www.electronicwings.com
*
*/
#include "DHT11/DHT11_Master.h"
#include "ESP8266/ESP8266.h"

int main(void)
{
	char _buffer[150];
	uint8_t Connect_Status;
	#ifdef SEND_DEMO
	#endif
	USART_Init(115200);			/* Initiate USART with 115200 baud rate */
	sei();					/* Start global interrupt */

	while(!ESP8266_Begin());
	ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);/* 3 = Both (AP and STA) */
	ESP8266_ConnectionMode(SINGLE);		/* 0 = Single; 1 = Multi */
	ESP8266_ApplicationMode(NORMAL);	/* 0 = Normal Mode; 1 = Transperant Mode */
	if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)
	ESP8266_JoinAccessPoint(SSID, PASSWORD);	
	while(1)
	{
		Connect_Status = ESP8266_connected();
		if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)
		ESP8266_JoinAccessPoint(SSID, PASSWORD);

		#ifdef SEND_DEMO
		DHT_WakeUp();
		int array[5][8];
		if (DHT_Response())
		{
			DHT_Decode_Data(array);
			//TransmitData
			ESP8266_TRANSMIT(ConvertToDecimal(array, 3), 1, _buffer);
			_delay_ms(15000);	// Thingspeak server delay
			ESP8266_TRANSMIT(ConvertToDecimal(array, 1), 2, _buffer);
			_delay_ms(15000);	// Thingspeak server delay
		}		
		#endif
		
		#ifdef RECEIVE_DEMO
		memset(_buffer, 0, 150);
		sprintf(_buffer, "GET /channels/%s/feeds/last.txt", CHANNEL_ID);
		ESP8266_Send(_buffer);
		Read_Data(_buffer);
		_delay_ms(600);
		#endif
	}
}