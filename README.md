# skinselect
Skin select system. Requires [mselect](https://github.com/Open-GTO/mselect) library (optional).

# Defines
Define | Default value | Can be redefined?
---|---|---
SKINS_IGNORE | 74 | yes
SKINS_MINID | 0 | yes
SKINS_MAXID | 311 | yes
SKINS_COUNT | 310 | yes
SKINSELECT_MAX_FUNCTION_NAME | 31 | no

# Callbacks
```Pawn
forward OnSkinSelectResponse(playerid, SS_Response:type, oldskin, newskin);
```

# SS_Response types
- SS_Response_Start
- SS_Response_Stop
- SS_Response_Change
- SS_Response_Select

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
