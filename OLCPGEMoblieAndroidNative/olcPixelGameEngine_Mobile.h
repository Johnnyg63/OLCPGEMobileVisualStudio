
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region license_and_help 
/*
	olcPixelGameEngine_Mobile.h

	//////////////////////////////////////////////////////////////////
	// Beta Release 2.1.0, Not to be used for Production software   //
	// John Galvin aka Johnngy63: 18-July-2023                      //
	// Removed ASensor_getHandle() as it only supports SDK 29       //
	//and higher. Updated project to support SDK 21 to SDK32        //
	// Please report all bugs to https://discord.com/invite/WhwHUMV //
	// Or on Github: https://github.com/Johnnyg63					//
	//////////////////////////////////////////////////////////////////

	+-------------------------------------------------------------+
	|           OneLoneCoder Pixel Game Engine Mobile v2.00       |
	|  "What do you need? Pixels... Lots of Pixels..." - javidx9
	|	"Well now you have those pixels on Android/iOS" - Johnngy63
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	olc::PixelGameEngine is a single file, cross platform graphics and user-input
	framework used for games, visualisations, algorithm exploration and learning.
	It was developed by YouTuber "javidx9" as an assistive tool for many of his
	videos. The goal of this project is to provide high speed graphics with
	minimal project setup complexity, to encourage new programmers, younger people,
	and anyone else that wants to make fun things.

	However, olc::PixelGameEngine is not a toy! It is a powerful and fast utility
	capable of delivering high resolution, high speed, high quality applications
	which behave the same way regardless of the operating system or platform.

	This file provides the core utility set of the olc::PixelGameEngine, including
	window creation, keyboard/mouse input, main game thread, timing, pixel drawing
	routines, image/sprite loading and drawing routines, and a bunch of utility
	types to make rapid development of games/visualisations possible.


	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2023 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions or derivations of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce the above
	copyright notice. This list of conditions and the following	disclaimer must be
	reproduced in the documentation and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors may
	be used to endorse or promote products derived from this software without specific
	prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
				https://www.youtube.com/javidx9extra
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com
	Patreon:	https://www.patreon.com/javidx9
	Community:  https://community.onelonecoder.com



	Compiling in Linux
	~~~~~~~~~~~~~~~~~~
	You will need a modern C++ compiler, so update yours!
	To compile use the command:

	g++ -o YourProgName YourSource.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

	On some Linux configurations, the frame rate is locked to the refresh
	rate of the monitor. This engine tries to unlock it but may not be
	able to, in which case try launching your program like this:

	vblank_mode=0 ./YourProgName



	Compiling in Code::Blocks on Windows
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Well I wont judge you, but make sure your Code::Blocks installation
	is really up to date - you may even consider updating your C++ toolchain
	to use MinGW32-W64.

	Guide for installing recent GCC for Windows:
	https://www.msys2.org/
	Guide for configuring code::blocks:
	https://solarianprogrammer.com/2019/11/05/install-gcc-windows/
	https://solarianprogrammer.com/2019/11/16/install-codeblocks-gcc-windows-build-c-cpp-fortran-programs/

	Add these libraries to "Linker Options":
	user32 gdi32 opengl32 gdiplus Shlwapi dwmapi stdc++fs

	Set these compiler options: -std=c++17



	Compiling on Mac - EXPERIMENTAL! PROBABLY HAS BUGS
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Yes yes, people use Macs for C++ programming! Who knew? Anyway, enough
	arguing, thanks to Mumflr the PGE is now supported on Mac. Now I know nothing
	about Mac, so if you need support, I suggest checking out the instructions
	here: https://github.com/MumflrFumperdink/olcPGEMac

	clang++ -arch x86_64 -std=c++17 -mmacosx-version-min=10.15 -Wall -framework OpenGL
		-framework GLUT -framework Carbon -lpng YourSource.cpp -o YourProgName



	Compiling with Emscripten (New & Experimental)
	~~~~~~~~~~~~~~~~~~~~~~~~~
	Emscripten compiler will turn your awesome C++ PixelGameEngine project into WASM!
	This means you can run your application in teh browser, great for distributing
	and submission in to jams and things! It's a bit new at the moment.

	em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 ./YourSource.cpp -o pge.html



	Using stb_image.h
	~~~~~~~~~~~~~~~~~
	The PGE will load png images by default (with help from libpng on non-windows systems).
	However, the excellent "stb_image.h" can be used instead, supporting a variety of
	image formats, and has no library dependence - something we like at OLC studios ;)
	To use stb_image.h, make sure it's in your code base, and simply:

	#define OLC_IMAGE_STB

	Before including the olcPixelGameEngine.h header file. stb_image.h works on many systems
	and can be downloaded here: https://github.com/nothings/stb/blob/master/stb_image.h



	Multiple cpp file projects?
	~~~~~~~~~~~~~~~~~~~~~~~~~~~
	As a single header solution, the OLC_PGE_APPLICATION definition is used to
	insert the engine implementation at a project location of your choosing.
	The simplest way to setup multifile projects is to create a file called
	"olcPixelGameEngine.cpp" which includes the following:

	#define OLC_PGE_APPLICATION
	#include "olcPixelGameEngine.h"

	That's all it should include. You can also include PGEX includes and
	defines in here too. With this in place, you do not need to
	#define OLC_PGE_APPLICATION anywhere, and can simply include this
	header file as an when you need to.



	Ports
	~~~~~
	olc::PixelGameEngine has been ported and tested with varying degrees of
	success to: WinXP, Win7, Win8, Win10, Various Linux, Raspberry Pi,
	Chromebook, PlayStation Portable (PSP) and Nintendo Switch. If you are
	interested in the details of these ports, come and visit the Discord!



	Thanks
	~~~~~~
	I'd like to extend thanks to Ian McKay, Bispoo, Eremiell, slavka, Kwizatz77, gurkanctn, Phantim,
	IProgramInCPP, JackOJC, KrossX, Huhlig, Dragoneye, Appa, JustinRichardsMusic, SliceNDice,
	dandistine,	Ralakus, Gorbit99, raoul, joshinils, benedani, Moros1138, Alexio, SaladinAkara
	& MagetzUb for advice, ideas and testing, and I'd like to extend my appreciation to the
	250K YouTube followers,	80+ Patrons, 4.8K Twitch followers and 10K Discord server members
	who give me	the motivation to keep going with all this :D

	Significant Contributors: @Moros1138, @SaladinAkara, @MaGetzUb, @slavka,
							  @Dragoneye, @Gorbit99, @dandistine & @Mumflr

	Special thanks to those who bring gifts!
	GnarGnarHead.......Domina
	Gorbit99...........Bastion, Ori & The Blind Forest, Terraria, Spelunky 2, Skully
	Marti Morta........Gris
	Danicron...........Terraria
	SaladinAkara.......Aseprite, Inside, Quern: Undying Thoughts, Outer Wilds
	AlterEgo...........Final Fantasy XII - The Zodiac Age
	SlicEnDicE.........Noita, Inside
	TGD................Voucher Gift
	Dragoneye..........Lucas Arts Adventure Game Pack
	Anonymous Pirate...Return To Monkey Island

	Special thanks to my Patrons too - I wont name you on here, but I've
	certainly enjoyed my tea and flapjacks :D



	Author: OLC Pixel Game Engine 2.0
	~~~~~~
	David Barr, aka javidx9, (c) OneLoneCoder 2023

	Author@ OLC Pixel Game Engine 2.0 Mobile Port
	~~~~~~
	John Galvin, aka Johnngy63, (c) OneLoneCoder 2023
*/
#pragma endregion 
/*
	olcPixelGameEngine_mobile.h

	+-------------------------------------------------------------+
	|           OneLoneCoder Pixel Game Engine v2.0 Mobile        |
	|  "What do you need? Pixels... Lots of Pixels..." - javidx9  |
	|  "Well now you have pixels, and lots of them on Android/iOS |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	olc::PixelGameEngine is a single file, cross platform graphics and user-input
	framework used for games, visualisations, algorithm exploration and learning.
	It was developed by YouTuber "javidx9" as an assistive tool for many of his
	videos. The goal of this project is to provide high speed graphics with
	minimal project setup complexity, to encourage new programmers, younger people,
	and anyone else that wants to make fun things.

	However, olc::PixelGameEngine is not a toy! It is a powerful and fast utility
	capable of delivering high resolution, high speed, high quality applications
	which behave the same way regardless of the operating system or platform.

	This file provides the core utility set of the olc::PixelGameEngine, including
	window creation, keyboard/mouse input, main game thread, timing, pixel drawing
	routines, image/sprite loading and drawing routines, and a bunch of utility
	types to make rapid development of games/visualisations possible.


	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2023 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions or derivations of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce the above
	copyright notice. This list of conditions and the following	disclaimer must be
	reproduced in the documentation and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors may
	be used to endorse or promote products derived from this software without specific
	prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
				https://www.youtube.com/javidx9extra
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com
	Patreon:	https://www.patreon.com/javidx9
	Community:  https://community.onelonecoder.com



	Compiling in Linux
	~~~~~~~~~~~~~~~~~~
	TODO: Update CMake
	You will need a modern C++ compiler, so update yours!
	To compile use the command:

	g++ -o YourProgName YourSource.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

	On some Linux configurations, the frame rate is locked to the refresh
	rate of the monitor. This engine tries to unlock it but may not be
	able to, in which case try launching your program like this:

	vblank_mode=0 ./YourProgName



	Compiling in Code::Blocks on Windows
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Not Supported in olc Pixel Game Engine 2.0 Mobile

	Compiling in Android
	~~~~~~~~~~~~~~~~~~~~
	Android Support only use the project templates on GitHub
	TODO: Add GitHub Links

	Compiling in iOS (Coming Soon...)
	~~~~~~~~~~~~~~~~~~~~
	iOS Support only use the project templates on GitHub
	TODO: Add GitHub Links


	Compiling with Emscripten (New & Experimental)
	~~~~~~~~~~~~~~~~~~~~~~~~~
	Not supported in olc Pixel Game Engine 2.0 Mobile


	Using stb_image.h
	~~~~~~~~~~~~~~~~~
	The PGE will load png images by default (with help from libpng on non-windows systems).
	However, the excellent "stb_image.h" can be used instead, supporting a variety of
	image formats, and has no library dependence - something we like at OLC studios ;)
	To use stb_image.h, make sure it's in your code base, and simply:

	#define OLC_IMAGE_STB

	We use stb_image.h so the same code can be ran on both Android & iOS, using the Native methods
	makes the code to complex and messy. KISS (Keep It Simple Stupid)

	Before including the olcPixelGameEngine_mobile.h header file. stb_image.h works on many systems
	and can be downloaded here: https://github.com/nothings/stb/blob/master/stb_image.h



	Multiple cpp file projects?
	~~~~~~~~~~~~~~~~~~~~~~~~~~~
	As a single header solution, the OLC_PGE_APPLICATION definition is used to
	insert the engine implementation at a project location of your choosing.
	The simplest way to setup multifile projects is to create a file called
	"olcPixelGameEngine.cpp" which includes the following:

	#define OLC_PGE_APPLICATION
	#include "olcPixelGameEngine_mobile.h"

	That's all it should include. You can also include PGEX includes and
	defines in here too. With this in place, you do not need to
	#define OLC_PGE_APPLICATION anywhere, and can simply include this
	header file as an when you need to.



	Ports
	~~~~~
	olc::PixelGameEngine has been ported and tested with varying degrees of
	success to: WinXP, Win7, Win8, Win10, Various Linux, Raspberry Pi,
	Chromebook, PlayStation Portable (PSP), Nintendo Switch, Android and iOS
	If you are interested in the details of these ports, come and visit the Discord!



	Thanks
	~~~~~~
	I'd like to extend thanks to Ian McKay, Bispoo, Eremiell, slavka, Kwizatz77, gurkanctn, Phantim,
	IProgramInCPP, JackOJC, KrossX, Huhlig, Dragoneye, Appa, JustinRichardsMusic, SliceNDice,
	dandistine,	Ralakus, Gorbit99, raoul, joshinils, benedani, Moros1138, Alexio, SaladinAkara
	& MagetzUb for advice, ideas and testing, and I'd like to extend my appreciation to the
	250K YouTube followers,	80+ Patrons, 4.8K Twitch followers and 10K Discord server members
	who give me	the motivation to keep going with all this :D

	Significant Contributors: @Moros1138, @SaladinAkara, @MaGetzUb, @slavka,
							  @Dragoneye, @Gorbit99, @dandistine & @Mumflr

	Special thanks to those who bring gifts!
	GnarGnarHead.......Domina
	Gorbit99...........Bastion, Ori & The Blind Forest, Terraria, Spelunky 2, Skully
	Marti Morta........Gris
	Danicron...........Terraria
	SaladinAkara.......Aseprite, Inside, Quern: Undying Thoughts, Outer Wilds
	AlterEgo...........Final Fantasy XII - The Zodiac Age
	SlicEnDicE.........Noita, Inside
	TGD................Voucher Gift
	Dragoneye..........Lucas Arts Adventure Game Pack
	Anonymous Pirate...Return To Monkey Island

	Special thanks to my Patrons too - I wont name you on here, but I've
	certainly enjoyed my tea and flapjacks :D



	Author
	~~~~~~
	David Barr, aka javidx9, (c) OneLoneCoder 2023

	Author OlC Pixel Game Engine 2.0 port to mobile (Android/iOS) (c) OneLoneCoder 2023
	~~~~~~
	John Galvin, aka Johnngy63
*/

#pragma region version_history
/*
	2.01: BETA Port code from olcPixelGameEngine.h to olcPixelGameEngine_mobile.h
	2.02: Corrected support for X86
	2.03: Update EventManager to handle, Touch, Mouse and Keyboard events
	2.04: Corrected Touch offset, added 1 touch point, unlinked Mouse & Touch Events
	2.05: Sensors Support added
	2.06: Multi Touch Support
	2.06a: Basic mouse support for Android Emulator
	2.07: Updated SIMD_SSE for Intel Atom devices, Updated GetTouch() to default to touch point zero when no touch piont selected
	2.08: Added ClearTouchPoints(int8_t startIndex = 0) for clearing of touch points at index x, some bug fixes too
	2.09: Added: FileManager: for gaining acccess to the Andriod Assets APK and iOS Zip Packages
				+ app_LoadFileFromAssets()
				+ app_ExtractFileFromAssets()
				+ app_GetInternalAppStorage()
				+ app_GetExternalAppStorage()
				+ app_GetPublicAppStorage()

				++ SmartPtr filehandler->
				++ LoadFileFromAssets()
				++ ExtractFileFromAssets()
				++ GetInternalAppStorage()
				++ GetExternalAppStorage()
				++ GetPublicAppStorage()
	2.10: Removed ASensor_getHandle() as it only supports SDK 29 and higher. Updated project to support SDK 21 to SDK32. Thank you @VasCoder :)

	!! Apple Platforms will not see these updates immediately !!
	!! Starting on iOS port ASAP    !!
*/
#pragma endregion

#pragma region hello_world_example
// O------------------------------------------------------------------------------O
// | Example "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O
/*

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		// Name your application
		sAppName = "BETA Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}

	void OnSaveStateRequested() override
	{
		// Save State
	}

	void OnRestoreStateRequested() override
	{
		// Restore state
	}
};

void android_main(struct android_app* initialstate)
{
	Example demo;
	if (demo.Construct(1280, 720, 4, 4))
		demo.Start();
	return 0;
}

*/
#pragma endregion
#pragma GCC diagnostic pop
// Start of the Engine
#ifndef OLC_PGE_DEF
#define OLC_PGE_DEF	

#define PGE_MOB_VER 210

// O------------------------------------------------------------------------------O
// | COMPILER CONFIGURATION ODDITIES                                              |
// O------------------------------------------------------------------------------O
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region compiler_config

#define UNUSED(x) (void)(x)

#pragma endregion
#pragma GCC diagnostic pop

// O------------------------------------------------------------------------------O
// | STANDARD INCLUDES                                                            |
// O------------------------------------------------------------------------------O
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region std_includes
/*
	Header files, these will not match with the full PGE

*/
#include <cstdio>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <array>
#include <atomic>
#include <thread>
#include <memory>
#include <fstream>

#pragma endregion
#pragma GCC diagnostic pop

/*
	We only support Android (min ver 23 -> 32) and iOS (8 - 15)
	however new versions of Android (33 example) and iOS are backward compatible within the range above
	you might get a message warning you tho when debugging.

	Like everything for mobile devices this is a cut down version of the full PGE
	olcPixelGameEngine_Mobile support OpenGLES 2.0 -> OpenGLES 3.0, however please note simulators do not support OpenGLES 3.0
	Therefore there is code in the CreateDevice that will auto change the supported version when a simulator is been used
	There are some restrictions when using OpenGLES, such as there is no hint GL_STREAM_DRAW, only GL_STATIC_DRAW & GL_DYNAMIC_DRAW
	that is ok as long as we do not enter the code for GL_STREAM_DRAW (0x88E0)... oh wait we did, that caught me out for a while
	therefore any direct code calling will now be replaced with their respective const value or nearest too:
	0x88E0 moved to 0x88E4 called out as GL_STATIC_DRAW
	0x8892 --> called out as GL_ARRAY_BUFFER

	Lets KISS it first (KISS -> Keep It Simple Stupid)
	Finally... there maybe a little to much commenting here, again we can we clean it up later

*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region test_code
/*
	Default test code, used to ensure everything is still works
	Do not delete. Can be removed when moved to production
	This code is used for the iOS project, just forget about it for the moment
*/

void PGE_MOB_setupGL(double width, double height);
void PGE_MOB_tearDownGL();
void PGE_MOB_update();
void PGE_MOB_prepare();
void PGE_MOB_draw();

#pragma endregion
#pragma GCC diagnostic pop

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INTERFACE DECLARATION                                     |
// O------------------------------------------------------------------------------O
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region pge_declaration
namespace olc {
	class PixelGameEngine;
	class Sprite;

	// Pixel Game Engine Advanced Configuration
	constexpr uint8_t  nMouseButtons = 5;
	constexpr uint8_t  nDefaultAlpha = 0xFF;
	constexpr uint32_t nDefaultPixel = (nDefaultAlpha << 24);
	constexpr uint8_t  nTabSizeInSpaces = 4;
	constexpr size_t OLC_MAX_VERTS = 128;
	enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };

	// O------------------------------------------------------------------------------O
	// | olc::Pixel - Represents a 32-Bit RGBA colour                                 |
	// O------------------------------------------------------------------------------O
	struct Pixel
	{
		union
		{
			uint32_t n = nDefaultPixel;
			struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
		};

		enum Mode { NORMAL, MASK, ALPHA, CUSTOM };

		Pixel();
		Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = nDefaultAlpha);
		Pixel(uint32_t p);
		Pixel& operator = (const Pixel& v) = default;
		bool   operator ==(const Pixel& p) const;
		bool   operator !=(const Pixel& p) const;
		Pixel  operator * (const float i) const;
		Pixel  operator / (const float i) const;
		Pixel& operator *=(const float i);
		Pixel& operator /=(const float i);
		Pixel  operator + (const Pixel& p) const;
		Pixel  operator - (const Pixel& p) const;
		Pixel& operator +=(const Pixel& p);
		Pixel& operator -=(const Pixel& p);
		Pixel  operator * (const Pixel& p) const;
		Pixel& operator *=(const Pixel& p);
		Pixel  inv() const;
	};

	Pixel PixelF(float red, float green, float blue, float alpha = 1.0f);
	Pixel PixelLerp(const olc::Pixel& p1, const olc::Pixel& p2, float t);


	// O------------------------------------------------------------------------------O
	// | USEFUL CONSTANTS                                                             |
	// O------------------------------------------------------------------------------O
	static const Pixel
		GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
		RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
		YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
		GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
		CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
		BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
		MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
		WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);

	// Thanks to scripticuk and others for updating the key maps
	// NOTE: The GLUT platform will need updating, open to contributions ;)
	enum Key
	{
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		UP, DOWN, LEFT, RIGHT,
		SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
		BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
		NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
		NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
		EQUALS, COMMA, MINUS,
		OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
		CAPS_LOCK, ENUM_END
	};

	namespace Mouse
	{
		static constexpr int32_t LEFT = 0;
		static constexpr int32_t RIGHT = 1;
		static constexpr int32_t MIDDLE = 2;
	};

	// O------------------------------------------------------------------------------O
	// | olc::HWButton - Represents the state of a hardware button (mouse/key/joy)    |
	// O------------------------------------------------------------------------------O
	struct HWButton
	{
		bool bPressed = false;	// Set once during the frame the event occurs
		bool bReleased = false;	// Set once during the frame the event occurs
		bool bHeld = false;		// Set true for all frames between pressed and released events
	};

	// Supported Sensors Types
	// Do not edit :)
	enum SensorType
	{
		/**
		* Invalid sensor type.
		*/
		ASENSOR_TYPE_INVALID = -1,

		/**
		 * reporting-mode: continuous
		 *
		 *  All values are in SI units (m/s^2) and measure the acceleration of the
		 *  device minus the force of gravity.
		 */
		ASENSOR_TYPE_ACCELEROMETER = 1,

		/**
		 * reporting-mode: continuous
		 *
		 *  All values are in micro-Tesla (µT) and measure the geomagnetic
		 *  field in the X, Y and Z axis.
		 */
		ASENSOR_TYPE_MAGNETIC_FIELD = 2,

		/**
		 * reporting-mode: continuous
		 *
		 *  All values are in degrees and measure the geomagnetic
		 *  field in the X, Y and Z axis.
		 */
		ASENSOR_TYPE_ORIENTATION = 3,

		/**
		 * reporting-mode: continuous
		 *
		 *  All values are in radians/second and measure the rate of rotation
		 *  around the X, Y and Z axis.
		 */
		ASENSOR_TYPE_GYROSCOPE = 4,

		/**
		 * reporting-mode: on-change
		 *
		 * The light sensor value is returned in SI lux units.
		 */
		ASENSOR_TYPE_LIGHT = 5,

		/**
		 * reporting-mode: on-change
		 *
		 * The pressure sensor value is returned in hPa (millibar).
		 */
		ASENSOR_TYPE_PRESSURE = 6,

		/**
		 * reporting-mode: on-change
		 *
		 * The proximity sensor which turns the screen off and back on during calls is the
		 * wake-up proximity sensor. Implement wake-up proximity sensor before implementing
		 * a non wake-up proximity sensor. For the wake-up proximity sensor set the flag
		 * SENSOR_FLAG_WAKE_UP.
		 * The value corresponds to the distance to the nearest object in centimeters.
		 */
		ASENSOR_TYPE_PROXIMITY = 8,

		/**
		 * reporting-mode: continous
		 *
		 * All values are in SI units (m/s^2) and measure the direction and
		 * magnitude of gravity. When the device is at rest, the output of
		 * the gravity sensor should be identical to that of the accelerometer.
		 */
		ASENSOR_TYPE_GRAVITY = 9,

		/**
		 * reporting-mode: continuous
		 *
		 *  All values are in SI units (m/s^2) and measure the acceleration of the
		 *  device not including the force of gravity.
		 */
		ASENSOR_TYPE_LINEAR_ACCELERATION = 10,

		/**
		 * reporting-mode: continous
		 *
		 * The rotation vector represents the orientation of the device as a combination of an angle and
		 * an axis, in which the device has rotated through an angle θ around an axis (x, y, z).
		 */
		ASENSOR_TYPE_ROTATION_VECTOR = 11,

		/**
		 * reporting-mode: on-change
		 *
		 * The relative humidity sensor value is returned in percent.
		 */
		ASENSOR_TYPE_RELATIVE_HUMIDITY = 12,

		/**
		 * reporting-mode: on-change
		 *
		 * The ambient temperature sensor value is returned in Celcius.
		 */
		ASENSOR_TYPE_AMBIENT_TEMPERATURE = 13,

		/**
		 * reporting-mode: continuous
		 *
		 *  All values are in micro-Tesla (µT) and measure the uncalibrated geomagnetic
		 *  field in the X, Y and Z axis.
		 */
		ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED = 14,

		/**
		 * reporting-mode: continuous
		 *
		 * Identical to SensorType.RotationVector except that it doesn't use the geomagnetic field.
		 * Therefore the Y axis doesn't point north, but instead to some other reference,
		 * that reference is allowed to drift by the same order of magnitude as the gyroscope drift around the Z axis.
		 */
		ASENSOR_TYPE_GAME_ROTATION_VECTOR = 15,

		/**
		 *  reporting-mode: continuous
		 *
		 *  All values are in radians/second and measure the rate of uncalibrated rotation
		 *  around the X, Y and Z axis.
		 */
		ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED = 16,

		/**
		 * reporting-mode: continuous
		 *
		 * All values are in SI units (m/s^2) and measure the acceleration of the device minus the force of gravity.
		 * NOTE: If not supported used Accelerometer
		 */
		ASENSOR_TYPE_SIGNIFICANT_MOTION = 17,

		/**
		 * reporting-mode: on-change
		 *
		 * Fires when steps are detected
		 * NOTE: Mostly supported by Android Watch
		 */
		ASENSOR_TYPE_STEP_DETECTOR = 18,

		/**
		 * reporting-mode: continuous
		 *
		 * Number of steps detected per sample rate
		 * NOTE: Mostly supported by Android Watch
		 */
		ASENSOR_TYPE_STEP_COUNTER = 19,

		/**
		 * reporting-mode: continuous
		 * All values are in radians/second and measure the rate of rotation around the X, Y and Z axis.
		 */
		ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR = 20,

		/**
		 * reporting-mode: on-change
		 *
		 * Number of beats per sample rate
		 * NOTE: Mostly supported by Android Watch
		 */
		ASENSOR_TYPE_HEART_RATE = 21,

		/**
		 * reporting-mode: continous
		 * 6D Pose Estimation using RGB refers to the task of determining the six degree-of-freedom (6D) pose of an object in 3D space based on RGB images.
		 * This involves estimating the position and orientation of an object in a scene, and is a fundamental problem in computer vision and robotics.
		 */
		ASENSOR_TYPE_POSE_6DOF = 28,

		/**
		* reporting-mode: on-change
		*
		*Fires when Stationary Detected
		* NOTE: Mostly supported by Android Watch
		*/
		ASENSOR_TYPE_STATIONARY_DETECT = 29,

		/**
		 * reporting-mode: on-change
		 *
		 * Fires when Motion Detected
		 */
		ASENSOR_TYPE_MOTION_DETECT = 30,

		/**
		 * reporting-mode: continuous
		 *  Number of heart beats per sample rate
		 */
		ASENSOR_TYPE_HEART_BEAT = 31,

		/**
		 * SPECIAL CASE.
		 *
		 */
		ASENSOR_TYPE_ADDITIONAL_INFO = 33,

		/**
		 * reporting-mode: on-change
		 *
		 * A sensor of this type returns an event every time the device transitions from off-body to on-body and from on-body to off-body (e.g. a wearable device being removed from the wrist would trigger an event indicating an off-body transition).
		 * The event returned will contain a single value to indicate off-body state:
		 * 1.0 (device is on-body) 0.0 (device is off - body)
		 */
		ASENSOR_TYPE_LOW_LATENCY_OFFBODY_DETECT = 34,

		/**
		 * reporting-mode: continuous
		 *
		 *  Uncalibrated values are in SI units (m/s^2) and measure the acceleration of the device minus the force of gravity.
		 */
		ASENSOR_TYPE_ACCELEROMETER_UNCALIBRATED = 35,

		/**
		 * reporting-mode: on-change
		 *
		 * The hinge angle sensor value is returned in degrees.
		 */
		ASENSOR_TYPE_HINGE_ANGLE = 36,

	};

	/**
	* Sensor accuracy measure.
	*/
	enum SensorStatus {
		/** no contact */
		ASENSOR_STATUS_NO_CONTACT = -1,
		/** unreliable */
		ASENSOR_STATUS_UNRELIABLE = 0,
		/** low accuracy */
		ASENSOR_STATUS_ACCURACY_LOW = 1,
		/** medium accuracy */
		ASENSOR_STATUS_ACCURACY_MEDIUM = 2,
		/** high accuracy */
		ASENSOR_STATUS_ACCURACY_HIGH = 3
	};

	/**
	 * Sensor Reporting Modes.
	 */
	enum SensorReportingMode {
		/** invalid reporting mode */
		AREPORTING_MODE_INVALID = -1,
		/** continuous reporting */
		AREPORTING_MODE_CONTINUOUS = 0,
		/** reporting on change */
		AREPORTING_MODE_ON_CHANGE = 1,
		/** on shot reporting */
		AREPORTING_MODE_ONE_SHOT = 2,
		/** special trigger reporting */
		AREPORTING_MODE_SPECIAL_TRIGGER = 3
	};

	struct SensorInformation
	{
		const char* Name;
		const char* Vendor;
		olc::SensorType Type;
		float Resolution;
		int MinDelay;
		int FifoMaxEventCount;
		int FifoReservedEventCount;
		const char* GetStringType;
		olc::SensorReportingMode ReportingMode;
		bool isWakeUpSensor;
		int Handle;
	};

	/// <summary>
	/// OLC Phone Sensors
	/// Enable Sensor before used using EnableSensor(SENSORTYPE, SampleRate ms)
	/// Ensure Sensor is supported before calling
	/// See: https://developer.android.com/reference/android/hardware/SensorEvent.html#values
	/// </summary>
	struct olcSensors
	{
		/// <summary>
		/// All values are in SI units (m/s^2) and measure the acceleration of the device minus the force of gravity.
		/// </summary>
		ASensorVector Accelerometer;

		/// <summary>
		/// All values are in micro-Tesla (uT) and measure the geomagnetic field in the X, Y and Z axis.
		/// </summary>
		ASensorVector MagniticField;

		/// <summary>
		/// All values are in degrees and measure the geomagnetic field in the X, Y and Z axis.
		/// </summary>
		ASensorVector Orientation;

		/// <summary>
		/// All values are in radians/second and measure the rate of rotation around the X, Y and Z axis.
		/// </summary>
		ASensorVector Gyroscope;

		/// <summary>
		/// The light sensor value is returned in SI lux units.
		/// </summary>
		float Light;

		/// <summary>
		/// The pressure sensor value is returned in hPa (millibar).
		/// </summary>
		float Pressure;

		/// <summary>
		/// The proximity sensor which turns the screen off and back on during calls is the
		/// wake - up proximity sensor.Implement wake - up proximity sensor before implementing
		/// a non wake - up proximity sensor.For the wake - up proximity sensor set the flag
		/// SENSOR_FLAG_WAKE_UP.
		/// The value corresponds to the distance to the nearest object in centimeters.
		/// </summary>
		float* Proximity;

		/// <summary>
		/// All values are in SI units (m/s^2) and measure the direction and
		/// magnitude of gravity.When the device is at rest, the output of
		/// the gravity sensor should be identical to that of the accelerometer.
		/// </summary>
		ASensorVector Gravity;

		/// <summary>
		/// All values are in SI units (m/s^2) and measure the acceleration of the
		/// device not including the force of gravity.
		/// </summary>
		ASensorVector LinearAcceleration;

		/// <summary>
		/// The rotation vector represents the orientation of the device as a combination of an angle and
		/// an axis, in which the device has rotated through an angle θ around an axis (x, y, z).
		/// </summary>
		ASensorVector RotationVector;

		/// <summary>
		/// The relative humidity sensor value is returned in percent.
		/// </summary>
		float RelativeHumidity;

		/// <summary>
		/// The ambient temperature sensor value is returned in Celcius.
		/// </summary>
		float AmbientTemperature;

		/// <summary>
		/// Uncalibrated values are in micro-Tesla (uT) and measure the geomagnetic field in the X, Y and Z axis.
		/// </summary>
		AUncalibratedEvent Uncalibrated_MagniticField;

		/// <summary>
		/// Identical to SensorType.RotationVector except that it doesn't use the geomagnetic field.
		/// Therefore the Y axis doesn't point north, but instead to some other reference, 
		/// that reference is allowed to drift by the same order of magnitude as the gyroscope drift around the Z axis.
		/// </summary>
		ASensorVector GameRotation;

		/// <summary>
		/// Uncalibrated values are in radians/second and measure the rate of rotation around the X, Y and Z axis.
		/// </summary>
		AUncalibratedEvent Uncalibrated_Gyroscope;

		/// <summary>
		/// All values are in SI units (m/s^2) and measure the acceleration of the device minus the force of gravity.
		/// NOTE: If not supported used Accelerometer
		/// </summary>
		ASensorVector SignificantMotion;

		/// <summary>
		/// Fires when steps are detected
		/// NOTE: Mostly supported by Android Watch
		/// </summary>
		float* StepDetector;

		/// <summary>
		/// Number of steps detected per sample rate
		/// NOTE: Mostly supported by Android Watch
		/// </summary>
		float* StepCounter;

		/// <summary>
		/// All values are in radians/second and measure the rate of rotation around the X, Y and Z axis.
		/// </summary>
		ASensorVector GeomagneticRotationVector;

		/// <summary>
		/// Number of beats per sample rate
		/// NOTE: Mostly supported by Android Watch
		/// </summary>
		AHeartRateEvent HeartRate;

		/// <summary>
		/// 6D Pose Estimation using RGB refers to the task of determining the six degree-of-freedom (6D) pose of an object in 3D space based on RGB images. 
		/// This involves estimating the position and orientation of an object in a scene, and is a fundamental problem in computer vision and robotics.
		/// </summary>
		ASensorVector Pose_6D;

		/// <summary>
		/// Fires when Stationary Detected
		/// NOTE: Mostly supported by Android Watch
		/// </summary>
		float* StationaryDetect;

		/// <summary>
		///  Fires when Motion Detected
		/// </summary>
		float* MotionDetect;

		/// <summary>
		/// Number of heart beats per sample rate
		/// </summary>
		float* HeartBeat;

		// Special Case
		// TODO:ASENSOR_TYPE_ADDITIONAL_INFO

		/// <summary>
		/// A sensor of this type returns an event every time the device transitions from off-body to on-body and from on-body to off-body (e.g. a wearable device being removed from the wrist would trigger an event indicating an off-body transition). 
		/// The event returned will contain a single value to indicate off-body state: 
		/// 1.0 (device is on-body) 0.0 (device is off - body)
		/// </summary>
		float* LowLatencyOffBodyDetect;

		/// <summary>
		/// Uncalibrated values are in SI units (m/s^2) and measure the acceleration of the device minus the force of gravity.
		/// WARNING: Enable Sensor before used using EnableSensor(SENSORTYPE, SampleRate ms)
		/// </summary>
		AUncalibratedEvent Uncalibrated_Accelerometer;

		/// <summary>
		/// Hinge in degress
		/// </summary>
		float* HingeAngle;








	};



	// O------------------------------------------------------------------------------O
	// | olc::vX2d - A generic 2D vector type                                         |
	// O------------------------------------------------------------------------------O
#if !defined(OLC_IGNORE_VEC2D)
	template <class T>
	struct v2d_generic
	{
		T x = 0;
		T y = 0;
		v2d_generic() : x(0), y(0) {}
		v2d_generic(T _x, T _y) : x(_x), y(_y) {}
		v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
		v2d_generic& operator=(const v2d_generic& v) = default;
		T mag() const { return T(std::sqrt(x * x + y * y)); }
		T mag2() const { return x * x + y * y; }
		v2d_generic  norm() const { T r = 1 / mag(); return v2d_generic(x * r, y * r); }
		v2d_generic  perp() const { return v2d_generic(-y, x); }
		v2d_generic  floor() const { return v2d_generic(std::floor(x), std::floor(y)); }
		v2d_generic  ceil() const { return v2d_generic(std::ceil(x), std::ceil(y)); }
		v2d_generic  max(const v2d_generic& v) const { return v2d_generic(std::max(x, v.x), std::max(y, v.y)); }
		v2d_generic  min(const v2d_generic& v) const { return v2d_generic(std::min(x, v.x), std::min(y, v.y)); }
		v2d_generic  cart() { return { std::cos(y) * x, std::sin(y) * x }; }
		v2d_generic  polar() { return { mag(), std::atan2(y, x) }; }
		v2d_generic  clamp(const v2d_generic& v1, const v2d_generic& v2) const { return this->max(v1)->min(v2); }
		v2d_generic	 lerp(const v2d_generic& v1, const double t) { return this->operator*(T(1.0 - t)) + (v1 * T(t)); }
		T dot(const v2d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
		T cross(const v2d_generic& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
		v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
		v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
		v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs); }
		v2d_generic  operator *  (const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
		v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs); }
		v2d_generic  operator /  (const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }
		v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
		v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
		v2d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
		v2d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
		v2d_generic& operator *= (const v2d_generic& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
		v2d_generic& operator /= (const v2d_generic& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
		v2d_generic  operator +  () const { return { +x, +y }; }
		v2d_generic  operator -  () const { return { -x, -y }; }
		bool operator == (const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
		bool operator != (const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
		const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
		friend std::ostream& operator << (std::ostream& os, const v2d_generic& rhs) { os << rhs.str(); return os; }
		operator v2d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
		operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
		operator v2d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
	};

	// Note: joshinils has some good suggestions here, but they are complicated to implement at this moment, 
	// however they will appear in a future version of PGE
	template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y));
	}
	template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y));
	}
	template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y));
	}
	template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y));
	}
	template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y));
	}
	template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y));
	}

	// To stop dandistine crying...
	template<class T, class U> inline bool operator < (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
	{
		return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
	}
	template<class T, class U> inline bool operator > (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
	{
		return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x);
	}

	typedef v2d_generic<int32_t> vi2d;
	typedef v2d_generic<uint32_t> vu2d;
	typedef v2d_generic<float> vf2d;
	typedef v2d_generic<double> vd2d;
#endif


	// O------------------------------------------------------------------------------O
	// | olc::ResourcePack - A virtual scrambled filesystem to pack your assets into  |
	// O------------------------------------------------------------------------------O

	/// <summary>
	/// Not Implemented 
	/// </summary>
	class ResourcePack {
	public:
		ResourcePack();
		~ResourcePack();

		/// <summary>
		/// Add a file to your resource pact
		/// </summary>
		/// <param name="sFile">full file path</param>
		/// <returns>True: Success, False: Fail </returns>
		bool AddFile(const std::string& sFile);

		/// <summary>
		/// Load a file from your resource pack
		/// </summary>
		/// <param name="sFile">Full file path</param>
		/// <param name="sKey">String Key</param>
		/// <returns>True: Success, False: Fail/Not found</returns>
		bool LoadPack(const std::string& sFile, const std::string& sKey);

		/// <summary>
		/// Saves a file to your resource pack
		/// </summary>
		/// <param name="sFile">Full file address</param>
		/// <param name="sKey">String key</param>
		/// <returns>True: Success, False: Fail</returns>
		/// 
		bool SavePack(const std::string& sFile, const std::string& sKey);
		//ResourceBuffer GetFileBuffer(const std::string& sFile);

		/// <summary>
		/// Set when resource pack exists and loaded
		/// </summary>
		/// <returns>True: Success, False: Fail</returns>
		bool Loaded();

	private:

		struct sResourceFile { uint32_t nSize; uint32_t nOffset; };
		std::map<std::string, sResourceFile> mapFiles;
		//std::ifstream baseFile;
		//std::vector<char> scramble(const std::vector<char>& data, const std::string& key);
		//std::string makeposix(const std::string& path);
	};


	// O------------------------------------------------------------------------------O
	// | olc::ImageLoader - It loads your images!									  |
	// O------------------------------------------------------------------------------O

	class ImageLoader
	{
	public:
		ImageLoader() = default;
		virtual ~ImageLoader() = default;
		virtual olc::rcode LoadImageResource(olc::Sprite* spr, const std::string& sImageFile, olc::ResourcePack* pack) = 0;
		virtual olc::rcode SaveImageResource(olc::Sprite* spr, const std::string& sImageFile) = 0;

		/// <summary>
		/// Loads the image directly in to the passed buffer. Ensure you clear the buffer after use
		///	This buffer is used mostly with Android / iOS to extract the compressed image from the apk / TBD
		///	You can think of an APK as a very fancy Resource File
		/// </summary>
		/// <param name="spr">Pointer to the sprite</param>
		/// <param name="sImageFile">Image file name, use all lowercase (Android)</param>
		/// <param name="buffer">Vector to load the image into</param>
		/// <returns> FAIL = 0, OK = 1, NO_FILE = -1</returns>
		virtual olc::rcode GetImageBuffer(olc::Sprite* spr, const std::string& sImageFile, std::vector<char>* buffer) = 0;
	};

	/// <summary>
	/// FileHandler allows easy access to the Android/iOS Assests (APK file) and App Storage
	/// </summary>
	class FileHandler
	{
	public:
		FileHandler() = default;
		virtual ~FileHandler() = default;

		enum StorageType
		{
			INTERNAL = 0,
			EXTERNAL,
			PUBLIC
		};

		/// <summary>
		/// Load a file from the Assets APK into the passed buffer
		/// </summary>
		/// <param name="sFilePath">Full file path name excudling the assets dir and leading "/": Example: "images/test.png" "maps/example1.city"</param>
		/// <param name="outbuffer">A pointer to a clear buffer. Buffer will be populated and returned</param>
		/// <returns>FAIL = 0, OK = 1, NO_FILE = -1, and outBuffer</returns>
		virtual olc::rcode LoadFileFromAssets(const std::string& sFilePath, std::vector<char>* outBuffer) = 0;

		/// <summary>
		/// Extracts a compressed file from the assests APK to a depcompressed app storage file
		/// </summary>
		/// <param name="sAssetFilePath">Full assets file path name excudling the assets dir and leading "/": Example: "images/test.png" "maps/example1.city"</param>
		/// <param name="sAppStorageFilePath">Full app storage path. Use GetInternalAppStorage(), GetExteralAppStorage() and GetPublicAppStorage() to get the storage path</param>
		/// <returns>FAIL = 0, OK = 1, NO_FILE = -1,</returns>
		virtual olc::rcode ExtractFileFromAssets(const std::string& sAssetFilePath, const std::string& sAppStorageFilePath) = 0;

		/// <summary>
		/// Get the App Internal storage path where you can save,  editing, deleting files
		/// Internal Storage is private and non volatile
		/// RECOMMANDED: Use this storage for saving, editing, deleting files
		/// </summary>
		/// <returns>The full Android/iOS path to internal storage. FAIL: NULL</returns>
		virtual const char* GetInternalAppStorage() = 0;

		/// <summary>
		/// Get the App Exteral storage where you can save files
		/// WARNING: MAY NOT EXIST. May be volatile
		/// </summary>
		/// <returns>SUCCESS: The full Android/iOS path to external storage. FAIL: NULL</returns>
		virtual const char* GetExteralAppStorage() = 0;

		/// <summary>
		/// Get the App public storage where you can save files
		/// WARNING: MAY NOT EXIST. May be volatile
		/// NOTE: Android will default to the \obb\com.AppName, iOS TBA
		/// </summary>
		/// <returns>SUCCESS: The full Android/iOS path to external storage. FAIL: NULL</returns>
		virtual const char* GetPublicAppStorage() = 0;

	};

	// O------------------------------------------------------------------------------O
	// | olc::Sprite - An image represented by a 2D array of olc::Pixel               |
	// O------------------------------------------------------------------------------O
	class Sprite
	{
	public:
		Sprite();
		Sprite(const std::string& sImageFile, olc::ResourcePack* pack = nullptr);
		Sprite(int32_t w, int32_t h);
		Sprite(const olc::Sprite&) = delete;
		~Sprite();

	public:

		/// <summary>
		/// Loads an image from a file
		/// </summary>
		/// <param name="sImageFile">Image file name</param>
		/// <param name="pack">Optional: Resource Pack Pointer</param>
		/// <returns>FAIL = 0, OK = 1, NO_FILE = -1</returns>
		olc::rcode LoadFromFile(const std::string& sImageFile, olc::ResourcePack* pack = nullptr);

	public:
		int32_t width = 0;								// Sprite width in pixel
		int32_t height = 0;								// Sprite height in pixels
		enum Mode { NORMAL, PERIODIC, CLAMP };			// Sprite Mode
		enum Flip { NONE = 0, HORIZ = 1, VERT = 2 };	// Sprite orientation

	public:

		/// <summary>
		/// Set the Sprite Mode
		/// </summary>
		/// <param name="mode">NORMAL, PERIODIC, CLAMP</param>
		void SetSampleMode(olc::Sprite::Mode mode = olc::Sprite::Mode::NORMAL);

		/// <summary>
		/// Get a pixel at location (X,Y)
		/// </summary>
		/// <param name="x">int32_t x</param>
		/// <param name="y">int32_t x</param>
		/// <returns>Pixel</returns>
		Pixel GetPixel(int32_t x, int32_t y) const;

		/// <summary>
		/// Sets a pixel at location (X,Y)
		/// </summary>
		/// <param name="x">int32_t x</param>
		/// <param name="y">int32_t y</param>
		/// <param name="p">Replace with pixel</param>
		/// <returns>Success: true, Fail: false</returns>
		bool  SetPixel(int32_t x, int32_t y, Pixel p);

		/// <summary>
		/// Get a pixel at location position {x,y}
		/// </summary>
		/// <param name="a">vi2d {x, y}</param>
		/// <returns>Pixel</returns>
		Pixel GetPixel(const olc::vi2d& a) const;

		/// <summary>
		/// Set a pixel at location position {x , y}
		/// </summary>
		/// <param name="a">vi2d {x, y}</param>
		/// <param name="p">Replace with pixel</param>
		/// <returns>Success: true, Fail: false</returns>
		bool  SetPixel(const olc::vi2d& a, Pixel p);

		/// <summary>
		/// Sample a pixel at location (X, Y)
		/// </summary>
		/// <param name="x">float x</param>
		/// <param name="y">float y</param>
		/// <returns>Pixel</returns>
		Pixel Sample(float x, float y) const;

		/// <summary>
		/// Sample a pixel at location position {x , y}
		/// </summary>
		/// <param name="uv">vf2d {x, y}</param>
		/// <returns>Pixel</returns>
		Pixel Sample(const olc::vf2d& uv) const;

		/// <summary>
		/// TODO: What is SampleBL?? a pixel at location (X, Y)
		/// </summary>
		/// <param name="x">float x</param>
		/// <param name="y">float y</param>
		/// <returns>Pixel</returns>
		Pixel SampleBL(float u, float v) const;

		/// <summary>
		/// TODO: What is SampleBL?? a pixel at location position {x , y}
		/// </summary>
		/// <param name="uv">vf2d {x, y}</param>
		/// <returns>Pixel</returns>
		Pixel SampleBL(const olc::vf2d& uv) const;

		/// <summary>
		/// Returns a pointer to vector that contains the pixels from the sprite
		/// </summary>
		/// <returns>Pointer to the internal pColData Vector</returns>
		Pixel* GetData();

		/// <summary>
		/// Creates a new duplicate sprite
		/// </summary>
		/// <returns>A pointer to the new create duplicate sprite</returns>
		olc::Sprite* Duplicate();

		/// <summary>
		/// Creates a new duplicate sub sprite 
		/// </summary>
		/// <param name="vPos">{x, y}</param>
		/// <param name="vSize">{width, height}</param>
		/// <returns>A pointer to the new create duplicate sprite</returns>
		olc::Sprite* Duplicate(const olc::vi2d& vPos, const olc::vi2d& vSize);

		/*-------------- New Methods John Galvin --------------*/

		/// <summary>
		/// Creates a new duplicate sprite flipped.
		/// NOTE: All sprite modifications are now handled by SIMD NEON (ARM, ARM64) and SIMD (x86, x64) automatically under the hood.
		/// All the speed with none of the headache.
		/// </summary>
		/// <param name="flip">NONE = 0, HORIZ = 1, VERT = 2</param>
		/// <returns>A pointer to the new create duplicate sprite</returns>
		olc::Sprite* Duplicate(olc::Sprite::Flip flip);

		/// <summary>
		/// Creates a new duplicate sprite flipped. 
		/// NOTE: All sprite modifications are now handled by SIMD NEON (ARM, ARM64) and SIMD (x86, x64) automatically under the hood. 
		/// All the speed with none of the headache.
		/// NOTE: New scale code coming soon.  
		/// </summary>
		/// <param name="scale">Cannot be less that 1</param>
		/// <returns>A pointer to the new create duplicate sprite</returns>
		olc::Sprite* Duplicate(uint32_t scale);

		/// <summary>
		/// Merges this Sprite into another Sprite and returns a new Sprite, based on the merge pixel
		/// NOTE: All sprite modifications are now handled by SIMD NEON (ARM, ARM64) and SIMD (x86, x64) automatically under the hood
		/// All the speed with none of the headache
		/// </summary>
		/// <param name="vTargetPos">Start Position with in the target Sprite to merge</param>
		/// <param name="pTargetSprite">A pointer to the Target Sprite</param>
		/// <param name="p">Blend Pixel, default Alpha (PNG)</param>
		/// <returns>A pointer to the new created merge Sprite</returns>
		olc::Sprite* DuplicateMerge(const olc::vi2d& vTargetPos, olc::Sprite* pTargetSprite, olc::Pixel p = olc::BLANK);

		/*-------------- END New Methods John Galvin --------------*/


		olc::vi2d Size() const;				// Size of Sprite
		std::vector<olc::Pixel> pColData;	// Stores the pixels 
		Mode modeSample = Mode::NORMAL;		// Same Mode

		static std::unique_ptr<olc::ImageLoader> loader;	// Unique pointer to the image loader


		// Sub Sprites Stuff
	private:

		uint32_t maxSubSprites = 20;		// MAX num of sub sprites an Sprite can store
		bool bIsSubSpritesFull = false;

	public:

		/// <summary>
		/// Stores sub sprites that are created during runtime, if 'Store Sub Sprites' is enabled. 
		/// vecSubSprites.push_back({vStartPos, vSize, scale, flip, pDrawTarget, id, pSubSprite, Decal});
		/// </summary>
		std::vector<std::tuple<olc::vi2d, olc::vi2d, uint32_t, uint8_t, Sprite*, size_t, Sprite*, void* >> vecSubSprites;

		/// <summary>
		/// Returns if the Sub Sprites vector is full
		/// </summary>
		/// <returns>Full: true, Still have Space: false</returns>
		bool IsSubSpritesFull();

		/// <summary>
		/// Returns the max number of sub sprites this sprite can store.
		/// Default: 20
		/// </summary>
		/// <returns>Disabled: 0, Count: (> 0)</returns>
		uint32_t GetMaxSubSprite();

		/// <summary>
		/// Set the maximum number of sub sprites this sprite can store.
		/// Set to 0 to disable sub sprites. Default: 20.
		/// </summary>
		/// <param name="max">Number of sub sprites</param>
		void SetMaxSubSpriteCount(uint32_t max);

		/// <summary>
		/// Clears all sub sprites and resets the sub sprites vector
		/// </summary>
		void ClearSubSprites();

		/// <summary>
		/// Clears all sub sprites from position start
		/// </summary>
		/// <param name="start">Start position</param>
		void ClearSubSprites(size_t start);

		/// <summary>
		/// Clears all sub sprites from position start to position end
		/// </summary>
		/// <param name="start">Start position</param>
		/// <param name="end">End position, if end position is greater that then size of the vector. The size of the vector is used</param>
		void ClearSubSprites(size_t start, size_t end);

		/// <summary>
		/// Stores a sprite in the Sub Sprites vector if it does not exist
		/// </summary>
		/// <param name="pSubSprite">A pointer to the sprite to be stored</param>
		/// <param name="vStartPos">Partial Sprite Start position, (Default {0,0})</param>
		/// <param name="scale">Scaler value (>= 1) (Default 1)</param>
		/// <param name="flip">olc::Sprite::NONE.. HORIZ.. VERT; (default NONE)</param>
		/// <returns>Success: True, Fail: false, usually means sub sprites are disabled</returns>
		bool StoreSubSprite(olc::Sprite* pSubSprite, olc::vi2d vStartPos = { 0, 0 }, uint32_t scale = 1,
			olc::Sprite::Flip flip = olc::Sprite::NONE, olc::Sprite* pDrawTarget = nullptr);

		/// <summary>
		/// Gets the Sub Sprite by ID
		/// </summary>
		/// <param name="id">The id value in the vector</param>
		/// <returns>A pointer to a sprite, nullptr if not exist</returns>
		olc::Sprite* GetStoredSubSprite(size_t id);

		/// <summary>
		/// Gets the ID of the sprite in the vector
		/// </summary>
		/// <param name="pSubSprite">A pointer to the Sub Sprite</param>
		/// <returns>Returns the ID, -1 if not exist</returns>
		size_t GetStoredSubSprite_id(olc::Sprite* pSubSprite);

		/// <summary>
		/// Gets a stored sub sprite from the Stored Sub Sprite Vector
		/// </summary>
		/// <param name="vStartPos">Start position (x,y)</param>
		/// <param name="vSize">Size (width, height)</param>
		/// <param name="scale">Scaler (>=1) (Default 1)</param>
		/// <param name="flip">olc::Sprite::NONE.. HORIZ.. VERT; (Default NONE)</param>
		/// <param name="pMergeFromSprite">Used solely for merging of sprites (Default nullptr)</param>
		/// <returns>A pointer to a sprite, nullptr if not exist</returns>
		olc::Sprite* GetStoredSubSprite(olc::vi2d vStartPos, olc::vi2d vSize, uint32_t scale = 1, olc::Sprite::Flip flip = olc::Sprite::NONE,
			olc::Sprite* pDrawTarget = nullptr);

		/// <summary>
		/// Gets a stored sub decal from the Stored Sub Sprite Vector
		/// </summary>
		/// <param name="vStartPos">Start position (x,y)</param>
		/// <param name="vSize">Size (width, height)</param>
		/// <param name="scale">Scaler (>=1)</param>
		/// <param name="flip">olc::Sprite::NONE.. HORIZ.. VERT; (Default NONE)</param>
		/// <param name="pDrawTarget">The pointer to the Sprite</param>
		/// <returns>A pointer to a decal, nullptr if not exist</returns>
		void* GetStoredSubDecal(olc::vi2d vStartPos, olc::vi2d vSize, uint32_t scale = 1, olc::Sprite::Flip flip = olc::Sprite::NONE,
			olc::Sprite* pDrawTarget = nullptr);


	};

	// O------------------------------------------------------------------------------O
	// | olc::Decal - A GPU resident storage of an olc::Sprite                        |
	// O------------------------------------------------------------------------------O
	class Decal
	{
	public:
		Decal(olc::Sprite* spr, bool filter = false, bool clamp = true);
		Decal(const uint32_t nExistingTextureResource, olc::Sprite* spr);
		virtual ~Decal();

		/// <summary>
		/// Updates the Decal
		/// </summary>
		void Update();

		/// <summary>
		/// Updates the Decal with any Sprite changes
		/// </summary>
		void UpdateSprite();

	public: // But do not touch
		int32_t id = -1;						// Sprite id
		olc::Sprite* sprite = nullptr;			// Sprite pointer
		olc::vf2d vUVScale = { 1.0f, 1.0f };	// Sprite vUV Scale
	};

	/// <summary>
	/// Decal Mode options
	/// </summary>
	enum class DecalMode
	{
		NORMAL,
		ADDITIVE,
		MULTIPLICATIVE,
		STENCIL,
		ILLUMINATE,
		WIREFRAME,
		MODEL3D,
	};

	/// <summary>
	/// Decal Structure Options
	/// </summary>
	enum class DecalStructure
	{
		LINE,
		FAN,
		STRIP,
		LIST
	};

	// O------------------------------------------------------------------------------O
	// | olc::Renderable - Convenience class to keep a sprite and decal together      |
	// O------------------------------------------------------------------------------O
	class Renderable
	{
	public:
		Renderable() = default;
		Renderable(Renderable&& r) : pSprite(std::move(r.pSprite)), pDecal(std::move(r.pDecal)) {}
		Renderable(const Renderable&) = delete;
		olc::rcode Load(const std::string& sFile, ResourcePack* pack = nullptr, bool filter = false, bool clamp = true);
		void Create(uint32_t width, uint32_t height, bool filter = false, bool clamp = true);
		olc::Decal* Decal() const;
		olc::Sprite* Sprite() const;

	private:
		std::unique_ptr<olc::Sprite> pSprite = nullptr;
		std::unique_ptr<olc::Decal> pDecal = nullptr;
	};


	// O------------------------------------------------------------------------------O
	// | Auxiliary components internal to engine                                     |
	// O------------------------------------------------------------------------------O

	/// <summary>
	/// Decal Instance Struct
	/// </summary>
	struct DecalInstance
	{
		olc::Decal* decal = nullptr;
		std::vector<olc::vf2d> pos;
		std::vector<olc::vf2d> uv;
		std::vector<float> w;
		std::vector<olc::Pixel> tint;
		olc::DecalMode mode = olc::DecalMode::NORMAL;
		olc::DecalStructure structure = olc::DecalStructure::FAN;
		uint32_t points = 0;
	};

	/// <summary>
	/// Layer Description Struct
	/// </summary>
	struct LayerDesc
	{
		olc::vf2d vOffset = { 0, 0 };
		olc::vf2d vScale = { 1, 1 };
		bool bShow = false;
		bool bUpdate = false;
		olc::Renderable pDrawTarget;
		uint32_t nResID = 0;
		std::vector<DecalInstance> vecDecalInstance;
		olc::Pixel tint = olc::WHITE;
		std::function<void()> funcHook = nullptr;
	};

#ifdef __ANDROID__

	/// <summary>
	/// Android Engine Struct
	/// </summary>
	struct OSEngineInstance
	{
		struct android_app* app;	// Allows access to Android OS App
		int animating = 0;			// Set to 0 when app is pause, else 1
		bool StartPGE = false;		// Set to true when it is safe to start the PGE Engine
		bool LostFocus = false;		// Is set when the app has lost focus but is not paused by the OS
		EGLDisplay display;			// OpenGLES Display
		EGLSurface surface;			// OpenGLES Surface
		EGLContext context;			// OpenGLES Context
		int32_t viewWidth = 0;		// Width of the viewable Rectangle
		int32_t viewHeight = 0;		// Height of the viewable Rectangle
		int32_t screenWidth = 0;	// Width of the phone screen
		int32_t screenHeight = 0;	// Height of the phone screen


		void* lastGameState = nullptr;		// A pointer to your save state struct

		// Coming Soon....
		ASensorManager* sensorManager;

		/// <summary>
		/// Tuple Vector for os Sensors: { OS Const Type, Pointer to ASenor Struct, sample rate ms}
		/// </summary>
		std::vector<std::tuple<olc::SensorType, const ASensor*, uint32_t>> deviceSensors;
		ASensorEventQueue* sensorEventQueue;


	};



#endif // __Andriod__

#ifdef __APPLE__
	/// <summary>
	/// Apple iOS Engine Struct
	/// </summary>
	struct OSEngineInstance
	{
		int animating;
		int32_t width;
		int32_t height;
	};

	class iOSEngine
	{
		// TBA
	};
#endif // __Andriod__

	/// <summary>
	/// Class Renderer used to your pixels to the screen
	/// </summary>
	class Renderer
	{
	public:
		virtual ~Renderer() = default;
		virtual void       PrepareDevice() = 0;
		virtual olc::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
		virtual olc::rcode DestroyDevice() = 0;
		virtual void       DisplayFrame() = 0;
		virtual void       PrepareDrawing() = 0;
		virtual void	   SetDecalMode(const olc::DecalMode& mode) = 0;
		virtual void       DrawLayerQuad(const olc::vf2d& offset, const olc::vf2d& scale, const olc::Pixel tint) = 0;
		virtual void       DrawDecal(const olc::DecalInstance& decal) = 0;
		virtual uint32_t   CreateTexture(const uint32_t width, const uint32_t height, const bool filtered = false, const bool clamp = true) = 0;
		virtual void       UpdateTexture(uint32_t id, olc::Sprite* spr) = 0;
		virtual void       ReadTexture(uint32_t id, olc::Sprite* spr) = 0;
		virtual uint32_t   DeleteTexture(const uint32_t id) = 0;
		virtual void       ApplyTexture(uint32_t id) = 0;
		virtual void       UpdateViewport(const olc::vi2d& pos, const olc::vi2d& size) = 0;
		virtual void       ClearBuffer(olc::Pixel p, bool bDepth) = 0;
		static olc::PixelGameEngine* ptrPGE;


	};

	/// <summary>
	/// Class Platform, used to get your game running on the select platform
	/// </summary>
	class Platform
	{
	public:
		virtual ~Platform() = default;

		/// <summary>
		/// Fires when the PGE Engine starts up
		/// </summary>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode ApplicationStartUp() = 0;

		/// <summary>
		/// Fires when the PGE Engine shuts down
		/// </summary>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode ApplicationCleanUp() = 0;

		/// <summary>
		/// Fires when the PGE Engine Thread starts up
		/// </summary>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode ThreadStartUp() = 0;

		/// <summary>
		/// Fires when the PGE Engine thread shuts down
		/// </summary>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode ThreadCleanUp() = 0;

		/// <summary>
		/// Creates the Graphic Interface between PGE and the Mobile OS
		/// </summary>
		/// <param name="bFullScreen">Full Screen mode</param>
		/// <param name="bEnableVSYNC">Enable VSYNC</param>
		/// <param name="vViewPos">{x,y} position of the game view</param>
		/// <param name="vViewSize">{w,h} size if game view</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) = 0;

		/// <summary>
		/// DEPRECATED: Not supported by Mobile OS 
		/// </summary>
		/// <param name="vWindowPos"></param>
		/// <param name="vWindowSize"></param>
		/// <param name="bFullScreen"></param>
		/// <returns>FAIL = 0</returns>
		virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) = 0;

		/// <summary>
		/// DEPRECATED: Not supported by Mobile OS 
		/// </summary>
		/// <param name="s"></param>
		/// <returns>FAIL = 0</returns>
		virtual olc::rcode SetWindowTitle(const std::string& s) = 0;

		/// <summary>
		/// DEPRECATED:Replaced with EventManager
		/// Events are injected into your app, it is not the same as a PC OS
		/// EventManager will handle all events for you
		/// </summary>
		/// <returns>FAIL = 0</returns>
		virtual olc::rcode StartSystemEventLoop() = 0;

		/// <summary>
		/// DEPRECATED:Replaced with EventManager
		/// Events are injected into your app, it is not the same as a PC OS
		/// EventManager will handle all events for you
		/// </summary>
		/// <returns>FAIL = 0</returns>
		virtual olc::rcode HandleSystemEvent() = 0;

		/// <summary>
		/// Static pointer to the PGE, allows the platform to access the PGE
		/// </summary>
		static olc::PixelGameEngine* ptrPGE;


	};

	/// <summary>
	/// Class SIMDDrawRoutines, these classes are used to execute Draw commands via SIMD NEON (ARM, ARM64) and SIMD (x86, x64)
	/// The PGE engine will not automatically, when possible, execute your draw commands via SIMD
	/// </summary>
	class SIMDDrawRoutines
	{
	public:
		virtual ~SIMDDrawRoutines() = default;

		/// <summary>
		/// Clears the draw target to the passed pixel color, (SIMD)
		/// </summary>
		/// <param name="p">Pixel colour</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode Clear_SIMD(Pixel p = olc::BLANK, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Draws a horizontal line only (SIMD)
		/// </summary>
		/// <param name="sx">Start X</param>
		/// <param name="ex">End X</param>
		/// <param name="ny">Position y</param>
		/// <param name="p">Pixel colour</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode DrawFillLine(int sx, int ex, int ny, Pixel p, olc::Sprite* pDrawTarget) = 0;

		/// <summary>
		/// Draws a filled circle (SIMD)
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="radius">Circle radius</param>
		/// <param name="p">Pixel colour</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode FillCircle_SIMD(int32_t x, int32_t y, int32_t radius, Pixel p = olc::WHITE, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Draws a filled triangle (SIMD)
		/// </summary>
		/// <param name="x1">Position x1</param>
		/// <param name="y1">Position y1</param>
		/// <param name="x2">Position x2</param>
		/// <param name="y2">Position y2</param>
		/// <param name="x3">Position x3</param>
		/// <param name="y3">Position y3</param>
		/// <param name="p">Pixel colour</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode FillTriangle_SIMD(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = olc::WHITE, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Draws a fille rectangle (SIMD)
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="w">Rectangle width</param>
		/// <param name="h">Rectangle height</param>
		/// <param name="p">Pixel colour</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode FillRect_SIMD(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = olc::WHITE, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Draws a sprite (SIMD)
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="sprite">Pointer to sprite</param>
		/// <param name="scale">Sprite scale (>=1)</param>
		/// <param name="flip">Sprite Orientation NONE = 0, HORIZ = 1, VERT = 2</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode DrawSprite_SIMD(int32_t x, int32_t y, Sprite* sprite, uint32_t scale = 1, uint8_t flip = olc::Sprite::NONE, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Draws a partial sprite (SIMD)
		/// </summary>
		/// <param name="vPos">Position {x,y}</param>
		/// <param name="pSource">Pointer to source sprite</param>
		/// <param name="vStartPos">Start Position {x1, y1}</param>
		/// <param name="vSize">Size of partial sprite {width, height}</param>
		/// <param name="scale">Sprite scale (>=1)</param>
		/// <param name="flip">Sprite Orientation NONE = 0, HORIZ = 1, VERT = 2</param>
		/// <param name="pDrawTarget">Pointer to draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode DrawPartialSprite_SIMD(const olc::vi2d& vPos, olc::Sprite* pSource, const olc::vi2d& vStartPos, const olc::vi2d& vSize, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Merges the From Sprite into the To Sprite (SIMD)
		/// </summary>
		/// <param name="vPosx">From Sprite Start Position x</param>
		/// <param name="vPosy">From Sprite Start Position y</param>
		/// <param name="pFromSprite">Pointer to the From Sprite</param>
		/// <param name="vToSpritePosx">To Sprite Start Position x</param>
		/// <param name="vToSpritePosy">To Sprite Start Position y</param>
		/// <param name="pToSprite">Pointer to the To Sprite</param>
		/// <param name="blendPixel">Blend Pixel</param>
		/// <param name="scale">Sprite scale (>=1)</param>
		/// <param name="flip">Sprite Orientation NONE = 0, HORIZ = 1, VERT = 2</param>
		/// <param name="pDrawTarget">Pointer to the draw target</param>
		/// <returns>FAIL = 0, OK = 1</returns>
		virtual olc::rcode DrawMergeSprite_SIMD(int32_t vPosx, int32_t vPosy, Sprite* pFromSprite, int32_t vToSpritePosx, int32_t vToSpritePosy, Sprite* pToSprite, Pixel blendPixel = olc::BLANK, uint32_t scale = 1, olc::Sprite::Flip flip = olc::Sprite::NONE, olc::Sprite* pDrawTarget = nullptr) = 0;

		/// <summary>
		/// Duplicates a sprite (SIMD)
		/// </summary>
		/// <param name="pSource">Pointer to the source sprite</param>
		/// <returns>Pointer to a new duplicate sprite</returns>
		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite* pSource) = 0;

		/// <summary>
		/// Creates a duplicate partial sprite (SIMD)
		/// </summary>
		/// <param name="vPos">Start position {x, y}</param>
		/// <param name="vSize">Size {width, height}</param>
		/// <param name="pSource">Pointer to the source sprite</param>
		/// <returns>Pointer to a new duplicate partial sprite</returns>
		virtual olc::Sprite* Duplicate_SIMD(const olc::vi2d& vPos, const olc::vi2d& vSize, olc::Sprite* pSource) = 0;

		/*-------------- New Methods John Galvin --------------*/

		/// <summary>
		/// Creates a duplicate orientation sprite (SIMD)
		/// </summary>
		/// <param name="flip">Sprite Orientation NONE = 0, HORIZ = 1, VERT = 2</param>
		/// <param name="pSource">Pointer to the source sprite</param>
		/// <returns>Pointer to a new duplicate orientation sprite</returns>
		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite::Flip flip, olc::Sprite* pSource) = 0;

		/// <summary>
		/// Creates a duplicate scaled sprite (SIMD)
		/// </summary>
		/// <param name="scale">Scale (>= 1)</param>
		/// <param name="pSource">Pointer to the source sprite</param>
		/// <returns>Pointer to a new duplicate scale sprite</returns>
		virtual olc::Sprite* Duplicate_SIMD(uint32_t scale, olc::Sprite* pSource) = 0;

		/// <summary>
		/// Creates a duplicate merge sprite (SIMD)
		/// </summary>
		/// <param name="vTargetPos">Target start position {x, y}</param>
		/// <param name="pTargetSprite">Pointer to the target sprite</param>
		/// <param name="p">Blend pixel</param>
		/// <param name="pSource">Pointer to the source sprite</param>
		/// <returns>Pointer to a new duplicate merge sprite</returns>
		virtual olc::Sprite* DuplicateMerge_SIMD(const olc::vi2d& vTargetPos, olc::Sprite* pTargetSprite, olc::Pixel p, olc::Sprite* pSource) = 0;

		/*-------------- END New Methods John Galvin --------------*/

		/// <summary>
		/// Static pointer PGE
		/// </summary>
		static olc::PixelGameEngine* ptrPGE;

	private:

		/*
		// <summary>
		/// Draws a Merge Sprite from the pSource to pDrawTarget
		/// </summary>
		/// <param name="vPos">Start position in the draw target (x,y)</param>
		/// <param name="pdrawTarget">A pointer to the draw target</param>
		/// <param name="vecPositions">Position Vector that is used to crop the sprite if out of bounds</param>
		/// <returns>A pointer to the draw target</returns>
		olc::Sprite* DrawToTarget(const olc::vi2d& vTargetPos, olc::Sprite* pdrawTarget, std::vector<int> vecPositions, olc::Sprite pSource);

		*/

	};

	class PGEX;

	// The Static Twins (plus three)
	static std::unique_ptr<Renderer> renderer;				// Pointer to the renderer (OpenGLES10/20/30)
	static std::unique_ptr<Platform> platform;				// Pointer to the OS platform (Android, iOS)
	static std::unique_ptr<SIMDDrawRoutines> simddrawer;	// Pointer to the SIMD Draw functions
	static std::unique_ptr<FileHandler> filehandler;		// Pointer to the file handler for (Android, iOS)
	static std::map<size_t, uint8_t> mapKeys;				// Mapped keys vector

	// O------------------------------------------------------------------------------O
	// | olc::PixelGameEngine - The main BASE class for your application              |
	// O------------------------------------------------------------------------------O
	class PixelGameEngine
	{
	public:
		PixelGameEngine();
		virtual ~PixelGameEngine();
	public:

		/// <summary>
		/// Creates the base window frame for your game
		/// </summary>
		/// <param name="screen_w">Screen Width in Pixels, set to 0 for auto width. Default: 0</param>
		/// <param name="screen_h">Screen Height in Pixels, set to 0 for auto height. Default: 0</param>
		/// <param name="pixel_w">Pixel Width. Default: 1, Min: 1</param>
		/// <param name="pixel_h">Pixel Height. Default: 1, Min: 1</param>
		/// <param name="full_screen">Use Full Screen: Default: true</param>
		/// <param name="vsync">Use vSync: Default: false</param>
		/// <param name="cohesion">NOT WORKING: Use Engine bounds cohesion: Default: false</param>
		/// <returns></returns>
		olc::rcode Construct(int32_t screen_w = 0, int32_t screen_h = 0, int32_t pixel_w = 1, int32_t pixel_h = 1,
			bool full_screen = true, bool vsync = false, bool cohesion = false);

		/// <summary>
		/// Starts the PGE Mobile Engine (Where the magic begins)
		/// </summary>
		/// <returns> FAIL = 0, OK = 1, NO_FILE = -1</returns>
		olc::rcode Start();

	public: // User Override Interfaces

		/// <summary>
		/// Called once on application startup, use to load your resources
		/// </summary>
		/// <returns>Success: true, Fail: false</returns>
		virtual bool OnUserCreate();

		/// <summary>
		/// Called every frame, and provides you with a time per frame value
		/// </summary>
		/// <param name="fElapsedTime">Time per frame</param>
		/// <returns>Success: true, Fail: false</returns>
		virtual bool OnUserUpdate(float fElapsedTime);

		/// <summary>
		/// Called once on application termination, so you can be one clean coder
		/// </summary>
		/// <returns>Success: true, Fail: false</returns>
		virtual bool OnUserDestroy();

		/// <summary>
		/// Called when a text entry is confirmed with "enter" key
		/// </summary>
		/// <param name="sText">Text to be displayed</param>
		virtual void OnTextEntryComplete(const std::string& sText);

		/// <summary>
		/// Fires when the OS is about to put the app into limp mode
		/// I.e. the user has swiped your game to close, a phone call occurred
		/// Basic any time something blocks the execution of your app 
		/// </summary>
		virtual void OnSaveStateRequested();

		/// <summary>
		/// Fires when the OS is about to resume your app, i.e. after a pause event
		/// Use this method to restore any setting from your save state as the onUserCreate will be called again
		/// </summary>
		virtual void OnRestoreStateRequested();


		// Deprecated: Called when a console command is executed
		//virtual bool OnConsoleCommand(const std::string& sCommand);


	public: // Hardware Interfaces

		/// <summary>
		/// Returns a sturct of sensor options
		/// </summary>
		olcSensors SelectSensor;

		/// <summary>
		/// Returns true if window is currently in focus
		/// </summary>
		/// <returns>Focused: true, Unfocused: false</returns>
		bool IsFocused() const;

		/// <summary>
		/// Set/Unset IsFocused 
		/// NOTE: This can also be called from the OS
		/// </summary>
		/// <param name="focus">Focused: true, Unfocused: false</param>
		void SetFocused(bool focus);

		/// <summary>
		/// Get the state of a specific keyboard button
		/// </summary>
		/// <param name="k">Enum Key Value</param>
		/// <returns>Key state: bPressed, bReleased, bHeld</returns>
		HWButton GetKey(Key k) const;

		/// <summary>
		/// Get the state of a specific mouse button
		/// WARNING: Touch and Mouse positions are currently linked
		/// Please update your code to use GetTouch()
		/// </summary>
		/// <param name="b">Button number (1,2,3)</param>
		/// <returns>Mouse button state: bPressed, bReleased, bHeld</returns>
		HWButton GetMouse(uint32_t b) const;

		/// <summary>
		/// Get the state of a specific touch point. Default: 0
		/// Note: Multi-touch now supported see: https://en.wikipedia.org/wiki/Multi-touch  
		/// </summary>
		/// <param name="p">points 0 - 4</param>
		/// <returns>Touch point state: bPressed, bReleased, bHeld</returns>
		HWButton GetTouch(uint32_t p = 0) const;

		/// <summary>
		/// Clears all touch points, or from start index
		/// </summary>
		/// <param name="startIndex">Start index to clear touch points. Default: 0 (All points)</param>
		void ClearTouchPoints(uint8_t startIndex = 0);

		/// <summary>
		/// Get Mouse X coordinate in "pixel" space
		/// WARNING: Touch and Mouse positions are not linked
		/// Please update your code to use GetTouchX()
		/// </summary>
		/// <returns>X coordinate</returns>
		int32_t GetMouseX() const;

		/// <summary>
		/// Get Touch ~X coordinate in "pixel" space
		/// WARNING: this is a approx (≅) value if the center position
		/// It depends on how big the finger is and how hard the touch is been pressed
		/// </summary>
		/// <param name="index">Which touch point: Default: 0</param>
		/// <returns>≅X coordinate</returns>
		int32_t GetTouchX(int8_t index = 0) const;

		/// <summary>
		/// Get Mouse Y coordinate in "pixel" space
		/// WARNING: Touch and Mouse positions are not linked
		/// Please update your code to use GetTouchX()
		/// </summary>
		/// <returns>Y coordinate</returns>
		int32_t GetMouseY() const;

		/// <summary>
		/// Get Touch ~Y coordinate in "pixel" space
		/// WARNING: this is a approx (≅) value if the center position
		/// It depends on how big the finger is and how hard the touch is been pressed
		/// </summary>
		/// <param name="index">Which touch point: Default: 0</param>
		/// <returns>≅Y coordinate</returns>
		int32_t GetTouchY(int8_t index = 0) const;

		/// <summary>
		/// Simi Deprecated: Get Mouse Wheel Delta
		/// This only works correctly with Chrome Book
		/// </summary>
		/// <returns>int32_t value</returns>
		int32_t GetMouseWheel() const;

		/// <summary>
		/// Simi Deprecated: Get the mouse in window space
		/// The PGE now auto controls any offsets required for touch & mouse position
		/// </summary>
		/// <returns>Mouse {x, y}</returns>
		const olc::vi2d& GetWindowMouse() const;

		/// <summary>
		/// Gets the mouse as a vector
		/// WARNING: Touch and Mouse positions are currently linked
		/// Please update your code to use GetTouchPos
		/// Mouse position only works correctly with Chrome Book
		/// </summary>
		/// <returns>Mouse {x, y}</returns>
		const olc::vi2d& GetMousePos() const;

		/// <summary>
		/// Gets the touch position as a vi2d vector {≅x, ≅y}
		/// WARNING: this is a approx (≅) value if the center position
		/// It depends on how big the finger is and how hard the touch is been pressed
		/// </summary>
		/// <param name="index">Touch point index, Default: 0. Touch points are index by the timing of the first touch to the last</param>
		/// <returns>touch {≅x, ≅y}</returns>
		const olc::vi2d& GetTouchPos(int8_t index = 0) const;


		/// <summary>
		/// Get Key Map
		/// </summary>
		/// <returns>Map Keys</returns>
		static const std::map<size_t, uint8_t>& GetKeyMap() { return mapKeys; }

	public: // Utility

		/// <summary>
		/// Returns the width of the screen in "pixels"
		/// </summary>
		/// <returns>Screen Width in pixels</returns>
		int32_t ScreenWidth() const;

		/// <summary>
		/// Returns the height of the screen in "pixels"
		/// </summary>
		/// <returns>Screen Height in pixels</returns>
		int32_t ScreenHeight() const;

		/// <summary>
		/// Returns the width of the currently selected drawing target in "pixels"
		/// </summary>
		/// <returns>Draw target width in pixels</returns>
		int32_t GetDrawTargetWidth() const;

		/// <summary>
		/// Returns the height of the currently selected drawing target in "pixels"
		/// </summary>
		/// <returns>Draw target height in pixels</returns>
		int32_t GetDrawTargetHeight() const;

		/// <summary>
		/// Returns the currently active draw target
		/// </summary>
		/// <returns>A pointer to the draw target</returns>
		olc::Sprite* GetDrawTarget() const;

		/// <summary>
		/// Resize the primary screen sprite. 
		/// WARNING: The OS will automatically resize, your resize, to ensure it is displayed correctly.
		/// However all offsets, i.e. mouse, touch etc will be automatically corrected too.
		/// </summary>
		/// <param name="w">New width</param>
		/// <param name="h">New height</param>
		void SetScreenSize(int w, int h);

		/// <summary>
		/// Specify which Sprite/Drawtarget should be the target of drawing functions, use nullptr to specify the primary screen
		/// </summary>
		/// <param name="target">A pointer to a Sprite or Draw Target. Pass nullptr to select drawtarget[0] (primary screen)</param>
		void SetDrawTarget(Sprite* target);

		/// <summary>
		/// Gets the current Frames Per Second
		/// </summary>
		/// <returns>Number of frames per second</returns>
		uint32_t GetFPS() const;

		/// <summary>
		/// Gets last update of elapsed time
		/// </summary>
		/// <returns>float value of elapsed time</returns>
		float GetElapsedTime() const;

		/// <summary>
		/// Gets Actual Window size. 
		/// WARNING: This will not be a true size, 
		/// The Engine will automatically resize, correct offsets, etc. to ensure your game appears correctly.
		/// Therefore your Android/iOS setting made differ to this, however you have nothing to worry about, it will all work automatically. 
		/// FINALLY: There is no way of getting the true size from the PGE. You will need to use MyAndroidApp* or MyiOSApp*.
		/// </summary>
		/// <returns>Windows Size {width, height}</returns>
		const olc::vi2d& GetWindowSize() const;

		/// <summary>
		/// Gets pixel scale
		/// </summary>
		/// <returns>{width, height}</returns>
		const olc::vi2d& GetPixelSize() const;

		/// <summary>
		/// Gets actual pixel scale
		/// </summary>
		/// <returns>{width, height}</returns>
		const olc::vi2d& GetScreenPixelSize() const;

		/// <summary>
		/// Gets "screen" size.
		/// WARNING: This will not be a true size, 
		/// The Engine will automatically resize, correct offsets, etc. to ensure your game appears correctly. 
		/// Therefore your Android/iOS setting made differ to this, however you have nothing to worry about, it will all work automatically. 
		/// FINALLY: There is no way of getting the true size from the PGE. You will need to use MyAndroidApp* or MyiOSApp*.
		/// </summary>
		/// <returns>{width, height}</returns>
		const olc::vi2d& GetScreenSize() const;

		/// <summary>
		/// Gets any files dropped this frame
		/// </summary>
		/// <returns>List of files</returns>
		const std::vector<std::string>& GetDroppedFiles() const;

		/// <summary>
		/// Gets the point where the files where dropped
		/// </summary>
		/// <returns>{x, y}</returns>
		const olc::vi2d& GetDroppedFilesPoint() const;

	public: // CONFIGURATION ROUTINES


		/// <summary>
		/// Layer targeting functions
		/// </summary>
		/// <param name="layer">layer number</param>
		/// <param name="bDirty">Default true</param>
		void SetDrawTarget(uint8_t layer, bool bDirty = true);

		/// <summary>
		/// Enable/Disable a layer
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="b">true / false</param>
		void EnableLayer(uint8_t layer, bool b);

		/// <summary>
		/// Set the layer offset
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="offset">{x , y}</param>
		void SetLayerOffset(uint8_t layer, const olc::vf2d& offset);

		/// <summary>
		/// Set the layer offset
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		void SetLayerOffset(uint8_t layer, float x, float y);

		/// <summary>
		/// Set the layer scale
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="scale">{sx, sy}</param>
		void SetLayerScale(uint8_t layer, const olc::vf2d& scale);

		/// <summary>
		/// Set the layer scale
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="x">Scale sX</param>
		/// <param name="y">Scale sY</param>
		void SetLayerScale(uint8_t layer, float x, float y);

		/// <summary>
		/// Set layer tint
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="tint">Pixel color</param>
		void SetLayerTint(uint8_t layer, const olc::Pixel& tint);

		/// <summary>
		/// Set a layer function
		/// </summary>
		/// <param name="layer">Layer number</param>
		/// <param name="f">Pass the std::function<void()> required</param>
		void SetLayerCustomRenderFunction(uint8_t layer, std::function<void()> f);

		/// <summary>
		/// Get a vector list of layers
		/// </summary>
		/// <returns>Vector of layers</returns>
		std::vector<LayerDesc>& GetLayers();

		/// <summary>
		/// Create a layer
		/// </summary>
		/// <returns>New layer number</returns>
		uint32_t CreateLayer();

		/// <summary>
		/// Change the pixel mode for different optimisations
		/// olc::Pixel::NORMAL = No transparency
		/// olc::Pixel::MASK   = Transparent if alpha is < 255
		/// olc::Pixel::ALPHA  = Full transparency
		/// </summary>
		/// <param name="m">NORMAL, MASK, ALPHA</param>
		void SetPixelMode(Pixel::Mode m);

		/// <summary>
		/// Get the current pixel mode
		/// </summary>
		/// <returns>NORMAL, MASK, ALPHA, CUSTOM</returns>
		Pixel::Mode GetPixelMode();

		/// <summary>
		/// Use a custom blend function
		/// </summary>
		/// <param name="pixelMode">Pixel mode custom function</param>
		void SetPixelMode(std::function<olc::Pixel(const int x, const int y, const olc::Pixel& pSource, const olc::Pixel& pDest)> pixelMode);

		/// <summary>
		/// Change the blend factor from between 0.0f to 1.0f;
		/// </summary>
		/// <param name="fBlend">float (min 0.0f, max 1.0f)</param>
		void SetPixelBlend(float fBlend);

		/// <summary>
		/// Returns a vector SensorInformation structs for all supported sensors on this device
		/// </summary>
		/// <returns>Vector of SensorInformation</returns>
		std::vector<olc::SensorInformation> GetSupportedSensors();

		/// <summary>
		/// Returns the passed Sensor Information
		/// NOTE: If SensorInformation.Type = ASENSOR_TYPE_INVALID the sensor is not supported
		/// </summary>
		/// <param name="Type">olc::SensorType</param>
		/// <returns>ensorInformation Struct</returns>
		olc::SensorInformation GetSensorInfo(olc::SensorType Type);

		/// <summary>
		/// Enable the selected sensor, and set the default sample rate
		/// NOTE: If the sample rate is less than what the sensor can handle, the default is used.
		/// </summary>
		/// <param name="Type">olc::SensorType</param>
		/// <param name="sampleRate">Number of samples per second, set to -1 to reset to default values. Default: -1 (Auto)</param>
		/// <returns>Success: OK, Notsupported: FAIL</returns>
		olc::rcode EnableSensor(olc::SensorType Type, int32_t sampleRate = -1);


		/// <summary>
		/// Attempts to change the sample rate of the sensor
		/// NOTE: If the sample rate is less than what the sensor can handle, the default is used.
		/// </summary>
		/// <param name="Type">olc::SensorType</param>
		/// <param name="sampleRate">Number of samples per second, set to -1 to reset to default values</param>
		/// <returns></returns>
		olc::rcode ChangeSensorSampleRate(olc::SensorType Type, int32_t sampleRate);

		/// <summary>
		/// Disables the passed Sensor if supported
		/// </summary>
		/// <param name="Type">Sensor</param>
		/// <returns>Disabled: OK, Error: FAIL</returns>
		olc::rcode DisableSensor(olc::SensorType Type);



	public: // DRAWING ROUTINES

		/// <summary>
		/// Draws a single Pixel. 
		/// Example: Draw(50, 50, olc::BLACK);
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		/// <returns>Success: true, Fail: false</returns>
		virtual bool Draw(int32_t x, int32_t y, Pixel p = olc::WHITE);

		/// <summary>
		/// Draws a single Pixel. 
		/// Example: Draw({50, 50}, olc::BLACK);
		/// </summary>
		/// <param name="pos">{x , y}</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		/// <returns>Success: true, Fail: false</returns>
		bool Draw(const olc::vi2d& pos, Pixel p = olc::WHITE);

		/// <summary>
		/// Draws a line from (x1,y1) to (x2,y2). 
		/// Example: DrawLine(50, 50, 50, 100, olc::BLUE);
		/// </summary>
		/// <param name="x1">Start Position x1</param>
		/// <param name="y1">Start Position y1</param>
		/// <param name="x2">End Position x2</param>
		/// <param name="y2">End Position y2</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		/// <param name="pattern">Pattern, Default: 0xFFFFFFFF (Solid Line)</param>
		void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p = olc::WHITE, uint32_t pattern = 0xFFFFFFFF);

		/// <summary>
		/// Draws a line from {x1,y1} to {x2,y2}. 
		/// Example: DrawLine({50, 50}, {50, 100}, olc::BLUE);
		/// </summary>
		/// <param name="pos1">Start Position vector {x1, y1}</param>
		/// <param name="pos2">End Position vector {x2, y2}</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		/// <param name="pattern">Pattern, Default: 0xFFFFFFFF (Solid Line)</param>
		void DrawLine(const olc::vi2d& pos1, const olc::vi2d& pos2, Pixel p = olc::WHITE, uint32_t pattern = 0xFFFFFFFF);

		/// <summary>
		/// Draws a circle located at (x,y) with radius. 
		/// Example: DrawCircle(100, 100, 50, olc::YELLOW);
		/// </summary>
		/// <param name="x">Center Position x</param>
		/// <param name="y">Center Position y</param>
		/// <param name="radius">radius in pixels</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		/// <param name="mask">Pattern, Default: 0xFF (Solid Line)</param>
		void DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p = olc::WHITE, uint8_t mask = 0xFF);

		/// <summary>
		/// Draws a circle located at {x,y} with radius. 
		/// Example: DrawCircle({100, 100}, 50, olc::YELLOW); 
		/// </summary>
		/// <param name="pos">Center Position vector {x , y}</param>
		/// <param name="radius">radius in pixels</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		/// <param name="mask">Pattern, Default: 0xFF (Solid Line)</param>
		void DrawCircle(const olc::vi2d& pos, int32_t radius, Pixel p = olc::WHITE, uint8_t mask = 0xFF);

		/// <summary>
		/// Fills a circle located at (x,y) with radius.
		/// Example: FillCircle(200, 200, 100, olc::RED); 
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches.
		/// </summary>
		/// <param name="x">Center Position x</param>
		/// <param name="y">Center Position y</param>
		/// <param name="radius">radius in pixels</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		void FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p = olc::WHITE);

		/// <summary>
		/// Fills a circle located at {x,y} with radius. 
		/// Example: FillCircle({200, 200}, 100, olc::RED); 
		/// NOTE: Auto SIMD Enabled, all the speed none of the headache.
		/// </summary>
		/// <param name="pos">Center Position vector {x, y}</param>
		/// <param name="radius">radius in pixels</param>
		/// <param name="p">Pixel Colour, Default: olc::WHITE</param>
		void FillCircle(const olc::vi2d& pos, int32_t radius, Pixel p = olc::WHITE);

		/// <summary>
		/// Draws a rectangle at (x,y) to (x+w,y+h). 
		/// DrawRect(150, 150, 50, 50, olc::GREEN);
		/// </summary>
		/// <param name="x">Start Position x</param>
		/// <param name="y">Start Position y</param>
		/// <param name="w">Rectangle Width</param>
		/// <param name="h">Rectangle height</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = olc::WHITE);

		/// <summary>
		/// Draws a rectangle at {x,y} with a vSize {w, h}. 
		/// DrawRect({150, 150}, {50, 50}, olc::GREEN);
		/// </summary>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="size">Rectangle vector Size {width, height}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void DrawRect(const olc::vi2d& pos, const olc::vi2d& size, Pixel p = olc::WHITE);

		/// <summary>
		///  Fills a rectangle at (x,y) to (x+w,y+h). 
		///  FillRect(150, 150, 50, 50, olc::DARK_CYAN);
		///  NOTE: Auto SIMD Enabled, all the speed none of the headaches
		/// </summary>
		/// <param name="x">Start Position x</param>
		/// <param name="y">Start Position y</param>
		/// <param name="w">Rectangle Width</param>
		/// <param name="h">Rectangle height</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = olc::WHITE);

		/// <summary>
		/// Fills a rectangle at {x,y} with a vSize {w, h}. 
		/// FillRect({150, 150}, {50, 50}, olc::GREEN);
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches
		/// </summary>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="size">Rectangle vector Size {width, height}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void FillRect(const olc::vi2d& pos, const olc::vi2d& size, Pixel p = olc::WHITE);

		/// <summary>
		/// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3).
		/// Example: DrawTriangle(100, 100, 150, 50, 150, 100, olc::VERY_DARK_YELLOW);
		/// </summary>
		/// <param name="x1">Position Point x1</param>
		/// <param name="y1">Position Point y1</param>
		/// <param name="x2">Position Point x2</param>
		/// <param name="y2">Position Point y2</param>
		/// <param name="x3">Position Point x3</param>
		/// <param name="y3">Position Point y3</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = olc::WHITE);

		/// <summary>
		/// Draws a triangle between vector points {x1,y1}, {x2,y2} and {x3,y3}.
		/// Example: DrawTriangle({100, 100}, {150, 50}, {150, 100}, olc::VERY_DARK_YELLOW);
		/// </summary>
		/// <param name="pos1">Position Point vector {x1, y1}</param>
		/// <param name="pos2">Position Point vector {x2, y2}</param>
		/// <param name="pos3">Position Point vector {x3, y3}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void DrawTriangle(const olc::vi2d& pos1, const olc::vi2d& pos2, const olc::vi2d& pos3, Pixel p = olc::WHITE);

		/// <summary>
		/// Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3). 
		/// Example: FillTriangle(100, 100, 150, 50, 150, 100, olc::VERY_DARK_YELLOW); 
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches. 
		/// </summary>
		/// <param name="x1">Position Point x1</param>
		/// <param name="y1">Position Point y1</param>
		/// <param name="x2">Position Point x2</param>
		/// <param name="y2">Position Point y2</param>
		/// <param name="x3">Position Point x3</param>
		/// <param name="y3">Position Point y3</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = olc::WHITE);

		/// <summary>
		/// Flat fills a triangle between vectors points {x1,y1}, {x2,y2} and {x3,y3}. 
		/// Example: FillTriangle({100, 100}, {150, 50}, {150, 100}, olc::VERY_DARK_YELLOW); 
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches.
		/// </summary>
		/// <param name="pos1">Position Point vector {x1, y1}</param>
		/// <param name="pos2">Position Point vector {x2, y2}</param>
		/// <param name="pos3">Position Point vector {x3, y3}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void FillTriangle(const olc::vi2d& pos1, const olc::vi2d& pos2, const olc::vi2d& pos3, Pixel p = olc::WHITE);

		/// <summary>
		/// Fill a textured and coloured triangle.
		/// Example ---: 
		/// std::vector<olc::vf2d> vPoints;
		///	vPoints.push_back({ 100, 100 });
		///	vPoints.push_back({ 150, 50 });
		///	vPoints.push_back({ 150, 100 });
		///
		///	std::vector<olc::vf2d> vTex;
		///	vTex.push_back({ 0.5f, 0.9f });
		///
		///	std::vector<olc::Pixel> vColour;
		///	vColour.push_back(olc::DARK_YELLOW);
		///	vColour.push_back(olc::WHITE);
		///	vColour.push_back(olc::GREEN);
		///
		///	olc::Sprite* someSprite;
		///
		///	FillTexturedTriangle(vPoints, vTex, vColour, someSprite); ---
		/// </summary>
		/// <param name="vPoints">vector of triangle points</param>
		/// <param name="vTex">vector of textures</param>
		/// <param name="vColour">vector of colours (pixels)</param>
		/// <param name="sprTex">A pointer to the sprite</param>
		void FillTexturedTriangle(const std::vector<olc::vf2d>& vPoints, std::vector<olc::vf2d> vTex, std::vector<olc::Pixel> vColour, olc::Sprite* sprTex);

		/// <summary>
		/// Fill a Textures Polygon
		/// Example: --- 
		/// std::vector<olc::vf2d> vPoints;
		///	vPoints.push_back({ 100, 100 });
		///	vPoints.push_back({ 150, 50 });
		///	vPoints.push_back({ 150, 100 });
		///	vPoints.push_back({ 200, 200 });
		///
		///	std::vector<olc::vf2d> vTex;
		///	vTex.push_back({ 0.5f, 0.9f });
		///
		///	std::vector<olc::Pixel> vColour;
		///	vColour.push_back(olc::DARK_YELLOW);
		///	vColour.push_back(olc::WHITE);
		///	vColour.push_back(olc::GREEN);
		///
		///	olc::Sprite* someSprite;
		///
		///	FillTexturedPolygon(vPoints, vTex, vColour, someSprite); ---
		/// </summary>
		/// <param name="vPoints">vector of ploygon points</param>
		/// <param name="vTex">vector of textures</param>
		/// <param name="vColour">vector of colours (pixels)</param>
		/// <param name="sprTex">A pointer to the sprite</param>
		/// <param name="structure">olc::DecalStructure::LINE, FAN, STRIP, LIST, Default: olc::DecalStructure::LIST</param>
		void FillTexturedPolygon(const std::vector<olc::vf2d>& vPoints, const std::vector<olc::vf2d>& vTex, const std::vector<olc::Pixel>& vColour, olc::Sprite* sprTex, olc::DecalStructure structure = olc::DecalStructure::LIST);

		/// <summary>
		/// Draws an entire sprite at location (x,y)
		/// Example: DrawSprite(200, 200, pSprite);
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="sprite">A pointer to the sprite</param>
		/// <param name="scale">Scale (>= 1), Default: 1</param>
		/// <param name="flip">olc::Sprite::NONE, FLIP, HORIZ, Default olc::Sprite::NONE</param>
		void DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale = 1, uint8_t flip = olc::Sprite::NONE);

		/// <summary>
		/// Draws an entire sprite at vector location {x,y}
		/// Example: DrawSprite({ 200, 200 }, pSprite);
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches
		/// </summary>
		/// <param name="pos">{x, y}</param>
		/// <param name="sprite">A pointer to the sprite</param>
		/// <param name="scale">Scale (>= 1), Default: 1</param>
		/// <param name="flip">olc::Sprite::NONE, FLIP, HORIZ, Default olc::Sprite::NONE</param>
		void DrawSprite(const olc::vi2d& pos, Sprite* sprite, uint32_t scale = 1, uint8_t flip = olc::Sprite::NONE);

		/// <summary>
		/// Draws an area of a sprite at location (x,y), where the selected area is (ox,oy) to (ox+w,oy+h)
		/// Example: DrawPartialSprite(200, 200, pSprite, 50, 50, 100, 100);
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches
		/// </summary>
		/// <param name="x">Position x on draw target to draw the partial sprite</param>
		/// <param name="y">Position y on draw target to draw the partial sprite</param>
		/// <param name="sprite">A pointer to the sprite</param>
		/// <param name="ox">Position x on the sprite to start creating the partial sprite</param>
		/// <param name="oy">Position y on the sprite to start creating the partial sprite</param>
		/// <param name="w">Width of the partial sprite</param>
		/// <param name="h">Height of the partial sprite</param>
		/// <param name="scale">Scale (>= 1), Default: 1</param>
		/// <param name="flip">olc::Sprite::NONE, FLIP, HORIZ, Default olc::Sprite::NON</param>
		void DrawPartialSprite(int32_t x, int32_t y, Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale = 1, uint8_t flip = olc::Sprite::NONE);

		/// <summary>
		/// Draws an area of a sprite at vector location {x,y}, where the selected area is {ox,oy} to {ox+w,oy+h}
		/// Example: DrawPartialSprite({200, 200}, pSprite, {50, 50}, {100, 100});
		/// NOTE: Auto SIMD Enabled, all the speed none of the headaches
		/// </summary>
		/// <param name="pos">Vector Position {x, y} on draw target to draw the partial sprite</param>
		/// <param name="sprite">A pointer to the sprite</param>
		/// <param name="sourcepos">Vector Position {x, y} on the sprite to start creating the partial sprite</param>
		/// <param name="size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="scale">Scale (>= 1), Default: 1</param>
		/// <param name="flip">olc::Sprite::NONE, FLIP, HORIZ, Default olc::Sprite::NON</param>
		void DrawPartialSprite(const olc::vi2d& pos, Sprite* sprite, const olc::vi2d& sourcepos, const olc::vi2d& size, uint32_t scale = 1, uint8_t flip = olc::Sprite::NONE);

		/// <summary>
		/// Draws a single line of text - traditional monospaced
		/// Example: DrawString(100, 100, "Pixel Game Engine 2.0 Mobile Rocks!!");
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="col">Pixel colour, Default: olc::WHITE</param>
		/// <param name="scale">Scale (>=1), Default: 1</param>
		void DrawString(int32_t x, int32_t y, const std::string& sText, Pixel col = olc::WHITE, uint32_t scale = 1);

		/// <summary>
		/// Draws a single line of text - traditional monospaced
		/// Example: DrawString({100, 100}, "Pixel Game Engine 2.0 Mobile Rocks!!"); 
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="col">Pixel colour, Default: olc::WHITE</param>
		/// <param name="scale">Scale (>=1), Default: 1</param>
		void DrawString(const olc::vi2d& pos, const std::string& sText, Pixel col = olc::WHITE, uint32_t scale = 1);

		/// <summary>
		/// Gets the passed string text size {width, height} - traditional monospaced
		/// Example: olc::vi2d vTextSize = GetTextSize("Pixel Game Engine 2.0 Mobile Rocks!!");
		/// </summary>
		/// <param name="s">Text to be test</param>
		/// <returns>{width, height}</returns>
		olc::vi2d GetTextSize(const std::string& s);

		/// <summary>
		/// Draws a single line of text - non-monospaced
		/// Example: DrawStringProp(100, 100, "Pixel Game Engine 2.0 Mobile Rocks!!");
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="col">Pixel colour, Default: olc::WHITE</param>
		/// <param name="scale">Scale (>=1), Default: 1</param>
		void DrawStringProp(int32_t x, int32_t y, const std::string& sText, Pixel col = olc::WHITE, uint32_t scale = 1);

		/// <summary>
		/// Draws a single line of text - non-monospaced
		/// Example: DrawString({100, 100}, "Pixel Game Engine 2.0 Mobile Rocks!!"); 
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="col">Pixel colour, Default: olc::WHITE</param>
		/// <param name="scale">Scale (>=1), Default: 1</param>
		void DrawStringProp(const olc::vi2d& pos, const std::string& sText, Pixel col = olc::WHITE, uint32_t scale = 1);

		/// <summary>
		/// Gets the passed string text size {width, height} - non-monospaced
		/// Example: olc::vi2d vTextSize = GetTextSizeProp("Pixel Game Engine 2.0 Mobile Rocks!!");
		/// </summary>
		/// <param name="s">Text to be test</param>
		/// <returns>{width, height}</returns>
		olc::vi2d GetTextSizeProp(const std::string& s);

		/*----- New Methods John Galvin------*/

		/// <summary>
		/// Merges the pFromSprite Into the pToSprite and draws it to the Draw Target at position (vPosx, vPosy)
		/// </summary>
		/// <param name="vPosx">Target position x</param>
		/// <param name="vPosy">Target position y</param>
		/// <param name="pFromSprite">a pointer to the From Sprite</param>
		/// <param name="vToSpritePosx">Position x within the ToSprite to Draw the From Sprite</param>
		/// <param name="vToSpritePosy">Position y within the ToSprite to Draw the From Sprite</param>
		/// <param name="pToSprite">A pointer to the Sprite to which the from Sprite will be merged into</param>
		/// <param name="blendPixel">Blend Pixel for merge (Default olc::BLANK)</param>
		/// <param name="scale">Scaler size (>= 1, Default 1)</param>
		/// <param name="flip">olc::Sprite::NONE, ..HORIZ, ..VERT (Default NONE</param>
		void DrawMergeSprite(int32_t vPosx, int32_t vPosy, Sprite* pFromSprite, int32_t vToSpritePosx, int32_t vToSpritePosy,
			Sprite* pToSprite, Pixel blendPixel = olc::BLANK, uint32_t scale = 1, olc::Sprite::Flip flip = olc::Sprite::NONE);

		/// <summary>
		/// Merges the pFromSprite Into the pToSprite and draws it to the Draw Target at position (vPos.x, vPos.y)
		/// </summary>
		/// <param name="pos">Target position (x,y)</param>
		/// <param name="pFromSprite">a pointer to the From Sprite</param>
		/// <param name="vToSpritePos">Position within the ToSprite to Draw the From Sprite</param>
		/// <param name="pToSprite">A pointer to the Sprite to which the from Sprite will be merged into</param>
		/// <param name="blendPixel">Blend Pixel for merge (Default olc::BLANK)</param>
		/// <param name="scale">Scaler size (>= 1, Default 1)</param>
		/// <param name="flip">olc::Sprite::NONE, ..HORIZ, ..VERT (Default NONE)</param>
		void DrawMergeSprite(const olc::vi2d& vPos, Sprite* pFromSprite, const olc::vi2d& vToSpritePos, Sprite* pToSprite,
			Pixel blendPixel = olc::BLANK, uint32_t scale = 1, olc::Sprite::Flip flip = olc::Sprite::NONE);

		/*----- END New Methods John Galvin------*/


		/// <summary>
		/// Set Decal Quad functions
		/// </summary>
		/// <param name="mode">NORMAL, ADDITIVE, MULTIPLICATIVE, STENCIL, ILLUMINATE, WIREFRAME, MODEL3D </param>
		void SetDecalMode(const olc::DecalMode& mode);

		/// <summary>
		/// Set Decal Structure
		/// </summary>
		/// <param name="structure">LINE, FAN, STRIP, LIST</param>
		void SetDecalStructure(const olc::DecalStructure& structure);

		/// <summary>
		/// Draws a whole decal, with optional scale and tinting
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f,1.0f } </param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawDecal(const olc::vf2d& pos, olc::Decal* decal, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a region of a decal, with optional scale and tinting
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="source_pos">Vector Position {x, y} on the decal to start creating the partial decal</param>
		/// <param name="source_size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f,1.0f } </param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawPartialDecal(const olc::vf2d& pos, olc::Decal* decal, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a region of a decal, with optional tinting
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="source_pos">Vector Position {x, y} on the decal to start creating the partial decal</param>
		/// <param name="source_size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawPartialDecal(const olc::vf2d& pos, const olc::vf2d& size, olc::Decal* decal, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws fully user controlled 4 vertices, pos(pixels), uv(pixels), colours
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="uv"></param>
		/// <param name="col">Pixel colour</param>
		/// <param name="elements">Default 4</param>
		void DrawExplicitDecal(olc::Decal* decal, const olc::vf2d* pos, const olc::vf2d* uv, const olc::Pixel* col, uint32_t elements = 4);

		/// <summary>
		/// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position vf2d{x, y}[4]</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawWarpedDecal(olc::Decal* decal, const olc::vf2d(&pos)[4], const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawWarpedDecal(olc::Decal* decal, const olc::vf2d* pos, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position std::array<olc::vf2d, 4>&{x, y}</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawWarpedDecal(olc::Decal* decal, const std::array<olc::vf2d, 4>& pos, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a Partial Warped decal
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position vf2d{x, y}[4]</param>
		/// <param name="source_pos">Vector Position {x, y} on the decal to start creating the partial decal</param>
		/// <param name="source_size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawPartialWarpedDecal(olc::Decal* decal, const olc::vf2d(&pos)[4], const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a Partial Warped decal
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position vf2d{x, y}[4]</param>
		/// <param name="source_pos">Vector Position {x, y} on the decal to start creating the partial decal</param>
		/// <param name="source_size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawPartialWarpedDecal(olc::Decal* decal, const olc::vf2d* pos, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a Partial Warped decal
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Vector Position vf2d{x, y}[4]</param>
		/// <param name="source_pos">Vector Position std::array<olc::vf2d, 4>&{x, y} on the decal to start creating the partial decal</param>
		/// <param name="source_size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="tint">Tint pixel colour, Default: olc:WHITE</param>
		void DrawPartialWarpedDecal(olc::Decal* decal, const std::array<olc::vf2d, 4>& pos, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a decal rotated to specified angle, with point of rotation offset
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="fAngle">Angle</param>
		/// <param name="center">Vector Center Position {x, y}, Default: { 0.0f, 0.0f }</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f, 1.0f }</param>
		/// <param name="tint">Tint colour, Default: olc::WHITE</param>
		void DrawRotatedDecal(const olc::vf2d& pos, olc::Decal* decal, const float fAngle, const olc::vf2d& center = { 0.0f, 0.0f }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a Partial decal rotated to specified angle, with point of rotation offset
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="fAngle">Angle</param>
		/// <param name="center">Vector Center Position {x, y}</param>
		/// <param name="source_pos">Vector Position {x, y} on the decal to start creating the partial decal</param>
		/// <param name="source_size">Vector Size {width, height} of the partial sprite</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f, 1.0f }</param>
		/// <param name="tint">Tint colour, Default: olc::WHITE</param>
		void DrawPartialRotatedDecal(const olc::vf2d& pos, olc::Decal* decal, const float fAngle, const olc::vf2d& center, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::vf2d& scale = { 1.0f, 1.0f }, const olc::Pixel& tint = olc::WHITE);

		/// <summary>
		/// Draws a multiline string as a decal, with tinting and scaling
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="col">Pixel colour, Default: olc::WHITE</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f, 1.0f }</param>
		void DrawStringDecal(const olc::vf2d& pos, const std::string& sText, const Pixel col = olc::WHITE, const olc::vf2d& scale = { 1.0f, 1.0f });

		/// <summary>
		/// Draws a multiline propionate string as a decal, with tinting and scaling
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="col">Pixel colour, Default: olc::WHITE</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f, 1.0f }</param>
		void DrawStringPropDecal(const olc::vf2d& pos, const std::string& sText, const Pixel col = olc::WHITE, const olc::vf2d& scale = { 1.0f, 1.0f });

		/// <summary>
		///  Draws a single rectangle as a decal
		/// </summary>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="size">Rectangle vector Size {width, height}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void DrawRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel col = olc::WHITE);

		/// <summary>
		/// Draws a single shaded filled rectangle as a decal
		/// </summary>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="size">Rectangle vector Size {width, height}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void FillRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel col = olc::WHITE);

		/// <summary>
		/// Draws a corner shaded rectangle as a decal
		/// </summary>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="size">Rectangle vector Size {width, height}</param>
		/// <param name="colTL">Pixel colour Top Left</param>
		/// <param name="colBL">Pixel colour Bottom Left</param>
		/// <param name="colBR">Pixel colour Top Right</param>
		/// <param name="colTR">Pixel colour Bottom Right</param>
		void GradientFillRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel colTL, const olc::Pixel colBL, const olc::Pixel colBR, const olc::Pixel colTR);

		/// <summary>
		/// Draws an arbitrary convex textured polygon using GPU
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="uv">vector<olc::vf2d> uv</param>
		/// <param name="tint">Tint Colour, Default: olc::WHITE</param>
		void DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<olc::vf2d>& uv, const olc::Pixel tint = olc::WHITE);

		/// <summary>
		/// Draws an arbitrary convex textured polygon using GPU
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="depth">std::vector<float> depth</param>
		/// <param name="uv">vector<olc::vf2d>& uv</param>
		/// <param name="tint">Tint Colour, Default: olc::WHITE</param>
		void DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<float>& depth, const std::vector<olc::vf2d>& uv, const olc::Pixel tint = olc::WHITE);

		/// <summary>
		/// Draws an arbitrary convex textured polygon using GPU
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="uv">vector<olc::vf2d>& uv</param>
		/// <param name="tint">vector<olc::Pixel>& tint</param>
		void DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<olc::vf2d>& uv, const std::vector<olc::Pixel>& tint);

		/// <summary>
		/// Draws an arbitrary convex textured polygon using GPU
		/// </summary>
		/// <param name="decal">A pointer to the decal</param>
		/// <param name="pos">Start Position vector {x, y}</param>
		/// <param name="uv">vector<olc::vf2d>& uv</param>
		/// <param name="colours">vector<olc::Pixel>& colours</param>
		/// <param name="tint">Tint pixel colour</param>
		void DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<olc::vf2d>& uv, const std::vector<olc::Pixel>& colours, const olc::Pixel tint);

		/// <summary>
		/// Draws a line in Decal Space
		/// </summary>
		/// <param name="pos1">Start Position Vector {x, y}</param>
		/// <param name="pos2">End Position Vector {x1, y1}</param>
		/// <param name="p">Pixel colour, Default: olc::WHITE</param>
		void DrawLineDecal(const olc::vf2d& pos1, const olc::vf2d& pos2, Pixel p = olc::WHITE);

		/// <summary>
		/// Draw a rotated string decal
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="fAngle">Angle</param>
		/// <param name="center">Vector Center Position {x, y}, Default: { 0.0f, 0.0f }</param>
		/// <param name="col">Pixel colour: Default: olc::WHITE</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f, 1.0f }</param>
		void DrawRotatedStringDecal(const olc::vf2d& pos, const std::string& sText, const float fAngle, const olc::vf2d& center = { 0.0f, 0.0f }, const olc::Pixel col = olc::WHITE, const olc::vf2d& scale = { 1.0f, 1.0f });

		/// <summary>
		/// Draw a rotated propionate string decal
		/// </summary>
		/// <param name="pos">Vector Position {x, y}</param>
		/// <param name="sText">Text to be drawn</param>
		/// <param name="fAngle">Angle</param>
		/// <param name="center">Vector Center Position {x, y}, Default: { 0.0f, 0.0f }</param>
		/// <param name="col">Pixel colour: Default: olc::WHITE</param>
		/// <param name="scale">Scale {width, height}, Default: { 1.0f, 1.0f }</param>
		void DrawRotatedStringPropDecal(const olc::vf2d& pos, const std::string& sText, const float fAngle, const olc::vf2d& center = { 0.0f, 0.0f }, const olc::Pixel col = olc::WHITE, const olc::vf2d& scale = { 1.0f, 1.0f });

		/// <summary>
		/// Clears entire draw target to Pixel
		/// </summary>
		/// <param name="p">Pixel colour</param>
		void Clear(Pixel p);

		/// <summary>
		/// Clears the rendering back buffer
		/// </summary>
		/// <param name="p">Pixel Colour</param>
		/// <param name="bDepth">Depth, Default: true</param>
		void ClearBuffer(Pixel p, bool bDepth = true);

		/// <summary>
		/// Returns the font image
		/// </summary>
		/// <returns>A pointer to the font image</returns>
		olc::Sprite* GetFontSprite();

		/// <summary>
		/// Clip a line segment to visible area
		/// </summary>
		/// <param name="in_p1">Vector position 1 {x, y}</param>
		/// <param name="in_p2">Vector position 1 {x, y}</param>
		/// <returns>Clipped: true/false</returns>
		bool ClipLineToScreen(olc::vi2d& in_p1, olc::vi2d& in_p2);

		/// <summary>
		/// Do not allow PGE to mark layers as dirty, so pixel graphics don't update
		/// </summary>
		/// <param name="bEnable">Default: true</param>
		void EnablePixelTransfer(const bool bEnable = true);

		/// <summary>
		/// Text Entry Routines
		/// </summary>
		/// <param name="bEnable">True/False</param>
		/// <param name="sText">Text, Default: ""</param>
		void TextEntryEnable(const bool bEnable, const std::string& sText = "");

		/// <summary>
		/// Returns the enter text string
		/// </summary>
		/// <returns>Text string</returns>
		std::string TextEntryGetString() const;

		/// <summary>
		/// Gets the cursor position
		/// </summary>
		/// <returns>Cursor position</returns>
		int32_t TextEntryGetCursor() const;

		/// <summary>
		/// Returns if the Text Entry mode is enabled
		/// </summary>
		/// <returns>True/False</returns>
		bool IsTextEntryEnabled() const;

	private:

		/// <summary>
		/// Updated the text entry buffer with any new text
		/// </summary>
		void UpdateTextEntry();

	public:

		// Experimental Lightweight 3D Routines ================
#ifdef OLC_ENABLE_EXPERIMENTAL
		// Set Manual View Matrix
		void LW3D_View(const std::array<float, 16>& m);
		// Set Manual World Matrix
		void LW3D_World(const std::array<float, 16>& m);
		// Set Manual Projection Matrix
		void LW3D_Projection(const std::array<float, 16>& m);

		// Draws a vector of vertices, interprted as individual triangles
		void LW3D_DrawTriangles(olc::Decal* decal, const std::vector<std::array<float, 3>>& pos, const std::vector<olc::vf2d>& tex, const std::vector<olc::Pixel>& col);

		void LW3D_ModelTranslate(const float x, const float y, const float z);

		// Camera convenience functions
		void LW3D_SetCameraAtTarget(const float fEyeX, const float fEyeY, const float fEyeZ,
			const float fTargetX, const float fTargetY, const float fTargetZ,
			const float fUpX = 0.0f, const float fUpY = 1.0f, const float fUpZ = 0.0f);
		void LW3D_SetCameraAlongDirection(const float fEyeX, const float fEyeY, const float fEyeZ,
			const float fDirX, const float fDirY, const float fDirZ,
			const float fUpX = 0.0f, const float fUpY = 1.0f, const float fUpZ = 0.0f);

		// 3D Rendering Flags
		void LW3D_EnableDepthTest(const bool bEnableDepth);
		void LW3D_EnableBackfaceCulling(const bool bEnableCull);
#endif
	public: // Branding
		/// <summary>
		/// Your Amazing PGE Mobile Game NAME!
		/// </summary>
		std::string sAppName;


	private: // Inner mysterious workings
		olc::Sprite* pDrawTarget = nullptr;
		Pixel::Mode	nPixelMode = Pixel::NORMAL;
		float		fBlendFactor = 1.0f;
		olc::vi2d	vScreenSize = { 256, 240 };
		olc::vf2d	vInvScreenSize = { 1.0f / 256.0f, 1.0f / 240.0f };
		olc::vi2d	vPixelSize = { 4, 4 };
		olc::vi2d   vScreenPixelSize = { 4, 4 };
		olc::vi2d	vMousePos = { 0, 0 };
		olc::vi2d	vTouchPos = { 0, 0 };
		int32_t		nMouseWheelDelta = 0;
		olc::vi2d	vMousePosCache = { 0, 0 };
		olc::vi2d   vMouseWindowPos = { 0, 0 };
		int32_t		nMouseWheelDeltaCache = 0;
		olc::vi2d	vWindowSize = { 0, 0 };
		olc::vi2d	vViewPos = { 0, 0 };
		olc::vi2d	vViewSize = { 0,0 };
		bool		bFullScreen = false;
		olc::vf2d	vPixel = { 1.0f, 1.0f };
		bool		bHasInputFocus = false;
		bool		bHasMouseFocus = false;
		bool		bHasTouchFocus = false;
		bool		bEnableVSYNC = false;
		float		fFrameTimer = 1.0f;
		float		fLastElapsed = 0.0f;
		int			nFrameCount = 0;
		bool bSuspendTextureTransfer = false;
		Renderable  fontRenderable;
		std::vector<LayerDesc> vLayers;
		uint8_t		nTargetLayer = 0;
		uint32_t	nLastFPS = 0;
		bool        bPixelCohesion = false;
		DecalMode   nDecalMode = DecalMode::NORMAL;
		DecalStructure nDecalStructure = DecalStructure::FAN;
		std::function<olc::Pixel(const int x, const int y, const olc::Pixel&, const olc::Pixel&)> funcPixelMode;
		std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
		std::vector<olc::vi2d> vFontSpacing;
		std::vector<std::string> vDroppedFiles;
		std::vector<std::string> vDroppedFilesCache;
		olc::vi2d vDroppedFilesPoint;
		olc::vi2d vDroppedFilesPointCache;

		// Text Entry Specific
		bool bTextEntryEnable = false;
		std::string sTextEntryString = "";
		int32_t nTextEntryCursor = 0;

		std::vector<std::tuple<olc::Key, std::string, std::string>> vKeyboardMap;

		// State of keyboard		
		bool		pKeyNewState[256] = { 0 };
		bool		pKeyOldState[256] = { 0 };
		HWButton	pKeyboardState[256]; // = { {0} }; // Make complier happy

		// State of mouse
		bool		pMouseNewState[nMouseButtons] = { 0 };
		bool		pMouseOldState[nMouseButtons] = { 0 };
		HWButton	pMouseState[nMouseButtons]; // = { {0} }; // Make complier happy


		// State of touch
		bool		pTouchNewState[__UINT8_MAX__] = { 0 };
		bool		pTouchNewStateCache[__UINT8_MAX__] = { 0 };
		bool		pTouchOldState[__UINT8_MAX__] = { 0 };
		HWButton	pTouchState[__UINT8_MAX__]; // = { {0} }; // Make complier happy
		olc::vi2d	pTouchPoints[__UINT8_MAX__];
		olc::vi2d	pTouchPointsCache[__UINT8_MAX__];

		std::mutex mutexTouchPoints;

		// The main engine thread
		void		EngineThread();


		/// <summary>
		/// If anything sets this flag to false, the engine "should" shut down gracefully
		/// </summary>
		static std::atomic<bool> bAtomActive;


		/// <summary>
		/// Display CopyRight Splash Screen
		/// This can be disabled in DEBUG mode only
		/// Will always be enabled in RELEASE mode
		/// I don't make the rulez folks
		/// </summary>
		bool bDisplayCopyRight = true;

	private:
		// CopyRight Stuff Do Not Remove

		olc::Renderable sprCR;
		std::vector<std::pair<olc::vf2d, olc::vf2d>> vBoomCR;
		olc::vf2d vScaleCR;
		olc::vf2d vPositionCR;
		float fParticleTimeCR = 0.0f;
		float fAspectCR = 0.0f;
		bool bCompleteCR = false;
		void CreateCRSprite();
		bool DisplayCR(float& fElapsedTime);


	public:

		/// <summary>
		/// The OS Engine Instance Struct
		/// </summary>
		OSEngineInstance pOsEngine;

	public:
		// "Break In" Functions

		/// <summary>
		/// Updates the current mouse position
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		void olc_UpdateMouse(int32_t x, int32_t y);

		/// <summary>
		/// Updates the current touch position
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		void olc_UpdateTouch(int32_t x, int32_t y, int32_t index);

		/// <summary>
		/// Update the mouse scroll wheel position
		/// </summary>
		/// <param name="delta">new Delta position</param>
		void olc_UpdateMouseWheel(int32_t delta);

		/// <summary>
		/// Update the Window Size
		/// </summary>
		/// <param name="x">Position x</param>
		/// <param name="y">Position y</param>
		void olc_UpdateWindowSize(int32_t x, int32_t y);

		/// <summary>
		/// Update the OpenGLES View Port
		/// </summary>
		void olc_UpdateViewport();

		/// <summary>
		/// Construct and create the font sheet for text display
		/// </summary>
		void olc_ConstructFontSheet();

		/// <summary>
		/// Update the core, draws the frame to the screen folks
		/// </summary>
		void olc_CoreUpdate();

		/// <summary>
		/// Perpare the OpenGLES Engine
		/// </summary>
		void olc_PrepareEngine();

		/// <summary>
		/// Update the mouse button state
		/// </summary>
		/// <param name="button">0, 1, 2,</param>
		/// <param name="state">State</param>
		void olc_UpdateMouseState(int32_t button, bool state);

		/// <summary>
		/// Update the touch state
		/// </summary>
		/// <param name="touch">Up to 5 touch points</param>
		/// <param name="state">State,</param>
		void olc_UpdateTouchState(int32_t touchPoint, bool state);

		/// <summary>
		/// Updates the olc Sensor Structs with repective events
		/// NOTE: This method is called from EngineThread before the next frame is drawn
		/// </summary>
		/// <param name="event">ASensorEvent event</param>
		void olc_UpdateSensorEvent(ASensorEvent event);

		/// <summary>
		/// Update the Key Stage
		/// </summary>
		/// <param name="key">int Key Value</param>
		/// <param name="state">State</param>
		void olc_UpdateKeyState(int32_t key, bool state);

		/// <summary>
		/// Update mouse focus
		/// </summary>
		/// <param name="state">true/false</param>
		void olc_UpdateMouseFocus(bool state);

		/// <summary>
		/// Update the touch focus
		/// </summary>
		/// <param name="state">true/false</param>
		void olc_UpdateTouchFocus(bool state);

		/// <summary>
		/// Update key focus
		/// </summary>
		/// <param name="state">true/false</param>
		void olc_UpdateKeyFocus(bool state);

		/// <summary>
		/// Tell the OpenGLES Engine & PGE Engine its time to shutdown
		/// </summary>
		void olc_Terminate();

		/// <summary>
		/// Update the position where files are dropped 
		/// </summary>
		/// <param name="x">Position y</param>
		/// <param name="y">Position y</param>
		/// <param name="vFiles">Vector of files</param>
		void olc_DropFiles(int32_t x, int32_t y, const std::vector<std::string>& vFiles);

		/// <summary>
		/// Request the OpenGLES/PGE engine to reanimate
		/// </summary>
		void olc_Reanimate();

		/// <summary>
		/// Returns if the PGE is running
		/// </summary>
		/// <returns></returns>
		bool olc_IsRunning();

		/// <summary>
		/// At the very end of this file, chooses which components to compile
		/// </summary>
		virtual void olc_ConfigureSystem();

	public:
		/// <summary>
		/// Load a file from the Assets APK into the passed buffer
		/// </summary>
		/// <param name="sFilePath">Full file path name excudling the assets dir: Example: "images/test.png" "maps/example1.city"</param>
		/// <param name="outbuffer">A pointer to a clear buffer. Buffer will be populated and returned</param>
		/// <returns>FAIL = 0, OK = 1, NO_FILE = -1, and outBuffer</returns>
		olc::rcode app_LoadFileFromAssets(const std::string& sFilePath, std::vector<char>* outBuffer);

		/// <summary>
		/// Extracts a compressed file from the assests APK to a depcompressed app storage file
		/// </summary>
		/// <param name="sAssetFilePath">Full assets file path name excudling the assets dir: Example: "images/test.png" "maps/example1.city"</param>
		/// <param name="sAppStorageFilePath">Full app storage path. Use app_GetInternalAppStorage(), app_GetExteralAppStorage() and app_GetPublicAppStorage() to get the storage path</param>
		/// <returns>FAIL = 0, OK = 1, NO_FILE = -1,</returns>
		olc::rcode app_ExtractFileFromAssets(const std::string& sAssetFilePath, const std::string& sAppStorageFilePath);

		/// <summary>
		/// Get the App Internal storage path where you can save,  editing, deleting files
		/// Internal Storage is private and non volatile
		/// RECOMMANDED: Use this storage for saving, editing, deleting files
		/// </summary>
		/// <returns>The full Android/iOS path to internal storage. FAIL: NULL</returns>
		const char* app_GetInternalAppStorage();

		/// <summary>
		/// Get the App Exteral storage where you can save files
		/// WARNING: MAY NOT EXIST. May be volatile
		/// </summary>
		/// <returns>SUCCESS: The full Android/iOS path to external storage. FAIL: NULL</returns>
		const char* app_GetExteralAppStorage();

		/// <summary>
		/// Get the App public storage where you can save files
		/// WARNING: MAY NOT EXIST. May be volatile
		/// NOTE: Android will default to the \obb\com.AppName, iOS TBA
		/// </summary>
		/// <returns>SUCCESS: The full Android/iOS path to external storage. FAIL: NULL</returns>
		const char* app_GetPublicAppStorage();



	public: // PGEX Stuff
		friend class PGEX;

		/// <summary>
		/// Register your PGE Extensions
		/// </summary>
		/// <param name="pgex"></param>
		void pgex_Register(olc::PGEX* pgex);



	private:
		std::vector<olc::PGEX*> vExtensions;
	};



	// O------------------------------------------------------------------------------O
	// | PGE EXTENSION BASE CLASS - Permits access to PGE functions from extension    |
	// O------------------------------------------------------------------------------O
	class PGEX
	{
		friend class olc::PixelGameEngine;
	public:
		PGEX(bool bHook = false);

	protected:
		virtual void OnBeforeUserCreate();
		virtual void OnAfterUserCreate();
		virtual bool OnBeforeUserUpdate(float& fElapsedTime);
		virtual void OnAfterUserUpdate(float fElapsedTime);

	protected:
		static PixelGameEngine* pge;
	};

#ifdef __ANDROID__

	class EventManager
	{
	public:
		static EventManager& getInstance();

		enum EventResult {

			RELEASED = 0,	// The event was not handled and released back to the OS
			CAPTURED = 1	// The event was captured and handled
		};

		/// <summary>
		/// Handles Commands requests from the Android/iOS
		/// See Android_native_app_glue.h or iOS_app_glue.h
		/// </summary>
		/// <param name="app">AndroidApp* or iOSApp*</param>
		/// <param name="cmd">OS Commands</param>
		static void HandleCommand(struct android_app* app, int32_t cmd);

		/// <summary>
		/// Manages the input events for, Keyboard, touch and mouse
		/// NOTE: If you use the event you MUST return CAPTURED
		/// If you do not use the event you MUST return RELEASED
		/// </summary>
		/// <param name="app">AndroidApp* or iOSApp*</param>
		/// <param name="event">Input Events</param>
		/// <returns>RELEASED, CAPTURED </returns>
		static int32_t HandleInput(struct android_app* app, AInputEvent* event);

		/// <summary>
		/// Event fired from OS when app is to be destroyed
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onDestroy(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when app Staring
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onStart(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when app is resuming from some paused state, i.e. phone call, etc etc.
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onResume(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when a SaveState is required as the app is going into limp mode
		/// I.E. the app has lost focus, paused, swiped to close etc
		/// </summary>
		/// <param name="activity">Native Activity</param>
		/// <param name="outLen">Length of save state to place in buffer</param>
		/// <returns>Length of save state buffer</returns>
		static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen);

		/// <summary>
		/// Event fired from OS when a pause is about to occur
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onPause(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when the before the App is to be stopped
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onStop(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when configuration of the app has changed
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onConfigurationChanged(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when your app is using to much memory. 
		/// WARNING: you need to clear memory fast, otherwise Event onStop will be fired.
		/// </summary>
		/// <param name="activity">Native Activity</param>
		static void onLowMemory(ANativeActivity* activity);

		/// <summary>
		/// Event fired from OS when the app gains/loses focus, i.e. Phone call
		/// </summary>
		/// <param name="activity">Native Activity</param>
		/// <param name="focused">Gain: 1, lost: 0</param>
		static void onWindowFocusChanged(ANativeActivity* activity, int focused);

		/// <summary>
		/// Event fired from OS when your Window for your app is created
		/// </summary>
		/// <param name="activity">Native Activity</param>
		/// <param name="window">Native Window</param>
		static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);

		/// <summary>
		/// Event fired from OS when your Window for your app is destroyed
		/// </summary>
		/// <param name="activity">Native Activity</param>
		/// <param name="window">Native Window</param>
		static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);

		/// <summary>
		/// Event fired from OS when the input queue for Keyboard, Mouse and Touch are ready
		/// </summary>
		/// <param name="activity">Native Activity</param>
		/// <param name="queue">Input queue</param>
		static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);

		/// <summary>
		/// Event fired from OS when the input queue for Keyboard, Mouse and Touch are destroyed
		/// </summary>
		/// <param name="activity">Native Activity</param>
		/// <param name="queue">Input queue</param>
		static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);


		~EventManager();
	private:
		EventManager();
		EventManager(EventManager const&);
		void operator=(EventManager const&);

	};
#endif // __ANDROID__

#ifdef __APPLE__

	class EventManager
	{
	public:
		static EventManager& getInstance();
		enum EventResult {

			RELEASED = 0,	// The event was not handled and released back to the OS
			CAPTURED = 1	// The event was captured and handled
		};

		static void HandleCommand(int32_t cmd);
		static int32_t HandleInput(int32_t tbd);

		static void onDestroy();
		static void onStart();
		static void onResume();
		static void* onSaveInstanceState();
		static void onPause();
		static void onStop();
		static void onConfigurationChanged();
		static void onLowMemory();
		static void onWindowFocusChanged();
		static void onNativeWindowCreated();
		static void onNativeWindowDestroyed();
		static void onInputQueueCreated();
		static void onInputQueueDestroyed();
		~EventManager();
	private:
		EventManager();
		EventManager(EventManager const&);
		void operator=(EventManager const&);
	};


#endif // __APPLE__

}

#pragma endregion
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region opengl33_iface
/*
	TBA Place holder. Using this interface will be great
	but it may be more work than is needed
	OpenGLES does not have the same POWER! as OpenGL 3.3
*/


#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>
#define CALLSTYLE
typedef EGLBoolean(locSwapInterval_t)(EGLDisplay display, EGLint interval);
#define GL_CLAMP GL_CLAMP_TO_EDGE
#define OGL_LOAD(t, n) n;

#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#define CALLSTYLE
#define OGL_LOAD(t, n) n;
#endif


namespace olc
{
	typedef char GLchar;
	//typedef ptrdiff_t GLsizeiptr;

	typedef GLuint CALLSTYLE  locCreateShader_t(GLenum type);
	typedef GLuint CALLSTYLE locCreateProgram_t(void);
	typedef void CALLSTYLE locDeleteShader_t(GLuint shader);
	typedef void CALLSTYLE locCompileShader_t(GLuint shader);
	typedef void CALLSTYLE locLinkProgram_t(GLuint program);
	typedef void CALLSTYLE locDeleteProgram_t(GLuint program);
	typedef void CALLSTYLE locAttachShader_t(GLuint program, GLuint shader);
	typedef void CALLSTYLE locBindBuffer_t(GLenum target, GLuint buffer);
	typedef void CALLSTYLE locBufferData_t(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	typedef void CALLSTYLE locGenBuffers_t(GLsizei n, GLuint* buffers);
	typedef void CALLSTYLE locVertexAttribPointer_t(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	typedef void CALLSTYLE locEnableVertexAttribArray_t(GLuint index);
	typedef void CALLSTYLE locUseProgram_t(GLuint program);
	typedef void CALLSTYLE locBindVertexArray_t(GLuint array);
	typedef void CALLSTYLE locGenVertexArrays_t(GLsizei n, GLuint* arrays);
	typedef void CALLSTYLE locGetShaderInfoLog_t(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
	typedef GLint CALLSTYLE locGetUniformLocation_t(GLuint program, const GLchar* name);
	typedef void CALLSTYLE locUniform1f_t(GLint location, GLfloat v0);
	typedef void CALLSTYLE locUniform1i_t(GLint location, GLint v0);
	typedef void CALLSTYLE locUniform2fv_t(GLint location, GLsizei count, const GLfloat* value);
	typedef void CALLSTYLE locActiveTexture_t(GLenum texture);
	typedef void CALLSTYLE locGenFrameBuffers_t(GLsizei n, GLuint* ids);
	typedef void CALLSTYLE locBindFrameBuffer_t(GLenum target, GLuint fb);
	typedef GLenum CALLSTYLE locCheckFrameBufferStatus_t(GLenum target);
	typedef void CALLSTYLE locDeleteFrameBuffers_t(GLsizei n, const GLuint* fbs);
	typedef void CALLSTYLE locFrameBufferTexture2D_t(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	typedef void CALLSTYLE locDrawBuffers_t(GLsizei n, const GLenum* bufs);
	typedef void CALLSTYLE locBlendFuncSeparate_t(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);

#if defined(__ANDROID__)
	typedef void CALLSTYLE locShaderSource_t(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
	typedef EGLBoolean(locSwapInterval_t)(EGLDisplay display, EGLint interval);
#else
	//typedef void CALLSTYLE locShaderSource_t(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
#endif




}


#pragma endregion
#pragma GCC diagnostic pop

#endif /* defined(OLC_PGE_DEF) */



/*------------------------------------------------------------------------------------*/
/* Now the fun stuff*/

// O------------------------------------------------------------------------------O
// | START OF OLC_PGE_APPLICATION                                                 |
// O------------------------------------------------------------------------------O
#ifdef OLC_PGE_APPLICATION
#undef OLC_PGE_APPLICATION

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INTERFACE IMPLEMENTATION (CORE)                           |
// | Note: The core implementation is platform independent                        |
// O------------------------------------------------------------------------------O
//#pragma region pge_implementation

namespace olc {

	// O------------------------------------------------------------------------------O
	// | olc::Pixel IMPLEMENTATION                                                    |
	// O------------------------------------------------------------------------------O
	Pixel::Pixel()
	{
		r = 0; g = 0; b = 0; a = nDefaultAlpha;
	}

	Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	{
		n = red | (green << 8) | (blue << 16) | (alpha << 24);
	} // Thanks jarekpelczar 

	Pixel::Pixel(uint32_t p)
	{
		n = p;
	}

	bool Pixel::operator==(const Pixel& p) const
	{
		return n == p.n;
	}

	bool Pixel::operator!=(const Pixel& p) const
	{
		return n != p.n;
	}

	Pixel  Pixel::operator * (const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, float(r) * i));
		float fG = std::min(255.0f, std::max(0.0f, float(g) * i));
		float fB = std::min(255.0f, std::max(0.0f, float(b) * i));
		return Pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
	}

	Pixel  Pixel::operator / (const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, float(r) / i));
		float fG = std::min(255.0f, std::max(0.0f, float(g) / i));
		float fB = std::min(255.0f, std::max(0.0f, float(b) / i));
		return Pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
	}

	Pixel& Pixel::operator *=(const float i)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * i)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * i)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * i)));
		return *this;
	}

	Pixel& Pixel::operator /=(const float i)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) / i)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) / i)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) / i)));
		return *this;
	}

	Pixel  Pixel::operator + (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, int(r) + int(p.r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, int(g) + int(p.g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, int(b) + int(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel  Pixel::operator - (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, int(r) - int(p.r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, int(g) - int(p.g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, int(b) - int(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel& Pixel::operator += (const Pixel& p)
	{
		this->r = uint8_t(std::min(255, std::max(0, int(r) + int(p.r))));
		this->g = uint8_t(std::min(255, std::max(0, int(g) + int(p.g))));
		this->b = uint8_t(std::min(255, std::max(0, int(b) + int(p.b))));
		return *this;
	}

	Pixel& Pixel::operator -= (const Pixel& p) // Thanks Au Lit
	{
		this->r = uint8_t(std::min(255, std::max(0, int(r) - int(p.r))));
		this->g = uint8_t(std::min(255, std::max(0, int(g) - int(p.g))));
		this->b = uint8_t(std::min(255, std::max(0, int(b) - int(p.b))));
		return *this;
	}

	Pixel Pixel::operator * (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * float(p.r) / 255.0f)));
		uint8_t nG = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * float(p.g) / 255.0f)));
		uint8_t nB = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * float(p.b) / 255.0f)));
		uint8_t nA = uint8_t(std::min(255.0f, std::max(0.0f, float(a) * float(p.a) / 255.0f)));
		return Pixel(nR, nG, nB, nA);
	}

	Pixel& Pixel::operator *=(const Pixel& p)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * float(p.r) / 255.0f)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * float(p.g) / 255.0f)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * float(p.b) / 255.0f)));
		this->a = uint8_t(std::min(255.0f, std::max(0.0f, float(a) * float(p.a) / 255.0f)));
		return *this;
	}

	Pixel Pixel::inv() const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, 255 - int(r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, 255 - int(g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, 255 - int(b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel PixelF(float red, float green, float blue, float alpha)
	{
		return Pixel(uint8_t(red * 255.0f), uint8_t(green * 255.0f), uint8_t(blue * 255.0f), uint8_t(alpha * 255.0f));
	}

	Pixel PixelLerp(const olc::Pixel& p1, const olc::Pixel& p2, float t)
	{
		return (p2 * t) + p1 * (1.0f - t);
	}

	// O------------------------------------------------------------------------------O
	// | olc::Sprite - An image represented by a 2D array of olc::Pixel               |
	// O------------------------------------------------------------------------------O
	Sprite::Sprite()
	{
		width = 0; height = 0;
	}

	Sprite::Sprite(const std::string& sImageFile, olc::ResourcePack* pack)
	{
		LoadFromFile(sImageFile, pack);
	}

	Sprite::Sprite(int32_t w, int32_t h)
	{
		width = w; height = h;
		pColData.resize(width * height);
		pColData.resize(width * height, nDefaultPixel);
	}

	Sprite::~Sprite()
	{
		// John Galvin, Ensures no memory leak should 'Store Sub Sprites' have sprites
		// TODO: We need to look at using Smart Pointers here, to better manage this
		for (int i = 0; i < vecSubSprites.size(); i++)
		{
			Sprite* spr = std::get<4>(vecSubSprites[i]);
			spr->pColData.clear();
		}

		pColData.clear();
	}

	olc::rcode Sprite::LoadFromFile(const std::string& sImageFile, olc::ResourcePack* pack)
	{
		UNUSED(pack);
		return loader->LoadImageResource(this, sImageFile, pack);

	}

	void Sprite::SetSampleMode(olc::Sprite::Mode mode)
	{
		modeSample = mode;
	}

	Pixel Sprite::GetPixel(const olc::vi2d& a) const
	{
		return GetPixel(a.x, a.y);
	}

	bool Sprite::SetPixel(const olc::vi2d& a, Pixel p)
	{
		return SetPixel(a.x, a.y, p);
	}

	Pixel Sprite::GetPixel(int32_t x, int32_t y) const
	{
		if (modeSample == olc::Sprite::Mode::NORMAL)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
				return pColData[y * width + x];
			else
				return Pixel(0, 0, 0, 0);
		}
		else
		{
			if (modeSample == olc::Sprite::Mode::PERIODIC)
				return pColData[abs(y % height) * width + abs(x % width)];
			else
				return pColData[std::max(0, std::min(y, height - 1)) * width + std::max(0, std::min(x, width - 1))];
		}

	}

	bool Sprite::SetPixel(int32_t x, int32_t y, Pixel p)
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			pColData[y * width + x] = p;
			return true;
		}
		else
			return false;
	}


	Pixel Sprite::Sample(float x, float y) const
	{
		int32_t sx = std::min((int32_t)((x * (float)width)), width - 1);
		int32_t sy = std::min((int32_t)((y * (float)height)), height - 1);
		return GetPixel(sx, sy);
	}

	Pixel Sprite::Sample(const olc::vf2d& uv) const
	{
		return Sample(uv.x, uv.y);
	}

	Pixel Sprite::SampleBL(float u, float v) const
	{
		u = u * width - 0.5f;
		v = v * height - 0.5f;
		int x = (int)floor(u); // cast to int rounds toward zero, not downward
		int y = (int)floor(v); // Thanks @joshinils
		float u_ratio = u - x;
		float v_ratio = v - y;
		float u_opposite = 1 - u_ratio;
		float v_opposite = 1 - v_ratio;

		olc::Pixel p1 = GetPixel(std::max(x, 0), std::max(y, 0));
		olc::Pixel p2 = GetPixel(std::min(x + 1, (int)width - 1), std::max(y, 0));
		olc::Pixel p3 = GetPixel(std::max(x, 0), std::min(y + 1, (int)height - 1));
		olc::Pixel p4 = GetPixel(std::min(x + 1, (int)width - 1), std::min(y + 1, (int)height - 1));

		return olc::Pixel(
			(uint8_t)((p1.r * u_opposite + p2.r * u_ratio) * v_opposite + (p3.r * u_opposite + p4.r * u_ratio) * v_ratio),
			(uint8_t)((p1.g * u_opposite + p2.g * u_ratio) * v_opposite + (p3.g * u_opposite + p4.g * u_ratio) * v_ratio),
			(uint8_t)((p1.b * u_opposite + p2.b * u_ratio) * v_opposite + (p3.b * u_opposite + p4.b * u_ratio) * v_ratio));
	}

	Pixel Sprite::SampleBL(const olc::vf2d& uv) const
	{
		return SampleBL(uv.x, uv.y);
	}

	Pixel* Sprite::GetData()
	{
		return pColData.data();
	}

	olc::Sprite* Sprite::Duplicate()
	{
		return simddrawer->Duplicate_SIMD(this);
	}

	olc::Sprite* Sprite::Duplicate(const olc::vi2d& vPos, const olc::vi2d& vSize)
	{
		return simddrawer->Duplicate_SIMD(vPos, vSize, this);
	}

	olc::Sprite* Sprite::Duplicate(olc::Sprite::Flip flip)
	{
		return simddrawer->Duplicate_SIMD((olc::Sprite::Flip)flip, this);
	}

	olc::Sprite* Sprite::Duplicate(uint32_t scale)
	{
		return simddrawer->Duplicate_SIMD((uint32_t)scale, this);
	}

	olc::Sprite* Sprite::DuplicateMerge(const olc::vi2d& vTargetPos, olc::Sprite* pTargetSprite, olc::Pixel p)
	{
		// OK as we are create a new merge sprite we need to protect the existing sprites
		olc::Sprite* pMergeSprite = pTargetSprite->Duplicate();

		// Get the new sprite
		return simddrawer->DuplicateMerge_SIMD(vTargetPos, pMergeSprite, p, this);

	}

	olc::vi2d Sprite::Size() const
	{
		return { width, height };
	}


	olc::Sprite* Sprite::GetStoredSubSprite(olc::vi2d vStartPos, olc::vi2d vSize, uint32_t scale, olc::Sprite::Flip flip, Sprite* pDrawTarget)
	{
		// Pre Checks
		if (maxSubSprites < 1) return nullptr;
		scale = (scale <= 1) ? 1 : scale;
		if (vSize.x < 1 || vSize.y < 1) return nullptr;

		olc::Sprite* spr = nullptr;

		for (int i = 0; i < vecSubSprites.size(); i++)
		{
			if (std::get<0>(vecSubSprites[i]) == vStartPos
				&& std::get<1>(vecSubSprites[i]) == vSize
				&& std::get<2>(vecSubSprites[i]) == scale
				&& std::get<3>(vecSubSprites[i]) == flip
				&& std::get<6>(vecSubSprites[i]) == pDrawTarget)
			{
				// found it, break and return the sprite
				spr = std::get<4>(vecSubSprites[i]);
				break;
			}
		}

		return spr;
	}

	void* Sprite::GetStoredSubDecal(olc::vi2d vStartPos, olc::vi2d vSize, uint32_t scale, olc::Sprite::Flip flip, Sprite* pDrawTarget)
	{
		// Pre Checks
		if (maxSubSprites < 1) return nullptr;
		scale = (scale <= 1) ? 1 : scale;
		if (vSize.x < 1 || vSize.y < 1) return nullptr;

		void* dec = nullptr;

		for (int i = 0; i < vecSubSprites.size(); i++)
		{
			if (std::get<0>(vecSubSprites[i]) == vStartPos
				&& std::get<1>(vecSubSprites[i]) == vSize
				&& std::get<2>(vecSubSprites[i]) == scale
				&& std::get<3>(vecSubSprites[i]) == flip
				&& std::get<6>(vecSubSprites[i]) == pDrawTarget)
			{
				// Found it, break and return the decal
				dec = std::get<7>(vecSubSprites[i]);

				break;
			}
		}

		return dec;
	}

	size_t Sprite::GetStoredSubSprite_id(olc::Sprite* pSubSprite)
	{
		// Pre Checks
		if (maxSubSprites < 1) return -1;
		if (pSubSprite == nullptr) return -1;
		size_t id = -1;

		for (size_t i = 0; i < vecSubSprites.size(); i++)
		{
			if (std::get<4>(vecSubSprites[i]) == pSubSprite || std::get<6>(vecSubSprites[i]) == pSubSprite)
			{
				// Found it, break and return the sprite
				id = std::get<5>(vecSubSprites[i]);
				break;
			}
		}

		return id;

	}

	olc::Sprite* Sprite::GetStoredSubSprite(size_t id)
	{
		// Pre Checks
		if (maxSubSprites < 1) return nullptr;
		if (id < 0) return nullptr;
		if (id > vecSubSprites.size()) return nullptr;

		olc::Sprite* spr = nullptr;

		for (size_t i = 0; i < vecSubSprites.size(); i++)
		{
			if (std::get<5>(vecSubSprites[i]) == id)
			{
				// Found it, break and return the sprite
				spr = std::get<4>(vecSubSprites[i]);
				break;
			}
		}

		return spr;

	}

	uint32_t Sprite::GetMaxSubSprite()
	{
		return maxSubSprites;
	}

	bool Sprite::IsSubSpritesFull()
	{
		return bIsSubSpritesFull;
	}

	void Sprite::SetMaxSubSpriteCount(uint32_t max)
	{
		// PreChecks
		if (max < 0) max = 0;
		if (max < vecSubSprites.size())
		{
			ClearSubSprites(max);
		}

		maxSubSprites = max;
	}

	void Sprite::ClearSubSprites()
	{
		// Pre Checks
		if (vecSubSprites.size() < 1) return;

		for (size_t i = 0; i < vecSubSprites.size(); i++)
		{
			delete (olc::Sprite*)std::get<4>(vecSubSprites[i]);
			delete (olc::Decal*)std::get<7>(vecSubSprites[i]);
		}

		vecSubSprites.clear();


	}

	void Sprite::ClearSubSprites(size_t start)
	{
		ClearSubSprites(start, vecSubSprites.size());
	}

	void Sprite::ClearSubSprites(size_t start, size_t end)
	{
		// Pre Checks
		if (vecSubSprites.size() < 1) return;
		if (start > end) std::swap(start, end);
		if (start < 0) start = 0;
		if (end >= vecSubSprites.size()) end = vecSubSprites.size() - 1;

		for (size_t i = end; i >= start; i--)
		{
			delete (olc::Sprite*)std::get<4>(vecSubSprites[i]);
			delete (olc::Decal*)std::get<7>(vecSubSprites[i]);
			vecSubSprites.erase(vecSubSprites.begin() + i);
		}

		vecSubSprites.resize(start);

	}

	bool Sprite::StoreSubSprite(olc::Sprite* pSubSprite, olc::vi2d vStartPos,
		uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget)
	{
		// Pre-checks
		if (maxSubSprites < 1) return false;
		if (pSubSprite == nullptr) return false;
		olc::vi2d vSize = { pSubSprite->width, pSubSprite->height };
		if (vSize.x < 1 || vSize.y < 1) return false;

		// Check if the subsprite is already there
		for (int i = 0; i < vecSubSprites.size(); i++)
		{
			if (std::get<0>(vecSubSprites[i]) == vStartPos
				&& std::get<1>(vecSubSprites[i]) == vSize
				&& std::get<2>(vecSubSprites[i]) == scale
				&& std::get<3>(vecSubSprites[i]) == flip
				&& std::get<4>(vecSubSprites[i]) == pDrawTarget)
			{
				// We found a match nothing to do but return
				return true;
				break;
			}
		}

		// Manage Store Sub Sprites to ensure no memory leak
		size_t max = maxSubSprites;
		bIsSubSpritesFull = false;
		if (vecSubSprites.size() >= max)
		{
			bIsSubSpritesFull = true;
			return false;
		}

		size_t id = vecSubSprites.size();

		olc::Decal* pSubDecal = new olc::Decal(pSubSprite);
		pSubDecal->UpdateSprite();
		vecSubSprites.push_back({ vStartPos, vSize, scale, flip, pSubSprite, id, pDrawTarget, pSubDecal });

		return true;
	}

	// O------------------------------------------------------------------------------O
	// | olc::Decal IMPLEMENTATION                                                    |
	// O------------------------------------------------------------------------------O
	Decal::Decal(olc::Sprite* spr, bool filter, bool clamp)
	{
		id = -1;
		if (spr == nullptr) return;
		sprite = spr;
		id = renderer->CreateTexture(sprite->width, sprite->height, filter, clamp);
		Update();
	}

	Decal::Decal(const uint32_t nExistingTextureResource, olc::Sprite* spr)
	{
		if (spr == nullptr) return;
		id = nExistingTextureResource;
	}

	void Decal::Update()
	{
		if (sprite == nullptr) return;
		vUVScale = { 1.0f / float(sprite->width), 1.0f / float(sprite->height) };
		renderer->ApplyTexture(id);
		renderer->UpdateTexture(id, sprite);
	}

	void Decal::UpdateSprite()
	{
		if (sprite == nullptr) return;
		renderer->ApplyTexture(id);
		renderer->ReadTexture(id, sprite);
	}

	Decal::~Decal()
	{
		if (id != -1)
		{
			renderer->DeleteTexture(id);
			id = -1;
		}
	}

	void Renderable::Create(uint32_t width, uint32_t height, bool filter, bool clamp)
	{
		pSprite = std::make_unique<olc::Sprite>(width, height);
		pDecal = std::make_unique<olc::Decal>(pSprite.get(), filter, clamp);
	}

	olc::rcode Renderable::Load(const std::string& sFile, ResourcePack* pack, bool filter, bool clamp)
	{
		pSprite = std::make_unique<olc::Sprite>();
		if (pSprite->LoadFromFile(sFile, pack) == olc::rcode::OK)
		{
			pDecal = std::make_unique<olc::Decal>(pSprite.get(), filter, clamp);
			return olc::rcode::OK;
		}
		else
		{
			pSprite.release();
			pSprite = nullptr;
			return olc::rcode::NO_FILE;
		}
	}

	olc::Decal* Renderable::Decal() const
	{
		return pDecal.get();
	}

	olc::Sprite* Renderable::Sprite() const
	{
		return pSprite.get();
	}



	// O------------------------------------------------------------------------------O
	// | olc::PixelGameEngine IMPLEMENTATION                                          |
	// O------------------------------------------------------------------------------O
	PixelGameEngine::PixelGameEngine()
	{
		sAppName = "Undefined";
		olc::PGEX::pge = this;

		olc_ConfigureSystem();


	}

	PixelGameEngine::~PixelGameEngine()
	{}


	olc::rcode PixelGameEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync, bool cohesion)
	{

		bPixelCohesion = cohesion;

		screen_h = screen_h / pixel_h;
		screen_w = screen_w / pixel_w;
		vScreenSize = { screen_w, screen_h };

		vInvScreenSize = { 1.0f / float(screen_w), 1.0f / float(screen_h) };
		vPixelSize = { pixel_w, pixel_h };

		vWindowSize = vScreenSize * vPixelSize;
		bFullScreen = full_screen;
		bEnableVSYNC = vsync;
		vPixel = 2.0f / vScreenSize;

		if (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0)
			return olc::FAIL;

		return olc::OK;
	}


	void PixelGameEngine::SetScreenSize(int w, int h)
	{
		vScreenSize = { w, h };
		vInvScreenSize = { 1.0f / float(w), 1.0f / float(h) };
		for (auto& layer : vLayers)
		{
			layer.pDrawTarget.Create(vScreenSize.x, vScreenSize.y);
			layer.bUpdate = true;
		}
		SetDrawTarget(nullptr);
		renderer->ClearBuffer(olc::BLACK, true);
		renderer->DisplayFrame();
		renderer->ClearBuffer(olc::BLACK, true);
		renderer->UpdateViewport(vViewPos, vViewSize);
	}

#if !defined(PGE_USE_CUSTOM_START)
	olc::rcode PixelGameEngine::Start()
	{


		if (platform->ApplicationStartUp() != olc::OK) return olc::FAIL;

		// Construct the window
		if (platform->CreateWindowPane({ 0, 0 }, vWindowSize, bFullScreen) != olc::OK) return olc::FAIL;
		olc_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

		// Start the thread
		bAtomActive = true;

#if defined(__ANDROID__)
		// Android handles it own threading therefore we just need to call the engine
		EngineThread();
#endif

#if defined(__APPLE__)
		std::thread t = std::thread(&PixelGameEngine::EngineThread, this);

		// Some implementations may form an event loop here
		platform->StartSystemEventLoop();

		// Wait for thread to be exited
		t.join();
#endif


		if (platform->ApplicationCleanUp() != olc::OK) return olc::FAIL;

		return olc::OK;
	}
#endif

	void PixelGameEngine::SetDrawTarget(Sprite* target)
	{
		if (target)
		{
			pDrawTarget = target;
		}
		else
		{
			nTargetLayer = 0;
			pDrawTarget = vLayers[0].pDrawTarget.Sprite();
		}
	}

	void PixelGameEngine::SetDrawTarget(uint8_t layer, bool bDirty)
	{
		if (layer < vLayers.size())
		{
			pDrawTarget = vLayers[layer].pDrawTarget.Sprite();
			vLayers[layer].bUpdate = bDirty;
			nTargetLayer = layer;
		}
	}

	void PixelGameEngine::EnableLayer(uint8_t layer, bool b)
	{
		if (layer < vLayers.size()) vLayers[layer].bShow = b;
	}

	void PixelGameEngine::SetLayerOffset(uint8_t layer, const olc::vf2d& offset)
	{
		SetLayerOffset(layer, offset.x, offset.y);
	}

	void PixelGameEngine::SetLayerOffset(uint8_t layer, float x, float y)
	{
		if (layer < vLayers.size()) vLayers[layer].vOffset = { x, y };
	}

	void PixelGameEngine::SetLayerScale(uint8_t layer, const olc::vf2d& scale)
	{
		SetLayerScale(layer, scale.x, scale.y);
	}

	void PixelGameEngine::SetLayerScale(uint8_t layer, float x, float y)
	{
		if (layer < vLayers.size()) vLayers[layer].vScale = { x, y };
	}

	void PixelGameEngine::SetLayerTint(uint8_t layer, const olc::Pixel& tint)
	{
		if (layer < vLayers.size()) vLayers[layer].tint = tint;
	}

	void PixelGameEngine::SetLayerCustomRenderFunction(uint8_t layer, std::function<void()> f)
	{
		if (layer < vLayers.size()) vLayers[layer].funcHook = f;
	}

	std::vector<LayerDesc>& PixelGameEngine::GetLayers()
	{
		return vLayers;
	}

	uint32_t PixelGameEngine::CreateLayer()
	{
		LayerDesc ld;
		ld.pDrawTarget.Create(vScreenSize.x, vScreenSize.y);
		vLayers.push_back(std::move(ld));
		return uint32_t(vLayers.size()) - 1;
	}

	Sprite* PixelGameEngine::GetDrawTarget() const
	{
		return pDrawTarget;
	}

	int32_t PixelGameEngine::GetDrawTargetWidth() const
	{
		if (pDrawTarget)
			return pDrawTarget->width;
		else
			return 0;
	}

	int32_t PixelGameEngine::GetDrawTargetHeight() const
	{
		if (pDrawTarget)
			return pDrawTarget->height;
		else
			return 0;
	}

	uint32_t PixelGameEngine::GetFPS() const
	{
		return nLastFPS;
	}

	bool PixelGameEngine::IsFocused() const
	{
		return bHasInputFocus;
	}

	void PixelGameEngine::SetFocused(bool focus)
	{
		bHasInputFocus = focus;
	}

	HWButton PixelGameEngine::GetKey(Key k) const
	{
		return pKeyboardState[k];
	}

	HWButton PixelGameEngine::GetMouse(uint32_t b) const
	{
		return pMouseState[b];
	}

	void PixelGameEngine::ClearTouchPoints(uint8_t startIndex)
	{
		mutexTouchPoints.lock();

		for (int i = startIndex; i < INT8_MAX; i++)
		{
			pTouchNewState[i] = false;
			pTouchNewStateCache[i] = false;
			pTouchPoints[i] = { 0,0 };
			pTouchPointsCache[i] = { 0,0 };

		}

		mutexTouchPoints.unlock();

	}

	HWButton PixelGameEngine::GetTouch(uint32_t p) const
	{
		return pTouchState[p];
	}

	int32_t PixelGameEngine::GetMouseX() const
	{
		return vMousePos.x;
	}

	int32_t PixelGameEngine::GetMouseY() const
	{
		return vMousePos.y;
	}

	int32_t PixelGameEngine::GetTouchX(int8_t index) const
	{
		return pTouchPoints[index].x;

	}

	int32_t PixelGameEngine::GetTouchY(int8_t index) const
	{
		return pTouchPoints[index].y;

	}

	const olc::vi2d& PixelGameEngine::GetMousePos() const
	{
		return vMousePos;
	}

	const olc::vi2d& PixelGameEngine::GetTouchPos(int8_t index) const
	{
		return pTouchPoints[index];

	}


	int32_t PixelGameEngine::GetMouseWheel() const
	{
		return nMouseWheelDelta;
	}

	int32_t PixelGameEngine::ScreenWidth() const
	{
		return vScreenSize.x;
	}

	int32_t PixelGameEngine::ScreenHeight() const
	{
		return vScreenSize.y;
	}

	float PixelGameEngine::GetElapsedTime() const
	{
		return fLastElapsed;
	}

	const olc::vi2d& PixelGameEngine::GetWindowSize() const
	{
		return vWindowSize;
	}

	const olc::vi2d& PixelGameEngine::GetPixelSize() const
	{
		return vPixelSize;
	}

	const olc::vi2d& PixelGameEngine::GetScreenPixelSize() const
	{
		return vScreenPixelSize;
	}

	const olc::vi2d& PixelGameEngine::GetScreenSize() const
	{
		return vScreenSize;
	}

	const olc::vi2d& PixelGameEngine::GetWindowMouse() const
	{
		return vMouseWindowPos;
	}

	bool PixelGameEngine::Draw(const olc::vi2d& pos, Pixel p)
	{
		return Draw(pos.x, pos.y, p);
	}

	// This is it, the critical function that plots a pixel
	bool PixelGameEngine::Draw(int32_t x, int32_t y, Pixel p)
	{
		if (!pDrawTarget) return false;

		if (nPixelMode == Pixel::NORMAL)
		{
			return pDrawTarget->SetPixel(x, y, p);
		}

		if (nPixelMode == Pixel::MASK)
		{
			if (p.a == 255)
				return pDrawTarget->SetPixel(x, y, p);
		}

		if (nPixelMode == Pixel::ALPHA)
		{
			Pixel d = pDrawTarget->GetPixel(x, y);
			float a = (float)(p.a / 255.0f) * fBlendFactor;
			float c = 1.0f - a;
			float r = a * (float)p.r + c * (float)d.r;
			float g = a * (float)p.g + c * (float)d.g;
			float b = a * (float)p.b + c * (float)d.b;
			return pDrawTarget->SetPixel(x, y, Pixel((uint8_t)r, (uint8_t)g, (uint8_t)b/*, (uint8_t)(p.a * fBlendFactor)*/));
		}

		if (nPixelMode == Pixel::CUSTOM)
		{
			return pDrawTarget->SetPixel(x, y, funcPixelMode(x, y, p, pDrawTarget->GetPixel(x, y)));
		}

		return false;
	}




	void PixelGameEngine::DrawLine(const olc::vi2d& pos1, const olc::vi2d& pos2, Pixel p, uint32_t pattern)
	{
		DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, p, pattern);
	}

	void PixelGameEngine::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p, uint32_t pattern)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1; dy = y2 - y1;

		auto rol = [&](void) { pattern = (pattern << 1) | (pattern >> 31); return pattern & 1; };

		olc::vi2d p1(x1, y1), p2(x2, y2);
		//if (!ClipLineToScreen(p1, p2))
		//	return;
		x1 = p1.x; y1 = p1.y;
		x2 = p2.x; y2 = p2.y;

		// straight lines idea by gurkanctn
		if (dx == 0) // Line is vertical
		{
			if (y2 < y1) std::swap(y1, y2);
			for (y = y1; y <= y2; y++) if (rol()) Draw(x1, y, p);
			return;
		}

		if (dy == 0) // Line is horizontal
		{
			if (x2 < x1) std::swap(x1, x2);

			// If the line has no pattern we use simd
			if (pattern == 0xFFFFFFFF)
			{
				simddrawer->DrawFillLine(x1, x2, y1, p, pDrawTarget);
			}
			else
			{
				for (x = x1; x <= x2; x++) if (rol()) Draw(x, y1, p);
			}


			return;
		}

		// Line is Funk-aye
		dx1 = abs(dx); dy1 = abs(dy);
		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1; y = y1; xe = x2;
			}
			else
			{
				x = x2; y = y2; xe = x1;
			}

			if (rol()) Draw(x, y, p);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				if (rol()) Draw(x, y, p);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1; y = y1; ye = y2;
			}
			else
			{
				x = x2; y = y2; ye = y1;
			}

			if (rol()) Draw(x, y, p);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				if (rol()) Draw(x, y, p);
			}
		}
	}

	void PixelGameEngine::DrawCircle(const olc::vi2d& pos, int32_t radius, Pixel p, uint8_t mask)
	{
		DrawCircle(pos.x, pos.y, radius, p, mask);
	}

	void PixelGameEngine::DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p, uint8_t mask)
	{
		// Thanks to IanM-Matrix1 #PR121
		if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius)
			return;

		if (radius > 0)
		{
			int x0 = 0;
			int y0 = radius;
			int d = 3 - 2 * radius;

			while (y0 >= x0) // only formulate 1/8 of circle
			{
				// Draw even octants
				if (mask & 0x01) Draw(x + x0, y - y0, p);// Q6 - upper right right
				if (mask & 0x04) Draw(x + y0, y + x0, p);// Q4 - lower lower right
				if (mask & 0x10) Draw(x - x0, y + y0, p);// Q2 - lower left left
				if (mask & 0x40) Draw(x - y0, y - x0, p);// Q0 - upper upper left
				if (x0 != 0 && x0 != y0)
				{
					if (mask & 0x02) Draw(x + y0, y - x0, p);// Q7 - upper upper right
					if (mask & 0x08) Draw(x + x0, y + y0, p);// Q5 - lower right right
					if (mask & 0x20) Draw(x - y0, y + x0, p);// Q3 - lower lower left
					if (mask & 0x80) Draw(x - x0, y - y0, p);// Q1 - upper left left
				}

				if (d < 0)
					d += 4 * x0++ + 6;
				else
					d += 4 * (x0++ - y0--) + 10;
			}
		}
		else
			Draw(x, y, p);
	}

	void PixelGameEngine::FillCircle(const olc::vi2d& pos, int32_t radius, Pixel p)
	{
		FillCircle(pos.x, pos.y, radius, p);
	}

	void PixelGameEngine::FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p)
	{
		simddrawer->FillCircle_SIMD(x, y, radius, p, pDrawTarget);
	}

	void PixelGameEngine::DrawRect(const olc::vi2d& pos, const olc::vi2d& size, Pixel p)
	{
		DrawRect(pos.x, pos.y, size.x, size.y, p);
	}

	void PixelGameEngine::DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
	{
		simddrawer->DrawFillLine(x, x + w, y, p, pDrawTarget);		// Top Line
		DrawLine(x + w, y, x + w, y + h, p);						// Right line
		simddrawer->DrawFillLine(x, x + w, y + h, p, pDrawTarget);	// Buttom line
		DrawLine(x, y + h, x, y, p);								// Left Line

	}

	void PixelGameEngine::Clear(Pixel p)
	{
		simddrawer->Clear_SIMD(p, pDrawTarget);

	}

	void PixelGameEngine::ClearBuffer(Pixel p, bool bDepth)
	{
		renderer->ClearBuffer(p, bDepth);
	}

	olc::Sprite* PixelGameEngine::GetFontSprite()
	{
		return fontRenderable.Sprite();
	}

	bool PixelGameEngine::ClipLineToScreen(olc::vi2d& in_p1, olc::vi2d& in_p2)
	{
		// https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
		static constexpr int SEG_I = 0b0000, SEG_L = 0b0001, SEG_R = 0b0010, SEG_B = 0b0100, SEG_T = 0b1000;
		auto Segment = [&vScreenSize = vScreenSize](const olc::vi2d& v)
		{
			int i = SEG_I;
			if (v.x < 0) i |= SEG_L; else if (v.x > vScreenSize.x) i |= SEG_R;
			if (v.y < 0) i |= SEG_B; else if (v.y > vScreenSize.y) i |= SEG_T;
			return i;
		};

		int s1 = Segment(in_p1), s2 = Segment(in_p2);

		while (true)
		{
			if (!(s1 | s2))	  return true;
			else if (s1 & s2) return false;
			else
			{
				int s3 = s2 > s1 ? s2 : s1;
				olc::vi2d n;
				if (s3 & SEG_T) { n.x = in_p1.x + (in_p2.x - in_p1.x) * (vScreenSize.y - in_p1.y) / (in_p2.y - in_p1.y); n.y = vScreenSize.y; }
				else if (s3 & SEG_B) { n.x = in_p1.x + (in_p2.x - in_p1.x) * (0 - in_p1.y) / (in_p2.y - in_p1.y); n.y = 0; }
				else if (s3 & SEG_R) { n.x = vScreenSize.x; n.y = in_p1.y + (in_p2.y - in_p1.y) * (vScreenSize.x - in_p1.x) / (in_p2.x - in_p1.x); }
				else if (s3 & SEG_L) { n.x = 0; n.y = in_p1.y + (in_p2.y - in_p1.y) * (0 - in_p1.x) / (in_p2.x - in_p1.x); }
				if (s3 == s1) { in_p1 = n; s1 = Segment(in_p1); }
				else { in_p2 = n; s2 = Segment(in_p2); }
			}
		}
		return true;
	}

	void PixelGameEngine::EnablePixelTransfer(const bool bEnable)
	{
		bSuspendTextureTransfer = !bEnable;
	}


	void PixelGameEngine::FillRect(const olc::vi2d& pos, const olc::vi2d& size, Pixel p)
	{
		FillRect(pos.x, pos.y, size.x, size.y, p);
	}

	void PixelGameEngine::FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
	{
		simddrawer->FillRect_SIMD(x, y, w, h, p, pDrawTarget);
	}

	void PixelGameEngine::DrawTriangle(const olc::vi2d& pos1, const olc::vi2d& pos2, const olc::vi2d& pos3, Pixel p)
	{
		DrawTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p);
	}

	void PixelGameEngine::DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p)
	{
		DrawLine(x1, y1, x2, y2, p);
		DrawLine(x2, y2, x3, y3, p);
		DrawLine(x3, y3, x1, y1, p);
	}

	void PixelGameEngine::FillTriangle(const olc::vi2d& pos1, const olc::vi2d& pos2, const olc::vi2d& pos3, Pixel p)
	{
		FillTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p);
	}

	void PixelGameEngine::FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p)
	{
		simddrawer->FillTriangle_SIMD(x1, y1, x2, y2, x3, y3, p, pDrawTarget);
	}

	void PixelGameEngine::FillTexturedTriangle(const std::vector<olc::vf2d>& vPoints, std::vector<olc::vf2d> vTex, std::vector<olc::Pixel> vColour, olc::Sprite* sprTex)
	{
		olc::vi2d p1 = vPoints[0];
		olc::vi2d p2 = vPoints[1];
		olc::vi2d p3 = vPoints[2];

		if (p2.y < p1.y) { std::swap(p1.y, p2.y); std::swap(p1.x, p2.x); std::swap(vTex[0].x, vTex[1].x); std::swap(vTex[0].y, vTex[1].y); std::swap(vColour[0], vColour[1]); }
		if (p3.y < p1.y) { std::swap(p1.y, p3.y); std::swap(p1.x, p3.x); std::swap(vTex[0].x, vTex[2].x); std::swap(vTex[0].y, vTex[2].y); std::swap(vColour[0], vColour[2]); }
		if (p3.y < p2.y) { std::swap(p2.y, p3.y); std::swap(p2.x, p3.x); std::swap(vTex[1].x, vTex[2].x); std::swap(vTex[1].y, vTex[2].y); std::swap(vColour[1], vColour[2]); }

		olc::vi2d dPos1 = p2 - p1;
		olc::vf2d dTex1 = vTex[1] - vTex[0];
		int dcr1 = vColour[1].r - vColour[0].r;
		int dcg1 = vColour[1].g - vColour[0].g;
		int dcb1 = vColour[1].b - vColour[0].b;
		int dca1 = vColour[1].a - vColour[0].a;

		olc::vi2d dPos2 = p3 - p1;
		olc::vf2d dTex2 = vTex[2] - vTex[0];
		int dcr2 = vColour[2].r - vColour[0].r;
		int dcg2 = vColour[2].g - vColour[0].g;
		int dcb2 = vColour[2].b - vColour[0].b;
		int dca2 = vColour[2].a - vColour[0].a;

		float dax_step = 0, dbx_step = 0, dcr1_step = 0, dcr2_step = 0, dcg1_step = 0, dcg2_step = 0, dcb1_step = 0, dcb2_step = 0, dca1_step = 0, dca2_step = 0;
		olc::vf2d vTex1Step, vTex2Step;

		if (dPos1.y)
		{
			dax_step = dPos1.x / (float)abs(dPos1.y);
			vTex1Step = dTex1 / (float)abs(dPos1.y);
			dcr1_step = dcr1 / (float)abs(dPos1.y);
			dcg1_step = dcg1 / (float)abs(dPos1.y);
			dcb1_step = dcb1 / (float)abs(dPos1.y);
			dca1_step = dca1 / (float)abs(dPos1.y);
		}

		if (dPos2.y)
		{
			dbx_step = dPos2.x / (float)abs(dPos2.y);
			vTex2Step = dTex2 / (float)abs(dPos2.y);
			dcr2_step = dcr2 / (float)abs(dPos2.y);
			dcg2_step = dcg2 / (float)abs(dPos2.y);
			dcb2_step = dcb2 / (float)abs(dPos2.y);
			dca2_step = dca2 / (float)abs(dPos2.y);
		}

		olc::vi2d vStart;
		olc::vi2d vEnd;
		int vStartIdx;

		for (int pass = 0; pass < 2; pass++)
		{
			if (pass == 0)
			{
				vStart = p1; vEnd = p2;	vStartIdx = 0;
			}
			else
			{
				dPos1 = p3 - p2;
				dTex1 = vTex[2] - vTex[1];
				dcr1 = vColour[2].r - vColour[1].r;
				dcg1 = vColour[2].g - vColour[1].g;
				dcb1 = vColour[2].b - vColour[1].b;
				dca1 = vColour[2].a - vColour[1].a;
				dcr1_step = 0; dcg1_step = 0; dcb1_step = 0; dca1_step = 0;

				if (dPos2.y) dbx_step = dPos2.x / (float)abs(dPos2.y);
				if (dPos1.y)
				{
					dax_step = dPos1.x / (float)abs(dPos1.y);
					vTex1Step = dTex1 / (float)abs(dPos1.y);
					dcr1_step = dcr1 / (float)abs(dPos1.y);
					dcg1_step = dcg1 / (float)abs(dPos1.y);
					dcb1_step = dcb1 / (float)abs(dPos1.y);
					dca1_step = dca1 / (float)abs(dPos1.y);
				}

				vStart = p2; vEnd = p3; vStartIdx = 1;
			}

			if (dPos1.y)
			{
				for (int i = vStart.y; i <= vEnd.y; i++)
				{
					int ax = int(vStart.x + (float)(i - vStart.y) * dax_step);
					int bx = int(p1.x + (float)(i - p1.y) * dbx_step);

					olc::vf2d tex_s(vTex[vStartIdx].x + (float)(i - vStart.y) * vTex1Step.x, vTex[vStartIdx].y + (float)(i - vStart.y) * vTex1Step.y);
					olc::vf2d tex_e(vTex[0].x + (float)(i - p1.y) * vTex2Step.x, vTex[0].y + (float)(i - p1.y) * vTex2Step.y);

					olc::Pixel col_s(vColour[vStartIdx].r + uint8_t((float)(i - vStart.y) * dcr1_step), vColour[vStartIdx].g + uint8_t((float)(i - vStart.y) * dcg1_step),
						vColour[vStartIdx].b + uint8_t((float)(i - vStart.y) * dcb1_step), vColour[vStartIdx].a + uint8_t((float)(i - vStart.y) * dca1_step));

					olc::Pixel col_e(vColour[0].r + uint8_t((float)(i - p1.y) * dcr2_step), vColour[0].g + uint8_t((float)(i - p1.y) * dcg2_step),
						vColour[0].b + uint8_t((float)(i - p1.y) * dcb2_step), vColour[0].a + uint8_t((float)(i - p1.y) * dca2_step));

					if (ax > bx) { std::swap(ax, bx); std::swap(tex_s, tex_e); std::swap(col_s, col_e); }

					float tstep = 1.0f / ((float)(bx - ax));
					float t = 0.0f;

					for (int j = ax; j < bx; j++)
					{
						olc::Pixel pixel = PixelLerp(col_s, col_e, t);
						if (sprTex != nullptr) pixel *= sprTex->Sample(tex_s.lerp(tex_e, t));
						Draw(j, i, pixel);
						t += tstep;
					}
				}
			}
		}
	}

	void PixelGameEngine::FillTexturedPolygon(const std::vector<olc::vf2d>& vPoints, const std::vector<olc::vf2d>& vTex, const std::vector<olc::Pixel>& vColour, olc::Sprite* sprTex, olc::DecalStructure structure)
	{
		if (structure == olc::DecalStructure::LINE)
		{
			return; // Meaningless, so do nothing
		}

		if (vPoints.size() < 3 || vTex.size() < 3 || vColour.size() < 3)
			return;

		if (structure == olc::DecalStructure::LIST)
		{
			for (int tri = 0; tri < vPoints.size() / 3; tri++)
			{
				std::vector<olc::vf2d> vP = { vPoints[tri * 3 + 0], vPoints[tri * 3 + 1], vPoints[tri * 3 + 2] };
				std::vector<olc::vf2d> vT = { vTex[tri * 3 + 0], vTex[tri * 3 + 1], vTex[tri * 3 + 2] };
				std::vector<olc::Pixel> vC = { vColour[tri * 3 + 0], vColour[tri * 3 + 1], vColour[tri * 3 + 2] };
				FillTexturedTriangle(vP, vT, vC, sprTex);
			}
			return;
		}

		if (structure == olc::DecalStructure::STRIP)
		{
			for (int tri = 2; tri < vPoints.size(); tri++)
			{
				std::vector<olc::vf2d> vP = { vPoints[tri - 2], vPoints[tri - 1], vPoints[tri] };
				std::vector<olc::vf2d> vT = { vTex[tri - 2], vTex[tri - 1], vTex[tri] };
				std::vector<olc::Pixel> vC = { vColour[tri - 2], vColour[tri - 1], vColour[tri] };
				FillTexturedTriangle(vP, vT, vC, sprTex);
			}
			return;
		}

		if (structure == olc::DecalStructure::FAN)
		{
			for (int tri = 2; tri < vPoints.size(); tri++)
			{
				std::vector<olc::vf2d> vP = { vPoints[0], vPoints[tri - 1], vPoints[tri] };
				std::vector<olc::vf2d> vT = { vTex[0], vTex[tri - 1], vTex[tri] };
				std::vector<olc::Pixel> vC = { vColour[0], vColour[tri - 1], vColour[tri] };
				FillTexturedTriangle(vP, vT, vC, sprTex);
			}
			return;
		}
	}


	void PixelGameEngine::DrawSprite(const olc::vi2d& pos, Sprite* sprite, uint32_t scale, uint8_t flip)
	{
		DrawSprite(pos.x, pos.y, sprite, scale, flip);
	}

	void PixelGameEngine::DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip)
	{
		simddrawer->DrawSprite_SIMD(x, y, sprite, scale, flip, pDrawTarget);
	}

	void PixelGameEngine::DrawPartialSprite(const olc::vi2d& pos, Sprite* pSource, const olc::vi2d& sourcepos, const olc::vi2d& size, uint32_t scale, uint8_t flip)
	{
		simddrawer->DrawPartialSprite_SIMD(pos, pSource, sourcepos, size, scale, (olc::Sprite::Flip)flip, pDrawTarget);
	}

	void PixelGameEngine::DrawPartialSprite(int32_t x, int32_t y, Sprite* pSource, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip)
	{
		DrawPartialSprite({ x,y }, pSource, { ox,oy }, { w,h }, scale, flip);
	}

	void PixelGameEngine::DrawMergeSprite(const olc::vi2d& vPos, Sprite* pFromSprite, const olc::vi2d& vToSpritePos, Sprite* pToSprite,
		Pixel blendPixel, uint32_t scale, olc::Sprite::Flip flip)
	{
		DrawMergeSprite(vPos.x, vPos.y, pFromSprite, vToSpritePos.x, vToSpritePos.y, pToSprite, blendPixel, scale, flip);
	}
	void PixelGameEngine::DrawMergeSprite(int32_t vPosx, int32_t vPosy, Sprite* pFromSprite, int32_t vToSpritePosx, int32_t vToSpritePosy,
		Sprite* pToSprite, Pixel blendPixel, uint32_t scale, olc::Sprite::Flip flip)
	{
		simddrawer->DrawMergeSprite_SIMD(vPosx, vPosy, pFromSprite, vToSpritePosx, vToSpritePosy, pToSprite, blendPixel, scale, flip, pDrawTarget);
	}

	void PixelGameEngine::SetDecalMode(const olc::DecalMode& mode)
	{
		nDecalMode = mode;
	}

	void PixelGameEngine::SetDecalStructure(const olc::DecalStructure& structure)
	{
		nDecalStructure = structure;
	}

	void PixelGameEngine::DrawPartialDecal(const olc::vf2d& pos, olc::Decal* decal, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::vf2d& scale, const olc::Pixel& tint)
	{
		olc::vf2d vScreenSpacePos =
		{
			  (pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			-((pos.y * vInvScreenSize.y) * 2.0f - 1.0f)
		};


		olc::vf2d vScreenSpaceDim =
		{
			  ((pos.x + source_size.x * scale.x) * vInvScreenSize.x) * 2.0f - 1.0f,
			-(((pos.y + source_size.y * scale.y) * vInvScreenSize.y) * 2.0f - 1.0f)
		};

		olc::vf2d vWindow = olc::vf2d(vViewSize);
		olc::vf2d vQuantisedPos = ((vScreenSpacePos * vWindow) + olc::vf2d(0.5f, 0.5f)).floor() / vWindow;
		olc::vf2d vQuantisedDim = ((vScreenSpaceDim * vWindow) + olc::vf2d(0.5f, -0.5f)).ceil() / vWindow;

		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.pos = { { vQuantisedPos.x, vQuantisedPos.y }, { vQuantisedPos.x, vQuantisedDim.y }, { vQuantisedDim.x, vQuantisedDim.y }, { vQuantisedDim.x, vQuantisedPos.y } };
		olc::vf2d uvtl = (source_pos + olc::vf2d(0.0001f, 0.0001f)) * decal->vUVScale;
		olc::vf2d uvbr = (source_pos + source_size - olc::vf2d(0.0001f, 0.0001f)) * decal->vUVScale;
		di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };
		di.w = { 1,1,1,1 };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialDecal(const olc::vf2d& pos, const olc::vf2d& size, olc::Decal* decal, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint)
	{
		olc::vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		olc::vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * size.x * vInvScreenSize.x),
			vScreenSpacePos.y - (2.0f * size.y * vInvScreenSize.y)
		};

		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.pos = { { vScreenSpacePos.x, vScreenSpacePos.y }, { vScreenSpacePos.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpacePos.y } };
		olc::vf2d uvtl = (source_pos)*decal->vUVScale;
		olc::vf2d uvbr = uvtl + ((source_size)*decal->vUVScale);
		di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };
		di.w = { 1,1,1,1 };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}


	void PixelGameEngine::DrawDecal(const olc::vf2d& pos, olc::Decal* decal, const olc::vf2d& scale, const olc::Pixel& tint)
	{
		if (decal == nullptr) return;
		olc::vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		olc::vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * (float(decal->sprite->width) * vInvScreenSize.x)) * scale.x,
			vScreenSpacePos.y - (2.0f * (float(decal->sprite->height) * vInvScreenSize.y)) * scale.y
		};

		DecalInstance di;
		di.decal = decal;
		di.points = 4;
		di.tint = { tint, tint, tint, tint };
		di.pos = { { vScreenSpacePos.x, vScreenSpacePos.y }, { vScreenSpacePos.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpacePos.y } };
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		di.w = { 1, 1, 1, 1 };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawExplicitDecal(olc::Decal* decal, const olc::vf2d* pos, const olc::vf2d* uv, const olc::Pixel* col, uint32_t elements)
	{
		DecalInstance di;
		di.decal = decal;
		di.pos.resize(elements);
		di.uv.resize(elements);
		di.w.resize(elements);
		di.tint.resize(elements);
		di.points = elements;
		for (uint32_t i = 0; i < elements; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = col[i];
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<olc::vf2d>& uv, const olc::Pixel tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = tint;
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<olc::vf2d>& uv, const std::vector<olc::Pixel>& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = tint[i];
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<olc::vf2d>& uv, const std::vector<olc::Pixel>& colours, const olc::Pixel tint)
	{
		std::vector<olc::Pixel> newColours(colours.size(), olc::WHITE);
		std::transform(colours.begin(), colours.end(), newColours.begin(),
			[&tint](const olc::Pixel pin) {	return pin * tint; });
		DrawPolygonDecal(decal, pos, uv, newColours);
	}


	void PixelGameEngine::DrawPolygonDecal(olc::Decal* decal, const std::vector<olc::vf2d>& pos, const std::vector<float>& depth, const std::vector<olc::vf2d>& uv, const olc::Pixel tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = tint;
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

#ifdef OLC_ENABLE_EXPERIMENTAL
	// Lightweight 3D
	void PixelGameEngine::LW3D_DrawTriangles(olc::Decal* decal, const std::vector<std::array<float, 3>>& pos, const std::vector<olc::vf2d>& tex, const std::vector<olc::Pixel>& col)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { pos[i][0], pos[i][1] };
			di.w[i] = pos[i][2];
			di.uv[i] = tex[i];
			di.tint[i] = col[i];
		}
		di.mode = DecalMode::MODEL3D;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}
#endif

	void PixelGameEngine::DrawLineDecal(const olc::vf2d& pos1, const olc::vf2d& pos2, Pixel p)
	{
		auto m = nDecalMode;
		nDecalMode = olc::DecalMode::WIREFRAME;
		DrawPolygonDecal(nullptr, { pos1, pos2 }, { {0, 0}, {0,0} }, p);
		nDecalMode = m;

	}

	void PixelGameEngine::DrawRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel col)
	{
		auto m = nDecalMode;
		SetDecalMode(olc::DecalMode::WIREFRAME);
		olc::vf2d vNewSize = size;// (size - olc::vf2d(0.375f, 0.375f)).ceil();
		std::array<olc::vf2d, 4> points = { { {pos}, {pos.x, pos.y + vNewSize.y}, {pos + vNewSize}, {pos.x + vNewSize.x, pos.y} } };
		std::array<olc::vf2d, 4> uvs = { {{0,0},{0,0},{0,0},{0,0}} };
		std::array<olc::Pixel, 4> cols = { {col, col, col, col} };
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data(), 4);
		SetDecalMode(m);

	}

	void PixelGameEngine::FillRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel col)
	{
		olc::vf2d vNewSize = size;// (size - olc::vf2d(0.375f, 0.375f)).ceil();
		std::array<olc::vf2d, 4> points = { { {pos}, {pos.x, pos.y + vNewSize.y}, {pos + vNewSize}, {pos.x + vNewSize.x, pos.y} } };
		std::array<olc::vf2d, 4> uvs = { {{0,0},{0,0},{0,0},{0,0}} };
		std::array<olc::Pixel, 4> cols = { {col, col, col, col} };
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data(), 4);
	}

	void PixelGameEngine::GradientFillRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel colTL, const olc::Pixel colBL, const olc::Pixel colBR, const olc::Pixel colTR)
	{
		std::array<olc::vf2d, 4> points = { { {pos}, {pos.x, pos.y + size.y}, {pos + size}, {pos.x + size.x, pos.y} } };
		std::array<olc::vf2d, 4> uvs = { {{0,0},{0,0},{0,0},{0,0}} };
		std::array<olc::Pixel, 4> cols = { {colTL, colBL, colBR, colTR} };
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data(), 4);
	}

	void PixelGameEngine::DrawRotatedDecal(const olc::vf2d& pos, olc::Decal* decal, const float fAngle, const olc::vf2d& center, const olc::vf2d& scale, const olc::Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.pos.resize(4);
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		di.w = { 1, 1, 1, 1 };
		di.tint = { tint, tint, tint, tint };
		di.points = 4;
		di.pos[0] = (olc::vf2d(0.0f, 0.0f) - center) * scale;
		di.pos[1] = (olc::vf2d(0.0f, float(decal->sprite->height)) - center) * scale;
		di.pos[2] = (olc::vf2d(float(decal->sprite->width), float(decal->sprite->height)) - center) * scale;
		di.pos[3] = (olc::vf2d(float(decal->sprite->width), 0.0f) - center) * scale;
		float c = cos(fAngle), s = sin(fAngle);
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = pos + olc::vf2d(di.pos[i].x * c - di.pos[i].y * s, di.pos[i].x * s + di.pos[i].y * c);
			di.pos[i] = di.pos[i] * vInvScreenSize * 2.0f - olc::vf2d(1.0f, 1.0f);
			di.pos[i].y *= -1.0f;
			di.w[i] = 1;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}


	void PixelGameEngine::DrawPartialRotatedDecal(const olc::vf2d& pos, olc::Decal* decal, const float fAngle, const olc::vf2d& center, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::vf2d& scale, const olc::Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = 4;
		di.tint = { tint, tint, tint, tint };
		di.w = { 1, 1, 1, 1 };
		di.pos.resize(4);
		di.pos[0] = (olc::vf2d(0.0f, 0.0f) - center) * scale;
		di.pos[1] = (olc::vf2d(0.0f, source_size.y) - center) * scale;
		di.pos[2] = (olc::vf2d(source_size.x, source_size.y) - center) * scale;
		di.pos[3] = (olc::vf2d(source_size.x, 0.0f) - center) * scale;
		float c = cos(fAngle), s = sin(fAngle);
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = pos + olc::vf2d(di.pos[i].x * c - di.pos[i].y * s, di.pos[i].x * s + di.pos[i].y * c);
			di.pos[i] = di.pos[i] * vInvScreenSize * 2.0f - olc::vf2d(1.0f, 1.0f);
			di.pos[i].y *= -1.0f;
		}

		olc::vf2d uvtl = source_pos * decal->vUVScale;
		olc::vf2d uvbr = uvtl + (source_size * decal->vUVScale);
		di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(olc::Decal* decal, const olc::vf2d* pos, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint)
	{
		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.w = { 1, 1, 1, 1 };
		di.pos.resize(4);
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		olc::vf2d center;
		float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
		if (rd != 0)
		{
			olc::vf2d uvtl = source_pos * decal->vUVScale;
			olc::vf2d uvbr = uvtl + (source_size * decal->vUVScale);
			di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };

			rd = 1.0f / rd;
			float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
			float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;
			if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)) center = pos[0] + rn * (pos[2] - pos[0]);
			float d[4];	for (int i = 0; i < 4; i++)	d[i] = (pos[i] - center).mag();
			for (int i = 0; i < 4; i++)
			{
				float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
				di.uv[i] *= q; di.w[i] *= q;
				di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			}
			di.mode = nDecalMode;
			di.structure = nDecalStructure;
			vLayers[nTargetLayer].vecDecalInstance.push_back(di);
		}
	}

	void PixelGameEngine::DrawWarpedDecal(olc::Decal* decal, const olc::vf2d* pos, const olc::Pixel& tint)
	{
		// Thanks Nathan Reed, a brilliant article explaining whats going on here
		// http://www.reedbeta.com/blog/quadrilateral-interpolation-part-1/
		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.w = { 1, 1, 1, 1 };
		di.pos.resize(4);
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		olc::vf2d center;
		float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
		if (rd != 0)
		{
			rd = 1.0f / rd;
			float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
			float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;
			if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)) center = pos[0] + rn * (pos[2] - pos[0]);
			float d[4];	for (int i = 0; i < 4; i++)	d[i] = (pos[i] - center).mag();
			for (int i = 0; i < 4; i++)
			{
				float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
				di.uv[i] *= q; di.w[i] *= q;
				di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			}
			di.mode = nDecalMode;
			di.structure = nDecalStructure;
			vLayers[nTargetLayer].vecDecalInstance.push_back(di);
		}
	}

	void PixelGameEngine::DrawWarpedDecal(olc::Decal* decal, const std::array<olc::vf2d, 4>& pos, const olc::Pixel& tint)
	{
		DrawWarpedDecal(decal, pos.data(), tint);
	}

	void PixelGameEngine::DrawWarpedDecal(olc::Decal* decal, const olc::vf2d(&pos)[4], const olc::Pixel& tint)
	{
		DrawWarpedDecal(decal, &pos[0], tint);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(olc::Decal* decal, const std::array<olc::vf2d, 4>& pos, const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint)
	{
		DrawPartialWarpedDecal(decal, pos.data(), source_pos, source_size, tint);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(olc::Decal* decal, const olc::vf2d(&pos)[4], const olc::vf2d& source_pos, const olc::vf2d& source_size, const olc::Pixel& tint)
	{
		DrawPartialWarpedDecal(decal, &pos[0], source_pos, source_size, tint);
	}

	void PixelGameEngine::DrawStringDecal(const olc::vf2d& pos, const std::string& sText, const Pixel col, const olc::vf2d& scale)
	{
		olc::vf2d spos = { 0.0f, 0.0f };
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = 0; spos.y += 8.0f * scale.y;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialDecal(pos + spos, fontRenderable.Decal(), { float(ox) * 8.0f, float(oy) * 8.0f }, { 8.0f, 8.0f }, scale, col);
				spos.x += 8.0f * scale.x;
			}
		}
	}

	void PixelGameEngine::DrawStringPropDecal(const olc::vf2d& pos, const std::string& sText, const Pixel col, const olc::vf2d& scale)
	{
		olc::vf2d spos = { 0.0f, 0.0f };
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = 0; spos.y += 8.0f * scale.y;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialDecal(pos + spos, fontRenderable.Decal(), { float(ox) * 8.0f + float(vFontSpacing[c - 32].x), float(oy) * 8.0f }, { float(vFontSpacing[c - 32].y), 8.0f }, scale, col);
				spos.x += float(vFontSpacing[c - 32].y) * scale.x;
			}
		}
	}

	// Thanks Oso-Grande/Sopadeoso For these awesom and stupidly clever Text Rotation routines... duh XD
	void PixelGameEngine::DrawRotatedStringDecal(const olc::vf2d& pos, const std::string& sText, const float fAngle, const olc::vf2d& center, const Pixel col, const olc::vf2d& scale)
	{
		olc::vf2d spos = center;
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = center.x; spos.y -= 8.0f;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialRotatedDecal(pos, fontRenderable.Decal(), fAngle, spos, { float(ox) * 8.0f, float(oy) * 8.0f }, { 8.0f, 8.0f }, scale, col);
				spos.x -= 8.0f;
			}
		}
	}

	void PixelGameEngine::DrawRotatedStringPropDecal(const olc::vf2d& pos, const std::string& sText, const float fAngle, const olc::vf2d& center, const Pixel col, const olc::vf2d& scale)
	{
		olc::vf2d spos = center;
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = center.x; spos.y -= 8.0f;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialRotatedDecal(pos, fontRenderable.Decal(), fAngle, spos, { float(ox) * 8.0f + float(vFontSpacing[c - 32].x), float(oy) * 8.0f }, { float(vFontSpacing[c - 32].y), 8.0f }, scale, col);
				spos.x -= float(vFontSpacing[c - 32].y);
			}
		}
	}

	olc::vi2d PixelGameEngine::GetTextSize(const std::string& s)
	{
		olc::vi2d size = { 0,1 };
		olc::vi2d pos = { 0,1 };
		for (auto c : s)
		{
			if (c == '\n') { pos.y++;  pos.x = 0; }
			else if (c == '\t') { pos.x += nTabSizeInSpaces; }
			else pos.x++;
			size.x = std::max(size.x, pos.x);
			size.y = std::max(size.y, pos.y);
		}
		return size * 8;
	}

	void PixelGameEngine::DrawString(const olc::vi2d& pos, const std::string& sText, Pixel col, uint32_t scale)
	{
		DrawString(pos.x, pos.y, sText, col, scale);
	}

	void PixelGameEngine::DrawString(int32_t x, int32_t y, const std::string& sText, Pixel col, uint32_t scale)
	{
		int32_t sx = 0;
		int32_t sy = 0;
		Pixel::Mode m = nPixelMode;
		// Thanks @tucna, spotted bug with col.ALPHA :P
		if (m != Pixel::CUSTOM) // Thanks @Megarev, required for "shaders"
		{
			if (col.a != 255)		SetPixelMode(Pixel::ALPHA);
			else					SetPixelMode(Pixel::MASK);
		}
		for (auto c : sText)
		{
			if (c == '\n')
			{
				sx = 0; sy += 8 * scale;
			}
			else if (c == '\t')
			{
				sx += 8 * nTabSizeInSpaces * scale;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;

				if (scale > 1)
				{
					for (uint32_t i = 0; i < 8; i++)
						for (uint32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8, j + oy * 8).r > 0)
								for (uint32_t is = 0; is < scale; is++)
									for (uint32_t js = 0; js < scale; js++)
										Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
				}
				else
				{
					for (uint32_t i = 0; i < 8; i++)
						for (uint32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8, j + oy * 8).r > 0)
								Draw(x + sx + i, y + sy + j, col);
				}
				sx += 8 * scale;
			}
		}
		SetPixelMode(m);
	}

	olc::vi2d PixelGameEngine::GetTextSizeProp(const std::string& s)
	{
		olc::vi2d size = { 0,1 };
		olc::vi2d pos = { 0,1 };
		for (auto c : s)
		{
			if (c == '\n') { pos.y += 1;  pos.x = 0; }
			else if (c == '\t') { pos.x += nTabSizeInSpaces * 8; }
			else pos.x += vFontSpacing[c - 32].y;
			size.x = std::max(size.x, pos.x);
			size.y = std::max(size.y, pos.y);
		}

		size.y *= 8;
		return size;
	}

	void PixelGameEngine::DrawStringProp(const olc::vi2d& pos, const std::string& sText, Pixel col, uint32_t scale)
	{
		DrawStringProp(pos.x, pos.y, sText, col, scale);
	}

	void PixelGameEngine::DrawStringProp(int32_t x, int32_t y, const std::string& sText, Pixel col, uint32_t scale)
	{
		int32_t sx = 0;
		int32_t sy = 0;
		Pixel::Mode m = nPixelMode;

		if (m != Pixel::CUSTOM)
		{
			if (col.a != 255)		SetPixelMode(Pixel::ALPHA);
			else					SetPixelMode(Pixel::MASK);
		}
		for (auto c : sText)
		{
			if (c == '\n')
			{
				sx = 0; sy += 8 * scale;
			}
			else if (c == '\t')
			{
				sx += 8 * nTabSizeInSpaces * scale;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;

				if (scale > 1)
				{
					for (int32_t i = 0; i < vFontSpacing[c - 32].y; i++)
						for (int32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8 + vFontSpacing[c - 32].x, j + oy * 8).r > 0)
								for (int32_t is = 0; is < int(scale); is++)
									for (int32_t js = 0; js < int(scale); js++)
										Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
				}
				else
				{
					for (int32_t i = 0; i < vFontSpacing[c - 32].y; i++)
						for (int32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8 + vFontSpacing[c - 32].x, j + oy * 8).r > 0)
								Draw(x + sx + i, y + sy + j, col);
				}
				sx += vFontSpacing[c - 32].y * scale;
			}
		}
		SetPixelMode(m);
	}

	void PixelGameEngine::SetPixelMode(Pixel::Mode m)
	{
		nPixelMode = m;
	}

	Pixel::Mode PixelGameEngine::GetPixelMode()
	{
		return nPixelMode;
	}

	void PixelGameEngine::SetPixelMode(std::function<olc::Pixel(const int x, const int y, const olc::Pixel&, const olc::Pixel&)> pixelMode)
	{
		funcPixelMode = pixelMode;
		nPixelMode = Pixel::Mode::CUSTOM;
	}

	void PixelGameEngine::SetPixelBlend(float fBlend)
	{
		fBlendFactor = fBlend;
		if (fBlendFactor < 0.0f) fBlendFactor = 0.0f;
		if (fBlendFactor > 1.0f) fBlendFactor = 1.0f;
	}

	std::vector<olc::SensorInformation> PixelGameEngine::GetSupportedSensors()
	{

		std::vector<olc::SensorInformation> vecSensorInfo;
		ASensorList sensor_list;
		int sensor_count = ASensorManager_getSensorList(pOsEngine.sensorManager, &sensor_list);
		std::string name;
		for (int i = 0; i < sensor_count; i++) {

			SensorInformation sensorInfo;
			sensorInfo.Name = ASensor_getStringType(sensor_list[i]);
			sensorInfo.Vendor = ASensor_getVendor(sensor_list[i]);
			sensorInfo.Type = (olc::SensorType)ASensor_getType(sensor_list[i]);
			sensorInfo.Resolution = ASensor_getResolution(sensor_list[i]);
			sensorInfo.MinDelay = ASensor_getMinDelay(sensor_list[i]);
			sensorInfo.FifoMaxEventCount = ASensor_getFifoMaxEventCount(sensor_list[i]);
			sensorInfo.FifoReservedEventCount = ASensor_getFifoReservedEventCount(sensor_list[i]);
			sensorInfo.GetStringType = ASensor_getStringType(sensor_list[i]);
			sensorInfo.ReportingMode = (olc::SensorReportingMode)ASensor_getReportingMode(sensor_list[i]);
			sensorInfo.isWakeUpSensor = ASensor_isWakeUpSensor(sensor_list[i]);

			//sensorInfo.Handle = ASensor_getHandle(sensor_list[i]);

			vecSensorInfo.push_back(sensorInfo);

		}

		return vecSensorInfo;
	}

	olc::SensorInformation PixelGameEngine::GetSensorInfo(olc::SensorType Type)
	{
		SensorInformation sensorInfo;
		sensorInfo.Type = olc::ASENSOR_TYPE_INVALID;
		ASensorList sensor_list;
		int sensor_count = ASensorManager_getSensorList(pOsEngine.sensorManager, &sensor_list);

		for (int i = 0; i < sensor_count; i++) {

			if (Type == (olc::SensorType)ASensor_getType(sensor_list[i]))
			{
				sensorInfo.Name = ASensor_getStringType(sensor_list[i]);
				sensorInfo.Vendor = ASensor_getVendor(sensor_list[i]);
				sensorInfo.Type = (olc::SensorType)ASensor_getType(sensor_list[i]);
				sensorInfo.Resolution = ASensor_getResolution(sensor_list[i]);
				sensorInfo.MinDelay = ASensor_getMinDelay(sensor_list[i]);
				sensorInfo.FifoMaxEventCount = ASensor_getFifoMaxEventCount(sensor_list[i]);
				sensorInfo.FifoReservedEventCount = ASensor_getFifoReservedEventCount(sensor_list[i]);
				sensorInfo.GetStringType = ASensor_getStringType(sensor_list[i]);
				sensorInfo.ReportingMode = (olc::SensorReportingMode)ASensor_getReportingMode(sensor_list[i]);
				sensorInfo.isWakeUpSensor = ASensor_isWakeUpSensor(sensor_list[i]);
				//sensorInfo.Handle = ASensor_getHandle(sensor_list[i]);
				break;
			}

		}

		return sensorInfo;
	}


	olc::rcode olc::PixelGameEngine::EnableSensor(olc::SensorType Type, int32_t sampleRate)
	{
		// 1: Lets check if it already exist, if so we need to disable it
		DisableSensor(Type);

		// 2: Get the sensor
		const ASensor* pSensor = ASensorManager_getDefaultSensor(pOsEngine.sensorManager, Type);

		if (pSensor == nullptr) return rcode::FAIL;



		ASensorEventQueue_enableSensor(pOsEngine.sensorEventQueue, pSensor);

		int32_t minRate = ASensor_getMinDelay(pSensor);
		if (sampleRate > 0)
		{
			minRate = std::fmin(minRate, sampleRate);
		}



		ASensorEventQueue_setEventRate(pOsEngine.sensorEventQueue, pSensor, minRate);

		pOsEngine.deviceSensors.push_back({ Type, pSensor, sampleRate });

		return olc::rcode::OK;
	}

	olc::rcode PixelGameEngine::ChangeSensorSampleRate(olc::SensorType Type, int32_t sampleRate)
	{
		for (size_t i = 0; i < pOsEngine.deviceSensors.size(); i++)
		{
			if (Type == std::get<0>(pOsEngine.deviceSensors[i]))
			{
				int32_t minRate = ASensor_getMinDelay(std::get<1>(pOsEngine.deviceSensors[i]));
				minRate = std::fmax(minRate, sampleRate);

				ASensorEventQueue_setEventRate(pOsEngine.sensorEventQueue, std::get<1>(pOsEngine.deviceSensors[i]), minRate);

				std::get<2>(pOsEngine.deviceSensors[i]) = minRate;

				return olc::rcode::OK;
				break;
			}
		}

		return olc::rcode::FAIL;
	}


	olc::rcode PixelGameEngine::DisableSensor(olc::SensorType Type)
	{
		for (size_t i = 0; i < pOsEngine.deviceSensors.size(); i++)
		{
			if (Type == std::get<0>(pOsEngine.deviceSensors[i]))
			{
				ASensorEventQueue_disableSensor(pOsEngine.sensorEventQueue, std::get<1>(pOsEngine.deviceSensors[i]));
				pOsEngine.deviceSensors.erase(pOsEngine.deviceSensors.begin() + i);
				break;
			}
		}

		return olc::rcode::OK;
	}


	const std::vector<std::string>& PixelGameEngine::GetDroppedFiles() const
	{
		return vDroppedFiles;
	}

	const olc::vi2d& PixelGameEngine::GetDroppedFilesPoint() const
	{
		return vDroppedFilesPoint;
	}

	void PixelGameEngine::CreateCRSprite()
	{
		const char logo[] =
			"000000000000000000000000000000000000000000000000000000000000000000005"
			"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEED1EE"
			"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEED5EEE"
			"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE@E@000"
			"0000000000000000000000000000000000000000000000000000000000001E1D:ZZZZ"
			"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ1D5BZZZZZZ"
			"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ5@E:P0002Z0"
			"02ZZX000000000000ZP0000000000000000000000000000ZX000Z002XE1DX?o`o:Poo"
			"800SooaE5@E1ED5BX?ol5E@E0E1ED?oo5@E1ED5DE1D5E@ZQEEBPEE2QD5BSooclZ?olQ"
			"AB?oo5DEEDEEDE:SooaEEAE5DEEDoolEADEEDEAE5AEEBZ5EE:5EE:5@E:?oo?bXoob55"
			"8o3lEAEEAD5ADZ?oo5@E5EEAD5Cl01E5AD5AE5DE5@E:X01DXEEDXE1DXo3lo:Sl0800S"
			"ooaE1ED5EE5BXo00EEDEEE5EE?oo5EE5EE5DEEDEEDZQEEBQD5BQD5BSl?cl0?`0ZZZ?o"
			"o5D5E@EEDE03loaEEAEEDEEDoolEED5EDEAEEAEEBZ5EE:5@E:5@E:?oo?oloob008o00"
			"EAEEAD01EE?co5EE5EEAD03l01DE@05AE5AE5@0:XE000EEDXE1DXooloocoo8DDSlZQE"
			"5EE5EE5EDoolE1DE4E5EE?oo5AE5EE5DE5DEEDZQEEAAEEBQD5BPoo3oo3olQAB?bZ5DE"
			"1D5EDEE@ooaD5AD1D5EDoolE1DEE@EAD5@EEBZ5EE51ED:5@E:P000000020080:X0000"
			"00000000000000000000000000000000000:X0000002XE1DZZZZZZZZZZZZZZZZZZZZZ"
			"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZQD5@ZZZZZZZZZZZZZZZZZZZZZZ"
			"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZX5@E@00000000000000000000000"
			"00000000000000000000000000000000000000001E1EEEEEEEEEEEEEEEEEEEEEEEEEE"
			"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEED5EEEEEEEEEEEEEEEEEEEEEEEEEEE"
			"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE@5EEEEEEEEEEEEEEEEEEEEEEEEEEEE"
			"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEED0000000000000000000000000000000"
			"0000000000000000000000000000000000000";

		sprCR.Create(203, 24);
		int px = 0, py = 0;
		for (size_t b = 0; b < 1624; b += 4)
		{
			uint32_t sym1 = (uint32_t)logo[b + 0] - 48;
			uint32_t sym2 = (uint32_t)logo[b + 1] - 48;
			uint32_t sym3 = (uint32_t)logo[b + 2] - 48;
			uint32_t sym4 = (uint32_t)logo[b + 3] - 48;
			uint32_t r = sym1 << 18 | sym2 << 12 | sym3 << 6 | sym4;

			for (int i = 0; i < 12; i++)
			{
				olc::Pixel p = olc::RED;
				switch ((r & 0xC00000) >> 22)
				{
				case 0: p = olc::Pixel(0, 0, 0, 255);  break;
				case 1: p = olc::Pixel(255, 255, 255, 255);  break;
				case 2: p = olc::Pixel(255, 120, 26, 255);  break;
				case 3: p = olc::Pixel(79, 193, 255, 255);  break;
				}
				sprCR.Sprite()->SetPixel(px, py, p);
				if (++px == 203) { py++; px = 0; }
				r <<= 2;
			}
		}

		sprCR.Decal()->Update();
		vBoomCR.resize(sprCR.Sprite()->width * sprCR.Sprite()->height);
		vScaleCR = { float(ScreenWidth()) / 500.0f, float(ScreenWidth()) / 500.0f };
		fAspectCR = float(ScreenWidth()) / float(ScreenHeight());
		vPositionCR = olc::vf2d(
			(250 - sprCR.Sprite()->width) / 2.0f,
			(250 - sprCR.Sprite()->height) / 2.0f / fAspectCR);

		for (int y = 0; y < sprCR.Sprite()->height; y++)
			for (int x = 0; x < sprCR.Sprite()->width; x++)
				vBoomCR[y * sprCR.Sprite()->width + x] = std::make_pair(
					vPositionCR + olc::vf2d(x, y),
					olc::vf2d(
						(float(rand()) / float(RAND_MAX)) * 10.0f - 5.0f,
						(float(rand()) / float(RAND_MAX)) * 10.0f - 5.0f)
				);

	}


	bool PixelGameEngine::DisplayCR(float& fElapsedTime)
	{

		if (bCompleteCR) return false;

		SetDrawTarget(nullptr);

		fParticleTimeCR += fElapsedTime;

		for (int y = 0; y < sprCR.Sprite()->height; y++)
			for (int x = 0; x < sprCR.Sprite()->width; x++)
			{

				if (fParticleTimeCR < 1.0f)
				{

				}
				else if (fParticleTimeCR < 2.0f)
				{
					vBoomCR[y * sprCR.Sprite()->width + x].first =
						olc::vf2d(
							(250 - sprCR.Sprite()->width) / 2.0f + float(x),
							(250 - sprCR.Sprite()->height) / 2.0f / fAspectCR + float(y)
						) +
						olc::vf2d(
							(float(rand()) / float(RAND_MAX)) * 0.5f - 0.25f,
							(float(rand()) / float(RAND_MAX)) * 0.5f - 0.25f);
				}
				else if (fParticleTimeCR < 5.0f)
				{
					vBoomCR[y * sprCR.Sprite()->width + x].first += vBoomCR[y * sprCR.Sprite()->width + x].second * fElapsedTime * 20.0f;
				}
				else
				{
					bCompleteCR = true;
				}

				DrawPartialDecal(vScaleCR * vBoomCR[y * sprCR.Sprite()->width + x].first * 2.0f, sprCR.Decal(), olc::vf2d(x, y), { 1, 1 }, vScaleCR * 2.0f, olc::PixelF(1.0f, 1.0f, 1.0f, std::min(1.0f, std::max(4.0f - fParticleTimeCR, 0.0f))));
			}

		olc::vi2d vSize = GetTextSizeProp("Powered By Pixel Game Engine Mobile BETA 2.1.0");
		DrawStringPropDecal(olc::vf2d(float(ScreenWidth() / 2) - vSize.x / 2, float(ScreenHeight()) - vSize.y * 2.0f), "Powered By Pixel Game Engine Mobile BETA 2.1.0", olc::PixelF(1.0f, 1.0f, 1.0f, 0.5f), olc::vf2d(1.0, 1.0f));

		vSize = GetTextSizeProp("Copyright OneLoneCoder.com 2023.");
		DrawStringPropDecal(olc::vf2d(float(ScreenWidth() / 2) - vSize.x / 2, float(ScreenHeight()) - vSize.y * 3.0f), "Copyright OneLoneCoder.com 2023", olc::PixelF(1.0f, 1.0f, 1.0f, 0.5f), olc::vf2d(1.0, 1.0f));


		return true;

	}


	void PixelGameEngine::TextEntryEnable(const bool bEnable, const std::string& sText)
	{
		if (bEnable)
		{
			nTextEntryCursor = int32_t(sText.size());
			sTextEntryString = sText;
			bTextEntryEnable = true;
		}
		else
		{
			bTextEntryEnable = false;
		}
	}

	std::string PixelGameEngine::TextEntryGetString() const
	{
		return sTextEntryString;
	}

	int32_t PixelGameEngine::TextEntryGetCursor() const
	{
		return nTextEntryCursor;
	}

	bool PixelGameEngine::IsTextEntryEnabled() const
	{
		return bTextEntryEnable;
	}


	void PixelGameEngine::UpdateTextEntry()
	{
		// Check for typed characters
		for (const auto& key : vKeyboardMap)
			if (GetKey(std::get<0>(key)).bPressed)
			{
				sTextEntryString.insert(nTextEntryCursor, GetKey(olc::Key::SHIFT).bHeld ? std::get<2>(key) : std::get<1>(key));
				nTextEntryCursor++;
			}

		// Check for command characters
		if (GetKey(olc::Key::LEFT).bPressed)
			nTextEntryCursor = std::max(0, nTextEntryCursor - 1);
		if (GetKey(olc::Key::RIGHT).bPressed)
			nTextEntryCursor = std::min(int32_t(sTextEntryString.size()), nTextEntryCursor + 1);
		if (GetKey(olc::Key::BACK).bPressed && nTextEntryCursor > 0)
		{
			sTextEntryString.erase(nTextEntryCursor - 1, 1);
			nTextEntryCursor = std::max(0, nTextEntryCursor - 1);
		}
		if (GetKey(olc::Key::DEL).bPressed && nTextEntryCursor < sTextEntryString.size())
			sTextEntryString.erase(nTextEntryCursor, 1);

		if (GetKey(olc::Key::ENTER).bPressed)
		{
			OnTextEntryComplete(sTextEntryString);
			TextEntryEnable(false);
		}
	}

	void PixelGameEngine::OnTextEntryComplete(const std::string& sText) { UNUSED(sText); }

	// User must override these functions as required. I have not made
	// them abstract because I do need a default behaviour to occur if
	// they are not overwritten

	bool PixelGameEngine::OnUserCreate()
	{
		return false;
	}

	bool PixelGameEngine::OnUserUpdate(float fElapsedTime)
	{
		UNUSED(fElapsedTime);  return false;
	}

	bool PixelGameEngine::OnUserDestroy()
	{
		return true;
	}

	void PixelGameEngine::OnSaveStateRequested()
	{

	}

	void PixelGameEngine::OnRestoreStateRequested()
	{

	}

	/*void PixelGameEngine::OnTextEntryComplete(const std::string& sText) { UNUSED(sText); }
	bool PixelGameEngine::OnConsoleCommand(const std::string& sCommand) { UNUSED(sCommand); return false; }*/

	// Externalised API
	void PixelGameEngine::olc_UpdateViewport()
	{
		int32_t ww = vScreenSize.x * vPixelSize.x;
		int32_t wh = vScreenSize.y * vPixelSize.y;
		float wasp = (float)ww / (float)wh;


		if (bPixelCohesion)
		{
			vScreenPixelSize = (vWindowSize / vScreenSize);
			vViewSize = (vWindowSize / vScreenSize) * vScreenSize;
		}
		else
		{
			vViewSize.x = (int32_t)vWindowSize.x;
			vViewSize.y = (int32_t)((float)vViewSize.x / wasp);

			if (vViewSize.y > vWindowSize.y)
			{
				vViewSize.y = vWindowSize.y;
				vViewSize.x = (int32_t)((float)vViewSize.y * wasp);
			}
		}

		vViewPos = (vWindowSize - vViewSize) / 2;
	}

	void PixelGameEngine::olc_UpdateWindowSize(int32_t x, int32_t y)
	{
		vWindowSize = { x, y };
		olc_UpdateViewport();
	}

	void PixelGameEngine::olc_UpdateMouseWheel(int32_t delta)
	{
		nMouseWheelDeltaCache += delta;
	}

	void PixelGameEngine::olc_UpdateMouse(int32_t x, int32_t y)
	{
		/* Mouse coords come in OS Screen Size
		 Therefore we need to update the offset, if any for Auto FullScreen mode
		 The OS Screen size will always have a pixelSize of 1 i.e. {1,1}
		 Therefore we need to convert this to PGE Pixel Size */

		if (bFullScreen)
		{
			// Correct the offset, we simple get the % of the full screen and apply it to the game screen for x & y
			// Correct the offset, we simple get the % of the full screen and apply it to the game screen for x & y
			float xPec = (x / (float)pOsEngine.screenWidth) * 100.0f;
			float yPec = (y / (float)pOsEngine.screenHeight) * 100.0f;

			x = (float(pOsEngine.viewWidth) / 100.0f) * xPec;
			y = (float(pOsEngine.viewHeight) / 100.0f) * yPec;

		}

		bHasMouseFocus = true;
		vMouseWindowPos = { x, y };
		// Full Screen mode may have a weird viewport we must clamp to
		x -= vViewPos.x;
		y -= vViewPos.y;
		vMousePosCache.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
		vMousePosCache.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));
		if (vMousePosCache.x >= (int32_t)vScreenSize.x)	vMousePosCache.x = vScreenSize.x - 1;
		if (vMousePosCache.y >= (int32_t)vScreenSize.y)	vMousePosCache.y = vScreenSize.y - 1;
		if (vMousePosCache.x < 0) vMousePosCache.x = 0;
		if (vMousePosCache.y < 0) vMousePosCache.y = 0;
	}

	void PixelGameEngine::olc_UpdateTouch(int32_t x, int32_t y, int32_t index)
	{
		/* Touch coords come in OS Screen Size
		 Therefore we need to update the offset, if any for Auto FullScreen mode
		 The OS Screen size will always have a pixelSize of 1 i.e. {1,1}
		 Therefore we need to convert this to PGE Pixel Size */

		mutexTouchPoints.lock();

		olc::vi2d tPos = { x, y };

		if (bFullScreen)
		{
			// Correct the offset, we simple get the % of the full screen and apply it to the game screen for x & y
			float xPec = (tPos.x / (float)pOsEngine.screenWidth) * 100.0f;
			float yPec = (tPos.y / (float)pOsEngine.screenHeight) * 100.0f;

			tPos.x = (float(pOsEngine.viewWidth) / 100.0f) * xPec;
			tPos.y = (float(pOsEngine.viewHeight) / 100.0f) * yPec;

		}
		else
		{
			// Get the approx off set
			int32_t  offsetx = (pOsEngine.screenWidth - (vScreenSize.x * GetPixelSize().x)) / 2;
			int32_t  offsety = (pOsEngine.screenHeight - (vScreenSize.y * GetPixelSize().y)) / 2;
			x += offsetx;
			y += offsety;

			tPos.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
			tPos.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));


		}

		// Full Screen mode may have a weird viewport we must clamp to
		tPos.x -= vViewPos.x;
		tPos.y -= vViewPos.y;

		bHasTouchFocus = true;

		if (tPos.x >= (int32_t)vScreenSize.x)	tPos.x = vScreenSize.x;
		if (tPos.y >= (int32_t)vScreenSize.y)	tPos.y = vScreenSize.y;
		if (tPos.x < 0) tPos.x = 0;
		if (tPos.y < 0) tPos.y = 0;


		pTouchPointsCache[index] = tPos;
		mutexTouchPoints.unlock();

	}


	void PixelGameEngine::olc_UpdateMouseState(int32_t button, bool state)
	{

		pMouseNewState[button] = state;
	}


	void PixelGameEngine::olc_UpdateTouchState(int32_t touchPoint, bool state)
	{
		// We need locks as the sensors can sample up to 10000 times per second
		mutexTouchPoints.lock();

		pTouchNewStateCache[touchPoint] = state;

		if (state == false)
		{
			// we need to shift to support MultiTouch
			// Example if there is 3 touch points and point 1 is lifted then
			// point 3 becomes point 2, there we need to move point 3 state to point 2 state
			for (int i = touchPoint; i < INT8_MAX; i++)
			{
				pTouchNewStateCache[i] = pTouchNewStateCache[i++];
			}
		}

		mutexTouchPoints.unlock();

	}

	void PixelGameEngine::olc_UpdateSensorEvent(ASensorEvent event)
	{

		if (event.type == ASENSOR_TYPE_INVALID) return;

		for (auto& s : pOsEngine.deviceSensors)
		{
			if (event.type == std::get<0>(s))
			{
				// We have a match lets check if we support it
				// This list will be expanded in time
				switch (event.type)
				{

				case ASENSOR_TYPE_ACCELEROMETER:
				{
					SelectSensor.Accelerometer = event.acceleration;
					break;
				}

				case ASENSOR_TYPE_MAGNETIC_FIELD:
				{
					SelectSensor.MagniticField = event.magnetic;
					break;
				}

				case ASENSOR_TYPE_ORIENTATION:
				{
					SelectSensor.Orientation = event.vector;
				}

				case ASENSOR_TYPE_GYROSCOPE:
				{
					SelectSensor.Gyroscope = event.gyro;
					break;
				}

				case ASENSOR_TYPE_LIGHT:
				{
					SelectSensor.Light = event.light;
					break;
				}

				case ASENSOR_TYPE_PRESSURE:
				{
					SelectSensor.Pressure = event.pressure;
					break;
				}

				case ASENSOR_TYPE_PROXIMITY:
				{
					SelectSensor.Proximity = event.data;
					break;
				}

				case ASENSOR_TYPE_GRAVITY:
				{
					SelectSensor.Gravity = event.vector;
					break;
				}

				case ASENSOR_TYPE_LINEAR_ACCELERATION:
				{
					SelectSensor.LinearAcceleration = event.vector;
					break;
				}


				case ASENSOR_TYPE_ROTATION_VECTOR:
				{
					SelectSensor.RotationVector = event.vector;
					break;
				}

				case ASENSOR_TYPE_RELATIVE_HUMIDITY:
				{
					SelectSensor.RelativeHumidity = event.relative_humidity;
					break;
				}

				case ASENSOR_TYPE_AMBIENT_TEMPERATURE:
				{
					SelectSensor.AmbientTemperature = event.temperature;
					break;
				}

				case ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED:
				{
					SelectSensor.Uncalibrated_MagniticField = event.uncalibrated_magnetic;
					break;
				}

				case ASENSOR_TYPE_GAME_ROTATION_VECTOR:
				{
					SelectSensor.GameRotation = event.vector;
					break;
				}


				case ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED:
				{
					SelectSensor.Uncalibrated_Gyroscope = event.uncalibrated_gyro;
					break;
				}

				case ASENSOR_TYPE_SIGNIFICANT_MOTION:
				{
					SelectSensor.SignificantMotion = event.vector;
					break;
				}

				case ASENSOR_TYPE_STEP_DETECTOR:
				{
					SelectSensor.StepDetector = event.data;
					break;
				}

				case ASENSOR_TYPE_STEP_COUNTER:
				{
					SelectSensor.StepCounter = event.data;
					break;
				}


				case ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR:
				{
					SelectSensor.GeomagneticRotationVector = event.vector;
					break;
				}

				case ASENSOR_TYPE_HEART_RATE:
				{
					SelectSensor.HeartRate = event.heart_rate;
					break;
				}

				case ASENSOR_TYPE_POSE_6DOF:
				{
					SelectSensor.Pose_6D = event.vector;
					break;
				}

				case ASENSOR_TYPE_STATIONARY_DETECT:
				{
					SelectSensor.StationaryDetect = event.data;
					break;
				}

				case ASENSOR_TYPE_MOTION_DETECT:
				{
					SelectSensor.MotionDetect = event.data;
					break;
				}

				case ASENSOR_TYPE_HEART_BEAT:
				{
					SelectSensor.HeartBeat = event.data;
					break;
				}

				case ASENSOR_TYPE_ADDITIONAL_INFO:
				{
					//Speical Case
					break;
				}

				case ASENSOR_TYPE_LOW_LATENCY_OFFBODY_DETECT:
				{
					SelectSensor.LowLatencyOffBodyDetect = event.data;
					break;
				}


				case ASENSOR_TYPE_ACCELEROMETER_UNCALIBRATED:
				{
					SelectSensor.Uncalibrated_Accelerometer = event.uncalibrated_acceleration;
					break;
				}

				case ASENSOR_TYPE_HINGE_ANGLE:
				{
					SelectSensor.HingeAngle = event.data;
					break;
				}


				default:
				{
					break;
				}

				}
				break;
			}

		};

	}

	void PixelGameEngine::olc_UpdateKeyState(int32_t key, bool state)
	{
		pKeyNewState[key] = state;
	}

	void PixelGameEngine::olc_UpdateMouseFocus(bool state)
	{
		bHasMouseFocus = state;
	}

	void PixelGameEngine::olc_UpdateTouchFocus(bool state)
	{
		bHasTouchFocus = state;
	}

	void PixelGameEngine::olc_UpdateKeyFocus(bool state)
	{
		bHasInputFocus = state;
	}

	void PixelGameEngine::olc_DropFiles(int32_t x, int32_t y, const std::vector<std::string>& vFiles)
	{
		x -= vViewPos.x;
		y -= vViewPos.y;
		vDroppedFilesPointCache.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
		vDroppedFilesPointCache.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));
		if (vDroppedFilesPointCache.x >= (int32_t)vScreenSize.x)	vDroppedFilesPointCache.x = vScreenSize.x - 1;
		if (vDroppedFilesPointCache.y >= (int32_t)vScreenSize.y)	vDroppedFilesPointCache.y = vScreenSize.y - 1;
		if (vDroppedFilesPointCache.x < 0) vDroppedFilesPointCache.x = 0;
		if (vDroppedFilesPointCache.y < 0) vDroppedFilesPointCache.y = 0;
		vDroppedFilesCache = vFiles;
	}

	void PixelGameEngine::olc_Reanimate()
	{
		bAtomActive = true;
	}

	bool PixelGameEngine::olc_IsRunning()
	{
		return bAtomActive;
	}

	void PixelGameEngine::olc_Terminate()
	{
		bAtomActive = false;
		renderer->DestroyDevice();
	}

#if defined(__ANDROID__)
	void PixelGameEngine::EngineThread()
	{
		// Allow platform to do stuff here if needed, since its now in the
		// context of this thread
		if (platform->ThreadStartUp() == olc::FAIL)	return;

		// There are a few background workers that need to completed before we can start the engine
		// Android needs to create the events, create the window, apply our construct options etc etc
		// The bAtomActive loop, is used to give time for events to kick in
		// once the events kick in, we need time for the window to appear StartPGE = false
		// Once StartPGE = True, we need to wait for prepare to complete we can ROCK and ROLL Baby!


		//Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;
		bool bPrepare = false;
		size_t sensorCount = 0;

		while (bAtomActive) {

			if (!bAtomActive) break;
			ident = ALooper_pollAll(0, NULL, &events, (void**)&source);

			// If we have an event, let process it
			if (ident >= 0)
			{
				if (source != NULL) {
					source->process(renderer->ptrPGE->pOsEngine.app, source);
				}
			}

			// If a sensor has data, process it now.
			if (ident == LOOPER_ID_USER) {
				sensorCount = pOsEngine.deviceSensors.size();
				if (sensorCount > 0)
				{
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(pOsEngine.sensorEventQueue, &event, 1) > 0)
					{
						olc_UpdateSensorEvent(event);
					}
				}
			}

			// Once the engine ready lets go
			if (renderer->ptrPGE->pOsEngine.StartPGE == true)
			{
				if (!bPrepare)
				{
					// Do engine context specific initialisation
					olc_PrepareEngine();

					// Create the CopyRight Sprite : DO NOT REMOVED
					CreateCRSprite();

					// Create user resources as part of this thread
					for (auto& ext : vExtensions) ext->OnBeforeUserCreate();
					if (!OnUserCreate()) bAtomActive = false;
					for (auto& ext : vExtensions) ext->OnAfterUserCreate();
					bPrepare = true;
				}
				else
				{
					if (renderer->ptrPGE->pOsEngine.animating == 1)
					{
						olc_CoreUpdate();
					}
					else
					{
						if (renderer->ptrPGE->pOsEngine.LostFocus == false)
						{
							bPrepare = false;
							renderer->ptrPGE->pOsEngine.StartPGE = false;
						}

					}

				}

			}

			// Allow the user to free resources if they have overrided the destroy function
			if (!OnUserDestroy())
			{
				// User denied destroy for some reason, so continue running
				bAtomActive = true;
			}


		}

		platform->ThreadCleanUp();
	}
#endif

#if defined(__APPLE__)
	void PixelGameEngine::EngineThread()
	{
		// Allow platform to do stuff here if needed, since its now in the
		// context of this thread
		if (platform->ThreadStartUp() == olc::FAIL)	return;

		// Do engine context specific initialisation
		olc_PrepareEngine();

		// Create the CopyRight Sprite : DO NOT REMOVED
		CreateCRSprite();

		// Create user resources as part of this thread
		for (auto& ext : vExtensions) ext->OnBeforeUserCreate();
		if (!OnUserCreate()) bAtomActive = false;
		for (auto& ext : vExtensions) ext->OnAfterUserCreate();


		while (bAtomActive)
		{
			// Run as fast as possible
			while (bAtomActive) { olc_CoreUpdate(); }

			// Allow the user to free resources if they have overrided the destroy function
			if (!OnUserDestroy())
			{
				// User denied destroy for some reason, so continue running
				bAtomActive = true;
			}
		}

		platform->ThreadCleanUp();
	}
#endif

	olc::rcode PixelGameEngine::app_LoadFileFromAssets(const std::string& sFilePath, std::vector<char>* outBuffer)
	{
		return filehandler->LoadFileFromAssets(sFilePath, outBuffer);
	}

	olc::rcode PixelGameEngine::app_ExtractFileFromAssets(const std::string& sAssetFilePath, const std::string& sAppStorageFilePath)
	{
		return filehandler->ExtractFileFromAssets(sAssetFilePath, sAppStorageFilePath);
	}

	const char* PixelGameEngine::app_GetInternalAppStorage()
	{
		return filehandler->GetInternalAppStorage();
	}

	const char* PixelGameEngine::app_GetExteralAppStorage()
	{
		return filehandler->GetExteralAppStorage();
	}

	const char* PixelGameEngine::app_GetPublicAppStorage()
	{
		return filehandler->GetPublicAppStorage();
	}

	void PixelGameEngine::olc_PrepareEngine()
	{

		m_tp1 = std::chrono::system_clock::now();

		// Start OpenGL, the context is owned by the game thread
		if (platform->CreateGraphics(bFullScreen, bEnableVSYNC, vViewPos, vViewSize) == olc::FAIL) return;

		// Construct default font sheet
		olc_ConstructFontSheet();

		// As the OS can pause, restart etc our app, layer 0 may already exist, 
		// we do not want to keep recreating it, as it will cause a memory leak
		vLayers.clear();

		CreateLayer();

		vLayers[0].bUpdate = true;
		vLayers[0].bShow = true;
		SetDrawTarget(nullptr);


		m_tp2 = std::chrono::system_clock::now();
	}


	void PixelGameEngine::olc_CoreUpdate()
	{
		// Handle Timing
		m_tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
		m_tp1 = m_tp2;

		// Our time per frame coefficient
		float fElapsedTime = elapsedTime.count();
		fLastElapsed = fElapsedTime;

		//// Some platforms will need to check for events
		//platform->HandleSystemEvent();

		// Compare hardware input states from previous frame
		auto ScanHardware = [&](HWButton* pKeys, bool* pStateOld, bool* pStateNew, uint32_t nKeyCount)
		{
			for (uint32_t i = 0; i < nKeyCount; i++)
			{
				pKeys[i].bPressed = false;
				pKeys[i].bReleased = false;
				if (pStateNew[i] != pStateOld[i])
				{
					if (pStateNew[i])
					{
						pKeys[i].bPressed = !pKeys[i].bHeld;
						pKeys[i].bHeld = true;
					}
					else
					{
						pKeys[i].bReleased = true;
						pKeys[i].bHeld = false;
					}
				}
				pStateOld[i] = pStateNew[i];
			}
		};


		// We need some locks as the sensors can sample to 10000 times a second
		// This is way to fast for our engine
		// By adding some locks and cache ensure clear stable values for the engine
		mutexTouchPoints.lock();

		////// Cache mouse coordinates so they remain consistent during frame

		ScanHardware(pKeyboardState, pKeyOldState, pKeyNewState, 256);
		ScanHardware(pMouseState, pMouseOldState, pMouseNewState, nMouseButtons);
		ScanHardware(pTouchState, pTouchOldState, pTouchNewState, __INT8_MAX__);

		for (int i = 0; i < __INT8_MAX__; i++)
		{

			pTouchNewState[i] = pTouchNewStateCache[i];
			pTouchPoints[i] = pTouchPointsCache[i];

			// Strange edge case, ensures that lost touch pointers removed
			if (pTouchPoints[i].x == 0 && pTouchPoints[i].y == 0) pTouchNewStateCache[i] = false;

		}

		vMousePos = vMousePosCache;

		mutexTouchPoints.unlock();

		nMouseWheelDelta = nMouseWheelDeltaCache;
		nMouseWheelDeltaCache = 0;

		//vDroppedFiles = vDroppedFilesCache;
		//vDroppedFilesPoint = vDroppedFilesPointCache;
		//vDroppedFilesCache.clear();

#ifdef NDEBUG 
		bDisplayCopyRight = !bCompleteCR;
#endif
		if (bDisplayCopyRight)
		{
			bDisplayCopyRight = DisplayCR(fElapsedTime);

			// Display Frame
			renderer->UpdateViewport(vViewPos, vViewSize);
			renderer->ClearBuffer(olc::BLACK, true);
		}
		else
		{
			// Handle Frame Update
			bool bExtensionBlockFrame = false;
			for (auto& ext : vExtensions) bExtensionBlockFrame |= ext->OnBeforeUserUpdate(fElapsedTime);
			if (!bExtensionBlockFrame)
			{
				if (!OnUserUpdate(fElapsedTime)) bAtomActive = false;

			}
			for (auto& ext : vExtensions) ext->OnAfterUserUpdate(fElapsedTime);


			// Display Frame
			renderer->UpdateViewport(vViewPos, vViewSize);
			renderer->ClearBuffer(olc::BLACK, true);
		}



		//// Layer 0 must always exist
		vLayers[0].bUpdate = true;
		vLayers[0].bShow = true;
		SetDecalMode(DecalMode::NORMAL);
		renderer->PrepareDrawing();

		for (auto layer = vLayers.rbegin(); layer != vLayers.rend(); ++layer)
		{
			if (layer->bShow)
			{
				if (layer->funcHook == nullptr)
				{
					renderer->ApplyTexture(layer->pDrawTarget.Decal()->id);
					if (!bSuspendTextureTransfer && layer->bUpdate)
					{
						layer->pDrawTarget.Decal()->Update();
						layer->bUpdate = false;
					}

					renderer->DrawLayerQuad(layer->vOffset, layer->vScale, layer->tint);

					// Display Decals in order for this layer
					for (auto& decal : layer->vecDecalInstance)
					{
						renderer->DrawDecal(decal);
					}

					layer->vecDecalInstance.clear();
				}
				else
				{
					// Mwa ha ha.... Have Fun!!!
					layer->funcHook();
				}
			}
		}



		// Present Graphics to screen
		renderer->DisplayFrame();

		// Update Title Bar
		fFrameTimer += fElapsedTime;
		nFrameCount++;
		if (fFrameTimer >= 1.0f)
		{
			nLastFPS = nFrameCount;
			fFrameTimer -= 1.0f;
			nFrameCount = 0;
		}

	}

	void PixelGameEngine::olc_ConstructFontSheet()
	{
		std::string data;
		data += "?Q`0001oOch0o01o@F40o0<AGD4090LAGD<090@A7ch0?00O7Q`0600>00000000";
		data += "O000000nOT0063Qo4d8>?7a14Gno94AA4gno94AaOT0>o3`oO400o7QN00000400";
		data += "Of80001oOg<7O7moBGT7O7lABET024@aBEd714AiOdl717a_=TH013Q>00000000";
		data += "720D000V?V5oB3Q_HdUoE7a9@DdDE4A9@DmoE4A;Hg]oM4Aj8S4D84@`00000000";
		data += "OaPT1000Oa`^13P1@AI[?g`1@A=[OdAoHgljA4Ao?WlBA7l1710007l100000000";
		data += "ObM6000oOfMV?3QoBDD`O7a0BDDH@5A0BDD<@5A0BGeVO5ao@CQR?5Po00000000";
		data += "Oc``000?Ogij70PO2D]??0Ph2DUM@7i`2DTg@7lh2GUj?0TO0C1870T?00000000";
		data += "70<4001o?P<7?1QoHg43O;`h@GT0@:@LB@d0>:@hN@L0@?aoN@<0O7ao0000?000";
		data += "OcH0001SOglLA7mg24TnK7ln24US>0PL24U140PnOgl0>7QgOcH0K71S0000A000";
		data += "00H00000@Dm1S007@DUSg00?OdTnH7YhOfTL<7Yh@Cl0700?@Ah0300700000000";
		data += "<008001QL00ZA41a@6HnI<1i@FHLM81M@@0LG81?O`0nC?Y7?`0ZA7Y300080000";
		data += "O`082000Oh0827mo6>Hn?Wmo?6HnMb11MP08@C11H`08@FP0@@0004@000000000";
		data += "00P00001Oab00003OcKP0006@6=PMgl<@440MglH@000000`@000001P00000000";
		data += "Ob@8@@00Ob@8@Ga13R@8Mga172@8?PAo3R@827QoOb@820@0O`0007`0000007P0";
		data += "O`000P08Od400g`<3V=P0G`673IP0`@3>1`00P@6O`P00g`<O`000GP800000000";
		data += "?P9PL020O`<`N3R0@E4HC7b0@ET<ATB0@@l6C4B0O`H3N7b0?P01L3R000000020";

		fontRenderable.Create(128, 48);

		int px = 0, py = 0;
		for (size_t b = 0; b < 1024; b += 4)
		{
			uint32_t sym1 = (uint32_t)data[b + 0] - 48;
			uint32_t sym2 = (uint32_t)data[b + 1] - 48;
			uint32_t sym3 = (uint32_t)data[b + 2] - 48;
			uint32_t sym4 = (uint32_t)data[b + 3] - 48;
			uint32_t r = sym1 << 18 | sym2 << 12 | sym3 << 6 | sym4;

			for (int i = 0; i < 24; i++)
			{
				int k = r & (1 << i) ? 255 : 0;
				fontRenderable.Sprite()->SetPixel(px, py, olc::Pixel(k, k, k, k));
				if (++py == 48) { px++; py = 0; }
			}
		}

		fontRenderable.Decal()->Update();

		constexpr std::array<uint8_t, 96> vSpacing = { {
			0x03,0x25,0x16,0x08,0x07,0x08,0x08,0x04,0x15,0x15,0x08,0x07,0x15,0x07,0x24,0x08,
			0x08,0x17,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x24,0x15,0x06,0x07,0x16,0x17,
			0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x17,0x08,0x08,0x17,0x08,0x08,0x08,
			0x08,0x08,0x08,0x08,0x17,0x08,0x08,0x08,0x08,0x17,0x08,0x15,0x08,0x15,0x08,0x08,
			0x24,0x18,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x33,0x17,0x17,0x33,0x18,0x17,0x17,
			0x17,0x17,0x17,0x17,0x07,0x17,0x17,0x18,0x18,0x17,0x17,0x07,0x33,0x07,0x08,0x00, } };

		for (auto c : vSpacing) vFontSpacing.push_back({ c >> 4, c & 15 });

		// UK Standard Layout
		vKeyboardMap =
		{
			{olc::Key::A, "a", "A"}, {olc::Key::B, "b", "B"}, {olc::Key::C, "c", "C"}, {olc::Key::D, "d", "D"}, {olc::Key::E, "e", "E"},
			{olc::Key::F, "f", "F"}, {olc::Key::G, "g", "G"}, {olc::Key::H, "h", "H"}, {olc::Key::I, "i", "I"}, {olc::Key::J, "j", "J"},
			{olc::Key::K, "k", "K"}, {olc::Key::L, "l", "L"}, {olc::Key::M, "m", "M"}, {olc::Key::N, "n", "N"}, {olc::Key::O, "o", "O"},
			{olc::Key::P, "p", "P"}, {olc::Key::Q, "q", "Q"}, {olc::Key::R, "r", "R"}, {olc::Key::S, "s", "S"}, {olc::Key::T, "t", "T"},
			{olc::Key::U, "u", "U"}, {olc::Key::V, "v", "V"}, {olc::Key::W, "w", "W"}, {olc::Key::X, "x", "X"}, {olc::Key::Y, "y", "Y"},
			{olc::Key::Z, "z", "Z"},

			{olc::Key::K0, "0", ")"}, {olc::Key::K1, "1", "!"}, {olc::Key::K2, "2", "\""}, {olc::Key::K3, "3", "#"},	{olc::Key::K4, "4", "$"},
			{olc::Key::K5, "5", "%"}, {olc::Key::K6, "6", "^"}, {olc::Key::K7, "7", "&"}, {olc::Key::K8, "8", "*"},	{olc::Key::K9, "9", "("},

			{olc::Key::NP0, "0", "0"}, {olc::Key::NP1, "1", "1"}, {olc::Key::NP2, "2", "2"}, {olc::Key::NP3, "3", "3"},	{olc::Key::NP4, "4", "4"},
			{olc::Key::NP5, "5", "5"}, {olc::Key::NP6, "6", "6"}, {olc::Key::NP7, "7", "7"}, {olc::Key::NP8, "8", "8"},	{olc::Key::NP9, "9", "9"},
			{olc::Key::NP_MUL, "*", "*"}, {olc::Key::NP_DIV, "/", "/"}, {olc::Key::NP_ADD, "+", "+"}, {olc::Key::NP_SUB, "-", "-"},	{olc::Key::NP_DECIMAL, ".", "."},

			{olc::Key::PERIOD, ".", ">"}, {olc::Key::EQUALS, "=", "+"}, {olc::Key::COMMA, ",", "<"}, {olc::Key::MINUS, "-", "_"}, {olc::Key::SPACE, " ", " "},

			{olc::Key::OEM_1, ";", ":"}, {olc::Key::OEM_2, "/", "?"}, {olc::Key::OEM_3, "\'", "@"}, {olc::Key::OEM_4, "[", "{"},
			{olc::Key::OEM_5, "\\", "|"}, {olc::Key::OEM_6, "]", "}"}, {olc::Key::OEM_7, "#", "~"},

			// {olc::Key::TAB, "\t", "\t"}
		};

	}

	void PixelGameEngine::pgex_Register(olc::PGEX* pgex)
	{
		if (std::find(vExtensions.begin(), vExtensions.end(), pgex) == vExtensions.end())
			vExtensions.push_back(pgex);
	}


	PGEX::PGEX(bool bHook) { if (bHook) pge->pgex_Register(this); }
	void PGEX::OnBeforeUserCreate() {}
	void PGEX::OnAfterUserCreate() {}
	bool PGEX::OnBeforeUserUpdate(float& fElapsedTime) { return false; }
	void PGEX::OnAfterUserUpdate(float fElapsedTime) {}

	// Need a couple of statics as these are singleton instances
	// read from multiple locations
	std::atomic<bool> PixelGameEngine::bAtomActive{ false };
	olc::PixelGameEngine* olc::PGEX::pge = nullptr;
	olc::PixelGameEngine* olc::Platform::ptrPGE = nullptr;
	olc::PixelGameEngine* olc::Renderer::ptrPGE = nullptr;
	std::unique_ptr<ImageLoader> olc::Sprite::loader = nullptr;
};


#ifdef __ANDROID__

/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <jni.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

 /* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

// --------------------------------------------------------------------
// Methods used by the main tread, we intercept these in olc::EventManager
// --------------------------------------------------------------------

static void free_saved_state(struct android_app* android_app) {

	pthread_mutex_lock(&android_app->mutex);
	if (android_app->savedState != NULL) {
		free(android_app->savedState);
		android_app->savedState = NULL;
		android_app->savedStateSize = 0;
	}
	pthread_mutex_unlock(&android_app->mutex);
}

int8_t android_app_read_cmd(struct android_app* android_app) {

	int8_t cmd;
	if (read(android_app->msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
		switch (cmd) {
		case APP_CMD_SAVE_STATE:
			free_saved_state(android_app);
			break;
		}
		return cmd;
	}
	else {
		LOGE("No data on command pipe!");
	}
	return -1;
}

static void print_cur_config(struct android_app* android_app) {

	char lang[2], country[2];
	AConfiguration_getLanguage(android_app->config, lang);
	AConfiguration_getCountry(android_app->config, country);

	LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
		"keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
		"modetype=%d modenight=%d",
		AConfiguration_getMcc(android_app->config),
		AConfiguration_getMnc(android_app->config),
		lang[0], lang[1], country[0], country[1],
		AConfiguration_getOrientation(android_app->config),
		AConfiguration_getTouchscreen(android_app->config),
		AConfiguration_getDensity(android_app->config),
		AConfiguration_getKeyboard(android_app->config),
		AConfiguration_getNavigation(android_app->config),
		AConfiguration_getKeysHidden(android_app->config),
		AConfiguration_getNavHidden(android_app->config),
		AConfiguration_getSdkVersion(android_app->config),
		AConfiguration_getScreenSize(android_app->config),
		AConfiguration_getScreenLong(android_app->config),
		AConfiguration_getUiModeType(android_app->config),
		AConfiguration_getUiModeNight(android_app->config));
}

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd) {

	switch (cmd) {
	case APP_CMD_INPUT_CHANGED:
		LOGV("APP_CMD_INPUT_CHANGED\n");
		pthread_mutex_lock(&android_app->mutex);
		if (android_app->inputQueue != NULL) {
			AInputQueue_detachLooper(android_app->inputQueue);
		}
		android_app->inputQueue = android_app->pendingInputQueue;
		if (android_app->inputQueue != NULL) {
			LOGV("Attaching input queue to looper");
			AInputQueue_attachLooper(android_app->inputQueue,
				android_app->looper, LOOPER_ID_INPUT, NULL,
				&android_app->inputPollSource);
		}
		pthread_cond_broadcast(&android_app->cond);
		pthread_mutex_unlock(&android_app->mutex);
		break;

	case APP_CMD_INIT_WINDOW:
		LOGV("APP_CMD_INIT_WINDOW\n");
		pthread_mutex_lock(&android_app->mutex);
		android_app->window = android_app->pendingWindow;
		pthread_cond_broadcast(&android_app->cond);
		pthread_mutex_unlock(&android_app->mutex);

		break;

	case APP_CMD_TERM_WINDOW:
		LOGV("APP_CMD_TERM_WINDOW\n");
		pthread_cond_broadcast(&android_app->cond);
		break;

	case APP_CMD_RESUME:
	case APP_CMD_START:
	case APP_CMD_PAUSE:
	case APP_CMD_STOP:
		LOGV("activityState=%d\n", cmd);
		pthread_mutex_lock(&android_app->mutex);
		android_app->activityState = cmd;
		pthread_cond_broadcast(&android_app->cond);
		pthread_mutex_unlock(&android_app->mutex);
		break;

	case APP_CMD_CONFIG_CHANGED:
		LOGV("APP_CMD_CONFIG_CHANGED\n");
		AConfiguration_fromAssetManager(android_app->config,
			android_app->activity->assetManager);
		print_cur_config(android_app);
		break;

	case APP_CMD_DESTROY:
		LOGV("APP_CMD_DESTROY\n");
		android_app->destroyRequested = 1;
		break;
	}
}

void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd) {

	switch (cmd) {
	case APP_CMD_TERM_WINDOW:
		LOGV("APP_CMD_TERM_WINDOW\n");
		pthread_mutex_lock(&android_app->mutex);
		android_app->window = NULL;
		pthread_cond_broadcast(&android_app->cond);
		pthread_mutex_unlock(&android_app->mutex);
		break;

	case APP_CMD_SAVE_STATE:
		LOGV("APP_CMD_SAVE_STATE\n");
		pthread_mutex_lock(&android_app->mutex);
		android_app->stateSaved = 1;
		pthread_cond_broadcast(&android_app->cond);
		pthread_mutex_unlock(&android_app->mutex);
		break;

	case APP_CMD_RESUME:
		free_saved_state(android_app);
		break;
	}
}

static void android_app_destroy(struct android_app* android_app) {

	LOGV("android_app_destroy!");
	free_saved_state(android_app);
	pthread_mutex_lock(&android_app->mutex);
	if (android_app->inputQueue != NULL) {
		AInputQueue_detachLooper(android_app->inputQueue);
	}
	AConfiguration_delete(android_app->config);
	android_app->destroyed = 1;
	pthread_cond_broadcast(&android_app->cond);
	pthread_mutex_unlock(&android_app->mutex);
	// Can't touch android_app object after this.
}

static void process_input(struct android_app* app, struct android_poll_source* source) {

	AInputEvent* event = NULL;
	while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
		LOGV("New input event: type=%d\n", AInputEvent_getType(event));
		if (AInputQueue_preDispatchEvent(app->inputQueue, event)) {
			continue;
		}
		int32_t handled = 0;
		if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
		AInputQueue_finishEvent(app->inputQueue, event, handled);
	}
}

static void process_cmd(struct android_app* app, struct android_poll_source* source) {

	int8_t cmd = android_app_read_cmd(app);
	android_app_pre_exec_cmd(app, cmd);
	if (app->onAppCmd != NULL) app->onAppCmd(app, cmd);
	android_app_post_exec_cmd(app, cmd);
}



// --------------------------------------------------------------------
// Native activity interaction (called from main thread)
// --------------------------------------------------------------------

static void android_app_write_cmd(struct android_app* android_app, int8_t cmd) {

	if (write(android_app->msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd)) {
		LOGE("Failure writing android_app cmd: %s\n", strerror(errno));
	}
}

static void android_app_set_input(struct android_app* android_app, AInputQueue* inputQueue) {

	pthread_mutex_lock(&android_app->mutex);
	android_app->pendingInputQueue = inputQueue;
	android_app_write_cmd(android_app, APP_CMD_INPUT_CHANGED);
	while (android_app->inputQueue != android_app->pendingInputQueue) {
		pthread_cond_wait(&android_app->cond, &android_app->mutex);
	}
	pthread_mutex_unlock(&android_app->mutex);

}

static void android_app_set_window(struct android_app* android_app, ANativeWindow* window) {

	pthread_mutex_lock(&android_app->mutex);
	if (android_app->pendingWindow != NULL) {
		android_app_write_cmd(android_app, APP_CMD_TERM_WINDOW);
	}
	android_app->pendingWindow = window;
	if (window != NULL) {
		android_app_write_cmd(android_app, APP_CMD_INIT_WINDOW);
	}
	while (android_app->window != android_app->pendingWindow) {
		pthread_cond_wait(&android_app->cond, &android_app->mutex);
	}
	pthread_mutex_unlock(&android_app->mutex);

}

static void android_app_set_activity_state(struct android_app* android_app, int8_t cmd) {

	pthread_mutex_lock(&android_app->mutex);
	android_app_write_cmd(android_app, cmd);
	while (android_app->activityState != cmd) {
		pthread_cond_wait(&android_app->cond, &android_app->mutex);
	}
	pthread_mutex_unlock(&android_app->mutex);

}

static void android_app_free(struct android_app* android_app) {

	pthread_mutex_lock(&android_app->mutex);
	android_app_write_cmd(android_app, APP_CMD_DESTROY);
	while (!android_app->destroyed) {
		pthread_cond_wait(&android_app->cond, &android_app->mutex);
	}
	pthread_mutex_unlock(&android_app->mutex);

	close(android_app->msgread);
	close(android_app->msgwrite);
	pthread_cond_destroy(&android_app->cond);
	pthread_mutex_destroy(&android_app->mutex);
	free(android_app);

}


// --------------------------------------------------------------------
// OS Engine Start up! Lets get things linked and running
// --------------------------------------------------------------------

/*
	This is the pointer to the Android Engine Running your App
	We use this pointer throughout the engine for when we need
	to access the the Android Engine
	This pointer maintains state
*/
struct android_app* MyAndroidApp = nullptr;

/**
* Our saved state data.
* Save All your settings here
*/
struct saved_state {
	float angle;
	int32_t x;
	int32_t y;
	void* gameState;
};

/**
* Shared state for our app
* Keep this struct in place until you are 100% your game is stable
* It is used to ensure the app is cleanly removed when your game crashes
* or you press stop etc etc, NO guarantees tho.
*/
struct engine {

	struct android_app* app;
	int animating = 0;
	bool StartPGE = false;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t viewWidth = 0;
	int32_t viewHeight = 0;
	int32_t screenWidth = 0;
	int32_t screenHeight = 0;

	struct saved_state state;

	// Coming Soon...
	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

};


/*
	Engine Startup Step 3: We now create the app entry point for the PGE
	In a PGE you would simply create a console application
	and then create static void main() and off you go
	This is kind of doing the same thing, but it will create an
	void android_main(struct android_app* state) of which you
	must place in your main class.
	there is an extern void android_main(struct android_app* app)
	that will ensure everything will work... I promise..ish.
	NOTE: this method can be called more than once, try not to worry about it

*/
static void* android_app_entry(void* param) {

	// void* param is never a good idea, however at this stage of the start up
	// it is not really possible to Type the pointer been passed
	// it will just give you a headache
	// therefore void* param holds a pointer to android_app object created in android_app_create

	// cast the param pointer to a known struct
	struct android_app* android_app = (struct android_app*)param;
	MyAndroidApp = (struct android_app*)param;

	// Set up our config, i.e. where our files are stored etc etc
	// The OS will provide this info for us
	android_app->config = AConfiguration_new();
	AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

	// Debugging so you can see what is connected
	print_cur_config(android_app);

	// We need two threads from the Android
	// One to handle when the App is Paused, a phone call is received etc etc: Looper_ID_MAIN
	// One to handle input events, Keyboard, touch screen, Bluetooth game controllers etc etc
	android_app->cmdPollSource.id = LOOPER_ID_MAIN;
	android_app->cmdPollSource.app = android_app;
	android_app->cmdPollSource.process = process_cmd;
	android_app->inputPollSource.id = LOOPER_ID_INPUT;
	android_app->inputPollSource.app = android_app;
	android_app->inputPollSource.process = process_input;

	// Prepare our threads to start looping!
	ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	ALooper_addFd(looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL,
		&android_app->cmdPollSource);
	android_app->looper = looper;

	// A few mutexs and broadcasts so we can use these events in the PGE_Mobile engine
	pthread_mutex_lock(&android_app->mutex);
	android_app->running = 1;
	pthread_cond_broadcast(&android_app->cond);
	pthread_mutex_unlock(&android_app->mutex);

	struct engine engine;
	memset(&engine, 0, sizeof(engine));
	engine.app = android_app;


	// Right ready, this will now call your void android_main(struct android_app* app)
	// We still pass the android_app object, you do not have to do anything with it
	// but if you need more custom actions, create them in your void android_main(struct android_app* app) 
	android_main(android_app);

	// Here for safety, should you have bugs etc in your android_main(...) we need to ensure
	// we can destroy the application, otherwise you will have issues trying to run the application
	// later
	android_app_destroy(android_app);
	return NULL;
}

/*
	Engine Startup Step 2:
	This creates the android_app object
	We use this object to commutate with the Android
*/
static struct android_app* android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize) {

	struct android_app* android_app = (struct android_app*)malloc(sizeof(struct android_app));
	memset(android_app, 0, sizeof(struct android_app));
	android_app->activity = activity;

	pthread_mutex_init(&android_app->mutex, NULL);
	pthread_cond_init(&android_app->cond, NULL);

	if (savedState != NULL) {
		android_app->savedState = malloc(savedStateSize);
		android_app->savedStateSize = savedStateSize;
		memcpy(android_app->savedState, savedState, savedStateSize);
	}

	// Message pipes are used to commutate back and forth to the Android OS
	int msgpipe[2];
	if (pipe(msgpipe)) {
		LOGE("could not create pipe: %s", strerror(errno));
		return NULL;
	}
	android_app->msgread = msgpipe[0];
	android_app->msgwrite = msgpipe[1];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&android_app->thread, &attr, android_app_entry, android_app);

	// Wait for thread to start.
	pthread_mutex_lock(&android_app->mutex);
	while (!android_app->running) {
		pthread_cond_wait(&android_app->cond, &android_app->mutex);
	}
	pthread_mutex_unlock(&android_app->mutex);

	return android_app;
}

/*
	Engine Startup Step 1:This is the Android entry point to the application
	Here is where we start to link the Android to the PGE
	And create the pOSEngine struct so we can get/send events
	to and from the phone.

*/
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {

	LOGV("Creating: %p\n", activity);
	activity->callbacks->onDestroy = &olc::EventManager::getInstance().onDestroy;
	activity->callbacks->onStart = &olc::EventManager::getInstance().onStart;
	activity->callbacks->onResume = &olc::EventManager::getInstance().onResume;
	activity->callbacks->onSaveInstanceState = &olc::EventManager::getInstance().onSaveInstanceState;
	activity->callbacks->onPause = &olc::EventManager::getInstance().onPause;
	activity->callbacks->onStop = &olc::EventManager::getInstance().onStop;
	activity->callbacks->onConfigurationChanged = &olc::EventManager::getInstance().onConfigurationChanged;
	activity->callbacks->onLowMemory = &olc::EventManager::getInstance().onLowMemory;
	activity->callbacks->onWindowFocusChanged = &olc::EventManager::getInstance().onWindowFocusChanged;
	activity->callbacks->onNativeWindowCreated = &olc::EventManager::getInstance().onNativeWindowCreated;
	activity->callbacks->onNativeWindowDestroyed = &olc::EventManager::getInstance().onNativeWindowDestroyed;
	activity->callbacks->onInputQueueCreated = &olc::EventManager::getInstance().onInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = &olc::EventManager::getInstance().onInputQueueDestroyed;

	// This is the first phase of creating the application 
	activity->instance = android_app_create(activity, savedState, savedStateSize);
}



#endif


#ifdef __ANDROID__
namespace olc {
	EventManager& olc::EventManager::getInstance()
	{
		static EventManager instance;
		return instance;
	}

	EventManager::~EventManager() {}

	EventManager::EventManager() {}

	void EventManager::operator=(EventManager const&) {}

	void EventManager::HandleCommand(struct android_app* app, int32_t cmd)
	{
		struct engine* engine = (struct engine*)app->userData;

		switch (cmd) {

		case APP_CMD_SAVE_STATE:
		{
			platform->ptrPGE->pOsEngine.LostFocus = false;
			platform->ptrPGE->OnSaveStateRequested();
			// The system has asked us to save our current state.  Do so.
			engine->app->savedState = malloc(sizeof(struct saved_state));
			*((struct saved_state*)engine->app->savedState) = engine->state;
			engine->app->savedStateSize = sizeof(struct saved_state);
			break;
		}

		case APP_CMD_RESUME:
		{
			platform->ptrPGE->OnRestoreStateRequested();
		}

		case APP_CMD_INIT_WINDOW:
		{
			// The window is being shown, get it ready.
			if (MyAndroidApp->window != NULL) {

				// it is now safe for the PGE Engine to start!
				platform->ptrPGE->pOsEngine.LostFocus = false;
				platform->ptrPGE->pOsEngine.StartPGE = true;
				platform->ptrPGE->pOsEngine.animating = 1;


				platform->ptrPGE->pOsEngine.sensorManager = ASensorManager_getInstance();
				platform->ptrPGE->pOsEngine.sensorEventQueue = ASensorManager_createEventQueue(platform->ptrPGE->pOsEngine.sensorManager, platform->ptrPGE->pOsEngine.app->looper, LOOPER_ID_USER, NULL, NULL);

			}
			break;

		}

		case APP_CMD_TERM_WINDOW:
		{
			// The window is being hidden or closed, clean it up.
			//platform->ApplicationCleanUp();
			//platform->ThreadCleanUp();
			//renderer->DestroyDevice();
			//engine_term_display(engine);
			break;
		}
		case APP_CMD_GAINED_FOCUS:
		{
			// When our app gains focus, we start monitoring the accelerometer.
			//if (platform->ptrPGE->pOsEngine.accelerometerSensor != NULL) {
			//	ASensorEventQueue_enableSensor(platform->ptrPGE->pOsEngine.sensorEventQueue,
			//		platform->ptrPGE->pOsEngine.accelerometerSensor);

			//	// We'd like to get 60 events per second (in microseconds).
			//	ASensorEventQueue_setEventRate(platform->ptrPGE->pOsEngine.sensorEventQueue,
			//		platform->ptrPGE->pOsEngine.accelerometerSensor, (1000L / 60) * 1000);
			//}

			const ASensor* pASensor = nullptr;
			uint32_t sampleRate = 0;
			for (auto& s : platform->ptrPGE->pOsEngine.deviceSensors)
			{
				pASensor = std::get<1>(s);
				sampleRate = std::get<2>(s);
				ASensorEventQueue_enableSensor(platform->ptrPGE->pOsEngine.sensorEventQueue, pASensor);
				ASensorEventQueue_setEventRate(platform->ptrPGE->pOsEngine.sensorEventQueue, pASensor, sampleRate);
			}


			if (platform->ptrPGE->pOsEngine.LostFocus)
			{
				platform->ptrPGE->pOsEngine.animating = 1;
				platform->ptrPGE->pOsEngine.LostFocus = false;
				platform->ptrPGE->SetFocused(true);
			}

			break;
		}

		case APP_CMD_LOST_FOCUS:
		{
			// When our app loses focus, we stop monitoring the accelerometer.
			// This is to avoid consuming battery while not being used.


			const ASensor* pASensor = nullptr;
			uint32_t sampleRate = 0;
			for (auto& s : platform->ptrPGE->pOsEngine.deviceSensors)
			{
				pASensor = std::get<1>(s);
				sampleRate = std::get<2>(s);
				ASensorEventQueue_disableSensor(platform->ptrPGE->pOsEngine.sensorEventQueue, pASensor);
			}

			// Also stop animating.
			platform->ptrPGE->pOsEngine.LostFocus = true;
			platform->ptrPGE->pOsEngine.animating = 0;
			platform->ptrPGE->SetFocused(false);


			break;
		}

		}
	}

	int32_t EventManager::HandleInput(struct android_app* app, AInputEvent* event)
	{
		// First we get what device sent the event, and then the event itself

		int32_t device = AInputEvent_getSource(event);
		int32_t inputEvent = AInputEvent_getType(event);

		// There are 5 Master Events, but we only care about Key and Motion
		switch (inputEvent)
		{

		case AINPUT_EVENT_TYPE_KEY:
		{
			// Key Event, could  be a keyboard or soft keyboard (touch screen)
			switch (device)
			{
			case AINPUT_SOURCE_KEYBOARD:
			{
				int action = AKeyEvent_getAction(event);
				switch (action)
				{
				case AKEY_EVENT_ACTION_DOWN:
				{
					int32_t key = AKeyEvent_getKeyCode(event);
					platform->ptrPGE->olc_UpdateKeyState(key, true);
					return CAPTURED;
					break;
				}
				case AKEY_EVENT_ACTION_UP:
				{
					int32_t key = AKeyEvent_getKeyCode(event);
					platform->ptrPGE->olc_UpdateKeyState(key, false);
					return CAPTURED;
					break;
				}
				default:
					return RELEASED;
					break;
				}
				// Lets handle the key pressed/released
			}

			default:
			{
				return RELEASED;
				break;
			}

			}

		}
		case AINPUT_EVENT_TYPE_MOTION:
		{

			// A little auto to update the touch points if pressed / unpressed 
			auto updateTouchPoints = [&](int pointerIndex, bool touchState, bool movement = false)
			{
				//int32_t pointerId = AMotionEvent_getPointerId(event, pointerIndex);	// Gets the touch pionter device Id
				int32_t tPosX = AMotionEvent_getX(event, pointerIndex);				// Gets the current x position of this touch point
				int32_t tPosY = AMotionEvent_getY(event, pointerIndex);				// Gets the current y position of the toucy point
				platform->ptrPGE->olc_UpdateTouch(tPosX, tPosY, pointerIndex);		// Update the PGE Engine {X, Y} for this touch point
				platform->ptrPGE->olc_UpdateTouchState(pointerIndex, touchState);	// Update the touchState true/false

				// strange edge case, ensures that lost touch pointers removed
				if (tPosX == 0 && tPosY == 0)
				{
					platform->ptrPGE->olc_UpdateTouchState(pointerIndex, false);
				}

			};


			switch (device)
			{
				/** Touch Screen, Touchpad **/
			case AINPUT_SOURCE_TOUCHPAD:
			case AINPUT_SOURCE_TOUCHSCREEN:
			{

				size_t count = AMotionEvent_getPointerCount(event);
				int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;

				int32_t index = ((AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT);
				//int32_t pointerID = AMotionEvent_getPointerId(event, index);


				switch (action) {

				case AMOTION_EVENT_ACTION_DOWN:
				{
					updateTouchPoints(0, true);
					return CAPTURED;
					break;
				}

				case AMOTION_EVENT_ACTION_POINTER_DOWN:
				{

					updateTouchPoints(index, true);
					return CAPTURED;
					break;
				}


				case AMOTION_EVENT_ACTION_UP:
				{
					updateTouchPoints(0, false);
					return CAPTURED;
					break;
				}

				case AMOTION_EVENT_ACTION_POINTER_UP:
				{
					updateTouchPoints(index, false);
					return CAPTURED;
					break;
				}

				case AMOTION_EVENT_ACTION_MOVE:
				{
					for (int i = 0; i < count; i++)
					{
						//If it is moving it is pressed!
						updateTouchPoints(i, true, true);
					}

					return CAPTURED;
					break;
				}


				}


			}

			case 20482: // Speical Case: Used for Android Emulator
			case AINPUT_SOURCE_STYLUS:
			case AINPUT_SOURCE_BLUETOOTH_STYLUS:
			case AINPUT_SOURCE_MOUSE:
			{
				int32_t mPosX = AMotionEvent_getX(event, 0);
				int32_t mPosY = AMotionEvent_getY(event, 0);
				int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
				int button = AMotionEvent_getButtonState(event);

				platform->ptrPGE->olc_UpdateMouse(mPosX, mPosY);

				switch (action) {
				case AMOTION_EVENT_ACTION_DOWN:
					platform->ptrPGE->olc_UpdateMouseState(button, true);
					return CAPTURED;
					break;

				case AMOTION_EVENT_ACTION_UP:
					platform->ptrPGE->olc_UpdateMouseState(button, false);
					return CAPTURED;
					break;

				case AMOTION_EVENT_ACTION_SCROLL:
					return CAPTURED;
					break;

				case AMOTION_EVENT_ACTION_MOVE:
					return RELEASED;
					break;
				}


			}

			case AINPUT_SOURCE_TRACKBALL:
			{
				int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK;
				return RELEASED;
			}

			default:
			{
				return RELEASED;
				break;
			}

			}

		}
		case AINPUT_EVENT_TYPE_FOCUS:
		case AINPUT_EVENT_TYPE_CAPTURE:
		case AINPUT_EVENT_TYPE_DRAG:
		{
			// Not supported let the OS deal with it
			return RELEASED;
			break;
		}

		default:
		{
			return RELEASED;
			break;
		}

		}



		return RELEASED;
	}


	void EventManager::onDestroy(ANativeActivity* activity)
	{
		LOGV("Destroy: %p\n", activity);
		platform->ptrPGE->olc_Terminate();
		android_app_free((struct android_app*)activity->instance);
	}

	void EventManager::onStart(ANativeActivity* activity)
	{
		LOGV("Start: %p\n", activity);
		android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_START);
	}

	void EventManager::onResume(ANativeActivity* activity)
	{
		LOGV("Resume: %p\n", activity);
		// TOPO: correct this quick hack
		platform->ptrPGE->SetFocused(true);

		android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_RESUME);
	}

	void* EventManager::onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
	{
		struct android_app* android_app = (struct android_app*)activity->instance;
		void* savedState = NULL;

		LOGV("SaveInstanceState: %p\n", activity);
		pthread_mutex_lock(&android_app->mutex);
		android_app->stateSaved = 0;
		android_app_write_cmd(android_app, APP_CMD_SAVE_STATE);
		while (!android_app->stateSaved) {
			pthread_cond_wait(&android_app->cond, &android_app->mutex);
		}

		if (android_app->savedState != NULL) {
			savedState = android_app->savedState;
			*outLen = android_app->savedStateSize;
			android_app->savedState = NULL;
			android_app->savedStateSize = 0;
		}

		pthread_mutex_unlock(&android_app->mutex);

		return savedState;
	}

	void EventManager::onPause(ANativeActivity* activity)
	{
		LOGV("Pause: %p\n", activity);
		platform->ptrPGE->SetFocused(false);
		android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_PAUSE);
	}

	void EventManager::onStop(ANativeActivity* activity)
	{
		LOGV("Stop: %p\n", activity);

		android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_STOP);

	}

	void EventManager::onConfigurationChanged(ANativeActivity* activity)
	{
		struct android_app* android_app = (struct android_app*)activity->instance;
		LOGV("ConfigurationChanged: %p\n", activity);
		android_app_write_cmd(android_app, APP_CMD_CONFIG_CHANGED);
	}

	void EventManager::onLowMemory(ANativeActivity* activity)
	{
		struct android_app* android_app = (struct android_app*)activity->instance;
		LOGV("LowMemory: %p\n", activity);
		android_app_write_cmd(android_app, APP_CMD_LOW_MEMORY);
		// TODO: we need to manage this somehow

	}

	void EventManager::onWindowFocusChanged(ANativeActivity* activity, int focused)
	{
		LOGV("WindowFocusChanged: %p -- %d\n", activity, focused);
		android_app_write_cmd((struct android_app*)activity->instance,
			focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);

		// Yep made it explicit, as focused is an int and I am not taking any chances with Android 
		platform->ptrPGE->SetFocused(focused ? true : false);

	}

	void EventManager::onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
	{
		LOGV("NativeWindowCreated: %p -- %p\n", activity, window);
		android_app_set_window((struct android_app*)activity->instance, window);
	}

	void EventManager::onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
	{
		LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);
		android_app_set_window((struct android_app*)activity->instance, NULL);
	}

	void EventManager::onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
	{
		LOGV("InputQueueCreated: %p -- %p\n", activity, queue);
		android_app_set_input((struct android_app*)activity->instance, queue);
	}

	void EventManager::onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
	{
		LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);
		android_app_set_input((struct android_app*)activity->instance, NULL);
	}

}
#endif // __ANDROID__

#ifdef __APPLE__

EventManager& olc::EventManager::getInstance()
{
	static EventManager instance;
	return instance;
}

EventManager::~EventManager() {}

EventManager::EventManager() {}

void EventManager::operator=(EventManager const&) {}

void EventManager::HandleCommand(int32_t cmd)
{
	//platform->engine_handle_cmd(app, cmd);
}

int32_t EventManager::HandleInput(int32_t tbd)
{
	return 0;
}


#endif // __APPLE__


namespace olc {

	class Platform_Android : public olc::Platform
	{

	public:

		virtual olc::rcode ApplicationStartUp() override
		{

			return olc::rcode::OK;
		}

		virtual olc::rcode ApplicationCleanUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ThreadStartUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();

			return olc::OK;
		}

		virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({}, bFullScreen, bEnableVSYNC) == olc::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return olc::rcode::OK;
			}
			else
				return olc::rcode::FAIL;
			return olc::rcode::OK;
		}

		virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) override
		{

			renderer->PrepareDevice();
			android_app* app = (android_app*)MyAndroidApp;
			app->contentRect.left = vWindowPos.x;
			app->contentRect.top = vWindowPos.y;
			app->contentRect.right = vWindowSize.x;
			app->contentRect.bottom = vWindowSize.y;

			return olc::rcode::OK;
		}

		virtual olc::rcode SetWindowTitle(const std::string& s) override
		{

			return olc::OK;
		}

		virtual olc::rcode StartSystemEventLoop() override
		{
			return rcode::OK;
		}

		virtual olc::rcode HandleSystemEvent() override
		{
			return olc::OK;
		}

	};
}



namespace olc {

	// Suppress -Wunused-private-field cleans up a few warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-private-field"


	class Renderer_OGLES10 : public olc::Renderer
	{

	private:
		EGLDisplay olc_Display;
		EGLConfig olc_Config;
		EGLContext olc_Context;
		EGLSurface olc_Surface;

	private:
		locCreateShader_t* locCreateShader = nullptr;
		locShaderSource_t* locShaderSource = nullptr;
		locCompileShader_t* locCompileShader = nullptr;
		locDeleteShader_t* locDeleteShader = nullptr;
		locCreateProgram_t* locCreateProgram = nullptr;
		locDeleteProgram_t* locDeleteProgram = nullptr;
		locLinkProgram_t* locLinkProgram = nullptr;
		locAttachShader_t* locAttachShader = nullptr;
		locBindBuffer_t* locBindBuffer = nullptr;
		locBufferData_t* locBufferData = nullptr;
		locGenBuffers_t* locGenBuffers = nullptr;
		locVertexAttribPointer_t* locVertexAttribPointer = nullptr;
		locEnableVertexAttribArray_t* locEnableVertexAttribArray = nullptr;
		locUseProgram_t* locUseProgram = nullptr;
		locBindVertexArray_t* locBindVertexArray = nullptr;
		locGenVertexArrays_t* locGenVertexArrays = nullptr;
		locSwapInterval_t* locSwapInterval = nullptr;
		locGetShaderInfoLog_t* locGetShaderInfoLog = nullptr;

		uint32_t m_nFS = 0;
		uint32_t m_nVS = 0;
		uint32_t m_nQuadShader = 0;
		uint32_t m_vbQuad = 0;
		uint32_t m_vaQuad = 0;

		struct locVertex
		{
			float pos[3];
			olc::vf2d tex;
			olc::Pixel col;
		};

		locVertex pVertexMem[OLC_MAX_VERTS];

		olc::Renderable rendBlankQuad;


	private:
		bool mFullScreen = false;
		bool bSync = false;			// Left in for backward comp. will not work anymore :( I will think of something for you folks
		olc::DecalMode nDecalMode = olc::DecalMode(-1); // Thanks Gusgo & Bispoo
		olc::DecalStructure nDecalStructure = olc::DecalStructure(-1);

#pragma GCC diagnostic pop
	public:

		void PrepareDevice() override
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		olc::rcode CreateDevice(std::vector<void*> params, bool bFullScreen = true, bool bVSYNC = false) override
		{
			// This is a heavy going function, but must run in order to ensure the app loads

			// 1: Setup out OpenGLES settings (NOTE: these are not the same as in the PGE 2.0)
			EGLint const attribute_list[] = { EGL_SURFACE_TYPE, EGL_OPENGL_ES2_BIT, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE };
			EGLint const context_config[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
			EGLint num_config;
			EGLint w, h, format;

			// 2: Get a pointer to our App (Android = MyAndroidApp, iOS = MyiOSApp), get our screen size
			android_app* app = renderer->ptrPGE->pOsEngine.app;
			int32_t nFullScreenWidth = ANativeWindow_getWidth(app->window);
			int32_t nFullScreenHeight = ANativeWindow_getHeight(app->window);

			// 3: Get, Initialize and configure our display
			olc_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			eglInitialize(olc_Display, nullptr, nullptr);
			eglChooseConfig(olc_Display, attribute_list, &olc_Config, 1, &num_config);
			eglGetConfigAttrib(olc_Display, olc_Config, EGL_NATIVE_VISUAL_ID, &format);

			// 4: Configure our display for FullScreen | Viewport
			mFullScreen = bFullScreen;
			if (bFullScreen)
			{
				// Set the buffer to auto scale te app to fit the screen
				olc::vi2d vSize = renderer->ptrPGE->GetScreenSize();
				ANativeWindow_setBuffersGeometry(app->window, vSize.x, vSize.y, format);
				ANativeActivity_setWindowFormat(app->activity, format);


			}
			else
			{
				// Set the buffer to display the app in the centre of the screen
				ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);
			}

			// 5: AWINDOW_FLAG_FULLSCREEN tell Android to hide title bar, status etc
			// See: https://developer.android.com/ndk/reference/group/native-activity and https://developer.android.com/ndk/reference/group/native-activity#group___native_activity_1gga2f1398dba5e4a5616b83437528bdb28eaca1f1d91313d7c32bb7982d8a5abcd71
			ANativeActivity_setWindowFlags(app->activity, 0x00000400, 0);

			// 6: Create an EGL rendering context
			olc_Context = eglCreateContext(olc_Display, olc_Config, EGL_NO_CONTEXT, context_config);
			olc_Surface = eglCreateWindowSurface(olc_Display, olc_Config, app->window, nullptr);
			eglMakeCurrent(olc_Display, olc_Surface, olc_Surface, olc_Context);

			// 7: Setup buffers interval
			locSwapInterval = &eglSwapInterval;
			locSwapInterval(olc_Display, bVSYNC ? 1 : 0);

			// 8: Setup Linkage to OpenGLES Command
			locCreateShader = OGL_LOAD(locCreateShader_t, glCreateShader);
			locCompileShader = OGL_LOAD(locCompileShader_t, glCompileShader);
			locShaderSource = OGL_LOAD(locShaderSource_t, glShaderSource);
			locDeleteShader = OGL_LOAD(locDeleteShader_t, glDeleteShader);
			locCreateProgram = OGL_LOAD(locCreateProgram_t, glCreateProgram);
			locDeleteProgram = OGL_LOAD(locDeleteProgram_t, glDeleteProgram);
			locLinkProgram = OGL_LOAD(locLinkProgram_t, glLinkProgram);
			locAttachShader = OGL_LOAD(locAttachShader_t, glAttachShader);
			locBindBuffer = OGL_LOAD(locBindBuffer_t, glBindBuffer);
			locBufferData = OGL_LOAD(locBufferData_t, glBufferData);
			locGenBuffers = OGL_LOAD(locGenBuffers_t, glGenBuffers);
			locVertexAttribPointer = OGL_LOAD(locVertexAttribPointer_t, glVertexAttribPointer);
			locEnableVertexAttribArray = OGL_LOAD(locEnableVertexAttribArray_t, glEnableVertexAttribArray);
			locUseProgram = OGL_LOAD(locUseProgram_t, glUseProgram);
			locGetShaderInfoLog = OGL_LOAD(locGetShaderInfoLog_t, glGetShaderInfoLog);

			// 9: Bind our Arrays 
			locBindVertexArray = glBindVertexArrayOES;
			locGenVertexArrays = glGenVertexArraysOES;

			// 10: Load & Compile Quad Shader - assumes no errors 
			// 0x8B30 = GL_FRAGMENT_SHADER
			m_nFS = locCreateShader(GL_FRAGMENT_SHADER);

			//*************************************************************
			// 11: Now we need to create a program that will link the PGE
			// To OPENGLES Engine: 
			// TODO: Temp set "#version 200 es\n" as x86_64 simulators do not support OpenGLES 3
			//*************************************************************
			const GLchar* strFS =
#if defined(__arm__) || defined(__aarch64__)
				"#version 300 es\n"
				"precision mediump float;"
#else
				"#version 200 es\n"
				"precision mediump float;"
#endif
				"out vec4 pixel;\n""in vec2 oTex;\n"
				"in vec4 oCol;\n""uniform sampler2D sprTex;\n""void main(){pixel = texture(sprTex, oTex) * oCol;}";
			locShaderSource(m_nFS, 1, &strFS, NULL);
			locCompileShader(m_nFS);

			// 0x8B31 = GL_VERTEX_SHADER
			m_nVS = locCreateShader(GL_VERTEX_SHADER);
			const GLchar* strVS =
#if defined(__arm__) || defined(__aarch64__)
				"#version 300 es\n"
				"precision mediump float;"
#else
				"#version 200 es\n"
				"precision mediump float;"
#endif
				"layout(location = 0) in vec3 aPos;\n""layout(location = 1) in vec2 aTex;\n"
				"layout(location = 2) in vec4 aCol;\n""out vec2 oTex;\n""out vec4 oCol;\n"
				"void main(){ float p = 1.0 / aPos.z; gl_Position = p * vec4(aPos.x, aPos.y, 0.0, 1.0); oTex = p * aTex; oCol = aCol;}";

			// 12: Configure our Shaders, Buffers, Textures
			locShaderSource(m_nVS, 1, &strVS, NULL);
			locCompileShader(m_nVS);
			m_nQuadShader = locCreateProgram();
			locAttachShader(m_nQuadShader, m_nFS);
			locAttachShader(m_nQuadShader, m_nVS);
			locLinkProgram(m_nQuadShader);

			// 14: Create Quads
			locGenBuffers(1, &m_vbQuad);
			locGenVertexArrays(1, &m_vaQuad);
			locBindVertexArray(m_vaQuad);
			locBindBuffer(GL_ARRAY_BUFFER, m_vbQuad);

			locVertex verts[OLC_MAX_VERTS];
			// 0x8892 == GL_ARRAY_BUFFER, 0x88E0 == GL_DRAW_STREAM of which is not supported, replaced with 0x88E4 GL_STATIC_DRAW
			locBufferData(GL_ARRAY_BUFFER, sizeof(locVertex) * OLC_MAX_VERTS, verts, GL_STATIC_DRAW);
			locVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(locVertex), 0); locEnableVertexAttribArray(0);
			locVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(locVertex), (void*)(3 * sizeof(float))); locEnableVertexAttribArray(1);
			locVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(locVertex), (void*)(5 * sizeof(float)));	locEnableVertexAttribArray(2);
			locBindBuffer(GL_ARRAY_BUFFER, 0);
			locBindVertexArray(0);

			// 15: Create blank texture for no sprite decals
			rendBlankQuad.Create(1, 1);
			rendBlankQuad.Sprite()->GetData()[0] = olc::WHITE;
			rendBlankQuad.Decal()->Update();

			// 16: Update the pOSEngine struct, so we can use it later
			eglQuerySurface(olc_Display, olc_Surface, EGL_WIDTH, &w);
			eglQuerySurface(olc_Display, olc_Surface, EGL_HEIGHT, &h);

			renderer->ptrPGE->pOsEngine.display = olc_Display;
			renderer->ptrPGE->pOsEngine.surface = olc_Surface;
			renderer->ptrPGE->pOsEngine.context = olc_Context;
			renderer->ptrPGE->pOsEngine.viewHeight = h;
			renderer->ptrPGE->pOsEngine.viewWidth = w;
			renderer->ptrPGE->pOsEngine.screenHeight = nFullScreenHeight;
			renderer->ptrPGE->pOsEngine.screenWidth = nFullScreenWidth;

			// Create the content RECT, this is where your game graphics live
			app->contentRect.left = 0;
			app->contentRect.top = 0;
			app->contentRect.right = w;
			app->contentRect.bottom = h;
			olc::vi2d vWindowSize = { w, h };

			// 17: Create plane and update
			if (platform->CreateWindowPane({ 0, 0 }, vWindowSize, bFullScreen) != olc::OK) return olc::FAIL;
			platform->ptrPGE->olc_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

			return olc::rcode::OK;
		}

		olc::rcode DestroyDevice() override
		{

			if (olc_Display != EGL_NO_DISPLAY) {

				eglMakeCurrent(olc_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

				if (olc_Context != EGL_NO_CONTEXT) {
					eglDestroyContext(olc_Display, olc_Context);
				}

				if (olc_Surface != EGL_NO_SURFACE) {
					eglDestroySurface(olc_Display, olc_Surface);
				}

				eglTerminate(olc_Display);
			}
			renderer->ptrPGE->pOsEngine.animating = 0;
			olc_Display = EGL_NO_DISPLAY;
			olc_Context = EGL_NO_CONTEXT;
			olc_Surface = EGL_NO_SURFACE;
			return olc::rcode::OK;
		}

		void DisplayFrame() override
		{

			if (olc_Display == NULL)
			{
				// Nothing is displaying just return
				return;
			}

			eglSwapBuffers(olc_Display, olc_Surface);

		}

		void PrepareDrawing() override
		{
			glEnable(GL_BLEND);
			nDecalMode = DecalMode::NORMAL;
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			locUseProgram(m_nQuadShader);
			locBindVertexArray(m_vaQuad);

			locVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(locVertex), 0); locEnableVertexAttribArray(0);
			locVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(locVertex), (void*)(3 * sizeof(float))); locEnableVertexAttribArray(1);
			locVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(locVertex), (void*)(5 * sizeof(float)));	locEnableVertexAttribArray(2);

		}

		void SetDecalMode(const olc::DecalMode& mode) override
		{
			if (mode != nDecalMode)
			{
				switch (mode)
				{
				case olc::DecalMode::NORMAL:
				case olc::DecalMode::MODEL3D:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case olc::DecalMode::ADDITIVE:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					break;
				case olc::DecalMode::MULTIPLICATIVE:
					glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case olc::DecalMode::STENCIL:
					glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
					break;
				case olc::DecalMode::ILLUMINATE:
					glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
					break;
				case olc::DecalMode::WIREFRAME:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				}

				nDecalMode = mode;
			}
		}

		void DrawLayerQuad(const olc::vf2d& offset, const olc::vf2d& scale, const olc::Pixel tint) override
		{
			locBindBuffer(GL_ARRAY_BUFFER, m_vbQuad);
			locVertex verts[4] = {
				{{-1.0f, -1.0f, 1.0}, {0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y}, tint},
				{{+1.0f, -1.0f, 1.0}, {1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y}, tint},
				{{-1.0f, +1.0f, 1.0}, {0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y}, tint},
				{{+1.0f, +1.0f, 1.0}, {1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y}, tint},
			};

			locBufferData(GL_ARRAY_BUFFER, sizeof(locVertex) * 4, verts, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


		}

		void DrawDecal(const olc::DecalInstance& decal) override
		{
			// 0x8892 == GL_ARRAY_BUFFER, 0x88E0 == GL_DRAW_STREAM of which is not supported, replaced with 0x88E4 GL_STATIC_DRAW
			// 0x8892 == GL_ARRAY_BUFFER,

			SetDecalMode(decal.mode);
			if (decal.decal == nullptr)
				glBindTexture(GL_TEXTURE_2D, rendBlankQuad.Decal()->id);
			else
				glBindTexture(GL_TEXTURE_2D, decal.decal->id);

			locBindBuffer(GL_ARRAY_BUFFER, m_vbQuad);

			for (uint32_t i = 0; i < decal.points; i++)
				pVertexMem[i] = { { decal.pos[i].x, decal.pos[i].y, decal.w[i] }, { decal.uv[i].x, decal.uv[i].y }, decal.tint[i] };

			locBufferData(GL_ARRAY_BUFFER, sizeof(locVertex) * decal.points, pVertexMem, GL_STATIC_DRAW);

			if (nDecalMode == DecalMode::WIREFRAME)
				glDrawArrays(GL_LINE_LOOP, 0, decal.points);
			else
			{
				if (decal.structure == olc::DecalStructure::FAN)
					glDrawArrays(GL_TRIANGLE_FAN, 0, decal.points);
				else if (decal.structure == olc::DecalStructure::STRIP)
					glDrawArrays(GL_TRIANGLE_STRIP, 0, decal.points);
				else if (decal.structure == olc::DecalStructure::LIST)
					glDrawArrays(GL_TRIANGLES, 0, decal.points);
			}


		}

		uint32_t CreateTexture(const uint32_t width, const uint32_t height, const bool filtered, const bool clamp) override
		{
			UNUSED(width);
			UNUSED(height);
			uint32_t id = 0;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			if (filtered)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

			if (clamp)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}


			return id;
		}

		uint32_t DeleteTexture(const uint32_t id) override
		{
			glDeleteTextures(1, &id);
			return id;
		}

		void UpdateTexture(uint32_t id, olc::Sprite* spr) override
		{
			UNUSED(id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ReadTexture(uint32_t id, olc::Sprite* spr) override
		{
			glReadPixels(0, 0, spr->width, spr->height, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ApplyTexture(uint32_t id) override
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void ClearBuffer(olc::Pixel p, bool bDepth) override
		{
			glClearColor(float(p.r) / 255.0f, float(p.g) / 255.0f, float(p.b) / 255.0f, float(p.a) / 255.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
		}

		void UpdateViewport(const olc::vi2d& pos, const olc::vi2d& size) override
		{
			glViewport(pos.x, pos.y, size.x, size.y);
		}


	};



}

#pragma region Image_STB
// O------------------------------------------------------------------------------O
// | START IMAGE LOADER: stb_image.h, all systems, very fast                      |
// O------------------------------------------------------------------------------O
// Thanks to Sean Barrett - https://github.com/nothings/stb/blob/master/stb_image.h
// MIT License - Copyright(c) 2017 Sean Barrett

// Note you need to download the above file into your project folder, and
// #define OLC_IMAGE_STB 
// #define OLC_PGE_APPLICATION
// #include "olcPixelGameEngine.h"

#if defined(__ANDROID__)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace olc
{
	class ImageLoader_STB_ANDROID : public olc::ImageLoader
	{
	public:
		ImageLoader_STB_ANDROID() : ImageLoader()
		{}

		olc::rcode LoadImageResource(olc::Sprite* spr, const std::string& sImageFile, olc::ResourcePack* pack) override
		{
			std::vector<char> buffer;
			std::string sAssestFile = sImageFile;

			while (sAssestFile[0] == '/' && sAssestFile.length() > 0)
			{
				sAssestFile.erase(0, 1);
			}

			int retCode = GetImageBuffer(spr, sAssestFile, &buffer);
			if (retCode != rcode::OK) return (olc::rcode)retCode;

			UNUSED(pack); // Clear out existing sprite
			spr->pColData.clear();

			// Load the image from the buffer into STB for rendering 
			stbi_uc* bytes = nullptr;
			int w = 0, h = 0, cmp = 0;
			bytes = stbi_load_from_memory((unsigned char*)buffer.data(), buffer.size(), &w, &h, &cmp, 4);
			if (!bytes) return olc::rcode::FAIL;

			// Update the sprite
			spr->width = w; spr->height = h;
			spr->pColData.resize(spr->width * spr->height, olc::BLANK);

			std::memcpy(spr->pColData.data(), bytes, spr->width * spr->height * 4);

			// Clean up
			delete[] bytes;
			buffer.clear();
			return olc::rcode::OK;
		}

		olc::rcode GetImageBuffer(olc::Sprite* spr, const std::string& sImageFile, std::vector<char>* buffer) override
		{
			// Right Android
			// the APK is an Android version of a ResourcePack, in short you do not need a ResourcePack with Android
			// The APK already has compress, index and secured your assets all bundled up in a neat package APK.
			// Please read the Readme.txt in the Android.Package project under assets/readme.txt for the rulez... you will thank me later

			// This code will look very out of place, but there is a mountain of documentation that explains it
			// In short this is 'C' on steroids

			// Pre check


			// 1: Lets get a pointer to the Android Asset Manager
			android_app* MyAndroidApp = platform->ptrPGE->pOsEngine.app;
			AAssetManager* pAssetManager = MyAndroidApp->activity->assetManager;


			//2: Open a pointer to the asset and tell Android we will in the future request a buffer
			// For MP3, or AVIs etc, AASSET_MODE_STREAMING might be a better choice 
			AAsset* pAsset = AAssetManager_open(pAssetManager, sImageFile.c_str(), AASSET_MODE_BUFFER);
			if (pAsset == nullptr) return rcode::NO_FILE;

			//4: Lets extract the compress image into a buffer
			off64_t length = AAsset_getLength64(pAsset);				//	Holds size of searched file
			off64_t remaining = AAsset_getRemainingLength64(pAsset);	//	Keeps track of remaining bytes to read
			size_t Mb = 1000 * 1024;									//	1Mb is maximum Android chunk size for compressed assets 
			size_t currChunk;											//	Current Chuck of data we are processing
			buffer->reserve(length);									//	Resize our buffer


			// While we have still some data to read
			while (remaining != 0)
			{
				// Set proper size for our next chunk
				if (remaining >= Mb)
				{
					currChunk = Mb;
				}
				else
				{
					currChunk = remaining;
				}
				char chunk[currChunk];

				// Read data chunk...
				if (AAsset_read(pAsset, chunk, currChunk) > 0) // returns less than 0 on error
				{
					// ...and append it to our vector
					buffer->insert(buffer->end(), chunk, chunk + currChunk);
					remaining = AAsset_getRemainingLength64(pAsset);
				}
			}
			AAsset_close(pAsset);

			return olc::rcode::OK;

		}

		olc::rcode SaveImageResource(olc::Sprite* spr, const std::string& sImageFile) override
		{
			// TODO: Currently you cannot save back into the APK (Fancy Zip file) that the android uses
			return olc::rcode::FAIL;
		}


	};

	class FileHandler_ANDROID : public olc::FileHandler
	{
	public:
		FileHandler_ANDROID() : FileHandler()
		{}

		virtual olc::rcode LoadFileFromAssets(const std::string& sFilePath, std::vector<char>* outBuffer) override
		{
			//Pre Checks
			if (sFilePath.length() < 1) return rcode::NO_FILE;

			// 1: Lets get a pointer to the Android Asset Manager
			android_app* MyAndroidApp = platform->ptrPGE->pOsEngine.app;
			AAssetManager* pAssetManager = MyAndroidApp->activity->assetManager;


			//2: Open a pointer to the asset and tell Android we will in the future request a buffer
			// For MP3, or AVIs etc, AASSET_MODE_STREAMING might be a better choice 
			AAsset* pAsset = AAssetManager_open(pAssetManager, sFilePath.c_str(), AASSET_MODE_BUFFER);
			if (pAsset == nullptr) return rcode::NO_FILE;

			//3: Lets extract the compress image into a buffer
			off64_t length = AAsset_getLength64(pAsset);				//	Holds size of searched file
			if (length < 1) return rcode::FAIL;
			off64_t remaining = AAsset_getRemainingLength64(pAsset);	//	Keeps track of remaining bytes to read
			size_t Mb = 1000 * 1024;									//	1Mb is maximum Android chunk size for compressed assets 
			size_t currChunk;											//	Current Chuck of data we are processing
			outBuffer->reserve(length);									//	Resize our buffer
			if (length < 1) return rcode::FAIL;

			//4: While we have still some data to read
			while (remaining != 0)
			{
				// Set proper size for our next chunk
				if (remaining >= Mb)
				{
					currChunk = Mb;
				}
				else
				{
					currChunk = remaining;
				}
				char chunk[currChunk];

				// Read data chunk...
				if (AAsset_read(pAsset, chunk, currChunk) > 0) // returns less than 0 on error
				{
					// ...and append it to our vector
					outBuffer->insert(outBuffer->end(), chunk, chunk + currChunk);
					remaining = AAsset_getRemainingLength64(pAsset);
				}
			}
			AAsset_close(pAsset);

			//5: done
			return rcode::OK;



		}

		virtual olc::rcode ExtractFileFromAssets(const std::string& sAssetFilePath, const std::string& sAppStorageFilePath) override
		{
			//Pre Checks
			if (sAssetFilePath.length() < 1 || sAppStorageFilePath.length() < 1)
			{
				return rcode::NO_FILE;
			}

			// Lets get a pointer to the Android Asset Manager
			android_app* MyAndroidApp = platform->ptrPGE->pOsEngine.app;
			AAssetManager* pAssetManager = MyAndroidApp->activity->assetManager;

			AAsset* pAsset = AAssetManager_open(pAssetManager, sAssetFilePath.c_str(), AASSET_MODE_BUFFER);
			if (pAsset == nullptr) return rcode::NO_FILE;

			char cChunk[BUFSIZ];
			int currChunk = 0;
			FILE* out = fopen(sAppStorageFilePath.c_str(), "w");

			if (out == nullptr) return rcode::FAIL;

			while ((currChunk = AAsset_read(pAsset, cChunk, BUFSIZ)) > 0)
			{
				fwrite(cChunk, currChunk, 1, out);
			}

			fclose(out);
			AAsset_close(pAsset);

			return rcode::OK;
		}

		virtual const char* GetInternalAppStorage() override
		{
			android_app* pMyAndroid = platform->ptrPGE->pOsEngine.app;
			ANativeActivity* nativeActivity = pMyAndroid->activity;
			const char* cPath = nativeActivity->internalDataPath;

			return cPath;
		}

		virtual const char* GetExteralAppStorage() override
		{
			android_app* pMyAndroid = platform->ptrPGE->pOsEngine.app;
			ANativeActivity* nativeActivity = pMyAndroid->activity;
			const char* cPath = nativeActivity->internalDataPath;

			return cPath;
		}

		virtual const char* GetPublicAppStorage() override
		{
			android_app* pMyAndroid = platform->ptrPGE->pOsEngine.app;
			ANativeActivity* nativeActivity = pMyAndroid->activity;
			const char* cPath = nativeActivity->obbPath;

			return cPath;
		}

	};
}
#endif

#ifdef __APPLE__
#include "stb_image.h"
namespace olc
{
	class ImageLoader_STB_iOS : public olc::ImageLoader
	{
	public:
		ImageLoader_STB_iOS() : ImageLoader()
		{}

		olc::rcode LoadImageResource(olc::Sprite* spr, const std::string& sImageFile, olc::ResourcePack* pack) override
		{
			UNUSED(pack);
			// clear out existing sprite
			spr->pColData.clear();
			// Open file
			stbi_uc* bytes = nullptr;
			int w = 0, h = 0, cmp = 0;
			if (pack != nullptr)
			{
				/*ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				bytes = stbi_load_from_memory((unsigned char*)rb.vMemory.data(), rb.vMemory.size(), &w, &h, &cmp, 4);*/
			}
			else
			{
				// Check file exists
				/*if (!_gfs::exists(sImageFile)) return olc::rcode::NO_FILE;
				bytes = stbi_load(sImageFile.c_str(), &w, &h, &cmp, 4);*/
			}

			if (!bytes) return olc::rcode::FAIL;
			spr->width = w; spr->height = h;
			spr->pColData.resize(spr->width * spr->height);
			std::memcpy(spr->pColData.data(), bytes, spr->width * spr->height * 4);
			delete[] bytes;
			return olc::rcode::OK;
		}

		olc::rcode GetImageBuffer(olc::Sprite* spr, const std::string& sImageFile, std::vector<char>* buffer) override
		{
			return olc::rcode::OK;
		}

		olc::rcode SaveImageResource(olc::Sprite* spr, const std::string& sImageFile) override
		{
			return olc::rcode::OK;
		}

	};

	class FileHandler_IOS : public olc::FileHandler
	{
	public:
		FileHandler_IOS() : FileHandler()
		{}

		virtual olc::rcode LoadFileFromAssets(const std::string& sFilePath, std::vector<char>* outBuffer) override
		{
			//Pre Checks
			if (sFilePath.length() < 1) return rcode::NO_FILE;

			//5: done
			return rcode::NO_FILE;

		}

		virtual olc::rcode ExtractFileFromAssets(const std::string& sAssetFilePath, const std::string& sAppStorageFilePath) override
		{
			return rcode::FAIL;
		}

		virtual const char* GetInternalAppStorage() override
		{
			const char* cPath = nullptr;

			return cPath;
		}

		virtual const char* GetExteralAppStorage() override
		{
			const char* cPath = nullptr;

			return cPath;
		}

		virtual const char* GetPublicAppStorage() override
		{
			const char* cPath = nullptr;

			return cPath;
		}

	};
}

#endif // __APPLE

#pragma endregion

// O------------------------------------------------------------------------------O
// | ARM SIMD NEON / Intel SIMD:                                         |
// O------------------------------------------------------------------------------O
#pragma region PGE_SIMD

/*
	Default methods should SIMD be not supported or NO_SIMD Defined
*/

namespace olc
{
	class SIMD_NONE : public olc::SIMDDrawRoutines
	{
		virtual olc::rcode Clear_SIMD(Pixel p, olc::Sprite* pDrawTarget) override
		{
			int pixels = platform->ptrPGE->GetDrawTargetWidth() * platform->ptrPGE->GetDrawTargetHeight();
			Pixel* m = platform->ptrPGE->GetDrawTarget()->GetData();
			for (int i = 0; i < pixels; i++) m[i] = p;

			return olc::OK;
		}

		virtual olc::rcode DrawFillLine(int sx, int ex, int ny, Pixel p, olc::Sprite* pDrawTarget) override
		{
			for (int i = sx; i <= ex; i++)
			{
				platform->ptrPGE->Draw({ i, ny }, p);
			}
			return olc::OK;
		}

		virtual olc::rcode FillCircle_SIMD(int32_t x, int32_t y, int32_t radius, Pixel p, olc::Sprite* pDrawTarget) override
		{
			if (radius < 0 || x < -radius || y < -radius || x - pDrawTarget->width > radius || y - pDrawTarget->height > radius)
				return rcode::FAIL;

			if (radius > 0)
			{
				int x0 = 0;
				int y0 = radius;
				int d = 3 - 2 * radius;

				auto drawline = [&](int sx, int ex, int y)
				{
					for (int x = sx; x <= ex; x++)
						platform->ptrPGE->Draw(x, y, p);
				};

				while (y0 >= x0)
				{
					drawline(x - y0, x + y0, y - x0);
					if (x0 > 0)	drawline(x - y0, x + y0, y + x0);

					if (d < 0)
						d += 4 * x0++ + 6;
					else
					{
						if (x0 != y0)
						{
							drawline(x - x0, x + x0, y - y0);
							drawline(x - x0, x + x0, y + y0);
						}
						d += 4 * (x0++ - y0--) + 10;
					}
				}
			}
			else
				platform->ptrPGE->Draw(x, y, p);
			return rcode::OK;

		}

		virtual olc::rcode FillTriangle_SIMD(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p, olc::Sprite* pDrawTarget) override
		{
			auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) platform->ptrPGE->Draw(i, ny, p); };

			int t1x, t2x, y, minx, maxx, t1xp, t2xp;
			bool changed1 = false;
			bool changed2 = false;
			int signx1, signx2, dx1, dy1, dx2, dy2;
			int e1, e2;
			// Sort vertices
			if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
			if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
			if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

			t1x = t2x = x1; y = y1;   // Starting points
			dx1 = (int)(x2 - x1);
			if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y2 - y1);

			dx2 = (int)(x3 - x1);
			if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
			else signx2 = 1;
			dy2 = (int)(y3 - y1);

			if (dy1 > dx1) { std::swap(dx1, dy1); changed1 = true; }
			if (dy2 > dx2) { std::swap(dy2, dx2); changed2 = true; }

			e2 = (int)(dx2 >> 1);
			// Flat top, just process the second half
			if (y1 == y2) goto next;
			e1 = (int)(dx1 >> 1);

			for (int i = 0; i < dx1;) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < dx1) {
					i++;
					e1 += dy1;
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) t1xp = signx1;//t1x += signx1;
						else          goto next1;
					}
					if (changed1) break;
					else t1x += signx1;
				}
				// Move line
			next1:
				// process second line until y value is about to change
				while (1) {
					e2 += dy2;
					while (e2 >= dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;//t2x += signx2;
						else          goto next2;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next2:
				if (minx > t1x) minx = t1x;
				if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x;
				if (maxx < t2x) maxx = t2x;
				drawline(minx, maxx, y);    // Draw line from min to max points found on the y
				// Now increase y
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y == y2) break;
			}
		next:
			// Second half
			dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y3 - y2);
			t1x = x2;

			if (dy1 > dx1) {   // swap values
				std::swap(dy1, dx1);
				changed1 = true;
			}
			else changed1 = false;

			e1 = (int)(dx1 >> 1);

			for (int i = 0; i <= dx1; i++) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < dx1) {
					e1 += dy1;
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) { t1xp = signx1; break; }//t1x += signx1;
						else          goto next3;
					}
					if (changed1) break;
					else   	   	  t1x += signx1;
					if (i < dx1) i++;
				}
			next3:
				// process second line until y value is about to change
				while (t2x != x3) {
					e2 += dy2;
					while (e2 >= dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;
						else          goto next4;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next4:

				if (minx > t1x) minx = t1x;
				if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x;
				if (maxx < t2x) maxx = t2x;
				drawline(minx, maxx, y);
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y > y3) return rcode::OK;
			}
			return rcode::OK;
		}

		virtual olc::rcode FillRect_SIMD(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p, olc::Sprite* pDrawTarget) override
		{
			int32_t x2 = x + w;
			int32_t y2 = y + h;

			if (x < 0) x = 0;
			if (x >= (int32_t)platform->ptrPGE->GetDrawTargetWidth()) x = (int32_t)platform->ptrPGE->GetDrawTargetWidth();
			if (y < 0) y = 0;
			if (y >= (int32_t)platform->ptrPGE->GetDrawTargetHeight()) y = (int32_t)platform->ptrPGE->GetDrawTargetHeight();

			if (x2 < 0) x2 = 0;
			if (x2 >= (int32_t)platform->ptrPGE->GetDrawTargetWidth()) x2 = (int32_t)platform->ptrPGE->GetDrawTargetWidth();
			if (y2 < 0) y2 = 0;
			if (y2 >= (int32_t)platform->ptrPGE->GetDrawTargetHeight()) y2 = (int32_t)platform->ptrPGE->GetDrawTargetHeight();

			for (int i = x; i < x2; i++)
				for (int j = y; j < y2; j++)
					platform->ptrPGE->Draw(i, j, p);

			return rcode::OK;
		}

		virtual olc::rcode DrawSprite_SIMD(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip, olc::Sprite* pDrawTarget) override
		{
			if (sprite == nullptr)
				return rcode::FAIL;

			int32_t fxs = 0, fxm = 1, fx = 0;
			int32_t fys = 0, fym = 1, fy = 0;
			if (flip & olc::Sprite::Flip::HORIZ) { fxs = sprite->width - 1; fxm = -1; }
			if (flip & olc::Sprite::Flip::VERT) { fys = sprite->height - 1; fym = -1; }

			if (scale > 1)
			{
				fx = fxs;
				for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
				{
					fy = fys;
					for (int32_t j = 0; j < sprite->height; j++, fy += fym)
						for (uint32_t is = 0; is < scale; is++)
							for (uint32_t js = 0; js < scale; js++)
								platform->ptrPGE->Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx, fy));
				}
			}
			else
			{
				fx = fxs;
				for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
				{
					fy = fys;
					for (int32_t j = 0; j < sprite->height; j++, fy += fym)
						platform->ptrPGE->Draw(x + i, y + j, sprite->GetPixel(fx, fy));
				}
			}
			return rcode::OK;
		}

		virtual olc::rcode DrawPartialSprite_SIMD(const olc::vi2d& vPos, olc::Sprite* pdrawTarget, const olc::vi2d& vStartPos, const olc::vi2d& vSize, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget) override
		{
			if (pdrawTarget == nullptr) return rcode::FAIL;

			int32_t fxs = 0, fxm = 1, fx = 0;
			int32_t fys = 0, fym = 1, fy = 0;
			if (flip & olc::Sprite::Flip::HORIZ) { fxs = vSize.x - 1; fxm = -1; }
			if (flip & olc::Sprite::Flip::VERT) { fys = vSize.y - 1; fym = -1; }

			if (scale > 1)
			{
				fx = fxs;
				for (int32_t i = 0; i < vSize.x; i++, fx += fxm)
				{
					fy = fys;
					for (int32_t j = 0; j < vSize.y; j++, fy += fym)
						for (uint32_t is = 0; is < scale; is++)
							for (uint32_t js = 0; js < scale; js++)
								platform->ptrPGE->Draw(vPos.x + (i * scale) + is, vPos.y + (j * scale) + js, pdrawTarget->GetPixel(fx + vStartPos.x, fy + vStartPos.y));
				}
			}
			else
			{
				fx = fxs;
				for (int32_t i = 0; i < vSize.x; i++, fx += fxm)
				{
					fy = fys;
					for (int32_t j = 0; j < vSize.y; j++, fy += fym)
						platform->ptrPGE->Draw(vPos.x + i, vPos.y + j, pdrawTarget->GetPixel(fx + vStartPos.x, fy + vStartPos.y));
				}
			}
			return rcode::OK;
		}

		virtual olc::rcode DrawMergeSprite_SIMD(int32_t vPosx, int32_t vPosy, Sprite* pFromSprite, int32_t vToSpritePosx, int32_t vToSpritePosy, Sprite* pToSprite, Pixel blendPixel, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget) override
		{
			if (pFromSprite == nullptr) return rcode::FAIL;

			if (pToSprite == nullptr) return rcode::FAIL;

			olc::Sprite* pMergeSprite = nullptr;
			olc::vi2d vToSpritePos = { vToSpritePosx, vToSpritePosy };

			pMergeSprite = pFromSprite->DuplicateMerge(vToSpritePos, pToSprite, blendPixel);

			if (pMergeSprite != nullptr)
			{
				platform->ptrPGE->DrawSprite(vPosx, vPosy, pMergeSprite, scale, flip);

				delete pMergeSprite;
			}
			return rcode::OK;
		}

		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite* pSource) override
		{

			// This is the fastest way of duplicating, I say this is not required, keep for testing 
			olc::Sprite* spr = new olc::Sprite(pSource->width, pSource->height);
			std::memcpy(spr->GetData(), pSource->GetData(), pSource->width * pSource->height * sizeof(olc::Pixel));
			spr->modeSample = pSource->modeSample;
			return spr;

		}

		virtual olc::Sprite* Duplicate_SIMD(const olc::vi2d& vPos, const olc::vi2d& vSize, olc::Sprite* pSource) override
		{
			olc::Sprite* spr = new olc::Sprite(vSize.x, vSize.y);
			for (int y = 0; y < vSize.y; y++)
				for (int x = 0; x < vSize.x; x++)
					spr->SetPixel(x, y, pSource->GetPixel(vPos.x + x, vPos.y + y));
			return spr;

		}

		/*-------------- New Methods John Galvin --------------*/

		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite::Flip flip, olc::Sprite* pSource) override
		{
			olc::Sprite* spr = new olc::Sprite(pSource->width, pSource->height);

			int32_t fxs = 0, fxm = 1, fx = 0;
			int32_t fys = 0, fym = 1, fy = 0;
			if (flip & olc::Sprite::Flip::HORIZ) { fxs = pSource->width - 1; fxm = -1; }
			if (flip & olc::Sprite::Flip::VERT) { fys = pSource->height - 1; fym = -1; }

			fx = fxs;
			for (int32_t i = 0; i < pSource->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < pSource->height; j++, fy += fym)
					spr->SetPixel(i, j, pSource->GetPixel(fx, fy));

			}

			return spr;

		}

		virtual olc::Sprite* Duplicate_SIMD(uint32_t scale, olc::Sprite* pSource) override
		{
			scale = (scale < 1) ? 1 : scale;
			olc::Sprite* spr = new olc::Sprite(pSource->width * scale, pSource->height * scale);

			int32_t fxs = 0, fxm = 1, fx = 0;
			int32_t fys = 0, fym = 1, fy = 0;

			fx = fxs;
			for (int32_t i = 0; i < pSource->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < pSource->height; j++, fy += fym)
					for (uint32_t is = 0; is < scale; is++)
						for (uint32_t js = 0; js < scale; js++)
							spr->SetPixel((i * scale) + is, (j * scale) + js, pSource->GetPixel(fx, fy));
			}


			return spr;

		}

		virtual olc::Sprite* DuplicateMerge_SIMD(const olc::vi2d& vTargetPos, olc::Sprite* pTargetSprite, olc::Pixel p, olc::Sprite* pSource) override
		{
			if (pTargetSprite == nullptr) return nullptr;

			olc::Sprite* pMergeSprite = pTargetSprite->Duplicate();
			olc::Pixel writePixel = p;

			int32_t fxs = 0, fxm = 1, fx = 0;
			int32_t fys = 0, fym = 1, fy = 0;


			fx = fxs;
			for (int32_t i = 0; i < pSource->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < pSource->height; j++, fy += fym)
				{
					writePixel = pSource->GetPixel(fx, fy);
					if (writePixel != p)
					{
						pMergeSprite->SetPixel(fx + vTargetPos.x, fy + vTargetPos.y, writePixel);

					}

				}

			}

			return pMergeSprite;

		}

		/*-------------- END New Methods John Galvin --------------*/


		virtual olc::Sprite* DrawToTarget(const olc::vi2d& vPos, olc::Sprite* pdrawTarget, std::vector<int> vecPositions, olc::Sprite* pSource)
		{

			return nullptr;

		}

	};
}



#if defined(__ANDROID__)

#if defined(__arm__ ) || defined(__aarch64__)
#include "sse2neon.h"

namespace olc
{
	class SIMD_NEON_ARM : public olc::SIMDDrawRoutines
	{
		virtual olc::rcode Clear_SIMD(Pixel p, olc::Sprite* pDrawTarget) override
		{
			if (pDrawTarget == nullptr) return rcode::FAIL;

			int VecEndIndex = (int)pDrawTarget->pColData.size();

			int nVecA = 0;

			int nReplacePixel = (int)p.n; // Get the int value of the pixel

			__m128i _replacepixel; // instance a 128bit register which can hold 4 uint32_t slots 

			//_replacepixel = | uint32_t nReplacePixel | uint32_t nReplacePixel | uint32_t nReplacePixel | uint32_t nReplacePixel |... 4 slots
			_replacepixel = _mm_set1_epi32(nReplacePixel);

			int i = 0;
			int j = 0;
			for (i = 0; i < VecEndIndex; i += 4, nVecA += 4)
			{
				j = i;
				_mm_store1_ps((float*)pDrawTarget->pColData.data() + nVecA, _replacepixel);
			}

			// Clean up left over pixels
			for (; j < VecEndIndex; j++)
			{
				pDrawTarget->pColData[j] = p;
			}

			return olc::OK;
		}

		virtual olc::rcode DrawFillLine(int sx, int ex, int ny, Pixel p, olc::Sprite* pDrawTarget) override
		{
			if (pDrawTarget == nullptr) return rcode::FAIL;
			// Some optimisation
			if (ny < 0 || ny > pDrawTarget->height) return rcode::OK;	// The line is above/below the viewable screen, no use in drawing it
			if (ex < 0 || sx > pDrawTarget->width) return rcode::OK;	// The line is outside the left/right side of the view screen, no use in drawing it

			// Crop line to fit within draw target
			ny = (ny < 0) ? 0 : ny;
			sx = (sx < 0) ? 0 : sx;
			ex = (ex > pDrawTarget->width) ? ex = pDrawTarget->width : ex;

			// Lets get any left over pixels to be processed
			int nOffSet = ex % 16;
			int nTempVecEnd = ex - nOffSet;
			int setPixel = (int)p.n;	// Set the pixel colour

			__m128i _setpixel;
			_setpixel = _mm_set1_epi32(setPixel);

			float* nVecA = (float*)pDrawTarget->pColData.data(); // Get the start pointer of the vector

			nVecA += (ny * pDrawTarget->width) + sx; // Move the start pointer to the location where we want to start drawing

			int i = sx;
			int j = sx;
			for (i = sx; i < nTempVecEnd; i += 4, nVecA += 4)
			{
				j = i;
				_mm_store1_ps(nVecA, _setpixel);

			}


			// Clean up left over pixels
			int pos = 0;
			size_t vecSize = pDrawTarget->pColData.size();

			for (; j <= ex; j++)
			{
				pos = (ny * pDrawTarget->width) + j;
				if (pos < vecSize) pDrawTarget->pColData[pos] = p; // fixed a small
			}


			return olc::OK;
		}

		virtual olc::rcode FillCircle_SIMD(int32_t x, int32_t y, int32_t radius, Pixel p, olc::Sprite* pDrawTarget) override
		{

			if (radius < 0 || x < -radius || y < -radius || x - pDrawTarget->width > radius || y - pDrawTarget->height > radius)
				return rcode::FAIL;

			if (radius > 0)
			{
				int x0 = 0;
				int y0 = radius;
				int d = 3 - 2 * radius;

				while (y0 >= x0)
				{
					DrawFillLine(x - y0, x + y0, y - x0, p, pDrawTarget);
					if (x0 > 0)	DrawFillLine(x - y0, x + y0, y + x0, p, pDrawTarget);

					if (d < 0)
						d += 4 * x0++ + 6;
					else
					{
						if (x0 != y0)
						{
							DrawFillLine(x - x0, x + x0, y - y0, p, pDrawTarget);
							DrawFillLine(x - x0, x + x0, y + y0, p, pDrawTarget);
						}
						d += 4 * (x0++ - y0--) + 10;
					}
				}
			}
			else
				platform->ptrPGE->Draw(x, y, p);



			return rcode::OK;

		}

		virtual olc::rcode FillTriangle_SIMD(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p, olc::Sprite* pDrawTarget) override
		{
			int t1x, t2x, y, minx, maxx, t1xp, t2xp;
			bool changed1 = false;
			bool changed2 = false;
			int signx1, signx2, dx1, dy1, dx2, dy2;
			int e1, e2;
			// Sort vertices
			if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
			if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
			if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

			t1x = t2x = x1; y = y1;   // Starting points
			dx1 = (int)(x2 - x1);
			if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y2 - y1);

			dx2 = (int)(x3 - x1);
			if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
			else signx2 = 1;
			dy2 = (int)(y3 - y1);

			if (dy1 > dx1) { std::swap(dx1, dy1); changed1 = true; }
			if (dy2 > dx2) { std::swap(dy2, dx2); changed2 = true; }

			e2 = (int)(dx2 >> 1);
			// Flat top, just process the second half
			if (y1 == y2) goto next;
			e1 = (int)(dx1 >> 1);

			/// End Setup

			for (int i = 0; i < dx1;) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < dx1) {
					i++;
					e1 += dy1;
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) t1xp = signx1;//t1x += signx1;
						else          goto next1;
					}
					if (changed1) break;
					else t1x += signx1;
				}
				// Move line
			next1:
				// process second line until y value is about to change
				while (1) {
					e2 += dy2;
					while (e2 >= dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;//t2x += signx2;
						else          goto next2;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next2:
				if (minx > t1x) minx = t1x;
				if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x;
				if (maxx < t2x) maxx = t2x;
				simddrawer->DrawFillLine(minx, maxx, y, p, pDrawTarget); // Draw line from min to max points found on the y using SIMD, // John Galvin added missing 'p'
				// Now increase y
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y == y2) break;
			}

		next:
			// Second half
			dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y3 - y2);
			t1x = x2;

			if (dy1 > dx1) {   // swap values
				std::swap(dy1, dx1);
				changed1 = true;
			}
			else changed1 = false;

			e1 = (int)(dx1 >> 1);

			for (int i = 0; i <= dx1; i++) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < dx1) {
					e1 += dy1;
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) { t1xp = signx1; break; }//t1x += signx1;
						else          goto next3;
					}
					if (changed1) break;
					else   	   	  t1x += signx1;
					if (i < dx1) i++;
				}
			next3:
				// process second line until y value is about to change
				while (t2x != x3) {
					e2 += dy2;
					while (e2 >= dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;
						else          goto next4;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next4:

				if (minx > t1x) minx = t1x;
				if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x;
				if (maxx < t2x) maxx = t2x;
				simddrawer->DrawFillLine(minx, maxx, y, p, pDrawTarget); // Draw line from min to max points found on the y using SIMD. // John Galvin added missing 'p'
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y > y3) return rcode::OK;
			}

			return rcode::OK;
		}

		virtual olc::rcode FillRect_SIMD(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p, olc::Sprite* pDrawTarget) override
		{
			int32_t x2 = x + w;
			int32_t y2 = y + h;

			if (x < 0) x = 0;
			if (x >= (int32_t)pDrawTarget->width) x = (int32_t)pDrawTarget->width;
			if (y < 0) y = 0;
			if (y >= (int32_t)pDrawTarget->height) y = (int32_t)pDrawTarget->height;

			if (x2 < 0) x2 = 0;
			if (x2 >= (int32_t)pDrawTarget->width) x2 = (int32_t)pDrawTarget->width;
			if (y2 < 0) y2 = 0;
			if (y2 >= (int32_t)pDrawTarget->height) y2 = (int32_t)pDrawTarget->height;

			for (int j = y; j < y2; j++)
			{
				simddrawer->DrawFillLine(x, x2, j, p, pDrawTarget);
			}

			return rcode::OK;
		}

		virtual olc::rcode DrawSprite_SIMD(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip, olc::Sprite* pDrawTarget) override
		{
			if (sprite == nullptr) return rcode::FAIL;
			olc::vi2d vPos = { x, y };

			// Lets check if the sprite all ready exist?
			olc::vi2d vStartPos = { 0,0 };
			olc::vi2d vScaleSize = { sprite->width * (int)scale, sprite->height * (int)scale };
			olc::Decal* dec = (olc::Decal*)sprite->GetStoredSubDecal(vStartPos, vScaleSize, scale, (olc::Sprite::Flip)flip, pDrawTarget);
			if (dec == nullptr)
			{
				//1: Lets flip it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprFlipped = sprite->Duplicate((olc::Sprite::Flip)flip);

				//2: Lets scale it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprScaled = sprFlipped->Duplicate(scale);

				//3: Store the SubSprite, a Decal will also be created 
				if (!sprite->StoreSubSprite(sprScaled, vStartPos, scale, (olc::Sprite::Flip)flip, pDrawTarget))
				{
					// OK the vector is full or sub sprites disabled
					// We Cannot Store the sub sprite, lets draw it
					DuplicateMerge_SIMD(vStartPos, pDrawTarget, olc::BLANK, sprScaled);
					delete sprScaled;
					delete sprFlipped;
					return rcode::OK;
				}
				else
				{
					//4: Get the newly created Decal
					dec = (olc::Decal*)sprite->GetStoredSubDecal(vStartPos, vScaleSize, scale, (olc::Sprite::Flip)flip, pDrawTarget);

					//5: Clean up
					delete sprFlipped;

				}

			}

			renderer->ptrPGE->DrawDecal(vPos, dec);
			return rcode::OK;
		}

		virtual olc::rcode DrawPartialSprite_SIMD(const olc::vi2d& vPos, olc::Sprite* pSource, const olc::vi2d& vStartPos, const olc::vi2d& vSize, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget) override
		{

			// Lets check if the sprite all ready exist?
			scale = (scale < 1) ? 1 : scale;

			olc::vi2d vScaleSize = { vSize.x * (int)scale, vSize.y * (int)scale };
			olc::Decal* dec = (olc::Decal*)pSource->GetStoredSubDecal(vStartPos, vScaleSize, scale, flip, pDrawTarget);
			if (dec == nullptr)
			{

				//1: lets get the partial;
				olc::Sprite* sprPartial = pSource->Duplicate(vStartPos, vSize);

				//2: Lets flip it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprFlipped = sprPartial->Duplicate((olc::Sprite::Flip)flip);

				//3: Lets scale it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprScaled = sprFlipped->Duplicate(scale);


				//4: Store the SubSprite, a Decal will also be created 
				if (!pSource->StoreSubSprite(sprScaled, vStartPos, scale, flip))
				{
					// OK the vector is full or sub sprites disabled
					// We Cannot Store the sub sprite, lets draw it
					DuplicateMerge_SIMD(vStartPos, pDrawTarget, olc::BLANK, sprScaled);
					delete sprScaled;
					delete sprFlipped;
					return rcode::OK;
				}
				else
				{
					//5: Get the Decal
					dec = (olc::Decal*)pSource->GetStoredSubDecal(vStartPos, vScaleSize, scale, flip, pDrawTarget);

					//6: Clean up
					delete sprPartial;
					delete sprFlipped;

				}

			}

			renderer->ptrPGE->DrawDecal(vPos, dec);
			return rcode::OK;
		}

		virtual olc::rcode DrawMergeSprite_SIMD(int32_t vPosx, int32_t vPosy, Sprite* pFromSprite, int32_t vToSpritePosx, int32_t vToSpritePosy, Sprite* pToSprite, Pixel blendPixel, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget) override
		{

			olc::vi2d vPos = { vPosx , vPosy };
			olc::vi2d vSize = { pToSprite->width * (int32_t)scale ,  pToSprite->height * (int32_t)scale };

			olc::vi2d vToSpritePos = { vToSpritePosx ,vToSpritePosy };

			olc::Decal* dec = (olc::Decal*)pFromSprite->GetStoredSubDecal(vToSpritePos, vSize, scale, flip, pToSprite);
			if (dec == nullptr)
			{
				olc::Sprite* pMergeSprite = nullptr;
				olc::Sprite* pMergeScaleSprite = nullptr;
				olc::Sprite* pMergeFilpSprite = nullptr;

				pMergeSprite = pFromSprite->DuplicateMerge(vToSpritePos, pToSprite, blendPixel);
				pMergeScaleSprite = pMergeSprite->Duplicate(scale);
				pMergeFilpSprite = pMergeScaleSprite->Duplicate((olc::Sprite::Flip)flip);

				//4: Store the SubSprite, a Decal will also be created 
				if (!pFromSprite->StoreSubSprite(pMergeFilpSprite, vToSpritePos, scale, flip, pToSprite))
				{
					// OK the vector is full or sub sprites disabled
					// We Cannot Store the sub sprite, lets draw it
					DuplicateMerge_SIMD(vToSpritePos, pDrawTarget, olc::BLANK, pMergeFilpSprite);
					delete pMergeSprite;
					delete pMergeScaleSprite;
					delete pMergeFilpSprite;
					return rcode::OK;
				}
				else
				{
					//5: Get the Decal
					dec = (olc::Decal*)pFromSprite->GetStoredSubDecal(vToSpritePos, vSize, scale, flip, pToSprite);

					//6: Clean up
					delete pMergeSprite;
					delete pMergeScaleSprite;
					renderer->ptrPGE->DrawDecal(vPos, dec);
				}

			}

			renderer->ptrPGE->DrawDecal(vPos, dec);
			return rcode::OK;
		}

		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite* pSource) override
		{
			// This is the fastest way of duplicating, I say this is not required, keep for testing 
			olc::Sprite* spr = new olc::Sprite(pSource->width, pSource->height);
			std::memcpy(spr->GetData(), pSource->GetData(), pSource->width * pSource->height * sizeof(olc::Pixel));
			spr->modeSample = pSource->modeSample;
			return spr;

		}

		virtual olc::Sprite* Duplicate_SIMD(const olc::vi2d& vPos, const olc::vi2d& vSize, olc::Sprite* pSource) override
		{

			// Some Maths, to ensure the partial sprite is created correctly
			int newSizeX = vSize.x;
			int newSizeY = vSize.y;

			int maxX = vPos.x + vSize.x;
			int maxY = vPos.y + vSize.y;

			if (maxX > pSource->width) newSizeX = pSource->width - vPos.x;
			if (maxY > pSource->height) newSizeY = pSource->height - vPos.y;


			olc::Sprite* spr = new olc::Sprite(newSizeX, newSizeX);
			Clear_SIMD(olc::BLANK, spr);
			int sx = 0;
			int ex = newSizeX;
			int nOffSet = ex % 4;

			if (nOffSet > 0)
			{
				// We need to work out what is the next muliple of 4 pixels
				nOffSet = (ex / 4) + 1;
				nOffSet = (nOffSet * 4);
				nOffSet = nOffSet - ex;

			}
			bool bUseHighSpeed = (nOffSet == 0) ? true : false;

			int nVecTarget = 0;
			float* pTargetVector = (float*)spr->pColData.data();
			size_t nVecTLen = spr->pColData.size();

			size_t nVecRead = (vPos.y * pSource->width) + vPos.x; // Start position of read vector
			size_t nVecRLen = pSource->pColData.size();

			__m128 _sx, _ex, _result, _vecRead;

			_sx = _mm_set1_ps(sx);
			_ex = _mm_set1_ps(ex);
			_result = _mm_set1_ps(0xFF); // 0xFF = -1 -> True, 0x00 = 0 -> False;

			// NOTE: We write out the full for-->loop for both High & Low speed
			// If we put the condional statement between the for Y for loop we get a 'branch' in our assembly and lose any gains in proformance
			if (bUseHighSpeed)
			{
				// High speed (up too 2times faster as we have no offset to manage)
				for (int y = 0; y < newSizeY; y++)
				{
					if (nVecRead > nVecRLen)
					{
						break; // Break if we reached the end of the read vector
					}
					if (nVecTarget > nVecTLen) {
						break; // break if we reached the end of the target vector
					}

					// Get the next position of the read vector
					// Take note of (y + vPos.y), we need the position of y + the next row of y for the read vector (nVecRead)
					nVecRead = ((y + vPos.y) * pSource->width) + vPos.x;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						// Load in the read vector
						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_mm_storeu_ps(pTargetVector, _vecRead);

					}


				}

			}
			else
			{
				// We have an offset to manage
				for (int y = 0; y < newSizeY; y++)
				{
					if (nVecRead > nVecRLen)
					{
						break; // Break if we reached the end of the read vector
					}
					if (nVecTarget > nVecTLen) {
						break; // break if we reached the end of the target vector
					}

					// Get the next position of the read vector
					// Take note of (y + vPos.y), we need the position of y + the next row of y for the read vector (nVecRead)
					nVecRead = ((y + vPos.y) * pSource->width) + vPos.x;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						// Load in the read vector
						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));

						// We compare if the all the pixels ly within sx->ex, and pixel greater then ex are not process
						_sx = _mm_set_ps(x + 3, x + 2, x + 1, x);

						// Take note there is 'no less than or equals', but if you just reverse the operands and use 'greater than' you get the excat same affect
						_result = _mm_cmpgt_ps(_ex, _sx);

						// Store only the pixels that are between sx-->ex
						_mm_maskmoveu_si128(_vecRead, _result, (char*)pTargetVector);

					}

					// Shift the ptr for pTargetVector by the offset
					// This ensures the ptr is always in the correct position for the next row of y
					// Debug it to understand better
					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}

			}

			//Clean up any left over pixels
			for (size_t x = nVecTarget; x < (size_t)nVecTLen; x++, nVecRead++)
			{
				if (nVecRead > nVecRLen)
				{
					break; // Break if we reached the end of the read vector
				}
				if (nVecTarget > nVecTLen) {
					break; // break if we reached the end of the target vector
				}

				spr->pColData[x] = pSource->pColData[nVecRead];


			}

			return spr;

		}

		/*-------------- New Methods John Galvin --------------*/

		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite::Flip flip, olc::Sprite* pSource) override
		{
			if (pSource == nullptr) return nullptr;

			olc::Sprite* spr = nullptr;

			// Some optimisations, if we are not flipping just return a duplicate
			if ((uint8_t)flip < 1)
			{
				spr = pSource->Duplicate();
				return spr;
			}

			olc::vi2d vStartPos = { 0, 0 };
			olc::vi2d vSize = { pSource->width, pSource->height };

			spr = new olc::Sprite(pSource->width, pSource->height);

			int sx = 0;
			int ex = pSource->width;
			int nOffSet = ex % 4;

			if (nOffSet > 0)
			{
				// we need to work out what is the next muliple of 8 pixels
				// Example: vSize.x = 270 
				nOffSet = (ex / 4) + 1; // 270 / 4 = 67. + 1 = 68
				nOffSet = (nOffSet * 4); // 68 * 4 = 272
				nOffSet = nOffSet - ex; // therefore the offset is 2

			}

			int nVecTarget = 0;
			float* pTargetVector = (float*)spr->pColData.data();
			size_t nVecTLen = spr->pColData.size();

			size_t nVecRead = 0; // Start position of read vector
			size_t nVecRLen = pSource->pColData.size();

			__m128i _sx, _ex, _result, _vecRead;

			_sx = _mm_set1_epi32(sx);
			_ex = _mm_set1_epi32(ex);
			_result = _mm_set1_epi32(0xFF); // 0xFF = -1 -> True, 0x00 = 0 -> False;

			if (flip & olc::Sprite::Flip::HORIZ)
			{
				nVecRead = nVecRLen;
				for (int y = 1; y <= pSource->height; y++)
				{
					if (y == 0) y = 1;
					nVecRead = (y * pSource->width) - 4;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += -4, nVecTarget += 4)
					{

						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_mm_storer_ps(pTargetVector, _vecRead);

					}

					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}


			}

			if (flip & olc::Sprite::Flip::VERT)
			{
				nVecRead = nVecRLen;
				for (int y = pSource->height; y > 0; y--)
				{
					if (nVecTarget + 4 > nVecTLen) break;
					nVecRead = (y * pSource->width) + 0;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_mm_storeu_ps(pTargetVector, _vecRead);

					}
					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}


			}

			// There MAY be a few left over sprites we just clear them
			// This is a little cheat, you could write some very complex code to ensure all left pixels are matched, but this will be very slow. 
			// Therefore we just hide (Aphla) them, at most there could be 1 line of pixels at the top/buttom/top, in most cases it will be a few pixels
			// The end user cannot see that this 1 line of pixels is missing, it will be so small
			for (size_t x = nVecTarget; x < (size_t)nVecTLen; x++)
			{
				spr->pColData[x] = olc::BLANK;

			}

			return spr;

		}

		virtual olc::Sprite* Duplicate_SIMD(uint32_t scale, olc::Sprite* pSource) override
		{
			if (pSource == nullptr) return nullptr;

			scale = (scale < 1) ? 1 : scale;
			if ((uint32_t)scale == 1) return pSource->Duplicate();
			olc::Sprite* spr = new olc::Sprite(pSource->width * scale, pSource->height * scale);

			int nVecTarget = 0;										// Target vector position
			float* pTargetVector = (float*)spr->pColData.data();	// Target vector pointer
			size_t nVecTLen = spr->pColData.size();					// Target vector size

			uint32_t nVecRead = 0;									// Start position of read vector
			size_t nVecRLen = pSource->pColData.size();				// Read vector size

			int nReadCount = std::max(int(4 / scale), 1);			// Number of pixels to be read in

			int nOffSet = 4 % scale;								// Offset for left over pixels
			uint32_t nScaleCount = 0;								// Scale count used when the scale is greater than the register
			if (scale > 4)
			{
				nOffSet = 0;
				nScaleCount = scale - 4;
			}

			int nsuffle[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Suffle Pixels
			int nPos = 0;
			if (scale > 1)
			{
				// If Scale 2 the it is double 1 pixel becomes 2 pixels
				// {0, 1, 2, 3, 4, 5, 6 >> 16} --> {0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6, 7 etc >> 16}; 
				// There are fancy ways to do this, but you can debug the below to see how it works
				int i = 0;
				while (nPos < 16)
				{
					for (int j = 0; j < scale; j++)
					{
						if (nPos > 15) break;
						for (int k = 0; k < 4; k++)
						{
							if (nPos > 15) break;
							nsuffle[nPos] = i + k;
							nPos++;
						}
					}
					i += 4;
				}

			}

			__m128i _shufflePixels;
			__m128 _result, _vecRead;

			// Lets do the Suffle Suffle baby
			_shufflePixels = _mm_set_epi8(nsuffle[15], nsuffle[14], nsuffle[13], nsuffle[12],
				nsuffle[11], nsuffle[10], nsuffle[9], nsuffle[8],
				nsuffle[7], nsuffle[6], nsuffle[5], nsuffle[4],
				nsuffle[3], nsuffle[2], nsuffle[1], nsuffle[0]
			);

			int y = 0; int x = 0; int yS = 0;
			uint32_t nTottle = scale;

			for (y = 0; y < pSource->height; y++, yS++)
			{
				// Added extra Y Lines of x values
				nTottle++;
				if (nTottle < scale) y--;
				if (nTottle >= scale) nTottle = 0;

				nVecRead = (y * pSource->width) + 0;
				nVecTarget = (yS * spr->width) + 0;
				pTargetVector += nVecTarget;
				for (x = 0; x < pSource->width; x += nReadCount, nVecRead += nReadCount, pTargetVector += 4, nVecTarget += 4)
				{
					_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
					_result = _mm_shuffle_epi8(_vecRead, _shufflePixels);
					_mm_storeu_ps(pTargetVector, _result);

					// If out scale is greater than 4 times, i.e.10 then we need repeat the pixels
					if (nScaleCount > 0)
					{
						for (int i = 1; i < (int)nScaleCount; i += 4)
						{
							pTargetVector += 4;
							nVecTarget += 4;
							nOffSet = (i * 4) - (int)nScaleCount;
							_mm_storeu_ps(pTargetVector, _result);

						}
					}

					// Move back the pointer and vectors to get the offset bytes
					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}

				pTargetVector -= nVecTarget;

			}

			// There can be some pixels on the target sprite left over
			//TODO: Still not happy with this maths
			int nYPos = ((y - scale) * pSource->width);
			int nYTarPos = (yS * (pSource->width * scale));

			// Check is there are left over pixels
			if (nYTarPos < nVecTLen)
			{
				// If so process them
				for (int i = nYPos; i < nVecRLen; i++)
				{
					for (size_t j = 0; j < scale; j++, nYTarPos++)
					{
						if (nYTarPos >= nVecTLen) break;
						spr->pColData[nYTarPos] = pSource->pColData[i];
					}
				}
			}


			return spr;

		}

		virtual olc::Sprite* DuplicateMerge_SIMD(const olc::vi2d& vTargetPos, olc::Sprite* pTargetSprite, olc::Pixel p, olc::Sprite* pSource) override
		{
			if (pTargetSprite == nullptr) return nullptr;

			/*---- Non-SIMD Vs SIMD*/


			/*
				There is no real performance gain using either of the executions (Non-SIMD, SIMD)
				Always remember it is near impossible to beat the complier. You might ask then why write it in SIMD at all?
				Well, when you are developing low level code, it is difficult to jump between languages.
				Most developers prefer to stay with one language within a method.
				As these methods are SIMD executions, then write it all in SIMD, therefore there is no surprises later when another developer
				needs to debug.
				They are expecting SIMD, then they get SIMD
				Finally the SIMD code below should be a tiny bit faster, but it would be impossible to measure
			*/
			/*
			Non SIMD Code :

			// Ok we need to ensure the sprite can fit on the layer (pdrawTarget)
			// Work out if the sprite is out of bounds and crop the sprite to fit into the bounds

			int nFullWidth = vPos.x + pSource->width;
			int nFullHeight = vPos.y + pSource->height;
			int nWidth = pSource->width; //std::min(nFullWidth, pdrawTarget->width);
			int nHeight = pSource->height; // std::min(nFullHeight, pdrawTarget->height);

			if (nFullWidth >= pdrawTarget->width)
			{
				// Get the new width for off layer sprite
				nWidth = nFullWidth - pdrawTarget->width;
				nWidth = pSource->width - nWidth;
			}

			if (nFullHeight >= pdrawTarget->height)
			{
				// Get the new height for off layer sprite
				nHeight = nFullHeight - pdrawTarget->height;
				nHeight = pSource->height - nHeight;
			}

			// Get the new Start Position for off layer sprite
			int nXStart = (vPos.x < 0) ? vPos.x * -1 : 0;
			int nYStart = (vPos.y < 0) ? vPos.y * -1 : 0;

			// Get the new vPosition for off layer sprite
			int nXPos = (vPos.x < 0) ? 0 : vPos.x;
			int nYPos = (vPos.y < 0) ? 0 : vPos.y;

			std::vector<int> vecPositions = { vPos.y, vPos.x, nHeight, nWidth, nYPos, nXPos, nYStart, nXStart };
			*/


			/*
				Ok we need to ensure the sprite can fit the sprite on the layer (pdrawTarget)
				Work out if the sprite is out of bounds and crop the sprite to fit into the bounds

				Vector of position: Order is important, SIMD will read the vector in backwards, (right to left) <--- */

				/*---- END Non-SIMD Vs SIMD ---*/

			std::vector<int> vecPositions = { vTargetPos.y, vTargetPos.x, pSource->height, pSource->width, vTargetPos.y, vTargetPos.x, 0, 0 };
			int* pPositions = vecPositions.data();

			__m128i _reg1, _reg2, _reg3, _reg4, _reg5, _compare;

			_reg1 = _mm_set_epi32(pSource->width, pSource->height, 0, 0);			// Holds width and height
			_reg2 = _mm_set_epi32(vTargetPos.x, vTargetPos.y, 0, 0);				// Holds vPos.x and vPos.y
			_reg3 = _mm_add_epi32(_reg1, _reg2);									// nFullWidth = vPos.x + width, nFullHeight = vPos.y + height;
			_reg4 = _mm_set_epi32(pTargetSprite->width, pTargetSprite->height, 0, 0);	// Holds pdrawTarget->width, pdrawTarget->height
			_compare = _mm_cmpgt_epi32(_reg3, _reg4);								// if (nFullWidth >= pdrawTarget->width) (true false)
			_reg5 = _mm_sub_epi32(_reg3, _reg4);									// nWidth = nFullWidth - pdrawTarget->width, nheight = nheight - pdrawTarget->height,
			_reg5 = _mm_sub_epi32(_reg1, _reg5);									// nWidth = width - nWidth, nHeight = height - nHeight;
			_mm_maskmoveu_si128(_reg5, _compare, (char*)pPositions);				// We only store the computed values of reg5, if _comp is set. i.e. nFullWidth is greater than pdrawTarget->width 

			// Now lets get the nXStart, nYStart 
																					// Note the vector is read in backwards, (right to left) <---    <---    <--- 					
			pPositions += 4;														// Move our pionter down by 4 so we are pointing to {... vPos.y, vPos.x, 0, 0}
			_reg1 = _mm_set1_epi32(0);												// Clear reg1 to 0, (vPos.x < 0) ? vPos.x * -1 : 0 <- this zero
			_compare = _mm_cmpgt_epi32(_reg1, _reg2);								//(vPos.x < 0)?,  (vPos.y < 0)?
			_reg5 = _mm_abs_epi32(_reg2);											// vPos.x * -1, vPos.y * -1. Abs will resturn positive absolute numbers, we do not need to muliply
			_mm_maskmoveu_si128(_reg5, _compare, (char*)pPositions);				// We only change the values of nXStart & nYStart if _comp is set (nXStart = (vPos.x < 0) ? vPos.x * -1)

			// Now lets get the nXPos, nYPso

			_reg2 = _mm_set_epi32(0, 0, vTargetPos.x, vTargetPos.y);				// Tottle the reg2 so that 0's will cause nXStart & nYStart results not to be affected
			_compare = _mm_cmpgt_epi32(_reg1, _reg2);								// (vPos.x < 0)?,  (vPos.y < 0)? . We reuse _reg1 as it is already set to 0's
			_mm_maskmoveu_si128(_reg1, _compare, (char*)pPositions);				// We only change the values of nXPos & nYPos if _comp is set (vPos.x < 0) ? 0 : vPos.x;


			return DrawToTarget(vTargetPos, pTargetSprite, vecPositions, pSource);


		}

		virtual olc::Sprite* DrawToTarget(const olc::vi2d& vPos, olc::Sprite* pdrawTarget, std::vector<int> vecPositions, olc::Sprite* pSource)
		{
			// Create ints to represent the vector positions
			// makes life easier for debugging and creation of the for loop for SIMD
			// std::vector<int> vecPositions = { vPos.y, vPos.x, nHeight, nWidth, nYPos, nXPos, nYStart, nXStart };

			// Create ints to represent the vector positions
			// makes life easier for debugging and creation of the for loop for SIMD
			// std::vector<int> vecPositions = { vPos.y, vPos.x, nHeight, nWidth, nYPos, nXPos, nYStart, nXStart };
			int nHeight = vecPositions[2];
			int nWidth = vecPositions[3];
			int nYPos = vecPositions[4];
			int nXPos = vecPositions[5];
			int nYStart = vecPositions[6];
			int nXStart = vecPositions[7];


			// Get the target layer vector pointer
			int nVecTarget = (nYPos * pdrawTarget->width) + nXPos;
			float* pTargetVector = (float*)pdrawTarget->pColData.data();

			size_t nVecTLen = pdrawTarget->pColData.size();
			int nTargetY = 0;

			// Get the local sprite vector detals
			size_t nVecRead = 0; // Start position of read vector

			// Set up counters
			int ex = nWidth;

			// Get if we have an offset to manage
			// Try to keep your spites width in even mulitples of 4/8 (4, 8, 16, 24, 32, 40... 80, 88, 96, 104)
			// In this way most of your sprites will fall into the the "high speed" processing
			int nOffSet = nWidth % 4;
			bool bUseHighSpeed = (nOffSet == 0) ? true : false;


			// Set up registers
			__m128i _sx, _ex, _compare, _comparePixel, _blendpixel;
			__m128  _vecRead, _vecTargetRead, _vecOutPut;

			Pixel p = olc::BLANK;
			_blendpixel = _mm_set1_epi32(p.n);
			_sx = _mm_set1_epi32(0);
			_ex = _mm_set1_epi32(ex);

			// NOTE: We write out the full for-->loop for both High & Low speed
			// If we put the condional statement between the Y for loop we get a 'branch' in our assembly
			// and lose any gains in proformance
			if (bUseHighSpeed)
			{
				// High speed (up too 2times faster as we have no offset to manage)
				for (int y = nYStart; y < nHeight; y++, nTargetY++)
				{
					// Get next Target Vector position, but if we are out of bounds on the target we break
					nVecTarget = ((nTargetY + nYPos) * pdrawTarget->width) + nXPos;
					if (nVecTarget >= nVecTLen) break;
					pTargetVector += nVecTarget;

					// Get next read Position 
					nVecRead = (y * pSource->width) + nXStart;

					for (int x = nXStart; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_comparePixel = _mm_cmpgt_epi32(_blendpixel, _vecRead);
						_mm_maskmoveu_si128(_vecRead, _comparePixel, (char*)pTargetVector);

					}

					pTargetVector -= nVecTarget; // reset the pointer to 0 position

				}
			}
			else
			{
				// Low speed as we have an offset to manage
				for (int y = nYStart; y < nHeight; y++, nTargetY++)
				{
					// Get next Target Vector position, but if we are out of bounds on the target we break
					nVecTarget = ((nTargetY + nYPos) * pdrawTarget->width) + nXPos;
					if (nVecTarget >= nVecTLen) break;
					pTargetVector += nVecTarget;

					// Get next read Position 
					nVecRead = (y * pSource->width) + nXStart;

					for (int x = nXStart; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						_sx = _mm_set_epi32(x + 3, x + 2, x + 1, x);

						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_vecTargetRead = _mm_load_ps((const float*)((olc::Pixel*)pdrawTarget->pColData.data() + nVecTarget));

						_comparePixel = _mm_cmpgt_epi32(_blendpixel, _vecRead);
						_vecOutPut = _mm_blendv_epi8(_vecTargetRead, _vecRead, _comparePixel);

						_compare = _mm_cmpgt_epi32(_ex, _sx);
						_mm_maskmoveu_si128(_vecOutPut, _compare, (char*)pTargetVector);

					}

					pTargetVector -= nVecTarget; // reset the pointer to 0 position


				}
			}

			return pdrawTarget;


		}

	};
}
#endif


#if defined(__x86_64__ )
#include <immintrin.h>

namespace olc
{
	class SIMD_SSE : public olc::SIMDDrawRoutines
	{

		virtual olc::rcode Clear_SIMD(Pixel p, olc::Sprite* pDrawTarget) override
		{
			if (pDrawTarget == nullptr) return rcode::FAIL;

			int VecEndIndex = (int)pDrawTarget->pColData.size();

			// Lets get any left over pixels to be processed
			// Lets get any left over pixels to be processed
			int nOffSet = VecEndIndex % 4;

			if (nOffSet > 0)
			{
				// we need to work out what is the next multiple of 4 pixels
				nOffSet = (VecEndIndex / 4) + 1;
				nOffSet = (nOffSet * 4);
				nOffSet = nOffSet - VecEndIndex;

			}


			int nTempVecEnd = (VecEndIndex - nOffSet) - 4;

			int nReplacePixel = (int)p.n; // Get the int value of the pixel

			int* nVecA = (int*)pDrawTarget->pColData.data();

			//_replacepixel = | uint32_t nReplacePixel | uint32_t nReplacePixel | uint32_t nReplacePixel | uint32_t nReplacePixel |... 4 slots
			__m128i _replacepixel = _mm_setr_epi32(nReplacePixel, nReplacePixel, nReplacePixel, nReplacePixel);

			int i = 0;
			int j = 0;
			for (i = 0; i < nTempVecEnd; i += 4, nVecA += 4)
			{
				j = i;
				_mm_storeu_si128((__m128i*)nVecA, _replacepixel);
			}


			// Clean up left over pixels
			for (; j < VecEndIndex; j++)
			{
				pDrawTarget->pColData[j] = p;
			}

			return olc::OK;
		}

		virtual olc::rcode DrawFillLine(int sx, int ex, int ny, Pixel p, olc::Sprite* pDrawTarget) override
		{
			if (pDrawTarget == nullptr) return rcode::FAIL;
			// Some optimisation
			if (ex < sx) std::swap(sx, ex);
			if (ny < 0 || ny > pDrawTarget->height) return rcode::OK;	// The line is above/below the viewable screen, no use in drawing it
			if (ex < 0 || sx > pDrawTarget->width) return rcode::OK;	// The line is outside the left/right side of the view screen, no use in drawing it

			// Crop line to fit within draw target
			ny = (ny < 0) ? 0 : ny;
			sx = (sx < 0) ? 0 : sx;
			ex = (ex > pDrawTarget->width) ? ex = pDrawTarget->width : ex;

			// Lets get any left over pixels to be processed
			int nOffSet = ex % 4;

			if (nOffSet > 0)
			{
				// we need to work out what is the next multiple of 4 pixels
				nOffSet = (ex / 4) + 1;
				nOffSet = (nOffSet * 4);
				nOffSet = nOffSet - ex;

			}


			int nTempVecEnd = (ex - nOffSet) - 4;
			int nReplacePixel = (int)p.n; // Get the int value of the pixel

			int i = sx;
			int j = sx;

			int nLineLength = ex - sx;
			if (nLineLength > 8)
			{

				//_replacepixel = | uint32_t nReplacePixel | uint32_t nReplacePixel | uint32_t nReplacePixel | uint32_t nReplacePixel |... 4 slots
				__m128i _replacepixel = _mm_setr_epi32(nReplacePixel, nReplacePixel, nReplacePixel, nReplacePixel);

				int* nVecA = (int*)pDrawTarget->pColData.data(); // Get the start pointer of the vector

				// Move to correct poistion, as we are using __m128i we need to divide by 4
				nVecA += ((ny * pDrawTarget->width) + sx);

				for (i = sx; i <= nTempVecEnd; i += 4, nVecA += 4)
				{
					j = i;
					_mm_storeu_si128((__m128i*)nVecA, _replacepixel);

				}

			}

			// Clean up left over pixels
			int pos = 0;
			size_t vecSize = pDrawTarget->pColData.size();

			for (; j <= ex; j++)
			{
				pos = (ny * pDrawTarget->width) + j;
				if (pos < vecSize) pDrawTarget->pColData[pos] = p; // fixed a small
			}


			return olc::OK;
		}

		virtual olc::rcode FillCircle_SIMD(int32_t x, int32_t y, int32_t radius, Pixel p, olc::Sprite* pDrawTarget) override
		{

			if (radius < 0 || x < -radius || y < -radius || x - pDrawTarget->width > radius || y - pDrawTarget->height > radius)
				return rcode::FAIL;

			if (radius > 0)
			{
				int x0 = 0;
				int y0 = radius;
				int d = 3 - 2 * radius;

				while (y0 >= x0)
				{
					DrawFillLine(x - y0, x + y0, y - x0, p, pDrawTarget);
					if (x0 > 0)	DrawFillLine(x - y0, x + y0, y + x0, p, pDrawTarget);

					if (d < 0)
						d += 4 * x0++ + 6;
					else
					{
						if (x0 != y0)
						{
							DrawFillLine(x - x0, x + x0, y - y0, p, pDrawTarget);
							DrawFillLine(x - x0, x + x0, y + y0, p, pDrawTarget);
						}
						d += 4 * (x0++ - y0--) + 10;
					}
				}
			}
			else
				platform->ptrPGE->Draw(x, y, p);



			return rcode::OK;

		}

		virtual olc::rcode FillTriangle_SIMD(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p, olc::Sprite* pDrawTarget) override
		{
			int t1x, t2x, y, minx, maxx, t1xp, t2xp;
			bool changed1 = false;
			bool changed2 = false;
			int signx1, signx2, dx1, dy1, dx2, dy2;
			int e1, e2;
			// Sort vertices
			if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
			if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
			if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

			t1x = t2x = x1; y = y1;   // Starting points
			dx1 = (int)(x2 - x1);
			if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y2 - y1);

			dx2 = (int)(x3 - x1);
			if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
			else signx2 = 1;
			dy2 = (int)(y3 - y1);

			if (dy1 > dx1) { std::swap(dx1, dy1); changed1 = true; }
			if (dy2 > dx2) { std::swap(dy2, dx2); changed2 = true; }

			e2 = (int)(dx2 >> 1);
			// Flat top, just process the second half
			if (y1 == y2) goto next;
			e1 = (int)(dx1 >> 1);

			/// End Setup

			for (int i = 0; i < dx1;) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < dx1) {
					i++;
					e1 += dy1;
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) t1xp = signx1;//t1x += signx1;
						else          goto next1;
					}
					if (changed1) break;
					else t1x += signx1;
				}
				// Move line
			next1:
				// process second line until y value is about to change
				while (1) {
					e2 += dy2;
					while (e2 >= dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;//t2x += signx2;
						else          goto next2;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next2:
				if (minx > t1x) minx = t1x;
				if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x;
				if (maxx < t2x) maxx = t2x;
				simddrawer->DrawFillLine(minx, maxx, y, p, pDrawTarget); // Draw line from min to max points found on the y using SIMD, // John Galvin added missing 'p'
				// Now increase y
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y == y2) break;
			}

		next:
			// Second half
			dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
			else signx1 = 1;
			dy1 = (int)(y3 - y2);
			t1x = x2;

			if (dy1 > dx1) {   // swap values
				std::swap(dy1, dx1);
				changed1 = true;
			}
			else changed1 = false;

			e1 = (int)(dx1 >> 1);

			for (int i = 0; i <= dx1; i++) {
				t1xp = 0; t2xp = 0;
				if (t1x < t2x) { minx = t1x; maxx = t2x; }
				else { minx = t2x; maxx = t1x; }
				// process first line until y value is about to change
				while (i < dx1) {
					e1 += dy1;
					while (e1 >= dx1) {
						e1 -= dx1;
						if (changed1) { t1xp = signx1; break; }//t1x += signx1;
						else          goto next3;
					}
					if (changed1) break;
					else   	   	  t1x += signx1;
					if (i < dx1) i++;
				}
			next3:
				// process second line until y value is about to change
				while (t2x != x3) {
					e2 += dy2;
					while (e2 >= dx2) {
						e2 -= dx2;
						if (changed2) t2xp = signx2;
						else          goto next4;
					}
					if (changed2)     break;
					else              t2x += signx2;
				}
			next4:

				if (minx > t1x) minx = t1x;
				if (minx > t2x) minx = t2x;
				if (maxx < t1x) maxx = t1x;
				if (maxx < t2x) maxx = t2x;
				simddrawer->DrawFillLine(minx, maxx, y, p, pDrawTarget); // Draw line from min to max points found on the y using SIMD.
				if (!changed1) t1x += signx1;
				t1x += t1xp;
				if (!changed2) t2x += signx2;
				t2x += t2xp;
				y += 1;
				if (y > y3) return rcode::OK;
			}

			return rcode::OK;
		}

		virtual olc::rcode FillRect_SIMD(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p, olc::Sprite* pDrawTarget) override
		{
			int32_t x2 = x + w;
			int32_t y2 = y + h;

			if (x < 0) x = 0;
			if (x >= (int32_t)pDrawTarget->width) x = (int32_t)pDrawTarget->width;
			if (y < 0) y = 0;
			if (y >= (int32_t)pDrawTarget->height) y = (int32_t)pDrawTarget->height;

			if (x2 < 0) x2 = 0;
			if (x2 >= (int32_t)pDrawTarget->width) x2 = (int32_t)pDrawTarget->width;
			if (y2 < 0) y2 = 0;
			if (y2 >= (int32_t)pDrawTarget->height) y2 = (int32_t)pDrawTarget->height;

			for (int j = y; j < y2; j++)
			{
				simddrawer->DrawFillLine(x, x2, j, p, pDrawTarget);
			}

			return rcode::OK;
		}

		virtual olc::rcode DrawSprite_SIMD(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip, olc::Sprite* pDrawTarget) override
		{
			if (sprite == nullptr) return rcode::FAIL;
			olc::vi2d vPos = { x, y };

			// Lets check if the sprite all ready exist?
			olc::vi2d vStartPos = { 0,0 };
			olc::vi2d vScaleSize = { sprite->width * (int)scale, sprite->height * (int)scale };
			olc::Decal* dec = (olc::Decal*)sprite->GetStoredSubDecal(vStartPos, vScaleSize, scale, (olc::Sprite::Flip)flip, pDrawTarget);
			if (dec == nullptr)
			{
				//1: Lets flip it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprFlipped = sprite->Duplicate((olc::Sprite::Flip)flip);

				//2: Lets scale it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprScaled = sprFlipped->Duplicate(scale);

				//3: Store the SubSprite, a Decal will also be created 
				if (!sprite->StoreSubSprite(sprScaled, vStartPos, scale, (olc::Sprite::Flip)flip, pDrawTarget))
				{
					// OK the vector is full or sub sprites disabled
					// We Cannot Store the sub sprite, lets draw it
					DuplicateMerge_SIMD(vStartPos, pDrawTarget, olc::BLANK, sprScaled);
					delete sprScaled;
					delete sprFlipped;
					return rcode::OK;
				}
				else
				{
					//4: Get the newly created Decal
					dec = (olc::Decal*)sprite->GetStoredSubDecal(vStartPos, vScaleSize, scale, (olc::Sprite::Flip)flip, pDrawTarget);

					//5: Clean up
					delete sprFlipped;

				}

			}

			renderer->ptrPGE->DrawDecal(vPos, dec);
			return rcode::OK;
		}

		virtual olc::rcode DrawPartialSprite_SIMD(const olc::vi2d& vPos, olc::Sprite* pSource, const olc::vi2d& vStartPos, const olc::vi2d& vSize, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget) override
		{

			// Lets check if the sprite all ready exist?
			scale = (scale < 1) ? 1 : scale;

			olc::vi2d vScaleSize = { vSize.x * (int)scale, vSize.y * (int)scale };
			olc::Decal* dec = (olc::Decal*)pSource->GetStoredSubDecal(vStartPos, vScaleSize, scale, flip, pDrawTarget);
			if (dec == nullptr)
			{

				//1: lets get the partial;
				olc::Sprite* sprPartial = pSource->Duplicate(vStartPos, vSize);

				//2: Lets flip it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprFlipped = sprPartial->Duplicate((olc::Sprite::Flip)flip);

				//3: Lets scale it (if Store Sub Sprites has a copy it will be returned)
				olc::Sprite* sprScaled = sprFlipped->Duplicate(scale);


				//4: Store the SubSprite, a Decal will also be created 
				if (!pSource->StoreSubSprite(sprScaled, vStartPos, scale, flip))
				{
					// OK the vector is full or sub sprites disabled
					// We Cannot Store the sub sprite, lets draw it
					DuplicateMerge_SIMD(vStartPos, pDrawTarget, olc::BLANK, sprScaled);
					delete sprScaled;
					delete sprFlipped;
					return rcode::OK;
				}
				else
				{
					//5: Get the Decal
					dec = (olc::Decal*)pSource->GetStoredSubDecal(vStartPos, vScaleSize, scale, flip, pDrawTarget);

					//6: Clean up
					delete sprPartial;
					delete sprFlipped;

				}

			}

			renderer->ptrPGE->DrawDecal(vPos, dec);
			return rcode::OK;
		}

		virtual olc::rcode DrawMergeSprite_SIMD(int32_t vPosx, int32_t vPosy, Sprite* pFromSprite, int32_t vToSpritePosx, int32_t vToSpritePosy, Sprite* pToSprite, Pixel blendPixel, uint32_t scale, olc::Sprite::Flip flip, olc::Sprite* pDrawTarget) override
		{

			olc::vi2d vPos = { vPosx , vPosy };
			olc::vi2d vSize = { pToSprite->width * (int32_t)scale ,  pToSprite->height * (int32_t)scale };

			olc::vi2d vToSpritePos = { vToSpritePosx ,vToSpritePosy };

			olc::Decal* dec = (olc::Decal*)pFromSprite->GetStoredSubDecal(vToSpritePos, vSize, scale, flip, pToSprite);
			if (dec == nullptr)
			{
				olc::Sprite* pMergeSprite = nullptr;
				olc::Sprite* pMergeScaleSprite = nullptr;
				olc::Sprite* pMergeFilpSprite = nullptr;

				pMergeSprite = pFromSprite->DuplicateMerge(vToSpritePos, pToSprite, blendPixel);
				pMergeScaleSprite = pMergeSprite->Duplicate(scale);
				pMergeFilpSprite = pMergeScaleSprite->Duplicate((olc::Sprite::Flip)flip);

				//4: Store the SubSprite, a Decal will also be created 
				if (!pFromSprite->StoreSubSprite(pMergeFilpSprite, vToSpritePos, scale, flip, pToSprite))
				{
					// OK the vector is full or sub sprites disabled
					// We Cannot Store the sub sprite, lets draw it
					DuplicateMerge_SIMD(vToSpritePos, pDrawTarget, olc::BLANK, pMergeFilpSprite);
					delete pMergeSprite;
					delete pMergeScaleSprite;
					delete pMergeFilpSprite;
					return rcode::OK;
				}
				else
				{
					//5: Get the Decal
					dec = (olc::Decal*)pFromSprite->GetStoredSubDecal(vToSpritePos, vSize, scale, flip, pToSprite);

					//6: Clean up
					delete pMergeSprite;
					delete pMergeScaleSprite;
					renderer->ptrPGE->DrawDecal(vPos, dec);
				}

			}

			renderer->ptrPGE->DrawDecal(vPos, dec);
			return rcode::OK;
		}

		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite* pSource) override
		{
			// This is the fastest way of duplicating, I say this is not required, kept for testing 
			olc::Sprite* spr = new olc::Sprite(pSource->width, pSource->height);
			std::memcpy(spr->GetData(), pSource->GetData(), pSource->width * pSource->height * sizeof(olc::Pixel));
			spr->modeSample = pSource->modeSample;
			return spr;

		}

		virtual olc::Sprite* Duplicate_SIMD(const olc::vi2d& vPos, const olc::vi2d& vSize, olc::Sprite* pSource) override
		{

			// Some Maths, to ensure the partial sprite is created correctly
			int newSizeX = vSize.x;
			int newSizeY = vSize.y;

			int maxX = vPos.x + vSize.x;
			int maxY = vPos.y + vSize.y;

			if (maxX > pSource->width) newSizeX = pSource->width - vPos.x;
			if (maxY > pSource->height) newSizeY = pSource->height - vPos.y;


			olc::Sprite* spr = new olc::Sprite(newSizeX, newSizeX);
			Clear_SIMD(olc::BLANK, spr);
			int sx = 0;
			int ex = newSizeX;
			int nOffSet = ex % 4;

			if (nOffSet > 0)
			{
				// we need to work out what is the next multiple of 4 pixels
				nOffSet = (ex / 4) + 1;
				nOffSet = (nOffSet * 4);
				nOffSet = nOffSet - ex;

			}
			bool bUseHighSpeed = (nOffSet == 0) ? true : false;

			int nVecTarget = 0;
			float* pTargetVector = (float*)spr->pColData.data();
			size_t nVecTLen = spr->pColData.size();

			size_t nVecRead = (vPos.y * pSource->width) + vPos.x; // Start position of read vector
			size_t nVecRLen = pSource->pColData.size();

			__m128i _sx, _ex, _result, _vecReadi;
			__m128 _vecReadp;

			_sx = _mm_set1_epi32(sx);
			_ex = _mm_set1_epi32(ex);
			_result = _mm_set1_epi32(0xFF); // 0xFF = -1 -> True, 0x00 = 0 -> False;

			// NOTE: We write out the full for-->loop for both High & Low speed
			// If we put the conditional statement between the for Y for loop we get a 'branch' in our assembly 
			// and lose any gains in performance
			if (bUseHighSpeed)
			{
				// High speed (up too 2times faster as we have no offset to manage)
				for (int y = 0; y < newSizeY; y++)
				{
					if (nVecRead > nVecRLen)
					{
						break; // Break if we reached the end of the read vector
					}
					if (nVecTarget > nVecTLen) {
						break; // break if we reached the end of the target vector
					}

					// Get the next position of the read vector
					// Take note of (y + vPos.y), we need the position of y + the next row of y for the read vector (nVecRead)
					nVecRead = ((y + vPos.y) * pSource->width) + vPos.x;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						// Load in the read vector
						_vecReadp = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_mm_storeu_ps(pTargetVector, _vecReadp);

					}


				}

			}
			else
			{
				// We have an offset to manage
				for (int y = 0; y < newSizeY; y++)
				{
					if (nVecRead > nVecRLen)
					{
						break; // Break if we reached the end of the read vector
					}
					if (nVecTarget > nVecTLen) {
						break; // break if we reached the end of the target vector
					}

					// Get the next position of the read vector
					// Take note of (y + vPos.y), we need the position of y + the next row of y for the read vector (nVecRead)
					nVecRead = ((y + vPos.y) * pSource->width) + vPos.x;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						// Load in the read vector
						_vecReadi = _mm_load_si128((const __m128i*)((olc::Pixel*)pSource->pColData.data() + nVecRead));

						// We compare if the all the pixels ly within sx->ex, and pixel greater then ex are not process
						_sx = _mm_set_epi32(x + 3, x + 2, x + 1, x);

						// Take note there is 'no less than or equals', but if you just reverse the operands and use 'greater than' you get the excat same affect
						_result = _mm_cmpgt_epi32(_ex, _sx);

						// Store only the pixels that are between sx-->ex
						_mm_maskmoveu_si128(_vecReadi, _result, (char*)pTargetVector);

					}

					// Shift the ptr for pTargetVector by the offset
					// This ensures the ptr is always in the correct position for the next row of y
					// Debug it to understand better
					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;


				}

			}


			//Clean up any left over pixels
			for (size_t x = nVecTarget; x < (size_t)nVecTLen; x++, nVecRead++)
			{
				if (nVecRead > nVecRLen)
				{
					break; // Break if we reached the end of the read vector
				}
				if (nVecTarget > nVecTLen) {
					break; // break if we reached the end of the target vector
				}

				spr->pColData[x] = pSource->pColData[nVecRead];


			}


			return spr;

		}

		/*-------------- New Methods John Galvin --------------*/

		virtual olc::Sprite* Duplicate_SIMD(olc::Sprite::Flip flip, olc::Sprite* pSource) override
		{
			if (pSource == nullptr) return nullptr;

			olc::Sprite* spr = nullptr;

			// Some optimisations, if we are not flipping return a duplicate
			if ((uint8_t)flip < 1)
			{
				spr = pSource->Duplicate();
				return spr;
			}

			olc::vi2d vStartPos = { 0, 0 };
			olc::vi2d vSize = { pSource->width, pSource->height };

			spr = new olc::Sprite(pSource->width, pSource->height);

			int ex = pSource->width;
			int nOffSet = ex % 4;

			if (nOffSet > 0)
			{
				// we need to work out what is the next multiple of 4 pixels
				// Example: vSize.x = 270 
				nOffSet = (ex / 4) + 1; // 270 / 4 = 67. + 1 = 68
				nOffSet = (nOffSet * 4); // 68 * 4 = 272
				nOffSet = nOffSet - ex; // therefore the offset is 2

			}

			int nVecTarget = 0;
			float* pTargetVector = (float*)spr->pColData.data();
			size_t nVecTLen = spr->pColData.size();

			size_t nVecRead = 0; // Start position of read vector
			size_t nVecRLen = pSource->pColData.size();

			__m128 _vecRead;

			if (flip & olc::Sprite::Flip::HORIZ)
			{
				nVecRead = nVecRLen;
				for (int y = 1; y <= pSource->height; y++)
				{
					if (y == 0) y = 1;
					nVecRead = (y * pSource->width) - 4;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += -4, nVecTarget += 4)
					{

						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_mm_storer_ps(pTargetVector, _vecRead);

					}

					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}

			}

			if (flip & olc::Sprite::Flip::VERT)
			{
				nVecRead = nVecRLen;
				for (int y = pSource->height; y > 0; y--)
				{
					if (nVecTarget + 4 > nVecTLen) break;
					nVecRead = (y * pSource->width) + 0;
					for (int x = 0; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_mm_storeu_ps(pTargetVector, _vecRead);

					}
					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}

			}

			// There MAY be a few left over sprites we just clear them
			// This is a little cheat, you could write some very complex code to ensure all left pixels are matched, but this will be very slow. 
			// Therefore we just hide (Alpha) them, at most there could be 1 line of pixels at the top/bottom/top, in most cases it will be a few pixels
			// The end user cannot see that this 1 line of pixels is missing, it will be so small
			for (size_t x = nVecTarget; x < (size_t)nVecTLen; x++)
			{

				spr->pColData[x] = olc::BLANK;

			}

			return spr;

		}

		virtual olc::Sprite* Duplicate_SIMD(uint32_t scale, olc::Sprite* pSource) override
		{
			if (pSource == nullptr) return nullptr;

			scale = (scale < 1) ? 1 : scale;
			if ((uint32_t)scale == 1) return pSource->Duplicate();
			olc::Sprite* spr = new olc::Sprite(pSource->width * scale, pSource->height * scale);

			int nVecTarget = 0;										// Target vector position
			float* pTargetVector = (float*)spr->pColData.data();	// Target vector pointer
			size_t nVecTLen = spr->pColData.size();					// Target vector size

			uint32_t nVecRead = 0;									// Start position of read vector
			size_t nVecRLen = pSource->pColData.size();				// Read vector size

			int nReadCount = std::max(int(4 / scale), 1);			// Number of pixels to be read in

			int nOffSet = 4 % scale;								// Offset for left over pixels
			uint32_t nScaleCount = 0;								// Scale count used when the scale is greater than the register
			if (scale > 4)
			{
				nOffSet = 0;
				nScaleCount = scale - 4;
			}

			int nsuffle[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Suffle Pixels
			int nPos = 0;
			if (scale > 1)
			{
				// If Scale 2 the it is double 1 pixel becomes 2 pixels
				// {0, 1, 2, 3, 4, 5, 6 >> 16} --> {0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6, 7,  etc >> 16}; 
				// I know there are fancy ways of doing this, but at least this way you can debug it and see what is happening
				int i = 0;
				while (nPos < 16)
				{
					for (int j = 0; j < scale; j++)
					{
						if (nPos > 15) break;
						for (int k = 0; k < 4; k++)
						{
							if (nPos > 15) break;
							nsuffle[nPos] = i + k;
							nPos++;
						}
					}
					i += 4;
				}

			}

			__m128i _shufflePixels, _vecRead;
			__m128 _result;

			// 'Lets do the shuffle, shuffle baby...'
			_shufflePixels = _mm_set_epi8(nsuffle[15], nsuffle[14], nsuffle[13], nsuffle[12],
				nsuffle[11], nsuffle[10], nsuffle[9], nsuffle[8],
				nsuffle[7], nsuffle[6], nsuffle[5], nsuffle[4],
				nsuffle[3], nsuffle[2], nsuffle[1], nsuffle[0]
			);

			int y = 0; int x = 0; int yS = 0;
			uint32_t nTottle = scale;

			for (y = 0; y < pSource->height; y++, yS++)
			{
				// Added extra Y Lines of x values
				nTottle++;
				if (nTottle < scale) y--;
				if (nTottle >= scale) nTottle = 0;

				nVecRead = (y * pSource->width) + 0;
				nVecTarget = (yS * spr->width) + 0;
				pTargetVector += nVecTarget;
				for (x = 0; x < pSource->width; x += nReadCount, nVecRead += nReadCount, pTargetVector += 4, nVecTarget += 4)
				{
					_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
					_result = _mm_shuffle_epi8(_vecRead, _shufflePixels);
					_mm_storeu_ps(pTargetVector, _result);

					// If out scale is greater than 4 times, i.e.10 then we need repeat the pixels
					if (nScaleCount > 0)
					{
						for (int i = 1; i < (int)nScaleCount; i += 4)
						{
							pTargetVector += 4;
							nVecTarget += 4;
							nOffSet = (i * 4) - (int)nScaleCount;
							_mm_storeu_ps(pTargetVector, _result);

						}
					}

					// Move back the pointer and vectors to get the offset bytes
					pTargetVector -= nOffSet;
					nVecTarget -= nOffSet;

				}

				pTargetVector -= nVecTarget;

			}

			// There can be some pixels on the target sprite left over
			// TODO: Still not happy with this maths, 
			// the formula p = (y * width) + x is always perfect, it just how I am executing this I do not like
			int nYPos = ((y - scale) * pSource->width);
			int nYTarPos = (yS * (pSource->width * scale));

			// Check is there are left over pixels
			if (nYTarPos < nVecTLen)
			{
				// If so process them
				for (int i = nYPos; i < nVecRLen; i++)
				{
					for (size_t j = 0; j < scale; j++, nYTarPos++)
					{
						if (nYTarPos >= nVecTLen) break;
						spr->pColData[nYTarPos] = pSource->pColData[i];
					}
				}
			}


			return spr;

		}

		virtual olc::Sprite* DuplicateMerge_SIMD(const olc::vi2d& vTargetPos, olc::Sprite* pTargetSprite, olc::Pixel p, olc::Sprite* pSource) override
		{
			if (pTargetSprite == nullptr) return nullptr;

			/*---- Non-SIMD Vs SIMD*/


			/*
				There is no real performance gain using either of the executions (Non-SIMD, SIMD)
				Always remember it is near impossible to beat the complier. You might ask then why write it in SIMD at all?
				Well, when you are developing low level code, it is difficult to jump between languages.
				Most developers prefer to stay with one language within a method.
				As these methods are SIMD executions, then write it all in SIMD, therefore there is no surprises later when another developer
				needs to debug.
				They are expecting SIMD, then they get SIMD
				Finally the SIMD code below should be a tiny bit faster, but it would be impossible to measure
			*/
			/*
			Non SIMD Code :

			// Ok we need to ensure the sprite can fit on the layer (pdrawTarget)
			// Work out if the sprite is out of bounds and crop the sprite to fit into the bounds

			int nFullWidth = vPos.x + pSource->width;
			int nFullHeight = vPos.y + pSource->height;
			int nWidth = pSource->width; //std::min(nFullWidth, pdrawTarget->width);
			int nHeight = pSource->height; // std::min(nFullHeight, pdrawTarget->height);

			if (nFullWidth >= pdrawTarget->width)
			{
				// Get the new width for off layer sprite
				nWidth = nFullWidth - pdrawTarget->width;
				nWidth = pSource->width - nWidth;
			}

			if (nFullHeight >= pdrawTarget->height)
			{
				// Get the new height for off layer sprite
				nHeight = nFullHeight - pdrawTarget->height;
				nHeight = pSource->height - nHeight;
			}

			// Get the new Start Position for off layer sprite
			int nXStart = (vPos.x < 0) ? vPos.x * -1 : 0;
			int nYStart = (vPos.y < 0) ? vPos.y * -1 : 0;

			// Get the new vPosition for off layer sprite
			int nXPos = (vPos.x < 0) ? 0 : vPos.x;
			int nYPos = (vPos.y < 0) ? 0 : vPos.y;

			std::vector<int> vecPositions = { vPos.y, vPos.x, nHeight, nWidth, nYPos, nXPos, nYStart, nXStart };
			*/

			/*---- END Non-SIMD Vs SIMD ---*/

			/* Ok we need to ensure the sprite can fit the sprite on the layer (pdrawTarget)
				Work out if the sprite is out of bounds and crop the sprite to fit into the bounds
			*/

			// Vector of position: Order is important, SIMD will read the vector in backwards, (right to left) <---
			std::vector<int> vecPositions = { vTargetPos.y, vTargetPos.x, pSource->height, pSource->width, vTargetPos.y, vTargetPos.x, 0, 0 };
			int* pPositions = vecPositions.data();

			__m128i _reg1, _reg2, _reg3, _reg4, _reg5, _compare;

			_reg1 = _mm_set_epi32(pSource->width, pSource->height, 0, 0);			// Holds width and height
			_reg2 = _mm_set_epi32(vTargetPos.x, vTargetPos.y, 0, 0);				// Holds vPos.x and vPos.y
			_reg3 = _mm_add_epi32(_reg1, _reg2);									// nFullWidth = vPos.x + width, nFullHeight = vPos.y + height;
			_reg4 = _mm_set_epi32(pTargetSprite->width, pTargetSprite->height, 0, 0);	// Holds pdrawTarget->width, pdrawTarget->height
			_compare = _mm_cmpgt_epi32(_reg3, _reg4);								// if (nFullWidth >= pdrawTarget->width) (true false)
			_reg5 = _mm_sub_epi32(_reg3, _reg4);									// nWidth = nFullWidth - pdrawTarget->width, nheight = nheight - pdrawTarget->height,
			_reg5 = _mm_sub_epi32(_reg1, _reg5);									// nWidth = width - nWidth, nHeight = height - nHeight;
			_mm_maskmoveu_si128(_reg5, _compare, (char*)pPositions);				// We only store the computed values of reg5, if _comp is set. i.e. nFullWidth is greater than pdrawTarget->width 

			// Now lets get the nXStart, nYStart 
																					// Note the vector is read in backwards, (right to left) <---    <---    <--- 					
			pPositions += 4;														// Move our pointer down by 4 so we are pointing to {... vPos.y, vPos.x, 0, 0}
			_reg1 = _mm_set1_epi32(0);												// Clear reg1 to 0, (vPos.x < 0) ? vPos.x * -1 : 0 <- this zero
			_compare = _mm_cmpgt_epi32(_reg1, _reg2);								//(vPos.x < 0)?,  (vPos.y < 0)?
			_reg5 = _mm_abs_epi32(_reg2);											// vPos.x * -1, vPos.y * -1. Abs will return positive absolute numbers, we do not need to multiply
			_mm_maskmoveu_si128(_reg5, _compare, (char*)pPositions);				// We only change the values of nXStart & nYStart if _comp is set (nXStart = (vPos.x < 0) ? vPos.x * -1)

			// Now lets get the nXPos, nYPso

			_reg2 = _mm_set_epi32(0, 0, vTargetPos.x, vTargetPos.y);				// Toddle the reg2 so that 0's will cause nXStart & nYStart results not to be affected
			_compare = _mm_cmpgt_epi32(_reg1, _reg2);								// (vPos.x < 0)?,  (vPos.y < 0)? . We reuse _reg1 as it is already set to 0's
			_mm_maskmoveu_si128(_reg1, _compare, (char*)pPositions);				// We only change the values of nXPos & nYPos if _comp is set (vPos.x < 0) ? 0 : vPos.x;


			return DrawToTarget(vTargetPos, pTargetSprite, vecPositions, pSource);


		}

		virtual olc::Sprite* DrawToTarget(const olc::vi2d& vPos, olc::Sprite* pdrawTarget, std::vector<int> vecPositions, olc::Sprite* pSource)
		{
			// Create ints to represent the vector positions
			// makes life easier for debugging and creation of the for loop for SIMD
			// std::vector<int> vecPositions = { vPos.y, vPos.x, nHeight, nWidth, nYPos, nXPos, nYStart, nXStart };

			// Create ints to represent the vector positions
			// makes life easier for debugging and creation of the for loop for SIMD
			// std::vector<int> vecPositions = { vPos.y, vPos.x, nHeight, nWidth, nYPos, nXPos, nYStart, nXStart };
			int nHeight = vecPositions[2];
			int nWidth = vecPositions[3];
			int nYPos = vecPositions[4];
			int nXPos = vecPositions[5];
			int nYStart = vecPositions[6];
			int nXStart = vecPositions[7];


			// Get the target layer vector pointer
			int nVecTarget = (nYPos * pdrawTarget->width) + nXPos;
			float* pTargetVector = (float*)pdrawTarget->pColData.data();

			size_t nVecTLen = pdrawTarget->pColData.size();
			int nTargetY = 0;

			// Get the local sprite vector details
			size_t nVecRead = 0; // Start position of read vector
			int ex = nWidth;

			// Get if we have an offset to manage
			// Try to keep your spites width in even multiples of 4/8 (4, 8, 16, 24, 32, 40... 80, 88, 96, 104)
			// In this way most of your sprites will fall into the the "high speed" processing
			int nOffSet = nWidth % 4;
			bool bUseHighSpeed = (nOffSet == 0) ? true : false;

			// Set up registers
			__m128i _sx, _ex, _compare, _comparePixel, _blendpixel, _vecRead, _vecTargetRead, _vecOutPut;

			Pixel p = olc::BLANK;
			_blendpixel = _mm_set1_epi32(p.n);
			_sx = _mm_set1_epi32(0);
			_ex = _mm_set1_epi32(ex);

			// NOTE: We write out the full for-->loop for both High & Low speed
			// If we put the conditional statement between the Y for loop we get a 'branch' in our assembly
			// and lose any gains in performance
			if (bUseHighSpeed)
			{
				// High speed (up too 2times faster as we have no offset to manage)
				for (int y = nYStart; y < nHeight; y++, nTargetY++)
				{
					// Get next Target Vector position, but if we are out of bounds on the target we break
					nVecTarget = ((nTargetY + nYPos) * pdrawTarget->width) + nXPos;
					if (nVecTarget >= nVecTLen) break;
					pTargetVector += nVecTarget;

					// Get next read Position 
					nVecRead = (y * pSource->width) + nXStart;

					for (int x = nXStart; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_comparePixel = _mm_cmpgt_epi32(_blendpixel, _vecRead);
						_mm_maskmoveu_si128(_vecRead, _comparePixel, (char*)pTargetVector);

					}

					pTargetVector -= nVecTarget; // reset the pointer to 0 position

				}
			}
			else
			{
				// Low speed as we have an offset to manage
				for (int y = nYStart; y < nHeight; y++, nTargetY++)
				{
					// Get next Target Vector position, but if we are out of bounds on the target we break
					nVecTarget = ((nTargetY + nYPos) * pdrawTarget->width) + nXPos;
					if (nVecTarget >= nVecTLen) break;
					pTargetVector += nVecTarget;

					// Get next read Position 
					nVecRead = (y * pSource->width) + nXStart;

					for (int x = nXStart; x < ex; x += 4, pTargetVector += 4, nVecRead += 4, nVecTarget += 4)
					{
						_sx = _mm_set_epi32(x + 3, x + 2, x + 1, x);

						_vecRead = _mm_load_ps((const float*)((olc::Pixel*)pSource->pColData.data() + nVecRead));
						_vecTargetRead = _mm_load_ps((const float*)((olc::Pixel*)pdrawTarget->pColData.data() + nVecTarget));

						_comparePixel = _mm_cmpgt_epi32(_blendpixel, _vecRead);
						_vecOutPut = _mm_blendv_epi8(_vecTargetRead, _vecRead, _comparePixel);

						_compare = _mm_cmpgt_epi32(_ex, _sx);
						_mm_maskmoveu_si128(_vecOutPut, _compare, (char*)pTargetVector);

					}

					pTargetVector -= nVecTarget; // reset the pointer to 0 position


				}
			}

			return pdrawTarget;

		}

	};
}

#endif

#endif


#pragma endregion
// O------------------------------------------------------------------------------O
// | END SIMD:                                         |
// O------------------------------------------------------------------------------O



// O------------------------------------------------------------------------------O
// | olcPixelGameEngine Auto-Configuration                                        |
// O------------------------------------------------------------------------------O
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region pge_config
namespace olc
{
	void PixelGameEngine::olc_ConfigureSystem()
	{
		olc::Sprite::loader = nullptr;

#if defined(__ANDROID__)
		platform = std::make_unique<olc::Platform_Android>();
		renderer = std::make_unique<olc::Renderer_OGLES10>();
		platform->ptrPGE = this;

		struct android_app* android_app = (struct android_app*)MyAndroidApp;
		memset(&this->pOsEngine, 0, sizeof(olc::OSEngineInstance));

		MyAndroidApp->userData = &this->pOsEngine;

		MyAndroidApp->onAppCmd = &EventManager::getInstance().HandleCommand;
		MyAndroidApp->onInputEvent = &EventManager::getInstance().HandleInput;
		this->pOsEngine.app = android_app;
		olc::Sprite::loader = std::make_unique<olc::ImageLoader_STB_ANDROID>();

		filehandler = std::make_unique<olc::FileHandler_ANDROID>();


#if defined(__arm__ ) || defined(__aarch64__)
		simddrawer = std::make_unique<olc::SIMD_NEON_ARM>();

#else

#if defined(__x86_64__)
		/*
			64 bit Processor
			Use SSE4 128bit
			Note: most Android devices use Intel Atom, which supports SSE3/4 only
			Chromebooks however can use iCore processors (AVX2)
			I have never hear of a Chromebook using Xeon processors (AVX512)

			NOTE: Simulators can often break when using SEE, it is best to
			use a real phone if possible
		*/
		simddrawer = std::make_unique<olc::SIMD_NONE>();
#else
		//32 bit Processor Use SIMD NONE, will update this later (defined(__i386__))
		// There should now be many of these around
		simddrawer = std::make_unique<olc::SIMD_NONE>();

#endif // defined(__x86_64__)


#endif // defined(__arm__ ) || defined(__aarch64__)



#endif // defined(__ANDROID__)



#if defined(__APPLE__)
		platform = std::make_unique<olc::Platform_iOS>();
		renderer = std::make_unique<olc::Renderer_OGLES10>();
		simddrawer = std::make_unique<olc::SIMD_NONE>();
		// TODO: Apple event manager

		olc::Sprite::loader = std::make_unique<olc::ImageLoader_STB_iOS>();
#if defined (__arm__ )
		simddrawer = std::make_unique<olc::SIMD_NEON_ARM>();
#endif

		//#if defined (__aarch64__)
		//		simddrawer = std::make_unique<olc::SIMD_NEON_ARM64>();
		//#else
		//		simddrawer = std::make_unique<olc::SIMD_NONE>();
		//#endif // __arm__ || __aarch64__

#endif// __APPLE__	
		// Associate components with PGE instance
		platform->ptrPGE = this;
		renderer->ptrPGE = this;

	}


}

#pragma endregion
#pragma GCC diagnostic pop


#endif // END OLC_PGE_APPLICATION

// O------------------------------------------------------------------------------O
// | END OF OLC_PGE_APPLICATION                                                   |
// O------------------------------------------------------------------------------O