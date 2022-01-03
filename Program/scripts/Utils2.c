// велосипеды

// метод форсит убирание сабли
void SM_HideWeapon(string qName)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
}

// узнать расстояние между двумя персами на локации (в ярдах кажется)
float SM_GetCharactersDistance(ref ch1, ref ch2)
{
	float dst;
	GetCharacterDistByChr(ch1, ch2, &dst);
	return dst;
}

// прикинуть время, требующееся неписи, чтоб добежать до заданного перса
float SM_GetRunTime(ref ch1, ref ch2)
{
	return SM_GetCharactersDistance(ch1, ch2) / 5; // на 20 ярдов около 4 сек в среднем :)
}

// конвертор часов в интенсивность освещения (2 часа ночи - самый черный час, интенсивность 0; 14 часов - самый яркий час, интенсивность 1)
float SM_HourToLightIntencity(float hour)
{
	return abs(abs((hour - 14) / 12) - 1);
}

// тоже самое, только для текущего часа
float SM_CurrentHourToLightIntencity()
{
	return SM_HourToLightIntencity(GetHour());
}

// округление до знаков после точки
float SM_FastRound(float f, int d)
{
	float h = 0.5;
	if (f < 0) h = -0.5;

	if (d == 0)
		return makeint(f + h);

	return makefloat(makeint(f * pow(10, d) + h)) / pow(10, d);
}


/*
void TestAttr()
{
	int n = GetAttributesNum(pchar);
	aref attr;
	for (int i = 0; i < n; i++) {
		if (i > 38 )
			continue;
		attr = GetAttributeN(pchar, i);
		Log_info(GetAttributeName(attr) + ", " + GetAttributeValue(attr));
	}
}
*/

// Пылесосит весь лут с трупов и сундуков в абордажной локации, помещает все собранное добро в спецсундук и запускает его обыск
void csmLootCollector()
{
	if (!IsEntity(&loadedLocation) || !csmCA(pchar, "CSM.LootCollector.Enable") || !csmCA(pchar, "CSM.LootCollector.CanBeRun"))
		return;

	if (!csmCA(loadedLocation, "type") || loadedLocation.type == "boarding_cabine" || loadedLocation.type == "residence" || sti(InterfaceStates.Launched) != 0)
		return;

	int i, j, iBoxes;
	float x, y, z;

	string sBox, sTemp, sAttr;

	aref arFader, arLC, arBoxLC, arBoxes, arFromBox, arFromBody, arItem;
	ref rDeadman;
	ref rLoc = &Locations[FindLocation(pchar.location)];

	if (GetEntity(arFader, "fader"))
		return;

	GetCharacterPos(pchar, &x, &y, &z);
	makearef(arLC, rLoc.locators.box.csmBoxLC);

	arLC.x = x;
	arLC.y = y;
	arLC.z = z;

	arLC.vx.x = 0.0;
	arLC.vx.y = 0.0;
	arLC.vx.z = 0.0;

	arLC.vy.x = 0.0;
	arLC.vy.y = 0.0;
	arLC.vy.z = 0.0;

	arLC.vz.x = 0.0;
	arLC.vz.y = 0.0;
	arLC.vz.z = 0.0;

	arLC.radius = 3.0;
	rLoc.locators_radius.box.csmBoxLC = 2.0;

	if (LAi_IsBoardingProcess())
	{
	makearef(arBoxes, rLoc.locators.box);
	iBoxes = GetAttributesNum(arBoxes);

	if (iBoxes > 0)
	{
		if (iBoxes > MAX_HANDLED_BOXES)
			iBoxes = MAX_HANDLED_BOXES;

		for (i = 0; i < iBoxes; i++)
		{
			sTemp = GetAttributeName(GetAttributeN(arBoxes, i));

			if (sTemp == "csmBoxLC" || sTemp == "")
				continue;

			if (!csmCA(rLoc, sTemp + ".items") && !csmCA(rLoc, sTemp + ".money"))
				continue;

			if (csmCA(rLoc, sTemp + ".money"))
				rLoc.csmBoxLC.money = sti(rLoc.csmBoxLC.money) + sti(rLoc.(sTemp).money);

			makearef(arFromBox, rLoc.(sTemp).items);

			for (j = 0; j < GetAttributesNum(arFromBox); j++)
			{
				arItem = GetAttributeN(arFromBox, j);
				sAttr = GetAttributeName(arItem);

				if (sAttr != "")
				{
					if (!csmCA(rLoc, "csmBoxLC.items." + sAttr))
						rLoc.csmBoxLC.items.(sAttr) = 0;

					rLoc.csmBoxLC.items.(sAttr) = makeint(sti(rLoc.csmBoxLC.items.(sAttr)) + makeint(GetAttributeValue(arItem)));
					rLoc.(sTemp).items.(sAttr) = 0;
				}
			}

			csmDA(rLoc, sTemp + ".items");
			rLoc.(sTemp).items = "";
			rLoc.(sTemp).money = 0;
		}

		if (!CheckAttribute(rLoc, "csmBoxLC.ExtraLoot"))
		{
			rLoc.csmBoxLC.ExtraLoot = true;
			if (rand (1) == 0)	rLoc.csmBoxLC.items.potion1 = makeint(rLoc.csmBoxLC.items.potion1) + rand (3);//Зелье
			if (rand (3) == 0)	rLoc.csmBoxLC.items.potion2 = makeint(rLoc.csmBoxLC.items.potion2) + rand (2);//Эликсир
			if (rand (1) == 0)	rLoc.csmBoxLC.items.potion3 = makeint(rLoc.csmBoxLC.items.potion3) + rand (1);//противоядие
			if (rand (3) == 0)	rLoc.csmBoxLC.items.potion4 = makeint(rLoc.csmBoxLC.items.potion4) + rand (1);//микстура
			if (rand (1) == 0)	rLoc.csmBoxLC.items.potion5 = makeint(rLoc.csmBoxLC.items.potion5) + rand (5);//Виноград
			if (rand (3) == 0)	rLoc.csmBoxLC.items.potionwine = makeint(rLoc.csmBoxLC.items.potionwine) + rand (1);//вино
			if (rand (1) == 0)	rLoc.csmBoxLC.items.potionrum = makeint(rLoc.csmBoxLC.items.potionrum) + rand (2);//ром
			if (rand (1) == 0)	rLoc.csmBoxLC.items.Food1 = makeint(rLoc.csmBoxLC.items.Food1) + rand (5);//фрукты
			if (rand (2) == 0)	rLoc.csmBoxLC.items.Food2 = makeint(rLoc.csmBoxLC.items.Food2) + rand (4);//хлеб
			if (rand (2) == 0)	rLoc.csmBoxLC.items.Food3 = makeint(rLoc.csmBoxLC.items.Food3) + rand (3);//сыр
			if (rand (3) == 0)	rLoc.csmBoxLC.items.Food4 = makeint(rLoc.csmBoxLC.items.Food4) + rand (2);//рыба
			if (rand (3) == 0)	rLoc.csmBoxLC.items.Food5 = makeint(rLoc.csmBoxLC.items.Food5) + rand (2);//мясо
			if (rand (99) == 0)	rLoc.csmBoxLC.items.chest_quest = 1;//странный сундук
		}
		}
	}

	if (Dead_Char_num > 0)
	{
		for (i = 0; i < Dead_Char_num; i++)
		{
			rDeadman = &Dead_Characters[i];

			if (!csmCA(rDeadman, "id"))
				continue;

			sld = CharacterFromId(rDeadman.id)
			if (CheckAttribute(sld, "CantLoot"))//fix
				continue;

			if (!csmCA(rDeadman, "items") && !csmCA(rDeadman, "money"))
				continue;

			if (csmCA(rDeadman, "money"))
				rLoc.csmBoxLC.money = sti(rLoc.csmBoxLC.money) + sti(rDeadman.money);

			makearef(arFromBody, rDeadman.items);

			for (j = 0; j < GetAttributesNum(arFromBody); j++)
			{
				arItem = GetAttributeN(arFromBody, j);
				sAttr = GetAttributeName(arItem);

				if (sAttr != "")
				{
					if (!csmCA(rLoc, "csmBoxLC.items." + sAttr))
						rLoc.csmBoxLC.items.(sAttr) = 0;

					aref weapon;
					Items_FindItem(sAttr, &weapon);
					/*if(CheckAttribute(weapon,"quality") && weapon.quality == "excellent") // ugeen --> на обычных трупах топовое оружие не даем !!!
					{
						rDeadman.items.(sAttr) = 0;
						continue;
					}*/ //нахуй второй фильтр для лута если в методе труповещей уже есть 1

					rLoc.csmBoxLC.items.(sAttr) = makeint(sti(rLoc.csmBoxLC.items.(sAttr)) + makeint(GetAttributeValue(arItem)));
					rDeadman.items.(sAttr) = 0;

				}
			}

			csmDA(rDeadman, "items");
			rDeadman.items = "";
			rDeadman.money = 0;
			//Dead_DelLoginedCharacter(rDeadman); // для упорных хомячков оставим
		}
	}

	pchar.CSM.LootCollector.Run = true;
	sBox = "csmBoxLC";
	pchar.boxname = sBox;
	makearef(arBoxLC, rLoc.(sBox));
	LaunchItemsBox(&arBoxLC);
}

// Скрыть или удалить в текущей локе локатор сундука csmBoxLC из csmLootCollector
void csmHideLootCollectorBox(bool bDelete)
{
	float x, y, z;
	ref rLoc;

	if (FindLoadedLocation() >= 0)
	{
		rLoc = &Locations[FindLocation(pchar.location)];

		if (csmCA(rLoc, "csmBoxLC"))
		{
			GetCharacterPos(pchar, &x, &y, &z);
			rLoc.locators.box.csmBoxLC.y -= 10000.0;

			if (bDelete)
			{
				csmDA(rLoc, "csmBoxLC.items");

				rLoc.csmBoxLC.items = "";
				rLoc.csmBoxLC.money = 0;

				csmDA(rLoc, "csmBoxLC");
				csmDA(pchar, "CSM.LootCollector.CanBeRun");
			}
		}
	}
}

// Сокращение CheckAttribute
int csmCA(object oChar, string sAttr)
{
	return CheckAttribute(&oChar, sAttr);
}

// Сокращение DeleteAttribute
void csmDA(object oChar, string sAttr)
{
	DeleteAttribute(&oChar, sAttr);
}
