#include <Adafruit_NeoPixel.h>
#include<Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);
#define PIN 2	 // input pin Neopixel is attached to
#define POT_PIN A0	//Potentiometer to simulate humidity sensor
#define NUMPIXELS      12 // number of neopixels in Ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void ventilator(int flag);
Servo s;

int triggerPin = 7;
int echoPin = 8;

int motorControlPin = 9;
int gasSensor = A3;
int delayval = 100; // timing delay
int tempVal=0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int x = 0;

int ledPin = 3;
int ldrPin = A2;
int pot_reading = 0; 

void setup() {
  // setup pin modes
  //pinMode(ledPin, OUTPUT);
  Wire.begin();
  pinMode(0,OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(motorControlPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(A1, INPUT);
 
  pinMode(1,INPUT);

  lcd.begin(16, 2); 
  s.attach(9);
  pixels.begin();
  Serial.begin(9600);
}


void loop() {
	Wire.beginTransmission(4); 
  	x=digitalRead(1);
   	Wire.write(x); 

	Wire.endTransmission();   

  
  int cm = 0.01723 * readUltrasonicDistance(7, 8);
  
  Serial.print("Height is ");
  Serial.println(200 - cm);
  
  lcd.clear();
  lcd.setCursor(0,0);          
  lcd.print("Smart GreenHouse"); 
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  //lcd.setCursor(0,0);          
  //lcd.print("Hello"); 

  int ldrValue = analogRead(ldrPin); 
  //analogWrite(ledPin, ldrValue);
  int sensorValue = analogRead(gasSensor);
  // Print out the value you read
  Serial.print("Gas sensor:");
  Serial.println(sensorValue);
  
  Serial.print("LDR Value:");
  Serial.println(ldrValue);
  
  NeoPixel(ldrValue);
  Serial.print("Temperature:");
  tempVal= analogRead(A1);
  Serial.print(tempVal);
  Serial.println(" F");
  if(tempVal>160 || sensorValue>250){
    lcd.clear();
    lcd.setCursor(0,0);          
  	lcd.print("Ventilator Open"); 
    ventilator(1);
  	delay(1000);
    ventilator(0);
    lcd.setCursor(0,0);          
  	lcd.print("Ventilator Close"); 
   
  }
  
  
  
  pot_reading = analogRead(POT_PIN);
  Serial.print("Potentiometer: ");
  Serial.println(pot_reading);
  if(pot_reading<30){
  	for(int i = 0; i <= 255; i++){
  		analogWrite(10, i);
      delay(5);
  	}
    digitalWrite(0,HIGH);
    delay(2);
    digitalWrite(0,LOW);
    delay(2);
    digitalWrite(0,HIGH);
    delay(2);
    digitalWrite(0,LOW);  

  
  }
    //digitalWrite(motorControlPin, HIGH);
  else
  {
  	analogWrite(10, 0);
  }
  digitalWrite(motorControlPin, LOW);
  delay(1000); 
  delay(500);


//helloooo
}
void ventilator(int flag){
  int i=0;
  if(flag){
    
	for(i=0;i<180;i++)
		s.write(i);
	while(i--)
		s.write(i);
    //lcd.clear();
	}
  else{
   
    for(i=180;i>0;i--)
		s.write(i);
	while(i++<180)
		s.write(i);
    //lcd.clear();
  }
}


void setColor(){
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
  /*Serial.print("red: ");
  Serial.println(redColor);
  Serial.print("green: ");
  Serial.println(greenColor);
  Serial.print("blue: ");
  Serial.println(blueColor);*/
  
}


void NeoPixel(int ldrValue) {
  setColor();

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255  
    if(ldrValue < 935){
    	pixels.setPixelColor(i, pixels.Color(255, 255, 0));
    }
    else{
    	pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
     // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
    
    // Serial.println(i);
    
    if (i == NUMPIXELS){
    	i = 0; // start all over again!
        setColor();
	  }

  }
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}



