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

#if !defined ShowModelSelectionMenuEx
	#error "Please include mSelection before skinselect"
#endif

#if defined _skin_select_included
	#endinput
#endif

#define _skin_select_included

/*
	Defines
*/

#define MSELECTION_MENU_ID 37000
#define SKINSELECT_MAX_FUNCTION_NAME 32

#if !defined SKINS_IGNORE
	#define SKINS_IGNORE 0, 74
#endif

#if !defined SKINS_MINID
	#define SKINS_MINID 1
#endif

#if !defined SKINS_MAXID
	#define SKINS_MAXID 311
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
	FunctionName[MAX_PLAYERS][SKINSELECT_MAX_FUNCTION_NAME - 4],
	CurrentSkin[MAX_PLAYERS],
	OldSkin[MAX_PLAYERS],
	SkinsArray[SKINS_MAXID + 1],
	SkinsCount,

	Text:TD_ArrowLeft,
	Text:TD_ArrowRight,
	Text:TD_Select,
	Text:TD_List,
	Text:TD_Exit;

/*
	OnGameModeInit
*/

public OnGameModeInit()
{
	// mSelection array
	for (new skinid = 0; skinid <= SKINS_MAXID; skinid++) {
		switch (skinid) {
			case SKINS_IGNORE: {

			}
			default: {
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
	if (IsSelectOpen[playerid]) {
		if (clickedid == TD_ArrowLeft) {
			SS_ChangeSkin(playerid, CurrentSkin[playerid], CurrentSkin[playerid] - 1);
			return 0;
		} else if (clickedid == TD_ArrowRight) {
			SS_ChangeSkin(playerid, CurrentSkin[playerid], CurrentSkin[playerid] + 1);
			return 0;
		} else if (clickedid == TD_Select) {
			SS_CallFunction(playerid, SS_Response_Select, OldSkin[playerid], CurrentSkin[playerid]);
			return 0;
		} else if (clickedid == TD_List) {
			IsListOpen[playerid] = true;
			SS_HideTextDraws(playerid, false);
			ShowModelSelectionMenuEx(playerid, SkinsArray, SkinsCount, "Select skin", MSELECTION_MENU_ID, 16.0, 0.0, -55.0);
			return 0;
		} else if ((clickedid == TD_Exit || clickedid == Text:INVALID_TEXT_DRAW) && !IsListOpen[playerid]) {
			SkinSelect_Stop(playerid);
			return 0;
		}
	}

	#if defined SS_OnPlayerClickTextDraw
		return SS_OnPlayerClickTextDraw(playerid, clickedid);
	#else
		return 1;
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
	OnPlayerModelSelectionEx
*/

public OnPlayerModelSelectionEx(playerid, response, extraid, modelid)
{
	if (extraid == MSELECTION_MENU_ID) {
		IsListOpen[playerid] = false;
		SS_ShowTextDraws(playerid);

		if (response) {
			SS_ChangeSkin(playerid, CurrentSkin[playerid], modelid);
		}

		return 0;
	}

	#if defined SS_OnPlayerModelSelectionEx
		return SS_OnPlayerModelSelectionEx(playerid, response, extraid, modelid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerModelSelectionEx
	#undef OnPlayerModelSelectionEx
#else
	#define _ALS_OnPlayerModelSelectionEx
#endif

#define OnPlayerModelSelectionEx SS_OnPlayerModelSelectionEx
#if defined SS_OnPlayerModelSelectionEx
	forward SS_OnPlayerModelSelectionEx(playerid, response, extraid, modelid);
#endif

/*
	Public functions
*/

stock IsSkinValid(skinid)
{
	switch (skinid) {
		case SKINS_IGNORE: {
			return 0;
		}
	}

	return 1;
}

stock SkinSelect_Start(playerid, function[])
{
	IsSelectOpen[playerid] = true;

	OldSkin[playerid] = GetPlayerSkin(playerid);
	CurrentSkin[playerid] = SKINS_MINID;
	strmid(FunctionName[playerid], function, 0, strlen(function), sizeof(FunctionName[]));

	SetPlayerSkin(playerid, CurrentSkin[playerid]);

	SS_ShowTextDraws(playerid);

	SS_CallFunction(playerid, SS_Response_Start, OldSkin[playerid], CurrentSkin[playerid]);
}

stock SkinSelect_Stop(playerid)
{
	IsSelectOpen[playerid] = false;

	SetPlayerSkin(playerid, OldSkin[playerid]);

	SS_HideTextDraws(playerid);

	SS_CallFunction(playerid, SS_Response_Stop, OldSkin[playerid], CurrentSkin[playerid]);

	OldSkin[playerid] = 0;
	CurrentSkin[playerid] = 0;
	FunctionName[playerid][0] = '\0';
}

stock SkinSelect_GetCurrentSkin(playerid)
{
	return CurrentSkin[playerid];
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
	new call_func[SKINSELECT_MAX_FUNCTION_NAME];
	strcat(call_func, "ssr_");
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
	TextDrawHideForPlayer(playerid, TD_List);
	TextDrawHideForPlayer(playerid, TD_Exit);

	if (cancel_select) {
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

static stock SS_ShowTextDraws(playerid, bool:set_select = true)
{
	TextDrawShowForPlayer(playerid, TD_ArrowLeft);
	TextDrawShowForPlayer(playerid, TD_ArrowRight);
	TextDrawShowForPlayer(playerid, TD_Select);
	TextDrawShowForPlayer(playerid, TD_List);
	TextDrawShowForPlayer(playerid, TD_Exit);

	if (set_select) {
		SelectTextDraw(playerid, 0xFFFFFFFF);
	}
	return 1;
}

static stock SS_ChangeSkin(playerid, oldskin, newskin)
{
	if (newskin > SKINS_MAXID) {
		newskin = SKINS_MINID;
	} else if (newskin < SKINS_MINID) {
		newskin = SKINS_MAXID;
	}

	if (!IsSkinValid(newskin)) {
		newskin += (newskin > oldskin) ? 1 : -1;
	}

	SetPlayerSkin(playerid, newskin);
	CurrentSkin[playerid] = newskin;

	SS_CallFunction(playerid, SS_Response_Change, oldskin, newskin);
}
