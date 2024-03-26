// motor drivers defined for 4 motors with 1 dir pin and 1 speed pin 


//#ifdef BLD750_MOTOR_DRIVER

  #define FRONT_RIGHT_MOTOR_PWM D4
  #define FRONT_LEFT_MOTOR_PWM D25
  #define BACK_RIGHT_MOTOR_PWM D16
  #define BACK_LEFT_MOTOR_PWM D14

  #define FRONT_RIGHT_MOTOR_DIR D21
  #define FRONT_LEFT_MOTOR_DIR D35
  #define BACK_RIGHT_MOTOR_DIR D17
  #define BACK_LEFT_MOTOR_DIR  D12

  #define FRONT_RIGHT_MOTOR_ENABLE 13
  #define FRONT_LEFT_MOTOR_ENABLE 14
  #define BACK_RIGHT_MOTOR_ENABLE 15
  #define BACK_LEFT_MOTOR_ENABLE 16 

  


//#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed,int backLeftSpeed, int backRightSpeed);

