void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname;

	int iBricks = sti(PChar.BuildingColony.Blocks);
	int iPlanks = sti(PChar.BuildingColony.Planks);
	int iMahogany = sti(PChar.BuildingColony.Mahogany);
	int iEbony = sti(PChar.BuildingColony.Ebony);
	int iSlaves = sti(PChar.BuildingColony.Slaves);
	int iFood = sti(PChar.BuildingColony.Food);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Чем могу быть полезен, господин капитан " + sName + "?";
			if(PChar.ColonyBuilding.Stage != "2" && PChar.ColonyBuilding.Action != true)
			{
				link.l1 = "Пожалуй, я заинтересован в ваших услугах.";
				link.l1.go = "Building";
			}
			link.l2 = "Просто зашёл вас повидать.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Hi1":
			dialog.text = "Приветствую, капитан! Нуждаетесь в моих услугах?";
			link.l1 = "Здравствуйте. В каких услугах?";
			link.l1.go = "Hi";
			NextDiag.TempNode = "First time";
		break;

		case "Hi":
			dialog.text = "Ах, вы наверное не знаете. Я - известный в этом архипелаге архитектор. Я могу начать строительство колонии на одном из необитаемых островов. За моими плечами очень большой опыт, поверьте.";
			link.l1 = "Вот как? Достаточно интересно.";
			link.l1.go = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
