void ProcessDialogEvent()
{
	ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FirstTime":
			dialog.text = "Здравствуйте. Я работаю от имени губернатора и ищу вражеского лазутчика в городе. Кто вы "+GetSexPhrase("такой","такая") + "?";
			link.l1 = "Здравствуйте. Я не живу в этом городе, но я не шпион. Можем пойти к губернатору, он подтвердит.";
			link.l1.go = "TryNotBeCut";
			if (CheckNationLicence(sti(npchar.nation)))
				{
					link.l1 = "У меня имеется " + GetRusNameNationLicence(sti(npchar.nation)) + ", так что, я нахожусь здесь на законных основаниях. Прошу ознакомиться...";
					link.l1.go = "LicenceOk";
				}
		break;
		case "TryNotBeCut":
			if(pchar.SpySeeker == "Enemy" && (10 + rand(50) + rand(50)) > sti(pchar.skill.sneak))
			{
				dialog.text = "Сдаётся мне, что ты меня обманываешь. Но хорошо, давай пройдем к губернатору.";
				link.l1 = "Никуда я с тобой не пойду! Защищайся!";
				link.l1.go = "exit";
				AddDialogExitQuest("SeekerFight");
			}
			else
			{
				dialog.text = "Хорошо, не нужно. Я вам верю. Удачи!";
				link.l1 = "Вот и славно. Удачи!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				AddCharacterExpToSkill(pchar, "Sneak", 100);
				AddDialogExitQuest("SpySeekerGood");
			}
		break;
		case "LicenceOk":
			dialog.text = "Хорошо. Не смею больше вас задерживать."
			link.l1 = "Отлично, прощайте.";
			link.l1.go = "exit";
			AddDialogExitQuest("SpySeekerGood");
		break;
	}
}
