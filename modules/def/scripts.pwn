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


/* Hooks */
    #define PlayerTextDraw OnPlayerClickPlayerTextDraw
    #define Kick(%0) SetTimerEx("Kicka", 100, false, "i", %0)
    #define Ban(%0) SetTimerEx("Bana", 100, false, "i", %0)




/* Funções em geral */
    // Forwards
    forward Kicka(p);
    forward Bana(p);


    // Funções
    public Kicka(p) 
    {
        #undef Kick
        Kick(p);
        #define Kick(%0) SetTimerEx("Kicka", 100, false, "i", %0)
        return 1;
    }

    public Bana(p) 
    {
        #undef Ban
        Ban(p);
        #define Ban(%0) SetTimerEx("Bana", 100, false, "i", %0)
        return 1;
    }

    IsNumeric(const string[])
    {
        for (new i = 0, j = strlen(string); i < j; i++)
        {
            if (string[i] > '9' || string[i] < '0') return 0;
        }
        return 1;
    }



    //-----------------------------------------------------------------------------------------------



    /* Funções relaciodas ao player */
    ProxDetector(Float:radi, playerid, string[], color)
    {
        new Float:x,Float:y,Float:z;
        GetPlayerPos(playerid,x,y,z);
        foreach(new i : Player)
        {
            if(IsPlayerInRangeOfPoint(i,radi,x,y,z))
            {
                SendClientMessage(i,color,string);
            }
        }
    }