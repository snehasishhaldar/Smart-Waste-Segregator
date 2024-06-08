#include <Servo.h>


// Define for Motor Driver
#define MotorEnable 11
#define MotorIn_1 8
#define MotorIn_2 7

// Define for Ultrasonic Sensor
// for sensor1
#define TriggerPin1 6
#define EchoPin1 5

// for sensor2
#define TriggerPin2 4
#define EchoPin2 2

// for soil sensor
#define SoilSensor A0

// define for lights
#define redLed 13
#define GreenLed 12


Servo servo;

int motorSpeed = 120;
long distance1, duration1;
long distance2, duration2;

void setup() {
  Serial.begin(9600);

  servo.attach(3);

  pinMode(MotorEnable, OUTPUT);
  pinMode(MotorIn_1, OUTPUT);
  pinMode(MotorIn_2, OUTPUT);

  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);

  pinMode(TriggerPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);

  pinMode(SoilSensor, INPUT);

  pinMode(GreenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  digitalWrite(MotorIn_1, LOW);
  // digitalWrite(MotorIn_2, HIGH);
  // digitalWrite(GreenLed, HIGH);
  // digitalWrite(redLed, HIGH);

  delay(500);
}

void loop() {

  digitalWrite(redLed, HIGH);
  digitalWrite(TriggerPin1, LOW);
  digitalWrite(TriggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin1, HIGH);
  digitalWrite(TriggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin1, LOW);
  digitalWrite(TriggerPin2, LOW);

  // Measure the duration of the echo pulse
  duration1 = pulseIn(EchoPin1, HIGH);
  duration2 = pulseIn(EchoPin2, HIGH);

  // Calculate distance in centimeters
  distance1 = duration1 * 0.034 / 2;
  distance2 = duration2 * 0.034 / 2;

  if (distance1 <= 6) {
    digitalWrite(redLed, LOW);
    digitalWrite(GreenLed, HIGH);
    Serial.println("Waste Detected by Sensor 1");
    digitalWrite(MotorIn_1, LOW);
    digitalWrite(MotorIn_2, HIGH);
    analogWrite(MotorEnable, motorSpeed);

    // delay(500);


    delay(1200);

    digitalWrite(MotorIn_1, LOW);
    digitalWrite(MotorIn_2, LOW);
    digitalWrite(redLed, HIGH);
    delay(1200);

    int wasteValue = analogRead(SoilSensor);
    Serial.println(wasteValue);
delay(500);

    


    digitalWrite(MotorIn_1, LOW);
    digitalWrite(MotorIn_2, HIGH);
    analogWrite(MotorEnable, motorSpeed);
    
    




    if (distance2 <= 7) {

      if (wasteValue <= 100) {
        servo.write(0);
        Serial.println("Metal Detected");
      } else if (wasteValue <= 1010 && wasteValue > 100) {
        servo.write(100);
        Serial.println("Wet Waste Detected");
      }
      //  else if (wasteValue <=1015 && wasteValue >750)

      // {
      //   servo.write(100);
      //   Serial.println("Organic Waste Detected");
      // }

      else {
        servo.write(180);
        Serial.println("Plastic Detected");
      }

      delay(100);
    }



    delay(4000);
    servo.write(0);
  }

  else {
    // Turn off the motor if no waste detected by sensor 1
    digitalWrite(MotorIn_1, LOW);
    digitalWrite(MotorIn_2, LOW);
    servo.write(0);
    digitalWrite(redLed, HIGH);
  }
}
