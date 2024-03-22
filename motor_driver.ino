/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

  void initMotorController() {
        digitalWrite(FRONT_RIGHT_MOTOR_ENABLE,HIGH);
        digitalWrite(FRONT_LEFT_MOTOR_ENABLE,HIGH); 
        digitalWrite(BACK_RIGHT_MOTOR_ENABLE,HIGH); 
        digitalWrite(BACK_LEFT_MOTOR_ENABLE ,HIGH);
  }
  
  void setMotorSpeed(int i, int spd) {
    int reverse = 1;
    if (spd < 0)   
    {
      spd = -spd;
      reverse = -1;
    }
    if (spd > 255)
      spd = 255; 
    

    // //PWM and Direction control for each wheel 
    if (i == FRONT_LEFT) { 
      if      (reverse == 1) { analogWrite(FRONT_LEFT_MOTOR_PWM, spd); digitalWrite(FRONT_LEFT_MOTOR_DIR, HIGH); }
      else if (reverse == -1) { analogWrite(FRONT_LEFT_MOTOR_PWM, spd); digitalWrite(FRONT_LEFT_MOTOR_DIR, LOW); }
    }
    if (i == FRONT_RIGHT) { 
      if      (reverse == 1) { analogWrite(FRONT_RIGHT_MOTOR_PWM, spd); digitalWrite(FRONT_RIGHT_MOTOR_DIR, HIGH); }
      else if (reverse == -1) { analogWrite(FRONT_RIGHT_MOTOR_PWM, spd); digitalWrite(FRONT_RIGHT_MOTOR_DIR, LOW); }
    }
    if (i == BACK_LEFT) { 
      if      (reverse == 1) { analogWrite(BACK_LEFT_MOTOR_PWM, spd); digitalWrite(BACK_LEFT_MOTOR_DIR, HIGH); }
      else if (reverse == -1) { analogWrite(BACK_LEFT_MOTOR_PWM, spd); digitalWrite(BACK_LEFT_MOTOR_DIR, LOW); }
    }
    if (i == BACK_RIGHT) {
      if      (reverse == 1) { analogWrite(BACK_RIGHT_MOTOR_PWM, spd); digitalWrite(BACK_RIGHT_MOTOR_DIR, HIGH); }
      else if (reverse == -1) { analogWrite(BACK_RIGHT_MOTOR_PWM, spd); digitalWrite(BACK_RIGHT_MOTOR_DIR, LOW); }
    }
  }
  
  void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed,int backLeftSpeed, int backRightSpeed) {
    setMotorSpeed(FRONT_LEFT, frontLeftSpeed);
    setMotorSpeed(FRONT_RIGHT, frontRightSpeed);
    setMotorSpeed(BACK_LEFT, backLeftSpeed);
    setMotorSpeed(BACK_RIGHT, backRightSpeed);
  }


