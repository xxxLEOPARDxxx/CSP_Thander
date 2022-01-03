
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	float   locx, locy, locz;

	switch(Dialog.CurrentNode)
	{
		case "prisonerHead":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуйте. Я так понимаю, что это вы - "+ GetSexPhrase("последний прибывший гражданин","последняя прибывшая гражданка") +"?";
				link.l1 = "Именно так. Меня зовут " + GetFullName(pchar) + ".";
				link.l1.go = "FTH_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Здравствуйте. Что вам нужно в тюрьме?";
				link.l1 = "Да ничего особенного. Просто так заскочил"+ GetSexPhrase("","а") +".";
				link.l1.go = "Exit";
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l6 = "А вы не знаете, кто был начальником тюрьмы до вас?";
						link.l6.go = "LostDecsterHead";
					}
				}
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = "Не подскажете, а за что сюда попал Максим Тейлор?";
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "seekFreeMotod")
				{
					link.l7 = "Послушайте, а можно как-нибудь содействовать освобождению этого пьяницы и дебошира Максима Тейлора?";
					link.l7.go = "ELTHusb_SF";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
				{
					link.l7 = "Послушайте, а можно как-нибудь содействовать освобождению этого пьяницы и дебошира Максима Тейлора?";
					link.l7.go = "ELTHusb_SF";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Послушайте, есть серьезный разговор. Я набираю команду.";
					link.l8.go = "SeekCrew";
				}
			}
			NextDiag.TempNode = "prisonerHead";
		break;
		case "FTH_1":
			dialog.text = "Ну что же, примите мои поздравления. Я - начальник тюрьмы Города, подчиняюсь непосредственно адмиралу. Я не против дружеских отношений с кем бы то ни было, но учтите, что если окажетесь за решеткой - дружбе конец.";
			link.l1 = "Да-да, я понимаю. И много через вас народу проходит?";
			link.l1.go = "FTH_2";
		break;
		case "FTH_2":
			dialog.text = "Нет, к сожалению, давно уже никого не было. Кланы живут своей жизнью, не высовываются. А граждане предпочитают не дебоширить.";
			link.l1 = "Ясно. Ну что же, удачи вам в нелегком труде ничегонеделания.";
			link.l1.go = "FTH_3";
		break;
		case "FTH_3":
			dialog.text = "И не говорите! Порой, от тоски на луну выть готов...";
			link.l1 = "Понимаю... Ну, всего доброго.";
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "prisoner":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Приветствую. Я рад, что ты выжил"+ GetSexPhrase("","а") +" и теперь находишься среди нас. Я тюремщик, меня зовут " + GetFullName(npchar) + ".";
				link.l1 = "Очень приятно. А я - капитан " + GetFullName(pchar) + ".";
				link.l1.go = "FTP_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Если ты здесь по делу, то я прошу разговаривать с начальником.";
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && npchar.chr_ai.type == LAI_TYPE_SIT && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l1 = "Слушай, а ты не в курсе, кто такой Лейтон Декстер?";
						link.l1.go = "LostDecster";
					}
				}
				//квест с вином от Доминика Легро
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toTomasBoil" && CheckCharacterItem(pchar, "potionwine"))
				{
					link.l2 = "Приятель, я принес"+ GetSexPhrase("","ла") +" тебе бутылочку вина от твоего друга Доминика Легро. Выпей, расслабься, а то сидишь тут безвылазно...";
					link.l2.go = "WineLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toSecondToPrison")
				{
					link.l2 = "Приятель, это опять я. И снова по поводу Доминика Легро.";
					link.l2.go = "SecondLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "to3ToPrison")
				{
					link.l2 = "Дружище, похоже, что Доминик ничего предосудительного в отношении Армо не делал.";
					link.l2.go = "LastLegro";
				}
				//помощь тюремщика в наезде на касперов, если Армо убита
				iTemp = GetCharacterIndex("LSCwaitress");
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && CheckAttribute(pchar, "questTemp.LSC.LegroHelp.Armo") && iTemp != -1 && characters[iTemp].name != "Армо" && pchar.questTemp.LSC == "toSeekMechanik")
				{
					link.l3 = "Дружище, ты знаешь, что Армо убита?";
					link.l3.go = "ArmoIsDead";
				}
				link.l10 = "Хорошо, я понял"+ GetSexPhrase("","а") +".";
				link.l10.go = "Exit";
			}
			NextDiag.TempNode = "prisoner";
		break;
		case "FTP_1":
			dialog.text = "Ну что же, вот и познакомились. Если ты здесь по делу, то тебе нужно разговаривать с моим шефом.";
			link.l1 = "Ясно.";
			link.l1.go = "exit";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Какую команду?",
				"Мы уже говорили об этом.",
				"Это уже обсуждено, второй раз повторяю.",
                "Хватит, утомил"+ GetSexPhrase("","а") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Команду на корабль. Я ухожу из города.",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаешь...",
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Вы что, с ума сошли? Законов Города не знаете?";
			link.l1 = "Я спасаю свою жизнь, только и всего. Предлагаю вам спасти заодно и вашу. Дело в том, что Город будет разрушен этим штормом.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Я вам не верю.";
			link.l1 = "Очень зря.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хех, каков"+ GetSexPhrase("","а") +" "+ GetSexPhrase("провидец","предсказательница") +", просто оторопь берет! Я порекомендую вам умерить прыть.";
			link.l1 = "Ну, мое дело предложить...";
			link.l1.go = "exit";
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat("Вы не поверите! Этот кретин нализался в таверне и пошел в резиденцию к адмиралу права качать.",
				"Я уже ответил на ваш вопрос.",
				"Мы уже говорили об этом!",
                "Послушайте, прекратите немедленно!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("О-хо-хо... И что за требования он пытался предъявить?",
				"Да-да, я помню.",
                "Конечно.",
				"Хорошо-хорошо...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = "Да шут его знает. Вообще-то, Максим - наш перманентный постоялец, но с Каппером он в первый раз связался. И очень зря, скажу я вам. Попав сюда, он еще оч-чень хорошо отделался...";
			link.l1 = "А что могло произойти в наихудшем варианте?";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "Ну, история не терпит сослагательных наклонений.";
			link.l1 = "В общем, понятно...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "3");
		break;

		case "ELTHusb_SF":
			dialog.text = NPCStringReactionRepeat("С этим вопросом я просил бы вас обратиться к адмиралу. Он его сюда посадил, он же пусть и принимает решение о его дальнейшей судьбе.",
				"Мы уже говорили на эту тему.",
				"Еще раз повторю, что мы уже говорили на эту тему.",
                "Вы идиот?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("А с вами я могу как-нибудь договориться?",
				"Да, забыл"+ GetSexPhrase("","а") +"...",
                "Опять забыл"+ GetSexPhrase("","а") +".",
				"Очень на похоже на то...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_SF_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_SF_1":
			dialog.text = "Да вы с ума сошли! Идите к Капперу, мой вам совет.";
			link.l1 = "За совет спасибо.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "4");
		break;

		case "LostDecsterHead":
			dialog.text = "Нет, не знаю. И вам не советую знать.";
			link.l1 = "В каком смысле?";
			link.l1.go = "LostDecsterHead_1";
		break;
		case "LostDecsterHead_1":
			dialog.text = "В прямом. Я не советую вам знать, кто был начальником тюрьмы до меня.";
			link.l1 = "А может быть, это Лейтон Декстер.";
			link.l1.go = "LostDecsterHead_2";
		break;
		case "LostDecsterHead_2":
			dialog.text = "Все может быть... А к чему эти расспросы?";
			link.l1 = "Да ни к чему, пустое любопытство.";
			link.l1.go = "LostDecsterHead_3";
		break;
		case "LostDecsterHead_3":
			dialog.text = "Не проявляйте его более. Любопытство, знаете ли, весьма опасное свойство организма...";
			link.l1 = "Хм... Да-да, я понимаю.";
			link.l1.go = "exit";
			npchar.quest.decster = true; //не повторять базар
		break;

		case "LostDecster":
			dialog.text = "Бывший начальник 'Тартаруса'.";
			link.l1 = "А где он сейчас?";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "Хе-хе... За во-о-он той дверью, что слева от последней клетки в правом ряду. Но только никому ни слова!..";
			link.l1 = "Никогда!";
			link.l1.go = "exit";
			AddQuestRecord("LSC_findDekster", "4");
			npchar.quest.decster = true; //не повторять базар
		break;
		//вино от Доминика Легро
		case "WineLogro":
			dialog.text = "Бутылочка вина от Доминика Легро?!\nВино я возьму, так уж и быть. Но этому проходимцу передай, я еще с ним расквитаюсь!";
			link.l1 = "Не понял"+ GetSexPhrase("","а") +"...";
			link.l1.go = "WineLogro_1";
		break;
		case "WineLogro_1":
			dialog.text = "А тебе и нечего понимать. Просто передай, что я ему уши на ходу обрежу.";
			link.l1 = "Ну ладно, передам... А Доминик-то думал, что ты обрадуешься.";
			link.l1.go = "WineLogro_2";
			TakeItemFromCharacter(pchar, "potionwine");
		break;
		case "WineLogro_2":
			dialog.text = "Я очень рад... Ну ладно, некогда мне тут говорильню разводить. За вино спасибо, а Доминику передай мои слова.";
			link.l1 = "Хорошо, передам.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toFackDominic";
			AddQuestRecord("TakeVineToPrisoner", "2");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("","ла"));
		break;

		case "SecondLogro":
			dialog.text = "Что скажешь?";
			link.l1 = "Передал"+ GetSexPhrase("","а") +" я ему твои слова. Он очень удивился и клянется, что совершенно не в курсе того, что происходит.";
			link.l1.go = "SecondLogro_1";
		break;
		case "SecondLogro_1":
			dialog.text = "Неужели?";
			link.l1 = "Он поклялся.";
			link.l1.go = "SecondLogro_2";
		break;
		case "SecondLogro_2":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name == "Армо")
			{
				dialog.text = "А когда он клялся, он, случайно, не вспоминал о том, как намедни заигрывал с Армо Дюлин, официанткой из таверны?";
				link.l1 = "Понятия не имею.";
				link.l1.go = "SecondLogro_3";
				pchar.questTemp.LSC.LegroHelp.Armo = true; //флаг на то, что квест пошел с участием Армо
			}
			else
			{
				dialog.text = "Даже так?.. Хм, ну что же, тогда, пожалуй, нам стоит помириться.";
				link.l1 = "Так Доминик с тобой и не ругался.";
				link.l1.go = "LastLegroAdd";
			}
		break;
		case "SecondLogro_3":
			dialog.text = "Ну, так ты спроси его.";
			link.l1 = "Ладно...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toArmoDominic";
			AddQuestRecord("TakeVineToPrisoner", "4");
		break;

		case "LastLegro":
			dialog.text = "Как это?";
			link.l1 = "Он говорит, что просто разговаривал с Армо, но никоим образом не клеился к ней.";
			link.l1.go = "LastLegro_1";
		break;
		case "LastLegro_1":
			dialog.text = "Но мне сказали...";
			link.l1 = "Не стоит руководствоваться сплетнями в отношениях с друзьями.";
			link.l1.go = "LastLegro_2";
		break;
		case "LastLegro_2":
			dialog.text = "Да, ты прав"+ GetSexPhrase("","а") +"\nНу что же, я верю Доминику. Передай ему, что я прошу у него прощения. Похоже, что я недостойно себя вел.";
			link.l1 = "Да уж, действительно, похоже на то.";
			link.l1.go = "LastLegro_3";
		break;
		case "LastLegro_3":
			dialog.text = "Спасибо тебе, "+ GetSexPhrase("друг","" + pchar.name + "") +", за участие в наших с Домиником делах.";
			link.l1 = "Всегда рад"+ GetSexPhrase("","а") +" помочь.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toKeyDominic";
			AddQuestRecord("TakeVineToPrisoner", "6");
		break;

		case "LastLegroAdd":
			dialog.text = "Да, ты прав"+ GetSexPhrase("","а") +"... Слушай, передай Доминику, что все нормально. Я не сержусь на него.";
			link.l1 = "Ну, отлично! Что же, тогда я, пожалуй, пойду...";
			link.l1.go = "LastLegro_3";
		break;
		//если Армо убита, то тюремщик может помочь в наезде на касперов
		case "ArmoIsDead":
			dialog.text = "Мне это известно.";
			link.l1 = "А ты знаешь, кто это сделал?";
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = "Пытаюсь узнать. Как найду - вырежу сердце.";
			link.l1 = "Это сделал Хуан Кобо, один из 'касперов'.";
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = "Откуда ты знаешь?";
			link.l1 = "Он сам мне это сказал. Но спешить тебе некуда, я уже прикончил"+ GetSexPhrase("","а") +" его.";
			link.l1.go = "ArmoIsDead_3";
		break;
		case "ArmoIsDead_3":
			dialog.text = "Жаль...";
			link.l1 = "Ну, я бы так не сказал"+ GetSexPhrase("","а") +".";
			link.l1.go = "ArmoIsDead_4";
		break;
		case "ArmoIsDead_4":
			dialog.text = "Что ты имеешь в виду?";
			link.l1 = "Я предлагаю тебе не персонифицировать месть, а отомстить всему клану, ведь Кобо был просто исполнителем. Ты не хуже меня знаешь, что они и шагу не ступают без указки главаря клана.";
			link.l1.go = "ArmoIsDead_5";
		break;
		case "ArmoIsDead_5":
			dialog.text = "Это так...";
			link.l1 = "Я собираюсь вторгнуться на 'Сан Габриэль'. Ты можешь пойти со мной.";
			link.l1.go = "ArmoIsDead_6";
		break;
		case "ArmoIsDead_6":
			dialog.text = "Я готов.";
			link.l1 = "Тогда вперед, не будет откладывать это дело.";
			link.l1.go = "ArmoIsDead_7";
		break;
		case "ArmoIsDead_7":
			if (npchar.chr_ai.type == LAI_TYPE_SIT)
			{
				GetCharacterPos(npchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			sld.dialog.currentnode = "AfterFightCasper";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("ISS_MainLine", "70");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "AfterFightCasper":
			dialog.text = "Ну что, похоже, что мы справились.";
			link.l1 = "Верно. Спасибо за помощь, дружище. Не хочешь и дальше участвовать со мной в заварушках такого рода?";
			link.l1.go = "AfterFightCasper_1";
		break;
		case "AfterFightCasper_1":
			dialog.text = "Нет. Это была месть, а не жажда приключений. Я, пожалуй, пойду напьюсь. Тяжко без Армо...";
			link.l1 = "А как же тюрьма?";
			link.l1.go = "AfterFightCasper_2";
		break;
		case "AfterFightCasper_2":
			dialog.text = "Плевать на тюрьму, на адмирала, да и вообще на весь этот проклятый город! Эх, без Армо мне жизнь не мила...";
			link.l1 = "Сожалею, дружище.";
			link.l1.go = "AfterFightCasper_3";
		break;
		case "AfterFightCasper_3":
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
