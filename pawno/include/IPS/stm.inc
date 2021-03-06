///////////////////////////////////////////////////////////////////////////////
//
//
//        #### ########   ######     ######## ########    ###    ##     ##
//         ##  ##     ## ##    ##       ##    ##         ## ##   ###   ###
//         ##  ##     ## ##             ##    ##        ##   ##  #### ####
//         ##  ########   ######        ##    ######   ##     ## ## ### ##
//         ##  ##              ##       ##    ##       ######### ##     ##
//         ##  ##        ##    ##       ##    ##       ##     ## ##     ##
//        #### ##         ######        ##    ######## ##     ## ##     ##
//
//
//                    Criado por Bruno da Silva
//
//          Acesse meu blog sobre programa��o www.brunodasilva.com
//
//              Seja membro da melhor equipe de programa��o
//         http://ips-team.forumeiros.com/t2-informacao-inscricao-na-ips

//                    [iPs]TeaM solu��es de programa��o em geral
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////

#include a_samp
#include a_http

#include IPS/dynamic

#define detectar    "auto"

#define afric�ner	"af"
#define alban�s		"sq"
#define alem�o		"de"
#define arabe		"ar"
#define armenio		"hy"
#define azerbaijano	"az"
#define basco		"eu"
#define bielo-russo	"be"
#define b�lgaro		"bg"
#define catalao		"ca"
#define chinesS		"zh-CN"
#define coreano		"ko"
#define Haitiano 	"ht"
#define croata		"hr"
#define dinamarqu�s	"da"
#define eslovaco	"sk"
#define esloveno	"sl"
#define espanhol	"es"
#define estoniano	"et"
#define finland�s	"fi"
#define franc�s		"fr"
#define galego		"gl"
#define gales		"cy"
#define georgiano	"ka"
#define grego		"el"
#define hebraico	"iw"
#define hindi		"hi"
#define holandes	"nl"
#define h�ngaro		"hu"
#define indon�sio	"id"
#define ingles		"en"
#define irland�s	"ga"
#define island�s	"is"
#define italiano	"it"
#define japon�s		"ja"
#define latim		"la"
#define let�o		"lv"
#define lituano		"lt"
#define maced�nico	"mk"
#define malaio		"ms"
#define maltes		"mt"
#define noruegu�s	"no"
#define persa		"fa"
#define polones		"pl"
#define portugues	"pt"
#define romeno		"ro"
#define russo		"ru"
#define servio		"sr"
#define suaile		"sw"
#define sueco		"sv"
#define tagalo		"tl"
#define tailand�s	"th"
#define tcheco		"cs"
#define turco		"tr"
#define ucraniano	"uk"
#define urdu		"ur"
#define vietnamita	"vi"
#define yiddish		"yi"

#define traducao	"brunosilva.net16.net/tradutor.php"


stock SendTranslatedMessage( playerid, color, string[], entrada[] = detectar, linguagem[] ) {

	static buffer[255];
	format(buffer, 255, traducao"?texto=%s&entrada=%s&saida=%s", urlencode(string), entrada, linguagem);

    arraySet(tradutor, playerid, color);
	return HTTP( playerid == -1 ? MAX_PLAYERS + 1 : playerid, HTTP_GET , buffer , "\0", "RespostaTraducao");
}

stock SendTranslatedMessageToAll( color, string[], linguagem[]) {
		// sei que � melhor por defines, mas como fica com uma sintaxe mais abrangente fiz por fun��o
		return SendClientTranslatedMessage( -1, color, string, linguagem);
}


forward RespostaTraducao( playerid, resposta, data[]); public RespostaTraducao( playerid, resposta, data[]) {

	if(resposta == 200)	{
	    data[strfind(data, "<!-- Hosting24 Analytics Code -->")] = 0;
	    
	    ////////////
	    print(data);

		if( MAX_PLAYERS + 1 == playerid )
		
		    SendClientMessageToAll( arrayGet(tradutor, MAX_PLAYERS + 1) , data ) ;


		else
		    SendClientMessage( playerid, arrayGet(tradutor, playerid) , data );

		/////////////
		
		arraySet(tradutor, playerid, 0);
	}
	
	return true;
}


////////////////////////////////////////////////////////////////////////////////
//
// URL ENCODE CRIADO POR DRACOBLUE
//
////////////////////////////////////////////////////////////////////////////////

stock urlencode(string[]) {
    new ret[0xff];
    ret[0] = 0;
    new i = 0;
    new p = 0;
    new s = 0;
    while (string[i] != 0) {
        if  (
                (string[i] >= 'A' && string[i] <='Z')
                || (string[i] >= 'a' && string[i] <='z')
                || (string[i] >= '0' && string[i] <='9')
                || (string[i] == '-')
                || (string[i] == '_')
                || (string[i] == '.')
            ) {
                ret[p] = string[i];
            } else {
                //
                ret[p] = '%';
                p++;
                s = (string[i] % 16); //
                ret[p+1] = (s>9) ? (55+s) : (48+s); // 64 - 9 = 55
                s = floatround((string[i] - s)/16);
                ret[p] = (s>9) ? (55+s) : (48+s); // 64 - 9 = 55
                p++;
            }
        p++;
        i++;
    }
    return ret;
}