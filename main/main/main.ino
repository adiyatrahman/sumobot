// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "NewPing.h"
// #include "Button.h"


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
// const int buttonPin = 1;

int button_state = 0;

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
// Button pushButton(PUSHBUTTON_PIN_2);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;


void setup() {
  // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed message
    Serial.begin(115200);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    
    // pinMode(IRLINEFOLLOW_PIN_OUT, INPUT);
    // pushButton.init();
    pinMode(PUSHBUTTON_PIN_2, INPUT_PULLUP);
    // button_state = digitalRead(PUSHBUTTON_PIN_2);
    while (!digitalRead(PUSHBUTTON_PIN_2)) {
      Serial.println("Not Pressed");
    }
    // button_state = 1;
    Serial.println("Pressed");
    
}

void loop() {
  startRoutine();
  delay(2000);
  //while the button is not pressed, do nothing
    // int left_distance = hcsr04_l.ping_cm();
    // int front_distance = hcsr04_f.ping_cm();
    // int right_distance = hcsr04_r.ping_cm();

    // while (left_distance > 20 && front_distance > 20 && right_distance > 20) {
    //     search();
    //     delay(10);
    //     left_distance = hcsr04_l.ping_cm();
    //     front_distance = hcsr04_f.ping_cm();
    //     right_distance = hcsr04_r.ping_cm();        
    // }
    // dcMotorDriverL298.stopMotors();
    // delay(20000);

    // while (front_distance > 10) {
    //   if (left_distance < front_distance) {
    //     turnLeft();
    //   }

    //   if (right_distance < front_distance) {
    //     turnRight();
    //   } 
    // }

    // attack();
}

void turnRight() {
    dcMotorDriverL298.setMotorA(250,1);
    dcMotorDriverL298.setMotorB(250,0);
}

void turnLeft() {
    dcMotorDriverL298.setMotorA(250,0);
    dcMotorDriverL298.setMotorB(250,1);
}

void attack() {
    dcMotorDriverL298.setMotorA(250,1);
    dcMotorDriverL298.setMotorB(250,1);
}


void search() {
    dcMotorDriverL298.setMotorA(250,1);
    dcMotorDriverL298.setMotorB(100,1);
}

void startRoutine() {
  // Start delay.
  delay(2000);

  // Turn right around 45 degress.
  dcMotorDriverL298.setMotorA(250,1);
  dcMotorDriverL298.setMotorB(250,0);
  delay(500);

  dcMotorDriverL298.stopMotors();
  // Go straight.
  dcMotorDriverL298.setMotorA(250,0);
  dcMotorDriverL298.setMotorB(250,0);
  delay(1000);

  dcMotorDriverL298.stopMotors();

  // Turn left until opponent is detected.
  dcMotorDriverL298.setMotorA(250,0);
  dcMotorDriverL298.setMotorB(250,1);
  delay(500);
  dcMotorDriverL298.stopMotors();
  // uint32_t startTimestamp = millis();
  // while (hcsr04_f.ping_cm() > 30) {
  //   // Quit if opponent is not found after timeout.
  //   if (millis() - startTimestamp > 5000) {
  //     break;
  //   }
  // }
  // attack(); 
  
 }



