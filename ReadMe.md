# SourceDEFUN
A love letter to Source Engine and Valve Software. A good faith project based on leaked Source Engine code.

Read more info about SourceDEFUN, why it was created, and features here: [SourceDEFUN's project](https://github.com/orgs/SourceDEFUN/projects/2?pane=info). Project also contains timeline and Secton's implementation logs if you're interested in history of SourceDEFUN.

## Special thanks
* [valberrie](https://github.com/valberrie) - CMake port
* [Maksymilian Wilczyński](https://github.com/maksw2) - For [helping me](https://github.com/SourceDEFUN/OldVersion/commits?author=maksw2) back when i was learning how to code in C++ 😅

## Announcement: Wanted!~
Contributors who have an Apple device with macOS installed to maintain future macOS builds. Windows users should get maintenance from me, but it wouldn't be as frequent. I'm also planning to maintain \*BSD platforms.

> [!NOTE]
> It is not my intention to break platforms support. I also would never buy an Apple device in my life, because i feel very comfortable on Linux 😊.

-------------------------------------------


## Using
Because SourceDEFUN is based off of leaked Source Engine code, you **CAN NOT** use this to create and/or modify games/engine with commercial purposes. Valve Software will have every right to DMCA your commercial project.

### Playing Source Engine games on SourceDEFUN
It is and will be possible. However, playing games with 20th Anniversary updates will be partially compatible, as Valve Software has updated the shaders. SourceDEFUN *will not* be compatible with that any time soon.


## Building
SourceDEFUN no longer uses [Valve Project Creator](https://developer.valvesoftware.com/wiki/Valve_Project_Creator) in favor of CMake. WAF is planned to be removed together with VPC as soon as CMake compiles SourceDEFUN with no problems.

### Prerequisites
1. Create a folder with any name and move into it (this is because CMake will install the build there)
2. Clone SourceDEFUN
3. Install [CMake](https://cmake.org/) or [Python](https://www.python.org/) (3; for WAF)
4. Install SDL3, Opus, OpenSSL, [TODO] with your preferred package manager.

Choose the game you want to build.
* On CMake: `hl2` `episodic` (more soon!)
* On WAF: `hl2` `hl2mp` `hl1` `episodic` `portal` `hl1mp` `cstrike` `dod`

### CMake (all platforms)
> [!WARNING]
> CMake building is experimental. Currently you can not load maps and VGUI2 just refuses to work properly for reasons i couldn't find. I'll fix map launching as soon as i'll port RmlUI.

Configure, Generate, Build and Install. No big deal.
I also recommend using CMake GUI frontend to change options easily, like which game to build.

### macOS & \*BSD
Wanted!

### Android
[TODO]

### Postrequisites
Put your builded game's assets into the Build folder (`Engine/../Build/`). 

For example, Half-Life 2:
1. Install Half-Life 2 on Steam, then switch to `steam_legacy` "beta" branch.
2. Once it finishes downloading, copy `hl2` and `platform` folders into the Build folder.

The final result should look something like this (future subject to change):
* My SourceDEFUN
    * Build
        * bin
        * hl2
        * platform
    * Engine (this)
    * Tools (in future, some utilities would be separate)

---
---
*Half-Life, the Half-Life logo, the Lambda logo and Source are trademarks and/or registered trademarks of Valve Software. All other trademarks are property of their respective owners. SourceDEFUN and Secton are not affiliated with Valve Software*