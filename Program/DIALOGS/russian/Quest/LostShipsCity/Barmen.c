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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = "Я не желаю с тобой разговаривать! Ты напал"+ GetSexPhrase("","а") +" на моих сограждан!";
				link.l1 = "Как знаешь..."
				link.l1.go = "exit";
				break;
			}

			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "Это твой корабль разбился последним? Ну что же, добро пожаловать! Я здесь содержу таверну, зовут меня " + GetFullName(npchar) + ". Тебе здорово повезло, "+ GetSexPhrase("приятель","девушка") +"!";
					link.l1 = "Да уж, повезло просто фатально!.. Меня зовут " + GetFullName(pchar) + ". Я был"+ GetSexPhrase("","а") +" капитаном...";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.Text = "А-а-а, так это твой корабль разбился последним? Ну что же, добро пожаловать! Я здесь содержу таверну, зовут меня " + GetFullName(npchar) + ". Так что заходи, ежели что...";
					Link.l1 = "Хорошо, " + npchar.name + ". Приятно познакомиться, так сказать... А меня зовут " + GetFullName(pchar) + ".";
					Link.l1.go = "First time";
				}
			}
			else
			{
				//базар в винном погребе
				if (pchar.questTemp.LSC == "toWineCellarGone" && npchar.location.locator == "stay1")
				{
					dialog.Text = "А-а, вот и ты!";
					link.l4 = "Именно! Теперь хотелось бы послушать тебя.";
					link.l4.go = "TizerCellar";
					PChar.quest.LSC_returnBarmen.over = "yes"; //снимаем таймер на опоздание, разговор состоялся
					break;
				}
				//после завала Хилла Брюннера
				if (pchar.questTemp.LSC == "barmenIsDead" && !CheckAttribute(npchar, "quest.HillNB_1"))
				{
					dialog.Text = "Слушаю тебя внимательно.";
					link.l4 = "Какого это дьявола ты тут делаешь? А где Брюннер?";
					link.l4.go = "NB_1";
					pchar.questTemp.LSC = "barmenIsDeadYouKnow";
					break;
				}
				if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toAdmiralBarmenDead")
				{
					if (!CheckAttribute(npchar, "quest.HillNBB_1"))
					{
						dialog.Text = "Слушаю тебя внимательно.";
						link.l4 = "Н-да, похоже, Хилл действительно мертв...";
						link.l4.go = "NBB_1";
						break;
					}
				}
				//убийство Армо
				sld = characterFromId("LSCwaitress");
				if (sld.lastname == "Прескотт" && !CheckAttribute(npchar, "quest.Armo"))
				{
					dialog.Text = "Армо убили... Сначала Хилл Брюннер, теперь Армо. Зловещее место эта таверна.";
					link.l4 = "Ты ничего не мог сделать, чтобы помешать этому?";
					link.l4.go = "ADied_1";
					npchar.quest.Armo = true;
					break;
				}
				//==> штатый диалог
				dialog.Text = LinkRandPhrase("Эй, " + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    "О-о-о, рад видеть нов"+ GetSexPhrase("ого","ую") +" граждан"+ GetSexPhrase("ина","ку") +" нашего города...",
                                    "Рад тебя видеть у себя в таверне. Зачем пожаловал"+ GetSexPhrase("","а") +"?");
				Link.l1 = "Я надеюсь, ты сможешь ответить на пару вопросов.";
				Link.l1.go = "int_quests";
				link.l2 = "Мне нужно переночевать.";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?",
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				Link.l4 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l4.go = "exit";
				//==>> квесты
				if (pchar.questTemp.LSC == "AfterAdmiral" && GetQuestPastDayParam("questTemp.LSC") > 3)
				{
					link.l4 = "Дружище, мы договаривались с тобой, что ты пораскинешь мозгами по поводу Тизера Дэна...";
					link.l4.go = "Tizer";
				}
				if (pchar.questTemp.LSC == "toWineCellarLate")
				{
					link.l4 = "Послушай, я так и не наш"+ GetSexPhrase("ел","ла") +" тебя в этом твоем винном погребе...";
					link.l4.go = "TizerCellarLate";
				}
				if (pchar.questTemp.LSC == "toDiffindoor" && CheckCharacterItem(pchar, "letter_LSC"))
				{
					link.l4 = "Я обследовал"+ GetSexPhrase("","а") +" 'Диффиндур' и наш"+ GetSexPhrase("ел","ла") +" там сундук Тизера. В нем, кроме прочего, было еще и очень интересное письмо...";
					link.l4.go = "TizerCellarOk_1";
				}
				if (pchar.questTemp.LSC == "afterFightInProtector")
				{
					link.l4 = "Послушай, тут такое дело...";
					link.l4.go = "AfterProtector_1";
				}
				if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
				{
					link.l4 = "Я сделал"+ GetSexPhrase("","а") +", как ты сказал. Кольцо 'нарвалов' у меня.";
					link.l4.go = "NarvalRing_1";
				}
				if (pchar.questTemp.LSC == "toTavernNarvalDestroyed")
				{
					link.l4 = "Ты знаешь, все получилось!";
					link.l4.go = "AfterNarvalDesrt_1";
				}
				if (pchar.questTemp.LSC == "waitInterception" && GetQuestPastDayParam("questTemp.LSC") > 2 && GetHour() < 20)
				{
					link.l4 = "Ну, как дела? Выяснил, что планировал?";
					link.l4.go = "Interception";
				}
				if (pchar.questTemp.LSC == "InterceptionLate")
				{
					link.l4 = "Слушай, я не смог"+ GetSexPhrase("","ла") +" к полуночи быть в твоем погребе. Так что я никого не видел"+ GetSexPhrase("","а") +" и нечего не услышал"+ GetSexPhrase("","а") +".";
					link.l4.go = "InterceptionLate";
				}
				if (pchar.questTemp.LSC == "InterceptionYouSeen")
				{
					link.l4 = "Ты знаешь, ровно в полночь я был"+ GetSexPhrase("","а") +" в твоем погребе. Адмирал и еще какой-то тип собирались поговорить, но заметили меня и ушли. Так что я ничего не услышал"+ GetSexPhrase("","а") +".";
					link.l4.go = "InterceptionYouSeen";
				}
				if (pchar.questTemp.LSC == "waitInterceptionResult")
				{
					link.l4 = "Приятель, удалось что-нибудь узнать по нашему делу?";
					link.l4.go = "Result";
				}
				if (pchar.questTemp.LSC == "InterceptionOk")
				{
					link.l4 = "Знаешь, твой погреб - действительно хорошее место для подслушивания разговоров. Я дождал"+ GetSexPhrase("ся","ась") +" Чада.";
					link.l4.go = "InterceptionOk";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Слушай, я ищу некоторые товары.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Слушай, есть серьезный разговор. Я набираю команду.";
					link.l8.go = "SeekCrew";
				}
			}
		break;

		case "FS_1":
			dialog.text = "Ты счастлив"+ GetSexPhrase("чик","ица") +", капитан, просто пока этого не понимаешь. Если бы ты подош"+ GetSexPhrase("ел","ла") +" к Городу часов пять назад - ты бы ни за что не сумел"+ GetSexPhrase("","а") +" выбраться из воды.";
			link.l1 = "Я моря"+ GetSexPhrase("к","чка") +", хорошо плаваю...";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "Это ничего не значит, когда речь идет о водах вокруг Города! Просто шторм пошел на убыль, и именно это дало тебе шанс.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//крутим время
		case "room":
   			if (chrDisableReloadToLocation) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Я думаю, что тебе не стоит сейчас спать. Поверь мне...";
				link.l1 = "Ладно.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ты можешь выспаться на кровати, что находится на верхнем ярусе. Когда тебя разбудить?";
			if(!isDay())
			{
				link.l1 = "Утром.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "К ночи.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Следующим утром.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Передумал"+ GetSexPhrase("","а") +". Обойдусь без сна.";
			link.l3.go = "exit";
		break;
		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Внимательно тебя слушаю, "+ GetSexPhrase("дружище","" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Погодка у вас, конечно, просто потрясающая!!";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Послушай, что это за остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Как получилось, что я попал"+ GetSexPhrase("","а") +" сюда?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "И что, отсюда действительно невозможно выбраться? Сколько кораблей вокруг, неужели нельзя сколотить один целый?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Как вы здесь живете, черт возьми?..";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6"))
			{
				link.l6 = "Послушай, ты знал такого человека - Тизера Дэна?";
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && pchar.questTemp.LSC == "AdmiralIsWaiting" && CheckCharacterItem(pchar, "keyQuestLSC"))
			{
				link.l7 = "Послушай, ты не знаешь, что такое Диффиндур?";
				link.l7.go = "ansewer_7";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l8"))
			{
				link.l8 = "Что за кланы живут в Городе?";
				link.l8.go = "ansewer_8";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l9"))
			{
				link.l9 = "Слушай, тут все замки на ключи заперты. Где взять хоть один?";
				link.l9.go = "ansewer_9";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l10"))
			{
				link.l10 = "А кто такой Августо Брамс?";
				link.l10.go = "ansewer_10";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l11"))
			{
				link.l11 = "Что-то я никак не освоюсь в Городе. Нет ли какой-нибудь карты, что ли?..";
				link.l11.go = "ansewer_11";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l12") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l12 = "Слушай, ты не знаешь кто такой Лейтон Декстер?";
				link.l12.go = "ansewer_12";
			}
			link.l20 = "Нет вопросов. Извини, приятель...";
			link.l20.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "Это еще ничего! Бывало и похуже. Штормы здесь - обычное дело.";
			link.l1 = "Понятно...";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "Этот шторм закончится завтра ближе к вечеру. У нас положено по прибытии отмечаться у адмирала, так что если до окончания шторма ты не явишься к нему, то он найдет тебя сам.";
			link.l1 = "Адмирал?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "Чад Каппер, "+ GetSexPhrase("приятель","" + pchar.name + "") +". Не шути с этим делом, мой тебе совет!";
			link.l1 = "Ясно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = "Это Город Потерянных Кораблей, "+ GetSexPhrase("приятель","подруга") +". Если попал"+ GetSexPhrase("","а") +" сюда, то забудь обо всем, чем жил"+ GetSexPhrase("","а") +" раньше. Отсюда не вырвешься, к сожалению...";
			link.l1 = "Дьявол!!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Не знаю, это тебя надо спросить, как ты сюда заплыл"+ GetSexPhrase("","а") +". Ты же капитан, своим кораблем сам"+ GetSexPhrase("","а") +" и управлял"+ GetSexPhrase("","а") +". Это я ничего не знаю, сидел себе в каюте, вдруг крики, потом треск обшивки... Вот и все.";
			link.l1 = "И ничего не видел?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Потом уже увидел, конечно, этот морской пейзажец, так сказать. Но как наш кэп умудрился сюда прийти - понятия не имею. Погиб он. Вообще-то, мало кто спасается после крушения, так что тебе повезло.";
			link.l1 = "Да уж...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Ха!!! И откуда ты так"+ GetSexPhrase("ой","ая") +" умн"+ GetSexPhrase("ый","ая") +" взял"+ GetSexPhrase("ся","ась") +"?.. Были попытки, но все неудачные. Получается, что люди берут материалы и попросту портят их. От этого Город серьезно страдает, так как это понижает его устойчивость. Если высвободить какой-нибудь корабль, то остров начинает двигаться, все переходы ломаются, каюты встают по другому\nВ общем, это боком выходит. Поэтому сейчас это запрещено нашим Законом. И уже давно!";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = "Да вполне нормально. Хотя, знаешь, надоело все до смерти... А вообще, Город живет на основании Закона. О его главных положениях тебе лучше узнать у адмирала Каппера.";
			link.l1 = "Это что за адмирал?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "Это, "+ GetSexPhrase("приятель","" + pchar.name + "") +", так называемый глава местного самоуправления, Чад Каппер его зовут. Говорят, что раньше он был пиратом, так что задирать его не стоит без дела.";
			link.l1 = "Никто и не собирается... А что, у вас действительно проходят выборы, и граждане выбирают адмирала?";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "Ну, когда-то выборы были, но сейчас это уже не актуально. Чад хорошо справляется со своими обязанностями, никто не хочет ничего менять. Уже никто не хочет...";
			link.l1 = "Что значит 'уже'?";
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = "До 'уже' были граждане, которые хотели стать адмиралом. Но теперь их нет с нами.";
			link.l1 = "Уплыли отсюда, что ли?";
			link.l1.go = "ansewer_4_4";
		break;
		case "ansewer_4_4":
			dialog.text = "Ну, можно и так сказать. На дно уплыли...";
			link.l1 = "Понятно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = "Знал. Он жил у нас несколько месяцев, потом погиб. А жаль, хороший был мужик.";
			link.l1 = "А вот и нет!";
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = "Что, нехороший был мужик?";
			link.l1 = "Да я не об этом! Похоже, что он каким-то образом добрался до Большой земли...";
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = "Дьявол!!! Не может быть!..";
			link.l1 = "Может. Правда, это, в итоге, не принесло ему счастья, он стал нищим...";
			link.l1.go = "ansewer_6_3";
		break;
		case "ansewer_6_3":
			dialog.text = "Черт! Черт!! Черт!!! Неужели это возможно?..";
			link.l1 = "Ты это о чем?";
			link.l1.go = "ansewer_6_4";
		break;
		case "ansewer_6_4":
			dialog.text = "Знаешь что, "+ GetSexPhrase("приятель","" + pchar.name + "") +", вот что я тебе скажу: никому не болтай об этом! Если адмирал узнает, что кто-то нарушил Закон, да еще в этом и преуспел... В общем, этому вестнику не поздоровится.";
			link.l1 = "Хм, не понимаю...";
			link.l1.go = "ansewer_6_5";
		break;
		case "ansewer_6_5":
			dialog.text = "Поймешь потом. А пока, ради твоего же блага, делай так, как я говорю. Не упоминай имя Тизера! Понял"+ GetSexPhrase("","а") +"?";
			link.l1 = "Понял"+ GetSexPhrase("","а") +".";
			link.l1.go = "ansewer_6_6";
		break;
		case "ansewer_6_6":
			dialog.text = "Хорошо. А я пока пораскину мозгами об этой твоей новости...";
			link.l1 = "Ну ладно, пораскинь.";
			link.l1.go = "int_quests";
			AddQuestRecord("ISS_MainLine", "4");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		case "ansewer_7":
			dialog.text = "Это флейт 'Фернандо Диффиндур', гиблое место.";
			link.l1 = "Будь добр, поясни...";
			link.l1.go = "ansewer_7_1";
			NextDiag.(NodePrevName).l7 = true;
		break;
		case "ansewer_7_1":
			dialog.text = "Флейт этот по идее должен был пойти ко дну - он буквально расколот пополам. Однако, как-то держится на поверхности, зацепился, видать, за рифы. В общем, корабль этот особняком стоит, никто там не живет и жить не будет.";
			link.l1 = "Почему?";
			link.l1.go = "ansewer_7_2";
		break;
		case "ansewer_7_2":
			dialog.text = "Такие корабли, когда начинают уходить по воду, погружаются за несколько секунд. Так что надо быть сумасшедшим, чтобы там проводить время.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_8":
			dialog.text = "Есть такие у нас в Городе. Знаешь, всегда находятся те, кто жить не может спокойно. Вот это они и есть - кланы...";
			link.l1 = "Хм, как понять?";
			link.l1.go = "ansewer_8_1";
			NextDiag.(NodePrevName).l8 = true;
		break;
		case "ansewer_8_1":
			dialog.text = "Ну, в эти кланы собираются каторжники, пираты... В общем, криминальные элементы, отбросы общества.";
			link.l1 = "Ты что это, и меня к отбросам относишь? Я ведь пират!";
			link.l1.go = "ansewer_8_2";
		break;
		case "ansewer_8_2":
			dialog.text = "Нет, ты не "+ GetSexPhrase("обычный","просто") +" пират, ты - пиратский капитан. Вот, у тебя само"+ GetSexPhrase("го","й") +" в команде мало было негодяев всех мастей?";
			link.l1 = "Ну, хватало, честно говоря.";
			link.l1.go = "ansewer_8_3";
		break;
		case "ansewer_8_3":
			dialog.text = "Вот это я и имею в виду... В общем, отдали им два корабля, чтобы они у себя там обретались и остальным гражданам не мешали. Адмирал со своей милицией их держит в узде, иначе здесь был бы полный кошмар.";
			link.l1 = "Ну и как, конфликты бывают с ними?";
			link.l1.go = "ansewer_8_4";
		break;
		case "ansewer_8_4":
			dialog.text = "Были, конечно, но сейчас все тихо. Но имей в виду, что тебе внутрь их кораблей заходить не стоит!";
			link.l1 = "Понятно. Ну что же, спасибо за информацию.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_9":
			dialog.text = "Где хочешь, там и бери. Это личное дело каждого, никто тебе в этом помогать не будет.";
			link.l1 = "М-да, хорошо объяснил, слов нет...";
			link.l1.go = "ansewer_9_1";
			NextDiag.(NodePrevName).l9 = true;
		break;
		case "ansewer_9_1":
			dialog.text = "Ну, что тебе сказать? Все сундуки заперты на замки трех уровней сложности. Если простой ключ можно найти даже на улице, то с остальными куда сложней. Ведь именно в сундуки с хорошими замками люди прячут действительно ценные вещи.\n"+
				"Даже если ты раздобудешь ключи, имей в виду, что такие ключи есть и у других. Если хочешь что-то спрятать надежно, то лучше искать сундуки подальше, за Городом.";
			link.l1 = "Ну вот, уже более-менее ясно. Спасибо.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_10":
			dialog.text = "Ха! Если бы я знал, "+ GetSexPhrase("приятель","" + pchar.name + "") +", кто такой Августо Брамс... А вообще я и знать этого не желаю.";
			link.l1 = "Объясни, пожалуйста.";
			link.l1.go = "ansewer_10_1";
			NextDiag.(NodePrevName).l10 = true;
		break;
		case "ansewer_10_1":
			dialog.text = "Хм, даже как он сюда попал - никто не знает, а ты хочешь, чтобы я тебе что-то объяснил. Он дает деньги в долг, но лучше от него держаться подальше"+ GetSexPhrase(", приятель","") +".";
			link.l1 = "Ничего не понял"+ GetSexPhrase("","а") +", ну да ладно...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_11":
			dialog.text = "Спроси у Эрика Йоста в магазине. У него должна быть такая.";
			link.l1 = "Спасибо, дружище.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l11 = true;
		break;
		case "ansewer_12":
			dialog.text = "Я-то знаю, а тебе зачем это?";
			link.l1 = "Хм, да просто интересно...";
			link.l1.go = "ansewer_12_1";
			NextDiag.(NodePrevName).l12 = true;
		break;
		case "ansewer_12_1":
			dialog.text = "Не стоит тебе копаться в этом деле, "+ GetSexPhrase("приятель","" + pchar.name + "") +", уж поверь мне.";
			link.l1 = "Расскажи, дружище. Там и посмотрим, стоит или нет.";
			link.l1.go = "ansewer_12_2";
		break;
		case "ansewer_12_2":
			dialog.text = "Ну, ладно... В общем, Декстер до попадания в Город был пиратом. Так же, как и Каппер, кстати. И как-то у них отношения сразу не заладились. Вскоре Декстер пропал. Вот и все, что я могу тебе рассказать.";
			link.l1 = "Да, не густо... Но все равно, спасибо тебе, " + npchar.name + ".";
			link.l1.go = "int_quests";
		break;

		// ------------------ квесты ------------------
		//бармен забивает стрелу в винном погребе
		case "Tizer":
			dialog.text = "Да-да, я пораскинул. Только говорить об этом здесь не могу. Давай встретимся у меня в винном погребе после полуночи.";
			link.l1 = "А где находится этот твой винный погреб?";
			link.l1.go = "Tizer_1";
		break;
		case "Tizer_1":
			dialog.text = "Ну, погребом я называю его по привычке, а вообще это одна из кают здесь. Нужно выйти на основную палубу 'Флерона' и с нее зайти в квартердек.";
			link.l1 = "Понятно. Ну что же, договорились.";
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = "Не задерживайся, долго тебя ждать я не смогу.";
			link.l1 = "Понятно. Буду обязательно.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
			AddQuestRecord("ISS_MainLine", "5");
		break;
		//бармен ругается, что ГГ не пришел в погреб
		case "TizerCellarLate":
			dialog.text = "Это мне известно, ведь я ждал тебя там битый час! Черт возьми, нельзя же быть так"+ GetSexPhrase("им","ой") +" легкомысленн"+ GetSexPhrase("ым","ой") +" в таком серьезном деле!";
			link.l1 = "В каком таком серьезном?";
			link.l1.go = "TizerCellarLate_1";
		break;
		case "TizerCellarLate_1":
			dialog.text = "Еще раз говорю, что я не могу об этом деле болтать с тобой прилюдно! Это безумие!";
			link.l1 = "Ладно, не кипятись. Давай еще раз попробуем встретиться, раз это так необходимо.";
			link.l1.go = "TizerCellarLate_2";
		break;
		case "TizerCellarLate_2":
			dialog.text = "Ну, хорошо. Жду тебя там же, в погребе, сегодня после полуночи. Но на сей раз изволь явиться.";
			link.l1 = "Хорошо, буду обязательно.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
		break;
		//базар с барменом в погребе
		case "TizerCellar":
			dialog.text = "Ты никому не говорил"+ GetSexPhrase("","а") +" о Тизере Дэне за это время?";
			link.l1 = "Нет, как мы и договаривались.";
			link.l1.go = "TizerCellar_1";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.LSC_returnBarmen_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_returnBarmen_2.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_returnBarmen_2.function = "LSC_returnBarmen_2";
		break;
		case "TizerCellar_1":
			dialog.text = "Это хорошо. Итак, давай я изложу тебе результаты своих размышлений по этому поводу.";
			link.l1 = "С удовольствием выслушаю.";
			link.l1.go = "TizerCellar_2";
		break;
		case "TizerCellar_2":
			dialog.text = "Ты, наверное, уже в курсе того, что Закон Города запрещает строить что-либо, на чем можно отсюда уплыть. Так вот, я просто ума не приложу, как это Тизер смог построить втихаря некое корыто, да еще и успешно на нем добраться до Большой земли.";
			link.l1 = "К сожалению, мне лично с Тизером увидеться не довелось, иначе, без сомнения, я узнал"+ GetSexPhrase("","а") +" бы все подробности этого дела.";
			link.l1.go = "TizerCellar_3";
		break;
		case "TizerCellar_3":
			dialog.text = "Да, жаль... Ну, давай смотреть на то, что имеем. А имеем мы загадку, которую нужно разрешить как можно быстрей. Прежде, чем что-то делать, необходимо в деталях понимать, как Тизер смог выбраться отсюда.";
			link.l1 = "А дальше что?";
			link.l1.go = "TizerCellar_4";
		break;
		case "TizerCellar_4":
			dialog.text = "Если граждане узнают, что Тизер добрался до Большой земли, то, без сомнения, многие захотят последовать его примеру. Только прежде, чем что-то говорить о Тизере Дэне, нужно иметь доказательства твоих утверждений.";
			link.l1 = "Но ведь я...";
			link.l1.go = "TizerCellar_5";
		break;
		case "TizerCellar_5":
			dialog.text = "Одного твоего слова мало, "+ GetSexPhrase("приятель","" + pchar.name + "") +"\nЯ вот что думаю. Ты долж"+ GetSexPhrase("ен","на") +" отправиться на флейт 'Фернандо Диффиндур'. Место это опасное чрезвычайно - корабль треснул пополам и непонятно как держится на поверхности. Однако именно там Тизер Дэн проводил очень много времени. Полагаю, что именно там мы сможем найти ключ к тайне Тизера.";
			link.l1 = "Как туда добраться?";
			link.l1.go = "TizerCellar_6";
		break;
		case "TizerCellar_6":
			dialog.text = "Вплавь, флейт не примыкает к Городу непосредственно. Ближайшими к 'Диффиндуру' кораблями являются флейт 'Церес Смити' и барк 'Сан Габриэль'. Там же, на связке между двумя этими парусниками, ты сможешь спрыгнуть в воду.\nИ будь осторож"+ GetSexPhrase("ен","на") +" на 'Сан Габриэле', не заходи внутрь. Этот барк - собственность клана 'Каспер'!";
			link.l1 = "Ясно. Послушай, ты можешь хоть примерно назвать, что мы ищем на 'Диффиндуре'?";
			link.l1.go = "TizerCellar_7";
		break;
		case "TizerCellar_7":
			dialog.text = "Если бы я знал! Напомню тебе, что мы ищем доказательства того, что несчастный Тизер Дэн сумел добраться до Большой земли.";
			if (CheckCharacterItem(pchar, "letter_LSC"))
			{
				link.l1 = "Хм, ты знаешь, на 'Диффиндуре' я уже побывал"+ GetSexPhrase("","а") +". И наш"+ GetSexPhrase("ел","ла") +" там сундук Тизера. В нем, кроме прочего, было еще и очень интересное письмо...";
				link.l1.go = "TizerCellarOk_1";
			}
			else
			{
				link.l1 = "Ты знаешь, у меня есть ключ, который друг Тизера отдал мне на Большой земле. Этот ключ Тизер Дэн наказал вручить тому, кто отправится на поиски Острова Справедливости, то есть Города Потерянных Кораблей.";
				link.l1.go = "TizerCellar_8";
			}
		break;
		case "TizerCellar_8":
			dialog.text = "Интересно, очень интересно... Однако, это опять же ничего не доказывает. Каппер выслушает тебя, а затем убьет на глазах остальных граждан как возмутител"+ GetSexPhrase("я","ьницу") +" спокойствия. И никто ему и слова скажет. Ключ? Да ключей в Городе полно, практически каждый сундук закрыт на ключ.";
			link.l1 = "Да, тоже верно.";
			link.l1.go = "TizerCellar_9";
		break;
		case "TizerCellar_9":
			dialog.text = "Однако, ключ - уже кое что. А что приятель Тизера говорил про него?";
			link.l1 = "Что это ключ 'Диффиндур'.";
			link.l1.go = "TizerCellar_10";
		break;
		case "TizerCellar_10":
			dialog.text = "Точно! Мы на верном пути!\nОтправляйся к 'Диффиндуру'. Полагаю, что там ты найдешь предмет, к которому данный ключ и подойдет. Тизер, хоть и казался мне человеком с причудами, тем не менее был далеко не дурак, судя по всему...";
			link.l1 = "М-да, может быть. Но то, что он был человеком хорошим - это факт.";
			link.l1.go = "TizerCellar_11";
		break;
		case "TizerCellar_11":
			dialog.text = "Согласен! Ну, не будем терять времени. Я жду тебя с результатами обследования флейта.";
			link.l1 = "Скоро буду, дружище. Ожидай.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "6");
			pchar.questTemp.LSC = "toDiffindoor"; //флаг линейки ГПК
		break;

		case "TizerCellarOk_1":
			dialog.text = "Что это за письмо?";
			link.l1 = "Прочти сам. Вот, держи.";
			link.l1.go = "TizerCellarOk_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "TizerCellarOk_2":
			dialog.text = "Так-так, очень интересно... Он пишет: '...так как мы долго и очень серьезно готовились.' Значит, он был не один...";
			link.l1 = "Да, судя по всему, ты прав.";
			link.l1.go = "TizerCellarOk_3";
		break;
		case "TizerCellarOk_3":
			dialog.text = "Хе-хе, без сомнения! Я неплохо знал Тизера, он ни за что на свете не сумел бы построить и дырявого плота - руки у него не из того места росли. Но раз он сумел-таки добраться до Большой земли, значит, его помощник, как пить дать, является специалистом в корабельном деле\nХа! Да ведь это наш плотник, Андре Лабор!! Вот что, "+ GetSexPhrase("дружище","капитан") +", отправляйся к нему. Поговори с ним тихо и мирно, расскажи о Тизере Дэне. А то ведь он и не знает, что этот бродяга все-таки добрался до Большой земли!";
			link.l1 = "А это необходимо? Ведь письмо Тизера уже является доказательством моих слов.";
			link.l1.go = "TizerCellarOk_4";
		break;
		case "TizerCellarOk_4":
			dialog.text = "Уже лучше, но, тем не менее, совершенно непонятно, как Тизер умудрился провернуть такое дело. Я не думаю, что нам стоит требовать отмены положения Закона, не имея конкретного предложения взамен.";
			link.l1 = "Почему? Как отменим запрет на постройку кораблей, так сразу и займемся этим. Там и решим, что да как строить.";
			link.l1.go = "TizerCellarOk_5";
		break;
		case "TizerCellarOk_5":
			dialog.text = "Не все так просто, "+ GetSexPhrase("дружище","" + pchar.name + "") +". Мы должны дать людям надежду и цель, а не право ломать Город кто как пожелает. С отменой положения Закона мы сразу же должны принять новый, о постройке ОДНОГО корабля для ВСЕХ!";
			link.l1 = "Хм, пожалуй, ты прав...";
			link.l1.go = "TizerCellarOk_6";
		break;
		case "TizerCellarOk_6":
			dialog.text = "И еще нужно не забывать, что адмирал вряд ли будет стоять, слушать тебя и репу чесать в растерянности. Требовать отмены положения Закона, который внесен Каппером и ревностно им исполняется, - большой риск. Мы должны убедить адмирала в своей правоте, а сделать это будет непросто, как мне кажется.";
			link.l1 = "Почему непросто?";
			link.l1.go = "TizerCellarOk_7";
		break;
		case "TizerCellarOk_7":
			dialog.text = "Хм, как тебе сказать... Иногда я ловлю себя на мысли, что адмирал не очень-то желает убраться отсюда.";
			link.l1 = "Хм, интересно...";
			link.l1.go = "TizerCellarOk_8";
		break;
		case "TizerCellarOk_8":
			dialog.text = "В общем, все это мои домыслы, к ним мы вернемся позднее. А сейчас найди Андрэ Лабора и аккуратно выясни все о его участии в деле Тизера.";
			link.l1 = "Хорошо, я так и сделаю.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAndreLabor"; //флаг линейки ГПК
			AddQuestRecord("ISS_MainLine", "7");
			pchar.questTemp.LSC.checkBoxes = true; //шмалять по открытым сундукам ежесуточно
		break;

		case "AfterProtector_1":
			dialog.text = "Что случилось?";
			link.l1 = "Хм... Ну, в общем, поговорил"+ GetSexPhrase("","а") +" я с плотником, этим Андре Лабором, и он попросил меня пройти в каюту корвета 'Протектор'. Я туда заш"+ GetSexPhrase("ел","ла") +", ну, и жду его, ничего такого не думаю даже... А этот Андрэ привел милиционера на разговор со мной! Пришлось всех отправить на тот свет.";
			link.l1.go = "AfterProtector_2";
		break;
		case "AfterProtector_2":
			dialog.text = "Дьявол! Это надо же! Ну, теперь тебе конец... Слушай, будь так добр"+ GetSexPhrase("","а") +", не рассказывай, что это я тебя надоумил. Тебя уже все равно убьют, а я еще пожить могу...";
			link.l1 = "Веди себя как мужчина! Никто меня не убьет, ведь никто и не знает, что это сделал"+ GetSexPhrase("","а") +" именно я. Они не успели рассказать обо мне адмиралу.";
			link.l1.go = "AfterProtector_3";
		break;
		case "AfterProtector_3":
			dialog.text = "Ты в этом уверен"+ GetSexPhrase("","а") +"?";
			link.l1 = "Милиционер сам так сказал.";
			link.l1.go = "AfterProtector_4";
		break;
		case "AfterProtector_4":
			dialog.text = "Уже лучше, хотя успокаиваться смысла не вижу. Адмирал далеко не дурак, он тебя вычислит.";
			link.l1 = "И что ты предлагаешь?";
			link.l1.go = "AfterProtector_5";
		break;
		case "AfterProtector_5":
			dialog.text = "Хм, думаю, что надо все списать на один из кланов.";
			link.l1 = "На какой?";
			link.l1.go = "AfterProtector_6";
		break;
		case "AfterProtector_6":
			dialog.text = "На клан 'Нарвал', они послабее будут.";
			link.l1 = "А как это сделать? Я же не могу прийти к Чаду и сказать: 'Это не я, это все 'нарвалы'!'.";
			link.l1.go = "AfterProtector_7";
		break;
		case "AfterProtector_7":
			dialog.text = "У всех членов клана 'Нарвал' есть амулет с изображением перевернутой пятиконечной звезды. Достань амулет и иди с ним к адмиралу. Расскажешь ему о том, что наш"+ GetSexPhrase("ел","ла") +" его на месте убийства милиционера и плотника.";
			link.l1 = "Ну и как мне найти это кольцо?";
			link.l1.go = "AfterProtector_8";
		break;
		case "AfterProtector_8":
			dialog.text = "В носовой части галеона 'Веласко' есть каюта, в которой 'нарвалы' хранят всякую ерунду. Это у них что-то вроде подсобки. Жди кого-нибудь из них там, а когда 'нарвал' появится – убей его.";
			link.l1 = "Понятно. Ну что же, так и поступлю.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "10");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ен", "на"));
			pchar.questTemp.LSC = "toKillOneNarval";
			pchar.quest.LSC_KillOneNarval.win_condition.l1 = "locator";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator = "reload2";
			pchar.quest.LSC_KillOneNarval.function = "LSC_KillOneNarval";
		break;

		case "NarvalRing_1":
			dialog.text = NPCStringReactionRepeat("Отлично! Теперь дуй к адмиралу и расскажи, что наш"+ GetSexPhrase("ел","ла") +" его в каюте 'Протектора'.",
				"Я это понял. Не мне, а адмиралу его надо показывать.",
				"Слушай, это уже не смешно. Дуй к адмиралу!",
                "Ну, ты туп"+ GetSexPhrase("ой","ая") +", однако...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Понял"+ GetSexPhrase("","а") +".",
				"Да, конечно...",
                "Ага, обязательно!",
				"Да, так"+ GetSexPhrase("им","ой") +" уродил"+ GetSexPhrase("ся","ась") +". Все чего-то делаю одно и тоже. На что рассчитываю - непонятно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "AfterNarvalDesrt_1":
			dialog.text = "Да ну!";
			link.l1 = "Точно! При помощи амулета я сумел"+ GetSexPhrase("","а") +" доказать Капперу, что убийство милиционера совершили 'нарвалы'. Адмирал поверил и послал меня уничтожить их всех. Что я и сделал"+ GetSexPhrase("","а") +".";
			link.l1.go = "AfterNarvalDesrt_2";
		break;
		case "AfterNarvalDesrt_2":
			dialog.text = "Н-да, лихо... Ну, "+ GetSexPhrase("братец","сестренка") +", медаль тебе положена. Хотя, если как следует поразмыслить, вреда от твоего деяния больше, чем пользы.";
			link.l1 = "Как понять?";
			link.l1.go = "AfterNarvalDesrt_3";
		break;
		case "AfterNarvalDesrt_3":
			dialog.text = "Понимаешь, до твоего 'подвига' в Городе существовал баланс - 'касперы' уравновешивались 'нарвалами'. Теперь это в прошлом...";
			link.l1 = "Хех, ты же сам подал идею подставить 'нарвалов', а теперь недоволен.";
			link.l1.go = "AfterNarvalDesrt_4";
		break;
		case "AfterNarvalDesrt_4":
			dialog.text = "Ну, я не то, что недоволен, просто свои соображения высказываю. К тому же, тогда я здорово испугался, признаю...";
			link.l1 = "Хе, ну да, это было заметно.";
			link.l1.go = "AfterNarvalDesrt_5";
		break;
		case "AfterNarvalDesrt_5":
			dialog.text = "Что теперь думаешь делать? Ты ведь теперь геро"+ GetSexPhrase("й","иня") +".";
			link.l1 = "Не знаю. Похоже, что я добил"+ GetSexPhrase("ся","ась") +" уважения у Чада. Вообще, мне здесь начинает нравиться. Может, в милицию запишусь...";
			link.l1.go = "AfterNarvalDesrt_6";
		break;
		case "AfterNarvalDesrt_6":
			dialog.text = "Вот что, "+ GetSexPhrase("приятель","" + pchar.name + "") +", ты пока погуляй, но не забывай наведываться ко мне. Я тут постараюсь выяснить кое-что...";
			link.l1 = "Что именно?";
			link.l1.go = "AfterNarvalDesrt_7";
		break;
		case "AfterNarvalDesrt_7":
			dialog.text = "Пока рано говорить об этом.";
			link.l1 = "Ладно, будут заходить к тебе.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterception";
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
			AddQuestRecord("ISS_MainLine", "17");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
		break;

		case "Interception":
			dialog.text = "Знаешь, у меня в таверне много чего происходит странного. Порой я думаю, что в действительности все совсем не так, как есть на самом деле...";
			link.l1 = "Чего?";
			link.l1.go = "Interception_1";
		break;
		case "Interception_1":
			dialog.text = "Я философом стал, в некотором роде, знаешь ли... В общем, я предлагаю тебе провернуть одно дело. Ты помнишь, где находится мой винный погреб?";
			link.l1 = "Помню, конечно.";
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			dialog.text = "Так вот, будь там сегодня до полуночи, встань возле решетки за колонной и подожди. Только повернись так, чтобы плечи твои не было видно из-за колонны. Возможно, тебе удастся подслушать очень интересный разговор, который повлияет на твое решение о дальнейших действиях.";
			link.l1 = "Чей разговор?";
			link.l1.go = "Interception_3";
		break;
		case "Interception_3":
			dialog.text = "Адмирала и еще одного человека. Мне самому давно уже интересно, о чем это они там периодически беседуют... В общем, сделай это, и, полагаю, обстановка во многом прояснится.";
			link.l1 = "Хорошо, как скажешь.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toInterception";
			pchar.questTemp.LSC.itemState = false; //флаг нахождения в локаторе итем в таверне
			AddQuestRecord("ISS_MainLine", "18");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ен", "на"));
		break;

		case "InterceptionLate":
			dialog.text = "Да уж, хорошего мало, как говорится... Ну, теперь делай что хочешь и живи как знаешь.";
			link.l1 = "Хм, понятно... А кто был тот человек, с кем адмирал должен был встретиться?";
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionYouSeen":
			dialog.text = "Да уж, хорошего мало, как говорится... Ну, теперь делай что хочешь и живи как знаешь.";
			link.l1 = "Хм, понятно... А кто был тот человек, что разговаривал с адмиралом?";
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionBadWork_1":
			dialog.text = "Это главарь клана 'Каспер' Каспер Лонгмэн.";
			link.l1 = "Хе-хе, вот это да!..";
			link.l1.go = "InterceptionBadWork_2";
		break;
		case "InterceptionBadWork_2":
			dialog.text = "Как-то я случайно столкнулся с ними у решетки погреба, когда они разговаривали. Начал наблюдать за ними и понял, что они втихаря встречаются здесь время от времени. Хотел бы я услышать, о чем они говорят...";
			link.l1 = "Ну, может еще не поздно? Давай подождем их следующую встречу.";
			link.l1.go = "InterceptionBadWork_3";
		break;
		case "InterceptionBadWork_3":
			dialog.text = "Подождем, конечно, но только я сам все сделаю теперь. Интересно было бы услышать их разговор именно сейчас, после устроенной тобой резни 'нарвалов'. А теперь надо будет подождать...";
			link.l1 = "Хм, понятно. И долго ждать?";
			link.l1.go = "InterceptionBadWork_4";
		break;
		case "InterceptionBadWork_4":
			dialog.text = "Это уж как получится.";
			link.l1 = "Ясно. Ну, хорошо. Буду наведываться к тебе время от времени.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "21");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 15);
		break;

		case "Result":
			dialog.text = NPCStringReactionRepeat("Пока нет, но я стараюсь. Жди.",
				"Я уже говорил тебе, чтобы ты продолжал"+ GetSexPhrase("","а") +" ждать. Пока ничего нового.",
				"В третий раз повторяю - жди.",
                "Не надоело еще?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Хорошо.",
				"Да-да, я понял"+ GetSexPhrase("","а") +".",
                "Понял"+ GetSexPhrase("","а") +", будут ждать.",
				"Не-е, я так"+ GetSexPhrase("ой","ая") +", настырн"+ GetSexPhrase("ый","ая") +".", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "InterceptionOk":
			sld = characterFromId("LSCMayor");
			if (sld.location == "FleuronTavern")
				dialog.text = "Говори тише, "+ GetSexPhrase("приятель","подруга") +"! У меня тут адмирал как раз прохлаждается... Ну что, сумел"+ GetSexPhrase("","а") +" разобрать разговор?";
			else
				dialog.text = "Сумел"+ GetSexPhrase("","а") +" разобрать разговор?";
			link.l1 = "Сумел"+ GetSexPhrase("","а") +". Оказывается, адмирал сам собирается покинуть Город!";
			link.l1.go = "InterceptionOk_1";
		break;
		case "InterceptionOk_1":
			dialog.text = "Не может быть! Он же принял тот пункт Закона, что запрещает даже строить корабли!";
			link.l1 = "Ну, пока он его не строил, а только собирается.";
			link.l1.go = "InterceptionOk_2";
		break;
		case "InterceptionOk_2":
			dialog.text = "Невозможно сделать это втайне от других Граждан!";
			link.l1 = "Можно. Клан 'Каспер' работает на адмирала. Да и вообще, за реальным примером далеко ходить не надо, Тизер Дэн же смог.";
			link.l1.go = "InterceptionOk_4";
		break;
		case "InterceptionOk_4":
			dialog.text = "Да, действительно... Ну, я же тебе говорил, что это будет важно!";
			link.l1 = "М-да, важней некуда... Послушай, адмирал упоминал к каком-то Механике. Кто это?";
			link.l1.go = "InterceptionOk_5";
		break;
		case "InterceptionOk_5":
			dialog.text = "Хм, не знаю...";
			link.l1 = "Вот дьявол!.. Послушай, ты же давно здесь живешь, должен знать всех.";
			link.l1.go = "InterceptionOk_6";
		break;
		case "InterceptionOk_6":
			dialog.text = "А с чего ты взял"+ GetSexPhrase("","а") +", что этот твой Механик существует? Может, ты неверно понял"+ GetSexPhrase("","а") +" смысл сказанного адмиралом?";
			link.l1 = "Может быть, но вряд ли... Слушай, а есть гражданин, кто уже жил здесь до твоего появления в Городе?";
			link.l1.go = "InterceptionOk_7";
		break;
		case "InterceptionOk_7":
			dialog.text = "Что-то затрудняюсь ответить. Вроде, из живых никого...";
			link.l1 = "Точно? Подумай, как следует.";
			link.l1.go = "InterceptionOk_8";
		break;
		case "InterceptionOk_8":
			dialog.text = "Хорошо, подумаю, но не сейчас. Я должен работать, так что приходи завтра.";
			link.l1 = "Договорились.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "23");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 3);
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = "Ты что, ничего не знаешь? Брюннера больше нет...";
			link.l1 = "Как нет?";
			link.l1.go = "NB_2";
			npchar.quest.HillNB_1 = true;
		break;
		case "NB_2":
			dialog.text = "Его нашли мертвым в винном погребе таверны. Знаешь эту каюту на корме, где стоят винные бочки? Вот это там его и нашли...";
			link.l1 = "Вот это да! Кого-нибудь видели? Убийцу нашли?";
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = "Нет, никто ничего не видел. Армо, наша официантка, нашла его уже мертвым. Она пошла в погреб, когда Хилл задержался там надолго, и вот...";
			link.l1 = "Черт возьми!.. Теперь ты хозяин таверны, как я понимаю.";
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = "Да. Как только все стало известно, адмирал вызвал меня и попросил заняться делом Брюннера. Без таверны, сам"+ GetSexPhrase("","а") +" понимаешь, жизни нет...";
			link.l1 = "Это точно... Ну ладно, желаю удачи на новом месте.";
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow")
			{
				pchar.questTemp.LSC = "toArmo_BrunnerDead";
			}
			AddQuestRecord("ISS_MainLine", "24");
		break;

		case "NBB_1":
			dialog.text = "Мертвее не бывает, "+ GetSexPhrase("дружище","подруга") +".";
			link.l1 = "Как это случилось?";
			link.l1.go = "NBB_2";
			npchar.quest.HillNBB_1 = true;
		break;
		case "NBB_2":
			dialog.text = "Его нашли мертвым в винном погребе таверны. Знаешь эту каюту на корме, где стоят винные бочки? Вот это там его и нашли...";
			link.l1 = "Кого-нибудь видели? Убийцу нашли?";
			link.l1.go = "NB_3";
		break;
		//базар по убийству Армо
		case "ADied_1":
			dialog.text = "Куда там! Никто даже не видел, как это произошло. Она пошла прибираться в носовую часть таверны, там, где стоит кровать. Вдруг мы услышали ее крик. И все...";
			link.l1 = "А что дальше?";
			link.l1.go = "ADied_2";
		break;
		case "ADied_2":
			dialog.text = "Побежали все туда, а она лежит там с перерезанным горлом. Вот и все, что тут уже делать-то?";
			link.l1 = "Тут уже ничего не сделать. А не видели, кто это?.. Хотя, знаю я. Это один из 'касперов'.";
			link.l1.go = "ADied_3";
		break;
		case "ADied_3":
			dialog.text = "Значит, они все-таки вышли из-под контроля. М-да... А за что они ее убили?";
			link.l1 = "Из-за меня все. Не сумел"+ GetSexPhrase("","а") +" я предусмотреть такого. Дьявол, никогда себе не прощу!";
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Что именно?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                "Ты уже спрашивал"+ GetSexPhrase("","а") +" меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны бомбы, книппеля, провиант, порох, оружие, лекарства...",
				"Да... Извини, запамятовал"+ GetSexPhrase("","") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Извини, такого не держим.";
			link.l1 = "Понял"+ GetSexPhrase("","а") +", спасибо.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Какую команду?",
				"Мы уже говорили об этом.",
				"Это уже обсуждено, второй раз повторяю.",
                "Хватит, утомил"+ GetSexPhrase("","а") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("На корабль. Я ухожу из Города.",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаешь...",
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "И что, есть на чем?";
			link.l1 = "Есть. Иначе я бы тебя не звал"+ GetSexPhrase("","а") +".";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Да уж... Знаешь, я, пожалуй, откажусь. Подожду, когда на это будет разрешение, и соберется адмирал.";
			link.l1 = "Ты многим рискуешь, оставаясь. На Город идет сильный шторм.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Ну, не впервой...";
			link.l1 = "Хм... Ну, как знаешь.";
			link.l1.go = "exit";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
