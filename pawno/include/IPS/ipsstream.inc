/*=================================================================
     _ ____     _____         __  __
    (_)  _ \ ___  |_   _|__  __ _|  \/  |
    | | |_) / __|   | |/ _ \/ _` | |\/| |
    | |  __/\__ \   | |  __/ (_| | |  | |
    |_|_|   |___/   |_|\___|\__,_|_|  |_|

        Created by Bruno da Silva
       www.ips-team.blogspot.com
       Stremaer Objects [iPs]Streamer

=================================================================*/

#include <a_samp>


#define MAX_STREAM          3000
#define MIN_INTERVAL        00500
#define MAX_DRAW            210.0

#define function%0(%1)      %0(%1); public %0(%1)

// ===================== [ Declarar Variaveis ] ================================

enum eFileLoad
{
    mapName[24],
    primeiro,
    ultimo
}


stock static
	bool:objetoDeletado[MAX_PLAYERS][MAX_STREAM],
	Float:objetoDistancia[MAX_PLAYERS],
	gFileLoaded[MAX_STREAM][eFileLoad],
	Float:dataObject[MAX_STREAM][7],
	bool:structObject[MAX_STREAM],
	objetoConfigs[MAX_STREAM][2],
	objetosCriados[MAX_PLAYERS],
	objetoNumero[MAX_PLAYERS],
	bool:objetoCriado[MAX_STREAM] = {false,...},
	objectModel[MAX_STREAM],
	objetoIdd[MAX_STREAM],
	mapasCarregados = 0,
	objCriados = 0;


#if defined foreach
#undef foreach
#endif
#define foreach(%0,%1) for(new %1; %1 != MAX_PLAYERS; %1++)



// ========================== [ Funções ] ======================================


public OnGameModeInit()
{
	SetTimer("ObjectUpdate", MIN_INTERVAL, true);
	return CallLocalFunction("Ex_OnGameModeInit", "");
}


//

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Ex_OnGameModeInit
forward Ex_OnGameModeInit();



forward ExOnGameModeInit();

stock getMapXMLParam(string[], param[])
{
    new
        tempString[128],
        paramInt = strfind(string, param, true)
        ;

    if(-1 != paramInt) {
        paramInt += strlen(param);

        for(new j = -1; string[paramInt] != '"'; ++paramInt) {
            tempString[++j] = string[paramInt];
        }
    }

    return tempString;
}


function deleteObjectsFromFile(file[])
{
    for(new x = 0; x != mapasCarregados; x++) {
        if(!strcmp(gFileLoaded[x][mapName], file, true)) {
            for( ; gFileLoaded[x][primeiro] != gFileLoaded[x][ultimo]; ++gFileLoaded[x][primeiro]) {
                deleteObject(gFileLoaded[x][primeiro]);
            }

            gFileLoaded[x][primeiro] = 0;
            gFileLoaded[x][ultimo] = 0;
            gFileLoaded[x][mapName][0] = EOS;
            break;
        }

        continue;
    }
    return true;
}


function createObjectsFromMAPFile(arquivo[])
{
    new
        File:arquivoFopen = fopen(arquivo, io_read),
        string[256]
        ;

    new ultimoObjeto = CreateObject(2587, 2001.195679, 1547.113892, 14.283400, 0.0, 0.0, 0.0);

    while(fread(arquivoFopen, string)) {
        if(strlen(getMapXMLParam(string, "id=\"object")) < 2) continue;

        createObject
            (
            strval(getMapXMLParam(string, "model=\"")),
            floatstr(getMapXMLParam(string, "posX=\"")),
            floatstr(getMapXMLParam(string, "posY=\"")),
            floatstr(getMapXMLParam(string, "posZ=\"")),
            floatstr(getMapXMLParam(string, "rotX=\"")),
            floatstr(getMapXMLParam(string, "rotY=\"")),
            floatstr(getMapXMLParam(string, "rotZ=\"")),
            MAX_DRAW, strval(getMapXMLParam(string, "interior=\"")), 0
            );

    }

    gFileLoaded[mapasCarregados][primeiro] = ultimoObjeto;
    DestroyObject(ultimoObjeto);

    ultimoObjeto = CreateObject(2587, 2001.195679, 1547.113892, 14.283400, 0.0, 0.0, 0.0);
    DestroyObject(ultimoObjeto);

    gFileLoaded[mapasCarregados][ultimo] = ultimoObjeto;
    format(gFileLoaded[mapasCarregados][mapName], 24, arquivo);

    ++mapasCarregados;
    return true;
}


function createObjectsFromTXTFile(arquivo[], split)
{
    static
        fileFormat[24],
        string[64],
        modelid,
        interior,
        worldids
        ;

    new
        File:arquivoFopen = fopen(arquivo, io_read)
        ;

    enum E_OBJECTF
    {
        Float:float1,
        Float:float2,
        Float:float3,
        Float:float4,
        Float:float5,
        Float:float6,
        Float:float7
    };

    new
        Float:dataFloat[E_OBJECTF]
        ;

    format(fileFormat, 24, "p<%c>de<fffffff>dd", split);

    new ultimoObjeto = CreateObject(2587, 2001.195679, 1547.113892, 14.283400, 0.0, 0.0, 0.0);

    while(fread(arquivoFopen, string)) {
        sscanf(string, fileFormat, modelid, dataFloat,interior, worldids);

        if(!dataFloat[float7]) {
            dataFloat[float7] = 350.0;
        }

        createObject(modelid, dataFloat[float1], dataFloat[float2], dataFloat[float3], dataFloat[float4], dataFloat[float5], dataFloat[float6], dataFloat[float7], interior, worldids);
    }

    gFileLoaded[mapasCarregados][primeiro] = ultimoObjeto;
    DestroyObject(ultimoObjeto);

    ultimoObjeto = CreateObject(2587, 2001.195679, 1547.113892, 14.283400, 0.0, 0.0, 0.0);
    DestroyObject(ultimoObjeto);

    gFileLoaded[mapasCarregados][ultimo] = ultimoObjeto;
    format(gFileLoaded[mapasCarregados][mapName], 24, arquivo);

    ++mapasCarregados;

#pragma unused modelid
#pragma unused dataFloat
#pragma unused string
#pragma unused split
#pragma unused fileFormat
#pragma unused interior
#pragma unused worldids

    return fclose(arquivoFopen);
}


function createObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance, interior, worldids)
{
    if(MAX_STREAM - 1 == objCriados) {

        print("[ERRO] Informação acessada inválida (objeto numero " #MAX_STREAM - 1 " ) (limite excedido)");
        return false;

    }

    ++objCriados;

    objectModel[objCriados] = modelid;

    dataObject[objCriados][0] = X;
    dataObject[objCriados][1] = Y;
    dataObject[objCriados][2] = Z;

    dataObject[objCriados][3] = rX;
    dataObject[objCriados][4] = rY;
    dataObject[objCriados][5] = rZ;

    objetoConfigs[objCriados][0] = worldids;
    objetoConfigs[objCriados][1] = interior;

    dataObject[objCriados][6] = DrawDistance;
	
    structObject[objCriados] = true;
    return objCriados;
}


function deleteObject(objectid)
{
    foreach(Player,i)  if(IsPlayerConnected(i)) {{
        DestroyPlayerObject(i, objectid);

        dataObject[objectid][0] = 0;
        dataObject[objectid][1] = 0;
        dataObject[objectid][2] = 0;

        dataObject[objectid][3] = 0;
        dataObject[objectid][4] = 0;
        dataObject[objectid][5] = 0;

        dataObject[objectid][6] = 0;

        objetoIdd[objectid] = 0;

        objectModel[objectid] = 0;

        objetoConfigs[objectid][0] = 0;
        objetoConfigs[objectid][1] = 0;

        structObject[objectid] = false;

    }}
    return true;
}


function stopObject(objectid)
{
    foreach(Player,i)  if(IsPlayerConnected(i)) {{

        static
            Float:px, Float:py, Float:pz
            ;

        GetPlayerPos(i, px, py, pz);
        dataObject[objectid][0] = px;
        dataObject[objectid][1] = py;
        dataObject[objectid][2] = pz;

        StopPlayerObject(i, objectid);
    }}
    return 1;
}


function moveObject(objectid, Float:pX, Float:pY, Float:pZ, Float:Speed, Float:rotX, Float:rotY, Float:rotZ)
{
    foreach(Player,i)  if(IsPlayerConnected(i)) {{
        dataObject[objectid][0] = pX;
        dataObject[objectid][1] = pY;
        dataObject[objectid][2] = pZ;

#if defined PlayAudioStreamForPlayer
        {
            MovePlayerObject(i, objectid, pX, pY, pZ, Speed, rotX, rotY, rotZ);
        }
#else
        {
            MovePlayerObject(i, objectid, pX, pY, pZ, Speed);
        }
#endif
    }}
    return 1;
}


function ObjectUpdate()
{

    static objetoPerto;
    static o;

    foreach(Player,i) { if(IsPlayerConnected(i)) { for(o = 0; o != sizeof structObject; ++o) if(structObject[o]) {
        objetoPerto = IsPlayerInRangeOfPoint(i, dataObject[o][6], dataObject[o][0], dataObject[o][1], dataObject[o][2]);

printf("%d %d", objetoPerto, objetoCriado[o]);
        if(objetoPerto  && !objetoCriado[o]/* && GetPlayerVirtualWorld(i) == objetoConfigs[o][0] && GetPlayerInterior(i) == objetoConfigs[o][1]*/) {


            static
                Float: px,
                Float: py,

                Float: pz,
                Float: pd;

            GetPlayerPos(i, px, py, pz);

            px -= dataObject[o][0];
            py -= dataObject[o][1];
            pz -= dataObject[o][2];

            pd = floatsqroot((px * px) + (py * py) + (pz * pz));

            if(pd > objetoDistancia[i]) {
                objetoDistancia[i] = pd;
                objetoNumero[i] = o;
            }

// criar ojeto
            objetoCriado[o] = true;
            ++objetosCriados[i];

            objetoIdd[o] = CreatePlayerObject(i, objectModel[o], dataObject[o][0], dataObject[o][1], dataObject[o][2], dataObject[o][3], dataObject[o][4], dataObject[o][5], dataObject[o][6]);

// tirar objeto caso limite for ultrapssado
                                                  // PREVENT CRASH
            if(objetosCriados[i] > MAX_OBJECTS - 50) {
                DestroyPlayerObject(i, objetoIdd[objetoNumero[i]]);
                objetoDistancia[i] = 0.0;

                --objetosCriados[i];
                objetoCriado[o] = false;
            }

            continue;
        }
        if(objetoPerto && !objetoCriado[o]) {
            DestroyPlayerObject(i, objetoIdd[o]);

            objetoCriado[o] = true;
            --objetosCriados[i];
        }
    }}}
    return true;
}


// SSCANF BY BRUNO S
sscanf(string[], format[],{Float,_}
:...)
{

#if !defined isNull
#define isNull(%0) (!%0[0]  || %0[0] == '\1' && !%0[1])
#endif

#if defined strcpy
#undef strcpy
#endif

#if !defined foreach
#define foreach(%0,%1) for (new %1 = 0; %1 != MAX_PLAYERS; ++%1) if(IsPlayerConnected(%1))
#endif

#define strcpy(%0,%1) strcat((%0[0] = '\0', %0), %1, sizeof(%0))

#define MAX_BUFFER  128

    if(isNull(string)) {
        return false;

    }

    new
    formatCount = -1,
    stringCount = -1,
    paramsCount = 2,
    delim = 0x20,
    bool:silentMod = false,
    totalParams = numargs()
    ;

    static
    temporaria[MAX_BUFFER]
    ;

    strcpy(temporaria, string);

#pragma unused string

    while(format[++formatCount]) {
        switch(format[formatCount]) {
            case '{':

                {
                    silentMod = true;
                    continue;

                }

            case '}':

                {
                    silentMod = false;
                    continue;

                }

        }

        if(silentMod) {
            continue;

        }

        switch(format[formatCount]) {
            case 'i', 'd':

                {
                    new
                        numero,
                        caractere = temporaria[stringCount + 1],
                        negativo = 1                                                ;

                    if(caractere == '-') {
                        ++stringCount;
                        negativo = -1;

                    }

                    while((caractere = temporaria[++stringCount]) != delim && caractere) {
                        if ('0' <= caractere <= '9') {
                            numero =  (numero * 10) + (caractere - '0');

                        }
                        else {
                            return false;

                        }

                    }

                    setarg(paramsCount, 0, numero * negativo);
                    ++paramsCount;
                    continue;

                }

            case 'f':

                {

                    new sscanfValor = -1;

                    new
                        stringFloat[15]
                        ;

                    while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                        stringFloat[++sscanfValor] = temporaria[stringCount];

                    }

                    if(sscanfValor != -1) {
                        setarg(paramsCount, 0, _:floatstr(stringFloat));
                        ++paramsCount;
                    }

#pragma unused sscanfValor
                    continue;

                }

            case 'u':

                {
                    new
                        texto,
                        tempVal = stringCount,
                        stringTemp[MAX_BUFFER],
                        caractere = temporaria[stringCount + 1]   ;

                    while((caractere = temporaria[++tempVal]) != delim && temporaria[stringCount]) if ('0' > caractere || '9' < caractere) {
                        texto = 1;
                        break;

                    }

                    if(!texto) {
                        while((caractere = temporaria[++stringCount])!= delim && caractere) {
                            texto  =  (texto * 10) + (caractere - '0');

                        }
                        texto = 10;
                        setarg(paramsCount, 0, texto);

                    }
                    else {
                        texto = -1;
                        while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                            stringTemp[++texto] = temporaria[stringCount];

                        }

                        foreach(Player, i) {
                            static
                                name[MAX_PLAYER_NAME]
                                ;

                            GetPlayerName(i, name, MAX_PLAYER_NAME);
                            if(-1 != strfind(name, stringTemp, true)) {
                                setarg(paramsCount, 0, i);
                                texto = 10;
                                break;

                            }

                        }

                    }

                    if(10 != texto) {
                        setarg(paramsCount, 0, -1);

                    }

                    ++paramsCount;
                    continue;

                }

            case 's', 'z':

                {
                    new
                        sscanfValor = -1
                        ;

                    while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                        setarg(paramsCount, ++sscanfValor, temporaria[stringCount]);

                    }

                    if(sscanfValor != -1) {
                        ++paramsCount;

                    }
#pragma unused sscanfValor
                    continue;

                }

            case 'c':

                {
                    if(!temporaria[++stringCount]) return false;
                    setarg(paramsCount, 0, temporaria[stringCount]);
                    continue;

                }

            case '(':

                {
                    switch(format[formatCount - 1]) {
                        case 'g':

                            {
                                new
                                    findString[MAX_BUFFER],
                                    sscanfValor = -1
                                    ;

                                while(format[++formatCount] != ')') {
                                    findString[++sscanfValor] = format[formatCount];

                                }

                                if(-1 != sscanfValor) {
                                    sscanfValor = strfind(temporaria, findString, true);
                                    if(-1 != sscanfValor) {
                                        setarg(paramsCount, 0, sscanfValor);
                                        stringCount = sscanfValor+strlen(findString)+1;
                                        setarg(++paramsCount, 0, stringCount);

                                    }

                                }

                                ++paramsCount;
#pragma unused sscanfValor
                                continue;

                            }

                        case 'r':

                            {
                                while(format[++formatCount] ) {

                                    switch(format[formatCount]) {
                                        case ')':

                                            {
                                                break;

                                            }

                                        case 's' , 'z':

                                            {
                                                new
                                                    sscanfValor = -1,
                                                    bufferString[MAX_BUFFER]                        ;

                                                while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                                                    bufferString[++sscanfValor] = temporaria[stringCount];

                                                }

                                                new
                                                    i = sscanfValor
                                                    ;

                                                sscanfValor = -1;

                                                for( ; 0xFFFFFFFF != i; --i) {
                                                    setarg(paramsCount, ++sscanfValor, bufferString[i]);

                                                }

                                                if(sscanfValor != -1) {
                                                    ++paramsCount;

                                                }
#pragma unused sscanfValor

                                            }

                                        case 'f':

                                            {
                                                new
                                                    sscanfValor = -1,
                                                    stringFloat[MAX_BUFFER]                     ;

                                                while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                                                    stringFloat[++sscanfValor] = temporaria[stringCount];

                                                }

                                                new
                                                    i = sscanfValor
                                                    ;

                                                sscanfValor = -1;

                                                for( ; -1 != i; --i) {
                                                    stringFloat[++sscanfValor] = stringFloat[i];

                                                }

                                                if(sscanfValor != -1) {
                                                    setarg(++paramsCount, 0, _:floatstr(stringFloat));

                                                }
#pragma unused sscanfValor

                                            }

                                        case 'd' , 'i':

                                            {
                                                new
                                                    sscanfValor = -1,
                                                    stringValue[MAX_BUFFER]                     ;

                                                while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                                                    stringValue[++sscanfValor] = temporaria[stringCount];

                                                }

                                                new
                                                    i = sscanfValor
                                                    ;

                                                sscanfValor = -1;

                                                for( ; -1 != i; --i) {
                                                    stringValue[++sscanfValor] = stringValue[i];

                                                }

                                                if(sscanfValor != -1) {
                                                    setarg(++paramsCount, 0, strval(stringValue));

                                                }
#pragma unused sscanfValor

                                            }

                                    }

                                }
                                continue;

                            }

                    }

                }

            case '<':

                {
                    new
                        paramEnum = -1
                        ;

                    switch(format[formatCount-1]) {
                        case 'e' , 'a':

                            {
                                while(format[++formatCount]) {
                                    switch(format[formatCount]) {
                                        case '>':

                                            {
                                                break                                       ;

                                            }

                                        case 'i', 'd':

                                            {

                                                new
                                                    numero,
                                                    caractere = temporaria[stringCount + 1],
                                                    negativo = 1                            ;

                                                if(caractere == '-') {

                                                    ++stringCount;
                                                    negativo = -1;

                                                }

                                                while((caractere = temporaria[++stringCount]) != delim && caractere) {

                                                    if ('0' <= caractere <= '9') {
                                                        numero =  (numero * 10) + (caractere - '0');

                                                    }
                                                    else {
                                                        return false;

                                                    }

                                                }
                                                setarg(paramsCount, ++paramEnum, numero * negativo);
                                                continue;

                                            }

                                        case 'u':

                                            {
                                                new
                                                    texto,
                                                    tempVal = stringCount,
                                                    stringTemp[MAX_BUFFER],
                                                    caractere = temporaria[stringCount + 1] ;

                                                while((caractere = temporaria[++tempVal]) != delim && temporaria[stringCount]) if ('0' > caractere || '9' < caractere) {
                                                    texto = 1;
                                                    break;

                                                }

                                                if(!texto) {
                                                    while((caractere = temporaria[++stringCount])!= delim && caractere) {
                                                        texto  =  (texto * 10) + (caractere - '0');

                                                    }
                                                    texto = 10;

                                                    setarg(paramsCount, ++paramEnum, texto);

                                                }
                                                else {
                                                    texto = -1;
                                                    while(temporaria[++stringCount] != delim && temporaria[stringCount]) {
                                                        stringTemp[++texto] = temporaria[stringCount];

                                                    }

                                                    foreach(Player, i) {
                                                        static
                                                            name[MAX_PLAYER_NAME]
                                                            ;

                                                        GetPlayerName(i, name, MAX_PLAYER_NAME);
                                                        if(-1 != strfind(name, stringTemp, true)) {
                                                            setarg(paramsCount, ++paramEnum, i);
                                                            texto = 10;
                                                            break;

                                                        }

                                                    }

                                                }

                                                if(10 != texto) {
                                                    setarg(paramsCount, ++paramEnum, -1)    ;

                                                }
                                                continue;

                                            }

                                        case 'f':

                                            {
                                                new
                                                    sscanfValor = -1,
                                                    stringFloat[15]                         ;

                                                while(temporaria[++stringCount] != delim && temporaria[stringCount]) {

                                                    stringFloat[++sscanfValor] = temporaria[stringCount];

                                                }

                                                if(sscanfValor != -1) {
                                                    setarg(paramsCount, ++paramEnum, _:floatstr(stringFloat));

                                                }
#pragma unused sscanfValor
                                                continue;

                                            }

                                        case 'c':

                                            {
                                                setarg(paramsCount, ++paramEnum, temporaria[++stringCount]);
                                                continue;

                                            }

                                    }

                                }
                                ++paramsCount;

                            }

                        case 'p':

                            {

                                delim = format[++formatCount];

                                while(format[++formatCount] != '>') continue;

                            }

                    }

                }

        }

    }
    return paramsCount == totalParams;
}


#define StopObject          stopObject
#define MoveObject          moveObject
#define DestroyObject       destroyObject
#define CreateObject        createObject
