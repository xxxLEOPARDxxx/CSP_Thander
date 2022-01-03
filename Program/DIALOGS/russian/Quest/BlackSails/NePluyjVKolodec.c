
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "BS_NPVK_1":	//Торговец
			dialog.text = "Капитан, ничего личного, но очень влиятельная особа запретила вести дела с вами. Никаких сделок, извините";
			link.l1 = "Простите, но я не понимаю. Что произошло?";
			link.l1.go = "BS_NPVK_2";
		break;

		case "BS_NPVK_2":
            dialog.text = "Обратитесь к мисс Гатри, она недавно прибыла с Нассау и взяла под контроль сделки с призами. Сам Джекман к ней с поклоном заходит.";
            link.l1 = "Хм. Гатри… Что – то знакомое. Хорошо, до встречи.";
			link.l1.go = "exit";
		break;

		case "BS_NPVK_3":	//Гатри
            dialog.text = "А, вот и наш проблемный капитан! Пришли уладить разногласия? Давайте уладим, но предупреждаю – эти парни с мушкетами здесь не просто так стоят.";
            link.l1 = "Хм. Дело в том, что торговцы в колониях и даже пираты перестали вести со мной дела, говорят, что это вы тому причиной. Могу я поинтересоваться, в чём дело?";
			link.l1.go = "BS_NPVK_4";
		break;

		case "BS_NPVK_4":
            dialog.text = "Дело в вашей неосмотрительности, и как я думаю, в неопытности в делах Нового Света. Позвольте объяснить.";
            link.l1 = "Слушаю вас.";
			link.l1.go = "BS_NPVK_5";
		break;

		case "BS_NPVK_5":
            dialog.text = "Прежний владелец этого магазина, месье Вуазье, был, можно сказать, поверенным нашей семьи. Весь добытый пиратами, а часто и каперами товар, его усилиями, становился вполне легальным и приносил прибыль всем. В том числе и губернаторам и командующим военных эскадр.\n"+
							"И вдруг, некий бравый капитан решает, что ему правила не указ и начинает творить хаос. Деньги, дорог"+ GetSexPhrase("ой","ая") +" мо"+ GetSexPhrase("й","я") +" – любят покой.\n";
            link.l1 = "Ваш 'поверенный' сам, по сути был пиратом и мешал торговле на архипелаге. Ко мне обратился уважаемый торговец от имени сообщества, и я решил"+ GetSexPhrase("","а") +" проблему в меру своих сил и возможностей. Не понимаю, какие у нас с Вами могут быть разногласия?";
			link.l1.go = "BS_NPVK_6";
		break;

		case "BS_NPVK_6":
            dialog.text = "Капитан. Ваш тон я могу списать на неопытность и непонимание сути вещей, но предупреждаю: ещё слово и говорить будет оружие!";
            if (WhisperIsHere())
			{
				link.l1.go = "BS_NPVK_6_WhisperIsHere";
				break;
			}
			link.l1 = "Да кем ты себя возомнила, девка?";	//Драка
			link.l1.go = "Fight_gatri";
			link.l2 = "Давайте сбавим тон и найдём решение наших 'затруднений'.";
			link.l2.go = "BS_NPVK_7";
		break;

		case "BS_NPVK_6_1":
			link.l1 = "Да кем ты себя возомнила, девка?";	//Драка
			link.l1.go = "Fight_gatri";
			link.l2 = "Давайте сбавим тон и найдём решение наших 'затруднений'.";
			link.l2.go = "BS_NPVK_7";
		break;

		case "BS_NPVK_6_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_9_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "Fight_gatri":
			pchar.quest.BS_Fail_Prologue.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BS_Fail_Prologue.win_condition.l1.location = pchar.location;
			pchar.quest.BS_Fail_Prologue.function = "BS_RestoreGatriTrader";

			ChangeCharacterHunterScore(pchar, "enghunter", 200);
			ChangeCharacterHunterScore(pchar, "frahunter", 200);
			ChangeCharacterHunterScore(pchar, "spahunter", 200);
			ChangeCharacterHunterScore(pchar, "holhunter", 200);

			CloseQuestHeader("BSPrologue");
			pchar.questTemp.BlueBird = "declined";//Блокировка ЧП
			string killGatri;
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromID("gatri_grunt"+i);
				LAi_SetImmortal(sld, false);
				killGatri = "l"+i;
				pchar.quest.KillGatri.win_condition.(killGatri) = "NPC_Death";
				pchar.quest.KillGatri.win_condition.(killGatri).character = sld.id;
				pchar.quest.KillGatri1.win_condition.(killGatri) = "NPC_Death";
				pchar.quest.KillGatri1.win_condition.(killGatri).character = sld.id;
				LAi_SetHP(sld, 1000, 1000);

			}
			killGatri = npchar.id;
			LAi_SetImmortal(npchar, false);
			npchar.Dialog.FileName = npchar.beforeGatriFileName;
			npchar.Dialog.CurrentNode = npchar.beforeGatriCurrentNode;
			pchar.quest.KillGatri.win_condition.(killGatri) = "NPC_Death";
			pchar.quest.KillGatri.win_condition.(killGatri).character = npchar.id;
			pchar.quest.KillGatri1.win_condition.(killGatri) = "NPC_Death";
			pchar.quest.KillGatri1.win_condition.(killGatri).character = npchar.id;
			pchar.quest.KillGatri.function = "LockWeapons";
			pchar.quest.KillGatri1.win_condition = "OpenTheDoors";

			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "BS_NPVK_7":
            dialog.text = "600 мер золотой руды. Сразу или частями – на ваш выбор. И мы забудем это недоразумение.";
            if (WhisperIsHere())
			{
				link.l1.go = "BS_NPVK_7_WhisperIsHere";
				break;
			}
			link.l1 = "Сколько?! Да вы в своём уме? Это же невероятно!";
			link.l1.go = "BS_NPVK_8";
		break;

		case "BS_NPVK_7_1":
			link.l1 = "Сколько?! Да вы в своём уме? Это же невероятно!";
			link.l1.go = "BS_NPVK_8";
		break;

		case "BS_NPVK_7_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_10_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "BS_NPVK_8":
            dialog.text = "Именно столько понесла убытков моя семья и её партнёры от вашей выходки. Надеюсь, выгода того стоила?";
            link.l1 = "И как прикажите добывать такое количество золота? Ведь торговцы у вас под каблуком!";
			link.l1.go = "BS_NPVK_9";
		break;

		case "BS_NPVK_9":
            dialog.text = "Вы же грозный пират? Капер? Авантюрист? Неужели оскудели местные моря галеонами? Думайте сами. Срок – один месяц. Иначе все охотники за головами в Новом и Старом свете, вдруг загорятся желанием принести мне вашу голову.";
            link.l1 = "Ну, я пош"+ GetSexPhrase("ёл","ла") +".";
			link.l1.go = "exit";
			AddQuestRecord("BSPrologue", "2");
			pchar.BSPrologue.GatriGold = 600;
			SetTimerCondition("Gatri_Hunters", 0, 0, 30, true);//Отсчет времени до НЗГ
			NextDiag.TempNode = "BS_NPVK_10";
		break;

		case "BS_NPVK_10":	//Гатри, задание сделано не полностью
            dialog.text = "Вы вернулись?";
			if (GetSquadronGoods(Pchar, GOOD_GOLD) > 0)
			{
				link.l1 = "Вот, что мне удалось добыть.";
				link.l1.go = "BS_NPVK_11"
			}
			//SetCharacterGoods(pchar, GOOD_GOLD, 400);//test
			link.l2 = "Уже ухожу.";
			link.l2.go = "exit"
		break;

		case "BS_NPVK_11":
			int ammount = GetSquadronGoods(Pchar, GOOD_GOLD);
			if (sti(pchar.BSPrologue.GatriGold) > ammount)
			{
				RemoveCharacterGoods(Pchar, GOOD_GOLD, ammount);
				pchar.BSPrologue.GatriGold = sti(pchar.BSPrologue.GatriGold) - ammount;
				dialog.text = "Неплохое начало, вам осталось ещё "+pchar.BSPrologue.GatriGold+" мер.";
				link.l1 = "Ну, я пош"+ GetSexPhrase("ёл","ла") +".";
				link.l1.go = "exit";
			}
			else
			{
				RemoveCharacterGoods(Pchar, GOOD_GOLD, sti(pchar.BSPrologue.GatriGold));
				dialog.text = "Вижу, здесь все. На данный момент, наши разногласия улажены. Всегда рада видеть исполнительного и смекалистого добытчика. Заходите ещё!";
				if (CheckAttribute(pchar, "BSPrologue.GatriHunters"))
				{
					link.l1 = "Теперь вы отозвёте своих охотников?";
					link.l1.go = "BS_NPVK_12";
				}
				link.l2 = "До свидания.";
				link.l2.go = "end_quest";
			}
		break;

		case "end_quest":
			SaveCurrentQuestDateParam("BSPrologueEnded");
			AddQuestRecord("BSPrologue", "3");
			CloseQuestHeader("BSPrologue");
			DeleteAttribute(pchar, "BSStart")//Снимаем блокировку торгашей и ежемесячное начисление НЗГ
			pchar.BSInProgress = true;
			//NPChar.Dialog.Filename = "Common_store.c";
			//NPChar.Dialog.CurrentNode = "Second time";
			NextDiag.CurrentNode = "end_quest_loop";
			DialogExit();

			//LAi_CharacterDisableDialog(npchar);
			pchar.quest.BS_End_Prologue.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BS_End_Prologue.win_condition.l1.location = pchar.location;
			pchar.quest.BS_End_Prologue.function = "BS_RestoreGatriTrader";
		break;

		case "end_quest_loop":
			NextDiag.TempNode = "end_quest_loop";
			dialog.text = "Мне от вас пока ничего не нужно, капитан. Можете идти.";
			link.l2 = "Приятно слышать.";
			link.l2.go = "exit";
		break;

		case "BS_NPVK_12":
			dialog.text = "Боюсь, я ничем не смогу помочь, вы сами навлекли на себя эти проблемы. Стоило выполнять моё поручение более расторопно\nДеньги уже давно уплачены, маховик запущен, и охотников нельзя остановить одним лишь щелчком пальцев. Но, я уверена, вы находчивый капитан и сможете выпутаться из любой передряги. Со своей стороны могу лишь пообщещать, что не отправлю к вам новых наёмников.";
			link.l2 = "Мне очень хочется вам нахамить, но, пожалуй, я воздержусь. До свидания.";
			link.l2.go = "end_quest";
		break;
	}
}
