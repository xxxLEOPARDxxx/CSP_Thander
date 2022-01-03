void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

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
		case "Exit_Chinaman_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanSpeaks", 0.5);
			DialogExit();
		break;
		case "Exit_ChiGuard_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanCapSpeaksAgain", 0.5);
			DialogExit();
		break;
		case "Exit_portman":
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.questTemp.Whisper.Portman_Deck = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
			DialogExit();
		break;

		case "First time":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "exit";

			if (npchar.id == "W_ChinamanGuard")
			{

				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Капитан, смотрите какую 'крысу' мы поймали в трюме.";
					Link.l1 = "Проклятье, только бы не ещё один путешественник во времени. Он наш язык хоть понимает?";
					Link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Не то место ты выбрал лучшей жизни. Здесь ситуация ненамного лучше, разве что женщины у нас доступнее. Э-э-э... конечно же я не вас конкретно имел в виду, капитан.";
					link.l1 = "Не мешай мне проводить допрос.";
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Но капитан\nЭх, ладно.";
					RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 3;
					break;
				}
			}
			if (npchar.id == "W_Chinaman")
			{

				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Понимаю.";
					Link.l1 = "И как же тебя звать?";
					Link.l1.go = "ChinamanSpeak_1";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Какое-то время все идти так, как нам и обещали. Мы долго плыть на запад, минуя множество стран и народов, неизвестных в нашей стране.  Хотя еда которой нас снабжали быть однообразной, радость переполняла нас. Мы дойти до страны песков края мира, который смутно описывал великий адмирал, и пойти даже дальше. Однако, некоторые из нас начать болеть, терять зубы, даже умирать, хотя путешествие не было тяжелым\nКогда мы наконец добраться, голландцы приняли нас не так, как мы того ожидать. Наши корабли отправлять по одному в уединенную бухту. Я заподозрил неладное и приказал команде подготовиться к бою. Но все быть решено уже задолго до этого. Голландцы намочить наш порох, так что наша команда не смогла окачать должного сопротивления. Голландцы отобрать корабль, а меня и команду сделать рабом.";
					Link.l1 = "Суровая история. Меня примерно также здесь приняли.";
					Link.l1.go = "ChinamanSpeak_1_1";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Спасибо капитан, я не забыть этого.";
					GiveItem2Character(npchar, "blade9");
					EquipCharacterByItem(npchar, "blade9");
					LAi_SetImmortal(NPChar, false);
					Link.l1 = "Очень на это надеюсь.";
					Link.l1.go = "ChinamanOff";
					npchar.quest.meting = 3;
					break;
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Portman_Cabin":
			dialog.Text = "Ты, девушка, совсем страх потеряла? Какого чёрта ты на меня напала?";
			Link.l1 = "Ты знаешь кое-что, что меня интересует. Координаты острова, где зарыт клад.";
			Link.l1.go = "Portman_Cabin_1";
		break;
		case "Portman_Cabin_1":
			dialog.Text = "А... Я всё того вора, что обчистил мой схрон на Бермудах. У тебя еще хватило наглости заявляться прямо ко мне? Ничего ты от меня не узнаешь!";
			Link.l1 = "Тогда я сама всё найду, как с тобой закончу!";
			Link.l1.go = "Portman_Cabin_fight";
		break;
		case "Portman_Cabin_fight":
			//AddQuestRecord("WhisperQuestline", "8");
			//CloseQuestHeader("WhisperQuestline");
			//SetFunctionNPCDeathCondition("Whisper_Portman_Cabin_Is_Dead", npchar.id, false);
			pchar.questTemp.Whisper.KilledPortman = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			//AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Portman":
			dialog.Text = "Приветствую, прекрасная незнакомка.";
			Link.l1 = "Здравствуйте, капитан.";
			Link.l1.go = "Portman_1";

			if (CheckAttribute(pchar, "Whisper.BetrayChard"))
			{
				dialog.Text = "Ну как, этот наглый пират получил заслуженное наказание?";
				Link.l1 = "Ещё нет.";
				Link.l1.go = "exit";
				if (CheckCharacterItem(pchar, "Bible"))
				{
					Link.l1 = "А как же. Вот твоя библия.";
					Link.l1.go = "Portman_betray_chard_1";
					pchar.Whisper.GotPortmanAx = true;
				}
			}
		break;
		case "Portman_1":
			NextDiag.TempNode = "Portman_3";
			dialog.Text = "Какими судьбами вас занесло на борт моего судна?";
			//Link.l1 = "Хочу спросить, можно ли обыскать вашу каюту? Дело в том, что мой брат служил у вас и недавно списался на берег, но забыл кое-какие документы.";
			//Link.l1.go = "Portman_enemy";
			Link.l1 = "Хочу предупредить, что ваш тайник на Бермудах найден и ограблен одним пиратом. Этот человек охотится и за другими вашими кладами, если такие у вас есть.";
			Link.l1.go = "Portman_ally";
			Link.l2 = "Просто осматриваюсь. Подумываю приобрести похожий корабль.";
			Link.l2.go = "Portman_2";
		break;
		case "Portman_2":
			dialog.Text = "В таком случае, не буду вам мешать. Только прошу вас, не задерживайтесь, нам скоро пора отплывать.";
			Link.l1 = "Ладно.";
			Link.l1.go = "exit_portman";
		break;
		case "Portman_3":
			dialog.Text = "Прошу не задерживаться, мы скоро отплываем!";
			Link.l1 = "Ладно...";
			Link.l1.go = "exit";
		break;
		case "Portman_ally":
			dialog.Text = "Я в курсе этого. Но имени грабителя не знал, кто это?";
			Link.l1 = "Авантюриста зовут Майкл Чард. Этот глупец послал меня выбить информацию о ваших тайниках.";
			Link.l1.go = "Portman_ally_1";
		break;
		case "Portman_ally_1":
			dialog.Text = "Никогда не слышал такого имени. Ну и неважно. Если это правда он, наверняка у него моя библия. Убей этого Чарда и принеси ее.";
			Link.l1 = "А награда за помощь какая будет?";
			Link.l1.go = "Portman_ally_2";
		break;
		case "Portman_ally_2":
			AddQuestRecord("WhisperChardQuest", "4");
			pchar.Whisper.BetrayChard = true;
			NextDiag.TempNode = "Portman_betray_chard";
			dialog.Text = "С этим не обижу, поверь мне. Ну все, ступай. Когда сделаешь дело, думаю сможешь без проблем меня найти, раз уже сделала это однажды.";
			Link.l1 = "Договорились.";
			Link.l1.go = "exit";
		break;
		case "Portman_betray_chard":
			dialog.Text = "Ну как, этот наглый пират получил заслуженное наказание?";
			Link.l1 = "Ещё нет.";
			Link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				Link.l1 = "Да. Вот твоя библия.";
				Link.l1.go = "Portman_betray_chard_1";
				pchar.Whisper.GotPortmanAx = true;
			}
		break;
		case "Portman_betray_chard_1":
			AddQuestRecord("WhisperChardQuest", "5");
			CloseQuestHeader("WhisperChardQuest");
			TakeItemFromCharacter(pchar, "Bible");
			Log_Info("Вы получили императорский топор");
			GiveItem2Character(pchar, "topor_emperor");
			PlaySound("interface\important_item.wav");
			dialog.Text = "Отлично! Теперь я могу спать спокойно, не боясь что эта падаль опять меня ограбит\nЯ же говорил, что с наградой не обижу. Вот, возьми этот топор. Не спрашивай, откуда я его взял, там таких больше нет. Если он тебе не нравится, можешь продать. Уверен, денег эта штука стоит немалых.";
			Link.l1 = "Вот это да! Спасибо.";
			Link.l1.go = "exit";
		break;

		case "WarDogCap":
			dialog.Text = "Снова ты? Я думал ты давно уже сгинула в стенах инквизиции.";
			Link.l1 = "От меня так просто не избавиться.";
			Link.l1.go = "WarDogCap_1";
		break;
		case "WarDogCap_1":
			dialog.Text = "Как ты меня вообще нашла?";
			Link.l1 = "Твой дружок-инквизитор, Антониу де Соуза, сам устроил эту западню. Твои недавние поступки очень разозлили испанскую корону, де Соуза хотел лично тебя здесь поймать, но я вежливо попросила оказать эту честь мне.";
			Link.l1.go = "WarDogCap_2";
		break;
		case "WarDogCap_2":
			dialog.Text = "Какого чёрта тебе от меня нужно?";
			Link.l1 = "У тебя есть кое-что моё.";
			Link.l1.go = "WarDogCap_2_1";
		break;
		case "WarDogCap_2_1":
			dialog.Text = "Ты про свой костюм? Могу отдать, если позволишь мне уйти.";
			Link.l1 = "Не только костюм, всё моё снаряжение, включая устройство, с помощью которого я телепортировалась сюда.";
			Link.l1.go = "WarDogCap_3";
		break;
		case "WarDogCap_3":
			dialog.Text = "Чего? А, ты про ту бесполезную железку? Так я от неё уже избавился, вместе с остальным барахлом. Только костюм остался.";
			Link.l1 = "Что ты сделал, тупица?! В каком смысле избавился?";
			Link.l1.go = "WarDogCap_4";
		break;
		case "WarDogCap_4":
			dialog.Text = "В том, что больше ты его не увидишь. И я не позволю бабе так с собой разговаривать!";
			Link.l1 = "Да я тебя закопаю, сволочь!";
			Link.l1.go = "WarDogCap_fight";
		break;
		case "WarDogCap_fight":
			AddQuestRecord("WhisperQuestline", "8");
			CloseQuestHeader("WhisperQuestline");

			UnlockAchievement("WhisperLine", 3);

			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.Whisper.NanoCostume = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "DeSouza":
			dialog.Text = "Надо же, какой сюрприз. А я везде тебя искал, Виспер.";
			Link.l1 = "Мне надоело ждать, когда же ты меня найдёшь, так что я сама к тебе пришла.";
			Link.l1.go = "DeSouza_1";
		break;
		case "DeSouza_1":
			dialog.Text = "Храбро, но глупо. Ты хоть представляешь, что я сейчас с тобой сделаю?";
			Link.l1 = "Сомневаюсь, что тебе хватит на это сил, ты еле на ногах стоишь. Могу предложить тебе передышку. Давай немного поговорим.";
			Link.l1.go = "DeSouza_2";
		break;
		case "DeSouza_2":
			dialog.Text = "И о чём же ты хочешь говорить?";
			Link.l1 = "Я прибыла сюда с машиной времени. Это нетипичного вида устройство, вы бы точно его запомнили. Не передавал ли вам Эрнан Эстебан что-то подобное?";
			Link.l1.go = "DeSouza_2_1";
		break;
		case "DeSouza_2_1":
			dialog.Text = "Да, он что-то такое показывал мне в день, когда тебя привёл. Я попросил его поскорее убрать с глаз этот дьявольский предмет, а потом похоронить на дне морском. Не знаю правда, послушал он меня или нет.";
			Link.l1 = "Очень надеюсь, что нет. А вы знаете где можно найти Эстебана?";
			Link.l1.go = "DeSouza_3";
		break;
		case "DeSouza_3":
			dialog.Text = "Если бы! Я тоже хочу это знать. До недавних пор он был образцовым капером, однако в последнее время начал делать непозволительные для слуги Испании поступки. Не представляю, что за муха его укусила\nОн перестал появляться у генерал-губернатора, а его корабль, по слухам, был замечен за грабежами других кораблей Испании. Такое недопустимо, так что генерал-губернатор попросил меня найти его лично и покарать. Этим я и занимаюсь сейчас, а заодно отлавливаю других врагов короны, вроде тебя.";
			Link.l1 = "И что, нет совсем никаких зацепок, где он может быть?";
			Link.l1.go = "DeSouza_4";
		break;
		case "DeSouza_4":
			dialog.Text = "Есть одна, но прежде чем я её назову, позволь и мне задать вопрос. Правда ли ты из будущего?";
			Link.l1 = "Да.";
			Link.l1.go = "DeSouza_5";
		break;
		case "DeSouza_5":
			dialog.Text = "Боже, теперь я вижу - ты не врёшь. Ответь же мне, помнит ли кто-то в будущем обо мне и моём ордене?";
			Link.l1 = "В будущем люди стараются забыть о вашем безумном ордене. Если и вспоминают, то только в негативном ключе, как о рассаднике жестокости и невежества. Всё, чего вы добились - множество смертей и разрушенных жизней.";
			Link.l1.go = "DeSouza_6";
		break;
		case "DeSouza_6":
			dialog.Text = "За такие слова, я тебя\nИ всё же, доля правды в этом есть. Стараясь выполнить волю господа я немало согрешил. Однако я не считаю, что поступал неправильно, иногда грех - это вынужденная мера, чтобы нести добро\nК чёрту людей! Только Господу дано меня судить!";
			Link.l1 = "Я удовлетворила твое любопытство. Твой черёд.";
			Link.l1.go = "DeSouza_7";
		break;
		case "DeSouza_7":
			AddQuestRecord("WhisperQuestline", "7");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			SetTimerCondition("Whisper_WarDog", 0, 0, 7, false);
			dialog.Text = "Я заплатил одной бордельной девице, которую часто посещает "+GetFullName(characterFromId("wl_Pirate_Cap"))+", чтобы она пустила ему в ухо один слух, якобы в бухте на Терксе спрятан клад. Он жадный человек, наверняка должен клюнуть. По моим примерным подсчётам, если всё сработало, он должен объявиться там через неделю.";
			Link.l1 = "Коварный и жестокий план, как раз в стиле инквизиции.";
			Link.l1.go = "DeSouza_8";
		break;
		case "DeSouza_8":
			dialog.Text = "Пускай же Господь решит, кому из нас двоих суждено его перехватить, а кому отправиться сегодня на суд Божий.";
			Link.l1 = "Аминь.";
			Link.l1.go = "DeSouza_fight";
		break;
		case "DeSouza_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.Whisper.DeSouzaTalked = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "ChinamanSpeak_1":
			dialog.Text = "Лонг Вэй.";
			Link.l1 = "Вижу, далековато тебя забросило от дома. Ты ведь из Японии? Знаешь, у меня когда-то был японский меч...";
			Link.l1.go = "ChinamanSpeak_2";
		break;
		case "ChinamanSpeak_2":
			dialog.Text = "Я прибыть сюда из Китая, провинция Шаньдун.";
			Link.l1 = "Ясно. А по какой причине, вместо того, чтобы находиться в своём Китае, ты оказался у меня на корабле?";
			Link.l1.go = "ChinamanSpeak_3";
		break;
		case "ChinamanSpeak_3":
			dialog.Text = "Это долгий история\nНа родине круглый год идти война. Император постоянно устраивать призыв в армию. Многие мужчины умирать, так и не познав женщина\nЯ служить под началом адмирала Цзян Инь, который управлять тем что осталось от некогда великой флотилии Чжэн Хэ, что совершать семь великих морских путешествий еще два столетия назад. Мне приказать быть капитаном джонки\nОднажды адмирал собрать доверенных офицеров и капитанов, включая меня, и предложить уйти со службы. Уйти не в пираты, а к голландцы, нации мореходов, таких как мы, таких как Чжэн Хе. адмирал сказать, что они ценить хороших моряков. Многие согласились пойти, несогласные умерли. После этого, мы отправиться сюда, на Карибы, в поисках лучшей жизни.";
			Link.l1 = "...";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSpeak_1_1":
			dialog.Text = "Меня перепродавать много раз, пока однажды не отправили служить к этим злым людям, что вы встречать на берегу. Они бить меня и заставлять носить тяжести. Я спрятаться от них в трюме этого корабля.";
			Link.l1 = "Ага, теперь мне всё ясно. Значит ты - беглый раб.";
			Link.l1.go = "ChinamanSpeak_1_2";
		break;
		case "ChinamanSpeak_1_2":
			dialog.Text = "Получаться, что так.";
			Link.l1 = "Меня зацепила твоя история. Могу предложить место в команде. Говоришь, был капитаном? Мне бы не помешал кто-то с твоим опытом, так как я сама в этом ремесле недавно.";
			Link.l1.go = "ChinamanSpeak_1_3";
			Link.l2 = "Тогда твоё место - среди других рабов. Хуан, отведи его в трюм.";
			Link.l2.go = "ChinamanSlave";
		break;
		case "ChinamanSpeak_1_3":
			dialog.Text = "Могу помочь управлять кораблём, а также, я владеть мечом, могу быть телохранителем. ";
			Link.l1 = "В таком случае, Хуан, отдай ему свой клинок. Потом найдёшь себе другой.";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSlave":
			DialogExit();
			ChangeCharacterReputation(pchar, -30);
			AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			npchar.lifeday = 0;
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;

			PlayVoice("interface\_EvEnemy1.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
		case "ChinamanOff":
			DialogExit();
			NPChar.Payment = true;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "GR_longway";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			LAi_SetWarriorType(NPChar);
			SetSelfSkill(NPChar, 25, 25, 25, 25, 25);
			SetShipSkill(NPChar, 15, 15, 20, 20, 40, 15, 15, 15, 15);
			SetSPECIAL(sld, 5, 5, 9, 4, 9, 9, 9);
			NPChar.rank = 6;
			LAi_SetHP(npchar, 120.0, 120.0);
			SetCharacterPerk(NPChar, "ByWorker");
			SetCharacterPerk(NPChar, "ShipSpeedUp");
			SetCharacterPerk(NPChar, "ShipTurnRateUp");
			SetCharacterPerk(NPChar, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней

			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			PlayVoice("interface\_EvShip3.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;

		//Реакции
		case "WhisperIsHere_exit":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_SetPlayerType(pchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
		break;

		case "BS_21_WhisperIsHere":
			dialog.text = "";
			Link.l1 = "Ты как нельзя вовремя! Не знаю, о чем я только думаю, когда лезу в каюты драться с капитанами в одиночку.";
			Link.l1.go = "BS_21_WhisperIsHere_1";
		break;

		case "BS_21_WhisperIsHere_1":
			Pchar.CabinHelp = false;
			dialog.text = "Если хочешь, я буду всегда штурмовать каюты с тобой.";
			Link.l1 = "Да, было бы неплохо.";
			Link.l1.go = "BS_21_WhisperIsHere_2";
			Link.l2 = "Пожалуй, это лишнее.";
			Link.l2.go = "WhisperIsHere_exit";
		break;

		case "BS_21_WhisperIsHere_2":
			Pchar.CabinHelp = true;
			dialog.text = "Договорились.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
	}
}
