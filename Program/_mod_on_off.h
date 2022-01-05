// Mods on_off mode
// здесь и далее ник boal - это разработческий ник ALexusB

#define VERSION_NUMBER1       "ГПК v.1.3.2 ATR  "
#define VERSION_NUMBER2       "CSP v2.2.0 (02.01.2022)"
#define VERSION_NUMBER3       ""
#define PROVIDER_TXT            "LEOPARD's team"
#define VERSION_NUM      99910  // текущий номер
#define VERSION_NUM_PRE  99910  // последний совместмый

#define VERSION_WWW     ""
#define BI_COMPARE_HEIGHT 900
// Show special message for test game statment
#define MOD_BETTATESTMODE			"On"  // On -DEV version; Test - TST ver; Off

// глобальная строковая переменная
string sGlobalTemp;

// quest.c bool    bQuestCheckProcessFreeze = false; // заморозка квестов
//Времянка типа для сдачи
int surrenderenabled = 1;
// запрет всех случаек на суше (офицеры и клады тоже)
bool    bDisableLandEncounters = false;
// запрет жать ф2
bool    bDisableCharacterMenu  = false;
// флаг - игрок читер
bool    bPlayerIsCheater =  false;  // на перспективу, патчем
// режим супер читов
bool    bBettaTestMode = false;
// показывать quest_reaction Log
bool    bQuestLogShow  = false;
// показывать инфу по балансу
bool    bExpLogShow    = false;
// всегда сдаются капитаны - отладка
bool    TestRansackCaptain = false;
// показ локаторов
bool    bLocatorShow  = false;
// Не жрать, нет крыс
bool    bNoEatNoRats  = false;
// Живой мир на паузе: губер не переезжает от времени, нации не объявляют войну и мир, эскадры не берут город себе, город нельзя взять себе (даже с патентом)
bool    bWorldAlivePause      = true;
// пауза метро
bool bPauseContrabandMetro = false;
// лог для ПГГ
bool bPGGLogShow = false;
// флаг генерации монстров
bool bMonstersGen = false;
// флаг генерации сухопутных энкаунтеров
bool bLandEncountersGen = true;
// флаг в сундуке
bool bMainCharacterInBox = false;
// флаг в огне
bool bMainCharacterInFire = false;
// главное меню
bool bMainMenu = false;
//загрузка начала игры
bool startGameWeather = false;
//движок проверяет эту переменную, должна равной #define ENGINE_SCRIPT_VERSION в core.h
int iScriptVersion = 8675309;       //54128  --  15650

// Генератор фантомов - альтернатива
bool    bNewFantomGenerator       	= true;  // резерв "новый фехт"
bool    bRechargePistolOnLine  		= true;  // пистолеты перезаряжаются без сабли
// упрощение невозможного
bool    bNewCodeOn                	= false;  // упрощение абордажа
// нет сайвов, токо в церкви есть
bool    bHardcoreGame             	= false;
// раздел добычи
bool 	bPartitionSet 				= true;
// вес матросов
bool 	bSailorsWeight 				= true;
// новые паруса
bool 	bNewSails 					= true;
// хардкорные анимации
bool 	bHardAnimations				= true;
// Усложнённые боссы 15.12.2021
bool 	bHardBoss					= true;
// -10 корабельного порога
bool 	bHigherShipRate				= true;
// Маркировка квестовых
bool 	bQuestMark 					= false;
// -10 личного порога
bool 	bHigherSelfRate 			= true;
// влияние сложности на переносимый вес
bool 	bDifficultyWeight 			= true;
// Найм полубессмертного ПГГ
bool 	bHalfImmortalPGG 			= false;
// Сбор денег за швартовку
bool 	bPortPermission 			= false;
//Абордаж стенка на стенку
bool   bBoardMode                   = false;
//Срез скиллов от офицеров
bool   bNoBonusSkillOff             = false;
//Взятки стражникам
bool   bBribeSoldiers               = false;
//система скрытности
int 	iStealthSystem = 1;
//заполнение энциклопедии
bool 	bFillEncyShips              = false;
//альтернативный баланс
bool 	bAltBalance                 = false;
//Разговор местных жителей
bool 	bCharVoice                 = false;

// платный сайв-лоад
//bool    bPayForSaveLoad           = true;

// Скейлинг интерфейса
int screenscaling = BI_COMPARE_HEIGHT;

// Lugger: Режим дополнения -->
bool bAddonMode = true;
bool bAddonLine = true;
bool bNationLines = true;
bool bEnglandOrPirates = false;
bool bDisableQuestInterface = false;
bool bDisableOfficers = false;
bool bSanJuanIsDamned = false;
// Lugger: Режим дополнения <--

///////////////////////////////////////////////////
//          complexity
//  Next Level rate
int MOD_EXP_RATE           = 10; // это база... + (сложность)
//int Level_Complexity       = 5; // by default только настройка
//  complexity of fantom skill
int MOD_SKILL_ENEMY_RATE   = 5; // 1- easy; 2; 3; 4;  5-medium; 6; 7; 8; 9;  10 - hard (please, do not set more 10 or less 1 it mays crash game
#define MOD_Complexity_1_DMG  3.0
//officers count
int MOD_OFFICERS_RATE   = 3;
//количество кораблей охраны
int MOD_DEFENDERS_RATE   = 4;
// Killed body clear
#define MOD_DEAD_CLEAR           "On"
int MOD_DEAD_CLEAR_TIME = 100; // in sec.
string MainChAnim = "";
int chest_ammo[99];
int chest_treasure[99];
int chest_quest[99];
int chest_craftsmans[99];
int chest_ammo2[99];
int chest_treasure2[99];
int chest_quest2[99];
int chest_craftsmans2[99];

int shipspool[32];
string skillz[14];
string rand_arr[2];

#define CHAR_ITEMS_WEIGHT        70

#define InstantRepairRATE        65.0

// дистанция до корабля для разговора
#define DistanceToShipTalk        300.0

//#define ShipyardMoneyInit        190000.0
//#define ShipyardMoneyMax         900000.0
//#define ShipyardMoneyAdd         2000

// boal 23.01.2004 доработка 091004 сколь угодно героев -->
int    startHeroType = 1;
//int    heroFaceId    = 1;
// boal 23.01.2004 <--

int ItemDeadStartCount = 0; // заполняется в itemInit порог для заполения трупов (оптимизация)

#define STARTGAME_YEAR       1665
#define STARTGAME_MONTH      1
#define STARTGAME_DAY        1

// пасхалка Кукурузина
#define FUNY_SHIP_NAME    "Кукурузина"
#define KEY_ENG_LINE	  "uFRklw7Ghww19ywWQ"

int TimeScaleCounter = 0;
// запрет перехода
bool chrDisableReloadToLocation = false;
// для видения форта в АИ шипов
bool bIsFortAtIsland = false;
float fFort_x, fFort_z;
int iFortNation, iFortCommander;
//начало и конец предметов для локаторов item
int ItemsForLocators_start, ItemsForLocators_end, Totems_start, Totems_end;

//GetEngineVersion();
