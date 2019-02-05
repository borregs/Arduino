#include <dht11.h>
dht11 DHT11;
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,2,13,12,11,10); 

#define DHT11PIN 6 // sensor de humedad
#define pumpPin 3  //bomba de agua
#define  gled  5            // LED verde
#define bled 4           // blue LED 
#define thermistorPin  A0 //Termistor
#define lightsense 9 //fotosensor
/*y aqui iria el sensor de ph y humedad de la tierra...
https://i.ytimg.com/vi/BE6ogFlKp6A/hqdefault.jpg */


unsigned long time;
unsigned long lastPumpTime;


int pumpPeriodHours = 6;      // horas de retraso
//int pumpPeriodSec;            // segundos de retraso H*60*60*1000
int pumpDurationSec = 10;     // segundos q estoy activado
int pumpPeriodSec = 30;    // inicializamos para probar
int statusPeriod = 5000;      // Tiempo en MS q estare prendido
int statusBlink = 200;        // Tiempo en MS q parpadeare como indicador

void setup()
{
pinMode(thermistorPin,INPUT);  
pinMode(lightsense,INPUT);
 pinMode(gled, OUTPUT);
 digitalWrite(gled, LOW);
 pinMode(bled, OUTPUT);
 digitalWrite(bled, LOW);
 //pumpPeriodSec = pumpPeriodHours * 60 * 60;         // Solo mientras probamos
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
  Serial.begin(9600); 
  //Serial.println("Presione la barra espaciadora para alternar entre relay O/I");
   lcd.begin(16, 2);    
   lcd.clear();         
}

void loop()
{
  static bool relayVal = 0;
  int op;
  lastPumpTime = millis();
 
 // Prendemos la Bomba de agua y esperamos
 digitalWrite(pumpPin, HIGH);
 digitalWrite(bled, HIGH);
 delay((pumpDurationSec*1000));
 digitalWrite(pumpPin, LOW);
 digitalWrite(bled, LOW);

 // Mientras esperamos vemos un led de control de perdida    
 time = millis();
 while ( ((time-lastPumpTime)/1000) < pumpPeriodSec ) {
   delay(statusPeriod-statusBlink);
   digitalWrite(gled, HIGH);
   delay(statusBlink);
   digitalWrite(gled, LOW);
   time = millis();

    int inservible = DHT11.read(DHT11PIN);
    lcd.setCursor(0, 0); 
    lcd.print("Humidity:");
    lcd.print((float)DHT11.humidity, 2);
    lcd.print(" % "); 
    
    lcd.setCursor(0, 1); 
    lcd.print("Temp:    ");
    lcd.print((float)DHT11.temperature, 2); 
    lcd.print(" C "); 
    delay(5000); 
      for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(100);
     }
    float a = analogRead(thermistorPin);
  //the calculating formula of temperature
  float resistor = (1023.0*10000)/a-10000;
  float tempC = (3435.0/(log(resistor/10000)+(3435.0/(273.15+25)))) - 273.15;
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Crop: Potatoes");
  lcd.setCursor(0, 1); 
  lcd.print("  Temp: ");
  lcd.print(tempC);
  lcd.print(" C  "); 
  delay(5000);
   for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position right;
    lcd.scrollDisplayRight();
     }

float bebepaquito = analogRead(lightsense);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Lights: ");
  lcd.setCursor(0, 1); 
  lcd.print(bebepaquito);
  lcd.print(" Lux");
  delay(5000);
  if(bebepaquito<1000.00){
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Check Lights system!!!");
      lcd.setCursor(0,1);
      lcd.print("> 1000 Lux required ");
     for (int x = 0; x < 25; x++) {
      delay(500);
      lcd.scrollDisplayLeft();
     }
      lcd.clear();
    }
  }

}





