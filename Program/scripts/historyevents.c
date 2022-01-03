// Philippe, de AoP1
#define MAX_STORY_EVENTS	100;

object HistoryEvents[MAX_STORY_EVENTS];

void ActivateHistoryEvents()
{
	FillHistoryEvents();
	//RechargeHistoryEvents();

	string sQuest = "";
	int iday, imonth, iyear;
	for(int i = 0; i<MAX_STORY_EVENTS; i++)
	{
		if (CheckAttribute(&HistoryEvents[i], "text"))
		{
			sQuest = "history_event" + "_" + i;
			iday = sti(HistoryEvents[i].day);
			imonth = sti(HistoryEvents[i].month);
			iyear = sti(HistoryEvents[i].year);

			pchar.quest.(sQuest).win_condition.l1 = "timer";
			pchar.quest.(sQuest).win_condition.l1.date.day = iday;
			pchar.quest.(sQuest).win_condition.l1.date.month = imonth;
			pchar.quest.(sQuest).win_condition.l1.date.year = iyear;
			pchar.quest.(sQuest).win_condition.l1.date.hour = rand(23);
			pchar.quest.(sQuest).win_condition = "Historical_event";
			pchar.quest.(sQuest).number = i;
		}
	}
}

void CheckHistoryEvent(string sQuest)
{
	int iNumber = sti(pchar.quest.(sQuest).number);
	//GenerateRumour("history_event", iNumber, 0, 0);//<<== Rumours.c
    GenerateRumour();
}

void FillHistoryEvents()
{
	int n = 0;

	HistoryEvents[n].text = "In England, at Edgigil, the first battle took place, which initiated the civil war.";
	HistoryEvents[n].day = 23;
	HistoryEvents[n].month = 10;
	HistoryEvents[n].year = 1642;
	n++;

	HistoryEvents[n].text = "In France, Cardinal Richelieu died (Arman Jean du Plesi).";
	HistoryEvents[n].day = 4;
	HistoryEvents[n].month = 12;
	HistoryEvents[n].year = 1642;
	n++;

	HistoryEvents[n].text = "In France, King Louis XIII died. Giulio Raimondo Mazarin is appointed first minister and regent under the young Louis XIV.";
	HistoryEvents[n].day = 14;
	HistoryEvents[n].month = 5;
	HistoryEvents[n].year = 1643;
	n++;

	HistoryEvents[n].text = "In the Battle of Nesby, the final defeat of the armies of the English King Charles I.";
	HistoryEvents[n].day = 14;
	HistoryEvents[n].month = 6;
	HistoryEvents[n].year = 1645;
	n++;

	HistoryEvents[n].text = "The troops of the parliament entered Oxford and Charles I was forced to flee to Scotland.";
	HistoryEvents[n].day = 23;
	HistoryEvents[n].month = 6;
	HistoryEvents[n].year = 1646;
	n++;

	HistoryEvents[n].text = "In the battle near Preston, Oliver Cromwell defeated the army of Scots and captured Charles I.";
	HistoryEvents[n].day = 17;
	HistoryEvents[n].month = 8;
	HistoryEvents[n].year = 1648;
	n++;

	HistoryEvents[n].text = "Conclusion of the Treaty of Westphalia, which put an end to the Thirty Years' War.";
	HistoryEvents[n].day = 24;
	HistoryEvents[n].month = 10;
	HistoryEvents[n].year = 1648;
	n++;

	HistoryEvents[n].text = "On the verdict of the court in England, King Charles I was executed. England was proclaimed a republic.";
	HistoryEvents[n].day = 30;
	HistoryEvents[n].month = 1;
	HistoryEvents[n].year = 1649;
	n++;

	HistoryEvents[n].text = "Oliver Cromwell dispelled the English Parliament and the Council of State.";
	HistoryEvents[n].day = 20;
	HistoryEvents[n].month = 4;
	HistoryEvents[n].year = 1652;
	n++;

	HistoryEvents[n].text = "England started the war with Holland.";
	HistoryEvents[n].day = 29;
	HistoryEvents[n].month = 5;
	HistoryEvents[n].year = 1652;
	n++;

	HistoryEvents[n].text = "England signed the world by Holland.";
	HistoryEvents[n].day = 20;
	HistoryEvents[n].month = 4;
	HistoryEvents[n].year = 1654;
	n++;

	HistoryEvents[n].text = "In Westminster Palace, a solemn ceremony of 'introduction' of Cromwell in the post of Lord Protector.";
	HistoryEvents[n].day = 16;
	HistoryEvents[n].month = 2;
	HistoryEvents[n].year = 1654;
	n++;

	HistoryEvents[n].text = "Coronation of Louis XIV.";
	HistoryEvents[n].day = 7;
	HistoryEvents[n].month = 6;
	HistoryEvents[n].year = 1654;
	n++;

	HistoryEvents[n].text = "As a result of disease, Oliver Cromwell died.";
	HistoryEvents[n].day = 3;
	HistoryEvents[n].month = 9;
	HistoryEvents[n].year = 1658;
	n++;

	HistoryEvents[n].text = "On the Fasagne Island on the border river Bidassoa, the Pyrenean Peace between France and Spain was signed.";
	HistoryEvents[n].day = 7;
	HistoryEvents[n].month = 11;
	HistoryEvents[n].year = 1659;
	n++;

	HistoryEvents[n].text = "General George Monk enters the troops in London and proclaims King Charles II.";
	HistoryEvents[n].day = 29;
	HistoryEvents[n].month = 5;
	HistoryEvents[n].year = 1660;
	n++;

	HistoryEvents[n].text = "In Fuenterabia, Louis XIV was considered to be a marriage to the Spanish infanta Maria Theresa.";
	HistoryEvents[n].day = 3;
	HistoryEvents[n].month = 6;
	HistoryEvents[n].year = 1660;
	n++;

	HistoryEvents[n].text = "In France, Cardinal Giulio Raimondo Mazarin died. Louis XIV takes the reins in his own hands.";
	HistoryEvents[n].day = 9;
	HistoryEvents[n].month = 3;
	HistoryEvents[n].year = 1661;
	n++;

	HistoryEvents[n].text = "The plague came to London.";
	HistoryEvents[n].day = 10;
	HistoryEvents[n].month = 4;
	HistoryEvents[n].year = 1665;
	n++;

	HistoryEvents[n].text = "Charles II becomes King of Spain.";
	HistoryEvents[n].day = 1;
	HistoryEvents[n].month = 1;
	HistoryEvents[n].year = 1665;
	n++;

}
