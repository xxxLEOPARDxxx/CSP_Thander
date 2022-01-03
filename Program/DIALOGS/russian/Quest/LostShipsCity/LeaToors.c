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
					if (npchar.location == "PlutoStoreSmall") dialog.text = "Приветствую вас, "+ GetSexPhrase("минхер","госпожа") +", у себя дома, вы можете переждать у меня этот шторм. Меня зовут " + GetFullName(npchar) + ".";
					else dialog.text = "Приветствую вас, минхер. Меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "А я - капитан " + GetFullName(pchar) + ". Переждать шторм, говорите?";
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "PlutoStoreSmall") dialog.text = "Приветствую вас, "+ GetSexPhrase("минхер","госпожа") +", у себя дома. Меня зовут " + GetFullName(npchar) + ".";
					else dialog.text = "Приветствую вас, "+ GetSexPhrase("минхер","госпожа") +". Меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "А я - капитан " + GetFullName(pchar) + ". Справедливости ради надо заметить, что бывш"+ GetSexPhrase("ий","ая") +" капитан...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Я могу вам чем-нибудь помочь, "+ GetSexPhrase("минхер","госпожа") +"?";
				link.l1 = "Вы знаете, я ищу одного человека. Не поможете мне?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Я хотел"+ GetSexPhrase("","а") +" задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//квест со скелетом Декстера
				if (CheckActiveQuest("LSC_findDekster") && !CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
				{
					link.l4 = "Леа, я слышал"+ GetSexPhrase("","а") +", что вы знаете что-то о неком Лейтоне Декстере...";
					link.l4.go = "LostDecster";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.grapes"))
				{
					link.l8 = "Послушайте, я ищу некоторые товары.";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.grapes") && sti(npchar.quest.grapes))
				{
					link.l8 = "Я по поводу картечи.";
					link.l8.go = "TakeGrapes";
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
			dialog.text = "Да, вы можете находиться здесь сколь угодно. Закон гласит, что каждый хозяин дома в Городе должен давать приют нуждающимся во время буйства стихии. Сейчас как раз такое время.";
			link.l1 = "Да, это заметно... Ну что же, огромное вам спасибо.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Я понимаю, что вам нелегко потерять все. Но вы же спаслись!";
			link.l1 = "Да-да, конечно...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Послушайте, вам не стоит отчаиваться. Я советую вам быстрей включаться в нашу жизнь, здесь не так уж и плохо, как может показаться на первый взгляд.";
			link.l1 = "Спасибо вам за поддержку.";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи "+ GetSexPhrase("его","ее") +", он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
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
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием на изготовку. Это меня пугает...");
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
					Link.l2 = "Нет, я имел"+ GetSexPhrase("","а") +" в виду другого.";
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
					dialog.text = LinkRandPhrase("Понятия не имею, где он.", "Ни малейшего представления не имею, где он сейчас.", "Я не видела его уже довольно долго. Так что не могу знать.");
					link.l1 = RandPhraseSimple("Понятно.", "Ясно... Что же, спасибо.");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Понятия не имею, где она.", "Ни малейшего представления не имею, где он сейчас.", "Я не видела ее уже довольно долго. Так что не могу знать.");
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
							dialog.text = LinkRandPhrase("Простите, но он находится прямо здесь, " + npchar.quest.seekIdx.where + ". Вам нужно быть внимательн"+ GetSexPhrase("ым","ой") +".", "Хм, он ведь здесь, среди нас!", "Если бы вы посмотрели вокруг более внимательно, то наверняка уже увидели его...");
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
							dialog.text = LinkRandPhrase("Простите, но она находится прямо здесь, " + npchar.quest.seekIdx.where + ". Вам нужно быть внимательн"+ GetSexPhrase("ым","ой") +".", "Хм, она ведь здесь, среди нас!", "Если бы вы посмотрели вокруг более внимательно, то наверняка уже увидели ее...");
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
			if (!CheckAttribute(NextDiag, NodeName+".l1") && npchar.location == "PlutoStoreSmall")
			{
				link.l1 = "И каково вам быть хозяйкой этого дома?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = "Скажите, а вы давно здесь живете?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Вполне нормально, знаете ли. У меня все под контролем, мой дом - моя крепость.";
			link.l1 = "Это здорово.";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "И не вздумайте что-то у меня прихватить, я строго за этим слежу!";
			link.l1 = "Ни в коем разе!";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Нет, около года всего лишь.";
			link.l1 = "Понятно... Скажите, а вы не знаете кого-нибудь из местных старожилов, кто уже очень долго здесь живет?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Знала. Это Хилл Брюннер.";
			link.l1 = "Хе, это мне известно. Только вот незадача - он мертв...";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "Да, ужасная история! И совершенно непонятная, к тому же.";
			link.l1 = "Это верно... Ну ладно, всего вам наилучшего, Леа.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("И чем я могу вам помочь?",
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
			dialog.text = "У меня на корабле есть картечь. Сколько вам нужно?";
			link.l1 = "5 центнеров будет вполне достаточно.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Хорошо, я отдам ее вам. Только сначала принесите мне 10 мешочков соли.";
			link.l1 = "Чего?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Я хочу, чтобы вы принесли мне 10 мешочков соли. Что тут непонятного? И тогда я отдам вам картечь.";
			link.l1 = "Хорошо, будет вам ваша соль.";
			link.l1.go = "exit";
			npchar.quest.grapes = true;
			AddQuestRecord("ISS_MainLine", "53");
		break;
		//проверка на соль
		case "TakeGrapes":
			dialog.text = "Вы принесли мне десять мешочков?";
            if (CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) >= 10)
            {
				link.l1 = "Да, они у меня, и я готов"+ GetSexPhrase("","а") +" вам их вручить.";
				link.l1.go = "TakeGrapes_yes";
			}
			else
			{
				link.l1 = "Нет еще, не могу найти. Может, как-нибудь по-другому договоримся?";
				link.l1.go = "TakeGrapes_no";
			}
		break;
		case "TakeGrapes_no":
			dialog.text = "И не мечтайте!";
			link.l1 = "Хм, ясно...";
			link.l1.go = "exit";
		break;
		case "TakeGrapes_yes":
			dialog.text = "Превосходно! Ну что же, вы можете забирать свою картечь.";
			link.l1 = "Спасибо. Эх, как бы доставить ее на 'Сан Габриэль'?..";
			link.l1.go = "TakeGrapes_1";
			TakeNItems(pchar, "Mineral10", -10);
		break;
		case "TakeGrapes_1":
			dialog.text = "Гм... Ну что же, я заставила вас побегать, и теперь помогу вам. Перевозку на 'Сан Габриэль' я вам организую сама, благо знакомых мужчин у меня много...";
			link.l1 = "Отлично! Я даже не знаю, как вас благодарить.";
			link.l1.go = "TakeGrapes_2";
		break;
		case "TakeGrapes_2":
			dialog.text = "Да ну что вы, не стоит. Все в порядке.";
			link.l1 = "Всего хорошего.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddQuestRecord("ISS_MainLine", "54");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "ла"));
			npchar.quest.grapes = false;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Вот это да!.. Вы не шутите?";
			link.l1 = "Ни в коей мере.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Вы знаете, мне здесь все порядком надоело. Так что, если вы говорите правду, то я согласна.";
			link.l1 = "Вы сделали правильный выбор, могу вас уверить.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Очень на это надеюсь. Так, что мне теперь делать?";
			link.l1 = "Отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль. И не медлите!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо, скоро буду на 'Сан Габриэле'.";
			link.l1 = "Прошу вас, быстрее...";
			link.l1.go = "SeekCrew_all";
		break;
		//квест со скелетом Лейтона Декстера
		case "LostDecster":
			dialog.text = "Хм, а почему вы спрашиваете?";
			link.l1 = "Ну, как сказать?.. Мне просто интересно стало.";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "Позвольте заметить, что интересы ваши распространяются в оч-чень опасном направлении...";
			link.l1 = "Как это понимать?";
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = "Если вы хотите вступить в противоборство с адмиралом, то, боюсь, вас ждет судьба несчастного Лейтона.";
			link.l1 = "Так, кто он такой? И что с ним случилось вообще?";
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = "Вы уверены, что хотите это знать?";
			link.l1 = "Абсолютно.";
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = "Ну хорошо, я расскажу\nВы, наверно, уже знаете, что Декстер был пиратом, как и Чад Каппер, собственно. Сначала два корсара сдружились. Чад, когда стал адмиралом, тут же назначил Лейтона начальником 'Тартаруса'. Надеюсь, вы знаете, что это наша тюрьма?";
			link.l1 = "Хм... Да, конечно, это мне известно.";
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = "Но потом меж ними пробежала черная кошка. Как-то я ходила навещать Максима Тейлора, который очередной раз угодил за решетку. А дело было к вечеру, и, в общем, я там задержалась до полуночи\nИ вот, когда я вышла на палубу, то услышала два голоса - Чада и Лейтона. Они спорили о деньгах...";
			link.l1 = "Ага... И что было дальше?";
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = "Дальше спор прервался хриплым булькающим стоном. Я не дура, и поспешила тихо убраться с 'Тартаруса'. Больше я ничего не знаю, но с тех пор никто не видел Лейтона Декстера.";
			link.l1 = "Вы думаете, что Чад его прикончил?";
			link.l1.go = "LostDecster_7";
		break;
		case "LostDecster_7":
			dialog.text = "Не знаю, но очень на то похоже.";
			link.l1 = "Понятно... Значит, все это случилось на 'Тартарусе'?";
			link.l1.go = "LostDecster_8";
		break;
		case "LostDecster_8":
			dialog.text = "Судя по всему.";
			link.l1 = "Ясно. Спасибо вам за откровенность.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "toAdmiral";
			AddQuestRecord("LSC_findDekster", "3");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
