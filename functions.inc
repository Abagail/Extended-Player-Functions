#if !defined _samp_included
	#include <a_samp>
#endif

enum INC_PLAYER_DATA
{
	inc_playerJoinName[MAX_PLAYER_NAME],
	inc_playerConnectTime,
	inc_playerConnectPort
}

new static gINC_pData[MAX_PLAYERS][INC_PLAYER_DATA];

// START OF CALLBACKS //
public OnPlayerConnect(playerid)
{
	gINC_pData[playerid][inc_playerConnectTime] = gettime();

	GetPlayerName(playerid, gINC_pData[playerid][inc_playerJoinName], MAX_PLAYER_NAME);
	CallLocalFunction("INC_OnPlayerConnect", "i", playerid);
	return 1;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
	gINC_pData[playerid][inc_playerConnectPort] = port;
	CallLocalFunction("INC_OnIncomingConnection", "isi", playerid, ip_address, port);
	
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	gINC_pData[playerid][inc_playerConnectTime] = 0;
	gINC_pData[playerid][inc_playerConnectPort] = 0;
	gINC_pData[playerid][inc_playerJoinName][0] = '\0';
	
	CallLocalFunction("INC_OnPlayerDisconnect", "ii", playerid, reason);

	return 1;
}

// END OF CALLBACKS

// START OF HOOKING //

#if defined _ALS_OnPlayerConnect
  #undef OnPlayerConnect
#else
#define _ALS_OnPlayerConnect
#endif

#if defined _ALS_OnPlayerDisconnect
  #undef OnPlayerDisconnect
#else
#define _ALS_OnPlayerDisconnect
#endif

#if defined _ALS_OnIncomingConnection
  #undef OnIncomingConnection
#else
#define _ALS_OnIncomingConnection
#endif

#define OnPlayerConnect    		INC_OnPlayerConnect
#define OnPlayerDisconnect 		INC_OnPlayerDisconnect
#define OnIncomingConnection    INC_OnIncomingConnection


forward INC_OnPlayerConnect(playerid);
forward INC_OnPlayerDisconnect(playerid, reason);
forward INC_OnIncomingConnection(playerid, ip_address[], port);

// END OF HOOKING //

// START OF FUNCTIONS //

stock GetPlayerJoinTime(playerid) {
	if(IsPlayerConnected(playerid))
	    return gINC_pData[playerid][inc_playerConnectTime];

	return INVALID_PLAYER_ID;
}

stock GetPlayerJoinPort(playerid) {
	if(IsPlayerConnected(playerid))
	    return gINC_pData[playerid][inc_playerConnectPort];

	return INVALID_PLAYER_ID;
}

stock GetPlayerJoinName(playerid) {
	if(IsPlayerConnected(playerid))
	    return gINC_pData[playerid][inc_playerJoinName];

	return INVALID_PLAYER_ID;
}

// END OF FUNCTIONS
