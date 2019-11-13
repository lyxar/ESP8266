# ESP8266

<h3>Introduction</h3>
This program is designed on a Arduino mega 2560.
This program is designed with the intention of reciving data from the DHT11 temperature/humidity module, and send this data to an API, in this example <a href="https://thingspeak.com/">Thingspeak</a> is used as the API. The program will contact the API every 15 seconds and send Temp/Humidity alternating.

The potentional result of using this program is as follows.
<img src="https://i.imgur.com/KryIs54.png"/>

<h3>Component List</h3>
<ul>
<li>DHT11 Temp/Humidity module</li>
<li>ESP8266 Wifi module</li>
<li>1x External power supply 3.3v </li>
<li>1x Button</li>
<li>1x 1k Resistor</li>
<li>1x 2k Resistor</li>
<li>Various wires for conneting</li>
<li>Breadboard</li>
<li>Arduino Mega2560</li>
<li>Atmel encoder</li>
</ul>

<img src="https://i.imgur.com/PajVLN5.png"/>


<h3>Methods</h3>
Here is a list explaining the methods used in this program.

<h4>DHT11</h4>
Temperature and humidity module. A digram of what method is used where can be seen further down the readme.

<h5>DHT_WakeUp</h5>
This method is used to start the initial connection to the DHT11, by pulling the bit LOW for a minimum of 18ms before changing the bit to input and adding a pullup resistor.

It takes void and returns void.

<h5>DHT_Response</h5>
This method is used to detect if the DHT11 responds after using the DHT_WakeUp method.

This method returns 1 or 0 depending on whether not the DHT11 responds, the method takes no arguments.

<h5>DHT_Decode_Data</h5>
This method is used to decode the serial data that the DHT11 transmits. The method does this by using 2 loops one for every byte transmitted and one for every bit transmitted, it saves the bytes in a two dimensonal array. It can tell the difference between HIGH and LOW bits by the length the connection is pulled HIGH. Under 23us the bit is LOW, over 60us and the bit is HIGH.

This method takes a two dimensonal array pointer and returns void.

As seen on this capture from a logic analyser, it is visible how the data is transmitted.

<img src="https://i.imgur.com/gNrkYGE.png"/>

<h5>ConvertToDecimal</h5>
This method is used to convert the bytes saved from the transmission to decimal, it does this by taking a defined byte and running through the array linked to this byte. Taking the byte and multiplying it with a multiplyer that goes up each time, and adding it to a total value.

The math operates as shown below, with the multiplyer in the top row and the bits in the bottom row. The total of this byte would then be 35.

<table>
  <tr>
    <td>1</td>
    <td>2</td>
    <td>4</td>
    <td>8</td>
    <td>16</td>
    <td>32</td>
    <td>64</td>
    <td>128</td>
  </tr>
  <tr>
    <td>1</td>
    <td>1</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>1</td>
    <td>0</td>
    <td>0</td>
  </tr>
</table>

This method takes 2 arguments, first an two dimensonal array pointer. Second a int defining which byte to be converted. The method returns the decimal value of the selected byte.

This figure show the process between the MCU and the DHT11.
<img src="https://i.imgur.com/VBbpFrD.png"/>
