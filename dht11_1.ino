/***********************************************************
File name: 18_DHT11.ino
Description: you can see the temperature and humidity data
             displayed on the LCD1602.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2015/05/02 
***********************************************************/
 
#include <dht11.h>
#include <LiquidCrystal.h>
#define DHT11PIN 6

 
dht11 DHT11;
LiquidCrystal lcd(7,2,13,12,11,10);  //Define the connection LCD pin  
void setup()
{ 
     lcd.begin(16, 2);    // 
     lcd.clear();         // 
     delay(1000); //
}
 
void loop()
{
    int chk = DHT11.read(DHT11PIN);
    lcd.setCursor(0, 0); // set the cursor to column 0, line 0
    lcd.print("Humidity:");// Print a message of "Humidity: "to the LCD.
    lcd.print((float)DHT11.humidity, 2);// Print a message of "Humidity: "to the LCD.
    lcd.print(" % "); // Print the unit of the centigrade temperature to the LCD.
    
    lcd.setCursor(0, 1); // set the cursor to column 0, line 0
    lcd.print("Temp:    ");// Print a message of "Temp: "to the LCD.
    lcd.print((float)DHT11.temperature, 2);// Print a centigrade temperature to the LCD. 
    lcd.print(" C "); // Print the unit of the centigrade temperature to the LCD.
    delay(1000);     
}
