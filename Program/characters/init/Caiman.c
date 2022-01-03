
int CreateCaimanCharacters(int n)
{
	ref ch;

	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Священик
	ch.id		= "Caiman_Priest";
	ch.model	= "priest_" + (rand(3)+1);
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "Gr_Church";
	ch.nation = PIRATE;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Caiman_waitress";
	ch.model	= "girl_" + (rand(8)+1);
	ch.sex = "woman";
	ch.City = "Caiman";
	ch.location	= "Caiman_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "Gr_officiant";
	ch.nation = PIRATE;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Caiman_tavernkeeper";
	ch.model	= "barmen_" + (rand(15)+1);
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = PIRATE;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "Caiman_trader";
	ch.model	= "trader_" + (rand(15)+1);
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.StoreNum   = Caiman_STORE;
	ch.from_sea   = "shore16";
	ch.nation = PIRATE;
	LAi_SetOwnerType(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "Caiman_shipyarder";
	ch.model	= "shipowner_" + (rand(15)+1);
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = PIRATE;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    	SetSelfSkill(ch, 90, 90, 90, 60, 70);
	//ch.standUp = true; //вставать и нападать на врага
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "Caiman_usurer";
	ch.model	= "usurer_" + (rand(7)+1);
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = PIRATE;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 10000; // *1000 денег
	LAi_SetOwnerType(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Caiman_PortMan";
	ch.model	= "usurer_" + (rand(7)+1);
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = PIRATE;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;


	makeref(ch,Characters[n]);			// Кладовщик на складе
	ch.id		= "Caiman_StoreKeeper";
	ch.model	= "trader_" + (rand(15)+1);
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Caiman";
	ch.location	= "Caiman_StoreHouse";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_StoreHouse.c";
	ch.quest.type = "none";
	ch.nation = PIRATE;
	LAi_SetOwnerType(ch);
    	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	return n;
}
