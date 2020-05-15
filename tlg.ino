//----------------------------------------
//telegram bot
//----------------------------------------

uint32_t get_Tlg_Bot_interval = 5000; //mean time between scan messages
uint32_t get_Tlg_Bot_lasttime;   //last time messages' scan has been done
uint32_t botlast_message_received;
uint32_t botlast_message_received_alarm;
int logT = 0;

//---------------------------------------------------------
int  botsendMessage(String chat_id, String msg, String p){
	
	if (msg.indexOf("!!!")<0){if (millis() < botlast_message_sending){return 0;}}
	
	int timeout = 500;
	if (logT==1){Serialprint("-botsendMessage-sending tlg start");}
	String res = bot.sendMessage(chat_id,msg,"");
	if (logT==1){Serialprint("-botsendMessage-sending tlg finish");}
	if (logT==1){Serialprint("-botsendMessage-sending tlg result: "+res);}
	
	int rez = 1;
	if (res.indexOf("error") == 0){
		timeout = 60000;
		Serialprint("-botsendMessage-sending tlg timeout = "+String(timeout/1000)+" секунд");
		rez = 0;
	}
	botlast_message_sending = millis() + timeout;
	
	return rez;
}

//---------------------------------------------------------
void getUpdTLG(){
	
  	//if (Uskoritel > 0){if (millis() > get_Tlg_Bot_lasttime + 3000){get_Tlg_Bot_lasttime = 0;Uskoritel = Uskoritel - 1;}}
	//if (get_Tlg_Bot_lasttime > millis()){get_Tlg_Bot_lasttime = millis();} 
	if (millis() < get_Tlg_Bot_lasttime + get_Tlg_Bot_interval){return;} 
		
	uint32_t millis0T = millis();
	//print_lcd(7,0,"T-"+String(Uskoritel)+"-"+String(millis0T));
	print_lcd(7,0,"TLGRM get");


	if (logT==1){Serialprint("-getUpdTLG-getupdates tlg start");}
	
	
	int numNewMessages = bot.getUpdates(botlast_message_received + 1);
	 //numNewMessages = 0;
	
	if (logT==1){Serialprint("-getUpdTLG-getupdates tlg finish");}
	if (numNewMessages == -1){
		
		int timeout = 60000*3;
		get_Tlg_Bot_lasttime = millis() + timeout;
		Serialprint("-getUpdTLG-getupdates tlg timeout = "+String(timeout/1000)+" секунд");
		print_lcd(7,0,"TLGRM ERROR");
		return;
		
	}
	
	
	botlast_message_received = bot.last_message_received;
	
	if (numNewMessages == 1){
	//	Uskoritel = 10;

			String chat_id 		= bot.messages[0].chat_id;
			String text 		= bot.messages[0].text.substring(0,200);
			String iniciator 	= bot.messages[0].from_name.substring(0,200);
			//text = rus(text);
			Serialprint("<-tlg-["+chat_id+"]["+text+"]["+iniciator+"]");
			add_input_array(chat_id, text, iniciator);
	}
	
	get_Tlg_Bot_lasttime = millis();
	
	//Serialprint("botlast_message_received ="+String(botlast_message_received));
	//Serialprint("botlast_message_received="+String(bot.last_message_received));
	
	//return;
	
	uint32_t millis1T = get_Tlg_Bot_lasttime;
	uint32_t millis2T = millis1T - millis0T;
	//print_lcd(7,0,"t-"+String(Uskoritel)+"-"+String(millis0T)+"-"+String(millis1T)+"="+String(millis2T));
	
	print_lcd(7,0,"TLGRM "+String(millis2T)+"ms");

	
}
