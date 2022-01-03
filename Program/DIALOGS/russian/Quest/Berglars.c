
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp, sStr, sPlace;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (!CheckAttribute(NPChar,"refreshanim")) NPChar.refreshanim = "yes";
    if (NPChar.refreshanim == "yes")
    {
        if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) NPChar.model.animation = "spy"; //LEO: Превозмогаторам страдать 08.12.2021
        Characters_RefreshModel(NPChar);
        if (bHardBoss) NPChar.AlwaysReload = true;//перезарядка независимо от Дозарядки
        NPChar.refreshanim = "no";
    }
	if (Dialog.CurrentNode == "First time")
	{
		switch (pchar.questTemp.tugs.berglarState)
		{
			case "2": Dialog.CurrentNode = "Second time";	break;
			case "3": Dialog.CurrentNode = "Third time";	break;
			case "4": Dialog.CurrentNode = "Fourth time";	break;
			case "5": Dialog.CurrentNode = "Fifth time";	break;
			case "6": Dialog.CurrentNode = "Sixth time";	break;
		}
	}

	switch (Dialog.CurrentNode)
    {
        //------------- первая боевка --------------
		case "First time":
            dialog.text = "Постой, "+ GetSexPhrase("приятель","подруга") +"... Будь добр"+ GetSexPhrase("","а") +", скажи мне, как тебя зовут?";
            if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = GetFullName(pchar) + " собственной персоной. А что такое?";
				link.l1.go = "Step1_1";
			}
			link.l2 = "Простите, но я сейчас ничего не покупаю и не продаю. До свидания.";
			link.l2.go = "exit";
        break;
 		case "Step1_1":
        	dialog.text = "Ага, ты-то мне и нуж"+ GetSexPhrase("ен","на") +"...";
    		link.l1 = "Внимательно слушаю.";
    		link.l1.go = "Step1_2";
		break;
 		case "Step1_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "под";
			else sStr = "за";
        	dialog.text = "Это хорошо, что внимательно, так как нам нужно обсудить нечто важное... Значит, так: я буду ждать тебя в подземелье, что находится " + sStr + " городом.";
    		link.l1 = "Может, в таверну пойдем, там обсудим? Какого дьявола таскаться по норам?";
    		link.l1.go = "Step1_3";
		break;
 		case "Step1_3":
        	dialog.text = "Нет, лишние уши и глаза нам не нужны, ты уж поверь мне...";
    		link.l1 = "Хм, даже не знаю... А дело того стоит?";
    		link.l1.go = "Step1_4";
		break;
 		case "Step1_4":
        	dialog.text = "Дело жизни и смерти, "+ GetSexPhrase("приятель","подруга") +".\nНу ладно, некогда мне с тобой рассусоливать здесь, жду тебя в подземелье до полуночи. Не придешь - как знаешь...";
    		link.l1 = "Вот еще что хотел"+ GetSexPhrase("","а") +" спросить...";
    		link.l1.go = "Step_overAll";
		break;
		//--------------
        case "Fight_1":
            dialog.text = "А-а-а, приш"+ GetSexPhrase("ел","ла") +" все-таки...";
            link.l1 = "Да, приш"+ GetSexPhrase("ел","ла") +". Говори скорей, что там у тебя за дело жизни и смерти?";
            link.l1.go = "FirstFight_1";
        break;
		case "FirstFight_1":
            dialog.text = "Так и есть, "+ GetSexPhrase("приятель","подруга") +", так и есть... Давай уточним детали - дело ТВОЕЙ смерти.";
            link.l1 = "О чем это ты?";
            link.l1.go = "FirstFight_2";
        break;
		case "FirstFight_2":
            dialog.text = "Надеюсь, ты исповедовал"+ GetSexPhrase("ся","ась") +" недавно. Сейчас ты отправишься к праотцам, хорошо бы уш"+ GetSexPhrase("ел","ла") +" причащенн"+ GetSexPhrase("ым","ой") +", а то я буду переживать за тебя...";
            link.l1 = "Хех, ценю заботу. Ты, вообще, знаешь, кто я так"+ GetSexPhrase("ой","ая") +", чтобы вот так со мной разговаривать?";
            link.l1.go = "FirstFight_3";
        break;
		case "FirstFight_3":
            dialog.text = "Капитан как"+ GetSexPhrase("ой","ая") +"-то, а большего мне знать и не надо. Не ты перв"+ GetSexPhrase("ый из дурачков","ая дурочка") +", что сюда приходят, здесь же и остаются навечно. "+ GetSexPhrase("","Хотя нет, ты первая дурочка, остальные дурачки были. ") +"Кстати, ты стоишь прямо на одном таком, хороший был парень. А красив был, как Аполлон.\nПонимаешь, я обязательно должен тебя убить, иначе никак.";
            link.l1 = "Надо же, никогда бы не подумал"+ GetSexPhrase("","а") +", что за такой внешностью может скрываться циничный убийца...";
            link.l1.go = "FirstFight_4";
		break;
		case "FirstFight_4":
            dialog.text = "Хех, на это и расчет, "+ GetSexPhrase("приятель","подруга") +", внешность обманчива. Хотел сказать - запомни на будущее, но какое у тебя будущее...";
			link.l1 = "Хочется надеяться - счастливое...";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ вторая боевка ----------------
        case "Second time":
            dialog.text = "Скажите, я могу отнять минуту вашего времени?";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Можете.";
				link.l1.go = "Step2_1";
			}
			link.l2 = "Простите, но я сейчас ничего не покупаю и не продаю. До свидания.";
			link.l2.go = "exit";
        break;
        case "Step2_1":
            dialog.text = "Ваше имя...";
            link.l1 = GetFullName(pchar) + ". И что?";
            link.l1.go = "Step2_2";
        break;
        case "Step2_2":
            dialog.text = "Тогда вы-то мне и нужны. У меня есть кое-что для вас, мне нужно встретиться с вами в уединенной обстановке.";
            link.l1 = "Давайте пройдем в таверну.";
            link.l1.go = "Step2_3";
        break;
        case "Step2_3":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "под";
			else sStr = "за";
            dialog.text = "Простите, но я не могу этого сделать, и поверьте, причина есть. Я не могу долго разговаривать с вами, так что прошу вас явиться в подземелье, что находится " + sStr + " городом.";
            link.l1 = "Хех, что-то мне это напоминает...";
            link.l1.go = "Step_overAll";
        break;
		//----------
        case "Fight_2":
            dialog.text = "Дождался...";
            link.l1 = "Да, как видишь, я приш"+ GetSexPhrase("ел","ла") +". Что у тебя ко мне, говори быстрей!";
            link.l1.go = "SecondFight_1";
        break;
        case "SecondFight_1":
            dialog.text = "Выкладывай все, что у тебя есть, и рассказывай, какой у тебя корабль, что за товар в трюмах...";
            link.l1 = "С какой это стати?";
            link.l1.go = "SecondFight_2";
        break;
        case "SecondFight_2":
            dialog.text = "Говори, "+ GetSexPhrase("идиот","дуреха") +", иначе вмиг лишишься головы!";
            link.l1 = "Тьфу, напасть какая-то! Ты второй уже, кто пытается меня убить таким вот образом.";
            link.l1.go = "SecondFight_3";
        break;
        case "SecondFight_3":
            dialog.text = "Хм, вот оно как\nНу что же, теперь мне кое-что ясно...";
            link.l1 = "И что тебе ясно?";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ третья встреча, сумасшедший ----------------
        case "Third time":
            dialog.text = "Берегись оптиматов, "+ GetSexPhrase("приятель","подруга") +"!";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Чего?";
				link.l1.go = "Step3_1";
			}
			link.l2 = "С дороги, а не то я позову стражу, сумасшедший!";
			link.l2.go = "exit";
        break;
        case "Step3_1":
            dialog.text = "Сулланские проскрипции - откровенное зло! Знал бы он, что это сотворит с империей...";
            link.l1 = "Ты о чем это?";
            link.l1.go = "Step3_2";
        break;
        case "Step3_2":
            dialog.text = "Как о чем? Как ты не понимаешь?!\n'Берегись плохо подпоясавшегося юнца' - вот что Сулла говорил оптиматам, и был прав! Божественный Юлий уничтожил остатки республики...";
            link.l1 = "Приятель, по всему видать, ты сильно болен. Так что извини, но я пойду...";
            link.l1.go = "Step3_3";
        break;
        case "Step3_3":
            dialog.text = "Куда?! Куда ты пойдешь? Зло на каждом шагу, и ты уже имел"+ GetSexPhrase("","а") +" несчастье познакомиться с его ледяным прикосновением. Дважды попасть в ловушку и избежать смерти, хи-хи-хи...";
            link.l1 = "Это ты о странных людях, что зазывали меня в подземелье и пытались убить?";
            link.l1.go = "Step3_4";
        break;
        case "Step3_4":
            dialog.text = "Именно так, "+ GetSexPhrase("друг мой","милая") +", именно так...";
            link.l1 = "Черт возьми, кто они такие?!";
            link.l1.go = "Step3_5";
        break;
        case "Step3_5":
            dialog.text = "Хи-хи-хи, не скажу...";
            link.l1 = "Скажешь, не то шею мигом сверну!";
            link.l1.go = "Step3_6";
        break;
        case "Step3_6":
            dialog.text = "Я уже не боюсь... Я ведь тоже убивал капитанов, мне приходилось это делать... А-а-а-а, страх пожирал мою душу!!!\nНо теперь все кончилось, я больше не боюсь. И мне надо спешить! Нужно предупредить Августа, чтобы он не прогревал желчный пузырь, а наоборот, делал холодный компресс. Тогда желчь выйдет...";
            link.l1 = "Чего?!";
            link.l1.go = "Step3_7";
        break;
        case "Step3_7":
            dialog.text = "Да ничего, тебя это не касается. Это мои дела с Цезарями!";
            link.l1 = "А-а-а, понятненько...";
            link.l1.go = "Step3_8";
        break;
        case "Step3_8":
            dialog.text = "Ну, а ты ищи их. Тебе нужно добраться до Остина раньше, чем они узнают, что это ты убил"+ GetSexPhrase("","а") +" двоих. Будь осторож"+ GetSexPhrase("ен","на") +" и хит"+ GetSexPhrase("ер","ра") +", не спугни их, иначе они исчезнут!";
            link.l1 = "Остин?..";
            link.l1.go = "Step3_9";
        break;
        case "Step3_9":
			sTemp = "berglar" + npchar.city;
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счетчик
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        //------------ четвертая встреча ----------------
        case "Fourth time":
            dialog.text = "Здравствуйте, " + GetAddress_Form(NPChar) + ".";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Здравствуйте. Чем обязан"+ GetSexPhrase("","а") +"?";
				link.l1.go = "Step4_1";
			}
			link.l2 = "Простите, но я сейчас ничего не покупаю и не продаю. До свидания.";
			link.l2.go = "exit";
        break;
        case "Step4_1":
            dialog.text = "Послушайте, у меня есть для вас вещица, которая бесспорно вас заинтересует. И по сходной цене!";
            link.l1 = "Ну что же, я всегда рад"+ GetSexPhrase("","а") +" деловым предложениям. Выкладывай, что там у тебя.";
            link.l1.go = "Step4_2";
        break;
        case "Step4_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "под";
			else sStr = "за";
            dialog.text = "Только не здесь, " + GetAddress_Form(NPChar) + ". Нам лишние глаза и уши не нужны. Я буду ждать вас до полуночи в подземелье, что находится " + sStr + " городом. Приходите, не пожалеете!";
            link.l1 = "Знаешь, приятель, ты уже третий невзрачный тип, что зазывает меня в местные катакомбы. Прошлые два раз кончились большими неприятностями...";
            link.l1.go = "Step4_3";
            link.l2 = "Хех, с удовольствием явлюсь на место встречи, ты меня заинтриговал. Вещица дорогостоящая?";
            link.l2.go = "Step4_5";
        break;
        case "Step4_3":
            dialog.text = "Ах, вот оно что... Простите, наша сделка отменяется.";
            link.l1 = "Неужели?!";
            link.l1.go = "Step4_4";
        break;
        case "Step4_4":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        case "Step4_5":
            dialog.text = "Да уж, не дешевая.";
            link.l1 = "Тогда захвачу побольше денег!";
            link.l1.go = "Step4_6";
        break;
        case "Step4_6":
            dialog.text = "Ну что же, жду вас с нетерпением, " + GetAddress_Form(NPChar) + ".";
            link.l1 = "До скорой встречи, приятель.";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_4":
            dialog.text = "А-а-а, ну наконец-то!";
            link.l1 = "Выкладывай, что там у тебя.";
            link.l1.go = "Fight4_1";
        break;
        case "Fight4_1":
            dialog.text = "Хех, это ты выкладывай. Сколько денег принес"+ GetSexPhrase("","ла") +"?";
            link.l1 = "Покажи сначала свой товар.";
            link.l1.go = "Fight4_2";
        break;
        case "Fight4_2":
			dialog.text = "Да нет никакого товара, ты так еще и не понял"+ GetSexPhrase("","а") +"?";
            link.l1 = "Чтобы это понять, особого ума не надо. Ты ведь третий по счету, кто пытается меня таким вот образом ограбить. Так что колись, кто вы такие и кто такой Остин?";
            link.l1.go = "Fight4_3";
        break;
        case "Fight4_3":
            dialog.text = "Не ожидал такого поворота...";
            link.l1 = "Понимаю... Ну, хватит тянуть кота за хвост, немедленно отвечай на вопросы или умрешь!";
            link.l1.go = "Fight4_4";
        break;
        case "Fight4_4":
            dialog.text = "Хм, я бы не был так категоричен.";
            link.l1 = "Нарываешься, значит...";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ пятая встреча ----------------
        case "Fifth time":
            dialog.text = "Здравствуйте, " + GetAddress_Form(NPChar) + ". Скажите, не вы ли т"+ GetSexPhrase("от","а") +" знаменит"+ GetSexPhrase("ый капитан","ая женщина-капитан") +", что привез"+ GetSexPhrase("","ла") +" из Старого Света крупный груз копры?";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Нет, я не занимаюсь транзитными перевозками в Старый Свет.";
				link.l1.go = "Step5_1";
			}
			link.l2 = "Простите, но я сейчас ничего не покупаю и не продаю. До свидания.";
			link.l2.go = "exit";
        break;
        case "Step5_1":
            dialog.text = "Ах, как жаль, как жаль! Я хотел предложить "+ GetSexPhrase("этому капитану","ей") +" в крайней степени выгодную сделку.";
            link.l1 = "Вам нужна именно копра?";
            link.l1.go = "Step5_2";
        break;
        case "Step5_2":
            dialog.text = "Нет, что вы! У меня есть малогабаритный, но весьма дорогостоящий товар. Это как раз то, о чем мечтают торговые капитаны - минимум места на судне и максимум выгоды.";
            link.l1 = "И что это за товар? Возможно, я заинтересуюсь этим.";
            link.l1.go = "Step5_3";
        break;
        case "Step5_3":
            dialog.text = "Хм, капитан, так просто я об этом сказать не могу. Сами понимаете - безопасность превыше всего. Не могу я первому встречному выкладывать все карты.";
            link.l1 = "А как же я, или любой другой капитан, сможет оценить целесообразность сделки, если вы не желаете говорить о товаре?";
            link.l1.go = "Step5_4";
        break;
        case "Step5_4":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "под";
			else sStr = "за";
            dialog.text = "Я готов все обсуждать в полном объеме, но не здесь. Предлагаю встретиться с вами наедине в подземелье, что находится " + sStr + " городом. Времени это займет немного, но я буду уверен в собственной безопасности.";
            link.l1 = "Хех, рандеву в подземельях мне уже назначали трижды. И все три раза там меня пытались убить.";
            link.l1.go = "Step5_5";
            link.l2 = "Полагаю, это справедливое требование. В наши времена надо быть оч-ч-чень осторожным...";
            link.l2.go = "Step5_7";
        break;
        case "Step5_5":
            dialog.text = "В таком случае, нам не о чем говорить!";
            link.l1 = "...";
            link.l1.go = "Step5_6";
        break;
        case "Step5_6":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        case "Step5_7":
            dialog.text = "Ну, вот и договорились. Я буду ждать вас там до полуночи, если вы не придете - все отменяется.";
            link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +".";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_5":
            dialog.text = "Так-так, ну что же, превосходно!";
            link.l1 = "Показывай свой товар.";
            link.l1.go = "Fight5_1";
        break;
        case "Fight5_1":
            dialog.text = "Ты знаешь, у меня неприятная новость. Товар пропал, но заплатить тебе за него придется.";
            link.l1 = "Хм, все как всегда...";
            link.l1.go = "Fight5_2";
        break;
        case "Fight5_2":
            dialog.text = "Ты это о чем?";
            link.l1 = "На моей памяти ты уже четвертый проходимец, что пытается меня ограбить таким вот образом. У вас что, сезон охоты на меня открыт?";
            link.l1.go = "Fight5_3";
        break;
        case "Fight5_3":
            dialog.text = "Так это ты убил"+ GetSexPhrase("","а") +" их всех?! Хм, достойный противник...";
            link.l1 = "Говори, где Остин, и будешь жить.";
            link.l1.go = "Fight5_4";
        break;
        case "Fight5_4":
            dialog.text = "Если я скажу, где Остин, мне в любом случае крышка, банда не прощает предательства. А так у меня есть шанс выжить.";
            link.l1 = "Выжить в схватке со мной у тебя шансов нет. Говори, проживешь дольше, по крайней мере...";
            link.l1.go = "Fight5_5";
        break;
        case "Fight5_5":
            dialog.text = "Все-таки я попытаюсь!";
            link.l1 = "Хм, как знаешь...";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ шестая встреча ----------------
        case "Sixth time":
            dialog.text = "Здравствуйте " + GetAddress_Form(NPChar) + ". Скажите, вы капитан " + GetFullName(pchar) + "?";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Да, так меня зовут.";
				link.l1.go = "Step6_1";
			}
			link.l2 = "Простите, но я сейчас ничего не покупаю и не продаю. До свидания.";
			link.l2.go = "exit";
        break;
        case "Step6_1":
			dialog.text = "У меня для вас сообщение: некто Остин хочет с вами увидеться.";
            link.l1 = "Хм, я соглас"+ GetSexPhrase("ен","на") +".";
            link.l1.go = "Step6_2";
        break;
        case "Step6_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "под";
			else sStr = "за";
            dialog.text = "Прекрасно. Он будет ждать вас до полуночи в подземелье, что находится " + sStr + " городом.";
            link.l1 = "Все как всегда... Ну, хорошо.";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_6":
            dialog.text = "А, вот и вы...";
            link.l1 = "Где Остин?";
            link.l1.go = "Fight6_1";
        break;
        case "Fight6_1":
            dialog.text = "Его самого здесь нет, но он передавал вам привет и приказал вас убить.";
            link.l1 = "Хм, ничего нового. А ты знаешь, что случилось с теми, кто пытался это сделать до тебя?";
            link.l1.go = "Fight6_2";
        break;
        case "Fight6_2":
            dialog.text = "Знаю, но я полагаю, что у меня получится.";
            link.l1 = "Ну, а сам-то Остин где, мать его? Утомил он меня уже, честно говоря.";
            link.l1.go = "Fight6_3";
        break;
        case "Fight6_3":
            dialog.text = "Он живет в одном из поселений ловцов жемчуга, на западной стороне Мейна.";
            link.l1 = "Ну, спасибо за информацию, никогда бы не догадал"+ GetSexPhrase("ся","ась") +", что главарь шайки грабителей и убийц скрывается так далеко.";
            link.l1.go = "Fight6_4";
        break;
        case "Fight6_4":
            dialog.text = "Ну, а теперь давай проверим, сумеешь ли ты воспользоваться этим знанием.";
            link.l1 = "Как скажешь, приятель...";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "1");
        break;
		//------------ общие ноды ----------------
 		case "Step_overAll":
			sTemp = "berglar" + npchar.city;
			sStr = "Birglars_fight_" + npchar.index;
			pchar.quest.(sStr).win_condition.l1 = "locator";
			pchar.quest.(sStr).win_condition.l1.location = pchar.questTemp.tugs.(sTemp);
			pchar.quest.(sStr).win_condition.l1.locator_group = "item";
			pchar.quest.(sStr).win_condition.l1.locator = "berglar1";
			pchar.quest.(sStr).function = "Birglars_fight";
			pchar.quest.(sStr).city = npchar.city; //запомним город грабителя
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "Fight_" + pchar.questTemp.tugs.berglarState;
			if (npchar.city == "SentJons")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade22"));
			}
			if (npchar.city == "FortFrance")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade31"));
			}
			if (npchar.city == "Marigo")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade34"));
			}
			if (npchar.city == "Panama")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade21"));
			}
			if (npchar.city == "Cartahena")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("topor2"));
			}
			if (npchar.city == "SantaCatalina")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade15"));
			}
			sTemp = "berglar" + npchar.city;
			LAi_LocationDisableMonGenTimer(pchar.questTemp.tugs.(sTemp), 1); //монстров не генерить 1 день
			LAi_LocationDisableOffGenTimer(pchar.questTemp.tugs.(sTemp), 1); //офицеров не пускать 1 день
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, pchar.questTemp.tugs.(sTemp), "item", "berglar1", "OpenTheDoors", -1.0);
			chrDisableReloadToLocation = true;
			//pchar.questTemp.tugs.(sTemp) = "fight";
			DialogExit();
		break;
		case "FirstFight_overAll":
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счетчик
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			SetCharacterPerk(npchar, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			npchar.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
			sTemp = "berglar" + npchar.city;

			// дадим слухи
			if(sti(pchar.questTemp.tugs.berglarState) == 2)
			{
				AddSimpleRumourCityTip("Ох, в неспокойные мы с вами, " + GetAddress_Form(pchar) + ", времена живём. У нас вот давеча судно встало на рейд, капитан его на берег сошёл, а на борт так и не поднялся. Только через неделю, в пещерах за городом, стража нашла его труп... с перерезанной от уха до уха глоткой!.. " +
					"Во время дознания местные отвечали, что видели того капитана по пути к пещере с каким-то ничем не примечательным на первый взгляд проходимцем. Так что, у нас нужно глядеть в оба...", npchar.city, 3, 1, "habitue", "");
			}
			if(sti(pchar.questTemp.tugs.berglarState) == 4)
			{
				AddSimpleRumourCityTip("Была тут у нас история - капитан один пропал... сошел с корабля и ни слуху, ни духу. Нашли его почитай через месяц, в пещере за городом. Голова прострелена, а в карманах - ни гроша! Да то, " + GetAddress_Form(pchar) + ", скажу я вам, не нечисть никак! Нечисть по карманам не шарит. Тут дело в другом, это точно!.. " +
					"Слыхал я, в Сент-Джонсе капитаны так же пропадали, и не единожды... Ну, вздрогнем...", npchar.city, 3, 1, "habitue", "");
			}

			LAi_SetHP(npchar, stf(pchar.questTemp.tugs.(sTemp).hp), stf(pchar.questTemp.tugs.(sTemp).hp));
			LAi_SetCurHPMax(npchar);
			chrDisableReloadToLocation = true;
			DeleteAttribute(npchar, "city"); //чтобы не ругались с нацией
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (npchar.id == "BerglarFortFrance")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "spy", 18, PIRATE, 0, true)); //LEO: Превозмогаторам страдать 08.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man_fast", 18, PIRATE, 0, true));
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				FantomMakeCoolFighter(sld, 18, 60, 50, BLADE_LONG, "pistol3", 10);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarPanama")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "spy", 21, PIRATE, 0, true)); //LEO: Превозмогаторам страдать 08.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man_fast", 21, PIRATE, 0, true));
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				FantomMakeCoolFighter(sld, 21, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarSantaCatalina")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "spy", 20, PIRATE, 0, true)); //LEO: Превозмогаторам страдать 08.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man_fast", 20, PIRATE, 0, true));
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        //------------ финальная боевка с Остином ----------------
        case "Final_fight":
            dialog.text = "Приветствую посетителя, это редкость для нашей глуши. Чем обязан?";
            link.l1 = "Добрый день, Остин. Решил"+ GetSexPhrase("","а") +" посмотреть на тебя лично, так сказать. А то одни приветы передают, и все в подземельях...";
            link.l1.go = "StepF1_1";
        break;
        case "StepF1_1":
            dialog.text = "Остин? Немногие знают это мое имя... А-а, я понял. Ты и есть т"+ GetSexPhrase("от","а") +" капитан, что убил"+ GetSexPhrase("","а") +" нескольких моих людей. " + GetFullName(pchar) + ", если не ошибаюсь...";
            link.l1 = "Именно так, Остин... Скажи-ка мне, приятель, что же это делается на свете? По городам шатаются убийцы, заманивают доверчивых капитанов и вспарывают им кишки.";
            link.l1.go = "StepF1_2";
        break;
        case "StepF1_2":
            dialog.text = "Ушам не верю! Ты что, пристыдить меня хочешь? И это мне говорит "+ GetSexPhrase("капитан, который","девчонка, которая") +" занимается ровно тем же!";
            link.l1 = "Что это значит?!";
            link.l1.go = "StepF1_3";
        break;
        case "StepF1_3":
            dialog.text = "Не ты ли гоняешься по морю за торговцами? Не ты ли убиваешь людей сотнями? И я хочу задать вопрос, ради чего? И сам же на него отвечу - ради денег.\nМы с тобой "+ GetSexPhrase("братья","родные") +" по крови своих жертв, только я - сухопутный брат.";
            link.l1 = "Я не заманиваю подло людей в норы!";
            link.l1.go = "StepF1_4";
        break;
        case "StepF1_4":
            dialog.text = "Хм, а не ты ли поднимаешь флаги других держав, пытаясь тем самым обмануть жертву и беспрепятственно с ней сблизиться?";
            link.l1 = "Это другое...";
            link.l1.go = "StepF1_5";
        break;
        case "StepF1_5":
            dialog.text = "Это то же самое, "+ GetSexPhrase("приятель","подруга") +"! Обман, убийство, овладение имуществом жертвы. Все сходится, "+ GetSexPhrase("морской брат","морская сестра") +".\nТак что отвечу на твой вопрос в начале нашей беседы - а ничего не происходит сверхординарного, все как шло, так и идет своим чередом.";
            link.l1 = "Гладко стелешь...";
            link.l1.go = "StepF1_6";
        break;
        case "StepF1_6":
            dialog.text = "Хм, может и так... Говори, зачем приш"+ GetSexPhrase("ел","ла") +", морск"+ GetSexPhrase("ой брат","ая сестра") +".";
            link.l1 = "Здорово умеешь запутать, но я тоже не лыком шит"+ GetSexPhrase("","а") +". И вот что я тебе скажу - между нами огромная разница. И заключается она в том, что я даю людям выбор - сдаться или принять смерть. А ты выбора не даешь, и все твои жертвы закопаны там же, в подземельях. Так что, не брат ты мне.";
            link.l1.go = "StepF1_7";
        break;
        case "StepF1_7":
            dialog.text = "Обострять приш"+ GetSexPhrase("ел","ла") +"?";
            link.l1 = "Именно. Хочу закончить начатое и избавить Карибское море от мрази.";
            link.l1.go = "StepF1_8";
        break;
        case "StepF1_8":
            dialog.text = "Что же, это к лучшему, ты тоже мне порядком надоел"+ GetSexPhrase("","а") +". Давай приступим, сеньор"+ GetSexPhrase("","ита") +"!";
            link.l1 = "Пора, пожалуй...";
            link.l1.go = "StepF1_9";
        break;
        case "StepF1_9":
			LAi_LocationFightDisable(loadedLocation, false);
			CloseQuestHeader("BerglarsGang");
			LAi_group_Delete("EnemyFight");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
   			npchar.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
