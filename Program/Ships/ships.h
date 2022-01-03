#define SAILS_COLOR_QUANTITY				9
#define SHIP_TYPES_QUANTITY					139
#define SHIP_TYPES_QUANTITY_WITH_FORT		140	// must be (SHIP_TYPES_QUANTITY + 1)

//====================================================================================================================================================================================================================
//7
#define SHIP_TARTANE				0
#define SHIP_PLOT					1
#define SHIP_WAR_TARTANE			2
//====================================================================================================================================================================================================================
//6 пушки(8-12)
#define SHIP_BERMSLOOP 				3
#define SHIP_EMPRESS				4
#define SHIP_PINK					5
#define SHIP_LUGGER					6
#define SHIP_LUGGER_H				7
#define SHIP_SPEEDY					8
#define SHIP_FR_SLOOP				9
#define SHIP_GALEOTH_H				10
#define SHIP_SLOOP					11
#define SHIP_SLOOP_B				12
#define SHIP_NEPTUNUS        	 	13
#define SHIP_SOPHIE					14
//====================================================================================================================================================================================================================
//5 пушки(8-12-16)
#define SHIP_POLACCA				15
#define SHIP_BARQUE					16
#define SHIP_FR_POSTILLIONEN		17
#define SHIP_SCHOONER				18
#define SHIP_COLONIALSCHOONER		19
#define SHIP_XEBEC					20
#define SHIP_BATTLEXEBEC			21
#define SHIP_XEBECLIGHT				22
#define SHIP_SCHOONERLIGHT			23
#define SHIP_MIRAGE					24
#define SHIP_POLACRE			    25
#define SHIP_ENSLAVER				26
#define SHIP_SHNYAVA				27
//====================================================================================================================================================================================================================
//4 пушки(16-24)
#define SHIP_BRIG					28
#define SHIP_BRIGHEAVY				29
#define SHIP_BARKENTINE				30
#define SHIP_BRIGANTINE				31
#define SHIP_CASTELF				32
#define SHIP_DERFFLINGER			33
#define SHIP_INTERCEPTOR			34
#define SHIP_FLEUT					35
#define SHIP_PO_FLEUT50				36
#define SHIP_GALEON_L				37
#define SHIP_GREYHOUND				38
#define SHIP_CORVETTELIGHT			39
#define SHIP_PACKET_BRIG			40
#define SHIP_PDN					41
#define SHIP_ENTERPRISE				42
#define SHIP_POLACRE_H				43
#define SHIP_CARAVEL				44
#define SHIP_FRIGATEMEDIUM			45
#define SHIP_RAAFRIGATE				46
#define SHIP_CARAVEL2				47
#define SHIP_FLEUTWAR				48
#define SHIP_FLEUTWARSAT			49
#define SHIP_GALEONTRADER			50
#define SHIP_LYDIA					51
//====================================================================================================================================================================================================================
//3 пушки(16-24-32)
#define SHIP_PINNACE				52
#define SHIP_DUTCHPINNACE			53
#define SHIP_PINNACELIGHT			54
#define SHIP_XEBEKVT				55
#define SHIP_FELIPE					56
#define SHIP_CRIMSONBLOOD			57
#define SHIP_CORVETTE				58
#define SHIP_FRIGATE_l				59
#define SHIP_BATTLECORVETTE			60
#define SHIP_BLACKANGEL				61
#define SHIP_COASTALFRIGATE			62
#define SHIP_FR_FRIGATE				63
#define SHIP_JAMAICASHIP			64
#define SHIP_THEBLACKPEARL			65
#define SHIP_GALEON_H				66
#define SHIP_GALEON1				67
#define SHIP_LA_MARIANNA			68
#define SHIP_PIRATFASTGAL			69
#define SHIP_UNICORN				70
#define SHIP_REVENGE				71
#define SHIP_LINEFRIGATE			72
#define SHIP_LIGHTFRIGATE			73
#define SHIP_BOUSSOLE				74
#define SHIP_SURPRISE				75
#define SHIP_SALAMANDER				76
#define SHIP_FRIGATE_SAT			77
#define SHIP_BATTLEFRIGATE			78
#define SHIP_NIGHTMARE				79
#define SHIP_MORDAUNT				80
#define SHIP_FRIGATE				81
#define SHIP_AMSTERDAM				82
#define SHIP_CARRACA				83
//====================================================================================================================================================================================================================
//2 пушки(24-32)
#define SHIP_GALEON50				84
#define SHIP_FASTFRIGATE			85
#define SHIP_FR_ESSEX				86
#define SHIP_FRIGATE_H			    87
#define SHIP_WARGALLEON2			88
#define SHIP_NL_PINNACEOFWAR47		89
#define SHIP_HOLLGALEON_H			90
#define SHIP_FEARLESS				91
#define SHIP_LINESHIP				92
#define SHIP_NL_FWZP				93
#define SHIP_CONSTITUTION			94
#define SHIP_OXFORD                 95
#define SHIP_DUTCHLINESHIP			96
#define SHIP_DUTCHSHIP				97
#define SHIP_NL_CONVOISHIP			98
#define SHIP_COURONNE				99
#define SHIP_ALEXIS					100
#define SHIP_LINESHIPHEAVY			101
#define SHIP_WARSHIP				102
#define SHIP_HEAVYWARSHIP			103
#define SHIP_HEAVYLINESHIP			104
//====================================================================================================================================================================================================================
//1 пушки(42)
#define SHIP_POSEIDON				105
#define SHIP_HMS_CENTURION			106
#define SHIP_RESOLUTION             107
#define SHIP_FR_SUPERIORWARSHIP1	108
#define SHIP_LINK					109
#define SHIP_SUPERBE				110
#define SHIP_BATTLESHIP				111
#define SHIP_LINK2					112
#define SHIP_BELLONA				113
#define SHIP_LINEARSHIP				114
#define SHIP_SHARK					115
#define SHIP_ZEVENPROVINCIEN		116
#define SHIP_FR_TRINITY				117
#define SHIP_MANOWAR_FAST			118
#define SHIP_BATTLEMANOWAR			119
#define SHIP_MANOWAR_GUB			120
#define SHIP_PRINCE                 121
#define SHIP_MANOWAR				122
#define SHIP_HMS_VICTORY			123
#define SHIP_SP_SANFELIPE			124
//====================================================================================================================================================================================================================
// QuestShip
#define SHIP_LUGGERQUEST     	   	125
#define SHIP_XEBEKVML				126
#define SHIP_BRIGQEEN				127
#define SHIP_BRIGSW					128
#define SHIP_CLIPPER				129
#define SHIP_CORVETTE_QUEST			130
#define SHIP_WH_CORVETTE_QUEST		131
#define SHIP_ARABELLA				132
#define SHIP_FRIGATEQUEEN			133
#define SHIP_CATHERINE				134
#define SHIP_FLYINGDUTCHMAN			135
#define SHIP_SANTISIMA		 	   	136
#define SHIP_SOLEYRU				137
//====================================================================================================================================================================================================================

//	ЛОДКА + ФОРТ
#define SHIP_BOAT          	  	   138
#define SHIP_FORT           	   139


#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];


ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // пользовать GetRealShip
