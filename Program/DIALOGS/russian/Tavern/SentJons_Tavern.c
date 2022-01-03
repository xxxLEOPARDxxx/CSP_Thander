// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_Apt_Markus_v_krovi"))	//Квест "Аптекарь"
			{
    			link.l1 = "Расскажи мне о человеке, который лежит на полу у тебя в таверне. На нём живого места на теле не осталось.";
				link.l1.go = "PDM_Apt_Markus_v_krovi_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Apt_Markus_lekarstvo"))	//Квест "Аптекарь"
			{
    			link.l1 = "Ну как он? Живой? Я лекарство нашёл, щас пойду давать нашему больному.";
				link.l1.go = "PDM_Apt_Markus_lekarstvo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Apt_Rasskazat_Tavern"))	//Квест "Аптекарь"
			{
    			link.l1 = "Возьмите этот мешок, мистер "+npchar.name+". В нём вы найдете кое-что, что пригодится Маркусу для того, чтобы поправиться. Насыпьте в воду и давайте ему пить это три раза в день. Он поправится, так сказал доктор.";
				link.l1.go = "PDM_Apt_Rasskazat_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Apt_Vizdorovel"))	//Квест "Аптекарь"
			{
    			link.l1 = "Я по поводу Маркуса. Как его самочувствие?";
				link.l1.go = "PDM_Apt_Vizdorovel_1";
			}
		break;
		//Квест "Аптекарь"
		case "PDM_Apt_Markus_v_krovi_1":
			dialog.text = "Три дня назад дверь таверны открылась, и в неё ввалился человек. Это был Маркус, торговец. Он владел 'Фараоном', самым красивым шлюпом в этих водах. Пират Ропфлейк поймал его на пути в Сент-Джонс, захватил Маркуса, и требовал за него выкуп. Маркус бежал в небольшой лодке, ему пришлось две недели есть чаек и пить дождевую воду. Он смертельно болен. Так и лежит здесь.";
			link.l1 = "Бедный Маркус. Может быть, ты выделишь ему комнату? Я заплачу за неё. 100 монет хватит?";
			link.l1.go = "PDM_Apt_Markus_v_krovi_2";
			link.l2 = "Понятно. Жалко его.";
			link.l2.go = "exit";
		break;

		case "PDM_Apt_Markus_v_krovi_2":
			dialog.text = "Благодарю, "+ GetSexPhrase("сэр","мисс") +", я сейчас же выделю ему комнату на первом этаже. Но боюсь, он всё равно скоро помрёт.";
			link.l1 = "Ну же, "+npchar.name+". Должно же быть какое-то решение.";
			link.l1.go = "PDM_Apt_Markus_v_krovi_3";
			AddMoneyToCharacter(pchar, -100);
			sld = CharacterFromID("PDM_Markus")
			ChangeCharacterAddressGroup(sld,"CommonRoom_MH3","prison","prison1");
		break;

		case "PDM_Apt_Markus_v_krovi_3":
			dialog.text = "Ходят слухи, что на Сан-Мартине дочка губернатора заболела тяжёлым недугом, и никто не мог понять, что с ней. Как вдруг из Европы прибыл доктор Алюмнус, и исцелил неизвестную ранее болезнь. Губернатор был так рад, что позволил доктору Алюмнусу открыть аптеку на Сан-Мартине, и теперь любой нуждающийся может обратиться за помощью. За плату, разумеется.";
			link.l1 = "Это очень интересно! Мне стоит обратиться к Алюмнусу за лекарством. А ты позаботься о Маркусе до моего возвращения.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Markus_v_krovi");

			sld = GetCharacter(NPC_GenerateCharacter("Doktor_Alumnus", "Alumnus", "man", "man", 10, HOLLAND, -1, false));
			sld.name = "Алюмнус";
			sld.lastname = "";
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetBarmanType(sld);
			sld.greeting = "GR_Doctor_Alumnus";
			sld.city = "Marigo";
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_FT";
			ChangeCharacterAddressGroup(sld,"Farmacia","barmen","stay");

			Locations[FindLocation("Marigo_town")].reload.l47.disable = false;

			AddQuestRecord("PDM_Aptekar", "2");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","а"));
		break;

		case "PDM_Apt_Markus_lekarstvo_1":
			dialog.text = "Он еле-еле дышит. Поспешите, он сейчас в комнате, которая на первом этаже.";
			link.l1 = "Точно, я прямо сейчас направляюсь туда.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Markus_lekarstvo");
		break;

		case "PDM_Apt_Rasskazat_Tavern_1":
			dialog.text = "Как мило с вашей стороны, "+pchar.name+". Надеюсь, вы правы, "+ GetSexPhrase("сэр","мисс") +". Я позабочусь о нём, буду давать ваше лекарство, и надеюсь, с божьей помощью, он пойдёт на поправку. Возвращайтесь через неделю, "+pchar.name+", я думаю, он будет в состоянии что-то говорить.";
			link.l1 = "Обязательно проведаю, "+npchar.name+". До свидания.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Rasskazat_Tavern");

			TakeItemFromCharacter(pchar, "PDM_Heal_Poroshok");

			SetTimerCondition("PDM_Apt_Markus_Vizdorovel", 0, 0, 7, false);

			AddQuestRecord("PDM_Aptekar", "4");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","а"));
		break;

		case "PDM_Apt_Vizdorovel_1":
			dialog.text = "О чудо! Капитан, свершилось чудо, он выздоровел! Честно сказать, я не верил в это лекарство, но оно сработало! Не без Божьей помощи конечно, мы все молились за него. И Бог дал ему второй шанс.";
			link.l1 = "Это прекрасная новость, "+npchar.name+"! Пойду, посмотрю на него.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Vizdorovel");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

