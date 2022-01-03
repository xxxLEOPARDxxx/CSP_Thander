
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

            		if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,
                                LinkRandPhrase("Меня зовут ", "Мое имя ", "Можешь называть меня ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". Чего тебе нужно?", ". Я тебя раньше здесь не "
                                +NPCharSexPhrase(NPChar, "видел", "видела")
                                +", кто ты такой?", ". Кто ты и что тебе от меня надо?"),

        		                LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Мое имя " + GetFullName(npchar) + ". А как зовут вас?",
                                 "Здравствуйте, " + GetAddress_Form(NPChar) + "! Я " + GetFullName(npchar) + ". Могу я узнать ваше имя?",
                                 "Да, " + GetAddress_Form(NPChar) + ". Что вы хотели? Кстати, меня зовут " + GetFullName(npchar) + ". А вас?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("Разрази меня гром! ", "Тысяча чертей! ", "Чтоб тебе пусто было! ") + "Да я капитан "+ GetFullName(Pchar)+ LinkRandPhrase(", ты разве не слыхал"+NPCharSexPhrase(NPChar,"","а")+" обо мне, "+NPCharSexPhrase(NPChar,"каналья?","?"), " и самый известный пират в этих водах! ", " и провалиться мне на этом месте, если это не так!"),
                                LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан " + GetFullName(Pchar)));
                                Link.l1.go = "Meeting";
			}
			else
			{
				dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("А ты не врешь, капитан " + GetFullName(Pchar)+"?",
                                                                    "И что с того " + PChar.name+"?",
                                                                    "Я запомню тебя, " + GetFullName(Pchar)+".")
                                                                     + " А теперь говори, чего тебе надо?",
                                                    LinkRandPhrase("Приятно познакомиться, капитан " + PChar.name,
                                                                    "Рад"+NPCharSexPhrase(NPChar, " ", "а ")+" нашему знакомству, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "Очень приятно, капитан " + PChar.name) + ". Но вряд ли вы просто хотели узнать мое имя, не так ли?");
				link.l1 = PCharRepPhrase("Хот"+ GetSexPhrase("ел","ела") +" кое-что узнать об этом городишке!", "Хот"+ GetSexPhrase("ел","ела") +" узнать кое-что о городе.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
				link.l2.go = "quests";//(перессылка в файл города)
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

            	link.l1 = PCharRepPhrase("Хот"+ GetSexPhrase("ел","ела") +" кое-что узнать об этом городишке!", "Хот"+ GetSexPhrase("ел","ела") +" узнать кое-что о городе.");
			link.l1.go = "new question";
            		Link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
			Link.l2.go = "quests";

			Link.l5 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш"+ GetSexPhrase("ел","ла") +" в таверну."),
                                        RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
			Link.l5.go = "exit";
			NextDiag.TempNode = "Meeting";
		break;

		case "new question":
            		dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("О, да я рад"+NPCharSexPhrase(NPChar, " ", "а ")+" тебе, как выпивке, спрашивай, чего хочешь.", "Любишь поболтать, капитан? Что ж, я тоже... Особенно за кружечкой рома.", "Да, " + PChar.name + "?"),
                                        LinkRandPhrase("Ну, чего тебе еще?", "Вижу, капитан "+PChar.name+", ты охотник поболтать? ", "Замучил вопросами, капитан, лучше бы угостил ромом.")),
		                PCharRepPhrase(LinkRandPhrase("Что вы хотели узнать "+ GetAddress_Form(NPChar) + "?", "Я вас слушаю капитан.", "Мне нужно идти, поэтому спрашивайте скорее, капитан."),
                                        LinkRandPhrase("Всегда рад"+NPCharSexPhrase(NPChar, " ", "а ")+" приятному собеседнику, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Говорите.",
                                                        "Да, " + GetAddress_Form(NPChar) + "?",
                                                        "Любите поболтать, капитан? Что ж, я тоже...")));

            		link.l1 = RandPhraseSimple("Есть важное дело!", "У меня к вам дело.");
			link.l1.go = "quests";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш"+ GetSexPhrase("ел","ла") + " в таверну."),
                                        RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
			link.l2.go = "exit";
		break;

		case "quests":
            		dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я передум"+ GetSexPhrase("ал","ала") + "...", "Сейчас мне не о чем говорить");
		    	link.l1.go = "exit";
		break;


		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, капитан, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда люди ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Пон"+ GetSexPhrase("ял","яла") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;




		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
