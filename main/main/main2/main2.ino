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
void turnRight();
void turnLeft();
void attack();
void startRoutine();


// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
NewPing hcsr04_l(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_f(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
NewPing hcsr04_r(HCSR04_3_PIN_TRIG,HCSR04_3_PIN_ECHO);

int distance;


void setup() {
  // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed message
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    
    pinMode(IRLINEFOLLOW_PIN_OUT, INPUT);
    delay(3400);
}

void loop() {
    int IR_front = analogRead(IRLINEFOLLOW_PIN_OUT);
    // Serial.print("IR_front: ");
    // Serial.println(IR_front);
    delay(5);
    distance = hcsr04_f.ping_cm();
    // Serial.print("Distance: ");
    // Serial.println(distance);

    turnRight();  // start rotete if (distance < 20){
    while (distance < 60 && distance > 0 )  {
        attack(); 
        distance = hcsr04_f.ping_cm();
        IR_front = analogRead(IRLINEFOLLOW_PIN_OUT);
        if ( IR_front > 900) { break;}
    }
    
    
  if (IR_front > 900 )  // <  650 means white line
    {
    back_away();
    } 
}

void back_away() {
    Serial.println("Backing Away");
    dcMotorDriverL298.setMotorA(250,1);
    dcMotorDriverL298.setMotorB(250,1);
    delay(200);
    turnRight();
    delay(1000);//turn 180 degrees to face center again
  }

void turnRight() {
    Serial.println("Turning right");
    dcMotorDriverL298.setMotorA(250,1);
    dcMotorDriverL298.setMotorB(250,0);
}

void turnRight_slow() {
    Serial.println("Turning right");
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
}

void turnLeft() {
    Serial.println("Turning left");
    dcMotorDriverL298.setMotorA(200,0);
    dcMotorDriverL298.setMotorB(200,1);
}

void attack() {
    Serial.println("Attacking");
    dcMotorDriverL298.setMotorA(250,0);
    dcMotorDriverL298.setMotorB(250,0);
}



