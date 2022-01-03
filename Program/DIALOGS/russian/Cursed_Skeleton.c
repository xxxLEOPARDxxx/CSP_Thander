// Генерируемый скелет-босс из пещеры
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	ref cursedLocLoad = &locations[reload_location_index];
	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	//ref itm;
	int skullgen = drand(2)+1;
	string cursed_artifact = "sculMa"+sti(skullgen); // Квестовый предмет

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				scareOfficers(50);
				dialog.text = "Как ты смеешь нарушать покой в моей гробнице, смертн"+ GetSexPhrase("ый","ая")+"? Да еще и роешься в моих вещах! Стоит преподать тебе урок.";
				npchar.quest.meeting = "1";
				link.l1 = "Вот черт, я думал" +GetSexPhrase("","а")+" что здесь никто не живет. Прошу прощения, я сейчас же уйду.";
				link.l1.go = "meeting_1";
				//Если мы пришли по церковному квесту
				if(CheckAttribute(cursedLocLoad, "DestroyGhost"))
				{
					link.l1 = "Я при" + GetSexPhrase("шел","шла") + " избавить это место от скверны! Изыди, нечистый! Именем господа, я заклинаю...";
					link.l1.go = "meeting_2";
					break;
				}
				link.l3 = "Умри, отродье!";
				link.l3.go = "skel_fight";
				NextDiag.TempNode = "First time";
				break;
			}
			else if (npchar.quest.meeting == "2")
			{
				dialog.text = "Я давал тебе шанс сохранить свою жалкую жизнь, но ты им не воспользовал"+GetSexPhrase("ся","ась")+". ";
				DeleteAttribute(pchar, "cursed.waitingSkull");
				LAi_SetPlayerType(PChar);



				link.l1 = "Дьявол, как ты здесь оказался? Постой, я еще смогу найти  твой череп!";
				link.l1.go = "end_quest_battle";
				link.l2 = "Якорь мне в..!";
				link.l2.go = "skel_fight";
				if(CheckCharacterItem(pchar, pchar.questTemp.Cursed.Item) && CheckAttribute(pchar,"cursed.Skullbought"))
				{
					dialog.text = "Я знаю, что череп у тебя. Давай его сюда.";
					link.l1 = "Забирай и оставь меня в покое наконец!";
					link.l1.go = "end_quest";
					link.l2 = "Еще чего. Теперь череп мой. Спасибо за наводку, без тебя я бы его не наш"+GetSexPhrase("ел","ла")+".";
					link.l2.go = "end_quest_battle";
				}

			}
			else
			{
				dialog.text = "Есть вопросы?";
				npchar.quest.meeting = "1";

				link.l1 = "Когда я верну тебе череп, что собираешься делать? Расторгнешь контракт и примешь смерть?";
				link.l1.go = "question";
				link.l2 = "Я решил" + GetSexPhrase("","а") + " отправить тебя на покой другим, более эффективным способом!";
				link.l2.go = "skel_fight";
				link.l3 = "Нет.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = "Я давно думал об этом. С черепом я смогу вернуть себе прошлую жизнь, свое тело. Может быть даже раздобуду корабль и верну свою дурную славу. Нет, умирать я не точно собираюсь.";
			link.l1 = "Ладно, пойду искать.";
			link.l1.go = "question";
			link.l2 = "Даже если эта жизнь будет достигаться ценой тысяч смертей других? Ну уж нет, я обязан" + GetSexPhrase("","а") + " тебя остановить!";
			link.l2.go = "skel_fight";
		break;
		case "end_quest_battle":
			dialog.text = "Слишком поздно, я подыщу себе более сговорчивого искателя.";
			link.l1 = "Каррамба!";
			link.l1.go = "skel_fight";
			if(CheckCharacterItem(pchar, pchar.questTemp.Cursed.Item) && CheckAttribute(pchar,"cursed.Skullbought"))
				{
					dialog.text = "Зря ты это затеял" + GetSexPhrase("","а") + ", еще никому не удалось одолеть меня в такой форме.";
					link.l1 = "Я стану перв" + GetSexPhrase("ым","ой") + "!";
					link.l1.go = "skel_fight";
				}

		break;

		case "end_quest":
			dialog.text = "Благодарю. Как я и обещал, ты свобод" + GetSexPhrase("ен","на") + ". В награду за старания я даже подарю тебе одну книженцию. За долгие годы что я просидел в пещере, заняться было особо нечем, так что я не раз ее перечитывал. Должен признаться, весьма занятное чтиво. Я умудрялся при каждом прочтении находить для себя что-то новое.";
			TakeItemFromCharacter(pchar, pchar.questTemp.Cursed.Item);
			string book = PickAbook();
			GiveItem2Character(pchar, book);
			LAi_SetImmortal(npchar, true);
			link.l1 = "Ух ты, спасибо!";
			CloseQuestHeader("CursedSkeleton");
			link.l1.go = "Exit_1";
		break;

		case "skel_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			npchar.SaveItemsForDead = true;
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			SetSkeletonsToLocation(cursedLocLoad);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			npchar.quest.meeting = "0";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DeleteAttribute(pchar, "cursed.Skullbought");
			CloseQuestHeader("CursedSkeleton");
            DialogExit();
		break;

		case "meeting_1":
			dialog.text = "Ну уж нет, так просто тебе не выкрутиться. Мне нужна помощь в одном деле. Справишься - я сохраню тебе жизнь и свободу. А что будет в случае провала или отказа тебе лучше не знать.";
			link.l1 = "И то же за помощь тебе нужна?";
			link.l1.go = "meeting_3";

			link.l2 = "Да лучше я тебя просто зарублю!";
			link.l2.go = "skel_fight";
		break;

		case "meeting_2":
			dialog.text = "У тебя нет шансов в бою со мной. И твои заклинания здесь не помогут, а Господь - не услышит.";
			npchar.quest.answer_1 = "true";
			TakeNItems(NPCHAR, "Chest_ammo", 2 + sti(pchar.rank)*0.1);
			TakeNItems(NPCHAR, "Chest_quest", 1 );
			link.l1 = "Это мы еще посмотрим! Прошу тебя, Господи, направь мою руку, чтобы я смог"+GetSexPhrase("","ла")+" поразить этого нечистого во славу твою!";
			link.l1.go = "skel_fight";
		break;

		case "meeting_3":
			dialog.text = "Видишь ли, я не всегда был таким. В прошлой жизни у меня был собственный корабль, прямо как у тебя. Скажу больше - я был корсаром, имя которого внушало ужас во всех колониях. Однако, прошло уже слишком много времени чтобы это кто-то помнил.";
			link.l2 = "...";
			link.l2.go = "meeting_5";
			link.l1 = "Ближе к сути.";
			link.l1.go = "meeting_4";
		break;
		case "meeting_4":
			dialog.text = "Не перебивай меня, смертн"+ GetSexPhrase("ый","ая")+", иначе твоя жизнь закончится здесь и сейчас!";
			link.l1 = "Прошу прощения, продолжай.";
			link.l1.go = "meeting_5";

			link.l2 = "Мне это все уже надоело. Сейчас я избавлю тебя от страданий!";
			link.l2.go = "skel_fight";
		break;
		case "meeting_5":
			dialog.text = "При жизни я был удачлив и собрал много ценной добычи. А когда решил отойти от дел, я собирался  зарыть часть своей добычи в сундуке, что рядом с тобой. Сейчас там ничего, конечно же, нет, ведь меня подло убили прямо здесь, так и не дав возможности завершить начатое.";
			link.l1 = "И кто же это сделал?";
			link.l1.go = "meeting_6";

			link.l2 = "Это все очень интересно, но мне пора на корабль, а тебе - на тот свет!";
			link.l2.go = "skel_fight";
		break;
		case "meeting_6":
			dialog.text = "Мой собственный старпом! Я считал его своим лучшим другом, даже выдал свою дочь замуж за его сына, а он меня предал, еще и команду подговорил. Все из-за этого проклятого черепа, будь он не ладен.";
			link.l1 = "Что за череп?";
			link.l1.go = "meeting_7";
		break;
		case "meeting_7":
			SelectCursedRendom();
			pchar.questTemp.Cursed.Item = cursed_artifact;
			dialog.text = "Угораздило меня по пьяни пойти на сделку с каким-то типом с кошачьими глазами. Слишком поздно до меня дошло, что это был демон. Он дал мне "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +" и сказал, что пока я буду носить этот предмет при себе, удача меня не покинет. Но всему есть цена. Чтобы эффект продолжался, необходимо регулярно отправлять души других людей на тот свет, иначе место удачи займет проклятие, в результате которого я и оказался в таком положении.";
			link.l1.go = "meeting_7_1";
		break;
		case "meeting_7_1":
			dialog.text = "Для того, чтобы аннулировать контракт с демоном, череп нужно было зарыть подальше от живых людей. Это я и собирался тут сделать. Видать я слишком долго не убивал и поздно спохватился, так что не заметил как положительный эффект черепа сменился на отрицательный и обратил против меня лучшего друга. Что самое ужасное, с этим проклятием нельзя ни жить полноценной жизнью, ни умереть.";
			link.l1 = "Как я понимаю, ты хочешь найти этот "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +"?";
			link.l1.go = "meeting_8";
		break;
		case "meeting_8":
			dialog.text = "Да. И  даже знаю где он может быть. При жизни мы с командой сбывали награбленное одному купцу из "+ XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId + "Gen") +". Наверняка мой старпом не догадывался об истинной ценности этого предмета и продал его вместе с остальными моими вещами. Отправляйся туда немедленно, я больше не в силах ждать.";
			link.l1 = "Ладно.";
			link.l1.go = "meeting_9";
		break;
		case "meeting_9":
			dialog.text = "Я даю тебе ровно месяц на розыски черепа. Если ты не справишься то очень пожалеешь. И не думай, что как только отсюда выйдешь ты от меня избавишься, я привязал свою душу к твоей, так что без проблем найду тебя даже на краю света.";

			ReOpenQuestHeader("CursedSkeleton");
			AddQuestRecord("CursedSkeleton", "1");
			AddQuestUserData("CursedSkeleton", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CursedSkeleton", "sSex1", GetSexPhrase("ся","ась"));
			AddQuestUserData("CursedSkeleton", "scityName", XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId));
			npchar.lifeday = 0;
			link.l1 = "Да хорош пугать меня. Так и быть, помогу тебе. Беру курс на "+ XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId + "Acc") +".";
			pchar.cursed.waitingSkull = true;
			link.l1.go = "exit";
		break;


// <-- специальные реакции

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "Exit_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterAddress(npchar, "none", "");
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "cursed.Skullbought");
			chrDisableReloadToLocation = false;
			DialogExit();
		break;
	}
}

void SelectCursedRendom()
{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[drand(howStore-1)];
		pchar.questTemp.Cursed.TownId = colonies[nation].id;
		pchar.questTemp.Cursed.TraderId = colonies[nation].id + "_trader";

}

string PickAbook()
{
	int quality = 1;
	if (pchar.rank <= 10) quality = 1;
	if (pchar.rank >= 10) quality = 2;
	if (pchar.rank >= 20) quality = 3;
	if (pchar.rank > 30) quality = 4;
	return "book"+quality+"_"+sti(drand(13)+1);
}
