int ledPin = 2;

int leftEnable = 3;
int leftLegOne = 4;
int leftLegTwo = 5;
int rightEnable = 6;
int rightLegOne = 7;
int rightLegTwo = 8;

int trigPin = 10;
int echoPin = 11;

int infraPin = A1;
int buzzPin = A2;

boolean allClear = true;

void setup() {
  pinMode(ledPin, OUTPUT);
  
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLegOne, OUTPUT);
  pinMode(leftLegTwo, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightLegOne, OUTPUT);
  pinMode(rightLegTwo, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  
  Serial.begin(9600);
}
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.print(", ");
  delay(500);
  
  if (distance < 100){
    allClear = false;
  }
  else{
    allClear = true;
  }
  
  if (allClear){
    // left motor forward
    digitalWrite(leftLegOne, LOW);
    digitalWrite(leftLegTwo, HIGH);
    // right motor forward
    digitalWrite(rightLegTwo, LOW);
    digitalWrite(rightLegOne, HIGH);
    
    analogWrite(buzzPin, 0);
    Serial.println("All Clear");
  }
  else{
    // left motor off
    digitalWrite(leftLegOne, LOW);
    digitalWrite(leftLegTwo, LOW);
    // right motor off
    digitalWrite(rightLegTwo, LOW);
    digitalWrite(rightLegOne, LOW);
    
    // led on
    digitalWrite(ledPin, HIGH);
    analogWrite(buzzPin, 130);
    Serial.println("Collision");
  }
}
