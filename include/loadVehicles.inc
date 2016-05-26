#if defined _loadVehicles_included
	#endinput
#endif
#define _loadVehicles_included
#pragma library loadVehicles

#define MAX_CARS_COPS   	10
#define MAX_CARS_MEDICS 	3
#define MAX_CARS_GANGS   	7
#define MAX_CARS_GIFT   	4
#define MAX_SPECIAL_VEH     2

#define TOTAL_CARS			(MAX_CARS_COPS + MAX_CARS_MEDICS \
				+ MAX_CARS_GANGS + MAX_SPECIAL_VEH + MAX_CARS_GIFT)

#define NO_KEY              0
#define TEAM_KEY            1
#define PLAYER_KEY          2

enum e_veh {
	key_owner
};

new Vehicle[TOTAL_CARS][e_veh];

/*
stock loadVehicles()
stock getClosestVehicle(playerid, Float:range)
stock setVehicleTrunkState(vehicleid, setstate)
stock getVehicleTrunkState(vehicleid)
stock getVehicleEngineState(vehicleid)
stock setVehicleEngineState(vehicleid, setstate)
stock setVehicleKeyType(vehicleid, type)
stock getVehicleKeyType(vehicleid)
*/

stock loadVehicles()
{
	new DB:db_handle, x = 0;

	if((db_handle = db_open("JustFunDB.db")) == DB:0)
	{
		print("Failed to open a connection to \"JustFunDB.db\".");
		SendRconCommand("exit");
	}
	else
	{
		new DBResult:db_result;
		new Float:p[4], c1, c2, m;
		
		db_result = db_query(db_handle, "SELECT * FROM `vehicles`");

		do
		{
		    x++;
		    m = db_get_field_int(db_result, 1);
		    p[0] = db_get_field_float(db_result, 2);
		    p[1] = db_get_field_float(db_result, 3);
		    p[2] = db_get_field_float(db_result, 4);
		    p[3] = db_get_field_float(db_result, 5);
		    c1 = db_get_field_int(db_result, 6);
			c2 = db_get_field_int(db_result, 7);
		    
		    AddStaticVehicle(m, p[0], p[1], p[2], p[3], c1, c2);
            Vehicle[x][key_owner] = NO_KEY;
		}
		while(db_next_row(db_result));

		db_free_result(db_result);
	}
	db_close(db_handle);
	
	printf("%d vehicles loaded!", x);
	/*
	convertFFS converted your input in 0.01 seconds - Chuck Norris could have done it in 0.0002 seconds!
	*/
}

stock getClosestVehicle(playerid, Float:range)
{
	new vehicle = INVALID_VEHICLE_ID, Float:tmp_dist, Float:dist = 0xFFFFFF;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	for(new v = 1; v < TOTAL_CARS; v++)
	{
	    tmp_dist = GetVehicleDistanceFromPoint(v, x, y, z);
	    if(tmp_dist > range || tmp_dist > dist)
	        continue;
	        
	    dist = tmp_dist;
	    vehicle = v;
	}
	return vehicle;
}

stock setVehicleTrunkState(vehicleid, setstate)
{
     new engine,lights,alarm,doors,bonnet,boot,objective;
     GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	 if(setstate) SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,VEHICLE_PARAMS_ON,objective);
	 else SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,VEHICLE_PARAMS_OFF,objective);
}

stock getVehicleTrunkState(vehicleid)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);

	return boot;
}

stock getVehicleEngineState(vehicleid)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);

	return engine;
}

stock setVehicleEngineState(vehicleid, setstate)
{
     new engine,lights,alarm,doors,bonnet,boot,objective;
     GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	 if(setstate) SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_ON,lights,alarm,doors,bonnet,boot,objective);
	 else SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_OFF,lights,alarm,doors,bonnet,boot,objective);
}

stock setVehicleKeyType(vehicleid, type)
{
    Vehicle[vehicleid][key_owner] = type;
}

stock getVehicleKeyType(vehicleid)
{
	return Vehicle[vehicleid][key_owner];
}
