#if defined _keychain_included
	#endinput
#endif
#define _keychain_included
#pragma library keychain

#define     VEHICLE_KEY		0
#define     HOUSE_KEY		1

new keychain_list[MAX_TEAMS][2];

/*
stock loadKeyChains()
stock teamHasKey(teamid, key_type, key)
stock addTeamKey(teamid, key_type, key)
stock removeTeamKey(teamid, key_type, key)
stock updateKeyChains()
*/

stock loadKeyChains()
{
    new DB:db_handle;
	new i;
	
	for(i = 0; i < MAX_TEAMS; i++)
	{
	    keychain_list[i][0] = new_dynamic_data_int();//key_type
	    keychain_list[i][1] = new_dynamic_data_int();//key
	}
	
	
	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
		SendRconCommand("exit");
	}
	else
	{
		new DBResult:db_result, x = 0;
		db_result = db_query(db_handle, "SELECT * FROM `team_keychain`");
		
		do
		{
		    i = db_get_field_int(db_result, 0);
		    
		    add_dynamic_data_int(keychain_list[i][0],
				db_get_field_int(db_result, 1));
			add_dynamic_data_int(keychain_list[i][1],
				db_get_field_int(db_result, 2));
				
			x++;
		}
		while(db_next_row(db_result));

		printf("%d team keys loaded!", x);
		db_free_result(db_result);
		
	}
	db_close(db_handle);
}

stock teamHasKey(teamid, key_type, key)
{
	return
		(find_dynamic_data_int(keychain_list[teamid][0], key_type) !=
			INVALID_DYNAMIC_DATA_POS &&
		find_dynamic_data_int(keychain_list[teamid][1], key) !=
			INVALID_DYNAMIC_DATA_POS);
}

stock addTeamKey(teamid, key_type, key)
{
    add_dynamic_data_int(keychain_list[teamid][0], key_type);
    add_dynamic_data_int(keychain_list[teamid][1], key);
}

stock removeTeamKey(teamid, key_type, key)
{
    remove_dynamic_data_int(keychain_list[teamid][0], key_type);
    remove_dynamic_data_int(keychain_list[teamid][1], key);
}

stock updateKeyChains()
{
    new DB:db_handle;
    new str_query[127];
	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
	}
	else
	{
	    int size;
	    db_query(db_handle, "DELETE FROM `team_keychain`");
	    
	    for(int teamid = 0; teamid < MAX_TEAMS; teamid++)
	    {
		    size = size_dynamic_data_int(keychain_list[teamid][0]);
		    for(int x = 0; x < size; x++)
		    {
		        format(str_query, 127, "INSERT INTO `team_keychain`(`id`,`type`,`key`) \
								VALUES(%d, %d, %d)", teamid,
								keychain_list[teamid][0], keychain_list[teamid][1]);
				db_query(db_handle, str_query);
		    }
	    }
    }
    db_close(db_handle);
}

