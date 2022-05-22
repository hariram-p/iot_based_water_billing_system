#include<LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);

/*****************************************/
/*MAIN TANK ULTRASONIC SENSOR*/
const int trigPin = 7;
const int echoPin = 6;
long duration;
int distanceCm;

/*****************************************/

/*****************************************/
/*HOUSE 1 ULTRASONIC SENSOR*/
const int trigPin1 = 5;
const int echoPin1 = 4;
long duration1;
int distanceCm1;

/*****************************************/



/*****************************************/
/*HOUSE 2 ULTRASONIC SENSOR*/
const int trigPin2 = 3;
const int echoPin2 = 2;
long duration2;
int distanceCm2;

/*****************************************/

int valve_H1=A0; /*INLET SOLENOID VALVE FOR HOUSE1*/

int valve_H2=A1; /*INLET SOLENOID VALVE FOR HOUSE 2*/

int valve_O1=A2; /*OUTLET SOLENOID VALVE FOR HOUSE1*/

int valve_O2=A3; /*OUTLET SOLENOID VALVE FOR HOUSE2*/

int motor=A4; /*MAIN TANK MOTOR*/

String web_data,webdata_len;

String H1,H2;




int count1=0; /*INITIALIZE COUNT =0 FOR HOUSE 1*/
int count2=0; /*INITIALIZE COUNT =0 FOR HOUSE 2*/

int flag1=0; /*INITIALIZE FLAG=0 FOR HOUSE 1*/
int flag2=0; /*INITIALIZE FLAG=0 FOR HOUSE 2*/


 
void setup()
{
  
              lcd.begin(16,2);
              Serial.begin(9600);

         /*************************************/
      
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);

      /************************************/
         /*************************************/
      
      pinMode(trigPin1, OUTPUT);
      pinMode(echoPin1, INPUT);

      /************************************/
         /*************************************/
      
      pinMode(trigPin2, OUTPUT);
      pinMode(echoPin2, INPUT);

      /************************************/
 pinMode(valve_H1,OUTPUT);

  pinMode(valve_H2,OUTPUT);

   pinMode(valve_O1,OUTPUT);

    pinMode(motor,OUTPUT);


      /************************************/
        lcd.setCursor(0,0);
        lcd.print("water tank");
        lcd.setCursor(0,1);
        lcd.print("system");
        delay(2000);
        lcd.clear();
        
       /**********************************/
           
}



void loop() 
{
  
String amount_L;//water consumption amount FOR HOUSE 1

String amount_H;//water price FOR HOUSE 1
int water1=count1*10;
int price1=count1*200;
amount_L=String(water1);
amount_H=String(price1);
//house 2
String amount_L1;//water consumption amount FOR HOUSE 2

String amount_H1;//water price FOR HOUSE 2
int water2=count2*10;
int price2=count2*200;
amount_L1=String(water2);
amount_H1=String(price2);



        ultrasonic(); 

        ultrasonic1(); 
        ultrasonic2();





      web_data = "House1_"+amount_L+"_Amount_"+amount_H+"_House2_"+amount_L1+"_Amount_"+amount_H1;
      webdata_len = web_data.length();
      String send_data  = String(webdata_len)+"_"+web_data;
      Serial.print(send_data);
      delay(3000);
         
                 
}


void ultrasonic()
{
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distanceCm= duration*0.034/2;

         lcd.setCursor(0,1);
        lcd.print(distanceCm);

         lcd.print("   ");
          delay(1000);
        
   
if(distanceCm <= 4)
{

 lcd.setCursor(0,0);
  
  lcd.print("T1:F");
  
 digitalWrite(motor,LOW);/*OFF MOTOR*/
         
 }

else
{
     lcd.setCursor(0,0);
        
     lcd.print("T1:L");

     digitalWrite(motor,HIGH);/*ON MOTOR*/
  
}
   
}

void ultrasonic1()
{
        digitalWrite(trigPin1, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin1, LOW);
        duration1 = pulseIn(echoPin1, HIGH);
        distanceCm1= duration1*0.034/2;

        lcd.setCursor(5,1);
        lcd.print(distanceCm1);

         lcd.print("   ");
          delay(1000);
        



if(distanceCm1 <= 3 )
{

 lcd.setCursor(5,0);
 lcd.print("H1:F");

  
 digitalWrite(valve_H1,LOW);/*INLET SOLENOID VALVE CLOSES*/

 digitalWrite(valve_O1,HIGH); /*OUTLET SOLENOID VALVE OPEN*/

if(flag1==0)
   {
    count1++;
    flag1=1;
    
   }



          
 }

 


if(distanceCm1>=8)
   
    {

       digitalWrite(valve_H1,HIGH);/*INLET SOLENOID VALVE OPEN*/
        
          lcd.setCursor(5,0);
        
        lcd.print("H1:L");

   digitalWrite(valve_O1,LOW);/*OUTLET SOLENOID VALVE CLOSE*/
     flag1=0;


    }



}
void ultrasonic2()
{
        digitalWrite(trigPin2, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin2, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin2, LOW);
        duration2 = pulseIn(echoPin2, HIGH);
        distanceCm2= duration2*0.034/2;

        lcd.setCursor(10,1);
        lcd.print(distanceCm2);

         lcd.print("   ");
          delay(1000);
        



if(distanceCm2 <= 3 )
{

 lcd.setCursor(10,0);
 lcd.print("H2:F");

  
 digitalWrite(valve_H2,LOW);/*INLET SOLENOID VALVE CLOSE*/

 digitalWrite(valve_O2,HIGH); /*OUTLET SOLENOID VALVE OPEN*/

if(flag2==0)
   {
    count2++;
    flag2=1;
    
   }



          
 }

 


if(distanceCm2>=8)
   
    {

       digitalWrite(valve_H2,HIGH);/*INLET SOLENOID VALVE OPEN*/
       
       digitalWrite(valve_O2,LOW); /*OUTLET SOLENOID VALVE CLOSE*/
        
          lcd.setCursor(10,0);
        
        lcd.print("H2:L");

  
     flag2=0;


    }



}
