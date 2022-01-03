int iTypeCount = 0;

void InitInterface(string iniName)
{
    	GameInterface.title = "titleCreateNotice";
    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetBaseInterfaceData();

	HideButtons("_DONE", false, false);
	CheckCreateNotice();
	SetNoticeTypeInfo();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("IsCorrectNotice","IsCorrectNotice",0);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("IsCorrectNotice","IsCorrectNotice");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void IDoExitTwo(int exitCode, bool bCode)
{
	interfaceResultCommand = exitCode;
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("IsCorrectNotice","IsCorrectNotice");
	EndCancelInterface(bCode);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if(nodName == "STRING1_RESET" || nodName == "STRING2_RESET" || nodName == "STRING3_RESET" || nodName == "STRING4_RESET"
	|| nodName == "STRING5_RESET" || nodName == "STRING6_RESET" || nodName == "STRING7_RESET" || nodName == "STRING8_RESET"
	|| nodName == "STRING9_RESET" || nodName == "STRING10_RESET")
	{
		if(comName=="activate" || comName=="click")
		{
			ResetString(nodName);
		}
	}

	if(nodName == "STRING1_DONE" || nodName == "STRING2_DONE" || nodName == "STRING3_DONE" || nodName == "STRING4_DONE"
	|| nodName == "STRING5_DONE" || nodName == "STRING6_DONE" || nodName == "STRING7_DONE" || nodName == "STRING8_DONE"
	|| nodName == "STRING9_DONE" || nodName == "STRING10_DONE"
	|| nodName == "STRING1_DONE_OFF" || nodName == "STRING2_DONE_OFF" || nodName == "STRING3_DONE_OFF" || nodName == "STRING4_DONE_OFF"
	|| nodName == "STRING5_DONE_OFF" || nodName == "STRING6_DONE_OFF" || nodName == "STRING7_DONE_OFF" || nodName == "STRING8_DONE_OFF"
 	|| nodName == "STRING9_DONE_OFF"|| nodName == "STRING10_DONE_OFF")
	{
		if(comName=="activate" || comName=="click")
		{
			ChangeOffOrOn(nodName);
		}
	}

	switch(nodName)
	{
		case "EXIT":
			if(comName=="activate" || comName=="click")
			{
				PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
			}
		break;

		case "DONE":
			if(comName=="activate" || comName=="click")
			{
				CreateNotice();
			}
		break;

		case "RESET":
			if(comName=="activate" || comName=="click")
			{
				SetBaseInterfaceData();
			}
		break;

		case "ALL_DONE":
			if(comName=="activate" || comName=="click")
			{
				OffOnStrings(true);
			}
		break;

		case "ALL_RESET":
			if(comName=="activate" || comName=="click")
			{
				OffOnStrings(false);
			}
		break;

		case "DELETE_ALL_NOTICES":
			if(comName=="activate" || comName=="click")
			{
				DeleteQuestHeader("MyNotices");
			}
		break;

		case "JOURNAL_BUTTON":
			if(comName=="click")
			{
				IDoExitTwo(RC_INTERFACE_TO_LOGBOOK, true);
				return;
			}
		break;

		case "NOTICE_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectNoticeType(true);
			}
		break;

		case "NOTICE_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectNoticeType(false);
			}
		break;
	}
}

void AddQuestRecordInterface(string idQuest,string idReferenceQuest,string idText, string sText)
{
	if(CheckAttribute(pchar,"QuestInfo."+idQuest)==false)
	{
		SetQuestHeaderEx(idQuest,idReferenceQuest);
	}

	string sTextLbl = "l0";
	if( CheckAttribute(pchar,"QuestInfo."+idQuest+".Text") )
	{
		aref arTmp; makearef( arTmp, pchar.QuestInfo.(idQuest) );
		makearef(arTmp,pchar.QuestInfo.(idQuest).Text);
		sTextLbl = "l" + GetAttributesNum(arTmp);
	}
	if( sTextLbl != "" )
	{
		pchar.QuestInfo.(idQuest).Text.(sTextLbl) = "@"+idReferenceQuest+"@"+GetQuestBookData() + NewStr();
		pchar.QuestInfo.(idQuest).Text.(sTextLbl) = pchar.QuestInfo.(idQuest).Text.(sTextLbl) + sText;
		Log_SetStringToLog(XI_ConvertString("Logbook Update"));
		AddMsgToCharacter(pchar,MSGICON_LOGBOOK);
		PlayStereoSound("notebook");
	}

	SetQuestHeaderColor(idQuest, argb(255,255,128,255));
}

int IsCorrectNotice()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	int n,nLen;
	string str, sName;

	sName = GameInterface.(nodName).str;
	string sFullString;

	nLen = strlen(sName);
	for( n=0; n<nLen; n++ )
	{
		str = GetSymbol(&sName,n);
		sFullString += str;

		if(sFullString=="хуй" || sFullString=="пизда" || sFullString=="хуйпизда" || sFullString=="пидар" || sFullString=="пидр" || sFullString=="пидарас" || sFullString=="пидораз" || str=="пидорас"
		|| sFullString=="хуеплет" || sFullString=="хуеплёт" || sFullString=="ебалай" || sFullString=="сука" || sFullString=="падла" || sFullString=="чмо" || sFullString=="лох" || sFullString=="ебарь"
		|| sFullString=="ёбарь" || sFullString=="сукаблянах" || sFullString=="ипаныйрот" || sFullString=="жопа" || sFullString=="песда" || sFullString=="сцука" || sFullString=="сцуко" || str=="ебать"
		|| sFullString=="ебатьврот" || sFullString=="нахуй" || sFullString=="нах" || sFullString=="на хуй" || sFullString=="куй" || sFullString=="накуй" || str=="на куй" || sFullString=="ниибаццо"
		|| sFullString=="нивьипенный" || sFullString=="ебаный" || sFullString=="охуел" || sFullString=="охуела" || sFullString=="охуели" || sFullString=="пиздец" || sFullString=="соси" || sFullString=="сосать")
		{
			GameInterface.(nodName).str = "мат запрещён";
			return -1;
		}
	}

	return -1;
}

void SetBaseInterfaceData()
{
	CreateString(true,"StringsHeader", "Содержимое: ", FONT_CAPTION, argb(255,255,255,156), 335,40,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"Sbros_Done", "Вкл. / Выкл.", FONT_CAPTION, argb(255,255,255,156), 635,44,SCRIPT_ALIGN_CENTER,1.2);

	string sNode;
	for(int s=1; s <= 10; s++)
	{
		sNode = "NOTICE_WINDOW_" + s;
		GameInterface.(sNode).str = "пусто";
	}

	SetNewGroupPicture("CREATE_NOTICE_PICTURE", "CREATE_NOTICE_PAPER", "paper");
}

void SetNoticeTypeInfo()
{
	string sType = "";

	if(iTypeCount == 0)
	{
		sType = "Строка";
	}
	else
	{
		sType = "Столбец";
	}

	CreateString(true,"NoticeTypeStr", sType, FONT_CAPTION, argb(255,255,255,255), 635,523,SCRIPT_ALIGN_CENTER,1.2);
}

void OffOnStrings(bool bOn)
{
	string sButton;

	if(bOn)
	{
		sButton = "_DONE";
		HideButtons(sButton, true, false);

		sButton = "_DONE_OFF";
		HideButtons(sButton, false, false);
	}
	else
	{
		sButton = "_DONE_OFF";
		HideButtons(sButton, true, false);

		sButton = "_DONE";
		HideButtons(sButton, false, false);
	}

	CheckCreateNotice();
}

void HideButtons(string sButton, bool bOpen, bool bButton)
{
	string sNode;

	if(bButton)
	{
		SetNodeUsing(sButton, bOpen);
	}
	else
	{
		for(int b=1; b<=10; b++)
		{
			sNode = "STRING" + b;
			sNode += sButton;

			SetNodeUsing(sNode, bOpen);
			SetSelectable(sNode, bOpen);
		}
	}
}

void ResetString(string sNode)
{
	if(sNode == "STRING1_RESET") 		{ sNode = "NOTICE_WINDOW_1"; }
	if(sNode == "STRING2_RESET") 		{ sNode = "NOTICE_WINDOW_2"; }
	if(sNode == "STRING3_RESET") 		{ sNode = "NOTICE_WINDOW_3"; }
	if(sNode == "STRING4_RESET") 		{ sNode = "NOTICE_WINDOW_4"; }
	if(sNode == "STRING5_RESET") 		{ sNode = "NOTICE_WINDOW_5"; }
	if(sNode == "STRING6_RESET") 		{ sNode = "NOTICE_WINDOW_6"; }
	if(sNode == "STRING7_RESET") 		{ sNode = "NOTICE_WINDOW_7"; }
	if(sNode == "STRING8_RESET") 		{ sNode = "NOTICE_WINDOW_8"; }
	if(sNode == "STRING9_RESET") 		{ sNode = "NOTICE_WINDOW_9"; }
	if(sNode == "STRING10_RESET") 		{ sNode = "NOTICE_WINDOW_10"; }

	GameInterface.(sNode).str = "пусто";
}

void ChangeOffOrOn(string sNode)
{
	string sResultNode;

	if(sNode == "STRING1_DONE" || sNode == "STRING2_DONE" || sNode == "STRING3_DONE" || sNode == "STRING4_DONE"
	|| sNode == "STRING5_DONE" || sNode == "STRING6_DONE" || sNode == "STRING7_DONE" || sNode == "STRING8_DONE"
	|| sNode == "STRING9_DONE" || sNode == "STRING10_DONE")
	{
		SetNodeUsing(sNode, false);
		SetSelectable(sNode, false);

		sResultNode = sNode + "_OFF";
		SetNodeUsing(sResultNode, true);
		SetSelectable(sResultNode, true);
	}
	else
	{
		if(sNode == "STRING1_DONE_OFF" || sNode == "STRING2_DONE_OFF" || sNode == "STRING3_DONE_OFF" || sNode == "STRING4_DONE_OFF"
		|| sNode == "STRING5_DONE_OFF" || sNode == "STRING6_DONE_OFF" || sNode == "STRING7_DONE_OFF" || sNode == "STRING8_DONE_OFF"
		|| sNode == "STRING9_DONE_OFF" || sNode == "STRING10_DONE_OFF")
		{
			SetNodeUsing(sNode, false);
			SetSelectable(sNode, false);

			switch(sNode)
			{
				case "STRING1_DONE_OFF": sResultNode = "STRING1_DONE"; break;
				case "STRING2_DONE_OFF": sResultNode = "STRING2_DONE"; break;
				case "STRING3_DONE_OFF": sResultNode = "STRING3_DONE"; break;
				case "STRING4_DONE_OFF": sResultNode = "STRING4_DONE"; break;
				case "STRING5_DONE_OFF": sResultNode = "STRING5_DONE"; break;
				case "STRING6_DONE_OFF": sResultNode = "STRING6_DONE"; break;
				case "STRING7_DONE_OFF": sResultNode = "STRING7_DONE"; break;
				case "STRING8_DONE_OFF": sResultNode = "STRING8_DONE"; break;
				case "STRING9_DONE_OFF": sResultNode = "STRING9_DONE"; break;
				case "STRING10_DONE_OFF": sResultNode = "STRING10_DONE"; break;
			}

			SetNodeUsing(sResultNode, true);
			SetSelectable(sResultNode, true);
		}
	}

	CheckCreateNotice();
}

void CreateNotice()
{
	string sText, sNode, sButtonNode, sNodeText, sType;

	sText = "";

	if(iTypeCount == 1)
	{
		sType = "2";
		//sText += newStr() + sNodeText;
	}
	else
	{
		sType = "1";
		//sText += " " + sNodeText;
	}

	AddQuestRecordEx("MyNotices", "MyNotices", sType);

	for(int i=1; i<=10; i++)
	{
		sNode = "NOTICE_WINDOW_" + i;
		sButtonNode = "STRING" + i + "_DONE";

		if(GetSelectable(sButtonNode) == 0)
		{
			continue;
		}

		sNodeText = GameInterface.(sNode).str;

		if(sNodeText != "") // if(sNodeText != "пусто" && sNodeText != "")
		{
			AddQuestUserData("MyNotices", "sTextNum" + i, sNodeText);
		}
	}

	//AddQuestRecordInterface("MyNotices", "MyNotices", "1", sText);

	HideButtons("_DONE", false, false);
	HideButtons("_DONE_OFF", true, false);
	CheckCreateNotice();

	for(int s=1; s<=10; s++)
	{
		ResetString("STRING" + s + "_RESET");
	}
}

void CheckCreateNotice()
{
	int iCount = 0;
	string sButtonNode;

	for(int i=1; i <= 10; i++)
	{
		sButtonNode = "STRING" + i + "_DONE";

		if(GetSelectable(sButtonNode) == 0)
		{
			iCount++;
			continue;
		}

	}

	if(iCount == 10)
	{
		SetSelectable("DONE", false);
	}
	else
	{
		SetSelectable("DONE", true);
	}
}

void SelectNoticeType(bool bLeft)
{
	if(bLeft)
	{
		iTypeCount -= 1;
	}
	else
	{
		iTypeCount += 1;
	}

	if(iTypeCount > 1)
	{
		iTypeCount = 0;
	}

	if(iTypeCount < 0)
	{
		iTypeCount = 1;
	}

	SetNoticeTypeInfo();
}
