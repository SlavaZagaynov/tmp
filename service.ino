
int Countsubstring(String s){
	
	s = s+",";
	String _s = s;
	_s.replace(",", "");
    int count = (s.length() - _s.length());
    return count;
}

int get_np_T(String T, String v, int r){
	
	int fp = T.indexOf(v);
	String _t = T.substring(0,fp+1);
	int np = Countsubstring(_t);
	return np/r+1;
}

String get_v(String T, int np, int r, int is){
	
	int np_ = (np-1)*r+is;
	String ts = T;
	int ix;
	do{ix = ts.indexOf(","); 
		ts = ts.substring(ix+1);    
		--np_;
	}while (np_ > 0);	
	String v = ts.substring(0,ts.indexOf(",")); 
/* 	int i = np_; 
	int ix = np_;
	String ts;
	do{ix = T.indexOf(',', i + 1); 
		ts = T.substring(i, ix);    
		v = v + ts; 		
	}while ((i = T.indexOf(',', ++i) + 1) > 0);	 */
	return v;
}




//---------------------------------------------------------
String trim(String txt){
	
	txt.replace("  "," ");
	txt.replace(" \n","\n");
	txt.replace("\n ","\n");
	txt.replace("\n\n","\n");
	
	txt.replace("\r","");
	txt.replace("\0","");
	
	//txt.replace("\n","; ");

	int length = txt.length();	if (txt.substring(length-1) == "\n"){txt = txt.substring(0,length-1);}
		length = txt.length();	if (txt.substring(length-1) == " "){txt = txt.substring(0,length-1);}
			
	return txt;
}



//---------------------------------------------------------
void print_lcd(int str, int kol, String txt){
	
	if (config.noDisplay == 1){return;}  
	if (txt == ""){return;}

	String tmp_s;
	char tmp_char[17]; 
	tmp_s = txt+"                ";    strlcpy(tmp_char, tmp_s.c_str(), 17);
	//tmp_s = txt+"                ";    strlcpy(tmp_char, tmp_s.c_str(), tmp_s.length()+1);
	
		

	//display.print(tmp_char, str, kol);

	//taskENTER_CRITICAL(&mmux);
	//display.print(tmp_char, str, kol);
	//taskEXIT_CRITICAL(&mmux);
	
	
	//return;
	
	//tft.setCursor(str*12, kol*8, 0);
	// Set the font colour to be white with a black background, set text size multiplier to 1
	tft.setTextColor(TFT_WHITE,TFT_BLACK); 
	//tft.setTextColor(TFT_YELLOW); 
	// tft.setTextFont(2);
	// tft.setTextSize(2);
	// tft.print(txt);
	int s = str*18;
	int k = kol*8;
	
	tmp_s = txt+"                  ";    strlcpy(tmp_char, tmp_s.c_str(), 17);
	tft.drawString(tmp_s, k, s, 2);
	//tft.drawString(String(txt)+"-"+String(str)+"-"+String(kol), str*12+50, kol*8+20, 2);
	
}


//---------------------------------------------------------
void Serialprint(String txt){
	
	if (debug_to_serial == 0 && config.log == 0){return;}

	txt.replace("\n"," ");
	txt.replace("  "," ");
	//txt = trim(txt);
	
	// txt.replace("[<","[");
	// txt.replace(">]","]");
	// txt.replace("<br>"," ");
	
	// txt.replace(" ","^"); // отладка - видеть пробелы
	txt = String6(HHMMSS)+" "+ txt;
	if (debug_to_serial == 1){
		if (debug_to_serial_mask != ""){
			if (txt.indexOf(debug_to_serial_mask) >=0 ){
				Serial.println(txt);
			}	
		}else{
			Serial.println(txt);
		}
	}
	
	if (config.log == 1){
		txtlog += txt + "<br>\n";
	}
	
}

//---------------------------------------------------------
void Serialprintln(String txt){
	Serialprint(txt);
	}

//---------------------------------------------------------
void kill_tcp(){
	
	//while (tcp_tw_pcbs){tcp_abort(tcp_tw_pcbs);}
	
}

//---------------------------------------------------------
void connect_(){
	
	if (AP == 1){
		if (millis() > 1800000/3){
			ESP.restart();
		} // рестарт каждые 30/3 минут
		return;
	} 
	
	return;
	
	//print_lcd(4, 0, "WIFI");
	uint8_t count = 0;

	while (WiFi.status() != WL_CONNECTED){
		print_lcd(4, 0, "WIFI lost");
		delay(2000);
		count++;
		
		if (count > 5){
			Serialprint("ERR: WIFI LOST - restart");
			savelog();
			delay(5000);
			ESP.restart();
		}
		
		
		print_lcd(4, 0, "WIFI reconnect");
		
		WiFi.mode(WIFI_STA);
		WiFi.disconnect();
		delay(1000);
		WiFi.mode(WIFI_STA);

		//пример String txt = "192.168.1.1";
		String txt = config.ip;
		int i = 0, 
		c = 0;
		do{c++;} while ((i = txt.indexOf('.', ++i)) > 0);
		uint8_t rawData[c]; 
		
		i = 0; 		c = 0; 		int ix = 0;		String ts;
		do{			ix = txt.indexOf('.', i + 1); 			ts = txt.substring(i, ix);			rawData[c] = (uint8_t)ts.toInt();			c++;						} 
			while ((i = txt.indexOf('.', ++i) + 1) > 0);		IPAddress ip(rawData);
	
		txt = config.gateway; 		i = 0; 		c = 0; 		ix = 0;		do{			ix = txt.indexOf('.', i + 1); 			ts = txt.substring(i, ix);			rawData[c] = (uint8_t)ts.toInt();			c++;			} 
			while ((i = txt.indexOf('.', ++i) + 1) > 0);		IPAddress gateway(rawData);

		txt = config.subnet; 		i = 0; 		c = 0; 		ix = 0;		do{			ix = txt.indexOf('.', i + 1); 			ts = txt.substring(i, ix);			rawData[c] = (uint8_t)ts.toInt();			c++;			} 
			while ((i = txt.indexOf('.', ++i) + 1) > 0);		IPAddress subnet(rawData);

		//WiFi.config(ip, gateway, subnet, gateway);
		WiFi.begin(config.ssid, config.pass);
		WiFi.config(ip, gateway, subnet, gateway);


		//delay(2000);
		print_lcd(4, 0, "                ");
	}
	//print_lcd(4, 0, "                ");
}




//---------------------------------------------------------
void Slushat_Port_(){ //nu
	
	String text = "";    
	if (Serial.available()){
		while (Serial.available()){
			text += String(char(Serial.read()));
		}
		Serial.println(text);	
	} 
	
}

//---------------------------------------------------------
void Slushat_Port(){
	
	String text = "";    
	String line1 = "";
	String line2 = "";

 	if (Serial.available()){
		while (Serial.available()){
			line1 += String(char(Serial.read()));
		}
		line1.replace("\0","");
		line1.replace("\n","");
		line1.replace("\r","");
		line1.replace("  "," ");
		
		//print_lcd(2, 0, line1);
		//line2 = "<txt:"+config.botname+" услышал: "+line1+">\r\n";
		//Serial.print(line2);
		line2 = " услышал из Serial: "+line1;
		//add_out_array("", line2);
		text = line1;
		
		
		//print_lcd(0,0,line1);
		
	} 	 
	
/* 	if (Serial2.available()){
		while (Serial2.available()){
			line1 += String(char(Serial2.read()));
		}
		line1.replace("\0","");
		line1.replace("\n","");
		line1.replace("\r","");
		line1.replace("  "," ");
		
		//print_lcd(2, 0, line1);
		//line2 = "<txt:"+config.botname+" услышал: "+line1+">\r\n";
		
		line2 = " услышал из Serial2: "+line1;
		//add_out_array("", line2);
		text = line2;
		//Serial.print(text);
		
		//print_lcd(0,0,line1);
		
	} 	 */
	
	
	
	
	
	
/*  	if (text == ""){
		if (SerialBT.available()){
			while (SerialBT.available()){
				line1 += String(char(SerialBT.read()));
			}
			line1.replace("\0","");
			line1.replace("\n","");
			line1.replace("\r","");
			line1.replace("  "," ");
		
			//print_lcd(2, 0, line1);
			//line2 = "<txt:"+config.botname+" услышал: "+line1+">\r\n";
			//Serial.print(line2);
			line2 = config.botname+" услышал: "+line1;
			add_out_array(chat_id, line2);
			text = line1;
		}
	}  */


if (text.indexOf("debug_to_serial_mask=") == 0){
	text.replace("debug_to_serial_mask=","");
	debug_to_serial_mask = text;
	return;
}



	if (text == ""){return;}

	if (text.length() > 100){
		text == "ERR long txt";
	}
	
	text = rus(text);

	Serialprint("<-Serial:["+text+"]");
	
/* 	for (byte j = 0; j < 10; j++){
		if (String(in_msg_array[j]) == ""){
			int ln2 = text.length() + 1;
			char ss2[ln2];
			text.toCharArray(ss2, ln2);
			memcpy(in_msg_array[j], ss2, ln2);
			memcpy(in_user_array[j], "", 1);
			break;
		}
	} */
	
	add_input_array("",text,"Serial port");
	
	return;
} 




//---------------------------------------------------------
String print2digits(int number){

	String x; 
	if (number >= 0 && number < 10){x = "0" + String(number);} else{x = String(number);}
	return x;
	
}
//---------------------------------------------------------

//---------------------------------------------------------
static const char* bin2tristate(const char* bin);
static char * dec2binWzerofill(uint32_t Dec, unsigned int bitLength);

void output(uint32_t decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol){

const char* b = dec2binWzerofill(decimal, length);
Serialprint("Decimal: ");
Serialprint(String(decimal));
Serialprint(" (");
Serialprint(String( length ));
Serialprint("Bit) Binary: ");
Serialprint( String(b) );
Serialprint(" Tri-State: ");
Serialprint( String(bin2tristate(b)) );
Serialprint(" PulseLength: ");
Serialprint(String(delay));
Serialprint(" microseconds");
Serialprint(" Protocol: ");
Serialprint(String(protocol));

//Serial.print("Raw data: ");
//for (unsigned int i=0; i<= length*2; i++){
//  Serial.print(raw[i]);
//  Serial.print(",");
// }
//Serial.println();
//Serial.println();
}
//---------------------------------------------------------
static const char* bin2tristate(const char* bin){
	
	static char returnValue[50];
	int pos = 0;
	int pos2 = 0;
	while (bin[pos] != '\0' && bin[pos + 1] != '\0'){
		if (bin[pos] == '0' && bin[pos + 1] == '0'){returnValue[pos2] = '0';
		} else if (bin[pos] == '1' && bin[pos + 1] == '1'){returnValue[pos2] = '1';
		} else if (bin[pos] == '0' && bin[pos + 1] == '1'){returnValue[pos2] = 'F';
		} else{return "not applicable";}
	pos = pos + 2;
	pos2++;
	}
	returnValue[pos2] = '\0';
	return returnValue;
}

//---------------------------------------------------------
static char * dec2binWzerofill(uint32_t Dec, unsigned int bitLength){
	
	static char bin[64];
	unsigned int i = 0;

	while (Dec > 0){bin[32 + i++] = ((Dec & 1) > 0) ? '1' : '0';    Dec = Dec >> 1;}

	for (unsigned int j = 0; j < bitLength; j++){if (j >= bitLength - i){bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
	} else{bin[j] = '0';}
	}
	bin[bitLength] = '\0';

	return bin;
}




//---------------------------------------------------------
String StartMsg(){
	
	String _txt = "реСтарт\n(с) @SlavaZagaynov\nv." + String(versia) + "\nip: " + IP + " mac: " + String(WiFi.macAddress());
	_txt += "\n/start - go";
	return _txt;
	
}
		
//---------------------------------------------------------
String list_LineCmd(){
	
	String _txt = "/команды:\n";
	//_txt += (String(config.line01) + " - " + String(config.line_cmd01) + "\n");     
	if (config.line01 != ""){_txt +=  m_prefix+"_/" + (String(config.line01) + "\n");}
	if (config.line02 != ""){_txt +=  m_prefix+"_/" + (String(config.line02) + "\n");}     
	if (config.line03 != ""){_txt +=  m_prefix+"_/" + (String(config.line03) + "\n");}     
	if (config.line04 != ""){_txt +=  m_prefix+"_/" + (String(config.line04) + "\n");}     
	if (config.line05 != ""){_txt +=  m_prefix+"_/" + (String(config.line05) + "\n");}     
	if (config.line06 != ""){_txt +=  m_prefix+"_/" + (String(config.line06) + "\n");}     
	if (config.line07 != ""){_txt +=  m_prefix+"_/" + (String(config.line07) + "\n");}     
	if (config.line08 != ""){_txt +=  m_prefix+"_/" + (String(config.line08) + "\n");}     
	if (config.line09 != ""){_txt +=  m_prefix+"_/" + (String(config.line09) + "\n");}     
	_txt.replace("\n\n","\n");
	_txt.replace("//","/");
	_txt.replace("_/","_");
	return _txt;

}

//---------------------------------------------------------
String Keyboard(){
	
	String kbdJson = "[\
[\"key01\",\"key02\",\"key03\"],\
[\"key04\",\"key05\",\"key06\"],\
[\"key07\",\"key08\",\"key09\"],\
[\"Домовой\",\"Миньоны\",\"Рапорт\"]]";
  //String kbdJson = "[[\"key01\",\"key02\"],[\"key03\",\"key04\"],[\"key05\",\"key06\"],[\"key07\",\"key08\"],[\"key09\",\"\"],[\"Миньоны\",\"Рапорт\"]]";
	
	kbdJson.replace("key01", config.key01);
	kbdJson.replace("key02", config.key02);
	kbdJson.replace("key03", config.key03);
	kbdJson.replace("key04", config.key04);
	kbdJson.replace("key05", config.key05);
	kbdJson.replace("key06", config.key06);
	kbdJson.replace("key07", config.key07);
	kbdJson.replace("key08", config.key08);
	kbdJson.replace("key09", config.key09);
	return kbdJson;
	
}


//---------------------------------------------------------
String String4(int a){
	
	String _a = "000"+String(a); 
	_a = _a.substring(_a.length()-4);
	return _a;
	
}

//---------------------------------------------------------
String String4(char* a){
	
	String _a = "000"+String(a); 
	_a = _a.substring(_a.length()-4);
	return _a;
	
}

//---------------------------------------------------------
String String6(int a){
	
	String _a = "00000"+String(a); 
	_a = _a.substring(_a.length()-6);
	return _a;
	
}



//---------------------------------------------------------
int saveAset(){

	//if (file_a_status_loaded == 0) {return 0;}

	Serialprint("запись /a_status cfg");
	File myFile_a_status = SPIFFS.open(file_a_status.c_str(), "w");

	if (myFile_a_status){
		
	counter_rw++;
	String txt = "{\n\
\"counter_rw\":" + String(counter_rw) + ",\n\
\"YYYYMMDD-HHMMSS\":" + String(YYYYMMDD_HHMMSS) + ",\n\
\"OHRANA\":" + String(OHRANA) + ",\n";

 	for (byte j = 0; j < 10; j++){
txt += "\
\"t"+String(j)+"date\":" + "\"" + String(timer_date_array[j]) + "\"" + ",\
\"t"+String(j)+"time\":" + "\"" + String(timer_time_array[j]) + "\"" + ",\
\"t"+String(j)+"reprat\":" + "\"" + String(timer_repeet_array[j]) + "\"" + ",\
\"t"+String(j)+"comand\":" + "\"" + String(timer_command_array[j]) + "\"" + ",\
\"t"+String(j)+"exdate\":" + "\"" + String(timer_exdate_array[j]) + "\"" + ",\
\"t"+String(j)+"extime\":" + "\"" + String(timer_extime_array[j]) + "\"" + ",\n";
} 

txt += "\
\"GPIO0\":" + String(digitalRead(0)) + ",\n\
\"GPIO2\":" + String(digitalRead(2)) + ",\n\
\"GPIO4\":" + String(digitalRead(4)) + ",\n\
\"GPIO5\":" + String(digitalRead(5)) + ",\n\
\"GPIO12\":" + String(digitalRead(12)) + ",\n\
\"GPIO13\":" + String(digitalRead(13)) + ",\n\
\"GPIO14\":" + String(digitalRead(14)) + ",\n\
\"GPIO15\":" + String(digitalRead(15)) + ",\n\
\"GPIO16\":" + String(digitalRead(16)) + "\n\
}";

	myFile_a_status.print(txt);
	//Serialprint(txt);
	myFile_a_status.close();
	//delay(50);
	} 
}


//---------------------------------------------------------
String listTimers(){

	String msg = "Таймеры:\n";
	if (String(timer_date_array[0]) != ""){msg += "1. " + String(timer_date_array[0]) + "-" + String4(timer_time_array[0]) + " " + String(timer_command_array[0]) + " " + String(timer_exdate_array[0]) + "-" + String4(timer_extime_array[0]) + "\n";}
	if (String(timer_date_array[1]) != ""){msg += "2. " + String(timer_date_array[1]) + "-" + String4(timer_time_array[1]) + " " + String(timer_command_array[1]) + " " + String(timer_exdate_array[1]) + "-" + String4(timer_extime_array[1]) + "\n";}
	if (String(timer_date_array[2]) != ""){msg += "3. " + String(timer_date_array[2]) + "-" + String4(timer_time_array[2]) + " " + String(timer_command_array[2]) + " " + String(timer_exdate_array[2]) + "-" + String4(timer_extime_array[2]) + "\n";}
	if (String(timer_date_array[3]) != ""){msg += "4. " + String(timer_date_array[3]) + "-" + String4(timer_time_array[3]) + " " + String(timer_command_array[3]) + " " + String(timer_exdate_array[3]) + "-" + String4(timer_extime_array[3]) + "\n";}
	if (String(timer_date_array[4]) != ""){msg += "5. " + String(timer_date_array[4]) + "-" + String4(timer_time_array[4]) + " " + String(timer_command_array[4]) + " " + String(timer_exdate_array[4]) + "-" + String4(timer_extime_array[4]) + "\n";}
	if (String(timer_date_array[5]) != ""){msg += "6. " + String(timer_date_array[5]) + "-" + String4(timer_time_array[5]) + " " + String(timer_command_array[5]) + " " + String(timer_exdate_array[5]) + "-" + String4(timer_extime_array[5]) + "\n";}
	if (String(timer_date_array[6]) != ""){msg += "7. " + String(timer_date_array[6]) + "-" + String4(timer_time_array[6]) + " " + String(timer_command_array[6]) + " " + String(timer_exdate_array[6]) + "-" + String4(timer_extime_array[6]) + "\n";}
	if (String(timer_date_array[7]) != ""){msg += "8. " + String(timer_date_array[7]) + "-" + String4(timer_time_array[7]) + " " + String(timer_command_array[7]) + " " + String(timer_exdate_array[7]) + "-" + String4(timer_extime_array[7]) + "\n";}
	if (String(timer_date_array[8]) != ""){msg += "9. " + String(timer_date_array[8]) + "-" + String4(timer_time_array[8]) + " " + String(timer_command_array[8]) + " " + String(timer_exdate_array[8]) + "-" + String4(timer_extime_array[8]) + "\n";}
	
	if(msg == "Таймеры:\n"){msg = msg + "не назначены.\n";}
	
	msg += String(YYYYMMDD)+"-"+String6(HHMMSS)+"\n"; 
	
	return msg;	
	
}



//---------------------------------------------------------
String list_KeyCmd(int kratko){
	
	String cmdlist = "команды:\n";
	if (kratko == 0){
		cmdlist += m_prefix+"_status - статус\n";
		cmdlist += m_prefix+"_raport - рапорт\n";
		cmdlist += m_prefix+"_commands - команды\n";
		cmdlist += m_prefix+"_restart - рестарт\n";
		cmdlist += m_prefix+"_t - таймеры\n";
	}
	
	if (config.key01 != ""){cmdlist += m_prefix+"_01 - " + config.key01 + "\n";}
	if (config.key02 != ""){cmdlist += m_prefix+"_02 - " + config.key02 + "\n";}
	if (config.key03 != ""){cmdlist += m_prefix+"_03 - " + config.key03 + "\n";}
	if (config.key04 != ""){cmdlist += m_prefix+"_04 - " + config.key04 + "\n";}
	if (config.key05 != ""){cmdlist += m_prefix+"_05 - " + config.key05 + "\n";}
	if (config.key06 != ""){cmdlist += m_prefix+"_06 - " + config.key06 + "\n";}
	if (config.key07 != ""){cmdlist += m_prefix+"_07 - " + config.key07 + "\n";}
	if (config.key08 != ""){cmdlist += m_prefix+"_08 - " + config.key08 + "\n";}
	if (config.key09 != ""){cmdlist += m_prefix+"_09 - " + config.key09 + "\n";}
	
	cmdlist.replace("\n\n", "\n");

	return cmdlist;
}

//---------------------------------------------------------
String rus(String text){
	
	return text;
	

	//	text.replace("u0400","_");
	text.replace("u0401", "Ё");
	text.replace("u0451", "ё");

	text.replace("u0410", "А");
	text.replace("u0411", "Б");
	text.replace("u0412", "В");
	text.replace("u0413", "Г");
	text.replace("u0414", "Д");
	text.replace("u0415", "Е");
	text.replace("u0416", "Ж");
	text.replace("u0417", "З");
	text.replace("u0418", "И");
	text.replace("u0419", "Й");
	text.replace("u041a", "К");
	text.replace("u041b", "Л");
	text.replace("u041c", "М");
	text.replace("u041d", "Н");
	text.replace("u041e", "О");
	text.replace("u041f", "П");

	text.replace("u0420", "Р");
	text.replace("u0421", "С");
	text.replace("u0422", "Т");
	text.replace("u0423", "У");
	text.replace("u0424", "Ф");
	text.replace("u0425", "Х");
	text.replace("u0426", "Ц");
	text.replace("u0427", "Ч");
	text.replace("u0428", "Ш");
	text.replace("u0429", "Щ");
	text.replace("u042a", "Ъ");
	text.replace("u042b", "Ы");
	text.replace("u042c", "Ь");
	text.replace("u042d", "Э");
	text.replace("u042e", "Ю");
	text.replace("u042f", "Я");

	text.replace("u0430", "а");
	text.replace("u0431", "б");
	text.replace("u0432", "в");
	text.replace("u0433", "г");
	text.replace("u0434", "д");
	text.replace("u0435", "е");
	text.replace("u0436", "ж");
	text.replace("u0437", "з");
	text.replace("u0438", "и");
	text.replace("u0439", "й");
	text.replace("u043a", "к");
	text.replace("u043b", "л");
	text.replace("u043c", "м");
	text.replace("u043d", "н");
	text.replace("u043e", "о");
	text.replace("u043f", "п");

	text.replace("u0440", "р");
	text.replace("u0441", "с");
	text.replace("u0442", "т");
	text.replace("u0443", "у");
	text.replace("u0444", "ф");
	text.replace("u0445", "х");
	text.replace("u0446", "ц");
	text.replace("u0447", "ч");
	text.replace("u0448", "ш");
	text.replace("u0449", "щ");
	text.replace("u044a", "ъ");
	text.replace("u044b", "ы");
	text.replace("u044c", "ь");
	text.replace("u044d", "э");
	text.replace("u044e", "ю");
	text.replace("u044f", "я");
	
	return text;
	
}

