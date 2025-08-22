cmake_minimum_required(VERSION 4.0)
set(GAME_NAME hl2)
target_include_directories(server PUBLIC ../.. ./ ../shared/hl2 hl2)
target_compile_definitions(server PUBLIC HL2_DLL USES_SAVERESTORE)
target_sources(server PUBLIC
	ai_eventresponse.cpp
	ai_eventresponse.h
	ai_relationship.cpp
	base_gameinterface.cpp
	basegrenade_concussion.cpp
	basegrenade_contact.cpp
	basegrenade_timed.cpp
	EntityFlame.h
	hl2/Func_Monitor.cpp
	grenadethrown.cpp
	grenadethrown.h
	h_cycler.cpp
	h_cycler.h
	logic_achievement.cpp
	monstermaker.cpp
	monstermaker.h
	physics_bone_follower.h
	../shared/ragdoll_shared.h
	../shared/solidsetdefaults.h
	../shared/hl2/survival_gamerules.cpp
	team_spawnpoint.cpp
	team_spawnpoint.h
	../shared/touchlink.h
	vehicle_choreo_generic.cpp
	../shared/vehicle_choreo_generic_shared.h
	../shared/weapon_parse_default.cpp
)