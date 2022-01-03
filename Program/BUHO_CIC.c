bool CIC_CdreCommand = False;
void CIC_SendCommand(string sComm)
{
	int nShipType;
	ref rChr;
	int i;

	CIC_CdreCommand = True;
	for (i = 1; i < COMPANION_MAX; i++)
	{
		int cn;
		cn = GetCompanionIndex(PChar, i);
		if (cn == -1) continue;
		makeref(rChr, Characters[cn]);
		nShipType = GetCharacterShipType(rChr);
		if (nShipType == SHIP_NOTUSED) continue;
		switch (sComm)
		{
			case "CIC_LoadBalls":
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_BALLS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
                }
			break;
			case "CIC_LoadGrapes":
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_GRAPES)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 2, "");
                }
			break;
			case "CIC_LoadChain":
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_KNIPPELS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 3, "");
                }
			break;
			case "CIC_LoadBombs":
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_BOMBS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 4, "");
                }
			break;
			case "CIC_LoadAtWill":
                Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
                Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
			break;
			case "CIC_SailAway"	:
				Event("BI_LaunchCommand","lsls", cn, "BI_SailAway", -1, "");
			break;
			case "CIC_LowerSails":
				Event("BI_LaunchCommand","lsls", cn, "BI_HeaveToDrift", -1, "");
			break;
			case "CIC_ProtFlagship":
				Event("BI_LaunchCommand","lsls", cn, "BI_Defend", GetMainCharacterIndex(), "");
			break;
		}
	}
	CIC_CdreCommand = False;
}
