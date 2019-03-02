//QRD variables
const unsigned int QrdPinLeft = A0;
const unsigned int QrdPinRight = A1;
const unsigned int QrdThresholdLeft = 1000;
const unsigned int QrdThresholdRight = 1000;
unsigned int QrdValueLeft;
unsigned int QrdValueRight;

//Ultrasonic sensor variables
const unsigned int echoPin = 12;
const unsigned int trigPin = 13;
int maximumRange = 50; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
boolean lastQRDLeft = false;
boolean foundRobot = true;

//motor variables TODO: rename left and right
int enablePinLeft = 11;
int in1PinLeft = 10;
int in2PinLeft = 9;
int enablePinRight = 6;
int in1PinRight = 5;
int in2PinRight = 4;

void setup() {
  //QRD pins
  pinMode(QrdPinLeft, INPUT);
  pinMode(QrdPinRight, INPUT);

  //Ultra pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //motor pins
  pinMode(in1PinLeft, OUTPUT);
  pinMode(in2PinLeft, OUTPUT);
  pinMode(enablePinLeft, OUTPUT);
  pinMode(in1PinRight, OUTPUT);
  pinMode(in2PinRight, OUTPUT);
  pinMode(enablePinRight, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //check QRD first 
  QrdValueLeft = analogRead(QrdPinLeft);
  QrdValueRight = analogRead(QrdPinRight);

  if (QrdValueLeft < QrdThresholdLeft) {
    Serial.println("Qrd Left is reading white!!!");
  } else {
    Serial.print("Qrd Left is reading black!!!");
    Serial.print("\n");
  }
  if (QrdValueRight < QrdThresholdRight) {
    Serial.println("Qrd Right is reading white!!!");
  } else {
    Serial.print("Qrd Right is reading black!!!");
    Serial.print("\n");
  }
  Serial.println("---------------------------------------------");
  
  //check Ultra values
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = duration/58.2;

  Serial.println(distance);
   
  //motor loop
  int speed = 500;
  int slowSpeed = 100;

  foundRobot = distance < maximumRange;
  
  if (QrdValueLeft < QrdThresholdLeft) {
    lastQRDLeft = true;
  }
  else if (QrdValueRight < QrdThresholdRight) {
    lastQRDLeft = false;
  }
  
  foundRobot = distance < maximumRange;
  boolean reverseLeft = QrdValueRight < QrdThresholdRight || (! lastQRDLeft && ! foundRobot);
  boolean reverseRight = QrdValueLeft < QrdThresholdLeft || (lastQRDLeft && ! foundRobot);
  if (! foundRobot && QrdValueRight >= QrdThresholdRight && QrdValueLeft >= QrdThresholdLeft) {
    setMotorLeft(slowSpeed, reverseLeft);
    setMotorRight(slowSpeed, reverseRight);
  }
  else {
    setMotorLeft(speed, reverseLeft);
    setMotorRight(speed, reverseRight);
  }
  delay(1000);
}

void setMotorLeft(int speed, boolean reverse)
{
  analogWrite(enablePinLeft, speed);
  digitalWrite(in1PinLeft, ! reverse);
  digitalWrite(in2PinLeft, reverse);
}

void setMotorRight(int speed, boolean reverse)
{
  analogWrite(enablePinRight, speed);
  digitalWrite(in1PinRight, ! reverse);
  digitalWrite(in2PinRight, reverse);
}
