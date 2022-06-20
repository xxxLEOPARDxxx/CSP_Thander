void InitBaseCannons_CalcSpeedV0(ref rCannon, float fFireRange)
{
	rCannon.FireRange = fFireRange;
	rCannon.SpeedV0 = sqrt(fFireRange * 9.81 / sin( 2.0 * MakeFloat(rCannon.FireAngMax)) );
}

void InitCannons()
{
	ref rCannon;

    makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS8]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber8";
	rCannon.picture = "cannons1";
	rCannon.Sound = "cannon_fire_culverine_8";
	rCannon.caliber = 8;
	rCannon.ReloadTime = 8;               //45 WW
	rCannon.Cost = 150;
	rCannon.Weight = 2;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 6;
	rCannon.hp = 35.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,400.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS12]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber12";
	rCannon.picture = "cannons1";
	rCannon.Sound = "cannon_fire_culverine_12";
	rCannon.caliber = 12;
	rCannon.ReloadTime = 13;               // 41.5
	rCannon.Cost = 250;
	rCannon.Weight = 4;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.3;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 9;
	rCannon.hp = 40.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,500.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS16]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber16";
	rCannon.picture = "cannons2";
	rCannon.Sound = "cannon_fire_culverine_16";
	rCannon.caliber = 16;
	rCannon.ReloadTime = 18;            //40
	rCannon.Cost = 350;
	rCannon.Weight = 6;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.6;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 12;
	rCannon.hp = 45.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,600.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS20]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber20";
	rCannon.picture = "cannons2";
	rCannon.Sound = "cannon_fire_culverine_20";
	rCannon.caliber = 20;
	rCannon.ReloadTime = 23;             //39.1
	rCannon.Cost = 450;
	rCannon.Weight = 7;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.6;
	rCannon.HeightMultiply = 0.6;
	rCannon.DamageMultiply = 15;
	rCannon.hp = 45.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,650.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS24]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber24";
	rCannon.picture = "cannons3";
	rCannon.Sound = "cannon_fire_culverine_24";
	rCannon.caliber = 24;
	rCannon.ReloadTime = 28;        //  38.6
	rCannon.Cost = 550;
	rCannon.Weight = 8;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.9;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 18;
	rCannon.hp = 50.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,700.0);

    makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS32]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.caliber = 32;
	rCannon.name = "caliber32";
	rCannon.picture = "cannons4";
	rCannon.Sound = "cannon_fire_culverine_32";
	rCannon.ReloadTime = 39;            //    36.9
	rCannon.Cost = 750;
	rCannon.Weight = 10;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 2.2;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 24;
	rCannon.hp = 55.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,800.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS36]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.caliber = 36;
	rCannon.name = "caliber36";
	rCannon.picture = "cannons4";
	rCannon.Sound = "cannon_fire_culverine_36";
	rCannon.ReloadTime = 43;             // 36.2
	rCannon.Cost = 900;
	rCannon.Weight = 11;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 2.2;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 28;
	rCannon.hp = 55.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,850.0);

    makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS8]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber8";
	rCannon.picture = "cannons5";
	rCannon.Sound = "cannon_fire_cannon_8";
	rCannon.caliber = 8;                             //48
	rCannon.ReloadTime = 10;
	rCannon.Cost = 100;
	rCannon.Weight = 3;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 8;
	rCannon.hp = 40.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,300.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS12]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber12";
	rCannon.picture = "cannons5";
	rCannon.Sound = "cannon_fire_cannon_12";
	rCannon.caliber = 12;
	rCannon.ReloadTime = 16;                 //  45
	rCannon.Cost = 150;
	rCannon.Weight = 6;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.4;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 12;
	rCannon.hp = 45.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,400.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS16]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber16";
	rCannon.picture = "cannons6";
	rCannon.Sound = "cannon_fire_cannon_16";
	rCannon.caliber = 16;
	rCannon.ReloadTime = 22;         //43.6
	rCannon.Cost = 250;
	rCannon.Weight = 9;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.6;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 16;
	rCannon.hp = 50.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,500.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS20]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber20";
	rCannon.picture = "cannons6";
	rCannon.Sound = "cannon_fire_cannon_20";
	rCannon.caliber = 20;
	rCannon.ReloadTime = 29;        // 41.3
	rCannon.Cost = 350;
	rCannon.Weight = 10;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.6;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 20;
	rCannon.hp = 50.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,550.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS24]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber24";
	rCannon.picture = "cannons7";
	rCannon.Sound = "cannon_fire_cannon_24";
	rCannon.caliber = 24;
	rCannon.ReloadTime = 35;          //   41.1
	rCannon.Weight = 12;
	rCannon.Cost = 450;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.9;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 24;
	rCannon.hp = 55.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,600.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS32]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 32;
	rCannon.name = "caliber32";
	rCannon.picture = "cannons8";
	rCannon.Sound = "cannon_fire_cannon_32";
	rCannon.ReloadTime = 48;          // 40
	rCannon.Cost = 650;
	rCannon.Weight = 15;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 2.2;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 32;
	rCannon.hp = 60.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,700.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS36]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 36;
	rCannon.name = "caliber36";
	rCannon.picture = "cannons8";
	rCannon.Sound = "cannon_fire_cannon_36";
	rCannon.ReloadTime = 55;         //   39.2
	rCannon.Cost = 850;
	rCannon.Weight = 17;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 2.2;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 36;
	rCannon.hp = 60.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,750.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS42]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 42;
	rCannon.name = "caliber42";
	rCannon.picture = "cannons11";
	rCannon.Sound = "cannon_fire_cannon_42";
	rCannon.ReloadTime = 65;     //  38.7
	rCannon.Cost = 1000;
	rCannon.Weight = 18;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 2.5;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 42;
	rCannon.TradeOff = true;
	rCannon.hp = 70.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,800.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS48]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 48;
	rCannon.name = "caliber48";
	rCannon.picture = "cannons12";
	rCannon.Sound = "cannon_fire_cannon_48";
	rCannon.ReloadTime = 75;       // дпм = 38.4
	rCannon.Cost = 1200;
	rCannon.Weight = 24;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.DamageMultiply = 96.0;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 2.8;
	rCannon.HeightMultiply = 1.0;
	rCannon.TradeOff = true;
	rCannon.hp = 80.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,900.0);
}
