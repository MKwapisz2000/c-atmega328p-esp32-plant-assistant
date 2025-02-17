# c-atmega328p-esp32-plant-assistant

**Project Description - English**

"Plant Assistant" is an intelligent plant watering system that automatically adjusts irrigation based on soil moisture and temperature readings. The project uses Arduino Nano and ESP32 microcontrollers, with data stored in a MySQL database on a XAMPP server.

The goal is to assist users in maintaining optimal plant conditions efficiently and automatically.

Main features

- Real-time soil moisture and temperature monitoring

- Automatic water pump activation based on soil moisture

- Dynamic scheduling of measurements based on temperature changes

- Data transmission to a MySQL database via ESP32

- Web application for real-time data visualization

- RGB LED signaling the moisture level

Technologies used

- Arduino Nano – manages sensors and pump control

- ESP32 – handles WiFi communication

- RTC PCF8563 – real-time clock module

- Soil moisture sensor – measures soil moisture

- DS18B20 – digital temperature sensor

- Peristaltic pump – watering system

- UART, I2C, OneWire – communication interfaces

- XAMPP, MySQL, PHP – backend and database

- HTML, CSS – frontend for the web application

How does it work?

- Measurement & Analysis

- Arduino Nano measures soil moisture and temperature

- If soil moisture drops below 40%, the system activates the pump

- If the temperature exceeds 28°C, soil moisture is checked more frequently

- ESP32 → Server Communication

- ESP32 connects to WiFi and sends data to a MySQL database

- Data includes soil moisture before and after watering, temperature, date, and time

- Web Application

- Displays real-time data

- Allows monitoring of plant conditions remotely

Code structure:

- Arduino – handles sensors and pump control

- ESP32 – manages WiFi and data transmission

- Backend – PHP for database interaction

- Frontend – HTML, CSS for visualization

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

- Komunikacja ESP32 → Serwer

- ESP32 łączy się z WiFi i przesyła dane do bazy MySQL

- Dane zawierają wilgotność gleby przed i po podlewaniu, temperaturę, datę i czas

- Aplikacja webowa

- Dane są prezentowane w interfejsie webowym

- Możliwość monitorowania warunków w czasie rzeczywistym

Struktura kodu

- Arduino – kod obsługujący czujniki i pompę

- ESP32 – kod obsługujący komunikację WiFi i wysyłkę danych

- Backend – PHP do zapisu danych w MySQL

- Frontend – HTML, CSS do wizualizacji
