// structure to hold all the variables of related to the pid calculations

typedef struct{

   float targetTicksPerFrame;
   float currentTicksPerFrame;
   float prevTicksPerFrame;
   float Integral;
   float output;
   float prevError;




}
setPointInfo;

setPointInfo backLeftPID, backRightPID, frontLeftPID, frontRightPID;


float kp = 6.0;
float kd = 0.055;
float ki = 0.2;

unsigned char moving = 0; 

void resetPID() {
    // Reset PID variables for backLeftPID
    backLeftPID.targetTicksPerFrame = 0.0;
    backLeftPID.currentTicksPerFrame = readEncoder(BACK_LEFT);
    backLeftPID.prevTicksPerFrame = backLeftPID.currentTicksPerFrame;
    backLeftPID.Integral = 0.0;
    backLeftPID.output = 0.0;
    backLeftPID.prevError = 0.0;

    // Reset PID variables for backRightPID
    backRightPID.targetTicksPerFrame = 0.0;
    backRightPID.currentTicksPerFrame =  readEncoder(BACK_RIGHT);
    backRightPID.prevTicksPerFrame = backRightPID.currentTicksPerFrame;
    backRightPID.Integral = 0.0;
    backRightPID.output = 0.0;
    backRightPID.prevError = 0.0;

    // Reset PID variables for frontLeftPID
    frontLeftPID.targetTicksPerFrame = 0.0;
    frontLeftPID.currentTicksPerFrame = readEncoder(FRONT_LEFT);
    frontLeftPID.prevTicksPerFrame = frontLeftPID.currentTicksPerFrame;
    frontLeftPID.Integral = 0.0;
    frontLeftPID.output = 0.0;
    frontLeftPID.prevError = 0.0;

    // Reset PID variables for frontRightPID
    frontRightPID.targetTicksPerFrame = 0.0;
    frontRightPID.currentTicksPerFrame = readEncoder(FRONT_RIGHT);
    frontRightPID.prevTicksPerFrame = frontRightPID.currentTicksPerFrame;
    frontRightPID.Integral = 0.0;
    frontRightPID.output = 0.0;
    frontRightPID.prevError = 0.0;
}

void doPID(setPointInfo *M){  

    // Calculate the error (difference between target and current value)
    //current ticks is always going to be bigger than previous ticks while moving in the forward direction
    float error = 0.0;
    float dError = 0.0;
    float pTerm = 0.0;
    float iTerm = 0.0;
    float dTerm = 0.0;

    error = (M->targetTicksPerFrame - (M->currentTicksPerFrame - M->prevTicksPerFrame));
    //Serial.println(error);
    // Calculate the rate of change of the error (differential term)
    Serial.print(M->targetTicksPerFrame);
    Serial.print(" ");
    Serial.print(M->currentTicksPerFrame - M->prevTicksPerFrame);
    Serial.print(" ");
    Serial.println(error);
    dError = error - M->prevError;

    // integral 
      M->Integral += error;

    // Calculate the proportional term 
     pTerm = kp * error;

    // Calculate the integral term
     iTerm = ki * M->Integral; 

    // Calculate the differential term
     dTerm = kd * dError; 
    
    
    //Output
    M->output = pTerm + iTerm + dTerm;
    //Serial.println(M->output);
    // assigning current error to previous error for the next calculation 
    M->prevError = error;
    
    //assigining current to previous ticks per frame for the next calculation
    M->prevTicksPerFrame = M->currentTicksPerFrame;

}

void updatePID(){ 
// noInterrupts();
  backLeftPID.currentTicksPerFrame = readEncoder(BACK_LEFT);
  backRightPID.currentTicksPerFrame = readEncoder(BACK_RIGHT);
  frontLeftPID.currentTicksPerFrame = readEncoder(FRONT_LEFT);
  frontRightPID.currentTicksPerFrame = readEncoder(FRONT_RIGHT);
 //interrupts(); 

//reset pid if not moving
// if(moving == 0){
//    resetPID();
// }


  if(frontLeftPID.targetTicksPerFrame != 0){
    doPID(&frontLeftPID);
  }
  if(frontRightPID.targetTicksPerFrame  != 0){
    doPID(&frontRightPID);
  }
  if(backLeftPID.targetTicksPerFrame != 0){
    doPID(&backLeftPID);
  }
  if(backRightPID.targetTicksPerFrame  != 0){
    doPID(&backRightPID);
  }

   
 setMotorSpeeds(frontLeftPID.output, frontRightPID.output, backLeftPID.output, backRightPID.output);
}
