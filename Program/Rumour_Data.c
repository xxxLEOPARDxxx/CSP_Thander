// Philippe, de AoP1
//Таблица слухов, и их состояние. "active" - слух включен в поле случаного выбора слуха, "passive" - слух исключен из поля
#define MAX_RUMOURS 32
object	Rumour[MAX_RUMOURS];


void SetRumourDefaults()
{
	for (int i = 0; i < MAX_RUMOURS; i++)
	{
		Rumour[i].text = GlobalStringConvert("Rumour_"+i);
		Rumour[i].state = "active";
	}
}
