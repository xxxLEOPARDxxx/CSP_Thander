int checkingstagenum = 10;
int pickposition = 90;
int openingcount = 0;

int correctposition;

string wrenchtex, picktex;
string chestID;

bool openingstarted = false;
bool cylinderstarted = false;
bool lockclick = false;
bool g_bToolTipStarted = false;

bool	LckPckngProcessBooster	 = true;

bool firsttime;
bool opened = false;
bool broken = false;

bool mousechangepos = true;
string mpos;
string ompos;

void InitInterface_gm(string iniName)
{
	string sHeader = "TEST";

	string sText1, sText2, sText3;
	LAi_SetActorTypeNoGroup(pchar);
	locCameraSleep(true);
	SetTimeScale(0.0);

	if(LckPckngProcessBooster == false) EngineLayersOffOn(true);
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("eSlideChange","procSlideChange",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);

	if (CheckAttribute(pchar, "questTemp.lockpicking.firsttime"))
	{
		if(makeint(pchar.questTemp.lockpicking.firsttime) == 1) firsttime = true;
		else firsttime = false;
	}
	else
	{
		firsttime = true;
	}

	PlaySound("interface\lockpicking\ui_lockpicking_enter_01.wav"); // Звук начала процедуры
	chestID = pchar.questTemp.lockpicking.ID;

	correctposition = 1+rand(179);

	if(correctposition < 15) correctposition = 15;
	if(correctposition > 165) correctposition = 165;

	sHeader = "Вскрытие замков";
	sText1 = "Взлом замков позволяет открыть некоторые закрытые сундуки, чтобы заполучить их содержимое. Вскрытие производится путем подбора правильного положения отмычки, вставленной в цилиндр. Клавиша 'Ctrl' - поворот цилиндра. Движение мыши по вертикали - смена угла вставленной отмычки. Клавиша 'Esc' - выход.");
	sText2 = "Передвигая мышь вверх-вниз, подбирайте положение отмычки. Когда ее угол выбран, нажмите и удерживайте клавишу 'Ctrl' для того, чтобы начать вращать цилиндр. Для открытия замка необходимо, чтобы цилиндр был повернут на 90 градусов."
	sText3 = "Если цилиндр в процессе вращения неожиданно остановился, это значит, что положение отмычки выбрано неправильно. В этом случае, отпустите клавишу 'Ctrl' и дождитесь, когда цилиндр вернется в исходное положение, чтобы разблокировать отмычку. Помните, чем ближе к правильному положению вы выставите отмычку, тем на больший угол цилиндр будет повернут.";

	if(firsttime == true) CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), "none", "none", "none", 64, 64);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

    switch(nodName)
	{

	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();
}

void IProcessFrame()
{
	int randsound;
	int squeaksound;
	int randclicksound;

	int difference;
	float dmultiplier;

	float mouseposition;
	int movsound;

	if (CheckAttribute(GameInterface,"mousepos")) mouseposition = 600.0-(stf(GameInterface.mousepos.y));

	if(mouseposition > 600) mouseposition = 600;
	if(mouseposition < 9) mouseposition = 9;

	pickposition = mouseposition*0.3;
	picktex = "interfaces\LockPicking\pick\" + makeint(pickposition/2) + ".tga";
	SetNewPicture("PICK_PIC",picktex);

	if(lockclick == false)
	{
		SetRealMouseSensitivity();
	}
	else
	{
		XI_SetMouseSensitivity(0.0, 0.0);
	}

	if(checkingstagenum < 460)
	{
		if(mousechangepos == false)
		{
			mpos = GameInterface.mousepos.y;

			if(mpos != ompos)
			{
				if(rand(20) == 0)
				{
					movsound = rand(11)+1;

					if(movsound < 10) PlaySound("interface\lockpicking\mov\ui_lockpicking_pickmovement_0"+ movsound +".wav");
					else PlaySound("interface\lockpicking\mov\ui_lockpicking_pickmovement_"+ movsound +".wav");
				}
			}

			mousechangepos = true;
		}

		if(mousechangepos == true)
		{
			if (CheckAttribute(GameInterface,"mousepos")) ompos = GameInterface.mousepos.y;
			mousechangepos = false;
		}
	}

	if(checkingstagenum < 460)
	{
		if((pickposition - correctposition) <= 0) difference = correctposition - pickposition;
		else difference = pickposition - correctposition;

		dmultiplier = makefloat(difference)/180.0;

		if(XI_IsKeyPressed("control")) // Двигаем цилиндр, если нажата кнопка Ctrl
		{
			checkingstagenum = checkingstagenum + 10;

			if(cylinderstarted == false) // Звук начала поворота цилиндра
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = true;
			}
		}
		else // Если кнопка не нажата, то возвращаем в исходное положение
		{
			checkingstagenum = checkingstagenum - 10;

			if(cylinderstarted == true) // Звук начала поворота цилиндра
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = false;
			}
		}

		if(makeint(dmultiplier*100.0) > 2)
		{
			if(checkingstagenum > makeint((1.0 - dmultiplier)*460.0))
			{
				checkingstagenum = makeint((1.0 - dmultiplier)*460.0);

				if(lockclick == false)
				{
					lockclick = true;

					randclicksound = rand(2)+1;
					PlaySound("interface\lockpicking\cylstop\ui_lockpicking_cylinderstop_0"+ randclicksound +".wav");
					if (rand(20)==0 && pickposition != 0)
					{
						broken = true;
						IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
					}
				}

			}
		}

		if(checkingstagenum > 460) checkingstagenum = 460;

		if(checkingstagenum < 10)
		{
			checkingstagenum = 10;
			lockclick = false;
		}

		if(checkingstagenum == 460) OpenProcedure(); // Если цилиндр повернут на 90 градусов, то запускаем процесс открытия

		if(checkingstagenum != 10 && checkingstagenum != 460 && checkingstagenum != makeint((1.0 - dmultiplier)*460.0)) // Поскрипывания цилиндра при его движении
		{
			if(rand(160) == 0)
			{
				squeaksound = rand(11)+1;

				if(squeaksound < 10) PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_0"+ squeaksound +".wav");
				else PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_"+ squeaksound +".wav");
			}
		}

		// Меняем визуальное положение цилиндра
		wrenchtex = "interfaces\LockPicking\wrench\" + makeint(checkingstagenum/10) + ".tga";
		SetNewPicture("WRENCH_PIC",wrenchtex);
	}

	if(openingstarted == true)
	{
		openingcount = openingcount + 4;

		if(openingcount > 200)
		{
			openingstarted = false;
			opened = true;

			SetNodeUsing("BACK_PIC",false);
			SetNodeUsing("LOCK_PIC",false);
			SetNodeUsing("WRENCH_PIC",false);
			SetNodeUsing("PICK_PIC",false);
			SetNodeUsing("PICKSLIDE",false);

			OpenChest();
		}
	}
}

void OpenProcedure() // Процесс открытия
{
	int randsound = rand(2)+1;

	openingstarted = true;
	PlaySound("interface\lockpicking\ui_lockpicking_unlock_0"+ randsound +".wav"); // Звук щелчка замка
}

void OpenChest()
{
	AddCharacterExpToSkill(PChar, "Fortune", 50);
	AddCharacterExpToSkill(PChar, "Repair", 50);
	TakeItemFromCharacter(pchar, chestID);
	pchar.questTemp.chestcount = sti(pchar.questTemp.chestcount) + 1;
	// Открываем достижения
	if(sti(pchar.questTemp.chestcount) >= 5) UnlockAchievement("AchChest", 1);
	if(sti(pchar.questTemp.chestcount) >= 15) UnlockAchievement("AchChest", 2);
	if(sti(pchar.questTemp.chestcount) >= 30) UnlockAchievement("AchChest", 3);
	string nameitm[35];
	int itmq[35];
	int value;
	int value_alt;
	switch (chestID)
	{
		case "Chest_treasure":
			value = chest_treasure[sti(pchar.Chest_treasure)];
			pchar.Chest_treasure = sti(pchar.Chest_treasure) + 1;
			if (sti(pchar.Chest_treasure) > 99) pchar.Chest_treasure = 0;
			value_alt = chest_treasure2[sti(pchar.Chest_treasure2)];
			pchar.Chest_treasure2 = sti(pchar.Chest_treasure2) + 1;
			if (sti(pchar.Chest_treasure2) > 99) pchar.Chest_treasure2 = 0;
		break;
		case "Chest_Craftsmans":
			value = chest_craftsmans[sti(pchar.Chest_Craftsmans)];
			pchar.Chest_Craftsmans = sti(pchar.Chest_Craftsmans) + 1;
			if (sti(pchar.Chest_Craftsmans) > 99) pchar.Chest_Craftsmans = 0;
			value_alt = chest_craftsmans2[sti(pchar.Chest_Craftsmans2)];
			pchar.Chest_Craftsmans2 = sti(pchar.Chest_Craftsmans2) + 1;
			if (sti(pchar.Chest_Craftsmans2) > 99) pchar.Chest_Craftsmans2 = 0;
		break;
		case "Chest_ammo":
			value = chest_ammo[sti(pchar.chest_ammo)];
			pchar.chest_ammo = sti(pchar.chest_ammo) + 1;
			if (sti(pchar.chest_ammo) > 99) pchar.chest_ammo = 0;
			value_alt = chest_ammo2[sti(pchar.chest_ammo2)];
			pchar.chest_ammo2 = sti(pchar.chest_ammo2) + 1;
			if (sti(pchar.chest_ammo2) > 99) pchar.chest_ammo2 = 0;
		break;
		case "Chest_quest":
			value = chest_quest[sti(pchar.Chest_quest)];
			pchar.Chest_quest = sti(pchar.Chest_quest) + 1;
			if (sti(pchar.Chest_quest) > 99) pchar.Chest_quest = 0;
			value_alt = chest_quest2[sti(pchar.Chest_quest2)];
			pchar.Chest_quest2 = sti(pchar.Chest_quest2) + 1;
			if (sti(pchar.Chest_quest2) > 99) pchar.Chest_quest2 = 0;
		break;
	}
	int value2 = 999 - value;
	int value3 = 999 - value_alt;
	//В каждом сундуке может сгенерироваться до 10 предметов (массивы с индексом от 0 до 9) по текущей логике. Задействовано максимум 4 слота пока.

	if(chestID == "Chest_treasure") // Малый
	{
		switch (makeint(value/111))
		{
			case 0:
				nameitm[1] = "jewelry4"; // Изумруд
				itmq[1] = 10;
				nameitm[2] = "jewelry8"; // Бронзовое кольцо
				itmq[2] = 10;
				nameitm[3] = "jewelry9"; // Бронзовый крестик
				itmq[3] = 10;
				nameitm[4] = "jewelry15"; // Изумрудные подвески
				itmq[4] = 10;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 4000*(sti(PChar.rank)/2);
			break;
			case 1:
				nameitm[1] = "jewelry1"; // Сапфир
				itmq[1] = 10;
				nameitm[2] = "jewelry2"; // Алмаз
				itmq[2] = 10;
				nameitm[3] = "jewelry3"; // Рубин
				itmq[3] = 10;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 18000*(sti(PChar.rank)/2);
			break;
			case 2:
				nameitm[1] = "jewelry5"; // Золотой слиток
				itmq[1] = 4;
				nameitm[2] = "jewelry6"; // Серебряное кольцо с сапфиром
				itmq[2] = 9;
				nameitm[3] = "jewelry7"; // Золотое кольцо с изумрудом
				itmq[3] = 8;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 12000*(sti(PChar.rank)/2);
			break;
			case 3:
				nameitm[1] = "jewelry10"; // Золотое кольцо с сапфиром
				itmq[1] = 10;
				nameitm[2] = "jewelry11"; // Большая жемчужина
				itmq[2] = 10;
				nameitm[3] = "jewelry12"; // Маленькая жемчужина
				itmq[3] = 10;
				nameitm[4] = "jewelry13"; // Камея
				itmq[4] = 10;
				nameitm[5] = "jewelry14"; // Золотая брошь
				itmq[5] = 10;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 6000*(sti(PChar.rank)/2);
			break;
			case 4:
				nameitm[1] = "jewelry16"; // Ожерелье
				itmq[1] = 10;
				nameitm[2] = "jewelry17"; // Серебряный слиток
				itmq[2] = 5;
				nameitm[3] = "jewelry18"; // Золотое кольцо с рубином
				itmq[3] = 3;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 16000*(sti(PChar.rank)/2);
			break;
			case 5:
				nameitm[1] = "jewelry5"; // Золотой слиток
				itmq[1] = 7;
				nameitm[2] = "jewelry7"; // Золотое кольцо с изумрудом
				itmq[2] = 8;
				nameitm[3] = "jewelry10"; // Золотое кольцо с сапфиром
				itmq[3] = 10;
				nameitm[4] = "jewelry14"; // Золотая брошь
				itmq[4] = 10;
				nameitm[5] = "jewelry18"; // Золотое кольцо с рубином
				itmq[5] = 6;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 10000*(sti(PChar.rank)/2);
			break;
			case 6:
				nameitm[1] = "jewelry6"; // Серебряное кольцо с сапфиром
				itmq[1] = 20;
				nameitm[2] = "jewelry17"; // Серебряный слиток
				itmq[2] = 20;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 20000*(sti(PChar.rank)/2);
			break;
			case 7:
				nameitm[1] = "jewelry6"; // Серебряное кольцо с сапфиром
				itmq[1] = 15;
				nameitm[2] = "jewelry7"; // Золотое кольцо с изумрудом
				itmq[2] = 15;
				nameitm[3] = "jewelry8"; // Бронзовое кольцо
				itmq[3] = 15;
				nameitm[4] = "jewelry10"; // Золотое кольцо с сапфиром
				itmq[4] = 15;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 7000*(sti(PChar.rank)/2);
			break;
			case 8:
				nameitm[1] = "jewelry5"; // Золотой слиток
				itmq[1] = 25;
				nameitm[2] = "jewelry11"; // Большая жемчужина
				itmq[2] = 25;
				nameitm[3] = "jewelry12"; // Маленькая жемчужина
				itmq[3] = 25;
				nameitm[4] = "jewelry17"; // Серебряный слиток
				itmq[4] = 25;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 1000*(sti(PChar.rank)/2);
			break;
			case 9:
				nameitm[1] = "jewelry8"; // Бронзовое кольцо
				itmq[1] = 10;
				nameitm[2] = "jewelry9"; // Бронзовый крестик
				itmq[2] = 10;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 15000*(sti(PChar.rank)/2);
			break;
			case 10:
				nameitm[1] = "jewelry8"; // Бронзовое кольцо
				itmq[1] = 10;
				nameitm[2] = "jewelry9"; // Бронзовый крестик
				itmq[2] = 10;
				nameitm[9] = "gold"; // Золото
				itmq[9] = 15000*(sti(PChar.rank)/2);
			break;
		}
		if (itmq[0] > 0) itmq[0] += makeint(value/50);
		if (itmq[1] > 0) itmq[1] += makeint(value/50);
		if (itmq[2] > 0) itmq[2] += makeint(value/50);
		if (itmq[3] > 0) itmq[3] += makeint(value/50);
		if (itmq[4] > 0) itmq[4] += makeint(value/50);
		if (itmq[5] > 0) itmq[5] += makeint(value/50);
		itmq[9] += makeint(value/3);
		if (value < 100) {nameitm[3] = "Mineral2"; itmq[3] = 1;}
		if (value >= 200 && value < 400) {nameitm[3] = "Mineral4"; itmq[3] = 1;}
		if (value >= 800) {nameitm[3] = "Mineral8"; itmq[3] = 1;}
	}

	if(chestID == "Chest_Craftsmans") // Ремесленника
	{
		switch (makeint(value/83))
		{
			case 0:
				nameitm[1] = "CompCraft_Parchment"; // Бумага
				itmq[1] = 150;
			break;
			case 1:
				nameitm[1] = "CompCraft_Nails"; // Гвозди
				itmq[1] = 50;
				nameitm[2] = "CompCraft_Lead"; // Свинец
				itmq[2] = 12;
				nameitm[3] = "CompCraft_Grindstone"; // Оселок
				itmq[3] = 5+(sti(PChar.rank));
			break;
			case 2:
				nameitm[1] = "CompCraft_Magnesium"; // Магний
				itmq[1] = 10;
				nameitm[2] = "CompCraft_Flint"; // Кремень
				itmq[2] = 11;
				nameitm[3] = "CompCraft_Copper"; // Медь
				itmq[3] = 15;
				nameitm[4] = "CompCraft_Sulfur"; // Сера
				itmq[4] = 17;
			break;
			case 3:
				nameitm[1] = "CompCraft_SulfurCrush"; // Измельчённая сера
				itmq[1] = 30;
				nameitm[2] = "CompCraft_PowderMixture"; // Пороховая смесь
				itmq[2] = 31;
				nameitm[3] = "CompCraft_Parchment"; // Бумага
				itmq[3] = 32;
			break;
			case 4:
				nameitm[1] = "CompCraft_Nails"; // Гвозди
				itmq[1] = 200;
				nameitm[2] = "CompCraft_Parchment"; // Бумага
				itmq[2] = 100;
			break;
			case 5:
				nameitm[1] = "CompCraft_Copper"; // Медь
				itmq[1] = 83;
			break;
			case 6:
				nameitm[1] = "CompCraft_Flint"; // Кремень
				itmq[1] = 45+(sti(PChar.rank)*2);
			break;
			case 7:
				nameitm[1] = "CompCraft_Magnesium"; // Магний
				itmq[1] = 57;
			break;
			case 8:
				nameitm[1] = "CompCraft_Nails"; // Гвозди
				itmq[1] = 10;
				nameitm[2] = "CompCraft_Magnesium"; // Магний
				itmq[2] = 10;
				nameitm[3] = "CompCraft_Flint"; // Кремень
				itmq[3] = 10;
				nameitm[4] = "CompCraft_Lead"; // Свинец
				itmq[4] = 10;
				nameitm[5] = "CompCraft_Copper"; // Медь
				itmq[5] = 10;
				nameitm[6] = "CompCraft_Sulfur"; // Сера
				itmq[6] = 10;
				nameitm[7] = "CompCraft_SulfurCrush"; // Измельчённая сера
				itmq[7] = 10;
				nameitm[8] = "CompCraft_PowderMixture"; // Пороховая смесь сера
				itmq[8] = 10;
				nameitm[9] = "CompCraft_Parchment"; // Бумага
				itmq[9] = 10;
				nameitm[10] = "CompCraft_Grindstone"; // Оселок
				itmq[10] = 5+(sti(PChar.rank));
			break;
			case 9:
				nameitm[1] = "CompCraft_SulfurCrush"; // Измельчённая сера
				itmq[1] = 100;
				nameitm[2] = "CompCraft_PowderMixture"; // Пороховая смесь сера
				itmq[2] = 100;
			break;
			case 10:
				nameitm[1] = "CompCraft_Grindstone"; // Оселок
				itmq[1] = 15+(sti(PChar.rank));
			break;
			case 11:
				nameitm[1] = "slave_01"; // Гарпун
				itmq[1] = 15+(sti(PChar.rank)*2);
			break;
			case 12:
				nameitm[1] = "CompCraft_Grindstone"; // Оселок
				itmq[1] = 11+(sti(PChar.rank));
				nameitm[2] = "slave_01"; // Гарпун
				itmq[2] = 12+(sti(PChar.rank));
			break;
			case 13:
				nameitm[1] = "CompCraft_Grindstone"; // Оселок
				itmq[1] = 11+(sti(PChar.rank)*2);
				nameitm[2] = "slave_01"; // Гарпун
				itmq[2] = 12+(sti(PChar.rank)*2);
			break;
		}
		if (itmq[0] > 0) itmq[0] += makeint(value/50);
		if (itmq[1] > 0) itmq[1] += makeint(value/50);
		if (itmq[2] > 0) itmq[2] += makeint(value/50);
		if (itmq[3] > 0) itmq[3] += makeint(value/50);
		if (itmq[4] > 0) itmq[4] += makeint(value/50);
		if (itmq[5] > 0) itmq[5] += makeint(value/50);
		if (itmq[6] > 0) itmq[6] += makeint(value/50);
		if (itmq[7] > 0) itmq[7] += makeint(value/50);
		if (itmq[8] > 0) itmq[8] += makeint(value/50);
		if (itmq[9] > 0) itmq[9] += makeint(value/50);
		if (itmq[10] > 0) itmq[10] += makeint(value/50);

		if (value < 333) {nameitm[11] = "CompCraft_HealthTobacco"; itmq[11] = 1;}
		if (value >= 333 && value < 666) {nameitm[12] = "CompCraft_EnergyTobacco"; itmq[12] = 1;}
		if (value >= 666) {nameitm[13] = "CompCraft_StrengthTobacco"; itmq[13] = 1;}
		if (value >= 700) {nameitm[14] = "CompCraft_Scissors"; itmq[14] = 1;}
	}

	if(chestID == "Chest_ammo") // Снаряжение
	{
		switch (makeint(value/59)) // от 0 до 14
		{
			case 0:
				nameitm[1] = "bullet"; // Свинцовые пули
				itmq[1] = 37+(sti(PChar.rank)*2);
				nameitm[2] = "gunpowder"; // Гранулированный порох
				itmq[2] = 35+(sti(PChar.rank)*2);
				nameitm[4] = "grapeshot"; // Картечь
				itmq[4] = 33+(sti(PChar.rank)*2);
				nameitm[5] = "cartridge"; // Бумажный патрон
				itmq[5] = 31+(sti(PChar.rank)*2);
			break;
			case 1:
				nameitm[1] = "bullet"; // Свинцовые пули
				itmq[1] = 52+(sti(PChar.rank)*2);
				nameitm[2] = "gunpowder"; // Гранулированный порох
				itmq[2] = 55+(sti(PChar.rank)*2);
			break;
			case 2:
				nameitm[1] = "bullet"; // Свинцовые пули
				itmq[1] = 154;
				nameitm[2] = "gunpowder"; // Гранулированный порох
				itmq[2] = 151;
			break;
			case 3:
				nameitm[1] = "grapeshot"; // Картечь
				itmq[1] = 53;
				nameitm[2] = "cartridge"; // Бумажный патрон
				itmq[2] = 31;
			break;
			case 4:
				nameitm[1] = "grapeshot"; // Картечь
				itmq[1] = 155;
				nameitm[2] = "cartridge"; // Бумажный патрон
				itmq[2] = 101;
			break;
			case 5:
				nameitm[1] = "powder_pellet"; // Петарда
				itmq[1] = 10+(sti(PChar.rank)*2);
				nameitm[2] = "grenade"; // Граната
				itmq[2] = 5+(sti(PChar.rank)*2);
			break;
			case 6:
				nameitm[1] = "powder_pellet"; // Петарда
				itmq[1] = 32;
				nameitm[2] = "grenade"; // Граната
				itmq[2] = 15;
			break;
			case 7:
				nameitm[1] = "powder_pellet"; // Петарда
				itmq[1] = 50+(sti(PChar.rank));
			break;
			case 8:
				nameitm[2] = "grenade"; // Граната
				itmq[2] = 32+(sti(PChar.rank));
			break;
			case 9:
				nameitm[1] = "harpoon"; // Стрела
				itmq[1] = 16+(sti(PChar.rank)*2);
			break;
			case 10:
				nameitm[1] = "harpoon"; // Стрела
				itmq[1] = 26;
			break;
			case 11:
				nameitm[1] = "GunEchin"; // Ежовый заряд
				itmq[1] = 15+(sti(PChar.rank)*2);
			break;
			case 12:
				nameitm[1] = "GunEchin"; // Ежовый заряд
				itmq[1] = 28;
			break;
			case 13:
				nameitm[1] = "bullet"; // Свинцовые пули
				itmq[1] = 52+(sti(PChar.rank));
				nameitm[2] = "gunpowder"; // Гранулированный порох
				itmq[2] = 54+(sti(PChar.rank));
				nameitm[3] = "grapeshot"; // Картечь
				itmq[3] = 31+(sti(PChar.rank));
				nameitm[4] = "cartridge"; // Бумажный патрон
				itmq[4] = 23+(sti(PChar.rank));
				nameitm[5] = "powder_pellet"; // Петарда
				itmq[5] = 11+(sti(PChar.rank));
				nameitm[6] = "grenade"; // Граната
				itmq[6] = 5+(sti(PChar.rank));
				nameitm[7] = "harpoon"; // Стрела
				itmq[7] = 5+(sti(PChar.rank));
				nameitm[8] = "GunEchin"; // Ежовый заряд
				itmq[8] = 5+(sti(PChar.rank));
			break;
			case 14:
				nameitm[1] = "potion1"; // Лечебное зелье
				itmq[1] = 31+(sti(PChar.rank));
				nameitm[2] = "potion2"; // Эликсир
				itmq[2] = 15+(sti(PChar.rank));
				nameitm[3] = "potionrum"; // Бутылка рома
				itmq[3] = 23+(sti(PChar.rank));
			break;
			case 15:
				nameitm[1] = "potion1"; // Лечебное зелье
				itmq[1] = 72+(sti(PChar.rank));
			break;
			case 16:
				nameitm[1] = "potion2"; // Эликсир
				itmq[1] = 31+(sti(PChar.rank));
			break;
			case 17:
				nameitm[1] = "potionrum"; // Бутылка рома
				itmq[1] = 43+(sti(PChar.rank));
			break;
			case 18:
				nameitm[3] = "potionrum"; // Бутылка рома
				itmq[3] = 43+(sti(PChar.rank));
			break;
		}
		if (itmq[0] > 0) itmq[0] += makeint(value/50);
		if (itmq[1] > 0) itmq[1] += makeint(value/50);
		if (itmq[2] > 0) itmq[2] += makeint(value/50);
		if (itmq[3] > 0) itmq[3] += makeint(value/50);
		if (itmq[4] > 0) itmq[4] += makeint(value/50);
		if (itmq[5] > 0) itmq[5] += makeint(value/50);
		if (itmq[6] > 0) itmq[6] += makeint(value/50);
		if (itmq[7] > 0) itmq[7] += makeint(value/50);
		if (itmq[8] > 0) itmq[8] += makeint(value/50);
		if (itmq[9] > 0) itmq[9] += makeint(value/50);
		if (value >= 800) {nameitm[9] = "GunCap_colt"; itmq[9] = 5;}
	}

	if(chestID == "Chest_quest") // Странный
	{
		switch (makeint(value/62))
		{
			case 0:
				nameitm[0] = "indian4"; // Глиняный кувшин
				itmq[0] = 1;
				nameitm[1] = "indian8"; // Серебряный кубок
				itmq[1] = 1;
				nameitm[2] = "indian9"; // Алебастровый сосуд
				itmq[2] = 1;
				nameitm[3] = "indian13"; // Древняя курительница
				itmq[3] = 1;
				nameitm[4] = "indian16"; // Раскрашенный сосуд
				itmq[4] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 9000*(sti(PChar.rank)/2);
			break;
			case 1:
				nameitm[0] = "indian3"; // Нефритовая маска
				itmq[0] = 1;
				nameitm[1] = "indian5"; // Двойная маска
				itmq[1] = 1;
				nameitm[2] = "indian10"; // Оберег Эхекатля
				itmq[2] = 1;
				nameitm[3] = "indian2"; // Пугающая фигурка
				itmq[3] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 10000*(sti(PChar.rank)/2);
			break;
			case 2:
				nameitm[0] = "indian6"; // Амулет Шиукоатля
				itmq[0] = 1;
				nameitm[1] = "indian7"; // Идол Великой Матери
				itmq[1] = 1;
				nameitm[2] = "indian12"; // Кубок-тотем Тепейоллотля
				itmq[2] = 1;
				nameitm[3] = "indian14"; // Чаша Ололиуки
				itmq[3] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 11000*(sti(PChar.rank)/2);
			break;
			case 3:
				nameitm[0] = "indian18"; // Идол Атлауа
				itmq[0] = 1;
				nameitm[1] = "indian19"; // Статуэтка Тлалока
				itmq[1] = 1;
				nameitm[2] = "indian21"; // Церемониальный сосуд
				itmq[2] = 1;
				nameitm[3] = "indian22"; // Голова воина племени майя
				itmq[3] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 12000*(sti(PChar.rank)/2);
			break;
			case 4:
				nameitm[0] = "indian15"; // Базальтовая голова
				itmq[0] = 1;
				nameitm[1] = "indian17"; // Тельная ладанка
				itmq[1] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 13000*(sti(PChar.rank)/2);
			break;
			case 5:
				nameitm[0] = "indian1"; // Оберег Тлальчитонатиу
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 27000*(sti(PChar.rank)/2);
			break;
			case 6:
				nameitm[0] = "indian2"; // Пугающая фигурка
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 36000*(sti(PChar.rank)/2);
			break;
			case 7:
				nameitm[0] = "indian3"; // Нефритовая маска
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 25000*(sti(PChar.rank)/2);
			break;
			case 8:
				nameitm[0] = "indian5"; // Двойная маска
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 24000*(sti(PChar.rank)/2);
			break;
			case 9:
				nameitm[0] = "indian6"; // Амулет Шиукоатля
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 14000*(sti(PChar.rank)/2);
			break;
			case 10:
				nameitm[0] = "indian7"; // Идол Великой Матери
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 15000*(sti(PChar.rank)/2);
			break;
			case 11:
				nameitm[0] = "indian12"; // Кубок-тотем Тепейоллотля
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 16000*(sti(PChar.rank)/2);
			break;
			case 12:
				nameitm[0] = "indian14"; // Чаша Ололиуки
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 17000*(sti(PChar.rank)/2);
			break;
			case 13:
				nameitm[0] = "indian18"; // Идол Атлауа
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 18000*(sti(PChar.rank)/2);
			break;
			case 14:
				nameitm[0] = "indian19"; // Статуэтка Тлалока
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 19000*(sti(PChar.rank)/2);
			break;
			case 15:
				nameitm[0] = "indian21"; // Церемониальный сосуд
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 23000*(sti(PChar.rank)/2);
			break;
			case 16:
				nameitm[0] = "indian22"; // Голова воина племени майя
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 22000*(sti(PChar.rank)/2);
			break;
			case 17:
				nameitm[0] = "indian22"; // Голова воина племени майя
				itmq[0] = 1;
				nameitm[30] = "gold"; // Золото
				itmq[30] = 21000*(sti(PChar.rank)/2);
			break;
		}
		itmq[30] += makeint(value/3);

        if (value >= 1 && value < 80) {nameitm[15] = "BackPack2"; itmq[15] = 1;}     		// Обычный рюкзак
        if (value_alt >= 80 && value_alt < 160) {nameitm[15] = "BackPack3"; itmq[15] = 1;}  // Хороший рюкзак
        if (value2 >= 160 && value2 < 240) {nameitm[15] = "BackPack4"; itmq[15] = 1;} 		// Отличный рюкзак

        if (value3 >= 240 && value3 < 320) {nameitm[15] = "cirass2"; itmq[15] = 1;}     	// Рейтарский панцирь
        if (value >= 320 && value < 400) {nameitm[15] = "cirass3"; itmq[15] = 1;}     		// Гвардейская кираса
        if (value_alt >= 400 && value_alt < 480) {nameitm[15] = "cirass4"; itmq[15] = 1;}   // Офицерская кираса

        if (value2 >= 480 && value2 < 560) {nameitm[15] = "Totem_1"; itmq[15] = 1;}     	// Тотем Шочикецаль
        if (value3 >= 560 && value3 < 640) {nameitm[15] = "Totem_2"; itmq[15] = 1;}     	// Тотем Миктлантекутли
        if (value >= 640 && value < 720) {nameitm[15] = "Totem_3"; itmq[15] = 1;}     		// Тотем Кецалькоатля
        if (value_alt >= 720 && value_alt < 800) {nameitm[15] = "Totem_4"; itmq[15] = 1;}   // Тотем Мишкоатля
        if (value2 >= 800 && value2 < 880) {nameitm[15] = "Totem_7"; itmq[15] = 1;}     	// Тотем Уицилопочтли
        if (value3 >= 880 && value3 < 999) {nameitm[15] = "Totem_8"; itmq[15] = 1;}     	// Тотем Тлалока

        if (value >= 1 && value < 40) {nameitm[16] = "blade19"; itmq[16] = 1;}     			// Маринера ЛО
        if (value_alt >= 40 && value_alt < 80) {nameitm[16] = "blade22"; itmq[16] = 1;}     // Испанская рапира ЛО
        if (value2 >= 80 && value2 < 120) {nameitm[16] = "blade36"; itmq[16] = 1;}     		// Саксенфедер ЛО
        if (value3 >= 120 && value3 < 160) {nameitm[16] = "blade37"; itmq[16] = 1;}     	// Персидская сабля ЛО

        if (value >= 160 && value < 200) {nameitm[16] = "blade31"; itmq[16] = 1;}     		// Шамшир СО
        if (value_alt >= 200 && value_alt < 240) {nameitm[16] = "blade34"; itmq[16] = 1;}   // Скаллоп СО
        if (value2 >= 240 && value2 < 280) {nameitm[16] = "blade39"; itmq[16] = 1;}    		// Скимитар СО
        if (value3 >= 280 && value3 < 320) {nameitm[16] = "blade40"; itmq[16] = 1;}    		// Мадонна СО
        if (value >= 320 && value < 360) {nameitm[16] = "blade46"; itmq[16] = 1;}    		// Офицерский клеванг СО

        if (value_alt >= 360 && value_alt < 400) {nameitm[16] = "blade15"; itmq[16] = 1;}   // Сторта ТО
        if (value2 >= 400 && value2 < 440) {nameitm[16] = "blade21"; itmq[16] = 1;}    		// Бастард ТО
        if (value3 >= 440 && value3 < 480) {nameitm[16] = "blade202"; itmq[16] = 1;}     	// Цвайхандер ТО
        if (value >= 480 && value < 520) {nameitm[16] = "blade42"; itmq[16] = 1;}     		// Кханда ТО
        if (value_alt >= 520 && value_alt < 560) {nameitm[16] = "topor2"; itmq[16] = 1;}    // Рейтарский чекан ТО

        if (value2 >= 560 && value2 < 600) {nameitm[16] = "blade23"; itmq[16] = 1;}       	// Бретта ЛО
        if (value3 >= 600 && value3 < 640) {nameitm[16] = "blade32"; itmq[16] = 1;}     	// Фламберж ЛО
        if (value >= 640 && value < 680) {nameitm[16] = "blade26"; itmq[16] = 1;}     		// Паппенхаймер ЛО

        if (value_alt >= 680 && value_alt < 720) {nameitm[16] = "blade30"; itmq[16] = 1;}   // Нобиль СО
        if (value2 >= 720 && value2 < 760) {nameitm[16] = "blade24"; itmq[16] = 1;}     	// Чиавона СО
        if (value3 >= 760 && value3 < 800) {nameitm[16] = "blade25"; itmq[16] = 1;}     	// Карабела СО

        if (value >= 800 && value < 840) {nameitm[16] = "blade13"; itmq[16] = 1;}     		// Кракемарт ТО
        if (value_alt >= 840 && value_alt < 880) {nameitm[16] = "blade20"; itmq[16] = 1;}   // Клейбэг ТО
        if (value2 >= 880 && value2 < 920) {nameitm[16] = "blade33"; itmq[16] = 1;}     	// Валлонская шпага ТО
        if (value3 >= 920 && value3 < 999) {nameitm[16] = "blade28"; itmq[16] = 1;}     	// Танат ТО

		if (value >= 1 && value < 150) {nameitm[17] = "pistol_grapebok"; 		itmq[17] = 1;} // Трёхствольный дробовик
		if (value_alt >= 200 && value_alt < 350) {nameitm[17] = "pistol6"; 		itmq[17] = 1;} // Бок-пистолет
		if (value2 >= 400 && value2 < 550) {nameitm[17] = "pistol9"; 			itmq[17] = 1;} // Двузарядный пистолет
		if (value3 >= 600 && value3 < 750) {nameitm[17] = "pistol4"; 			itmq[17] = 1;} // Четырёхствольный пистолет
		if (value >= 800 && value < 900) {nameitm[17] = "pistol5"; 				itmq[17] = 1;} // Бретерский пистолет
		if (value_alt >= 900 && value_alt < 950) {nameitm[17] = "mushket"; 		itmq[17] = 1;} // Фитильный мушкет
		if (value >= 950 && value < 999) {nameitm[17] = "mushket_drob"; 		itmq[17] = 1;} // Аркебуза

		if (value >= 10 && value < 30) {nameitm[18] = "mushket_spanish"; 			itmq[18] = 1;} // Испанский мушкетон
		if (value_alt >= 150 && value_alt < 170) {nameitm[18] = "mushket_english"; 	itmq[18] = 1;} // Английский мушкетон
		if (value >= 600 && value < 620) {nameitm[18] = "mushket_france"; 			itmq[18] = 1;} // Французcкий мушкетон
		if (value_alt >= 900 && value_alt < 920) {nameitm[18] = "mushket_holland"; 	itmq[18] = 1;} // Голландский мушкетон
	}
	// LEO: Вот выскажусь. Как же я заебался впиливать эту ссаную херню с сундуками. А вот всякие хейтеры потом будут подпёздывать, что мы тип ток готовое пиздим. Сукины вы дети. Если бы вы знали, сколько мы делаем уже эти ёбанные сундуки (и это ток сундуки), чтобы они были ахуенно разнообразны и избавив вас от сейвскама, чтобы вы не могли рандомить их.
	// LEO: Вот реально, я рот эбал эту рутину. Чот в 2013 году, когда я начинал моделить кораблики в иксах и делал это каждый день и всирал кучу времени, мне тогда было как то похуй. Сейчас чот мне как то немного жалко потраченного времени, конкретно на такую вот рутину. Но сук, это же и для себя делается в первую очередь. Один раз сделать ЗБС и потом играть-кайфовать. Т.ч. я всё еще в деле и едем дальше :)
	// LEO: Ну и да, без Gregg я бы тут вообще лицо сломал фейспалмом с этой логики и кода в целом. Но оно всё работает и работает как швейцарские часы.
	for (i = 0; i < 35; i++)
	{
		if (itmq[i] == 0) continue;
		if(nameitm[i] != "")
		{
			if(nameitm[i] == "gold") AddMoneyToCharacter(pchar, itmq[i]);
			else
			{
		    	if(HasSubstr(nameitm[i], "blade"))TakeNItems(pchar, GetGeneratedItem(nameitm[i]), itmq[i]);
		    	else TakeNItems(pchar, nameitm[i], itmq[i]);
			}

			if(i == 0) nameitm[i] = "- " + GetConvertStr("itmname_"+nameitm[i], "ItemsDescribe.txt") + " в количестве " + itmq[i];
			else nameitm[i] = NewStr() + "- " + GetConvertStr("itmname_"+nameitm[i], "ItemsDescribe.txt") + " в количестве " + itmq[i];
		}
	}

	TakeNItems(pchar, "Lockpick", -1);
	EngineLayersOffOn(true);
	CreateTooltip("#" + "Содержимое сундука", "Вы открыли сундук и нашли следующие предметы:", argb(255,255,255,255), "", argb(255,255,192,192), nameitm[0]+nameitm[1]+nameitm[2]+nameitm[3]+nameitm[4]+nameitm[5]+nameitm[6]+nameitm[7]+nameitm[8]+nameitm[9]+nameitm[10]+nameitm[11]+nameitm[12]+nameitm[13]+nameitm[14]+nameitm[15]+nameitm[16]+nameitm[17]+nameitm[18]+nameitm[19]+nameitm[20]+nameitm[21]+nameitm[22]+nameitm[23]+nameitm[24]+nameitm[25]+nameitm[26]+nameitm[27]+nameitm[28]+nameitm[29]+nameitm[30], argb(255,255,255,255), "", argb(255,255,255,255), "none", "none", "none", 64, 64);
}

void ShowInfo()
{
	if(firsttime == false && opened == false)
	{
		g_bToolTipStarted = true;
		string sHeader = "TEST";
		string sNode = GetCurrentNode();

		string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
		sPicture = "none";
		sGroup = "none";
		sGroupPicture = "none";

		switch (sNode)
		{
			case "BACK_PIC":
				sHeader = "Вскрытие замков";
				sText1 = "Взлом замков позволяет открыть некоторые закрытые сундуки, чтобы заполучить их содержимое. Вскрытие производится путем подбора правильного положения отмычки, вставленной в цилиндр. Клавиша 'Ctrl' - поворот цилиндра. Движение мыши по вертикали - смена угла вставленной отмычки. Клавиша 'Esc' - выход.");
				sText2 = "Передвигая мышь вверх-вниз, подбирайте положение отмычки. Когда ее угол выбран, нажмите и удерживайте клавишу 'Ctrl' для того, чтобы начать вращать цилиндр. Для открытия замка необходимо, чтобы цилиндр был повернут на 90 градусов."
				sText3 = "Если цилиндр в процессе вращения неожиданно остановился, это значит, что положение отмычки выбрано неправильно. В этом случае, отпустите клавишу 'Ctrl' и дождитесь, когда цилиндр вернется в исходное положение, чтобы разблокировать отмычку. Помните, чем ближе к правильному положению вы выставите отмычку, тем на больший угол цилиндр будет повернут.";
			break;
		}

		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfo()
{
	if(firsttime == false && opened == false)
	{
		if( g_bToolTipStarted )
		{
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("PICKSLIDE");
		}
	}
}

void ProcessCancelExit()
{
	if(openingstarted == false)
	{
		if(firsttime == false || opened == true)
		{
			CloseTooltip();
			IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
		}
		else
		{
			firsttime = false;
			pchar.questTemp.lockpicking.firsttime = false;
			CloseTooltip();
			SetCurrentNode("PICKSLIDE");
		}
	}
}

void IDoExit(int exitCode, bool bClear)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("eSlideChange","procSlideChange");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");

	LAi_SetPlayerType(pchar);
	SetRealMouseSensitivity();

	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);

	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DeleteAttribute(pchar, "pause");
	DelPerkFromActiveList("TimeSpeed");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME )
	{
		DeleteEntitiesByType("scrshoter");
	}

	if((rand(99)+1) <= 10*(MOD_SKILL_ENEMY_RATE/2) && opened == false) // доработка взлома. Шанс поломки отмычки при отмене взлома
    {
	    TakeNItems(pchar, "Lockpick", -1);
	    PlaySound("interface\lockpicking\lockpick_breaks.wav"); // Звук поломки
	    Log_info("А-а-ать, Черт! Отмычка сломалась!");
	}
	else
	{
		if(broken)
		{
			TakeNItems(pchar, "Lockpick", -1);
			PlaySound("interface\lockpicking\lockpick_breaks.wav"); // Звук поломки
			Log_info("А-а-ать, Черт! Отмычка сломалась во время взлома!");
		}
	}

	EndCancelInterface(bClear);
}

bool CheckSkull(string SkullId)
{
    if(CheckCharacterItem(pchar, "sculMa1") || CheckAttribute(pchar, "OwnsSkull1"))
	{
		if(!CheckAttribute(pchar, "OwnsSkull1")) pchar.OwnsSkull1 = true;
		return true;
	}
    if(CheckCharacterItem(pchar, "sculMa2") || CheckAttribute(pchar, "OwnsSkull2"))
	{
		if(!CheckAttribute(pchar, "OwnsSkull2")) pchar.OwnsSkull2 = true;
		return true;
	}
    if(CheckCharacterItem(pchar, "sculMa3") || CheckAttribute(pchar, "OwnsSkull3"))
	{
		if(!CheckAttribute(pchar, "OwnsSkull3")) pchar.OwnsSkull3 = true;
		return true;
	}
    return false;
}
