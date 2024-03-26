   
//#ifdef BLD750_ENC_Counter

  #define FRONT_LEFT_ENC_PIN_A D33
  #define FRONT_LEFT_ENC_PIN_B D32 

  #define FRONT_RIGHT_ENC_PIN_A D22  
  #define FRONT_RIGHT_ENC_PIN_B D23 

  #define BACK_LEFT_ENC_PIN_A D27  
  #define BACK_LEFT_ENC_PIN_B D26 

  #define BACK_RIGHT_ENC_PIN_A D18 
  #define BACK_RIGHT_ENC_PIN_B D19
     
//#endif


long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();