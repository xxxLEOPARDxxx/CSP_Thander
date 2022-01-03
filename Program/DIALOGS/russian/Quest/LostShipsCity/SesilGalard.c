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
			//после драки, когда Сесил пытаются убить
			if (pchar.questTemp.LSC == "toKnowAboutMechanic")
			{
				dialog.text = "Вы убили их! Спасибо вам!";
				link.l1 = "Хм, а кто эти люди?";
				link.l1.go = "AfterFight";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "AvaShipInside3") dialog.text = "Приветствую вас в моей скромной обители, капитан. Как добрались в шторм?";
					else dialog.text = "Приветствую вас, капитан. Как добрались в шторм?";
					link.l1 = "Не без проблем, но спасибо за заботу. Моё имя " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				else
				{
					if (npchar.location == "AvaShipInside3") dialog.text = "Приветствую вас в моей скромной обители, капитан. Как добрались?";
					else dialog.text = "Приветствую вас, капитан. Как добрались?";
					link.l1 = "Не без проблем, но спасибо за заботу. Моё имя " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что вам опять нужно?";
				link.l1 = "Вы знаете, я ищу одного человека. Не поможете мне?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Я хотел"+ GetSexPhrase("","а") +" задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал бы последние сплетни...");
				link.l3.go = "rumours_LSC";
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


		case "FS_1":
			dialog.text = GetFullName(npchar) + ", капитан. Рада знакомству.";
			link.l1 = "Чем вы занимаетесь здесь в такую погоду?";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "При всём уважении, капитан, это не ваше дело.";
			link.l1 = "Понимаю. Нам всем есть что скрывать, не так ли?";
			link.l1.go = "FS_3";
		break;
		case "FS_3":
			dialog.text = "Прошу Вас покинуть мой дом!";
			link.l1 = "А Закон позволяет вам это делать?";
			link.l1.go = "FS_4";
		break;
		case "FS_4":
			dialog.text = "Если визитер является "+ GetSexPhrase("хамовитым мужланом","невоспитанной девкой") +", то вполне!";
			link.l1 = "О-о, спасибо за комплимент...";
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = GetFullName(npchar) + ", капитан. Рада знакомству.";
			link.l1 = "Чем вы занимаетесь здесь?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "При всём уважении, капитан, это не ваше дело.";
			link.l1 = "Понимаю. Нам всем есть что скрывать, не так ли?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Прошу Вас покинуть мой дом!";
			link.l1 = "Не горячитесь, я всего лишь осваиваюсь.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Осваивайтесь в другом месте.";
			link.l1 = "Хм, я не доставлю вам беспокойства.";
			link.l1.go = "exit";
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
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Чем тут можно заняться, кроме как расхаживать туда-сюда, жалея самого себя?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Как организована жизнь? Здесь люди работают?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Высокомерн"+ GetSexPhrase("ый дурак","ая дура") +"! Лучше бы вам позабыть о том, как вы были сильны в море и на суше. Возможно, конечно, так и было... но не здесь! Здесь вы никто, как и все мы, и для вас сейчас важно добиться расположения людей в городе, а вы...";
			link.l1 = "Я вовсе не хотел"+ GetSexPhrase("","а") +" вас обидеть, мадам. Просто подскажите, чем здесь можно себя занять на досуге. Чем-нибудь интересным, а?..";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Интересным? А вы любитель"+ GetSexPhrase("","ница") +" риска, наверное, "+ GetSexPhrase("бывалый джентльмен удачи","бывалая 'леди удачи'") +", да? Ну, попробуйте сходить в гости к 'нарвалам', например...";
			link.l1 = "Это вы про клан 'Нарвал'?";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "О них, родим"+ GetSexPhrase("ый","ая") +". Впечатлений будет масса, обещаю.";
			link.l1 = "Хм, а вы веселая дама, как я погляжу...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Ха, если бы в этом был смысл... или цель. Но вы не можете ставить перед собой цели. Вы не уйдёте отсюда жив"+ GetSexPhrase("ым","ой") +", вы будете существовать, как и все мы.";
			link.l1 = "Весьма обнадёживающе...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//квесты
		case "HelpMe":
			dialog.text = "Боже мой, помогите мне!! Не дайти им меня убить!!";
			link.l1 = "Что случилось?..";
			link.l1.go = "HelpMe_1";
		break;
		case "HelpMe_1":
			dialog.text = "Потом... Защитите меня, прошу вас!";
			link.l1 = "Хм, я пока никого не вижу.";
			link.l1.go = "exit";
			npchar.quest.meeting = "1";
			AddDialogExitQuestFunction("LSC_SaveSesilGalard_2");
		break;

		case "AfterFight":
			dialog.text = "Это 'касперы'.";
			link.l1 = "Они уже и этот корабль приватизировали?";
			link.l1.go = "AfterFight_1";
		break;
		case "AfterFight_1":
			dialog.text = "Нет, что вы. Они пришли просто убить меня.";
			link.l1 = "Так вот и просто? Они же нарушили Закон Города, дающий гражданам право на жизнь!";
			link.l1.go = "AfterFight_2";
			npchar.greeting = "Gr_Woman_Citizen";
		break;
		case "AfterFight_2":
			dialog.text = ""+ GetSexPhrase("Молодой человек","Девушка") +", вот что я вам скажу... Я, наверное, старейший житель этого острова, и не такое еще видела здесь.";
			link.l1 = "Вы жили здесь еще до того, как Хилл Брюннер попал в Город?";
			link.l1.go = "AfterFight_3";
		break;
		case "AfterFight_3":
			dialog.text = "Я живу здесь уже около десяти лет. Когда меня вынесло к острову, на нем жили только пять человек, и Хилла Брюннера среди них не было.";
			link.l1 = "Вот это да... Вы знаете, а ведь Хилл Брюннер перед смертью искал человека, который попал на остров раньше него.";
			link.l1.go = "AfterFight_4";
		break;
		case "AfterFight_4":
			dialog.text = "А вы не знаете, зачем?";
			link.l1 = "Судя по всему, спросить о Механике.";
			link.l1.go = "AfterFight_5";
		break;
		case "AfterFight_5":
			dialog.text = "Хм, ну надо же... Вы знаете, с тех пор, как его изолировали, вы второй человек, которому я рассказываю о нем. Первым был Тизер Дэн.";
			link.l1 = "Тизер Дэн?! Черт возьми, вы знаете что с ним произошло?";
			link.l1.go = "AfterFight_6";
		break;
		case "AfterFight_6":
			dialog.text = "Говорят, что он утонул.";
			link.l1 = "Ничего подобного. Он добрался до Большой земли!";
			link.l1.go = "AfterFight_7";
		break;
		case "AfterFight_7":
			dialog.text = "Значит, он жив?!";
			link.l1 = "Гм, теперь уже нет... Его убили в Виллемстаде агенты Голландской Ост-Индской компании.";
			link.l1.go = "AfterFight_8";
		break;
		case "AfterFight_8":
			dialog.text = "Ах, как жаль! Он исполнил свою мечту - выбрался отсюда, но уберечь себя так и не сумел. Жаль...";
			link.l1 = "Да, жаль... Послушайте, так кто такой этот Механик?";
			link.l1.go = "AfterFight_9";
		break;
		case "AfterFight_9":
			dialog.text = "О-о-о, это легендарный человек, его зовут Хенрик Ведекер. Абсолютное большинство граждан Города даже не знают, что он живет с нами. С тех пор, как клан 'Каспер' обосновался на барке 'Сан Габриэль', Механика я не видела.";
			link.l1 = "Вы сказали, что его изолировали...";
			link.l1.go = "AfterFight_10";
		break;
		case "AfterFight_10":
			dialog.text = "Ну, а как это еще можно назвать? Думаю, что адмирал держит Хенрика в изоляции специально. Все дело в том, что Механик - необыкнованно талантливый человек в плане смастерить что-нибудь. Одно время начал он рассказывать об какой-то опасности, грозящей нам всем. Говорил о том, что мы должны покинуть Город, пока не поздно\n"+
				"Но вы знаете, чудаковатых людей воспринимают несерьезно, вот и над его байками хохотали только. А потом вышел Закон о недопущении строительства плавательных средств, и сразу же 'касперы' заняли Сан Габриэль. Ну и о нашем чудаке как-то неприлично стало вспоминать, да и небезопасно.";
			link.l1 = "Что значит, небезопасно?";
			link.l1.go = "AfterFight_11";
		break;
		case "AfterFight_11":
			dialog.text = "Люди, знавшие Хенрика лично, стали пропадать бесследно. И я бы тоже сегодня пропала, если бы не вы...";
			link.l1 = "Вы имеете в виду это покушение на убийство?";
			link.l1.go = "AfterFight_12";
		break;
		case "AfterFight_12":
			dialog.text = "Именно. Скрыть следы преступления сейчас стало очень просто. Дело в том, что под нами, на глубине, завелись какие-то жуткие твари. Если сбросить тело в воду, то оно даже не всплывет потом...";
			link.l1 = "М-да... А зачем Механика изолировали? А может, его уже убили?";
			link.l1.go = "AfterFight_13";
		break;
		case "AfterFight_13":
			dialog.text = "Механик жив, так как он слишком нужный человек. Ведь это он придумал способ крепления кораблей друг с другом. Когда я сюда попала, тут было всего четыре корабля, и они постоянно двигались. А Хенрик сумел их так скрепить, чтобы они держались нормально.";
			link.l1 = "Ах, вот оно что...";
			link.l1.go = "AfterFight_14";
		break;
		case "AfterFight_14":
			dialog.text = "А изолировал его Чад после того, как тот стал паниковать. Говорил, что мы все должны уйти отсюда, пока есть такая возможность...";
			link.l1 = "Понятно. Полагаю, что я долж"+ GetSexPhrase("ен","на") +" добраться до вашего гениального Хенрика и переговорить с ним.";
			link.l1.go = "AfterFight_15";
		break;
		case "AfterFight_15":
			dialog.text = "Ну что же, дерзайте. Удачи!";
			link.l1 = "Спасибо.";
			link.l1.go = "AfterFight_16";
		break;
		case "AfterFight_16":
			LAi_SetOwnerTypeNoGroup(npchar);
			pchar.questTemp.LSC = "toSeekMechanik";
			AddQuestRecord("ISS_MainLine", "31");
			pchar.quest.LSC_enterCasper.win_condition.l1 = "location";
			pchar.quest.LSC_enterCasper.win_condition.l1.location = "SanGabrielMechanic";
			pchar.quest.LSC_enterCasper.function = "LSC_enterCasper";
			sld = characterFromID("Casper_head");
			LAi_SetImmortal(sld, false);
			for (int i=1; i<=11; i++)
			{
				sld = characterFromID("Casper_"+i);
				LAi_SetImmortal(sld, false);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Интересное предложение...",
				"Мы уже говорили об этом.",
				"Это уже обсуждено, второй раз повторяю.",
                "Хватит, вы меня утомили...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, и своевременное, к тому же. На Город надвигается страшная буря.",
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаете...",
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Да что вы говорите? И кто это вам сказал?";
			link.l1 = "Ни кто иной, как прекрасно знакомый вам Хенрик Ведекер.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Хм... Вы знаете, а я рискну и останусь здесь. Я уже слишком стара для морских путешествий.";
			link.l1 = "Вы уверены в своем решении? Я не для того спасал"+ GetSexPhrase("","а") +" вас от 'касперов', чтобы вы так бездарно рисковали своей жизнью теперь.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Согласитесь, капитан, что я имею на это право.";
			link.l1 = "Бесспорно.";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "Тогда разговор окончен.";
			link.l1 = "Ну что же, очень жаль.";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
