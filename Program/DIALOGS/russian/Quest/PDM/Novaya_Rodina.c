
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
			dialog.text = "Какая жалость, какая жалость. О, чёрт подери!";
			link.l1 = "Чего ты ты тут бормочешь себе под нос?";
			link.l1.go = "Nachalo_1";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
		break;

		case "Nachalo_1":
            dialog.text = "Меня зовут Хьюго. Хьюго Лесопилка. Я вижу, что ты тоже капитан. Не потратишь ли часок, чтобы выслушать мою историю?";
            link.l1 = "Я не против.";
			link.l1.go = "Slushau_1";
			link.l2 = "Ну, нет, вообще-то. Я лучше ещё где-нибудь часок проведу.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Slushau_1":
            dialog.text = "Ты ведь корсар"+ GetSexPhrase("","ка") +", не так ли?";
            if (CheckCharacterItem(Pchar, "patent_spa") || CheckCharacterItem(Pchar, "patent_fra") || CheckCharacterItem(Pchar, "patent_hol") || CheckCharacterItem(Pchar, "patent_eng"))
			{
				link.l1 = "Да, я корсар"+ GetSexPhrase("","ка") +".";
				link.l1.go = "Korsar_1";
			}
			else
			{
				link.l1 = "Ты что, хочешь меня оскорбить? Я "+ GetSexPhrase("свободный пират","свободная пиратка") +"!";
				link.l1.go = "Nelzya_Pomoch";
			}
		break;

		case "Nelzya_Pomoch":
            dialog.text = "А, тогда ты мне ничем не поможешь. Желаю тебе удачи, прощай.";
			link.l1 = "М-да, плодотворная беседа, нечего сказать. До встречи.";
			link.l1.go = "exit";
            link.l2 = "Ну, ты можешь, по крайней мере, поведать мне свою историю.";
			link.l2.go = "Istoria_1";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Istoria_1":
            dialog.text = "Ну хорошо. Вот, слушай: я стал слишком стар, чтобы вести жизнь пирата. Грабёж и драки - игры для молодёжи, понимаешь? А я не хочу больше рисковать своей шкурой, и хочу плавать спокойно, не вздрагивая при виде других кораблей. Но проблема в том, что мне некуда идти. Все хотят повесить меня, понимаешь? Но я придумал одну штуку, "+ GetSexPhrase("парень","девочка") +".\n"+
							"Я думаю купить себе каперское свидетельство, заработать золотишка и подкупить пару чиновников, да проклятые форты открывают пальбу, как только я подхожу к какому-либо порту, и я не могу добраться до губернатора, чтобы сделать ему предложение. Англичане или французы повесят меня, едва я окажусь у них в руках: у них приказ убить меня, как только я высуну нос. Я думаю, что я мог бы поступить на службу к испанцам, но я не могу зайти в их чёртовы порты, они тут же откроют по мне огонь!";
			link.l1 = "Мне очень жаль, Хьюго, но я ничем не могу помочь тебе. Я желаю тебе удачи. Счастливо.";
			link.l1.go = "exit";
			link.l2 = "Но чем я могу тебе помочь?";
			link.l2.go = "Davai_Pomogu_NET";
			link.l3 = "А как насчет Братства?";
			link.l3.go = "Davai_Pomogu_Bratstvo";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Davai_Pomogu_NET":
            dialog.text = "Ты не сможешь мне помочь, "+ GetSexPhrase("парень","девочка") +". Ты ведь пират"+ GetSexPhrase("","ка") +", не так ли? Тебе вышибут мозги, как только ты приблизишься к испанскому городу на расстояние мили.";
            link.l1 = "Верное замечание. Тогда до встречи. И желаю тебе удачи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Davai_Pomogu_Bratstvo":
            dialog.text = "Братство! Я не вхожу в него, и никогда не войду! Они устанавливают правила пиратства - правила, слыхал"+ GetSexPhrase("","а") +"? Правила для пиратов! Я никогда не слышал подобной чуши. Я тебе честно скажу, "+ GetSexPhrase("парень","девочка") +", Братство - это всего лишь банда безмозглых кретинов, собравшихся вместе, чтобы путаться у нас, свободных моряков, под ногами.";
            link.l1 = "Хмм. В конце концов, это твоё мнение. Ну ладно, тогда я боюсь, что ничего больше не смогу тебе предложить. До встречи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Podhodim_SNOVA_Reactia":
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
			if (CheckCharacterItem(Pchar, "patent_spa"))
			{
				dialog.text = "(Пьёт ром)";
				link.l1 = "Привет, Хьюго. Я теперь "+ GetSexPhrase("испанский корсар","испанская корсарка") +", могу я тебе чем-то помочь?";
				link.l1.go = "Ya_Ispania_1";
			}
			else
			{
				dialog.text = "Если ты не испанский капер, то нам не о чем с тобой разговаривать.";
				link.l1 = "Тогда счастливо.";
				link.l1.go = "exit";
			}
		break;

		case "Korsar_1":
			if (CheckCharacterItem(Pchar, "patent_eng"))
			{
				dialog.text = "Я так и думал. И под каким флагом ты плаваешь?";
				link.l1 = "Я плаваю под флагом Англии.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = "Я так и думал. И под каким флагом ты плаваешь?";
				link.l1 = "Я плаваю под флагом Франции.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
			if (CheckCharacterItem(Pchar, "patent_spa"))
			{
				dialog.text = "Я так и думал. И под каким флагом ты плаваешь?";
				link.l1 = "Я плаваю под флагом Испании.";
				link.l1.go = "Ya_Ispania_1";
			}
			if (CheckCharacterItem(Pchar, "patent_hol"))
			{
				dialog.text = "Я так и думал. И под каким флагом ты плаваешь?";
				link.l1 = "Я плаваю под флагом Голландии.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
		break;

		case "Nelzya_Pomoch_Korsar_2":
            dialog.text = "А, тогда ты мне ничем не поможешь. Желаю тебе удачи, прощай.";
			link.l1 = "М-да, плодотворная беседа, нечего сказать. До встречи.";
			link.l1.go = "exit";
            link.l2 = "Ну, ты можешь, по крайней мере, поведать мне свою историю.";
			link.l2.go = "Istoria_Korsar_2";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Istoria_Korsar_2":
            dialog.text = "Ну хорошо. Вот, слушай: я стал слишком стар, чтобы вести жизнь пирата. Грабёж и драки - игры для молодёжи, понимаешь? А я не хочу больше рисковать своей шкурой, и хочу плавать спокойно, не вздрагивая при виде других кораблей. Но проблема в том, что мне некуда идти. Все хотят повесить меня, понимаешь? Но я придумал одну штуку, "+ GetSexPhrase("парень","девочка") +".\n"+
							"Я думаю купить себе каперское свидетельство, заработать золотишка и подкупить пару чиновников, да проклятые форты открывают пальбу, как только я подхожу к какому-либо порту, и я не могу добраться до губернатора, чтобы сделать ему предложение. Англичане или французы повесят меня, едва я окажусь у них в руках: у них приказ убить меня, как только я высуну нос. Я думаю, что я мог бы поступить на службу к испанцам, но я не могу зайти в их чёртовы порты, они тут же откроют по мне огонь!";
			link.l1 = "Мне очень жаль, Хьюго, но я ничем не могу помочь тебе. Я желаю тебе удачи. Счастливо.";
			link.l1.go = "exit";
			link.l2 = "Но чем я могу тебе помочь?";
			link.l2.go = "Davai_Pomogu_KORSAR_NET_2";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Davai_Pomogu_KORSAR_NET_2":
            dialog.text = "Ты не сможешь мне помочь, "+ GetSexPhrase("парень","девочка") +". Ты ведь служишь врагам Испании, не так ли? Тебе вышибут мозги, как только ты приблизишься к испанскому городу на расстояние мили.";
            link.l1 = "Верное замечание. Тогда до встречи. И желаю тебе удачи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Ya_Ispania_1":
            dialog.text = "О, так ты с испанцами! Ты в самом деле мог"+ GetSexPhrase("","ла") +" бы мне помочь!";
            link.l1 = "А что у тебя случилось?";
			link.l1.go = "Ya_Ispania_2"
		break;

		case "Ya_Ispania_2":
            dialog.text = "Ну хорошо. Вот, слушай: я стал слишком стар, чтобы вести жизнь пирата. Грабёж и драки - игры для молодёжи, понимаешь? А я не хочу больше рисковать своей шкурой, и хочу плавать спокойно, не вздрагивая при виде других кораблей. Но проблема в том, что мне некуда идти. Все хотят повесить меня, понимаешь? Но я придумал одну штуку, "+ GetSexPhrase("парень","девочка") +".\n"+
							"Я думаю купить себе каперское свидетельство, заработать золотишка и подкупить пару чиновников, да проклятые форты открывают пальбу, как только я подхожу к какому-либо порту, и я не могу добраться до губернатора, чтобы сделать ему предложение. Англичане или французы повесят меня, едва я окажусь у них в руках: у них приказ убить меня, как только я высуну нос. Я думаю, что я мог бы поступить на службу к испанцам, но я не могу зайти в их чёртовы порты, они тут же откроют по мне огонь!";
            link.l1 = "И что мне нужно сделать?";
			link.l1.go = "Ya_Ispania_3";
		break;

		case "Ya_Ispania_3":
            dialog.text = "Ты корсар"+ GetSexPhrase("","ка") +", не так ли? Ты можешь зайти в испанский порт, и орудия форта не пустят твою лохань ко дну, ведь правда? Тогда ты можешь замолвить за меня словечко перед генерал-губернатором, что на Гаване, так? Просто скажи ему, что я купил бы каперское свидетельство за десять тысяч золотом, и готов поклясться верно служить ему.";
            link.l1 = "Я сочувствую тебе, Хьюго, но у меня сейчас нет на это времени. До встречи.";
			link.l1.go = "Otkazal";
			link.l2 = "Вообще-то я мог"+ GetSexPhrase("","ла") +" бы сделать это, но, если говорить начистоту, что я с этого буду иметь?";
			link.l2.go = "Ya_Ispania_4";
		break;

		case "Otkazal":
            dialog.text = "Как скажешь, "+ GetSexPhrase("парень","девочка") +". Я найду ещё кого-нибудь для этой работы.";
            link.l1 = "До встречи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Obida";
		break;

		case "Obida":
            dialog.text = "Ха, "+ GetSexPhrase("приятель","девочка") +", я так не играю. Ты один раз "+ GetSexPhrase("отказался","отказалась") +" мне помочь, и второго шанса я тебе не предоставлю.";
            link.l1 = "Это твои проблемы, капитан. Тогда счастливо.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Obida";
		break;

		case "Ya_Ispania_4":
            dialog.text = "Деньги, ясное дело! Я могу заплатить тебе 8000 золотом. Что скажешь?";
            link.l1 = "Это меня устраивает. Я соглас"+ GetSexPhrase("ен","на") +". Я принесу тебе испанское каперское свидетельство в обмен на золото.";
			link.l1.go = "Ya_Ispania_5";
			link.l2 = "Ты, должно быть, шутишь. 8000 золотых за такое сложное и опасное дело? Не пойдёт.";
			link.l2.go = "Otkazal";
		break;

		case "Ya_Ispania_5":
            dialog.text = "Вот добрый человек! Попутного ветра тебе, капитан. Я могу подождать тебя здесь только пару месяцев. Если ты к тому времени не вернёшься, то, наверное, я уже буду болтаться на французской или английской виселице.";
            link.l1 = "До встречи.";
			link.l1.go = "Havana_Cod_1";
			NextDiag.TempNode = "Jugo_PodhodimSnova";
		break;

		case "Jugo_PodhodimSnova":
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
            dialog.text = "Так, "+pchar.name+" - и где же это каперское свидетельство, которое ты обещал"+ GetSexPhrase("","а") +" принести мне?";
            link.l1 = "Прости меня, Хьюго, но у меня ещё его нет.";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Patent") && pchar.questTemp.PDM_Novaya_Rodina.Patent == "Patent")
			{
				link.l2 = "О да, всё получилось! Дон Франсиско сказал, что приглашает тебя посетить его в его резиденции как можно скорее - вместе с твоими десятью тысячами, конечно. И теперь, я полагаю, ты и мне также должен 8000?";
				link.l2.go = "Ya_Ispania_Patent_1";
			}
		break;

		case "Havana_Cod_1":
            SetQuestHeader("PDM_Novaya_Rodina");
			AddQuestRecord("PDM_Novaya_Rodina", "1");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.PDM_Novaya_Rodina.Guber = "HugoLesopilka";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Ya_Ispania_Patent_1":
            dialog.text = "Это потрясающие новости, "+ GetSexPhrase("парень","девочка") +"! Потрясающие! Вот - вот твоё золото, а с ним прими и мою благодарность. Дон Франсиско, ты сказал"+ GetSexPhrase("","а") +"? Я немедленно поверну штурвал в том направлении!";
            link.l1 = "Прощай, Хьюго.";
			link.l1.go = "Ya_Ispania_Patent_Сod_1";
			AddMoneyToCharacter(pchar, 8001);
			TakeItemFromCharacter(pchar, "Patent_Espa_Lesopilka");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;

		case "Ya_Ispania_Patent_Сod_1":
			AddQuestRecord("PDM_Novaya_Rodina", "4");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","а"));
			PChar.quest.PDM_HugoSeaHavana.win_condition.l1 = "EnterToSea"
			Pchar.quest.PDM_HugoSeaHavana.win_condition = "PDM_HugoSeaHavana";
			pchar.questTemp.PDM_Novaya_Rodina.Guber = "Lubopitno";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Podhodim_SNOVA_vipemromu":
            dialog.text = "А, "+ GetSexPhrase("парень","девочка") +"! "+ GetSexPhrase("Вернулся","Вернулась") +" опять, э? Ну, а мне надо идти к дону Франсиско... Ну, после того, как я выпью пару кружек за тебя и мой новый дом, Испанию!";
            link.l1 = "Спасибо на добром слове, Хьюго. Я оставляю тебя праздновать своё назначение.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;

		case "Novoe_Zadanie_1":
			PlayVoice("Kopcapkz\Voices\PDM\Timothy - Town Guard.wav");
            dialog.text = "А, это опять ты, капитан "+pchar.name+"! Рад тебя видеть!";
            link.l1 = "О, старая Лесопилка! И как твоя честная жизнь?";
			link.l1.go = "Novoe_Zadanie_2";
		break;

		case "Novoe_Zadanie_2":
            dialog.text = "Очень хорошо, спасибо. Скажу тебе, что другие испанские капитаны сначала с подозрением ко мне отнеслись, но я показал им пару боевых приёмов, и теперь мы все лучшие друзья.\n"+
							"Ха!  Слушай, "+pchar.name+", в благодарность за то, что ты для меня сделал"+ GetSexPhrase("","а") +", у меня есть для тебе хороший совет. Подойди поближе и слушай.\n"+
							"Я знаю, где ты можешь получить хороший товар, очень хороший товар. Видишь ли, "+pchar.name+", один из моих старых, э-э, приятелей, принадлежащий к пиратам, понимаешь ли... ну, он сказал мне, что английский тяжёлый галеон, набитый золотыми и серебряными слитками, попал в сильный шторм и сейчас чинится рядом с Доминикой.";
            link.l1 = "И что?";
			link.l1.go = "Novoe_Zadanie_3";
		break;

		case "Novoe_Zadanie_3":
            dialog.text = "Что? Ты чего, репой торгуешь, "+pchar.name+"? Да в этом галеоне целое состояние!";
            link.l1 = "А-а. Я понял"+ GetSexPhrase("","а") +". И...?";
			link.l1.go = "Novoe_Zadanie_4";
		break;

		case "Novoe_Zadanie_4":
            dialog.text = "Ну, корабль стоит на якоре рядом с Доминикой - ты его точно знаешь: маленький остров между Гваделупой и Барбадосом. Мой друг сказал, что он видел, как этот галеон чинят после жестокой бури - у него была повреждена оснастка, если так можно назвать полное её отсутствие, и корпус его тоже повреждён. Он сказал, что корабль почти что не может двигаться. Без верфи починка, похоже, займёт некоторое время, так что он там, можно сказать, застрял и ждёт только капитана, который придёт и его захватит.";
            link.l1 = "А почему ты сам его не захватишь?";
			link.l1.go = "Novoe_Zadanie_5";
		break;

		case "Novoe_Zadanie_5":
            dialog.text = "А, ты думаешь, я заманиваю тебя в ловушку, а? Не, "+ GetSexPhrase("парень","девочка") +": у меня корабль не настолько силён, чтобы захватить тяжёлый галеон, да и я слишком стар, чтобы менять корабль. Я на своей 'Фелиции' знаю каждый гвоздь и каждую планку, и не хочу её бросать. Так что, "+ GetSexPhrase("парень","девочка") +", он твой, если ты только пожелаешь взять его!";
            link.l1 = "Хммм. Знаешь ли, я думаю, стоит пойти взглянуть на него. Он стоит на рейде у Доминики, говоришь? Ну, спасибо за совет, Хьюго. До свидания!";
			link.l1.go = "Novoe_Zadanie_Cod_1";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;

		case "Novoe_Zadanie_Cod_1":
			AddQuestRecord("PDM_Novaya_Rodina", "6");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","а"));

			int Rank = sti(pchar.rank) - 3 + MOD_SKILL_ENEMY_RATE;
			if (Rank < 1) Rank = 1;
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Lesopilka_Galeon", "off_eng_1", "man", "man", Rank, ENGLAND, -1, true));
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, "Вкуснятина", CANNON_TYPE_CANNON_LBS32, 20, 20, 50);
			FantomMakeCoolFighter(sld, Rank, 55, 55, "blade22", "pistol2", 120);
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "EnergyPlus");
			sld.equip.blade = "blade22";
			sld.equip.gun = "pistol2";
			AddItems(sld, "bullet", 10);
			AddItems(sld, "GunPowder", 10);
			EquipCharacterByItem(Pchar, "cirass1");
			AddCharacterGoodsSimple(sld, GOOD_GOLD, 800 + rand(400));
			AddCharacterGoodsSimple(sld, GOOD_SILVER, 800 + rand(400));
			AddCharacterGoodsSimple(sld, GOOD_WEAPON, 500);
			SetShipSkill(sld, 100, 80, 80, 80, 80, 80, 80, 80, 80);
			sld.ship.Crew.Morale = 100;
			sld.ship.masts.mast4 = 1;
			sld.ship.masts.mast3 = 1;
			sld.ship.masts.mast1 = 1;
			sld.ship.HP = sti(sld.ship.HP) / 3.5;
			sld.DontRansackCaptain = true;

			Group_FindOrCreateGroup("PDM_HUGO_GAL");
			Group_SetType("PDM_HUGO_GAL", "war");
			Group_AddCharacter("PDM_HUGO_GAL", "PDM_Lesopilka_Galeon");

			Group_SetGroupCommander("PDM_HUGO_GAL", "PDM_Lesopilka_Galeon");
			Group_SetTaskAttack("PDM_HUGO_GAL", PLAYER_GROUP);
			Group_SetAddress("PDM_HUGO_GAL", "Dominica", "quest_ships", "Quest_ship_2");
			Group_LockTask("PDM_HUGO_GAL");

			SetTimerCondition("PDM_Lesopilka_Vremy", 0, 0, 30, false);

			PChar.quest.PDM_Lesopilka_SJ.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_Lesopilka_SJ.win_condition.l1.character = "PDM_Lesopilka_Galeon";
			PChar.quest.PDM_Lesopilka_SJ.win_condition = "PDM_Lesopilka_SJ";

			PChar.quest.PDM_Lesopilka_SJNashel.win_condition.l1 = "item";
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition.l1.item = "PDM_SJ_Angl_Gal";
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition = "PDM_Lesopilka_SJNashel";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Novoe_Zadanie_PodhodimSnova_1":
            dialog.text = "А! Не желаешь ли выпить со мной, "+pchar.name+"?";
            link.l1 = "Не сейчас, Хьюго. Но спасибо!";
			link.l1.go = "Novoe_Zadanie_PodhodimSnova_2";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
		break;

		case "Novoe_Zadanie_PodhodimSnova_2":
            dialog.text = "Тогда чего же ты тратишь тут время, "+ GetSexPhrase("парень","девочка") +"? Иди и возьми этот галеон, пока он не уплыл!";
            link.l1 = "Ты прав, Хьюго. Я ухожу. Прощай!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;

		case "Novoe_Zadanie_ZaIspaniu":
            dialog.text = LinkRandPhrase("За короля!", "За Испанию!", "За нашего капитана!");
            link.l1 = LinkRandPhrase("Так держать, солдат!", "Молодец!", "Умница!");
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_ZaIspaniu";
		break;

		case "Final_1":
            dialog.text = "Ха, "+ GetSexPhrase("парень","девочка")+", я знал, что у тебя всё получится!";
            link.l1 = "Спасибо, Хьюго. Все эти сокровища я заполучил"+ GetSexPhrase("","а")+" только благодаря тебе.";
			link.l1.go = "Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\William Shakesbeer.wav");
		break;

		case "Final_2":
			dialog.text = "";
			if (sti(pchar.Money) >= 30000)
			{
				link.l1 = "И я подумал"+ GetSexPhrase("","а")+", что ты заслужил эти 30000 золотых.";
				link.l1.go = "Final_3";
				link.l2 = "Ладно, Хьюго, у меня есть дела. До встречи.";
				link.l2.go = "FinalPL_3";
				NextDiag.TempNode = "Final_Again";
			}
			else
			{
				link.l2 = "Ладно, Хьюго, у меня есть дела. До встречи.";
				link.l2.go = "FinalPL_3";
				NextDiag.TempNode = "Final_Again";
			}
		break;

		case "Final_3":
            dialog.text = "О-о-о! "+ GetSexPhrase("Парень","Девочка")+", ты очень добр"+ GetSexPhrase("","а")+" ко мне, конечно я возьму эти деньги! Может, пойдём выпьем?";
            link.l1 = "Извини, Хьюго, у меня есть незаконченные дела, может быть в другой раз. Адиос!";
			link.l1.go = "Final_4";
			ChangeCharacterReputation(pchar, 5);
			NextDiag.TempNode = "Final_Again";
			AddMoneyToCharacter(pchar, -30000);
			AddCharacterExpToSkill(pchar, "Leadership", 70);
			AddCharacterExpToSkill(pchar, "Commerce", 70);
			AddCharacterExpToSkill(pchar, "Fortune", 70);
		break;

		case "Final_4":
			CloseQuestHeader("PDM_Novaya_Rodina");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FinalPL_3":
			CloseQuestHeader("PDM_Novaya_Rodina");
            sld = CharacterFromID("Hugo_Lesopilka")
			sld.lifeday = 0;
			ChangeCharacterReputation(pchar, -5);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Final_Again":
            dialog.text = "А! Не желаешь ли выпить со мной, "+pchar.name+"?";
            link.l1 = "Извини, Хьюго, у меня есть незаконченные дела, может быть в другой раз. Адиос!";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\William Shakesbeer.wav");
			NextDiag.TempNode = "Final_Again";
		break;


	}
}
