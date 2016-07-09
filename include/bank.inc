#if defined _bank_included
	#endinput
#endif
#define _bank_included
#pragma library bank

new player_money_b[MAX_PLAYERS];

stock giveMoney(playerid, amount)
{
    player_money_b[playerid] += amount;
    GivePlayerMoney(playerid, amount);
}

stock resetMoney(playerid)
{
    player_money_b[playerid] = 0;
    ResetPlayerMoney(playerid);
}

stock loadBankAccount(playerid)
{
	//load from bank
	//
    player_money_b[playerid] = 0;
}

stock bankWithdraw(playerid, amount)
{
    giveMoney(playerid, amount);
    //take of from bank
    //
}

stock bankDeposit(playerid, amount)
{
    giveMoney(playerid, -amount);
    //take of from bank
    //
}

stock bankStatus(playerid)
{
	#unused playerid
	//show status
}

stock addATM(Float:atm_x, Float:x, Float:atm_y, Float:atm_z)
{
	#unused x
	#unused y
	#unused z
	//create
}
