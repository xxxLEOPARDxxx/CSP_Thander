

int LocationInitQuestLocations(int n)
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Локация клон
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Clone_location";
	locations[n].id.label = "Farm Field";
	locations[n].filespath.models = "locations\";
	locations[n].image = "loading\Farmfield.tga";
	//Sound
	locations[n].type = "land";
	//Models
	//Always
	locations[n].models.always.house = "farmfield";
	locations[n].models.always.locators = "farmfield_locators";
	locations[n].models.always.grassPatch = "farmfield_grass";

	locations[n].models.always.plan = "farmfield_plan";
	locations[n].models.always.plan.level = 9;

	//Day
	locations[n].models.day.charactersPatch = "farmfield_patch";
	locations[n].models.day.fonar = "farmfield_fd";

	//Night
	locations[n].models.night.charactersPatch = "farmfield_patch";
	locations[n].models.night.fonar = "farmfield_fn";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Cob_house";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	n = n + 1;

	////////////////////////////////////////////////////////////
	/// Корабельная палуба  для карта - море
	////////////////////////////////////////////////////////////
	Locations[n].id = "Ship_deck";
	Locations[n].image = "loading\art\open_sea_clear.tga";
	locations[n].id.label = "Boarding deck";
	//Sound
	Locations[n].type = "deck";
	// нельзя, иначе нет моря Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deckMedium";
	Locations[n].models.always.deckMedium = "deckMedium";
	Locations[n].models.always.locators = "deckMedium_locators";
	//Day
	locations[n].models.day.charactersPatch = "deckMedium_patch";
	Locations[n].models.day.deckMediumFonarsDay = "deckMedium_fd";
	//Night
	locations[n].models.night.charactersPatch = "deckMedium_patch";
	Locations[n].models.night.deckMediumFonarsNight= "deckMedium_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";

	n = n + 1;

	////////////////////////////////////////////////////////////
	/// Корабельная палуба  для море - море
	////////////////////////////////////////////////////////////
    //ID
	Locations[n].id = "Deck_Near_Ship";   // выслать туда шлюпку
	Locations[n].id.label = "Boarding deck";
	//Info
	Locations[n].image = "loading\art\open_sea_clear.tga";
	//Sound
	Locations[n].type = "residence";
	Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deckMedium";
	Locations[n].models.always.deckMedium = "deckMedium";
	Locations[n].models.always.locators = "deckMedium_locators";
	//Day
	locations[n].models.day.charactersPatch = "deckMedium_patch";
	Locations[n].models.always.deckMediumFonarsDay = "deckMedium_fd";
	//Night
	locations[n].models.night.charactersPatch = "deckMedium_patch";
	Locations[n].models.always.deckMediumFonarsNight= "deckMedium_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

  	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Имение Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Estate";
	locations[n].id.label = "Estate";
	locations[n].filespath.models = "locations\Estate";
	locations[n].image = "loading\EstateN.tga";
	//Sound
	locations[n].type = "land";
	//Models
	//Always
	locations[n].models.always.estate = "estate";

	locations[n].models.always.windows = "estate_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66532;
	//VolumeLight
	Locations[n].models.always.vlight = "estate_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
    Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;

	locations[n].models.always.locators = "estate_locators";
	locations[n].models.always.grassPatch = "estate_grass";
	//Day
	locations[n].models.day.charactersPatch = "estate_patch";
	locations[n].models.day.fonar = "estate_fd";
	//Night
	locations[n].models.night.charactersPatch = "estate_patch";
	locations[n].models.night.fonar = "estate_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";
	Locations[n].QuestlockWeather.hours = 20;
	Locations[n].QuestlockWeather.minutes = 00;
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "EstateBadRoom1";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Bedroom";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "EstateBadRoom2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Bedroom";

	locations[n].reload.l3.name = "reload5";
	locations[n].reload.l3.go = "EstateOffice";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cabinet";
	locations[n].locators_radius.item.item1 = 1.0;

	//homo
	locations[n].private1.key = "key3";     //сундук на балконе
	locations[n].private1.key.delItem = true; //eddy. нужно забрать ключ, иначе в ГПК у геймера будет суперлафа
	locations[n].private1.items.blade2 = 1;
	locations[n].private1.items.pistol1 = 1;
	locations[n].private1.items.bullet = 10;
	locations[n].private1.items.GunPowder = 10; // Warship fix 19.03.09 добавим порох
	n = n + 1;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спальня #1 Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "EstateBadRoom1";
	locations[n].id.label = "Bedroom";
	locations[n].filespath.models = "locations\EstateRooms\EstateBadRoom1";
	locations[n].image = "loading\EstateRoomN.tga";
	//Models
	//Sound
	locations[n].type = "house";
	//Always
	locations[n].models.always.estateBadRoom = "estateBadRoom1";
	locations[n].models.always.windows = "estateBadRoom1_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66532;
	//VolumeLight
	Locations[n].models.always.vlight = "estateBadRoom1_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
    Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;

	locations[n].models.always.locators = "estateBadRoom1_locators";
	locations[n].models.always.grassPatch = "estateRooms_grass";
	//Day
	locations[n].models.day.charactersPatch = "estateBadRoom1_patch";
	locations[n].models.day.fonar = "estateRooms_fd";
	//Night
	locations[n].models.night.charactersPatch = "estateBadRoom1_patch";
	locations[n].models.night.fonar = "estateRooms_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Estate";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Estate";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спальня #2 Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "EstateBadRoom2";
	locations[n].id.label = "Bedroom";
	locations[n].filespath.models = "locations\EstateRooms\EstateBadRoom2";
	locations[n].image = "loading\EstateRoomN.tga";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].models.always.estateBadRoom = "estateBadRoom2";
	locations[n].models.always.windows = "estateBadRoom2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66532;
	//VolumeLight
	Locations[n].models.always.vlight = "estateBadRoom2_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
   	Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;

	locations[n].models.always.locators = "estateBadRoom2_locators";
	locations[n].models.always.grassPatch = "estateRooms_grass";
	//Day
	locations[n].models.day.charactersPatch = "estateBadRoom2_patch";
	locations[n].models.day.fonar = "estateRooms_fd";
	//Night
	locations[n].models.night.charactersPatch = "estateBadRoom2_patch";
	locations[n].models.night.fonar = "estateRooms_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Estate";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Estate";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Кабинет #1 Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "EstateOffice";
	locations[n].id.label = "Cabinet";
	locations[n].filespath.models = "locations\EstateRooms\EstateOffice";
	locations[n].image = "loading\EstateRoomN.tga";
	//Sound
	locations[n].type = "residence";
	//Models
	//Always
	locations[n].models.always.EstateOffice = "estateOffice";
	locations[n].models.always.windows = "estateOffice_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66532;
	//VolumeLight
	Locations[n].models.always.vlight = "estateOffice_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
   	Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;

	locations[n].models.always.locators = "estateOffice_locators";
	locations[n].models.always.grassPatch = "estateOffice_grass";
	//Day
	locations[n].models.day.charactersPatch = "estateOffice_patch";
	locations[n].models.day.fonar = "estateOffice_fd";
	//Night
	locations[n].models.night.charactersPatch = "estateOffice_patch";
	locations[n].models.night.fonar = "estateOffice_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Estate";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Estate";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подводная Локация
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "UnderWater";
	locations[n].id.label = "UnderWater";
	locations[n].filespath.models = "locations\UnderWater";
	locations[n].image = "loading\seadeath_"+rand(3)+".tga";
	//Sound
	locations[n].type = "underwater";
	locations[n].type.LSC = true; //локация ГПК
	//Models
	//Always
	Locations[n].models.always.UnderWater = "UnderWater";
	Locations[n].models.always.UnderWater.tech = "DLightModel";

	Locations[n].models.always.outside = "UnderWater_outside";
	Locations[n].models.always.outside.tech = "DLightModel";

	Locations[n].models.always.reflect = "UnderWater_reflect";
	Locations[n].models.always.reflect .tech = "DLightModel";
	Locations[n].models.always.reflect.sea_reflection = 1;

	Locations[n].models.always.sails = "UnderWater_sails";
	Locations[n].models.always.sails.tech = "DLightModel";

	Locations[n].models.always.plants = "UnderWater_plants";
	Locations[n].models.always.plants.tech = "DLightModel";
	//Locations[n].models.always.plants.tech = "LocationWindows";
	//Locations[n].models.always.plants.level = 66532;

	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.sea_reflection = 1;

	Locations[n].models.always.plan2 = "Plan2";

	Locations[n].models.always.locators = "UnderWater_locators";

	Locations[n].models.always.grassPatch = "UnderWater_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU2.tga";
	//Day
	locations[n].models.day.charactersPatch = "UnderWater_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "UnderWater_patch_day";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload73";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].locators_radius.reload.reload1 = 2.0;
	locations[n].locators_radius.item.item1 = 0.6;
	locations[n].locators_radius.item.item2 = 0.6;
	locations[n].locators_radius.item.item3 = 0.6;
	locations[n].locators_radius.item.item4 = 0.6;
	locations[n].locators_radius.item.item5 = 0.6;

	//в сундуках
	locations[n].private1.money = 174366;
	locations[n].private1.items.indian1 = 1;
	locations[n].private1.items.indian2 = 1;
	locations[n].private1.items.indian3 = 2;
	locations[n].private1.items.indian4 = 2;
	locations[n].private1.items.indian5 = 1;
	locations[n].private1.items.indian6 = 1;
	locations[n].private1.items.indian7 = 1;
	locations[n].private1.items.indian8 = 2;
	locations[n].private1.items.indian9 = 1;
	locations[n].private1.items.statue1 = 5;
	locations[n].private1.items.potion2 = 21;

	locations[n].private2.money = 72890;
	locations[n].private2.items.potion1 = 59;
	locations[n].private2.items.potionrum = 100;
	locations[n].private2.items.potionwine = 200;
	locations[n].private2.items.potion4 = 41;
	locations[n].private2.items.jewelry1 = 4;
	locations[n].private2.items.jewelry3 = 19;
	locations[n].private2.items.jewelry2 = 72;

	locations[n].private3.money = 375000;
	locations[n].private3.items.indian10 = 1;
	locations[n].private3.items.indian11 = 2;
	locations[n].private3.items.indian12 = 1;
	locations[n].private3.items.indian13 = 2;
	locations[n].private3.items.indian15 = 1;
	locations[n].private3.items.indian16 = 1;
	locations[n].private3.items.indian18 = 1;
	locations[n].private3.items.indian20 = 2;
	locations[n].private3.items.indian21 = 1;
	locations[n].private3.items.indian22 = 1;
	locations[n].private3.items.potion2 = 21;

	locations[n].private4.money = 69720;
	locations[n].private4.items.Mineral2 = 2;
	locations[n].private4.items.Mineral3 = 59332;
	locations[n].private4.items.Mineral5 = 1;
	locations[n].private4.items.Mineral6 = 61;
	locations[n].private4.items.Mineral7 = 5;
	locations[n].private4.items.Mineral8 = 63;
	locations[n].private4.items.Mineral9 = 2;
	locations[n].private4.items.indian15 = 1;
	locations[n].private4.items.indian17 = 2;
	locations[n].private4.items.indian19 = 1;

	locations[n].private5.money = 275900;
	locations[n].private5.items.jewelry5 = 126;
	locations[n].private5.items.jewelry17 = 332;

	locations[n].private6.money = 395100;
	locations[n].private6.items.potion1 = 4;
	locations[n].private6.items.jewelry18 = 14;
	locations[n].private6.items.jewelry16 = 28;
	locations[n].private6.items.jewelry15 = 23;
	locations[n].private6.items.jewelry14 = 34;
	locations[n].private6.items.jewelry13 = 11;
	locations[n].private6.items.jewelry10 = 27;
	locations[n].private6.items.blade27 = 1;

	locations[n].private7.money = 53670;
	locations[n].private7.items.jewelry7 = 10;
	locations[n].private7.items.jewelry11 = 123;
	locations[n].private7.items.jewelry12 = 345;
	locations[n].private7.items.potion1 = 14;
	locations[n].private7.items.potion2 = 21;
	locations[n].private7.items.potion4 = 27;

	n = n + 1;

	//Лока создания перса
	Locations[n].id = "SelectMainCharacter_Cabine";   // Lugger: Выбор ГГ
    	locations[n].id.label = "cabine2";
	locations[n].filespath.models = "locations\inside\cabin02\";
	locations[n].image = "loading\capdeck.tga";
	//Sound
	locations[n].type = "residence";
	locations[n].LoadCabinType.Type = "Cabin";
	//Models
	//Always
	locations[n].models.always.l1 = "cabin02";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.locators = "cabin02_locators";
	locations[n].models.always.window = "cabin02_fonar";
	Locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	//Day
	locations[n].models.day.charactersPatch = "cabin02_patch";

	//Night
	locations[n].models.night.charactersPatch = "cabin02_patch";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";

	//Locations[n].boarding = "false";
	//Locations[n].camshuttle = 0;

	locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box3 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box4 = Items_MakeTime(0, 1, 1, 2003);

    	LAi_LocationFightDisable(&Locations[n], false);

	Locations[n].locators_radius.randitem.randitem1 = 1;
    	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "";
	Locations[n].reload.l1.emerge = "";
	Locations[n].reload.l1.label = "";
	Locations[n].items.randitem1 = "";

	locations[n].environment.weather.rain = false;
	n = n + 1;

	return n;
}
