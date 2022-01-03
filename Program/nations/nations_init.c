void InitNations()
{
	ref rNation;
	//England
	makeref(rNation,Nations[ENGLAND]);
	rNation.Name = "England";
	rNation.ShortName = "Eng";
	rNation.worldMapShip = "british";
	rNation.fort = 0;  // колво фортов у нации, заполняется само в начале, методом CreateColonyCommanders
	//Location fantom models
	rNation.fantomModel.m0 = "off_eng_1";
	rNation.fantomModel.m1 = "off_eng_2";
	rNation.fantomModel.m2 = "sold_eng_1";
	rNation.fantomModel.m3 = "sold_eng_2";
	rNation.fantomModel.m4 = "sold_eng_3";
	rNation.fantomModel.m5 = "sold_eng_4";
	rNation.fantomModel.m6 = "sold_eng_5";
	rNation.fantomModel.m7 = "sold_eng_6";
	rNation.fantomModel.m8 = "sold_eng_7";
	rNation.fantomModel.m9 = "sold_eng_8";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_eng_1";// "off_eng_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_eng_2";// "off_eng_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_eng_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_eng_2";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_eng_3";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_eng_4";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_eng_5";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_eng_6";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_eng_7";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_eng_8";
	rNation.boardingModel.enemy.m10.ani = "man";



	//France
	makeref(rNation,Nations[FRANCE]);
	rNation.Name = "France";
	rNation.ShortName = "Fra";
	rNation.worldMapShip = "french";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "off_fra_1";
	rNation.fantomModel.m1 = "off_fra_2";
	rNation.fantomModel.m2 = "sold_fra_1";
	rNation.fantomModel.m3 = "sold_fra_2";
	rNation.fantomModel.m4 = "sold_fra_3";
	rNation.fantomModel.m5 = "sold_fra_4";
	rNation.fantomModel.m6 = "sold_fra_5";
	rNation.fantomModel.m7 = "sold_fra_6";
	rNation.fantomModel.m8 = "sold_fra_7";
	rNation.fantomModel.m9 = "sold_fra_8";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_fra_1"; // "off_fra_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_fra_2"; // "off_fra_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_fra_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_fra_2";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_fra_3";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_fra_4";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_fra_5";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_fra_6";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_fra_7";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_fra_8";
	rNation.boardingModel.enemy.m10.ani = "man";


	//Spain
	makeref(rNation,Nations[SPAIN]);
	rNation.Name = "Spain";
	rNation.ShortName = "Spa";
	rNation.worldMapShip = "spanish";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "off_spa_1";
	rNation.fantomModel.m1 = "off_spa_2";
	rNation.fantomModel.m2 = "sold_spa_1";
	rNation.fantomModel.m3 = "sold_spa_2";
	rNation.fantomModel.m4 = "sold_spa_3";
	rNation.fantomModel.m5 = "sold_spa_4";
	rNation.fantomModel.m6 = "sold_spa_5";
	rNation.fantomModel.m7 = "sold_spa_6";
	rNation.fantomModel.m8 = "sold_spa_7";
	rNation.fantomModel.m9 = "sold_spa_8";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_spa_1"; // "off_spa_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_spa_2"; // "off_spa_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_spa_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_spa_2";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_spa_3";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_spa_4";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_spa_5";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_spa_6";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_spa_7";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_spa_8";
	rNation.boardingModel.enemy.m10.ani = "man";

	//Pirate
	makeref(rNation,Nations[PIRATE]);
	rNation.Name = "Pirate";
	rNation.ShortName = "Pir";
	rNation.worldMapShip = "pirates";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "pirate_1";
	//Boarding models
	rNation.boardingModel.enemy.m0 = "pirate_1";
	rNation.boardingModel.enemy.m0.ani = "man";
	rNation.boardingModel.enemy.m1 = "pirate_2";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "pirate_3";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "pirate_4";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "pirate_5";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "pirate_6";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "pirate_7";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "pirate_8";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "pirate_9";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "pirate_10";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "pirate_11";
	rNation.boardingModel.enemy.m10.ani = "man";
	rNation.boardingModel.enemy.m11 = "pirate_12";
	rNation.boardingModel.enemy.m11.ani = "man";
	rNation.boardingModel.enemy.m12 = "pirate_13";
	rNation.boardingModel.enemy.m12.ani = "man";
	rNation.boardingModel.enemy.m13 = "pirate_14";
	rNation.boardingModel.enemy.m13.ani = "man";
	rNation.boardingModel.enemy.m14 = "pirate_15";
	rNation.boardingModel.enemy.m14.ani = "man";
	rNation.boardingModel.enemy.m15 = "pirate_16";
	rNation.boardingModel.enemy.m15.ani = "man";
	rNation.boardingModel.enemy.m16 = "pirate_17";
	rNation.boardingModel.enemy.m16.ani = "man";
	rNation.boardingModel.enemy.m17 = "pirate_18";
	rNation.boardingModel.enemy.m17.ani = "man";
	rNation.boardingModel.enemy.m18 = "pirate_19";
	rNation.boardingModel.enemy.m18.ani = "man";
	rNation.boardingModel.enemy.m19 = "pirate_20";
	rNation.boardingModel.enemy.m19.ani = "man";
	rNation.boardingModel.enemy.m20 = "pirate_21";
	rNation.boardingModel.enemy.m20.ani = "man";
	rNation.boardingModel.enemy.m21 = "pirate_22";
	rNation.boardingModel.enemy.m21.ani = "man";
	rNation.boardingModel.enemy.m22 = "pirate_23";
	rNation.boardingModel.enemy.m22.ani = "man";
	rNation.boardingModel.enemy.m23 = "pirate_24";
	rNation.boardingModel.enemy.m23.ani = "man";
	rNation.boardingModel.enemy.m24 = "pirate_25";
	rNation.boardingModel.enemy.m24.ani = "man";

	//Holland
	makeref(rNation,Nations[HOLLAND]);
	rNation.Name = "Holland";
	rNation.ShortName = "Hol";
	rNation.worldMapShip = "dutch";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "Off_hol_1";
	rNation.fantomModel.m1 = "Off_hol_2";
	rNation.fantomModel.m2 = "sold_hol_1";
	rNation.fantomModel.m3 = "sold_hol_2";
	rNation.fantomModel.m4 = "sold_hol_3";
	rNation.fantomModel.m5 = "sold_hol_4";
	rNation.fantomModel.m6 = "sold_hol_5";
	rNation.fantomModel.m7 = "sold_hol_6";
	rNation.fantomModel.m8 = "sold_hol_7";
	rNation.fantomModel.m9 = "sold_hol_8";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_hol_1"; // "Off_hol_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_hol_2"; // "Off_hol_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_hol_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_hol_2";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_hol_3";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_hol_4";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_hol_5";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_hol_6";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_hol_7";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_hol_8";
	rNation.boardingModel.enemy.m10.ani = "man";


	//Player boarding command
	for(int i = 0; i < MAX_NATIONS; i++)
	{
		// --> LEO: Матросы ГГ
		makeref(rNation,Nations[i]);
		rNation.boardingModel.player.m0 = "shipowner_20";
		rNation.boardingModel.player.m0.ani = "man";
		rNation.boardingModel.player.m1 = "shipowner_21";
		rNation.boardingModel.player.m1.ani = "man";
		rNation.boardingModel.player.m2 = "shipowner_22";
		rNation.boardingModel.player.m2.ani = "man";
		rNation.boardingModel.player.m3 = "shipowner_23";
		rNation.boardingModel.player.m3.ani = "man";
		rNation.boardingModel.player.m4 = "shipowner_24";
		rNation.boardingModel.player.m4.ani = "man";
		rNation.boardingModel.player.m5 = "shipowner_25";
		rNation.boardingModel.player.m5.ani = "man";
		rNation.boardingModel.player.m6 = "shipowner_26";
		rNation.boardingModel.player.m6.ani = "man";
		rNation.boardingModel.player.m7 = "shipowner_27";
		rNation.boardingModel.player.m7.ani = "man";
		rNation.boardingModel.player.m8 = "shipowner_28";
		rNation.boardingModel.player.m8.ani = "man";
		rNation.boardingModel.player.m9 = "shipowner_29";
		rNation.boardingModel.player.m9.ani = "man";
		// <-- LEO: Матросы ГГ

		// --> LEO: Торговцы
		rNation.boardingModel.merchant.m0 = "shipowner_1";
		rNation.boardingModel.merchant.m0.ani = "man";
		rNation.boardingModel.merchant.m1 = "shipowner_2";
		rNation.boardingModel.merchant.m1.ani = "man";
		rNation.boardingModel.merchant.m2 = "shipowner_5";
		rNation.boardingModel.merchant.m2.ani = "man";
		rNation.boardingModel.merchant.m3 = "shipowner_6";
		rNation.boardingModel.merchant.m3.ani = "man";
		rNation.boardingModel.merchant.m4 = "shipowner_7";
		rNation.boardingModel.merchant.m4.ani = "man";
		rNation.boardingModel.merchant.m5 = "shipowner_8";
		rNation.boardingModel.merchant.m5.ani = "man";
		rNation.boardingModel.merchant.m6 = "shipowner_9";
		rNation.boardingModel.merchant.m6.ani = "man";
		rNation.boardingModel.merchant.m7 = "shipowner_10";
		rNation.boardingModel.merchant.m7.ani = "man";
		rNation.boardingModel.merchant.m8 = "shipowner_11";
		rNation.boardingModel.merchant.m8.ani = "man";
		rNation.boardingModel.merchant.m9 = "shipowner_12";
		rNation.boardingModel.merchant.m9.ani = "man";
		rNation.boardingModel.merchant.m10 = "shipowner_13";
		rNation.boardingModel.merchant.m10.ani = "man";
		rNation.boardingModel.merchant.m11 = "shipowner_14";
		rNation.boardingModel.merchant.m11.ani = "man";
		rNation.boardingModel.merchant.m12 = "shipowner_15";
		rNation.boardingModel.merchant.m12.ani = "man";
		rNation.boardingModel.merchant.m13 = "shipowner_16";
		rNation.boardingModel.merchant.m13.ani = "man";
		rNation.boardingModel.merchant.m14 = "shipowner_17";
		rNation.boardingModel.merchant.m14.ani = "man";
		rNation.boardingModel.merchant.m15 = "shipowner_18";
		rNation.boardingModel.merchant.m15.ani = "man";
		rNation.boardingModel.merchant.m16 = "shipowner_19";
		rNation.boardingModel.merchant.m16.ani = "man";
		rNation.boardingModel.merchant.m17 = "citiz_2";
		rNation.boardingModel.merchant.m17.ani = "man";
		rNation.boardingModel.merchant.m18 = "citiz_3";
		rNation.boardingModel.merchant.m18.ani = "man";
		rNation.boardingModel.merchant.m19 = "citiz_5";
		rNation.boardingModel.merchant.m19.ani = "man";
		rNation.boardingModel.merchant.m20 = "citiz_7";
		rNation.boardingModel.merchant.m20.ani = "man";
		rNation.boardingModel.merchant.m21 = "citiz_11";
		rNation.boardingModel.merchant.m21.ani = "man";
		// <-- LEO: Торговцы
	}

	//Trace("Init nations complete.");
}

