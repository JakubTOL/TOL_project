#include <OneWire.h>
#include <DallasTemperature.h>// deklaracja biobliotek które używamy dla DS18B20

//na który port GPIO doprowadzony sygnał BUS
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);//dane zczytywane z lini BUS

DallasTemperature sensors(&oneWire);

// tablica przechowująca adresy urzadzeń z lini BUS
DeviceAddress insideThermometer;

void setup(void)
{
  Serial.begin(2400); //inicjalizacja monitora szeregowego

  // wyszukiwanie urządzeń na BUS
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements ??  sposób połączenia sensora wg dokumentacji sensora
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  
  // adresy znalezione na BUS
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();
  
  sensors.setResolution(insideThermometer, 12); // ustawienie rozdzielczości czujnika, wg noty katalogowej maksymalna to 2^12
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();
}

// temp dla danego urządzenia
void printTemperature(DeviceAddress deviceAddress) //docelowo drukowanie odczytanych wartości z każdego urządzenia 
{
 
  float tempC = sensors.getTempC(deviceAddress); // pobieranie danych z sensora za pomocą wewnętrznej funkcji; float bo zmienna z miejscami po przecinku w temperaturze wyświtlanej 
  Serial.print("Temperatura w stopniach Celsjusza: ");
  Serial.println(tempC);
 // Serial.print(" Temp F: ");
 // Serial.println(DallasTemperature::toFahrenheit(tempC)); // Celsjusze na farenhaity
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // rządanie od wszystkich czujników na lini BUS
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // wysłanie komendy aby uzyskać temp
  //Serial.println("DONE");
  
  printTemperature(insideThermometer);
}

// drukowanie adresu urządzenia
void printAddress(DeviceAddress deviceAddress) //pętla kolejno szeregująca urządzenia, które mają podać swój adres jeśli używamy więcej niż jednego
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
