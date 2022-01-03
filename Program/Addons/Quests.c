/////////////////////////////////////////////////////////////////////////////////////
// DoZoR
/////////////////////////////////////////////////////////////////////////////////////
void DozorSetRiddleQuestion(int iType)
{
	string sString = "";

	switch(iType)
	{
		case 1:
			sString = "- Капитан, корабль контрабандистов захвачен! В каюте корабля обнаружена записка странного содержания!";
			sString += newStr() + "- Покажите мне её немедленно!";
			sString += newStr() + "- Вот она, сэр!";
			sString += newStr() + "17 13 33 8";
			sString += newStr() + "22 1 23 1 18 5 16";
			sString += newStr() + "- Похоже это зашифрованное место сбора контрабандистов. ";
			sString += newStr() + "- Вы так думаете?";
			sString += newStr() + "- Иных вариантов быть не может!";

			PChar.Dozor.Riddle.Type_1.Question = sString;
			PChar.Dozor.Riddle.Type_1.Answer_1 = "пляж фахардо";
			PChar.Dozor.Riddle.Type_1.KeyPhrase = "Неуловимая Эскадра появилась в водах Карибского Моря.";
		break;

		case 2:
			sString = "Наверное, ты слыхал старую историю про Карибский Архипелаг? Её обычно картографы рассказывают. Нет? Ну, тогда, слушай. Коли поидёшь ты на север из самого центра, увидишь ты чудище злобное, страшнее которого на всем белом свете не сыщещь. Ежели победишь ты злобное чудище, и продолжишь свой путь в прежнем направлении встретишь ты там самого длинного зверя. Одолев сие исчадие ада, поворачивай на восток. На востоке увидишь ты бронированного гада, которого испанцы и французы кличут черепахой. Ежели ты одолел сего монстра, то путь твой лежит на северо-восток, где найдёшь ты покой и тепло.";
			PChar.Dozor.Riddle.Type_2.Question = sString;
			PChar.Dozor.Riddle.Type_2.Answer_1 = "теркс";
			PChar.Dozor.Riddle.Type_2.Answer_2 = "залив южный";
			PChar.Dozor.Riddle.Type_2.KeyPhrase = "Отважный капитан ищет Неуловимую Эскадру.";
		break;

		case 3:
			sString = "- Вам всегда следует обращать внимание на первый и последний корабли каравана, капитан. Чаще всего именно они первыми подвергаются нападению. Запомнили?";
			sString += newStr() + "- Так точно, адмирал! Первый и последний!";
			sString += newStr() + "- Очень хорошо! А теперь, капитан, взгляните на эти слова, и попробуйте понять, что здесь написано:";
			sString += newStr() + "ПНАСТРОТР";
			sString += newStr() + "ДОНОКАЧИ";
			sString += newStr() + "РЗЕВРЕ";
			sString += newStr() + "ЕПНТИЕЕР";
			sString += newStr() + "АДРУ";
			sString += newStr() + "ОНИРАЗНГ";
			sString += newStr() + "КАААТ";
			sString += newStr() + "- Ничего не понимаю, адмирал. Что это за бред?";
			sString += newStr() + "- Терпение, капитан, терпение. Немного усердия и вы увидите, что иногда и в бреду есть свой скрытый смысл. Вольно, капитан.";
			PChar.Dozor.Riddle.Type_3.Question = sString;
			PChar.Dozor.Riddle.Type_3.Answer_1 = "тортуга";
			PChar.Dozor.Riddle.Type_3.Answer_2 = "таверна";
			PChar.Dozor.Riddle.Type_3.KeyPhrase = "Отважный капитан напал на след Неуловимой Эскадры.";
		break;

		case 4:
			PChar.Dozor.Riddle.Type_4.Question = "picture";
			PChar.Dozor.Riddle.Type_4.Answer_1 = "виллемстад";
			PChar.Dozor.Riddle.Type_4.Answer_2 = "магазин";
			PChar.Dozor.Riddle.Type_4.KeyPhrase = "Отважный капитан вступил в схватку с Неуловимой Эскадрой.";
		break;

		case 5:
			sString = "Сначала они побывали в Порт-Рояле на Ямайке, затем сорвались на Эспаньолу, в испанский городок Санто-Доминго, потом побывали в Сан-Хуане, что на Пуэрто-Рико, после чего сорвались в английский Чарльстаун, остров Невис. Посетив после Невиса, английскую колонию Антигуа, они побывали на предпоследнем острове - Мартинике, в пиратском Ле-Франсуа. А вот последнее задание они разгадать не смогли, представляете? Им попалось очень недоступное задание.";
			PChar.Dozor.Riddle.Type_5.Question = sString;
			PChar.Dozor.Riddle.Type_5.Answer_1 = "гваделупа";
			PChar.Dozor.Riddle.Type_5.Answer_2 = "мыс недоступный";
			PChar.Dozor.Riddle.Type_5.KeyPhrase = "Отважный капитан вступил в схватку с Неуловимой Эскадрой.";
		break;

		case 6:
			PChar.Dozor.Riddle.Type_6.Question = "text";
			PChar.Dozor.Riddle.Type_6.Answer_1 = "залив гибели";
			PChar.Dozor.Riddle.Type_6.KeyPhrase = "Неуловимая Эскадра потеряла флагман.";
		break;

		case 7:
			sString = "- Капитан! По курсу два маленьких пиратских корабля!";
			sString += newStr() + "- Доложите о количестве орудий на каждом из них!";
			sString += newStr() + "- На одном корабле 9 орудий, на другом 8!";
			sString += newStr() + "- Приготовиться к бою!";
			sString += newStr() + "А – 1.2 1.9 2.2 2.4";
			sString += newStr() + "Е – 2.7";
			sString += newStr() + "И – 1.5 1.7";
			sString += newStr() + "К – 1.8";
			sString += newStr() + "Л – 2.1";
			sString += newStr() + "М – 1.1 2.3";
			sString += newStr() + "Н – 1.6 2.5 2.8";
			sString += newStr() + "Р – 1.3";
			sString += newStr() + "Т – 1.4 2.6";
			PChar.Dozor.Riddle.Type_7.Question = sString;
			PChar.Dozor.Riddle.Type_7.Answer_1 = "мартиника";
			PChar.Dozor.Riddle.Type_7.Answer_2 = "пляж ламантен";
			PChar.Dozor.Riddle.Type_7.KeyPhrase = "Неуловимая Эскадра потерпела поражение.";
		break;

		case 8:
			sString = "Вот и окончен твой путь, дозорный! За этими воротами ждёт тебя дом, а в доме том, в сундуке запертом ждёт тебя твоя награда! Если знаешь, где они находятся, отправляйся туда немедленно, если же не знаешь, советую тебе быть внимательнее и чаще глазеть по сторонам, чтобы найти нужное место.";
			PChar.Dozor.Riddle.Type_8.Question = sString;
		break;
	}
}

void DozorPrepare()
{
	for(int d=1; d<=8; d++)
	{
		DozorSetRiddleQuestion(d);
	}

	ref chr = GetCharacter(NPC_GenerateCharacter("Fabian Gronholm", "usurer_5", "man", "man", 1, PIRATE, -1, false));
	chr.name = "Фабиан";
	chr.lastname = "Гронхольм";
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Fabian_Gronholm.c";
	chr.Dialog.CurrentNode = "First Time";
	chr.greeting = "cit_quest";
	LAi_SetStayType(chr);
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, "Pirates_town", "officers", "reload6_3");
}

void DozorCancel()
{
	ref chr = CharacterFromID("Fabian Gronholm");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload4_back", "none", "", "", "", -1);

	PChar.quest.DozorClear.win_condition.l1 = "ExitFromLocation";
	PChar.quest.DozorClear.win_condition.l1.location = PChar.location;
	PChar.quest.DozorClear.function = "DozorClear";
}

void DozorClear(string qName)
{
	ref chr;
	if(GetCharacterIndex("Fabian Gronholm") != -1)
	{
		chr = CharacterFromID("Fabian Gronholm");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Fisher Pedro") != -1)
	{
		chr = CharacterFromID("Fisher Pedro");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Spanch Bob") != -1)
	{
		chr = CharacterFromID("Spanch Bob");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Dozor_Ship") != -1)
	{
		chr = CharacterFromID("Dozor_Ship");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Dozor NoName") != -1)
	{
		chr = CharacterFromID("Dozor NoName");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}

	for(int i=1; i<=3; i++)
	{
		if(GetCharacterIndex("Dozor Grot Agent Killer " + i) != -1)
		{
			chr = CharacterFromID("Dozor Grot Agent Killer " + i);
			chr.LifeDay = 0;
			ChangeCharacterAddress(chr, "None", "");
			LAi_KillCharacter(chr);
		}
	}

	if(CheckAttribute(PChar, "Dozor.CabinID")) { DeleteAttribute(PChar, "Dozor.CabinID"); }
	ClearQuestBoxStay("HouseDozor");
}

void DozorWait()
{
	SetTimerFunction("DozorClear", 0, 0, 90);
}

void DozorStart()
{
	ref chr = CharacterFromID("Fabian Gronholm");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload4_back", "none", "", "", "", -1);

	PChar.quest.DozorClear.over = "yes";

	PChar.Dozor = "1";
	PChar.Dozor.Riddle.CurType = 1;
	PChar.Dozor.Riddle.CanInterface = 1;

	SetQuestHeader("Dozor");
	AddQuestRecord("Dozor", "1");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));

	TakeNItems(PChar, "Dozor_Mekakhrom", 1);
}

void DozorToPuertoRicoShore()
{
	AddQuestRecord("Dozor", "2");

	string sPhrase = PChar.Dozor.Riddle.Type_1.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_1.Answer_1;
	AddQuestUserData("Dozor", "sLocation", sAnswer);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;
	PChar.Dozor = "2";

	ref chr = GetCharacter(NPC_GenerateCharacter("Fisher Pedro", "shipowner_4", "man", "man", 1, PIRATE, -1, false));
	chr.name = "рыбак";
	chr.lastname = "Педро";
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	chr.Dialog.CurrentNode = "Fisher_Pedro_1";
	chr.greeting = "Gr_Fisher";
	LAi_SetCitizenType(chr);
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, "Shore45", "goto", "goto8");
}

void DozorFisherPedroExit()
{
	PChar.Dozor = "3";
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);
	AddQuestRecord("Dozor", "3");

	PChar.Dozor.Riddle.CurType = 2;
	PChar.Dozor.Riddle.CanInterface = 1;

	ref chr = CharacterFromID("Fisher Pedro");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);
}

void DozorToTerks()
{
	PChar.Dozor = "4";
	AddQuestRecord("Dozor", "4");

	string sPhrase = PChar.Dozor.Riddle.Type_2.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_2.Answer_1;
	string sAnswer2 = PChar.Dozor.Riddle.Type_2.Answer_2;
	AddQuestUserData("Dozor", "sIsland", sAnswer);
	AddQuestUserData("Dozor", "sLocation", sAnswer2);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;

	PChar.quest.DozorInTerks.win_condition.l1 = "location";
	PChar.quest.DozorInTerks.win_condition.l1.location = "Shore57";
	PChar.quest.DozorInTerks.function = "DozorInTerks";
}

void DozorInTerks(string qName)
{
	PChar.Dozor = "5";
	AddQuestRecord("Dozor", "5");
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	PChar.quest.DozorPreTerksInGrot.win_condition.l1 = "location";
	PChar.quest.DozorPreTerksInGrot.win_condition.l1.location = "Terks_Grot";
	PChar.quest.DozorPreTerksInGrot.function = "DozorPreTerksInGrot";
}

void DozorPreTerksInGrot(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_SetActorType(PChar);
	DoQuestFunctionDelay("DozorTerksInGrot", 0.1);
}

void DozorTerksInGrot(string _tmp)
{
	PChar.Dozor = "6";

	StartQuestMovie(true, true, true);
	InterfaceStates.Buttons.Save.enable = false;

	SendMessage(&locCamera, "lfffl", MSG_CAMERA_TOPOS, 1, 3, 9, false);

	ref chr;

	int iRank = GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE;
	string sLocator = "";
	string sModel = "";
	for(int i=1; i<=3; i++)
	{
		switch(i)
		{
			case 1: sLocator = "monster1"; sModel = "pirate_" + (rand(25)+1); break;
			case 2: sLocator = "monster2"; sModel = "pirate_" + (rand(25)+1); break;
			case 3: sLocator = "monster3"; sModel = "citiz_" + (rand(11)+1); break;
		}

		chr = GetCharacter(NPC_GenerateCharacter("Dozor Grot Agent Killer " + i, sModel, "man", "man", iRank, PIRATE, 0, true));
		ChangeCharacterAddressGroup(chr, "Terks_Grot", "monsters", sLocator);
		chr.lastname = "";
		chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
		chr.Dialog.CurrentNode = "Grot_Agent_Killers_1";
		chr.greeting = "Gr_AllowToDump";
		LAi_SetStayType(chr);

		if(i == 1)
		{
			//TakeNItems(chr, "Dozor_Mekakhrom", 1);
			//chr.SaveItemsForDead   = true;
			chr.name = "Кригер";
		}
		else
		{
			if(i != 3)
			{
				chr.name = "Гебельс";
			}
		}

		if(i == 3)
		{
			LAi_SetActorType(chr);
			LAi_ActorSetLayMode(chr);
			LAi_SetImmortal(chr, true);
			LaunchBlood(chr, 5.0, true);
		}
	}

	LAi_SetActorType(CharacterFromID("Dozor Grot Agent Killer 1"));
	LAi_SetActorType(CharacterFromID("Dozor Grot Agent Killer 2"));
	LAi_SetActorType(PChar);

	LAi_ActorTurnToCharacter(CharacterFromID("Dozor Grot Agent Killer 1"), CharacterFromID("Dozor Grot Agent Killer 2"));
	LAi_ActorTurnToCharacter(CharacterFromID("Dozor Grot Agent Killer 2"), CharacterFromID("Dozor Grot Agent Killer 1"));
	LAi_ActorTurnToCharacter(PChar, CharacterFromID("Dozor Grot Agent Killer 1"));

	DoQuestFunctionDelay("DozorDialogInTerksGrot", 2.5);
}

void DozorDialogInTerksGrot(string _tmp)
{
	SetDialogCharacter2Character(PChar, CharacterFromID("Dozor Grot Agent Killer 1"), 0.1, true);
}

void DozorBattleInTerksGrot()
{
	locCameraFollow();
	EndQuestMovie();
	InterfaceStates.Buttons.Save.enable = true;

	LAi_SetPlayerType(PChar);
	LAi_SetWarriorType(CharacterFromID("Dozor Grot Agent Killer 1"));
	LAi_SetWarriorType(CharacterFromID("Dozor Grot Agent Killer 2"));
	LAi_group_MoveCharacter(CharacterFromID("Dozor Grot Agent Killer 1"), "EnemyFight");
	LAi_group_MoveCharacter(CharacterFromID("Dozor Grot Agent Killer 2"), "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l1 = "NPC_Death";
	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l1.character = "Dozor Grot Agent Killer 1";
	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l2 = "NPC_Death";
	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l2.character = "Dozor Grot Agent Killer 2";
	PChar.quest.DozorBattleInTerksGrotWinner.function = "DozorBattleInTerksGrotWinner";
}

void DozorBattleInTerksGrotWinner(string qName)
{
	//PlayStereoSound("new_round");
	//Log_Info("Найдите мекахром.");

	DozorTerksGrotFindMekakhrom("");
	TakeNItems(PChar, "Dozor_Mekakhrom", 1);

	/*PChar.quest.DozorTerksGrotFindMekakhrom.win_condition.l1 = "item";
	PChar.quest.DozorTerksGrotFindMekakhrom.win_condition.l1.item = "Dozor_Mekakhrom";
	PChar.quest.DozorTerksGrotFindMekakhrom.function = "DozorTerksGrotFindMekakhrom";*/
}

void DozorTerksGrotFindMekakhrom(string qName)
{
	PChar.Dozor = "7";
	AddQuestRecord("Dozor", "6");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Dozor", "sSex2", GetSexPhrase("ёл","ла"));

	PChar.Dozor.Riddle.CurType = 3;
	PChar.Dozor.Riddle.CanInterface = 1;

	chrDisableReloadToLocation = false;
}

void DozorToTortugaTavern()
{
	PChar.Dozor = "8";
	AddQuestRecord("Dozor", "7");

	string sPhrase = PChar.Dozor.Riddle.Type_3.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_3.Answer_1;
	string sAnswer2 = PChar.Dozor.Riddle.Type_3.Answer_2;
	AddQuestUserData("Dozor", "sIsland", sAnswer);
	AddQuestUserData("Dozor", "sLocation", sAnswer2);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;
}

void DozorTortugaTavernGetItem()
{
	PChar.Dozor = "9";
	AddQuestRecord("Dozor", "8");

	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	PChar.Dozor.Riddle.CurType = 4;
	PChar.Dozor.Riddle.CanInterface = 1;
}

void DozorToVillemstadStore()
{
	PChar.Dozor = "10";
	AddQuestRecord("Dozor", "9");

	string sPhrase = PChar.Dozor.Riddle.Type_4.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_4.Answer_1;
	string sAnswer2 = PChar.Dozor.Riddle.Type_4.Answer_2;
	AddQuestUserData("Dozor", "sIsland", sAnswer);
	AddQuestUserData("Dozor", "sLocation", sAnswer2);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;
}

void DozorToVillemstadStoreGetTask()
{
	PChar.Dozor = "11";
	AddQuestRecord("Dozor", "10");
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);
}

void DozorToGuadeloupeShore()
{
	PChar.Dozor = "12";
	AddQuestRecord("Dozor", "11");
	AddQuestUserData("Dozor", "sSex1", GetSexPhrase("ен","на"));

	string sPhrase = PChar.Dozor.Riddle.Type_5.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_5.Answer_1;
	string sAnswer2 = PChar.Dozor.Riddle.Type_5.Answer_2;
	AddQuestUserData("Dozor", "sIsland", sAnswer);
	AddQuestUserData("Dozor", "sLocation", sAnswer2);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	ref chr = GetCharacter(NPC_GenerateCharacter("Spanch Bob", "citiz_5", "man", "man", 1, PIRATE, -1, false));
	chr.name = "Спанч";
	chr.lastname = "Боб";
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	chr.Dialog.CurrentNode = "Spanch_Bob_1";
	chr.greeting = "Gr_Crazy";
	LAi_SetCitizenType(chr);
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, "Shore31", "goto", "goto4");
}

void DozorGuadeloupeShoreGetTask()
{
	PChar.Dozor = "13";
	AddQuestRecord("Dozor", "12");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));
}

void DozorToDeadShoreInMein()
{
	ref chr = CharacterFromID("Spanch Bob");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);

	PChar.Dozor = "14";
	AddQuestRecord("Dozor", "13");

	string sPhrase = PChar.Dozor.Riddle.Type_6.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_6.Answer_1;
	AddQuestUserData("Dozor", "sIsland", "Мэйн");
	AddQuestUserData("Dozor", "sLocation", sAnswer);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	SetQuestBoxItems("Shore_ship2", "Dozor_Mekakhrom", 1);
	PChar.quest.DozorInDeadShoreInMein.win_condition.l1 = "location";
	PChar.quest.DozorInDeadShoreInMein.win_condition.l1.location = "Shore_ship2";
	PChar.quest.DozorInDeadShoreInMein.function = "DozorInDeadShoreInMein";
}

void DozorInDeadShoreInMein(string qName)
{
	PChar.Dozor = "15";
	AddQuestRecord("Dozor", "14");
	chrDisableReloadToLocation = true;

	PChar.quest.DozorInDeadShoreInMeinFindItem.win_condition.l1 = "item";
	PChar.quest.DozorInDeadShoreInMeinFindItem.win_condition.l1.item = "Dozor_Mekakhrom";
	PChar.quest.DozorInDeadShoreInMeinFindItem.function = "DozorInDeadShoreInMeinFindItem";
}

void DozorInDeadShoreInMeinFindItem(string qName)
{
	ClearQuestBoxStay("Shore_ship2");
	chrDisableReloadToLocation = false;

	PChar.Dozor = "16";
	AddQuestRecord("Dozor", "15");
	AddQuestUserData("Dozor", "sSex2", GetSexPhrase("ёл","ла"));

	PChar.Dozor.Riddle.CurType = 7;
	PChar.Dozor.Riddle.CanInterface = 1;
}

void DozorToMartiniqueShore()
{
	PChar.Dozor = "17";
	AddQuestRecord("Dozor", "16");
	PChar.Dozor.Riddle.CanInterface = 0;

	string sPhrase = PChar.Dozor.Riddle.Type_7.KeyPhrase;
	string sAnswer = PChar.Dozor.Riddle.Type_7.Answer_1;
	string sAnswer2 = PChar.Dozor.Riddle.Type_7.Answer_2;
	AddQuestUserData("Dozor", "sIsland", sAnswer);
	AddQuestUserData("Dozor", "sLocation", sAnswer2);
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	Group_FindOrCreateGroup("DozorShip");
	Group_SetType("DozorShip","war");

	int iRank = GetRank(PChar, 15) + MOD_SKILL_ENEMY_RATE;
	ref sld = GetCharacter(NPC_GenerateCharacter("Dozor_Ship", "officer_4", "man", "man", iRank, PIRATE, -1, true));
	FantomMakeCoolSailor(sld, SHIP_DERFFLINGER, "Дозорный", CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
	sld.name = "Джастин";
	sld.lastname = "Батт";
	sld.greeting = "Gr_UnpleasantCaptain";
	sld.CaptanId = "";
	sld.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	sld.Dialog.CurrentNode = "Justin_Butt_1";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");

	// фиксируем некоторые статы для флейта -->
	realships[sti(sld.ship.type)].SpeedRate = realships[sti(sld.ship.type)].SpeedRate + 1.5; //Уведичиваем скорость
	realships[sti(sld.ship.type)].TurnRate  = realships[sti(sld.ship.type)].TurnRate  + 5; //Увеличиваем маневренность
	realships[sti(sld.ship.type)].HP = 3000; //Фиксируем ХП
	realships[sti(sld.ship.type)].Capacity = 3000; //Фиксируем трюм
	realships[sti(sld.ship.type)].MastMultiplier = 1.3; //Упрочняем мачты

	//Уменьшаем команду, как плату за предыдущие статы.
	realships[sti(sld.ship.type)].MaxCrew = 200;
	realships[sti(sld.ship.type)].MinCrew = 35;
	realships[sti(sld.ship.type)].OptCrew = 150;
	// фиксируем некоторые статы для флейта <--
	SetCrewQuantity(sld,GetMaxCrewQuantity(sld)); //Gregg - режем команду, а то прямо как у БМС вышел адовый оверперегруз
	sld.skill.Sailing = 80; //подрезаем наву
	sld.skill.Accuracy = 80; //подрезаем меткость
	sld.skill.Cannons = 80; //подрезаем пушки

	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	SetGeraldDetails(sld, 3, rand(7), "", "pir_" + (rand(5)+1));

	Group_AddCharacter("DozorShip", "Dozor_Ship");
	Group_SetType("DozorShip", "pirate");
	Group_SetGroupCommander("DozorShip", "Dozor_Ship");
	Group_SetAddress("DozorShip", "Martinique", "quest_ships", "quest_ship_10");
	Group_SetTaskAttack("DozorShip", PLAYER_GROUP);

	PChar.quest.DozorBattleWithDozorShip.win_condition.l1 = "location";
	PChar.quest.DozorBattleWithDozorShip.win_condition.l1.location = "Martinique";
	PChar.quest.DozorBattleWithDozorShip.function = "DozorBattleWithDozorShip";
}

void DozorBattleWithDozorShip(string qName)
{
	PChar.Dozor = "18";
	AddQuestRecord("Dozor", "17");

	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	PChar.quest.DozorDeadDozorShip.win_condition.l1 = "Group_Death";
	PChar.quest.DozorDeadDozorShip.win_condition.l1.group = "DozorShip";
	PChar.quest.DozorDeadDozorShip.function = "DozorDeadDozorShip";
}

void DozorDeadDozorShip(string qName)
{
	string sCabin = "";
	if(CheckAttribute(PChar, "Dozor.CabinID"))
	{
		sCabin = PChar.Dozor.CabinID;

		if(FindLocation(sCabin) != -1)
		{
			if(CheckAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Key"))
			{
				DeleteAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Key");
			}
			if(CheckAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Mekakhrom"))
			{
				DeleteAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Mekakhrom");
			}
		}
	}

	if(GetCharacterItem(PChar, "Dozor_Mekakhrom") >= 1 && GetCharacterItem(PChar, "Dozor_Key") >= 1)
	{
		DozorToHouse();
	}
	else
	{
		if(GetCharacterItem(PChar, "Dozor_Mekakhrom") <= 0 && GetCharacterItem(PChar, "Dozor_Key") <= 0)
		{
			AddQuestRecord("Dozor", "18");
		}
		else
		{
			if(GetCharacterItem(PChar, "Dozor_Mekakhrom") <= 0 && GetCharacterItem(PChar, "Dozor_Key") >= 1)
			{
				AddQuestRecord("Dozor", "18");
			}
			else
			{
				if(GetCharacterItem(PChar, "Dozor_Mekakhrom") >= 0 && GetCharacterItem(PChar, "Dozor_Key") <= 0)
				{
					AddQuestRecord("Dozor", "21");
					AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));
				}
			}
		}

		PChar.Dozor = "END";
		DozorClear("");
		TakeNItems(PChar, "Dozor_Mekakhrom", -1);
		TakeNItems(PChar, "Dozor_Key", -1);
		CloseQuestHeader("Dozor");
	}
}

void DozorToHouse()
{
	PChar.Dozor = "19";
	AddQuestRecord("Dozor", "19");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));

	PChar.Dozor.Riddle.CurType = 8;
	PChar.Dozor.Riddle.CanInterface = 1;

	Locations[FindLocation("Charles_town")].reload.l29.disable = 0;
	Locations[FindLocation("Charles_town")].reload.l29.go = "HouseDozor";

	/*PChar.GenQuestBox.HouseDozor = true;
	PChar.GenQuestBox.HouseDozor.box2.items.Dozor_Storm = 1;
	PChar.GenQuestBox.HouseDozor.box2.items.Dozor_HorseShoe = 1;
	PChar.GenQuestBox.HouseDozor.box2.items.Dozor_Mirror = 1;
	PChar.GenQuestBox.HouseDozor.box2.money = 100000;
	PChar.GenQuestBox.HouseDozor.stay = true;*/

	//SetQuestFunction("DozorToHouseKeyInit", "DozorToHouseKeyInit", "l", "HouseDozor");

	PChar.quest.DozorLastDialog.win_condition.l1 = "locator";
	PChar.quest.DozorLastDialog.win_condition.l1.location = "HouseDozor";
	PChar.quest.DozorLastDialog.win_condition.l1.locator_group = "box";
	PChar.quest.DozorLastDialog.win_condition.l1.locator = "box2";
	PChar.quest.DozorLastDialog.function = "DozorLastDialog";
}

void DozorToHouseKeyInit(string qName)
{
	Locations[FindLocation("HouseDozor")].box2.key = "Dozor_Key";
	Locations[FindLocation("HouseDozor")].box2.key.delItem = true;
}

void DozorLastDialog(string qName)
{
	Log_InfoS("Сундук открыт!");

	TakeNItems(PChar, "Dozor_Key", -1);
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	ref loc = LocFromID("HouseDozor");
	loc.box2.items.Dozor_Storm = 1;
	loc.box2.items.Dozor_HorseShoe = 1;
	loc.box2.items.Dozor_Mirror = 1;
	loc.box2.money = 100000;

	StartQuestMovie(true, true, true);
	InterfaceStates.Buttons.Save.enable = false;

	ref chr = GetCharacter(NPC_GenerateCharacter("Dozor NoName", "officer_6", "man", "man", 1, PIRATE, 0, false));
	chr.name = "незнакомец";
	chr.lastname = "";
	chr.greeting = "cit_common1";
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	chr.Dialog.CurrentNode = "NoName_1";
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	SetDialogCharacter2Character(PChar, chr, 5.0, true);
}

void DozorHappyEnd()
{
	EndQuestMovie();
	InterfaceStates.Buttons.Save.enable = true;

	PChar.Dozor = "END";
	AddQuestRecord("Dozor", "20");
	CloseQuestHeader("Dozor");

	LAi_SetPlayerType(PChar);

	ref chr = CharacterFromID("Dozor NoName");
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	Locations[FindLocation("Charles_town")].reload.l29.disable = 1;

	PChar.quest.DozorClear.win_condition.l1 = "ExitFromLocation";
	PChar.quest.DozorClear.win_condition.l1.location = PChar.location;
	PChar.quest.DozorClear.function = "DozorClear";

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", некий капитан " + GetNameLugger(PChar, "f") + " смог победить в сложнейшей игре ''DoZoR'', и получил заслуженный приз.", 5, 1);
}
