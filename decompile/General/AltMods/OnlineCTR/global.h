
#define VERSION 1009
//#define ONLINE_BETA_MODE

#ifndef WINDOWS_INCLUDE
	#include <common.h>
#endif

#ifdef __GNUC__ // GCC and Clang

	#ifdef WINDOWS_INCLUDE
		#include <unistd.h> // for the 'usleep()' function
	#endif

	#define STATIC_ASSERT2(test_for_true, message) _Static_assert((test_for_true), message)

#else // MSVC (Visual Studio)

	#define STATIC_ASSERT2 static_assert

#endif

#define true				1
#define false				0

#define DONT_SHOW_NAME		0
#define SHOW_NAME			1

#define DEFAULT_IP			"127.0.0.1" // the default IP address we want to use for private lobbies
#define IP_ADDRESS_SIZE		16 // assuming IPv4 (which is "xxx.xxx.xxx.xxx" + '\0')
#define PORT_SIZE			6 // the port number as a string (0-65535 + '\0')

enum ClientState
{
	LAUNCH_ENTER_PID,
	LAUNCH_ENTER_IP,
	LAUNCH_CONNECT_FAILED,
	LAUNCH_FIRST_INIT,
	LOBBY_ASSIGN_ROLE,
	LOBBY_HOST_TRACK_PICK,
	LOBBY_GUEST_TRACK_WAIT,
	LOBBY_CHARACTER_PICK,
	LOBBY_WAIT_FOR_LOADING,
	LOBBY_START_LOADING,
	GAME_WAIT_FOR_RACE,
	GAME_START_RACE,
	GAME_END_RACE,
	NUM_STATES
};

// This can be 0x400 bytes max:
// 0x8000C000 at 0x8000C400
struct OnlineCTR
{
	// 0x0
	int CurrState;

	// 0x4
	char PageNumber; // allow negative
	unsigned char CountPressX;
	unsigned char NumDrivers;
	unsigned char DriverID;

	// 0x8
	unsigned char boolLockedInLap;
	unsigned char boolLockedInLevel;
	unsigned char lapID;
	unsigned char levelID;
	
	// 0xC
	unsigned char IsBootedPS1;
	unsigned char boolLockedInCharacter;
	unsigned char numRooms;
	unsigned char numDriversEnded;

	// 0x10
	unsigned char serverCountry;
	unsigned char serverRoom;
	unsigned char serverLockIn1;
	unsigned char serverLockIn2;

	char clientCount[16];

	// determines if client and
	// emulator are still connected
	char time[8];

	char boolLockedInCharacters[8];

	char nameBuffer[0xC*8];

	struct
	{
		int slot;
		int time;
	} RaceEnd[8];
};

#ifdef WINDOWS_INCLUDE

#include <time.h>

#ifndef __GNUC__
	#include <windows.h>
#endif

enum ServerGiveMessageType
{
	// connection
	SG_ROOMS,

	// assign to room
	SG_NEWCLIENT,

	// lobby
	SG_NAME,
	SG_TRACK,
	SG_CHARACTER,
	SG_STARTLOADING,

	SG_STARTRACE,
	SG_RACEDATA,
	SG_ENDRACE,

	SG_SERVERCLOSED,

	SG_COUNT
};

// variety of opcodes (start load / start race)
struct SG_Header
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
};

struct SG_MessageRooms
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
	unsigned char numRooms;

	unsigned short version;
	
	unsigned char numClients01 : 4;
	unsigned char numClients02 : 4;
	unsigned char numClients03 : 4;
	unsigned char numClients04 : 4;
	unsigned char numClients05 : 4;
	unsigned char numClients06 : 4;
	unsigned char numClients07 : 4;
	unsigned char numClients08 : 4;
	
	unsigned char numClients09 : 4;
	unsigned char numClients10 : 4;
	unsigned char numClients11 : 4;
	unsigned char numClients12 : 4;
	unsigned char numClients13 : 4;
	unsigned char numClients14 : 4;
	unsigned char numClients15 : 4;
	unsigned char numClients16 : 4;

	// 12 bytes total
};

// sent to each user when someone connects
struct SG_MessageClientStatus
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// 1-15 for client, and total
	unsigned char clientID : 4;
	unsigned char numClientsTotal : 4;

	// server version
	unsigned short version;

	// special event
	unsigned short special;
};

// get name from any client
struct SG_MessageName
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// index 0 - 7
	unsigned char clientID : 4;
	unsigned char numClientsTotal : 4;

	char name[0xC];
};

// get track, assigned by host
struct SG_MessageTrack
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char trackID : 5;
	unsigned char lapID : 2;
	unsigned char boolAllowWeapons : 1;
};

// assign character,
struct SG_MessageCharacter
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// index 0 - 7
	// boolLockedIn 0/1
	// character 0 - 15
	unsigned char clientID : 3;
	unsigned char boolLockedIn : 1;
	unsigned char characterID : 4;
};

struct SG_EverythingKart
{
	// byte[0]

	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// byte[1-2]

	unsigned char clientID : 3;

	// bit-compressed driver->0x39A
	unsigned char kartRot1 : 5;
	unsigned char kartRot2;

	// byte[3]

	unsigned char buttonHold;

	// byte[4-12]

	unsigned char posX[3];
	unsigned char posY[3];
	unsigned char posZ[3];

	// 13 bytes
};

struct SG_MessageEndRace
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char clientID;
	unsigned char time[3];
};

STATIC_ASSERT2(sizeof(struct SG_Header) == 1, "Size of SG_Header must be 1 byte");
STATIC_ASSERT2(sizeof(struct SG_MessageRooms) == 12, "Size of SG_MessageRooms must be 12 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageClientStatus) == 6, "Size of SG_MessageClientStatus must be 4 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageName) == 14, "Size of SG_MessageName must be 14 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageCharacter) == 2, "Size of SG_MessageCharacter must be 2 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageTrack) == 2, "Size of SG_MessageTrack must be 2 bytes");
STATIC_ASSERT2(sizeof(struct SG_EverythingKart) == 13, "Size of SG_EverythingKart must be 13 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageEndRace) == 5, "Size of SG_MessageEndRace must be 5 bytes");

enum ClientGiveMessageType
{
	CG_JOINROOM,

	// lobby
	CG_NAME,
	CG_TRACK,
	CG_CHARACTER,

	CG_STARTRACE,
	CG_RACEDATA,
	CG_ENDRACE,

	CG_COUNT
};

// sent to each user when someone connects
struct CG_Header
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
};

struct CG_MessageRoom
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char room;
};

struct CG_MessageName
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	char name[0xC];
};

// get track, assigned by host
struct CG_MessageTrack
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char trackID : 5;
	unsigned char lapID : 2;
	unsigned char boolAllowWeapons : 1;
};

// character message
struct CG_MessageCharacter
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// character 0 - 15
	// lockedIn 0/1
	unsigned char characterID : 4;
	unsigned char boolLockedIn : 1;
	unsigned char padding : 3;
};

struct CG_EverythingKart
{
	// byte[0]

	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// bit-compressed driver->0x39A
	unsigned char kartRot1;
	unsigned char kartRot2;

	// byte[3]

	unsigned char buttonHold;

	// byte[4-12]

	unsigned char posX[3];
	unsigned char posY[3];
	unsigned char posZ[3];

	// 13 bytes
};

struct CG_MessageEndRace
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char time[3];
};

STATIC_ASSERT2(sizeof(struct CG_Header) == 1, "Size of CG_Header must be 1 byte");
STATIC_ASSERT2(sizeof(struct CG_MessageName) == 13, "Size of CG_MessageName must be 13 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageCharacter) == 2, "Size of CG_MessageCharacter must be 2 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageTrack) == 2, "Size of CG_MessageTrack must be 2 bytes");
STATIC_ASSERT2(sizeof(struct CG_EverythingKart) == 13, "Size of CG_EverythingKart must be 13 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageEndRace) == 4, "Size of CG_MessageEndRace must be 4 bytes");

// OnlineCTR functions
void StatePC_Launch_EnterPID();
void StatePC_Launch_EnterIP();
void StatePC_Launch_ConnectFailed();
void StatePC_Launch_FirstInit();
void StatePC_Lobby_HostTrackPick();
void StatePC_Lobby_GuestTrackWait();
void StatePC_Lobby_CharacterPick();
void StatePC_Lobby_WaitForLoading();
void StatePC_Lobby_StartLoading();
void StatePC_Game_WaitForRace();
void StatePC_Game_StartRace();
void StatePC_Game_EndRace();

// console functions
void PrintBanner(char show_name);
void StartAnimation();
void StopAnimation();

#endif

#ifndef WINDOWS_INCLUDE
	// set zero to fix DuckStation,
	// is it needed on console?
	#define USE_K1 0

	#if USE_K1 == 1
		register struct OnlineCTR* octr asm("k1");
	#else
		static struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif

	// my functions
	void StatePS1_Launch_EnterPID();
	void StatePS1_Launch_EnterIP();
	void StatePS1_Launch_ConnectFailed();
	void StatePS1_Launch_FirstInit();
	void StatePS1_Lobby_AssignRole();
	void StatePS1_Lobby_HostTrackPick();
	void StatePS1_Lobby_GuestTrackWait();
	void StatePS1_Lobby_CharacterPick();
	void StatePS1_Lobby_WaitForLoading();
	void StatePS1_Lobby_StartLoading();
	void StatePS1_Game_WaitForRace();
	void StatePS1_Game_StartRace();
	void StatePS1_Game_EndRace();
#endif