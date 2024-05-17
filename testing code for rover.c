#include <Servo.h>  
Servo myservo;

int pos = 0;
int motor_speed = 70;  
boolean fire = false;

#define Left 9      // left sensor
#define Right 10    // right sensor
#define Forward 8   //front sensor

//for controlling left motor
#define enA 3
#define in1 12
#define in2 4

//for controlling right motor
#define enB 5
#define in3 7
#define in4 2

//pump motor
#define pump 6      

void setup() {
  Serial.begin(9600);
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  
  pinMode(pump, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myservo.attach(11);
  myservo.write(90);
  
}


void loop() {

    myservo.write(90); //Sweep_Servo();

    //---------------------------------------------------
    //checking if motor driver is working or not
    speedControl();
    delay(500);

    //---------------------------------------------------
    //checking fire sensor
    Serial.print("\n\nLEFT: ");
    Serial.print(digitalRead(Left));
    Serial.print("\n\nRIGHT: ");
    Serial.print(digitalRead(Right));
    Serial.print("\n\nFORWARD: ");
    Serial.print(digitalRead(Forward));
    
    //---------------------------------------------------------
    //SERVO MOTOR WORKING FINE
    for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);  
    }
  
    for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
    } 
    //---------------------------------------------------------
    //pump motor fine
      digitalWrite(pump, HIGH);
    //---------------------------------------------------------

}





// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
  
  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
  
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
