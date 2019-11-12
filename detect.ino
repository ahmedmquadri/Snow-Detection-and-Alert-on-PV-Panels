#include <SoftwareSerial.h>
#define RxD 7
#define TxD 6
#define DEBUG_ENABLED 1
#define PIN_VOLT A0
#define PIN_SNOW A5
SoftwareSerial blueToothSerial(RxD,TxD);
const double VThresh = 0.5; double Vcur = 0 ;
double Scur = 0 ;
//Software Serial Port //Bluetooth Set-up
//Defining Threshold Voltage
/***************************************************************************
* Function Name: getVoltage
* Description: get the Voltage data
* Return: voltagerequired ***************************************************************************/
double getVolt() {
double voltage = analogRead(PIN_VOLT); double VoltCal = (5*voltage)/1023; return VoltCal;
}
/*************************************************************************** * Function Name: getSnowDepth
* Description: get the snow depth proximity data
* Return: finalsnow
***************************************************************************/
double getSnowDepth() {
double snow = analogRead(PIN_SNOW); double snowvolt = (5*snow)/1023;
double len = -17.22*pow(snowvolt, 5) + 145.9*pow(snowvolt,4) - 480.9*pow(snowvolt,3) + 778.5*pow(snowvolt,2) - 640.5*snowvolt + 242.9;
double finalsnow = 44.5 - len; if(finalsnow <= 0)
{
finalsnow = 0;
}
return finalsnow;
}
/*************************************************************************** * Function Name:setup
* Description: setting up Bluetooth function
***************************************************************************/
 void setup()
{
Serial.begin(9600); pinMode(RxD, INPUT); pinMode(TxD, OUTPUT); setupBlueToothConnection();
}
void loop() { Vcur=getVolt(); Scur=getSnowDepth();
if(Vcur<=VThresh) {
Alert(); }
else {
Reading(); }
}
/*************************************************************************** * Function Name: Alert
* Description: prints out required error messages
***************************************************************************/
void Alert()
{
blueToothSerial.println("**************************"); blueToothSerial.println("********* ALERT *********"); blueToothSerial.println("**************************");
if(Scur==0) {
 blueToothSerial.println("Snow Pile Perry: It's either dark out, or something's wrong :( ");
 blueToothSerial.print("Snow Level: "); blueToothSerial.print(Scur); blueToothSerial.println("cm");
}
else
{
blueToothSerial.println("Snow Pile Perry: You should clear snow now!");
blueToothSerial.print("Snow Level: "); blueToothSerial.print(Scur); blueToothSerial.println("cm");
}
delay(5000); }
/*************************************************************************** * Function Name: Reading
* Description: prints out required readings
***************************************************************************/
void Reading() {
Scur=Scur-8;
if(Scur<0)
Scur=0;
blueToothSerial.println("Snow Pile Perry: Don't you worry.");

blueToothSerial.print("Snow Level: "); blueToothSerial.print(Scur); blueToothSerial.println("cm");
/*
blueToothSerial.print("Voltage Level: "); blueToothSerial.print(Vcur); blueToothSerial.println("V");
*/
blueToothSerial.println();
/*
Serial.print("Snow Level: "); Serial.println(Scur); Serial.print("Voltage Level: "); Serial.println(Vcur); Serial.println();
*/
delay(1800000);
}
/*************************************************************************** * Function Name: setupBlueToothConnection
* Description: initilizing bluetooth connction
***************************************************************************/
void setupBlueToothConnection() {
blueToothSerial.begin(9600);
blueToothSerial.print("AT"); delay(400);
blueToothSerial.print("AT+DEFAULT"); // Restore all setup value to factory setup delay(2000);
blueToothSerial.print("AT+NAMESolarSnowDetector"); // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
delay(400);
blueToothSerial.print("AT+PIN0000"); delay(400);
blueToothSerial.print("AT+AUTH1"); delay(400);
blueToothSerial.flush(); }
// set the pair code to connect
