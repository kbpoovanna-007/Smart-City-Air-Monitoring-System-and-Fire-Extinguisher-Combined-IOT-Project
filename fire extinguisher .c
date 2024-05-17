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

#define pump 6

//Setting up 
void setup ()
{

  pinMode (Left, INPUT);
  pinMode (Right, INPUT);
  pinMode (Forward, INPUT);

  pinMode (enA, OUTPUT);
  pinMode (enB, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);

  analogWrite(enA, 255);
  analogWrite(enB, 255);
  myservo.attach (11);
  myservo.write (90);
}



void loop ()
{
  myservo.write (90);   

  //Move forward
  if (digitalRead (Left) == 1 && digitalRead (Right) == 1 && digitalRead (Forward) == 1)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (digitalRead (Forward) == 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    fire = true;
  }
  else if (digitalRead (Left) == 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (digitalRead (Right) == 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  delay (300);     

  while (fire == true)
  {
    put_off_fire ();
  }
}


//Function to put off fire
void put_off_fire ()
{

  delay (500);
  
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

  digitalWrite (pump, HIGH);

  delay (500);

  for (pos = 50; pos <= 130; pos += 1)
  {
    myservo.write (pos);
    delay (10);
  }

  for (pos = 130; pos >= 50; pos -= 1)
  {
    myservo.write (pos);
    delay (10);
  }

  digitalWrite (pump, LOW);

  myservo.write (90);
  fire = false;
}
