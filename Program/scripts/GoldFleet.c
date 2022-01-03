
int igoldpos = 0;
int GoldCapNum  = 0;
string GoldMonth;
bool isGoldFleet = false;



void GoldFleet()
{
    ref sld, chref;
    int iChar = NPC_GenerateCharacter("Head_of_Gold_Squadron", "off_spa_2", "man", "man", 5, SPAIN, 31, true);
    makeref(chref, Characters[iChar]);
    chref.ship.type = GenerateShipExt(SHIP_SP_SANFELIPE, 1, chref);
	SetBaseShipData(chref);
	UpgradeShipParameter(chref, "MaxCrew");
	UpgradeShipParameter(chref, "HP");
    SetCrewQuantityFull(chref);
    Fantom_SetCannons(chref, "war"); //fix
    Fantom_SetBalls(chref, "pirate");
	for( int i = 0; i<9; i++)
	{
		AddCharacterGoods(chref, i, 10000);
	}
	SetRandomNameToShip(chref);
	SetFantomParamHunter(chref); //крутые парни
    SetCaptanModelByEncType(chref, "war");//
	string sGroup = "Sea_"+chref.id;

	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, chref.id);
	Group_SetGroupCommander(sGroup, chref.id);
	int st = GetCharacterShipType(chref);
	ref shref;
	shref = GetRealShip(st);
	shref.ShipSails.Gerald_Name = "Ing_11";//герб
	shref.ship.upgrades.sails = 22;//паруса
	chref.dialog.filename = "Capitans_dialog.c"; // homo 20/01/07
	chref.dialog.currentnode = "GoldSquadron";
	chref.DeckDialogNode = "GoldSquadron";
	//parus_usual_18
	if(!CheckAttribute(pchar, "QuestTemp.GoldFleetMorganaTaken") && rand(3) == 1)
	{
		pchar.QuestTemp.GoldFleetMorganaTaken = true;
		chref.SaveItemsForDead = true;
		chref.DontClearDead = true;
		string sEquipItem = GetGeneratedItem("blade27");
		AddItems(chref, sEquipItem, 1);
		EquipCharacterbyItem(chref, sEquipItem);
		Log_TestInfo("Этот кэп будет вооружен морганой !");
	}

	SetSelfSkill(chref, 100, 100, 100, 100, 90);
	SetShipSkill(chref, 90, 90, 100, 100, 100, 100, 100, 100, 90);

    int nfreg = (6+rand(1));
    int ngal = (5+rand(1));
    GoldCapNum = nfreg + ngal;

    for(int k = 1; k <=(nfreg + ngal) ; k++)
	{
		iChar = NPC_GenerateCharacter("GoldCap_"+k, "off_spa_2", "man", "man", 5, SPAIN, 31, true);
        makeref(sld, Characters[iChar]);
        if (k <= nfreg)
        {
            sld.Ship.Mode = "war";
			if(k < 3)  sld.ship.type = GenerateShipExt(SHIP_SP_SANFELIPE, 1, sld);
			else sld.ship.type = GenerateShipExt(SHIP_ALEXIS, 1, sld);
    	    SetBaseShipData(sld);
			SetFantomParamHunter(sld); //крутые парни
			if(k < 3)
			{
				SetSelfSkill(sld, 100, 100, 100, 100, 90);
				SetShipSkill(sld, 90, 90, 100, 100, 100, 100, 100, 100, 90);
				UpgradeShipParameter(sld, "MaxCrew");
				UpgradeShipParameter(sld, "HP");
			}
            SetCrewQuantityFull(sld);
            Fantom_SetCannons(sld, "war"); //fix
			st = GetCharacterShipType(sld);
			shref = GetRealShip(st);
			shref.ShipSails.Gerald_Name = "spa_2";//герб
			shref.ship.upgrades.sails = 15;//паруса
            Fantom_SetBalls(sld, "pirate");
    	    for(i = 0; i<10; i++)
			{
				if(k < 3) AddCharacterGoods(sld, i, 10000);
				else AddCharacterGoods(sld,i, 5000);
			}
            SetCaptanModelByEncType(sld, "war");//
			else
			{
				SetSelfSkill(sld, sti(pchar.skill.FencingLight), sti(pchar.skill.Fencing), sti(pchar.skill.FencingHeavy), sti(pchar.skill.Pistol), sti(pchar.skill.Fortune));
				SetShipSkill(sld, 80, 80, sti(pchar.skill.Accuracy), sti(pchar.skill.Cannons), 80, sti(pchar.skill.Repair), sti(pchar.skill.Grappling), sti(pchar.skill.Defence), 80);
			}

        }
        else
        {
            sld.Ship.Mode = "war";
            sld.ship.type = GenerateShipExt(SHIP_GALEON50, 1, sld);
    	    SetBaseShipData(sld);
            SetCrewQuantityFull(sld);
            Fantom_SetCannons(sld, "war"); // fix
            Fantom_SetBalls(sld, "war");
			st = GetCharacterShipType(sld);
			shref = GetRealShip(st);
			shref.ShipSails.Gerald_Name = "Ing_73"//герб
			shref.ship.upgrades.sails = 22;//паруса
			Fantom_SetGoods(sld, "war");

            int iSpace = GetCharacterFreeSpace(sld, GOOD_GOLD)
            iSpace = iSpace * 1/3;
			AddCharacterGoods(sld, GOOD_GOLD, iSpace * 2);
            AddCharacterGoods(sld, GOOD_SILVER, iSpace * 2);
            SetFantomParamHunter(sld); //крутые парни
            SetCaptanModelByEncType(sld, "war");//
			SetSelfSkill(sld, sti(pchar.skill.FencingLight), sti(pchar.skill.Fencing), sti(pchar.skill.FencingHeavy), sti(pchar.skill.Pistol), sti(pchar.skill.Fortune));
			SetShipSkill(sld, 80, 80, sti(pchar.skill.Accuracy), sti(pchar.skill.Cannons), 80, sti(pchar.skill.Repair), sti(pchar.skill.Grappling), sti(pchar.skill.Defence), 80);
        }

        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true; //квестовые не сдаются

        sld.dialog.filename = "Capitans_dialog.c"; // homo 20/01/07
	    sld.dialog.currentnode = "GoldSquadron";
	    sld.DeckDialogNode = "GoldSquadron";

        SetRandomNameToShip(sld);
        Group_AddCharacter(sGroup, sld.id);
	}


    chref.AlwaysEnemy = true;
    chref.DontRansackCaptain = true; //квестовые не сдаются
	chref.mapEnc.type = "trade";
	chref.mapEnc.worldMapShip = "Manowar_gold";
	chref.mapEnc.Name = XI_ConvertString("GoldConvoy");

	string sQuest = "KillHeadGoldFleet";
	pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
	pchar.quest.(sQuest).win_condition.l1.character = chref.id;
	pchar.quest.(sQuest).win_condition = "KillHeadGoldFleet";
    pchar.quest.(sQuest).function= "KillHeadGoldFleet";
}

void KillHeadGoldFleet(string temp)
{
	isGoldFleet = false;
	Map_ReleaseQuestEncounter("Head_of_Gold_Squadron");

}

void GoldFleetEncounter(string temp)
{
    string sQuest = "LeaveGoldleet";
    pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
    pchar.quest.(sQuest).win_condition = "LeaveGoldleet";
    pchar.quest.(sQuest).function = "LeaveGoldleet";
}

void LeaveGoldleet(string temp)
{

    if ( isGoldFleet )
    {
        if (NumDeadCapitan() > 0)
        {
            //конвой атакован
            DefeatRumour(1);
            AddQuestRecord("Rumour_GoldFleet", 13+rand(2));
        }
        else
        {
            // конвой не тронули
            isGoldFleet = true;

        }
        if ( temp == "CheckHavanaGoldFleet" )
        {
               string sQuest = "HeadGoldFleetInHavana";
               pchar.quest.(sQuest).win_condition.l1 = "location";
               pchar.quest.(sQuest).win_condition.l1.location = "Cuba2";
               pchar.quest.(sQuest).function= "GoldfleetInHavana";
               Log_TestInfo("GoldFleet in Havana");


        }
        return;
    }
    else
    {
        // конвой погиб
        Map_ReleaseQuestEncounter("Head_of_Gold_Squadron");
    	igoldpos = 0;
    	DefeatRumour(0);
    	DefeatGoldFleet("");
    }


}

void DefeatGoldFleet(string temp)
{
    string Text;
    ref rParams;
    Group_DeleteGroup("Sea_Head_of_Gold_Squadron");
    AddQuestRecord("Rumour_GoldFleet", 4+rand(2));
    CloseQuestHeader("Rumour_GoldFleet");
    Pchar.quest.EndOfGoldFleet.over = "yes";
	pchar.questTemp.GoldFleetNum = sti(pchar.questTemp.GoldFleetNum) + 1;
	if(sti(pchar.questTemp.GoldFleetNum) >= 1) UnlockAchievement("AchGoldFleet", 1);
	if(sti(pchar.questTemp.GoldFleetNum) >= 3) UnlockAchievement("AchGoldFleet", 2);
	if(sti(pchar.questTemp.GoldFleetNum) >= 7) UnlockAchievement("AchGoldFleet", 3);
    Pchar.quest.HeadGoldFleetInHavana.over = "yes"; //fix
    Pchar.quest.CheckHavanaGoldFleet.over = "yes"; //fix
    Pchar.quest.LeaveGoldleet.over = "yes"; //fix
    Pchar.GoldfleetInHavana.over = "yes"; //fix
    isGoldFleet = false;
    Log_TestInfo("Defeat GoldFleet");

	if (rand(2) == 0 && !CheckAttribute(pchar, "DevFleet"))
	{
		pchar.DevFleet = true;
		Log_Info("Штормовая эскадра разработчиков решила поживиться награбленным!");
		string  sGroup = "Sea_Devs0";
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		for (int i = 0; i < 8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Devs"+i, "pirate_"+sti(rand(25)+1), "man", "man", 55, PIRATE, 8, true));

			//Модель корабля на глобалке менять здесь
			sld.mapEnc.worldMapShip = "pirates_manowar";

			sld.mapEnc.Name = "штормовая эскадра разработчиков, в количестве 8 кораблей";
			sld.mapEnc.type = "war";
			FantomMakeCoolSailor(sld, rand(SHIP_PLOT), "", CANNON_TYPE_CANNON_LBS48, 100, 100, 100);

			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.AnalizeShips = true;

			sld.ship.Crew.Morale = 100;
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);

			LAi_group_MoveCharacter(sld, "Devs");
			Group_AddCharacter(sGroup, sld.id);

			sld.lastname = "";
			if (i == 0)
			{
				sld.name 	= "LEOPARD";
				sld.Ship.name 	= "LEOPARD";
				Group_SetGroupCommander(sGroup, sld.id);
				Map_CreateFastWarrior("", sld.id, 8);
			}
			if (i == 1)
			{
				sld.name 	= "Gregg";
				sld.Ship.name 	= "Gregg";
			}
			if (i == 2)
			{
				sld.name 	= "Googman";
				sld.Ship.name 	= "Googman";
			}
			if (i == 3)
			{
				sld.name 	= "BlackThorn";
				sld.Ship.name 	= "BlackThorn";
			}
			if (i == 4)
			{
				sld.name 	= "Shaharan";
				sld.Ship.name 	= "Shaharan";
			}
			if (i == 5)
			{
				sld.name 	= "Lipsar";
				sld.Ship.name 	= "Lipsar";
			}
			if (i == 6)
			{
				sld.name 	= "Sinistra";
				sld.Ship.name 	= "Sinistra";
			}
			if (i == 7)
			{
				sld.name 	= "Qwerry, St.";
				sld.Ship.name 	= "Qwerry, St.";
			}
		}
	}
}

void RouteGoldFleet()
{
    ref sld;
    if (isGoldFleet==true)
    {
        switch (igoldpos)
        {
            case 0 :
                int hvx = worldMap.islands.Cuba2.Havana_town.position.x;
    	        int hvz = worldMap.islands.Cuba2.Havana_town.position.z;
                Map_CreateTraderXZ(-858.089, 897.072, hvx, hvz, "Head_of_Gold_Squadron", 3);
                Log_TestInfo("GoldFleet is near of Havana");
            break;

            case 1 :
                ClearIslandShips("Havana");
                Colonies[FindColony("Havana")].DontSetShipInPort = true;
                sld = CharacterFromID("Head_of_Gold_Squadron"); //По прибытию в Гавану конвой расслабляется =)
                DeleteAttribute(sld, "AlwaysEnemy");
                for(int k = 1; k <= GoldCapNum ; k++)
                {
                    sld = CharacterFromID("GoldCap_"+k);
                    DeleteAttribute(sld, "AlwaysEnemy");
                }                                        //
                Group_SetAddress("Sea_Head_of_Gold_Squadron", "Cuba2", "Quest_ships", "reload_fort1_siege");//fix 1
                string sQuest = "HeadGoldFleetInHavana";
                pchar.quest.(sQuest).win_condition.l1 = "location";
                pchar.quest.(sQuest).win_condition.l1.location = "Cuba2";
                pchar.quest.(sQuest).function= "GoldfleetInHavana";
                Log_TestInfo("GoldFleet in Havana");
                igoldpos = 0;
                return;
            break;

        }
        igoldpos++;
    }
}

void GoldfleetInHavana(string temp)
{
	 string sQuest = "CheckHavanaGoldFleet";
	 pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
	 pchar.quest.(sQuest).win_condition = "LeaveGoldleet";
	 pchar.quest.(sQuest).function = "LeaveGoldleet";
}

void EndOfGoldFleet(string temp)
{
    string Text;
    string sGroupID = "Sea_Head_of_Gold_Squadron";
    Log_TestInfo("Complited GoldFleet "+NumDeadCapitan());
    Map_ReleaseQuestEncounter("Head_of_Gold_Squadron");
    Group_SetAddressNone(sGroupID);
    CloseQuestHeader("Rumour_GoldFleet");
    Group_DeleteGroup(sGroupID);
    Pchar.quest.HeadGoldFleetInHavana.over = "yes";
    Pchar.quest.CheckHavanaGoldFleet.over = "yes"; //fix
    Pchar.quest.LeaveGoldleet.over = "yes"; //fix
    Pchar.GoldfleetInHavana.over = "yes"; //fix
    igoldpos = 0;
    isGoldFleet = false;
    DeleteAttribute (&colonies[FindColony("Havana")], "DontSetShipInPort"); //возвращаем жизнь

}
void StartGoldFleet(string temp);
{
    if (Colonies[FindColony("Havana")].nation == SPAIN && Colonies[FindColony("PortoBello")].nation == SPAIN
    && !CheckAttribute(Colonies[FindColony("Havana")], "Siege") && !CheckAttribute(Colonies[FindColony("PortoBello")], "Siege"))
    {
            Log_TestInfo("start GoldFleet");
            AddTemplRumour("Start_GoldFleet", id_counter+1);
            string sQuest = "EndOfGoldFleet";
            SetTimerCondition(sQuest, 0, 0, 29, false);
            pchar.quest.(sQuest).win_condition = "EndOfGoldFleet";
            pchar.quest.(sQuest).function= "EndOfGoldFleet";
            GoldFleet();
            int pbx = worldMap.islands.PortoBello.PortoBello_town.position.x;
	        int pbz = worldMap.islands.PortoBello.PortoBello_town.position.z;
            Map_CreateTraderXZ(pbx, pbz, -858.089, 897.072, "Head_of_Gold_Squadron", 22);
            igoldpos = 0;
    }
}

void EndTime_GoldFleet(int nid)
{
    ref Prm, CurTpl;
    aref varARef;
    int ind = FindRumour(nid);
    if (ind != -1)
    {
        makeref(Prm, Rumour[ind]);
        int tNum = TplNameToNum("End_GoldFleet");
        makeref(CurTpl,  templat[tNum]);
        int StartNext =(sti(Prm.starttime) + 21)
        if ( StartNext > DateToInt(0))
        {
            CurTpl.starttime =  (StartNext - DateToInt(0));
            CurTpl.actualtime = (sti(CurTpl.actualtime)+ sti(CurTpl.starttime));
        }
    }
}

int NumDeadCapitan()
{
    int rez = 0

    //for(int k = 1; k <= GoldCapNum ; k++)
    //{
    //   if (GetCharacterIndex("GoldCap_"+k) == -1 || CharacterIsDead(CharacterFromID("GoldCap_"+k))) rez++;
    //}
    rez = GoldCapNum + 1 - Group_GetLiveCharactersNum("Sea_Head_of_Gold_Squadron");
    Log_TestInfo(GoldCapNum +" | "+rez);
    GoldCapNum = GoldCapNum - rez;
    return rez;
}

void DefeatRumour(int noall)
{
    ref CurrentRumour;
    string tid;
    int lngFileID = LanguageOpenFile("RumourTexts.txt");



    for(int Rumour_Index = 0; Rumour_Index < MAX_RUMOURS; Rumour_Index++)
    {
        makeref(CurrentRumour, Rumour[Rumour_Index]);
        if ( CheckAttribute(CurrentRumour, "Name") && CurrentRumour.Name == "End_GoldFleet")
        {
            if (noall != 0)
            {
                tid = "Defeat_GoldFleet_t"+rand(2);
                CurrentRumour.text = LanguageConvertString(lngFileID, tid);
            }
            else
            {
                tid = "Attak_GoldFleet_t"+rand(2);
                CurrentRumour.text = LanguageConvertString(lngFileID, tid);


            }
            DeleteAttribute (CurrentRumour, "loginfo");
            return;
        }
        if (CurrentRumour.next == "End_GoldFleet" || CurrentRumour.next == "Attak_GoldFleet" )
        {
            if (noall == 0) CurrentRumour.next = "Defeat_GoldFleet";
            else CurrentRumour.next = "Attak_GoldFleet";
            DeleteAttribute (CurrentRumour, "nonation");
            DeleteAttribute (CurrentRumour, "loginfo");
            return;
        }

    }

}

//OnInit_GoldFleet
void OnInit_GoldFleet(ref rTmpl)
{
    object Prm;
    string tresult;
    aref varARef;
    Prm.gold_month = GoldMonth;
    makearef(varARef, Prm);
    tresult += GetAssembledString( ttttstr,	varARef);
    ttttstr = tresult;
}
