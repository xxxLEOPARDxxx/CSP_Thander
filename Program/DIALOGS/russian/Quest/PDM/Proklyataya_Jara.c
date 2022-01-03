
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "Эй, ты! Ты чего тут болтаешься! Ну-ка, иди сюда, "+ GetSexPhrase("парень","девочка") +"!";
			link.l1 = "Меня зовут капитан "+pchar.name+", и я прогуливаюсь, а не болтаюсь!";
			link.l1.go = "Mne_Jarko_1";
			PlayVoice("Kopcapkz\Voices\PDM\Hervisse - Town Guard.wav");
		break;

		case "Mne_Jarko_1":
			dialog.text = "О, простите, капитан. Не узнал вас сразу. Это всё проклятая жара.";
			MakeRandomLinkOrderTwo(link,
			"Я принимаю ваши извинения. Стоять здесь весь день на солнце, наверное, не очень-то приятно. Вам хоть дают передохнуть во время вахты?",
			"Mne_Jarko_2",

			"Нет, этого недостаточно. Вы беспечны и неопрятно выглядите. В следующий раз будьте повежливее.",
			"exit");
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
		break;

		case "Mne_Jarko_2":
			dialog.text = "Иногда мы меняемся друг с другом, левый на правого, правый на левого... Всё зависит от того, куда падает тень. Ужасно, всё бы отдал за глоток прохладного вина.";
			link.l1 = "Да, это просто отвратительно... Быть может, я могу помочь вам как-то?";
			link.l1.go = "Mne_Jarko_3";
		break;

		case "Mne_Jarko_3":
			dialog.text = "О, спасибо вам, "+ GetSexPhrase("месье","мадмуазэль") +"! Всё, о чём я могу мечтать сейчас - это всего лишь небольшой глоток вина. Конечно, мне не полагается пить на посту, но всё же... Вы не согласились бы принести мне бутыль вина? Я даже мог бы заплатить вам за это.";
			MakeRandomLinkOrderTwo(link,
			"Я знаю, как иногда тяжел бывает долг... Я принесу вам бутылку вина.",
			"Mne_Jarko_4",

			"Солдат, вы очень близки к тому, чтобы преступить границы долга. Я закрою глаза на это в данный момент... Но не просите меня об этом более. До встречи.",
			"exit");
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
		break;

		case "Mne_Jarko_4":
			dialog.text = "Спасибо вам, "+ GetSexPhrase("месье","мадмуазэль") +"... Я в вечном долгу перед вами. Прошу вас, поспешите.";
			link.l1 = "Не успеешь моргнуть, как я уже вернусь.";
			link.l1.go = "Mne_Jarko_5";
			DeleteAttribute(npchar, "talker");
		break;

		case "Mne_Jarko_5":
			SetQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "1");
			DialogExit();
			pchar.questTemp.PDM_PJ_KV = "KupitVino";
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Mne_Jarko_5_EsheRaz";
		break;

		case "Mne_Jarko_5_EsheRaz":
			dialog.text = "Вы принесли для меня вино?";
			link.l1 = "Нет пока, я просто осматривал"+ GetSexPhrase("","а") +" город. Любовал"+ GetSexPhrase("ся","ась") +" достопримечательностями, так сказать. Но я загляну в таверну, попозже.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Mne_Jarko_5_EsheRaz";
		break;

		case "Prines_Vino_1":
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			dialog.text = "Приветствую вас ещё раз, "+ GetSexPhrase("месье","мадмуазэль") +" капитан! Вы принесли мне вино?";
			link.l1 = "Вот, возьми.";
			link.l1.go = "Prines_Vino_2";
		break;

		case "Prines_Vino_2":
			TakeItemFromCharacter(pchar, "PDM_PJ_Vino");
			sld = CharacterFromID("FortFrance_tavernkeeper")
			dialog.text = "Я и не думал, что вы вправду сподобитесь принести мне бутылку. Спасибо, капитан "+pchar.name+". Сколько я должен вам за это вино?";
			MakeRandomLinkOrderTwo(link,
			"Не волнуйся относительно денег - мне было приятно сделать это для тебя.",
			"Prines_Vino_Drujba_1",

			"Десять золотых. Я попросил"+ GetSexPhrase("","а") +" вина не очень дорогого, но, похоже, в вашей таверне заправляет бывший пират, этот "+sld.name+".",
			"Prines_Vino_Obman_1");
		break;

		case "Prines_Vino_Drujba_1":
			dialog.text = "Вы очень добрый человек, "+ GetSexPhrase("месье","мадмуазэль") +". Я буду рад послужить вам, если вам что-то понадобится.";
			link.l1 = "Спасибо, дружок. До встречи.";
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, 3);
		break;

		case "Prines_Vino_Obman_1":
			dialog.text = "Десять? Ой, но это же половина моего жалованья... И что мне теперь делать?";
			MakeRandomLinkOrderTwo(link,
			"Тебе следовало подумать об этом раньше. А теперь уж плати.",
			"Prines_Vino_Obman_2",

			"Да забудь ты про это. Будем считать эту бутылочку просто подарком.",
			"Prines_Vino_Drujba_1");
		break;

		case "Prines_Vino_Obman_2":
			sld = CharacterFromID("FortFrance_tavernkeeper")
			dialog.text = "Чёрт подери. Ну, попадись мне этот "+sld.name+". Ладно, берите деньги. Всё, мне нужно стоять на посту, я на могу разговаривать с вами больше. До встречи.";
			link.l1 = "До свидания, солдат.";
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, -3);
			AddMoneyToCharacter(pchar, 8);
		break;

		case "A_Eto_eshe_ne_vse":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.5, 0);
		break;

		case "Ya_Toje_Hochu_1":
			PlayVoice("Kopcapkz\Voices\PDM\Eustache Heumont.wav");
			dialog.text = "Приветствую вас, "+ GetSexPhrase("месье","мадмуазэль") +". Рад видеть вас!";
			link.l1 = "Почему же вы так рады видеть меня, солдат? И что это за ухмылка у вас на физиономии?";
			link.l1.go = "Ya_Toje_Hochu_2";
		break;

		case "Ya_Toje_Hochu_2":
			dialog.text = "Я знаю, "+ GetSexPhrase("месье","мадмуазэль") +", что вы добрый человек. Я видел, как вы принесли моему напарнику бутылку вина... Христианский поступок, и я его оценил. А ещё я хотел спросить вас, капитан... Не могли бы вы и мне тоже оказать такое милосердие? Пожалуйста, капитан!";
			link.l1 = "Что?!? Вы хотите, чтобы я и вам купил"+ GetSexPhrase("","а") +" вина?";
			link.l1.go = "Ya_Toje_Hochu_3";
		break;

		case "Ya_Toje_Hochu_3":
			dialog.text = "Что ж, если говорить правду, "+ GetSexPhrase("месье","мадмуазэль") +", я не большой поклонник вина. Но вот капелька рома мне бы не помешала, "+ GetSexPhrase("месье","мадмуазэль") +".";
			MakeRandomLinkOrderTwo(link,
			"Ну, вас не назовешь стеснительным мальчуганом... Ладно уж. Честно говоря, я сам"+ GetSexPhrase("","а") +" в замешательстве от собственного мягкосердечия, но я куплю вам рома. Подождите меня здесь.",
			"Ya_Toje_Hochu_4",

			"Очевидно, они теперь позволяют слепым служить в армии, раз вы принимаете меня за официантку. Никакого рома, юноша, а если я узнаю, что кто-то из часовых пьёт на посту, я расскажу об этом губернатору.",
			"Ya_Toje_Hochu_Proval");
		break;

		case "Ya_Toje_Hochu_Proval":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.dialog.filename   = "Common_Soldier.c";
			sld.dialog.currentnode   = "First time";
			CloseQuestHeader("PDM_Proklyataya_Jara");
		break;

		case "Ya_Toje_Hochu_4":
			dialog.text = "Конечно,  "+ GetSexPhrase("месье","мадмуазэль") +". Я не могу никуда уйти - я на посту... Спасибо вам большое,  "+ GetSexPhrase("месье","мадмуазэль") +".";
			link.l1 = "Я скоро вернусь.";
			link.l1.go = "Ya_Toje_Hochu_5";
		break;

		case "Ya_Toje_Hochu_5":
			DialogExit();
			AddQuestRecord("PDM_Proklyataya_Jara", "3");
			pchar.questTemp.PDM_PJ_KR = "KupitRom";
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_5_EsheRaz";
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		break;

		case "Ya_Toje_Hochu_5_EsheRaz":
			dialog.text = "О, вы уже вернулись, капитан? Где мой ром?";
			link.l1 = "Стыдно сказать, но я забыл"+ GetSexPhrase("","а") +" о нашем маленьком договоре. Я прямо сейчас пойду за ним.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ya_Toje_Hochu_5_EsheRaz";
		break;

		case "Prines_Rom_1":
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			dialog.text = "Ой, вы вернулись, капитан? И... прошу прощения, "+ GetSexPhrase("месье","мадмуазэль") +"... но... вы не нашли рома?";
			link.l1 = "Вот, возьмите. Полагаю, это укрепит мою репутацию лучшего местного поставщика спиртных напитков для французской армии.";
			link.l1.go = "Prines_Rom_2";
		break;

		case "Prines_Rom_2":
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			TakeItemFromCharacter(pchar, "PDM_PJ_Rom");
			dialog.text = "Хорошая шутка, "+ GetSexPhrase("месье","мадмуазэль") +". И большое вам спасибо за ром. Вы "+ GetSexPhrase("простой и симпатичный джентльмен","простая и симпатичная девушка") +", не то, что эти заносчивые аристократы. Хотелось бы мне, чтобы у меня был такой командир.";
			link.l1 = "Хорошо, солдат, вам лучше вернуться на пост. И помалкивайте насчёт рома, а не то моя шутка может оказаться слишком похожей на правду...";
			link.l1.go = "Prines_Rom_3";
		break;

		case "Prines_Rom_3":
			dialog.text = "Как хотите, "+ GetSexPhrase("месье","мадмуазэль") +". Я буду помалкивать, обещаю. Спасибо вам. Всего вам хорошего.";
			link.l1 = "Не за что. До встречи.";
			link.l1.go = "Prines_Rom_4";
		break;

		case "Prines_Rom_4":
			DialogExit();
			CloseQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "5");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

	}
}
