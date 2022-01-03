//функции для некоторых вычислений

// выбор приветствия ПГГ в зависимости от пола
string GetPggTavernGreeting(ref rChar)
{
    switch (rChar.sex)
    {
    case "skeleton":
        return "skeleton";
    break;

    case "man":
        return "Gr_Tavern_Mate";
    break;

    case "woman":
        return "Gr_Woman_Citizen";
    break;
    }
}

/// (Выдача рандомного оружия по качеству (ржавое, обычное, редкое, уникальное))
string GiveRandomBladeByType(string sType)
{
	switch(sType)
	{
    string blade = "blade2";
	case "Poor":
	   switch(rand(9))
	   {
		    case 0: blade = "blade5"; break;
		    case 1: blade = "blade2"; break;
		    case 2: blade = "blade1"; break;
	    	case 3: blade = "blade4"; break;
		    case 4: blade = "topor3"; break;
		    case 5: blade = "blade3"; break;
		    case 6: blade = "blade10"; break;
		    case 7: blade = "blade35"; break;
		    case 8: blade = "topor1"; break;
		    case 9: blade = "blade17"; break;
	    }
	break;

	case "ordinary":
		switch(rand(7))
	    {
			case 0: blade = "blade6"; break;
			case 1: blade = "blade9"; break;
			case 2: blade = "blade7"; break;
			case 3: blade = "blade12"; break;
			case 4: blade = "blade18"; break;
			case 5: blade = "blade8"; break;
			case 6: blade = "blade11"; break;
			case 7: blade = "blade16"; break;
		}
	break;

	case "good":
		switch(rand(6))
	    {
			case 0: blade = "blade19"; break;
			case 1: blade = "blade22"; break;
			case 2: blade = "blade31"; break;
			case 3: blade = "blade34"; break;
			case 4: blade = "blade15"; break;
			case 5: blade = "blade21"; break;
			case 6: blade = "topor2"; break;
		}
	break;

	case "excellent":
		switch(rand(10))
	    {
			case 0: blade = "blade28"; break;
			case 1: blade = "blade23"; break;
			case 2: blade = "blade27"; break;
			case 3: blade = "blade30"; break;
			case 4: blade = "blade24"; break;
			case 5: blade = "blade25"; break;
			case 6: blade = "blade26"; break;
			case 7: blade = "blade32"; break;
			case 8: blade = "blade13"; break;
			case 9: blade = "blade20"; break;
			case 10: blade = "blade33"; break;
	    }
	break;

	case "indian":
		switch(rand(2))
	    {
			case 0: blade = "blade_01"; break;
			case 1: blade = "blade_02"; break;
			case 2: blade = "topor_05"; break;
	    }
	break;
	}

	return blade;
}

// быстрое пополнение массива мушкетерских моделей. (Дабы не копатся в разных файлах)
string GetPirateMushketerModel()
{
    string sModel;

	sModel = "mushketer_" + (rand(24) + 1);

    return sModel;
}
