
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	string sTemp;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Здравствуйте! Так вы и есть "+ GetSexPhrase("тот герой, что сумел","та героиня, что сумела") +" пробиться ко мне?";
			link.l1 = "Да, это я и есть.";
			link.l1.go = "FT_1";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи "+ GetSexPhrase("его, он нарушил","ее, она нарушила") +" Закон!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумали?! Теперь граждане и милиция порвут тебя, как старую тряпку!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал"+ GetSexPhrase("","а") +" оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как три мушкетера, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это "+ GetSexPhrase("серьезному мужчине","девушке") +"...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","тут всякие") +" ходят передо мной с оружием наизготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		case "FT_1":
			dialog.text = "Хорошо, очень хорошо... Будьте добры, назовите себя, "+ GetSexPhrase("мой досточтимый друг","прекрасная амазонка") +".";
			link.l1 = "Меня зовут капитан " + GetFullName(pchar) + ". А вы, насколько я могу судить, - Хенрик Ведекер, по прозвищу Механик.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Верно!.. А откуда мы меня знаете?";
			link.l1 = "Ох, лучше не спрашивайте, долгая история...";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Все-таки, я бы послушал. Понимаете, я долгое время был лишен общения с нормальными людьми. 'Касперы' - и те со мной старались не общаться. Кстати, о клане 'Каспер'. Вы что, их всех уложили?";
			link.l1 = "Всех до единого. А до этого я пустил"+ GetSexPhrase("","а") +" под нож еще и клан 'Нарвал'.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Хе-хе, так Город теперь лишен разбойников? Н-да, снимаю шляпу, как говорится\nНу, а теперь расскажите мне, пожалуйста, ради чего вы совершали эти впечатляющие подвиги.";
			link.l1 = "Как вам сказать... Понимаете, я по собственной инициативе попал"+ GetSexPhrase("","а") +" на этот остров, расследую гибель Тизера Дэна. Ну а теперь хочу убраться отсюда.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Тизера Дэна? Вы знали Тизера?";
			link.l1 = "Встречаться лично не довелось, но могу сказать, что он благополучно добрался до Большой земли. К сожалению, его убили агенты Голландской Вест-Индской компании.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Жаль. Вы знаете, а ведь это я построил ему плот, на котором он ушел отсюда в океан.";
			link.l1 = "Да?! А как же он до вас добрался через 'касперов'?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Он часто плавал на 'Фернандо Диффиндур'. В один из таких заплывов я был у себя на платформе, готовил погружение...";
			link.l1 = "Погружение?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Да... Потом объясню. Так вот, мы познакомились, поговорили, и я сделал все, чтобы он уплыл отсюда и рассказал людям об этом острове.";
			link.l1 = "Хоть он и добрался до цели, но именно рассказы о Городе стали причиной его смерти. Голландская Вест-Индская компания полагает, что в Городе сосредоточены огромные богатства, и их резкое появление на рынке могло бы обрушить цены. В этом случае коммерция полетит к чертям собачьим.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Ясно. Значит, Тизер все-таки сдержал данное мне обещание до конца, даже несмотря на угрозу своей жизни. Черт возьми, как жаль, что он погиб!";
			link.l1 = "Жаль, конечно. Вы знаете, столько хороших людей умерло за последнее время, что я уже устал"+ GetSexPhrase("","а") +" жалеть...";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Ну, не будем о грустном. Вы знаете, эта ваша Голландская компания права насчет ценностей Города. Тут чего только нет. А еще больше - под водой...";
			link.l1 = "Серьезно? А откуда вы знаете?";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "Видел собственными глазами... Ну ладно, это, опять же, потом. Сейчас расскажите мне, "+ GetSexPhrase("друг мой","милая девушка") +", что творится в Городе и зачем вы пришли ко мне.";
			link.l1 = "В городе хозяйничает адмирал Чад Каппер. Граждане города живут согласно положениям Закона, одно из которых запрещает строить любые плавательные средства. Ну, а я случайно узнал"+ GetSexPhrase("","а") +" о Механике и решил"+ GetSexPhrase("","а") +" побеседовать с вами любой ценой. Вот, собственно, и все...";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "Чад Каппер твердо держит бразды правления Городом, как и раньше...";
			link.l1 = "Ну, я бы не сказал"+ GetSexPhrase("","а") +", что твердо. Два клана уничтожены один за другим, происходят убийства граждан. Люди недовольны адмиралом и его милицией, ведь это в их обязанность входит обеспечение безопасности!";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "Вы знаете, "+ GetSexPhrase("друг мой","девушка") +", я совершенно не удивлюсь, если окажется, что за всем происходящим в Городе так или иначе стоит адмирал.";
			link.l1 = "Ну, не совсем. Теперь я веду свою игру. И доказательство этому - отсутствие клана 'Каспер' на барке 'Сан Габриэль'.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "Хм, 'касперы' действовали в связке с Каппером, поэтому вынужден с вами согласиться... Ну что же, благодаря вам жизнь в Городе серьезно изменилась...";
			link.l1 = "Верно! И теперь я предлагаю провести выборы адмирала. Хочу выставить свою кандидатуру на эту должность.";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "Какие выборы, "+ GetSexPhrase("друг мой","девушка") +"! Нужно спасать свои жизни, пока еще не поздно...";
			link.l1 = "О чем это вы?";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "Вы знаете, почему меня зовут Механиком?";
			link.l1 = "Знаю. Вы придумали способ крепления кораблей Города между собой. Да и вообще, насколько я слышал"+ GetSexPhrase("","а") +", смастерить что-нибудь эдакое для вас не проблема.";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "Хорошо. Вы, наверное, понимаете, что я знаю о Городе больше, чем любой другой житель. К тому же, теперь я не делаю предположений, я говорю все абсолютно точно, так как изучил строение Города Потерянных Кораблей под водой.";
			link.l1 = "Под водой?";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = "Да. Несколько лет назад я смастерил костюм для дыхания под водой. В этом костюме я спускался под воду много раз, пока была такая возможность. И вот что я вам скажу - Город наверняка будет разрушен сильной бурей.";
			link.l1 = "Насколько я знаю, штормы здесь не редкость...";
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = "Вот, и вы тоже! Не спорьте со мной, это вопрос жизни и смерти!";
			link.l1 = "Хорошо-хорошо... Так что вы там говорили про дыхание под водой?";
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = "Я спускался под воду, изучал рифы. Так вот, Город держится всего на трех кораблях, которые зацепились за рифы. Остальные корабли попросту сцеплены с этими тремя! Понимаете, что это значит?";
			link.l1 = "М-да, неприятно это осознавать... А что будет, если Город оторвется? Мы ляжем в дрейф?";
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = "Ничего подобного! Всё пойдет ко дну, ведь корабли Города не на плаву. Не выживет никто, так как разрушение Города будет происходить в шторм, причем очень сильный шторм.";
			link.l1 = "Апокалипсис какой-то... И когда это произойдет?";
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = "Не знаю. Я ученый, а не медиум\nА вообще, это может произойти в любую бурю.";
			link.l1 = "Хм... и что делать?";
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = "Я могу помочь вам, если вы поможете мне.";
			link.l1 = "Интересное предложение. Расскажите подробней, пожалуйста.";
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = "Дело в том, что у меня есть корабль на плаву. Пару лет назад к Городу пристал фрегат с небольшой пробоиной в днище, и я сумел его починить. Пока у меня была такая возможность...";
			link.l1 = "Вы уже несколько раз упоминаете о какой-то утерянной возможности...";
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = "А-а, ну это возможность спускаться под воду в моем костюме. Дело в том, что под водой завелись здоровенные твари, которые ходят по дну и жрут все, что попало. Вот я и не рискую теперь спускаться. Я ведь ученый, а не боец...";
			link.l1 = "Понятно. Так что я долж"+ GetSexPhrase("ен","на") +" сделать?";
			link.l1.go = "FT_26";
		break;
		case "FT_26":
			dialog.text = "Сначала вы должны купить у меня фрегат. Затем достать со дна кое-что, без чего мы не сможем освободить фрегат от стискивающих его кораблей.";
			link.l1 = "Купить?! Хм, а вы что, не заинтересованы уйти отсюда и спасти свою шкуру? Ведь в случае предрекаемого вами апокалипсиса, погибнете и вы тоже!";
			link.l1.go = "FT_27";
		break;
		case "FT_27":
			dialog.text = "Ну, я же не знаю точно, когда случится катастрофа. К тому же, я вижу, что вы "+ GetSexPhrase("человек смелый и деятельный","девушка смелая и деятельная") +", и вам вполне по силам будет выполнить мои условия. Тем более, что я много не прошу, всего лишь полтора миллиона за фрегат и возможность один раз спуститься под воду.";
			link.l1 = "Полтора миллиона?! Я не ослышал"+ GetSexPhrase("ся","ась") +"?";
			link.l1.go = "FT_28";
		break;
		case "FT_28":
			dialog.text = "Нет, все верно.";
			link.l1 = "Но у меня нет таких денег!";
			link.l1.go = "FT_29";
		break;
		case "FT_29":
			dialog.text = "Ну, деньги здесь не проблема, "+ GetSexPhrase("друг мой","" + pchar.name + "") +". Ищите, и, полагаю, без труда отыщете нужную мне сумму, так как Город буквально напичкан ценностями. К тому же, можно занять у Августо Брамса, он охотно дает в долг до миллиона монет.";
			link.l1 = "Хех, про него ходят всякие слухи нехорошие... Говорят, что он чернокнижник.";
			link.l1.go = "FT_30";
		break;
		case "FT_30":
			dialog.text = "Ну вот, и вы туда же. Послушайте, я ученый, мракобесие мне чуждо... Да и вообще, я дам вам возможность спуститься по воду, а там денег еще больше!";
			link.l1 = "Да, но там же и какие-то твари обитают!";
			link.l1.go = "FT_30_1";
		break;
		case "FT_30_1":
			dialog.text = "Но вы же справились с 'касперами', справитесь и с этой проблемой... Ну, что же вы робеете?! Как будто это не вы только что положили целую орду головорезов...";
			link.l1 = "Хорошо, я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "FT_31";
		break;
		case "FT_31":
			dialog.text = "Ну, вот и отлично! Жду вас с деньгами, "+ GetSexPhrase("друг мой","леди") +", и это только первый вопрос. Сейчас вам нужно явиться к Чаду Капперу, рассказать ему, что я освободился, так сказать... Только никаких выборов! Иначе он убьет вас.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", что выборы того не стоят.";
			link.l1.go = "FT_32";
		break;
		case "FT_32":
			dialog.text = "Они просто не состоятся, вот и все... В общем, передавайте Чаду от меня привет, уведомите его об уничтожении 'касперов'. Не думаю, что это его обрадует, но сделать это нужно.";
			link.l1 = "Зачем?";
			link.l1.go = "FT_33";
		break;
		case "FT_33":
			dialog.text = "Но он же все равно узнает, если еще не узнал. Потому, хорошо бы было уведомить его от лица виновника торжества, так сказать. С Чадом нужно вести себя очень аккуратно, иначе...";
			link.l1 = "Что иначе?";
			link.l1.go = "FT_34";
		break;
		case "FT_34":
			dialog.text = "Иначе он прикончит вас, "+ GetSexPhrase("друг мой","дорогая") +". Не стоит злить адмирала, а вы это сделали. Чад имел дела с 'касперами', и я слышал в разговорах, что он готовился уплыть с ними из Города.";
			link.l1 = "Интересно... А почему же остальных не пускает?";
			link.l1.go = "FT_35";
		break;
		case "FT_35":
			dialog.text = "Чтобы никто не узнал о городе раньше положенного Чадом срока.";
			link.l1 = "Понятно... Ну что же, я все понял"+ GetSexPhrase("","а") +". Пош"+ GetSexPhrase("ел","ла") +" заниматься делами.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CheckMillion";
			pchar.questTemp.LSC = "fromMechanicToAdmiral";
			Npchar.quest.money = 0; //счетчик бабла, отданного Механику
			AddQuestRecord("ISS_MainLine", "40");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("ен", "на"));
		break;

		//проверка миллиона
		case "CheckMillion":
			dialog.text = "Ну что, как там дела с моими деньгами?";
			if (sti(pchar.money) < 20000)
			{
				link.l1 = "Пока не насобирал"+ GetSexPhrase("","а") +" практически ничего.";
				link.l1.go = "CheckMillion_noMoney";
			}
			else
			{
				link.l1 = "Кое-что имеется. Я готов"+ GetSexPhrase("","а") +" вручить вам некоторую сумму.";
				link.l1.go = "OffM_GiveMoney";
			}
			NextDiag.TempNode = "CheckMillion";
		break;
		case "CheckMillion_noMoney":
			dialog.text = "Ну что же, старайтесь, я думаю, что все у вас получится.";
			link.l1 = "Я тоже так думаю.";
			link.l1.go = "exit";
		break;
		case "OffM_GiveMoney":
			dialog.text = "Сколько?";
			link.l1 = "";
			Link.l1.edit = 6;
			link.l1.go = "OffM_GiveMoney_1";
		break;
		case "OffM_GiveMoney_1":
			iTemp = sti(dialogEditStrings[6]);
			if (iTemp <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Хм, извините, ошибочка вышла..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Хм, таких денег у вас при себе нет, к сожалению. Давайте без глупостей...";
				link.l1 = "Гм... хорошо.";
				link.l1.go = "exit";
				break;
			}
			Npchar.quest.money = sti(Npchar.quest.money) + iTemp;
			AddMoneyToCharacter(pchar, -iTemp);
			if (sti(Npchar.quest.money) < 1500000)
			{
				dialog.text = "Ну что же, отлично! Сейчас вы отдали мне " + FindRussianMoneyString(iTemp) + ", всего вы принесли мне " + FindRussianMoneyString(sti(Npchar.quest.money)) + ". Вам осталось раздобыть еще " + FindRussianMoneyString(1500000 - sti(Npchar.quest.money)) + ".";
				link.l1 = "Продолжу поиски.";
				link.l1.go = "exit";
				AddQuestRecord("ISS_MainLine", "41");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ISS_MainLine", "iMoney1", sti(Npchar.quest.money));
				AddQuestUserData("ISS_MainLine", "iMoney2", 1500000 - sti(Npchar.quest.money));
			}
			else
			{
				dialog.text = "Ну что же, дело сделано. Я получил требуемую сумму, теперь фрегат ваш.";
				link.l1 = "Очень хорошо. Что дальше?";
				link.l1.go = "FreeCorvett";
			}
		break;
		//освобождние корвета
		case "FreeCorvett":
			dialog.text = "Теперь фрегат нужно освободить. Дело в том, что он находится на внешнем кольце корабельного хлама острова и стиснут обломками со всех сторон.";
			link.l1 = "Ну и как это сделать?";
			link.l1.go = "FreeCorvett_1";
		break;
		case "FreeCorvett_1":
			dialog.text = "Я уже все подготовил. У меня на платформе стоит лебедка, к ней я прикрепил обломки вокруг фрегата. Так что стоит только привести механизм в действие - и вуаля, фрегат свободен!";
			link.l1 = "Звучит прекрасно. А в чем подвох?";
			link.l1.go = "FreeCorvett_2";
		break;
		case "FreeCorvett_2":
			dialog.text = "Да, подвох действительно имеется. Я уронил шестеренку от механизма лебедки в воду. Эту шестеренку нужно достать со дна.";
			link.l1 = "Та-ак... Если мне не изменяет память, вы говорили, что у вас есть костюм для дыхания под водой. В нем мне и предстоит осуществить спуск на дно?";
			link.l1.go = "FreeCorvett_3";
		break;
		case "FreeCorvett_3":
			dialog.text = "Да, именно так. Я бы и сам давно это сделал, но очень боюсь. Там эти здоровенные твари!..";
			link.l1 = "А вы их видели?";
			link.l1.go = "FreeCorvett_4";
		break;
		case "FreeCorvett_4":
			dialog.text = "Видел, и, признаться честно, обмочился со страха... Так что детально не разглядел. А вообще, нет, конечно, ничего удивительного, что под Городом существует эта прожорливая популяция.";
			link.l1 = "Ну, может они безобидные? Откуда вы знаете, что они прожорливы?";
			link.l1.go = "FreeCorvett_5";
		break;
		case "FreeCorvett_5":
			dialog.text = "Так они живут тем, что сбрасывается за борт жителями Города! Это единственная причина, по которой эти твари осели здесь.";
			link.l1 = "Понятно... Ну что же, я готов"+ GetSexPhrase("","а") +".";
			link.l1.go = "FreeCorvett_6";
		break;
		case "FreeCorvett_6":
			dialog.text = "Итак, давайте я расскажу, как пользоваться костюмом. Костюм заправляется сжатым воздухом, которым вы и дышите. Воздуха хватает на 6 минут беспрерывного дыхания под водой. За это время вы должны успеть всплыть на поверхность. Если этого не произойдет - вам конец. Все понятно?";
			link.l1 = "Понятно, что я ограничен"+ GetSexPhrase("","а") +" во времени пребывания под водой. Остальное непонятно.";
			link.l1.go = "FreeCorvett_7";
		break;
		case "FreeCorvett_7":
			dialog.text = "А это главное, что вам нужно помнить. Теперь вы можете идти на платформу, костюм находится там, заправлен воздухом на одно погружение. Полагаю, вы разберетесь без труда, как его надеть. Помните, что погружаться можно только днем, с десяти до девятнадцати часов. После использования поставьте костюм туда же, где взяли. Удачи вам в подводном мире!";
			link.l1 = "Спасибо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor";
			pchar.questTemp.LSC = "toUnderwater";
			pchar.questTemp.LSC.immersions = 0; //количество совершенных погружений
			pchar.questTemp.LSC.immersions.model = pchar.model; //запомним модельку ГГ
			pchar.questTemp.LSC.immersions.animation = pchar.model.animation;
			pchar.questTemp.LSC.immersions.pay = true; //оплачено
			pchar.questTemp.LSC.immersions.pinion = false; //флаг найденной шестеренки
			AddQuestRecord("ISS_MainLine", "42");
			pchar.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, false, pchar);
			SetBaseShipData(pchar);
			pchar.Ship.name = "Чёрная Жемчужина";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCharacterGoods(pchar, GOOD_BALLS, 0);
			SetCharacterGoods(pchar, GOOD_GRAPES, 0);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
			SetCharacterGoods(pchar, GOOD_BOMBS, 0);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 0);
			SetCharacterGoods(pchar, GOOD_PLANKS, 0);
			SetCharacterGoods(pchar, GOOD_POWDER, 0);
			SetCharacterGoods(pchar, GOOD_FOOD, 0);
			SetCharacterGoods(pchar, GOOD_WEAPON, 0);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 0);
			SetCrewQuantity(pchar, 0);
			AddSimpleRumourCityTip("Вы знаете, в Городе появился некий Механик. И говорят, что он старейший житель! Надо же...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Вы слышали о Хенрике Ведекере? Вот так дела! Оказывается, его держали взаперти на 'Сан Габриэле' много лет.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Говорят, что новый-старый житель Города, некий Хенрик Ведекер, очень способный человек.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("А я не верю, что этот Механик так важен для Города. Сколько жили без него, проживем и еще...", "LostShipsCity", 10, 1, "LSC", "");
			// нулим предметы в каюте
			ref loc;
			int n;
			if (Pchar.SystemInfo.CabinType != "")
			{
				loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

				for (n = 1; n <= 4; n++)
				{
					sTemp = "box" + n;
					DeleteAttribute(loc, sTemp + ".items");
					loc.(sTemp).items = "";
					loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
					loc.(sTemp).money = 0;
				}
			}
			loc = &locations[FindLocation("My_Deck")];
			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}
		break;
		//
		case "takeArmor":
			dialog.text = "Ну, как у вас дела?";
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = "Готовлюсь к погружению. Потом сообщу, как все прошло.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Мне нужно еще раз спуститься на дно. Не успел"+ GetSexPhrase("","а") +" сделать там все, что хотел"+ GetSexPhrase("","а") +".";
				link.l1.go = "DeepAgain";
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = "Я наш"+ GetSexPhrase("ел","ла") +" шестеренку, вот она!";
					link.l2.go = "FoundPinion";
				}
			}
		break;

		case "DeepAgain":
			dialog.text = "Я не против, костюм всегда в вашем распоряжении. Только за каждое погружение я вынужден с вас брать 30 тысяч пиастров. Так что деньги на бочку.";
			link.l1 = "Опять деньги нужны? Я же принес"+ GetSexPhrase("","ла") +" вам полтора миллиона!";
			link.l1.go = "DeepAgain_1";
		break;
		case "DeepAgain_1":
			dialog.text = "Эти деньги - плата за фрегат и за одно погружение. Я не обещал вам продать костюм, он остается у меня. Я сдаю его вам в аренду. Амортизация и все дела...";
			link.l1 = "Какая амортизация?";
			link.l1.go = "DeepAgain_2";
		break;
		case "DeepAgain_2":
			dialog.text = "Износ оборудования, вы об этом не знали? В общем, спорить бесполезно. Тридцать тысяч - и вы оправляетесь к морскому дьяволу на рандеву. Нет денег - нет погружений.";
			link.l1 = "Н-да, неплохо...";
			link.l1.go = "DeepAgain_3";
		break;
		case "DeepAgain_3":
			dialog.text = "Я не понимаю, на что вы жалуетесь. Я даю вам возможность заработать гораздо больше. Ведь на дне очень много ценностей. Если вы туда на прогулку спускались, то извините меня... В общем, нужно быть более расторопн"+ GetSexPhrase("ым","ой") +" там, на дне.";
			link.l1 = "Ясно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "takeArmor2":
			dialog.text = "Ну, как вас дела?";
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = "Собираюсь с силами для очередного погружения.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Я хочу еще раз спуститься на дно.";
				link.l1.go = "DeepAgain2";
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = "Я наш"+ GetSexPhrase("ел","ла") +" шестеренку, вот она!";
					link.l2.go = "FoundPinion";
				}
			}
			if (sti(pchar.questTemp.LSC.immersions.pinion))
			{
				link.l3 = "Все, я закончил"+ GetSexPhrase("","а") +" с погружениями. Более подводное царство меня не интересует.";
				link.l3.go = "endImmersion";
			}
		break;

		case "DeepAgain2":
			dialog.text = "Приготовили деньги?";
			if (sti(pchar.money) >= 30000)
			{
				link.l1 = "Да, готов"+ GetSexPhrase("","а") +" заплатить.";
				link.l1.go = "DeepAgain2_1";
			}
			else
			{
				link.l1 = "Нет еще... Но я их раздобуду обязательно.";
				link.l1.go = "exit";
			}
		break;
		case "DeepAgain2_1":
			dialog.text = "Отлично! Приходите завтра, я подготовлю костюм к работе.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -30000);
			SaveCurrentQuestDateParam("questTemp.LSC.immersions");
			NextDiag.TempNode = "readyArmor";
		break;
		case "readyArmor":
			if (GetQuestPastDayParam("questTemp.LSC.immersions") > 1)
			{
				dialog.text = "Все в порядке, костюм исправен и заправлен воздухом. В общем, все готово к погружению. Желаю удачи.";
				link.l1 = "Спасибо.";
				link.l1.go = "exit";
				pchar.questTemp.LSC.immersions.pay = true; //оплачено
				NextDiag.TempNode = "takeArmor2";
			}
			else
			{
				dialog.text = "Костюм не готов к работе. Приходите завтра.";
				link.l1 = "Хорошо.";
				link.l1.go = "exit";
			}
		break;

		case "FoundPinion":
			dialog.text = "Великолепно! Давайте ее быстрей...";
			link.l1 = "Да, конечно.";
			link.l1.go = "FoundPinion_1";
		break;
		case "FoundPinion_1":
			dialog.text = "Ну что же, теперь я могу заняться восстановлением механизма лебедки. Скажите, вы еще будете совершать погружения?";
			link.l1 = "Да, хочу более детально обследовать дно.";
			link.l1.go = "FoundPinion_deep";
			link.l2 = "Нет, подводное царство меня более не интересует.";
			link.l2.go = "endImmersion";
			TakeItemFromCharacter(pchar, "Pinion");
			pchar.questTemp.LSC.immersions.pinion = true; //нашел шестеренку
			AddQuestRecord("ISS_MainLine", "44");
		break;
		case "FoundPinion_deep":
			dialog.text = "Ну что же, здравая мысль. Мои условия вы знаете - 30 тысяч монет за каждое погружение. Дерзайте.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "endImmersion":
			dialog.text = "Ну что же, как скажете. Тогда я консервирую костюм.";
			link.l1 = "Как знаете.";
			link.l1.go = "endImmersion_1";
		break;
		case "endImmersion_1":
			dialog.text = "Теперь, когда у меня есть все необходимое, я займусь восстановлением механизма лебедки, которая освободит ваш фрегат. Это займет у меня определенное время. Вам же пока не следует почивать на лаврах, а стоит провести ряд важных подготовительных мероприятий.";
			link.l1 = "Что вы имеете в виду?";
			link.l1.go = "endImmersion_2";
		break;
		case "endImmersion_2":
			dialog.text = "Для начала обеспечьте корабль всем необходимым. Весь набор боеприпасов, продовольствие, оружие... Ну, не мне вас учить. Все найденное доставляйте на 'Сан Габриэль', а переправкой этого добра на фрегат я займусь сам.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", постараюсь все сделать.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.immersions");
			AddQuestRecord("ISS_MainLine", "45");
			pchar.questTemp.LSC = "toSeekGoods";
			NextDiag.TempNode = "takeGoods";
		break;
		//комплектование корвета товарами
		case "takeGoods":
			NextDiag.TempNode = "takeGoods";
			dialog.text = "Приветствую. Ну, как дела с заполнением трюма фрегата?";
			npchar.quest.LSC.Balls = false;
			npchar.quest.LSC.Grapes = false;
			npchar.quest.LSC.Knippels = false;
			npchar.quest.LSC.Bombs = false;
			npchar.quest.LSC.Sailcloth = false; //магазин
			npchar.quest.LSC.Planks = false; //магазин
			npchar.quest.LSC.Powder = false;
			npchar.quest.LSC.Food = false; //магазин
			npchar.quest.LSC.Weapon = false;
			npchar.quest.LSC.Medicament = false;
			iTemp = 0;
			npchar.quest.LSC.s0 = "";
			npchar.quest.LSC.s1 = "";
			if (GetCargoGoods(pchar , GOOD_BALLS) >= 100)
			{
				npchar.quest.LSC.Balls = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Balls;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " ядра,";
			if (GetCargoGoods(pchar , GOOD_GRAPES) >= 100)
			{
				npchar.quest.LSC.Grapes = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Grapes;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " картечь,";
			if (GetCargoGoods(pchar , GOOD_KNIPPELS) >= 100)
			{
				npchar.quest.LSC.Knippels = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Knippels;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " книппели,";
			if (GetCargoGoods(pchar , GOOD_BOMBS) >= 100)
			{
				npchar.quest.LSC.Bombs = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Bombs;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " бомбы,";
			if (GetCargoGoods(pchar , GOOD_SAILCLOTH) >= 50)
			{
				npchar.quest.LSC.Sailcloth = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Sailcloth;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " парусину,";
			if (GetCargoGoods(pchar , GOOD_PLANKS) >= 50)
			{
				npchar.quest.LSC.Planks = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Planks;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " доски,";
			if (GetCargoGoods(pchar , GOOD_POWDER) >= 200)
			{
				npchar.quest.LSC.Powder = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Powder;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " порох,";
			if (GetCargoGoods(pchar , GOOD_FOOD) >= 200)
			{
				npchar.quest.LSC.Food = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Food;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " провиант,";
			if (GetCargoGoods(pchar , GOOD_WEAPON) >= 50)
			{
				npchar.quest.LSC.Weapon = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Weapon;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " оружие,";
			if (GetCargoGoods(pchar , GOOD_MEDICAMENT) >= 50)
			{
				npchar.quest.LSC.Medicament = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Medicament;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " медикаменты,";
			if (iTemp < 10)
			{
				if (iTemp == 0)
				{
					link.l1 = "Пока ничего не раздобыл"+ GetSexPhrase("","а") +", но я стараюсь.";
				}
				else
				{
					sTemp = npchar.quest.LSC.s0;
					npchar.quest.LSC.s0 = strcut(sTemp, 0, (strlen(sTemp)-2));
					sTemp = npchar.quest.LSC.s1;
					npchar.quest.LSC.s1 = strcut(sTemp, 0, (strlen(sTemp)-2));
					link.l1 = "Кое-что уже есть. Удалось достать " + npchar.quest.LSC.s1 + ". Осталось раздобыть " + npchar.quest.LSC.s0 + ".";
				}
				link.l1.go = "takeGoods_again";
			}
			else
			{
				link.l1 = "Все, что нужно для плавания, у меня в трюме.";
				link.l1.go = "TakeCrew";
				DeleteAttribute(pchar, "questTemp.LSC.Balls");
				DeleteAttribute(pchar, "questTemp.LSC.Grapes");
				DeleteAttribute(pchar, "questTemp.LSC.Knippels");
				DeleteAttribute(pchar, "questTemp.LSC.Bombs");
				DeleteAttribute(pchar, "questTemp.LSC.Sailcloth");
				DeleteAttribute(pchar, "questTemp.LSC.Planks");
				DeleteAttribute(pchar, "questTemp.LSC.Powder");
				DeleteAttribute(pchar, "questTemp.LSC.Food");
				DeleteAttribute(pchar, "questTemp.LSC.Weapon");
				DeleteAttribute(pchar, "questTemp.LSC.Medicament");
				DeleteAttribute(pchar, "questTemp.LSC.additional");
			}
		break;
		case "takeGoods_again":
			dialog.text = "Ну что же, успехов. И постарайтесь не тянуть с этим делом.";
			link.l1 = "Это в моих интересах.";
			link.l1.go = "exit";
		break;
		//Набор команды
		case "TakeCrew":
			dialog.text = "Прекрасно, "+ GetSexPhrase("друг мой","дорогая моя") +", все уже размещено в трюме вашего фрегата. Теперь вам нужно набрать команду из жителей Города. Сами понимаете, вдвоем мы с фрегатом не управимся.";
			link.l1 = "Хех, а раньше нельзя было об этом сказать? Я оббегал"+ GetSexPhrase("","а") +" весь Город в поисках товаров на фрегат, заодно мог"+ GetSexPhrase("","ла") +" бы и команду набрать.";
			link.l1.go = "TakeCrew_1";
		break;
		case "TakeCrew_1":
			dialog.text = "Ну, во-первых, вряд ли бы это понравилось адмиралу. А во-вторых, я не очень-то и торопился. Но теперь дело принимает очень нехороший оборот.";
			link.l1 = "Что вы имеете в виду?";
			link.l1.go = "TakeCrew_2";
		break;
		case "TakeCrew_2":
			dialog.text = "Видите ли, я столько лет уже живу ожиданием той бури, что разрушит Город, что ждать в неведении мне осточертело. Не так давно я смастерил прибор, который показывает приближение штормов. Я его назвал 'штормометр'! Занимательная, знаете ли, штука...";
			link.l1 = "Как и все, что вы делаете... Так, что там поводу нехорошего оборота дел?";
			link.l1.go = "TakeCrew_3";
		break;
		case "TakeCrew_3":
			dialog.text = "А-а, ну да... Так вот, мой штормометр показывает, что на Город движется не просто шторм, а настоящая буря. Даже не знаю, какой силы - прибор зашкаливает.";
			link.l1 = "Получается, что время пришло?";
			link.l1.go = "TakeCrew_4";
		break;
		case "TakeCrew_4":
			dialog.text = "Именно так, "+ GetSexPhrase("друг мой","" + pchar.name + "") +". Я могу сказать с очень большой долей вероятности, что сейчас город будет разрушен. Так что поторопитесь.";
			link.l1 = "Хорошо, я так и сделаю. Кстати, вы сумели освободить фрегат?";
			link.l1.go = "TakeCrew_5";
		break;
		case "TakeCrew_5":
			dialog.text = "Еще нет, но опробовал лебедку, она в полной готовности. Договаривайтесь с людьми, пусть они прибывают сюда, а я буду переправлять их на корабль. Нам нужно хотя бы пятнадцать человек, чтобы отплыть. Как только вы соберете необходимое количество - сразу же бегите сюда. По вашему прибытию на 'Сан Габриэль', мы задействуем лебедку и освободим фрегат.";
			link.l1 = "Хорошо, я вас понял"+ GetSexPhrase("","а") +". Начну договариваться.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TakeCrewNew";
			AddQuestRecord("ISS_MainLine", "59");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ен","на"));
			pchar.questTemp.LSC = "toSeekPeopleInCrew";
			pchar.questTemp.LSC.crew = 0; //количество уговоренных людей.
			AddDialogExitQuestFunction("LSC_SmallStormIsBegin");
		break;
		//прием народа в команду
		case "TakeCrewNew":
			if (sti(pchar.questTemp.LSC.crew) > 0)
			{
				dialog.text = "Вы еще не набрали достаточного количества людей для плавания. Всего ко мне прибыли " + FindRussianPeoplesString(sti(pchar.questTemp.LSC.crew), "Acc") + ". Продолжайте, и прошу вас - быстрей...";
			}
			else
			{
				dialog.text = "Вы еще никого не уговорили пойти к вам в команду. Поторопитесь!";
			}
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
		break;
		//разговор в тюрьме
		case "inPrison":
			dialog.text = "Ага, вот и вы!";
			link.l1 = "Точно! Приш"+ GetSexPhrase("ел","ла") +" на выручку.";
			link.l1.go = "inPrison_1";
		break;
		case "inPrison_1":
			dialog.text = "Ну что же, спасибо, не ожидал... Только все зря.";
			link.l1 = "Как понять?";
			link.l1.go = "inPrison_2";
		break;
		case "inPrison_2":
			dialog.text = "Я заперт в этой камере, а ключ конвоиры унесли адмиралу. Это был его приказ начальнику тюрьмы. Мне не вырваться из этой клетки.";
			if (CheckCharacterItem(pchar, "key_mechanic"))
			{
				link.l1 = "Адмирала больше нет, я разделал"+ GetSexPhrase("ся","ась") +" с ним. При нём был вот этот ключ. Тот?";
				link.l1.go = "inPrison_3_alt";
			}
			link.l2 = "Адмирала больше нет, я разделал"+ GetSexPhrase("ся","ась") +" с ним. Но никакого ключа не находил"+ GetSexPhrase("","а") +"... Я вернусь и поищу!";
			link.l2.go = "inPrison_3";
		break;
		case "inPrison_3":
			dialog.text = "Поздно, "+ GetSexPhrase("друг мой","" + pchar.name + "") +". Буря набирает силу.";
			link.l1 = "Я успею!";
			link.l1.go = "inPrison_4";
		break;
		case "inPrison_4":
			dialog.text = "Нет, это вряд ли. Да и не стоит рисковать фрегатом и жизнями стольких людей, что уже находятся на нем. Слушайте, что вам нужно сделать...";
			link.l1 = "Хенрик, я успею и освобожу вас.";
			link.l1.go = "inPrison_5";
		break;
		case "inPrison_5":
			dialog.text = "Я решил, что остаюсь. Проверю, как говорится, воочию, правильность своей теории. Большое дело для ученого - видеть собственными глазами воплощение в жизнь своих прогнозов.\nК тому же, возможно, я ошибался, и город устоит перед натиском стихии. Тогда оставшиеся здесь начнут новую жизнь, без кланов и адмирала.";
			link.l1 = "Вы уверены?";
			link.l1.go = "inPrison_6";
		break;
		case "inPrison_6":
			dialog.text = "Да, я так решил. А теперь слушайте, что вы должны сделать, чтобы попасть на свой фрегат.";
			link.l1 = "Я слушаю.";
			link.l1.go = "inPrison_7";
		break;
		case "inPrison_7":
			dialog.text = "Отправляйтесь ко второй мачте 'Фернадо Диффиндура', оттуда до корабля уже рукой подать. Я успел использовать лебедку до ареста и растащил корабли, окружающие фрегат. Теперь вы с легкостью оторветесь от Города.\nШторм набирает силу, боюсь, что сейчас вам придется нелегко... При выходе из 'Тартаруса', вы должны четко представлять себе, куда направиться - направо отсюда. Иначе в этом хаосе вы погибнете. Я еще раз повторю, что вы должны двигаться по направлению ко второй мачте 'Фернандо Диффиндура'.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", спасибо вам... Может быть, все-таки попытаться открыть это чертову клетку?";
			link.l1.go = "inPrison_8";
		break;
		case "inPrison_8":
			dialog.text = "Прощайте, мне было приятно иметь с вами дело. Теперь моя судьба - не ваша забота...";
			link.l1 = "Прощайте, Хенрик Ведекер. Желаю вам выжить в этом шторме.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "67");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся","ась"));
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
		case "inPrison_3_alt":
			dialog.text = "Тот самый. Давайте его сюда, скорее.";
			TakeItemFromCharacter(pchar, "key_mechanic");
			link.l1 = "Держите. Что дальше?";
			link.l1.go = "inPrison_4_alt";
		break;
		case "inPrison_4_alt":
			dialog.text = "Отправляйтесь ко второй мачте 'Фернадо Диффиндура', оттуда до корабля уже рукой подать. Я успел использовать лебедку до ареста и растащил корабли, окружающие фрегат. Теперь вы с легкостью оторветесь от Города.\nШторм набирает силу, боюсь, что сейчас вам придется нелегко... При выходе из 'Тартаруса', вы должны четко представлять себе, куда направиться - направо отсюда. Иначе в этом хаосе вы погибнете. Я еще раз повторю, что вы должны двигаться по направлению ко второй мачте 'Фернандо Диффиндура'.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", спасибо вам.";
			link.l1.go = "inPrison_5_alt";
		break;
		case "inPrison_5_alt":
			dialog.text = "Я буду следом за вами. Надеюсь, не потонем.";
			link.l1 = "Я тоже... Я тоже...";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "71");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
			//офицер
			ref sld = GetCharacter(NPC_GenerateCharacter("Mechanic1", "CCS_Mechanic", "man", "man", 30, SPAIN, -1, true));
			sld.name = "Хенрик";
			sld.lastname = "Ведекер";
			sld.greeting = "Gr_questOfficer";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			// Прописка всех моделей для кирас. -->
         	sld.HeroModel = "CCS_Mechanic,CCS_Mechanic_1,CCS_Mechanic_2,CCS_Mechanic_3,CCS_Mechanic_4,CCS_Mechanic_5,CCS_Mechanic,CCS_Mechanic,CCS_Mechanic";
        	// Прописка всех моделей для кирас. <--
			sld.quest.meeting = true;
			SetSelfSkill(sld, 30, 30, 30, 30, 99);
			SetShipSkill(sld, 55, 50, 60, 45, 65, 100, 50, 90, 50);
			SetSPECIAL(sld, 6, 10, 9, 10, 10, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LightRepair");
			SetCharacterPerk(sld, "InstantRepair");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "Carpenter");
			SetCharacterPerk(sld, "Builder");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			TakeNItems(sld, "talisman7", 1);
			EquipCharacterbyItem(sld, "talisman7");
			sld.quest.OfficerPrice = sti(pchar.rank)*350;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			sld.loyality = MAX_LOYALITY;
			pchar.VedekerDiscount = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
	}
}
