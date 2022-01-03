// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "SeekInPortoBello")
			{
				link.l1 = "Послушай, ты не в курсе, никто не ждет здесь прибытия брига 'Восторженный'?";
				link.l1.go = "Romantic_1";
			}

			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Послушай, не видел ли ты капера по имени Франсуа Гонтьер? Он недавно был в вашем городе.";
                link.l1.go = "Portobello_rat_1";
            }

			if (CheckAttribute(pchar, "questTemp.mushket2x2_stid") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "Слушай, Роландо, ты не знаешь, где мне найти Альберта Зиверта - капитана брига 'Стрела'?";
				if (GetQuestPastDayParam("questTemp.mushket2x2_stid") < 11 || GetQuestPastDayParam("questTemp.mushket2x2_stid") > 60)
				{
					link.l1.go = "Mushket_stid";
				}
				else
				{
					link.l1.go = "Mushket_late";
				}
			}

			if (CheckAttribute(pchar, "questTemp.PDM_ONV_PortoBello"))	//Квест "Охота на ведьму"
            {
                link.l1 = "Тебе ни о чём не говорит имя Карла?";
                link.l1.go = "PDM_ONV_PB_1";
            }
		break;

		case "PDM_ONV_PB_1":	//Квест "Охота на ведьму"
			dialog.text = "Мне это имя ни о чём не говорит. Но вам повезло, тот мужчина за столиком не раз произносил это имя, когда в неистовой злобе глотал ром.";
			link.l1 = "Как же ты меня выручил. Спасибо!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
		break;

		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Нет, не знаю. В таверну он не заходил, да и в городе я его не видел.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Гонтьере.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ну что же, будем искать.", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			break;

		case "Mushket_stid":
			dialog.text = "Вот это да!.. Aх-ха-ха! Зачем это тебе понадобился мой лучший друг, знаменитый разбойник Алберто Зиверт?!";
			link.l1 = "Нужен... у меня к нему дело.";
			link.l1.go = "Mushket_stid_1";
			break;

		case "Mushket_stid_1":
			dialog.text = "Да неужели?! Последнего, у кого было к нему 'дело', давно уже крабы доели. Он ни с кем дел не имеет - псих-одиночка, жлоб несчастный. Только контрабандисты его терпят, потому что товар регулярно поставляет. В порты он не заходит - в каждом его одноногая ждет. Даже пираты на него охотятся... А тебя, случайно не Джекмен по его душу послал?";
			link.l1 = "Да нет... Есть у него вещица, которая ему не принадлежит, выкупить хочу...";
			link.l1.go = "Mushket_stid_2";
		break;

		case "Mushket_stid_2":
			dialog.text = "Ха-ха! Да Зиверту даже его собственная шкура не принадлежит - Джекмен поклялся, что снимет, как только его поймает. Хотя нет - 'Стрела' принадлежит ему законно - строил у Алексуса на свои деньги, по своим чертежам.\nСлушай, а не на кораблик ли его ты глаз положил"+ GetSexPhrase("","а") +", а? А то я все думаю - что за 'дело' у тебя к нему! Только учти - Зиверт может запросто пустить тебя на дно, прежде, чем ты спустишь шлюпку. Такие уж у него манеры - сначала стреляет, потом говорит.";
			link.l1 = "Да не нужен мне его бриг! Ты можешь просто сказать - где его найти?";
			link.l1.go = "Mushket_stid_3";
		break;

		case "Mushket_stid_3":
			dialog.text = "Он пират-одиночка, прячется по бухтам, скрытно ходит от острова к острову, нападает внезапно, так что отыскать его непросто... Но не был бы я Каталонским Лисом, если бы не знал, куда он подался! Так что готовь кошель, "+ GetSexPhrase("приятель","подруга") +"!";
			link.l1 = "Та-ак, отлично! И сколько ты хочешь за эту информацию?";
			link.l1.go = "Mushket_stid_4";
		break;

		case "Mushket_stid_4":
			dialog.text = "Сто тысяч золотом, приятель! Сто тысяч золотом - и прямо сейчас.";
			if(makeint(Pchar.money) >= 100000)
			{
				link.l1 = "Сколько?? Да ты что, сдурел - просить такие деньги за два слова?!";
				link.l1.go = "Mushket_stid_nopay";
				link.l2 = "Без проблем, Роландо. Держи свои пиастры.";
				link.l2.go = "Mushket_stid_paymoney";
			}
			link.l3 = "Послушай, но у меня нет таких денег!";
			link.l3.go = "Mushket_stid_nomoney";
		break;

		case "Mushket_stid_nopay":
			dialog.text = "Не считай меня простофилей - его бриг стоит намного дороже. А свою байку про 'вещицу' будешь рассказывать гусыне на заднем дворе таверны - тебе поверит только сын панамского верфиста... Если удастся завладеть бригом - еще благодарить меня будешь. А, если не удастся - покойникам деньги ни к чему, ха-ха-ха...";
			link.l1 = "Ладно, черт с тобой. Держи.";
			link.l1.go = "Mushket_stid_paymoney";
			link.l2 = "Не каркай. Обойдёшься без золота - сам"+ GetSexPhrase("","а") +" найду.";
			link.l2.go = "Mushket_stid_goaway";
		break;

		case "Mushket_stid_nomoney":
			dialog.text = "Ну что ж - видно не судьба тебе достать 'Стрелу'. Подожду, пока моим бывшим приятелем заинтересуется кто-то посолиднее. А ждать, что ты разбогатеешь, смысла нет - он сегодня в одном месте, а завтра в другом... Так что, захочешь - найдешь, если будешь смотреть в оба. А я тебе не помощник.";
			link.l1 = "Ну что, прощай, Роландо. Не напрасно тебя называют пройдохой. Мог заработать немного пиастров, а не заработал - зато много...";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "5");
		break;

		case "Mushket_stid_goaway":
			dialog.text = "Как знаешь. Хозяин - барин. Удачных поисков!";
			link.l1 = "Прощай, Роландо.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "6");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("ся","ась"));
		break;

		case "Mushket_stid_paymoney":
			AddMoneyToCharacter(Pchar, -100000);
			SetMushketCapitainInWorld();
			dialog.text = "О-о, у меня появил"+ GetSexPhrase("ся щедрый приятель","ась щедрая приятельница") +"! Я даже стал подумывать - не продешевил ли я! Ну, да ладно - чего не сделаешь ради бескорыстной дружбы... Теперь слушай: он на днях отправился в бухту под названием " + XI_ConvertString(pchar.questTemp.Mushket.Shore) + ".\nДолго он там не будет - разгрузится и уйдет, так что поторопись. Догнать его ты не сможешь, но застать там долж"+ GetSexPhrase("ен","на") +" еще успеть. Правда, если будешь лететь быстрее ветра, хе-хе... Если нет, то придется потом искать само"+ GetSexPhrase("му","й") +". Я и рад буду тебе помочь, в знак нашей дружбы, но он мне свои маршруты не докладывает.";
			link.l1 = "Спасибо, Лис! Немедленно выдвигаюсь.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "4");
			AddQuestUserData("SeekDoubleMushket","sShore", XI_ConvertString(pchar.questTemp.Mushket.Shore));
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");
		break;

		case "Mushket_late":
			dialog.text = "Aх-ха-ха! Зачем это тебе понадобился мой лучший друг, знаменитый разбойник Алберто Зиверт?!";
			link.l1 = "Нужен... у меня к нему дело.";
			link.l1.go = "Mushket_late_1";
		break;

		case "Mushket_late_1":
			dialog.text = "Ну что я могу сказать... Не свезло тебе, "+ GetSexPhrase("приятель","подруга") +". Приди ты ко мне немного пораньше - я бы поделился с тобой информацией, в какой бухте можно отыскать Зиверта.\nНо теперь поздно - он ушел оттуда, а куда - не ведаю. Так что ищи теперь сам"+ GetSexPhrase("","а") +"... по всему архипелагу. Он может быть где угодно. Хотя можешь попробовать заглянуть попозже, вдруг свезёт?";
			link.l1 = "Вот дьявол! Ладно, раз так - прощай.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "7");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("ся","ась"));
		break;

		case "Romantic_1":
            dialog.text = "Нет, меня никто не спрашивал.";
            link.l1 = "Понятно... Скажи, а комнату кто-нибудь снимает у тебя?";
			link.l1.go = "Romantic_2";
		break;
		case "Romantic_2":
            dialog.text = "Сейчас нет, " + GetAddress_Form(pchar) + ", все пусто.";
            link.l1 = "Ясно... Ну что же, спасибо тебе.";
			link.l1.go = "exit";
			pchar.RomanticQuest = "ToRositaInBeliz";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SetMushketCapitainInWorld()
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 15;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "man", Rank, PIRATE, -1, true));
	sld.name = "Альберт";
	sld.lastname = "Зиверт";
 	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_BRIGQEEN, "Стрела", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade34", "pistol2", 50);
	sld.Ship.Mode = "pirate";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "Shore47"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = "Shore58";
	pchar.questTemp.Mushket.Shore = sld.city;
	Log_TestInfo("Кэп с мушкетом вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Бриг 'Стрела'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
