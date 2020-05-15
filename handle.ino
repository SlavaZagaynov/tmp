

//---------------------------------------------------------
void savelog(){

	if (YYYYMMDD == 0){
		Serialprint("ERR: bad YYYYMMDD");
	}
	if (config.log_to_SDcard == 1){
		namelogfile = "/log" + String(YYYYMMDD) + ".txt";
		File myFile = SD.open(namelogfile.c_str(), FILE_APPEND);
		if (myFile){
			Serialprint("Запись log" + String(YYYYMMDD) + ".txt");
			myFile.print(txtlog);
			myFile.close();
		}
	}

}


//---------------------------------------------------------
void handle_restart(){
	
	server.send ( 200, "text/html", "<html>\
<head><meta http-equiv=\"refresh\" content=\"1;URL=http://"+IP+"\"/></head>\
<style>body{width:400px; padding:0px; margin:0px; background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}\
</style></html>");

		delay(1000);
		WiFi.disconnect();delay(3000);ESP.restart();delay(100000);
		
}

//---------------------------------------------------------
void input_post(String chat_id, String msg, String bot_ip, String minion_name, String sek){

	msg = trim(msg);

	// запомнить миньона
	if (minion_name != ""){
		int reg = 0;for (byte j = 0; j < 9; j++){if (String(m_ip_array[j]) == bot_ip){reg = 1;break;}}
		if (reg == 0){
			for (byte j = 0; j < 9; j++){
				if (String(m_ip_array[j]) == ""){
					int ln1_m = bot_ip.length() + 1;		
					char ss1_m[ln1_m]; 	
					bot_ip.toCharArray(ss1_m, ln1_m);				
					memcpy(m_ip_array[j], ss1_m, ln1_m);
					int ln2_m = minion_name.length() + 1; 	
					char ss2_m[ln2_m];	
					minion_name.toCharArray(ss2_m, ln2_m);				
					memcpy(m_name_array[j], ss2_m, ln2_m);
					break;
				}
			}
		}
	}
	
	// запомнить номер сообщения
	if (sek != ""){
		for (byte j = 0; j < 9; j++){
			if (String(m_ip_array[j]) == bot_ip){
				if (String(m_sek_array[j]) == sek){
					return;
				}
				int ln1_m = sek.length() + 1;		
				char ss1_m[ln1_m]; 	
				sek.toCharArray(ss1_m, ln1_m);				
				memcpy(m_sek_array[j], ss1_m, ln1_m);
				break;
			}
		}
	}
	
	if (msg == ""){return;}
	if (msg.length() > 2000){Serialprint("ERR: длина сообщения =" + String(msg.length())); 
	msg = msg.substring(0, 2000);}
	Serialprint("-input_post-["+bot_ip+"]["+minion_name+"]["+sek+"]["+chat_id+"]["+msg+"]");
	add_out_array(chat_id,msg);
	print_lcd(5,0,"<m:"+bot_ip);


}

//---------------------------------------------------------
void handle_input_post(){
		

	//server.send ( 200, "text/plain", "OK" );
	server.send ( 200, "" );

/* 	String chat_id = "";
	String msg = "";
	String minion = "";
	String minion_name = "";
	String bot_ip = "";
	String sek = ""; */

/* 	if (server.args() > 0){
		for ( uint8_t i = 0; i < server.args(); i++ ){
			if (server.argName(i) == "chat_id"){chat_id = server.arg(i);}
			if (server.argName(i) == "plain"){msg = server.arg(i);}
			if (server.argName(i) == "bot_ip"){bot_ip = server.arg(i);}
			if (server.argName(i) == "minion"){
				//minion = server.argName(i) + ":" + server.arg(i) + "\n";
				minion_name = server.arg(i);}
			if (server.argName(i) == "sek"){sek = server.arg(i);}
		}
	}else{return;} */
	
	String chat_id 		= server.arg("chat_id");
	String msg 			= server.arg("plain");
	String bot_ip 		= server.arg("bot_ip");
	String minion_name 	= server.arg("minion");
	String sek 			= server.arg("sek");
	
	
	input_post( chat_id,  msg,  bot_ip,  minion_name,  sek);
	//return;
	

} 



//---------------------------------------------------------
void handle_input_web(){

	String msg = "";
	String chat_id = "1";

	String URL = "";
	if (server.args() > 0){
		for ( uint8_t i = 0; i < server.args(); i++ ){
			//URL += "" + server.argName(i) + "=" + server.arg(i) + "&";
			if (server.argName(i) == "msg"){msg = server.arg(i);}
			if (server.argName(i) == "chat_id"){chat_id = server.arg(i);}
		}
	}


	server.send ( 200, "text/html", "<html>\
<head>\
<meta http-equiv=\"refresh\" content=\"1;URL=http://" + IP + "\" />\
</head>\
<style>\
body{width:400px; padding:0px; margin:0px; background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}\
</style>\
</html>"\
);


/*<meta name='viewport' content='width=device-width,minimum-scale=1,maximum-scale=1,initial-scale=1,user-scalable=no'/>\
<style>\
body{width:400px; padding:0px; margin:0px; background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}\
</style>\
<body>\
<table width:400px;><tr width:400px><td>\
<form>\
<input type=\"button\" value=\"<-back-\" onclick=\"location.href='http://" + IP + "'\" />\
</form>\
</td></tr></table>\
</body>\*/

	if (msg == ""){return;}
	if (msg == "01"){Serialprint("1." + config.cmd01);  msg += " " + config.key01; add_input_array(chat_id, config.cmd01);}
	if (msg == "02"){Serialprint("2." + config.cmd02);  msg += " " + config.key02; add_input_array(chat_id, config.cmd02);}
	if (msg == "03"){Serialprint("3." + config.cmd03);  msg += " " + config.key03; add_input_array(chat_id, config.cmd03);}
	if (msg == "04"){Serialprint("4." + config.cmd04);  msg += " " + config.key04; add_input_array(chat_id, config.cmd04);}
	if (msg == "05"){Serialprint("5." + config.cmd05);  msg += " " + config.key05; add_input_array(chat_id, config.cmd05);}
	if (msg == "06"){Serialprint("6." + config.cmd06);  msg += " " + config.key06; add_input_array(chat_id, config.cmd06);}
	if (msg == "07"){Serialprint("7." + config.cmd07);  msg += " " + config.key07; add_input_array(chat_id, config.cmd07);}
	if (msg == "08"){Serialprint("8." + config.cmd08);  msg += " " + config.key08; add_input_array(chat_id, config.cmd08);}

	add_out_array(chat_id, "команда: " + msg);
	Serialprintln("web команда: " + msg);
}

//---------------------------------------------------------
void handle_ROOT(){

//Serialprint("handle_ROOT start");

	String rootmsg = "";
	String userwebcmd;
	String cfg;

	if (server.args() > 0){
		for ( uint8_t i = 0; i < server.args(); i++ ){
			if (server.argName(i) == "userwebcmd"){userwebcmd = server.arg(i);}
			if (server.argName(i) == "cfg"){cfg = server.arg(i);}
		}
	}

	if (userwebcmd == "clearlog"){
		savelog();
		txtlog = "clearlog<br>";
		rootmsg = "clearlog";
	}

	if (userwebcmd == "savecfg"){
		txtlog = "savecfg: " + cfg;
		rootmsg = "savecfg";
	}


	if (userwebcmd == "log"){
		savelog(); 
		txtlog = "";
		namelogfile = "/log" + String(YYYYMMDD) + ".txt";
		File dataFile = SD.open(namelogfile.c_str());
		server.send ( 200, "text/html", "<html>\
<head>\
<meta charset='utf-8'>\
</head>\
<style>\
body{background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}\
</style>\
<body>\
" + String(dataFile.readString()) + "\
</body>\
</html>");

	return;
	}


	if (userwebcmd == "dellog"){
		if (!SD.begin(16)){//Serialprint("No card or failed");
		}
		namelogfile = "/log" + String(YYYYMMDD) + ".txt";
		SD.remove(namelogfile.c_str());
		rootmsg = "dellog";
	}




String txt = "<!DOCTYPE html>\
<html>\
<head>\
<meta http-equiv='refresh' content='300'>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,minimum-scale=1,maximum-scale=1,initial-scale=1,user-scalable=no'>\
<meta name='format-detection' content='telephone=no'>\
<meta name='mobile-web-app-capable' content='yes'><meta name='referrer' content='origin'/>\
<title>"+config.botname+"</title>\
<style>\
body{width:700px; padding:0px; margin:0px; background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}\
</style>\
</head>\
<body>\
<table width:700px;><tr width:700px><td>\
" + rootmsg + "<br>\
<form>\
<input type=\"button\" value=\"F5\" onclick=\"location.href='http://" + IP + "'\" />\
<input type=\"button\" value=\"log\" onclick=\"location.href='http://" + IP + "/?userwebcmd=log'\" />\
<input type=\"button\" value=\"clearlog\" onclick=\"location.href='http://" + IP + "/?userwebcmd=clearlog'\" />\
<input type=\"button\" value=\"dellogSD\" onclick=\"location.href='http://" + IP + "/?userwebcmd=dellog'\" />\
<input type=\"button\" value=\"cfg\" onclick=\"location.href='http://" + IP + "/cfg'\" />\
<input type=\"button\" value=\"a\" onclick=\"location.href='http://" + IP + "/a'\" />\
<input type=\"button\" value=\"restart\" onclick=\"location.href='http://" + IP + "/restart'\" />\
<input type=\"button\" value=\"update\" onclick=\"location.href='http://" + IP + "/u'\" />\
</form>\
-----------------------------------------------<br>\
"+config.botname+" (c) 2018 Slava Zagaynov +79165793105<br>\
ip: " + IP + " mac: " + mac + "<br>RSSI: " + String(WiFi.RSSI()) + " dBm\
" + uptime + " <br>\
-----------------------------------------------<br>\
txtSTATUS<br>\
-----------------------------------------------<br>\
<form>\
<input type=\"button\" value=\"1.key01\" onclick=\"location.href='http://"+IP+"/input_web?msg=01'\"/><br>\
<input type=\"button\" value=\"2.key02\" onclick=\"location.href='http://"+IP+"/input_web?msg=02'\"/><br>\
<input type=\"button\" value=\"3.key03\" onclick=\"location.href='http://"+IP+"/input_web?msg=03'\"/><br>\
<input type=\"button\" value=\"4.key04\" onclick=\"location.href='http://"+IP+"/input_web?msg=04'\"/><br>\
<input type=\"button\" value=\"5.key05\" onclick=\"location.href='http://"+IP+"/input_web?msg=05'\"/><br>\
<input type=\"button\" value=\"6.key06\" onclick=\"location.href='http://"+IP+"/input_web?msg=06'\"/><br>\
<input type=\"button\" value=\"7.key07\" onclick=\"location.href='http://"+IP+"/input_web?msg=07'\"/><br>\
<input type=\"button\" value=\"8.key08\" onclick=\"location.href='http://"+IP+"/input_web?msg=08'\"/><br>\
<input type=\"button\" value=\"9.key09\" onclick=\"location.href='http://"+IP+"/input_web?msg=09'\"/><br>\
</form>\
<br>\
" + txtlog + "<br>\
</td></tr></table>\
</body>\
</html>";

	String key;
	key = config.key01; key.replace(" ", " ");  txt.replace("key01", key);
	key = config.key02; key.replace(" ", " ");  txt.replace("key02", key);
	key = config.key03; key.replace(" ", " ");  txt.replace("key03", key);
	key = config.key04; key.replace(" ", " ");  txt.replace("key04", key);
	key = config.key05; key.replace(" ", " ");  txt.replace("key05", key);
	key = config.key06; key.replace(" ", " ");  txt.replace("key06", key);
	key = config.key07; key.replace(" ", " ");  txt.replace("key07", key);
	key = config.key08; key.replace(" ", " ");  txt.replace("key08", key);
	key = config.key09; key.replace(" ", " ");  txt.replace("key09", key);

	String status1 = status(1);
	status1.replace("\n","<br>");

	txt.replace("txtSTATUS", status1);

	txt.replace("<br><br>", "<br>");
	
	txt.replace("  ", " ");
	txt.replace("<br>", "<br>\n");
 

	txt += ("in msg:"); 
	txt += ("<br>");
	for (byte j = 0; j < 10; j++){
		txt += (String(j)+". [" +String(in_user_array[j])+"] "+String(in_msg_array[j])+" #"+String(in_iniciator_array[j]));    
		txt += ("<br>");}

	txt += ("out msg:"); 
	txt += ("<br>");
	for (byte j = 0; j < 10; j++){
		txt += (String(j)+". ["+String(out_user_array[j])+"] "+String(out_msg_array[j])+" #"+String(out_sek_array[j]));    
		txt += ("<br>");}

	txt += ("minions:"); 
	txt += ("<br>");
	for (byte j = 0; j < 9; j++){
		txt += (String(j) + ". " + "["+String(m_sek_array[j])+ "] " + String(m_ip_array[j])+ " "+String(m_name_array[j]));    
		txt += ("<br>");
	} 

	server.send ( 200, "text/html", txt );

//Serialprint("handle_ROOT finish");

}

//---------------------------------------------------------
void handle_a_status(){

	String cfg;
	int rez = 0;

	if (server.args() > 0){
		for ( uint8_t i = 0; i < server.args(); i++ ){
			if (server.argName(i) == "plain"){
				cfg = server.arg(i);
				rez = 1;
				break;
			}
		}
		
		if (rez == 1) {
			Serialprint("запись a_status на SD и SPIFFS");
			//Serialprint("запись cfg на SD/SPIFFS: "+cfg);
		
			//SD.remove(file_a_status);
			//File myFile = SD.open(file_a_status.c_str(), FILE_WRITE);
			//if (myFile){Serialprint("Writing to SD cfg...");myFile.print(cfg);myFile.close();}
	
			File myFile = SPIFFS.open(file_a_status.c_str(), FILE_WRITE);
			if (myFile){Serialprint("Writing to SPIFFS a_status...");
				myFile.print(cfg);
				myFile.close();
			}
		
			WiFi.disconnect();delay(3000);ESP.restart();delay(100000);return;
		}
	}

		//Serialprint("загрузка cfg с SD");
		//File dataFile = SD.open(file_a_status.c_str());
		//if (!dataFile){
			Serialprint("загрузка a_status с SPIFFS");
			File dataFile = SPIFFS.open(file_a_status.c_str());
		//}
		
		
	
//alert('если ничего не глюкануло, то cfg записан');\

String t = "\
<!DOCTYPE HTML><html><head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,minimum-scale=1,maximum-scale=1,initial-scale=1,user-scalable=no'>\
<meta name='format-detection' content='telephone=no'>\
<meta name='mobile-web-app-capable' content='yes'><meta name='referrer' content='origin'/>\
<title>"+config.botname+"</title>\
<script>function save_cfg(f){server = '?savecfg=';request = new XMLHttpRequest();request.open('POST', server, true);request.send(f.ncfg.value);}</script>\
</head>\
<style>body{width:400px; padding:0px; margin:0px; background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}</style>\
<body><table width:400px;><tr width:400px><td>\
<form action='handler.php'>\
<textarea width:400px; rows=\"50\" cols=\"110\" name=\"ncfg\">CFG</textarea>\
<input type=\"button\" value=\"Назад\" onclick=\"location.href='http://" + IP + "'\" />\
<input type=\"button\" value=\"Сохранить  и перезапустить ESP\" onclick=\"save_cfg(this.form)\" >\
</form>\
</td></tr></table></body></html>";

	//server = '?savecfg='+f.ncfg.value;\	//alert(server);\	//alert(f.ncfg.value);\	//t.replace("''", \" );
	String cfgtxt = String(dataFile.readString());
	t.replace("CFG", cfgtxt );
	//t.replace("txtlog", txtlog );	//t.replace("txtlog", "" );	//t.replace("alert(server);", "" );
	server.send ( 200, "text/html", t);

}

//---------------------------------------------------------
void handle_cfg(){

	String cfg;
	int rez = 0;


	if (server.args() > 0){
		for ( uint8_t i = 0; i < server.args(); i++ ){
			if (server.argName(i) == "plain"){
				cfg = server.arg(i);
				rez = 1;
				break;
			}
		}
		
		if (rez ==1 ){
			Serialprint("запись cfg на SD или SPIFFS");
			//Serialprint("запись cfg на SD/SPIFFS: "+cfg);
		
/* 			//SD.remove(filecfg);
			File myFile = SD.open(filecfg.c_str(), FILE_WRITE);
			if (myFile){Serialprint("Writing to SD cfg...");
				myFile.print(cfg);
				myFile.close();
			} */
	
			File myFile = SPIFFS.open(filecfg.c_str(), FILE_WRITE);
			if (myFile){Serialprint("Writing to SPIFFS cfg...");
				myFile.print(cfg);
				myFile.close();
			}
		
			WiFi.disconnect();delay(3000);ESP.restart();delay(100000);return;
		}
	}

	//Serialprint("загрузка cfg с SD");
	//File dataFile = SD.open(filecfg.c_str());
	//if (!dataFile){
		Serialprint("загрузка cfg с SPIFFS");
		File dataFile = SPIFFS.open(filecfg.c_str());
	//}
	
//alert('если ничего не глюкануло, то cfg записан');\

String t = "\
<!DOCTYPE HTML><html><head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,minimum-scale=1,maximum-scale=1,initial-scale=1,user-scalable=no'>\
<meta name='format-detection' content='telephone=no'>\
<meta name='mobile-web-app-capable' content='yes'><meta name='referrer' content='origin'/>\
<title>"+config.botname+"</title>\
<script>function save_cfg(f){server = '?savecfg=';request = new XMLHttpRequest();request.open('POST', server, true);request.send(f.ncfg.value);}</script>\
</head>\
<style>body{width:500px; padding:0px; margin:0px; background-color: #000000; font-family: Courier; Color: #FFFFFF; font-size: 10px;}</style>\
<body><table width:500px;><tr width:500px><td>\
<form action='handler.php'>\
<textarea width:500px; rows=\"50\" cols=\"70\" name=\"ncfg\">CFG</textarea>\
<input type=\"button\" value=\"Назад\" onclick=\"location.href='http://" + IP + "'\" />\
<input type=\"button\" value=\"Сохранить cfg и перезапустить ESP\" onclick=\"save_cfg(this.form)\" >\
</form>\
</td></tr></table></body></html>";

	//server = '?savecfg='+f.ncfg.value;\	//alert(server);\	//alert(f.ncfg.value);\	//t.replace("''", \" );
	String cfgtxt = String(dataFile.readString());
	t.replace("CFG", cfgtxt );
	//t.replace("txtlog", txtlog );	//t.replace("txtlog", "" );	//t.replace("alert(server);", "" );
	server.send ( 200, "text/html", t);

}

//---------------------------------------------------------
void notFound(AsyncWebServerRequest *request) {
	
	
    request->send(404, "text/plain", "Not found");
}

//---------------------------------------------------------
void NotFound(){

	//server.send ( 404, "text/html", "NotFound");
	//kill_tcp();
	//return;

	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ){
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}
	message = message + " \nplain: " + server.arg("plain");

	server.send ( 404, "text/plain", message );

	Serialprint(message);
	delay(1); 

} // end handle_NotFound()

//---------------------------------------------------------
void handle_t(){








	String message = "handle_t\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ){
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}
	message = message + " \nplain: " + server.arg("plain");

	server.send ( 404, "text/plain", message );

	Serialprint(message);
	delay(1); 

} // end handle_t()



//---------------------------------------------------------
void handle_input_svz(){
	
	server.send ( 200, "" );
	
	// http://192.168.1.242/input_svz?msg=print_lcd=хохохо&chat_id=1

/* 	String msg;
	String chat_id;

	String URL = "";
	if (server.args() > 0){
		for ( uint8_t i = 0; i < server.args(); i++ ){
		URL += "" + server.argName(i) + "=" + server.arg(i) + "&";
		if (server.argName(i) == "msg"){msg = server.arg(i);}
		if (server.argName(i) == "chat_id"){chat_id = server.arg(i);}
		}
	} */

	String msg 		= server.arg("msg");
	String chat_id 	= server.arg("chat_id");


	Serialprint("-input_svz-:["+chat_id+"]["+msg+"]");
	if (msg == ""){return;}
	add_input_array(chat_id, msg);

}