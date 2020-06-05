/*
*  Copyright (c) 2012 [iPs]TeaM
*  Bruno da Silva (email@brunodasilva.com)
*  Função: Memória Dinâmica em Pawn !!
*
* www.brunodasilva.com
* www.ips-team.forumeiros.com
*/

//--------------------------------------

#define Dynamic:: Dynamic_

new Dynamic::Container = 0x1e1c6;


//--------------------------------------

#define arraySet(%0,%1,%2) \
				Dynamic::Set( #%0 , %1 , %2 )



#define arrayGet(%0,%1) \
				Dynamic::Get( #%0 , %1 )


/*--------------------------------------


Função: Dynamic::SetS

Parametros: (arrayName, stringSet)

Proposito: Colocar valor da array para string arrayName = "stringSet"

Autor: Bruno da Silva

--------------------------------------*/


stock Dynamic::SetS(nome[], valor[]) {

	Dynamic::Container++;

	static cellname[128];
	format(cellname, 128, "%sDATA", nome);

	Dynamic::Set(cellname, 0, Dynamic::Container);

	setproperty(0, "", Dynamic::Container * 2, valor);


	return true;
}




/*--------------------------------------


Função: Dynamic::GetS

Parametros: (arrayName,  &string,  stringLen, boolean: stringPacked)

Proposito: Retornar o valor da string contida em "arrayName" para a array "string"

Autor: Bruno da Silva

--------------------------------------*/

stock Dynamic::GetS(nome[], string[], len = sizeof(string), bool: packed = false) {

	static cellname[256];
	format(cellname, 256, "%sDATA", nome);


	getproperty(0, "", Dynamic::Get(cellname, 0) * 2, string);


	if (packed){
		return string;
	}

	strunpack(string, string, len);

	return string;
}





/*--------------------------------------


Função: Dynamic::Set

Parametros: (arrayName, slotArray, value)

Proposito: Atribuir valor a uma array.arrayName[slotArray] = value!

Autor: Bruno da Silva

--------------------------------------*/

stock Dynamic::Set(nome[], slot, valor) {


	new cellname[256 char], id;
	format(cellname, 128, "%sTOTAL", nome);

	id = Dynamic::Get(cellname, 0);
	setproperty(0, cellname, id + 1);

	format(cellname, 128, "%sINTE", nome);
	setproperty(id, cellname, slot);

	return bool: setproperty(slot, nome, valor);
}





/*--------------------------------------

Função: Dynamic::Get

Parametros: (arrayName, slotArray)

Retorno: Valor da array[slot]

Autor: Bruno da Silva

--------------------------------------*/

stock Dynamic::Get(nome[], slot) {
	return getproperty(slot, nome);
}



/*--------------------------------------

Função: Dynamic::Free

Parametros: (arrayName)

Propósito: Limpar uma array

Autor: Bruno da Silva

--------------------------------------*/

stock Dynamic::Free(nome[]) {

	// pegar  nomeDATA. Caso este existir é string!
	static cellname[256 char];
	format(cellname, 128, "%sDATA", nome);

	if(existproperty(0, cellname)) {

		// is string
		deleteproperty( .name = "", .value = Dynamic::Get(cellname, 0) >> 1);

		// deletar nomeDATA
		deleteproperty( 0, .name = cellname);

		return true ;

	}
	else {
		// is array

		static id ;

		// pegar total de slots modificacos
		format(cellname, 128, "%sTOTAL", nome);
		id = Dynamic::Get(cellname, 0);
		deleteproperty ( 0, cellname );

		// pegar parte que armazena quais slot s foram modificados
		format(cellname, 128, "%sINTE", nome);

		// percorrer toda array modificando os slots
		while((id--) > -1) {

			// deletar slot pego
			deleteproperty(Dynamic::Get ( cellname, id ), .name = nome);

			// deletar parte que mostra slot modificado
			deleteproperty ( id, cellname );
		}

		return true;

	}

	//return true;
}