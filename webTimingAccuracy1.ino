int lightPin =1; // LED connected to digital pin 13
int inPin = 6;   // pushbutton connected to digital pin 6
int buttonVal = 0;     // variable to store the read value
int lightVal = 0;
int lightOn = 0;

void setup()
{
  pinMode(lightPin, INPUT);      // sets the digital pin 13 as output
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input
  Serial.begin(9600);
}

void loop()
{
  buttonVal = digitalRead(inPin);   // read the input pin
  doLight(buttonVal);

  lightVal = digitalRead(lightPin);   // read the input pin

  Serial.println(lightVal);  // prints hello with ending line break 
  doLight(lightVal);
}

int doLight(int yes)
{
  if(yes==1){
    if(lightOn == false){
      lightOn = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else{
      lightOn = false;
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(1000);
  }
}

