#include <Keyboard.h>

int lightPin = 1; // LED connected to digital pin 13
int inPin = 7;   // pushbutton connected to digital pin 6
int buttonVal = 0;     // variable to store the read value
String _message = "";
volatile int lightVal = 0;
volatile boolean lightOn = false;
long startMicrosecondStamp = -1;
long lastEventMicrosendStamp = -1;
long duration = -1;

void setup()
{
  pinMode(lightPin, INPUT);      // sets the digital pin 13 as output
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input

  //only one interupt per pin
  //http://stackoverflow.com/questions/33380218/multiple-arduino-interrupts-on-same-pin
  attachInterrupt(digitalPinToInterrupt(lightPin), lightOnEvent, CHANGE  );

  attachInterrupt(digitalPinToInterrupt(inPin), buttonOnEvent, RISING );
  Keyboard.begin();

  Serial.begin(9600);
  startMicrosecondStamp = micros();
}

//add to list of characters to send
void message(String str) {
  _message += str;
}

//character by character, send the string, then enter
void send() {
  while (_message.length() > 0) {
    Keyboard.println(_message.charAt(0));
    _message.remove(0, 1);
    delay(10);
  }
   Keyboard.write(176);
   delay(10);
}

void buttonOnEvent() {
  lightOn = ! lightOn;
  doLight();
  calcDuration();
}

void calcDuration(){
  long now = micros();
  if(lastEventMicrosendStamp == -1){
    duration = -1;
  }
  else{
    duration = now - lastEventMicrosendStamp;
  }
  lastEventMicrosendStamp = now;
  message("duration: "+String(duration));
  send();
}

void lightOffEvent() {
  Serial.println(0);
  lightOn = ! lightOn;
  doLight();
}

void lightOnEvent() {
  lightVal = digitalRead(lightPin);   // read the input pin
  Serial.println(lightVal);
  lightOn = lightVal == 1;
        message("hello");
        send();
  doLight();

}

void loop()
{
  //Serial.println(1);  // prints hello with ending line break
  //send();
  //delay(100);
}

int doLight()
{
  if (lightOn) {
    digitalWrite(LED_BUILTIN, HIGH);

  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
