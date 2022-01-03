
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

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
					dialog.text = LinkRandPhrase("Ха, нов"+ GetSexPhrase("ый","ая") +" граждан"+ GetSexPhrase("ин","ка") +"! Полагаю, что шторм не помешает нам познакомиться. Я - " + GetFullName(npchar) + ", состою в здешней милиции.",
						"Так вы и есть единственн"+ GetSexPhrase("ый","ая") +" спасш"+ GetSexPhrase("ийся","аяся") +" с последнего корабля в этом шторме? Ну что же, добро пожаловать в Город. Меня зовут " + GetFullName(npchar) + ", я работаю в милиции.",
						"Вижу нов"+ GetSexPhrase("ого","ую") +" граждан"+ GetSexPhrase("ина","ку") +" Города! Добро пожаловать, как говорится, а на шторм уже можете не обращать внимания. Мое имя - " + GetFullName(npchar) + ", я числюсь в местной милиции.");
					link.l1 = RandPhraseSimple("Привет, я - " + GetFullName(pchar) + ". Что за милиция?", "Приветствую. Меня зовут " + GetFullName(pchar) + ". А что это за милиция?");
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ха, нов"+ GetSexPhrase("ый","ая") +" граждан"+ GetSexPhrase("ин","ка") +"! Ну, здравствуй и давай знакомится. Я - " + GetFullName(npchar) + ", состою в здешней милиции.",
						"Так вы и есть единственн"+ GetSexPhrase("ый","ая") +" спасш"+ GetSexPhrase("ийся","аяся") +" с последнего корабля? Ну что же, добро пожаловать в Город. Меня зовут " + GetFullName(npchar) + ", я работаю в милиции.",
						"Вижу нового гражданина Города! Добро пожаловать, как говорится. Мое имя - " + GetFullName(npchar) + ", я числюсь в местной милиции.");
					link.l1 = RandPhraseSimple("Привет, я - " + GetFullName(pchar) + " Что за милиция?", "Приветствую. Меня зовут " + GetFullName(pchar) + " А что это за милиция?");
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Где-то преступление?", "В чем дело, в Городе беспорядки?", "Что-то случилось?");
				link.l1 = RandPhraseSimple("Слушай, я ищу одного человека. Не знаешь, где он сейчас?", "Мне нужно найти одного человека. Ты не видел его где-нибудь поблизости?");
				link.l1.go = "SeekCitizen";
				link.l2 = RandPhraseSimple("Хочу задать тебе вопрос.", "У меня есть к тебе вопрос.");
				link.l2.go = "int_quests";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.additional.powder") && sti(pchar.questTemp.LSC.additional.powder))
				{
					link.l8 = "Слушай, мне очень нужны порох и оружие. Адмирал не хочет мне ничего давать, а мне очень нужно...";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && !CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = "Приветствую, дружище. Ну что же, время пришло. Мы уходим.";
					link.l8.go = "SeekCrew";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = "Ну, как дела?";
					link.l8.go = "SeekCrew2";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = "Ну что, дружище, похоже, что время пришло.";
					link.l8.go = "SeekCrew3";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && !CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = "Приятель, мы как-то говорили о том, что ты хочешь уйти со мной с этого проклятого острова.";
					link.l8.go = "SeekCrew4";
				}
				link.l10 = "Нет, все нормально.";
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = LinkRandPhrase("Милиция обеспечивает порядок и соблюдение Закона гражданами Города.",
				"Милиция смотрит тут за всем происходящим. В общем, это власть в Городе...",
				"В обычных городах есть губернатор с гарнизоном солдат. Здесь губернатор - наш адмирал, а гарнизон - это мы, милиционеры.")
			link.l1 = RandPhraseSimple("Понятно...", "Теперь ясно, спасибо за разъяснения.");
			link.l1.go = "exit";
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
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием наизготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = "А кого ты ищешь?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "Я не понимаю, о ком ты говоришь. Мне нужно знать имя и фамилию этого человека.";
				Link.l1 = "Понятно. Давай я еще попробую назвать.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Спасибо, я лучше сам"+ GetSexPhrase("","а") +" поищу.";
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "Так это же я!";
					link.l1 = "Надо же, точно на тебя выш"+ GetSexPhrase("ел","ла") +"!";
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", ты о нем говоришь?";
					Link.l1 = "Да-да, точно, это он.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о нем. Давай еще раз назову.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", ты о ней говоришь?";
					Link.l1 = "Ага, именно о ней.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о ней. Слушай, давай я еще раз попробую назвать.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "Знаешь, не хочу я больше ни о ком спрашивать. До свидания.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Тогда назови еще раз имя и фамилию.";
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
					dialog.text = LinkRandPhrase("Не знаю, давно его не видел.", "Черт его знает, где он...", "Не видел его уже прилично, так что не ведаю.");
					link.l1 = RandPhraseSimple("Понятно.", "Жаль...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Не видел ее уже довольно давно, сожалею.", "Понятия не имею, где она сейчас.", "Хм, я не знаю, где она может сейчас быть.");
					link.l1 = RandPhraseSimple("Ясно.", "Жаль...");
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
							dialog.text = LinkRandPhrase("Он здесь, на этом корабле. Ищи внимательней.", "Ха, так он здесь, на этом корабле!", "Он на этом корабле, странно, что ты еще не увидел"+ GetSexPhrase("","а") +" его.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищи его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Так он здесь, " + npchar.quest.seekIdx.where + ". Смотри внимательней.", "Так ведь он здесь, среди нас!", "Куда ты смотришь? Он же здесь ошивается.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищи его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо тебе, приятель.", "Спасибо тебе!");
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
							dialog.text = LinkRandPhrase("Она здесь, на этом корабле. Ищи внимательней.", "Ха, так она здесь, на этом корабле!", "Она на этом корабле, странно, что ты еще не увидел"+ GetSexPhrase("","а") +" ее.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил ее " + npchar.quest.seekIdx.where + ". Мы даже поговорили.", "Насколько я знаю, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Так она здесь, " + npchar.quest.seekIdx.where + ". Смотри внимательней.", "Так ведь она здесь, среди нас!", "Куда ты смотришь? Она же где-то здесь ходит.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил ее " + npchar.quest.seekIdx.where + ". Мы даже поговорили с ней.", "Насколько я знаю, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо тебе, приятель.", "Спасибо тебе!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = LinkRandPhrase("Внимательно тебя слушаю, "+ GetSexPhrase("дружище","гражданка") +".", "Говори, я слушаю.", "Внимательно слушаю.");
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = LinkRandPhrase("Послушай, что это за остров?", "Что это за остров странный?", "Слушай, дружище, а что это за остров такой?");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = LinkRandPhrase("А ты не пробовал вырваться отсюда?", "Может, есть возможность свалить с этого места?", "Не пробовал уплыть отсюда?");
				link.l2.go = "ansewer_2";
			}
			link.l10 = RandPhraseSimple("Нет вопросов. Извини, дружище...", "Что-то из головы вылетело, забыл"+ GetSexPhrase("","а") +"...");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = LinkRandPhrase("Этот остров называется Городом Потерянных Кораблей. Ты теперь гражданин этого Города.",
				"Очень необычное место, не правда ли? Остров называется Городом Потерянных Кораблей. Теперь и ты будешь жить с нами.",
				"Это Город Потерянных Кораблей. Весь остров состоит из кораблей, которые сюда занесла нелегкая...");
			link.l1 = RandPhraseSimple("Понятно.", "Ясно...");
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = LinkRandPhrase("А зачем? Нас и здесь неплохо кормят...",
				"Это запрещено Законом. А вообще-то, лично я и не хочу, меня здесь все устраивает.",
				"Ты знаешь, здесь есть все, что я хотел получить от жизни. Зачем мне искать лучшей доли?");
			link.l1 = RandPhraseSimple("Понятно.", "Ясно...");
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//диалог перед боем на Веласко
		case "OffNarval":
			dialog.text = LinkRandPhrase("Мы готовы к атаке, веди.", "Заждались тебя уже... Ну, давай, не медли.", "Отправим этих 'нарвалов' к чертям собачьим!");
			link.l1 = "Хорошо!";
			link.l1.go = "exit";
		break;
		//диалог после боем на Веласко
		case "AffterFightN":
			dialog.text = LinkRandPhrase("Мы справились!", "Хе-хе, адмирал будет доволен...", "Все, клана 'Нарвал' более не существует!");
			link.l1 = "Более я вас не задерживаю.";
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("А зачем тебе порох и оружие? Здесь это - мертвый груз.",
				"Все решили.",
				"Я все сделаю.",
                "Ох, и приставуч"+ GetSexPhrase("ий","ая") +" же ты.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Здесь - да. Но есть места, где эти товары необходимы.",
				"Отлично!",
                "А-а, ну да.",
				"Ага.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Например, в плавании?";
			link.l1 = "Хм... ну, предположим.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Понятно... Знаешь, я помогу тебе, если ты возьмешь меня с собой.";
			link.l1 = "Соглас"+ GetSexPhrase("ен","на") +", тем более, что хорошая компания мне просто необходима.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Хорошо. Я могу втихаря вытащить со склада многое... Сколько тебе нужно оружия и пороха, и куда это доставить?";
			link.l1 = "Мне нужно 10 центнеров пороха и 50 единиц оружия. Доставить это нужно на барк 'Сан Габриэль'.";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "Хорошо, я все сделаю. Не забудь забрать меня потом!";
			link.l1 = "Ни за что, это в моих интересах, дружище. Бывай.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_WEAPON, 50);
			AddCharacterGoods(pchar, GOOD_POWDER, 200);
			AddQuestRecord("ISS_MainLine", "58");
			pchar.questTemp.LSC.additional.powder = false;
		break;
		//поиски команды на корвет
		case "SeekCrew":
			dialog.text = "Отлично! Когда?";
			link.l1 = "Я сейчас как раз набираю команду на корабль, так что добро пожаловать. Отправляйся на 'Сан Габриэль'. Хенрик Ведекер, который там находится, переправит тебя на мой фрегат.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Да, это было бы неплохо. Но ты знаешь, я пока подожду здесь.";
			link.l1 = "Зачем?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Адмирал тобой очень недоволен. Полагаю, что он готовится прикончить тебя. Поэтому я подожду здесь, посмотрю, что будет дальше. Если у тебя наступят проблемы с Чадом - я смогу прикрыть твою спину.";
			link.l1 = "Да, это было бы неплохо. Знаешь, дружище, когда все это закончиться, я хочу взять тебя офицером к себе на корвет. Ежемесячное жалование гарантирую.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Интересное предложение. Пожалуй, соглашусь. Ну, а пока нужно постараться сделать так, чтобы 'все это' закончилось благополучно для нас.";
			link.l1 = "Это верно! Ну что же, ожидай здесь.";
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.LSC.crew.ment_6 = true;
			npchar.quest.LSCofficer = true;
			AddQuestRecord("ISS_MainLine", "61");
		break;

		case "SeekCrew2":
			dialog.text = "Пока все в порядке, но держи ухо востро! Если начнется заварушка, то я приду на помощь.";
			link.l1 = "Отлично! Спасибо тебе.";
			link.l1.go = "exit";
		break;

		case "SeekCrew3":
			dialog.text = "Я готов. Заходи в резиденцию, я зайду туда чуть позже.";
			link.l1 = "Договорились!";
			link.l1.go = "exit";
		break;

		case "SeekCrew4":
			dialog.text = "Да, это так. И что скажешь?";
			link.l1 = "Если ты поможешь мне сейчас, то я готов"+ GetSexPhrase("","а") +" взять тебя офицером с достойным ежемесячным окладом. Мы уходим, и твоя помощь мне нужна прямо сейчас.";
			link.l1.go = "SeekCrew4_1";
		break;
		case "SeekCrew4_1":
			dialog.text = "Я согласен. Чем я могу помочь тебе?";
			link.l1 = "Судя по всему, сейчас будет серьезная заварушка в резиденции. Если ты выступишь на моей стороне, то, считай, по рукам.";
			link.l1.go = "SeekCrew4_2";
		break;
		case "SeekCrew4_2":
			dialog.text = "Хм, адмирал - серьезный боец. Но я готов рискнуть!";
			link.l1 = "Отлично! Тогда договоримся так: жди здесь, но если начнется драка, то вступай в бой немедленно.";
			link.l1.go = "SeekCrew4_3";
		break;
		case "SeekCrew4_3":
			dialog.text = "Хорошо. Я не подведу, капитан.";
			link.l1 = "Ну вот и славно...";
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ref ment = CharacterFromID("Ment_5");
			ment.model = "officer_8";
			FaceMaker(ment);
			npchar.quest.LSCofficer = true;
			AddQuestRecord("ISS_MainLine", "68");
		break;
		//финальный разговор мента_6 перед посадкой на корвет
		case "MentOffIsLife":
			dialog.text = "Ну что, похоже, мы отбились.";
			link.l1 = "Да... Спасибо тебе, дружище, ты сдержал слово. Я у тебя в долгу.";
			link.l1.go = "MentOffIsLife_1";
		break;
		case "MentOffIsLife_1":
			Npchar.quest.OfficerPrice = (rand(4)+1)*1000;
			dialog.text = "Без проблем. Я готов идти к тебе в команду офицером. Что ты мне предложишь?";
			link.l1 = "Дружище, сейчас не время для торговли. Назначь себе жалование сам, потом разберемся...";
			link.l1.go = "MentOffIsLife_2";
		break;
		case "MentOffIsLife_2":
			dialog.text = "Хорошо, как скажешь...";
			link.l1 = "Слушай, адмирал арестовал Механика. Ты не в курсе, где он?";
			link.l1.go = "MentOffIsLife_3";
		break;
		case "MentOffIsLife_3":
			dialog.text = "В тюрьме, конечно. Его отправили на 'Тартарус'.";
			link.l1 = "Спасибо, ты мне здорово помог. Сейчас отправляйся на 'Сан Габриэль', там есть возможность попасть на мой фрегат. Остальные граждане Города, пожелавшие уйти со мной, уже там. Ждите нас с Ведекером.";
			link.l1.go = "MentOffIsLife_4";
		break;
		case "MentOffIsLife_4":
			dialog.text = "Хорошо, капитан. Я только осмотрюсь здесь немного...";
			link.l1 = "Хорошо, но не опаздывай на корабль.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DialogExit();
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
			AddQuestRecord("ISS_MainLine", "66");
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "Gr_questOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;

		break;
	}
	NextDiag.PrevNode = NodeName;
}
