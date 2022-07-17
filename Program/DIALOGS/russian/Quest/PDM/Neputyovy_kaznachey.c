
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sBlade;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int Plata1 = 14000 * MOD_SKILL_ENEMY_RATE * 0.21;
	int Plata2 = 14000 * MOD_SKILL_ENEMY_RATE * 0.31;

	pchar.PDM_NK_Plata2.Money = 14000 * MOD_SKILL_ENEMY_RATE * 0.31;

	int Sila = 25 + MOD_SKILL_ENEMY_RATE * 2.8;
	int DopHP = 40 + MOD_SKILL_ENEMY_RATE * 10;
	int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE * 1.2;
	if (Rank < 1) Rank = 1;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "К-кто вы?";
			link.l1 = "Капитан "+pchar.name+". А вы?";
			link.l1.go = "Fickler_1";
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			DeleteAttribute(npchar, "talker");
		break;

		case "Fickler_1":
			dialog.text = "А-а-андреас Фиклер, к-к вашим услугам.";
			link.l1 = "Ты чего весь трясёшься, приятель?";
			link.l1.go = "Fickler_2";
		break;

		case "Fickler_2":
			dialog.text = "В-в-вы тоже т-т-тряслись бы, если бы к-кто-нибудь собирался вас убить!";
			link.l1 = "Кто-то хочет тебя убить?";
			link.l1.go = "Fickler_3";
		break;

		case "Fickler_3":
			dialog.text = "Д-да, "+ GetSexPhrase("минхер","мефрау") +". Я не могу спать. Я в-весь разбит. И это всё из-за этого п-проклятого пороха!";
			link.l1 = "Похоже, это любопытная история. Излей мне свою душу, приятель.";
			link.l1.go = "Fickler_4";
		break;

		case "Fickler_4":
			dialog.text = "Ну, д-думаю, я могу вам д-доверять. Я казначей... Я б-был казначеем на каравелле 'Морская чайка'. Наш к-к-капитан закупил слишком много п-пороха - хотя я советовал ему этого не делать! Мне п-пришлось хранить некоторые бочонки в неп-подходящих местах. На юте, к примеру. И один из наших безмозглых матросов как-то нализался до бесчувствия. Я г-говорил, чтобы никто не курил н-на юте, но этот тупоголовый пьяный урод уселся прямо на бочонок с порохом и... и...";
			link.l1 = "Закурил трубку?";
			link.l1.go = "Fickler_5";
		break;

		case "Fickler_5":
			dialog.text = "Д-да... А потом уронил её... И отправился п-прямиком в ад. Вместе с ютом, штурвалом и половиной корабля. Мат-т-тросы потушили пожар, но весь груз уже был п-потерян. А к-капитан сказал, что я не доживу до рассвета! Сейчас он в таверне, заливает свою злобу ромом. Но я б-боюсь, что он не ограничится в-выпивкой. И т-тогда он вытащит свой к-кортик и убьёт меня прямо здесь, на площади!";
			link.l1 = "Действительно забавная история. Не волнуйся, Андреас. Я помогу тебе.";
			link.l1.go = "Fickler_6";
			link.l2 = "Ну, в будущем будь осторожнее с порохом. Ладно, счастливо тебе прожить несколько оставшихся часов. Прощай.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;

		case "Fickler_6":
			dialog.text = "К-к-как?";
			link.l1 = "Не знаю. Что-нибудь придумаю. Жди меня здесь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_NK_Viktor", "officer_52", "man", "man", 10, PIRATE, -1, false));
			sld.name = "Виктор";
			sld.lastname = "Бретье";
			sld.city = "Villemstad";
			sld.location	= "Villemstad_tavern";
			sld.location.group = "sit";
			sld.location.locator = "sit12";
			LAi_SetSitType(sld);
			sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Viktor";

			SetQuestHeader("PDM_Neputyovy_kaznachey");
			AddQuestRecord("PDM_Neputyovy_kaznachey", "1");
		break;

		case "Fickler_7":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "Капитан Виктор! А, это вы, да... Вы н-нап-пуг-гали меня до полусмерти. В-в-вы видели В-в-иктора?");
			link.l1 = "Нет пока. Но не волнуйся - я позабочусь о нём.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";
		break;

		case "Fickler_8":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "Эээ! Стойте! Держитесь от меня подальше! А... это вы. Ну что ж, скоро он меня найдёт...";
			link.l1 = "Не волнуйся, Андреас. Я позабочусь о нём.";
			link.l1.go = "Fickler_6";
			link.l2 = "Ладно, счастливо тебе прожить несколько оставшихся часов. Прощай.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;

		case "Viktor":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "Ты! Эй, ты! Ты не видел здесь очкастого, безмозглого казначея по имени Андреас? Он виноват в том, что я на мели! Паразит! Я убью его! Он разорил меня!";
			link.l1 = "Так-так-так. Ты - Виктор Бретье.";
			link.l1.go = "Viktor_2";
		break;

		case "Viktor_2":
			dialog.text = "Да, я Виктор. А этот вонючий пёс спалил половину моего корабля этими чёртовыми бочонками с порохом! Я сдеру с него кожу заживо!";
			link.l1 = "Успокойся, приятель. Андреас под моей защитой.";
			link.l1.go = "Viktor_3";
		break;

		case "Viktor_3":
			dialog.text = "Чего? Под твоей защитой? Да кто ты "+ GetSexPhrase("такой","такая") +"?";
			link.l1 = "Я - капитан "+pchar.name+". И если ты тронешь хотя бы волосок на его голове, то я спалю и вторую половину твоего корабля.";
			link.l1.go = "Viktor_4";
		break;

		case "Viktor_4":
			dialog.text = ""+ GetSexPhrase("Проклятый пират","Проклятая пиратка") +"! Кем ты себя вообразил"+ GetSexPhrase("","а") +"? Есть управа в этом мире на этих обнаглевших пиратов? Они притесняют честных капитанов как в море, так и на суше! Где же справедливость?";
			link.l1 = "Ты угрожаешь убить своего казначея, и ещё говоришь о справедливости? Я не думаю, что губернатор отнесётся спокойно к убийству невинного человека, произошедшему на его земле.";
			link.l1.go = "Viktor_5";
		break;

		case "Viktor_5":
			dialog.text = "Невинного? Из-за этого идиота я потерял свой фрахт! " + Plata1 + " золотых! Если не больше! Я узнаю, куда он спрятался!";
			link.l1 = "Уж лучше я тебя покромсаю на мелкие кусочки, чем дам Андреаса в обиду.";
			link.l1.go = "Viktor_Bitva";
			link.l2 = "" + Plata1 + " золотых? И из-за этого ты поднял шум? Вот. Я покрываю твой ущерб, теперь оставь Андреаса в покое.";
			link.l2.go = "Zaplati_ED";
			link.l3 = "" + Plata1 + "? Я принесу тебе эти деньги. Но помни - один залп моего корабля превратит твоё корыто в решето, так что не трогай Андреаса и пальцем!";
			link.l3.go = "Zaplati_ND";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;

		case "Zaplati_ED":
			dialog.text = "Я сказал " + Plata1 + "? Нет, я ошибся! По крайней мере, " + Plata2 + "!";
			link.l1 = "Да ты обнаглел, Виктор! Уж лучше я тебя покромсаю на мелкие кусочки, чем дам Андреаса в обиду.";
			link.l1.go = "Viktor_Bitva";
			link.l2 = "Вот, держи свои деньги. Приятного времяпрепровождения, Виктор.";
			link.l2.go = "Zaplati_2";
			link.l3 = "Я принесу тебе эти " + Plata2 + ". Но помни - один залп моего корабля превратит твоё корыто в решето, так что не трогай Андреаса и пальцем!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
			AddQuestRecord("PDM_Neputyovy_kaznachey", "2");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sMoney", FindRussianMoneyString(sti(pchar.PDM_NK_Plata2.Money)));
		break;
		
		case "Zaplati_ND":
			dialog.text = "Я сказал " + Plata1 + "? Нет, я ошибся! По крайней мере, " + Plata2 + "!";
			link.l1 = "Да ты обнаглел, Виктор! Уж лучше я тебя покромсаю на мелкие кусочки, чем дам Андреаса в обиду.";
			link.l1.go = "Viktor_Bitva";
			link.l2 = "Хорошо, как только будут у меня деньги, я к тебе загляну.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
			AddQuestRecord("PDM_Neputyovy_kaznachey", "2");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sMoney", FindRussianMoneyString(sti(pchar.PDM_NK_Plata2.Money)));
		break;

		case "Zaplati_2":
			if (sti(pchar.Money) >= Plata2)
			{
				AddMoneyToCharacter(pchar, -sti(Plata2));
				Log_SetStringToLog("Авторитет + 1");
				Log_SetStringToLog("Торговля + 2");
				Log_SetStringToLog("Скрытность + 1");
				AddCharacterSkillDontClearExp(pchar, "Leadership", 1);
				AddCharacterSkillDontClearExp(pchar, "Commerce", 2);
				AddCharacterSkillDontClearExp(pchar, "Sneak", 1);
				sld = CharacterFromID("PDM_NK_Viktor")
				sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
				sld.dialog.currentnode   = "Viktor_Poka";
				sld.lifeday = 0;
				sld = CharacterFromID("Andreas_Fickler")
				sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
				sld.dialog.currentnode   = "Fickler_11";
				AddQuestRecord("PDM_Neputyovy_kaznachey", "3");
				AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("","а"));
				DialogExit();
			}
			else
			{
				dialog.text = "";
				link.l1 = "Сейчас у меня нет таких денег, Виктор, но я зайду позже и заплачу за Андреаса.";
				link.l1.go = "exit";
			}
		break;

		case "Viktor_Poka":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "Лопни твоя селезёнка! Что ещё тебе нужно?";
			link.l1 = "Ничего. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Viktor_Poka";
		break;

		case "Viktor_VernulsyDengi":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "Снова ты? Чего тебе нужно?";
			link.l1 = "Я просто хочу расплатиться за твоего бывшего казначея, Андреаса.";
			link.l1.go = "Viktor_VernulsyDengi_2";
		break;

		case "Viktor_VernulsyDengi_2":
			dialog.text = "Ты прин"+ GetSexPhrase("ёс","есла") +" деньги?";
			link.l1 = "" + Plata2 + " золотых. Вот, держи.";
			link.l1.go = "Zaplati_2";
			link.l2 = "Ещё нет, но я скоро принесу их тебе.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;

		case "Viktor_Bitva":
			dialog.text = "Ты пожалеешь об этих словах, ничтожество!";
			link.l1 = "Меньше слов - к делу!";
			link.l1.go = "fight_right_now";
			sld = CharacterFromID("PDM_NK_Viktor")

			if (MOD_SKILL_ENEMY_RATE <= 6)
				FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade18", "Pistol1", DopHP);
			else
				FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade39", "Pistol2", DopHP);

			sld.SaveItemsForDead = true;
			AddMoneyToCharacter(sld, 15000);
			GiveItem2Character(sld, "Litsenzia");

			PChar.quest.PDM_NK_Viktor.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_NK_Viktor.win_condition.l1.character = "PDM_NK_Viktor";
			PChar.quest.PDM_NK_Viktor.win_condition = "PDM_NK_Viktor";

			PChar.quest.PDM_NK_Litsenzia.win_condition.l1 = "item";
			PChar.quest.PDM_NK_Litsenzia.win_condition.l1.item = "Litsenzia";
			PChar.quest.PDM_NK_Litsenzia.win_condition = "PDM_NK_Litsenzia";
		break;

		case "fight_right_now":
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Fickler_11":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "К-к-капитан "+pchar.name+"! Ох, это вы, "+ GetSexPhrase("минхер","мефрау") +"! Вы н-папугали меня. Вы уже говорили с В-виктором?");
			link.l1 = "Да. Он больше не тронет тебя. Можешь спокойно возвращаться на свою 'Морскую чайку'.";
			link.l1.go = "Fickler_12";
		break;

		case "Fickler_12":
			dialog.text = "Спасибо! Т-тысячу раз с-с-спасибо! В-вы спасли мою жизнь! Но я не могу вернуться на свой корабль. Я стану п-п-посмешищем для команды. И это несмотря на то, что я хороший к-казначей с десятилетним стажем. Я не имею ни малейшего желания возвращаться на 'Морскую чайку'. Э-э... может, вам бы пригодился к-к-казначей, капитан?");
			link.l1 = "Думаю, пригодился бы. Ты нанят. Но только посмей подойти к крюйт-камере!";
			link.l1.go = "Fickler_13";
			link.l2 = "Извини, но мне сейчас казначей не нужен.";
			link.l2.go = "Fickler_NeNujen";
		break;

		case "Fickler_13":
			dialog.text = "Спасибо, к-капитан! Вы не п-п-пожалеете об этом!");
			link.l1 = "Добро пожаловать на борт, Андреас.";
			link.l1.go = "Fickler_Nanyat";
			sld = CharacterFromID("Andreas_Fickler")
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			ChangeCharacterReputation(sld, 80);
			sld.rank = 10;
			SetSPECIAL(sld, 4, 6, 4, 10, 10, 7, 6);
			SetSelfSkill(sld, 5, 5, 5, 5, 5);
			SetShipSkill(sld, 30, 60, 5, 5, 5, 5, 5, 5, 30);
			sld.loyality = MAX_LOYALITY;
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.greeting = "GR_Andreas_Fickler";
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true;
		break;

		case "Fickler_NeNujen":
			AddQuestRecord("PDM_Neputyovy_kaznachey", "6");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			DialogExit();
		break;

		case "Fickler_Nanyat":
			sld = CharacterFromID("Andreas_Fickler")
			SetCharacterRemovable(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PDM_NK_NaKorabl", 5);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("PDM_Neputyovy_kaznachey", "5");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			DialogExit();
		break;

	}
}
