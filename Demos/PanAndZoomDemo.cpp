
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.1,                      //
// John Galvin aka Johnngy63: 21-Oct-2023                       //
// Full production release                                      //
// Pan and Zoom Demo                                            //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////


/*
OneLoneCoder.com - Programming Panning & Zooming
"Left a bit, bit more, there..." - @Javidx9

License
~~~~~~~
One Lone Coder Console Game Engine  Copyright (C) 2018  Javidx9
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions; See license for details.
Original works located at:
https://www.github.com/onelonecoder
https://www.onelonecoder.com
https://www.youtube.com/javidx9
GNU GPLv3
https://github.com/OneLoneCoder/videos/blob/master/LICENSE

From Javidx9 :)
~~~~~~~~~~~~~~~
Hello! Ultimately I don't care what you use this for. It's intended to be
educational, and perhaps to the oddly minded - a little bit of fun.
Please hack this, change it and use it in any way you see fit. You acknowledge
that I am not responsible for anything bad that happens as a result of
your actions. However this code is protected by GNU GPLv3, see the license in the
github repo. This means you must attribute me if you use it. You can view this
license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
Cheers!

Background
~~~~~~~~~~
Used in absolutely everything now, panning and zooming is an important
tool to know how to implement. Even though it appears simple, getting
your head around different spatial transforms can be challenging!

Author
~~~~~~
Twitter: @javidx9
Blog: http://www.onelonecoder.com
Discord: https://discord.gg/WhwHUMV

Video:
~~~~~~
https://youtu.be/ZQ8qtAizis4

Last Updated: 10/06/2018
*/


/* Alterations Joseph21 - 2022-07-18
 *
 * Port to PixelGameEngine - 2022-07-18
 *   - see cheat sheet for generic adaptations needed for port
 *   - changed screen and pixel sizes
 *
 * Port to PixelGameEngine Mobile Johnngy63 - 08-Jul-2023
 */


#include <malloc.h>
#define OLC_PGE_APPLICATION
#define OLC_IMAGE_STB 
 //#define STBI_NO_SIMD 
#if defined(__arm__)
// Use Advance SIMD NEON when loading images for STB 
// Default is SSE2 (x86)
#define STBI_NEON
#endif
#include "olcPixelGameEngine_Mobile.h"
#include <fstream> // Used for saving the savestate to a file


class PGE_Mobile : public olc::PixelGameEngine
{

public:
	PGE_Mobile()
	{
		sAppName = "Pan and Zoom Demo";
	}

	/* Vectors */
	std::vector<std::string> vecMessages;
	/* END Vectors*/

	int nFrameCount = 0;
	int nStep = 20;

	/* Sprites */
	olc::Sprite* sprTouchTester = nullptr;
	/* END Sprites*/

	/* Decals */
	olc::Decal* decTouchTester = nullptr;
	/* End Decals */


	/* Sensors */
	std::vector<olc::SensorInformation> vecSensorInfos;
	/*End Sensors*/


public:
	//Example Save State Struct and Vector for when your app is paused
	struct MySaveState
	{
		std::string key;
		int value;
	};

	std::vector<MySaveState> vecLastState;

private:

	/// <summary>
	/// Draws a Target Pointer at the center position of Center Point
	/// </summary>
	/// <param name="vCenterPoint">Center Position of the target</param>
	/// <param name="nLineLenght">Length of lines</param>
	/// <param name="nCircleRadus">Center Circle radius</param>
	void DrawTargetPointer(olc::vi2d vCenterPoint, int32_t nLineLenght, int32_t nCircleRadus, olc::Pixel p = olc::WHITE)
	{
		/*
						|
						|
					----O----
						|
						|


		*/
		FillCircle(vCenterPoint, nCircleRadus, p);
		DrawLine(vCenterPoint, { vCenterPoint.x, vCenterPoint.y + nLineLenght }, p);
		DrawLine(vCenterPoint, { vCenterPoint.x, vCenterPoint.y - nLineLenght }, p);
		DrawLine(vCenterPoint, { vCenterPoint.x + nLineLenght, vCenterPoint.y }, p);
		DrawLine(vCenterPoint, { vCenterPoint.x - nLineLenght, vCenterPoint.y }, p);

	}

private:

	float fOffsetX = 0.0f;
	float fOffsetY = 0.0f;
	float fScaleX = 1.0f;
	float fScaleY = 1.0f;

	float fStartPanX = 0.0f;
	float fStartPanY = 0.0f;

	float fSelectedCellX = 0.0f;
	float fSelectedCellY = 0.0f;

	std::chrono::time_point<std::chrono::system_clock> m_StartTime, m_CurrentTime;

	float fChangeTime = 0.0f;

	float fStartDistance = 0.0f;
	float fCurrentDistance = 0.0f;
	float fChangeDistance = 0.0f;
	float fLastDistance = 0.0f;
	float fMinDistance = 3.0f;


public:
	bool OnUserCreate() override
	{
		//NOTE: To access the features with your phone device use:
#if defined(__ANDROID__)
		// Access android directly 
		//android_app* pMyAndroid = this->pOsEngine.app;

#endif

#if defined(__APPLE__)
		// Access iOS directly
		//apple_app* pMyApple = this->pOsEngine.app;
#endif

		sprTouchTester = new olc::Sprite("images/north_south_east_west_logo.png");
		decTouchTester = new olc::Decal(sprTouchTester);


		// Initialise offset so 0,0 in world space is middle of the screen
		fOffsetX = -ScreenWidth() / 2;
		fOffsetY = -ScreenHeight() / 2;

		return true;
	}

	// Convert coordinates from World Space --> Screen Space
	void WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY)
	{
		nScreenX = (int)((fWorldX - fOffsetX) * fScaleX);
		nScreenY = (int)((fWorldY - fOffsetY) * fScaleY);
	}

	// Convert coordinates from Screen Space --> World Space
	void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY)
	{
		fWorldX = ((float)nScreenX / fScaleX) + fOffsetX;
		fWorldY = ((float)nScreenY / fScaleY) + fOffsetY;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		SetDrawTarget(nullptr);
		Clear(olc::BLUE);
		SetDefaultMessages();
		SetTouchMessages();

		// Just grab a copy of mouse coordinates for convenience
		float fMouseX = (float)GetTouchX(1);
		float fMouseY = (float)GetTouchY(1);

		// One we release touch point 1 the OS will tottle Touch Point 1 to 0
		// There we restart
		if (GetTouch().bReleased && GetTouch(1).bPressed) return true;

		// For panning, we need to capture the screen location when the user starts
		// to pan...
		if (GetTouch(1).bPressed && GetTouch().bHeld)
		{
			fStartPanX = fMouseX;
			fStartPanY = fMouseY;

			// Let get out zoom params ready
			m_StartTime = std::chrono::system_clock::now();
			m_CurrentTime = m_StartTime;
			fStartDistance = GetDistanceBetweenPoints(GetTouchPos(), GetTouchPos(1));
			fCurrentDistance = fStartDistance;
			fChangeDistance = 0.0f;
			fLastDistance = 0.0f;


		}

		// ...as the mouse moves, the screen location changes. Convert this screen
		// coordinate change into world coordinates to implement the pan. Simples.
		if (GetTouch().bHeld && GetTouch(1).bHeld)
		{
			fOffsetX -= (fMouseX - fStartPanX) / fScaleX;
			fOffsetY -= (fMouseY - fStartPanY) / fScaleY;

			// Start "new" pan for next epoch
			fStartPanX = fMouseX;
			fStartPanY = fMouseY;

			// Lets calcutate the zoom factor

			// Get the time changed
			m_CurrentTime = std::chrono::system_clock::now();
			std::chrono::duration<float> fduration = m_CurrentTime - m_StartTime;

			float fdurationTime = fduration.count();

			// Get the current distance
			fCurrentDistance = GetDistanceBetweenPoints(GetTouchPos(), GetTouchPos(1));

			// Get the change in distance
			fChangeDistance = fCurrentDistance - fStartDistance;

			// Check if we have met the min distance, and some time has passed
			if (std::abs(fChangeDistance) >= fMinDistance && fdurationTime > 0)
			{
				// Now we need to check if we are zooming in or out
				if (fChangeDistance > fLastDistance)
				{
					// Zooming out
					fScaleX *= (0.999f - fElapsedTime);
					fScaleY *= (0.999f - fElapsedTime);

				}
				if (fChangeDistance < fLastDistance)
				{
					fScaleX *= (1.001f + fElapsedTime);
					fScaleY *= (1.001f + fElapsedTime);
				}

			}

			fLastDistance = fChangeDistance;

		}

		// For zoom, we need to extract the location of the cursor before and after the
		// scale is changed. Here we get the cursor and translate into world space...
		float fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom;
		ScreenToWorld(fMouseX, fMouseY, fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom);


		// ...change the scale as required...
		if (GetKey(olc::Key::Q).bHeld)
		{
			fScaleX *= 1.001f;
			fScaleY *= 1.001f;
		}

		if (GetKey(olc::Key::A).bHeld)
		{
			fScaleX *= 0.999f;
			fScaleY *= 0.999f;
		}

		// ...now get the location of the cursor in world space again - It will have changed
		// because the scale has changed, but we can offset our world now to fix the zoom
		// location in screen space, because we know how much it changed laterally between
		// the two spatial scales. Neat huh? ;-)
		float fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom;
		ScreenToWorld(fMouseX, fMouseY, fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom);
		fOffsetX += (fMouseWorldX_BeforeZoom - fMouseWorldX_AfterZoom);
		fOffsetY += (fMouseWorldY_BeforeZoom - fMouseWorldY_AfterZoom);

		// Clip
		float fWorldLeft, fWorldTop, fWorldRight, fWorldBottom;
		ScreenToWorld(0, 0, fWorldLeft, fWorldTop);
		ScreenToWorld(ScreenWidth(), ScreenHeight(), fWorldRight, fWorldBottom);

		auto function = [](float x)
		{
			return sinf(x);
		};


		// Draw Main Axes a 10x10 Unit Grid
		// Draw 10 horizontal lines
		int nLinesDrawn = 0;
		for (float y = 0.0f; y <= 10.0f; y++)
		{
			if (y >= fWorldTop && y <= fWorldBottom)
			{
				float sx = 0.0f, sy = y;
				float ex = 10.0f, ey = y;

				int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

				WorldToScreen(sx, sy, pixel_sx, pixel_sy);
				WorldToScreen(ex, ey, pixel_ex, pixel_ey);

				DrawLine(pixel_sx, pixel_sy, pixel_ex, pixel_ey, olc::WHITE);
				nLinesDrawn++;
			}
		}

		// Draw 10 vertical lines
		for (float x = 0.0f; x <= 10.0f; x++)
		{
			if (x >= fWorldLeft && x <= fWorldRight)
			{
				float sx = x, sy = 0.0f;
				float ex = x, ey = 10.0f;

				int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

				WorldToScreen(sx, sy, pixel_sx, pixel_sy);
				WorldToScreen(ex, ey, pixel_ex, pixel_ey);

				DrawLine(pixel_sx, pixel_sy, pixel_ex, pixel_ey, olc::WHITE);
				nLinesDrawn++;
			}
		}

		// Draw selected cell

		// We can easily determine where the mouse is in world space. In fact we already
		// have this frame so just reuse the values
		if (GetTouch(1).bReleased)
		{
			fSelectedCellX = (int)fMouseWorldX_AfterZoom;
			fSelectedCellY = (int)fMouseWorldY_AfterZoom;
		}

		// Draw selected cell by filling with red circle. Convert cell coords
		// into screen space, also scale the radius
		int cx, cy, cr;
		WorldToScreen(fSelectedCellX + 0.5f, fSelectedCellY + 0.5f, cx, cy);
		cr = 0.3f * fScaleX;
		FillCircle(cx, cy, cr, olc::RED);
		DrawString(2, 2, "Lines Drawn: " + std::to_string(nLinesDrawn));


		// Draw Chart
		float fWorldPerScreenWidthPixel = (fWorldRight - fWorldLeft) / ScreenWidth();
		float fWorldPerScreenHeightPixel = (fWorldBottom - fWorldTop) / ScreenHeight();
		int px, py, opx = 0, opy = 0;
		WorldToScreen(fWorldLeft - fWorldPerScreenWidthPixel, -function((fWorldLeft - fWorldPerScreenWidthPixel) - 5.0f) + 5.0f, opx, opy);
		for (float x = fWorldLeft; x < fWorldRight; x += fWorldPerScreenWidthPixel)
		{
			float y = -function(x - 5.0f) + 5.0f;
			WorldToScreen(x, y, px, py);
			DrawLine(opx, opy, px, py, olc::GREEN);
			opx = px;
			opy = py;
		}


		DisplayMessages();
		return true;
	}

	float GetDistanceBetweenPoints(olc::vi2d vPos1, olc::vi2d vPos2)
	{
		return GetDistanceBetweenPoints(vPos1.x, vPos1.y, vPos2.x, vPos2.y);
	}

	float GetDistanceBetweenPoints(float x1, float y1, float x2, float y2)
	{
		return std::sqrtf(std::powf((x2 - x1), 2) + std::powf((y2 - y1), 2));
	}

	olc::vi2d GetCenterPoint(olc::vi2d vPos1, olc::vi2d vPos2)
	{
		return GetCenterPoint(vPos1.x, vPos1.y, vPos2.x, vPos2.y);
	}

	olc::vi2d GetCenterPoint(int x1, int y1, int x2, int y2)
	{
		olc::vi2d cPoint;
		cPoint.x = (x1 + x2) / 2;
		cPoint.y = (y1 + y2) / 2;
		return cPoint;
	}

	float GetAngleDegress(int x1, int y1, int x2, int y2)
	{
		float angleRadians = GetAngleRadians(x1, y1, x2, y2);
		return angleRadians * 180 / 3.14159f;
	}

	float GetAngleRadians(int x1, int y1, int x2, int y2)
	{
		float deltaY = float(y2 - y1);
		float deltaX = float(x2 - x1);

		return atan2f(deltaY, deltaX);
	}

	float GetAngleDegressXYZ(olc::vi2d vPosX, olc::vi2d vPosY, olc::vi2d vPosZ)
	{
		float alpha = GetAngleRadiansXYZ(vPosX, vPosY, vPosZ);
		return (alpha * 180. / 3.14159f + 0.5f);
	}

	float GetAngleRadiansXYZ(olc::vi2d vPosX, olc::vi2d vPosY, olc::vi2d vPosZ)
	{
		olc::vi2d xy = { vPosY.x - vPosX.x, vPosY.y - vPosX.y };
		olc::vi2d zy = { vPosY.x - vPosZ.x, vPosY.y - vPosZ.y };

		float dot = (xy.x * zy.x + xy.y * zy.y); // dot product
		float cross = (xy.x * zy.y - xy.y * zy.x); // cross product

		return			atan2(cross, dot);

	}

	void SetDefaultMessages()
	{
		nFrameCount = GetFPS();

		std::string sLineBreak = "-------------------------";

		std::string sTitle = "OneLoneCoder.com";
		vecMessages.push_back(sTitle);

		std::string sPGEMobile = "PGE Mobile Pre-Release 2.2.0";
		vecMessages.push_back(sPGEMobile);

		std::string sFps = sAppName + " - FPS: " + std::to_string(nFrameCount);
		vecMessages.push_back(sFps);

		vecMessages.push_back(sLineBreak);
	}

	void SetTouchMessages()
	{
		std::string sTouchScreen = "Touch the screen";
		vecMessages.push_back(sTouchScreen);

		olc::vi2d defautTouchPos = GetTouchPos();
		std::string defautTouch = "Touch 1:  X: " + std::to_string(defautTouchPos.x) + " Y: " + std::to_string(defautTouchPos.y);
		vecMessages.push_back(defautTouch);

		if (GetTouch().bHeld)
		{
			DrawTargetPointer(defautTouchPos, 50, 10, olc::YELLOW);
		}

		if (GetTouch().bHeld && GetTouch(1).bHeld)
		{
			DrawLine(GetTouchPos(), GetTouchPos(1), olc::YELLOW, 0xF0F0F0F0);
			DrawTargetPointer(GetTouchPos(1), 50, 10, olc::WHITE);
			defautTouch = "Touch 1:  X: " + std::to_string(GetTouchPos(1).x) + " Y: " + std::to_string(GetTouchPos(1).y);
			vecMessages.push_back(defautTouch);
		}



	}

	void DisplayMessages()
	{
		nStep = 10;
		for (auto& s : vecMessages)
		{
			DrawString(20, nStep, s);
			nStep += 10;
		}
		vecMessages.clear();
	}

	bool OnUserDestroy() override
	{
		return true;
	}

	void OnSaveStateRequested() override
	{
		// Fires when the OS is about to put your game into pause mode
		// You have, at best 30 Seconds before your game will be fully shutdown
		// It depends on why the OS is pausing your game tho, Phone call, etc
		// It is best to save a simple Struct of your settings, i.e. current level, player position etc
		// NOTE: The OS can terminate all of your data, pointers, sprites, layers can be freed
		// Therefore do not save sprites, pointers etc 

		// Example 1: vector
		vecLastState.clear();
		vecLastState.push_back({ "MouseX", 55 });
		vecLastState.push_back({ "MouseY", 25 });
		vecLastState.push_back({ "GameLevel", 5 });

		// Example 2 with a file:
#if defined(__ANDROID__)

		android_app* pMyAndroid = this->pOsEngine.app;
		ANativeActivity* nativeActivity = pMyAndroid->activity;
		const char* internalPath = nativeActivity->internalDataPath;
		std::string dataPath(internalPath);

		// internalDataPath points directly to the files/ directory                                  
		std::string lastStateFile = dataPath + "/lastStateFile.bin";

		std::ofstream file(lastStateFile, std::ios::out | std::ios::binary);

		if (file)
		{
			float fVecSize = vecLastState.size();
			file.write((char*)&fVecSize, sizeof(long));
			for (auto& vSS : vecLastState)
			{
				file.write((char*)&vSS, sizeof(MySaveState));
			}

			file.close();
		}

#endif

#if defined(__APPLE__)
		// Coming soon
		//apple_app* pMyApple = this->pOsEngine.app;
#endif

	}

	void OnRestoreStateRequested() override
	{
		// This will fire every time your game launches 
		// OnUserCreate will be fired again as the OS may have terminated all your data

#if defined(__ANDROID__)

		android_app* pMyAndroid = this->pOsEngine.app;
		ANativeActivity* nativeActivity = pMyAndroid->activity;

		// internalDataPath points directly to the files/ directory          
		const char* internalPath = nativeActivity->internalDataPath;
		std::string dataPath(internalPath);
		std::string lastStateFile = dataPath + "/lastStateFile.bin";

		vecLastState.clear();

		std::ifstream file(lastStateFile, std::ios::in | std::ios::binary);

		MySaveState saveState;

		if (file)
		{
			float fVecSize;
			file.read((char*)&fVecSize, sizeof(long));
			for (long i = 0; i < fVecSize; i++)
			{
				file.read((char*)&saveState, sizeof(MySaveState));
				vecLastState.push_back(saveState);
			}

			file.close();
			// Note this is a temp file, we must delete it
			std::remove(lastStateFile.c_str());

		}


#endif

#if defined(__APPLE__)
		// Coming soon
		//apple_app* pMyApple = this->pOsEngine.app;
#endif

	}
};


/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
* This is now what drives the engine, the thread is controlled from the OS
*/
void android_main(struct android_app* initialstate) {

	/*
		initalstate allows you to make some more edits
		to your app before the PGE Engine starts
		Recommended just to leave it at its defaults
		but change it at your own risk
		to access the Android/iOS directly in your code
		android_app* pMyAndroid = this->pOsEngine.app;;

	*/

	PGE_Mobile demo;

	/*
		Note it is best to use HD(1280, 720, ? X ? pixel, Fullscreen = true) the engine can scale this best for all screen sizes,
		without affecting performance... well it will have a very small affect, it will depend on your pixel size
		Note: cohesion is currently not working
	*/
	demo.Construct(1280, 720, 2, 2, true, false, false);

	demo.Start(); // Lets get the party started


}


