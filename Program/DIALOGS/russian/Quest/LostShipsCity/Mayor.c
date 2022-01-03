
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp, i;

	string NodeName = Dialog.CurrentNode;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.location == "SanAugustineResidence")
			{
				dialog.text = "Что ты хотел"+ GetSexPhrase("","а") +"? Не задерживай меня по пустякам, я занят.";
				link.l1 = "Извини, так просто заскочил"+ GetSexPhrase("","а") +" к тебе.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Когда я не у себя в резиденции, то, в принципе, не прочь поговорить... Что ты хотел"+ GetSexPhrase("","а") +"?";
				link.l1 = "Да так, просто хотел"+ GetSexPhrase("","а") +" узнать, все ли в порядке в Городе.";
				link.l1.go = "NRes_1";
			}
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				pchar.questTemp.LSC = "AdmiralFoundHero";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "А-а-а, вот и ты. Это хорошо, что ты сам"+ GetSexPhrase("","а") +" приш"+ GetSexPhrase("ел","ла") +" ко мне. Не люблю, когда от меня бегают, да еще в такой шторм...";
					link.l1 = "Ни от кого бегать не намерен"+ GetSexPhrase("","а") +". Меня зовут " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
					PChar.quest.LSC_admiralOwnFind.over = "yes";
				}
				else
				{
					dialog.text = "А-а-а, вот и ты. Я ждал, когда ты явишься ко мне.";
					link.l1 = "Приветствую. Меня зовут " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				break;
			}
			//квестовые ноды по главной линейке
			if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
			{
				link.l4 = "Адмирал, у меня есть для тебя важная информация. Гм, как мне кажется...";
				link.l4.go = "NarvalRing_1";
			}
			if (pchar.questTemp.LSC == "NarvalDestroyed")
			{
				link.l4 = "Я все сделал"+ GetSexPhrase("","а") +", клан 'Нарвал' уничтожен. Вырезал"+ GetSexPhrase("","а") +" там всех под корень, никто не ушел!";
				link.l4.go = "DestrNarval_1";
			}
			if (pchar.questTemp.LSC == "toAdmiralBarmenDead")
			{
				link.l4 = "Адмирал, я хотел"+ GetSexPhrase("","а") +" поговорить об убийстве Хилла Брюннера.";
				link.l4.go = "BarmenDead_1";
			}
			if (pchar.questTemp.LSC == "fromMechanicToAdmiral")
			{
				link.l4 = "Адмирал, я хотел"+ GetSexPhrase("","а") +" поговорить с тобой.";
				link.l4.go = "CasperDead_1";
			}
			//дополнительные квестовые ноды
			//муж Элис Тейлор
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.ElisHusband == "toElis")
			{
				link.l5 = "Адмирал, скажи, пожалуйста, что Максим Тейлор наделал тут у тебя?";
				link.l5.go = "ELTHusb_begin";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
			{
				link.l5 = "Адмирал, я хотел"+ GetSexPhrase("","а") +" бы помочь Максиму Тейлору.";
				link.l5.go = "ELTHusb_SF";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiralGood")
			{
				link.l5 = "Адмирал, я тут узнал"+ GetSexPhrase("","а") +" кое-что об обстоятельствах того дела с Тейлором.";
				link.l5.go = "ELTHusb_good";
			}
			//квест со скелетом Декстера
			if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.lostDecster == "toAdmiral")
			{
				link.l6 = "Адмирал, у меня есть к тебе небольшой вопрос по поводу Лейтона Декстера.";
				link.l6.go = "LostDecster";
			}
			//поиск товаров на корвет
			if (pchar.questTemp.LSC == "toSeekGoods")
			{
				link.l8 = "Слушай, я тут ищу кое-какие товары. Не мог бы ты меня выручить?";
				link.l8.go = "SeekGoods";
			}
			//найм команды
			if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
			{
				link.l8 = "Адмирал, надвигается шторм...";
				link.l8.go = "SeekCrew";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NRes_1":
			dialog.text = "Да, все хорошо. Я рад, что тебя так живо заботит наш Город. Ты "+ GetSexPhrase("хороший гражданин","хорошая гражданка") +".";
			link.l1 = "Рад"+ GetSexPhrase("","а") +" стараться, адмирал!";
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = "Очень хорошо, "+ GetSexPhrase("приятель","подруга") +", просто замечательно... А меня зовут " + GetFullName(npchar) + ", я адмирал этого Города Потерянных Кораблей!";
			link.l1 = "Ха, а ведь слышал"+ GetSexPhrase("","а") +" о тебе! Ты тот самый пиратский капитан, что вышел за призом на 'Ужасе Мейна' и пропал. Так вот куда ты задевался!";
			link.l1.go = "FT_1_1";
		break;
		case "FT_1_1":
			dialog.text = "Да, обо мне еще помнят в Карибском море... Видишь, как получилось. Два дня мы гнались за испанским галеоном, а в ночь на третьи сутки оказались здесь... Дьявол, вся моя команда пошла ко дну, выбраться смогли только я, Уоркман и Форе.";
			link.l1 = "Сожалею...";
			link.l1.go = "FT_1_2";
		break;
		case "FT_1_2":
			dialog.text = "По правде сказать, дерьмо была команда тогда. Так что, можно и не горевать особо, тем более, что дело прошлое... Ну, сейчас мы не об этом!";
			link.l1 = "Говори, что нужно. Я внимательно слушаю, " + npchar.name + ".";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Значит, так! С того момента, как ты влез"+ GetSexPhrase("","ла") +" с моря на палубу нашего острова, ты стал"+ GetSexPhrase("","а") +" граждан"+ GetSexPhrase("ином","кой") +" Города, и теперь обязан"+ GetSexPhrase("","а") +" подчиняться его Закону. Это тебе понятно?";
			link.l1 = "Вполне. И что за Закон, как с ним можно ознакомиться?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "С Законом знакомлю тебя я в данный конкретный момент. На скрижалях он не выбит, так как с камнем у нас напряженка, ха-ха... А Закон по сути своей заключается в следующих пунктах\n"+
				"Все граждане Города Потерянных Кораблей имеют право на жизнь. Это право обеспечивает гарнизон милиции, который находится в распоряжении адмирала, то есть в моем распоряжении... Кстати, а ты не хочешь записаться в милицию?";
			link.l1 = "Там посмотрим. Сначала нужно обжиться, как-то устроиться здесь, а потом уже решать такие вопросы.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Ты по виду "+ GetSexPhrase("парень неслабый","девушка боевая") +". Кем был"+ GetSexPhrase("","а") +" в Большом мире?";
			link.l1 = "Да так, знаешь ли, странствовал"+ GetSexPhrase("","а") +"... Был"+ GetSexPhrase("","а") +" свободным капитаном, таким же, как и ты, в общем.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Понятно... Но сейчас, собственно, мне до этого дела нет. Будь ты до попадания сюда испан"+ GetSexPhrase("цем","кой") +" или францу"+ GetSexPhrase("зом","женкой") +", ангелом или чертом лысым - здесь все равны. Теперь ты стал"+ GetSexPhrase("","а") +" граждан"+ GetSexPhrase("ином","кой") +" Города, со своими правами, важнейшим из которых является право на жизнь! Хех, как завернул!..";
			link.l1 = "Да, неплохо. Всеобщая справедливость. Кстати, в Карибском море ходят слухи о каком-то Острове Справедливости. Полагаю, что это и есть ваш Город.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Нет, этого не может быть. Путь отсюда заказан... Ну, продолжим. Итак, с правами все, теперь о твоих обязанностях. Первое: ты не можешь покушаться на жизнь граждан Города. Если ты убьешь кого-то, то тебя убью я. Это ясно?";
			link.l1 = "Хм, ясно...";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Небольшой нюанс. У нас тут в Городе есть два сообщества, так называемые кланы 'Нарвал' и 'Каспер'. В общем, там собрались люди, которым жизнь добропорядочного человека - что кость в горле. Мы им выделили два корабля под постоянное место дислокации - это барк 'Сан Габриэль' и галеон 'Веласко'. Корабли эти стоят на отшибе, поэтому кланы жизни Города не мешают\n"+
				"Так вот, заходить внутрь этих кораблей гражданам не стоит - опасно для жизни. Внутренние помещения данных судов переданы в собственность кланов, и на этой территории у них действуют свои законы. Поэтому не лезь туда или пеняй на себя. Понятно?";
			link.l1 = "Понятно.";
			link.l1.go = "FT_7_1";
		break;
		case "FT_7_1":
			dialog.text = "Пойдем дальше. Второе: запрещается строить корабли, плоты и прочие плавсредства. Выбраться отсюда все равно невозможно, а разрушать Город нельзя.";
			link.l1 = "И это понятно.";
			link.l1.go = "FT_7_2";
		break;
		case "FT_7_2":
			dialog.text = "Третье: за воровство в Городе полагается смертная казнь. Если тебя застукают копающ"+ GetSexPhrase("имся","ейся") +" в чужом сундуке - ты автоматически лишаешься гражданства и становишься вне Закона. А это значит, что права на жизнь у тебя больше нет...";
			link.l1 = "Звучит заманчиво... Ну что же, это ясно. Что дальше?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Ну и четвертое: все материальные средства, которые попали в Город, принадлежат Городу.";
			link.l1 = "Хм, а вот по этому пункту подробней, пожалуйста.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Хех, ну что ж тут непонятного? Вот, к примеру, ты, как физическое лицо, попал"+ GetSexPhrase("","а") +" в Город. И заметь, сразу стал"+ GetSexPhrase("","а") +" его граждан"+ GetSexPhrase("ином","кой") +"!\nА вот твое имущество, как материальные средства, становятся собственностью Города. Так что все твое теперь наше общее!";
			link.l1 = "Погодите! Я с таким раскладом не соглас"+ GetSexPhrase("ен","на") +"!";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			if (pchar.questTemp.LSC == "AdmiralFoundHero")
			{
				dialog.text = "Вот "+ GetSexPhrase("чудак-человек","чудачка") +"! Твоего согласия не требуется, мы просто забираем, и все... Но у меня есть и хорошая новость. Тебе, как полноправно"+ GetSexPhrase("му","й") +" граждан"+ GetSexPhrase("ину","ке") +" Города, полагается 1/50 часть!";
				link.l1 = "От моего же имущества!!";
				link.l1.go = "FT_11";
				pchar.money = makeint(sti(pchar.money) / 50);
			}
			else
			{
				dialog.text = "А твоего согласия никто не спрашивает. Вообще-то, Закон обязывает включать бывшего хозяина добра в число дольщиков при разделе. Но так как ты нарушил"+ GetSexPhrase("","а") +" Закон, а именно не явил"+ GetSexPhrase("ся","ась") +" ко мне вовремя по прибытии в Город, данный пункт Закона в отношении тебя утрачивает свою силу. То есть тебе не достается ничего.";
				link.l1 = "Мне все это очень сильно не нравится!";
				link.l1.go = "FT_12";
				pchar.money = 0;
			}
		break;
		case "FT_11":
			dialog.text = "Именно! Ну вот, ты начинаешь понимать... Вообще-то, тебе все одно это барахло тут ни к чему, а нам всем приятно будет...";
			link.l1 = "Мне все это очень сильно не нравится!";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "Не ты перв"+ GetSexPhrase("ый","ая") +", "+ GetSexPhrase("приятель","подруга") +", кому это не нравится. Но только, уж поверь мне, все это в твоих интересах. Чем быстрей ты избавишься всего того, что тебя связывает с большим миром, тем быстрей ты вольешься в нашу размеренную жизнь.\nА так можешь сойти с ума, такое бывает. И, скажу я тебе, с такими мы не церемонимся - груз на шею, и на дно!";
			link.l1 = "Да уж, справедливость так и прет...";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "За хамство я лишаю тебя оружия, да и вообще карманы твои почищу! И имей в виду, что в следующий раз, если ты мне не понравишься, я тебя просто прикончу.";
			link.l1 = "М-да... Ну что же, придется смириться. Похоже, у меня нет другого выхода.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "Это верно. И не советую тебе его искать, это запрещено Законом!";
			link.l1 = "Я помню...";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "Ну вот и отлично... А теперь ты свобод"+ GetSexPhrase("ен","на") +" и можешь перемещаться по Городу как угодно. Делай, что хочешь, наслаждайся жизнью в Городе.";
			link.l1 = "Так и поступлю, Чад.";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			if (npchar.chr_ai.type == LAI_TYPE_ACTOR) LAi_SetLSCoutTypeNoGroup(npchar);
			AddDialogExitQuestFunction("LSC_admiralTakeAll");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//базар с ГГ, если сам не пришел к адмиралу
		case "FoundHero":
			npchar.quest.meeting = "1";
			NextDiag.TempNode = "First time";
			pchar.questTemp.LSC = "AdmiralNotFoundHero";
			dialog.text = "Ага, вот, значит, и ты, выживш"+ GetSexPhrase("ий","ая") +" в последнем шторме. Скажи-ка мне, "+ GetSexPhrase("приятель","подруга") +", какого это черта я должен искать тебя по всему Городу? Ты что, не знаешь наших порядков?";
			link.l1 = "Приветствую. Каких порядков?";
			link.l1.go = "FoundHero_1";
		break;
		case "FoundHero_1":
			dialog.text = "Хочешь сказать, что ты не знал"+ GetSexPhrase("","а") +" о том, что ко мне нужно явиться сразу же, как только оказался в Городе?";
			link.l1 = "Не знал"+ GetSexPhrase("","а") +"...";
			link.l1.go = "FoundHero_2";
		break;
		case "FoundHero_2":
			dialog.text = "Незнание Закона не освобождает от ответственности! А теперь говори, кто ты.";
			link.l1 = "Я прошу прощения за опоздание, я еще не изучил"+ GetSexPhrase("","а") +" Законов Города. Надеюсь, что дальше будет лучше... Меня зовут " + GetFullName(pchar) + ".";
			link.l1.go = "FT_1";
		break;

		//ГГ принес амулет нарвалов
		case "NarvalRing_1":
			dialog.text = "Говори.";
			link.l1 = "Я тут недавно забрел"+ GetSexPhrase("","а") +" в каюту корвета 'Протектор', и совершенно случайно наш"+ GetSexPhrase("ел","ла") +" там интересный предмет...";
			link.l1.go = "NarvalRing_2";
		break;
		case "NarvalRing_2":
			dialog.text = "Что за предмет? Говори быстрей, не тяни!";
			link.l1 = "Это кольцо. Вот оно, посмотри.";
			link.l1.go = "NarvalRing_3";
		break;
		case "NarvalRing_3":
			dialog.text = "Хо-хо, да это же амулет 'нарвала'! Так, где ты его наш"+ GetSexPhrase("ел","ла") +", говоришь?";
			link.l1 = "В каюте 'Протектора'.";
			link.l1.go = "NarvalRing_4";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			BackItemName("DOjeronRing");
			BackItemDescribe("DOjeronRing");
			ref itm;
			itm = ItemsFromID("DOjeronRing");
			itm.picIndex = 2;
			itm.picTexture = "ITEMS_9";
		break;
		case "NarvalRing_3":
			dialog.text = "А тебе известно, что там было совершено убийство милиционера и плотника Андрэ Лабора?";
			link.l1 = "Слышал"+ GetSexPhrase("","а") +"...";
			link.l1.go = "NarvalRing_4";
		break;
		case "NarvalRing_4":
			dialog.text = "М-да, твоя находка ясно показывает, кто это сделал... А ты знаком"+ GetSexPhrase("","а") +" с 'нарвалами'?";
			link.l1 = "Нет, Чад. Они же к себе никого не пускают. Чуть что - сразу нападают без разговоров.";
			link.l1.go = "NarvalRing_5";
		break;
		case "NarvalRing_5":
			dialog.text = "Да уж, это правда. На своей территории они могут делать, что хотят. Там у них свои законы. А ты знаешь, как получилось, что образовались кланы?";
			link.l1 = "Расскажи, пожалуйста. С удовольствием послушаю.";
			link.l1.go = "NarvalRing_6";
		break;
		case "NarvalRing_6":
			dialog.text = "Хм, хорошо... Дело в том, что наряду с обычными людьми, в Город попадает всякое отребье. Жить с остальными в мире они не могут, поэтому и было принято решение отдать таким людям два корабля в собственность. К тому времени образовалось две группировки головорезов, они и образовали кланы 'Нарвал' и 'Каспер'.";
			link.l1 = "Понятно... А что теперь делать? Ведь получается, что 'нарвалы' причастны к убийству официального представителя власти!";
			link.l1.go = "NarvalRing_7";
		break;
		case "NarvalRing_7":
			dialog.text = "Пора избавиться от клана 'Нарвал', утомили они своей отмороженностью.";
			link.l1 = "Правильное решение, адмирал!";
			link.l1.go = "NarvalRing_8";
		break;
		case "NarvalRing_8":
			dialog.text = "Без сомнения! И я поручаю это тебе.";
			link.l1 = "Хм, что поручаешь?";
			link.l1.go = "NarvalRing_9";
		break;
		case "NarvalRing_9":
			dialog.text = "Уничтожение 'нарвалов', "+ GetSexPhrase("приятель","подруга") +". Кому же, как не тебе, выполнить это дело? Ведь это благодаря тебе мы узнали правду!";
			link.l1 = "Черт! Я как-то на такой поворот сюжета не рассчитывал"+ GetSexPhrase("","а") +"...";
			link.l1.go = "NarvalRing_10";
		break;
		case "NarvalRing_10":
			dialog.text = "Никак, сдрейфил"+ GetSexPhrase("","а") +"? Ты же пиратский кэп, что это с тобой?!";
			link.l1 = "Их много. А я хоть и был"+ GetSexPhrase("","а") +" пиратским капитаном, но не самоубийца.";
			link.l1.go = "NarvalRing_11";
		break;
		case "NarvalRing_11":
			dialog.text = "А-а, ну это мы решим. Я даю тебе троих моих людей в помощь.";
			link.l1 = "Ну, это меняет дело. Я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "NarvalRing_12";
		break;
		case "NarvalRing_12":
			dialog.text = "Отлично! Так отправляйся на 'Веласко' прямо сейчас и поработай там, как следует. Мои люди будут ждать тебя на 'Веласко'.";
			link.l1 = "Хорошо, Чад, все сделаю в лучшем виде.";
			link.l1.go = "NarvalRing_13";
		break;
		case "NarvalRing_13":
			AddQuestRecord("ISS_MainLine", "12");
			pchar.questTemp.LSC = "toDestoyAllNarval";
			int idxMent;
			pchar.questTemp.LSC.qtyOfficers = 0;
			string sOffName;
			for (i=1 ; i<=3; i++)
			{
				idxMent = GetCharacterIndex("Ment_" + i);
				if (idxMent != -1)
				{
					ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "officers", "officer_"+i);
					characters[idxMent].Dialog.CurrentNode = "OffNarval";
					characters[idxMent].cityTape = "quest"; //тип нпс
					LAi_SetStayTypeNoGroup(&characters[idxMent]);
					pchar.questTemp.LSC.qtyOfficers = sti(pchar.questTemp.LSC.qtyOfficers) + 1;
				}
			}
			pchar.quest.NavalEnterOfficers.win_condition.l1 = "location";
			pchar.quest.NavalEnterOfficers.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.NavalEnterOfficers.function = "NavalEnterOfficers";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//клан Нарвал уничтожен
		case "DestrNarval_1":
			dialog.text = "Ну что же, это хорошо. А как там мои люди?";
			iTemp = 0;
			for (i=1 ; i<=3; i++)
			{
				if (GetCharacterIndex("Ment_" + i) != -1)
				{
					iTemp++;
				}
			}
			if (iTemp == 0)
			{
				link.l1 = "Все погибли, к сожалению. Мне очень жаль...";
				link.l1.go = "DestrNarval_Bad";
			}
			else
			{
				if (iTemp == sti(pchar.questTemp.LSC.qtyOfficers))
				{
					link.l1 = "Да все нормально. Все живы и здоровы, возвращаю их тебе в целости и сохранности.";
					link.l1.go = "DestrNarval_Ok";
				}
				else
				{
					link.l1 = "Потери имеются, но погибли не все. Оставшихся в живых возвращаю.";
					link.l1.go = "DestrNarval_BadOk";
				}
				DeleteAttribute(pchar, "questTemp.LSC.qtyOfficers");
			}
		break;
		case "DestrNarval_Bad":
			dialog.text = "М-да, печально... Однако, задача выполнена, 'нарвалы' уничтожены, а это главное. Так что все в порядке.";
			link.l1 = "Ну да, все путем, как говорится...";
			link.l1.go = "DestrNarval_Bad1";
		break;
		case "DestrNarval_Bad1":
			dialog.text = "Ну что же, отлично. Я тебя больше не задерживаю, ты можешь идти.";
			link.l1 = "Хм... Ну, спасибо, адмирал...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "16");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
		break;
		case "DestrNarval_Ok":
			dialog.text = "Отлично! За хорошо сделанную работу, я, пожалуй, подкину тебе деньжат. Сто тысяч золотых! Забирай, они твои.";
			link.l1 = "Хм, мне здесь пока деньги не нужны, но все равно спасибо тебе.";
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "14");
			AddMoneyToCharacter(pchar, 100000);
		break;
		case "DestrNarval_Ok1":
			dialog.text = "Не за что! Ну, я тебя больше не задерживаю, так что можешь спокойно заниматься своими делами.";
			link.l1 = "Хм... Хорошо.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
		break;
		case "DestrNarval_BadOk":
			dialog.text = "М-да, неприятно несколько... Ну да ладно, все-таки это была резня, а не легкая прогулка по палубе. В общем, я рад, что все кончилось хорошо. Хочу подкинуть тебе деньжат за работу. Десять тысяч золотых!";
			link.l1 = "Ну, деньги здесь особо не нужны... Но все равно спасибо.";
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "15");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			AddMoneyToCharacter(pchar, 10000);
		break;
		//подслушивание в погребке
		case "Interception":
			sld = characterFromId("Blaze");
			bool bOk = false;
			float fAng;
			GetCharacterAy(sld, &fAng);
			if (fAng > -1.35 && fAng < -0.28) bOk = true;
			if (fAng > 1.8 && fAng < 2.9) bOk = true;
			if (sti(sld.questTemp.LSC.itemState) && bOk)
			{
				dialog.text = "Рад тебя видеть, адмирал.";
				link.l1 = "Как дела у клана 'Каспер?'";
				link.l1.go = "Interception_1";
				sld.questTemp.LSC = "InterceptionOk";
				sld.questTemp.LSC.knowMechanic = true; //флаг ГГ знает о Механике
			}
			else
			{
				dialog.text = "Рад тебя видеть, адмирал.";
				link.l1 = "Тихо... Кажется, за решеткой кто-то есть. Поговорим в другом месте.";
				link.l1.go = "exit";
				sld.questTemp.LSC = "InterceptionYouSeen";
				AddDialogExitQuestFunction("LCS_EndScriptInterception");
			}
		break;
		case "Interception_1":
			sld = characterFromId("Blaze");
			dialog.text = "Неплохо. Особенно после того, как ты раздавил конкурентов.";
			link.l1 = "Хе-хе... Ты знаешь, а ведь все случилось само собой. Я, так сказать, только показал на них пальцем "+ NPCharSexPhrase(sld, "этому идиоту","этой наглой девке") +"...";
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			sld = characterFromId("Blaze");
			dialog.text = ""+ NPCharSexPhrase(sld, "Какому идиоту","Какой такой наглой девке") +"?";
			link.l1 = "Да "+ NPCharSexPhrase(sld, "этому новому гражданину","этой новой гражданке") +", " + GetFullName(sld) + " "+ NPCharSexPhrase(sld, "его","ее") +" зовут. Ты, наверное, слышал, что убили одного милиционера и нашего плотника. Так вот, "+ NPCharSexPhrase(sld, "этот новый гражданин принес","эта новая гражданка принесла") +" мне амулет нарвалов и сказал"+ NPCharSexPhrase(sld, "","а") +", что наш"+ NPCharSexPhrase(sld, "ел","ла") +" его на месте убийства. Хоть это и шито белыми нитками, я не стал долго разбираться с этим делом, так как подвернулся удобный случай осуществить давно задуманное, не навлекая на себя подозрения. Послал "+ NPCharSexPhrase(sld, "этого 'героя'","эту 'героиню'") +" на разборки, дал "+ NPCharSexPhrase(sld, "ему","ей") +" еще людей из милиции в подмогу.";
			link.l1.go = "Interception_4";
		break;
		case "Interception_4":
		sld = characterFromId("Blaze");
			dialog.text = ""+ NPCharSexPhrase(sld, "","Вот это девка! ") +"Ну, то, что он"+ NPCharSexPhrase(sld, "","а") +" на тебя поработал"+ NPCharSexPhrase(sld, "","а") +" – это прекрасно. Но ты, надеюсь, не ввел "+ NPCharSexPhrase(sld, "его","ее") +" в курс наших дел?";
			link.l1 = "Нет, я не доверяю "+ NPCharSexPhrase(sld, "ему","ей") +". На Большой земле он"+ NPCharSexPhrase(sld, "","а") +" был"+ NPCharSexPhrase(sld, "","а") +" каперским капитаном, а таких людей всегда нужно опасаться. Одно дело использовать "+ NPCharSexPhrase(sld, "его","ее") +" в своих интересах, а другое – подключать к нашему делу.";
			link.l1.go = "Interception_5";
		break;
		case "Interception_5":
			dialog.text = "Кстати, о нашем деле. Уже много всего собрано, моим ребятам не терпится прокутить свою долю в борделях Карибского моря. Когда мы начнем приготовления к отплытию из этого чертова места?";
			link.l1 = "Пока рано, я еще не собрал достаточно денег.";
			link.l1.go = "Interception_6";
		break;
		case "Interception_6":
			dialog.text = "Каррамба, да от денег и ценностей у меня сундуки ломятся! А тебе все мало?!!";
			link.l1 = "Не повышай на меня голос – кадык вырву!..";
			link.l1.go = "Interception_7";
		break;
		case "Interception_7":
			dialog.text = "Извини, адмирал, подобного не повторится...";
			link.l1 = "Смотри у меня! А теперь слушай внимательно. Может, для посещения борделей и покупки какой-нибудь халупы денег и хватит, но у меня совсем другие планы на Большой земле. Я хочу стать губернатором, а для этого мне надо ехать в Лондон и раздавать там деньги направо и налево без счета! Теперь тебе понятно?";
			link.l1.go = "Interception_8";
		break;
		case "Interception_8":
			dialog.text = "Понятно. Но и ты пойми нас. Мы столько времени работаем с тобой, собираем ценности и деньги, а мы даже еще не начали строить корабль! Я с трудом удерживаю людей под контролем.";
			link.l1 = "А мы и не сможем начать постройку, ведь наш плотник убит. Можешь так и сказать своим людям.";
			link.l1.go = "Interception_9";
		break;
		case "Interception_9":
			dialog.text = "М-да, а они у меня собирают чертежи кораблей, инструменты для постройки... И что теперь делать? Может, заставить Механика?";
			link.l1 = "Я против. Этот безумец ненадежен, а своими бредовыми речами он кому хочешь мозги запудрит. Твои люди, кстати, с ним не общаются?";
			link.l1.go = "Interception_10";
		break;
		case "Interception_10":
			dialog.text = "Нет, я за этим строго слежу. Механик не вылезает из своей конуры.";
			link.l1 = "Хорошо... Значит, своим людям скажешь, что строить корабль начнем, как только появится новый плотник. Хе-хе, следующему дровосеку повезет...";
			link.l1.go = "Interception_11";
		break;
		case "Interception_11":
			dialog.text = "Оставишь ему жизнь?";
			link.l1 = "Оставлю, ведь таков Закон! Ха-ха! Ну что же, я думаю, так мы уладим текущие проблемы.";
			link.l1.go = "Interception_12";
		break;
		case "Interception_12":
			dialog.text = "Полагаю, все будет нормально.";
			link.l1 = "Отлично. Отправляйся в клан и держи руку на пульсе.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LCS_EndScriptInterception");
		break;

		case "BarmenDead_1":
			dialog.text = "Говори.";
			link.l1 = "Я считаю, что должно быть проведено расследование.";
			link.l1.go = "BarmenDead_2";
		break;
		case "BarmenDead_2":
			dialog.text = "Хм, хорошая мысль. Может быть, ты и сейчас пойдешь на место убийства и найдешь что-нибудь эдакое, что укажет нам на преступника? Не желаешь?";
			link.l1 = "Может, и пойду!";
			link.l1.go = "BarmenDead_3";
		break;
		case "BarmenDead_3":
			dialog.text = "Иди, "+ GetSexPhrase("друг мой","подруга") +", и ищи, как следует. Только на этот раз я не буду так легковерен... Ты меня понял"+ GetSexPhrase("","а") +"?";
			link.l1 = "Хм, не очень...";
			link.l1.go = "BarmenDead_4";
		break;
		case "BarmenDead_4":
			dialog.text = "Сейчас, прежде чем принимать решение наказать кого-то, я проведу собственное дознание.";
			link.l1 = "Ага, теперь понял"+ GetSexPhrase("","а") +". Дознание – это то, чего я добиваюсь. Поставишь меня в известность о ходе следствия?";
			link.l1.go = "BarmenDead_5";
		break;
		case "BarmenDead_5":
			dialog.text = "Это вряд ли. И вообще, мне не очень понятно твое рвение. Вы что, друзья-товарищи с Хиллом были? Что вас связывает?";
			link.l1 = "Да ничего особенного. Просто мы общались с ним...";
			link.l1.go = "BarmenDead_6";
		break;
		case "BarmenDead_6":
			dialog.text = "Раз так, то и не лезь в это дело. Ты в Городе – пустое место. Не бери на себя лишнего, можешь надорваться. Понятно?";
			link.l1 = "Понятно, адмирал.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekOldCitizen";
			AddQuestRecord("ISS_MainLine", "27");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ел", "ла"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("ся", "ась"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("", "ла"));
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1          = "location";
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_SaveSesilGalard.function                  = "LSC_SaveSesilGalard";
		break;
		//замочили касперов
		case "CasperDead_1":
			dialog.text = "Какое совпадение! Ну, говори, что там на 'Сан Габриэле' произошло?";
			link.l1 = "Ну, помнишь, ты говорил, чтобы я самостоятельно занял"+ GetSexPhrase("ся","ась") +" убийством Хилла Брюннера?";
			link.l1.go = "CasperDead_2";
		break;
		case "CasperDead_2":
			dialog.text = "Я такое говорил? Ты что, сбрендил"+ GetSexPhrase("","а") +"?!";
			link.l1 = "Ну, ты мне это не поручал, но и не запрещал. Так что я, с твоего разрешения, пош"+ GetSexPhrase("ел","ла") +" искать улики. Ну, и заш"+ GetSexPhrase("ел","ла") +" на 'Сан Габриэль'.";
			link.l1.go = "CasperDead_3";
		break;
		case "CasperDead_3":
			dialog.text = ""+ GetSexPhrase("Идиот","Ах ты, черт возьми") +"! Я что, не говорил тебе не лезть туда?";
			link.l1 = "Нет, ты говорил, что у них на 'Сан Габриэле' свои законы. Я же не знал"+ GetSexPhrase("","а") +", что законы эти такие кровожадные! В общем, набросились они на меня, ну и мне пришлось защищаться...";
			link.l1.go = "CasperDead_4";
		break;
		case "CasperDead_4":
			dialog.text = "И что?";
			link.l1 = "Защитил"+ GetSexPhrase("ся","ась") +". Клана 'Каспер' более не существует... Так же, впрочем, как и клана 'Нарвал'. Город теперь свободен он негодяев всех мастей!";
			link.l1.go = "CasperDead_5";
		break;
		case "CasperDead_5":
			dialog.text = "Поверить не могу...";
			link.l1 = "Зачем верить? Можно проверить.";
			link.l1.go = "CasperDead_6";
		break;
		case "CasperDead_6":
			dialog.text = "Да ты "+ GetSexPhrase("дьявол какой-то","сущая дьяволица") +"! Два клана пустил"+ GetSexPhrase("","а") +" под нож!";
			link.l1 = "Осмелюсь заметить, что один из них - по твоему прямому приказанию.";
			link.l1.go = "CasperDead_7";
		break;
		case "CasperDead_7":
			dialog.text = "Н-да... Кого-нибудь наш"+ GetSexPhrase("ел","ла") +" на 'Сан Габриэле'? Кроме 'касперов', конечно.";
			link.l1 = "Да. Человек по имени Хенрик Ведекер передавал тебе привет.";
			link.l1.go = "CasperDead_8";
		break;
		case "CasperDead_8":
			dialog.text = "Значит, Механик жив...";
			link.l1 = "А чего с ним будет? Он же на меня не нападал, ну и я его не тронул"+ GetSexPhrase("","а") +"...";
			link.l1.go = "CasperDead_9";
		break;
		case "CasperDead_9":
			dialog.text = "Хм, не тронул"+ GetSexPhrase("","а") +"... Вот что, "+ GetSexPhrase("'крутой Уокер'","крутая девчонка") +"! Ты меня всерьез утомил"+ GetSexPhrase("","а") +" своими выходками. Я сейчас очень зол на тебя и подумываю, не отправить ли тебя на дно с грузом на шее!";
			link.l1 = ""+ GetSexPhrase("Адмирал, я больше так не буду!..","Я вообще-то выполняла работу твоих милицейских бездельников. 'Касперы' - преступники, и я...") +"";
			link.l1.go = "CasperDead_10";
		break;
		case "CasperDead_10":
			dialog.text = "Заткнись, "+ GetSexPhrase("полудурок","наглая девчонка") +"!\nТы еще жив"+ GetSexPhrase("","а") +" только потому, что я хочу закончить эту череду убийств. Кто бы ни был в этом виноват, я не хочу вести дальнейших расследований. Допустим, что во всем виноваты 'касперы', и на этом поставим точку. Тебе ясно?";
			link.l1 = "Да, адмирал.";
			link.l1.go = "CasperDead_11";
		break;
		case "CasperDead_11":
			dialog.text = "Хорошо. Ты долж"+ GetSexPhrase("ен","на") +" понимать, что теперь в Городе нет исключений. Кланов больше нет, соответственно теперь нет территорий, на которые не распространяется Закон Города. Тебе ясно?";
			link.l1 = "Да, адмирал.";
			link.l1.go = "CasperDead_12";
		break;
		case "CasperDead_12":
			dialog.text = "Если ты еще кого-нибудь хоть пальцем тронешь...";
			link.l1 = "Адмирал, я знаю Закон. Право на жизнь для граждан - это все очень правильно.";
			link.l1.go = "CasperDead_13";
		break;
		case "CasperDead_13":
			dialog.text = "Ну, смотри у меня!.. Ведекеру передай, чтобы он сидел себе на 'Сан Габриэле' и сопел в трубочку. Будет шататься по городу и пугать народ своими бреднями - брошу его за решетку!\nХотя, я лучше кого-нибудь из милиции пошлю к нему. Свобод"+ GetSexPhrase("ен","на") +".";
			link.l1 = "Спасибо, адмирал! Честное слово, я хотел"+ GetSexPhrase("","а") +" как лучше...";
			link.l1.go = "CasperDead_14";
		break;
		case "CasperDead_14":
			dialog.text = "Убирайся!!";
			link.l1 = "До свидания, Чад.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "seekMillionAndHalf";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Посмотрим. О каких товарах речь?",
				"Ты уже спрашивал"+ GetSexPhrase("","а") +" об этом.",
				"Уже спрашивал"+ GetSexPhrase("","а") +"...",
                "Ты уже спрашивал"+ GetSexPhrase("","а") +" меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны порох и оружие.",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.",
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Зачем?";
			link.l1 = "Нужно, адмирал...";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Твои шашни с Ведекером до добра не доведут! Ты обязан"+ GetSexPhrase("","а") +" соблюдать положения Закона Города.";
			link.l1 = "Я и соблюдаю. В Законе ничего нет о запрете искать оружие или порох.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Все оружие и порох с вновь поступающих кораблей я изымаю. Все находится у меня на складе в резиденции.";
			link.l1 = "Может, поделишься?..";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "С какой это стати? На мой вопрос, зачем тебе это, ты ответа не дал"+ GetSexPhrase("","а") +". А вдруг ты хочешь заложить куда-нибудь бочонок с порохом, а потом взорвать?";
			link.l1 = "Да ты что, адмирал, я же не сумасшедш"+ GetSexPhrase("ий","ая") +".";
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = "В целях безопасности Города я изымаю порох и оружие. Ты ничего не получишь.";
			link.l1 = "Ясно...";
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = "Знаешь, ты стал"+ GetSexPhrase("","а") +" популяр"+ GetSexPhrase("ен","на") +" среди граждан. Если бы не это обстоятельство, думаю, что скормил бы тебя тем тварям, что копошатся под городом.";
			link.l1 = "А ты их видел, тварей этих?";
			link.l1.go = "SeekGoods_7";
		break;
		case "SeekGoods_7":
			dialog.text = "Никто их не видел. А кто видел, тот смотрел на них в последний раз в жизни.";
			link.l1 = "Я их видел"+ GetSexPhrase("","а") +", адмирал...";
			link.l1.go = "SeekGoods_8";
		break;
		case "SeekGoods_8":
			dialog.text = "Да? Где?";
			link.l1 = "На дне.";
			link.l1.go = "SeekGoods_9";
		break;
		case "SeekGoods_9":
			dialog.text = "Н-да... Вот теперь я точно понимаю, что тебе не стоит даже близко подходить к пороху. Общение с Механиком пагубно влияет на твою психику.\nЯ наблюдаю за тобой. Учти, как только ты допустишь малейшую оплошность - я отправлю тебя на 'Тартарус', в тюрьму. Ты меня понял"+ GetSexPhrase("","а") +"?";
			link.l1 = "Понял"+ GetSexPhrase("","а") +", адмирал...";
			link.l1.go = "SeekGoods_10";
		break;
		case "SeekGoods_10":
			dialog.text = "А теперь иди, я тебя не задерживаю.";
			link.l1 = "Хорошо, Чад. Но зря ты так...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "57");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.LSC.additional.powder = true; //флаг на дачу квеста ментом
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("И что?",
				"Мы уже говорили об этом.",
				"Не хочу ничего слышать об этом!",
                "Убирайся!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Есть основание полагать, что этот шторм будет очень сильным. Адмирал, город может разрушиться.",
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаешь...",
				"Хорошо-хорошо...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Н-да, все-таки крыша у тебя поехала...";
			link.l1 = "Я в абсолютно трезвом уме, Чад. А вот тебе надо бы раскрыть глаза и признаться, прежде всего самому себе, что дела плохи.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Что?!!";
			link.l1 = "Тебе лучше многих известно, что такое Город. Он держится непонятно на чем! Ты подвергаешь риску жизни людей, запрещая им пытаться уплыть отсюда.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Еще ты мне порассуждай о Городе! Механик - человек грамотный, но трус и паникер. Мы здесь столько штормов видели, что его теории уже просто смешны. Я говорил ему, чтобы он держал свои мысли при себе...";
			link.l1 = "А он и держит... Послушай меня, Чад, сюда идет не шторм, а настоящая буря...";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "А ты откуда знаешь?";
			link.l1 = "Хенрик сказал. У него есть прибор, который предсказывает штормы.";
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = "Я этого бреда от Механика вдоволь наслушался. Вот что, "+ GetSexPhrase("приятель","подруга") +", я тебе скажу. И советую хорошенько это запомнить, так как я предупреждаю тебя в последний раз.\nПока я здесь адмирал, я и буду решать, когда мы уйдем из Города. Понятно?";
			link.l1 = "Чад, я не претендую стать адмиралом. Не скрою, раньше хотел"+ GetSexPhrase("","а") +"... Но теперь вопрос стоит о жизни и смерти.";
			link.l1.go = "SeekCrew_6";
		break;
		case "SeekCrew_6":
			dialog.text = "Раньше хотел"+ GetSexPhrase("","а") +"? Хм, я так и знал, что ты не успокоишься...";
			link.l1 = "Адмирал, мы не о том говорим. Нужно спасать свои шкуры, и способ есть! Все твои планы так и останутся нереализованными, если Ведекер прав.";
			link.l1.go = "SeekCrew_7";
		break;
		case "SeekCrew_7":
			dialog.text = "Хех, ты мне еще о моих планах расскажи!\nНу, что же, спасибо за познавательную беседу. А теперь можешь быть свобод"+ GetSexPhrase("ен","на") +". И не вздумай пугать граждан, а не то я тебе башку откручу! Учти, что терпеть тебя я больше не намерен.";
			link.l1 = "Ну что же, я сделал"+ GetSexPhrase("","а") +" все, что мог"+ GetSexPhrase("","ла") +". Жаль, что ты не слушаешь меня...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "60");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
		break;
		//финальный диалог
		case "fightTalking":
			dialog.text = "Твое время вышло. Ты готов"+ GetSexPhrase("","а") +" к смерти?";
			link.l1 = "Гм.. ну, я как-то специально не готовил"+ GetSexPhrase("ся","ась") +"...";
			link.l1.go = "fightTalking_1";
		break;
		case "fightTalking_1":
			dialog.text = "У тебя есть пара секунд.";
			link.l1 = "А где Ведекер?";
			link.l1.go = "fightTalking_2";
		break;
		case "fightTalking_2":
			dialog.text = "Ты неправильно их использовал"+ GetSexPhrase("","а") +".";
			link.l1 = "Эх, жаль...";
			link.l1.go = "fightTalking_3";
		break;
		case "fightTalking_3":
			LAi_LocationFightDisable(loadedLocation, false);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorTypeNoGroup(NPChar);
			//LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuestFunction("LSC_figtInResidence");
            DialogExit();
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat("А тебе что до этого?",
				"Я уже все сказал.",
				"Вроде бы, мы все прояснили.",
                "Ну и "+ GetSexPhrase("болван","дура") +" же ты, "+ GetSexPhrase("приятель","подруга") +"!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Хм... Ну, интересуюсь.",
				"Да-да, я помню.",
                "Конечно.",
				"И верно, "+ GetSexPhrase("болван еще тот","дура еще та") +". Зачем одно и тоже спрашиваю - сам"+ GetSexPhrase("","а") +" не пойму...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = "Больше не интересуйся. Это не твое дело.";
			link.l1 = "Ну, я же гражданин Города, так сказать...";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "Это все. Я не хочу больше говорить об этом кретине!";
			link.l1 = "Хорошо, адмирал, как скажешь.";
			link.l1.go = "exit";
		break;

		case "ELTHusb_SF":
			dialog.text = "Ну, отнеси ему бутылочку вина...";
			link.l1 = "Хе, можно и так. Только я хочу помочь освободить его.";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "Нет, "+ GetSexPhrase("приятель","" + pchar.name + "") +", этому не бывать! Хватит, от него устал уже весь Город. Он сгниет в своей клетке.";
			link.l1 = "Ты что, решил его убить?";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "Я имею на это право!\nНо нет, он просто получил пожизненный срок.";
			link.l1 = "Черт, да что же он сделал такого? Адмирал, расскажи, пожалуйста.";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "Хорошо, расскажу. Хотя и не понимаю, зачем тебе это нужно.\nЭтот храбрец приставил к моему горлу нож и потребовал немедленно отпустить его домой, в Плимут.";
			link.l1 = "Слушай, он был пьян и ничего не помнит. Может, ты войдешь в положение и простишь его?";
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = "Нет уж, на это пусть не надеется. И, кстати, я уведомил об этом его жену, Элис. Пьяница и дебошир должен сидеть в тюрьме! Зубочистка, которой он тут размахивал, меня не волнует.";
			link.l1 = "Хм, и я тоже думаю, что для тебя его нож - что комариный укус.";
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = "Но меня озадачивает то, что он себя не контролирует в пьяном виде. А вдруг завтра, после очередного посещения таверны, он решит подпалить какой-нибудь корабль? В общем, Тейлора нужно изолировать от общества.";
			link.l1 = "Черт, похоже, ты прав...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toWaitress";
			AddQuestRecord("ISS_ElisHusband", "7");
		break;

		case "ELTHusb_good":
			dialog.text = "Ты уже надоел"+ GetSexPhrase("","а") +"...";
			link.l1 = "Послушай, это Жиль Бару отправил Тейлора к тебе для разговора по душам.";
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = "Вот как?";
			link.l1 = "Ага. Жиль Бару обещал мне поговорить с тобой и извиниться за неудачную шутку.";
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = "Ну что же, это несколько меняет дело\nПожалуй, дам Тейлору еще один шанс остепениться.";
			link.l1 = "Адмирал, я считаю, что это очень правильное решение.";
			link.l1.go = "ELTHusb_good_3";
		break;
		case "ELTHusb_good_3":
			dialog.text = "Я отправлю милиционера на 'Тартарус' к Габриэлю, а ты можешь навестить Элис и сказать ей, что я выпускаю Максима.";
			link.l1 = "Отлично! Я так и сделаю. Спасибо, адмирал...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toElisGood";
			AddQuestRecord("ISS_ElisHusband", "10");
			sld = characterFromId("MaximTailor");
			ChangeCharacterAddress(sld, "none", "");
		break;
		//квест со скелетом Декстера
		case "LostDecster":
			dialog.text = "По поводу кого?!";
			link.l1 = "Лейтона Декстера.";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "Хм... Ну, что же, задавай свой вопрос.";
			link.l1 = "Куда он делся? Никто не знает. А вы, вроде, были дружны...";
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = "Ну хорошо, я скажу тебе.\nЛейтон Декстер оказался очень жадным человеком. Он откусил больше, чем сумел проглотить. Поэтому он наказан.";
			link.l1 = "Как это, наказан? Где он сейчас?";
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = "Он охраняет мои деньги.";
			link.l1 = "И это наказание?";
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = "В некотором роде\nЯ удовлетворил твое любопытство?";
			link.l1 = "Хм... Ну, в некотором роде.";
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = "Хорошо. А теперь ты удовлетвори мое. К чему эти расспросы о Лейтоне?";
			link.l1 = "Адмирал, ничего особенного. Праздное любопытство, не более того. Осваиваю Город, знакомлюсь с людьми...";
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = "Понятно. По поводу Декстера, ты, надеюсь, понял"+ GetSexPhrase("","а") +", что он занят. Поэтому его для знакомства можешь не искать.";
			link.l1 = "Хорошо, адмирал, как скажешь. Спасибо за разговор.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "seekBox";
			AddQuestRecord("LSC_findDekster", "5");
		break;

	}
}
