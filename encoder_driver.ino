 /* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */


   
//#ifdef USE_BASE

//#define BLD750_ENC_Counter
  
   volatile int ticksBL = 0;
   
   volatile int ticksBR = 0;
   
   volatile int ticksFL = 0;
   
   volatile int ticksFR = 0;
      

  // count the number of pulses for one encoder in each wheel 

void updateEncoderBL(){
  int b = digitalRead(BACK_LEFT_ENC_PIN_B);
  if(b > 0){
    ticksBL++;
  }
  else{
    ticksBL--;
  }
}
  

void updateEncoderFL(){
  int b = digitalRead(FRONT_LEFT_ENC_PIN_B);
  if(b > 0){
    ticksFL++;
  }
  else{
    ticksFL--;
  }
}

void updateEncoderFR(){
  int b = digitalRead(FRONT_RIGHT_ENC_PIN_B);
  if(b > 0){
    ticksFR++;
  }
  else{
    ticksFR--;
  }
}

void updateEncoderBR(){
  int b = digitalRead(BACK_RIGHT_ENC_PIN_B);
  if(b > 0){
    ticksBR++;
  }
  else{
    ticksBR--;
  }
}
  
  long readEncoder(int i) {
    if (i == FRONT_LEFT) return ticksFL;
    else if(i == BACK_LEFT)return ticksBL;
    else if(i == BACK_RIGHT)return ticksBR;
    else if(i == FRONT_RIGHT)return ticksFR;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == FRONT_LEFT){
      ticksFL=0;
      return;
    } 
    else if (i == BACK_LEFT) { 
      ticksBL=0;
      return;
    }
    else if (i == BACK_RIGHT) { 
      ticksBR=0;
      return;
    }
    else if (i == FRONT_RIGHT) { 
      ticksFR=0;
      return;
    }
  }
// #else
//   #error A encoder driver must be selected!
// #endif

/* Wrap the encoder reset function */

void resetEncoders() {
  Serial.println("encoders have been reset");
  resetEncoder(FRONT_LEFT);
  resetEncoder(FRONT_RIGHT);
  resetEncoder(BACK_LEFT);
  resetEncoder(BACK_RIGHT);
}

//#endif
