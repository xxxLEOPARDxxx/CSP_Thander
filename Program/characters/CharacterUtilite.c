#define FELLOWTRAVEL_NO			0
#define FELLOWTRAVEL_CAPTIVE	1
#define FELLOWTRAVEL_PASSENGER	2
#define FELLOWTRAVEL_OFFICER	3
#define FELLOWTRAVEL_COMPANION	4

#define EVENT_CHANGE_OFFICERS	"EvntChangeOfficers"
#define EVENT_CHANGE_COMPANIONS	"EvntChangeCompanions"

#define MAX_ITEM_TAKE	5000

#define MSGICON_ACTIVE_TIME 10
#define MSGICON_LEVELUP	0
#define MSGICON_LOGBOOK	1
#define MSGICON_GETITEM	2

//Boyer add
#define GUN_SPEED_BASE 10.0
#define GUN_MIN_WT 0.75
#define GUN_MAX_WT 0.5

//Boyer add
int MAX_NUM_FIGHTERS = MOD_OFFICERS_RATE; // Range from 3 to 8...or 10 is the most supported by battle_mansign, but only 6 display on
// screen, given heights of icons and real estate available.
#event_handler("evnt_MsgIconTick","proc_MsgIconTick");

bool GetShipRemovable(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"ShipRemovable") && sti(_refCharacter.ShipRemovable) == false )
	{
		return false;
	}
	return true;
}

bool GetShipRemovableEx(ref _refCharacter)
{
	if(GetShipRemovable(_refCharacter) == false && _refCharacter.id != pchar.id)
	{
		return false;
	}
	return true;
}

void SetShipRemovable(ref _refCharacter, bool bRemovable)
{
	if(bRemovable)
	{
		DeleteAttribute(_refCharacter,"ShipRemovable");
	}
	else
	{
		_refCharacter.ShipRemovable = false;
	}
}

//ugeen --> проверка, является ли персонаж глав.героем
bool IsMainCharacter(ref chr)
{
	if(CheckAttribute(chr,"chr_ai.type") && chr.chr_ai.type == LAI_TYPE_PLAYER) return true;
	if(CheckAttribute(chr,"index") && sti(chr.index) == GetMainCharacterIndex()) return true;
	return false;
}
// <-- ugeen

//
bool CharacterIsDead(ref _refCharacter)
{
	return LAi_IsDead(_refCharacter);
}

bool IsCompanion(ref _refCharacter)
{
	int findIdx = 0;

	if (CheckAttribute(_refCharacter,"index")) 
	{
   		findIdx = sti(_refCharacter.index);
	}
	ref mc = GetMainCharacter();
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if(GetCompanionIndex(mc,i)==findIdx) return true;
	}
	return false;
}

bool IsOfficer(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	for(int i=0; i<=MAX_NUM_FIGHTERS; i++)
	{
		if(GetOfficersIndex(mc,i)==findIdx) return true;
	}
	return false;
}

void SetCharacterRemovable(ref _refCharacter,bool removable)
{
	if(removable) DeleteAttribute(_refCharacter,"NonRemovable");
	else _refCharacter.NonRemovable = true;
}

bool GetRemovable(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"NonRemovable") ) return !sti(_refCharacter.NonRemovable);
	return true;
}

// Cargo utilites
//------------------------------------------
int GetCargoLoad(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Cargo.Load")) return 0;
	int iLoad = sti(_refCharacter.Ship.Cargo.Load);
	return iLoad;
}

int GetCargoLoadEx(ref _refCharacter, int addGoods, int iGoods)
{
	int iGoodsQ = addGoods;
	if(iGoodsQ < 0)
	{
		iGoodsQ = -iGoodsQ;
	}
	iGoodsQ = GetGoodWeightByType(iGoods, iGoodsQ);//addGoods / sti(Goods[iGoods].units);

	int iLoad;

	if(addGoods < 0)
	{
		iLoad = GetCargoLoad(_refCharacter) - iGoodsQ;
	}
	else
	{
		iLoad = GetCargoLoad(_refCharacter) + iGoodsQ;
	}

	return iLoad;
}

int RecalculateCargoLoad(ref _refCharacter)
{
	int loadSpace = 0;
	// boal 27/07/06 учет орудий на борту -->
	if (CheckAttribute(_refCharacter,"Ship.Cannons.Type") && sti(_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		ref Cannon = GetCannonByType(sti(_refCharacter.Ship.Cannons.Type));
		loadSpace = GetCannonsNum(_refCharacter) * sti(Cannon.Weight);
	}
	// учет орудий на борту <--
	// ugeen --> учет веса экипажа (1 тушка члена экипажа весит 1 ц.)
	if (bSailorsWeight)
	{
		loadSpace = loadSpace + GetCrewQuantity(_refCharacter);
	}
	// <-- учет веса экипажа
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		loadSpace = loadSpace + GetGoodWeightByType(i,GetCargoGoods(_refCharacter,i));
	}
	_refCharacter.Ship.Cargo.Load = loadSpace;
	return loadSpace;
}

int GetCargoFreeSpace(ref _refCharacter)
{
	int freeSpace = GetCargoMaxSpace(_refCharacter) - GetCargoLoad(_refCharacter);
	if (freeSpace < 0) freeSpace = 0;  // fix
	return freeSpace;
}

int GetCargoSquadronFreeSpace(ref _refCharacter)
{
	int freeSpace = GetCargoMaxSpace(_refCharacter) - GetCargoLoad(_refCharacter);
	int i, cn;
	ref chref;
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
  		if(cn != -1 && GetRemovable(&Characters[cn]))
		{
			chref = GetCharacter(cn);
			freeSpace += GetCargoMaxSpace(chref) - GetCargoLoad(chref);
		}
	}
	if (freeSpace < 0) freeSpace = 0;  // fix
	return freeSpace;
}

int GetCargoMaxSpace(ref _refCharacter)
{
	if( !CheckAttribute(_refCharacter,"Ship.Type") ) return 0;
	int _ShipType = sti(_refCharacter.Ship.Type);
	if( _ShipType==SHIP_NOTUSED )
		return 0;
	return sti(RealShips[_ShipType].Capacity);
}

int GetCharacterFreeSpace(ref _refCharacter,int _Goods)
{
	int g = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(_refCharacter) );
	if (g < 0) g = 0; // fix
	return g;
}

int GetSquadronFreeSpace(ref _refCharacter,int _Goods)
{
	float weight = stf(Goods[_Goods].weight);
	if(weight==0.0) weight = 0.00001;
	int unitQ = sti(Goods[_Goods].Units);

	int retVal = unitQ * (GetCargoFreeSpace(_refCharacter)/weight);
	int i,cn;
	ref chref;
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
  		if(cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			chref = GetCharacter(cn);
			//if(GetShipRemovableEx(chref))
			//{
				retVal = retVal + unitQ*(GetCargoFreeSpace(chref)/weight);
			//}
		}
	}
	if (retVal < 0) retVal = 0; // fix
	return retVal;
}

int GetCargoGoods(ref _refCharacter,int _Goods)
{
	string goodsName = Goods[_Goods].name;
	if(!CheckAttribute(_refCharacter,"Ship.Cargo.Goods."+goodsName))
		return 0;
	return sti(_refCharacter.Ship.Cargo.Goods.(goodsName));
}

int GetSquadronGoods(ref _refCharacter,int _Goods)
{
	int i,cn;
	ref chref;
	int retVal = GetCargoGoods(_refCharacter,_Goods);
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			chref = GetCharacter(cn);
			if( GetShipRemovableEx(chref) )
			{
				retVal = retVal + GetCargoGoods(chref,_Goods);
			}
		}
	}
	return retVal;
}

void SetCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	string goodsName = Goods[_Goods].name;
	_refCharacter.Ship.Cargo.Goods.(goodsName) = _Quantity;
	int curLoad = RecalculateCargoLoad(_refCharacter);
	int maxLoad = GetCargoMaxSpace(_refCharacter);
	if(curLoad>maxLoad)
	{
		Trace("ERROR! Cargo space overup (character=" + _refCharacter.index + ",Quantity=" + _Quantity + ")");
	}
}

// boal -->
int RemoveCharacterGoodsSelf(ref _refCharacter,int _Goods,int _Quantity)
{
	int    curQuantity;
	string goodsName = Goods[_Goods].name;

	curQuantity = sti( _refCharacter.Ship.Cargo.Goods.(goodsName) );
	if (curQuantity>=_Quantity)
	{
		_refCharacter.Ship.Cargo.Goods.(goodsName) = curQuantity - _Quantity;
		RecalculateCargoLoad(_refCharacter);
		return true;
	}
	_refCharacter.Ship.Cargo.Goods.(goodsName) = 0;
	//_Quantity = _Quantity - curQuantity;
	RecalculateCargoLoad(_refCharacter);
	return false;
}
// доработал метод, теперь возвращает сколько взял
int AddCharacterGoodsSimple(aref aCharacter, int iGood, int iQuantity)
{
	string sGoodName = Goods[iGood].name;
	int    freeQuantity;

	freeQuantity = GetGoodQuantityByWeight(iGood, GetCargoFreeSpace(aCharacter));
	if (freeQuantity < 0) freeQuantity = 0; //fix
	if (freeQuantity > iQuantity)
	{
		freeQuantity = iQuantity;
	}
	aCharacter.Ship.Cargo.Goods.(sGoodName) = sti(aCharacter.Ship.Cargo.Goods.(sGoodName)) + freeQuantity;
	RecalculateCargoLoad(aCharacter);
	return freeQuantity;
}
// boal <--

int AddCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	int i,cn,freeQuantity;
	string goodsName = Goods[_Goods].name;

	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			freeQuantity = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(&Characters[cn]) );
			if(freeQuantity>=_Quantity)
			{
				Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + _Quantity;
				RecalculateCargoLoad(&Characters[cn]);
				return true;
			}
			Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + freeQuantity;
			_Quantity = _Quantity - freeQuantity;
			RecalculateCargoLoad(&Characters[cn]);
		}
	}
	Trace("Overup cargo space on "+_Quantity + " id = " + _refCharacter.id);
	return false;
}

int RemoveCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	int i,cn,curQuantity;
	string goodsName = Goods[_Goods].name;

	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
            if (CheckAttribute(&Characters[cn], "Ship.Cargo.Goods."+goodsName)) // boal fix 230804
            {
                curQuantity = sti( Characters[cn].Ship.Cargo.Goods.(goodsName) );
    			if(curQuantity>=_Quantity)
    			{
    				Characters[cn].Ship.Cargo.Goods.(goodsName) = curQuantity - _Quantity;
    				RecalculateCargoLoad(&Characters[cn]);
    				return true;
    			}
    			Characters[cn].Ship.Cargo.Goods.(goodsName) = 0;
    			_Quantity = _Quantity - curQuantity;
    			RecalculateCargoLoad(&Characters[cn]);
			}
			else
			{
                if (MOD_BETTATESTMODE == "On") Log_TestInfo("Проверка (не критично): RemoveCharacterGoods нет груза для characterID = "+ Characters[cn].id);
			}
		}
	}
	Trace("Overup cargo space on "+_Quantity);
	return false;
}
// Cannons utilite
int GetCaracterShipCannonsType(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Cannons.Type")) return CANNON_TYPE_NONECANNON;
	return sti(_refCharacter.Ship.Cannons.Type);
}
int GetCannonQuantity(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref rShip = GetRealShip(nShipType);
	return sti(rShip.CannonsQuantity);
}

int GetIntactCannonQuantity(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref refBaseShip = GetRealShip(nShipType);

	int canQ = GetBortIntactCannonsNum(refCharacter, "fcannon", sti(refBaseShip.fcannon)) + GetBortIntactCannonsNum(refCharacter, "bcannon", sti(refBaseShip.bcannon)) + GetBortIntactCannonsNum(refCharacter, "lcannon", sti(refBaseShip.lcannon)) + GetBortIntactCannonsNum(refCharacter, "rcannon", sti(refBaseShip.rcannon));
	return canQ;
}

int GetMaximumCaliber(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref rShip = GetRealShip(nShipType);
	return sti(rShip.MaxCaliber);
}

// Ship utilite
int GetCharacterShipType(ref _refCharacter)
{
	if(CheckAttribute(_refCharacter,"Ship.Type"))
	{
		int iShipType = sti(_refCharacter.Ship.Type);
		if(iShipType != SHIP_NOTUSED)
		{
            return iShipType;
		}
	}
	return SHIP_NOTUSED;
}
int GetCharacterShipHP(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	return sti(RealShips[nShipType].HP);
}
int GetCurrentShipHP(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"ship.hp") ) return sti(_refCharacter.ship.hp);
	return 0;
}
float GetCharacterShipSP(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0.0;
	return stf(RealShips[nShipType].SP);
}
string GetShipTypeName(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED)
	{
		return SHIP_NOTUSED_TYPE_NAME;
	}

	return ShipsTypes[sti(RealShips[nShipType].basetype)].name;
}
int GetCharacterShipClass(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return 7; // -1 неправильно, иначе сравнение врет, нет кораля - это лодка
	return sti(RealShips[nShipType].Class);
}
int GetMaxCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
    if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].MaxCrew);
}
//boal optimal crew
int GetOptCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
	if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].OptCrew);
}

int GetMinCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
	if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].MinCrew);
}
int GetFreeCrewQuantity(ref _refCharacter)
{
	return (GetMaxCrewQuantity(_refCharacter)-GetCrewQuantity(_refCharacter));
}
int GetFreePartyCrewQuantity(ref _refCharacter)
{
	int cn;
	int sumCrew = 0;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{
			sumCrew = sumCrew + GetFreeCrewQuantity(GetCharacter(cn));
		}
	}
	return sumCrew;
}
int GetCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Crew.Quantity")) return 0;
	if (sti(_refCharacter.Ship.Crew.Quantity) < 0) _refCharacter.Ship.Crew.Quantity = 0; // boal FIX 21.04.05

	return sti(_refCharacter.Ship.Crew.Quantity);
}
int SetCrewQuantity(ref _refCharacter,int num)
{
	int maxCrew = GetMaxCrewQuantity(_refCharacter);
	if(num>maxCrew)
	{
		Trace("Error!!! Overup maximum crew quantity (character=" + _refCharacter.index + ")");
		_refCharacter.Ship.Crew.Quantity = maxCrew;
		return false;
	}
	if (num < 0) num = 0; // boal fix
	_refCharacter.Ship.Crew.Quantity = num;
	return true;
}

// --> Eddy, пусть будет пока, а то неудобно в тестах.
void SetCrewQuantityFull(ref _refCharacter)
{
	SetCrewQuantity(_refCharacter, GetMaxCrewQuantity(_refCharacter)); // переделал в мах перегруз 01/08/06 boal
}
// <-- Eddy

// boal
int SetCrewQuantityOverMax(ref _refCharacter, int num)
{
    /*if (num < 0) num = 0; // boal fix
    _refCharacter.Ship.Crew.Quantity = num;*/ //отключил овербафф команды
	SetCrewQuantityFull(_refCharacter);
	return true;
}
int AddCharacterCrew(ref _refCharacter,int num)
{
	return SetCrewQuantity(_refCharacter,GetCrewQuantity(_refCharacter)+num);
}
int RemoveCharacterCrew(ref _refCharacter,int num)
{
	int curCrew = GetCrewQuantity(_refCharacter);
	if(curCrew<num)
	{
		//Trace("Error!!! Remove overup crew (character=" + _refCharacter.index + ")");
		SetCrewQuantity(_refCharacter,0);
		return false;
	}
	SetCrewQuantityOverMax(_refCharacter,curCrew-num);//fix
	return true;
}
float GetSailPercent(ref _refCharacter)
{
	if( !CheckAttribute(_refCharacter,"Ship.SP") ) return 100.0;
	float fSP = GetCharacterShipSP(_refCharacter);
	if(fSP<=0.0) return 100.0;
	float fpsp = 100.0*stf(_refCharacter.Ship.SP)/fSP;
	return fpsp;
}
float GetHullPercent(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.HP")) return 100.0;
	int iHP = GetCharacterShipHP(_refCharacter);
	if(iHP<=0) return 100.0;
	float fphp = 100.0*stf(_refCharacter.Ship.HP)/iHP;
	return fphp;
}

float GetHullPercentWithModifier(ref _refCharacter, int iModifier)
{
	if(!CheckAttribute(_refCharacter,"Ship.HP")) return 100.0;
	int iHP = GetCharacterShipHP(_refCharacter);
	if(iHP<=0) return 100.0;
	float fphp = 100.0*(stf(_refCharacter.Ship.HP) + iModifier)/iHP;
	return fphp;
}

float GetSailRPD(ref _refCharacter) // процент ремонта парусов в день
{
	float repairSkill = GetSummonSkillFromNameToOld(_refCharacter, SKILL_REPAIR);
	if(CheckOfficersPerk(_refCharacter, "Carpenter"))
	{
		repairSkill = repairSkill * 1.1;
	}
	if(IsEquipCharacterByArtefact(_refCharacter, "talisman7")) repairSkill = repairSkill * 1.5;
	float damagePercent = 100.0 - GetSailPercent(_refCharacter);
	if (damagePercent == 0.0) return 0.0;

	float ret = repairSkill*25.0 / (damagePercent+15) + 2;
	if (ret > damagePercent) ret = damagePercent;
	return ret;  //boal
}
float GetHullRPD(ref _refCharacter) // процент ремонта корпуса в день
{
	float repairSkill = GetSummonSkillFromNameToOld(_refCharacter, SKILL_REPAIR);
	if(CheckOfficersPerk(_refCharacter, "Carpenter"))
	{
		repairSkill = repairSkill * 1.1;
	}
	if(IsEquipCharacterByArtefact(_refCharacter, "talisman7")) repairSkill = repairSkill * 1.5;
	float damagePercent = 100.0 - GetHullPercent(_refCharacter);
	//if (damagePercent < 10.0) return 0.0;

	float ret = (repairSkill+2)/36 * damagePercent;
	if (ret > damagePercent) ret = damagePercent;
	return ret;  //boal
}
float GetSailSPP(ref _refCharacter) // количество парусины на один процент починки
{
	float ret = 8-GetCharacterShipClass(_refCharacter);

	if (CheckOfficersPerk(_refCharacter, "Builder"))
	{
		ret = ret * 0.9; // потребность ниже
	}

	return ret;
}
float GetHullPPP(ref _refCharacter) // количество досок на один процент починки
{
	float ret = 8-GetCharacterShipClass(_refCharacter);

	float HPpercent = GetCharacterShipHP(_refCharacter) / 700.0;

	if (HPpercent > ret) ret = HPpercent;

	if (CheckOfficersPerk(_refCharacter, "Builder"))
	{
		ret = ret * 0.9; // потребность ниже
	}

	return ret;
}
// расчет починки корпуса
float GetHullRepairDay(ref _refCharacter, bool _qty) // процент ремонта корпуса в день с материалом
{
    float repPercent = 0.0;
    float matQ, tmpf;

    matQ = 0;
	if (GetHullPercent(_refCharacter)<100.0 )
	{
		repPercent = GetHullRPD(_refCharacter);
		matQ = repPercent*GetHullPPP(_refCharacter);
		tmpf = GetRepairGoods(true,_refCharacter);
		if (tmpf >= 0)
		{
			if (tmpf < matQ)
			{
                matQ = tmpf;
				repPercent = tmpf/GetHullPPP(_refCharacter);
			}
        }
	}
	if (_qty)
	{
	    return matQ;
	}
	return repPercent;
}

float GetSailRepairDay(ref _refCharacter, bool _qty) // расчет починки парусов
{
    float repPercent = 0.0;
    float matQ, tmpf;

    matQ = 0;

	if (GetSailPercent(_refCharacter)<100.0 )
	{
		repPercent = GetSailRPD(_refCharacter);
		matQ = repPercent*GetSailSPP(_refCharacter);
		tmpf = GetRepairGoods(false,_refCharacter);
		if (tmpf >= 0)
		{
			if (tmpf < matQ)
			{
                matQ = tmpf;
				repPercent = tmpf/GetSailSPP(_refCharacter);
			}
        }
	}
	if (_qty)
	{
	    return matQ;
	}
	return repPercent;
}
// Fellowtravels utilites
// работа с пассажирами
int GetPassengersQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	return sti(_refCharacter.Fellows.Passengers.Quantity);
}

// пассажиры без пленных и квестовых boal
int GetOfficerPassengerQuantity(ref _refCharacter)
{
	int psgQuant = GetPassengersQuantity(_refCharacter);
	int curIdx=0;
	ref curChar;
	int cn;
	int how = 0;
	bool ok;

	for (int i=0; i<psgQuant; i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		ok = CheckAttribute(curChar, "prisoned") && curChar.prisoned == true;
		if (!ok && GetRemovable(curChar))
		{
   			how++;
		}
	}

	return how;
}

int GetNotCaptivePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		if(sti(characters[idx].prisoned) != 1)
		{
			result = result+1;
			//idx = GetNotCaptivePassenger( _refCharacter,i);
			//if (idx >0) result = result+1;
		}
	}
	return result;
}

int GetFreePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		if(!CheckAttribute(&characters[idx], "isfree"))
		{
			result = result+1;
		}
		//idx = GetFreePassenger( _refCharacter,i);
		//if (idx >0) result = result+1;
	}
	return result;
}

int GetNotQuestPassengersQuantity(ref _refCharacter)
{
	int result, idx;
	bool bOk;

	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);

		bOk =  CheckAttribute(&characters[idx], "prisoned") && sti(characters[idx].prisoned) == true;
		if (!bOk && !CheckAttribute(&characters[idx], "isquest") && !CheckAttribute(&characters[idx],"nonremovable"))
		{
			result = result+1;
		}
		/*idx = GetNotCaptivePassenger( _refCharacter,i);
		if (idx >0)
		{
			idx = GetNotQuestPassenger( _refCharacter,i);
		}
		if (idx >0) result = result+1;
		*/
	}
	return result;
}

int GetNotQuestFreePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	bool ok;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		if (idx >0)
		{
			ok = !CheckAttribute(&characters[idx], "prisoned") || sti(characters[idx].prisoned) != true;
			if (ok && !CheckAttribute(&characters[idx], "isquest") && !CheckAttribute(&characters[idx], "isfree"))   //to_do  isquest?
			{
				result = result+1;
			}
		}
	}
	return result;
}

int GetPassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	if(idx>=GetPassengersQuantity(_refCharacter)) return -1;

	string PsgAttrName = "id"+(idx+1);
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers."+PsgAttrName)) return -1;
	return sti(_refCharacter.Fellows.Passengers.(PsgAttrName));
}

int GetPassengerEx(ref _refCharacter,int idx)
{
	if(idx < 0)
	{
		return -1;
	}
	if(idx > GetPassengersQuantity(_refCharacter))
	{
		return -1;
	}
	if(idx == 0)
	{
		return nMainCharacterIndex;
	}
	string PsgAttrName = "id" + (idx);
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers."+PsgAttrName))
	{
		return -1;
	}
	return sti(_refCharacter.Fellows.Passengers.(PsgAttrName));
}

int GetPassengerNumber(ref _refCharacter,int findCharacterIdx)
{
	int psgQuant = GetPassengersQuantity(_refCharacter);
	int cn;
	ref cr;
	for(int i=0; i<psgQuant; i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;
		cr = GetCharacter(cn);
		if(findCharacterIdx==sti(cr.index)) return i;
	}
	return -1;
}
int GetNotCaptivePassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"prisoned"))
		{
			if(sti(curChar.prisoned)==true) continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int GetFreePassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"isfree"))
		{
			continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int GetNotQuestPassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"isquest") || CheckAttribute(curChar,"isfree"))
		{
			continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int ChangePassenger(ref _refCharacter,int idx, int psngIdx)
{
	int retVal = GetPassenger(_refCharacter,idx);
	if(idx>=0)
	{
		string PsgAttrName = "id"+(idx+1);
		_refCharacter.Fellows.Passengers.(PsgAttrName) = psngIdx;
	}
	return retVal;
}
int AddPassenger(ref _refCharacter,ref _refPassenger, int prisonFlag)
{
	ref characterRef;
	int PsgQuantity = GetPassengersQuantity(_refCharacter);
	if(PsgQuantity<PASSENGERS_MAX)
	{
		aref tmpRef; makearef(tmpRef,_refCharacter.Fellows.Passengers);
		string PsgAttrName;
		for(int i=0;i<PsgQuantity;i++)
		{
			PsgAttrName = "id"+(i+1);
			characterRef = GetCharacter(sti(tmpRef.(PsgAttrName)));
			if(tmpRef.(PsgAttrName) == _refPassenger.index && sti(characterRef.id) == 0) return PsgQuantity;
			//if(tmpRef.(PsgAttrName) == _refPassenger.index ) return PsgQuantity;
		}
		PsgQuantity++;
		tmpRef.Quantity = PsgQuantity;
		PsgAttrName = "id"+PsgQuantity;
		tmpRef.(PsgAttrName) = _refPassenger.index;
		if(prisonFlag==true)	_refPassenger.prisoned = true;
	}
	else	trace("Overup maximum passengers quantity");
	return PsgQuantity;
}
int RemovePassenger(ref _refCharacter,ref _refPassenger)
{
 	if (sti(_refCharacter.index) == GetMainCharacterIndex())
	{
		CheckForReleaseOfficer(sti(_refPassenger.index));  // boal super fix
	}
	else
	{
	    RemoveOfficersIndex(_refCharacter,sti(_refPassenger.index));
	}
	int PsgQuantity = GetPassengersQuantity(_refCharacter);
	int psgNum = GetPassengerNumber(_refCharacter,sti(_refPassenger.index));
	if(psgNum==-1) return PsgQuantity;

	aref tmpRef;
	makearef(tmpRef,_refCharacter.Fellows.Passengers);
	string inPsgAttrName,outPsgAttrName;
	for(int i=(psgNum+1); i<PsgQuantity; i++)
	{
		inPsgAttrName = "id"+i;
		outPsgAttrName = "id"+(i+1);
		tmpRef.(inPsgAttrName) = tmpRef.(outPsgAttrName);
	}

	outPsgAttrName = "id"+PsgQuantity;
	DeleteAttribute(tmpRef,outPsgAttrName);
	PsgQuantity--;
	tmpRef.Quantity = PsgQuantity;
	return PsgQuantity;
}

int FindFellowtravellers(ref _refCharacter,ref _refFindCharacter)
{
	int i;
	string stmp;
	aref atmp;
	aref curref;

	if(sti(_refFindCharacter.index)==-1) return FELLOWTRAVEL_NO;
	if(CheckAttribute(_refFindCharacter,"prisoned"))
	{
		if(sti(_refFindCharacter.prisoned)==true) return FELLOWTRAVEL_CAPTIVE;
	}
	for(i=1;i<=MAX_NUM_FIGHTERS;i++)
	{
		if( sti(_refFindCharacter.index) == GetOfficersIndex(_refCharacter,i) )	return FELLOWTRAVEL_OFFICER;
	}
	for(i=0;i<GetPassengersQuantity(_refCharacter);i++)
	{
		if(sti(_refFindCharacter.index)==GetPassenger(_refCharacter,i))	return FELLOWTRAVEL_PASSENGER;
	}
	for(i=1;i<COMPANION_MAX;i++)
	{
		if( GetCompanionIndex(_refCharacter,i)==sti(_refFindCharacter.index) )
		{
			return FELLOWTRAVEL_COMPANION;
		}
	}
	return FELLOWTRAVEL_NO;
}

// ==> eddy
bool CheckPassengerInCharacter(ref _refBaseChar, string _seekId)
{
	int psgQuant = GetPassengersQuantity(_refBaseChar);
    if(psgQuant<0) return false;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refBaseChar,i);
		if(cn==-1) continue;
		if (characters[cn].id == _seekId) return true;
	}
	return false;
}

// работа с компаньонами
int SetCompanionIndex(ref _refCharacter,int _CompanionNum, int _CompanionIdx)
{
  if(_CompanionNum == -1)
	{
		for(int i = 1; i < COMPANION_MAX; i++)
		{
			if (GetCompanionIndex(_refCharacter, i) == -1)
			{
				_CompanionNum = i;
				break;
			}
		}
	}
	if(_CompanionNum < 1) return _CompanionIdx;
	if(_CompanionNum > COMPANION_MAX - 1) return _CompanionIdx;

	if(_CompanionIdx!=-1)
	{
		for(i=0;i<COMPANION_MAX;i++)
		{
			if(GetCompanionIndex(_refCharacter,i)==_CompanionIdx) return -1;
		}
	}

	string compName = "id"+_CompanionNum;
	int retVal = GetCompanionIndex(_refCharacter,_CompanionNum);
	_refCharacter.Fellows.Companions.(compName) = _CompanionIdx;

	//Character_SetCompanionEnemyEnable(&characters[_CompanionIdx], true);

	if( _CompanionIdx>=0 && CheckAttribute(&Characters[_CompanionIdx],"nation") ) {
		Characters[_CompanionIdx].prev_nation = Characters[_CompanionIdx].nation;
		Characters[_CompanionIdx].nation = _refCharacter.nation;
		Characters[_CompanionIdx].location = "none";//fix
	}
	if( retVal>=0 && CheckAttribute(&Characters[retVal],"prev_nation") ) {
		Characters[retVal].nation = Characters[retVal].prev_nation;
		Characters[retVal].location = "none"; //fix
	}

	// to_do CheckCompanionSkillsUp(_CompanionIdx);
	Event(EVENT_CHANGE_COMPANIONS,"");
	return _CompanionIdx;
}
int RemoveCharacterCompanion(ref _refCharacter, ref refCompanion)
{
	string compName;
	int i;

	aref refComps;
	makearef(refComps,_refCharacter.Fellows.Companions);
	for(i=1; i<COMPANION_MAX; i++)  // был баг к3
	{
		compName = "id"+i;
		if(CheckAttribute(refComps,compName) && refComps.(compName)==refCompanion.index)
		{
			refComps.(compName) = -1;
			refCompanion.location = "none";
			refCompanion.location.group = _refCharacter.location.group;
			refCompanion.location.locator = _refCharacter.location.locator;
			Event(EVENT_CHANGE_COMPANIONS,"");

			return i;
		}
	}
	return -1;
}
int GetCompanionIndex(ref _refCharacter,int _CompanionNum)
{
	if(_CompanionNum < 0)
	{
		return -1;
	}
	if(_CompanionNum > (COMPANION_MAX - 1))
	{
		return -1;
	}
	if(_CompanionNum==0)
	{
		if (!CheckAttribute(_refCharacter,"index"))
		{
			//Log_Info("Error GetCompanionIndex");
			return -1;
		}
		return sti(_refCharacter.index);
	}

	string compName = "id"+_CompanionNum;
	if(!CheckAttribute(_refCharacter, "Fellows.Companions."+compName))
	{
		return -1;
	}
	if(sti(_refCharacter.Fellows.Companions.(compName)) < 1)
	{
		return -1;
	}
	if(sti(characters[sti(_refCharacter.Fellows.Companions.(compName))].ship.type) != SHIP_NOTUSED)
	{
		return sti(_refCharacter.Fellows.Companions.(compName));
	}
	return -1;
}
int GetCompanionNumber(ref _refCharacter,int _CompanionIdx)
{
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if( GetCompanionIndex(_refCharacter,i) == _CompanionIdx ) return i;
	}
	return -1;
}
int GetCompanionQuantity(ref _refCharacter)
{
	int qn = 0;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if( GetCompanionIndex(_refCharacter,i)>=0 ) qn++;
	}
	if(qn >= COMPANION_MAX) UnlockAchievement("ships", 3);
	return qn;
}
// нигде не юзается
int GetRemovableCompanionsNumber(ref _refCharacter)
{
	int qn = 0;
	int cn = 1;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn > 0 && GetShipRemovable(&characters[cn]) == true)
		{
			qn++;
		}
	}
	return qn;
}

// ==> eddy
bool CheckCompanionInCharacter(ref _refBaseChar, string _seekId)
{
	int cn;
	for(int i=0;i<COMPANION_MAX;i++)
	{
		cn = GetCompanionIndex(_refBaseChar,i);
		if(cn==-1) continue;
		if (characters[cn].id == _seekId) return true;
	}
	return false;
}

// работа с офицерами
int GetOfficersQuantity(ref _refCharacter)
{
	int idx=0;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		if( GetOfficersIndex(_refCharacter,i)!=-1 ) idx++;
	}
	return idx;
}
int GetOfficersIndex(ref _refCharacter,int _OfficerNum)
{
	if(_OfficerNum<0) return -1;
	if(_OfficerNum>MAX_NUM_FIGHTERS) return -1;
	if(_OfficerNum==0)
    {
        if(!CheckAttribute(_refCharacter,"index")) return -1; // boal fix
        return MakeInt(_refCharacter.index);
    }

	string compName = "id"+_OfficerNum;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Officers."+compName)) return -1;
	if(sti(_refCharacter.Fellows.Passengers.Officers.(compName)) < 1)
	{
		return - 1;
	}
	return sti(_refCharacter.Fellows.Passengers.Officers.(compName));
}

int SetOfficersIndex(ref _refCharacter,int _OfficerNum, int _OfficerIdx)
{
	int i;
    if(_OfficerNum == -1)
	{
		for(i=1; i<=MAX_NUM_FIGHTERS; i++)
		{
			if(GetOfficersIndex(_refCharacter, i) == -1)
			{
				_OfficerNum = i;
				break;
			}
		}
        // fix
        if (_OfficerNum == -1)
        {
            _OfficerNum = MAX_NUM_FIGHTERS; // нет места?? да пофиг
        }
	}
	if(_OfficerNum<1) return _OfficerIdx;
	if(_OfficerNum>MAX_NUM_FIGHTERS) return _OfficerIdx;

	if(_OfficerIdx!=-1)
	{
		for(i=1;i<=MAX_NUM_FIGHTERS;i++)
		{
			if(GetOfficersIndex(_refCharacter,i)==_OfficerIdx) return -1;
		}
		AddPassenger(_refCharacter,GetCharacter(_OfficerIdx),false);
	}

	string compName = "id"+_OfficerNum;
	int retVal = GetOfficersIndex(_refCharacter,_OfficerNum);
	_refCharacter.Fellows.Passengers.Officers.(compName) = _OfficerIdx;
	if(_OfficerIdx>=0)
	{
		LAi_SetOfficerType(GetCharacter(_OfficerIdx));
		Characters[_OfficerIdx].location = _refCharacter.location;
	}
	if(retVal>=0)
	{
		LAi_SetCitizenTypeNoGroup(GetCharacter(retVal));
		Characters[retVal].location = "none";
	}
	Event(EVENT_CHANGE_OFFICERS,"");

	return retVal;
}
bool RemoveOfficersIndex(ref _refCharacter, int _OfficerIdx)
{
	if(_OfficerIdx==-1) return false;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		if(GetOfficersIndex(_refCharacter,i) == _OfficerIdx)
		{
			SetOfficersIndex(_refCharacter,i,-1);
			return true;
		}
	}
	return false;
}

int AddMoneyToCharacter(ref _refCharacter,int _Money)
{
	// boal -->
	if (_Money < 0 && sti(_refCharacter.Money) < abs(_Money))
	{
	    _Money = -sti(_refCharacter.Money);
	}
	// boal <--
	int newMoney = sti(_refCharacter.Money) + _Money;
	if(newMoney<0) newMoney=0;
	_refCharacter.Money = newMoney;

    //boal -->
	if (sti(_refCharacter.index) == GetMainCharacterIndex()) // флаг лога
	{
		if (_Money > 0)
		{
			Log_Info("Добавлено " + _Money + " золотых");
			Statistic_AddValue(Pchar, "Money_get", _Money);
		}
		else
		{
		    if (_Money < 0)
			{
				Log_Info("Потрачено " + abs(_Money) + " золотых");
				Statistic_AddValue(Pchar, "Money_spend", abs(_Money));
			}
		}
		// Открываем достижение
		if(sti(_refCharacter.Money) >= 1000000) UnlockAchievement("money", 1);
		if(sti(_refCharacter.Money) >= 5000000)	UnlockAchievement("money", 2);
		if(sti(_refCharacter.Money) >= 15000000) UnlockAchievement("money", 3);
	}
	// boal <--
	return newMoney;
}

void AddAchievementPoints(int points) // Даем очки достижений
{
	pchar.ach_points = sti(pchar.ach_points)+points;
	Log_Info("Всего очков достижений у вас: " + pchar.ach_points);
}

void UnlockAchievement(string ach_name, int level) // Открываем достижениие
{
	int points;

	if(sti(pchar.achievements.(ach_name)) == level) return; // Не даем дважды открыть один и тот же уровень достижения

	if(sti(pchar.achievements.(ach_name)) == 3)
	{
		if((level == 2) || (level == 1)) return;
	}

	if(sti(pchar.achievements.(ach_name)) == 2)
	{
		if(level == 1) return;
	}


	string achievement = GetAchievementName(ach_name, level);

	if(level == 1) points = 25;
	if(level == 2) points = 50;
	if(level == 3) points = 100;

	Log_Info("Открыто достижение '" + achievement + "' (+" + points + " очков)");
    PlaySound("interface\AchievementComplite.wav");

	pchar.achievements.(ach_name) = level;
	AddAchievementPoints(points);
}
void SetBaseShipData(ref refCharacter)
{
    int  i;
    aref refShip;
    int  nShipType;
    ref  refBaseShip;

	if (CheckAttribute(refCharacter,"Ship"))
	{
		if(!CheckAttribute(refCharacter, "ship.upgrades"))
		{
			refCharacter.ship.upgrades.hull = 1;
			refCharacter.ship.upgrades.sails = 1;
			refCharacter.ship.upgrades.cannons = 1;
		}
		makearef(refShip,refCharacter.Ship);
		nShipType = GetCharacterShipType(refCharacter);
		if(nShipType==SHIP_NOTUSED) return;

		//trace (refCharacter.id);
		refBaseShip = GetRealShip(nShipType);

		if(!CheckAttribute(refBaseShip, "HP"))
		{
			trace ("ship have not HP.");
			return;
		}

		refShip.HP = refBaseShip.HP;
		refShip.SP = refBaseShip.SP;

		if (!CheckAttribute(refShip,"soiling"))
		{
			refShip.soiling = 0;
		}

		refShip.Pos.x = 0;
		refShip.Pos.y = 0;
		refShip.Pos.z = 0;
		refShip.Ang = "";
		/* refShip.Cannons.Borts = "";
		if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages"); } */

		refShip.Cannons.Charge.Type = GOOD_BALLS;

		if (!CheckAttribute(refShip,"Cannons.Type"))
		{
			refShip.Cannons.Type = GetCannonByTypeAndCaliber("cannon", sti(refBaseShip.MaxCaliber)); // MakeInt(refBaseShip.Cannon);
		}

		if (!CheckAttribute(refShip,"Crew.Morale"))
		{
			refShip.Crew.Morale = 20 + rand(79);
		}
		if (!CheckAttribute(refShip,"Crew.Quantity"))
		{
			refShip.Crew.Quantity = refBaseShip.OptCrew; // оптимальная команда
		}

		SetGoodsInitNull(refCharacter); // boal пееренс в метод
		// новый опыт
        if(!CheckAttribute(refCharacter, "ship.crew.Exp"))
		{
			refCharacter.Ship.Crew.Exp.Sailors   = 1 + rand(80);
			refCharacter.Ship.Crew.Exp.Cannoners = 1 + rand(80);
			refCharacter.Ship.Crew.Exp.Soldiers  = 1 + rand(80);
		}
		int iGoodN = 0;
		int iGoodR = 0;

		// boal -->
		i = GetCharacterFreeSpace(refCharacter,GOOD_POWDER) / 40;
        if(i>0)
        {
			if(i>=500)
            {
				SetCharacterGoods(refCharacter,GOOD_POWDER, 500 - rand(50));
			} else
            {
				SetCharacterGoods(refCharacter,GOOD_POWDER,i);
			}
		}
		// boal <--
		// bombs
		i = GetCharacterFreeSpace(refCharacter,GOOD_BOMBS) / 42;
		if(i>0)
		{
			if(i > 600)
			{
				i = 600;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_BOMBS,iGoodN);
		}

		// grapes
		i = GetCharacterFreeSpace(refCharacter,GOOD_GRAPES) / 60;
		if(i>0)
		{
			if(i > 200)
			{
				i = 200;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_GRAPES,iGoodN);
		}

		// knippels
		i = GetCharacterFreeSpace(refCharacter,GOOD_KNIPPELS) / 60;
		if(i>0)
		{
			if(i > 200)
			{
				i = 200;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_KNIPPELS,iGoodN);
		}

		// cannonballs
		i = GetCharacterFreeSpace(refCharacter,GOOD_BALLS) / 42;
		if(i>0)
		{
			if(i > 800)
			{
				i = 800;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_BALLS,iGoodN);
		}

		//food
		i = GetCharacterFreeSpace(refCharacter,GOOD_FOOD) / 20;
		if(i>0)
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_FOOD,iGoodN);
		}
		//GOOD_WEAPON
		i = GetCharacterFreeSpace(refCharacter,GOOD_WEAPON) / 60;
		if(i>0)
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_WEAPON,iGoodN);
		}
		//
		i = GetCharacterFreeSpace(refCharacter,GOOD_MEDICAMENT) / 100;
		if(i>0)
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_MEDICAMENT,iGoodN);
		}
	}
	refCharacter.ship.crew.disease = 0;
	SetTuningShipStates(refCharacter);
	//Mett: nation sails —->
	if(sti(refCharacter.nation) == PIRATE)
	{
		refBaseShip.ship.upgrades.sails = 38 + rand(50); // LEO: пиратские паруса
	}
		else refBaseShip.ship.upgrades.sails = 1 + rand(22); // LEO: все остальные
	// <-—

	//Debug —->
	Dev_Trace("******************************************************************");
	Dev_Trace("SetBaseShipData: Debug:");
	Dev_Trace("chr id " + refCharacter.id + " chr index " + sti(refCharacter.index));
	Dev_Trace("chr nation " + GetNationNameByType(sti(refCharacter.nation)));
	Dev_Trace("chr ship type " + GetShipTypeName(refCharacter));
	Dev_Trace("chr sails num " + sti(refBaseShip.ship.upgrades.sails));
	Dev_Trace("******************************************************************");
	// <---
}
void SetGoodsInitNull(ref refCharacter)
{
	NullCharacterGoods(refCharacter);
}

// Warship. Нулим все товары у персонажа. Так уж получилось, что два одинаковых метода
void NullCharacterGoods(ref rChar)
{
	string sGood;
	if(!CheckAttribute(rChar, "Ship")) return;

	rChar.Ship.Cargo.Load = 0;

	for(i=0; i<GOODS_QUANTITY; i++)
	{
		sGood = Goods[i].Name;
		rChar.Ship.Cargo.Goods.(sGood) = 0;
	}
}
// метод рудимент от к1 видимо :)
void SetBaseFellows(object refCharacter)
{
	int i;
	string sAttName;
	aref tmpRef;

	makearef(tmpRef,refCharacter.Fellows.Companions);
	//Boyer mod
	/* tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1; */
	for(i=1;i<=COMPANION_MAX;i++) {
		sAttName = "id" + i;
		tmpRef.(sAttName) = -1;
	}

	makearef(tmpRef,refCharacter.Fellows.Passengers);
	tmpRef.Quantity = 0;
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;
	tmpRef.id4 = -1;
	tmpRef.id5 = -1;
	tmpRef.id6 = -1;
	tmpRef.id7 = -1;
	tmpRef.id8 = -1;

	makearef(tmpRef,refCharacter.Fellows.Passengers.Officers);
	//Boyer mod
	/* tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1; */
	for(i=1;i<=MAX_NUM_FIGHTERS;i++) {
		sAttName = "id" + i;
		tmpRef.(sAttName) = -1;
	}
}

// Выполняем достижение
// ===>

void PerformAchievement(string AchID, string AchStep, string LogAch)
{
	if(pchar.questTemp.Achievements.(AchID).(AchStep) != "true")
	{
		pchar.questTemp.Achievements.(AchID).(AchStep) = "true"; // Запоминаем, что достижение выполнено
		Log_Info("Выполнено достижение: ''" +LogAch+"''"); // Выводим в лог

		pchar.questTemp.Achievements.Points = sti(pchar.questTemp.Achievements.Points) + (sti(AchStep)*15); // Даем "очки достижений"
	}
}

// <===
// Items Utilite
int GetChrItemQuantity(ref _refCharacter)
{
	aref ar; makearef(ar,_refCharacter.items);
	return GetAttributesNum(ar);
}
bool GiveItem2Character(ref _refCharacter,string itemName)
{
	return TakeNItems(_refCharacter,itemName,1);
}
void TakeItemFromCharacter(ref _refCharacter,string itemName)
{
	TakeNItems(_refCharacter,itemName,-1);
}
// Warship. Просто сокращения -->
void AddItems(ref _Chr, string _ItemID, int _Num)
{
	TakeNItems(_Chr, _ItemID, _Num);
}

void RemoveItems(ref _Chr, string _ItemID, int _Num)
{
	TakeNItems(_Chr, _ItemID, -1*_Num);
}
// <-- Просто сокращения

// Warship 11.05.09 Для новой системы предметов
void GenerateAndAddItems(ref _chr, string _itemID, int _qty)
{
	int i;
	String curItemID;

	for(i = 1; i <= _qty; i++)
	{
		curItemID = GetGeneratedItem(_itemID);
		AddItems(_chr, curItemID, 1);
	}
}
bool CheckCharacterItem(ref _refCharacter,string itemName)
{
	ref tmpRef;
	if(!IsGenerableItem(itemName))
	{
		if( CheckAttribute(_refCharacter,"Items."+itemName) && sti(_refCharacter.Items.(itemName))>0 )	return true;
		else return false;
	}
	else
	{
		for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
		{
			tmpRef = &Items[i];
			if(CheckAttribute(tmpRef, "ID"))
			{
				if(tmpRef.DefItemID == itemName) return true;
			}
		}
		return false;
	}
}

int GetCharacterItem(ref _refCharacter,string itemName)
{
	if(CheckAttribute(_refCharacter,"Items."+itemName))
	{
		return sti(_refCharacter.Items.(itemName));
	}
	return 0;
}

int GetCharacterFreeItem(ref _refCharacter,string itemName)
{
	if(CheckAttribute(_refCharacter,"Items."+itemName))
	{
		int iItemQ = sti(_refCharacter.Items.(itemName));
		if(IsEquipCharacterByItem(_refCharacter, itemName) || IsEquipCharacterByMap(_refCharacter, itemName))
		{
			iItemQ = iItemQ - 1;
		}
		return iItemQ;
	}
	return 0;
}

bool ReplaceItem(ref _refTakingCharacter,ref _refGivingCharacter,string itemName)
{
	bool retVal = CheckCharacterItem(_refGivingCharacter,itemName);
	if( TakeNItems(_refTakingCharacter,itemName,1) )
		TakeNItems(_refGivingCharacter,itemName,-1);
	return retVal;
}
bool TakeNItems(ref _refCharacter, string itemName, int n)
{
	int q;
	aref arItm;

	if(Items_FindItem(itemName, &arItm) < 0)
	{
		trace("TakeNItems warning - can't find " + itemName + " item");
		return false;
	}


	if(CheckAttribute(arItm, "gold"))
	{
		if(CheckAttribute(_refCharacter,"Money"))
		{
			q = sti(_refCharacter.Money);
		}
		else
		{
			q = 0;
		}

		q += n * sti(arItm.gold);

		if(q < 0)
		{
			q = 0;
		}

		_refCharacter.Money = q;

		return true;
	}

	//блокируем получения тотемов вторично
	if(n > 0 && findsubstr(itemName, "Totem_" , 0) != -1 && GetCharacterItem(_refCharacter,itemName) > 0 && !CheckAttribute(arItm, "shown.used"))
	{
		return true;
	}

	if(n > 0 && findsubstr(itemName, "map_part" , 0) != -1 && GetCharacterItem(_refCharacter,itemName) > 0)
	{
		return true;
	}

	// Dolphin -> генератор игрока
	if(itemName == "Bag_with_money" && n>0) // ГГ может только брать
	{
		DoQuestFunctionDelay("LooserGenerator_DopProverka", 0.2);
	}
	//<-

	if(CheckAttribute(arItm, "price") && sti(arItm.price) == 0)
	{
		if(arItm.ID != "Gold") // Warship. Для нового интерфейса обмена - проверка на золото
		{
			if(CheckAttribute(_refCharacter, "index"))
			{
				if(sti(_refCharacter.index) == GetMainCharacterIndex() && IsEntity(_refCharacter))
				{
					if(n > 0)
					{
						Log_Info(XI_ConvertString("You take item"));
						AddMsgToCharacter(_refCharacter, MSGICON_GETITEM);
					}

					if(n < 0)
					{
						Log_Info(XI_ConvertString("You give item"));
					}

					PlayStereoSound("interface\important_item.wav");
				}
			}

			// Warship 08.05.09 - Не ясная мне логика. И и ИЛИ в одном выражении не поддерживаются скриптовым двигом
			// Перенес вверх
			/*if(n > 0 && IsOfficer(_refCharacter) || IsCompanion(_refCharacter))
			{
				AddMsgToCharacter(_refCharacter, MSGICON_GETITEM);
			}*/
		}
	}

	q = GetCharacterItem(_refCharacter, itemName);

	if(q + n <= 0)
	{
		DeleteAttribute(_refCharacter, "Items." + itemName);
	}
	else
	{
		if(q <= 0 && GetChrItemQuantity(_refCharacter) >= MAX_ITEM_TAKE)
		{
			return false;
		}

		_refCharacter.Items.(itemName) = q + n;
	}

	return true;
}

int GetCharacterCurrentIsland(ref _refCharacter)
{
	int curLocNum = FindLocation(_refCharacter.location);   // boal fix Characters[GetMainCharacterIndex()]    - ну-ну
	if(curLocNum<0) return -1;
	return GetIslandIdxByLocationIdx(curLocNum);
}

string GetCharacterCurrentIslandId(ref _refCharacter)
{
	int curLocNum = FindLocation(_refCharacter.location);
	if(curLocNum < 0) return "";
	int CurIdx = GetIslandIdxByLocationIdx(curLocNum);
	ref CurIsland = GetIslandByIndex(CurIdx);
	return CurIsland.id;
}
int GetIslandIdxByLocationIdx(int locIdx)
{
	aref rootar,ar;
	makearef(rootar,Locations[0].IslandsList);
	for(int i=0; i<GetAttributesNum(rootar); i++)
	{
		ar = GetAttributeN(rootar,i);
		if (locIdx >= sti(ar.begin) && locIdx < sti(ar.end) ) //fix boal 02.02.05
		{
			return FindIsland(GetAttributeName(ar));
		}
	}
	return -1;
}

int GetCurrentLocationNation()
{
	int curLocNum = FindLocation(Characters[GetMainCharacterIndex()].location);
	if(curLocNum<0) return -1;
	return GetLocationNation(&Locations[curLocNum]);
}

void SetRandomNameToCharacter(ref rCharacter)
{
	int iNation = sti(rCharacter.nation);
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }

	ref rNames, rLastNames;
    // fix -->
    rNames = &sEnManNames;
	if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
	rLastNames = &sEnFamilies;
	// fix <--
	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
		case FRANCE:
			rNames = &sFrManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sFrWomenNames;
			rLastNames = &sFrFamilies;
		break;
		case SPAIN:
			rNames = &sSpManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sSpWomenNames;
			rLastNames = &sSpFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sHoWomenNames;
			rLastNames = &sHoFamilies;
		break;
		case PIRATE:
			rNames = &sEnManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
	}

	int iMassiveOfNamesSize = GetArraySize(rNames);
    int nRand = rand(iMassiveOfNamesSize-1);
    if (nRand < 0)
        nRand = 0;
	rCharacter.name = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	iMassiveOfNamesSize = GetArraySize(rLastNames);
    nRand = rand(iMassiveOfNamesSize-1);
    if (nRand < 0)
        nRand = 0;
	rCharacter.lastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
}

string GenerateRandomName(int iNation, string sSex)
{
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }

	ref rNames, rLastNames;
	rNames = &sEnManNames;
    if (sSex != "man") rNames = &sEnWomenNames;
    rLastNames = &sEnFamilies;

	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManNames;
			if (sSex != "man") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
		case FRANCE:
			rNames = &sFrManNames;
			if (sSex != "man") rNames = &sFrWomenNames;
			rLastNames = &sFrFamilies;
		break;
		case SPAIN:
			rNames = &sSpManNames;
			if (sSex != "man") rNames = &sSpWomenNames;
			rLastNames = &sSpFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManNames;
			if (sSex != "man") rNames = &sHoWomenNames;
			rLastNames = &sHoFamilies;
		break;
		case PIRATE:
			rNames = &sEnManNames;
			if (sSex != "man") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
	}

	int iMassiveOfNamesSize = GetArraySize(rNames);
    int nRand = rand(iMassiveOfNamesSize-1);
    if (nRand < 0)
        nRand = 0;
	string sname = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	iMassiveOfNamesSize = GetArraySize(rLastNames);
    nRand = rand(iMassiveOfNamesSize-1);
    if (nRand < 0)
        nRand = 0;
	string slastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);

	sname = sname + " " + slastName;
	return sName;
}

void SetRandomNameToCharacter_Generator(ref rCharacter)
{
	int iNation = sti(rCharacter.nation);
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }

	ref rNames, rLastNames;
    // fix -->
    rNames = &sEnManGenNames;
	if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
	rLastNames = &sEnGenFamilies;
	// fix <--
	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
		case FRANCE:
			rNames = &sFrManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sFrWomenGenNames;
			rLastNames = &sFrGenFamilies;
		break;
		case SPAIN:
			rNames = &sSpManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sSpWomenGenNames;
			rLastNames = &sSpGenFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sHoWomenGenNames;
			rLastNames = &sHoGenFamilies;
		break;
		case PIRATE:
			rNames = &sEnManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
	}

	rCharacter.name = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	rCharacter.lastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
}

string GenerateRandomName_Generator(int iNation, string sSex)
{
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }

	ref rNames, rLastNames;

	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManGenNames;
			if (sSex != "man") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
		case FRANCE:
			rNames = &sFrManGenNames;
			if (sSex != "man") rNames = &sFrWomenGenNames;
			rLastNames = &sFrGenFamilies;
		break;
		case SPAIN:
			rNames = &sSpManGenNames;
			if (sSex != "man") rNames = &sSpWomenGenNames;
			rLastNames = &sSpGenFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManGenNames;
			if (sSex != "man") rNames = &sHoWomenGenNames;
			rLastNames = &sHoGenFamilies;
		break;
		case PIRATE:
			rNames = &sEnManGenNames;
			if (sSex != "man") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
	}

	string sname = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	string slastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);

	sname = sname + " " + slastName;
	return sName;
}

//=============================================================================
//  EQUIP SECTION
//=============================================================================
string FindCharacterItemByGroup(ref chref, string groupID)
{
 	int i,n;
	ref refItm;
    float  maxBladeValue, curBladeValue;
    string resultItemId;
   if (CheckAttribute(chref, "CanTakeMushket") && CheckAttribute(chref, "IsMushketer")) return ""; // мушкеты не выбираем
    // boal 17.06.05 офицерам даем кулаки -->
	if (groupID == BLADE_ITEM_TYPE && IsOfficer(chref) && IsEquipCharacterByItem(chref, "unarmed") && !CheckAttribute(chref, "isMusketer"))
	{
        RemoveCharacterEquip(chref, BLADE_ITEM_TYPE);
        TakeItemFromCharacter(chref, "unarmed");
	}
	// boal 17.06.05 офицерам даем кулаки <--
	maxBladeValue = 0;
	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(groupID==GUN_ITEM_TYPE)
		{
			if( !CheckAttribute(refItm,"chargeQ") ) continue;
			n = sti(refItm.chargeQ);
			if(n<2) {return refItm.id;}
			if(n<4)
			{
				if( IsCharacterPerkOn(chref,"Gunman") ) {return refItm.id;}
				else continue;
			}
            //boal -->
            if( IsCharacterPerkOn(chref,"GunProfessional") )	{return refItm.id;}
            // boal <--
			continue;
		}
		// boal 08.10.04 броню офицерам -->
		if (groupID == CIRASS_ITEM_TYPE)
		{
           if( IsCharacterPerkOn(chref, "Ciras") )	{return refItm.id;}
           continue;
		}
		// boal 08.10.04 броню офицерам <--

		// Lugger -->
		if (groupID == BACKPACK_ITEM_TYPE)
		{
			if(!CheckAttribute(refItm, "BackPackWeight"))
			{
				continue;
			}

			if(sti(refItm.BackPackWeight) >= 75)
			{
				return refItm.id;
			}
			else
			{
				if(sti(refItm.BackPackWeight) >= 50)
				{
					return refItm.id;
				}
				else
				{
					if(sti(refItm.BackPackWeight) >= 36)
					{
						return refItm.id;
					}
					else
					{
						if(sti(refItm.BackPackWeight) >= 20)
						{
							return refItm.id;
						}
						else
						{
							if(sti(refItm.BackPackWeight) >= 10)
							{
								return refItm.id;
							}
							else
							{
								continue;
							}
						}
					}
				}
			}

           		continue;
		}
		// Lugger <--

		// перебор на лучшую саблю
		if (groupID == BLADE_ITEM_TYPE)
		{
			// формула лучшего выбора
			curBladeValue = (stf(refItm.dmg_min)*3 + (stf(refItm.dmg_max)*GetCharacterSkill(chref, refItm.FencingType)) / SKILL_MAX) / GetEnergyBladeDrain(stf(refItm.Weight));// + stf(refItm.piercing) + stf(refItm.block);
			if (curBladeValue > maxBladeValue)
			{
			    maxBladeValue = curBladeValue;
			    resultItemId  = refItm.id;
			}
		}
		else
		{
		    return refItm.id;
		}
	}
	if (resultItemId != "")
	{
        return resultItemId;
	}
	// boal 17.06.05 офицерам даем кулаки -->
	if (groupID == BLADE_ITEM_TYPE && IsOfficer(chref) && sti(chref.index) != GetMainCharacterIndex() && !CheckAttribute(chref, "isMusketer"))
	{
        GiveItem2Character(chref, "unarmed");
        EquipCharacterByItem(chref, "unarmed");
	}
	// boal 17.06.05 офицерам даем кулаки <--
	return "";  //ничего не делать далее
}

bool IsEquipCharacterByItem(ref chref, string itemID)
{
	aref arEquip;
	makearef(arEquip,chref.equip);
	int q = GetAttributesNum(arEquip);
	for(int i=0; i<q; i++)
	{	if(GetAttributeValue(GetAttributeN(arEquip,i))==itemID) return true;
	}
	return false;
}

bool IsEquipCharactersByItem(ref chref, string itemID)
{
	int 	iOfficer = -1;
	ref 	rItem, sld;
	string  sKind = "";

	if (IsMainCharacter(chref)) // ГГ и его офицеры
	{
		if(IsEquipCharacterByItem(pchar, itemID)) return true;
		rItem = ItemsFromID(itemID);
		if(CheckAttribute(rItem, "kind"))
		{
			sKind = rItem.kind;
			if(sKind == "fighter")
			{
				for(int i = 1; i < MAX_NUM_FIGHTERS; i++)
				{
					iOfficer = GetOfficersIndex(pchar, i);
					if(iOfficer != -1)
					{
						if(IsEquipCharacterByItem(&characters[iOfficer], itemID)) return true;
					}
				}
			}
			else
			{
				iOfficer = sti(pchar.Fellows.Passengers.(sKind));
				if(iOfficer != -1)
				{
					return IsEquipCharacterByItem(&characters[iOfficer], itemID);
				}
			}
			return false;
		}
		else
		{
			for (int io = 0; io < GetNotQuestPassengersQuantity(chref); io++)
			{
				iOfficer = GetNotQuestPassenger(chref, io);
				if(iOfficer != -1)
				{
					sld = GetCharacter(iOfficer);
					if(isOfficerInShip(sld, true))
					{
						if(IsEquipCharacterByItem(sld, itemID)) return true;
					}
				}
			}
			return false;
		}
	}
	return IsEquipCharacterByItem(chref, itemID);
}

// --> ugeen - проверяем, есть ли карта в атласе     18.06.09
bool IsEquipCharacterByMap(ref chref, string itemID)
{
	aref arEquip;
	string groupID = MAPS_ITEM_TYPE;

	makearef(arEquip,chref.equip.(groupID));
	int q = GetAttributesNum(arEquip);
	for(int i=0; i<q; i++)
	{
		if(GetAttributeValue(GetAttributeN(arEquip,i))==itemID) return true;
	}

	return false;
}
// получить суммарный вес экипированных предметов в зависимости от группы -> нужно для атласа карт
float GetEquippedItemsWeight(ref chref, string groupID)
{
	int 	j;
	string  itemID;
    ref     itm;
	float 	fEquipWeight = 0.0;

	for (j=0; j<TOTAL_ITEMS; j++)
	{
		makeref(itm,Items[j]);
		if(CheckAttribute(itm, "ID"))
		{
			itemID = itm.id;
			if(groupID == MAPS_ITEM_TYPE)
			{
				if (!CheckAttribute(itm,"mapSpecial"))
				{
					if (CheckAttribute(chref, "items."+itemID) && IsEquipCharacterByMap(chref, itemID))
					{
						fEquipWeight += stf(itm.Weight);
					}
				}
			}
			else
			{
				if (CheckAttribute(chref, "items."+itemID) && IsEquipCharacterByItem(chref, itemID))
				{
					fEquipWeight += stf(itm.Weight);
				}
			}
		}
	}

	return fEquipWeight;
}
// <-- ugeen
string GetCharacterEquipByGroup(ref chref, string groupID)
{
	if( CheckAttribute(chref,"equip."+groupID) ) return chref.equip.(groupID);
	return "";
}

string GetCharacterEquipPictureByGroup(ref chref, string groupID)
{
	string sItem = GetCharacterEquipByGroup(chref, groupID);
	for(int i = TOTAL_ITEMS-1; i >= 0; i--)
	{
		if(CheckAttribute(&items[i], "ID") && items[i].id == sItem)
		{
			if(Items[i].id == "spyglass5")
			{
				Items[i].picIndex = 4;
			}
			return groupID + items[i].picIndex;
		}
	}
	return "";
}

void RemoveCharacterEquip(ref chref, string groupID)
{
	DeleteAttribute(chref,"equip."+groupID);
	SetEquipedItemToCharacter(chref,groupID,"");
	SetNewModelToChar(chref);
}

void RemoveOfficerEquip(ref chref, string groupID)
{
	string sItemID = chref.equip.(groupid);

	DeleteAttribute(chref,"equip."+groupID);
	SetEquipedItemToCharacter(chref,groupID,"");
	TakeItemFromCharacter(chref, sItemID);
	GiveItem2Character(pchar, sItemID);
	SetNewModelToChar(chref);
}

void SetEquipedItemToCharacter(ref chref, string groupID, string itemID)
{
	object emptyItm;
	aref arItm;
	string modelName = "";
	makearef(arItm,emptyItm);
 	int itemNum; // boal 23.01.2004

	if(itemID!="")
	{
		if( !CheckCharacterItem(chref,itemID) ) return;
		itemNum = Items_FindItem(itemID,&arItm);// boal 23.01.2004
	}

	switch(groupID)
	{
	case SPYGLASS_ITEM_TYPE:
		if(CheckAttribute(arItm,"id"))
		{
			setTelescopeInitParameters(arItm);
		}
	break;
    // boal -->
    case CIRASS_ITEM_TYPE:
        if (CheckAttribute(chref, "HeroModel")) // все, у кого есть что одеть
        {
            if (CheckAttribute(arItm, "model"))
            {
                chref.model = GetSubStringByNum(chref.HeroModel, sti(arItm.model));
                chref.cirassId = itemNum;
            }
            else
            {
                chref.model = GetSubStringByNum(chref.HeroModel, 0);
                DeleteAttribute(chref, "cirassId");
            }
        }
        else
        {
            // тут анализ модели офицера или пирата
            if(CheckAttribute(arItm, "model"))
            {
                chref.cirassId = itemNum;
            }
            else
            {
                DeleteAttribute(chref, "cirassId");
            }
        }
		ChangeWhisperHeroModel();
        SetNewModelToChar(chref);//boal
	break;

	case PATENT_ITEM_TYPE:
        if(CheckAttribute(arItm,"quest"))
        {
            DoQuestCheckDelay(arItm.quest, 1.0);
            chref.EquipedPatentId = itemNum; // boal текущий патент
        }
        else
        {
            DeleteAttribute(chref, "EquipedPatentId");
        }
    break;
    // boal <--
	case GUN_ITEM_TYPE:
		if(CheckAttribute(arItm,"model"))	{modelName = arItm.model;}
		SendMessage(chref,"ls",MSG_CHARACTER_SETGUN,modelName);
		if(itemID != "")
		{
			LAi_SetCharacterDefaultBulletType(chref);
			if(CheckAttribute(chref,"chr_ai.sGun") && itemID != chref.chr_ai.sGun) LAi_GunSetUnload(chref);
		}
		else
		{
			if(CheckAttribute(chref,"chr_ai.sGun"))			DeleteAttribute(chref,"chr_ai.sGun");
			if(CheckAttribute(chref,"chr_ai.bullet"))		DeleteAttribute(chref,"chr_ai.bullet");
			if(CheckAttribute(chref,"chr_ai.charge_max")) 	DeleteAttribute(chref,"chr_ai.charge_max");
			if(CheckAttribute(chref,"chr_ai.chargeprc")) 	DeleteAttribute(chref,"chr_ai.chargeprc");
		}
	break;

	case BLADE_ITEM_TYPE:
		float liveTime = 0.1;
		int colors = argb(64, 64, 64, 64);
		int colore = argb(0, 32, 32, 32);
		if(CheckAttribute(arItm,"model"))	{modelName = arItm.model;}
		if(CheckAttribute(arItm, "blade.time"))	{liveTime = stf(arItm.blade.time);}
		if(CheckAttribute(arItm, "blade.colorstart"))	{colors = sti(arItm.blade.colorstart);}
		if(CheckAttribute(arItm, "blade.colorend"))	{colore = sti(arItm.blade.colorend);}
		//SendMessage(chref, "lsfll", MSG_CHARACTER_SETBLADE, modelName, liveTime, colors, colore);
		SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, modelName, liveTime, colors, colore);

		if (CheckAttribute(arItm,"special")) SetWeaponsSpecials(chref,arItm);
		else
		{
			UnsetSpecialAttributes(chref);
		}

		if(CheckAttribute(arItm,"dmg_min"))
		{	LAi_BladeSetDamageMin(chref,stf(arItm.dmg_min));
		} else
		{	LAi_BladeSetDamageMin(chref,0.0);
		}
		if(CheckAttribute(arItm,"dmg_max"))
		{	LAi_BladeSetDamageMax(chref,stf(arItm.dmg_max));
		} else
		{	LAi_BladeSetDamageMax(chref,0.0);
		}
		if(CheckAttribute(arItm,"piercing"))
		{	LAi_BladeSetPiercing(chref,stf(arItm.piercing)*0.01);
		} else
		{	LAi_BladeSetPiercing(chref,0.0);
		}
		if(CheckAttribute(arItm,"block"))
		{	LAi_BladeSetBlock(chref,stf(arItm.block)*0.01);
		} else
		{	LAi_BladeSetBlock(chref,0.0);
		}
		// boal -->
		if(CheckAttribute(arItm,"FencingType"))
		{	LAi_BladeFencingType(chref, arItm.FencingType);
		} else
		{	LAi_BladeFencingType(chref, "Fencing");
		}
		if(CheckAttribute(arItm,"Weight")) //eddy.при загрузки локации если у ГГ нет оружия - ошибка
		{
			LAi_BladeEnergyType(chref, GetEnergyBladeDrain(stf(arItm.Weight)) );  // энергоемкость от веса
		}
		// boal <--
	break;
	// --> ugeen 18.06.09   - увеличиваем счетчик карт в атласе
	case MAPS_ITEM_TYPE:
		if(CheckAttribute(chref, "MapsAtlasCount"))
		{
			if(CheckAttribute(arItm, "MapIsland"))
			{
				chref.MapsAtlasCount = sti(chref.MapsAtlasCount) + 1;
				if(sti(chref.MapsAtlasCount) == MAPS_IN_ATLAS && !CheckCharacterPerk(chref, "MapMaker"))  // даем скрытый перк если собрали все карты островов
				{
					SetCharacterPerk(chref, "MapMaker");
				}
			}
		}
	break;
	case AMMO_ITEM_TYPE:
		chref.curammo = arItm.id;
	break;
	// <-- ugeen
	}
}

void UnsetSpecialAttributes(ref chr)
{
	chr.chr_ai.special.valueBB = 0;
	chr.chr_ai.special.valueCrB = 0;
	chr.chr_ai.special.valueCB = 0;
	chr.chr_ai.special.valueSS = 0;
	chr.chr_ai.special.valueStS = 0;
	chr.chr_ai.special.valueT = 0;
	chr.chr_ai.special.valueB = 0;
	chr.chr_ai.special.valueP = 0;
}

void SetWeaponsSpecials(ref chr, ref arItm)
{
	UnsetSpecialAttributes(chr);
	if (CheckAttribute(arItm,"special.valueBB"))
	{
		chr.chr_ai.special.valueBB = sti(arItm.special.valueBB);
	}
	if (CheckAttribute(arItm,"special.valueCrB"))
	{
		chr.chr_ai.special.valueCrB = sti(arItm.special.valueCrB);
	}
	if (CheckAttribute(arItm,"special.valueCB"))
	{
		chr.chr_ai.special.valueCB = sti(arItm.special.valueCB);
	}
	if (CheckAttribute(arItm,"special.valueSS"))
	{
		chr.chr_ai.special.valueSS = sti(arItm.special.valueSS);
	}
	if (CheckAttribute(arItm,"special.valueStS"))
	{
		chr.chr_ai.special.valueStS = sti(arItm.special.valueStS);
	}
	if (CheckAttribute(arItm,"special.valueT"))
	{
		chr.chr_ai.special.valueT = sti(arItm.special.valueT);
	}
	if (CheckAttribute(arItm,"special.valueB"))
	{
		chr.chr_ai.special.valueB = sti(arItm.special.valueB);
	}
	if (CheckAttribute(arItm,"special.valueP"))
	{
		chr.chr_ai.special.valueP = sti(arItm.special.valueP);
	}
}

// коэф траты энергии от веса сабли
float GetEnergyBladeDrain(float _weight)
{
	return _weight / 9.0 + 0.4;
}

void EquipCharacterByItem(ref chref, string itemID)
{
	aref arItm;

	if( !CheckCharacterItem(chref, itemID) ) return;
	if( Items_FindItem(itemID, &arItm)<0 )	return;
	if( !CheckAttribute(arItm, "groupID") ) return;

	if(chref.id == "pet_crab" && itemID != "unarmed")
	{
		TakeItemFromCharacter(chref, "unarmed");
		GiveItem2Character(chref, "unarmed");
		itemID = "unarmed";
	}

	string groupName = arItm.groupID;

	if (groupName == BLADE_ITEM_TYPE && CheckAttribute(chref, "DontChangeBlade")) return;
	if (groupName == GUN_ITEM_TYPE && CheckAttribute(chref, "DontChangeGun")) return;
	if (itemID == "mushket2x2" && chref.id != "OffMushketer") return;

	if(groupName != MAPS_ITEM_TYPE) // ugeen - для атласа карт  18.06.09
	{
		string oldItemID = GetCharacterEquipByGroup(chref, groupName);
		if(oldItemID==itemID) return;
	}

	if (findsubstr(chref.model.animation, "mushketer" , 0) != -1)
	{
		if(groupName == BLADE_ITEM_TYPE && itemID != "unarmed") return;

		if(chref.index != GetMainCharacterIndex())
		{
			if (chref.id == "OffMushketer")
			{
				if (groupName == GUN_ITEM_TYPE && itemID != "mushket2x2") return;
			}
			else
			{
				//if (groupName == GUN_ITEM_TYPE && itemID != "mushket") return;
				if (groupName == GUN_ITEM_TYPE && !isMushket(itemID)) return; // Dolphin
			}
		}
	}
	else
	{
		// if (groupName == GUN_ITEM_TYPE && itemID == "mushket") return;
		if (groupName == GUN_ITEM_TYPE && isMushket(itemID)) return; // Dolphin

		// Dolphin -> 2x стволку пока не даем
		//if (groupName == GUN_ITEM_TYPE && itemID == "mushket2x2" && chref.id != pchar.id) return;
	}

	if(groupName != MAPS_ITEM_TYPE) // ugeen  18.06.09
	{
		chref.equip.(groupName) = itemID;
	}
	else
	{
		if (!CheckAttribute(arItm,"mapSpecial"))
		{
			chref.equip.(groupName).(itemID) = itemID;
		}
	}
	if(IsEntity(chref))
	{	SetEquipedItemToCharacter(chref, groupName, itemID);
	}
	if(groupName==GUN_ITEM_TYPE && sti(chref.index)==GetMainCharacterIndex())
	{	LAi_GunSetUnload(chref);
	}
	if (CheckAttribute(arItm, "HeadAccessory"))
	{
		chref.HeadAccessory = arItm.HeadAccessory;
		SetNewModelToChar(chref);
	}
	// boal -->
	/*if (groupName == SPYGLASS_ITEM_TYPE && sti(chref.index)==GetMainCharacterIndex())// && bSeaActive)
	{
		FillISpyGlassParameters();
	}*/
	// boal <--
}
 // to_do
void EquipOfficerByItem(ref chref, string itemID)
{
	aref arItm;

	if(chref.id == "pet_crab" && itemID != "unarmed")
	{
		TakeItemFromCharacter(chref, "unarmed");
		GiveItem2Character(chref, "unarmed");
		itemID = "unarmed";

	}

	string groupName = arItm.groupID;
	if (groupName == BLADE_ITEM_TYPE && CheckAttribute(chref, "DontChangeBlade")) return;
	if (groupName == GUN_ITEM_TYPE && CheckAttribute(chref, "DontChangeGun")) return;
	if (itemID == "mushket2x2" && chref.id != "OffMushketer") return;

	int iItemQuantity = 0;
	if( !CheckCharacterItem(chref, itemID))
	{
		iItemQuantity = GetCharacterItem(pchar);
		if(iItemQuantity == 1 && IsEquipCharacterByItem(pchar, itemID) == true)
		{
			return;
		}
		else
		{
			TakeItemFromCharacter(pchar, itemID);
			GiveItem2Character(chref, itemID);
		}
	}

	EquipCharacterByItem(chref, itemID);
	/*
	if( Items_FindItem(itemID, &arItm)<0 )	return;
	if( !CheckAttribute(arItm, "groupID") ) return;

	string groupName = arItm.groupID;
	string oldItemID = GetCharacterEquipByGroup(chref, groupName);
	if(oldItemID==itemID) return;
	chref.equip.(groupName) = itemID;

	if(IsEntity(chref))
	{	SetEquipedItemToCharacter(chref, groupName, itemID);
	}
	if(groupName==GUN_ITEM_TYPE && sti(chref.index)==GetMainCharacterIndex())
	{	LAi_GunSetUnload(chref);
	}
	*/
}

void ChangeWhisperHeroModel()
{
	if (startherotype == 2)
	{
		bool isMush = false;
		if (findsubstr(PChar.model, "_mush" , 0) != -1)
		{
			PChar.model = FindStringBeforeChar(PChar.model, "_mush");
			isMush = true;
		}
		if(IsEquipCharacterByItem(pchar, "hatWhisper"))
		{
			if (Pchar.model=="PGG_Whisper_0_NoHat")
			{
				Pchar.model="PGG_Whisper_0";
			}
			if (Pchar.model=="PGG_Whisper_1_NoHat")
			{
				Pchar.model="PGG_Whisper_1";
			}
			if (Pchar.model=="PGG_Whisper_2_NoHat")
			{
				Pchar.model="PGG_Whisper_2";
			}
			if (Pchar.model=="PGG_Whisper_3_NoHat")
			{
				Pchar.model="PGG_Whisper_3";
			}
			if (Pchar.model=="PGG_Whisper_4_NoHat")
			{
				Pchar.model="PGG_Whisper_4";
			}
			if (Pchar.model=="PGG_Whisper_5_NoHat")
			{
				Pchar.model="PGG_Whisper_5";
			}
			if (Pchar.model=="PGG_Whisper_5_Cirass_NoHat")
			{
				Pchar.model="PGG_Whisper_5_Cirass";
				if (CheckAttribute(pchar, "Whisper.NanoCostume"))	Pchar.model="PGG_Whisper_5";
			}
			if (Pchar.model=="PGG_Whisper_6_NoHat")
			{
				Pchar.model="PGG_Whisper_6";
			}
			if (Pchar.model=="PGG_Whisper_7_NoHat")
			{
				Pchar.model="PGG_Whisper_7";
			}
			if (Pchar.model=="PGG_Whisper_8_NoHat")
			{
				Pchar.model="PGG_Whisper_8";
			}
			if (isMush)
			{
				Pchar.model = Pchar.model + "_mush";
			}

			if (CheckAttribute(pchar, "Whisper.NanoCostume"))
			{
				pchar.HeroModel  = "PGG_Whisper_0,PGG_Whisper_1,PGG_Whisper_2,PGG_Whisper_3,PGG_Whisper_4,PGG_Whisper_5,PGG_Whisper_6,PGG_Whisper_7,PGG_Whisper_8";
			}
			else
			{
				pchar.HeroModel  = "PGG_Whisper_0,PGG_Whisper_1,PGG_Whisper_2,PGG_Whisper_3,PGG_Whisper_4,PGG_Whisper_5_Cirass,PGG_Whisper_6,PGG_Whisper_7,PGG_Whisper_8";
			}
			DeleteAttribute(pchar,"Whisper.Equipped");
			SetNewModelToChar(pchar);
		}
		else
		{
			if (Pchar.model=="PGG_Whisper_0")
			{
				Pchar.model="PGG_Whisper_0_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_1")
			{
				Pchar.model="PGG_Whisper_1_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_2")
			{
				Pchar.model="PGG_Whisper_2_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_3")
			{
				Pchar.model="PGG_Whisper_3_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_4")
			{
				Pchar.model="PGG_Whisper_4_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_5")
			{
				Pchar.model="PGG_Whisper_5_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_5_Cirass")
			{
				Pchar.model="PGG_Whisper_5_Cirass_NoHat";
				if (CheckAttribute(pchar, "Whisper.NanoCostume"))	Pchar.model="PGG_Whisper_5_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_6")
			{
				Pchar.model="PGG_Whisper_6_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_7")
			{
				Pchar.model="PGG_Whisper_7_NoHat";
			}
			if (Pchar.model=="PGG_Whisper_8")
			{
				Pchar.model="PGG_Whisper_8_NoHat";
			}
			if (isMush)
			{
				Pchar.model = Pchar.model + "_mush";
			}
			if (CheckAttribute(pchar, "Whisper.NanoCostume"))
			{
				pchar.HeroModel  = "PGG_Whisper_0_NoHat,PGG_Whisper_1_NoHat,PGG_Whisper_2_NoHat,PGG_Whisper_3_NoHat,PGG_Whisper_4_NoHat,PGG_Whisper_5_NoHat,PGG_Whisper_6_NoHat,PGG_Whisper_7_NoHat,PGG_Whisper_8_NoHat";
			}
			else
			{
				pchar.HeroModel  = "PGG_Whisper_0_NoHat,PGG_Whisper_1_NoHat,PGG_Whisper_2_NoHat,PGG_Whisper_3_NoHat,PGG_Whisper_4_NoHat,PGG_Whisper_5_Cirass_NoHat,PGG_Whisper_6_NoHat,PGG_Whisper_7_NoHat,PGG_Whisper_8_NoHat";
			}
			pchar.Whisper.Equipped = true;
			SetNewModelToChar(pchar);
		}
	}
}

void ExecuteCharacterEquip(ref chref)
{
	stmp = GetCharacterEquipByGroup(chref,BLADE_ITEM_TYPE);
	if(stmp!="")	{SetEquipedItemToCharacter(chref, BLADE_ITEM_TYPE, stmp);}
	string stmp = GetCharacterEquipByGroup(chref,GUN_ITEM_TYPE);
	if(stmp!="")	{SetEquipedItemToCharacter(chref, GUN_ITEM_TYPE, stmp);}
}

bool IsCanEquiping(ref chref, string equiping_group)
{
	if( CheckAttribute(chref,"equip.disabled_group."+equiping_group)
		&& sti(chref.equip.disabled_group.(equiping_group))==true ) return false;
	return true;
}

void EnableEquip(ref chref, string equiping_group, bool enable)
{
	if(enable)
	{	if(equiping_group=="")
		{	DeleteAttribute(chref,"equip.disabled_group");
		}
		else
		{	DeleteAttribute(chref,"equip.disabled_group."+equiping_group);
		}
	}
	else
	{	if(equiping_group=="")
		{
			string stmp;
			stmp = GUN_ITEM_TYPE;		chref.equip.disabled_group.(stmp) = true;
			stmp = BLADE_ITEM_TYPE;		chref.equip.disabled_group.(stmp) = true;
			stmp = SPYGLASS_ITEM_TYPE;	chref.equip.disabled_group.(stmp) = true;
		}
		else
		{
			chref.equip.disabled_group.(equiping_group) = true;
		}
	}
}
///  репутация ГГ 06/06/06 boal new concept -->
//изменить репутацию персонажа в зависимости от текущей репутации.
//минус для плохого это рост в плюс
bool IsEquipCharacterByArtefact(ref chref, string itemID)
{
	if (IsEquipCharactersByItem(chref, itemID)) return true;
	return false;
}

float isEquippedArtefactUse(ref rChar, string sItem, float fOff, float fOn)
{
	if (IsEquipCharactersByItem(rChar, sItem)) return fOn;
	return fOff;
}

int ChangeCharacterReputationABS(ref chref, float incr)
{
	int curVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") ) curVal = stf(chref.reputation);

	if (curVal < REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterReputation(chref , incr);
}

// репутация стремится к нейтральной
int ChangeCharacterReputationToNeutral(ref chref, float incr)
{
	int curVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") ) curVal = stf(chref.reputation);

	if (curVal > REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterReputation(chref , incr);
}

int ChangeCharacterReputation(ref chref, float incr)
{
	if (CheckAttribute(chref, "GenQuest.ReputationNotChange")) return sti(chref.reputation); //eddy. нужен флаг
	float prevVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") )	prevVal = stf(chref.reputation);

	float newVal = prevVal + incr;
	if (newVal<REPUTATION_MIN) newVal = REPUTATION_MIN;
	if (newVal>REPUTATION_MAX) newVal = REPUTATION_MAX;
	chref.reputation = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return makeint(newVal);

	string prevName = GetReputationName(makeint(prevVal));
	string newName = GetReputationName(makeint(newVal));
	if (prevName!=newName)
	{
		string outString = XI_ConvertString("Your reputation")+" ";
		if (incr>0)	{outString+=XI_ConvertString("increase");}
		else	{outString+=XI_ConvertString("decrease");}
		outString += " "+XI_ConvertString("to")+" "+XI_ConvertString(newName);
		Log_SetStringToLog(outString);
	}

	return makeint(newVal);
}
//    ChangeCharacterNationReputation(chref, iType, incr);

// метод вызывается ежедневно, уменьшает значение крайних репутаций - эффект забывания.
void UpdateFame()
{
	if (sti(pchar.reputation) < (REPUTATION_NEUTRAL - 10))  // плохиш
	{
		ChangeCharacterReputation(pchar, (MOD_SKILL_ENEMY_RATE / 40.0)); // медленнее
	}
	if (sti(pchar.reputation) > (REPUTATION_NEUTRAL + 10))  // кибальчиш
	{
		ChangeCharacterReputation(pchar, (-MOD_SKILL_ENEMY_RATE / 20.0));
	}
}
///  репутация ГГ 06/06/06 boal new concept <--

bool Character_IsAbordageEnable(ref rCharacter)
{
	if (CheckAttribute(rCharacter, "AlwaysFriend")) return false; // boal
	if (CheckAttribute(rCharacter, "Abordage.Enable")) { return sti(rCharacter.Abordage.Enable); }
	return true;
}

void Character_SetAbordageEnable(ref rCharacter, bool bEnable)
{
	rCharacter.Abordage.Enable = bEnable;
}

void Character_SetCompanionEnemyEnable(ref rCharacter, bool bEnable)
{
	rCharacter.CompanionEnemyEnable = bEnable;
}

void AddMsgToCharacter(ref chref, int nMsg)
{
	string msgName = "msg"+nMsg;
	bool bStartEvent = !CheckAttribute(chref,"MessageIcons."+msgName);
	chref.MessageIcons.(msgName).pic = nMsg;
	chref.MessageIcons.(msgName) = MSGICON_ACTIVE_TIME;
	if(bStartEvent) PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,sti(chref.index));
}

void DelMsgFromCharacter(ref chref, int nMsg)
{
	DeleteAttribute(chref,"MessageIcons.msg"+nMsg);
}

void proc_MsgIconTick()
{
	int nMsg = GetEventData();
	int chrIdx = GetEventData();
	if(DialogRun!=0) {
		PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,chrIdx);
		return;
	}
	ref chref = GetCharacter(chrIdx);
	string msgName = "msg"+nMsg;
	int nTime = 0;

	if( CheckAttribute(chref,"MessageIcons."+msgName) )
	{
		nTime = sti(chref.MessageIcons.(msgName));
		if(nTime>0)
		{
			chref.MessageIcons.(msgName) = nTime-1;
			PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,chrIdx);
			return;
		}
		DelMsgFromCharacter(chref,nMsg);
	}
}
 // to_do
int GetCharacterReputation(aref chr, int iNation)
{
	int iVal = 0;
	switch (iNation)
	{
		case 0:
			iVal = sti(chr.reputation.england);
		break;

		case 1:
			iVal = sti(chr.reputation.france);
		break;

		case 2:
			iVal = sti(chr.reputation.spain);
		break;

		case 3:
			iVal = sti(chr.reputation.holland);
		break;

		case 4:
			iVal = sti(chr.reputation.pirate);
		break;

		case 5:
			iVal = sti(chr.reputation.smuggler);
		break;

		case 6:
			iVal = sti(chr.reputation.trader);
		break;
	}

	return iVal;
}

bool isPrisonedChar(aref chr)
{
	if(CheckAttribute(chr,"prisoned"))
	{
		if(sti(chr.prisoned) == 1)
		{
			return true;
		}
	}
	return false;
}

bool CheckForRank(aref chr, int iRank)
{
	if(CheckAttribute(chr, "rank"))
	{
		if(sti(chr.rank) >= iRank)
		{
			return true;
		}
	}
	return false;
}

string  Get_My_Cabin()
{
	return Pchar.SystemInfo.CabinType;
}

string  Get_My_Cabin_Pic()
{
    int  i;

    i = FindLocation(Pchar.SystemInfo.CabinType);
    if (i != -1)
    {
    	return   Locations[i].image;
    }
	return "";
}
bool isShipInside(string _id)
{
    bool   ret = false;
    if (_id == Get_My_Cabin() || _id == "My_Deck_Medium" || _id == "My_Campus" || _id == "My_Deck" || _id == "Deck_Near_Ship")
    {
        ret = true;
        if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && CheckAttribute(pchar, "GenQuest.CaptainId"))
		{
			if (pchar.GenQuest.CaptainId == "MQPirate")
			{
				if (!CheckQuestAttribute("Munity", "Deads")) ret = false;
			}
		}
    }
    return ret;
}
void  Set_My_Cabin()
{
    int     n,i;
    string  sTemp, newCab;
    ref     rShip;

    int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)
	{
        newCab = "My_Cabin";
	}
	else
	{
	    rShip = GetRealShip(nShipType);
	    newCab = "My_" + rShip.CabinType;  // превратим из каюты типа корабля
	}

    if (Pchar.SystemInfo.CabinType != newCab)
    {
        if (Pchar.SystemInfo.CabinType != "")
        {
            // переселить предметы
            ref     loc, locTo;
            aref    arFromBox;
            aref    curItem;
	        string  attr;

            loc   = &locations[FindLocation(Pchar.SystemInfo.CabinType)];
            locTo = &locations[FindLocation(newCab)];
            locTo.box1.money = 0;
            for (n = 1; n <= 4; n++)
            {
                sTemp = "box" + n;

                if (CheckAttribute(loc, sTemp + ".money"))
                {
                    locTo.box1.money = sti(locTo.box1.money) + sti(loc.(sTemp).money);
                }
                makearef(arFromBox, loc.(sTemp).items);
                for(i=0; i<GetAttributesNum(arFromBox); i++)
                {
                    curItem = GetAttributeN(arFromBox, i);
                    attr = GetAttributeName(curItem);
                    if (attr != "")
                    {
                        if (!CheckAttribute(locTo, "box1.items." + attr))
                        {
                            locTo.box1.items.(attr) = 0;
                        }
                        locTo.box1.items.(attr) = makeint(sti(locTo.box1.items.(attr)) + makeint(GetAttributeValue(curItem)));
                    }
                }
                // del
        		DeleteAttribute(loc, sTemp + ".items");
        	    loc.(sTemp).items = "";
        	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
        	    loc.(sTemp).money = 0;
            }
        }
        Pchar.SystemInfo.CabinType = newCab;
        n = FindLocation("My_Deck");
        if (n != -1)
        {
            if (sti(rShip.Class) > 4)
            {
                Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;
                Locations[n].reload.l1.emerge = "reload1";
            }
            else
            {
                Locations[n].reload.l1.go = "My_Deck_Medium";
                Locations[n].reload.l1.emerge = "reload_hold";
            }
        }
        n = FindLocation(Pchar.SystemInfo.CabinType);
        if (n != -1)
        {
            if (sti(rShip.Class) > 4)
            {
                Locations[n].reload.l1.go = "My_Deck";
                Locations[n].reload.l1.emerge = "reload1";
            }
            else
            {
                Locations[n].reload.l1.go = "My_Deck_Medium";
                Locations[n].reload.l1.emerge = "reload_cabin";
            }
        }
        n = FindLocation("My_Deck_Medium");
        if (n != -1)
        {
            Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;
        }
    }
}
// есть ли патент
bool isMainCharacterPatented()
{
    if(CheckAttribute(pchar, "EquipedPatentId") && CheckCharacterItem(pchar, Items[sti(pchar.EquipedPatentId)].id))
    {
        return true;
    }
    return false;
}

int GetPatentNation()
{
    if(CheckAttribute(pchar, "EquipedPatentId") && CheckCharacterItem(pchar, Items[sti(pchar.EquipedPatentId)].id))
    {
        return sti(Items[sti(pchar.EquipedPatentId)].Nation);
    }
    return -1;
}

// звания
void AddTitleNextRate(int nation, float num)
{
    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == nation)
    {
        Items[sti(pchar.EquipedPatentId)].TitulCurNext = stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) + num;
        if (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) < 0) Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
        if (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) > MAX_TITLENEXTRATE) Items[sti(pchar.EquipedPatentId)].TitulCurNext = MAX_TITLENEXTRATE;
        Log_TestInfo("TitleCurNext = " + stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext));
    }
}
// присвоить следующее?
bool isReadyToNextTitle(int nation)
{
    bool    ret = false;

    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == nation)
    {
        if (sti(Items[sti(pchar.EquipedPatentId)].TitulCur) < MAX_TITLE && (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) / sti(Items[sti(pchar.EquipedPatentId)].TitulCur)) >= 3)
        {
            ret = true;
        }
    }

    return ret;
}
// проверка на допустимость игры в карты и кости -->
float GetCardsGameCheckRate()
{
	float k;
	float   fWin, fLose;


	fWin  = makefloat(Statistic_AddValue(Pchar, "GameCards_Win", 0));
    fLose = makefloat(Statistic_AddValue(Pchar, "GameCards_Lose", 0));
    if (fLose < 1) fLose = 1.0;

    k = fWin / fLose;

	return k;
}
bool CheckCardsGameSmallRate()
{
	bool    ret = true;

    if (GetCardsGameCheckRate() >= 15)
    {
        ret = false;
    }
	return ret;
}

bool CheckCardsGameBigRate()
{
	bool    ret = true;

    if (GetCardsGameCheckRate() >= 7)
    {
        ret = false;
    }
	return ret;
}

float GetDiceGameCheckRate()
{
	float k;
	float   fWin, fLose;


	fWin  = makefloat(Statistic_AddValue(Pchar, "GameDice_Win", 0));
    fLose = makefloat(Statistic_AddValue(Pchar, "GameDice_Lose", 0));
    if (fLose < 1) fLose = 1.0;

    k = fWin / fLose;

	return k;
}
bool CheckDiceGameSmallRate()
{
	bool    ret = true;

    if (GetDiceGameCheckRate() >= 15)
    {
        ret = false;
    }
	return ret;
}

bool CheckDiceGameBigRate()
{
	bool    ret = true;

    if (GetDiceGameCheckRate() >= 7)
    {
        ret = false;
    }
	return ret;
}
// проверка на допустимость игры в карты и кости <--
// boal 08.01.05 -->
int GetPartyCrewQuantity(ref _refCharacter, bool _removable) // true - если только наши
{
	int cn;
	int sumCrew = 0;
	ref officer;

	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1)
		{
            officer = GetCharacter(cn);
            if (!GetRemovable(officer) && _removable) continue; // только наши + ГГ
			sumCrew = sumCrew + GetCrewQuantity(officer);
		}
	}
	return sumCrew;
}

int GetTroopersCrewQuantity(ref _refCharacter)
{
	int cn, j;
	int compCrew;
	int sumCrew = 0;
	ref officer;

 	if (CheckOfficersPerk(_refCharacter, "Troopers"))
    {
        Log_TestInfo("-= GetTroopersCrewQuantit =-");
        for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
        {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (!GetRemovable(officer)) continue;

		        compCrew = GetCrewQuantity(officer) - GetMinCrewQuantity(officer);
		        if (compCrew < 0)
		        {
		           compCrew = 0;
		        }
				compCrew = GetWeaponCrew(officer, compCrew);  // без оружия просто не идут (как половина команды учет)

                if (compCrew > 0)
                {
	                RemoveCharacterGoodsSelf(officer, GOOD_WEAPON, makeint(compCrew/2 + 0.5));
	                SetCrewQuantity(officer, GetCrewQuantity(officer) - compCrew);
                	Log_SetStringToLog("Десант корабля " + officer.Ship.Name + " составляет " + compCrew + " человек.");
                	AddCharacterExpToSkill(officer, "Defence", makeint(compCrew / 2 + 0.5)); //качаем защиту
                	AddCharacterExpToSkill(officer, "Grappling", makeint(compCrew / 2 + 0.5)); //качаем абордаж
                	sumCrew = sumCrew + compCrew;
                }
		    }
		}
    }
    // квестовый перк
    if (CheckAttribute(_refCharacter, "TempPerks.QuestTroopers"))
	{
        Log_TestInfo("-= QuestTroopers =-");
		for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
        {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (GetRemovable(officer)) continue; // токо квесты

		        compCrew = GetCrewQuantity(officer);
		        if (compCrew < 0)
		        {
		           compCrew = 0;
		        }
		        Log_SetStringToLog("Десант корабля " + officer.Ship.Name + " составляет " + compCrew + " человек.");
                if (compCrew > 0)
                {
                	sumCrew = sumCrew + compCrew;
                }
		    }
		}
		DeleteAttribute(_refCharacter, "TempPerks.QuestTroopers");
	}
	return sumCrew;
}
// распределить перегруз экипажа по кораблям ГГ
void AddTroopersCrewToOther(ref _refCharacter)
{
	int cn, j;
	int compCrew;
	int sumCrew = 0;
	ref officer;

    compCrew = 0;
    if (GetMaxCrewQuantity(_refCharacter) < GetCrewQuantity(_refCharacter))
    {
        compCrew = GetCrewQuantity(_refCharacter) - GetMaxCrewQuantity(_refCharacter);
        SetCrewQuantity(_refCharacter, GetMaxCrewQuantity(_refCharacter));
    }
	if (compCrew > 0)
	{
	    for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
	    {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (!GetRemovable(officer)) continue;

                if (GetMaxCrewQuantity(officer) >= (GetCrewQuantity(officer) + compCrew))
                {
                    SetCrewQuantity(officer, (GetCrewQuantity(officer) + compCrew));
                    break;  // все влезли
                }
                else
                {
                    compCrew = (GetCrewQuantity(officer) + compCrew) - GetMaxCrewQuantity(officer);
                    SetCrewQuantity(officer, GetMaxCrewQuantity(officer));
                }
		    }
		}
	}
}
// boal 21.01.2004
int GetWeaponCrew(ref _char, int _crew)
{
    int weaponOnBoard = GetCargoGoods(_char, GOOD_WEAPON);
	if (_crew > weaponOnBoard)
	{
	    _crew = weaponOnBoard + makeint(( _crew - weaponOnBoard)/2.0 + 0.5);
	}
	return makeint(_crew);
}
// boal 08.01.05 <--

// ========================= eddy пока сюда перенесу
int GenerateNationTrade(int nation)
{
	int i = -1;
	// boal -->
	int   j = 0;
	bool  ok;

	while (i == -1 && j < 10)
	{
		i = rand(MAX_NATIONS - 1);
		ok = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) && (i != PIRATE); //fix 12.05.05
		if (ok || GetNationRelation(nation, i) == RELATION_ENEMY) // boal было nation == i || i == PIRATE- но сами себе можем!!!
		{
			i = -1;
		}
		j++;
	}
    // boal <--
	return i;
}

int RecalculateSquadronCargoLoad(ref _refCharacter)
{
	int i,cn;
	int retVal = RecalculateCargoLoad(_refCharacter);

	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{
			retVal = retVal + RecalculateCargoLoad(&Characters[cn]);
		}
	}
	return retVal;
}

// из Боф_реакшн
void LoansMoneyAvenger(ref _loan)
{
    Log_SetStringToLog("Срок Вашего займа истек");

    LoansMoneyAvengerAmount(_loan, 25);
}

void LoansMoneyAvengerAmount(ref _loan, int _sum)
{
    string typeHunter = NationShortName(sti(_loan.nation)) + "hunter";
    ChangeCharacterReputation(Pchar, -20);
    OfficersReaction("bad");
    if ( _loan.nation == PIRATE)
    {
        typeHunter = "enghunter";  // за пиратов мстит англия
    }
    ChangeCharacterHunterScore(PChar, typeHunter, _sum);
}
//homo возращает нпс стоящего на локаторе
int GetCharacterbyLocation(string location, string group, string locator)
{
    ref sld;
    for(int i=0;i<MAX_CHARACTERS;i++)
	{
        sld = &characters[i];
        if (sld.location == location && sld.location.group == group && sld.location.locator == locator) return i;
	}
	return -1;
}

// Warship -->
// Сделать ГГ мушкетером или обычным фехтовальщиком
bool SetMainCharacterToMushketer(string sMushket, bool _ToMushketer) // если _ToMushketer == true, значит делаем мушкетером, иначе - делаем ГГ фехтовальщиком
{
	int iItem;
	string sLastGun = "";

	if(_ToMushketer && sMushket != "") // Делаем ГГ мушкетером
	{
		iItem = GetItemIndex(sMushket);
		if(iItem == -1) return false;

		// Стоит проверка при надевании предмета. Если каким-то образом дошло до сюда, то тут не разрешим
		//if(!CanEquipMushketOnLocation(PChar.Location)) return false; //мушкеты в тавернах - Gregg

		sLastGun = GetCharacterEquipByGroup(PChar, GUN_ITEM_TYPE);
		PChar.IsMushketer = true; // Ставим флаг "ГГ - мушкетер"
		PChar.IsMushketer.MushketID = sMushket; // Запомним, какой мушкет надели
		PChar.IsMushketer.LastGunID = sLastGun; // Запомним ID предыдущего пистоля
		PChar.model = PChar.model + "_mush";
		if (pchar.sex == "woman")
		{
			aref weapon;
			Items_FindItem(sMushket, &weapon);
			if (CheckAttribute(weapon, "fromHip"))
			{
				PChar.model.animation = "mushketer_whisper_short"; // Сменим анимацию
			}
			else
			{
				PChar.model.animation = "mushketer_whisper"; // Сменим анимацию
			}
		}
		else
		{
			PChar.model.animation = "mushketer"; // Сменим анимацию
		}
		Characters_RefreshModel(PChar); // Обновим модель. Важно: обновлять модель нужно ДО экипировки мушкетом
		EquipCharacterByItem(PChar, sMushket); // Экипируем мушкет
		PChar.Equip.TempGunID = sLastGun; // Пистоль оставляем экипированным, но в другой группе

	}
	else // Делаем ГГ обычным фехтовальщиком
	{
		PChar.model = FindStringBeforeChar(PChar.model, "_mush"); // Вернем модель и анимацию
		if (IsCharacterPerkOn(pchar,"AgileMan")) PChar.model.Animation = MainChAnim+"_fast";
		else PChar.model.Animation = MainChAnim;
		Characters_RefreshModel(PChar);
		RemoveCharacterEquip(PChar, GUN_ITEM_TYPE); // Снимим мушкет
		if(PChar.IsMushketer.LastGunID != "" && GetCharacterItem(PChar, PChar.IsMushketer.LastGunID) > 0)
		{
			EquipCharacterByItem(PChar, PChar.IsMushketer.LastGunID); // Оденем прошлый пистоль
		}

		DeleteAttribute(PChar, "IsMushketer");
		DeleteAttribute(PChar, "Equip.TempGunID");
	}

	return true;
}

// Можно-ли экипировать мушкет в локации?
bool CanEquipMushketOnLocation(string LocationID)
{
	int iLocation = FindLocation(LocationID);
	if(iLocation == -1) return false;

	if(HasSubStr(LocationID, "Tavern")) // В таверне нельзя
	{
		return false;
	}

	return true;
}

// Есть ли для нашего ГГ мушкетерская модель?
bool IsPCharHaveMushketerModel()
{
	String sModel = PChar.Model;

	if(HasSubStr(sModel, "Blad") ||
	HasSubStr(sModel, "Whisper") ||
	HasSubStr(sModel, "PGG_Anamaria") ||
	HasSubStr(sModel, "PGG_Victori") ||
	HasSubStr(sModel, "PGG_Angellica") ||
	HasSubStr(sModel, "PGG_Beatric") ||
	HasSubStr(sModel, "PGG_Isabella") ||
	HasSubStr(sModel, "PGG_Cirilla") ||
	HasSubStr(sModel, "PGG_Isabella") ||
	HasSubStr(sModel, "PGG_Mary") ||
	HasSubStr(sModel, "PGG_Rumba") ||
	HasSubStr(sModel, "YokoDias") ||
	HasSubStr(sModel, "PGG_PettY") ||
	HasSubStr(sModel, "PGG_Shicoba") ||
	HasSubStr(sModel, "PGG_Black") ||
	HasSubStr(sModel, "PGG_Benito") ||
	HasSubStr(sModel, "PGG_Sharp") ||
	HasSubStr(sModel, "PGG_PeBlad") ||
	HasSubStr(sModel, "PGG_Montoia") ||
	HasSubStr(sModel, "Pat") ||
	HasSubStr(sModel, "Resc") ||
	HasSubStr(sModel, "Port") ||
	HasSubStr(sModel, "PGG_ShMor") ||
	HasSubStr(sModel, "PGG_ShBerg") ||
	HasSubStr(sModel, "PGG_Devlin") ||
	HasSubStr(sModel, "PGG_Uof") ||
	HasSubStr(sModel, "PGG_Alonso") ||
	HasSubStr(sModel, "PGG_Archy") ||
	HasSubStr(sModel, "PGG_Chard") ||
	HasSubStr(sModel, "PGG_Isterling") ||
	HasSubStr(sModel, "PGG_Barrows") ||
	HasSubStr(sModel, "PGG_Pitt") ||
	HasSubStr(sModel, "PGG_Claude_Durand") ||
	HasSubStr(sModel, "PGG_DeLuck") ||
	HasSubStr(sModel, "PGG_Fox") ||
	HasSubStr(sModel, "PGG_Hugh") ||
	HasSubStr(sModel, "PGG_Alex_blade") ||
	HasSubStr(sModel, "PGG_HuanChahotka") ||
	HasSubStr(sModel, "PGG_Doggerty") ||
	HasSubStr(sModel, "PGG_Fleetwood") ||
	HasSubStr(sModel, "PGG_Longway") ||
	HasSubStr(sModel, "PGG_Black") ||
	HasSubStr(sModel, "PGG_Yohang") ||
	HasSubStr(sModel, "PGG_Tich") ||
	HasSubStr(sModel, "PGG_Tibo") ||
	HasSubStr(sModel, "PGG_Hero") ||
	HasSubStr(sModel, "PGG_Blad_vorob") ||
	HasSubStr(sModel, "PGG_Ballantre") ||
	HasSubStr(sModel, "PGG_Dartanian") ||
	HasSubStr(sModel, "PGG_Enrique") ||
	HasSubStr(sModel, "PGG_Espinosa") ||
	HasSubStr(sModel, "PGG_Espinosa") ||
	HasSubStr(sModel, "PGG_Skeletcap") ||
	HasSubStr(sModel, "PGG_Baltrop") ||
	HasSubStr(sModel, "PGG_Nord") ||
	HasSubStr(sModel, "PGG_Lejitos") ||
	HasSubStr(sModel, "PGG_Vincento") ||
	HasSubStr(sModel, "PGG_Alvares") ||
	HasSubStr(sModel, "PGG_Natan") ||
	HasSubStr(sModel, "PGG_Darkhuman") ||
	HasSubStr(sModel, "PGG_Norman") ||
	HasSubStr(sModel, "PGG_Barbossa") ||
	HasSubStr(sModel, "PGG_Meriman") ||
	HasSubStr(sModel, "PGG_WillTerner") ||
	HasSubStr(sModel, "PGG_Kneepel") ||
	HasSubStr(sModel, "PGG_Rozencraft"))
	{
		return true;
	}

	return false;
}

// Создадим клона персонажа. Корабль не копируется
int CreateCharacterClone(ref Character, int iLifeDay)
{
	int iTemp = NPC_GeneratePhantomCharacter("citizen", sti(Character.Nation), MAN, iLifeDay);
	if(iTemp != -1)
	{
		ref rCloneChar = &Characters[iTemp];
		ChangeAttributesFromCharacter(rCloneChar, Character, true);
	}

	return iTemp;
}

// Получим ID надетой одежды
String GetCharacterEquipSuitID(ref rChar)
{
	ref rItem;
	String sItem = GetCharacterEquipByGroup(rChar, CIRASS_ITEM_TYPE);

	if(sItem == "") return INVALID_SUIT;

	rItem = ItemsFromID(sItem);

	if(sti(GetAttrValue(rItem, "Clothes"))) // Одежда
	{
		return sItem;
	}

	return INVALID_SUIT;
}
// <-- Warship
// --> ugeen   16.02.09
// Запомним офицеров во временном хранилище(нужно по Аскольду)
bool StoreOfficers_Ascold(ref refCh)
{
	if( CheckAttribute( refCh, "Fellows.Old") ) DeleteAttribute( refCh, "Fellows.Old" );

	string sTmp;
	aref arTmp;
	int i, idx;
	// сохраним офицеров
	makearef( arTmp, refCh.Fellows.Old.Officers );
	for(i = 1; i < MAX_NUM_FIGHTERS; i++ )
	{
		idx = GetOfficersIndex(refCh,i);
		if( idx == -1 ) continue;
		sTmp = "id"+i;
		arTmp.(sTmp) = idx;
	}
	return true;
}

// Восстановить запомненных ранее офицеров
bool RestoreOfficers_Ascold(ref refCh)
{
	if( !CheckAttribute( refCh, "Fellows.Old") ) return false;

	int i,idx;
	aref arTmp,arCur;

	// Восстановление офицеров
	makearef(arTmp, refCh.Fellows.Old.Officers);
	for(i=0; i<GetAttributesNum(arTmp); i++)
	{
		arCur = GetAttributeN(arTmp,i);
		idx = sti(GetAttributeValue(arCur));
		if( idx == -1 ) continue;
		SetOfficersIndex( refCh, -1 , idx );
	}

	// удаление временного хранилища офицеров
	DeleteAttribute(refCh,"Fellows.Old");
	return true;
}

void EquipCharacterByAtlas(ref chref)
{
	string groupID = MAPS_ITEM_TYPE;
	ref rLoc = ItemsFromID("MapsAtlas");
	chref.equip.(groupID) = rLoc.id;
}

// проверим наличие атласа и карты в нем
bool CheckMapForEquipped(ref refCh, string itemID)
{
	int   idLngFile;
	ref   arItem;

	arItem = ItemsFromID(itemID);
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	if(sti(refCh.index) == GetMainCharacterIndex() && CheckCharacterItem(refCh, arItem.id))
	{
		if(!CheckCharacterItem(refCh, "MapsAtlas")) { // тривиальная проверка на наличие атласа - если его нет,  то получите и распишитесь
			GiveItem2Character(refCh, "MapsAtlas");
			EquipCharacterByAtlas(refCh);
		}
		if(!IsEquipCharacterByMap(refCh, itemID)) { // проверяем, экипирован ли ГГ  этой картой
			EquipCharacterByItem(refCh, itemID);
			Log_SetStringToLog(LanguageConvertString(idLngFile, arItem.name) +" добавлена в атлас");
			arItem = ItemsFromID("MapsAtlas");
			arItem.Weight = GetEquippedItemsWeight(refCh, MAPS_ITEM_TYPE);
		}
		else return false;
	}

	LanguageCloseFile(idLngFile);
	return true;
}

// проверка - есть ли новые карты для включения в атлас
void RefreshEquippedMaps(ref chref)
{
	int 	i;
	string  itemID, groupID;
    ref     itm;

	for (i=0; i<TOTAL_ITEMS; i++)
	{
		makeref(itm,Items[i]);
		if(CheckAttribute(itm, "ID") && CheckAttribute(itm, "groupID"))
		{
			itemID = itm.id;
			groupID = itm.groupID;
			if(groupID == MAPS_ITEM_TYPE && !CheckAttribute(itm, "mapSpecial"))
			{
				CheckMapForEquipped(chref, itemID);
			}
		}
	}
}

void StoreEquippedMaps(ref refCh)
{
    aref arItems;
	string  sName, groupID;
	ref rLoc;

	if( CheckAttribute( refCh, "Stored.Maps") ) DeleteAttribute( refCh, "Stored.Maps" );
	makearef(arItems, refCh.items);
    int	Qty = GetAttributesNum(arItems);

	for (int a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if(CheckAttribute(rLoc, "GroupID"))
		{
			groupID = rLoc.groupID;
			if(groupID == MAPS_ITEM_TYPE)
			{
				if(IsEquipCharacterByMap(refCh, rLoc.id))
				// проверяем, экипирован ли ГГ  этой картой
				{
					refCh.Stored.Maps.(sName) = refCh.items.(sName);
				}
			}
		}
    }
}

void RestoreEquippedMaps(ref refCh)
{
    aref arItems;
	string sName;

	if( !CheckAttribute( refCh, "Stored.Maps") ) return;

	makearef(arItems, refCh.Stored.Maps);
    int Qty = GetAttributesNum(arItems);
    for (int a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(refCh, sName, 1);
    }
	DeleteAttribute(refCh, "Stored.Maps");
	RefreshEquippedMaps(refCh);
}
// <-- ugeen

void OfficersHold()
{
	int idx;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx)
			SetCharacterTask_Stay(offchar);
		}
	}
}

void OfficersFollow()
{
	int idx;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx)
			LAi_tmpl_SetFollow(offchar, GetMainCharacter(), -1.0);
		}
	}
}

/*void OfficersFree()
{
	int idx;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx)
			LAi_tmpl_walk_go(offchar);
		}
	}
}*/

void OfficersFree()
{
    int idx;
    for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
    {
        idx = GetOfficersIndex(PChar,i);
        if (idx != -1)
        {
            ref offchar = GetCharacter(idx);
            if(bAbordageStarted) SetCharacterTask_GotoPoint(offchar, "rld", LAi_FindFreeRandomLocator("rld"));
            else LAi_tmpl_walk_go(offchar);
        }
    }
}

//Boyer mod #20170318-25 for applying item equip logic after an officer receives new perk
void CharacterCheckEquipAll(ref refCharacter)
{

	if(!CheckAttribute(refCharacter, "id")) return;
	//The following is derived from itemstrade.c and itemsbox.c
	//Calls functions in CharacterUtilite.c to apply logic to equip item from refCharacter's inventory
	if (CheckAttribute(refCharacter, "skill.Fencing")) {
		EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BLADE_ITEM_TYPE));
		if (GetCharacterSkill(refCharacter,"Fencing") > 0.1) {
            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,CIRASS_ITEM_TYPE));
		}
	}
	if (CheckAttribute(refCharacter, "skill.Pistol") && GetCharacterSkill(refCharacter,"Pistol") > 0.1 )
	{
		EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,GUN_ITEM_TYPE));
	}
}

// dolphin смена мушкета
#event_handler("Event_SwapWeapon", "SwapWeapon");
void SwapWeapon()
{
	SetMainCharacterToMushketer(pchar.mushket, true);
	PostEvent("Event_SwapWeapon2", 100);
}

#event_handler("Event_SwapWeapon3", "SwapWeapon3");
void SwapWeapon3()
{
	SetMainCharacterToMushketer(pchar.mushket, false);
	PostEvent("Event_SwapWeapon2", 100);
}

#event_handler("Event_SwapWeapon2", "SwapWeaponFight");
void SwapWeaponFight()
{
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	PostEvent("Event_SwapWeapon4", 2000);
}

#event_handler("Event_SwapWeapon4", "SwapWeaponFight2");
void SwapWeaponFight2()
{
	pchar.mushket.timer = false;
}
