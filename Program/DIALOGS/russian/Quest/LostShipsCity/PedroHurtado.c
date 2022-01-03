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
					dialog.text = "Ага, так это ты из шторма выш"+ GetSexPhrase("ел","ла") +"? Ну что же, отлично! Давай знакомиться. Меня зовут " + GetFullName(npchar) + ", а тебя?";
					link.l1 = "Мое имя - " + GetFullName(pchar) + ".";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Ага, так это ты из последнего пополнения? Понятно... Ну что же, давай знакомиться. Меня зовут " + GetFullName(npchar) + ", а тебя?";
					link.l1 = "Мое имя - " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест проникновения в дом хозяина магазина
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.store"))
				{
					dialog.text = ""+ GetSexPhrase("Приятель","Подруга") +", не желаешь провернуть одно дельце?";
					link.l1 = "Говори, что за дельце такое.";
					link.l1.go = "StBegin_1";
					break;
				}
				// <-- квесты
				dialog.text = "Ты что-то хотел"+ GetSexPhrase("","а") +"?";
				link.l1 = "Слушай, я ищу одного человека. Не знаешь, где он сейчас?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Хочу задать тебе вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.store") && npchar.quest.store == "waiting" && npchar.chr_ai.type == LAI_TYPE_STAY)
				{
					link.l4 = "Ну что, я готов"+ GetSexPhrase("","а") +" зайти в эту устрашающую дверь.";
					link.l4.go = "StStart_1";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Слушай, я тут ищу некоторые товары.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Знаешь, я набираю команду, чтобы уйти отсюда. Предлагаю тебе пойти ко мне матросом.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;

		case "FS_1":
			dialog.text = "Очень приятно. На шторм внимания не обращай, скоро он закончится. Народ здесь дружный, так что становись граждан"+ GetSexPhrase("ином","кой") +" Города и все будет в порядке. В общем, добро пожаловать в Город!";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Очень приятно. Ну что же, осваивайся здесь понемногу. Народ тут живет довольно дружно, так что добро пожаловать в Город, как говориться...";
			link.l1 = "Спасибо.";
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
			dialog.text = "Слушаю тебя. Спрашивай все, что душе угодно.";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Чертов шторм! И часто у вас такое бывает?";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Что в городе достойно внимания?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Ты сам как сюда попал?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "На Большой земле я не один раз слышал"+ GetSexPhrase("","а") +" об Острове Справедливости. Это, случаем, не ваш Город?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l6 = "Слушай, ты давно уже живешь в Городе?";
				link.l6.go = "ansewer_6";
			}
			link.l10 = "Нет вопросов. Извини, приятель...";
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "Случаются, чего уж... Кстати, тебе надо поговорить с адмиралом Чадом Каппером, если ты до сих пор этого не сделал"+ GetSexPhrase("","а") +".";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = "Это Город Потерянных Кораблей, "+ GetSexPhrase("приятель","" + pchar.name + "") +". Тут живут все те, кто сумел спастись после кораблекрушений. Вот теперь и ты.";
			link.l1 = "Да, теперь и я... Послушай, а почему тут такое творится? Есть какое-нибудь объяснение всем этим крушениям?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Точно никто не знает. Корабли, вроде бы, налетают на рифы. Ну а на рифы их несет течение... Но это так, догадки. Точно никто не знает.";
			link.l1 = "И никто так и не пытался узнать?";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "Пытались, чего уж. Только идея эта плохая - гибнут особо любопытные. Так что и тебе не советую прыть проявлять. Или погибнешь, или крыша поедет...";
			link.l1 = "Да уж, веселенькие перспективы...";
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = "Раз уж попал"+ GetSexPhrase("","а") +" сюда, то смирись и живи как все. Вот тебе мой совет.";
			link.l1 = "Ну что же, за совет спасибо.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Во-первых, тебе нужно побыстрей явиться к адмиралу Города, если еще не был"+ GetSexPhrase("","а") +" у него. Ну а потом можно наведаться в таверну и магазин. Еще есть церковь.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Да так же, как и все - через кораблекрушение"+ GetSexPhrase(", приятель","") +"...";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = "Не знаю... А вообще, "+ GetSexPhrase("дружище","" + pchar.name + "") +", это теперь и твой Город, а не только наш.";
			link.l1 = "Ха, это радует!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_6":
			dialog.text = "Года полтора, не больше.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		//квест проникновения в кабинет хозяина магазина
		case "StBegin_1":
			dialog.text = "Есть тут одно место, где много денег имеется...";
			link.l1 = "И что?";
			link.l1.go = "StBegin_2";
		break;
		case "StBegin_2":
			dialog.text = "Предлагаю пойти туда и забрать их. Потом поделим доход пополам.";
			link.l1 = "Я, в принципе, не против. И где это место?";
			link.l1.go = "StBegin_3";
		break;
		case "StBegin_3":
			dialog.text = "На галеоне 'Эсмеральда'. Это где магазин, только в другой половине корабля. Если мы пойдем туда днем, то хозяина магазина, Эрика Йоста, мы не застанем, а дверь открыть я смогу.";
			link.l1 = "Если там не будет хозяина магазина, и дверь открыть ты сможешь, то зачем ты меня-то зовешь? Ведь половину денег ты теряешь.";
			link.l1.go = "StBegin_4";
		break;
		case "StBegin_4":
			dialog.text = "Ну, там не все так просто. Эрик нанял трех головорезов, они там у него постоянно живут. Мне самому с ними не справиться, а вот ты сумеешь.";
			link.l1 = "Хех, теперь понятно...";
			link.l1.go = "StBegin_5";
		break;
		case "StBegin_5":
			dialog.text = "Ну что, соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Ну что же, можно попробовать. Давай провернем это дельце, деньги мне не помешают.";
			link.l1.go = "StBegin_6";
			link.l2 = "Нет, мне это неинтересно. Воровство, знаешь ли...";
			link.l2.go = "StBegin_not";
		break;
		case "StBegin_not":
			dialog.text = "Ну, как знаешь, "+ GetSexPhrase("приятель","подруга") +"...";
			link.l1 = "Ага, бывай.";
			link.l1.go = "exit";
			npchar.quest.store = "over";
		break;
		case "StBegin_6":
			dialog.text = "Отлично! Итак, договоримся таким образом. Ты сейчас иди по своим делам, как будешь готов"+ GetSexPhrase("","а") +" - дуй к 'Эсмеральде', днем я буду тебя там ждать на квартердеке рядом с дверью, над которой черепушка прибита. Там и разберемся, что к чему...";
			link.l1 = "Договорились.";
			link.l1.go = "exit";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1.location = pchar.location;
			pchar.quest.LCS_SetPedroHurtado.function = "LCS_SetPedroHurtado";
			npchar.quest.store = "waiting";
			AddQuestRecord("ISS_takeStoreMoney", "1");
		break;
		case "StStart_1":
			dialog.text = "Отлично! Ну что же, тогда я открываю?";
			link.l1 = "Да, открывай.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_PedroRunOpenDoor");
		break;
		case "StStart_Opened":
			dialog.text = "Дверь открыта, ты можешь проходить.";
			link.l1 = "Отлично! Сам-то что будешь делать?";
			link.l1.go = "StStart_3";
		break;
		case "StStart_3":
			dialog.text = "Я тебя здесь подожду, снаружи.";
			link.l1 = "Хорошо, ожидай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "StResult";
			npchar.quest.store.money = pchar.money;
			AddQuestRecord("ISS_takeStoreMoney", "2");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("cя","ась"));
			AddDialogExitQuestFunction("LSC_PedroGoWaiting");
		break;
		case "StResult":
			dialog.text = "Ну что, "+ GetSexPhrase("приятель","подруга") +", дело сделано, как я погляжу?";
			link.l1 = "Да, все в порядке, 'причесал"+ GetSexPhrase("'","a'") +" там троих охранников.";
			link.l1.go = "StResult_1";
		break;
		case "StResult_1":
			dialog.text = "Ну, иного я и не ожидал. То, что ты "+ GetSexPhrase("хороший воин","хорошо драться умеешь") +" - видно с полувзгляда... А теперь давай делить добычу"+ GetSexPhrase(", дружище","") +".";
			if (sti(pchar.money) <= sti(npchar.quest.store.money))
			{
				link.l1 = "Слушай, ничего я там не наш"+ GetSexPhrase("ел","ла") +". Не было там денег. Все обыскал"+ GetSexPhrase("","а") +", а денег не наш"+ GetSexPhrase("ел","ла") +".";
				link.l1.go = "StResult_2";
			}
			else
			{
				npchar.quest.store.money = sti(pchar.money) - sti(npchar.quest.store.money); //чистая выручка
				link.l1 = "Всего я наш"+ GetSexPhrase("ел","ла") +" там " + FindRussianMoneyString(sti(npchar.quest.store.money)) + ". Половина, как и договаривались, твоя.";
				link.l1.go = "StResult_3";
			}
		break;
		case "StResult_2":
			dialog.text = "Да уж, такого исхода я не ожидал... Ну, да ладно. Денег здесь - как грязи, достану где-нибудь в другом месте...";
			link.l1 = "Тоже верно.";
			link.l1.go = "StResult_4";
			AddQuestRecord("ISS_takeStoreMoney", "3");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("ел","ла"));
		break;
		case "StResult_3":
			dialog.text = "Ну, вот и отлично! Рад, что все так удачно завершилось... Ну, бывай, "+ GetSexPhrase("приятель","подруга") +". Будут проблемы - обращайся.";
			link.l1 = "Всенепременно.";
			link.l1.go = "StResult_4";
			AddMoneyToCharacter(pchar, -makeint(sti(npchar.quest.store.money)/2));
			AddQuestRecord("ISS_takeStoreMoney", "4");
			CloseQuestHeader("ISS_takeStoreMoney");
		break;
		case "StResult_4":
			npchar.quest.store = "over"; //флаг этого миниквеста
			LAi_SetLoginTime(npchar, 6.0, 21.99);
			LAi_SetLSCoutType(npchar);
			LAi_group_MoveCharacter(npchar, "TmpEnemy");
			SaveCurrentNpcQuestDateParam(npchar, "location");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Что за товары?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                "Ты уже спрашивал меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны ядра, бомбы, книппеля, провиант, лекарства, порох, оружие...",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Зачем это тебе?";
			link.l1 = "Да так, на всякий случай.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Ну, бомбы с ядрами, да и прочие боеприпасы, можно достать у хозяек кораблей. Этого добра навалом. А вот порох и оружие - это только у адмирала.";
			link.l1 = "Ясно. Ну что же, спасибо тебе.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Однако!.. Что-то отстал от жизни.";
			link.l1 = "Я жду ответа.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = ""+ GetSexPhrase("Дружище","" + pchar.name + "") +", у тебя что, действительно есть корабль, на котором можно уплыть отсюда?";
			link.l1 = "Да.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Тогда и думать нечего! Я согласен.";
			link.l1 = "Отлично! Прямо сейчас отправляйся на 'Сан Габриэль', там Механик переправит тебя на мой фрегат.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо, вещички только соберу по быстрому.";
			link.l1 = "Не задерживайся!";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
