/////////////motors//////////////
#define rightMotorForwardPin 5
#define rightMotorBackPin    6
#define leftMotorForwardPin  9
#define leftMotorBackPin     10

#define speed 120
/////////////////////////////////

////////////ultrasonic///////////
#define middleEchoPin 3 
#define middleTrigPin 2 
long middleUltrasonicDuration; 
int middleUltrasonicDistance; 

#define leftEchoPin 4 
#define leftTrigPin 7
long leftUltrasonicDuration; 
int leftUltrasonicDistance; 

#define rightEchoPin 8 
#define rightTrigPin 11 
long rightUltrasonicDuration; 
int rightUltrasonicDistance; 

#define ultrasonicLowerError 4.0
#define ultrasonicUpperError 200
/////////////////////////////////

////////////Walls variable///////////
#define wallThreshold  20
#define frontThreshold  10 

boolean frontWall ; // true means that it is blocked
boolean leftWall ;
boolean rightWall ;

/////////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  /////////////motors//////////////
  pinMode(rightMotorForwardPin,OUTPUT);
  pinMode(rightMotorBackPin,OUTPUT);
  pinMode(leftMotorForwardPin,OUTPUT);
  pinMode(leftMotorBackPin,OUTPUT);
  /////////////////////////////////

  ////////////ultrasonic///////////
  pinMode(middleTrigPin, OUTPUT);
  pinMode(middleEchoPin, INPUT); 
  
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT); 
  
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT); 
 /////////////////////////////////
}

void loop() 
{
  
/////////Reading the ultrasonic sensors/////////
rightUltrasonicDistance = rightUltrasonicRead();
leftUltrasonicDistance = leftUltrasonicRead();
middleUltrasonicDistance = middleUltrasonicRead();
////////////////////////////////////////////////
walls(); // reading the walls
  
  if (leftWall == true ) 
  {
    Serial.print("leftWall:True ");
  }
  else 
  {
   Serial.print("leftWall:False ");
  }

  if (frontWall == true ) 
  {
    Serial.print("frontWall:True ");
  }
  else 
  {
   Serial.print("frontWall:False ");
  }
  
  if (rightWall == true ) 
  {
    Serial.print("rightWall:True ");
  }
  else 
  {
   Serial.print("rightWall:False ");
  }
  
  Serial.print(leftUltrasonicRead());
  Serial.print(" cm ");
  
  
  Serial.print(middleUltrasonicRead());
  Serial.print(" cm ");
  
 
  Serial.print(rightUltrasonicRead());
  Serial.print(" cm ");
  


if(leftWall == true && frontWall == false && rightWall == true)
{
  forward();
  Serial.print(" Forward ");
}
else if(leftWall == false && frontWall == true && rightWall == true)
{
  left();
  Serial.print(" Left ");
}
else if(leftWall == true && frontWall == true && rightWall == false)
{
  right();
  Serial.print(" Right ");
}
  Serial.println("");
}
//////////////////////move functions///////////////////////////
void forward()
{
  analogWrite(rightMotorForwardPin,speed);  
  analogWrite(rightMotorBackPin,LOW);  
  analogWrite(leftMotorForwardPin,speed);  
  analogWrite(leftMotorBackPin,LOW);  
}

void right()
{
  analogWrite(rightMotorForwardPin,LOW);  
  analogWrite(rightMotorBackPin,speed);  
  analogWrite(leftMotorForwardPin,speed);  
  analogWrite(leftMotorBackPin,LOW);    
}
void left()
{
  analogWrite(rightMotorForwardPin,speed);  
  analogWrite(rightMotorBackPin,LOW);  
  analogWrite(leftMotorForwardPin,LOW);  
  analogWrite(leftMotorBackPin,speed);    
}
////////////////////////////////////////////////////////////////

//////////////////////Ultrasonic read functions////////////////////////////
int middleUltrasonicRead()
{
  // Clears the trigPin condition
  digitalWrite(middleTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(middleTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(middleTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  middleUltrasonicDuration = pulseIn(middleEchoPin, HIGH);
  // Calculating the distance
  middleUltrasonicDistance = middleUltrasonicDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  if(middleUltrasonicDistance < ultrasonicLowerError|| middleUltrasonicDistance > ultrasonicUpperError )
  {
    middleUltrasonicDistance = 0;
  }
  return middleUltrasonicDistance;
}


int leftUltrasonicRead()
{
  // Clears the trigPin condition
  digitalWrite(leftTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(leftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  leftUltrasonicDuration = pulseIn(leftEchoPin, HIGH);
  // Calculating the distance
  leftUltrasonicDistance = leftUltrasonicDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  if(leftUltrasonicDistance < ultrasonicLowerError || leftUltrasonicDistance > ultrasonicUpperError)
  {
    leftUltrasonicDistance = 0;
  }
  return leftUltrasonicDistance;
}

int rightUltrasonicRead()
{
  // Clears the trigPin condition
  digitalWrite(rightTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(rightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  rightUltrasonicDuration = pulseIn(rightEchoPin, HIGH);
  // Calculating the distance
  rightUltrasonicDistance = rightUltrasonicDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  if(rightUltrasonicDistance < ultrasonicLowerError || rightUltrasonicDistance > ultrasonicUpperError)
  {
    rightUltrasonicDistance = 0;
  }
  return rightUltrasonicDistance;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////Walls////////////////////////////
void walls()
{
  if ( leftUltrasonicDistance < wallThreshold ) 
  {
    leftWall = true ;
  }
  else 
  {
    leftWall = false ;
  }

  if ( rightUltrasonicDistance < wallThreshold ) 
  {
    rightWall = true ;
  }
  else 
  {
    rightWall = false ;
  } 
  
  if ( middleUltrasonicDistance < frontThreshold ) 
  {
    frontWall = true ;
  }
  else 
  {
    frontWall = false ;
  }
  
 }
//////////////////////////////////////////////////////
