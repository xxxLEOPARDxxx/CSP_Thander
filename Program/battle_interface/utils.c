native float funcGetSailSpeed(int holeQ,int holeMax,float sailPow);
native float GetSailSpeed(int holeQ, int holeMax, float maxSpeed, float fSailHoleDepend);
native int RandomHole2Sail(int chrIdx, string reyName, int groupNum, int maxHole, int holeData, int addHoleQ);
native int DeleteOneSailHole(int chrIdx, string groupName, string reyName, int holeMask, int deleteHoleQ );
native string GetAssembledString(string formatStr, aref arDataBase);
native int ShipSailState(int chrIdx);

#libriary "script_rigging_files"

//==========================================================
//   Секция починки при использовании специальных умений.
//
//==========================================================
#define BI_SLOW_REPAIR_PERCENT	1
#define BI_SLOW_REPAIR_PERIOD	3000
#define BI_FAST_REPAIR_PERCENT	1.0
#define BI_FAST_REPAIR_SAIL		3.0
#define BI_FAST_REPAIR_PERIOD	50

#event_handler("evntActionRepair","procActionRepair");

void ActivateSpecRepair(ref chref,int repairType)
{
	if(repairType==0)
	{	PostEvent("evntActionRepair",BI_SLOW_REPAIR_PERIOD,"ll",sti(chref.index),0);
	}
	else
	{	PostEvent("evntActionRepair",BI_FAST_REPAIR_PERIOD,"llff",sti(chref.index),1, 0.0,0.0);
	}
}

void procActionRepair()
{
	int chrIdx = GetEventData();
	int eRepType = GetEventData();

	if(eRepType!=0) // fix
	{
		float fMaterialH = GetEventData();
		float fMaterialS = GetEventData();
	}

	if(chrIdx<0) return;
	if(!bSeaActive)	return;
	ref chref = GetCharacter(chrIdx);
	// boal 29.02.2004 -->
	if (!IsCompanion(chref)) return;
	// boal 29.02.2004 <--
	if( LAi_IsDead(chref) ) return;

	if(bAbordageStarted)
	{
		if(eRepType==0)
		{
			PostEvent("evntActionRepair",BI_FAST_REPAIR_PERIOD,"ll", chrIdx, 0);
		}
		else
		{
			PostEvent("evntActionRepair",BI_FAST_REPAIR_PERIOD,"llff", chrIdx, eRepType, fMaterialH,fMaterialS);
		}
		return;
	}

	float hpp = GetHullPercent(chref);
	float spp = GetSailPercent(chref);
	float fRepairH,fRepairS;
	if(eRepType==0)
	//=====================================================
	// Slow repair
	//=====================================================
	{
		if(hpp<10.0)
		{
			fRepairH = 10.0-hpp;
			if(fRepairH>BI_SLOW_REPAIR_PERCENT)	{fRepairH=BI_SLOW_REPAIR_PERCENT;}
			hpp += ProcessHullRepair(chref,fRepairH);
		}
		if(spp<10.0)
		{
			fRepairS = 10.0-spp;
			if(fRepairS>BI_SLOW_REPAIR_PERCENT)	{fRepairS=BI_SLOW_REPAIR_PERCENT;}
			spp += ProcessSailRepair(chref,fRepairS);
		}
		//if( IsPerkIntoList("LightRepair") ) {
		if (CheckOfficersPerk(chref, "LightRepair"))
		{
			PostEvent("evntActionRepair",BI_SLOW_REPAIR_PERIOD,"ll",chrIdx,0);
		}
	}
	else
	//======================================================
	// Fast repair
	//======================================================
	{
		float ftmp1,ftmp2;
		int nMaterialH = GetCargoGoods(chref,GOOD_PLANKS);
		int nMaterialS = GetCargoGoods(chref,GOOD_SAILCLOTH);
		int nMatDeltaH = 0;
		int nMatDeltaS = 0;
		string goodsName;
		int iRepair = GetSummonSkillFromName(chref, SKILL_REPAIR) - 1;
		iRepair /= 20;//каждые 20 скилла начиная с 41 дают ускорение починки
		if(iRepair == 0)
			iRepair++;
		if(chref.Fellows.Passengers.carpenter > 0)
			iRepair++;
		//ftmp1 = GetCharacterShipHP(chref);
		//ftmp2 = stf(chref.Ship.HP)*InstantRepairRATE*0.01;//макс хп * InstantRepairRATE из _mod_on_off.c
		if(hpp < InstantRepairRATE && nMaterialH > 0)//if(hpp < InstantRepairRATE && nMaterialH>0) // boal 23.01.2004
		{
			//Log_Info(" carpenter "+chref.Fellows.Passengers.carpenter);
			//Log_Info("Скорость ремонта "+iRepair);
			//iRepair = MakeInt(iRepair);
			fRepairH = makefloat(iRepair*BI_FAST_REPAIR_PERCENT);
			if(CheckOfficersPerk(chref, "Carpenter"))
				fRepairH *= 1.1;
			if(CheckOfficersPerk(chref, "Builder"))
			{
				ftmp1 = BI_FAST_REPAIR_PERCENT*0.9;
				if(!CheckAttribute(chref, "ship.MatDelta"))
					chref.ship.MatDelta = 0.01;
				ftmp1 += stf(chref.ship.MatDelta);
				if(ftmp1 >= 1)
				{
					nMatDeltaH = ftmp1;
					//Log_Info("nMatDeltaH "+nMatDeltaH+" ftmp1 "+ftmp1);
					ftmp1 -= nMatDeltaH;
				}
				chref.ship.MatDelta = ftmp1;
			}
			else
				nMatDeltaH = BI_FAST_REPAIR_PERCENT;
			fMaterialH = 0.0;
			/* старый механ
			if(nMaterialH>=1)
			{fRepairH = InstantRepairRATE - hpp; // boal 23.01.2004
			//if(fRepairH>BI_FAST_REPAIR_PERCENT)	{fRepairH=BI_FAST_REPAIR_PERCENT;}
			ftmp1 = GetHullPPP(chref)*5; //*1
			ftmp2 = MaterialH + ftmp1*fRepairH;
			}
			if(ftmp2>nMaterialH)
			{
				fRepairH = (nMaterialH-fMaterialH)/ftmp1;
				nMatDeltaH = nMaterialH;
				fMaterialH = 0.0;
			}
			else
			{
				if(ftmp2>1.0)
				{
					nMatDeltaH = makeint(ftmp2);
					fMaterialH = ftmp2 - nMatDeltaH;
				}
			}*/
			ProcessHullRepairDigital(chref,fRepairH);
		}
		if(spp < InstantRepairRATE && nMaterialS>0) // boal 23.01.2004
		{
			//fRepairS = ProcessSailRepairFast(chref,fRepairS);
			//Log_Info("fRepairS "+chref.ship.Repair+"GetSailPercent(chref) "+chref.ship.SP);
			//else{chref.ship.Repair = 1;}
			//Log_Info("fRepairS "+chref.ship.Repair);
			//bool allow = CalculateShipSP(chref) >= GetSailPercent(chref);
			//Log_Info("chref.ship.scriptsp "+chref.ship.scriptsp+" chref.ship.sp "+chref.ship.sp);
			ftmp1 = GetCharacterShipClass(chref);//замедление починки парусов от класса выше 5
			if(ftmp1 < 5)
				ftmp1 = (6 - ftmp1);//первоклассник в 5 раз
			else
				ftmp1 = 1;
			if(!CheckAttribute(chref, "chref.ship.RepairS"))
				chref.ship.RepairS = 0.01;
			fRepairS = stf(chref.ship.RepairS);
			fRepairS += (BI_FAST_REPAIR_PERCENT*iRepair*BI_FAST_REPAIR_SAIL*(1+1.1*CheckOfficersPerk(chref, "Carpenter"))) / (CalculateShipHoles(chref)*ftmp1);//тут происходит основной расчет ремонта - доп.модификатор * бонус навыка * опорное число * бонус перка плотник / количество дырок * модификатор класса
			chref.ship.RepairS = fRepairS;
			//Log_Info("chref.ship.sp "+chref.ship.sp+" chref.ship.RepairS "+chref.ship.RepairS);
			if(fRepairS > 0)
				chref.ship.RepairS = ProcessSailRepairFast(chref, fRepairS);
				//Log_Info("chref.ship.RepairS "+chref.ship.RepairS);
			if(fRepairS != stf(chref.ship.RepairS))
			{
				if(CheckOfficersPerk(chref, "Builder"))
				{
					ftmp2 = BI_FAST_REPAIR_PERCENT*0.9;
					if(!CheckAttribute(chref, "ship.MatDeltaS"))
						chref.ship.MatDeltaS = 0.01;
					ftmp2 += stf(chref.ship.MatDeltaS);
					if(ftmp2 >= 1)
					{
						nMatDeltaS = ftmp2;
						//Log_Info("nMatDeltaS "+nMatDeltaS+" ftmp1 "+ftmp1);
						ftmp2 -= nMatDeltaS;
					}
					chref.ship.MatDeltaS = ftmp2;
				}
				else
				{
					nMatDeltaS = BI_FAST_REPAIR_PERCENT;
				}
			}
			else
			{
				nMatDeltaS = 0;
			}
			//Log_Info("nMatDeltaS "+nMatDeltaS);
			//if(fRepairS>BI_FAST_REPAIR_PERCENT)
			//	{fRepairS=BI_FAST_REPAIR_PERCENT;}
			//Log_Info("ремонт "+ fRepairS + " nMatDeltaS " + nMatDeltaS + "fMaterialS" + fMaterialS);
			/*старое
			fRepairS = InstantRepairRATE -spp; // boal 23.01.2004
			if(fRepairS>BI_FAST_REPAIR_PERCENT)	{fRepairS=BI_FAST_REPAIR_PERCENT;}
			ftmp1 = GetSailSPP(chref)*5; //*1
			ftmp2 = fMaterialS + ftmp1*fRepairS;
			if(ftmp2>nMaterialS)	{ fRepairS = (nMaterialS-fMaterialS)/ftmp1; }
			fRepairS = ProcessSailRepair(chref,fRepairS);
			if(fRepairS<=0.0)
			{
				nMatDeltaS = 0;
				fMaterialS = 0.0;
				nMaterialS = 0;
			}
			else
			{
				ftmp2 = fMaterialS + ftmp1*fRepairS;
				if(ftmp2>1.0)
				{
					nMatDeltaS = makeint(ftmp2);
					fMaterialS = ftmp2 - nMatDeltaS;
				}
			}
			*/
		}
		if(nMatDeltaH>0)
		{
			nMaterialH -= nMatDeltaH;
			goodsName = Goods[GOOD_PLANKS].Name;
			chref.Ship.Cargo.Goods.(goodsName) = nMaterialH;
			chref.Ship.Cargo.Load = sti(chref.Ship.Cargo.Load) - sti(Goods[GOOD_PLANKS].Weight)*nMatDeltaH;
		}
		if(nMatDeltaS>0)
		{
			nMaterialS -= nMatDeltaS;
			goodsName = Goods[GOOD_SAILCLOTH].Name;
			chref.Ship.Cargo.Goods.(goodsName) = nMaterialS;
			chref.Ship.Cargo.Load = sti(chref.Ship.Cargo.Load) - sti(Goods[GOOD_SAILCLOTH].Weight)*nMatDeltaS;
		}
		/*if(GetOfficersPerkUsingIdx(chref, "InstantRepair") > 0)
			{repairAllow = true;}
		else
		{
			if(!bAltBalance && chref.perks.list.InstantRepair.active > 0)
			{repairAllow = true}
		}*/
		//Log_Info("CheckOfficersPerk "+CheckOfficersPerk(chref, "InstantRepair"));
		if (CheckOfficersPerk(chref, "InstantRepair"))
		{
			if((hpp < InstantRepairRATE)) // boal 23.01.2004
			{	PostEvent("evntActionRepair",BI_FAST_REPAIR_PERIOD,"llff",chrIdx,1, fMaterialH,fMaterialS);
			}
			else
			{
				if(spp < InstantRepairRATE) // boal 23.01.2004
				{	PostEvent("evntActionRepair",BI_FAST_REPAIR_PERIOD,"llff",chrIdx,1, fMaterialH,fMaterialS);
				}
				else
				{
					// EnableUsingAbility(chref,"InstantRepair"); // сам выключится, иначе прописывается ГГ
				}
			}
		}
	}
}
//============================================================

//============================================================
//	Починка заданного количества процентов повреждения корпуса
// (возвращает число реально починеных процентов,
//  материалы не использует, пробоины в корпусе удаляет)
//============================================================
float ProcessHullRepair(ref chref,float repPercent)
{
	float dmg = 100.0 - GetHullPercent(chref);
	if(dmg==0.0) return 0.0;
	if(repPercent>dmg) repPercent=dmg;
	int blotsQuantity = GetBlotsQuantity(chref);
	int repBlots = makeint(blotsQuantity*repPercent/dmg);
	DeleteBlots(chref,repBlots);
	float baseHP = makefloat(GetCharacterShipHP(chref));
	chref.ship.HP = baseHP+(repPercent-dmg)*baseHP/100.0;
	if(sti(chref.ship.HP) > baseHP)
	{
		chref.ship.HP = baseHP;
	}
	return repPercent;
}

//	Починка заданного количества единиц повреждения корпуса - bestreducer
float ProcessHullRepairDigital(ref chref,float Digit)
{
	int baseHP = GetCharacterShipHP(chref);
	//Log_Info("baseHP " + baseHP);
	//Log_Info("Digit " + Digit);
	int dmg = baseHP - sti(chref.ship.HP);
	//Log_Info("dmg " + dmg);
	//Log_Info("chref.ship.HP " + chref.ship.HP);
	if(dmg==0.0) return 0.0;
	if(Digit>dmg) Digit=dmg;
	int blotsQuantity = GetBlotsQuantity(chref);
	int repBlots = makeint(blotsQuantity*Digit/dmg);
	//Log_Info("repBlots "+repBlots);
	DeleteBlots(chref,repBlots);
	chref.ship.HP = makefloat(baseHP+Digit-dmg);
	return Digit;
}
//============================================================
//	Починка заданного количества процентов повреждения парусов
// (возвращает число реально починеных процентов,
//  материалы не использует, дырки залатывает)
//============================================================
float ProcessSailRepair(ref chref, float repPercent)
{
	float dmg = 100.0-GetSailPercent(chref);
	if(dmg==0.0) return 0.0;
	if(repPercent>dmg) repPercent=dmg;

	float fMakeRepair = repPercent;
	int i,j,rq,gq;
	aref arRoot,arGroup,arSail;
	string tmpstr;
	makearef(arRoot, chref.ship.sails);
	rq = GetAttributesNum(arRoot);

	for(i=0; i<rq; i++)
	{
		arGroup = GetAttributeN(arRoot, i);
		gq = GetAttributesNum(arGroup);
		for(j=0; j<gq; j++)
		{
			arSail = GetAttributeN(arGroup, j);

			if( CheckAttribute(arSail,"mastFall") )
			{
				tmpstr = "ship.masts."+arSail.mastFall;
				if( CheckAttribute(chref,tmpstr) && stf(chref.(tmpstr))>=1.0 )	{continue;}
			}
			fMakeRepair -= OneSailDmgRepair(chref,arGroup,arSail,fMakeRepair);
			if(fMakeRepair<=0.0) {break;}
			if(!CheckAttribute(chref,"ship.sails")) break;
			if(GetAttributesNum(arRoot)!=rq) break;
			if(GetAttributesNum(arGroup)!=gq)
			{
				gq = GetAttributesNum(arGroup);
				j--;
			}
		}
		if(fMakeRepair<=0.0) {break;}
		if(!CheckAttribute(chref,"ship.sails")) break;
		if(GetAttributesNum(arRoot)!=rq)
		{
			rq = GetAttributesNum(arRoot);
			i--;
		}
	}
	chref.ship.sp = CalculateShipSP(chref);
	return repPercent;
}

// Починка заданного количества дырок - bestreducer
float ProcessSailRepairFast(ref chref, float fMakeRepair)
{
	float dmg = 100.0-GetSailPercent(chref);
	//if(dmg==0.0) return 0.0;
	//if(repPercent>dmg) repPercent=dmg;
	int i,j,rq,gq;
	aref arRoot,arGroup,arSail;
	string tmpstr;
	makearef(arRoot, chref.ship.sails);
	rq = GetAttributesNum(arRoot);
	for(i=0; i<rq; i++)
	{
		arGroup = GetAttributeN(arRoot, i);
		gq = GetAttributesNum(arGroup);
		for(j=0; j<gq; j++)
		{
			arSail = GetAttributeN(arGroup, j);

			if( CheckAttribute(arSail,"mastFall") )
				continue;
			/*{
				tmpstr = "ship.masts."+arSail.mastFall;
				if( CheckAttribute(chref,tmpstr) && stf(chref.(tmpstr))>=1.0 )
					{continue;}
			}*/
			//fMakeRepair -= OneSailDmgRepair(chref,arGroup,arSail,fMakeRepair);
				if (!CheckAttribute(arSail, "dmg"))
					continue; // fix boal 18.08.06
				float fSailDmg = stf(arSail.dmg);
				float sailDmgMax = GetCharacterShipSP(chref) * stf(arSail.sp);
				if(fMakeRepair<=0.0)
					break;
				//Log_Info("ремонт: " + fMakeRepair + " повреждение " + fSailDmg);
				if (fSailDmg <= 0.0 || !CheckAttribute(arSail, "hd"))
					continue;  // fix boal 14.09.06

				if (fMakeRepair>=fSailDmg)
				{
						DeleteOneSailHole( sti(chref.index), GetAttributeName(arSail), GetAttributeName(arGroup), sti(arSail.hd), sti(arSail.hc) );
						DeleteAttribute(arGroup,GetAttributeName(arSail));
						if( GetAttributesNum(arGroup)==0 )
							{DeleteAttribute(chref,"ship.sails."+GetAttributeName(arGroup));}
					fMakeRepair -= fSailDmg;
					continue;
				}

				fSailDmg -= fMakeRepair;
				int iAfterHole = GetNeedHoleFromDmg( fSailDmg, sailDmgMax, sti(arSail.mhc) );
				fMakeRepair += (MakeFloat(iAfterHole)/stf(arSail.mhc))*sailDmgMax - fSailDmg/stf(arSail.sp);//получение значения починки после починки движком
				//Log_Info("fMakeRepair "+fMakeRepair+" fAfterHole "+fAfterHole+" fSailDmg "+fSailDmg);
				if( sti(arSail.hc) > iAfterHole )
				{
					arSail.hd = DeleteOneSailHole( sti(chref.index), GetAttributeName(arSail), GetAttributeName(arGroup), sti(arSail.hd), sti(arSail.hc)-iAfterHole );
					arSail.hc = iAfterHole;
				}
				arSail.dmg = fSailDmg;
////////////////////////////////////////
			if(fMakeRepair<=0.0) {break;}
			if(!CheckAttribute(chref,"ship.sails")) break;
			if(GetAttributesNum(arRoot)!=rq) break;
			if(GetAttributesNum(arGroup)!=gq)
			{
				gq = GetAttributesNum(arGroup);
				j--;
			}
		}
		if(fMakeRepair<=0.0) {break;}
		if(!CheckAttribute(chref,"ship.sails")) break;
		if(GetAttributesNum(arRoot)!=rq)
		{
			rq = GetAttributesNum(arRoot);
			i--;
		}
	}
	//chref.ship.RepairS = fMakeRepair;
	chref.ship.sp = CalculateShipSP(chref);
	return fMakeRepair;
}

//=========================================================================
//	Починка заданного количества процентов повреждения конкретного паруса
//=========================================================================
float OneSailDmgRepair(ref chref, aref arSailNode, aref arSail, float fDmgRepair)
{
	if(fDmgRepair<=0.0) return 0.0;
	if (!CheckAttribute(arSail, "dmg")) return 0.0; // fix boal 18.08.06
	float fSailDmg = stf(arSail.dmg);

	if (fSailDmg <= 0.0 || !CheckAttribute(arSail, "hd"))  return 0.0;  // fix boal 14.09.06

	if (fDmgRepair>=fSailDmg)
	{
		DeleteOneSailHole( sti(chref.index), GetAttributeName(arSail), GetAttributeName(arSailNode), sti(arSail.hd), sti(arSail.hc) );
		DeleteAttribute(arSailNode,GetAttributeName(arSail));
		if( GetAttributesNum(arSailNode)==0 )
		{
			DeleteAttribute(chref,"ship.sails."+GetAttributeName(arSailNode));
		}
		return fSailDmg;
	}

	fSailDmg -= fDmgRepair;
	float sailDmgMax = GetCharacterShipSP(chref) * stf(arSail.sp);
	int iAfterHole = GetNeedHoleFromDmg( fSailDmg, sailDmgMax, sti(arSail.mhc) );
	if( sti(arSail.hc) > iAfterHole )
	{
		arSail.hd = DeleteOneSailHole( sti(chref.index), GetAttributeName(arSail), GetAttributeName(arSailNode), sti(arSail.hd), sti(arSail.hc)-iAfterHole );
		arSail.hc = iAfterHole;
	}
	arSail.dmg = fSailDmg;
	return fDmgRepair;
}

//============================================================
// Получить число дырок в корпусе корабля
//============================================================
int GetBlotsQuantity(ref chref)
{
	if( !CheckAttribute(chref,"ship.blots") ) return 0;
	aref blref;
	makearef(blref,chref.ship.blots);
	return GetAttributesNum(blref);
}

//============================================================
// Удалить заданное число дырок в корпусе корабля
//============================================================
void DeleteBlots(ref chref, int repBlots)
{
	if( !CheckAttribute(chref,"ship.blots") ) return;
	aref blref,curblots;
	makearef(blref,chref.ship.blots);
	int blotsQ = GetAttributesNum(blref);
	while(repBlots>0)
	{
		if(blotsQ==0) break;
		blotsQ--;
		curblots = GetAttributeN(blref,blotsQ);
		DeleteAttribute(blref,GetAttributeName(curblots));
	}
}

//================================================================
// Получить число дырок в парусах исходя из имеющихся повреждений
//================================================================
int GetNeedHoleFromDmg(float sailDmg, float sailDmgMax, int maxHoleCount)
{
	if(sailDmgMax<=0.0) return 0;
	int holeNeed = makeint(sailDmg/sailDmgMax*maxHoleCount);
	return holeNeed;
}

//================================================================
// Надырявить конкретный парус на заданное число дырок и получить
// маску получившихся дырок
// (в параметрах координаты паруса: индекс перса, полное имя реи и
//  номер группы; затем идут максимальное возможное число дырок в
//  парусе, текущая маска дырок и число дополнительных дырок)
//================================================================

//================================================================
// Получить повреждение в парусах исходя из имеющихся дырок
//================================================================
float GetNeedDmgFromHole(int holeCount, float sailDmgMax, int maxHoleCount)
{
	if(maxHoleCount<=0) return 0.0;
	return sailDmgMax*holeCount/maxHoleCount;
}

//================================================================
// Посчитать состояние парусов
//================================================================
float CalculateShipSP(ref chref)
{
	float fSP = GetCharacterShipSP(chref);
	aref arRoot,arGroup,arSail;
	int q,n,i,j;

	makearef(arRoot, chref.ship.sails);
	q = GetAttributesNum(arRoot);
	for(i=0; i<q; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		n = GetAttributesNum(arGroup);
		for(j=0; j<n; j++)
		{
			arSail = GetAttributeN(arGroup,j);
			if(!CheckAttribute(arSail, "dmg"))
			{
				arSail.dmg = 0.0;
			}
			fSP -= stf(arSail.dmg);
		}
	}

	if(fSP<0.0) fSP = 0.0;
	return fSP;
}

//посчитать макс.количество дырок на корабле
int CalculateShipHoles(ref chref)
{
	aref arRoot,arGroup,arSail;
	int Holes = 0;
	int q,n,i,j;

	makearef(arRoot, chref.ship.sails);
	q = GetAttributesNum(arRoot);
	for(i=0; i<q; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		n = GetAttributesNum(arGroup);
		for(j=0; j<n; j++)
		{
			arSail = GetAttributeN(arGroup,j);
			Holes += sti(arSail.mhc);
		}
	}
	return Holes;
}
//===============================================
// Заполнение
//===============================================
int AddTextureToList(ref rHostObj, string texName, int hSize, int vSize)
{
	return SendMessage(rHostObj, "lsll", BI_MSG_ADD_NEWTEXTURE, texName, hSize, vSize);
}

void GetTextureUVForShip(int nShipType, ref rLeft, ref rTop, ref rRight, ref rBottom)
{
	float fLeft = 0.0;
	float fTop = 0.0;
	float fRight = 0.03125;
	float fBottom = 0.03125;//0.25;

	if( nShipType> -1 && nShipType<SHIP_TYPES_QUANTITY_WITH_FORT ) // <-- ugeen fix, для тартаны nShipType = 0 !!!!
	{
		ref rBaseShip = &ShipsTypes[nShipType];
		SetShipPictureDataByShipTypeName( rBaseShip.name );
		int nV = BI_intNRetValue[0] / 32;
		int nH = BI_intNRetValue[0] - nV * 32;
		fLeft = stf(nH) * 0.03125;
		fTop = stf(nV) * 0.03125;//0.25;
		fRight = fLeft + 0.03125;
		fBottom = fTop + 0.03125;//0.25;
	}

	rLeft = fLeft;
	rTop = fTop;
	rRight = fRight;
	rBottom = fBottom;
}

object objTimerInterface;
#event_handler("evntTimerTimeOut","procTimerTimeOut");
void InitTimerInterface()
{
	float fHtRatio = stf(Render.screen_y) / screenscaling;
	DeleteAttribute( &objTimerInterface, "" );
	objTimerInterface.timerpos = RecalculateHIcon(makeint(100*fHtRatio))+","+RecalculateVIcon(makeint(20*fHtRatio))+","+RecalculateHIcon(makeint(228*fHtRatio))+","+RecalculateVIcon(makeint(40*fHtRatio));
	objTimerInterface.timeroffset = "0,0,0,0";
	objTimerInterface.timerbackuv = "0.0,0.0,1.0,0.5";
	objTimerInterface.timerforeuv = "0.0,0.5,1.0,1.0";
	objTimerInterface.timerbackcolor = argb(255,128,128,128);
	objTimerInterface.timerforecolor = argb(255,128,128,128);
	CreateEntity( &objTimerInterface, "BITimer" );
	LayerAddObject(SEA_REALIZE,&objTimerInterface,-1);
	LayerAddObject(REALIZE,&objTimerInterface,-1);
}

void LaunchTimerInterface(float fTime,string questtype,string questname)
{
	objTimerInterface.questname = questname;
	objTimerInterface.questtype = questtype;
	SendMessage(&objTimerInterface,"lfs",0,fTime,"evntTimerTimeOut");
}

void CloseTimerInterface()
{
	SendMessage(&objTimerInterface,"l",1);
}

void procTimerTimeOut()
{
	QuestComplete(objTimerInterface.questtype, objTimerInterface.questname);
}
