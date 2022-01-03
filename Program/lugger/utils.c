/* PROGRAM/LUGGER/UTILS.C */
/////////////////////////////////////////////////////////////////////////////////
// Раздача еды
/////////////////////////////////////////////////////////////////////////////////
void SetFoodToCharacter(ref chr, int iQuantity, int iFoodQuantity)
{
	int d = 1;
	int iSum = 0;
	string sFood = "";
	for(int f = 1; f <= iQuantity; f++)
	{
		sFood = "Food" + f;
		if(CheckAttribute(chr, "items." + sFood))
		{
			DeleteAttribute(chr, "items." + sFood);
		}

		switch(f)
		{
			case 1: d = 2; break;
			case 2: d = 4; break;
			case 3: d = 6; break;
			case 4: d = 8; break;
			case 5: d = 10; break;
		}

		iSum = iFoodQuantity / d;
		TakeNItems(chr, sFood, iSum);
	}
}
