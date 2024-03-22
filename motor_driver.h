// motor drivers defined for 4 motors with 1 dir pin and 1 speed pin 


//#ifdef BLD750_MOTOR_DRIVER

  #define FRONT_RIGHT_MOTOR_PWM 12
  #define FRONT_LEFT_MOTOR_PWM 11
  #define BACK_RIGHT_MOTOR_PWM 10
  #define BACK_LEFT_MOTOR_PWM  9

  #define FRONT_RIGHT_MOTOR_DIR 8
  #define FRONT_LEFT_MOTOR_DIR 7
  #define BACK_RIGHT_MOTOR_DIR 6
  #define BACK_LEFT_MOTOR_DIR  5 

  #define FRONT_RIGHT_MOTOR_ENABLE 13
  #define FRONT_LEFT_MOTOR_ENABLE 14
  #define BACK_RIGHT_MOTOR_ENABLE 15
  #define BACK_LEFT_MOTOR_ENABLE 16 

  


//#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed,int backLeftSpeed, int backRightSpeed);

