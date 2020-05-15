



//---------------------------------------------------------
void LoadConfigSDorSPIFFS(){
	
	//print_lcd(0,0,"LoadConfigSDorSPIFFS-1");

	Serialprint("Init SD card");
	if (!SD.begin(4, SPI, 1000000)){Serialprint("Card bad");		//delay(3000);
	}

//print_lcd(0,0,"LoadConfigSDorSPIFFS-2");

			
	File dataFile = SD.open(filecfg.c_str());
	if (!dataFile){
		Serial.println("Failed to open SD file for reading");
		//ESP.restart();
		dataFile = SPIFFS.open(filecfg.c_str());
		if (!dataFile){
			Serial.println("Failed to SPIFFS open file for reading");
			//ESP.restart();
		}else{Serial.println("OK to SPIFFS open file for reading");
		}
	}
	
	//Serialprint(String(dataFile));
	//delay(3000);
//print_lcd(0,0,"LoadConfigSDorSPIFFS-3");

	DynamicJsonBuffer jsonBuffer;
	JsonObject &root = jsonBuffer.parseObject(dataFile);
	if (!root.success()){Serialprint("No read/bad " + filecfg + ".");
	//if (!root.success()){Serialprint("No read/bad " + filecfg + ", 5 sec, restart");
//savelog();
//delay(5000);
//ESP.restart();
	}

// Copy values from the JsonObject to the Config
//config.port = root["port"] | 2731;
//strlcpy(config.hostname, // <- destination
// root["hostname"] | "example.com", // <- source
// sizeof(config.hostname)); // <- destination's capacity

	debug_to_serial = root["debug_to_serial"] | 1;
	debug_to_serial_mask = root["debug_to_serial_mask"] | "";

	config.BOTtoken = root["BOTtoken"] | "";
	config.BOTtoken_ALARM = root["BOTtoken_ALARM"] | "";
	config.botname 			= root["botname"] | "";
	config.botinfo 			= root["botinfo"] | "";
	//if(config.botname == ""){config.botname = appname+" no cfg";}
	if(config.botname == ""){"no cfg";}

	config.legal_chat_id = root["legal_chat_id"] | ",1,";
	config.admin_chat_id = root["admin_chat_id"] | "";
	config.alarm_chat_id = root["alarm_chat_id"] | "";

	config.ip = root["ip"] | "192.168.1.254";
	config.ip123_ = root["ip123_"] | "192.168.1.";
	config.subnet = root["subnet"] | "255.255.255.0";
	config.gateway = root["gateway"] | "192.168.1.1";

	strlcpy(config.ssid, root["ssid"] | "ubnt", sizeof(config.ssid));
	strlcpy(config.pass, root["pass"] | "", sizeof(config.pass));

	config.Clear_log_interval = root["Clear_log_interval"] | 300000;

	//Clear_log_interval = config.Clear_log_interval;

	config.noDisplay 		= root["noDisplay"] | 0;
	i2c_pin_1 				= root["i2c_pin_1"] | 5;
	i2c_pin_2 				= root["i2c_pin_2"] | 4;
	
	config.log 				= root["log"] | 0;
	config.log_to_SDcard 	= root["log_to_SDcard"] | 0;
	config.OTA 				= root["OTA"] | 1;
	config.getTLG 			= root["getTLG"] | 0;
	config.sendTLG 			= root["sendTLG"] | 0;
	config.send_svyaznoy 	= root["send_svyaznoy"] | 0;
	config.ip_svyaznoy 		= root["ip_svyaznoy"] | "";





	config.use_RF_PULT					= root["use_RF_PULT"] | 0;
	config.GPIO_RF_RECIVER				= root["GPIO_RF_RECIVER"] | 0;

	config.F_Ohrana 					= root["F_Ohrana"] | 0;
	config.F_Ohrana_Sirena_GPIO 		= root["F_Ohrana_Sirena_GPIO"] | 0;
	config.F_Ohrana_Trevoga_GPIO 		= root["F_Ohrana_Trevoga_GPIO"] | 0;

	config.F_UltraSonic 				= root["F_UltraSonic"] | 0;
	config.F_UltraSonic_trig_GPIO 		= root["F_UltraSonic_trig_GPIO"] | 0;
	config.F_UltraSonic_echo_GPIO 		= root["F_UltraSonic_echo_GPIO"] | 0;
	config.hcsr04_interval				= root["hcsr04_interval"] | 15000;
	config.hcsr04_delta					= root["hcsr04_delta"] | 2;
	
	config.F_DHT 						= root["F_DHT"] | 0;
	
	config.F_DS18B20 					= root["F_DS18B20"] | 0;
	
	config.DS18B20_1_Alarm 					= root["DS18B20_1_Alarm"] | 0;
	config.DS18B20_1_name 					= root["DS18B20_1_name"] | "";
	config.DS18B20_1_min 					= root["DS18B20_1_min"] | 0;
	config.DS18B20_1_max 					= root["DS18B20_1_max"] | 0;
	config.DS18B20_1_msg 					= root["DS18B20_1_msg"] | "";
	config.DS18B20_1_msg_ok					= root["DS18B20_1_msg_ok"] | "";
	
	config.DS18B20_2_Alarm 					= root["DS18B20_2_Alarm"] | 0;
	config.DS18B20_2_name 					= root["DS18B20_2_name"] | "";
	config.DS18B20_2_min 					= root["DS18B20_2_min"] | 0;
	config.DS18B20_2_max 					= root["DS18B20_2_max"] | 0;
	config.DS18B20_2_msg 					= root["DS18B20_2_msg"] | "";
	config.DS18B20_2_msg_ok					= root["DS18B20_2_msg_ok"] | "";
	
	






	//пример
	//"m01_name": "Ветряной",
	//"m01_ip": "192.168.1.240",

	String n, i;
	int ln1, ln2;
	char ss1[40], ss2[20];

	n = root["m01_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[0], ss1, ln1);
	i = root["m01_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[0],   ss2, ln2);
	n = root["m02_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[1], ss1, ln1);
	i = root["m02_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[1],   ss2, ln2);
	n = root["m03_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[2], ss1, ln1);
	i = root["m03_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[2],   ss2, ln2);
	n = root["m04_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[3], ss1, ln1);
	i = root["m04_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[3],   ss2, ln2);
	n = root["m05_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[4], ss1, ln1);
	i = root["m05_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[4],   ss2, ln2);
	n = root["m06_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[5], ss1, ln1);
	i = root["m06_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[5],   ss2, ln2);
	n = root["m07_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[6], ss1, ln1);
	i = root["m07_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[6],   ss2, ln2);
	n = root["m08_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[7], ss1, ln1);
	i = root["m08_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[7],   ss2, ln2);
	n = root["m09_name"] | ""; ln1 = n.length() + 1; memcpy(ss1, "", 40); n.toCharArray(ss1, ln1); memcpy(m_name_array[8], ss1, ln1);
	i = root["m09_ip"] | "";   ln2 = i.length() + 1; memcpy(ss2, "", 20); i.toCharArray(ss2, ln2); memcpy(m_ip_array[8],   ss2, ln2);


	config.key01 = root["key01"] | "";		config.cmd01 = root["cmd01"] | "";
	config.key02 = root["key02"] | "";		config.cmd02 = root["cmd02"] | "";
	config.key03 = root["key03"] | "";		config.cmd03 = root["cmd03"] | "";
	config.key04 = root["key04"] | "";		config.cmd04 = root["cmd04"] | "";
	config.key05 = root["key05"] | "";		config.cmd05 = root["cmd05"] | "";
	config.key06 = root["key06"] | "";		config.cmd06 = root["cmd06"] | "";
	config.key07 = root["key07"] | "";		config.cmd07 = root["cmd07"] | "";
	config.key08 = root["key08"] | "";		config.cmd08 = root["cmd08"] | "";
	config.key09 = root["key09"] | "";		config.cmd09 = root["cmd09"] | "";
		

	config.line01 		= root["line01"] | "";		config.line_cmd01 	= root["line_cmd01"] | "";
	config.line02 		= root["line02"] | "";		config.line_cmd02 	= root["line_cmd02"] | "";
	config.line03 		= root["line03"] | "";		config.line_cmd03 	= root["line_cmd03"] | "";
	config.line04 		= root["line04"] | "";		config.line_cmd04 	= root["line_cmd04"] | "";
	config.line05 		= root["line05"] | "";		config.line_cmd05 	= root["line_cmd05"] | "";
	config.line06 		= root["line06"] | "";		config.line_cmd06 	= root["line_cmd06"] | "";
	config.line07 		= root["line07"] | "";		config.line_cmd07 	= root["line_cmd07"] | "";
	config.line08 		= root["line08"] | "";		config.line_cmd08 	= root["line_cmd08"] | "";
	config.line09 		= root["line09"] | "";		config.line_cmd09 	= root["line_cmd09"] | "";


config.in00name = root["in00name"] | "GPIO00";
config.in00cmd0 = root["in00cmd0"] | "";
config.in00cmd1 = root["in00cmd1"] | "";
config.in00i = root["in00i"] | 0;
	if (config.in00i == 1){
		config.in00i0 = root["in00i0"] | "";
		config.in00i1 = root["in00i1"] | "";
		config.in00mode = root["in00mode"] | "";
		if (config.in00mode == "INPUT"){pinMode(0, INPUT);}
		if (config.in00mode == "OUTPUT"){pinMode(0, OUTPUT);      config.in00v = root["in00v"] | 2;
			if ((config.in00v == 0) || (config.in00v == 1)){digitalWrite(0, config.in00v);}
		}
		config.in00save = root["in00save"] | 0;
		config.in00load = root["in00load"] | 0;
	}
	
config.in02name = root["in02name"] | "GPIO02";
config.in02cmd0 = root["in02cmd0"] | "";
config.in02cmd1 = root["in02cmd1"] | "";
config.in02i = root["in02i"] | 0;
	if (config.in02i == 1){
		config.in02i0 = root["in02i0"] | "";
		config.in02i1 = root["in02i1"] | "";
		config.in02mode = root["in02mode"] | "";
		if (config.in02mode == "INPUT"){pinMode(2, INPUT);}
		if (config.in02mode == "OUTPUT"){pinMode(2, OUTPUT);      config.in02v = root["in02v"] | 2;
			if ((config.in02v == 0) || (config.in02v == 1)){digitalWrite(2, config.in02v);}
		}
		config.in02save = root["in02save"] | 0;
		config.in02load = root["in02load"] | 0;
	}
	
config.in04name = root["in04name"] | "GPIO04";
config.in04i = root["in04i"] | 0;
	if (config.in04i == 1){
		config.in04i0 = root["in04i0"] | "";
		config.in04i1 = root["in04i1"] | "";
		config.in04mode = root["in04mode"] | "";
		if (config.in04mode == "INPUT"){pinMode(4, INPUT);}
		if (config.in04mode == "OUTPUT"){pinMode(4, OUTPUT);      config.in04v = root["in04v"] | 2;
			if ((config.in04v == 0) || (config.in04v == 1)){digitalWrite(4, config.in04v);}
		}
		config.in04save = root["in04save"] | 0;
		config.in04load = root["in04load"] | 0;
	}

config.in05name = root["in05name"] | "GPIO05";
config.in05i = root["in05i"] | 0;
	if (config.in05i == 1){
		config.in05i0 = root["in05i0"] | "";
		config.in05i1 = root["in05i1"] | "";
		config.in05mode = root["in05mode"] | "";
		if (config.in05mode == "INPUT"){pinMode(5, INPUT);}
		if (config.in05mode == "OUTPUT"){pinMode(5, OUTPUT);      config.in05v = root["in05v"] | 2;
			if ((config.in05v == 0) || (config.in05v == 1)){digitalWrite(5, config.in05v);}
		}
		config.in05save = root["in05save"] | 0;
		config.in05load = root["in05load"] | 0;
	}



config.in12name = root["in12name"] | "GPIO12";
config.in12i = root["in12i"] | 0;
	if (config.in12i == 1){
		config.in12i0 = root["in12i0"] | "";
		config.in12i1 = root["in12i1"] | "";
		config.in12mode = root["in12mode"] | "";
		if (config.in12mode == "INPUT"){pinMode(12, INPUT);}
		if (config.in12mode == "OUTPUT"){pinMode(12, OUTPUT);      config.in12v = root["in12v"] | 2;
			if ((config.in12v == 0) || (config.in12v == 1)){digitalWrite(12, config.in12v);}
		}
		config.in12save = root["in12save"] | 0;
		config.in12load = root["in12load"] | 0;
	}

config.in13name = root["in13name"] | "GPIO13";
config.in13i = root["in13i"] | 0;
	if (config.in13i == 1){
		config.in13i0 = root["in13i0"] | "";
		config.in13i1 = root["in13i1"] | "";
		config.in13mode = root["in13mode"] | "";
		if (config.in13mode == "INPUT"){pinMode(13, INPUT);}
		if (config.in13mode == "OUTPUT"){pinMode(13, OUTPUT);      config.in13v = root["in13v"] | 2;
			if ((config.in13v == 0) || (config.in13v == 1)){digitalWrite(13, config.in13v);}
		}
		config.in13save = root["in13save"] | 0;
		config.in13load = root["in13load"] | 0;
	}
	
	

config.RF_keys_1 = root["RF_keys_1"] | "";
config.RF_keys_2 = root["RF_keys_2"] | "";
config.RF_keys_3 = root["RF_keys_3"] | "";
config.RF_keys_4 = root["RF_keys_4"] | "";
config.RF_keys_5 = root["RF_keys_5"] | "";
config.RF_keys_6 = root["RF_keys_6"] | "";
config.RF_keys_TREVOGA = root["RF_keys_TREVOGA"] | "";
config.Pins_TREVOGA = root["Pins_TREVOGA"] | "";

config.RF_array = root["RF_array"] | "";


	dataFile.close();
	
	
	
//*************** A-SETTING ******************
	delay(50);
	
	File myFile_a_status = SPIFFS.open(file_a_status.c_str(), "r");
	JsonObject &root2 = jsonBuffer.parseObject(myFile_a_status);
	if (!root.success()){
		Serialprintln("No read /a_status.cfg");
		}else{
			file_a_status_loaded = 1;
		}
	
	OHRANA = root2["OHRANA"] | 0;
	
	if(config.in00load == 1){
		if (root2["GPIO0"] == 1){digitalWrite(0, HIGH);}
		if (root2["GPIO0"] == 0){digitalWrite(0, LOW);}	}

	if(config.in02load == 1){
		if (root2["GPIO2"] == 1){digitalWrite(2, HIGH);}
		if (root2["GPIO2"] == 0){digitalWrite(2, LOW);}	}
	
	if(config.in04load == 1){
		if (root2["GPIO4"] == 1){digitalWrite(4, HIGH);}
		if (root2["GPIO4"] == 0){digitalWrite(4, LOW);}	}

	if(config.in05load == 1){
		if (root2["GPIO5"] == 1){digitalWrite(5, HIGH);}
		if (root2["GPIO5"] == 0){digitalWrite(5, LOW);}	}
	
	if(config.in12load == 1){
		if (root2["GPIO12"] == 1){digitalWrite(12, HIGH);}
		if (root2["GPIO12"] == 0){digitalWrite(12, LOW);}}
	
	if(config.in13load == 1){
		if (root2["GPIO13"] == 1){digitalWrite(13, HIGH);}
		if (root2["GPIO13"] == 0){digitalWrite(13, LOW);}}
	
	if(config.in14load == 1){
		if (root2["GPIO14"] == 1){digitalWrite(14, HIGH);}
		if (root2["GPIO14"] == 0){digitalWrite(14, LOW);}}
	
	if(config.in15load == 1){
		if (root2["GPIO15"] == 1){digitalWrite(15, HIGH);}
		if (root2["GPIO15"] == 0){digitalWrite(15, LOW);}}
	
	
	
	
	
	
 	for (byte Q = 0; Q < 10; Q++){
		memcpy(timer_date_array[Q]		,root2["t"+String(Q)+"date"]	| "" , 8 	);
 		memcpy(timer_time_array[Q]		,root2["t"+String(Q)+"time"] 	| "" , 4 	);
		memcpy(timer_repeet_array[Q]	,root2["t"+String(Q)+"reprat"] 	| "" , 1 	);
		memcpy(timer_command_array[Q]	,root2["t"+String(Q)+"comand"] 	| "" , 100 	);
		memcpy(timer_exdate_array[Q]	,root2["t"+String(Q)+"exdate"] 	| "" , 8 	);
		memcpy(timer_extime_array[Q]	,root2["t"+String(Q)+"extime"] 	| "" , 4 	); 
	}	
	
	
	//if (root2["GPIO15"] == 1){digitalWrite(15, HIGH);}
	//if (root2["GPIO15"] == 0){digitalWrite(15, LOW);} 
	//if (root2["GPIO16"] == 1){digitalWrite(16, HIGH);}
	//if (root2["GPIO16"] == 0){digitalWrite(16, LOW);} 
	myFile_a_status.close();  
	
	
	
	
	Serialprint("LoadConfig-end");
	//print_lcd(0,0,"LoadConfig-end");
	if (config.getTLG == 1 ){bot.BOTtoken(config.BOTtoken);}
	if (config.sendTLG == 1 ){bot.BOTtoken(config.BOTtoken);}
	

	
}

