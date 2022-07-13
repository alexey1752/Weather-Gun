#include <UTFT.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

UTFT myGLCD(CTE32HR, 38, 39, 40, 41);

SFE_BMP180 pressure; 

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

void setup()
{
delay(1000);

Serial.begin(9600);

if(pressure.begin())                         // Инициализация датчика
Serial.println("Датчик подключен");      
else
{                                      
Serial.println("Датчик не подключен\n\n");  
while(1);                                
}
       
myGLCD.InitLCD(1); // Горизонтальная ориентация
myGLCD.setColor(0, 0, 0);
myGLCD.clrScr();
myGLCD.setColor(0, 255, 0);

for (int i = 0; i < 2; i++) 
{
myGLCD.setColor(255, 255, 255);
myGLCD.setFont(BigFont);
myGLCD.print("Waiting data of GPS...", CENTER, 217);
delay(200);
myGLCD.fillCircle(240 + 40 * (cos(-i * PI / 4)), 120 + 40 * (sin(-i * PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 7)*PI / 4)), 120 + 40 * (sin(-(i + 7)*PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 6)*PI / 4)), 120 + 40 * (sin(-(i + 6)*PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 5)*PI / 4)), 120 + 40 * (sin(-(i + 5)*PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 4)*PI / 4)), 120 + 40 * (sin(-(i + 4)*PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 3)*PI / 4)), 120 + 40 * (sin(-(i + 3)*PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 2)*PI / 4)), 120 + 40 * (sin(-(i + 2)*PI / 4)), 10); delay(550);
myGLCD.fillCircle(240 + 40 * (cos(-(i + 1)*PI / 4)), 120 + 40 * (sin(-(i + 1)*PI / 4)), 10); delay(550);
myGLCD.clrScr();
}

myGLCD.print("No satellite connection", CENTER, 160);

delay(4500);
}



void loop()
{
char status;
double T,P,p0,a;
char Tc[5];
char Pc[5];   
String PString = String(P);
String TString = String(T);

status = pressure.startTemperature();       // Считывание показаний
if(status!=0)
{                              // Если значение status не 0, выполняем следующию команду.
delay(status);                                
status = pressure.getTemperature(T);     
if(status!=0)
{                          // Если все хорошо, функция вернет 1, иначе вернет 0
Serial.print("Temperature: ");       
Serial.print(T,2);                   
//dtostrf(T, 5/*Полная_длина_строки*/, 1/*Количество_символов_после_запятой*/, Tc);
Serial.println(" C, ");              

/* Определяем показания атмосферного давления
 * Параметр указывает расширение, от 0 до 3 (чем больше расширение, тем больше точность, тем долше ждать)
 * Если все хорошо, функция pressure.startTemperature вернет status с количеством милисикунд
 * которые нужно подождать. Если какая то проблема, то функция вернет 0.
*/

status = pressure.startPressure(3);         // Считывание показания
if(status!=0)
{                              // Если значение status не 0, выполняем следующию команду.
delay(status);                           
status = pressure.getPressure(P,T);      
if(status!=0)
{                          // Если все хорошо, функция вернет 1, иначе вернет 0 
Serial.print("Absolute pressure: "); 
Serial.print(P,2);                  
PString = String(P);
TString = String(T);
Serial.print(" mbar, ");            
Serial.print(P*0.7500637554192,2);  
Serial.println(" mmHg");
}           

else Serial.println("error retrieving pressure measurement\n");}    // Ошибка получения давления
else Serial.println("error starting pressure measurement\n");}      // Ошибка запуска получения давления
else Serial.println("error retrieving temperature measurement\n");} // Ошибка получения температуры
else Serial.println("error starting temperature measurement\n");    // Ошибка запуска получения температуры
      
myGLCD.InitLCD(1);
myGLCD.clrScr();
myGLCD.setFont(BigFont);
//myGLCD.setFont(SevenSegNumFont);
myGLCD.print("Date: ", 7, 26);
myGLCD.print("Time: ", 7, 52);
myGLCD.print("Latitude: ", 7, 78);
myGLCD.print("longitude: ", 7, 104);
myGLCD.print("Temperature: ", 7, 130);
myGLCD.print(TString, 199, 130);
myGLCD.print("C", 282, 130);
myGLCD.print("Pressure: ", 7, 156);
myGLCD.print(PString, 160, 156);
myGLCD.print("mbar", 280, 156);
myGLCD.print("Humidity: ", 7, 182);
myGLCD.print("CO2: ", 7, 208);
myGLCD.print("Click to save measurements", CENTER, 260);
delay(20000);
}
