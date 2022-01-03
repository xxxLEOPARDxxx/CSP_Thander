// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting() + "! Я "+ GetFullName(NPChar) + ", новый наместник в этой дыре. К сожалению, призвать к порядку местный сброд довольно трудно, но угрозы от них для Испанских колоний больше не будет.";
					Link.l1 = "Рад"+ GetSexPhrase("","а") +" знакомству. Я капитан " + GetFullName(Pchar) + ". Мне уже пора.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting() + ". Я занят, очень много дел, нужно контролировать настроение местных жителей, дабы пресечь угрозу колониям Испании.";
					Link.l1 = "Не буду мешать.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("У тебя ко мне дело? Нет? Тогда "+ GetSexPhrase("выметайся отсюда!","попрошу не отвлекать меня.") +"",
	                         "Я, кажется, ясно выразился...", "Хотя я выразился и ясно, но ты продолжаешь отвлекать меня!",
	                         "Хм, да ты не в меру "+ GetSexPhrase("хамовит, мон шер","нагла, деваха") +"...", "repeat", 30, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Уже ухожу.",
	                                               "Да, " + npchar.name + ", совершенно ясно.",
	                                               "Извини, " + npchar.name + "...",
	                                               "Ай, ай...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
					{
						link.l2 = "Может какая работенка для меня найдется?";
						link.l2.go = "pirateStartQuest";
					}
					else
					{
						if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
						{
							link.l2 = "Я выш"+ GetSexPhrase("ел","ла") +" на след, но мне нужны деньги - 30 000 пиастров, чтобы выманить крысу из норы.";
							link.l2.go = "pirateStartQuest_many";
						}
						if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
						{
							link.l2 = "Посмотри, что за письмо я наш"+ GetSexPhrase("ел","ла") +" на трупе одного из контрабандистов.";
							link.l2.go = "pirateStartQuest_info_1";
						}
						if(pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
						{
							link.l2 = "Дело сделано. Норман Виго вместе со своей лоханкой отправился к морскому дьяволу.";
							link.l2.go = "pirateStartQuest_final";
						}
					}
					if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
					{
						link.l3 = "Есть какое-нибудь интересное дело для меня?";
						link.l3.go = "pirateVikingQuest";
					}
					else
					{
						if(pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
						{
							dialog.text = "Вижу ты с новостями?"
							link.l1 = "Да, завалил"+ GetSexPhrase("","а") +" таки северянина, ох и лютый же был. Обычно все разговоры заводят как смерть почуят, а этот рычал только аж пена изо рта шла.";
							link.l1.go = "pirateVikingQuest_final";
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		//Blackthorn. Квест викинга
		case "pirateVikingQuest":
			dialog.text = "Для тебя найдётся работёнка. Ты не только саблей "+ GetSexPhrase("остёр","остра") +", но и умом, как мне рассказывали. Слушай сюда. Появился пару лет назад в наших водах скандинав какой то, то ли датчанин, то ли швед, неважно, Рагнаром назвался. Корабль у него просто загляденье и команда сплошняком из норманов состоит. И вроде как, всё ничего, пиратствует помаленьку, гроши на хлеб зарабатывает, вот только долю в общий котёл не вносит, губернаторам грубит, призы вообще неизвестно где сбывает. Смекаешь к чему разговор?";
			link.l1 = "Смекаю, наказать его нужно, так чтоб примером стал. Вот только это не по законам берегового братства как то. Ну, зарвался пират, так пусть шепнет кто властям где он обитает. И к нам, честным корсарам никаких претензий, никто не предъявит.";
			link.l1.go = "pirateVikingQuest_1";
			link.l2 = "Что-то не нравится мне этот разговор. Прощай...";
			link.l2.go = "exit";
			pchar.questTemp.pirateVikingQuest = "0";
		break;
		case "pirateVikingQuest_1":
			dialog.text = "Законы братства, Кодекс, пиратская честь… Пфф… Детские шалости это. Ты ещё Либерталию вспомни, которую Шарп построить пытался. Ха-ха! Тут у нас баланс сил существует, власти закрывают глаза на наши делишки, если мы их делишкам не мешаем. А вдруг в Европе мир подпишут? Так и патенты отзовут, а все бравые каперы в один миг преступниками станут. И приплывут карательные эскадры. Нас с тобой ловить. А такие капитаны, как этот викинг, репутацию нам всем портят. Смекаешь?";
			link.l1 = "Понял"+ GetSexPhrase("","а") +", дал ты мне пищу для размышлений. Где искать этого викинга?";
			link.l1.go = "pirateVikingQuest_2";
		break;
		case "pirateVikingQuest_2":
			dialog.text = "Где то. Знал бы где обитает, сам бы в море вышел, не посмотрел бы на старые раны и возраст. Ты у нас смекалист"+ GetSexPhrase("ый","ая") +", разберёшься. Одно условие – Рагнар этот и вся его команда на корм рыбам пойти должна, а золотишком я не обижу.";
			link.l1 = "Жди новостей. Да и про отзыв патентов, если новости будут, дай знать. Бывай, "+GetFullName(npchar)+".";
			link.l1.go = "exit";

			pchar.questTemp.pirateVikingQuest = "1";
			pchar.questTemp.pirateVikingQuest.City = npchar.city;
			pchar.questTemp.pirateVikingQuest.Areal = GetArealByCityName(pchar.questTemp.pirateVikingQuest.City);
			pchar.questTemp.pirateVikingQuest.Name = GetFullName(npchar);
			pchar.LastHearedViking = npchar.city;
			AddQuestRecord("pirateVikingQuest", "1");
			AddQuestUserData("pirateVikingQuest", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateVikingQuest.City + "Gen"));
			AddQuestUserData("pirateVikingQuest", "sName", pchar.questTemp.pirateVikingQuest.Name);
		break;
		case "pirateVikingQuest_final":
			CloseQuestHeader("pirateVikingQuest");
			TakeNItems(pchar, "chest", 5);
			Log_Info("Вы получили кредитные сундуки");
			dialog.text = "Ага, читал как то. Берсерк видать. Прямо осколок прошлого. Вот, держи награду, заслужил"+ GetSexPhrase("","а") +".";
			pchar.questTemp.pirateVikingQuest = "end";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Хм... работенка, говоришь? А это даже очень хорошо, что ты ко мне обратил"+ GetSexPhrase("ся","ась") +". Мне как раз нужен человек со стороны. Необходимо кое-что разузнать в соседнем поселении, а моих ребят там знают, как облупленных. Много денег не обещаю, но кое-что перепадет.";
			link.l1 = "Вот и славно. А что за дело?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Извини, за копейки я рисковать не буду. Прощай...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "А дело в следующем - с месяц назад сговорился я с капитаном шхуны 'Сентблу' о доставке 200 рабов, чтобы продать их одному плантатору из соседнего поселения. Уже и сроки поджимать стали, и заказчик нервничать, и вот вчера мне сообщают, что эту шхуну видели в акватории острова. Но!.. капитан у меня не появился. А сегодня плантатор потребовал вернуть задаток и сказал, что рабов ему предложили в другом месте - хоть и дороже, но всю партию и сразу.";
			link.l1 = "И что? Я долж"+ GetSexPhrase("ен","на") +" в считанные дни раздобыть 200 рабов, чтоб ты не потерял задаток? И все это за копейки?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Нет, конечно. Разве я похож на идиота? Задаток я не верну в любом случае. Но мне нужны доказательства, что рабы, которых ему подсовывают - это и есть моя партия. А ты просто найдешь тех, кто предложил ему новую сделку, и получишь свои 10 000 пиастров. Остальное моя забота. Ну что, берешься?";
			link.l1 = "Берусь! А кто это может быть? Есть какие-то соображения?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Нет. Искать непонятно кого, непонятно где и всего за 10 000 - извини, не возьмусь.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Если бы у меня был хоть намек, я обошелся бы и без твоих услуг. Они бы уже к ночи ловили кальмаров на живца. Но меня больше интересует другое - как они узнали о грузе 'Сентблу' и о моем заказчике? Уж очень все быстро у них срослось. Смекаешь?";
			link.l1 = "Да, явно кто-то приторговывает сведениями.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Вот! Вот его и ищу. Поэтому тихо прирезать конкурентов и вернуть рабов - в этом деле не главное. Мне нужен информатор, а вернее - его голова на вертеле. Теперь ты понимаешь, почему никто из моих об этом задании знать не должен? Пока я не выясню, кто продает информацию - подозревать буду каждого. А мне этого очень не хочется...";
			link.l1 = "Понятно... Значит, будем действовать тихо и не поднимать волну. Отправляюсь на поиски.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Тридцать тысяч, говоришь? Это большая сумма... Могу дать только 5000 пиастров, больше у меня сейчас нет. Но если вздумаешь сбежать с ними - найду и повешу на ближайшем заборе! Со мной такие шутки не пройдут.";
			link.l1 = "Давай пять тысяч...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Вот, держи. Жду результаты поиска.";
			link.l1 = "Все будет в порядке.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ха! Отличная новость! Я был уверен, что ты с этим справишься. Ко мне попала весьма любопытная информация.";
			link.l1 = "Я работу свою выполнил"+ GetSexPhrase("","а") +". Хочу получить свои десять тысяч.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Конечно, вот обещанная награда. Но ты не спеши, я хочу поручить тебе еще одно дело\nПфайфер - это человек из команды Нормана Виго, который ходит на люггере 'Септима'. Я уверен, что Норман Виго и есть информатор, хотя он и из наших. Его недавно видели в акватории острова, твоя работа - отправить крысу к морскому дьяволу. В первый раз ты меня не подвел"+ GetSexPhrase("","а") +", поэтому и сейчас хочу поручить это дело тебе. Заплачу 15 000 пиастров. Соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Берусь! Считай, что предатель Норман Виго уже покойник.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Знаешь что, неохота мне в это ввязываться... Да и некогда. Извини, но я пас.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Знаем-знаем. Мои люди наблюдали бой и уже доложили мне, как ты здорово управил"+ GetSexPhrase("ся","ась") +". Ну что ж, дело свое ты исправно сделал"+ GetSexPhrase("","а") +", вот обещанная награда в 15 000 пиастров. И спасибо тебе, здорово ты мне помог"+ GetSexPhrase("","ла") +".";
			link.l1 = "Все в порядке, рад"+ GetSexPhrase(" был","а была") +" помочь! А теперь меня ждут дела, я и так здесь задержал"+ GetSexPhrase("ся","ась") +". До встречи!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;

		//********************* Английская линейка *********************
 		case "EngLine_quests":
			dialog.text = "Я слушаю вас, капитан.";
			link.l1 = "Я прибыл"+ GetSexPhrase("","а") +" к вам по поручению генерал-губернатора Ямайки сэра Томаса Мэдифорда.";
			link.l1.go = "Step_1";
  		break;
 		case "Step_1":
			dialog.text = "Слушаю внимательно.";
			link.l1 = "Сэр Томас Мэдифорд просит вас собрать каперскую эскадру, возглавить ее и атаковать голландский форпост в Карибском море - город Кюрасао.";
			link.l1.go = "Step_2";
  		break;
 		case "Step_2":
			dialog.text = "Хм... А в чем причина такого решения? Признаюсь, оно выглядит странным. Англичане не нападают на голландцев. Да, у государств есть противоречия в торговой экспансии, но они распространяются на Индийский океан. Здесь же - Новый свет.";
			link.l1 = "Сэр, между Англией и Голландией разразилась очередная торговая война. Более того, британский военный флот совершил нападение на голландцев у берегов Европы, но был отбит.";
			link.l1.go = "Step_3";
  		break;
 		case "Step_3":
			dialog.text = "Понятно. Благодарю за информацию. Я этого не знал.";
			link.l1 = "Итак, я жду вашего согласия на экспедицию.";
			link.l1.go = "Step_4";
  		break;
 		case "Step_4":
			dialog.text = ""+ GetSexPhrase("Друг мой, я","Я") +" не могу вам дать положительного ответа на просьбу генерал-губернатора Ямайки.";
			link.l1 = "Теперь МНЕ кажется ваш ответ весьма странным.";
			link.l1.go = "Step_5";
  		break;
 		case "Step_5":
			dialog.text = "Ничего странного. Моя настоящая фамилия - Эдвард Мансвельт. Я - голландец.";
			link.l1 = "Но вы - английский капер, и пользуетесь покровительством сэра Томаса Мэдифорда. Мне кажется неразумным такой категоричный отказ от его просьбы.";
			link.l1.go = "Step_6";
  		break;
 		case "Step_6":
			dialog.text = "Вам может казаться все, что угодно. Я действительно имею английский каперский патент, но это отнюдь не означает того, что я буду резать глотки моим соотечественникам. Право выбора действий всегда за мной. Я ответил вам, более мне нечего сказать. Прощайте.";
			link.l1 = "Что ж, если вам больше нечего сказать, то прощайте.";
			link.l1.go = "exit";
            NextDiag.TempNode = "First time";
            AddQuestRecord("Eng_Line_2_Talking", "3");

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
			}
  		break;
 		case "No_Mansfield_first_time":
			dialog.text = "Добрый день, меня зовут Алистер Гуд. После гибели Мансфилда я выбран главой буканьеров.";
			link.l1 = "Будем знакомы, Алистер.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Мне сейчас некогда с тобой разговаривать. Зайди позже.";
			link.l1 = "Я уже ухожу.";
			link.l1.go = "exit";
  		break;
		//********************* Голландская линейка *********************
  		case "HolLine3_WormEngPlans":
			dialog.text = "Что привело тебя ко мне?";
			link.l1 = "Я прибыл"+ GetSexPhrase("","а") +" к вам по поручению генерал-губернатора Кюрасао Питера Стэвезанта.";
			link.l1.go = "Step_H3_1";
        break;
 		case "Step_H3_1":
			dialog.text = "Очень хорошо. Что нужно от меня генерал-губернатору Стэвезанту?";
			link.l1 = "Эдвард, англичане напали на Нидерланды, началась очередная торговая война.";
			link.l1.go = "Step_H3_2";
  		break;
 		case "Step_H3_2":
			dialog.text = "Печальная новость, у меня дела в Порт Рояле...";
			link.l1 = "Вот пакет от Стэвезанта, прошу ознакомиться.";
			link.l1.go = "Step_H3_3";
  		break;
 		case "Step_H3_3":
			dialog.text = "Так, ну давай посмотрим... Хм, он просит меня информировать его о том, что хочет предпринять Мэдифорд на Карибах в рамках участия в войне.";
			link.l1 = "Совершенно верно. Знать это - жизненная необходимость для голландских поселений.";
			link.l1.go = "Step_H3_4";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
  		break;
 		case "Step_H3_4":
			dialog.text = "Все дело в том, что я не знаю ничего о планах Мэдифорда по этой войне. У меня с ним дела другого порядка, политика здесь ни при чем.";
			link.l1 = "И что мне ответить Стэвезанту? Что вы ничего не знаете и ничем не сможете помочь своей родине в трудный час?";
			link.l1.go = "Step_H3_5";
  		break;
 		case "Step_H3_5":
			dialog.text = "Не надо пафосных выражений, "+ GetSexPhrase("молодой человек","девушка") +", я знаю, кто я такой. Но я действительно ничего не ведаю о планах Мэдифорда. Однако, вот что я тебе расскажу.\n"+
                          "Буквально на прошлой неделе ко мне заявился некий посланец от Мэдифорда, который уговаривал меня организовать экспедицию на Кюрасао. Я, естественно, отказался. Отказались также Морган, Джекмен и Джон Моррис.\n"+
                          "Итого получается, что известный пройдоха Томас Мэдифорд пытался открыть боевые действия против Нидерландов с помощью пиратов. Хитер, что тут еще скажешь...";
			link.l1 = "Получается, что Мэдифорд планирует напасть на Кюрасао?";
			link.l1.go = "Step_H3_6";
  		break;
 		case "Step_H3_6":
			dialog.text = "Планировать нападение на Кюрасао он может, а вот выполнить данное мероприятие - вряд ли. У него недостаточно сил для такой операции, не от хорошей жизни он пытался привлечь корсарство.\n"+
                          "Да и вообще, самой надежной охраной Порт Рояля от тех же испанцев является постоянное присутствие некоторого количества пиратов на рейде Ямайки. Так что нет, Кюрасао сейчас ему не по зубам.";
			link.l1 = "Ну что же, все ясно, нападения можно не опасаться...";
			link.l1.go = "Step_H3_7";
  		break;
 		case "Step_H3_7":
			dialog.text = "Я бы так категорично не мыслил. Дело в том, что раз попытка привлечения корсаров к нападению была, значит Мэдифорд все-таки имеет приказ открыть боевые действия. Так что мира здесь между Англией и Голландией не будет точно.\n"+
                          "Вот что я тебе предложу сделать - отправляйся немедленно в Порт Рояль к Генри Моргану.";
			link.l1 = "К Генри Моргану, адмиралу корсаров?";
			link.l1.go = "Step_H3_8";
  		break;
 		case "Step_H3_8":
			dialog.text = "Да, именно так. И не беспокойся, адмиралом он стал не без моего участия. Если быть точным, то этот титул именно я ему и передал. Попросишь его от моего имени помочь тебе.";
			link.l1 = "И он поможет?";
			link.l1.go = "Step_H3_9";
  		break;
 		case "Step_H3_9":
			dialog.text = "Если сможет помочь, то сделает это.";
			link.l1 = "Эдвард, вы не напишите мне письмо для Моргана, чтобы он поверил моим словам?";
			link.l1.go = "Step_H3_10";
  		break;
 		case "Step_H3_10":
			dialog.text = "Нет, это не обязательно. Вряд ли кто-то в своем уме будет вводить в заблуждение Моргана, такой человек долго не проживет. Он тебе поверит.";
			link.l1 = "Эдвард Мансвельд, вы настоящий сын своего Отечества. Спасибо вам за помощь!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_toMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "2");
    		QuestSetCurrentNode("Henry Morgan", "HolLine3_fromMansfield");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            LAi_SetHuberStayType(characterFromId("Henry Morgan"));
          break;


// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Пошел вон","Убирайся") +" отсюда!", "Вон из моего дома!");
			link.l1 = "Ой-ой-ой...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Тебе не стоит доставать меня, запомни это.";
        			link.l1 = "Я понял"+ GetSexPhrase("","а") +", Эдвард, больше не буду.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
