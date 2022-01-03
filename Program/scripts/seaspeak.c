void Sea_Speak(aref chr, int whospeak, int isTaxAsk)
{
	//chr is non-player ship
	// whospeak = pchar.index
	//or whospeak = non-player ship index

	string starget = chr.id;
	chr.dialogtype = "";
	string sMode = "";

	if (whospeak != sti(pchar.index))
	{
		//trace("Sea_Speak: Other ship is speaking");
		//enemy offering or asking for money
		//if (!bIslandLoaded)
		//{
			if(isTaxAsk == -1)
			{
				if (!CheckAttribute(&characters[GetCharacterIndex(sTarget)], "speak.ransom.offered"))
				{
					//JA: character does not offer capture via the speak interface anymore
					//if (CalculateForCapture(chr))
					//{
					//	sMode = "capture";
					//}
					//else
					//{
						if (CalculateForRansom(chr))
						{
							sMode = "ransom";
							chr.speak.ransom.offered = true;

						}
					//}
				}
			}
			else
			{
				if(!CheckAttribute(&characters[GetCharacterIndex(sTarget)], "speak.tax"))
				{
					sMode = "tax";
					//trace("etape 1 seaspeak")
				}
			}
		//}
	}
	//trace("LaunchSpeakInterface: sMode=" + sMode);

	if(sMode != "" || whospeak == sti(pchar.index))
	{
		LaunchSpeakInterface(chr, whospeak, sMode);
	}
}

void DeleteRansomCharacters()
{
	for(int i=800; i<1000; i++)
	{
		//if(checkAttribute(&characters[i], "ransom"))
		//{
			DeleteAttribute(&characters[i], "ransom");
            //trace("etape drc seaspeak")
		//}
	}
}

void AnalizeSituations(aref rSpeakCharacter)
{
	string sGroup = "Analize_Group_" + rSpeakCharacter.id;
	if (checkAttribute(rSpeakCharacter, "speak.ransom.taked"))
	{
		Ship_Neutral(GetCharacterIndex(rSpeakCharacter.id),sGroup);
		//trace("etape 2 seaspeak")
	}
}

// Celui d'origine:
void AnalizeSituationsTAX(ref rSpeakCharacter)
{
 int visibleFlag;// Philippe
 int NEUTRAL;

	if(checkAttribute(rSpeakCharacter, "speak.tax"))
	{
		if (checkAttribute(rSpeakCharacter, "SeaAI.Group.Name"))
		{
			string sGroup = rSpeakCharacter.SeaAI.Group.Name;
			Group_SetNeutralToCharacter(sGroup, nMainCharacterIndex);
            // sGroup.visibleFlag = NEUTRAL;

			NationUpdate();
            //trace("etape 3 seaspeak")
		}
	}
}
void AnalizeSituationsEnemy()
{
	string sTarget = pchar.speakchr;
	Ship_SetTaskAttack(PRIMARY_TASK, getCharacterIndex(sTarget), nMainCharacterIndex);
	SetCharacterRelationBoth(GetCharacterIndex(sTarget),nMainCharacterIndex,RELATION_ENEMY);
	NationUpdate();
    //trace("etape 4 seaspeak")
}

bool CheckForSpeak(int iCharacterIndex)
{
	ref chr = &Characters[iCharacterIndex];

	if (!CheckAttribute(chr, "speak.ransom.offered"))
	{
		if (Getrelation(iCharacterIndex, nMainCharacterIndex) == RELATION_ENEMY)
		{
			if(IsCompanion(GetCharacter(sti(chr.SeaAI.Task.Target))))
			{
			    //#20180524-01 Remove unneeded sqrt
                float fMapDisable =  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER *  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
                float fDistance = Ship_GetDistance2DRel(chr, pchar);
                if (fDistance < fMapDisable)
				{
					//trace("etape 5 seaspeak")
					//#20200307-03
					int nTimes = 15;
					int nSurr = SurrenderEnabled;
                    if(nSurr > 1)
                        nTimes *= nSurr;
					if(CheckAttribute(chr, "seatime.thinkSurr") && sti(chr.seatime.thinkSurr) > nSurr)
                        return true;
                    else
                        return false;
				}
			}
		}
	}
	return false;
}

bool CalculateForRansom(ref rEnemyChar)
{
//trace("CalculateForRansom: rEnemyChar.id:" + rEnemyChar.id);
	if(CheckAttribute(rEnemyChar, "cannotsurrender"))
	{
		return false;
	}
    //#20180115-02 Correct speak/surrender
	if(CheckAttribute(rEnemyChar, "DontRansackCaptain"))
        return false;
    if (CheckAttribute(rEnemyChar, "AlwaysEnemy"))
        return false;

	//return CheckForSurrender(pchar, rEnemyChar, 1)
	return Ship_Check_Surrender(GetCharacterIndex(rEnemyChar.id),3.0) //check for surrender with high surrender morale multiplier
}

bool CalculateForCapture(aref rSpeakCharacter)
{
	if(CheckAttribute(rSpeakCharacter, "cannotsurrender"))
	{
		return false;
	}
	//#20180115-02 Correct speak/surrender
	if(CheckAttribute(rSpeakCharacter, "DontRansackCaptain")) {
        return false;
	}
	string sResult = "";

	//return CheckForSurrender(pchar, rSpeakCharacter, 3)  // old surrender check
	return Ship_CheckMoraleFail(GetCharacterIndex(rSpeakCharacter.id),0.9) // They were thinking of surrendering anyway
}

int CalculateSumm(aref chr)
{
    //#20171230-02
    int iMoney = sti(chr.money);
    if(iMoney <1500)
    {
        iMoney = rand(1250) + rand(250) + 300;
        if(rand(99) < 5) //Big money
            iMoney = iMoney + rand(3500);
        chr.money = iMoney;
    }
	int iPrice = chr.money * 0.2 * GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 2);
    //trace("etape 8 seaspeak")
	/*
	int iTradeType;

	int iPrice = 0;

	for (int i = GOOD_WHEAT; i<GOODS_QUANTITY; i++)
	{
		iTradeType = GetCargoGoods(chr, i);
		iPrice = iPrice + sti(Goods[i].cost)*(0.5 + GetSummonSkillFromName(Pchar, SKILL_COMMERCE)/5);
	}*/

	return iPrice;
}
