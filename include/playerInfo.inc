#if defined _playerInfo_included
	#endinput
#endif
#define _playerInfo_included
#pragma library playerInfo

#define GENDER_MALE     1
#define GENDER_FEMALE   2

enum e_pInfo {
	keys[2],
	team_id,
	gender
}

new PlayerInfo[MAX_PLAYERS][e_pInfo];

stock loadPlayerInfo(playerid)
{
    new DB:db_handle;
    
	PlayerInfo[playerid][keys][0] = new_dynamic_data_int();//type_key
	PlayerInfo[playerid][keys][1] = new_dynamic_data_int();//key
	
	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
		SendRconCommand("exit");
	}
	else
	{
		new DBResult:db_result;
		new str_query[127];
		new player_name[24];
		GetPlayerName(playerid, player_name, 24);
		
		//
		
		PlayerInfo[playerid][gender] = GENDER_MALE;
		//
		
		//player table
		format(str_query, 127,
			"SELECT `skin` FROM `player` WHERE `name` = '%s'", player_name);
		db_result = db_query(db_handle, str_query);
		if(db_num_rows(db_result) > 0)
		{
			SetPlayerSkin(playerid, db_get_field_int(db_result, 0));
		}
		db_free_result(db_result);
		//
		//player keys table
		format(str_query, 127, "SELECT * FROM `player_keys` WHERE \
			`id` = (SELECT `n` FROM `player` WHERE `nome` = '%s')", player_name);
		db_result = db_query(db_handle, str_query);

		do
		{
		    add_dynamic_data_int(PlayerInfo[playerid][keys][0],
				db_get_field_int(db_result, 1));
			add_dynamic_data_int(PlayerInfo[playerid][keys][1],
				db_get_field_int(db_result, 2));
		}
		while(db_next_row(db_result));
		
		db_free_result(db_result);
		//
		//player team table
		format(str_query, 127,
			"SELECT `teamid` FROM `team_members` WHERE `name` = '%s'", player_name);
		db_result = db_query(db_handle, str_query);
		if(db_num_rows(db_result) > 0)
		{
		    PlayerInfo[playerid][team_id] = db_get_field_int(db_result, 0);
			addTeamMember(db_get_field_int(db_result, 0), playerid);
			//welcome message
		}
		db_free_result(db_result);
		//
		
	}
	db_close(db_handle);
}

stock savePlayerInfo(playerid)
{
	new DB:db_handle;
	
	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
		SendRconCommand("exit");
	}
	else
	{
	    new DBResult:db_result;
		new str_query[127];
		new player_name[24];
		new n_reg, t, k;
		new size = size_dynamic_data_int(PlayerInfo[playerid][keys][0]);
		
		GetPlayerName(playerid, player_name, 24);
		//player table
		format(str_query, 127,
				"UPDATE `player` SET `skin`=%d WHERE `name` = '%s'",
				GetPlayerSkin(playerid), player_name);
		db_query(db_handle, str_query);
		
		format(str_query, 127, "SELECT `n` FROM `player` WHERE `nome` = '%s'", player_name);
		db_result = db_query(db_handle, str_query);
		n_reg = db_get_field_int(db_result, 0);
		db_free_result(db_result);
		
		for(new p = 0; p < size; p++)
		{
		    t = get_dynamic_data_int(PlayerInfo[playerid][keys][0], p);
		    k = get_dynamic_data_int(PlayerInfo[playerid][keys][1], p);
		    format(str_query, 127, "INSERT INTO `player_keys`(`id`,`type`,`key`) \
						VALUES(%d,%d,%d)", n_reg, t, k);
            db_query(db_handle, str_query);
		}
		
		//free dynamic data
		
	}
	db_close(db_handle);
}

stock playerHasKey(playerid, key_type, key)
{
	return (find_dynamic_data_int(PlayerInfo[playerid][keys][0], key_type)
		!= INVALID_DYNAMIC_DATA_POS &&
			find_dynamic_data_int(PlayerInfo[playerid][keys][1], key)
		!= INVALID_DYNAMIC_DATA_POS);
}

stock addPlayerKey(playerid, key_type, key)
{
    add_dynamic_data_int(PlayerInfo[playerid][keys][0], key_type);
	add_dynamic_data_int(PlayerInfo[playerid][keys][1], key);
}

stock removePlayerKey(playerid, key_type, key)
{
    remove_dynamic_data_int(PlayerInfo[playerid][keys][0], key_type);
	remove_dynamic_data_int(PlayerInfo[playerid][keys][1], key);
}
