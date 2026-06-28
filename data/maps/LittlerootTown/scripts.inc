LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Carter
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveSusanToMaysDoor
	call_if_unset FLAG_RESCUED_CARTER, LittlerootTown_EventScript_SetTwinPos
	call_if_eq VAR_LITTLEROOT_TOWN_STATE, 3, LittlerootTown_EventScript_SetSusanStandingInFrontOfDoorPos
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_MAY, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_OLDALE_RIVAL_STATE, 1, LittlerootTown_EventScript_MoveRivalFromOldale
	call_if_eq VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_EventScript_SetRivalLeftForRoute103
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_HideMapNamePopup
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_EventScript_LeftLabAfterDexUpgrade
	end

LittlerootTown_EventScript_LeftLabAfterDexUpgrade::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

LittlerootTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

LittlerootTown_EventScript_MoveRivalFromOldale::
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	return

LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
	return

LittlerootTown_EventScript_MoveSusanToMaysDoor::
	setobjectxyperm LOCALID_LITTLEROOT_SUSAN, 14, 8
	return

LittlerootTown_EventScript_SetTwinPos::
	goto_if_eq VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_SetTwinGuardingRoutePos
	setobjectxyperm LOCALID_LITTLEROOT_TWIN, 10, 1
	setobjectmovementtype LOCALID_LITTLEROOT_TWIN, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_SetTwinGuardingRoutePos::
	setobjectxyperm LOCALID_LITTLEROOT_TWIN, 7, 2
	setobjectmovementtype LOCALID_LITTLEROOT_TWIN, MOVEMENT_TYPE_FACE_DOWN
	return

LittlerootTown_EventScript_SetSusanStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_SUSAN_OUTSIDE
	setobjectmovementtype LOCALID_LITTLEROOT_SUSAN, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetSusanInFrontOfDoorMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetSusanInFrontOfDoorFemale
	return

LittlerootTown_EventScript_SetSusanInFrontOfDoorMale::
	setobjectxyperm LOCALID_LITTLEROOT_SUSAN, 5, 9
	return

LittlerootTown_EventScript_SetSusanInFrontOfDoorFemale::
	setobjectxyperm LOCALID_LITTLEROOT_SUSAN, 14, 9
	return

LittlerootTown_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
	.2byte 0

LittlerootTown_EventScript_StepOffTruckMale::
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithSusan
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_StepOffTruckFemale::
	lockall
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithSusan
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_GoInsideWithSusan::
	delay 15
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_LITTLEROOT_SUSAN
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerAtTruck
	waitmovement 0
	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachDoor
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanEnterHouse
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_LITTLEROOT_TOWN_SUSAN_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideplayer
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_Movement_SusanExitHouse:
	walk_down
	step_end

LittlerootTown_Movement_SusanApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_Movement_SusanApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

LittlerootTown_Movement_SusanEnterHouse:
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

LittlerootTown_EventScript_BeginDexUpgradeScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_LITTLEROOT_CARTER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox LittlerootTown_Text_CarterSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_CARTER
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_CARTERS_LAB, 6, 5
	waitstate
	releaseall
	end

LittlerootTown_OnWarp:
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalCarterPosForDexUpgrade
	.2byte 0

LittlerootTown_EventScript_SetRivalCarterPosForDexUpgrade::
	addobject LOCALID_LITTLEROOT_CARTER
	addobject LOCALID_LITTLEROOT_RIVAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetRivalCarterPosForDexUpgradeMale
	goto LittlerootTown_EventScript_SetRivalCarterPosForDexUpgradeFemale
	end

LittlerootTown_EventScript_SetRivalCarterPosForDexUpgradeMale::
	setobjectxy LOCALID_LITTLEROOT_RIVAL, 6, 10
	setobjectxy LOCALID_LITTLEROOT_CARTER, 5, 10
	end

LittlerootTown_EventScript_SetRivalCarterPosForDexUpgradeFemale::
	setobjectxy LOCALID_LITTLEROOT_RIVAL, 13, 10
	setobjectxy LOCALID_LITTLEROOT_CARTER, 14, 10
	end

LittlerootTown_EventScript_FatMan::
	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_NPC
	end

LittlerootTown_EventScript_Boy::
	msgbox LittlerootTown_Text_CarterSpendsDaysInLab, MSGBOX_NPC
	end

LittlerootTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_CARTER, LittlerootTown_EventScript_YouSavedCarter
	goto_if_ne VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_GoSaveCarter
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoSaveCarter::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	release
	end

LittlerootTown_EventScript_YouSavedCarter::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_YouSavedCarter, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoodLuck::
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_DangerousWithoutPokemon::
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinPushPlayerFromRoute
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_Movement_TwinApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

LittlerootTown_Movement_TwinPushPlayerFromRoute:
	walk_down
	step_end

LittlerootTown_Movement_TwinReturnLeft:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_faster_down
	step_end

LittlerootTown_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LittlerootTown_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_Movement_TwinApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

LittlerootTown_Movement_TwinReturnRight:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_EventScript_GoSaveCarterTrigger::
	lockall
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	releaseall
	end

LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_CartersLabSign::
	msgbox LittlerootTown_Text_ProfCartersLab, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BrendansHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_CartersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_CartersHouseSignFemale::
	msgbox LittlerootTown_Text_ProfCartersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_CartersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_CartersHouseSignMale::
	msgbox LittlerootTown_Text_ProfCartersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_GiveRunningShoesTrigger0::
	lockall
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_LITTLEROOT_SUSAN, 10, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger1::
	lockall
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_LITTLEROOT_SUSAN, 11, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger3::
	lockall
	setvar VAR_0x8008, 3
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger4::
	lockall
	setvar VAR_0x8008, 4
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger5::
	lockall
	setvar VAR_0x8008, 5
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SusanNoticePlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SusanNoticePlayerFemale
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	msgbox LittlerootTown_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SusanApproachPlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SusanApproachPlayerFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SusanReturnHomeMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SusanReturnHomeFemale
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SetHomeDoorCoordsFemale::
	setvar VAR_0x8009, 14
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SusanNoticePlayerMale::
	applymovement LOCALID_LITTLEROOT_SUSAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LittlerootTown_EventScript_SusanNoticePlayerFemale::
	applymovement LOCALID_LITTLEROOT_SUSAN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_SusanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_SusanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_SusanApproachPlayerMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_SusanApproachPlayerMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_SusanApproachPlayerMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_SusanApproachPlayerMale5
	return

LittlerootTown_EventScript_SusanApproachPlayerFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_SusanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_SusanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_SusanApproachPlayerFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_SusanApproachPlayerFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_SusanApproachPlayerFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_SusanApproachPlayerFemale5
	return

LittlerootTown_EventScript_SusanApproachPlayer0::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayer1::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerMale2::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerMale2
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerMale3::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerMale3
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerMale4::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerMale4
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerMale5::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerMale5
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerFemale2::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerFemale2
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerFemale3::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerFemale3
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerFemale4::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerFemale4
	waitmovement 0
	return

LittlerootTown_EventScript_SusanApproachPlayerFemale5::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanApproachPlayerFemale5
	waitmovement 0
	return

LittlerootTown_EventScript_SusanReturnHomeMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_SusanReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_SusanReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_SusanReturnHomeMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_SusanReturnHomeMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_SusanReturnHomeMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_SusanReturnHomeMale5
	return

LittlerootTown_EventScript_SusanReturnHomeFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_SusanReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_SusanReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_SusanReturnHomeFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_SusanReturnHomeFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_SusanReturnHomeFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_SusanReturnHomeFemale5
	return

LittlerootTown_EventScript_SusanReturnHome0::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHome0
	waitmovement 0
	return

LittlerootTown_EventScript_SusanReturnHome1::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHome1
	waitmovement 0
	return

LittlerootTown_EventScript_SusanReturnHomeMale2::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeMale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeMale3::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeMale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeMale4::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeMale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeMale5::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeMale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeFemale2::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeFemale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeFemale3::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeFemale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeFemale4::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeFemale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_SusanReturnHomeFemale5::
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanReturnHomeFemale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_Movement_SusanApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_SusanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_SusanApproachPlayerMale2:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_SusanApproachPlayerMale3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_SusanApproachPlayerMale4:
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_SusanApproachPlayerMale5:
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_SusanApproachPlayerFemale2:
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_SusanApproachPlayerFemale3:
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_SusanApproachPlayerFemale4:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_SusanApproachPlayerFemale5:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_SusanReturnHome0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_SusanReturnHome1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_SusanReturnHomeMale2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeMale3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeMale4:
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeMale5:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeFemale2:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeFemale3:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeFemale4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanReturnHomeFemale5:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_SusanExitThroughDoor:
	walk_up
	step_end

LittlerootTown_EventScript_Susan::
	lock
	faceplayer
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	applymovement LOCALID_LITTLEROOT_SUSAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_SUSAN, LittlerootTown_Movement_SusanExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_SUSAN, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetReceivedRunningShoes::
	removeobject LOCALID_LITTLEROOT_SUSAN
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	release
	end

LittlerootTown_EventScript_GiveRunningShoes::
	msgbox LittlerootTown_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_Text_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox LittlerootTown_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

LittlerootTown_Text_OurNewHomeLetsGoInside:
	.string "SUSAN: {PLAYER}, we're here, Mr. Dulin!\p"
	.string "It must be tiring riding with our things\n"
	.string "in the moving truck.\p"
	.string "Well, this is LITTLEROOT TOWN.\p"
	.string "How do you like it?\n"
	.string "This is our new home!\p"
	.string "It has a quaint feel, but it seems to be\n"
	.string "an easy place to live, don't you think?\p"
	.string "And, you get your own room, {PLAYER}!\n"
	.string "Let's go inside.$"

LittlerootTown_Text_WaitPlayer:
	.string "SUSAN: Wait, {PLAYER}!$"

LittlerootTown_Text_WearTheseRunningShoes:
	.string "SUSAN: {PLAYER}! {PLAYER}! Did you\n"
	.string "introduce yourself to PROF. CARTER?\p"
	.string "Oh! What an adorable POKéMON!\n"
	.string "You got it from PROF. CARTER. How nice!\p"
	.string "You're your father's child, all right.\n"
	.string "You look good together with POKéMON!\p"
	.string "Here, Mr. Dulin! If you're going out on an\n"
	.string "adventure, wear these RUNNING SHOES.\p"
	.string "They'll put a zip in your step!$"

LittlerootTown_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

LittlerootTown_Text_ExplainRunningShoes:
	.string "SUSAN: {PLAYER}, those shoes came with\n"
	.string "instructions.\p"
	.string "“Press the B Button while wearing these\n"
	.string "RUNNING SHOES to run extra-fast!\p"
	.string "“Slip on these RUNNING SHOES and race\n"
	.string "in the great outdoors!”$"

LittlerootTown_Text_ComeHomeIfAnythingHappens:
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "To think that you have your very own\n"
	.string "POKéMON now…\l"
	.string "Your father will be overjoyed.\p"
	.string "…But please be careful.\n"
	.string "If anything happens, you can come home.\p"
	.string "Go on, go get them, Mr. Dulin!$"

LittlerootTown_Text_CanUsePCToStoreItems:
	.string "If you use a PC, you can store items\n"
	.string "and POKéMON.\p"
	.string "The power of science is staggering!$"

LittlerootTown_Text_CarterSpendsDaysInLab:
	.string "PROF. CARTER spends days in his LAB\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does PROF. CARTER spend time\n"
	.string "at home?$"

LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Um, um, um!\p"
	.string "If you go outside and go in the grass,\n"
	.string "wild POKéMON will jump out!$"

LittlerootTown_Text_DangerousIfYouDontHavePokemon:
	.string "It's dangerous if you don't have\n"
	.string "your own POKéMON.$"

LittlerootTown_Text_CanYouGoSeeWhatsHappening:
	.string "Um, hi!\p"
	.string "There are scary POKéMON outside!\n"
	.string "I can hear their cries!\p"
	.string "I want to go see what's going on,\n"
	.string "but I don't have any POKéMON…\p"
	.string "Can you go see what's happening\n"
	.string "for me?$"

LittlerootTown_Text_YouSavedCarter:
	.string "You saved PROF. CARTER!\n"
	.string "I'm so glad!$"

LittlerootTown_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_Text_TownSign:
	.string "LITTLEROOT TOWN\n"
	.string "“A town that can't be shaded any hue.”$"

LittlerootTown_Text_ProfCartersLab:
	.string "PROF. CARTER'S POKéMON LAB$"

LittlerootTown_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

LittlerootTown_Text_ProfCartersHouse:
	.string "PROF. CARTER'S HOUSE$"

LittlerootTown_Text_CarterSomethingToShowYouAtLab:
	.string "PROF. CARTER: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

