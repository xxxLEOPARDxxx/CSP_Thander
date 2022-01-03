string	sEnManFaces = "30,35,10,6,32,33,42,43";
string	sFrManFaces = "19,27,29,31,32,33,43,43";
string	sSpManFaces = "25,37,38,44,7,32,33,42,43";
string	sHoManFaces = "11,26,28,36,32,33,42,43";
string	sPoManFaces = "12,30,39,32,33,42,43";
string	sPiManFaces = "0,1,13,14,2,23,24,3,40,5";

void SetRandomFaceToCharacter(ref rCharacter)
{
	string sFaceID = "1";
	if (rCharacter.sex == "man")
	{
		switch (sti(rCharacter.nation))
		{
			case ENGLAND:
				sFaceID = GetRandSubString(sEnManFaces);
			break;
			case FRANCE:
				sFaceID = GetRandSubString(sFrManFaces);
			break;
			case SPAIN:
				sFaceID = GetRandSubString(sSpManFaces);
				break;
			case PIRATE:
				sFaceID = GetRandSubString(sPiManFaces);
				break;
			case HOLLAND:
				sFaceID = GetRandSubString(sHoManFaces);
				break;
		}
	}
	else
	{
		sFaceID = "16";
	}

	rCharacter.FaceId = sti(sFaceID);
}

void FaceMaker(aref rCharacter)
{
	// Warship 07.07.09 Пасхалка с кораблем "Мэри Селест" - за место лица кэпа - море с облаками
	if(rCharacter.ID == "MaryCelesteCapitan")
	{
		rCharacter.FaceId = 333;
		return;
	}

	switch (rCharacter.model)
	{
		case "beatrice":		rCharacter.FaceId = 0; break;
		case "beatriceA":		rCharacter.FaceId = 0; break;
		case "devlin":			rCharacter.FaceId = 1; break;
		case "barmen_1":		rCharacter.FaceId = 2; break;
		case "barmen_2":		rCharacter.FaceId = 3; break;
		case "barmen_3":		rCharacter.FaceId = 4; break;
		case "barmen_4":		rCharacter.FaceId = 5; break;
		case "barmen_5":		rCharacter.FaceId = 6; break;
		case "barmen_6":		rCharacter.FaceId = 7; break;
		case "barmen_7":		rCharacter.FaceId = 8; break;
		case "barmen_8":		rCharacter.FaceId = 9; break;
		case "barmen_9":		rCharacter.FaceId = 10; break;
		case "barmen_10":		rCharacter.FaceId = 11; break;
		case "barmen_11":		rCharacter.FaceId = 12; break;
		case "barmen_12":		rCharacter.FaceId = 13; break;
		case "barmen_13":		rCharacter.FaceId = 14; break;
		case "barmen_14":		rCharacter.FaceId = 15; break;
		case "barmen_15":		rCharacter.FaceId = 16; break;
		case "barmen_16":		rCharacter.FaceId = 17; break;
		// --> Офицеры
		case "officer_1":		rCharacter.FaceId = 18; break;
		case "officer_2":		rCharacter.FaceId = 19; break;
		case "officer_3":		rCharacter.FaceId = 20; break;
		case "officer_4":		rCharacter.FaceId = 21; break;
		case "officer_5":		rCharacter.FaceId = 22; break;
		case "officer_6":		rCharacter.FaceId = 23; break;
		case "officer_7":		rCharacter.FaceId = 24; break;
		case "officer_8":		rCharacter.FaceId = 25; break;
		case "officer_9":		rCharacter.FaceId = 26; break;
		case "officer_10":		rCharacter.FaceId = 27; break;
		case "officer_11":		rCharacter.FaceId = 28; break;
		case "officer_12":		rCharacter.FaceId = 29; break;
		case "officer_13":		rCharacter.FaceId = 30; break;
		case "officer_14":		rCharacter.FaceId = 31; break;
		case "officer_15":		rCharacter.FaceId = 32; break;
		case "officer_16":		rCharacter.FaceId = 33; break;
		case "officer_17":		rCharacter.FaceId = 34; break;
		case "officer_18":		rCharacter.FaceId = 35; break;
		case "officer_19":		rCharacter.FaceId = 36; break;
		case "officer_20":		rCharacter.FaceId = 37; break;
		case "officer_21":		rCharacter.FaceId = 401; break;
		case "officer_22":		rCharacter.FaceId = 402; break;
		case "officer_23":		rCharacter.FaceId = 403; break;
		case "officer_24":		rCharacter.FaceId = 456; break;
		case "officer_25":		rCharacter.FaceId = 405; break;
		case "officer_26":		rCharacter.FaceId = 406; break;
		case "officer_27":		rCharacter.FaceId = 408; break;
		case "officer_28":		rCharacter.FaceId = 409; break;
		case "officer_29":		rCharacter.FaceId = 410; break;
		case "officer_30":		rCharacter.FaceId = 411; break;
		case "officer_31":		rCharacter.FaceId = 454; break;
		case "officer_32":		rCharacter.FaceId = 413; break;
		case "officer_33":		rCharacter.FaceId = 451; break;
		case "officer_34":		rCharacter.FaceId = 415; break;
		case "officer_35":		rCharacter.FaceId = 416; break;
		case "officer_36":		rCharacter.FaceId = 418; break;
		case "officer_37":		rCharacter.FaceId = 450; break;
		case "officer_38":		rCharacter.FaceId = 420; break;
		case "officer_39": 		rCharacter.FaceId = 429; break;
		case "officer_40": 		rCharacter.FaceId = 430; break;
		case "officer_41": 		rCharacter.FaceId = 431; break;
		case "officer_42": 		rCharacter.FaceId = 433; break;
		case "officer_43": 		rCharacter.FaceId = 168; break;
		case "officer_44": 		rCharacter.FaceId = 436; break;
		case "officer_45": 		rCharacter.FaceId = 437; break;
		case "officer_46": 		rCharacter.FaceId = 438; break;
		case "officer_47": 		rCharacter.FaceId = 442; break;
		case "officer_48": 		rCharacter.FaceId = 444; break;
		case "officer_49": 		rCharacter.FaceId = 445; break;
		case "officer_50": 		rCharacter.FaceId = 447; break;
		case "officer_51": 		rCharacter.FaceId = 448; break;
		case "officer_52": 		rCharacter.FaceId = 449; break;
		case "officer_53":		rCharacter.FaceId = 455; break;
		case "officer_54":		rCharacter.FaceId = 473; break;
		case "officer_55":		rCharacter.FaceId = 474; break;
		case "officer_56":		rCharacter.FaceId = 475; break;
		case "officer_57":		rCharacter.FaceId = 476; break;
		case "officer_58":		rCharacter.FaceId = 477; break;
		case "officer_59":		rCharacter.FaceId = 421; break;
		case "officer_60":		rCharacter.FaceId = 422; break;
		case "officer_61":		rCharacter.FaceId = 423; break;
		case "officer_62":		rCharacter.FaceId = 424; break;
		case "officer_63":		rCharacter.FaceId = 425; break;
		case "officer_64":		rCharacter.FaceId = 426; break;
		// <-- Офицеры

		// --> ПКМ рабы
		case "PKM_rab_1":		rCharacter.FaceId = 478; break;
		case "PKM_rab_2":		rCharacter.FaceId = 478; break;
		case "PKM_rab_3":		rCharacter.FaceId = 478; break;
		case "PKM_rab_4":		rCharacter.FaceId = 478; break;
		// <-- ПКМ рабы

		// --> ОЗГи
		case "OZG_1":		rCharacter.FaceId = 461; break;
		case "OZG_2":		rCharacter.FaceId = 462; break;
		case "OZG_3":		rCharacter.FaceId = 460; break;
		case "OZG_4":		rCharacter.FaceId = 419; break;
		case "OZG_5":		rCharacter.FaceId = 432; break;
		case "OZG_6":		rCharacter.FaceId = 404; break;
		case "OZG_7":		rCharacter.FaceId = 412; break;
		case "OZG_8":		rCharacter.FaceId = 414; break;
		case "OZG_9":		rCharacter.FaceId = 417; break;
		case "OZG_10":		rCharacter.FaceId = 407; break;
		// <-- ОЗГи

		case "citiz_1":			rCharacter.FaceId = 38; break;
		case "citiz_2":			rCharacter.FaceId = 39; break;
		case "citiz_3":			rCharacter.FaceId = 40; break;
		case "citiz_4":			rCharacter.FaceId = 41; break;
		case "citiz_5":			rCharacter.FaceId = 42; break;
		case "citiz_6":			rCharacter.FaceId = 43; break;
		case "citiz_7":			rCharacter.FaceId = 44; break;
		case "citiz_8":			rCharacter.FaceId = 45; break;
		case "citiz_9":			rCharacter.FaceId = 46; break;
		case "citiz_10":		rCharacter.FaceId = 47; break;
		case "citiz_11":		rCharacter.FaceId = 48; break;
		case "citiz_12":		rCharacter.FaceId = 49; break;

		case "girl_1":			rCharacter.FaceId = 50; break;
		case "girl_2":			rCharacter.FaceId = 51; break;
		case "girl_3":			rCharacter.FaceId = 52; break;
		case "girl_4":			rCharacter.FaceId = 53; break;
		case "girl_5":			rCharacter.FaceId = 54; break;
		case "girl_6":			rCharacter.FaceId = 55; break;
		case "girl_7":			rCharacter.FaceId = 56; break;
		case "girl_8":			rCharacter.FaceId = 57; break;

		case "head_pir":		rCharacter.FaceId = 58; break;
		case "huber_eng":		rCharacter.FaceId = 59; break;
		case "huber_fra":		rCharacter.FaceId = 60; break;
		case "huber_spa":		rCharacter.FaceId = 61; break;
		case "huber_hol":		rCharacter.FaceId = 62; break;

		case "lady_1":			rCharacter.FaceId = 63; break;
		case "lady_2":			rCharacter.FaceId = 64; break;
		case "lady_3":			rCharacter.FaceId = 65; break;
		case "lady_4":			rCharacter.FaceId = 66; break;
		case "lady_5":			rCharacter.FaceId = 67; break;
		case "lady_6":			rCharacter.FaceId = 68; break;

		case "off_eng_1":		rCharacter.FaceId = 69; break;
		case "off_eng_2":		rCharacter.FaceId = 70; break;
		case "off_fra_1":		rCharacter.FaceId = 71; break;
		case "off_fra_2":		rCharacter.FaceId = 72; break;
		case "off_spa_1":		rCharacter.FaceId = 73; break;
		case "off_spa_2":		rCharacter.FaceId = 74; break;
		case "off_hol_1":		rCharacter.FaceId = 75; break;
		case "off_hol_2":		rCharacter.FaceId = 76; break;
		// --> Пиратская команда абордажа
		case "pirate_1":		rCharacter.FaceId = 77; break;
		case "pirate_2":		rCharacter.FaceId = 78; break;
		case "pirate_3":		rCharacter.FaceId = 79; break;
		case "pirate_4":		rCharacter.FaceId = 80; break;
		case "pirate_5":		rCharacter.FaceId = 81; break;
		case "pirate_6":		rCharacter.FaceId = 82; break;
		case "pirate_7":		rCharacter.FaceId = 83; break;
		case "pirate_8":		rCharacter.FaceId = 84; break;
		case "pirate_9":		rCharacter.FaceId = 85; break;
		case "pirate_10":		rCharacter.FaceId = 86; break;
		case "pirate_11":		rCharacter.FaceId = 169; break;
		case "pirate_12":		rCharacter.FaceId = 170; break;
		case "pirate_13":		rCharacter.FaceId = 171; break;
		case "pirate_14":		rCharacter.FaceId = 172; break;
		case "pirate_15":		rCharacter.FaceId = 173; break;
		// --> Сюжетка Чёрных парусов
		case "BS_Billy":		rCharacter.FaceId = 300; break;
		case "BS_Bony":			rCharacter.FaceId = 301; break;
		case "BS_Flint_0":		rCharacter.FaceId = 302; break;
		case "BS_Gatry":		rCharacter.FaceId = 303; break;
		case "BS_Maks":			rCharacter.FaceId = 304; break;
		case "BS_Rakham":		rCharacter.FaceId = 305; break;
		case "BS_Silver":		rCharacter.FaceId = 306; break;
		case "BS_Vein":			rCharacter.FaceId = 307; break;
		// <-- Сюжетка Чёрных парусов
		case "pirate_16":		rCharacter.FaceId = 435; break;
		case "pirate_17":		rCharacter.FaceId = 439; break;
		case "pirate_18":		rCharacter.FaceId = 440; break;
		case "pirate_19":		rCharacter.FaceId = 441; break;
		case "pirate_20":		rCharacter.FaceId = 452; break;
		case "pirate_21":		rCharacter.FaceId = 453; break;
		case "pirate_22":		rCharacter.FaceId = 457; break;
		case "pirate_23":		rCharacter.FaceId = 458; break;
		case "pirate_24":		rCharacter.FaceId = 459; break;
		case "pirate_25":		rCharacter.FaceId = 434; break;
		// <-- Пиратская команда абордажа
		case "priest_1":		rCharacter.FaceId = 87; break;
		case "priest_2":		rCharacter.FaceId = 88; break;
		case "priest_3":		rCharacter.FaceId = 89; break;
		case "priest_4":		rCharacter.FaceId = 90; break;
		// --> Команда абордажа ИГРОКА
		case "shipowner_1":		rCharacter.FaceId = 91; break;
		case "shipowner_2":		rCharacter.FaceId = 92; break;
		case "shipowner_3":		rCharacter.FaceId = 93; break;
		case "shipowner_4":		rCharacter.FaceId = 94; break;
		case "shipowner_5":		rCharacter.FaceId = 95; break;
		case "shipowner_6":		rCharacter.FaceId = 96; break;
		case "shipowner_7":		rCharacter.FaceId = 97; break;
		case "shipowner_8":		rCharacter.FaceId = 98; break;
		case "shipowner_9":		rCharacter.FaceId = 99; break;
		case "shipowner_10":	rCharacter.FaceId = 100; break;
		case "shipowner_11":	rCharacter.FaceId = 101; break;
		case "shipowner_12":	rCharacter.FaceId = 102; break;
		case "shipowner_13":	rCharacter.FaceId = 103; break;
		case "shipowner_14":	rCharacter.FaceId = 104; break;
		case "shipowner_15":	rCharacter.FaceId = 105; break;
		case "shipowner_16":	rCharacter.FaceId = 106; break;
		case "shipowner_17":	rCharacter.FaceId = 106; break;
		case "shipowner_18":	rCharacter.FaceId = 106; break;
		case "shipowner_19":	rCharacter.FaceId = 106; break;
		case "shipowner_20":	rCharacter.FaceId = 472; break;
		case "shipowner_21":	rCharacter.FaceId = 471; break;
		case "shipowner_22":	rCharacter.FaceId = 470; break;
		case "shipowner_23":	rCharacter.FaceId = 469; break;
		case "shipowner_24":	rCharacter.FaceId = 467; break;
		case "shipowner_25":	rCharacter.FaceId = 467; break;
		case "shipowner_26":	rCharacter.FaceId = 466; break;
		case "shipowner_27":	rCharacter.FaceId = 465; break;
		case "shipowner_28":	rCharacter.FaceId = 464; break;
		case "shipowner_29":	rCharacter.FaceId = 463; break;
		// <-- Команда абордажа ИГРОКА
		case "smuggler_boss":	rCharacter.FaceId = 107; break;

		case "sold_hol_1":		rCharacter.FaceId = 108; break;
		case "sold_hol_2":		rCharacter.FaceId = 109; break;
		case "sold_hol_3":		rCharacter.FaceId = 110; break;
		case "sold_hol_4":		rCharacter.FaceId = 111; break;
		case "sold_hol_5":		rCharacter.FaceId = 112; break;
		case "sold_hol_6":		rCharacter.FaceId = 113; break;
		case "sold_hol_7":		rCharacter.FaceId = 114; break;
		case "sold_hol_8":		rCharacter.FaceId = 115; break;

		case "sold_eng_1":		rCharacter.FaceId = 116; break;
		case "sold_eng_2":		rCharacter.FaceId = 117; break;
		case "sold_eng_3":		rCharacter.FaceId = 118; break;
		case "sold_eng_4":		rCharacter.FaceId = 119; break;
		case "sold_eng_5":		rCharacter.FaceId = 120; break;
		case "sold_eng_6":		rCharacter.FaceId = 121; break;
		case "sold_eng_7":		rCharacter.FaceId = 122; break;
		case "sold_eng_8":		rCharacter.FaceId = 123; break;

		case "sold_fra_1":		rCharacter.FaceId = 124; break;
		case "sold_fra_2":		rCharacter.FaceId = 125; break;
		case "sold_fra_3":		rCharacter.FaceId = 126; break;
		case "sold_fra_4":		rCharacter.FaceId = 127; break;
		case "sold_fra_5":		rCharacter.FaceId = 128; break;
		case "sold_fra_6":		rCharacter.FaceId = 129; break;
		case "sold_fra_7":		rCharacter.FaceId = 130; break;
		case "sold_fra_8":		rCharacter.FaceId = 131; break;

		case "sold_spa_1":		rCharacter.FaceId = 131; break;
		case "sold_spa_2":		rCharacter.FaceId = 133; break;
		case "sold_spa_3":		rCharacter.FaceId = 134; break;
		case "sold_spa_4":		rCharacter.FaceId = 135; break;
		case "sold_spa_5":		rCharacter.FaceId = 136; break;
		case "sold_spa_6":		rCharacter.FaceId = 137; break;
		case "sold_spa_7":		rCharacter.FaceId = 138; break;
		case "sold_spa_8":		rCharacter.FaceId = 139; break;

		case "trader_1":		rCharacter.FaceId = 140; break;
		case "trader_2":		rCharacter.FaceId = 141; break;
		case "trader_3":		rCharacter.FaceId = 142; break;
		case "trader_4":		rCharacter.FaceId = 143; break;
		case "trader_5":		rCharacter.FaceId = 144; break;
		case "trader_6":		rCharacter.FaceId = 145; break;
		case "trader_7":		rCharacter.FaceId = 146; break;
		case "trader_8":		rCharacter.FaceId = 147; break;
		case "trader_9":		rCharacter.FaceId = 148; break;
		case "trader_10":		rCharacter.FaceId = 149; break;
		case "trader_11":		rCharacter.FaceId = 150; break;
		case "trader_12":		rCharacter.FaceId = 151; break;
		case "trader_13":		rCharacter.FaceId = 152; break;
		case "trader_14":		rCharacter.FaceId = 153; break;
		case "trader_15":		rCharacter.FaceId = 154; break;
		case "trader_16":		rCharacter.FaceId = 155; break;

		case "usurer_1":		rCharacter.FaceId = 156; break;
		case "usurer_2": 		rCharacter.FaceId = 157; break;
		case "usurer_3":		rCharacter.FaceId = 158; break;
		case "usurer_4":		rCharacter.FaceId = 159; break;
		case "usurer_5":		rCharacter.FaceId = 160; break;
		case "usurer_6":		rCharacter.FaceId = 161; break;
		case "usurer_7":		rCharacter.FaceId = 162; break;
		case "usurer_8":		rCharacter.FaceId = 163; break;

		case "whore_1":			rCharacter.FaceId = 164; break;
		case "whore_2":			rCharacter.FaceId = 165; break;
		case "whore_3":			rCharacter.FaceId = 166; break;
		case "whore_4":			rCharacter.FaceId = 167; break;
		// 1.2.3 -->
		case "Daniel":			rCharacter.FaceId = 170; break;
		case "Researcher":		rCharacter.FaceId = 222; break;
		// 1.2.3 <--
		case "mushketer_1":		rCharacter.FaceId = 80; break;
		case "mushketer_2":		rCharacter.FaceId = 77; break;
		case "mushketer_3":		rCharacter.FaceId = 81; break;
		case "mushketer_4":		rCharacter.FaceId = 79; break;
		case "mushketer_5":		rCharacter.FaceId = 78; break;

		case "eng_mush_1":		rCharacter.FaceId = 116; break;
		case "eng_mush_2":		rCharacter.FaceId = 118; break;
		case "eng_mush_3":		rCharacter.FaceId = 123; break;

		case "hol_mush_1":		rCharacter.FaceId = 108; break;
		case "hol_mush_2":		rCharacter.FaceId = 109; break;
		case "hol_mush_3":		rCharacter.FaceId = 115; break;

		case "fra_mush_1":		rCharacter.FaceId = 124; break;
		case "fra_mush_2":		rCharacter.FaceId = 128; break;
		case "fra_mush_3":		rCharacter.FaceId = 130; break;

		case "spa_mush_1":		rCharacter.FaceId = 131; break;
		case "spa_mush_2":		rCharacter.FaceId = 133; break;
		case "spa_mush_3":		rCharacter.FaceId = 139; break;
		// к ПКМ моделям
		case "Corsair1_2":      rCharacter.FaceId = 198; break;
		case "AnnaDeLeiva":		rCharacter.FaceId = 199; break;
		case "Albermal":		rCharacter.FaceId = 200; break;
		case "Corsair1_3":		rCharacter.FaceId = 201; break;
		case "capitan":		    rCharacter.FaceId = 202; break;
		case "pirat00":		    rCharacter.FaceId = 203; break;
		case "MorrisWillams":   rCharacter.FaceId = 204; break;
		case "ThomasLinch":     rCharacter.FaceId = 205; break;
		case "Korsar1":         rCharacter.FaceId = 206; break;
		case "mummy":           rCharacter.FaceId = 207; break;
		case "liza":            rCharacter.FaceId = 208; break;
		case "bocman":          rCharacter.FaceId = 209; break;
		// новые модельки
		case "BigPirate":		rCharacter.FaceId = 210; break;
		case "chard":			rCharacter.FaceId = 211; break;
		case "chard2":			rCharacter.FaceId = 212; break;
		case "chard3":			rCharacter.FaceId = 213; break;
		case "Espinosa":		rCharacter.FaceId = 214; break;
		case "Hero1":			rCharacter.FaceId = 215; break;
		case "Isterling":		rCharacter.FaceId = 216; break;
		case "Morgan":			rCharacter.FaceId = 217; break;
		case "SpaOfficer1":		rCharacter.FaceId = 218; break;
		case "SpaOfficer2":		rCharacter.FaceId = 219; break;
		case "Youngman":		rCharacter.FaceId = 220; break;
		case "Blood5":			rCharacter.FaceId = 221; break;
		case "blood_bomj":		rCharacter.FaceId = 221; break;
		case "Mechanic":		rCharacter.FaceId = 222; break;
		case "capitan_2":		rCharacter.FaceId = 223; break;
		case "capitan_3":		rCharacter.FaceId = 224; break;
		case "MusketeerEnglish_1":		rCharacter.FaceId = 225; break;
		case "MusketeerEnglish_2":		rCharacter.FaceId = 225; break;
		case "Dragoon_1":		rCharacter.FaceId = 226; break;
		case "Hobart":			rCharacter.FaceId = 227; break;
		case "Sharp":			rCharacter.FaceId = 228; break;
		case "SoldierEnglish_1":		rCharacter.FaceId = 229; break;
		case "skeletcap":		rCharacter.FaceId = 231; break;
		case "girl_9":			rCharacter.FaceId = 232; break;
		case "girl_10":			rCharacter.FaceId = 233; break;
		case "Chard3a":			rCharacter.FaceId = 234; break;
		case "Danielle":		rCharacter.FaceId = 235; break;

		// Линейка Блада CSP - пять офицеров -->
		case "PBLine_Daik_0":		rCharacter.FaceId = 236; break;
		case "PBLine_Hagtorp_0":	rCharacter.FaceId = 237; break;
		case "PBLine_NedOgl_0":		rCharacter.FaceId = 238; break;
		case "PBLine_Pitt_0":		rCharacter.FaceId = 230; break;
		case "PBLine_Volverston_0":	rCharacter.FaceId = 239; break;
		// Линейка Блада CSP - пять офицеров <--

		// ГПК 1.2.5 -->
		case "PGG_Angellica":	rCharacter.FaceId = 242; break;
		case "PGG_Rumba":		rCharacter.FaceId = 488; break;

		case "YokoDias":		rCharacter.FaceId = 243; break;
		case "PGG_YokoDias_0":	rCharacter.FaceId = 243; break;

		case "Jessika":			rCharacter.FaceId = 244; break;
		// <-- ГПК 1.2.3
		//ОЗГи
		case "ozg_carlos":		rCharacter.FaceId = 281; break; //Карлос Кассир
		case "ozg_horn":		rCharacter.FaceId = 282; break; //Ганнибал Холм
		case "ozg_piRat":		rCharacter.FaceId = 283; break; //Матиас Грин-Крыса
		case "ozg_miko":		rCharacter.FaceId = 284; break; //Мико Пистольеро
		case "ozg_martin":		rCharacter.FaceId = 285; break; //Мартин ван Хален
		case "QuestCaptain":	rCharacter.FaceId = 290; break; //Джа Престон
		// Орион
		case "OffOrion":		rCharacter.FaceId = 291; break; //Мартин Блэкер
		// Мушкетеры
		case "quest_mush_1":	rCharacter.FaceId = 292; break; //саксонец
		case "quest_mush_2":	rCharacter.FaceId = 293; break; //пират
		case "Lil_Jim_0":		rCharacter.FaceId = 294; break; //Маленький Джимми
		case "CCS_Mechanic":	rCharacter.FaceId = 295; break;
		// временное решение для девиц из борделя
		case "horse01": 		rCharacter.FaceId = 164; break;
		case "horse02": 		rCharacter.FaceId = 165; break;
		case "horse03": 		rCharacter.FaceId = 166; break;
		case "horse04": 		rCharacter.FaceId = 167; break;
		case "horse05": 		rCharacter.FaceId = 164; break;
		case "horse06": 		rCharacter.FaceId = 165; break;
		case "horse07": 		rCharacter.FaceId = 166; break;
		case "horse08": 		rCharacter.FaceId = 167; break;

		case "PGG_Blad_0": 		rCharacter.FaceId = 221; break;
		case "PGG_Blad_6": 		rCharacter.FaceId = 221; break;

		case "PGG_DeLuck_0": 	rCharacter.FaceId = 481; break;
		case "PotCMobCap": 		rCharacter.FaceId = 510; break;
		case "Chard3b":			rCharacter.FaceId = 1510; break; //Волверстон
		case "pet_crab":		rCharacter.FaceId = 1512; break;
		case "crabSmall":		rCharacter.FaceId = 1512; break;
		case "crabBig":			rCharacter.FaceId = 1512; break;
		case "Tichingitu_0"		:  	rCharacter.FaceId = 1513; break;		// Тиничгиту
		case "Tichingitu_0_mush":   rCharacter.FaceId = 1513; break;		// Тиничгиту - модель мушкетера
		case "PGG_Longway_0":		rCharacter.FaceId = 487; break;
		case "PGG_Lejitos_0":	rCharacter.FaceId = 535; break;
		case "PGG_Rozencraft":	rCharacter.FaceId = 496; break;
		case "priest":			rCharacter.FaceId = 531; break;
		case "PGG_Vincento_0":	rCharacter.FaceId = 531; break;
		case "PGG_Beatric_0":	rCharacter.FaceId = 522; break;
		case "PGG_Devlin_0":	rCharacter.FaceId = 1; break;
		case "PGG_ShMor_0":		rCharacter.FaceId = 508; break;
		case "PGG_Mary":		rCharacter.FaceId = 517; break;
		case "ozg_green":		rCharacter.FaceId = 287; break;
		case "PGG_Chard_0":		rCharacter.FaceId = 211; break;
		case "PGG_Tich_0":		rCharacter.FaceId = 540; break;
		else rCharacter.FaceId 	= 478; break;
	}
	if (InterfaceStates.VISUAL_CIRASS && !CheckAttribute(rCharacter,"VISUAL_CIRASS"))
	{
		// --> LEO&Gregg: Подключение визуала для надетых кирас (если не будет нужной модели, персонаж не появится и будет баговать)
		if (HasSubStr(rCharacter.model,"_0"))
		{
			//log_info(rCharacter.model);
			rCharacter.model = strreplace(rCharacter.model,"_0","");
			//log_info(rCharacter.model);
			rCharacter.HeroModel = rCharacter.model+"_0,"+rCharacter.model+"_1,"+rCharacter.model+"_2,"+rCharacter.model+"_3,"+rCharacter.model+"_4,"+rCharacter.model+"_5";
			//log_info(rCharacter.HeroModel);
			rCharacter.model = GetSubStringByNum(rCharacter.HeroModel,0);
		}
		else
		{
			if (HasSubStr(rCharacter.model,"DebugOfficer_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"officer_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"Mushketer_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"pirate_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"OZG_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"PKM_rab_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"AztecCitizen")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"AztecWarrior")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"Canib_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"citiz_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"prison_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"prizon_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"skel")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"Skel_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"Slave")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
			if (HasSubStr(rCharacter.model,"shipowner_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
		}
		rCharacter.VISUAL_CIRASS = true;
		// if (HasSubStr(rCharacter.model,"trader_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
		// if (HasSubStr(rCharacter.model,"usurer_")) rCharacter.HeroModel = rCharacter.model+","+rCharacter.model+"_1"+","+rCharacter.model+"_2"+","+rCharacter.model+"_3"+","+rCharacter.model+"_4"+","+rCharacter.model+"_5";
		// <-- LEO&Gregg: Подключение визуала для надетых кирас
	}
}

//Создадим вражеских фантомов - команда для ЛГ
string GetRandSkelModel()
{
	string emodel = "mummy";

	switch (rand(3))
    {
        case 0: emodel = "PotCMob1";   break;
        case 1: emodel = "PotCMob2";   break;
        case 2: emodel = "PotCMob3";   break;
        case 3: emodel = "PotCMob4";   break;
    }
    return emodel;
}

string GetRandSkelModelClassic()
{
	string emodel = "mummy";

	switch (rand(3))
    {
        case 0: emodel = "Skel1";   break;
        case 1: emodel = "Skel2";   break;
        case 2: emodel = "Skel3";   break;
        case 3: emodel = "Skel4";   break;
    }
    return emodel;
}

// boal 22.04.04 выбор модели зависимо от типа
void SetCaptanModelByEncType(ref Chref, string sFantomType)
{
    string ModelPirate = "Albermal"; // значит баг

	if (sti(Chref.nation) == PIRATE) sFantomType = "pirate"; // иначе баг

    switch (sFantomType)
	{
		case "trade":
            ModelPirate = "trader_" + (rand(15) + 1);
		break;
		case "war":
			ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(1) + 1);
		break;
		case "pirate":
            ModelPirate = "officer_" + (rand(63) + 1);
		break;
	}
	Chref.model = ModelPirate;
	FaceMaker(Chref);
}

void SetModelPirate(ref ChrefPirate)
{
    string ModelPirate;

    ModelPirate = "Pirate_" + (rand(24) + 1);

    ChrefPirate.model = ModelPirate;
	DeleteAttribute(ChrefPirate,"VISUAL_CIRASS");
	DeleteAttribute(ChrefPirate,"HeroModel");
    FaceMaker(ChrefPirate);
}

void SetOZGModel(ref Chref)
{
    string OZGModel;

    OZGModel = "OZG_" + (rand(9) + 1);

    Chref.model = OZGModel;
    FaceMaker(Chref);
}

// Warship. Обновим персу модель и анимацию. Пока-что здесь
void Characters_RefreshModel(ref rChar)
{
	SendMessage(rChar, "lss", MSG_CHARACTER_SETMODEL, rChar.model, rChar.model.animation);
	/*if (CheckAttribute(rChar, "HeadAccessory") && IsEquipCharacterByItem(rChar, rChar.HeadAccessory))
	{
		SendMessage(rChar,"lsss",MSG_CHARACTER_SETHEAD,rChar.model, rChar.HeadAccessory, "pscripts\HeadGear.ini");
	}*/
}
