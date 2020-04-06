#include <SD.h> //Include the library.
#include <TMRpcm.h> //Include the library.

TMRpcm tmrpcm; //Creating a player object.
int chipSelect = 4;

//initialize colors 
int RedLED = 13;  
int GreenLED = 12;  
int BlueLED = 11;  

int delaytime = 500; 

int sensorPin = A0; 
int sensorCounter = 0; // counter for the number of button presses
int sensorState = 0;       // current state of the button
int lastSensorState = 0;   // previous state of the button

int buttonPin = A1; //initialize button pin 
int buttonState = 0; //current state of the button


 
void setup(){ 
  
  //initialize the LED pin as outputs
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT); 
  
  // initialize the sensor pin as a input:
  pinMode(sensorPin, INPUT);
  
  //initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  if(!SD.begin(chipSelect)) //If the card is available.
  {
    Serial.println("SD fail"); //Write in the serial port "SD fail".
    return; //Return.
  }
  Serial.println("SD working");
  
}
 
void loop(){
  
  if(digitalRead(buttonPin)==1 && !tmrpcm.isPlaying()) //check if button is pressed, and nothing is playing.
  {  
    tmrpcm.play("sandstorm.mp3"); //Play music file 
    Serial.println("button was pressed");
  }
  
    // read the input on analog pin 0:
    sensorState = analogRead(sensorPin); 
  
  // compare the buttonState to its previous state
  if (sensorState !=lastSensorState) {
    // if the state has changed, increment the counter
    if (sensorState >=2000) {
     // if the current state is HIGH then the sensor went from off to on:
    sensorCounter++; 
    Serial.println("on"); 
    Serial.print("number of sensor flashes: ");
    Serial.println(sensorCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    
    // Delay a little bit to avoid bouncing
    delay(50);
}
  // save the current state as the last state, for next time through the loop
  lastSensorState = sensorState;
  
  	Serial.print("sensorCounter: ");
  	Serial.println(sensorCounter);
  //Alternates between Green, Blue & Red everytime you press the button
  if (sensorCounter ==1) {
     Green(); 
     Serial.println("Green");
  } 
  
  if (sensorCounter == 2) {
     Blue(); 
     Serial.println("Blue");
  } 
  
  if (sensorCounter == 3) {
     Red(); 
     Serial.println("Red");
  } 

    if (sensorCounter == 4) {
     sensorCounter = 0; 
     Serial.println("RESET");
  } 
  
    // print out the value you read: 
    Serial.println(sensorState); 
    delay(1); //delay in between reads for stability
  
}

//Green LED
void Green() {
 digitalWrite(GreenLED, HIGH);
    delay(delaytime);
    digitalWrite(GreenLED, LOW);
    delay(delaytime/4);
}

//Red LED
void Red() {
  
    digitalWrite(RedLED, HIGH);
    delay(delaytime);
    digitalWrite(RedLED, LOW);
    delay(delaytime/4);
}

//Blue LED 
void Blue() {
 digitalWrite(BlueLED, HIGH);
    delay(delaytime);
    digitalWrite(BlueLED, LOW);
    delay(delaytime/4);}
