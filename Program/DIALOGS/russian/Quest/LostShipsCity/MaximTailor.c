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
			dialog.text = "Приветствую моего друга и просто очень "+ GetSexPhrase("хорошего человека","хорошую девушку") +". Чем я могу тебе помочь?";
			link.l1 = "Слушай, я ищу одного человека. Не знаешь, где он сейчас?";
			link.l1.go = "SeekCitizen";
			link.l2 = "Хочу задать тебе вопрос.";
			link.l2.go = "int_quests";
			link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?",
				"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
			link.l3.go = "rumours_LSC";
			link.l10 = "Ничего...";
			link.l10.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = "Внимательно тебя слушаю, "+ GetSexPhrase("дружище","" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Ну, как дела после пребывания в тюрьме?";
				link.l1.go = "ansewer_1";
			}
			link.l10 = "Нет вопросов. Извини, приятель...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Теперь я у жены на побегушках. Дал слово больше не пить.";
			link.l1 = "И это правильно, молодец.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		//нерадивый муж Элис Тейлор
		case "InPrison":
			dialog.text = "Эй, "+ GetSexPhrase("приятель","подруга") +"! Не поможешь мне?";
			link.l1 = "Ну, и чем я могу тебе помочь?";
			link.l1.go = "InPrison_1";
		break;
		case "InPrison_1":
			dialog.text = "Сообщи моей жене, что я опять вляпался!";
			link.l1 = "А кто твоя жена?";
			link.l1.go = "InPrison_2";
		break;
		case "InPrison_2":
			dialog.text = "Элис Тейлор, "+ GetSexPhrase("друг","подруга") +". Она хозяйка флейта 'Церес Смити'. А меня зовут Максим Тейлор.";
			link.l1 = "Приятно познакомиться, Максим.";
			link.l1.go = "InPrison_3";
		break;
		case "InPrison_3":
			dialog.text = "Мне тоже! Ну, так что, сделаешь?";
			link.l1 = "Если увижу твою жену, то обязательно сообщу.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "2");
			pchar.questTemp.LSC.ElisHusband = "toElis";
			NextDiag.TempNode = "InPrison_wait";
		break;

		case "InPrison_wait":
			dialog.text = "Эх, "+ GetSexPhrase("друг","подруга") +", на тебя вся моя надежда выйти отсюда. Пожалуйста, поскорее найди Элис...";
			link.l1 = "Ладно.";
			link.l1.go = "exit";
		break;

		case "DontRemember":
			dialog.text = NPCStringReactionRepeat("Что тебе нужно, "+ GetSexPhrase("дружище","подруга") +"?",
				""+ GetSexPhrase("Приятель","Подруга") +", ты еще что-то хочешь узнать?",
				"Ничего не помню, полнейший мрак в сознании.",
                ""+ GetSexPhrase("Дружище","Подруга") +", ты бы побыстрей меня вытаскивал"+ GetSexPhrase("","а") +" отсюда. Поднимаешь, трубы горят...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Твоя жена хочет вытащить тебя отсюда. Можешь мне объяснить, что ты наделал такого, чтобы сюда попасть?",
				"Нет.",
                "Да уж...",
				"Придется потерпеть.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("DontRemember_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "DontRemember_1":
			dialog.text = "Ничего не помню...";
			link.l1 = "Как? Вообще ничего?";
			link.l1.go = "DontRemember_2";
		break;
		case "DontRemember_2":
			dialog.text = "Вообще. Я еще в таверне отрубился. Говорят, что я пошел в резиденцию и наехал на самого адмирала! Ужас...";
			link.l1 = "М-да, надо меньше пить.";
			link.l1.go = "DontRemember_3";
		break;
		case "DontRemember_3":
			dialog.text = "Надо. Но никак не получается!";
			link.l1 = "Хех, ну дела!";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "6");
			pchar.questTemp.LSC.ElisHusband = "toAdmiral";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
