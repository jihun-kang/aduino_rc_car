#include <SoftwareSerial.h>

// Setup Motor A (front and rear) pins
const int enableA = 6;
const int pinA1 = 8;
const int pinA2 = 7;

// Setup Motor B (front and rear) pins
const int enableB = 3;
const int pinB1 = 2;
const int pinB2 = 4;

// Setup Ultrasonic Sensor pins
//#define trigPin 10
//#define echoPin 11

int state;
int flag=0;        //makes sure that the serial only prints once the state

int blueTx=12; //TX설정 at
int blueRx=11; //RX설정
SoftwareSerial bluetooth(blueTx, blueRx);

const int SPEED = 255;

void setup() {
   pinMode (enableA, OUTPUT);
   pinMode (pinA1, OUTPUT);
   pinMode (pinA2, OUTPUT);

   pinMode (enableB, OUTPUT);
   pinMode (pinB1, OUTPUT);
   pinMode (pinB2, OUTPUT);

   // Configure the pin modes for the Ultrasonic Sensor
   //pinMode(trigPin, OUTPUT);
   //pinMode(echoPin, INPUT);
    
    Serial.begin(9600);
    bluetooth.begin(9600); //블루투스 시리얼 
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(bluetooth.available() > 0){     
      state = bluetooth.read();   
      flag=0;
    //  Serial.println(state);
    }   

    // if the state is '0' the DC motor will turn off
    if (state == '0') {
        digitalWrite(pinA1, LOW); 
        digitalWrite(pinA2, LOW);
        analogWrite(enableA, SPEED); // Motor A 속도조절 (0~255)
  
        digitalWrite(pinB1, LOW);
        digitalWrite(pinB2, LOW);
        analogWrite(enableB, SPEED); // Motor A 속도조절 (0~255)
       
        if(flag == 0){
          Serial.println("Motor: off");
          flag=1;
        }
    }
     // if the state is '1' the motor will turn up
    else if (state == '1') {
        digitalWrite(pinB1, LOW);
        digitalWrite(pinB2, LOW);
        
        digitalWrite(pinA1, HIGH);
        digitalWrite(pinA2, LOW);
        analogWrite(enableA, SPEED);// Motor A 속도조절 (0~255)

        if(flag == 0){
          Serial.println("Motor: up");
          flag=1;
        }
    }
    // if the state is '2' the motor will turn down
    else if (state == '2') {
        digitalWrite(pinB1, LOW);
        digitalWrite(pinB2, LOW);

        digitalWrite(pinA1, LOW);
        digitalWrite(pinA2, HIGH);
        analogWrite(enableA, SPEED);// Motor A 속도조절 (0~255)

        if(flag == 0){
          Serial.println("Motor: down");
          flag=1;
        }
    }
    // if the state is '2' the motor will turn left
    else if (state == '3') {      
        digitalWrite(pinB1, LOW);
        digitalWrite(pinB2, HIGH);
        analogWrite(enableB, SPEED);// Motor A 속도조절 (0~255)
       
        if(flag == 0){
          Serial.println("Motor: left");
          flag=1;
        }
    }
     // if the state is '1' the motor will turn right
    else if (state == '4') {
        digitalWrite(pinB1, HIGH);
        digitalWrite(pinB2, LOW);
        analogWrite(enableB, SPEED);// Motor A 속도조절 (0~255)

        if(flag == 0){
          Serial.println("Motor: right");
          flag=1;
        }
    }
}

