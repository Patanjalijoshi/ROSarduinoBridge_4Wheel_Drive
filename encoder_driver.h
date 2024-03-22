   
//#ifdef BLD750_ENC_Counter

  #define FRONT_LEFT_ENC_PIN_A 2  
  #define FRONT_LEFT_ENC_PIN_B 3  

  #define FRONT_RIGHT_ENC_PIN_A 18  
  #define FRONT_RIGHT_ENC_PIN_B 19 

  #define BACK_LEFT_ENC_PIN_A 20  
  #define BACK_LEFT_ENC_PIN_B 21 

  #define BACK_RIGHT_ENC_PIN_A 62 
  #define BACK_RIGHT_ENC_PIN_B 63
     
//#endif


long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();