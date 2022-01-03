// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			if (CheckAttribute(pchar, "questTemp.PDM_PI_Rostov"))	//Квест "Аптекарь"
			{
    			link.l1 = "Я хочу преподнести вам дар. Я слышал"+ GetSexPhrase("","а") +", что вы интересуетесь драгоценными камнями... Что вы скажете по поводу этого идола?";
				link.l1.go = "PDM_PI_Rostov_2";
			}
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l2 = "Послушай, "+ GetSexPhrase("хотел","хотела") +" бы предложить тебе одну финансовую операцию...";
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;

		case "PDM_PI_Rostov_2":
			dialog.text = "О-о-о-о! О, Бог мой! "+ GetSexPhrase("месье","мадемуазель") +" "+pchar.name+"! Как прекрасно! Великолепно! Да этот идол может искупить все десять смертных грехов!";
			link.l1 = "Похоже, он вам нравится. Он ваш.";
			link.l1.go = "PDM_PI_Rostov_3";
        break;

		case "PDM_PI_Rostov_3":
			dialog.text = "Вы преподнесли мне бесценный подарок, "+ GetSexPhrase("месье","мадемуазель") +" "+pchar.name+". Я вам чрезвычайно благодарен. Я вознаграждаю вас 45000 золотых - никто не скажет, что я - скряга! Если вы хотите знать, "+ GetSexPhrase("месье","мадемуазель") +" "+pchar.name+", я, пожалуй, пошлю этого идола Его Величеству! Я слыхал, что он как раз увлекается такими интересными вещами.";
			link.l1 = "Я очень рад"+ GetSexPhrase("","а") +", что мой подарок оказался так кстати.";
			link.l1.go = "PDM_PI_Rostov_4";
			AddMoneyToCharacter(pchar, 45000);
			Log_info("Вы подарили идола ростовщику");
			TakeItemFromCharacter(pchar, "Cursed_idol");
        break;

		case "PDM_PI_Rostov_4":
			dialog.text = "Да-да, ваш подарок пришёлся очень ко времени. Но я должен попросить вас уйти. Я хочу полюбоваться... э-э, я хотел сказать, я хочу подумать, как отослать этого идола Его Величеству.";
            link.l1 = "(сзади открывается дверь)";
			link.l1.go = "Rostovshik_5";
			bDisableFastReload = true;
			DeleteAttribute(pchar, "questTemp.PDM_PI_Rostov");
			DeleteAttribute(pchar, "questTemp.PDM_PI_Skelety_v_more");
        break;

		case "Rostovshik_5":
			DialogExit();
			int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
			if (Rank < 1) Rank = 1;
			int Phrase;
			Phrase = rand(2);
            if (Phrase == 0)
            {
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "pirate_22", "man", "man", Rank, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 4, 15 + MOD_SKILL_ENEMY_RATE * 4, "blade19", "", 20 + MOD_SKILL_ENEMY_RATE * 4);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;
			}
            if (Phrase == 1)
            {
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "off_fra_1", "man", "man", Rank, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 4, 15 + MOD_SKILL_ENEMY_RATE * 4, "blade19", "", 20 + MOD_SKILL_ENEMY_RATE * 4);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_2";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;
			}
			if (Phrase == 2)
            {
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "skel1", "skeleton", "skeleton", Rank, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 20 + MOD_SKILL_ENEMY_RATE * 5, 20 + MOD_SKILL_ENEMY_RATE * 5, "blade19", "", 30 + MOD_SKILL_ENEMY_RATE * 4);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_3";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;
			}
		break;

 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("Сразу хочу сказать, что деньги в рост не беру. Занять - это пожалуйста.", "Опять та же финансовая операция?...", "Снова деньги будем предлагать?", "Давайте делом займемся, а не о делах разговоры вести.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Это почему?", "Да, опять та же...", "Опять...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "Пьер Пикардиец обеспечил меня солидной суммой, мне бы эти деньги освоить. Ну так что, берёшь?";
			link.l1 = "Нет, я как раз "+ GetSexPhrase("хотел","хотела") +" дать тебе деньги.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Usurer = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "10");
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

