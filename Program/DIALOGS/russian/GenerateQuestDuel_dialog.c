
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = PChar.name + " " + PChar.lastname;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// Первый дуалист -->
		case "Duelist_1_1":
			dialog.text = "Здравствуйте, капитан " + sName + ". Надеюсь, у вас найдётся свободное время для разговора?";
			link.l1 = "Приветствую, сударь. А что случилось?";
			link.l1.go = "Duelist_1_2";
            PlayVoice("Voice\Russian\cit_quest_" +(1 + rand(3))+".wav");
		break;

		case "Duelist_1_2":
			dialog.text = "Дело в том, что на сегодня у меня назначена дуэль, с неким человеком...";
			link.l1 = "И в чём же ваша проблема?";
			link.l1.go = "Duelist_1_3";
		break;

		case "Duelist_1_3":
			dialog.text = "Понимаете... Мне бы не хотелось самому драться с ним. Я плохой фехтовальщик, но на кону моя честь и от дуэли я отказаться не могу. Я подумал, что...";
			link.l1 = "Что я могу выступить вместо вас?";
			link.l1.go = "Duelist_1_4";
		break;

		case "Duelist_1_4":
			dialog.text = "Совершенно верно. Я заплачу вам.";
			link.l1 = "И сколько?";
			link.l1.go = "Duelist_1_5";
		break;

		case "Duelist_1_5":
			dialog.text = sti(PChar.GenerateQuestDuel.Money) + " пиастров.";
			link.l1 = "Я к вашим услугам.";
			link.l1.go = "Duelist_1_7";
			link.l2 = "Ха-ха-ха! За свою честь сражайтесь сами.";
			link.l2.go = "Duelist_1_6";
		break;

		case "Duelist_1_6":
			dialog.text = "Но капитан!";
			link.l1 = "Удачи. Она вам понадобиться.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelManCancel");
		break;

		case "Duelist_1_7":
			dialog.text = "Огромное спасибо, капитан. Дуэль назначена за городскими воротами. Время пришло - идёмте.";
			link.l1 = "Идёмте.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelAgree");
		break;

		case "Duelist_1_8":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = PChar.GenerateQuestDuel.WifeName + ", кто это такой?";
			link.l1 = PChar.GenerateQuestDuel.WifeName + ": "+ GetSexPhrase("Дорогой, этот капитан согласился помочь нам.","Дорогой, эта леди согласилась помочь нам.") +"";
			link.l1.go = "Duelist_1_9";
		break;

		case "Duelist_1_9":
			SetCameraDialogMode(NPChar);
			dialog.text = "Помочь в чём?!";
			link.l1 = "Сударь, я обещал вашей супруге отговорить вас от дуэли.";
			link.l1.go = "Duelist_1_10";
		break;

		case "Duelist_1_10":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = "Об этом не может быть и речи. Дуэль состоится, даже если этот ублюдок прилюдно извинится передо мной. Задета твоя честь, дорогая, и я должен смыть позор кровью!";
			link.l1 = PChar.GenerateQuestDuel.WifeName + ": " + PChar.GenerateQuestDuel.DuelistName + ", прошу тебя, ради всех святых, опомнись и пойди на мировую!..";
			link.l1.go = "Duelist_1_11";
		break;

		case "Duelist_1_11":
			SetCameraDialogMode(NPChar);
			dialog.text = "Я буду драться ради тебя и если нужно умру. Но умру с честью!";
			link.l1 = "Всё ясно. Я вижу, что дуэль нельзя предотвратить. И поэтому предлагаю вам свои фехтовальные услуги.";
			link.l1.go = "Duelist_1_12";
		break;

		case "Duelist_1_12":
			dialog.text = PChar.GenerateQuestDuel.WifeName + ": Как вы добры! " + PChar.GenerateQuestDuel.DuelistName + ", соглашайся! \n В сложившихся обстоятельствах это единственный выход. Я плохой боец, а судя по вашему виду, вы побывали и в более серьёзных передрягах.";
			link.l1 = "Ваша правда. Итак, за " + sti(PChar.GenerateQuestDuel.Money) + " пиастров я к вашим услугам. Где назначена дуэль?";
			link.l1.go = "Duelist_1_13";
		break;

		case "Duelist_1_13":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = "За городскими воротами. Идёмте, капитан, время пришло. " + PChar.GenerateQuestDuel.WifeName + ", ты останешься дома. \n " + PChar.GenerateQuestDuel.WifeName + ": Храни вас господь, капитан...";
			link.l1 = "Нам пора.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelWoman2Agree");
		break;

		case "Duelist_1_14":
			dialog.text = "Капитан, не знаю как вас и благодарить! Вы спасли мою жизнь. Этот наёмник не оставил бы мне и шанса!";
			link.l1 = "Насколько понимаю, свою часть договора я "+ GetSexPhrase("выполнил","выполнила") +"?";
			link.l1.go = "Duelist_1_15";
		break;

		case "Duelist_1_15":
			dialog.text = "Вот, возьмите эти деньги. Ещё раз благодарю вас, капитан!";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenaryHappyEnd");
		break;

		case "Duelist_1_16":
			dialog.text = "Не знаю, как и благодарить вас, капитан! Возьмите деньги и... Надеюсь, никто не узнает детали дуэли?";
			link.l1 = "Не беспокойтесь, я не из болтливых. До встречи.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithDuelistHappyEnd");
		break;
		// Первый дуалист <--

		// Жена первого дуэлянта -->
		case "Wife_1":
			dialog.text = "Капитан! Умоляю вас, помогите!";
			link.l1 = "Сударыня, прошу вас, успокойтесь. Что случилось?";
			link.l1.go = "Wife_2";
            PlayVoice("Kopcapkz\Voices\Events\Jungle_woman_hlp_0" +rand(9)+".wav");
		break;

		case "Wife_2":
			dialog.text = "Мой муж повздорил с соседом и ссора зашла так далеко, что они решили разрешить её на дуэли. " + PChar.GenerateQuestDuel.DuelistName + " плохо владеет шпагой. Его убьют, я уверена!";
			link.l1 = "Понимаю. Вы хотите, что бы я помирил"+ GetSexPhrase("","а") +" вашего мужа с соседом?";
			link.l1.go = "Wife_3";
		break;

		case "Wife_3":
			dialog.text = "Да! Я заплачу вам " + sti(PChar.GenerateQuestDuel.Money) + " пиастров, только отговорите его от дуэли.";
			link.l1 = "Я попробую. Ведите меня к вашему мужу.";
			link.l1.go = "Wife_5";
			link.l2 = "Извините, но это не по мне. Поищите другого парламентёра.";
			link.l2.go = "Wife_4";
		break;

		case "Wife_4":
			dialog.text = "Вы жестокий человек!";
			link.l1 = "Ээ.. Что поделать.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelWomanCancel");
		break;

		case "Wife_5":
			QuestDuelWomanAgree();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// Жена первого дуэлянта <--


		// Второй дуалист -->
		case "Duelist_2_1":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "Ага, пришёл! Кхм!";
			link.l1 = PChar.GenerateQuestDuel.DuelistFullName + ": Я требую сатисфакции!";
			link.l1.go = "Duelist_2_2";
		break;

		case "Duelist_2_2":
			SetCameraDialogMode(NPChar);
			dialog.text = "Вы будете удовлетворены. Кто это с вами?";
			link.l1 = PChar.GenerateQuestDuel.DuelistFullName + ": Этот человек будет драться вместо меня.";
			link.l1.go = "Duelist_2_3";
		break;

		case "Duelist_2_3":
			dialog.text = "Это ваше право. Ну а вместо меня выступит "+ GetSexPhrase("мой доверенный","эта девушка") +". Скажу по секрету - "+ GetSexPhrase("отменный фехтовальщик","отменная фехтовальщица") +". \n " + PChar.GenerateQuestDuel.DuelistFullName + ": К чёрту слова. Капитан, вы готовы?";
			link.l1 = "К вашим, услугам, господа.";
			link.l1.go = "Duelist_2_4";
		break;

		case "Duelist_2_4":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Mercenary));
			dialog.text = "Наёмник: Что же, приготовьтесь к смерти. Начнём!";
			link.l1 = "Начнём!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenary");
		break;

		case "Duelist_2_5":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "Чёрт побери!!! Надеюсь вы удовлетворены?";
			link.l1 = PChar.GenerateQuestDuel.DuelistFullName + ": Вполне. А теперь убирайтесь. Я не намерен больше смотреть на вас.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenaryEnd");
		break;

		case "Duelist_2_6":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "Приветствую, господа! " + PChar.GenerateQuestDuel.DuelistName + ", а кто это с вами?";
			link.l1 = PChar.GenerateQuestDuel.DuelistName + ": "+ GetSexPhrase("Этот человек","Эта девушка") +" будет драться вместо меня.";
			link.l1.go = "Duelist_2_7";
		break;

		case "Duelist_2_7":
			dialog.text = "Боже мой! А вы порядочный трус, " + PChar.GenerateQuestDuel.DuelistName + ". Не знал, не знал...";
			link.l1 = PChar.GenerateQuestDuel.DuelistName + ": Довольно ломать комедию! Правила позволяют пользоваться услугами доверенных лиц.";
			link.l1.go = "Duelist_2_8";
		break;

		case "Duelist_2_8":
			SetCameraDialogMode(NPChar);
			dialog.text = "Что же, когда я прикончу "+ GetSexPhrase("вашего доверенного","вашу защитницу") +", весь город узнает о вашей трусости. Начнём?";
			link.l1 = "К вашим услугам.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithDuelist");
		break;
		// Второй дуалист <--

		// Родственники -->
		case "Relative_1":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_1));
			dialog.text = "Что здесь произошло?";
			link.l1 = "Кто вы такие?";
			link.l1.go = "Relative_2";
            PlayVoice("Kopcapkz\Voices\Events\Captive_0"+(1 + rand(9))+".wav");
		break;

		case "Relative_2":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_2));
			dialog.text = "Мы не успели! Наш дядя убит! "+ GetSexPhrase("Мерзавец!!! Что ты натворил?","Мерзавка!!! Что ты натворила?") +"";
			link.l1 = "Постойте, я сейчас всё объясню...";
			link.l1.go = "Relative_3";
		break;

		case "Relative_3":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_1));
			dialog.text = "Я ШКУРУ С ТЕБЯ СПУЩУ!!!";
			link.l1 = "Мы как бы не так друг друга поняли...";
			link.l1.go = "Relative_4";
		break;

		case "Relative_4":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_2));
			dialog.text = "Защищайся, падаль!";
			link.l1 = "Чёрт!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithRelativeRevenge");
		break;
		// Родственники <--

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
