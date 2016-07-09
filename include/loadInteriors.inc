#if defined _loadInteriors_included
	#endinput
#endif
#define _loadInteriors_included
#pragma library loadInteriors


#define MAX_HOUSES          20
#define MAX_BUSINESS		15
#define MAX_INTERIOR_NAME	32

new house_pickup[MAX_HOUSES];
new business_pickup[MAX_BUSINESS];

enum e_Bus {
	name[MAX_INTERIOR_NAME],
	Float:ix,
	Float:iy,
	Float:iz,
	Float:ia,
	iInt,
	Float:ex,
	Float:ey,
	Float:ez,
	Float:ea
}
new Business[MAX_BUSINESS][e_Bus];

enum e_House {
	owner, //new_dynamic_data_string();
	Float:ix,
	Float:iy,
	Float:iz,
	Float:ia,
	iInt,
	rooms,
	price,
	comment[MAX_INTERIOR_NAME],
	ex, //new_dynamic_data_float(),
	ey, //new_dynamic_data_float(),
	ez, //new_dynamic_data_float(),
	ea //new_dynamic_data_float()
};
new House[MAX_HOUSES][e_House];

/*
stock loadBusiness()
stock loadHouses()
stock process_interior_cmd(playerid)
stock process_visit_house_cmd(playerid)
stock show_interior_info(playerid)
*/

stock loadBusiness()
{
    new DB:db_handle;
    new s_query[64];
	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
		SendRconCommand("exit");
	}
	else
	{
		new DBResult:db_result, DBResult:db_result_int, x = 0;
		db_result = db_query(db_handle, "SELECT * FROM `business`");

        do
		{
		    db_get_field(db_result, 1, Business[x][name], MAX_INTERIOR_NAME );
			Business[x][ex] = db_get_field_float(db_result, 3);
			Business[x][ey] = db_get_field_float(db_result, 4);
			Business[x][ez] = db_get_field_float(db_result, 5);
			Business[x][ea] = db_get_field_float(db_result, 6);
			
			format(s_query, sizeof(s_query),
				"SELECT * FROM `business_int` WHERE `number`=%d",
				db_get_field_int(db_result, 2));
			db_result_int = db_query(db_handle, s_query);
			
			Business[x][iInt] = db_get_field_int(db_result_int, 2);
			Business[x][ix] = db_get_field_float(db_result_int, 3);
			Business[x][iy] = db_get_field_float(db_result_int, 4);
			Business[x][iz] = db_get_field_float(db_result_int, 5);
			Business[x][ia] = db_get_field_float(db_result_int, 6);
			
			db_free_result(db_result_int);
			
			business_pickup[x] = CreatePickup(1272, 1, Business[x][ex],
				Business[x][ey], Business[x][ez], -1);
			x++;
		}
		while(db_next_row(db_result));
		
		printf("%d interiors loaded!", x);
		db_free_result(db_result);
	}
	db_close(db_handle);
}

stock loadHouses()
{

    new DB:db_handle;
    new s_query[64], owner_name[24];
	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
		SendRconCommand("exit");
	}
	else
	{
		new DBResult:db_result, DBResult:db_result_tmp, x = 0;
		db_result = db_query(db_handle, "SELECT * FROM `house`");

        do
		{
		    //interior
		    format(s_query, sizeof(s_query),
				"SELECT * FROM `house_int` WHERE `interior`=%d",
				db_get_field_int(db_result, 1));
			db_result_tmp = db_query(db_handle, s_query);
			
			House[x][ix] = db_get_field_float(db_result_tmp, 1);
			House[x][iy] = db_get_field_float(db_result_tmp, 2);
			House[x][iz] = db_get_field_float(db_result_tmp, 3);
			House[x][ia] = db_get_field_float(db_result_tmp, 4);
			House[x][iInt] = db_get_field_int(db_result_tmp, 5);
			House[x][rooms] = db_get_field_int(db_result_tmp, 6);
			House[x][price] = db_get_field_int(db_result_tmp, 7);
			db_get_field(db_result_tmp, 8, House[x][comment], MAX_INTERIOR_NAME);
			
			db_free_result(db_result_tmp);
		    //
		    //owner
		    format(s_query, sizeof(s_query),
				"SELECT `owner` FROM `house_owner` WHERE `id`=%d",
				db_get_field_int(db_result, 0));
			db_result_tmp = db_query(db_handle, s_query);
			
			House[x][owner] = new_dynamic_data_string();
			if(db_num_rows(db_result_tmp) > 0)
			{
				do
				{
				    db_get_field(db_result_tmp, 0, owner_name, 24);
				    add_dynamic_data_string(House[x][owner], owner_name);
				}
				while(db_next_row(db_result_tmp));
			}
			db_free_result(db_result_tmp);
			//
			//door
			format(s_query, sizeof(s_query),
				"SELECT * FROM `house_door` WHERE `house`=%d",
				db_get_field_int(db_result, 0));
			db_result_tmp = db_query(db_handle, s_query);
			
			House[x][ex] = new_dynamic_data_float();
			House[x][ey] = new_dynamic_data_float();
			House[x][ez] = new_dynamic_data_float();
			House[x][ea] = new_dynamic_data_float();
			if(db_num_rows(db_result_tmp) > 0)
			{
				do
				{
				    add_dynamic_data_float(House[x][ex],
						db_get_field_float(db_result_tmp, 1));
	                add_dynamic_data_float(House[x][ey],
						db_get_field_float(db_result_tmp, 2));
					add_dynamic_data_float(House[x][ez],
						db_get_field_float(db_result_tmp, 3));
					add_dynamic_data_float(House[x][ea],
						db_get_field_float(db_result_tmp, 4));
						
                    house_pickup[x] = CreatePickup(1273, 1,
						db_get_field_float(db_result_tmp, 1),
						db_get_field_float(db_result_tmp, 2),
						db_get_field_float(db_result_tmp, 3),
					-1);
				}
				while(db_next_row(db_result_tmp));
			}
			db_free_result(db_result_tmp);
			//
			
			x++;
		}
		while(db_next_row(db_result));

		printf("%d houses loaded!", x);
		db_free_result(db_result);
	}
	db_close(db_handle);
	//1273
}

stock process_interior_cmd(playerid)
{
    new e;
	if(!GetPlayerInterior(playerid))
	{
		for(e = 0; e < MAX_BUSINESS; e++)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 3.0, Business[e][ex],
				Business[e][ey], Business[e][ez]))
			continue;

			SetPlayerPos(playerid, Business[e][ix], Business[e][iy], Business[e][iz]);
			SetPlayerFacingAngle(playerid, Business[e][ia]);
			SetPlayerInterior(playerid, Business[e][iInt]);
			SetPlayerVirtualWorld(playerid, e);
			break;
		}
	}
	else
	{
		e = GetPlayerVirtualWorld(playerid);
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, Business[e][ix],
			Business[e][iy], Business[e][iz]))
		{
			SendClientMessage(playerid, 0xFFFFFF, "You need to be near the exit!");
		}
		
		SetPlayerPos(playerid, Business[e][ex], Business[e][ey], Business[e][ez]);
		SetPlayerFacingAngle(playerid, Business[e][ea]);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
}

stock process_visit_house_cmd(playerid)
{
    new h, t;
	if(!GetPlayerInterior(playerid))
	{
	    for(h = 0; h < MAX_HOUSES; h++)
		{
		    for(t = 0; t < size_dynamic_data_float(House[h][ex]); t++)
		    {
		    	new Float:x, Float:y, Float:z;
		    	x = get_dynamic_data_float(House[h][ex], t);
				y = get_dynamic_data_float(House[h][ey], t);
				z = get_dynamic_data_float(House[h][ez], t);
				
		        if(IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
				{
        			printf("Close!");
				    break;
				}
		    }
		    if(t < size_dynamic_data_float(House[h][ex]))
		    {
				SetPlayerPos(playerid, House[h][ix], House[h][iy], House[h][iz]);
				SetPlayerFacingAngle(playerid, House[h][ia]);
				SetPlayerInterior(playerid, House[h][iInt]);
				SetPlayerVirtualWorld(playerid, h);
				break;
			}
		}
	}
	else
	{
	    h = GetPlayerVirtualWorld(playerid);
	    if(!IsPlayerInRangeOfPoint(playerid, 15.0,
			House[h][ix],
			House[h][iy],
			House[h][iz]))
		{
			SendClientMessage(playerid, 0xFFFFFF, "You need to be near the exit!");
		}

		SetPlayerPos(playerid,
			get_dynamic_data_float(House[h][ex], 0),
			get_dynamic_data_float(House[h][ey], 0),
			get_dynamic_data_float(House[h][ez], 0));
		SetPlayerFacingAngle(playerid,
			get_dynamic_data_float(House[h][ea], 0));
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
}

stock show_interior_info(playerid)
{

	if(	GetPVarInt(playerid, LAST_PICKUP) >= house_pickup[0] &&
		GetPVarInt(playerid, LAST_PICKUP) <= house_pickup[MAX_HOUSES - 1])
	{
	    //house pickup
	}
	else if(GetPVarInt(playerid, LAST_PICKUP) >= business_pickup[0] &&
			GetPVarInt(playerid, LAST_PICKUP) <= business_pickup[MAX_BUSINESS - 1])
	{
	    //business pickup
	}

	SendClientMessage(playerid, 0xFF0000, "Not finished!");
}

/*CREATE TABLE `interiors` (
	`name`	TEXT,
	`ix`	REAL,
	`iy`	REAL,
	`iz`	REAL,
	`ia`	REAL,
	`iInt`	INTEGER,
	`ex`	REAL,
	`ey`	REAL,
	`ez`	REAL,
	`ea`	REAL
);*/
