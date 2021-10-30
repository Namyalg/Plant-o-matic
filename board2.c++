#include <Wire.h>
#include <Keypad.h>

const int numRows= 4; //number of rows on the keypad
const int numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad

char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3
byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


void setup()
{
  delay(1000);
  Wire.begin(4);                
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
}



void loop()
{
    Serial.println("Welcome to Greenhouse!");
  	delay(100000);
}


void receiveEvent(int flag)
{
  int x = Wire.read();    
  Serial.println(x); 
 if (x==1)
 {
   //digitalWrite(led,HIGH);
   char keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY)
    {
    Serial.print("123");
    Serial.println("Authentication Successful! Welcome to Greenhouse!");
    //if(keypressed == "123")
    
    }
 }
}
