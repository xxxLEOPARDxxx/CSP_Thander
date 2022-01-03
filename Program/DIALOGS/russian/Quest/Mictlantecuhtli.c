
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
	}
}
