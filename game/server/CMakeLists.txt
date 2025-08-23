cmake_minimum_required(VERSION 4.0)
project(server)
add_library(server SHARED)

target_include_directories(server PUBLIC ../shared ../../utils/common ../shared/econ NextBot ../../common ../../public ../../public/tier0 ../../public/tier1
                                        .)

# DISABLE_STEAM doesn't work, NO_STEAM is actually checked
target_compile_definitions(server PUBLIC DISABLE_STEAM=1 NO_STEAM GAME_DLL VECTOR _snprintf=use_Q_snprintf_instead) # strncpy=use_Q_strncpy_instead

add_dependencies     (server        choreoobjects dmxloader mathlib particles tier0 tier1 tier2 tier3 vstdlib steam_api)
target_link_libraries(server PUBLIC choreoobjects dmxloader mathlib particles tier0 tier1 tier2 tier3 vstdlib steam_api)

if(WIN32)
    target_compile_definitions(server PUBLIC fopen=dont_use_fopen)
    target_sources(server PUBLIC ../../public/haptics/haptic_utils.cpp)
endif()

target_sources(server PUBLIC
        # the acheivements api is causing issues with the steam api stub
         ../shared/achievementmgr.cpp
        ../shared/achievement_saverestore.cpp
         ../shared/baseachievement.cpp
        ../shared/achievements_hlx.cpp
        ../shared/activitylist.cpp
        ../../public/tier0/memoverride.cpp
        ai_activity.cpp
        ai_baseactor.cpp
        ai_basehumanoid.cpp
        ai_basenpc.cpp
        ai_basenpc_flyer.cpp
        ai_basenpc_flyer_new.cpp
        ai_basenpc_movement.cpp
        ai_basenpc_physicsflyer.cpp
        ai_basenpc_schedule.cpp
        ai_basenpc_squad.cpp
        ai_behavior.cpp
        ai_behavior_assault.cpp
        ai_behavior_fear.cpp
        ai_behavior_follow.cpp
        ai_behavior_lead.cpp
        ai_behavior_rappel.cpp
        ai_behavior_standoff.cpp
        ai_blended_movement.cpp
        ai_concommands.cpp
        ai_condition.cpp
        AI_Criteria.cpp
        ai_default.cpp
        ai_dynamiclink.cpp
        ai_event.cpp
        ai_goalentity.cpp
        ai_hint.cpp
        ai_hull.cpp
        ai_initutils.cpp
        AI_Interest_Target.cpp
        ai_link.cpp
        ai_localnavigator.cpp
        ai_looktarget.cpp
        ai_memory.cpp
        ai_motor.cpp
        ai_moveprobe.cpp
        ai_moveshoot.cpp
        ai_movesolver.cpp
        ai_namespaces.cpp
        ai_navigator.cpp
        ai_network.cpp
        ai_networkmanager.cpp
        ai_node.cpp
        ai_pathfinder.cpp
        ai_planesolver.cpp
        ai_playerally.cpp
        AI_ResponseSystem.cpp
        ai_route.cpp
        ai_saverestore.cpp
        ai_schedule.cpp
        ai_scriptconditions.cpp
        ai_senses.cpp
        ai_sentence.cpp
        ai_speech.cpp
        ai_speechfilter.cpp
        ai_squad.cpp
        ai_squadslot.cpp
        ai_tacticalservices.cpp
        ai_task.cpp
        ai_trackpather.cpp
        ai_utils.cpp
        ai_waypoint.cpp
        ../shared/ammodef.cpp
        ../shared/animation.cpp
        ../shared/base_playeranimstate.cpp
        base_transmit_proxy.cpp
        baseanimating.cpp
        BaseAnimatingOverlay.cpp
        basecombatcharacter.cpp
        ../shared/basecombatcharacter_shared.cpp
        basecombatweapon.cpp
        ../shared/basecombatweapon_shared.cpp
        baseentity.cpp
        ../shared/baseentity_shared.cpp
        baseflex.cpp
        ../shared/basegrenade_shared.cpp
        basemultiplayerplayer.cpp
        ../shared/baseparticleentity.cpp
        ../shared/baseplayer_shared.cpp
        ../shared/baseprojectile.cpp
        baseviewmodel.cpp
        ../shared/baseviewmodel_shared.cpp
        ../shared/beam_shared.cpp
        bitstring.cpp
        bmodels.cpp
        buttons.cpp
        cbase.cpp
        client.cpp
        ../shared/collisionproperty.cpp
        colorcorrection.cpp
        colorcorrectionvolume.cpp
        CommentarySystem.cpp
        controlentities.cpp
        cplane.cpp
        CRagdollMagnet.cpp
        damagemodifier.cpp
        ../shared/death_pose.cpp
        ../shared/debugoverlay_shared.cpp
        ../shared/decals.cpp
        doors.cpp
        dynamiclight.cpp
        ../shared/effect_dispatch_data.cpp
        effects.cpp
        EffectsServer.cpp
        ../shared/ehandle.cpp
        entityblocker.cpp
        EntityDissolve.cpp
        EntityFlame.cpp
        entitylist.cpp
        ../shared/entitylist_base.cpp
        EntityParticleTrail.cpp
        ../shared/EntityParticleTrail_Shared.cpp
        env_debughistory.cpp
        ../shared/env_detail_controller.cpp
        env_effectsscript.cpp
        env_entity_maker.cpp
        env_particlescript.cpp
        env_player_surface_trigger.cpp
        env_projectedtexture.cpp
        env_screenoverlay.cpp
        env_texturetoggle.cpp
        env_tonemap_controller.cpp
        ../shared/env_wind_shared.cpp
        env_zoom.cpp
        EnvBeam.cpp
        EnvFade.cpp
        EnvHudHint.cpp
        EnvLaser.cpp
        EnvMessage.cpp
        envmicrophone.cpp
        EnvShake.cpp
        EnvSpark.cpp
        ../shared/eventlist.cpp
        EventLog.cpp
        explode.cpp
        filters.cpp
        fire.cpp
        fire_smoke.cpp
        fish.cpp
        fogcontroller.cpp
        fourwheelvehiclephysics.cpp
        func_areaportal.cpp
        func_areaportalbase.cpp
        func_areaportalwindow.cpp
        func_break.cpp
        func_breakablesurf.cpp
        func_dust.cpp
        ../shared/func_ladder.cpp
        func_ladder_endpoint.cpp
        func_lod.cpp
        func_movelinear.cpp
        func_occluder.cpp
        func_reflective_glass.cpp
        func_smokevolume.cpp
        game.cpp
        game_ui.cpp
        gameinterface.cpp
        ../shared/gamemovement.cpp
        ../shared/gamerules.cpp
        ../shared/gamerules_register.cpp
        ../shared/GameStats.cpp
        ../shared/gamestringpool.cpp
        gametrace_dll.cpp
        ../shared/gamevars_shared.cpp
        gameweaponmanager.cpp
        genericactor.cpp
        genericmonster.cpp
        gib.cpp
        globals.cpp
        globalstate.cpp
        guntarget.cpp
        h_ai.cpp
        hierarchy.cpp
        hltvdirector.cpp
        ../shared/hintmessage.cpp
        ../shared/hintsystem.cpp
        ../shared/igamesystem.cpp
        info_camera_link.cpp
        info_overlay_accessor.cpp
        intermission.cpp
        item_world.cpp
        lightglow.cpp
        lights.cpp
        logic_measure_movement.cpp
        logic_navigation.cpp
        logicauto.cpp
        logicentities.cpp
        logicrelay.cpp
        mapentities.cpp
        ../shared/mapentities_shared.cpp
        maprules.cpp
        MaterialModifyControl.cpp
        message_entity.cpp
        modelentities.cpp
        ../shared/ModelSoundsCache.cpp
        movehelper_server.cpp
        movement.cpp
        ../shared/movevars_shared.cpp
        ../shared/multiplay_gamerules.cpp
        ndebugoverlay.cpp
        npc_vehicledriver.cpp
        ../shared/obstacle_pushaway.cpp
        particle_light.cpp
        ../shared/particle_parse.cpp
        particle_system.cpp
        ../shared/particlesystemquery.cpp
        pathcorner.cpp
        pathtrack.cpp
        phys_controller.cpp
        physconstraint.cpp
        physics.cpp
        physics_bone_follower.cpp
        physics_cannister.cpp
        physics_fx.cpp
        physics_impact_damage.cpp
        physics_main.cpp
        ../shared/physics_main_shared.cpp
        physics_npc_solver.cpp
        physics_prop_ragdoll.cpp
        ../shared/physics_saverestore.cpp
        ../shared/physics_shared.cpp
        physobj.cpp
        player.cpp
        player_command.cpp
        player_lagcompensation.cpp
        player_pickup.cpp
        player_resource.cpp
        playerinfomanager.cpp
        playerlocaldata.cpp
        plugin_check.cpp
        ../shared/point_bonusmaps_accessor.cpp
        point_camera.cpp
        point_devshot_camera.cpp
        point_playermoveconstraint.cpp
        ../shared/point_posecontroller.cpp
        point_spotlight.cpp
        point_template.cpp
        pointanglesensor.cpp
        PointAngularVelocitySensor.cpp
        pointhurt.cpp
        pointteleport.cpp
        ../shared/precache_register.cpp
        ../shared/predictableid.cpp
        props.cpp
        ../shared/props_shared.cpp
        ../shared/querycache.cpp
        ragdoll_manager.cpp
        ../shared/ragdoll_shared.cpp
        RagdollBoogie.cpp
        recipientfilter.cpp
        rope.cpp
        ../shared/rope_helpers.cpp
        ../shared/saverestore.cpp
        saverestore_gamedll.cpp
        ../shared/SceneCache.cpp
        sceneentity.cpp
        ../shared/sceneentity_shared.cpp
        scratchpad_gamedll_helpers.cpp
        scripted.cpp
        scriptedtarget.cpp
        sendproxy.cpp
        ../shared/sequence_Transitioner.cpp
        ../server/serverbenchmark_base.cpp
        ServerNetworkProperty.cpp
        shadowcontrol.cpp
        ../shared/simtimer.cpp
        ../shared/singleplay_gamerules.cpp
        SkyCamera.cpp
        slideshow_display.cpp
        sound.cpp
        ../shared/SoundEmitterSystem.cpp
        soundent.cpp
        ../shared/soundenvelope.cpp
        ../../public/SoundParametersInternal.cpp
        soundscape.cpp
        soundscape_system.cpp
        spotlightend.cpp
        ../shared/Sprite.cpp
        sprite_perfmonitor.cpp
        ../shared/studio_shared.cpp
        subs.cpp
        sun.cpp
        tactical_mission.cpp
        ../shared/takedamageinfo.cpp
        tanktrain.cpp
        team.cpp
        ../shared/teamplay_gamerules.cpp
        TemplateEntities.cpp
        tempmonster.cpp
        tesla.cpp
        ../shared/test_ehandle.cpp
        test_proxytoggle.cpp
        test_stressentities.cpp
        testfunctions.cpp
        testtraceline.cpp
        textstatsmgr.cpp
        timedeventmgr.cpp
        trains.cpp
        triggers.cpp
        ../shared/usercmd.cpp
        util.cpp
        ../shared/util_shared.cpp
        variant_t.cpp
        vehicle_base.cpp
        vehicle_baseserver.cpp
        ../shared/vehicle_viewblend_shared.cpp
        vguiscreen.cpp
        ../shared/voice_gamemgr.cpp
        waterbullet.cpp
        WaterLODControl.cpp
        wcedit.cpp
        ../shared/weapon_parse.cpp
        ../shared/weapon_proficiency.cpp
        weight_button.cpp
        world.cpp
        ../shared/mp_shareddefs.cpp
        ../server/vote_controller.cpp
        ../../public/haptics/haptic_msgs.cpp

        # replay
        # gamedll_replay.cpp

        # tools framework
        entity_tools_server.cpp

        # not using pch? i don't know if this is necessary
        ../../public/bone_setup.cpp
        ../../public/collisionutils.cpp
        ../../public/dt_send.cpp
        ../../public/dt_utlvector_common.cpp
        ../../public/dt_utlvector_send.cpp
        ../../public/editor_sendcommand.cpp
        ../../public/filesystem_helpers.cpp
        gamehandle.cpp
        h_export.cpp
        init_factory.cpp
        ../../public/interpolatortypes.cpp
        ../../game/shared/interval.cpp
        ../../public/keyframe/keyframe.cpp
        ../../common/language.cpp
        ../../public/map_utils.cpp
        ../../public/networkvar.cpp
        ../../common/randoverride.cpp
        ../../public/registry.cpp
        ../../public/rope_physics.cpp
        ../../public/scratchpad3d.cpp
        ../../public/ScratchPadUtils.cpp
        ../../public/server_class.cpp
        ../../game/shared/sheetsimulator.cpp
        ../../public/simple_physics.cpp
        ../../public/stringregistry.cpp
        ../../public/studio.cpp
        GameStats_BasicStatsFunctions.cpp

        # aand to make dlopen happy
        # ../../tier0/threadtools.cpp
        basetempentity.cpp
        te.cpp
        te_armorricochet.cpp
        te_basebeam.cpp
        te_beamentpoint.cpp
        te_beaments.cpp
        te_beamfollow.cpp
        te_beamlaser.cpp
        te_beampoints.cpp
        te_beamring.cpp
        te_beamringpoint.cpp
        te_beamspline.cpp
        te_bloodsprite.cpp
        te_bloodstream.cpp
        te_breakmodel.cpp
        te_bspdecal.cpp
        te_bubbles.cpp
        te_bubbletrail.cpp
        te_clientprojectile.cpp
        te_decal.cpp
        te_dynamiclight.cpp
        te_effect_dispatch.cpp
        te_energysplash.cpp
        te_explosion.cpp
        te_fizz.cpp
        te_footprintdecal.cpp
        te_glassshatter.cpp
        te_glowsprite.cpp
        te_impact.cpp
        te_killplayerattachments.cpp
        te_largefunnel.cpp
        te_muzzleflash.cpp
        te_particlesystem.cpp
        te_physicsprop.cpp
        te_playerdecal.cpp
        te_projecteddecal.cpp
        te_showline.cpp
        te_smoke.cpp
        te_sparks.cpp
        te_sprite.cpp
        te_spritespray.cpp
        te_worlddecal.cpp
        # ../../tier1/datamanager.cpp
        ../shared/usermessages.cpp
        # ../../tier1/tier1.cpp # oh dear god no
        # ../../tier1/utlsymbol.cpp
        # ../../tier1/mempool.cpp
        smoke_trail.cpp
        # ../../tier0/vcrmode.cpp # TODO: Might want to fix it.
        steamjet.cpp
        toolframework_server.cpp
        ../../dmxloader/dmxloader.cpp # bad idea, but the UnserializeDMX symbol is missing even though we link dmxloader?!@?
        ../shared/SpriteTrail.cpp
        ../../mathlib/randsse.cpp
        plasma.cpp
        event_tempentity_tester.cpp
)

# we don't need to bother with vpc projects, just use subdirs, and include the base project
# TODO: make the rest of the project files
if(BUILD_GAME STREQUAL "hl2")
    include(hl2.cmake)
elseif(BUILD_GAME STREQUAL "episodic")
    include(episodic.cmake)
elseif(BUILD_GAME STREQUAL "hl2mp")
    message(FATAL_ERROR "Half-Life 2: Deathmatch has not been ported to CMake yet!")
    include(hl2mp.cmake)
elseif(BUILD_GAME STREQUAL "portal")
    message(FATAL_ERROR "Portal has not been ported to CMake yet!")
    include(portal.cmake)
elseif(BUILD_GAME STREQUAL "hl1")
    message(FATAL_ERROR "Half-Life: Source has not been ported to CMake yet!")
    include(hl1.cmake)
elseif(BUILD_GAME STREQUAL "hl1mp")
    message(FATAL_ERROR "Half-Life Deathmatch: Source has not been ported to CMake yet!")
    include(hl1mp.cmake)
elseif(BUILD_GAME STREQUAL "cstrike")
    message(FATAL_ERROR "CSS has not been ported to CMake yet!")
    include(cstrike.cmake)
elseif(BUILD_GAME STREQUAL "dod")
    message(FATAL_ERROR "Day of Defeat has not been ported to CMake yet!")
    include(dod.cmake)
elseif(BUILD_GAME STREQUAL "tf")
    message(WARNING "Consider using the latest TF2 SDK instead.")
    message(FATAL_ERROR "TF2 has not been ported to CMake yet!")
    include(tf.cmake)
else()
    message(FATAL_ERROR "Game '${BUILD_GAME}' is not a valid target! (hl2, episodic, hl2mp, portal, hl1, hl1mp, cstrike, dod, tf)")
endif()

# the GAME_NAME variable should be set by now
set(GAME_BIN_DIR ${GAME_NAME}/bin)

if(NOT (ANDROID EQUAL 1))
    install(TARGETS server DESTINATION ${GAME_BIN_DIR})
endif()