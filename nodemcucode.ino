

#include <ESP8266WiFi.h>


String apiKey = "RV63GEGRK89C25EQ"; 


//  Enter your Write API key from ThingSpeak

const char *ssid =  "HARIRAM";     // replace with your wifi ssid and wpa2 key
const char *pass =  "123456789";
const char* server = "api.thingspeak.com";

String get_data;
String iot1 ;

WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
  
                      if(Serial.available()>0)
                      {

        
                          get_data = Serial.readString();
                          //String iot = c.substring(0,2);
                         // int len=Integer.parseInt(iot);
                         // String iot1 = c.substring(3,(len-1));

                          String iot = get_data.substring(0,3);
                          int len=iot.toInt();
                          iot1 = get_data.substring(3,(len+3));
                          
                          //Serial.println("******************************");
                          Serial.println(iot1);
                          //Serial.println("******************************");
                                     
                      }
      

                         
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             

                             postStr +="&field1=";
                             postStr += String(iot1);
 


                             

                             postStr += "\r\n\r\n\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 

                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(15000);
}
