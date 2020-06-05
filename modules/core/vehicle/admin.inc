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



//------------------------------------------------------------------------------------------------------------------------------------------

/* Callbacks */
hook OnGameModeInit()
{
    Command_AddAltNamed("criarveiculo", "cv"); // Opção de usar tanto /criarveiculo, quanto /cv.
    return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    if(GetPVarInt(playerid, "admin_vehicle_created") == vehicleid)
    {
        DestroyVehicle(vehicleid);
        SendClientMessage(playerid, Branco, "| INFO | Veículo destruído com sucesso!");
        DeletePVar(playerid, "admin_vehicle_created");
    }
    return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------

/* Comandos */
YCMD:criarveiculo(playerid, params[], help)
{
    if(help) SendClientMessage(playerid, -1, "Cria um veiculo que será destruído quando você sair do carro!");

    if(pInfo[playerid][admin] == 0) return SendClientMessage(playerid, -1, "| ERRO | Você não tem permissão!");
    if(adminInfo[playerid][logado] == false) return SendClientMessage(playerid, Vermelho, "| ERRO | Você não está logado como admin!");

    new idveh;
    if(sscanf(params, "d", idveh)) return SendClientMessage(playerid, Vermelho, "| ERRO | Digite /CriarVeiculo(cv) [ ID ]");
    if(idveh < 400 || idveh > 611) return SendClientMessage(playerid, Vermelho, "| ERRO | Veículo invalido!");
    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, Vermelho, "| ERRO | Você já está dentro de um veículo!");

    new Float:Pos[4], veh;
    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
    GetPlayerFacingAngle(playerid, Pos[3]);

    veh = CreateVehicle(idveh, Pos[0], Pos[1], Pos[2], Pos[3], -1, -1, -1);
    UpdateVehicleDamageStatus(veh, encode_panels(random(4), random(4), random(4), random(4), random(4), random(4), random(4)),
        encode_doors(random(5), random(5), random(5), random(5), random(5), random(5)), encode_lights(random(2), random(2), random(2), random(2)),
        encode_tires(random(2), random(2), random(2), random(2)));
    SetVehicleVirtualWorld(veh, GetPlayerVirtualWorld(playerid));
    PutPlayerInVehicle(playerid, veh, 0);
    SetPVarInt(playerid, "admin_vehicle_created", veh);

    SendClientMessageEx(playerid, Verde, "| INFO | Veículo id %d criado com sucesso!", idveh);
    return 1;
}

YCMD:cvp(playerid, params[], help)
{
    if(help) SendClientMessage(playerid, -1, "Cria um veiculo permanente");

    if(pInfo[playerid][admin] < 3) return SendClientMessage(playerid, -1, "| ERRO | Você não tem permissão!");
    if(adminInfo[playerid][logado] == false) return SendClientMessage(playerid, Vermelho, "| ERRO | Você não está logado como admin!");

    new idveh;
    if(sscanf(params, "d", idveh)) return SendClientMessage(playerid, Vermelho, "| ERRO | Digite /Cvp [ ID ]");
    if(idveh < 400 || idveh > 611) return SendClientMessage(playerid, Vermelho, "| ERRO | Veículo invalido!");

    new Float:Pos[4], veh;
    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
    GetPlayerFacingAngle(playerid, Pos[3]);

    veh = CreateVehicle(idveh, Pos[0], Pos[1], Pos[2], Pos[3], -1, -1, -1);
    SetVehicleVirtualWorld(veh, GetPlayerVirtualWorld(playerid));
    PutPlayerInVehicle(playerid, veh, 0);

    SendClientMessageEx(playerid, Verde, "| INFO | Veículo permanente id %d criado com sucesso!", idveh);
    return 1;
}

YCMD:dvp(playerid, params[], help)
{
    if(help) SendClientMessage(playerid, -1, "Destroi um veiculo permanente");

    if(pInfo[playerid][admin] < 3) return SendClientMessage(playerid, -1, "| ERRO | Você não tem permissão!");
    if(adminInfo[playerid][logado] == false) return SendClientMessage(playerid, Vermelho, "| ERRO | Você não está logado como admin!");
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, Vermelho, "| ERRO | Você precisa estar dentro do veículo a ser respawnado.");
    
    DestroyVehicle(GetPlayerVehicleID(playerid));
    SendClientMessage(playerid, Verde, "| INFO | Veículo destruido com sucesso!");
    return 1;
}

YCMD:respawnveh(playerid, params[], help)
{
    #pragma unused params
    if(help) SendClientMessage(playerid, -1, "Da respawn em um veiculo");

    if(pInfo[playerid][admin] < 2) return SendClientMessage(playerid, -1, "| ERRO | Você não tem permissão!");
    if(adminInfo[playerid][logado] == false) return SendClientMessage(playerid, Vermelho, "| ERRO | Você não está logado como admin!");
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, Vermelho, "| ERRO | Você precisa estar dentro do veículo a ser respawnado.");

    SetVehicleToRespawn(GetPlayerVehicleID(playerid));
    SendClientMessage(playerid, Verde, "| INFO | Veículo respawnado com sucesso!");
    return 1;
}

YCMD:irveh(playerid, params[], help)
{
    if(help) SendClientMessage(playerid, -1, "Vai até um veiculo");

    if(pInfo[playerid][admin] < 2) return SendClientMessage(playerid, -1, "| ERRO | Você não tem permissão!");
    if(adminInfo[playerid][logado] == false) return SendClientMessage(playerid, Vermelho, "| ERRO | Você não está logado como admin!");


    new vehid;
    if(sscanf(params, "d", vehid)) return SendClientMessage(playerid, Vermelho, "| ERRO | Digite /IrVeh [ ID ]");

    new Float:x, Float:y, Float:z;
    GetVehiclePos(vehid, x, y, z);
    SetPlayerPos(playerid, x, y, z);

    SendClientMessage(playerid, Verde, "| INFO | Você foi até o veículo com sucesso!");
    return 1;
}



decode_lights(lights, &light1, &light2, &light3, &light4)
{
    light1 = lights & 1;
    light2 = lights >> 1 & 1;
    light3 = lights >> 2 & 1;
    light4 = lights >> 3 & 1;
}
 
decode_panels(panels, &front_bumper, &rear_bumper)
{
    front_bumper= panels >> 20 & 15;
    rear_bumper = panels >> 24 & 15;
}
 
decode_doors(doors, &bonnet, &boot, &driver_door, &passenger_door)
{
    bonnet = doors & 7;
    boot = doors >> 8 & 7;
    driver_door = doors >> 16 & 7;
    passenger_door = doors >> 24 & 7;
}
 
decode_tires(tires, &tire1, &tire2, &tire3, &tire4)
{
    tire1 = tires & 1;
    tire2 = tires >> 1 & 1;
    tire3 = tires >> 2 & 1;
    tire4 = tires >> 3 & 1;
}
 
encode_tires(tire1, tire2, tire3, tire4)
{
    return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}
 
encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper)
{
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}
 
encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door)
{
    #pragma unused behind_driver_door
    #pragma unused behind_passenger_door
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}
 
encode_lights(light1, light2, light3, light4)
{
    return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}