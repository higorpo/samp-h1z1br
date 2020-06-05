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


/* Includes necessárias para o bom funcionamento do script */
#include <YSI\y_hooks>


//------------------------------------------------------------------------------------------------------------------------------------------

hook OnGameModeInit()
{
	SetTimer("@TimerOneSecond", 1000, true);
	
	LoadTextDraws();
	
	LastItemID = 0;
	return 1;
}

hook OnPlayerConnect(playerid)
{
	ResetVariables(playerid);
	
    for(new i = 0; i < 10; i++)
	   	RemovePlayerAttachedObject(playerid, i);

    pInventory[playerid][invSelectedSlot] = -1;
    pCharacter[playerid][charSelectedSlot] = -1;
    
   	LoadPlayerTextDraws(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(Player[playerid][MessageInventory])
	    KillTimer(Player[playerid][MessageInventoryTimer]);

    ResetVariables(playerid);
	return true;
}

hook OnPlayerSpawn(playerid)
{
    //SetPlayerSkin(playerid, 292);
	return true;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == Text:INVALID_TEXT_DRAW)
	{
	    if(Player[playerid][inInventory])
	    	HideInventory(playerid);
	}
    else if(clickedid == inventario_close[0])
    {
        HideInventory(playerid);
    }
    else if(clickedid == inventario_usar)
    {
        if(pInventory[playerid][invSelectedSlot] == -1)
            return 0;

		new slot = pInventory[playerid][invSelectedSlot];
		
		pInventory[playerid][invSelectedSlot] = -1;
        UseItem(playerid, slot, Itens[pInventory[playerid][invSlot][slot]][item_id]);
    }
    else if(clickedid == inventario_split[0])
    {
        if(pInventory[playerid][invSelectedSlot] == -1)
            return 0;
            
        if(InventoryFull(playerid))
            return ShowMessageInventory(playerid, "~r~ERRO: ~w~Seu inventário está cheio.");
            
        new slot = pInventory[playerid][invSelectedSlot];

		if(pInventory[playerid][invSlotAmount][slot] <= 1)
            return ShowMessageInventory(playerid, "~r~ERRO: ~w~Você não pode dividir esse item.");
            
        SplitItem(playerid, pInventory[playerid][invSelectedSlot]);
    }
    else if(clickedid == inventario_drop[0])
    {
        if(pInventory[playerid][invSelectedSlot] == -1)
            return 0;
            
        new slot = pInventory[playerid][invSelectedSlot];
        new itemid = pInventory[playerid][invSlot][slot];
        new amount = pInventory[playerid][invSlotAmount][slot];
        new Float:armourstatus = pInventory[playerid][invArmourStatus][slot];
		new Float:pos[3];
		
		if(!Itens[itemid][item_canbedropped])
			return ShowMessageInventory(playerid, "~r~ERRO: ~w~Você não pode dropar esse item.");
		
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		if(itemid == 6)
			DropItem(pos[0], pos[1], pos[2], itemid, amount, armourstatus);
		else
	    	DropItem(pos[0], pos[1], pos[2], itemid, amount);
	    	
		RemoveItemFromInventory(playerid, slot);
		
	   	for(new a = 0; a < 4; a++)
		   	PlayerTextDrawHide(playerid, inventario_description[playerid][a]);

		TextDrawHideForPlayer(playerid, inventario_backgrounds[4]);
		
		pInventory[playerid][invSelectedSlot] = -1;

    }
    else if(clickedid == inventario_remover)
    {
        if(pCharacter[playerid][charSelectedSlot] == -1)
            return 0;
        
  	    if(InventoryFull(playerid))
	        return ShowMessageInventory(playerid, "~r~ERRO: ~w~Seu inventário está cheio.");

        new selected = pCharacter[playerid][charSelectedSlot];

		if(selected == 2)
        	if(SlotsInUse(playerid) > 5)
	        	return ShowMessageInventory(playerid,"~r~ERRO: ~w~Esvazie os itens de sua mochila.");
	        	
  		if(selected == 2)
        	if(SlotsInUse(playerid) >= 5)
	        	return ShowMessageInventory(playerid,"~r~ERRO: ~w~Não tem espaço no seu inventário.");
        
        if(selected == 1)
            AddItem(playerid, pCharacter[playerid][charSlot][selected], 1, pCharacter[playerid][charArmourStatus]);
        else if(Itens[pCharacter[playerid][charSlot][selected]][item_id] == 5 || Itens[pCharacter[playerid][charSlot][selected]][item_id] == 17)
        {
	        new weapons[13][2];

	        for (new s = 0; s <= 12; s++)
			    GetPlayerWeaponData(playerid, s, weapons[s][0], weapons[s][1]);

            AddItem(playerid, pCharacter[playerid][charSlot][selected], weapons[8][1]);
		}
        else
        	AddItem(playerid, pCharacter[playerid][charSlot][selected], 1);
        	
        RemoveItemFromCharacter(playerid, selected);
	   	
		pCharacter[playerid][charSelectedSlot] = -1;
    }

	return 1;
}

inv_PlayerClickPlayerTextdraw(playerid, PlayerText:playertextid)
{
    for(new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    	if(playertextid == inventario_index[playerid][i])
    	{
    	    if(pInventory[playerid][invSlot][i] == 0)
    	        break;
    	        
    	    if(pInventory[playerid][invSelectedSlot] == i)
    	    {
    	        PlayerTextDrawBackgroundColor(playerid, inventario_index[playerid][i], 96);
    	        pInventory[playerid][invSelectedSlot] = -1;
    	        PlayerTextDrawHide(playerid, inventario_index[playerid][i]);
				PlayerTextDrawShow(playerid, inventario_index[playerid][i]);
				
				for(new a = 0; a < 4; a++)
		    		PlayerTextDrawHide(playerid, inventario_description[playerid][a]);
		    		
                TextDrawHideForPlayer(playerid, inventario_backgrounds[4]);
                
               	TextDrawHideForPlayer(playerid, inventario_usar);
				TextDrawHideForPlayer(playerid, inventario_split[0]);
				TextDrawHideForPlayer(playerid, inventario_split[1]);
				TextDrawHideForPlayer(playerid, inventario_drop[0]);
				TextDrawHideForPlayer(playerid, inventario_drop[1]);
				
				PlayerTextDrawHide(playerid, inventario_textos[playerid][9]);
		    		
				break;
			}
			else if(pInventory[playerid][invSelectedSlot] != -1)
			{
    	        PlayerTextDrawBackgroundColor(playerid, inventario_index[playerid][pInventory[playerid][invSelectedSlot]], 96);
    	        PlayerTextDrawHide(playerid, inventario_index[playerid][pInventory[playerid][invSelectedSlot]]);
				PlayerTextDrawShow(playerid, inventario_index[playerid][pInventory[playerid][invSelectedSlot]]);
			}
			
            PlayerTextDrawBackgroundColor(playerid, inventario_index[playerid][i], 0xFFFFFF50);

			PlayerTextDrawHide(playerid, inventario_index[playerid][i]);
			PlayerTextDrawShow(playerid, inventario_index[playerid][i]);
			
			// Descrição do Item
			
			PlayerTextDrawSetPreviewModel(playerid, inventario_description[playerid][0], Itens[pInventory[playerid][invSlot][i]][item_modelo]);
            PlayerTextDrawSetPreviewRot(playerid, inventario_description[playerid][0], Itens[pInventory[playerid][invSlot][i]][item_previewrot][0], Itens[pInventory[playerid][invSlot][i]][item_previewrot][1], Itens[pInventory[playerid][invSlot][i]][item_previewrot][2], Itens[pInventory[playerid][invSlot][i]][item_previewrot][3]);
            PlayerTextDrawShow(playerid, inventario_description[playerid][0]);

			PlayerTextDrawSetString(playerid, inventario_description[playerid][1], ConvertToGameText(Itens[pInventory[playerid][invSlot][i]][item_nome]));
			PlayerTextDrawSetString(playerid, inventario_description[playerid][2], ConvertToGameText(Itens[pInventory[playerid][invSlot][i]][item_description]));
			
			if(Itens[pInventory[playerid][invSlot][i]][item_tipo] == ITEM_TYPE_BODY)
			    format(invString, sizeof(invString), "Durabilidade: %.1f", pInventory[playerid][invArmourStatus][i]);
			else if(pInventory[playerid][invSlotAmount][i] > 1)
				format(invString, sizeof(invString), "Quantidade: %d", pInventory[playerid][invSlotAmount][i]);
			else
				invString = " ";
				
			PlayerTextDrawSetString(playerid, inventario_description[playerid][3], invString);

			if(pInventory[playerid][invSelectedSlot] == -1)
			{
	            TextDrawShowForPlayer(playerid, inventario_usar);
			    TextDrawShowForPlayer(playerid, inventario_split[0]);
			    TextDrawShowForPlayer(playerid, inventario_split[1]);
			    TextDrawShowForPlayer(playerid, inventario_drop[0]);
			    TextDrawShowForPlayer(playerid, inventario_drop[1]);
			    PlayerTextDrawShow(playerid, inventario_textos[playerid][9]);
			    
			    for(new a = 0; a < 4; a++)
    				PlayerTextDrawShow(playerid, inventario_description[playerid][a]);

                TextDrawShowForPlayer(playerid, inventario_backgrounds[4]);
			}
		    
		    pInventory[playerid][invSelectedSlot] = i;
			break;
    	}

    for(new i = 0; i < 7; i++)
    	if(playertextid == inventario_personagemindex[playerid][i])
		{
		    if(pCharacter[playerid][charSlot][i] == 0)
    	        break;
    	        
		    if(pCharacter[playerid][charSelectedSlot] == i)
    	    {
    	        PlayerTextDrawBackgroundColor(playerid, inventario_personagemindex[playerid][i], 96);
    	        PlayerTextDrawHide(playerid, inventario_personagemindex[playerid][i]);
				PlayerTextDrawShow(playerid, inventario_personagemindex[playerid][i]);
    	        pCharacter[playerid][charSelectedSlot] = -1;

				PlayerTextDrawHide(playerid, inventario_textos[playerid][10]);
				TextDrawHideForPlayer(playerid, inventario_remover);
				break;
    	    }
    	    else if(pCharacter[playerid][charSelectedSlot] != -1)
    	    {
    	        new char_slot = pCharacter[playerid][charSelectedSlot];
    	        PlayerTextDrawBackgroundColor(playerid, inventario_personagemindex[playerid][char_slot], 96);
    	        PlayerTextDrawHide(playerid, inventario_personagemindex[playerid][char_slot]);
				PlayerTextDrawShow(playerid, inventario_personagemindex[playerid][char_slot]);
    	    }
    	    
		    PlayerTextDrawBackgroundColor(playerid, inventario_personagemindex[playerid][i], 0xFFFFFF50);
			PlayerTextDrawHide(playerid, inventario_personagemindex[playerid][i]);
			PlayerTextDrawShow(playerid, inventario_personagemindex[playerid][i]);

			if(pCharacter[playerid][charSelectedSlot] == -1)
			{
				PlayerTextDrawShow(playerid, inventario_textos[playerid][10]);
				TextDrawShowForPlayer(playerid, inventario_remover);
			}
			
			pCharacter[playerid][charSelectedSlot] = i;
			break;
		}
		
	return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	new bool:valid_shot = true;
	
    new ammu_slot = GetAmmunationSlot(playerid);
	    
	if(ammu_slot == -1)
	{
	    for(new s = 3; s < 7; s ++)
    	    if(Itens[pCharacter[playerid][charSlot][s]][item_tipo] != ITEM_TYPE_MELEEWEAPON)
	    	    if(pCharacter[playerid][charSlot][s] != 0)
	    	    {
				    AddItem(playerid, pCharacter[playerid][charSlot][s], 1);
			    	RemoveItemFromCharacter(playerid, s);
				}
				
		return false;
	}

    pInventory[playerid][invSlotAmount][GetAmmunationSlot(playerid)] --;
	SetPlayerAmmo(playerid, weaponid, GetAmmunation(playerid));

	if(GetAmmunation(playerid) <= 0)
	    for(new s = 3; s < 7; s ++)
    	    if(Itens[pCharacter[playerid][charSlot][s]][item_tipo] != ITEM_TYPE_MELEEWEAPON)
	    	    if(pCharacter[playerid][charSlot][s] != 0)
	    	    {
				    AddItem(playerid, pCharacter[playerid][charSlot][s], 1);
			    	RemoveItemFromCharacter(playerid, s);
			    	valid_shot = false;
				}

	if(pInventory[playerid][invSlotAmount][ammu_slot] <= 0)
		RemoveItemFromInventory(playerid, ammu_slot);
		
	if(valid_shot == false)
		return false;

	return true;
}

hook OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
    if(newkeys == KEY_NO)
	    if(!Player[playerid][inInventory])
		    ShowInventory(playerid);
		    
 	if(newkeys == KEY_CROUCH)
        for(new i = 0; i < MAX_ITENS_WORLD; i++)
        {
            if(ItensWorld[i][world_active])
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, ItensWorld[i][world_position][0], ItensWorld[i][world_position][1], ItensWorld[i][world_position][2]))
                {
                    new bool:sucess = false;

                    if(!InventoryFull(playerid))
                    {
	                    AddItem(playerid, ItensWorld[i][world_itemid], ItensWorld[i][world_amount], ItensWorld[i][world_armourstatus]);
	                    DeleteItemWorld(i);
	                    sucess = true;
					}

					if(!sucess)
	                    for(new a = 0; a < GetSlotsInventory(playerid); a ++)
							if(pInventory[playerid][invSlot][a] == ItensWorld[i][world_itemid])
					            if(Itens[ItensWorld[i][world_itemid]][item_limite] >= ItensWorld[i][world_amount]+pInventory[playerid][invSlotAmount][a])
								{
								    AddItem(playerid, ItensWorld[i][world_itemid], ItensWorld[i][world_amount], ItensWorld[i][world_armourstatus]);
	                   				DeleteItemWorld(i);
	                   				sucess = true;
	                                break;
								}

					if(!sucess)
						ShowMessageInventory(playerid, "~r~ERRO: ~w~Seu inventário está cheio.");
						
					break;
				}
            }
        }

	return true;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
    if(issuerid != INVALID_PLAYER_ID )
        if(bodypart == 9)
            if(weaponid == 23 || weaponid == 24 || weaponid == 25 || weaponid == 34)
	  			if(pCharacter[playerid][charSlot][0] != 0)
				    RemoveItemFromCharacter(playerid, 0);
				else
					SetPlayerHealth(playerid, 0.0);
				
 	return true;
}

hook OnPlayerUpdate(playerid)
{
    new bool:have_fuzil = false;
    for(new s = 3; s < 7; s ++)
    {
	    if(pCharacter[playerid][charSlot][s] == 3 || pCharacter[playerid][charSlot][s] == 9)
		{
		    new weaponid = GetWeaponIDFromModel(Itens[pCharacter[playerid][charSlot][s]][item_modelo]);

		    if(GetPlayerWeapon(playerid) != weaponid)
		        SetPlayerAttachedObject(playerid, 3, Itens[pCharacter[playerid][charSlot][s]][item_modelo], 1, 0.015999,-0.125999,-0.153000,0.000000,-22.700004,0.400000,1.000000,1.000000,1.000000);
		    else
		        RemovePlayerAttachedObject(playerid, 3);
		        
			have_fuzil = true;
		}
		
		if(!have_fuzil && pCharacter[playerid][charSlot][s] == 16)
		{
	        new weaponid = GetWeaponIDFromModel(Itens[pCharacter[playerid][charSlot][s]][item_modelo]);

		    if(GetPlayerWeapon(playerid) != weaponid)
		        SetPlayerAttachedObject(playerid, 3, Itens[pCharacter[playerid][charSlot][s]][item_modelo], 1, 0.015999,-0.125999,-0.153000,0.000000,-22.700004,0.400000,1.000000,1.000000,1.000000);
		    else
		        RemovePlayerAttachedObject(playerid, 3);
		}
		
		if(pCharacter[playerid][charSlot][s] == 10)
		{
		    new weaponid = GetWeaponIDFromModel(Itens[pCharacter[playerid][charSlot][s]][item_modelo]);
		    
		    if(GetPlayerWeapon(playerid) != weaponid)
		    	SetPlayerAttachedObject(playerid, 4, Itens[pCharacter[playerid][charSlot][s]][item_modelo],1,-0.032000,-0.127000,0.000999,20.600004,29.900007,-2.599998,1.000000,1.000000,1.000000);
		    else
		        RemovePlayerAttachedObject(playerid, 4);
		}
		
		if(pCharacter[playerid][charSlot][s] == 2)
		{
		    new weaponid = GetWeaponIDFromModel(Itens[pCharacter[playerid][charSlot][s]][item_modelo]);
		    
		    if(GetPlayerWeapon(playerid) != weaponid)
				SetPlayerAttachedObject(playerid, 5, Itens[pCharacter[playerid][charSlot][s]][item_modelo],1,-0.053999,0.005999,-0.207000,67.899978,-177.600006,-0.400004,1.000000,1.000000,1.000000);
            else
		        RemovePlayerAttachedObject(playerid, 5);
		}
		
		new itemid = pCharacter[playerid][charSlot][s];
		if(Itens[itemid][item_tipo] == ITEM_TYPE_MELEEWEAPON)
		{
		    new weaponid = GetWeaponIDFromModel(Itens[pCharacter[playerid][charSlot][s]][item_modelo]);

		    if(GetPlayerWeapon(playerid) != weaponid)
                SetPlayerAttachedObject(playerid,6,Itens[pCharacter[playerid][charSlot][s]][item_modelo],1,-0.226999,-0.034999,0.211999,-97.999916,-88.000083,3.600018,1.000000,1.000000,1.000000);
			else
		        RemovePlayerAttachedObject(playerid, 6);
		}
	}
	
	return true;
}

//----------------------------------------------------------


CMD:additemtoplayer(playerid, params[])
{
    new
	    id_item, item, amount;

	if(sscanf(params, "uii", id_item, item, amount))
		return SendClientMessage(playerid, -1, "/additem <id/nick> <id do item> <quantidade>");

   	AddItem(id_item, item, amount);
		
	format(invString, sizeof(invString), "additem (%d) (%d) (%d)", id_item, item, amount);
	SendClientMessage(playerid, -1, invString);
	return true;
}

CMD:additem(playerid, params[])
{
    new item[100], amount, Float:Pos[3];
	if(sscanf(params, "s[100]i", item, amount)) return SendClientMessage(playerid, Vermelho, "| ERRO | Digite: /AddItem [ Id do item ] [ Quantidade ]");

	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

	for(new i = 0; i < sizeof(Itens); i++)
	{
		if(!strcmp(Itens[i][item_nome], item))
		{
			AddItemInWord(Pos[0], Pos[1], Pos[2], Itens[i][item_id], amount);
			break;
		}

	}
		
	format(invString, sizeof(invString), "| INFO | Item adicionado com sucesso, configurações: (item id: %d) (amount: %d)", item, amount);
	SendClientMessage(playerid, Verde, invString);
	return 1;
}

//----------------------------------------------------------