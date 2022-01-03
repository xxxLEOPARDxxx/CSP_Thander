// boal 25/04/04 общий диалог Usurer
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;

	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "First time":
			if(!CheckAttribute(npchar, "CapitolMoney")) npchar.CapitolMoney = 500000 + drand(30) * 50000;
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "Все, поторопитесь, " + pchar.name + ". А я здесь приберусь...";
					link.l1 = "Выхожу в море!";
					link.l1.go = "exit";
					break;
				}
				//работорговец

       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff"))
                {
                    dialog.text = "Добрый день, доктор Блад. Не хотите ли помочь мне в одном дельце? Разумеется, Вы получите щедрую премию.";
                    Link.l1 = "Интересно, что за дельце?";
    				Link.l1.go = "CapBloodUsurer_5";
                    break;
                }
                dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
                                    "Рад видеть вас, Питер Блад.",
                                    "Хорошо, что вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == false)//homo линейка Блада
                {
                    Link.l2 = "Я к вам по делу.";
    				Link.l2.go = "CapBloodUsurer_1";
                }
				break;
            }
			//пиратка, квест №5, заглушка на возврат бабла -->
			if (CheckAttribute(npchar, "PLQ5Money"))
			{
				dialog.text = "Вы принесли мне мои 50 тысяч?";
				link.l1 = "Нет еще, я этим занимаюсь. Ждите.";
				link.l1.go = "exit";
				link.l2 = "Боюсь, что у меня ничего не выйдет с этим делом. Считайте, что я отказал"+ GetSexPhrase("ся","ась") +".";
				link.l2.go = "StepPL5End_close";
				if (sti(pchar.money) >= 50000)
				{
					link.l3 = "Да, я забрал"+ GetSexPhrase("","а") +" ваши 50 тысяч и готов"+ GetSexPhrase("","а") +" их вам вернуть.";
					link.l3.go = "StepPL5End_1";
				}
				break;
			}
			//<--пиратка, квест №5, заглушка на возврат бабла

			//-->работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ну, наконец-то ко мне заглянул"+ GetSexPhrase(" достойный капитан","а достойная леди") +", а не эти скудоумные обыватели, которые думают, что я их пиастры высаживаю во внутреннем дворике банка и каждый месяц собираю урожай, чтоб выплачивать им проценты\nОни дрожат за каждый пенни, совершенно не подозревая, на какие ухищрения приходится идти бедному ростовщику, чтобы самому не умереть с голоду и еще дать им возможность купить гуся к рождеству.";
				Link.l1 = "Думаю, ваши вкладчики не обрадовались бы, услышав такие слова от человека, которому они доверяют свои сбережения.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}

			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Ну, старый хорек, сейчас тебе придется здорово постараться, чтобы объяснить мне все! На корабле в трюме вместо рабов меня поджидала целая рота солдат! Мне едва удалось справиться с ними! Я очень з"+ GetSexPhrase("ол","ла") +", так что поторопись с разъяснениями!";
				Link.l1.go = "Slaveshore_5";
				break;
			}
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "А-а-а, вот и вы, наконец! По всему архипелагу уже ходят слухи о вашем дерзком налете. Рад вас видеть!";
				Link.l1 = "Я бы предпоч"+ GetSexPhrase("ел","ла") +" безвестность такой славе... Уж очень она опасная.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Вы привезли пять тысяч рабов?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
				Link.l1 = "Да, привез"+ GetSexPhrase("","ла") +". Они у меня в трюмах.";
				Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Нет, я еще работаю над этим.";
					Link.l1.go = "exit";
				}
				break;
			}

			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Хм... Вы еще живы? Странно... Ну, думаю, это ненадолго. Солдаты! На помощь! Здесь бандит!";
				link.l1 = "Вот ведь гад!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}

			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Добрый день. Меня зовут " + GetFullName(npchar) + ". Чем могу быть вам полезен?";
				link.l1 = "О! А что вы тут делаете, уважаемый?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<--работорговец

			//-->> дача квеста найти потерянный драгоценный камень
			if (rand(1) && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.usurersJewel") && GetNpcQuestPastDayWOInit(npchar, "usurersJewel") > 7 && !CheckAttribute(pchar, "questTemp.different.SeekUsurersJewel") && npchar.city != "Charles" && !CheckAttribute(npchar, "quest.slave"))
			{
				dialog.text = "Здравствуйте, вы как нельзя вовремя! Хочу поручить вам одно дело.";
				link.l1 = "Внимательно слушаю. Что за дело?";
				link.l1.go = "usurersJewel_1";
				npchar.quest.usurersJewel = "inSeek"; //личный флаг ростовщика на взятый квест
				SaveCurrentNpcQuestDateParam(npchar, "usurersJewel");
				break;
			}
			//<<-- дача квеста найти потерянный драгоценный камень
			dialog.text = NPCStringReactionRepeat("Здравствуйте, " + GetAddress_Form(npchar) + ". Чем я могу вам помочь?",
				"О, это опять вы? Добро пожаловать, " + GetAddress_Form(npchar) + " Что вы хотите на этот раз?",
				"Хм, снова вы, " + GetAddress_Form(npchar) + "... Ну что же, рад вас видеть который уже раз за день. Что вы желаете?",
                "Эх, " + GetAddress_Form(npchar) + ", вы себе представить не можете, до чего порой бывают навязчивы клиенты... Что вам угодно?" , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ничем, я просто заш"+ GetSexPhrase("ел","ла") +" посмотреть и поговорить.",
				"Опять я. И опять просто так поговорить решил"+ GetSexPhrase("","а") +".",
                "Ага, снова я. И снова без конкретного дела заш"+ GetSexPhrase("ел","ла") +" поговорить.",
				"Да-а-а, тяжело приходится ростовщикам порой... А мне от вас ничего не нужно, просто поболтать хотел"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Я хочу обсудить наши финансовые взаимоотношения.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Мне нужна кое-какая информация... В общем, есть вопрос.";
			link.l3.go = "quests";//(перессылка в файл города)
			if (CheckAttribute(npchar, "quest.usurersJewel.type") && !CheckCharacterItem(pchar, "UsurersJew"))
			{
				link.l4 = "Пожалуй, я отказываюсь от поисков камня. Не думаю, что я смогу его разыскать.";
				link.l4.go = "jewelCancel";
			}

			//линейка ГПК, закладка миллиона на депозит
			if (CheckAttribute(pchar, "questTemp.LSC.usurerId") && pchar.questTemp.LSC.usurerId == npchar.id)
			{
				if (pchar.questTemp.LSC == "SignOnPoorMurder")
				{
					link.l4 = "Послушайте, вам должен был поступить депозит на мое имя.";
					link.l4.go = "ISS_deposit";
				}
				if (pchar.questTemp.LSC == "PoorMurderExecute")
				{
					link.l4 = "Мне необходимо снять депозит на миллион пиастров, что находится у вас.";
					link.l4.go = "ISS_takeDeposit";
					DeleteAttribute(pchar, "questTemp.LSC.usurerId");
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
				link.l7.go = "IntelligenceForAll";
			}
			//<<<<---------------- пиратка, квест №5. --------------------
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_1") && npchar.city == pchar.questTemp.piratesLine.Q5.city_1)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirstUsurer")
				{
					link.l5 = "Говорят, что вы Джона Эйвори нанимали.";
					link.l5.go = "StepPL5First_1";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst")
				{
					link.l5 = "Послушайте, не нанимали ли вы Джона Эйвори?";
					link.l5.go = "StepPL5First_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_2") && npchar.city == pchar.questTemp.piratesLine.Q5.city_2)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecondUsurer")
				{
					link.l5 = "Говорят, у вас были проблемы с Джоном Эйвори...";
					link.l5.go = "StepPL5Second_0";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond")
				{
					link.l5 = "Послушайте, не нанимали ли вы Джона Эйвори для выполнения поручений?";
					link.l5.go = "StepPL5Second_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_3") && npchar.city == pchar.questTemp.piratesLine.Q5.city_3)
			{
				if (pchar.questTemp.piratesLine == "PPL5Hunter_toThirdUsurer" || pchar.questTemp.piratesLine == "PPL5Hunter_toThird")
				{
					link.l5 = "Я ищу Джона Эйвори, к вам он не обращался?";
					link.l5.go = "StepPL5Third_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_4") && npchar.city == pchar.questTemp.piratesLine.Q5.city_4)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFourth")
				{
					link.l5 = "Я слышал"+ GetSexPhrase("","а") +", у вас случилось несчастье, возможно, вам понадобится помощь?";
					link.l5.go = "StepPL5Four_1";
				}
			}
			//-------------------- пиратка, квест №5. ---------------->>>>
			//-->> сдача квеста найти потерянный драгоценный камень
			if (CheckCharacterItem(pchar, "UsurersJew") && CheckAttribute(npchar, "quest.usurersJewel.type"))
			{
				link.l6 = "Я наш"+ GetSexPhrase("ел","ла") +" ваш " + npchar.quest.usurersJewel.type + ". Вот он.";
				link.l6.go = "usurersJewel_R1";
			}
			//<<-- сдача квеста найти потерянный драгоценный камень
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына.";
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Меня интересует, что представляет собой владелец этих документов.";
				link.l10.go = "ShipLetters_Usurer1";
			}
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Я по поводу вашего поручения о поставке рабов.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Здравствуйте, " + NPChar.name + ", я по поводу вашего поручения.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Здравствуйте, " + NPChar.name + ", я по поводу вашего поручения.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Здравствуйте, " + NPChar.name + ", я по поводу вашего поручения.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Я приш"+ GetSexPhrase("ел","ла") +", как мы и договаривались. Что там насчет работенки?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Как мы и договаривались, я приш"+ GetSexPhrase("ел","ла") +". Что там насчет работенки?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Как ваши дела? Есть новое задание?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Ваше задание выполнено. Мне удалось разыскать беглых рабов, хоть это было и непросто.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Я приш"+ GetSexPhrase("ел","ла") +", как мы и договаривались, за очередным выгодным дельцем.";
				link.l8.go = "Slaveshore";
				break;
			}

			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "У меня плохие новости, " + npchar.name + ". Мне не удалось захватить бригантину.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Послушай, " + npchar.name + ". Я настиг"+ GetSexPhrase("","ла") +" бригантину, но никаких бумаг не наш"+ GetSexPhrase("ел","ла") +". Ты уверен, что они там были?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "У меня хорошие новости, " + npchar.name + ". Мне удалось настичь бригантину и достать бумаги. Вот они.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Ну как, вы уже подготовили для меня новое дело?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", мне удалось перехватить ваш так называемый 'галеон'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", мне очень жаль, но я не смог"+ GetSexPhrase("","ла") +" захватить этот галеон.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Я приш"+ GetSexPhrase("ел","ла") +" за своими деньгами.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", твое задание выполнено. Мерзавец Гонтьер мертв, как и вся его команда.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", мне очень жаль, я упустил"+ GetSexPhrase("","а") +" Франсуа Гонтьера, хотя вел"+ GetSexPhrase("","а") +" его до самой Тортуги. Но там ему удалось скрыться на своем корвете прямо у меня из-под носа.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Ну, рассказывайте, что за горячее дело вы мне приготовили.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			//Капитул
			if(CheckAttribute(pchar, "SellCapitol"))
			{
				link.lCapitol = "У меня есть кое-что, что может вас заинтересовать. Взгляните на этот список.";
				link.lCapitol.go = "SellCapitol";
			}
			//Китайская реликвия
			if(CheckAttribute(pchar, "Whisper.UsurerId") && npchar.id == pchar.Whisper.UsurerId)
			{
				if (!CheckAttribute(pchar, "WhisperChSpokeToUsurer"))
				{
					link.lWhisper = "Добрый день. До меня дошли сведения, что в вашем распоряжении находится некий древний китайский меч. Это так?";
					link.lWhisper.go = "Whisper_china_relic";
				}
				else
				{
					if (sti(pchar.Items.topor_emperor)>0)
					{
						link.lWhisper = "Я принесла вам императорский топор.";
						link.lWhisper.go = "Whisper_china_relic_finish_topor";
					}
					if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3"))
					{
						link.lWhisper1 = "Я принесла вам три хрустальных черепа.";
						link.lWhisper1.go = "Whisper_china_relic_finish_sculma";
					}
					if(CheckAttribute(pchar, "SellCapitol"))
					{
						link.lCapitol = "Я нашла кое-что интересней, чем вещи, о которых вы меня просили. Взгляните на этот список.";
						link.lCapitol.go = "Whisper_china_relic_finish_capitol";
					}
				}
			}
			//Нежданное наследство
			if (CheckAttribute(PChar,"UnexpectedInheritance"))
            {
				if(!CheckAttribute(pchar, "UnexpectedInheritance_translator"))
				{
					link.lUnexpectedInheritance = "Не оказываете ли Вы услуги перевода? У меня есть занятный документ на латыни.";
					link.lUnexpectedInheritance.go = "UnexpectedInheritance_translate";
				}
				else
				{
					if(npchar.id == pchar.UnexpectedInheritance_translator && GetNpcQuestPastDayWOInit(npchar, "UnexpectedInheritance_translate") > 0 && sti(pchar.money) >= 1000)
					{
						link.lUnexpectedInheritance = "Не оказываете ли Вы услуги перевода? У меня есть занятный документ на латыни.";
						link.lUnexpectedInheritance.go = "UnexpectedInheritance_translate_end";
					}
				}
            }


			NextDiag.TempNode = "First time";
		break;

		//Нежданное наследство
		case "UnexpectedInheritance_translate":
			dialog.text = "Обычно нет, но за десять тысяч...";
			if(sti(pchar.money) >= 10000)
			{
				link.l1 = "Вот ваши деньги.";
				link.l1.go = "UnexpectedInheritance_translate_end";
			}
			link.l2 = "У вас какие-то неадекватные расценки. Я пожалуй пойду.";
			link.l2.go = "exit";

		break;

		case "UnexpectedInheritance_translate_end":
			dialog.text = "Посмотрим\nХм\nЭто не совсем латынь, это вульгарис. Минутку\nВот, держите.";
			link.l1 = "Благодарю.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			UnexpectedInheritanceTranslatePart(pchar.UnexpectedInheritance);
			DeleteAttribute(pchar, "UnexpectedInheritance_translator");
			DeleteAttribute(pchar, "UnexpectedInheritance");

		break;
		//Капитул
		case "SellCapitol":
			dialog.text = "Хм, и правда интересный списочек. Я готов отдать вам за эти вещи... "+npchar.CapitolMoney+". Что скажете?";
			link.l1 = "По рукам. Вы сможете всё это забрать на рифе Скелета. Вот координаты. Там безопасно, можете отправить туда корабль.";
			link.l1.go = "SellCapitol_1";
			link.l2 = "Маловато будет. Я поищу другого покупателя, без обид.";
			link.l2.go = "exit";
		break;
		case "SellCapitol_1":
			AddMoneyToCharacter(pchar, sti(npchar.CapitolMoney));
			DeleteAttribute(pchar, "SellCapitol");
			Log_Info("Вы выдали местонахождение Капитула");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("TheLastMass");
			dialog.text = "С вами приятно иметь дело. Я надеюсь вы не обманываете и всё правда окажется на месте. А не то...";
			link.l1 = "У меня нет желания встречаться с вашими знакомыми охотниками за головами. Уверяю вас, всё там. До свидания.";
			link.l1.go = "exit";
		break;
		//Виспер - Китайская реликвия
		case "Whisper_china_relic_finish_topor":
			dialog.text = "Ничего себе! Он выглядит даже более роскошно, чем я себе представлял. Боюсь представить, каким образом он у вас оказался.";
			pchar.Items.topor_emperor = sti(pchar.Items.topor_emperor)-1;
			if (pchar.equip.blade == "topor_emperor")
			{
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			}
			Log_Info("Вы отдали императорский топор");
			PlaySound("interface\important_item.wav");
			link.l1 = "И не нужно, лучше покажите наконец меч. ";
			link.l1.go = "Whisper_china_relic_finish";
		break;
		case "Whisper_china_relic_finish_sculma":
			dialog.text = "Вы и в самом деле их нашли?! Если честно, я даже не надеялся. ";
			TakeItemFromCharacter(pchar, "sculMa1");
			TakeItemFromCharacter(pchar, "sculMa2");
			TakeItemFromCharacter(pchar, "sculMa3");
			Log_Info("Вы отдали хрустальные черепа");
			PlaySound("interface\important_item.wav");
			link.l1 = "Теперь я я хочу увидеть меч.";
			link.l1.go = "Whisper_china_relic_finish";
		break;
		case "Whisper_china_relic_finish_capitol":
			DeleteAttribute(pchar, "SellCapitol");
			CloseQuestHeader("TheLastMass");
			dialog.text = "Хм, и правда интересный список. Я готов отдать вам за него меч. Где я смогу найти все эти вещи?";

			Log_Info("Вы выдали местонахождение Капитула");
			PlaySound("interface\important_item.wav");
			link.l1 = "На рифе Скелета. Вот координаты. Там безопасно, можете отправить туда корабль. Так что насчёт меча? Хотелось бы поскорей его увидеть.";
			link.l1.go = "Whisper_china_relic_finish";
		break;
		case "Whisper_china_relic_finish":
			DeleteAttribute(pchar, "WhisperChSpokeToUsurer");
			DeleteAttribute(pchar, "Whisper.UsurerId");
			pchar.Whisper.GiveChinaSword = true;
			CloseQuestHeader("WhisperChinamanRelic");
			GiveItem2Character(pchar, "blade_china");
			Log_Info("Вы получили китайский меч");
			PlaySound("interface\important_item.wav");
			dialog.text = "Конечно! Вот он, красавец. Я постарался сохранить его в хорошем состоянии, так что прошу, осторожней с ним.";
			link.l1 = "Не беспокойтесь, я передам его тому, кто будет беречь его как зеницу ока - настоящему владельцу. До свидания. ";
			link.l1.go = "exit";
		break;
		case "Whisper_china_relic":
			dialog.text = "Всё так. Судя по украшениям на клинке, он принадлежал известному и влиятельному роду. А почему вы в  нём заинтересованы?";
			link.l1 = "Сколько вы за него хотите? Я бы хотела его купить. ";
			link.l1.go = "Whisper_china_relic_1";
		break;
		case "Whisper_china_relic_1":
			dialog.text = "Купить? Прошу прощения, но я ничего из своей коллекции не продаю.";
			link.l1 = "Жаль. Тогда, быть может, вы были бы не прочь обменять его на какой-то другой предмет?";
			link.l1.go = "Whisper_china_relic_2";
		break;
		case "Whisper_china_relic_2":
			dialog.text = "Хм, а это можно. Я уже давно ищу императорский топор. Это золотой, инкрустированный драгоценностями символ власти. Говорят, на Карибах он точно есть у какого-то пирата\nЕщё, я бы хотел получить три хрустальных черепа тольтеков: белый, красный и синий. Если найдёте все три - с радостью обменяюсь с вами.";
			link.l1 = "Ясно. Есть какая-то зацепка, где эти предметы можно достать?";
			link.l1.go = "Whisper_china_relic_3";
		break;
		case "Whisper_china_relic_3":
			dialog.text = "Если бы я это знал, то ни о чем вас не просил бы. Но я не тороплю, приходите, когда найдёте. От меча в ближайшее время я избавляться не собираюсь.";
			pchar.WhisperChSpokeToUsurer = true;
			AddQuestRecord("WhisperChinamanRelic", "2");
			link.l1 = "Хорошо, будем искать. До свидания.";
			link.l1.go = "exit";
		break;
		//

		//<<<<----------генератор -"Судовые документы". ------
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Чтобы ознакомиться подробно со всеми бумагами нужно много времени, а мое время стоит дорого.";
			link.l1 = "Может быть " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " золотых компенсируют Ваши труды?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Воля Ваша. Прощайте!";
			link.l2.go = "exit";
		break;

		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть! Нет, впервые вижу это имя. Покажите бумаги в портовом управлении.";
				link.l1 = "Позвольте, но мы же договорились, что вы расскажете мне об этом капитане!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Ну что же ... Я знаю владельца этого корабля. Он пусть и не самый богатый, но весьма обеспеченный человек. ";
				dialog.text = s1 + "поговаривают, что он уже давно и успешно торгует контрабандой. Не это ли вы хотели услышать ?";
				link.l1 = "Вас послушать, так можно сделать вывод ....";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "М-да.... даже и не знаю, повезло ли Вам с находкой. ";
				dialog.text = s1 + "Документы оформлены на наш колониальный патрульный корабль, а его капитан известен своей принципиальностью и строгостью нравов.";
				link.l1 = "Патрульный? В ведении коменданта?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;

		case "ShipLetters_Usurer2_1":
			dialog.text = "Мы договорились, что я посмотрю эти бумаги, не более того. Не смею вас больше задерживать.";
			link.l1 = "Спасибо и на этом...";
			link.l1.go = "exit";
		break;

		case "ShipLetters_Usurer2_2":
			dialog.text = "Делать выводы Вам. Наш комендант давненько 'присматривается', Вы догадываетесь к кому? А тут есть не помеченные таможней накладные...";
			link.l1 = "Догадываюсь. Спасибо, милейший!";
			link.l1.go = "exit";
		break;

		case "ShipLetters_Usurer2_3":
			s1 = "Именно так. Кстати, на этого капитана имеют большой зуб местные контрабандисты. ";
			dialog.text = s1 + "Как я уже говорил, владелец этих бумаг весьма строг и не жалует нарушителей закона.";
			link.l1 = "Догадываюсь. Спасибо, милейший!";
			link.l1.go = "exit";
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привёз","та девушка, которая привезла") +" моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас, как могу. Примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = "Какая благодарность? за что благодарность? Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";
		break;

		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//<<<<---------------- пиратка, квест №5. --------------------
		case "StepPL5First_1":
			dialog.text = "Нанимал, и он прекрасно справился с моим поручением. Правда, хи-хи, говорят, в таверне он так напился, что перепутал местного пьянчужку с моим должником.";
			link.l1 = "А он не сказал, куда направился? Может, еще какому ростовщику помощь нужна?";
			link.l1.go = "StepPL5First_2";
		break;
		case "StepPL5First_2":
			dialog.text = "Вот этого не знаю, чужие проблемы меня не касаются.";
			link.l1 = "Это понятно, что не касаются. Но, может, вскользь что-то было?..";
			link.l1.go = "StepPL5First_3";
		break;
		case "StepPL5First_3":
			pchar.questTemp.piratesLine.Q5.city_2 = GetQuestNationsCity(SPAIN);
			dialog.text = "Да вроде бы собирался на север Мейна курс держать, к испанцам. А куда точно - не ведаю... Хотя подождите, что-то он говорил о " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Dat") + ". Но сами понимаете, что за достоверность не ручаюсь.";
			link.l1 = "Понял"+ GetSexPhrase("","а") +". Спасибо.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "4");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Acc"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_2) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecond";
		break;

		case "StepPL5Second_0":
			dialog.text = "Э-э-э, не то чтобы проблемы...";
			link.l1 = "Хм, так вы нанимали его?";
			link.l1.go = "StepPL5Second_1";
		break;
		case "StepPL5Second_1":
			dialog.text = "Нанимал. Работу он выполнил, долг вернул сполна. Только в таверне стал болтать языком, что, якобы, выбил у должника сумму, многократно превышающую сумму долга, и как провел меня, умолчав об этом.\n"+
				"Лично мне, совершенно не понятно, где здесь обман, и почему этот рассказ, всех ужасно веселит?! Немного обидно, конечно, знал бы я раньше, что должник обладает такой суммой...\n"+
				"В общем, я вздохнул с облегчением, когда Джон Эйвори куда-то уплыл из нашего города. И теперь, слышать о нем не желаю!";
			link.l1 = "Ясно. А куда он направился, вы, конечно, не в курсе...";
			link.l1.go = "StepPL5Second_2";
		break;
		case "StepPL5Second_2":
			pchar.questTemp.piratesLine.Q5.city_3 = GetQuestNationsCity(FRANCE);
			dialog.text = "Думаю, к французам подался этот паршивец. Довелось краем уха услышать его разговор в борделе. Туда я заходил по делам, не по прямому назначению этого заведения...";
			link.l1 = "Уважаемый, мне все равно, что вы там делали. Спасибо вам за информацию об Эйвори.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "6");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_3) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toThird";
		break;

		case "StepPL5Third_1":
			dialog.text = "Джон периодически выполняет мои заказы, вот совсем недавно выполнил еще один...";
			link.l1 = "А где он может сейчас находиться?";
			link.l1.go = "StepPL5Third_2";
		break;
		case "StepPL5Third_2":
			dialog.text = "Это одному Богу только известно. Понимаете, как исполнитель Джон хорош, но уж очень он вспыльчивый. Давеча в таверне, прости господи душу грешную, человека зарезал. Поэтому я лишних вопросов Джону не задаю...";
			link.l1 = "Понятно... Но, может быть, есть хоть какие-то соображения, куда он мог отправиться?";
			link.l1.go = "StepPL5Third_3";
		break;
		case "StepPL5Third_3":
			pchar.questTemp.piratesLine.Q5.city_4 = GetQuestNationsCity(Holland);
			dialog.text = "Если вас интересует мое мнение, то думаю, что он отправился в " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4) + ".";
			link.l1 = "Хм... А причины данного умозаключения я могу услышать?";
			link.l1.go = "StepPL5Third_4";
		break;
		case "StepPL5Third_4":
			dialog.text = "Конечно. Видите ли, дело в том, что в " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Dat") + " недавно был ограблен ростовщик.";
			link.l1 = "А-а-а, я вас понял"+ GetSexPhrase("","а") +"! Спасибо огромное.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "8");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_4) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFourth";
		break;

		case "StepPL5Four_1":
			dialog.text = "Нет, нет, спасибо. Помощь уже не нужна, я только вчера нанял Джона Эйвори, он лучший в этом деле! О, не обижайтесь, вы тоже од"+ GetSexPhrase("ин","на") +" из лучших, просто Эйвори зашел ко мне раньше вас... Э-э-э, простите, как вы сказали, вас зовут?";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "StepPL5Four_2";
		break;
		case "StepPL5Four_2":
			dialog.text = "Да, да, я о вас слышал... кажется... Так о чем я рассказывал? А да, представляете, врывается эдакая образина, приставляет нож к горлу, и начинает меня грабить! Меня!!! Уважаемого человека, посреди бела дня...";
			link.l1 = "Простите, что перебиваю, но вы это, сейчас, о ком?";
			link.l1.go = "StepPL5Four_3";
		break;
		case "StepPL5Four_3":
			dialog.text = "...сколько денег пропало. Как о ком?! О грабителе, конечно! Ах, мои деньги! Ну, ничего, Джон Эйвори ему покажет! Эйвори - это сила! Мощь!.. Он имел наглость бахвалиться, что мол, руки у меня коротки, его на Бермудах достать...";
			link.l1 = "Кто? Эйвори?!";
			link.l1.go = "StepPL5Four_4";
		break;
		case "StepPL5Four_4":
			dialog.text = "Да, причем здесь Эйвори? Грабитель, конечно! Слушайте, что вы меня все время перебиваете?!";
			link.l1 = "Извините. А если я принесу вам награбленное? Вас это не сильно огорчит?";
			link.l1.go = "StepPL5Four_5";
		break;
		case "StepPL5Four_5":
			dialog.text = "Э-э-э... Ну... Мне, в принципе, все равно, кто деньги вернет, но с Эйвори вы разбирайтесь сами. Меня ваши с ним дела не касаются.";
			link.l1 = "Никаких проблем. Наши с Джоном дела вас не затронут. Так о какой сумме идет речь?";
			link.l1.go = "StepPL5Four_6";
		break;
		case "StepPL5Four_6":
			dialog.text = "Пятьдесят тысяч! Если вы мне все это принесете, ваша награда составит пять тысяч.";
			link.l1 = "Как звали грабителя?";
			link.l1.go = "StepPL5Four_7";
		break;
		case "StepPL5Four_7":
			dialog.text = "Вы думаете, он мне представился?! Где вы видели таких вежливых грабителей? Между прочим, Джон подобных вопросов не задавал.";
			link.l1 = "Хорошо. По рукам! Ждите меня, я скоро!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "9");
			pchar.questTemp.piratesLine = "PL5Hunter_toBermudes";
			npchar.PLQ5Money = true; //метка на ростовщика, которому должен бабла
			//здесь ставим прерывание на вход в дом Орри на Бермудах
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1 = "location";
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1.location = "Pirates_houseS1";
            Pchar.quest.PQ5_inOrryHouse.function = "PQ5_inOrryHouse";
		break;

		case "StepPL5End_close":
			dialog.text = "Плохо, я вами очень разочарован. Мне кажется, что вы что-то недоговариваете... Ну да ладно.";
			link.l1 = "Вот именно! Все нормально, приятель.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "PLQ5Money");
    		ChangeCharacterReputation(pchar, -50);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -20);
		break;

		case "StepPL5End_1":
			dialog.text = "Черт побери, я рад! Скажите, а что случилось с тем мерзавцем, который ограбил меня?";
			link.l1 = "Он получил по заслугам, больше он вас не побеспокоит...";
			link.l1.go = "StepPL5End_2";
		break;
		case "StepPL5End_2":
			dialog.text = "Великолепно, ну что же, я готов посчитать мои деньги. Давайте начнем...";
			link.l1 = "Извольте получить.";
			link.l1.go = "StepPL5End_3";
		break;
		case "StepPL5End_3":
			dialog.text = "Отлично! Просто превосходно! Все в порядке. Вот ваши 5 тысяч, как и договаривались.";
			link.l1 = "Спасибо...";
			link.l1.go = "StepPL5End_4";
			DeleteAttribute(npchar, "PLQ5Money");
			AddMoneyToCharacter(pchar, -45000);
    		ChangeCharacterReputation(pchar, 10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
		break;
		case "StepPL5End_4":
			dialog.text = "Ну что же, я всегда рад вас видеть у себя. И хочу вам сказать, что всем расскажу о вашей исполнительности и честности. Наглец Эйвори вам не чета, вы однозначно лучш"+ GetSexPhrase("ий","ая") +"...";
			link.l1 = "Прямо в краску вгоняете... Ну ладно, прощайте.";
			link.l1.go = "exit";
		break;
		//-------------------- пиратка, квест №5. ---------------->>>>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			dialog.text = "Давайте обсудим. Внимательно вас слушаю.";
			link.l1 = "Есть ли у вас дело, требующее сторонней помощи?";
			link.l1.go = "Loan_GiveWork";
			if (!CheckAttribute(NPChar,"StorageOpen"))
			{
				link.l11 = "Могу ли я арендовать у вас ячейку для хранения личных вещей?";
				link.l11.go = "PersonalStorage";
			}
			else
			{
				link.l11 = "Откройте мою ячейку хранилища.";
				link.l11.go = "PersonalStorage_Open";
			}
			//найти должника
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
            {
                link.l2 = "Я по поводу задания о должнике.";
                link.l2.go = "FindCitizen_1";
            }
			//доставить сундук
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
            {
                link.l3 = "Я по поводу задания о доставке кредита.";
                link.l3.go = "TakeChest_1";
            }
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l4 = "Я привез"+ GetSexPhrase("","ла") +" ваш кредит.";
                link.l4.go = "TakeChest_2";
            }
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Я долж"+ GetSexPhrase("ен","на") +" вам "+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(". Я готов"+ GetSexPhrase("","а") +" вернуть долг.", ". В данный момент я в состоянии выплатить вам долг.", ". Настало время, наконец, рассчитаться.");
					Link.l5.go = "loan_return";
					sTemp = "credit";
				}
			}
			else
			{
				Link.l6 = LinkRandPhrase("Я хочу занять денег.", "Мне срочно понадобилась пара-другая пиастров.", "Как насчет небольшого кредита?");
				Link.l6.go = "loan";
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Я бы хотел"+ GetSexPhrase("","а") +" отдать деньги в рост.","Примете на хранение пиратскую добычу?", "Золотишко на черный день оставить можно?");
					Link.l7.go = "deposit";
				}
			}
			if(CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(NPC_Area).StartYear),makeint(Pchar.Quest.Deposits.(NPC_Area).StartMonth),makeint(Pchar.Quest.Deposits.(NPC_Area).StartDay), makefloat(Pchar.Quest.Deposits.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Deposits.(NPC_Area).Result = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Deposits.(NPC_Area).Interest))*iPastMonths;
				Link.l8 = LinkRandPhrase("Я хочу забрать свой вклад.", "Пришло время забрать мои деньги, что у вас хранятся.", "Мне нужно мое золото и набежавшие проценты.");
				Link.l8.go = "Deposit_return";
			}
			//выход
			if (sTemp == "credit")
			{
				link.l9 = LinkRandPhrase("Я помню, что брал"+ GetSexPhrase("","а") +" у вас кредит, но рассчитатся пока не готов"+ GetSexPhrase("","а") +"...", "Я знаю, что долж"+ GetSexPhrase("ен","на") +" вам, но сейчас у меня нет денег. Верну позже...", "Я помню, что долж"+ GetSexPhrase("ен","на") +" вам, но в данный момент не имею достаточных средств для погашения кредита. Я сделаю это позже.");
				link.l9.go = "Loan_Remind";
			}
			else
			{
				link.l9 = "Я ошиб"+ GetSexPhrase("ся","лась") +", никаких финансовых дел у меня с вами нет. Прощайте.";
				link.l9.go = "exit";
			}
		break;
		//Ветка для персонального хранилища
		case "PersonalStorage":
			dialog.text = "Да, я предоставляю такую услугу своим клиентам. Могу дать гарантию, что из моих хранилищ никогда ничего не пропадёт. Стоимость услуги - 10000 пиастров единовременно, а после 1500 за каждый последующий месяц. Охрана - дело хлопотное и дорогое, сами понимаете. Желаете оформить?";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Разумеется, вот ваши деньги.";
				link.l1.go = "PersonalStorage_2";
			}
			link.l2 = "Пожалуй, как нибудь в другой раз...";
			link.l2.go = "exit";
		break;
		case "PersonalStorage_2":
			AddMoneyToCharacter(Pchar, -10000);
			NPChar.StorageOpen = "Opened";
			NPChar.StoragePrice = 1500;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			DeleteAttribute(NPChar,"items");
			dialog.text = "Что-ж, всё оплачено, прошу к ячейке.";
			link.l1 = "(Открыть ячейку)";
			link.l1.go = "PersonalStorage_Open_2";
		break;
		case "PersonalStorage_Open":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.StoragePrice);
			if(sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "С вас за аренду ячейки еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Хорошо, сейчас оплачу аренду.";
					link.l1.go = "PersonalStorage_Open_1";
				}
				else
				{
					link.l1 = "Я зайду попозже.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "... Всё в порядке, можете проходить к хранилищу.";
				link.l1 = "(Открыть ячейку)";
				link.l1.go = "PersonalStorage_Open_2";
			}
			link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit";
		break;
		case "PersonalStorage_Open_1":
			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForStorage));
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			dialog.text = "... Всё в порядке, можете проходить к хранилищу.";
			link.l1 = "(Открыть ячейку)";
			link.l1.go = "PersonalStorage_Open_2";
		break;
		case "PersonalStorage_Open_2":
			DialogExit();
			LaunchItemsBox(npchar);
		break;
		//=============================  даем или не даем работу - сундуки и должники
		case "Loan_GiveWork":
            // проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "Ты ведь " + GetFullName(pchar)+ ", не так ли? О тебе " +
                              RandPhraseSimple("ходят ужасные слухи","говорят не лучшим образом") + ", я не хочу иметь с тобой дело.";
				link.l1 = RandPhraseSimple("Эх... Стоит человеку оступиться, и все будут в него плевать.", RandSwear() + "Ну и не надо!");
				link.l1.go = "exit";
                break;
            }
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//при низком авторитете не даем
			{
            dialog.text = "Нет, к счастью, у меня все хорошо.";
			link.l9 = "Извините, мне пора.";
		    link.l9.go = "exit";
			break;
			}
            // проверка на проф пригодность <--
            dialog.text = "Нет, к счастью, у меня все хорошо.";

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
                npchar.quest.trade_date = lastspeak_date;
                iNum = rand(1);
                if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
                {
                    iNum = 0; // всегда первый
                }
                switch (iNum)
                {
                    case 0 : // найти должника
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;

                        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
                        {
                            iNum = findCitizenMan(Npchar, true);
                            npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // знатичит на суше без корабля
                        }
                        else
                        {
                            iNum = findCitizenMan(Npchar, false);
                        }
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.Loan.FindCitizenMoney   = (7 + cRand(sti(PChar.rank)))*1000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*200 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
                            pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3+rand(2)));
                            pchar.GenQuest.Loan.FindCitizenIdx  =  iNum;
							pchar.GenQuest.Loan.FindCitizenChance1 = rand(2);
							pchar.GenQuest.Loan.FindCitizenChance2 = rand(1);
							pchar.GenQuest.Loan.FindCitizenChance3 = rand(1);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = ", что на " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = "Да, вы вовремя. Есть у меня щекотливый вопрос, требующий решения. "+
                                     GetFullName(chr) + ", живущий в " + XI_ConvertString("Colony"+chr.city+"Dat") + sTemp + ", задолжал мне " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)) +
                                     ". Если вы вернете мне всю сумму, то набежавшие проценты можете оставить себе. Они, кстати, составляют " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)) + ".";
                            link.l1 = "Я берусь!";
                			link.l1.go = "LoanUsurer_GiveWork_1";
            			}
                    break;

                    case 1: // доставить сундуки
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;

                        iNum = findChestMan(Npchar);
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.LoanChest.Chest      = 2 + drand(2);
                            pchar.GenQuest.LoanChest.Money      = (3 + cRand(sti(pchar.GenQuest.LoanChest.Chest)))*400 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*250;
                            pchar.GenQuest.LoanChest.TargetIdx  =  iNum;
                            pchar.GenQuest.LoanChest.Time       = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = ", что на " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = "Мне нужен проверенный человек для важной миссии. Нужно доставить кредит - " + pchar.GenQuest.LoanChest.Chest +
									" сундука с золотом в "+ XI_ConvertString("Colony"+chr.city+"Acc") + sTemp + " для человека по имени " +
									GetFullName(chr) + ". Он местный " + GetWorkTypeOfMan(chr, "") +
									". За работу получите " + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)) + ". Это нужно сделать за " + FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)) + ".";
                            link.l1 = "Я готов"+ GetSexPhrase("","а") +"!";
                			link.l1.go = "LoanUsurer_ChestWork_1";
            			}
                     break;
    			}
    		}
            else
            {
                dialog.text = "Я вам уже все сказал.";
            }
            link.l9 = "Извините, мне пора.";
		    link.l9.go = "exit";
		break;
		//============== boal нахождение должника ===============
		case "LoanUsurer_GiveWork_1":
            pchar.GenQuest.Loan.FindCitizen = true;
            pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
            dialog.text = "Замечательно. Жду вас как можно скорее.";
			link.l9 = "Не подведу!";
			link.l9.go = "exit";
            chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = ", что на " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
            AddQuestRecord("Gen_LoanFindCitizen", "1");
            AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
            AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony"+chr.city+"Dat") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //проверка выполнения квеста
            dialog.text = "Я весь внимание.";
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
            {
                link.l1 = "Ваше поручение выполнено!";
                link.l1.go = "finish_work";
                link.l2 = "Мне удалось найти должника, но не удалось выбить из него денег.";
                //if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
               // {
                //    link.l2.go = "finish_work_bad";
                //}
               // else
               // {
                    link.l2.go = "finish_work_lie";
              //  }
            }

            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                link.l1 = "Мне удалось найти должника, но не удалось выбить из него денег.";
                link.l1.go = "finish_work_bad";
            }
            link.l3 = "Я решил"+ GetSexPhrase("","а") +" аннулировать ваш заказ по поиску должника - это не для меня.";
            link.l3.go = "finish_work_cancel";
            //link.l9 = "Нет. Ничего.";
			//link.l9.go = "exit";
		break;

		case "finish_work":
            if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
            {
                dialog.text = "Вот и славно!";
    			link.l9 = "Пожалуйста!";
    			link.l9.go = "exit";
    			AddMoneyToCharacter(Pchar, -1*sti(pchar.GenQuest.Loan.FindCitizenMoney));
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
    			ChangeCharacterReputation(pchar, 1);
    			OfficersReaction("good");
    			AddQuestRecord("Gen_LoanFindCitizen", "4");
                CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
			    dialog.text = "Замечательно! Но где мои деньги? Время-то идет.";
    			link.l9 = "Скоро будут!";
    			link.l9.go = "exit";
    		}
		break;

		case "finish_work_bad":
            dialog.text = "Очень и очень плохо! Вы не в состоянии делать свою работу!";
			link.l9 = "Этот человек правда был не состоятелен, но вы правы - это моя работа.";
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
			AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("ся","ась"));
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		case "finish_work_cancel":
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                dialog.text = "А мне сдается, вы меня обманываете! Я точно знаю, что вы с ним говорили. Верните мои деньги!";
                link.l1 = "Да, вы правы, вот деньги.";
    			link.l1.go = "finish_work";
    			link.l2 = "Но он отказался платить!";
    			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
    			   link.l2.go = "finish_work_bad";
    			}
    			else
    			{
    			   link.l2.go = "finish_work_bad_2";
    			}
    			//link.l9 = "Мне сейчас некогда. Я зайду позже.";
    			//link.l9.go = "exit";
    			//ChangeCharacterReputation(pchar, -1);
			}
            else
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = "Плохо, я уже рассчитывал на вас.";
                link.l1 = "Да, вы правы, но такова жизнь.";
    			link.l1.go = "exit";
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddQuestRecord("Gen_LoanFindCitizen", "6");
				AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("ся","ась"));
                CloseQuestHeader("Gen_LoanFindCitizen");
            }
		break;

		case "finish_work_bad_2":
			ChangeCharacterReputation(pchar, -3);
            dialog.text = "Вы уже показали, что склонны ко лжи. Верните мои деньги!";
			link.l1 = "Да говорю же - нет у меня денег!";
    		link.l1.go = "finish_work_hanter";
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
            link.l2 = "Да, вы правы, вот деньги.";
    		link.l2.go = "finish_work";
			}
		break;

		case "finish_work_lie":
            dialog.text = "Хм, точно?";
            link.l1 = "Конечно!";
    		link.l1.go = "finish_work_cancel";
		break;

		case "finish_work_hanter":
            dialog.text = "Ах вот как? И вы думаете, что я это вот так оставлю? У вас будут крупные неприятности, которые обойдутся вам много дороже этих денег, я вам обещаю. Убирайтесь!";
            link.l1 = "Не напугаете. Счастливо оставаться!";
    		link.l1.go = "exit";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 40);
			DeleteAttribute(pchar, "GenQuest.Loan");
    		DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    		AddQuestRecord("Gen_LoanFindCitizen", "7");
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		//============== boal доставка сундуков ===============
		case "LoanUsurer_ChestWork_1":
            pchar.GenQuest.LoanChest.TakeChest = true;
            pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
            dialog.text = "Я на вас очень рассчитываю.";
			link.l9 = "Не подведу!";
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// немного веселой жизни
            TraderHunterOnMap();
            chr  = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = ", что на " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
            AddQuestRecord("Gen_LoanTakeChest", "1");
            AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", pchar.GenQuest.LoanChest.Chest);
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony"+chr.city+"Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
            dialog.text = "Я весь внимание.";
            link.l1 = "Я решил"+ GetSexPhrase("","а") +" аннулировать ваш заказ по доставке кредита - это не для меня.";
            link.l1.go = "TakeChestFinish_work_cancel";
            link.l9 = "Нет. Ничего.";
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = "Плохо, я уже рассчитывал на вас.";
                link.l1 = "Да, вы правы, но такова жизнь.";
    			link.l1.go = "exit";
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
                AddQuestRecord("Gen_LoanTakeChest", "5");
				AddQuestUserData("Gen_LoanTakeChest", "sSex", GetSexPhrase("ся","ась"));
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                dialog.text = "Возможно, я готов прервать выполнение вашей миссии, если вы ВЕРНЕТЕ мне все сундуки.";
                link.l1 = "Зайду позже.";
    			link.l1.go = "Exit";
			}
		break;
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Нет, ничем не могу помочь. В нашем неспокойном месте я могу предложить только услуги хранения денег.";
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Хорошо, давайте определимся с суммой.";
	                Link.l1.go = "deposit";
				}
                Link.l2 = "Мне это не интересно.";
				link.l2.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "Ты ведь " + GetFullName(pchar)+ ", не так ли? О тебе " +
                              RandPhraseSimple("ходят ужасные слухи","говорят не лучшим образом") + ", я не хочу иметь с тобой дело.";
				link.l1 = RandPhraseSimple("Эх.. стоит человеку оступиться, и все будут в него плевать.", RandSwear() + "Ну и не надо!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "О, всегда пожалуйста. Какая сумма вам необходима?";
			Link.l1 = "Мне нужен краткосрочный кредит на небольшую сумму";
			Link.l1.go = "Small";
			Link.l2 = "Хочу приличную сумму на средний срок";
			Link.l2.go = "Medium";
			Link.l3 = "Мне нужен долгосрочный кредит на весьма значительную сумму.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 5000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Отлично. С небольшими суммами всегда проще - меньше риска. Я могу предложить вам " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest_1";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			//Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 10000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Не проблема. Надеюсь, что " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " помогут вам решить ваши проблемы. Это вполне значительная сумма.";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest_2";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 20000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "М-да... Рискованно... Но ладно, я готов предоставить вам заем на сумму в " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". Как вы понимаете, капитан, это действительно крупные деньги. Очень прошу вас серьезно отнестись к этому делу.";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest_3";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Interest_1":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " процентов в месяц. Основываясь на том, что я о вас знаю, я не могу предложить вам сейчас лучших условий.";
			Link.l1 = "Меня это вполне устраивает. Осталось обговорить срок.";
			Link.l1.go = "Period_1";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest_2":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " процентов в месяц. Основываясь на том, что я о вас знаю, я не могу предложить вам сейчас лучших условий.";
			Link.l1 = "Меня это вполне устраивает. Осталось обговорить срок.";
			Link.l1.go = "Period_2";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest_3":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " процентов в месяц. Основываясь на том, что я о вас знаю, я не могу предложить вам сейчас лучших условий.";
			Link.l1 = "Меня это вполне устраивает. Осталось обговорить срок.";
			Link.l1.go = "Period_3";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_1":
			Pchar.Quest.Loans.(NPC_Area).Period = 3;
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Учитывая то, что я о вас слышал, " + Pchar.name + ", я буду ждать возврата этого кредита " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". После чего, как вы понимаете, я приму меры.";
			Link.l1 = "Что же, я с удовольствием принимаю ваши условия... И ваши деньги.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Увы, мы с вами не договорились. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_2":
			Pchar.Quest.Loans.(NPC_Area).Period = 6;
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Учитывая то, что я о вас слышал, " + Pchar.name + ", я буду ждать возврата этого кредита " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". После чего, как вы понимаете, я приму меры.";
			Link.l1 = "Что же, я с удовольствием принимаю ваши условия... И ваши деньги.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Увы, мы с вами не договорились. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_3":
			Pchar.Quest.Loans.(NPC_Area).Period = 12;
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Учитывая то, что я о вас слышал, " + Pchar.name + ", я буду ждать возврата этого кредита " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". После чего, как вы понимаете, я приму меры.";
			Link.l1 = "Что же, я с удовольствием принимаю ваши условия... И ваши деньги.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Увы, мы с вами не договорились. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Искренне этому рад. Но позвольте мне вас предупредить. Я давно занимаюсь своим делом и знаю, как вернуть вложенные средства. Так что если у вас и были какие мысли прикарманить мои деньги, лучше оставьте их\nНе хочу вас обидеть - просто предупреждаю.";
			Link.l1 = "Хм... Ну-ну. Всего хорошего.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "Ну, смотрите... Проценты капают. Да и времени у вас осталось не так уж много.";
			Link.l1 = "Не волнуйтесь. До встречи.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("О, это просто чудесно! В любое время, как вам понадобятся деньги - я к вашим услугам.", "Благодарю. Очень приятно иметь дело с деловым человеком, умеющим вовремя вернуть долг. А то знаете, разное бывает...",  "О, не зря я был в вас столь уверен, " + GetAddress_Form(NPChar) + "! Надеюсь, это не последний раз, когда вы прибегаете к моим услугам!");
			Link.l1 = LinkRandPhrase("Я хочу занять денег.", "Мне срочно понадобилась пара-другая пиастров.", "Как насчет небольшого кредита?");
			Link.l1.go = "loan";
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Я бы хотел"+ GetSexPhrase("","а") +" отдать деньги в рост.","Примете на хранение пиратскую добычу?", "Золотишко на черный день оставить можно?");
				Link.l2.go = "deposit";
			}
			Link.l3 = "До свидания, " + NPchar.name + ".";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Я слышу разумного человека! Так сколько денег вы готовы отдать в рост?", "Хорошо. Поверьте мне, та сумма, что вы мне отдаете, будет ждать вас в целости и сохранности, и даже с процентами... А, кстати, какова эта сумма?", "Я смотрю, вы понимаете, что к чему в этой жизни. Сколько вы хотите отдать мне на хранение?");
			link.l1.edit = 3;
			link.l1 = "";
			Link.l1.go = "result";
		break;

		case "result":
			Pchar.QuestTemp.Deposits.(NPC_Area).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1;
			Pchar.QuestTemp.Deposits.(NPC_Area).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Хм, извините, ошибочка вышла..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Хм, таких денег у вас при себе нет, к сожалению. Давайте без глупостей...";
				link.l1 = "Гм... хорошо.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Хорошо. Процентов под эту сумму я готов вам предложить... мм... скажем, " + Pchar.QuestTemp.Deposits.(NPC_Area).Interest + ". Разумеется, в месяц.";
			Link.l1 = "Меня это устраивает.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Лучше я изменю сумму.";
			Link.l2.go = "Deposit";
			Link.l3 = "Кажется, мне не стоит расставаться с деньгами. Всего хорошего.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)+".Result"))
			{
			    Pchar.Quest.Deposits.(NPC_Area).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Извините меня, капитан, но эта сумма слишком велика для провинциального банка. Мне просто негде организовать оборот таких денег, чтобы иметь возможность выплачивать проценты по вашему депозиту. Да и отсутствие достойной охраны, знаете ли... ну, надеюсь, вы меня правильно понимаете? В общем, я могу принять от вас в целом не более " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Очень жаль, придется обратиться к другому ростовщику.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Теперь вы можете быть уверены, что даже самая жестокая буря не оставит вас без средств к существованию. Если же вы решите забрать вклад, то приходите в любое время.";
				Link.l1 = "Хорошо. Всего хорошего.";
				Link.l1.go = "Deposit_Exit";
			}
		break;

		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			Pchar.Quest.Deposits.(NPC_Area).Interest = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Pchar.Quest.Deposits.(NPC_Area).Sum      = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum);

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) + makeint(Pchar.Quest.Deposits.(NPC_Area).Sum);
			//if(sti(pchar.questTemp.depositcount) >= 50000000) UnlockAchievement("bank_money", 3);
			// общий долг
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.Quest.Deposits.(NPC_Area).Sum);
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			CheckForAchievement();
			DialogExit();
		break;

		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Исходя из процентов, которые мы оговорили в прошлый раз, и учитывая прошедшее время, я подсчитал, что должен вам " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)) + "... Вы уверены, что хотите забрать эти деньги";
			Link.l1 = "Абсолютно. Давайте их все сюда.";
			Link.l1.go = "Deposit_return_1";
			Link.l2 = "Я бы хотел"+ GetSexPhrase("","а") +" забрать часть своего вклада.";
			Link.l2.go = "Deposit_return_2";
			Link.l3 = "Знаете, вы правы. Пусть они еще немного полежат. Всего хорошего.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) - makeint(Pchar.Quest.Deposits.(NPC_Area).ClearDeposite);
			//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) - makeint(Pchar.Quest.Deposits.(NPC_Area).Result);
			//if(sti(pchar.questTemp.depositcount) >= 50000000) UnlockAchievement("bank_money", 3);
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Ох... Даже жаль с ними расставаться. Я к ним уже как-то привык. Что же - приходите ко мне еще.";
			Link.l1 = "Если понадобится - приду. Счастливо оставаться.";
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
			CheckForAchievement();
		break;

		case "Deposit_return_2":
			link.l1.edit = 3;
			link.l1 = "";
			Link.l1.go = "Deposit_return_3";
			dialog.text = "И сколько же вы желаете забрать?";
		break;

		case "Deposit_return_3":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0 || iTemp > sti(Pchar.Quest.Deposits.(NPC_Area).Sum))
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Хм, извините, ошибочка вышла..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp <= sti(Pchar.Quest.Deposits.(NPC_Area).Result))
			{
				AddMoneyToCharacter(pchar,iTemp);
				if (sti(Pchar.Quest.Deposits.(NPC_Area).Result) == iTemp)
				{
					DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
					dialog.text = "Получите и распишитесь.";
					link.l1 = "Отлично!";
					link.l1.go = "exit";
				}
				else
				{
					Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result)-iTemp;
					Pchar.Quest.Deposits.(NPC_Area).Result = Pchar.Quest.Deposits.(NPC_Area).Sum;
					Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
					Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
					Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
					Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
					dialog.text = "Получите и распишитесь. Ваш остаток по вкладу составляет "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result))+".";
					link.l1 = "Отлично!";
					link.l1.go = "exit";
				}
				//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) - iTemp;
				//if(sti(pchar.questTemp.depositcount) >= 50000000) UnlockAchievement("bank_money", 3);
				CheckForAchievement();
			}
		break;

		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Вы еще живы? Наверное, хотите вернуть мне деньги? К черту! Из-за вас я потерял столько, сколько вы мне в жизни не возместите! Я не успокоюсь, пока не увижу ваш труп!";
            Link.l1 = "Я как раз хочу уладить наши дела мирно.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Ну, давай посмотрим! Только учти, что ты и сам легко можешь стать трупом!", "Угрожаешь мне?! Ну хорошо, посмотрим, что ты предпримешь...", "Деньги - не главное в жизни. Так что не стоит тебе ради них так убиваться самому и убивать других.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Убирайтесь из моего дома! Глаза мои вас бы не видели!";
			Link.l1 = "...";
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Да? И что вы предлагаете?";
			Link.l1 = "На сегодня я долж"+ GetSexPhrase("ен","на") +" вам сумму в " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". Предлагаю ее вам.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Чтобы наладить отношения, предлагаю вернуть вам сумму долга в размере " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;

		case "LoanRestore_2":
			dialog.text = "Это другое дело! С вами все же можно иметь дела.";
			Link.l1 = "Спасибо. Больше не подведу.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";

			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
		//поиски драгоценного камня за гордом
		case "usurersJewel_1":
			sld = ItemsFromID("UsurersJew");
			switch (rand(3))
			{
				case 0:
					sld.JevelType = "бриллиант";
					sld.model = "DiamondA";
					sld.picIndex = 2;
					sld.Jewel = "jewelry5";
				break;
				case 1:
					sld.JevelType = "рубин";
					sld.model = "RubyA";
					sld.picIndex = 3;
					sld.Jewel = "jewelry5";
				break;
				case 2:
					sld.JevelType = "изумруд";
					sld.model = "EmeraldA";
					sld.picIndex = 4;
					sld.Jewel = "jewelry5";
				break;
				case 3:
					sld.JevelType = "сапфир";
					sld.model = "SapphireA";
					sld.picIndex = 1;
					sld.Jewel = "jewelry5";
				break;
			}
			dialog.text = "Вы знаете, со мной случилось огромное несчастье. Я потерял " + sld.JevelType + " прекрасной работы. Но самое неприятное даже не это. Самое плохое, что камень - не мой!";
			link.l1 = "Ну и что? Купите другой " + sld.JevelType + " и дело с концом.";
			link.l1.go = "usurersJewel_2";
			npchar.quest.usurersJewel.type = sld.JevelType; //тип камня
			npchar.quest.usurersJewel.money = (cRand(6)+2) * 500 + 1000; //вознаграждение
			npchar.quest.usurersJewel.jewel = sld.Jewel;//камешек
		break;
		case "usurersJewel_2":
			dialog.text = "Эх, если бы все было так просто! Дело в том, что этот " + npchar.quest.usurersJewel.type + " уникален в своем роде. Этот камень передал мне заказчик для изготовления перстня. Подобрать что-нибудь подобное по размеру и форме я не имею возможности...";
			link.l1 = "М-да, это действительно проблема. Ну, и чем же я могу вам помочь?";
			link.l1.go = "usurersJewel_3";
		break;
		case "usurersJewel_3":
			dialog.text = "Найдите " + npchar.quest.usurersJewel.type + ", только и всего!";
			link.l1 = "А где вы его потеряли?";
			link.l1.go = "usurersJewel_4";
		break;
		case "usurersJewel_4":
			dialog.text = "В джунглях, сразу за городом. Я иногда люблю прогуляться там в тишине. Это успокаивает...";
			link.l1 = "Понимаете, я человек несколько другой профессии. Я не сыщик и не "+ GetSexPhrase("лакей","служанка") +". Поиски потерянных вами вещей мне не интересны.";
			link.l1.go = "usurersJewel_out";
			link.l2 = "Гм, ну что же, я готов"+ GetSexPhrase("","а") +" взяться за поиски потерянного камня. Каково вознаграждение за работу?";
			link.l2.go = "usurersJewel_5";
		break;

		case "usurersJewel_out":
			dialog.text = "М-да, очень жаль. Видимо, я в вас ошибся. Прошу меня извинить...";
			link.l1 = "Да не проблема.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.usurersJewel");
			ChangeCharacterReputation(pchar, -1);
		break;
		case "jewelCancel":
			dialog.text = "М-да, очень жаль. Видимо, я в вас ошибся. Прошу меня извинить...";
			link.l1 = "Да не проблема.";
			link.l1.go = "exit";
			OfficersReaction("good");
			sTitle = npchar.city + "UsurersJewel";
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.usurersJewel");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			ChangeCharacterReputation(pchar, -1);
		break;
		case "usurersJewel_5":
			dialog.text = "Если вы найдете утерянный " + npchar.quest.usurersJewel.type + ", то я хорошо заплачу. Хочу заметить, что время терпит.";
			link.l1 = "Хм, это хорошо. Ну что же, я отправляюсь на поиски. Ожидайте результата.";
			link.l1.go = "exit";
			pchar.questTemp.different = "SeekUsurersJewel";
			pchar.questTemp.different.SeekUsurersJewel = true;
			//ложим камень
			sld = ItemsFromID("UsurersJew");
			sld.shown = true;
			sld.startLocation = npchar.city + "_ExitTown";
			sld.startLocator = "item" + (rand(14)+1);
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			Log_QuestInfo("Камень находится в локаторе " + sld.startLocator);
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			sTitle = npchar.city + "UsurersJewel";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SeekUsurersJewel", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sJewType", npchar.quest.usurersJewel.type);
		break;

		case "usurersJewel_R1":
			dialog.text = "Прекрасно! Да-да, это он, тот самый потерянный " + npchar.quest.usurersJewel.type + "... Ну что же, я доволен, очень доволен. Я готов выплатить вам награду за работу.";
			link.l1 = "Очень хорошо.";
			link.l1.go = "usurersJewel_R2";
			TakeItemFromCharacter(pchar, "UsurersJew");
		break;
		case "usurersJewel_R2":
			dialog.text = "Спасибо вам еще раз. Вы можете в любое время обращаться ко мне, я всегда выслушаю вас.";
			link.l1 = "Спасибо, чего уж...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fortune", 25);
			AddMoneyToCharacter(pchar, sti(npchar.quest.usurersJewel.money));
			TakeNItems(pchar, npchar.quest.usurersJewel.jewel, 1);
			Log_Info("Вы получили золотой слиток");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			sTitle = npchar.city + "UsurersJewel";
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.usurersJewel");
		break;

        //============== Линейка Блада =============== homo

		case "CapBloodUsurer_1":
			dialog.text = "Я не выдаю средств живой собственности полковника, сэр.";
			link.l1 = "Тем не менее, вы это сделали.";
			link.l1.go = "CapBloodUsurer_2";
		break;

		case "CapBloodUsurer_2":
			dialog.text = "Что?! О чем вы говорите?";
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = "Спокойно. Я принес вам заем, который взял старый артиллерист Огл. Ровно пять тысяч.";
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = "Я говорю вам про заем, который взял старый артиллерист Огл. Ровно пять тысяч. Я уплачу вам за него.";
    			link.l1.go = "CapBloodUsurer_4";
            }
		break;


		case "CapBloodUsurer_3":
            AddMoneyToCharacter(pchar, -5000);
            Pchar.questTemp.CapBloodLine.Ogl = true;
            AddQuestRecord("OglQuest", "2");
			dialog.text = "Оо... благодарю Вас, сэр.";
			link.l1 = "Всего наилучшего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "CapBloodUsurer_4":
			dialog.text = "Вы принесли деньги за Огла?";
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = "Совершенно верно.";
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = "К сожалению, нет, но скоро принесу.";
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_4";
            }
		break;

		case "CapBloodUsurer_5":
			dialog.text = "Сегодня рано утром у меня взял заем человек из города. Дело в том, что... он меня обманул. Он назвался именем Рафаэля Гиннеса, который частенько ко мне заходит, и, признаться, немного на него похож. Я дал ему заем в размере 30 000 пиастров, но потом зашел Раф и...";
			link.l1 = "Вы хотите, чтобы я нашел этого человека? Почему вы думаете, что он еще в городе?";
			link.l1.go = "CapBloodUsurer_6";
		break;

		case "CapBloodUsurer_6":
			dialog.text = "Он в городе, уверяю вас. Сегодня еще никто не отплывал. А вы в качестве премии получите 10 процентов, то есть - 3000 пиастров. Что скажете?";
			link.l1 = "Знаете, пожалуй, я вам помогу.";
			link.l1.go = "CapBloodUsurer_7";
			link.l2 = "На меня не рассчитывайте.";
			link.l2.go = "Exit";
			NextDiag.TempNode = "First time";
			PChar.questTemp.CapBloodLine.QuestRaff = false;
		break;

		case "CapBloodUsurer_7":

            AddQuestRecord("UsurerQuest", "1");
            PChar.questTemp.CapBloodLine.QuestRaff = true;
            NextDiag.CurrentNode = "CapBloodUsurer_8";
			DialogExit();
		break;

		case "CapBloodUsurer_8":
			dialog.text = "Ну что, тебе удалось?";
			if (sti(pchar.money) >= 27000)
			{
    			link.l1 = "Да, вот ваши деньги за вычетом моих десяти процентов.";
    			link.l1.go = "exit";
    			AddMoneyToCharacter(pchar, -27000);
                Pchar.quest.QUsurer.over = "yes";
                NextDiag.TempNode = "First time"; // fix многократной отдачи денег
		   		CloseQuestHeader("UsurerQuest");
            }
            else
            {
    			link.l1 = "К сожалению, нет, но скоро принесу.";
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_8";
            }
		break;
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ах оставьте! Мы с вами серьезные люди, и ни к чему оглядываться на пересуды всей этой голытьбы, которая готова удавиться за испанский дублон, но при этом и пальцем не пошевелит, чтобы сделать из него два\nЯ ищу человека, которому хочу предложить серьезное дело. Человека отважного и деятельного, честного и пунктуального, но не обремененного... э-эм... излишней щепетильностью в вопросах морали. И очень надеюсь найти такого человека в вашем лице.";
			Link.l1 = "Это во многом будет зависеть от того, какого рода 'дело' вы собираетесь мне предложить.";
			Link.l1.go = "GiveTaskSlave_1";
		break;

		case "GiveTaskSlave_1":
			dialog.Text = "Хорошо, слушайте. Сейчас нет на всех Карибах прибыльнее дела, чем работорговля. Я не плантатор, но у меня есть надежный покупатель на этот товар, и не один\nВ общем, мне нужны рабы в количестве " + pchar.questTemp.Slavetrader.iSlaveQuantity + " штук. За каждого я готов заплатить по 250 пиастров - это неплохая цена, согласитесь. Всего сумма сделки составит " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + " золотом.";
			Link.l1 = "Нет, работорговлей я не занимаюсь. Ищите себе другого помощника, не обремененного наличием совести.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Хм, предложение действительно заманчивое. Я бы взял"+ GetSexPhrase("ся","ась") +". Как срочно вам нужны эти рабы?";
			Link.l2.go = "GiveTaskSlave_2";
		break;

		case "exit_slaves":
			dialog.Text = "Э-э-эх, мало кто хочет пошевелить задом, чтоб поднять золото, которое валяется прямо под ногами. Я разочарован... Прощайте, и не вздумайте болтать о нашем разговоре - у меня длинные руки...";
			Link.l1 = "Я вижу, что у вас 'грязные' руки... впрочем, как и язык. Всего хорошего.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;

		case "GiveTaskSlave_2":
			dialog.Text = "В сроках я вас не ограничиваю, но все же постарайтесь побыстрее. Спрос на 'черную слоновую кость' огромен. Если вы зарекомендуете себя в моих глазах с хорошей стороны, подобные заказы станут поступать вам без перебоя, уверяю.";
			Link.l1 = "Охотно верю. Что же, ждите хороших новостей.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
		break;

		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Ну что, удалось вам добыть уговоренную партию 'черного дерева'?";
            if (amount < 0)
			{
				Link.l1 = "Пока нет. Просто решил"+ GetSexPhrase("","а") +" убедиться, что наш уговор еще в силе.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Удалось. Вся партия у меня в трюмах.";
            	Link.l1.go = "Takeslaves";
			}
		break;

		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Отлично! Мои люди их заберут... Насчет таможни и коменданта форта не беспокойтесь. У меня этот бизнес поставлен на широкую ногу, так что проблем не будет, и в контрабанде вас никто не обвинит.";
			Link.l1 = "Смотрю, у вас здесь уже все схвачено! Как насчет оплаты?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;

		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Пожалуйста, получите... Я слов на ветер не бросаю. Держитесь за меня, капитан, и скоро у вас будет столько пиастров, что для их перевозки понадобится целый галеон!";
			Link.l1 = "Хорошо бы... Ну а что дальше?";
            Link.l1.go = "Takeslaves_2";
		break;

		case "Takeslaves_2":
			dialog.Text = "Дальше? А дальше - зайдите недели через три, у меня как раз зреет солидный заказ. Думаю, к тому времени все уже сложится.";
			Link.l1 = "Договорились. До встречи...";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;

		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Работа будет. Но есть проблема - у вас слабоват корабль. Я не хочу провалить дело, да и вас посылать на верную смерть тоже нет желания. Поскольку время терпит, обзаведитесь кораблем посолиднее, не меньше баркентины, а лучше бригом или бригантиной. Ну, флейтом, на крайний случай. И не затягивайте, мы можем упустить момент.";
				Link.l1 = "Понятно, этот вопрос решим. До встречи.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Наконец-то! Я вас ждал. Теперь к сути дела. Как вы понимаете, в любом бизнесе есть конкуренты. Имеются таковые и у меня. Эти алчные беспринципные негодяи всегда норовят увести клиента из-под самого носа! В общем, я хочу устранить одного такого мерзавца и хорошенько заработать на этом.";
				Link.l1 = "Я в"+ GetSexPhrase("есь","ся") +" внимание.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;

		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Превосходно. Так вот. Этот проходимец, по кличке " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + ", привез из Африки груз рабов, и сейчас остановился в бухте " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + ", это остров " + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + ". Он ждет там контрабандистов. Его галеон называется '" + pchar.questTemp.Slavetrader.ShipName + "'. Эту сделку нужно сорвать, во что бы то ни стало!";
			link.l1 = "Хм, а что делать с рабами? Не топить же их!";
			link.l1.go = "Takeslaves_5";
		break;

		case "Takeslaves_5":
			dialog.Text = "С какой стати? " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " на очень плохом счету, и никто не расстроится, если он исчезнет. Вы захватываете галеон, его самого отправляете в расход, товар привозите мне, а я его продаю. По моим сведениям, у него на борту находится не менее полутора тысяч рабов - огромная партия.";
			Link.l1 = "Ого! Действительно немало. Что насчет гонорара за работу?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Нет, уважаемый, эти интриги не по мне. С какой стати мне ссориться с контрабандистами?";
            Link.l2.go = "exit_slaves_1";
		break;

		case "exit_slaves_1":
			dialog.Text = "Да-а, похоже, я в вас ошибся... Прощайте, и забудьте о нашем разговоре. И, если не хотите неприятностей, советую не распространяться о том, что здесь слышали. Как вы уже могли убедиться, у меня в городе все схвачено. А если вы хитрите и попробуете абордировать '" + pchar.questTemp.Slavetrader.ShipName + "' самостоятельно - я позабочусь, чтобы вас вздернули на виселице. Имейте это в виду.";
			Link.l1 = "Можете не переживать - я не занимаюсь доносами. И ваш галеон с рабами мне тоже не нужен. Всего доброго.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста, зачищать атрибут нельзя
		break;

		case "Takeslaves_6":
			dialog.Text = "С учетом того, что я даю полную информацию о местонахождении груза, избавляя вас от необходимости бороздить море в поисках добычи, оплата будет, как вы сами понимаете, несколько ниже. По 200 пиастров за каждого раба. Но это все равно огромная сумма - порядка трехсот тысяч, если все пройдет успешно.";
			Link.l1 = "Годится. Сколько у меня времени на операцию?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Хо-хо! Вы говорите так, будто эти рабы сами бросятся вплавь, чтобы перебраться ко мне в трюм! Хотите, чтобы мои люди подставляли головы под картечь за такую несуразную цену? Увеличьте вознаграждение, или я не стану этим заниматься.";
            Link.l2.go = "exit_slaves_1";
		break;

		case "Takeslaves_7":
			dialog.text = "Думаю, не больше двух недель. Если опоздаете - он успеет выгрузиться и момент будет упущен.";
			link.l1 = "Придется поторопиться. Ждите меня с хорошими новостями. До встречи.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Abl"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Dat"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;

		case "Takeslaves_4_lose":
			dialog.text = "Ну что, " + GetFullName(pchar) + ", как прошла операция? Судя по вашему унылому виду, вы ее провалили.";
			link.l1 = "Вы правы, черт возьми... Я... ну, это... опоздал"+ GetSexPhrase("","а") +" к острову. Он, видимо, уже ушел оттуда, так как я никого не наш"+ GetSexPhrase("ел","ла") +". Весь путь пришлось идти в бейдевинд - постоянно дул встречный ветер, будь он неладен...";
			link.l1.go = "Takeslaves_5_lose";
		break;

		case "Takeslaves_4_win":
			dialog.text = "Ну что, " + GetFullName(pchar) + ", каков нынче улов? Мне уже доложили, что " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " пускает пузыри.";
			link.l1 = "Да, я подоспел"+ GetSexPhrase("","а") +" как раз вовремя! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " перегружал рабов на корабль контрабандистов. Пришлось и его покупателей заодно отправить на свидание к Дэви Джонсу, так что конкурентов у вас значительно поубавилось.";
			link.l1.go = "Takeslaves_5_win";
		break;

		case "Takeslaves_5_lose":
			dialog.text = "Да, похоже, я в тебе ошибся. Ты опоздал"+ GetSexPhrase("","а") +"? А может, просто струсил"+ GetSexPhrase("","а") +", покинув поля боя? Ладно. Теперь это уже не имеет значения. Ты загубил"+ GetSexPhrase("","а") +" отличную идею, и я более не желаю иметь с тобой дел. Проваливай, и забудь обо всем, что ты здесь видел"+ GetSexPhrase("","а") +" и слышал"+ GetSexPhrase("","а") +".";
			link.l1 = "Ну что же, прощайте.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Вижу, я в вас не ошибся - "+ GetSexPhrase("головорез вы лихой","морячка вы лихая") +". Такой человек мне и нужен. Вы великолепно справились с поставленной задачей - у вас в трюмах больше полутора тысяч рабов! Но, к сожалению, я могу принять только тысячу шестьсот единиц товара - на большее у меня сейчас просто нет денег. Остальных рабов вам придется сбыть самостоятельно. Итак, ваша награда составляет 320 000 пиастров.";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6_1");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Вижу, я в вас не ошибся - "+ GetSexPhrase("головорез вы лихой","морячка вы лихая") +". Такой человек мне и нужен. Вы великолепно справились с поставленной задачей - привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Ну что же, вы с честью вышли из сложной ситуации. И хотя добыча меньше, чем я ожидал, я все равно доволен. Итак, вы привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Да уж... Это конечно все понятно, но я рассчитывал на большее. Вы привезли всего лишь "+ sTemp +" рабов. Ну, да ладно, с другой стороны - вы устранили конкурентов, это тоже чего-то стоит. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Спасибо за понимание, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Это конечно весьма занимательно, но... Гм... Похоже, я в тебе ошибся. Что ты мне привез"+ GetSexPhrase("","ла") +"? "+ sTemp +" рабов? А где остальной товар? И только не говори, что ты его утопил"+ GetSexPhrase("","а") +". Ты продал"+ GetSexPhrase("","а") +" его контрабандистам, или, что еще хуже - мерзавцу Вуазье с Бермуд. Убирайся с глаз долой, не желаю больше иметь с тобой никаких дел.";
				link.l1 = "Счастливо оставаться.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Это конечно весьма занимательно, но... Где рабы? Где наш товар? И только не говори, что ты его утопил"+ GetSexPhrase("","а") +". Ты продал"+ GetSexPhrase("","а") +" его контрабандистам, или, что еще хуже - мерзавцу Вуазье с Бермуд. Убирайся с глаз долой, не желаю больше иметь с тобой никаких дел.";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "node_hanter_1";
		break;

		case "node_hanter_1":
			dialog.text = "Это еще не все. Я никому не позволяю водить себя за нос! И за свое вероломство ты поплатишься - я обеспечу тебе проблемы, не сомневайся. А теперь проваливай!";
			link.l1 = "Черт бы тебя побрал с твоей работорговлей!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Takeslaves_6_win":
			dialog.text = "Я вижу, мы сработались, " + pchar.name + ". Я очень этому рад. Заходите ко мне примерно через месяц - возможно, я подберу работу по вашему профилю. У меня как раз намечается кое-что.";
			link.l1 = "Зайду обязательно! Сотрудничество с вами приносит неплохие дивиденды.";
			link.l1.go = "Takeslaves_7_win";
		break;

		case "Takeslaves_7_win":
			dialog.text = "Оно принесет вам целое состояние... Да, еще такой вопрос, " + pchar.name + ": во время абордажа вы ничего такого в каюте галеона не находили?";
			link.l1 = "Нет, ничего такого необычного мне не встречалось. А что, что-то должно было быть?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "statue1"))
			{
				link.l2 = "Вы имеете в виду вот эту статую?";
				link.l2.go = "Yestatue";
			}
		break;

		case "Nostatue":
			dialog.text = "Может, должно, а может, и не должно... Ладно, не находили - так не находили. Жду вас через месяц. До свидания!";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "Yestatue":
			dialog.text = "Да, именно! Это статуя древнего индийского божка Шочипилли. Значит, она все-таки была в каюте этого мерзавца... Разрешите, я взгляну поближе?";
			link.l1 = "Конечно, держите.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "statue1", 1);
		break;

		case "Yestatue_1":
			Log_Info("Вы отдали статую Шочипилли");
			PlaySound("interface\important_item.wav");
			dialog.text = "Так-так... Без сомнения, это она. Послушайте, " + pchar.name + ", продайте мне эту статую. Я готов заплатить за нее сто тысяч золотом.";
			link.l1 = "Сто тысяч? Хм... Я соглас"+ GetSexPhrase("ен","на") +". Забирайте!";
			link.l1.go = "Buystatue";
			link.l2 = "Нет, не продам. Ценность этой статуэтки отнюдь не в золоте, которое можно за нее выручить. Я разбираюсь в предметах индейского культа.";
			link.l2.go = "Nobuystatue";
		break;

		case "Buystatue":
			dialog.text = "Превосходно! Я рад, что мы договорились. Получите ваши деньги. И жду вас через месяц. До свидания.";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "Nobuystatue":
			dialog.text = "Понимаете, но мне очень нужна эта статуя! Я полностью с вами согласен - она ценна не деньгами - любой безграмотный торгаш не заплатит вам за нее и пары тысяч. Но вы и впрямь знаете толк в индейских обрядах, если отказываетесь продать ее за такую сумму\nРаз вы не хотите за нее денег, то я предлагаю обмен. У меня есть кое-что, что может вас заинтересовать. Вот, посмотрите. Великолепное дворянское одеяние! Прямо из Европы! Такого на Карибах не сыскать. Не каждый губернатор может похвастать подобным. Оцените!\nОно стоит много дороже ста тысяч, но его основная ценность, как вы понимаете, тоже меряется отнюдь не деньгами. Предлагаю вам это одеяние в обмен на статую. Она не единственная такая на Карибах. Вы моря"+ GetSexPhrase("к","чка") +", вы сможете отыскать себе еще. А вот мне сложнее. Ну, так что, согласны?";
			link.l1 = "Хех... Пожалуй, я соглас"+ GetSexPhrase("ен","на") +". Давайте мне это платье, и оставьте статую себе.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Нет. Статуя имеет для меня большую ценность, нежели это великолепное платье. Я оставлю ее себе.";
			link.l2.go = "Nobuystatue_no";
		break;

		case "Nobuystatue_yes":
			dialog.text = "Превосходно! Я рад, что мы договорились. Это восхитительное одеяние отныне ваше. Получите. И жду вас через месяц. До свидания.";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "suit_3", 1);
			Log_Info("Вы получили дворянское платье");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "Nobuystatue_no":
			dialog.text = "Жаль, очень жаль... Ну что же, возьмите ее назад. Я не осуждаю вас - статуя действительно ценна для моряка. Жду вас через месяц. До свидания.";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
			TakeNItems(pchar, "statue1", 1);
			Log_Info("Вы получили статую Шочипилли");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "EscapeSlave":
			dialog.text = "Вы вовремя, " + pchar.name + ". Задание есть, если вы готовы приступить к его выполнению прямо сейчас.";
			link.l1 = "Конечно, готов"+ GetSexPhrase("","а") +". Для этого я сюда и явил"+ GetSexPhrase("ся","ась") +".";
			link.l1.go = "EscapeSlave_1";
		break;

		case "EscapeSlave_1":
			dialog.text = "Отлично! Теперь по существу. Вы слышали последнюю новость?";
			link.l1 = "Гм... О чем это вы? Новостей много, и каждый день - новая.";
			link.l1.go = "EscapeSlave_2";
		break;

		case "EscapeSlave_2":
			dialog.text = "Эта новость касается непосредственно нашего дела. На Кюрасао произошел самый массовый побег рабов за всю историю Нового Света! Сбежало больше тысячи душ, причем попутно вырезали и сожгли несколько голландских факторий.";
			link.l1 = "Интересно. Продолжайте.";
			link.l1.go = "EscapeSlave_3";
		break;

		case "EscapeSlave_3":
			dialog.text = "Но они не просто сбежали - они невероятным образом скрылись с острова! Бесследно. Стевезант просто в ярости. Но это неважно... Важно то, что я прошу вас отправиться на Кюрасао, выяснить все подробности случившегося, найти этих беглецов и захватить\nНу и, конечно, не передать в руки голландского правосудия, по законам которого их ждет весьма печальная участь, а привезти мне. За каждого раба я заплачу по 300 пиастров - я слышал, это очень хорошие рабы.";
			link.l1 = "Задача ясна. Беру курс на Кюрасао. Ждите меня с хорошими новостями.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Знаете, я за это не возьмусь. Я не стану отнимать свободу у людей, которые добывали ее, рискуя жизнью. Они ее заслужили.";
			link.l2.go = "EscapeSlave_no";
		break;

		case "EscapeSlave_no":
			dialog.text = "Жаль, очень жаль... Не ждал я от вас подвоха в самый неподходящий момент... Я думаю, вам ясно, что после этого наше сотрудничество продолжаться не может. До свидания.";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;

		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Хе-хе! Да вы не только великолепно справились с непростым заданием, но еще и привезли рабов больше означенного количества - "+ sTemp +" рабов. Но "+ sNum +" рабов явно не из беглых с Кюрасао. Я заплачу за них по 100 пиастров за каждого. Полагаю, в накладе вы не останетесь. Ваша награда составляет 330 000 пиастров за основную партию рабов, и " + FindRussianMoneyString(iSlaveMoneyH) + " за превышение нормы, так сказать.";
				link.l1 = "Ха-ха-ха, а вас не проведешь! Соглас"+ GetSexPhrase("ен","на") +", будь по-вашему, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "Вы великолепно выполнили непростую задачу и привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Вы выполнили сложное задание, и хотя добыча меньше, чем я ожидал, я все равно доволен. Итак, вы привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Нашли? Гм... Ну а что вы мне привезли? "+ sTemp +" рабов? А где остальной товар? И только не говорите, что вы его утопили. Вы продали его контрабандистам, или, что еще хуже - мерзавцу Вуазье с Бермуд. Убирайтесь с глаз долой, не желаю больше иметь с вами никаких дел.";
				link.l1 = "Счастливо оставаться.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Нашли? А где рабы? Где наш товар? И только не говорите, что вы его утопили. Вы продали его контрабандистам, или, что еще хуже - мерзавцу Вуазье с Бермуд. Убирайтесь с глаз долой, не желаю больше иметь с тобой никаких дел.";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "node_hanter_1";
		break;

		case "Escape_slaves_win_1":
			dialog.text = "Я весьма доволен вами, " + pchar.name + ". Очень доволен. Приходите через месяц, я подготовлю к этому времени очередное выгодное для нас обоих дельце.";
			link.l1 = "Я тоже рад"+ GetSexPhrase("","а") +" нашему сотрудничеству, " + npchar.name + ". Через месяц обязательно появлюсь.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;

		case "Slaveshore":
			dialog.text = "Вы очень вовремя появились, " + pchar.name + ". Мне как раз требуются услуги отважного и не очень щепетильного моряка, хе-хе. Вы готовы выполнить мое поручение?";
			link.l1 = "Да, я вас внимательно слушаю.";
			link.l1.go = "Slaveshore_1";
		break;

		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "На этот раз все предельно просто. Сегодня у " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + " встал на якорь пинас '" + pchar.questTemp.Slavetrader.ShipName + "' под флагом " + NationNameGenitive(sti(npchar.nation)) + ". На него тайно, при помощи местных контрабандистов, уже погружена большая партия 'черного дерева', не менее двух тысяч голов\nКоманда пинаса - обыкновенная портовая матросня, капитан - торгаш. В общем, никудышные вояки. Задача ваша - как обычно: абордировать судно, товар - забрать и привезти мне. Оплата - согласно нашей таксы, по 200 пиастров за единицу товара. Все, как обычно.";
			link.l1 = "Хм... Не совсем, как в прошлый раз. Вы предлагаете мне напасть на корабль ваших соотечественников!";
			link.l1.go = "Slaveshore_2";
		break;

		case "Slaveshore_2":
			dialog.text = "Я что-то не совсем понял вас, " + pchar.name + ". Какая разница, какой нации это судно? Или для вас это имеет принципиальное значение?";
			link.l1 = "Мне? Да мне-то наплевать, у золота нет национальности! Меня просто несколько удивило...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Да, имеет. Ссориться с " + NationNameAblative(sti(npchar.nation)) + " я не намерен"+ GetSexPhrase("","а") +".";
			link.l2.go = "Slaveshore_3_no";
		break;

		case "Slaveshore_3_no":
			dialog.text = "Вот как? Вы что, шутите? Ну раз такое дело, тогда проваливайте. И забудьте обо всем, что здесь видели и слышали!";
			link.l1 = "Счастливо оставаться, " + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;

		case "Slaveshore_3_yes":
			dialog.text = "Что вас удивило? Что мне тоже неинтересна национальность золотых монет? Уверяю, так и есть, и странно, что вы еще этого не заметили. Мало того, излишние патриотические пристрастия просто вредны для профессионального банкира, если он, конечно, не планирует окончить свои дни на паперти\nНо давайте обойдемся без философии. Ближе к делу - судно будет в нашей акватории до полуночи, так что времени у вас совсем немного. Вы готовы приступить к операции?";
			link.l1 = "Да, " + npchar.name + ", приступаю немедленно.";
			link.l1.go = "Slaveshore_4";
		break;

		case "Slaveshore_4":
			dialog.text = "Отлично. Я ни на секунду не сомневаюсь в успехе нашего предприятия. Удачи вам, " + pchar.name + ".";
			link.l1 = "Спасибо! До встречи.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;

		case "Pinas_lose":
		dialog.text = "Ну что, " + GetFullName(pchar) + ", как прошла операция? Судя по вашему унылому виду, вы ее провалили.";
			link.l1 = "Вы правы, черт возьми... Я... ну, это... опоздал"+ GetSexPhrase("","а") +". Задержал"+ GetSexPhrase("ся","ась") +" в таверне, а когда выш"+ GetSexPhrase("ел","ла") +" в море - уже никого не наш"+ GetSexPhrase("ел","ла") +".";
			link.l1.go = "Takeslaves_5_lose";
		break;

		case "Slaveshore_5":
			dialog.text = "" + pchar.name + ", прошу вас, успокойтесь. Это не моя вина! Дьявол, мне доложили слишком поздно... Это предательство! Меня подставил один из моих доверенных людей!";
			link.l1 = "Ладно, вижу, что не врешь. На твое счастье капитан пинаса перед смертью проболтался, что наши дела раскрыты. Если бы не эта его фраза, я бы уже прикончил"+ GetSexPhrase("","а") +" тебя... Но ты же говорил, чертов денежный мешок, что у тебя здесь на острове все схвачено!";
			link.l1.go = "Slaveshore_6";
		break;

		case "Slaveshore_6":
			dialog.text = "Засада была организована не местными властями, иначе я бы все знал об этом... " + pchar.name + ", сейчас не время для ругани и оскорблений. Мы с вами оба в смертельной опасности - нас выдал один из моих прежних подрядчиков\nМне удалось узнать, что все собранные доказательства - пакет бумаг - сейчас находятся в пути к нашему генерал-губернатору. Если они попадут к нему в руки - нам конец! И вам, кстати, в первую очередь.";
			link.l1 = "Так вот что имел в виду этот каналья капитан!";
			link.l1.go = "Slaveshore_7";
		break;

		case "Slaveshore_7": //выбор острова, куда бригантина пойдет
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Tortuga";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Слушайте внимательно. У нас есть еще шанс. Пакет отправили бригантиной '" + pchar.questTemp.Slavetraderbrig.ShipName + "'. Это единственное, что я знаю. Бумаги везут генерал-губернатору, в его резиденцию на острове " + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + ". Вы должны перехватить ее, взять на абордаж и найти этот компромат.";
			link.l1 = "Большего мне не остается. Ну что же, молитесь, и за себя, и за меня, и надейтесь, что я ее догоню. А когда вернусь - мы еще продолжим наш разговор. И не думайте, что я все это вот так оставлю!";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;

		case "Slaveshore_8":
			dialog.text = "Главное - найдите пакет! Я буду уверен в своей безопасности, только если вы доставите его мне... Вот черт... " + pchar.name + ", кажется, у нас проблемы...";
			link.l1 = "Что еще такое?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;

		case "Brig_lose":
			dialog.text = "Проклятие... А я так надеялся, на вас, " + pchar.name + ". Ну что же, больше никаких дел мы с вами вести не можем. Если мне не удасться откупиться от следствия, я буду вынужден бежать. Да и вам не советую здесь находиться - солдаты могут нагрянуть в любой момент. Прощайте.";
			link.l1 = "Прощайте, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Letter_lose":
			dialog.text = "Были. Я это знаю достоверно. Ну что же, больше никаких дел мы с вами вести не можем - это теперь небезопасно. Прощайте.";
			link.l1 = "Прощайте, " + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Brig_win":
			dialog.text = "Великолепно! Я ни минуты не сомневался в вас, " + pchar.name + ". Пожалуйста, передайте бумаги мне, иначе у меня душа не на месте.";
			link.l1 = "Держите.";
			link.l1.go = "Brig_win_1";
		break;

		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Отлично... Теперь можно быть спокойным. Генерал-губернатор ни о чем не узнает, а с местными властями все вопросы я уже уладил, хотя пришлось посуетиться изрядно, скажу я вам.";
			link.l1 = "Все это конечно, хорошо, но вы не считаете, что должны компенсировать мне моральный и материальный урон из-за ваших непродуманных действий?";
			link.l1.go = "Brig_win_2";
		break;

		case "Brig_win_2":
			dialog.text = "Безусловно, " + pchar.name + ". Более того, я обязан вам очень многим. И весьма рассчитываю на продолжение нашего сотрудничества. Но прошу вас войти в мое положение - я понес огромные траты - лояльность губернатора и коменданта стоит недешево. Кроме того, пришлось замять убийство патрульного наряда в моей резиденции...";
			link.l1 = "Вы хотите сказать, что не намерены покрывать мои убытки?!";
			link.l1.go = "Brig_win_3";
		break;

		case "Brig_win_3":
			dialog.text = "Не горячитесь, " + pchar.name + ". У меня сейчас и впрямь проблемы с деньгами, поэтому предлагаю вам расчет несколько иного рода.";
			link.l1 = "Тогда я вас внимательно слушаю.";
			link.l1.go = "Brig_win_4";
		break;

		case "Brig_win_4":
			dialog.text = "Около года назад у южного побережья Мейна нас с компаньоном застал сильный шторм. Корабли разбило о скалы близ Бока де ла Сьерпе, и хоть на плаву они продержались недолго, мы успели вывезти на берег наш груз - сундуки с драгоценностями, в которых была большая партия камней и ювелирных изделий. Бухта там уютная, и припрятать сокровища не составило труда\nУтром, едва буря улеглась, на нас напали индейцы. Так погибли те немногие, которым удалось выжить в кораблекрушении, и мой компаньон в том числе. А мне с горсткой матросов удалось уйти на шлюпке\nМы благополучно добрались до Куманы, но вернуться за сундуками я не рискнул. Уверен, что местные дикари надежно охраняют от вторжения свой берег, а заодно и мой клад. Но вы - "+ GetSexPhrase("человек сильный и отважный","девушка сильная и отважная") +" - вполне управитесь с этой бандой краснокожих\nА драгоценностей там действительно много - покроют все понесенные вами убытки, а также затраты на экспедицию до южного Мейна.";
			link.l1 = "Хм... ладно. Тогда, пожалуй, отправлюсь к Кумане. Надеюсь, вы мне не врете. Имейте в виду: попробуете меня надуть - из под земли достану!";
			link.l1.go = "Brig_win_5";
		break;

		case "Brig_win_5":
			dialog.text = "Можете быть уверены, " + pchar.name + ", все сказанное - правда. Ну, и жду вас примерно через месяц - я уже наметил одно дело, которое призвано укрепить пошатнувшиеся позиции моего бизнеса. До встречи.";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			pchar.GenQuestRandItem.Shore18 = true;
			pchar.GenQuestRandItem.Shore18.randitem1 = "sculMa1";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;

		case "SlaveGalleon":
			dialog.text = "Вот и вы, " + pchar.name + ". Замечательно, вы, как всегда, вовремя. Прежде, чем перейти к сути вопроса, я бы хотел немного ввести вас в курс дел, которые творятся на архипелаге вокруг рынка невольников. Думаю, вам это будет полезно. Знаете ли вы, что означает слово 'репартиментос'?";
			link.l1 = "Хм... Нет, " + npchar.name + ", я не знаю, что это такое. Но, судя по звучанию - близко к тому, чтобы что-то у кого-то отобрать. Я прав"+ GetSexPhrase("","а") +"?";
			link.l1.go = "SlaveGalleon_1";
		break;

		case "SlaveGalleon_end":
			dialog.text = "Вы, право, меня удивили. А чего вы ждали от меня? Убирайтесь!";
			link.l1 = "Незаконный бизнес, а тем более, торговля людьми, слишком угнетает морально. Счастливо оставаться.";
			link.l1.go = "node_hanter_1";
		break;

		case "SlaveGalleon_1":
			dialog.text = "Вы очень близки к истине, " + pchar.name + ". Именно отобрать, а конкретно - свободу. Репартиментос - это своеобразный хитрый способ закабаления индейцев под благовидными псевдо-законными предлогами - мирным путем, так сказать. Применяется испанскими властями по отношению к коренному населению Мейна. Вам интересно полушать подробности?";
			link.l1 = "Почему бы и нет?";
			link.l1.go = "SlaveGalleon_2";
		break;

		case "SlaveGalleon_2":
			dialog.text = "Представители испанской короны посещают индейские поселения. В них они, используя циничный обман и под действием прямых угроз, заставляют индейцев покупать у них за баснословные суммы всякую никому не нужную дрянь: гнилое мясо, старые бритвы и тому подобное. Причем в долг\nСпустя определенный период времени, допустим, год, посланцы возвращаются и требуют платы. Если индейцы не могут расплатиться - а так чаще всего и бывает - испанцы забирают с собой часть работоспособного мужского населения якобы на время, для того, чтобы отработать долг и 'научиться возделывать землю'\nСами понимаете, что назад в свои поселения эти индейцы уже никогда не возвращаются. Вот так наши доверчивые краснокожие братья попадают на плантации сахарного тростника и фактории красного дерева.";
			link.l1 = "Хех, ну это же надо... А индейцы не сопротивляются, когда их увозят в рабство? Или они не понимают?";
			link.l1.go = "SlaveGalleon_3";
		break;

		case "SlaveGalleon_3":
			dialog.text = "Понимают, наверное, но открыто выступать, когда тебе тычут бумагу с оттиском большого пальца вождя, мало кто осмеливается. Конечно, подобная тактика чаще применяется в отношении мирных племен - таких как араваки, например, или мискито. С воинственными ица и акавоями, а тем более, караибами, такой ход не пройдет - там и сила-то не всегда помогает\nНу, а теперь перейдем непосредственно к вашей задаче.";
			link.l1 = "Я уже чувствую запах больших денег! Слушаю вас, " + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;

		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add;
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "На днях " + sTemp + " выйдет тяжелый галеон под названием " + pchar.questTemp.Slavetrader.ShipName + ". Он перевозит огромную партию рабов - около 3 000 человек - индейцев, доставленных из различных поселений нижнего Ориноко, захваченных согласно тактике репартиментос\nГалеон идет в Сантьяго - сахарные плантации Кубы остро нуждаются в рабочих руках. Ваша задача - захватить этот галеон вместе с грузом. Оплата за товар - как обычно, по 200 пиастров за единицу.";
			link.l1 = "Хех! Звучит заманчиво. Я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Знаете, что-то не нравится мне эта ваша репартиментос, слишком уж она цинична. Пожалуй, я не стану заниматься этим делом.";
			link.l2.go = "SlaveGalleon_end";
		break;

		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add;
			dialog.text = "Ну что же, тогда я желаю вам удачи. Имейте в виду: этим галеоном управляет очень опытный военный моряк. Бой с ним будет нелегким, так что подготовьтесь, как следует. И не теряйте времени - ему потребуется дней пятнадцать-двадцать, чтобы добраться " + sTemp + " до Сантьяго. Постарайтесь не упустить его, смотрите в оба - этот галеон вы легко отличите от прочих кораблей\nДа! Чуть не забыл! Кроме того, на корабле будет полно всяких индейских побрякушек - краснокожие платят долги произведениями своих ремесел и предметами культа. Если обнаружите на галеоне что-нибудь необычное - обязательно прихватите и привезите мне - я щедро заплачу за каждую ценную находку.";
			link.l1 = "Я вас понял"+ GetSexPhrase("","а") +". Немедленно выдвигаюсь.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 21, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ым","ой"));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;

		case "Lostgalleon":
			dialog.text = "Эх, " + pchar.name + ", это была моя последняя надежда... Поэтому я поручил дело вам - все равно кроме вас с ним никто не смог бы справиться... Как оказалось - и вы тоже. Ну что же, будем прощаться. После давешнего провала и последовавших за ним нехороших слухов, вся моя клиентура разбежалась. Я практически банкрот, и, возможно, мне придется покинуть этот город. Но я вас не виню - задача была очень непростой. Эх-х... Прощайте, " + pchar.name + ".";
			link.l1 = "Мне очень жаль, " + npchar.name + ", что все так получилось. Честное слово. Может, все еще образуется. До свидания.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1)
			{
				dialog.text = "Фух, камень с души свалился... Не зря я вам доверился, не зря... А к чему такая ирония? Что-то не так?";
				link.l1 = "А к тому, уважаемый, что ваш галеон был совсем не галеон... Ну, или очень большой галеон... Дьявол!! Это был линейный корабль! А вы меня об этом не предупредили! Тем не менее, я ухитрил"+ GetSexPhrase("ся","ась") +" его захватить. У меня в трюмах находится "+ sTemp +" рабов, и я готов"+ GetSexPhrase("","а") +" вам их передать. Согласно нашего уговора, вы должны мне " + FindRussianMoneyString(iSlaveMoney) + ". И не мешало бы еще и компенсацию за дезинформацию.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Нашли галеон? А где рабы? Там должно было быть не меньше трех тысяч рабов! Черт возьми, кругом одни негодяи и предатели! Вот от кого-кого, а от вас я этого не ожидал... Вы были моей последней надеждой\nНу, раз так... Клянусь, я потрачу остатки своего состояния и пойду на паперть, но сделаю так, что за вами будет гоняться весь флот " + NationNameGenitive(sti(npchar.nation)) + "! Убирайтесь с глаз моих долой!";
				link.l1 = "Эм-м...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;

		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;

		case "Wingalleon_1":
			dialog.text = "Да вы что! Клянусь, я не знал этого. Должен был выйти именно тяжелый галеон, но никак не линейный корабль! Видимо, в последний момент что-то изменилось... Но вы же справились!\nНасчет денег и компенсации ваших внеплановых издержек я полностью согласен, все признаю, но есть одно обстоятельство непреодолимой силы - у меня просто нет сейчас такой большой суммы. Недавние проблемы... ну, вы и сами все знаете. Но только не горячитесь, " + pchar.name + ", ради Бога. Вы передаете мне товар, я его реализую - заказчик уже ждет\nРовно через пять дней у меня будет вся сумма, и я полностью рассчитаюсь с вами. Можете не сомневаться. А для пущей уверенности, я готов дать вам всю наличность, что у меня есть на данный момент - все мои кредиты.";
			link.l1 = "Хм... Я рассчитывал"+ GetSexPhrase("","а") +" получить деньги сейчас. Знали бы вы, какой бой мне пришлось выдержать! А, ладно... Войду в ваше положение. Но имейте в виду: только попробуйте меня надуть - в Европе достану!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Знаете, что, " + npchar.name + ", катитесь вы куда подальше. Мы так не договаривались. Вы даже не представляете, какой бой мне пришлось выдержать. Я оставлю всех рабов себе и реализую их без вашего посредничества.";
			link.l2.go = "Wingalleon_no";
		break;

		case "Wingalleon_no":
			dialog.text = "Ах вот, значит, как мы заговорили! Значит, пока доверчивый " + npchar.name + " был для вас дойной коровой, вас все устраивало, а как только дело коснулось отсрочки, вы готовы переступить через него и вести дела самостоятельно. При этом вы сразу забыли, что наводку на эту добычу получили от меня\nНу, раз так... Клянусь, я потрачу остатки своего состояния и пойду на паперть, но сделаю так, что за вами будет гоняться весь флот " + NationNameGenitive(sti(npchar.nation)) + "! Убирайтесь с глаз моих долой!";
			link.l1 = "Не пугай меня, пустой денежный мешок. Твой флот я скормлю крабам. Счастливо оставаться!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Wingalleon_yes":
			dialog.text = "Спасибо за понимание, " + pchar.name + ". Обещаю, все будет в лучшем виде, так что ваши угрозы здесь ни к чему\nВозьмите вот это в качестве аванса. Здесь пятнадцать сундуков. Десять пойдут в зачет при окончательном расчете, а пять заберите себе в качестве компенсации морального ущерба. За остальным заходите через пять дней.\nНе забудьте принести все индейские предметы, которые нашли на захваченном корабле... если нашли, конечно. Сейчас мне все равно нечего вам за них предложить.";
			link.l1 = "Ровно через пять дней, " + npchar.name + ". Ровно через пять дней...";
			link.l1.go = "Wingalleon_yes_1";
		break;

		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;

		case "FindRat":
			dialog.text = "Как я и обещал, " + pchar.name + ", я готов с вами расплатиться. Рабы проданы, заказчик доволен, и мы с вами тоже. За вычетом аванса причитающаяся вам сумма составляет " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ". Прошу вас, получите ваши деньги.";
			link.l1 = "Превосходно, " + npchar.name + ". Приятно иметь дело с человеком, способным держать свое слово...";
			link.l1.go = "FindRat_1";
		break;

		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Вы всегда можете верить моему слову, " + pchar.name + ". Я еще ни разу не дал вам повода усомниться в этом. Так будет и впредь. Честность партнеров друг с другом - это фундамент успеха в любом совместном бизнесе\nТеперь об индейских артефактах. Показывайте, что у вас там есть, а то я, как истовый коллекционер, уже весь извелся.";
			link.l1 = "Гхм... Смотрите, пожалуйста.";
			link.l1.go = "FindRat_2";
		break;

		case "FindRat_2":
			if (CheckCharacterItem(pchar, "indian15"))
			{
				dialog.text = "Вот! Замечательно! Базальтовая голова Ольмеков! Это редкий артефакт. Я давно хотел иметь ее в своей коллекции. Предлагаю вам за нее 30 000, или обмен на статуэтку Тлалока, у меня таких две.";
				link.l1 = "Я возьму деньги.";
				link.l1.go = "BG_money";
				link.l2 = "Я меняю этот предмет на статуэтку Тлалока.";
				link.l2.go = "BG_change";
				link.l3 = "Я оставлю этот артефакт себе.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Так-так... К сожалению, нет ничего такого, что могло бы меня заинтересовать.";
				link.l1 = "Ну, нет так нет, как скажете.";
				link.l1.go = "BG_PF";
			}
		break;

		case "BG_money":
			dialog.text = "Замечательно! Вот ваши 30 000, а эта ольмекская голова теперь моя.";
			link.l1 = "Прекрасно. Ну, если это все, что вас заинтересовало...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("Вы отдали базальтовую голову");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian15", 1);
		break;

		case "BG_change":
			dialog.text = "Замечательно! Вот ваша статуэтка, а эта ольмекская голова теперь моя.";
			link.l1 = "Прекрасно. Ну, если это все, что вас заинтересовало...";
			link.l1.go = "BG_PF";
			Log_Info("Вы отдали базальтовую голову");
			Log_Info("Вы получили статуэтку Тлалока");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian15", 1);
			TakeNItems(pchar, "indian19", 1);
		break;

		case "BG_no":
			dialog.text = "Ну, как знаете. Хотя жаль, очень жаль...";
			link.l1 = "Ну, если это все, что вас заинтересовало...";
			link.l1.go = "BG_PF";
		break;

		case "BG_PF":
			dialog.text = "Стойте! Дайте гляну еще разок...";
			link.l1 = "Пожалуйста, смотрите, выбирайте.";
			link.l1.go = "PF_check";
		break;

		case "PF_check":
			if (CheckCharacterItem(pchar, "indian2"))
			{
				dialog.text = "Вот! Я ее сразу не заметил! Меня интересует вот эта фигурка индейского юноши. Очень занятный предмет, скажу я вам... Я готов заплатить за нее 20 000 пиастров, либо обменять на амулет Шиукоатля.";
				link.l1 = "Я возьму деньги.";
				link.l1.go = "PF_money";
				link.l2 = "Я меняю этот предмет на амулет Шиукоатля.";
				link.l2.go = "PF_change";
				link.l3 = "Я оставлю этот артефакт себе.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Нет, гм... Все-таки ничего нужного мне у вас нет.";
				link.l1 = "Ну и ладно! На нет и суда нет.";
				link.l1.go = "FindRat_3";
			}
		break;

		case "PF_money":
			dialog.text = "Замечательно! Вот ваши 20 000, а эта фигурка теперь моя.";
			link.l1 = "Прекрасно. Меня наша сделка весьма устроила.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("Вы отдали пугающую фигурку");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian2", 1);
		break;

		case "PF_change":
			dialog.text = "Замечательно! Вот ваш амулет, а эта фигурка теперь моя.";
			link.l1 = "Прекрасно. Меня наша сделка весьма устроила.";
			link.l1.go = "FindRat_3";
			Log_Info("Вы отдали пугающую фигурку");
			Log_Info("Вы получили амулет Шиукоатля");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian2", 1);
			TakeNItems(pchar, "indian6", 1);
		break;

		case "PF_no":
			dialog.text = "Ну, как знаете. Хотя жаль, очень жаль...";
			link.l1 = "Эта статуэтка мне нужна само"+ GetSexPhrase("му","й") +", извините.";
			link.l1.go = "FindRat_3";
		break;

		case "FindRat_3":
			dialog.text = "Ну что же... Захватив этот галеон... простите, линейный корабль, вы буквально спасли меня. Я рад нашему сотрудничеству, " + pchar.name + ". Лучше вас, наверное, у меня не было ни одного агента.";
			link.l1 = "Польщен"+ GetSexPhrase("","а") +", не скрою. Но вы несколько преувеличиваете мои заслуги...";
			link.l1.go = "FindRat_4";
		break;

		case "FindRat_4":
			dialog.text = "Я говорю совершенно серьезно. И именно потому, что вы обладаете столь выдающимися способностями, и потому, что я вам полностью доверяю, я прошу вас выполнить мое очередное поручение.";
			link.l1 = "Хех! Неожиданно! Слушаю внимательно. Где очередной галеон с рабами?";
			link.l1.go = "FindRat_5";
		break;

		case "FindRat_5":
			dialog.text = "На этот раз у меня будет для вас иное задание, не имеющее отношения к рабам. Вы удивлены? Я хорошо заплачу за выполнение этого поручения... Очень хорошо заплачу.";
			link.l1 = "Давайте ближе к делу.";
			link.l1.go = "FindRat_6";
		break;

		case "FindRat_6":
			dialog.text = "Это дело напрямую связано с недавними событиями, к которым вы, между прочим, тоже имели отношение... Итак, как вам известно, я занимаюсь не вполне законным бизнесом - работорговлей. Также вам известно, что я нанимаю для выполнения поручений каперов, таких, как вы\nНедавно один из моих людей, по совершенно непонятной мне причине, предал меня - составил донос и собрал доказательства, уличающие меня и моих доверенных лиц в незаконной торговле рабами. Последствия вы видели - из соседней колонии сюда прибыл корабль с солдатами, ну... остальное вы знаете\nМне с большим трудом удалось урегулировать ситуацию, а также скрыть обстоятельства уничтожения пинаса и убийства солдат в моем доме. Как вы понимаете, предательство не может остаться безнаказанным. Кроме того, я не могу жить и работать спокойно, зная, что эта крыса жива и разгуливает по архипелагу. Я натравил на этого негодяя охотников за головами, но пока результат нулевой\nЯ прошу вас лично заняться этим делом. Тем более, что предательство этого мерзавца коснулось непосредственно и вас.";
			link.l1 = "Хм... Этого негодяя следует вздернуть на нок-рее! Сообщите мне более подробную информацию о нем, ну и, конечно, размер гонорара за работу.";
			link.l1.go = "FindRat_7";
		break;

		case "FindRat_7":
			dialog.text = "Насчет вознаграждения не беспокойтесь. Я щедро заплачу вам за его уничтожение, и не только деньгами. Я не пожалею лучших вещей из своей индейской коллекции. Теперь о нем. Эту крысу зовут Франсуа Гонтьер\nНедавно, чтобы замести следы - ибо он знает, что я за ним охочусь - он продал свой фрегат на одной из верфей архипелага и скрылся. Мне удалось выяснить у своих коллег, что его недавно видели в Панаме. Пожалуй, вам стоит начать поиски именно оттуда.";
			link.l1 = "Ну что же, немедленно выдвигаюсь.";
			link.l1.go = "FindRat_8";
		break;

		case "FindRat_8":
			dialog.text = "Желаю вам удачи. И будьте осторожны: каналья Гонтьер весьма опытный моряк, и располагает командой отчаянных головорезов. Терять ему нечего, поэтому сражаться он будет отчаянно.";
			link.l1 = "И не таких грозных видали... Но я приму к сведению ваши слова. До свидания, и будьте уверены - я отыщу его даже в преисподней.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;

		case "Wincorvette":
			dialog.text = "Великолепно! Пусть теперь строчит свои доносы медузам. Никто не смеет гадить мне безнаказанно! Спасибо вам, " + pchar.name + ", вы просто незаменимый человек.";
			link.l1 = "Спасибо, " + npchar.name + ", за лестную оценку моих действий. Что насчет оплаты?";
			link.l1.go = "Wincorvette_1";
		break;

		case "Wincorvette_1":
			dialog.text = "Да, конечно. За эту сложнейшую работу я рассчитаюсь соответствующим образом. Я отдаю вам безвозмездно гордость моей коллекции - статуэтку Атлауа. Надеюсь, вы в курсе, что это не простая безделушка?";
			link.l1 = "Ух ты, какой подарок! Да, я знаю, это 'владыка вод', магическая статуя. Очень нужная вещь для моряка.";
			link.l1.go = "Wincorvette_2";
		break;

		case "Wincorvette_2":
			dialog.text = "Кроме того, я выплачу вам 100 000 пиастров премии и 50 000 пиастров на покрытие дорожных издержек.";
			link.l1 = "Спасибо, " + npchar.name + ". В очередной раз повторюсь - с вами приятно работать.";
			link.l1.go = "Wincorvette_3";
			Log_Info("Вы получили идол Атлауа");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "indian18", 1);
		break;

		case "Wincorvette_3":
			dialog.text = "Ну, и как обычно, через месяц, я жду вас у себя. Готовится очень масштабное дело, и вам понадобится хорошо оснащенная эскадра. Прошу, отнеситесь к моим словам серьезно и подготовьтесь, как следует. Если дело выгорит, мы с вами станем богачами.";
			link.l1 = "Хорошо, " + npchar.name + ". Прибуду во всеоружии.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;

		case "Lostcorvette":
			dialog.text = "Жаль, очень жаль... Что же, не расстраивайтесь сильно: вы не перв"+ GetSexPhrase("ый","ая") +", кому не удалось поймать этого проходимца. Ничего, я все равно его прищучу\nНу а вас я жду через месяц. Готовится очень масштабное дело, и вам понадобится хорошо оснащенная эскадра. Прошу, отнеситесь к моим словам серьезно и подготовьтесь, как следует. Если дело выгорит, мы с вами станем богачами.";
			link.l1 = "Хорошо, " + npchar.name + ". Прибуду во всеоружии.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;

		case "Havana_fort":
			dialog.text = "Вы очень вовремя, " + pchar.name + "! Я уже было начал волноваться, и собирался послать на ваши поиски человека\nНу-с, приступим! Задача на этот раз перед вами будет стоять очень серьезная, но и вознаграждение будет соответствующим. После проведенной операции вы получите миллион, или больше.";
			link.l1 = "Вот это дело! Слушаю вас внимательно, " + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;

		case "Havana_fort_1":
			dialog.text = "В течение последнего месяца в Гавану со всего Мейна, мелкими партиями, свозились порабощенные индейцы, кроме того, туда прибыли из Африки и разгрузились несколько галеонов с 'черной слоновой костью'. В данный момент в Гаване, за высокими стенами форта, находится не меньше пяти тысяч рабов.";
			link.l1 = "Чувствую я, что речь пойдет ни больше, ни меньше, как о штурме Гаваны.";
			link.l1.go = "Havana_fort_2";
		break;

		case "Havana_fort_2":
			dialog.text = "Вы все правильно понимаете, " + pchar.name + ". Именно это я и хочу вам поручить. Вам и только вам. Не думаю, что кто-либо из моих других агентов сможет провести столь серьезную операцию\nВы ведь, безусловно, возьметесь за это дело?";
			link.l1 = "Честно сказать, " + npchar.name + ", я несколько ошарашен"+ GetSexPhrase("","а") +". Не думал"+ GetSexPhrase("","а") +" я, что ваша деятельность столь... масштабна. Берусь конечно. " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Знаете что, " + npchar.name + ", это уже ни в какие ворота не лезет. Меня утомили ваши сюрпризы. С вашей алчностью завтра мне придется идти войной на Испанию. Если вам нужны эти рабы - штурмуйте Гавану лично.";
			link.l2.go = "Havana_fort_not";
		break;

		case "Havana_fort_not":
			dialog.text = "Не ожидал я от вас этого. Не ожидал... Черт возьми, что я теперь скажу заказчику? Ладно. Не хотите - как хотите, буду искать другого исполнителя. Прощайте, " + pchar.name + ". Не думаю, что я буду впредь пользоваться вашими услугами. И помните - вы добровольно бросили дело, которое могло обеспечить всех ваших потомков до седьмого колена.";
			link.l1 = "Всех денег не заработаешь. Вы никогда не слышали поговорку 'большая ложка рот дерет'? Всего доброго, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Havana_fort_3":
			dialog.text = "Я не сомневался, что услышу именно такой ответ. Немного подробностей: форт Гаваны и так взять непросто, но теперь эта задача стала еще сложнее\nУ берегов Гаваны в данный момент постоянно крейсируют два линейных корабля - охраняют подступы к городу с моря. Вам нужно будет избавиться от этих кораблей, прежде чем приступить к штурму...";
			link.l1 = "Понятно. Мне не впервой вести сражение против линейных кораблей. Сколько у меня времени?";
			link.l1.go = "Havana_fort_4";
		break;

		case "Havana_fort_4":
			dialog.text = "Немного. Недели три, не больше. После этого рабы будут отправлены на испанские фактории Кубы. Так что вам следует поторопиться.";
			link.l1 = "Тогда не будем медлить. Я отправляюсь!";
			link.l1.go = "Havana_fort_5";
		break;

		case "Havana_fort_5":
			dialog.text = "Одну минутку! " + pchar.name + ", у нас с вами никогда не было недопониманий и разногласий. Но все же хочу поставить вас в известность о текущем положении дел. Я рассчитываю на вас, а на меня рассчитывает заказчик\nИ я, и он, уже вложили в это предприятие силы и средства, и немаленькие - для получения информации, которую я вам сейчас предоставил. Все захваченные рабы, все пять тысяч единиц товара, должны быть доставлены мне в целости и сохранности\nВ противном случае мы примем очень и очень радикальные меры в отношении вас. Прошу вас не обижаться на это предупреждение, а просто принять к сведению.";
			link.l1 = "Можете не переживать, " + npchar.name + ", я понимаю, что такое бизнес. До встречи.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;

		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Ну-с, каковы результаты вашей победы в материальном, так сказать, эквиваленте?";
				link.l1 = "У меня в трюмах находится " + sTemp + " рабов.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Так-так... Вы что, забыли, что я вам говорил? Вы должны были привезти мне не меньше пяти тысяч рабов, а у вас их почему-то всего " + sTemp + ". Как так получилось?";
				link.l1 = "Гм... Не все перенесли дорогу в трюмах сюда от Гаваны...";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Так-так... Вы решили меня надуть? Вы что, забыли, что я вам говорил? Где мои рабы? Где они, я вас спрашиваю?!";
			link.l1 = "Гм... Тут такое дело вышло...";
			link.l1.go = "Havana_Fort_no";
		break;

		case "Havana_Fort_no":
			dialog.text = "Ладно. Не нужно никаких объяснений. Я даю вам неделю на то, чтобы вы доставили мне согласно нашего договора не меньше пяти тысяч рабов. В противном случае - пеняйте на себя!";
			link.l1 = "Хорошо, хорошо, не кипятитесь, будут вам ваши пять тысяч рабов!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;

		case "Havana_Fort_yes":
			dialog.text = "Великолепно! Вы как всегда, отлично справились с моим поручением. Я весьма и весьма вами доволен.";
			link.l1 = "Я тоже собой довол"+ GetSexPhrase("ен","ьна") +"... Но еще больше буду довол"+ GetSexPhrase("ен","ьна") +", когда получу деньги за товар.";
			link.l1.go = "Havana_Fort_yes_1";
		break;

		case "Havana_Fort_yesA":
		dialog.text = "Что же, я этому очень и очень рад. Несмотря на проволочку, вы блестяще справились с моим заданием.";
			link.l1 = "Ну, а теперь я хочу получить деньги за товар.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;

		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Да, безусловно. Я передам рабов заказчику, он рассчитается, и вы получите свои деньги. Все, как в прошлый раз. Давайте посчитаем: вы привезли " + sTemp + " рабов. Соответственно, причитающаяся вам сумма составляет " + FindRussianMoneyString(iSlaveMoney) + ". Через неделю приходите ко мне за расчетом.";
			link.l1 = "Хорошо, " + npchar.name + ", договорились. Ждите меня через неделю. Но смотрите...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;

		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + ", прошу вас, не надо продолжать. Мы же партнеры, а между партнерами не может быть обмана и недоверия. Я обещал вам огромные деньги - вы их получили, я обещал вам прибыльные задания - они у вас есть. Я компенсировал ваши затраты и покрывал ваши расходы даже в самые тяжелые для моего бизнеса времена. Вы можете пожаловаться, что я хоть раз не сдержал слова?";
			link.l1 = "Гм... Нет.";
			link.l1.go = "Havana_Fort_yes_3";
		break;

		case "Havana_Fort_yes_3":
			dialog.text = "Вот видите... " + pchar.name + ", вы мой лучший агент, и я рассчитываю вести с вами бизнес в дальнейшем. Может, хватит уже постоянно высказывать мне свое недоверие, да еще в такой... резкой форме?";
			link.l1 = "Хорошо, " + npchar.name + ". Просто вы и меня поймите: миллион - не маленькая сумма.";
			link.l1.go = "Havana_Fort_yes_4";
		break;

		case "Havana_Fort_yes_4":
			dialog.text = "Я вас прекрасно понимаю, но и вы поймите, что товар надо сначала реализовать, и только потом получить деньги.";
			link.l1 = "Ладно. Будем считать, что мы друг друга поняли.";
			link.l1.go = "Havana_Fort_yes_5";
		break;

		case "Havana_Fort_yes_5":
			dialog.text = "Вот и замечательно. Через неделю жду вас у себя. А сейчас мне нужно заняться подготовкой сделки с заказчиком.";
			link.l1 = "Тогда не буду мешать. До встречи через неделю, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Что я здесь делаю? Хм... Это мой банк. Я буквально пару дней назад его приобрел. Вам, как первому клиенту, могу предложить очень выгодные условия кредитов...";
			link.l1 = "К черту кредиты! Где " + pchar.questTemp.Slavetrader.Name + "?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Тише, тише, не кричите! Его уже давно здесь нет.";
			link.l1 = "Как нет?";
			link.l1.go = "Usurer_Escape_2";
		break;

		case "Usurer_Escape_2":
			dialog.text = "А вы не в курсе? Он исчез неделю назад. Потом обнаружилось, что он прихватил с собой денежки всех своих вкладчиков. Говорят, даже губернатор пострадал. Дом этот он бросил, а я выкупил его у города.";
			link.l1 = "Куда исчез? Как?";
			link.l1.go = "Usurer_Escape_3";
		break;

		case "Usurer_Escape_3":
			dialog.text = "Слышал, что он уплыл из нашей колонии... Вижу, вам он тоже должен... Много?";
			link.l1 = "Больше миллиона! Ну, я все равно эту крысу достану! Куда он отплыл, неизвестно? На каком корабле?";
			link.l1.go = "Usurer_Escape_4";
		break;

		case "Usurer_Escape_4":
			dialog.text = "Никто не знает. Ничего. Вообще. Он словно испарился. Был - и нет. В тот день из гавани вышел флейт, то ли 'Маврикий', то ли 'Мавродий' - наверно, на нем он и скрылся.";
			link.l1 = "Вот проклятье! Это же надо было - довериться такому мерзавцу! От него же за версту несло подлостью! А я, простофиля, поверил"+ GetSexPhrase("","а") +", что мы действительно партнеры! Но он еще здорово пожалеет... Ладно, " + npchar.name + ", прошу меня извинить за грубость... До свидания.";
			link.l1.go = "Usurer_Escape_5";
		break;

		case "Usurer_Escape_5":
		string sColony;
		sColony = npchar.city;
		SetNull2Deposit(sColony);
			dialog.text = "Да ничего, я все понимаю. Если вам понадобятся деньги, или наоборот, захотите открыть вклад - я всегда к вашим услугам.";
			link.l1 = "Спасибо. Но лучше я буду хранить деньги при себе. Всего доброго.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ел","ла"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
		break;

		//<--работорговец
	}
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(npchar.nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true;
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{
		for(n=0; n<MAX_COLONIES; n++)
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1;
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(colonies[nation].nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true;
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, -1, true));
 	SetCaptanModelByEncType(sld, "war");
	FantomMakeCoolSailor(sld, SHIP_WARSHIP, sName, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade28", "pistol5", 100);//создание фантома кэпа
	sld.Ship.Mode = "war";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	sld.AlwaysEnemy = true;
	sld.SuperShooter  = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";//какую группу уничтожить
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";//это победа
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Кэп галеона вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Галеон '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
	sld.lifeDay = 20;
}


int PcharReputation()
{
	return makeint((100-makeint(pchar.reputation))*0.5)+1;
}

void CheckForAchievement()
{
	int deposits = 0;
	if (CheckAttribute(pchar, "Quest.Deposits")) // не треться при возврате
	{
		aref quest;
		aref quests;
		makearef(quests,Characters[GetMainCharacterIndex()].Quest.Deposits);

		int nQuestsNum = GetAttributesNum(quests);

		for(int n = 0; n < nQuestsNum; n++)
		{
			quest = GetAttributeN(quests,n);

			string sQuestName = GetAttributeName(quest);
			if (CheckAttribute(Pchar, "Quest.Deposits."+sQuestName+".Sum"))
			{
				int iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sQuestName).StartYear),makeint(Pchar.Quest.Deposits.(sQuestName).StartMonth),makeint(Pchar.Quest.Deposits.(sQuestName).StartDay), makefloat(Pchar.Quest.Deposits.(sQuestName).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				deposits += makeint(Pchar.Quest.Deposits.(sQuestName).Sum) + ((makeint(Pchar.Quest.Deposits.(sQuestName).Sum)/100)*makeint(Pchar.Quest.Deposits.(sQuestName).Interest))*iPastMonths;
			}
		}
	}
	if(deposits >= 50000000) UnlockAchievement("bank_money", 3);
}
