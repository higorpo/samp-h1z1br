/*
 * similar_text
 *
 * (c) Copyright 2010-2013, Bruno da Silva
 * Função para checar proximidade de textos
 */
 
#if defined _similart_included
  #endinput
#endif
#define _similart_included

#if !defined MAX_STRING
    #define MAX_STRING 0xff
#endif

stock function_r[MAX_STRING][MAX_STRING];
stock ff_calcule[MAX_STRING][MAX_STRING];
    
    
stock Float:similar_text(texto1[], texto2[]) {

    static len1, len2, x, y ;

    len1 = strlen(texto1);
    len2 = strlen(texto2);

    ff_calcule = function_r ;


    for (x = 1; x <= len2; x++) {
        ff_calcule[x][0] = ff_calcule[x-1][0] + 1;
    }

    for(y = 1; y <= len1; y++) {
        ff_calcule[0][y] = ff_calcule[0][y-1] + 1;
    }

    for (x = 1; x <= len2; x++) {
        for (y = 1; y <= len1; y++) {
            ff_calcule[x][y] = MIN3D(ff_calcule[x-1][y] + 1,ff_calcule[x][y-1] + 1,ff_calcule[x-1][y-1] + _: !(texto1[y-1] == texto2[x-1]));
        }
    }

    return (1.0 - (float(ff_calcule[len2][len1]) / float(max(len1,len2)))) * 100.0;
}

stock MIN3D(v0,v1,v2) {
    return v0 < v1 ? v0 < v2 ? v0 : v2 : v1 < v2 ? v1 : v2;
}

// atualizado 13/10