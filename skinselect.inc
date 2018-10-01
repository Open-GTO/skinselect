/*

	About: skin select system
	Author:	ziggi

	Instalation:
		Include this file after a_samp.inc

	Type SS_Response:
		SS_Response_Start
		SS_Response_Stop
		SS_Response_Change
		SS_Response_Select

	Start skin selection:
		SkinSelect_Start(playerid, SkinSelect:test);

	Stop skin selection:
		SkinSelect_Stop(playerid, SkinSelect:test);

	Get response:
		SkinSelectResponse:test(playerid, SS_Response:type, oldskin, newskin)
		{

		}

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before skinselect"
#endif

#if defined _skin_select_included
	#endinput
#endif

#define _skin_select_included

/*
	Defines
*/

#define SKINSELECT_MAX_FUNCTION_NAME 31

#if !defined SKINS_IGNORE
	#define SKINS_IGNORE 74
#endif

#if !defined SKINS_MINID
	#define SKINS_MINID 0
#endif

#if !defined SKINS_MAXID
	#define SKINS_MAXID 311
#endif

#if !defined SKINS_COUNT
	#define SKINS_COUNT 310
#endif

/*
	Define functions
*/

#define SkinSelectResponse:%0(%1) \
	forward ssr_%0(%1); \
	public ssr_%0(%1)

#define SkinSelect: #

/*

	Forwards

*/

forward OnSkinSelectResponse(playerid, SS_Response:type, oldskin, newskin);

/*

	Enums

*/

enum SS_Response {
	SS_Response_Start,
	SS_Response_Stop,
	SS_Response_Change,
	SS_Response_Select,
}

/*
	Vars
*/

static
	bool:IsSelectOpen[MAX_PLAYERS],
	bool:IsListOpen[MAX_PLAYERS],
	bool:TD_SkipCancel[MAX_PLAYERS],
	FunctionName[MAX_PLAYERS][SKINSELECT_MAX_FUNCTION_NAME - 4],
	CurrentIndex[MAX_PLAYERS],
	OldSkin[MAX_PLAYERS],
	SkinsArray[SKINS_COUNT],
	SkinsCount,

	Text:TD_ArrowLeft,
	Text:TD_ArrowRight,
	Text:TD_Select,
#if defined _mselect_included
	Text:TD_List,
#endif
	Text:TD_Exit;

/*
	OnGameModeInit
*/

public OnGameModeInit()
{
	// skins array
	for (new skinid = SKINS_MINID; skinid <= SKINS_MAXID; skinid++) {
		switch (skinid) {
			case SKINS_IGNORE: {

			}
			default: {
				if (SkinsCount >= sizeof(SkinsArray)) {
					printf("Error (SkinSelect): SkinsArray lower than needed.");
					break;
				}
				SkinsArray[SkinsCount] = skinid;
				SkinsCount++;
			}
		}
	}

	// td
	TD_ArrowLeft = TextDrawCreate(288.000000, 372.000000, "<<");
	TextDrawAlignment(TD_ArrowLeft, 2);
	TextDrawBackgroundColor(TD_ArrowLeft, 255);
	TextDrawFont(TD_ArrowLeft, 1);
	TextDrawLetterSize(TD_ArrowLeft, 0.500000, 1.299999);
	TextDrawColor(TD_ArrowLeft, 0xDDDDDDAA);
	TextDrawSetOutline(TD_ArrowLeft, 0);
	TextDrawSetProportional(TD_ArrowLeft, 0);
	TextDrawSetShadow(TD_ArrowLeft, 1);
	TextDrawUseBox(TD_ArrowLeft, 1);
	TextDrawBoxColor(TD_ArrowLeft, 0x00000099);
	TextDrawTextSize(TD_ArrowLeft, 12.000000, 50.000000);
	TextDrawSetSelectable(TD_ArrowLeft, 1);

	TD_ArrowRight = TextDrawCreate(343.000000, 372.000000, ">>");
	TextDrawAlignment(TD_ArrowRight, 2);
	TextDrawBackgroundColor(TD_ArrowRight, 255);
	TextDrawFont(TD_ArrowRight, 1);
	TextDrawLetterSize(TD_ArrowRight, 0.500000, 1.299999);
	TextDrawColor(TD_ArrowRight, 0xDDDDDDAA);
	TextDrawSetOutline(TD_ArrowRight, 0);
	TextDrawSetProportional(TD_ArrowRight, 0);
	TextDrawSetShadow(TD_ArrowRight, 1);
	TextDrawUseBox(TD_ArrowRight, 1);
	TextDrawBoxColor(TD_ArrowRight, 0x00000099);
	TextDrawTextSize(TD_ArrowRight, 12.000000, 50.000000);
	TextDrawSetSelectable(TD_ArrowRight, 1);

	TD_Select = TextDrawCreate(315.500000, 390.000000, "Select");
	TextDrawAlignment(TD_Select, 2);
	TextDrawBackgroundColor(TD_Select, 255);
	TextDrawFont(TD_Select, 1);
	TextDrawLetterSize(TD_Select, 0.500000, 1.500000);
	TextDrawColor(TD_Select, 0xDD0000AA);
	TextDrawSetOutline(TD_Select, 0);
	TextDrawSetProportional(TD_Select, 1);
	TextDrawSetShadow(TD_Select, 1);
	TextDrawUseBox(TD_Select, 1);
	TextDrawBoxColor(TD_Select, 0x00000099);
	TextDrawTextSize(TD_Select, 14.000000, 105.000000);
	TextDrawSetSelectable(TD_Select, 1);

#if defined _mselect_included
	TD_List = TextDrawCreate(288.000000, 409.000000, "List");
	TextDrawAlignment(TD_List, 2);
	TextDrawBackgroundColor(TD_List, 255);
	TextDrawFont(TD_List, 1);
	TextDrawLetterSize(TD_List, 0.420000, 0.899999);
	TextDrawColor(TD_List, 0xDDDDDDAA);
	TextDrawSetOutline(TD_List, 0);
	TextDrawSetProportional(TD_List, 1);
	TextDrawSetShadow(TD_List, 1);
	TextDrawUseBox(TD_List, 1);
	TextDrawBoxColor(TD_List, 0x00000099);
	TextDrawTextSize(TD_List, 15.000000, 50.000000);
	TextDrawSetSelectable(TD_List, 1);
#endif

	TD_Exit = TextDrawCreate(343.000000, 409.000000, "Exit");
	TextDrawAlignment(TD_Exit, 2);
	TextDrawBackgroundColor(TD_Exit, 255);
	TextDrawFont(TD_Exit, 1);
	TextDrawLetterSize(TD_Exit, 0.420000, 0.899999);
	TextDrawColor(TD_Exit, 0xDDDDDDAA);
	TextDrawSetOutline(TD_Exit, 0);
	TextDrawSetProportional(TD_Exit, 1);
	TextDrawSetShadow(TD_Exit, 1);
	TextDrawUseBox(TD_Exit, 1);
	TextDrawBoxColor(TD_Exit, 0x00000099);
	TextDrawTextSize(TD_Exit, 10.000000, 50.000000);
	TextDrawSetSelectable(TD_Exit, 1);

	#if defined SS_OnGameModeInit
		return SS_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit SS_OnGameModeInit
#if defined SS_OnGameModeInit
	forward SS_OnGameModeInit();
#endif

/*
	OnPlayerClickTextDraw
*/

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == Text:INVALID_TEXT_DRAW && TD_SkipCancel[playerid]) {
		TD_SkipCancel[playerid] = false;
		return 1;
	}

	if (IsSelectOpen[playerid]) {
		if (IsListOpen[playerid]) {
			return 0;
		}

		if (clickedid == TD_ArrowLeft) {
			SS_ChangeSkin(playerid, CurrentIndex[playerid] - 1, CurrentIndex[playerid]);
			return 1;
		} else if (clickedid == TD_ArrowRight) {
			SS_ChangeSkin(playerid, CurrentIndex[playerid] + 1, CurrentIndex[playerid]);
			return 1;
		} else if (clickedid == TD_Select) {
			SS_CallFunction(playerid, SS_Response_Select, OldSkin[playerid], SkinsArray[ CurrentIndex[playerid] ]);
			return 1;

	#if defined _mselect_included
		} else if (clickedid == TD_List) {
			IsListOpen[playerid] = true;
			SS_HideTextDraws(playerid, false);
			MSelect_Open(playerid, MSelect:SkinSelect, SkinsArray, SkinsCount, .list_loop = true,
			             .header = "Select skin", .header_fg_color = 0xFFA500FF);
			return 1;
	#endif

		} else if (clickedid == TD_Exit || clickedid == Text:INVALID_TEXT_DRAW) {
			SkinSelect_Stop(playerid);
			return 1;
		}
	}

	#if defined SS_OnPlayerClickTextDraw
		return SS_OnPlayerClickTextDraw(playerid, clickedid);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw SS_OnPlayerClickTextDraw
#if defined SS_OnPlayerClickTextDraw
	forward SS_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

/*
	MSelectResponse:SkinSelect
*/
#if defined _mselect_included

MSelectResponse:SkinSelect(playerid, MSelectType:response, itemid, modelid)
{
	if (response == MSelect_Item || response == MSelect_Button || response == MSelect_Cancel) {
		IsListOpen[playerid] = false;

		if (response == MSelect_Item) {
			MSelect_Close(playerid);
			SS_ChangeSkin(playerid, itemid, CurrentIndex[playerid]);
		}

		SS_ShowTextDraws(playerid);
	}
	return 1;
}

#endif

/*
	Public functions
*/

stock IsSkinValid(skinid)
{
	if (SKINS_MINID <= skinid <= SKINS_MAXID) {
		switch (skinid) {
			case SKINS_IGNORE: {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

stock SkinSelect_Start(playerid, const function[])
{
	IsSelectOpen[playerid] = true;

	OldSkin[playerid] = GetPlayerSkin(playerid);
	CurrentIndex[playerid] = 0;
	FunctionName[playerid][0] = '\0';
	strcat(FunctionName[playerid], function, sizeof(FunctionName[]));

	new newskin = SkinsArray[0];
	SetPlayerSkin(playerid, newskin);
	SS_ShowTextDraws(playerid);
	SS_CallFunction(playerid, SS_Response_Start, OldSkin[playerid], newskin);
}

stock SkinSelect_Stop(playerid)
{
	IsSelectOpen[playerid] = false;

	SetPlayerSkin(playerid, OldSkin[playerid]);
	SS_HideTextDraws(playerid);
	SS_CallFunction(playerid, SS_Response_Stop, OldSkin[playerid], SkinsArray[ CurrentIndex[playerid] ]);

	OldSkin[playerid] = 0;
	CurrentIndex[playerid] = 0;
	FunctionName[playerid][0] = '\0';
}

stock SkinSelect_GetCurrentSkin(playerid)
{
	return SkinsArray[ CurrentIndex[playerid] ];
}

stock SkinSelect_GetOldSkin(playerid)
{
	return OldSkin[playerid];
}

/*
	Private functions
*/

static stock SS_CallFunction(playerid, SS_Response:type, oldskin, newskin)
{
	new call_func[SKINSELECT_MAX_FUNCTION_NAME] = "ssr_";
	strcat(call_func, FunctionName[playerid]);

	if (funcidx(call_func) != -1) {
		CallLocalFunction(call_func, "iiii", playerid, _:type, oldskin, newskin);
	}
}

static stock SS_HideTextDraws(playerid, bool:cancel_select = true)
{
	TextDrawHideForPlayer(playerid, TD_ArrowLeft);
	TextDrawHideForPlayer(playerid, TD_ArrowRight);
	TextDrawHideForPlayer(playerid, TD_Select);
#if defined _mselect_included
	TextDrawHideForPlayer(playerid, TD_List);
#endif
	TextDrawHideForPlayer(playerid, TD_Exit);

	if (cancel_select) {
		TD_SkipCancel[playerid] = true;
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

static stock SS_ShowTextDraws(playerid, bool:set_select = true)
{
	TextDrawShowForPlayer(playerid, TD_ArrowLeft);
	TextDrawShowForPlayer(playerid, TD_ArrowRight);
	TextDrawShowForPlayer(playerid, TD_Select);
#if defined _mselect_included
	TextDrawShowForPlayer(playerid, TD_List);
#endif
	TextDrawShowForPlayer(playerid, TD_Exit);

	if (set_select) {
		SelectTextDraw(playerid, 0xFFFFFFFF);
	}
	return 1;
}

static stock SS_ChangeSkin(playerid, index, prev_index)
{
	if (index < 0) {
		index = sizeof(SkinsArray) - 1;
	} else if (index >= sizeof(SkinsArray)) {
		index = 0;
	}

	new
		oldskin = SkinsArray[prev_index],
		newskin = SkinsArray[index];

	CurrentIndex[playerid] = index;
	SetPlayerSkin(playerid, newskin);

	SS_CallFunction(playerid, SS_Response_Change, oldskin, newskin);
}
