
int LocationInitTenotchitlan(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли  ----------- ход к пирамиде и жемчужным промыслам из бухты Аматике (shore9)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle1.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle1\";
	Locations[n].models.always.jungle = "jungle1";
	Locations[n].models.always.locators = "jungle1_locators";
	Locations[n].models.always.grassPatch = "jungle1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].models.day.charactersPatch = "jungle1_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_Jungle_04"; //жемчужный берег
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.5;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle3.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";
	Locations[n].models.always.locators = "jungle3_locators";
	Locations[n].models.always.grassPatch = "jungle3_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenotchitlan_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_03";       // на Shore9
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Temple";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пирамида
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple";
	Locations[n].image = "loading\jonny_load\outside\pyramid1.tga";
	//Sound
	locations[n].type = "teno";
	locations[n].id.label = "Incas Temple";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\pyramid1\";
	Locations[n].models.always.pyramid1 = "pyramid1";
	locations[n].models.always.pyramid1.sea_reflection = 1;
	Locations[n].models.always.pyramid1seabed = "pyramid1_sb";
	Locations[n].models.always.locators = "pyramid1_locators";

	Locations[n].models.always.grassPatch = "pyramid1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 99948;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 99947;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 99946;
	Locations[n].models.always.l3.tech = "DLightModel";
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 99945;
	Locations[n].models.always.l4.tech = "DLightModel";
	//Waterfall
	Locations[n].models.always.Waterfall1 = "waterfall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 99950;

	Locations[n].models.always.Waterfall2 = "waterfall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 99949;
	//Day
	locations[n].models.day.charactersPatch = "pyramid1_patch";
	//Night
	locations[n].models.night.charactersPatch = "pyramid1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Tenotchitlan_Jungle_02";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].locators_radius.reload.reload1_back = 3;

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Temple_Inside";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.disable = true;
	Locations[n].locators_radius.item.item1 = 0.9;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пирамида Старая Изнутри
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Inside";
	locations[n].id.label = "Pyramid1Inside";
	Locations[n].image = "loading\jonny_load\inside\Pyramid1Inside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].id.label = "Incas Temple";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	Locations[n].filespath.models = "Locations\Inside\Pyramid1Inside\";
	//Always
	Locations[n].models.always.pyramid1 = "Pyramid1Inside";
	Locations[n].models.always.locators = "Pyramid1Inside_locators";
	//Day
	locations[n].models.day.charactersPatch = "Pyramid1Inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "Pyramid1Inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Temple";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].locators_radius.item.item1 = 1.1;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle7.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle7";
	Locations[n].models.always.jungle = "jungle7";
	Locations[n].models.always.locators = "jungle7_locators";
	Locations[n].models.always.grassPatch = "jungle7_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].models.day.charactersPatch = "jungle7_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle7_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Beliz_jungle_02"; //из Белиза от бухты Аматике
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_02";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Tenotchitlan_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\jonny_load\jungle\CaveEnt2.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt2";
	Locations[n].models.always.caveEnt2 = "caveEnt2";
	Locations[n].models.always.locators = "caveEnt2_locators";
	Locations[n].models.always.grassPatch = "caveEnt2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].reload.l3.go = "Tenotchitlan_Cave";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_03";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Cave";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\jonny_load\inside\cavernMedium1.tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium1";
	locations[n].models.always.cavernMedium1 = "cavernMedium1";
	locations[n].models.always.cavernMedium1.sea_reflection = 1;
	locations[n].models.always.lamps = "cavernMedium1_lamps";
	locations[n].models.always.locators = "cavernMedium1_locators";

	locations[n].locators_radius.item.duhi1 = 1.3;

	Locations[n].models.always.rays = "cavernMedium1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium1_patch";
	Locations[n].models.day.jumpPatch = "CavernMedium1_jump";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium1_patch";
	Locations[n].models.night.jumpPatch = "CavernMedium1_jump";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenotchitlan_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли    ----------- вход в Теночтитлан из мыса Перлас (shore53) -----------
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle1.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle1\";
	Locations[n].models.always.jungle = "jungle1";
	Locations[n].models.always.locators = "jungle1_locators";
	Locations[n].models.always.grassPatch = "jungle1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].models.day.charactersPatch = "jungle1_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";    //на мыс Перлас
	locations[n].reload.l1.go = "Shore53";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.5;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_06";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Tenotchitlan_Jungle_06";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle8.tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle8";
	Locations[n].models.always.jungle = "jungle8";
	Locations[n].models.always.locators = "jungle8_locators";
	Locations[n].models.always.grassPatch = "jungle8_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].models.day.charactersPatch = "jungle8_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle8_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore9";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_05";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenochtitlan";
	locations[n].id.label = "Tenochtitlan";
	locations[n].filespath.models = "locations\Tenochtitlan";
	locations[n].image = "loading\jonny_load\quest\Tenochtitlan.tga";
	//Sound
	locations[n].type = "teno";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].gotoFire = true; //локаторы teleport вспыхивают и ранят
	locations[n].changeAnimation = MainChAnim; //сменить анимацию на обычную
	//Models
	//Always
	locations[n].models.always.Tenochtitlan = "Tenochtitlan";
	locations[n].models.always.reflect = "Tenochtitlan_reflect";
	locations[n].models.always.reflect.sea_reflection = 1;
	locations[n].models.always.seabed = "Tenochtitlan_sb";
	locations[n].models.always.grassPatch = "Tenochtitlan_grass";
	Locations[n].models.day.jumpPatch = "Tenochtitlan_jamp";
	Locations[n].models.night.jumpPatch = "Tenochtitlan_jamp";
	locations[n].models.always.locators = "Tenochtitlan_locators";
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 12;
	locations[n].models.always.plan = "plan2";
	locations[n].models.always.plan.level = 11;
	locations[n].models.always.plan = "plan3";
	locations[n].models.always.plan.level = 10;
	locations[n].models.always.plan = "plan4";
	locations[n].models.always.plan.level = 9;
	//Day
	locations[n].models.day.charactersPatch = "Tenochtitlan_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tenochtitlan_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenotchitlan_Jungle_06";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	//---------- храм №1 ----------
	locations[n].reload.l2.name = "reloadTemple1";
	locations[n].reload.l2.go = "Temple_1";
	locations[n].reload.l2.emerge = "reload1";
	//---------- храм №2 ----------
	locations[n].reload.l3.name = "reloadTemple2";
	locations[n].reload.l3.go = "Temple_2";
	locations[n].reload.l3.emerge = "reload2";
	//---------- храм №3 ----------
	locations[n].reload.l4.name = "reloadTemple3";
	locations[n].reload.l4.go = "Temple_3";
	locations[n].reload.l4.emerge = "reload3";
	//---------- храм №4 ----------
	locations[n].reload.l5.name = "reloadTemple4";
	locations[n].reload.l5.go = "Temple_4";
	locations[n].reload.l5.emerge = "reload4";
	//---------- храм №5 ----------
	locations[n].reload.l6.name = "reloadTemple5";
	locations[n].reload.l6.go = "Temple_5";
	locations[n].reload.l6.emerge = "reload5";
	//---------- храм №6 ----------
	locations[n].reload.l7.name = "reloadTemple6";
	locations[n].reload.l7.go = "Temple_6";
	locations[n].reload.l7.emerge = "reload1";
	//---------- храм №7 ----------
	locations[n].reload.l8.name = "reloadTemple7";
	locations[n].reload.l8.go = "Temple_7";
	locations[n].reload.l8.emerge = "reload2";
	//---------- храм №8 ----------
	locations[n].reload.l9.name = "reloadTemple8";
	locations[n].reload.l9.go = "Temple_8";
	locations[n].reload.l9.emerge = "reload3";
	//---------- храм №9 ----------
	locations[n].reload.l10.name = "reloadTemple9";
	locations[n].reload.l10.go = "Temple_9";
	locations[n].reload.l10.emerge = "reload4";
	//---------- храм №10 ----------
	locations[n].reload.l11.name = "reloadTemple10";
	locations[n].reload.l11.go = "Temple_10";
	locations[n].reload.l11.emerge = "reload5";

	//---------- храм большой ----------
	locations[n].reload.l32.name = "reloadTemple32";
	locations[n].reload.l32.go = "Temple_great";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.disable = true;
	locations[n].reload.l33.name = "reloadTemple33";
	locations[n].reload.l33.go = "Temple_great";
	locations[n].reload.l33.emerge = "reload2";
	locations[n].reload.l33.disable = true;
	locations[n].reload.l34.name = "reloadTemple34";
	locations[n].reload.l34.go = "Temple_great";
	locations[n].reload.l34.emerge = "reload3";
	locations[n].reload.l34.disable = true;

	locations[n].reload.l35.name = "reloadTemple41";
	locations[n].reload.l35.go = "Temple_great";
	locations[n].reload.l35.emerge = "reload4";
	locations[n].reload.l35.disable = true;
	locations[n].reload.l36.name = "reloadTemple42";
	locations[n].reload.l36.go = "Temple_great";
	locations[n].reload.l36.emerge = "reload5";
	locations[n].reload.l36.disable = true;
	locations[n].reload.l37.name = "reloadTemple43";
	locations[n].reload.l37.go = "Temple_great";
	locations[n].reload.l37.emerge = "reload6";
	locations[n].reload.l37.disable = true;

	locations[n].reload.l38.name = "reloadTemple40";
	locations[n].reload.l38.go = "Temple_great";
	locations[n].reload.l38.emerge = "reload7";
	locations[n].reload.l38.disable = true;
	locations[n].reload.l39.name = "reloadTemple39";
	locations[n].reload.l39.go = "Temple_great";
	locations[n].reload.l39.emerge = "reload8";
	locations[n].reload.l39.disable = true;
	//---------- храм круглый ----------
	locations[n].reload.l40.name = "reloadTemple31";
	locations[n].reload.l40.go = "Temple_round";
	locations[n].reload.l40.emerge = "reload1";
	locations[n].reload.l40.disable = true;
	locations[n].locators_radius.item.button01 = 1.4;
	//---------- храм черепков ----------
	locations[n].reload.l41.name = "reloadTemple35";
	locations[n].reload.l41.go = "Temple_Skulls";
	locations[n].reload.l41.emerge = "reload1";
	locations[n].reload.l42.name = "reloadTemple36";
	locations[n].reload.l42.go = "Temple_Skulls";
	locations[n].reload.l42.emerge = "reload2";
	locations[n].reload.l43.name = "reloadTemple37";
	locations[n].reload.l43.go = "Temple_Skulls";
	locations[n].reload.l43.emerge = "reload3";
	//---------- подводные храмы ----------
	locations[n].reload.l44.name = "reloadU1_back";
	locations[n].reload.l44.go = "Temple_Underwater_right";
	locations[n].reload.l44.emerge = "reload1";
	locations[n].reload.l44.autoreload = "1";
	locations[n].locators_radius.reload.reloadU1_back = 3.0;
	locations[n].reload.l45.name = "reloadU2_back";
	locations[n].reload.l45.go = "Temple_Underwater_left";
	locations[n].reload.l45.emerge = "reload1";
	locations[n].reload.l45.autoreload = "1";
	locations[n].locators_radius.reload.reloadU2_back = 3.0;

	string sTemp;
	for(int i=1; i<=20; i++)
	{
		sTemp = "fire" + i;
		locations[n].locators_radius.teleport.(sTemp) = 4.1;
	}
	int iTeno = n;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан Храмы Тотемов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//----------------- Храм №1 ------------------------
	locations[n].id = "Temple_1";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx1 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple1";
	n = n + 1;
	//----------------- Храм №2 ------------------------
	locations[n].id = "Temple_2";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx2 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple2";
	n = n + 1;
	//----------------- Храм №3 ------------------------
	locations[n].id = "Temple_3";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx3 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple3";
	n = n + 1;
	//----------------- Храм №4 ------------------------
	locations[n].id = "Temple_4";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx4 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload4";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple4";
	n = n + 1;
	//----------------- Храм №5 ------------------------
	locations[n].id = "Temple_5";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx5 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload5";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple5";
	n = n + 1;
	//----------------- Храм №6 ------------------------
	locations[n].id = "Temple_6";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx6 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple6";
	n = n + 1;
	//----------------- Храм №7 ------------------------
	locations[n].id = "Temple_7";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx7 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple7";
	n = n + 1;
	//----------------- Храм №8 ------------------------
	locations[n].id = "Temple_8";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx8 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple8";
	n = n + 1;
	//----------------- Храм №9 ------------------------
	locations[n].id = "Temple_9";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx9 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload4";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple9";
	n = n + 1;
	//----------------- Храм №10 ------------------------
	locations[n].id = "Temple_10";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\jonny_load\quest\TemplePointInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].idxTeno = iTeno; //индекс Теночтитлана
	locations[iTeno].temples.idx10 = n; //в локацию Теночтитлана индекс храма
	locations[n].smallGodTemple = 0; //кол-во посещений храма геймером
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload5";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple10";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан Большой Храм
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Temple_great";
	locations[n].id.label = "TempleGreatInside";
	locations[n].filespath.models = "locations\TenochtitlanInside\TempleGreatInside";
	locations[n].image = "loading\jonny_load\quest\TempleGreatInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].changeAnimation = MainChAnim; //сменить анимацию на обычную
	locations[n].greatTemple = true;
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TempleGreatInside";
	locations[n].models.always.locators = "TempleGreatInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TempleGreatInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleGreatInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple32";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple33";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple34";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple41";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple42";
	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "Tenochtitlan";
	locations[n].reload.l6.emerge = "reloadTemple43";

	locations[n].reload.l7.name = "reload7";
	locations[n].reload.l7.go = "Tenochtitlan";
	locations[n].reload.l7.emerge = "reloadTemple40";
	locations[n].reload.l8.name = "reload8";
	locations[n].reload.l8.go = "Tenochtitlan";
	locations[n].reload.l8.emerge = "reloadTemple39";

	locations[n].reload.l9.name = "reload9";
	locations[n].reload.l9.go = "Temple_Underwater_right";
	locations[n].reload.l9.emerge = "reload2";
	//locations[n].reload.l9.go = "Tenochtitlan";
	//locations[n].reload.l9.emerge = "reloadU1";
	locations[n].reload.l9.autoreload = "1";
	locations[n].reload.l10.name = "reload10";
	locations[n].reload.l10.go = "Temple_Underwater_left";
	locations[n].reload.l10.emerge = "reload2";
	//locations[n].reload.l10.go = "Tenochtitlan";
	//locations[n].reload.l10.emerge = "reloadU2";
	locations[n].reload.l10.autoreload = "1";

	locations[n].locators_radius.reload.reload9 = 1.2;
	locations[n].locators_radius.reload.reload10 = 1.2;
	//каменные сундуки
	locations[n].private1.closed = true;
	locations[n].private1.items.KnifeAztec = 1;
	locations[n].private1.items.shotgun_cartridge = 5;
	locations[n].private1.items.GunCap_colt = 5;
	locations[n].private1.items.indian1 = 5;
	locations[n].private1.items.indian2 = 7;
	locations[n].private1.items.indian3 = 11;
	locations[n].private1.items.indian4 = 15;
	locations[n].private1.items.indian5 = 4;
	locations[n].private1.items.indian6 = 16;

	locations[n].private2.closed = true;
	locations[n].private2.money = 120100;
	locations[n].private2.items.indian10 = 11;
	locations[n].private2.items.indian11 = 12;
	locations[n].private2.items.indian12 = 15;
	locations[n].private2.items.indian13 = 7;
	locations[n].private2.items.indian14 = 9;
	locations[n].private2.items.indian15 = 4;
	locations[n].private2.items.indian16 = 13;
	locations[n].private2.items.indian17 = 8;
	locations[n].private2.items.indian18 = 6;
	locations[n].private2.items.indian19 = 12;
	locations[n].private2.items.indian20 = 4;
	locations[n].private2.items.indian21 = 7;
	locations[n].private2.items.indian22 = 11;

	locations[n].private3.items.Totem_12 = 1;
	locations[n].private3.items.indian7 = 1;
	locations[n].private3.items.indian8 = 2;
	locations[n].private3.items.indian9 = 2;

	locations[n].private4.money = 17423;
	locations[n].private4.items.talisman6 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан Круглый Храм
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Temple_round";
	locations[n].id.label = "TempleRoundInside";
	locations[n].filespath.models = "locations\TenochtitlanInside\TempleRoundInside";
	locations[n].image = "loading\jonny_load\quest\TempleRoundInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TempleRoundInside = "TempleRoundInside";
	locations[n].models.always.locators = "TempleRoundInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TempleRoundInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleRoundInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple31";
	locations[n].locators_radius.item.item1 = 1.6;

	locations[n].box1 = Items_MakeTime(0, 0, 1, 2003);
	locations[n].box1.items.pistol7 = 1;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан Храм Черепов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Skulls";
	locations[n].id.label = "TempleSecondInside";
	Locations[n].image = "loading\jonny_load\quest\TempleSecondInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	Locations[n].filespath.models = "Locations\TenochtitlanInside\TempleSecondInside\";
	Locations[n].models.always.Temple = "TempleSecondInside";
	Locations[n].models.always.locators = "TempleSecondInside_locators";
	//Day
	locations[n].models.day.charactersPatch = "TempleSecondInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleSecondInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple35";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple36";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple37";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан Затопленный Храм левый
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Underwater_left";
	locations[n].id.label = "TempleUnderwater";
	Locations[n].image = "loading\jonny_load\quest\TempleUnderwater.tga";
	//Sound
	locations[n].type = "underwater";
	locations[n].changeAnimation = MainChAnim+"_swim"; //сменить анимацию на плавание
	//Models
	//Always
	Locations[n].filespath.models = "Locations\TenochtitlanInside\TempleUnderwater\";
	Locations[n].models.always.Temple = "TempleUnderwater";
	//Locations[n].models.always.Temple.tech = "DLightModel";
	Locations[n].models.always.reflect = "TempleUnderwater_reflect";
	//Locations[n].models.always.reflect.tech = "DLightModel";
	Locations[n].models.always.reflect.sea_reflection = 1;
	Locations[n].models.always.locators = "TempleUnderwater_locators";
	//Day
	locations[n].models.day.charactersPatch = "TempleUnderwater_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleUnderwater_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	Locations[n].lockWeather = "Inside";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadU2";
	locations[n].reload.l1.autoreload = "1";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Temple_great";
	locations[n].reload.l2.emerge = "reload10";
	locations[n].reload.l2.autoreload = "1";
	locations[n].locators_radius.reload.reload1_back = 0.4;
	locations[n].locators_radius.reload.reload2_back = 0.4;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан Затопленный Храм правый
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Underwater_right";
	locations[n].id.label = "TempleUnderwater";
	Locations[n].image = "loading\jonny_load\quest\TempleUnderwater.tga";
	//Sound
	locations[n].type = "underwater";
	locations[n].changeAnimation = MainChAnim+"_swim"; //сменить анимацию на плавание
	//Models
	//Always
	Locations[n].filespath.models = "Locations\TenochtitlanInside\TempleUnderwater\";
	Locations[n].models.always.Temple = "TempleUnderwater";
	//Locations[n].models.always.Temple.tech = "DLightModel";
	Locations[n].models.always.reflect = "TempleUnderwater_reflect";
	//Locations[n].models.always.reflect.tech = "DLightModel";
	Locations[n].models.always.reflect.sea_reflection = 1;
	Locations[n].models.always.locators = "TempleUnderwater_locators";
	//Day
	locations[n].models.day.charactersPatch = "TempleUnderwater_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleUnderwater_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	Locations[n].lockWeather = "Inside";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadU1";
	locations[n].reload.l1.autoreload = "1";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Temple_great";
	locations[n].reload.l2.emerge = "reload9";
	locations[n].reload.l2.autoreload = "1";
	locations[n].locators_radius.reload.reload1_back = 0.4;
	locations[n].locators_radius.reload.reload2_back = 0.4;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	return n;
}
