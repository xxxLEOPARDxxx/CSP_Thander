// boal 25/04/04 общий диалог церковь
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

    string iDay, iMonth, lastspeak_date;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }

    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {
        npchar.quest.BadMeeting = "";
    }
	if (!CheckAttribute(npchar, "quest.Fooled"))
    {
        npchar.quest.Fooled = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}

	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}

	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(""+ GetSexPhrase("Сын мой","Дочь моя") +", к сожалению, я не могу дать тебе убежища. Беги!", "Вся городская стража рыщет по городу в поисках тебя, "+ GetSexPhrase("сын мой","дочь моя") +". Церковь открыта для страждущих, но я не могу предоставить тебе убежища...", ""+ GetSexPhrase("Сын мой","Дочь моя") +", тебе надо бежать! Прошу тебя, не медли с этим!"),
					LinkRandPhrase("Что ты делаешь в церкви, падшая душа? Я требую, чтобы ты удалил"+ GetSexPhrase("ся","ась") +" немедленно, пока солдаты не ворвались и не устроили здесь резню!", "Немедленно покинь храм, безбожни"+ GetSexPhrase("к","ца") +"! Я не заступлюсь за так"+ GetSexPhrase("ого","ую") +", как ты!", "Немедленно покинь храм Божий! Мне не нужны здесь убийства!!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Да ладно тебе, падре...", "Да не нужна мне твоя помощь..."),
					LinkRandPhrase("Святой отец, лучше не путайся под ногами...", "Уйду, не беспокойся...", "Падре, не суетись, не до тебя, ей богу"));
				link.l1.go = "fight";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				Dialog.Text = "Добро пожаловать под сень святой обители, "+ GetSexPhrase("сын мой","дочь моя") +".";
				link.l1 = "Падре, таверну штурмует толпа подвыпивших горожан. Уверяют, что там засел оборотень, но я говорил"+ GetSexPhrase("","а") +" с ним и видел"+ GetSexPhrase("","а") +" всего лишь перепуганного человека. Он хочет исповедоваться!";
				link.l1.go = "MC_CaracasChirch";
				Link.l2 = "Мне пора.";
				Link.l2.go = "exit";
				break;
			}
			if (IsEquipCharactersByItem(pchar, "DHGlove") && npchar.quest.BadMeeting != lastspeak_date)
			{
				Dialog.Text = "Ты... колдун! Как ты посмел, грязный нечестивец, явиться в храм Божий?! Исчадие ада, гнев Господень да падет на тебя!";
				Link.l1 = "Колдун говоришь... А собственно почему колдун?";
				Link.l1.go = "DHreaction";
				break;
			}
			if (startherotype == 2 && npchar.quest.BadMeeting != lastspeak_date && npchar.quest.Fooled != lastspeak_date && !IsEquipCharacterByItem(pchar, "glasses") && 80 > sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)))
			{
				Dialog.Text = "Твои глаза... Покинь храм Господа, исчадие ада! Нам с тобой не о чем говорить!";
				Link.l2 = "Ты заблуждаешься, святой отец. Я ангел небесный, и спустилась на землю дабы исполнить поручение Господне.";
				Link.l2.go = "fool_priest";
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit";
				break;
			}

			if (pchar.sex == "Skeleton" && GetCharacterEquipSuitID(pchar)!= "suit_1")
			{
				Dialog.Text = "Покинь храм Господа, исчадие ада! Нам с тобой не о чем говорить!";
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit";
				Link.l2 = "Плевать я хотел на тебя и твоего бога!";
				Link.l2.go = "exit";
				break;
			}

            if (npchar.quest.BadMeeting != lastspeak_date )
			{
				if(Pchar.questTemp.CapBloodLine == false)
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
					{
						dialog.text = "...вечно гореть им в геенне огненной! Не видать им...";
						link.l1 = RandPhraseSimple("Гм! Не помешал"+ GetSexPhrase("","а") +", падре?", "Вот это спич!");
						link.l1.go = "GenQuest_Church_2_Start_1";
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
						break;
					}

					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
					{
						Dialog.Text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", я рад снова видеть вас!";
						link.l1 = "И я рад"+ GetSexPhrase("","а") +" видеть вас в добром здравии, отец " + NPChar.name + "...";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
						break;
					}

					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						Dialog.Text = ""+ GetSexPhrase("Сын мой","Дочь моя") +"! Рад снова видеть тебя в добром здравии и хорошем настроении. Видимо, Бог способствовал счастливому завершению нашего дела?";
						link.l1 = "Да, " + RandPhraseSimple("падре", "святой отец") + ", хоть в мои паруса и не всегда дул попутный ветер, хоть я и потратил"+ GetSexPhrase("","а") +" несколько больше времени, сил и денег, но в итоге ваше поручение выполнено.";
						link.l1.go = "GenQuest_Church_1_Complete_1";
						break;
					}
				}
				Dialog.Text = "Добро пожаловать под сень святой обители, "+ GetSexPhrase("сын мой","дочь моя") +".";
				link.l1 = "Здравствуйте, святой отец.";
				link.l1.go = "node_3";
				Link.l2 = "Ты мне не отец, и не смей так больше обращаться.";
				Link.l2.go = "node_2";

				if (startherotype == 2 && !IsEquipCharacterByItem(pchar, "glasses"))
				{
					Dialog.Text = "Мой ангел! Чем я могу помочь?";
					Link.l2 = "Ничем, я уже ухожу.";
					Link.l2.go = "exit";
				}
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			if (npchar.quest.BadMeeting == lastspeak_date)
			{
				Dialog.Text = "Покинь храм Господа, богохульни"+ GetSexPhrase("к","ца") +"! Нам с тобой не о чем говорить!";
				if (pchar.sex == "Skeleton" || startherotype == 2)
				{
					Dialog.Text = "Покинь храм Господа, нечисть! Нам с тобой не о чем говорить!";
				}
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit";
			}

			NextDiag.TempNode = "First time";
		break;

		case "DHreaction":
			dialog.text = "Убирайся! Мне не о чем с тобой говорить!";
			link.l1 = "Мда... ты же просто дурачок.";
			link.l1.go = "exit";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -5);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "fool_priest":
			if (drand(80) > sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)))
			{
				dialog.text = "Тебе не обмануть меня! Прочь отсюда, дабы не осквернять своим присутствием храм Божий!";
				link.l1 = "Дьявол!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 5 + 5 * sti(pchar.rank));
				ChangeCharacterReputation(pchar, -1);
				npchar.quest.BadMeeting = lastspeak_date;
			}
			else
			{
				dialog.text = "Простите великодушно, не узнал. Как простой священник может услужить такому небесному созданию?";
				link.l1 = "Есть один вопрос.";
				AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50 + 10 * sti(pchar.rank));
				link.l1.go = "node_3";
				npchar.quest.Fooled = lastspeak_date;

			}
		break;

		case "node_2":
			dialog.text = "Ах, ты богохульни"+ GetSexPhrase("к","ца") +"! А ну прочь отсюда, дабы не осквернять своим присутствием храм Божий!";
			link.l1 = "Да я и так не собирал"+ GetSexPhrase("ся","ась") +" здесь задерживаться.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = "Да благословит Господь вас и дела ваши... Вы пришли ко мне с какой-то целью?";
			if (startherotype == 2 && !IsEquipCharacterByItem(pchar, "glasses"))
			{
				dialog.text = "Я к вашим услугам. Все, что угодно.";
			}
			//зачарованный город -->
  			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				link.l1 = "Падре, таверну штурмует толпа подвыпивших горожан. Уверяют, что там засел оборотень, но я говорил"+ GetSexPhrase("","а") +" с ним и видел"+ GetSexPhrase("","а") +" всего лишь перепуганного человека. Он хочет исповедоваться!";
				link.l1.go = "MC_CaracasChirch";
				break;
			}
  			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = "Приводите этого человека ко мне. Я исповедую его здесь, в церкви.";
				link.l1 = "Я понял"+ GetSexPhrase("","а") +", падре.";
				link.l1.go = "exit";
				break;
			}
			//<-- зачарованный город
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine != true)
            {
    			link.l1 = RandPhraseSimple("Я хочу внести пожертвования.", "Хочу пожертвовать на благое дело.");
    			link.l1.go = "donation";
				if (startherotype !=2)
				{
					link.l2 = RandPhraseSimple("Думаю, настало время исповеди.","Мне нужно покаяться, "+RandPhraseSimple("падре.", "святой отец."));
					link.l2.go = "ispoved";
				}
    			link.l3 = RandPhraseSimple("У меня к вам дело, " + RandPhraseSimple("падре.", "святой отец."),
                                           "Я прибыл"+ GetSexPhrase("","а") +" по делу, " + RandPhraseSimple("падре.", "святой отец."));
    			link.l3.go = "work";//"quest lines";
            }

			link.l6 = "Извините, мне пора идти.";
			link.l6.go = "exit";
		break;

		// Church GenQuest_2 -->
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...и милости Божьей! Да поглотит их души мрак вселенский за прегрешения...";
				link.l1 = LinkRandPhrase("Святой отец", "Падре", "Отче") + ", не слишком ли вы усердствуете? Так недолго и удар получить.";
				link.l1.go = "GenQuest_Church_2_Start_2";
				link.l2 = RandPhraseSimple("О-о... Не буду вам мешать...", "Я, кажется, не вовремя - пойду, пожалуй...");
				link.l2.go = "exit";
		break;

		case "GenQuest_Church_2_Start_2":
			dialog.text = "О, "+ GetSexPhrase("сын мой","дочь моя") +", совершено ужасное кощунство, позорнейшее из преступлений! Обокрасть церковь!!! Да это все равно, что запустить свои грязные лапы прямо в карман Господу!";
				link.l1 = "Ах, вот оно что!.. И как же это случилось?";
				link.l1.go = "GenQuest_Church_2_Start_3";
				link.l2 = LinkRandPhrase("Это все, конечно, печально, но я, пожалуй, пойду...", "Сочувствую, падре, но мне уже пора...", "Наверное вы слишком понадеялись на Господа, нужно было замки ставить покрепче. Пойду я, пожалуй...");
				link.l2.go = "exit";
			break;

		case "GenQuest_Church_2_Start_3":
			dialog.text = "Какие-то мерзавцы под покровом ночи вынесли все, что было собрано паствой! И жертвенную чашу прихватили, безбожники!";
				link.l1 = "Да уж, времена... Но, я надеюсь, вы предприняли какие-то шаги?.. по горячим следам, так сказать.";
				link.l1.go = "GenQuest_Church_2_Start_4";
			break;

		case "GenQuest_Church_2_Start_4":
			dialog.text = "О да! Конечно!! Я отлучил богомерзких грабителей от церкви! А сейчас предаю их души анафеме.";
				link.l1 = "Не сомневаюсь, что это самая действенная мера. Но я имел"+ GetSexPhrase("","а") +" в виду нечто более практичное. Организовать погоню, к примеру.";
				link.l1.go = "GenQuest_Church_2_Start_5";
			break;

		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ах, "+ GetSexPhrase("сын мой","дочь моя") +", что может простой священник, связанный обетом непротивления злу? Эти негодяи наверняка уже далеко отсюда - пропивают в тавернах  награбленное, или предаются разврату и беспутству в объятиях блудниц! Надеюсь, там им и придет конец!";
				link.l1 = RandPhraseSimple("Хм, я уверен"+ GetSexPhrase("","а") +", что такой исход гораздо привлекательнее, нежели болтаться на рее. Впрочем, не буду вам мешать. Всего доброго.", "Хм, ну раз всем нам рано или поздно суждено отправиться к праотцам - от такого исхода и я бы не отказал"+ GetSexPhrase("ся","ась") +". Впрочем, мне уже пора. Желаю успехов в вашем нелёгком труде.");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + ", но ведь я никакими обетами не связан"+ GetSexPhrase("","а") +", и с готовностью помогу Господу приблизить час возмездия.";
				link.l2.go = "GenQuest_Church_2_Start_5_1";
			break;
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Я буду молиться за тебя," + GetSexPhrase("сын мой","дочь моя") + "! Иди и воздай этим мошенникам их заслугу!";
				link.l1 = "Можете не сомневаться, " + RandPhraseSimple("падре.", "святой отец.");
				link.l1.go = "GenQuest_Church_2_Start_6";
			break;

		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		//	AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			break;

		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Ну, разве всеблагой Создатель нашлёт мор и глад на неразумных детей своих, дабы покарать за грехи их тяжкие...";
				link.l1 = "Например, за гордыню, или, допустим, алчность... Что это вы так побледнели, Падре?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;

		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Господи Иисусе... помилуй мя, грешного... Вы нашли... грабителей? Вы их убили?";
					link.l1 = "Или возьмём десять заповедей, которые известны каждому доброму христианину с младенчества: не убий, не укради, не произноси лжесвидетельства против ближнего своего. Разве может нарушить их богобоязненный человек? А уж тем более, духовный пастырь?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "Здесь очень душно... Так вы нашли грабителей? Вы их убили?..";
					link.l1 = "Или возьмём десять заповедей, которые известны каждому доброму христианину с младенчества: не убий, не укради, не произноси лжесвидетельства против ближнего своего. Разве может нарушить их богобоязненный человек? А уж тем более, духовный пастырь?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
			break;

		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase("Сын мой, сударь","Дочь моя, сударыня") +"... Господи прости... такие деньги, такое искушение... слаб человек, слаб! Не устоял... Места себе не находил... Непрестанно возносил молитвы, исполнял епитимию, соблюдал строгий пост... умерщвлял плоть и, недостойный, просил небеса об одном лишь - чтобы живы остались те несчастные, которых ввёл во грех, движимый алчностью...";
				link.l1 = LinkRandPhrase("Святой Отец", "Падре", "Отче") + ", успокойтесь. Главное, что они никому ничего не рассказали... и не расскажут. Кстати, они добровольно отдали мне чашу для причастия, которую я вам и привез"+ GetSexPhrase("","ла") +".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
			break;

		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Благодарю тебя, Боже! Услышаны молитвы недостойного раба, оступившегося грешника, погрязшего в скверне и пороке...";
				link.l1 = "Оступиться может каждый... Однако, видя ваше искреннее раскаяние, я скажу так: человек вы неплохой, и священник хороший. Если вы пойдёте под суд, никому от этого пользы не будет. А уж оставаться или нет на службе Господу, это вы решите сами в ваших с Ним беседах...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
			break;

		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +"... Со слезами раскаяния и благодарности принимаю от вас чашу. Чистота и благородство вашей души потрясли меня. От всего сердца благословляю вас и умоляю принять это скромное вознаграждение в размере " + FindRussianMoneyString(iMoneyToCharacter) + "... Надеюсь, оно окупит ваши расходы?";
					// ГГ не берет деньги. Плюсанем репу
					link.l1 = "Это лишнее, отец " + NPChar.name + ". Я и так небед"+ GetSexPhrase("ен","на") +", а эти деньги используйте на благо ваших прихожан.";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
					// ГГ берет деньги
					link.l2 = "Благодарю, " + LinkRandPhrase("святой отец", "падре", "отче") + ", этого вполне достаточно.";
					link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +"... Со слезами раскаяния и благодарности принимаю от вас чашу, как знак Божьей милости и прощения. Чистота и благородство вашей души потрясли меня. От всего сердца благословляю вас!";
					link.l1 = "Спасибо за благословение, " + LinkRandPhrase("падре", "отче") + ".";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
					link.l1 = "Благословение, конечно, дело нужное, но неплохо бы подкрепить его чем-то более материальным, так как в дороге я понес"+ GetSexPhrase("","ла") +" немалые траты...";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}

			// Если будет чаша - здесь ее отбирать!
			ChurchGenQuest2_RemoveCup();
			break;

		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("cя","ась"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Ох, дитя моё, совсем забыл... Надеюсь, эта скромная лепта в размере " + FindRussianMoneyString(iMoneyToCharacter) + " окупит Ваши расходы?";
				link.l1 = "Да, " + LinkRandPhrase("падре", "отче") + ", спасибо.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
			break;

		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Я не понимаю ваших намёков, "+ GetSexPhrase("сын мой","дочь моя") +", о чём это вы говорите?!";
				link.l1 = "Я говорю о страшных вещах, которые способна сотворить с человеком жадность. И об этой чаше для причастия, которую я получил"+ GetSexPhrase("","а") +" от оборванцев, якобы ограбивших вашу церковь... Вы что-то хотели сказать?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
			break;

		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Я скажу, дитя моё, что вы весьма непочтительны с лицом духовного звания, и что вы можете об этом пожалеть. А эту чашу я впервые вижу, но если вы желаете пожертвовать её в пользу прихода, то...";
				link.l1 = "Полегче, падре, вы её не получите, пока не объяснитесь.";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
			break;

		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Что я должен вам объяснять?! Вы же "+ GetSexPhrase("умный человек","умная девушка") +", и сами должны понимать - всё, что наговорили эти проходимцы о том, что я их якобы нанял - это всё наглая ложь! Господь покарает этих безбожников не только за кощунство, но и за лжесвидетельство!";
					link.l1 = "Оставьте Господа в покое! Откуда вы знаете, что сказали мне те несчастные, на которых вы меня натравили? Может, я убил"+ GetSexPhrase("","а") +" их прежде, чем они успели поведать о ваших гнусных делишках?";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "Мне не о чем с вами говорить, вы не выполнили обязательства, взятого перед лицом Господа, сквернословите в храме, пытаетесь шантажировать священника, потрясая церковной утварью, которую заполучили неизвестно каким путём! И благодарите Бога, что я не зову послушников, чтобы задержать вас с поличным!";
					link.l1 = "Что ж... я вижу, вы погрязли в грехе настолько, что не боитесь людского суда. Но есть Высший Суд, перед которым все мы рано или поздно предстанем. Возьмите вашу 'церковную утварь' и подумайте о том, достойны ли вы прикасаться к ней, отец " + NPChar.name + ".";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
					link.l2 = "Простите мои сомнения, святой отец, ибо сердце человеческое слабо, а душа в смятении. Возьмите чашу и благословите меня.";
					link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
			break;

		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Э-э-э... "+ GetSexPhrase("Сын мой... Сударь... Господин","Дочь моя... Сударыня... Госпожа") +" " + PChar.name + "... я готов пойти вам навстречу... рассмотреть наши разногласия.... компенсировать ваши дорожные расходы вот этой скромной суммой в размере " + FindRussianMoneyString(iMoneyToCharacter) + "... конечно, в том случае, если вы не станете вмешивать в это дело посторонних...";
			// При этом варианте репу плюсуем
			link.l1 = "Я никого не собираюсь вмешивать. Забирайте чашу! И не думайте, что я возьму золото, которое вы тайком таскаете из карманов ваших прихожан!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Я никого не собираюсь вмешивать. Возьмите чашу! Это золото я беру лишь потому, что потратил"+ GetSexPhrase("","а") +" на вас слишком много времени и денег, но ничто не компенсирует моё глубокое разочарование в вас!";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";

			// Если будет чаша - здесь ее отбирать!
			break;

		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен","на"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("","ла"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен","на"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1":

		// ничего не принесли священнику.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
		{
			link.l1 = "Известия неутешительные, " + LinkRandPhrase("святой отец", "падре", "отче") + ": грабители оказались столь коварны и изворотливы, что мне не удалось вернуть церковное золото...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
			break;
		}

		// Принесли священнику только чашу.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
		{
			link.l1 = "Известия неутешительные, " + LinkRandPhrase("святой отец", "падре", "отче") + ": мне удалось настичь похитителей, но моим единственным трофеем оказалась вот эта чаша для причастия.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}

		// Принесли священнику и деньги и чашу.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
		{
			if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "Уверен"+ GetSexPhrase("","а") +", что известия вас обрадуют - я примерно наказал"+ GetSexPhrase("","а") +" грабителей и забрал"+ GetSexPhrase("","а") +" у них приходские деньги, а также вот эту чашу для причастия.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}

			// Деньги можно заныкать.
			link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + ", я принес"+ GetSexPhrase("","ла") +" дурные вести... Мне пришлось потратить много времени, сил и средств, чтобы выследить мерзавцев, но, когда я всё-таки добрал"+ GetSexPhrase("ся","ась") +" до них, оказалось, что они успели пропить и промотать всё, кроме вот этой чаши для причастия...";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}

		// Священник - вор.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
		{
			dialog.text = "Ах, "+ GetSexPhrase("сын мой","дочь моя") +", да что могло со мной случиться? Это ваш путь полон опасностей и тревог, а моя мирная келья - предел раздумий и молитв - как тихий остров в бушующем океане человеческих страстей...";
				link.l1 = "Неужели ничто не в силах поколебать покой вашего блаженного уединения?";
				link.l1.go = "GenQuest_Church_2_Thief_2";
			break;
		}

		// Короткий вариант прохождения квеста.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
		{
			if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "Уверен"+ GetSexPhrase("","а") +", что известия вас обрадуют - я примерно наказал"+ GetSexPhrase("","а") +" грабителей и привез"+ GetSexPhrase("","ла") +" приходские деньги.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}

			// Деньги можно заныкать.
			link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + "... Я вынужден"+ GetSexPhrase("","а") +" вас огорчить. Я преследовал"+ GetSexPhrase("","а") +" грабителей по всему архипелагу, преодолел"+ GetSexPhrase("","а") +" множество опасностей и преград, почти разорил"+ GetSexPhrase("ся","ась") +" и в конце-концов настиг"+ GetSexPhrase("","ла") +" их, но увы... они уже успели промотать церковные деньги.";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
		}

		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
		if(rand(1) == 0)	// Священник верит ГГ но не дает денег...
		{
			if(rand(4) == 3) // Более "мягкий" исход событий.
			{
				dialog.text = "Ох, "+ GetSexPhrase("сын мой","дочь моя") +". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру.";
					link.l1 = "Аминь, святой отец...";
					link.l1.go = "exit";
					sQuestTitle = NPChar.City + "ChurchGenQuest2";
					AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
					AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
					CloseQuestHeader(sQuestTitle);
					ChangeCharacterReputation(PChar, -2);
					DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", не лги духовному пастырю своему.";
					link.l1 = "Мне жаль, отче, но, клянусь всеми святыми - я говорю правду...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
			}
		}
		else
		{
			// Священник дает деньги ГГ...
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Ох, "+ GetSexPhrase("сын мой","дочь моя") +". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру. Однако ваши усилия и затраты должны быть вознаграждены, хоть и не принесли плодов. Возьмите эту небольшую сумму - " + FindRussianMoneyString(iMoneyToCharacter) + " -  и продолжайте ваш праведный путь!";
				link.l1 = "Э-хм!... Спасибо, падре, я направлю эти деньги на богоугодное дело.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
				link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + "... вы ставите меня в неловкое положение. Я не могу принять от вас вознаграждение за невыполненную работу, лучше обновите на эти деньги алтарь.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
		}
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
		if(rand(6) == 3)
		{
			dialog.text = "Хорошо, я тебе верю, "+ GetSexPhrase("сын мой","дочь моя") +". Господь подвергает нас очередному испытанию, чтобы укрепить нашу веру.";
				link.l1 = "Аминь...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
			break;
		}
			dialog.text = "Презренн"+ GetSexPhrase("ый","ая") +", неужели ты думал"+ GetSexPhrase("","а") +", что способ"+ GetSexPhrase("ен","на") +" обмануть Господа нашего? Будь ты проклят"+ GetSexPhrase("","а") +"! Убирайся прочь и помни, что эти деньги не принесут тебе никакой пользы!";
				link.l1 = "Как же так!.. падре!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterReputation(PChar, -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterReputation(PChar, -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Ох, "+ GetSexPhrase("сын мой","дочь моя") +". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру.";
					link.l1 = "Аминь, святой отец...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Да, это та самая чаша, которая пропала вместе с деньгами... Но... если вы добыли её, то почему не вернули и деньги? Там была немалая сумма, и простые мошенники не могли её так скоро потратить... "+ GetSexPhrase("Сын мой","Дочь моя") +", помните, что нет худшего греха, нежели лгать своему духовному пастырю, да ещё и лжесвидетельствовать во храме, перед ликом Господа!!";
					link.l1 = "Отец " + NPChar.name + ", я чуть жизни не лишил"+ GetSexPhrase("ся","ась") +", добывая эту вазу, думал"+ GetSexPhrase("","а") +" обрадовать вас, пусть не монетами, так хоть утварью. Я уже не говорю о своих расходах на это предприятие!";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Подите прочь, судар"+ GetSexPhrase("ь","ыня") +", и благодарите Создателя, который наградил меня мягким сердцем, ибо лишь по этой причине вы еще не объявлены вор"+ GetSexPhrase("ой","овкой") +" и мошенни"+ GetSexPhrase("ком","цей") +"!";
				link.l1 = "Как же так?! " + LinkRandPhrase("святой отец", "падре", "отче") + "!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Ох, "+ GetSexPhrase("сын мой","дочь моя") +". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру.";
				link.l1 = "Аминь, святой отец...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Боже, благодарю Тебя! Вы послужили орудием Господа, дитя моё! Я знал, что Отец наш небесный направит вас верным путём и не оставит своей помощью! Я непрестанно молился, и вот...";
				link.l1 = "Вообще-то, в таких делах больше пользы от оружия, чем от молитв, падре. Но, видимо, Бог действительно услышал ваши молитвы.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", я хочу вознаградить вас по достоинству, ибо вы"+ GetSexPhrase(", как истинный рыцарь Святой матери Церкви,","") +" приложили все силы и преодо...";
				link.l1 = "Святой отец, вы слишком преувеличиваете мои скромные заслуги. Оставляю вас возносить хвалу Господу...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

	//================================================================================================================


		case "donation":
			if (startherotype != 2 || IsEquipCharacterByItem(pchar, "glasses"))
			{
				dialog.Text = "Конечно, "+ GetSexPhrase("сын мой","дочь моя") +". Сколько ты желаешь пожертвовать Святой Церкви?";
				Link.l1 = "Простите, святой отец, но пожертвования не будет.";
				Link.l1.go = "No donation";
				if(makeint(PChar.money)>=100)
				{
					Link.l2 = "Моя лепта будет скромной. Всего 100 пиастров.";
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
			}
			else
			{
				dialog.Text = "Нет нужды. Одно ваше появление здесь уже стоит дороже любых денег.";
				Link.l1 = "Как знаешь. тогда еще вопрос...";
				Link.l1.go = "node_3";

			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Святой отец, я хочу сделать пожертвование не от себя. Я делаю это по поручению.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Хм... Это ваше решение, и вы вправе его изменить. Но не забывайте, что это зачтется вам на Страшном Суде.";
			Link.l1 = "И не только это. Давайте лучше сменим тему.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "От лица Святой Церкви благодарю вас, "+ GetSexPhrase("сын мой","дочь моя") +", за ваш дар.";
			Link.l1 = "Мне надо поговорить с вами, святой отец.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "От лица Святой Церкви благодарю вас, "+ GetSexPhrase("сын мой","дочь моя") +", за ваш дар.";
            Link.l1 = "Мне надо поговорить с вами, святой отец.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "От лица Святой Церкви благодарю вас, "+ GetSexPhrase("сын мой","дочь моя") +", за ваш дар.";
            Link.l1 = "Мне надо поговорить с вами, святой отец.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Конечно же, "+ GetSexPhrase("сын мой","дочь моя") +", я тебя слушаю.";
			link.l1 = "Я передумал"+ GetSexPhrase("","а") +". Может быть в другой раз.";
			link.l1.go = "exit";
			link.l2 = "Я так греш"+ GetSexPhrase("ен","на") +", святой отец. Чтобы перечислить все мои прегрешения, не хватит целого дня...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Все мы грешны, дитя моё...";
			link.l1 = "Да, но на моей совести тяжким бременем лежит груз тысяч смертей. Я грабил"+ GetSexPhrase("","а") +" и топил"+ GetSexPhrase("","а") +" корабли...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Я надеюсь, среди них не было таких, что ходили под флагом " + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = "Нет, конечно, святой отец.";
			link.l1.go = "ispoved_3";
			link.l2 = "Всякие были, святой отец... всякие.";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Тогда Господь простит тебе эти грехи. Ибо век наш жесток, и уничтожая недругов своего государя, ты спасаешь жизни верных его подданных.";
			link.l1 = "Спасибо, святой отец, вы меня очень утешили... я пойду.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Господь никогда не простит такого греха! Молись и кайся, кайся и молись! Одна тебе дорога - в монастырь!";
			link.l1 = "С монастырём придётся погодить. Не в этой жизни, по крайней мере. Прощайте...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Сожалею, "+ GetSexPhrase("сын мой","дочь моя") +", но сейчас все исповедальни заняты. Я буду рад выслушать твоё покаяние не раньше, чем через полчаса.";
				link.l1 = "Извините, " + RandPhraseSimple("падре", "святой отец") + ", это дело несколько иного характера. Отец " + PChar.GenQuest.ChurchQuest_1.PriestName + " из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " некогда поделился с вами бесценными сокровищами своей богословской библиотеки, а сейчас поручил мне заехать за ними, если будет оказия.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Какое дело привело тебя, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Я хотел"+ GetSexPhrase("","а") +" бы задать вам один вопрос, падре...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Я хочу поговорить о работе на благо церкви " + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        "Как идут дела в приходе, не нужна ли какая помощь?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Святой отец", "Падре") + ", я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о финансовых вопросах."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Я нуждаюсь в исцелении.";
                link.l4.go = "healthAdd_1";
				//Lipsar квест История давней дружбы
				if(CheckAttribute(PChar,"Luke.BadPoison"))
				{
						link.l4 = "Падре, помогите мне. Меня отравили каким-то очень сильным ядом, что мне делать?";
						link.l4.go = "LukePoison";
				}
            }
			// BlackThorn - Нежданное наследство
			if (CheckAttribute(PChar,"UnexpectedInheritance"))
            {
				if(!CheckAttribute(pchar, "UnexpectedInheritance_translator"))
				{
					link.l10 = "Святой отец, мне попал в руки один интересный текст. Он на латыни. Могу я попросить Вас сделать перевод?";
					link.l10.go = "UnexpectedInheritance_translate";
				}
				else
				{
					if(npchar.id == pchar.UnexpectedInheritance_translator && GetNpcQuestPastDayWOInit(npchar, "UnexpectedInheritance_translate") > 0 && sti(pchar.money) >= 1000)
					{
						link.l10 = "Святой отец, я по поводу перевода. И вот, пожалуйста, возьмите на нужды прихода.";
						link.l10.go = "UnexpectedInheritance_translate_end";
					}
				}
            }
            //==> Вставка Эдди, квест Аззи, возможность сдачи лампы.
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
                link.l6 = "Святой Отец, у меня есть вещь, которую я хочу отдать вам. Это странный жестяной сосуд, посмотрите.";
                link.l6.go = "GiveLamp";
            }
			//<== Вставка Эдди, квест Аззи возможность сдачи лампы.
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Святой отец", "Падре") + ", я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			//==> успокоить нечисть в пещерах
			if (CheckAttribute(npchar, "quest.DestroyGhost") && npchar.quest.DestroyGhost == "GoodResult")
			{
				switch (npchar.quest.DestroyGhost.label)
				{
					case "Пещера": sTemp = "пещера очищена"; break;
					case "пещера": sTemp = "пещера очищена"; break;
					case "Грот": sTemp = "грот очищен"; break;
					case "грот": sTemp = "грот очищен"; break;
					case "Подземелье": sTemp = "подземелье очищено"; break;
					case "подземелье": sTemp = "подземелье очищено"; break;
				}
				link.l5 = "Святой отец, " + sTemp + " от нечисти. Дело сделано, теперь жителей никто не побеспокоит.";
                link.l5.go = "GhostShip_S1";
			}
			//==> ночной сторож в церкви
			if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && pchar.questTemp.different.Church_NightGuard == npchar.location)
			{
	            link.l8 = RandPhraseSimple("Святой отец", "Падре") + ", я хочу отчитаться о поручении поработать в качестве ночного сторожа.";
	            link.l8.go = "NightGuard_result";
            }
			//<== ночной сторож в церкви
			link.l99 = "Я передумал"+ GetSexPhrase("","а") +", меня ждут дела.";
			link.l99.go = "exit";
		break;

		case "UnexpectedInheritance_translate":
			dialog.text = "Прошу прощения, но я оказываю такие услуги только своим друзьям и истинным верующим. Вас я не могу отнести ни к тем, ни к другим.";
			link.l1 = "Очень жаль.";
			link.l1.go = "exit";
			if (sti(pchar.reputation) > (REPUTATION_NEUTRAL + 10))  // кибальчиш
			{
				dialog.text = "Хорошо, я посмотрю. Приходите завтра, "+GetSexPhrase("сын мой","дочь моя")+", и не забывайте о нуждающихся.";
				SaveCurrentNpcQuestDateParam(npchar, "UnexpectedInheritance_translate");
				pchar.UnexpectedInheritance_translator = npchar.id;
				link.l1 = "Благодарю вас, святой отец.";
				link.l1.go = "exit";
			}

		break;

		case "UnexpectedInheritance_translate_end":
			dialog.text = "Благослови вас Господь. Вот, что у меня получилось.";
			link.l1 = "Спасибо, отче.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			UnexpectedInheritanceTranslatePart(pchar.UnexpectedInheritance);
			DeleteAttribute(pchar, "UnexpectedInheritance_translator");
			DeleteAttribute(pchar, "UnexpectedInheritance");

		break;

		case "prihod":
			//упокоение нечисти
			if (rand(2)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.DestroyGhost") && GetNpcQuestPastDayWOInit(npchar, "Ghost") > 7)
			{
                dialog.text = "Мне не совсем удобно об этом говорить, но у меня нет другого выхода. В жизни нет случайных вещей. И на всем лежит воля Всевышнего. Может быть, ты и есть то оружие Господне, которое необходимо нам для истребления нечисти, оскверняющей нашу землю.";
        		link.l1 = RandPhraseSimple("Мне не совсем понятно, святой отец, что вас так напугало? Чем вызван этот страх?",
                                            "Я прошу вас, продолжайте дальше, святой отец.");
        		link.l1.go = "DestroyGhost_1";
				SaveCurrentNpcQuestDateParam(npchar, "Ghost");
				npchar.quest.add = true;
				break;
			}
			//караулить церковь ночью
			if (!CheckAttribute(npchar, "quest.add") && rand(4)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.GuardNightChurch") && !CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && GetNpcQuestPastDayWOInit(npchar, "NightChurch") > 60 && GetHour() < 23)
			{
                dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", у меня есть для тебя несложное поручение. Нам нужен ночной сторож, но не старик с колотушкой и не беззащитная прихожанка. Все дело в том, что в последнее время 'братья' немного нервничают. Какие-то странные типы стали заходить в церковь, но не молятся, а только глазеют по сторонам...";
        		link.l1 = "И это вас беспокоит, святой отец?";
				link.l1.go = "NightChurch_1";
				SaveCurrentNpcQuestDateParam(npchar, "NightChurch");
				break;
			}
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        		dialog.text = "Это прекрасно. Однако в наши суровые дни, "+ GetSexPhrase("сын мой","дочь моя") +", не каждый пришедший в храм способен принести пользу матери нашей Церкви.";
						link.l1 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + ", я истинно верующ"+ GetSexPhrase("ий","ая") +" христиан"+ GetSexPhrase("ин","ка") +", и мои намерения послужить матери-Церкви - искренни."+ GetSexPhrase(" Кто же станет её опорой, если не такие верные рыцари, как я?","") +"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
            dialog.text = "У нас в приходе все спокойно, "+ GetSexPhrase("сын мой","дочь моя") +". Спасибо за предложение.";
    		link.l2 = "Ну, раз все хорошо, я пойду по своим делам.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;

		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Ну что ж, есть у меня одно деликатное поручение, исполнение которого потребует не только чистоты помыслов, но и немалой храбрости, а также тонкости ума...";
				link.l1 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + ", я буду счастлив"+ GetSexPhrase("","а") +" оказать вам любую услугу, даже если для этого мне придётся проскользнуть в саму преисподнюю! Не в церкви будь сказано.";
				link.l1.go = "GenQuest_Church_1_Start_2";
			break;

		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Вот как! Это хорошо... Но дело крайне деликатное... Некоторое время назад настоятель церкви " + PChar.GenQuest.ChurchQuest_1.ToName + " из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + ", что на " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Dat") + " попросил у меня на время несколько богословских трудов и древних рукописей из церковной библиотеки. Так как просьба была подкреплена требованием архиепископа не препятствовать распространению благостного света знаний, отказать я не мог, хотя и предполагал, что сложность морских путешествий не позволит ему вернуть рукописи в срок...\nНе могли бы вы поспособствовать разрешению этой проблемы?";
			link.l1 = "Боюсь, " + LinkRandPhrase("падре", "святой отец", "отец мой") + ", что не оправдаю вашего доверия. Дело слишком деликатное, и для его решения нужно быть изрядным дипломатом.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + ", ваше поручение не представляется мне сложным. Я сегодня же отправлюсь в путь.";
			link.l2.go = "GenQuest_Church_1_Start_3";
			break;

		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
			break;

		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "О!.. Да... Действительно, припоминаю... Но, "+ GetSexPhrase("сын мой","дочь моя") +", эти сокровища более духовны, нежели материальны, они принесли неизмеримую пользу моим прихожанам и могли бы приносить её впредь!";
				link.l1 = "Однако, " + LinkRandPhrase("падре", "святой отец", "отец мой") + ", души прихожан отца " + PChar.GenQuest.ChurchQuest_1.PriestName + " столь же нуждаются в спасении, а без этих трудов он лишён поддержки столпов теософии и вдохновения в своих проповедях.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "О, да!.. Действительно... "+ GetSexPhrase("Сын мой","Дочь моя") +", эти сокровища более духовны, нежели материальны, они принесли столько пользы моим прихожанам, что я, к стыду своему, несколько задержался с их возвращением владельцу...";
				link.l1 = "Именно, " + RandPhraseSimple("падре", "святой отец") + ", именно. Поэтому отец " + PChar.GenQuest.ChurchQuest_1.PriestName + " и поручил мне доставить эти книги лично ему в руки.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;

		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Я понимаю, дитя моё, но разве не возносим мы каждодневно молитву Господу: 'и прости нам, как мы прощаем должникам нашим'? А ведь церковь " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " неизмеримо богаче моего скромного прихода.";
			link.l1 = "Да, святой отец, вы правы, но в голову мне пришли другие библейские строки: 'не ищи лёгких путей, ибо на них подстерегает нас Диавол, и голос его тем вкрадчивей, а соблазн тем сильнее, чем легче путь!' А падре " + PChar.GenQuest.ChurchQuest_1.PriestName + " уже намеревался архиепископу доложить о вашей забывчивости, едва я его отговорил"+ GetSexPhrase("","а") +", предложив свою помощь.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;

		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "А-а-архиепископу?! О такой мелочи!.. Ну зачем же, зачем же? Я и сам давно хотел отослать эти труды любезному брату моему во Христе, да как-то всё не попадалось надёжной оказии. Но в тебе, "+ GetSexPhrase("сын мой","дочь моя") +", я узрел достойного слугу Божьего. Вот, вручаю книги и рукописи, доставь их отцу " + PChar.GenQuest.ChurchQuest_1.PriestName + " в целости и сохранности и присовокупи мою глубочайшую благодарность.";
			link.l1 = "Всенепременнейше присовокуплю, " + LinkRandPhrase("падре", "святой отец", "отче") + ". Всенепременнейше.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;

		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
			break;

		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "officer_" + (rand(63)+1), "man", "man", 15, NPChar.nation, -1, true));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade24", "pistol3", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS24, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
		//	sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1"; // Выставляем ноду диалога на палубе корабля
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа

			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Но, "+ GetSexPhrase("сын мой","дочь моя") +"... Дело в том, что на прошлой неделе мне довелось встретиться с капитаном судна '" + sld.Ship.Name + "', куда меня призвали для причащения умирающего матроса. К моей великой радости капитан " + GetFullName(sld) + " сообщил, что направляется в " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". И хотя он не ручался за сроки, однако согласился помочь, уверив меня, что в порт " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " он непременно зайдёт. Конечно же, я воспользовался оказией, отослал книги с этим добрым человеком и вручил их дальнейшую судьбу Господу.";
					link.l1 = "Хм, а вы уверены, что этому капитану можно доверять?.. Достаточно ли он уразумел ценность вверенных ему трудов и важность возложенного поручения?";
					link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Ах, "+ GetSexPhrase("сын мой","дочь моя") +"! Вы опоздали буквально на несколько часов! Я уже отправил книги Отца " + PChar.GenQuest.ChurchQuest_1.PriestName + " с капитаном " + PChar.GenQuest.ChurchQuest_1.CapFullName + ". Утром этот богобоязненный человек пришёл на исповедь и обмолвился, что сегодня его судно отправляется в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". И хотя господин капитан не ручался за сроки, однако согласился помочь, уверив меня, что в порт " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " он непременно зайдёт.";
					link.l1 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + "... а вы уверены, что этому капитану можно доверять?.. И еще я хотел"+ GetSexPhrase("","а") +" бы узнать, как называется его судно.";
					link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
			break;

		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Я верю людям, "+ GetSexPhrase("сын мой","дочь моя") +", ведь все мы созданы по образу и подобию, и в каждой душе горит искра Божия!";
				link.l1 = "М-да. Это веский аргумент. Ну что ж... благословите меня, святой отец, и пожелайте удачи в поисках этого капитана.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
			break;

		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Нужно верить людям, "+ GetSexPhrase("сын мой","дочь моя") +". А про корабль я, к сожалению, ничего сказать не могу.";
				link.l1 = "И вы отдали ценные рукописи капитану, даже не потрудившись узнать название его судна?!!";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Видите ли, "+ GetSexPhrase("сын мой","дочь моя") +", капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + " очень богобоязненный че...";
				link.l1 = "Это я уже слышал"+ GetSexPhrase("","а") +", " + LinkRandPhrase("падре", "святой отец", "отче") + ".";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Терпение, "+ GetSexPhrase("молодой человек","девушка") +"! Капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + " очень богобоязнен, а его судно до нынешнего дня называлось таким словом, что священнослужителю не потребно произносить его даже мысленно! Сегодня на исповеди я указал заблудшей душе на это упущение. Ибо, согласно Библии, чистота духа должна блюстись нами, грешными, пуще чистоты тела, ибо Господь наш преградил сквернословам путь в царствие небе...";
				link.l1 = "Я понял"+ GetSexPhrase("","а") +", " + LinkRandPhrase("падре", "святой отец", "Отче") + ", я понял"+ GetSexPhrase("","а") +"! Богобоязненный капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", известный всем Карибам картежник и пьяница, благодаря вашему внушению решился переименовать своё корыто?..";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Ты очень проницател"+ GetSexPhrase("ен","ьна") +", "+ GetSexPhrase("сын мой","дочь моя") +". Нового имени корабля я не знаю, но, несомненно, это будет нечто возвышенное.";
				link.l1 = "Ох, " + RandPhraseSimple("падре", "святой отец") + "... благодарю вас за всё. И помолитесь за мою грешную душу...";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			break;

		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Ах, дитя моё! Я истово молился, и вот всё разрешилось как нельзя лучше! За твою помощь и рвение, "+ GetSexPhrase("сын мой","дочь моя") +", тебя несомненно ждут райские кущи и ангельское пе...";
				link.l1 = RandPhraseSimple("Падре", "Отче") + ", на свидание со Святым Петром я пока, слава Создателю, не собираюсь. А живым, кроме обещаний райской благодати, надобно много разных материальных вещей...";
				link.l1.go = "GenQuest_Church_1_Complete_2";
			break;

		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Да-да, "+ GetSexPhrase("сын мой","дочь моя") +", да-да. Я вознагражу тебя по достоинству. Вот, возьми это, и помни, что Бог наказывает тех неразумных, которые чрезмерно пекутся о благах земных и поклоняются желтому дьяволу!";
				link.l1 = "Благодарю, " + LinkRandPhrase("падре", "святой отец", "отец мой") + ". Возьмите ваши долгожданные книги и рукописи, и помолитесь за мою грешную душу... Прощайте";
				link.l1.go = "GenQuest_Church_1_Complete_3";
			break;

		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			//PChar.GenQuest.ChurchQuest_1.AwardSumm = (rand(8) + 2) * 500;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterReputation(PChar, 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			//AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_1.AwardSumm));
			TakeNItems(pchar, "chest", 3+drand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			break;
		// <-- Church GenQuest_1

		//--->> успокоить нечисть
		case "DestroyGhost_1":
			npchar.quest.DestroyGhost = "toCave"; //личный флаг священника на взятый квест
			//получим пещеру для чистки
			sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace)-1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			npchar.quest.DestroyGhost.locationId = GetAttributeName(aPlace_2); //Id целевой пещеры
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			npchar.quest.DestroyGhost.label = GetConvertStr(sld.id.label, "LocLables.txt"); //тип подземелья для диалогов
			switch (npchar.quest.DestroyGhost.label)
			{
				case "пещера": sTemp = "Дело в том, что пещера, находящаяся возле нашего города, стала прибежищем нечисти!"; break;
				case "Пещера": sTemp = "Дело в том, что пещера, находящаяся возле нашего города, стала прибежищем нечисти!"; break;
				case "грот": sTemp = "Дело в том, что грот, находящийся возле нашего города, стал прибежищем нечисти!"; break;
				case "Грот": sTemp = "Дело в том, что грот, находящийся возле нашего города, стал прибежищем нечисти!"; break;
				case "подземелье": sTemp = "Дело в том, что подземелье, находящееся возле нашего города, стало прибежищем нечисти!"; break;
				case "Подземелье": sTemp = "Дело в том, что подземелье, находящееся возле нашего города, стало прибежищем нечисти!"; break;
			}
			dialog.text = "Все больше и больше людей рассказывают о страшных происшествиях. " + sTemp + " Оттуда на свет Божий лезут такие твари, что и в страшном сне не приснятся. Люди напуганы, страх проникает в их сердца...";
			link.l1 = "Чем я могу вам помочь, святой отец?";
			link.l1.go = "DestroyGhost_2";
		break;
		case "DestroyGhost_2":
			dialog.text = "Вы - "+ GetSexPhrase("смелый человек","храбрая девушка") +". Станьте орудием Господа в моих руках! Уничтожьте нечисть! И даровано вам будет отпущение грехов ваших...";
			link.l1 = "Я готов"+ GetSexPhrase("","а") +", падре!";
			link.l1.go = "DestroyGhost_3";
			link.l2 = "Святой отец, я не могу принять ваше предложение. Как-нибудь в другой раз.";
			link.l2.go = "DestroyGhost_out";
		break;
		case "DestroyGhost_out":
			dialog.text = "Плохо, "+ GetSexPhrase("сын мой","дочь моя") +", очень плохо. Я надеялся на тебя!";
			link.l1 = "Я думаю, все уладится со временем...";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.DestroyGhost");
			ChangeCharacterReputation(pchar, -3);
		break;
		case "DestroyGhost_3":
			dialog.text = "Очень хорошо, "+ GetSexPhrase("сын мой","дочь моя") +". Отправляйся туда, и да пребудет с тобой сила!";
			link.l1 = "Все будет в порядке, святой отец.";
			link.l1.go = "exit";
			pchar.questTemp.different = "DestroyGhost";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			//флаг квеста на локацию, сюда же пишем индекс дающего священника
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sld.DestroyGhost = npchar.index;
			LAi_LocationResetMonGenTimer(sld.id);
			sTitle = sld.id + "Church_DestroyGhost";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "1");
			AddQuestUserDataForTitle(sTitle, "sLocation", GetStrSmallRegister(npchar.quest.DestroyGhost.label));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sLocation", npchar.quest.DestroyGhost.label);
		break;

		case "GhostShip_S1":
			dialog.text = "Отлично, "+ GetSexPhrase("сын мой","дочь моя") +"! Ты сделал"+ GetSexPhrase("","а") +" богоугодное дело. Знай, что отношение к тебе " + NationNameGenitive(sti(NPChar.nation)) + " станет лучше.";
			link.l1 = "Я счастлив"+ GetSexPhrase("","а") +", падре...";
			link.l1.go = "GhostShip_S2";
		break;
		case "GhostShip_S2":
			dialog.text = "Я буду молиться за тебя. Иди "+ GetSexPhrase("сын мой","дочь моя") +", и будь чест"+ GetSexPhrase("ен","на") +" перед своей совестью и Господом нашим.";
			link.l1 = "Хорошо, святой отец.";
			link.l1.go = "exit";
			switch (npchar.quest.DestroyGhost.label)
			{
				case "Пещера": sTemp = "пещеру"; break;
				case "пещера": sTemp = "пещеру"; break;
				case "Грот": sTemp = "грот"; break;
				case "грот": sTemp = "грот"; break;
				case "Подземелье": sTemp = "подземелье"; break;
				case "подземелье": sTemp = "подземелье"; break;
			}
			AddSimpleRumourCity(LinkRandPhrase("Наш святой отец, " + GetFullName(npchar) + ", рассказал о том, что вы очистили от нечисти " + sTemp + " близ нашего города. Богоугодное дело, скажу я вам...",
				"Вы слышали, "+ GetSexPhrase("некий капитан","некая девушка") +" по просьбе нашего святого отца очистил"+ GetSexPhrase("","а") +" от демонов " + sTemp + " рядом с нашим городом."+ GetSexPhrase(" Каков храбрец!","") +"",
				""+ GetSexPhrase("Капитан","Девушка") +", это вы очистили " + sTemp + " рядом с нашим городом от нечисти? Знайте, что мы все вам очень благодарны!"), npchar.city, 10, 1, "");
			ChangeCharacterReputation(pchar, 5);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sTitle = sld.id + "Church_DestroyGhost";
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader(sTitle);

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

			DeleteAttribute(npchar, "quest.DestroyGhost");
			//#20170727-01 Bug fix church skeleton quest infinite reputation
			//Attribute set in SetSkeletonsToLocation, QuestsUtilite.c
			DeleteAttribute(npchar, "DestroyGhost");
		break;
        //<<--- успокоить нечисть
		//--->> ночной сторож
		case "NightChurch_1":
			dialog.text = "Именно так. И поверь мне, что это неспроста. Когда происходят такие вещи, то это является верным признаком грядущего ограбления. Судя по всему, кому-то приглянулась церковная утварь\nНу что, ты соглас"+ GetSexPhrase("ен","на") +" провести несколько ночей в церкви?";
			link.l1 = "Нет, пожалуй, откажусь, святой отец. Прошу меня извинить.";
			link.l1.go = "exit";
			link.l2 = "В принципе, я соглас"+ GetSexPhrase("ен","на") +". Но сколько ночей мне надо будет охранять церковь? Может, никто и не появится, а ваши странные типы - обычные головорезы, которые просто стесняются на людях проявлять свои религиозные чувства.";
			link.l2.go = "NightChurch_2";
		break;
		case "NightChurch_2":
			dialog.text = "Хм, может и так, но это маловероятно. В общем, тебе нужно будет находиться здесь три ночи. Если никто так и не появится, то будем считать, что твоя работа выполнена успешно.";
			link.l1 = "Что же, это меня устраивает. Я соглас"+ GetSexPhrase("ен","на") +"!";
			link.l1.go = "NightChurch_3";
		break;
		case "NightChurch_3":
			dialog.text = "Тогда приступай с сегодняшней ночи. И помни, что ты долж"+ GetSexPhrase("ен","на") +" находится в церкви безотлучно с полуночи до шести утра.";
			link.l1 = "Ясно, святой отец. Три ночи можете быть спокойны за свою утварь.";
			link.l1.go = "exit";
			pchar.questTemp.different = "Church_NightGuard";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			pchar.questTemp.different.Church_NightGuard = npchar.location; //флаг срабатывания нуля часов
			pchar.questTemp.different.Church_NightGuard.NightQty = 0; //кол-вот отработанных ночей
			pchar.questTemp.different.Church_NightGuard.chance = rand(3); //рендом на появление грабителей
			pchar.questTemp.different.Church_NightGuard.fight = false; //флаг боевки
			SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //запишем дату
			sTitle = npchar.location + "Church_NightGuard";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_NightGuard", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "NightGuard_result":
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0)
			{
				dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", ты еще не сторожил"+ GetSexPhrase("","а") +" ни одной ночи. Иди, выполняй свою работу, не мешай мне...";
				link.l1 = "Хорошо, святой отец.";
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) > 0 && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", ты не выполнил"+ GetSexPhrase("","а") +" работу до конца, мы договаривались о трех ночах...";
				link.l1 = "Да, я помню... Продолжу сторожить.";
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
			{
				if (sti(pchar.questTemp.different.Church_NightGuard.fight))
				{
					dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", мне уже известно о том, что ты сумел"+ GetSexPhrase("","а") +" поймать церковных воров. И хоть убийство в стенах храма Господня - грех, но Господь отпускет тебе его.";
					link.l1 = "Спасибо, святой отец...";
					link.l1.go = "NightGuard_fight";
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", ты честно продежурил"+ GetSexPhrase("","а") +" в церкви по ночам. Ничего странного не видел"+ GetSexPhrase("","а") +"?";
					link.l1 = "Нет, святой отец, все было спокойно. Никого не видел"+ GetSexPhrase("","а") +" вообще.";
					link.l1.go = "NightGuard_noLook";
				}
			}
		break;

		case "NightGuard_noLook":
			dialog.text = "Хм, похоже, мы ошибались... Ну что же, прекрасный результат! В качестве награды я не предлагаю тебе денег, но могу сказать, что грехи твои перед Господом нашим и " + NationNameAblative(sti(npchar.nation)) + " будут уменьшены.";
			link.l1 = "Спасибо, святой отец.";
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddSimpleRumourCity(LinkRandPhrase("Говорят, что вы дежурите в нашей церкви по ночам...",
				"Ночное дежурство в церкви - дело богоугодное. Спасибо вам.",
				"Наш святой отец, " + GetFullName(npchar) + ", упомянул, что вы несли караул по ночам в нашей церкви."), npchar.city, 10, 1, "");
		break;
		case "NightGuard_fight":
			dialog.text = "Помимо этого, я в силах уменьшить твои грехи перед " + NationNameAblative(sti(npchar.nation)) + ", что и сделаю. К тому же, я буду молиться за твое здоровье, и, полагаю, скоро ты почувствуешь исцеляющую силу молитвы Господу нашему!";
			link.l1 = "Огромное спасибо, святой отец!";
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddCharacterMaxHealth(pchar, 2);
			AddSimpleRumourCity(LinkRandPhrase("Говорят, что вы ночью вы поймали бандитов в нашей церкви! Огромное вам спасибо!",
				"Вы знаете, все жители города благодарны вам за то, что вы не допустили разорение нашей церкви. Спасибо вам!",
				"Наш святой отец, " + GetFullName(npchar) + ", только о том и говорит, как вы спасли нашу церковную утварь той ночью..."), npchar.city, 10, 1, "");
		break;

		//<<--- ночной сторож
		//Lipsar квест История давней дружбы
		case "LukePoison":
			dialog.text = GetSexPhrase("Сын мой","Дочь моя") +", дай мне тебя осмотреть... Господи помилуй! Мне не известен этот яд, я никогда с таким не сталкивался. Тебе нужно срочно найти того, кто поможет тебе, иначе твоё здоровье не поправится никогда!";
			link.l1 = "Очень жаль, падре, что вы не можете мне помочь.";
			link.l1.go = "exit";
			if (NPChar.City == "Bridgetown")
			{
				dialog.text = GetSexPhrase("Сын мой","Дочь моя") +", дай мне тебя осмотреть... Господи помилуй! Я знаю, что это за яд! Он очень опасен, нужно немедленно начинать лечение! Я помогу тебе.";
				link.l1 = "Чего же мы ждём?! Я с радостью приму вашу помощь!";
				link.l1.go = "exit";
				AddDialogExitQuest("HealingPoison");
			}
		break;
        case "healthAdd_1":
            if (GetHealthMaxNum(pchar) == 6) // отлично
            {
                dialog.text = "Здоровье твое " + GetHealthNameMaxSmall(pchar) + ", а раны заживут сами. Нужно просто избегать кровопролития и поберечь своё здоровье.";
    			link.l1 = "Спасибо, обнадежили. Постараюсь некоторое время не ввязываться в драки.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Здоровье твое " + GetHealthNameMaxSmall(pchar) + ", и хоть раны заживут сами, тебе не помешает его поправить.";
    			link.l1 = "Что для этого нужно?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "А почему вообще мое здоровье портится?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "Очень просто, "+ GetSexPhrase("сын мой","дочь моя") +", ты получаешь урон, когда тебя ранят. Это не проходит бесследно, здоровье твое подрывается каждой раной, и в результате ты становишься слаб"+ GetSexPhrase("","а") +" и фехтовать уже не в силах.\n Команда твоя, видя слабость вожака, теряет к тебе уважение. Но зато ты делаешься более осторожным и умение защиты временно увеличивается. Своевременный отдых и минимизация ранений помогут оставаться всегда полным сил.";
			link.l1 = "Спасибо, вы меня просветили.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Молитвы и отказ от насилия, "+ GetSexPhrase("сын мой","дочь моя") +". Тогда Господь вернет тебе утерянное тобой.";
			link.l1 = "А вы не могли бы помолится за меня?";
			link.l1.go = "healthAdd_3";
			link.l2 = "То есть - никак? Хм.. обнадежили, спасибо.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Я? Пожалуй, это возможно. Но тебе придеться внести подаяние в наш приход.";
    			link.l1 = pcharrepphrase("Сколько?", "С радостью! Каков его размер?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Я уж как-нибудь сам"+ GetSexPhrase("","а") +"...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", я уже молюсь о твоем благополучии. Молитвы займут все мое время до конца месяца.";
    			link.l1    = "Спасибо, "+RandPhraseSimple("падре.", "святой отец.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Сто тысяч золотом будет вполне достаточной платой за чудо исцеления.";
			link.l1 = pcharrepphrase("Сколько!!! Да вы в своём уме?! Я заплачу такую сумму, когда разграблю пару церквей.", "Для меня это слишком много. Видно правду говорят - здоровье за деньги не купишь.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Я соглас"+ GetSexPhrase("ен","на") +"!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Хорошо. Твое здоровье немного улучшится. Но тебе нужно избегать стычек и беречь себя, иначе эффект сойдет на нет. Мне нужно целый месяц провести в молитвах о твоем бренном теле.";
			link.l1 = "Спасибо. Если что, я зайду через месяц снова.";
			link.l1.go = "exit";
		break;
		// диалог для капелата из тюряги
		case "Prison_Temp":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = "Нам не о чем более говорить.";
			link.l1 = "Да и не нужно.";
			link.l1.go = "Exit";
		break;

		case "Prison_Cell":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = "Заблудшая душа, не хочешь ли ты покаятся в грехах своих, очистить душу и облегчить участь свою?";
			link.l1 = "А вы, собственно, кто?";
			link.l1.go = "Prison_Cell_Info";
			link.l2 = "С готовностью и смирением, падре.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "Убирайся прочь, святоша.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info":
			dialog.text = "Я местный капеллан, облегчаю участь узников, исповедую до и отпеваю после исполнения смертного приговора, или напутствую перед долгой дорогой на рудники.";
			link.l1 = "А другой выбор кроме каторги и расстрела бывает?";
			link.l1.go = "Prison_Cell_Info_2";
			link.l2 = "Я готов"+ GetSexPhrase("","а") +" покаяться, падре.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "Я совершенно не винов"+ GetSexPhrase("ен","на") +". Мне это все не нужно.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info_2":
			dialog.text = "Конечно, "+ GetSexPhrase("сын мой","дочь моя") +", не все доживают до вынесения приговора, многим казематы остаются вечным приютом. Готов"+ GetSexPhrase("","а") +" ли ты поведать о своих грехах?";
			link.l2 = "Я готов"+ GetSexPhrase("","а") +" покаяться, падре.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "Я совершенно не винов"+ GetSexPhrase("ен","на") +". Мне это все не нужно.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_None":
			dialog.text = "Упорство в ереси и отступничество никогда не приведут тебя в Царствие Божие. Охолонись и покайся!";
			link.l1 = "Я настаиваю, мне это не нужно. Подите прочь!";
			link.l1.go = "Prison_Cell_death";//"Exit";
			//AddDialogExitQuest("MoveToPrison_Cell");
		break;

		case "Prison_Cell_Talk":
			dialog.text = "Я слушаю тебя, "+ GetSexPhrase("сын мой","дочь моя") +".";
			link.l2 = "Я греш"+ GetSexPhrase("ен","на") +", падре, многие злодеяния на моем счету, я грабил"+ GetSexPhrase("","а") +" и убивал"+ GetSexPhrase("","а") +" невинных, но действовал"+ GetSexPhrase("","а") +" я не од"+ GetSexPhrase("ин","на") +". Мне помогали верные соратники. Вы можете передать им от меня весточку?";
			link.l2.go = "Prison_Cell_Talk_2";
			link.l3 = "Я передумал"+ GetSexPhrase("","а") +". Оставьте меня.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Talk_2":
			dialog.text = "Так ты еще и главарь преступников? И просишь меня пособничать твоим коварным планам? Не бывать этому! Я немедля буду настаивать на твоем приговоре.";
			link.l1 = "Ну и дурак же ты, а еще рясу нацепил!";
			link.l1.go = "Prison_Cell_death";
		break;

		case "Prison_Cell_death":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   			sld = &Characters[sti(PChar.GenQuest.ToPrisonCmdIdx)];
			// to_do DeathExecutionStart(Pchar, sti(sld.nation));
		break;
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "И кто же эта добрая душа, что жертвует?";
			link.l1 = "Хм... Это хозяйка местного борделя.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "Я бы предпоч"+ GetSexPhrase("ел","ла") +" не называть имен. Ведь может же быть анонимное пожертвование!";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5))
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Сам"+ GetSexPhrase("","а") +" грешни"+ GetSexPhrase("к","ца") +", еще за грешницу и просишь? О своей душе подумал"+ GetSexPhrase("","а") +" бы лучше, ведь все мы перед Господом предстанем!";
					link.l1 = "Это точно. Надеюсь, Господь будет милостив ко мне... Так как насчет пожертвования?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Изыди, сатана!!! Забирай свои нечестивые деньги и убирайся отсюда!";
					link.l1 = "Святой отец, как же так?! Мы к вам со всей душой, а вы...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Я рад, что ты помогаешь грешникам обрести путь к Господу нашему. За это тебе воздастся на небесах!";
					link.l1 = "Это было бы здорово! Так что насчет пожертвования?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Я не могу принять деньги, добытые во грехе. Верни их этой блуднице, "+ GetSexPhrase("сын мой","дочь моя") +". Через деньги пути к Господу не отыскать.";
					link.l1 = "Очень жаль, что вы отвергаете ее. Очень жаль...";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Взять эти деньги, даже не зная, от кого они...";
				link.l1 = "Да, падре, именно так. Примите пожертвование от чистого сердца!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Взять эти деньги, даже не зная, от кого они? Ты с ума сош"+ GetSexPhrase("ел","ла") +"?! А вдруг, на этих деньгах - кровь!!";
				link.l1 = "Святой отец, на всех деньгах - кровь...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Я принимаю его, "+ GetSexPhrase("сын мой","дочь моя") +". Пойди, можешь передать это блуднице.";
			link.l1 = "Хорошо, падре. Спасибо.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_ok_1":
			dialog.text = "Я принимаю его, "+ GetSexPhrase("сын мой","дочь моя") +". Можешь передать подающему.";
			link.l1 = "Хорошо, падре. Спасибо.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_bad":
			dialog.text = "Убирайся, исчадие ада!!! И не смей показываться мне на глаза!";
			link.l1 = "Хех, ну хорошо.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_1":
			dialog.text = "Таково мое решение. Иди с миром, "+ GetSexPhrase("сын мой","дочь моя") +".";
			link.l1 = "Прощайте, падре.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_2":
			dialog.text = "Это ты так думаешь, нечестив"+ GetSexPhrase("ец","ая") +"! Убирайся из храма и не показывайся мне на глаза!";
			link.l1 = "Так? Да пожалуйста, уйду...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		//зачарованный город. базар падре в Каракасе
		case "MC_CaracasChirch":
			dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", Церковь спасает заблудших. Оборотней, ведьм и колдунов наставляет на путь истинный Святая Инквизиция. Или простые горожане, если Господь изберет их своим орудием. Кто мы такие, чтобы вмешиваться?";
			link.l1 = "Но если он и правда не виновен? Странно: мне"+ GetSexPhrase(", корсару,","") +" приходится взывать к совести священника!";
			link.l1.go = "MC_CaracasChirch_1";
		break;
		case "MC_CaracasChirch_1":
			dialog.text = "Не горячитесь, "+ GetSexPhrase("сын мой","дочь моя") +". Если его душа невинна, то она попадет в рай! Но если я исповедую исчадие ада\nВпрочем, есть способ проверить. Дьявольское отродье не сможет войти в храм Божий. Если вы приведете его сюда, и не поразит его кара небесная - конечно, я не откажу ему в исповеди.";
			link.l1 = "Я приведу его!";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toCaracasTavern";
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.lifeDay = 0;
			}
			//дым от костра
			locations[FindLocation("Caracas_town")].hidden_effects = true;
		break;

	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr);
	//string sColony = FindNonEnemyColonyForAdventure(GetCityNation(PChar.GenQuest.ChurchQuest_1.QuestTown), PChar.GenQuest.ChurchQuest_1.QuestTown, true);
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;

	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2А (просто забрать у священника рукописи).");
		break;

		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-А (поиск кэпа. О нем есть полная инфа).");
		break;

		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-Б (поиск кэпа. Название шипа неизвестно.)");
		break;
	}
}
