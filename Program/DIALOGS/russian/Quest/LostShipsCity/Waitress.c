
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
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = "Я не желаю с тобой разговаривать! Ты напал"+ GetSexPhrase("","а") +" на граждан!!";
				link.l1 = "Как знаешь..."
				link.l1.go = "exit";
				break;
			}
			//после завала Хилла Брюннера
			if (pchar.questTemp.LSC == "barmenIsDead")
			{
				dialog.Text = "Ах, "+ GetSexPhrase("месье капитан","мадемуазель") +", вы уже знаете о нашем несчастье?";
				link.l4 = "О каком несчастье? Что случилось?";
				link.l4.go = "NB_1";
				pchar.questTemp.LSC = "barmenIsDeadYouKnow";
				break;
			}
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toArmo_BrunnerDead")
			{
				dialog.Text = "Ах, "+ GetSexPhrase("месье капитан","мадемуазель") +", какой кошмар! Какой ужас!!";
				link.l4 = "Да, Армо, я в курсе. Жаль Хилла, очень жаль...";
				link.l4.go = "NBB_1";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.Text = "Да-да, я знаю вас! Этот шторм погубил ваш корабль. Что ж, такова ваша судьба, и теперь она объединена с нашей! Мы все заключены на этом острове...";
					Link.l1 = "Да уж, успел"+ GetSexPhrase("","а") +" заметить...";
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.Text = "Да-да, я знаю вас! Это ваш корабль затонул тут последним. Что ж, такова ваша судьба, и теперь она объединена с нашей! Мы все заключены на этом острове...";
					Link.l1 = "Да уж, успел"+ GetSexPhrase("","а") +" заметить...";
					Link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что вы хотели, "+ GetSexPhrase("месье капитан","мадемуазель") +"?";
				Link.l1 = "Хочу задать тебе пару вопросов, " + npchar.name + ".";
				Link.l1.go = "int_quests";
				link.l10 = "Да так, ничего, собственно...";
				link.l10.go = "exit";
				//рассказываем ей о том, что, возможно, за убийством Хилла стоят касперы
				if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(pchar, "questTemp.LSC.Armo"))
				{
					link.l4 = "Послушай, Армо, у меня есть некоторые мысли по поводу смерти Хилла.";
					link.l4.go = "AboutCasper_1";
				}
				//наводка на первого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 0)
				{
					link.l4 = "Армо, есть какие-нибудь новости по первому свиданию?";
					link.l4.go = "Casper1";
				}
				//ждем втогого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Армо, хочу доложить тебе, что мое первое свидание прошло успешно...";
					link.l4.go = "WaitCasper1";
				}
				//наводка на второго
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Армо, есть какие-нибудь новости по второму свиданию?";
					link.l4.go = "Casper2";
				}
				//ждем третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Армо, второй готов.";
					link.l4.go = "WaitCasper2";
				}
				//наводка на третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Армо, есть какие-нибудь новости по третьему свиданию?";
					link.l4.go = "Casper3";
				}
                //опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 11 && npchar.name == "Armo")
				{
					link.l4 = "Армо, прошу прощения, но я, кажется, все-таки опоздал"+ GetSexPhrase("","а") +" к свиданию.";
					link.l4.go = "CasperLate";
				}
                //опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 15 && npchar.name == "Armo")
				{
					link.l4 = "Армо, тут такое дело получилось...";
					link.l4.go = "CasperAllFight";
				}
				if (pchar.questTemp.LSC == "seekMillionAndHalf" && npchar.name == "Армо" && !CheckAttribute(npchar, "quest.giveMoney"))
				{
					link.l4 = "Слушай, Армо, у меня тут проблемы финансовые...";
					link.l4.go = "askMoney";
				}
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toWaitress")
				{
					link.l5 = "Послушай, " + npchar.name + ", ты не помнишь тот вечер, когда Максим Тейлор выпивал у вас?";
					link.l5.go = "ELTHusb_SF";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Послушай, ты не знаешь, где можно раздобыть некоторые товары.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Слушай, есть серьезный разговор. Я набираю команду, чтобы уйти отсюда на корабле.";
					link.l8.go = "SeekCrew";
				}
			}
		break;
		case "FT_1":
			dialog.text = "Ну что же, давайте знакомиться. Меня зовут " + GetFullName(npchar) + ". А вас?";
			link.l1 = "Мое имя - " + GetFullName(pchar) + ". Я капитан... К-хе, бывш"+ GetSexPhrase("ий","ая") +" капитан...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Так вы капитан того корабля, что затонул?! Представляю, как вас мучает совесть за гибель своих людей. Ох, мне очень жаль, простите...";
			link.l1 = "Да без проблем, собственно...";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Я буду называть вас "+ GetSexPhrase("'месье капитанан'","просто 'мадемуазель'") +"! Вы не против?";
			link.l1 = "Не против, " + npchar.name + ". Называй как хочешь...";
			link.l1.go = "exit";
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Задавайте, капитан.";
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Здесь как-то неуютно, ты не находишь? Еще штормит тут у вас...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "А ты как сюда попала?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Ты не хочешь выбраться отсюда?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Послушай, а что за кланы у вас тут процветают? Я имею в виду 'нарвалов' и 'касперов'.";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Слушай, я пока никак не могу толком сориентироваться в Городе. Где бы мне раздобыть какую-нибудь карту, что-ли...";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l6 = "Послушай, " + npchar.name + ", ты что-нибудь знаешь о Лейтоне Декстере?";
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && npchar.name == "Армо")
			{
				link.l7 = "Я слышал"+ GetSexPhrase("","а") +", ты встречаешься в Томасом Бойлом.";
				link.l7.go = "ansewer_7";
			}
			link.l10 = "Ты знаешь, что-то я забыл"+ GetSexPhrase("","а") +", о чем хотел"+ GetSexPhrase("","а") +" спросить. Извини, что отвлек"+ GetSexPhrase("","ла") +"...";
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = "Штормит, да... Но вы же моря"+ GetSexPhrase("к","чка") +", вам не привыкать.";
			link.l1 = "Это да, но все же... мрачновато как-то.";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Не падайте духом, это бывает у всех, кто сюда попадает. Все образуется, главное не делать глупостей.";
			link.l1 = "Глупостей?";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "Не ссорьтесь с адмиралом, соблюдайте Закон - и все будет хорошо.";
			link.l1 = "Понятно... Спасибо за поддержку.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = "Так же, как и все здесь. Наш корабль затонул, я сумела выплыть. Вообще знаете, с кораблей, что идут на дно, очень мало народу выплывает. Тут какое-то течение странное, что ли... В общем, не знаю я, но факт, как говорится, налицо.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Хи-хи, все хотят выбраться отсюда. Только это невозможно.";
			link.l1 = "Ты уверена?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Да, к сожалению. Корабли приходят только сюда, отсюда никто уже не уплывает. А строить новые корабли запрещено Законом.";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Хм... Я вам скажу одну очень простую вещь, и, надеюсь, вы ее запомните как следует. Не лезьте к ним!!";
			link.l1 = "А в чем дело?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "Дело в том, что вас просто убьют. Раньше было такое не раз с новенькими, так не повторяйте ошибок предшественников. Мне очень неприятно будет видеть ваш плавающий за бортом труп.";
			link.l1 = "Спасибо, учту.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_5":
			dialog.text = "Карту? Есть такая у Эрика Йорста! Это хозяин магазина.";
			link.l1 = "А где находится магазин?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "На галеоне 'Эсмеральда', "+ GetSexPhrase("месье капитан","мадемуазель") +".";
			link.l1 = "Понял"+ GetSexPhrase("","а") +". Огромное тебе спасибо, " + npchar.name + ".";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = ""+ GetSexPhrase("Месье капитан","Мадемуазель") +", я ничего не знаю о Лейтоне Декстере. И знать не желаю.";
			link.l1 = "Хм, ну, извини...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_7":
			dialog.text = "Да, это так. А зачем вы спрашиваете, "+ GetSexPhrase("месье капитан","мадемуазель") +"?";
			link.l1 = "Да так, просто... Рад"+ GetSexPhrase("","а") +" за вас!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l7 = true;
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = "Хилла Брюннера убили!!";
			link.l1 = "Что?! Не может быть!..";
			link.l1.go = "NB_2";
		break;
		case "NB_2":
			dialog.text = "Да-да, именно так! Господи, я до сих пор не могу отойти от этого кошмара.";
			link.l1 = "Армо, расскажи мне, как это случилось.";
			link.l1.go = "NB_3";
		break;
		case "NBB_1":
			dialog.text = "Ах, боже мой, я проработала у него столько времени! Какой он был хороший человек!";
			link.l1 = "Да, это точно... Армо, расскажи мне, как это случилось.";
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = "Ох, ужас какой-то! Не могу вспоминать об этом без содрогания...";
			link.l1 = "Армо, я прошу тебя, соберись и расскажи мне, как все было.";
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = "Сейчас... К полуночи Хилл собрался в погреб. Когда он пробыл там больше двух часов, я пошла туда же поторопить его, так как клиентов нужно был обслуживать. И нашла его там...";
			link.l1 = "Он точно был мертв?";
			link.l1.go = "NB_5";
		break;
		case "NB_5":
			dialog.text = "Да, у него был раскроен череп. Ох, я не могу это вспоминать без слез...";
			link.l1 = "Слушай, а ты никого не видела рядом? Выходящим из погреба, например...";
			link.l1.go = "NB_6";
		break;
		case "NB_6":
			dialog.text = "Нет, никого.";
			link.l1 = "Тысяча чертей! Совершенно непонятно... Слушай, может, он что-нибудь тебе говорил перед смертью? Ну, вспомни детали какие-нибудь...";
			link.l1.go = "NB_7";
		break;
		case "NB_7":
			dialog.text = "Гм, не знаю, пригодится ли вам это, но он спросил меня, не знаю ли я кого-нибудь из граждан, кто жил здесь до него.";
			link.l1 = "И что ты ответила?";
			link.l1.go = "NB_8";
		break;
		case "NB_8":
			dialog.text = "Ответила, что не знаю. А потом он спросил, не слышала ли я в разговорах посетителей о каком-то механике...";
			link.l1 = "И что ты ответила?";
			link.l1.go = "NB_9";
		break;
		case "NB_9":
			dialog.text = "Что не слышала.";
			link.l1 = "Это действительно так?";
			link.l1.go = "NB_10";
		break;
		case "NB_10":
			dialog.text = "Ну конечно! С чего бы это мне врать своему шефу?!";
			link.l1 = "Да, действительно... Ну что же, спасибо тебе, Армо.";
			link.l1.go = "NB_11";
		break;
		case "NB_11":
			dialog.text = "За что?";
			link.l1 = "За то, что ты такая хорошая девушка.";
			link.l1.go = "NB_12";
		break;
		case "NB_12":
			dialog.text = "Хм... Вы знаете, "+ GetSexPhrase("месье капитан","мадемуазель") +", мне сейчас не до шуток.";
			link.l1 = "А я и не шучу... Ладно, Армо, не печалься. Жизнь такая штука - люди умирают...";
			link.l1.go = "NB_13";
		break;
		case "NB_13":
			dialog.text = "Хорошо, если своей смертью!.. "+ GetSexPhrase("Месье капитан","Мадемуазель") +", обещайте мне, что если вы что-нибудь узнаете об этом деле, то сообщите мне.";
			link.l1 = "Обещаю, Армо.";
			link.l1.go = "NB_14";
		break;
		case "NB_14":
			dialog.text = "Спасибо. Я бы очень хотела знать, кто это сделал. Это негодяй не имеет права жить!";
			link.l1 = "Да-да, я с тобой соглас"+ GetSexPhrase("ен","на") +"...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAdmiralBarmenDead";
			npchar.quest.meeting = "1";
			if (CheckAttribute(pchar, "questTemp.LSC.knowMechanic"))
			{
				AddQuestRecord("ISS_MainLine", "26");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("му","й"));
				DeleteAttribute(pchar, "questTemp.LSC.knowMechanic");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "25");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся","ась"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("му","ой"));
			}
		break;

		case "AboutCasper_1":
			dialog.text = "Говорите, "+ GetSexPhrase("месье капитан","мадемуазель") +".";
			link.l1 = "Похоже, что за этим стоит клан 'Каспер'.";
			link.l1.go = "AboutCasper_2";
		break;
		case "AboutCasper_2":
			dialog.text = "Вы уверены?";
			link.l1 = "Да, уверен"+ GetSexPhrase("","а") +". Я пош"+ GetSexPhrase("ел","ла") +" к адмиралу, задавал"+ GetSexPhrase("","а") +" ему вопросы относительно расследования убийства Хилла, хотел"+ GetSexPhrase("","а") +" помочь. В итоге, мне было сказано, чтобы я не лез"+ GetSexPhrase("","ла") +" в это дело. Прямо и откровенно.";
			link.l1.go = "AboutCasper_3";
		break;
		case "AboutCasper_3":
			dialog.text = "А при чем тут 'касперы'?";
			link.l1 = "Как оказалось, они тесно связаны с адмиралом. Очень тесно... И видимо адмирал теперь их прикрывает.";
			link.l1.go = "AboutCasper_4";
		break;
		case "AboutCasper_4":
			dialog.text = "Ясно... Я хочу отомстить за Хилла.";
			link.l1 = "Я собираюсь вступить с кланом 'Каспер' в борьбу.";
			link.l1.go = "AboutCasper_5";
		break;
		case "AboutCasper_5":
			dialog.text = "Вы собираетесь делать это од"+ GetSexPhrase("ин","на") +"?";
			link.l1 = "Ну да. Адмирал на этот раз помогать мне не будет.";
			link.l1.go = "AboutCasper_6";
		break;
		case "AboutCasper_6":
			dialog.text = "Они вас убьют. В этом нет никаких сомнений, "+ GetSexPhrase("месье капитан","мадемуазель") +".";
			link.l1 = "Ну, это мы еще посмотрим...";
			link.l1.go = "AboutCasper_7";
		break;
		case "AboutCasper_7":
			dialog.text = "Вот что, я знаю, чем смогу вам помочь. Дело в том, что я ношу на 'Сан Габриэль' еду для этих мерзавцев. Моих поклонников там - хоть отбавляй. Я буду назначать им свидания, а вы будете разбираться с ними один на один.";
			link.l1 = "Хо! Неплохо придумано...";
			link.l1.go = "AboutCasper_8";
		break;
		case "AboutCasper_8":
			dialog.text = "Где вам будет удобно проводить эти встречи?";
			link.l1 = "Хм, не знаю. Мне, собственно, все равно, где встречаться с "+ GetSexPhrase("мужчиной","врагом") +"...";
			link.l1.go = "AboutCasper_9";
		break;
		case "AboutCasper_9":
			dialog.text = "Хи-хи, хорошо сказано... Приходите сюда завтра, я скажу вам, на какое время назначено свидание.";
			link.l1 = "Хорошо, Армо. Спасибо тебе.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "33");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","ла"));
			pchar.questTemp.LSC.Armo = 0; //флаг на мочилово касперов. четные - готовность Армо, нечетные - флаг questAction
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//первый каспер
		case "Casper1":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "Сегодня, в полночь 'каспер' по имени Денис Хопфер будет добиваться моего расположения на квартердеке флейта 'Церес Смити'. Будте острожны, "+ GetSexPhrase("месье капитан","мадемуазель") +", если вы нападете на Хопфера слишком близко к 'Сан Габриэлю', то звуки драки могут услышать остальные бандиты, и тогда вам конец.";
				link.l1 = "Я понял"+ GetSexPhrase("","а") +", Армо.";
				link.l1.go = "Casper1_1";
			}
			else
			{
				dialog.text = "Пока нет, ждите.";
				link.l1 = "Понял"+ GetSexPhrase("","а") +".";
				link.l1.go = "exit";
			}
		break;
		case "Casper1_1":
			dialog.text = "Прошу вас не опаздывать на свидание, это будет неприлично с вашей стороны...";
			link.l1 = ""+ GetSexPhrase("Хе-хе, это верно. В полночь буду на месте как штык!","Да, приличные девушки не опаздывают. Буду вовремя, не сомневайся.") +"";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 1; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "34");
		break;

		case "WaitCasper1":
			dialog.text = "Отлично, "+ GetSexPhrase("месье капитан","мадемуазель") +". Ну, продолжим?";
			link.l1 = "Конечно, Армо!";
			link.l1.go = "WaitCasper1_1";
		break;
		case "WaitCasper1_1":
			dialog.text = "Тогда подходите завтра, возможно, я сумею вытащить еще кого-нибудь.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +" тебя.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//второй каспер
		case "Casper2":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "Да, есть. На том же месте, в тот же час, я назначила свидание 'касперу' по имени Серж Шамбон. Хлыщ еще тот, давно за мной увивается...";
				link.l1 = "Хе, недолго ему осталось досаждать тебе.";
				link.l1.go = "Casper2_1";
			}
			else
			{
				dialog.text = "Пока нет, "+ GetSexPhrase("месье капитан","мадемуазель") +". Ожидайте.";
				link.l1 = "Ясно.";
				link.l1.go = "exit";
			}
		break;
		case "Casper2_1":
			dialog.text = "Хорошо, это радует. Итак, "+ GetSexPhrase("месье капитан","мадемуазель") +", не опаздывайте на квартердек флейта 'Церес Смити'. Думаю, что не стоит разочаровывать Сержа.";
			link.l1 = "Ни в коем разе, Армо.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 3; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "37");
		break;

		case "WaitCasper2":
			dialog.text = "Очень хорошо, "+ GetSexPhrase("месье капитан","мадемуазель") +". Еще попробуем провернуть это дело?";
			link.l1 = "Если можно, Армо.";
			link.l1.go = "WaitCasper2_1";
		break;
		case "WaitCasper2_1":
			dialog.text = "Можно. Приходите завтра, надеюсь, я успею договорится еще с кем-нибудь.";
			link.l1 = "Хорошо, Армо. Спасибо тебе.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//третий каспер
		case "Casper3":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "Да, конечно. Там же, где и ранее, в то же время, меня будет поджидать Фелипе Армас. Мерзавец, каких свет не видывал.";
				link.l1 = "Ну, займемся и им...";
				link.l1.go = "Casper3_1";
			}
			else
			{
				dialog.text = "Пока нет, "+ GetSexPhrase("месье капитан","мадемуазель") +". Ожидайте.";
				link.l1 = "Ясно.";
				link.l1.go = "exit";
			}
		break;
		case "Casper3_1":
			dialog.text = "Прекрасно! Что ж, "+ GetSexPhrase("месье капитан","мадемуазель") +", удачи вам.";
			link.l1 = "Спасибо, она мне понадобится.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 5; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "38");
		break;
		//прерывания хода квеста Армо
		case "CasperLate":
			dialog.text = "Знаете, что, "+ GetSexPhrase("месье капитан","мадемуазель") +", я не для того рискую своей жизнью, чтобы вы так легкомысленно относились к своим обещаниям. Я не намерена более помогать вам. Извините.";
			link.l1 = "Эх, жаль...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 12; //Отмазала девка
			AddQuestRecord("ISS_MainLine", "35");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
		break;
		case "CasperAllFight":
			dialog.text = "Да, я знаю. На вас напал весь клан разом, наверное, услышали шум вашей схватки. Главное, что вы справились. Я рада за вас, "+ GetSexPhrase("месье капитан","мадемуазель") +".";
			link.l1 = "Спасибо, Армо.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 16; //чтобы диалога больше не было
		break;
		//Армо мертва
		case "ArmoIsDead":
			dialog.text = "Здравствуйте. Я вас знаю, вы "+ GetSexPhrase("тот самый новый гражданин, с которым","та самая новая гражданка, с которой") +" Армо была очень дружна.";
			link.l1 = "Да, это так.";
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = "Очень жаль, что Армо погибла. Никто не знает, кто ее убил. В таверне просто услышали ее крик наверху. Там, как назло, никого не было в этот момент. Когда на ее крик сбежался народ, она лежала с перерезанным горлом в луже собственной крови...";
			link.l1 = "Армо погибла из-за меня, это точно!";
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = "Ну, слезами горю не поможешь, как говорится... Знаете, в память об Армо, я буду назвать вас так же, как она - "+ GetSexPhrase("месье капитан","мадемуазель") +". Вы не против?";
			link.l1 = "Конечно, нет.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		//Если Армо жива, то дает денег
		case "askMoney":
			dialog.text = "Вам нужны деньги, "+ GetSexPhrase("месье капитан","мадемуазель") +"? А зачем?";
			link.l1 = "На одно очень нужное для всего Города дело. Вопрос жизни и смерти!";
			link.l1.go = "askMoney_1";
		break;
		case "askMoney_1":
			dialog.text = "Я верю вам, "+ GetSexPhrase("месье капитан","мадемуазель") +". Я могу вам отдать мои сбережения, тем более, что мне они ни к чему.";
			link.l1 = "Ты меня очень обяжешь, Армо.";
			link.l1.go = "askMoney_2";
		break;
		case "askMoney_2":
			dialog.text = "Сто тысяч - это все, что я могу предложить.";
			link.l1 = "Отлично!";
			link.l1.go = "askMoney_3";
		break;
		case "askMoney_3":
			dialog.text = "Тогда берите. И желаю вам удачи.";
			link.l1 = "Спасибо, Армо!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			npchar.quest.giveMoney = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("О каких товарах идет речь, "+ GetSexPhrase("месье капитан","мадемуазель") +"?",
				"Вы уже спрашивали об этом.",
				"Уже спрашивали...",
                "Вы уже спрашивали меня об этих товарах. Может хватит?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны бомбы, книппеля, провиант, порох, оружие, лекарства...",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Бомбы и прочее можно спросить у хозяек в кораблях. Если вы с ними не знакомы, то это Элис Тейлор, Орели Бертин, Леа Тоорс и Элиза Кальво. Об остальном понятия не имею.";
			link.l1 = "Ясно... Спасибо тебе.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "48");
			AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("И что?",
				"Мы уже поговорили об этом.",
				"Это уже обсуждено, второй раз повторяю.",
                "Хватит, утомили...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Я хочу пригласить тебя пойти ко мне в команду.",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаешь...",
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			if (npchar.name == "Армо")
			{
				dialog.text = "Нет, "+ GetSexPhrase("месье капитан","мадемуазель") +". Мы с Томасом остаемся в Городе.";
				link.l1 = "Да при чем тут твой Томас?! Оставаясь здесь, ты рискуешь жизнью.";
				link.l1.go = "SeekCrew_2";
			}
			else
			{
				dialog.text = "Нет, "+ GetSexPhrase("месье капитан","мадемуазель") +". Я останусь здесь, в своей таверне.";
				link.l1 = "Оставаясь здесь, ты рискуешь жизнью.";
				link.l1.go = "SeekCrew_2";
			}
		break;
		case "SeekCrew_2":
			dialog.text = "Почему?";
			link.l1 = "Надвигающийся шторм скорей всего разрушит Город.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Сколько уже этих штормов было, переживем и еще один.";
			link.l1 = "Зря... Ну, ладно, как знаешь.";
			link.l1.go = "exit";
		break;
		//освобождение мужа Элис Тейлор
		case "ELTHusb_SF":
			dialog.text = "Помню, "+ GetSexPhrase("месье капитан","мадемуазель") +".";
			link.l1 = "Расскажи пожалуйста, как все было.";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "Да, рассказывать-то особо и нечего. Тейлор просидел у нас часа три и ушел 'на бровях'. Впрочем, как всегда.";
			link.l1 = "Понятно... Один ушел?";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "С Жилем Бару под ручку.";
			link.l1 = "Подожди. Получается, что Жиль Бару провожал его домой?";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "Ну да.";
			link.l1 = "Ага! Спасибо тебе, дорогуша.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "8");
			pchar.questTemp.LSC.ElisHusband = "toZhilBaru";
		break;

	}
	NextDiag.PrevNode = NodeName;
}

