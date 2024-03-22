


 // Enable use of PWM servos as defined in servos.h
#undef USE_SERVOS     // Disable use of PWM servos

/* Serial port baud rate */
#define BAUDRATE     57600

/* Maximum PWM signal */
#define MAX_PWM        150


 #include "Arduino.h"

/* Include definition of serial commands */
#include "commands.h"

/* Sensor functions */
#include "sensors.h"


  /* Motor driver function definitions */
  #include "motor_driver.h"

  /* Encoder driver function definitions */
  #include "encoder_driver.h"

  /* PID parameters and functions */
  #include "diff_controller.h"

  /* Run the PID loop at 30 times per second */
  #define PID_RATE           10     // Hz

  /* Convert the rate into an interval */
  const int PID_INTERVAL = 1000 / PID_RATE;
  
  /* Track the next time we make a PID calculation */
  unsigned long nextPID = PID_INTERVAL;

  /* Stop the robot if it hasn't received a movement command
   in this number of milliseconds */
  #define AUTO_STOP_INTERVAL 2000
 long lastMotorCommand = AUTO_STOP_INTERVAL;


/* Variable initialization */

// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int index = 0;

// Variable to hold an input character
char chr;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the first and second arguments
char argv1[16];
char argv2[16];
char argv3[16];
char argv4[16];


// The arguments converted to integers
long arg1;
long arg2;
long arg3;
long arg4;

/* Clear the current command parameters */
void resetCommand() {
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  memset(argv3, 0, sizeof(argv3));
  memset(argv4, 0, sizeof(argv4));
  arg1 = 0;
  arg2 = 0;
  arg3 = 0;
  arg4 = 0;
  arg = 0;
  index = 0;
}

/* Run a command.  Commands are defined in commands.h */
int runCommand() {
  int i = 0;
  char *p = argv1;
  char *str;
  int pid_args[4];
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);
  arg3 = atoi(argv3);
  arg4 = atoi(argv4); 
  

  switch(cmd) {
  
  case READ_ENCODERS:
    Serial.print(readEncoder(FRONT_LEFT));
    Serial.print(" ");
    Serial.println(readEncoder(FRONT_RIGHT));
    Serial.print(readEncoder(BACK_LEFT));
    Serial.print(" ");
    Serial.println(readEncoder(BACK_RIGHT));
    break;
   case RESET_ENCODERS:
    resetEncoders();
    resetPID();
    Serial.println("OK");
    break;
  case MOTOR_SPEEDS:
    /* Reset the auto stop timer */
    resetPID();
    resetEncoders();
    lastMotorCommand = millis();
    if (arg1 == 0 && arg2 == 0 && arg3 == 0 && arg4 == 0) 
    {
      setMotorSpeeds(0, 0, 0, 0);
      resetPID();
      moving = 0;
    }
    else moving = 1;
    if(arg1 >= 12){
    arg1 = 8;
    } 
  if(arg2 >= 12){
    arg2 = 8;
    } 
  if(arg3 >= 12){
    arg3 = 8;
    } 
  if(arg4 >= 12){
    arg4 = 8;
    }
    frontLeftPID.targetTicksPerFrame = arg1;
    frontRightPID.targetTicksPerFrame = arg2;
    backLeftPID.targetTicksPerFrame = arg3; 
    backRightPID.targetTicksPerFrame = arg4;
    
    Serial.println("OK"); 
    break;
  case MOTOR_RAW_PWM:
    /* Reset the auto stop timer */
    lastMotorCommand = millis();
    resetPID();
    moving = 0; // Sneaky way to temporarily disable the PID
    setMotorSpeeds(arg1, arg2, arg3, arg4);
    Serial.println("OK"); 
    break;
  case UPDATE_PID:
    while ((str = strtok_r(p, ":", &p)) != '\0') {
      pid_args[i] = atoi(str);
       i++;
    }
    kd = pid_args[0];
    kd = pid_args[1];
    ki = pid_args[2];
    Serial.println("OK");
    break;
//#endif
  default:
    Serial.println("Invalid Command");
    break;
  }
}

/* Setup function--runs once at startup. */
void setup() {
  Serial.begin(BAUDRATE);


    //set as inputs
  // set motor DIR and PWM pins as output 
    pinMode(FRONT_RIGHT_MOTOR_PWM, OUTPUT);
    pinMode(FRONT_LEFT_MOTOR_PWM, OUTPUT); 
    pinMode(BACK_RIGHT_MOTOR_PWM, OUTPUT); 
    pinMode(BACK_LEFT_MOTOR_PWM, OUTPUT); 

    pinMode(FRONT_RIGHT_MOTOR_DIR, OUTPUT);
    pinMode(FRONT_LEFT_MOTOR_DIR, OUTPUT); 
    pinMode(BACK_RIGHT_MOTOR_DIR, OUTPUT); 
    pinMode(BACK_LEFT_MOTOR_DIR, OUTPUT);  
    
  //set Encoder pins as inputs and config interrupts
    pinMode(FRONT_LEFT_ENC_PIN_A, INPUT);
    pinMode(FRONT_LEFT_ENC_PIN_B, INPUT);

    pinMode(FRONT_RIGHT_ENC_PIN_A, INPUT);
    pinMode(FRONT_RIGHT_ENC_PIN_B, INPUT);

    pinMode(BACK_LEFT_ENC_PIN_A, INPUT);
    pinMode(BACK_LEFT_ENC_PIN_B, INPUT);

    pinMode(BACK_RIGHT_ENC_PIN_A, INPUT);
    pinMode(BACK_RIGHT_ENC_PIN_B, INPUT);

    attachInterrupt(digitalPinToInterrupt(FRONT_LEFT_ENC_PIN_A), updateEncoderFL, RISING);
    

    attachInterrupt(digitalPinToInterrupt(FRONT_RIGHT_ENC_PIN_A), updateEncoderFR, RISING);
    

    attachInterrupt(digitalPinToInterrupt(BACK_LEFT_ENC_PIN_A), updateEncoderBL, RISING);


    attachInterrupt(digitalPinToInterrupt(BACK_RIGHT_ENC_PIN_A), updateEncoderBR, RISING);
    

  initMotorController();
  resetPID();


/* Attach servos if used */
  #ifdef USE_SERVOS
    int i;
    for (i = 0; i < N_SERVOS; i++) {
      servos[i].initServo(
          servoPins[i],
          stepDelay[i],
          servoInitPosition[i]);
    }
  #endif
}

/* Enter the main loop.  Read and parse input from the serial port
   and run any valid commands. Run a PID calculation at the target
   interval and check for auto-stop conditions.
*/
void loop() {
  while (Serial.available() > 0) {
    
    // Read the next character
    chr = Serial.read();

    // Terminate a command with a CR
    if (chr == 13) {
      if (arg == 1) argv1[index] = NULL;
      else if (arg == 2) argv2[index] = NULL;
      else if (arg == 3) argv3[index] = NULL;
      else if (arg == 4) argv4[index] = NULL;
      runCommand();
      resetCommand();
    }
    // Use spaces to delimit parts of the command
    else if (chr == ' ') {
      // Step through the arguments
      if (arg == 0){
         arg = 1;
      }
      else if (arg == 1)  {
        argv1[index] = NULL;
        arg = 2;
        index = 0;
      }
      else if (arg == 2)  {
        argv2[index] = NULL;
        arg = 3;
        index = 0;
      }
      else if (arg == 3)  {
        argv3[index] = NULL;
        arg = 4;
        index = 0;    
      }
      continue;
    }
    else {
      if (arg == 0) {
        // The first arg is the single-letter command
        cmd = chr;
      }
      else if(arg == 1) {
        // Subsequent arguments can be more than one character
        argv1[index] = chr;
        //Serial.println(argv1[index]);
        index++;
        
      }
      else if (arg == 2) {
        argv2[index] = chr;
        //Serial.println(argv2[index]);
        index++;
      }
      else if (arg == 3) {
        argv3[index] = chr;
        //Serial.println(argv3[index]);
        index++;
      }
      else if (arg == 4) {
        argv4[index] = chr;
        //Serial.println(argv4[index]);
        index++;
      }
    }
  }
  
if(moving == 1){
  if (millis() > nextPID) {
    updatePID();
    nextPID += PID_INTERVAL;
  }
}
  
  // Check to see if we have exceeded the auto-stop interval
  // if ((millis() - lastMotorCommand) > AUTO_STOP_INTERVAL) {;
  //   setMotorSpeeds(0, 0, 0, 0);
  //   moving = 0;
  // }


//Sweep servos
#ifdef USE_SERVOS
  int i;
  for (i = 0; i < N_SERVOS; i++) {
    servos[i].doSweep();
  }
#endif
}
