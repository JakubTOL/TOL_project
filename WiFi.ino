#include <WiFi.h> //biblioteka połączenia WiFI
const char* ssid = "DeR.Net-Wola-Laska-82"; //Nazwa naszej sieci internetowej
const char* password = "DSNW4bdf9ff0"; // hasło do sieci
uint64_t chipid;
void setup() {
Serial.begin(115200);

WiFi.begin(ssid,password); //inicjalizacja połączenia sieciowego
//pętla jeśli cały czas łączy się z siecią
while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.println("Connecting to WiFi...");
}
//w momencie uzyskania połączenia z siecią wyświetla tekst oraz IP naszego ESP
Serial.println("Connected to the WiFi network");
Serial.println(WiFi.localIP());
}
// pętla która uzyskuje adres MAC naszego ESP (w pętli dlatego, że w domyśle nadając paczki danych będzie wyświetlało się z którego urządzenia aktualnie są nadawane)
void loop(){
  chipid=ESP.getEfuseMac();//ChipId=MAC adress urządzenia
  Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
  Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

  delay(3000);
}
