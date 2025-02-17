# c-atmega328p-esp32-plant-assistant

**Project Description - English**

Plant Assistant is a smart system for monitoring plant growth conditions. The project uses ESP32, Arduino Nano, soil moisture sensors, DS18B20 temperature sensor, and PCF8563 RTC clock to collect and send real-time data to a server. The system allows:

Measuring soil moisture before and after watering  

Measuring ambient temperature

Storing data on a server via WiFi

Alert signaling when the soil is too dry

Viewing results on a web page

This allows remote plant monitoring and better irrigation management.

Technologies:

- ESP32 – WiFi communication, data transfer
  
- Arduino Nano – sensor processing
  
- DS18B20 – temperature sensor
  
- PCF8563 RTC – real-time clock for logging
  
- USART (UART) – ESP32-Arduino communication
  
- WiFi + HTTP Client – sending data to the server
  
- PHP + MySQL – database for storage and analysis
  
- HTML, CSS, JavaScript – web visualization

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Opis projektu - Polski**

„Roślinny Asystent” to inteligentny system nawadniania roślin, który na podstawie pomiarów wilgotności gleby oraz temperatury otoczenia automatycznie reguluje proces podlewania. Projekt wykorzystuje mikrokontrolery Arduino Nano oraz ESP32, a dane przechowywane są w bazie MySQL na lokalnym serwerze XAMPP.

System ma na celu wsparcie użytkowników w utrzymaniu odpowiednich warunków dla roślin w sposób efektywny i zautomatyzowany.

Główne funkcje

- Pomiar wilgotności gleby i temperatury w czasie rzeczywistym

- Automatyczne uruchamianie pompy na podstawie pomiarów wilgotności

- Dynamiczne dostosowanie harmonogramu pomiarów w zależności od temperatury

- Wysyłanie danych do bazy MySQL za pomocą ESP32

- Wizualizacja danych w aplikacji webowej

- Sygnalizacja stanu za pomocą diody RGB

Wykorzystane technologie

- Arduino Nano – obsługuje czujniki i sterowanie pompą

- ESP32 – obsługuje komunikację z serwerem

- RTC PCF8563 – zegar czasu rzeczywistego

- Czujnik wilgotności gleby – pomiar wilgotności

- DS18B20 – cyfrowy czujnik temperatury

- Pompa perystaltyczna – system podlewania

- UART, I2C, OneWire – interfejsy komunikacyjne

- XAMPP, MySQL, PHP – backend i baza danych

- HTML, CSS – frontend aplikacji webowej

Jak działa system?

- Pomiary i analiza

- Arduino Nano mierzy wilgotność gleby i temperaturę otoczenia

- Jeśli wilgotność spadnie poniżej 40%, system aktywuje pompę

- Jeśli temperatura przekroczy 28°C, zwiększa częstotliwość sprawdzania gleby

Komunikacja ESP32 → Serwer

- ESP32 łączy się z WiFi i przesyła dane do bazy MySQL

- Dane zawierają wilgotność gleby przed i po podlewaniu, temperaturę, datę i czas

Aplikacja webowa

- Dane są prezentowane w interfejsie webowym

- Możliwość monitorowania warunków w czasie rzeczywistym

Struktura kodu

- Arduino – kod obsługujący czujniki i pompę

- ESP32 – kod obsługujący komunikację WiFi i wysyłkę danych

- Backend – PHP do zapisu danych w MySQL

- Frontend – HTML, CSS do wizualizacji
