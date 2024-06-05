
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile All In One Release 2.2.7,           //
// John Galvin aka Johnngy63: 03-Jun-2024                       //
// iOS Sensor NOT supported, coming soon                        //
// 3D Example                                                   //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63                   //
// Thank you to @YouGotJoshed                                   //
// Please check out: http://sig.projectdivar.com/sigonasr2/     //
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
#define OLC_PGEX_GRAPHICS3D
#include "olcPGEX_Graphics3D.h"

#include <fstream> // Used for saving the savestate to a file



class PGE_Mobile : public olc::PixelGameEngine
{
public:

	olc::GFX3D::mesh cube;
	olc::GFX3D::PipeLine renderer;

	olc::GFX3D::vec3d vUp = { 0,1,0 };
	olc::GFX3D::vec3d vEye = { 0,0,-4 };
	olc::GFX3D::vec3d vLookDir = { 0,0,1 };

	float fTheta = 0;

	olc::Sprite* cubeTex;



public:
	PGE_Mobile()
	{
		sAppName = "Graphics3D PGEX Demo";
	}

	/* Vectors */
	std::vector<std::string> vecMessages;
	/* END Vectors*/

	int nFrameCount = 0;
	int nStep = 20;


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

		cube.LoadOBJFile("objectfiles/unitcube.obj");
		//cube.LoadOBJFile("/unitcube.obj", olc::FileHandler::INTERNAL);
		olc::GFX3D::ConfigureDisplay();

		cubeTex = new olc::Sprite("images/dirtblock.png");


		renderer.SetProjection(90.0f, (float)ScreenHeight() / (float)ScreenWidth(), 0.1f, 1000.0f, 0.0f, 0.0f, ScreenWidth(), ScreenHeight());

		std::string sAssetFile = "images/car_top.png";
		std::string sStorageFoler(app_GetPublicAppStorage()); /* Store it in --YOURPHONE--/Phone/Android/obb/com.olcPEGMob3DGraphicTest */
		std::string sStorageFile = sStorageFoler + "/car_top.png";

		if (app_ExtractFileFromAssets(sAssetFile, sStorageFile) == olc::rcode::OK)
		{
			// Test point
			int testPoint = 1;
		}

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

		std::string sPGEMobile = "PGE Mobile 2.2.2";
		vecMessages.push_back(sPGEMobile);

		std::string sFps = sAppName + " - FPS: " + std::to_string(nFrameCount);
		vecMessages.push_back(sFps);

		std::string sThankYou = "Thank to @YouGotJoshed for you help";
		vecMessages.push_back(sThankYou);

		sThankYou = "Please Check out: http://sig.projectdivar.com/sigonasr2/";
		vecMessages.push_back(sThankYou);

		vecMessages.push_back(sLineBreak);

		fTheta += fElapsedTime;

		Clear(olc::VERY_DARK_BLUE);

		olc::GFX3D::ClearDepth();

		olc::GFX3D::vec3d vLookTarget = olc::GFX3D::Math::Vec_Add(vEye, vLookDir);

		renderer.SetCamera(vEye, vLookTarget, vUp);

		olc::GFX3D::mat4x4 matRotateX = olc::GFX3D::Math::Mat_MakeRotationX(fTheta);
		olc::GFX3D::mat4x4 matRotateZ = olc::GFX3D::Math::Mat_MakeRotationZ(fTheta / 3.0f);
		olc::GFX3D::mat4x4 matWorld = olc::GFX3D::Math::Mat_MultiplyMatrix(matRotateX, matRotateZ);

		renderer.SetTransform(matWorld);

		renderer.SetTexture(cubeTex);
		//renderer.Render(cube.tris, GFX3D::RENDER_WIRE);

		renderer.Render(cube.tris);



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

		const char* internalPath = app_GetInternalAppStorage();
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


	}

	void OnRestoreStateRequested() override
	{
		// This will fire every time your game launches 
		// OnUserCreate will be fired again as the OS may have terminated all your data

		const char* internalPath = app_GetInternalAppStorage();
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
	demo.Construct(1280, 720, 4, 4, true, false, false);

	demo.Start(); // Lets get the party started


}


