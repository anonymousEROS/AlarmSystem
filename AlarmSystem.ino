
#include <LiquidCrystal_I2C.h>
#include <Temperature_LM75_Derived.h>

//input for switches
const int SW1=29;
const int SW2=28;
const int SW3=27;
const int SW4=26;
//input for LED
const int LED1=3;
const int LED2=4;
const int LED3=5;
const int LED4=6;
const int LED5=9;
const int LED6=10;
const int LED7=11;
const int LED8=12;
//Switch State
int SWSTATE1=0;
int SWSTATE2=0;
int SWSTATE3=0;
int SWSTATE4=0;


int CLK=39;
int DT=40;
int SW=41;

 
int counter=0;
int currentStateCLK;
int previousStateCLK;  

Generic_LM75 LM75;


//const int i2c_addr=0x27;
LiquidCrystal_I2C lcd(0x27, 16, 4);


void setup() {
  // put your setup code here, to run once:

  pinMode(LED1,OUTPUT);
  pinMode(SW1,INPUT_PULLUP);
  pinMode(LED2,OUTPUT);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(LED3,OUTPUT);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(LED4,OUTPUT);
  pinMode(SW4,INPUT_PULLUP);


  //encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);

  //Setting LED pins as OUTPUTS
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED8,OUTPUT);
  
  //tester for each task 
  Serial.begin(9600);
  
  previousStateCLK=digitalRead(CLK);

  //init lcd screen
  lcd.init();
  //turn on backlight
  lcd.backlight();

}

void loop() {
  unsigned long currentMillis = millis();
  
  currentStateCLK=digitalRead(CLK);

 if(currentStateCLK != previousStateCLK){

  if(digitalRead(DT) != currentStateCLK){
    counter--;
    if(counter < 60){
      counter=60;
    }
  }
  else{
    counter++;
    if(counter>120){
      counter=120;
    }
  }

 }
  
  previousStateCLK=currentStateCLK;
  
 
  SWSTATE1=digitalRead(SW1);
  SWSTATE2=digitalRead(SW2);
  SWSTATE3=digitalRead(SW3);
  SWSTATE4=digitalRead(SW4);


   if(SWSTATE1 == LOW){
    digitalWrite(LED1,HIGH);
    lcd.display(); 
  }
  else{
    digitalWrite(LED1,LOW);
    lcd.noDisplay();
      
  }
   if(SWSTATE2 == LOW){
    digitalWrite(LED2,HIGH);
    lcd.setCursor(0,0);
    lcd.print("Heat Mode");
    lcd.setCursor(0,1);
    lcd.print("Set Temp: ");
    lcd.print(counter);
    lcd.print(" F");
    lcd.setCursor(0,2);
    lcd.print("Temp = ");
    lcd.print(LM75.readTemperatureF());
    lcd.print(" F");
   }
  else{
    digitalWrite(LED2,LOW);
  
  }
   if(SWSTATE3 == LOW){
    digitalWrite(LED3,HIGH);
    lcd.setCursor(0,0);
    lcd.print("Cool Mode");
    lcd.setCursor(0,1);
    lcd.print("Set Temp: ");
    lcd.print(counter);
    lcd.print(" F");
    lcd.setCursor(0,2);
    lcd.print("Temp = ");
    lcd.print(LM75.readTemperatureF());
    lcd.print(" F");
  }
  else{
     
    digitalWrite(LED3,LOW);
   
  }
   if(SWSTATE4 == LOW){
    digitalWrite(LED4,HIGH);
    lcd.setCursor(0,0);
    lcd.print("Auto Mode");
    lcd.setCursor(0,1);
    lcd.print("Set Temp: ");
    lcd.print(counter);
    lcd.print(" F");
    lcd.setCursor(0,2);
    lcd.print("Temp = ");
    lcd.print(LM75.readTemperatureF());
    lcd.print(" F");
  }
  else{
     
    digitalWrite(LED4,LOW);  
  }

  if(SWSTATE2 == LOW && SWSTATE3==LOW || SWSTATE2 == LOW && SWSTATE4==LOW || 
  SWSTATE3 == LOW && SWSTATE4==LOW){
    digitalWrite(LED5, HIGH);
    delay(1000);
    digitalWrite(LED5, LOW);
    delay(1000);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
    
    lcd.clear();
    lcd.print("Mode Invalid");
    delay(5000);
    lcd.clear();  
  }
    if(SWSTATE2 == LOW &&  counter > LM75.readTemperatureF()){
    digitalWrite(LED7,HIGH);
    digitalWrite(LED5,HIGH);
    }
    else{
      digitalWrite(LED7,LOW);
       digitalWrite(LED5,LOW);
    }
    if(SWSTATE2 == LOW && counter <= LM75.readTemperatureF()){
     digitalWrite(LED6,HIGH);
    }
    else{
      digitalWrite(LED6,LOW);
    }
      
    if(SWSTATE3 == LOW && counter < LM75.readTemperatureF()){
     digitalWrite(LED8,HIGH); 
     digitalWrite(LED5,HIGH);
    }
    else{
      digitalWrite(LED8,LOW);
      digitalWrite(LED5,LOW);
    }
    if(SWSTATE3 == LOW && counter >= LM75.readTemperatureF()){
    digitalWrite(LED6,HIGH);
    }
    else{
      digitalWrite(LED6,LOW);
      
    }
   
    if(SWSTATE4 == LOW && counter < LM75.readTemperatureF()){
    digitalWrite(LED8,HIGH);
    digitalWrite(LED5,HIGH);
    }
    else{
      digitalWrite(LED8,LOW);
      digitalWrite(LED5,LOW);
    }
    if(SWSTATE4 == LOW && counter > LM75.readTemperatureF()){
    digitalWrite(LED7,HIGH);
    digitalWrite(LED5,HIGH);
    }
    else{
    digitalWrite(LED7,LOW);
    digitalWrite(LED5,LOW);
      
    } 
    if(SWSTATE4 == LOW && counter == LM75.readTemperatureF()){
       digitalWrite(LED6,HIGH);
    }
    else{
      digitalWrite(LED6,LOW);
    }
    
  }
