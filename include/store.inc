#if defined _store_included
	#endinput
#endif
#define _store_included
#pragma library store

#define CLOTH_POS       "cloth_pos"

#define MAX_CLOTHES_STORE   10

new pickup_clothes_store[MAX_CLOTHES_STORE];

new malePedSkins[] = {	101, 136, 14, 142, 143, 144, 15, 156,
						168, 17, 170, 180, 182, 183, 184, 186,
						185, 188, 19, 20 };
						
new femalePedSkins[] = {10, 12, 13, 151, 169, 54, 263, 75, 216,
						91 };


/*
*/


stock addClothesStore(Float:x, Float:y, Float:z)
{
	static last_pickup = 0;
	if(last_pickup >= MAX_CLOTHES_STORE)
	{
	    printf("You are using too much ClothesStore!");
	    return 0;
	}
	
	pickup_clothes_store[last_pickup] = CreatePickup(1275, 1, x, y, z, -1);
	last_pickup ++;
	return 1;
}

stock process_clothes_store_cmd(playerid)
{
	if(	GetPVarInt(playerid, LAST_PICKUP) >= pickup_clothes_store[0] &&
		GetPVarInt(playerid, LAST_PICKUP) <= pickup_clothes_store[MAX_CLOTHES_STORE - 1])
	{
	    SetPVarInt(playerid, CLOTH_POS, 1);
	    if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        SetPlayerSkin(playerid, malePedSkins[0]);
	    }
	    else if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        SetPlayerSkin(playerid, femalePedSkins[0]);
	    }
	
	    TextDrawHideForPlayer(playerid, choose_skin[0]);
		TextDrawHideForPlayer(playerid, choose_skin[1]);
	    //open a menu
	    return 1;
	}
	return 0;
}

stock selectingClothes(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_SECONDARY_ATTACK))
	{
	    //close and back to initial skin

	    SetCameraBehindPlayer(playerid);
	    DeletePVar(playerid, CLOTH_POS);
	}
	else if(PRESSED(KEY_SPRINT))
	{
	    //save and close
	    
	    SetCameraBehindPlayer(playerid);
	    DeletePVar(playerid, CLOTH_POS);
	}
	else
	{
	    new skin_p = GetPVarInt(playerid, CLOTH_POS) - 1;
	    if(PRESSED(KEY_FIRE))
	        skin_p --;
	    else if(PRESSED(KEY_HANDBRAKE))
	        skin_p ++;
	    
	    if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        if(!skin_p)
	            skin_p = sizeof(malePedSkins) - 1;
	        else if(skin_p == sizeof(malePedSkins))
	            skin_p = 0;
	            
	        SetPlayerSkin(playerid, malePedSkins[skin_p]);
	    }
	    else if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        if(!skin_p)
	            skin_p = sizeof(femalePedSkins) - 1;
	        else if(skin_p == sizeof(femalePedSkins))
	            skin_p = 0;
	            
	        SetPlayerSkin(playerid, femalePedSkins[skin_p]);
	    }
	    
	    SetPVarInt(playerid, CLOTH_POS, skin_p + 1);
    }
    return 1;
}

stock addWeaponStore()
{
}

stock addCarStore()
{
}

stock addGasStation()
{
}
