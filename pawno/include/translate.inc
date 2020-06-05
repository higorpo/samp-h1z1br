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
//          Acesse meu blog sobre programação www.brunodasilva.com
//
//              Seja membro da melhor equipe de programação
//         http://ips-team.forumeiros.com/t2-informacao-inscricao-na-ips

//                    [iPs]TeaM soluções de programação em geral
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////

#include a_samp
#include a_http

#include IPS/dynamic

#define detectar    "auto"

#define africâner	"af"
#define albanês		"sq"
#define alemão		"de"
#define arabe		"ar"
#define armenio		"hy"
#define azerbaijano	"az"
#define basco		"eu"
#define bielo-russo	"be"
#define búlgaro		"bg"
#define catalao		"ca"
#define chinesS		"zh-CN"
#define coreano		"ko"
#define Haitiano 	"ht"
#define croata		"hr"
#define dinamarquês	"da"
#define eslovaco	"sk"
#define esloveno	"sl"
#define espanhol	"es"
#define estoniano	"et"
#define finlandês	"fi"
#define francês		"fr"
#define galego		"gl"
#define gales		"cy"
#define georgiano	"ka"
#define grego		"el"
#define hebraico	"iw"
#define hindi		"hi"
#define holandes	"nl"
#define húngaro		"hu"
#define indonésio	"id"
#define ingles		"en"
#define irlandês	"ga"
#define islandês	"is"
#define italiano	"it"
#define japonês		"ja"
#define latim		"la"
#define letão		"lv"
#define lituano		"lt"
#define macedônico	"mk"
#define malaio		"ms"
#define maltes		"mt"
#define norueguês	"no"
#define persa		"fa"
#define polones		"pl"
#define português	"pt"
#define romeno		"ro"
#define russo		"ru"
#define servio		"sr"
#define suaile		"sw"
#define sueco		"sv"
#define tagalo		"tl"
#define tailandês	"th"
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
		// sei que é melhor por defines, mas como fica com uma sintaxe mais abrangente fiz por função
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