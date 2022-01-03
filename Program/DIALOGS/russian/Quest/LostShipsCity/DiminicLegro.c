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
					dialog.text = "Мои поздравления новоприбывше"+ GetSexPhrase("му","й") +", сейчас как раз время. Я " + GetFullName(npchar) + ", меня еще зовут здесь Счастливым.";
					link.l1 = "Ну, здравствуй, " + npchar.name + ". Мое имя " + GetFullName(pchar) + ", будем знакомы. А что значит 'вовремя'?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Мои поздравления новоприбывше"+ GetSexPhrase("му","й") +". Я " + GetFullName(npchar) + ", меня еще зовут здесь Счастливым.";
					link.l1 = "Ну, здравствуй, " + npchar.name + ". Мое имя " + GetFullName(pchar) + ", будем знакомы.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест отнести бутылочку вина тюремщику. дача квеста
				if (!CheckActiveQuest("TakeVineToPrisoner") && !CheckAttribute(pchar, "questTemp.LSC.LegroHelp"))
				{
					dialog.text = "Эй, "+ GetSexPhrase("приятель","подруга") +", у меня к тебе есть дело.";
					link.l1 = "Выкладывай.";
					link.l1.go = "GiveVineBottle";
					break;
				}
				dialog.text = "Что вы хотели, "+ GetSexPhrase("сэр","мисс") +"?";
				link.l1 = "Слушай, я ищу одного человека. Не знаешь, где он сейчас?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Хочу задать тебе вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//квест доставки вина тюремщику. после разговора с Бойлом
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toFackDominic")
				{
					link.l7 = "Знаешь, передал"+ GetSexPhrase("","а") +" я от тебя бутылку вина Томасу Бойлу.";
					link.l7.go = "FackDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toArmoDominic")
				{
					link.l7 = "Дружище, а не заигрывал ли ты с Армо Дюлин на днях?";
					link.l7.go = "ArmoDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toKeyDominic")
				{
					link.l7 = "Ну что же, я все уладил"+ GetSexPhrase("","а") +" с Томасом Бойлом.";
					link.l7.go = "KeyDominic";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Слушай, я ищу некоторые товары.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Знаешь, я набираю команду, чтобы уйти отсюда. Предлагаю тебе идти со мной.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "Шторм спадает, и все везунчики выползают из воды.";
			link.l1 = "Понятно. Ну, ты тоже в их числе!";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "Это верно, но я - абсолютный везунчик. Дело в том, что мой корабль разбился в самый пик шторма!";
			link.l1 = "Ого, вот это да! Расскажи, пожалуйста.";
			link.l1.go = "FT_3";
		break;
		case "FT_1":
			dialog.text = "Что ж, очень приятно.";
			link.l1 = "А почему тебя называют Счастливым?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Тому причин более чем достаточно. Я спасся после кораблекрушения, как и большинство местных, но мое крушение было особенным...";
			link.l1 = "И что же особенного было в твоем крушении?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Ха, это было просто дьявольское крушение, черт побери! В наш фрегат ударила молния, и мигом начался пожар, после чего огонь как-то очень быстро пробрался в пороховой погреб.\n"+
				"Нет, ты только представь! Корабль за считанные минуты превратился в груду полыхающих обломков, а я даже не обжегся! Более того, я находился неподалеку от трюма в момент начала катастрофы, и в Город явился вовсе не с пустыми руками – при мне были драгоценности, деньги, редкие артефакты...";
			link.l1 = "Адмирал не конфисковал все это?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Адмирал – на редкость сообразительный алчный мерзавец, но я любого жулика сумею обжулить. О предстоящей встрече с Каппером мне сообщили заранее, и я успел принять меры, так сказать. Хотя, на какой ляд мне сдались эти побрякушки здесь - самому непонятно...";
			link.l1 = "Хм... Слушай, а что это за меры ты предпринял? Очень интересно узнать...";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Не скажу, "+ GetSexPhrase("приятель","девушка") +", ты уж извини. Мое счастье - оно только мое, боюсь потерять. Я суеверный.";
			link.l1 = "Да уж, это точно. А чем ты здесь занимаешься?";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Да ничем! Пути назад нет, а потому мне и искать его не хочется. Я просто живу сегодняшним днем... и мне это нравится, черт возьми!";
			link.l1 = "Что ж, это тоже позиция. Спасибо за беседу... Слушай, а может, передумаешь и расскажешь мне о мерах?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Прости, "+ GetSexPhrase("дружище","" + pchar.name + "") +", никак невозможно. Могу только намекнуть, что все надо кое-куда сложить перед встречей с Чадом... Это все.";
			link.l1 = "Понятно... Ну что ж, спасибо и на этом.";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи е"+ GetSexPhrase("го","ее") +", он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
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
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как три мушкетера, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это "+ GetSexPhrase("серьезному мужчине","девушке") +"...");
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
			dialog.text = "А кого вы ищете?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "Я не понимаю, о ком вы говорите. Мне нужно знать имя и фамилию этого человека.";
				Link.l1 = "Понятно. Давайте я еще попробую назвать.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Спасибо, я лучше сам"+ GetSexPhrase("","а") +" поищу.";
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "Так это же я!";
					link.l1 = "Надо же, точно на вас выш"+ GetSexPhrase("ел","ла") +"!";
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", вы о нем говорите?";
					Link.l1 = "Да-да, точно, это он.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о нем. Давайте еще раз назову.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", вы о ней говорите?";
					Link.l1 = "Ага, именно о ней.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о ней. Послушайте, давайте я еще раз попробую назвать.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "Знаете, не хочу я больше ни о ком спрашивать. До свидания.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Тогда назовите еще раз имя и фамилию.";
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
							dialog.text = LinkRandPhrase("Он здесь, на этом корабле. Ищите внимательней.", "Ха, так он здесь, на этом корабле!", "Он на этом корабле, странно, что вы еще не увидели его.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Так он здесь, " + npchar.quest.seekIdx.where + ". Смотрите внимательней.", "Так ведь он здесь, среди нас!", "Куда вы смотрите? Он же здесь ошивается.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам.", "Спасибо вам!");
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
							dialog.text = LinkRandPhrase("Она здесь, на этом корабле. Ищите внимательней.", "Ха, так она здесь, на этом корабле!", "Она на этом корабле, странно, что вы еще не увидели ее.");
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
							dialog.text = LinkRandPhrase("Так она здесь, " + npchar.quest.seekIdx.where + ". Смотрите внимательней.", "Так ведь она здесь, среди нас!", "Куда вы смотрите? Она же где-то здесь ходит.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил ее " + npchar.quest.seekIdx.where + ". Мы даже поговорили с ней.", "Насколько я знаю, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам, "+GetAddress_FormToNPC(NPChar)+".", "Спасибо вам!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Внимательно тебя слушаю, "+ GetSexPhrase("дружище","" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Я так понимаю, что штормы здесь - дело привычное.";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "А здесь можно?..";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Как в городе решаются личные проблемы? Неужели люди здесь настолько законопослушные, что не устраивают драк и не убивают друг друга?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Есть шанс добраться вплавь... куда-нибудь?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = "Слушай, а ты давно здесь обретаешься?";
				link.l5.go = "ansewer_5";
			}
			link.l10 = "Нет вопросов. Извини, приятель...";
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = "Да я бы не сказал. Просто, что ни шторм - так сущий ад! Все скрипит, шатается... Страшновато, в общем.";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = "Можно все то, что не запрещено Законом. Можно... только осторожно.";
			link.l1 = "Я учту.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Всякое бывает, конечно. Чад со своей милицией может кого угодно утихомирить. Просто объявляется, что гражданин сошел с ума - и все дела.";
			link.l1 = "Неплохо... А что, действительно у людей башню сносит?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Бывает...";
			link.l1 = "Ясно. Ну а остальной народ как разбирается друг с другом?";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "Втихаря. Бывает, кое-кто исчезает без следа, грешат на кланы... В общем, не пойман - не вор.";
			link.l1 = "Угу, понятно...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Конечно"+ GetSexPhrase(", приятель","") +"! Прямиком в преисподнюю!";
			link.l1 = "Благодарю.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = "Ну, это как сказать. Для некоторых и год здесь - вечность...";
			link.l1 = "Так ты уже год здесь живешь?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "Нет, больше. Про год я образно выразился.";
			link.l1 = "Понятно. Хилл Брюннер был уже здесь?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "Был. Жаль Хилла, хороший был трактирщик. Как ни зайдешь к нему - у него все есть в ассортименте. Эх, жаль...";
			link.l1 = "Ладно, будь здоров.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Что за товары?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                "Ты уже спрашивал"+ GetSexPhrase("","а") +" меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны ядра, бомбы, книппеля, провиант, лекарства, порох, оружие...",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Ну, ядра можно выпросить у хозяек домов. У них такого добра много бесхозного. Лекарства рекомендую попросить у нашего святого отца. А вот оружие и порох - это дела адмирала...";
			link.l1 = "Как понять?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Ну, он со всех кораблей собирает оружие и порох. Так что все запасы у него.";
			link.l1 = "Понял"+ GetSexPhrase("","а") +", спасибо.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "К-хе.. ошарашил"+ GetSexPhrase("","а") +", однако...";
			link.l1 = "Понимаю. Но принимай решение быстро. Если ты согласен, то нужно прямо сейчас отравляться на мой корабль.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Немедленно?";
			link.l1 = "Да. На Город надвигается шторм, который, скорей всего, уничтожит остров. Нужно торопиться.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Хех, опять мне повезло! Я согласен.";
			link.l1 = "Отлично. Сейчас отправляйся на 'Сан Габриэль', там Механик организует переправу на фрегат.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо. Заскочу только вещички собрать.";
			link.l1 = "Не опаздывай.";
			link.l1.go = "SeekCrew_all";
		break;
		//отнести бутылку вина тюремщику
		case "GiveVineBottle":
			dialog.text = "У меня есть друг, Томас Бойл, тюремщик. Целыми днями сидит на этом чертовом 'Тартарусе', как будто сам за решеткой.\nХочу сделать ему приятное.";
			link.l1 = "Великолепно. Чем я могу помочь?";
			link.l1.go = "GiveVineBottle_1";
		break;
		case "GiveVineBottle_1":
			dialog.text = "Слушай, раздобудь где-нибудь бутылочку вина и отнеси ему от меня. Вот Томас будет удивлен!";
			link.l1 = "Приятель, ты, часом, не сбрендил? Я что, по-твоему, "+ GetSexPhrase("мальчик","девочка") +" на побегушках?";
			link.l1.go = "GiveVineBottle_not";
			link.l2 = "Ладно, сделаю.";
			link.l2.go = "GiveVineBottle_2";
		break;
		case "GiveVineBottle_not":
			dialog.text = "Да не заводись ты так. Не хочешь - не надо...";
			link.l1 = "И впредь не лезь ко мне с такими идиотскими предложениями!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "over";
			CloseQuestHeader("TakeVineToPrisoner");
		break;
		case "GiveVineBottle_2":
			dialog.text = "Ну, спасибо тебе, "+ GetSexPhrase("дружище","" + pchar.name + "") +". Томас-то как обрадуется!..";
			link.l1 = "Надеюсь.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toTomasBoil";
			AddQuestRecord("TakeVineToPrisoner", "1");
		break;

		case "FackDominic":
			dialog.text = "Отлично! Представляю, как он был рад...";
			link.l1 = "Вину он был рад, а вот тебе просил передать, что отрежет на ходу уши. Тебе отрежет.";
			link.l1.go = "FackDominic_1";
		break;
		case "FackDominic_1":
			dialog.text = "Мне? За что?!!";
			link.l1 = "Понятия не имею. Но он очень зол на тебя.";
			link.l1.go = "FackDominic_2";
		break;
		case "FackDominic_2":
			dialog.text = "Вот это да!\nСлушай, сходи к нему еще раз, прошу тебя. Узнай, что случилось-то!";
			link.l1 = "Сам сходи и выясни.";
			link.l1.go = "FackDominic_3";
		break;
		case "FackDominic_3":
			dialog.text = "Черт, я боюсь. Думаю, он сначала мне накостыляет, а потом разбираться будет. Сходи, спроси, в чем дело, очень тебя прошу!";
			link.l1 = "Ладно, так уж и быть, спрошу.";
			link.l1.go = "FackDominic_4";
			link.l2 = "Черта с два! Я тебе что, "+ GetSexPhrase("мальчик","девочка") +" на побегушках?";
			link.l2.go = "GiveVineBottle_not";
		break;
		case "FackDominic_4":
			dialog.text = "Спасибо тебе, "+ GetSexPhrase("дружище","" + pchar.name + "") +"! Я клянусь, что совершенно не догадываюсь, в чем тут дело.";
			link.l1 = "Я верю тебе.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toSecondToPrison";
			AddQuestRecord("TakeVineToPrisoner", "3");
		break;

		case "ArmoDominic":
			dialog.text = "Ну, разговаривал я с ней давеча. Ни о каком флирте и речи быть не может! Как будто я не знаю, чья она барышня.";
			link.l1 = "А чья она барышня?";
			link.l1.go = "ArmoDominic_1";
		break;
		case "ArmoDominic_1":
			dialog.text = "Томаса Бойла, естественно. Я же не такой идиот, чтобы под носом у друга крутить шашни с его девушкой!";
			link.l1 = "Полагаю, что так. Это был бы явный перебор...";
			link.l1.go = "ArmoDominic_2";
		break;
		case "ArmoDominic_2":
			dialog.text = ""+ GetSexPhrase("Дружище","" + pchar.name + "") +", окажи мне еще одну услугу.";
			link.l1 = "Опять?..";
			link.l1.go = "ArmoDominic_3";
		break;
		case "ArmoDominic_3":
			dialog.text = "Хм, ну да... Сходи еще раз к Томасу, убеди его, что меня оклеветали.";
			link.l1 = "Кстати, а кто это мог сделать?";
			link.l1.go = "ArmoDominic_4";
		break;
		case "ArmoDominic_4":
			dialog.text = "Да кто угодно в таверне! Когда я с Армо разговаривал, там как раз полгорода сидело.";
			link.l1 = "М-да... Ну ладно, так уж быть, постараюсь убедить Томаса в твоей невиновности.";
			link.l1.go = "ArmoDominic_5";
		break;
		case "ArmoDominic_5":
			dialog.text = "Спасибо тебе"+ GetSexPhrase(", приятель","") +"!";
			link.l1 = "Да не за что.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "to3ToPrison";
			AddQuestRecord("TakeVineToPrisoner", "5");
		break;

		case "KeyDominic":
			dialog.text = "Отлично! Что он сказал?";
			link.l1 = "Он извиняется перед тобой за свое недостойное поведение.";
			link.l1.go = "KeyDominic_1";
		break;
		case "KeyDominic_1":
			dialog.text = "Это Томас, узнаю друга\n"+ GetSexPhrase("Дружище","" + pchar.name + "") +", я тебе бесконечно благодарен!";
			link.l1 = "Слушай, а нельзя ли бесконечную благодарность конвертировать во что-нибудь более осязаемое?";
			link.l1.go = "KeyDominic_2";
		break;
		case "KeyDominic_2":
			dialog.text = "Даже не знаю, что я могу тебе дать\nА, вот что! Я даю тебе ключ от сундуков. Думаю, он тебе пригодится.";
			link.l1 = "Полагаю, что так.";
			link.l1.go = "KeyDominic_3";
		break;
		case "KeyDominic_3":
			dialog.text = "Ну, вот и отлично! Еще раз благодарю тебя.";
			link.l1 = "Не за что, чего уж...";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "key1");
			pchar.questTemp.LSC.LegroHelp = "over";
			AddQuestRecord("TakeVineToPrisoner", "7");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("TakeVineToPrisoner");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
