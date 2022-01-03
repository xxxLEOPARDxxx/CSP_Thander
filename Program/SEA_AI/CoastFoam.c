object CoastFoam;

void CreateCoastFoamEnvironment(string sFoamID, int iExecuteLayer, int iRealizeLayer)
{
	CoastFoam.id = sFoamID;
	CoastFoam.Edit = false;
	CreateEntity(&CoastFoam, "CoastFoam");
	LayerAddObject(iExecuteLayer, &CoastFoam, 65530);
	LayerAddObject(iRealizeLayer, &CoastFoam, 65531);
}

void DeleteCoastFoamEnvironment()
{
	DeleteClass(&CoastFoam);
}
