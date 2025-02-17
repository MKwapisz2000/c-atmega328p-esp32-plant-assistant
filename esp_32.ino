#include <WiFi.h>
#include <HTTPClient.h>

// Ustawienia WiFi
const char* ssid = "Galaxy S20 FE 5GF6D0";
const char* password = "rytm2804";
const char* serverUrl = "http://192.168.4.30/esp_project/save_data.php";  // Adres pliku PHP

HardwareSerial mySerial(1);  // UART do Arduino (pin 16 i 17)

const int ledPin = 2; // Pin dla wbudowanej diody LED

// Zmienne do przechowywania danych
String wilgotnosc_gleby_przed;
String wilgotnosc_gleby_po;
String temperatura;
String stan;
String godzina;
String data;

void setup() {
  pinMode(ledPin, OUTPUT);  // Ustawienie pinu LED jako wyjście
  digitalWrite(ledPin, LOW);  // Wyłączenie diody na starcie

  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // UART na pinach 16 i 17
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Dioda miga, gdy ESP32 próbuje połączyć się z WiFi
    digitalWrite(ledPin, !digitalRead(ledPin)); 
  }
  digitalWrite(ledPin, LOW);  // Wyłącz diodę po połączeniu z WiFi
}

void loop() {
  if (mySerial.available()) {
    String received = mySerial.readStringUntil('\n');  // Odczytaj dane z Arduino

    if (received == "start") {
      // Zainicjuj zmienne
      wilgotnosc_gleby_przed = mySerial.readStringUntil('\n'); 
      wilgotnosc_gleby_po = mySerial.readStringUntil('\n');
      temperatura = mySerial.readStringUntil('\n');
      stan = mySerial.readStringUntil('\n');
      godzina = mySerial.readStringUntil('\n');
      data = mySerial.readStringUntil('\n');
    }

    if (received == "koniec") {
      // Po otrzymaniu "koniec", prześlij dane do PHP
      if (sendToServer()) {
        digitalWrite(ledPin, HIGH);  // Zapal diodę, jeśli dane zostały wysłane
        delay(1000);                  // Trzymaj diodę zapaloną przez 0,5 sekundy
        digitalWrite(ledPin, LOW);   // Wyłącz diodę
      }
    }
  }
  delay(1000);  // Czekaj 1 sekundę
}

// Funkcja wysyłająca dane do PHP
bool sendToServer() {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Tworzenie danych w formacie: zmienne=wartości
  String payload = "wilgotnosc_gleby_przed=" + wilgotnosc_gleby_przed +
                   "&wilgotnosc_gleby_po=" + wilgotnosc_gleby_po +
                   "&temperatura=" + temperatura +
                   "&stan=" + stan +
                   "&godzina=" + godzina +
                   "&data=" + data;

  // Wysyłanie danych przez POST
  int httpResponseCode = http.POST(payload);
  http.end();
  
  // Zwróć true, jeśli dane zostały wysłane poprawnie
  return (httpResponseCode > 0);
}
