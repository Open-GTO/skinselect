# skinselect
Skin select system

# Defines
```Pawn
#if !defined SKINS_IGNORE
	#define SKINS_IGNORE 0, 74
#endif

#if !defined SKINS_MINID
	#define SKINS_MINID 1
#endif

#if !defined SKINS_MAXID
	#define SKINS_MAXID 311
#endif
```

# Callbacks
```Pawn
forward OnSkinSelectResponse(playerid, SS_Response:type, oldskin, newskin);
```

# SS_Response types
```Pawn
SS_Response_Start
SS_Response_Stop
SS_Response_Change
SS_Response_Select
```

# Functions
```Pawn
SkinSelect_Start(playerid, function[]);
SkinSelect_Stop(playerid);
SkinSelect_GetCurrentSkin(playerid);
SkinSelect_GetOldSkin(playerid);
IsSkinValid(skinid);
```

# Usage
```Pawn
// Start skin selection:
SkinSelect_Start(playerid, SkinSelect:test);

// Stop skin selection:
SkinSelect_Stop(playerid, SkinSelect:test);

// Get response:
SkinSelectResponse:test(playerid, SS_Response:type, oldskin, newskin)
{

}
```
