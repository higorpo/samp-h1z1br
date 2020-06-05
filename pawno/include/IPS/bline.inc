
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
//                    Criado por Bruno da Silva (iPs DraKiNs) 
// 
//          Acesse meu blog sobre programação [url]www.brunodasilva.com.br[/url] 
// 
//                    Seja membro de nossa equipe de programação 
//         [url]http://ips-team.forumeiros.com/t2-informacao-inscricao-na-ips[/url] 
// 
//                    [iPs]TeaM soluções de programação em geral 
// 
// 
//                     bLine Files (mais rápido que bini) 
// 
// 
// > Funções < 
// File_Isset(linha) 
// File_Get(linha) 
// File_GetFloat(linha) 
// File_GetInt(linha) 
// File_GetBool(linha) 
// File_SetBool(linha, bool:valor) 
// File_SetPersonal(linha, "format", var) 
// File_SetInt(linha, Int:valor) 
// File_SetFloat(linha, Float:valor) 
// File_Set(linha, string[]) 

// File_Open(arquivo[]) 
// File_Save() // apenas em onGameModeExit para fechar a include 
// 
// 
// 
///////////////////////////////////////////////////////////////////////////////// 

// Configurações 
#define MAX_LINE_FILE   500 
#define MAX_LINE_TEXT   500 
#define MAX_FILE_NAME   064 

// Definições e Declarações 

stock 
	totalLines, 
	bool:fileOpen, 
	bool:fileWrited, 
	_filed[MAX_LINE_TEXT], 
	blineset[MAX_LINE_FILE], 
	fileOpenned[MAX_FILE_NAME], 
	bcache[MAX_LINE_FILE+1][MAX_LINE_TEXT+1]; 

#define File_Isset(%0) \ 
		!!bcache[%0][0] 

#define File_Get(%0) \ 
		bcache[%0] 

#define File_GetFloat(%0) \ 
		floatstr(bcache[%0]) 

#define File_GetInt(%0) \ 
		strval(bcache[%0]) 

#define File_GetBool(%0) \ 
		!strcmp(bcache[%0], "true") 

#define File_SetPersonal(%0,%1,%2) \ 
		File_Set(%0, (format((_filed[0] = EOS, _filed), MAX_LINE_TEXT, %1, %2), _filed)) 

#define File_SetInt(%0,%1) \ 
		File_SetPersonal(%0, "%d", %1) 

#define File_SetFloat(%0,%1) \ 
		File_SetPersonal(%0, "%f", %1) 

// Funções 

stock File_SetBool(line, bool:value) { 
    return value ? File_Set(line, "true") :  File_Set(line, "false"); 
} 


stock File_Set(line, value[]) { 

    if(line > totalLines) { 
        totalLines = line; 
    } 
    blineset[line] = 1; 
    return fileWrited = true, bcache[line][0] = EOS, strcat(bcache[line], value, MAX_LINE_TEXT); 
} 



static
	totalContadoINIHASHFILE
; 
stock File_HashStr(buffer[]) 
{ 
    totalContadoINIHASHFILE = 0; 
    for(new i = strlen(buffer); i != -1; i--) { 
        totalContadoINIHASHFILE += buffer[i]; 
    } 
    return totalContadoINIHASHFILE; 
} 



stock File_Open(file[]) 
{ 

    if(fileOpen && File_HashStr(file) == File_HashStr(fileOpenned) && !strcmp(file, fileOpenned, false)) { 
            return true; 
    } 
    else { 
        File_Save(); 
    } 


    static 
        f_i, 
        len, 
        File: f; 

    f = fopen(file, io_readwrite); 

    if(f) { 
        fileOpenned[0] = EOS; 
        strcat(fileOpenned, file, MAX_FILE_NAME); 
        f_i = 0; 

        while((len = fread(f, bcache[f_i]))) StripNewLine(bcache[f_i], len),++ f_i, blineset[f_i-1] = 1; 

        fclose(f); 

        fileOpen = true; 
        return totalLines = f_i, bcache[f_i +1][0] = EOS, 1; 

    } 
    return false; 
} 


stock File_Save() 
{ 

    if(fileWrited) { 
        if(fileOpenned[0]) { 

            static File: f, f_i, s_I; 

            f = fopen(fileOpenned,  io_write ); 

            { 

                f_i = 0; 

                while(f_i != totalLines +1) { 
                    if(blineset[f_i]) { 
                        s_I = strlen(bcache[f_i]); 

                        StripNewLine(bcache[f_i], s_I); 

                        strcat(bcache[f_i], "\r\n"); 
                        fwrite(f, bcache[f_i]); 

                        blineset[f_i] = 0; 
                    } 
                    f_i++; 
                } 
            } 

            fclose(f); 

            return fileWrited = false, fileOpen = false, bcache[0][0] = EOS, totalLines = 0, fileOpenned[0] = EOS, true; 
        } 
    } 
    return false; 
} 


// By Draco Blue 
stock StripNewLine(string[], len) 
{ 
    if (string[0]==0) return ; 
    if ((string[len - 1] == '\n') || (string[len - 1] == '\r')) { 
        string[len - 1] = 0; 
        if (string[0]==0) return ; 
        if ((string[len - 2] == '\n') || (string[len - 2] == '\r')) string[len - 2] = 0; 
    } 
}  