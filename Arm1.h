//***                 First Arm Header File                     ***
//***
//*** This file contains the Class definition of the Arm1 Class 
//***  which will be instantiated to control the first arm.
//*** The Arm1 class will contain the CServo class to control the two
//***  servos used to move the arm. 
//*** Additionally the Arm1 class will take the average output of the two
//***  potetiometers attached to it in order to read position. This will be
//***  done as the output of the two pots vary slightly and non-linearly.

class Arm1 {
  private:
  
  CServo cServo1;
  CServo cServo2;


  public:
    
};

