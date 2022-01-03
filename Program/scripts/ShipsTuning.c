
//генератор "отбермуженных" статов для кораблей
void SetTuningShipStates(ref chr)
{
	int iType = GetCharacterShipType(chr);
	if(iType == SHIP_NOTUSED)
	{
		return; //нет корабля - отсекаем
	}
	ref rShip = GetRealShip(iType);

	if(rShip.class == 7) return;	//мелкие корабли отсекаем
	//if(rShip.stolen == 0) return;	//генератор будет только на захваченных в море

	int iRand = 30;
	if(rand(iRand) == 0) SetShipMaxCaliberTuning(chr, true);	//увеличение калибра
	if(rand(iRand) == 0) SetShipCapacityTuning(chr, true);		//увеличение трюма
	if(rand(iRand) == 0) SetShipSpeedRateTuning(chr, true);		//увеличение скорости
	if(rand(iRand) == 0) SetShipMastMultiplierTuning(chr, true);//увеличение прочности мачт
	if(rand(iRand) == 0) SetShipMaxCrewTuning(chr, true);		//увеличение команды
	if(rand(iRand) == 0) SetShipTurnRateTuning(chr, true);		//увеличение маневренности
	if(rand(iRand) == 0) SetShipHPTuning(chr, true);			//увеличение ХП
}

//генератор "отбермуженных" статов для кораблей с ручным рандомом
void SetTuningShipStatesRandom(ref chr, int iRand)
{
	int iType = GetCharacterShipType(chr);
	if(iType == SHIP_NOTUSED)
	{
		return; //нет корабля - отсекаем
	}
	ref rShip = GetRealShip(iType);

	if(rShip.class == 7) return;	//мелкие корабли отсекаем
	//if(rShip.stolen == 0) return;	//генератор будет только на захваченных в море

	if(rand(iRand) == 0) SetShipMaxCaliberTuning(chr, true);	//увеличение калибра
	if(rand(iRand) == 0) SetShipCapacityTuning(chr, true);		//увеличение трюма
	if(rand(iRand) == 0) SetShipSpeedRateTuning(chr, true);		//увеличение скорости
	if(rand(iRand) == 0) SetShipMastMultiplierTuning(chr, true);//увеличение прочности мачт
	if(rand(iRand) == 0) SetShipMaxCrewTuning(chr, true);		//увеличение команды
	if(rand(iRand) == 0) SetShipTurnRateTuning(chr, true);		//увеличение маневренности
	if(rand(iRand) == 0) SetShipHPTuning(chr, true);			//увеличение ХП
}

//установка назначенных "отбермуженных" статов для корабля
void SetTuningStates2Ship(ref chr, bool MaxCaliber, bool Capacity, bool SpeedRate, bool MaxCrew, bool TurnRate, bool HP, bool MastMulti)
{
	int iType = GetCharacterShipType(chr);
	if(iType == SHIP_NOTUSED)
	{
		return; //нет корабля - отсекаем
	}

	if(MaxCaliber)	SetShipMaxCaliberTuning(chr, MaxCaliber);		//увеличение калибра
	if(Capacity)	SetShipCapacityTuning(chr, Capacity);			//увеличение трюма
	if(SpeedRate)	SetShipSpeedRateTuning(chr, SpeedRate);			//увеличение скорости
	if(MastMulti)	SetShipMastMultiplierTuning(chr, MastMulti);	//увеличение прочности мачт
	if(MaxCrew)		SetShipMaxCrewTuning(chr, MaxCrew);				//увеличение команды
	if(TurnRate)	SetShipTurnRateTuning(chr, TurnRate);			//увеличение маневренности
	if(HP)			SetShipHPTuning(chr, HP);						//увеличение ХП
}

//увеличение калибра
void SetShipMaxCaliberTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.MaxCaliber") && sti(rShip.MaxCaliber) < 36)
	{
		if(isSet)
		{
			int iCaliber = sti(rShip.MaxCaliber);
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
			}
			iCaliber = iCaliber + 1;
			if(iCaliber > 6) iCaliber = 6;
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
			}
			rShip.MaxCaliber = iCaliber;
			rShip.Tuning.Cannon = true;
		}
	}
}

//увеличение трюма
void SetShipCapacityTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.Capacity"))
	{
		if(isSet)
		{
			rShip.Capacity = sti(rShip.Capacity) + makeint(sti(rShip.Capacity)/5);
			rShip.Tuning.Capacity = true;
		}
	}
}

//увеличение скорости
void SetShipSpeedRateTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.SpeedRate"))
	{
		if(isSet)
		{
			rShip.SpeedRate = (stf(rShip.SpeedRate) + stf(rShip.SpeedRate)/5.0);
			rShip.Tuning.SpeedRate = true;
		}
	}
}

//прочность мачт
void SetShipMastMultiplierTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.MastMultiplier"))
	{
		if(isSet)
		{
			rShip.MastMultiplier        = stf(rShip.MastMultiplier) - 0.3;
			rShip.Tuning.MastMultiplier = true;
		}
	}
}

//увеличение команды
void SetShipMaxCrewTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.MaxCrew"))
	{
		if(isSet)
		{
			rShip.MaxCrew = sti(rShip.MaxCrew) + makeint(sti(rShip.MaxCrew)/5);
			rShip.Tuning.MaxCrew = true;
		}
	}
}

//увеличение маневренности
void SetShipTurnRateTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.TurnRate"))
	{
		if(isSet)
		{
			rShip.TurnRate = (stf(rShip.TurnRate) + stf(rShip.TurnRate)/5.0);
			rShip.Tuning.TurnRate = true;
		}
	}
}

//увеличение ХП
void SetShipHPTuning(ref chr, bool isSet)
{
	ref rShip = &RealShips[sti(chr.ship.type)];

	if(!CheckAttribute(rShip, "Tuning.HP"))
	{
		if(isSet)
		{
			rShip.HP = sti(rShip.HP) + makeint(sti(rShip.HP)/5);
			rShip.Tuning.HP = true;
			chr.ship.HP = sti(rShip.HP);		//чтобы были полные ХП после тюнинга
		}
	}
}
