// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> квест №5 голл.линейки, забрать три флейта.
            if (pchar.questTemp.State == "ThreeFleutes_toPortMan")
            {
    			link.l1 = "Я к вам по поручению Стэвезанта. Мне необходимо принять командование над тремя флейтами.";
    			link.l1.go = "Step_H5_1";
            }
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "Я бы хотел"+ GetSexPhrase("","а") +" узнать по поводу барка, пропавшего в ночь после восстания рабов.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//ОЗГ, Крыса
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
    			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countV == 0)
    			{
    				link.l1 = "Слышал"+ GetSexPhrase("","а") +", недавно, по выходу из вашего порта, пропало торговое судно. Не можете рассказать об этом поподробнее?";
	    			link.l1.go = "Rat_portmanV";
	    		}
			}
		break;

//************************************* Диалоги по голл.линейке *******************************
		case "Step_H5_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = "Пожалуйста, принимайте. Три флейта поступают в ваше распоряжение.";
    			link.l1 = "Великолепно.";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("HL5_portManGiveFleuts");
            }
            else
            {
                dialog.text = "Да, я в курсе данного вопроса. Однако, чтобы принять командование над флейтами, вам необходимо изабавиться от вашей эскадры. Прошу вас сделать это и затем вновь обратиться ко мне.";
    			link.l1 = "Хорошо, я так и сделаю.";
    			link.l1.go = "exit";
            }
		break;
		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Хм... А с какой стати вдруг это вас заинтересовало?";
				link.l1 = "Я действую по указаниям Питера Стевезанта, генрал-губернатора. Есть основания полагать, что к исчезновению корабля причастны беглые рабы. Поэтому я прошу вас оказать мне все возможное содействие в розысках.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;

		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Понятно. Но, к сожалению, я мало чем могу вам помочь. Барк с именем " + pchar.questTemp.Slavetrader.ShipName + ", пропал ночью, никто ничего не видел и не слышал. Вахтенный исчез бесследно\nРозыск корабля по горячим сдедам ничего не дал, собственно, потому что никаких следов не было. Город был взбудоражен, все ожидали нападения рабов, готовились к обороне...";
				link.l1 = "Да уж, действительно информации немного. Но спасибо и на этом. До свидания.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;

		//ОЗГ, Крыса
		case "Rat_portmanV":
			dialog.text = "Да, пару недель назад, или около того, тяжелый галеон 'Санта Анна' вышел из гавани, и, как говорят, не пришел в указанный пункт. Больше его никто не видел, а почему вам это интересно?";
			link.l1 = "Это, скажем так, частный интерес. Никаких подробностей не припомните?";
			link.l1.go = "Rat_portmanV_1";
		break;

		case "Rat_portmanV_1":
			dialog.text = "Что я могу припомнить, погодите минутку... Да, вот здесь запись – тяжелый галеон 'Санта Анна' отплыл с грузом черного дерева на борту, более шестисот единиц. Так... в порт назначения не явился. Вроде бы и все.";
			link.l1 = "Скажите, а какие корабли вышли из гавани в тот же день, или днем позже этого галеона?";
			link.l1.go = "Rat_portmanV_2";
		break;

		case "Rat_portmanV_2":
			dialog.text = "Давайте посмотрим. В тот день покинули порт корабли: пинас 'Аделаида', галеон 'Медемблинк' и фрегат 'Зултхен'.";
			link.l1 = "Спасибо!";
			link.l1.go = "CheckV";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countV = 1;
		break;

		case "CheckV":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_3");
			}
			DialogExit();
		break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

