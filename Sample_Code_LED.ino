//Last Edited 7/11/2018 by Vitus Putra

#include <Servo.h>

int LED_Blue = 11;
int LED_Red = 10;
int LED_Green = 9;
Servo myServo;

//bounce button variable
const int LEDBtn = 4;
const int SUSPENDBtn = 2;
boolean lastLEDBtn = LOW;
boolean currentButtonLED = LOW;
boolean lastSUSPENDBtn = LOW;
boolean currentButtonSUSPEND = LOW;

boolean SUSPENDFULLDEGREE = false;
boolean LEDON = false;

bool toggle;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myServo.attach(8);
  toggle = true;
  pinMode(LED_Blue, OUTPUT); 
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(LEDBtn, INPUT);
  pinMode(SUSPENDBtn, INPUT);
  analogWrite(LED_Blue, 0);
  analogWrite(LED_Red, 0);
  analogWrite(LED_Green, 0);


}

void loop() {

  currentButtonLED = debounceLED(lastLEDBtn);
  currentButtonSUSPEND = debounceSUSPEND(lastSUSPENDBtn);

  if(lastLEDBtn == LOW && currentButtonLED == HIGH)
  {
    //TOGGLE LED
    LEDON = !LEDON;
    if(LEDON)
    {
      analogWrite(LED_Blue, 255);
      analogWrite(LED_Red, 255);
      analogWrite(LED_Green, 255);
    }
    else
    {
      analogWrite(LED_Blue, 0);
      analogWrite(LED_Red, 0);
      analogWrite(LED_Green, 0);
    }
  }
  if(lastSUSPENDBtn == LOW && currentSUSPENDBtn == HIGH)
  {
    //TOGGLE SUSPEND
    SUSPENDFULLDEGREE = !SUSPENDFULLDEGREE;
      if(SUSPENDFULLDEGREE)
    {
      Serial.println("1");
      myServo.write(90);
      delay(1000);
    }
    else
    {
      Serial.println("0");
      myServo.write(0);
      delay(1000);
    }
  }

  
}

boolean debounceLED(boolean last){
  boolean current = digitalRead(LEDBtn);
  if(last != current)
  {
    delay(5);
    current = digitalRead(LEDBtn);
  }
  return current;
}

boolean debounceSUSPEND(boolean last){
   boolean current = digitalRead(SUSPENDBtn);
  if(last != current)
  {
    delay(5);
    current = digitalRead(SUSPENDBtn);
  }
  return current;
}

