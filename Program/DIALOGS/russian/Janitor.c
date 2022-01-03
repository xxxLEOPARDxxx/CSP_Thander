
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
		case "First":
			dialog.text = RandPhraseSimple("Ходют тут, топчут всякие, а мне убирать потом...","И чего припёр"+GetSexPhrase("ся сюда? Заброшенный храм, в уборке нуждается, а он таскает тут грязь повсюду.","лась сюда? Заброшенный храм, в уборке нуждается, а она таскает тут грязюку."));
			link.l1 = "O__O";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
