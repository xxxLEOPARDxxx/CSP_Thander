
int LocationInitSentMartin(int n)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "SentMartin";

	locations[n].townsack = "Marigo";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";

	locations[n].filespath.models = "locations\Town_StMartin\Town\";
	locations[n].image = "loading\Town_"+rand(8)+".tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	locations[n].questSeekCap = 5;
	//Sound
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].models.always.town = "StMartin";
	locations[n].models.always.town.sea_reflection = 1;
 	locations[n].models.always.L1 = "StMartin_palms";
 	locations[n].models.always.L2 = "StMartin_flora";
	locations[n].models.always.locators = "StMartin_locators";
	locations[n].models.always.seabed = "StMartin_sb";
	locations[n].models.always.grassPatch = "StMartin_grass";

	locations[n].models.always.plan = "plan1";
//	locations[n].models.always.plan.level = 9;

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.1;

	//Day
 	locations[n].models.day.fonar = "StMartin_fd";
	locations[n].models.day.charactersPatch = "StMartin_patch_day";
	locations[n].models.day.rinok = "StMartin_rinok";
	Locations[n].models.day.jumpPatch = "StMartin_jump";
	//Night
 	locations[n].models.night.fonar = "StMartin_fn";
	locations[n].models.night.charactersPatch = "StMartin_patch_night";
	locations[n].models.night.rinok = "StMartin_rinokN";
	Locations[n].models.night.jumpPatch = "StMartin_jump";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l0.name = "reload1";
	locations[n].reload.l0.go = "SentMartin";
	locations[n].reload.l0.emerge = "reload_1";
	locations[n].reload.l0.autoreload = "0";
	locations[n].reload.l0.label = "Sea";
	locations[n].locators_radius.reload.reload1 = 5.0;

	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SentMartin";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "SentMartin";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 12;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Marigo_townhall";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.lR1.name = "reloadR2";
	locations[n].reload.lR1.go = "Marigo_townhall";
	locations[n].reload.lR1.emerge = "reload3";
	locations[n].reload.lR1.autoreload = "0";
	locations[n].reload.lR1.label = "Residence";
	locations[n].reload.lR1.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Marigo_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Marigo_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Marigo_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

//	locations[n].reload.l61.name = "reload61";
//	locations[n].reload.l61.go = "Marigo_store";
//	locations[n].reload.l61.emerge = "reload2";
//	locations[n].reload.l61.autoreload = "0";
//	locations[n].reload.l61.label = "Store";
//	locations[n].reload.l61.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Marigo_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	//locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Marigo_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "Marigo_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

 	locations[n].reload.l91.name = "reload91";
	locations[n].reload.l91.go = "Marigo_SecBrRoom";
	locations[n].reload.l91.emerge = "reload2";
	locations[n].reload.l91.autoreload = "0";
	locations[n].reload.l91.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Marigo_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate";
	locations[n].reload.gate.go = "Marigo_ExitTown";
	locations[n].reload.gate.emerge = "reload5";
	locations[n].reload.gate.autoreload = "1";
	locations[n].reload.gate.label = "ExitTown";
	locations[n].locators_radius.reload.gate = 8.1;

    // --> Штаб квартира ГВИК
	locations[n].reload.l11.name = "HouseO1";
	locations[n].reload.l11.go = "GVIK";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "GWIK";
	locations[n].reload.l11.close_for_night = 1;

	locations[n].reload.l12.name = "HouseO2";
	locations[n].reload.l12.go = "GVIK";
	locations[n].reload.l12.emerge = "reload2";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "GWIK";
	locations[n].reload.l12.close_for_night = 1;

    // --> Квестовые локации.
	locations[n].reload.l13.name = "houseF1";
	locations[n].reload.l13.go = "Marigo_houseF1";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "House";

	locations[n].reload.l14.name = "Hut3";
	locations[n].reload.l14.go = "Hut3_Kns";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "Hut";

	locations[n].reload.l15.name = "houseK2";
	locations[n].reload.l15.go = "Smallhome_K2";
	locations[n].reload.l15.emerge = "reload1";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";

  // --> Псевдо локации для всегда запертых дверей.
	locations[n].reload.l16.name = "houseK2a";
	locations[n].reload.l16.go = "Smallhome_K2";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";
	locations[n].reload.l16.disable = 1;

	locations[n].reload.l17.name = "Hut4";
	locations[n].reload.l17.go = "Hut3_Kns";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "Hut";
	locations[n].reload.l17.disable = 1;

	locations[n].reload.l18.name = "houseS3";
	locations[n].reload.l18.go = "Hut3_Kns";
	locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "House";
	locations[n].reload.l18.disable = 1;

	locations[n].reload.l19.name = "houseB5";
	locations[n].reload.l19.go = "BigHouseKNS";
	locations[n].reload.l19.emerge = "reload3";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "House";
	locations[n].reload.l19.disable = 1;


    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseSp1";
	locations[n].reload.l20.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l21.name = "houseSp2";
	locations[n].reload.l21.go = "CommonRoom_MH7";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";

	locations[n].reload.l22.name = "houseS1";
	locations[n].reload.l22.go = "CommonPirateHouse";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseS2";
	locations[n].reload.l23.go = "CommonFlamHouse";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseS4";
	locations[n].reload.l24.go = "CommonPirateHouse";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";

	locations[n].reload.l25.name = "houseH1";
	locations[n].reload.l25.go = "CommonRoom_MH3";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";

	locations[n].reload.l26.name = "houseH2";
	locations[n].reload.l26.go = "CommonRoom_MH2";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";

	locations[n].reload.l27.name = "houseH3";
	locations[n].reload.l27.go = "StM_Hut";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";

	locations[n].reload.l28.name = "houseH4";
	locations[n].reload.l28.go = "StM_Hut";
	locations[n].reload.l28.emerge = "reload2";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "House";

	locations[n].reload.l29.name = "houseH5";
	locations[n].reload.l29.go = "CommonRoom_MH9_2";
	locations[n].reload.l29.emerge = "reload1";
	locations[n].reload.l29.autoreload = "0";
	locations[n].reload.l29.label = "House";

	locations[n].reload.l30.name = "houseH6";
	locations[n].reload.l30.go = "CommonRoom_MH9";
	locations[n].reload.l30.emerge = "reload1";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "House";

	locations[n].reload.l31.name = "Hut5";
	locations[n].reload.l31.go = "CommonHut";
	locations[n].reload.l31.emerge = "reload1";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l31.label = "Hut";

	locations[n].reload.l32.name = "houseB1";
	locations[n].reload.l32.go = "BigHouseKNS";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "House";

	locations[n].reload.l33.name = "houseB2";
	locations[n].reload.l33.go = "BigHouseKNS";
	locations[n].reload.l33.emerge = "reload2";
	locations[n].reload.l33.autoreload = "0";
	locations[n].reload.l33.label = "House";

	locations[n].reload.l34.name = "houseB3";
	locations[n].reload.l34.go = "BigHouseKNS";
	locations[n].reload.l34.emerge = "reload3";
	locations[n].reload.l34.autoreload = "0";
	locations[n].reload.l34.label = "House";

	locations[n].reload.l35.name = "houseB4";
	locations[n].reload.l35.go = "BigHouseKNS";
	locations[n].reload.l35.emerge = "reload3";
	locations[n].reload.l35.autoreload = "0";
	locations[n].reload.l35.label = "House";
	locations[n].reload.l35.disable = 1; // Закроем на совсем

	locations[n].reload.l36.name = "houseRs1";
	locations[n].reload.l36.go = "ResidencePKM";
	locations[n].reload.l36.emerge = "reload1";
	locations[n].reload.l36.autoreload = "0";
	locations[n].reload.l36.label = "House";

	locations[n].reload.l37.name = "houseRs2";
	locations[n].reload.l37.go = "ResidencePKM";
	locations[n].reload.l37.emerge = "reload1";
	locations[n].reload.l37.autoreload = "0";
	locations[n].reload.l37.label = "House";
	locations[n].reload.l37.disable = 1; // Закроем на совсем

	locations[n].reload.l38.name = "houseM1";
	locations[n].reload.l38.go = "CommonRoom_MH";
	locations[n].reload.l38.emerge = "reload1";
	locations[n].reload.l38.autoreload = "0";
	locations[n].reload.l38.label = "House";

	locations[n].reload.l39.name = "houseM2";
	locations[n].reload.l39.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l39.emerge = "reload1";
	locations[n].reload.l39.autoreload = "0";
	locations[n].reload.l39.label = "House";

	locations[n].reload.l40.name = "houseM3";
	locations[n].reload.l40.go = "CommonRoom_MH";
	locations[n].reload.l40.emerge = "reload1";
	locations[n].reload.l40.autoreload = "0";
	locations[n].reload.l40.label = "House";

	locations[n].reload.l41.name = "houseM4";
	locations[n].reload.l41.go = "CommonRoom_MH5";
	locations[n].reload.l41.emerge = "reload1";
	locations[n].reload.l41.autoreload = "0";
	locations[n].reload.l41.label = "House";

	locations[n].reload.l42.name = "houseM5";
	locations[n].reload.l42.go = "CommonRoom_MH10";
	locations[n].reload.l42.emerge = "reload1";
	locations[n].reload.l42.autoreload = "0";
	locations[n].reload.l42.label = "House";

	locations[n].reload.l43.name = "houseRs2";
	locations[n].reload.l43.go = "ResidencePKM";
	locations[n].reload.l43.emerge = "reload1";
	locations[n].reload.l43.autoreload = "0";
	locations[n].reload.l43.label = "House";
	locations[n].reload.l43.disable = 1; // Закроем на совсем

	locations[n].reload.l44.name = "houseRs3";
	locations[n].reload.l44.go = "ResidencePKM";
	locations[n].reload.l44.emerge = "reload1";
	locations[n].reload.l44.autoreload = "0";
	locations[n].reload.l44.label = "House";
	locations[n].reload.l44.disable = 1; // Закроем на совсем

	locations[n].reload.l45.name = "reloadR1";
	locations[n].reload.l45.go = "CommonResidence_2";
	locations[n].reload.l45.emerge = "reload1";
	locations[n].reload.l45.autoreload = "0";
	locations[n].reload.l45.label = "House";

	locations[n].reload.l46.name = "reload33";
	locations[n].reload.l46.go = "Marigo_Jungle_03";
	locations[n].reload.l46.emerge = "reload1";
	locations[n].reload.l46.autoreload = "1";
	locations[n].reload.l46.label = "House";
	locations[n].locators_radius.reload.reload33 = 3.5;

	locations[n].reload.l47.name = "houseFa1";
	locations[n].reload.l47.go = "Farmacia";
	locations[n].reload.l47.emerge = "reload1";
	locations[n].reload.l47.autoreload = "0";
	locations[n].reload.l47.label = "House";
	locations[n].reload.l47.disable = true;

	locations[n].reload.l48.name = "houseFa2";
	locations[n].reload.l48.go = "Farmacia";
	locations[n].reload.l48.emerge = "reload2";
	locations[n].reload.l48.autoreload = "0";
	locations[n].reload.l48.label = "House";
	locations[n].reload.l48.disable = 1; // Вход будет только со двора

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern03\";
	locations[n].image = "loading\inside\Tavern_"+rand(7)+".tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.tavern = "tavern03";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "tavern03_locators";
	locations[n].models.always.window = "tavern03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern03_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern03_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_tavern_upstairs";
	locations[n].id.label = "Marigo_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].image = "loading\inside\TavernCommon.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store04\";
	locations[n].image = "loading\inside\shop_"+rand(3)+".tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Store04_locators";
	locations[n].models.always.store = "Store04";
	locations[n].models.always.window = "store04_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Store04_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store04_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РОСТОВЩИК
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\Bank01\";
	locations[n].image = "loading\inside\bank_"+rand(3)+".tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Bank01_locators";
	locations[n].models.always.store = "Bank01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Bank01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Bank01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Bank01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_5";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ВЕРФЬ //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard03\";
	locations[n].image = "loading\inside\Shipyard_"+rand(4)+".tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Shipyard03_locators";
	locations[n].models.always.shipyard = "Shipyard03";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Shipyard03_patch";
	//Night
    locations[n].models.night.charactersPatch = "Shipyard03_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РЕЗИДЕНЦИЯ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence01";
	locations[n].image = "loading\inside\residence_2.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Residence01_locators";
	locations[n].models.always.l1 = "Residence01";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Residence01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Residence01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "reloadR2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Marigo_TownhallRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "TownhallRoom";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_TownhallRoom"; //кабинет
	locations[n].id.label = "TownhallRoom";
	locations[n].image = "loading\inside\CommonResidence_4.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Always
	locations[n].filespath.models = "locations\Inside\BigHouse04";
	locations[n].models.always.house = "BigHouse04";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse04_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse04_patch";
	locations[n].models.day.locators = "BigHouse04_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse04_patch";
	locations[n].models.night.locators = "BigHouse04_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_townhall";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Residence";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall_"+rand(3)+".tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_locators";
	locations[n].models.always.store = "Brothel";
	locations[n].models.always.window = "brothel_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Marigo_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room_0.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_room_locators";
	locations[n].models.always.store = "Brothel_room";
	locations[n].models.always.window = "Brothel_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_SecBrRoom"; // вторая комната борделя
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\CommonResidence_3.tga";
 	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse03\";
	locations[n].models.always.house = "BigHouse03";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse03_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse03_patch";
	locations[n].models.day.locators = "BigHouse03_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse03_patch";
	locations[n].models.night.locators = "BigHouse03_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "reload91";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_church";
	locations[n].id.label = "Church";
	locations[n].filespath.models = "locations\inside\Church01";
	locations[n].image = "loading\inside\Church01.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "Church01_locators";
	locations[n].models.always.tavern = "Church01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Church01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Church01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Church01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\PortOffice";
	locations[n].models.always.housePortOffice = "PortOffice";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "PortOffice_locators";

	Locations[n].models.always.PortOffice = "PortOffice_windows";
	Locations[n].models.always.PortOffice.tech = "LocationWindows";
	locations[n].models.always.PortOffice.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "PortOffice_patch";
	//Night
	locations[n].models.night.charactersPatch = "PortOffice_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом в Мариго, houseF1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_houseF1";
	locations[n].filespath.models = "locations\inside\StoneHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\stonehouse.tga.tx";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.tavern = "StoneHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "StoneHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "StoneHouse_locators";
	locations[n].models.night.locators = "StoneHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "StoneHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "StoneHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseF1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_RoomHouseF1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_RoomHouseF1";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\CommonRoom_MH5.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse05";
	locations[n].models.always.mediumhouse05 = "mediumhouse05";
	locations[n].models.always.mediumhouse05.level = 65538;
	locations[n].models.day.locators = "mediumhouse05_locators";
	locations[n].models.night.locators = "mediumhouse05_Nlocators";

	Locations[n].models.always.mediumhouse05windows = "mediumhouse05_windows";
	Locations[n].models.always.mediumhouse05windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse05windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse05rand= "mediumhouse05_rand";
	locations[n].models.day.charactersPatch = "mediumhouse05_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse05_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_houseF1";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	n = n + 1;


//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Штаб-квартира ГВИК
//////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "GVIK";
	locations[n].id.label = "GWIKshort";
	locations[n].image = "loading\inside\smallresidence.tga";
	locations[n].HWIC = true;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	locations[n].filespath.models = "locations\inside\office";
	//Always
	locations[n].models.always.office = "office";
	locations[n].models.always.office.level = 65538;
	locations[n].models.always.window = "office_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "office_locators";
	locations[n].models.day.charactersPatch = "office_patch";
	//Night
	locations[n].models.night.locators = "office_Nlocators";
	locations[n].models.night.charactersPatch = "office_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "HouseO1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "HouseO2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "GVIK";
	locations[n].reload.l3.emerge = "reload3";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "House";
	locations[n].reload.l3.disable  = true; //Закрыт, типа там ещё много всякого, но нас туды не пускают

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Marigo_houseH2";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "residence";
//	locations[n].reload.l4.disable  = true; //дом закрыт до нужного момента
	n = n + 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом представителя Голландской Вест-Индской компании
//////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_houseH2";
	locations[n].id.label = "Townhall ";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	locations[n].noFight = true; //до поры не даем тут драться
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallResidence";
	locations[n].models.always.locators = "SmallResidence_locators";
	locations[n].models.always.house = "SmallResidence";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "SmallResidence_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SmallResidence_patch";
	//Night
	locations[n].models.night.charactersPatch = "SmallResidence_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "GVIK";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.item.item1 = 0.9;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина у пирса с двумя входами
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "StM_Hut";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonHut.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "";
	//Models
	//Always
	locations[n].models.always.locators = "Hut_locators";
	locations[n].models.always.tavern = "Hut";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseH3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "houseH4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Средний дом 9 с заменённой стенкой
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "CommonRoom_MH9_2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonRoom_MH9.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse09_2";
	locations[n].models.always.house = "mediumhouse09";
	locations[n].models.always.house.level = 65538;
	locations[n].models.day.locators = "mediumhouse09_locators";
	locations[n].models.night.locators = "mediumhouse09_Nlocators";

	Locations[n].models.always.mediumhouse09windows = "mediumhouse09_windows";
	Locations[n].models.always.mediumhouse09windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse09windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse09rand= "mediumhouse09_rand";
	locations[n].models.day.charactersPatch = "mediumhouse09_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse09_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseH5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Хижина с камином (NikK)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hut3_Kns";
	locations[n].filespath.models = "locations\inside\Hut3";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonHut.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "";
	//Models
	//Always
	locations[n].models.always.locators = "Hut3_locators";
	locations[n].models.always.tavern = "Hut3";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut3_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut3_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "none";
	locations[n].reload.l1.autoreload = "Hut3";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Маленький дом из ПКМ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Smallhome_K2";
	locations[n].filespath.models = "locations\inside\Smallhome";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonHut.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "";
	//Models
	//Always
	locations[n].models.always.locators = "SH_l";
	locations[n].models.always.tavern = "SH";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "SH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SH_p";
	//Night
	locations[n].models.night.charactersPatch = "SH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "houseK2";
	locations[n].reload.l1.emerge = "Marigo_town";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Дом с 4 дверьми (NikK)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "BigHouseKNS";
 	locations[n].id.label = "House";
	locations[n].image = "loading\inside\BigHouseBack.tga";
 	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse06\";
	locations[n].models.always.house = "BigHouse06";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse06_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.locators = "BigHouse06_locators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse06_patch";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse06_patch";
	locations[n].models.night.locators = "BigHouse06_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseB1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "houseB2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Marigo_town";
	locations[n].reload.l3.emerge = "houseB3";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маленькая резиденция из ПКМ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "ResidencePKM";
	locations[n].filespath.models = "locations\inside\residence_PKM";
	locations[n].id.label = "Residence";
	locations[n].image = "loading\inside\smallresidence.tga";
	//locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.locators = "ResP_locators_x";
	locations[n].models.always.tavern = "ResP";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "ResP_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "ResP_patch";
	//Night
	locations[n].models.night.charactersPatch = "ResP_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseRs1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Аптека (NikK)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Farmacia";
	locations[n].filespath.models = "locations\inside\Farmacia1";
	locations[n].id.label = "Apteka";
	locations[n].image = "loading\inside\smallresidence.tga";
	//locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "House";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].models.always.office = "Farmacia";
	locations[n].models.always.office.level = 65538;
 	locations[n].models.always.L1 = "Farmacia_back";
 	locations[n].models.always.L2 = "Farmacia_lamp";
	locations[n].models.always.window = "Farmacia_glas";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.locators = "Farmacia_locators";
	//Day
	locations[n].models.day.charactersPatch = "patch";
	//Night
	locations[n].models.night.charactersPatch = "patch";
	locations[n].models.night.L3 = "Farmacia_locatorsN";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseFa1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "houseFa2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "CommonRoom_MH3";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "House";
	locations[n].reload.l3.disable = 1; // Закроем на совсем

//	locations[n].private1.key = "keyA";
	locations[n].private1.money = 2300;
	locations[n].private1.items.indian22 = 1;
	locations[n].private1.items.potion4 = 8;
	locations[n].private1.items.potion3 = 1;
	locations[n].private1.items.book2_12 = 1;
	n = n + 1;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Marigo_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Town sack
	locations[n].townsack = "PortPax";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	locations[n].islandIdAreal = "Marigo";
    //Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitT";
	Locations[n].models.always.townExit = "townExitT";

	Locations[n].models.always.locators = "townExitT_KNS_locators";

	Locations[n].models.always.grassPatch = "townExitT_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	locations[n].models.always.l4 = "plan_KNS";
	//Day
	locations[n].models.day.charactersPatch = "townExitT_KNS_patch";
	locations[n].models.day.fonars = "townExitT_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitT_KNS_patch";
	locations[n].models.night.fonars = "townExitT_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload5_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Marigo";
	locations[n].locators_radius.reload.reload5_back = 3.0;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Marigo_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Marigo_fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Marigo Fort";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt1";
	Locations[n].models.always.caveEnt1 = "caveEnt1";
	Locations[n].models.always.locators = "caveEnt1_locators";
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_Cave";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_jungle_01";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_Cave";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\Cave_"+(rand(1)+1)+".tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium2";
	locations[n].models.always.cavernMedium2 = "cavernMedium2";
	locations[n].models.always.lamps = "cavernMedium2_lamps";
	locations[n].models.always.locators = "cavernMedium2_locators";

	locations[n].locators_radius.item.duhi1 = 1.3;

	Locations[n].models.always.rays = "cavernMedium2_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium2_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium2_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].locators_radius.reload.reload1 = 2.0;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_Jungle_02";
	locations[n].reload.l2.emerge = "reloadW";
	locations[n].locators_radius.reload.reload2 = 2.0;
	locations[n].locators_radius.item.berglar1 = 3.5;
	locations[n].locators_radius.item.CheckReload1 = 3.5;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Marigo_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle4";
	Locations[n].models.always.jungle = "jungle4";
	Locations[n].models.always.locators = "jungle4_locators";
	Locations[n].models.always.grassPatch = "jungle4_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle4_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle4_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_jungle_02";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Marigo_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle2";
	Locations[n].models.always.jungle = "jungle2";
	Locations[n].models.always.locators = "jungle2_lSentMartin02";
	Locations[n].models.always.grassPatch = "jungle2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";

	locations[n].models.always.well_small = "well_big";
	Locations[n].models.always.well_small.locator.group = "reload";
	Locations[n].models.always.well_small.locator.name ="reloadW_back";
	Locations[n].models.always.well_small.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle2_pSentMartin02";
	//Night
	locations[n].models.night.charactersPatch = "jungle2_pSentMartin02";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_jungle_04";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore40";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore40";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Marigo_jungle_01";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;

	locations[n].reload.l4.name = "reloadW_back";
	locations[n].reload.l4.go = "Marigo_Cave";
	locations[n].reload.l4.emerge = "reload2";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Jungle";
	locations[n].locators_radius.reload.reloadW_back = 2.3;
	n = n + 1;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли (сквозной пролёт)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle10";
	Locations[n].models.always.jungle = "jungle10";
	Locations[n].models.always.locators = "jungle10_locators";
	Locations[n].models.always.grassPatch = "jungle10_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle10_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle10_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload33_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_jungle_04";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;
	n = n + 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Marigo_jungle_04";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle6";
	Locations[n].models.always.jungle = "jungle6";
	Locations[n].models.always.locators = "jungle6_locators";
	Locations[n].models.always.grassPatch = "jungle6_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle6_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle6_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_Jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_Jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Shore41";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Shore41";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж41
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore41";
	locations[n].id.label = "Shore41";
	locations[n].image = "loading\outside\harbor_" + rand(14) + ".tga";
	locations[n].worldmap = "Shore41";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore07";
	Locations[n].models.always.shore07 = "shore07";
	locations[n].models.always.shore07.sea_reflection = 1;
	Locations[n].models.always.shore07seabed = "shore07_sb";
	Locations[n].models.always.locators = "shore07_locators";

	Locations[n].models.always.grassPatch = "shore07_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "shore07_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore07_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_Jungle_04";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "SentMartin";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
        locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж40
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore40";
	locations[n].id.label = "Shore40";
	locations[n].image = "loading\outside\harbor_" + rand(14) + ".tga";
	locations[n].worldmap = "Shore40";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "SentMartin";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore08";
	Locations[n].models.always.shore08 = "shore08";
	locations[n].models.always.shore08.sea_reflection = 1;
	Locations[n].models.always.shore08seabed = "shore08_sb";
	Locations[n].models.always.locators = "shore08_locators";
	Locations[n].models.always.grassPatch = "shore08_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "shore08_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore08_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_Jungle_02";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "SentMartin";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
        locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	return n;
}
