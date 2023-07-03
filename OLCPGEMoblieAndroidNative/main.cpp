
//////////////////////////////////////////////////////////////////
// Beta Release 2.0.7, Not to be used for Production software  //
// John Galvin aka Johnngy63: 03-July-2023                      //
// Updated SIMD_SSE Support for Intel Atom
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

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
		sAppName = "OLC PGE Mobile BETA 2.0.7";
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

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		SetDrawTarget(nullptr);
		Clear(olc::BLUE);

		nFrameCount = GetFPS();

		std::string sLineBreak = "-------------------------";

		std::string sTitle = "OneLoneCoder.com";
		vecMessages.push_back(sTitle);

		std::string sPGEMobile = "Pixel Game Engine Mobile Beta 2.0.7";
		vecMessages.push_back(sPGEMobile);

		std::string sFps = sAppName + " - FPS: " + std::to_string(nFrameCount);
		vecMessages.push_back(sFps);

		std::string sTouchScreen = "Touch the screen";
		vecMessages.push_back(sTouchScreen);

		vecMessages.push_back(sLineBreak);

		olc::vi2d centreScreenPos = GetScreenSize();
		centreScreenPos.x = centreScreenPos.x / 2;
		centreScreenPos.y = centreScreenPos.y / 2;
		DrawTargetPointer(centreScreenPos, 50, 10);

		// Get the default touch point
		// This is alway Index 0 and first touch piont
		olc::vi2d defautTouchPos = GetTouch();
		std::string defautTouch = "Default Touch 0:  X: " + std::to_string(defautTouchPos.x) + " Y: " + std::to_string(defautTouchPos.y);
		vecMessages.push_back(defautTouch);

		if (GetMouse().bHeld)
		{
			DrawLine(centreScreenPos, defautTouchPos, olc::YELLOW, 0xF0F0F0F0);
			DrawTargetPointer(defautTouchPos, 50, 10, olc::YELLOW);
		}

		/*
			You asked for Multi-touch... you got it!
			You can support up to 126 touch points, however most phones and tablets can only handle 5

			As always with touch sensors it is an approxmaite and alway will be
			I would recommand no more that 3 points

			When you are using lots of touch points it is best to run ClearTouchPoints();
			every so often to ensure lost touch points are cleared

		*/
		
		olc::vi2d touchPos;
		// The more touch points the harder to manage
		for (int i = 1; i < 3; i++)
		{
			if (GetTouch(i).bHeld)
			{

				touchPos = GetTouchPos(i);
				std::string TouchID = "Touch ID: " + std::to_string(i) + " X: " + std::to_string(touchPos.x) + " Y: " + std::to_string(touchPos.y);
				vecMessages.push_back(TouchID);
				DrawLine(centreScreenPos, touchPos, olc::WHITE, 0xF0F0F0F0);
				DrawTargetPointer(touchPos, 50, 10);

			}
		}



		// Called once per frame, draws random coloured pixels
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));*/

		nStep = 10;
		for (auto& s : vecMessages)
		{
			DrawString(20, nStep, s);
			nStep += 10;
		}
		vecMessages.clear();

		return true;
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


