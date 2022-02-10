////  файл для кораблей в порту, море и сторожевиков
int iCount;
void GenerateIslandShips(string sIslandID)
{
	//trace(sIslandID);
	//if (!TestRansackCaptain) return; // to_do
	if (FindIsland(sIslandID) == -1)) return;
	int iColonyQuantity = sti(Islands[FindIsland(sIslandID)].colonyquantity);
	int iNation;
	int iShipsQuantity;
	int iChar;
	int iType = 0;
	ref chr;
	string sTemp;
	int defendersCount = MOD_DEFENDERS_RATE;

	int MainDefenderChar = -1;

	for (int i = 0; i< MAX_COLONIES; i++)
	{
		iCount = 1;
		MainDefenderChar = -1;
		if (Colonies[i].island == sIslandID)
		{
			if (colonies[i].nation != "none" && colonies[i].id != "Caiman" && !CheckAttribute(&colonies[i], "HasNoFort") && !CheckAttribute(&colonies[i], "Siege") && !CheckAttribute(&colonies[i], "DontSetShipInPort"))
			{
				bool FortDefender;
				ref FortChref = GetFortCommander(colonies[i].id);
				if (CheckAttribute(&colonies[i], "AlreadyGen")) //охрана
				{
					int check = 0;
					for (int j=GlobalCharacters; j<MAX_CHARACTERS; j++)
					{
						if (CheckAttribute(&characters[j], "fortDefender") && CheckAttribute(&characters[j], "IslandShips") && characters[j].IslandShips == colonies[i].id)
						{
							//Log_Info(characters[j].id);
							check++;
						}
						/* if (CheckAttribute(&characters[j], "fortDefender") && CheckAttribute(&characters[j], "IslandShips") && characters[j].IslandShips != colonies[i].id)
						{
							InitCharacter(&characters[j], j);
							Group_FreeAllDead();
						} */
					}
					//Log_Info(""+check);
					if (check == 0) DeleteAttribute(&colonies[i],"AlreadyGen");
				}
				if (!CheckAttribute(&colonies[i], "AlreadyGen")) //охрана
				{
                    //SaveCurrentNpcQuestDateParam(&colonies[i], "GenShipDate"); // дата заполнения
					iNation = sti(Colonies[i].nation);

					FortDefender = false;

					if (defendersCount != 0);
					{
						iShipsQuantity = rand(2)+defendersCount;
						if (CheckAttribute(FortChref,"Fort.Mode"))
						{
							if(sti(FortChref.Fort.Mode) == FORT_ABORDAGE || sti(FortChref.Fort.Mode) == FORT_DEAD || iNation == PIRATE)
							{
								iShipsQuantity = 0;
								continue;
							}
						}
						colonies[i].AlreadyGen = true;
						for (j = 0; j < iShipsQuantity; j++)
						{
							sTemp = "off_" + NationShortName(iNation) + "_" + i;
							if(defendersCount > 0) iChar = NPC_GenerateCharacter("FortDefender"+i+j, sTemp, "man","spy", 30, iNation, -1, true);
							else iChar = NPC_GenerateCharacter("Officer"+i + (j-defendersCount), "pirate", "man","man", sti(pchar.rank) + 5, iNation, -1, true);

							if(defendersCount > 0) FortDefender = true;
							else FortDefender = false;


							if(defendersCount > 0 && MainDefenderChar == -1) MainDefenderChar = iChar;
							chr = GetCharacter(iChar);

							if(defendersCount > 0) CreateFortDefenders(chr, iNation);
							else chr.Ship.Type = GenerateShipExt(28 + rand (4), 1, chr);

							PlaceCharacterShip(iChar, iNation, sIslandID, i, FortDefender, MainDefenderChar);

							characters[iChar].IslandShips = Colonies[i].id; // номер города, чтоб тереть по захвату города to_do
							if (iNation == PIRATE)
							{ // нащ город
								characters[iChar].AlwaysFriend        = true;
								SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
							}

							if(defendersCount > 0) characters[iChar].Ship.Mode = "war";
							else characters[iChar].Ship.Mode = "pirate";

							if (rand(4) == 1 || GetCharacterShipClass(&characters[iChar]) == 1) SetRandGeraldSail(chr, iNation);

							characters[iChar].AlwaysSandbankManeuver = true;  // тупым запрет тонуть об берег

							characters[iChar].AnalizeShips = true; //анализить вражеские корабли

							characters[iChar].location.from_sea = colonies[i].from_sea;

							if(defendersCount > 0) SetCaptanModelByEncType(chr, "war");
							else SetCaptanModelByEncType(chr, "pirate");

							Fantom_SetCannons(chr, characters[iChar].Ship.Mode);

							Fantom_SetBalls(chr, characters[iChar].Ship.Mode);

							SetRandomNameToShip(chr);

							SetBaseShipData(chr);

							AddItems(chr,"potion2",10);

							if(defendersCount > 0) SetCrewQuantityFull(chr);
							else SetCrewQuantity(chr, GetOptCrewQuantity(chr));



							if(defendersCount < 0) SetSeaFantomParam(chr, "pirate");

							Ship_FlagRefresh(chr);


							if(defendersCount > 0)
							{
								SelAllPerksToNotPchar(chr);
								if(CheckAttribute(chr,"perks.list.ShipEscape")) DeleteAttribute(chr,"perks.list.ShipEscape");
								switch(rand(2))
								{
									case 0:
										GiveItem2Character(chr,"blade32");
										EquipCharacterByItem(chr,"blade32");
									break;
									case 1:
										GiveItem2Character(chr,"blade28");
										EquipCharacterByItem(chr,"blade28");
									break;
									case 2:
										GiveItem2Character(chr,"blade26");
										EquipCharacterByItem(chr,"blade26");
									break;
								}
								SetSelfSkill(chr, 100, 100, 100, 100, 90);
								SetShipSkill(chr, 90, 90, 90, 90, 100, 90, 90, 90, 90);
							}

							if(defendersCount > 0) defendersCount = defendersCount - 1;
						}
					}

				}
				if (!CheckAttribute(&colonies[i], "GenShipDate") || GetNpcQuestPastDayParam(&colonies[i], "GenShipDate") > 0) //торгаши
				{
                    SaveCurrentNpcQuestDateParam(&colonies[i], "GenShipDate"); // дата заполнения
					iNation = sti(Colonies[i].nation);

					FortDefender = false;

					iShipsQuantity = rand(2);
					if (CheckAttribute(FortChref,"Fort.Mode"))
					{
						if(sti(FortChref.Fort.Mode) == FORT_ABORDAGE || sti(FortChref.Fort.Mode) == FORT_DEAD || iNation == PIRATE)
						{
							iShipsQuantity = 0;
							continue;
						}
					}
					for (j = 0; j < iShipsQuantity; j++)
					{
						iChar = NPC_GenerateCharacter("ColonyTrader" + i +j, "trade", "man", "man", MOD_SKILL_ENEMY_RATE, iNation, -1, true));
						chr = GetCharacter(iChar);
						chr.AlwaysSandbankManeuver = true;
						CreateFortMerchants(chr, iNation);
						PlaceCharacterShip(iChar, iNation, sIslandID, i, FortDefender, MainDefenderChar);
						characters[iChar].IslandShips = Colonies[i].id;

						if (iNation == PIRATE)
						{ // нащ город
							characters[iChar].AlwaysFriend        = true;
							SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
						}

						characters[iChar].Ship.Mode = "trade";

						SetRandomNameToShip(chr);
						SetBaseShipData(chr);
						SetCrewQuantity(chr, GetOptCrewQuantity(chr));

						if (rand(4) == 1 || GetCharacterShipClass(&characters[iChar]) == 1) SetRandGeraldSail(chr, sti(characters[iChar].Nation));
						characters[iChar].AlwaysSandbankManeuver = true;
						characters[iChar].AnalizeShips = true; //анализить вражеские корабли
						characters[iChar].location.from_sea = colonies[i].from_sea;

						SetCaptanModelByEncType(chr, characters[iChar].Ship.Mode);//

						Fantom_SetCannons(chr, characters[iChar].Ship.Mode);
						Fantom_SetBalls(chr, characters[iChar].Ship.Mode);
						Fantom_SetGoods(chr, characters[iChar].Ship.Mode);
						SetSeaFantomParam(chr, characters[iChar].Ship.Mode);


						Ship_FlagRefresh(chr);
					}
				}
			}
		}
	}
}
void PlaceCharacterShip(int iChar, int iNation, string sIslandID, int iColonyIdx, bool isFortDefender, int defendersGroup)
{
	int iColonyNum = sti(colonies[iColonyIdx].num);
	string sColonyID = colonies[iColonyIdx].id;

	ref chr = GetCharacter(iChar);
	ref FortChref = GetFortCommander(colonies[iColonyIdx].id);
	string sGroup1 = "Fort_"+colonies[iColonyIdx].id;
	Group_AddCharacter(sGroup1, FortChref.id);
	Group_SetGroupCommander(sGroup1, FortChref.id);

	string sGroup = "IslandGroup" + iChar;
	string sLocatorGroup = "IslandShips" + iColonyNum;
	string sLocator = "Ship_"+(rand(5)+1);
	if(isFortDefender)
	{
		sLocator = "Ship_" + iCount;
		iCount++;
	}

	//ref FortChref = GetFortCommander(colonies[iColonyIdx].id);

	/* if(isFortDefender)
	{
		sGroup = "IslandGroup" + defendersGroup;
	}
	 */
	Group_AddCharacter(sGroup, characters[iChar].id);

	if(isFortDefender)
	{
		//Group_SetGroupCommander(sGroup, FortChref.id);
		Group_SetGroupCommander(sGroup, characters[defendersGroup].id);
		// sLocator = "Ship_1";
	}
	else
	{
		Group_SetGroupCommander(sGroup, characters[iChar].id);
	}

	Group_SetAddress(sGroup, sIslandID, sLocatorGroup, sLocator);

	//trace("sLocatorGroup is " + sLocatorGroup + " sLocator is " + sLocator);
	int iTask = rand(1);
	float x, z;
	if(isFortDefender)
	{
		characters[iChar].WatchFort = true;
		characters[iChar].fortDefender = 1;
		chr.SeaAI.Task = AITASK_DEFEND;
		chr.SeaAI.Task.Target = GetCharacterIndex(FortChref.id);
	}
	else
	{
		if (iTask == 0)
		{
			x = rand(1000000);
			z = rand(1000000);
			Group_SetTaskMove(sGroup, x, z);
		}
		else
		{
			Ship_SetTaskDrift(SECONDARY_TASK, iChar);
			Group_SetTaskNone(sGroup);
		}
	}

	/*if (sti(characters[iChar].nation) != PIRATE && GetNationRelation2Character(iNation, nMainCharacterIndex) == RELATION_ENEMY)
	{
		Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	}*/
}
// очистить порт
void ClearIslandShips(string _city)
{
	if (!bSeaActive)
	{
		for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
		{
			// отдельный код зачистки boal -->
			if (CheckAttribute(&characters[i], "IslandShips") && characters[i].IslandShips == _city)
			{
				InitCharacter(&characters[i], i);
			}
			if (CheckAttribute(&characters[i], "fortDefender") && sti(characters[i].fortDefender) == 1 && characters[i].IslandShips == _city)
			{
				InitCharacter(&characters[i], i);
			}
		}
		// потрем пустые группы
		Group_FreeAllDead();
	}
}
