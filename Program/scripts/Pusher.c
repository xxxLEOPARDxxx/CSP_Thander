int SM_PusherSkipFrame = 0;


void SM_PusherSwitch()
{
	pchar.CSM.CrowdPusher = 1;
	SM_PusherEnable();
}


void SM_PusherEnable()
{
	if (!CheckAttribute(pchar, "CSM.CrowdPusher"))
		pchar.CSM.CrowdPusher = 1;

	SetEventHandler(EVENT_LOCATION_LOAD, "SM_PS_OnLocationLoad", 0);
	SetEventHandler(EVENT_LOCATION_UNLOAD, "SM_PS_OnLocationUnload", 0);

	if (!IsEntity(loadedLocation))
		return;

	if(bSeaActive && !isShipInside(pchar.location) && !HasSubStr(pchar.location, "BOARDING_"))
		return;

	SetEventHandler("frame", "SM_PS_OnEnterFrame", 0);
}


void SM_PusherDisable()
{
	DeleteAttribute(pchar, "CSM.CrowdPusher");
	DelEventHandler("frame", "SM_PS_OnEnterFrame");
	DelEventHandler(EVENT_LOCATION_LOAD, "SM_PS_OnLocationLoad");
	DelEventHandler(EVENT_LOCATION_UNLOAD, "SM_PS_OnLocationUnload");

	SM_PS_PushRevert(true);
}


void SM_PusherOnLoad()
{
	if (CheckAttribute(pchar, "CSM.CrowdPusher"))
		SM_PusherEnable();
}


void SM_PS_OnLocationUnload()
{
	DelEventHandler("frame", "SM_PS_OnEnterFrame");
	SM_PusherSkipFrame = 0;
	SM_PS_PushRevert(true);
}


void SM_PS_OnLocationLoad()
{
	SetEventHandler("frame", "SM_PS_OnEnterFrame", 0);
}


void SM_PS_OnEnterFrame()
{
	SM_PS_PushAction();
}


void SM_PS_PushAction()
{
	int i, n;
	float scanRadius, plocx, plocy, plocz, nlocx, nlocy, nlocz, scale;
	if (!LAi_IsFightMode(pchar)) return;
	if (LAi_IsFightMode(pchar)) {
		switch (sti(pchar.CSM.CrowdPusher))
		{
			case 0: scanRadius = 1.3; scale = 0.04; break;
			case 1: scanRadius = 1.6; scale = 0.06; break;
			case 2: scanRadius = 1.7; scale = 0.09; break;
			case 3: scanRadius = 1.8; scale = 0.12; break;
		}
	} else {
		scanRadius = 1.2;
		scale = 0.04;
	}

	n = FindNearCharacters(pchar, scanRadius, -1.0, -1.0, 0.001, false, true);
	if (n <= 0)
		return;

	GetCharacterPos(pchar, &plocx, &plocy, &plocz);

	for (i = 0; i < n; i++)
	{
		if (!CheckAttribute(chrFindNearCharacters[i], "index"))
			continue;

		ref npc = GetCharacter(sti(chrFindNearCharacters[i].index));

		if (npc.chr_ai.type == LAI_TYPE_CARRY ||
		npc.chr_ai.type == LAI_TYPE_POOR ||
		npc.chr_ai.type == LAI_TYPE_SIT)
			continue;

		if (CheckAttribute(npc, "chr_ai.type.quest") && npc.chr_ai.type.quest != "")
			continue;

		GetCharacterPos(npc, &nlocx, &nlocy, &nlocz);

		if (!CheckAttribute(npc, "CSM.Pushed"))
		{
			npc.CSM.Pushed.x = nlocx;
			npc.CSM.Pushed.y = nlocy;
			npc.CSM.Pushed.z = nlocz;
			npc.CSM.Pushed.resetFrameCount = 50;
			if (CheckAttribute(npc, "chr_ai") &&
				CheckAttribute(npc, "chr_ai.tmpl") &&
				CheckAttribute(npc, "chr_ai.tmpl.group") &&
				CheckAttribute(npc, "chr_ai.tmpl.locator") &&
				CheckAttribute(npc, "chr_ai.tmpl.timeout") &&
				npc.chr_ai.tmpl == LAI_TMPL_GOTO
			)
			{
				npc.CSM.Pushed.group = npc.chr_ai.tmpl.group;
				npc.CSM.Pushed.locator = npc.chr_ai.tmpl.locator;
				npc.CSM.Pushed.timeout = npc.chr_ai.tmpl.timeout;
			}
		}

		TeleportCharacterToPos(npc, (nlocx - plocx) * scale + nlocx, nlocy, (nlocz - plocz) * scale + nlocz);
	}
}


void SM_PS_PushRevert(bool revertImmediately)
{
	int i;
	float scanRadius = 12;

	int n = FindNearCharacters(pchar, scanRadius, -1.0, -1.0, 0.001, false, true);

	if (n <= 0)
		return;

	ref npc;

	for (i = 0; i < n; i++)
	{
		if (!CheckAttribute(chrFindNearCharacters[i], "index"))
			continue;

		npc = GetCharacter(sti(chrFindNearCharacters[i].index));

		if (!CheckAttribute(npc, "CSM.Pushed"))
			continue;

		if (sti(npc.CSM.Pushed.resetFrameCount) <= 0 || revertImmediately)
		{
			TeleportCharacterToPos(npc, stf(npc.CSM.Pushed.x), stf(npc.CSM.Pushed.y), stf(npc.CSM.Pushed.z));
			if (CheckAttribute(npc, "CSM.Pushed.locator"))
				LAi_tmpl_goto_SetLocator(npc, npc.CSM.Pushed.group, npc.CSM.Pushed.locator, npc.CSM.Pushed.timeout);
			DeleteAttribute(npc, "CSM.Pushed");
			continue;
		}

		npc.CSM.Pushed.resetFrameCount = sti(npc.CSM.Pushed.resetFrameCount) - 10;
	}
}
