#include <Keyboard.h>

int lightPin = 1; // LED connected to digital pin 13
int inPin = 7;   // pushbutton connected to digital pin 6
int buttonVal = 0;     // variable to store the read value
String message = "";
volatile int lightVal = 0;
volatile boolean lightOn = false;

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
}

//add to list of characters to send
void send(String str) {
  if (message.length() > 0) message += '/n';
  message += str;
}

//character by character, send the string
void _send() {
  while (message.length() > 0) {
    Keyboard.println(message.charAt(0));
    message.remove(0, 1);
     delay(10);
  }
}

void buttonOnEvent() {
  lightOn = ! lightOn;
  doLight();
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
        send("hello");
        _send();
  doLight();

}

void loop()
{
  //Serial.println(1);  // prints hello with ending line break
  //_send();
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

