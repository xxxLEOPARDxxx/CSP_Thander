

int LocationInitCaiman(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Остров Кайман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж17
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore17";
	locations[n].id.label = "Shore17";
	locations[n].image = "loading\outside\harbor_" + rand(14) + ".tga";
	locations[n].worldmap = "Caiman";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Caiman";
	//locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].fastreload = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore01";
	Locations[n].models.always.shore01 = "shore01";
	locations[n].models.always.shore01.sea_reflection = 1;
	Locations[n].models.always.shore01seabed = "shore01_sb";
	Locations[n].models.always.locators = "shore01_locators";

	Locations[n].models.always.grassPatch = "shore01_grass";
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
	locations[n].models.day.charactersPatch = "shore01_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Caiman_Jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Caiman";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Caiman";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].fastreload = "Caiman";
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
	locations[n].reload.l1.go = "Shore17";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore17";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore16";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore16";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Caiman_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// пляж 16
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore16";
	locations[n].id.label = "Shore16";
	locations[n].image = "loading\outside\harbor_" + rand(14) + ".tga";
	locations[n].worldmap = "Caiman";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Caiman";
	//locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].fastreload = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Caiman";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Caiman";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt2";
	Locations[n].models.always.caveEnt2 = "caveEnt2";
	Locations[n].models.always.locators = "caveEnt2_locators";
	Locations[n].models.always.grassPatch = "caveEnt2_grass";
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
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "caveEnt2_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Caiman_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Caiman_Jungle_01";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\Grot_"+rand(2)+".tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Caiman";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto1";
	locations[n].models.always.grotto1 = "grotto1";
	locations[n].models.always.grotto1alpha = "grotto1_alpha";
	Locations[n].models.always.grotto1alpha.tech = "LocationWindows";
	locations[n].models.always.grotto1alpha.level = 65532;
	locations[n].models.always.chest = "chest";
	locations[n].models.always.locators = "grotto1_locators";

	locations[n].locators_radius.item.duhi1 = 1.3;

	Locations[n].models.always.rays = "grotto1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;
	//Day
	locations[n].models.day.charactersPatch = "grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Caiman_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из поселения Кайман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate_"+rand(1)+".tga";
	//Town sack
	locations[n].townsack = "Caiman";
	//Sound
	locations[n].type = "town";
	//locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
	locations[n].DisableEncounters = true;
	locations[n].fastreload = "Caiman";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\smugglerLairExit";
	Locations[n].models.always.smugglerLairExit = "smugglerLairExit";
	Locations[n].models.always.locators = "smugglerLairExit_locators";
	Locations[n].models.always.grassPatch = "smugglerLairExit_grass";
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
	locations[n].models.day.charactersPatch = "smugglerLairExit_patch";
	locations[n].models.day.fonars = "smugglerLairExit_fd";
	//Night
	locations[n].models.night.charactersPatch = "smugglerLairExit_patch";
	locations[n].models.night.fonars = "smugglerLairExit_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Caiman_Jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore17";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore17";
	locations[n].locators_radius.reload.reload1_back = 2.0;

    	Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Caiman_town";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Street";
	locations[n].locators_radius.reload.reload3 = 1.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Кайман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_town";
	locations[n].id.label = "Street";
	locations[n].image = "loading\towns\pearl1.tga";
	locations[n].worldmap = "Caiman_town";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].NotCitizens = true;
	//Town sack
	locations[n].townsack = "Caiman";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\smugglerLairTown";
	Locations[n].models.always.smugglerLairTown = "smugglerLairTown";
	Locations[n].models.always.locators = "smugglerLairTown_locators";
	Locations[n].models.always.grassPatch = "smugglerLairTown_grass";
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
	locations[n].models.day.charactersPatch = "smugglerLairTown_patch";
	locations[n].models.day.fonars = "smugglerLairTown_fd";
	//Night
	locations[n].models.night.charactersPatch = "smugglerLairTown_patch";
	locations[n].models.night.fonars = "smugglerLairTown_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map

	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Caiman_ExitTown";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1 = 1.8;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonHut";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	Locations[n].reload.l3.name = "reload6";
	Locations[n].reload.l3.go = "Caiman_townhall";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Townhall";
	locations[n].reload.l3.disable = false;

	Locations[n].reload.l4.name = "reload5";
	Locations[n].reload.l4.go = "Caiman_tavern";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Tavern";
	locations[n].reload.l4.disable = true;

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Caiman_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.disable = true;
	locations[n].reload.l5.close_for_night = 1;

	Locations[n].reload.l6.name = "reload8";
	Locations[n].reload.l6.go = "Caiman_store";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Store";
	Locations[n].reload.l6.close_for_night = 1;
	locations[n].reload.l6.disable = true;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Caiman_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	locations[n].reload.l7.disable = true;
	locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Caiman_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;
	locations[n].reload.l8.disable = true;

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Caiman_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;
	locations[n].reload.l10.disable = true;

	locations[n].reload.l11.name = "reload4";
	locations[n].reload.l11.go = "Caiman_StoreHouse";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "";
	locations[n].reload.l11.disable = true;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "Caiman_ExitTown";
	locations[n].reload.gate.emerge = "reload3";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
    	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Кайман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "Caiman_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern04\";
	locations[n].image = "loading\inside\Tavern_"+rand(7)+".tga";
	locations[n].habitues = 0;
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Caiman";
 	locations[n].islandId = "Caiman";
	locations[n].DisableExtortion = true;
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern04";
	locations[n].models.always.locators = "Tavern04_locators";
	locations[n].models.always.window = "tavern04_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Tavern04_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern04_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
    	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Caiman_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Кайман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\TavernCommon.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Кайман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop_"+rand(3)+".tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\StoreSmall\";
	locations[n].models.always.locators = "StoreSmall_locators";
	locations[n].models.always.store = "StoreSmall";
	locations[n].models.always.window = "StoreSmall_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "StoreSmall_patch";
	//Night
	locations[n].models.night.charactersPatch = "StoreSmall_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
    	locations[n].reload.l1.label = "Street";

	/*locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";*/
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// СКЛАД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_StoreHouse";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\inside\Storage_"+rand(3)+".tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\sklad";
	locations[n].models.always.locators = "sklad_locators";
	locations[n].models.always.modelSklad = "sklad";
	locations[n].models.always.modelSklad.level = 65538;
	locations[n].models.always.window = "sklad_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "sklad_patch";
	//Night
	locations[n].models.night.charactersPatch = "sklad_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция Caiman
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Caiman";
 	locations[n].islandId = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РОСТОВЩИК
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\Bank01\";
	locations[n].image = "loading\inside\bank_"+rand(3)+".tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
    	locations[n].reload.l1.label = "Street";

	/*locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_5";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";*/
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard03\";
	locations[n].image = "loading\inside\Shipyard_"+rand(4)+".tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Caiman";
  	locations[n].islandId = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	/*locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";*/
	locations[n].locators_radius.item.item1 = 1.0;
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\inside\churchInside3.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\churchInside3";
	locations[n].models.always.churchInside3 = "churchInside3";
	locations[n].models.always.churchInside3.level = 65538;
	locations[n].models.always.locators = "churchInside3_locators";

	Locations[n].models.always.churchInside3windows = "churchInside3_windows";
	Locations[n].models.always.churchInside3windows.tech = "LocationWindows";
	locations[n].models.always.churchInside3windows.level = 65539;

	locations[n].models.always.backgroundInsides = "backgroundInsides";
	locations[n].models.always.backgroundInsides.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "churchInside3_patch";
	//Night
	locations[n].models.night.charactersPatch = "churchInside3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
    	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Caiman";
	locations[n].islandId = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
    	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Плантация Каймана
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Plantation";
	locations[n].id.label = "Plantation";
	locations[n].image = "loading\Plantation.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	locations[n].citizens = false;
	locations[n].soldiers = false;
	locations[n].carrier = false;
	locations[n].DisableEncounters = true;
	//Sound
	locations[n].type = "jungle";
	locations[n].fastreload = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\BarbadosPlantation";
	locations[n].models.always.BarbadosPlantation = "BarbadosPlantation";
	locations[n].models.always.reflect = "BarbadosPlantation_reflect";
	Locations[n].models.always.reflect.sea_reflection = 1;
	locations[n].models.always.gate = "BarbadosPlantation_gateopen";
	locations[n].models.always.locators = "BarbadosPlantation_locators";
	locations[n].models.always.grassPatch = "BarbadosPlantation_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.Waterfall = "waterfall";
	Locations[n].models.always.Waterfall.uvslide.v0 = 0.3;
    	Locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall.level = 99949;
	locations[n].models.always.plan1 = "plan1";
	locations[n].models.always.plan1.level = 9;
	locations[n].models.always.plan2 = "plan2";
	locations[n].models.always.plan2.level = 8;
	locations[n].models.always.plan3 = "plan3";
	locations[n].models.always.plan3.level = 7;
	locations[n].models.always.plan4 = "plan4";
	locations[n].models.always.plan4.level = 6;
	//Day
	locations[n].models.day.charactersPatch = "BarbadosPlantation_patchopen";
	locations[n].models.day.fonar = "BarbadosPlantation_fd";
	//Night
	locations[n].models.night.charactersPatch = "BarbadosPlantation_patchopen";
	locations[n].models.night.fonar = "BarbadosPlantation_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Caiman_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Caiman_Jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "houseSp1";
	locations[n].reload.l3.go = "CaimanPlantationOffice";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = false;
	locations[n].reload.l3.label = "Caiman Plantation Office";
	Locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "houseS1";
	locations[n].reload.l4.go = "Caiman_Plantation_S1";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = false;
	locations[n].reload.l4.label = "house";
	Locations[n].reload.l4.close_for_night = 1;

	locations[n].reload.l5.name = "houseS2";
	locations[n].reload.l5.go = "Caiman_Plantation_S2";
	locations[n].reload.l5.emerge = "reload2";
	locations[n].reload.l5.autoreload = false;
	locations[n].reload.l5.label = "house";
	Locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "houseF1";
	locations[n].reload.l6.go = "Caiman_Plantation_F1";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = false;
	locations[n].reload.l6.label = "house";
	Locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "houseF2";
	locations[n].reload.l7.go = "Caiman_Plantation_F2";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = false;
	locations[n].reload.l7.label = "house";
	Locations[n].reload.l7.close_for_night = 1;
    	locations[n].locators_radius.quest.detector1 = 1.0;

    	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "CaimanPlantationOffice";
	locations[n].filespath.models = "locations\inside\StoneHouse";
	locations[n].id.label = "Caiman Plantation Office";
	locations[n].image = "loading\inside\stonehouse.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
	locations[n].fastreload = "Caiman";
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
	locations[n].reload.l1.go = "Caiman_Plantation";
	locations[n].reload.l1.emerge = "houseSp1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Plantation";
    	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Plantation_S1";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonHut.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
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
	locations[n].reload.l1.go = "Caiman_Plantation";
	locations[n].reload.l1.emerge = "houseS1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Plantation";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Plantation_S2";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonHut.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
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
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "Caiman_Plantation";
	locations[n].reload.l1.emerge = "houseS2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Plantation";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Plantation_F1";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\CommonRoom_MH5.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
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
	locations[n].reload.l1.go = "Caiman_Plantation";
	locations[n].reload.l1.emerge = "houseF1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Plantation";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Plantation_F2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CommonRoom_MH9.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse09";
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
	locations[n].reload.l1.go = "Caiman_Plantation";
	locations[n].reload.l1.emerge = "houseF2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Plantation";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ДОМ НАЧАЛЬНИКА РУДНИКОВ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Mines_Comendant_House";
	locations[n].filespath.models = "locations\inside\FlamHouse";
	locations[n].id.label = "Cayman Mines Office";
	locations[n].image = "loading\inside\CommonFlamHouse.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
	//locations[n].fastreload = "";
	locations[n].fastreload = "Caiman";
	//Models
	//Always
	locations[n].models.always.tavern = "FlamHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "FlamHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "FlamHouse_locators";
	locations[n].models.night.locators = "FlamHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "FlamHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "FlamHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Caiman_Mines";
	locations[n].reload.l1.emerge = "reload3_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Mines";
    	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РУДНИКИ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Caiman_Mines";
    	locations[n].id.label = "Caiman Mines";
	locations[n].filespath.models = "locations\Outside\mine\";
	locations[n].image = "loading\outside\Mines.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].townsack = "Caiman";
	locations[n].islandId = "Caiman";
	locations[n].DisableEncounters = true;
	locations[n].fastreload = "Caiman";
	//Models
	//Always
	locations[n].models.always.l1 = "mine";
	// locations[n].models.always.l1.level = 65538;
	locations[n].models.always.locators = "mine_locators_addon";
	locations[n].models.always.grassPatch = "mine_grass";
	//Day
	locations[n].models.day.charactersPatch = "mine_patch";
	locations[n].models.day.fonar = "mine_fd";

	//Night
	locations[n].models.night.charactersPatch = "mine_patch";
	locations[n].models.night.fonar = "mine_fn";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

    	LAi_LocationFightDisable(&Locations[n], false);

    	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Caiman_ExitMines";
	Locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Caiman Mines Exit";
	locations[n].locators_radius.reload.reload1_back = 1.5;

    	Locations[n].reload.l2.name = "reload2_back";
	Locations[n].reload.l2.go = "Caiman_Mines_CaveEntrance";
	Locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	Locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 5.0;

    	Locations[n].reload.l3.name = "reload3_back";
	Locations[n].reload.l3.go = "Caiman_Mines_Comendant_House";
	Locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Cayman Mines Office";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из рудников
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    	locations[n].id = "Caiman_ExitMines";
	locations[n].id.label = "Caiman Mines Exit";
	locations[n].image = "loading\Gate_"+rand(1)+".tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].DisableEncounters = true;
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Caiman";
	locations[n].fastreload = "Caiman";
    	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitY";
	Locations[n].models.always.townExit = "townExitY";
	Locations[n].models.always.townWalls = "townExitY_wood";

	Locations[n].models.always.locators = "townExitY_locators";

	Locations[n].models.always.grassPatch = "townExitY_grass";
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
	locations[n].models.day.charactersPatch = "townExitY_patch";
	locations[n].models.day.fonars = "townExitY_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitY_patch";
	locations[n].models.night.fonars = "townExitY_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "Caiman_Mines";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Caiman Mines";
	locations[n].locators_radius.reload.reload2_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Caiman_ExitTown";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "ExitTown";

	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Caiman_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Mines_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\Jungle_"+rand(5)+".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Caiman";
	locations[n].DisableEncounters = true;
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
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Caiman_Mines_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Caiman_Mines";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Caiman Mines";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Caiman_Mines_Grot";
	locations[n].id.label = "Grot";
    	locations[n].image = "loading\inside\Grot_"+rand(2)+".tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto2";
	locations[n].models.always.grotto2 = "grotto2";
	locations[n].models.always.grotto2.sea_reflection = 1;
	locations[n].models.always.grotto2alpha = "grotto2_alpha";
	Locations[n].models.always.grotto2alpha.tech = "LocationWindows";
	locations[n].models.always.grotto2alpha.level = 65532;
	locations[n].models.always.locators = "grotto2_locators";

	locations[n].locators_radius.item.duhi1 = 1.3;

	Locations[n].models.always.rays = "grotto2_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;
	//Day
	locations[n].models.day.charactersPatch = "grotto2_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Caiman_Mines_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Охранная база вместо форта - ПОРТ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "LandGuardingPort";
	locations[n].id.label = "Land Guarding Port";
	Locations[n].image = "loading\outside\FortDefence.tga";

	//Town sack
	locations[n].type = "seashore";
	Locations[n].townsack = "Caiman";
	Locations[n].DisableCrabs = true;
	locations[n].DisableEncounters = true;
	//Locations[n].DisableStuff = true;
	locations[n].fastreload = "Caiman";

	//Sound
	locations[n].parent_colony = "Caiman";
	locations[n].islandId = "Caiman";
	//locations[n].soldiers = true;
	//Models
	//Always
	Locations[n].filespath.models = "Locations\Colony\LandGuardingPort";
	Locations[n].models.always.city = "FFport02";
	Locations[n].models.always.city.foam = "1";
	Locations[n].models.always.seabed = "FFport02_sb";
	Locations[n].models.always.seabed.foam = "1";
	Locations[n].models.always.locators = "FFport02_l";
	Locations[n].models.always.grassPatch = "FFport02_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	//Day
	Locations[n].models.day.fonar = "FFport02_fd";
	Locations[n].models.day.charactersPatch = "FFport02_p";
	//Night
	Locations[n].models.night.fonar = "FFport02_fn";
	Locations[n].models.night.charactersPatch = "FFport02_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFantomsGen(&locations[n], true);
	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Caiman_ExitTown";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].reload.l1.label = "ExitTown";
	Locations[n].locators_radius.reload.reload1_back = 2.5;

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "LandGuardingFort";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "Land Guarding Fort";

	Locations[n].reload.l3.name = "home";
	Locations[n].reload.l3.go = "LandGuardingHeadHouse";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Land Guarding Head House";
	Locations[n].reload.l3.disable = 0;

	Locations[n].reload.l4.name = "boat";
	Locations[n].reload.l4.go = "Caiman";
	Locations[n].reload.l4.emerge = "reload_1";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Caiman";
	Locations[n].reload.l4.disable = 0;
	Locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Охранная база вместо форта - ФОРТ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "LandGuardingFort";
	locations[n].id.label = "Land Guarding Fort";
	Locations[n].image = "loading\outside\CaimanFort.tga";

	//Town sack
	locations[n].type = "fort";
	Locations[n].townsack = "Caiman";

	//Sound
	locations[n].parent_colony = "Caiman";
	locations[n].islandId = "Caiman";
	locations[n].soldiers = true;
	locations[n].DisableEncounters = true;

	locations[n].fastreload = "Caiman";
	//Models
	//Always
	Locations[n].filespath.models = "Locations\Colony\LandGuardingFort";
	Locations[n].models.always.locators = "fort1_l";
	Locations[n].models.always.l1 = "fort1";
	//Day
	Locations[n].models.day.charactersPatch = "fort1_p";
	Locations[n].models.day.fonar = "fort1_fd";
	//Night
	Locations[n].models.night.charactersPatch = "fort1_p";
	Locations[n].models.night.fonar = "fort1_fn";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";

	LAi_LocationFantomsGen(&locations[n], true);
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "LandGuardingPort";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Land Guarding Port";
	Locations[n].reload.l1.disable = 0;
	Locations[n].locators_radius.reload.reload1 = 2.5;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Охранная база вместо форта - Дом начальника гарнизона
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LandGuardingHeadHouse";
	locations[n].id.label = "Land Guarding Head House";
	locations[n].image = "loading\inside\CommonRoom_MH2.tga";
	//Town sack
	locations[n].townsack = "Caiman";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Caiman";
	//Sound
	locations[n].type = "house";
	locations[n].DisableEncounters = true;
	locations[n].fastreload = "Caiman";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse02";
	locations[n].models.always.mediumhouse02 = "mediumhouse02";
	locations[n].models.always.mediumhouse02.level = 65538;
	locations[n].models.day.locators = "mediumhouse02_locators";
	locations[n].models.night.locators = "mediumhouse02_Nlocators";

	Locations[n].models.always.mediumhouse02windows = "mediumhouse02_windows";
	Locations[n].models.always.mediumhouse02windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse02windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse02rand= "mediumhouse02_rand";
	locations[n].models.day.charactersPatch = "mediumhouse02_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
    	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LandGuardingPort";
	locations[n].reload.l1.emerge = "home";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Land Guarding Port";
    	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

	return n;
}
