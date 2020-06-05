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

/*        Livrarias         */
#include <a_samp>
#include <SQLitei>
#include <DOF2>
#include <YSI\y_hooks>
#include <YSI\y_commands>
#include <foreach>
#include <streamer>
#include <fadein>
#include <nmailer>
#include <sscanf2>
#include <optimize>



/*       Configurações      */
#undef MAX_PLAYERS
#define MAX_PLAYERS (150) 



/* Variaveis de configurações */
new DB:Connect; // Handle de de conexão com o banco de dados.

//------------------------------------------------------------------------------------------------------------------------------------------





main(){}
hook OnGameModeInit()
{
	// Cria uma conexão com o banco de dados.
	if((Connect = db_open("server.db")) == DB:0)
	{
		// Printa um erro no console caso o banco de dados não seja encontrado.
		print("ERROR: Banco de dados nao encontrado =(");
		SendRconCommand("exit");
	}
	else
	{
		// Se o banco foi encontrado, gera uma mensagem de sucesso.
		print("INFO: Banco de dados encontrado com sucesso.");


		// Criar as tabelas e arquivos, caso elas não sejam encontradas no banco de dados SQL.
 		if(!DOF2_FileExists("configurations.cfg")) // Se o arquivo "configurations.cfg" não existir, será criado um na scriptfiles, com as seguintes configurações!
 		{
 			DOF2_CreateFile("configurations.cfg");
 			DOF2_SetString("configurations.cfg", "hostname", "default");
 			DOF2_SetString("configurations.cfg", "password", "default");
 			DOF2_SetString("configurations.cfg", "language", "default");
  			DOF2_SetString("configurations.cfg", "modname", "default");
   			DOF2_SetString("configurations.cfg", "mapname", "default");
 			DOF2_SetString("configurations.cfg", "weburl", "www.site.com");

 			// Configurações de versões entre outras.
 			DOF2_SetString("configurations.cfg", "script_version", "0.0");
 			DOF2_SetString("configurations.cfg", "last_release", "06-04-2016");

 			// Configurações do servidor em geral
 			DOF2_SetInt("configurations.cfg", "ping_limit", 1000);
 			DOF2_SaveFile();
 		}	

		db_query(Connect, "CREATE TABLE IF NOT EXISTS `contas` \
			(`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
			`nome`	TEXT NOT NULL UNIQUE,\
			`senha`	TEXT NOT NULL, \
			`salt`	INTEGER NOT NULL,\
			`email`	TEXT NOT NULL UNIQUE, \
			`admin`	INTEGER, `skin`	INTEGER, \
			`admin_pass` TEXT DEFAUT 0 \
			`skin`	INTEGER)"); // contas


		/* Verificação para saber se o configurations.cfg está configurado corretamente */
		if(!strcmp(DOF2_GetString("configurations.cfg", "script_version"), "0.0") && !strcmp(DOF2_GetString("configurations.cfg", "hostname"), "defaut"))
		{
			SendRconCommand("hostname H1Z1 ERROR: Código do erro: #1010");
			SendRconCommand("password h1z1_error_number_1010");
			print("            \n\n\n\nH1Z1 ERROR:\n\
				            O arquivo \"configurations.cfg\" não foi configurado corretamente!\n\n\n\n");
			return 0;
		}


		/* Configurações do servidor. */
		new field[50];

		format(field, sizeof(field), "hostname %s", DOF2_GetString("configurations.cfg", "hostname"));
		SendRconCommand(field);

		format(field, sizeof(field), "password %s", DOF2_GetString("configurations.cfg", "password"));
		SendRconCommand(field);

		format(field, sizeof(field), "language %s", DOF2_GetString("configurations.cfg", "language"));
		SendRconCommand(field);

		format(field, sizeof(field), "weburl %s", DOF2_GetString("configurations.cfg", "weburl"));
		SendRconCommand(field);

		format(field, sizeof(field), "%s", DOF2_GetString("configurations.cfg", "modname"));
		SetGameModeText(field);

		format(field, sizeof(field), "mapname %s", DOF2_GetString("configurations.cfg", "mapname"));
		SendRconCommand(field);

		/* Configurações gerais */
		UsePlayerPedAnims(); // desativa as animações do ped.
		ShowNameTags(0); // desativa poder ver o nick dos players pelo mapa.
	}
	return 1;
}

hook OnGameModeExit()
{
	db_close(Connect); // desfaz a conexão com o banco de dados.
	return 1;
}

CMD:testing(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19621, 6, 0.056999, 0.023000, 0.011000, 13.699995, -31.299966, 95.699974, 1.000000, 1.000000, 1.000000);
	return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------

/* Modulos */
	#include "..\modules\def\colors.pwn"
	#include "..\modules\def\dialogs.pwn"
	#include "..\modules\def\scripts.pwn"

	#include "..\modules\_fixes\OnPlayerClickPlayerTextDraw.hook"

	#include "..\modules\core\players\main_player.pwn"
	#include "..\modules\core\admins\main_admin.pwn"
	#include "..\modules\core\vehicle\main_veh.pwn"
	#include "..\modules\core\battle_royale\main_br.pwn"
	#include "..\modules\core\inventario\main_inv.pwn"
	#include "..\modules\core\airdrop\main_Airdrop.pwn"

	#include "..\modules\core\players\hud.function"
	#include "..\modules\core\players\clearchat.function"
	#include "..\modules\core\players\random_messages.function"
	#include "..\modules\core\players\generate_cod.function"
	#include "..\modules\core\players\func_player.function"
	#include "..\modules\core\players\recover_password.function"
	#include "..\modules\core\players\login.function"
	#include "..\modules\core\players\menu.function"
	#include "..\modules\core\players\commands_player.function"
	#include "..\modules\core\admins\func_admin.function"
	#include "..\modules\core\admins\commands_admin.function"
	#include "..\modules\core\admins\chatadmin.function"
	#include "..\modules\core\vehicle\admin.inc"
	#include "..\modules\core\admins\loginAdmin.function"
	#include "..\modules\core\admins\setadmin.function"
	#include "..\modules\core\vehicle\fuel.function"
	#include "..\modules\core\vehicle\engine.function"
	#include "..\modules\core\vehicle\lights.function"
	#include "..\modules\core\vehicle\generate_vehicles.function"
	#include "..\modules\core\battle_royale\func_br.function"
	#include "..\modules\core\inventario\textdraws_inv.function"
	#include "..\modules\core\inventario\func_inv.function"
	
	#include "..\modules\data\players.pwn"
	#include "..\modules\data\admin.pwn"
	#include "..\modules\data\vehicles.pwn"
	#include "..\modules\data\battle_royale.pwn"
	#include "..\modules\data\inventario.pwn"
	#include "..\modules\data\airdrop.pwn"

//------------------------------------------------------------------------------------------------------------------------------------------
