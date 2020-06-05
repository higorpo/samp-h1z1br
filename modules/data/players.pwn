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


/* Variaveis */
	new black_zone;

/* Forwards */
	forward OnPlayerConnected(playerid); // forward para o timer do callback OnPlayerConnect.



//------------------------------------------------------------------------------------------------------------------------------------------

hook OnGameModeInit()
{
	black_zone = GangZoneCreate(-996999, -3000, 3000, 996999); // deixa o mapa todo preto.
	return 1;
}

hook OnGameModeExit()	
{
    foreach(new i : Player) 
    { 
    	SavePlayer(i);
    } 
	return 1;
}

hook OnPlayerConnect(playerid)
{
	/* Configurações do player */
	ClearChat(playerid, 130);
	SendClientMessage(playerid, 0x0080FFFF, "| INFO | Aguarde, o servidor está carregando suas configurações de login.");
	SetTimerEx("OnPlayerConnected", 5000, false, "i", playerid);
	TogglePlayerSpectating(playerid, true);
	return 1;
}

public OnPlayerConnected(playerid)
{
	/* Seta a camera do player. */
	ClearChatTimer(playerid);
	SetPlayerCameraPos(playerid, -1502.1558, 2254.7742, 337.4642);
	SetPlayerCameraLookAt(playerid, -1503.1375, 2254.9680, 337.3146);
	ShowLogin(playerid, 0);
	ShowLogin(playerid, 1);

	SetTimerEx("timer_1second", 1000, true, "i", playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	SavePlayer(playerid);
    for (new p; p < sizeof(pInfo[]); ++p) //Reseta a array do player, evita alguns bugs
    {
        pInfo[playerid][player_data: p] = 0;
    }

    HideHudForPlayer(playerid);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	GangZoneShowForAll(black_zone, 0x000000FF);
	SetPlayerHealth(playerid, 99.9);
	return 1;
}

hook OnPlayerText(playerid, text[])
{
	new string[128];
	if(GetPVarInt(playerid, "chat_admin_ativado") == 1) return 0;
	if(pInfo[playerid][admin] > 0 && adminInfo[playerid][logado] == true) format(string, sizeof(string), "%s:{FFFFFF} [ %s{FFFFFF} ][ %d ] %s", GetPlayerName(playerid), getAdmin(playerid, 1), playerid, text);
	else format(string, sizeof(string), "%s:{FFFFFF} [ %d ] %s", GetPlayerName(playerid), playerid, text);
	ProxDetector(15.0, playerid, string, 0xA7A7A7FF);

	if(pInfo[playerid][admin] == 0)
	{
		foreach(new i : Player)
		{
			if(pInfo[i][admin] > 0)
			{
				new Float:x, Float:y, Float:z;
				GetPlayerPos(i, x, y, z);
				if(!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
				{	
					format(string, sizeof(string), "[{FF0000}Battle Royale{A7A7A7}] %s:{FFFFFF} [ %d ] %s", GetPlayerName(playerid), playerid, text);
					SendClientMessage(i, 0xA7A7A7FF, string);
				}
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

forward timer_1second(playerid);
public timer_1second(playerid)
{
	if(pInfo[playerid][admin] == 0 && GetPlayerWeapon(playerid) == 38 || GetPlayerWeapon(playerid) == 35)
	{
		ExitRoom(playerid);
    	HideLogin(playerid, 0);
	    HideMenu(playerid, 1);
	    ClearChat(playerid, 130);
	    SendClientMessageToAllEx(Vermelho, "| H1Z1 | O(A) jogador(a) %s foi kickado por usar armas proibidas.", GetPlayerName(playerid));
	    SendClientMessage(playerid, Branco, "| INFO | Você foi kickado do servidor pelo motivo ( Armas proibidas )");
	    Kick(playerid);
	}
	if(GetPlayerPing(playerid) > DOF2_GetInt("configurations.cfg", "ping_limit") && pInfo[playerid][logado] == true)
	{
		ExitRoom(playerid);
    	HideLogin(playerid, 0);
	    HideMenu(playerid, 1);
	    ClearChat(playerid, 130);
	    SendClientMessageToAllEx(Vermelho, "| H1Z1 | O(A) jogador(a) %s foi kickado por ter um ping maior do que o permitido!", GetPlayerName(playerid));
	    SendClientMessage(playerid, Branco, "| INFO | Você foi kickado do servidor pelo motivo ( Ping muito alto )");
		Kick(playerid);
		return 1;
	}
	if(room_player_config[playerid][loby] == false && GetPlayerHealth(playerid) > 99.9)
	{
		ExitRoom(playerid);
    	HideLogin(playerid, 0);
	    HideMenu(playerid, 1);
	    ClearChat(playerid, 130);
	    SendClientMessageToAllEx(Vermelho, "| H1Z1 | O(A) jogador(a) %s foi kickado por possível health-hack!", GetPlayerName(playerid));
	    SendClientMessage(playerid, Branco, "| INFO | Você foi kickado do servidor pelo motivo ( Possivel health-hack )");
		Kick(playerid);
		return 1;
	}
	if(GetPlayerMoney(playerid) > 0)
	{
		ExitRoom(playerid);
    	HideLogin(playerid, 0);
	    HideMenu(playerid, 1);
	    ClearChat(playerid, 130);
	    SendClientMessageToAllEx(Vermelho, "| H1Z1 | O(A) jogador(a) %s foi kickado por possível money-hack!", GetPlayerName(playerid));
	    SendClientMessage(playerid, Branco, "| INFO | Você foi kickado do servidor pelo motivo ( Possivel money-hack )");
		Kick(playerid);
		return 1;
	}
	return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------

/* Scripts gerais para o player me um modo geral. */
SavePlayer(playerid)
{
	if(pInfo[playerid][logado] == false) return 0;
	new query[300], DBResult:Result;
	format(query, sizeof(query), "UPDATE `contas` SET `nome`='%q', `email`='%q',`admin`='%d',`skin`='%d' WHERE `id`='%d'", 
		GetPlayerName(playerid),
		pInfo[playerid][email],
		pInfo[playerid][admin],
		pInfo[playerid][skin],
		pInfo[playerid][id]);
	Result = db_query(Connect, query);

	if(db_num_rows(Result) == 1) print("conta salva");
	return 1;
}


//------------------------------------------------------------------------------------------------------------------------------------------
