// Does absolutely nothing, doesn't even include the functions to perform license checks. 
// The app would immediately crash if it actually tried to check for game ownership
// Implements juuuuust enough for the game to ask for leaderboards and never get an answer

//  Build with:
//  gcc -shared -fPIC -o libsteam_api.so steam_stub.c

#include <stdbool.h>
#include <stdint.h>

typedef char (*VirtualFunction)(void* this_ptr);
struct clazz {VirtualFunction* vtable;};

char ret0() {return 0;} //For when we just want to return 0 in virtual functions
bool SteamAPI_Init() { return true; } //Steam is "running"
bool SteamAPI_RestartAppIfNecessary(uint32_t app_id) { return false; } // Never restart the app
void SteamAPI_RunCallbacks() {} //We don't do any callbacks
void SteamAPI_RegisterCallResult() {} 
void SteamAPI_UnregisterCallResult() {}
// SteamRemoteStorage
VirtualFunction storage_vtable[] = {[0x90/sizeof(VirtualFunction)] = ret0}; // Some sort of highscore getter
struct clazz storage_class = { storage_vtable };
void* SteamRemoteStorage(void) {return &storage_class;}
//SteamUser
VirtualFunction user_vtable[] = {};
struct clazz user_class = { user_vtable };
void* SteamUser(void) {return &user_class;}
//SteamUserStats
VirtualFunction userstats_vtable[]={[0xb8/sizeof(VirtualFunction)] = ret0, // Associated with finding leaderboards
                                    [0x38/sizeof(VirtualFunction)] = ret0, // Obviously the function to set achievements, takes a string parameter like "ACHIEVEMENT_HEXAGON", returns nothing
                                    [0x50/sizeof(VirtualFunction)] = ret0};// No idea what this does, but gets called after setting achievements
struct clazz userstats_class = { userstats_vtable };
void* SteamUserStats(void) {return &userstats_class;}
