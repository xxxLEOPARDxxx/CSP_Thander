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
					dialog.text = "Здравствуйте, "+ GetSexPhrase("сэр","мисс") +". Я очень рада, вы сумели спастись после этой ужасной катастрофы... Хотя, что говорить, мы все через это прошли... Вы знаете, скоро этот шторм закончится, и настроение у вас точно поднимется. Да, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " к вашим услугам, мисс... Скажите, после каждого шторма у вас бывает пополнение?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Здравствуйте, "+ GetSexPhrase("сэр","мисс") +". Я очень рада, вы сумели спастись после этой ужасной катастрофы... Хотя, что говорить, мы все через это прошли. Да, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " к вашим услугам, мисс...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что вам нужно?";
				link.l1 = "Вы знаете, я ищу одного человека. Не поможете мне?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Я хотел"+ GetSexPhrase("","а") +" задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "begin")
				{
					link.l7 = "Я слышал"+ GetSexPhrase("","а") +", что вы ищете помощи в одном деле...";
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = "Меня послал к вам ваш муж, Максим Тейлор.";
					link.l7.go = "ELTHusb_toElis";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElisGood")
				{
					link.l7 = "Элис, адмирал освободит вашего мужа.";
					link.l7.go = "ELTHusb_good";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Послушайте, я ищу некоторые товары.";
					link.l8.go = "SeekGoods";
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
			dialog.text = "Нет, это далеко не так, к сожалению. Кораблей к нам пристает много, а вот живых людей там оказывается маловато. Не знаю, почему... И, кстати, я миссис.";
			link.l1 = "О-о, простите...";
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = "Миссис. Я замужем.";
			link.l1 = "О-о, простите...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Кстати, если вы еще не были у нашего главы, адмирала Чада Каппера, то вам лучше поторопиться. Иначе, он сам к вам придет.";
			link.l1 = "Хм, понятно.";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи его, он"+ GetSexPhrase("","а") +" нашрушил"+ GetSexPhrase("","а") +" Закон!");
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
				link.l1 = "Послушайте, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Вы англичанка?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Скажите, вы давно уже живете в Городе?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Как, вы еще не знаете? Это Город Потерянных Кораблей. А мы здесь все - потерянные люди... Ах, до чего же все это надоело!";
			link.l1 = "Понимаю...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Да, я англичанка. А что?";
			link.l1 = "А много здесь англичан вообще?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Имеются, но я не считала. Вы знаете, здесь совершенно все равно, какой вы нации. Это ровным счетом ни о чем не говорит и ни на что не влияет.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Да, я англичанка. А что?";
			link.l1 = "А много здесь англичан вообще?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Не очень, около полугода.";
			link.l1 = "Ясно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Какие именно?",
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
			dialog.text = "Ну, провианта и лекарств у меня нет. А вот ядер на корабле осталось довольно много еще с тех времен, когда он ходил под парусом. А сколько вам нужно?";
			link.l1 = "100 штук вполне хватит.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Ну хорошо, забирайте.";
			link.l1 = "Спасибо огромное! А не подскажете, кто может перетащить их на 'Сан Габриэль'?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Хм, ну, не знаю... Попросите Феликса Мендозу!";
			link.l1 = "Хорошо, обязательно так и поступлю. Спасибо!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.balls = true;
			AddQuestRecord("ISS_MainLine", "49");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Однако... И почему я должна верить вам?";
			link.l1 ="Вы ничего мне не должны. Но если вы не уйдете сейчас со мной, то наверняка погибнете. Дело в том, что надвигающийся шторм разрушит Город.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "А откуда вы знаете?";
			link.l1 = "Это вычислил Механик.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Ох, я верю Ведекеру, видимо, так и произойдет\nНу что же, я согласна.";
			link.l1 = "Хорошо. Сейчас отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Договорились.";
			link.l1 = "Только не задерживайтесь нигде!";
			link.l1.go = "SeekCrew_all";
		break;
		//вызволение мужа
		case "ELTHusb_begin":
			dialog.text = "Именно так, "+ GetSexPhrase("сэр","мисс") +". Мой муж, этот кретин Максим, опять попал в тюрьму. Хочу помочь ему в последний раз.";
			link.l1 = "Насколько я понимаю, вы хотите вызволить его из тюрьмы.";
			link.l1.go = "ELTHusb_begin_1";
		break;
		case "ELTHusb_begin_1":
			dialog.text = "Верно. Сделайте это, и я сумею вас отблагодарить.";
			link.l1 = "Чем, позвольте спросить?";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "Ну, вы нов"+ GetSexPhrase("ый гражданин","ая гражданка") +" Города. Я могу дать вам очень нужную вещь.";
			link.l1 = "Что именно?";
			link.l1.go = "ELTHusb_begin_3";
		break;
		case "ELTHusb_begin_3":
			dialog.text = "Один из ключей, на который запираются все сундуки в Городе.";
			link.l1 = "Это действительно нужная вещь. Я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = "Извините, мне это не нужно.";
			link.l2.go = "ELTHusb_begin_disagree";
		break;
		case "ELTHusb_begin_disagree":
			dialog.text = "Ну, что же, очень жаль. Поищу помощи у других людей.";
			link.l1 = "Счастливо.";
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
		break;
		case "ELTHusb_begin_4":
			dialog.text = "Очень хорошо. Тогда я буду ждать своего мужа.";
			link.l1 = "Я все сделаю, ожидайте.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "5");
			AddQuestUserData("ISS_ElisHusband", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.LSC.ElisHusband = "seekFreeMotod";
			sld = characterFromId("MaximTailor");
			sld.dialog.currentnode = "DontRemember";
		break;

		case "ELTHusb_toElis":
			dialog.text = "И чего хочет этот мерзавец?";
			link.l1 = "Я так понимаю, что он хочет выйти из тюрьмы.";
			link.l1.go = "ELTHusb_toElis_1";
		break;
		case "ELTHusb_toElis_1":
			dialog.text = "Как я от него устала!..";
			link.l1 = "Послушайте, вы хотите вытащить его оттуда или нет? Если хотите, то я мог"+ GetSexPhrase("","ла") +" бы помочь в этом деле.";
			link.l1.go = "ELTHusb_toElis_2";
		break;
		case "ELTHusb_toElis_2":
			dialog.text = "Хорошо, я принимаю вашу помощь. Освободите его, и я дам вам очень нужную вещицу.";
			link.l1 = "Хм... А что именно, позвольте вас спросить?";
			link.l1.go = "ELTHusb_toElis_3";
		break;
		case "ELTHusb_toElis_3":
			dialog.text = "Один из ключей, что открывают сундуки в Городе.";
			link.l1 = "Это нужная штука, я соглас"+ GetSexPhrase("ен","на") +"!";
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = "Извините, мне это не нужно.";
			link.l2.go = "ELTHusb_begin_disagree";
		break;

		case "ELTHusb_good":
			dialog.text = "Боже мой, неужели это правда? Как вам удалось это сделать?";
			link.l1 = "Ну, я кое-что выяснил"+ GetSexPhrase("","а") +" и рассказал"+ GetSexPhrase("","а") +" об этом адмиралу. Чад согласился дать вашему мужу еще один шанс остепениться.";
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = "Отлично! Думаю, что после такой встряски он больше не будет так пить.";
			link.l1 = "Очень на это надеюсь.";
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = "Вы сдержали свое слово, а я сдержу свое. Извольте получить ключ.";
			link.l1 = "Спасибо вам, он мне действительно нужен.";
			link.l1.go = "ELTHusb_good_3";
			GiveItem2Character(pchar, "key1");
		break;
		case "ELTHusb_good_3":
			dialog.text = "Но имейте в виду, что вам не стоит шарить по чужим сундукам. Если вас застукают, то вам конец.";
			link.l1 = "Я это понимаю, спасибо.";
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
			SetTimerFunction("LSC_ElisHusbandSet", 0, 0, 1);
		break;

	}
	NextDiag.PrevNode = NodeName;
}
