// Ришард Шамбон - контрабандист
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "(Перед вами детеныш чудовищ-переростков, истреблением которых вы занимались последние несколько часов. Быть может, вам это только кажется, но глядя на краба вы чувствуете его скорбь.)";
				npchar.quest.meeting = "1";
				link.l1 = "Прости приятель, но у меня не было другого выхода. На кону стояла либо моя жизнь, либо их.";
				link.l1.go = "crab_meat";

				link.l2 = "Надо же, пропустил" + GetSexPhrase("","а") + " одного. Сдохни, тварь!";
				link.l2.go = "crab_fight";
				//link.l3 = "Нire";
				//link.l3.go = "crab_hire";


				NextDiag.TempNode = "First time";
				break;
			}
			else
			{
				if (!CheckAttribute(npchar, "quest.answer_1"))
				{
					dialog.text = "(Краб смотрит на вас, словно ждет чего-то.)";
					link.l1 = "Проголодался?";
					link.l1.go = "crab_meat_1";
					link.l2 = "Прости, но у меня сейчас есть дела поважнее.";
					link.l2.go = "exit";


				}
				else
				{
					dialog.text = "(Краб щелкает клешней в знак приветствия.)";
					link.l1 = "И тебе привет, дружище.";
					link.l1.go = "exit";

				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "crab_fight": // первая встреча
            DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld.SaveItemsForDead = true;
		break;

		case "crab_meat":
			dialog.text = "(Краб с грустным пониманием царапает лапами по палубе корабля.)";
			link.l1 = "Даже не знаю, смогу ли я как-то тебя утешить... Вот черт, теперь же совсем некому о тебе заботиться. Может быть ты голоден?";
			link.l1.go = "crab_meat_1";

		break;

		case "crab_meat_1":
			dialog.text = "(Краб одобрительно щелкает клешней, предвкушая свое угощение.)";

			if (CheckCharacterItem(pchar, "food1") || CheckCharacterItem(pchar, "food2") || CheckCharacterItem(pchar, "food3") || CheckCharacterItem(pchar, "food4") || CheckCharacterItem(pchar, "food5"))
			{
				link.l1 = "Вот, держи!";
				link.l1.go = "crab_meat_2";
			}
			link.l2 = "Жди здесь, сейчас что-нибудь принесу.";
			link.l2.go = "exit";
		break;

		case "crab_meat_2":
			dialog.text = "(Краб жадно поглощает еду из протянутой руки, а затем бесцеремонно лезет в вашу сумку и съедает все остальные припасы.)";
			RemoveItems(PChar, "food1", 100);
			RemoveItems(PChar, "food2", 100);
			RemoveItems(PChar, "food3", 100);
			RemoveItems(PChar, "food4", 100);
			RemoveItems(PChar, "food5", 100);
			npchar.quest.answer_1 = "true";
			link.l1 = "Полегче, дружище! Не все сразу! Ладно, мне пора. Может еще к тебе как-нибудь загляну.";
			link.l1.go = "exit";
		break;

		case "crab_hire":
			dialog.text = "(К вам приближается огромных размеров краб. Инстинктивно ваша рука тянется к оружию, однако вы оставливаете себя. Почему-то вам кажется, что у этого существа дружелюбные намерения.)";
			link.l1 = "Крабик, ты что ли? Ну и вымахал! На моей еде такую массу набрал? Или ты кого-то... Пожалуй, мне лучше не знать. Что ты здесь делаешь?";
			link.l1.go = "crab_hire_1";
		break;
		case "crab_hire_1":
			dialog.text = "(Краб издает серию щелкающих звуков)";
			link.l1 = "Вот черт. Я тебя не понимаю, но надеюсь что ты меня сможешь. Ты вроде смышленый и не такой злой, как твои сородичи. Не хочешь сбежать отсюда вместе со мной?";
			link.l1.go = "crab_hire_2";
		break;
		case "crab_hire_2":
			dialog.text = "(Существо издает звук, который вы воспринимаете как согласие)";
			link.l1 = "У меня есть одно срочное дело, а ты пока доберись вон до того корабля, скоро тебя встречу.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
		/*
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");

			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.dialog.CurrentNode = "First time";
			NPChar.quest.meeting = true;
			*/



			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.loyality = MAX_LOYALITY;

			npchar.Dialog.Filename = "Enc_OfficerCrab.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Npchar.cirassId = Items_FindItemIdx("cirass5");  // предмета нет, но влияение есть
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.OfficerWantToGo.DontGo = true;

			DialogExit();
		break;


// <-- специальные реакции

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(npchar);
			DialogExit();
		break;
	}
}
