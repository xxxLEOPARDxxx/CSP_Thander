/*
Тип: игрок

	Используемые шаблоны:
		player
		dialog
*/



#define LAI_TYPE_PLAYER		"player"


//Инициализация
void LAi_type_player_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_PLAYER) isNew = true;
	}
	if(isNew == true)
	{
		//Новый тип
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_PLAYER;
	}
	//Установим шаблон стояния
	LAi_tmpl_player_InitTemplate(chr);
	//Установим анимацию персонажу
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
	//Время стояния с оружием
	chr.chr_ai.type.weapontime = 0;
}

//Процессирование типа персонажа
void LAi_type_player_CharacterUpdate(aref chr, float dltTime)
{
	float time;
	if (CheckAttribute(chr, "showTimer"))
	{
		chr.showTimer = stf(chr.showTimer) - dltTime;
		if (sti(chr.showTimer) <= 0.0)
		{
			DeleteAttribute(chr, "showTimer");
			DoQuestFunctionDelay("LSC_underwaterDeathTimer", 0.1);
		}
		else Log_SetEternalString("" + sti(chr.showTimer));
	}
	if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsActive") != 0)
	{
		chr.chr_ai.type.weapontime = "0";
	}
	if(LAi_group_GetPlayerAlarm())
	{
		chr.chr_ai.type.weapontime = "0";
	}
	if(LAi_IsFightMode(chr))
	{
		time = stf(chr.chr_ai.type.weapontime) + dltTime;
		chr.chr_ai.type.weapontime = time;
		if(time > 300.0)
		{
			chr.chr_ai.type.weapontime = "0";
			SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", false);
		}
	}else{
		chr.chr_ai.type.weapontime = "0";
	}
}

//Загрузка персонажа в локацию
bool LAi_type_player_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_player_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_player_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}

//Сообщить о желании завести диалог
void LAi_type_player_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_player_CanDialog(aref chr, aref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//Если сражаемся, то откажем
	if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsFightMode") != 0) return false;
	//Согласимся на диалог
	return true;
}

//Начать диалог
void LAi_type_player_StartDialog(aref chr, aref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_player_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_player_InitTemplate(chr);
}


//Персонаж выстрелил и в кого-то попал
void LAi_type_player_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
	Log_TestInfo("Выстрелил персонаж с ID - " + attack.id + " и попал в персонажа с ID - " + enemy.id);
	int iCurHP = enemy.chr_ai.hp;
	int iMaxHP = LAi_GetCharacterMaxHP(enemy);
	if(iCurHP > 0 && !LAi_IsImmortal(enemy))
		Log_Info("Осталось здоровья - " + iCurHP + " из " + iMaxHP);
}


//Персонаж атакован
void LAi_type_player_Attacked(aref chr, aref by)
{
}
