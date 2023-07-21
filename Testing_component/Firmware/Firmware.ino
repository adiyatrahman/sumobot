
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

// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
NewPing hcsr04_1(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_2(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
NewPing hcsr04_3(HCSR04_3_PIN_TRIG,HCSR04_3_PIN_ECHO);
Button pushButton(PUSHBUTTON_PIN_2);


// define vars for testing menu
const int timeout = 30000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    pinMode(IRLINEFOLLOW_PIN_OUT, INPUT);
    pushButton.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Hobby DC motors - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // Ultrasonic Sensor - HC-SR04 #1 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_1Dist = hcsr04_1.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_1Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 #2 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_2Dist = hcsr04_2.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_2Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // Ultrasonic Sensor - HC-SR04 #3 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_3Dist = hcsr04_3.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_3Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '5') {
    // IR Line Track Follower Sensor - Test Code
    //Read IR Line Follower Sensor. irLineFollowVar will be '0' if a black line was detected
    bool irLineFollowVar = digitalRead(IRLINEFOLLOW_PIN_OUT);
    Serial.print(F("LineFollow: ")); Serial.println(irLineFollowVar);

    }
    else if(menuOption == '6') {
    // Mini Pushbutton Switch - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButtonVal = pushButton.read();
    Serial.print(F("Val: ")); Serial.println(pushButtonVal);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Hobby DC motors"));
    Serial.println(F("(2) Ultrasonic Sensor - HC-SR04 #1"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04 #2"));
    Serial.println(F("(4) Ultrasonic Sensor - HC-SR04 #3"));
    Serial.println(F("(5) IR Line Track Follower Sensor"));
    Serial.println(F("(6) Mini Pushbutton Switch"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #1"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #2"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #3"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing IR Line Track Follower Sensor"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Mini Pushbutton Switch"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/