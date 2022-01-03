
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
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fightQuest":
			pchar.questTemp.LSC.Armo.checkCasper = npchar.index; //для обработки в АИ
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//первый каспер на разводе Армо
		case "Casper_1":
			dialog.text = "Эй, "+ GetSexPhrase("приятель","подруга") +", ну-ка, вали отсюда! Очисти площадку.";
			link.l1 = "В чем дело?";
			link.l1.go = "Casper_1_1";
			NextDiag.TempNode = "Casper_12";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_1_1":
			dialog.text = "Я тут кое-кого жду, третий лишний будет. Понял"+ GetSexPhrase("","а") +"?";
			link.l1 = "Армо, что ли, ожидаешь? Так я за нее.";
			link.l1.go = "Casper_1_2";
			link.l2 = "А-а, понятно. Ну ладно...";
			link.l2.go = "exit";
		break;
		case "Casper_1_2":
			dialog.text = "Чего?!";
			link.l1 = "Так и не понял? Ну ладно, сейчас поймешь...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_12":
			dialog.text = "Слушай, я, кажется, ясно выразился. Убирайся отсюда, "+ GetSexPhrase("приятель","подруга") +"...";
			link.l1 = "А ты не Армо ждешь, дружище? Так ее не будет, я за нее.";
			link.l1.go = "Casper_12_1";
			link.l2 = "Ладно, ладно...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_13";
		break;
		case "Casper_12_1":
			dialog.text = "Чего?!";
			link.l1 = "Так и не понял? Ну ладно, сейчас поймешь...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_13":
			dialog.text = "Ну все, ты меня достал"+ GetSexPhrase("","а") +". По-хорошему не получается...";
			link.l1 = "Ну да, я настойчив"+ GetSexPhrase("","а") +"!";
			link.l1.go = "fightQuest";
		break;
		//второй каспер на разводе Армо
		case "Casper_3":
			dialog.text = ""+ GetSexPhrase("Дружище","Дорогуша") +", ты бы ш"+ GetSexPhrase("ел","ла") +" отсюда...";
			link.l1 = "А что такое?";
			link.l1.go = "Casper_3_1";
			NextDiag.TempNode = "Casper_32";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_3_1":
			dialog.text = "Ну, понимаешь, у меня тут свидание. Так что твое присутствие здесь нежелательно, мягко говоря.";
			link.l1 = "Не Армо, случайно, ждешь?";
			link.l1.go = "Casper_3_2";
			link.l2 = "Хорошо, дружище.";
			link.l2.go = "exit";
		break;
		case "Casper_3_2":
			dialog.text = "А откуда ты знаешь?";
			link.l1 = "Армо не будет, я вместо нее.";
			link.l1.go = "fightQuest";
		break;

		case "Casper_32":
			dialog.text = ""+ GetSexPhrase("Дружище","Дорогуша") +", я прошу тебя, не нарывайся грубость.";
			link.l1 = "Грубость? Хе-хе, ладно, хватит. Армо не придет, я за нее.";
			link.l1.go = "Casper_32_1";
			link.l2 = "Хорошо.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_33";
		break;
		case "Casper_32_1":
			dialog.text = "Как понять?";
			link.l1 = "Как хочешь, так и понимай...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_33":
			dialog.text = "Я тебя предупреждал, "+ GetSexPhrase("приятель","девчонка") +". Теперь пеняй на себя!";
			link.l1 = "На кого пенять? Подожди, я не расслышал"+ GetSexPhrase("","а") +"...";
			link.l1.go = "fightQuest";
		break;
		//третий каспер на разводе Армо
		case "Casper_5":
			dialog.text = "Эй, а ну вали отсюда, пока цел"+ GetSexPhrase("","а") +"!";
			link.l1 = "Хм, это почему?";
			link.l1.go = "Casper_5_1";
			NextDiag.TempNode = "Casper_52";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_5_1":
			dialog.text = "Потому что я здесь стою! У меня тут свидание. Понял"+ GetSexPhrase("?","а? И не с тобой.") +"";
			link.l1 = "Свидание с Армо? Ну, это зря...";
			link.l1.go = "Casper_5_2";
			link.l2 = "Понял"+ GetSexPhrase("","а") +"...";
			link.l2.go = "exit";
		break;
		case "Casper_5_2":
			dialog.text = "Да, с Армо.";
			link.l1 = "Армо не будет, у тебя свидание со мной.";
			link.l1.go = "fightQuest";
		break;

		case "Casper_52":
			dialog.text = "Слушай, я тебе уже говорил, чтобы ты валил"+ GetSexPhrase("","а") +" отсюда!";
			link.l1 = "Если ты Армо ожидаешь, то ее не будет. Видишь ли, у тебя свидание со мной.";
			link.l1.go = "Casper_52_1";
			link.l2 = "Да-да, уже ухожу...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_53";
		break;
		case "Casper_52_1":
			dialog.text = "Чего?!";
			link.l1 = "Того, идиот!..";
			link.l1.go = "fightQuest";
		break;

		case "Casper_53":
			dialog.text = "Ну все, хватит с меня уговоров...";
			link.l1 = "Да, думаю, хватит.";
			link.l1.go = "fightQuest";
		break;
		//ГГ застукали за первым
		case "FackYou":
			dialog.text = "Не зря я подозревал нехорошие вещи. Слишком много пропало наших...";
			link.l1 = ""+ GetSexPhrase("Ой... А ты это о чем?","Какого черта... Ты это о чем?") +"";
			link.l1.go = "FackYou_1";
		break;
		case "FackYou_1":
			dialog.text = "Об этой сучке Армо. Ну и о тебе, конечно, "+ GetSexPhrase("приятель","подруга") +". Что же ты творишь, "+ GetSexPhrase("скотина","мерзавка") +"?";
			link.l1 = ""+ GetSexPhrase("Даже и не знаю, как сказать... Ну-у, в общем, режу 'касперов' по одному.","Выследил, гад... Да вот, режу вас, подонков, поодиночке.") +"";
			link.l1.go = "FackYou_2";
		break;
		case "FackYou_2":
			dialog.text = "Понятно... Ну что же, не зря я пустил кровь Армо.";
			link.l1 = "Что?!";
			link.l1.go = "FackYou_3";
		break;
		case "FackYou_3":
			dialog.text = "Да-да, "+ GetSexPhrase("приятель","подруга") +". Армо я отправил вслед за ее шефом, Хиллом Брюннером. И это справедливо - им так было хорошо вдвоем...";
			link.l1 = ""+ GetSexPhrase("Ты за это заплатишь!","Ах ты... Ну все, тебе конец, сволочь.") +"";
			link.l1.go = "FackYou_4";
		break;
		case "FackYou_4":
			dialog.text = "Что, думаешь, я совсем глупый? Еще вчера мне все стало ясно, хотя это были только подозрения. И сейчас я не один.";
			link.l1 = ""+ GetSexPhrase("Это тебе не поможет...","Это тебе не поможет! Сдохни, ублюдок!!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_3CarperAttackArmo");
		break;

	}
}
