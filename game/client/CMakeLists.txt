cmake_minimum_required(VERSION 4.0)
project(client)
add_library(client SHARED)

target_include_directories(client PUBLIC game_controls ../../vgui2/include ../../vgui2/vgui_controls ../shared .)

# DISABLE_STEAM doesn't work, NO_STEAM is actually checked
target_compile_definitions(client PUBLIC DISABLE_STEAM=1 NO_STEAM CLIENT_DLL NO_STRING_T VECTOR strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead)

add_dependencies(client tier0 tier1 tier2 tier3 particles dmxloader vgui_controls matsys_controls mathlib vstdlib choreoobjects steam_api bitmap vtf)
target_link_libraries(client PUBLIC tier0 tier1 tier2 tier3 particles dmxloader vgui_controls matsys_controls mathlib vstdlib choreoobjects steam_api bitmap vtf)
target_sources(client PUBLIC in_touch.cpp ../../public/tier0/memoverride.cpp)

find_package(CURL REQUIRED)
target_link_libraries(client PUBLIC rt z CURL::libcurl)

if(WIN32)
    target_compile_definitions(client PUBLIC fopen=dont_use_fopen)
    target_sources(client PUBLIC ../../public/haptics/haptic_utils.cpp)
endif()

if(UNIX)
	find_package(OpenSSL REQUIRED)
    target_link_libraries(client PUBLIC OpenSSL::Crypto)
endif()

if(LINUX)
	find_package(OpenSSL REQUIRED)
    target_link_libraries(client PUBLIC OpenSSL::SSL)
endif()

target_sources(client PUBLIC
        hl2/C_Func_Monitor.cpp
		geiger.cpp
		history_resource.cpp
		hud_weapon.cpp
		train.cpp
		../shared/weapon_parse_default.cpp
		../shared/achievement_saverestore.cpp
		../shared/achievementmgr.cpp
		../shared/achievements_hlx.cpp
		achievement_notification_panel.cpp
		../shared/activitylist.cpp
		alphamaterialproxy.cpp
		../shared/ammodef.cpp
		animatedentitytextureproxy.cpp
		animatedoffsettextureproxy.cpp
		animatedtextureproxy.cpp
		AnimateSpecificTextureProxy.cpp
		../shared/animation.cpp
		../shared/base_playeranimstate.cpp
		../shared/baseachievement.cpp
		baseanimatedtextureproxy.cpp
		baseclientrendertargets.cpp
		../shared/basecombatcharacter_shared.cpp
		../shared/basecombatweapon_shared.cpp
		../shared/baseentity_shared.cpp
		../shared/basegrenade_shared.cpp
		../shared/baseparticleentity.cpp
		../shared/baseplayer_shared.cpp
		../shared/baseprojectile.cpp
		../shared/baseviewmodel_shared.cpp
		beamdraw.cpp
		../shared/beam_shared.cpp
		../../public/bone_accessor.cpp
		bone_merge_cache.cpp
		c_ai_basehumanoid.cpp
		c_ai_basenpc.cpp
		c_baseanimating.cpp
		c_baseanimatingoverlay.cpp
		c_basecombatcharacter.cpp
		c_basecombatweapon.cpp
		c_basedoor.cpp
		c_baseentity.cpp
		c_baseflex.cpp
		c_baseplayer.cpp
		c_baseviewmodel.cpp
		c_breakableprop.cpp
		c_colorcorrection.cpp
		c_colorcorrectionvolume.cpp
		c_dynamiclight.cpp
		c_entitydissolve.cpp
		c_entityparticletrail.cpp
		c_env_fog_controller.cpp
		c_env_particlescript.cpp
		c_env_projectedtexture.cpp
		c_env_screenoverlay.cpp
		c_env_tonemap_controller.cpp
		c_fire_smoke.cpp
		c_fish.cpp
		c_func_areaportalwindow.cpp
		c_func_breakablesurf.cpp
		c_func_conveyor.cpp
		c_func_dust.cpp
		c_func_lod.cpp
		c_func_occluder.cpp
		c_func_reflective_glass.cpp
		c_func_rotating.cpp
		c_func_smokevolume.cpp
		c_func_tracktrain.cpp
		c_gib.cpp
		c_hairball.cpp
		c_info_overlay_accessor.cpp
		c_lightglow.cpp
		C_MaterialModifyControl.cpp
		c_particle_system.cpp
		c_physbox.cpp
		c_physicsprop.cpp
		c_physmagnet.cpp
		c_pixel_visibility.cpp
		c_plasma.cpp
		c_playerresource.cpp
		c_point_camera.cpp
		c_point_commentary_node.cpp
		c_props.cpp
		c_ragdoll_manager.cpp
		c_rope.cpp
		c_rumble.cpp
		c_sceneentity.cpp
		c_shadowcontrol.cpp
		c_slideshow_display.cpp
		c_soundscape.cpp
		c_spotlight_end.cpp
		c_sprite.cpp
		c_sprite_perfmonitor.cpp
		c_sun.cpp
		c_team.cpp
		c_tesla.cpp
		c_test_proxytoggle.cpp
		c_user_message_register.cpp
		c_vehicle_choreo_generic.cpp
		c_vehicle_jeep.cpp
		c_vguiscreen.cpp
		hl2/c_waterbullet.cpp
		hl2/hud_autoaim.cpp
		C_WaterLODControl.cpp
		c_world.cpp
		../shared/cam_thirdperson.cpp
		camomaterialproxy.cpp
		cdll_client_int.cpp
		cdll_bounded_cvars.cpp
		cdll_util.cpp
		cl_mat_stub.cpp
		classmap.cpp
		client_factorylist.cpp
		client_thinklist.cpp
		client_virtualreality.cpp
		clienteffectprecachesystem.cpp
		cliententitylist.cpp
		clientleafsystem.cpp
		clientmode_shared.cpp
		clientshadowmgr.cpp
		clientsideeffects.cpp
		clientsideeffects_test.cpp
		clientsteamcontext.cpp
		colorcorrectionmgr.cpp
		commentary_modelviewer.cpp
		../shared/collisionproperty.cpp
		../shared/death_pose.cpp
		../shared/debugoverlay_shared.cpp
		../shared/decals.cpp
		detailobjectsystem.cpp
		dummyproxy.cpp
		../shared/effect_dispatch_data.cpp
		EffectsClient.cpp
		../shared/ehandle.cpp
		../shared/entitylist_base.cpp
		entityoriginmaterialproxy.cpp
		../shared/EntityParticleTrail_Shared.cpp
		../shared/env_detail_controller.cpp
		../shared/env_wind_shared.cpp
		../shared/eventlist.cpp
		flashlighteffect.cpp
		../shared/func_ladder.cpp
		functionproxy.cpp
		fx_blood.cpp
		fx_cube.cpp
		fx_explosion.cpp
		fx_fleck.cpp
		fx_impact.cpp
		fx_interpvalue.cpp
		fx_quad.cpp
		fx_shelleject.cpp
		fx_staticline.cpp
		fx_tracer.cpp
		fx_trail.cpp
		fx_water.cpp
		../shared/gamemovement.cpp
		../shared/gamerules.cpp
		../shared/gamerules_register.cpp
		../shared/GameStats.cpp
		../shared/gamestringpool.cpp
		gametrace_client.cpp
		../shared/gamevars_shared.cpp
		glow_outline_effect.cpp
		glow_overlay.cpp
		../shared/hintmessage.cpp
		../shared/hintsystem.cpp
		hltvcamera.cpp
		hud.cpp
		hud_animationinfo.cpp
		hud_basechat.cpp
		hud_basetimer.cpp
		hud_bitmapnumericdisplay.cpp
		hud_closecaption.cpp
		hud_crosshair.cpp
		hud_element_helper.cpp
		hl2/hud_filmdemo.cpp
		hl2/hud_hdrdemo.cpp
		hud_hintdisplay.cpp
		hud_msg.cpp
		hud_numericdisplay.cpp
		hud_pdump.cpp
		hud_redraw.cpp
		hud_vehicle.cpp
		../shared/igamesystem.cpp
		in_camera.cpp
		in_joystick.cpp
		in_main.cpp
		initializer.cpp
		interpolatedvar.cpp
		IsNPCProxy.cpp
		lampbeamproxy.cpp
		lamphaloproxy.cpp
		../shared/mapentities_shared.cpp
		mathproxy.cpp
		matrixproxy.cpp
		menu.cpp
		message.cpp
		movehelper_client.cpp
		../shared/movevars_shared.cpp
		../shared/multiplay_gamerules.cpp
		../shared/obstacle_pushaway.cpp
		panelmetaclassmgr.cpp
		particle_collision.cpp
		particle_litsmokeemitter.cpp
		../shared/particle_parse.cpp
		../shared/particle_property.cpp
		particle_proxies.cpp
		particle_simple3d.cpp
		particlemgr.cpp
		particles_attractor.cpp
		particles_ez.cpp
		particles_localspace.cpp
		particles_new.cpp
		particles_simple.cpp
		../shared/particlesystemquery.cpp
		perfvisualbenchmark.cpp
		physics.cpp
		physics_main_client.cpp
		../shared/physics_main_shared.cpp
		../shared/physics_saverestore.cpp
		../shared/physics_shared.cpp
		physpropclientside.cpp
		playerandobjectenumerator.cpp
		playerspawncache.cpp
		../shared/point_bonusmaps_accessor.cpp
		../shared/point_posecontroller.cpp
		../shared/precache_register.cpp
		../shared/predictableid.cpp
		prediction.cpp
		../shared/predictioncopy.cpp
		../shared/props_shared.cpp
		proxyentity.cpp
		ProxyHealth.cpp
		proxyplayer.cpp
		proxypupil.cpp
		ragdoll.cpp
		../shared/ragdoll_shared.cpp
		recvproxy.cpp
		basepresence.cpp
		../shared/rope_helpers.cpp
		../shared/saverestore.cpp
		../shared/sceneentity_shared.cpp
		ScreenSpaceEffects.cpp
		../shared/sequence_Transitioner.cpp
		simple_keys.cpp
		../shared/simtimer.cpp
		../shared/singleplay_gamerules.cpp
		../shared/SoundEmitterSystem.cpp
		../shared/soundenvelope.cpp
		../../public/SoundParametersInternal.cpp
		splinepatch.cpp
		../shared/Sprite.cpp
		spritemodel.cpp
		../shared/SpriteTrail.cpp
		../shared/studio_shared.cpp
		studio_stats.cpp
		../shared/takedamageinfo.cpp
		../shared/teamplay_gamerules.cpp
		../shared/teamplayroundbased_gamerules.cpp
		../shared/test_ehandle.cpp
		text_message.cpp
		texturescrollmaterialproxy.cpp
		timematerialproxy.cpp
		toggletextureproxy.cpp
		../shared/usercmd.cpp
		../shared/usermessages.cpp
		../shared/util_shared.cpp
		../shared/vehicle_viewblend_shared.cpp
		vgui_avatarimage.cpp
		vgui_basepanel.cpp
		vgui_bitmapbutton.cpp
		vgui_bitmapimage.cpp
		vgui_bitmappanel.cpp
		vgui_schemevisualizer.cpp
		vgui_centerstringpanel.cpp
		vgui_consolepanel.cpp
		vgui_debugoverlaypanel.cpp
		vgui_fpspanel.cpp
		vgui_game_viewport.cpp
		vgui_grid.cpp
		vgui_int.cpp
		vgui_loadingdiscpanel.cpp
		vgui_messagechars.cpp
		vgui_netgraphpanel.cpp
		vgui_slideshow_display_screen.cpp
		view.cpp
		view_beams.cpp
		view_effects.cpp
		view_scene.cpp
		viewangleanim.cpp
		ViewConeImage.cpp
		viewdebug.cpp
		viewpostprocess.cpp
		viewrender.cpp
		../shared/voice_banmgr.cpp
		../shared/voice_status.cpp
		warp_overlay.cpp
		WaterLODMaterialProxy.cpp
		../shared/weapon_parse.cpp
		weapon_selection.cpp
		weapons_resource.cpp
		WorldDimsProxy.cpp
		vgui_video.cpp
		vgui_video_player.cpp
		../shared/mp_shareddefs.cpp
		../client/c_vote_controller.cpp
		../../public/haptics/haptic_msgs.cpp
		../client/touch.cpp

        # pch shit
        ../../public/bone_setup.cpp
        ../../public/posedebugger.cpp
        ../../public/client_class.cpp
        ../../common/compiledcaptionswap.cpp
        ../../public/collisionutils.cpp
        ../../public/crtmemdebug.cpp
        ../../public/dt_recv.cpp
        ../../public/dt_utlvector_common.cpp
        ../../public/dt_utlvector_recv.cpp
        ../../public/filesystem_helpers.cpp
        ../../public/interpolatortypes.cpp
        ../../game/shared/interval.cpp
        ../../common/language.cpp
        ../../public/networkvar.cpp
        ../../common/randoverride.cpp
        ../../public/rope_physics.cpp
        ../../public/scratchpad3d.cpp
        ../../public/ScratchPadUtils.cpp
        ../../public/sentence.cpp
        ../../game/shared/sheetsimulator.cpp
        ../../public/simple_physics.cpp
        ../../public/stringregistry.cpp
        ../../public/studio.cpp
        ../../public/vallocator.cpp
        ../../public/vgui_controls/vgui_controls.cpp
        ../../public/jigglebones.cpp
        hud_lcd.cpp
        in_mouse.cpp
        mumble.cpp
        ../../public/renamed_recvtable_compat.cpp
        rendertexture.cpp
        stdafx.cpp

        # game_controls
        game_controls/baseviewport.cpp
        game_controls/basemodelpanel.cpp
        game_controls/basemodelpanel.h
        game_controls/basemodel_panel.cpp
        game_controls/basemodel_panel.h
        game_controls/ClientScoreBoardDialog.cpp
        game_controls/commandmenu.cpp
        game_controls/intromenu.cpp
        game_controls/MapOverview.cpp
        game_controls/NavProgress.cpp
        game_controls/SpectatorGUI.cpp
        game_controls/teammenu.cpp
        game_controls/vguitextwindow.cpp
        game_controls/IconPanel.cpp

        # mp3
        mp3player.cpp

        # tool framework
        ../../public/tools/bonelist.cpp
        entity_client_tools.cpp
        toolframework_client.cpp

        # sixense shit
        sixense/in_sixense.cpp
        sixense/in_sixense_gesture_bindings.cpp
        ../shared/sixense/sixense_convars.cpp

        # replay stuff
        # replay/replaycamera.cpp
		# replay/cdll_replay.cpp
		# replay/gamedefs.cpp
		# replay/replay_ragdoll.cpp
		# replay/replay_screenshot.cpp
		# replay/replayperformanceplaybackhandler.cpp
		# replay/replayrenderer.cpp
		# replay/replayvideo.cpp
		# replay/genericclassbased_replay.cpp
		# doesn't exist?
		# ../shared/replay_gamestats_shared.cpp
        # replay/vgui/replaybrowserbasepage.cpp
        # replay/vgui/replaybrowserbasepanel.cpp
        # replay/vgui/replayconfirmquitdlg.cpp
        # replay/vgui/replaybrowserdetailspanel.cpp
        # replay/vgui/replaybrowseritemmanager.cpp
        # replay/vgui/replaybrowserlistitempanel.cpp
        # replay/vgui/replaybrowserlistpanel.cpp
        # replay/vgui/replaybrowsermainpanel.cpp
        # replay/vgui/replaybrowsermovieplayerpanel.cpp
        # replay/vgui/replaybrowserpreviewpanel.cpp
        # replay/vgui/replaybrowserrenderdialog.cpp
        # replay/vgui/replayinputpanel.cpp
        # replay/vgui/replaymessagepanel.cpp
        # replay/vgui/replayperformanceeditor.cpp
        # replay/vgui/replayperformancesavedlg.cpp
        # replay/vgui/replayrenderoverlay.cpp
        # replay/vgui/replayreminderpanel.cpp
        # game_controls/slideshowpanel.cpp
        # ../../common/movieobjects/timeutils.cpp
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
    install(TARGETS client DESTINATION ${GAME_BIN_DIR})
endif()