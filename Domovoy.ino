char versia[] = "202000511"; //Домовой-2020 .251

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
WiFiClientSecure clientT;
WiFiClient client;


int debug_to_serial = 0;
String debug_to_serial_mask = "";
uint32_t Ishod_nomer_msg = 0;

String m_prefix = ""; //		m_prefix = "/m_"+ip4; 








void loop1( void *pvParameters );
void loop2( void *pvParameters );












//********************************************************************

struct Config{
	
	String BOTtoken;  	String BOTtoken_ALARM;  
	String legal_chat_id;	String admin_chat_id;	String alarm_chat_id;
	String botname;	String botinfo;
	String ip;	String ip123_;	String subnet;	String gateway;
	char ssid[20];	char pass[20];
	int Clear_log_interval;
	int noDisplay;
	int log; int log_to_SDcard;
	int OTA;
	int getTLG;	int sendTLG;
	int send_svyaznoy;	String ip_svyaznoy;

	String key01;	String cmd01;	String key02;	String cmd02;	String key03;	String cmd03;	String key04;	String cmd04;
	String key05;	String cmd05;	String key06;	String cmd06;	String key07;	String cmd07;	String key08;	String cmd08;
	String key09;	String cmd09;
	
	
	String line01; 	String line_cmd01;	String line02; 	String line_cmd02;	String line03; 	String line_cmd03;
	String line04; 	String line_cmd04;	String line05; 	String line_cmd05;	String line06; 	String line_cmd06;
	String line07; 	String line_cmd07;	String line08; 	String line_cmd08;	String line09; 	String line_cmd09;
	
	int use_RF_PULT; 	int GPIO_RF_RECIVER; int GPIO_RF_TRANSMITER; 

	int F_Ohrana = 0; 	int F_Ohrana_Sirena_GPIO;	int F_Ohrana_Trevoga_GPIO;
	
	int F_UltraSonic = 0; 	int F_UltraSonic_trig_GPIO;	int F_UltraSonic_echo_GPIO;	int hcsr04_interval;	int hcsr04_delta;

	int F_DHT = 0;
	
	int F_DS18B20 = 0;
	
	int DS18B20_1_Alarm = 0;	String DS18B20_1_name = "";	int DS18B20_1_min = 0;	int DS18B20_1_max = 0;	String DS18B20_1_msg = "";	String DS18B20_1_msg_ok = "";
	int DS18B20_2_Alarm = 0;	String DS18B20_2_name = "";	int DS18B20_2_min = 0;	int DS18B20_2_max = 0;	String DS18B20_2_msg = "";	String DS18B20_2_msg_ok = "";

	String in00cmd0;	String in00cmd1;	String in00name;	int in00i;	String in00i0;	String in00i1;	int in00v;	String in00mode;	int in00save;	int in00load;
	String in02cmd0;	String in02cmd1;	String in02name;	int in02i;	String in02i0;	String in02i1;	int in02v;	String in02mode;	int in02save;	int in02load;
	String in04cmd0;	String in04cmd1;	String in04name;	int in04i;	String in04i0;	String in04i1;	int in04v;	String in04mode;	int in04save;	int in04load;
	String in05cmd0;	String in05cmd1;	String in05name;	int in05i;	String in05i0;	String in05i1;	int in05v;	String in05mode;	int in05save;	int in05load;
	String in12cmd0;	String in12cmd1;	String in12name;	int in12i;	String in12i0;	String in12i1;	int in12v;	String in12mode;	int in12save;	int in12load;
	String in13cmd0;	String in13cmd1;	String in13name;	int in13i;	String in13i0;	String in13i1;	int in13v;	String in13mode;	int in13save;	int in13load;
	String in14cmd0;	String in14cmd1;	String in14name;	int in14i;	String in14i0;	String in14i1;	int in14v;	String in14mode;	int in14save;	int in14load;
	String in15cmd0;	String in15cmd1;	String in15name;	int in15i;	String in15i0;	String in15i1;	int in15v;	String in15mode;	int in15save;	int in15load;

	

	String RF_keys_1;	String RF_keys_2;	String RF_keys_3;	String RF_keys_4;	String RF_keys_5;	String RF_keys_6;
	String RF_keys_TREVOGA;	String Pins_TREVOGA;	
	
	String RF_array;
};


Config config;



// автор Загайнов Вячеслав +79165793105 не претендует на титул гения 
// пишу как могу
// помогите оптимизировать код

//мои заметки
//debug("started (%s)\n", WiFi.softAPIP().toString().c_str());
//https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
//https://github.com/Toshik/TickerScheduler
//https://github.com/beegee-tokyo/DHTesp


//#include "BluetoothSerial.h" 
//BluetoothSerial SerialBT;

/* You only need to format SPIFFS the first time you run a
test or else use the SPIFFS plugin to create a partition
https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED true

const char* serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update'><input type='submit' value='Update'>"
"</form><div id='prg'>progress: 0%</div>"
"<script>"
"$('form').submit(function(e){e.preventDefault();"
"var form = $('#upload_form')[0];var data = new FormData(form);"
" $.ajax({url: '/update',type: 'POST',data: data,contentType: false,processData:false,xhr: function(){"
"var xhr = new window.XMLHttpRequest();xhr.upload.addEventListener('progress', function(evt){"
"if (evt.lengthComputable){var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');}"
"}, false);return xhr;},success:function(d, s){console.log('success!')},error: function (a, b, c){}});});"
"</script>";


//String _chat_id;

String uptime;
String filecfg = "/svyaznoy.cfg";
String file_a_status = "/a_status.cfg";

int file_a_status_loaded = 0;
String appname = "ДОМОВОЙ";
String namelogfile;

int AP = 0;


int Alarm;
uint32_t Relay1_lasttime = 0;
uint32_t Relay2_lasttime = 0;
uint32_t SendErrorSVZ_lasttime = 0;



char in_user_array[10][20] 			={"", "", "", "", "", "", "", "", "", ""};
char in_msg_array[10][200] 			={"", "", "", "", "", "", "", "", "", ""};
char in_iniciator_array[10][200] 	={"", "", "", "", "", "", "", "", "", ""};

char out_user_array[10][60] 		={"", "", "", "", "", "", "", "", "", ""};
char out_msg_array[10][2000] 		={"", "", "", "", "", "", "", "", "", ""};
char out_sek_array[10][10] 			={"", "", "", "", "", "", "", "", "", ""};

char minion_user_array[10][20] 		={"", "", "", "", "", "", "", "", "", ""};
char minion_msg_array[10][20] 		={"", "", "", "", "", "", "", "", "", ""};


char m_ip_array[9][20] 				={"", "", "", "", "", "", "", "", ""};
char m_name_array[9][40] 			={"", "", "", "", "", "", "", "", ""};
char m_sek_array[9][20] 			={"", "", "", "", "", "", "", "", ""};

uint32_t counter_rw = 0;
char timer_date_array[10][9] 		={"", "", "", "", "", "", "", "", "", ""};
char timer_time_array[10][5] 		={"", "", "", "", "", "", "", "", "", ""};
char timer_repeet_array[10][1] 		={"", "", "", "", "", "", "", "", "", ""};
char timer_command_array[10][100] 	={"", "", "", "", "", "", "", "", "", ""};
char timer_exdate_array[10][9] 		={"", "", "", "", "", "", "", "", "", ""};
char timer_extime_array[10][5] 		={"", "", "", "", "", "", "", "", "", ""};






//----------------------------------------
//I2C WIRE OLED 
//----------------------------------------
//#include <Wire.h>//5 4 / 22 21
#include <OLED.h>
int i2c_pin_1 = 22;
int i2c_pin_2 = 21;
OLED display(i2c_pin_1, i2c_pin_2, 0x3c);
//OLED display(5, 4, 0x3c);		//wemos / ttgo
//OLED display(22, 21, 0x3c); // m5stack
//




#include <UniversalTelegramBot_modSZ.h>
UniversalTelegramBot bot(config.BOTtoken, clientT);


//#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <WebServer.h>
WebServer server(80);

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer aserver(82);


/* #include <HTTPClient.h>
HTTPClient http; */

#include <Update.h>



struct tcp_pcb;
extern struct tcp_pcb* tcp_tw_pcbs;
extern "C" void tcp_abort (struct tcp_pcb* pcb);



//----------------------------------------
#include "FS.h"
#include "SPIFFS.h"
#include <SD.h>
//#include <SPI.h>
//

#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#define TFT_GREY 0x5AEB // New colour
TFT_eSPI tft = TFT_eSPI();  // Invoke library



//----------------------------------------
//433 мгц
//----------------------------------------
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int OHRANA;
int TREVOGA = 0;
String RFS_cods = "";
uint32_t RFS_cods_lasttime = 0;
uint32_t RFKEY1_lasttime = 0;
uint32_t RFKEY2_lasttime = 0;
uint32_t RFKEY3_lasttime = 0;
uint32_t RFKEY4_lasttime = 0;
uint32_t RFKEY5_lasttime = 0;
uint32_t RFKEY6_lasttime = 0;
uint32_t RFKEYTREVOGA_lasttime = 0;



//----------------------------------------
// термометры ds18b20
//----------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
//float tempC1;
//float tempC2;
//float tempC3;
int tempC1;
int tempC2;
int tempC3;
#define TEMPERATURE_PRECISION 9
DeviceAddress Thermometer1, Thermometer2, Thermometer3;
uint32_t DS18B20_1_Alarm_lasttime = 0;
uint32_t DS18B20_2_Alarm_lasttime = 0;
uint32_t DS18B20_3_Alarm_lasttime = 0;
uint32_t Temp_lasttime 	= 0;
uint32_t Temp_interval 	= 1 * 60 * 1000;
//

//----------------------------------------
// время и таймеры
//----------------------------------------
#include <TimeLib.h>
#include <DS1307RTC.h>
String YYYYMMDD_HHMMSS = "00000000-000000";
int YYYYMMDD = 0;
int HHMMSS = 0;
int HHMM = 0;
int HH = 0;
int MM = 0;
int rtc_YYYY = 0;
int rtc_MM = 0;
int rtc_DD = 0;
int rtc_hh = 0;
int rtc_mm = 0;
int rtc_ss = 0;
uint32_t Timers_lasttime = 0;
uint32_t Timers_interval = 15000;
//





uint32_t Bot_lasttime = 0;
uint32_t Bot_interval = 1000;

int Uskoritel = 0;


uint32_t Clear_log_lasttime = 0;
//uint32_t Clear_log_interval = 0;

uint32_t TXERD_lasttime = 0;

String mac;
String IP="";
String ip4="";
String txtlog;
String msg = "";

int in00GPIO_lastState = 2;
int in02GPIO_lastState = 2;
int in04GPIO_lastState = 2;
int in05GPIO_lastState = 2;
int in12GPIO_lastState = 2;
int in13GPIO_lastState = 2;
int in14GPIO_lastState = 2;
int in15GPIO_lastState = 2;
int in16GPIO_lastState = 2;
int in17GPIO_lastState = 2;
int in18GPIO_lastState = 2;
int in19GPIO_lastState = 2;
int in20GPIO_lastState = 2;
int in21GPIO_lastState = 2;
int in22GPIO_lastState = 2;
int in23GPIO_lastState = 2;


//----------------------------------------
#include "SHCSR04.h"
SHCSR04 hcsr04;
uint32_t hcsr04_lasttime = 0;
//uint32_t hcsr04_interval = 15000;
int hcsr04_lastvalue = 0;
//


/*  #include "DHTesp.h"
DHTesp dht;
int humidity = 0;
int temperature = 0;  */







//---------------------------------------------------------
void Msg_for_Minion_R(String chat_id, String msg){
	
	print_lcd(6, 0, "Msg_for_Minion");

	String msg_cmd = "";
	String ipm = "";

	if (msg.indexOf("/m0") == 0){
		if (msg.indexOf("/m01") == 0){ipm = m_ip_array[0];}
		if (msg.indexOf("/m02") == 0){ipm = m_ip_array[1];}
		if (msg.indexOf("/m03") == 0){ipm = m_ip_array[2];}
		if (msg.indexOf("/m04") == 0){ipm = m_ip_array[3];}
		if (msg.indexOf("/m05") == 0){ipm = m_ip_array[4];}
		if (msg.indexOf("/m06") == 0){ipm = m_ip_array[5];}
		if (msg.indexOf("/m07") == 0){ipm = m_ip_array[6];}
		if (msg.indexOf("/m08") == 0){ipm = m_ip_array[7];}
		if (msg.indexOf("/m09") == 0){ipm = m_ip_array[8];}
		msg_cmd = "status";
		if (msg.indexOf("raport") >= 0){msg_cmd = "raport";}
	}
	//Serialprint("ipm="+ipm);
		
	if (msg.indexOf("/m_") == 0){
		msg.replace("/m_","");
		if (msg.indexOf("_") > 0){
			// /tasker__s__m_242_status
			int pd = msg.indexOf("_");
			ipm = msg.substring(0, pd);
			ipm = config.ip123_ + ipm;
			ipm.replace("_", "");
			//ipm.replace("m", "");
			msg_cmd = msg.substring(pd + 1);
		}else{
			// /tasker__s__m_242
			ipm = config.ip123_ + msg;
			msg_cmd = "status";
		}
	}

	//WiFiClient client;
	if (!client.connect(ipm.c_str(), 80, 1500)){
		Serialprint("ERR: connection to minion failed " + ipm);
		add_out_array(chat_id, "миньон " + ipm + " не доступен, возможно села батарейка");
 		client.flush();
		client.stop();		//client.flush();		kill_tcp(); 
		return;
	}
	
	Serialprint("-->min ["+ipm+"]["+chat_id+"]["+msg+"]["+msg_cmd+"]");
	print_lcd(6, 0, ">m:" + msg);

	String url = "/input_svz?msg=" + msg_cmd + "&chat_id=" + chat_id;
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
"Host: " + ipm + "\r\n" +
"Connection: close\r\n\r\n");
			   
	uint32_t timeout = millis();
	while (client.available() == 0){
		if (millis() - timeout > 2000){
			Serialprint("ERR: Msg_for_Minion Timeout !" + ipm);
			add_out_array(chat_id, "миньон " + ipm + " долго не отвечает, возможно сдох");
			client.flush();
			client.stop();		//client.flush();			//kill_tcp();
			return;
		}
	}

	String line = ""; while (client.available()){line += String(char(client.read()));}
	Serialprint("<--min: " + line); 

    client.flush();client.stop();//client.flush();	kill_tcp(); */
	return;
}



//---------------------------------------------------------
int Msg_for_Minion(String chat_id, String msg){
	
	Serialprint("Msg_for_Minion "+chat_id+" "+msg);
	print_lcd(6, 0, "Msg_for_Minion");
	String msg_cmd = "";
	String ipm = "";

	if (msg.indexOf("/raport") == 0){
		ipm = m_ip_array[0];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m01_raport");delay(100);}
		ipm = m_ip_array[1];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m02_raport");delay(100);}
		ipm = m_ip_array[2];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m03_raport");delay(100);}
		ipm = m_ip_array[3];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m04_raport");delay(100);}
		ipm = m_ip_array[4];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m05_raport");delay(100);}
		ipm = m_ip_array[5];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m06_raport");delay(100);}
		ipm = m_ip_array[6];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m07_raport");delay(100);}
		ipm = m_ip_array[7];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m08_raport");delay(100);}
		ipm = m_ip_array[8];if (ipm != ""){Msg_for_Minion_R(chat_id,"/m09_raport");delay(100);}
		
		return 1;
	}


	if (msg.indexOf("/m0") == 0){
		if (msg.indexOf("/m01") == 0){ipm = m_ip_array[0];}
		if (msg.indexOf("/m02") == 0){ipm = m_ip_array[1];}
		if (msg.indexOf("/m03") == 0){ipm = m_ip_array[2];}
		if (msg.indexOf("/m04") == 0){ipm = m_ip_array[3];}
		if (msg.indexOf("/m05") == 0){ipm = m_ip_array[4];}
		if (msg.indexOf("/m06") == 0){ipm = m_ip_array[5];}
		if (msg.indexOf("/m07") == 0){ipm = m_ip_array[6];}
		if (msg.indexOf("/m08") == 0){ipm = m_ip_array[7];}
		if (msg.indexOf("/m09") == 0){ipm = m_ip_array[8];}
		msg_cmd = "status";
		if (msg.indexOf("raport") >= 0){msg_cmd = "raport";}
	}
	//Serialprint("ipm="+ipm);
		
	if (msg.indexOf("/m_") == 0){
		msg.replace("/m_","");
		if (msg.indexOf("_") > 0){
			// /tasker__s__m_242_status
			int pd = msg.indexOf("_");
			ipm = msg.substring(0, pd);
			ipm = config.ip123_ + ipm;
			ipm.replace("_", "");
			//ipm.replace("m", "");
			msg_cmd = msg.substring(pd + 1);
		}else{
			// /tasker__s__m_242
			ipm = config.ip123_ + msg;
			msg_cmd = "status";
		}
	}

	if (!client.connect(ipm.c_str(), 80, 1000)){
		Serialprint("ERR: connection to minion failed " + ipm);
		add_out_array(chat_id, "миньон " + ipm + " не доступен, возможно села батарейка");
		client.flush();
		client.stop(); 
		return 1;
	}
	
	Serialprint("-->min ["+ipm+"]["+chat_id+"]["+msg+"]["+msg_cmd+"]");
	print_lcd(6, 0, ">m:" + msg);

	String url = "/input_svz?msg=" + msg_cmd + "&chat_id=" + chat_id;
	client.print("GET " + url + " HTTP/1.1\r\n" +
"Host: " + ipm + "\r\n" +
"\r\n");
//"Connection: close\r\n			   
	uint32_t timeout = millis();
	while (!client.available()){
		if (millis() - timeout > 3000){
			Serialprint("ERR: Msg_for_Minion Timeout !" + ipm);
			add_out_array(chat_id, "миньон " + ipm + " долго не отвечает, возможно сдох");
			client.flush();
			client.stop();
			return 0;
		}
	} 

	String line = ""; while (client.available()){line += String(char(client.read()));}
	Serialprint("<--min: " + line);

	client.flush();client.stop();//client.flush();kill_tcp();
	return 1;
}


//---------------------------------------------------------
int Obrabotka_vhodyashih(){

	int data = 0;for (byte j = 0; j < 10; j++){if (String(in_msg_array[j]) != ""){data = 1; break;}}if (data == 0){return 0;}
	
	for (byte j = 0; j < 10; j++){

		int com_ok = 0;

		
		String chat_id = String(in_user_array[j]);
		String komanda = String(in_msg_array[j]);
		if (komanda == ""){continue;}
		
		String komanda_0 = String(in_msg_array[j]);
		String iniciator = String(in_iniciator_array[j]);
		


		if ( (komanda.indexOf("Рапорт") == 0 )|| (komanda.indexOf("/raport_all")) == 0 ){
			add_out_array(String(in_user_array[j]), config.botinfo+"\nстатус:\n"+status(1)+"\n"+uptime+"\n"+listTimers());com_ok = 1; 	
			Msg_for_Minion(in_user_array[j],"/raport");
			
			memcpy(in_user_array[j], 		"", 20);
			memcpy(in_msg_array[j], 		"", 200);
			memcpy(in_iniciator_array[j], 	"", 200);
			com_ok = 1;
			//break;
			return 1;
		}



/* 		if (komanda.indexOf("/m_/") != 0){
			if(komanda.indexOf(m_prefix) != 0){
				if ((komanda.indexOf("/m_") == 0) || (komanda.indexOf("/m0") == 0) || (komanda.indexOf("/raport") == 0)){
					Msg_for_Minion(chat_id,komanda);
					memcpy(in_user_array[j], 		"", 20);
					memcpy(in_msg_array[j], 		"", 200);
					memcpy(in_iniciator_array[j], 	"", 200);
					
					com_ok = 1;
					//break;
					return 1;
				}
			}
		}	 */






		if (komanda == m_prefix){
			komanda = "/status";
		}
		

/* 		if(komanda.indexOf("/") == 0 ){// отрезаем лишнее "/cmd - бла бла бла"
			if(komanda.indexOf(" ") > 0 ){
				komanda = komanda.substring(0,komanda.indexOf(" "));
			}
		} */
		
		
		
		 if(komanda.indexOf("/") == 0 ){// отрезаем лишнее "/cmd - бла бла бла"
			if(komanda.indexOf("@") > 0 ){
				komanda = komanda.substring(0,komanda.indexOf("@"));
			}
		} 
		
		if(komanda.indexOf("/m_/") == 0 ){// отрезаем лишнее если домовому
				komanda = komanda.substring(3);
		}
		
		if(komanda.indexOf(m_prefix) == 0){
			komanda.replace(m_prefix+"_","/"); 
		}
		
/* 		if(komanda.indexOf(m_prefix) != 0){
			if ( (komanda.indexOf("/m_") == 0) || (komanda.indexOf("/m0") == 0) ){
				Msg_for_Minion(chat_id,komanda);
				memcpy(in_user_array[j], 		"", 20);
				memcpy(in_msg_array[j], 		"", 200);
				memcpy(in_iniciator_array[j], 	"", 200);
				
				com_ok = 1;
				//break;
				return 1;
			}
		} */
		
		
		
		
	
		if ((komanda == "/m") || (komanda == "Миньоны")){

			String msg = "Ⓜ Миньоны:\n";
			msg += "/m01 " + String(m_name_array[0]) + " " + String(m_ip_array[0]) + "\n";
			msg += "/m02 " + String(m_name_array[1]) + " " + String(m_ip_array[1]) + "\n";
			msg += "/m03 " + String(m_name_array[2]) + " " + String(m_ip_array[2]) + "\n";
			msg += "/m04 " + String(m_name_array[3]) + " " + String(m_ip_array[3]) + "\n";
			msg += "/m05 " + String(m_name_array[4]) + " " + String(m_ip_array[4]) + "\n";
			msg += "/m06 " + String(m_name_array[5]) + " " + String(m_ip_array[5]) + "\n";
			msg += "/m07 " + String(m_name_array[6]) + " " + String(m_ip_array[6]) + "\n";
			msg += "/m08 " + String(m_name_array[7]) + " " + String(m_ip_array[7]) + "\n";
			msg += "/m09 " + String(m_name_array[8]) + " " + String(m_ip_array[8]) + "\n";
			msg += "/raport_all - рапорт от всех\n";

			add_out_array(chat_id, msg);
			memcpy(in_msg_array[j], "", 200);
			com_ok = 1;

			//break;
		}
		

		if (komanda.indexOf("/t+") == 0){

			//String msg = "Таймер добавлен:\n";
			String tdate = komanda.substring(3,komanda.indexOf("-"));
			String ttime = komanda.substring(komanda.indexOf("-")+1,komanda.indexOf(" "));
			String tcommand = komanda.substring(komanda.indexOf(" "));
			
			for (byte j = 0; j < 10; j++){
				if (String(timer_date_array[j]) == ""){
					//Serialprint("add_out->["+chat_id+"]["+msg+"]");
					//strlcpy(out_user_array[j], chat_id.c_str(), chat_id.length()+1);
					strlcpy(timer_date_array[j], tdate.c_str(), tdate.length()+1);
					strlcpy(timer_time_array[j], ttime.c_str(), ttime.length()+1);
					strlcpy(timer_command_array[j], tcommand.c_str(), tcommand.length()+1);
					break;
				}
			}
			komanda = "/t";
		}
		


		//Serialprint("Obrabotka_vhodyashih komanda:["+komanda+"]");
		String usercmd = "";

		if (komanda != ""){
			
			if(komanda.indexOf("/") < 0){komanda = "/"+komanda;}

			
			if (komanda == "/01"){usercmd = config.cmd01;}
			if (komanda == "/02"){usercmd = config.cmd02;}
			if (komanda == "/03"){usercmd = config.cmd03;}
			if (komanda == "/04"){usercmd = config.cmd04;}
			if (komanda == "/05"){usercmd = config.cmd05;}
			if (komanda == "/06"){usercmd = config.cmd06;}
			if (komanda == "/07"){usercmd = config.cmd07;}
			if (komanda == "/08"){usercmd = config.cmd08;}
			if (komanda == "/09"){usercmd = config.cmd09;}

			if (komanda == "/"+config.key01){usercmd = config.cmd01;}
			if (komanda == "/"+config.key02){usercmd = config.cmd02;}
			if (komanda == "/"+config.key03){usercmd = config.cmd03;}
			if (komanda == "/"+config.key04){usercmd = config.cmd04;}
			if (komanda == "/"+config.key05){usercmd = config.cmd05;}
			if (komanda == "/"+config.key06){usercmd = config.cmd06;}
			if (komanda == "/"+config.key07){usercmd = config.cmd07;}
			if (komanda == "/"+config.key08){usercmd = config.cmd08;}
			if (komanda == "/"+config.key09){usercmd = config.cmd09;}
	
			if (config.line01.indexOf(komanda) == 0){usercmd = config.line_cmd01;}
			if (config.line02.indexOf(komanda) == 0){usercmd = config.line_cmd02;}
			if (config.line03.indexOf(komanda) == 0){usercmd = config.line_cmd03;}
			if (config.line04.indexOf(komanda) == 0){usercmd = config.line_cmd04;}
			if (config.line05.indexOf(komanda) == 0){usercmd = config.line_cmd05;}
			if (config.line06.indexOf(komanda) == 0){usercmd = config.line_cmd06;}
			if (config.line07.indexOf(komanda) == 0){usercmd = config.line_cmd07;}
			if (config.line08.indexOf(komanda) == 0){usercmd = config.line_cmd08;}
			if (config.line09.indexOf(komanda) == 0){usercmd = config.line_cmd09;}

			if (usercmd != ""){komanda = usercmd;}
			
		}		

			if(komanda.indexOf("/") < 0){komanda = "/"+komanda;}
		
				
		if (komanda.indexOf("/RF433_") == 0){
			komanda.replace("/RF433_", "");
			
			
			
			
			mySwitch.enableTransmit(15); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			
			
			
			

			int ln1 = komanda.length() + 1;
			char ss1[ln1];
			komanda.toCharArray(ss1, ln1);
			//Serialprint(String(ss1));
			//mySwitch.setPulseLength(484);
			//mySwitch.setProtocol(1);
			//mySwitch.setRepeatTransmit(20);
			
			if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
				//------------------
				mySwitch.send(atoi(ss1),24);
				//------------------
			}else{add_out_array(chat_id, config.botname+": тебе не разрешено, команда не будет выполнена");}
	
			String msg = "выполнил команду "+komanda_0+" от "+iniciator ;
			add_out_array(chat_id, msg);
			memcpy(in_msg_array[j], "", 200);
			memcpy(in_iniciator_array[j], "", 200);
			komanda = "";
						com_ok = 1;

			return 1;
		}
				
		if (komanda.indexOf("/tt+") == 0){
		if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
		//------------------

			//RTCread();
			String tt1 = komanda.substring(4,komanda.indexOf(";"));
			String tt2 = komanda.substring(komanda.indexOf(";")+1);
			//Serialprint("tt1:["+tt1+"]");
			//Serialprint("tt2:["+tt2+"]");
			String tdatetime1 = tt1.substring(0,tt1.indexOf(" "));
			String tcommand1 = tt1.substring(tt1.indexOf(" ")+1);
			String tdatetime2 = tt2.substring(0,tt2.indexOf(" "));
			String tcommand2 = tt2.substring(tt2.indexOf(" ")+1);
			Serialprint("1:["+tdatetime1+"]["+tcommand1+"]");
			Serialprint("2:["+tdatetime2+"]["+tcommand2+"]");

			int m_plus1 = 0;
			int h_plus1 = 0;
			int d_plus1 = 0;

			if (tdatetime1.indexOf("m")>=0){tdatetime1.replace("m",""); m_plus1 = tdatetime1.toInt();}
			if (tdatetime1.indexOf("h")>=0){tdatetime1.replace("h",""); h_plus1 = tdatetime1.toInt();}
					
			//int t1_ss1 = rtc_ss;
			int t1_mm1 = rtc_mm + m_plus1;if(t1_mm1 >= 60){h_plus1++;t1_mm1 = t1_mm1-60;}
			int t1_hh1 = rtc_hh + h_plus1; if(t1_hh1 >= 24){d_plus1++;t1_hh1 = t1_hh1-24;}
			int t1_DD1 = rtc_DD + d_plus1;
			int t1_MM1 = rtc_MM;
			int t1_YYYY1 = rtc_YYYY;
			
			String YYYYMMDD1 = String(t1_YYYY1)+""+String(print2digits(t1_MM1))+""+String(print2digits(t1_DD1));
			String HHMM1 = String(print2digits(t1_hh1))+String(print2digits(t1_mm1));
			String YYYYMMDD_HHMM1 = YYYYMMDD1+"-"+HHMM1;
			
			int m_plus2 = 0;
			int h_plus2 = 0;
			int d_plus2 = 0;

			if (tdatetime2.indexOf("m")>=0){tdatetime2.replace("m",""); m_plus2 = tdatetime2.toInt();}
			if (tdatetime2.indexOf("h")>=0){tdatetime2.replace("h",""); h_plus2 = tdatetime2.toInt();}
					
			//int t2_ss2 = rtc_ss;
			int t2_mm2 = rtc_mm + m_plus2;if(t2_mm2 >= 60){h_plus2++;t2_mm2 = t2_mm2-60;}
			int t2_hh2 = rtc_hh + h_plus2; if(t2_hh2 >= 24){d_plus2++;t2_hh2 = t2_hh2-24;}
			int t2_DD2 = rtc_DD + d_plus2;
			int t2_MM2 = rtc_MM;
			int t2_YYYY2 = rtc_YYYY;
		
			String YYYYMMDD2 = String(t2_YYYY2)+""+String(print2digits(t2_MM2))+""+String(print2digits(t2_DD2));
			String HHMM2 = String(print2digits(t2_hh2))+String(print2digits(t2_mm2));
			String YYYYMMDD_HHMM2 = YYYYMMDD2+"-"+HHMM2;
			
			Serialprint("1:["+YYYYMMDD_HHMM1+"]["+tcommand1+"]");
			Serialprint("2:["+YYYYMMDD_HHMM2+"]["+tcommand2+"]"); 
			
			for (byte j1 = 0; j1 < 10; j1++){
				if (String(timer_date_array[j1]) == ""){
					strlcpy(timer_date_array[j1], YYYYMMDD1.c_str(), YYYYMMDD1.length()+1);
					strlcpy(timer_time_array[j1], HHMM1.c_str(), HHMM1.length()+1);
					strlcpy(timer_command_array[j1], tcommand1.c_str(), tcommand1.length()+1);
					break;
				}
			}
					
			for (byte j = 0; j < 10; j++){
				if (String(timer_date_array[j]) == ""){
					strlcpy(timer_date_array[j], YYYYMMDD2.c_str(), YYYYMMDD2.length()+1);
					strlcpy(timer_time_array[j], HHMM2.c_str(), HHMM2.length()+1);
					strlcpy(timer_command_array[j], tcommand2.c_str(), tcommand2.length()+1);
					break;
				}
			} 
					
			add_out_array(chat_id, "установка таймеров\n+1:["+YYYYMMDD_HHMM1+"]["+tcommand1+"]\n+2:["+YYYYMMDD_HHMM2+"]["+tcommand2+"]");	
			memcpy(in_msg_array[j], "", 200);
			komanda = "/t";
			saveAset();
			
		//------------------
		}else{add_out_array(chat_id, komanda_0+": тебе не разрешено, команда не будет выполнена");}
					

		}
		
		
		
				// Домовой /ping
		if (komanda.equalsIgnoreCase("/Домовой") || komanda.equalsIgnoreCase("/ping")){
			add_out_array(chat_id, "ok " + IP + " " + uptime );
			add_out_array(chat_id, list_KeyCmd(0) +"\n"+ list_LineCmd());
			com_ok = 1;
		}
		
		// /start
		if (komanda.equalsIgnoreCase("/start") || komanda.equalsIgnoreCase("/start")){
			//add_out_array(chat_id, StartMsg());
			
			if (config.sendTLG == 1){
				add_out_array(chat_id, list_KeyCmd(0) +"\n"+ list_LineCmd());
				//UniversalTelegramBot bot(config.BOTtoken, clientT);
				bot.sendMessageWithReplyKeyboard(chat_id, "включена клавиатура команд", "", Keyboard(), true );
			
			

			
			}
			
			com_ok = 1;
		}
		
		
		
		
		if ((komanda == "/111") || (komanda == "/kbrd")){
					String keyboardJson = "\
[[{ \"text\" : \"Включить охрану\", \"callback_data\" : \"/alarmOn\" },\
{ \"text\" : \"Выключить охрану\", \"callback_data\" : \"/alarmOff\" }]]";
			bot.sendMessageWithInlineKeyboard(chat_id, ":", "", keyboardJson);
		com_ok = 1;
		}
		
		
		
		
		
		if ((komanda == "/t") || (komanda == "/Таймеры")){

/* 			String msg = "Таймеры:\n";
			msg += "1. " + String(timer_date_array[0]) + " " + String4(timer_time_array[0]) + " " + String(timer_command_array[0]) + " " + String(timer_exdate_array[0]) + " " + String4(timer_extime_array[0]) + "\n";
			msg += "2. " + String(timer_date_array[1]) + " " + String4(timer_time_array[1]) + " " + String(timer_command_array[1]) + " " + String(timer_exdate_array[1]) + " " + String4(timer_extime_array[1]) + "\n";
			msg += "3. " + String(timer_date_array[2]) + " " + String4(timer_time_array[2]) + " " + String(timer_command_array[2]) + " " + String(timer_exdate_array[2]) + " " + String4(timer_extime_array[2]) + "\n";
			msg += "4. " + String(timer_date_array[3]) + " " + String4(timer_time_array[3]) + " " + String(timer_command_array[3]) + " " + String(timer_exdate_array[3]) + " " + String4(timer_extime_array[3]) + "\n";
			msg += "5. " + String(timer_date_array[4]) + " " + String4(timer_time_array[4]) + " " + String(timer_command_array[4]) + " " + String(timer_exdate_array[4]) + " " + String4(timer_extime_array[4]) + "\n";
			msg += "6. " + String(timer_date_array[5]) + " " + String4(timer_time_array[5]) + " " + String(timer_command_array[5]) + " " + String(timer_exdate_array[5]) + " " + String4(timer_extime_array[5]) + "\n";
			msg += "7. " + String(timer_date_array[6]) + " " + String4(timer_time_array[6]) + " " + String(timer_command_array[6]) + " " + String(timer_exdate_array[6]) + " " + String4(timer_extime_array[6]) + "\n";
			msg += "8. " + String(timer_date_array[7]) + " " + String4(timer_time_array[7]) + " " + String(timer_command_array[7]) + " " + String(timer_exdate_array[7]) + " " + String4(timer_extime_array[7]) + "\n";
			msg += "9. " + String(timer_date_array[8]) + " " + String4(timer_time_array[8]) + " " + String(timer_command_array[8]) + " " + String(timer_exdate_array[8]) + " " + String4(timer_extime_array[8]) + "\n";
			msg += String(YYYYMMDD)+" "+String6(HHMMSS)+"\n"; */

			add_out_array(chat_id, listTimers());
			memcpy(in_msg_array[j], "", 200);
			com_ok = 1;
			//break;
		}
		
		//komanda.replace("/","");
		
		if (komanda.equalsIgnoreCase("/raport")){
			add_out_array(chat_id, config.botinfo+"\nстатус:\n"+status(1)+"\n"+uptime+"\n"+listTimers());com_ok = 1; 	}
		
		if (komanda.equalsIgnoreCase("/status")){
			add_out_array(chat_id, "статус:\n"+status(1)+"\n"+list_KeyCmd(0)+"\n"+list_LineCmd()+"\n"+uptime);com_ok = 1; 	}
			
		if (komanda.equalsIgnoreCase("/commands")){
			add_out_array(chat_id, list_KeyCmd(0)+"\n"+list_LineCmd());com_ok = 1; 	}
			
		if (komanda.equalsIgnoreCase("/list_cmd")){
			add_out_array(chat_id, list_KeyCmd(0)+"\n"+list_LineCmd());com_ok = 1; 	}
		
		//if (komanda.equalsIgnoreCase("status")){add_out_array(chat_id, "статус:\n"+status(1)+"\n"+list_KeyCmd(0)+"\n"+uptime);com_ok = 1; 	}
		//if (komanda.equalsIgnoreCase("commands")){add_out_array(chat_id, list_KeyCmd(0));com_ok = 1; 	}
		//if (komanda.equalsIgnoreCase("list_cmd")){add_out_array(chat_id, list_KeyCmd(0));com_ok = 1; 	}
		
		
		if (komanda.equalsIgnoreCase("/restart")){
			if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
				//------------------
				Serialprint("---RESTART---");
		WiFi.disconnect();		delay(3000);		ESP.restart();
			}else{add_out_array(chat_id, config.botname+": тебе не разрешено, команда не будет выполнена");}
			com_ok = 1;
		}
	
	
		if (komanda.indexOf("/m_") == 0){Msg_for_Minion(in_user_array[j],komanda); com_ok = 1;}
		if (komanda.indexOf("/m0") == 0){Msg_for_Minion(in_user_array[j],komanda); com_ok = 1;}
		
		
		
		if (com_ok ==0){com_ok = DO_CMD(komanda,chat_id);}
		
		if (com_ok == 0){add_out_array(chat_id, "userID:"+chat_id+"\nЩТА?\n{"+komanda_0+"}\n{"+komanda+"}\n");}

		
		
		//обработал - почистил очередь
		memcpy(in_user_array[j], 		"", 20);
		memcpy(in_msg_array[j], 		"", 200);
		memcpy(in_iniciator_array[j], 	"", 200);
	}
	
	
	return 1;

}

/* #include <HTTPClient.h>
HTTPClient http; */

//---------------------------------------------------------
int Send_msg_to_Svyaznoy(String chat_id, String msg, String sek){
	
	if (chat_id == ""){return 1;}
	if (chat_id == "1"){return 1;}
	if (msg == ""){return 1;}
	if (AP == 1){return 1;}  

	if ((millis() - SendErrorSVZ_lasttime < 5000) && (millis() > 5000)){return 0;}
	Serialprintln("->svz: ["+chat_id+"]["+msg+"]["+sek+"]");

	if (!client.connect(config.ip_svyaznoy.c_str(), 80, 1500)){
		Serialprint("ERR: connection to svyaznoy failed");	
		SendErrorSVZ_lasttime = millis();		
		client.flush();	client.stop();// kill_tcp(); 
		return 0;
	}

	// исключения для команд минионам
	if (msg.indexOf("/m_") != 0){msg = "Ⓜ " + config.botname + " /m_"+ip4+"\n" + msg;}
	// исключения для команд минионам

	String url = "/input?chat_id=" + chat_id +"&bot_ip=" + IP + "&minion=" + config.botname + "&sek=" + sek;

//msg = "0"+msg+"0";

//Сonnection: close\r\n\
//Content-Type: text/plain\r\n\
	
	String msglength = String(msg.length());
	String command = "POST " + url + " HTTP/1.1\r\n\
Сonnection: close\r\n\
Content-Type: text/plain\r\n\
Host: " + config.ip_svyaznoy + "\r\n\
Content-Length: " + msglength + "\r\n\r\n" + msg;

	client.print(command);
	//client.flush();

// не работает
/* 	String sn = "http://"+config.ip_svyaznoy+":80"+url;
    Serial.println(sn);
	http.begin(sn);
	//http.addHeader("Content-Type", "text/plain");
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");
	String httpRequestData = msg;           
    int httpResponseCode = http.POST(httpRequestData);
	Serial.print("HTTP Response code: ");    
	Serial.print(httpResponseCode+" ");    
	Serial.println(http.errorToString(httpResponseCode).c_str());
	String payload = http.getString();
    Serial.println(payload);
    http.end();
	return 1;
	delay(500); */



/* 			Serialprint("================");			
//http.setReuse(true);
	http.begin("http://192.168.1.251/cfg");
int httpCode = http.GET();
if(httpCode > 0){
Serial.printf("[HTTP] GET... code: %d\n", httpCode);

// file found at server
if(httpCode == HTTP_CODE_OK){http.writeToStream(&Serial);}
} else{Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());}
http.end();
			Serialprint("================");	 */		






	uint32_t timeout = millis();
	while (!client.available()){
		if (millis() - timeout > 3000){
			Serialprint("ERR: Send_msg_to_Svyaznoy timeout 3 s!");			
			SendErrorSVZ_lasttime = millis();
			client.flush();
			client.stop();
			return 0;
		}
	}

	String line = "";	
	while (client.available()){line += String(char(client.read()));}
	Serialprint("<-svz: " + line);
	client.flush();
	client.stop();

	//client.flush();	client.stop();	kill_tcp();
	return 1;
}



uint32_t botlast_message_sending;


//---------------------------------------------------------
int Send_msg_to_(String chat_id, String msg, String sek){

	if (msg == ""){return 1;}
	if (chat_id == ""){return 1;}
	if (chat_id == "1"){chat_id = config.alarm_chat_id;}
	
	int rez = 1;
	if (config.sendTLG == 1){
		
		if (millis() < botlast_message_sending){return 0;}
		
		msg = trim(msg); if (msg == ""){return 1;}		

		Serialprint("-Send_msg_to_TlgBot-:["+chat_id+"]["+msg+"]");
		if (msg.indexOf("Ⓜ") >= 0){}
		else{msg = "ℹ " + config.botname + " /m_"+ip4+"\n" + msg;}

		rez = botsendMessage(chat_id,msg,"");
		
		//Uskoritel = 10;
		//rez = 1;
	
		if(msg.indexOf("!!!") >= 0){
			if (config.BOTtoken_ALARM != ""){
				Serialprint("-Send_msg_to_TlgBot_ALARM-:["+chat_id+"]["+msg+"]");
				bot.BOTtoken(config.BOTtoken_ALARM);
				rez = botsendMessage(chat_id,msg,"");
				bot.BOTtoken(config.BOTtoken);
			}
		}
	}	
		
		
	if (config.send_svyaznoy == 1){
		//Serialprint("-Send_msg_to_Svyaznoy-:["+chat_id+"]["+msg+"]["+sek+"]");
		rez = Send_msg_to_Svyaznoy(chat_id, msg, sek);
	}

/* 	if (config.send_SMS == 1){
		Serialprint("-Send_msg_to_SMS-:["+chat_id+"]["+msg+"]");
		rez = Send_msg_to_SMS(chat_id, msg, sek);
	} */
	
	return rez;
	
	//String msg2 = "<txt:"+msg+">";
	//Serialprint("->["+msg2+"]");
	//msg.replace(";", ">\n\r<txt:");
	//msg.replace(";", ">\r\n<txt:");
	//msg.replace(";", ">\n<txt:");
	//String msg3 = "<txt:"+msg+">";
	//Serial.println(msg3);
	//SerialBT.println(msg3);
} 

//---------------------------------------------------------
void Obrabotka_ishodyashih(){
	
	for (byte j = 0; j < 10; j++)
{
		if (String(out_msg_array[j]) != ""){
			String chat_id 	= String(out_user_array[j]); 
			String text 	= String(out_msg_array[j]); 
			String ishnomer = String(out_sek_array[j]); 
			
			if (text.indexOf("/m_") == 0){
				//от миньон к миньону перекладываем из out_msg_array в in_msg_array
				//Serialprint("<-m-m-["+chat_id+"]["+text+"]");
				for (byte j2 = 0; j2 < 10; j2++){
					if (String(in_msg_array[j2]) == ""){
						int ln2 = text.length() + 1;
						char ss2[ln2];
						text.toCharArray(ss2, ln2);
						memcpy(in_msg_array[j2], ss2, ln2);
						memcpy(in_user_array[j2], "", 20);
						
						memcpy(out_msg_array[j], "", 2000);      
						memcpy(out_user_array[j], "", 60);      
						break;
					}
				}
				
			}else{
				int rez = Send_msg_to_(chat_id, text, ishnomer);
				//Serialprintln("Send_msg_to_ rez="+String(rez));
				if (rez == 1){memcpy(out_msg_array[j], "", 2000);}      
				return; // return - по одному или все в одном loop ()
			}
		}
	}

}


void _10sek(){
	
	
		// 10 секунд
		
	if ((millis() > (Bot_lasttime + 10000)) ){
		uint32_t ss = millis() / 1000; uint32_t mm = ss / 60; uint32_t hh = mm / 60; uint32_t dd = hh / 24;
		String upt = String(ss) + "с ";
		if (mm != 0){upt = String(mm) + "м ";}
		if (hh != 0){upt = String(hh) + "ч ";} 
		if (dd != 0){upt = String(dd) + "д ";}
		uptime = "up: " + upt + "m: " + String(ESP.getFreeHeap() / 1000) + "k";
		print_lcd(2,0,uptime);
		if (RTCread() == 0){time_h_read();}
		print_lcd(0,0,YYYYMMDD_HHMMSS);
		
		connect_();
		
		Bot_lasttime = millis(); 
	}
	
}




//---------------------------------------------------------
void loop(){
	
	//vTaskDelay(portMAX_DELAY);
	//OR
	//vTaskDelete(NULL);
	//return;
	

	if (1 == 1){// для свёртывания кода
		//if (millis() < Dom_lasttime){Dom_lasttime = 0;}
		if (millis() < Bot_lasttime){Bot_lasttime = 0;}
		if (millis() < Clear_log_lasttime){Clear_log_lasttime = 0;}
	}	
	
	Slushat_Port(); 
	server.handleClient();
	Obrabotka_ishodyashih();
	
	Obrabotka_vhodyashih();

	String msg = status(0);
	if (msg != ""){
		//add_out_array("","🅰 изменение статуса: "+msg);			
		add_out_array("1","🅰 "+msg);			
		//OLED_lasttime = 0;
		//print_lcd(0,0,"");
	}
				


	_10sek();

	
	
	
	// таймеры 
	if ((millis() > (Timers_lasttime + Timers_interval)) ){
		int u = 0;
		for (byte j1 = 0; j1 < 10; j1++){
			if (String(timer_date_array[j1]) != ""){
			
				String d 	= String(timer_date_array[j1]);
				String t 	= String(timer_time_array[j1]);
				String t_m 	= t.substring(2); //Serial.println("t_m="+t_m);
				
				String exd 	= String(timer_exdate_array[j1]);
				String ext 	= String(timer_extime_array[j1]);

				//Serialprint("d="+d+"/"+String(YYYYMMDD)+" t="+t+"/"+String4(HHMM) );
				
				if  (d.indexOf("*") == -1) {
					if  (YYYYMMDD > d.toInt()) {
						memcpy(timer_date_array[j1], "", 8);	
						memcpy(timer_time_array[j1], "", 4);	
						memcpy(timer_repeet_array[j1], "", 1);	
						memcpy(timer_command_array[j1], "", 100);	
						memcpy(timer_exdate_array[j1], "", 8);	
						memcpy(timer_extime_array[j1], "", 4);	
						u = 1;
				}	}
				
				
				if (exd != ""){
					if (exd.toInt() <= YYYYMMDD && ext.toInt() < HHMM && d.indexOf("*") >= 0){
						memcpy(timer_exdate_array[j1], "", 8);	
						memcpy(timer_extime_array[j1], "", 4);	
						u = 1;
					}
					if (exd.toInt() <= YYYYMMDD && ext.toInt() < HHMM && d.indexOf("*") == -1){
						memcpy(timer_date_array[j1], "", 8);	
						memcpy(timer_time_array[j1], "", 4);	
						memcpy(timer_repeet_array[j1], "", 1);	
						memcpy(timer_command_array[j1], "", 100);	
						memcpy(timer_exdate_array[j1], "", 8);	
						memcpy(timer_extime_array[j1], "", 4);	
						u = 1;
					}
				} 
				
				
				if ( (d.indexOf("*") == -1) && ( t.indexOf("*") == -1) && (YYYYMMDD == d.toInt()) && (HHMM == t.toInt()) && (exd == "") ){
					String chat_id = config.admin_chat_id;
					String text = timer_command_array[j1];
					add_input_array("", text, "таймер "+m_prefix);
					memcpy(timer_exdate_array[j1], String(YYYYMMDD).c_str(), 8);	
					memcpy(timer_extime_array[j1], String4(HHMM).c_str(), 4);	
					u = 1;
				}
				
				if ( (d.indexOf("*") >= 0) && ( t.indexOf("*") == -1) && (HHMM == t.toInt()) && (exd == "") ) {
					String chat_id = config.admin_chat_id;
					String text = timer_command_array[j1];
					add_input_array("", text, "таймер "+m_prefix);
					memcpy(timer_exdate_array[j1], String(YYYYMMDD).c_str(), 8);	
					memcpy(timer_extime_array[j1], String4(HHMM).c_str(), 4);	
					u = 1;
				}
				
				if ( (d.indexOf("*") >= 0) && ( t.indexOf("*") >= 0 ) && (MM == t_m.toInt()) && (exd == "") ) {
					String chat_id = config.admin_chat_id;
					String text = timer_command_array[j1];
					add_input_array("", text, "таймер "+m_prefix);
					memcpy(timer_exdate_array[j1], String(YYYYMMDD).c_str(), 8);	
					memcpy(timer_extime_array[j1], String4(HHMM).c_str(), 4);	
					u = 1;
				}
				
				
				
				
			}
		}
		Timers_lasttime = millis();
		if (u == 1){saveAset();}
	}
	
	
	
	
	
	
	
	

	if (millis() > Clear_log_lasttime + config.Clear_log_interval){
		savelog();
		Clear_log_lasttime = millis();
		txtlog = "";
	}

	if (config.getTLG == 1){getUpdTLG();}
	
	if (config.OTA == 1){ArduinoOTA.handle();}




	if (config.F_DS18B20 == 1){
		if (millis() > Temp_lasttime + Temp_interval){
			// call sensors.requestTemperatures() to issue a global temperature
			// request to all devices on the bus
			//Serialprint("Requesting temperatures...");
			DS18B20.requestTemperatures();
			//Serialprintln("DONE");
			// print the device information
			//printData(Thermometer1);
			//printData(Thermometer2);
			tempC1 = DS18B20.getTempC(Thermometer1);
			tempC2 = DS18B20.getTempC(Thermometer2);
			//tempC3 = DS18B20.getTempC(Thermometer3);
			//Serialprint("t1 C= "+String(tempC1)+" t2 C= "+String(tempC2)+" t3 C= "+String(tempC3));
			print_lcd(5, 0, "#"+String(tempC1)+" "+String(tempC2)+"#");
			//print_lcd(5, 0, String(tempC1)+" "+String(tempC2));
			//print_lcd(6, 0, String(tempC3));
			
			Temp_lasttime = millis();

		}
	}	
	

	
	
	if (config.F_Ohrana == 1){
		if (OHRANA == 1){
			if ((int(digitalRead(config.F_Ohrana_Trevoga_GPIO)) == 1) && (TREVOGA == 0)){
				TREVOGA = 1;
				//Serialprintln("type=TREVOGA");
				DO_CMD("type=TREVOGA","");
			}
		}
		
	}
	
	if (config.use_RF_PULT == 1){
		
		if (mySwitch.available()){
			uint32_t kod = mySwitch.getReceivedValue();

			//output(kod, mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(), mySwitch.getReceivedProtocol());
			Serialprintln("RF433:"+String(kod));
			String _kod = ","+String(kod)+",";
			if (millis() > RFS_cods_lasttime + 30000 ){RFS_cods = "";}
			
			if (RFS_cods.indexOf(_kod) >= 0){
					
			}else{
				add_out_array("","Слышу 433 МГц - "+String(kod));
				RFS_cods = RFS_cods + _kod;
				RFS_cods_lasttime = millis();
			}
				
			if (millis() - 	RFKEY1_lasttime > 3000){if (config.RF_keys_1.indexOf(_kod)>-1){add_input_array("",config.cmd01); RFKEY1_lasttime = millis();}}
			if (millis() - 	RFKEY2_lasttime > 3000){if (config.RF_keys_2.indexOf(_kod)>-1){add_input_array("",config.cmd02); RFKEY2_lasttime = millis();}}
			if (millis() - 	RFKEY3_lasttime > 3000){if (config.RF_keys_3.indexOf(_kod)>-1){add_input_array("",config.cmd03); RFKEY3_lasttime = millis();}}
			if (millis() - 	RFKEY4_lasttime > 3000){if (config.RF_keys_4.indexOf(_kod)>-1){add_input_array("",config.cmd04); RFKEY4_lasttime = millis();}}
			if (millis() - 	RFKEY5_lasttime > 3000){if (config.RF_keys_5.indexOf(_kod)>-1){add_input_array("",config.cmd05); RFKEY5_lasttime = millis();}}
			if (millis() - 	RFKEY6_lasttime > 3000){if (config.RF_keys_6.indexOf(_kod)>-1){add_input_array("",config.cmd06); RFKEY6_lasttime = millis();}}
			if (millis() - 	RFKEYTREVOGA_lasttime > 300000){if (config.RF_keys_TREVOGA.indexOf(_kod)>-1){DO_CMD("type=TREVOGA","");  RFKEYTREVOGA_lasttime = millis();}}
			
				//Serialprint("RFA="+String(config.RF_array));
				//Serialprint("kod="+String(kod));
			
			if (config.RF_array.indexOf(String(kod)) >= 0){
				
				//rs = Countsubstring(config.RF_array);

				int np = get_np_T(config.RF_array, String(kod), 3);
				String name = get_v(config.RF_array,np,3,1);
				String cmd = get_v(config.RF_array,np,3,2);
				
				Serialprint("np="+String(np));
				Serialprint("name="+String(name));
				Serialprint("cmd="+String(cmd));
				add_input_array("",cmd);
			};
			
			
		}	
		mySwitch.resetAvailable();
	}
	
	
	
} //end loop


//---------------------------------------------------------
int DO_CMD(String cmd, String chat_id){
	
	int rez = 0;
	cmd += "&";
	cmd.replace("&&", "&");

	String cmd_arg = cmd;
	//Serialprint("void DO_CMD() cmd = " + cmd);

// просто сообщение хз зачем этот функционал
	if (cmd_arg.indexOf("/msg=") == 0){
		String msg0 = cmd_arg.substring(cmd_arg.indexOf("msg=") + 4, cmd_arg.indexOf("&"));
		cmd_arg.replace(msg0 + "&", "");
		msg0.replace("msg=", "");
		add_out_array(chat_id,msg0);
		rez = 1;
	} 

	if (cmd_arg.indexOf("/msg_to_m=") == 0){
		String msg0 = cmd_arg.substring(cmd_arg.indexOf("msg_to_m=") + 9, cmd_arg.indexOf("&"));
		cmd_arg.replace(msg0 + "&", "");
		msg0.replace("msg_to_m=", "");
		add_out_array(chat_id,msg0);
		rez = 1;
	}




//http://192.168.1.242/input_svz?msg=/print_lcd=хо-хо-хо&chat_id=1
//http://192.168.1.242/input_svz?msg=/relay_GPIO=5_dodo=invert&chat_id=1
//http://192.168.1.242/input_svz?msg=/status&chat_id=1


	if (cmd_arg.indexOf("/print_lcd=") == 0){
		String msg0 = cmd_arg.substring(cmd_arg.indexOf("print_lcd=") + 10, cmd_arg.indexOf("&"));
		cmd_arg.replace(msg0 + "&", "");
		msg0.replace("print_lcd=", "");
		print_lcd(7,0,msg0);
		//add_out_array(chat_id,msg0);
		rez = 1;
	}

//команды
	String type = cmd_arg.substring(cmd_arg.indexOf("type=") + 5, cmd_arg.indexOf("&"));
	//cmd_arg.replace(type + "&", "");
	//type.replace("type=", "");

	if (type == "status"){add_out_array(chat_id,status(1));		rez = 1;	}

	if (cmd_arg.indexOf("/relay_") == 0) // /input_svz?msg=relay_GPIO=X_dodo=X
	{
		cmd_arg.replace("relay_","");
		String GPIOs = cmd_arg.substring(cmd_arg.indexOf("GPIO=") + 5, cmd_arg.indexOf("_"));
		cmd_arg.replace(GPIOs + "_", "");
		GPIOs.replace("GPIOs=", "");
		int GPIO = GPIOs.toInt();
		String dodo = cmd_arg.substring(cmd_arg.indexOf("dodo=") + 5, cmd_arg.indexOf("&"));
		cmd_arg.replace(dodo + "&", "");
		dodo.replace("dodo=", "");
		pinMode(GPIO, OUTPUT);
		
		
		if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
		//------------------
		if (dodo == "on"){digitalWrite(GPIO, HIGH);}
		if (dodo == "off"){digitalWrite(GPIO, LOW);}
		if (dodo == "invert"){digitalWrite(GPIO, !digitalRead(GPIO));}
		if (dodo == "onoff"){digitalWrite(GPIO, HIGH);      delay(750);      digitalWrite(GPIO, LOW);}
		saveAset();
		//------------------
		}else{add_out_array(chat_id, cmd+": тебе не разрешено, команда не будет выполнена");}
		rez = 1;
	}

	if (config.F_Ohrana == 1){
		if ((type == "/OHRANA_on")  && (OHRANA == 0 )){
			if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
			//------------------
			OHRANA = 1;
			saveAset();
			//------------------
			}else{add_out_array(chat_id, cmd+": тебе не разрешено, команда не будет выполнена");}
			add_out_array(chat_id, "Охрана вкл!");
		}
		if ((type == "/OHRANA_off") && (OHRANA == 1 )){
			if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
			//------------------
			OHRANA = 0;
			TREVOGA = 0;
			digitalWrite(config.F_Ohrana_Sirena_GPIO, LOW);
			saveAset();
			}else{add_out_array(chat_id, cmd+": тебе не разрешено, команда не будет выполнена");}
			add_out_array(chat_id, "Охрана вЫкл!");
		}
		if ((type == "/TREVOGA") && (OHRANA == 1 )){
			if (config.legal_chat_id.indexOf(","+chat_id+",") >= 0){
				//------------------
				//if (millis() - Alarm_lasttime  > 300000){
				TREVOGA = 1;
				digitalWrite(config.F_Ohrana_Sirena_GPIO, HIGH);
				}else{add_out_array(chat_id, cmd+": тебе не разрешено, команда не будет выполнена");}

				add_out_array(chat_id, "ТРЕВОГА, ОХРАНА, ГРАБЮ-Ю-Ю-Т !!!");
				//Alarm_lasttime = millis();			
			//}
			
		} 
		rez = 1;
	}
	
	return rez;
}


//---------------------------------------------------------
void add_input_array(String chat_id, String msg){
	add_input_array(chat_id, msg, "");
}

void add_input_array(String chat_id, String msg, String iniciator){
	
	String chat_id_v = chat_id;
	
	if (chat_id == ""){chat_id = config.admin_chat_id;} 
	msg = trim(msg); if (msg == ""){return;}	
	
	Serialprint("+in_array: ["+chat_id+"]["+msg+"]["+iniciator+"]");	
	
	if (config.botname == "Домовой"){
		add_out_array(config.admin_chat_id, "услышал: "+msg+" от "+iniciator+"  "+chat_id_v);
		if (config.admin_chat_id !=chat_id){add_out_array(chat_id, "услышал: "+msg+" от "+iniciator+"  "+chat_id_v);}
	}

	for (byte j = 0; j < 10; j++){
		if (String(in_msg_array[j]) == ""){
			strlcpy(in_user_array[j], 		chat_id.c_str(), 	chat_id.length()+1);
			strlcpy(in_msg_array[j], 		msg.c_str(), 		fmin(msg.length()+1,200));
			strlcpy(in_iniciator_array[j], 	iniciator.c_str(), 	fmin(iniciator.length()+1,200));
			//strlcpy(in_msg_array[j], msg.c_str(), msg.length()+1);
			//Serialprint("+in_array проверка : ["+String(in_user_array[j])+"]["+String(in_msg_array[j])+"]["+String(in_iniciator_array[j])+"]");
			break;
		}
	}
	
}



//---------------------------------------------------------
int add_out_array_once(String chat_id, String msg){
		for (byte j = 0; j < 10; j++){
		if (String(out_msg_array[j]) == ""){
			
			Serialprint("+out_array_once: ["+chat_id+"]["+msg+"]");

			strlcpy(out_user_array[j], chat_id.c_str(), chat_id.length()+1);
			strlcpy(out_msg_array[j], msg.c_str(), fmin(msg.length()+1,2000));
			strlcpy(out_sek_array[j], String(Ishod_nomer_msg).c_str(), 10);
			Ishod_nomer_msg++;

			break;
		}
	}
}

//---------------------------------------------------------
int add_out_array(String chat_id, String msg){
	
	if (chat_id == ""){chat_id = config.admin_chat_id;} 
	if (chat_id == "1"){chat_id = config.alarm_chat_id;}
	msg = trim(msg);if (msg == ""){Serialprint("---ERR--- пустое msg add_out_array");return 1;}
	
	//Serialprint("+out_array: ["+chat_id+"]["+msg+"]");
	
	if(String(out_msg_array[0]) == "" && String(out_msg_array[1]) != ""){
		strlcpy(out_user_array[0], out_user_array[1], 60);
		strlcpy(out_msg_array[0], out_msg_array[1], 2000);
		strlcpy(out_sek_array[0], out_sek_array[1], 10);
		strlcpy(out_user_array[1], "", 60);
		strlcpy(out_msg_array[1], "", 2000);
		strlcpy(out_sek_array[1], "", 10);
	}
			
		
	// if (chat_id.indexOf(",") > 0){
		chat_id = chat_id + ",";
		while (chat_id.indexOf(",")>0){
			int p = chat_id.indexOf(",");
			String _c = chat_id.substring(0, p);
			chat_id = chat_id.substring(chat_id.indexOf(",") + 1);
			add_out_array_once(_c,msg); 
		}
	// }
	// else{
		// add_out_array_once(chat_id,msg); 
	// }
	
	return 1;
}








//---------------------------------------------------------
String status(int a){

//------ ЭТА НЕПОНЯТНАЯ ХУЙНЯ ! РАБОТАЕТ ! ----------
//------ опрос портов и события, описанных как в cfg ----------
	String msg = "";
	

/* 	
	if ((config.F_DHT == 1) && (a == 1)){
		humidity = dht.getHumidity();
		temperature = dht.getTemperature();
		msg +="\nТемпература = "+ String(temperature) + "°";
		msg +="\nВлажность = "+ String(humidity) + " %";
	} */


	if ((config.F_DS18B20 == 1) && (a == 1)){
		msg +="\n"+config.DS18B20_1_name+" = "+ String(tempC1) + "°";
		msg +="\n"+config.DS18B20_2_name+" = "+ String(tempC2) + "°";
	}
	
	if (config.F_DS18B20 == 1){
		
		if (config.DS18B20_1_Alarm == 1){
			if(tempC1 < config.DS18B20_1_min){
				msg += "\n"+config.DS18B20_1_msg+" ("+config.DS18B20_1_min+"/"+config.DS18B20_1_max+")";
				msg +="\nt = "+ String(tempC1) + "°";
				config.DS18B20_1_Alarm = 2;
				}
			if(tempC1 > config.DS18B20_1_max){
				msg += "\n"+config.DS18B20_1_msg+" ("+config.DS18B20_1_min+"/"+config.DS18B20_1_max+")";
				msg +="\nt = "+ String(tempC1) + "°";
				config.DS18B20_1_Alarm = 2;}
			DS18B20_1_Alarm_lasttime = millis(); 
		}
		
		if (config.DS18B20_1_Alarm == 2){
			if(millis() > DS18B20_1_Alarm_lasttime + 3600000 ){
				if(tempC1 < config.DS18B20_1_min){
					msg += "\n"+config.DS18B20_1_msg+" ("+config.DS18B20_1_min+"/"+config.DS18B20_1_max+")";
				msg +="\nt = "+ String(tempC1) + "°";
					config.DS18B20_1_Alarm = 2;}
				if(tempC1 > config.DS18B20_1_max){
					msg += "\n"+config.DS18B20_1_msg+" ("+config.DS18B20_1_min+"/"+config.DS18B20_1_max+")";
				msg +="\nt = "+ String(tempC1) + "°";
					config.DS18B20_1_Alarm = 2;}
				DS18B20_1_Alarm_lasttime = millis(); 
			}
			if((tempC1 >= config.DS18B20_1_min) && (tempC1 <= config.DS18B20_1_max)){
				msg += "\n"+config.DS18B20_1_msg_ok+" ("+config.DS18B20_1_min+"/"+config.DS18B20_1_max+")";
				msg +="\nt = "+ String(tempC1) + "°";
				config.DS18B20_1_Alarm = 1;
				DS18B20_1_Alarm_lasttime = 0; 
			}
		}
		

		if (config.DS18B20_2_Alarm == 1){
			if(tempC2 < config.DS18B20_2_min){
				msg += "\n"+config.DS18B20_2_msg+" ("+config.DS18B20_2_min+"/"+config.DS18B20_2_max+")";
				msg +="\nt = "+ String(tempC2) + "°";
				config.DS18B20_2_Alarm = 2;}
			if(tempC2 > config.DS18B20_2_max){
				msg += "\n"+config.DS18B20_2_msg+" ("+config.DS18B20_2_min+"/"+config.DS18B20_2_max+")";
				msg +="\nt = "+ String(tempC2) + "°";
				config.DS18B20_2_Alarm = 2;}
			DS18B20_2_Alarm_lasttime = millis(); 
		}
		
		if (config.DS18B20_2_Alarm == 2){
			if(millis() > DS18B20_2_Alarm_lasttime + 3600000 ){
				if(tempC2 < config.DS18B20_2_min){
					msg += "\n"+config.DS18B20_2_msg+" ("+config.DS18B20_2_min+"/"+config.DS18B20_2_max+")";
					msg +="\nt = "+ String(tempC2) + "°";
					config.DS18B20_2_Alarm = 2;}
				if(tempC2 > config.DS18B20_2_max){
					msg += "\n"+config.DS18B20_2_msg+" ("+config.DS18B20_2_min+"/"+config.DS18B20_2_max+")";
					msg +="\nt = "+ String(tempC2) + "°";
					config.DS18B20_2_Alarm = 2;}
				DS18B20_2_Alarm_lasttime = millis(); 
			}
			if((tempC2 >= config.DS18B20_2_min) && (tempC2 <= config.DS18B20_2_max)){
				msg += "\n"+config.DS18B20_2_msg_ok+" ("+config.DS18B20_2_min+"/"+config.DS18B20_2_max+")";
				msg +="\nt = "+ String(tempC2) + "°";
				config.DS18B20_2_Alarm = 1;
				DS18B20_2_Alarm_lasttime = 0; 
			}
		}
		
	}

	if ((config.F_Ohrana == 1) && (a == 1)){
		if (OHRANA == 1){msg +="\nОхрана вкл!";	}
		if (OHRANA == 0){msg +="\nОхрана вЫкл!";}
	}

	if (config.F_UltraSonic == 1){
		 int dist = hcsr04.read(config.F_UltraSonic_trig_GPIO, config.F_UltraSonic_echo_GPIO)-0;
		 if ((dist > hcsr04_lastvalue + config.hcsr04_delta)||(dist < hcsr04_lastvalue - config.hcsr04_delta)||(a == 1)){
			delay(200);
			dist = hcsr04.read(config.F_UltraSonic_trig_GPIO, config.F_UltraSonic_echo_GPIO)-0;
			if ((dist > hcsr04_lastvalue + config.hcsr04_delta)||(dist < hcsr04_lastvalue - config.hcsr04_delta)||(a == 1)){
				//msg +="\nДистанция = "+ String(dist) + " см.";
				hcsr04_lastvalue = dist;
				print_lcd(3,0,"Д см = "+String(hcsr04_lastvalue));
			}
		 }
	}




//*********************************************************************************************************
// шаблон XX занеит на номер порта 00..99, Y заменить на номер порта 0...99
//*********************************************************************************************************
/* 
if (config.inXXi == 1){
	int actst = digitalRead(Y);
	if (( actst != inXXGPIO_lastState ) || (a == 1)){
		inXXGPIO_lastState = actst;  
		msg +="\n"+ config.inXXname;
		if (actst == 0) { msg += " " + config.inXXi0; if (a == 0){add_input_array("",config.inXXcmd0);} }
		if (actst == 1) { msg += " " + config.inXXi1; if (a == 0){add_input_array("",config.inXXcmd1);} }
	}
}
 *///*********************************************************************************************************



if (config.in00i == 1){
	int actst = digitalRead(0);
	if (( actst != in00GPIO_lastState ) || (a == 1)){
		in00GPIO_lastState = actst;  
		msg +="\n"+ config.in00name;
		if (actst == 0) { msg += " " + config.in00i0; if (a == 0){add_input_array("",config.in00cmd0);} }
		if (actst == 1) { msg += " " + config.in00i1; if (a == 0){add_input_array("",config.in00cmd1);} }
	}
}

if (config.in02i == 1){
	int actst = digitalRead(2);
	if (( actst != in02GPIO_lastState ) || (a == 1)){
		in02GPIO_lastState = actst;  
		msg +="\n"+ config.in02name;
		if (actst == 0) { msg += " " + config.in02i0; if (a == 0){add_input_array("",config.in02cmd0);} }
		if (actst == 1) { msg += " " + config.in02i1; if (a == 0){add_input_array("",config.in02cmd1);} }
	}
}


if (config.in04i == 1){
	int actst = digitalRead(4);
	if (( actst != in04GPIO_lastState ) || (a == 1)){
		in04GPIO_lastState = actst;  
		msg +="\n"+ config.in04name;
		if (actst == 0) { msg += " " + config.in04i0; if (a == 0){add_input_array("",config.in04cmd0);} }
		if (actst == 1) { msg += " " + config.in04i1; if (a == 0){add_input_array("",config.in04cmd1);} }
	}
}


if (config.in05i == 1){
	int actst = digitalRead(5);
	if (( actst != in05GPIO_lastState ) || (a == 1)){
		in05GPIO_lastState = actst;  
		msg +="\n"+ config.in05name;
		if (actst == 0) { msg += " " + config.in05i0; if (a == 0){add_input_array("",config.in05cmd0);} }
		if (actst == 1) { msg += " " + config.in05i1; if (a == 0){add_input_array("",config.in05cmd1);} }
	}
}


if (config.in12i == 1){
	int actst = digitalRead(12);
	if (( actst != in12GPIO_lastState ) || (a == 1)){
		in12GPIO_lastState = actst;  
		msg +="\n"+ config.in12name;
		if (actst == 0) { msg += " " + config.in12i0; if (a == 0){add_input_array("",config.in12cmd0);} }
		if (actst == 1) { msg += " " + config.in12i1; if (a == 0){add_input_array("",config.in12cmd1);} }
	}
}

if (config.in13i == 1){
	int actst = digitalRead(13);
	if (( actst != in13GPIO_lastState ) || (a == 1)){
		in13GPIO_lastState = actst;  
		msg +="\n"+ config.in13name;
		if (actst == 0) { msg += " " + config.in13i0; if (a == 0){add_input_array("",config.in13cmd0);} }
		if (actst == 1) { msg += " " + config.in13i1; if (a == 0){add_input_array("",config.in13cmd1);} }
	}
}

if (config.in14i == 1){
	int actst = digitalRead(14);
	if (( actst != in14GPIO_lastState ) || (a == 1)){
		in14GPIO_lastState = actst;  
		msg +="\n"+ config.in14name;
		if (actst == 0) { msg += " " + config.in14i0; if (a == 0){add_input_array("",config.in14cmd0);} }
		if (actst == 1) { msg += " " + config.in14i1; if (a == 0){add_input_array("",config.in14cmd1);} }
	}
}

if (config.in15i == 1){
	int actst = digitalRead(15);
	if (( actst != in15GPIO_lastState ) || (a == 1)){
		in15GPIO_lastState = actst;  
		msg +="\n"+ config.in15name;
		if (actst == 0) { msg += " " + config.in15i0; if (a == 0){add_input_array("",config.in15cmd0);} }
		if (actst == 1) { msg += " " + config.in15i1; if (a == 0){add_input_array("",config.in15cmd1);} }
	}
}







	
	if (a == 1){msg += "\nДата-время: "+ String(YYYYMMDD)+" "+String6(HHMMSS);}
	
	msg.replace("\n\n","\n");
	msg = msg.substring(1);
	// конец непонятной хуйни, которая работает


	if (msg != "" && a == 0){saveAset();
	
					Serialprint(msg);

	}


	return msg;
}



// --- ds18b20 ---------------------------------------------------------
/*  void printAddress(DeviceAddress deviceAddress){
	String da = "";
	for (uint8_t i = 0; i < 8; i++){
		// zero pad the address if necessary
		if (deviceAddress[i] < 16) da += "0";
		//Serialprint(deviceAddress[i], HEX);
		da += String(deviceAddress[i], HEX);
	}
	Serialprint(da); 
}  */


//---------------------------------------------------------
//format bytes
String formatBytes(size_t bytes){
	if (bytes < 1024){
		return String(bytes) + "B";
	} else if (bytes < (1024 * 1024)){
		return String(bytes / 1024.0) + "KB";
	} else if (bytes < (1024 * 1024 * 1024)){
		return String(bytes / 1024.0 / 1024.0) + "MB";
	} else{
		return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
	}
}


//---------------------------------------------------------
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
	Serial.printf("Listing directory: %s\r\n", dirname);

	File root = fs.open(dirname);
	if(!root){
		Serial.println("- failed to open directory");
		return;
	}
	if(!root.isDirectory()){
		Serial.println(" - not a directory");
		return;
	}

	File file = root.openNextFile();
	while(file){
		if(file.isDirectory()){
			Serial.print("  DIR : ");
			Serial.println(file.name());
			if(levels){
				listDir(fs, file.name(), levels -1);
			}
			} else{
			Serial.print("  FILE: ");
			Serial.print(file.name());
			Serial.print("\tSIZE: ");
			Serial.println(file.size());
		}
		file = root.openNextFile();
	}
}

//---------------------------------------------------------
void setup(){
	
	Serial.begin(921600);
	//Serial.begin(115200);
	
	//Serial2.begin(9600, SERIAL_8N1, 17, 16);

	Serial.println("init..." + filecfg);
	Serialprint("init..." + filecfg);
	
	if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
		Serial.println("SPIFFS Mount Failed");
		//return;
	}
	//listDir(SPIFFS, "/", 0);
	

	//SerialBT.begin(); //Bluetooth device name


// ===================================
//          исправить
// ===================================
	//pinMode(15, OUTPUT);
	//digitalWrite(15, LOW);
	//mySwitch.enableTransmit(15);
//pinMode(5, INPUT_PULLUP);
// mySwitch.enableReceive(14);	
// ===================================

	LoadConfigSDorSPIFFS();
	
	Serial.println("bot name = " + String(config.botname));
	Serialprintln("bot name = " + String(config.botname));
	Serial.println("debug_to_serial = " + String(debug_to_serial));
	Serialprintln("debug_to_serial = " + String(debug_to_serial));
	
	
	//Wire.begin(i2c_pin_1, i2c_pin_2);
	OLED display(i2c_pin_1, i2c_pin_2, 0x3c);

	display.begin();
	display.clear();
	display.print("#Start...#", 0, 0);

	//WiFi.mode(WIFI_STA);
	//WiFi.disconnect();
	//delay(3000);
	//WiFi.mode(WIFI_STA);
	//delay(3000);
	//Serialprint(String(config.ssid) + "/" + String(config.pass));
		

	//пример String txt = "192.168.1.1";
	String txt = config.ip;
	int i = 0, c = 0;
	do{c++;	} 	while ((i = txt.indexOf('.', ++i)) > 0);	
	
	
	uint8_t rawData[c]; 
	i = 0; 
	c = 0; 
	int ix = 0;
	
	String ts;
	do{ix = txt.indexOf('.', i + 1); ts = txt.substring(i, ix);    rawData[c] = (uint8_t)ts.toInt();    c++;} 	while ((i = txt.indexOf('.', ++i) + 1) > 0);	IPAddress ip(rawData);

	txt = config.gateway; i = 0; c = 0; ix = 0;
	do{ix = txt.indexOf('.', i + 1); ts = txt.substring(i, ix);    rawData[c] = (uint8_t)ts.toInt();    c++;} 	while ((i = txt.indexOf('.', ++i) + 1) > 0);	IPAddress gateway(rawData);

	txt = config.subnet; i = 0; c = 0; ix = 0;
	do{ix = txt.indexOf('.', i + 1); ts = txt.substring(i, ix);    rawData[c] = (uint8_t)ts.toInt();    c++;} 	while ((i = txt.indexOf('.', ++i) + 1) > 0);	IPAddress subnet(rawData);

	//WiFi.config(ip, gateway, subnet, gateway);
	Serialprint(String(config.ip) + "/" + String(config.subnet) + "/" + String(config.gateway));
	WiFi.begin(config.ssid, config.pass);
	WiFi.mode(WIFI_STA);


	int count = 0;
	while (WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.print(".");
		count++;
		if (count > 20){
			Serialprint("ERR: WiFi.status() != WL_CONNECTED");
			savelog();
			AP = 1;
			break;
		}
	}

	//print_lcd(0,0,"setup-2");
	//connect_();
	if (AP == 1){
		IP = "192.168.4.1";
		//WiFi.mode(WIFI_STA);
			WiFi.disconnect();
			delay(1000);
			Serialprint("\nup AP");
		WiFi.mode(WIFI_AP);
		//WiFi.softAP("minion");
		//WiFi.disconnect();
		IP = WiFi.softAPIP().toString();
		Serial.println(IP);
	}else{
		WiFi.config(ip, gateway, subnet, gateway);
		delay(1000);
		if (IP == ""){IP = WiFi.localIP().toString();}
		ip4 = String(IP);
		ip4.replace(config.ip123_,"");
		m_prefix = "/m_"+ip4+""; 
		
	}
	
	Serialprint("WiFi ok");
	mac = String(WiFi.macAddress());
	Serialprint("mac: "+mac);
	Serialprint("IP address: "+IP); 

	server.on ( "/", 			handle_ROOT );
	server.on ( "/input_web", 	handle_input_web );
	server.on ( "/input_svz", 	handle_input_svz );
	server.on ( "/input", 		handle_input_post );
	server.on ( "/restart", 	handle_restart );
	server.on ( "/cfg", 		handle_cfg );
	server.on ( "/a", 			handle_a_status );
	server.on ( "/t", 			handle_t );
	
	server.onNotFound ( NotFound );
	server.on("/u", HTTP_GET, [](){server.sendHeader("Connection", "close");server.send(200, "text/html", serverIndex);	});

server.on("/update", HTTP_POST, [](){
	
//	display.clear();	display.print("#UPDATE#", 5, 0);
	
	server.sendHeader("Connection", "close");
	server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
	WiFi.disconnect();	delay(2000);	ESP.restart();
}, []()
	{HTTPUpload& upload = server.upload();
	if (upload.status == UPLOAD_FILE_START){
		Serial.printf("Update: %s\n", upload.filename.c_str());
		
		
		
		if (!Update.begin(UPDATE_SIZE_UNKNOWN)){//start with max available size
			Update.printError(Serial);
		}
		} else if (upload.status == UPLOAD_FILE_WRITE){
		/* flashing firmware to ESP*/
			if (Update.write(upload.buf, upload.currentSize) != upload.currentSize){
				Update.printError(Serial);
			}
		} else if (upload.status == UPLOAD_FILE_END){
			if (Update.end(true)){//true to set the size to the current progress
				Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
			} else{
				Update.printError(Serial);
			}
		}
	});

server.begin();
Serialprint ( "HTTP server started" );



    aserver.on("/input", HTTP_POST, 
	
 	[](AsyncWebServerRequest *request)
    {
/* 		Serialprintln("1----------------------------------");
		int i;
		int params = request->params();
		for(i=0;i<params;i++){
			AsyncWebParameter* p = request->getParam(i);
			if(p->isFile()){
				Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
			} else if(p->isPost()){
				Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
			} else {
				Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
			}
		}
		request->send(200, "text/plain", "end"); 
*/
    }, 
	
    [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final)
    {
/*         Serialprintln("2---------------------------");
		request->send(200, "text/plain", "end"); */
    },
	
	[](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
	{
		
/* 	    Serialprintln("3-----------------------------");
        Serial.println(String("data=") + (char*)data);
 */		
/* 		int i;
		int params = request->params();
		for(i=0;i<params;i++){
			AsyncWebParameter* p = request->getParam(i);
			if(p->isFile()){
				Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
			} else if(p->isPost()){
				Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
			} else {
				Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
			}
		} */
		
		
		
/* 		String arg = "chat_id";
        String value;
        if (request->hasParam(arg)) {
            value = request->getParam(arg)->value();
        } else {
            value = "No value";
        }
		Serial.println("arg: "+arg+"=" + value); */
		
/* 	if (request->contentLength()){
      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
    } */
		
/* 	int headers = request->headers();
    int i;
    for(i=0;i<headers;i++){
      AsyncWebHeader* h = request->getHeader(i);
      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
    } */
	
	String chat_id;
	String bot_ip;
	String minion_name;
	String sek;
	
	if (request->hasParam("chat_id")) 	{chat_id 		= request->getParam("chat_id")->value();}
	if (request->hasParam("bot_ip")) 	{bot_ip 		= request->getParam("bot_ip")->value();}
	if (request->hasParam("minion")) 	{minion_name 	= request->getParam("minion")->value();}
	if (request->hasParam("sek")) 		{sek 			= request->getParam("sek")->value();}
	String msg = String((char*)data);
	
	request->send(200,"text/plain","OK");
	
	if (msg == ""){return;}
	input_post(chat_id,  msg,  bot_ip,  minion_name,  sek);
		
    });
	

    aserver.on("/input_svz", HTTP_GET, 
	
 	[](AsyncWebServerRequest *request)
    {
	
/*  		int i;
		int params = request->params();
		for(i=0;i<params;i++){
			AsyncWebParameter* p = request->getParam(i);
			if(p->isFile()){
				Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
			} else if(p->isPost()){
				Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
			} else {
				Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
			}
		}  */
		
	
	String arg;
	String value;
	//String chat_id 		= request->getParam("chat_id")->value();
	arg = "chat_id"; if (request->hasParam(arg)) {value = request->getParam(arg)->value();} else {value = "No value";Serial.println("arg: "+arg+"=" + value);}
 	String chat_id 		= value;

	//String msg 			= request->getParam("msg")->value();
	arg = "msg"; if (request->hasParam(arg)) {value = request->getParam(arg)->value();} else {value = "No value";Serial.println("arg: "+arg+"=" + value);}
 	String msg 		= value;
	
	
	request->send(200,"text/plain","OK");

	Serialprint("-a-input_svz-:["+chat_id+"]["+msg+"]");
	if (msg == ""){return;}
	add_input_array(chat_id, msg);
	
		
    });
	
	
	
	
	
	
	
	
	
	
	
	aserver.on("/input2", HTTP_POST, 
	
 	[](AsyncWebServerRequest *request)
    {

    }, 
	
    [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final)
    {

    },
	
	[](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
	{

        Serial.println(String("data=") + (char*)data);
//		String msg = String((char*)data);

 		int i;
		int params = request->params();
		for(i=0;i<params;i++){
			AsyncWebParameter* p = request->getParam(i);
			if(p->isFile()){
				Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
			} else if(p->isPost()){
				Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
			} else {
				Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
			}
		} 
	
 	if (request->contentLength()){
      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
    } 
		
 	int headers = request->headers();
    //int i;
    for(i=0;i<headers;i++){
      AsyncWebHeader* h = request->getHeader(i);
      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
    } 

	
	request->send(200);
	
		
    });
	
	
	
	

	aserver.onNotFound(notFound);
    aserver.begin();

//print_lcd(0,0,"setup-3");

			
ArduinoOTA
	.onStart([](){
		
		mySwitch.disableReceive();
		
	String type;
	if (ArduinoOTA.getCommand() == U_FLASH)
		type = "sketch";
	else // U_SPIFFS
		type = "filesystem";
		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
	Serial.println("Start updating " + type);
 
	  	//display.clear();
	print_lcd(0,0,"OTA             ");
	print_lcd(1,0,"Updating " + type);
	print_lcd(2,0,"                ");
	print_lcd(3,0,"                ");
	print_lcd(4,0,"                ");
	print_lcd(5,0,"                ");
	})
.onEnd([](){
Serial.println("\nEnd");
})
.onProgress([](unsigned int progress, unsigned int total){
//Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	  //print_lcd(1,0,"Progress " + String(progress / (total / 100))+" %");
})
.onError([](ota_error_t error){
Serial.printf("Error[%u]: ", error);
if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
else if (error == OTA_END_ERROR) Serial.println("End Failed");
});
	
	ArduinoOTA.begin();  





	setup_configTime();

	




	if (config.use_RF_PULT == 1){mySwitch.enableReceive(config.GPIO_RF_RECIVER);}

	//if (config.F_DHT == 1){dht.setup(5, DHTesp::DHT11);}
	
	



	if (config.F_DS18B20 == 1){
		
		DS18B20.begin(); 
	
// locate devices on the bus
Serialprint("Locating devices...");
Serialprint("Found ");
Serial.print(DS18B20.getDeviceCount(), DEC);
Serialprint(String(DS18B20.getDeviceCount()));
Serialprintln(" devices.");

// report parasite power requirements
Serialprint("Parasite power is: ");
if (DS18B20.isParasitePowerMode()) Serialprintln("ON");
else Serialprintln("OFF");

// Search for devices on the bus and assign based on an index. Ideally,
// you would do this to initially discover addresses on the bus and then
// use those addresses and manually assign them (see above) once you know
// the devices on your bus (and assuming they don't change).
//
// method 1: by index
if (!DS18B20.getAddress(Thermometer1, 0)) Serialprintln("Unable to find address for Device 0");
if (!DS18B20.getAddress(Thermometer2, 1)) Serialprintln("Unable to find address for Device 1");
if (!DS18B20.getAddress(Thermometer3, 2)) Serialprintln("Unable to find address for Device 1");

// method 2: search()
// search() looks for the next device. Returns 1 if a new address has been
// returned. A zero might mean that the bus is shorted, there are no devices,
// or you have already retrieved all of them. It might be a good idea to
// check the CRC to make sure you didn't get garbage. The order is
// deterministic. You will always get the same devices in the same order
//
// Must be called before search()
//oneWire.reset_search();
// assigns the first address found to Thermometer1
//if (!oneWire.search(Thermometer1)) Serial.println("Unable to find address for Thermometer1");
// assigns the seconds address found to Thermometer2
//if (!oneWire.search(Thermometer2)) Serial.println("Unable to find address for Thermometer2");

// show the addresses we found on the bus
//Serialprint("Device 0 Address: ");
//printAddress(Thermometer1);
//Serialprintln();

//Serialprint("Device 1 Address: ");
//printAddress(Thermometer2);
//Serial.println();

// set the resolution to 9 bit per device
DS18B20.setResolution(Thermometer1, TEMPERATURE_PRECISION);
DS18B20.setResolution(Thermometer2, TEMPERATURE_PRECISION);
DS18B20.setResolution(Thermometer3, TEMPERATURE_PRECISION);

//Serialprint("Device 0 Resolution: ");
//Serial.print(DS18B20.getResolution(Thermometer1), DEC);
//Serial.println();

//Serialprint("Device 1 Resolution: ");
//Serial.print(DS18B20.getResolution(Thermometer2), DEC);
//Serial.println();


		Serialprint("Requesting temperatures...");
		DS18B20.requestTemperatures();
		//Serialprintln("DONE");

		// print the device information
		//printData(Thermometer1);
		//printData(Thermometer2);
		tempC1 = DS18B20.getTempC(Thermometer1);
		tempC2 = DS18B20.getTempC(Thermometer2);
		tempC3 = DS18B20.getTempC(Thermometer3);
		Serialprint("-setup-t1 C= "+String(tempC1)+" t2 C= "+String(tempC2)+" t3 C= "+String(tempC3));
		
		
	}



	tft.init();
	tft.setRotation(2);//3
	tft.fillScreen(TFT_BLACK);


	print_lcd(0,0,"setup-end, start   ");
	display.clear();
	print_lcd(0,0,"start...   ");
	print_lcd(3,0,IP);
	
	
	
	
	
	
	if (AP == 0){
		add_out_array(config.admin_chat_id,StartMsg());
		status(0);
	//add_input_array(config.admin_chat_id,"/t");
	}  
	
	

/*   // Fill screen with grey so we can see the effect of printing with and without 
// a background colour defined
tft.fillScreen(TFT_GREY);

// Set "cursor" at top left corner of display (0,0) and select font 2
// (cursor will move to next line automatically during printing with 'tft.println'
//  or stay on the line is there is room for the text with tft.print)
tft.setCursor(0, 0, 0);
// Set the font colour to be white with a black background, set text size multiplier to 1
tft.setTextColor(TFT_WHITE,TFT_BLACK);  
tft.setTextSize(2);
// We can now plot text on screen using the "print" class
tft.println("Hello World! Жопа");

// Set the font colour to be yellow with no background, set to font 7
tft.setTextColor(TFT_YELLOW); 
tft.setTextFont(7);
tft.setTextSize(0);
tft.println(1234.56);

// Set the font colour to be red with black background, set to font 4
tft.setTextColor(TFT_RED,TFT_BLACK);    
tft.setTextFont(4);
//tft.println(3735928559L, HEX); // Should print DEADBEEF

// Set the font colour to be green with black background, set to font 4
tft.setTextColor(TFT_GREEN,TFT_BLACK);
tft.setTextFont(4);
tft.println("Groop");
tft.println("I implore thee,");

// Change to font 2
tft.setTextFont(2);
tft.println("my foonting turlingdromes.");
tft.println("And hooptiously drangle me");
tft.println("with crinkly bindlewurdles,");
// This next line is deliberately made too long for the display width to test
// automatic text wrapping onto the next line
tft.println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");

// Test some print formatting functions
float fnumber = 123.45;
// Set the font colour to be blue with no background, set to font 4
tft.setTextColor(TFT_BLUE);    
tft.setTextFont(4);
tft.print("Float = "); 
tft.println(fnumber);           // Print floating point number
tft.print("Binary = "); 
tft.println((int)fnumber, BIN); // Print as integer value in binary
tft.print("Hexadecimal = "); 
tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal */


/* 
   // Now set up two tasks to run independently.
  xTaskCreatePinnedToCore(
    loop1
    ,  "loop1"   // A name just for humans
    ,  10240  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  0); 

  xTaskCreatePinnedToCore(
    loop2
    ,  "loop2"
    ,  10240  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  1);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.

 */
}
 
 
void loop1(void *pvParameters){(void) pvParameters;
  for (;;){
	  
	
		  
	  
	print_lcd(10, 0, String(xPortGetCoreID())+"="+String(millis()/100)); 
	vTaskDelay(100); 
	//vTaskDelay(100); 
	
/*     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability */
	yield();
  }
}


void loop2(void *pvParameters){(void) pvParameters;
  for (;;){
	  
	      
		  
	print_lcd(11, 0, String(xPortGetCoreID())+"="+String(millis()/100)); 
	vTaskDelay(100);  
	//vTaskDelay(100);  
	
/*     // read the input on analog pin A3:
    int sensorValueA3 = analogRead(A3);
    // print out the value you read:
    Serial.println(sensorValueA3);
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability */
	yield();
  }
}
 