int sensePin1=A0; // analog Pin A0 on the arduino
int sensePin2=A1; // analog Pin A1 on the arduino
int RED1=6; // light on crossing signal
int RED2=5;  // light on crossing signal
int POWER=8; // POWER pin 8


void setup() {
  Serial.begin(9600); // enables display of sensor output
  pinMode(RED1,OUTPUT); //establishes pins as Output Pin
  pinMode(RED2,OUTPUT);
  pinMode(POWER,OUTPUT);

  
}

enum CROSSINGSTATES
{
  ST_OFF,
  ST_FLASHING1,
  ST_FLASHING2,
  ST_FLASHING3,
}; //identifies our 4 crossing states

CROSSINGSTATES crossingState=ST_OFF; // default state of the crossing

void loop() {
  int valA1=analogRead(sensePin1); //reads and stores value of sensors
  int valA2=analogRead(sensePin2);
  Serial.println(valA1); // displays value of the sensor in the serial monitor
  Serial.println(valA2);
  delay(200); //dealy of 0.2 seconds between sensor readings

  switch(crossingState) // this is establishing where the program goes to when a sensor is read
  {
    case ST_OFF:
    crossingoff(valA1, valA2);
    break;
    case ST_FLASHING1:
    crossingflashing1(valA1, valA2);
    break;
    case ST_FLASHING2:
    crossingflashing2(valA1, valA2);
    break;
    case ST_FLASHING3:
    crossingflashing3(valA1, valA2);
    break;
  }
}

void crossingoff(int valA1, int valA2){
  digitalWrite(RED1,HIGH);
  digitalWrite(RED2,HIGH);
  digitalWrite(POWER,HIGH); // this is what our lights are doing when in this phase of the program.  This has them both off

  if(valA1<500 && valA2>500){
    crossingState=ST_FLASHING1; // if sensePin1 is tripped the program switches to Flashing 1
  }
  else if (valA1>500 && valA2<500){
    crossingState=ST_FLASHING2; // if sensePin2 is tripped the program switches to Flashing 2
  }
}

void crossingflashing1(int valA1, int valA2){
  digitalWrite(RED1,HIGH);
  digitalWrite(RED2,LOW);
  digitalWrite(POWER,HIGH);
  delay(500);  // This is half of the flashing signal and it goes for 0.5 seconds
  digitalWrite(RED1,LOW);
  digitalWrite(RED2,HIGH);
  digitalWrite(POWER,HIGH);
  delay(500); // This will loop until a condition is met that would change it

  if (valA1>500 && valA2<500){
    crossingState=ST_FLASHING3;
   
  }
}

void crossingflashing2(int valA1, int valA2){
  digitalWrite(RED1,HIGH);
  digitalWrite(RED2,LOW);
  digitalWrite(POWER,HIGH);
  delay(500);  // This is half of the flashing signal and it goes for 0.5 seconds
  digitalWrite(RED1,LOW);
  digitalWrite(RED2,HIGH);
  digitalWrite(POWER,HIGH);
  delay(500); // This will loop until a condition is met that would change it

  if (valA1<500 && valA2>500){
    crossingState=ST_FLASHING3;
  }
  }

 void crossingflashing3(int valA1, int valA2){
  digitalWrite(RED1,HIGH);
  digitalWrite(RED2,LOW);
  digitalWrite(POWER,HIGH);
  delay(500);  // This is half of the flashing signal and it goes for 0.5 seconds
  digitalWrite(RED1,LOW);
  digitalWrite(RED2,HIGH);
  digitalWrite(POWER,HIGH);
  delay(500); // This will loop until a condition is met that would change it

  if (valA1>500 && valA2>500){
    crossingState=ST_OFF;
  }
  } 
