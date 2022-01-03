
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ага, так это ты у нас из последнего пополнения граждан? Ну, что же, добро пожаловать.";
				link.l1 = "Спасибо. Меня зовут " + GetFullName(pchar) + ".";
				link.l1.go = "FT_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Здравствуй. Ты что-то хотел"+ GetSexPhrase("","а") +"?";
				link.l1 = "Мне нужны деньги.";
				link.l1.go = "GiveMoney";
				link.l10 = "Нет, просто так заскочил"+ GetSexPhrase("","а") +" к тебе.";
				link.l10.go = "Exit";
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Слушай, есть серьезный разговор. Я набираю команду.";
					link.l8.go = "SeekCrew";
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FT_1":
			dialog.text = "Очень приятно. А меня Августо Брамс. Будем знакомы.";
			link.l1 = "Хорошо.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Если тебе будут нужны деньги - заходи ко мне, я cмогу выручить.";
			link.l1 = "Отлично, буду знать...";
			link.l1.go = "Exit";
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = "Ты, "+ GetSexPhrase("приятель","подруга") +", не знаешь, с кем связал"+ GetSexPhrase("ся","ась") +"! А теперь тебе конец...";
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумали?! Теперь граждане и милиция порвут тебя, как старую газету!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = "Хм, смешно... Убери оружие.";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Я знаю.",
				"Мы уже говорили об этом.",
				"Это уже обсуждено, второй раз повторяю.",
                "Хватит, утомил...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь? Откуда?",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаешь...",
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Мне многое известно... Ты хотел"+ GetSexPhrase("","а") +" позвать меня с собой?";
			link.l1 = "Да. Ты согласен пойти ко мне в команду?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Нет. Я останусь здесь до последнего момента.";
			link.l1 = "Кстати, он скоро наступит, этот последний момент. На город надвигается буря невиданной силы.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Я знаю, но все равно останусь. Мне ничего не угрожает.";
			link.l1 = "Странный ты... Ну как знаешь.";
			link.l1.go = "exit";
		break;

		//занять бабла
		case "GiveMoney":
			if (CheckAttribute(npchar, "quest.loan"))
			{
				if (sti(npchar.quest.loan.qtyMoney) >= 1000000)
				{
					dialog.text = "Ты полностю исчерпал"+ GetSexPhrase("","а") +" выделенную квоту. Кредитная линия тебе закрыта.";
					link.l1 = "Ясно.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Я готов рассмотреть твою просьбу.";
					link.l1 = "Отлично!";
					link.l1.go = "GiveMoney_1";
				}
			}
			else
			{
				dialog.text = "Хорошо. А ты знаешь условия, на которых я предоставляю займы?";
				link.l1 = "Пока нет. Но, надеюсь, ты мне расскажешь.";
				link.l1.go = "GiveMoneyKn_1";
				npchar.quest.loan = true;
				npchar.quest.loan.qtyMoney = 0; //кол-во взятых денег
			}
		break;

		case "GiveMoneyKn_1":
			dialog.text = "Обязательно. Итак, размер займа ограничивается одним миллионом пиастров. Ты можешь взять у меня любую сумму в этих пределах.";
			link.l1 = "Понятно. А под какой процент годовых?";
			link.l1.go = "GiveMoneyKn_2";
		break;
		case "GiveMoneyKn_2":
			dialog.text = "У меня нет процентовки, завязанной на времени. Ты просто долж"+ GetSexPhrase("ен","на") +" будешь вернуть мне в пять раз большую сумму по первому требованию моего доверенного лица.";
			link.l1 = "Чего?!!!";
			link.l1.go = "GiveMoneyKn_3";
		break;
		case "GiveMoneyKn_3":
			dialog.text = "У тебя проблемы со слухом?";
			link.l1 = "Нет, просто я немного опешил"+ GetSexPhrase("","а") +"...";
			link.l1.go = "GiveMoneyKn_4";
		break;
		case "GiveMoneyKn_4":
			dialog.text = "Других условий у меня нет, как и преференций кому бы то ни было.";
			link.l1 = "Хм, понятно...";
			link.l1.go = "GiveMoney_1";
		break;

		case "GiveMoney_1":
			dialog.text = "Какую сумму ты желаешь занять у меня?";
			Link.l1.edit = 4;
			Link.l1 = "";
			link.l1.go = "GiveMoney_2";
			Link.l2 = "Хм, пожалуй, пока откажусь от займа.";
			link.l2.go = "GiveMoney_disAgree";
		break;
		case "GiveMoney_2":
			iTemp = sti(dialogEditStrings[4]);
			if ((iTemp + sti(npchar.quest.loan.qtyMoney)) > 1000000)
			{
				dialog.text = "Запрашиваемая сумма превышает установленную квоту в миллион. Я могу дать тебе " + FindRussianMoneyString(1000000 - sti(npchar.quest.loan.qtyMoney)) + ", не более.";
				link.l1 = "Понятно...";
				link.l1.go = "exit";
			}
			else
			{
				if (iTemp <= 0)
				{
					dialog.text = "Шутни"+ GetSexPhrase("к","ца") +", да? Не советую дурачиться со мной.";
					link.l1 = "Хм, понял...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Хорошо, с увольствием вручаю тебе требуемую сумму.";
					link.l1 = "Превосходно! Ты здорово меня выручил, дружище.";
					link.l1.go = "GiveMoney_3";
					AddMoneyToCharacter(pchar, iTemp);
					npchar.quest.loan.qtyMoney = sti(npchar.quest.loan.qtyMoney) + iTemp;
				}
			}
		break;
		case "GiveMoney_3":
			dialog.text = "Очень рад. Надеюсь, что ты будешь помнить об условиях рассчета за предоставленный займ. Когда придется время, ты долж"+ GetSexPhrase("ен","на") +" будешь вернуть сумму, в пять раз превышающую размер долга. И на данный момент, это " + FindRussianMoneyString(sti(npchar.quest.loan.qtyMoney) * 5) + ".";
			link.l1 = "Да, я помню. А что будет, если я не смогу их сразу вернуть?";
			link.l1.go = "GiveMoney_4";
		break;
		case "GiveMoney_4":
			dialog.text = "Хм, лучше, если бы они у тебя были"+ GetSexPhrase(", приятель","") +". Альтернатива, мягко говоря, очень страшна. Очень...";
			link.l1 = "Ясно. Ну что же, буду страться.";
			link.l1.go = "exit";
		break;
		case "GiveMoney_disAgree":
			dialog.text = "Ну, как знаешь. Поразмысли как следует, может, и надумаешь еще.";
			link.l1 = "Да, конечно...";
			link.l1.go = "exit";
		break;
	}
}
