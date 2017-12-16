int ledPin = 2; // pin for LED
int ledPinTwo = 12; // pin for second LED

int leftEnable = 3; // pin to activate left motor
int leftLegOne = 4; // left motor leg 1
int leftLegTwo = 5; // left motor leg 2
int rightEnable = 6; // pin to activate right motor
int rightLegOne = 7; // right motor leg 1
int rightLegTwo = 8; // right motor leg 2

int trigPin = 10; // trigger pin (output) for ultrasonic
int echoPin = 11; // echo pin (input) for ultrasonic

int buzzPin = A2; // buzzer input

boolean allClear = false; // is there a collision in front?
boolean blinkOn = false; // boolean to control LED blink
boolean justSwitched = false; // did we just detect a collison/clear path?

int blink = 500;

void setup() {
  // setup function, initializing all pins
  
  // LED
  pinMode(ledPin, OUTPUT);
  
  // motors
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLegOne, OUTPUT);
  pinMode(leftLegTwo, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightLegOne, OUTPUT);
  pinMode(rightLegTwo, OUTPUT);
  
  // ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // enable both motors through the h-bridges
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  
  Serial.begin(9600);
}
void loop() {
  // collecting data from the ultrasonic sensor
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // sends out a pulse from the trigger
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // reads pulse from the echo
  Serial.print(duration);
  Serial.print(", ");
  delay(500); // short delay so we don't overload the arduino
  
  // when it stops detecting a collision, set allClear to false and
  // set justSwitched to true
  if (duration < 3000){
    if (allClear = true){
      justSwitched = true;
    }
    allClear = false;
  }
  // vice versa
  else{
    if (allClear = false){
      justSwitched = true;
    }
    allClear = true;
  }
  
  // if there's nothing in front:
  if (allClear){
    // left motor forward
    digitalWrite(leftLegOne, LOW);
    digitalWrite(leftLegTwo, HIGH);
    // right motor forward
    digitalWrite(rightLegTwo, LOW);
    digitalWrite(rightLegOne, HIGH);

    // turn LEDs on
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPinTwo, HIGH);
    
    // silence buzzer
    analogWrite(buzzPin, 0);
    Serial.println("All Clear");
  }
  // if there is something in front:
  else{
    // turn until there aren't any more obstacles
    // left motor forward
    digitalWrite(leftLegOne, LOW);
    digitalWrite(leftLegTwo, HIGH);
    // right motor backward
    digitalWrite(rightLegTwo, HIGH);
    digitalWrite(rightLegOne, LOW);
    
    // led alternate blink, buzzer beep
    if (blink < 1){
      blink++;
    }
    if (blink >= 1){
      if (blinkOn == false){
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinTwo, LOW);
        analogWrite(buzzPin, 130);
        blink = 0;
        blinkOn = true;
      }
      else{
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinTwo, HIGH);
        analogWrite(buzzPin, 0);
        blink = 0;
        blinkOn = false;
      }
    }
    Serial.println("Collision");
  }
}
