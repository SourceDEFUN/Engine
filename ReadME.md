# SourceDEFUN

Information from [wikipedia](https://wikipedia.org/wiki/Source_(game_engine)):

Source code is based on 2018 leak of CS:GO and "Source 2013". Don't use it for commercial purposes.

This project is using waf buildsystem. If you have waf-related questions look https://waf.io/book

## Features
### Inherited
- [X] Supports Android, macOS, FreeBSD, windows, Linux (glibc, musl)
- [X] Arm support (except windows)
- [X] 64 bits support
- [X] Supports Modern toolchains
- [X] Lots of fixes
- [X] Touchscreen support (even on windows/Linux/macOS)
- [X] VTF 7.5 support
- [X] Physically Based Rendering support
- [X] Supports BSP versions 19-21 (21 support is partial)
- [X] Supports MDL versions 46-49
- [X] Removed useless/unnecessary dependencies
- [X] Achivement system working without steam
- [X] Fixed many bugs
- [X] Serverbrowser works without steam
### defun
- [X] SDL3 support ([Input partially works](https://gitlab.com/defun/engine/-/issues/1))
- [ ] Fresh viewmodel bob
- [ ] Increase map size limits
- [ ] Get rid of useless stuff like telemetry
- [ ] Replace proprietary code with open source solutions
- [ ] Deferred lighting/shading
- [ ] Port some utilities to Linux and get them interface!
### ooh... Good luck with that!
take the following with grain of salt, as some of those might never get realized
- [ ] Replace VGUI2 with RmlUI/Custom GUI
- [ ] FMOD support
- [ ] Vulkan support
- [ ] Change VMT syntax!
- [ ] Replace VTF with PNG/WEBP!
- [ ] Get rid of brushed and convert to mesh-based world (May require next feature)!!
- [ ] Replace MDL with GLB and BSP with GLTF (Requires previous feature)!!!
- [ ] **Replace Hammer's UI with GTK4 and PORT TO LINUX!!!!**


## Building instructions
### Linux
#### Packages (For Debian distributions)
* Install `python3 libsdl3-dev libfreetype6-dev libfontconfig1-dev libopenal-dev libjpeg-dev libpng-dev libcurl4-openssl-dev libbz2-dev libedit-dev`.
If you want a voice chat support, install `libopus-dev` and then add `--enable-opus` argument to WAF.

#### Packages (For Arch distributions)
    Install `git python gcc gcc-multilib sdl3 freetype2 fontconfig zlib bzip2 libjpeg libpng curl openal opus`.
    For 32 bit install `lib32-gcc-libs lib32-sdl3 lib32-freetype2 lib32-fontconfig lib32-zlib lib32-bzip2 lib32-libjpeg lib32-libpng lib32-curl lib32-openal lib32-opus`

#### Compile and run
1. Execute `./waf.py configure -T release/debug` (choose one of the release or debug!). In case of errors inspect what went wrong and try to solve it.
2. After configuration is done successfully, run `./waf.py build` and wait for it to compile and link. In case of errors, you can try:
   * Revert latest commit
   * Wait for the next one, or...
   * Grab a stable source code release from "Releases", when available.
3. We will now proceed to put them in a structure similar to all of the Source Engine games. Write in terminal `./waf.py install --destdir=` and then write the path of where you want it to be. Put path around quotes in case it has spaces.
4. Now put your preferred game into the installed path. **DO NOT COPY YOUR PREFERRED GAME "bin" FOLDER'S *.so FILES!**
5. Now go into the installed path, and run "SourceDEFUN".


### FreeBSD (needs contributor!)
Required dependencies

1. Use pkg ins python sdl2 freetype2 fontconfig curl pkgconf openal-soft jpeg-turbo png.
2. Now, Follow instructions for all OS that has label "(needs contributor!)".

### Android (on Linux)
1. Download and extract Android NDK r10e from [here](https://github.com/android/ndk/wiki/Unsupported-Downloads).
2. Download and extract Clang 11 from [GitHub](https://github.com/llvm/llvm-project/releases/download/llvmorg-11.1.0/clang+llvm-11.1.0-x86_64-linux-gnu-ubuntu-16.04.tar.xz) or from [apt.llvm.org](https://apt.llvm.org/).
3. Run `export ANDROID_NDK_HOME="PATH/TO/NDK/android-ndk-r10e"` and `export PATH="PATH/TO/CLANG/bin:$PATH"` or `export PATH="/usr/lib/llvm-11/bin:$PATH"` if you're using llvm.sh.
4. Add to WAF args `--togles --android=armeabi-v7a-hard,host,21`. `armeabi-v7a-hard` can be replaced with `aarch64` for `arm64` build, but you need to add `--64bits` argument.

### macOS (needs contributor!)
#### Preparing

1. Install Xcode frop App Store.
2. Install Xcode build tools with xcode-select --install command.
3. Install HomeBrew.

#### Required dependencies
1. Run brew install sdl2 freetype2 fontconfig pkg-config opus libpng libedit
2. Now, Follow instructions for all OS that has label "(needs contributor!)".


### Windows (needs contributor!)

1. Install MSVC 15.9 and Windows SDK from Visual Studio Installer. Or you can install full version of Visual Studio 2017 and use his MSVC 15.9.
2. Install Python 3 and add it to Path.
3. Build works for some reason only in PowerShell.
4. Now, Follow instructions for all OS that has label "(needs contributor!)".


### For all OS that has label "(needs contributor!)":
1. You need to install Python 3 in order to use a WAF build system.
2. Run `waf.py configure -T release/debug` (choose one of the release or debug!)
3. On windows, run `waf.bat`.
4. If waf says something like `/usr/bin/env: 'python': No such file or directory` use `python3` prefix before `./waf.py`.
5. If you need a 32 bit build add --32bits argument to WAF.

-------------
To compile as Dedicated server, just add `-d`, while configuring engine.



## Support nillerusr
[Contribute to original repo](https://github.com/nillerusr/source-engine)

Donate BTC: bc1qnjq92jj9uqjtafcx2zvnwd48q89hgtd6w8a6na

Donate ETH: 0x5d0D561146Ed758D266E59B56e85Af0b03ABAF46

Donate XMR: 48iXvX61MU24m5VGc77rXQYKmoww3dZh6hn7mEwDaLVTfGhyBKq2teoPpeBq6xvqj4itsGh6EzNTzBty6ZDDevApCFNpsJ
