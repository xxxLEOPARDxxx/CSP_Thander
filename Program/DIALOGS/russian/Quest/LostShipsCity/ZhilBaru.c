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
					dialog.text = "Приветствую вас! Насколько я понимаю, вы именно "+ GetSexPhrase("тот человек, что спасся","та девушка, что спаслась") +" в последнем шторме. Разрешите представиться, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "Очень приятно. Ну а я - " + GetFullName(pchar) + ".";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Приветствую вас! Насколько я понимаю, вы именно "+ GetSexPhrase("тот человек, что спасся","та девушка, что спаслась") +" из последней катастрофы. Разрешите представиться, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "Очень приятно. Ну а я - " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что вы хотели, "+ GetSexPhrase("месье","мадемуазель") +"?";
				link.l1 = "Послушайте, я ищу одного человека. Не знаете, где он сейчас?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Хочу задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toZhilBaru")
				{
					link.l5 = "Мне необходимо с вами поговорить о Максиме Тейлоре.";
					link.l5.go = "ELTHusb_SF";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Знаете, я набираю команду, чтобы уйти отсюда.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "Ну и как вам наш Город в руках стихии, так сказать?..";
			link.l1 = "Знаете, я сейчас не совсем адекват"+ GetSexPhrase("ен","на") +", ведь потерял"+ GetSexPhrase("","а") +" все и всех. Поэтому впечатления пока ужасные.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "Ну конечно, оно и понятно! Простите за бестактность... Вы знаете, шторм скоро пройдет.";
			link.l1 = "Я знаю, спасибо.";
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = "Вы знаете, очень хорошо, что наш Город пополнился таким приятным в общении человеком, как вы. Очень хорошо.";
			link.l1 = "А с чего вы взяли, что я прият"+ GetSexPhrase("ен","на") +" в общении?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Гм... мне так показалось.";
			link.l1 = ""+ GetSexPhrase("Когда кажется - тогда крестятся, приятель. Понятно?","Ну что же, спасибо за комплимент!") +"";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = ""+ GetSexPhrase("Очень понятно, очень!..","Пожалуйста. Если будут какие вопросы - обращайтесь.") +"";
			link.l1 = ""+ GetSexPhrase("Ну, вот и ладненько...","Обязательно...") +"";
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи е"+ GetSexPhrase("го","е") +", он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
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
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал"+ GetSexPhrase("","а") +" оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это "+ GetSexPhrase("серьезному мужчине","девушке") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = "А кого вы ищете?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "Я не понимаю, о ком вы говорите. Мне нужно знать имя и фамилию этого человека.";
				Link.l1 = "Понятно. Давате я еще попробую назвать.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Спасибо, я лучше сам"+ GetSexPhrase("","а") +" поищу.";
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
					dialog.text = GetFullName(sld) + ", вы о нем говорите?";
					Link.l1 = "Да-да, точно, это он.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о нем. Даваите еще раз назову.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", вы о ней говорите?";
					Link.l1 = "Ага, именно о ней.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "Нет, не о ней. Послушайте, давайте я еще раз попробую назвать.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "Знаете, не хочу я больше ни о ком спрашивать. До свидания.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Тогда назовите еще раз имя и фамилию.";
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
							dialog.text = LinkRandPhrase("Он здесь, на этом корабле. Ищите внимательней.", "Ха, так он здесь, на этом корабле!", "Он на этом корабле, странно, что вы еще не увидели его.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Так он здесь, " + npchar.quest.seekIdx.where + ". Смотрите внимательней.", "Так ведь он здесь, среди нас!", "Куда вы смотрите? Он же здесь ошивается.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам.", "Спасибо вам!");
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
							dialog.text = LinkRandPhrase("Она здесь, на этом корабле. Ищите внимательней.", "Ха, так она здесь, на этом корабле!", "Она на этом корабле, странно, что вы еще не увидели ее.");
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
							dialog.text = LinkRandPhrase("Так она здесь, " + npchar.quest.seekIdx.where + ". Смотрите внимательней.", "Так ведь она здесь, среди нас!", "Куда вы смотрите? Она же где-то здесь ходит.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил ее " + npchar.quest.seekIdx.where + ". Мы даже поговорили с ней.", "Насколько я знаю, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам, "+GetAddress_FormToNPC(NPChar)+".", "Спасибо вам!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Внимательно вас слушаю, "+ GetSexPhrase("дружище","мадемуазель") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Послушайте, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Вы не знаете причин, по которым сформировался этот остров?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Послушайте, как давно вы уже здесь прохлаждаетесь?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Это Город Потерянных Кораблей, "+ GetSexPhrase("приятель","мадемуазель") +". Тут все немного иначе, нежели на Большой земле...";
			link.l1 = "И что вы имеете в виду?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Тут другая жизнь со своим Законом! В принципе, порядки весьма неплохие и довольно справедливые. Так что, полагаю, вам здесь понравится.";
			link.l1 = "Хм, надеюсь.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Нет, и никто не знает. Говорят то о каком-то сильном течении, то о водорослях, то о коралловых рифах, но точно никто не знает.";
			link.l1 = "А никто не пытался узнать?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Говорят, что попытки были, но заканчивалось все очень и очень печально...";
			link.l1 = "Хм, понятно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Прохлаждаюсь? Неплохо сказано... Около трех лет штаны протираю.";
			link.l1 = "Уже давно. Не надоело?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Может и надоело...";
			link.l1 = "А Хилл Брюннер уже был здесь, когда вы сюда попали?";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "Был, конечно. Он в Городе всех знал. Жаль Хилла, очень он был хорошим человеком...";
			link.l1 = "Согласен.";
			link.l1.go = "int_quests";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Простите, я не понял. Что вы сказали?";
			link.l1 ="Я предлагаю вам уплыть из Города на Большую землю в составе команды моего фрегата.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Вот это предложение! И у вас что, действительно есть корабль на плаву?";
			link.l1 = "Да, есть.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Ну что же, тут и думать нечего. Я ухожу с вами.";
			link.l1 = "Прекрасно. Сейчас отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корабль.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Только забегу за вещами, и я в вашем распоряжении.";
			link.l1 = "Отлично!";
			link.l1.go = "SeekCrew_all";
		break;
		//освобождение мужа Элис Тейлор
		case "ELTHusb_SF":
			dialog.text = "Слушаю вас.";
			link.l1 = "Я узнал"+ GetSexPhrase("","а") +", что вы вместе ушли из таверны в тот день, когда Тейлора арестовали. Что произошло? Как он попал в резиденцию к адмиралу?";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "Простите, но вам какое до этого дело?";
			link.l1 = "Все дело в том, что Максим Тейлор проведет остаток своих дней в клетке на 'Тартарусе'. В качестве наказания адмирал дал ему пожизненное заключение.";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "Вот это да!..";
			link.l1 = "Именно. Мне небезразлична судьба Тейлоров, поэтому я и хочу знать, что произошло.";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "Черт, не думал я, что до такого дойдет...";
			link.l1 = "Поясните ваши слова.";
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = "Ох, как бы это сказать... В общем, это я так подшутил над адмиралом. Достал он своими законами...";
			link.l1 = "А при чем тут Тейлор?";
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = "Да ни при чем, собственно. Просто мы с ним выпивали в тот день в таверне и как раз об этом говорили. Ну, а когда мы с Тейлором пошли домой, я повел его на 'Сан Августин' и предложил ему высказать недовольство адмиралу прямо в глаза. Он так и сделал.";
			link.l1 = "Хо-хо, неплохо... Правда, не скажу, что это выглядит прилично с точки зрения морали.";
			link.l1.go = "ELTHusb_SF_6";
		break;
		case "ELTHusb_SF_6":
			dialog.text = "Я понимаю, что поступил не совсем правильно. Поэтому я зайду к адмиралу и расскажу ему, что мы просто пошутили.";
			link.l1 = "Ну что же, отлично. Я тоже пойду к Капперу, постараюсь сделать так, чтобы Тейлора поскорей освободили.";
			link.l1.go = "ELTHusb_SF_7";
		break;
		case "ELTHusb_SF_7":
			dialog.text = "Давайте. Надеюсь, адмирал меня не прикончит.";
			link.l1 = "Это вряд ли.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "9");
			pchar.questTemp.LSC.ElisHusband = "toAdmiralGood";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
