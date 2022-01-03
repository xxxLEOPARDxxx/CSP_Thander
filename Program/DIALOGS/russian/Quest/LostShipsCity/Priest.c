
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

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
					dialog.text = "Вознеси хвалу Господу нашему, Иисусу Христу, за спасение свое! Пока шторм не прошел...";
					link.l1 = "Возношу, падре, и благодарю за оказанную мне честь продлить еще свое жалкое существование на этой бренной земле... Меня зовут " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = "Вознесем хвалу Господу нашему!";
					link.l1 = "Возношу, падре, и благодарю за оказанную мне честь продлить еще свое жалкое существование на этой бренной земле... Меня зовут " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что тебе нужно, "+ GetSexPhrase("сын мой","дочь моя") +"?";
    			link.l1 = RandPhraseSimple("Я хочу пожертвовать приходу Города, святой отец.", "Хочу внести пожертвование в приход Города, падре.");
    			link.l1.go = "donation";
				link.l2 = "Падре, мне нужно найти одного гражданина. Не знаете, где он сейчас?";
				link.l2.go = "SeekCitizen";
				link.l3 = "Хочу задать вам вопрос, святой отец.";
				link.l3.go = "int_quests";
				квесты
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l4 = "Падре, могу я чем-нибудь помочь вашему приходу?";
					link.l4.go = "askCandles";
				}
				if (CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek" && CheckCharacterItem(pchar, "mineral3"))
				{
					link.l4 = "Падре, хочу отдать вам свечи.";
					link.l4.go = "takeCandles";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l8 = "Святой отец, я хочу спросить, нельзя ли мне приобрести у вас некоторые товары?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek")
				{
					link.l8 = "Святой отец, я хочу спросить, нельзя ли мне приобрести у вас некоторые товары?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "found")
				{
					link.l8 = "Святой отец, хочу просить у вас лекарства.";
					link.l8.go = "FSeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Святой отец, я имею к вам серьезное предложение.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = "Я вижу, "+ GetSexPhrase("сын мой","дочь моя") +", что душа твоя неспокойна. Ибо нельзя за несчастия свои вину возлагать на Господа...";
			Link.l1 = "Святой отец, вот, скажите мне одну простую вещь. За все удачные повороты в жизни мы благодарим Господа нашего, а за все несчастия обвинять его права не имеем. Как же это так, падре?";
			Link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", разве ты безгреш"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Нет человека без греха!";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Верно. Пастырь наш водит стадо свое посреди сетей многих. Скажи, ты соблюдаешь заповеди его?";
			link.l1 = "Гм, не сказал"+ GetSexPhrase("","а") +" бы...";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Так почему же ты обижен"+ GetSexPhrase("","а") +" на Господа, если говорит Он тебе: 'Делай так!', а ты не делаешь? Если просит: 'Не делай эдак!', а ты делаешь?\n"+
				"Паства Его подобна сынам малолетним, непокорным отцу: всякий мнит, что сам знает все и обо всем. Вознеси хвалу Господу за те благодеяния, что оказаны тебе!";
			link.l1 = "Вы правы, святой отец. Я благодарю Господа нашего за спасение мое.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Хорошо. И впредь не богохульствуй!";
			link.l1 = "Не буду, падре.";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи его, он нарушил Закон!");
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
			dialog.text = LinkRandPhrase("Убери оружие, "+ GetSexPhrase("сын мой","дочь моя") +". А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Убери оружие, не к лицу это "+ GetSexPhrase("серьезному мужчине","девушке") +"...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
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
				Link.l1 = "Понятно. Давайте я еще попробую назвать.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Спасибо, я лучше сам поищу.";
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
					dialog.text = GetFullName(sld) + ", ты о нем говоришь?";
					Link.l1 = "Да-да, точно, это он.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о нем. Давайте еще раз назову.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", ты о ней говоришь?";
					Link.l1 = "Ага, именно о ней.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о ней. Давайте я еще раз попробую назвать.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "Не хочу я больше ни о ком спрашивать. До свидания.";
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
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам, святой отец.", "Спасибо, падре!");
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
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам, святой отец.", "Спасибо, падре!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Внимательно тебя слушаю, "+ GetSexPhrase("сын мой","дочь моя") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Послушайте, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Скажите, падре, а вы сами как сюда попали?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Скажите, падре, вы давно здесь живете?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "Нет вопросов. Извините, святой отец...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Это Город Потерянных Кораблей. Я здесь единственный священнослужитель, и моя миссия заключается в том, чтобы наставлять граждан Города на путь истинный.";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Я следовал из Старого Света проповедовать Слово Божье на новом континенте среди язычников. Но Господь рассудил иначе...";
			link.l1 = "Вы тоже пережили крушение?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Увы, да. Пути Господни неисповедимы.";
			link.l1 = "Это верно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Нет, не очень давно.";
			link.l1 = "Понятно... А не знаете какого-нибудь старожила?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Мне все равно, когда сюда попадает прихожанин. Главное, что сейчас все граждане именно здесь, в моей пастве.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
		break;
		//Исповедь
		case "donation":
			dialog.Text = "Конечно, "+ GetSexPhrase("сын мой","дочь моя") +". Как много ты хочешь пожертвовать во искупление грехов твоих?";
			Link.l1 = "Простите, святой отец, я передумал"+ GetSexPhrase("","а") +". На мели...";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "К сожалению, немного. 100 пиастров.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 пиастров. Я думаю, этого хватит.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Мне везет с деньгами, поэтому я пожертвую 5000 пиастров.";
				Link.l4.go = "donation paid_5000";
			}
		break;

		case "No donation":
			dialog.Text = "Хм, прихожане Города не будут от этого в восторге...";
			Link.l1 = "Ну и ладно. Извините, святой отец, мне пора.";
			Link.l1.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "От лица прихожан Города благодарю тебя, "+ GetSexPhrase("сын мой","дочь моя") +".";
			Link.l1 = "Да не за что...";
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "От лица прихожан Города благодарю тебя, "+ GetSexPhrase("сын мой","дочь моя") +".";
			Link.l1 = "Да не за что...";
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "От лица прихожан Города благодарю тебя, "+ GetSexPhrase("сын мой","дочь моя") +", за щедрый дар.";
			Link.l1 = "Да не за что...";
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		//достать свечки
		case "askCandles":
			dialog.text = "Да, "+ GetSexPhrase("сын мой","дочь моя") +". Приход нуждается в свечах, а у нас в Городе что-то давно не был поступлений этого товара. Помоги мне, принеси 400 свечей.";
			link.l1 = "И где мне их взять?";
			link.l1.go = "askCandles_1";
		break;
		case "askCandles_1":
			dialog.text = "Если бы я знал, где взять, то сам бы и сходил за ними. Поищи, "+ GetSexPhrase("сын мой","дочь моя") +".";
			link.l1 = "Хм... Ну, хорошо, святой отец, буду искать...";
			link.l1.go = "askCandles_2";
		break;
		case "askCandles_2":
			dialog.text = "Ищи прилежно, "+ GetSexPhrase("сын мой","дочь моя") +", награда будет достойной.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", падре. Все будет сделано.";
			link.l1.go = "exit";
			npchar.quest.takeCandles = "seek";
			npchar.quest.takeCandles.Qty = 0; //кол-во свечей
			AddQuestRecord("ISS_takeCandles", "1");
		break;

		case "takeCandles":
			iTemp = GetCharacterItem(pchar, "mineral3");
			npchar.quest.takeCandles.Qty = sti(npchar.quest.takeCandles.Qty) + iTemp;
			DeleteAttribute(pchar, "items.mineral3");
			if (sti(npchar.quest.takeCandles.Qty) < 400)
			{
				dialog.text = "Ну, давай посмотрим. Сейчас ты принес"+ GetSexPhrase("","ла") +" " + FindRussianQtyString(iTemp) + " свечей. Всего ты принес"+ GetSexPhrase("","ла") +" " + FindRussianQtyString(sti(npchar.quest.takeCandles.Qty)) + " свечей. Тебе осталось принести еще " + FindRussianQtyString(400 - sti(npchar.quest.takeCandles.Qty)) + ".";
				link.l1 = "Понятно. Ну что ж, продолжу поиски, святой отец.";
				link.l1.go = "exit";
				AddQuestRecord("ISS_takeCandles", "2");
				AddQuestUserData("ISS_takeCandles", "iQty", 400 - sti(npchar.quest.takeCandles.Qty));
			}
			else
			{
				dialog.text = "Отлично, ты выполнил"+ GetSexPhrase("","а") +" поставленную задачу в полном объеме, "+ GetSexPhrase("сын мой","дочь моя") +". Теперь нам хватит свечей для церковных служб на долгое время.";
				link.l1 = "Я рад"+ GetSexPhrase("","а") +", что смог"+ GetSexPhrase("","ла") +" помочь приходу. Святой отец, а что там насчет награды за труды?";
				link.l1.go = "takeCandles_ok";
			}
		break;
		case "takeCandles_ok":
			dialog.text = "Да, конечно, как и обещал. Я думаю, ты сам"+ GetSexPhrase("","а") +" почувствуешь изменения в твоей жизни здесь. Иди, "+ GetSexPhrase("сын мой","дочь моя") +".";
			link.l1 = "Да, падре, спасибо вам. Хотя и непонятно, за что...";
			link.l1.go = "exit";
			bDisableFastReload = false;
			npchar.quest.takeCandles = "found";
			AddQuestRecord("ISS_takeCandles", "3");
			CloseQuestHeader("ISS_takeCandles");
		break;
		//поиск товаров на корвет не принеся свечи
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("О чем ты, "+ GetSexPhrase("сын мой","дочь моя") +"?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                ""+ GetSexPhrase("Сын мой","Дочь моя") +", хватит уже...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны ядра, книппеля, провиант, порох, оружие, лекарства...",
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Лекарства? У тебя что-то болит?";
			link.l1 = "Нет, святой отец... Мне нужны лекарства, много лекарств для людей.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Хм, лекарства у меня имеются. Только для начала окажи и мне услугу, "+ GetSexPhrase("сын мой","дочь моя") +". Я говорю о свечах.";
			link.l1 = "О свечах?";
			link.l1.go = "askCandles";
		break;
		//поиск товаров на корвет не принеся свечи
		case "FSeekGoods":
			dialog.text = NPCStringReactionRepeat("Как много?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                ""+ GetSexPhrase("Сын мой","Дочь моя") +", хватит уже...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("50 пачек, полагаю, будет достаточно.",
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FSeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FSeekGoods_1":
			dialog.text = "А зачем тебе, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Увы, святой отец, сказать пока не могу.";
			link.l1.go = "FSeekGoods_2";
		break;
		case "FSeekGoods_2":
			dialog.text = "Ну что же, я не любопытен, ибо это грех... Ты можешь забрать у меня необходимую тебе партию лекарств. Как-то ты помог"+ GetSexPhrase("","ла") +" мне, теперь я помогу тебе.";
			link.l1 = "Спасибо, падре! Может, это будет слишком, но вы не можете организовать доставку этих лекарств на 'Сан Габриэль'?";
			link.l1.go = "FSeekGoods_3";
		break;
		case "FSeekGoods_3":
			dialog.text = "Хорошо. Иди с миром, "+ GetSexPhrase("сын мой","дочь моя") +", прихожане все сделают.";
			link.l1 = "Спасибо вам огромное, святой отец!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_MEDICAMENT, 50);
			AddQuestRecord("ISS_MainLine", "47");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("В чем дело, "+ GetSexPhrase("сын мой","дочь моя") +"?",
				"Мы уже говорили об этом.",
				"Это уже обсуждено, второй раз повторяю, "+ GetSexPhrase("сын мой","дочь моя") +".",
                "Ох, "+ GetSexPhrase("сын мой","дочь моя") +", как"+ GetSexPhrase("ой","ая") +" же ты надоедлив"+ GetSexPhrase("ый","ая") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Я набираю команду на свой корабль и предлагаю вам присоединиться ко мне.",
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаете...",
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Хм, вот как?.. За предложение спасибо, но я не могу покинуть паству Города.";
			link.l1 = "Святой отец, от Города скоро ничего не останется.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "На все воля Господа, "+ GetSexPhrase("сын мой","дочь моя") +". Я остаюсь.";
			link.l1 = "Ну что же, как знаете, святой отец.";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
