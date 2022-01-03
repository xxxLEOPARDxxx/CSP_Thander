//////////////////////////////////////// Спец свойства ХО /////////////////////////////////////////////////// -->

/*
	itm.special.valueBB = 100; 	// Пролом блока
	itm.special.valueCrB = 100; // Буст крита
	itm.special.valueCB = 100; 	// Пролом кирасы
	itm.special.valueSS = 100; 	// Резкий удар
	itm.special.valueStS = 100; // Стан
	itm.special.valueT = 100; 	// Травмы
	itm.special.valueB = 100; 	// Кровоток
	itm.special.valueP = 100; 	// Отравление

	itm.points_shop = 1; // Атрибут для магазина ачивок
*/

//////////////////////////////////////// Спец свойства ХО /////////////////////////////////////////////////// <--

//////////////////////////////////////// Крафт ////////////////////////////////////////////////////////////// -->

/*  Это всё нужно дописывать для определённого итема, чтобы он появился в списке крафта

	itm.PerkReq = 1;				// Требование перка для открытия рецепта
    itm.CraftedItem = "grenade"; 	// Айди создаваемого предемета
    itm.CraftFor = "Blacksmith"; 	// Форма крафта
	itm.ResultNum = 2;				// Количество получаемых компонентов
    itm.ComponentsNum = 2;		 	// Количество компонентов
    itm.Component1 = "bullet";	 	// Айди первого компонента
    itm.Component1Num = 5;		 	// Количество требуемых компонентов
    itm.Component2 = "gunpowder";	// Айди второго компонента
    itm.Component2Num = 5;			// Количество требуемых компонентов
*/

//////////////////////////////////////// Крафт ////////////////////////////////////////////////////////////// <--

//////////////////////////////////////// Стрелковое ///////////////////////////////////////////////////////// -->
/*
	Требования для экипировки огнестрела. Если нет - нет и требований

	itm.ReqPerk = "Gunman";
	itm.ReqPerk = "GunProfessional";
*/
//////////////////////////////////////// Стрелковое ///////////////////////////////////////////////////////// <--

int InitItems()
{
	InitButtons();
	InitRandItems();
	ref itm;
	int n;

	for(n=0; n<ITEMS_QUANTITY; n++)
	{
		makeref(itm,Items[n]);
		itm.id = "item"+(n+1);
		itm.describe = "";
		itm.index = n;
		itm.model = "";
		itm.shown = false;
		itm.startLocation = "";
		itm.startLocator = "";
		itm.useLocation = "";
		itm.useLocator = "";
		itm.describe = "";
        itm.Weight = 0.0; // boal
        itm.uniq  = false;
        itm.price = 1;
        itm.ItemType = "VARIETY";
	}
	n = 0;

	// Еда для восстановления энергии
	makeref(itm,Items[n]);
	itm.id = "Food1"; // Тропические фрукты
	itm.name = "itmname_Food1";
	itm.describe = "itmdescr_Food1";
	itm.model = "1";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_15";
	itm.price = 10;
	itm.Weight = 0.6;
	itm.Solder_o.rare = 0.3;
	itm.Solder_o.min = 2;
	itm.Solder_o.max = 6;
	itm.Solder.rare = 0.1;
	itm.Solder.min = 1;
	itm.Solder.max = 3;
	itm.Warrior.rare = 0.1;
	itm.Warrior.min = 1;
	itm.Warrior.max = 4;
	itm.Monster.rare = 0;
	itm.Monster.min = 0;
	itm.Monster.max = 0;
	itm.Food.tex = 3;
	itm.Food.pic = 4;
	itm.Food.selpic = 12;
	itm.Food.energy = 6.0;
	itm.Food.energy.speed = 25.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Food2"; // Хлеб
	itm.name = "itmname_Food2";
	itm.describe = "itmdescr_Food2";
	itm.model = "1";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_15";
	itm.price = 20;
	itm.Weight = 1.2;
	itm.Solder_o.rare = 0.3;
	itm.Solder_o.min = 2;
	itm.Solder_o.max = 6;
	itm.Solder.rare = 0.1;
	itm.Solder.min = 1;
	itm.Solder.max = 3;
	itm.Warrior.rare = 0.1;
	itm.Warrior.min = 1;
	itm.Warrior.max = 4;
	itm.Monster.rare = 0;
	itm.Monster.min = 0;
	itm.Monster.max = 0;
	itm.Food.tex = 3;
	itm.Food.pic = 0;
	itm.Food.selpic = 8;
	itm.Food.energy = 12.0;
	itm.Food.energy.speed = 15.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Food3"; // Сыр
	itm.name = "itmname_Food3";
	itm.describe = "itmdescr_Food3";
	itm.model = "1";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_15";
	itm.price = 30;
	itm.Weight = 1.8;
	itm.Solder_o.rare = 0.3;
	itm.Solder_o.min = 2;
	itm.Solder_o.max = 6;
	itm.Solder.rare = 0.1;
	itm.Solder.min = 1;
	itm.Solder.max = 3;
	itm.Warrior.rare = 0.1;
	itm.Warrior.min = 1;
	itm.Warrior.max = 4;
	itm.Monster.rare = 0;
	itm.Monster.min = 0;
	itm.Monster.max = 0;
	itm.Food.tex = 3;
	itm.Food.pic = 1;
	itm.Food.selpic = 9;
	itm.Food.energy = 18.0;
	itm.Food.energy.speed = 15.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Food4"; // рыба
	itm.name = "itmname_Food4";
	itm.describe = "itmdescr_Food4";
	itm.model = "fish" + (rand(6)+1);
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_15";
	itm.price = 40;
	itm.Weight = 2.4;
	itm.Solder_o.rare = 0.3;
	itm.Solder_o.min = 2;
	itm.Solder_o.max = 6;
	itm.Solder.rare = 0.1;
	itm.Solder.min = 1;
	itm.Solder.max = 3;
	itm.Warrior.rare = 0.1;
	itm.Warrior.min = 1;
	itm.Warrior.max = 4;
	itm.Monster.rare = 0;
	itm.Monster.min = 0;
	itm.Monster.max = 0;
	itm.Food.tex = 3;
	itm.Food.pic = 2;
	itm.Food.selpic = 10;
	itm.Food.energy = 24.0;
	itm.Food.energy.speed = 10.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Food5"; // Мясо
	itm.name = "itmname_Food5";
	itm.describe = "itmdescr_Food5";
	itm.model = "Meat";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_15";
	itm.price = 50;
	itm.Weight = 3.0;
	itm.Solder_o.rare = 0.3;
	itm.Solder_o.min = 2;
	itm.Solder_o.max = 6;
	itm.Solder.rare = 0.1;
	itm.Solder.min = 1;
	itm.Solder.max = 3;
	itm.Warrior.rare = 0.1;
	itm.Warrior.min = 1;
	itm.Warrior.max = 4;
	itm.Monster.rare = 0;
	itm.Monster.min = 0;
	itm.Monster.max = 0;
	itm.Food.tex = 3;
	itm.Food.pic = 3;
	itm.Food.selpic = 11;
	itm.Food.energy = 30.0;
	itm.Food.energy.speed = 5.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "QuestDuelNotice";
	itm.name = "itmname_QuestDuelNotice";
	itm.describe = "itmdescr_QuestDuelNotice";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_12";
	itm.price = 1;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	//Gregg Дозор

	makeref(itm,Items[n]);
	itm.id = "Dozor_Mekakhrom";
	itm.name = "itmname_Dozor_Mekakhrom";
	itm.describe = "itmdescr_Dozor_Mekakhrom";
	itm.model = "";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_15";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Dozor_Key";
	itm.name = "itmname_Dozor_Key";
	itm.describe = "itmdescr_Dozor_Key";
	itm.model = "";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_15";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Dozor_Storm";
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Dozor_Storm";
	itm.describe = "itmdescr_Dozor_Storm";
	itm.model = "";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_15";
	itm.price = 15000;
	itm.Weight = 1.0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Dozor_HorseShoe";
	itm.groupID = JEWELRY_INDIAN_LEFT_ITEM_TYPE;
	itm.name = "itmname_Dozor_HorseShoe";
	itm.describe = "itmdescr_Dozor_HorseShoe";
	itm.model = "";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_15";
	itm.price = 12500;
	itm.Weight = 1.5;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Dozor_Mirror";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Dozor_Mirror";
	itm.describe = "itmdescr_Dozor_Mirror";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_15";
	itm.price = 10000;
	itm.Weight = 0.5;
	itm.ItemType = "QUESTITEMS";
	n++;

	// Рюкзаки
    	makeref(itm,Items[n]);
	itm.id = "BackPack1";
	itm.groupID = BACKPACK_ITEM_TYPE;
	itm.name = "itmname_BackPack1";
	itm.describe = "itmdescr_BackPack1";
	itm.folder = "items";
	itm.model = "1";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_15";
	itm.price = 5000;
	itm.Weight = 1.0;
	itm.BackPackWeight = 10;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.ItemType = "WEAPON";
	n++;

    	makeref(itm,Items[n]);
	itm.id = "BackPack2";
	itm.groupID = BACKPACK_ITEM_TYPE;
	itm.name = "itmname_BackPack2";
	itm.describe = "itmdescr_BackPack2";
	itm.folder = "items";
	itm.model = "1";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_15";
	itm.price = 7500;
	itm.Weight = 1.5;
	itm.BackPackWeight = 20;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.ItemType = "WEAPON";
	n++;

    	makeref(itm,Items[n]);
	itm.id = "BackPack3";
	itm.groupID = BACKPACK_ITEM_TYPE;
	itm.name = "itmname_BackPack3";
	itm.describe = "itmdescr_BackPack3";
	itm.folder = "items";
	itm.model = "1";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_15";
	itm.price = 10000;
	itm.Weight = 2.0;
	itm.BackPackWeight = 36;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.ItemType = "WEAPON";
	n++;

    	makeref(itm,Items[n]);
	itm.id = "BackPack4";
	itm.groupID = BACKPACK_ITEM_TYPE;
	itm.name = "itmname_BackPack4";
	itm.describe = "itmdescr_BackPack4";
	itm.folder = "items";
	itm.model = "1";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_15";
	itm.price = 12500;
	itm.Weight = 2.5;
	itm.BackPackWeight = 50;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.ItemType = "WEAPON";
	n++;

    	makeref(itm,Items[n]);
	itm.id = "BackPack5";
	itm.groupID = BACKPACK_ITEM_TYPE;
	itm.name = "itmname_BackPack5";
	itm.describe = "itmdescr_BackPack5";
	itm.folder = "items";
	itm.model = "1";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_15";
	itm.price = 20000;
	itm.Weight = 3;
	itm.BackPackWeight = 75;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.ItemType = "WEAPON";
	n++;
	// в начате идут все без заполнения трупов
//==================PATENTS
    makeref(itm,Items[n]);
	itm.id = "patent_eng";
    itm.groupID = PATENT_ITEM_TYPE;
	itm.name = "itmname_patent_england";
	itm.describe = "itmdescr_patent_england";
	itm.model = "";
    itm.quest = "eng_flag_rise";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Nation = ENGLAND; //форма солдат
	itm.TitulCur = 1; // текущ звание
	itm.TitulCurNext = 0; // счетчик званий
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "patent_fra";
    itm.groupID = PATENT_ITEM_TYPE;
	itm.name = "itmname_patent_france";
	itm.describe = "itmdescr_patent_france";
	itm.model = "";
    itm.quest = "fra_flag_rise";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Nation = FRANCE; //форма солдат
	itm.TitulCur = 1; // текущ звание
	itm.TitulCurNext = 0; // счетчик званий
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "patent_spa";
    itm.groupID = PATENT_ITEM_TYPE;
	itm.name = "itmname_patent_spain";
	itm.describe = "itmdescr_patent_spain";
	itm.model = "";
    itm.quest = "spa_flag_rise";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Nation = SPAIN; //форма солдат
	itm.TitulCur = 1; // текущ звание
	itm.TitulCurNext = 0; // счетчик званий
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "patent_hol";
    itm.groupID = PATENT_ITEM_TYPE;
	itm.name = "itmname_patent_holland";
	itm.describe = "itmdescr_patent_holland";
	itm.model = "";
    itm.quest = "hol_flag_rise";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Nation = HOLLAND; //форма солдат
	itm.TitulCur = 1; // текущ звание
	itm.TitulCurNext = 0; // счетчик званий
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					WEAPONS   выбор оружия у офицера завязан на порядковый номер в списке, а не на крутизну!!!
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ОРУЖИЕ МАЛОГО ВЕСА
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    makeref(itm,Items[n]);
	itm.id = "unarmed"; // руки
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_unarmed";
	itm.describe = "itmdescr_unarmed";
	itm.model = "unarmed";
	itm.folder = "items";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_1";
	itm.price = 1;
	itm.Weight = 0.0;
	itm.dmg_min = 1.0;
	itm.dmg_max = 15.0;
	itm.piercing = 1;
	itm.minlevel = 0;
	itm.rare = 0.0001;
	itm.block = 0;
	itm.param.time = 0.05;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.special.valueSS = 2; 	// Резкий удар
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.dmg_min.min = 1.0;
	itm.Generation.dmg_min.max = 1.0;
	itm.Generation.dmg_max.min = 15.0;
	itm.Generation.dmg_max.max = 15.0;
	itm.Generation.Weight.min = 0.0;
	itm.Generation.Weight.max = 0.0;
	n++;

    makeref(itm,Items[n]);
	itm.id = "rabble"; // кочерга
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_rabble";
	itm.describe = "itmdescr_rabble";
	itm.model = "kocherg";
	itm.folder = "items";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_10";
	itm.price = 5;
	itm.Weight = 4;
	itm.dmg_min = 1.0;
	itm.dmg_max = 25.0;
	itm.piercing = 5;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 19;
	itm.param.time = 0.05;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	itm.special.valueSS = 5; 	// Резкий удар
	itm.special.valueStS = 5; // Стан
	itm.special.valueT = 1; 	// Травмы
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.dmg_min.min = 1.0;
	itm.Generation.dmg_min.max = 1.0;
	itm.Generation.dmg_max.min = 25.0;
	itm.Generation.dmg_max.max = 25.0;
	itm.Generation.Weight.min = 4.0;
	itm.Generation.Weight.max = 4.0;
	n++;

    makeref(itm,Items[n]);
	itm.id = "slave_01"; // Гарпун
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_slave_01";
	itm.describe = "itmdescr_slave_01";
	itm.model = "kocherg";
	itm.folder = "items";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_15";
	itm.price = 150;
	itm.Weight = 1.0;
	itm.dmg_min = 1.0;
	itm.dmg_max = 25.0;
	itm.piercing = 5;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 19;
	itm.param.time = 0.05;
	itm.special.valueT = 1; 	// Травмы
	itm.special.valueB = 5; 	// Кровоток
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	n++;

	makeref(itm,Items[n]);
	itm.id = "monkrab"; // оружие макак и крабов
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_monkrab";
	itm.describe = "itmdescr_monkrab";
	itm.model = "unarmed";
	itm.folder = "items";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_1";
	itm.price = 100000;
	itm.Weight = 3.0;
	itm.dmg_min = 15.0;
	itm.dmg_max = 60.0;
	itm.piercing = 100;
	itm.minlevel = 0;
	itm.rare = 0.001;
	itm.block = 100;
	itm.param.time = 0.05;
	itm.special.valueP = 20; //Яд
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	n++;

	// ГПК Дага
	makeref(itm,Items[n]);
	itm.id = "blade5";  //Кинжал
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade5";
	itm.describe = "itmdescr_blade5";
	itm.folder = "items";
	itm.model = "blade5";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 80;
	itm.Weight = 0.8 + fRandSmall(0.2); // 1;
	// boal 19.01.2004 <--
	itm.dmg_min = 1.0 + fRandSmall(2.0); // 3.0;
	itm.dmg_max = 7.0 + fRandSmall(3.0); // 35.0;
	itm.piercing = 25;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 5;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	itm.special.valueB = 5; 	// Кровоток
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 1.0;
	itm.Generation.dmg_min.max = 3.0;
	itm.Generation.dmg_max.min = 7.0;
	itm.Generation.dmg_max.max = 10.0;
	itm.Generation.Weight.min = 0.8;
	itm.Generation.Weight.max = 1.0;
	n++;

	// ГПК Венецианская шпага
    makeref(itm,Items[n]);
	itm.id = "blade2";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade2";
	itm.describe = "itmdescr_blade2";
	itm.folder = "items";
	itm.model = "blade2";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 120;
	itm.Weight = 2.8 + fRandSmall(0.2); // 3;
	// boal 19.01.2004 <--
	itm.dmg_min = 5.0 + rand(5); // 5.0;
	itm.dmg_max = 40.0 + rand(3); // 40.0;
	itm.piercing = 15;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 10;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 5.0;
	itm.Generation.dmg_min.max = 10.0;
	itm.Generation.dmg_max.min = 40.0;
	itm.Generation.dmg_max.max = 43.0;
	itm.Generation.Weight.min = 2.8;
	itm.Generation.Weight.max = 3.0;
	n++;

	// ГПК Скорпион
	makeref(itm,Items[n]);
	itm.id = "blade6";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade6";
	itm.describe = "itmdescr_blade6";
	itm.folder = "items";
	itm.model = "blade6";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 200;
	itm.Weight = 2.7 + fRandSmall(0.2); // 2.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 10.0 + rand(2); // 8.0;
	itm.dmg_max = 45.0 + rand(5); // 46.0;
	itm.piercing = 15;
	itm.special.valueCrB = 4; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 15;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 10.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 2.7;
	itm.Generation.Weight.max = 2.9;
	n++;

	// ГПК Сарагоса
	makeref(itm,Items[n]);
	itm.id = "blade9";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade9";
	itm.describe = "itmdescr_blade9";
	itm.folder = "items";
	itm.model = "blade9";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 600;
	itm.Weight = 2.5 + fRandSmall(0.4); // 2.8;
	// boal 19.01.2004 <--
	itm.dmg_min = 10.0 + rand(2); // 10.0;
	itm.dmg_max = 45.0 + rand(5); // 45.0;
	itm.piercing = 20;
	itm.special.valueSS = 4; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 15;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 10.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 2.5;
	itm.Generation.Weight.max = 2.9;
	n++;

	// ГПК Катана
	makeref(itm,Items[n]);
	itm.id = "blade14";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade14";
	itm.describe = "itmdescr_blade14";
	itm.folder = "items";
	itm.model = "blade14";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 400;
	itm.Weight = 3.0;// 3.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 20.0;// 20.0;
	itm.dmg_max = 66.0;// 60.0;
	itm.piercing = 20;
	itm.special.valueCrB = 10; //Буст крита
	itm.special.valueSS = 5; //Резкий удар
	itm.special.valueBB = 3; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 60;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
    itm.FencingType = "FencingLight";
    itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// для патча 1.2.5 фиксируем статы

	n++;

	// ГПК Маринера
	makeref(itm,Items[n]);
	itm.id = "blade19";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade19";
	itm.describe = "itmdescr_blade19";
	itm.folder = "items";
	itm.model = "blade19";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 700;
	itm.Weight = 2.5 + fRandSmall(0.2); // 2.6;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(2);// 12.0;
	itm.dmg_max = 50.0 + rand(5);// 50.0;
	itm.piercing = 20;
	itm.special.valueCrB = 7; //Буст крита
	itm.special.valueStS = 4; //Стан
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 60;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 14.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 55.0;
	itm.Generation.Weight.min = 2.5;
	itm.Generation.Weight.max = 2.7;
	n++;

	// ГПК Испанская рапира
	makeref(itm,Items[n]);
	itm.id = "blade22";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade22";
	itm.describe = "itmdescr_blade22";
	itm.folder = "items";
	itm.model = "blade22";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 900;
	itm.Weight = 2.5 + fRandSmall(0.2); // 2.7;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(2); // 13.0;
	itm.dmg_max = 50.0 + rand(5); // 53.0;
	itm.piercing = 44;
	itm.special.valueCrB = 4; //Буст крита
	itm.special.valueStS = 7; //Стан
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 73;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 14.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 55.0;
	itm.Generation.Weight.min = 2.5;
	itm.Generation.Weight.max = 2.7;
	n++;

	// ГПК Бретта
	makeref(itm,Items[n]);
	itm.id = "blade23";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade23";
	itm.describe = "itmdescr_blade23";
	itm.folder = "items";
	itm.model = "blade23";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 1300;
	itm.Weight = 2.4 + fRandSmall(0.2);// 2.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 16.0 + rand(2); // 14.0;
	itm.dmg_max = 56.0 + rand(9); // 55.0;
	itm.piercing = 50;
	itm.special.valueCrB = 12; //Буст крита
	itm.special.valueSS = 6; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 75;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 16.0;
	itm.Generation.dmg_min.max = 18.0;
	itm.Generation.dmg_max.min = 56.0;
	itm.Generation.dmg_max.max = 65.0;
	itm.Generation.Weight.min = 2.4;
	itm.Generation.Weight.max = 2.6;
	n++;

	// ГПК Моргана
	makeref(itm,Items[n]);
	itm.id = "blade27";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade27";
	itm.describe = "itmdescr_blade27";
	itm.folder = "items";
	itm.model = "blade27";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_8";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 2.4 + fRandSmall(0.2); //2.9;
	// boal 19.01.2004 <--
	itm.dmg_min = 17.0 + rand(2); // 18.0;
	itm.dmg_max = 64.0 + rand(3); // 65.0;
	itm.piercing = 99.0;
	itm.special.valueStS = 9; //Стан
	itm.special.valueSS = 9; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 99.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 17.0;
	itm.Generation.dmg_min.max = 19.0;
	itm.Generation.dmg_max.min = 64.0;
	itm.Generation.dmg_max.max = 68.0;
	itm.Generation.Weight.min = 2.4;
	itm.Generation.Weight.max = 2.6;
	n++;

	// ГПК Фламберж
	makeref(itm,Items[n]);
	itm.id = "blade32";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade32";
	itm.describe = "itmdescr_blade32";
	itm.folder = "items";
	itm.model = "blade32";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 3000;
	itm.Weight = 3.0 + fRandSmall(0.4); // 4.4;
	// boal 19.01.2004 <--
	itm.dmg_min = 15.0 + rand(3); // 18.0;
	itm.dmg_max = 65.0 + rand(5); // 70.0;
	itm.piercing = 90.0;
	itm.special.valueBB = 4; //Пролом блока
	itm.special.valueSS = 4; //Резкий удар
	itm.special.valueB = 10; 	//Кровоток
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 92.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 15.0;
	itm.Generation.dmg_min.max = 18.0;
	itm.Generation.dmg_max.min = 65.0;
	itm.Generation.dmg_max.max = 70.0;
	itm.Generation.Weight.min = 3.0;
	itm.Generation.Weight.max = 3.4;
	n++;

	// ККС, Саксенфедер
	makeref(itm,Items[n]);
	itm.id = "blade36";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade36";
	itm.describe = "itmdescr_blade36";
	itm.folder = "items";
	itm.model = "blade36";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 2.3 + fRandSmall(0.2);
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(4);
	itm.dmg_max = 45.0 + rand(10);
	itm.piercing = 99.0;
	itm.special.valueBB = 7; //Пролом блока
	itm.special.valueSS = 4; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 99.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 16.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 55.0;
	itm.Generation.Weight.min = 2.3;
	itm.Generation.Weight.max = 2.5;
	n++;

	// ККС, Гнев Пророка (Персидская сабля)
	makeref(itm,Items[n]);
	itm.id = "blade37";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade37";
	itm.describe = "itmdescr_blade37";
	itm.folder = "items";
	itm.model = "blade37";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 2.6 + fRandSmall(0.2);
	// boal 19.01.2004 <--
	itm.dmg_min = 10.0 + rand(4);
	itm.dmg_max = 55.0 + rand(5);
	itm.piercing = 99.0;
	itm.special.valueCB = 6; //Пролом кирасы
	itm.special.valueStS = 6; //Стан
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 99.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 10.0;
	itm.Generation.dmg_min.max = 14.0;
	itm.Generation.dmg_max.min = 55.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 2.6;
	itm.Generation.Weight.max = 2.8;
	n++;

	// ККС, Асоледа
	makeref(itm,Items[n]);
	itm.id = "blade38";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade38";
	itm.describe = "itmdescr_blade38";
	itm.folder = "items";
	itm.model = "blade38";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 2.2 + fRandSmall(0.3);
	// boal 19.01.2004 <--
	itm.dmg_min = 15.0 + rand(3);
	itm.dmg_max = 65.0 + rand(4);
	itm.piercing = 99.0;
	itm.special.valueCrB = 18; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 99.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 15.0;
	itm.Generation.dmg_min.max = 18.0;
	itm.Generation.dmg_max.min = 65.0;
	itm.Generation.dmg_max.max = 69.0;
	itm.Generation.Weight.min = 2.2;
	itm.Generation.Weight.max = 2.5;
	n++;

	// ККС, Стокката
	makeref(itm,Items[n]);
	itm.id = "blade45";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade45";
	itm.describe = "itmdescr_blade45";
	itm.folder = "items";
	itm.model = "blade45";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_16";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 2.6 + fRandSmall(0.3);
	// boal 19.01.2004 <--
	itm.dmg_min = 10.0 + rand(2);
	itm.dmg_max = 45.0 + rand(5);
	itm.piercing = 99.0;
	itm.special.valueStS = 4; // Стан
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 99.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 10.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 2.6;
	itm.Generation.Weight.max = 2.9;
	n++;

	// ГПК Паппенхаймер
    makeref(itm,Items[n]);
	itm.id = "blade26";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade26";
	itm.describe = "itmdescr_blade26";
	itm.folder = "items";
	itm.model = "blade26";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_8";
	// boal 19.01.2004 -->
	itm.price = 2500;
	itm.Weight = 2.4 + fRandSmall(0.4); // 4.7;
	// boal 19.01.2004 <--
	itm.dmg_min = 16.0 + rand(3); // 24.0;
	itm.dmg_max = 63.0 + rand(5); // 70.0;
	itm.piercing = 88.0;
	itm.special.valueCrB = 6; //Буст крита
	itm.special.valueStS = 6; //Стан
	itm.special.valueCB = 6; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 72.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 16.0;
	itm.Generation.dmg_min.max = 19.0;
	itm.Generation.dmg_max.min = 63.0;
	itm.Generation.dmg_max.max = 68.0;
	itm.Generation.Weight.min = 2.4;
	itm.Generation.Weight.max = 2.8;
	n++;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ОРУЖИЕ СРЕДНЕГО ВЕСА
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ГПК Канонирский тесак
	makeref(itm,Items[n]);
	itm.id = "blade1";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade1";
	itm.describe = "itmdescr_blade1";
	itm.model = "blade1";
	itm.folder = "items";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 50;
	itm.Weight = 4.5 + fRandSmall(1.5); // 4.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 6.0 + rand(6); // 6.0;
	itm.dmg_max = 45.0 + rand(5); // 45.0;
	itm.piercing = 10;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 5;
	itm.param.time = 0.05;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 6.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 6.0;
	n++;

	// ГПК Пехотная сабля
    makeref(itm,Items[n]);
	itm.id = "blade4";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade4";
	itm.describe = "itmdescr_blade4";
	itm.folder = "items";
	itm.model = "blade4";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 100;
	itm.Weight = 4.5 + fRandSmall(1.5); // 4.6;
	// boal 19.01.2004 <--
	itm.dmg_min = 6.0 + rand(6); // 8.0;
	itm.dmg_max = 45.0 + rand(5); // 50.0;
	itm.piercing = 30;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 1;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 6.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 6.0;
	n++;

	// ГПК Клевец
    makeref(itm,Items[n]);
	itm.id = "topor3";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_topor3";
	itm.describe = "itmdescr_topor3";
	itm.folder = "items";
	itm.model = "topor3";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 150;
	itm.Weight = 4.5 + fRandSmall(1.5); // 6;
	// boal 19.01.2004 <--
	itm.dmg_min = 6.0 + rand(6); // 10.0;
	itm.dmg_max = 45.0 + rand(5); // 60.0;
	itm.piercing = 14.0;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.block = 2.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 6.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 6.0;
	n++;

	// ГПК Кайман
	makeref(itm,Items[n]);
	itm.id = "blade3";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade3";
	itm.describe = "itmdescr_blade3";
	itm.folder = "items";
	itm.model = "blade3";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 200;
	itm.Weight = 4.5 + fRandSmall(1.5); // 5.3;
	// boal 19.01.2004 <--
	itm.dmg_min = 6.0 + rand(6); // 12.0;
	itm.dmg_max = 45.0 + rand(5); // 55.0;
	itm.piercing = 60;
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 5;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 6.0;
	itm.Generation.dmg_min.max = 12.0;
	itm.Generation.dmg_max.min = 45.0;
	itm.Generation.dmg_max.max = 50.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 6.0;
	n++;

	// ГПК Бильбо
	makeref(itm,Items[n]);
	itm.id = "blade7";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade7";
	itm.describe = "itmdescr_blade7";
	itm.folder = "items";
	itm.model = "blade7";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 250;
	itm.Weight = 4.5 + fRandSmall(0.5); // 4.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 13.0;
	itm.dmg_max = 55.0 + rand(5); // 55.0;
	itm.piercing = 18;
	itm.special.valueSS = 3; //Резкий удар
	itm.special.valueBB = 3; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 5;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 55.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 5.0;
	n++;

	// ГПК Катцбальгер
    makeref(itm,Items[n]);
	itm.id = "blade12";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade12";
	itm.describe = "itmdescr_blade12";
	itm.folder = "items";
	itm.model = "blade12";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 300;
	itm.Weight = 4.5 + fRandSmall(0.5); // 6;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 14.0;
	itm.dmg_max = 55.0 + rand(5); // 65.0;
	itm.piercing = 30;
	itm.special.valueStS = 6; //Стан
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 20;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 55.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 5.0;
	n++;

	// ГПК Висельник
    makeref(itm,Items[n]);
	itm.id = "blade18";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade18";
	itm.describe = "itmdescr_blade18";
	itm.folder = "items";
	itm.model = "blade18";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 400;
	itm.Weight = 4.5 + fRandSmall(0.5); // 5.4;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 16.0;
	itm.dmg_max = 55.0 + rand(5); // 60.0;
	itm.piercing = 35;
	itm.special.valueCrB = 4; //Буст крита
	itm.special.valueSS = 2; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 35;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 55.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 5.0;
	n++;

	// ГПК Нобиль
	makeref(itm,Items[n]);
	itm.id = "blade30";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade30";
	itm.describe = "itmdescr_blade30";
	itm.folder = "items";
	itm.model = "blade30";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 600;
	itm.Weight = 4.1 + fRandSmall(0.4); // 4.1;
	// boal 19.01.2004 <--
	itm.dmg_min = 20.0 + rand(5); // 18.0;
	itm.dmg_max = 80.0 + rand(10); // 63.0;
	itm.piercing = 55.0;
	itm.special.valueCrB = 8; //Буст крита
	itm.special.valueCB = 8; //Пролом кирасы
	itm.special.valueSS = 8; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 40.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 20.0;
	itm.Generation.dmg_min.max = 25.0;
	itm.Generation.dmg_max.min = 80.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 4.1;
	itm.Generation.Weight.max = 4.5;
	n++;

	// ГПК Шамшир
	makeref(itm,Items[n]);
	itm.id = "blade31";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade31";
	itm.describe = "itmdescr_blade31";
	itm.folder = "items";
	itm.model = "blade31";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 800;
	itm.Weight = 4.6 + fRandSmall(0.2); // 4.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 18.0 + rand(5); // 19.0;
	itm.dmg_max = 65.0 + rand(10); // 64.0;
	itm.piercing = 50.0;
	itm.special.valueBB = 7; //Пролом блока
	itm.special.valueCrB = 7; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 65.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 18.0;
	itm.Generation.dmg_min.max = 23.0;
	itm.Generation.dmg_max.min = 65.0;
	itm.Generation.dmg_max.max = 75.0;
	itm.Generation.Weight.min = 4.6;
	itm.Generation.Weight.max = 4.8;
	n++;

	// ГПК Чиавона
	makeref(itm,Items[n]);
	itm.id = "blade24";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade24";
	itm.describe = "itmdescr_blade24";
	itm.folder = "items";
	itm.model = "blade24";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_8";
	// boal 19.01.2004 -->
	itm.price = 1500;
	itm.Weight = 4.1 + fRandSmall(0.4); // 4.3;
	// boal 19.01.2004 <--
	itm.dmg_min = 20.0 + rand(5); // 20.0;
	itm.dmg_max = 80.0 + rand(10); // 66.0;
	itm.piercing = 58.0;
	itm.special.valueSS = 12; //Резкий удар
	itm.special.valueStS = 12; //Стан
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 45.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 20.0;
	itm.Generation.dmg_min.max = 25.0;
	itm.Generation.dmg_max.min = 80.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 4.1;
	itm.Generation.Weight.max = 4.5;
	n++;

	// ГПК Карабела
	makeref(itm,Items[n]);
	itm.id = "blade25";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade25";
	itm.describe = "itmdescr_blade25";
	itm.folder = "items";
	itm.model = "blade25";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_8";
	// boal 19.01.2004 -->
	itm.price = 1700;
	itm.Weight = 4.1 + fRandSmall(0.4); // 4.2;
	// boal 19.01.2004 <--
	itm.dmg_min = 20.0 + rand(5); // 21.0;
	itm.dmg_max = 80.0 + rand(5); // 65.0;
	itm.piercing = 60.0;
	itm.special.valueCB = 12; //Пролом кирасы
	itm.special.valueBB = 12; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 70.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 20.0;
	itm.Generation.dmg_min.max = 25.0;
	itm.Generation.dmg_max.min = 80.0;
	itm.Generation.dmg_max.max = 85.0;
	itm.Generation.Weight.min = 4.1;
	itm.Generation.Weight.max = 4.5;
	n++;

	// ГПК Скаллоп
    makeref(itm,Items[n]);
	itm.id = "blade34";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade34";
	itm.describe = "itmdescr_blade34";
	itm.folder = "items";
	itm.model = "blade34";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 2000;
	itm.Weight = 4.6 + fRandSmall(0.2); // 5.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 18.0 + rand(5); // 23.0;
	itm.dmg_max = 65.0 + rand(10); // 70.0;
	itm.piercing = 90.0;
	itm.special.valueStS = 5; //Стан
	itm.special.valueSS = 9; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 70.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 18.0;
	itm.Generation.dmg_min.max = 23.0;
	itm.Generation.dmg_max.min = 65.0;
	itm.Generation.dmg_max.max = 75.0;
	itm.Generation.Weight.min = 4.6;
	itm.Generation.Weight.max = 4.8;
	n++;

	// Gregg Катар
	makeref(itm,Items[n]);
	itm.id = "katar";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_katar";
	itm.describe = "itmdescr_katar";
	itm.model = "katar";
	itm.folder = "items";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_14";
	itm.price = 50;
	itm.Weight = 4.5;
	itm.dmg_min = 35.0;
	itm.dmg_max = 90.0;
	itm.piercing = 50;
	itm.special.valueCB = 16; //Пролом кирасы
	itm.special.valueSS = 4; //Резкий удар
	itm.special.valueStS = 4; //Стан
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 50;
	itm.param.time = 0.05;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// LEO: Меч Тритона
	makeref(itm,Items[n]);
	itm.id = "blackbeard_sword_baron";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blackbeard_sword_baron";
	itm.describe = "itmdescr_blackbeard_sword_baron";
	itm.model = "blackbeard_sword_baron";
	itm.folder = "items";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_20";
	itm.price = 50;
	itm.Weight = 4.0;
	itm.dmg_min = 31.0;
	itm.dmg_max = 85.0;
	itm.piercing = 50;
	itm.special.valueBB = 8; 	// Пролом блока
	itm.special.valueCrB = 8; // Буст крита
	itm.special.valueStS = 8; //Стан
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 50;
	itm.param.time = 0.05;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// ККС, Скимитар
    makeref(itm,Items[n]);
	itm.id = "blade39";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade39";
	itm.describe = "itmdescr_blade39";
	itm.folder = "items";
	itm.model = "blade39";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 2500;
	itm.Weight = 4.0 + fRandSmall(0.6);
	// boal 19.01.2004 <--
	itm.dmg_min = 18.0 + rand(7);
	itm.dmg_max = 60.0 + rand(10);
	itm.piercing = 88.0;
	itm.special.valueCB = 5; //Пролом кирасы
	itm.special.valueBB = 5; //Пролом блока
	itm.special.valueCrB = 4; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 72.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 18.0;
	itm.Generation.dmg_min.max = 25.0;
	itm.Generation.dmg_max.min = 60.0;
	itm.Generation.dmg_max.max = 70.0;
	itm.Generation.Weight.min = 4.0;
	itm.Generation.Weight.max = 4.6;
	n++;

	// ККС, Мадонна
    makeref(itm,Items[n]);
	itm.id = "blade40";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade40";
	itm.describe = "itmdescr_blade40";
	itm.folder = "items";
	itm.model = "blade40";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 2500;
	itm.Weight = 4.6 + fRandSmall(0.8);
	// boal 19.01.2004 <--
	itm.dmg_min = 18.0 + rand(5);
	itm.dmg_max = 65.0 + rand(15);
	itm.piercing = 88.0;
	itm.special.valueStS = 14; //Стан
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 72.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 18.0;
	itm.Generation.dmg_min.max = 23.0;
	itm.Generation.dmg_max.min = 65.0;
	itm.Generation.dmg_max.max = 80.0;
	itm.Generation.Weight.min = 4.6;
	itm.Generation.Weight.max = 5.4;
	n++;

	// ККС, Сторта Барбариго
    makeref(itm,Items[n]);
	itm.id = "blade41";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade41";
	itm.describe = "itmdescr_blade41";
	itm.folder = "items";
	itm.model = "blade41";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 2500;
	itm.Weight = 4.2 + fRandSmall(0.6);
	// boal 19.01.2004 <--
	itm.dmg_min = 24.0 + rand(2);
	itm.dmg_max = 80.0 + rand(10);
	itm.piercing = 88.0;
	itm.special.valueStS = 10; //Стан
	itm.special.valueSS = 10; //Резкий удар
	itm.special.valueCrB = 4; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 72.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 24.0;
	itm.Generation.dmg_min.max = 26.0;
	itm.Generation.dmg_max.min = 80.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 4.2;
	itm.Generation.Weight.max = 4.8;
	n++;

	// ГПК Фламберг Полутроручный
	makeref(itm,Items[n]);
	itm.id = "blade201";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade201";
	itm.describe = "itmdescr_blade201";
	itm.folder = "items";
	itm.model = "blade201";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_19";
	itm.price = 3000;
	itm.Weight = 4.2;
	itm.dmg_min = 33.0;
	itm.dmg_max = 80.0;
	itm.piercing = 90.0;
	itm.special.valueCrB = 7;// Буст крита
	itm.special.valueSS = 10;//Резкий удар
	itm.special.valueB = 7;//Кровоток
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 92.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// ККС, Офицерский Клеванг
    makeref(itm,Items[n]);
	itm.id = "blade46";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade46";
	itm.describe = "itmdescr_blade46";
	itm.folder = "items";
	itm.model = "blade46";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_16";
	// boal 19.01.2004 -->
	itm.price = 2500;
	itm.Weight = 4.3 + fRandSmall(0.6);
	// boal 19.01.2004 <--
	itm.dmg_min = 18.0 + rand(5);
	itm.dmg_max = 68.0 + rand(10);
	itm.piercing = 88.0;
	itm.special.valueStS = 4; //Стан
	itm.special.valueCrB = 10; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 72.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 18.0;
	itm.Generation.dmg_min.max = 23.0;
	itm.Generation.dmg_max.min = 68.0;
	itm.Generation.dmg_max.max = 78.0;
	itm.Generation.Weight.min = 4.3;
	itm.Generation.Weight.max = 4.9;
	n++;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ОРУЖИЕ БОЛЬШОГО ВЕСА
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ГПК Строевой фальшион
	makeref(itm,Items[n]);
	itm.id = "blade10";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade10";
	itm.describe = "itmdescr_blade10";
	itm.folder = "items";
	itm.model = "blade10";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 300;
	itm.Weight = 9.0 + fRandSmall(2.0);  // 7;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 10.0;
	itm.dmg_max = 50.0 + rand(10); // 60.0;
	itm.piercing = 50;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 10;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 11.0;
	n++;

	// ГПК Кортелач
    makeref(itm,Items[n]);
	itm.id = "blade35";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade35";
	itm.describe = "itmdescr_blade35";
	itm.folder = "items";
	itm.model = "blade35";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 400;
	itm.Weight = 9.0 + fRandSmall(2.0); // 9;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 10.0;
	itm.dmg_max = 50.0 + rand(10); // 60.0;
	itm.piercing = 65.0;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 25.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 11.0;
	n++;

	// ГПК Госсемесер
	makeref(itm,Items[n]);
	itm.id = "blade8";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade8";
	itm.describe = "itmdescr_blade8";
	itm.folder = "items";
	itm.model = "blade8";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 450;
	itm.Weight = 8.5 + fRandSmall(1.5); // 7.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 15.0 + rand(5); // 14.0;
	itm.dmg_max = 60.0 + rand(10); // 65.0;
	itm.piercing = 35;
	itm.special.valueT = 3; //Травмы
	itm.special.valueBB = 7; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 20;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 15.0;
	itm.Generation.dmg_min.max = 20.0;
	itm.Generation.dmg_max.min = 60.0;
	itm.Generation.dmg_max.max = 70.0;
	itm.Generation.Weight.min = 8.5;
	itm.Generation.Weight.max = 10.0;
	n++;

	// ГПК Риттершверт
	makeref(itm,Items[n]);
	itm.id = "blade11";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade11";
	itm.describe = "itmdescr_blade11";
	itm.folder = "items";
	itm.model = "blade11";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 500;
	itm.Weight = 8.5 + fRandSmall(1.5); // 8;
	// boal 19.01.2004 <--
	itm.dmg_min = 15.0 + rand(5); // 16.0;
	itm.dmg_max = 60.0 + rand(10); // 70.0;
	itm.piercing = 60;
	itm.special.valueT = 3; //Травмы
	itm.special.valueSS = 7; //Резкий удар
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 25;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 15.0;
	itm.Generation.dmg_min.max = 20.0;
	itm.Generation.dmg_max.min = 60.0;
	itm.Generation.dmg_max.max = 70.0;
	itm.Generation.Weight.min = 8.5;
	itm.Generation.Weight.max = 10.0;
	n++;

	// ГПК Кракемарт
	makeref(itm,Items[n]);
	itm.id = "blade13";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade13";
	itm.describe = "itmdescr_blade13";
	itm.folder = "items";
	itm.model = "blade13";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 600;
	itm.Weight = 9.0 + fRandSmall(0.5);
	// boal 19.01.2004 <--
	itm.dmg_min = 35.0 + rand(10);
	itm.dmg_max = 100.0 + rand(10);
	itm.piercing = 65;
	itm.special.valueT = 10; //Травмы
	itm.special.valueSS = 10; //Резкий удар
	itm.special.valueCB = 10; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 20;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 35.0;
	itm.Generation.dmg_min.max = 45.0;
	itm.Generation.dmg_max.min = 100.0;
	itm.Generation.dmg_max.max = 110.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 9.5;
	n++;

	// ГПК Боевой топор
    makeref(itm,Items[n]);
	itm.id = "topor1";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_topor1";
	itm.describe = "itmdescr_topor1";
	itm.folder = "items";
	itm.model = "topor1";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 650;
	itm.Weight = 9.0 + fRandSmall(2.0); // 10;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 10.0;
	itm.dmg_max = 50.0 + rand(10); // 60.0;
	itm.piercing = 70.0;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 3.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 11.0;
	n++;

	// ГПК Сторта
	makeref(itm,Items[n]);
	itm.id = "blade15";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade15";
	itm.describe = "itmdescr_blade15";
	itm.folder = "items";
	itm.model = "blade15";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 700;
	itm.Weight = 8.5 + fRandSmall(1.5); // 8.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 24.0 + rand(6); // 22.0;
	itm.dmg_max = 75.0 + rand(15); // 75.0;
	itm.piercing = 55;
	itm.special.valueT = 6; //Травмы
	itm.special.valueCrB = 4; //Буст крита
	itm.special.valueCB = 10; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 25;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 24.0;
	itm.Generation.dmg_min.max = 30.0;
	itm.Generation.dmg_max.min = 75.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 8.5;
	itm.Generation.Weight.max = 10.0;
	n++;

	// ГПК Рейтарский палаш
	makeref(itm,Items[n]);
	itm.id = "blade16";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade16";
	itm.describe = "itmdescr_blade16";
	itm.folder = "items";
	itm.model = "blade16";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 800;
	itm.Weight = 8.5 + fRandSmall(1.5); // 9.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 15.0 + rand(5); // 22.0;
	itm.dmg_max = 60.0 + rand(10); // 80.0;
	itm.piercing = 45;
	itm.special.valueT = 3; //Травмы
	itm.special.valueCrB = 7; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 35;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 15.0;
	itm.Generation.dmg_min.max = 20.0;
	itm.Generation.dmg_max.min = 60.0;
	itm.Generation.dmg_max.max = 70.0;
	itm.Generation.Weight.min = 8.5;
	itm.Generation.Weight.max = 10.0;
	n++;

	// ГПК Клеймор
	makeref(itm,Items[n]);
	itm.id = "blade17";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade17";
	itm.describe = "itmdescr_blade17";
	itm.folder = "items";
	itm.model = "blade17";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 900;
	itm.Weight = 9.0 + fRandSmall(2.0); // 11.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 12.0 + rand(3); // 24.0;
	itm.dmg_max = 50.0 + rand(10); // 90.0;
	itm.piercing = 65;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 10;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 12.0;
	itm.Generation.dmg_min.max = 15.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 60.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 11.0;
	n++;

	// ГПК Клейбэг
    makeref(itm,Items[n]);
	itm.id = "blade20";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade20";
	itm.describe = "itmdescr_blade20";
	itm.folder = "items";
	itm.model = "blade20";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 1000;
	itm.Weight = 9.0 + fRandSmall(0.5); // 8.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 35.0 + rand(10); // 25.0;
	itm.dmg_max = 100.0 + rand(10); // 93.0;
	itm.piercing = 65;
	itm.special.valueT = 10; //Травмы
	itm.special.valueSS = 15; //Резкий удар
	itm.special.valueCrB = 5; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 30;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 35.0;
	itm.Generation.dmg_min.max = 45.0;
	itm.Generation.dmg_max.min = 100.0;
	itm.Generation.dmg_max.max = 110.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 9.5;
	n++;

	// ГПК Бастард
	makeref(itm,Items[n]);
	itm.id = "blade21";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade21";
	itm.describe = "itmdescr_blade21";
	itm.folder = "items";
	itm.model = "blade21";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_3";
	// boal 19.01.2004 -->
	itm.price = 1100;
	itm.Weight = 8.5 + fRandSmall(1.5); // 10.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 25.0 + rand(7); // 26.0;
	itm.dmg_max = 70.0 + rand(20); // 100.0;
	itm.piercing = 75;
	itm.special.valueT = 10; //Травмы
	itm.special.valueCB = 5; //Пролом кирасы
	itm.special.valueStS = 5; //Стан
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 25;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 25.0;
	itm.Generation.dmg_min.max = 32.0;
	itm.Generation.dmg_max.min = 70.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 8.5;
	itm.Generation.Weight.max = 10.0;
	n++;

	// ГПК Валлонская шпага
	makeref(itm,Items[n]);
	itm.id = "blade33";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade33";
	itm.describe = "itmdescr_blade33";
	itm.folder = "items";
	itm.model = "blade33";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 1300;
	itm.Weight = 9.0 + fRandSmall(0.5); // 9;
	// boal 19.01.2004 <--
	itm.dmg_min = 35.0 + rand(10); // 27.0;
	itm.dmg_max = 100.0 + rand(10); // 95.0;
	itm.piercing = 70.0;
	itm.special.valueT = 5; //Травмы
	itm.special.valueCB = 15; //Пролом кирасы
	itm.special.valueBB = 10; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.block = 60.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 35.0;
	itm.Generation.dmg_min.max = 45.0;
	itm.Generation.dmg_max.min = 100.0;
	itm.Generation.dmg_max.max = 110.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 9.5;
	n++;

	// ГПК Танат
    makeref(itm,Items[n]);
	itm.id = "blade28";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade28";
	itm.describe = "itmdescr_blade28";
	itm.folder = "items";
	itm.model = "blade28";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 3000;
	itm.Weight = 9.4 + fRandSmall(0.3); // 9.3;
	// boal 19.01.2004 <--
	itm.dmg_min = 40.0 + rand(10); // 28.0;
	itm.dmg_max = 90.0 + rand(10); // 100.0;
	itm.piercing = 85.0;
	itm.special.valueT = 15; //Травмы
	itm.special.valueCB = 10; //Пролом кирасы
	itm.special.valueCrB = 5; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 75.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 40.0;
	itm.Generation.dmg_min.max = 50.0;
	itm.Generation.dmg_max.min = 90.0;
	itm.Generation.dmg_max.max = 100.0;
	itm.Generation.Weight.min = 9.4;
	itm.Generation.Weight.max = 9.7;
	n++;

	// ГПК Цвайхандер
    makeref(itm,Items[n]);
	itm.id = "blade202";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade202";
	itm.describe = "itmdescr_blade202";
	itm.folder = "items";
	itm.model = "blade202";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_19";
	itm.price = 3000;
	itm.Weight = 9.4 + fRandSmall(0.3); // 9.3;
	itm.dmg_min = 28.0 + rand(7); // 28.0;
	itm.dmg_max = 90.0 + rand(10); // 100.0;
	itm.piercing = 85.0;
	itm.special.valueBB = 7; //Пролом блока
	itm.special.valueSS = 6; //Резкий удар
	itm.special.valueT = 7; //Травмы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 75.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 28.0;
	itm.Generation.dmg_min.max = 35.0;
	itm.Generation.dmg_max.min = 90.0;
	itm.Generation.dmg_max.max = 100.0;
	itm.Generation.Weight.min = 9.4;
	itm.Generation.Weight.max = 9.7;
	n++;

	// ККС, Кханда
    makeref(itm,Items[n]);
	itm.id = "blade42";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade42";
	itm.describe = "itmdescr_blade42";
	itm.folder = "items";
	itm.model = "blade42";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_18";
	// boal 19.01.2004 -->
	itm.price = 3000;
	itm.Weight = 10.0 + fRandSmall(1.0);
	// boal 19.01.2004 <--
	itm.dmg_min = 35.0 + rand(5);
	itm.dmg_max = 85.0 + rand(5);
	itm.piercing = 85.0;
	itm.special.valueCrB = 10; //Буст крита
	itm.special.valueT = 10; //Травмы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 75.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 35.0;
	itm.Generation.dmg_min.max = 40.0;
	itm.Generation.dmg_max.min = 85.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 10.0;
	itm.Generation.Weight.max = 11.0;
	n++;

	// ККС, Нарвал
    makeref(itm,Items[n]);
	itm.id = "blade43";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade43";
	itm.describe = "itmdescr_blade43";
	itm.folder = "items";
	itm.model = "blade43";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_18";
	itm.price = 3000;
	itm.Weight = 9.0;
	itm.dmg_min = 44.0;
	itm.dmg_max = 115.0;
	itm.piercing = 85.0;
	itm.special.valueT = 8; //Травмы
	itm.special.valueStS = 12; //Стан
	itm.special.valueCrB = 10; //Буст крита
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 75.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// ККС, Мальтийский меч
    makeref(itm,Items[n]);
	itm.id = "blade44";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade44";
	itm.describe = "itmdescr_blade44";
	itm.folder = "items";
	itm.model = "blade44";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_18";
	itm.price = 3000;
	itm.Weight = 9.6;
	itm.dmg_min = 48.0;
	itm.dmg_max = 125.0;
	itm.piercing = 85.0;
	itm.special.valueT = 10; //Травмы
	itm.special.valueCB = 6; //Пролом кирасы
	itm.special.valueBB = 14; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 75.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// ГПК "Рейтарский чекан
	makeref(itm,Items[n]);
	itm.id = "topor2";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_topor2";
	itm.describe = "itmdescr_topor2";
	itm.folder = "items";
	itm.model = "topor2";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 3500;
	itm.Weight = 12.5 + fRandSmall(1.5); // 12.5;
	// boal 19.01.2004 <--
	itm.dmg_min = 32.0 + rand(8); // 35.0;
	itm.dmg_max = 100.0 + rand(15); // 120.0;
	itm.piercing = 95.0;
	itm.special.valueT = 5; //Травмы
	itm.special.valueCB = 15; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 20.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 32.0;
	itm.Generation.dmg_min.max = 40.0;
	itm.Generation.dmg_max.min = 100.0;
	itm.Generation.dmg_max.max = 115.0;
	itm.Generation.Weight.min = 12.5;
	itm.Generation.Weight.max = 14.0;
	n++;

	// ГПК Макуауитль
	makeref(itm,Items[n]);
	itm.id = "toporAZ";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_toporAZ";
	itm.describe = "itmdescr_toporAZ";
	itm.folder = "items";
	itm.model = "maquahuitl";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_13";
	// boal 19.01.2004 -->
	itm.price = 17500;
	itm.Weight = 12.5 + fRandSmall(1.5); // 15.0;
	// boal 19.01.2004 <--
	itm.dmg_min = 32.0 + rand(8); // 45.0;
	itm.dmg_max = 100.0 + rand(15); // 140.0;
	itm.piercing = 95.0;
	itm.special.valueT = 6; //Травмы
	itm.special.valueCrB = 6; //Буст крита
	itm.special.valueCB = 8; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 30.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "good";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 32.0;
	itm.Generation.dmg_min.max = 40.0;
	itm.Generation.dmg_max.min = 100.0;
	itm.Generation.dmg_max.max = 115.0;
	itm.Generation.Weight.min = 12.5;
	itm.Generation.Weight.max = 14.0;
	n++;

	//GUNS

	makeref(itm,Items[n]);
	itm.id = "pistol1";	//Пистоль
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol1";
	itm.describe = "itmdescr_pistol1";
	itm.folder = "items";
	itm.model = "pistol1";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 100;
	itm.Weight = 3;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 8;
	itm.dmg_min = 20.0;
	itm.dmg_max = 100.0;
	itm.accuracy = 30;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.quality = "poor";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol2";	//Колониальный пистолет
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol2";
	itm.describe = "itmdescr_pistol2";
	itm.folder = "items";
	itm.model = "pistol2";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 400;
	itm.Weight = 4;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 12;
	itm.dmg_min = 30.0;
	itm.dmg_max = 120.0;
	itm.accuracy = 50;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.quality = "ordinary";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol3"; //Тромбон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol3";
	itm.describe = "itmdescr_pistol3";
	itm.folder = "items";
	itm.model = "pistol3";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 800;
	itm.Weight = 6;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 22;
	itm.dmg_min = 50.0;
	itm.dmg_max = 175.0;
	itm.accuracy = 20;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.quality = "ordinary";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol6";  // Бок-пистолет
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol6";
	itm.describe = "itmdescr_pistol6";
	itm.folder = "items";
	itm.model = "pistol6";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 3600;
	itm.Weight = 5;
	// boal 19.01.2004 <--
	itm.chargeQ = 2;
	itm.chargespeed = 20;
	itm.dmg_min = 35.0;
	itm.dmg_max = 130.0;
	itm.accuracy = 60;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "good";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol5"; //Бретерский Пистолет
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol5";
	itm.describe = "itmdescr_pistol5";
	itm.folder = "items";
	itm.model = "pistol5";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_6";
	itm.price = 3800;
	// boal 19.01.2004 -->
	itm.Weight = 3;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 16;
	itm.dmg_min = 45.0;
	itm.dmg_max = 170.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol4"; // Четырёхствольный пистолет
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol4";
	itm.describe = "itmdescr_pistol4";
	itm.folder = "items";
	itm.model = "pistol4";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_6";
	itm.shown = 4;
	itm.price = 5000;
	// boal 19.01.2004 -->
	itm.Weight = 6;
	// boal 19.01.2004 <--
	itm.chargeQ = 4;
	itm.chargespeed = 28;
	itm.dmg_min = 40.0;
	itm.dmg_max = 140.0;
	itm.accuracy = 60;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol_grapebok"; //Трёхствольный дробовик
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol_grapebok";
	itm.describe = "itmdescr_pistol_grapebok";
	itm.folder = "items";
	itm.model = "pistol_grapebok";
	itm.picIndex = 5;
	itm.picTexture = "CSP_GUNS2";
	itm.price = 4100;
	// boal 19.01.2004 -->
	itm.Weight = 4.5;
	// boal 19.01.2004 <--
	itm.chargeQ = 3;
	itm.chargespeed = 16;
	itm.dmg_min = 30.0;
	itm.dmg_max = 120.0;
	itm.accuracy = 40;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "good";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol8"; //Бландербуз
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol8";
	itm.describe = "itmdescr_pistol8";
	itm.folder = "items";
	itm.model = "pistol8";
	itm.picIndex = 2;
	itm.picTexture = "CSP_GUNS2";
	itm.price = 4100;
	// boal 19.01.2004 -->
	itm.Weight = 5.5;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 16;
	itm.dmg_min = 50.0;
	itm.dmg_max = 175.0;
	itm.accuracy = 40;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol9"; //Двузарядный пистолет
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol9";
	itm.describe = "itmdescr_pistol9";
	itm.folder = "items";
	itm.model = "pistol9";
	itm.picIndex = 15;
	itm.picTexture = "CSP_GUNS2";
	itm.price = 5200;
	itm.Weight = 3.2;
	itm.chargeQ = 2;
	itm.chargespeed = 16;
	itm.dmg_min = 50.0;
	itm.dmg_max = 160.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "good";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "howdah"; //Гауда
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_howdah";
	itm.describe = "itmdescr_howdah";
	itm.folder = "items";
	itm.model = "howdah_black";
	itm.picIndex = 1;
	itm.picTexture = "CSP_GUNS2";
	itm.price = 10000;
	// boal 19.01.2004 -->
	itm.Weight = 4;
	// boal 19.01.2004 <--
	itm.chargeQ = 2;
	itm.chargespeed = 16;
	itm.dmg_min = 45.0;
	itm.dmg_max = 190.0;
	itm.accuracy = 40;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "grape_mushket"; //Склопетта
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_grape_mushket";
	itm.describe = "itmdescr_grape_mushket";
	itm.folder = "items";
	itm.model = "mortar";
	itm.picIndex = 11;
	itm.picTexture = "CSP_GUNS2";
	itm.price = 100000;
	// boal 19.01.2004 -->
	itm.Weight = 14;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 16;
	itm.dmg_min = 100.0;
	itm.dmg_max = 200.0;
	itm.accuracy = 50;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	itm.points_shop = 500;
	itm.fromHip = true;//для выбора другой анимации
	n++;

	makeref(itm,Items[n]);
	itm.id = "mushket6"; //Башенный мушкетон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket6";
	itm.describe = "itmdescr_mushket6";
	itm.folder = "items";
	itm.model = "portugize";
	itm.picIndex = 12;
	itm.picTexture = "CSP_GUNS2";
	itm.price = 50000;
	// boal 19.01.2004 -->
	itm.Weight = 16;
	// boal 19.01.2004 <--
	itm.chargeQ = 6;
	itm.chargespeed = 16;
	itm.dmg_min = 55.0;
	itm.dmg_max = 170.0;
	itm.accuracy = 30;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	itm.points_shop = 800; //атрибут для ачивок
	itm.fromHip = true;//для выбора другой анимации
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket"; //Фитильный мушкет
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket";
	itm.describe = "itmdescr_mushket";
	itm.folder = "items";
	itm.model = "mushket";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_10";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 13;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 25;
	itm.dmg_min = 100.0;
	itm.dmg_max = 150.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "good";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "mushket2"; //Охотничий штуцер
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_Mushket2";
	itm.describe = "itmdescr_Mushket2";
	itm.folder = "items";
	itm.model = "DBMusket";
	itm.picIndex = 10;
	itm.picTexture = "CSP_GUNS2";
	// boal 19.01.2004 -->
	itm.price = 20000;
	itm.Weight = 16;
	// boal 19.01.2004 <--
	itm.chargeQ = 2;
	itm.chargespeed = 20;
	itm.dmg_min = 140.0;
	itm.dmg_max = 240.0;
	itm.accuracy = 90;
	itm.minlevel = 10;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "mushket_spanish"; //Испанский мушкетон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket_spanish";
	itm.describe = "itmdescr_mushket_spanish";
	itm.folder = "items";
	itm.model = "mushket_spanish";
	itm.picIndex = 2;
	itm.picTexture = "CSP_GUNS1";
	// boal 19.01.2004 -->
	itm.price = 11000;
	itm.Weight = 12;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 30;
	itm.dmg_min = 60.0;
	itm.dmg_max = 180.0;
	itm.accuracy = 100;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	itm.fromHip = true;//для выбора другой анимации
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket_english"; //Английский Мушкетон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket_english";
	itm.describe = "itmdescr_mushket_english";
	itm.folder = "items";
	itm.model = "mushket_english";
	itm.picIndex = 3;
	itm.picTexture = "CSP_GUNS1";
	// boal 19.01.2004 -->
	itm.price = 9500;
	itm.Weight = 10;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 16;
	itm.dmg_min = 40.0;
	itm.dmg_max = 170.0;
	itm.accuracy = 75;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	itm.fromHip = true;//для выбора другой анимации
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket_france"; //Французский мушкетон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket_france";
	itm.describe = "itmdescr_mushket_france";
	itm.folder = "items";
	itm.model = "mushket_france";
	itm.picIndex = 4;
	itm.picTexture = "CSP_GUNS1";
	// boal 19.01.2004 -->
	itm.price = 15000;
	itm.Weight = 14;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 40;
	itm.dmg_min = 150.0;
	itm.dmg_max = 290.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	itm.fromHip = true;//для выбора другой анимации
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket_holland"; //Голландский мушкетон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket_holland";
	itm.describe = "itmdescr_mushket_holland";
	itm.folder = "items";
	itm.model = "mushket_holland";
	itm.picIndex = 5;
	itm.picTexture = "CSP_GUNS1";
	// boal 19.01.2004 -->
	itm.price = 10000;
	itm.Weight = 11;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 30;
	itm.dmg_min = 140.0;
	itm.dmg_max = 240.0;
	itm.accuracy = 70;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	itm.fromHip = true;//для выбора другой анимации
	n++;

	makeref(itm,Items[n]);
	itm.id = "mushket_drob"; //Аркебуза
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket_drob";
	itm.describe = "itmdescr_mushket_drob";
	itm.folder = "items";
	itm.model = "Arguebuse";
	itm.picIndex = 14;
	itm.picTexture = "CSP_GUNS2";
	// boal 19.01.2004 -->
	itm.price = 5000;
	itm.Weight = 11;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 24;
	itm.dmg_min = 60.0;
	itm.dmg_max = 110.0;
	itm.accuracy = 70;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.quality = "good";
	itm.ItemType = "WEAPON";
	itm.fromHip = true;//для выбора другой анимации
	n++;

	makeref(itm,Items[n]);
	itm.id = "mushket_SeaCarbine"; //Флотский карабин
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_SeaCarbine";
	itm.describe = "itmdescr_SeaCarbine";
	itm.folder = "items";
	itm.model = "SeaCarbine";
	itm.picIndex = 13;
	itm.picTexture = "CSP_GUNS2";
	// boal 19.01.2004 -->
	itm.price = 11000;
	itm.Weight = 11;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 20;
	itm.dmg_min = 135.0;
	itm.dmg_max = 235.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "Gunman";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket_Shtuzer"; //Винтовальный штуцер
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_Shtuzer";
	itm.describe = "itmdescr_Shtuzer";
	itm.folder = "items";
	itm.model = "Shtuzer";
	itm.picIndex = 9;
	itm.picTexture = "CSP_GUNS2";
	// boal 19.01.2004 -->
	itm.price = 25000;
	itm.Weight = 10;
	// boal 19.01.2004 <--
	itm.chargeQ = 1;
	itm.chargespeed = 40;
	itm.dmg_min = 200.0;
	itm.dmg_max = 300.0;
	itm.accuracy = 100;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	////////////////////////////////////////////////////////////////////////////////////////////
	// Заскриптованные предметы ТОЛЬКО ЗДЕСЬ -->
	////////////////////////////////////////////////////////////////////////////////////////////
	iScriptItemStartNum = n; // Начальный номер заскриптованных предметов

	iScriptItemEndNum = n; // Конечный номер заскриптованных предметов
	iScriptItemCount = iScriptItemStartNum-iScriptItemEndNum; // Всего заскриптованных предметов
	////////////////////////////////////////////////////////////////////////////////////////////
	// <-- Заскриптованные предметы ТОЛЬКО ЗДЕСЬ
	////////////////////////////////////////////////////////////////////////////////////////////

	// <<<< ---------------  QUEST ITEMS  --------------------

	makeref(itm,Items[n]);
	itm.id = "gold";
	itm.name = "itmname_gold";
	itm.describe = "itmdescr_gold";
	itm.model = "";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	n++;

	// Сундук
	makeref(itm,Items[n]);
	itm.id = "Chest";
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.name = "itmname_chest";
	itm.describe = "itmdescr_chest";
	itm.model = "stat1";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_4";
	itm.price = 15000;
	itm.Weight = 15;
	n++;

	// Малый сундук
	makeref(itm,Items[n]);
	itm.id = "Chest_treasure";
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.name = "itmname_chest_treasure";
	itm.describe = "itmdescr_chest_treasure";
	itm.model = "stat1";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_14";
	itm.price = 1500;
	itm.Weight = 5 + fRandSmall(3.0);
	// itm.points_shop = 50; // Атрибут для магазина ачивок
	n++;

	// Сундук ремесленника
	makeref(itm,Items[n]);
	itm.id = "chest_Craftsmans";
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.name = "itmname_chest_Craftsmans";
	itm.describe = "itmdescr_chest_Craftsmans";
	itm.model = "stat1";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_19";
	itm.price = 1500;
	itm.Weight = 7 + fRandSmall(4.5);
	// itm.points_shop = 100; // Атрибут для магазина ачивок
	n++;

	// Cундук со снаряжением
	makeref(itm,Items[n]);
	itm.id = "Chest_ammo";
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.name = "itmname_chest_ammo";
	itm.describe = "itmdescr_chest_ammo";
	itm.model = "stat1";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_14";
	itm.price = 1500;
	itm.Weight = 9 + fRandSmall(6.0);
	// itm.points_shop = 250; // Атрибут для магазина ачивок
	n++;

	// Странный сундук
	makeref(itm,Items[n]);
	itm.id = "Chest_quest";
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.name = "itmname_chest_quest";
	itm.describe = "itmdescr_chest_quest";
	itm.model = "stat1";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_14";
	itm.price = 1500;
	itm.Weight = 6 + fRandSmall(3.5);
	// itm.points_shop = 500; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "Coins";
	itm.name = "itmname_coins";
	itm.describe = "itmdescr_coins";
	itm.model = "purse";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_4";
	itm.price = 1000;
	itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "icollection";
	itm.name = "itmname_incas_collection";
	itm.describe = "itmdescr_incas_collection";
	itm.model = "";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_4";
	itm.price = 47000;
	itm.Weight = 50;

	itm.PerkReq = 1;
    itm.CraftedItem = "icollection";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 6;
    itm.Component1 = "jewelry1";
    itm.Component1Num = 10;
    itm.Component2 = "jewelry2";
    itm.Component2Num = 10;
    itm.Component3 = "jewelry3";
    itm.Component3Num = 10;
    itm.Component4 = "jewelry4";
    itm.Component4Num = 10;
    itm.Component5 = "jewelry14";
    itm.Component5Num = 10;
    itm.Component6 = "jewelry15";
    itm.Component6Num = 10;
	n++;

	// boal для генератора -->
	makeref(itm,Items[n]);
	itm.id = "letter_A";
	itm.name = "itmname_letter_A";
	itm.describe = "itmdescr_letter_A";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "letter_1";
	itm.name = "itmname_letter_1";
	itm.describe = "itmdescr_letter_1";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "letter_2";
	itm.name = "itmname_letter_2";
	itm.describe = "itmdescr_letter_2";
	itm.model = "";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "letter_open";
	itm.name = "itmname_letter_open";
	itm.describe = "itmdescr_letter_open";
	itm.model = "";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

    // boal для генератора <--

	makeref(itm,Items[n]); //записка
	itm.id = "letter_notes";
	itm.name = "itmname_letter_notes";
	itm.describe = "itmdescr_letter_notes";
	itm.model = "";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); //чемодан с барахлом
	itm.id = "leather_bag";
	itm.name = "itmname_leather_bag";
	itm.describe = "itmdescr_leather_bag";
	itm.model = "";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_14";
	itm.price = 0;
	itm.Weight = 8.0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); //вексель
	itm.id = "Order";
	itm.name = "itmname_order";
	itm.describe = "itmdescr_order";
	itm.model = "";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_8";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "letter_Albermal";
	itm.name = "itmname_letter_Albermal";
	itm.describe = "itmdescr_letter_Albermal";
	itm.model = "";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_12";
	itm.price = 0;
	itm.Weight = 0.1;
	n++;

    // eddy торговые грамоты <--
	makeref(itm,Items[n]);
	itm.id = "EngTradeLicence";
	itm.name = "itmname_EngTradeLicence";
	itm.describe = "itmdescr_EngTradeLicence";
	itm.model = "";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "FraTradeLicence";
	itm.name = "itmname_FraTradeLicence";
	itm.describe = "itmdescr_FraTradeLicence";
	itm.model = "";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "SpaTradeLicence";
	itm.name = "itmname_SpaTradeLicence";
	itm.describe = "itmdescr_SpaTradeLicence";
	itm.model = "";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "HolTradeLicence";
	itm.name = "itmname_HolTradeLicence";
	itm.describe = "itmdescr_HolTradeLicence";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); //общая верительная грамота для губеров.
	itm.id = "Trust";
	itm.name = "itmname_Trust";
	itm.describe = "itmdescr_Trust";
	itm.model = "";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_9";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;
	// eddy торговые грамоты <--

	makeref(itm,Items[n]); //секретная депеша по квесту мэра
	itm.id = "sicretLetter";
	itm.name = "itmname_sicretLetter";
	itm.describe = "itmdescr_sicretLetter";
	itm.model = "";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_12";
//	itm.shown = 0;
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "mapQuest";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_mapQuest";
	itm.describe = "itmdescr_mapQuest";
	itm.model = "";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_7";
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	// boal 19.01.2004 <--
	itm.imageTga = "none";
	itm.imageType = "MapRead"; // текстовая форма
	itm.ItemType = "QUESTITEMS";
	itm.mapSpecial = "";
	n++;

	makeref(itm,Items[n]);
	itm.id = "LegransMap";
	itm.name = "itmname_LegransMap";
	itm.describe = "itmdescr_LegransMap";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_10";
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "Bible";
	itm.name = "itmname_bible";
	itm.describe = "itmdescr_bible";
	itm.model = "";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_9";
//	itm.shown = 0;
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 2;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "ShipsJournal";
	itm.name = "itmname_ShipsJournal";
	itm.describe = "itmdescr_ShipsJournal";
	itm.model = "";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_4";
//	itm.shown = 0;
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 2;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;


    makeref(itm,Items[n]);
	itm.id = "MapsAtlas";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_MapsAtlas";
	itm.describe = "itmdescr_MapsAtlas";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_14";
//	itm.shown = 0;
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	itm.mapSpecial = "";
	n++;


	// ==> Предметы по квесту Аскольда
    makeref(itm,Items[n]);
	itm.id = "Powder_mummie";
	itm.name = "itmname_Powder_mummie";
	itm.describe = "itmdescr_Powder_mummie";
	itm.model = "pursel";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_12";
	//itm.shown = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.5;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]); // Крест Антониу де Соуза
	itm.id = "DeSouzaCross";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_DeSouzaCross";
	itm.describe = "itmdescr_DeSouzaCross";
	itm.model = "sapphire";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_12";
	// boal 19.01.2004 -->
	itm.Weight = 0.01;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]); // Темпоральный деформатор
	itm.id = "DHGlove";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_DHGlove";
	itm.describe = "itmdescr_DHGlove";
	itm.model = "sapphire";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_14";
	// boal 19.01.2004 -->
	itm.Weight = 2.0;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); // Шляпа капитана "Чёрной Вдовы"
	itm.id = "hatWhisper";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_hatWhisper";
	itm.describe = "itmdescr_hatWhisper";
	itm.model = "sapphire";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_19";
	// boal 19.01.2004 -->
	itm.Weight = 0.01;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); // Очки
	itm.id = "glasses";
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_glasses";
	itm.describe = "itmdescr_glasses";
	itm.model = "sapphire";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_19";
	// boal 19.01.2004 -->
	itm.Weight = 0.01;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	itm.HeadAccessory = "glasses";
	n++;

	makeref(itm,Items[n]);
	itm.id = "DOjeronRing";
	itm.name = "itmname_DOjeronRing";
	itm.describe = "itmdescr_DOjeronRing";
	itm.model = "RingJew";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_9";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "BlackLabel";
	itm.name = "itmname_BlackLabel";
	itm.describe = "itmdescr_BlackLabel";
	itm.model = "";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_8";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Term_arm";
	itm.name = "itmname_Term_arm";
	itm.describe = "itmdescr_Term_arm";
	itm.model = "pursel";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_12";
	itm.price = 0;
	itm.Weight = 5.5;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Malyava";
	itm.name = "itmname_Malyava";
	itm.describe = "itmdescr_Malyava";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_12";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "PortmansBook";
	itm.name = "itmname_PortmansBook";
	itm.describe = "itmdescr_PortmansBook";
	itm.model = "";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_1";
	itm.price = 0;
	itm.Weight = 0.2;
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket2x2"; //Двуствольный мушкетон
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_questMushket";
	itm.describe = "itmdescr_questMushket";
	itm.folder = "items";
	itm.model = "mushket2x2";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_13";
	// boal 19.01.2004 -->
	itm.price = 100000;
	itm.Weight = 17;
	// boal 19.01.2004 <--
	itm.chargeQ = 2;
	itm.chargespeed = 12;
	itm.dmg_min = 90.0;
	itm.dmg_max = 290.0;
	itm.accuracy = 80;
	itm.minlevel = 20;
	itm.rare = 0.0001;
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	itm.fromHip = true;//для выбора другой анимации
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_LSC";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_LSC";
	itm.describe = "itmdescr_map_LSC";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_13";
	itm.price = 200000;
	itm.Weight = 0.2;
	itm.imageTga = "LostShipsCity";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	//homo
    makeref(itm,Items[n]);
	itm.id = "Griffins_Weapon"; // оружие Гриффина
	itm.name = "itmname_Griffins_Weapon";
	itm.describe = "itmdescr_Griffins_Weapon";
	itm.model = "";
	itm.picIndex =14;
	itm.picTexture = "ITEMS_13";
	itm.shown = 0;
	itm.Weight = 3.4;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;
	//homo
    makeref(itm,Items[n]);
	itm.id = "Weapon_for_escape"; //оружие для побега Блада
	itm.name = "itmname_Weapon_for_escape";
	itm.describe = "itmdescr_Weapon_for_escape";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_13";
	itm.shown = 0;
	itm.Weight = 10;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	////////////////////////////////////////////////////////////////////////////////////////////
	//здесь начинаются квестовые предметы, заюзаные в локаторах item
	//оформлять эти предметы ТОЛЬКО ЗДЕСЬ, до конца сектора квестовых предметов
	////////////////////////////////////////////////////////////////////////////////////////////

	ItemsForLocators_start = n; //начальный номер для спец. предметов

	makeref(itm,Items[n]);
	itm.id = "Rock_letter";
	itm.name = "itmname_Rock_letter";
	itm.describe = "itmdescr_Rock_letter";
	itm.model = "StoneMap";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_4";
	itm.shown = 0; //сначала скрижали невидимы, т.е. взять их нельзя до прох.квеста Аскольда.
	string PutLocation, PutLocator;   //рендом скрижалей.
    int WherePut = rand(4);
    switch(WherePut)
    {
        case 0:
            PutLocation = "Pearl_Grot";
            PutLocator  = "item"+(rand(2)+1);
        break;
        case 1:
            PutLocation = "Caiman_Grot";
            PutLocator  = "item"+(rand(2)+1);
        break;
        case 2:
            PutLocation = "Terks_Grot";
            PutLocator  = "item"+(rand(2)+1);
        break;
        case 3:
            PutLocation = "Dominica_Grot";
            PutLocator  = "item"+(rand(2)+1);
        break;
        case 4:
            PutLocation = "Temple";
            PutLocator  = "item1";
        break;
    }
	itm.startLocation = PutLocation;
	itm.startLocator = PutLocator;
	itm.useLocation = "Guadeloupe_Cave";
	itm.useLocator = "button01";
	itm.price = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.2;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Azzy_bottle";
	itm.name = "itmname_Azzy_bottle";
	itm.describe = "itmdescr_Azzy_bottle";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_12";
	itm.shown = 1; //до поры локатор не реагирует на заступы
	itm.useLocator = "button01";
	// boal 19.01.2004 -->
	itm.Weight = 2.5;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "ShipyardsMap";
	itm.name = "itmname_ShipyardsMap";
	itm.describe = "itmdescr_ShipyardsMap";
	itm.model = "shipyardsMap";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_12";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "CaptainBook";
	itm.name = "itmname_CaptainBook";
	itm.describe = "itmdescr_CaptainBook";
	itm.model = "shipyardsMap";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_12";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "RingCapBook";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_ringcapbook";
	itm.describe = "itmdescr_ringcapbook";
    itm.model = "OpenBook";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_1";
	itm.price = 0;
	itm.Weight = 1.0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "MayorsRing";
	itm.name = "itmname_MayorsRing";
	itm.describe = "itmdescr_MayorsRing";
	itm.model = "RingSimGold";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_2";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "UsurersJew";
	itm.name = "itmname_UsurersJew";
	itm.describe = "itmdescr_UsurersJew";
	itm.model = "Diamond";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_2";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.JevelType = "бриллиант";
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "OpenBook";
	itm.name = "itmname_OpenBook";
	itm.describe = "itmdescr_OpenBook";
	itm.model = "OpenBook";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_4";
	itm.Weight = 0.2;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	itm.shown = false;
	itm.startLocation = "PuertoPrincipe_townhall";
	itm.startLocator = "item1";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Ladder";
	itm.name = "itmname_Ladder";
	itm.describe = "itmdescr_Ladder";
	itm.model = "Ladder";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_12";
	itm.Weight = 0.2;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "key1";
	itm.name = "itmname_Key1";
	itm.describe = "itmdescr_Key1";
	itm.model = "keysimple";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_12";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "key2";
	itm.name = "itmname_Key2";
	itm.describe = "itmdescr_Key2";
	itm.model = "keymiddle";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_12";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "key3";
	itm.name = "itmname_Key3";
	itm.describe = "itmdescr_Key3";
	itm.model = "keygrand";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_12";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "key_mechanic";
	itm.name = "itmname_Key_Mechanic";
	itm.describe = "itmdescr_Key_Mechanic";
	itm.model = "keygrand";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_15";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);  //ключ от сундука по штурму Панамы
	itm.id = "keyPanama";
	itm.name = "itmname_keyPanama";
	itm.describe = "itmdescr_keyPanama";
	itm.model = "keygrand";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_12";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);  //ключ для линейки ГПК
	itm.id = "keyQuestLSC";
	itm.name = "itmname_keyQuestLSC";
	itm.describe = "itmdescr_keyQuestLSC";
	itm.model = "keymiddle";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_12";
	itm.shown = 0; //сначала ключ невидим
	itm.startLocation = "Villemstad_houseSp5";
	itm.startLocator = "item2";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	// Warship Это ключ для сундуков Моргана на Ямайке, почему-то не было, хотя в инитах локации на сундуках указывается он
	makeref(itm, Items[n]);
	itm.id = "keyMorgan";
	itm.name = "itmname_keyMorgan";
	itm.describe = "itmdescr_keyMorgan";
	itm.model = "keygrand";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_12";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);	//письмо для линейки ГПК
	itm.id = "letter_LSC";
	itm.name = "itmname_letter_LSC";
	itm.describe = "itmdescr_letter_LSC";
	itm.model = "letter";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_4";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

    //homo лекарство по линейке Блада
    makeref(itm,Items[n]);
	itm.id = "migraine_potion"; // лекарство от Мигрени
	itm.name = "itmname_migraine_potion";
	itm.describe = "itmdescr_migraine_potion";
	itm.model = "balsam";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_1";
	itm.shown = 0;
	itm.Weight = 0.4;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	//homo
    makeref(itm,Items[n]);
	itm.id = "MsStid_ring"; // Колечко
	itm.name = "itmname_MsStid_ring";
	itm.describe = "itmdescr_MsStid_ring";
	itm.model = "RingJew";//pursel
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_7";
	itm.shown = 0;
	itm.Weight = 0.4;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);	//шестеренка
	itm.id = "Pinion";
	itm.name = "itmname_pinion";
	itm.describe = "itmdescr_pinion";
	itm.model = "Pinion";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_12";
	itm.shown = 1;
	itm.startLocation = "UnderWater";
	itm.startLocator = "item" + (rand(4)+1);
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

    makeref(itm,Items[n]);
	itm.id = "pistol7";  //Револьвер Колье
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol7";
	itm.describe = "itmdescr_pistol7";
	itm.folder = "items";
	itm.model = "pistol7";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_8";
	itm.shown = 1;
	itm.price = 25000;
	//ложим в храм
	itm.startLocation = "Temple_round";
	itm.startLocator = "item1";
	// boal 19.01.2004 -->
	itm.Weight = 9;
	// boal 19.01.2004 <--
	itm.chargeQ = 5;
	itm.chargespeed = 52;
	itm.dmg_min = 100.0;
	itm.dmg_max = 300.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

	makeref(itm,Items[n]);
	itm.id = "pistol7shotgun";  //Шотган
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_pistol7shotgun";
	itm.describe = "itmdescr_pistol7shotgun";
	itm.folder = "items";
	itm.model = "pistol7shotgun";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_14";
	itm.shown = 1;
	itm.price = 25000;
	itm.Weight = 9;
	itm.chargeQ = 4;
	itm.chargespeed = 52;
	itm.dmg_min = 100.0;
	itm.dmg_max = 300.0;
	itm.accuracy = 80;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	n++;

    makeref(itm,Items[n]);
	itm.id = "mushket_seadevil";  // Морской Дьявол
	itm.groupID = GUN_ITEM_TYPE;
	itm.name = "itmname_mushket_seadevil";
	itm.describe = "itmdescr_mushket_seadevil";
	itm.folder = "items";
	itm.model = "seadevil";
	itm.picIndex = 3;
	itm.picTexture = "CSP_GUNS2";
	itm.shown = 1;
	itm.price = 125000;
	itm.Weight = 18;
	itm.chargeQ = 3;
	itm.chargespeed = 65;
	itm.dmg_min = 200.0;
	itm.dmg_max = 400.0;
	itm.accuracy = 100;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ReqPerk = "GunProfessional";
	itm.quality = "excellent";
	itm.ItemType = "WEAPON";
	//itm.fromHip = true;//для выбора другой анимации
	n++;

    makeref(itm,Items[n]);
	itm.id = "Ascold_rabble"; // монтировка
	itm.name = "itmname_Ascold_rabble";
	itm.describe = "itmdescr_Ascold_rabble";
	itm.model = "kocherg";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_12";
	itm.shown = 0;
	itm.useLocation = "Guadeloupe_Cave";
	itm.useLocator = "button02";
	// boal 19.01.2004 -->
	itm.Weight = 1;
	itm.price = 0;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	//для проверки тотемов начальный номер
	Totems_start = n;

	makeref(itm,Items[n]);
	itm.id = "Totem_1";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_1";
	itm.describe = "itmdescr_Totem_1";
	itm.model = "Totem_1";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Shore_ship1";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_1";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_2";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_2";
	itm.describe = "itmdescr_Totem_2";
	itm.model = "Totem_2";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Shore55";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_2";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_3";
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Totem_3";
	itm.describe = "itmdescr_Totem_3";
	itm.model = "Totem_3";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Marigo_Cave";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_3";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_4";
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Totem_4";
	itm.describe = "itmdescr_Totem_4";
	itm.model = "Totem_4";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "PortSpein_town";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_4";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_5";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_5";
	itm.describe = "itmdescr_Totem_5";
	itm.model = "Totem_5";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "FortFrance_Dungeon";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_5";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_6";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_6";
	itm.describe = "itmdescr_Totem_6";
	itm.model = "Totem_6";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Tortuga_town";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_6";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_7";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_7";
	itm.describe = "itmdescr_Totem_7";
	itm.model = "Totem_7";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Villemstad_townhall";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_7";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_8";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_8";
	itm.describe = "itmdescr_Totem_8";
	itm.model = "Totem_8";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Mayak8";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_8";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_9";
	itm.groupID = IDOLS_LEFT_ITEM_TYPE;
	itm.name = "itmname_Totem_9";
	itm.describe = "itmdescr_Totem_9";
	itm.model = "Totem_9";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Santiago_Incquisitio";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_9";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_10";
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Totem_10";
	itm.describe = "itmdescr_Totem_10";
	itm.model = "Totem_10";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Temple";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_10";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_11";	//единый тотем на снятие огня
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Totem_11";
	itm.describe = "itmdescr_Totem_11";
	itm.model = "Totem_11";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Tenochtitlan";
	itm.startLocator = "item1";
	itm.useLocation = "Tenochtitlan";
	itm.useLocator = "button04";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_12";	//открывалка на каменный сундук с кинжалом
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Totem_12";
	itm.describe = "itmdescr_Totem_12";
	itm.model = "Totem_12";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = 0;
	itm.useLocation = "Temple_great";
	itm.useLocator = "button01";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_13";    //один из двух тотемов на снятие огня
	itm.name = "itmname_Totem_13";
	itm.describe = "itmdescr_Totem_13";
	itm.model = "Totem_13";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Tenotchitlan_Jungle_06";
	itm.startLocator = "item1";
	itm.useLocation = "Tenochtitlan";
	itm.useLocator = "button02";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_14";	//один из двух тотемов на снятие огня
	itm.name = "itmname_Totem_14";
	itm.describe = "itmdescr_Totem_14";
	itm.model = "Totem_14";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Panama_jungle_02";
	itm.startLocator = "item1";
	itm.useLocation = "Tenochtitlan";
	itm.useLocator = "button03";
	itm.price = (rand(8)+1)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Totem_15";	// Тотем Шипе-Тотеку
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
	itm.name = "itmname_Totem_15";
	itm.describe = "itmdescr_Totem_15";
	itm.model = "Totem_15";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = true;
	itm.startLocation = "Temple_Inside";
	itm.startLocator = "item1";
	itm.useLocation = "Temple_great";
	itm.useLocator = "button02";
	itm.price = (rand(8)+1)*1000;
	itm.Weight = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 1000; // Атрибут для магазина ачивок
	n++;

	Totems_end = n;
	//для проверки тотемов конечный номер

	makeref(itm,Items[n]);
	itm.id = "SkullAztec";
	itm.name = "itmname_SkullAztec";
	itm.describe = "itmdescr_SkullAztec";
	itm.model = "SkullAztec";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_AZTEC";
	itm.shown = 1;
	itm.startLocation = "Temple_great";
	itm.startLocator = "item1";
	itm.price = 100000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);
	itm.id = "KnifeAztec";
	itm.name = "itmname_KnifeAztec";
	itm.describe = "itmdescr_KnifeAztec";
	itm.model = "KnifeAztec";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_13";
	itm.shown = 0;
	itm.useLocation = "Tenochtitlan";
	itm.useLocator = "button01";
	itm.price = 25000;
	// boal 19.01.2004 -->
	itm.Weight = 0.3;
	// boal 19.01.2004 <--
	itm.ItemType = "QUESTITEMS";
	n++;

	ItemsForLocators_end = n; //конечный номер для спец. предметов

	// <<<< ---------------  QUEST ITEMS  --------------------

    // КАРТЫ //////////////////////////////////////////////////
    makeref(itm,Items[n]);
	itm.id = "map_bad";       // to del
    itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_bad";
	itm.describe = "itmdescr_map_bad";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_10";
//	itm.shown = 0;
	itm.price = (rand(4)+6)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	itm.imageTga = "map_1";
	itm.imageType = "cabin_map";
	// boal 19.01.2004 <--
    itm.rare = 0.005;
    itm.ItemType = "MAP";
	n++;

    makeref(itm,Items[n]);
	itm.id = "map_normal";
    itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_normal";
	itm.describe = "itmdescr_map_normal";
	itm.model = "";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_9";
//	itm.shown = 0;
	itm.price = (rand(8)+9)*1020;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	itm.imageTga = "map_good";
	itm.imageType = "cabin_map";
	// boal 19.01.2004 <--
	itm.rare = 0.001;
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "Map_Best"; // Warship. Отличная карта
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_Map_Best";
	itm.describe = "itmdescr_Map_Best";
	itm.model = "";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_9";
//	itm.shown = 0;
	itm.price = (rand(8)+37)*1000;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	itm.imageTga = "map_good";
	itm.imageType = "cabin_map";
	// boal 19.01.2004 <--
	itm.rare = 0.001;
	itm.ItemType = "MAP";
	n++;

	// boal 270904 -->
	makeref(itm,Items[n]);
	itm.id = "map_bermudas";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_bermudas";
	itm.describe = "itmdescr_map_bermudas";
	itm.model = "";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1050;
	itm.Weight = 0.2;
	itm.imageTga = "bermudas";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_jam";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_jam";
	itm.describe = "itmdescr_map_jam";
	itm.model = "";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1100;
	itm.Weight = 0.2;
	itm.imageTga = "Jamaica";
	itm.imageType = "";
	itm.MapIsland = "Redmond";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_cayman";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_cayman";
	itm.describe = "itmdescr_map_cayman";
	itm.model = "";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+8)*1015;
	itm.Weight = 0.2;
	itm.imageTga = "kayman";
	itm.imageType = "";
	itm.MapIsland = "Cayman";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_barbados";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_barbados";
	itm.describe = "itmdescr_map_barbados";
	itm.model = "";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1200;
	itm.Weight = 0.2;
	itm.imageTga = "barbados";
	itm.imageType = "";
	itm.MapIsland = "Oxbay";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_TORTUGA";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_TORTUGA";
	itm.describe = "itmdescr_map_TORTUGA";
	itm.model = "";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+6)*1070;
	itm.Weight = 0.2;
	itm.imageTga = "TORTUGA";
	itm.imageType = "";
	itm.MapIsland = "Oxbay";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);    ////
	itm.id = "map_Curacao";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_Curacao";
	itm.describe = "itmdescr_map_Curacao";
	itm.model = "";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1300;
	itm.Weight = 0.2;
	itm.imageTga = "curacao";
	itm.imageType = "";
	itm.MapIsland = "Douwesen";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_martiniqua";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_martiniqua";
	itm.describe = "itmdescr_map_martiniqua";
	itm.model = "";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1250;
	itm.Weight = 0.2;
	itm.imageTga = "martinica";
	itm.imageType = "";
	itm.MapIsland = "FalaiseDeFleur";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_dominica";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_dominica";
	itm.describe = "itmdescr_map_dominica";
	itm.model = "";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+7)*1030;
	itm.Weight = 0.2;
	itm.imageTga = "dominica";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_trinidad";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_trinidad";
	itm.describe = "itmdescr_map_trinidad";
	itm.model = "";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+6)*1080;
	itm.Weight = 0.2;
	itm.imageTga = "trinidad";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_puerto";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_puerto";
	itm.describe = "itmdescr_map_puerto";
	itm.model = "";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+6)*1500;
	itm.Weight = 0.2;
	itm.imageTga = "p_rico";
	itm.imageType = "";
	itm.MapIsland = "IslaMuelle";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_cuba";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_cuba";
	itm.describe = "itmdescr_map_cuba";
	itm.model = "";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+12)*1090;
	itm.Weight = 0.2;
	itm.imageTga = "cuba";
	itm.imageType = "";
	itm.MapIsland = "Cuba";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_Pearl";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_Pearl";
	itm.describe = "itmdescr_map_Pearl";
	itm.model = "";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+12)*1150;
	itm.Weight = 0.2;
	itm.imageTga = "Pearl";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_hisp";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_hisp";
	itm.describe = "itmdescr_map_hisp";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+12)*1220;
	itm.Weight = 0.2;
	itm.imageTga = "hispaniola";
	itm.imageType = "";
	itm.MapIsland = "Gaity";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_nevis";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_nevis";
	itm.describe = "itmdescr_map_nevis";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+6)*1010;
	itm.Weight = 0.2;
	itm.imageTga = "nevis";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_beliz";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_beliz";
	itm.describe = "itmdescr_map_beliz";
	itm.model = "";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+9)*1300;
	itm.Weight = 0.2;
	itm.imageTga = "beliz";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);    /////
	itm.id = "map_guad";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_guad";
	itm.describe = "itmdescr_map_guad";
	itm.model = "";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1015;
	itm.Weight = 0.2;
	itm.imageTga = "guadelupa";
	itm.imageType = "";
	itm.MapIsland = "Guadelupa";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);    /////
	itm.id = "map_santa";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_santa";
	itm.describe = "itmdescr_map_santa";
	itm.model = "";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+8)*1280;
	itm.Weight = 0.2;
	itm.imageTga = "santa";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_antigua";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_antigua";
	itm.describe = "itmdescr_map_antigua";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+6)*1400;
	itm.Weight = 0.2;
	itm.imageTga = "antigua";
	itm.imageType = "";
	itm.MapIsland = "Antigua";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_terks";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_terks";
	itm.describe = "itmdescr_map_terks";
	itm.model = "";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+9)*1350;
	itm.Weight = 0.2;
	itm.imageTga = "terks";
	itm.imageType = "";
	itm.MapIsland = "Terks";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_sm";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_sm";
	itm.describe = "itmdescr_map_sm";
	itm.model = "";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+6)*1500;
	itm.Weight = 0.2;
	itm.imageTga = "s_martin";
	itm.imageType = "";
	itm.MapIsland = "Sent";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_maine_1";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_maine_1";
	itm.describe = "itmdescr_map_maine_1";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+17)*1100;
	itm.Weight = 0.2;
	itm.imageTga = "maine_1";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_maine_2";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_maine_2";
	itm.describe = "itmdescr_map_maine_2";
	itm.model = "";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+18)*1150;
	itm.Weight = 0.2;
	itm.imageTga = "maine_2";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_panama";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_panama";
	itm.describe = "itmdescr_map_panama";
	itm.model = "";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_13";
	itm.price = (rand(8)+7)*1200;
	itm.Weight = 0.2;
	itm.imageTga = "panama";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_maracaibo";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_maracaibo";
	itm.describe = "itmdescr_map_maracaibo";
	itm.model = "";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+9)*1250;
	itm.Weight = 0.2;
	itm.imageTga = "maracaibo";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;

	makeref(itm,Items[n]);
	itm.id = "map_cumana";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_cumana";
	itm.describe = "itmdescr_map_cumana";
	itm.model = "";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_11";
	itm.price = (rand(8)+7)*1400;
	itm.Weight = 0.2;
	itm.imageTga = "cumana";
	itm.imageType = "";
	itm.MapIsland = "";
	itm.ItemType = "MAP";
	n++;
	// boal 270904 <--

    // boal карты генератора клада -->
    makeref(itm,Items[n]);
	itm.id = "map_full";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_full";
	itm.describe = "itmdescr_map_full";
	itm.model = "";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_7";
	itm.price = 0; // 0 test
	itm.Weight = 0.4;
	itm.imageTga = "none";
	itm.imageType = "MapRead"; // текстовая форма
	itm.mapType = "Full";
	itm.ItemType = "MAP";
	itm.mapSpecial = "";
	n++;

    makeref(itm,Items[n]);
	itm.id = "map_part1";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_part1";
	itm.describe = "itmdescr_map_part1";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_7";
	itm.price = 0;
	itm.Weight = 0.2;
	itm.imageTga = "none";
	itm.imageType = "MapRead"; // текстовая форма
	itm.mapType = "Part";
	itm.ItemType = "MAP";
	itm.mapSpecial = "";
	n++;

    makeref(itm,Items[n]);
	itm.id = "map_part2";
	itm.groupID = MAPS_ITEM_TYPE;
	itm.name = "itmname_map_part2";
	itm.describe = "itmdescr_map_part2";
	itm.model = "";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_7";
	itm.price = 0;
	itm.Weight = 0.2;
	itm.imageTga = "none";
	itm.imageType = "MapRead"; // текстовая форма
	itm.mapType = "Part";
	itm.ItemType = "MAP";
	itm.mapSpecial = "";
	n++;
    // boal карты генератора клада <--


    //  ЗАПОЛНЕНИЕ ТРУПОВ
    ItemDeadStartCount = n;
    trace("Заполнение трупов с предмета "+ItemDeadStartCount);


    makeref(itm,Items[n]);
	itm.id = STATUE1; //+1
	itm.groupID = JEWELRY_INDIAN_RIGHT_ITEM_TYPE;
	itm.name = "itmname_statue1";
	itm.describe = "itmdescr_statue1";
	itm.model = "stat1";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_1";
	//itm.shown = false;
	itm.price = 20;
	itm.Weight = 35;

    itm.Monster.rare = 0.05;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

//SPYGLASSES

	makeref(itm,Items[n]);
	itm.id = "spyglass1";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass1";
	itm.describe = "itmdescr_spyglass1";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 250;
	itm.Weight = 1;
	itm.radius = 1000.0;
    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Warrior.rare = 0.15;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.scope.texture = "eye_BadTub.tga";
	itm.scope.zoom = 2.5;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 0;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 0;
	itm.scope.show.sail = 0;
	itm.scope.show.crew = 0;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 0;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 0;
	itm.scope.show.mushketshot = 0;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "spyglass2";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass2";
	itm.describe = "itmdescr_spyglass2";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_6";
	// boal 19.01.2004 -->
	itm.price = 1500;
	itm.Weight = 1.5;
	itm.radius = 2000.0;
    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.scope.texture = "eye_CommonTub.tga";
	itm.scope.zoom = 4.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 0;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 0;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 0;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 0;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 0;
	itm.scope.show.mushketshot = 0;
	itm.minlevel = 1;
	itm.rare = 0.07;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "spyglass3";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass3";
	itm.describe = "itmdescr_spyglass3";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_6";
	itm.price = 4500;
	// boal 19.01.2004 -->
	itm.Weight = 2;
	itm.radius = 3000.0;
    itm.Solder_o.rare = 0.15;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    // boal 19.01.2004 <--
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.scope.texture = "eye_GoodTub.tga";
	itm.scope.zoom = 7.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 0;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 0;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 0;
	itm.scope.show.mushketshot = 1;
	itm.minlevel = 1;
	itm.rare = 0.05;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "spyglass4";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass4";
	itm.describe = "itmdescr_spyglass4";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_1";
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.price = 12000;
	// boal 19.01.2004 -->
	itm.Weight = 4;
	itm.radius = 4000.0;
    itm.Solder_o.rare = 0.05;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    // boal 19.01.2004 <--
	itm.scope.texture = "eye_BestTub.tga";
	itm.scope.zoom = 10.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 1;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 1;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 1;
	itm.scope.show.mushketshot = 1;
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "spyglass5";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass5";
	itm.describe = "itmdescr_spyglass5";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_1";
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.price = 75000;
	// boal 19.01.2004 -->
	itm.Weight = 7;
	itm.radius = 5000.0;
    itm.Solder_o.rare = 0.0001;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    // boal 19.01.2004 <--
	itm.scope.texture = "eye_BestTub.tga";
	itm.scope.zoom = 15.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 1;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 1;
	itm.scope.show.cannontype = 1;
	itm.scope.show.captain_skills = 1;
	itm.scope.show.mushketshot = 1;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ItemType = "SUPPORT";
	n++;

//POTIONS

	makeref(itm,Items[n]);
	itm.id = "potion1"; // Лечебное зелье
	itm.name = "itmname_potion1";
	itm.describe = "itmdescr_potion1";
	itm.model = "potion";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_1";
	itm.price = 100;
	itm.Weight = 0.8;
    itm.Solder_o.rare = 0.3;
    itm.Solder_o.min = 2;
    itm.Solder_o.max = 6;
    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 3;
    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 4;
    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 7;
	itm.potion.pic = 21;
	itm.potion.tex = 0;
	itm.potion.health = 40.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "potion2"; // Эликсир
	itm.name = "itmname_potion2";
	itm.describe = "itmdescr_potion2";
	itm.model = "potionbig";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_1";
	itm.price = 500;
	itm.Weight = 1;
    itm.Solder_o.rare = 0.3;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 3;
    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 3;
    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 5;
	itm.potion.pic = 22;
	itm.potion.tex = 0;
	itm.potion.health = 150.0;
	itm.potion.health.speed = 8;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";

    itm.CraftedItem = "potion2";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 2;
    itm.Component1 = "potion1";
    itm.Component1Num = 4;
    itm.Component2 = "indian16";
    itm.Component2Num = 0;
	n++;

	makeref(itm,Items[n]);
	itm.id = "potion3"; // Противоядие
	itm.name = "itmname_potion3";
	itm.describe = "itmdescr_potion3";
	itm.model = "Antidote";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_1";
	itm.price = 200;
	itm.Weight = 0.4;
    itm.Solder_o.rare = 0.05;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
	itm.potion.pic = 23;
	itm.potion.tex = 0;
	itm.potion.antidote = true;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "potion4"; // Микстура
	itm.name = "itmname_potion4";
	itm.describe = "itmdescr_potion4";
	itm.model = "balsam";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_1";
	itm.price = 900;
	itm.Weight = 0.4;
    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Solder_o.rare = 0.05;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 3;
    itm.Monster.rare = 0.05;
    itm.Monster.min = 1;
    itm.Monster.max = 3;
    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
	itm.potion.pic = 24;
	itm.potion.tex = 0;
	itm.potion.health = 130.0;
	itm.potion.health.speed = 8;
	itm.potion.antidote = true;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "potion4";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 3;
    itm.Component1 = "potion3";
    itm.Component1Num = 1;
    itm.Component2 = "potionrum";
    itm.Component2Num = 2;
    itm.Component3 = "indian16";
    itm.Component3Num = 0;
	n++;

//-----------ADDED BY VERRUCKT BROTHEL MOD------------------
	makeref(itm,Items[n]);
	itm.id = "potionrum"; // Бутылка рома
	itm.name = "itmname_potionrum";
	itm.describe = "itmdescr_potionrum";
    itm.model = "balsam";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_1";
	itm.price = 150;
	itm.Weight = 2;
    itm.Solder_o.rare = 0.1;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.Solder.rare = 0.2;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Warrior.rare = 0.2;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
	itm.potion.pic = 25;
	itm.potion.tex = 0;
	itm.potion.health = 50.0;
	itm.potion.antidote = true;
	itm.potion.drunk = 51;
	itm.potion.drunk.time = 5600;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "potionwine"; // Отличное вино
	itm.name = "itmname_potionwine";
	itm.describe = "itmdescr_potionwine";
    itm.model = "balsam";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_1";
	itm.price = 500;
	itm.Weight = 1;
    itm.Solder_o.rare = 0.3;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
	itm.potion.pic = 26;
	itm.potion.tex = 0;
	itm.potion.health = 175.0;
	itm.potion.health.speed = 7;
	itm.potion.drunk = 15;
	itm.potion.drunk.time = 8000;
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";

    itm.CraftedItem = "potionwine";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 3;
    itm.Component1 = "potion5";
    itm.Component1Num = 7;
    itm.Component2 = "indian4";
    itm.Component2Num = 1;
    itm.Component3 = "indian16";
    itm.Component3Num = 0;
	n++;

    makeref(itm,Items[n]);
	itm.id = "potion5"; // Виноград
	itm.name = "itmname_potion5";
	itm.describe = "itmdescr_potion5";
    itm.model = "balsam";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_7";
	itm.price = 30;
	itm.Weight = 0.4;
    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 9;
    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 9;
	itm.potion.pic = 27;
	itm.potion.tex = 0;
	itm.potion.health = 25.0;
	itm.minlevel = 1;
	itm.rare = 0.2;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	// Трубка здоровья
	makeref(itm,Items[n]);
	itm.id = "HealthTube";
	itm.name = "itmname_HealthTube";
	itm.describe = "itmdescr_HealthTube";
	itm.model = "1";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_18";
	itm.price = 300;
	itm.Weight = 0.01;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "HealthTube";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 3;
    itm.Component1 = "CompCraft_HealthTobacco";
    itm.Component1Num = 1;
    itm.Component2 = "Mineral7";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Scissors";
    itm.Component3Num = 0;
	n++;

	// Трубка энергии
	makeref(itm,Items[n]);
	itm.id = "EnergyTube";
	itm.name = "itmname_EnergyTube";
	itm.describe = "itmdescr_EnergyTube";
	itm.model = "1";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_18";
	itm.price = 300;
	itm.Weight = 0.01;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "EnergyTube";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 3;
    itm.Component1 = "CompCraft_EnergyTobacco";
    itm.Component1Num = 1;
    itm.Component2 = "Mineral7";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Scissors";
    itm.Component3Num = 0;
	n++;

	// Трубка силы
	makeref(itm,Items[n]);
	itm.id = "StrengthTube";
	itm.name = "itmname_StrengthTube";
	itm.describe = "itmdescr_StrengthTube";
	itm.model = "1";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_18";
	itm.price = 300;
	itm.Weight = 0.01;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "StrengthTube";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 3;
    itm.Component1 = "CompCraft_StrengthTobacco";
    itm.Component1Num = 1;
    itm.Component2 = "Mineral7";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Scissors";
    itm.Component3Num = 0;
	n++;

	// Дурно пахнущие грибы
	makeref(itm,Items[n]);
	itm.id = "StrangeMushrooms";
	itm.name = "itmname_StrangeMushrooms";
	itm.describe = "itmdescr_StrangeMushrooms";
	itm.model = "1";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_19";
	itm.price = 500;
	itm.Weight = 0.2;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "SUPPORT";
	n++;

	// Подозрительного цвета жидкость
	makeref(itm,Items[n]);
	itm.id = "StrangePotion";
	itm.name = "itmname_StrangePotion";
	itm.describe = "itmdescr_StrangePotion";
	itm.model = "1";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_19";
	itm.price = 500;
	itm.Weight = 0.5;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "SUPPORT";
	n++;

	// Убойная смесь
	makeref(itm,Items[n]);
	itm.id = "StrangeElixir";
	itm.name = "itmname_StrangeElixir";
	itm.describe = "itmdescr_StrangeElixir";
	itm.model = "1";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_19";
	itm.price = 500;
	itm.Weight = 1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "StrangeElixir";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 6;
    itm.Component1 = "StrangeMushrooms";
    itm.Component1Num = 1;
    itm.Component2 = "StrangePotion";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_StrengthTobacco";
    itm.Component3Num = 5;
    itm.Component4 = "CompCraft_SulfurCrush";
    itm.Component4Num = 3;
    itm.Component5 = "indian20";
    itm.Component5Num = 0;
    itm.Component6 = "indian21";
    itm.Component6Num = 0;
	n++;

//JEWELRY

	makeref(itm,Items[n]);
	itm.id = "jewelry1";
	itm.name = "itmname_jewelry1";
	itm.describe = "itmdescr_jewelry1";
	itm.model = "sapphire";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
    // boal 19.01.2004 -->
	itm.price = 450;
	itm.Weight = 0.2;

    itm.Solder_o.rare = 0.1;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 4;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.05;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.05;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 0;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry2";
	itm.name = "itmname_jewelry2";
	itm.describe = "itmdescr_jewelry2";
	itm.model = "diamond";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 700;
	itm.Weight = 0.2;

    itm.Solder_o.rare = 0.1;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 4;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry3";
	itm.name = "itmname_jewelry3";
	itm.describe = "itmdescr_jewelry3";
	itm.model = "ruby";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 550;
	itm.Weight = 0.2;

    itm.Solder_o.rare = 0.1;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 4;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 0;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry4";
	itm.groupID = JEWELRY_INDIAN_LEFT_ITEM_TYPE;
	itm.name = "itmname_jewelry4";
	itm.describe = "itmdescr_jewelry4";
	itm.model = "emerald";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 500;
	itm.Weight = 0.2;

    itm.Solder_o.rare = 0.1;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 4;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 0;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry5";  // Gold
	itm.name = "itmname_jewelry5";
	itm.describe = "itmdescr_jewelry5";
	itm.model = "sapphire";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 240;
	itm.Weight = 0.7;

    itm.Solder_o.rare = 0.2;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 4;

    itm.Monster.rare = 0.3;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 2;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry6"; // Серебряное кольцо с сапфиром
	itm.name = "itmname_jewelry6";
	itm.describe = "itmdescr_jewelry6";
	itm.model = "sapphire";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_2";
	itm.price = 100;
	itm.Weight = 0.1;
    itm.Solder.rare = 0.01;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    itm.Citizen_f.rare = 0.3;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
	itm.minlevel = 0;
	itm.rare = 0.1;

	itm.PerkReq = 1;
    itm.CraftedItem = "jewelry6";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 5;
    itm.ComponentsNum = 3;
    itm.Component1 = "jewelry1";
    itm.Component1Num = 1;
    itm.Component2 = "jewelry17";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Tools";
    itm.Component3Num = 0;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry7"; // Золотое кольцо с изумрудом
	itm.name = "itmname_jewelry7";
	itm.describe = "itmdescr_jewelry7";
	itm.model = "sapphire";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_2";
	itm.price = 200;
	itm.Weight = 0.1;
    itm.Solder_o.rare = 0.1;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.Monster.rare = 0.05;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
	itm.minlevel = 0;
	itm.rare = 0.1;

	itm.PerkReq = 1;
    itm.CraftedItem = "jewelry7";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 3;
    itm.ComponentsNum = 3;
    itm.Component1 = "jewelry4";
    itm.Component1Num = 1;
    itm.Component2 = "jewelry5";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Tools";
    itm.Component3Num = 0;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry8"; // +10 К везению
	itm.groupID = JEWELRY_INDIAN_LEFT_ITEM_TYPE;
	itm.name = "itmname_jewelry8";
	itm.describe = "itmdescr_jewelry8";
	itm.model = "sapphire";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_2";
	itm.price = 10;
	itm.Weight = 0.1;
    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    itm.Warrior.rare = 0.15;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.Citizen.rare = 0.15;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    itm.Citizen_f.rare = 0.25;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
	itm.minlevel = 0;
	itm.rare = 0.2;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry9"; // +1 sneak
	itm.groupID = JEWELRY_INDIAN_RIGHT_ITEM_TYPE;
	itm.name = "itmname_jewelry9";
	itm.describe = "itmdescr_jewelry9";
	itm.model = "sapphire";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 80;
	itm.Weight = 0.2;

    itm.Solder.rare = 0.01;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Warrior.rare = 0.03;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.2;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 0;
	itm.rare = 0.2;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry10"; // Золотое кольцо с сапфиром
	itm.name = "itmname_jewelry10";
	itm.describe = "itmdescr_jewelry10";
	itm.model = "emerald";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_2";
	itm.price = 170;
	itm.Weight = 0.1;
    itm.Solder_o.rare = 0.2;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.Monster.rare = 0.3;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    itm.Warrior.rare = 0.02;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    itm.Citizen_f.rare = 0.3;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
	itm.minlevel = 1;
	itm.rare = 0.1;

	itm.PerkReq = 1;
    itm.CraftedItem = "jewelry10";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 4;
    itm.ComponentsNum = 3;
    itm.Component1 = "jewelry1";
    itm.Component1Num = 1;
    itm.Component2 = "jewelry5";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Tools";
    itm.Component3Num = 0;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry11";
	itm.name = "itmname_jewelry11";
	itm.describe = "itmdescr_jewelry11";
	itm.model = "pearlbig";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 90;
	itm.Weight = 0.3;

    itm.Solder_o.rare = 0.2;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 5;

    itm.Monster.rare = 0.2;
    itm.Monster.min = 1;
    itm.Monster.max = 6;


    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 6;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 5;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 5;
    // boal 19.01.2004 <--
	itm.minlevel = 0;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry12";
	itm.name = "itmname_jewelry12";
	itm.describe = "itmdescr_jewelry12";
	itm.model = "pearlsmall";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 40;
	itm.Weight = 0.1;

    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 5;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 20;

    itm.Citizen.rare = 0.15;
    itm.Citizen.min = 1;
    itm.Citizen.max = 15;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 5;
    // boal 19.01.2004 <--
	itm.minlevel = 0;
	itm.rare = 0.2;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry13";
	itm.name = "itmname_jewelry13";
	itm.describe = "itmdescr_jewelry13";
	itm.model = "sapphire";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 150;
	itm.Weight = 0.3;

    itm.Solder_o.rare = 0.05;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;

    itm.Monster.rare = 0.01;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 2;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry14";
	itm.name = "itmname_jewelry14";
	itm.describe = "itmdescr_jewelry14";
	itm.model = "sapphire";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 200;
	itm.Weight = 0.1;

    itm.Solder_o.rare = 0.05;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;

    itm.Monster.rare = 0.01;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 2;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry15"; // +1 sneak
	itm.groupID = JEWELRY_INDIAN_LEFT_ITEM_TYPE;
	itm.name = "itmname_jewelry15";
	itm.describe = "itmdescr_jewelry15";
	itm.model = "sapphire";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 300;
	itm.Weight = 0.5;

    itm.Solder_o.rare = 0.01;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;

    itm.Monster.rare = 0.02;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "jewelry16";
	itm.name = "itmname_jewelry16";
	itm.describe = "itmdescr_jewelry16";
	itm.model = "sapphire";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_2";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 10;
	itm.Weight = 0.3;

    itm.Monster.rare = 0.01;
    itm.Monster.min = 1;
    itm.Monster.max = 4;

    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 2;

    itm.Citizen_f.rare = 0.4;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 2;
	itm.rare = 0.05;
	n++;

    makeref(itm,Items[n]);
	itm.id = "jewelry17";  // Серебряный слиток
	itm.name = "itmname_jewelry17";
	itm.describe = "itmdescr_jewelry17";
	itm.model = "pursel";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_7";
	itm.price = 110;
	itm.Weight = 0.5;
    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 5;
    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 3;
    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

    makeref(itm,Items[n]);
	itm.id = "jewelry18"; // Золотое кольцо с рубином
	itm.name = "itmname_jewelry18";
	itm.describe = "itmdescr_jewelry18";
	itm.model = "pursel";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_7";
	itm.price = 330;
	itm.Weight = 0.1;
    itm.Solder_o.rare = 0.2;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.Citizen_f.rare = 0.25;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
	itm.minlevel = 0;
	itm.rare = 0.1;

	itm.PerkReq = 1;
    itm.CraftedItem = "jewelry10";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 2;
    itm.ComponentsNum = 3;
    itm.Component1 = "jewelry3";
    itm.Component1Num = 1;
    itm.Component2 = "jewelry5";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Tools";
    itm.Component3Num = 0;
	n++;

    makeref(itm,Items[n]); // Свинцовые пули
	itm.id = "bullet";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_bullet";
	itm.describe = "itmdescr_bullet";
	itm.model = "pursel";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_8";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel =0;
	itm.rare = 0.3;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

    itm.CraftedItem = "bullet";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 4;
    itm.ComponentsNum = 1;
    itm.Component1 = "CompCraft_Lead";
    itm.Component1Num = 1;
	n++;

	makeref(itm,Items[n]); // Порох
	itm.id = "GunPowder";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_GunPowder";
	itm.describe = "itmdescr_GunPowder";
	itm.model = "pursel";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_7";
	//itm.shown = 0;
	// boal 19.01.2004 -->
	itm.Weight = 0.1;
	itm.price = 8;
	// boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.3;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "grapeshot"; // Картечь
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_grapeshot";
	itm.describe = "itmdescr_grapeshot";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_17";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

    itm.CraftedItem = "grapeshot";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 1;
    itm.Component1 = "CompCraft_Lead";
    itm.Component1Num = 1;
	n++;

	makeref(itm,Items[n]); // бумажный патрон
	itm.id = "cartridge";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_cartridge";
	itm.describe = "itmdescr_cartridge";
	itm.model = "pursel";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_17";
	itm.price = 100;
	itm.Weight = 0.1;
	itm.usepowder = false;
	itm.minlevel = 0;
	itm.rare = 0.05;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

    itm.CraftedItem = "cartridge";
    itm.CraftFor = "Blacksmith";
    itm.ComponentsNum = 3;
    itm.Component1 = "bullet";
    itm.Component1Num = 1;
    itm.Component2 = "GunPowder";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Parchment";
    itm.Component3Num = 1;
	n++;

	makeref(itm,Items[n]); // петарда
	itm.id = "powder_pellet";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_powder_pellet";
	itm.describe = "itmdescr_powder_pellet";
	itm.model = "pursel";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_17";
	itm.price = 200;
	itm.Weight = 0.5;
	itm.usepowder = false;
	itm.minlevel = 0;
	itm.rare = 0.001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

    itm.CraftedItem = "powder_pellet";
    itm.CraftFor = "Blacksmith";
    itm.ComponentsNum = 5;
    itm.Component1 = "CompCraft_Magnesium";
    itm.Component1Num = 2;
    itm.Component2 = "CompCraft_SulfurCrush";
    itm.Component2Num = 3;
    itm.Component3 = "CompCraft_PowderMixture";
    itm.Component3Num = 2;
    itm.Component4 = "CompCraft_Flint";
    itm.Component4Num = 1;
    itm.Component5 = "CompCraft_Tools";
    itm.Component5Num = 0;
	n++;

	makeref(itm,Items[n]); // граната
	itm.id = "grenade";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_grenade";
	itm.describe = "itmdescr_grenade";
	itm.model = "pursel";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_17";
	itm.price = 400;
	itm.Weight = 0.5;
	itm.usepowder = false;
	itm.minlevel = 0;
	itm.rare = 0.001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "grenade";
    itm.CraftFor = "Blacksmith";
    itm.ComponentsNum = 5;
    itm.Component1 = "CompCraft_Lead";
    itm.Component1Num = 4;
    itm.Component2 = "CompCraft_SulfurCrush";
    itm.Component2Num = 6;
    itm.Component3 = "CompCraft_PowderMixture";
    itm.Component3Num = 4;
    itm.Component4 = "CompCraft_Flint";
    itm.Component4Num = 2;
    itm.Component5 = "CompCraft_Locksmith";
    itm.Component5Num = 0;
	n++;

	makeref(itm,Items[n]); // Стрела
	itm.id = "harpoon";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_harpoon";
	itm.describe = "itmdescr_harpoon";
	itm.model = "pursel";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_17";
	itm.price = 500;
	itm.Weight = 1.0;
	itm.usepowder = true;
	itm.minlevel = 0;
	itm.rare = 0.2;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "harpoon";
    itm.CraftFor = "Blacksmith";
    itm.ComponentsNum = 3;
    itm.Component1 = "slave_01";
    itm.Component1Num = 1;
    itm.Component2 = "CompCraft_Grindstone";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Locksmith";
    itm.Component3Num = 0;
	n++;

	makeref(itm,Items[n]); // Капсюли
	itm.id = "GunCap_colt";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_GunCap_colt";
	itm.describe = "itmdescr_GunCap_colt";
	itm.model = "pursel";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_17";
	itm.price = 20;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.0001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "GunCap_colt";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 4;
    itm.ComponentsNum = 3;
    itm.Component1 = "CompCraft_Copper";
    itm.Component1Num = 2;
    itm.Component2 = "CompCraft_Magnesium";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_Puleleyka";
    itm.Component3Num = 0;
	n++;

	makeref(itm,Items[n]); // Револьверный картридж
	itm.id = "shotgun_cartridge";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_shotgun_cartridge";
	itm.describe = "itmdescr_shotgun_cartridge";
	itm.model = "pursel";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_17";
	itm.price = 100;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.0001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	itm.points_shop = 2; //атрибут для ачивок

	itm.PerkReq = 1;
    itm.CraftedItem = "shotgun_cartridge";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 4;
    itm.Component1 = "shotgun_bullet";
    itm.Component1Num = 1;
    itm.Component2 = "GunCap_colt";
    itm.Component2Num = 1;
    itm.Component3 = "CompCraft_PowderMixture";
    itm.Component3Num = 4;
    itm.Component4 = "CompCraft_Locksmith";
    itm.Component4Num = 0;
	n++;

	makeref(itm,Items[n]); // ежовый заряд
	itm.id = "GunEchin";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_GunEchin";
	itm.describe = "itmdescr_GunEchin";
	itm.model = "pursel";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_17";
	itm.price = 50;
	itm.Weight = 0.4;
	itm.minlevel = 0;
	itm.rare = 0.0001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	itm.points_shop = 1; //атрибут для ачивок

    itm.CraftedItem = "GunEchin";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 5;
    itm.Component1 = "CompCraft_Nails";
    itm.Component1Num = 2;
    itm.Component2 = "CompCraft_SulfurCrush";
    itm.Component2Num = 6;
    itm.Component3 = "gunpowder";
    itm.Component3Num = 4;
    itm.Component4 = "CompCraft_Parchment";
    itm.Component4Num = 2;
    itm.Component5 = "CompCraft_Flint";
    itm.Component5Num = 1;
	n++;

	makeref(itm,Items[n]); // Револьверные пули
	itm.id = "shotgun_bullet";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_shotgun_bullet";
	itm.describe = "itmdescr_shotgun_bullet";
	itm.model = "1";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_17";
	itm.price = 100;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.0001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";

	itm.PerkReq = 1;
    itm.CraftedItem = "shotgun_bullet";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 4;
    itm.ComponentsNum = 2;
    itm.Component1 = "CompCraft_Lead";
    itm.Component1Num = 2;
    itm.Component2 = "CompCraft_Puleleyka";
    itm.Component2Num = 0;
	n++;

	makeref(itm,Items[n]); // Гильзы 12 калибра
	itm.id = "12_gauge";
	itm.groupID = AMMO_ITEM_TYPE;
	itm.name = "itmname_12_gauge";
	itm.describe = "itmdescr_12_gauge";
	itm.model = "pursel";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_14";
	itm.price = 100;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.0001;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	itm.points_shop = 2; //атрибут для ачивок

	itm.PerkReq = 1;
    itm.CraftedItem = "12_gauge";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 1;
    itm.ComponentsNum = 3;
    itm.Component1 = "GunCap_colt";
    itm.Component1Num = 1;
    itm.Component2 = "CompCraft_PowderMixture";
    itm.Component2Num = 4;
    itm.Component3 = "CompCraft_Locksmith";
    itm.Component3Num = 0;
	n++;

	makeref(itm,Items[n]); // Отмычка
	itm.id = "Lockpick";
	itm.name = "itmname_Lockpick";
	itm.describe = "itmdescr_Lockpick";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_14";
	itm.Weight = 0.1;
	itm.price = 15;
	itm.minlevel =0;
	itm.rare = 0.2;
	itm.SortIndex = 1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral2";
	itm.name = "itmname_mineral2";
	itm.describe = "itmdescr_mineral2";
	itm.model = "sapphire";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_8";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 300;
	itm.Weight = 6;

    itm.Solder.rare = 0.01;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.02;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral3";
	itm.name = "itmname_mineral3";
	itm.describe = "itmdescr_mineral3";
	itm.model = "sapphire";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_8";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 10;
	itm.Weight = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 4;

    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral4"; // баклан
	itm.name = "itmname_mineral4";
	itm.describe = "itmdescr_mineral4";
	itm.model = "pursel"; // чтоб был виден
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_8";
//	itm.shown = false;
	itm.price = 25;
	// boal 19.01.2004 -->
	itm.Weight = 2;

    itm.Solder.rare = 0.05;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 3;

    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.05;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.05;
	n++;

    makeref(itm,Items[n]);
	itm.id = "mineral5";
	itm.name = "itmname_mineral5";
	itm.describe = "itmdescr_mineral5";
	itm.model = "pursel";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 2;
	itm.Weight = 3;

    itm.Monster.rare = 0.01;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.02;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral6";
	itm.name = "itmname_mineral6";
	itm.describe = "itmdescr_mineral6";
	itm.model = "pursel";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 20;
	itm.Weight = 1;

    itm.Solder.rare = 0.001;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.3;
    itm.Monster.min = 1;
    itm.Monster.max = 3;

    itm.Warrior.rare = 0.001;
    itm.Warrior.min = 1;
    itm.Warrior.max = 5;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 5;
    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.4;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral7";
	itm.name = "itmname_mineral7";
	itm.describe = "itmdescr_mineral7";
	itm.model = "pursel";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 140;
	itm.Weight = 0.8;

    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 3;

    itm.Warrior.rare = 0.3;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.2;
	n++;

    makeref(itm,Items[n]);
	itm.id = "mineral8";
	itm.name = "itmname_mineral8";
	itm.describe = "itmdescr_mineral8";
	itm.model = "pursel";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_9";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 30;
	itm.Weight = 1;

    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel =4;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral9";
	itm.name = "itmname_mineral9";
	itm.describe = "itmdescr_mineral9";
	itm.model = "pursel";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_9";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 80;
	itm.Weight = 1;

    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 3;

    itm.Warrior.rare = 0.2;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel =2;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "mineral10";
	itm.name = "itmname_mineral10";
	itm.describe = "itmdescr_mineral10";
	itm.model = "pursel";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_9";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 4;
	itm.Weight = 1;

    itm.Solder.rare = 0.001;
    itm.Solder.min = 1;
    itm.Solder.max = 5;

    itm.Monster.rare = 0.001;
    itm.Monster.min = 1;
    itm.Monster.max = 3;

    itm.Warrior.rare = 0.001;
    itm.Warrior.min = 1;
    itm.Warrior.max = 5;
    // boal 19.01.2004 <--
	itm.minlevel =0;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "sculMa1";
	itm.name = "itmname_sculMa1"; // Белый хрустальный череп
	itm.describe = "itmdescr_sculMa1";
	itm.model = "pursel";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_9";
	itm.price = 5000;
	// boal 19.01.2004 -->
	itm.Weight = 3.5;
	// boal 19.01.2004 <--
	itm.minlevel =5;
	itm.rare = 0.01;
	itm.points_shop = 350; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "sculMa2";
	itm.name = "itmname_sculMa2"; // Розовый хрустальный череп
	itm.describe = "itmdescr_sculMa2";
	itm.model = "pursel";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_9";
	itm.price = 7000;
	// boal 19.01.2004 -->
	itm.Weight = 3.5;
	// boal 19.01.2004 <--
	itm.minlevel =1;
	itm.rare = 0.01;
	itm.points_shop = 350; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "sculMa3";
	itm.name = "itmname_sculMa3"; // Голубой хрустальный череп
	itm.describe = "itmdescr_sculMa3";
 	itm.model = "pursel";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_9";
	itm.price = 10000;
	// boal 19.01.2004 -->
	itm.Weight = 3.5;
	// boal 19.01.2004 <--
	itm.minlevel =1;
	itm.rare = 0.01;
	itm.points_shop = 350; // Атрибут для магазина ачивок
	n++;

//INDIAN TRINKETS

	makeref(itm,Items[n]);
	itm.id = "indian1"; // +1 sneak
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian1";
	itm.describe = "itmdescr_indian1";
	itm.model = "pursel";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 30;
	itm.Weight = 3;

    itm.Solder.rare = 0.001;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.03;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.001;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.005;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian2";
	itm.name = "itmname_indian2";
	itm.describe = "itmdescr_indian2";
	itm.model = "pursel";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 40;
	itm.Weight = 1;

    itm.Solder.rare = 0.02;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Monster.rare = 0.03;
    itm.Monster.min = 1;
    itm.Monster.max = 3;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian3";
	itm.groupID = JEWELRY_INDIAN_RIGHT_ITEM_TYPE;
	itm.name = "itmname_indian3";
	itm.describe = "itmdescr_indian3";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 100;
	itm.Weight = 0.6;

    itm.Monster.rare = 0.05;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian4";
	itm.name = "itmname_indian4";
	itm.describe = "itmdescr_indian4";
	itm.model = "pursel";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 5;
	itm.Weight = 2;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.2;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian5"; // +1 sneak
	itm.groupID = JEWELRY_INDIAN_LEFT_ITEM_TYPE;
	itm.name = "itmname_indian5";
	itm.describe = "itmdescr_indian5";
	itm.model = "sapphire";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 130;
	itm.Weight = 1.5;

    itm.Monster.rare = 0.05;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.03;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 3;
	itm.rare = 0.05;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian6";
	itm.groupID = JEWELRY_INDIAN_RIGHT_ITEM_TYPE;
	itm.name = "itmname_indian6";
	itm.describe = "itmdescr_indian6";
	itm.model = "sapphire";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 600;
	itm.Weight = 1;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.001;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 2;
	itm.rare = 0.005;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian7"; // +1 sneak
	itm.groupID = JEWELRY_INDIAN_RIGHT_ITEM_TYPE;
	itm.name = "itmname_indian7";
	itm.describe = "itmdescr_indian7";
	itm.model = "sapphire";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 150;
	itm.Weight = 3.6;

    itm.Monster.rare = 0.07;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.01;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.01;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 4;
	itm.rare = 0.03;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian8";
	itm.name = "itmname_indian8";
	itm.describe = "itmdescr_indian8";
	itm.model = "sapphire";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 120;
	itm.Weight = 0.6;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 4;
	itm.rare = 0.07;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian9";
	itm.name = "itmname_indian9";
	itm.describe = "itmdescr_indian9";
	itm.model = "sapphire";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 20;
	itm.Weight = 1;

    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.2;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 5;
	itm.rare = 0.03;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian11";  // Крысиный бог
	itm.name = "itmname_indian11";
	itm.describe = "itmdescr_indian11";
	itm.model = "";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 5000;
	itm.Weight = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 5;
	itm.rare = 0.001;
	itm.points_shop = 250; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian10";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian10";
	itm.describe = "itmdescr_indian10";
	itm.model = "sapphire";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 210;
	itm.Weight = 2;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 7;
	itm.rare = 0.03;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian12";
	itm.groupID = JEWELRY_INDIAN_LEFT_ITEM_TYPE;
	itm.name = "itmname_indian12";
	itm.describe = "itmdescr_indian12";
	itm.model = "sapphire";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 1230;
	itm.Weight = 10;

    itm.Monster.rare = 0.3;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.1;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.2;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;

    itm.Solder.rare = 0.001;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 7;
	itm.rare = 0.001;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian13";
	itm.name = "itmname_indian13";
	itm.describe = "itmdescr_indian13";
	itm.model = "pursel";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 40;
	itm.Weight = 3;

    itm.Monster.rare = 0.05;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.1;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;

    itm.Solder.rare = 0.001;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.1;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian14";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian14";
	itm.describe = "itmdescr_indian14";
	itm.model = "pursel";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 110;
	itm.Weight = 3;

    itm.Monster.rare = 0.1;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.05;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.2;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;

    itm.Solder.rare = 0.001;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 10;
	itm.rare = 0.005;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian15";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian15";
	itm.describe = "itmdescr_indian15";
	itm.model = "sapphire";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 500;
	itm.Weight = 30;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 3;
	itm.rare = 0.005;
	n++;

	makeref(itm,Items[n]);
	itm.id = "indian16";
	itm.name = "itmname_indian16";
	itm.describe = "itmdescr_indian16";
	itm.model = "sapphire";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_5";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 15;
	itm.Weight = 3;

    itm.Monster.rare = 0.001;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.001;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.2;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.2;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;

    itm.Solder.rare = 0.1;
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 3;
	itm.rare = 0.05;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian17"; // +1 sneak
	itm.groupID = JEWELRY_INDIAN_RIGHT_ITEM_TYPE;
	itm.name = "itmname_indian17";
	itm.describe = "itmdescr_indian17";
	itm.model = "sapphire";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_9";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 50;
	itm.Weight = 2;

    itm.Monster.rare = 0.06;
    itm.Monster.min = 1;
    itm.Monster.max = 1;

    itm.Warrior.rare = 0.02;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;

    itm.Citizen.rare = 0.01;
    itm.Citizen.min = 1;
    itm.Citizen.max = 1;

    itm.Citizen_f.rare = 0.1;
    itm.Citizen_f.min = 1;
    itm.Citizen_f.max = 1;

    itm.Solder.rare = 0.01
    itm.Solder.min = 1;
    itm.Solder.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.05;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian18";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian18";
	itm.describe = "itmdescr_indian18";
	itm.model = "pursel";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 75;
	itm.Weight = 2;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian19";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian19";
	itm.describe = "itmdescr_indian19";
	itm.model = "pursel";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 950;
	itm.Weight = 2;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian20";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian20";
	itm.describe = "itmdescr_indian20";
	itm.model = "pursel";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 750;
	itm.Weight = 2;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian21";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian21";
	itm.describe = "itmdescr_indian21";
	itm.model = "sapphire";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 25;
	itm.Weight = 2;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

    makeref(itm,Items[n]);
	itm.id = "indian22";
	itm.groupID = INDIAN_CENTER_ITEM_TYPE;
	itm.name = "itmname_indian22";
	itm.describe = "itmdescr_indian22";
	itm.model = "pursel";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_7";
//	itm.shown = false;
	// boal 19.01.2004 -->
	itm.price = 5;
	itm.Weight = 2;

    itm.Monster.rare = 0.005;
    itm.Monster.min = 1;
    itm.Monster.max = 1;
    // boal 19.01.2004 <--
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

	// броня
    makeref(itm,Items[n]);
	itm.id = "cirass1"; // Скальд
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = false;
	itm.name = "itmname_cirass1";
	itm.describe = "itmdescr_cirass1";
	itm.folder = "items";
	itm.model = "1";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_8";
	itm.price = 7000;
	// boal 19.01.2004 -->
	itm.Weight = 30;
	itm.CirassLevel = 0.05;
	itm.CirassLevel.fast = 0.25;
	itm.CirassLevel.force = 0.10;
	itm.CirassLevel.round = 0.20;
	itm.CirassLevel.break = 0.10;
	itm.CirassLevel.feint = 0.20;
	// boal 19.01.2004 <--
	itm.minlevel = 2;
	itm.rare = 0.01;

    itm.Solder.rare = 0.01;
    itm.Solder.min = 1;
    itm.Solder.max = 1;

    itm.Warrior.rare = 0.01;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "cirass2"; // Рейтарский панцирь
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = false;
	itm.name = "itmname_cirass2";
	itm.describe = "itmdescr_cirass2";
	itm.folder = "items";
	itm.model = "2";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_8";
	itm.price = 15000;
	// boal 19.01.2004 -->
	itm.Weight = 25;
	itm.CirassLevel = 0.10;
	itm.CirassLevel.fast = 0.35;
	itm.CirassLevel.force = 0.20;
	itm.CirassLevel.round = 0.30;
	itm.CirassLevel.break = 0.20;
	itm.CirassLevel.feint = 0.30;
	// boal 19.01.2004 <--
	itm.minlevel = 5;
	itm.rare = 0.1;

    itm.Solder_o.rare = 0.01;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;

    itm.Warrior.rare = 0.005;
    itm.Warrior.min = 1;
    itm.Warrior.max = 1;
    itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "cirass3"; // Гвардейская кираса
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = false;
	itm.name = "itmname_cirass3";
	itm.describe = "itmdescr_cirass3";
	itm.folder = "items";
	itm.model = "3";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_8";
	itm.price = 19000;
	// boal 19.01.2004 -->
	itm.Weight = 20;
	itm.CirassLevel = 0.15;
	itm.CirassLevel.fast = 0.40;
	itm.CirassLevel.force = 0.25;
	itm.CirassLevel.round = 0.35;
	itm.CirassLevel.break = 0.30;
	itm.CirassLevel.feint = 0.35;
	// boal 19.01.2004 <--
	itm.minlevel = 11;
	itm.rare = 0.1;

	itm.Solder_o.rare = 0.003;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.ItemType = "SUPPORT";
	n++;

    makeref(itm,Items[n]);
	itm.id = "cirass4"; // Офицерская кираса
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = false;
	itm.name = "itmname_cirass4";
	itm.describe = "itmdescr_cirass4";
	itm.folder = "items";
	itm.model = "4";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_8";
	itm.price = 22000;
	// boal 19.01.2004 -->
	itm.Weight = 23;
	itm.CirassLevel = 0.20;
	itm.CirassLevel.fast = 0.45;
	itm.CirassLevel.force = 0.30;
	itm.CirassLevel.round = 0.40;
	itm.CirassLevel.break = 0.40;
	itm.CirassLevel.feint = 0.40;
	// boal 19.01.2004 <--
	itm.minlevel = 9;
	itm.rare = 0.1;

    itm.Solder_o.rare = 0.003;
    itm.Solder_o.min = 1;
    itm.Solder_o.max = 1;
    itm.ItemType = "SUPPORT";
    n++;

	makeref(itm,Items[n]);
	itm.id = "cirass5"; // Наградная кираса
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = false;
	itm.name = "itmname_cirass5";
	itm.describe = "itmdescr_cirass5";
	itm.folder = "items";
	itm.model = "5";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_8";
	itm.price = 30000;
	// boal 19.01.2004 -->
	itm.Weight = 17;
	itm.CirassLevel = 0.30;
	itm.CirassLevel.fast = 0.55;
	itm.CirassLevel.force = 0.40;
	itm.CirassLevel.round = 0.50;
	itm.CirassLevel.break = 0.50;
	itm.CirassLevel.feint = 0.50;
	// boal 19.01.2004 <--
	itm.minlevel = 20;
	itm.rare = 0.001;
	itm.ItemType = "SUPPORT";
	itm.points_shop = 1000; // Атрибут для магазина ачивок
	n++;

	// одежда 07.03.05
	makeref(itm,Items[n]);
	itm.id = "suit_1"; // Обноски
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = true;
	itm.name = "itmname_suit_1";
	itm.describe = "itmdescr_suit_1";
	itm.folder = "items";
	itm.model = "6";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_9";
	itm.price = 20;
	itm.Weight = 6;
	itm.CirassLevel = 0.0;
	itm.minlevel = 20;
	itm.rare = 0.001;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "suit_2"; // Одежда купца
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = true;
	itm.name = "itmname_suit_2";
	itm.describe = "itmdescr_suit_2";
	itm.folder = "items";
	itm.model = "7";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_1";
	itm.price = 20000;
	itm.Weight = 8;
	itm.CirassLevel = 0.0;
	itm.minlevel = 20;
	itm.rare = 0.001;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);
	itm.id = "suit_3"; // Одежда дворянина
	itm.groupID = CIRASS_ITEM_TYPE;
	itm.Clothes = true;
	itm.name = "itmname_suit_3";
	itm.describe = "itmdescr_suit_3";
	itm.folder = "items";
	itm.model = "8";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_1";
	itm.price = 150000;
	itm.Weight = 7;
	itm.CirassLevel = 0.0;
	itm.minlevel = 20;
	itm.rare = 0.001;
	itm.ItemType = "SUPPORT";
	n++;

	/////////////////// Обереги
	makeref(itm,Items[n]);
	itm.id = "talisman1"; // Маска Кукулькана
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman1";
	itm.describe = "itmdescr_talisman1";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "fighter";
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman2"; // Иона
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman2";
	itm.describe = "itmdescr_talisman2";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "navigator";
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman3"; // Молот Тора
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman3";
	itm.describe = "itmdescr_talisman3";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "cannoner";
	itm.points_shop = 650; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman4"; // Янычар
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman4";
	itm.describe = "itmdescr_talisman4";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "boatswain";
	itm.points_shop = 650; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman6"; // Богиня
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman6";
	itm.describe = "itmdescr_talisman6";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "doctor";
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman7"; // Скарабей
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman7";
	itm.describe = "itmdescr_talisman7";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "carpenter";
	itm.points_shop = 650; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman8"; // Скорпион
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman8";
	itm.describe = "itmdescr_talisman8";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_16";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.kind = "fighter";
	itm.points_shop = 650; // Атрибут для магазина ачивок
	n++;

	makeref(itm,Items[n]);
	itm.id = "talisman9"; // Святая Чаша
	itm.groupID = TALISMAN_ITEM_TYPE;
	itm.name = "itmname_talisman9";
	itm.describe = "itmdescr_talisman9";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_19";
	itm.price = 25000;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = 0.001;
	n++;

	// ККС Нааб-те
	makeref(itm,Items[n]);
	itm.id = "blade_01";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade_01";
	itm.describe = "itmdescr_blade_01";
	itm.folder = "items";
	itm.model = "blade_01";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_16";
	// boal 19.01.2004 -->
	itm.price = 300;
	itm.Weight = 2.0 + fRandSmall(1.0); // 1;
	// boal 19.01.2004 <--
	itm.dmg_min = 4.0 + Rand(2); // 7.0;
	itm.dmg_max = 33.0 + Rand(5); // 15.0;
	itm.piercing = 25;
	itm.special.valueP = 5; 	//Отравление
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 45;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	// Флаг "генерить цену"
	itm.Generation.dmg_min.min = 4.0;
	itm.Generation.dmg_min.max = 6.0;
	itm.Generation.dmg_max.min = 33.0;
	itm.Generation.dmg_max.max = 38.0;
	itm.Generation.Weight.min = 2.0;
	itm.Generation.Weight.max = 3.0;
    n++;

	// ККС Тлакоман
	makeref(itm,Items[n]);
	itm.id = "blade_02";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade_02";
	itm.describe = "itmdescr_blade_02";
	itm.folder = "items";
	itm.model = "blade_02";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_16";
	// boal 19.01.2004 -->
	itm.price = 300;
	itm.Weight = 2.5 + fRandSmall(1.0); // 1;
	// boal 19.01.2004 <--
	itm.dmg_min = 6.0 + Rand(4); // 7.0;
	itm.dmg_max = 40.0 + Rand(5); // 15.0;
	itm.piercing = 25;
	itm.special.valueP = 5; 	//Отравление
	itm.minlevel = 0;
	itm.rare = 0.1;
	itm.block = 45;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "poor";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	// Флаг "генерить цену"
	itm.Generation.dmg_min.min = 6.0;
	itm.Generation.dmg_min.max = 10.0;
	itm.Generation.dmg_max.min = 40.0;
	itm.Generation.dmg_max.max = 45.0;
	itm.Generation.Weight.min = 2.5;
	itm.Generation.Weight.max = 3.5;
    n++;

	// ККС Томагавк
	makeref(itm,Items[n]);
	itm.id = "topor_05";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_topor_05";
	itm.describe = "itmdescr_topor_05";
	itm.folder = "items";
	itm.model = "topor_05";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_16";
	// boal 19.01.2004 -->
	itm.price = 150;
	itm.Weight = 4.5 + fRandSmall(1.5); // 6;
	// boal 19.01.2004 <--
	itm.dmg_min = 14.0 + rand(5); // 10.0;
	itm.dmg_max = 50.0 + rand(5); // 60.0;
	itm.piercing = 24.0;
	itm.special.valueCB = 6; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.block = 12;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "Fencing";
	itm.ItemType = "WEAPON";
	itm.quality = "ordinary";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.dmg_min.min = 14.0;
	itm.Generation.dmg_min.max = 19.0;
	itm.Generation.dmg_max.min = 50.0;
	itm.Generation.dmg_max.max = 55.0;
	itm.Generation.Weight.min = 4.5;
	itm.Generation.Weight.max = 6.0;
	n++;

	// ККС Макуауитль
	makeref(itm,Items[n]);
	itm.id = "topor_01";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_toporAZ";
	itm.describe = "itmdescr_toporAZ";
	itm.folder = "items";
	itm.model = "topor_01";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_16";
	// boal 19.01.2004 -->
	itm.price = 17500;
	itm.Weight = 12.0 + fRandSmall(2.5); // 15.0;
	// boal 19.01.2004 <--
	itm.dmg_min = 50.0 + rand(10); // 45.0;
	itm.dmg_max = 120.0 + rand(10); // 140.0;
	itm.piercing = 105.0;
	itm.special.valueSS = 15; //Резкий удар
	itm.special.valueCrB = 5; //Буст крита
	itm.special.valueT = 10; //Травмы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 40.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	// Warship 08.05.09 - Новая система предметов, параметры для генерации
	itm.Generation.qty = 5;
	itm.Generation.dmg_min.min = 50.0;
	itm.Generation.dmg_min.max = 60.0;
	itm.Generation.dmg_max.min = 120.0;
	itm.Generation.dmg_max.max = 130.0;
	itm.Generation.Weight.min = 12.0;
	itm.Generation.Weight.max = 14.5;
	n++;

	// Топор Викинга
	makeref(itm,Items[n]);
	itm.id = "topor_viking";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_topor_viking";
	itm.describe = "itmdescr_topor_viking";
	itm.folder = "items";
	itm.model = "topor_viking";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_14";
	itm.price = 17500;
	itm.Weight = 12.0;
	itm.dmg_min = 60.0;
	itm.dmg_max = 140.0;
	itm.piercing = 110.0;
	itm.special.valueT = 5; //Травмы
	itm.special.valueStS = 5; //Стан
	itm.special.valueCB = 20; //Пролом кирасы
	itm.minlevel = 99;
	itm.rare = 0.0001;
	itm.block = 40.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// Клинок Виспер
	makeref(itm,Items[n]);
	itm.id = "blade_whisper";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade_whisper";
	itm.describe = "itmdescr_blade_whisper";
	itm.folder = "items";
	itm.model = "blade_whisper";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_14";
	itm.price = 10000;
	itm.Weight = 2.7;
	itm.dmg_min = 20.0;
	itm.dmg_max = 72.0;
	itm.piercing = 100;
	itm.special.valueStS = 12; //Стан
	itm.special.valueSS = 6; //Резкий удар
	//itm.special.valueBB = 15; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 95;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingLight";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	// Дадао
	makeref(itm,Items[n]);
	itm.id = "blade_china";
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_blade_china";
	itm.describe = "itmdescr_blade_china";
	itm.folder = "items";
	itm.model = "blade_china";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_14";
	itm.price = 400;
	itm.Weight = 10.0;
	itm.dmg_min = 50.0;
	itm.dmg_max = 120.0;
	itm.piercing = 100;
	itm.special.valueT = 10; //Травмы
	itm.special.valueSS = 5; //Резкий удар
	itm.special.valueBB = 15; //Пролом блока
	itm.minlevel = 1;
	itm.rare = 0.1;
	itm.block = 60;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
    itm.FencingType = "FencingHeavy";
    itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	n++;

	//Императорский топор
    makeref(itm,Items[n]);
	itm.id = "topor_emperor";  //Топор
	itm.groupID = BLADE_ITEM_TYPE;
	itm.name = "itmname_topor_emperor";
	itm.describe = "itmdescr_topor_emperor";
	itm.folder = "items";
	itm.model = "topor_emperor";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_14";
	itm.price = 100000;
	itm.Weight = 9.0 + fRandSmall(2.0);
	itm.dmg_min = 40.0 + rand(10);
	itm.dmg_max = 80.0+ rand(10);
	itm.piercing = 100.0;
	itm.special.valueT = 5; //Травмы
	itm.special.valueStS = 10; //Стан
	itm.special.valueCB = 15; //Пролом кирасы
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.block = 30.0;
	itm.param.time = 0.1;
	itm.param.colorstart = argb(64, 64, 64, 64);
	itm.param.colorend = argb(0, 32, 32, 32);
	itm.FencingType = "FencingHeavy";
	itm.ItemType = "WEAPON";
	itm.quality = "excellent";
	itm.Generation.qty = 5;
	itm.Generation.price = true; // Флаг "генерить цену"
	itm.Generation.dmg_min.min = 40.0;
	itm.Generation.dmg_min.max = 50.0;
	itm.Generation.dmg_max.min = 80.0;
	itm.Generation.dmg_max.max = 90.0;
	itm.Generation.Weight.min = 9.0;
	itm.Generation.Weight.max = 11.0;
	n++;
	/////////////////////////////////////////////////////////
	/////		-->		CSP Книги 56 штук				/////
	/////////////////////////////////////////////////////////

	/////////////// *** 1 уровень *** ///////////////

	makeref(itm,Items[n]);
	itm.id = "book1_1"; // Авторитет
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_1";
	itm.describe = "itmdescr_book1_1";
	itm.picIndex = 1;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Leadership";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_2"; // Легкое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_2";
	itm.describe = "itmdescr_book1_2";
	itm.picIndex = 2;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingLight";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_3"; // Среднее оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_3";
	itm.describe = "itmdescr_book1_3";
	itm.picIndex = 3;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fencing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_4"; // Тяжелое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_4";
	itm.describe = "itmdescr_book1_4";
	itm.picIndex = 4;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingHeavy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_5"; // Пистолеты
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_5";
	itm.describe = "itmdescr_book1_5";
	itm.picIndex = 5;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Pistol";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_6"; // Везение
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_6";
	itm.describe = "itmdescr_book1_6";
	itm.picIndex = 6;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fortune";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_7"; // Скрытность
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_7";
	itm.describe = "itmdescr_book1_7";
	itm.picIndex = 7;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sneak";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_8"; // Навигация
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_8";
	itm.describe = "itmdescr_book1_8";
	itm.picIndex = 8;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sailing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_9"; // Меткость
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_9";
	itm.describe = "itmdescr_book1_9";
	itm.picIndex = 9;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Accuracy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_10"; // Орудия
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_10";
	itm.describe = "itmdescr_book1_10";
	itm.picIndex = 10;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Cannons";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_11"; // Абордаж
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_11";
	itm.describe = "itmdescr_book1_11";
	itm.picIndex = 11;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Grappling";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_12"; // Защита
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_12";
	itm.describe = "itmdescr_book1_12";
	itm.picIndex = 12;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Defence";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_13"; // Починка
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_13";
	itm.describe = "itmdescr_book1_13";
	itm.picIndex = 13;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Repair";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book1_14"; // Торговля
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book1_14";
	itm.describe = "itmdescr_book1_14";
	itm.picIndex = 14;
	itm.picTexture = "BOOK1";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Commerce";
	n++;

	/////////////// *** 1 уровень *** ///////////////

	/////////////// *** 2 уровень *** ///////////////

	makeref(itm,Items[n]);
	itm.id = "book2_1"; // Авторитет
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_1";
	itm.describe = "itmdescr_book2_1";
	itm.picIndex = 1;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Leadership";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_2"; // Легкое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_2";
	itm.describe = "itmdescr_book2_2";
	itm.picIndex = 2;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingLight";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_3"; // Среднее оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_3";
	itm.describe = "itmdescr_book2_3";
	itm.picIndex = 3;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fencing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_4"; // Тяжелое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_4";
	itm.describe = "itmdescr_book2_4";
	itm.picIndex = 4;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingHeavy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_5"; // Пистолеты
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_5";
	itm.describe = "itmdescr_book2_5";
	itm.picIndex = 5;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Pistol";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_6"; // Везение
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_6";
	itm.describe = "itmdescr_book2_6";
	itm.picIndex = 6;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fortune";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_7"; // Скрытность
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_7";
	itm.describe = "itmdescr_book2_7";
	itm.picIndex = 7;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sneak";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_8"; // Навигация
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_8";
	itm.describe = "itmdescr_book2_8";
	itm.picIndex = 8;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sailing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_9"; // Меткость
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_9";
	itm.describe = "itmdescr_book2_9";
	itm.picIndex = 9;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Accuracy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_10"; // Орудия
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_10";
	itm.describe = "itmdescr_book2_10";
	itm.picIndex = 10;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Cannons";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_11"; // Абордаж
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_11";
	itm.describe = "itmdescr_book2_11";
	itm.picIndex = 11;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Grappling";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_12"; // Защита
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_12";
	itm.describe = "itmdescr_book2_12";
	itm.picIndex = 12;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Defence";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_13"; // Починка
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_13";
	itm.describe = "itmdescr_book2_13";
	itm.picIndex = 13;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Repair";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book2_14"; // Торговля
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book2_14";
	itm.describe = "itmdescr_book2_14";
	itm.picIndex = 14;
	itm.picTexture = "BOOK2";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(0.5);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Commerce";
	n++;

	/////////////// *** 2 уровень *** ///////////////

	/////////////// *** 3 уровень *** ///////////////

	makeref(itm,Items[n]);
	itm.id = "book3_1"; // Авторитет
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_1";
	itm.describe = "itmdescr_book3_1";
	itm.picIndex = 1;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Leadership";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_2"; // Легкое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_2";
	itm.describe = "itmdescr_book3_2";
	itm.picIndex = 2;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingLight";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_3"; // Среднее оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_3";
	itm.describe = "itmdescr_book3_3";
	itm.picIndex = 3;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fencing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_4"; // Тяжелое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_4";
	itm.describe = "itmdescr_book3_4";
	itm.picIndex = 4;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingHeavy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_5"; // Пистолеты
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_5";
	itm.describe = "itmdescr_book3_5";
	itm.picIndex = 5;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Pistol";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_6"; // Везение
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_6";
	itm.describe = "itmdescr_book3_6";
	itm.picIndex = 6;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fortune";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_7"; // Скрытность
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_7";
	itm.describe = "itmdescr_book3_7";
	itm.picIndex = 7;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sneak";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_8"; // Навигация
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_8";
	itm.describe = "itmdescr_book3_8";
	itm.picIndex = 8;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sailing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_9"; // Меткость
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_9";
	itm.describe = "itmdescr_book3_9";
	itm.picIndex = 9;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Accuracy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_10"; // Орудия
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_10";
	itm.describe = "itmdescr_book3_10";
	itm.picIndex = 10;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Cannons";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_11"; // Абордаж
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_11";
	itm.describe = "itmdescr_book3_11";
	itm.picIndex = 11;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Grappling";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_12"; // Защита
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_12";
	itm.describe = "itmdescr_book3_12";
	itm.picIndex = 12;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Defence";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_13"; // Починка
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_13";
	itm.describe = "itmdescr_book3_13";
	itm.picIndex = 13;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Repair";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book3_14"; // Торговля
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book3_14";
	itm.describe = "itmdescr_book3_14";
	itm.picIndex = 14;
	itm.picTexture = "BOOK3";
	itm.price = 1000;
	itm.Weight = 0.5 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Commerce";
	n++;

	/////////////// *** 3 уровень *** ///////////////

	/////////////// *** 4 уровень *** ///////////////

	makeref(itm,Items[n]);
	itm.id = "book4_1"; // Авторитет
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_1";
	itm.describe = "itmdescr_book4_1";
	itm.picIndex = 1;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Leadership";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_2"; // Легкое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_2";
	itm.describe = "itmdescr_book4_2";
	itm.picIndex = 2;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingLight";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_3"; // Среднее оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_3";
	itm.describe = "itmdescr_book4_3";
	itm.picIndex = 3;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fencing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_4"; // Тяжелое оружие
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_4";
	itm.describe = "itmdescr_book4_4";
	itm.picIndex = 4;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "FencingHeavy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_5"; // Пистолеты
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_5";
	itm.describe = "itmdescr_book4_5";
	itm.picIndex = 5;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Pistol";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_6"; // Везение
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_6";
	itm.describe = "itmdescr_book4_6";
	itm.picIndex = 6;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Fortune";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_7"; // Скрытность
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_7";
	itm.describe = "itmdescr_book4_7";
	itm.picIndex = 7;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sneak";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_8"; // Навигация
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_8";
	itm.describe = "itmdescr_book4_8";
	itm.picIndex = 8;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Sailing";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_9"; // Меткость
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_9";
	itm.describe = "itmdescr_book4_9";
	itm.picIndex = 9;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Accuracy";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_10"; // Орудия
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_10";
	itm.describe = "itmdescr_book4_10";
	itm.picIndex = 10;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Cannons";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_11"; // Абордаж
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_11";
	itm.describe = "itmdescr_book4_11";
	itm.picIndex = 11;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Grappling";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_12"; // Защита
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_12";
	itm.describe = "itmdescr_book4_12";
	itm.picIndex = 12;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Defence";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_13"; // Починка
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_13";
	itm.describe = "itmdescr_book4_13";
	itm.picIndex = 13;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Repair";
	n++;

	makeref(itm,Items[n]);
	itm.id = "book4_14"; // Торговля
	itm.groupID = BOOK_ITEM_TYPE;
	itm.name = "itmname_book4_14";
	itm.describe = "itmdescr_book4_14";
	itm.picIndex = 14;
	itm.picTexture = "BOOK4";
	itm.price = 1000;
	itm.Weight = 1.0 + fRandSmall(1.0);
	itm.minlevel = 1;
	itm.rare = 0.01;
	itm.skill = "Commerce";
	n++;

	/////////////// *** 4 уровень *** ///////////////

	/////////////////////////////////////////////////////////
	/////		<--		CSP Книги 56 штук				/////
	/////////////////////////////////////////////////////////

	makeref(itm, Items[n]); //письмо для моего квеста
    itm.id = "Lukes_letter";
    itm.name = "itmname_Lukes_letter";
    itm.describe = "itmdescr_Lukes_letter";
    itm.model = "letter";
    itm.picIndex = 16;
    itm.picTexture = "ITEMS_4";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Проклятый идол"
    itm.id = "Cursed_idol";
    itm.name = "itmname_Cursed_idol";
    itm.describe = "itmdescr_Cursed_idol";
    itm.picIndex = 9;
    itm.picTexture = "ITEMS_14";
    itm.price = 0;
    itm.Weight = 1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Новая Родина"
    itm.id = "Patent_Espa_Lesopilka";	//Испанский патент для Хьюго
    itm.name = "itmname_Patent_Espa_Lesopilka";
    itm.describe = "itmdescr_Patent_Espa_Lesopilka";
    itm.picIndex = 3;
    itm.picTexture = "ITEMS_4";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Золото не тонет"
    itm.id = "PDM_SJ_Angl_Gal";	//СЖ капитана английского гелеона
    itm.name = "itmname_PDM_SJ_Angl_Gal";
    itm.describe = "itmdescr_PDM_SJ_Angl_Gal";
    itm.picIndex = 8;
    itm.picTexture = "ITEMS_4";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Охота на ведьму"
    itm.id = "PDM_ONV_Kluch";	//Ключ от двери
    itm.name = "itmname_PDM_ONV_Kluch";
    itm.describe = "itmdescr_PDM_ONV_Kluch";
    itm.picIndex = 15;
    itm.picTexture = "ITEMS_12";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Потерянное кольцо"
    itm.id = "PDM_PK_Koltso";	//Кольцо Жозефины Лодет
    itm.name = "itmname_PDM_PK_Koltso";
    itm.describe = "itmdescr_PDM_PK_Koltso";
    itm.picIndex = 6;
    itm.picTexture = "ITEMS_2";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Проклятая жара"
    itm.id = "PDM_PJ_Vino";	//Бутылка вина
    itm.name = "itmname_PDM_PJ_Vino";
    itm.describe = "itmdescr_PDM_PJ_Vino";
    itm.picIndex = 3;
    itm.picTexture = "ITEMS_1";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Проклятая жара"
    itm.id = "PDM_PJ_Rom";	//Бутылка рома
    itm.name = "itmname_PDM_PJ_Rom";
    itm.describe = "itmdescr_PDM_PJ_Rom";
    itm.picIndex = 3;
    itm.picTexture = "ITEMS_1";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]); //квест "Проклятая жара"
    itm.id = "PDM_PJ_BsRL";	//Бутылка с розовой ленточкой
	itm.groupID = IDOLS_RIGHT_ITEM_TYPE;
    itm.name = "itmname_PDM_PJ_BsRL";
    itm.describe = "itmdescr_PDM_PJ_BsRL";
    itm.picIndex = 5;
    itm.picTexture = "ITEMS_20";
	itm.shown = true;
    itm.price = 1000;
    itm.Weight = 0.2;
    itm.ItemType = "QUESTITEMS";
    n++;

	makeref(itm, Items[n]);
    itm.id = "Litsenzia";	//Торговая лицензия
    itm.name = "itmname_Litsenzia";
    itm.describe = "itmdescr_Litsenzia";
    itm.picIndex = 13;
    itm.picTexture = "ITEMS_4";
    itm.price = 0;
    itm.Weight = 0.1;
    itm.ItemType = "QUESTITEMS";
    n++;

	// Билет на арену
	makeref(itm,Items[n]);
	itm.id = "ArenaBilet";
	itm.name = "itmname_ArenaBilet";
	itm.describe = "itmdescr_ArenaBilet";
	itm.model = "1";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_12";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	n++;

	// Листья здоровья
	makeref(itm,Items[n]);
	itm.id = "CompCraft_HealthTobacco";
	itm.name = "itmname_CompCraft_HealthTobacco";
	itm.describe = "itmdescr_CompCraft_HealthTobacco";
	itm.model = "1";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_18";
	itm.price = 2500;
	itm.Weight = 0.01;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Трава энергии
	makeref(itm,Items[n]);
	itm.id = "CompCraft_EnergyTobacco";
	itm.name = "itmname_CompCraft_EnergyTobacco";
	itm.describe = "itmdescr_CompCraft_EnergyTobacco";
	itm.model = "1";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_18";
	itm.price = 2400;
	itm.Weight = 0.01;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Табак силы
	makeref(itm,Items[n]);
	itm.id = "CompCraft_StrengthTobacco";
	itm.name = "itmname_CompCraft_StrengthTobacco";
	itm.describe = "itmdescr_CompCraft_StrengthTobacco";
	itm.model = "1";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_18";
	itm.price = 2300;
	itm.Weight = 0.01;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Гвозди
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Nails";
	itm.name = "itmname_CompCraft_Nails";
	itm.describe = "itmdescr_CompCraft_Nails";
	itm.model = "1";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_14";
	itm.price = 10;
	itm.Weight = 0.05;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Магний
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Magnesium";
	itm.name = "itmname_CompCraft_Magnesium";
	itm.describe = "itmdescr_CompCraft_Magnesium";
	itm.model = "1";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_17";
	itm.price = 50;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Кремень
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Flint";
	itm.name = "itmname_CompCraft_Flint";
	itm.describe = "itmdescr_CompCraft_Flint";
	itm.model = "1";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_17";
	itm.price = 50;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Свинец
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Lead";
	itm.name = "itmname_CompCraft_Lead";
	itm.describe = "itmdescr_CompCraft_Lead";
	itm.model = "1";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_17";
	itm.price = 30;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Медь
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Copper";
	itm.name = "itmname_CompCraft_Copper";
	itm.describe = "itmdescr_CompCraft_Copper";
	itm.model = "1";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_19";
	itm.price = 80;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Сера
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Sulfur";
	itm.name = "itmname_CompCraft_Sulfur";
	itm.describe = "itmdescr_CompCraft_Sulfur";
	itm.model = "1";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_17";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Измельчённая сера
	makeref(itm,Items[n]);
	itm.id = "CompCraft_SulfurCrush";
	itm.name = "itmname_CompCraft_SulfurCrush";
	itm.describe = "itmdescr_CompCraft_SulfurCrush";
	itm.model = "1";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_17";
	itm.price = 10;
	itm.Weight = 0.05;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";

    itm.CraftedItem = "CompCraft_SulfurCrush";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 3;
    itm.ComponentsNum = 1;
    itm.Component1 = "CompCraft_Sulfur";
    itm.Component1Num = 1;
	n++;

	// Пороховая смесь
	makeref(itm,Items[n]);
	itm.id = "CompCraft_PowderMixture";
	itm.name = "itmname_CompCraft_PowderMixture";
	itm.describe = "itmdescr_CompCraft_PowderMixture";
	itm.model = "1";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_17";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";

    itm.CraftedItem = "CompCraft_PowderMixture";
    itm.CraftFor = "Blacksmith";
	itm.ResultNum = 2;
    itm.ComponentsNum = 2;
    itm.Component1 = "CompCraft_SulfurCrush";
    itm.Component1Num = 1;
    itm.Component2 = "CompCraft_Magnesium";
    itm.Component2Num = 1;
	n++;

	// Пергамент
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Parchment";
	itm.name = "itmname_CompCraft_Parchment";
	itm.describe = "itmdescr_CompCraft_Parchment";
	itm.model = "1";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_17";
	itm.price = 10;
	itm.Weight = 0.02;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Оселок
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Grindstone";
	itm.name = "itmname_CompCraft_Grindstone";
	itm.describe = "itmdescr_CompCraft_Grindstone";
	itm.model = "1";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_16";
	itm.price = 100;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Ножницы
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Scissors";
	itm.name = "itmname_CompCraft_Scissors";
	itm.describe = "itmdescr_CompCraft_Scissors";
	itm.model = "1";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_10";
	itm.price = 1000;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Набор инструментов
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Tools";
	itm.name = "itmname_CompCraft_Tools";
	itm.describe = "itmdescr_CompCraft_Tools";
	itm.model = "1";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_16";
	itm.price = 10000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Слесарный набор
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Locksmith";
	itm.name = "itmname_CompCraft_Locksmith";
	itm.describe = "itmdescr_CompCraft_Locksmith";
	itm.model = "1";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_16";
	itm.price = 50000;
	itm.Weight = 5.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Пулелейка
	makeref(itm,Items[n]);
	itm.id = "CompCraft_Puleleyka";
	itm.name = "itmname_CompCraft_Puleleyka";
	itm.describe = "itmdescr_CompCraft_Puleleyka";
	itm.model = "1";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_18";
	itm.price = 50000;
	itm.Weight = 3.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "CRAFTCOMPONENTS";
	n++;

	// Уникальный чертёж
	makeref(itm,Items[n]);
	itm.id = "Ship_Print_6";
	itm.name = "itmname_Ship_Print_6";
	itm.describe = "itmdescr_Ship_Print_6";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_19";
	itm.price = 1000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 50; // Атрибут для магазина ачивок
	n++;

	// Уникальный чертёж
	makeref(itm,Items[n]);
	itm.id = "Ship_Print_5";
	itm.name = "itmname_Ship_Print_5";
	itm.describe = "itmdescr_Ship_Print_5";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_19";
	itm.price = 1000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 100; // Атрибут для магазина ачивок
	n++;

	// Уникальный чертёж
	makeref(itm,Items[n]);
	itm.id = "Ship_Print_4";
	itm.name = "itmname_Ship_Print_4";
	itm.describe = "itmdescr_Ship_Print_4";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_19";
	itm.price = 1000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 400; // Атрибут для магазина ачивок
	n++;

	// Уникальный чертёж
	makeref(itm,Items[n]);
	itm.id = "Ship_Print_3";
	itm.name = "itmname_Ship_Print_3";
	itm.describe = "itmdescr_Ship_Print_3";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_19";
	itm.price = 1000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 900; // Атрибут для магазина ачивок
	n++;

	// Уникальный чертёж
	makeref(itm,Items[n]);
	itm.id = "Ship_Print_2";
	itm.name = "itmname_Ship_Print_2";
	itm.describe = "itmdescr_Ship_Print_2";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_19";
	itm.price = 1000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 1800; // Атрибут для магазина ачивок
	n++;

	// Уникальный чертёж
	makeref(itm,Items[n]);
	itm.id = "Ship_Print_1";
	itm.name = "itmname_Ship_Print_1";
	itm.describe = "itmdescr_Ship_Print_1";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_19";
	itm.price = 1000;
	itm.Weight = 1.0;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	itm.points_shop = 2700; // Атрибут для магазина ачивок
	n++;

	// Бумаги с координатами
	makeref(itm,Items[n]);
	itm.id = "BS_PaperCoord";
	itm.name = "itmname_BS_PaperCoord";
	itm.describe = "itmdescr_BS_PaperCoord";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_20";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	n++;

	// Судовой журнал Флинта
	makeref(itm,Items[n]);
	itm.id = "BS_QBFlint";
	itm.name = "itmname_BS_QBFlint";
	itm.describe = "itmdescr_BS_QBFlint";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_20";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	n++;

	// Марк Аврелий "Размышления"
	makeref(itm,Items[n]);
	itm.id = "BS_MarkAvreliy";
	itm.name = "itmname_BS_MarkAvreliy";
	itm.describe = "itmdescr_BS_MarkAvreliy";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_20";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.ItemType = "QUESTITEMS";
	n++;

	//Для генераторного квеста "Проигравшийся игрок"
	makeref(itm,Items[n]);
	itm.id = "Bag_with_money";
	itm.name = "itmname_Bag_with_money";
	itm.describe = "itmdescr_Bag_with_money";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_20";
	itm.price = 0;
	itm.weight = 0.5;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);	//Квест "Аптекарь"
	itm.id = "PDM_Heal_Poroshok";	//Целебный порошок
	itm.name = "itmname_PDM_Heal_Poroshok";
	itm.describe = "itmdescr_PDM_Heal_Poroshok";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_9";
	itm.price = 0;
	itm.weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);	//Квест "Аптекарь"
	itm.id = "PDM_Derevo_Teshkali";	//Дерево Тешкатали
	itm.name = "itmname_PDM_Derevo_Teshkali";
	itm.describe = "itmdescr_PDM_Derevo_Teshkali";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_7";
	itm.model = "Diamond";
	itm.price = 0;
	itm.weight = 2;
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]);	//Квест "Аптекарь"
	itm.id = "PDM_Trava_Tzes_Umrat";	//Трава Тзескатлат Умтат
	itm.name = "itmname_PDM_Trava_Tzes_Umrat";
	itm.describe = "itmdescr_PDM_Trava_Tzes_Umrat";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_18";
	itm.price = 0;
	itm.weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	n++;

	//InitGunExt(id,	sAttr,  sBullet,  sGunPowder, DmgMin_NC, DmgMax_NC, DmgMin_C, DmgMax_C, EnergyP_NC, EnergyP_C, Stun_NC, Stun_C, MultiDamage, MisFire, SelfDamage, Explosion,Accuracy,ChargeSpeed,isDefault);
	InitGunExt(		 "pistol1", "t1",  	     "cartridge",               "",  20.0, 100.0,  20.0, 100.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 30,  8, 0);
	InitGunExt(		 "pistol1", "t2", 		    "bullet",      "gunpowder",  20.0, 100.0,  30.0, 100.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 30, 16, 1);
	InitGunExt( 	 "pistol2", "t1", 	     "cartridge",     			"",  30.0, 120.0,  30.0, 120.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 12, 0);
	InitGunExt(		 "pistol2", "t2", 		    "bullet",      "gunpowder",  30.0, 120.0,  30.0, 120.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 24, 1);
	InitGunExt(		 "pistol3", "t1", 	     "grapeshot",      "gunpowder",  20.0,  80.0,  40.0,  90.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 20, 24, 1);
	InitGunExt(		 "pistol4", "t1", 	     "cartridge",               "",  40.0, 140.0,  40.0, 140.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 60, 28, 0);
	InitGunExt(		 "pistol4", "t2", 		    "bullet",      "gunpowder",  40.0, 140.0,  40.0, 140.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 60, 56, 1);
	InitGunExt(		 "pistol5", "t1", 	     "cartridge",               "",  45.0, 170.0,  45.0, 170.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 80, 16, 0);
	InitGunExt(		 "pistol5", "t2", 		    "bullet",      "gunpowder",  45.0, 170.0,  45.0, 170.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 80, 32, 1);
	InitGunExt(		 "pistol6", "t1", 	     "cartridge",               "",  35.0, 130.0,  35.0, 130.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 60, 20, 0);
	InitGunExt(		 "pistol6", "t2", 		    "bullet",      "gunpowder",  35.0, 130.0,  35.0, 130.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 60, 40, 1);
	InitGunExt(		 "pistol7", "t1","shotgun_cartridge",   			"", 100.0, 300.0, 100.0, 300.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 80, 52, 1);
	InitGunExt(		 "pistol7shotgun", "t1", "grapeshot",       "12_gauge",  80.0, 200.0,  50.0, 180.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 80, 52, 1);
	InitGunExt(		 "pistol7shotgun", "t2", 	"bullet",       "12_gauge", 100.0, 300.0, 100.0, 300.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 80, 52, 0);
	InitGunExt(		 "pistol8", "t1", 	     "grapeshot",      "gunpowder",  50.0, 100.0,  50.0, 100.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 50, 20, 1);
	InitGunExt(		 "pistol8", "t2", 		   "harpoon",      "gunpowder", 150.0, 250.0, 150.0, 250.0,  20.0, 20.0,0, 1, 0, 0, 0, 0, 20, 35, 0);
	InitGunExt(		 "pistol8", "t3", 		  "GunEchin",               "", 120.0, 220.0, 120.0, 220.0,  20.0, 20.0,0, 1, 1, 0, 0, 0, 20, 30, 0);
	InitGunExt(		 "pistol9", "t1", 	     "cartridge",               "",  50.0, 160.0,  40.0, 140.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 25, 0);
	InitGunExt(		 "pistol9", "t2", 		    "bullet",      "gunpowder",  50.0, 160.0,  40.0, 140.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 50, 1);
	InitGunExt( 	 "pistol_grapebok", "t1","grapeshot",      "gunpowder",  30.0, 110.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 40, 1);
	InitGunExt(		 "howdah", "t1",         "grapeshot",      "gunpowder",  50.0,  85.0,  40.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 40, 1);
    InitGunExt(		 "howdah", "t2",          "GunEchin",               "", 115.0, 215.0, 115.0, 215.0,  20.0, 20.0,0, 1, 1, 0, 0, 0, 20, 60, 0);

	InitGunExt(		"mushket", "t1", 	             "cartridge",               "", 100.0, 150.0, 100.0, 150.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  20, 0);
	InitGunExt(		"mushket", "t2", 		            "bullet",      "gunpowder", 100.0, 150.0, 100.0, 150.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  40, 1);
	InitGunExt(		"mushket2", "t1", 	             "cartridge",               "", 140.0, 240.0, 140.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  90,  35, 0);
	InitGunExt(		"mushket2", "t2", 		            "bullet",      "gunpowder", 140.0, 240.0, 140.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  90,  55, 1);
	InitGunExt(		"mushket_spanish", "t1", 	     "cartridge",               "",  60.0, 180.0,  60.0, 180.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 100,  30, 0);
	InitGunExt(		"mushket_spanish", "t2", 		    "bullet",      "gunpowder",  60.0, 180.0,  60.0, 180.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 100,  60, 1);
	InitGunExt(		"mushket_english", "t1", 	     "cartridge",               "",  40.0, 170.0,  40.0, 170.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  75,  16, 0);
	InitGunExt(		"mushket_english", "t2", 		    "bullet",      "gunpowder",  40.0, 170.0,  40.0, 170.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  75,  32, 1);
	InitGunExt(		"mushket_france", "t1", 	     "cartridge",               "", 150.0, 290.0, 150.0, 290.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  40, 0);
	InitGunExt(		"mushket_france", "t2", 		    "bullet",      "gunpowder", 150.0, 290.0, 150.0, 290.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  80, 1);
	InitGunExt(		"mushket_holland", "t1", 	     "cartridge",               "", 140.0, 240.0, 140.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  70,  30, 0);
	InitGunExt(		"mushket_holland", "t2", 		    "bullet",      "gunpowder", 140.0, 240.0, 140.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  70,  60, 1);
	InitGunExt(		"mushket_SeaCarbine", "t1", 	 "cartridge", 		        "", 135.0, 235.0, 135.0, 235.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  30, 0);
	InitGunExt(		"mushket_SeaCarbine", "t2", 		"bullet",  	   "gunpowder", 135.0, 235.0, 135.0, 235.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  50, 1);
	InitGunExt(		"mushket2x2", "t1", 	         "cartridge",               "",  90.0, 290.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  12, 0);
	InitGunExt(		"mushket2x2", "t2", 		        "bullet",  	   "gunpowder",  90.0, 290.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  80,  24, 1);
	InitGunExt(		"mushket_Shtuzer", "t1", 	     "cartridge",               "", 200.0, 300.0, 200.0, 300.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 100,  40, 0);
	InitGunExt(		"mushket_Shtuzer", "t2", 		    "bullet",      "gunpowder", 200.0, 300.0, 200.0, 300.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 100,  60, 1);
	InitGunExt(		"mushket_drob", "t1", 	         "grapeshot",      "gunpowder",  60.0, 100.0,  70.0, 120.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1,  35,  25, 0);
	InitGunExt(		"mushket_drob", "t2", 	         "cartridge",               "",  50.0, 130.0,  60.0, 110.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  70,  12, 0);
	InitGunExt(		"mushket_drob", "t3", 		        "bullet",      "gunpowder",  60.0, 130.0,  60.0, 110.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0,  60,  20, 1);
	InitGunExt(		"grape_mushket", "t1", 	           "grenade",           	"", 100.0, 200.0,  80.0, 180.0, 10.0, 10.0, 1, 1, 1, 0, 1, 1, 100,  50, 1);
	InitGunExt(		"grape_mushket", "t2",       "powder_pellet",          		"",  15.0, 115.0,   5.0, 105.0,100.0, 80.0, 1, 1, 1, 0, 1, 1, 100,  50, 0);
	InitGunExt(		"mushket6", "t1", 	             "grapeshot",      "gunpowder",  90.0, 100.0,  50.0, 100.0, 20.0, 20.0, 1, 1, 1, 0, 0, 1,  70,  50, 1);
	InitGunExt(		"mushket6", "t2", 	              "GunEchin",               "", 115.0, 180.0,  65.0, 115.0, 20.0, 20.0, 1, 1, 1, 0, 0, 1,  60,  45, 0);
	InitGunExt(		"mushket_seadevil", "t1","shotgun_cartridge", 				"", 200.0, 375.0, 200.0, 375.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 100,  65, 1);

	trace("Всего предметов (размерность массива) "+n);
	trace("Всего заскриптованных предметов - " + iScriptItemCount);
	trace("Начальный специальный предмет: " + Items[ItemsForLocators_start].id);
	trace("Конечный специальный предмет: " + Items[ItemsForLocators_end].id);
	return n;
}

void InitGunExt(string id,
				string sAttr,
				string sBullet,
				string sGunPowder,
				float  DmgMin_NC,
				float  DmgMax_NC,
				float  DmgMin_C,
				float  DmgMax_C,
				float  EnergyP_NC,
				float  EnergyP_C,
				bool   Stun_NC,
				bool   Stun_C,
				bool   MultiDamage,
				int    MisFire,
				bool   SelfDamage,
				bool   Explosion,
				float  Accuracy,
				int    ChargeSpeed,
				bool   isDefault )
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).bullet 		= sBullet;
	gun.type.(sAttr).gunpowder 		= sGunPowder;
	gun.type.(sAttr).DmgMin_NC		= DmgMin_NC;
	gun.type.(sAttr).DmgMax_NC		= DmgMax_NC;
	gun.type.(sAttr).DmgMin_C		= DmgMin_C;
	gun.type.(sAttr).DmgMax_C		= DmgMax_NC;
	gun.type.(sAttr).EnergyP_NC		= EnergyP_NC;
	gun.type.(sAttr).EnergyP_C		= EnergyP_C;
	gun.type.(sAttr).Stun_NC		= Stun_NC;
	gun.type.(sAttr).Stun_C			= Stun_C;
	gun.type.(sAttr).multidmg       = MultiDamage;
	gun.type.(sAttr).misfire        = MisFire;
	gun.type.(sAttr).SelfDamage     = SelfDamage;
	gun.type.(sAttr).Explosion      = Explosion;
	gun.type.(sAttr).Accuracy       = Accuracy;
	gun.type.(sAttr).ChargeSpeed    = ChargeSpeed;
	gun.type.(sAttr).Default        = isDefault;

	if(Stun_NC || Stun_C) gun.stun = true;
}

// Warship 24.10.08 ГПК 1.2.3 Рандом статов холодного оружия
// Рудмент - нигде не используется
void SetRandomBladesStates()
{
	/*int iDamageMin, iDamageMax;
	ref rItem;

	for(int i=0; i<ITEMS_QUANTITY; i++)
	{
		rItem = &items[i];

		if(GetAttrValue(rItem, "groupID") == BLADE_ITEM_TYPE) // Значит холодное оружие
		{
			// Новые значения
			iDamageMin = sti(rItem.dmg_min) - rand(MakeInt(sti(rItem.dmg_min)/3)) + rand(MakeInt(sti(rItem.dmg_min)/3));
			iDamageMax = sti(rItem.dmg_max) - rand(MakeInt(sti(rItem.dmg_max)/2)) + rand(MakeInt(sti(rItem.dmg_max)/2));

			// Запомним прежние
			rItem.dmg_min.old = rItem.dmg_min;
			rItem.dmg_max.old = rItem.dmg_max;

			rItem.dmg_min = iDamageMin;
			rItem.dmg_max = iDamageMax;
		}
	}*/
}

void InitButtons()
{
	/*aref lab3;
	makearef(lab3, Locations[FindLocation("Labirint_3")]);

	lab3.items.b_1.locator = "button01";
	lab3.items.b_1.model   = "b1";
	lab3.items.b_1.itemDeltaY  = 0.0;
	lab3.items.b_1.deltaY  = -0.05;
	lab3.items.b_1.trigged  = false;
	*/
}

void InitRandItems()
{
	ref rnditem;
	int n = 0;
	int i;

	// --------> зелья
    makeref(rnditem,RandItems[n]);
	rnditem.id = "potion1";
	rnditem.maxQuantity = 8;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "potion2";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "potion3";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "potion4";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "potion5";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "potionwine";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "potionrum";
	rnditem.maxQuantity = 4;
	n++;
	// <--------

	// --------> еда
    makeref(rnditem,RandItems[n]);
	rnditem.id = "Food1";
	rnditem.maxQuantity = 5;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Food2";
	rnditem.maxQuantity = 5;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Food3";
	rnditem.maxQuantity = 5;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Food4";
	rnditem.maxQuantity = 5;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Food5";
	rnditem.maxQuantity = 5;
	n++;
	// <--------

	// --------> боеприпасы
    makeref(rnditem,RandItems[n]);
	rnditem.id = "bullet";
	rnditem.maxQuantity = 20;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "GunPowder";
	rnditem.maxQuantity = 20;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "grapeshot";
	rnditem.maxQuantity = 20;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "cartridge";
	rnditem.maxQuantity = 8;
	n++;
	// <--------

	// --------> компоненты крафта (включая гарпун)
    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Nails";
	rnditem.maxQuantity = 7;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Magnesium";
	rnditem.maxQuantity = 15;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Flint";
	rnditem.maxQuantity = 10;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Lead";
	rnditem.maxQuantity = 25;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Copper";
	rnditem.maxQuantity = 6;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Sulfur";
	rnditem.maxQuantity = 25;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Parchment";
	rnditem.maxQuantity = 25;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "slave_01";
	rnditem.maxQuantity = 10;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "CompCraft_Grindstone";
	rnditem.maxQuantity = 10;
	n++;
	// <--------

	// --------> хлам
    makeref(rnditem,RandItems[n]);
	rnditem.id = "mineral3";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Mineral4";
	rnditem.maxQuantity = 1;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Mineral5";
	rnditem.maxQuantity = 1;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Mineral6";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Mineral7";
	rnditem.maxQuantity = 1;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Mineral9";
	rnditem.maxQuantity = 2;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "Mineral10";
	rnditem.maxQuantity = 2;
	n++;
	// <--------

	// --------> драгоценности
    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry1";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry2";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry3";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry5";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry6";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry7";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry10";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry11";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry12";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry13";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry16";
	rnditem.maxQuantity = 15;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry17";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "jewelry18";
	rnditem.maxQuantity = 4;
	n++;
	// <--------

	// --------> экипировка
	for (i = 1; i <= 8; i++)
	{
		makeref(rnditem,RandItems[n]);
		rnditem.id = "blade" + i;
		rnditem.maxQuantity = 1;
		n++;
	}

	for (i = 1; i <= 3; i++)
	{
		makeref(rnditem,RandItems[n]);
		rnditem.id = "pistol" + i;
		rnditem.maxQuantity = 1;
		n++;
	}

	for (i = 1; i <= 2; i++)
	{
		makeref(rnditem,RandItems[n]);
		rnditem.id = "spyglass" + i;
		rnditem.maxQuantity = 1;
		n++;
	}
	// <--------

	// --------> идолы
    makeref(rnditem,RandItems[n]);
	rnditem.id = "indian4";
	rnditem.maxQuantity = 5;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "indian13";
	rnditem.maxQuantity = 4;
	n++;

    makeref(rnditem,RandItems[n]);
	rnditem.id = "indian16";
	rnditem.maxQuantity = 1;
	n++;
	// <--------
}
