/*------------------------------------------------------------------------------
					******************************************************
						» FunctionEdit - Funções própias melhoradas! «
					******************************************************
Descrição:
	Essa include serve para editar-mos as Funções/CallBacks melhorando o uso delas.
	
Versão:
	1.3
	
Autores:
	Paulo_TerroR.
	Los.
	ViniBorn.
	Lucas_Alemao.
	
ChangeLOG:
	25/06/2012(1.3):
		Adicionados:
			SendClientMessage By. Lucas_Alemao
			SendClientMessageToAll By. Lucas_Alemao
			OnPlayerDamage By. Paulo_TerroR
	31/05/2012(1.2):
		Adicionados:
			SetPlayerPos By. ViniBorn
			SetVehiclePos By. ViniBorn
			GetPlayerPos By. Paulo_TerroR
			SetPlayerPos By. Paulo_TerroR
		Agora pode-se desativar funções. Ex:
			#define @FE_OnVehicleDamageStatusUpdate false // Caso for desativar alguma função coloque '@FE_NomeFunção' seguido do valor 'false' para desativa-la.
			#include <FunctionEdit> //Sempre utilize a include abaixo das definições que desativam certas funções para não haver erros.
	30/05/2012(1.1):
		Adicionados:
			GetPlayerHealth By. Los
			GetPlayerArmour By. Los
			GetPlayerFacingAngle By. Los
			GetPlayerIp By. Los
			GetPlayerName By. Los
			GetPlayerVersion By. Los
			OnPlayerEnterVehicle By. Paulo_TerroR
			OnPlayerStateChange By. Paulo_TerroR
	30/05/2012(1.0):
		Lançamento.
		
Agradecimento:
	Paulo_TerroR - Criador.
	Equipe SA-MP(Passado\Presente\Futuro) - SAMP.
	Hiuship - Ideias.
	ViniBorn - Participação na Include.
	Los - Participação na Include.
	Lucas_Alemao - Participação na Include.
	
Funções Editadas:
	OnVehicleDamageStatusUpdate
		Autor da edição: Paulo_TerroR.
		Parametros Adicionados: Flaot:amount.
		Comentário: Parametro retorna o dano que o veiculo sofreu na batida.
		
	GetPlayerHealth
		Autor da edição: Los.
		Comentário: Agora a função Armazena e Retorna os dados.
		
	GetPlayerArmour
		Autor da edição: Los.
		Comentário: Agora a função Armazena e Retorna os dados.
		
	GetPlayerFacingAngle
		Autor da edição: Los.
		Comentário: Agora a função Armazena e Retorna os dados.
		
	GetPlayerIp
		Autor da edição: Los.
		Parametros Retirados: name[], len.
		Comentário: Agora a função Retorna os dados.
		
	GetPlayerName
		Autor da edição: Los.
		Parametros Retirados: const name[], len.
		Comentário: Agora a função  Retorna os dados.
		
	GetPlayerVersion
		Autor da edição: Los.
		Parametros Retirados: version[], len.
		Comentário: Agora a função Retorna os dados.
		
	OnPlayerEnterVehicle
		Autor da edição: Paulo_TerroR.
		Parametros Adicionados: veiculo.
		Comentário: Parametro retorna o modelo do veiculo.
		
	OnPlayerStateChange
		Autor da edição: Paulo_TerroR.
		Parametros Adicionados: vehicleid, veiculo.
		Comentário: Parametro retorna id e o modelo do veiculo.
	SetPlayerPos
		Autor da edição: ViniBorn.
		Parametros Adicionados: angulo.
		Comentário: Parametro seta o angulo do player.
	SetVehiclePos
		Autor da edição: ViniBorn.
		Parametros Adicionados: angulo.
		Comentário: Parametro seta o angulo do veiculo.
	GetPlayerPos
		Autor da edição: Paulo_TerroR.
		Parametros Adicionados: &Float:FE_Pos[4].
		Comentário: Parametro armazena o angulo do player. Armazenando-os em celulas.
	GetVehiclePos
		Autor da edição: Paulo_TerroR.
		Parametros Adicionados: &Float:FE_Pos[4].
		Comentário: Parametro armazena o angulo do veiculo;. Armazenando-os em celulas.
	SendClientMessageEx
		Autor da edição: Lucas_Alemao.
		Parametros Adicionados: {Float,_}:... .
		Comentário: Parametro permite enviar mensagens formatadas.
	SendClientMessageToAllEx
		Autor da edição: Lucas_Alemao.
		Parametros Adicionados: {Float,_}:... .
		Comentário: Parametro permite enviar mensagens formatadas.
	OnPlayerDamage
		Autor da edição: Paulo_TerroR.
		Parametros Adicionados: &Float:FE_Pos[4].
		Comentário: Parametro armazena o angulo do veiculo;. Armazenando-os em celulas.

------------------------------------------------------------------------------*/

#if defined @EditFunctions_Incluida
	#endinput
#endif

#define @EditFunctions_Incluida

#if !defined FunctionEdit_DebuG
	#define FunctionEdit_DebuG 				true //Atere para 'true' para ver o Debug.
#endif

#if !defined @FE_OnVehicleDamageStatusUpdate
	#define @FE_OnVehicleDamageStatusUpdate	true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerHealth
	#define @FE_GetPlayerHealth				true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerArmour
	#define @FE_GetPlayerArmour				true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerFacingAngle
	#define @FE_GetPlayerFacingAngle		true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerIp
	#define @FE_GetPlayerIp					true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerName
	#define @FE_GetPlayerName				true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerVersion
	#define @FE_GetPlayerVersion			true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_OnPlayerEnterVehicle
	#define @FE_OnPlayerEnterVehicle		true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_OnPlayerStateChange
	#define @FE_OnPlayerStateChange			true //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_SetPlayerPos
	#define @FE_SetPlayerPos				false //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_SetVehiclePos
	#define @FE_SetVehiclePos				false //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetPlayerPos
	#define @FE_GetPlayerPos				false //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_GetVehiclePos
	#define @FE_GetVehiclePos				false //Atere para 'false' para desativar a edição sobre a função.
#endif

#if !defined @FE_OnPlayerDamage
	#define @FE_OnPlayerDamage				true //Atere para 'false' para desativar a edição sobre a função.
#endif

#define VEICULO_INVALIDO 	(0)
#define VEICULO_AVIAO 		(1)
#define VEICULO_BARCO 		(2)
#define VEICULO_BIKE 		(3)
#define VEICULO_CARRO 		(4)
#define VEICULO_HELI 		(5)
#define VEICULO_MOTO 		(6)
#define VEICULO_INDEFINIDO 	(7)

stock FE_AVIAO(VehicleID) {
	switch(GetVehicleModel(VehicleID)) { case 460, 464, 476, 511..513, 519, 520, 553, 592, 593: return 1; }
	return 0;
}

stock FE_BARCO(VehicleID) {
	switch(GetVehicleModel(VehicleID)) { case 430, 446, 452..454, 472, 473, 484, 493: return 1; }
	return 0;
}

stock FE_BIKE(VehicleID) {
	switch(GetVehicleModel(VehicleID)) { case 481, 509, 510: return 1; }
	return 0;
}

stock FE_CARRO(VehicleID) {
	switch(GetVehicleModel(VehicleID)) { case 400..416, 418..424, 426..429, 431, 433, 434, 436..445, 451, 455..459, 466, 467, 470, 474, 475, 477..480, 482, 483, 485, 486, 489..492, 494..496, 498..508, 514..518, 524..536, 540..547, 549..562, 565..568, 571..576, 578..580, 582, 583, 585, 587..589, 596..605, 609: return 1; }
	return 0;
}

stock FE_HELI(VehicleID) {
	switch(GetVehicleModel(VehicleID)) { case 417, 425, 447, 465, 469, 487, 488, 497, 501, 548, 563: return 1; }
	return 0;
}

stock FE_MOTO(VehicleID) {
	switch(GetVehicleModel(VehicleID)) { case 461..463, 468, 521..523, 581, 586: return 1; }
	return 0;
}

new Float: FE_LifeVeiculo[MAX_VEHICLES] = {1000.0, ...};
new FE_PlayerNome[MAX_PLAYERS][MAX_PLAYER_NAME];
new bool: OVDSU = false;
new bool: OPD = false;
new Float: FE_LifePlayer[MAX_PLAYERS] = {100.0, ...};
new FE_String[128];

stock isNumeric(const string[]) {
	new length = strlen(string);
	if(!length) return 0;
	for(new i; i != length; i++) if((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+') || (string[i] == '-' && i) || (string[i] == '+' && i)) return 0;
  	if(length == 1 && (string[0] == '-' || string[0] == '+')) return 0;
	return 1;
}

stock isFloat(const string[]) {
	new length = strlen(string), bool: FE_Var = false;
	if(!length) return 0;
	for(new i; i != length; i++) { 
		if((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+' && string[i] != '.') || (string[i] == '-' && i) || (string[i] == '+' && i) || (string[i] == '.' && !i)) return 0;
		if(string[i] == '.') FE_Var = true;
	}
  	if(length == 1 && (string[0] == '-' || string[0] == '+') || !FE_Var) return 0;
	return 1;
}

public OnGameModeInit() {
	OPD = funcidx("OnPlayerDamage") != -1;
	OVDSU = funcidx("FE_OVDSU") != -1;
	if(OVDSU) SetTimer("PT_OnVehicleDamage", 100, true);
	if(OPD) SetTimer("PT_OnPlayerDamage", 100, true);
	return CallRemoteFunction("FE_OnGameModeInit", #);
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FE_OnGameModeInit
forward FE_OnGameModeInit();

public OnPlayerConnect(playerid) {
	FE_PlayerNome[playerid] = #;
	return CallRemoteFunction("FE_OnPlayerConnect", "i", playerid);
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FE_OnPlayerConnect
forward FE_OnPlayerConnect(playerid);

/* Inicio OnVehicleDamageStatusUpdate By. Paulo_TerroR */

#if @FE_OnVehicleDamageStatusUpdate
	#if defined _ALS_OnVehicleDamage\
		StatusUpdate
		#undef OnVehicleDamageStatusUpdate
	#else
		#define _ALS_OnVehicleDamageStatusUpdate
	#endif
	#define OnVehicleDamageStatusUpdate FE_OVDSU
	forward FE_OVDSU(vehicleid, playerid, Float:amount);

	forward PT_OnVehicleDamage();
	public PT_OnVehicleDamage() {
		static Float:FE_Health, FE_Player, Float:FE_Dano;
		for(new i; i != MAX_VEHICLES; i++) {
			GetVehicleHealth(i, FE_Health);
			if(FE_LifeVeiculo[i] > FE_Health) {
				FE_Dano = FE_LifeVeiculo[i]-FE_Health;
				if(FE_Dano >= 1000) continue;
				for( ; FE_Player != MAX_PLAYERS; FE_Player++) if(IsPlayerConnected(FE_Player) && IsPlayerInVehicle(FE_Player, i)) break;
				CallRemoteFunction("FE_OVDSU", "iif", i, FE_Player, FE_Dano);
				#if FunctionEdit_DebuG
					printf("OnVehicleDamageStatusUpdate - Dano: %f", FE_Dano);
				#endif
				FE_LifeVeiculo[i] = FE_Health;
			} else if(FE_LifeVeiculo[i] < FE_Health) FE_LifeVeiculo[i] = FE_Health;
		}
		return 1;
	}

	stock FE_SetVehicleHealth(vehicleid, Float:health) {
		SetVehicleHealth(vehicleid, health);
		FE_LifeVeiculo[vehicleid] = health;
		return 1;
	}

	#define SetVehicleHealth FE_SetVehicleHealth
#endif

/* Fim OnVehicleDamageStatusUpdate By. Paulo_TerroR */

/* Inicio FE_GetPlayerHealth By. Los */

#if @FE_GetPlayerHealth
	stock Float:FE_GetPlayerHealth(playerid, &Float:health = 0.0) {
		GetPlayerHealth(playerid, health);
		return health;
	}
	
	#define GetPlayerHealth FE_GetPlayerHealth
#endif

/* Fim FE_GetPlayerHealth By. Los */

/* Inicio FE_GetPlayerArmour By. Los */

#if @FE_GetPlayerArmour
	stock Float:FE_GetPlayerArmour(playerid, &Float:armour = 0.0) {
		GetPlayerArmour(playerid, armour);
		return armour;
	}

	#define GetPlayerArmour FE_GetPlayerArmour
#endif

/* Fim FE_GetPlayerArmour By. Los */

/* Inicio FE_GetPlayerFacingAngle By. Los */

#if @FE_GetPlayerFacingAngle
	stock Float:FE_GetPlayerFacingAngle(playerid, &Float:ang = 0.0) {
		GetPlayerFacingAngle(playerid, ang);
		return ang;
	}

	#define GetPlayerFacingAngle FE_GetPlayerFacingAngle
#endif

/* Inicio FE_GetPlayerFacingAngle By. Los */

/* Inicio FE_GetPlayerIp By. Los */

#if @FE_GetPlayerIp
	stock FE_GetPlayerIp(playerid) {
		new FE_IP[16]; GetPlayerIp(playerid, FE_IP, sizeof(FE_IP));
		return FE_IP;
	}

	#define GetPlayerIp FE_GetPlayerIp
#endif

/* Fim FE_GetPlayerIp By. Los */

/* Inicio FE_GetPlayerName By. Los */

#if @FE_GetPlayerName
	stock FE_GetPlayerName(playerid) {
		if(!strcmp(FE_PlayerNome[playerid], "\0", true)) {
			GetPlayerName(playerid, FE_PlayerNome[playerid], MAX_PLAYER_NAME);
			return FE_PlayerNome[playerid];
		} else return FE_PlayerNome[playerid];
	}

	#define GetPlayerName FE_GetPlayerName
#endif

/* Fim FE_GetPlayerName By. Los */

/* Inicio FE_GetPlayerVersion By. Los */

#if @FE_GetPlayerVersion
	stock FE_GetPlayerVersion(playerid) {
		new FE_Versao[40]; GetPlayerVersion(playerid, FE_Versao, sizeof(FE_Versao));
		return FE_Versao;
	}

#define GetPlayerVersion FE_GetPlayerVersion
#endif

/* Fim FE_GetPlayerVersion By. Los */

/* Inicio OnPlayerEnterVehicle By. Paulo_TerroR */

#if @FE_OnPlayerEnterVehicle
	public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
		new FE_Veiculo = (vehicleid == INVALID_VEHICLE_ID)?(VEICULO_INVALIDO):(FE_AVIAO(vehicleid))?(VEICULO_AVIAO):(FE_BARCO(vehicleid))?(VEICULO_BARCO):(FE_BIKE(vehicleid))?(VEICULO_BIKE):(FE_CARRO(vehicleid))?(VEICULO_CARRO):(FE_HELI(vehicleid))?(VEICULO_HELI):(FE_MOTO(vehicleid))?(VEICULO_MOTO):(VEICULO_INDEFINIDO);
		#if FunctionEdit_DebuG
			printf("OnPlayerEnterVehicle - veiculo: %d", FE_Veiculo);
		#endif
		return CallRemoteFunction("FE_OnPlayerEnterVehicle", "iiii", playerid, vehicleid, ispassenger, FE_Veiculo);
	}

	#if defined _ALS_OnPlayerEnterVehicle
		#undef OnPlayerEnterVehicle
	#else
		#define _ALS_OnPlayerEnterVehicle
	#endif
	#define OnPlayerEnterVehicle FE_OnPlayerEnterVehicle
	forward FE_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger, veiculo);
#endif

/* Fim OnPlayerEnterVehicle By. Paulo_TerroR */

/* Inicio OnPlayerStateChange By. Paulo_TerroR */

#if @FE_OnPlayerStateChange
	public OnPlayerStateChange(playerid, newstate, oldstate) {
		new FE_VehicleID = (IsPlayerInAnyVehicle(playerid))?(GetPlayerVehicleID(playerid)):(INVALID_VEHICLE_ID), FE_Veiculo = (FE_VehicleID == INVALID_VEHICLE_ID)?(VEICULO_INVALIDO):(FE_AVIAO(FE_VehicleID))?(VEICULO_AVIAO):(FE_BARCO(FE_VehicleID))?(VEICULO_BARCO):(FE_BIKE(FE_VehicleID))?(VEICULO_BIKE):(FE_CARRO(FE_VehicleID))?(VEICULO_CARRO):(FE_HELI(FE_VehicleID))?(VEICULO_HELI):(FE_MOTO(FE_VehicleID))?(VEICULO_MOTO):(VEICULO_INDEFINIDO);
		if(FE_VehicleID != INVALID_VEHICLE_ID) {
			#if FunctionEdit_DebuG
				printf("OnPlayerStateChange - vehicleid: %d, veiculo: %d", FE_VehicleID, FE_Veiculo);
			#endif
		}
		return CallRemoteFunction("FE_OnPlayerStateChange", "iiiii", playerid, newstate, oldstate, FE_VehicleID, FE_Veiculo);
	}

	#if defined _ALS_OnPlayerStateChange
		#undef OnPlayerStateChange
	#else
		#define _ALS_OnPlayerStateChange
	#endif
	#define OnPlayerStateChange FE_OnPlayerStateChange
	forward FE_OnPlayerStateChange(playerid, newstate, oldstate, vehicleid, veiculo);
#endif

/* Fim OnPlayerStateChange By. Paulo_TerroR */

/* Inicio FE_SetPlayerPos By. ViniBorn */

#if @FE_SetPlayerPos
	#define FE_SetPlayerPos(%0,%1,%2,%3,%4) SetPlayerPos(%0,%1,%2,%3); SetPlayerFacingAngle(%0,%4)
	#define SetPlayerPos FE_SetPlayerPos
#endif

/* Fim FE_SetPlayerPos By. ViniBorn */

/* Inicio FE_SetVehiclePos By. ViniBorn */

#if @FE_SetVehiclePos
	#define FE_SetVehiclePos(%0,%1,%2,%3,%4) SetVehiclePos(%0,%1,%2,%3); SetVehicleZAngle(%0,%4)
	#define SetVehiclePos FE_SetVehiclePos
#endif

/* Fim FE_SetVehiclePos By. ViniBorn */

/* Inicio FE_GetPlayerPos By. Paulo_TerroR */

#if @FE_GetPlayerPos
	stock FE_GetPlayerPos(playerid, Float:FE_Pos[4]) {
		GetPlayerPos(playerid, FE_Pos[0], FE_Pos[1], FE_Pos[2]);
		GetPlayerFacingAngle(playerid, FE_Pos[3]);
	}

	#define GetPlayerPos FE_GetPlayerPos
#endif

/* Fim FE_GetPlayerPos By. Paulo_TerroR */

/* Inicio FE_GetVehiclePos By. Paulo_TerroR */

#if @FE_GetVehiclePos
	stock FE_GetVehiclePos(vehicleid, Float:FE_Pos[4]) {
		GetVehiclePos(vehicleid, FE_Pos[0], FE_Pos[1], FE_Pos[2]);
		GetVehicleZAngle(vehicleid, FE_Pos[3]);
	}
	
	#define GetVehiclePos FE_GetVehiclePos
#endif

/* Fim FE_GetVehiclePos By. Paulo_TerroR */

/* Inicio SendClientMessageEx By. Lucas_Alemao */

#define SendClientMessageEx(%0,%1,%2,%3); format(FE_String, sizeof(FE_String),%2,%3); SendClientMessage(%0,%1,FE_String);

/* Fim SendClientMessageEx By. Lucas_Alemao */

/* Inicio SendClientMessageToAllEx By. Lucas_Alemao */

#define SendClientMessageToAllEx(%0,%1,%2); format(FE_String, sizeof(FE_String),%1,%2); SendClientMessageToAll(%0,FE_String);

/* Fim SendClientMessageToAllEx By. Lucas_Alemao */

/* Inicio OnPlayerDamage By. Paulo_TerroR */

#if @FE_OnPlayerDamage
	forward OnPlayerDamage(playerid, Float:amount);

	forward PT_OnPlayerDamage();
	public PT_OnPlayerDamage() {
		static Float:FE_Health, Float:FE_Dano;
		for(new i; i != MAX_PLAYERS; i++) {
			if(IsPlayerConnected(i)) {
				GetPlayerHealth(i, FE_Health);
				if(FE_LifePlayer[i] > FE_Health) {
					FE_Dano = FE_LifePlayer[i]-FE_Health;
					if(FE_Dano >= 100) continue;
					CallRemoteFunction("OnPlayerDamage", "if", i, FE_Dano);
					#if FunctionEdit_DebuG
						printf("OnPlayerDamage - Dano: %f", FE_Dano);
					#endif
					FE_LifePlayer[i] = FE_Health;
				} else if(FE_LifePlayer[i] < FE_Health) FE_LifePlayer[i] = FE_Health;
			}
		}
		return 1;
	}
	
	stock FE_SetPlayerHealth(playerid, Float:health) {
		SetPlayerHealth(playerid, health);
		FE_LifePlayer[playerid] = health;
		return 1;
	}

	#define SetPlayerHealth FE_SetPlayerHealth
	
/* Fim OnPlayerDamage By. Paulo_TerroR */