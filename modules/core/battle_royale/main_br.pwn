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

/* Includes necessárias para o funcionamento do script */
#include <YSI\y_hooks>


/* Definições */
#define MAX_SLOTS (40)


/* Variaveis */
// enums
	new Float:random_spawns_player[][] = // Spawn aleatórios para a "sala de espera";
	{
		{-1408.5637, -2249.6680, 36.0801, 241.2825},
		{-1330.0929, -2217.4404, 26.7741, 300.5031},
		{-1396.9501, -2209.2703, 26.8395, 73.3576}
	};

	new Float:random_spawns_player_game[][] = 
	{
		{-651.7209,-7430.6050,249.5725,160.5516},
		{-1127.7483,-7391.3916,337.1079,267.8727},
		{-1483.7942,-7419.2339,345.2025,357.5783},
		{-1283.8632,-7851.5337,288.7842,187.1341},
		{-1190.4558,-7950.5767,273.3162,287.8628},
		{-1041.7188,-7936.6626,315.7547,124.0605},
		{-864.3981,-7776.6450,233.6251,397.6863},
		{-768.8506,-7658.3594,258.0284,390.7906},
		{-642.9408,-7376.1963,268.5589,395.1544},
		{-495.3827,-7213.5508,231.0071,296.3404},
		{-295.5218,-7135.6221,191.8146,294.7671},
		{-502.2408,-7550.4854,436.4713,194.7627},
		{-1216.2986,-7512.0425,318.2771,194.1924}
	};

	new Float:random_cars_create[][] = 
	{
		{-847.6553,-7632.7930,20.0847,347.2562},
		{-892.3317,-7662.2305,15.8073,138.2076},
		{-1097.0753,-7776.4019,4.5603,339.5184},
		{-1147.6863,-7708.1479,37.8813,290.5905},
		{-965.9249,-7668.0137,62.0811,343.5218},
		{-929.7357,-7403.4219,79.4124,15.2274},
		{-1079.5568,-7440.4917,160.6356,58.6528},
		{-868.5490,-7393.0571,14.9375,342.9790},
		{-1032.1616,-7179.7559,35.6053,102.4985},
		{-912.3702,-7154.2246,39.5214,191.6912},
		{-1101.2050,-6965.7549,17.8723,330.2651},
		{-1067.8135,-7110.2432,34.1452,61.6749},
		{-865.1680,-7330.7915,29.2502,22.0625},
		{-637.0208,-7189.7813,1.7405,358.3583},
		{-350.5546,-7044.2539,8.8603,259.1096},
		{-598.0311,-7538.6987,11.4044,199.7201},
		{-1000.1561,-8013.6025,15.5059,23.1270},
		{-1237.4983,-8079.6948,15.3472,48.5950},
		{-1324.8494,-7851.1792,15.3560,296.6282},
		{-1558.5602,-7584.8823,15.8444,140.4298},
		{-1286.6268,-7881.0684,15.3571,293.8398},
		{-1424.5685,-7879.7666,15.3517,225.0369}
	};

	new random_vehicle[4][] = 
	{
		{468},
		{495},
		{605},
		{471}
	};

	enum rooms_server_config // Configurações de sala.
	{
		bool:started, // Salva se a sala foi iniciada ou não, ou seja se o modo de jogo já iniciou.
		nasala, // Guarda o total de jogadores jogando.
		restantes // Salva os players que ainda não morreram.
	};

	enum room_config_player // Configurações de sala para os players.
	{
		bool:em_uma_sala, // Salva se o player está em uma sala ou não.
		salaid, // Guarda em que sala o player está.
		bool:loby, // Guarda se o player está no loby de tal sala.
		terminou_posicao // guarda a posição final do player para quando ele morrer ficar salva no sistema.
	};


// Variaveis
	new room_config[3][rooms_server_config]; // configurações das salas.
	new room_player_config[MAX_PLAYERS][room_config_player]; // configurações dos players em relação ao battle royale.
	new timer_start_room[3]; // timer para iniciar uma sala.
	new exit_area_timer[MAX_PLAYERS]; // timer para sair da area.
	new vehicle_rooms[3][MAX_VEHICLES]; // veiculos das salas.



// Forwards
	forward Verificar_ExitLocal(playerid);
	forward comecarRoom(roomid);
	forward SpawnPlayer_Aguardar(playerid);
	forward SairRoom_Time(playerid);


//------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------

