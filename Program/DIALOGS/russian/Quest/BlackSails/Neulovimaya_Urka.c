
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

		case "Jackman_Defeated":
			sld = CharacterFromID("gatri_temp");
			sld.location.locator = "goto6";

			dialog.text = "Приш"+ GetSexPhrase("ел","ла") +" поглумиться надо мной?";
			link.l1 = "Вовсе нет. Мне просто любопытно, почему Гатри оставила тебя в живых?";
			link.l1.go = "Jackman_Defeated_1";
		break;
		case "Jackman_Defeated_1":
			dialog.text = "Эта хитрая сука хочет использовать меня как правителя-марионетку. Она знает, что Береговое Братство рассыпется, услышав о моей смерти, ведь они уж точно не пойдут за бабой"+ GetSexPhrase(".","... без обид.") +" Пусть и такой суровой, как Гатри. Но так она сможет всем управлять, через меня.";
			link.l1 = "И тебя устраивает этот расклад?";
			link.l1.go = "Jackman_Defeated_2";
		break;
		case "Jackman_Defeated_2":
			dialog.text = "Спрашиваешь! Да я по стенке эту шлюху размажу при первой же возможности! Ты не думай, что Джекмен сдался, я еще верну своё.";
			link.l1 = "Советую говорить потише, а то Гатри все свои планы раскроешь. Ну ладно, бывай.";
			link.l1.go = "Jackman_Defeated_exit";
		break;
		case "Jackman_Defeated_exit":
			npchar.Dialog.Filename = "Mayor\Jackman.c";
			NextDiag.CurrentNode = "I_know_you_good";
            DialogExit();

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_3_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Заменить хозяйку борделя в ПР на Максин. Пускать на глобалке английских охотников (скоростые) 2-3 третьеклассника.

		//Прибыли в ПР. Идём в бордель к мадам. Опа, сюрприз. Это Макс (смуглянка)

		case "BS_NU_1":	//Максин
			dialog.text = "...";
			link.l1 = "Поздравляю с карьерным ростом! Неожиданно, однако.";
			link.l1.go = "BS_NU_2";
		break;

		case "BS_NU_2":
            dialog.text = "Приветствую, "+pchar.name+". Решил"+ GetSexPhrase("","а") +" расслабиться или развлечь команду?";
            link.l1 = "Нужна твоя помощь. Я знаю, что девочки из борделей много чего видят и слышат, и готов"+ GetSexPhrase("","а") +" купить у тебя кое-какую информацию.";
			link.l1.go = "BS_NU_3";
		break;

		case "BS_NU_3":
            dialog.text = "Нужна наводка на жирную добычу? Не нужно ничего платить, поделюсь из взаимности, всё же я тебе обязана.";
            link.l1 = "Нужна не наводка, нужна любая зацепка о самой жирной добыче, какую только можно вообразить! Ты понимаешь, о чём я?";
			link.l1.go = "BS_NU_4";
		break;

		case "BS_NU_4":
            dialog.text = "'Урка Де Лима'! Флинт не разменивается по пустякам. Я знаю кое–что, но это не бесплатно, извини.";
            link.l1 = "Назови цену.";
			link.l1.go = "BS_NU_5";
		break;

		case "BS_NU_5":
            dialog.text = "Равная доля, как компаньона. И кое-что бесплатно от меня. Про английских рейдеров.";
            link.l1 = "Ты понимаешь, что о долях нужно договариваться со всеми участниками предприятия? Или ты хочешь долю от моей доли?";
			link.l1.go = "BS_NU_6";
		break;

		case "BS_NU_6":
            dialog.text = "Я понимаю, и поэтому – отправляюсь с тобой. А встретившись с остальными компаньонами, мы, надеюсь, придём к соглашению, взаимовыгодному для всех сторон.";
            link.l1 = "Уговорила, отправляемся сейчас же!";
			link.l1.go = "BS_NU_7";
		break;

		case "BS_NU_7":
            dialog.text = "Подожди минутку. Кое-что про англичан. На Карибы прибыла эскадра во главе с военным кораблём «Скарборо». Поговаривают, что это военная разведка Адмиралтейства. В английские порты они не заходят, перед губернаторами не отчитываются. Уже много каперов и пиратов пропали без вести. А некоторых видели, но они делали вид, что они не те, за кого их принимают. Что-то странное происходит.";
            link.l1 = "Я уже несколько раз сталкивал"+ GetSexPhrase("ся","ась") +" с рейдерами под английскими флагами. Ничего особенного. Только уж очень настойчивые эти британцы. Самоубийственно настойчивые.";
			link.l1.go = "BS_NU_8";
		break;

		case "BS_NU_8":
            dialog.text = "Это всё, что я о них знаю. Я готова отправляться.";
            link.l1 = "Идём. Хотя, стой. Ты про Чарльза Вейна что-нибудь слышала? Не объявлялся ли он в колониях?";
			link.l1.go = "BS_NU_9";
		break;

		case "BS_NU_9":
            dialog.text = "Обломки 'Рейнджера' выловили рыбаки у мыса Негрил. Про самого Чарльза я ничего не слышала.";
            link.l1 = "Хоть что-то. Нужно будет проверить. В путь.";
			AddQuestRecord("BSUrka", "1");
			SetQuestHeader("BSUrka");
			CloseQuestHeader("BSChaseBegun");
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
			PChar.quest.BSUrka_Negril.win_condition.l1 = "location";
			PChar.quest.BSUrka_Negril.win_condition.l1.location = "Shore35";
			PChar.quest.BSUrka_Negril.function = "BSUrka_Negril";
		break;

		case "BS_NU_9_exit":
            dialog.text = "Увидимся на корабле, капитан.";
            link.l1 = "Да, увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
		break;
		//Запись в СЖ: «Таинственные английские военные, пропавший Вейн и новый компаньон в нашем дельце на сто пятьдесят миллионов. Нужно проверить информацию о разбившемся 'Рейнджере' и выдвигаться на Бермуды. Как бы не упустить денежный галеон».

		//Пиздуем на Негрил, в бухте запись в СЖ: «Сломанные мачты, куски обшивки, рваный такелаж и прочий мусор. Нужно расспросить местных о случившемся»

		//В форт Оранж в таверне у бармена ничего. Выпиваем с алкашом – бинго

		case "BS_NU_10":	//Алкоголик
            dialog.text = "Ну твоё здоровье! Ух, хорош ром. Видел"+ GetSexPhrase("","а") +" бы ты, что пару дней назад тут в бухте творилось! Пиратский бриг, весь простреленный, с парусами как у корабля-призрака дал бой двум испанским фрегатам. И тут, откуда не возьмись, из-за мыса три пирата на корветах! Испанцы дружно на левый галс легли и ну шмалять по батарейно. Один корвет от носа до кормы прострелили, крику было! Аж в форте слыхать! Так вот, простреленный сразу на борт завалился, и тонуть начал, а два других, сами бортовыми, почти в упор разнесли фрегат. А бриг тот, который от испанцев удирал, вдруг осмелел, кинул якорь по левому борту и вокруг цепи разворот резкий сделал, такой, что мачту аж потерял. И давай с борта по пирату стрелять. В общем, потопили они корвет второй совместно с испанцем уцелевшим. Кхе, горло пересохло.";
            link.l1 = "Вот, хлебни ещё. Так что дальше-то было? Интересно рассказываешь! Я прям вижу этот бой наяву!";
			link.l1.go = "BS_NU_11";
		break;

		case "BS_NU_11":
            dialog.text = "Ух. Хорошо пошло, благодарствуйте. Так вот. Пират, на уцелевшем корвете, смекнул, что дело плохо, стал по ветру и на всех парусах за горизонт удрал! А на бриге, цепь якорную отрубили и бортом на фрегат навалились. На абордаж, стало быть, пошли. И одолели - таки испанцев! Фрегат черный флаг поднял, дал залп по бригу потрёпанному и ушел, куда - то на север. Такая баталия была, хоть на картину! Обломками всё побережье усыпано.";
            link.l1 = "Спасибо за рассказ. Тебе бы книги писать с таким талантом!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: «Вейн жив, обзавёлся новым кораблём и выполнил свою часть по отвлечению сопровождения. Каков корсар! Надеюсь, увидимся на Бермудах»

		//Выходим в море, спауним фиолетовую энку (англичане). Файт. Три фрегата, кэп флагмана – Билли Бонс. Берём на абордаж. Файт в каюте, после «убиения» - диалог.

		case "BS_NU_12":	//Билли Бонс
            dialog.text = "Стой! Нужно поговорить!";
            link.l1 = "Так, так, так. Старпом самого Флинта и вдруг английский капитан. Как это понимать?";
			link.l1.go = "BS_NU_13";
		break;

		case "BS_NU_13":
            dialog.text = "Я и был английским капитаном. Разведка Адмиралтейства, коммандер Вильям Блэкхэм, к вашим услугам.";
            link.l1 = "И какого чёрта разведка Адмиралтейства гоняется за мной? Все эти рейдеры, которых я потопил"+ GetSexPhrase("","а") +", тоже ваши?";
			link.l1.go = "BS_NU_14";
		break;

		case "BS_NU_14":
            dialog.text = "Каперы, пираты, получившие помилование и перешедшие на службу Его Величества. Рвения много, умения, к сожалению, мало.";
            link.l1 = "Понятно. Расходный материал. Так что вашей конторе от меня нужно?";
			link.l1.go = "BS_NU_15";
		break;

		case "BS_NU_15":
            dialog.text = "Флинт. Вернее капитан Джеймс МакГроу, изменник, вор, убийца. Бывший офицер флота Его Величества, виновен в убийстве лорда Гамильтона, его жены и сотне других преступлений. Все мои попытки арестовать или убить этого человека – провалились, и я предлагаю вам, как его доверенному компаньону, помочь Короне арестовать или уничтожить изменника!";
            link.l1 = "И какой интерес мне делать это?";
			link.l1.go = "BS_NU_16";
		break;

		case "BS_NU_16":	//Тут выбор
            dialog.text = "Королевское помилование вам и вашим подчинённым, четыреста тысяч фунтов серебром и возможность сделать блестящую карьеру в Адмиралтействе. А так же благодарность семьи Гамильтон, а это поверьте, многого стоит!";
            link.l1 = "Катись ты к дьяволу, Билли, со своим прощением и его величеством! Я друзей не предаю! И выгоды от этой дружбы я всяко больше поимею! Готов продолжить? Сдохни!";
			link.l1.go = "Fight_Billi_Bons";
			//link.l2 = "Я подумаю над этим. Как мне связаться с тобой?";
			//link.l2.go = "BS_NU_17";
		break;

		case "Fight_Billi_Bons":
			AddQuestRecord("BSUrka", "4");
			pchar.BSBonsKilled = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "BS_NU_17":
            dialog.text = "На Антигуа, в таверне, будет ждать мой человек. Пароль: «Рыбалка успешной была. Улов – загляденье».";
            link.l1 = "До встречи, сэр Вильям.";
			link.l1.go = "BS_NU_18";
		break;

		//Расходимся миром. В таверну Антигуа поселить непися за стол.

		//Запись в СЖ если убили Билла: «Ситуация с английскими рейдерами прояснилась. Надо же. Разведка адмиралтейства! Нужно предупредить Флинта. Где-то всё ещё охотится ‘Скарборо’ и с этим, нужно что-то делать. В путь. На Бермуды».

		//Запись в СЖ если приняли сторону Билла: «Я принял(ла) косвенно предложение Бонса, то есть Блэкхэма. Но сначала 'Урка'! Такую добычу нельзя упускать. Нужно записать пароль для встречи со связным на Антигуа. «Рыбалка успешной была. Улов – загляденье»»

		//При любом раскладе – рейдеров, на глобалке выключаем.

		//Пиздуем на Бермуды. По улицам гуляют Бонни и Рекхэм. Просто гуляют с обычными для нпс диалогами.

		//В резиденции Флинт, Сильвер, Гатри, Вейн. С нами приходит Макс. Если согласились топить за Англию – про «Скарборо» нет веток.

		case "BS_NU_18":	//Флинт
            dialog.text = "Наконец все в сборе. Кто твоя спутница, "+pchar.name+"?";
            link.l1 = "Знакомьтесь – это Максин. Эмм... Она хозяйка борделя в Порт Рояле.";
			link.l1.go = "BS_NU_18_1";
		break;

		case "BS_NU_18_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_19";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_19":	//Вейн
            dialog.text = "Ну надо же, Макс! Высоко взлетела! Помни, что больно падать, очень больно!";
            link.l1 = "";
			link.l1.go = "BS_NU_19_1";
		break;

		case "BS_NU_19_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_20";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_20":	//Максин
            dialog.text = "Я запомню, спасибо Чарльз. Господа, у меня есть необходимая вам информация о денежном галеоне, и я предлагаю продать её вам за равную долю в добыче.";
            link.l1 = "";
			link.l1.go = "BS_NU_20_1";
		break;
		case "BS_NU_20_1":
			DialogExit();
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21":	//Гатри
            dialog.text = "Твоя знакомая, Чарли? Хозяйка борделя? Кто-то пел мне истории о вечной любви и верности до гроба, а сам по шлюхам шастал!";
            link.l1 = "";
			link.l1.go = "BS_NU_21_1";
		break;
		case "BS_NU_21_1":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21_2";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21_2":	//Флинт
            dialog.text = "Сначала дела, Элеонора! Равная доля, мисс Максин, подразумевает равное участие и риски. Надеюсь, ваша информация того стоит. Изложите, и мы обдумаем ваше участие в нашем партнёрстве.";
            link.l1 = "";
			link.l1.go = "BS_NU_21_3";
		break;
		case "BS_NU_21_3":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_22";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_22":	//Максин
            dialog.text = "Насколько я знаю, ваша охота за 'Уркой' сорвалась. Дело в том, что она ушла другим маршрутом, не заходя в Гавану, всё это было отвлекающим манёвром. И я знаю, куда ушёл корабль!";
            link.l1 = "Невероятно! Откуда? Неужели от твоих работниц?";
			link.l1.go = "BS_NU_23";
		break;
		case "BS_NU_23":
            dialog.text = "'Урка' получила строжайший приказ не заходить в любые порты, а пользоваться услугами проверенных капитанов для пополнения запасов и перевозки войск. Один из этих капитанов имеет специфические вкусы, и только моё заведение может их удовлетворить. Пара визитов и он напел столько всего, что его можно вешать, расстреливать или четвертовать на выбор, или всё сразу.";
            link.l1 = "";
			link.l1.go = "BS_NU_23_1";
		break;
		case "BS_NU_23_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_24";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_24":	//Вейн
            dialog.text = "Какие такие вкусы?";
            link.l1 = "";
			link.l1.go = "BS_NU_24_1";
		break;
		case "BS_NU_24_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_25";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_25":	//Максин
            dialog.text = "Пусть это останется тайной. Так вот, 'Урка Де Лима' движется вдоль побережья Мэйна и встанет на якорь недалеко от западного берега Кюрасао, где будет ожидать прихода конвойной эскадры из Гаваны и уже оттуда двинется в Европу, минуя Барбадос и Тринидад. Я заслужила свою долю, господа?";
            link.l1 = "";
			link.l1.go = "BS_NU_25_1";
		break;
		case "BS_NU_25_1":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_26";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_26":	//Флинт
            dialog.text = "Вполне. Но попрошу вас составить компанию, мисс Гатри, здесь на острове. А нам нужно готовить корабли и не медля выходить в море!";
            link.l1 = "";
			link.l1.go = "BS_NU_26_exit";
			AddQuestRecord("BSUrka", "6");
		break;

		case "BS_NU_26_exit":
			DialogExit();
			NextDiag.CurrentNode = "BS_NU_28";

			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Maks");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("gatri_temp");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);
		break;
		//Запись в СЖ: «Макс дала важную информацию. Испанцы предвидели охоту за галеоном и запутали следы. Но болтливые и похотливые людишки рушат любые планы и вскрывают любые тайны. Заметка себе: «Не болтать в борделях!»»

		//Все сваливают из резиденции. Остаётся ГГ и Флинт.

		case "BS_NU_28":	//Флинт
			pchar.quest.BSUrka_Fail1.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail1.win_condition.c1.character ="Flint";
			PChar.quest.BSUrka_Fail1.function = "BSUrka_Fail";

			pchar.quest.BSUrka_Fail2.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail2.win_condition.c1.character ="BS_Vein";
			PChar.quest.BSUrka_Fail2.function = "BSUrka_Fail";

			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);
			BSRepairShip(npchar);
			LAi_SetImmortal(npchar, false);

			SetShipRemovable(npchar, false);

            dialog.text = "";
            link.l1 = "Последний рывок?";
			link.l1.go = "BS_NU_29_Ya_Ne_Krisa";
		break;

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_29_Ya_Ne_Krisa":
            dialog.text = "Подозреваю, что не последний.";

			link.l1 = "Мы уже многое пережили вместе. Можешь на меня рассчитывать, что бы не случилось.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
			if(CheckAttribute(pchar, "BSBonsKilled"))
			{
				link.l1 = "Я встретил"+ GetSexPhrase("","а") +" у Ямайки твоего старпома. Коммандера Вильяма Блэкхэма. Бонса. Билли Бонса.";
				link.l1.go = "BS_NU_30_Ya_Ne_Krisa";
			}
		break;

		case "BS_NU_30_Ya_Ne_Krisa":
            dialog.text = "Коммандера? Хм... Я подозревал, что он шпион, но работает на Джекмана. Но Адмиралтейство...";
            link.l1 = "Им нужна твоя голова, за убийство лорда Гамильтона и прочая, прочая, прочая. Золотые горы сулил.";
			link.l1.go = "BS_NU_31_Ya_Ne_Krisa";
		break;

		case "BS_NU_31_Ya_Ne_Krisa":
            dialog.text = "Но ты не внял"+ GetSexPhrase("","а") +" ему? Почему?";
            link.l1 = "Сто пятьдесят миллионов блестящих причин, чёрт возьми! И я не продаю друзей.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
		break;

		case "BS_NU_32_Ya_Ne_Krisa":
            dialog.text = "Ты оказываешь мне честь, предлагая свою дружбу. С радостью принимаю её. Вот моя рука.";
            link.l1 = "А вот моя. Ну что? Пора проверить, как там неуловимая 'Урка'!";
			link.l1.go = "BS_NU_32_exit";
		break;

		case "BS_NU_32_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			chrDisableReloadToLocation = false;
			DialogExit();

			PChar.quest.BSUrka_Pirates_town_Vein.win_condition.l1 = "location";
			PChar.quest.BSUrka_Pirates_town_Vein.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSUrka_Pirates_town_Vein.function = "BSUrka_Pirates_town_Vein";
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_29_Ya_Shpion":
            dialog.text = "Подозреваю, что не последний.";
            link.l1 = "...";
			link.l1.go = "exit";
		break;

		//Ставим Моржа и Вейна на ТФ «Рейнджер» в эскадру. На выходе из резиденции говорим с Вейном.

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_33_Ya_Ne_Krisa":
			FantomMakeCoolestSailor(npchar, SHIP_FRIGATE_H, "Рейнджер", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//вейн присоединяется к эскадре
			BSRepairShip(npchar);
			SetShipRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
			chrDisableReloadToLocation = false;
			LAi_SetImmortal(npchar, false);
            dialog.text = "О чём говорили с Флинтом?";
            link.l1 = "Планировали поход. Слышал"+ GetSexPhrase("","а") +" о твоём бое с испанцами! И корабль смотрю у тебя новый. Это же надо такое провернуть! Как ты вообще уцелел?";
			link.l1.go = "BS_NU_34_Ya_Ne_Krisa";
		break;

		case "BS_NU_34_Ya_Ne_Krisa":
            dialog.text = "Я чертовски удачлив, другого объяснения я сам не знаю.";
            link.l1 = "Мне бы хоть каплю твоей удачи. Что ж, пора выдвигаться.";
			link.l1.go = "BS_NU_34_exit";

			//Sea_CabinStartNow();
			//Set_My_Cabin();
			//Sea_DeckBoatStartNow(pchar);
			//BSUrka_Curacao_SeaBattle(1);
			//DoReloadCharacterToLocation(Get_My_Cabin(),"goto","goto4");

			//setCharacterShipLocation(pchar, "Shore23");
			//pchar.location.from_sea = "Shore23";
			//setWDMPointXZ("Shore23");  // коорд на карте
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_33_Ya_Shpion":
            dialog.text = "О чём говорили с Флинтом?";
            link.l1 = "Есть кое-что, что нужно обсудить. Но об этом после 'Урки'";
			link.l1.go = "BS_NU_34_Ya_Shpion";
		break;

		case "BS_NU_33_Ya_Shpion":
            dialog.text = "Как скажешь. В путь.";
            link.l1 = "";
			link.l1.go = "exit";
		break;

		case "BS_NU_34_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "reload1_2", "", "", "", -1);
			BSUrka_Curacao_SeaBattle();
            pchar.quest.BSUrka_Curacao_SeaBattle.win_condition.l1 = "EnterToSea";
			pchar.quest.BSUrka_Curacao_SeaBattle.function    = "BSUrka_Curacao_SeaBattle";
			DialogExit();
			SetTimerFunction("BSUrka_Curacao_SeaBattle", 0, 0, 2);
		break;

		//Выходим в море, чешем до Кюрасао. С западной стороны выходим на локалку. Сюрпрайз. Урки нету! Зато есть 6-8 испанских фрегатов и линейников. Адовое мочилово. После боя, ТП на палубу Флинта.

		case "BS_NU_35":
            dialog.text = "";
            link.l1 = "Почти всё сошлось, но где 'Урка'?";
			link.l1.go = "BS_NU_36";
		break;

		case "BS_NU_36":
			chrDisableReloadToLocation = false;

			DeleteAttribute(pchar, "LockShoreReload");
            dialog.text = "Спокойно, мы выловили несколько испанцев из воды, их сейчас допрашивают. Станем на рейде у мыса Кальвинистов. Поговорим на берегу.";
            link.l1 = "";
			link.l1.go = "exit";
			pchar.LockMapReload = "Сначала нужно допросить пленных испанцев у мыса Кальвинистов.";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1          = "location";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1.location = "Shore23";
			pchar.quest.BSUrka_Curacao_Shore.function             = "BSUrka_Curacao_Shore";
		break;
		/*
		case "BS_NU_36_exit":
			DialogExit();
			DoReloadCharacterToLocation("Shore23","reload","sea");
		break;
		*/
		//Доплываем до мыса Кальвинистов, выходим на берег. На берегу испанский офицер, Флинт, Вейн, Бонни.

		case "BS_NU_37":	//Флинт
            DeleteAttribute(pchar, "LockMapReload");
			dialog.text = "Мы на Кюрасао, вас отпустят, не причинив вреда, если мы получим интересующую нас информацию. Иначе, вам известна моя репутация! И не тяните с решением.";
            link.l1 = "";
			link.l1.go = "BS_NU_381";
		break;

		case "BS_NU_381":
			DialogExit();
			sld = CharacterFromID("BSUrka_Prisoner");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_38";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_38":	//Испанский офицер
			sld = CharacterFromId("Flint");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "Проклятые каброны! Вас всех ждёт преисподняя! Но я принимаю ваши условия! Интересующий вас корабль унесло шквалом в направлении Мейна. Он потрёпан штормом и встанет на ремонт в какой-нибудь из бухт. Это всё, что я могу вам сказать.";
            link.l1 = "";
			link.l1.go = "BS_NU_391";
		break;

		case "BS_NU_391":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_39";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_39":	//Флинт
            dialog.text = "Благодарю, вы можете идти.";
            link.l1 = "";
			link.l1.go = "BS_NU_401";
		break;

		case "BS_NU_401":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_40";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_40":	//Бонни убивает испанца
            dialog.text = "Черта с два он может идти!";
            link.l1 = "";
			link.l1.go = "exit";
			DoQuestFunctionDelay("BSUrka_BonyHits", 0.3);
		break;

		case "BS_NU_41":	//Вейн
            dialog.text = "Какого чёрта Энн? Что на тебя нашло?";
            link.l1 = "";
			link.l1.go = "BS_NU_421";
		break;

		case "BS_NU_421":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_42";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_42":	//Бонни
            dialog.text = "Поиски затянулись и слишком много сюрпризов было уже, чтоб отпускать этого пленника, который наведёт на нас очередную эскадру.";
            link.l1 = "";
			link.l1.go = "BS_NU_431";
		break;

		case "BS_NU_431":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_43";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_43":	//Флинт
            dialog.text = "Мистер Вейн, следите за вашими подчинёнными! Это последняя выходка, которую я потерплю.";
            link.l1 = "";
			link.l1.go = "BS_NU_44";
		break;

		case "BS_NU_44":	//Флинт
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
            dialog.text = "Энн, в шлюпку! Молча! Потом поговорим.";
            link.l1 = "Пора обыскать уйму бухт. За работу!";
			link.l1.go = "BS_NU_44_exit";
		break;

		case "BS_NU_44_exit":
			AddQuestRecord("BSUrka", "7");
			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			BSUrka_PlaceUrka();
			pchar.quest.BSUrka_Found.win_condition.l1          = "location";
			pchar.quest.BSUrka_Found.win_condition.l1.location = "Cumana";
			pchar.quest.BSUrka_Found.function             = "BSUrka_Found";

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_4_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Охота затянулась, и нервы начинают сдавать. Нужно разобраться с этим поскорее, пока мы не передрались»

		//Выходим в море. Ищем по бухтам Мурку. Мурка в Лос Текос. В бухте ставим раздолбаный имперский галеон под названием «Урка де Лима». Взаимодействовать с ней нельзя. Она просто декорация. На рейде – испанский мановар. Файт.

		//После потопления самовара, запись в СЖ: «Наконец то! Вот она 'Урка'. Её сильно потрепало штормом и команды не видно на борту. Высаживаемся на берег!»

		//На берегу – адский файт. Испанцев лучше пускать волнами, чтоб не лагало всё к херам штук по 30 и так пять раз. Флинта, Вейна, Сильвера – лучше сделать либо бессмертными, либо очень толстыми на момент файта.

		//После победы запись в СЖ: «Дело сделано, столько крови я никогда не проливал(ла) за один раз. Нет сил, даже говорить. Грузим сундуки на корабли и отчаливаем, пока на шум не налетела береговая охрана».

		//Ставим табличку «Прошло 3 часа, сундуки погружены на корабли»

		//Подходит Флинт

		case "BS_NU_45":	//Флинт
            dialog.text = "Дело сделано, делёжкой займёмся на Бермудах. Пора уходить.";
            link.l1 = "";
			link.l1.go = "BS_NU_45_exit";
		break;

		case "BS_NU_45_exit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);

			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_46_Ya_Ne_Krisa";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		//Флинт уходит на корабль. Остаётся Вейн.

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_46_Ya_Ne_Krisa":	//Вейн
            chrDisableReloadToLocation = false;
			RemoveCharacterCompanion(PChar, npchar);
			AddQuestRecord("BSUrka", "9");
			dialog.text = "Я уже почти перестал верить в то, что этот галеон реален. А ты хорошо дерёшься. Найди меня после всего, возможно провернём несколько дел вместе!";
            link.l1 = "Я очень нескоро пойду на следующее дело! Сам понимаешь, но за предложение спасибо! Ты тоже чертовски хороший корсар!";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisa";
		break;

		case "BS_NU_47_Ya_Ne_Krisa":
            dialog.text = "Я пират. Патентом, меня не заманишь. Не люблю униформу.";
            link.l1 = "Пора на Бермуды. Пойдём.";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisaexit";
		break;

		case "BS_NU_47_Ya_Ne_Krisaexit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();

			pchar.BSBonsSpawned = true;
			BSBons_SeaBattle(true);
			BSChaseBegun_unlock_townhall();

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_5_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}

			PChar.quest.BSUrka_Finish.win_condition.l1 = "location";
			PChar.quest.BSUrka_Finish.win_condition.l1.location = "Pirates_townhall";
			PChar.quest.BSUrka_Finish.function = "BSUrka_Finish";

			PChar.quest.BSChaseBegun_Fail.over = "yes";
			PChar.quest.BSUrka_Fail1.over = "yes";
			PChar.quest.BSUrka_Fail2.over = "yes";
			PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
			PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_46_Ya_Shpion":	//Вейн
            dialog.text = "Ты о чём-то поговорить хотел"+ GetSexPhrase("","а") +"? Ещё на Бермудах.";
            link.l1 = "Да, есть кое-что. Возле Ямайки я столкнул"+ GetSexPhrase("ся","ась") +" с Билли Бонсом, который не Бонс вовсе, а офицер британской морской разведки. Не перебивай! Им нужна голова Флинта в обмен на лояльность колониальных властей и вознаграждение. Четыреста тысяч фунтов серебром. В местной валюте – это по два с половиной миллиона на каждого, если ты в деле. Что скажешь?";
			link.l1.go = "BS_NU_47_Ya_Shpion";
		break;

		case "BS_NU_47_Ya_Shpion":
            dialog.text = "Поиметь кусок от всех этих испанских миллионов и награду от британской короны? В обмен на голову этого заносчивого сукина сына? Как ты думаешь провернуть всё это?";
            link.l1 = "Атакуй мы его в море, прямо сейчас – нас наши же команды порубят на фарш. Флинт сейчас для них полубог! После Бермуд и делёжки, когда все упьются, тогда его и повяжем. За живого можно будет ещё стрясти деньжат.";
			link.l1.go = "BS_NU_48_Ya_Shpion";
		break;

		case "BS_NU_48_Ya_Shpion":
            dialog.text = "Я в деле, хоть от этого дела несёт дерьмом, но посмотреть в его глаза, когда он поймёт, что его поимели – это того стоит!";
            link.l1 = "Значит ночью, после делёжки. Всё, на нас уже смотрят. В путь.";
			link.l1.go = "exit";
		break;

		//Если мы остались верны Флинту, то следующая запись в СЖ: «Осталось самое интересное – делёжка добычи! Пора отправляться на Бермуды»

		//Если мы предаём Флинта, то следующая запись в СЖ: «Вейн в деле, делим добычу и ловим Флинта. Надо постараться оставить его в живых. Пора на Бермуды»

		//Если решили не продавать Флинтушку – на глобалке догоняет фиолетовая энка. «Скарборо» линейник первого ранг. С ним пара фрегатов. Никаких диалогов, просто замес в море. По окончанию – запись в СЖ «Скарборо» на дне. Остался только Джекман»

		//Если решили продать, англичан нету, спокойно идём до бермуд.

		//В обоих вариантах – при выходе на локалку Бермуд – атакует эскадра Джекмана. Джекман на «Нептуне». Бах-бах. Абордируем «Нептуна» файт с Джекманом. Диалог

		case "BS_NU_49":	//Джекман
            dialog.text = "Да чтоб тебя черти драли! Это с тебя всё началось и на тебе закончиться должно!";
            link.l1 = "С чего ты взъелся так? Из-за Гатри? Ха-ха. Эта баба – вот истинная гроза пиратов, а не ты, заплывший жирком увалень!";
			link.l1.go = "exit";
		break;

		case "BS_NU_49":
            dialog.text = "Да я тебя пополам разрублю и сожру твоё сердце!";
            link.l1 = "";
			link.l1.go = "exit";
		break;

		//Файт. На тушку Джекмана положить какие - нибудь уники. В сундук – бабла 300к и камушков штук по 50 каждого. Запись в СЖ: «На подходе к Бермудам, мы были атакованы эскадрой Джекмана. Несчастный сукин сын не смог смириться с ролью второго после мисс Гатри. Передавай привет Сатане, мистер Джекман!»

		//Селим Гатри и Макс в резиденцию, в магаз – рандомного челика.

		//Высаживаемся, идём в резиденцию. ГГ, Флинт, Вейн, Гатри, Макс

		case "BS_NU_50":	//Флинт
            dialog.text = "Дело сделано, золото выгружают с кораблей на склад мисс Гатри, подсчетом и дележом займёмся сразу по окончании выгрузки. А пока предлагаю выпить за успешное окончание дела! Вы лучшая команда, с которой мне приходилось иметь дело. За вас! До дна!";
            link.l1 = "До дна!";
			link.l1.go = "BS_NU_50exit";
		break;

		case "BS_NU_50exit":	//Флинт
			DialogExit();
			BSUrka_Poison();
		break;

		//Типа пьём и валимся с ног все, кроме Флинта, Флинт уходит из резиденции. Нас отравили.

	}
}
