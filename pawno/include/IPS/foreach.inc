///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	 Foreach (fast loop in arrays)
//	   Author: Bruno da Silva 
//	 www.brunodasilva.com
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define iterArr:%0<%1>        ipsValue%0[%1], ipsSwap%0[%1] = {-1, ...}, ipsArray%0[%1] = {-1, ...}, ipsInit%0 = -1, ipsFinal%0 = 0

#define addItem(%0,%1)		add_item(ipsArray%0, %1, ipsFinal%0,ipsInit%0, ipsSwap%0)
#define delItem(%0,%1)		del_item(ipsArray%0, %1, ipsFinal%0,ipsInit%0,  ipsSwap%0)
#define setItem(%0,%1,%2)	set_item(ipsValue%0, %1, %2)

#define getChain(%0,%1)		ipsArray%0[%1]
#define getValue(%0,%1)		ipsValue%0[%1]

#define foreach(%0,%1)		for(new %1 = ipsInit%0; %1 != -1; %1 = getChain(%0,%1))
// #define foreachex(%0,%1)	for(new %1_ = ipsInit%0, %1; %1_ != -1; %1 = getValue(%0,%1_),%1_ = getChain(%0,%1))

new iterArr:Player<MAX_PLAYERS>;

del_item(array[], valor, &ultimo, &inicio, issetArr[], size = sizeof array) {

	if(valor < 0 || valor > size)
		return false;
		
	if(-1 == issetArr[valor] || ultimo == -1 || inicio == -1)
	    return false;

	new x = 0;
	issetArr[valor] = -1;
	for(new i; i != size; i++) {
		array[i] = -1;
		if(issetArr[i] != -1) {
			if(!x) {
				inicio = issetArr[i];
				array[inicio] = inicio;
				continue;
			}
			else x++;

			ultimo = issetArr[i];
			array[ultimo] = i;

		}
	}
/*	    
	if(array[valor] == -1) {
		if(ultimo != valor) {
			return false;
		}
		else {
		    

		}
	}
	else {
		if(inicio == valor) {
			inicio = array[valor];
			issetArr[valor] = -1;
			array[valor] = -1;
		}
		else {
			array[issetArr[valor]] = array[valor];
			array[valor] = -1;
			issetArr[valor] = -1;
		}
	}
*/
	return true;
	
}

set_item(array[], item, valor) {
	return array[item] = valor;
}

add_item(array[], valor, &ultimo, &inicio, issetArr[], size = sizeof array) {

	if(valor < 0 || valor > size)
		return false;
	
	if(array[valor] != -1 || issetArr[valor] != -1)
	    return false;

	if(ultimo == -1 || inicio == -1)
	    return issetArr[valor] = valor, ultimo = valor, inicio = valor;
	
	if(array[ultimo] == -1)
	    return issetArr[valor] = ultimo, array[ultimo] = valor, ultimo = valor, array[valor] = -1;

 	return printf("[ERROR VALUE] %d", valor);
}


public OnPlayerConnect(playerid)
{
    addItem(Player, playerid);
    return CallLocalFunction("CallOnPlayerConnect", "i", playerid);
}


#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif


public OnPlayerDisconnect(playerid, reason)
{
    delItem(Player,playerid);
    return CallLocalFunction("CallOnPlayerDisconnect", "ii", playerid, reason);
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif


#define OnPlayerConnect		CallOnPlayerConnect
#define OnPlayerDisconnect	CallOnPlayerDisconnect

forward OnPlayerConnect(playerid);
forward OnPlayerDisconnect(playerid, reason);