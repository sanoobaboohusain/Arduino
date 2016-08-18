/*
 * reads x,y,z values from an accelerometer module and 
 * sends it to an android phone through hc-05 module
 * 
 */

/*
 * @ author sanoob aboo husain
 */


const int xpin = A6;
const int ypin = A5;
const int zpin = A4;
const int led = 13;

int x = 0;
int y = 0;
int z = 0;

String data = "";

void setup() {
  Serial.begin(9600);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {

   digitalWrite(led, HIGH);
   x = analogRead(xpin);
   y = analogRead(ypin);
   z = analogRead(zpin);
   //data = "{\"x\":"+ String(x) + "\"}";
   data = "{\"x\":"+String(x)+",\"y\":"+String(y)+",\"z\":"+String(z)+"}";
   Serial.println(data);
   digitalWrite(led, LOW);
   delay(200);

}
