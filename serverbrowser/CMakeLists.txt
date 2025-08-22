cmake_minimum_required(VERSION 4.0)
project(serverbrowser)
add_library(ServerBrowser SHARED
        BaseGamesPage.cpp
#		BlacklistedServers.cpp
#		CustomGames.cpp
		DialogAddServer.cpp
		DialogGameInfo.cpp
		DialogServerPassword.cpp
		FavoriteGames.cpp
#		FriendsGames.cpp
		HistoryGames.cpp
		InternetGames.cpp
		LanGames.cpp
		ModList.cpp
		ServerBrowser.cpp
		ServerBrowserDialog.cpp
		ServerContextMenu.cpp
		ServerListCompare.cpp
#		SpectateGames.cpp
		VACBannedConnRefusedDialog.cpp
		QuickListPanel.cpp
		../public/vgui_controls/vgui_controls.cpp
		../common/ServerBrowser/blacklisted_server_manager.cpp
		../public/tier0/memoverride.cpp
)

target_compile_definitions(ServerBrowser PUBLIC SERVERBROWSER_EXPORTS=1 VERSION_SAFE_STEAM_API_INTERFACES GAME_SRC=1)

add_dependencies(ServerBrowser tier0 vgui_controls mathlib tier1 tier2 tier3 vstdlib steam_api)
target_link_libraries(ServerBrowser PUBLIC tier0 vgui_controls mathlib tier1 tier2 tier3 vstdlib steam_api)

install(TARGETS ServerBrowser DESTINATION bin)