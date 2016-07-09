#if defined _trunk_included
	#endinput
#endif
#define _trunk_included
#pragma library trunk

#define MAX_WEAPON_PER_CAR	5
#define TRUNK_EMPTY_SLOT	-1

enum e_trunk {
	weapon_[MAX_WEAPON_PER_CAR],
	ammo_[MAX_WEAPON_PER_CAR],
	playerid_
}
new carTrunk[TOTAL_CARS][e_trunk];

/*
stock setPlayerUsingTrunk(vehicleid, playerid)
stock getPlayerUsingTrunk(vehicleid)
stock setInVehicleTrunk(vehicleid, weaponid, ammo)
stock getInVehicleTrunk(vehicleid, slot, &weaponid, &ammo)
stock removeFromVehicleTrunk(vehicleid, slot)
stock getAllInVehicleTrunk(vehicleid, weaponid[], ammo[])
stock isPlayerInRearOfVehicle(playerid, vehicleid)
stock process_trunk_cmd(playerid)
*/

stock initTrunk()
{
    new i, j;
	for(i = 0; i < TOTAL_CARS; i++)
	{
		for(j = 0; j < MAX_WEAPON_PER_CAR; j++)
		{
			carTrunk[i][weapon_][j] = TRUNK_EMPTY_SLOT;
		}
		carTrunk[i][playerid_] = INVALID_PLAYER_ID;
	}
}


stock setPlayerUsingTrunk(vehicleid, playerid)
{
	carTrunk[vehicleid][playerid_] = playerid;
}

stock getPlayerUsingTrunk(vehicleid)
{
	return carTrunk[vehicleid][playerid_];
}

stock setInVehicleTrunk(vehicleid, weaponid, ammo)
{
	new i;
	for(i = 0; i < MAX_WEAPON_PER_CAR; i++)
	{
		if(carTrunk[vehicleid][weapon_][i] == TRUNK_EMPTY_SLOT)
			break;
	}
	if(i < MAX_WEAPON_PER_CAR)
	{
		carTrunk[vehicleid][weapon_][i] = weaponid;
		carTrunk[vehicleid][ammo_][i] = ammo;
		return true;
	}
	else
	{
		return false;
	}
}

stock getInVehicleTrunk(vehicleid, slot, &weaponid, &ammo)
{
	weaponid = carTrunk[vehicleid][weapon_][slot];
	ammo = carTrunk[vehicleid][ammo_][slot];
}

stock removeFromVehicleTrunk(vehicleid, slot)
{
    carTrunk[vehicleid][weapon_][slot] = TRUNK_EMPTY_SLOT;
    carTrunk[vehicleid][ammo_][slot] = 0;
}

stock getAllInVehicleTrunk(vehicleid, weaponid[], ammo[])
{
	for(new i = 0; i < MAX_WEAPON_PER_CAR; i++)
	{
		weaponid[i] = carTrunk[vehicleid][weapon_][i];
		ammo[i] = carTrunk[vehicleid][ammo_][i];
	}
}

stock isPlayerInRearOfVehicle(playerid, vehicleid)
{
	new Float:x, Float:y, Float:z, Float:a,
		Float:distance = 3.0;

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	x -= (distance * floatsin(-a, degrees));
	y -= (distance * floatcos(-a, degrees));
	if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

stock process_trunk_cmd(playerid)
{
	new vehicleid = getClosestVehicle(playerid, 5.0);
	if(isPlayerInRearOfVehicle(playerid, vehicleid))
	{
		if(getVehicleTrunkState(vehicleid) != 1 &&
			getPlayerUsingTrunk(vehicleid) == INVALID_PLAYER_ID)
		{
			setVehicleTrunkState(vehicleid, true);
			setPlayerUsingTrunk(vehicleid, playerid);
            SetPVarInt(playerid, "trunk_car", vehicleid);
            
			CallLocalFunction("updateTextDrawTrunk", "d", playerid);
			SelectTextDraw(playerid, 0xFF0000FF);
		}
		else if(getPlayerUsingTrunk(vehicleid) == playerid)
		{
			setVehicleTrunkState(vehicleid, false);
			setPlayerUsingTrunk(vehicleid, INVALID_PLAYER_ID);

			CallLocalFunction("hideTextDrawTrunk", "d", playerid);

			DeletePVar(playerid, "trunk_car");
			DeletePVar(playerid, "td_trunk_player");
			DeletePVar(playerid, "td_trunk_car");
			DeletePVar(playerid, "td_selected_player");
			DeletePVar(playerid, "td_selected_car");
			CancelSelectTextDraw(playerid);
		}
	}
}
