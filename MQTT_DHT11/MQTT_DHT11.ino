#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <PubSubClient.h>

#define DHTPIN A0
#define DHTTYPE DHT11

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char userId[] = "";
char passwd[] = "";  
//char server[] = "mqtt.dioty.co";
IPAddress server(162,222,176,239);
unsigned int port = 1883;
char topic[] = "//temp"; 
int deviceID = 99;
EthernetClient client; 
PubSubClient arduinoClient(server, port, 0, client) ;
DHT dht (DHTPIN, DHTTYPE); 
IPAddress ip(192, 168, 0, 177);
unsigned long time;
int incomingByte = 0;

void setup(){
  Serial.begin(9600); 
  Serial.println("Start");
  dht.begin();
  makeConnection();
}


void loop(){
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String hu = "{humidity:";
  String humid = hu+h;
  String temp =humid + ",temp:";
  String temperature = temp+t;
  time = millis();
  String message = temperature+","+"device:"+deviceID+",time:"+time+"}";
  int len = message.length()+1;
  char msgArray[len];
  ((String)message).toCharArray(msgArray, len);
  //String messsge = "Humidity: "+h+" %\t Temperature: "+t+" DegreeC";
  Serial.println(msgArray);
  if (not(arduinoClient.loop())){
      Serial.println("connection lost...");
      reConnect();
  }
  arduinoClient.publish(topic, msgArray);
  delay(8000);
}


void makeConnection(){
  if (Ethernet.begin(mac) == 0) {
      Serial.println(F("Failed to configure Ethernet using DHCP"));
      Ethernet.begin(mac, ip);          
  };
  if (arduinoClient.connect(NULL,userId,passwd)) {
      Serial.println("Connected to MQTT server");
  } else {
           Serial.println(F("Failed to connect to the MQTT Server"));      
          }
}

void reConnect(){
  Serial.println("Entering reConnect");
  if (arduinoClient.connected()){
    Serial.println("arduinoClient is connected");
  } else {
    Serial.println("arduinoClient is not connected");
      if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        Ethernet.begin(mac,ip);
      };
      Serial.print("Connected to Internet");
      Serial.println(Ethernet.localIP());
      if (arduinoClient.connect(NULL,userId,passwd)) {
        Serial.println("Reconnected to MQTT Server...");
      } else {
        Serial.println("Failed to connect to the MQTT Server");
      }
  };
}
