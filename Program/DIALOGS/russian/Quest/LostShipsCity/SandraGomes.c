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
					dialog.text = "Здравствуйте, сеньор"+ GetSexPhrase("","ита") +". Это вы т"+ GetSexPhrase("от","а") +" нов"+ GetSexPhrase("ый гражданин","ая гражданка") +", что сумел"+ GetSexPhrase("","а") +" спастись в последнем крушении?";
					link.l1 = "Да, это я. " + GetFullName(pchar) + " к вашим услугам, сеньора...";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Здравствуйте, сеньор"+ GetSexPhrase("","ита") +". Это вы "+ GetSexPhrase("тот новый гражданин, что сумел","та новая гражданка, что сумела") +" спастись в последнем крушении?";
					link.l1 = "Да, это я. " + GetFullName(pchar) + " к вашим услугам, сеньора...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Вам что-то нужно, сеньор"+ GetSexPhrase("","ита") +"?";
				link.l1 = "Вы знаете, я ищу одного человека. Вы не видели его в последнее время?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Я хотел"+ GetSexPhrase("","а") +" задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" && sld.quest.takeMap != "discount")
				{
					link.l4 = "Вы не представляете, каким жадным и эгоистичным человеком является Эрик Йост!";
					link.l4.go = "takeMap";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Знаете, я набираю команду, чтобы уйти отсюда. Я предлагаю вам плыть со мной на Большую землю.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "В этом шторме выжили только вы. Знаете, вам очень повезло, ведь вы разбились о рифы тогда, когда шторм уже потерял свою силу. Кстати, меня зовут " + GetFullName(npchar) + ".";
			link.l1 = "Ну что же, будем знакомы, сеньора.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Очень приятно! А меня зовут " + GetFullName(npchar) + ".";
			link.l1 = "Ну что же, будем знакомы, сеньора.";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи е"+ GetSexPhrase("го","е") +", он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумали?! Теперь граждане и милиция порвут тебя, как старую газету!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал"+ GetSexPhrase("","а") +" оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это "+ GetSexPhrase("серьезному мужчине","девушке") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = "Если видела, то обязательно скажу вам. Так кого вы ищете?";
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
					dialog.text = GetFullName(sld) + ", вы его имеете ввиду?";
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
					dialog.text = LinkRandPhrase("Понятия не имею, где он.", "Ни малейшего представления не имею, где он сейчас.", "Я не видела его уже прилично по времени. Так что не могу знать.");
					link.l1 = RandPhraseSimple("Понятно.", "Ясно... Что же, спасибо.");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Понятия не имею, где она.", "Ни малейшего представления не имею, где он сейчас.", "Я не видела ее уже прилично по времени. Так что не могу знать.");
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
							dialog.text = LinkRandPhrase("Он здесь, на этом корабле. Смотрите внимательней, пожалуйста.", "Хм, так ведь он сейчас на этом корабле...", "Он на этом корабле, странно, что вы еще встретились.");
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
							dialog.text = LinkRandPhrase("Она здесь, на этом корабле. Смотрите внимательней, пожалуйста.", "Хм, так ведь она сейчас на этом корабле...", "Она на этом корабле, странно, что вы еще встретились.");
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
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Скажите, часто тут случаются штормы?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Послушайте, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Не подскажете мне, " + GetAddress_FormToNPC(NPChar) + ", на что в городе стоит обратить внимание?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Что за человек, этот адмирал?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = "Скажите, вы попали сюда раньше Хилла Брюннера?";
				link.l5.go = "ansewer_5";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = "Нет, что вы, очень редко. Вы знаете, когда у нас штормит, то многие мужчины чуть ли не пачкают панталоны, а мне все нипочем. Штормов я не боюсь!";
			link.l1 = "Надо же, какая вы отважная испанка!";
			link.l1.go = "ansewer_4_1";
		break;
		case "ansewer_4_1":
			dialog.text = "Да, я такая, сеньор"+ GetSexPhrase("","ита") +"!";
			link.l1 = "Ну что же, желаю вам таковой и оставаться, сеньора.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = "Этот остров называется Городом Потерянных Кораблей. Все мы оторваны от окружающего мира и живем без надежды вырваться из этой клетки...";
			link.l1 = "Неужели все так печально? Я единственн"+ GetSexPhrase("ый","ая") +", кто спасся, мне повезло. Судя по всему, и вы тоже в категории счастливчиков.";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "С этой стороны, канечно, так оно и есть. Но если бы вы знали, как все это надоело! Ничего нового, только крушения и смерть вокруг нас. Живем в кольце несчастий, как это тягостно!..";
			link.l1 = "Ну, это да...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Я думаю, для начала вам стоит заглянуть в таверну. Есть церковь и магазин... Кстати, если вы еще не были у адмирала, то сначала вам стоит отправиться именно туда!";
			link.l1 = "Хорошо, я так и сделаю. Спасибо.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Чад Каппер - серьезный мужчина. Говорят, в прошлой жизни он был капитаном пиратов! Три года назад он попал сюда и сразу прибрал власть к рукам. С тех пор он - бессменный адмирал Города.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = "Раньше Хилла Брюннера? Я что, так стара?";
			link.l1 = "Нет, что вы! Извините...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Однако, вы меня поразили...";
			link.l1 = "Чем, сеньора?";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Вы нарушили Закон, и ведете себя так, как будто все нормально.";
			link.l1 = "Я спасаю свою жизнь, у меня нет иного выбора. Если вы присоединитесь ко мне, то также спасетесь.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Спасусь от чего?";
			link.l1 = "От надвигающейся бури, которая уничтожит Город. И это не пустые страхи, поверьте мне.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "А вы знаете, я верю вам. К тому же, мне надоело здесь все до смерти. Так что я с вами, капитан.";
			link.l1 = "Отлично. Сейчас как можно быстрей отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль.";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "Я поняла вас. Все сделаю, как вы сказали.";
			link.l1 = "Прошу вас, быстрее...";
			link.l1.go = "SeekCrew_all";
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = "Что у вас стряслось?";
			link.l1 = "Знаете, он хочет меня буквально ограбить!";
			link.l1.go = "TakeMap_1";
		break;
		case "TakeMap_1":
			dialog.text = "Не может быть.";
			link.l1 = "Ну, не приставив к горлу нож, конечно. Этот ваш Эрик Йост хочет продать мне карту Города за немыслимую цену!";
			link.l1.go = "TakeMap_2";
		break;
		case "TakeMap_2":
			dialog.text = "Ну, это в порядке вещей. Если у вас есть что продать, вы вправе выставлять любую цену на товар. И Эрик также в своем праве.";
			link.l1 = "Н-да, хорошенькое право...";
			link.l1.go = "TakeMap_3";
		break;
		case "TakeMap_3":
			dialog.text = "И что, вам так нужна эта карта? Без неё совсем плутаете?";
			link.l1 = "Да, тяжеловато...";
			link.l1.go = "TakeMap_4";
		break;
		case "TakeMap_4":
			dialog.text = "Ну хорошо, я помогу вам. Ведь Господь требует от нас быть милосердными к ближнему\nЗайдите к Эрику завтра, я скажу ему, чтобы он снизил цену на эту карту до божеской.";
			link.l1 = "И он послушает вас?";
			link.l1.go = "TakeMap_5";
		break;
		case "TakeMap_5":
			dialog.text = "Без сомнения.";
			link.l1 = "Спасибо вам огромное!";
			link.l1.go = "exit";
			sld = characterFromId("LSC_Trader");
			sld.quest.takeMap = "discount";
			sld.quest.takeMap.name = GetFullName(npchar);
		break;
	}
	NextDiag.PrevNode = NodeName;
}
