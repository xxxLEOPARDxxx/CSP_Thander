
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arAll;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Kamikazi":
			dialog.text = "...";
			link.l1 = "Какого...";
			link.l1.go = "Kamikazi_2";
		break;

		case "Kamikazi_2":
			StopSound(0,0);
			chrDisableReloadToLocation = false;
			LAi_Explosion(NPChar,20);
			LaunchBlood(NPChar,1.0,true);
			LaunchBlast(NPChar);
			LaunchBlastGrenade(NPChar);
			ChangeCharacterAddress(npchar, "none", "");

			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //флаг выполнил успешно
			pchar.Kamikazi = "Meet";
			string sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "22");
			// слухи
			AddSimpleRumour(LinkRandPhrase("Вы знаете, губернатор " + sTemp + " поручил неко"+ GetSexPhrase("ему капитану","й морячке") +" " + GetMainCharacterNameDat() + " уничтожить известного бандита по имени " + GetFullName(arAll) + ". И, кажется, что "+ GetSexPhrase("капитан выполнил","она выполнила") +" задание губернатора...",
				""+ GetSexPhrase("Какой-то смелый капитан вызвался","Какая-то смелая девушка вызвалась") +" найти и уничтожить местного бандита по имени " + GetFullName(arAll) + ". И, похоже, он"+ GetSexPhrase("","а") +" сделал"+ GetSexPhrase("","а") +" это!",
				"Ха, наконец-то наш губернатор взялся за наведение порядка в джунглях - он поручил капитану " + GetMainCharacterNameDat() + " разыскать в джунглях и убить наиболее известного бандита. И вы знате, этот бандит, " + GetFullName(arAll) + " - мертв!"), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
			DialogExit();
		break;
	}
}
