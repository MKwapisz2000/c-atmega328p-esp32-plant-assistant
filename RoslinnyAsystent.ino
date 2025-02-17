
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "RTC_PCF8563.h"
#include "DS18B20_1Wire.h"


#define F_CLK         16000000UL  //Częstotliwość taktowania zegara [Hz]

// Parametry czasu
#define SEC           50          //Sekundy
#define MIN           29          //Minuty
#define H             17          //Godzina

// Parametry daty
#define DAY           28           //Dzień
#define WEEKDAY       2           //Dzień tygodnia (niedziela = 0, poniedziałek = 1)
#define MONTH         1           //Miesiać
#define YEAR          25          //Rok

// Parametry alarmu
#define MINA          30          //Minuta
#define MIN_OnOff     1           //Alarm ze względu na wartość minuty (tak = 1, nie = 0)
#define HA            17          //Godzina
#define H_OnOff       1           //Alarm ze względu na wartość godziny (tak = 1, nie = 0)
#define DAYA          28          //Dzień 
#define DAY_OnOff     0           //Alarm ze względu na dzień (tak = 1, nie = 0)
#define WEEKDAYA      2           //Dzień tygodnia
#define WEEKDAY_OnOff 1           //Alarm ze względu na dzień tygodnia (tak = 1, nie = 0)

// Parametry pompy perystaltycznej
#define STOP_US       1500        //Czas impulsu dla zatrzymania [us]
#define N_POMPA       8           //Prescaler dla pompy
#define F_POMPA       50          //Częstotliwość dla pompy [Hz]

// Parametry czujnika temperatury
#define MAX_TEMP      0x1C        //Maksymalna temperatura alarmowa 28st
#define MIN_TEMP      0x0F        //Minimalna temperatura alarmowa 15st
#define HISTEREZA     2.0         //Histereza - 2st

// Zmienne globalne
uint8_t i;
uint8_t j; 
volatile bool alarm_flag;
bool podlanie;
bool tempAlarmTEST = 0;

RTC_PCF8563 rtc1=RTC_PCF8563();
DS18B20_1Wire ds18b20_1 = DS18B20_1Wire(MAX_TEMP, MIN_TEMP, HISTEREZA); 

 


//.......................................................... MAIN ...............................................................
int main()
{
  char string1[50];
  char string2[50];

  char wilgotnosc_gleby_przed[20] = "brak";
  char wilgotnosc_gleby_po[20] = "brak";
  char temperatura[20] = "brak";
  char stan[20] = "brak";
  char godzina[20] = "brak";
  char data[20] = "brak";

  float soil_moisture = 0;
  bool gotowe_do_przesylu = 0;
  bool czestotliwosc_HighTemp = 0;
 
  //dioda RGB 
  //DDRD |= (1<<PD5); //R
  //DDRD |= (1<<PD6); //G
  
  //popmpa
  DDRB |= (1<<PB1);

  //dioda Arduino Nano
  PORTB &= ~(1<<PB5);

  //inicjalizacje 
  ExternalInterupts_init();
  ADC_init();
  PWM_init();
  USART_init();

  //ustawienia daty, czasu, alarmu:
  //dzien/dzien_tyg/miesiac/rok
  rtc1.setData(DAY, WEEKDAY, MONTH, YEAR);
  //sekundy/minuty/godziny
  rtc1.setTime(SEC, MIN, H);
  //minuta/ON_OFF/ godzina/ON_OFF/ dzien/ON_OFF/ dzien_tyg/ON_OFF/
  rtc1.setAlarm(MINA, MIN_OnOff, HA, H_OnOff, DAYA, DAY_OnOff, WEEKDAYA ,WEEKDAY_OnOff);
  

      //WILGOTNOSC GLEBY PRZED
      soil_moisture = checkMoisture();
      dtostrf(soil_moisture, 5,1, string1);
      sprintf(wilgotnosc_gleby_przed, "%s", string1);
      _delay_ms(100);

      //TEMPERATURA
      ds18b20_1.checkTemperature();
      dtostrf(ds18b20_1.getTemperature(), 5, 2, string1);
      sprintf(temperatura, "%s", string1);
      _delay_ms(100);

      //DATA
      sprintf(data, "%d.%d.%d", rtc1.getDay(), rtc1.getMonth(), rtc1.getYear());
      _delay_ms(100);
  
      //CZAS
      sprintf(godzina, "%d:%d", rtc1.getHour(), rtc1.getMinute());
      _delay_ms(100);

      //STAN
      sprintf(stan, "%s", "proba");

      //proba przesylu
      //_delay_ms(7000);
      //przesylParametrow(wilgotnosc_gleby_przed, wilgotnosc_gleby_po, temperatura, stan, godzina, data);
      _delay_ms(5000);
      
      
  while (1) 
  { 
    if(j!=3)
    {
      //Sprawdzenie temperatury w pomieszczeniu 
      ds18b20_1.checkTemperature();
    }
    else
    {
      //Testowa temperatura 28st
      tempAlarmTEST = 1;
    }

    //Sprawdzenie flagi alarmu DS18B20
    if((ds18b20_1.temp_alarm == 1)||(tempAlarmTEST == 1))
    {
      //W przypadku zwiększenia temperatury w pomieszczeniu - 
      //zwiększenie częstotliwości pomiaru wilgotności (z raz w tygodniu na codziennie) do momentu ustabilizowania temperatury

      rtc1.setAlarm(MINA, 1, HA, 1, DAYA, 0, WEEKDAYA,0);
      czestotliwosc_HighTemp = 1;
    }
    else if((ds18b20_1.temp_alarm == 0)&&(czestotliwosc_HighTemp == 1)&&(tempAlarmTEST == 0))
    {
      //Po ustabilizowaniu temperatury -
      //powrót do wcześniejszej częstotliwości pomiaru wilgotności

      uint8_t day = rtc1.getDay();
      uint8_t weekday = rtc1.getWeekday();
    
      rtc1.setAlarm(MINA, MIN_OnOff, HA, H_OnOff, day, DAY_OnOff, weekday ,WEEKDAY_OnOff);
      czestotliwosc_HighTemp = 0;
    }
    

    //Sprawdzenie flagi alarmu RTC
    if(alarm_flag == 1)
    {
      //WILGOTNOSC GLEBY PRZED
      soil_moisture = checkMoisture();
      dtostrf(soil_moisture, 5,1, string1);
      sprintf(wilgotnosc_gleby_przed, "%s", string1);

      //TEMPERATURA
      if(tempAlarmTEST != 1)
      {
        dtostrf(ds18b20_1.getTemperature(), 4, 1, string1);
        sprintf(temperatura, "%s", string1);
      }
      else
      {
        sprintf(temperatura, "%d", 29);
        tempAlarmTEST = 0;
      }
     
      //Sprawdzenie czy wiglotność jest odpowiednia (ewentualne podlanie) i obsługa diody RGB
      RGB(soil_moisture);

      //Pomiar wiglotnośi gleby po ewentulanym podlaniu
      if(podlanie == 1)
      {
        while(podlanie == 1)
        {
          soil_moisture = checkMoisture();
         
          //Zaktualizowanie zmiennej podlanie oraz stanu diody RGB
          RGB(soil_moisture);
        }

        //WILGOTNOSC GLEBY PO
        dtostrf(soil_moisture, 5,1, string1);
        sprintf(wilgotnosc_gleby_po, "%s", string1);
        //STAN
        sprintf(stan, "%s", "podlane");
        
        gotowe_do_przesylu = 1;
      }
      //Jeżeli podlewaie się nie odbyło
      else
      {
        //STAN
        sprintf(stan, "%s", "niepodlane");
        //WILGOTNOSC GLEBY PO
        sprintf(wilgotnosc_gleby_po, "%s", "brak");

        gotowe_do_przesylu = 1;
      }

      //Wyzerowanie flagi alarmu
      alarm_flag = 0;
      
  
      //DATA
      sprintf(data, "%d.%d.%d", rtc1.getDay(), rtc1.getMonth(), rtc1.getYear());
  
      //CZAS
      sprintf(godzina, "%d:%d", rtc1.getHour(), rtc1.getMinute());

      //Przesyl parametrow do esp32
      if(gotowe_do_przesylu == 1)
      {
        przesylParametrow(wilgotnosc_gleby_przed, wilgotnosc_gleby_po, temperatura, stan, godzina, data);
      }
      
    }

   


//-------------------------------------------------------------------------
//Dla prezentacji upływu czasu - przejsćie do nowego tygodnia/dnia co 10 sekund:
    if (i >= 10) {
        uint8_t day = rtc1.getDay();
        uint8_t weekday = rtc1.getWeekday();
        uint8_t month = rtc1.getMonth();
        uint8_t year = rtc1.getYear();

        //Alarm temperatury nie występuje - przechodzimy do nowego tygodnia
        if(czestotliwosc_HighTemp == 0)
        {
          day += 7; // Dodaj tydzień
          weekday = (weekday + 7) % 7;
        }
        //Alarm temperatury występuje - przechodzimy do nowego dnia
        else
        {
          day += 1; // Dodaj dzień
          weekday = (weekday + 1) % 7;
        }
        
        //Sprawdź przekroczenie liczby dni w miesiącu
        uint8_t daysInMonth = getDaysInMonth(month, year);
        if (day > daysInMonth) {
            day -= daysInMonth;
            month++;
    
            //Sprawdź przekroczenie miesiąca
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    
        //Zaktualizuj datę i czas w RTC
        rtc1.setData(day, weekday, month, year); 
        rtc1.setTime(SEC, MIN, H);
        i = 0;

        j++;
    }

    if(j == 8)
    {
      j = 0;
    }

    i++;
    
    
    _delay_ms(1000);

//-------------------------------------------------------------------------

  }
  
  return 0;
}



//.................................................... EXTERNAL_INT .............................................................
void ExternalInterupts_init()
{
  //failling edge
  EICRA |= (1<<ISC01);
  EIMSK |= (1<<INT0);

  //wlaczenie przerwań 
  sei();
}

ISR(INT0_vect)
{ 
  rtc1.INT();
  alarm_flag = 1;
}



//........................................................ USART ................................................................
void USART_init()
{
  UBRR0H = (unsigned char)(103>>8);
  UBRR0L = (unsigned char)103;
    
  //Adres we/wy rejestrów danych nadawczych USART i rejestry odbierania danych USART
  //UDR0

  //By bufor transmisji mógłbyć zapisany
  UCSR0A |= (1<<UDRE0);

  //Włączenie odbiornika
  UCSR0B |= (1<<RXEN0);

  //Włączenie nadajnika
  UCSR0B |= (1<<TXEN0);

  //Liczba bitów danych w ramce
  UCSR0C |= (1<<UCSZ00);
  UCSR0C |= (1<<UCSZ01);
}


void USART_Transmit( unsigned char data )
 {
 /* Wait for empty transmit buffer */
 while ( !( UCSR0A & (1<<UDRE0)) )
 ;
 /* Put data into buffer, sends the data */
 UDR0 = data;
 }

unsigned char USART_Receive()
 {
 /* Wait for data to be received */
 while ( !(UCSR0A & (1<<RXC0)) )
 ;
 /* Get and return received data from buffer */
 return UDR0;
 }

void USART_String(const char *array)
{
  int i=0;
  while(array[i]!='\0')
  {
    USART_Transmit(array[i]);
    i++;
  }
}


void przesylParametrow(char wilgotnosc_gleby_przed[20], char wilgotnosc_gleby_po[20], char temperatura[20], 
char stan[20], char godzina[20], char data[20])
{
  _delay_ms(1000);
  
  USART_String("start\n");
  
  USART_String(wilgotnosc_gleby_przed);
  USART_Transmit('\n'); 
  _delay_ms(100);

  
  USART_String(wilgotnosc_gleby_po);
  USART_Transmit('\n'); 
  _delay_ms(100);

    
  USART_String(temperatura);
  USART_Transmit('\n'); 
  _delay_ms(100);

    
  USART_String(stan);
  USART_Transmit('\n'); 
  _delay_ms(100);

   
  USART_String(godzina);
  USART_Transmit('\n'); 
  _delay_ms(100);

    
  USART_String(data);
  USART_Transmit('\n');
  
  USART_String("koniec\n");
  _delay_ms(100);
}


//.......................................................... ADC ..................................................................
void ADC_init()
{
  //zasilanie
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);

  //division factor
  ADCSRA |= (1<<ADPS0);
  ADCSRA |= (1<<ADPS1);
  ADCSRA |= (1<<ADPS2);
  
  //włączenie ADC
  ADCSRA |= (1<<ADEN);
}

int channelA0()
{
  //kanał A0
  ADMUX &= ~(1<<MUX0);
  ADMUX &= ~(1<<MUX1);
  ADMUX &= ~(1<<MUX2);
  ADMUX &= ~(1<<MUX3);
  
  ADCSRA |= (1<<ADSC);

  while(ADCSRA & (1<<ADSC))
  {}

  //zwracanie zmierzonego napięcia
  return ADC;
}

float checkMoisture()
{
  int resultA0 = 0;
  float moisture_percent = 0.0;

  resultA0 = channelA0();
  moisture_percent = (1023.0 - resultA0)/1023.0*100.0;

  return moisture_percent;
}



//......................................................... PWM .................................................................
void PWM_init()
{
  // DIODA RGB -> TIMER 0
  //Konfiguracja Timer0 w trybie Fast PWM, prescaler 8
  //TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); 
  //TCCR0B = (1 << CS01); 
  
  //wypełnienie dla R i G 
  //OCR0B = 255;
  //OCR0A = 255;

  //.....................................................................

  // POMPA -> TIMER 1
  //Konfiguracja Timer1 w trybie Phase Correct PWM, prescaler 8
  TCCR1A = (1 << COM1A1) | (1 << WGM11); 
  TCCR1B = (1 << WGM13) | (1 << CS11);  
  
  //TOP = 20000 -> okres 20 ms (50 Hz)
  ICR1 = F_CLK/(F_POMPA*2*N_POMPA); 
  
}

void setDutyPomp(uint16_t us, uint8_t time_) 
{
  if (us < 500) us = 500;    // Minimalny czas impulsu
  if (us > 2400) us = 2400;  // Maksymalny czas impulsu

  //wypełnienie (prz prescalerze 8)
  OCR1A = (uint16_t)((uint32_t)F_CLK / (N_POMPA * 1000000UL) * us);   
  _delay_ms(time_); 
  OCR1A = (uint16_t)((uint32_t)F_CLK / (N_POMPA * 1000000UL) * STOP_US);
  //_delay_ms(2000);
}


void setColor(int r, int g)
{
  r = 255-r;
  g = 255-g;
  OCR0B = r;
  OCR0A = g;
}


void RGB(uint8_t soil_moisture)
{
   if(soil_moisture <= 30)
    {
      //odcienie czerwieni
      //int g = soil_moisture/2;
      //int r = 250-soil_moisture/2;
      //setColor(r,g);

      //podlanie wymagane
      PORTB |= (1<<PB5);
      setDutyPomp(1300,3000);
      podlanie = 1;
    }
    else if((soil_moisture > 30)&&(soil_moisture <= 40))
    {
      //czerwony->żółty
      //int g = soil_moisture;
      //int r = 235;
      //setColor(r,g);

      //podlanie wymagane
      setDutyPomp(1250,2000);
      PORTB &= ~(1<<PB5);
      podlanie = 1;
    }
    else if((soil_moisture > 50)&&(soil_moisture <= 60))
    {
       //żółty->zielony
       //int g = soil_moisture*1.2;
       //int r = 235-soil_moisture;
       //setColor(r,g);

       //podlanie nie wymagane
       PORTB &= ~(1<<PB5);
       podlanie = 0;
     }
     else if((soil_moisture > 60))
     {
        //odcienie zieleni
        //int g = soil_moisture*1.2;
        //int r = 174-soil_moisture;
        //setColor(r,g);

        //podlanie nie wymagane
        PORTB &= ~(1<<PB5);
        podlanie = 0;
     }
}



//.............................................................................................................................
uint8_t getDaysInMonth(uint8_t month, uint8_t year) {
    // Miesiące z 31 dniami
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    }
    // Miesiące z 30 dniami
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    // Luty
    if (month == 2) {
        // Rok przestępny
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        }
        return 28;
    }
    return 0; // Bezpieczny fallback (nie powinno się zdarzyć)
} 
