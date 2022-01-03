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
		case "first time":
			dialog.text = "Слушаю тебя.";
			link.l1 = "Мне не удалось сделать, как ты просил.";
			link.l1.go = "1";
		break;

		case "1":
			dialog.text = "Зря я с тобой связался. Ты не годишься даже для самых простых дел. А теперь убирайся! Ты меня больше не увидишь.";
			link.l1 = "Хех, жизнь покажет! А теперь, прощай. Надеюсь, что жизнь и тебя, приятель, тоже кое-чему научила!";
			link.l1.go = "exit";

			NextDiag.TempNode = "second time";
			AddDialogExitQuestFunction("LooserGenerator_TimeFailed");
		break;

		case "second time":
			dialog.text = LinkRandPhrase("Я не понятно выразился? Проваливай!","Я не хочу с тобой разговаривать.","Уйди, чтобы я тебя не видел.");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "second time";
		break;

		case "quest":
			dialog.text = "Слушаю тебя.";
			link.l1 = "Я всё сделал"+ GetSexPhrase("","а") +", как ты просил, теперь дело за тобой.";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "Я научу тебя нескольким хитростям, "+ GetSexPhrase("приятель","подруга") +", и фортуна будет тебе чаще благоволить. Надеюсь, это тебе всегда пригодится - везение в нашем деле ценится выше золота.";
			link.l1 = "Хех, жизнь покажет! А теперь, прощай. Надеюсь, что жизнь и тебя, приятель, тоже кое-чему научила!";
			link.l1.go = "exit";

			AddDialogExitQuestFunction("LooserGenerator_Complette");
			NextDiag.TempNode = "3";
		break;

		case "3":
			dialog.text = LinkRandPhrase("А, это Вы...","Я скоро ухожу, до встречи.","Может когда-нибудь еще пересечёмся...");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "3";
		break;

		case "Jdet_1":
			dialog.text = "Слушаю тебя.";
			link.l1 = "Я скоро достану твои деньги, не переживай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Jdet_1";
		break;

		case "exit":
			if (CheckAttribute(NextDiag,"TempNode")) NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
