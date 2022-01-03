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
					dialog.text = "Добрый день! Как вам у нас? Красивый город, не так ли? А в штормовую погоду он просто великолепен!";
					link.l1 = "Безусловно! Из этого шторма только я выбрал"+ GetSexPhrase("ся","ась") +"?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Добрый день! Как вам у нас? Красивый город, не так ли?";
					link.l1 = "Безусловно. Моё имя " + GetFullName(pchar) + ", я был"+ GetSexPhrase("","а") +"...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Что вы хотели, "+ GetSexPhrase("минхер","госпожа") +"?";
				link.l1 = "Послушайте, я ищу одного человека. Не знаете, где он сейчас?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Хочу задать вам вопрос.";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				link.l2.go = "int_quests";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Послушайте, я тут ищу некоторые товары.";
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
			dialog.text = "Похоже, что так и есть. Мне очень жаль...";
			link.l1 = "Такова жизнь... Да, позвольте представиться. Моё имя " + GetFullName(pchar) + ", я был"+ GetSexPhrase("","а") +"...";
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = "Неважно, кем вы были. Рекомендую вам эту конструкцию, слово 'город' я тут не употребляю. Ну что же, для вас началась новая жизнь, и возврата нет. Кстати, я - " + GetFullName(npchar) + ".";
			link.l1 = "А почему вы так уверены, минхер " + npchar.lastname + ", что возврата нет?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Потому что за три года бытия здесь я многократно видел, куда отправляются те, кто пытается вернуться. Уж поверьте, им там холодно и мокро, а торчать предстоит вечность. Я имею в виду чистилище...";
			link.l1 = "Я это понял"+ GetSexPhrase("","а") +". Хм, ну и кто им помогает обрести нирвану? Уж не Каппер ли?..";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Хе-хе-хе... Чад Каппер - наше всё, более того, он и наше ничто по совместительству. Как бы там ни было, а следовать его указаниям вам придётся. Так что вы аккуратней в разговорах.";
			link.l1 = "Аккуратней? А если я не захочу быть аккуратней?!";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Что ж, я помолюсь за упокой вашей души в этом случае. Без всяких сомнений, вас ждет участь Лейтона Декстера.";
			link.l1 = "Хм, ну и что случилось с этим Декстером?";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Я не хочу об этом говорить. Если хотите что-то узнать о нем, то спросите лучше Леа Тоорс.";
			link.l1 = "Хорошо... Вы знаете, надежда - хорошая штука, минхер " + npchar.lastname + ". Убеждая себя в безвыходности положения, вы сами делаете это положение таковым.";
			link.l1.go = "FT_6";
			AddQuestRecord("LSC_findDekster", "2");
			AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("LSC_findDekster", "sSex1", GetSexPhrase("ен","на"));
		break;
		case "FT_6":
			dialog.text = "Может быть, всё может быть. Но тут не так уж и плохо. У нас есть Закон, у нас есть своя жизнь, у нас... интересно. Я бы даже сказал, мне тут нравится.";
			link.l1 = "А вы приспособленец!";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Ну и что? По-моему, в данной ситуации это очень даже хорошо. Кстати, и вам искренне советую.";
			link.l1 = "Ладно, успехов вам, минхер " + npchar.lastname + ".";
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
			dialog.text = "Внимательно вас слушаю, "+ GetSexPhrase("дружище","госпожа") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Этот Закон... его можно как-то обойти?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "В городе одна власть? Здесь есть... противники адмирала?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Здесь есть, где поразвлечься?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = "Скажите, давно вы уже здесь живете? Не надоело?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Обойти можно всё, что угодно, "+ GetSexPhrase("дружище","госпожа") +". Важно лишь, чем это кончится. Уверен, вы говорите о том, чтобы уплыть отсюда...";
			link.l1 = "Именно об этом!";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Что ж, это возможно...";
			link.l1 = "Я в"+ GetSexPhrase("есь","ся") +" во внимании.";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "...в гробу, ха-ха-ха!..";
			link.l1 = "Забавный вы минхер, знаете ли...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Сколько угодно. Поищите под досками и на дне то, что от них осталось... У нас есть кланы, но живут они в мире с адмиралом и гражданами Города. Правда, до тех пор, пока вы не войдете внутрь их кораблей.";
			link.l1 = "И что будет, если войти?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Они, без всякого сомнения, убьют вошедшего.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Поразвлечься? А ты сюда развлекаться притащил"+ GetSexPhrase("ся","ась") +"?!";
			link.l1 = "Хм, почему бы и нет?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Развлекаться будешь, когда уберёшься отсюда! Кхм, только вот незадача: это невозможно! Ха-ха-ха!";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Конечно, надоело. Ну а куда деваться-то?.. Правильно, некуда.";
			link.l1 = "Ну да... А Хилл Брюннер уже был здесь, когда вы сюда попали?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "Был, уже командовал парадом в своей таверне. Эх, жаль человека, хороший он был трактирщик.";
			link.l1 = "Это точно...";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Очень хорошо. Чем я могу помочь?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                "Ты уже спрашивал"+ GetSexPhrase("","а") +" меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Я ищу бомбы, картечь, провиант, лекарства, порох, оружие...",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Ясно. Порох и оружие лучше просить у адмирала. Бомбы, картечь и прочие боеприпасы - у хозяек домов. А лекарства - у святого отца.";
			link.l1 = "Понял"+ GetSexPhrase("","а") +". Спасибо вам огромное.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Простите, что?";
			link.l1 ="Я предлагаю вам пойти ко мне матросом на мой фрегат. В скором времени я отчаливаю.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Вот это да!.. И как вам удалось провернуть такое? Ведь Закон запрещает...";
			link.l1 = "Простите, у меня нет времени. Вы согласны?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Конечно, согласен. Какие могут быть вопросы?..";
			link.l1 = "Хорошо! Тогда немедленно отправляйтесь на 'Сан Габриэль'. Механик переправит вас на мой фрегат.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо, я так и сделаю. Только мне нужно собрать вещи.";
			link.l1 = "Хорошо, но не задерживайтесь.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
