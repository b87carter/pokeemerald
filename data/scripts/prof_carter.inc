ProfCarter_EventScript_UpdateLocation::
	goto_if_eq VAR_PETALBURG_GYM_STATE, 0, Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfCarter_EventScript_MoveToLab
	call_if_eq VAR_CARTER_STATE, 0, ProfCarter_EventScript_MoveToLab
	call_if_eq VAR_CARTER_STATE, 1, ProfCarter_EventScript_MoveToLab
	call_if_eq VAR_CARTER_STATE, 2, ProfCarter_EventScript_MoveToRoute101
	call_if_eq VAR_CARTER_STATE, 3, ProfCarter_EventScript_MoveToRoute101
	call_if_eq VAR_CARTER_STATE, 4, ProfCarter_EventScript_MoveToRoute103
	call_if_eq VAR_CARTER_STATE, 5, ProfCarter_EventScript_MoveToRoute103
	call_if_eq VAR_CARTER_STATE, 6, ProfCarter_EventScript_MoveToLab
	call_if_eq VAR_CARTER_STATE, 7, ProfCarter_EventScript_MoveToLab
	return

ProfCarter_EventScript_MoveToLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_CARTERS_LAB_CARTER
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_CARTERS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_CARTER
	setflag FLAG_HIDE_ROUTE_103_CARTER
	return

ProfCarter_EventScript_MoveToRoute101::
	clearflag FLAG_HIDE_ROUTE_101_CARTER
	setflag FLAG_HIDE_LITTLEROOT_TOWN_CARTERS_LAB_CARTER
	setflag FLAG_HIDE_LITTLEROOT_TOWN_CARTERS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_CARTER
	return

ProfCarter_EventScript_MoveToRoute103::
	clearflag FLAG_HIDE_ROUTE_103_CARTER
	setflag FLAG_HIDE_ROUTE_101_CARTER
	setflag FLAG_HIDE_LITTLEROOT_TOWN_CARTERS_LAB_CARTER
	setflag FLAG_HIDE_LITTLEROOT_TOWN_CARTERS_LAB_UNKNOWN_0x380
	return

ProfCarter_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, ProfCarter_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_CARTER_MATCH_CALL, EventScript_RegisterProfCarter

ProfCarter_EventScript_AskRatePokedex::
	msgbox gCarterDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ProfCarter_EventScript_DeclineRating
	call ProfCarter_EventScript_RatePokedex
	release
	end

ProfCarter_EventScript_DeclineRating::
	msgbox gCarterDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfCarter_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfCarter_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	msgbox gCarterDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfCarter_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num National seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num National caught
	msgbox gCarterDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return
