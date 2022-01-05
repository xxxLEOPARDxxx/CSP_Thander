/////////////////////////
// GOF 1.2
/////////////////////////

#define DIRECTSAILDEBUG	0;

// #define DIRECTENCOUNTERCHANCE 50   // chance in percent that an encounter fleet appears every hour
#define DIRECTENCOUNTERDISTANCE 1000 // distance from player at which random ships appear

#define DIR_PORTBOW 1
#define DIR_FORWARD 2
#define DIR_STARBOW 3
#define DIR_STAR 4
#define DIR_PORT 5
#define DIR_PORTSTERN 6
#define DIR_ABAFT 7
#define DIR_STARSTERN 8

void CheckIslandChange()
{
	//#20190624-01
    float RTplayerShipX;
    float RTplayerShipZ;
    int scale;
    getRTplayerShipXZ(&RTplayerShipX, &RTplayerShipZ, &scale);
    //#20190628-01
    float distToClosestIsland;
    bool bScaleDiff;
	int nextisland = getRTclosestIsland(RTplayerShipX, RTplayerShipZ, scale, &distToClosestIsland, &bScaleDiff);

	//if (DIRECTSAILDEBUG) trace("CheckIslandChange: nextisland=" + nextisland);

	while(nextisland > -1 && nextisland != FindIsland(worldMap.island))
	{
		//only switch if pretty close
		ref rIsland = GetIslandByIndex(nextisland);//makeref(rIsland, Islands[inum]);
		string sNewIslandId = rIsland.id;
		string sIslandNow = worldMap.island;

		float distToCurIsland;
		if (worldMap.island == WDM_NONE_ISLAND) distToCurIsland = 2500000000.0; //50000.0;
		else distToCurIsland = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, stf(worldMap.islands.(sIslandNow).position.x), stf(worldMap.islands.(sIslandNow).position.z));
		//#20190628-01
		//float distToClosestIsland = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, stf(worldMap.islands.(sNewIslandId).position.x), stf(worldMap.islands.(sNewIslandId).position.z));

		//if (DIRECTSAILDEBUG) trace("CheckIslandChange: distToCurIsland=" + distToCurIsland + ", distToClosestIsland=" + distToClosestIsland);

		//only change if getting close
		if (bScaleDiff) {
            if(distToClosestIsland * 1.12 > distToCurIsland)
                return;
        }
        else {
            if(distToClosestIsland * 2.0 > distToCurIsland)
                return;
		}
		// aborts function if enemyships near, so that you aren't teleported out of an engagement
		//#20190703-01
		aref rSituation;
		makearef(rSituation, pchar.SeaAI.Update.Situation);
		float enemydist = 0.0;
		int nextenemy = 0;
		float enemyDistLimit   = 1000.0;
		float neutralDistLimit = 1000.0;

		nextenemy = sti(rSituation.MinEnemyIndex);
		enemydist = stf(rSituation.MinEnemyDistance);
		//if (DIRECTSAILDEBUG) trace("DirectsailCheck; next enemy: "+nextenemy + " dist: "+enemydist);
		if(nextenemy!= -1 && enemydist<enemyDistLimit )
		{
			//if (DIRECTSAILDEBUG) trace("Directsail aborted due to hostile ship, dist = " + enemydist);	// LDH - 07Jan09
			return;
		}
		// Jan 07, same for neutral ships
		nextenemy = sti(rSituation.MinNeutralIndex);
		enemydist = stf(rSituation.MinNeutralDistance);

		//if (DIRECTSAILDEBUG) trace("DirectsailCheck; next neutral ship: "+nextenemy + " dist: "+enemydist);
		if(nextenemy!= -1 && enemydist<neutralDistLimit && sti(Characters[nextenemy].ship.type) != SHIP_FORT ) // LDH added fort check 08Jan09
		{
		  //if (DIRECTSAILDEBUG) trace("Directsail aborted due to neutral ship, dist = " + enemydist);	// LDH added logit to trace - 07Jan09
		  return;
		}
		// looks like this doesn't always work, so I added another check for being in battle
		if(!bMapEnter) {
			//if (DIRECTSAILDEBUG) trace("Directsail aborted in battle");
			return;
		}		// LDH added logit to trace 07Jan09
        //#20180813-02
		SetEventHandler("FaderEvent_StartFade", "ChangeSeaMapNew", 0);
        SetEventHandler("FaderEvent_EndFade", "Sea2Sea_Reload", 0);
        CreateEntity(&wdm_fader, "fader");
        float fadeOutTime = 0.5;
        SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
        SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
        pchar.loadscreen = "loading\sea_" + rand(31) + ".tga";
        SendMessage(&wdm_fader, "ls",FADER_PICTURE0, pchar.loadscreen);
		break;
	}
}
//#20190624-01
void getRTplayerShipXZ(ref RTplayerShipX, ref RTplayerShipZ, ref scale)
{
	float zeroX = MakeFloat(worldMap.zeroX);
	float SeaX = stf(pchar.Ship.Pos.x);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float SeaZ = stf(pchar.Ship.Pos.z);
	string sIsland = worldMap.island;

	scale = WDM_MAP_TO_SEA_SCALE;
	if (sIsland == "Cuba1" || sIsland == "Cuba2" || sIsland == "Beliz" || sIsland == "SantaCatalina"
		|| sIsland == "PortoBello" || sIsland == "Cartahena" || sIsland == "Maracaibo"
		|| sIsland == "Caracas" || sIsland == "Cumana")
	{
		scale = 25;
	}
	RTplayerShipX = (SeaX/scale) + zeroX;
	RTplayerShipZ = (SeaZ/scale) + zeroZ;
	return;
}

float getRTplayerShipAY()
{
	float RTplayerShipAY = stf(pchar.Ship.Ang.y);
	return RTplayerShipAY;
}
//#20190628-01
int getRTclosestIsland(float RTplayerShipX, float RTplayerShipZ, int curScale, ref iDistanceNow, ref scaleDiff)
{
	//if(DIRECTSAILDEBUG) trace("getRTclosestIsland. curr island: " + worldMap.island);

	//#20190624-01
    bool tempDiff;
	float distance, iBearing, offShip, shipAY, iX, iZ;
	bool isStar;
	iDistanceNow = 2500000000.0; //50000.0;
    scaleDiff = false;
	int nextisland = -1;
	ref rIsland;
	string islandTemp;
    shipAY = stf(pchar.Ship.Ang.y);
	for (int inum=0; inum<=iNumIslands; inum++)
	{
		rIsland = GetIslandByIndex(inum);//makeref(rIsland, Islands[inum]);
		islandTemp = rIsland.id;
		iX = stf(worldMap.islands.(islandTemp).position.x);
		iZ = stf(worldMap.islands.(islandTemp).position.z);

		iBearing = GetAngleY(iX - RTplayerShipX, iZ - RTplayerShipZ);
        offShip = iBearing - shipAY;
        int nBear = ClosestDirFA(offShip);
        if(nBear != DIR_FORWARD) continue; //Skip islands not heading toward

		//#20190628-01
		tempDiff = false;
		if(curScale == WDM_MAP_TO_SEA_SCALE) {
            if (islandTemp == "Cuba1" || islandTemp == "Cuba2" || islandTemp == "Beliz" || islandTemp == "SantaCatalina"
                || islandTemp == "PortoBello" || islandTemp == "Cartahena" || islandTemp == "Maracaibo"
                || islandTemp == "Caracas" || islandTemp == "Cumana")
            {
                tempDiff = true;
            }
		}
        //#20190628-01
		distance = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, iX, iZ);

		//if(DIRECTSAILDEBUG) trace("getRTclosestIsland. islandTemp=" + islandTemp + ", distance=" + distance + ", iDistanceNow=" + iDistanceNow);

		if (distance < iDistanceNow)
		{
			iDistanceNow = distance
			nextisland = inum;
			scaleDiff = tempDiff;
		}
	}
	//if(DIRECTSAILDEBUG) trace("getRTclosestIsland. closest island: " + Islands[nextisland].id + ", idx=" + nextisland);

	return nextisland;
}

//#20180813-02
void ChangeSeaMapNew() //string sNewIslandId)
{
	//ShipsInit();
	DelEventHandler("FaderEvent_StartFade", "ChangeSeaMapNew");
    PauseAllSounds();
	DeleteSeaEnvironment();
	//SetEventHandler("Sea2Sea_Reload", "Sea2Sea_Reload", 0);
	//PostEvent("Sea2Sea_Reload", 0);
	LayerAddObject(SEA_REALIZE, &wdm_fader, -1);
}

void Sea2Sea_Reload()
{
    //#20180813-02
	//DelEventHandler("Sea2Sea_Reload", "Sea2Sea_Reload");
	DelEventHandler("FaderEvent_EndFade", "Sea2Sea_Reload");
    ReloadProgressStart();
	object seaLoginToSea;

	//#20190624-01
    float CX;
    float CZ;
    int scale = WDM_MAP_TO_SEA_SCALE;
    float fScrap;
    getRTplayerShipXZ(&CX, &CZ, &scale);

	float CAY = getRTplayerShipAY();
	//#20190628-01 //#20190628-01
	bool bScaleDiff;
	int nextisland = getRTclosestIsland(CX, CZ, scale, &fScrap, &bScaleDiff);
	ref rIsland = GetIslandByIndex(nextisland);
	string CIsland = rIsland.id;

	float ix = MakeFloat(worldMap.islands.(CIsland).position.x);
	float iz = MakeFloat(worldMap.islands.(CIsland).position.z);

	/*if (CIsland == "Cuba1" || CIsland == "Cuba2" || CIsland == "Beliz" || CIsland == "SantaCatalina"
		|| CIsland == "PortoBello" || CIsland == "Cartahena" || CIsland == "Maracaibo"
		|| CIsland == "Caracas" || CIsland == "Cumana")
	{
		scale = 25;
	}
	*/
	seaLoginToSea.playerGroup.x = (CX - ix)*scale;
	seaLoginToSea.playerGroup.z = (CZ - iz)*scale;
	seaLoginToSea.playerGroup.ay = CAY;
	seaLoginToSea.island = CIsland;

	seaLoginToSea.imageName = pchar.loadscreen;
    //musicName = "";
    DeleteAttribute(pchar, "pirateFriendly");
	SeaLogin(&seaLoginToSea);
	LayerAddObject(SEA_REALIZE, &wdm_fader, -1);
	ReloadProgressEnd();

	//#20190624-01
    float RTplayerShipX;
    float RTplayerShipZ;
    getRTplayerShipXZ(&RTplayerShipX, &RTplayerShipZ, &scale);
	worldMap.playerShipX = RTplayerShipX;
	worldMap.playerShipZ = RTplayerShipZ;
	worldMap.playerShipAY = getRTplayerShipAY();
	worldMap.island = rIsland.id;
	worldMap.zeroX = ix;
	worldMap.zeroZ = iz;
}

//Returns #define DIR_XXX
int ClosestDirE(float dir)
{
    //float aX[8] {-0.5,0.0,0.5,1.0,-1.0,-0.5,0.0,0.5};
    //float aZ[8] {1.0,1.0,1.0,0.0,0.0,-1.0,-1.0,-1.0};
    float aX[8];
    float aZ[8];
    //Bug in compiler...float inits don't work: invalid operand
    aX[0] = -0.5; aX[1] = 0.0; aX[2] = 0.5; aX[3] = 1.0; aX[4] = -1.0; aX[5] = -0.5; aX[6] = 0.0; aX[7] = 0.5;
    aZ[0] = 1.0; aZ[1] = 1.0; aZ[2] = 1.0; aZ[3] = 0.0; aZ[4] = 0.0; aZ[5] = -1.0; aZ[6] = -1.0; aZ[7] = -1.0;

    float maxDot = -999999999.0;
    int nRet = 0;
    for(int i = 0; i < 8; i++) {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot) {
             //ret = dir;
             nRet = i + 1;
             maxDot = t;
         }
    }
    return nRet;
}

int ClosestDirFA(float dir)
{
    float aX[6];
    float aZ[6];
    //Bug in compiler...array inits don't work in .c files
    aX[0] = -1.0; aX[1] = 0.0; aX[2] = 1.0; aX[3] = -1.0; aX[4] = 0.0; aX[5] = 1.0;
    aZ[0] = 0.5; aZ[1] = 1.0; aZ[2] = 0.5; aZ[3] = 0.0; aZ[4] = -1.0; aZ[5] = 0.0;

    float maxDot = -99999999.0;
    int nRet = 0;
    for(int i = 0; i < 6; i++) {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot) {
             nRet = i + 1;
             maxDot = t;
         }
    }
    if(nRet < 4)
        nRet = DIR_FORWARD;
    else
        nRet = DIR_ABAFT;

    return nRet;
}
