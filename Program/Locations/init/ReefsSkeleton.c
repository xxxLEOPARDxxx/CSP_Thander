
int LocationInitReefs(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ущелье Дьявола
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	locations[n].id = "MountainPath";
	locations[n].id.label = "MountainPath";
	locations[n].image = "loading\jonny_load\shores\MountainPathDMChest.tga";
	locations[n].worldmap = "MountainPath";
	locations[n].parent_colony = "MountainPath";
	//Sound
	locations[n].type = "MountainPath";
	locations[n].islandId = "Reefs";
	locations[n].onUninhabitedIsland = true;
	locations[n].DisableEncounters = true;
	locations[n].questflower = 1;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\MountainPathDMChest";
	Locations[n].models.always.shore = "MountainPathDMChest";
	locations[n].models.always.shore.sea_reflection = 1;
	Locations[n].models.always.seabed = "MountainPathDMChest_sb";
	Locations[n].models.always.locators = "MountainPathDMChest_locators";

	Locations[n].models.always.grassPatch = "MountainPath_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.Waterfall1 = "WaterFall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.6;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;

	Locations[n].models.always.Waterfall2 = "WaterFall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 49;
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;

	//Day
	locations[n].models.day.charactersPatch = "MountainPathDMChest_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "MountainPathDMChest_patch_day";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
    Locations[n].reload.l1.go = "Reefs";
    Locations[n].reload.l1.emerge = "reload_2";
    Locations[n].reload.l1.autoreload = "0";
    Locations[n].reload.l1.label = "Sea";
	Locations[n].locators_radius.reload.reload1_back = 2.5;

	Locations[n].locators_radius.item.splash1 = 1.0;
	Locations[n].locators_radius.item.splash2 = 1.0;
	Locations[n].locators_radius.item.splash3 = 1.0;
	Locations[n].locators_radius.item.splash4 = 1.0;
	Locations[n].locators_radius.item.splash5 = 1.0;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта проклятых
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DeckWithReefs";
	locations[n].id.label = "DeckWithReefs";
	locations[n].filespath.models = "locations\Outside\Shores\GuardGrot";
	locations[n].image = "loading\jonny_load\shores\GuardGrot.tga";
	//Sound
	locations[n].type = "DeckWithReefs";
 	locations[n].islandId = "Reefs";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].models.always.grot = "Grotto1";
	locations[n].models.always.grot.sea_reflection = 1;
	locations[n].models.always.seabed = "Grotto1_sb";
	locations[n].models.always.grassPatch = "Grotto1_grass";
	locations[n].models.always.locators = "Grotto1_locators";

	locations[n].models.always.Cfall = "Cfall";
	locations[n].models.always.Water = "Water";

	Locations[n].models.always.Waterfall1 = "Waterfall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.7;
	Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;

	Locations[n].models.always.Waterfall2 = "Waterfall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
	Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 50;
	//Day
	locations[n].models.day.charactersPatch = "Grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "Grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Reefs";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1 = 3.0;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Reefs_Chapter";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "";
	locations[n].reload.l2.disable = true;

	// locations[n].DisableOfficers = "1";

	string sloc;
	int i;
	for (i=1; i<=95; i++)
	{
		sloc = "fire"+i;
		locations[n].locators_radius.item.(sloc) = 1.0;
	}
	for (i=1; i<=4; i++)
	{
		sloc = "incasfire"+i;
		locations[n].locators_radius.item.(sloc) = 1.5;
	}
	Locations[n].locators_radius.item.item1 = 1.5;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////	Капитул		//////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Reefs_Chapter";
	locations[n].id.label = "";
	locations[n].image = "loading\jonny_load\inside\Maltains.tga";
	//Town sack
	locations[n].type = "Reefs_Chapter";
	// locations[n].townsack = "FortFrance";
	locations[n].islandId = "Reefs";
	//Sound
	// locations[n].fastreload = "FortFrance";
	// locations[n].Maltains = true;
	//Always
	locations[n].filespath.models = "locations\inside\Maltains";
	locations[n].models.always.Maltains = "Malta_Base";
	locations[n].models.always.InquisitionMaltainsFonars = "Malta_fonars";
	locations[n].models.always.locators = "Malta_locators";

	//Day
	locations[n].models.day.charactersPatch = "Malta_patch";
	//Night
	locations[n].models.night.charactersPatch = "Malta_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "DeckWithReefs";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "DeckWithReefs";

	LAi_LocationFightDisable(&locations[n], true);

	// locations[n].reload.l2.name = "reload2";
	// locations[n].reload.l2.go = "FortFrance_town";
	// locations[n].reload.l2.emerge = "basement1";
	// locations[n].reload.l2.autoreload = "0";
    // locations[n].reload.l2.label = "Street";

	n = n + 1;

	return n;
}
