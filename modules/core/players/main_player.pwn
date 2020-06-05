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




/* Definições/Variaveis */
// > enums
	enum player_data_login // enum para o armazenamento das informações do login.
	{
		@PlayerLoginName[24],
		@PlayerLoginPass[24],
		@PlayerRegisterName[24],
		@PlayerRegisterPass[24],
		@PlayerRegisterMail[32]
	}

	enum player_data // enum para o armazenamento das contas(player)
	{
		id, 
		senha[65], 
		salt[11], 
		email[32],
		admin,
		admin_pass[10],
		bool:vip,
		skin, 
		Float:vida,
		bool:logado, 
		errousenha
	};

// > variaveis
	new pLogin[MAX_PLAYERS][player_data_login]; // enum que armazena as informações do player em relação ao seu login/registro local: (login.funtion).
	new pInfo[MAX_PLAYERS][player_data]; //enum que armazena os dados dos players
	new ResetTimer[MAX_PLAYERS]; // Variavel que guarda o "id" do timer para limpar o chat local: (clearchat.function)
	new PlayerCodigo[MAX_PLAYERS]; // guarda o codigo que foi gerado local: (generate_cod.function).

// > textdraws
	new Text:hud[4];

	new Text:menu_base[11];
	new PlayerText:menu_base_player[MAX_PLAYERS][2];
	new Text:menu_exibir_menuPlayer[12];
	new Text:menu_configuracoes[15];
	new Text:menu_index[23];

	new Text:LOGIN_Base[9]; // Textdraws de base para a tela de login.
	new PlayerText:LOGIN_BasePlayer[4][MAX_PLAYERS]; // Textdraws de base para a tela do login (playerText)
	new Text:LOGIN_Index[14]; // Textdraws da index do sistema de login.
	new PlayerText:LOGIN_IndexPlayer[2][MAX_PLAYERS]; // Textdraws da index do sistema de login (playerText)
	new Text:LOGIN_Register[15]; // Textdraws da tela de registro.
	new PlayerText:LOGIN_RegisterPlayer[3][MAX_PLAYERS]; // Textdraws da tela de registro (playerText)

// > forwards 
	forward ClearChatTimer_Func(playerid);
	forward StopClearChatForTimer(playerid);




//------------------------------------------------------------------------------------------------------------------------------------------
