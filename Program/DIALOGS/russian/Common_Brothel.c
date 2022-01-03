
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1,iColony;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	if (Dialog.CurrentNode == "SpecialExit")
	{
		LAi_SetCitizenTypeNoGroup(npchar);
		Dialog.CurrentNode = "exit";
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(""+ GetSexPhrase("Милый-дорогой, какие девочки?! За тобой половина гарнизона гонится, а он в бордель пожаловал!","Шла бы ты отсюда... За тобой половина гарнизона гонится!") +"", "Вся городская стража рыщет по городу в поисках тебя. Я не идиотка, привечать тебя в такой момент...", "Попрошу удалиться из моего заведения, тебе здесь делать нечего!"),
					LinkRandPhrase(""+ GetSexPhrase("Попробуй только дотронуться до моих девочек - я с тебя живого шкуру сдеру!","Убирайся отсюда, мерзавка!") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего заведения! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Помолчала бы лучше, дура...", "Заткнись, не то хуже будет..."));
				link.l1.go = "exit";
				break;
			}
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
                                    "Рада видеть вас, Питер Блад.",
                                    "Хорошо, что вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
				break;
            }
			//-->> квест пожертвования в церковь
			//результаты
			if (npchar.questChurch == "baster")
			{
				dialog.text = "Ты взял"+ GetSexPhrase("","а") +" деньги, но пожертвования не сделал"+ GetSexPhrase("","а") +"! Мерзав"+ GetSexPhrase("ец","ка") +", одним словом. Я не буду тебя обслуживать в моем заведении. Пош"+ GetSexPhrase("ел","ла") +" вон!";
				link.l1 = "Кхе-кхе, проклятье!";
				link.l1.go = "exit";
				link.l2 = "Послушай, я понимаю, что ты на меня обижена. Я действительно виноват"+ GetSexPhrase("","а") +" перед тобой. Но я хочу задать тебе вопрос, и, полагаю, ответить на него в твоих интересах.";
				link.l2.go = "quests";//(перессылка в файл города)
				break;
			}
			if (npchar.questChurch == "taken")
			{

				if (!CheckAttribute(pchar, "HellSpawnFinished"))
				{
					dialog.text = "Ты еще не отдал"+ GetSexPhrase("","а") +" деньги в церковь. Займись этим, времени у тебя - текущий день! Ты обещал"+ GetSexPhrase("","а") +"!";
					link.l1 = "Да, я помню. Я занимаюсь этим.";
					link.l1.go = "exit";
					break;
				}
				else
				{
					dialog.text = "Ты вернулся...";
					link.l1 = "Я правда пытался тебе помочь и отнести деньги в церковь. Но как оказалось, таким как я добрые дела противопоказаны. В результате  моей попытки погибло много невинных. Забери свои деньги, я не в силах тебе помочь.";
					link.l1.go = "ResultChurch_2";
					LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", false);
					break;
				}
			}
			if (npchar.questChurch == "yes")
			{
				dialog.text = "Ты сделал"+ GetSexPhrase("","а") +" пожертвование?";
				link.l1 = "Да, я все сделал"+ GetSexPhrase("","а") +". Падре просил передать тебе, что твои деньги приняты церковью.";
				link.l1.go = "ResultChurch_1";
				break;
			}
			if (npchar.questChurch == "no")
			{
				dialog.text = "Ты сделал"+ GetSexPhrase("","а") +" пожертвование?";
				link.l1 = "Слушай, " + npchar.name + ", в церкви не взяли твои деньги. Я возвращаю тебе их обратно.";
				link.l1.go = "ResultChurch_2";
				break;
			}
			//-->> дача квеста пожертвования в церковь
			if (pchar.sex != "skeleton" || pchar.rank >= 10)
			{
				if (rand(2) == 1 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questChurch") > 45 && GetHour() < 20)
				{
					dialog.text = "Послушай, я хочу попросить об одном одолжении...";
					link.l5 = "Слушаю внимательно.";
					link.l5.go = "toChurch";
					//личные флаги хозяйки на взятие квеста
					npchar.questChurch = "taken";
					SaveCurrentNpcQuestDateParam(npchar, "questChurch");
					break;
				}
			}
			//<<-- квест пожертвования в церковь

			//-->> дача развода на секс
			if (rand(3) == 1 && pchar.questTemp.different == "free" && PChar.sex != "woman" && GetNpcQuestPastDayWOInit(npchar, "questSex") > 180 && !CheckAttribute(npchar, "quest.selected") && !CheckAttribute(npchar, "quest.NotGoneToSex.over"))
			{
				if (!CheckAttribute(npchar, "quest.NotGoneToSex"))
				{
					dialog.text = "Ах, как скучно в нашем городишке. Может быть, такой видный капитан как вы, развеет мою скуку?";
					link.l5 = "Безусловно! С радостью развлеку такую прекрасную даму.";
					link.l5.go = "toHostessSex";
					link.l8 = "К сожалению, мне некогда, " + npchar.name + ". Как-нибудь в другой раз...";
					link.l8.go = "exit";
					pchar.questTemp.different = "HostessSex";
					SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
					SaveCurrentNpcQuestDateParam(npchar, "questSex");
				}
				else
				{
					dialog.text = "В прошлый раз, когда я ждала тебя в комнате наверху, ты не пришел... Ты упустил свой шанс.";
					link.l1 = "Эх, жаль...";
					link.l1.go = "exit";
					npchar.quest.NotGoneToSex.over = true; //больше вообще не говоить
				}
				break;
			}
			//<<-- развод на секс

			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Добро пожаловать в дом терпимости. Меня зовут " + npchar.name + ", я здесь заведую всем. "+ GetSexPhrase("Чем могу быть полезна?, " + GetAddress_Form(NPChar) + "","Признаюсь, немного удивлена видеть вас здесь, " + GetAddress_Form(NPChar) + ", но смею заверить: мы оказываем услуги не только мужчинам.") +"",
				                               TimeGreeting() + ". Приветствую вас, "+ GetSexPhrase("незнакомец","девушка") +", в моем скромном заведении. Позвольте представиться, я "+ NPChar.Name + " - владелица этого приюта обиженных лаской мужчин. "+ GetSexPhrase("Чем я могу быть вам полезна?","Хотя для женщин у нас тоже кое-что есть...") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Чем я могу вам помочь, " + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + ". Что я могу для вас сделать, " + GetAddress_Form(NPChar) + "?");
			}
			link.l2 = npchar.name + ", я хочу провести время с одной из твоих девушек.";
			link.l2.go = "Hostess_1";
			link.l3 = "Давно я не баловал"+ GetSexPhrase("","а") +" своих парней. Можно сделать оптовый заказ на девочек?";
			link.l3.go = "ForCrew";
			link.l4 = "У меня есть вопрос.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}
			}
			else
			{
			link.l4.go = "quests";//(перессылка в файл города)
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Послушай, " + npchar.name + ", я ищу кольцо губернатора. Он тут кутил у тебя намедни, и потерял его.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			if (CheckAttribute(pchar,"drugstaken") && pchar.drugstaken >= 3)
			{
				link.l6 = "Что-то неважно я себя чувствую. Кажется, третья трубка была лишней.";
				link.l6.go = "tubeheal";
			}
			link.l9 = "Ничем. Я уже ухожу.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "tubeheal":
			pchar.questTemp.drugsprice = 1000*MOD_SKILL_ENEMY_RATE;
			dialog.text = "Похоже, ты и впрямь укурил"+GetSexPhrase("ся","ась")+" какой-то дряни, капитан. К счастью, я могу тебе помочь. Но это займёт некоторое время и будет стоить тебе "+pchar.questTemp.drugsprice+" пиастров. Согла"+ GetSexPhrase("сен","сна")+"?";
			if (sti(pchar.money) >= sti(pchar.questTemp.drugsprice))
			{
				link.l1 = "Что угодно, лишь бы это прошло.";
				link.l1.go = "tubeheal_1";
			}
			link.l2 = "Пожалуй нет.";
			link.l2.go = "exit";
		break;

		case "tubeheal_1":
			AddMoneyToCharacter(pchar,-sti(pchar.questTemp.drugsprice));
			ClearDrugs();
			WasteTime(12);
			dialog.text = "Ну вот, теперь выглядишь гораздо лучше. Полагаю, самочувствие тоже на высоте теперь?";
			link.l1 = "Однозначно! Премного благода"+GetSexPhrase("рен.","рна.");
			link.l1.go = "exit";
		break;

		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Чего ты хочешь, красавчик?","Слушаю Вас внимательно, капитан.");
				link.l1 = "Послушай, " + npchar.name + ", я обнаружил"+ GetSexPhrase("","а") +" эти бумаги в приватной зале вашего заведения...";
				link.l1.go = "ShipLetters_2";
		break;
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть ! Хм... какой-то неизвестный капитан обронил документы ? Я думаю, такие вопросы нужно задавать начальнику порта.";
				link.l1 = "Возможно, возможно ...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Дайте-ка взглянуть! О! Судя по имени, они принадлежат моему уважаемому клиенту и достойному гражданину нашего города. Я могу сама передать документы";
				link.l1	= "Пожалуй, нет ...";
				link.l1.go = "exit";
				link.l2 = "Замечательно! Всегда рад"+ GetSexPhrase("","а") +" помочь уважаемому человеку и достойному заведению.";
				link.l2.go = "ShipLetters_3";
			}
		break;

		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "2");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


		//#20171211-02 Allow reconciling with Hostess if promised donation missed.
		case "Reconcile_1":
		    sld = GetFreeHorseRef(npchar.city);
            int nRand = rand(1) + 2;
            int nPrice = sti(sld.quest.price) * nRand;
            //string sPrice = FindRussianMoneyString(nPrice);
            pchar.quest.reconcileHostess = nPrice;
            dialog.text = strreplace("Боже мой, я полностью признаю, что это моя вина, но если честно, то я просто отвлёкся и забыл об обещанном пожертвовании. Есть ли какой-нибудь способ вам это возместить?", "#thisamount", FindRussianMoneyString(nPrice));
            if (sti(pchar.money) >= nPrice)
            {
                link.l1 = "Ну, я полагаю, да. Как насчёт того, что вы вернёте мне #thisamount?";
                link.l1.go = "Reconcile_2";
                link.l2 = "Разумеется.  Держите.";
                link.l2.go = "exit";
            }
            else
            {
                Link.l1 = "Ни за что.";
                Link.l1.go = "exit";
            }
        break;
        case "Reconcile_2":
            AddMoneyToCharacter(pchar, -sti(pchar.quest.reconcileHostess));
            dialog.text = "Ерунда! Не бери в голову.";
            link.l1 = "Очень хорошо, продолжайте свой бизнес. Не испытывайте удачи в будущем.";
            link.l1.go = "exit";
            npchar.questChurch = "";
        break;
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("Мы всегда рады клиенту. Скажи мне, дорогой, ты уже присмотрел кого-то или тебе все равно?","Ну что же, мои девочки вполне смогут тебе... помочь. Ты присмотрела кого-нибудь, или тебе все равно?") +"";
					Link.l1 = ""+ GetSexPhrase("Хех, мне нужна девка и немедленно, а кто она такая - наплевать. У тебя все они симпатичные...","Да любая, лишь бы дело свое знала...") +"";
					Link.l1.go = "Hostess_NotChoice";
					Link.l2 = "Да, есть одна, "+ GetSexPhrase("что мне приглянулась...","с ней было бы приятнее...") +"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Сегодня я уже не могу дать тебе девочку, кроме тебя у меня еще есть клиенты. Приходи завтра, обслужим как следует!";
					Link.l1 = "Эх, жаль"+ GetSexPhrase(", я только вошел во вкус","") +"... Ну да ладно.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Хм, ты уже оплатил"+ GetSexPhrase("","а") +" девушку. Так что займись ею вплотную, так сказать, и не отвлекай меня по пустякам.";
				Link.l1 = "Хорошо, уже иду.";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			//#20171008-01 Brothel adjust changeover period
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > (BROTHEL_CHANGEDAYS - 2)) //98)
			{
				dialog.text = "Сейчас у меня нет свободных девушек, тебе нужно будет зайти сюда через пару дней.";
				Link.l1 = "Хорошо, как скажешь.";
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Ну что, жеребец, превосходно!","У меня они все умелые, можешь не сомневаться.") +" Могу предложить прекрасную девушку по имени " + GetFullName(sld) + ", она сейчас свободна. Стоить это удовольствие будет " + FindRussianMoneyString(sti(sld.quest.price)) + ". Соглас"+ GetSexPhrase("ен","на") +"?";
				Link.l1 = "Нет, пожалуй, откажусь. Дороговато...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= sti(sld.quest.price))
				{
					Link.l2 = "Конечно, соглас"+ GetSexPhrase("ен","на") +", какие могут быть вопросы?!";
					Link.l2.go = "Hostess_NotChoice_agree";
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Агрх, нет у меня сейчас таких денег...";
					Link.l1.go = "exit";
				}
			}
		break;
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= sti(sld.quest.price))
			{
				if (if (rand(4) == 0 && pchar.sex != "woman" && !CheckAttribute(pchar,"NoPriest") && GetCharacterSPECIALSimple(pchar, SPECIAL_L) >= 8)
				{
					dialog.text = "Отлично, дорогой, " + sld.name + " будет ждать тебя в комнате для уединения на втором этаже. Уверена, ты будешь оооочень доволен...");
					Link.l1 = "Хех, ну я пошел...";
					Link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -sti(sld.quest.price));
					sld.greeting = "Gr_Church";
					sld.model = "priest_2";
					sld.model.animation = "man";
					sld.name = "падре Педро";
					sld.lastname = "";
					sld.Dialog.Filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Priest1";
					pchar.NoPriest = true;
					pchar.PedroID = sld.id;
					pchar.quest.Pedro.win_condition.l1 = "location";
					pchar.quest.Pedro.win_condition.l1.location = npchar.city + "_Brothel_room";
					pchar.quest.Pedro.function = "Pedro_Horse";
				}
				else
				{
					dialog.text = "Отлично, дорог"+ GetSexPhrase("ой","уша") +". " + sld.name + " будет ждать тебя в комнате для уединения на втором этаже.";
					Link.l1 = ""+ GetSexPhrase("Хех, ну я пошел","Ну, я побежала") +"...";
					Link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -sti(sld.quest.price));
					sld.dialog.currentnode = "Horse_ReadyFack";
				}
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}

				// генератор найденных бумаг
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10)
				{
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;

					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем
					sTemp = "_Brothel_room";
					sTemp1 = "_town";
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("Бумаги находятся в локации " + sld.startLocation + ", в локаторе " + sld.startLocator + " p1 : " + p1);

					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";

					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");
				}

				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20)
				{
					iColony = FindColony(npchar.city);
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");
					}
				}

			}
			else
			{
				dialog.text = "Все бы было хорошо, но дело в том, что " + sld.name + " - девушка недешевая, стоит " + FindRussianMoneyString(sti(sld.quest.price)) + ". А у тебя, насколько я вижу, таких денег нет. Приходи как разбогатеешь"+ GetSexPhrase(", родной","") +"...";
				Link.l1 = "Эх, вот так всегда...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Я всегда рада, когда между девочками и клиентами возникают теплые чувства... Назови мне ее имя.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
		break;
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Хм, ты ошибаешься, у меня нет такой девочки в заведении. Возможно, ты неверно называешь ее имя.";
				Link.l1 = "Хм, но я только что с ней разговаривал"+ GetSexPhrase("","а") +".";
				Link.l1.go = "Hostess_Choice_2";
				Link.l2 = "Пожалуй, мне лучше уточнить ее имя. Я позже переговорю с тобой на эту тему.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = GetFullName(sld) + ", ты о ней говоришь?";
				Link.l1 = "Ага, именно о ней.";
				Link.l1.go = "Hostess_NotChoice_agree";
				Link.l2 = "Нет, не о ней.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
        case "Hostess_Choice_2":
			dialog.text = "Тогда тебе нужно назвать ее имя еще раз, возможно я пойму, о ком идет речь.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Пожалуй, мне лучше уточнить ее имя. Я позже переговорю с тобой на эту тему.";
			Link.l2.go = "exit";
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Хмм.. На всю команду? Значит, решил"+ GetSexPhrase("","а") +" 'сбросить пар' у ребят? Что ж, у меня есть несколько высоко квалифицированных девочек, способных на такое... С тебя " + FindRussianMoneyString(GetCrewQuantity(pchar)*30) + ".";
			link.l1 = "Хорошо, я соглас"+ GetSexPhrase("ен","на") +" заплатить эти деньги.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Думаю, они обойдутся как-нибудь...";
			link.l2.go = "exit";
		break;

		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*30 && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*30));

	            AddCrewMorale(Pchar, 10);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "Это, конечно, не мое дело, но мне кажется, что тебе сначала нужно заработать на команду, а потом думать о ее морали.";
			    link.l1 = "Пожалуй, да...";
			    link.l1.go = "exit";
		    }
		break;
		case "Woman_FackYou":
			dialog.text = "Мил"+ GetSexPhrase("ый","ая") +", ты куда это полез"+ GetSexPhrase("","ла") +"?! Надо же, а казался порядочн"+ GetSexPhrase("ым капитаном","ой девушкой") +".\nНу а теперь так просто тебе не уйти, красав"+ GetSexPhrase("чик","ица") +". Подрежут тебе крылышки...";
			link.l1 = "Заткнись, дура...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//просьба о пожертвовании в церкви
		case "toChurch":
			dialog.text = "Понимаешь, я содержу такое заведение, которое... Ну, не совсем обычное, что ли.";
			link.l1 = "Я понимаю.";
			link.l1.go = "toChurch_1";
		break;
		case "toChurch_1":
			dialog.text = "Хорошо... Но это не значит, что о душе своей я не думаю. В общем, я хочу сделать пожертвование церкви. Но появится там мне сложно - косые взгляды, перешептывания женушек...";
			link.l1 = "Ясно. Я сделаю пожертвание, не беспокойся.";
			link.l1.go = "toChurch_2";
		break;
		case "toChurch_2":
			pchar.questTemp.different.HostessChurch.money = (rand(4)+1) * 300;
			dialog.text = "Хорошо. Я даю тебе " + FindRussianMoneyString(sti(pchar.questTemp.different.HostessChurch.money)) +  ". Сделай пожертвование прямо сегодня!";
			link.l1 = "Все сделаю прямо сейчас, можешь не переживать.";
			link.l1.go = "toChurch_3";
			link.l2 = "Ты знаешь, я сейчас несколько занят"+ GetSexPhrase("","а") +". Прямо сегодня не получится. Извини.";
			link.l2.go = "toChurch_4";
		break;
		case "toChurch_3":
			dialog.text = "Отлично! Заскочи потом ко мне, расскажешь, как все прошло...";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessChurch.city = npchar.city; //город
			pchar.questTemp.different = "HostessChurch_toChurch";
			SetTimerFunction("HostessChurch_null", 0, 0, 1); //освобождаем разрешалку на миниквесты и чистим структуру
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.HostessChurch.money));
			ChangeCharacterReputation(pchar, 0.30);

			if(pchar.sex == "skeleton")
			{
				location = &locations[FindLocation(npchar.city + "_Town")];
				pchar.HellSpawnLocation = location.id;
				LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", true);
				//id Города
				//Log_Info(pchar.HellSpawnLocation);
				SaveCurrentQuestDateParam("pchar.questTemp.HellSpawn");
				pchar.quest.HellSpawn.win_condition.l1 = "locator";
				pchar.quest.HellSpawn.win_condition.l1.location = pchar.HellSpawnLocation;
				pchar.quest.HellSpawn.win_condition.l1.locator_group = "reload";
				pchar.quest.HellSpawn.win_condition.l1.locator = "reload7_back";
				pchar.quest.HellSpawn.function = "HellSpawn";
			}

		break;
		case "toChurch_4":
			dialog.text = "Жаль, очень жаль...";
			link.l1 = "Как-нибудь в другой раз.";
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.HostessChurch");
			npchar.questChurch = ""; //нулим личный флаг квеста
			ChangeCharacterReputation(pchar, -1);
		break;

		case "ResultChurch_1":
			dialog.text = "Слава Господу, для меня еще не все потеряно в этой жизни!.. Спасибо тебе.";
			link.l1 = "Да не за что."+ GetSexPhrase(" Ради тебя, " + npchar.name + ", я готов на все...","") +"";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
			npchar.questChurch = ""; //нулим личный флаг квеста
		break;
		case "ResultChurch_2":
			if (!CheckAttribute(pchar, "HellSpawnFinished"))
			{
				dialog.text = "Как не взяли?! Эх, ты, не смог"+ GetSexPhrase("","ла") +" уговорить святого отца! А я так надеялась...";
				link.l1 = "Извини, но так вышло...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
			else
			{
				DeleteAttribute(pchar, "HellSpawnFinished")
				dialog.text = "Да, я видела за окном какая резня творилась в городе. Подумать не могла, что моя маленькая просьба может привести к такому...";
				link.l1 = "В следующий раз лучше лишний раз подумай, прежде чем попросишь нежить сделать добрый поступок. Ни к чему хорошему это не приведет.";
				link.l1.go = "exit";
				PChar.HellSpawn.SeekRebirth = true;
				ChangeCharacterReputation(pchar, 12);
			}


			npchar.questChurch = ""; //нулим личный флаг квеста
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		break;
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Никакого кольца я не находила.";
			link.l1 = "А девочки твои?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		case "TakeMayorsRing_H2":
			dialog.text = "Девочки тоже. Если клиент что-то забывает или теряет, то они все приносят мне обязательно. Никто кольцо губернатора мне не приносил.";
			link.l1 = "Понятно... А может кто-то все-таки решил его придержать?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		case "TakeMayorsRing_H3":
			dialog.text = "Это вряд ли. Девочкам разрешается оставлять себе подарки клиентов, и только.";
			link.l1 = "Понятно... Спасибо тебе, " + npchar.name + ".";
			link.l1.go = "exit";
		break;
		//------- развод на секс ------------
		case "toHostessSex":
			dialog.text = "Ты очень мил. Так чем ты меня развлечешь?";
			link.l1 = "Чем?! Мм... А вот чем! У меня самый большой... э-э-э... авторитет... среди пиратов. Вот.";
			link.l1.go = "toHostessSex_1";
			link.l2 = "У меня зоркий глаз и сильные руки, а еще...";
			link.l2.go = "toHostessSex_2";
			link.l3 = "Мадам, я столько пережил на на этом свете...";
			link.l3.go = "toHostessSex_3";
		break;
		case "toHostessSex_1":
			dialog.text = "Твой 'авторитет' мне не интересен. Прощай...";
			link.l1 = "Как же так?..";
			link.l1.go = "exit";
		break;
		case "toHostessSex_2":
			if (rand(1))
			{
				dialog.text = "Послушай! Кроме самовосхваления, другие темы для разговора тебе известны?! Расскажи занимательную историю, в конце концов!";
				link.l1 = "О! Историю. Это можно! Значит, дело было так...";
				link.l1.go = "SpeakHistory";
			}
			else
			{
				dialog.text = "Послушай! Кроме самовосхваления, другие темы для разговора тебе известны?! Ты совершенно не знаешь, чем развлечь женщину...";
				link.l1 = "Хм, есть много интересных тем для разговора.";
				link.l1.go = "SpeakHistoryTwo";
			}
		break;
		case "toHostessSex_3":
			dialog.text = "Поплачься в жилетку какой-нибудь торговке в городе. И это называется пират?! М-да, куда подевались настоящие мужчины?..";
			link.l1 = "Я не это имел ввиду!";
			link.l1.go = "exit";
		break;
		//истории
		case "SpeakHistory":
			dialog.text = "Внимательно слушаю...";
			if (rand(1))
			{
				link.l1 = "Есть у меня одна история, как меня чуть не съела акула. Хочешь послушать?";
				link.l1.go = "SpeakHistory_1";
			}
			else
			{
				link.l1 = "Как-то брали мы одного торговца, славная добыча, доложу я тебе, у него оказалась в трюме! Золото и серебро!!! Клянусь громом, так и было! Ха-ха! А еще у него на борту были славные курочки, такие ладные, фигуристые, мы их хорошенько пощипали...";
				link.l1.go = "SpeakHistory_2";
			}
		break;
		case "SpeakHistory_1":
			dialog.text = "О-о! На тебя нападала акула! Как же тебе удалось спастись?!";
			link.l1 = "Ну, тогда по порядку. Попали мы как-то в полный штиль, ни ветерка, и жара страшенная стоит. Решили мы искупнуться, чтоб освежиться немного. Это такое наслаждение, доложу я тебе, окунуться после изнуряющей жары в воду. И так я увлекся плаванием и нырянием, что не услышал криков вахтенного: '" + GetAddress_Form(PChar) + ", берегитесь! Акула! Акула!!!'. И тут я ее увидел! Я как раз нырнул и заметил ее силуэт под собой. Ну и громадина!!! В пять раз больше меня! В этот момент она разворачивается и идет прямо на меня!..";
			link.l1.go = "SpeakHistory_3";
		break;
		case "SpeakHistory_2":
			dialog.text = "Хватит! С меня довольно! Ты наглый, самовлюбленный тип! Убирайся с глаз моих!";
			link.l1 = "Хм, за что?..";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_3":
			dialog.text = "О, боже! И что же?!";
			link.l1 = "Я понимаю, что мое спасение в моих руках, разворачиваюсь и плыву, что есть мочи к шлюпке, там ребята пытаются выстрелами отогнать акулу, но такого монстра разве отгонишь... До шлюпки оставалось всего семь ярдов, а за моей спиной уже показался огромный плавник...";
			link.l1.go = "SpeakHistory_4";
		break;
		case "SpeakHistory_4":
			dialog.text = "И ты?!..";
			link.l1 = "Нет, не я. Юнга. Наш храбрый юнга. Увидел, что я не успеваю доплыть до шлюпки, и кинул мне саблю.";
			link.l1.go = "SpeakHistory_5";
		break;
		case "SpeakHistory_5":
			dialog.text = "И ты ее зарубил! Правда?! Ведь ты зарубил этого монстра?";
			link.l1 = "Ну, конечно зарубил! Два раза взмахнул моей верной саблей - и ужасный монстр повержен!";
			link.l1.go = "SpeakHistory_6";
			link.l2 = "Нет, не зарубил. Что ты, разве можно зарубить такую громадину! Я спасся по-другому...";
			link.l2.go = "SpeakHistory_7";
		break;
		case "SpeakHistory_6":
			dialog.text = "Хи-хи... Ты никудышный лгун! Зарубить в воде, монстра в пять раз больше тебя?.. Я тебе не верю, ты такой же хвастун, как и все! Ты меня не заинтересовал...";
			link.l1 = "Дьявол!! Жаль, однако...";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_7":
			dialog.text = "И как же?! Как же ты спасся?";
			link.l1 = "Я еле успел схватить саблю, и развернутся, как увидел надвигающиеся на меня огромные, полные страшных зубов, челюсти. И мне ничего не оставалось, кроме как сунуть саблю меж ними в надежде, что сталь выдержит мощный натиск челюстей! И действительно, акула мотнула мордой, и ушла на глубину, напоследок так наподдав мне хвостом, что я вылетел на поверхность! К тому времени, когда акула избавилась от сабли и вернулась поквитаться со мной, я уже был в шлюпке и ребята гребли во всю мочь к кораблю... На память о той истории, у меня осталось несколько шрамов.";
			link.l1.go = "SpeakHistory_8";
		break;
		case "SpeakHistory_8":
			dialog.text = "О-о! Шрамы!.. Покажи мне...";
			link.l1 = "Сейчас покажу! Сейчас я тебе такое покажу, такое!..";
			link.l1.go = "SpeakHistory_9";
			link.l2 = "Показать? Здесь?! Гм, я, конечно, бываю, грубоват, но разоблачаться при даме, в комнате, куда могут войти посторонние... Я же могу тебя скомпрометировать.";
			link.l2.go = "SpeakHistory_10";
		break;
		case "SpeakHistory_9":
			dialog.text = "Фу, хам! Понятия не имеешь, как вести себя с дамой! Не хочу общаться!";
			link.l1 = "Хм, погоди, ну как же?..";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_10":
			dialog.text = "Ах, как вы благородны! Я даже на мгновение забыла, хозяйкой какого заведения являюсь. Наверное, вы действительно немного грубоваты и... прямолинейны, но в вас есть нечто влекущее...  И потом, мне все-таки любопытно посмотреть на ваши шрамы, пойдемте наверх, в комнату, там нас никто не побеспокоит... И там, возможно, вы тоже захотите что-нибудь посмотреть...";
			link.l1 = "Хм, это как водится!..";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes";
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "Hostess_inSexRoom":
			dialog.text = "Ах, вот и ты...";
			link.l1 = "Так точно, моя королева!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришел
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");

			//pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            		AddCharacterExpToSkill(pchar, "Fencing", -50);
            		AddCharacterExpToSkill(pchar, "Pistol", -50);
            		AddCharacterHealth(pchar, 10);
		break;

		case "SpeakHistoryTwo":
			dialog.text = "Например?";
			link.l1 = "Например, это ты. Поистине, неисчерпаемая тема!";
			link.l1.go = "SpeakHistoryTwo_1";
		break;
		case "SpeakHistoryTwo_1":
			dialog.text = "Осторожно, ты ходишь по краю...";
			link.l1 = "Я люблю риск! Натиск и напор, вот мой девиз! Как только я тебя увидел, сразу понял, ты должны стать моей! Такой очаровательной фигурки я еще не встречал! Какие формы, боже мой!..";
			link.l1.go = "SpeakHistoryTwo_2";
			link.l2 = "Я буду осторожен.";
			link.l2.go = "SpeakHistoryTwo_3";
		break;
		case "SpeakHistoryTwo_2":
			dialog.text = "Боюсь, что эти формы не про тебя. Ты упустил свой шанс, напористый ты наш...";
			link.l1 = "Дьявол, как же так?!";
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_3":
			dialog.text = "Хм, тогда я само внимание...";
			link.l1 = "Я повидал многих женщин, и только сейчас понял, что, увы, не все дамы могут одеваться, столь изыскано как ты. Я был глуп и слеп...";
			link.l1.go = "SpeakHistoryTwo_4";
		break;
		case "SpeakHistoryTwo_4":
			dialog.text = "Отчего же так самокритично?";
			link.l1 = "Мне надо было сразу бежать к тебе!";
			link.l1.go = "SpeakHistoryTwo_5";
		break;
		case "SpeakHistoryTwo_5":
			dialog.text = "Для чего же?";
			link.l1 = "Чтобы пригласить тебя наверх, моя королева!";
			link.l1.go = "SpeakHistoryTwo_6";
			link.l2 = "Мне понадобилась уйма времени, чтоб понять и увидеть эту истину. Мир без тебя скуден и беден, а при твоем появлении все оживает, звонче поют птицы, ласково шелестит прибой и в лучах утреннего солнца, блестят росой на лепестках распускающиеся цветы...";
			link.l2.go = "SpeakHistoryTwo_7";
		break;
		case "SpeakHistoryTwo_6":
			dialog.text = "Довольно! Ты слишком нагл. Ты упустил свой шанс.";
			link.l1 = "Агрх, не получилось...";
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_7":
			dialog.text = "О-о!.. А ты романтик... и льстец!";
			link.l1 = "Льстец? Ничуть! Я говорю истину. И говорю, увы, немногословно. Но это потому, что все слова улетучились при виде пары твоих восхитительных, невероятно огромных...";
			link.l1.go = "SpeakHistoryTwo_8";
		break;
		case "SpeakHistoryTwo_8":
			dialog.text = "Что-о-о?!!";
			link.l1 = "...сияющих глаз.";
			link.l1.go = "SpeakHistoryTwo_9";
		break;
		case "SpeakHistoryTwo_9":
			dialog.text = "О! Что-то я не о том подумала. Продолжай, прошу тебя.";
			link.l1 = "По правде говоря, я тоже думал не только о твоих глазах...";
			link.l1.go = "SpeakHistoryTwo_10";
			link.l2 = "Как ты могла подумать о чем-то другом? Конечно, я имел ввиду только глаза.";
			link.l2.go = "SpeakHistoryTwo_15";
		break;
		case "SpeakHistoryTwo_10":
			dialog.text = "Да? И о чем же еще? Даже боюсь предположить.";
			link.l1 = "О твоей прелестной шейке, и о твоем немыслимом декольте, и у меня перехватывает дыхание, как только я подумаю, сколь прекрасен твой бюст!";
			link.l1.go = "SpeakHistoryTwo_11";
		break;
		case "SpeakHistoryTwo_11":
			dialog.text = "Наглец!..";
			link.l1 = "Быть может... И ты, наверное, прогонишь меня прочь, но... глядя на твое прекрасное платье, я непрестанно думаю о том, что под ним. Ой, прости, я забылся...";
			link.l1.go = "SpeakHistoryTwo_12";
		break;
		case "SpeakHistoryTwo_12":
			dialog.text = "Наглец и плут... и...";
			link.l1 = "Что?";
			link.l1.go = "SpeakHistoryTwo_13";
		break;
		case "SpeakHistoryTwo_13":
			dialog.text = "Очаровательный плут...";
			link.l1 = "Так я прощен?";
			link.l1.go = "SpeakHistoryTwo_14";
		break;
		case "SpeakHistoryTwo_14":
			dialog.text = "Быть может... Здесь слишком душно, давай пройдем наверх, там прохладней, там и продолжим... разговор.";
			link.l1 = "С превеликим удовольствием!";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes";
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "SpeakHistoryTwo_15":
			dialog.text = "Да? А я думала, что интересую тебя целиком, а не отдельными деталями. Только глаза! У меня что, и посмотреть больше не на что?!";
			link.l1 = "Я не то имел в виду...";
			link.l1.go = "SpeakHistoryTwo_16";
		break;
		case "SpeakHistoryTwo_16":
			dialog.text = "Знаю, что вы имели в виду! Уродина, с глазами на выкате! Вот что!!! Убирайтесь! Вы мне противны!";
			link.l1 = "Да ты что " + npchar.name + ", и в мыслях не было!..";
			link.l1.go = "exit";
		break;
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("Вам лучше уйти из заведения!", "Вся городская стража рыщет по городу! Вам лучше уйти...", "Надебоширили - и к нам?! Нет уж, в другой раз..."),
					LinkRandPhrase("Убирайся!!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон отсюда! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Хех, ну и дура же ты...", "Заткнись, не то хуже будет..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Здравствуйте, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase("",", хи-хи-хи..") +". Вам нужно обратиться к хозяйке заведения, все заказы проходят через нее.",
				"Ой, это опять вы. Простите, но вам нужно сначала уладить все вопросы с хозяйкой. Прошу вас пройти к ней.",
				"Послушайте, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", я очень надеюсь, что вы так же упрямы и в других делах, а не только в разговорах... Еще","я еще") +" раз прошу вас пройти к хозяйке заведения.",
				"Ах, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", какой же вы... настойчивый!",", хи-хи-хи... Вы, однако, натойчивы.") +" Вам нужно пройти к хозяйке заведения для оформления заказа.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Хорошо, "+ GetSexPhrase("красавица, ","") +"я понял"+ GetSexPhrase("","а") +".", "А-а, да, конечно...",
                      ""+ GetSexPhrase("Можешь не сомневаться, красавица, я упрям и силен, как бык!","Да-да...") +"", ""+ GetSexPhrase("Вот дьявол, что-то упустил... Прости, милая.","Хорошо, хорошо.") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "А где она находится?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("Аргх, красавица, в твоих глазах можно утонуть...","Ты выглядишь просто замечательно, малышка!") +"", ""+ GetSexPhrase("Знаешь, я давно не видел такой красивой женщины!","Знаешь, я давненько не встречала такой симпатяшки!") +"", ""+ GetSexPhrase("Эх, милая, ты невероятно прелестна.","Эх, надоели все эти неотесаные мужланы... А ты просто прелесть!") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Слушай, "+ GetSexPhrase("красавица","милочка") +", ты не находила здесь обручального кольца? Потерял его тут один человек...",
					"Дорогуша, ты, случаем, не находила в вашем заведении обручального кольца?",
					"Послушай, "+ GetSexPhrase("рыба моя","малышка") +", колечко не попадалось тебе тут, обручальное?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
            //--> Голл. линейка, квест №8. базар с девокой о Библиии.
			if (pchar.questTemp.State == "SeekBible_toFFBrothel" || pchar.questTemp.State == "SeekBible_toGirl")
            {
    			if (npchar.id == "HorseGen_"+FindLocation("FortFrance_Brothel")+"_1")
				{
					if (!CheckAttribute(npchar, "quest.HolLineTalk"))
					{
						dialog.text = "Все, что пожелает так"+ GetSexPhrase("ой красивый пират","ая бравая девушка") +", будет исполнено...";
    					link.l4 = "Послушай, некоторое время назад у вас тут Джекмен с компанией развлекались...";
    					link.l4.go = "Step_Hol8_1";
					}
					else
					{
						dialog.text = "Раздобыл"+ GetSexPhrase("","а") +" тысячу?";
						link.l4 = "Вот твои деньги, говори немедленно все, что знаешь.";
    					link.l4.go = "Step_Hol8_5";
						AddMoneyToCharacter(pchar, -1000);
					}
				}
            }
			//<-- Голл. линейка, квест №8. базар с девокой о Библиии.
			NextDiag.TempNode = "Horse_talk";
		break;
        case "Horse_1":
			dialog.text = "Она в своем кабинете, вы можете пройти к ней отсюда через дверь, противоположную выходу на улицу, либо через улицу с другой стороны дома. Ее зовут " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = "Понятно, "+ GetSexPhrase("милая","дорогуша") +", спасибо.";
			Link.l1.go = "exit";
		break;
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Ах, боже мой, до чего приятно слышать такое! Слушай, я сейчас свободна, так что если ты выберешь меня, то не пожалеешь...", "Ты действительно так считаешь? Мне очень и очень приятно... Послушай, я сейчас свободна, так что ты можешь выбрать меня."+ GetSexPhrase(" Я обещаю тебе море любви и океан ласки...","") +"", ""+ GetSexPhrase("Вот как?! Хм, не скрою, я польщена, не часто приходится слышать в свой адрес такие слова...","Эх, девушка... как меня достали эти мужики...") +" Слушай, я не занята в данный момент, так что я предлагаю тебе выбрать меня. Обещаю, что ты останешься довол"+ GetSexPhrase("ен","ьна") +"...");
				link.l1 = "Хех, именно тебя и выбираю!";
				Link.l1.go = "Horse_3";
				Link.l2 = ""+ GetSexPhrase("Не-е-ет, это был просто комплимент прекрасной даме","Это был просто комплимент") +".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Знаешь что я тебе скажу, милый мой? Не нужно мне пустых разговоров. Займись делом!","Ну вот только этого мне не хватало - комплиментов от женщин!") +"", ""+ GetSexPhrase("Ты тоже воображаешь, что все женщины любят ушами? Хм, это очень зря... Если хочешь меня - плати хозяйке заведения, а трепотня мне не нужна.","Девушка, не растрачивайтесь на пустые слова. Хотите дел - платите...") +"", ""+ GetSexPhrase("Еще один любитель чувственности... Плати - и я буду твоей, но только без этого нежного бреда!","Ты чего, дорогуша? Хочешь удовольствия - плати, а не занимайся болтовней!") +"");
				link.l1 = "Ого, какая хватка!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " все оформляет в своем кабинете. Иди к ней"+ GetSexPhrase(", мой герой,","") +" и назови мое имя - " + npchar.name + ". Я буду тебя ждать...";
			Link.l1 = "Понятно, милая, скоро буду...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
        case "Horse_4":
			dialog.text = NPCStringReactionRepeat("Ты уже оплатил"+ GetSexPhrase("","а") +" девушку, она ждет тебя, поднимайся наверх.",
				"Я же тебе сказала - поднимайся к ней.",
				"Слушай внимательно, еще раз повторяю - поднимайся к ней...",
				"Бесполезно говорить, не доходит...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, я знаю.", "Я помню.",
                      "Можешь не повторять, о ней я помню.", "Хм, о чем это ты?..", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Что-то я тебя не пойму."+ GetSexPhrase(" То комплименты делаешь, то вдруг на попятную идешь. Странный тип...","") +"",
					"Опять со своим комплиментами? Хм, иди к хозяйке, с ней все решай.",
					"Хм, и не надоело тебе? Сказала же - иди к хозяйке заведения.",
					"Нам нельзя здесь оскорблять клиентов, но ты нарываешься, мил"+ GetSexPhrase("ый","ая") +"...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Так вышло, знаешь ли...", "Хорошо, я так и сделаю.",
						"Да-да, я понял"+ GetSexPhrase("","а") +"...", "Хм, извини, дорогуша.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Спасибо за комплимент. Если ты хочешь взять меня, то иди к хозяйке заведения. Все как всегда...";
				Link.l1 = "Понятно.";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Милый, мы все оговорили. ","") +"Не заставляй меня долго ждать...",
						""+ GetSexPhrase("Хм, послушай, милый, мне","Мне") +" очень приятны все твои слова, но пора уже и за дело браться...",
						"Послушай, может ты все-таки уладишь все с хозяйкой?..",
						"Хм, даже не знаю, что и сказать...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Да ни за что на свете!", "Обязательно!",
							"Да, конечно!", "Бегу, бегу к хозяйке...", npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Я тебя ждала, а ты так и не взял"+ GetSexPhrase("","а") +" меня! Не могу сказать, что я в восторге от этого...";
					Link.l1 = "Гм, так получилось...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Ах-х, это опять ты, мо"+ GetSexPhrase("й славный корсар","я славная девушка") +"! Если тебе опять нужна я, то иди к хозяйке - не пожалеешь..."+ GetSexPhrase(" Кстати, я тебя узнала, дорогой, только мы вынуждены обращаться ко всем клиентам стандартно, ты уж извини...","") +"";
				Link.l1 = "Подожди меня совсем чуть-чуть, "+ GetSexPhrase("красавица","милашка") +", и мы снова с тобой уединимся.";
				Link.l1.go = "exit";
				Link.l2 = "Мне очень приятно, что ты меня запомнила, но сейчас провести с тобой ночь я, сожалению, не могу.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
        case "HorseChoice_2":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Вот что,"+ GetSexPhrase(" милый друг,","") +" займись-ка лучше делом. Это полезней будет, чем языком чесать.",
					""+ GetSexPhrase("Хм, странный ты,","Ну что ты") +" талдычишь одно и тоже...",
					"Послушай, может хватит уже?!",
					"Хм, ну надо же, ничего нового"+ GetSexPhrase(", опять глупые попытки очаровать. Хочешь со мной переспать - иди к хозяйке заведения, недоумок!","...") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Да, слышал"+ GetSexPhrase("","а") +"...", "Хм, вот так оно и выходит...",
						"Хм, может хватит, а может и нет...", "Осторожней в выражениях"+ GetSexPhrase(", коза","") +"...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "А-а-а, это опять ты! "+ GetSexPhrase("И снова с глупыми хвалебными речами, ничего не меняется в этом мире... Е","Напоминаю, е") +"сли хочешь "+ GetSexPhrase("переспать","побаловаться") +" со мной - плати хозяйке заведения, а слова твои мне безразличны...";
				Link.l1 = "Хех, кто бы сомневался...";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1_Add":
			dialog.text = "Хм, не скажу, что меня это обрадовало... Очень жаль.";
			Link.l1 = "Извини...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		//===>> секс
		case "Priest1":
			chrDisableReloadToLocation = true;
			dialog.text = "Приветствую тебя, сын мой. Ну давай, подходи поближе...";
			Link.l1 = "Что за херня происходит? Нет, не подходи...";
			Link.l1.go = "SpecialExit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//лечение травмы в борделе - Gregg
			{
				DeleteAttribute(PChar, "chr_ai.TraumaQ");
				DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
				Log_Info("Вы оправились от тяжелой травмы");
				CheckAndSetOverloadMode(pchar);
			}
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Priest2";
			AddDialogExitQuest("PlaySex_1");

			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Luck", 500);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

		case "Priest2":
			dialog.text = "Тебе понравилось? Ты настоящий везунчик, ты первый, кого я окрестил своим достоинством, можешь идти и совершать любые дела и Бог простит тебя";
			Link.l1 = "Просто нет слов, падре...";
			Link.l1.go = "exit_2";
			NextDiag.TempNode = "Priest3";
		break;

		case "Priest3":
			dialog.text = "На сегодня достаточно. Можешь уходить с миром.";
			Link.l1 = "Пиздец...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Priest3";
		break;

        case "Horse_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Очень рада видеть тебя в комнате уединения. "+ GetSexPhrase("И чем мы дальше займемся?","Ну что же, будем развлекаться?") +"", "Проходи, не стесняйся"+ GetSexPhrase(", чувствуй себя как дома на ближайшие два часа.",". Я сумею тебя... развлечь, не переживай.") +"");
					Link.l1 = RandPhraseSimple("Скучать не будем, полагаю...", ""+ GetSexPhrase("Давай повеселимся, детка!","Не будем терять времени!") +"");
				break;
				case "1":
					dialog.text = "Ах, вот и ты, мо"+ GetSexPhrase("й славный корсар! Я кое-что обещала тебе и готова сдержать свое слово","я славная девушка! Следующие два часа ты не забудешь никогда") +"...";
					Link.l1 = "Ух, как заманчиво звучит...";
				break;
				case "2":
					dialog.text = "А-а-а, приш"+ GetSexPhrase("ел","ла") +", наконец-то. Ну, не будем терять времени!";
					Link.l1 = ""+ GetSexPhrase("Не будем, киска...","Ну, покажи мне, что ты можешь...") +"";
				break;
			}
			Link.l1.go = "exit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//лечение травмы в борделе - Gregg
			{
				DeleteAttribute(PChar, "chr_ai.TraumaQ");
				DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
				Log_Info("Вы оправились от тяжелой травмы");
				CheckAndSetOverloadMode(pchar);
			}
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");

			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Капитан, а чего ты так"+ GetSexPhrase("ой","ая") +" не разговорчив"+ GetSexPhrase("ый","ая") +"?";
				link.l1 = LinkRandPhrase("Уж как"+ GetSexPhrase("ой","ая") +" есть.", "В следущий раз поболтаем.", RandPhraseSimple("Я тебе не за разговоры плачу.", "Зато ты, "+ GetSexPhrase("красотка","милочка") +", прямо соловьем заливалась."));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase("Ты была так хороша, что я онемел от восторга! В редкой женщине совмещено столько красоты и темперамента","Ох-х, умеешь ты все-таки доставить удовольствие женщине... Я восхищена.") +".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Тебе понравилось?", "Ну, что скажешь? Все в порядке?", "Как дела,"+ GetSexPhrase(" корсар, все"," все") +" нормально?");
						Link.l1 = RandPhraseSimple(""+ GetSexPhrase("Конечно, все в порядке","А ты и впрямь... умеешь") +".", ""+ GetSexPhrase("Все в норме, крошка","Ты знаешь, я вполне довольна") +".");
						Link.l1.go = "exit";
					break;
					case "1":

						if (sti(npchar.quest.sexHappend) > (rand(4)+5) && sti(pchar.questTemp.HorseLoot) < 3 && !CheckAttribute(npchar, "questTemp.HorseLoot"))
						{
							dialog.text = "Послушай, ты ходишь ко мне уже давно, я так к тебе привязалась...";
							Link.l1 = "Да и я к тебе тоже, чего уж...";
							Link.l1.go = "HorseQuest";
						}
						else
						{
							dialog.text = LinkRandPhrase("Ну что, я выполнила обещание?", "Ну, как"+ GetSexPhrase(" я тебе, понравилась",", тебе понравилось") +"?", "Я надеюсь, "+ GetSexPhrase("ты доволен, потому что я о-о-очень довольна","ты довольна. Я старалась") +"...");
							Link.l1 = RandPhraseSimple("Да, мне все очень понравилось.", ""+ GetSexPhrase("Отлично покувыркались, ты была на высоте!","Все было просто замечательно!") +"");
							Link.l1.go = "exit";
						}
					break;
					case "2":
						dialog.text = RandPhraseSimple("Ну все, тебе пора.", "Время вышло,"+ GetSexPhrase(" корсар,","") +" тебе пора на выход.");
						Link.l1 = RandPhraseSimple("Ага, пока...", "До свидания и спасибо тебе...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}
		break;
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Ну, как вам у нас понравилось?";
				link.l1 = "Слушай, красотка, а не видала ли ты где-то здесь саквояж?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Заходи к нам еще как-нибудь...", "До свидания и до новых встреч...", "Будем рады видеть тебя у нас еще...");
				Link.l1 = "Ладно...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}
		break;

		case "EncGirl_GetBag":
			dialog.text = "Это такой коричневый сундучок с ручкой?";
			link.l1 = "Да, что-то подобное...";
			link.l1.go = "EncGirl_GetBag1";
		break;

		case "EncGirl_GetBag1":
			dialog.text = "Поскольку хозяйки у этого сундучка не нашлось, то мадам отнесла его к себе в будуар.";
			link.l1 = "Спасибо, детка. До свидания.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		//==> квест на лут
        case "HorseQuest":
			pchar.questTemp.HorseLoot = sti(pchar.questTemp.HorseLoot) + 1;
			npchar.questTemp.HorseLoot = true; //уже давала
			dialog.text = "Знаешь что, я хочу кое-что рассказать, возможно, это поможет тебе...";
			Link.l1 = "Хм, говори"+ GetSexPhrase(", дорогуша",", я тебя слушаю") +".";
			Link.l1.go = "HorseQuest_1";
		break;
        case "HorseQuest_1":
			dialog.text = "Недавно один мой клиент был очень пьян. Так вот, болтал он что-то про клад на побережье Мейна, обещал озолотить...";
			Link.l1 = "Может, просто пьяная болтовня.";
			Link.l1.go = "HorseQuest_2";
		break;
        case "HorseQuest_2":
			dialog.text = "Может быть и так. Хотя не думаю, он ничего не помнил потом, так что язык развязался против его воли.";
			Link.l1 = "А о конкретном местонахождении он ничего не говорил?";
			Link.l1.go = "HorseQuest_3";
		break;
        case "HorseQuest_3":
			sTemp = LinkRandPhrase("Shore55", "Shore9", "Shore_ship2");
			if (sTemp == "Shore55")
			{
				str = "заливе Сан-Хуан дель Норте";
				str1 = "box" + (rand(1)+1);
			}
			if (sTemp == "Shore9")
			{
				str = "бухте Аматике";
				str1 = "box1";
			}
			if (sTemp == "Shore_ship2")
			{
				str = "заливе Гибели, что рядом с Белизом";
				str1 = "box2";
			}
         	pchar.GenQuestBox.(sTemp) = true;
			switch (pchar.questTemp.HorseLoot)
			{
				case "1":
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass2 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry1 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry5 = 6;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry10 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.indian11 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 15000;
				break;
				case "2":
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass3 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry14 = 3;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry16 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry18 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.indian17 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 19000;
				break;
				case "3":
					pchar.GenQuestBox.(sTemp).(str1).items.indian20 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian5 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian10 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass4 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian19 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 24000;
				break;
			}
			dialog.text = "Он что-то бурчал о " + str + ".";
			Link.l1 = "Что ж, спасибо тебе за информацию. Если соберусь как-нибудь, то проверю это место.";
			Link.l1.go = "exit";
		break;

		// --> генератор - "Повод для спешки"
		case "Horse_ReasonToFast_1":
			dialog.text = "Тогда заходи еще, я всегда буду тебе рада... Ты так"+ GetSexPhrase("ой милый, не то что другие","ая милая, не то, что эти мужики") +" - ни здрасьте, ни до свиданья, да еще обидеть норовят...";
			link.l1 = "О чем это ты?..";
			link.l1.go = "Horse_ReasonToFast_2";
		break;

		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Да был перед тобой караульный старшина. Он вообще-то к нам не ходит, а тут принесла нелегкая. Еще и меня выбрал... Возился-возился, потом обозвал меня неумехой и заторопился в бухту какую-то. Так быстро убежал, чуть было портки не оставил, ха-ха-ха...";
			link.l1 = "Тебе ли не знать, "+ GetSexPhrase("красавица","дорогая") +", какие мужики бывают? Жене сказал, что в бордель пошёл, любовнице - что к жене торопится, а сам - в бухту, на патрулирование. "+ GetSexPhrase("Хо-хо-хо-хо!..","Ха-ха-ха!") +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;

		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "") {
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// <-- генератор "Повод для спешки"

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit_2":
			AddSimpleRumour("Ты знаешь что я слышал? Это же уму непостижимо! Батюшка нашей церкви решил перейти на тёмную сторону и занялся интимом с очень влиятельным и известным человеком на всём архипелаге.", sti(npchar.nation), 10, 1);
			npchar.lifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors_Priest", -1);
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("Нет, дорогой, не попадалось, к сожалению. Рада бы помочь, да не могу...",
					"Нет, "+ GetSexPhrase("красавчик","девушка") +", кольца не видела...",
					"К сожалению, нет. Никакого кольца не видела.");
				link.l1 = "Жаль... Ну что же, спасибо тебе.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Уж не кольцо ли губернатора ты имеешь ввиду?";
					link.l1 = "Именно, крошка!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Нет, дорогой, не попадалось, к сожалению. Рада бы помочь, да не могу...",
						"Нет, "+ GetSexPhrase("красавчик","девушка") +", кольца не видела...",
						"К сожалению, нет. Никакого кольца не видела.");
					link.l1 = "Жаль... Ну что же, спасибо тебе.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Извини, но кольцо мне подарено! Так что возвращать его я не обязана.";
			link.l1 = "Подарено?! Кем?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		case "TakeMayorsRing_S3":
			dialog.text = "Самим губернатором, конечно!";
			link.l1 = "Так он был слегка невеселе, мягко говоря. Он вообще ничего не помнит.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		case "TakeMayorsRing_S4":
			dialog.text = "Ну а я то здесь при чем? Если он был не был не в себе, то это его проблемы!";
			link.l1 = "Послушай, дорогуша, это же губернатор. Ну зачем тебе с ним ссориться? Кольцо ведь обручальное, сама понимаешь... Отдай, не делай себе проблем из-за такой мелочи.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Кольцо отдам, только ты заплатишь мне пять тысяч пиастров.";
				link.l1 = "Хорошо, забирай свои деньги и гони кольцо.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Хм, ну ладно. Пусть забирает!..";
				link.l1 = "Всенепременно, дорогуша!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		case "TakeMayorsRing_S6":
			dialog.text = "Пожалуйста...";
			link.l1 = "Ну, отлично. Спасибо за помощь, дорогуша.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
//********************************* Диалоги девки из борделя ФФ **********************************
  		case "Step_Hol8_1":
			dialog.text = "И что?";
			link.l1 = "Слышал"+ GetSexPhrase("","а") +" я, один из пиратов книгу какую-то предлагал к продаже, типа Библии...";
			link.l1.go = "Step_Hol8_2";
		break;
  		case "Step_Hol8_2":
			dialog.text = "Было такое, помню... Послушай, "+ GetSexPhrase("красавчик, давай поднимемся наверх","девушка, заплати мне -") +" и я отвечу на все твои вопросы. Тебе это будет стоить всего 1000 монет...";
			link.l1 = ""+ GetSexPhrase("Мне нужно просто узнать кое-что...","Ты вообще хоть что-нибудь делаешь бесплатно?") +"";
			link.l1.go = "Step_Hol8_3";
		break;
  		case "Step_Hol8_3":
			dialog.text = ""+ GetSexPhrase("Хорошо, отвечу на любой твой вопрос. Но только наверху - здесь не место для разговоров.","Хи-хи-хи... Тебе нужна информация - мне нужны деньги. Хочешь, могу дать не только информацию, но и кое-что еще, если поднимемся наверх... Я тебя знаю. Только это будет дороже, хи-хи...") +"";
			link.l1 = ""+ GetSexPhrase("Агрх, у меня времени нет...","У меня нет времени на глупости.") +"";
			link.l1.go = "Step_Hol8_4";
		break;
  		case "Step_Hol8_4":
			dialog.text = ""+ GetSexPhrase("Ой, мужчина женской ласки испугался!!!","Ой, да ладно тебе... Давай тысячу - расскажу все, что знаю.") +"";
            if (sti(pchar.money) >= 1000)
            {
    			link.l1 = "Вот твои деньги, но говори что знаешь здесь и сейчас.";
    			link.l1.go = "Step_Hol8_5";
                AddMoneyToCharacter(pchar, -1000);
            }
            else
            {
    			link.l1 = ""+ GetSexPhrase("Ничего я не испугался, денег просто нет... ","") +"Зайду к тебе, как раздобуду тысячу...";
    			link.l1.go = "exit";
				npchar.quest.HolLineTalk = true;
            }
			NextDiag.TempNode = "Horse_talk";
		break;
		case "Step_Hol8_5":
			dialog.text = "Лоран де Граф говорил тогда, что может продать редкостную книгу, вроде бы Библию.";
			link.l1 = "Хм, и что?";
			link.l1.go = "Step_Hol8_6";
		break;
		case "Step_Hol8_6":
			dialog.text = "Повертели они ее в руках. На обложке распятие выбито, а так невозможно и понять, что за книга. Написана она на незнакомом языке, никто не смог даже примерно сказать, что за письмена.";
			link.l1 = "Хм, раз она продается, то я хотел"+ GetSexPhrase("","а") +" бы ее приобрести. Как я могу найти этого корсара?";
			link.l1.go = "Step_Hol8_7";
    	break;
		case "Step_Hol8_7":
			dialog.text = "Иди прямиком на Тортугу, вот и найдешь. Как я уже сказала, зовут его Лоран де Граф, он известный флибустьер, голландец.";
			link.l1 = "Спасибо, отправлюсь туда.";
			link.l1.go = "Step_Hol8_8";
    	break;
		case "Step_Hol8_8":
			dialog.text = "Слушай, а что, действительно эта книга стоит денег?";
			link.l1 = "Сложно сказать, смотреть надо. А что де Граф говорил? Где нашел, что знает о книге?";
			link.l1.go = "Step_Hol8_9";
    	break;
		case "Step_Hol8_9":
			dialog.text = "Да ничего особенного, его и не слушал никто толком. Не до того было, не до Библии уж точно...";
			link.l1 = "Ясно. Спасибо тебе, поеду искать де Графа.";
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "4");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.State = "SeekBible_toTavern";
			NextDiag.TempNode = "Horse_talk";
    	break;
	}
}


ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
