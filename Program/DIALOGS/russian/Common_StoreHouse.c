
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
			NextDiag.TempNode = "First time";
			dialog.text = LinkRandPhrase("Приветсвую вас! Быть кладовщиком непросто...", "Эх, тоска тут смертная!", "Эх, черт возьми, чем бы заняться?..");
			link.l1 = LinkRandPhrase("Конечно!", "Понимаю...", "Да, проблемы у тебя серьезные...");
			link.l1.go = "exit";
			link.l2 = "Здравствуй, " + NPChar.name + ". Я приш"+GetSexPhrase("ёл","ла")+" поинтересоваться делами склада, а возможно и кое-что оставить на хранение.";
			link.l2.go = "StoreHouse_Details";
			link.l3 = "А отсюда точно ничего не пропадёт, вздумай я оставить что личное?";
			link.l3.go = "StoreHouse_Details2";

		break;

		case "StoreHouse_Details":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(STORE_HOUSE);
		break;

		case "StoreHouse_Details2":
			dialog.text = "Я головой ручаюсь, что ничего вашего отсюда не пропадёт. Можете оставлять здесь всё что пожелаете, "+GetSexPhrase("сэр!","мэм!");
			link.l1 = "Просто отлично! Тогда, до встречи.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
