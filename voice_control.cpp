#define BLYNK_TEMPLATE_ID "TMPLQBbJdPyF"
#define BLYNK_DEVICE_NAME "IoT"
#define BLYNK_AUTH_TOKEN "PSHf6PrMYPysgi65w150d_bXxa976bhR"
#define BLYNK_PRINT Serial

#include "NewPing.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIGGER_PIN D7
#define ECHO_PIN D8 
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool forward = 0; bool backward = 0; bool left = 0; bool right = 0; int Speed = 255;
int val; bool m;

char auth[] = BLYNK_AUTH_TOKEN ;
char ssid[] = "DJ";
char pass[] = "hotspot1234";

BLYNK_WRITE(V0)
{
  Speed = param.asInt();
  Serial.println(Speed);
}

BLYNK_WRITE(V1)
{
  forward = param.asInt(); 
}

BLYNK_WRITE(V2)
{
  backward = param.asInt(); 
}

BLYNK_WRITE(V3)
{
  left = param.asInt(); 
}

BLYNK_WRITE(V4)
{
  right = param.asInt(); 
}


BLYNK_WRITE(V5)
{
  Serial.println("Forward_voice");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  delay(5000);
}

BLYNK_WRITE(V6)
{
  Serial.println("Backward_voice");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  delay(5000);
}

BLYNK_WRITE(V7)
{
  Serial.println("Left_voice");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  delay(5000);
}

BLYNK_WRITE(V8)
{
  Serial.println("Right_voice");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  delay(5000);
}

BLYNK_WRITE(V9)
{
 val = param.asInt();
}

BLYNK_WRITE(V10)
{
  m = param.asInt();
}

void carcontrol()
{
  if (forward == 1)
  {
    car_forward();
  }
  else if (backward == 1)
  {
    car_backward();
  }
  else if (left == 1)
  {
    car_left();
  }
  else if (right == 1)
  {
    car_right();
  }
  else
  {
    car_stop();
  }
  
}

void handcontrol()
{
  if (val == 1)
  {
    Serial.println("Hand Forward");
    car_forward();
  }
  else if (val == 2)
    {
      Serial.println("Hand Backward");
      car_backward();
    }
  else if (val == 3)
  {
    Serial.println("Hand Right");
    car_right();
  }
  else if  (val == 4)
  {
    Serial.println("Hand Left");
    car_left();
  }
  else
  {
    Serial.println("Hand Stop");
    car_stop();
  }
}


void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D1, OUTPUT); // left in1
  pinMode(D2, OUTPUT); // left in2
  pinMode(D3, OUTPUT); // right in1
  pinMode(D4, OUTPUT); // right in2
  pinMode(D5, OUTPUT);
  pinMode(D0, OUTPUT);
 
}

void loop()
{
  Blynk.run();
  if (m == 0){
  carcontrol();
  }
  else{
  handcontrol();
  }

}

void car_forward()
{
  Serial.println("forward");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}

void car_backward()
{
  Serial.println("backward");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}

void car_left()
{
  Serial.println("left");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}


void car_right()
{
  Serial.println("right");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}


void car_stop()
{
  Serial.println("stop");
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
