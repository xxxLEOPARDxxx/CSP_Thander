/////////  новый файл под нужды ВМЛ, код К3 не совместим - весь потерт  ///////////
// boal абордаж офицеров 27.01.2004 -->
bool Ship_AutoAbordage(ref rCharacter, float fMinEnemyDistance)
{
    bool bSuccess = false;

    //Log_SetStringToLog("Корабль " + rCharacter.Ship.Name + " cap="+rCharacter.id+" начинает абордаж " + Characters[sti(rCharacter.SeaAI.Task.Target)].Ship.Name+" cap="+Characters[sti(rCharacter.SeaAI.Task.Target)].id);
    if (fMinEnemyDistance < 70)
    {
	    int   bGrapplingProfessional  = sti(rCharacter.TmpPerks.GrapplingProfessional);
        float fOurGrappling           = 10 * stf(rCharacter.TmpSkill.Grappling);
	    float fOurMaxAbordageDistance = 15 + 7 * (bGrapplingProfessional + fOurGrappling);

		//navy 18.02.08 Запрет абордажа
		if (CheckAttribute(rCharacter, "Tasks.CanBoarding") && !sti(rCharacter.Tasks.CanBoarding)) return false;

	    if (fMinEnemyDistance > fOurMaxAbordageDistance) return bSuccess;
	    if (!CheckAttribute(rCharacter, "SeaAI.Task.Target")) return bSuccess;

        ref rEnemyCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
        if (LAi_IsDead(rEnemyCharacter)) return bSuccess;
        //#20180524-01 Remove unneeded sqrt, was 90, now 90^2
        if (Ship_GetDistance2DRel(rCharacter, rEnemyCharacter) > 8100.0) return bSuccess;// fix левых дистанций

        int rCharIdx = sti(rCharacter.index);
        int rEnemyCharIdx = sti(rEnemyCharacter.index);
	    int iRelation = SeaAI_GetRelation(rCharIdx, rEnemyCharIdx);

	    if (!Character_IsAbordageEnable(rEnemyCharacter) || rEnemyCharIdx == GetMainCharacterIndex()) return bSuccess;

		if (iRelation != RELATION_ENEMY) return bSuccess;
		// решение об абордаже
		int rCharCrew = sti(rCharacter.Ship.Crew.Quantity);
		int rEnemyCharCrew = sti(rEnemyCharacter.Ship.Crew.Quantity);

		if (rCharCrew < (stf(rEnemyCharCrew) * 0.6)) return bSuccess;

	    float fOurFencing = stf(rCharacter.TmpSkill.Grappling); //Fencing
	    float fOurCrewFencing = (0.1 + fOurFencing * stf(rCharacter.Ship.Crew.Quantity)*GetCrewExp(rCharacter, "Soldiers"));

	    //#20180126-01
	    bool bIsCharCompanion = IsCompanion(rCharacter);
	    bool bIsEnemyCompanion = IsCompanion(rEnemyCharacter);
	    if (bIsCharCompanion)
	    {
	       fOurCrewFencing = (0.1 + fOurFencing * GetWeaponCrew(rCharacter, rCharCrew)*GetCrewExp(rCharacter, "Soldiers"));
	    }
	    float fMorale = GetCharacterCrewMorale(rCharacter);
        fOurCrewFencing = fOurCrewFencing * (0.5 + fMorale / MORALE_MAX);

	    float fEnFencing = stf(rEnemyCharacter.TmpSkill.Grappling); //Fencing
	    float fEnCrewFencing = (0.1 + fEnFencing * stf(rEnemyCharCrew) *GetCrewExp(rEnemyCharacter, "Soldiers"));

	    if (bIsEnemyCompanion)
	    {   // учет оружия
	       fEnCrewFencing = (0.1 + fEnFencing * GetWeaponCrew(rEnemyCharacter, rEnemyCharCrew)*GetCrewExp(rEnemyCharacter, "Soldiers") );
	    }
        fMorale  = GetCharacterCrewMorale(rEnemyCharacter);
        fEnCrewFencing = fEnCrewFencing * (0.5 + fMorale / MORALE_MAX);

		bool bAngleTest = true;// пока всегда, что верно дл¤ тупого компа
        int deadCrew = 0;
		int iNation;
		if (bGrapplingProfessional || bAngleTest)
		{
			bSuccess = true;
			PlayStereoSound("Interface\abordage.wav");

            if (fOurCrewFencing >= fEnCrewFencing)
            { // победа
                if (bIsEnemyCompanion)
			    {
			        Log_SetStringToLog("Наш корабль '" + rEnemyCharacter.Ship.Name + "' взят на абордаж");
			    }
			    else
			    {
			        iNation = sti(rEnemyCharacter.nation);
					Log_SetStringToLog("Корабль '" + rEnemyCharacter.Ship.Name + "' под флагом " + NationNameGenitive(iNation) + " взят на абордаж");
			    }
			    deadCrew = sti(rCharacter.Ship.Crew.Quantity) * fEnCrewFencing / (fOurCrewFencing*1.8);
				if (bIsCharCompanion) Statistic_AddValue(pchar, "Sailors_dead", deadCrew);
				if (bIsEnemyCompanion) Statistic_AddValue(pchar, "Sailors_dead", sti(rEnemyCharacter.Ship.Crew.Quantity));
			    SetCrewQuantity(rCharacter, makeint(sti(rCharacter.Ship.Crew.Quantity) - deadCrew));
				SetCrewQuantity(rEnemyCharacter, 0);
			    if (bIsCharCompanion)
			    {
			        RemoveCharacterGoodsSelf(rCharacter, GOOD_WEAPON, deadCrew);
					LAi_SetCurHP(rEnemyCharacter, 0.0);
					LaunchRansackMain(rCharacter, rEnemyCharacter, "companion_captured");
				}
				else
				{
					if (CheckChanceOfBetterShip(rCharacter, rEnemyCharacter))
					{
						SeaExchangeCharactersShips(rCharacter, rEnemyCharacter, true, true);
					}
					DoTakeAbordageGoods(rCharacter, rEnemyCharacter);
					ShipDead(sti(rEnemyCharacter.index), KILL_BY_ABORDAGE, sti(rCharacter.index));
				}
            }
            else
            { // поражение
                if (bIsCharCompanion)
			    {
			        Log_SetStringToLog("Наш корабль '" + rCharacter.Ship.Name + "' проиграл абордаж");
			    }
			    else
			    {
			        iNation = sti(rCharacter.nation);
					Log_SetStringToLog("Корабль '" + rCharacter.Ship.Name + "' под флагом " + NationNameGenitive(iNation) + " проиграл абордаж");
			    }
			    deadCrew = sti(rEnemyCharacter.Ship.Crew.Quantity) * fOurCrewFencing/ (fEnCrewFencing*1.8);
				if (bIsCharCompanion) Statistic_AddValue(pchar, "Sailors_dead", sti(rCharacter.Ship.Crew.Quantity));
				if (bIsEnemyCompanion) Statistic_AddValue(pchar, "Sailors_dead", deadCrew);
			    SetCrewQuantity(rEnemyCharacter, makeint(sti(rEnemyCharacter.Ship.Crew.Quantity) - deadCrew));
				SetCrewQuantity(rCharacter, 0);
			    if (bIsEnemyCompanion)
			    {
			        RemoveCharacterGoodsSelf(rEnemyCharacter, GOOD_WEAPON, deadCrew);
					LAi_SetCurHP(rCharacter, 0.0);
					LaunchRansackMain(rEnemyCharacter, rCharacter, "companion_captured");
				}
				else
				{
					if (CheckChanceOfBetterShip(rEnemyCharacter, rCharacter))
					{
						SeaExchangeCharactersShips(rEnemyCharacter, rCharacter, true, true);
					}
					DoTakeAbordageGoods(rEnemyCharacter, rCharacter);
					ShipDead(sti(rCharacter.index), KILL_BY_ABORDAGE, sti(rEnemyCharacter.index));
				}
            }
		}
	}
    return bSuccess;
}
// boal 27.01.2004 <--

//navy -->
//обменять кораблями двух персонажей, с сохранением груза
void SeaExchangeCharactersShips(ref rOneChr, ref rSecChr, bool _showLog, bool _swapCargo)
{
	int     nMyCrew;
	aref    arCargoOne, arCargoSec;
	object	oTmp;

	//команда первого (основного) перса...
	nMyCrew = GetCrewQuantity(rOneChr);
    float fMor = stf(rOneChr.ship.crew.morale);
    makearef(arCargoOne, rOneChr.Ship.Crew.Exp);
	CopyAttributes(&oTmp, arCargoOne); // опыт

	//меняем корабли...
	SeaAI_SwapShipsAttributes(rOneChr, rSecChr, true);
	//#20190207-01 //#20190627-01
	SeaAI_SwapShipAfterAbordage(rOneChr, rSecChr);

	//вернем команду
	SetCrewQuantity(rOneChr, nMyCrew);
	SetCrewQuantity(rSecChr, 0);
    rOneChr.ship.crew.morale = fMor;
    // опыт на место
    makearef(arCargoOne, rOneChr.Ship.Crew.Exp);
	DeleteAttribute(arCargoOne,"");
	CopyAttributes(arCargoOne,&oTmp);

	//вернем груз
	if (_swapCargo)
	{
		oTmp.Ship.Cargo = "";
		makearef(arCargoOne, rOneChr.Ship.Cargo);
		makearef(arCargoSec, oTmp.Ship.Cargo);

		CopyAttributes(arCargoSec, arCargoOne);
		DeleteAttribute(arCargoOne,"");

		makearef(arCargoSec, rSecChr.Ship.Cargo);
		CopyAttributes(arCargoOne,arCargoSec);
		DeleteAttribute(arCargoSec,"");

		makearef(arCargoOne, oTmp.Ship.Cargo);
		CopyAttributes(arCargoSec, arCargoOne);

		//обновим интерфейс
		//RefreshFlags();
		DoQuestCheckDelay("NationUpdate", 1.0);
		RefreshBattleInterface();
	}
	if (_showLog)
	{
		Log_SetStringToLog(GetFullName(rOneChr) + " обменял свой корабль на " +
						XI_ConvertString(RealShips[sti(rOneChr.Ship.Type)].BaseName) + " " + rOneChr.Ship.Name + ".");
		trace(GetFullName(rOneChr) + " обменял свой корабль на " +
						XI_ConvertString(RealShips[sti(rOneChr.Ship.Type)].BaseName) + " " + rOneChr.Ship.Name + ".");
	}
}
//сравнить два корабля
bool CheckChanceOfBetterShip(ref rChar, ref rTryChar)
{
	float fChance;
	ref  rShip;
	ref  rTryShip;

	rShip    = GetRealShip(sti(rChar.Ship.Type));
	rTryShip = GetRealShip(sti(rTryChar.Ship.Type));

	//запрет меняться кораблями 18.02.08
	if (CheckAttribute(rChar, "Tasks.CanChangeShipAfterBoarding") && !sti(rChar.Tasks.CanChangeShipAfterBoarding)) return false;
    if (CheckAttribute(rChar, "Tasks.CanBoarding") && !sti(rChar.Tasks.CanBoarding)) return false;
	//заглушка для квестовых кораблей с 48ф пушками. 22.09.05
	if (sti(rChar.Ship.Cannons.Type) == CANNON_TYPE_CANNON_LBS48 || sti(rTryChar.Ship.Cannons.Type) == CANNON_TYPE_CANNON_LBS48) return false;

	fChance = (stf(rShip.Class) / stf(rTryShip.Class)) * 0.3; //при равных классах база 30 процентов

	//форс-мажор... тонем
	if (GetHullPercent(rChar) < 10 && GetHullPercent(rTryChar) > 30)
	{
		fChance += fChance * 3;
	}

	//пока взял примерно из опроса... в сумме 75 процентов макс, может нужно будет добавить...
	if (sti(rShip.SpeedRate) < sti(rTryShip.SpeedRate))				fChance += 0.2;
	if (sti(rShip.TurnRate) < sti(rTryShip.TurnRate))				fChance += 0.15;
	if (sti(rShip.CannonsQuantity) < sti(rTryShip.CannonsQuantity)) fChance += 0.1;
	if (sti(rShip.MaxCrew) < sti(rTryShip.MaxCrew))					fChance += 0.1;
	if (sti(rShip.Capacity) < sti(rTryShip.Capacity))				fChance += 0.1;
	if (sti(rShip.Price) < sti(rTryShip.Price))
	{
		fChance += 0.1;
	}
	else
	{
	    fChance -= 0.2;
	}

	if (fChance > 0.7) return true;
	return false;
}
//взять товары с абордированного корабля
void DoTakeAbordageGoods(ref rOneChr, ref rSecChr)
{
	int i, j, maxPrice, iGood, itmp;
	int freeSpace, freeQuantity;

	//три прохода, т.е. всего возьмем три товара...
	for (j=0; j < 3; j++)
	{
		freeSpace = GetCargoFreeSpace(rOneChr);
		//если у нас полный трюм выходим...
		if (freeSpace <= 0) return;

		maxPrice = 0;
		iGood = -1;
		//ищем самый дорогой товар на борту
		for (i=0; i < GOODS_QUANTITY; i++)
		{
			itmp = GetCargoGoods(rSecChr, i);
			if (itmp > 0 && sti(Goods[i].Cost) * itmp/Goods[i].Units > maxPrice)
			{
				maxPrice = sti(Goods[i].Cost) * itmp/Goods[i].Units;
				iGood = i;
			}
		}

		//если нет ничего тоже выходим
		if (iGood == -1) return;

		//перегружаем товар
		freeQuantity = GetGoodQuantityByWeight(iGood, freeSpace);
		itmp = GetCargoGoods(rSecChr, iGood);
		if (itmp <= freeQuantity)
		{
			AddCharacterGoods(rOneChr, iGood, itmp);
			RemoveCharacterGoods(rSecChr, iGood, itmp);
		}
		else
		{
			AddCharacterGoods(rOneChr, iGood, freeQuantity);
			RemoveCharacterGoods(rSecChr, iGood, freeQuantity);
		}
	}
}

void PlaceCompanionCloneNearMChr(int _index, bool _isCampus)
{
	int iTemp;
	ref chr, sld;
	aref arClone, arReal;

	chr = GetCharacter(GetCompanionIndex(PChar, _index));
	iTemp = NPC_GeneratePhantomCharacter("citizen", sti(chr.Nation), MAN, 0);  // создать клон
	if (iTemp != -1)
	{
		sld = &Characters[iTemp];
        ChangeAttributesFromCharacter(sld, chr, true);
		makearef(arReal, chr.Tasks);
		makearef(arClone, sld.Tasks);
		CopyAttributes(arClone, arReal);

		if (_isCampus)
		{
			if (_index < 5)
			{
				PlaceCharacter(sld, "sit", PChar.location);
				LAi_SetSitType(sld);
			}
			else
			{
				LAi_SetCitizenType(sld);
				PlaceCharacter(sld, "rld", PChar.location);
			}
		}
		else
		{
			LAi_SetCitizenType(sld);
			PlaceCharacter(sld, "rld", PChar.location);
		}
		LAi_SetImmortal(sld, true); //неубиваемый.
		sld.IsCompanionClone = true; //флаг для диалога, т.к. он не компаньон все таки...
        sld.RealCompanionIdx = chr.index;

		chr.Tasks.Clone = iTemp; //признак, что клон уже вызван.
	}
}
//18.02.08
void CompanionSaveTasks()
{
	int i;
	ref chr, sld;
	aref arClone, arReal;

	for (i = 1; i < GetCompanionQuantity(PChar); i++)
	{
		chr = GetCharacter(GetCompanionIndex(PChar, i));
		if (CheckAttribute(chr, "Tasks.Clone"))
		{
			sld = GetCharacter(sti(chr.Tasks.Clone));

			makearef(arReal, chr.Tasks);
			makearef(arClone, sld.Tasks);
			CopyAttributes(arReal, arClone);

			sld.location = "none";
			DeleteAttribute(chr, "Tasks.Clone");
		}
	}
}
//navy <--

//.........................  табличка выхода из боя 09.07.06 ...............
// _loadForm - показать форму с вопросом или простая проверка для запрета
bool CheckEnemyCompanionDistance2GoAway(bool _loadForm)
{
    aref	arUpdate;
	int		i, k, cn, iRelation;
	//#20180524-01 Remove unneeded sqrt
	float	fDistance, fMapDisable;
	string  attr;

	ref rCharacter, rFortCharacter, rShipCharacter;

	makearef(arUpdate, pchar.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return true; }
	if (!CheckAttribute(arUpdate, "Forts")) { return true; }

	aref aShips, aForts;
	aref aFort;
	aref aShip;

	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	// check forts for abordage
	int iShipsNum = GetAttributesNum(aShips);

	int iFortsNum = GetAttributesNum(aForts);
	int iFortMode;

	DeleteAttribute(pchar, "CheckEnemyCompanionDistance");
	for (k=1; k<COMPANION_MAX; k++)
	{
		cn = GetCompanionIndex(pchar, k);
		if( cn>=0 )
		{
            attr = "CompIDX" + k;
			rCharacter = GetCharacter(cn);
			if (!GetRemovable(rCharacter)) continue;  // квестовые сами себ¤ спасают

			// живые форты
			for (i=0; i<iFortsNum; i++)
			{
				aFort = GetAttributeN(aForts, i);
				iRelation = sti(aFort.relation);

				rFortCharacter = GetCharacter(sti(aFort.idx));
				if (LAi_IsDead(rFortCharacter)) { continue; }
				iFortMode = sti(rFortCharacter.Fort.Mode);

				switch (iFortMode)
				{
					case FORT_NORMAL:
						if (iRelation == RELATION_ENEMY)
						{
		                    //#20180524-01 Remove unneeded sqrt
						    fMapDisable =  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT *  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT;
		                    fDistance = Ship_GetDistance2DRel(rCharacter, rFortCharacter);
							if (fDistance < fMapDisable)
							{
							    if (!_loadForm) return false; // все, кто-то есть
								// пишем кто, в форму
           						pchar.CheckEnemyCompanionDistance.(attr)) = cn;
							}
						}
					break;
				}
			}
			// check ships for abordage
			for (i=0; i<iShipsNum; i++)
			{
				aShip = GetAttributeN(aShips, i);

				rShipCharacter = GetCharacter(sti(aShip.idx));
				iRelation = sti(aShip.relation);

				if (LAi_IsDead(rShipCharacter)) { continue; }
				if (iRelation != RELATION_ENEMY) { continue; }
		        //#20180524-01 Remove unneeded sqrt
                fMapDisable =  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER *  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
                fDistance = Ship_GetDistance2DRel(rCharacter, rShipCharacter);
                if (fDistance < fMapDisable)
				{
				    if (!_loadForm) return false; // все, кто-то есть
					pchar.CheckEnemyCompanionDistance.(attr)) = cn;
				}
			}
		}
	}
	if (_loadForm && CheckAttribute(pchar, "CheckEnemyCompanionDistance"))
	{
		// вызов формы
		LaunchLeaveBattleScreen();
		return false;
	}
	return true; // все хорошо, ничто не мешает
}
//#20190706-01
/*void PostBoardDecision(ref victor, int victorIDX, ref defeated, int defeatIdx, int numOrigCrew)
{
    string sCurGroup; //, sEGroup;
    int nRemain;
    aref rSituation;
    makearef(rSituation, victor.SeaAI.Update.Situation);
    int nearEnemy = sti(rSituation.MinEnemyIndex);
    int nearFriend = sti(rSituation.MinFriendIndex);
    int nearGroup = sti(rSituation.MinGroupIndex);
    float fMinEnemyDistance = stf(rSituation.MinEnemyDistance);
	float fMinFriendDistance = stf(rSituation.MinFriendDistance);
	float fMinGroupDistance = stf(rSituation.MinGroupDistance);

    ShipDead(defeatIdx, KILL_BY_ABORDAGE, victorIDX);

    int bChkFrdfRef = -1;
    int bChkGrpRef = -1;
    if(nearFriend > -1 && CheckAttribute(&characters[nearFriend], "SeaAI.Task.Target"))
        bChkFrdfRef = sti(characters[nearFriend].SeaAI.Task.Target);
    if(nearGroup > -1 && CheckAttribute(&characters[nearGroup], "SeaAI.Task.Target"))
        bChkGrpRef = sti(characters[nearGroup].SeaAI.Task.Target);
    if(IsCompanion(victor)) {
        if(fMinGroupDistance < fMinEnemyDistance && victorIDX != bChkGrpRef) {
            Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,nearGroup);
        }
        else {
            if(fMinFriendDistance < fMinEnemyDistance && victorIDX != bChkFrdfRef) {
                Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,nearFriend);
            }
            else {
                if(nearEnemy != -1) {
                    Ship_SetTaskAttack(SECONDARY_TASK,victorIDX,nearEnemy);
                }
                else {
                    Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,GetMainCharacterIndex());
                }
            }
        }
        return;
    }
    sCurGroup = Ship_GetGroupID(victor);
    //sEGroup = Ship_GetGroupID(defeated);
    float fCrewRemain = stf(victor.Ship.Crew.Quantity);
    float fCrewPer = fCrewRemain / makefloat(numOrigCrew);
    int cmdridx = Group_GetGroupCommanderIndex(sCurGroup);
    bool bIamCmdr = false;
	if(victorIDX == cmdridx) bIamCmdr = true;

	float epower;
	float fpower;
    SendMessage(&AISea, "lale", AI_MESSAGE_GROUP_GET_POWERREL, victor, RELATION_ENEMY, &epower);
    SendMessage(&AISea, "lale", AI_MESSAGE_GROUP_GET_POWERREL, victor, RELATION_FRIEND, &fpower);
    epower += 0.0000001; //Div by zero
    float pwrDiff = fpower / epower;

    if(fCrewPer > 0.8 && pwrDiff > 0.9) {
        if(fMinGroupDistance < fMinEnemyDistance && victorIDX != bChkGrpRef) {
            Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,nearGroup);
            return;
        }
        else {
            if(nearEnemy != -1) {
                Ship_SetTaskAttack(SECONDARY_TASK,victorIDX,nearEnemy);
                return;
            }
            else {
                if(!bIamCmdr) {
                    Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,cmdridx);
                    return;
                }
            }
        }
    }
    nRemain = Group_GetLiveCharactersNum(sCurGroup);
    if(!bIamCmdr) {
        if(fCrewPer < 0.5 || pwrDiff < 0.5) {
            if(nearEnemy != -1) {
                Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,nearEnemy);
                return;
            }
            if(nearGroup != -1) {
                Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,nearGroup);
                return;
            }
            if(cmdridx != -1) {
                Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,cmdridx);
                return;
            }
        }
    }
    else {
        if(fCrewPer < 0.25 || pwrDiff < 0.25) {
            if(nearEnemy != -1) {
                Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,nearEnemy);
                return;
            }
            if(nearFriend != -1) {
                Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,nearFriend);
                return;
            }
            if(cmdridx != -1) {
                Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,cmdridx);
                return;
            }
        }
        if(nRemain < 2 && nearEnemy > -1) {
            if(fCrewPer < 0.6 || pwrDiff < 0.6) {
                if(nearEnemy != -1) {
                    Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,nearEnemy);
                    return;
                }
                if(nearFriend != -1) {
                    Ship_SetTaskRunaway(SECONDARY_TASK,victorIDX,nearFriend);
                    return;
                }
            }
        }
    }
    if(nearEnemy != -1) {
        if(nRemain < 2) {
            Ship_SetTaskRunaway(SECONDARY_TASK, victorIDX, nearEnemy);
            return;
        }
        Ship_SetTaskAttack(SECONDARY_TASK,victorIDX,nearEnemy);
        return;
    }
    if(cmdridx != -1) {
        Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,cmdridx);
        return;
    }
    if(nearGroup != -1 && victorIDX != bChkGrpRef) {
        if(nRemain < 2) {
            Ship_SetTaskRunaway(SECONDARY_TASK, victorIDX, nearGroup);
            return;
        }
        Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,nearGroup);
        return;
    }
    if(nearFriend != -1 && victorIDX != bChkFrdfRef) {
        if(nRemain < 2) {
            Ship_SetTaskRunaway(SECONDARY_TASK, victorIDX, nearFriend);
            return;
        }
        Ship_SetTaskDefend(SECONDARY_TASK,victorIDX,nearFriend);
        return;
    }
}
*/
