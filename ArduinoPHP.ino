#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <SoftwareSerial.h>
#include "dht.h"
SoftwareSerial softserial(A9, A8); // RX, TX
WiFiEspClient  client; 
int status = WL_IDLE_STATUS; 

#define SSID "Goattacons 2"      
#define PASS "716244wnnxs25"
#define DHT11_PIN 2 // Defines pin number to which the sensor is connected
#define gasSensor 4
dht DHT; // Creats a DHT object
int gasStatus=0;

char reply;
char server[] = "10.0.0.204";

void setup() {
  // initialize serial for debugging
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("start");
  // set the data rate for the SoftwareSerial port
  softserial.begin(9600);
  softserial.println("AT+UART_DEF=9600,8,1,0,0\r\n");
  softserial.write("AT+RST\r\n");
  delay(100);
  softserial.begin(9600);
  // initialize ESP module
  WiFi.init(&softserial);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SSID);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(SSID, PASS);
  }
Serial.println("You're connected to the network");

}

void loop() {
  while (client.connect(server, 80)) {
int chk = DHT.read11(DHT11_PIN);
float t = DHT.temperature; // Gets the values of the temperature
float h = DHT.humidity; // Gets the values of the humidity
String temp = "temperature=" +String(t);
String hum = "&humidity=" +String(h);
String gasStr;
gasStatus=digitalRead(gasSensor);
  if (gasStatus==1) {
   gasStr = "Yes";
  } else {
   gasStr = "No";
  }
String gas = "&gas=" + gasStr;
Serial.println();
Serial.println("Receiving Data...");

Serial.println("Connected to server");
Serial.println(gas);
client.println("GET /data.php?"+temp+hum+gas+ "HTTP/1.1");
client.println("Host: 10.0.0.204:80");
client.println("Connection: close");
client.println();

while (client.available()) {
char c = client.read();
Serial.write(c);     
}

//if (!client.connected()) {
//Serial.println();
//Serial.println("Disconnecting from server...");
//client.stop();
//while(true);
// }
}
}
