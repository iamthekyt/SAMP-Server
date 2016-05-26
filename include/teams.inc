#if defined _teams_included
	#endinput
#endif
#define _teams_included
#pragma library teams

#define CHOOSE_TEAM             "choose_team"

#define	MAX_TEAMS				4

#define TEAM_NAME_COPS			"Cops"
#define TEAM_NAME_MEDICS		"Medics"
#define TEAM_NAME_YELLOWGANG	"YellowGang"
#define TEAM_NAME_BLUEGANG		"BlueGang"

#define COPS_TEAM				0
#define MEDICS_TEAM				1
#define YELLOW_GANG_TEAM		2
#define BLUE_GANG_TEAM			3

new cops_skins[]		= { 283, 284, 288 };
new medics_skins[]		= { 274, 275, 276 };
new yellowgang_skins[]	= { 108, 109, 110 };
new bluegang_skins[]	= { 173, 174, 175 };

new Float:team_spawn[MAX_TEAMS][4] = {
	{ -2174.8, -2365.3, 32.9, 50.0 },
	{ -2203.9, -2319.5, 30.6, 0.0 },
	{ -1999.8, -2370.1, 30.6, 320.0 },
	{ -2088.6, -2241.2, 31.1, 50.0 }
};

/*
stock loadTeams()
stock chooseTeam(playerid)
stock selectingTeam(playerid, newkeys, oldkeys)
stock joinTeam(playerid, teamid)
stock leaveTeam(playerid)
stock addTeamMember(teamid, playerid)
stock removeTeamMember(teamid, playerid)
*/

enum e_team {
	members_in_game //new_dynamic_data_int();
};

new Team[MAX_TEAMS][e_team];

stock loadTeams()
{
	for(new t = 0; t < MAX_TEAMS; t++)
	{
    	Team[t][members_in_game] = new_dynamic_data_int();
	}
	//load from database
}

stock chooseTeam(playerid)
{
    if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID)
	{
	    //need to leave the car
	}
	
	SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerPos(playerid, -2233.8999, -1736.7, 480.79999);
	SetPlayerFacingAngle(playerid, 50.0);
	SetPlayerCameraPos(playerid, -2236.2207, -1734.6951, 480.91135);
	SetPlayerCameraLookAt(playerid, -2233.8999, -1736.7, 480.79999);
	
	SetPVarInt(playerid, CHOOSE_TEAM, 1);
	SetPlayerSkin(playerid, cops_skins[random(sizeof(cops_skins))]);
	
	TextDrawShowForPlayer(playerid, choose_skin[0]);
	TextDrawShowForPlayer(playerid, choose_skin[1]);
	PlayerTextDrawShow(playerid, p_choose_team);
}

stock selectingTeam(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SPRINT))
    {
		new teamid = GetPVarInt(playerid, CHOOSE_TEAM) - 1;

		joinTeam(playerid, teamid);

        SetPlayerPos(playerid, team_spawn[teamid][0],
			team_spawn[teamid][1], team_spawn[teamid][2]);
		SetPlayerFacingAngle(playerid, team_spawn[teamid][3]);
		SetCameraBehindPlayer(playerid);
		SetPlayerVirtualWorld(playerid, 0);
		
		TextDrawHideForPlayer(playerid, choose_skin[0]);
		TextDrawHideForPlayer(playerid, choose_skin[1]);
		PlayerTextDrawHide(playerid, p_choose_team);

		DeletePVar(playerid, CHOOSE_TEAM);
    }
    else
    {
	    new teamid = GetPVarInt(playerid, CHOOSE_TEAM) - 1;
	    new teamName[MAX_TEAMS][24] = {
				TEAM_NAME_COPS, TEAM_NAME_MEDICS,
				TEAM_NAME_YELLOWGANG, TEAM_NAME_BLUEGANG };
        new new_skin;
        new str_td[32];
        
	    if (PRESSED(KEY_FIRE))
	    {
	        teamid --;
	        if(teamid == -1)
	        {
	            teamid = MAX_TEAMS - 1;
	        }
	    }
	    else if (PRESSED(KEY_HANDBRAKE))
	    {
	        teamid ++;
	        if(teamid == MAX_TEAMS)
	        {
	            teamid = 0;
	        }
	    }
	    
        switch(teamid)
        {
            case 0: { new_skin = cops_skins[random(sizeof(cops_skins))]; }
            case 1: { new_skin = medics_skins[random(sizeof(medics_skins))]; }
            case 2: { new_skin = yellowgang_skins[random(sizeof(yellowgang_skins))]; }
            case 3: { new_skin = bluegang_skins[random(sizeof(bluegang_skins))]; }
        }
        format(str_td, 32, "Team_:_%s", teamName[teamid]);
        SetPlayerSkin(playerid, new_skin);
        PlayerTextDrawSetString(playerid, p_choose_team, str_td);

        SetPVarInt(playerid, CHOOSE_TEAM, teamid + 1);
    }
}

stock joinTeam(playerid, teamid)
{
	if(GetPlayerTeam(playerid) != NO_TEAM)
	{
	    leaveTeam(playerid);
	}
	
	new DB:db_handle;

	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
	}
	else
	{
		new str_query[127];
		new player_name[24];
		
		GetPlayerName(playerid, player_name, 24);
		format(str_query, 127, "INSERT INTO `team_members`(`teamid`,`name`) VALUES(%d, '%s')",
			teamid, player_name);
		db_query(db_handle, str_query);
		
		format(str_query, 127, "%s joined your team!", player_name);
		for(new m = 0; m < size_dynamic_data_int(Team[teamid][members_in_game]); m++)
	    {
	        SendClientMessage(get_dynamic_data_int(Team[teamid][members_in_game], m),
				0x00FF00, str_query);
	    }
	    SendClientMessage(playerid, 0x00FF00, "You joined to a new team!");
	    addTeamMember(teamid, playerid);
	}
	db_close(db_handle);
}

stock leaveTeam(playerid)
{
	new teamid = GetPlayerTeam(playerid);
	
	if(GetPlayerVehicleID(playerid) != 0)
	{
	    //need to leave the car
	}
    else if(teamid != NO_TEAM)
	{
	    new DB:db_handle;

		if((db_handle = db_open("JustFunDB.db")) == DB:0)
		{
			print("Failed to open a connection to \"JustFunDB.db\".");
		}
		else
		{
		    new str_query[127];
		    new player_name[24];
		    GetPlayerName(playerid, player_name, 24);
		    
			format(str_query, 127,
				"DELETE FROM `team_members` WHERE `name`='%s'", player_name);
			db_query(db_handle, str_query);
			
			format(str_query, 127, "%s left your team!", player_name);
			for(new m = 0; m < size_dynamic_data_int(Team[teamid][members_in_game]); m++)
		    {
		        SendClientMessage(get_dynamic_data_int(Team[teamid][members_in_game], m),
					0xFF0000, str_query);
		    }
		    SendClientMessage(playerid, 0xFF0000, "You left the team!");
		    removeTeamMember(teamid, playerid);
		    //choose a random skin
		}
		db_close(db_handle);
    }
}

stock addTeamMember(teamid, playerid)
{
    add_dynamic_data_int(Team[teamid][members_in_game], playerid);
    SetPlayerTeam(playerid, teamid);
}

stock removeTeamMember(teamid, playerid)
{
	if(GetPlayerTeam(playerid) == teamid)
	{
	    remove_dynamic_data_int(Team[teamid][members_in_game], playerid);
	    SetPlayerTeam(playerid, NO_TEAM);
	}
}
