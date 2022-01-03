void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

    Pchar.quest.FreeRandomOfficerIdx = NPChar.index;

	switch(Dialog.CurrentNode)
	{
		case "CitizenNotBlade":
			dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;

		//--> хорошист-саксонец
		case "Saxon":
			if (sti(PChar.reputation) >= 51)//при низкой репутации - в сад
			{
				dialog.text = "Приветствую вас, капитан! Я жду вас вот уже целый день...";
				link.l1 = "Ждёте? Меня!? Я не припоминаю, чтобы мы были знакомы.";
				link.l1.go = "Saxon_1";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Хорош гусь! Смотрите, сударь, по сторонам, а не в декольте встреченных дам","Сударыня! Я бы попросил вас не пытаться со мной флиртовать") +". Хоть я и в отставке, но порядок блюду...";
				link.l1 = "Какие мы нежные! Ступай, ветеран, своим курсом.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Saxon";
			}
		break;

		case "Saxon_1":
			dialog.text = "Это никогда не поздно наверстать. Разрешите представиться – Магнус фон Коккай-Штаде. Я служил разным королям и герцогам, сколько себя помню. В Европе стал лейтенантом в мушкетёрском полку, которому платила испанская корона... до недавних пор\nНо к губернатору прислали племянника, будь он неладен! – а этот юный прохвост захотел офицерский чин. Так что теперь в гарнизоне меньше одним саксонцем, но больше одним испанцем, что совсем не значит равнозначный обмен, если вы цените опыт, конечно же!";
			link.l1 = "Замечательно, сударь. Но вы так и не пояснили, почему ждали именно меня?";
			link.l1.go = "Saxon_2";
		break;

		case "Saxon_2":
			dialog.text = "Каждое утро я прихожу на пирс и спрашиваю у прибывающих капитанов, не нужен ли им глава абордажной роты. Бывшие сослуживцы рекомендовали вас, как весьма авторитетного, уважаемого, опытного и отважного командира"+ GetSexPhrase(".",", несмотря на то, что вы женщина.") +" Не хочу в расцвете лет служить под началом сосунка или оказаться в разбойничьей шайке.";
			link.l1 = "Говорите, вы были офицером?..";
			link.l1.go = "Saxon_3";
		break;

		case "Saxon_3":
			dialog.text = "Что значит 'был'? Капитан, я не был, я есть. Вот я. Я офицер, и буду им, запомните это. Если вам нужен порядок в строю и верное плечо в бою – располагайте мной, коли сойдёмся в цене. Я лишнего не возьму. Ровно столько, сколько хватит мне, чтобы разобраться с делами и раздать долги.";
			link.l1 = "Во сколько же в дальнейшем мне обойдутся ваши верный глаз, крепкая рука, надёжное плечо и прочие достоинства сына саксонских земель?";
			link.l1.go = "Saxon_4";
		break;

		case "Saxon_4":
			dialog.text = "Сорок тысяч единовременного пособия и небольшое жалование в дальнейшем. Лишних денег не клянчу, буду брать как и прочие, питаться стану из офицерского котла. От вас же попрошу пуль и пороха. Чем больше их предоставите, тем меньше останется причин для тревог и расстройства, ха-ха!";
			if(sti(Pchar.money) >= 40000)
			{
				link.l1 = "Годится! Вот ваши деньги, завершайте свои дела и ступайте на судно, я предупрежу, чтобы вам приготовили шконку.";
				link.l1.go = "Saxon_check";
			}
			link.l2 = "Вот это запросы! Приятно было познакомиться, герр офицер, но я привык"+ GetSexPhrase("","ла") +" больше доверять доброму клинку, чем чужому мушкету за своей спиной.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

        case "OnceAgain":
            NextDiag.TempNode = "OnceAgain";
			dialog.text = "Вот так встреча, капитан! Вы все-таки решили усилить свою команду бравым мушкетером?";
			link.l1 = "Вы правы, герр офицер, определённо правы. Напомните, во сколько вы оценили свою службу на моем корабле?";
			link.l1.go = "Saxon_4";
            link.l2 = "Нет, не решил"+ GetSexPhrase("","а") +". Счастливо оставаться, герр офицер.";
			link.l2.go = "exit";
		break;

		case "Saxon_check":
            if (FindFreeRandomOfficer() == -1)//если перебор с офицерами
            {
                dialog.text = "Хм. У вас полный комплект офицеров, капитан. Возвращайтесь, когда вы сможете дать мне работу.";
    			link.l1 = "Хорошо.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
    			break;
            }
			if (sti(PChar.reputation) < 51)//повторная проверка репутации, для второго и далее заходов
			{
				dialog.text = "Хм... Знаете, кэп, люди не лучшим образом отзываются о вас. Я же говорил, что не желаю служить в разбойничьей шайке!";
				link.l1 = "Какие мы нежные! Ступай, ветеран, своим курсом.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
			break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 21 + MOD_SKILL_ENEMY_RATE)//при низком авторитете - в сад
			{
                dialog.text = "Хм. Ничего личного, капитан, но хоть вас и считают героем, но ваши дела пока не слишком говорят за вас. Хочу быть уверен, что иду на службу к солидному человеку. Так что я, пожалуй, повременю наниматься к вам.";
    			link.l1 = "Что же, я не бегаю от трудностей, и ем по негодяю на завтрак, каждый день. Вы скоро обо мне услышите, не сомневайтесь. Пока же желаю здравствовать...";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
    			break;
            }
			dialog.text = "Вот и отлично. Клянусь служить верой и правдой. Вы не пожалеете о потраченных на меня деньгах.";
			link.l1 = "Надеюсь, я не прогадал"+ GetSexPhrase("","а") +".";
			link.l1.go = "Exit_hire_Saxon";
		break;
		//<-- хорошист-саксонец

		//--> плохиш-пират
		case "Lostpirate":
			if (sti(PChar.reputation) < 36)//при повышенной репутации - в сад
			{
				dialog.text = "Приветствую, кэп! Какое счастье вновь видеть человеческие лица и слышать живые голоса, а не отвратительный гомон пернатой братии.";
				link.l1 = "Что ты делаешь один в этом уединённом раю? Изучаешь повадки морских птиц?";
				link.l1.go = "Lostpirate_1";
			}
			else
			{
				dialog.text = "А ты счастлив"+ GetSexPhrase("чик","ица") +", кэп! Я чуть было не выстрелил, приняв за своего обидчика, хе-хе!";
				link.l1 = "Неизвестно, кому повезло больше. Ты ведь мог и промахнуться. А я просто хотел"+ GetSexPhrase("","а") +" тебе помочь.";
				link.l1.go = "exit_Rep";
				link.l1 = "Ты ведь мог и промахнуться. А мне стало интересно, я увидел"+ GetSexPhrase("","а") +" тебя с корабля. Отшельничаешь тут?";
				link.l1.go = "Lostpirate_1";
			}
		break;

		case "exit_Rep":
			NextDiag.TempNode = "Lostpirate";
			dialog.text = "Я никогда не промахиваюсь. Один выстрел – один труп. А то и два, как повезет. Так что не искушай судьбу своими благородными намерениями еще раз, мушкет заряжен.";
			link.l1 = "Ты мне тоже понравился, незнакомец. И я, пожалуй, последую твоему совету.";
			link.l1.go = "exit";
		break;

		case "Lostpirate_1":
			dialog.text = "Не угадали. Я скорее поэт, а не натуралист. Сочинительством занимаюсь для души, а пропитание добываю охотой. Ласковый шепот божественных муз хорошо слышен наедине с природой. Как поэт я, Николя Рималье, известен мало. Пока\nНо довольно популярен, как искусный стрелок. Так сказать, творец смертельных ран и маэстро залпов. Если человек талантлив, то талантлив во всём.";
			link.l1 = "Хм, и как же такой многогранный талант оказался в бухте необитаемого острова без судна, припасов и перспективы?";
			link.l1.go = "Lostpirate_2";
		break;

		case "Lostpirate_2":
			dialog.text = "(поёт)Трудно выжить в мире этом, без надежного мушкета, может это легче где-то - но не здесь, и не поэту\nМоя история может показаться нелепой, но всему виной злополучное пари, которое я заключил на свою голову со старшим помощником. Он имел глупость обвинить меня в том, что фуражирная команда вернулась с пустыми руками, потому что ее главный стрелок, в коем качестве меня в нее и назначили, не может попасть даже в акулью тушу. Нужно признать, я временами бываю излишне азартен\nВ этот раз, чтобы доказать свое мастерство, я должен был попасть в подброшенный пиастр. Желая посмеяться надо мной, старпом приказал стрелять, не выпуская монету из руки. Шутка у него не заладилась\nПуля оторвала ему палец и продырявила кисть вместе с монетой. Получается, что спор я выиграл. Это признали все. Видимо, поэтому и догоняли меня, несмотря на страшную брань старпома, неохотно. А я как был, с песней в душе и мушкетом в руках, так в зарослях и схоронился\nСудно ушло, с припасами и перспективой. Вот и весь сказ. Так что я давненько промышляю тем, что бью чаек на завтрак, обед и ужин.";
			link.l1 = "Забавная история. И что ты теперь собираешься делать?";
			link.l1.go = "Lostpirate_check";
		break;

        case "OnceAgainLP":
            NextDiag.TempNode = "OnceAgainLP";
			dialog.text = "Ну что, кэп, таки соблазнил"+ GetSexPhrase("ся","ась") +" моим песенным талантом? Или стрелковым? Я же говорю, что ты счастливчик - я до сих пор тут!";
			link.l1 = "Ты к тому же и плут, как я погляжу. Ты, вроде, хотел наняться на судно?";
			link.l1.go = "Lostpirate_check";
            link.l2 = "Очень может статься, что именно по этой причине на моем корабле команда до сих пор не перестреляла друг друга. Возможно, кто-то и поверит в твои россказни, но я сегодня слишком трезв"+ GetSexPhrase("","а") +" для этого.";
			link.l2.go = "exit";
		break;

		case "Lostpirate_check":
            if (FindFreeRandomOfficer() == -1)//если перебор с офицерами
            {
                dialog.text = "Хм. Я хотел бы пойти к вам на службу... Но вижу, у вас полный комплект офицеров, увы. А тесниться в кубрике с матросами я не намерен. Так что придется мне остаться в этой уютной бухте.";
    			link.l1 = "Да, вакансий у меня нет. Возможно, навещу тебя позже.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
    			break;
            }
			if (sti(PChar.reputation) >= 36)//повторная проверка репутации, для второго и далее заходов
			{
				if (!CheckAttribute(pchar,"RimalieDone"))
				{
					dialog.text = "Хм... Знаете, кэп, что-то вы мне не нравитесь. Еще сдадите властям, чего доброго... от святош можно чего угодно ждать. Лучше я останусь здесь, в этой уютной бухте.";
					link.l1 = "Удачи, соколиный глаз! Смотри, не одичай тут...";
					link.l1.go = "exit";
					link.l2 = "Так уж сразу и сдам? Хорошего мушкетёра ещё поискать надо, а ты создаешь подобное впечатление.";
					link.l2.go = "LPGoodSide";
					NextDiag.TempNode = "OnceAgainLP";
				}
				else
				{
					dialog.text = "Раз уж у вас удалось помирить меня с контрабандистами, то я не буду наглеть. 10000 пиастров и я ваш.";
					if (sti(pchar.money)>= 10000)
					{
						link.l1 = "Вот твои деньги. И надеюсь ты поумеришь свою скандальную натуру.";
						link.l1.go = "Exit_hire_Lostpirate";
					}
					link.l2 = "Как будут деньги, так сразу. Поиздержал"+ GetSexPhrase("ся","ась") +" я малость.";
					link.l2.go = "exit";
				}
				break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 31)//при низком везении - в сад
			{
                dialog.text = "Под рукой удачливого кэпа, лёгкого на подъём, я бы согласился и дальше бороздить моря. А с тобой, похоже, скорее не кураж поймаешь, а плетей.";
    			link.l1 = "Что же, если музы не заманят тебя в божественные дали, или дьявол не приберёт, то ещё встретимся. Думаю, совсем скоро.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
    			break;
            }
			dialog.text = "Возьмите меня к себе стрелком, не пожалеете! Я даже внесу посильный вклад в сегодняшнее меню - отдам всю добычу, ибо для настоящих друзей ничего не жалко!";
			link.l1 = "Почему бы и нет? Надеюсь, в моей команде ты ни с кем не станешь спорить.";
			link.l1.go = "Exit_hire_Lostpirate";
			link.l2 = "Я слышал"+ GetSexPhrase("","а") +" твою историю в другом варианте. Ты поднял руку на своего капитана, выбив ему выстрелом клинок, когда он хотел арестовать тебя за попытку мятежа. Мне нравятся отчаянные ребята вроде тебя, но я не хочу проверить твою меткость на собственной шкуре.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgainLP";
		break;
		case "LPGoodSide":
			dialog.text = "Если уж честно, мне откровенно осточертело торчать тут. Решите одну проблему и приплатите сверху - пойду с тобой.";
			link.l1 = "И чего же ты хочешь?";
			link.l1.go = "LPGoodSide_2";
		break;
		case "LPGoodSide_2":
			dialog.text = "Я уже давно мог добраться до цивилизации, да вот рассорился я с местными. Разок сорвал контрабандистам сделку, просто хотелось нормальной еды и разжиться пулями с порохом. А они судя по всему дали на лапу местному губернатору, который отдал приказ страже. Если увидят - положат на месте.";
			link.l1 = "С контрабандистами тебя помирить, значит?";
			link.l1.go = "LPGoodSide_3";
		break;
		case "LPGoodSide_3":
			dialog.text = "Они же люди обидчивые, из-под земли достанут. Пока мне получается прятаться, но я не уверен, что так будет вечно. Полагаю, что даже на другом острове они меня достанут.";
			link.l1 = "Попробую что-нибудь сделать. Жди моего возвращения.";
			link.l1.go = "LPGoodSide_4";
		break;
		case "LPGoodSide_4":
			dialog.text = "Что-ж, я попробую вам довериться и не пустить вам рефлекторно пулю в лоб по возвращению.";
			link.l1 = "Хе, если попадёшь...";
			link.l1.go = "exit";
			pchar.RimalieGood = 1;
			NextDiag.TempNode = "OnceAgainLPGood";
		break;
		case "OnceAgainLPGood":
			dialog.text = "Как успехи, капитан?";
			link.l1 = "Пока никак.";
			link.l1.go = "exit";
			if (CheckAttribute(pchar,"RimalieDone"))
			{
				link.l1 = "Проблема решена. Можешь присоединяться к моей команде. Кстати, сколько ты там хотел?";
				link.l1.go = "Lostpirate_check";
				NextDiag.TempNode = "OnceAgainLP";
			}
			else NextDiag.TempNode = "OnceAgainLPGood";
		break;
		//<-- плохиш-пират

		//--> приказы
        case "hired":
			NextDiag.TempNode = "Hired";
			dialog.text = "Какие будут распоряжения?";
			link.l2 = "Ты уволен. Я обойдусь без твоих услуг!";
			link.l2.go = "AsYouWish";
            Link.l5 = "Слушай мой приказ!";
            Link.l5.go = "stay_follow";
			Link.l3 = "Я хочу, чтобы ты держался на определенном расстоянии от цели.";
			Link.l3.go = "TargetDistance";

			// по тек локации определим можно ли тут приказать  -->
			if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
							if(Locations[FindLocation(PChar.location)].islandId != "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
							{
								NPChar.ColonyIdx = iTemp;
								Link.l7 = "Я назначаю тебя наместником этого города!";
								Link.l7.go = "Gover_Hire";
							}
                        }
                    }
                }
            }
			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
					{
						Link.l8 = "Я хочу назначить тебя управляющим колонии ''" + PChar.ColonyBuilding.ColonyName + "'', которую мы построили на острове Кайман.";
						Link.l8.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

            link.l9 = "Ничего. Вольно.";
			link.l9.go = "exit";
        break;
		//<-- приказы


		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "На каком именно, капитан? Укажите в метрах, но не более 20-ти.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;

		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Капитан, что за дурной тон!";
				link.l1 = "Извини, ошибочка вышла...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Я буду стоять на месте, никуда не двигаясь. Вас это устраивает, капитан?";
				link.l1 = "Да, именно это от тебя и требуется.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Я кажется говорил, что более 20 метров от цели мне держаться нельзя.";
				link.l1 = "Хорошо, держись на расстоянии в 20 метров.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Задачу понял, принимаю к сведению.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы

		//--> найм
        case "Exit_hire_Saxon":
			npchar.HalfImmortal = true;
			AddMoneyToCharacter(Pchar, -40000);
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral7", 1);
			TakeNItems(npchar, "indian17", 1);
			TakeNItems(npchar, "potionwine", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_hire_Lostpirate":
			if(CheckAttribute(pchar,"RimalieDone"))
			{
				AddMoneyToCharacter(pchar,-10000);
				npchar.reputation = 51;
				npchar.alignment = "good";
				DeleteAttribute(pchar,"RimalieDone");
			}
			npchar.HalfImmortal = true;
			TakeNItems(pchar, "Mineral4", 5);
			Log_Info("Вы получили бакланов");
			PlaySound("interface\important_item.wav");
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral2", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			locations[FindLocation("Shore59")].DisableEncounters = false; //энкаутеры в бухте откроем
		break;
		//<-- найм

		//--> увольнение
		 case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Капитан, хоть мне и непонятна причина такого заявления - давайте вернёмся к этому вопросу на берегу. Или вы решили просто выбросить меня за борт?";
					Link.l1 = "Хм... нет, я не это имел"+ GetSexPhrase("","а") +" в виду. Оставайся, пока не придём в порт.";
					Link.l1.go = "Exit";
					break;
				}
			}
			// проверка на море <--
			dialog.text = "Как скажете, капитан, решать вам. Второго такого мушкетера вам не найти.";
			link.l1 = "Пожалуй, я передумал"+ GetSexPhrase("","а") +". Ты мне еще нужен.";
			link.l1.go = "exit";
			link.l2 = "И не надо. Можешь проваливать, куда подальше.";
			link.l2.go = "Exit_Fire";
		break;

		case "exit_fire":
   			NextDiag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Fired":
		      NextDiag.TempNode = "Fired";
		      dialog.text = "Я же предупреждал вас, что не вернусь на ваш корабль. Пойду, наймусь к другому капитану.";
		      Link.l1 = "Да ты мне и не нужен.";
		      Link.l1.go = "Exit";
	    break;
		//<-- увольнение

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		//--> стоять-следовать
		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			if (!CheckAttribute(npchar,"AboardRestriction"))
			{
				Link.l4 = "Прошу тебя не участвовать в абордажах. Побереги себя.";
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = "Я передумал, можешь участвовать в абордажах.";
				Link.l4.go = "AboardAllowed";
			}
        break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "Так точно капитан. Не буду участвовать в абордажах, пока вы снова не разрешите.";
            Link.l1 = "Ну и хорошо.";
            Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar,"AboardRestriction");
			dialog.text = "Так точно капитан. Буду участвовать в абордажах с текущего момента.";
            Link.l1 = "Ну и хорошо.";
            Link.l1.go = "exit";
		break;

        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;

        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
        break;
		//<-- стоять-следовать

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Почту за честь!";
            Link.l1 = "Следи за порядком и процветанием города, я буду иногда приплывать за собранной пошлиной.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
            Link.l2.go = "Exit";
            NextDiag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Какие будут приказания? Последний ваш визит был " + FindRussianDaysString(iTemp) + " назад.";
			}
			else
			{
			    dialog.Text = "Какие будут приказания?";
			}

            Link.l1 = "Какую сумму налогов ты " + NPCharSexPhrase(NPChar, "собрал", "собрала") + " на данный момент?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Ты " + NPCharSexPhrase(NPChar, "нужен", "нужна") + " мне на корабле, я снимаю тебя с городской службы.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Всего хорошего.";
            Link.l9.go = "Exit";
            NextDiag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Мои навыки позволяют мне собирать " + FindRussianMoneyString(iFortValue*iTax) + " в день. За " + FindRussianDaysString(iTemp) + " я " + NPCharSexPhrase(NPChar, "собрал", "собрала") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Я хочу забрать всю сумму налогов.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Благодарю за службу!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
            Link.l8 = "Вот и славно.";
            Link.l8.go = "exit_hire";
            NextDiag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Внимательно слушаю.";
			Link.l1 = "Это касается абордажа.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Это касается твоего корабля.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Я хочу, чтобы ты на время выш"+ GetSexPhrase("ел","ла") +" из состава моей эскадры и поискал удачу самостоятельно.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Пока ничего.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не брал"+ GetSexPhrase("","а") +" корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно чтобы ты брал вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не менял"+ GetSexPhrase("","а") +" свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врагов на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	}
}
