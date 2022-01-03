
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
			dialog.text = "С кем имею честь разговаривать?";
			link.l1 = "Э-э... Меня зовут " + GetFullName(pchar) + " , я - капитан судна ''" + PChar.Ship.Name + "''.";
			link.l1.go = "talk_1";
			if (bBettaTestMode && !CheckAttribute(pchar,"ScamFanActive"))
			{
				link.l2 = "Вызвать Кракена";
				link.l2.go = "Kraken";
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			dialog.text = "Чем обязан, капитан " + GetFullName(pchar) + " ?";
			link.l1 = "Хотелось бы узнать насчёт предстоящих поединков.";
			link.l1.go = "ArenaBattle_1";
			link.l2 = "Хотелось бы потренироваться.";
			link.l2.go = "academy";
			if (CheckAttribute(pchar,"ScamFanActive") && !CheckAttribute(pchar,"KnowScam"))
			{
				link.l3 = "Вы случайно не знаете что-нибудь об этом ''фанате'' чемпиона?";
				link.l3.go = "legend";
			}
			link.l99 = "Хотелось только повидать вас, " + NPChar.name + " " + NPChar.lastname + ". До встречи.";
			link.l99.go = "exit";
			if (bBettaTestMode && !CheckAttribute(pchar,"ScamFanActive"))
			{
				link.l4 = "Вызвать Кракена";
				link.l4.go = "Kraken";
			}
			NextDiag.TempNode = "meeting";
		break;

		/////////////////////////////////////////////////////////////////////////////////////////
		/////////// Бои на арене - возможность сделать ставки или самому участвовать ////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "ArenaBattle_1":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "Капитан, вы собирались пойти и посмотреть соревнования.";
				link.l1 = "Ах-да, и правда.";
				link.l1.go = "exit";
				break;
			}

			if(CheckAttribute(PChar, "Arena"))
			{
				if(PChar.AcademyLand.Begin == true)
				{
					dialog.text = "Хм... По моему, вы ещё не завершили тренировку, о которой мы недавно договорились.";
					link.l1 = "Э-э-э, да?.. В таком случае, позвольте откланяться.";
					link.l1.go = "exit";
				}
				else
				{
					if(PChar.Arena == "Generate")
					{
						dialog.text = "Если тебя интересует, то в ближайшее время состоятся очередные поединки.";
						link.l1 = "Да, меня интересует это. Хочу узнать об этом подробнее.";
						link.l1.go = "ArenaBattle_2";
						link.l2 = "Хм.. Спасибо за информацию, но мне, пожалуй, сейчас не до этого...";
						link.l2.go = "exit";
					}
					else
					{
						if(PChar.Arena == "Prepare")
						{
							dialog.text = "Хм... По-моему, капитан, вы уже должны быть на месте мероприятия - ведь вы уже выбрали соревнование!";
							link.l1 = "Да?.. Э-э-э.. Уже бегу!";
							link.l1.go = "exit";
						}
						else
						{
							dialog.text = "К сожалению, капитан " + GetFullName(pchar) + ", пока поединков не ожидается.";
							link.l1 = "Жаль. Тогда, до встречи!";
							link.l1.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.text = "К сожалению, капитан " + GetFullName(pchar) + ", пока поединков не ожидается.";
				link.l1 = "Жаль. Тогда, до встречи!";
				link.l1.go = "exit";
			}

		break;

		case "ArenaBattle_2":
			dialog.text = "Желаешь принять участие в поединке или попытаться заработать немного денег?";
			link.l1 = "Я бы с удовольствием приня"+ GetSexPhrase("л","ла") +" участие или сдел"+ GetSexPhrase("ал","ала") +" бы ставку.";
			link.l1.go = "ArenaBattle_3";
			link.l3 = "Если это возможно, то хотелось бы просто понаблюдать за этим.";
			link.l3.go = "ArenaBattle_5";
		break;

		case "ArenaBattle_3":
			NextDiag.CurrentNode = "Meeting";
			DialogExit();
			LaunchArena(false);
		break;

		case "ArenaBattle_5":
			int iMoney = sti(PChar.Arena.ViewCost);
			dialog.text = "Хм... Пожалуй, я могу предоставить тебе такую возможность. За " + iMoney + " золотых, разумеется.";

			if(sti(PChar.money) >= iMoney)
			{
				link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +". Вот они, твои " + iMoney + " золотых.";
				link.l1.go = "ArenaBattle_6";
			}
			else
			{
				link.l1 = "М-да.. Пожалуй, подобные развлечения мне не по карману. Приду в другой раз.";
				link.l1.go = "exit";
			}

			link.l2 = "Вот ещё, платить за какое то жалкое зрелище!";
			link.l2.go = "exit";
		break;

		case "ArenaBattle_6":
			AddMoneyToCharacter(PChar, -sti(PChar.Arena.ViewCost));
			GiveItem2Character(PChar, "ArenaBilet");
			dialog.text = "Вот и славно. Возьмите эту бумажку - покажете при входе... ...(улыбается)...";
			link.l1 = "Хех. Благодарю.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PrepareArenaOdds");
			PChar.Arena.Mode.NotOdd = true;
		break;

		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////// ТРЕНИРОВКИ ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "academy":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "Капитан, вы собирались пойти и посмотреть соревнования.";
				link.l1 = "Ах-да, и правда.";
				link.l1.go = "exit";
				break;
			}

			if(PChar.AcademyLand.Can == false)
			{
				if(PChar.AcademyLand.Begin == true)
				{
					dialog.text = "Хм... По моему, вы ещё не завершили предыдущей тренировки...";
					link.l1 = "Э-э-э, да?.. В таком случае, позвольте откланяться.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Хм... В данный момент я не могу предоставить тебе людей для этого. Приходи позже.";
					link.l1 = "Что ж, жаль.";
					link.l1.go = "exit";
				}
			}
			else
			{
				if(PChar.Arena != "Prepare")
				{
					dialog.text = "Хм... Какой способ ты желаешь опробывать?";
					link.l1 = "Давайте посмотрим.";
					link.l1.go = "academy_land";
				}
				else
				{
					dialog.text = "Хм... По-моему, капитан, вы уже выбрали соревнование! Вам должно быть не до тренировок.";
					link.l1 = "Да?.. Э-э-э.. Уже бегу!";
					link.l1.go = "exit";
				}
			}
		break;

		case "academy_land":
			NextDiag.CurrentNode = "Meeting";
			DialogExit();
			LaunchAcademyLand();
		break;

		case "academy_sea":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////// ПЕРВАЯ ВСТРЕЧА ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "talk_1":
			dialog.text = "Рад знакомству, капитан. Зовут меня " + NPChar.name + " " + NPChar.lastname + ". Хм.. Честно говоря, не слыхал о вас. Как же вас сюда занесло, капитан?";
			link.l1 = "Ну, как сказать. Мне свойственно обследовать ранее невиданные территории. Именно поэтому я наш"+ GetSexPhrase("ёл","ла") +" ваше поселение здесь. Но, что это за поселение?";
			link.l1.go = "talk_2";
		break;

		case "talk_2":
			dialog.text = "О-о, это очень долгая история, которую нет желания вспоминать.. Но, наверное, стоит рассказать... Хотя вы возможно слышали её.";
			link.l1 = "Хм... Что-то не припоминаю.";
			link.l1.go = "talk_3";
		break;

		case "talk_3":
			dialog.text = "Несколько лет назад на этом острове один великий мореплаватель решился строить колонию. Месяцами длились транспортировки нужного товара, шло строительство колонии. \n Когда строительство форта была завершено, решено было приступать к строительству самой колонии... Но внезапно колониальные державы узнали о новостройке и решили вмешаться в ход строительства. Практически все были убиты, а форт и зачатки новой колонии разрушены... Остался этот маленький лагерь, где жили рабочие и рабы. \n Всем, кто сейчас живёт в этом поселении также была уготована смерть, но нас спас счастливый случай - в тот момент мы углубились в джунгли в поисках хвороста, а вернувшись увидели эти разрушения... Все те, кто сейчас живёт в этом поселение - строители, да команда того самого капитана.";
			link.l1 = "Да-а... Печальная история. Но чем вы же здесь занимаетесь?";
			link.l1.go = "talk_4";
		break;

		case "talk_4":
			dialog.text = "Прошло много времени, пока мы оправились от такого бедствия, тем более оставшись одни на необитаемом острове. Приходилось питаться растениями и насекомыми. Но со временем нам удалось построить это поселение, а позже, немного окрепнув, мы стали проводить бесконечные тренировки, и те строители и рабы, которые чуть не умерли с голода и едва держали шпагу в руках, благодаря неимоверной выдержке и желанию смогли неплохо обучиться исскуству фехтования. \n Вскоре наш городок заметили неизвестные проплывавшие мимо корабли, и о нашем поселении начали расходиться слухи по всем Карибам. Прошло время, и теперь можно сказать, что если бы не то несчастье, приключившиеся с нами - возможно ничего этого и не было, а те рабы продолжали гнить, работая на толстых торгашей в невыносимых условиях, а мы так и делили бы гроши между собой, преклоняясь перед своим капитаном... \n Теперь здесь время от времени проводятся различные турниры - от дуэлей до полноценных турниров, а также возможность делать ставки. Участвовать вы можете лишь заплатив, но если победите - все деньги станут вашими! Ну и конечно, мы можем предоставить вам людей для различного типа тренировок. За небольшую плату, разумеется.";
			link.l1 = "Очень интересно! Думаю, я смо"+ GetSexPhrase("г","гла") +" бы воспользоваться вашими услугами.";
			link.l1.go = "meeting";
			NextDiag.TempNode = "meeting";
		break;
		// говорим при первой встрече <--

		// На арене -->
		case "FightInArena_1":
			dialog.text = "Приветствую тебя, капитан " + GetFullName(pchar) + ". Тебе предстоит сразиться с достойным соперником\n Дуэль проходит в несколько раундов: до трёх побед одного из участников. Желаю удачи!";
			link.l1 = "Благодарю за информацию, " + NPChar.lastname + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelTalkWithEnemy");
		break;

		case "FightInArena_2":
			switch(sti(PChar.Arena.Duel.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("Вы проиграли, капитан " + GetNameLugger(PChar, "f") + "! Возможно, в следующий раз вы окажетесь сильнее!", "Очень жаль, что вы потерпели неудачу, капитан " + GetNameLugger(PChar, "l") + ".", "Эх, вам совсем чуть-чуть не хватило до победы! Ну что ж, возможно в следующий раз вам повезёт больше.");
					link.l1 = LinkRandPhrase("Эх.. Не повезло.", "Но ты видел как я ему тогда заряди"+ GetSexPhrase("л","ла") +"?!", "Глупости - эта ваша арена!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaDuelTheEnd");
				break;

				case 1:
					dialog.text = LinkRandPhrase("Вы уделали его, кэп! Я болел за вас. Вы честно заработали свой выигрыш. Вот, теперь эти " + sti(PChar.Arena.Duel.Prize) + " золотых по праву принадлежат вам.", "Как вы его уделали, капитан! А как вы осуществили первый переход! Я восхищался вашими действиями. Вы заслужили свои " + sti(PChar.Arena.Duel.Prize) + " золотых.", "Вы снова доказали всем, кто здесь главный. Поздравляю, вот ваши " + sti(PChar.Arena.Duel.Prize) + " золотых в качестве приза.");
					link.l1 = LinkRandPhrase("Благодарю! До скорых встреч.", "Спасибо, уважаемый. Обязательно приду в следующий раз.", "Хе-хе!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Duel.Prize));
					AddDialogExitQuestFunction("ArenaDuelTheEnd");
				break;
			}
		break;

		case "FightInArena_3":
			dialog.text = LinkRandPhrase("Ха-ха-ха! Добро пожаловать в ад, капитан " + GetFullName(pchar) + "! Тебе придёться серьёзно постараться, чтобы выйти из этой схватки с отшельниками природы победителем.", "Ну что, гото"+ GetSexPhrase("в","ва") +" к схватке с отродьями дьявола?", "Ах, вот и вы, капитан. Хе-хе, ну что ж - зрители ждут.");
			link.l1 = LinkRandPhrase("И не таких видали.", "Я изрешечу их в вермишель!", "Приготовь денежки, приятель.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaEtapsBattle");
		break;

		case "FightInArena_4":
			switch(sti(PChar.Arena.Etaps.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("Эти твари чуть не разорвали вас на куски! Возможно в следующий раз вы окажетесь сильнее.", "Да-а, да они чуть не сожрали вас! Ха-ха-ха!", "Класно ты этим тварям зарядил! Но на всех сил не хватило. Приходите ещё.");
					link.l1 = LinkRandPhrase("Да это у вас просто сабли тупые! Да крыша неровная...", "Где вы нашли этих монстров?! Ну ничего, я ещё вернусь! Так им и передайте...", "Мне просто не повезло!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;

				case 1:
					dialog.text = LinkRandPhrase("Как вы их! Почаще бы таких бойцов! Вы честно заработали свой выигрыш. Вот, теперь эти " + sti(PChar.Arena.Etaps.Prize) + " золотых по праву принадлежат вам. Приходите ещё.", "Да-а, не ожидал я от вас такой прыти. Да вы молодец - не каждый смельчак выйдет на бой с этими тварюгами. Вот ваш выигрыш - " + sti(PChar.Arena.Etaps.Prize) + " золотых.", "Они едва не рассыпались от твоего клинка! Вот это сеча была! Вот ваш выигрыш - " + sti(PChar.Arena.Etaps.Prize) + " золотых.");
					link.l1 = LinkRandPhrase("Хех. Никому не по силам одолеть меня!", "Закажите для меня партию этих тварей. Обязательно ещё приду!", "А ты видел как я тому крабу клешню отруби"+ GetSexPhrase("л","ла") +"?!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Etaps.Prize));
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;
			}
		break;

		case "FightInArena_5":
			dialog.text = LinkRandPhrase("А вот и вы, капитан " + GetFullName(pchar) + "! Что ж, вы как раз вовремя - все участники в сборе и нет никаких препятствий тому, чтобы начать уже наш турнир.", "Приветствую вас, капитан " + GetNameLugger(PChar, "f") + ". Вас ждут очень тяжёлые схватки - это я вам обещаю. Ну, если вы, конечно, первый раунд пройдёте. Ха-ха!", "Надеюсь, что вы дадите жару этим зазнайкам, капитан " + GetNameLugger(PChar, "l") + ".");
            PlayVoice("Kopcapkz\Voices\Arena\ArenaHead_"+rand(7)+".wav");
			link.l1 = LinkRandPhrase("Передай этим участникам, что у них никаких шансов в схватке со мной!", "Давай уже начинать - мне не терпится кого-нибудь уделать!", "Приз будет моим - даже не сомневайся.");
			AddDialogExitQuestFunction("ArenaTournamentTalkWithRandEnemy");
		break;


		case "FightInArena_7":
			switch(sti(PChar.Arena.Tournament.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("Да-а, турнир удался на славу! Вы достойно сражались, капитан! Но удача была не на вашей стороне. Будем ждать вас вновь - быть может, в следующий раз вы окажетесь победителем.", "Я надеялся на вас, кэп, а вас чуть по полу не размазали! Тьфу.", "Эх, вот не повезло. Наверное вы просто не выспались.");
					link.l1 = LinkRandPhrase("Просто я немного, кхм, приболе"+ GetSexPhrase("л","ла") +"... До свидания.", "Соперник использовал запрещённые приёмы - я буду жаловаться.", "Ну ничего, я ещё вернусь.");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;

				case 1:
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Tournament.Money));

					pchar.questTemp.tournamentcount = sti(pchar.questTemp.tournamentcount) + 1;
					if(sti(pchar.questTemp.tournamentcount) >= 1) UnlockAchievement("AchTurnir", 1);
					if(sti(pchar.questTemp.tournamentcount) >= 3) UnlockAchievement("AchTurnir", 2);
					if(sti(pchar.questTemp.tournamentcount) >= 7) UnlockAchievement("AchTurnir", 3);

					if (rand(3) == 0 && !CheckAttribute(pchar,"ScamFanActive"))
					{
						pchar.quest.SpawnScamFan.win_condition.l1 = "Location";
						pchar.quest.SpawnScamFan.win_condition.l1.location = "FencingTown_ExitTown";
						pchar.quest.SpawnScamFan.win_condition = "SpawnScamFan";
						pchar.ScamFanActive = true;
					}

					bool nopirate = false;
					if (!CheckAttribute(pchar,"questTemp.UniquePirate.Barbarigo") || !CheckAttribute(pchar,"questTemp.UniquePirate.BlackBeard") || !CheckAttribute(pchar,"questTemp.UniquePirate.Levasser")) nopirate = true;
					if (sti(pchar.questTemp.tournamentcount) == 3 && nopirate)
					{
						aref item;
						Items_FindItem("map_full", &item);
						string type = GetUniquePirateName();
						FillMapForUniqueTreasure(item, type);
						type = GetUniquePirateNameString(type);
						GiveItem2Character(pchar, "map_full");
						dialog.text = LinkRandPhrase("Да-а, турнир удался на славу. И вы стали его победителем! Признаюсь честно, я не мог оторвать глаз от того, как вы управляетесь с оружием! Теперь эти " + sti(PChar.Arena.Tournament.Money) + " золотых по праву принадлежат вам.", "Капитан, вы - чемпион! Такого умения обращаться с оружием не ожидали даже самые яростные соперники! Возьмите ваш приз - эти " + sti(PChar.Arena.Tournament.Money) + " золотых.", "Да вы их всех чуть в ласкуты не разорвали! Вот это хватка! Эти " + sti(PChar.Arena.Tournament.Money) + " золотых по праву ваши.");
						dialog.text = dialog.text + "\nТак как вы стали уже трёхкратным победителем турнира, мы решили приготовить кое-что особенное... Это будет карта сокровищ, что по слухам, она принадлежала знаменитому "+type+". Полагаю, вам будет по силам разыскать то, что спрятал этот злодей.";
						link.l1 = "Вот это поистене королевский подарок с вашей стороны! Премного благодар"+GetSexPhrase("ен!","на!");
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = LinkRandPhrase("Да-а, турнир удался на славу. И вы стали его победителем! Признаюсь честно, я не мог оторвать глаз от того, как вы управляетесь с оружием! Теперь эти " + sti(PChar.Arena.Tournament.Money) + " золотых по праву принадлежат вам.", "Капитан, вы - чемпион! Такого умения обращаться с оружием не ожидали даже самые яростные соперники! Возьмите ваш приз - эти " + sti(PChar.Arena.Tournament.Money) + " золотых.", "Да вы их всех чуть в ласкуты не разорвали! Вот это хватка! Эти " + sti(PChar.Arena.Tournament.Money) + " золотых по праву ваши.");
						int randreward = drand2(100);
						string reward;
						if (randreward < 6)
						{
							int quality = 1;
							if (pchar.rank <= 6) quality = 1;
							if (pchar.rank >= 12) quality = 2;
							if (pchar.rank >= 18) quality = 3;
							if (pchar.rank > 24) quality = 4;
							reward = "book"+quality+"_"+sti(drand(13)+1);
						}
						if (randreward >5 && randreward < 17)
						{
							switch (drand(11))
							{
								case 0: reward = "blade19"; break;
								case 1: reward = "blade22"; break;
								case 2: reward = "blade36"; break;
								case 3: reward = "blade37"; break;
								case 4: reward = "blade31"; break;
								case 5: reward = "blade34"; break;
								case 6: reward = "blade40"; break;
								case 7: reward = "blade46"; break;
								case 8: reward = "blade15"; break;
								case 9: reward = "blade21"; break;
								case 10: reward = "blade42"; break;
								case 11: reward = "topor2"; break;
							}
						}
						if (randreward >16 && randreward < 28)
						{
							switch (drand(4))
							{
								case 0: reward = "pistol6"; break;
								case 1: reward = "pistol_grapebok"; break;
								case 2: reward = "pistol9"; break;
								case 3: reward = "mushket"; break;
								case 4: reward = "mushket_drob"; break;
							}
						}
						if (randreward >17 && randreward < 39)
						{
							switch (drand(2))
							{
								case 0: reward = "cirass2"; break;
								case 1: reward = "cirass3"; break;
								case 2: reward = "cirass4"; break;
							}
						}
						if (randreward >38 && randreward < 50)
						{
							switch (drand(7))
							{
								case 0: reward = "indian1"; break;
								case 1: reward = "indian10"; break;
								case 2: reward = "indian15"; break;
								case 3: reward = "indian18"; break;
								case 4: reward = "indian19"; break;
								case 5: reward = "indian20"; break;
								case 6: reward = "indian21"; break;
								case 7: reward = "indian22"; break;
							}
						}
						if (randreward > 49)
						{
							GiveItem2Character(pchar,"Chest");
							reward = "icollection";
						}
						GiveItem2Character(pchar,reward);

						int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
						aref item1;
						Items_FindItem(reward, &item1);
						dialog.text = dialog.text + "\nПомимо денежного приза, мы также решили сделать вам особый подарок за победу. Это "+LanguageConvertString(idLngFile, item1.name)+".";
						LanguageCloseFile(idLngFile);
						link.l1 = LinkRandPhrase("Неужели ты во мне сомневался!", "Я ещё не раз покажу, кто здесь главный. А сейчас - отдыхать.", "Ха-ха-ха, жалкие насекомые! Таких соперников я на абордаже щёлкаю как орехи. Кстати, орехи полезны для здоровья.");
						link.l1.go = "exit";
					}
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;
			}
		break;

		case "FightInArena_8":
			dialog.text = LinkRandPhrase("А-а, вот и вы, капитан " + GetFullName(pchar) + ". Рад видеть вас тут. Надеюсь, что вам сегодня повезёт.", "А-а, вот и вы, капитан " + PChar.lastname + ". Ваша ставка должна непременно сыграть!", "А-а, вот и вы, капитан " + PChar.lastname + ". Думаю, что сегодня удача повернётся к вам лицом, а не как в прошлый раз...") + " Займите ваше место - пройдите в-о-о-о-н туда ...(показывает влево)... и поднимитесь на башню.";
			link.l1 = LinkRandPhrase("Это не удача - а холодный расчёт. Вот увидишь, я выиграю.", "Удача меня ещё никогда не покидала.", "Приготовьте мои денежки.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;

		case "FightInArena_9":
			switch(sti(PChar.Arena.Odds.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("Да-а, бои были что-надо! Но, к сожалению, ваша ставка не сыграла.. Будем ждать вас вновь - быть может, в следующий раз вы окажетесь более удачливы в ставках.", "Не повезло вам сегодня, капитан. Но игра продолжается! Э-э..", "Тот боец был близок к тому, чтобы принести вам кучу денег. Но не удалось.");
					link.l1 = LinkRandPhrase("Я так не играю!! Отдай мне деньги!", "Эх, не свезло. Но ты видел, как он ему вдарил, перед тем как упасть...", "Ну ничего, я ещё возьму своё, будь уверен!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;

				case 1:
					dialog.text = LinkRandPhrase("Да-а, бои были что-надо! Кроме того, ваша ставка сыграла и теперь эти " + sti(PChar.Arena.Odds.Prize) + " золотых по праву принадлежат вам. Честное слово, я был другого мнения о исходе поединков, но, похоже, я ещё слишком мало знаю о соотношении сил...", "Вот это да! Никто не предвещал такого хода событий, а вы смогли верно назвать победителя! Браво, браво! Вот ваши " + sti(PChar.Arena.Odds.Prize) + " золотых в качестве выигрыша.", "Ну вы капитан и знаток! Так разобраться в соотношении сил дуэлянтов! Вот это да! Никто не предвещал такого хода событий, а вы смогли верно назвать победителя! Браво, браво! Вот ваши " + sti(PChar.Arena.Odds.Prize) + " золотых!");
					link.l1 = LinkRandPhrase("Хе-хе, учись пока я жи"+ GetSexPhrase("в","ва") +".", "Ну так, мастерство не пропьёшь. Советую иногда слушать и других.", "Благодарю. Обязательно сюда вернусь.");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Odds.Prize));
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;
			}
		break;

		case "FightInArena_10":

			dialog.text = LinkRandPhrase("А вот и вы, " + GetFullName(pchar) + "! Добро пожаловать на наши поединки. Надеюсь, вам понравится наше мероприятие.", "Приветствую, кэп. Сегодня у нас намечаются очень серьёзные поединки.", "Я уверен, вам понравится наше мероприятие.") + " Займите ваше место - пройдите в-о-о-о-н туда ...(показывает влево)... и поднимитесь на башню.";
			link.l1 = LinkRandPhrase("Я тоже ра"+ GetSexPhrase("д","да") +" оказаться здесь. С удовольствием займу своё место.", "Надеюсь, здесь проводят серьёзные поединки, а не песочницу делят.", "Давай, начинай уже своё мероприятие.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;

		case "FightInArena_11":
			dialog.text = LinkRandPhrase("Да-а, поединки явно удались! Я не успевал восхищаться умением этих людей обращаться с оружием. Будем рады повторной встрече. А пока, до новых поединков!", "Да-а, ребята явно не оплошали - какой накал страстей, какое умение!", "Зря вы сами не поучаствовали в наших мероприятиях.");
			link.l1 = LinkRandPhrase("Мне не меньше чем вам понравились поединки. Спасибо, и до свидания.", "Да, бои вышли что надо. С удовольствием ещё раз приду сюда.", "Архг! В следующий раз са"+ GetSexPhrase("м","ма") +" поучаствую в этих мероприятиях - тогда посмотрят, что такое настоящий поединок.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaOddsTheEnd");
		break;

		case "EnemyFightInArena_1":
			dialog.text = LinkRandPhrase("Ну что, гот"+ GetSexPhrase("ов","ова") +" отдать свои деньги мне? Жду-не дождусь твоего поражения.", "Да я порву тебя в клочья, насекомое!", "Приготовься уйти ни с чем, ничтожество!");
			link.l1 = LinkRandPhrase("Хех. Не зарекайся, мой друг. Приступим к делу.", "Заткни свою пасть, гнилой кокос. Сейчас я тебя на тряпки пущу.", "Ха-ха, сейчас посмотрим, кто из нас уйдёт ни с чем.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelStartBattleWithEnemy");
		break;

		case "FightInArena_6":
			dialog.text = RandSwear() + " " + LinkRandPhrase("В схватке со мной тебя ждёт только неудача!",+ GetFullName(pchar) + "?! Я порву тебя на куски, если ты будешь у меня на пути!", "Эй, ты! Сейчас ты пожалеешь, что приш"+ GetSexPhrase("ёл","ла") +" сюда!");
			link.l1 = LinkRandPhrase("Сейчас ты уйдёшь отсюда ни с чем!", "Ха-ха, жалкий недоносок будет со мной спорить?", "Сейчас я тебя...");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaTournamentGo");
		break;
		// На арене <--

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдешь. Зато найдешь несколько дюймов холодной стали под ребро!"),
					LinkRandPhrase("Что тебе нужно, негодяй?! Городская стража уже взяла твой след, далеко тебе не уйти, грязный пират!", "Грязный убийца! Стража!!!", "Я не боюсь тебя, мерзавец! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живется же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"),
					RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Я тебя предупредил. А дальше сам смотри, нарываться или нет...";
					link.l1 = "Хех!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Что тебе надо в моем доме, негодяй?! Даю тебе десять секунд, чтобы ты убрался отсюда!";
					link.l1 = LinkRandPhrase("Хех, и здесь меня знают!", "Слава моя идет впереди меня...", "Хм, понятно.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Рад приветствовать вас в моем доме. Вы по делу ко мне?",
						"Чем я могу вам помочь?",
						"Хм, что я могу сделать для вас?",
						"Простите, если я вам не нужен, я попрошу вас меня не беспокоить...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Нет, просто осматриваю город, знакомлюсь с жителями...",
						"Да так, ничем особенным...",
						"Ничего...",
						"Хорошо, как скажешь.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Простите, вы не вовремя появились у меня дома - ночь на дворе. Я прошу вас покинуть мой дом!",
						"Я уже говорил, что время позднее. Прошу вас уйти.",
						"Не хочу показаться грубым, но я настаиваю, чтобы вы немедленно покинули мой дом!",
						"Черт возьми, что это такое?! Стража, воры!!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Хорошо, я понимаю...",
						"Да, сейчас...",
						"Ладно, не кипятись.",
						"Заткнись, какие воры?!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "О-о, разрешите представиться - " + GetFullName(npchar) + ". Мы рады вас видеть, законы гостеприимства для нашего города - не пустой звук.";
			link.l1 = GetFullName(pchar) + ", с вашего позволения...";
			link.l1.go = "exit_setOwner";
		break;

		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты вор, милейший! Стража, держи его!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи вора!!!", "Стража! Грабят!!! Держи вора!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
			link.l2 = "Если ты издашь ещё один звук - тебе конец!..";
			link.l2.go = "FackYou_1";
			link.l3 = "Я.. Я.. Я всё верну!..";
			link.l3.go = "FackYou_2";
		break;

		case "FackYou_1":
			dialog.text = "Что?.. Да ты смельчак, я посмотрю... Убирайся к дьяволу, чёртов прходимец!";
			link.l1 = "Чёрт!..";
			if(NPChar.sex == "man")
			{
				link.l1.go = "fight";
			}
			else
			{
				link.l1.go = "exit_setOwner3";
			}
		break;

		case "FackYou_2":
			dialog.text = "Конечно вернёшь... Хм, плати " + sti(PChar.StealItemsMoney) +  " золотых прямо сейчас и можешь убираться на все четыре стороны. Можешь быть уверен, всё будет как надо.";
			if(sti(PChar.money)>= sti(PChar.StealItemsMoney))
			{
				link.l1 = "Хорошо.. Вот твои деньги.";
				link.l1.go = "exit_setOwner2";
			}
			else
			{
				link.l2 = "Но у меня нет таких денег... Простите меня..";
				link.l2.go = "FackYou_3";
			}
			link.l3 = "Вот ещё! Я возьму здесь всё что захочу!";

			if(NPChar.sex == "man")
			{
				link.l3.go = "fight";
			}
			else
			{
				link.l3.go = "exit_setOwner3";
			}
		break;

		case "FackYou_3":
			dialog.text = "Что ты сказал, вор проклятый?";
			link.l1 = "Чёрт!..";

			if(NPChar.sex == "man")
			{
				link.l1.go = "fight";
			}
			else
			{
				link.l1.go = "exit_setOwner3";
			}
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner2":
			AddMoneyToCharacter(PChar, -sti(PChar.StealItemsMoney));
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner3":
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "legend":
			dialog.text = "А, вы наверное про Скэма Геймса? Неужели настолько не повезло, что он пристал к вам?";
			link.l1 = "Кто он вообще такой?";
			link.l1.go = "legend_1";
		break;

		case "legend_1":
			dialog.text = "По слухам, он - некогда проклятый дурачок, который по настоящему фанател по фехтовальным чемпионатам. Однажды с ним что-то случилось и с тех пор он не ест, не пьёт и не получает абсолютно никакого вреда от чего угодно. Уж поверьте, очень долго мы пытались отделаться от него.";
			link.l1 = "Он кажется совершенно безобидным... Но если он постоянно так себя ведёт - то прекрасно могу вас понять.";
			link.l1.go = "legend_2";
		break;

		case "legend_2":
			dialog.text = "Может вам повезёт, и вы найдёте способ избавиться от него не покидая архипелаг. Все его предыдущие ''жертвы'' уплывали в Европу и о них больше ничего не слышали.";
			link.l1 = "Есть хоть какие-нибудь мысли на этот счёт?";
			link.l1.go = "legend_3";
		break;

		case "legend_3":
			dialog.text = "Даже не знаю, что сказать на этот счёт. Тут разве что боги смогли бы помочь. Все возможные и невозможные способы избавиться от него мы уже опробовали.";
			link.l1 = "Боги, значит... Да, звучит совершенно бесперспективно, но спасибо хоть на этом.";
			link.l1.go = "exit";
			pchar.quest.RidScamFan.win_condition.l1 = "Location";
			pchar.quest.RidScamFan.win_condition.l1.location = "Temple_skulls";
			pchar.quest.RidScamFan.win_condition = "RidScamFan";
			pchar.KnowScam = true;
		break;

		case "Kraken":
			dialog.text = "Кракен вызван.";
			link.l1 = "Иду встречать.";
			link.l1.go = "exit";
			pchar.quest.SpawnScamFan.win_condition.l1 = "Location";
			pchar.quest.SpawnScamFan.win_condition.l1.location = "FencingTown_ExitTown";
			pchar.quest.SpawnScamFan.win_condition = "SpawnScamFan";
			pchar.ScamFanActive = true;
			AddDialogExitQuestFunction("ArenaTournamentTheEnd");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
