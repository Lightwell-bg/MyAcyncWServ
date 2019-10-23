#ifndef GLOBAL_H
#define GLOBAL_H
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include "SPIFFS.h"
  #include <Update.h>//for update firmware
  #include <ESPmDNS.h>//for Name of device ESPXX.local
  //#include <ESP32SSDP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include "FS.h"
  #include <Updater.h>//for update firmware
  #include <ESP8266mDNS.h>//for Name of device ESPXX.local
  #include <ESP8266SSDP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <Wire.h> // must be included here so that Arduino library object file references work

AsyncWebServer HTTP(80);

const String nVersion = "v3.9";
#define USE_RTC true //USE OR NO VERSION
#define AKA_CLOCK true //USE OR NO
#define USE_DHT false //USE OR NO
#define USE_BME280 true //USE OR NO

#if USE_RTC == true
  #include "RTClib.h" //https://github.com/adafruit/RTClib
  RTC_DS3231 rtc;
#endif

#if USE_RTC == true
  const String urts = "+RTC ";
  bool useRTC = true;
#else  
  const String urts = "noRTC ";
  bool useRTC = false;
#endif
#if AKA_CLOCK == true
  #if USE_DHT == true
    String cVersion = "iClock DHT22 " + urts + nVersion;
  #endif //DHT
  #if USE_BME280 == true // I2C D1, D2
    String cVersion = "iClock BME280 " + urts + nVersion;
  #endif //BME280  
#else
  String cVersion = "iScreen " + urts + nVersion;
#endif

String logo = "LIGHTWELL";
const char* day_ru[] PROGMEM = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
const char* day_bg[] PROGMEM = {"Неделя", "Понеделник", "Вторник", "Сряда", "Четвертък", "Петък", "Събота"};
const char* day_en[] PROGMEM = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char** day_table[] PROGMEM = {day_ru, day_bg, day_en};
const char* month_ru[] PROGMEM = {"Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентября", "Октября", "Ноября", "Декабря"};
const char* month_bg[] PROGMEM = {"Януари", "Февруари", "Март", "Април", "Май", "Юни", "Юли", "Август", "Септември", "Октомври", "Ноември", "Декември"};
const char* month_en[] PROGMEM = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const char** month_table[] PROGMEM = {month_ru, month_bg, month_en};

uint32_t timeCount = 0; //Time counter for All

// Определяем переменные wifi
String ssid = "hlanbg2.4";
String password = "19740623";
String ssidAP = "WiFi-LED";   // SSID AP точки доступа
String passwordAP = ""; // пароль точки доступа
String SSDP_Name = "LEDLightwell"; // Имя SSDP
IPAddress apIP(192, 168, 4, 1);

uint8_t lang = 2; //0-RU, 1-BG, 2 -EN, 3-UA
uint8_t modeShow = 1; //Mode of display 1 - clock, 2 - date, 3 - run text
//Time
int8_t timezone = 3;               // часовой пояс GTM
String sNtpServerName = "us.pool.ntp.org";
bool isDayLightSaving = true; //Summer time use
bool statusUpdateNtpTime = 1; //
const unsigned long TIME_UPDATE = 1000*60*10; //Интервал обновления времени
const unsigned long NTP_UPDATE = 1000*30; //Интервал обновления с NTP при отсутствии ответа сервера
unsigned long lastNtpTime = 0;

//Display TEXT
uint32_t  displayClockCount = 0; //отсчет для времени отображения часов
bool displayClockFirst = true; //Заход в процедуру отображения часов первый раз. Чтобы отображать нужный интервавл displayClockCount
char  szTime[9];    // hh:mm\0
String strText0="", strText1="LIGHTWELL", strText2="", strText3="";
bool isTxtOn0 = false, isTxtOn1 = true, isTxtOn2 = false, isTxtOn3 = false;
bool isCrLine0 = false, isCrLine1 = true, isCrLine2 = false, isCrLine3 = false;
float txtFrom0=0, txtFrom1=0, txtFrom2=0, txtFrom3=0; 
float txtTo0=24, txtTo1=24, txtTo2=24, txtTo3=24;
float weathFrom=0, fcastFrom=0, clockFrom=0, dateFrom=0, seaFrom=0;
float weathTo=24, fcastTo=24, clockTo=24, dateTo=24, seaTo=24; 

//Setup for LED
uint8_t fontUsed = 0; //fonts
uint8_t dmodefrom = 8, dmodeto = 20; //DAY MODE
uint8_t brightd = 3, brightn = 0; //brightness day and night
uint16_t speedTicker = 5; // БЕГУЩАЯ СТРОКА speed 
bool isLedClock = true, isLedDate = true, isLedWeather = false, isLedForecast = false, isLedSea = false;
float global_start = 0, global_stop = 24;

// Параметры погодного сервера
String  W_URL  = "api.openweathermap.org";
String  W_API    = "3527b31fcfc28604386f2f2079e67ac5"; //2d552ad9b7028c8eb1be5945af0f1ee1
String  CITY_ID     = "732770"; // Москва = 524901 Остальные города можно посмотреть http://bulk.openweathermap.org/sample/city.list.json.gz
String strWeather, strWeatherFcast, strSea;
const unsigned long PER_GET_WEATHER = 1000*60*6;
const unsigned long PER_GET_WEATHER_FCAST = 1000*60*11;
const unsigned long PER_GET_SEA = 1000*60*15;
unsigned long lastTimeWeather = 0; unsigned long lastTimeWeatherFcast = 0, lastTimeSea=0;
const char* overboard[] PROGMEM = {"За бортом ", "Извън борда ", "Overboard "};
const char* overboardfcast[] PROGMEM = {"Завтра за бортом ", "Утре извън борда ", "Tomorrow overboard "};
const char* temper[] PROGMEM = {". Темп ", ". Темп ", ". Temp "};
const char* hum[] PROGMEM = {"\xC2С. Влажн ", "\xC2С. Влажн ", "\xC2С. Humidity "};
const char* pres[] PROGMEM = {"% Давл ", "% Налягане ", "% Pressure "};
const char* wind[] PROGMEM = {"мм. Ветер ", "мм. Вятър ", "mm. Wind "};
const char* windsp[] PROGMEM = {" м/с.", " м/с.", " m/s."};
const char* windir_ru[] PROGMEM = {"север-вост ", "вост ", "юго-вост ", "южный ", "юго-запад ", "запад ", "север.-запад ", "север "};
const char* windir_bg[] PROGMEM = {"север-изт ", "източ ", "юго-източ ", "южен ", "южен-запад ", "запад ", "север.-запад ", "север "};
const char* windir_en[] PROGMEM = {"North-East ", "East ", "South-East ", "South ", "South-West ", "West ", "North-West ", "North "};
const char** windir_table[] PROGMEM = {windir_ru, windir_bg, windir_en};
const char* cloudstxt[] PROGMEM = {" Облачность ", " Облачност ", " Clouds "};
const char* forecast[] PROGMEM = {"Завтра  ", "Утре ", "Tomorrow "};
const char* tempermin[] PROGMEM = {". Темп.мин ", ". Темп.мин ", ". Temp.min "};
const char* tempermax[] PROGMEM = {"\xC2С макс ", "\xC2С макс ", "\xC2С max "};
const char* tempersea[] PROGMEM = {"Темп.моря ", "Морската вода ", "Sea temp "};

bool mqttOn = false;
char mqttData[80]; //Данные для передачи на MQTT
String mqtt_server = "m24.cloudmqtt.com"; // Имя сервера MQTT
int mqtt_port = 16728; // Порт для подключения к серверу MQTT
String mqtt_user = "fnncrtrr"; // Логи от сервер
String mqtt_pass = ""; // Пароль от сервера QvKr_jbEsHYb
String mqtt_name = "iClockLW";
String mqtt_sub_crline = "iClockLW/crLine"; //Топик для подписки на бег.строку
String crLine = "";
unsigned long ReconnectTime = 0;  const unsigned long MQTT_CONNECT = 1000*60*3;
#if AKA_CLOCK == true
//alarm
  #define ALARM_PIN 12  // D6 Define DST adjust button pin
  #define BUZ_PIN 15  // D8 Define DST adjust button pin
  typedef struct {
    uint8_t alarm_h;   
    uint8_t alarm_m;     
    uint8_t  alarm_stat;     
  } sAlarmSet;
  sAlarmSet myAlarm[] = {{6, 30, 0}, {7 ,30, 0}};
  //byte alarme[5][3]{{12, 30, 11},{7, 15, 9},{22, 55, 12},{0, 30, 0},{0, 0, 0}}; //1-часы, 2-минуты, 3-откл(0)/1раз(11)/пон-пят(8)/пон-сб(9)/сб-вс(10)/вс(1)/пон(2)/вто(3)/сре(4)/чет(5)/пят(6)/сб(7)/всегда(12)
  //const uint16_t PERIOD_ALARM = 60000; //period of ALARM
  bool stopAlarm = false; //Флаг кнопки выкл. ALARM
  unsigned long timeStopAlarm = 0; //Отсчет времени активности кнопки (1 мин)  
//mqtt
  float thpFrom=0, thpTo=24; 
  bool isLedTHP = true;
  String strTHP; //Строка темп.влажности давления внутри
  String mqtt_pub_temp = "iClockLW/temp"; //Топики для передачи значений датчиков
  String mqtt_pub_hum = "iClockLW/hum";
  String mqtt_pub_press = "iClockLW/press";
  unsigned long mqttDhtTime = 0;  const unsigned long MQTT_SEND_INT = 1000*60*7; //Интервал отправки на MQTT
  unsigned long lastTimePHT = 0; const unsigned long PER_GET_THP = 1000*60*3; //Интервал для вывода THP на часы
  const char* onboard[] PROGMEM = {"На борту темп ", "На борда темп ", "Onboard air "};
  //thingspeak.com
  unsigned long tspeakDhtTime = 0;  const unsigned long TSPEAK_SEND_INT = 1000*60*10; //Интервал отправки на TSPEAK
  bool tspeakOn = false;
  String tspeak_server = "api.thingspeak.com";
  unsigned long tspeak_channal = 111111;
  String tspeak_wapi = "HMW4HF3BRC7OIGSO";  
  const char* temperIn[] PROGMEM = {"Темп", "Темп ", "Temp"};
  const char* humIn[] PROGMEM = {"Влаж", "Влаж", "Hum"};
  const char* presIn[] PROGMEM = {"Давл", "Нал", "Pres"};  
  const uint8_t maxModeShow = 11; //ПереОпределяем число программ, добавляем темп внутри и строку из MQTT
#else
  const uint8_t maxModeShow = 10; //ПереОпределяем число программ, добавляем темп внутри и строку из MQTT
#endif
#endif