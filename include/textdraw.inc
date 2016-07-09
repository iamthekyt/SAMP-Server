#if defined _textdraw_included
	#endinput
#endif
#define _textdraw_included
#pragma library textdraw

#define MAX_WEAPON_SLOTS_PER_PLAYER		13
#define MAX_BASE_TD_TRUNK               6

new PlayerText:td_trunk_p[MAX_PLAYERS][MAX_WEAPON_SLOTS_PER_PLAYER];
new Text:td_trunk_b[MAX_BASE_TD_TRUNK];
new Text:td_trunk[MAX_WEAPON_PER_CAR];

new PlayerText:p_choose_team;
new Text:choose_skin[2];

/*
stock createGlobalTextDraw()
stock createPlayerTextDraw(playerid)
stock destroyPlayerTextDraw(playerid)
//
stock updateTextDrawTrunk(playerid)
stock hideTextDrawTrunk(playerid)
stock trunk_clickPlayerTD(playerid, PlayerText:playertextid)
stock trunk_clickTD(playerid, Text:clickedid)
*/

forward updateTextDrawTrunk(playerid);
forward hideTextDrawTrunk(playerid);

stock createGlobalTextDraw()
{
	new i;
	
	td_trunk_b[0] = TextDrawCreate(472.974151, 76.506744, "l");
	TextDrawLetterSize(td_trunk_b[0], 0.399998, 41.360008);
	TextDrawAlignment(td_trunk_b[0], 1);
	TextDrawColor(td_trunk_b[0], -1);
	TextDrawSetShadow(td_trunk_b[0], 0);

	td_trunk_b[1] = TextDrawCreate(320.948913, 145.199890, "_");
	TextDrawLetterSize(td_trunk_b[1], 0.536875, 28.621870);
	TextDrawTextSize(td_trunk_b[1], 629.000000, 0.000000);
	TextDrawAlignment(td_trunk_b[1], 1);
	TextDrawUseBox(td_trunk_b[1], 1);
	TextDrawBoxColor(td_trunk_b[1], 0xFFB90F7F);

	td_trunk_b[2] = TextDrawCreate(483.749084, 380.400207, "<<<");
	TextDrawLetterSize(td_trunk_b[2], 0.426875, 1.816533);
	TextDrawTextSize(td_trunk_b[2], 519.000000, 10.000000);
	TextDrawAlignment(td_trunk_b[2], 1);
	TextDrawColor(td_trunk_b[2], -1);
	TextDrawFont(td_trunk_b[2], 1);
	TextDrawSetSelectable(td_trunk_b[2], true);

	td_trunk_b[3] = TextDrawCreate(433.849090, 381.146911, ">>>");
	TextDrawLetterSize(td_trunk_b[3], 0.426250, 1.824000);
	TextDrawTextSize(td_trunk_b[3], 467.000000, 10.000000);
	TextDrawAlignment(td_trunk_b[3], 1);
	TextDrawColor(td_trunk_b[3], -1);
	TextDrawFont(td_trunk_b[3], 1);
	TextDrawSetSelectable(td_trunk_b[3], true);

    td_trunk_b[4] = TextDrawCreate(393.750000, 137.733337, "YOU");
	TextDrawLetterSize(td_trunk_b[4], 0.480000, 2.309333);
	TextDrawAlignment(td_trunk_b[4], 2);
	TextDrawColor(td_trunk_b[4], -1);
	TextDrawFont(td_trunk_b[4], 2);

	td_trunk_b[5] = TextDrawCreate(560.625000, 137.733337, "VEHICLE");
	TextDrawLetterSize(td_trunk_b[5], 0.480000, 2.309333);
	TextDrawAlignment(td_trunk_b[5], 2);
	TextDrawColor(td_trunk_b[5], -1);
	TextDrawFont(td_trunk_b[5], 2);
	

	for(i = 0; i < MAX_WEAPON_PER_CAR; i++)
	{
		td_trunk[i] = TextDrawCreate(555.625000, 160.133255 + 20.0 * i, "A");//weapon name
		TextDrawLetterSize(td_trunk[i], 0.426250, 1.824000);
		TextDrawTextSize(td_trunk[i], 10.000000, 141.000000);
		TextDrawAlignment(td_trunk[i], 2);
		TextDrawColor(td_trunk[i], -1);
		TextDrawFont(td_trunk[i], 1);
		TextDrawSetSelectable(td_trunk[i], true);
		TextDrawSetShadow(td_trunk[i], 0);
	}
	
	//choose team
	
	choose_skin[0] = TextDrawCreate(259.375000, 350.533599,
		"Use_~r~~k~~PED_FIREWEAPON~~w~_&_~r~~k~~PED_LOCK_TARGET~~w~_para_escolher");
	TextDrawLetterSize(choose_skin[0], 0.400000, 1.600000);
	TextDrawAlignment(choose_skin[0], 2);
	TextDrawColor(choose_skin[0], -1);
	TextDrawSetShadow(choose_skin[0], 0);
	TextDrawSetOutline(choose_skin[0], 0);
	TextDrawBackgroundColor(choose_skin[0], 255);
	TextDrawFont(choose_skin[0], 1);
	TextDrawSetProportional(choose_skin[0], 1);
	TextDrawSetShadow(choose_skin[0], 0);

	choose_skin[1] = TextDrawCreate(260.625000, 366.213439,
		"Use_~r~~k~~PED_SPRINT~~w~_para_selecionar");
	TextDrawLetterSize(choose_skin[1], 0.400000, 1.600000);
	TextDrawAlignment(choose_skin[1], 2);
	TextDrawColor(choose_skin[1], -1);
	TextDrawSetShadow(choose_skin[1], 0);
	TextDrawSetOutline(choose_skin[1], 0);
	TextDrawBackgroundColor(choose_skin[1], 255);
	TextDrawFont(choose_skin[1], 1);
	TextDrawSetProportional(choose_skin[1], 1);
	TextDrawSetShadow(choose_skin[1], 0);
}

stock createPlayerTextDraw(playerid)
{
	new i;
	//trunk
	for(i = 0; i < MAX_WEAPON_SLOTS_PER_PLAYER; i++)
	{
		td_trunk_p[playerid][i] = CreatePlayerTextDraw(playerid, 395.000000, 160.133285 + 20.0 * i, "A");//weapon name
		PlayerTextDrawLetterSize(playerid, td_trunk_p[playerid][i], 0.400000, 1.600000);
		PlayerTextDrawTextSize(playerid, td_trunk_p[playerid][i], 10.000000, 141.000000);
		PlayerTextDrawAlignment(playerid, td_trunk_p[playerid][i], 2);
		PlayerTextDrawColor(playerid, td_trunk_p[playerid][i], -1);
		PlayerTextDrawFont(playerid, td_trunk_p[playerid][i], 1);
		PlayerTextDrawSetSelectable(playerid, td_trunk_p[playerid][i], true);
		PlayerTextDrawSetShadow(playerid, td_trunk_p[playerid][i], 0);
	}
	//choose team
	p_choose_team = CreatePlayerTextDraw(playerid, 266.875000, 289.306732, "Team_:_Medics");
	PlayerTextDrawLetterSize(playerid, p_choose_team, 1.092499, 6.401065);
	PlayerTextDrawAlignment(playerid, p_choose_team, 2);
	PlayerTextDrawColor(playerid, p_choose_team, -1);
	PlayerTextDrawSetShadow(playerid, p_choose_team, 0);
	PlayerTextDrawSetOutline(playerid, p_choose_team, 0);
	PlayerTextDrawBackgroundColor(playerid, p_choose_team, 255);
	PlayerTextDrawFont(playerid, p_choose_team, 0);
	PlayerTextDrawSetProportional(playerid, p_choose_team, 1);
	PlayerTextDrawSetShadow(playerid, p_choose_team, 0);
}

stock destroyPlayerTextDraw(playerid)
{
	new i;

	for(i = 0; i < MAX_WEAPON_SLOTS_PER_PLAYER; i++)
	{
		PlayerTextDrawDestroy(playerid, td_trunk_p[playerid][i]);
	}
}

public updateTextDrawTrunk(playerid)
{
    new i, j, ammo, weapon, str[40], gunname[32];
    new vehicleid = GetPVarInt(playerid, "trunk_car");
    
    hideTextDrawTrunk(playerid);
    
    for(i = 0; i < MAX_BASE_TD_TRUNK; i++)
    	TextDrawShowForPlayer(playerid, td_trunk_b[i]);
    //
    for(i = 0, j = 0; i < MAX_WEAPON_PER_CAR; i++)
    {
    	getInVehicleTrunk(vehicleid, i, weapon, ammo);
        if(weapon != TRUNK_EMPTY_SLOT)
        {
			GetWeaponName(weapon, gunname, sizeof(gunname));
			format(str, 40, "%s ( %d )", gunname, ammo);

			TextDrawSetString(td_trunk[j], str);
			TextDrawShowForPlayer(playerid, td_trunk[j]);
			j++;
        }
	}
	//
	for(i = 0, j = 0; i < MAX_WEAPON_SLOTS_PER_PLAYER; i++)
    {
        GetPlayerWeaponData(playerid, i, weapon, ammo);
        if(weapon > 0)
		{
            GetWeaponName(weapon, gunname, sizeof(gunname));
			format(str, 40, "%s ( %d )", gunname, ammo);

            PlayerTextDrawSetString(playerid, td_trunk_p[playerid][j], str);
            PlayerTextDrawShow(playerid, td_trunk_p[playerid][j]);
            j++;
        }
    }
    //
	return 1;
}

public hideTextDrawTrunk(playerid)
{
	new i;
	for(i = 0; i < MAX_BASE_TD_TRUNK; i++)
		TextDrawHideForPlayer(playerid, td_trunk_b[i]);
	//
	for(i = 0; i < MAX_WEAPON_PER_CAR; i++)
		TextDrawHideForPlayer(playerid, td_trunk[i]);
	//
	for(i = 0; i < MAX_WEAPON_SLOTS_PER_PLAYER; i++)
		PlayerTextDrawHide(playerid, td_trunk_p[playerid][i]);
		
	return 1;
}

stock trunk_clickPlayerTD(playerid, PlayerText:playertextid)
{
	if(	playertextid >= td_trunk_p[playerid][0] &&
		playertextid <= td_trunk_p[playerid][MAX_WEAPON_SLOTS_PER_PLAYER-1])
	{
	    new i, j, w, weapon, ammo;
		if(!GetPVarInt(playerid, "td_trunk_player"))
		{
		    for(i = 0; i < MAX_WEAPON_SLOTS_PER_PLAYER; i++)
			{
			    if(playertextid == td_trunk_p[playerid][i])
			    {
				    PlayerTextDrawHide(playerid, td_trunk_p[playerid][i]);
				    PlayerTextDrawColor(playerid, td_trunk_p[playerid][i], 0x0000FFFF);
				    PlayerTextDrawShow(playerid, td_trunk_p[playerid][i]);

				    for(w = 0, j = 0; ; j++)
					{
			            GetPlayerWeaponData(playerid, j, weapon, ammo);
			            if(weapon > 0)
						{
						    if(w++ == i)
						    	break;
						}
					}

			        SetPVarInt(playerid, "td_trunk_player", j);
			        SetPVarInt(playerid, "td_selected_player", _:td_trunk_p[playerid][i]);
			        break;
			    }
			}
		}
		else if(GetPVarInt(playerid, "td_selected_player") == _:playertextid)
		{
		    PlayerTextDrawHide(playerid, playertextid);
		    PlayerTextDrawColor(playerid, playertextid, 0xFFFFFFFF);
		    PlayerTextDrawShow(playerid, playertextid);

		    DeletePVar(playerid, "td_trunk_player");
		    DeletePVar(playerid, "td_selected_player");
		    //unselect
		}
		else
		{
		    new PlayerText:t1 = PlayerText:GetPVarInt(playerid, "td_selected_player");
		    PlayerTextDrawHide(playerid, t1);
		    PlayerTextDrawColor(playerid, t1, 0xFFFFFFFF);
		    PlayerTextDrawShow(playerid, t1);

		    for(i = 0; i < MAX_WEAPON_SLOTS_PER_PLAYER; i++)
			{
			    if(playertextid == td_trunk_p[playerid][i])
			    {
			        PlayerTextDrawHide(playerid, td_trunk_p[playerid][i]);
			        PlayerTextDrawColor(playerid, td_trunk_p[playerid][i], 0x0000FFFF);
			        PlayerTextDrawShow(playerid, td_trunk_p[playerid][i]);

		            for(w = 0, j = 0; ; j++)
					{
			            GetPlayerWeaponData(playerid, j, weapon, ammo);
			            if(weapon > 0)
						{
						    if(w++ == i)
						    	break;
						}
					}

			        SetPVarInt(playerid, "td_trunk_player", j);
			        SetPVarInt(playerid, "td_selected_player", _:td_trunk_p[playerid][i]);
			        break;
			    }
			}
		    //select other
		}
	}
}

stock trunk_clickTD(playerid, Text:clickedid)
{
    new i, weapon, ammo, vehicleid;

    if(clickedid == td_trunk_b[2]) // car to player
    {
        i = GetPVarInt(playerid, "td_trunk_car") - 1;
        vehicleid = GetPVarInt(playerid, "trunk_car");
        getInVehicleTrunk(vehicleid, i, weapon, ammo);
        if(weapon > 0)
		{
		    GivePlayerWeapon(playerid, weapon, ammo);
		    removeFromVehicleTrunk(vehicleid, i);
		    SetTimerEx("updateTextDrawTrunk", 100, false, "i", playerid);
        }
        
        new Text:t1 = Text:GetPVarInt(playerid, "td_selected_car");
	    TextDrawHideForPlayer(playerid, t1);
	    TextDrawColor(t1, 0xFFFFFFFF);
	    TextDrawShowForPlayer(playerid, t1);
        
		DeletePVar(playerid, "td_trunk_car");
		DeletePVar(playerid, "td_selected_car");
    }
    else if(clickedid == td_trunk_b[3]) // player to car
    {
    	i = GetPVarInt(playerid, "td_trunk_player");
    	GetPlayerWeaponData(playerid, i, weapon, ammo);
        if(weapon > 0)
		{
		    vehicleid = GetPVarInt(playerid, "trunk_car");
		    i = setInVehicleTrunk(vehicleid, weapon, ammo);
		    if(i)
		    {
		        removePlayerWeapon(playerid, weapon);
		        GetPlayerWeaponData(playerid, i, weapon, ammo);
    			SetTimerEx("updateTextDrawTrunk", 100, false, "i", playerid);
		    }
        }
        
        new PlayerText:t1 = PlayerText:GetPVarInt(playerid, "td_selected_player");
	    PlayerTextDrawHide(playerid, t1);
	    PlayerTextDrawColor(playerid, t1, 0xFFFFFFFF);
	    PlayerTextDrawShow(playerid, t1);
        
        DeletePVar(playerid, "td_trunk_player");
		DeletePVar(playerid, "td_selected_player");
    }
	else if(clickedid >= td_trunk[0] && clickedid <= td_trunk[MAX_WEAPON_PER_CAR-1])
	{
	    for(i = 0; i < MAX_WEAPON_PER_CAR; i++)
		{
		    if(clickedid == td_trunk[i])
		    {
		        if(!GetPVarInt(playerid, "td_trunk_car"))
				{
				    vehicleid = GetPVarInt(playerid, "trunk_car");

				    TextDrawHideForPlayer(playerid, td_trunk[i]);
				    TextDrawColor(td_trunk[i], 0x0000FFFF);
				    TextDrawShowForPlayer(playerid, td_trunk[i]);

		        	getInVehicleTrunk(vehicleid, i, weapon, ammo);
		        	SetPVarInt(playerid, "td_trunk_car", i + 1);
		        	SetPVarInt(playerid, "td_selected_car", _:td_trunk[i]);
		        	break;
				}
				else if(GetPVarInt(playerid, "td_selected_car") == _:clickedid)
				{
				    TextDrawHideForPlayer(playerid, clickedid);
				    TextDrawColor(clickedid, 0xFFFFFFFF);
				    TextDrawShowForPlayer(playerid, clickedid);

				    DeletePVar(playerid, "td_trunk_car");
				    DeletePVar(playerid, "td_selected_car");
				    break;
				    //unselect
				}
				else
				{
					vehicleid = GetPVarInt(playerid, "trunk_car");

				    new Text:t1 = Text:GetPVarInt(playerid, "td_selected_car");
				    TextDrawHideForPlayer(playerid, t1);
				    TextDrawColor(t1, 0xFFFFFFFF);
				    TextDrawShowForPlayer(playerid, t1);

		        	getInVehicleTrunk(vehicleid, i, weapon, ammo);
		        	SetPVarInt(playerid, "td_trunk_car", i + 1);
		        	SetPVarInt(playerid, "td_selected_car", _:td_trunk[i]);
		        	TextDrawColor(td_trunk[i], 0x0000FFFF);
				    break;
				    //select other
				}
		    }
		}
	}
}
