#define PRICE_TYPE_BUY	0
#define PRICE_TYPE_SELL	1

#define CONTRA_SELL		1
#define CONTRA_BUY		2

#event_handler("NextDay","StoreDayUpdateStart");
#event_handler("EvStoreDayUpdate","StoreDayUpdate");

// Lugger -->
void SetStoreGoodsEdition(ref _refStore,int _Goods,int _Quantity, int iAddQuantity, bool bDelete)
{
	string tmpstr = Goods[_Goods].name;
	_refStore.Goods.(tmpstr).Quantity = _Quantity;

	if(CheckAttribute(_refStore, "StoreHouse"))
	{
		int iWeight = GetGoodWeightByType(_Goods, iAddQuantity);

		/*
		Log_TestInfo("Перегрузка со склада/на склад.");
		Log_TestInfo("ТОВАР: " + Goods[_Goods].name + "; NUM: " + _Goods);
		Log_TestInfo("КОЛ-ВО: " + iAddQuantity + "; ВЕС: " + iWeight);
		Log_TestInfo("ЗАГРУЖЕНО ДО ЭТОГО: " + makeint(_refStore.current_weight) + ";");
		*/

		if(bDelete)
		{
			_refStore.current_weight = makeint(_refStore.current_weight) - iWeight;
		}
		else
		{
			_refStore.current_weight = makeint(_refStore.current_weight) + iWeight;
		}

		// Пределы, что не больше и не меньше
		if(makeint(_refStore.current_weight) >= makeint(_refStore.max_weight))
		{
			_refStore.current_weight = makeint(_refStore.max_weight);
		}

		if(makeint(_refStore.current_weight) < 0)
		{
			_refStore.current_weight = 0;
		}

		//Log_TestInfo("ЗАГРУЖЕНО ПОСЛЕ ЭТОГО: " + makeint(_refStore.current_weight) + ";");
	}
}
// Lugger <--

void SetStoreGoods(ref _refStore,int _Goods,int _Quantity)
{
	string tmpstr = Goods[_Goods].name;
	_refStore.Goods.(tmpstr).Quantity = _Quantity;
}

void AddStoreGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) {q = sti(refGoods.Quantity);}
	refGoods.Quantity = q +_Quantity;
}

void RemoveStoreGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) q = sti(refGoods.Quantity);
	if(q<_Quantity) {refGoods.Quantity = 0;}
	else {refGoods.Quantity = q - _Quantity;}
}

int GetStoreGoodsQuantity(ref _refStore,int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	int q = 0;
	if( CheckAttribute(_refStore,"Goods."+tmpstr) )
		q = sti(_refStore.Goods.(tmpstr).Quantity);
	return q;
}

int GetContrabandGoods(ref _refStore, int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	if( CheckAttribute(_refStore,"Goods."+tmpstr+".canbecontraband") )
	{
		return sti(_refStore.Goods.(tmpstr).canbecontraband); // 1 or 2
	}
	return 0;
}

int GetStoreGoodsPrice(ref _refStore, int _Goods, int _PriceType, ref chref, int _qty)
{
	if(CheckAttribute(_refStore, "StoreHouse"))
	{
		return 0;
	}
	//if (CheckAttribute(pchar,"ContraInter")) Log_TestInfo(pchar.ContraInter);
    //else Log_TestInfo("Нет атрибута ContraInter");
	float _TradeSkill = GetSummonSkillFromNameToOld(pchar,SKILL_COMMERCE); // 0..10.0
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	int basePrice = MakeInt(Goods[_Goods].Cost);
		if (!CheckAttribute(_refStore,"Goods."+tmpstr) ) return 0;
	makearef(refGoods,_refStore.Goods.(tmpstr));
 	int tradeType = MakeInt(refGoods.TradeType);
	float tradeModify = 1.0;

	switch (tradeType)
	{
		case TRADE_TYPE_EXPORT:
			tradeModify = 0.55 + stf(refGoods.RndPriceModify); //0.55	+r0.1
			break;
		case TRADE_TYPE_NORMAL:
			tradeModify = 0.85 + stf(refGoods.RndPriceModify); //0.85	+r0.15
			break;
		case TRADE_TYPE_IMPORT:
			tradeModify = 1.2 + stf(refGoods.RndPriceModify); //1.2		+r0.2	//1.2 + r0.15
			break;
		case TRADE_TYPE_AGGRESSIVE:
			tradeModify = 1.5 + stf(refGoods.RndPriceModify); //1.8		+r0.25	//1.5 + r0.2
			break;
		case TRADE_TYPE_CONTRABAND:
			tradeModify = 1.8 + stf(refGoods.RndPriceModify); //2.4		+r0.35	//1.8 + r0.2
			break;
		case TRADE_TYPE_AMMUNITION:
			//return basePrice; делаю все тоже, что и длz нормального товара, а тип нужен, чтоб на корабле не скупали лишнее.
			tradeModify = 0.85 + stf(refGoods.RndPriceModify);
			break;
		case TRADE_TYPE_CANNONS:
			tradeModify = 0.85 + stf(refGoods.RndPriceModify); //0.8
			break;
	}

	float skillModify;
	if(_PriceType==PRICE_TYPE_BUY)
	{
		skillModify = 1.46 - _TradeSkill*0.019; // boal 20.01.2004
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify -= 0.2; }
		else
		{
			if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.1; }
		}
		if(CheckOfficersPerk(chref,"Trader"))	{ skillModify -= 0.05; }
		if(tradeType == TRADE_TYPE_CANNONS) skillModify *= 1.3;//цены пушек меняем после применения перков, иначе непропорционально их влияние на итог
	}
	else
	{
		skillModify = 0.69 + _TradeSkill*0.019; // boal
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	skillModify += 0.05;
		if(CheckOfficersPerk(chref,"Trader"))	{ skillModify += 0.05; }
		if(tradeType == TRADE_TYPE_CANNONS) skillModify /= 1.3;
	}

	// boal 23.01.2004 -->
	if (MakeInt(basePrice*tradeModify*skillModify + 0.5) < 1) return 1;
	// boal 23.01.2004 <--
	if(CheckAttribute(pchar,"Goods.Store.Contraband")) return MakeInt(basePrice*tradeModify*skillModify*_qty  + 0.5);

    return MakeInt(basePrice*tradeModify*skillModify*_qty  + 0.5);
}

// обратное преобразование цены в RndPriceModify
float GetStoreGoodsRndPriceModify(ref _refStore, int _Goods, int _PriceType, ref chref, int _price)
{
	if(CheckAttribute(_refStore, "StoreHouse"))
	{
		return 0.0;
	}
    float skillModify;
	float _TradeSkill = GetSummonSkillFromNameToOld(chref,SKILL_COMMERCE);
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	int basePrice = MakeInt(Goods[_Goods].Cost);
	if (!CheckAttribute(_refStore,"Goods."+tmpstr) ) return 0;
	makearef(refGoods,_refStore.Goods.(tmpstr));
 	int tradeType = MakeInt(refGoods.TradeType);

	float tradeModify = 1.0;

    if(_PriceType==PRICE_TYPE_BUY)
	{
		skillModify = 1.46 - _TradeSkill*0.019;
		if(CheckOfficersPerk(chref,"Trader"))	{ skillModify -= 0.05; }
		if(CheckOfficersPerk(chref,"AdvancedCommerce"))	{ skillModify -= 0.2; }
		else
		{
			if(CheckOfficersPerk(chref,"BasicCommerce"))	{ skillModify -= 0.1; }
		}
	}
	else
	{
		skillModify = 0.69 + _TradeSkill*0.019;
		if(CheckOfficersPerk(chref,"Trader"))	{ skillModify += 0.05; }
		if(CheckOfficersPerk(chref,"AdvancedCommerce"))	skillModify += 0.05;
	}
	tradeModify = makefloat(_price) / (basePrice*skillModify);

	switch (tradeType)
	{
		case TRADE_TYPE_EXPORT:
			tradeModify = tradeModify - 0.55; //0.55;
			break;
		case TRADE_TYPE_NORMAL:
			tradeModify = tradeModify - 0.85;
			break;
		case TRADE_TYPE_IMPORT:
			tradeModify = tradeModify - 1.2; //1.2;
			break;
		case TRADE_TYPE_AGGRESSIVE:
			tradeModify = tradeModify - 1.5;//почему не -1.5 было, а  просто -0.0???
		break;
		case TRADE_TYPE_CONTRABAND:
			tradeModify = tradeModify - 1.8; //2.4;
			break;
		case TRADE_TYPE_AMMUNITION:
			tradeModify = tradeModify - 0.85;
			break;
		case TRADE_TYPE_CANNONS:
			tradeModify = tradeModify - 0.85;
			break;
	}
	 // может быть минусом, а что делать :(
    return tradeModify;
}
// <--
string GetStoreGoodsType(ref _refStore,int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	int tradeType = TRADE_TYPE_NORMAL;
	if( CheckAttribute(_refStore,"Goods."+tmpstr) ) {
		tradeType = sti(_refStore.Goods.(tmpstr).TradeType);
	}

	switch(tradeType)
	{
	case TRADE_TYPE_NORMAL:
		return TRADE_TYPE_NORMAL_NAME;
		break;
	case TRADE_TYPE_EXPORT:
		return TRADE_TYPE_EXPORT_NAME;
		break;
	case TRADE_TYPE_IMPORT:
		return TRADE_TYPE_IMPORT_NAME;
		break;
	case TRADE_TYPE_CONTRABAND:
		return TRADE_TYPE_CONTRABAND_NAME;
		break;
	case TRADE_TYPE_AMMUNITION:
		return TRADE_TYPE_AMMUNITION_NAME;
		break;
	case TRADE_TYPE_CANNONS:   //new boal
		return TRADE_TYPE_CANNONS_NAME;
		break;
	case TRADE_TYPE_AGGRESSIVE:
		return TRADE_TYPE_AGGRESSIVE_NAME;
		break;
	}
	Trace("Missing trade type");
	return TRADE_TYPE_NORMAL_NAME;
}

bool GetStoreGoodsUsed(ref _refStore,int _Goods)
{
	if(CheckAttribute(_refStore, "StoreHouse"))
	{
		if(CheckAttribute(_refStore,"Goods."+tmpstr))
		{
			return true;
		}
	}
	string tmpstr = Goods[_Goods].name;
	if( !CheckAttribute(_refStore,"Goods."+tmpstr) ) return false;
	if( sti(_refStore.Goods.(tmpstr).NotUsed)==true ) return false;
	if( sti(_refStore.Goods.(tmpstr).TradeType) == TRADE_TYPE_CONTRABAND )
	{	if( !CheckOfficersPerk(GetMainCharacter(),"Trustworthy") ) return false;
	}
	return true;
}

void SetStoresTradeUsed(int StoreNum,int GoodsNum,bool goodsUsed)
{
	string tmpstr = Goods[GoodsNum].Name;
	Stores[StoreNum].Goods.(tmpstr).NotUsed = !goodsUsed;
}

int storeDayUpdateCnt = -1;
void StoreDayUpdateStart()
{
	if(storeDayUpdateCnt >= 0) return;
	storeDayUpdateCnt = 0;
	PostEvent("EvStoreDayUpdate", 30);

	Event("EvSituationsUpdate", "l", 0);   // вызов размазаных вычислений на Нехт?ай
}

void StoreDayUpdate()
{
	if(storeDayUpdateCnt >= 0)
	{
		UpdateStore(&Stores[storeDayUpdateCnt]);
		storeDayUpdateCnt++;
		if(storeDayUpdateCnt >= STORE_QUANTITY) storeDayUpdateCnt = -1;
		PostEvent("EvStoreDayUpdate", 30);
	}
}

void UpdateStore(ref pStore)
{
	if(CheckAttribute(pStore, "StoreHouse"))
	{
		return;
	}
	aref gref, curref;
	makearef(gref, pStore.Goods);
	int delta, oldQty;
	string tmpstr, nsale;
    float rateInc = 0.0;

	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		tmpstr = Goods[i].name;
		if (!CheckAttribute(gref,tmpstr) ) continue;
		makearef(curref, gref.(tmpstr));
        // пересмотр системы 24.01.08. Нова§ - "круги на воде"
        oldQty = sti(curref.Quantity);
        delta = makeint((oldQty - sti(curref.Norm))/7);
        curref.Quantity = oldQty - delta + (rand(2) - 1)*rand(sti(sti(curref.Norm)/100));

		if( sti(pStore.Goods.(tmpstr).TradeType) == TRADE_TYPE_CANNONS )
		{
			curref.Quantity = oldQty - delta + (rand(2) - 1)*rand(sti(sti(curref.Norm) * 3/100));
			if(sti(Goods[i].NotSale) == 1) // 1.2.5 --> старшие калибры не продаем !!!
			{
				curref.Quantity = 0;
				continue;
			}
		}

        if (sti(curref.Quantity) < 0) curref.Quantity = 0;
		if(stf(curref.Norm) > 0.0)
		{
			rateInc = stf(curref.Quantity) / stf(curref.Norm);
		}

		if (abs(rateInc - 1) < 0.015 )
		{  // нормализаци§ врем§ от времени
		    curref.RndPriceModify = curref.NormPriceModify;
		}
		else
		{
			curref.RndPriceModify = AddPriceModify(stf(curref.RndPriceModify), sti(curref.TradeType), rateInc);
		}
	}
}

float AddPriceModify(float curModify, int tradeType, float rateInc)
{
	float fMaxModify = 0.5;
	float fMinModify = -0.3;
	float delta = rand(7)/1000.0; //0.005*frnd();

	switch(tradeType)
	{
		case TRADE_TYPE_IMPORT:
		     fMinModify = -0.4;
             break;

		case TRADE_TYPE_CONTRABAND:
		     fMaxModify = 0.3;
		     fMinModify = -1.5;
             break;
		case TRADE_TYPE_AGGRESSIVE:
			fMinModify = -0.85;
			fMaxModify = 0.15;
			break;
	}
	if (rateInc <= 0.965)
	{
		curModify += delta;
	}
	else
	{
		if (rateInc >= 1.035)
        {
			curModify -= delta;
		}
		/*else
		{
		    if (rateInc >= 1.005)
		    {
		        curModify += delta;
		    }
		    else
		    {
		        if (rateInc <= 0.995)
			    {
			        curModify -= delta;
			    }
		    }
		} */
	}

	if(curModify < fMinModify)
	    curModify = fMinModify;

	if(curModify > fMaxModify)
        curModify = fMaxModify;

	return curModify;
}

int GetProductGoods(int tradeType,bool bLarge, int _i)
{
	// boal 27.01.2004 -->
    int rate = 1;
    if ((_i==GOOD_GOLD) || (_i==GOOD_SILVER) || (_i==GOOD_WEAPON) || (_i==GOOD_MEDICAMENT))//|| i==GOOD_FOOD
	{
	   rate = 6;
	}
	// boal 27.01.2004 <--
    if (!bLarge)
	{
	    rate = rate * 2;
	}
    switch(tradeType)
	{
		// boal 25.01.2004 -->
        case TRADE_TYPE_NORMAL:		return makeint((20 + rand(10)*10) / rate);	break;
        case TRADE_TYPE_AMMUNITION:	return makeint((20 + rand(10)*10) / rate);	break;
		case TRADE_TYPE_EXPORT:		return makeint( (20 + rand(10)*10) / rate);	break;
		case TRADE_TYPE_IMPORT:		return makeint( (10+ rand(6)*10) / rate);	break;
		case TRADE_TYPE_CONTRABAND: return rand(20);	break;
		case TRADE_TYPE_CANNONS:    return rand(15);	break;
		case TRADE_TYPE_AGGRESSIVE:    return makeint( (5 + rand(6)*10) / 2*rate);	break;
		// boal 25.01.2004 <--
	}

	return 0;
}

int GetConsumeGoods(int tradeType,bool bLarge, int _i)
{
	// boal 27.01.2004 -->
    int rate = 1;
    if ((_i==GOOD_GOLD) || (_i==GOOD_SILVER) || (_i==GOOD_WEAPON) || (_i==GOOD_MEDICAMENT))//|| i==GOOD_FOOD
	{
	   rate = 6;
	}
	// boal 27.01.2004 <--
	if (!bLarge)
	{
	    rate = rate * 2;
	}
	switch(tradeType)
	{
		// boal 25.01.2004 -->
        case TRADE_TYPE_NORMAL:		return makeint((20 + rand(10)*10) / rate);	break;
        case TRADE_TYPE_AMMUNITION:		return makeint((20 + rand(10)*10) / rate);	break;
		case TRADE_TYPE_EXPORT:		return makeint((10 + rand(6)*10) / rate);	break;
		case TRADE_TYPE_IMPORT:		return makeint((20+rand(10)*10) / rate);	break;
		case TRADE_TYPE_CONTRABAND: return 50+rand(100);	break;
		case TRADE_TYPE_CANNONS: return rand(14);	break;
		case TRADE_TYPE_AGGRESSIVE:		return makeint((10 + rand(6)*10) / rate);	break;
		// boal 25.01.2004 <--
	}

	return 0;
}

void FillShipStore( ref chr)
{
	ref pRef = &stores[SHIP_STORE];
	// boal все лишнее убрал, просто сбросить RndPriceModify   в 1 и все, тк иначе затаривание будет
	int iQuantity = 0;
	string goodName;

	for(int i = 0; i<GOODS_QUANTITY; i++)
	{
		iQuantity = GetCargoGoods(chr, i);
		SetStoreGoods(pref, i, iQuantity);

		goodName = Goods[i].name;
		pRef.Goods.(goodName).RndPriceModify = 1.0;
	}
}

int FindStore(string sColony)
{
	for(int i = 0; i < STORE_QUANTITY; i++)
	{
		if (Stores[i].colony == sColony)
		{
			return i;
		}
	}
	return -1;
}

void CheckForGoodsSpoil(aref chr)
{
	int iGoodsQ = 0;
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		iGoodsQ = GetCargoGoods(chr, i);
		if(iGoodsQ > 0)
		{
			if(CheckAttribute(&Goods[i], "AfraidWater"))
			{
				if(sti(Goods[i].AfraidWater) > 0)
				{
					iGoodsQ = iGoodsQ - sti(Goods[i].AfraidWater);
					if(iGoodsQ < 0)
					{
						iGoodsQ = 0;
					}
					SetCharacterGoods(chr, i, iGoodsQ);
				}
			}
		}
	}
}

int GetStoreFreeSpace(object refStore)
{
	int iGoodsQ = 0;
	int iWeight = 0;
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		iGoodsQ = GetStoreGoodsQuantity(refStore, i);
		iWeight = iWeight + iGoodsQ * stf(Goods[i].weight);
	}
	return iWeight;
}

// boal -->
string GetGoodsNameAlt(int idx)
{
    string ret;
    int iSeaGoods = LanguageOpenFile("ShipEatGood.txt");
    ret = LanguageConvertString(iSeaGoods, "seg_" + Goods[idx].Name);
    LanguageCloseFile(iSeaGoods);

    return ret;
}
// запоминаем цены в ГГ
void SetPriceListByStoreMan(ref rchar)   //rchar - это колония
{
    ref refStore, nulChr;
    string attr1, sGoods;
    int i, tradeType;
    string tmpstr;
    aref   refGoods;

    nulChr = &NullCharacter;

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];

	if(CheckAttribute(refStore, "StoreHouse"))
	{
		return;
	}
        attr1 = rchar.id; // ветка, где храним цены
        for (i = 0; i < GOODS_QUANTITY; i++)
        {
            sGoods = "Gidx" + i;

        	tmpstr = Goods[i].name;
        	tradeType = 0;
        	if (CheckAttribute(refStore,"Goods."+tmpstr))
        	{
        	   makearef(refGoods, refStore.Goods.(tmpstr));
         	   tradeType = MakeInt(refGoods.TradeType);
         	}
            nulChr.PriceList.(attr1).(sGoods).tradeType = tradeType; // тип торговли
            //attr2  = "Buy" + i;
            nulChr.PriceList.(attr1).(sGoods).Buy  = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
            if (tradeType == TRADE_TYPE_CONTRABAND && !bBettaTestMode)
            {
                nulChr.PriceList.(attr1).(sGoods).Buy  = "???";
            }
            //attr2  = "Sell" + i;
            nulChr.PriceList.(attr1).(sGoods).Sell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
            if (tradeType == TRADE_TYPE_CONTRABAND && !bBettaTestMode)
            {
                nulChr.PriceList.(attr1).(sGoods).Sell  = "???";
            }
            //attr2  = "Qty" + i;
            nulChr.PriceList.(attr1).(sGoods).Qty  = GetStoreGoodsQuantity(refStore, i);
            if (tradeType == TRADE_TYPE_CONTRABAND && !bBettaTestMode)
            {
                nulChr.PriceList.(attr1).(sGoods).Qty  = "???";
            }
        }
        nulChr.PriceList.(attr1).AltDate = GetQuestBookDataDigit();
    }
}
// нулим магазин при захвате города эскадрой
void SetNull2StoreMan(ref rchar)
{
    ref refStore;
    int i;
    string tmpstr

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];

        for (i = 0; i < GOODS_QUANTITY; i++)
        {
            tmpstr = Goods[i].name;
        	if( CheckAttribute(refStore,"Goods."+tmpstr) )
        	{
        		refStore.Goods.(tmpstr).Quantity = 0;
            }
        }
    }
}
// делим колво товара - остаток дл§ грабежа rchar - это колони§
void SetNull2StoreManPart(ref rchar, float part)
{
    ref refStore;
    int i;
    string tmpstr

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];

        for (i = 0; i < GOODS_QUANTITY; i++)
        {
            tmpstr = Goods[i].name;
        	if (CheckAttribute(refStore,"Goods."+tmpstr) )
        	{
        		refStore.Goods.(tmpstr).Quantity = makeint(sti(refStore.Goods.(tmpstr).Quantity) / part);
            }
        }
    }
}

// нулим ростовщиков
void SetNull2Deposit(string _city)
{
    if (CheckAttribute(Pchar, "quest.Deposits." + _city))
    {
        Log_Info("Dсе вклады у ростовщика в городе " + GetCityName(_city) + " пропали.");
        DeleteAttribute(Pchar, "quest.Deposits." + _city);
    }
}

// утилиты работы со складом --> ugeen  28.01.10
void SetStorageGoods(ref _refStore,int _Goods,int _Quantity)
{
	string tmpstr = Goods[_Goods].name;
	_refStore.Storage.Goods.(tmpstr).Quantity = _Quantity;
}

void AddStorageGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Storage.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) {q = sti(refGoods.Quantity);}
	refGoods.Quantity = q +_Quantity;
}

void RemoveStorageGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Storage.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) q = sti(refGoods.Quantity);
	if(q<_Quantity) {refGoods.Quantity = 0;}
	else {refGoods.Quantity = q - _Quantity;}
}

int GetStorageGoodsQuantity(ref _refStore,int _Goods)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Storage.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(_refStore,"Storage.Goods."+tmpstr) && CheckAttribute(refGoods,"Quantity"))
	{
		q = sti(_refStore.Storage.Goods.(tmpstr).Quantity);
	}
	return q;
}

int GetStorageUsedWeight(object refStore)
{
	int iGoodsQ = 0;
	int iWeight = 0;
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		iGoodsQ = GetStorageGoodsQuantity(refStore, i);
		iWeight = iWeight + GetGoodWeightByType(i, iGoodsQ)
	}
	return iWeight;
}

int GetStorage(string sColony)
{
	for(int i = 0; i < STORE_QUANTITY; i++)
	{
		if (Stores[i].colony == sColony)
		{
			return i;
		}
	}
	return -1;
}

void UpdateSmugglers()
{
	int max_gold = 500000;
	int increment = 50000;
	if (CheckCharacterPerk(pchar, "UnlimitedContra"))
	{
		max_gold = 1000000
		increment = 100000;
	}
	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama")
		{
			sld = CharacterFromID(colonies[n].id + "_Smuggler");
			if (!CheckAttribute(sld, "SmugglingMoney"))
			{
				sld.SmugglingMoney = max_gold + rand(increment);
				SaveCurrentQuestDateParam("SmugglingMoney"+n);
			}
			else
			{
				if(GetQuestPastDayParam("SmugglingMoney" + n) >= (5 + rand(2)) && sti(sld.SmugglingMoney) < max_gold)
				{
					sld.SmugglingMoney = sti(sld.SmugglingMoney) + increment + rand (increment);
					SaveCurrentQuestDateParam("SmugglingMoney"+n);
				}
			}
		}
	}
}

// <-- ugeen
void ChangeImport()
{
	string goodName;
	//pRef.StoreSize = "large"; // "small"
	ref pRef;
	int iType;

	//Границы перегода на другой тип
	int gModifierExport,gModifierImport;

	for(int i=0; i<STORE_QUANTITY; i++)
    {
		if(GetQuestPastDayParam("ChangeImport"+i) >= (5 + rand(2)))
		{
			pRef = &Stores[i];
			if(pRef.Colony != "Pirates" && pRef.Colony != "none" && pRef.Colony != "Panama")
			{
				int contraband = 0;
				int export = 0;
				int import = 0;
				int aggress = 0;
				for (int j = 0; j < GOODS_QUANTITY; j++)
				{
					goodName = Goods[j].Name;
					if(sti(pRef.Goods.(goodName).TradeType) == 3)
					{
						contraband++;
					}
					if(sti(pRef.Goods.(goodName).TradeType) == 1)
					{
						export++;
					}
					if (pRef.Goods.(goodName).TradeType == "2" || pRef.Goods.(goodName).TradeType == "3" || pRef.Goods.(goodName).TradeType == "6")
					{
						import++;
					}
					if (pRef.Goods.(goodName).TradeType == "6")
					{
						aggress++;
					}
				}
				for (j = 0; j < GOODS_QUANTITY; j++)
				{
					if(j > 34 && j < 51) continue;
					if (j == 32) continue;
					goodName = Goods[j].Name;

					gModifierExport = sti(sti(Goods[j].Norm)*0.6);
					gModifierImport = sti(sti(Goods[j].Norm)*0.3);

					switch(sti(pRef.Goods.(goodName).TradeType))
					{
						case TRADE_TYPE_NORMAL:
							if (rand(1) == 0)
							{
								pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*1.2);
							}
							else
							{
								pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*0.8);
							}
						break;
						case TRADE_TYPE_EXPORT:
							pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*0.9);
						break;
						case TRADE_TYPE_IMPORT:
							pRef.Goods.(goodName).Quantity =  sti(sti(pRef.Goods.(goodName).Quantity)*1.1);
						break;
						case TRADE_TYPE_CONTRABAND:
							pRef.Goods.(goodName).Quantity =  sti(sti(pRef.Goods.(goodName).Quantity)*1.3 + rand(50));
						break;
						case TRADE_TYPE_AGGRESSIVE:
							pRef.Goods.(goodName).Quantity =  sti(sti(pRef.Goods.(goodName).Quantity)*1.2);
						break;
					}
					if (j < 11)
					{//Расходники восстанавливаются чуток быстрее
						if (sti(pRef.Goods.(goodName).Quantity) < 250 * sti(Goods[j].Units))
						{
							pRef.Goods.(goodName).Quantity = sti(pRef.Goods.(goodName).Quantity) + rand(100 * sti(Goods[j].Units));
						}
					}
					int goodsQty = sti(pRef.Goods.(goodName).Quantity));

					if(i == 3 || i == 4 || i == 10 || i == 19)
					{
						iType = rand(2);
						if (aggress == 0)
						{
							aggress = -2;
						}
						if (i == 4 && CheckAttribute(pchar,"Whisper.Contraband") &&  j == GOOD_EBONY)
						{
							continue;
						}
					}

					else
					{
						iType = rand(1);
					}
					//импорт
					if (j > 10 && goodsQty < gModifierImport && pRef.Goods.(goodName).TradeType != "2" && pRef.Goods.(goodName).TradeType != "3" && pRef.Goods.(goodName).TradeType != "6")
					{
						if (sti(pRef.Goods.(goodName).TradeType) != 1)
						{
							if (import < 9 || goodsQty < gModifierImport/3)
							{
								import++;
								if(j == 33 || j == 34)
								{
									pRef.Goods.(goodName).TradeType = 2;
									//iImport--;
									pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*0.2);
								}
								else
								{
									if(iType == 0)
									{
										if (aggress < 1)
										{
											pRef.Goods.(goodName).TradeType = 6;
											aggress++;
										}
										else
										{
											if(contraband > 3)
											{
												pRef.Goods.(goodName).TradeType = 2;
												//iImport--;
											}
											else
											{
												pRef.Goods.(goodName).TradeType = 3;
												contraband++;
											}
										}
									}
									if(iType == 1)
									{
										if(contraband > 3)
										{
											if (aggress < 1)
											{
												pRef.Goods.(goodName).TradeType = 6;
												aggress++;
											}
											else
											{
												pRef.Goods.(goodName).TradeType = 2;
												//iImport--;
											}
										}
										else
										{
											pRef.Goods.(goodName).TradeType = 3;
											contraband++;
										}
									}
									pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*0.3);
								}
							}
							else
							{
								pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*1.2);
								pRef.Goods.(goodName).TradeType = 0;
							}
						}
						else
						{
							pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*1.5);
							pRef.Goods.(goodName).TradeType = 0;
						}

					}
					//норма
					if (goodsQty > gModifierImport && goodsQty < gModifierExport)
					{
						if (pRef.Goods.(goodName).TradeType == "2" || pRef.Goods.(goodName).TradeType == "3" || pRef.Goods.(goodName).TradeType == "6")
						{
							if(goodsQty > gModifierImport*1.3)
							{
								pRef.Goods.(goodName).TradeType = 0;
								import--;
							}
						}
						if (pRef.Goods.(goodName).TradeType == "1")
						{
							pRef.Goods.(goodName).TradeType = 0;
							if (sti(pRef.Goods.(goodName).Quantity) < gModifierImport*1.5)
							{
								pRef.Goods.(goodName).Quantity = gModifierExport/2;
							}
							export--;
						}
					}
					//экспорт
					if (goodsQty > gModifierExport)
					{
						if (sti(pRef.Goods.(goodName).TradeType) == 0)
						{
							if (export < 5)
							{//если не много экспортов
								pRef.Goods.(goodName).TradeType = 1;
								pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*2 + rand(sti(sti(pRef.Goods.(goodName).Quantity))));
								export++;
							}
							else
							{
								if (goodsQty > gModifierExport * 1.7)
								{//если экспортов достаточно, но товара слишком много, чтоб игнорить
									pRef.Goods.(goodName).TradeType = 1;
									pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*2 + rand(sti(sti(pRef.Goods.(goodName).Quantity))));
									export++;
								}
								else
								{
									pRef.Goods.(goodName).Quantity = sti(sti(pRef.Goods.(goodName).Quantity)*0.9);
								}
							}
						}
						else
						{
							if (sti(pRef.Goods.(goodName).TradeType) != 1)
							{
								pRef.Goods.(goodName).Quantity = gModifierExport * 0.9;
							}
						}
					}

					//Log_TestInfo("Обновление цен в" + " " + pRef.Colony + "_" + goodName + "_" + pRef.Goods.(goodName).TradeType);
					switch(sti(pRef.Goods.(goodName).TradeType))
					{
						case TRADE_TYPE_NORMAL:
							pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15;
						break;
						case TRADE_TYPE_EXPORT:
							pRef.Goods.(goodName).RndPriceModify = frnd() * 0.1;
						break;
						case TRADE_TYPE_IMPORT:
							pRef.Goods.(goodName).RndPriceModify = frnd() * 0.20;
						break;
						case TRADE_TYPE_CONTRABAND:
							pRef.Goods.(goodName).RndPriceModify = frnd() * 0.35;
						break;
						case TRADE_TYPE_AGGRESSIVE:
							pRef.Goods.(goodName).RndPriceModify = frnd() * 0.25;
						break;
					}
				}
				// Log_TestInfo("Обновление цен в" + " " + pRef.Colony);
			}
			SaveCurrentQuestDateParam("ChangeImport"+i);
		}
	}
}
