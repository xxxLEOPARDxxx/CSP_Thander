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
					dialog.text = "Здравствуйте! Я рада вас видеть. Вы знаете, в этом ужасном шторме выжили, похоже, только вы... Ой, простите, "+ GetSexPhrase("сэр","мисс") +", меня зовут " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " к вашим услугам. Рад"+ GetSexPhrase("","а") +" приветствовать гостеприимных хозяев.";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Здравствуйте! Я рада видеть нов"+ GetSexPhrase("ого","ую") +" граждан"+ GetSexPhrase("ина","ку") +". Вы знаете, в том ужасном последнем шторме выжили, похоже, только вы... Ой, простите, "+ GetSexPhrase("сэр","мисс") +", меня зовут " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " к вашим услугам. Рад"+ GetSexPhrase("","а") +" приветствовать гостеприимных хозяев.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Вам что-то нужно, "+ GetSexPhrase("сэр","мисс") +"?";
				link.l1 = "Вы знаете, я ищу одного человека. Не поможете мне?";
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
			dialog.text = "Вы знаете, давать приют любому в шторм - наша обязанность. Однако я всегда это делаю с огромным удовольствием.";
			link.l1 = "Это очень похвально.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "Вы знаете, мы и так в Городе как в клетке. Поэтому я всегда рада общению с новыми людьми.";
			link.l1 = "Я также рад"+ GetSexPhrase("","а") +" знакомству с приятным в общении человеком. Я так понимаю, что Город немноголюден.";
			link.l1.go = "FT_2";
		break;

		case "FT_1":
			dialog.text = "Вы знаете, сейчас погода хорошая. Но я бываю иногда даже рада, что начинается буря и застигнутые на 'Веласко' люди остаются у меня, чтобы переждать непогоду. Есть с кем поговорить...";
			link.l1 = "Да уж, у вас тут немноголюдно.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Что уж и говорить, тоска бывает смертная... Ну, а вы как к нам попали? Рассказывайте.";
			link.l1 = "Мой корабль разбился, и я потерял"+ GetSexPhrase("","а") +" всю команду. К сожалению... Хотя, с другой стороны, мне еще и повезло.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Гм... Звучит несколько кощунственно, но вам действительно повезло.";
			link.l1 = "Да, я это понимаю.";
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
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием наизготовку. Это меня пугает...");
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
							dialog.text = LinkRandPhrase("Простите, но он находится прямо здесь, " + npchar.quest.seekIdx.where + ". Вам нужно быть внимательн"+ GetSexPhrase("ым","ой") +".", "Хм, он ведь здесь, среди нас!", "Если бы вы посмотрели вокруг более внимательно, то наверняка уже увидели бы его...");
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
							dialog.text = LinkRandPhrase("Простите, но она находится прямо здесь, " + npchar.quest.seekIdx.where + ". Вам нужно быть внимательным.", "Хм, она ведь здесь, среди нас!", "Если бы вы посмотрели вокруг более внимательно, то наверняка уже увидели бы ее...");
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
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = "Давно вы сюда попали?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Добро пожаловать в Город Потерянных Кораблей, именно так называется этот остров.";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Не сказать, чтобы давно. Однако, надоесть все это успело до смерти.";
			link.l1 = "Понимаю...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Боже мой, это не сон?";
			link.l1 = "Это явь...";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Господи, наконец-то это свершилось! Я смогу уплыть отсюда?";
			link.l1 = "Да, если поторопитесь.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Я готова на все. Что я должна делать?";
			link.l1 = "Отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль. И не медлите!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо, скоро буду на 'Сан Габриэле'.";
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
			dialog.text = "И что, вам так нужна эта карта? Без нее совсем плутаете?";
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
