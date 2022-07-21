void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank;
	string attr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("Господи, как хорошо, что я вас встретила!",
				"Наконец-то хоть кто-то появился здесь!!",
				"Боже мой, как я рада вас видеть!");
			Link.l1 = LinkRandPhrase("Что случилось, крошка?",
				"Какие проблемы, дорогуша?",
				"Не надо так волноваться, это вредно для женского организма. Расскажи-ка мне быстренько, что там у тебя стряслось?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Моя подруга - такая бесстрашная, она полезла в заброшенный колодец!",
				"Моя подруга полезла в заброшенный колодец, и уже несколько часов её нет!",
				"Моя подруга исчезла в заброшенном колодце!");
			Link.l1 = "Какого чёрта она полезла туда?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Ах, она ничего не боится! Она услышала где-то, что там внизу есть подземелье, в котором можно отыскать золото, вот и полезла. Но я не такая дура, я туда ни ногой...";
			Link.l1 = "И это правильно, нечего тебе там делать.";
			Link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = "Что же мне теперь делать? Прошу вас, ради всего святого, помогите ей!";
			Link.l1 = "Хорошо, я разберусь с этим. А ты иди домой, нечего тут прохлаждаться одной.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Это ваши проблемы, мне до них дела нет. Прощай...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirl.locationId; //флаг для открытия релоада
				object models;
				for (i = 0; i < 10; i++)
				{
					attr = "s" + i;
					models.(attr) = "pirate_" + (i + 1);
				}
				RandomShuffle(&models);
				for (i = 0; i < 3; i++)
				{
					iRank = sti(pchar.rank) - rand(5) + rand(5);
					if (iRank < 1) iRank = 1;
					attr = "s" + i;
					sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, models.(attr), "man", "man", iRank, PIRATE, 1, true));
					SetFantomParamFromRank(sld, iRank, true);
					sld.SaveItemsForDead = true;
					sld.DontClearDead = true;
					sld.money = iRank*200+1000+rand(500);
					LAi_CharacterDisableDialog(sld);
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "quest", "quest" + i);
					LAi_group_MoveCharacter(sld, "CaveBandit");// лесник изменил группу чтобы ядом таино травить можно было
					LAi_group_FightGroups("CaveBandit", LAI_GROUP_PLAYER, true);
					i++;
				}
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1.location = pchar.location;
				pchar.quest.Enc_FriendGirl_afterGang.win_condition = "Enc_FriendGirl_afterGang";
			}
			else
			{ //и правда девка
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, PIRATE, 1, false));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground1";//+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "monsters", "monster"+(rand(9)+1));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterReputation(pchar, -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			//#20200315-01
            npchar.chr_ai.type.checkFight = 999999.0;
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		//#20200315-01
		case "CitizenNotBlade ":
		    npchar.chr_ai.type.checkFight = 999999.0;
            NextDiag.TempNode = "FackYou";
            dialog.text = "Не хочу разговаривать с "+ GetSexPhrase("таким бездушным болваном","такой бездушной девкой") +". Проваливай отсюда!";
			Link.l1 = "Хех, стерва...";
			Link.l1.go = "exit";
		break;
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "Не хочу разговаривать с "+ GetSexPhrase("таким бездушным болваном","такой бездушной девкой") +". Проваливай отсюда!";
			Link.l1 = "Хех, стерва...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Боже мой, как я рада вас видеть!!";
			Link.l1 = "Что случилось, красавица?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1":
            dialog.text = "Я заблудилась здесь! Господи, как же мне было страшно!!!";
			Link.l1 = "Ну, теперь-то всё в порядке. Иди за мной, я выведу тебя. Как окажешься на поверхности - быстро домой, и чтобы больше я тебя не "+ GetSexPhrase("видел","видела") +"!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2":
            dialog.text = "Как скажете, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "Хорошо.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterReputation(pchar, 4);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Надо же, ещё кому-то дело есть до этого подземелья!";
			Link.l1 = "Красавица, ты что тут делаешь?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1":
            dialog.text = "Не твоё дело!";
			Link.l1 = "Ого, ответ на миллион пиастров...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2":
            dialog.text = "На два миллиона... "+ GetSexPhrase("Шёл","Шла") +" бы ты отсюда своей дорогой, до тебя мне дела нет.";
			Link.l1 = "Хех, и мне до тебя тоже, собственно, да вот только подруга твоя панику подняла наверху...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3":
            dialog.text = "Вот ведь дуреха! Сама от страха обделаться готова, и думает, что я такая же.";
			Link.l1 = "Да уж, ты явно не такая же. Чёрт в юбке!";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4":
            dialog.text = "Полегче с эпитетами! Да и вообще, проваливай и дело с концом.";
			Link.l1 = "Ну ладно, раз тебе моя помощь не нужна...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5":
            dialog.text = "Не нужна!";
			Link.l1 = "Тогда прощай и будь здорова.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		case "Underground1_again":
            dialog.text = "Опять ты? Проваливай, надоел"+ GetSexPhrase("","а") +" уже...";
			Link.l1 = "Хм...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
