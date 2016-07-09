#if defined _funActors_included
	#endinput
#endif
#define _funActors_included
#pragma library funActors

#define     MAX_EAT_PLACE      3

new actors_eat_place[MAX_EAT_PLACE];
new pickup_eat_place[MAX_EAT_PLACE];

/*
stock loadActors()
stock loadEatPlaces()
stock eat_place(playerid)
*/

stock loadActors()
{
    actors_eat_place[0] = CreateActor(155, -2383.0, -2169.1001, 34.0, 178.0);
    actors_eat_place[1] = CreateActor(205, -2188.6001, -2264.8, 31.3, 142.0);
    actors_eat_place[2] = CreateActor(155, -2201.0, -2386.5, 30.6, 252.0);
}

stock loadEatPlaces()
{
    pickup_eat_place[0] = CreatePickup(2880, 1, -2382.6001, -2171.3, 33.3, -1);
    pickup_eat_place[1] = CreatePickup(2880, 1, -2189.8999, -2266.5, 30.6, -1);
    pickup_eat_place[2] = CreatePickup(2880, 1, -2198.8999, -2387.3, 30.6, -1);
}

stock eat_place(playerid)
{
	if(GetPVarInt(playerid, LAST_PICKUP) >= pickup_eat_place[0] &&
		GetPVarInt(playerid, LAST_PICKUP) <= pickup_eat_place[2])
	{
	    //open a menu
	    SendClientMessage(playerid, 0x00FF00, "No menu yet!");
	}
}
