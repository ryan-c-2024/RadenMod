#pragma once

#define REPLAY_ENABLED

typedef struct player_info_s
{
	//DECLARE_BYTESWAP_DATADESC();
	char __pad1[0x10];
	// scoreboard information
	char			name[32];
	// local server user ID, unique while server is running
	char __pad2[0x64]; //int				userID;
	// global unique player identifer
	char			guid[32 + 1];

	char __pad3[0x17B];	
	/*
		// friends identification number
	unsigned int			friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;

	
	#if defined( REPLAY_ENABLED )
	// true if player is the Replay proxy
	bool			isreplay;
#endif
	// custom files CRC for this player
	unsigned int			customFiles[32];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
	
	
	*/


} player_info_t;