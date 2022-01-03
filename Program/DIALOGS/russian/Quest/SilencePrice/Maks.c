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
        dialog.text = "Ты кто так" + GetSexPhrase("ой", "ая") + "? Иди отсюда, пока цел" + GetSexPhrase("", "а") + ", я не в настроении разговаривать.";
        link.l1 = "Тише, тише, приятель, я принёс" + GetSexPhrase("", "ла") + " тебе письмо от Люка Актера.";
        link.l1.go = "GiveLetter1";
		Map_CreateFastWarriorTreasure();
		DeleteAttribute(Pchar,"Luke.SpawnMaks");
    break;
    case "GiveLetter1":
        dialog.text = "Да? И где же оно?";
        link.l1 = "На, посмотри.";
        NextDiag.CurrentNode = "Plata";
        AddDialogExitQuest("GiveLetter");
    break;
    case "Plata":
        dialog.text = "Что же, все верно. Да, чуть не забыл, вот твои деньги. И всё равно, держись от меня подальше.";
        link.l1 = "Спасибо. С радостью покину твоё общество.";
        AddQuestRecord("Silence_Price", "2");
        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
        PlaySound("Interface\notebook_01");
        link.l1.go = "exit";
        AddDialogExitQuest("Plata1");
		NextDiag.TempNode="Bye";
        Characters[GetCharacterIndex("Old Friend")].Dialog.CurrentNode = "SecondQuest_1";
		ChangeCharacterAddressGroup(CharacterFromID("Old Friend"),"none","none","none");
		Pchar.Quest.Luke = "1";

    break;
	case "Bye":
		dialog.text="Проваливай, я не в настроении разговаривать.";
		link.l1="Не очень-то и хотелось.";
		link.l1.go="exit";
	break;
	case "Guardians":
		dialog.text = "Что здесь происходит?! Вражеский шпион?! Взять его!";
		link.l1 = "Ну попробуйте...";
		link.l1.go = "exit";
		AddDialogExitQuest("FightGuardians");
		LAi_group_MoveCharacter(NPChar, "Maks1");
	break;
    }
}
