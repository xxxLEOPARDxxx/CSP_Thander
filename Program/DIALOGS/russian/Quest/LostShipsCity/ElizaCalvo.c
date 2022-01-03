#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = "Этот шторм был очень сильным, сеньор"+ GetSexPhrase("","ита") +", вам очень повезло, что вы смогли выбраться к нам... Меня зовут " + GetFullName(npchar) + ", в этом доме я хозяйка.";
					else dialog.text = "Этот шторм был очень сильным, сеньор"+ GetSexPhrase("","ита") +", вам очень повезло, что вы смогли выбраться к нам... Меня зовут " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " к вашим услугам, сеньора. Скажите, а как долго продолжался этот шторм?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Здравствуйте! Я так понимаю, что это именно вы спаслись последн"+ GetSexPhrase("им","ей") +".";
					link.l1 = GetFullName(pchar) + " к вашим услугам, сеньора. Да, это я.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = "Что вам нужно у меня в доме, сеньор"+ GetSexPhrase("","ита") +"?";
				else dialog.text = "Я вас слушаю, сеньор"+ GetSexPhrase("","ита") +".";
				link.l1 = "Вы знаете, я ищу одного человека. Не поможете мне?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Я хотел"+ GetSexPhrase("","а") +" задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете, сеньора?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.bombs"))
				{
					link.l8 = "Вы знаете, я ищу некоторые товары. Не могли бы вы мне помочь?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.bombs") && sti(npchar.quest.bombs))
				{
					link.l8 = "Я по поводу бомб.";
					link.l8.go = "TakeBombs";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Знаете, я набираю команду, чтобы уйти отсюда. Я предлагаю вам идти со мной на Большую землю.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = "Что-то около недели, точно не скажу. Знаете, когда такое происходит вокруг, теряешь счет времени.";
			link.l1 = "Да, понимаю.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "Кстати, все попавшие в Город должны отметиться у адмирала Чада Каппера и получить гражданство. Если вы еще не сделали это, то советую поторопиться.";
			link.l1 = "А где он находится, этот Чад Каппер?";
			link.l1.go = "FS_3";
		break;
		case "FS_3":
			dialog.text = "В резиденции города, на варшипе 'Сан Августин'.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "А меня зовут " + GetFullName(npchar) + ". Я хозяйка этой каюты, или этого дома, как вам будет угодно называть это пристанище.";
			link.l1 = "Наверно, 'дом' будет правильней.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Я тоже так думаю. Ну что же, добро пожаловать в мой дом.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он нарушил Закон!", "Милиция! Грабят!!! Держи его, он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
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
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","тут всякие") +" ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		//ищем человека
		case "SeekCitizen":
			dialog.text = "С удовольствием вам помогу, если смогу, конечно. Так кого вы ищете?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "Простите, но я совершенно не понимаю, о ком вы говорите. Чтобы вам помочь, мне нужны имя и фамилия.";
				Link.l1 = "Хм. Давайте я попробую еще раз их назвать.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Благодарю вас, но лучше я сам"+ GetSexPhrase("","а") +" поищу.";
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "Хм, простите, но вы ищете меня. Это я.";
					link.l1 = "Надо же!";
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", вы его имеете в виду?";
					Link.l1 = "Именно его.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, я имел в виду другого.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", вы о ней говорили?";
					Link.l1 = "Точно, именно о ней.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о ней. Может, я еще раз попробую назвать?";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "Вы знаете, я вам очень благодар"+ GetSexPhrase("ен","на") +", но я не хочу больше ни о ком спрашивать.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Тогда вам придется еще раз назвать имя и фамилию.";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = LinkRandPhrase("Понятия не имею, где он.", "Ни малейшего представления не имею, где он сейчас.", "Я не видела его уже довольно давно. Так что не могу знать.");
					link.l1 = RandPhraseSimple("Понятно.", "Ясно... Что же, спасибо.");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Понятия не имею, где она.", "Ни малейшего представления не имею, где он сейчас.", "Я не видела ее уже довольно давно. Так что не могу знать.");
					link.l1 = RandPhraseSimple("Понятно.", "Ясно... Что же, спасибо.");
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = LinkRandPhrase("Он здесь, на этом корабле. Смотрите внимательней, пожалуйста.", "Хм, так ведь он сейчас на этом корабле...", "Он на этом корабле, странно, что вы еще не встретились.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видела его совсем недавно " + npchar.quest.seekIdx.where + ".", "Вы знаете, я недавно встретила его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько мне известно, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Простите, но он находится прямо здесь, " + npchar.quest.seekIdx.where + ". Вам нужно быть внимательным.", "Хм, он ведь здесь, среди нас!", "Если бы вы посмотрели вокруг более внимательно, то наверняка уже увидели его...");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видела его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретила его " + npchar.quest.seekIdx.where + ". Так что вы сможете увидеть его там.", "Насколько мне известно, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам!", "Спасибо вам огромное.");
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = LinkRandPhrase("Она здесь, на этом корабле. Смотрите внимательней, пожалуйста.", "Хм, так ведь она сейчас на этом корабле...", "Она на этом корабле, странно, что вы еще не встретились.");
						}
						else
						{
								dialog.text = LinkRandPhrase("Я видела ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Вы знаете, я недавно встретила ее " + npchar.quest.seekIdx.where + ". Так что ищите ее там.", "Насколько мне известно, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Простите, но она находится прямо здесь, " + npchar.quest.seekIdx.where + ". Вам нужно быть внимательным.", "Хм, она ведь здесь, среди нас!", "Если бы вы посмотрели вокруг более внимательно, то наверняка уже увидели ее...");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видела ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретила ее " + npchar.quest.seekIdx.where + ". Так что вы сможете увидеть ее там.", "Насколько мне известно, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам!", "Спасибо вам огромное.");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Внимательно вас слушаю.";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Послушайте, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Штормы часто здесь бывают?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Скажите, давно вы уже здесь живете?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Этот остров называется Городом Потерянных кораблей. И название, скажу я вам, совершенно точное по сути.";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Довольно часто. Очень страшно, конечно, но мы привыкли...";
			link.l1 = "Ну да, деваться-то некуда!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Довольно давно, около трех лет. А что?";
			link.l1 = "Да так, ничего. А покойный Хилл Брюннер уже был здесь, когда вы сюда попали?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Да, был, конечно. Он же был старожилом Города. Жаль, что он погиб...";
			link.l1 = "Да, жаль...";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Если смогу, то, конечно, помогу.",
				"Вы уже спрашивали об этом.",
				"Уже спрашивали...",
                "Вы уже спрашивали меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Я ищу ядра, бомбы, картечь, книппели, провиант, лекарства...",
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Бомбы... Кажется, у меня что-то такое есть... Да, точно! А сколько вам надо?";
			link.l1 = "100 штук будет вполне достаточно.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Столько найдется. Только вы должны сделать кое-что и для меня.";
			link.l1 = "Всегда к вашим услугам.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Принесите мне 10 кистей винограда, три бутылки вина и лютню. У меня хорошее настроение, я буду петь и учиться играть.";
			link.l1 = "А учить вас есть кому?";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = ""+ GetSexPhrase("На себя намекаете? Не стоит, место занято...","Есть, не переживайте.") +"";
			link.l1 = ""+ GetSexPhrase("Ни в коей мере, просто так спросил. ","Да-а...") +"Я думаю, что если съесть столько винограда и выпить столько вина, то вряд ли вы играть научитесь.";
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = "А вот это уже не ваше дело. Несите то, что я вам сказала, и все дела.";
			link.l1 = "Хорошо-хорошо, как скажете.";
			link.l1.go = "exit";
			npchar.quest.bombs = true;
			AddQuestRecord("ISS_MainLine", "55");
		break;
		//проверка на соль
		case "TakeBombs":
			dialog.text = "Вы принесли то, что я заказывала?";
            if (CheckCharacterItem(pchar, "Mineral2") && CheckCharacterItem(pchar, "potionwine") && sti(pchar.items.potionwine) >= 3 && CheckCharacterItem(pchar, "potion5") && sti(pchar.items.potion5) >= 10)
            {
				link.l1 = "Да, все у меня. Извольте получить.";
				link.l1.go = "TakeBombs_yes";
			}
			else
			{
				link.l1 = "Нет еще, не могу найти. Может, вы расхотели учиться играть?";
				link.l1.go = "TakeBombs_no";
			}
		break;
		case "TakeBombs_no":
			dialog.text = "Нет...";
			link.l1 = "Понятно.";
			link.l1.go = "exit";
		break;
		case "TakeBombs_yes":
			dialog.text = "Хорошо. Можете забирать свои бомбы.";
			link.l1 = "Спасибо. А можно как-нибудь на 'Сан Габриэль' доставить? Очень вас прошу.";
			link.l1.go = "TakeBombs_1";
			TakeNItems(pchar, "Mineral2", -1);
			TakeNItems(pchar, "potionwine", -3);
			TakeNItems(pchar, "potion5", -10);
		break;
		case "TakeBombs_1":
			dialog.text = "На 'Сан Габриэль'... Ну хорошо, красав"+ GetSexPhrase("чик","ица") +". За ваше старание я это организую. Попрошу своего избранника, он все сделает.";
			link.l1 = "Великолепно! Огромное спасибо вам и избраннику. Ему очень повезло...";
			link.l1.go = "TakeBombs_2";
		break;
		case "TakeBombs_2":
			dialog.text = "Спасибо..."+ GetSexPhrase(" Да вы льстец, как я погляжу!","") +"";
			link.l1 = ""+ GetSexPhrase("Временами... ","") +"Ну, всего хорошего.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddQuestRecord("ISS_MainLine", "56");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			npchar.quest.Bombs = false;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Очень откровенно! И вы вот так запросто нарушаете Закон?";
			link.l1 ="У меня нет выхода, я спасаю свою жизнь. Могу спасти и вашу.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Хм, объяснитесь.";
			link.l1 = "Дело в том, что грядущий шторм с высокой степенью вероятности уничтожит город. Это вычислил Механик.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Понятно... Ну что же, я согласна идти к вам на корабль. Что я должна сделать?";
			link.l1 = "Отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль. И не медлите!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо, скоро буду на 'Сан Габриэле'.";
			link.l1 = "Прошу вас, быстрее...";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
