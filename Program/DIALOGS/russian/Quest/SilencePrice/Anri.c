void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    int i;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
    break;
    case "First Time":
        dialog.text = "Тише, "+GetSexPhrase("приятель.","подруга.") + " Ты ищешь Люка, так? Можешь не отвечать. Жду сегодня в полночь на пляже мыса Изабелла. Одн" + GetSexPhrase("ого.","у.");
        link.l1 = "Кхм... Хорошо, я приду.";
        link.l1.go = "exit";
		AddDialogExitQuest("PirateGoOut");
		NextDiag.TempNode = "Isabella_1";
    break;
	case "Isabella_1":
		Pchar.quest.PirateComeToIsabellaLoose.over = "yes";
		dialog.text = "А, вот и ты. Ну, выкладывай, зачем тебе Люк?";
		link.l1 = "А кто ты такой, что бы я отвечал" + GetSexPhrase("","а") + " на твои вопросы?";
		link.l1.go = "PrepareFight";
		if (Pchar.Luke.Info == "Peace")
		{
			link.l2 = "Люк мой старый друг. Я выполнял" + GetSexPhrase("","а") + " его просьбу. Когда я вернул" + GetSexPhrase("ся","лась") + " его нигде не было. Меня это встревожило."
			link.l2.go = "PeaceDial";
		}
		DeleteAttribute(pchar,"Luke.Info");
	break;
	case "PrepareFight":
		dialog.text = "Ты вообще, знаешь кто такой Люк? Он агент, и не факт, что у одной нации. Что ты на это скажешь?";
		link.l1 = "Аргкх! Я даже подумать не мог"+GetSexPhrase(".","ла.") + " Какие у тебя с ним дела?!";
		link.l1.go = "PrepareFight_1";
	break;
	case "PrepareFight_1":
		dialog.text = "Тебя это абсолютно никак не касается! Всё, что мне нужно от тебя, это твой корабль.";
		link.l1 = "Я не ослышал" + GetSexPhrase("ся?!","ась?!") + " Ты хочешь мой корабль?! Зачем он тебе?";
		link.l1.go = "PrepareFight_2";
	break;
	case "PrepareFight_2":
		dialog.text = "Знаешь, я хочу поквитаться с Люком, но до " + XI_ConvertString("Colony" + Pchar.Luke.City + "Gen") + " пешком не добраться. Защищайся!";
		link.l1 = "Мерзавец, ну держись!";
		link.l1.go = "exit";
		AddDialogExitQuest("PrepareFightAnri");
	break;
	case "PeaceDial":
		dialog.text = "Хм... Понятно. Значит он и тебя обманул. Что ты собираешься делать?";
		link.l1 = "Для начала неплохо бы его найти, а там я уже разберусь, что делать.";
		link.l1.go = "PeaceDial_1";
	break;
	case "PeaceDial_1":
		dialog.text = "Знаешь, я тебе помогу. Я скажу тебе, где он находится. Самому мне его никак не достать, у меня нет корабля, да и в колонии " + NationNameGenitive(sti(Colonies[FindColony(Pchar.Luke.City)].nation)) + " мне путь заказан.";
		link.l1 = "Хорошо, я соглас" + GetSexPhrase("ен.","на.") + " Говори мне, всё что знаешь.";
		link.l1.go = "PeaceDial_2";
	break;
	case "PeaceDial_2":
		dialog.text = "Сейчас он находится в порту " + XI_ConvertString("Colony" + Pchar.Luke.City + "Gen") + ". Скорее всего он где-то прячется, ищи тщательнее, и будь осторож" + GetSexPhrase("ен","на") + ", он очень хитер.";
		link.l1 = "";
		link.l1.go = "PeaceDial_3";
	break;
	case "PeaceDial_3":
		dialog.text = "Удачи тебе, и возьми эти книги. Они помогут предвосхитить его уловки. Прощай.";
		link.l1 = "Спасибо тебе. Прощай.";
		link.l1.go = "exit";
		AddDialogExitQuest("PirateGoOut1");
	break;
    }
}
