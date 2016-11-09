//***                  Custom Servo Header File                 ***
//***
//***  This file contains a Custom Servo class which will house
//***   the attached Servo class, the min and max positions for that servo,
//***   and the potentiometer pin for that servo.
//***  It will also contain simple servo commands.
//***   These include a move servo command and a hold servo position command.
//***  A seperate header file will be used for ARM 1 control, as it combines 2 servos
//***   and other considerations must be taken into account when controlling it. 

class CServo {
  private:
  
  Servo servo;
  int maxPos;
  int minPos;
  int potPin;
  int potPos;
  int writeSpeed;
  bool invert;
  
  bool vel_flag;
  int vel_time;
  int vel_pos;
  
  bool accel_flag;
  int accel_time;
  

  public:

  CServo(Servo, int, int, int, bool);
  bool isInvert(void);
  int GetPos(void);
  int GetTruePos(void);
  void SetWriteSpeed(int);
  int GetWriteSpeed(void);
  void HoldPos(int);
  int GetVelocity(void);
  void MoveServoWithPot(int);
  bool MoveToPos(int);
  void Accelerate(int, int, bool);
  
};

CServo::CServo( Servo cServo, int MaxPos, int MinPos, int PotPin, bool Invert) {
  
  servo = cServo;
  maxPos = MaxPos;
  minPos = MinPos;
  potPin = PotPin; 
  invert = Invert;
  
  potPos = analogRead(potPin);
  writeSpeed = 1500;
  vel_flag = 0;
  accel_flag = 0;
  vel_time = 0;
  accel_time = 0;
  
}

bool CServo::isInvert() {

  return(invert);
  
}


int CServo::GetPos( ) {

  if (!isInvert()) potPos = analogRead( potPin);   
  else potPos = 1023 - analogRead( potPin );   // Invert is used for servo 1 when reading position
                                               //  because the pots for servo 1 and 2 are mirrored
                                               //  and we want their outputs to be in the same range
                                               
  return potPos;

}


int CServo::GetTruePos() {

  if(isInvert()) {return (1023-GetPos());}
  else {return(GetPos());}
  
}


void CServo::SetWriteSpeed( int WriteSpeed ) {

  writeSpeed = WriteSpeed;
  servo.write(writeSpeed);
  
}

int CServo::GetWriteSpeed( ) {

  return writeSpeed;
  
}


void CServo::HoldPos( int writeSpeed) {

  servo.write(writeSpeed);
  
}


int CServo::GetVelocity( ) {

  if (vel_flag == 0) {
    vel_flag == 1;
    vel_time = millis();
    vel_pos = GetTruePos();
  }

  if(vel_time <= millis() - 29) ;
  else { 
    vel_flag  = 0;
    return((vel_pos - GetTruePos())*10);      //0.293 degrees/point of analog output -> differenceinpos
  }
    
  
}


void CServo::MoveServoWithPot ( int ControlPotPin ) {

  int givenPos = analogRead(ControlPotPin);
  int velocity = GetVelocity();

  if (isInvert()) SetWriteSpeed( 1500 + ( ( GetTruePos() - givenPos ) ) );
  else SetWriteSpeed( 1500 - ( ( GetTruePos() - givenPos ) ) );

  Serial.print("Control Pos :");
  Serial.println(givenPos);
  Serial.print("Servo Pos: ");
  Serial.println(GetTruePos());
  Serial.print("Write Speed: ");
  Serial.println(GetWriteSpeed());
  Serial.print("Velocity : ");
  Serial.println(velocity);

  if (potPos > maxPos || potPos < minPos)                 //If servo moves beyond max range
    HoldPos( GetWriteSpeed() );                           //stop moving servo

  else if ( abs( potPos - givenPos) < 10  ) { 
    HoldPos( GetWriteSpeed() );
  }
  else HoldPos( GetWriteSpeed() );
  
}

bool CServo::MoveToPos( int givenPos ) {

int currentPos = GetTruePos();
int currentVel = GetVelocity();

  if (currentPos > maxPos || currentPos < minPos)   {                           //If servo moves beyond max range
    SetWriteSpeed(1500);                                                       //stop moving servo
    Serial.println("Holding pos");
    return false;
  }

  else if ( abs( currentPos - givenPos) > 34 && currentVel < 10 ) {            //Initial movement if current pos > 10 degrees away from given pos
    Accelerate(currentPos, givenPos, true);
    Serial.print("Accel. Write Speed is: ");
    Serial.println(GetWriteSpeed());
    delay(50);
    return false;
  }

  else if ( abs( currentPos - givenPos) > 34 && currentVel > 10 ) {              //After max velocity of 45 deg/s is reached
    HoldPos(GetWriteSpeed());
    Serial.println("Holding vel");
    return false;
    
  }

  else if ( abs( currentPos - givenPos) <= 34 && abs( currentPos - givenPos) > 30 ) {
    //Accelerate(currentPos, givenPos, false);

   HoldPos(GetWriteSpeed());
    Serial.println("Decell");
    return false;
    
  }

  else SetWriteSpeed(map(givenPos,170,850,1630,1340));
    return true;
  
}

void CServo::Accelerate( int currentPos, int endPos, bool Forward) {

  const int alpha_u = 4;
  const int alpha_d = 2;
  int dir, alpha;

  if( (currentPos<endPos && Forward) || (currentPos>endPos && !Forward ) ) { dir = 1; }
  else { dir = -1; }

  if( (dir == 1 && currentPos<1023/2) || (dir == -1 && currentPos>1023/2) ) {alpha = alpha_u;} 
  else {alpha = alpha_d;}

 if(isInvert()) SetWriteSpeed( GetWriteSpeed() - (alpha*dir) );
 else SetWriteSpeed( GetWriteSpeed() + (alpha*dir) );

}


