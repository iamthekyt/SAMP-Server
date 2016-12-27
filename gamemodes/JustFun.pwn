#include <a_samp>
#include <a_players>
//
#define LAST_PICKUP     	"last_pickup"
//#define BETWEEN(%0, %1, %2)	(%0 >= %1 && %0 <= %2)
#define EXIT_VEHICLE_ID     "exist_vehicle_id"
#define EXIT_VEHICLE_SEAT   "exit_vehicle_seat"

// PRESSED(keys)
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
//
#include "../include/fun_actors"
#include "../include/dynamicdata"
#include "../include/useful"
#include "../include/bank"
#include "../include/playerInfo"
#include "../include/loadInteriors"
#include "../include/loadVehicles"
#include "../include/trunk"
#include "../include/textdraw"
#include "../include/store"
#include "../include/teams"
#include "../include/keychain"

forward updateDayTime();

main() {
	print("\n----------------------------------");
	print(" Loading Gamemode ... ");
	print("----------------------------------\n");
}

public OnGameModeInit() {

	SetGameModeText("Cops/Robbers");
	AddPlayerClass(malePedSkins[random(sizeof(malePedSkins))],
			-2196.3999, -2254.7, 30.7, 230.0, 0, 0, 0, 0, 0, 0);
	
	
	createGlobalTextDraw();
	loadVehicles();
	initTrunk();
	loadBusiness();
	loadHouses();
	loadActors();
	loadEatPlaces();
	loadTeams();
	loadKeyChains();
	loadStores();
	
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	SetWeather(1);
	updateDayTime();
	SetTimer("updateDayTime", 720000, true);//12min
	return 1;
}

public OnPlayerRequestClass(playerid, classid) {

    TogglePlayerControllable(playerid, 0);
	SetPlayerPos(playerid,  -2155.8, -2408.7, 25.5);
	SetPlayerCameraPos(playerid, -2252.8999, -2324.7, 52.0);
	SetPlayerCameraLookAt(playerid, -2155.8, -2408.7, 30.5);
	return 1;
}

public OnPlayerConnect(playerid)
{
    PreloadAnimations(playerid);
    createPlayerTextDraw(playerid);
    loadPlayerInfo(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	
    destroyPlayerTextDraw(playerid);
	if(vehicleid != INVALID_VEHICLE_ID)
	{
	    if(!GetPlayerVehicleSeat(playerid) && vehicleid > 0)
		{
		    if(getVehicleKeyType(vehicleid) == TEAM_KEY)
		    {
		        addTeamKey(GetPlayerTeam(playerid), VEHICLE_KEY, vehicleid);
		    }
		    else
		    {
		        addPlayerKey(playerid, VEHICLE_KEY, vehicleid);
		    }
		    setVehicleKeyType(vehicleid, NO_KEY);
	    	setVehicleEngineState(vehicleid, false);
	    }
	    SetVehicleToRespawn(vehicleid);
	}
	savePlayerInfo(playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	TogglePlayerControllable(playerid, 1);
	SetPlayerTeam(playerid, PlayerInfo[playerid][team_id]);
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	trunk_clickPlayerTD(playerid, playertextid);
    return 1;
}
public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	trunk_clickTD(playerid, clickedid);
    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (!strcmp("/e", cmdtext, true) || !strcmp("/enter", cmdtext, true))
	{
	    process_interior_cmd(playerid);
		return 1;
	}
	else if (!strcmp("/t", cmdtext, true) || !strcmp("/trunk", cmdtext, true))
	{
		process_trunk_cmd(playerid);
		return 1;
	}
	else if (!strcmp("/i", cmdtext, true) || !strcmp("/info", cmdtext, true))
	{
		show_interior_info(playerid);
		return 1;
	}
	else if (!strcmp("/menu", cmdtext, true))
	{
	    eat_place(playerid);
		return 1;
	}
	else if (!strcmp("/visit", cmdtext, true))
	{
		process_visit_house_cmd(playerid);
		return 1;
	}
	else if (!strcmp("/jointeam", cmdtext, true))
	{
		chooseTeam(playerid);
		return 1;
	}
	else if (!strcmp("/leaveteam", cmdtext, true))
	{
		leaveTeam(playerid);
		return 1;
	}
	else if (!strcmp("/skin", cmdtext, true))
	{
		process_clothes_store_cmd(playerid);
		return 1;
	}
	
	
	
	
	else if(!strcmp(cmdtext, "/becop", true))
    {
        addTeamMember(COPS_TEAM, playerid);
        return 1;
    }
    else if(!strcmp(cmdtext, "/bemedic", true))
    {
        addTeamMember(MEDICS_TEAM, playerid);
        return 1;
    }
    else if(!strcmp(cmdtext, "/benot", true))
    {
        removeTeamMember(GetPlayerTeam(playerid), playerid);
        return 1;
    }
	else if(!strcmp(cmdtext, "/select", true))
    {
        SelectTextDraw(playerid, 0x00FF00FF); // Highlight green when hovering over
        SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: Please select a textdraw!");
        return 1;
    }
    else if(!strcmp(cmdtext, "/pos", true))
    {
        SetPlayerPos(playerid, -2177.8000000,-2368.1001000,32.5000000);
        return 1;
    }
    else if(!strcmp(cmdtext, "/weap", true))
    {
        GivePlayerWeapon(playerid, 29, 500);
        GivePlayerWeapon(playerid, 22, 500);
        return 1;
    }
    else if(!strcmp(cmdtext, "/to0", true))
    {
        SetPlayerVirtualWorld(playerid, 0);
        return 1;
    }
    else if(!strcmp(cmdtext, "/toc", true))
    {
        new Float:x, Float:y, Float:z;
        GetVehiclePos(1, x, y, z);
        SetPlayerPos(playerid, x, y, z);
        return 1;
    }
    else if(!strcmp(cmdtext, "/savepos", true))
    {
        new Float:x, Float:y, Float:z, Float:a;
        new output[128];
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
        
        // Open "file.txt" in "write only" mode
		new File:handle = fopen("file_pos.txt", io_write);

		// Check, if file is open
		if(handle)
		{
			// Success
			format(output, 128, "%.3f, %.3f, %.3f, %.3f\r\n", x, y, z, a);
			// Write "I just wrote here!" into this file
			fwrite(handle, output);

			// Close the file
			fclose(handle);
		}
		else
		{
			// Error
			print("Failed to open file \"file.txt\".");
		}
        
        return 1;
    }
	return 0;
}
public OnPlayerExitVehicle(playerid, vehicleid)
{
    SetPVarInt(playerid, EXIT_VEHICLE_ID, vehicleid);
    SetPVarInt(playerid, EXIT_VEHICLE_SEAT, GetPlayerVehicleSeat(playerid));
    return 1;
}
public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        if(!GetPlayerVehicleSeat(playerid))
	    {
	        new vehicleid = GetPlayerVehicleID(playerid);
	        new teamid = GetPlayerTeam(playerid);
	        
	        if(GetVehicleModel(vehicleid) == 510) //mountain byke
	        {
	            setVehicleEngineState(vehicleid, true);
	        }
	    	else if(teamHasKey(teamid, VEHICLE_KEY, vehicleid))
	    	{
	    	    setVehicleEngineState(vehicleid, true);
	    	    setVehicleKeyType(vehicleid, TEAM_KEY);
	    	    removeTeamKey(teamid, VEHICLE_KEY, vehicleid);
	    	}
	    	else if(playerHasKey(playerid, VEHICLE_KEY, vehicleid))
	    	{
	    	    setVehicleEngineState(vehicleid, true);
	    	    setVehicleKeyType(vehicleid, PLAYER_KEY);
	    	    removePlayerKey(playerid, VEHICLE_KEY, vehicleid);
	    	}
		}
    }
    else if(oldstate == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPVarInt(playerid, EXIT_VEHICLE_ID);
        
        if(!GetPVarInt(playerid, EXIT_VEHICLE_SEAT) && vehicleid > 0)
		{
		    if(GetVehicleModel(vehicleid) == 510) { } //mountain byke
		    else if(getVehicleKeyType(vehicleid) == TEAM_KEY)
		    {
		        addTeamKey(GetPlayerTeam(playerid), VEHICLE_KEY, vehicleid);
		    }
		    else  if(getVehicleKeyType(vehicleid) == PLAYER_KEY)
		    {
		        addPlayerKey(playerid, VEHICLE_KEY, vehicleid);
		    }
		    setVehicleKeyType(vehicleid, NO_KEY);
	    	setVehicleEngineState(vehicleid, false);
	    }
	    DeletePVar(playerid, EXIT_VEHICLE_ID);
	    DeletePVar(playerid, EXIT_VEHICLE_SEAT);
    }
    return 1;
}
public OnPlayerPickUpPickup(playerid, pickupid)
{
    SetPVarInt(playerid, LAST_PICKUP, pickupid);
    return 1;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPVarInt(playerid, CHOOSE_TEAM) > 0)
	{
	    selectingTeam(playerid, newkeys, oldkeys);
	}
	else if(GetPVarInt(playerid, CLOTH_POS) > 0)
	{
	    selectingClothes(playerid, newkeys, oldkeys);
	}
	return 1;
}
public updateDayTime()
{
	static dayTime = 6;
	
	SetWorldTime(dayTime);
	dayTime ++;
	return 1;
}
