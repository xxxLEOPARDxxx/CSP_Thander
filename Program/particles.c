object Particles;

void InitParticles()
{
	Particles.Server = false;
	Particles.windpower = 1.0;
	Particles.winddirection.x = frnd();
	Particles.winddirection.z = frnd();
	if (!CreateParticleEntity())
	{
		Trace("Can't create 'particles' class");
	}
}

void PauseParticles(bool bPause)
{
	if (!CreateParticleEntity()) return;
	SendMessage(&Particles, "ll", PS_PAUSEALL, bPause);
}

void DeleteParticles()
{
	SendMessage(&Particles,"l", PS_CLEARALL);
	Particles.winddirection.x = frnd();
	Particles.winddirection.z = frnd();
}

void DeleteParticleSystem(int id)
{
	SendMessage(&Particles,"ll",PS_DELETE,id);
}


int CreateParticleSystem(string name,float x,float y,float z,
		float ax,float ay,float az,int lifetime)
{
	int pid;
	if (!CreateParticleEntity()) return 0;
	pid = SendMessage(&Particles,"lsffffffl",PS_CREATE,name,x,y,z,ax,ay,az,lifetime);
	return pid;
}

bool CreateParticleEntity()
{
	if(IsEntity(Particles) == false)
	{
		if (CreateEntity(&Particles,"particles") == false) return false;
		//Trace("bool CreateParticleEntity()");
		LayerAddObject(REALIZE,Particles,65536);
		LayerAddObject(EXECUTE,Particles,0);
		LayerAddObject(SEA_REALIZE,Particles,65536);
		LayerAddObject(SEA_EXECUTE,Particles,0);
	}
	return true;
}

void MoveParticlesToLayers(int iExecuteLayer, int iRealizeLayer)
{
	LayerDelObject(EXECUTE, &Particles);
	LayerDelObject(REALIZE, &Particles);
	LayerDelObject(SEA_EXECUTE, &Particles);
	LayerDelObject(SEA_REALIZE, &Particles);

	LayerAddObject(iExecuteLayer, &Particles, 0);
	LayerAddObject(iRealizeLayer, &Particles, 65536);
}

int CreateParticleSystemX(string name,float x,float y,float z,
		float ax,float ay,float az,int lifetime)
{
	int pid;
	if (!CreateParticleEntity()) return false;
	pid = SendMessage(&Particles,"lsffffffl",PS_CREATEX,name,x,y,z,ax,ay,az,lifetime);
	return pid;
}

int CreateBlast(float x,float y,float z)
{
	int iRes;
	object blast;
	iRes = CreateEntity(&blast,"blast");
	SendMessage(&blast,"lfff",LM_SETPOINT,x,y,z);
	LayerAddObject(REALIZE,blast,3);
	LayerAddObject(SEA_REALIZE,blast,3);
	return iRes;
}

int CreateBlastX(float x,float y,float z,float ax,float ay,float az)
{
	int iRes;
	object blast;
	iRes = CreateEntity(&blast,"blast");
	SendMessage(&blast,"lffffff",LM_SETPOINTANDANGLES,x,y,z,ax,ay,az);
	LayerAddObject(REALIZE,blast,3);
	LayerAddObject(SEA_REALIZE,blast,3);
	return iRes;
}
