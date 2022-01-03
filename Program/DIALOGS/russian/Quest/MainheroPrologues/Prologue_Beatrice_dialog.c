void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			pchar.quest.SharpAfterTreasure.win_condition.l1          = "location";
			pchar.quest.SharpAfterTreasure.win_condition.l1.location = "Shore57";
			pchar.quest.SharpAfterTreasure.function                  = "SharpAfterTreasure";
			dialog.text = "Так это ты тот вор, что увел у меня карту.";
			link.l1 = "Какого..!? О чем ты? Я тебя в первый раз вижу, как я мог что-то у тебя украсть?";
			link.l1.go = "2";

			NextDiag.TempNode = "First time";
		break;

		case "2":
			dialog.text = "Ну конечно. Она просто валялась на дороге, а ты ее подобрал. И другую половину тоже, судя по тому, что ты сюда добрался. Так я и поверила.";
			link.l1 = "Слушай, я понятия не имею, с чего ты взяла, что я украл твою карту, но ты ошибаешься. Кстати, а как ты сама сюда попала?";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "Я просто следила за тобой с того момента как узнала, что это ты меня обокрал.";
			link.l1 = "А как ты узнала, что это я украл карту? Просто интересуюсь.";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "Довольно! Я собиралась выпустить тебе кишки, а не трепаться, и теперь я это сделаю!";
			link.l1 = "Черт...";
			link.l1.go = "Exit_fight";
		break;

//grotto - dialog 2

		case "5":
			LAi_SetCurHPMax(npchar);
			LAi_SetPlayerType(PChar);
			dialog.text = "А ты крепкий черт. Почему ты остановился? Давай, покончим с этим!";
			link.l1 = "Если бы я хотел тебя убить, я бы уже это сделал. Чего мне действительно хочется, так это узнать, почему ты решила, что я украл твою карту. И с чего ты взяла, что она вообще твоя.";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "Хорошо, я отвечу. Не так давно я встретила странного человека, который дал мне половину этой чертовой карты, объяснив, что обещал моему отцу это сделать. Однажны утром вскоре после этого кто-то стащил у меня карту, пока я боролась с похмельем в какой-то паршивой таверне. Я весьма настойчиво порасспросила местных, и наконец нашла человека, который рассказал, что видел, как ты разговаривал с трактирщиком и размахивал чем-то весьма напоминающим обрывок карты. Я подумала, что это ты украл мою карту, и что теперь ты ищешь вторую половину. Так что я решила позволить тебе ее найти и проследить, куда она тебя приведет.";
			link.l1 = "Ловко. Но ты ошиблась в одном - хотя я действительно искал вторую половину карты, это была, насколько я понимаю, твоя половина. Мою я к тому времени уже получил, причем таким же образом, как и ты - свою. Твою половину я на самом деле купил у того трактирщика, за совершенно сумасшедшие деньги, кстати. Напомни мне от души поблагодарить его за продажу краденого товара без скидки.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "Но если это правда, то получается, что ты - мой...";
			link.l1 = "Он самый. К твоим услугам, дражайшая сестрица. Жаль, что нам случилось встретиться благодаря такому дурацкому совпадению, но я все равно рад тебя видеть.";
			link.l1.go = "8";
			link.l2 = "Твой брат. Боюсь, теперь мне придется тебя убить - я не имею никакого желания делиться моими сокровищами с кем-либо кроме меня, и, опять же, меня. Пора заканчивать нашу семейную встречу.";
			link.l2.go = "Exit kill";
		break;

		case "8":
			dialog.text = "Хм... Вообще-то, если подумать, все это не похоже на совпадение. Я думаю, что наш отец именно это и планировал - чтобы нам пришлось найти друг друга, чтобы добраться сюда. Наверное, воровство и драку он не планировал, но в остальном все сходится. Особенно то, что он оставил каждому из нас половину карты с именем другого.";
			link.l1 = "Да, похоже ты права. Интересно, хотел ли он, чтобы мы сделали что-то особенное со всем этим золотом. Вряд ли он просто оставил его нам на растрату, хотя такое тоже возможно...";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "Не знаю, может и он и хотел... Но я знаю, зачем он сам собирал это богатство. Понимаешь, тот человек, что передал мне мою половину карты, дал мне еще и отцовский дневник. Похоже, у отца была мечта - создать на Карибах новое государство, свободное от мелочных войн и жадных губернаторов Старого Света, способное построить лучшее будущее для своих граждан. Он называл его Либертанией. Эти деньги предназначались для его создания.";
			link.l1 = "Либертания, говоришь... Большая мечта, это уж точно. Интересно, приблизился ли он к ее воплощению? Кроме того, что собрал здоровенную кучу денег, конечно.";
			link.l1.go = "10";
			link.l2 = "Эти деньги, как и все остальные в этом мире, предназначены моему кошельку. Все, кто считает иначе или убираются с моей дороги, или умирают. Поскольку ты вряд ли уберешься с дороги, придется тебя убить.";
			link.l2.go = "Exit kill";
		break;

		case "10":
			dialog.text = "Не просто приблизился, а почти что воплотил, но его враги сделали все, чтобы люди об этом забыли. 20 лет назад он собрал мощный флот, чтобы захватить колонии, но один из его людей предал все его планы врагам. Флот отца был перехвачен объединенными силами Англии, Франции и Голландии, и уничтожен в тяжелом бою. Наш отец погиб в том бою, и колониальные державы приложили большие усилия к тому, чтобы показать его простым пиратом, которого настигло справедливое возмездие. Но он, похоже, предусмотрел это, и устроил так, чтобы мы с тобой росли в безопасности, вдали друг от друга, и унаследовали его сокровище и мечты, когда мы вырастем, а его дела будут благополучно забыты.";
			link.l1 = "Да, эти канальи здорово постарались. Всю свою жизнь я был уверен, что мой отец - всего лишь известный пират... Подожди, ты сказала 'унаследовали его мечты' - думаешь, он хотел, чтобы мы...";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "Конечно! Он приложил столько усилий для того, чтобы мы встретились здесь и нашли его сокровища и дневник - он наверняка хотел, чтобы мы закончили то, что он начал, воплотили в жизнь его мечту. И эта мечта того стоит! Я не знаю, сумею ли я это сделать, я даже не знаю, возможно ли это вообще, но я, черт возьми, попробую! А ты?";
			link.l1 = "Либертания... Здорово звучит, пусть это и невозможное безумство. Я с тобой, сестрица!";
			link.l1.go = "Exit grotto continue";
			link.l2 = "Ты же не надеешься всерьез вот просто так взять и выкинуть колониальные власти с архипелага, со всеми их деньгами, кораблями и влиянием? Нет, в этом сумасшествии я не желаю принимать никакого участия. Транжирь свою половину сокровищ как тебе вздумается, а я заберу свою.";
			link.l2.go = "Exit half";
			link.l3 = "Надо было сразу тебя убить, тогда мне не пришлось бы слушать этот бред. Пора исправить эту ошибку!";
			link.l3.go = "Exit kill";
		break;

//grotto - dialog 3

		case "12":
			dialog.text = "Знаешь, это приятно - вдруг осознать, что у тебя есть семья...";
			link.l1 = "Да... Слушай, а как вообще создают новые страны?";
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = "Честно говоря, понятия не имею... Но у меня есть на примете кое-кто сведущий в этом деле. В своем дневнике отец часто упоминает некоего Роберта Стаффордшира - он, похоже, был главным советником отца в том, что касалось государственных дел. Я навела о нем справки - оказывается, он до сих пор в добром здравии, и живет на Исла Моне. Я не знаю, поможет ли он нам, но это наш лучший шанс. Я думаю, нам стоит с ним встретиться.";
			link.l1 = "Согласен. Если он помогал отцу, возможно, поможет и нам.";
			link.l1.go = "14";
		break;

		case "14":
			dialog.text = "Тогда я отправлюсь вперед и договорюсь о встрече. Мы будем ждать тебя в таверне Исла Моны.";
			link.l1 = "Договорились.";
			link.l1.go = "Exit grotto end";
		break;

//after advisor quest done

		case "16":
			dialog.text = "Он прав, ты справишься с капитанами лучше меня. Я прекрасно договорюсь с торговцами и ростовщиками, я часто имела с ними дело.";
			link.l1 = "Согласен, я доверяю твоему опыту.";
			link.l1.go = "17";
		break;

		case "17":
			dialog.text = "Тогда я начну готовиться к отплытию прямо сейчас. Нам еще многое нужно сделать. Я вернусь недели через две, но возможны задержки.";
			link.l1 = "Береги себя. Мне бы очень не хотелось тебя потерять.";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "Как мило с твоей стороны, Блэйз. Не думала, что тебя это особенно волнует...";
			link.l1 = "Волнует, и больше, чем ты думаешь. Удачи.";
			link.l1.go = "Exit";
		break;

//boss killed rant

		case "19":
			dialog.text = "Теперь я здесь главная. Есть возражения?";
			link.l1 = "...";
			link.l1.go = "20";
		break;

		case "20":
			dialog.text = "...Нет? Я так и думала. Теперь слушайте, и передайте остальным. Я созываю совет свободных капитанов, здесь, в моей новой резиденции, через две недели. Причину этого я пока оставлю при себе, но поверьте, она по настоящему важна.";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting - autodialog 2

		case "21":
			dialog.text = "Вы собрались, прекрасно. Я не великий оратор, и не собираюсь мучить вас долгими речами. Как вы, вероятно, знаете, мой отец, Николас Шарп, 20 лет назад попытался создать на этих островах Либертанию - новое, свободное государство. Свободное от жадных эксплуататоров Старого Света, свободное от их мелочных войн, весь смысл которых сводится к тому, чтобы тот или иной король получил немного славы и золота. Как вы опять же, возможно, знаете, отец потерпел поражение - один из соратников предал его, и в результате его флот был уничтожен. Но вот чего вы наверняка не знаете, так это того, как чертовски близок отец был к успеху. Сайчас я так же близка к осуществлению его мечты, и предприняла все меры к тому, чтобы не повторить его ошибок, но в одиночку мне не справиться. Мне нужны вы - свободные люди с вашими кораблями, чтобы драться против тех, кто смеет помыкать вами, навязывать вам свои законы и войны. Я не прошу вас умирать под огнем их фортов - нет, то, что мне от вас нужно, далеко не так опасно, но не менее важно для победы. Мне нужно, чтобы вы разрушили их торговые связи, топили конвои, нападали на их патрули. Мне нужно, чтобы вы стали каперами свободы. Я прошу многого, но та награда, та свобода, которую вы можете получить, поистине бесценна. Поэтому я прошу вас - пойдите за мной в тот прекрасный новый мир, который мы создадим!";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting

		case "22":
			dialog.text = "Вы сомневаетесь в Блэйзе, в том, что его мечты реальны. Я скажу вам - если в этой комнате и есть кто-то, кто способен воплощать мечты, то это он. Вы колеблетесь. Я могу вас понять - такие решения нелегко даются. Но подумайте вот о чем: шанс изменить мир - чертовски редкая штука. Очень немногие вообще когда-либо получают такой шанс, и никто, никогда не получает его дважды. Все это, здесь и сейчас - это наш шанс. Что с ним делать - решать вам и только вам. Но я знаю одно - я не упущу свой шанс даже за все золото мира! Я сделала свой выбор, теперь ваш черед!";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting - autodialog 2

		case "23":
			dialog.text = "Господа, вы не пожалеете о вашем решении. Теперь слушайте, нам нужно многое обсудить...";
			link.l1 = "...";
			link.l1.go = "23_exit";
		break;

		case "23_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("captains_long_speak");
		break;

		case "24":
			dialog.text = "(Прошло несколько часов) ...теперь вы знаете, что делать, господа. Сделайте это, и победа будет нашей. Можете идти.";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//after pirate meeting

		case "25":
			dialog.text = "Ну и ну, Блэйз. Ты действительно это сделал! Поздравляю!";
			link.l1 = "Мы сделали, Беатрис, мы. Если бы не твоя великолепная речь, они бы не пошли за мной.";
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = "Ну, если ты настаиваешь. Итак... что ты предлагаешь теперь делать, дорогой сводный братец?..";
			link.l1 = "Вообще-то у меня есть пара интересных идей, если ты не слишком занята...";
			link.l1.go = "27";
		break;

		case "27":
			dialog.text = "Я буду счастлива обсудить эти идеи. Наедине...";
			link.l1 = "Ха, так точно, мэм! В моей каюте или твоей?";
			link.l1.go = "28";
		break;

		case "28":
			dialog.text = "Что-то мне подсказывает, что в этой резиденции, которая, кстати, теперь твоя, должна быть хотя бы одна спальня.";
			link.l1 = "И верно! Предлагаю немедленно ее найти и использовать по назначению!";
			link.l1.go = "Exit";
		break;
//exits

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_fight":
			NextDiag.CurrentNode = "5";
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetCheckMinHP(NPChar, 1, true, "Sharp_Prologue_CheckHP");
			LAi_SetImmortal(NPChar, false);
			DialogExit();
		break;

		case "Exit grotto continue":
			NextDiag.CurrentNode = "hired";
			DialogExit();
			//pchar.questTemp.HiringOfficerIDX = NPChar.index;
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			Npchar.CanTakeMushket = true;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			LAi_SetImmortal(NPChar, false);
			sld.greeting = "Gr_Danielle";
			sld.rank = 5;
			SetSelfSkill(sld, 20, 20, 20, 20, 20);
			SetShipSkill(sld, 20, 20, 20, 25, 20, 20, 20, 20, 20);
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 8);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			sld.quest.meeting = true;
			NPChar.Payment = true;

			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 50000;
			//_location.box1.items.icollection = 1;
			//_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			//_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 10+rand(5);
			_location.box1.items.jewelry2 = 10+rand(5);
			_location.box1.items.jewelry3 = 10+rand(5);
			_location.box1.items.jewelry4 = 5+rand(5);
			_location.box1.items.jewelry6 = rand(25);
			_location.box1.items.jewelry7 = rand(50);
			_location.box1.items.jewelry10 = rand(25);
			_location.box1.items.jewelry14 = rand(25);
			_location.box1.items.jewelry15 = rand(5);
			_location.box1.items.jewelry18 = rand(50);
			chrDisableReloadToLocation = false;

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
		break;

		case "Exit kill":
			LAi_SetWarriorType(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetPlayerType(PChar);
			LAi_SetImmortal(NPChar, false);
			DialogExit();

			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 150000;
			_location.box1.items.icollection = 1;
			_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 20+rand(5);
			_location.box1.items.jewelry2 = 20+rand(5);
			_location.box1.items.jewelry3 = 20+rand(5);
			_location.box1.items.jewelry4 = 11+rand(5);
			_location.box1.items.jewelry6 = rand(50);
			_location.box1.items.jewelry7 = rand(100);
			_location.box1.items.jewelry10 = rand(50);
			_location.box1.items.jewelry14 = rand(50);
			_location.box1.items.jewelry15 = rand(10);
			_location.box1.items.jewelry18 = rand(100);

			pchar.quest.SharpExitFromCave.win_condition.l1 = "NPC_Death";
			pchar.quest.SharpExitFromCave.win_condition.l1.character ="Sharp_Sibling";
			pchar.quest.SharpExitFromCave.function = "SharpExitFromCave";

		break;

		case "Exit half":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 70000;
			//_location.box1.items.icollection = 1;
			_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 10+rand(5);
			_location.box1.items.jewelry2 = 10+rand(5);
			_location.box1.items.jewelry3 = 10+rand(5);
			_location.box1.items.jewelry4 = 5+rand(5);
			_location.box1.items.jewelry6 = rand(25);
			_location.box1.items.jewelry7 = rand(50);
			_location.box1.items.jewelry10 = rand(25);
			_location.box1.items.jewelry14 = rand(25);
			_location.box1.items.jewelry15 = rand(5);
			_location.box1.items.jewelry18 = rand(50);

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			chrDisableReloadToLocation = false;
		break;

		case "Exit grotto end":
			AddDialogExitQuest("Grotto end");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
