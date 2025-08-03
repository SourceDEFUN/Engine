A love letter to Source Engine and Valve Software.

## What's changed
* waifu renamed to waf
* Hammer's INFDEV Linux support

## What to expect
* Utilities port to Linux
* [SDL3 upgrade](https://gitlab.com/defun/Engine/tree/SDL3) (almost done with the exception of gamepads, double click, auto StartTyping, mouse filter bug, probably microphones and small VGUI2)
* Native Vulkan instead of OpenGL/DirectX
* Replacement of proprietary technology with open-source alternatives (this includes most of Valve technology, sources of which are not published in Source SDK)
* Global shader
* Better graphics (like Deferred lighting and POM and PBR and and)
* Improve VRAD and make it use SYCL instead of just CPU
### Perhaps...
* Hammer's full Linux support (don't expect it, though...)
* Map's Input/Output system replaced with Python scripting
* Add support for Mesh-based maps
* Organize folders

## Code Cleanup days
In these days, i try to remove as much lines of code that wouldn't be used
today as possible.

* **Total days wasted**: 4 (~34 hours)
* **Total Removed lines**: 206361
* **Removed stuff**: or atleast i think so...
    * VProf/Telemetry
    * Xbox
    * PS3