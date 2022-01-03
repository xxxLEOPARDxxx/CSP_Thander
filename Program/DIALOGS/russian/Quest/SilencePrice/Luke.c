void ProcessDialogEvent()
{
    ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
    break;
	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием наизготовку. Это меня пугает...");
			link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
		}
		Link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
	break;
    case "First Time":
        if (!isMainCharacterPatented())
        {
            Log_info("У вас нет патента");
            dialog.text = "Проходи, чего встал" + GetSexPhrase(".", "а.");
            link.l1 = "Ладно, ладно, не кипятись.";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "О! Кого я вижу? " + GetFullName(Pchar) + " собственной персоной! Вот это встреча!";
            link.l1 = "Э-э... Боюсь, я вас не узнаю.";
            link.l1.go = "StartQuest_1";
            AddBonusEnergyToCharacter(NPChar, 50);
        }
    break;
    case "StartQuest_1":
        dialog.text = "Да это же я, Люк! Мы с тобой ходили под флагом Барта Португальца.";
        link.l1 = "Твою бизань! Люк! Как ты изменился, старина!";
        link.l2 = "Хмм... Все ещё нет. Ты бы отвалил от меня, приятель, по добру, по здорову";
        link.l1.go = "StartQuest_3";
        link.l2.go = "exit";
    break;
    case "StartQuest_3":
        dialog.text = "Хех! А я уж думал, совсем с ума сошёл, и это не ты. Пойдем в таверну, посидим, поболтаем!";
        link.l1 = "Ха! С радостью!";
		DeleteAttribute(NPChar, "quest");
        AddDialogExitQuest("Taverna");
    break;
    case "StartQuest_4":
        dialog.text = GetFullName(Pchar) + ", как ты, " + GetSexPhrase("приятель", "подруга") + "? Расскажи, как тебя сюда занесло?";
        link.l1 = "Я своего рода путешественни" + GetSexPhrase("к", "ца") + ", то на один остров поплыву, то на другой, а может и на Мейн захочу.";
        link.l1.go = "StartQuest_6";
    break;
    case "StartQuest_6":
        dialog.text = "Вот оно как. Помню я наше последнее путешествие, когда мы шли грабить к Гвинее за рабами. Нас тогда чуть не перебили. Поселение, которое мы решили захватить, было очень хорошо защищено. Да... Не всем удалось уйти... Давай выпьем за то, что мы остались живы!";
        link.l1 = "Эх, да уж, много наших тогда полегло. А ведь могли все уйти, если бы не жадность нашего командира! Выпьем!";
        link.l1.go = "StartQuest_7";
    break;
    case "StartQuest_7":
        dialog.text = "Я смотрю у тебя и корабль свой есть, и звание... Слушай, мне не удобно тебя просить, столько времени не виделись, и так сразу...";
        link.l1 = "Не юли, выкладывай, помогу, если смогу.";
        link.l1.go = "GiveQuest";
    break;
    case "GiveQuest":
        string spawn_max;
        int Gorod;
        NPChar = characterFromID("Old Friend");
        if (Pchar.PatentNation == "eng")
        {
            while (0 < 1)
            {
                Gorod = rand(5);
                if (Gorod == 0)
                {
                    spawn_max = "PortRoyal_tavern";
                    dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Порт Роял. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                    link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                    AddQuestUserData("Silence_Price", "sCity2", "Порт Роял");
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 1)
                {
                    spawn_max = "SentJons_tavern";
                    dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Сент-Джонс. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                    link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                    AddQuestUserData("Silence_Price", "sCity2", "Сент-Джонс");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 2)
                {
                    spawn_max = "Charles_tavern";
                    dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Чарлстаун. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                    link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                    AddQuestUserData("Silence_Price", "Friendname", NPChar.name + "a " + NPChar.lastname + "а");
                    AddQuestUserData("Silence_Price", "sCity2", "Чарлстаун");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 3)
                {
                    spawn_max = "Bridgetown_tavern";
                    dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Бриджтаун. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                    link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                    AddQuestUserData("Silence_Price", "sCity2", "Бриджтаун");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 4)
                {
                    spawn_max = "Portspein_tavern";
                    dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Порт оф Спейн. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                    link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                    AddQuestUserData("Silence_Price", "sCity2", "Порт оф Спейн");
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
            }
        }
        else
        {
            if (Pchar.PatentNation == "hol")
            {
                while (0 < 1)
                {
                    Gorod = rand(3);
                    if (Gorod == 0)
                    {
                        spawn_max = "Villemstad_tavern";
                        dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Виллемстад. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                        link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                        AddQuestUserData("Silence_Price", "sCity2", "Виллемстад");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                    if (Gorod == 1)
                    {
                        spawn_max = "Marigo_tavern";
                        dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Мариго. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                        link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                        AddQuestUserData("Silence_Price", "sCity2", "Мариго");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                    if (Gorod == 2)
                    {
                        spawn_max = "FortOrange_tavern";
                        dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Форт-Оранж. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                        link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                        AddQuestUserData("Silence_Price", "sCity2", " Форт-Оранж");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                }
            }
            else
            {
                if (Pchar.PatentNation == "fra")
                {
                    while (0 < 1)
                    {
                        Gorod = rand(4);
                        if (Gorod == 0)
                        {
                            spawn_max = "FortFrance_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Форт Де Франс. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Форт Де Франс");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 1)
                        {
                            spawn_max = "FortFrance_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Форт Де Франс. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Форт Де Франс");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 2)
                        {
                            spawn_max = "BasTer_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Бас Тер. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Бас Тер");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 3)
                        {
                            spawn_max = "Tortuga_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга на Тортугу. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Тортугу");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                    }
                }
                else
                {
                    while (0 < 1)
                    {
                        Gorod = rand(9);
                        if (Gorod == 0)
                        {
                            spawn_max = "Caracas_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Каракас. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Каракас");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 1)
                        {
                            spawn_max = "Cumana_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Куману. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Куману");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 2)
                        {
                            spawn_max = "Cartahena_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Картахену. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Картахену");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 3)
                        {
                            spawn_max = "Maracaibo_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Маракайбо. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Маракайбо");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 4)
                        {
                            spawn_max = "PortoBello_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Порто Белло. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Порто Белло");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 5)
                        {
                            spawn_max = "SantaCatalina_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Санта Каталину. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Санта Каталину");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 6)
                        {
                            spawn_max = "Beliz_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Белиз. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Белиз");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 7)
                        {
                            spawn_max = "SantoDomingo_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Санто Доминго. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Санто Доминго");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 8)
                        {
                            spawn_max = "SanJuan_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Сан Хуан. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1")
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Сан Хуан");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 9)
                        {
                            spawn_max = "Santiago_tavern";
                            dialog.text = "Пожалуйста, доставь письмо от меня для моего друга в Сантьяго. Не смотри так, тебе заплатят по прибытии! Наверняка, ты найдешь его в таверне. Друга зовут Максимилиан Вебер, скажи, что ты от Люка Артиста.";
                            link.l1 = "Ха! Твоя старая кличка! Давай письмо!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "а"));
                            AddQuestUserData("Silence_Price", "sCity2", "Сантьяго");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "а");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                    }
                }
            }
        }
        break;
    case "StartQuest_8":
        dialog.text = "Да, кличка никуда не делась! Спасибо большое! Удачи тебе в плавании и попутного ветра! Выпьем!";
        link.l1 = "Выпьем!";
        NextDiag.TempNode = "Story1";
        link.l1.go = "Exit";
		Pchar.Luke.SpawnMaks = "1";
    break;
    case "Story1":
		dialog.text = "Что же ты ждешь? Тебе пора в путь!";
		link.l1="Постой, Люк. Как тебе удалось тогда выбраться? Я помню, что я уш"+GetSexPhrase("ел","ла")+" од"+GetSexPhrase("ин","на")+". Расскажи, что тогда случилось?";
		link.l1.go="Story2";
	break;
	case "Story2":
		dialog.text = "Хм, я знал что ты спросишь. Ну, слушай. Тогда, после того как мы бросились в бегство, мушкетер попал мне прямо в бедро и я упал среди мертвых тел. Когда пальба утихла, меня нашли живым вражеские солдаты. Они не стали меня убивать, но взяли в плен... ";
		link.l1="Что же было дальше?";
		link.l1.go="Story3";
	break;
	case "Story3":
		dialog.text = "Вот слушай. Они не пытали меня, а наоборот помогли с моим ранением и поставили на ноги. Научили меня военному и морскому исскуству и за обещание отпустили на свободу.";
		link.l1="Что же за обещание ты дал им?";
		link.l1.go="Story4";
	break;
	case "Story4":
		dialog.text = "Хм, я обещаю, что расскажу об этом, когда ты вернешься от Максимилиана. Сейчас не время для этого разговора.";
		link.l1="Хорошо, Люк, надеюсь ты сдержишь свое обещание";
		link.l1.go="exit";
		AddQuestRecord("Silence_Price","3");
		AddQuestUserData("Silence_Price","sSex",GetSexPhrase("","а"));
		NextDiag.TempNode="Pause";
	break;
    case "Pause":
        dialog.text = "О, кого я вижу! Присаживайся, выпьем.";
        link.l1 = "Да, это я. Нет, спасибо, у меня дела.";
        link.l1.go = "exit";
    break;
	case "SecondQuest_1":
		dialog.text = Pchar.name +"?! Что ты тут делаешь?! Как... Как ты наш" + GetSexPhrase("ел","ла") + " меня? Это... Это невозможно!";
		link.l1="Что же ты, Люк. В чем смысл твоих игр? Ты хочешь избавиться от меня? Насолить мне? В чем твоя цель, ублюдок?";
		link.l1.go="SecondQuest_2";
	break;
	case "SecondQuest_2":
		dialog.text = "Тебе не понять... У меня было всё, всё что мне было нужно. Я был счастлив. Но после того злополучного похода, будь он проклят, моя жизнь пошла под откос. Я хочу отомстить всем, кто виновен в этом.";
		link.l1 = "Постой, Люк, но в чем заключается моя вина?";
		link.l1.go = "SecondQuest_3";
	break;
	case "SecondQuest_3":
		dialog.text = Pchar.Name + ", я же говорил, не поймешь. Homo homini lupus est. Невиновных не бывает. Есть только разные степени ответственности. И сейчас ты почувствуешь ответственность за всё, что тогда случилось.";
		link.l1 = "Как скажешь. Сейчас я положу конец твоей актерской карьере, ублюдок!";
		link.l1.go = "exit";
		AddDialogExitQuest("LukeFight");
	break;
	case "SecondQuest_4":
		dialog.text = Pchar.Name + ", постой, я сдаюсь... Ты победил" + GetSexPhrase(".","а.");
		link.l1 = "Что?! Вот так просто?!";
		link.l1.go = "SecondQuest_5";
	break;
	case "SecondQuest_5":
		dialog.text = "Конечно нет! Макс, ко мне! " + Pchar.Name + ", лови!";
		link.l1 = "Кха, кха кха... Что это такое?!");
		link.l1.go = "exit";
		AddDialogExitQuest("LukeOut");
	break;
	}
}
