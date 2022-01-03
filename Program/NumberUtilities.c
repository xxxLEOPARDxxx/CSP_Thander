// Warship. Методы для работы с числами
// Большую часть попереносил из других файлов, чтобы все в одном месте было

#define PI 3.14159265
#define PIm2 6.28318530
#define PId2 1.57079632

float FRAND(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

// boal
float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

// Warship 30.07.09. -->
// Рандом 0.0 ... 1.0
float Random()
{
	return rand(32768) / 32768.0; // 65536
}

/*	Псевдорандом на одну цифру. Работает так:
	Первое cгенерированное число записывается в переменную игрока и при последующих активациях метод проверяет если переменная аналогична генерирующемуся числу,
	то рандом генерит его заново до тех пор, пока оно не будет отличаться от записанной переменной. При окончании цикла записывает новое сгенеренное число в переменную игрока.*/
int prand(int _max)
{
	if (!CheckAttribute(pchar,"prandvalue")) pchar.prandvalue = 0;
	int value = rand(_max); //генерация числа по диапазону
	while (value == sti(pchar.prandvalue)) //проверочный цикл по совпадению/несовпадению с записанным ранее значением в переменной игрока
	{
		value = rand(_max);
	}
	pchar.prandvalue = value; //запись в переменную игрока сгенерированного числа для последующей проверки
	return value;
}

// Коммент - не нравится мне cRand() - он возвращает не псевдослучайное число,
// а зависящее от конкретного дня месяца, да еще и подряд может быть несколько
// одинаковых числе, например, cRand(5) будет давать 5 дней подряд одно и тоже.
// Функция ниже вернет псевдослучайное число, потом запоминает его в PChar и пока не наступит
// новый день будет возвращать его-же. PChar.dayRandom устанавливается в первом шаге обновления дня
int dRand(int _max)
{
	float dayRandom;

	if(CheckAttribute(PChar, "dayRandom"))
	{
		dayRandom = stf(PChar.dayRandom);
		// Log_Info(""+dayRandom);
		// Log_Info(""+MakeInt(dayRandom * (_max+1)));
		return MakeInt(dayRandom * (_max+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom = Random();
	PChar.dayRandom = dayRandom;

	return MakeInt(dayRandom * (_max+1));
}

int dRand1(int _max1)
{
	float dayRandom1;

	if(CheckAttribute(PChar, "dayRandom1"))
	{
		dayRandom1 = stf(PChar.dayRandom1);
		// Log_Info(""+dayRandom1);
		// Log_Info(""+MakeInt(dayRandom1 * (_max1+1)));
		return MakeInt(dayRandom1 * (_max1+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom1 = Random();
	PChar.dayRandom1 = dayRandom1;

	return MakeInt(dayRandom1 * (_max1+1));
}

int dRand2(int _max2)
{
	float dayRandom2;

	if(CheckAttribute(PChar, "dayRandom2"))
	{
		dayRandom2 = stf(PChar.dayRandom2);
		// Log_Info(""+dayRandom2);
		// Log_Info(""+MakeInt(dayRandom2 * (_max2+1)));
		return MakeInt(dayRandom2 * (_max2+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom2 = Random();
	PChar.dayRandom2 = dayRandom2;

	return MakeInt(dayRandom2 * (_max2+1));
}
// <-- Warship 30.07.09

// cRand() - античитовый рандом Эдди. Юзать не рекомендуется, за место него - dRand()
//античитовый рендом
int cRand(int num)
{
	if (num < 1) return 0;
	if (num > 30) return rand(num);
	int sResult = num;
	int iData = GetDataDay();

	int iDel = 30.0 / (num + 1) + 0.5; //делитель месяца
	int step = iDel; //шаг увеличения уровня сравнения в месяце

	for (i=0; i<num; i++)
	{
		if (iData < iDel)
		{
			sResult = i;
			break;
		}
		else iDel += step;
	}
	return sResult;
}

// Радианы в градусы
float Radian2Degree(float _rad)
{
	return 180 / PI * _rad;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}
