// boal 25/04/04 общий диалог горожан
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	String attrLoc = Dialog.CurrentNode;

	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":

            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Шпион? Стража!!!!!", "Караул! В городе враг!");
				link.l1 = "Заткнись! Я уже ухожу.";
				link.l1.go = "fight";
				break;
			}*/

            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase("Меня зовут ", "Мое имя ", "Можешь называть меня ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". Чего тебе нужно?", ". Я тебя раньше здесь не "
                                +NPCharSexPhrase(NPChar, "видел", "видела")
                                +", кто ты так"+ GetSexPhrase("ой","ая") +"?", ". Кто ты и что тебе от меня надо?"),

        		                LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Мое имя " + GetFullName(npchar) + ". А как зовут вас?",
                                 "Здравствуйте, " + GetAddress_Form(NPChar) + "! Я " + GetFullName(npchar) + ". Могу я узнать ваше имя?",
                                 "Да, " + GetAddress_Form(NPChar) + ". Что вы хотели? Кстати, меня зовут " + GetFullName(npchar) + ". А вас?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("Разрази меня гром! ", "Тысяча чертей! ", "Чтоб тебе пусто было! ") + "Да я капитан "+ GetFullName(Pchar)+ LinkRandPhrase(", ты разве не слыхал"+NPCharSexPhrase(NPChar,"","а")+" обо мне"+NPCharSexPhrase(NPChar,", каналья?","?"), " и "+ GetSexPhrase("самый известный пират","самая известная женщина-пират") +" в этих водах! ", " и провалиться мне на этом месте, если это не так!"),
                                LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан " + GetFullName(Pchar)));

                //LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				link.l1 = PCharRepPhrase("Хотел"+ GetSexPhrase("","а") +" кое-что узнать об этом городишке!", "Хотел"+ GetSexPhrase("","а") +" узнать кое-что о городе.");
				link.l1.go = "new question";
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l2 = LinkRandPhrase("Ты в курсе", "Ты знаешь", "Ты знаешь что-нибудь о том") + ", что недавно была ограблена местная церковь?");
					link.l2.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.

                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("А, это ты "+GetFullName(Pchar)
                        +" "+ GetSexPhrase("- старый пройдоха","- отчаянная деваха") +"", "Рад тебя видеть, "+ GetSexPhrase("старина","красавица") +" "
                        + Pchar.name, "О, да это же "+ GetSexPhrase("сам капитан","сама") +" "
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(". Думал, тебя уже нет на этом свете!", ". И, наверное, "+ GetSexPhrase("как всегда пьян.","уже слегка навеселе.") +"", ". И, как вижу, еще на свободе!")
                                        +LinkRandPhrase(" Ну, говори, чего тебе нужно?", " Чего тебе на этот раз?", " Опять тревожишь меня по пустякам?"),
                                        LinkRandPhrase(TimeGreeting() + ", капитан ", "Здравствуйте, "+GetAddress_Form(NPChar)+" ", "Приветствую вас, капитан ")+GetFullName(Pchar)
                                        +LinkRandPhrase(". Что может быть нужно "+ GetSexPhrase("такому почтенному человеку","такой бравой девушке") +", как вы, от меня?", ". Зачем вы пришли?", ". Что на этот раз вы хотите узнать?")

                                        ),

                        PCharRepPhrase(LinkRandPhrase("Здравствуйте, капитан ", "Приветствую, ах это вы "+GetAddress_Form(NPChar)+" ", "А, капитан ")
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(", я думал"+NPCharSexPhrase(NPChar, " ", "а ")+"мы больше с вами не встретимся,",
                                                         ", не скажу, что рад"+NPCharSexPhrase(NPChar, " ", "а ")+"вас видеть, но", ", вижу, вы еще живы, прискорбно, а")
                                        +LinkRandPhrase(" что вам нужно?", " зачем вы пришли?", " чем могу быть "+NPCharSexPhrase(NPChar, "полезен?", "полезна?")),
                                        LinkRandPhrase(TimeGreeting() + ", капитан " + GetFullName(Pchar) + ". Чем могу помочь?",
                                        "О, да это же сам"+ GetSexPhrase("","а") +" капитан " + GetFullName(Pchar) + "! Что вы хотите узнать на этот раз?",
                                        "Здравствуйте, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Вы что-то хотели?"))
                                        );
	   			link.l3 = "Ничего, я передумал" + GetSexPhrase(".","а.");
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("А ты не врешь, капитан " + GetFullName(Pchar)+"?",
                                                                    "И что с того " + PChar.name+"?",
                                                                    "Я запомню тебя, " + GetFullName(Pchar)+".")
                                                                     + " А теперь говори, чего тебе надо?",
                                                    LinkRandPhrase("Приятно познакомиться, капитан " + PChar.name,
                                                                    "Рад"+NPCharSexPhrase(NPChar, " ", "а ")+" нашему знакомству, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "Очень приятно, капитан " + PChar.name) + ". Но вряд ли вы просто хотели узнать мое имя, не так ли?");

            link.l1 = PCharRepPhrase("Хотел"+ GetSexPhrase("","а") +" кое-что узнать об этом городишке!", "Хотел"+ GetSexPhrase("","а") +" узнать кое-что о городе.");
			link.l1.go = "new question";
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l2 = LinkRandPhrase("Ты в курсе", "Тебе что-нибудь известно о том", "Ты знаешь что-нибудь о том") + ", что недавно была ограблена местная церковь?");
				link.l2.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.

			link.l3 = "Ничего, я передумал" + GetSexPhrase(".","а.");
			Link.l3.go = "exit";
		break;

		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("О, да я рад"+NPCharSexPhrase(NPChar, " ", "а ")+" тебе, как выпивке, спрашивай, чего хочешь.", "Любишь поболтать, капитан? Что ж, я тоже... Особенно за кружечкой рома.", "Да, " + PChar.name + "?"),
                                        LinkRandPhrase("Ну, чего тебе еще?", "Вижу, капитан "+PChar.name+", ты охотни"+ GetSexPhrase("к","ца") +" поболтать? ", "Замучил"+ GetSexPhrase("","а") +" вопросами, капитан, лучше бы угостил"+ GetSexPhrase("","а") +" ромом.")),
		                PCharRepPhrase(LinkRandPhrase("Что вы хотели узнать "+ GetAddress_Form(NPChar) + "?", "Я вас слушаю капитан.", "Мне нужно идти, поэтому спрашивайте скорее, капитан."),
                                        LinkRandPhrase("Всегда рад"+NPCharSexPhrase(NPChar, " ", "а ")+" приятному собеседнику, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Говорите.",
                                                        "Да, " + GetAddress_Form(NPChar) + "?",
                                                        "Любите поболтать, капитан? Что ж, я тоже..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("Какие байки в ходу в здешней таверне?",
                                    "Что новенького в этих краях?",
                                    "Как течет жизнь на суше?");
			link.l1.go = "rumours_citizen";
			link.l2 = "Ничего, я передумал" + GetSexPhrase(".","а.");
			link.l2.go = "exit";
		break;

		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Нет, я ничего об этом не знаю.", "Мне ничего не известно по этому вопросу.", "Я ничего не знаю.");
					link.l1 = LinkRandPhrase("Ладно, хорошо.", "Ясно, спасибо.", "Хорошо, извини.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Я ничего об этом не знаю, но вы можете расспросить завсегдатаев в таверне - они уж точно что-нибудь вам расскажут.", "Я вам ничего сказать не могу, спросите лучше кого-нибудь в таверне.", "Мне ничего конкретного не известно, но я слышал, что об этом трепались в таверне.");
				link.l1 = "Спасибо и на том.";
				link.l1.go = "exit";
			}

			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;

		//замечение по обнаженному оружию
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

		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи ее") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}
