// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Вопросы, " + GetAddress_Form(NPChar) + "?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Хм, уж не пристаете ли вы ко мне, " + GetAddress_Form(NPChar) + "? ","Опять со странными вопросами? Девушка, выпили бы вы рому, что ли...") +"", "В течение этого дня вы уже третий раз говорите о каком-то вопросе..."+ GetSexPhrase(" Это знаки внимания?","") +"",
                          "Опять вопросы будете задавать, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Да нет, что ты, красавица...",
                      "Никак нет, дорогуша, склероз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHolWaitress"))
			{
				DeleteAttribute(pchar, "Whisper.FindDesouzaHolWaitress")
				link.l1 = "Твой начальник, "+GetCharacterFullName("Marigo_tavernkeeper")+", сказал мне, что к тебе подходили подозрительные типы с клеймом в форме распятия на руке. Я их ищу. Можешь подробней рассказать о чем они спрашивали?";
				link.l1.go = "FindDesouzaHolWaitress";
				break;
			}
		break;

		case "FindDesouzaHolWaitress":
			dialog.text = "Были такие. Они, кстати, тоже вас искали. По крайней мере, вы подходите под описание, что они мне дали.";
			link.l1 = "А для чего они искали кого-то, похожего на меня?";
			link.l1.go = "FindDesouzaHolWaitress_1";
		break;
		case "FindDesouzaHolWaitress_1":
			dialog.text = "Этого они, увы, не сказали. Но они не только вас искали, у них был список из нескольких десятков человек с нетипичной внешностью, большая часть из которых - испанцы. Они сказали, что все эти люди - преступники и их разыскивают. Одного, как оказалось, недавно видели в городе, так что эти клейменные отправились за ним. Это было буквально пару часов назад.";
			link.l1 = "И в каком направлении они ушли искать этого типа?";
			link.l1.go = "FindDesouzaHolWaitress_2";
		break;
		case "FindDesouzaHolWaitress_2":
			dialog.text = "Капитан, мне немного не по себе от всей этой истории. Скажите, для чего они вас разыскивают?";
			link.l1 = "У меня с ними старые счеты. Их лидер - садист и безумец. Он пытает людей ради забавы. Эти люди опасны и их нужно остановить.";
			link.l1.go = "FindDesouzaHolWaitress_3";
		break;
		case "FindDesouzaHolWaitress_3":
			dialog.text = "Мне все еще ничего не ясно, но почему-то хочется вам верить. Элихио тоже не был похож на опасного преступника, которым его описывали эти люди.";
			link.l1 = "Элихио? Это его ищут инквизиторы?";
			link.l1.go = "FindDesouzaHolWaitress_4";
		break;
		case "FindDesouzaHolWaitress_4":
			dialog.text = "Так это были инквизиторы? Что же вы сразу не сказали, капитан? Этих католических подонков нужно гнать поганой метлой из нашей протестантской колонии! Инквизиторы! Бедный Элихио...";
			link.l1 = "Скажи, куда они ушли. Быть может, я еще сумею его спасти.";
			link.l1.go = "FindDesouzaHolWaitress_5";
		break;
		case "FindDesouzaHolWaitress_5":
			dialog.text = "Один из постояльцев говорил, что Элихио ушел в пещеру, проверить слухи о каком-то кладе.";
			link.l1 = "Спасибо за информацию, я побежала.";
			link.l1.go = "exit";
			PChar.quest.WhisperHuntersCaveEntrance.win_condition.l1 = "location";
			PChar.quest.WhisperHuntersCaveEntrance.win_condition.l1.location = "Marigo_CaveEntrance";
			PChar.quest.WhisperHuntersCaveEntrance.function = "WhisperHuntersCaveEntrance";
			AddQuestRecord("WhisperQuestline", "5");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

