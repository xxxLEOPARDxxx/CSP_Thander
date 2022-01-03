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
			//если Сесил Галард замочили, то это оставшийся шанс узнать о Механике
			if (pchar.questTemp.LSC == "SessilIsDead")
			{
				dialog.text = "Скажите, это правда, что вы пытались спасти Сесил Галард?";
				link.l1 = "Да, это так. К сожалению, не получилось...";
				link.l1.go = "SessilDead";
				npchar.quest.meeting = "1";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "FurieShipInside2") dialog.text = "Боже мой, какой шторм!.. Здравствуйте, меня зовут " + GetFullName(npchar) + ", я хозяйка этого дома.";
					else dialog.text = "Боже мой, как шторм!.. Здравствуйте, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "Очень приятно. А я - капитан " + GetFullName(pchar) + ". Вернее, бывш"+ GetSexPhrase("ий","ая") +" капитан. А все из-за этого дьявольского шторма!";
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "FurieShipInside2") dialog.text = "Здравствуйте, меня зовут " + GetFullName(npchar) + ", я хозяйка этого дома.";
					else dialog.text = "Здравствуйте, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "Очень приятно. А я - капитан " + GetFullName(pchar) + ". Вернее, бывш"+ GetSexPhrase("ий","ая") +" капитан...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что вам нужно, "+ GetSexPhrase("месье","мадемуазель") +"?";
				link.l1 = "Вы знаете, я ищу одного человека. Не поможете мне?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Я хотел"+ GetSexPhrase("","а") +" задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
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
			dialog.text = "Не поминайте нечистого, а то появится! И, находясь у меня дома, извольте не сквернословить!";
			link.l1 = "О-о, простите...";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Ну, не стоит так переживать. В конце концов, вы живы, а это уже очень даже неплохо!";
			link.l1 = "Да, вы правы. Прошу прощения за минутную слабость"+ GetSexPhrase(", недостойную мужчины","") +"...";
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
				link.l1 = "Давно вы здесь?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Скучаете?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Скажите, а вы оказались здесь раньше Хилла Брюннера?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "У меня нет к вам вопросов, извините.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Я лично... хм, не припоминаю уже. Но если вам интересно, давно ли этот город стоит здесь, то... очень давно. Очень.";
			link.l1 = "Ясно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "По родным землям? Конечно... Но приходится мириться с обстоятельствами. Человек может приспосабливаться, что и требуется от нас.";
			link.l1 = "Что-то не горю желанием.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Нет, он уже был здесь хозяином таверны.";
			link.l1 = "Понятно... Послушайте, а имя или кличка Механик вам ни о чем не говорит?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "М-м-м... не припоминаю, извините. Вы знаете, я сейчас несколько занята и не хотела бы продолжать эту беседу. Простите.";
			link.l1 = "Понятно. Ну что же, спасибо вам.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "30");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
		break;

		case "SessilDead":
			dialog.text = "Сесил была старейшим жителем Города... Вы знаете, почему ее убили?";
			link.l1 = "Нет, но я, как и Хилл Брюннер, искал"+ GetSexPhrase("","а") +" человека, который смог бы мне ответить на вопрос. Она, наверное, смогла бы.";
			link.l1.go = "SessilDead_1";
		break;
		case "SessilDead_1":
			dialog.text = "И что это за вопрос?";
			link.l1 = "Кто такой Механик?";
			link.l1.go = "SessilDead_2";
		break;
		case "SessilDead_2":
			dialog.text = "Я знаю, кто это. Я не хотела говорить об этом раньше, так как считала такие разговоры небезопасными. Но смерть Сесил заставила меня изменить мнение...";
			link.l1 = "Говорите, я внимательно вас слушаю.";
			link.l1.go = "SessilDead_3";
		break;
		case "SessilDead_3":
			dialog.text = "Имя Механика - Хенрик Ведекер. Большинство граждан Города даже не знают, что он живет с нами. С тех пор, как клан 'Каспер' обосновался на барке 'Сан Габриэль', Механика я не видела.";
			link.l1 = "Вы тоже давно живете в Городе?";
			link.l1.go = "SessilDead_4";
		break;
		case "SessilDead_4":
			dialog.text = "Не так давно, как жила Сесил, но все же давно. Механика я видела...";
			link.l1 = "Так вы говорите, что этот Хенрик находится барке 'Сан Габриэль'?";
			link.l1.go = "SessilDead_5";
		break;
		case "SessilDead_5":
			dialog.text = "Да. Думаю, что адмирал держит Хенрика в изоляции специально, поэтому и отдал барк 'Сан Габриэль' клану 'Каспер'. Все дело в том, что Механик - необыкновенно талантливый человек. Когда нужно смастерить что-нибудь, ему равных нет. Одно время начал он рассказывать об какой-то опасности, грозящей нам всем. Говорил о том, что мы должны покинуть Город, пока не поздно\n"+
				"Но вы знаете, чудаковатых людей воспринимают несерьезно, вот и над его байками хохотали только. А потом вышел Закон о недопущении строительства плавательных средств, и сразу же касперы заняли 'Сан Габриэль'. Ну и о нашем чудаке как-то неприлично стало вспоминать, да и небезопасно.";
			link.l1 = "А вы уверены, что Хенрик еще жив?";
			link.l1.go = "SessilDead_6";
		break;
		case "SessilDead_6":
			dialog.text = "Уверена. Дело в том, Хенрик изобрел способ крепления кораблей в острове, он нужен адмиралу. Иначе Город Потерянных Кораблей некому будет чинить.";
			link.l1 = "Вот оно как!.. Ну что же, спасибо вам огромное, Орели. Полагаю, что мне нужно добраться до Механика и переговорить с ним.";
			link.l1.go = "SessilDead_7";
		break;
		case "SessilDead_7":
			dialog.text = "Ну, попробуйте. Я желаю вам удачи.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekMechanik";
			AddQuestRecord("ISS_MainLine", "32");
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
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Что именно вы ищете?",
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
			dialog.text = "С книппелями я могу вам помочь, хотя и не понимаю, зачем вам этот хлам.";
			link.l1 = "Нужен. Вы знаете, 100 штук этого хлама мне будет достаточно.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Ну хорошо, можете забирать.";
			link.l1 = "Вот дьявол, я сам"+ GetSexPhrase("","а") +" не дотащу! Вы не подскажете, кто может организовать доставку на барк 'Сан Габриэль'?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Попросите от моего имени Пабло Барадеса. Он должен помочь.";
			link.l1 = "Хорошо, обязательно так и поступлю. Спасибо!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.knippels = true;
			AddQuestRecord("ISS_MainLine", "51");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Вот как? Интересно... У вас действительно есть корабль?";
			link.l1 = "Да.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "И он в хорошем состоянии? Мы доплывем до Большой земли?";
			link.l1 = "Непременно.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Тогда я согласна.";
			link.l1 = "Хорошо. Сейчас как можно быстрей отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Я поняла вас. Все сделаю, как вы сказали.";
			link.l1 = "Прошу вас, быстрее...";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
