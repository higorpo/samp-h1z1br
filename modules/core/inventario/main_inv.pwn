 /*







												 _       _     _    _________     _
												| |     | |   / |  |______  /    / |
												| |     | |  /  |        / /    /  |
												| |     | | / / |       / /    / / |
												| |_____| |/_/| |      / /    /_/| |
												|  _____  |   | |     / /        | |
												| |     | |   | |    / /         | |
												| |     | |   | |   / /          | |
												| |     | | __| |__/ /______   __| |__
												|_|     |_||______/_________| |_______|

															Battle Royale

*/


//------------------------------------------------------------------------------------------------------------------------------------------


/* Variaveis, enums */
// > defines
	#define MAX_INVENTORY_SLOTS 	15
	#define MAX_ITENS_WORLD 		500
	#define TIMER_ITEM_WORLD        60*10


// > enums
	enum enum_Itens
	{
		item_id,
	 	item_tipo,
	  	item_modelo,
	 	item_nome[24],
		item_limite,
		bool:item_canbedropped,
		Float:item_previewrot[4],
		item_description[200]
	}

	enum
	{
		ITEM_TYPE_WEAPON,
		ITEM_TYPE_HELMET,
		ITEM_TYPE_NORMAL,
		ITEM_TYPE_BODY,
		ITEM_TYPE_AMMO,
		ITEM_TYPE_BACKPACK,
		ITEM_TYPE_MELEEWEAPON
	}

	enum enum_pInventory
	{
		invSlot[MAX_INVENTORY_SLOTS],
		invSelectedSlot,
		invSlotAmount[MAX_INVENTORY_SLOTS],
		Float:invArmourStatus[MAX_INVENTORY_SLOTS]
	}

	enum enum_pCharacter
	{
		charSlot[7],
		charSelectedSlot,
		Float:charArmourStatus
	}

	enum enum_Player
	{
		bool:inInventory,
		bool:MessageInventory,
		MessageInventoryTimer
	}

	enum enum_oWorld
	{
		bool:world_active,
		world_itemid,
		world_model,
		world_amount,
		world_object,
		world_timer,
		Text3D:world_3dtext,
		Float:world_armourstatus,
		Float:world_position[3],
		
	}


// > variaveis
	new Itens[][enum_Itens] =
	{
		{0, 	ITEM_TYPE_NORMAL,		19382, 		"Nada", 				0,			false,		{0.0,0.0,0.0,0.0}, 								"N/A"},
		{1, 	ITEM_TYPE_HELMET, 		18645, 		"Capacete", 			1,			true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Protege contra headshots."},
		{2, 	ITEM_TYPE_WEAPON, 		348, 		"Deagle", 				1, 			true,		{0.000000, -30.00000, 0.000000, 1.200000}, 		"Pistola de alto calibre.~n~~n~~g~Headshot habilitado."},
		{3, 	ITEM_TYPE_WEAPON, 		356, 		"M4", 					1, 			true,		{0.000000, -30.00000, 0.000000, 2.200000}, 		"Fuzil de longo alcance~n~com média precisão."},
		{4, 	ITEM_TYPE_AMMO, 		2061, 		"Munição", 				200, 		true,		{0.000000, 0.000000, 0.000000, 2.000000}, 		"Munição para armas de fogo."},
		{5, 	ITEM_TYPE_WEAPON, 		344, 		"Molotov", 				5,	 		true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Arma incendiaria caseira."},
		{6, 	ITEM_TYPE_BODY, 		19142, 		"Colete", 				1,	 		true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Colete aprova de balas."},
		{7, 	ITEM_TYPE_BACKPACK, 	3026, 		"Mochila Média",		1,	 		true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Mochila que aumenta seu~n~inventário."},
		{8, 	ITEM_TYPE_BACKPACK, 	3026, 		"Mochila Grande",		1,	 		true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Mochila que aumenta seu~n~inventário."},
	    {9, 	ITEM_TYPE_WEAPON, 		355, 		"AK-47", 				1, 			true,		{0.000000, -30.00000, 0.000000, 2.200000}, 		"Fuzil de longo alcance~n~com média precisão."},
	    {10, 	ITEM_TYPE_WEAPON, 		349, 		"Shotgun", 				1, 			true,		{0.000000, -30.00000, 0.000000, 2.200000}, 		"Shotgun de curto alcance~n~com um grande poder de fogo.~n~~n~~g~Headshot habilitado."},
	    {11, 	ITEM_TYPE_MELEEWEAPON,	335, 		"Faca", 				1, 			true,		{0.000000, -30.00000, 0.000000, 2.200000}, 		"Arma de corpo-a-corpo."},
	    {12, 	ITEM_TYPE_MELEEWEAPON,	334, 		"Cacetete", 			1, 			true,		{0.000000, -30.00000, 0.000000, 1.500000}, 		"Arma de corpo-a-corpo."},
	    {13, 	ITEM_TYPE_WEAPON, 		352, 		"Uzi", 					1, 			true,		{0.000000, -30.00000, 0.000000, 1.200000}, 		"Micro metralhadora~n~de duas mãos.."},
	    {14, 	ITEM_TYPE_WEAPON, 		347, 		"Usp", 					1, 			true,		{0.000000, -30.00000, 0.000000, 1.200000}, 		"Pistola com silenciador.~n~~n~~g~Headshot habilitado."},
	    {15, 	ITEM_TYPE_WEAPON, 		353, 		"MP5", 					1, 			true,		{0.000000, -30.00000, 0.000000, 2.200000}, 		"Micro metralhadora."},
	    {16, 	ITEM_TYPE_WEAPON, 		358, 		"Sniper", 				1, 			true,		{0.000000, -30.00000, 0.000000, 2.200000}, 		"Rifle de longo alcance.~n~~n~~g~Headshot habilitado."},
	    {17, 	ITEM_TYPE_WEAPON, 		342, 		"Granada", 				5,	 		true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Explosivo poderoso."},
	    {18, 	ITEM_TYPE_NORMAL, 		11738, 		"Kit Médico", 			5,	 		true,		{0.000000, 0.000000, 0.000000, 1.000000}, 		"Kit de primeiro socorros~n~que recupera sua vida."}
	};

	new pInventory[MAX_PLAYERS][enum_pInventory];
	new pCharacter[MAX_PLAYERS][enum_pCharacter];
	new Player[MAX_PLAYERS][enum_Player];
	new ItensWorld[MAX_ITENS_WORLD][enum_ItensWorld];
	new LastItemID;
	new invString[256];


// > textdraws
	new PlayerText:inventario_index[MAX_PLAYERS][15];
	new PlayerText:inventario_skin[MAX_PLAYERS];
	new PlayerText:inventario_textos[MAX_PLAYERS][11];
	new PlayerText:inventario_description[MAX_PLAYERS][4];
	new PlayerText:inventario_personagemindex[MAX_PLAYERS][7];
	new PlayerText:inventario_mensagem[MAX_PLAYERS];

	new Text:inventario_usar;
	new Text:inventario_split[2];
	new Text:inventario_drop[2];
	new Text:inventario_close[2];
	new Text:inventario_backgrounds[5];
	new Text:inventario_remover;


// forwards
	forward @TimerOneSecond();
	forward HideMessageInventory(playerid);
	forward Float:GetPlayerArmourEx(playerid);


//------------------------------------------------------------------------------------------------------------------------------------------
