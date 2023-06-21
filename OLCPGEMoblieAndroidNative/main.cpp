
//////////////////////////////////////////////////////////////////
// Beta Release 2.0.5, Not to be used for Production software    //
// John Galvin aka Johnngy63: 21-June-2023
// Now with Sensor Support									    //
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
		sAppName = "OLC PGE Mobile BETA 2.0.5";
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

		// Eamples:
		vecSensorInfos = GetSupportedSensors();

		const char* name;
		const char* vendor;
		for (auto& sInfo : vecSensorInfos)
		{
			name = sInfo.Name;
			vendor = sInfo.Vendor;
		}


		olc::SensorInformation senAccInfo = GetSensorInfo(olc::ASENSOR_TYPE_ACCELEROMETER);

		olc::SensorInformation sHeartInfo2 = GetSensorInfo(olc::ASENSOR_TYPE_HEART_BEAT);

		EnableSensor(olc::ASENSOR_TYPE_ACCELEROMETER);
		EnableSensor(olc::ASENSOR_TYPE_MAGNETIC_FIELD);
		EnableSensor(olc::ASENSOR_TYPE_GYROSCOPE);
		EnableSensor(olc::ASENSOR_TYPE_GAME_ROTATION_VECTOR);
		EnableSensor(olc::ASENSOR_TYPE_ORIENTATION);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		SetDrawTarget(nullptr);
		Clear(olc::BLUE);

		olc::vi2d touchPos = GetTouchPos();
		olc::vi2d sprSize = decTouchTester->sprite->Size();

		touchPos.x = touchPos.x - (sprSize.x / 2);
		touchPos.y = touchPos.y - (sprSize.y / 2);

		if (GetTouch(0).bHeld)
		{
			DrawDecal(touchPos, decTouchTester);
		}

		nFrameCount = GetFPS();

		// Called once per frame, draws random coloured pixels
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));*/

		std::string sLineBreak = "-------------------------";

		std::string sTitle = "OneLoneCoder.com";
		vecMessages.push_back(sTitle);

		std::string sPGEMobile = "Pixel Game Engine Mobile Beta 2.0.4";
		vecMessages.push_back(sPGEMobile);

		std::string sFps = sAppName + " - FPS: " + std::to_string(nFrameCount);
		vecMessages.push_back(sFps);

		std::string sTouchScreen = "Touch the screen";
		vecMessages.push_back(sTouchScreen);

		std::string sTouchX = "Touch X: " + std::to_string(GetTouchX());
		vecMessages.push_back(sTouchX);

		std::string sTouchY = "Touch Y: " + std::to_string(GetTouchY());
		vecMessages.push_back(sTouchY);


		std::string sSensors = "--------Sensors!---------";
		vecMessages.push_back(sSensors);

		std::string sAccelerometerX = "Accelerometer X: " + std::to_string(SelectSensor.Accelerometer.x) + " m/s^2";
		vecMessages.push_back(sAccelerometerX);

		std::string sAccelerometerY = "Accelerometer Y: " + std::to_string(SelectSensor.Accelerometer.y) + " m/s^2";
		vecMessages.push_back(sAccelerometerY);

		std::string sAccelerometerZ = "Accelerometer Z: " + std::to_string(SelectSensor.Accelerometer.z) + " m/s^2";
		vecMessages.push_back(sAccelerometerZ);

		std::string sAccelerometerV = "Accelerometer V: " + std::to_string(SelectSensor.Accelerometer.v[0]) + " m/s^2";
		vecMessages.push_back(sAccelerometerV);

		vecMessages.push_back(sLineBreak);

		std::string sMagniticFieldX = "MagniticField X: " + std::to_string(SelectSensor.MagniticField.x) + " uT";
		vecMessages.push_back(sMagniticFieldX);

		std::string sMagniticFieldY = "MagniticField Y: " + std::to_string(SelectSensor.MagniticField.y) + " uT";
		vecMessages.push_back(sMagniticFieldY);

		std::string sMagniticFieldZ = "MagniticField Z: " + std::to_string(SelectSensor.MagniticField.z) + " uT";
		vecMessages.push_back(sMagniticFieldZ);

		std::string sMagniticFieldV = "MagniticField V: " + std::to_string(SelectSensor.MagniticField.v[0]) + " uT";
		vecMessages.push_back(sMagniticFieldV);

		vecMessages.push_back(sLineBreak);


		std::string sGyroscopeX = "Gyroscope X: " + std::to_string(SelectSensor.Gyroscope.x) + " rad/s";
		vecMessages.push_back(sGyroscopeX);

		std::string sGyroscopeY = "Gyroscope Y: " + std::to_string(SelectSensor.Gyroscope.y) + " rad/s";
		vecMessages.push_back(sGyroscopeY);

		std::string sGyroscopeZ = "Gyroscope Z: " + std::to_string(SelectSensor.Gyroscope.z) + " rad/s";
		vecMessages.push_back(sGyroscopeZ);

		std::string sGyroscopeV = "Gyroscope V: " + std::to_string(SelectSensor.Gyroscope.v[1]) + " rad/s";
		vecMessages.push_back(sGyroscopeV);

		vecMessages.push_back(sLineBreak);

		std::string sGameRototionX = "GameRototion X: " + std::to_string(SelectSensor.GameRotation.x);
		vecMessages.push_back(sGameRototionX);

		std::string sGameRototionY = "GameRototion Y: " + std::to_string(SelectSensor.GameRotation.y);
		vecMessages.push_back(sGameRototionY);

		std::string sGameRototionZ = "GameRototion Z: " + std::to_string(SelectSensor.GameRotation.z);
		vecMessages.push_back(sGameRototionZ);

		std::string sGameRototionV = "GameRototion V: " + std::to_string(SelectSensor.GameRotation.v[2]);
		vecMessages.push_back(sGameRototionV);

		vecMessages.push_back(sLineBreak);

		std::string sOrientationA = "Orientation Azimuth : " + std::to_string(SelectSensor.Orientation.azimuth) + " degress/s";
		vecMessages.push_back(sOrientationA);

		std::string sOrientationP = "Orientation Pitch   : " + std::to_string(SelectSensor.Orientation.pitch) + " degrees/s";
		vecMessages.push_back(sOrientationP);

		std::string sOrientationR = "Orientation Roll    : " + std::to_string(SelectSensor.Orientation.roll) + " degrees/s";
		vecMessages.push_back(sOrientationR);

		vecMessages.push_back(sLineBreak);


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


