
//------------------------------------------------------------------------------------------
//Login
//------------------------------------------------------------------------------------------

//Установить время загрузки персонажа
void LAi_SetLoginTime(aref chr, float start, float end)
{
	if(start < 0) start = 0;
	if(start >= 24) start = 23.99999999;
	if(end < 0) end = 0;
	if(end >= 24) end = 23.99999999;
	chr.location.stime = start;
	chr.location.etime = end;
}

//Удалить время загрузки персонажа
void LAi_RemoveLoginTime(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "stime");
	DeleteAttribute(loc, "etime");
}

//Данный персонаж является верующим, и в определённое время находиться в церкви
void LAi_SetFanatic(aref chr, string churchID, string group, string locator, float start, float end)
{
	chr.location.church = churchID;
	chr.location.church.group = group;
	chr.location.church.locator = locator;
	chr.location.church.stime = start;
	chr.location.church.etime = end;
}

//Сделать обычным персонаж
void LAi_RemoveFanatic(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "church");
}

//Запретить перерождение персонажа после убийства
void LAi_NoRebirthEnable(aref chr)
{
	chr.location.norebirth = "1";
}

//Разрешить перерождение персонажа после убийства
void LAi_NoRebirthDisable(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "norebirth");
}

//Перерождение нпс со старым именем
void LAi_RebirthOldName(aref chr)
{
	chr.location.rebirthOldName = true;
}

//Разрешить/запретить персонажу загружаться в захваченную локацию
void LAi_LoginInCaptureTown(aref chr, bool isEnable)
{
	aref loc;
	makearef(loc, chr.location);
	if(isEnable)
	{
		loc.loadcapture = "1";
	}else{
		DeleteAttribute(loc, "loadcapture");
	}
}

//------------------------------------------------------------------------------------------
//Fight, hp
//------------------------------------------------------------------------------------------

//Установить хитпойнты
void LAi_SetHP(aref chr, float cur, float max)
{
	if(max < 1) max = 1;
	if(cur < 0) cur = 0;
	if(cur > max) cur = max;
	chr.chr_ai.hp = cur;
	chr.chr_ai.hp_max = max;
}

//Установить текущии хитпойнты
void LAi_SetCurHP(aref chr, float cur)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	if(cur < 0) cur = 0;
	if(cur > maxHP) cur = maxHP;
	chr.chr_ai.hp = cur;
	if (cur == 0.0 && CheckAttribute(chr, "PGGAi"))
	{
		PGG_CheckDead(chr);
	}
}

//Установить текущии хитпойнты и энергию максимальными
void LAi_SetCurHPMax(aref chr)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	chr.chr_ai.hp = maxHP;

	chr.chr_ai.energy    = LAi_GetCharacterMaxEnergy(chr); // восстановление там, где мах НР
}

//Скорость изменения хп в секунду
void LAi_SetDltHealth(aref chr, float healthPerSec)
{
	//if(healthPerSec < 0) healthPerSec = 0;
	chr.chr_ai.hp_dlt = healthPerSec;
}

//Использовать бутылочку-лечилку
void LAi_UseHealthBottle(aref chr, float healthInBottle)
{
	if(healthInBottle <= 0) return;
	if(!CheckAttribute(chr, "chr_ai.hp_bottle"))
	{
		chr.chr_ai.hp_bottle = "0";
	}
	chr.chr_ai.hp_bottle = stf(chr.chr_ai.hp_bottle) + healthInBottle;
}
// boal
void LAi_UseHealthBottleSpeed(aref chr, float healthSpeed)
{
	if (healthSpeed <= 0) return;

	chr.chr_ai.hp_dlt_bottle = healthSpeed;
}

// Energy Item -->
void LAi_UseEnergyBottle(aref chr, float EnergyInBottle)
{
	if(EnergyInBottle <= 0) return;
	if(!CheckAttribute(chr, "chr_ai.Energy"))
	{
		chr.chr_ai.Energy = 0;
	}
	chr.chr_ai.Energy = stf(chr.chr_ai.Energy) + EnergyInBottle;
}
// Energy Item <--

//navy -->
void LAi_AlcoholSetDrunk(aref chr, float alcoholDegree, float time)
{
	//эффекты не суммируются.
	if (CheckAttribute(chr, "chr_ai.drunk")) return;
	//float energyMax;

	chr.chr_ai.drunk = time;
	//много рома в таверне
	if (alcoholDegree > 70)
	{
		chr.chr_ai.drunk.skill.FencingLight = -20;
		chr.chr_ai.drunk.skill.Fencing 	    = -20;
		chr.chr_ai.drunk.skill.FencingHeavy = -20;
		chr.chr_ai.drunk.skill.Pistol       = -20;
		chr.chr_ai.drunk.skill.Fortune      = -20;
		chr.chr_ai.drunk.skill.Sneak        = -20;
		chr.chr_ai.drunk.skill.Leadership   = -20;
	}
	else
	{
		//Ром
		if (alcoholDegree > 50)
		{
			chr.chr_ai.drunk.skill.FencingLight = -10;
			chr.chr_ai.drunk.skill.FencingHeavy = 10;
		}
		//вино
		else
		{
			chr.chr_ai.drunk.skill.FencingLight = 10;
			chr.chr_ai.drunk.skill.FencingHeavy = -10;
		}
		chr.chr_ai.drunk.skill.Fortune = 5;
		chr.chr_ai.drunk.skill.Pistol = -20;
	}

	//думал бонус к макс энергии сделать, но оно по другому работает :) пока так.. а там видно будет.
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		/*
		energyMax = stf(chr.chr_ai.energyMax);
		if(energyMax < 1) energyMax = 1;
		chr.chr_ai.drunk.energyMax = energyMax*0.2;
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) + stf(chr.chr_ai.drunk.energyMax);
		*/
		chr.chr_ai.energy = stf(chr.chr_ai.energy) + 20;
	}
}

void LAi_SetAlcoholNormal(aref chr)
{
	/*
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) - stf(chr.chr_ai.drunk.energyMax);
	}
	*/
	if (CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
	if (CheckAttribute(pchar, "GenQuest.CamShuttle")) DeleteAttribute(pchar, "GenQuest.CamShuttle");

	DeleteAttribute(chr, "chr_ai.drunk");
}
//<--

//Использовать бутылочку-противоядие
void LAi_UseAtidoteBottle(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.poison"))
    {
        DeleteAttribute(chr, "chr_ai.poison");
        UnmarkCharacter(chr);
    }
}

//Отравлен
bool LAi_IsPoison(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.poison")) return true;
    return false;
}

//Сделать персонажа бессмертным
void LAi_SetImmortal(aref chr, bool isImmortal)
{
	if(isImmortal)
	{
		chr.chr_ai.immortal = "1";
	}else{
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "immortal");
	}
}

//Узнать отношение персонажа к бессмертию
bool LAi_IsImmortal(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		if(sti(chr.chr_ai.immortal) != 0)
		{
			return true;
		}
	}
	return false;
}


//Получить хп персонажа
float LAi_GetCharacterHP(aref chr)
{
	float curHp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp"))
	{
		curHp = stf(chr.chr_ai.hp);
	}
	float maxHp = LAi_GetCharacterMaxHP(chr);
	if(curHp > maxHp) curHp = maxHp;
	chr.chr_ai.hp = curHp;
	chr.chr_ai.hp_max = maxHp;
	return curHp;
}

//Получить максимальные хп персонажа
float LAi_GetCharacterMaxHP(aref chr)
{
	float max_hp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		max_hp = stf(chr.chr_ai.hp_max);
	}
	if(max_hp < 0.0) max_hp = 0.0;
	chr.chr_ai.hp_max = max_hp;
	return max_hp;
}

//Получить относительные хп персонажа 0..1
float LAi_GetCharacterRelHP(aref chr)
{
	float hp = LAi_GetCharacterHP(chr);
	float maxhp = LAi_GetCharacterMaxHP(chr);
	if(maxhp <= 0.0) return 0.0;
	if(maxhp > 0.0)
	{
		return hp/maxhp;
	}
	return 0.0;
}

//Получить относительную энергию персонажа 0..1
float LAi_GetCharacterRelEnergy(aref chr)
{
	float energy = 0.0;
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		energy = stf(chr.chr_ai.energy);
		energy = energy / LAi_GetCharacterMaxEnergy(chr); // boal
	}
	return energy;
}

float LAi_GetCharacterEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		return stf(chr.chr_ai.energy);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}
// boal
float LAi_GetCharacterMaxEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		return stf(chr.chr_ai.energyMax);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}

//Установить проверяльщик хп, если их становиться меньше чем, вызвать квест
void LAi_SetCheckMinHP(aref chr, float min, bool immortal, string quest)
{
	if(min < 0.9999999) min = 0.9999999;
	chr.chr_ai.hpchecker = min;
	chr.chr_ai.hpchecker.quest = quest;
	chr.chr_ai.hpchecker.immortal = immortal;
}

//Удалить проверяльщик хп
void LAi_RemoveCheckMinHP(aref chr)
{
	aref chr_ai;
	makearef(chr_ai, chr.chr_ai);
	DeleteAttribute(chr_ai, "hpchecker");
}

//Убить персонажа
void LAi_KillCharacter(aref chr)
{
	chr.ScriptedDeath = true;
	chr.chr_ai.hp = "0";
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		string old = chr.chr_ai.immortal;
		chr.chr_ai.immortal = "0";
		LAi_CheckKillCharacter(chr);
		chr.chr_ai.immortal = old;
	}else{
		LAi_CheckKillCharacter(chr);
	}
}

//Убит ли персонаж
bool LAi_IsDead(aref chr)
{
	if (chr.id == "0")
	{
		DeleteAttribute(chr,"chr_ai.blooding");
		return true; // boal если фантома нет, то НПС умер
	}
	if(CheckAttribute(chr,"chr_ai.hp") == false)
	{
		DeleteAttribute(chr,"chr_ai.blooding");
		return true;
	}
	if(stf(chr.chr_ai.hp) < 1.0)
	{
		DeleteAttribute(chr,"chr_ai.blooding");
		return true;
	}
	return false;
}


//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Является ли персонаж управляемым
bool LAi_IsCharacterControl(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_PLAYER) return true;
	}
	return false;
}

//Запретить диалог с персонажем
void LAi_CharacterDisableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "1";
}

//Разрешить диалог с персонажем
void LAi_CharacterEnableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "0";
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnation(aref chr, bool isEnable, bool isUseCurModel)
{
	LAi_CharacterReincarnationEx(chr, isEnable, isUseCurModel, "");
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnationEx(aref chr, bool isEnable, bool isUseCurModel, string locgroup)
{
	if(isEnable)
	{
		if(isUseCurModel)
		{
			chr.chr_ai.reincarnation = "0";
		}else{
			chr.chr_ai.reincarnation = "1";
		}
		if(locgroup == "") locgroup = "goto";
		chr.chr_ai.reincarnation.group = locgroup;
	}else{
		chr.chr_ai = "";
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "reincarnation");
	}
}

bool LAi_CharacterIsReincarnation(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false) return false;
	return true;
}

bool LAi_CharacterReincarnationMode(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false)
	{
		Trace("LAi_CharacterReincarnationMode -> no field chr.chr_ai.reincarnation");
		return false;
	}
	if(sti(chr.chr_ai.reincarnation) != 0) return true;
	return false;
}

string LAi_CharacterReincarnationGroup(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation.group") == false)
	{
		Trace("LAi_CharacterReincarnationGroup -> no field chr.chr_ai.reincarnation");
		return "goto";
	}
	if(chr.chr_ai.reincarnation.group != "") return chr.chr_ai.reincarnation.group;
	return "goto";
}

//eddy. установить установить шаг повышения ранга фантома при реинкарнации.
bool LAi_SetReincarnationRankStep(aref _chr, int _step)
{
	if(CheckAttribute(_chr, "chr_ai.reincarnation"))
	{
		_chr.chr_ai.reincarnation.step = _step;
		_chr.baseIndex = _chr.index; //теперь все реинкарнированные фантомы будут помнить индекс своего прародителя.
		return true;
	}
	else Trace("LAi_SetReincarnationRankStep -> no field chr.chr_ai.reincarnation");
	return false;
}

//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Проиграть звук
/* void LAi_CharacterPlaySound(aref chr, string soundname)
{
	SendMessage(chr, "s", soundname);
} */

//Проиграть звук
void LAi_CharacterPlaySound(aref chr, string soundname)
{
	float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	//InitSound();
	SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, soundname, SOUND_WAV_3D, VOLUME_SPEECH, false, false, false, 0, x, y, z);
	pchar.soundname = soundname;
}

void LAi_CharacterPlaySoundAtOnce(aref chr, string soundname)
{
	float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	//InitSound();
	PauseAllSounds();
	ReloadStaticSound();
	SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, soundname, SOUND_WAV_3D, VOLUME_SPEECH, false, false, false, 0, x, y, z);
}

//Переключиться в режим боя и обратно
void LAi_SetFightMode(aref chr, bool isFightMode)
{
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
}
// boal
void LAi_SetFightModeForOfficers(bool isFightMode)
{
    ref chr;
    int j, cn;
    for(j=1; j<=MAX_NUM_FIGHTERS; j++)
    {
        cn = GetOfficersIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        chr = GetCharacter(cn);
	        LAi_type_officer_Init(chr);
	        //LAi_group_UpdateTargets(chr);
            SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
	    }
	}
}

//Заблокировать текущий режим (!!! сбрасывается при смене шаблона !!!)
void LAi_LockFightMode(aref chr, bool isLockFightMode)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", isLockFightMode);
}

//Получить режим боя (вытащена ли сабля)
bool LAi_CheckFightMode(aref chr)
{
	return SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode");
}

//------------------------------------------------------------------------------------------
//Weapons
//------------------------------------------------------------------------------------------


//Получить относительный заряд пистолета
float LAi_GetCharacterRelCharge(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		if(CheckAttribute(chr, "chr_ai.chargeprc"))
		{
			if(sti(chr.chr_ai.chargeprc))
			{
				if(!CheckAttribute(chr, "chr_ai.charge_max")) return 0.0;
				float charge = stf(chr.chr_ai.charge);
				float chargemax = stf(chr.chr_ai.charge_max);
				if(chargemax <= 0) return 0.0;
				if(charge >= chargemax) charge = chargemax;
				charge = charge/chargemax;
				if(charge < 0.0) charge = 0.0;
				if(charge > 1.0) charge = 1.0;
				return charge;
			}else{
				return 1.0;
			}
		}else{
			chr.chr_ai.chargeprc = "1";
		}
	}
	return 0.0;
}

//Получить максимальное количество зарядов пистолета
int LAi_GetCharacterChargeQuant(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge_max"))
	{
		return sti(chr.chr_ai.charge_max);
	}
	return 0;
}

//Получить текущее количество зарядов пистолета
int LAi_GetCharacterChargeCur(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		float charge = stf(chr.chr_ai.charge);
		return MakeInt(charge);
	}
	return 0;
}

//Установить количество зарядов
void LAi_GunSetChargeQuant(aref chr, int quant)
{
	if(quant < 0) quant = 0;
	if(quant > 6) quant = 6;
	chr.chr_ai.charge_max = quant;

	// Warship. Переделка

	/*// boal сюда добавть проверку на наличие пуль gun bullet-->
	int bulletNum = GetCharacterItem(chr, "bullet");

	if (bulletNum > 0)
	{
	    if (bulletNum > quant)
	    {
			chr.chr_ai.charge = quant;
	    }
	    else
	    {
	       chr.chr_ai.charge = bulletNum;
	    }
	}
	else
	{
	    chr.chr_ai.charge = 0;
	}*/
	// boal сюда добавть проверку на наличие пуль gun bullet <--

	int iCharge = iGetPistolChargeNum(chr, quant);
	chr.chr_ai.charge = iCharge;

	chr.chr_ai.chargeprc = "1";
}
float LAi_GetGunChargeProgress(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		float charge = chr.chr_ai.charge;
		if(charge > 1) charge -= MakeInt(chr.chr_ai.charge);
		if(CheckAttribute(chr, "chr_ai.charge_max") && MakeInt(chr.chr_ai.charge_max) == MakeInt(chr.chr_ai.charge)) 
			charge = 1.0;
	}

	return charge;
}
bool LAi_SetCharacterUseBullet(ref rChar, string sBullet)
{
	string 	sAttr;
	string 	sBulletType = "";
	int 	iNum;
	aref 	rType;

	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	if(sGun != "")
	{
		ref rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);
		for (int i = 0; i < iNum; i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBulletType = rItm.type.(sAttr).bullet;
			if(sBulletType == sBullet)
			{
				rChar.chr_ai.sGun			= sGun;
				rChar.chr_ai.bulletType		= sAttr;
				rChar.chr_ai.bulletNum 		= iNum;
				rChar.chr_ai.bullet 		= sBulletType;
				rChar.chr_ai.gunpowder		= rItm.type.(sAttr).gunpowder;
				rChar.chr_ai.accuracy		= rItm.type.(sAttr).Accuracy;
				rChar.chr_ai.chargespeed	= rItm.type.(sAttr).ChargeSpeed;
				rChar.chr_ai.DmgMin_NC		= rItm.type.(sAttr).DmgMin_NC;
				rChar.chr_ai.DmgMax_NC 		= rItm.type.(sAttr).DmgMax_NC;
				rChar.chr_ai.DmgMin_C 		= rItm.type.(sAttr).DmgMin_C;
				rChar.chr_ai.DmgMax_C 		= rItm.type.(sAttr).DmgMax_C;
				rChar.chr_ai.EnergyP_NC 	= rItm.type.(sAttr).EnergyP_NC;
				rChar.chr_ai.EnergyP_C 		= rItm.type.(sAttr).EnergyP_C;
				rChar.chr_ai.Stun_NC 		= rItm.type.(sAttr).Stun_NC;
				rChar.chr_ai.Stun_C			= rItm.type.(sAttr).Stun_C;
				rChar.chr_ai.MultiDmg       = rItm.type.(sAttr).multidmg;
				rChar.chr_ai.MisFire		= rItm.type.(sAttr).misfire;
				rChar.chr_ai.SelfDamage		= rItm.type.(sAttr).SelfDamage;
				rChar.chr_ai.Explosion		= rItm.type.(sAttr).Explosion;

				rItm.ChargeSpeed			= rItm.type.(sAttr).ChargeSpeed;
				rItm.Accuracy				= rItm.type.(sAttr).Accuracy;
				rItm.DmgMin					= rItm.type.(sAttr).DmgMin_NC;
				rItm.DmgMax					= rItm.type.(sAttr).DmgMax_NC;
				rItm.dmg_min 				= rItm.type.(sAttr).DmgMin_NC;
				rItm.dmg_max				= rItm.type.(sAttr).DmgMax_NC;

				if(CheckAttribute(rItm,"chargeQ"))										LAi_GunSetChargeQuant(rChar,sti(rItm.chargeQ));
				else																	LAi_GunSetChargeQuant(rChar, 0);
				if(CheckAttribute(rItm,"chargespeed") && stf(rItm.chargespeed) > 0.0)	LAi_GunSetChargeSpeed(rChar, 1.0/stf(rItm.chargespeed));
				else																	LAi_GunSetChargeSpeed(rChar, 0.0);
				if(CheckAttribute(rItm,"dmg_min"))										LAi_GunSetDamageMin(rChar,stf(rItm.dmg_min));
				else																	LAi_GunSetDamageMin(rChar, 0.0);
				if(CheckAttribute(rItm,"dmg_max"))										LAi_GunSetDamageMax(rChar,stf(rItm.dmg_max));
				else																	LAi_GunSetDamageMax(rChar, 0.0);
				if(CheckAttribute(rItm,"accuracy"))										LAi_GunSetAccuracy(rChar,stf(rItm.accuracy)*0.01);
				else																	LAi_GunSetAccuracy(rChar,0.0);

				rChar.curammo = sBullet;
				return true;
			}
		}
	}
	return false;
}

// ugeen --> получим тип пуль на одетом огнестрельном оружии
string LAi_GetCharacterBulletType(ref rChar)
{
	string sBulletType = "";
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	if(sGun != "")
	{
		if(CheckAttribute(rChar,"chr_ai.bullet"))
		{
			sBulletType 	= rChar.chr_ai.bullet;
		}
	}
	return sBulletType;
}

// ugeen --> получим тип пороха на одетом огнестрельном оружии и известном типе пуль
string LAi_GetCharacterGunpowderType(ref rChar)
{
	string sGunpowderType = "";
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	if(sGun != "")
	{
		if(CheckAttribute(rChar,"chr_ai.gunpowder"))
		{
			sGunPowderType  = rChar.chr_ai.gunpowder;
		}
	}
	return sGunpowderType;
}

string LAi_SetCharacterDefaultBulletType(ref rChar)
{
	string sAttr;
	string sBulletType = "";
	int iNum, i;
	bool isBulletSet = false;
	aref rType;
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	if(sGun != "")
	{
		ref rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);
		if(CheckAttribute(rChar,"curammo"))
		{
			for (i = 0; i < iNum; i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				if (rItm.type.(sAttr).bullet == rChar.curammo)
				{
					sBulletType = rItm.type.(sAttr).bullet;
					isBulletSet = LAi_SetCharacterUseBullet(rChar, sBulletType);
					break;
				}
			}
		}
		if (sBulletType == "")
		{
			for (i = 0; i < iNum; i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				if(sti(rItm.type.(sAttr).Default) > 0)
				{
					sBulletType = rItm.type.(sAttr).bullet;
					isBulletSet = LAi_SetCharacterUseBullet(rChar, sBulletType);
				}
			}
		}
		if(!isBulletSet) trace("can't set default bullet for character id " + rChar.id);
		else rChar.curammo = sBulletType;
	}
	return sBulletType;
}

// Warship. Методы по зарядке пистоля -->
int iGetMinPistolChargeNum(ref rChar) // Чего меньше, пороха или пуль?
{
	string sBulletType = LAi_GetCharacterBulletType(rChar);	 					// узнаем тип пуль
	int iBulletQty = GetCharacterItem(rChar, sBulletType);   					// считаем кол-во пуль
	string sGunPowderType = LAi_GetCharacterGunpowderType(rChar); 				// тип пороха
	if(sGunPowderType != "")
	{
		int iGunPowderQty = GetCharacterItem(rChar, sGunPowderType); 				// кол-во пороха
		int iChargeQty = func_min(iBulletQty, iGunPowderQty); 						// Узнаем, чего меньше
		return iChargeQty;
	}
	return iBulletQty;
}

int iGetPistolChargeNum(ref rChar, int iQuant) // Скока можем зарядить
{
	int iChargeQty = iGetMinPistolChargeNum(rChar);

	if(iChargeQty == 0) return 0;
	if(iChargeQty >= iQuant) return iQuant;
	if(iChargeQty < iQuant) return iChargeQty;
}
// <-- Методы по зарядке пистоля

//Разрядить пистлет
void LAi_GunSetUnload(aref chr)
{
	chr.chr_ai.charge = "0";
	chr.chr_ai.chargeprc = "1";
}

//Установить скорость заряда пистолета
void LAi_GunSetChargeSpeed(aref chr, float speed)
{
	if(speed < 0.0) speed = 0.0;
	if(speed > 4.0) speed = 4.0;
	chr.chr_ai.charge_dlt = speed;
}

//Установить минимальный урон от пистолета
void LAi_GunSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmggunmin = min;
}

//Установить максимальный урон от пистолета
void LAi_GunSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmggunmax = max;
}

//Установить вероятность попадания на максимальной дальности стрельбы
void LAi_GunSetAccuracy(aref chr, float accuracy)
{
	if(accuracy < 0.0) accuracy = 0.0;
	if(accuracy > 1.0) accuracy = 1.0;
	chr.chr_ai.accuracy = accuracy;
}

//Установить минимальный урон от сабли
void LAi_BladeSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmgbldmin = min;
}

//Установить максимальный урон от сабли
void LAi_BladeSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmgbldmax = max;
}

//Установить вероятность пробивки
void LAi_BladeSetPiercing(aref chr, float piercing)
{
	if(piercing < 0.0) piercing = 0.0;
	if(piercing > 1.0) piercing = 1.0;
	chr.chr_ai.piercing = piercing;
}

//Установить вероятность неблокирования
void LAi_BladeSetBlock(aref chr, float block)
{
	if(block < 0.0) block = 0.0;
	if(block > 1.0) block = 1.0;
	chr.chr_ai.block = block;
}
// тип сабли boal
void LAi_BladeFencingType(aref chr, string FencingType)
{
	chr.chr_ai.FencingType = FencingType;
}

string LAi_GetBladeFencingType(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.FencingType"))
	{
        return chr.chr_ai.FencingType;
    }
    return SKILL_FENCING;
}

void LAi_BladeEnergyType(aref chr, float fEnergyType)
{
	chr.chr_ai.EnergyType = fEnergyType;
}

float LAi_GetBladeEnergyType(aref chr)
{
    if (CheckAttribute(chr, "chr_ai.EnergyType"))
	{
        return stf(chr.chr_ai.EnergyType);
    }
    return 1.0;
}

//------------------------------------------------------------------------------------------
//Internal
//------------------------------------------------------------------------------------------

//Процессируем всех загружекных персонажей
void LAi_AllCharactersUpdate(float dltTime)
{
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			//Персонаж
			aref chr_ai;
			makearef(chr_ai, Characters[idx].chr_ai);
			ref chr = &Characters[idx];
			if(LAi_IsDead(chr)) continue;
			//Востоновление жизни
			float dlthp = LAI_DEFAULT_DLTHP;
			if(CheckAttribute(chr_ai, "hp_dlt")) dlthp = stf(chr_ai.hp_dlt);
			float hp = stf(chr_ai.hp) + dlthp*dltTime;
			float oldhp = hp;
			if(CheckAttribute(chr_ai, "hp_bottle"))
			{
				float bottle = stf(chr_ai.hp_bottle);
				if(bottle > 0)
				{
					//Скорость высасывания из бутылки
					float bottledlthp = LAI_DEFAULT_DLTBLTHP;
					if(CheckAttribute(chr_ai, "hp_dlt_bottle"))
					{
						bottledlthp = stf(chr_ai.hp_dlt_bottle);
					}
					//Количество вытянутых хп за текущий период времени
					bottledlthp = bottledlthp*dltTime;
					if(bottledlthp > bottle)
					{
						bottledlthp = bottle;
					}
					bottle = bottle - bottledlthp;
					hp = hp + bottledlthp;
					chr_ai.hp_bottle = bottle;
				}else{
					//Нет больше бутылки
					DeleteAttribute(chr_ai, "hp_bottle");
					DeleteAttribute(chr_ai, "hp_dlt_bottle");//fix
				}
			}
			if(CheckAttribute(chr_ai, "poison"))
			{
				chr_ai.poison = stf(chr_ai.poison) - dltTime;
				if(stf(chr_ai.poison) <= 0.0)
				{
					DeleteAttribute(chr_ai, "poison");
					UnmarkCharacter(chr);
				}else{
					hp = hp - dltTime*2.0;
					if (!CheckAttribute(chr, "poison.hp") || hp < sti(chr.poison.hp)-1.0)
					{
						chr.poison.hp = hp;
						SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, MakeFloat(MakeInt(chr.chr_ai.hp)), MakeFloat(MakeInt(chr.chr_ai.hp_max)));
					}
				}
			}
			//navy --> время действия бутылки
			if(CheckAttribute(chr_ai, "drunk"))
			{
				chr_ai.drunk = sti(chr_ai.drunk) - 1;
				if(sti(chr_ai.drunk) < 1) LAi_SetAlcoholNormal(chr);
			}
			//<--
			if(CheckAttribute(chr_ai, "blooding"))
			{
				chr_ai.blooding = stf(chr_ai.blooding) - dltTime;
				if(stf(chr_ai.blooding) <= 0.0)
				{
					DeleteAttribute(chr_ai, "blooding");
					UnmarkCharacter(chr);
					if(sti(chr.index) == GetMainCharacterIndex())
					{
						Log_Info("Кровотечение прекратилось.")
					//DelPerkFromActiveList("BloodingPerkA");	// Убираем перк, если кровотечение окончено
					//pchar.questTemp.bloodingperk = "false"; // Анти-баг
					}
				}
				else
				{
					hp = hp - dltTime*1.5*sti(chr_ai.Blooding.Power);
					//hp = hp - dltTime*(MakeFloat(chr.chr_ai.hp_max)/100); // -1 ХП в сек.
					hp = hp - GetCharacterRegenHPForBlooding(chr, false)*dltTime; // Нанесение процентного урона, чем больше хп у цели, чем чаще бьют тики урона
					if (!CheckAttribute(chr, "blooding.hp") || hp < sti(chr.blooding.hp)-1.0)
					{
						chr.blooding.hp = hp;
						// LAi_CharacterPlaySound(chr, "blooddrop"); // LEO: Вырубил нахер. А то крипота какая то была с ёба-звуками.
						LaunchBlood(chr, 1.6, true);
						SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, MakeFloat(MakeInt(chr.chr_ai.hp)), MakeFloat(MakeInt(chr.chr_ai.hp_max)));
					}
				}
			}
			if(CheckAttribute(chr_ai, "understun"))
			{
				chr_ai.understun = stf(chr_ai.understun) - dltTime;
				if(CheckAttribute(chr_ai, "underStun") && stf(chr_ai.understun) <= 0.1)
				{
					DeleteAttribute(chr_ai, "underStun")
					UnmarkCharacter(chr);
					if(sti(chr.index) == GetMainCharacterIndex())
					{
						LAi_SetPlayerType(chr);
						LAi_SetFightMode(chr, true);
					}
					else
					{
						LAi_SetWarriorTypeNoGroup(chr);
						LAi_SetFightMode(chr, true);
					}
				}
			}
			if(CheckAttribute(chr_ai, "swift"))
			{
				chr_ai.swift = stf(chr_ai.swift) - dltTime;
				if(stf(chr_ai.swift) <= 0.0)
				{
					DeleteAttribute(chr_ai, "swift");
					chr_ai.energy = chr_ai.curen;
					DeleteAttribute(chr_ai, "curen");
					UnmarkCharacter(chr);
					if(sti(chr.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы восстановились после резкого удара.")
					//DelPerkFromActiveList("BloodingPerkA");	// Убираем перк, если кровотечение окончено
					//pchar.questTemp.bloodingperk = "false"; // Анти-баг
					}
				}
				else
				{
					chr_ai.energy = 0;
				}
			}
			if(CheckAttribute(chr_ai, "Trauma"))
			{
				chr_ai.Trauma = stf(chr_ai.Trauma) - dltTime;
				if(stf(chr_ai.Trauma) <= 0.0)
				{
					DeleteAttribute(chr_ai, "TraumaQ");
					DeleteAttribute(chr_ai, "Trauma");
					UnmarkCharacter(chr);
					if(sti(chr.index) == GetMainCharacterIndex())
					{
						Log_Info("Травма прошла.")
					//DelPerkFromActiveList("BloodingPerkA");	// Убираем перк, если кровотечение окончено
					//pchar.questTemp.bloodingperk = "false"; // Анти-баг
					}
				}
			}

			if (sti(chr.index) == GetMainCharacterIndex() && !CheckAttribute(pchar, "autofood") && CheckAttribute(pchar, "foodquery"))
			{
				if (!LAi_IsFightMode(pchar) || chr_ai.energy == (LAi_GetCharacterMaxEnergy(chr)))
				{
					if (pchar.foodquery > 0)
					{
						pchar.foodquery = 0;
						Log_Info("Очередь остановлена.");
					}
				}
			}

			if(CheckAttribute(chr_ai, "noeat"))
			{
				if(CheckAttribute(pchar,"query_delay")) 
				{
					pchar.query_delay = stf(pchar.query_delay) - dltTime;
					if (stf(pchar.query_delay) <= 0.0)
					{
						DeleteAttribute(pchar, "query_delay");
					}
				}
				chr_ai.noeat = stf(chr_ai.noeat) - dltTime;
				
				if(stf(chr_ai.noeat) <= 0.0 )
				{
					DeleteAttribute(chr_ai, "noeat");

					if (sti(chr.index) == GetMainCharacterIndex() && !CheckAttribute(pchar, "autofood") && CheckAttribute(pchar, "foodquery"))
					{
						if (!LAi_IsFightMode(pchar) || chr_ai.energy == (LAi_GetCharacterMaxEnergy(chr)))
						{
							if (pchar.foodquery > 0)
							{
								pchar.foodquery = 0;
								Log_Info("Очередь остановлена.");
							}
						}
					}

					//chr_ai.noeat = 0.0;
					if(sti(chr.index) == GetMainCharacterIndex() && !CheckAttribute(pchar, "autofood"))
					{
						if (CheckAttribute(pchar, "foodquery"))
						{
							if (pchar.foodquery == 0)
							{
								Log_Info("Можно кушать.");
							}
							else
							{
									if(!CheckAttribute(pchar, "autofood") && pchar.foodquery > 0)
								{
									pchar.foodquery = sti(pchar.foodquery)-1;
									EatSomeFood();
								}

							}
						}
					//DelPerkFromActiveList("BloodingPerkA");	// Убираем перк, если кровотечение окончено
					//pchar.questTemp.bloodingperk = "false"; // Анти-баг
					}
				}
			}
			if (sti(chr.index) == GetMainCharacterIndex() && CheckAttribute(pchar, "autofood") && !CheckAttribute(chr, "noeat"))
			{
				if(chr_ai.energy < (LAi_GetCharacterMaxEnergy(chr) * (sti(PChar.autofood_use) * 0.01)) && LAi_IsFightMode(pchar))
				{
					//Log_Info("Автоюз.");
					EatSomeFood();
				}
			}
			if(LAi_IsImmortal(chr))
			{
				if(hp < oldhp) hp = oldhp;
			}
			float maxhp = stf(chr_ai.hp_max);
			if(hp > maxhp)
			{
				hp = maxhp;
				DeleteAttribute(chr_ai, "bottle");
			}
			chr_ai.hp = hp;
			//Проверка квеста на hp
			LAi_ProcessCheckMinHP(chr);
			//Проверка на смерть
			LAi_CheckKillCharacter(chr);
			//Востоновление заряда
			float chargemax = 0.0;
			if(CheckAttribute(chr_ai, "charge_max"))
			{
				chargemax = stf(chr_ai.charge_max);
			}
			//if(!CheckAttribute(chr_ai, "chargeprc")) chr_ai.chargeprc = "1";
			if(chargemax > 0.0)
			{
				if(sti(chr_ai.chargeprc))
				{
					// boal 22/07/05 зарядка не в бою. eddy.но если мушкетер, то пофиг
					if (bRechargePistolOnLine || !LAi_IsFightMode(chr) || findsubstr(chr.model.animation, "mushketer" , 0) != -1 || CheckAttribute(chr,"AlwaysReload"))//перезаряд независимо от дозарядки
					{
						float charge = stf(chr_ai.charge);
	                    // boal сюда добавть проверку на наличие пуль gun bullet-->
	                    if((iGetMinPistolChargeNum(chr) - charge) > 0) // Warship. Переделка, т.к. появился порох
		                {
							//zagolski. убираем тормоза при зарядке
							if(!CheckAttribute(chr_ai, "charge_pSkill"))
							{
							//Скорость зарядки
								chr_ai.charge_pSkill = LAi_GunReloadSpeed(chr);
							}

							float dltcharge = stf(chr_ai.charge_pSkill);
							//Подзаряжаем пистолет
							charge = charge + dltcharge*dltTime;
							if(charge >= chargemax)
							{
								charge = chargemax;
								chr_ai.chargeprc = "0";
									DeleteAttribute(chr_ai, "charge_pSkill");
								// boal 24.04.04 озвучка зарядки пистоля -->
									if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
									{
										PlaySound("People Fight\reload1.wav");
									}
							}
							chr_ai.charge = charge;
						}
						// boal сюда добавть проверку на наличие пуль gun bullet <--
					} // boal 22/07/05 зарядка не в бою
				}
			}
			else
			{
				chr_ai.charge = "0";
			}
			//Востоновление энергии
			if(CheckAttribute(chr_ai, "energy"))
			{
				float energy = Lai_UpdateEnergyPerDltTime(chr, stf(chr_ai.energy), dltTime);
				if(energy < 0.0)
				{
					energy = 0.0;
				}
				if(energy > LAi_GetCharacterMaxEnergy(chr))   // boal
				{
					energy = LAi_GetCharacterMaxEnergy(chr);
				}
				chr_ai.energy = energy;
			}
		}
	}
	RefreshChargeTime();
}

void LAi_ProcessCheckMinHP(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.hpchecker"))
	{
		float minhp = stf(chr.chr_ai.hpchecker);
		float hp = stf(chr.chr_ai.hp);
		if(hp < minhp)
		{
			DeleteAttribute(chr,"chr_ai.poison");
			DeleteAttribute(chr,"chr_ai.Blooding");
			if(sti(chr.chr_ai.hpchecker.immortal))
			{
				LAi_SetImmortal(chr, true);
				chr.chr_ai.hp = minhp;
			}
			if(chr.chr_ai.hpchecker.quest != "")
			{
				LAi_QuestDelay(chr.chr_ai.hpchecker.quest, 0.0);
			}
			LAi_RemoveCheckMinHP(chr);
		}
	}
}

void LAi_CharacterSaveAy(aref chr)
{
	float ay = 0.0;
	if(GetCharacterAy(chr, &ay) == false) ay = 0.0;
	chr.chr_ai.type.ay = ay;
}

void LAi_CharacterRestoreAy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.type.ay"))
	{
		float ay = stf(chr.chr_ai.type.ay);
		aref type;
		makearef(type, chr.chr_ai.type);
		DeleteAttribute(type, "ay");
		CharacterTurnAy(chr, ay);
	}
}

//Gregg
float GetCharacterRegenHP(aref chr, bool useItms) // Новая функция расчета регенерации жизни (Rasteador) (ver. 0.3.0)
{
	float fMultiplier = LAi_GetCharacterMaxHP(chr)/450.0; // Внесение процентного урона, в зависимости от макс. кол-ва ХП

	//if(fMultiplier > 2.0) fMultiplier = 2.0; // Лимит

	return fMultiplier;
}

float GetCharacterRegenHPForBlooding(aref chr, bool useItms) // Новая функция расчета регенерации жизни (Rasteador) (ver. 0.3.0)
{
	float fMultiplier = LAi_GetCharacterMaxHP(chr)/100.0; // Внесение процентного урона, в зависимости от макс. кол-ва ХП

	if(fMultiplier > 10.0) fMultiplier = 10.0; // Лимит

	return fMultiplier;
}

int BookTime(ref refchar, int tier)//книги, расчёт длительности - Gregg
{
	int Intel = GetCharacterSPECIALSimple(refchar, SPECIAL_I);
	int time = 0;
	switch (tier)
	{
		case 1: time = 4;
		break;
		case 2: time = 7;
		break;
		case 3: time = 15;
		break;
		case 4: time = 30;
		break;
	}
	return makeint(time+((10-Intel)*(time*0.285)));
}


void EatSomeFood()
{
	bool bEnableFood = true;
	if(CheckAttribute(PChar, "AcademyLand"))
	{
		if(PChar.AcademyLand == "Start")
		{
			bEnableFood = sti(PChar.AcademyLand.Temp.EnableFood);
		}
	}
	if(!bEnableFood)
	{
		Log_SetStringToLog("В данный момент запрещено использовать еду.");
	}
	else
	{
		aref  arItm;
		int   itmIdx;
		String itemID;
		if (!CheckAttribute(pchar, "autofood_betterfood"))
		{
			itmIdx = FindFoodFromChr(pchar, &arItm, 0);
		}
		else
		{
			itmIdx = FindBetterFoodFromChr(pchar, &arItm);
			if (itmIdx == -1)
			{
				itmIdx = FindFoodFromChr(pchar, &arItm, 1);
			}
		}
		while(itmIdx>=0)
		{
			if(EnableFoodUsing(pchar, arItm))
			{
				DoCharacterUsedFood(pchar, arItm.id);
				PlaySound("interface\_Hrust_"+rand(3)+".wav");
				break;
			}
			if (!CheckAttribute(pchar, "autofood_betterfood"))
			{
				itmIdx = FindFoodFromChr(pchar, &arItm, itmIdx+1);
			}
			else
			{
				itmIdx = FindFoodFromChr(pchar, &arItm, itmIdx-1);
				break;
			}
		}
	}

	if (CheckAttribute(pchar, "pressedFoodButton"))
	{
		DeleteAttribute(pchar, "pressedFoodButton");
	}
}

int FindBetterFoodFromChr(ref chref, ref arFind)
{
	int i;
	aref arItm;
	for(i=ITEMS_QUANTITY; i>-1; i--)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"Food") && GetCharacterItem(chref,Items[i].id)>0 )
		{
			arFind = arItm;
			return i;
		}
	}
	return -1;
}
