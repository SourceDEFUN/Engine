cmake_minimum_required(VERSION 4.0)
project(gameui)
add_library(GameUI SHARED
        BackgroundMenuButton.cpp
		BasePanel.cpp
		GameConsole.cpp
		GameUI_Interface.cpp
		ModInfo.cpp
		MouseMessageForwardingPanel.cpp
		../common/GameUI/ObjectList.cpp
		PanelListPanel.cpp
		RunGameEngine.cpp
		../common/GameUI/scriptobject.cpp
		Sys_Utils.cpp
		TextEntryBox.cpp
		TGAImagePanel.cpp
		../public/vgui_controls/vgui_controls.cpp
		VGuiSystemModuleLoader.cpp
		BonusMapsDatabase.cpp
		../common/language.cpp
		../common/imageutils.cpp
		SaveGameBrowserDialog.cpp
		gameui_util.cpp
		BitmapImagePanel.cpp
		CommandCheckButton.cpp
		CvarNegateCheckButton.cpp
		../common/GameUI/cvarslider.cpp
		CvarTextEntry.cpp
		CvarToggleCheckButton.cpp
		HapticControlBox.cpp
		KeyToggleCheckButton.cpp
		LabeledCommandComboBox.cpp
		URLButton.cpp
		vcontrolslistpanel.cpp
		BenchmarkDialog.cpp
		BonusMapsDialog.cpp
		CommentaryDialog.cpp
		CommentaryExplanationDialog.cpp
		ContentControlDialog.cpp
		CustomTabExplanationDialog.cpp
		GameConsoleDialog.cpp
		LoadGameDialog_Xbox.cpp
		LoadGameDialog.cpp
		MultiplayerAdvancedDialog.cpp
		NewGameDialog.cpp
		PlayerListDialog.cpp
		SaveGameDialog_Xbox.cpp
		SaveGameDialog.cpp
		LoadCommentaryDialog.cpp
		LoadingDialog.cpp
		BaseSaveGameDialog.cpp
		CreateMultiplayerGameBotPage.cpp
		CreateMultiplayerGameDialog.cpp
		CreateMultiplayerGameGameplayPage.cpp
		CreateMultiplayerGameServerPage.cpp
		OptionsDialog_Xbox.cpp
		ControllerDialog.cpp
		matchmaking/achievementsdialog.cpp
		matchmaking/basedialog.cpp
		matchmaking/dialogmenu.cpp
		matchmaking/leaderboarddialog.cpp
		matchmaking/matchmakingbasepanel.cpp
		matchmaking/pausedialog.cpp
		matchmaking/sessionlobbydialog.cpp
		matchmaking/sessionoptionsdialog.cpp
		matchmaking/sessionbrowserdialog.cpp
		matchmaking/welcomedialog.cpp
		OptionsDialog.cpp
		OptionsSubAudio.cpp
		OptionsSubDifficulty.cpp
		OptionsSubGame.cpp
		OptionsSubKeyboard.cpp
		OptionsSubMouse.cpp
		OptionsSubTouch.cpp
		OptionsSubMultiplayer.cpp
		OptionsSubPortal.cpp
		OptionsSubVideo.cpp
		OptionsSubVoice.cpp
		../public/tier0/memoverride.cpp
)

target_compile_definitions(GameUI PUBLIC GAMEUI_EXPORTS=1 NO_STEAM=1 VERSION_SAFE_STEAM_API_INTERFACES=1)
target_include_directories(GameUI PUBLIC ./ ../thirdparty ../common/GameUI)

add_dependencies(GameUI tier0 tier1 tier2 tier3 vstdlib vgui_controls vtf bitmap mathlib steam_api matsys_controls)
target_link_libraries(GameUI PUBLIC tier0 tier1 tier2 tier3 vstdlib vgui_controls vtf bitmap mathlib steam_api matsys_controls SDL3 jpeg png z)

if(WIN32)
    target_sources(GameUI PUBLIC LogoFile.cpp ChangeGameDialog.cpp OptionsSubHaptics.cpp)
endif()

install(TARGETS GameUI DESTINATION bin)