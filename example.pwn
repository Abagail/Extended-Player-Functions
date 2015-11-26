#include <a_samp>
#include <function>

public OnPlayerSpawn(playerid)
{
	new string[128];
	format(string, sizeof string, "Join time: %d(port: %d)", GetPlayerJoinTime(playerid), GetPlayerJoinPort(playerid));
	SendClientMessage(playerid, -1, string);
	
	format(string, sizeof string, "Join name: %s", GetPlayerJoinName(playerid));
	SendClientMessage(playerid, -1, string);
	
	return 1;
}
