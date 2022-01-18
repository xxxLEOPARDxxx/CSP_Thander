
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Не о чем говорить.";
			link.l1 = "Ладно...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_orient":			
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
                LAi_ActorStay(sld);
			}
			LAi_ActorTurnByLocator(npchar, npchar.location.group, npchar.location.locator);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//замечение по обнаженному оружию
		case "CitizenNotBlade":
			dialog.text = "В Дес-Мойнесе не стоит ходить с обнаженным оружием.";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
			NextDiag.TempNode = "DesMoinesCitizen";
		break;

		//бунтующие горожане в Каракасе
		case "CaracasMan":
			dialog.text = "Эй, "+ GetSexPhrase("моряк","девушка") +", тоже хочешь поучаствовать? Лишн"+ GetSexPhrase("им","ей") +" не будешь!";
			link.l1 = "Может, и поучаствую, если ты расскажешь, в чем.";
			link.l1.go = "CaracasMan_1";
		break;
		case "CaracasMan_1":
			dialog.text = "Да тут, в таверне, оборотень засел. Вот, хотим его - ик! - на костерке подогреть, ха-ха!";
			link.l1 = "Да ты пьян, приятель! Иди-ка проспись!";
			link.l1.go = "CaracasMan_2";
		break;
		case "CaracasMan_2":
			dialog.text = "Лопни мои глаза, если вру! А выпил, так для храбрости и на свои! А ты каждый день, что ли, оборотня встречаешь?";
			link.l1 = "Оборотень, говоришь? Ну, и чего вы тогда тут стоите? На костер его!";
			link.l1.go = "CaracasMan_3";
		break;
		case "CaracasMan_3":
			dialog.text = "Так хозяин таверны, каналья, заперся! Вот ребята за бревном - ик! - пошли, дверь ломать!";
			link.l1 = "Э, вы тут с пьяных глаз полгорода разнесете! Ну-ка, пропустите меня, разузнаю, что там за оборотень. А если кто за мной сунется – уши отрежу!";
			link.l1.go = "exit_orient";
			DeleteAttribute(&locations[reload_location_index], "reload.l41.disable");
		break;
		//оборотень в Каракасе
		case "CaracasWervolf":
			dialog.text = "Кто вы и что вам нужно?";
			link.l1 = "Я капитан " + GetFullName(pchar) + ". А вот вы кто? Там, на улице, несколько решительных ребят собираются к вам в гости, и вряд ли затем, чтобы преподнести подарки к Рождеству.";
			link.l1.go = "CaracasWervolf_1";
		break;
		case "CaracasWervolf_1":
			dialog.text = "Они собираются сжечь меня! Но видит Бог, я невиновен! Я бежал из Маракайбо, от страшного проклятья, которое обрушилось на всех жителей нашего города. Капитан! Вы можете мне помочь. Мне необходимо исповедоваться!";
			link.l1 = "Не по адресу, милейший. Я не священник.";
			link.l1.go = "CaracasWervolf_2";
		break;
		case "CaracasWervolf_2":
			dialog.text = "Но вы ведь можете привести сюда священника?";
			link.l1 = ""+ GetSexPhrase("Я погубил столько душ, что помощь в спасении хотя бы одной, пожалуй, мне зачтется.","Хорошо.") +" Ждите здесь, постарайтесь продержаться!";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.MC = "toCaracasPadre";
			iTemp = FindLocation("Caracas_tavern");
			DeleteAttribute(&locations[iTemp], "reload.l1.disable");
			DeleteAttribute(&locations[iTemp], "reload.l4.disable");
			LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
			locations[iTemp].reload.l2.disable = true;
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.dialog.currentnode = "CaracasMan2";  
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorWaitDialog(sld, pchar);
			}
		break;
		//горожане Каракаса на выходе из таверны
		case "CaracasMan2":
			dialog.text = "Ну, что? Оборотень не сбежал?";
			link.l1 = "Вот что, разошлись бы вы по домам! Нет там никакого оборотня!";
			link.l1.go = "exit_orient";
		break;
		//охрана Дес-Мойнеса в бухте
		case "ShoreGuard":
			dialog.text = "Эй, ты! Здесь чужаки не нужны. Убирайся подобру-поздорову!";
			link.l1 = "Может, сотня желтеньких кругленьких цыплят научит тебя кудахтать повежливее?";
			link.l1.go = "ShoreGuard_1";
		break;
		case "ShoreGuard_1":
			dialog.text = "Как бы ты "+ GetSexPhrase("сам не докукарекался, петушок","сама не докудахталась, курочка") +"! Не повернешь назад добром - заставим!";
			link.l1 = "А кто может мне запретить ходить там, где я хочу?";
			link.l1.go = "ShoreGuard_2";
		break;
		case "ShoreGuard_2":
			dialog.text = "Три дюйма стали меж ребер!";
			link.l1 = "Что ж, сравним, чья сталь лучше?";
			link.l1.go = "ShoreGuard_3";
		break;
		case "ShoreGuard_3":
			LocatorReloadEnterDisable("Shore_ship3", "reload1", false);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("MagicCity", "3");
			DialogExit();
		break;
		//жители Дес-Мойнеса обычные
		case "DMCitiz":
			NextDiag.TempNode = "DMCitiz";
			dialog.text = LinkRandPhrase("Что вам нужно у нас в городе?", "Гости в нашем городе появляются очень редко. А вы что хотели?", "Не сказал бы, что мы рады вас приветствовать. Что вам нужно в Дес-Мойнесе?");
			link.l1 = "Посмотреть, как живете...";
			link.l1.go = "DesMoinesCitizen_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase("Будь ты проклят"+ GetSexPhrase("","а") +"! Уходи, пока еще можешь это сделать...", "Давай, беги отсюда, трус"+ GetSexPhrase("","иха") +" несчастн"+ GetSexPhrase("ый","ая") +"...", "Вали отсюда! И чтобы я тебя здесь больше не видел...");
				link.l1 = "Обязательно!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase("Говорят, что вы согласились помочь нам. Удачи вам, капитан...", "Да благословит вас Господь, "+ GetSexPhrase("сеньор капитан","сеньорита") +"!", "Как я желаю, чтобы у вас все получилось!");
				link.l1 = "Обязательно!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = ""+ GetSexPhrase("Сеньор, вы наш спаситель","Сеньорита, вы наша спасительница") +"! Да хранит вас Господь!";
				link.l1 = "Спасибо. Тронут"+ GetSexPhrase("","а") +", тронут"+ GetSexPhrase("","а") +"...";
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesCitizen_1":
			dialog.text = "Все в порядке.";
			link.l1 = "Ну-у, великолепно!";
			link.l1.go = "DesMoinesCitizen_2";
		break;
		case "DesMoinesCitizen_2":
			dialog.text = "Не советую вам задерживаться у нас. Наш городок не очень гостеприимен...";
			link.l1 = "Хм... ну, это как получится.";
			link.l1.go = "exit";
		break;
		//жители Дес-Мойнеса скелеты
		case "DMSkel":
			NextDiag.TempNode = "DMSkel";
			dialog.text = LinkRandPhrase("Проклятие пало на нас!", "Наш город проклят!", "Видите, что с нами происходит? Какое ужасное несчастье!");
			link.l1 = "Да уж...";
			link.l1.go = "DesMoinesSkel_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase("Будь ты проклят"+ GetSexPhrase("","а") +"! Уходи, пока еще можешь это сделать...", "Давай, беги отсюда, трус"+ GetSexPhrase("","иха") +" несчастн"+ GetSexPhrase("ый","ая") +"...", "Вали отсюда! И чтобы я тебя здесь больше не видел...");
				link.l1 = "Обязательно!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase("Говорят, что вы согласились помочь нам. Удачи вам, капитан...", "Да благословит вас Господь, "+ GetSexPhrase("сеньор капитан","сеньорита") +"!", "Как я желаю, чтобы у вас все получилось!");
				link.l1 = "Обязательно!";
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesSkel_1":
			dialog.text = "Раз уж вы увидели весь этот кошмар, то пройдите к нашему главе, Фернандо Торресу. Обязательно переговорите с ним.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", true);
		break;
		//глава городка обычный
		case "DMCitizHead":
			NextDiag.TempNode = "DMCitizHead";
			dialog.text = "Здравствуйте. Зачем пожаловали к нам в Дес-Мойнес?";
			link.l1 = "Да так, посмотреть, что к чему... Скажите, у вас все нормально в городе?";
			link.l1.go = "DMCitizHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = "Уходите! Я не хочу иметь с вами дело.";
				link.l1 = "Хм... ну и зря.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = ""+ GetSexPhrase("Сеньор капитан","Сеньорита") +", как только узнаете что-то новое - сразу прошу уведомлять меня. По сути, вы - наша последняя надежда на нормальную жизнь.";
				link.l1 = "Приложу все усилия для снятия этого ужасного проклятия. Надейтесь!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = "Здравствуйте, капитан! Что скажете?";
				link.l1 = "Я наш"+ GetSexPhrase("ел","ла") +" Элизабет Шеппард.";
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = "Здравствуйте, капитан! Что скажете?";
				link.l1 = "Я отравил"+ GetSexPhrase("ся","ась") +" на поиски галеон 'Королева'. Похоже, что это последний шаг к вашему освобождению.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = "Это вы сняли проклятие? В какой-то момент у нас все нормализовалось!";
				link.l1 = "Да. Я наш"+ GetSexPhrase("ел","ла") +" галеон 'Королева' и все сделал"+ GetSexPhrase("","а") +". Рад"+ GetSexPhrase("","а") +", что сумел"+ GetSexPhrase("","а") +" вам помочь.";
				link.l1.go = "DMHeadOver";
			}
			if (CheckAttribute(pchar, "questTemp.MC.DesMoines"))
			{
				dialog.text = "Сеньор"+ GetSexPhrase("","ита") +", наш"+ GetSexPhrase("","а") +" спаситель"+ GetSexPhrase("","ница") +"! Вы что-то хотели?";
				link.l1 = "Да нет, ничего особенного...";
				link.l1.go = "exit";
			}
		break;
		case "DMCitizHead_1":
			dialog.text = "Все хорошо. А почему вы спрашиваете?";
			link.l1 = "Вы знаете, когда я высадил"+ GetSexPhrase("ся","ась") +" на мысе Несбывшихся надежд, то на меня напали какие-то люди. Совершенно непонятно почему.";
			link.l1.go = "DMCitizHead_2";
		break;
		case "DMCitizHead_2":
			dialog.text = "Ничего не могу вам сказать по этому поводу. Я не в курсе, кто это был.";
			link.l1 = "Понятно... Так, вы говорите, в Дес-Мойнесе все спокойно.";
			link.l1.go = "DMCitizHead_3";
		break;
		case "DMCitizHead_3":
			dialog.text = "Совершенно правильно.";
			link.l1 = "Ну, понятно. Извините...";
			link.l1.go = "exit";
		break;

		case "FoundLiz":
			dialog.text = NPCStringReactionRepeat("Отлично! И что вы выяснили?", 
				"Мы уже говорили об этом, капитан.", 
				"Капитан, мы уже говорили об этом.",
                "Капитан, ну сколько можно?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Элизабет не знает, как и почему было наложено это проклятие. Но ей стало известно, как его снять.", 
				"Да, я помню.",
                "Да, конечно...", 
				"Я так"+ GetSexPhrase("ой","ая") +", настойчив"+ GetSexPhrase("ый","ая") +". Вот думаю, буду одно и то же спрашивать - авось случится чудо! Заклятие спадет, или еще чего-нибудь...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FoundLiz_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FoundLiz_1":
			dialog.text = "Господи, капитан! Надежда принимает очертания реальности! Скажите скорей, как это сделать?";
			link.l1 = "При помощи нефритового черепа ацтеков. Нужно раздобыть его, а Элизабет скажет, что делать дальше.";
			link.l1.go = "FoundLiz_2";
		break;
		case "FoundLiz_2":
			dialog.text = "Капитан, прошу вас, сделайте все, что в ваших силах.";
			link.l1 = "Я и делаю.";
			link.l1.go = "exit";
		break;

		case "DMHeadOver":
			dialog.text = "Спасибо вам огромнейшее! От лица наших граждан с удовольствием уведомляю ваc о том, что мы приготовили вам награду за труды.";
			link.l1 = "Что за награда?";
			link.l1.go = "DMHeadOver_1";
		break;
		case "DMHeadOver_1":
			dialog.text = "Двадцать тысяч пиастров! Может быть для вас это немного, но наш город за проклятое время здорово обеднел, так что это все, что у нас есть.";
			link.l1 = "Да ладно, оставьте эти деньги себе. Они вам сейчас нужней.";
			link.l1.go = "DMHeadOver_2";
			link.l2 = "Я принимаю ваши деньги.";
			link.l2.go = "DMHeadOver_3";
		break;
		case "DMHeadOver_2":
			dialog.text = "Спасибо еще раз. Честно говоря, не ожидал...";
			link.l1 = "Да не за что. Живите счастливо.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 20);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
		break;
		case "DMHeadOver_3":
			dialog.text = "Отлично! Ну что же, всего вам доброго, сеньор"+ GetSexPhrase("","ита") +".";
			link.l1 = "И вам всего наилучшего.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
		break;

		//глава городка скелет
		case "DMSkelHead":
			NextDiag.TempNode = "DMSkelHead";
			dialog.text = "Я уже забыл, когда посреди ночи видел живого человека, а не мерзкого скелета!";
			link.l1 = "Матерь Божья, веселенькое у вас тут местечко! Ради всех святых, что здесь творится?";
			link.l1.go = "DMSkelHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = "Уходите! Я не хочу иметь с вами дело.";
				link.l1 = "Хм... ну и зря.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = ""+ GetSexPhrase("Сеньор капитан","Сеньорита") +", как только узнаете что-то новое - сразу прошу уведомлять меня. По сути, вы - наша последняя надежда на нормальную жизнь.";
				link.l1 = "Приложу все усилия для снятия этого ужасного проклятия. Надейтесь!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = "Здравствуйте, капитан! Что скажете?";
				link.l1 = "Я наш"+ GetSexPhrase("ел","ла") +" Элизабет Шеппард.";
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = "Здравствуйте, капитан! Что скажете?";
				link.l1 = "Я отравил"+ GetSexPhrase("ся","ась") +" на поиски галеона 'Королева'. Похоже, что это последний шаг к вашему освобождению.";
				link.l1.go = "exit";
			}
		break;
		case "DMSkelHead_1":
			dialog.text = "Расскажу, если вы этого желаете! Все равно вы с этой историей далеко не уйдете.";
			link.l1 = "Я не из пугливых, так что нечего меня стращать. Рассказывайте.";
			link.l1.go = "DMSkelHead_2";
		break;
		case "DMSkelHead_2":
			dialog.text = "Как-то причалил к нашему мысу пиратский галеон 'Королева'. Пираты здесь рабов контрабандистам продали. Договариваются между собой...\n"+
				"Продали пираты рабов, а потом у них между собой ссора какая-то вышла. Часть команды здесь осталась, а остальные с капитаном на галеоне в море ушли. С той поры все и началось.";
			link.l1 = "Да что началось? Говорите вы толком!";
			link.l1.go = "DMSkelHead_3";
		break;
		case "DMSkelHead_3":
			dialog.text = "Да вот то, что видите. Днем все люди, как люди, а как солнце сядет - такой вот маскарад. Сообразили, что все из-за пиратов этих, будь они прокляты! И хоть они тоже по ночам скелетами оборачивались, но все равно - всех, кто у нас оставался, в одну прекрасную ночь на костер отправили. Не помогло...";
			link.l1 = "М-да, печальная история...";
			link.l1.go = "DMSkelHead_4";
		break;
		case "DMSkelHead_4":
			dialog.text = "Итак, капитан, вы знаете нашу тайну и наше горе. Вы понимаете, что отныне вам придется разделять их с нами?";
			link.l1 = "В смысле?";
			link.l1.go = "DMSkelHead_5";
		break;
		case "DMSkelHead_5":
			dialog.text = "В том смысле, что Дес-Мойнес вам покидать не разрешается. Огласка никому не нужна.";
			link.l1 = "В мои планы не входит оставаться здесь.";
			link.l1.go = "DMSkelHead_6";
		break;
		case "DMSkelHead_6":
			dialog.text = "Вас сюда честно не пускала охрана на мысе Несбывшихся надежд. Но вы все равно прорвались к нам. Так что пеняйте только на себя.";
			link.l1 = "Я не советую пытаться удержать меня силой. Прорвал"+ GetSexPhrase("ся","ась") +" сюда - вырвусь и отсюда...";
			link.l1.go = "DMSkelHead_7";
		break;
		case "DMSkelHead_7":
			dialog.text = "Пожалуй, что так\nВпрочем, силком вас держать никто не будет. Все равно вашим рассказам никто не поверит, а если поверят, пришлют Инквизицию с сотней солдат... и жизнь целого города будет на вашей совести. Впрочем, видно, вам-то не привыкать...";
			link.l1 = "Черт, вы правы. Может, я смогу чем-то помочь?";
			link.l1.go = "DMSkelHead_8";		
			link.l2 = "Вы абсолютно правы, господин мэр. Какое мне дело до вас и вашего городишки? Приятных снов!";
			link.l2.go = "DMSkelHead_bye";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", false); //выпускаем из города
		break;

		case "DMSkelHead_bye":
			dialog.text = "И вам того же, многоуважаем"+ GetSexPhrase("ый","ая") +" капитан.";
			link.l1 = "Пока. Не скучайте...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -20);
			AddQuestRecord("MagicCity", "4");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("ел","ла"));
			pchar.questTemp.MC = "toByeBye"; //флаг квеста	
		break;

		case "DMSkelHead_8":
			dialog.text = "Снять проклятие - это наша мечта. Беда в том, что мы даже не знаем, в чем дело.";
			link.l1 = "Плохо... Может попытаться разыскать этот галеон, на котором ушли пираты? Похоже, что это единственная ниточка.";
			link.l1.go = "DMSkelHead_9";
		break;
		case "DMSkelHead_9":
			dialog.text = "Вы знаете, недавно к нам в город приходила девушка, Элизабет Шеппард, кажется, ее звали. Так вот, эта юная сеньора наняла тартану на Маракайбо, приплыла к нам и уговорила охрану пропустить ее ко мне.";
			link.l1 = "И что?";
			link.l1.go = "DMSkelHead_10";
		break;
		case "DMSkelHead_10":
			dialog.text = "Она пыталась в подробностях выяснить, что произошло той ночью среди пиратов. Я спрашивал у нее, зачем ей это нужно, но она оказалась штучкой еще той! Ничего не сказала.";
			link.l1 = "И вы ее отпустили?";
			link.l1.go = "DMSkelHead_11";
		break;
		case "DMSkelHead_11":
			dialog.text = "Отпустил. Она ведь не видела нас в этом чудовищном образе.\nТак вот, к чему я это рассказываю. Чем больше проходит времени с нашего с ней разговора, тем больше я утверждаюсь в мысли, что мисс Элизабет Шеппард что-то известно.";
			link.l1 = "Она англичанка?";
			link.l1.go = "DMSkelHead_12";
		break;
		case "DMSkelHead_12":
			dialog.text = "Без сомнения. Я признаю, что дал маху, отпустив ее на все четыре стороны. Надо было допытаться до всего, что она знает.\nСейчас я прошу вас найти ее и выяснить все, что ей известно об этих проклятых пиратах и галеоне 'Королева'.";
			link.l1 = "Хорошо, я так и поступлю.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("MagicCity", "5");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("ся","ась"));
			pchar.questTemp.MC = "toSeekSister"; //флаг квеста	
			LocatorReloadEnterDisable("Charles_town", "housePirate", false);
			//ставим Лиз Шеппард
			sld = GetCharacter(NPC_GenerateCharacter("LizSheppard", "BaynesDaughterSTOK", "woman", "towngirl", 10, ENGLAND, -1, false));
			sld.name = "Элизабет";
			sld.lastname = "Шеппард";		
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "LizBegin"; 
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");	
			ChangeCharacterAddressGroup(sld, "Charles_PirateHouse", "goto", "goto1");
		break;
		//Элизабет Шеппард
		case "LizBegin":
			dialog.text = "Здравствуйте, капитан. Чем обязана удовольствию видеть вас у себя дома?";
			link.l1 = "Здравствуйте, Элизабет. Меня зовут " + GetFullName(pchar) + ". Я приш"+ GetSexPhrase("ел","ла") +" переговорить с вами об одном... очень необычном деле.";
			link.l1.go = "LizBegin_1";
		break;
		case "LizBegin_1":
			dialog.text = "Слушаю вас внимательно, капитан.";
			link.l1 = "Некоторое время назад вы посетили небольшое испанское поселение - Дес-Мойнес. Глава этого небольшого города, Фернандо Торрес, с которым вы, полагаю, знакомы, попросил меня разыскать вас. Что я с удовольствием и сделал"+ GetSexPhrase("","а") +".";
			link.l1.go = "LizBegin_2";
		break;
		case "LizBegin_2":
			dialog.text = "Вы меня удивили, капитан. Продолжайте.";
			link.l1 = "Фернандо просит вас о помощи.";
			link.l1.go = "LizBegin_3";
		break;
		case "LizBegin_3":
			dialog.text = "Чем я могу помочь?";
			link.l1 = "Помогите мне разыскать галеон 'Королева'.";
			link.l1.go = "LizBegin_4";
		break;
		case "LizBegin_4":
			dialog.text = "Зачем ему нужен этот фрегат?";
			link.l1 = "Дело в том, юная леди, что жители города связывают с этим галеоном... возникновение внезапной эпидемии, поразившей город.";
			link.l1.go = "LizBegin_5";
		break;
		case "LizBegin_5":
			dialog.text = "Проклятие настигло и жителей Дес-Мойнеса?!";
			link.l1 = "Да, это так. Так вы знаете о проклятии?";
			link.l1.go = "LizBegin_6";
		break;
		case "LizBegin_6":
			dialog.text = "Конечно знаю! Дело в том, что капитан галеона 'Королева' - очень дорогой мне человек. Последнее время я только тем и занимаюсь, что пытаюсь распутать этот клубок и развеять дьявольские чары.";
			link.l1 = "Получается?";
			link.l1.go = "LizBegin_7";
		break;
		case "LizBegin_7":
			dialog.text = "Отчасти. Дело в том, что я дочь известного среди пиратов человека. Мой отец, капитан Стейтон, был ближайшим соратником Эдварда Мэнсфилда!";
			link.l1 = "О-о, это очень достойно, мисс...";
			link.l1.go = "LizBegin_8";
		break;
		case "LizBegin_8":
			dialog.text = "Так вот, не имея другого выхода, я обратилась за помощью к Джекмену. Надеюсь, вы знаете, кто это?";
			link.l1 = "Еще бы!";
			link.l1.go = "LizBegin_9";
		break;
		case "LizBegin_9":
			dialog.text = "То, что узнали пираты у рабов-индейцев, вызвало у корсаров только дружный хохот. Но мне не до шуток, я своими глазами такое видела!..";
			link.l1 = "Я тоже это видел"+ GetSexPhrase("","а") +", Элизабет. Ходящие и разговаривающие человеческие скелеты - зрелище малоприятное. Так что же узнали мои коллеги у индейцев?";
			link.l1.go = "LizBegin_10";
		break;
		case "LizBegin_10":
			dialog.text = "Такое мог сделать только ацтекский бог мертвых по имени Миктлантекутли.";
			link.l1 = "Н-да... Ну, и что теперь делать?";
			link.l1.go = "LizBegin_11";
		break;
		case "LizBegin_11":
			dialog.text = "Нужно раздобыть нефритовый череп, артефакт этого бога. Только с его помощью можно снять проклятие.";
			link.l1 = "И как вы думаете, где он находится?";
			link.l1.go = "LizBegin_12";
		break;
		case "LizBegin_12":
			dialog.text = "В затерянном городе ацтеков.";
			link.l1 = "Элизабет, так что же произошло на мысе Несбывшихся надежд? Почему это проклятие пало на жителей Дес-Мойнеса?";
			link.l1.go = "LizBegin_13";
		break;
		case "LizBegin_13":
			dialog.text = "Я не знаю\nОднажды ночью, больше года назад, я услышала, как в дом кто-то вошел. Я спустилась вниз и увидела истлевший скелет. Это было ужасно\nЯ закричала. Скелет тоже вскрикнул и убежал. Только тогда я поняла, что это был капитан 'Королевы'. А я отпугнула его!";
			link.l1 = "Знаете, мисс, вы - девушка редкого хладнокровия. Большинство барышень на вашем месте получили бы разрыв сердца от страха.";
			link.l1.go = "LizBegin_14";
		break;
		case "LizBegin_14":
			dialog.text = "Тем не менее, я оттолкнула близкого мне человека. Тогда я твердо решила, что узнаю о несчастье, постигшем капитана 'Королевы' и освобожу его!";
			link.l1 = "Черт возьми, как романтично! Повезло бедняге, что у него есть такая верная девушка.";
			link.l1.go = "LizBegin_15";
		break;
		case "LizBegin_15":
			dialog.text = "Капитан, я прошу вас быть очень корректн"+ GetSexPhrase("ым","ой") +" в выражениях. Не забывайте, чья дочь стоит перед вами!\nТеперь, когда стало ясно, что вы занимаетесь по сути тем же делом, я хочу просить вас раздобыть нефритовый череп бога мертвых. Мне это не под силу, как вы понимаете.";
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = "Этот череп уже у меня, Элизабет.";
				link.l1.go = "LizBegin_haveSkull";
			}
			else
			{
				link.l1 = "Ну что же, юная леди, я готов"+ GetSexPhrase("","а") +" этим заняться, хотя бы в память о вашем отце. Значит, вы говорите, что этот череп находится в индейском городе?";
				link.l1.go = "LizBegin_seekSkull";
			}
		break;
		
		case "LizBegin_SeekSkull":
			dialog.text = "Именно так. В заброшенной столице ацтеков Теночтитлане.";
			link.l1 = "Понятно. Если мне удасться раздобыть этот череп, то я первым делом отправлюсь сюда, в Чарльзтаун.";
			link.l1.go = "LizBegin_16";
			ChangeCharacterReputation(pchar, 3);
		break;
		case "LizBegin_16":
			dialog.text = "Хорошо, капитан, я буду вас ждать. Спасибо вам.";
			link.l1 = "Да не за что...";
			link.l1.go = "exit";
			AddQuestRecord("MagicCity", "6");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("ся","ась"));
			pchar.questTemp.MC = "toSeekSkull"; //флаг квеста	
			NextDiag.TempNode = "LizCheckSkull";
		break;

		case "LizBegin_haveSkull":
			dialog.text = "Как вам удалось его раздобыть?!";
			link.l1 = "Это долгая история... Расскажите мне, что делать дальше.";
			link.l1.go = "LizCheckSkull_1";
		break;
		//проверка черепа
		case "LizCheckSkull":
			dialog.text = "Вы принесли нефритовый череп, капитан?";
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = "Он у меня, Элизабет.";
				link.l1.go = "LizCheckSkull_Ok";
			}
			else
			{
				link.l1 = "Нет еще. Но я занимаюсь этим делом.";
				link.l1.go = "exit";
			}
		break;
		case "LizCheckSkull_Ok":
			dialog.text = "Вам все-таки удалось раздобыть его!";
			link.l1 = "Это было нелегко, скажу я вам... Что теперь делать, мисс?";
			link.l1.go = "LizCheckSkull_1";
		break;
		case "LizCheckSkull_1":
			dialog.text = "Теперь у нас есть инструмент для снятия проклятия. Вам нужно отыскать галеон 'Королева' и, собственно, снять проклятие с капитана.";
			link.l1 = "Ацтекский бог мертвых, тот самый, что дал мне нефритовый череп, сказал между прочим, что череп способен помочь проклятым живым. А как помочь - не объяснил...";
			link.l1.go = "LizCheckSkull_2";
		break;
		case "LizCheckSkull_2":
			dialog.text = "Полагаю, что нужно просто доставить череп в каюту к капитану 'Королевы'. В этом случае проклятие должно исчезнуть само по себе.";
			link.l1 = "Может быть... А где искать это галеон?";
			link.l1.go = "LizCheckSkull_3";
		break;
		case "LizCheckSkull_3":
			dialog.text = "Не знаю. Скорей всего, капитан блуждает по морю вдали от городов. Смотрите внимательней вокруг, этот галеон вы точно не пропустите.";
			link.l1 = "Ясно. Ну что же, займусь поисками.";
			link.l1.go = "exit";
			SetDanielleInWorld();
			AddQuestRecord("MagicCity", "7");
			pchar.questTemp.MC = "toSeekQueen"; //флаг квеста	
			NextDiag.TempNode = "LizSeekQueen";
		break;
		case "LizSeekQueen":
			dialog.text = "Капитан, вы нашли галеон 'Королева'?";
			link.l1 = "Нет еще...";
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = "Вы все-таки сняли проклятие!";
				link.l1 = "Да, мне это удалось.";
				link.l1.go = "LizOver";
			}
		break;

		case "LizOver":
			dialog.text = "Господи, как я рада за сестру!";
			link.l1 = "Кстати, Элизабет, а почему вы не сказали мне сразу, что дорогой вам человек - ваша сестра?";
			link.l1.go = "LizOver_1";
		break;
		case "LizOver_1":
			dialog.text = "Так, на всякий случай...";
			link.l1 = "Понятно. Вы - дочь своего отца, это заметно... Кстати, Даниэль поступила ко мне на службу офицером.";
			link.l1.go = "LizOver_2";
		break;
		case "LizOver_2":
			dialog.text = "Очень хорошо. Я думаю, что вы сумеете о ней позаботиться, а то она совсем было чувство меры потеряла в корсарской удали.";
			link.l1 = "Ну, я постараюсь.";
			link.l1.go = "LizOver_3";
		break;
		case "LizOver_3":
			dialog.text = "Кстати, капитан, пока вы не ушли, я хотела бы отблагодарить вас чем-нибудь. Я подумала и решила подарить вам вещь, что досталась мне от отца. Это старинный оберег, называемый ''Янычар''. По слухам, у владельца такого оберега команда становится намного более послушней. Надеюсь, что он принесёт вам больше пользы, чем мне.";
			link.l1 = "Ого, и не жаль вам расставаться с такой вещью, мисс? Что-ж, я с радостью приму ваш подарок!";
			Log_Info("Вы получили оберег ''Янычар''.");
			AddItems(pchar, "talisman4", 1);
			link.l1.go = "LizOver_4";
		break;
		case "LizOver_4":
			dialog.text = "Пожалуй, на этом всё. Прощайте, капитан!";
			link.l1 = "Прощайте, Элизабет.";
			link.l1.go = "exit";
			npchar.lifeDay = 30;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			NextDiag.TempNode = "LizOver_end";
		break;
		case "LizOver_end":
			dialog.text = "Вы что-то хотели, капитан?";
			link.l1 = "Да нет, ничего особенного...";
			link.l1.go = "exit";
		break;
		//Даниэль на абордаже
		case "DanAbordage":
			dialog.text = "Сейчас пущу тебе кровь!";
			link.l1 = "Эй, леди, что за дела?! Давайте поговорим, что вы бросаетесь на меня, как разъяренная фурия?!";
			link.l1.go = "DanAbordage_1";
		break;
		case "DanAbordage_1":
			dialog.text = "Нам не о чем разговаривать. Ты напал"+ GetSexPhrase("","а") +" на мой галеон!";
			link.l1 = "Мне нужно было попасть в капитанскую каюту, иного варианта у меня не было!.. Подождите, разве этот галеон ваш?";
			link.l1.go = "DanAbordage_2";
		break;
		case "DanAbordage_2":
			dialog.text = "Мой уже пять лет.";
			link.l1 = "Так вы и есть дорогой сердцу Элизабет человек... А я-то думал"+ GetSexPhrase("","а") +", что она говорит о мужчине!";
			link.l1.go = "DanAbordage_3";
		break;
		case "DanAbordage_3":
			dialog.text = "Вы знаете мою сестру Элизабет?";
			link.l1 = "Именно по ее поручению я нахожусь сейчас здесь. А вы, как я понимаю, ее старшая сестра Даниэль Шеппард?";
			link.l1.go = "DanAbordage_4";
		break;
		case "DanAbordage_4":
			dialog.text = "Точно! Позвольте вас спросить, кто вы так"+ GetSexPhrase("ой","ая") +"?";
			link.l1 = "Меня зовут капитан " + GetFullName(pchar) + ". Я разыскал"+ GetSexPhrase("","а") +" ваш галеон для того, чтобы снять проклятие. Расскажите мне, как получилось, что на вас пало проклятие ацтекского бога мертвых.";
			link.l1.go = "DanAbordage_5";
		break;
		case "DanAbordage_5":
			dialog.text = "Так вот кто это был! А я до сих пор и не знала, что это за чучело\nДело было на мысе Несбывшихся надежд, в заливе Маракайбо, у Дес-Мойнеса. Вы, наверное, знаете, что я дочь капитана Стейтона. Несмотря на то, что являюсь женщиной, я сумела отстоять свое право быть капитаном 'Королевы'.\n"+
				"Как-то раз на Бермудах я наняла шкипера, по имени Пьер Кабаль. Это было ошибкой, такого негодяя свет еще не видывал. У берегов Санта-Каталины он схватил какого-то молодого индейца. К сожалению, я узнала об этом, когда мы уже подходили к Маракайбо. Негодяй решил продать его, а деньги забрать себе. Мотивировал он это тем, что индеец - лично его законная добыча.\n"+
				"Понятно, что такого беспредела я допустить не могла. У Дес-Мойнеса, во время заключения сделки, я заявила, что или мы продаем индейца на общих основаниях, или я отпускаю его. В итоге, пришлось отпустить. Но этот негодяй Кабаль выхватил пистолет и выстрелил индейцу в спину. Казалось, наш поединок было неминуем.\n"+
				"Однако судьба распорядилась иначе. Как только индеец со стоном свалился в траву, откуда ни возьмись появилось ужасное чучело в перьях, схватило мертвого индейца, и громовым голосом заявило, что я и моя команда теперь прокляты. И исчезло.";
			link.l1 = "Узнаю Миктлантекутли собственной персоной.";
			link.l1.go = "DanAbordage_6";
		break;
		case "DanAbordage_6":
			dialog.text = "Все стояли, как громом пораженные. Ни о каком поединке не могло быть и речи. Но и взять Кабаля на борт галеона тоже было невозможно. Поэтому, с большей частью команды я ушла в море. С Пьером остались только те, кто ему симпатизировал.";
			link.l1 = "А потом вы поняли, что проклятие - не шутка..";
			link.l1.go = "DanAbordage_7";
		break;
		case "DanAbordage_7":
			dialog.text = "В ту же ночь. Представьте себе наш ужас!";
			link.l1 = "Представляю. Кстати, проклятие пало не только на вас, но и на жителей Дес-Мойнеса.";
			link.l1.go = "DanAbordage_8";
		break;
		case "DanAbordage_8":
			dialog.text = "Вот дьявол!";
			link.l1 = "Вам повезло, Даниэль, что Элизабет узнала вас в скелете, что приходил к ней ночью. И она начала действовать.";
			link.l1.go = "DanAbordage_10";
		break;
		case "DanAbordage_10":
			dialog.text = "Малышка Элизабет! Да уж, есть повод для гордости за сестру\nТак что, капитан, если вы пришли снимать проклятие, то делайте это!";
			link.l1 = "Похоже, что дело уже сделано. Мне нужно было доставить нефритовый череп Миктлантекутли поближе к капитану галеона 'Королева', что я сделал"+ GetSexPhrase("","а") +".";
			link.l1.go = "DanAbordage_11";
		break;
		case "DanAbordage_11":
			dialog.text = "Проклятие снято? Я больше не стану скелетом?";
			link.l1 = "Думаю, что нет. Все кончилось.";
			link.l1.go = "DanAbordage_12";
		break;
		case "DanAbordage_12":
			dialog.text = "Капитан, как я могу отблагодарить вас за оказанную услугу?";
			link.l1 = "Благодарите сестру... Хотя, знаете, у меня есть к вам деловое предложение - идите ко мне офицером. Я "+ GetSexPhrase("пират","такая же женщина-корсар") +", как и вы. Полагаю, мы сработаемся.";
			link.l1.go = "DanAbordage_13";
		break;
		case "DanAbordage_13":
			dialog.text = "Ну что же, почему нет? Я согласна.";
			link.l1 = "Отлично!";
			link.l1.go = "DanAbordage_14";
		break;
		case "DanAbordage_14":
			//чистим базу нпс-кэпов  -->
			DeleteAttribute(NullCharacter, "capitainBase.Danielle");
			//<-- чистим базу нпс-кэпов
			AddQuestRecord("MagicCity", "8");
			pchar.questTemp.MC = "over"; //флаг квеста
			sld = GetCharacter(NPC_GenerateCharacter("DanielleOff", "Danielle", "woman", "Danielle", 25, PIRATE, -1, true));
			sld.name = "Даниэль";
			sld.lastname = "Шеппард";
			sld.greeting = "Gr_Danielle";
			sld.Dialog.Filename = "Enc_OfficerGirl.c";
			sld.quest.meeting = true;
			SetSelfSkill(sld, 90, 60, 30, 60, 90);
			SetShipSkill(sld, 80, 20, 75, 75, 80, 20, 70, 60, 70);
			SetSPECIAL(sld, 6, 9, 9, 10, 8, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
	}
}

void SetDanielleInWorld()
{
	//создаем кэпов
	ref sld = GetCharacter(NPC_GenerateCharacter("Danielle", "Danielle", "woman", "Danielle", 30, PIRATE, -1, true));
	sld.name = "Даниэль";
	sld.lastname = "Шеппард";
	sld.dialog.filename   = "Quest\MagicCity.c";
	sld.dialog.currentnode   = "DanAbordage";
	sld.greeting = "";
	sld.GenQuest.CrewSkelModeClassic = true; //команда - скелеты 
	FantomMakeCoolSailor(sld, SHIP_CATHERINE, "Королева", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
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
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "SantaCatalina"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Фрегат Queen вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Фрегат 'Королева'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "Danielle"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "MagicCity"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "MagicCity"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

