ref refNPCShipyard;
ref refStore;

int iYarderSkill = 100;
int iTunPoints = 8;
int iTimeMake, iShipPoints, iQBorders, iPriceOrder;
int iQMAX, iQMIN, iFreeSP, iFreeTP;
bool Tune_Sheme[10] = {0,0,0,0,0,0,0,0,0,0};//элементы 0(заголовок таблицы) и 2(паруса) пропускаем. просто для удобства
float Ship_Sheme[11] = {0.0,0.0,0.0,-1.0,0.0,0.0,0.0,0.0,0.0,0.0,-10.0};//тип флоат, чтоб не преобразовывать лишний раз при умножении на коэффициент, по факту - целые
int CannonTypes[16] = {1000,7,0,8,1,9,2,10,3,11,4,12,5,13,6,14};// #define CANNON_TYPE_CULVERINE_LBS8	0, #define CANNON_TYPE_CANNON_LBS8		7

string CurTable, CurRow, sNation;
int iSelected; // курсор в таблице
int FIS_FilterState = 7;
bool FState_Material = 0;
string sMessageMode, index;

int sundukSum;//на все апгрейды одинаковое колво сундуков	//chest
int Tun_Mater1[10];//кол-во товар
string Tun_Name1_Goods[10] = {"","Mahogany","","Planks","Silk","Linen","Cotton","Sandal","Leather","Ebony"};//0.HP.0.MAST.Speed.Turn.WAS.Capacity.Crew.Cannon
int Tun_Mater2[10];//кол-во предмет
string Tun_Name2_Items[10] = {"","jewelry17","","jewelry9","jewelry2","jewelry3","jewelry4","jewelry5","jewelry1","icollection"};
int Tun_Mater3[10];//кол-во деньги	//gold
string sAdd[10] = {"","\nкорпус: ","","\nмачты: ","\nскорость: ","\nманёвренность: ","\nбейдевинд: ","\nдэдвейт: ","\nкоманда: ","\nкалибр: "};
//сменить крестики на жемчуг?? jewelry9
int lastsort = 0;
bool blastsort;

void InitInterface_R(string iniName, ref _shipyarder)
{
	GameInterface.title = "titleShipyard";

	refNPCShipyard  = _shipyarder;
	sNation = GetNationNameByType(sti(refNPCShipyard.nation));
//TODO - надо ли брать нацию локации на случай захвата города(с одной стороны - чужие корабли будут делать, с другой - если вся карта захвачена - то везде одни и те же корабли)
//TODO - можно снимать ограничение нации квестом каким-нибудь - украсть чертежи кораблей других наций...

	if (refNPCShipyard.id != "Pirates_shipyarder") {iYarderSkill = (sti(refNPCShipyard.reputation) + 11)/2+50; iTunPoints = (iYarderSkill-8)/22;}
	//берём за навык кораблестроения репутацию верфиста и приводим к отрезку (56:100)

	iShipPoints = 6 + iYarderSkill/6 - (MOD_SKILL_ENEMY_RATE)/3;//целые переменные делятся с округлением вниз
	iQBorders = (iShipPoints+10)/3;
	if (iQBorders > 9) iQBorders = 9;
	iQMAX = iQBorders - 1;
	iQMIN = -iQBorders - 1;
	iFreeSP = iShipPoints;
	iFreeTP = iTunPoints;

	int iTest = FindColony(refNPCShipyard.City); // город магазина
	ref rColony;
	if (iTest != -1) {rColony = GetColonyByIndex(iTest);}
	refStore = &stores[sti(rColony.StoreNum)];

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("CheckButtonChange", "ProcessFilter", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);

	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,40,366,275); // tak from SHIP_BIG_PICTURE
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,246,361,1, 4);
	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,46,134,161);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,187,147,1, 4);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,166,147,1, 4);

	SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + refNPCShipyard.FaceId + ".tga");

	SetFormatedText("HERO_TEXT", "Мастерство корабела:\n\nПределы улучшений:\n\nБаллов улучшений:\n\nДоступно апгрейдов:");

	SetFormatedText("HERO_NAME", GetFullName(refNPCShipyard));
	SetFormatedText("HERO_RANK",refNPCShipyard.Rank);

	SetFormatedText("HERO_SKILL","" + iYarderSkill);
	SetFormatedText("HERO_QBORDERS", iQBorders*100/9 + "%");
	SetFormatedText("HERO_SHIPPOINTS",iFreeSP + "/" + iShipPoints);
	SetFormatedText("HERO_TUNPOINTS",iFreeTP + "/" + iTunPoints);

	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));

	FillShipyardTable();
	FillOrderShip(3);//шлюп на старте
	FillShipParam();
	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
	SetButtionsAccess();//доступность кнопки "Заказать"
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("CheckButtonChange", "ProcessFilter");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("OnTableClick", "OnTableClick");

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
		DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{

		case "B_SKILLUP":
			if (comName=="click")
			{
				IncShipQ(1);
			}
			if (comName=="rclick")
			{
				IncShipQ(8);
			}
		break;

		case "B_SKILLDOWN":
			if (comName=="click")
			{
				DecShipQ(1);
			}
			if (comName=="rclick")
			{
				DecShipQ(8);
			}
		break;

		case "BUTTON_BUY":
			if (comName=="click" || comName=="activate")
			{
				ShowMessageInfo();
			}
		break;

		case "MSG_OK":
			if (comName=="click" || comName=="activate")
			{
				DoBuyShip();
			}
		break;
	}
}

void FillOrderShip(int _iShipBaseType)
{
	int iShip = CreateBaseShip(_iShipBaseType);
	refNPCShipyard.Ship.Type = iShip;
	aref refShip;
	makearef(refShip, refNPCShipyard.Ship);

	if (!CheckAttribute(refShip,"soiling")) refShip.soiling = 0;//чтоб не срало в лог об отсутствии

	if(!CheckAttribute(refNPCShipyard, "ship.upgrades"))
	{
		refNPCShipyard.ship.upgrades.hull = 1;
		refNPCShipyard.ship.upgrades.sails = 1;
		refNPCShipyard.ship.upgrades.cannons = 1;
	}

	refShip.Pos.x = 0;
	refShip.Pos.y = 0;
	refShip.Pos.z = 0;
	refShip.Ang = "";
	refShip.Cannons.Charge.Type = GOOD_BALLS;

	if (!CheckAttribute(refShip,"Cannons.Type")) refShip.Cannons.Type = CANNON_TYPE_NONECANNON;
	if (!CheckAttribute(refShip,"Crew.Morale"))	refShip.Crew.Morale = 20 + rand(79);
	if (!CheckAttribute(refShip,"Crew.Quantity")) refShip.Crew.Quantity = 0;

	if(!CheckAttribute(refNPCShipyard, "ship.crew.Exp"))
	{
		refNPCShipyard.Ship.Crew.Exp.Sailors   = 1 + rand(80);
		refNPCShipyard.Ship.Crew.Exp.Cannoners = 1 + rand(80);
		refNPCShipyard.Ship.Crew.Exp.Soldiers  = 1 + rand(80);
	}
	refNPCShipyard.ship.crew.disease = 0;
	ResetShipCannonsDamages(refNPCShipyard);
	DeleteAttribute(refNPCShipyard, "Ship.Cargo");
	NullCharacterGoods(refNPCShipyard);
	SetRandomNameToShip(refNPCShipyard);
	SetCabinTypeEx(RealShips[iShip], sti(RealShips[iShip].Class));//рандом каюты //TODO - добавить в интерфейс выбор?
	//ещё вес корабля рандомиться может, но пока оставляю стандарт //TODO - добавить в интерфейс выбор?
}

void FillShipParam()
{
	int iShip = sti(refNPCShipyard.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		ref rRealShip = &RealShips[iShip];
		ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
		DeleteAttribute(rRealShip, "Tuning");//просто затираем записи об апгрейдах

		rRealShip.HP = stf(rBaseShip.HP) * (1 + Ship_Sheme[1]/100);
		rRealShip.MastMultiplier = stf(rBaseShip.MastMultiplier) - (Ship_Sheme[3]+1)/30;//прочность мачт без коэфф 0,8
		rRealShip.SpeedRate = stf(rBaseShip.SpeedRate) * (1 + Ship_Sheme[4]/100);
		rRealShip.TurnRate = stf(rBaseShip.TurnRate) * (1 + Ship_Sheme[5]/100);
		rRealShip.WindAgainstSpeed = stf(rBaseShip.WindAgainstSpeed) * (1 + Ship_Sheme[6]/100);
		rRealShip.Capacity = makeint(stf(rBaseShip.Capacity) * (1 + Ship_Sheme[7]/80));
		rRealShip.OptCrew = stf(rBaseShip.OptCrew) * (1 + Ship_Sheme[8]/60);
		rRealShip.MaxCrew = stf(rBaseShip.MaxCrew) * (1 + Ship_Sheme[8]/60);
		rRealShip.MinCrew = stf(rBaseShip.MinCrew) * (1 + Ship_Sheme[8]/60);//верно ли что минимальная команда в пять раз меньше оптимальной?
		rRealShip.MaxCaliber = rBaseShip.MaxCaliber;
		rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);

		refNPCShipyard.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		rRealShip.Price	= GetShipPriceByTTH(iShip, refNPCShipyard);//цена без пушек
		CalcTuningPrice();//стоимость апгрейда до применения апгрейдов считаем

		SetTuningStates2Ship(refNPCShipyard, 0, Tune_Sheme[7], Tune_Sheme[4], Tune_Sheme[8], Tune_Sheme[5], Tune_Sheme[1], Tune_Sheme[3]);//калибр тюнингуем отдельно, иначе несколько раз до 36 можно поднимать
		//void SetTuningStates2Ship(ref chr, bool MaxCaliber, bool Capacity, bool SpeedRate, bool MaxCrew, bool TurnRate, bool HP, bool MastMulti)
		SetShipWASTuning(refNPCShipyard, Tune_Sheme[6]);//бейдевинд

		int BaseCaliber = sti(rBaseShip.MaxCaliber);
		if (Tune_Sheme[9])//тюнинг калибра
		{
			switch (BaseCaliber)
			{
				case 8: rRealShip.MaxCaliber = 12; rRealShip.Tuning.Cannon = true; break;
				case 12: rRealShip.MaxCaliber = 16; rRealShip.Tuning.Cannon = true; break;
				case 16: rRealShip.MaxCaliber = 20; rRealShip.Tuning.Cannon = true; break;
				case 20: rRealShip.MaxCaliber = 24; rRealShip.Tuning.Cannon = true; break;
				case 24: rRealShip.MaxCaliber = 32; rRealShip.Tuning.Cannon = true; break;
				case 32: rRealShip.MaxCaliber = 36; rRealShip.Tuning.Cannon = true; break;
				case 42: SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 2, 9, 0);break;//снимаем чекбокс тюнинга
			}
		}

		int iQMAXTemp = 5;
		int curMaxCaliber = sti(rRealShip.MaxCaliber);
		switch (curMaxCaliber)
		{
		case 8: iQMAXTemp = -8; break;
		case 12: iQMAXTemp = -6; break;
		case 16: iQMAXTemp = -4; break;
		case 20: iQMAXTemp = -2; break;
		case 24: iQMAXTemp = 0; break;
		case 32: iQMAXTemp = 2; break;
		case 36: iQMAXTemp = 4; break;
		}
		if (Ship_Sheme[10] > iQMAXTemp) Ship_Sheme[10] = iQMAXTemp;//сбрасываем установленный тип орудий до максимально возможного для корабля (после смены корабля или снятия тюнинга калибра)
		refNPCShipyard.Ship.Cannons.Type = CannonTypes[makeint(Ship_Sheme[10])+10];

		refNPCShipyard.ship.hp = GetCharacterShipHP(refNPCShipyard);//прочность корпуса на максимум
		refNPCShipyard.ship.sp = 100;
		DeleteAttribute(refNPCShipyard,"ship.blots");//и пробоины убираем //а они могут тут быть???
		DeleteAttribute(refNPCShipyard,"ship.sails");
		DeleteAttribute(refNPCShipyard,"ship.masts");

		iTimeMake = 5 + sti(rRealShip.Price)/10000 + (iTunPoints - iFreeTP)*0.27;
		SetFormatedText("Time_TEXT", "Время постройки: " + iTimeMake + " д.");

		FillPrice();

		string sShip = rRealShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga");
		GameInterface.edit_box.str = refNPCShipyard.ship.name;
		SetFormatedText("SHIP_RANK", rRealShip.Class);
		SetShipOTHERTable("TABLE_OTHER", refNPCShipyard);
		SetShipQualityTable(refNPCShipyard, "BAR_HP", "BAR_Mast", "BAR_Speed", "BAR_TurnRate", "BAR_WAS", "BAR_Capacity", "BAR_Crew");
		SetFormatedText("FRAME_INFO_CAPTION", XI_ConvertString(sShip));
		SetFormatedText("INFO_TEXT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga");
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetFormatedText("FRAME_INFO_CAPTION","");
		SetFormatedText("INFO_TEXT","");
	}
	Table_UpdateWindow("TABLE_OTHER");

	HideSkillChanger();
	SetSkillArrows();
	SetButtionsAccess();
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;

	bool  bShowHint = true;

	ref rChr = refNPCShipyard;

	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			iShip = sti(rChr.ship.type);
			refBaseShip = CreateBaseShip(iShip);
			sHeader = XI_ConvertString(refBaseShip.BaseName);
			sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
			sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
			{
				ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
				sText2 = "Тип: " + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
				sText2 = sText2 + NewStr() + "Калибр: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
				sText2 = sText2 + NewStr() + "Дальность: "  + sti(Cannon.FireRange);
				sText2 = sText2 + NewStr() + "Урон: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
				sText2 = sText2 + NewStr() + "Перезарядка: "  + sti(GetCannonReloadTime(Cannon)) + " сек.";
				sText2 = sText2 + NewStr() + "Вес: "  + sti(Cannon.Weight) + " ц.";

				sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));

				sText3 = "Двойной клик или Enter по этому полю вызывает просмотр экипировки орудий по бортам.";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "Команды может быть больше максимальной, но это вызывает перегруз и условия жизни на корабле становятся ужасными, что влечет ежедневное падение морали. В среднем можно взять на борт до 25% больше матросов.";
				sText2 = sText2 + NewStr() + "Максимальное количество экипажа с учетом перегруза: " + GetMaxCrewQuantity(rChr);
			}
			// процент ремонта
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "Занято: " + FloatToString((stf(GetCargoLoad(rChr))  /  stf(GetCargoMaxSpace(rChr))) * 100.0, 1)+ " %";
			}
		break;
		case "TABLE_SHIPYARD" :
			sHeader = XI_Convertstring("Shipyard");
			sText1  = GetConvertStr("Shipyard_hint", "ShipsDescribe.txt");
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
	CurRow   =  "tr" + (iSelected);
	NullSelectTable("TABLE_OTHER");

	if (CurTable == "TABLE_SHIPYARD")
	{

		int iCurShip = RealShips[sti(refNPCShipyard.ship.type)].basetype;
		int iNewShip = sti(GameInterface.(CurTable).(CurRow).index);
		if (iNewShip == iCurShip) return;

		DeleteAttribute(&RealShips[sti(refNPCShipyard.Ship.Type)], "name");//при смене типа корабля помечаем предыдущий на удаление из массива реальных
		FillOrderShip(iNewShip);
	}
	FillShipParam();
}

void SetShipWASTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.WindAgainst"))
	{
		if(isSet)
			{
				rShip.WindAgainstSpeed   = FloatToString(stf(rShip.WindAgainstSpeed) + stf(rShip.WindAgainstSpeed) / (2*stf(rShip.Class)) + 0.005, 2);
				rShip.Tuning.WindAgainst = true;
			}
	}
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
		GameInterface.(sControl).select = 0;
		Table_UpdateWindow(sControl);
	}
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

void FillShipyardTable()
{
	Table_Clear("TABLE_SHIPYARD", false, true, false);

	GameInterface.TABLE_SHIPYARD.hr.td1.str = "Корабль";
	GameInterface.TABLE_SHIPYARD.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td2.str = "Класс";
	GameInterface.TABLE_SHIPYARD.hr.td2.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td3.str = "Орудия";
	GameInterface.TABLE_SHIPYARD.hr.td3.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td4.str = "Дедвейт";
	GameInterface.TABLE_SHIPYARD.hr.td4.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td5.str = "Скорость";
	GameInterface.TABLE_SHIPYARD.hr.td5.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td6.str = "Команда";
	GameInterface.TABLE_SHIPYARD.hr.td6.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;

	int	iStart = 0;
	int iEnd = -1;
	switch (FIS_FilterState)
	{
	case 7:
		{iStart = SHIP_BERMSLOOP; iEnd = SHIP_SP_SANFELIPE;}
	break;
	case 1:
		{iStart = SHIP_POSEIDON; iEnd = SHIP_SP_SANFELIPE;}
	break;
	case 2:
		{iStart = SHIP_GALEON50; iEnd = SHIP_HEAVYLINESHIP;}
	break;
	case 3:
		{iStart = SHIP_PINNACE; iEnd = SHIP_CARRACA;}
	break;
	case 4:
		{iStart = SHIP_BRIG; iEnd = SHIP_LYDIA;}
	break;
	case 5:
		{iStart = SHIP_POLACCA; iEnd = SHIP_SHNYAVA;}
	break;
	case 6:
		{iStart = SHIP_BERMSLOOP; iEnd = SHIP_SOPHIE;}
	break;
	}
	iEnd++;
	int k = 0;
	string sShip, sTemp;
	string row;
	aref aTemp;
	bool isCapital;
	if ( refNPCShipyard.city == "Tortuga" || refNPCShipyard.city == "Villemstad" || refNPCShipyard.city == "PortRoyal" || refNPCShipyard.city == "Havana" || refNPCShipyard.city == "Pirates") isCapital = 1; else isCapital = 0;

	for (i = iStart; i < iEnd; i++)
	{
		row = "tr" + (k+1);

		if (ShipsTypes[i].nation.(sNation))
		{
			if (i>=SHIP_FR_TRINITY && !isCapital) continue;//мановары только в столицах
		}
		else continue;//пропускаем корабли без нации верфиста

		sShip = shipstypes[i].Name;
		GameInterface.TABLE_SHIPYARD.(row).index = i;

		GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\\ships\\" + sShip + ".tga.tx";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 46;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 46;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "0, 1";
		GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "51,0";

		if (i >= SHIP_FR_TRINITY)
		{
			switch (sNation)
			{
			case "England": sTemp = " (нужен англ. патент)"; break;
			case "Spain": sTemp = " (нужен исп. патент)"; break;
			case "France": sTemp = " (нужен фран. патент)"; break;
			case "Holland": sTemp = " (нужен гол. патент)"; break;
			}
		}
		else sTemp = "";

		GameInterface.TABLE_SHIPYARD.(row).td1.str = XI_Convertstring(sShip) + sTemp;
		GameInterface.TABLE_SHIPYARD.(row).td1.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td1.scale = 0.82;
		GameInterface.TABLE_SHIPYARD.(row).td2.str = shipstypes[i].Class;
		GameInterface.TABLE_SHIPYARD.(row).td3.str = shipstypes[i].rcannon + "\n" + shipstypes[i].fcannon + "<::::::::::>" + shipstypes[i].bcannon + "\n" + shipstypes[i].lcannon;
		GameInterface.TABLE_SHIPYARD.(row).td4.str = shipstypes[i].Capacity;
		GameInterface.TABLE_SHIPYARD.(row).td5.str = floattostring(stf(shipstypes[i].Speedrate),1);
		GameInterface.TABLE_SHIPYARD.(row).td6.str = shipstypes[i].OptCrew;
		k++;
	}
	Table_UpdateWindow("TABLE_SHIPYARD");
}

void ProcessFilter()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
//========================================//
	if (sControl == "CLASS_ALL")
	{
	FIS_FilterState = 8 - iSelectedCB;
	FillShipyardTable();
	return;
	}
//========================================//
	if (sControl == "Check_Material")
	{
	FState_Material = iNewState;
	FillPrice();
	return;
	}
//========================================//
	if (sControl == "TunSheme")
	{
		bool bneedunlock = false;
		int i;
		if (!iFreeTP) bneedunlock = true;//было залочено

		if (iNewState) {iFreeTP--;} else {iFreeTP++; }
		Tune_Sheme[iSelectedCB] = iNewState;

		if (iFreeTP < 1 || bneedunlock)
		{
		for(i=1;i<10;i++)
			{
				if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 3, i)) continue;//нажатые кнопки не трогаем
				SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 5, i, !bneedunlock); //ненажатые блочим, если апгрейды кончились
			}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 5, 2, 1);//паруса всегда заблочены
		if (RealShips[refNPCShipyard.ship.type].MaxCaliber == 42) SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 5, 9, 1);
		}
		SetFormatedText("HERO_TUNPOINTS",iFreeTP + "/" + iTunPoints);
		FillShipParam();
		return;
	}
//========================================//
}

void SetButtionsAccess()
{
	int iShip = sti(refNPCShipyard.Ship.Type);
	int iClass = RealShips[iShip].Class;
	int iRank = sti(pchar.rank);
	string sText = "Заказать";
	if (iPriceOrder > sti(pchar.Money)) SetSelectable("BUTTON_BUY", false); else SetSelectable("BUTTON_BUY", true);

	if (iRank<4 && iClass<6) {SetSelectable("BUTTON_BUY", false); sText = "c 4 ранга";}
	if (iRank<9 && iClass<5) {SetSelectable("BUTTON_BUY", false); sText = "c 9 ранга";}
	if (iRank<14 && iClass<4) {SetSelectable("BUTTON_BUY", false); sText = "c 14 ранга";}
	if (iRank<19 && iClass<3) {SetSelectable("BUTTON_BUY", false); sText = "c 19 ранга";}
	if (iRank<29 && iClass<2) {SetSelectable("BUTTON_BUY", false); sText = "c 29 ранга";}
	if (refNPCShipyard.id != "Pirates_shipyarder" && sti(RealShips[iShip].basetype) >= SHIP_FR_TRINITY && !CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(refNPCShipyard.nation))) && sText == "Заказать")
	{SetSelectable("BUTTON_BUY", false); sText = "нет патента";}
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BUTTON_BUY", 0, "#" + sText);
}

void ShowMessageInfo()
{
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));
	SetFormatedText("MSG_WINDOW_TEXT", "Заказать корабль за " + FindRussianMoneyString(iPriceOrder) + "?");
	SetSelectable("MSG_OK", true);
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_CANCEL");
}

void GetBortName(string _sBort, string _sBort_real, int BortNumb)
{
	if (BortNumb == 1) {_sBort = "rcannon"; _sBort_real = "cannonr"; return;}
	if (BortNumb == 2) {_sBort = "lcannon"; _sBort_real = "cannonl"; return;}
	if (BortNumb == 3) {_sBort = "fcannon"; _sBort_real = "cannonf"; return;}
	if (BortNumb == 4) {_sBort = "bcannon"; _sBort_real = "cannonb"; return;}
}

void DoBuyShip()
{
	AddMoneyToCharacter(pchar, -iPriceOrder);
	AddCharacterExpToSkill(pchar, "Commerce", GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) / 700.0);//опыт торговли надо начислять только за корабль? За апгрейды и пушки не начисляется?
	WaitDate("",0,0,0, 0, 35);
	Statistic_AddValue(pchar, "BuyShip", 1);
	Statistic_AddValue(Pchar, "Money_spend", iPriceOrder);

	pchar.ShipInOrder = sti(pchar.ShipInOrder) + 1;//TODO - Проверить, может ли верфист исчезнуть-умереть и добавить там проверок закрытия стройки корабля
	SaveCurrentNpcQuestDateParam(refNPCShipyard,"questTemp.ShipOrderDate");
	refNPCShipyard.questTemp.ShipOrderTime = iTimeMake;
	refNPCShipyard.questTemp.NPCid = NPC_GenerateCharacter("ShipOrder", "PKM_rab_"+(rand(3)+1), "man", "man", rand(5)+1, refNPCShipyard.nation, -1, false);//непись для хранения заказанного корабля
	ref chref = GetCharacter(sti(refNPCShipyard.questTemp.NPCid));
	chref.id = chref.id + "_" + chref.index; //меняем ID на оригинальный
	DeleteAttribute(chref,"ship");
	chref.ship = "";

	aref	arTo, arFrom;
	makearef(arTo, chref.ship);
	makearef(arFrom, refNPCShipyard.Ship);
	CopyAttributes(arTo, arFrom);
	chref.location = "";
	chref.location.group = "";
	chref.location.locator = "";

	if (Ship_Sheme[10] == -10) //если пушки не выбраны, ставим 8фт и обнуляем их кол-во
	{
		int maxQty;
		string sBort, sBort_real, attr;

		chref.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS8;

		sBort = "rcannon";
		sBort_real = "cannonr";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
		sBort = "lcannon";
		sBort_real = "cannonl";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
		sBort = "fcannon";
		sBort_real = "cannonf";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
		sBort = "bcannon";
		sBort_real = "cannonb";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
	}

	string sTemp, sTemp2;
	if (!FState_Material && iFreeTP<iTunPoints)//запоминаем число нужных материалов и записываем их судовой журнал
	{
		int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
		sTemp = "Кроме того, для особых усовершенствований корабля мне нужно будет доставить следующие материалы: ";
		for (int i=1; i<10; i++)
		{
		if (i==2) continue;
		if (Tune_Sheme[i])
			{
			sTemp2 = Tun_Name1_Goods[i];
			refNPCShipyard.questTemp.(sTemp2) = Tun_Mater1[i];
			sTemp += XI_ConvertString(sTemp2) + " - " + Tun_Mater1[i] + "шт., ";
			sTemp2 = Tun_Name2_Items[i];
			refNPCShipyard.questTemp.(sTemp2) = Tun_Mater2[i];
			sTemp += LanguageConvertString(idLngFile, Items[FindItem(Tun_Name2_Items[i])].name) + " - " + Tun_Mater2[i] + "шт., ";
			}
		else
			{
			sTemp2 = Tun_Name1_Goods[i];
			refNPCShipyard.questTemp.(sTemp2) = 0;
			sTemp2 = Tun_Name2_Items[i];
			refNPCShipyard.questTemp.(sTemp2) = 0;
			}
		}
		refNPCShipyard.questTemp.chest = sundukSum*(iTunPoints-iFreeTP);
		sTemp += "сундуков с монетами - " + sundukSum*(iTunPoints-iFreeTP) + " шт.";
	}
	else sTemp = "";

	string sTitle = "ShipOrder";
	ReOpenQuestHeader(sTitle);
	AddQuestRecordEx(sTitle, "ShipOrder", "t1");
	AddQuestUserData(sTitle, "sName", GetFullName(refNPCShipyard));
	AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + refNPCShipyard.city + "Gen"));
	AddQuestUserData(sTitle, "sShipType", XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(refNPCShipyard.ship.type)].basetype), "Name")));
	AddQuestUserData(sTitle, "money", iPriceOrder);
	AddQuestUserData(sTitle, "time", iTimeMake);
	AddQuestUserData(sTitle, "TuningMaterial", sTemp);

	DeleteAttribute(refNPCShipyard,"ship");
	refNPCShipyard.ship = "";
	ProcessExitCancel();
}

void IncShipQ(int _add)
{
	if (CurTable != "TABLE_OTHER") return;

	int iQMAXTemp = iQMAX;
	int iFreeSPTemp = iFreeSP;
	if (iSelected == 10) //если выбран тип пушек
	{
		iFreeSPTemp = 10;//выбор типа орудий не тратит очки апгрейда
		int curCaliber = sti(RealShips[sti(refNPCShipyard.ship.type)].MaxCaliber);
		iQMAXTemp = 5;//42 фт
		switch (curCaliber)
		{
		case 8: iQMAXTemp = -8; break;
		case 12: iQMAXTemp = -6; break;
		case 16: iQMAXTemp = -4; break;
		case 20: iQMAXTemp = -2; break;
		case 24: iQMAXTemp = 0; break;
		case 32: iQMAXTemp = 2; break;
		case 36: iQMAXTemp = 4; break;
		}
	}

	if (iFreeSPTemp < _add) _add = iFreeSPTemp;
	if ((Ship_Sheme[iSelected] + _add) > iQMAXTemp)
	{
		_add = iQMAXTemp - Ship_Sheme[iSelected];
	}
	if (_add > 0)
	{
		Ship_Sheme[iSelected] += _add;
		if (iSelected-10) iFreeSP -= _add;//если строка 10, то свободные баллы не меняем
	}
	else return;
	FillShipParam();
	SetFormatedText("HERO_SHIPPOINTS",iFreeSP + "/" + iShipPoints);
}

void DecShipQ(int _add)
{
	if (CurTable != "TABLE_OTHER") return;
	int iQMINTemp = iQMIN;

	if (iSelected == 10) iQMINTemp = -10;//если строка 10, то нижний предел всегда максимальный

	if ((Ship_Sheme[iSelected] - _add) < iQMINTemp)
	{
		_add = Ship_Sheme[iSelected] - iQMINTemp;
	}
	if (_add > 0)
	{
		Ship_Sheme[iSelected] -= _add;
		if (iSelected-10) iFreeSP += _add;//если строка 10, то свободные баллы не меняем
	}
	else return;
	FillShipParam();
	SetFormatedText("HERO_SHIPPOINTS",iFreeSP + "/" + iShipPoints);
}

void HideSkillChanger()
{
	SetNodeUsing("B_SKILLUP",  false);
	SetNodeUsing("B_SKILLDown",  false);
}

void SetSkillArrows()
{
	if (CurTable == "TABLE_OTHER")
	{
		if (iSelected == 2) return;//на парусах не включаем
		if (iSelected == 9) return;//на калибре тоже

		int iQMINTemp = iQMIN;
		int iQMAXTemp = iQMAX;
		int iFreeSPTemp = iFreeSP;
		if (iSelected == 10) //тип пушек
		{
			iFreeSPTemp = 1;//выбор типа орудий не тратит очки апгрейда
			iQMINTemp = -10;//минимум - без пушек

			int curCaliber = sti(RealShips[sti(refNPCShipyard.ship.type)].MaxCaliber);
			iQMAXTemp = 5;//42 фт
			switch (curCaliber)
			{
			case 8: iQMAXTemp = -8; break;
			case 12: iQMAXTemp = -6; break;
			case 16: iQMAXTemp = -4; break;
			case 20: iQMAXTemp = -2; break;
			case 24: iQMAXTemp = 0; break;
			case 32: iQMAXTemp = 2; break;
			case 36: iQMAXTemp = 4; break;
			}
		}

		if (Ship_Sheme[iSelected] > iQMINTemp)
		{
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 237,298 + 26*(iSelected-1), 258, 319 + 26*(iSelected-1), 0);
			SetNodeUsing("B_SKILLDown", true);
		}

		if (iFreeSPTemp > 0 && Ship_Sheme[iSelected] < iQMAXTemp)
		{
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 258,298 + 26*(iSelected-1), 279, 319 + 26*(iSelected-1), 0);
			SetNodeUsing("B_SKILLUP",  true);
		}
	}
}

void FillPrice()
{
	int iShip = sti(refNPCShipyard.ship.type);
	ref rRealShip = &RealShips[iShip];
	int iTemp, i, k, m;
	string row, sGood;
	iPriceOrder =  GetShipBuyPrice(iShip, refNPCShipyard);
	string stextPRICE = "Цена корабля: " + MakeMoneyShow(iPriceOrder, MONEY_SIGN, MONEY_DELIVER);

	if (Ship_Sheme[10] != -10.0)
	{
	iTemp = GetStoreGoodsPrice(refStore, GetCannonGoodsIdxByType(sti(refNPCShipyard.Ship.Cannons.Type)), PRICE_TYPE_BUY, pchar, sti(rRealShip.CannonsQuantity));
	stextPRICE += "\nЦена пушек: " + MakeMoneyShow(iTemp, MONEY_SIGN, MONEY_DELIVER);
	iPriceOrder += iTemp;
	}
	else stextPRICE += "\n";

	if (iFreeTP < iTunPoints)
	{
	SetNodeUsing("TABLE_TUN", !FState_Material);//показать/скрыть таблицу с материалами
	SetNodeUsing("SCROLL_TUN", !FState_Material);
	SetNodeUsing("Money_TEXT4", !FState_Material);
		if (FState_Material)
		{
			stextPRICE += "\n\n\n";
			for (k=1;k<10;k++)
			{
				if(Tune_Sheme[k])
				{
				iTemp = Tun_Mater3[k];
				iTemp += GetStoreGoodsPrice(refStore, FindGood(Tun_Name1_Goods[k]), PRICE_TYPE_BUY, pchar, Tun_Mater1[k]);
				iTemp += Tun_Mater2[k] * GetTradeItemPrice(FindItem(Tun_Name2_Items[k]), PRICE_TYPE_BUY);
				stextPRICE += sAdd[k] + MakeMoneyShow(iTemp, MONEY_SIGN, MONEY_DELIVER);
				iPriceOrder += iTemp;
				}
			}
		}
		else
		{
			Table_Clear("TABLE_TUN", false, true, false);
			GameInterface.TABLE_TUN.hr.td1.str = "Материал";//заголовок скрываю, но если его не объявлять первая строчка не будет показываться
			GameInterface.TABLE_TUN.hr.td2.str = "Кол-во";

			int Tun_Mater3_sum = 0;
			int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
			i = 1;
			for (k=1;k<10;k++)
			{
			if (Tune_Sheme[k])
				{
				row = "tr" + i;
		 		sGood = Tun_Name1_Goods[k];
				GameInterface.TABLE_TUN.(row).td1.icon.group = "GOODS";
				GameInterface.TABLE_TUN.(row).td1.icon.image = sGood;
				GameInterface.TABLE_TUN.(row).td1.icon.offset = "-3, -1";
				GameInterface.TABLE_TUN.(row).td1.icon.width = 20;
				GameInterface.TABLE_TUN.(row).td1.icon.height = 20;
				GameInterface.TABLE_TUN.(row).td1.textoffset = "17,0";
				GameInterface.TABLE_TUN.(row).td1.str = XI_ConvertString(sGood);
				GameInterface.TABLE_TUN.(row).td1.scale = 0.85;
				GameInterface.TABLE_TUN.(row).td1.align = "left";
				GameInterface.TABLE_TUN.(row).td2.str = Tun_Mater1[k];
				GameInterface.TABLE_TUN.(row).td2.scale = 0.85;
				i++;
				row = "tr" + i;
				m = FindItem(Tun_Name2_Items[k]);
				GameInterface.TABLE_TUN.(row).td1.icon.group = Items[m].picTexture;
				GameInterface.TABLE_TUN.(row).td1.icon.image = "itm" + Items[m].picIndex;
				GameInterface.TABLE_TUN.(row).td1.icon.offset = "-2,0";
				GameInterface.TABLE_TUN.(row).td1.icon.width = 18;
				GameInterface.TABLE_TUN.(row).td1.icon.height = 18;
				GameInterface.TABLE_TUN.(row).td1.textoffset = "17,0";
				GameInterface.TABLE_TUN.(row).td1.scale = 0.70;
				GameInterface.TABLE_TUN.(row).td1.align = "left";
				GameInterface.TABLE_TUN.(row).td1.str = LanguageConvertString(idLngFile, Items[m].name);
				GameInterface.TABLE_TUN.(row).td2.str = Tun_Mater2[k];
				GameInterface.TABLE_TUN.(row).td2.scale = 0.85;
				i++;
				Tun_Mater3_sum += Tun_Mater3[k];
				}
			}
				row = "tr" + i;
				m = FindItem("Chest");
				GameInterface.TABLE_TUN.(row).td1.icon.group = Items[m].picTexture;
				GameInterface.TABLE_TUN.(row).td1.icon.image = "itm" + Items[m].picIndex;
				GameInterface.TABLE_TUN.(row).td1.icon.offset = "-2, 0";
				GameInterface.TABLE_TUN.(row).td1.icon.width = 18;
				GameInterface.TABLE_TUN.(row).td1.icon.height = 18;
				GameInterface.TABLE_TUN.(row).td1.textoffset = "17,0";
				GameInterface.TABLE_TUN.(row).td1.scale = 0.85;
				GameInterface.TABLE_TUN.(row).td1.align = "left";
				GameInterface.TABLE_TUN.(row).td1.str = LanguageConvertString(idLngFile, Items[m].name);
				GameInterface.TABLE_TUN.(row).td2.str = sundukSum*(iTunPoints - iFreeTP);
				GameInterface.TABLE_TUN.(row).td2.scale = 0.85;

			Table_UpdateWindow("TABLE_TUN");
			SetFormatedText("Money_TEXT4", "Аванс за апгрейды: " + MakeMoneyShow(Tun_Mater3_sum, MONEY_SIGN, MONEY_DELIVER));
			iPriceOrder += Tun_Mater3_sum;
		}
	}
	else
	{
	SetNodeUsing("TABLE_TUN", false);//скрыть таблицу с материалами
	SetNodeUsing("SCROLL_TUN", false);
	SetNodeUsing("Money_TEXT4", false);
	}

	SetFormatedText("Money_TEXT3", stextPRICE);
	SetFormatedText("Money_TEXT2", "Общая стоимость: " + MakeMoneyShow(iPriceOrder, MONEY_SIGN, MONEY_DELIVER));
}

void CalcTuningPrice()
{
	int iShipT = refNPCShipyard.ship.type;
	int cannonQ = sti(RealShips[iShipT].CannonsQuantity);
	int shipClass = sti(RealShips[iShipT].Class);
	int shipCapacity = sti(RealShips[iShipT].Capacity);
	float shipSpeedRate = stf(RealShips[iShipT].SpeedRate);
	float MastMulti = stf(RealShips[iShipT].MastMultiplier);
	int shipMaxCrew = sti(RealShips[iShipT].MaxCrew);
	int shipHP		= sti(RealShips[iShipT].HP);
	float shipTurnRate = stf(RealShips[iShipT].TurnRate);
	float shipWindAgainst = stf(RealShips[iShipT].WindAgainstSpeed);

	float fQuestShip = 1.0;
	if(CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "QuestShip")) fQuestShip = 1.2;

	sundukSum = 7-shipClass;

	int i = 1;//HP
	Tun_Mater1[i] = makeint((35 * (7-shipClass) + shipHP * 7/100) * fQuestShip);
	Tun_Mater2[i] = makeint(5 * ((7-shipClass)*3) * fQuestShip);
	Tun_Mater3[i] = makeint((shipHP * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i = i + 2;//MAST
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 70 * (7-shipClass)) * fQuestShip);
	Tun_Mater2[i] = makeint(5 * (7-shipClass) * fQuestShip);
	Tun_Mater3[i] = makeint((100 * MastMulti * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i++;//Speed
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 70 * (7-shipClass)) * fQuestShip);
	Tun_Mater2[i] = makeint(5 * (7-shipClass) * fQuestShip);
	Tun_Mater3[i] = makeint((100 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i++;//Turn
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 375/shipClass+20) * fQuestShip);
	Tun_Mater2[i] = makeint((5 * (7-shipClass)+2) * fQuestShip);
	Tun_Mater3[i] = makeint((30 * shipTurnRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i++;//Wind
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 750/shipClass+20) * fQuestShip);
	Tun_Mater2[i] = makeint((6 * (7-shipClass)+1) * fQuestShip);
	Tun_Mater3[i] = makeint((300 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i++;//capacity
	Tun_Mater1[i] = makeint((35 * (7-shipClass) + shipCapacity * 7/100) * fQuestShip);
	Tun_Mater2[i] = makeint((10 * (7-shipClass)+10) * fQuestShip);
	Tun_Mater3[i] = makeint((2 * shipCapacity * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i++;//MaxCrew
	Tun_Mater1[i] = makeint((shipMaxCrew * 6/10 + 50 * (7-shipClass)) * fQuestShip);
	Tun_Mater2[i] = makeint((6 * (7-shipClass)+3) * fQuestShip);
	Tun_Mater3[i] =  makeint((15 * shipMaxCrew * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	i++;//cannon
	Tun_Mater1[i] = makeint((cannonQ * 2 + 35 * (7-shipClass) - 20) * fQuestShip);
	Tun_Mater2[i] = makeint((7-shipClass)/2 * fQuestShip);
	if (Tun_Mater2[i] < 1) Tun_Mater2[i] = 1;
	Tun_Mater3[i] = makeint((100 * cannonQ * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
	if (sControl == "TABLE_SHIPYARD")
		{
		if (!SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, sControl, 1 ))
			{
			if (iColumn == 3) return;//эти колонки не сортируем
			if (lastsort == iColumn) {bLastSort = !bLastSort;} else {lastsort = iColumn; bLastSort = 1;}

			if (iColumn == 1)
				SortTable(sControl, iColumn, 1, bLastSort, -1);//текст
			else
				SortTable(sControl, iColumn, 0, !bLastSort, -1);//числа
			}
		Table_UpdateWindow(sControl);
		}
}
