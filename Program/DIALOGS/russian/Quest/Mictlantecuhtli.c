
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arChestItems;
	string sBlade;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Не желаю разговаривать.";
			link.l1 = "Как хочешь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//должок ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = "Ты задолжал"+ GetSexPhrase("","а") +" моему адепту по имени Августо Брамс!";
			link.l1 = "Я?.. А-а, ну да, было дело... Гм, но только я не знал"+ GetSexPhrase("","а") +", что он твой адепт.";
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = "Тем не менее, это так. Ты долж"+ GetSexPhrase("ен","на") +" отдать мне немедленно " + FindRussianMoneyString(sti(pchar.questTemp.LSC_climeUsurer.qtyMoney )) + ". У тебя есть такие деньги?";
			if (sti(pchar.money) >= sti(pchar.questTemp.LSC_climeUsurer.qtyMoney))
			{
				link.l1 = "Гм, имеются...";
				link.l1.go = "ClimeUsurer_yes";
			}
			else
			{
				link.l1 = "Как-то все это неожиданно... Я же не знал"+ GetSexPhrase("","а") +", что так быстро надо будет рассчитаться.";
				link.l1.go = "ClimeUsurer_no";
			}
		break;
		case "ClimeUsurer_yes":
			dialog.text = "Хорошо. Тогда я отпускаю тебя.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LSC_climeUsurer.qtyMoney));
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;
		case "ClimeUsurer_no":
			dialog.text = "Не знал"+ GetSexPhrase("","а") +"?!!\nТогда ты останешься в храме Жертвы навечно! Одним черепом больше, одним меньше...";
			link.l1 = "Как же это так?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_noMoney");
		break;

		//в большом храме разговор перед боевкой
		case "InGreateTemple":
			dialog.text = "Как ты посмел"+ GetSexPhrase("","а") +", смертн"+ GetSexPhrase("ый","ая") +"?!!";
			link.l1 = "Оба-на!.. Если не ошибаюсь, то вы и есть тот самый бог мертвых.";
			link.l1.go = "InGreateTemple_1";
		break;
		case "InGreateTemple_1":
			dialog.text = "Это так\nЯ давно наблюдаю за тобой, твое рысканье по Теночтитлану занимало меня. Но сейчас ты взял"+ GetSexPhrase("","а") +" предмет моего культа, и это уже не смешно...";
			link.l1 = "Понимаете, уважаемый бог, мне заказал этот самый предмет некий ацтек, имя которого здесь произносить не принято.";
			link.l1.go = "InGreateTemple_2";
		break;
		case "InGreateTemple_2":
			dialog.text = "Монтесума? Ха-ха, никак не угомонится. Хотя, иначе и быть не может.\nНу что же, ты дотронул"+ GetSexPhrase("ся","ась") +" до нефритового черепа, а это является преступлением. Но ты сумел"+ GetSexPhrase("","а") +" нейтрализовать охрану, которая состоит их героев прошлого\nБолее всего на свете ацтеки почитают воинскую доблесть. Ты показал"+ GetSexPhrase("","а") +", что являешься хорошим воином,"+ GetSexPhrase(""," несмотря на то, что ты женщина,") +" поэтому я дам тебе шанс выжить. Докажи, что ты великий воин, и ты сможешь уйти отсюда.";
			link.l1 = "Что я долж"+ GetSexPhrase("ен","на") +" сделать?";
			link.l1.go = "InGreateTemple_3";
		break;
		case "InGreateTemple_3":
			dialog.text = "Сразиться со мной. Начнем!";
			link.l1 = "Деваться некуда...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_fightInTemple");
		break;

		//в большом храме разговор после боевки
		case "WinInTemple":
			dialog.text = "Ну что же, ты доказал"+ GetSexPhrase("","а") +", что досто"+ GetSexPhrase("ин","йна") +". Теперь ты можешь уйти отсюда жив"+ GetSexPhrase("ым","ой") +".";
			link.l1 = "Уф-ф-ф... Если хотите, я положу череп на место.";
			link.l1.go = "WinInTemple_1";
		break;
		case "WinInTemple_1":
			dialog.text = "Не надо, у меня таких много. Череп можешь взять себе, ты это заслужил"+ GetSexPhrase("","а") +".";
			link.l1 = "Спасибо вам, уважаемый бог.";
			link.l1.go = "WinInTemple_2";
		break;
		case "WinInTemple_2":
			dialog.text = "Прежде чем ты уйдешь, я хочу рассказать тебе, кто такой Монтесума.";
			link.l1 = "Очень интересно послушать.";
			link.l1.go = "WinInTemple_3";
		break;
		case "WinInTemple_3":
			dialog.text = "Это Монтесума Второй, последний вождь империи ацтеков. 150 лет назад он предал богов своего народа, когда попытался договориться с испанскими миссионерами о принятии христианства\n"+
				"Мы, боги ацтеков, не простили ему предательства и прокляли Монтесуму, хотя в итоге почти всем богам пришлось уйти в лимб. Здесь остался только я.";
			link.l1 = "Простите, уйти куда? В лимб?";
			link.l1.go = "WinInTemple_4";
		break;
		case "WinInTemple_4":
			dialog.text = "Боги живут только тогда, когда им поклоняются люди. Если богов забывают, то им приходится уйти в лимб, мир забвения. Я остался на Земле только потому, что теперь мне принадлежит весь народ ацтеков, ибо все ацтеки были истреблены испанцами, оставшись без нашей помощи.\n"+
				"Я обладаю властью заставлять мертвые тела жить новой жизнью. Став хозяином Теночтитлана, я поднимаю нужных мне усопших для несения службы.\n"+
				"Монтесума же проклят, ему закрыт ход в царство мертвых, и он принужден вечно ходить по берегам озера Тескоко и скорбеть по участи своего народа.";
			link.l1 = "Так это призрак?!";
			link.l1.go = "WinInTemple_5";
		break;
		case "WinInTemple_5":
			dialog.text = "Можно и так сказать. Теперь ты знаешь, кто такой ацтек на берегу Тескоко. И знай, что нефритовый череп имеет власть над мертвыми, а так же может помочь проклятым живым\nПрощай, воин.";
			link.l1 = "До свидания, уважаемый Митклан... Миктлан...";
			link.l1.go = "WinInTemple_6";
		break;
		case "WinInTemple_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			AddQuestRecord("Tenochtitlan", "4");
			AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("","а"));
			DialogExit();
		break;

		case "Samil":
			dialog.text = "Ты впечатлил"+ GetSexPhrase("","а") +" меня, смертн"+ GetSexPhrase("ый","ая") +". Ещё никому не удавалось одолеть моё земное воплощение. Знай же, что ты видишь самого Юм Самиля во плоти!";
			link.l1 = "Юм... кого? Я заглянул"+ GetSexPhrase("","а") +" в этот храм за ценностями, но не наш"+ GetSexPhrase("ёл","ла") +" здесь абсолютно ничего, кроме целой армии нежити.";
			link.l1.go = "Samil_2";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_1_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_1_woman");
		break;

		case "Samil_2":
			dialog.text = "Сколько же прошло лет, раз смертные уже позабыли моё имя...";
			link.l1 = "Полагаю, весьма и весьма много. Я никогда не слышал"+ GetSexPhrase("","а") +" о тебе.";
			link.l1.go = "Samil_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_2");
		break;

		case "Samil_3":
			dialog.text = "Полагаю, такова судьба всех богов ныне исчезнувших цивилизаций. Они забываются в пустоте, лишаясь сил из-за отсутствия притока силы от верующих...";
			link.l1 = "...";
			link.l1.go = "Samil_4";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_3");
		break;

		case "Samil_4":
			dialog.text = "Что-ж, не будем о грустном. Ты победил меня и заслуживаешь награды. Думаю, этот клинок предыдущего визитёра тебе пригодится.";
			link.l1 = "Благодарю тебя, Юм Самиль.";
			link.l1.go = "Samil_5";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			log_info("Вы получили Полуторный Фламберж от Юм Самиля");
			UnlockAchievement("AchUmSamil", 3);
			TakeNItems(pchar,"blade201",1);
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_4_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_4_woman");
		break;

		case "Samil_5":
			dialog.text = "Думаю, пришло время попрощаться. Расскажи об этой встрече людям. Не хочу быть забытым навечно, как все прочие... Не могу также просить тебя о поклонении, слишком уж разные у нас культуры. Прощай, воин.";
			link.l1 = "Обещаю никогда не забывать нашей встречи. Прощай!";
			link.l1.go = "Samil_6";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_5");
		break;

		case "Samil_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			pchar.quest.treasure_portal.win_condition.l1 = "locator";
			pchar.quest.treasure_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.treasure_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.treasure_portal.win_condition.l1.locator = "teleport6";
			pchar.quest.treasure_portal.win_condition = "treasure_portal";
			DialogExit();
		break;

		case "Uicilopochtli_F_0":
			dialog.text = "Приветствую тебя, смертн" + GetSexPhrase("ый.","ая.");
			link.l1 = "Кхм... здравствуй, Миктлан... Миктлан...";
			link.l1.go = "Uicilopochtli_F_1";
		break;

		case "Uicilopochtli_F_1":
			dialog.text = "Что?! Да как ты смеешь! Я - Уицилопочтли, бог войны, самый могущественный воин среди людей и богов, и Миктлантекутли не сравниться со мной в силе и выносливости. Ты оскорбил" + GetSexPhrase("","a") + " меня, и за это тебя ждет мучительная смерть. Готовься узреть каков Уицилопочтли в бою!";
			link.l1 = "А, черт...";
			link.l1.go = "Uicilopochtli_F_2";
		break;

		case "Uicilopochtli_F_2":
			dialog.text = "Ха-ха, да что ты задрожал" + GetSexPhrase("","a") + "-то так, пошутить нельзя что-ли? Ха-ха-ха! Успокойся, я не стану на тебя бросаться за то что ты черопочек потрогал" + GetSexPhrase("","a") + ", ха-ха-ха!";
			link.l1 = "Фу-ух, спасибо. Поединка с Миктлантекутли мне, честно говоря, хватило...";
			link.l1.go = "Uicilopochtli_F_3";
		break;

		case "Uicilopochtli_F_3":
			dialog.text = "Да, Миклуха в своем репертуаре... Он небось наплел тебе про то что череп - это предмет культа, к которому нельзя прикасаться? Ага, а как он интересно ритуалы проводить собрался, если череп не трогать? Чтоб ты знал" + GetSexPhrase("","a") + " - этот персонаж просто хотел тебя в свою коллекцию добавить. Любит он души павших воинов, а тут " + GetSexPhrase("подвернулся такой мастер меча","подвернулась такая мастерица меча") + ", как ты.";
			link.l1 = "Хорошо что мне удалось выбраться из той передряги. Не хотелось бы навсегда стать стражем Теночтитлана.";
			link.l1.go = "Uicilopochtli_F_4";
		break;

		case "Uicilopochtli_F_4":
			dialog.text = "И не говори - ты бы " + GetSexPhrase("помер","померла") + " со скуки, ха-ха! А 'мертвому богу' давно пора было нос утереть - таким уж напыщенным заделался после падения ацтеков... Пока все скучают в лимбе, он себе тут гуляет со своими игрушками и ни разу к нам не заглянул. Даже Миктлансиуатль не навещал, бедняжка совсем без мужского внимания осталась, представляешь? И ведь я ему предлагал: у тебя тут целая армия, говорю, давай между ними бойню устроим, повеселимся, кости разомнем? А он все нет и нет - видите ли, занят он, Теночтитлан охранять нужно. Ну вот и доохранялся, что ты " + GetSexPhrase("пришел да всю его охрану порешил","пришла да всю его охрану порешила") + ", ха-ха!";
			link.l1 = "Вот как... Кстати... не сочтите за дерзость, уважаемый бог, но если все боги кроме Миктлантекутли находятся в лимбе, то как вы здесь оказались?";
			link.l1.go = "Uicilopochtli_F_5";
		break;

		case "Uicilopochtli_F_5":
			dialog.text = "Не сочту, " + GetSexPhrase("дружище","дорогуша") + ". Да, я очень долго прозябал в лимбе и не мог оттуда выбраться. Но потом ты " + GetSexPhrase("устроил", "устроила") + " здесь заварушку с духами ацтекских воинов, а это вернуло из небытия ацтекскую воинскую славу и подкрепило мои силы как бога войны. В какой-то момент я почувствовал что могу переместиться сюда и решил не упускать момент\nТак что ты " + GetSexPhrase("оказал","оказала") + " мне услугу, за которую тебе положена награда. Отныне я разрешаю тебе совершать ритуал поклонения Уицилопочтли!";
			link.l1 = "Гхм, спасибо...";
			link.l1.go = "Uicilopochtli_F_6";
		break;

		case "Uicilopochtli_F_6":
			dialog.text = "Ты не очень-то " + GetSexPhrase("рад","рада") + ", верно? Ничего, сейчас я тебе все объясню. Ритуал поклонения заключается в том, что ты приносишь жертву и просишь даровать тебе силу для будущих сражений. И если сделать все правильно, то ты эту силу получаешь, а именно - твой клинок становится лучше.";
			link.l1 = "Ага, значит ты можешь улучшить мое оружие?";
			link.l1.go = "Uicilopochtli_F_7";
		break;

		case "Uicilopochtli_F_7":
			dialog.text = "Да, могу, если совершишь ритуал. Ты же не думал, что это Миктлантекутли сделал макуауитли такими смертоносными? Но давай я сразу обозначу некоторые ограничения\nПервое - я не буду улучшать оружие сверх его инженерных возможностей. Я мог бы, но тогда оно бы превратилось в магическое оружие богов и... в общем, такой клинок в человеческих руках никогда до добра не доводил. Но я уверен, что ты все равно сможешь почувствовать улучшение\nВторое - за один раз я могу улучшить лишь одну из характеристик - уменьшить вес или увеличить минимальный или максимальный урон. Выбирать характеристику и величину улучшения ты не сможешь - все таки, поклонение богу - это неточная наука. Но ты сможешь провести много ритуалов над одним и тем же клинком, и через некоторое их количество твое оружие улучшится до идеального состояния.";
			link.l1 = "Звучит неплохо. А что на счет жертв? Много пленных понадобится?";
			link.l1.go = "Uicilopochtli_F_8";
		break;

		case "Uicilopochtli_F_8":
			dialog.text = "Нет, не надо мне твоих пленных. Мне эти обычаи никогда не нравились. Вопли, визги - они хороши, если враг издает их в честной битве, а не когда привязан к алтарю. Я долго пытался объяснить ацтекам, что человеческие жертвы - это по части Миктлантекутли, но все без толку - уж очень любили они людей резать\nЖертва для ритуала должна состоять из двух частей. Первая - это оружие поверженных врагов. Для одного ритуала тебе понадобится 10 других клинков того же качества, что и твое оружие. Вторая - это золото, в количестве, эквивалентном десятикратной стоимости клинка. Оно мне и не нужно особо, это просто традиция такая, и без нее никак. Вот в твоем народе есть шаманы? Они небось без золота с тобой и разговаривать не станут, так?";
			link.l1 = "Хе-хе, да, тут не поспоришь.";
			link.l1.go = "Uicilopochtli_F_9";
		break;

		case "Uicilopochtli_F_9":
			dialog.text = "Вот и я пытаюсь не казаться белой вороной... В общем, собираешь это добро, кладешь на алтарь, обращаешься ко мне - и, если все хорошо, я заберу жертву и улучшу экипированный тобой клинок. И не волнуйся, если что-то пойдет не так - например, жертвы на алтаре будет недостаточно или твой клинок уже некуда будет улучшать - я жульничать не буду, скажу все как есть, и все что на алтаре - останется при тебе.";
			link.l1 = "Понятно. А как нужно обращаться?";
			link.l1.go = "Uicilopochtli_F_10";
		break;

		case "Uicilopochtli_F_10":
			dialog.text = "Да просто попроси от чистого сердца, ха-ха! В конце-концов, это взаимовыгодная сделка - ты получаешь оружие получше, а я - поклонение, подпитывающее мои божественные силы. Так что приходи, не стесняйся."
			link.l1 = "Что ж, спасибо за такую возможность, уважаемый бог. Загляну при случае.";
			link.l1.go = "Uicilopochtli_exit";
			LAi_SetStayType(NPChar);
		break;

		case "Uicilopochtli_exit":
			NPChar.dialog.currentnode = "Uicilopochtli_default";
			DialogExit();
		break;

		case "Uicilopochtli_default":
			dialog.text = "Приветствую тебя, смертн" + GetSexPhrase("ый.","ая.");
			link.l1 = "О великий бог войны Уицилопочтли! Преподношу тебе в дар оружие поверженных мною врагов и прошу тебе дать мне силы для будущих сражений!";
			link.l1.go = "Uicilopochtli_improve";

			if (CheckAttribute(pchar,"ScamFanActive") && CheckAttribute(pchar,"KnowScam") && !CheckAttribute(pchar,"ScamDestroyed"))
			{
				link.l2 = "Здравствуй, Уицилопочтли. Извини что побеспокоил" + GetSexPhrase("","а") + ", но у меня тут проблема...";
				link.l2.go = "Uicilopochtli_fan_1";
			}

			link.l3 = "Здравствуй, Уицилопочтли. Я так, просто поздороваться " + GetSexPhrase("зашел...", "зашла...");
			link.l3.go = "Uicilopochtli_exit";
		break;

		case "Uicilopochtli_improve":
			sBlade = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			if (sBlade == "")
			{
				dialog.text = "Я бы не против, но ты ведь клинок не экипировал" + GetSexPhrase(".","а.");
				link.l1 = "Точно! Сейчас разберусь.";
				link.l1.go = "Uicilopochtli_exit";
				break;
			}

			if (BladeIsPerfect(sBlade))
			{
				dialog.text = "За дары спасибо, но дело в том, что твой клинок уже достиг своих пределов совершенства, так что улучшить его еще сильнее я не могу, извини.";
				link.l1 = "Вот как? Ладно.";
				link.l1.go = "Uicilopochtli_exit";
				break;
			}

			makearef(arChestItems, Locations[FindLocation(PChar.location)].box1);
			if (!TryTakeSacrificeForBladeImprovement(arChestItems, sBlade))
			{
				dialog.text = "Твоей жертвы недостаточно. Напоминаю, нужно 10 клинков эквивалентного твоему качества и золото в количестве, эквивалентном десятикратной стоимости твоего клинка.";
				link.l1 = "Хорошо, как скажешь.";
				link.l1.go = "Uicilopochtli_exit";
				break;
			}

			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sBlade);
			sBlade = ImproveGeneratedBlade(sBlade, 0.25);
			GiveItem2Character(PChar, sBlade);
			EquipCharacterByItem(PChar, sBlade);
			Dialog.Text = "Благодарю тебя, смертн" + GetSexPhrase("ый.","ая.");
			link.l1 = "И тебе спасибо, уважаемый бог.";
			link.l1.go = "Uicilopochtli_exit";
		break;

		case "Uicilopochtli_fan_1":
			dialog.text = "Проблема?"
			link.l1 = "Ага. Видишь это чучело, которое за мной бегает? Хочу от него избавиться, да все никак не могу. Уже по-всякому пробовал" + GetSexPhrase("","а") + " - ни рапира, ни чекан, ни мушкет его не берут. И все бы ничего, но он такой доставучий, что я скоро с ума сойду.";
			link.l1.go = "Uicilopochtli_fan_2";
		break;

		case "Uicilopochtli_fan_2":
			dialog.text = "Вот как. Подожди-ка... Так ведь это же тот дурачек, которого Миктлантекутли сделал бессмертным, ха-ха! Не верится что ты до сих пор не утратил" + GetSexPhrase("","а") + " рассудок - этот тип умеет мозги расплавить."
			link.l1 = "Кажется, еще чуть-чуть и мои мозги таки перейдут в жидкое состояние... Ты можешь что-то с ним сделать?";
			link.l1.go = "Uicilopochtli_fan_3";
		break;

		case "Uicilopochtli_fan_3":
			dialog.text = "Да, заберу его в лимб. Камаштли давно не охотился, будет потеха старику... Ну, а тебе полагается награда. Вот, дарю тебе клинок, равный по ценности этому персонажу, ха-ха! Не благодари, ха-ха-ха!"
			link.l1 = "Спасибо тебе, Уицилопочтли! И от психического расстройства спас, и оружие подарил...";
			link.l1.go = "Uicilopochtli_exit";

			ref rChar = CharacterFromID("ScamCharacter");
			rChar.LifeDay = 0;
			ChangeCharacterAddressGroup(rChar, "none", "", "");
			pchar.ScamDestroyed = true;
			Log_info("Самый преданный фанат чемпиона арены Скэм Геймс навсегда отстал от вас.");

			GiveItem2Character(PChar, GenerateBladeByParams("blade28", 1, 1, 25));
		break;
	}
}

bool TryTakeSacrificeForBladeImprovement(aref arChestItems, string sBlade)
{
	int price = GetItemPrice(sBlade) * 10;
	if (sti(arChestItems.money) < price)
	{
		return false;
	}

	object bladesToTake;
	aref arBlades, arItem;
	makearef(arBlades, arChestItems.Items);
	string sCurrBlade, sCurrBladeQuality;
	string sBladeQuality = ItemsFromID(sBlade).quality;
	int bladesCount = 10;
	int i, num;
	for (i = 0; (i < GetAttributesNum(arBlades)) && (bladesCount > 0); i++)
	{
		arItem = GetAttributeN(arBlades, i);
		sCurrBlade = GetAttributeName(arItem);
		num = sti(GetAttributeValue(arItem));

		if (!IsBlade(sCurrBlade))
		{
			continue;
		}

		sCurrBladeQuality = ItemsFromID(sCurrBlade).quality;
		if (sCurrBladeQuality == sBladeQuality)
		{
			num = func_min(num, bladesCount);
			bladesToTake.(sCurrBlade) = num;
			bladesCount = bladesCount - num;
		}
	}

	if (bladesCount > 0)
	{
		return false;
	}

	arChestItems.money = sti(arChestItems.money) - price;
	makearef(arBlades, bladesToTake);
	for (i = 0; i < GetAttributesNum(arBlades); i++)
	{
		arItem = GetAttributeN(arBlades, i);
		sCurrBlade = GetAttributeName(arItem);
		num = sti(GetAttributeValue(arItem));
		TakeNItems(arChestItems, sCurrBlade, -num);
	}
	return true;
}
