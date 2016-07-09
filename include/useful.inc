#if defined _useful_included
	#endinput
#endif
#define _useful_included
#pragma library useful


/*
new weapon_model_id[][2] = {
	321, 10, // - Regular Dildo
	322, 11, // - White Dildo
	323, 12, // - Vibrator
	324, 13, // - Small Vibrator
	325, 14, // - Flowers
	326, 15, // - Cane
	//327,// - Girlfriend gift box small
	//328,// - Girlfriend gift box large
	//330,// - CJ's Phone
	331, 1, // - Brass Knuckles
	333, 2, // - Golf Club
	334, 3, // - Night Stick
	335, 4, // - Combat Knife
	336, 5, // - Baseball Bat
	337, 6, // - Shovel
	338, 7, // - Pool Cue
	339, 8, // - Katana
	341, 9, // - Chainsaw
	342, 16, // - Frag Grenade
	343, 17, // - Tear Gas Grenade
	344, 18, // - Molotov Cocktail
	//345// - Hydra / Hunter Missile (Use sparingly, crash prone in large quantities.)
	346, 22, // - Colt 45 Pistol
	347, 23, // - Silenced Pistol
	348, 24, // - Desert Eagle
	349, 25, // - Regular Shotgun
	350, 26, // - Sawn-Off Shotgun
	351, 27, // - Combat Shotgun
	352, 28, // - Micro Uzi
	353, 29, // - MP5
	//354,// - Hydra Flare
	355, 30, // - AK47 Assault Rifle
	356, 31, // - M4 Assault Rifle
	357, 33, // - Country Rifle?
	358, 34, // - Sniper Rifle
	359, 35, // - Rocket Launcher
	360, 36, // - Heat Seeking Rocket Launcher
	361, 37, // - Flamethrower
	362, 38, // - Minigun
	363, 39, // - Satchel Charges
	364, 40, // - Detonator (Useless without satchels).
	365, 41, // - Spray Paint Can
	366, 42, // - Fire Extinguisher
	367, 43, // - Camera
	368, 44, // - Night Vision Goggles
	369, 45, // - Infra-Red Goggles
	//370,// - Jet pack
	371, 46, // - Parachute
	372, 32, // - Tec-9
	373, 0 // - Armour model (No Effect)
};*/

new s_AnimationLibraries[][] = {
	!"AIRPORT",    !"ATTRACTORS",   !"BAR", 		!"BASEBALL",
	!"BD_FIRE",    !"BEACH", 	    !"BENCHPRESS",  !"BF_INJECTION",
	!"BIKED", 	   !"BIKEH", 	    !"BIKELEAP", 	!"BIKES",
	!"BIKEV", 	   !"BIKE_DBZ",     !"BMX", 		!"BOMBER",
	!"BOX", 	   !"BSKTBALL",     !"BUDDY", 		!"BUS",
	!"CAMERA", 	   !"CAR",          !"CARRY", 		!"CAR_CHAT",
	!"CASINO",	   !"CHAINSAW",     !"CHOPPA", 		!"CLOTHES",
	!"COACH", 	   !"COLT45",       !"COP_AMBIENT", !"COP_DVBYZ",
	!"CRACK", 	   !"CRIB",         !"DAM_JUMP", 	 !"DANCING",
	!"DEALER", 	   !"DILDO",        !"DODGE", 	 	 !"DOZER",
	!"DRIVEBYS",   !"FAT",          !"FIGHT_B", 	 !"FIGHT_C",
	!"FIGHT_D",    !"FIGHT_E",      !"FINALE", 		 !"FINALE2",
	!"FLAME",      !"FLOWERS",      !"FOOD", 	 	 !"FREEWEIGHTS",
	!"GANGS",      !"GHANDS",       !"GHETTO_DB", 	 !"GOGGLES",
	!"GRAFFITI",   !"GRAVEYARD",    !"GRENADE", 	 !"GYMNASIUM",
	!"HAIRCUTS",   !"HEIST9",       !"INT_HOUSE", 	 !"INT_OFFICE",
	!"INT_SHOP",   !"JST_BUISNESS", !"KART", 		 !"KISSING",
	!"KNIFE",      !"LAPDAN1", 		!"LAPDAN2", 	 !"LAPDAN3",
	!"LOWRIDER",   !"MD_CHASE", 	!"MD_END", 	 	 !"MEDIC",
	!"MISC",       !"MTB", 			!"MUSCULAR", 	 !"NEVADA",
	!"ON_LOOKERS", !"OTB", 			!"PARACHUTE", 	 !"PARK",
	!"PAULNMAC",   !"PED", 			!"PLAYER_DVBYS", !"PLAYIDLES",
	!"POLICE",     !"POOL", 		!"POOR", 		 !"PYTHON",
	!"QUAD",       !"QUAD_DBZ", 	!"RAPPING", 	 !"RIFLE",
	!"RIOT",       !"ROB_BANK", 	!"ROCKET",	 	 !"RUSTLER",
	!"RYDER",      !"SCRATCHING", 	!"SHAMAL", 		 !"SHOP",
	!"SHOTGUN",    !"SILENCED", 	!"SKATE", 		 !"SMOKING",
	!"SNIPER",     !"SPRAYCAN", 	!"STRIP", 		 !"SUNBATHE",
	!"SWAT",       !"SWEET", 		!"SWIM", 		 !"SWORD",
	!"TANK",       !"TATTOOS",	 	!"TEC", 		 !"TRAIN",
	!"TRUCK",      !"UZI", 			!"VAN", 		 !"VENDING",
	!"VORTEX",     !"WAYFARER", 	!"WEAPONS", 	 !"WUZI",
	!"WOP",        !"GFUNK", 		!"RUNNINGMAN"
};

stock PreloadAnimations(playerid)
{
	for(new i = 0; i < sizeof(s_AnimationLibraries); i ++)
	{
	    ApplyAnimation(playerid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
	}
}

// Author unknown. It was probably someone smart like [[User:DracoBlue|DracoBlue]] or [[User:Y_Less|Y_Less]].
stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

stock removePlayerWeapon(playerid, weaponid)
{
	new weapons[13][2];
	new i;

	for (i = 0; i <= 12; i++)
	{
	    GetPlayerWeaponData(playerid, i, weapons[i][0], weapons[i][1]);
	 	if(weaponid == weapons[i][0])
	 	{
	 	    weapons[i][0] = 0;
	 	    weapons[i][1] = 0;
	 	}
	}

	ResetPlayerWeapons(playerid);

	for (i = 0; i <= 12; i++)
	{
	    GivePlayerWeapon(playerid, weapons[i][0], weapons[i][1]);
	}
}
