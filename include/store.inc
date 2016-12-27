#if defined _store_included
	#endinput
#endif
#define _store_included
#pragma library store

#define CLOTH_POS       	"cloth_pos"
#define PREVIOUS_SKIN		"previous_skin"
#define LAST_PCK_CLOTHES	"last_pck_clothes"

#define MAX_CLOTHES_STORE   10

new pickup_clothes_store[MAX_CLOTHES_STORE];
new Float:clothes_store_angle[MAX_CLOTHES_STORE];

new malePedSkins[] = {	101, 136, 14, 142, 143, 144, 15, 156,
						168, 17, 170, 180, 182, 183, 184, 186,
						185, 188, 19, 20 };
						
new femalePedSkins[] = {10, 12, 13, 151, 169, 54, 263, 75, 216,
						91 };


/*
*/

stock addClothesStore(Float:x, Float:y, Float:z, Float:a)
{
	new last_pickup = GetSVarInt(LAST_PCK_CLOTHES);
	
	if(last_pickup >= MAX_CLOTHES_STORE)
	{
	    printf("The server has too much ClothesStore!");
	    return 0;
	}
	
	pickup_clothes_store[last_pickup] = CreatePickup(1275, 1, x, y, z, -1);
	clothes_store_angle[last_pickup] = a;
	last_pickup ++;
	SetSVarInt(LAST_PCK_CLOTHES, last_pickup);
	return 1;
}

stock process_clothes_store_cmd(playerid)
{
	new pickup = GetPVarInt(playerid, LAST_PICKUP);
	
	if(	pickup >= pickup_clothes_store[0] &&
		pickup <= pickup_clothes_store[GetSVarInt(LAST_PCK_CLOTHES) - 1])
	{
	    SetPlayerFacingAngle(playerid,
			clothes_store_angle[pickup - pickup_clothes_store[0]]);
	    SetCameraBehindPlayer(playerid);
	    SetPVarInt(playerid, CLOTH_POS, 1);
	    SetPVarInt(playerid, PREVIOUS_SKIN, GetPlayerSkin(playerid));
	    
	    if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        SetPlayerSkin(playerid, malePedSkins[0]);
	    }
	    else if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        SetPlayerSkin(playerid, femalePedSkins[0]);
	    }
	    
	    TextDrawShowForPlayer(playerid, choose_skin[0]);
		TextDrawShowForPlayer(playerid, choose_skin[1]);

		SetTimerEx("lookAtPlayer", 500, false, "i", playerid);
		
		TogglePlayerControllable(playerid, 0);
	    //open a menu
	}
}

forward lookAtPlayer(playerid);
public lookAtPlayer(playerid)
{
    new
        Float:fPX, Float:fPY, Float:fPZ,
        Float:fVX, Float:fVY, Float:fVZ,
        Float:object_x, Float:object_y, Float:object_z;
	//
    const Float:fScale = 5.0;
 	//

    // Change me to change the scale you want. A larger scale increases the distance from the camera.
    // A negative scale will inverse the vectors and make them face in the opposite direction.

    GetPlayerCameraPos(playerid, fPX, fPY, fPZ);
    GetPlayerCameraFrontVector(playerid, fVX, fVY, fVZ);

    object_x = fPX + floatmul(fVX, fScale);
    object_y = fPY + floatmul(fVY, fScale);
    object_z = fPZ + floatmul(fVZ, fScale);

    GetPlayerPos(playerid, fPX, fPY, fPZ);
    SetPlayerCameraPos(playerid, object_x, object_y, object_z);
    SetPlayerCameraLookAt(playerid, fPX, fPY, fPZ);

	return 1;
}

stock selectingClothes(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_SECONDARY_ATTACK))
	{
	    //close and back to initial skin
		SetPlayerSkin(playerid, GetPVarInt(playerid, PREVIOUS_SKIN));
	    SetCameraBehindPlayer(playerid);
	    DeletePVar(playerid, CLOTH_POS);
	    DeletePVar(playerid, PREVIOUS_SKIN);
	    TogglePlayerControllable(playerid, 1);
	    //
	    TextDrawHideForPlayer(playerid, choose_skin[0]);
		TextDrawHideForPlayer(playerid, choose_skin[1]);
	}
	else if(PRESSED(KEY_SPRINT))
	{
	    //save and close
	    SetCameraBehindPlayer(playerid);
	    DeletePVar(playerid, CLOTH_POS);
	    DeletePVar(playerid, PREVIOUS_SKIN);
	    TogglePlayerControllable(playerid, 1);
	    //
	    TextDrawHideForPlayer(playerid, choose_skin[0]);
		TextDrawHideForPlayer(playerid, choose_skin[1]);
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
	        if(skin_p < 0)
	            skin_p = sizeof(malePedSkins) - 1;
	        else if(skin_p == sizeof(malePedSkins))
	            skin_p = 0;
	            
	        SetPlayerSkin(playerid, malePedSkins[skin_p]);
	    }
	    else if(PlayerInfo[playerid][gender] == GENDER_MALE)
	    {
	        if(skin_p < 0)
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

stock loadStores()
{
    addClothesStore(216.551, -98.528, 1005.257, 89.705);
}
