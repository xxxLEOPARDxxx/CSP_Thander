
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = GetNameLugger(PChar, "f");
	string sCharacter = "";

	int iShip = 0;
	int iCrew = 0;
	int iShipSP = 0;
	int iShipHP = 0;

	string sShipName = "";

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ещё раз благодарю за оказанную услугу.";
			link.l1 = "Не стоит благодарности.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Спасибо, Господи!!!";
			link.l1 = "Мое имя " + GetNameLugger(PChar, "f") + "! Я капитан корабля ''" + PChar.Ship.Name + "''. Что с вами случилось?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "Я - капитан " + GetNameLugger(NPChar, "f") + ". Неделю назад мы попали в шторм.";
			link.l1 = "Чёрт вас раздери - наверное это было торнадо!";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "Это был самый ужасный и сильный шторм, который я когда-либо видел на этом архипелаге. А я много повидал, поверьте мне. Три дня нас мотало в этой болтанке, а на исходе четвёртого дня, когда шторм уже пошёл на убыль - треснули сразу две мачты. Матросы даже не успели захватить их - всё мгновенно смыло за борт. Когда этот ужас закончился, мой старпом недосчитался больше половины нашей команды! Несколько дней мы дрейфуем в этих водах. Вы перв"+ GetSexPhrase("ый","ая")+", кого мы повстречали.";
			link.l1 = "Искренне сочувствую вам! Если я могу чем-то помочь...";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "Понимаете, капитан. Мы могли бы уплыть с вами - я думаю, места на вашем корабле хватило бы. Но дело в том, что в трюме моего корабля находится груз, который я должен доставить по назначению. Я не хочу слишком утруждать, но я прошу вас лишь взять моего человека и высадить на ближайшей колонии...";
			link.l1 = "Конечно.";
			link.l1.go = "YesYes";
			link.l2 = "Извините, но ничем не смогу помочь...";
			link.l2.go = "NotNot";
		break;

		case "YesYes":
			ShipWreckInSeaWait();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NotNot":
			ShipWreckInSeaCancel();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "5":
			sCharacter = PChar.GenerateShipWreck.CharacterID;
			SetCameraDialogMode(CharacterFromID(sCharacter));
			dialog.text = GetNameLugger(CharacterFromID(sCharacter), "f") + ": " + GetNameLugger(NPChar, "n") + ", этот пакет ты вскроешь по прибытии на землю. Но не раньше. Там дополнительные инструкции.";
			link.l1 = GetNameLugger(NPChar, "f") + ": Понял, капитан.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInSeaWaitEnd");
		break;

		case "6":
			dialog.text = "Вы давно в капитанах?";
			link.l1 = "О, это давняя история.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "Тогда вы понимаете, что я сейчас испытываю. Пятнадцать лет я плавал на этом корабле, и за какие-то три дня он превратился в оборванную лоханку. Нет ни малейшего шанса отремонтировать его. Когда за нами прибудет судно, мне придётся затопить свой корабль. Я не переживу этого...";
			link.l1 = "Держитесь, " + GetAddress_FormToNPC(NPChar) + ". В жизни случаются вещи гораздо хуже.";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Ну что же, хватит лирики. По прибытию в место назначения мой человек передаст вам " + sti(PChar.GenerateShipWreck.Money) + " золотых. Это всё, чем я могу вознаградить Вас за помощь.";
			link.l1 = "Право, не стоило!";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "Отправляйтесь в путь. Удачи, " + GetNameLugger(PChar, "f") + "!";
			link.l1 = "До свидания.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInSeaWaitEndToSea");
		break;

		case "10":
			dialog.text = "А-а, капитан. Ещё раз спасибо, что взяли нас на борт.";
			link.l1 = "Не стоит благодарности.";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "Позвольте узнать, куда мы плывём?";
			link.l1 = "Я не могу... Чёрт, я не могу!!!";
			link.l1.go = "12";
			link.l2 = "У меня к тебе дело. Я слыша"+ GetSexPhrase("л","ла") +", что в трюме вашего корабля есть некий груз...";
			link.l2.go = "14";
		break;

		case "12":
			dialog.text = "Вы в порядке? Что-то случилось?";
			link.l1 = "Мой штурман уведомит вас о нашем курсе. Обед будет в полдень. Вас позовут.";
			link.l1.go = "exit";
			NextDiag.TempNode = "13";
		break;

		case "13":
			dialog.text = "А-а, капитан. Ещё раз спасибо, что взяли нас на борт.";
			link.l1 = "Не стоит благодарности.";
			link.l1.go = "exit";
			NextDiag.TempNode = "13";
		break;

		case "14":
			dialog.text = "На что это вы намекаете?!";
			link.l1 = "Я бы хотел"+GetSexPhrase("","а")+" узнать, что это за груз. И ты мне в этом поможешь. Либо...";
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = "Либо?";
			link.l1 = "Либо умрешь, прямо здесь и сейчас.";
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = "Двуличная скотина! Защищайся, падаль!";
			link.l1 = "Эх...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBattleWithSailor");
		break;

		case "17":
			dialog.text = "Мерзав" + GetSexPhrase("ец","ка") +"! Что тебе нужно?";
			link.l1 = "Всего лишь ваше золото, " + GetAddress_FormToNPC(NPChar) + " " + GetNameLugger(NPChar, "f") + ".";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "Забирай его. И проваливай к чертям!";
			link.l1 = "Я также заберу вашу жизнь, ведь вы знаете, что мертвые молчат?";
			link.l1.go = "19";
		break;

		case "19":
			dialog.text = "Какую змею я потчевал на своём корабле!";
			link.l1 = "...";
			link.l1.go = "exit";
			PChar.GenerateShipWreck.State = "none";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam");
		break;

		case "20":
			dialog.text = "Вот мы и доплыли. Спасибо, капитан, дальше я сам.";
			link.l1 = "Ну что ж. Удачи тебе.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInTownSuccess");
		break;

		case "21":
			dialog.text = "Кто вы такие?";
			link.l1 = "У меня точно такой же вопрос.";
			link.l1.go = "22";
		break;

		case "22":
			dialog.text = "Я не люблю ждать.";
			link.l1 = "Остынь. Я капитан " + GetNameLugger(PChar, "f") + ".";
			link.l1.go = "23";
		break;

		case "23":
			dialog.text = "И что тебе надо на борту этого корабля?";
			link.l1 = "Я тоже не люблю ждать. Иногда я становлюсь очень раздраженн" + GetSexPhrase("ым","ой") +", поэтому могу принять неверное для тебя решение.";
			link.l1.go = "24";
		break;

		case "24":
			dialog.text = "Якорь мне в глотку. Я штурман этого корабля - " + GetNameLugger(NPChar, "f") + ". Так что тебе нужно здесь?";
			link.l1 = "Хочу поговорить с капитаном.";
			link.l1.go = "25";
		break;

		case "25":
			dialog.text = "Капитан заболел. Во время шторма его накрыл приступ лихорадки. Сейчас я его замещаю.";
			link.l1 = "Неужели? А что это за кровь на палубе?";
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = "Спроси у нашего кока. Он любит резать рыбу прямо на палубе, дышит свежим воздухом.";
			link.l1 = "Понятно. Ну что же, господа, не смею вас задерживать. Удачного вам плаванья.";
			link.l1.go = "27";
			link.l2 = "Слушайте меня, жалкие оборванцы...";
			link.l2.go = "36";
			link.l3 = "Ты что меня за дур" + GetSexPhrase("ака","очку") +" держишь?";
			link.l3.go = "45";
			link.l4 = "Я не морской патруль, но я ненавижу предателей. Поэтому лучше вам умереть - живых я лично прикажу повесить вон на той мачте. К оружию, канальи!";
			link.l4.go = "41";
		break;

		case "27":
			dialog.text = "Постой. Как видишь, корабль наш попал в шторм. Цельная парусина и штабель досок нам бы не помешали. Что скажешь?";

			if(GetCargoGoods(PChar, GOOD_PLANKS) > 0 || GetCargoGoods(PChar, GOOD_SAILCLOTH) > 0)
			{
				link.l1 = "Бесплатно - только в раю.";
				link.l1.go = "28";
			}

			link.l2 = "Я же сказал"+GetSexPhrase("","а")+" - до свидания.";
			link.l2.go = "35";
		break;

		case "28":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			SetCameraDialogMode(CharacterFromID(sCharacter));
			dialog.text = GetNameLugger(CharacterFromID(sCharacter), "n") + ", сбегай к капитану, одолжи у него кошелёк.";
			link.l1 = "...";
			link.l1.go = "29";
			ShipWreckBandValodyaToMoney();
		break;

		case "29":
			SetCameraDialogMode(NPChar);
			dialog.text = "Не желаешь обмен на товары? У нас в трюме как раз есть груз хорошо оплачиваемого товара.";
			link.l1 = "Предпочитаю звонкую монету.";
			link.l1.go = "30";
		break;

		case "30":
			dialog.text = "Хе-хе.";
			link.l1 = "...";
			link.l1.go = "31";
		break;

		case "31":
			ShipWreckBandValodyaReturnWithMoney();
			dialog.text = "Золото так золото. Сколько можешь передать?";
			link.l1 = "Давай посмотрим.";
			link.l1.go = "32";
		break;

		case "32":
			PChar.GenerateShipWreck.GoodsChange = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchQuicklyTrade();
		break;

		case "33":
			dialog.text = "Закончи"+ GetSexPhrase("л","ла") +"?";
			link.l1 = "Вполне. Груз будет доставлен на шлюпках. И, штурман, я бы посоветова"+ GetSexPhrase("л","ла") +" тебе поменять своё звание на корабле, а коку готовить на камбузе. Морской патруль Его Величества может не понять.";
			link.l1.go = "34";
		break;

		case "34":
			PChar.GenerateShipWreck.GoodsChange.Yes = true;
			dialog.text = "Ха-ха.";
			link.l1 = "Удачного плаванья.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "35":
			PChar.GenerateShipWreck.GoodsChange.Yes = false;
			ShipWreckBanditsOneTypeEnd();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "36":
			dialog.text = "Как ты со мной говоришь, собака?";
			link.l1 = "Я все ещё могу отличить кровь человека. Ни в какой шторм вы не попадали. Не знаю, кто из вас рубил мачты и рвал паруса. А также поджигал эти бочонки с порохом, но он явно был не в своём уме. То, что ваш капитан приболел, расскажете морскому патрулю, который возьмёт вас на абордаж и перевешает как бунтовщиков, на вон той единственной мачте. Так вот, мерзкие крысы, вы хотите жить?";
			link.l1.go = "37";
		break;

		case "37":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "За такие слова я лично вскрою твой желудок.";

			if(sti(PChar.GenerateShipWreck.ToSquadron) == 1)
			{
				SetCameraDialogMode(CharacterFromID(sCharacter));
				link.l1 = GetNameLugger(CharacterFromID(sCharacter), "f") + ": Остынь, " + GetNameLugger(NPChar, "n") + ". У него больше людей и целый корабль.";
				link.l1.go = "38";
			}
			else
			{
				link.l1 = "Ну попробуй, " + LinkRandPhrase("холоп", "недоносок", "слабак") + "!";
				link.l1.go = "41";
			}
		break;

		case "38":
			SetCameraDialogMode(NPChar);
			dialog.text = RandSwear();
			link.l1 = "Я прощаю тебя на первый раз, кусок дерьма. Но если услышу впредь что-либо подобное - брошу на корм акулам.";
			link.l1.go = "39";
		break;

		case "39":
			dialog.text = "Что тебе нужно?";
			link.l1 = "Вы хотите плавать под моим началом?";
			link.l1.go = "40";
		break;

		case "40":
			dialog.text = "Черт побери, конечно! Я слышал о тебе.";
			link.l1 = "У меня два условия. Первое, вы заплатите взнос за вступление под моё начало. И второе, вы прикончите всех пленников из старой команды.";
			link.l1.go = "42";
			link.l2 = "Вы должны прикончить всех пленников из старой команды.";
			link.l2.go = "43";
			link.l3 = "Ха-ха, я пошутил" + GetSexPhrase("","а") +". Удачного плавания!";
			link.l3.go = "35";
		break;

		case "41":
			ShipWreckBanditsStartBattle();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "42":
			if(sti(PChar.GenerateShipWreck.ToSquadronWithMoney) == 1)
			{
				sCharacter = PChar.GenerateShipWreck.ValodyaID;
				PChar.GenerateShipWreck.ValodyaToMoney = true;
				SetCameraDialogMode(CharacterFromID(sCharacter));
				dialog.text = "Мы согласны. " + GetNameLugger(CharacterFromID(sCharacter), "n") + ", ты знаешь что делать.";
				link.l1 = "Понял" + GetSexPhrase("","а") +".";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ShipWreckBandValodyaToMoney");
			}
			else
			{
				dialog.text = "Но у нас нет денег.";
				link.l1 = "В таком случае катитесь подальше. Всего хорошего.";
				link.l1.go = "35";
				link.l2 = "Тогда приготовьтесь к смерти, " + LinkRandPhrase("мрази", "твари", "собаки") + "!";
				link.l2.go = "41";
				link.l3 = "Так и быть - я возьму вас.";
				link.l3.go = "43";
			}
		break;

		case "43":
			PChar.GenerateShipWreck.AddBandaShip = true;
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "Мы согласны. " + GetNameLugger(CharacterFromID(sCharacter), "n") + ", ты знаешь что делать.";
			link.l1 = "Вот и замечательно. А теперь за работу!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "44":
			PChar.GenerateShipWreck.AddBandaShip = true;
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			dialog.text = "Капитан, вот деньги. Здесь ровно " + sti(PChar.GenerateShipWreck.Money) + " пиастров.";
			link.l1 = "Считайте, что вы в моей команде. А сейчас навести порядок на этой лоханке! И, ЖИВО!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "45":
			dialog.text = "Ты это о чём?";
			link.l1 = "Видишь вон тот корабль? Так вот, пикнуть не успеешь, как он сметет все задницы с этой посудины, если со мной что-то случится. А теперь слушай сюда, кусок дерьма. Ты бунтовщик и по закону тебя вздёрнут на вон той мачте. И всю команду вздёрнут. Так вот, что бы спасти свои жалкие душонки, вы заплатите мне. Если через пять минут я не увижу этих денег, то можете заочно молить Господа Бога о пощаде. Но в рай вы ребята явно не попадёте. Время пошло.";
			link.l1.go = "46";
		break;

		case "46":
			dialog.text = "Ты забыл" + GetSexPhrase("","а") +", что находишься здесь, а не в каюте своего корабля. Я запросто проткну тебя насквозь.";
			link.l1 = "Я од" + GetSexPhrase("ин","на") +" из лучших фехтовальщи" + GetSexPhrase("ков","ц") +" на этом архипелаге. А со мной абордажная команда закаленных бойцов. Ржавый палаш вытащить не успеешь, как твоя голова будет кататься по палубе. Усек?";
			link.l1.go = "48";
		break;

		case "47":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "За такие слова я лично вскрою твой желудок.";

			if(sti(PChar.GenerateShipWreck.ToSquadronWithMoney) == 1)
			{
				SetCameraDialogMode(CharacterFromID(sCharacter));
				link.l1 = GetNameLugger(CharacterFromID(sCharacter), "f") + ": Вот деньги, " + GetNameLugger(NPChar, "n") + ", у нас нет выхода.";
				link.l1.go = "49";
			}
			else
			{
				link.l1 = "Ну попробуй, " + LinkRandPhrase("холоп", "недоносок", "слабак") + "!";
				link.l1.go = "41";
			}
		break;

		case "48":
			dialog.text = "...";
			link.l1 = "Прошло три минуты. Я жду.";
			link.l1.go = "47";
		break;

		case "49":
			AddQuestRecord("ShipWreck", "8");
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			SetCameraDialogMode(NPChar);
			dialog.text = "...";
			link.l1 = "Я рад, что вы спасли свои шкуры. Советую поменять этого неудачника, на капитана он мало похож. Прощайте. И молитесь Богу, если я ещё раз вас увижу.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "NewCap_1":
			dialog.text = "Вы спасли нас!";
			link.l1 = "Что здесь произошло?";
			link.l1.go = "NewCap_2";

			iShip = sti(PChar.GenerateShipWreck.ShipWreckIdx);
			iCrew = sti(PChar.GenerateShipWreck.PrisonedCrew);

			sShipName = PChar.GenerateShipWreck.ShipWreckName;
			NPChar.Ship.Type = iShip;
			NPChar.Ship.Name = sShipName;
			SetCrewQuantity(NPChar, iCrew);

			iShipHP = sti(PChar.GenerateShipWreck.ShipHP);

			SetBaseShipData(NPChar);
			NPChar.ship.HP = iShipHP;
			MakeSailDmg(GetCharacterIndex(NPChar.id), 90);
		break;

		case "NewCap_2":
			dialog.text = "Меня зовут " + GetNameLugger(NPChar, "f") + " - я настоящий капитан корабля. Около месяца назад меня абордировало пиратское судно. Я бы не разговаривал с вами сейчас, если бы вовремя не подоспел военный патруль. Мы кое как отбились, а вражеский корабль на всех парусах уплыл. \n Догнать его патрулю не удалось. Я торговец, постоянно перевожу товары. В одном из портов мне пришлось нанять новую команду. Из старых членов осталось не больше тридцати... А теперь нас осталось всего " + sti(PChar.GenerateShipWreck.PrisonedCrew) + " человек. Неделю назад я понял, что нанял отпетых негодяев. \n В одну из ночей, накачавшись ромом, они сбили замок на арсенале и вооружившись, начали громить корабль, попутно убивая всех, кто им встретится. Не знаю, как так получилось, но они сами срубили мачты и подорвали несколько бочечек с порохом. Хорошо, что пробоины были небольшие. Протрезвев, они загнали нас в эту каюту. Что было дальше, вы понимаете сами.";
			link.l1 = "Да, ваши шансы прожить ещё один день, были равны нулю.";
			link.l1.go = "NewCap_3";
		break;

		case "NewCap_3":
			dialog.text = "Как вас зовут?";
			link.l1 = GetNameLugger(PChar, "f") + ", капитан корабля ''" + PChar.Ship.Name + "''.";
			link.l1.go = "NewCap_4";
		break;

		case "NewCap_4":
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			dialog.text = GetNameLugger(PChar, "n") + ", я благодарю вас за спасение. Возьмите эти " + sti(PChar.GenerateShipWreck.Money) + " золотых, в знак большого уважения.";
			link.l1 = "Я сделал" + GetSexPhrase("","а") +" это из благородных побуждений. Скажите, что вы собираетесь делать дальше?";
			link.l1.go = "NewCap_5";
		break;

		case "NewCap_5":
			if(sti(PChar.GenerateShipWreck.ToSquadron) == 1)
			{
				dialog.text = "Я предлагаю вам взять мой корабль в эскадру. Вы доказали свою честность.";

				if(GetCompanionQuantity(PChar) < 5)
				{
					link.l1 = "Почему бы и нет. С удовольствием.";
					link.l1.go = "NewCap_6";
				}

				link.l2 = "К сожалению, я не могу взять вас в свою эскадру. Удачи вам.";
				link.l2.go = "NewCap_7";
			}
			else
			{
				dialog.text = "До ближайшей колонии не так далеко - мы доплывём сами. Еще раз спасибо вам, капитан.";
				link.l1 = "До свидания.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ShipWreckBanditsNewCapNoAdd");
			}
		break;

		case "NewCap_6":
			dialog.text = "Благодарю вас, капитан. Надеюсь, мы с вами сработаемся.";
			link.l1 = "Не сомневаюсь.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsNewCapAdd");
		break;

		case "NewCap_7":
			dialog.text = "Очень жаль. Придётся добираться своим силами.";
			link.l1 = "До свидания.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsNewCapNoAdd");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
