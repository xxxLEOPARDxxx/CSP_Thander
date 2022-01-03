
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int i, iOfficer;
	string attrL, offtype;
	ref chref;

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "OfficerConfusedSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToHealConfuse = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "OfficerConfused";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "(мужчина лежит, весь испачканный в крови с полуоткрытыми глазами, и стонет) М-м-м... А-а-х... У-у-у...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.PDM_Apt_Markus_v_krovi = "PDM_Apt_Markus_v_krovi";
			NextDiag.TempNode = "Markus_v_krovi";

			SetQuestHeader("PDM_Aptekar");
			AddQuestRecord("PDM_Aptekar", "1");
		break;

		case "Markus_v_krovi":
			dialog.text = LinkRandPhrase("М-м-м...", "О-о-о-х...", "А-а-х...");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "Alumnus_FT":
			dialog.text = "Приветствую вас, я доктор алхимии и медицины. Моё имя Алюмнус. А как зовут вас, "+ GetSexPhrase("молодой человек","девушка") +"?";
			link.l1 = "Можете звать меня "+pchar.name+", капитан "+pchar.name+". Доктор Алюмнус, я слышал"+ GetSexPhrase("","а") +", что вам удалось излечить дочь губернатора, когда все другие доктора отказались лечить её. Так ли это?";
			link.l1.go = "Alumnus_1";
		break;

		case "Alumnus_1":
			dialog.text = "О, да. Поистине невероятный случай. Бедная девочка страдала анемией. Теперь из трудов Главка и Эфистиуса нам известно, что причиной анемии является подавление элементов воздуха и земли элементами огня и воды. С другой стороны Хоррок утверждает, что анемия происходит не от дисбаланса элементов, а от зарождения злокачественного гомункула в желчном пузыре больного. В то же время древние считали, что анемия происходит от влияния Плутона на созвездие, под которым был рождён пациент...";
			link.l1 = "Гм. Прошу прощения, доктор, но у меня нет времени выслушивать ваши, несомненно, высоконаучные рассуждения. Человек при смерти. Ему пришлось провести две недели в маленькой лодке почти без воды и пищи. Он не приходит в сознание и его кожа жёлтого цвета. Что я долж"+ GetSexPhrase("ен","на") +" сделать с ним?";
			link.l1.go = "Alumnus_2";
		break;

		case "Alumnus_2":
			dialog.text = "О, интересный случай. Этот человек просто страдает от глобального дисбаланса своих составляющих. Ему не хватает воды и земли - еда, несомненно, это субстанция, имеющая земное происхождение - пациента лихорадит, что указывает на присутствие в крови слишком большого количества элемента огня. Цвет его кожи происходит от скопившейся под ней желчи. Полкес отмечает, что в Праге он наблюдал пациента с кожей, цветом подобной жёлтому нарциссу. Поразительно!";
			link.l1 = "У меня нет времени на научные объяснения. Скажешь ты мне, что я долж"+ GetSexPhrase("ен","на") +" сделать, чтобы спасти этого человека, или мне придётся вытрясти это из тебя?";
			link.l1.go = "Alumnus_3";
		break;

		case "Alumnus_3":
			dialog.text = "Фу, как вы грубы, "+ GetSexPhrase("молодой человек","девушка") +"! Вам следует уважать тех, кто старше и учёнее вас. Вам стоит кое-чему поучиться, хотя я сомневаюсь, что вы на это способны. Вот, возьмите это средство. Растворите порошок в воде и давайте вашему пациенту три раза в день. Если он не в состоянии пить, то вы должны смазывать ему губы этой микстурой. В течение недели или около того, с Божьего благословения, он должен прийти в себя. Теперь, до свидания, "+ GetSexPhrase("молодой человек","девушка") +".";
			link.l1 = "До свидания, доктор Алюмнус. И спасибо вам.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_4";

			sld = CharacterFromID("PDM_Markus")
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Markus_Dat_Lekarstvo";
			pchar.questTemp.PDM_Apt_Markus_lekarstvo = "PDM_Apt_Markus_lekarstvo";

			GiveItem2Character(PChar, "PDM_Heal_Poroshok");
			AddQuestRecord("PDM_Aptekar", "3");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("ся","ась"));
		break;

		case "Alumnus_4":
			dialog.text = LinkRandPhrase("Я ведь дал вам всё, что вам было необходимо! Попрошу больше не отвлекать меня от моих размышлений.", "...но здесь элемент огня представлен ароматом корицы, чьё доминирование уравновешивается запахом... Нет, пожалуйста, не мешайте мне! Я нахожусь на самом важном этапе своей работы.", "Я ведь дал вам всё, что вам было необходимо! Попрошу больше не отвлекать меня от моих размышлений.", "...но здесь элемент огня представлен ароматом корицы, чьё доминирование уравновешивается запахом... Нет, пожалуйста, не мешайте мне! Я нахожусь на самом важном этапе своей работы.");
			link.l1 = "Извините, доктор. Я ухожу.";
			link.l1.go = "exit";
		break;

		case "Markus_Dat_Lekarstvo":
			dialog.text = "";
			link.l1 = "(вы растворяете порошок в воде и даёте Маркусу выпить из кружки)";
			link.l1.go = "Markus_Dat_Lekarstvo_2";
		break;

		case "Markus_Dat_Lekarstvo_2":
			dialog.text = "(осушив содержимое, Маркус на несколько секунд сделался бодрее... а затем улёгся на кровать и заснул)";
			link.l1 = "(следует рассказать тавернщику о том, что вы только что увидели)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Markus_lekarstvo");
			pchar.questTemp.PDM_Apt_Rasskazat_Tavern = "PDM_Apt_Rasskazat_Tavern";
			NextDiag.TempNode = "Markus_Dat_Lekarstvo_3";
		break;

		case "Markus_Dat_Lekarstvo_3":
			dialog.text = "(спит)";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Markus_Dat_Lekarstvo_3";
		break;

		case "Markus_Vizdorovel":
			sld = CharacterFromID("SentJons_tavernkeeper")
			dialog.text = "Ах, вы должно быть, капитан "+pchar.name+"! Я должен поблагодарить вас за моё исцеление. "+sld.name+" рассказал мне обо всём, что вы для меня сделали.";
			link.l1 = "Я рад"+ GetSexPhrase("","а") +", что ты поправился, и теперь ты расскажешь, что же с тобой случилось. "+sld.name+" сказал, что Ропфлейк захватил твой корабль.";
			link.l1.go = "Markus_Vizdorovel_2";
			AddCharacterSkillDontClearExp(pchar, "Leadership", 1);
			AddCharacterSkillDontClearExp(pchar, "Defence", 1);
			Log_SetStringToLog("Авторитет + 1");
			Log_SetStringToLog("Защита + 1");
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Vizdorovel");
		break;

		case "Markus_Vizdorovel_2":
			dialog.text = "Да, это правда. Ропфлейк действительно очень опасен, недаром его так боятся торговцы. У этого негодяя хороший, манёвренный корабль и неплохие канониры. Когда я напоролся на этих ублюдков, первым же залпом, первым же! Они снесли мой бушприт ко всем чертям. В основном Ропфлейк ловит корабли при выходе из Сент-Джонса, так что будьте осторожны, капитан.";
			link.l1 = "Спасибо за предостережение, Маркус, я буду осторож"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "Markus_Vizdorovel_3";
		break;

		case "Markus_Vizdorovel_3":
			dialog.text = "И вот ещё что. Возьмите эти деньги и передайте их доктору, поблагодарите его от меня.";
			link.l1 = "Хорошо, я как раз собирал"+ GetSexPhrase("ся","ась") +" навестить Алюмнуса.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddMoneyToCharacter(pchar, 5000);

			sld = GetCharacter(NPC_GenerateCharacter("Ropfleik", "officer_58", "man", "man", sti(PChar.rank) + 6, PIRATE, 15, false));
			SetShipHunter(sld);
			sld.name = "Ропфлейк";
			sld.lastname = "";
			SetFantomParamHunter(sld);
			SetCaptanModelByEncType(sld, "war");
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.Name = "тот самый Ропфлейк";
			sld.hunter = "pirate";
			Group_AddCharacter("Ropf_Ship", "Ropfleik");

			Group_SetGroupCommander("Ropf_Ship", "Ropfleik");
			Group_SetTaskAttackInMap("Ropf_Ship", PLAYER_GROUP);
			Group_LockTask("Ropf_Ship");
			Map_CreateFastWarrior("", "Ropfleik", 30);

			sld = CharacterFromID("Doktor_Alumnus")
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_Novoe_Zadanie";

			AddQuestRecord("PDM_Aptekar", "5");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("ёс","есла"));
		break;

		case "Alumnus_Novoe_Zadanie":
			dialog.text = "А-а, это вы, "+ GetSexPhrase("мой юный и нетерпеливый капитан","моя юная и нетерпеливая знакомая") +"! Что вам угодно от меня?";
			link.l1 = "Хотел"+ GetSexPhrase("","а") +" поблагодарить вас, доктор. Вы и вправду творите чудеса. Тот порошок, что вы мне дали, поставил на ноги моего друга. И я вернул"+ GetSexPhrase("ся","ась") +", чтобы выразить вам свою глубочайшую признательность.";
			link.l1.go = "Alumnus_Novoe_Zadanie_2";
			AddMoneyToCharacter(pchar, -5000);
		break;

		case "Alumnus_Novoe_Zadanie_2":
			dialog.text = "Великолепно, я очень рад, что я помог человеку в нужде. Спасибо, капитан, вы не так уж неотесанны, как мне показалось в первый раз\nНо скажите мне, достаточно ли далеко простирается ваша благодарность, чтобы я мог попросить вас об одной услуге? Мне необходимо небольшое количество одной редкой травы, что произрастает на карибских островах. Без неё я не могу готовить свои чудодейственные целебные отвары. Если бы вы достали для меня эту траву, я бы мог лечить вас и ваших офицеров от любых ранений и болезней. Однажды я приобрёл немного этой травы у... Как же его звали? Ах да, у Пабло Локо.";
			link.l1 = "Я в долгу у вас, доктор. Расскажите мне об этом Пабло Локо - очень странное имя.";
			link.l1.go = "Alumnus_Novoe_Zadanie_3";
		break;

		case "Alumnus_Novoe_Zadanie_3":
			dialog.text = "Он и вправду немножко... странный, и поэтому его зовут 'Локо'. На своей лодочке он плавает от одного острова к другому, собирая разные редкие травы и снадобья, и потом продаёт их докторам, аптекарям и повивальным бабкам. Но мне кажется, что он умный человек, несмотря на его привычки - он дал мне пару очень полезных советов насчёт местных болезней и психологии индейцев. Он живёт обособленно от людей, и в последний раз его видели где-то на Эспаньоле. Так как у него есть лодка, то живёт он где-то недалеко от моря.";
			link.l1 = "Я привезу вам эту травку. А как она называется?";
			link.l1.go = "Alumnus_Novoe_Zadanie_4";
		break;

		case "Alumnus_Novoe_Zadanie_4":
			dialog.text = "А-а. Вот здесь небольшая проблема. Я не могу в точности припомнить её название. Я уверен, что Локо называл мне эту траву при продаже, но я просто забыл название, оно звучит крайне странно для слуха европейца, знаете ли.";
			link.l1 = "И как же я долж"+ GetSexPhrase("ен","на") +" искать эту траву, когда не знаю, как она называется?";
			link.l1.go = "Alumnus_Novoe_Zadanie_5";
		break;

		case "Alumnus_Novoe_Zadanie_5":
			dialog.text = "Ну, я скажу вам, как опознать эту траву. Её запах напоминает одновременно запахи корицы и аниса. Достаточно пахучая смесь, надо сказать. Я думаю, что это происходит из-за влияния Нептуна и Европы на процесс созревания этой травы. Гинденбург написал целый труд о влиянии внешних планет на созревание трав в период весеннего равноденствия. Впрочем, я отвлекаюсь.";
			link.l1 = "Да, вы отвлекаетесь. Спасибо за лекцию. Я постараюсь найти для вас эту траву. До встречи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Novoe_Zadanie_6";

			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco", "indsar1", "man", "man", 10, PIRATE, -1, false));
			sld.name = "Пабло";
			sld.lastname = "Локо";
			sld.greeting = "GR_Pablo_Loco";
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetCitizenType(sld);
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Pablo_Loco_FT";
			ChangeCharacterAddressGroup(sld,"Shore34","goto","goto1");

			AddQuestRecord("PDM_Aptekar", "6");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","а"));
		break;

		case "Alumnus_Novoe_Zadanie_6":
			dialog.text = "Добро пожаловать назад! Удалось ли вам найти необходимое мне растение?";
			link.l1 = "Ещё нет, доктор. Продолжаю поиски.";
			link.l1.go = "exit";
			link.l2 = "Доктор, напомните мне, как опознать эту траву.";
			link.l2.go = "Alumnus_Novoe_Kak_Opoznat";
			NextDiag.TempNode = "Alumnus_Novoe_Zadanie_6";
		break;

		case "Alumnus_Novoe_Kak_Opoznat":
			dialog.text = "Запоминайте: эта редкая трава произрастает на карибских островах, её запах напоминает одновременно корицы и аниса. Я думаю, что это происходит из-за влияния Нептуна и Европы на процесс созревания этой травы. Гинденбург написал целый труд о влиянии внешних планет на созревание трав в период весеннего равноденствия...";
			link.l1 = "Ладно, доктор, этого достаточно, я побежал"+ GetSexPhrase("","а") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Novoe_Zadanie_6";
		break;

		case "Pablo_Loco_FT":
			dialog.text = "А! Ты желаешь золота, да? Ты желаешь много золота. Слеп"+ GetSexPhrase("ой дурак","ая дура") +"! Неужели ты не заботишься о состоянии своей души?";
			link.l1 = "О чём ты говоришь? Кто ты?";
			link.l1.go = "Pablo_Loco_1";
			//link.l1.go = "Pablo_Loco_8";
			NextDiag.TempNode = "Pablo_Loco_ER_1";
		break;

		case "Pablo_Loco_ER_1":
			dialog.text = "Ты выбросил"+ GetSexPhrase("","а") +" свою жадность в море?";
			link.l1 = "О чём ты говоришь?";
			link.l1.go = "Pablo_Loco_ER_2";
		break;

		case "Pablo_Loco_ER_2":
			dialog.text = "Жадность делает твоё сердце тяжелым, как само золото. Ты долж"+ GetSexPhrase("ен","на") +" выбросить её в море, чтобы очиститься.";
			link.l1 = "Расскажи мне свою историю.";
			link.l1.go = "Pablo_Loco_2";
		break;

		case "Pablo_Loco_1":
			dialog.text = "Я Пабло. Тот, чьи уши тоскуют по птичьему пению и голосам братьев, но слышат лишь вопли и крики. Тот, чей нос тоскует по благоуханию цветов и солёного моря, но чувствует лишь горький чёрный порох.";
			link.l1 = "Ты, несомненно, несчастный человек. Расскажи мне свою историю.";
			link.l1.go = "Pablo_Loco_2";
			link.l2 = "Твой разум явно вышел погулять, а у меня везде есть неотложные дела. До свидания.";
			link.l2.go = "exit";
		break;

		case "Pablo_Loco_2":
			dialog.text = "Я жил в Иначетле. Я был найден в лодке, дрейфующей в океане, малое дитя, живое среди множества мертвецов. Я вырос сильным. Я чувствовал дух этого острова, и я чувствовал дух моря. Мои братья рыбачили в море на маленьких лодках. Они черпали жизнь из моря. Но потом море принесло им смерть.";
			link.l1 = "Что ты имеешь в виду?";
			link.l1.go = "Pablo_Loco_3";
		break;

		case "Pablo_Loco_3":
			dialog.text = "Однажды мои братья увидели огромные корабли на море. Они никогда не видели таких больших кораблей, и они подумали, что это огромные крылатые птицы, посланные богами. Они направились к этим кораблям, крича и размахивая своими острогами в радостном приветствии. Но это не были корабли богов. Это были корабли белых людей. Бледнолицые испугались моих братьев и подумали, что на них нападают. Так что они убили моих братьев, а потом пошли в мою деревню и убили всех, кто был там - всех, кроме меня, снова оставшегося живым среди мертвецов. Так что теперь я остался единственным, кто чувствует дух острова и моря. Вот моя история.";
			link.l1 = "Я скорблю о твоей потере.";
			link.l1.go = "Pablo_Loco_4";
		break;

		case "Pablo_Loco_4":
			dialog.text = "";
			link.l1 = "Расскажи мне ещё о своем народе.";
			link.l1.go = "Pablo_Loco_Plemya_Ushlo";
			link.l2 = "Это ты Пабло, травник?";
			link.l2.go = "Pablo_Loco_Trava";
		break;

		case "Pablo_Loco_Plemya_Ushlo":
			dialog.text = "Моё племя ушло. Я не хочу говорить об этом.";
			link.l1 = "Это ты Пабло, травник?";
			link.l1.go = "Pablo_Loco_Trava";
		break;

		case "Pablo_Loco_Trava":
			dialog.text = "Да, это я. Они называют меня 'Пабло Локо' - сумасшедшим, то есть. Они думают, что я сумасшедший, потому что я чувствую духи природы: зов моря, шёпот семян, смех цветов. Пабло Локо: вот кто я такой.";
			link.l1 = "Действительно. 'Смех цветов', а? Это, э-э, очень всё интересно. Ну, Пабло, мне нужна трава, которая пахнет, как...";
			link.l1.go = "Pablo_Loco_5";
		break;

		case "Pablo_Loco_5":
			dialog.text = "Какой запах у этой травы?";
			Link.l1.edit = 1;
			Link.l1 = "";
			link.l1.go = "Pablo_Loco_Pravilno";
			NextDiag.TempNode = "Pablo_Loco_5";
		break;

		case "Pablo_Loco_Pravilno":
			if ("корицы и аниса" == GetStrSmallRegister(dialogEditStrings[1]) || "корица и анис" == GetStrSmallRegister(dialogEditStrings[1]) || "запах корицы и аниса" == GetStrSmallRegister(dialogEditStrings[1]) || "запахи корицы и аниса" == GetStrSmallRegister(dialogEditStrings[1]) || "анис и корица" == GetStrSmallRegister(dialogEditStrings[1]) || "аниса и корицы" == GetStrSmallRegister(dialogEditStrings[1]) || "запах аниса и корицы" == GetStrSmallRegister(dialogEditStrings[1]) || "запахи аниса и корицы" == GetStrSmallRegister(dialogEditStrings[1]))
			{
				Dialog.text = "Пахнет корицей и анисом? Я знаю такую траву. Она может лечить, а может убить. Скажи мне, зачем тебе нужна эта трава?";
				Link.l1 = "Доктор Алюмнус послал меня за ней.";
				Link.l1.go = "Pablo_Loco_6";
				break;
			}
			else
			{
				Dialog.text = "Не знаю такой травы с таким запахом.";
				{
					Link.l1 = "Щас ещё раз попробую.";
					Link.l1.go = "Pablo_Loco_5";
				}
				link.l2 = "Мне надо подумать.";
				link.l2.go = "exit";
			}
		break;

		case "Pablo_Loco_6":
			dialog.text = "Так, Алюмнус, ты сказал"+ GetSexPhrase("","а") +"? Я знаю этого человека - мудрый дурак. Это опасно, давать тзескатлат умтат в руки 'человека знания'. Но я знаю, что он не будет использовать траву, чтобы намеренно убить другого - это не тот человек. Очень хорошо. Чтобы найти эту траву, мне нужна лодка, потому что я должен плыть туда, где она растёт. Травы не растут все в одном месте, капитан.";
			link.l1 = "Я куплю её тебе.";
			link.l1.go = "Pablo_Loco_7";
		break;

		case "Pablo_Loco_7":
			dialog.text = "Нет, нет! Лодку нельзя 'покупать'! Золотая зараза испортит дух лодки! Ты должен построить лодку своими собственными руками и своим собственным сердцем, а не заражать её золотым ядом!";
			link.l1 = "Ты трудный человек, Пабло, ты знаешь об этом? Ну ладно: что я долж"+ GetSexPhrase("ен","на") +" сделать, чтобы помочь тебе построить лодку?";
			link.l1.go = "Pablo_Loco_8";
		break;

		case "Pablo_Loco_8":
			dialog.text = "Мне нужно особенное дерево. Это дерево называется Тешкатали. Если ты хочешь, чтобы я достал для тебя твою траву, ты долж"+ GetSexPhrase("ен","на") +" доставить мне дерево Тешкатали. Оно растёт на континенте в джунглях, рядом с лагуной Каратаска.";
			link.l1 = "Дерево Тешкатали? Я понял"+ GetSexPhrase("","а") +" и не забуду. До свидания, Пабло. Я вернусь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";

			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1 = "location";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1.location = "Shore10";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition = "PDM_Apt_Prihov_v_buhtu";

			AddQuestRecord("PDM_Aptekar", "7");
		break;

		case "Pablo_Loco_9":
			dialog.text = "Зачем ты докучаешь мне? Единственное, что мне нужно от тебя, это дерево Тешкатали. Когда ты привезёшь его мне, я построю себе новую лодку. И тогда ты получишь тзескатлат умтат. Это всё, что я могу сказать.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +". До свидания.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";
		break;

		case "Nashel_Derevo":
			dialog.text = "Ты опять? Ты доставил"+ GetSexPhrase("","а") +" дерево Тешкатали?";
			link.l1 = "У меня есть дерево, которое тебе нужно. Вот оно. Теперь давай, строй свою лодку, чтобы ты мог привезти мне мою тзеска... тла.. ла... мумат... или как там называется эта чёртова травка.";
			link.l1.go = "Nashel_Derevo_2";
		break;

		case "Nashel_Derevo_2":
			TakeItemFromCharacter(pchar, "PDM_Derevo_Teshkali");
			dialog.text = "Приходи через неделю, в это время нужная тебе трава будет уже у меня.";
			link.l1 = "Давай я позову своих матросов, вместе с ними ты сделаешь лодку в пять раз быстрее.";
			link.l1.go = "Nashel_Derevo_3";
		break;

		case "Nashel_Derevo_3":
			dialog.text = "(смотрит на вас сердитым взглядом)";
			link.l1 = "Ладно, ладно, не буду мешать. Увидимся через неделю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";

			SetTimerCondition("PDM_Apt_Lodka_Postroena", 0, 0, 7, false);

			AddQuestRecord("PDM_Aptekar", "10");
		break;

		case "Pablo_Loco_Stroit_lodku":
			dialog.text = "Лодка ещё не готова, приходи позже.";
			link.l1 = "Хорошо, Пабло, делай как умеешь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";
		break;

		case "Pablo_Loco_Lodka_Postroena":
			dialog.text = "Белый человек, я нашёл твою траву.";
			link.l1 = "Благодарю, Пабло Локо. Не волнуйся, эта трава не принесёт смерть, а будет служить медицине. Прощай.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;

			AddCharacterSkill(pchar, "Sailing", 1);
			AddCharacterSkill(pchar, "Repair", 1);
			Log_SetStringToLog("Навигация + 1");
			Log_SetStringToLog("Ремонт + 1");

			GiveItem2Character(PChar, "PDM_Trava_Tzes_Umrat");
			AddQuestRecord("PDM_Aptekar", "11");

			sld = CharacterFromID("Doktor_Alumnus")
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_Finish_Zadanie";
		break;

		case "Alumnus_Finish_Zadanie":
			dialog.text = "Вы вернулись. Потрясающе. Вы принесли мне траву, что я у вас просил, "+ GetSexPhrase("мой юный капитан","минфрау") +"?";
			link.l1 = "Тзескатлат Умтат?";
			link.l1.go = "Alumnus_Finish_Zadanie_2";
		break;

		case "Alumnus_Finish_Zadanie_2":
			dialog.text = "Простите, что?";
			link.l1 = "Вот она.";
			link.l1.go = "Alumnus_Finish_Zadanie_3";
		break;

		case "Alumnus_Finish_Zadanie_3":
			dialog.text = "А-а! Вы принесли её! Какая удача! Я смогу теперь готовить свои целебные отвары, а также продолжить одно незаконченное исследование!";
			link.l1 = "Скажите, доктор, если это не секрет - зачем вам эта вонючая трава?";
			link.l1.go = "A_pravda_ZACHEM???";
			TakeItemFromCharacter(pchar, "PDM_Trava_Tzes_Umrat");
		break;

		case "A_pravda_ZACHEM???":
			dialog.text = "Видите ли, "+ GetSexPhrase("мой юный капитан","сударыня") +", я собираюсь разрешить главную загадку натуральной философии - секрет бессмертия! С помощью этой травки я намереваюсь создать зелье, которое позволит мне жить вечно!";
			link.l1 = "Ясно. Ладно, если после того, как вы проглотите это зелье, вы вдруг обнаружите, что от вас отскакивают ядра - сообщите мне, пожалуйста.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Lechenie_s_voprosom";

			CloseQuestHeader("PDM_Aptekar");
		break;

		case "Alumnus_Lechenie_s_voprosom":	//Для Грегга
			dialog.text = "...но здесь элемент огня представлен ароматом корицы, чьё доминирование уравновешивается запахом... Капитан, это снова вы, чем я могу быть вам полезен?";
			link.l1 = "Здравствуйте, доктор Алюмнус, я бы хотел"+ GetSexPhrase("","а") +", чтобы вы осмотрели моих раненных офицеров.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Чего это у вас закрыта дверь с улицы? Клиентов упускаете.";
			link.l2.go = "Alumnus_Lechenie_s_voprosom_2";
			link.l3 = "Решил"+ GetSexPhrase("","а") +" проведать вас. До свидания.";
			link.l3.go = "exit";	//Для выхода
			if(CheckAttribute(PChar,"Luke.BadPoison"))
			{
				link.l4 = "Доктор, мне очень нужна ваша помощь, меня отравили очень сильным ядом!";
				link.l4.go = "LukePoison";
			}
		break;

		case "Alumnus_Lechenie_s_voprosom_2":
			dialog.text = "Понимаете ли, мой дом расположен аккурат между доками и таверной, если я держу дверь открытой, сюда постоянно наведываются случайные посетители, которые так и норовят опрокинуть одну из моих настоек. Одного такого 'гостя' мне потом пришлось приводить в чувства целую неделю, а недостатка в клиентах я никак не испытываю, эту лавку в городе знают все местные, от губернатора до портового грузчика.";
			link.l1 = "Ладно, я понял"+ GetSexPhrase("","а") +". Вы можете осмотреть моих раненных офицеров?";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Это было очень интересно. До свидания.";
			link.l2.go = "exit";

			NextDiag.TempNode = "Alumnus_Lechenie";
		break;

		case "Alumnus_Lechenie":
			dialog.text = "...но здесь элемент огня представлен ароматом корицы, чьё доминирование уравновешивается запахом... Капитан, это снова вы, чем я могу быть вам полезен?";
			link.l1 = "Здравствуйте, доктор Алюмнус, я бы хотел"+ GetSexPhrase("","а") +", чтобы вы осмотрели моих раненных офицеров.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Решил"+ GetSexPhrase("","а") +" проведать вас. До свидания.";
			link.l2.go = "exit";
			if(CheckAttribute(PChar,"Luke.BadPoison"))
			{
				link.l3 = "Доктор, мне очень нужна ваша помощь, меня отравили очень сильным ядом!";
				link.l3.go = "LukePoison";
			}
		break;

		case "CheckForConfuse":
			dialog.text = "Кому именно требуется медицинская помощь, капитан?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (!GetRemovable(sld)) continue;
				if (!CheckAttribute(sld, "HPminusDaysNeedtoRestore") || CheckAttribute(sld, "Doctored")) continue;
				attrL = "l"+i;
				Link.(attrL)	= "Офицер " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerConfusedSel_" + i;
			}
			Link.l99 = "В данный момент никому.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));

			if (!CheckAttribute(chref,"quest.officertype")) offtype = "Универсал";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "Вы имеете в виду "+GetFullName(chref)+", специализация - "+offtype+".";
			Link.l1 = "Да, именно.";
			Link.l1.go = "OfficerConfused_2";
			Link.l99 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused_2":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			if (CheckAttribute(chref,"chr_ai.max_hp")) npchar.HealPrice = (makeint(chref.chr_ai.max_hp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE/2));
			else npchar.HealPrice = (makeint(chref.health.maxhp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE/2));
			dialog.Text = "По прогнозам, этому офицеру до полного излечения естественным путём ещё дней так..."+(sti(chref.HPminusDaysNeedtoRestore)-sti(chref.HPminusDays))+". Я мог бы попробовать ускорить процесс выздоровления, но это обойдётся вам в... "+FindRussianMoneyString(sti(npchar.HealPrice));
			if (sti(pchar.money)>=sti(npchar.HealPrice))
			{
				Link.l1 = "Хорошо, я гото"+ GetSexPhrase("в","ва")+" заплатить.";
				Link.l1.go = "OfficerConfused_3";
			}
			Link.l99 = "Пожалуй нет, я пока несколько стесн"+ GetSexPhrase("ён","ена") +" в средствах.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused_3":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			AddMoneyToCharacter(pchar,-sti(npchar.HealPrice));
			LAi_Fade("", "");
			WaitDate("",0,0,0, 0, 60);
			int plusdays = makeint(sti(chref.HPminusDaysNeedtoRestore)/4*3);
			if (plusdays > 30) plusdays = 39;
			chref.HPminusDays = sti(chref.HPminusDays) + plusdays;
			if(sti(chref.HPminusDays) >= sti(chref.HPminusDaysNeedtoRestore))
			{
				DeleteAttribute(chref, "HPminusDays");
				DeleteAttribute(chref, "HPminusDaysNeedtoRestore");
				Log_Info("Офицер " + GetFullName(chref) + " выздоровел.");
				dialog.Text = "Мне удалось полностью исцелить " + GetFullName(chref) + ". Хотя надо признать, что это было весьма непросто...  У вас всё или кому-то ещё требуется моя помощь?";
			}
			else
			{
				chref.Doctored = true;
				dialog.Text = "Я сделал всё, на что я способен. Скорее всего уже в ближайшие дни " + GetFullName(chref) + " будет в полном порядке. У вас всё или кому-то ещё требуется моя помощь?";
			}
			Link.l1 = "Нет, есть ещё нуждающиеся.";
			Link.l1.go = "CheckForConfuse";
			Link.l99 = "Пока всё. Благодарю вас за помощь.";
			Link.l99.go = "exit";
		break;

		case "LukePoison":
			dialog.text = "Капитан, дайте мне вас осмотреть... Да, этот яд был приготовлен из очень редких и вредоносных трав! Но не волнуйтесь, я знаю, как это лечить. А сейчас, "+pchar.name+", ложитесь в кровать, я скоро вами займусь.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("HealingPoison");
		break;
	}
}
