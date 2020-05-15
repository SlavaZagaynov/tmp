
//---------------------------------------------------------
#include "time.h"
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600*3;
const int   daylightOffset_sec = 3600*0;
//---------------------------------------------------------

void time_h_read(){
	
	struct tm timeinfo;
	if(!getLocalTime(&timeinfo)){Serialprintln("Failed to obtain time");    return;}
	//Serial.println(&timeinfo, "%m %d %Y %H:%M:%S");
	//Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");
	
	rtc_YYYY = timeinfo.tm_year+1900;
	rtc_MM = timeinfo.tm_mon+1;
	rtc_DD = timeinfo.tm_mday;
		
	rtc_hh = timeinfo.tm_hour;
	rtc_mm = timeinfo.tm_min;
	rtc_ss = timeinfo.tm_sec;
	
	YYYYMMDD = (timeinfo.tm_year+1900)*10000+(timeinfo.tm_mon+1)*100+timeinfo.tm_mday;
	HHMMSS = timeinfo.tm_hour*10000+timeinfo.tm_min*100+timeinfo.tm_sec;
	HHMM = timeinfo.tm_hour*100+timeinfo.tm_min;
	HH = timeinfo.tm_hour*100;
	MM = timeinfo.tm_min;
	YYYYMMDD_HHMMSS = String(YYYYMMDD)+"-"+String6(HHMMSS);
	//Serialprint(YYYYMMDD_HHMMSS);
	//C:\Documents and Settings\glory\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\tools\sdk\include\newlib
	//struct tm
	//{//  int tm_sec; //  int tm_min; //  int tm_hour;  //  int tm_mday; //  int tm_mon; //  int tm_year;  //  int tm_wday; //  int tm_yday; //  int tm_isdst;
	//#ifdef __TM_GMTOFF //  long  __TM_GMTOFF; //#endif
	//#ifdef __TM_ZONE //  const char *__TM_ZONE; //#endif //};
}

//---------------------------------------------------------
void setup_configTime(){
	
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	time_h_read();
	
}

//---------------------------------------------------------
int RTCread(){
	
	return 0;
	
	tmElements_t tm;
	if (RTC.read(tm)){
		
		//rtc_YYYY = tmYearToCalendar(tm.Year);
		rtc_YYYY = tm.Year+1970;
		rtc_MM = tm.Month;
		rtc_DD = tm.Day;
		
		rtc_hh = tm.Hour;
		rtc_mm = tm.Minute;
		rtc_ss = tm.Second;

		YYYYMMDD = rtc_YYYY*10000+rtc_MM*100+rtc_DD;
		HHMMSS = rtc_hh*10000+rtc_mm*100+rtc_ss;
		HHMM = rtc_hh*100+rtc_mm;
		YYYYMMDD_HHMMSS = String(YYYYMMDD)+"-"+String6(HHMMSS);  
		return 1;		
	}
	return 0;
	
}
