// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
			{
				link.l1 = "Офицер, я вижу, у вас очень озабоченный вид. Могу я чем-то помочь?";
				link.l1.go = "zpq_prs1";
			}
			if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
			{
				link.l2 = "Спешу сообщить, что груз пороха доставлен. Судно готово встать под разгрузку.";
				link.l2.go = "zpq_ex";
			}
			if (pchar.questTemp.zpq == "begin")
			{
				link.l3 = "Хочу отказаться от нашего договора по доставке пороха. Это оказалось слишком хлопотно...";
				link.l3.go = "zpq_fld2";
			}
			link.l4 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Всего хорошего.";
			link.l4.go = "Exit";
		break;

		case "zpq_prs1":
		if(!isBadReputation(pchar, 70))
		{
			dialog.text = "Хм, возможно-возможно... пожалуй, благодаря вашей хорошей репутации, рискну вам довериться. В противном случае, я бы даже не стал разговаривать на подобную тему. Дело в том, что нам нужна довольно большая партия непростого груза, так что вам понадобится судно с большим трюмом и готовность рисковать. И вы должны пообещать, что полученная информация останется закрытой для посторонних ушей\nЕсли вас смущает хотя бы одно из условий - скажите об этом сразу. Я думаю, вы меня понимаете...";
			link.l1 = "Достаточно интригующе звучит. И хоть я не догадываюсь, о каком грузе идет речь, все же готов"+ GetSexPhrase("","а") +" рискнуть, если оплата будет достойной. В любом случае, я даю слово.";
			link.l1.go = "zpq_prs2";
			link.l2 = "Нет, пожалуй... Данное вам слово обяжет меня взяться за дело, которое уже представляется мне весьма сомнительным. Я не стану связываться с этим...";
			link.l2.go = "zpq_fld";
		}
		else
		{
			dialog.text = "Ваша репутация не позволяет мне вести с вами сколько-нибудь серьёзных дел. Прошу вас освободить помещение. Мы сами в состоянии решить свои проблемы.";
			link.l1 = "Ну что ж, решайте...";
			link.l1.go = "exit";
		}
		break;
		case "zpq_fld":
			dialog.text = "Ну, по крайней мере, вы отказались честно и не стали лукавить... Не смею вас задерживать.";
			link.l1 = "Прощайте.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_fld2":
			dialog.text = "Хм, признаться, не ожидал я такого ретирования. Вынужден просить вас удалиться... И помните про обещание не разглашать полученную информацию.";
			link.l1 = "Прошу меня простить...";
			link.l1.go = "exit";
    			ChangeCharacterReputation(pchar, -10);

			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_prs2":
			dialog.text = "Вот и великолепно. Дело в том, что недавний затяжной шторм подмочил изрядное количество орудийного пороха в арсеналах нашего форта. Надеюсь, вам не нужно объяснять в каком щекотливом положении мы оказались. В случае серьёзной осады, форт вряд ли сможет оказать достойный отпор, мы долго не продержимся.";
			link.l1 = "Теперь ясно, что за груз вам понадобился. И о каком количестве идёт речь?";
			link.l1.go = "zpq_prs3";
		break;
		case "zpq_prs3":
			dialog.text = "Нам нужно 50 000 картузов орудийного пороха. За всю партию я заплачу 300 000 пиастров... Это очень хорошая цена, сами понимаете. Наше положение вынуждает идти на подобные издержки, хотя мне стоило немалых усилий убедить в этом губернаторского казначея... Сезон штормов не даёт возможности воспользоваться штатными каналами снабжения, да и афишировать такой казус нам не с руки...";
			link.l1 = "Понятно... цена и впрямь хороша. Кстати, вы упомянули о каком-то риске.";
			link.l1.go = "zpq_prs4";
		break;
		case "zpq_prs4":
			dialog.text = "Я имел в виду, что такое количество пороха в трюме может быть очень опасным при транспортировке. На моей памяти было несколько случаев взрыва судов от случайной искры, а уж если в шторм попасть... При перевозке даже конвой держится подальше от такого потенциального брандера, ведь если что случится - всех в щепки разнесет!..";
			link.l1 = "Ясно... Но я слова на ветер не бросаю - считайте, что заказ принят.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Да уж, сеньор... Страшные вещи вы рассказываете... Что-то мне расхотелось в это ввязываться.";
			link.l2.go = "zpq_fld2";
		break;
		case "zpq_prs5":
			dialog.text = "Вот и прекрасно, я очень рад, что мы договорились. Рассчитаемся сразу же после доставки, можете насчет этого не волноваться\nГруз нужен не ранее, чем через неделю, как раз к этому времени вся сумма будет у меня. Хоть я понимаю, что собрать такую партию будет непросто, и ограничения по времени вам не даю, все же постарайтесь не затягивать.";
			link.l1 = "Мне всё предельно ясно, сеньор. Приступаю немедленно.";
			link.l1.go = "zpq_prs5_ok";
		break;
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		case "zpq_ex":
			dialog.text = "Ну наконец-то! Я уж подумал, что вы забыли о нашем договоре. Сейчас распоряжусь отрядить солдат для выгрузки. Обращение с порохом не терпит суеты, хе-хе!";
			link.l1 = "Это все прекрасно, сеньор, но я вынужден"+ GetSexPhrase("","а") +" напомнить об оплате.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            		pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            		pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            		pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		case "zpq_ex2":
			dialog.text = "Да-да, конечно. Вам сейчас же выплатят 150 000 пиастров, согласно нашему уговору.";
			link.l1 = "Вы, верно, шутите, сеньор?! Договор был на 300 000, и я не намерен"+ GetSexPhrase("","а") +" уступать ни пиастра!";
			link.l1.go = "zpq_ex3";
			link.l2 = "Я начинаю думать, что вы хотите меня обмануть, поэтому без своих 450 000 пиастров я отсюда не уйду!";
			link.l2.go = "zpq_ex4";
			link.l3 = "Хм... вижу, обстоятельства изменились. Что ж я готов"+ GetSexPhrase("","а") +" принять указанную сумму, чтоб не накалять обстановку.";
			link.l3.go = "zpq_ex5";
		break;
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			{
				dialog.text = "Ах да-а... точно! 300 000 пиастров. Запамятовал, прошу меня простить. Возраст, знаете ли, уже не тот, склероз... Конечно, вот ваши деньги. Приятно было иметь с вами дело. А теперь прошу меня простить, дела ждут...";
				link.l1 = "Мне тоже приятно, сеньор. Всего вам хорошего.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            			AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "Что-о?!! Забирай деньги и выметайся вон, иначе сгниёшь в этих казематах!";
				link.l1 = "Да вы, сеньор, оказывается лжец! Предлагаю по-хорошему отдать деньги, о которых мы договаривались или я забираю товар!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Прошу меня простить... Хорошо, я возьму предлагаемую сумму, и мы разойдемся.";
				link.l2.go = "zpq_ex5";
			}
		break;
		case "zpq_ex4":
				dialog.text = "Какая дерзость! Я ещё из ума не выжил и совершенно точно помню, что наш уговор был на 300 000 пи\n... Ах чёрт! тебе не удастся меня надуть!";
				link.l1 = "Не кипятитесь. Лучше подумайте о том, что у стен вашего форта стоит готовый брандер, доверху набитый порохом. Мне достаточно только свистнуть и от ваших укреплений одни руины останутся.";
				link.l1.go = "zpq_ex6";
		break;
		case "zpq_ex6":
			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			{
				dialog.text = "Гм-гм... веский аргумент. 450 000 пиастров, говорите? Вот, держите ваши деньги... А теперь прошу меня простить, дела ждут...";
				link.l1 = "Всего вам хорошего, сеньор. Прощайте.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            			AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "Что?! Я боевой офицер! Ты кого пугать вздумал"+ GetSexPhrase(", сопляк","а, соплячка") +"?! Стража, взять е"+ GetSexPhrase("го","е") +"!!";
				link.l1 = "Ну держитесь, крысы казематные...";
				link.l1.go = "zpq_ex_war";
			}
		break;
		case "zpq_ex5":
			dialog.text = "Прекрасно! Вы сделали правильный выбор. Получите деньги и прощайте. С вами приятно было иметь дело. Ха-ха-ха!";
			link.l1 = "Прощайте...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            		AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		case "zpq_ex_agry":
			dialog.text = "Ах ты мерзав"+ GetSexPhrase("ец","ка") +"!! Стража, взять е"+ GetSexPhrase("го","е") +"!!";
			link.l1 = "Аргх!! Придется забрать деньги с твоего трупа...";
			link.l1.go = "zpq_ex_war";
		break;
        	case "zpq_ex_war":

			DialogExit();

			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_Change(PIRATE);
			pchar.questTemp.zpq = "failed";
            		AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade20");
			EquipCharacterbyItem(npchar, "blade20");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass4");

			chrDisableReloadToLocation = true;

			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";

			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");

			AddSimpleRumour("Ну и дела у нас происходят!! Поговаривают, что в Кумане какой-то заключенный выбрался из казематов, перебил всю охрану форта, ограбил казну и был таков! Ну, дела-а!..", SPAIN, 5, 1);

		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

