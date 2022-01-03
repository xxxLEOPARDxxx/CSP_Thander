int idLngFile = 0;

void InitInterface(string iniName)
{
	GameInterface.title = "titleMekakhrom";
    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetInformation();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "TYPE_1_OK":
			if(comName=="activate" || comName=="click")
			{
				Done_1();
			}
		break;

		case "TYPE_1_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset_1();
			}
		break;

		case "TYPE_2_OK":
			if(comName=="activate" || comName=="click")
			{
				Done_2();
			}
		break;

		case "TYPE_2_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset_2();
			}
		break;

		case "TYPE_3_OK":
			if(comName=="activate" || comName=="click")
			{
				Done_3();
			}
		break;

		case "TYPE_3_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset_3();
			}
		break;

		case "TYPE_4_OK":
			if(comName=="activate" || comName=="click")
			{
				Done_4();
			}
		break;

		case "TYPE_4_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset_4();
			}
		break;

		case "TYPE_7_OK":
			if(comName=="activate" || comName=="click")
			{
				Done_7();
			}
		break;

		case "TYPE_7_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset_7();
			}
		break;
	}
}

void SetInformation()
{
	int iType = sti(PChar.Dozor.Riddle.CurType);

	for(int f=1; f<=8; f++)
	{
		OpenCloseFrame(f, false);
	}

	switch(iType)
	{
		case 1: Type_1(); break;
		case 2: Type_2(); break;
		case 3: Type_3(); break;
		case 4: Type_4(); break;
		case 5: Type_5(); break;
		case 6: Type_6(); break;
		case 7: Type_7(); break;
		case 8: Type_8(); break;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
// TYPE 1
//////////////////////////////////////////////////////////////////////////////////////////
void Type_1()
{
	OpenCloseFrame(1, true);

	CreateString(true,"Type_1_RiddleHeader", "Загадка: ", FONT_CAPTION, COLOR_NORMAL, 400,148,SCRIPT_ALIGN_CENTER,1.5);

	string sString = PChar.Dozor.Riddle.Type_1.Question;
	SetFormatedText("RIDDLE_TEXT_1", sString);

	CreateString(true,"Type_1_Answer_1", "Место назначения:", FONT_CAPTION, COLOR_NORMAL, 125,359,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Type_1_KeyPhrase", "Ответьте правильно для получения ключевой фразы.", FONT_CAPTION, COLOR_NORMAL, 410,400,SCRIPT_ALIGN_CENTER,1.0);
}

void Done_1()
{
	string sAnswer = GameInterface.TYPE_1_ANSWER_1.str;
	string sAnswerBase = PChar.Dozor.Riddle.Type_1.Answer_1;

	sAnswer = GetStrSmallRegister(sAnswer);

	if(sAnswer == sAnswerBase)
	{
		string sKeyPhrase = PChar.Dozor.Riddle.Type_1.KeyPhrase;
		CreateString(true,"Type_1_KeyPhrase", "Ключевая фраза: " + sKeyPhrase, FONT_CAPTION, argb(255,128,255,128), 410,400,SCRIPT_ALIGN_CENTER,1.0);
		SetSelectable("TYPE_1_OK", false);
		SetSelectable("TYPE_1_RESET", false);
		DozorToPuertoRicoShore();
	}
	else
	{
		CreateString(true,"Type_1_KeyPhrase", "Ответ неверный.", FONT_CAPTION, argb(255,255,128,128), 410,400,SCRIPT_ALIGN_CENTER,1.0);
		SetSelectable("TYPE_1_OK", false);
	}
}

void Reset_1()
{
	SetSelectable("TYPE_1_OK", true);
	SetSelectable("TYPE_1_RESET", true);
	GameInterface.TYPE_1_ANSWER_1.str = "";
	Type_1();
}


//////////////////////////////////////////////////////////////////////////////////////////
// TYPE 2
//////////////////////////////////////////////////////////////////////////////////////////
void Type_2()
{
	OpenCloseFrame(2, true);
	CreateString(true,"Type_2_RiddleHeader", "Загадка: ", FONT_CAPTION, COLOR_NORMAL, 400,148,SCRIPT_ALIGN_CENTER,1.5);

	string sString = PChar.Dozor.Riddle.Type_2.Question;
	SetFormatedText("RIDDLE_TEXT_2", sString);

	CreateString(true,"Type_2_Answer_1", "Остров:", FONT_CAPTION, COLOR_NORMAL, 215,319,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Type_2_Answer_2", "Место назначения:", FONT_CAPTION, COLOR_NORMAL, 270,359,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Type_2_KeyPhrase", "Ответьте правильно для получения ключевой фразы.", FONT_CAPTION, COLOR_NORMAL, 410,400,SCRIPT_ALIGN_CENTER,1.0);
}

void Done_2()
{
	string sAnswer = GameInterface.TYPE_2_ANSWER_1.str;
	string sAnswer2 = GameInterface.TYPE_2_ANSWER_2.str;
	string sAnswerBase = PChar.Dozor.Riddle.Type_2.Answer_2;
	string sAnswerBase2 = PChar.Dozor.Riddle.Type_2.Answer_1;

	sAnswer = GetStrSmallRegister(sAnswer);
	sAnswer2 = GetStrSmallRegister(sAnswer2);

	if(sAnswer == sAnswerBase && sAnswer2 == sAnswerBase2)
	{
		string sKeyPhrase = PChar.Dozor.Riddle.Type_2.KeyPhrase;
		CreateString(true,"Type_2_KeyPhrase", "Ключевая фраза: " + sKeyPhrase, FONT_CAPTION, argb(255,128,255,128), 410,400,SCRIPT_ALIGN_CENTER,1.0);
		SetSelectable("TYPE_2_OK", false);
		SetSelectable("TYPE_2_RESET", false);
		DozorToTerks();
	}
	else
	{
		CreateString(true,"Type_2_KeyPhrase", "Ответ неверный.", FONT_CAPTION, argb(255,255,128,128), 410,400,SCRIPT_ALIGN_CENTER,1.0);
		SetSelectable("TYPE_2_OK", false);
	}
}

void Reset_2()
{
	SetSelectable("TYPE_2_OK", true);
	SetSelectable("TYPE_2_RESET", true);
	GameInterface.TYPE_2_ANSWER_1.str = "";
	GameInterface.TYPE_2_ANSWER_2.str = "";
	Type_2();
}

//////////////////////////////////////////////////////////////////////////////////////////
// TYPE 3
//////////////////////////////////////////////////////////////////////////////////////////
void Type_3()
{
	OpenCloseFrame(3, true);
	CreateString(true,"Type_3_RiddleHeader", "Загадка: ", FONT_CAPTION, COLOR_NORMAL, 400,88,SCRIPT_ALIGN_CENTER,1.5);

	string sString = PChar.Dozor.Riddle.Type_3.Question;
	SetFormatedText("RIDDLE_TEXT_3", sString);

	CreateString(true,"Type_3_Answer_1", "Остров:", FONT_CAPTION, COLOR_NORMAL, 165,409,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Type_3_Answer_2", "Здание:", FONT_CAPTION, COLOR_NORMAL, 220,449,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Type_3_KeyPhrase", "Ответьте правильно для получения ключевой фразы.", FONT_CAPTION, COLOR_NORMAL, 410,490,SCRIPT_ALIGN_CENTER,1.0);
}

void Done_3()
{
	string sAnswer = GameInterface.TYPE_3_ANSWER_1.str;
	string sAnswer2 = GameInterface.TYPE_3_ANSWER_2.str;
	string sAnswerBase = PChar.Dozor.Riddle.Type_3.Answer_2;
	string sAnswerBase2 = PChar.Dozor.Riddle.Type_3.Answer_1;

	sAnswer = GetStrSmallRegister(sAnswer);
	sAnswer2 = GetStrSmallRegister(sAnswer2);

	if(sAnswer == sAnswerBase && sAnswer2 == sAnswerBase2)
	{
		string sKeyPhrase = PChar.Dozor.Riddle.Type_3.KeyPhrase;
		CreateString(true,"Type_3_KeyPhrase", "Ключевая фраза: " + sKeyPhrase, FONT_CAPTION, argb(255,128,255,128), 410,490,SCRIPT_ALIGN_CENTER,1.0);
		SetSelectable("TYPE_3_OK", false);
		SetSelectable("TYPE_3_RESET", false);
		DozorToTortugaTavern();
	}
	else
	{
		CreateString(true,"Type_3_KeyPhrase", "Ответ неверный.", FONT_CAPTION, argb(255,255,128,128), 410,490,SCRIPT_ALIGN_CENTER,1.0);
		SetSelectable("TYPE_3_OK", false);
	}
}

void Reset_3()
{
	SetSelectable("TYPE_3_OK", true);
	SetSelectable("TYPE_3_RESET", true);
	GameInterface.TYPE_3_ANSWER_1.str = "";
	GameInterface.TYPE_3_ANSWER_2.str = "";
	Type_3();
}

//////////////////////////////////////////////////////////////////////////////////////////
// TYPE 4
//////////////////////////////////////////////////////////////////////////////////////////
void Type_4()
{
	OpenCloseFrame(4, true);
	CreateString(true,"Type_4_RiddleHeader", "Загадка: ", FONT_CAPTION, COLOR_NORMAL, 400,88,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("Type_4_Riddle_Image", "DOZOR", "pic_1", 125,180,695,350);
	CreateString(true,"Type_4_Answer_1", "Пункт назначения:", FONT_CAPTION, COLOR_NORMAL, 165,410,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"Type_4_Answer_1", "Пункт назначения:", FONT_CAPTION, COLOR_NORMAL, 160,409,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Type_4_Answer_2", "Место:", FONT_CAPTION, COLOR_NORMAL, 300,449,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Type_4_Phrase_1", "Сегодня на площади из здания верфи был слышен крик:", FONT_NORMAL, COLOR_NORMAL, 410,355,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"Type_4_Phrase_2", "''Наконец-то я достроил этот корабль! Достроил!''", FONT_NORMAL, COLOR_NORMAL, 410,375,SCRIPT_ALIGN_CENTER,1.0);
}

void Done_4()
{
	string sAnswer = GameInterface.TYPE_4_ANSWER_1.str;
	string sAnswer2 = GameInterface.TYPE_4_ANSWER_2.str;
	string sAnswerBase = PChar.Dozor.Riddle.Type_4.Answer_2;
	string sAnswerBase2 = PChar.Dozor.Riddle.Type_4.Answer_1;

	sAnswer = GetStrSmallRegister(sAnswer);
	sAnswer2 = GetStrSmallRegister(sAnswer2);

	if(sAnswer == sAnswerBase && sAnswer2 == sAnswerBase2)
	{
		string sKeyPhrase = PChar.Dozor.Riddle.Type_4.KeyPhrase;
		CreateString(true,"Type_4_KeyPhrase", "Ключевая фраза: " + sKeyPhrase, FONT_CAPTION, argb(255,128,255,128), 410,490,SCRIPT_ALIGN_CENTER,0.9);
		SetSelectable("TYPE_4_OK", false);
		SetSelectable("TYPE_4_RESET", false);
		DozorToVillemstadStore();
	}
	else
	{
		CreateString(true,"Type_4_KeyPhrase", "Ответ неверный.", FONT_CAPTION, argb(255,255,128,128), 410,490,SCRIPT_ALIGN_CENTER,0.9);
		SetSelectable("TYPE_4_OK", false);
	}
}

void Reset_4()
{
	SetSelectable("TYPE_4_OK", true);
	SetSelectable("TYPE_4_RESET", true);
	GameInterface.TYPE_4_ANSWER_1.str = "";
	GameInterface.TYPE_4_ANSWER_2.str = "";
	Type_4();
}

//////////////////////////////////////////////////////////////////////////////////////////
// TYPE 7
//////////////////////////////////////////////////////////////////////////////////////////
void Type_7()
{
	OpenCloseFrame(7, true);
	CreateString(true,"Type_7_RiddleHeader", "Загадка: ", FONT_CAPTION, COLOR_NORMAL, 400,88,SCRIPT_ALIGN_CENTER,1.5);

	string sString = PChar.Dozor.Riddle.Type_7.Question;
	SetFormatedText("RIDDLE_TEXT_7", sString);

	CreateString(true,"Type_7_Answer_1", "Остров:", FONT_CAPTION, COLOR_NORMAL, 165,409,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Type_7_Answer_2", "Место:", FONT_CAPTION, COLOR_NORMAL, 215,449,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Type_7_KeyPhrase", "Ответьте правильно для получения ключевой фразы.", FONT_CAPTION, COLOR_NORMAL, 390,490,SCRIPT_ALIGN_CENTER,1.0);
}

void Done_7()
{
	string sAnswer = GameInterface.TYPE_7_ANSWER_1.str;
	string sAnswer2 = GameInterface.TYPE_7_ANSWER_2.str;
	string sAnswerBase = PChar.Dozor.Riddle.Type_7.Answer_2;
	string sAnswerBase2 = PChar.Dozor.Riddle.Type_7.Answer_1;

	sAnswer = GetStrSmallRegister(sAnswer);
	sAnswer2 = GetStrSmallRegister(sAnswer2);

	if(sAnswer == sAnswerBase && sAnswer2 == sAnswerBase2)
	{
		string sKeyPhrase = PChar.Dozor.Riddle.Type_7.KeyPhrase;
		CreateString(true,"Type_7_KeyPhrase", "Ключевая фраза: " + sKeyPhrase, FONT_CAPTION, argb(255,128,255,128), 390,490,SCRIPT_ALIGN_CENTER,0.9);
		SetSelectable("TYPE_7_OK", false);
		SetSelectable("TYPE_7_RESET", false);
		DozorToMartiniqueShore();
	}
	else
	{
		CreateString(true,"Type_7_KeyPhrase", "Ответ неверный.", FONT_CAPTION, argb(255,255,128,128), 390,490,SCRIPT_ALIGN_CENTER,0.9);
		SetSelectable("TYPE_7_OK", false);
	}
}

void Reset_7()
{
	SetSelectable("TYPE_7_OK", true);
	SetSelectable("TYPE_7_RESET", true);
	GameInterface.TYPE_7_ANSWER_1.str = "";
	GameInterface.TYPE_7_ANSWER_2.str = "";
	Type_7();
}

//////////////////////////////////////////////////////////////////////////////////////////
// TYPE 8
//////////////////////////////////////////////////////////////////////////////////////////
void Type_8()
{
	OpenCloseFrame(8, true);
	CreateString(true,"Type_8_RiddleHeader", "Загадка: ", FONT_CAPTION, COLOR_NORMAL, 400,98,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("Type_8_Riddle_Image", "COLONY_ARCHITECTURE", "Dozor_1", 315,160,485,340);

	string sString = PChar.Dozor.Riddle.Type_8.Question;
	SetFormatedText("RIDDLE_TEXT_8", sString);
}

//////////////////////////////////////////////////////////////////////////////////////////
// OTHER
//////////////////////////////////////////////////////////////////////////////////////////
void Type_5()
{

}

void Type_6()
{

}

void OpenCloseFrame(int f, bool open)
{
	SetNodeUsing("RIDDLE_TEXT_" + f, open);
	SetNodeUsing("TYPE_" + f + "_ANSWER_1", open);
	SetNodeUsing("TYPE_" + f + "_ANSWER_1_VIDEO", open);
	SetNodeUsing("TYPE_" + f + "_ANSWER_2", open);
	SetNodeUsing("TYPE_" + f + "_ANSWER_2_VIDEO", open);
	SetNodeUsing("TYPE_" + f + "_OK", open);
	SetNodeUsing("TYPE_" + f + "_RESET", open);
	SetNodeUsing("FRAME_" + f, open);
}

