
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
		case "First time":
			dialog.text = "Не хочу разговаривать.";
			link.l1 = "Хм, понятно...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//встреча в бухте с перцем, который валит из Тено
		case "Shore53":
			pchar.defaultanimation = MainChAnim;
			dialog.text = "Сеньор"+ GetSexPhrase("","ита") +", уходите отсюда! Уплывайте немедленно!";
			link.l1 = "В чем дело?";
			link.l1.go = "Shore53_1";
		break;
		case "Shore53_1":
			dialog.text = "Погибли все, их пожрало адское пламя!!!";
			link.l1 = "Кто погиб?";
			link.l1.go = "Shore53_2";
		break;
		case "Shore53_2":
			dialog.text = "А-а-а, зачем мы вообще туда пошли?..";
			link.l1 = "Дружище, успокойся! Расскажи медленно и по порядку, что случилось.";
			link.l1.go = "Shore53_3";
		break;
		case "Shore53_3":
			dialog.text = "Хорошо, сеньор"+ GetSexPhrase("","ита") +". Меня зовут Сильвио Риччи\nВсе началось с того, что дон Эстебан нанял меня, наряду с прочими, для поиска нового Эльдорадо. Мы высадились в этой бухте и пошли к индейскому городу, который сам Кортес разграбил больше сотни лет назад. Господи, за что?!!";
			link.l1 = "Так, опять началось... Немедленно прекрати!!!";
			link.l1.go = "Shore53_4";
		break;
		case "Shore53_4":
			dialog.text = "Хорошо, сеньор"+ GetSexPhrase("","ита") +"\nНеделю назад в эти джунгли вошли почти 50 человек. А сейчас вышел оттуда один я.";
			link.l1 = "А где остальные?";
			link.l1.go = "Shore53_5";
		break;
		case "Shore53_5":
			dialog.text = "Они мертвы, сеньор"+ GetSexPhrase("","ита") +"! Их пожрало адское пламя!";
			link.l1 = "Что?!";
			link.l1.go = "Shore53_6";
		break;
		case "Shore53_6":
			dialog.text = "Я говорю истинную правду, сеньор"+ GetSexPhrase("","ита") +"! Огонь, возникающий ниоткуда, на этом мосту нет ни малейшего признака того, что может гореть. Один камень!\nСеньор"+ GetSexPhrase("","ита") +", этот огонь зажигает там сам дьявол!";
			link.l1 = "Ты что, дьявола там видел?";
			link.l1.go = "Shore53_7";
		break;
		case "Shore53_7":
			dialog.text = "Может, это и был дьявол!\nТам на берегу, у города, стоит раскрашенный индеец. Нас осталось человек десять, тех, кто выжил в адском огне. Мы собрались уже идти обратно, когда Педро решил снять золотые побрякушки с этого черномазого. Только он протянул к нему руки - тут же получил дубиной по голове. И голова лопнула, как спелый арбуз!\nА потом этот дьявол стал бегать за нами и бить своей дубиной всех подряд. Один удар - и голова разлетается на куски. Только я и убежал...";
			link.l1 = "А где же ваш начальник, дон Эстебан, кажется?";
			link.l1.go = "Shore53_8";
		break;
		case "Shore53_8":
			dialog.text = "Сгорел в адском пламени.";
			link.l1 = "М-да, бесславная кончина...";
			link.l1.go = "Shore53_9";
		break;
		case "Shore53_9":
			dialog.text = "Сеньор"+ GetSexPhrase("","ита") +", не ходите туда. Это место проклято!";
			link.l1 = "Я все-таки рискну.";
			link.l1.go = "Shore53_10";
		break;
		case "Shore53_10":
			dialog.text = "Ну, дело ваше, а с меня хватит. Прощайте, сеньор"+ GetSexPhrase("","ита") +"!";
			link.l1 = "Прощай...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_startInShore_2");
		break;
	}
}
