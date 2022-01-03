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
					dialog.text = "Здравствуйте, "+ GetSexPhrase("уважаемый новый гражданин","уважаемая новая гражданка") +" Города. Несмотря на шторм, я не думаю, что нам стоит затягивать знакомство. Так вот, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "Очень приятно. А мое имя " + GetFullName(pchar) + ". Дьявольский шторм!..";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Здравствуйте, "+ GetSexPhrase("уважаемый новый гражданин","уважаемая новая гражданка") +" Города. Мы не имели еще удовольствия общаться с вами. Так вот, меня зовут " + GetFullName(npchar) + ".";
					link.l1 = "Очень приятно. А мое имя " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Вам что-то нужно, сеньор"+ GetSexPhrase("","ита") +"?";
				link.l1 = "Послушайте, я ищу одного человека. Не знаете, где он сейчас?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Хочу задать вам вопрос.";
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
					link.l8 = "Знаете, я набираю команду, чтобы уйти отсюда.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "Что вы, это еще куда ни шло! Вам вообще крупно повезло, вы ведь разбились уже в конце бури, когда сила стихии пошла на убыль. Чуть раньше, и вы бы не сумели выбраться к нам...";
			link.l1 = "Жаль людей, корабль... Грустно, в общем.";
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = "Очень рад познакомиться с вами. Как вам наш Город на первый взгляд?";
			link.l1 = "Не успел"+ GetSexPhrase("","а") +" еще освоиться в полной мере.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Ну, это не страшно. Скоро все наладится и у вас, мы все через это прошли. Так что я желаю вам удачи. Не унывайте!";
			link.l1 = "Ни в коей мере!";
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
			dialog.text = "Внимательно вас слушаю, "+ GetSexPhrase("дружище","сеньорита") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Скажите, а в Город попадают люди только после штормов?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Послушайте, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Как вы оцените адмирала Города?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = "Послушайте, а вы давно тут живете. Я имею в виду, как давно вы попали на остров?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = "Да, только так. Когда у нас хорошая погода, к нам вообще подойти невозможно. Кажется, все дело в водороcлях, а движение вод неспокойного штормового моря временно раздвигает эту преграду.";
			link.l1 = "Как интересно!";
			link.l1.go = "ansewer_3_1";
		break;
		case "ansewer_3_1":
			dialog.text = "Да, действительно интересно. Справедливости ради хочу заметить, что моя теория не является истиной в последней инстанции. Хотя многие среди граждан с ней согласны.";
			link.l1 = "Я, пожалуй, тоже соглашусь.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_1":
			dialog.text = "Это Город Потерянных Кораблей, сеньор"+ GetSexPhrase("","ита") +". Мы все здесь оказались не по своей воле, но, знаете, это не самое плохое место на земле. И в океане.";
			link.l1 = "Ха! Скажите еще, что вам здесь нравится!";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Вы знаете, я - оптимист. Мне свойственно обустраивать свою жизнь в данной конкретной обстановке, а не искать лучшей доли. Горечь утраты друзей и знакомых при крушении корабля - она, конечно, имела место быть. Однако, жизнь продолжается, и, как мне кажется, нужно пройти ее не в печали, а в заботах и трудах!";
			link.l1 = "Вы знаете, ваш образ мыслей внушает мне уважение!";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "Спасибо за комплимент... Так я советую вам не опускать руки.";
			link.l1 = "С удовольствием последую вашему совету. Спасибо вам.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Адмирал человек довольно интересный. Знаете, он ведь был капитаном пиратского корабля!";
			link.l1 = "Да, это мне известно...";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Так вот, сами понимаете, что личность очень сильная, настоящий лидер. Я бы не советовал вам переходить ему дорогу. Это так, на будущее...";
			link.l1 = "Это понятно. А что там насчет выборов адмирала?";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "Вот именно это я вам и не советовал...";
			link.l1 = "Гм, понятно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Около года тому назад.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Какие товары?",
				"Вы уже спрашивали об этом.",
				"Уже спрашивали...",
                "Вы уже спрашивали меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Я ищу бомбы, картечь, провиант, лекарства, порох, оружие...",
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Не знаю, не знаю...";
			link.l1 = "Что не знаешь?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Не знаю, где взять.";
			link.l1 = "А-а, понятно.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Команду? Вы что, имеете в виду команду на корабль?";
			link.l1 ="Именно так.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "И у вас действительно есть корабль на плаву?";
			link.l1 = "Да, у меня есть фрегат, подготовленный к отплытию.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Я хочу уплыть отсюда вместе с вами. Что я должен делать?";
			link.l1 = "Немедленно отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на корабль.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Забегу за вещами, и считайте, что я уже на 'Сан Габриэле'.";
			link.l1 = "Хорошо. Но больше нигде не задерживайтесь.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
