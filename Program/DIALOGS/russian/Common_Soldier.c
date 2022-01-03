// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	int bribe_price = sti(PChar.rank) * (500) * (0.01 * (160 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));

	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
            NextDiag.TempNode = "First time";
			// заглушка на нежить
			if (pchar.sex == "Skeleton" && GetCharacterEquipSuitID(pchar)!= "suit_1")
			{
				dialog.text = RandPhraseSimple("Живые мертвецы в городе?! К оружию!!!", "Сгинь, нечистая сила!!!");
				link.l1 = "За эту дерзость я заберу твою дущу, глупец!";
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Пираты в городе?! Ну дела... Хватай е"+ GetSexPhrase("го","е") +"!!", "Это пират!! Держи е"+ GetSexPhrase("го","е") +"!!!");
					link.l1 = RandPhraseSimple("Пират, ну и что?..", "Хех, попробуйте схватить.");
					link.l1.go = "fight";
					break;
				}
				dialog.text = RandPhraseSimple("Шпион? Сдать оружие!! Следовать за мной!", "Вражеский агент!! Немедленно схватить е"+ GetSexPhrase("го","е") +"!");
				link.l1 = RandPhraseSimple("Заткнись, малахольный!", "Как бы не так!");
				link.l1.go = "fight";
				// ==> eddy. Засада, если опознали в инквизиции.
				if (Pchar.location == "Santiago_Incquisitio") StartIncquisitioAttack();
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Кто ты и что тебе здесь нужно?", "Стой! Кто ты? На каком основании пытаешься войти в город?");
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = "Офицер, у меня имеется " + GetRusNameNationLicence(sti(npchar.nation)) + ", так что, я нахожусь здесь на законных основаниях. Прошу ознакомиться...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Ты что, не видишь, как на моем корабле развевается флаг " + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l2 = "Я бросил"+ GetSexPhrase("","а") +" якорь у " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " под флагом " + NationNameGenitive(sti(pchar.nation)) + ". Что тебе еще не ясно?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Пираты в городе?! Ну дела... Хватай его!!", "Это пират!! Держи его!!!");
							link.l1 = RandPhraseSimple("Да, пират, ну и что?..", "Хех, попробуйте схватить...");
							link.l1.go = "fight";
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Ты что, не видишь, как на моем корабле развевается флаг " + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Я бросил"+ GetSexPhrase("","а") +" якорь у " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " под флагом " + NationNameGenitive(sti(pchar.nation)) + ". Что тебе еще не ясно?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Эх, капитан, как славно было с вами в море! Сколько кораблей мы потопили под вашей командой! А тут...";
									link.l1 = "А тут, друг мой, перед вами постоянно мелькают очаровательные женщины, которых в море не бывает.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Капитан, за что такое наказание?! Мы ведь не сухопутные крысы!";
									link.l1 = "Спокойно, моряк! Вы на важном и почетном посту, так что не нойте.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Как там в море, капитан? Мы когда-нибудь снова увидим его?";
									link.l1 = "Конечно, матрос! Сменитесь с караула, выйдете на пирс и наслаждайтесь морем сколько угодно.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Спешу пожаловаться, капитан: мы все стремимся снова в море. Эта служба на суше просто поперек горла стоит!";
									link.l1 = "Я устал"+ GetSexPhrase("","а") +" от этого нытья! Выпивки вам хватает и на земле! Служи там, где тебя поставил капитан! А то кое-кого придется вздернуть для примера.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Скажу вам по секрету, капитан, новый губернатор - взяточник и казнокрад. Но это, конечно, не мое дело...";
									link.l1 = "Ты прав, корсар: твое дело - стоять на посту и следить за порядком. Ну, а вздернуть губернатора на нок-рее - это уже занятие для меня. Молодец!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Спасибо, что не забываете о нас капитан! Мы за вас и в огонь и в воду!";
									link.l1 = "Знаю я вас, проходимцев! Любите только золото. Сегодня в таверне попойка, я угощаю. Не забудь заглянуть.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Эх, капитан! Как давно мы не были в кровавой драке! Ну, какие из корсаров копы?!";
									link.l1 = "Не расслабляйся, корсар! Вражеские армады рыщут вокруг наших островов, так что кровавая баня может приключиться в любой момент.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Капитан, говорят, королевские власти снова посылают сюда эскадру?";
									link.l1 = "Конечно, корсар. Пока мы живы, мира не будет никогда. И даже в Аду станем сражаться с чертями!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Йо-хо-хо! Какая знатная вчера у нас была попойка, капитан! Жалко, что вас не было.";
									link.l1 = "Ничего, я свое еще наверстаю. И вам, ребята, я не завидую.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Скажу вам по секрету, капитан, поскольку вы нас никогда не обижали, завалили мы вчера с ребятами здесь одну телочку...";
									link.l1 = "Эх, корсар, плачет по вам петля!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Кэп! Освободите вы меня от этой проклятой повинности! Ну, не могу я здесь блюстителя порядка разыгрывать!";
									link.l1 = "Ты лучше вспомни: ночную вахту на корабле стоять тоже не легко. Служба, брат, она везде служба.";
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple("Есть важное дело!", "У меня к тебе дело.");
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
						else
						{ // пираты, не наши
							dialog.text = LinkRandPhrase(RandPhraseSimple("У вас ко мне дело, капитан?", "Я тут по делам мотаюсь, если что-то надо - спрашивайте, не тяните."), RandPhraseSimple("Капитан, я очень занят, так что поищите других собеседников.", "Что-то не так, капитан? Если вопросов нет, то разрешите пройти."), "Дайте дорогу, капитан, я тороплюсь.");
							link.l1 = LinkRandPhrase("Извини, приятель, я "+ GetSexPhrase("обознался","обозналась") +" ", "Ладно, занимайся своими делами.", "Нет, ничего.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("У меня к тебе пара вопросов.", "У меня к тебе дело."), RandPhraseSimple("Вижу, что торопишься. Один вопрос и будешь свободен.", "Я "+ GetSexPhrase("хотел","хотела") +" спросить кое-что."), "Твои дела подождут. Я вот что спросить "+ GetSexPhrase("хотел","хотела") +".");
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Вы посмотрите, "+ GetSexPhrase("каков мерзавец! Посмел","какова мерзавка! Посмела") +" явится в " + XI_ConvertString("Colony" + npchar.city)+ ". Держи "+ GetSexPhrase("его","ее") +"!!", "Ха, я узнал тебя, "+ GetSexPhrase("негодяй","негодяйка") +"! Хватай "+ GetSexPhrase("его","ее") +"!!");
							link.l1 = RandPhraseSimple("Аргх!..", "Ну, вы сами напросились...");
							link.l1.go = "fight";
							break;
						}
					}
					//зачарованный город -->
					if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
					{
						dialog.text = LinkRandPhrase("Видите, что творится в городе? Но мы не будем ни во что вмешиваться...",
							"До тех пор, пока волнения не перейдут в погромы, мы ничего не будем делать. Пусть буянят.",
							"Мы ведем себя так, как будто в городе все нормально. Нельзя поддаваться настроениям толпы, иначе волнения могут перейти в бунт!");
						link.l1 = "Понятно...";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
					{
						dialog.text = "Вы ходили в таверну. И что скажете?";
						link.l1 = "Пока ничего...";
						link.l1.go = "exit";
						break;
					}
					//<-- зачарованный город
					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)
						{
							dialog.text = "О-о, какие лица! Сама " + pchar.GenQuest.EncGirl.name + " к нам пожаловала собственной персоной! И как это ты отважилась? А мы тебя обыскались уже! Пожалуйте в каземат, ваша камера давно приготовлена и только вас дожидается. ";
							link.l1 = "Чего вы несёте?! Вы обознались! Мы с "+ GetSexPhrase("кавалером","подругой") +" в джунглях гуляли, цветы собирали. Отвяжитесь! Что за манеры у этих солдафонов?! Как только увидят симпатичную девушку, сразу находят повод прицепиться! "+ GetSexPhrase("Милый, скажи этим болванам, чтоб валили и не приставали к честной даме","Дорогая, ну скажи же этим болванам...") +"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)
						{
							dialog.text = "А вот и ты, красавица. Сама пришла! Твой папаша весь гарнизон на ноги поднял, велел тебя разыскать и домой вернуть";
							link.l1 = "Отвяжитесь! Я сама знаю куда мне идти и в вашей помощи не нуждаюсь!.. Капитан, скажите им, чтобы убрали руки.";
							link.l1.go = "GirlEnc_2";
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Устав караульной службы не позволяет мне болтать с прохожими";
							link.l1 = "Молодец, солдат! Так держать.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Что-то неладно? Вы заметили какие-то беспорядки?";
							link.l1 = "Нет, всё в порядке. Но твоя бдительность похвальна.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Драки и дуэли на улицах города запрещены. Оружие можно обнажать только в случае опасности.";
							link.l1 = "Хорошо, я приму это к сведению.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Эх, погодка-то какая! А я торчу здесь, как истукан... только мух гоняю.";
							link.l1 = RandPhraseSimple("Не расслабляйся, солдат. Враг не дремлет.", "Негоже на службу сетовать. С таким настроением много не навоюешь.");
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Поищите другого собеседника, если поболтать приспичило - мне поручено за порядком следить, а не языком чесать.";
							link.l1 = "Молодец, солдат, исправно служишь! Только груб не в меру.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Поддерживать порядок, скажу я вам, это совсем не так просто, как может показаться со стороны. Это очень ответственная и опасная работа. Вот случай был в гарнизоне...";
							link.l1 = LinkRandPhrase("Не отвлекайся на посту.", "Что за разговоры на службе?!", "Стой, где поставили. Языком чесать в таверне будешь.");
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = RandPhraseSimple("Не отвлекайте меня, " + GetAddress_Form(NPChar) + ", я на посту.", "Проходите, " + GetAddress_Form(NPChar) + ", не отвлекайте часового от несения службы.");
							link.l1 = "Я просто "+ GetSexPhrase("проверял","проверяла") +", не заснул ли ты на посту. А то стоишь, как истукан.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Эй, " + GetAddress_Form(NPChar) + ", у вас не найдется пары глотков вина, чтобы промочить горло? Умираю от жажды.";
							link.l1 = "Служба есть служба. Терпи, пока не сменят.";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("Вы уже не первый моряк, который пытается отвлечь меня от несения службы. Ну почему ко мне не подходят аппетитные вдовушки","Эй, красавица! Как насчет того, чтобы немного пофлиртовать с бравым воякой") +"?";
							link.l1 = RandPhraseSimple("Ты никак позабыл, что находишься на посту, а не в борделе.", "Твоё дело за порядком следить... и слюни подбери.");
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("Ты выглядишь крепким парнем! Не хочешь поступить на службу? У нас просторная казарма, хорошая кормёжка и выпивка бесплатно.","О, вы даже не представляете, девушка, насколько приятно встретить в этом захолустье такую милую особу, как вы!") +"";
							link.l1 = ""+ GetSexPhrase("Соблазнительно, черт побери, но я вынужден отказаться. Казарменная муштра не для меня","Спасибо за комплимент, солдат") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Эта жара... Я бы пол жизни отдал, что бы снова оказаться в Европе.";
							link.l1 = RandPhraseSimple("Да уж, вояка из тебя никудышный.", "Солдатская служба везде не сахар.");
							link.l1.go = "exit";
						break;
					}
					link.l3 = "Минуту. Я вот что спросить "+ GetSexPhrase("хотел","хотела") +"...";
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
		if (GetQuestPastDayParam("questTemp.LastBribe") > 0 || !CheckAttribute(pchar, "BribePrice"))
		{
			SaveCurrentQuestDateParam("questTemp.LastBribe");
			pchar.BribePrice = bribe_price;
		}
		if (IsCharacterPerkOn(pchar, "Adventurer") || IsCharacterPerkOn(pchar, "Agent"))
		{
			dialog.text = RandPhraseSimple("Сдается мне, что это обман... Давай-ка пройдем в комендатуру, "+ GetSexPhrase("голубчик","голубушка") +", там разберемся...", "Хм, что-то подсказывает мне, что ты не "+ GetSexPhrase("тот","та") +", за кого себя выдаешь... Немедленно сдайте оружие, " + GetAddress_Form(npchar) + ", и следуйте за мной для дальнейшего разбирательства!");
			link.l1 = RandPhraseSimple("Почему вы мне не верите?", "С чего такие выводы?");
			switch (rand(1))
			{
				case 0: link.l1.go = "NotPegYou"; break;
				else link.l1.go = "PegYou_2"; break;
			}
			if(bBribeSoldiers == true)
			{
				if(makeint(Pchar.money) >= sti(pchar.BribePrice))
				{
					link.l2 = RandPhraseSimple("Тут рядом кошель валялся, случаем не ваш? Ух, а он тяжелый, зараза! Вот, держите и больше не теряйте. Кстати, я могу идти?", "Вы меня раскусили. На самом деле я просто странствую по Карибам и раздаю деньги нуждающимся. Говорят, страже мало платят? Это необходимо исправлять. Начнем с вас. Вот, держите. Теперь все в порядке?");
					link.l2.go = "NotPegYou_2";
				}
			}
		}
		else
		{
			if(bBribeSoldiers == true)
			{
				if(makeint(Pchar.money) >= sti(pchar.BribePrice))
				{
					link.l2 = RandPhraseSimple("Тут рядом кошель валялся, случаем не ваш? Ух, а он тяжелый, зараза! Вот, держите и больше не теряйте. Кстати, я могу идти?", "Вы меня раскусили. На самом деле я просто странствую по Карибам и раздаю деньги нуждающимся. Говорят, страже мало платят? Это необходимо исправлять. Начнем с вас. Вот, держите. Теперь все в порядке?");
					link.l2.go = "NotPegYou_2";
				}
			}
			dialog.text = RandPhraseSimple("Сдается мне, что это обман... Давай-ка пройдем в комендатуру, "+ GetSexPhrase("голубчик","голубушка") +", там разберемся...", "Хм, что-то подсказывает мне, что ты не "+ GetSexPhrase("тот","та") +", за кого себя выдаешь... Немедленно сдайте оружие, " + GetAddress_Form(npchar) + ", и следуйте за мной для дальнейшего разбирательства!");
			link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
			link.l1.go = "fight";

		}
		if (!CheckAttribute(pchar,"questTemp.stels.landSolder"))
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
		case "PegYou_2":
		dialog.text = RandPhraseSimple("Вам не запудрить мне голову! Сдавайте оружие!", "Ну точно шпион... Сдавайтесь немедленно!");
		if(bBribeSoldiers == true)
			{

				if(makeint(Pchar.money) >= sti(pchar.BribePrice))
				{
					link.l2 = RandPhraseSimple("Тут рядом кошель валялся, случаем не ваш? Ух, а он тяжелый, зараза! Вот, держите и больше не теряйте. Кстати, я могу идти?", "Вы меня раскусили. На самом деле я просто странствую по Карибам и раздаю деньги нуждающимся. Говорят, страже мало платят? Это необходимо исправлять. Начнем с вас. Вот, держите. Теперь все в порядке?");
					link.l2.go = "NotPegYou_2";
				}
			}
		link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
		link.l1.go = "fight";
		if (!CheckAttribute(pchar,"questTemp.stels.landSolder"))
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("А-а-а, вижу... Все в порядке, вы можете идти, " + GetAddress_Form(pchar) + ".", "Что-то я немного подустал в карауле... Все в порядке, " + GetAddress_Form(pchar) + ", прошу прощения.");
			link.l1 = "Так-то!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder"))
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
				case "NotPegYou_2":
			dialog.text = RandPhraseSimple("А вот за это спасибо вам, " + GetAddress_Form(pchar) + "." + " На прощание, дам вам бесплатный совет: загляните к нашему портовому начальнику и попросите какую-нибудь бумажку. Сразу легче жить станет.", "Я думаю, в вашем кошеле найдется гораздо больше монет, " + GetAddress_Form(pchar) + ", но ладно, я сегодня добрый." + " На прощание, дам вам бесплатный совет: загляните к нашему портовому начальнику и попросите какую-нибудь бумажку. Сразу легче жить станет.");
			link.l1 = "До свидания.";
			link.l1.go = "exit";
			AddMoneyToCharacter(Pchar, -sti(pchar.BribePrice));

			pchar.questTemp.bribescount = sti(pchar.questTemp.bribescount) +1;
			if(sti(pchar.questTemp.bribescount) >= 10) UnlockAchievement("AchVzyatka", 1);
			if(sti(pchar.questTemp.bribescount) >= 25) UnlockAchievement("AchVzyatka", 2);
			if(sti(pchar.questTemp.bribescount) >= 50) UnlockAchievement("AchVzyatka", 3);

			pchar.BribePrice = sti(pchar.BribePrice) * 1.33;

			if (!CheckAttribute(pchar,"questTemp.stels.landSolder"))
			{
				AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 60);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 60);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = "Ваша лицензия подлежит изъятию, так как просрочена и поэтому недействительна. Сдайте оружие и следуйте за мной для последующих разбирательств!";
				link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
				link.l1.go = "fight";
				TakeNationLicence(sti(npchar.nation));
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20); // враг, которого узнали - потом будет умнее - бонус в скрытность
			}
			if (iTemp == 0)
			{
				dialog.text = "Хм, все верно. Однако позволю себе заметить, что срок действия вашей лицензии сегодня истекает. Я пропущу вас сейчас, но вам нужно будет сменить лицензию на действительную.";
				link.l1 = "Спасибо, я обзаведусь новой при первой же возможности.";
				link.l1.go = "exit";
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Хм, все верно. Однако позволю себе заметить, что срок действия вашей лицензии вскоре истекает - она действительна еще только " + FindRussianDaysString(iTemp) + ". Так что имейте в виду, " + GetAddress_Form(npchar) + ".";
				link.l1 = "Спасибо, я обзаведусь новой при первой же возможности.";
				link.l1.go = "exit";
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Ну что же, очень хорошо, ваша лицензия действует еще " + FindRussianDaysString(iTemp) + ". Вы можете пройти.", "Все ясно, "+GetAddress_Form(npchar)+". Вы можете свободно проходить в город, ваша лицензия действует еще " + FindRussianDaysString(iTemp) + ". Прошу прощения за беспокойство.", "Все в порядке, " + GetAddress_Form(npchar) + ", не смею вас задерживать.");
				link.l1 = RandPhraseSimple("Отлично. Всего хорошего.", "Спасибо, офицер.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Эй, приятель, смотри ничего не сломай на маяке.", "Маяк - очень важный объект для города. Будь осторожен!");
			link.l1 = RandPhraseSimple("Хорошо, не переживай.", "Все будет в порядке.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Не нужно ходить возле орудий - это военный объект!", "Доступ к орудиям посторонних лиц категорически запрещен!", "Если я замечу, что ты ошиваешься возле орудий - тебе конец!");
			link.l1 = RandPhraseSimple("Я понял" + GetSexPhrase("","а") + "тебя.", "Хорошо, я все понял" + GetSexPhrase("","а") + ".");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице ==================
		case "SeekSpy_Checking":
			dialog.text = "Да, я подтверждаю. " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "Он действительно местный житель.", "Она действительно местная жительница.");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("понял","поняла") +". Спасибо за помощь.", "Все ясно. Спасибо за помощь.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;

		// --> генератор "Девица в джунглях"
		case "GirlEnc_1":
			dialog.text = "А вы, капитан, кто "+ GetSexPhrase("такой","такая") +" будете? Не "+ GetSexPhrase("подельничек","подельница") +" ли самой знаменитой на всё поселение воровки?";
			link.l1 = "Ты кого "+ GetSexPhrase("'подельничком'","'подельницей'") +" назвал?! На солнце перегрелся?! А ну, уберите руки от девчонки!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Да я, собственно, только что с ней "+ GetSexPhrase("познакомился","познакомилась") +"...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+ GetSexPhrase("Сударь","Сударыня") +", нам приказано её задержать и сопроводить в каземат. И напрасно вы думаете, что сможете нам помешать.";
			link.l1 = "Вот сейчас и проверим...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterReputation(pchar, -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "GirlEnc_12":
			dialog.text = "Да? Вы б тогда карманы проверили. Не ровен час... Дамочка ведь профессионал с большой буквы 'П'";
			link.l1 = "Спасибо, проверю обязательно. Это же надо было так опростоволоситься...";
			link.l1.go = "GirlEnc_12End";
		break;

		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "GirlEnc_2":
			dialog.text = ""+ GetSexPhrase("Сударь","Сударыня") +", нам приказано разыскать эту особу и доставить к отцу.";
			link.l1 = "Хм, ну доставляйте, раз приказано.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Вы опоздали. Я уже веду её домой.";
			link.l2.go = "GirlEnc_21";
		break;

		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("JungleGirl", "11");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "GirlEnc_21":
			ChangeCharacterReputation(pchar, 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Капитан, у нас есть приказ и вы напрасно думаете, что сможете нам помешать.";
				link.l1 = "Вот сейчас и проверим...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Эх, "+ GetSexPhrase("счастливчик","счастливица") +". Её папаша обещал щедро наградить того, кто дочку вернёт..";
				link.l1 = "Не отчаивайтесь, ваши награды ещё впереди.";
				link.l1.go = "exit";
			}
		break;

		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// <-- генератор "Девица в джунглях"

		//замечение по обнаженному оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase("Чего вы клинком размахиваете?! Немедленно уберите оружие!", "Приказываю вам немедленно убрать оружие!", "Эй, " + GetAddress_Form(NPChar) + ", не пугайте народ! Уберите оружие.");
			link.l1 = LinkRandPhrase("Хорошо, убираю...", "Уже "+ GetSexPhrase("убрал","убрала") +".", "Как скажешь...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Черта с два!", "Сейчас пущу его в дело!", "Уберу, когда время придёт.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
			if(NPChar.chr_ai.type == "guardian") link.l1.go = "First Time";
		break;

	}
}
