// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "NewPing.h"
#include "Button.h"


// Pin Definitions
#define DCMOTORDRIVERL298_PIN_INT1	2
#define DCMOTORDRIVERL298_PIN_ENB	5
#define DCMOTORDRIVERL298_PIN_INT2	4
#define DCMOTORDRIVERL298_PIN_ENA	3
#define DCMOTORDRIVERL298_PIN_INT3	6
#define DCMOTORDRIVERL298_PIN_INT4	7
#define HCSR04_1_PIN_TRIG	9
#define HCSR04_1_PIN_ECHO	8
#define HCSR04_2_PIN_TRIG	11
#define HCSR04_2_PIN_ECHO	10
#define HCSR04_3_PIN_TRIG	13
#define HCSR04_3_PIN_ECHO	12
#define IRLINEFOLLOW_PIN_OUT	A0
#define PUSHBUTTON_PIN_2	A1

// Global variables and defines

//function declarations
void back_away();
void turnRight();
void turnLeft();
void attack();
void startRoutine();


// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
NewPing hcsr04_l(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_f(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
NewPing hcsr04_r(HCSR04_3_PIN_TRIG,HCSR04_3_PIN_ECHO);
Button pushButton(PUSHBUTTON_PIN_2);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;
const int lineThreshold = 700;


void setup() {
  // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed message
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    
    pinMode(IRLINEFOLLOW_PIN_OUT, INPUT);
    pushButton.init();

    while (!pushButton.onPress()) {
    }
    startRoutine();
}

void loop() {
  //while the button is not pressed, do nothing
    //int left_distance = hcsr04_l.ping_cm();
  int front_distance = hcsr04_f.ping_cm();
    //int right_distance = hcsr04_r.ping_cm();
  int IRValue = analogRead(IRLINEFOLLOW_PIN_OUT);
    /*
    while (left_distance > 30 && front_distance > 30 && right_distance > 30) {
        turnRight();
    }

    while (left_distance < front_distance || right_distance < front_distance) {
      if (left_distance < front_distance) {
        turnRight();
      }

      if (right_distance < front_distance) {
        turnLeft();
      } 
    }
    */
  // turn around search for opponents
  while (IRValue < lineThreshold && front_distance > 30) {  
    turnRight();  
  }
  if (IRValue > lineThreshold ) {
    // Stop the robot
    back_away()
  }
  //if opponents found go forward
  if (front_distance <30 && IRValue < lineThreshold) {
    attack();
  }
    


}



void back_away() {
  dcMotorDriverL298.setMotorA(-200,1);
  dcMotorDriverL298.setMotorB(-200,1);
  delay(180);
  turnRight();
  delay(180);//turn 180 degrees to face center again
}

void turnRight() {
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,1);
}

void turnLeft() {
    dcMotorDriverL298.setMotorA(0,1);
    dcMotorDriverL298.setMotorB(200,1);
}

void attack() {
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,1);
}


void startRoutine() {
  // Start delay.
  delay(5000);

  // Turn right around 45 degress.
  dcMotorDriverL298.setMotorA(200,1);
  dcMotorDriverL298.setMotorB(0,1);
  delay(180);

  // Go straight.
  dcMotorDriverL298.setMotorA(200,1);
  dcMotorDriverL298.setMotorB(200,1);
  delay(450);

  // Turn left until opponent is detected.
  dcMotorDriverL298.setMotorA(0,1);
  dcMotorDriverL298.setMotorB(200,1);
  uint32_t startTimestamp = millis();
  while (hcsr04_f.ping_cm() > 30) {
    // Quit if opponent is not found after timeout.
    if (millis() - startTimestamp > 400) {
      break;
    }
  }
  
 }



