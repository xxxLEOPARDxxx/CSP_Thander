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
			link.l1 = "Я забрал"+ GetSexPhrase("","а") +" все кошельки, как ты просил. Так что там с наградой?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "У меня есть для тебя необычная вещица. Благодаря ей, ты сможешь чаще выигрывать в азартных играх.";
			link.l1 = "Хах, как же ты проиграл все деньги, имея при себе такую вещицу?";
			link.l1.go = "2.1";
			
			GiveItem2Character(PChar, "Joker");
			Log_info("Вы получили игральную карту Джокер.");
			PlaySound("Interface\important_item.wav"); 
		break;
		
		case "2.1":
			dialog.text = "Она лишь увеличивает шанс выигрыша, но не гарантирует победу. В любом случае, тебе она принесёт больше пользы чем мне.";
			link.l1 = "Благодарю за такой подарок, а теперь я вынужден"+ GetSexPhrase("","а") +" откланяться, до встречи.";
			link.l1.go = "exit";

			AddDialogExitQuestFunction("LooserGenerator_Complette");
			NextDiag.TempNode = "3";
		break;

		case "3":
			dialog.text = LinkRandPhrase("А, это ты...","Я скоро ухожу, до встречи.","Может когда-нибудь еще пересечёмся...");
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
