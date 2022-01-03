
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

		case "First time":
			dialog.text = "Что? Кто вы? Что вам от меня нужно?";
			link.l1 = "Простите, что побеспокоил"+ GetSexPhrase("","а") +" вас. До свидания.";
			link.l1.go = "exit";
			link.l2 = "Полегче, полегче. Кто вы такой?";
			link.l2.go = "Next_1";
			LAi_CharacterPlaySound(NPChar, "GR_Kakovi_Merzavczi");
			DeleteAttribute(npchar, "talker");
		break;

		case "Next_1":
            dialog.text = "Меня зовут Альбрехт Цальпфер, но я не имею желания разговаривать с вами.";
            link.l1 = "Ммм... Простите, но мне непонятно, мистер, почему бы нам не поговорить?";
			link.l1.go = "Next_2";
			link.l2 = "О, ну если так, тогда до свидания.";
			link.l2.go = "exit";
		break;

		case "Next_2":
            dialog.text = "Потому что я имею намерение уехать с этого острова, где живут сплошные мерзавцы. Я - голос, который вопиет в пустыне! Никто не хочет слушать меня, никто не хочет вступить в новую эру, йа!";
            link.l1 = "Слушай, ты ничего не потеряешь, если расскажешь мне, что случилось.";
			link.l1.go = "Next_4";
			link.l2 = "А что это за новая эпоха?";
			link.l2.go = "Next_3";
		break;

		case "Next_3":
            dialog.text = "Не будет никакой новой эпохи, никакого прогресса, и всё из-за этих тупоголовых кретинов, у которых недостаточно мозгов, чтобы послушать меня, йа. Я должен выбраться с этого острова, и как можно скорее. Мне противно само пребывание здесь.";
            link.l1 = "Да, очень жаль. Чёрт побери, никакого прогресса - вы только подумайте! Слушай, ты ничего не потеряешь, если расскажешь мне, что случилось.";
			link.l1.go = "Next_4";
		break;

		case "Next_4":
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "Я работал несколько лет на верфи этого негодяя "+sld.name+"а, в качестве помощника. А потом, он уволил меня за то, что я попросил у него рабочих, для того, чтобы осуществить своё последнее изобретение!\n"+
							"Я говорил ему, что это изобретение откроет новую эру в кораблестроении, что это будет настоящая революция, йа! Но меня посадили под замок в ту самую минуту, когда губернатор прослышал, что я затеваю революцию.\n"+
							"Не так давно меня выпустили, но никто не хочет брать меня на работу - и вот, я мыкаюсь тут, без гроша в кармане.";
            link.l1 = "Да, похоже, вас действительно не поняли. Так в чём вы говорите, состоит ваше открытие?";
			link.l1.go = "Next_5";
			link.l2 = "У меня есть идея, мистер. Если вы работали на верфи, то должны знать толк в корабельном деле. Я нанимаю вас в качестве плотника, и вы выберетесь с этого острова, который вам так не нравится.";
			link.l2.go = "Next_6";
		break;

		case "Next_5":
			npchar.lifeday = 0;
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "Ага! Я подозревал! Я предполагал, что вы один из шпионов моего бывшего хозяина-корабела "+sld.name+"а! Я не скажу не слова больше! Сначала, вы сажаете меня в тюрьму, а потом вы хотите ещё и украсть моё изобретение? Вы все просто мерзавцы! Мерзавцы, йа! Я не стану говорить с вами!";
            link.l1 = "Э, приятель, мне приходилось красть раньше, особенно корабли - но идеи? Никогда! И что мне делать с твоими изобретениями - я ничего не смыслю в кораблестроении. Я просто хотел"+ GetSexPhrase("","а") +" узнать...";
			link.l1.go = "Next_7";
		break;

		case "Next_6":
            dialog.text = "ПЛОТНИК? Что я слышу, "+ GetSexPhrase("герр","фрау") +" капитан? Меня, наиболее выдающегося изобретателя нашего столетия, вы хотите нанять в качестве жалкого корабельного ремесленника? Вы в своём... хотя... Я согласен! Мне омерзителен этот жалкий английский островок! Прекрасно! Я просто соберу вещи, и только меня и видели! Я готов, "+ GetSexPhrase("герр","фрау") +" капитан! Где ваш корабль?";
            link.l1 = "В гавани, конечно же, мистер Цальпфер. Я надеюсь, что вы не передумаете, и будете на борту к моменту отплытия.";
			link.l1.go = "Next_8";
		break;

		case "Next_7":
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "Никогда! Вы просто "+ GetSexPhrase("обманщик","обманщица") +", "+ GetSexPhrase("жулик","воровка") +", как и ваш хозяин "+sld.name+", йа! Когда меня выпустили из тюрьмы, я пришёл к этому негодяю, и потребовал вернуть мои чертежи. Но он лишь посмеялся надо мной, и сказал, что он сжёг их. Ха! Но я знаю, знаю, что он забрал их себе, йа, и теперь он хочет выведать саму суть этого изобретения - ну уж нет! Пусть поломает голову! Я не стану с вами разговаривать больше!";
            link.l1 = "Простите, господин изобретатель, но вам следует подумать над конструкцией вашей головы. В ней определенно чего-то не хватает. Всего доброго.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Next_9";
		break;

		case "Next_9":
            dialog.text = "Ха! Это вы! Вы, "+ GetSexPhrase("герр","фрау") +" шпион! Вы хотите украсть секрет моего гениального изобретения - я ничего вам не буду рассказывать!";
            link.l1 = "Э, полегче, полегче. Не больно-то и хотелось с тобой разговаривать. Всего доброго.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Next_9";
		break;

		case "Next_8":
            dialog.text = "Но знайте, я собираюсь покинуть ваш корабль, как только мы доплывём до Порт-Рояла. Мне приходилось слышать, что тамошний губернатор, человек понимающий, и способен оценить всю гениальность моего изобретения.";
            link.l1 = "Несомненно, мистер Цальпфер, а теперь проследуйте на мой корабль.";
			link.l1.go = "Cod_1"
			NextDiag.TempNode = "Pl_1";
		break;

		case "Cod_1":
			SetQuestHeader("ColonyBuilding");
			AddQuestRecord("ColonyBuilding", "0.1");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ColonyBuilding", "sSex1", GetSexPhrase("ся","ась"));
			sld = CharacterFromID("Albreht_Zalpfer")
			LAi_SetLoginTime(sld, 0.0, 24.0);
			DeleteAttribute(sld, "talker");
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*10;
			sld.OfficerWantToGo.DontGo = true;
			sld.rank = 4;
			SetSelfSkill(sld, 5, 40, 5, 5, 5);
			SetShipSkill(sld, 5, 5, 5, 5, 5, 35, 5, 5, 5);
			Pchar.quest.PDM_Albreht_Vhod.win_condition.l1           = "location";
        	Pchar.quest.PDM_Albreht_Vhod.win_condition.l1.location  = "PortRoyal_town";
        	Pchar.quest.PDM_Albreht_Vhod.win_condition              = "PDM_Albreht_Vhod";
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PDM_Albreht_Saditsya_na_korabl", 5);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Pl_1":
            dialog.text = "Я собираюсь покинуть ваш корабль, как только мы доплывём до Порт-Рояла. Мне приходилось слышать, что тамошний губернатор, человек понимающий, и способен оценить всю гениальность моего изобретения.";
            link.l1 = "Да, мистер Цальпфер, я помню.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pl_1";
		break;

		case "Ja_1":
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "Спасибо вам, "+ GetSexPhrase("герр","фрау") +" капитан "+GetFullName(Pchar)+". Вы дали мне шанс вырваться из этого средоточия интриг, и я вам очень признателен.\n"+
							"В залог моей благодарности, я прошу вас принять от меня эти чертежи, раскрывающие суть моего изобретения. В том случае, если до вас дойдут известия о моей смерти, или же если этот негодяй "+sld.name+" попытается присвоить себе право первооткрывателя, я хочу, чтобы эти бумаги оставались только у вас, йа. Любой человек, мало-мальски смыслящий в механике, разберётся в том, что там написано.";
            link.l1 = "Благодарю, Альбрехт, я  "+ GetSexPhrase("был рад","была рада") +" оказать тебе помощь. До свидания.";
			link.l1.go = "Finish";
			AddQuestRecord("ColonyBuilding", "0.2");
			RemovePassenger(pchar, NPChar);
			RemoveCharacterCompanion(pchar, NPChar);
			NextDiag.TempNode = "Ja_2";
		break;

		case "Ja_2":
            dialog.text = "О! Я не могу поверить, "+ GetSexPhrase("герр","фрау") +" капитан, насколько они все глупы! Они просто не СМОГЛИ понять, насколько я гениален, вы себе представляете? Мне следует обратиться в Лондон, в Королевское Научное Общество! Или в Парижскую Академию! Лишь там есть люди, способные по достоинству оценить мой мозг. Йа, мне следует плыть в Англию. Отвезите меня в Англию. Немедленно...";
            link.l1 = "Прости, Альбрехт, но я сейчас не "+ GetSexPhrase("намерен","намерена") +" плыть в Европу. У меня тут много незаконченных дел.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ja_2";
		break;

		case "Finish":
			Log_info("Получены чертежи от Альбрехта Цальпфера.");
			PlaySound("Interface\important_item.wav");
			GiveItem2Character(PChar, "Ship_Print_6");
			AddCharacterSkill(pchar, "Repair", 1);
			Log_SetStringToLog("Починка + 1");
			ChangeCharacterReputation(pchar, 3);
			LAi_SetCitizenType(npchar);
			Pchar.quest.PDM_Albreht_Vihod.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Albreht_Vihod.win_condition.l1.location  = "PortRoyal_town";
        	Pchar.quest.PDM_Albreht_Vihod.win_condition              = "PDM_Albreht_Vihod";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
