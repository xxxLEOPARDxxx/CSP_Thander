extern void StoreInit();

void InitStores()
{
    int i;

    for(i=0; i<STORE_QUANTITY; i++)
    {
		stores[i].index = i;
        StoreVoidFill(&stores[i]);
    }

	if(LoadSegment("store\store_init.c"))
	{
		StoreInit();
		UnloadSegment("store\store_init.c");
	}

   for(i=0; i<STORE_QUANTITY; i++)
   {
       FillStoreGoods(&stores[i]);
   }

}

void SetStoresTradeType(int StoreNum,int GoodsNum,int TradeType)
{
	string tmpstr = Goods[GoodsNum].Name;
	Stores[StoreNum].Goods.(tmpstr).TradeType = TradeType;
}

void FillStoreGoods(ref pRef)
{
	int i,j,nq,n,tt;
	string goodName;
	string goodType;
	//int goodBasePrice;
	int iColony = FindColony(pRef.Colony); // город магазина
	aref arTypes, arCurType;
	if (iColony != -1)
	{
		ref rColony = GetColonyByIndex(iColony);
		int islandIdx = FindIsland(rColony.island); // остров города

		if (islandIdx!=-1)
		{
            ref rIsland = GetIslandByIndex(islandIdx);
			makearef(arTypes, rIsland.Trade); // вся инфа как и в ПКМ по островам
			nq = GetAttributesNum(arTypes);
			for(i=0;i<nq;i++)
			{
				arCurType = GetAttributeN(arTypes,i);
				tt=TRADE_TYPE_NORMAL;
				switch(GetAttributeName(arCurType))
				{
					case "Export":		tt=TRADE_TYPE_EXPORT;		break;
					case "Import":		tt=TRADE_TYPE_IMPORT;		break;
					case "Contraband":	tt=TRADE_TYPE_CONTRABAND;	break;
					case "Aggressive":	tt=TRADE_TYPE_AGGRESSIVE;	break;
				}
				n = GetAttributesNum(arCurType);
				for(j=0;j<n;j++)
				{
					goodName = Goods[sti(GetAttributeValue(GetAttributeN(arCurType,j)))].name;
					pRef.Goods.(goodName).TradeType = tt;
				}
			}
		}
		else
		{
			trace("Mistake island id into store:  id="+rColony.island);
		}
	}
	else
	{
		trace("Mistake Colony id into store:  id=" + pRef.Colony);
	}

	for (i=0; i<GOODS_QUANTITY; i++)
	{
	   	goodName = Goods[i].Name;
	   	// boal 22.01.2004 -->
		switch(sti(pRef.Goods.(goodName).TradeType))
		{
			case TRADE_TYPE_EXPORT:
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.9 + rand(sti(sti(Goods[i].Norm)*0.2)));
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.1;
			break;
			case TRADE_TYPE_NORMAL:
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.5 + rand(sti(sti(Goods[i].Norm)*0.2)));
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15;
			break;
			case TRADE_TYPE_IMPORT:
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.15 + rand(sti(sti(Goods[i].Norm)*0.15)));
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15;
			break;
			case TRADE_TYPE_AGGRESSIVE:
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.1 + rand(sti(sti(Goods[i].Norm)*0.02)));
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.2;
			break;
			case TRADE_TYPE_CONTRABAND:
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.1 + rand(sti(sti(Goods[i].Norm)*0.1)));
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.2;
			break;
			case TRADE_TYPE_AMMUNITION:  //делаю все тоже, что и для нормального товара, а тип нужен, чтоб на корабле не скупали лишнее.
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.5 + rand(sti(sti(Goods[i].Norm)*0.2))); //200 + Rand(2500) + rand(500);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15;//0.2
			break;
			case TRADE_TYPE_CANNONS:
				if(sti(Goods[i].NotSale) == 1) // 1.2.5 --> старшие калибры не продаем !!!
				{
					pRef.Goods.(goodName).Quantity = 0;
				}
				else
				{
					pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.6 + rand(sti(sti(Goods[i].Norm)*0.6))); //20 + Rand(50) + rand(50);
				}
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.3 // 0.4
				break;
		}

		// размер имеет значение
		if (pRef.StoreSize == "small")
		{
		    pRef.Goods.(goodName).Quantity = makeint(sti(pRef.Goods.(goodName).Quantity) / 3); // было 2 до 1.2.3
		}
		// 24/01/08
		pRef.Goods.(goodName).Norm            = pRef.Goods.(goodName).Quantity; // колво в начале, это норма магазина на всегда
		pRef.Goods.(goodName).NormPriceModify = pRef.Goods.(goodName).RndPriceModify; // начальная цена - тоже limit стремлений
	}
}

void StoreVoidFill(ref pRef)
{
	string goodName;
	//pRef.StoreSize = "large"; // "small"
	pRef.Island = "";
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		goodName = Goods[i].Name;
		// boal fix -->
		if (CheckAttribute(&Goods[i], "type"))
		{
		    pRef.Goods.(goodName).TradeType = Goods[i].type;
		}
		else
		{ // boal fix <--
			pRef.Goods.(goodName).TradeType = TRADE_TYPE_NORMAL;
		}
		pRef.Goods.(goodName).NotUsed = false;
		pRef.Goods.(goodName).Quantity = 0;
	}
}
