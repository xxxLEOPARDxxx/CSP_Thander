/*

	Возможные типы атаки attackType:
	"fast" быстрая атака
	"force" обычная
	"round" круговая
	"break" пробивающая блок
	"feint" атака после финта

*/

//--------------------------------------------------------------------------------
//Blade parameters
//--------------------------------------------------------------------------------

//Расчитать повреждение для персонажа
//#20200522-01
float LAi_CalcDamageForBlade(aref attack, aref enemy, string attackType, bool isBlocked, bool blockSave)
{
	//Расчитываем повреждение от сабли
	float min = 10.0;
	float max = 10.0;
	if(CheckAttribute(attack, "chr_ai.dmgbldmin"))
	{
		min = stf(attack.chr_ai.dmgbldmin);
	}
	if(CheckAttribute(attack, "chr_ai.dmgbldmax"))
	{
		max = stf(attack.chr_ai.dmgbldmax);
	}
	//float bladeDmg = min + frand((max - min));//*(rand(10)*0.1);
	if (findsubstr(attack.model.animation, "mushketer" , 0) != -1)
	{
		min = 10.0;
		max = 20.0;
	}

	float atSkill = LAi_GetCharacterFightLevel(attack);
	string fencing_type = LAi_GetBladeFencingType(attack);
	/*if (CheckAttribute(attack,"chr_ai.Trauma"))
	{
		atSkill = atSkill - 0.25;
		if (atSkill < 0.0) atSkill = 0.01;
	}*/
	if (rand(1)==0) atSkill = atSkill - (rand(5)*0.02);
	else atSkill = atSkill + (rand(5)*0.02);
	if (atSkill<0.0) atSkill *= -1;

	float bladeDmg = min + (max - min)*atSkill);
	//Коэфициент в зависимости от скилов
	float aSkill = LAi_GetCharacterFightLevel(attack);
	float eSkill = LAi_GetCharacterFightLevel(enemy);
	//float kSkillDmg = 1.0;
	//kSkillDmg = 1.0 * (1.0 + (0.3 * aSkill));
    if (aSkill < eSkill)
	{
		bladeDmg = bladeDmg * (1.0 + 0.7 * (aSkill - eSkill));
	}

	// Warship 27.08.09 Для сильных противников
	// Если долбить совсем сильных (хардкорные абордажи), то шансов взять шип будет меньше
	if(sti(enemy.Rank) > 50)
	{
		bladeDmg = bladeDmg * 45 / sti(enemy.Rank);
	}

	if(CheckAttribute(loadedLocation, "CabinType") && sti(enemy.index) == GetMainCharacterIndex())
	{
		bladeDmg = bladeDmg * (1.0 + stf(attack.rank)/100);
	}
	//Коэфициент в зависимости от удара
	float kAttackDmg = 1.0;

	// TO_DO оптимизация на ветку параметров
	//if (sti(attack.index) == GetMainCharacterIndex()) Log_Info(attackType);
	if (bAltBalance)
	{
		switch(attackType)
		{
			case "fast": // быстрая атака
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 0.0;
					}
					else
					{
						kAttackDmg = 0.46;
					}
				}
				else
				{
					kAttackDmg = 0.7;
				}
				if (fencing_type != "Fencing") kAttackDmg *= 0.6;
			break;
			case "force": // обычная атака
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 0.0;
					}
					else
					{
						kAttackDmg = 0.66;
					}
				}
				else
				{
					kAttackDmg = 1.0;
				}
				if (fencing_type != "FencingLight") kAttackDmg *= 0.6;
			break;
			case "round": // круговая атака
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 0.0;
					}
					else
					{
						kAttackDmg = 0.4;
					}
				}
				else
				{
					kAttackDmg = 0.6;
				}
				if(CheckCharacterPerk(attack, "BladeDancer"))
				{
					kAttackDmg = kAttackDmg * 1.3;
				}
				if (fencing_type != "Fencing") kAttackDmg *= 0.6;
				break;
			case "break": // пробивающая блок
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 1.25;
					}
					else
					{
						kAttackDmg = 2.25;
					}
				}
				else
				{
					kAttackDmg = 3.0;
				}
				if (fencing_type != "FencingHeavy") kAttackDmg *= 0.6;
			break;

			case "feintc":  // фикс после изучения ядра //Атакующие продолжение финта
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.8;
				}
				if (fencing_type != "FencingLight") kAttackDmg *= 0.6;
			break;

			case "feint":
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.5;
				}
			break;
		}
	}
	else
	{
		switch(attackType)
		{
			case "fast": // быстрая атака
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 0.0;
					}
					else
					{
						kAttackDmg = 0.46;
					}
				}
				else
				{
					kAttackDmg = 0.7;
				}
			break;
			case "force": // обычная атака
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 0.0;
					}
					else
					{
						kAttackDmg = 0.66;
					}
				}
				else
				{
					kAttackDmg = 1.0;
				}
			break;
			case "round": // круговая атака
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 0.0;
					}
					else
					{
						kAttackDmg = 0.4;
					}
				}
				else
				{
					kAttackDmg = 0.6;
				}
				if(CheckCharacterPerk(attack, "BladeDancer"))
				{
					kAttackDmg = kAttackDmg * 1.3;
				}
				break;
			case "break": // пробивающая блок
				if(isBlocked)
				{
					if(blockSave)
					{
						kAttackDmg = 1.25;
					}
					else
					{
						kAttackDmg = 2.25;
					}
				}
				else
				{
					kAttackDmg = 3.0;
				}
			break;

			case "feintc":  // фикс после изучения ядра //Атакующие продолжение финта
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.8;
				}
			break;

			case "feint":
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.5;
				}
			break;
		}
	}
	if (kAttackDmg > 0)  // оптимизация boal
	{
		if (findsubstr(attack.model.animation, "mushketer" , 0) != -1)
		{
			if (IsEquipCharacterByItem(attack, "mushket_SeaCarbine"))
			{
				if (attackType == "force") kAttackDmg += 1.0;
			}
			if (attackType == "break") kAttackDmg += 1.5;
			if (attackType == "fast") kAttackDmg += 0.5;
		}
		if(CheckCharacterPerk(attack, "Agent"))
		{
			if (attackType == "feintc") kAttackDmg *= 2;
		}
		//Результирующий демедж
		float dmg = bladeDmg * kAttackDmg; // *kArcadeDmg * kSkillDmg
		if(CheckCharacterPerk(attack, "HardHitter"))
		{
			if(CheckAttribute(enemy, "chr_ai.energy"))
			{
				enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.9); //fix
			}
		}
		// упрощение игры новичкам
		if (MOD_SKILL_ENEMY_RATE == 1 && CheckAttribute(enemy, "chr_ai.group"))
		{
			if (enemy.chr_ai.group == LAI_GROUP_PLAYER)
			{
				dmg = dmg / MOD_Complexity_1_DMG;
			}
		}

		//Boyer mod #20170318-33 difficulty level rebalancing
		//if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())
		if (MOD_SKILL_ENEMY_RATE < 10 && sti(enemy.index) == GetMainCharacterIndex())
		{
			dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
		}
		return dmg;
	}
	return 0.0;
}

string RecalculateMushketHitsType(aref attack)
{
	if (IsEquipCharacterByItem(attack, "mushket_SeaCarbine"))
	{
		return "force";
	}
	return "";
}

//Расчитать полученный опыт при ударе саблей
//#20200522-01
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, bool isBlocked,float dmg, bool blockSave)
{
	if (stf(enemy.chr_ai.hp) < dmg)
       dmg = stf(enemy.chr_ai.hp);
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank"))
		ra = 1.0 + 0.5*stf(attack.rank);
	if (CheckAttribute(enemy, "rank"))
		re = 1.0 + 0.5*stf(enemy.rank);
	ra = re/ra;
	if (ra > 3.0)
		ra = 3.0;//обрезание слишком большого множителя. кривые множители тоже решает
	float exp = frandSmall(dmg * ra);//Lipsar передeлка опыта
	// frandSmall на замену эффекта Lipsar-а

	if(attackType == "feintc")
		exp = exp * 1.5;

	return exp;
}

//Энергия, необходимая для запуска действия
float LAi_CalcUseEnergyForBlade(aref character, string actionType)
{
	float energy = 0.0;
	switch(actionType)
	{
		case "fast":
			energy = 10.0;
		break;
		case "force":
			energy = 7.0;
		break;
		case "round":
			energy = 14.0;
		break;
		case "break":
			energy = 25.0;
		break;
		// case "feint":
			// energy = 7.0;
		// break;
		// case "parry":
			// energy = 20.0;
		// break;
		case "hit_parry":  // boal fix эту энергию тратит не атакующий, а атакуемый в анимации fgt_hit_parry
			energy = 20.0;
		break;
		case "feintc":
			energy = 7.0; // расход при успехе финта
		break;
	}
	/*if(CheckCharacterPerk(character, "BladeDancer"))  // to_do
	{
		energy = energy * 0.9;
	}*/
	 // честно все всем
	/*if(character.id == pchar.id || character.chr_ai.group == LAI_GROUP_PLAYER)
	{
		energy = energy * (1.05 - (0.025 * MOD_SKILL_ENEMY_RATE));
	} */
	if (energy > 0.0)  // оптимизация
	{
		float fSkill = LAi_GetCharacterFightLevel(character);  // stf(character.skill.fencing) - не так это далеют!!
		fSkill = (1.0 - (0.3 * fSkill));
		energy = energy * fSkill * LAi_GetBladeEnergyType(character);  // энергоемкость от веса
	}
	return energy;
}

float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime)
{
	float fMultiplier = 1.6666667;

	if(CheckCharacterPerk(chr, "Energaiser")) // скрытый перк боссов и ГГ
	{
		fMultiplier = fMultiplier * 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless"))
	{
		fMultiplier = fMultiplier * 1.15;
	}
	if(CheckAttribute(chr, "bonusEnergy") && chr.index != nMainCharacterIndex)
	{
		fMultiplier = fMultiplier * 2;
	}
    // честно все всем
	/*
	if(chr.id == pchar.id || chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
		fMultiplier = fMultiplier * (1.0 + (0.025 * MOD_SKILL_ENEMY_RATE));
	}
	*/
	float fEnergy;
	fEnergy = curEnergy + dltTime * fMultiplier;

	return fEnergy;
}


//--------------------------------------------------------------------------------
//Gun parameters
//--------------------------------------------------------------------------------

//Расчитаем вероятность попадания
float LAi_GunCalcProbability(aref attack, float kDist)
{
	//Если близко, то попадём точно
	if(kDist >= 0.9) return 1.0;
	//Расчитаем вероятность на конце отрезка
	float pmin = 0.3;
 	if(CheckAttribute(attack, "chr_ai.accuracy")) // boal это меткость самого пистолета, а не скил!
	{
		pmin = stf(attack.chr_ai.accuracy);
	}
 	//Применим разброс от скила
	// boal -->
	float aSkill = LAi_GetCharacterGunLevel(attack);
	// boal <--

	pmin = pmin + 0.3*aSkill;

	//Вероятность попадания в текущей позиции
	float p = pmin + (1.0 - pmin)*(kDist/0.9)+(GetCharacterSPECIALSimple(attack, SPECIAL_P)*0.01);
 	//Учесть абилити
	if(IsCharacterPerkOn(attack, "GunProfessional"))
	{
		p = p + 0.25;
	}else{
		if(IsCharacterPerkOn(attack, "Gunman"))
		{
			p = p + 0.1;
		}
	}
	// путь будет больше 1 - тогда 100 процентов попал
	return p;
}

//Получить повреждение от пистолета
float LAi_GunCalcDamage(aref attack, aref enemy)
{
	//Расчитываем повреждение
	float min = 10.0;
	float max = 10.0;
	if(CheckAttribute(attack, "chr_ai.dmggunmin"))
	{
		min = stf(attack.chr_ai.dmggunmin);
	}
	if(CheckAttribute(attack, "chr_ai.dmggunmax"))
	{
		max = stf(attack.chr_ai.dmggunmax);
	}
	string sBullet = LAi_GetCharacterBulletType(attack);
	if(sBullet == "powder_pellet") LaunchBlastPellet(enemy);
	if(sBullet == "grenade") LaunchBlastGrenade(enemy);
	if(CheckAttribute(enemy, "cirassId"))
	{
		min = stf(attack.chr_ai.DmgMin_C);
		max = stf(attack.chr_ai.DmgMax_C);

		if(stf(attack.chr_ai.EnergyP_C) > 0.0 )
		{
			if(sBullet == "powder_pellet")
			{
				if(enemy.chr_ai.group != LAI_GROUP_PLAYER) Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.EnergyP_C));
			}
		}
	}
	else
	{
		min = stf(attack.chr_ai.DmgMin_NC);
		max = stf(attack.chr_ai.DmgMax_NC);

		if(stf(attack.chr_ai.EnergyP_NC) > 0.0)
		{
			if(sBullet == "powder_pellet")
			{
				if(enemy.chr_ai.group != LAI_GROUP_PLAYER) Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.EnergyP_C));
			}
		}
	}
	//Учитываем скилы
	float aSkill = LAi_GetCharacterGunLevel(attack);
	float eSkill = LAi_GetCharacterLuckLevel(enemy); // good luck

	float dmg = min + (max - min)*frandSmall(aSkill);
	//Модифицировать повреждение от pistol с учетом скилов
    if(aSkill < eSkill)
	{
		dmg = dmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	// упрощение игры новичкам
	if (MOD_SKILL_ENEMY_RATE == 1 && CheckAttribute(enemy, "chr_ai.group"))
	{
		if (enemy.chr_ai.group == LAI_GROUP_PLAYER)
		{
			dmg = dmg * MOD_Complexity_1_DMG;
		}
	}
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	//if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())
	if (MOD_SKILL_ENEMY_RATE < 10 && sti(enemy.index) == GetMainCharacterIndex())
	{
		dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
	}
	if(CheckCharacterPerk(attack, "Buccaneer"))
	{
		if(CheckAttribute(enemy, "chr_ai.energy"))
		{
			enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.65); //fix
		}
	}
	return dmg;
}

//Расчитать полученный опыт при попадании из пистолета
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
	if (stf(enemy.chr_ai.hp) < dmg)
       dmg = stf(enemy.chr_ai.hp);
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank"))
		ra = 1.0 + 0.5*stf(attack.rank);
	if (CheckAttribute(enemy, "rank"))
		re = 1.0 + 0.5*stf(enemy.rank);
	ra = re/ra;
	if (ra > 3.0)
		ra = 3.0;//обрезание слишком большого множителя. кривые множители тоже решает
	dmg = frandSmall(dmg * ra);//Lipsar передeлка опыта
	// frandSmall на замену эффекта Lipsar-а
	if(bRechargePistolOnLine || findsubstr(attack.model.animation, "mushketer" , 0) != -1)
		{}
	else
		dmg *= 2;
	return dmg;
}

//Расчитаем текущую скорость перезарядки пистолета
float LAi_GunReloadSpeed(aref chr)
{
	//Получим текущее состояние скорости зарядки
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if(CheckAttribute(chr, "chr_ai.charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.charge_dlt);
	}
	//Модифицируем скилом
	// boal -->
	//float skill = LAi_GetCharacterFightLevel(chr);
	float skill = LAi_GetCharacterGunLevel(chr);
	// boal <--

	charge_dlt = charge_dlt*(1.0 + 0.3*skill);//boal
	//УчтЈм абилити
	if(IsCharacterPerkOn(chr, "GunProfessional"))
	{
		if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.5;
		else charge_dlt = charge_dlt*1.25;
	}
	else
	{
		if(IsCharacterPerkOn(chr, "Gunman"))
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.35;
			else charge_dlt = charge_dlt*1.1;
		}
		else
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.25;
		}
	}
	return charge_dlt;
}

//--------------------------------------------------------------------------------
//All
//--------------------------------------------------------------------------------

/*float LAi_CalcDeadExp(aref attack, aref enemy)
{
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	float dmg = (0.5 + 4.0*LAi_GetCharacterFightLevel(enemy))*LAi_GetCharacterMaxHP(enemy);
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));
	return dmg*0.5;
} */

//--------------------------------------------------------------------------------
//Calculate total
//--------------------------------------------------------------------------------

//Начисление повреждений при атаке мечём
//#20200522-01
void LAi_ApplyCharacterAttackDamage(aref attack, aref enemy, string attackType, bool isBlocked, bool blockSave)
{
	if(IsCharacterPerkOn(enemy, "Fencer") && rand(9)==1)  {Log_Info("Избежал удара!"); return;}
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	string fencing_type = LAi_GetBladeFencingType(attack);
	float coeff = 0.0;

	int valueCrB = sti(attack.chr_ai.special.valueCrB);

	/*switch (fencing_type) старый расчёт чистого стата без учёта бонусов. Ниже с учётом - Gregg
	{
		case "FencingLight": coeff = makefloat(attack.Skill.FencingLight)/20; break;
		case "Fencing": coeff = makefloat(attack.Skill.Fencing)/20; break;
		case "FencingHeavy": coeff = makefloat(attack.Skill.FencingHeavy)/20; break;
	}*/
	//--->Пробитие блоков - Gregg
	if (isBlocked && blockSave)
	{
		if (fencing_type == "FencingHeavy") blockSave = CheckForBlockBreak(attack,enemy,true);
		else blockSave = CheckForBlockBreak(attack,enemy,false);
	}
	//<---Пробитие блоков тяжёлым оружием
	//Вычисляем повреждение
	float dmg = LAi_CalcDamageForBlade(attack, enemy, attackType, isBlocked, blockSave);
	float critical = 0.0;
	int critchance = 0;
	if (IsCharacterPerkOn(attack, "SwordplayProfessional")) critchance += 10;
	if (IsCharacterPerkOn(attack, "CriticalHit")) critchance += 5;
	if (IsCharacterPerkOn(attack, "Fencer")) critchance += 5;
	if (valueCrB != 0) critchance += valueCrB;//доп крит
	if(IsCharacterPerkOn(attack, "Agent") && attackType == "feint")
	{
		if (rand(99 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= critchance+33) critical = 1.0;
	}
	if (critchance > 0 && rand(99 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= critchance) critical = 1.0;
	/*if(IsCharacterPerkOn(attack, "SwordplayProfessional"))
	{
		if(IsCharacterPerkOn(attack, "Fencer"))
		{
			if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 20)
			{
				critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.30;
			}
		}
		else
		{
			if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 15)
			{
				critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.30;
			}
		}
	}
	else
	{
		if(IsCharacterPerkOn(attack, "CriticalHit"))
		{
			if(IsCharacterPerkOn(attack, "Fencer"))
			{
				if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 10)
				{
					critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
				}
			}
			else
			{
				if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 5)
				{
					critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
				}
			}
		}
		else
		{
			if(IsCharacterPerkOn(attack, "Fencer"))
			{
				if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 5)
				{
					critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
				}
			}
		}
	}*/
	float kDmg = 1.0;
	if(IsCharacterPerkOn(attack, "Rush"))
	{
		kDmg = 2.0;
	}
	float kDmgRush = 1.0;
	if(IsCharacterPerkOn(enemy, "Rush"))
	{
		kDmgRush = 0.5;
	}
	dmg = dmg*kDmg*kDmgRush;
	//Атака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group") && CheckAttribute(enemy, "chr_ai.group"))
	{
		if(attack.chr_ai.group == enemy.chr_ai.group)
		{
			return;
			//dmg = 0.0;
			//critical = 0.0;
			//noExp = true;
		}
	}
	bool cirign = false;
	if (!blockSave && !isBlocked && dmg > 0.0)
	{
		switch (fencing_type)
		{
			case "FencingLight":
				//--->Функционал лёгкого оружия - Gregg
				CheckForBlooding(attack,enemy,true,attackType);
				CheckForSwift(attack,enemy,false);
				CheckForStun(attack,enemy);
				cirign = CheckForCirassBreak(attack,enemy,false);
				//<---Функционал лёгкого оружия
			break;
			case "Fencing":
				//--->Функционал среднего оружия - Gregg
				CheckForBlooding(attack,enemy,false,attackType);
				CheckForSwift(attack,enemy,true);
				CheckForStun(attack,enemy);
				cirign = CheckForCirassBreak(attack,enemy,false);
				//<---Функционал среднего оружия - Gregg
			break;
			case "FencingHeavy":
				//--->Функционал тяжёлого оружия - Gregg
				CheckForBlooding(attack,enemy,false,attackType);
				CheckForSwift(attack,enemy,false);
				CheckForStun(attack,enemy);
				CheckForTrauma(attack,enemy);
				cirign = CheckForCirassBreak(attack,enemy,true);
				//<--- Функционал тяжёлого оружия - Gregg
			break;
		}
	}
	else
    {
        if(HasSubStr(attack.equip.blade, "katar") && rand(19)==0)//Поломка катаром оружий - Gregg
        {
            string weaponID = GetCharacterEquipByGroup(enemy, BLADE_ITEM_TYPE);
            aref weapon;
            Items_FindItem(weaponID, &weapon);
            if(weapon.model != "unarmed" && weapon.quality != "excellent") //Не отличное и не безоружный
            {
                if(GetCharacterItem(enemy, weaponID) <= 1) RemoveCharacterEquip(enemy, weapon.groupID);
                TakeItemFromCharacter(enemy, weaponID);
                string sEquipItem = GetGeneratedItem("unarmed");
                AddItems(enemy, sEquipItem, 1);
                EquipCharacterbyItem(enemy, sEquipItem);
                if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Оружие противника было сломано.");
					PlaySound("interface\Crash_"+rand(2)+".wav");
				}
				else
				{
					Log_Info("Ваше оружие было сломано.");
					PlaySound("interface\Crash_"+rand(2)+".wav");
				}
            }
        }
        critical = 0;
    }

	if(CheckAttribute(enemy, "cirassId") && !cirign && critical > 0.0)// защиты от критов у кирас
	{
		string cirasstype = enemy.cirassId;
		switch (Items[sti(cirasstype)].id)
		{
			case "suit_1": break;
			case "suit_2": break;
			case "suit_3": break;
			case "cirass1": if (rand(9)<4) critical = 0.0; break;
			case "cirass2": if (rand(9)<6) critical = 0.0; break;
			case "cirass3": if (rand(1)==0) critical = 0.0; break;
			case "cirass4": if (rand(4)>0) critical = 0.0; break;
			case "cirass5": critical = 0.0; break;
		}
		if (critical == 0.0)
		{
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Критический удар был предотвращен!");
			}
			else
			{
				Log_TestInfo(""+enemy.Name+" заблокировал крит!");
			}
		}
	}
	if(critical > 0.0)
	{
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
		critical += GetCharacterSPECIALSimple(attack, SPECIAL_L)*0.05;//бонусный урон крита от удачи
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			Log_SetStringToLog(XI_ConvertString("Critical Hit"));
			Log_TestInfo(" " + critical + " хитов");

			pchar.questTemp.criticalcount = sti(pchar.questTemp.criticalcount) + 1;

			// Открываем достижения
			if(sti(pchar.questTemp.criticalcount) >= 100) UnlockAchievement("criticals", 1);
			if(sti(pchar.questTemp.criticalcount) >= 250) UnlockAchievement("criticals", 2);
			if(sti(pchar.questTemp.criticalcount) >= 500) UnlockAchievement("criticals", 3);
		}
	}
	kDmg = 1.0;
	if(IsCharacterPerkOn(enemy, "BasicDefense")) kDmg = 0.9;
	if(IsCharacterPerkOn(enemy, "AdvancedDefense")) kDmg = 0.8;
	if(IsCharacterPerkOn(enemy, "SwordplayProfessional")) kDmg = 0.7;
	if(IsEquipCharacterByArtefact(enemy, "talisman9") && CheckAttribute(attack,"sex") && attack.sex == "skeleton") kDmg -= 0.33;

	// ГПК 1.2.3
	dmg = dmg*kDmg;
	if (dmg < 1) return;
	dmg = dmg *(1 + critical);//dmg + critical;
	if(CheckAttribute(enemy, "cirassId") && !cirign)//сопротивления уронам у кирас
	{
		if (CheckAttribute(Items[sti(enemy.cirassId)],"CirassLevel.fast"))
		{
			switch (attackType)
			{
				case "fast": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.fast)); break;
				case "force": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.force)); break;
				case "round": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.round)); break;
				case "break": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.break)); break;
				case "feint": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.feint)); break;
			}
		}
	}
	//Наносим повреждение
	if (IsEquipCharacterByArtefact(attack, "talisman1")) dmg *= 1.1; //Пернатый Змей
	if(IsCharacterPerkOn(attack, "Grunt")) dmg *= 1.15; //Рубака
	if(CheckAttribute(attack, "StrangeElixir")) dmg *= 1.1; //Убойная смесь
	if(IsEquipCharacterByArtefact(attack, "talisman9") && CheckAttribute(enemy,"sex") && enemy.sex == "skeleton") dmg *= 1.33;
	//Начисляем опыт - ДО нанесения урона
	float exp = LAi_CalcExperienceForBlade(attack, enemy, attackType, isBlocked, dmg, blockSave);
	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
	/*if(!IsCharacterPerkOn(attack, "Grunt"))
	{
		if(IsEquipCharacterByArtefact(attack, "talisman1"))	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg/10) + 0.5));//Пернатый Змей
		else  LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
	}
	else
	{
		if(IsEquipCharacterByArtefact(attack, "talisman1"))	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg/10)+(dmg*0.15) + 0.5));//Пернатый Змей
		else  LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg*0.15) + 0.5));
	}*/
	//Проверим на смерть
	LAi_CheckKillCharacter(enemy);
	//проверим на отравление
	MakePoisonAttackCheckSex(enemy, attack);
	//Есть ли оружие у цели
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	if (CheckAttribute(attack,"vampire"))
	{
		float hp = attack.chr_ai.hp;
		float maxhp = attack.chr_ai.hp_max;
		float hpup = dmg/2;
		log_Testinfo(FloatToString(hpup,2));
		if (hp+hpup >= maxhp) attack.chr_ai.hp = maxhp;
		else attack.chr_ai.hp = hp + hpup;

		SendMessage(attack, "lfff", MSG_CHARACTER_VIEWDAMAGE, hpup, MakeFloat(attack.chr_ai.hp), MakeFloat(attack.chr_ai.hp_max));
	}
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	} */
	if(LAi_IsDead(enemy) && isSetBalde)
	{
		//Начислим за убийство
		//exp = exp + LAi_CalcDeadExp(attack, enemy);
		//exp = LAi_GetCharacterMaxHP(enemy) * 10;
		//noExp = false;
		//DoCharacterKilledStatistics(sti(attack.index), sti(enemy.index));
		/*if(!isSetBalde)
		{
			//LAi_ChangeReputation(attack, -3);
		}*/
		// boal  check skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
		if (stf(enemy.rank) < 4) int experience = GetCharacterSPECIALSimple(attack, SPECIAL_I) + rand(GetCharacterSPECIALSimple(attack, SPECIAL_A));
		else experience = Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_I) * re / ra;;//Lipsar передeлка опыта
		AddCharacterExpToSkill(attack, fencing_type, experience);
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 1);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_s");
        // boal statistic info 17.12.2003 <--
        LAi_SetResultOfDeath(attack, enemy, isSetBalde);
	}
	if(!isSetBalde)
	{
		exp = 0.0;
	}

	if (!noExp)
    {
        //AddCharacterExp(attack, MakeInt(exp*0.5 + 0.5));
        AddCharacterExpToSkill(attack, fencing_type, Makefloat(exp*0.2));
    }

}

void CheckForBlooding(ref attack, ref enemy, bool type, string attackType)
{
	int valueB = sti(attack.chr_ai.special.valueB);
	if (type)
	{
		/*if (HasSubStr(attack.equip.blade, "blade32") && 12.5+valueB+coeff>rand(99))//фламберж
		{
			if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator")
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы вызвали кровотечение.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
					pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Вам нанесли кровоточащую рану.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
				}
				MakeBloodingAttack(enemy, attack, coeff);
			}
		}
		if (!HasSubStr(attack.equip.blade, "blade32") && attackType == "force")//выпад*/
		if (attackType == "force")//выпад
		{
			float coeff = makefloat(GetCharacterSkillSimple(attack,"FencingLight"))/20;
			if ((2.5+valueB+coeff)*10>rand(999))
			{
				if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы вызвали кровотечение.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						if(IsEquipCharacterByArtefact(enemy, "talisman9") && rand(9)>0) {log_info("Кровотечение предотвращено.") return;}
						Log_Info("Вам нанесли кровоточащую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					MakeBloodingAttack(enemy, attack, coeff);
				}
				else
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы нанесли глубокую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Вам нанесли глубокую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(coeff*2)));
				}
			}
		}
	}
	else
	{
		if (valueB != 0)
		{
			if (valueB>rand(99))
			{
				if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы вызвали кровотечение.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						if(IsEquipCharacterByArtefact(enemy, "talisman9") && rand(9)>0) {log_info("Кровотечение предотвращено.") return;}
						Log_Info("Вам нанесли кровоточащую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					MakeBloodingAttack(enemy, attack, 3.0);
				}
				else
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы нанесли глубокую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Вам нанесли глубокую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(valueB*2)));
				}
			}
		}
	}
}

void CheckForSwift(ref attack, ref enemy, bool type)
{
	int valueSS = sti(attack.chr_ai.special.valueSS);
	if (type)
	{
		float coeff = makefloat(GetCharacterSkillSimple(attack,"Fencing"))/20;
		if ((2.5+valueSS+coeff)*10>rand(999))
		{
			if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы нанесли резкий удар.");
					PlaySound("interface\Stan_"+rand(5)+".wav");
					pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Вам был нанесён резкий удар.");
					PlaySound("interface\Stan_"+rand(5)+".wav");
				}
				MakeSwiftAttack(enemy, attack, coeff);
			}
			else
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы нанесли глубокую рану.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
					pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Вам нанесли глубокую рану.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
				}
				LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(coeff*4)));
			}
		}
	}
	else
	{
		if (valueSS != 0)
		{
			if (valueSS>rand(99))
			{
				if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы нанесли резкий удар.");
						PlaySound("interface\Stan_"+rand(5)+".wav");
						pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Вам нанесён резкий удар.");
						PlaySound("interface\Stan_"+rand(5)+".wav");
					}
					MakeSwiftAttack(enemy, attack, 3.0);
				}
				else
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы нанесли глубокую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Вам нанесли глубокую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(valueSS*2)));
				}
			}
		}
	}
}

void CheckForStun(ref attack, ref enemy)
{
	int valueStS = sti(attack.chr_ai.special.valueStS);
	if (valueStS != 0)
	{
		if (rand(99)<valueStS)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Удар оглушил противника.");
				PlaySound("interface\Stan_"+rand(5)+".wav");
				pchar.questTemp.stuncount = sti(pchar.questTemp.stuncount) + 1;
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Вас оглушили!");
				PlaySound("interface\Stan_"+rand(5)+".wav");
			}
			MushketStun(enemy);
		}
	}
}

void CheckForTrauma(ref attack, ref enemy)
{
	int valueT = sti(attack.chr_ai.special.valueT);
	if (valueT != 0)
	{
		if (rand(99)<valueT)
		{
			if (CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_") && rand(6)<1) return;

			if (!CheckAttribute(enemy,"chr_ai.TraumaQ")) enemy.chr_ai.TraumaQ = 1;
			else enemy.chr_ai.TraumaQ = sti(enemy.chr_ai.TraumaQ)+1;
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Вы травмировали противника.");
				PlaySound("interface\HrustBones_"+rand(2)+".wav");
				pchar.questTemp.traumacount = sti(pchar.questTemp.traumacount) + 1;
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Вы получили травму.");
				PlaySound("interface\HrustBones_"+rand(2)+".wav");
				if (CheckAttribute(enemy,"chr_ai.TraumaQ") && sti(enemy.chr_ai.TraumaQ)>2)
				{
					Log_Info("Вы получили тяжелую травму");
					enemy.chr_ai.HeavyTrauma = 2;
					SetNoRun(enemy);
				}
			}
			MakeTraumaAttack(enemy, attack);
		}
	}
}

bool CheckForBlockBreak(ref attack, ref enemy, bool type)
{
	bool blockSave = true;
	int valueBB = sti(attack.chr_ai.special.valueBB);
	if (type)
	{
		float coeff = makefloat(GetCharacterSkillSimple(attack,"FencingHeavy"))/20;
		if (HasSubStr(attack.equip.blade, "topor") && rand(99)<8.0+(coeff*2.0)+valueBB) //15+%
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Пробитие блока.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Ваш блок пробит.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			blockSave = false;
		}
		if (!HasSubStr(attack.equip.blade, "topor") && rand(99)<5.0+(coeff*2.0)+valueBB) //10+%
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Пробитие блока.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Ваш блок пробит.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			blockSave = false;
		}
	}
	else
	{
		if (valueBB != 0)
		{
			if (rand(99)<valueBB)
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Пробитие блока.");
					PlaySound("interface\Block_"+rand(1)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Ваш блок пробит.");
					PlaySound("interface\Block_"+rand(1)+".wav");
				}
				blockSave = false
			}
		}
	}
	return blockSave;
}

bool CheckForCirassBreak(ref attack, ref enemy, bool type)
{
	int valueCB = sti(attack.chr_ai.special.valueCB);
	bool cirign = false;
	if (type)
	{
		float coeff = makefloat(GetCharacterSkillSimple(attack,"FencingHeavy"))/20;
		if (CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))
		{
			if (HasSubStr(attack.equip.blade, "topor") && rand(99)<8.0+valueCB+(coeff*2.0)) //15%
			{
				cirign = true;
				// Log_TestInfo("топор");
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы пробили кирасу.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Ваша кираса была пробита.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
			}
			if (!HasSubStr(attack.equip.blade, "topor") && rand(99)<5.0+valueCB+(coeff*2.0)) //10%
			{
				cirign = true;
				// Log_TestInfo("тяж");
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы пробили кирасу.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Ваша кираса была пробита.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
			}
		}
	}
	else
	{
		if (valueCB != 0)
		{
			if (CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))
			{
				if (rand(99)<valueCB)
				{
					cirign = true;
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы пробили кирасу.");
						PlaySound("interface\Breaking_"+rand(5)+".wav");
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Ваша кираса была пробита.");
						PlaySound("interface\Breaking_"+rand(5)+".wav");
					}
				}
			}
		}
	}
	return cirign;
}

//boal 19.09.05 -->
void LAi_SetResultOfDeath(ref attack, ref enemy, bool isSetBalde)
{
    if (sti(attack.index) == GetMainCharacterIndex())
    {
		if (GetRelation2BaseNation(sti(enemy.nation)) == RELATION_ENEMY)
		{
			if (!isSetBalde)
			{
				LAi_ChangeReputation(attack, -1);   // to_do
				if (rand(1) && CheckAttribute(enemy, "City"))
				{
					ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 1);
				}
			}
		}
		else
		{
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 2);
			}
		}
		// обида нации на разборки в городе boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// нужна проверка на дуэли и квесты
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // скрытность
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
	}
}
// boal <--

//Начисление повреждений при попадании
void LAi_ApplyCharacterFireDamage(aref attack, aref enemy, float kDist)
{
	Lai_CharacterChangeEnergy(attack, -4); // жрем энергию за выстрел boal 20/06/06
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//Вероятность поподания
	float p = LAi_GunCalcProbability(attack, kDist);
	//Если промахнулись, то выйдем
	if(rand(10000) > p*10000)
	{
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			string missed = "";
			switch (rand(4))
			{
				case 0: missed = "Промах!"; break;
				case 1: missed = "Мазила!"; break;
				case 2: missed = "Целься лучше!"; break;
				case 3: missed = "Да прицелься уже!"; break;
				case 4: missed = "Не попал!"; break;
			}
			Log_Info(missed);
		}
		return;
	}
	string sBullet = LAi_GetCharacterBulletType(attack);
	bool ignore = false;
	if(sBullet == "powder_pellet") ignore = true;
	if(sBullet == "grenade") ignore = true;
	if(CheckCharacterPerk(enemy, "AgileMan"))
	{
		if (rand(3)==0 && !ignore)
		{
			Log_Info("Уклонился от выстрела!")
			return;
		}
	}
	// boal брон работает всегда, а не токо в блоке 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId")&& !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))
	{
		if (CheckCharacterPerk(attack,"Buccaneer") || ignore) {}
		else
		{
			if(rand(1000) < stf(Items[sti(enemy.cirassId)].CirassLevel)*500)
			{
				if(sti(enemy.index) == GetMainCharacterIndex()) Log_Info("Ваша кираса заблокировала урон от выстрела.");
				return;
			}
		}
	}

	// boal 23.05.2004 <--
	//Начисляем повреждение
	float damage = LAi_GunCalcDamage(attack, enemy);
	if (attack.chr_ai.sgun == "pistol_grapebok") damage *= 2;

	//Аттака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group"))
	{
		if(CheckAttribute(enemy, "chr_ai.group"))
		{
			if(attack.chr_ai.group == enemy.chr_ai.group)
			{
				damage = 0.0;
				noExp = true;
			}
		}
	}
	if (HasSubStr(attack.equip.gun, "mushket")) //Мушкетное оглушение - Gregg
	{
		if (damage > 0 && rand(1)==0)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Выстрел из мушкета оглушил противника.");
				//PlaySound("interface\Breaking_"+rand(5)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Вас оглушили выстрелом из мушкета.");
				//PlaySound("interface\Breaking_"+rand(5)+".wav");
			}
			MushketStun(enemy);
		}
	}
	if(CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))//не учитываем костюмы
	{
		if (CheckCharacterPerk(attack,"Buccaneer") && rand(2)>0)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Кираса противника была пробита выстрелом");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Ваша кираса была пробита выстрелом противника");
			}
		}
		else
		{
			if (!ignore)
			{
				damage = damage * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel));
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Урон от выстрела был снижен кирасой");
				}
			}
		}
	}
	if(damage > 0.0)
	{
		//Начисляем опыт
		float exp = LAi_GunCalcExperience(attack, enemy, damage);
		if(IsEquipCharacterByArtefact(attack, "talisman1"))
		{
			if (rand(4)==0)	{LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)*2); Log_Info("Критический выстрел");}
			else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)+25);
		}
		else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5));

		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
	}
	//Есть ли оружие у цели
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	}  */
	if(LAi_IsDead(enemy) && isSetBalde)
	{
		//Начислим за убийство
		//exp = exp + LAi_CalcDeadExp(attack, enemy);
		//exp = LAi_GetCharacterMaxHP(enemy) * 10;
		//noExp = false;
		//if(!isSetBalde)
		//{
			//LAi_ChangeReputation(attack, -3);
		//	exp = 0.0;
		//}
		//DoCharacterKilledStatistics(sti(attack.index), sti(enemy.index));
		// boal skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
		if (stf(enemy.rank) < 4) int experience = GetCharacterSPECIALSimple(attack, SPECIAL_P) + rand(GetCharacterSPECIALSimple(attack, SPECIAL_I));
		else experience = Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_P) * re / ra;//Lipsar передeлка опыта
		AddCharacterExpToSkill(attack, SKILL_PISTOL, experience);
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
		// boal skill <--
		// boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_g");
        // boal statistic info 17.12.2003 <--

        //Начислим за убийство
		/*exp = exp + */
        //LAi_CalcDeadExp(attack, enemy); // начисляем только за удар и смерть
  		LAi_SetResultOfDeath(attack, enemy, isSetBalde);
	}
	if(sBullet == "grapeshot")
		exp *= 2;
	if(!isSetBalde)
	{
		//LAi_ChangeReputation(attack, -1);
		exp = 0.0;
	}

	if(!noExp)
    {
        AddCharacterExpToSkill(attack, SKILL_PISTOL, MakeFloat(exp*0.25));
    }
}

void SetBack()
{

}

//--------------------------------------------------------------------------------
//Параметры NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//Атаки
//Скорость нарастания вероятности атаки в секунду  p > 0
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.7;
	npc_return_tmp = npc_return_tmp + 0.1;
	return npc_return_tmp;
}

//Вес выбора удара "fast", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFast","LAi_NPC_GetAttackWeightFast");
float LAi_NPC_GetAttackWeightFast()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "Fencing")
	{
		npc_return_tmp = npc_return_tmp * 10 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 0.5 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//Вес выбора удара "force", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightForce", "LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 50.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "FencingLight")
	{
		npc_return_tmp = npc_return_tmp * 10 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 0.5 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//Вес выбора удара "round", 0 - никогда не выбирать, если врагов <3 то удар не выбирается
#event_handler("NPC_Event_GetAttackWeightRound", "LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "FencingLight")
	{
		npc_return_tmp = npc_return_tmp * 2 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//Вес выбора удара "break", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightBreak", "LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	if (LAi_GetBladeEnergyType(chr) == "FencingHeavy")
	{
		npc_return_tmp = npc_return_tmp * 6 * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 0.5 * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	}
	return npc_return_tmp;
}

//Вес выбора удара "feint", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFeint", "LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Прараметры защиты
//Вероятность желания защитится - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceActive", "LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	if (LAi_GetBladeFencingType(pchar) == "FencingHeavy")

	{
		npc_return_tmp = 1 + level * 0.35;
		return npc_return_tmp;
	}
	else
	{
		npc_return_tmp = 0.35 + level * 0.35;
		return npc_return_tmp;
	}
}

// boal 20.01.08 коммент - забавно, что спустя два года, понал как и что с вероятностями. Они все приводятся к 0-1 от веса общей суммы, то есть фактически умножение на сложность или цифры распределяют сумму по другим акшенам, а не усиливают этот
// Экшены идут парами - все атаки и защита (блок + пари)
//Вес выбора блока, 0 - никогда не выбирать
#event_handler("NPC_Event_GetDefenceWeightBlock", "LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	if (LAi_GetBladeFencingType(pchar) == "FencingHeavy")
	{
		npc_return_tmp = 8.0;
	}
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора  паррирования, 0 - никогда не выбирать
//кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0; // 40 boal
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Разрешён ли отскок
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}


//Параметры стрельбы

//Shot through allies
#event_handler("NPC_Event_ShotEnemyTest", "LAi_NPC_ShotEnemyTest");
bool LAi_NPC_ShotEnemyTest()
{
	npc_return_tmpb = false;
	if(LAi_IsFightMode(pchar)) npc_return_tmpb = true;
	return npc_return_tmpb;
}

//Вероятность желания выстрелить - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.001 + level*0.06;
	// boal наши офицеры пулят из всех стволов -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
        npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal наши офицеры пулят из всех стволов <--
		if (CheckAttribute(chr, "SuperShooter"))
		{
			npc_return_tmp = npc_return_tmp + 0.4 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
		else
		{
			npc_return_tmp = npc_return_tmp + 0.1 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
	}
	//if (npc_return_tmp > 0.5) npc_return_tmp = 0.5;

	return npc_return_tmp;
}

//Разрешён ли выстрел
#event_handler("NPC_Event_EnableFire","LAi_NPC_EnableFire");
bool LAi_NPC_EnableFire()
{
	aref chr = GetEventData();
	return   true;
	/*float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmpb = false;
	if(!iArcadeFencingAI)
	{
		level = level + 0.02;
	}
	else
	{
		level = level - 0.01;
	}
	if(level > 0.1) npc_return_tmpb = true;
	return npc_return_tmpb;    */
}

//Разрещён ли временный перевыбор цели среди ближних - опрашивается постоянно
#event_handler("NPC_Event_AdaptiveTargetSelect","LAi_NPC_AdaptiveTargetSelect");
bool LAi_NPC_AdaptiveTargetSelect()
{
	aref chr = GetEventData();
	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		npc_return_tmpb = false;
	}else{
		npc_return_tmpb = true;
	}
	return npc_return_tmpb;
}


//--------------------------------------------------------------------------------
//Work
//--------------------------------------------------------------------------------

#event_handler("Location_CharacterSGFire","LAi_Location_CharacterSGFire");
void LAi_Location_CharacterSGFire()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDmg = GetEventData();
	if(LAi_IsDead(enemy)) return;
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//AddCharacterExp(attack, 100*kDmg);
	//Наносим повреждение
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg));
	//Проверим на смерть
	LAi_CheckKillCharacter(enemy);
}

#event_handler("ChrAttackAction", "LAi_ChrAttackAction");
bool LAi_ChrAttackAction()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float curEnergy = Lai_CharacterGetEnergy(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	if(curEnergy >= needEnergy)
	{
		npc_return_tmpb = true;
	}
	else
	{
		npc_return_tmpb = false;
	}
	return npc_return_tmpb;
}
//#20200510-03
#event_handler("Event_ChrFeint_Init", "LAi_BlockInitTime");
#event_handler("Event_ChrBlock_Init", "LAi_BlockInitTime");
#event_handler("Event_ChrParry_Init", "LAi_BlockInitTime");
void LAi_BlockInitTime()
{
	aref chr = GetEventData();
	float fSet = GetEventData();
	chr.chr_ai.BlockInitTime = fSet;
}

#event_handler("ChrFgtActApply", "LAi_ChrFightActionApply");
void LAi_ChrFightActionApply()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	Lai_CharacterChangeEnergy(attack, -needEnergy);
}

//Получить относительную затрачиваемую энергию
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение жизни
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}


//Необходимо вернуть максимально быстро нормализованое значение энергии
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}
