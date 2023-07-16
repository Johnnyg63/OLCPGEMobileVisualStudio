
//////////////////////////////////////////////////////////////////
// Beta Release 2.0.8, Not to be used for Production software  //
// John Galvin aka Johnngy63: 08-July-2023                      //
// Circle v Rectangle Demo
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

#define OLC_PGEX_TRANSFORMEDVIEW
#include "olcPGEX_TransformedView.h"

class PGE_Mobile : public olc::PixelGameEngine
{

public:
	PGE_Mobile()
	{
		sAppName = "Circle V Rectangle";
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

private:
	olc::TileTransformedView tv;

	struct sWorldObject
	{
		olc::vf2d vPos;
		olc::vf2d vVel;
		float fRadius = 0.5f;
	};

	sWorldObject object;

	std::string sWorldMap =
		"################################"
		"#..............................#"
		"#.......#####.#.....#####......#"
		"#.......#...#.#.....#..........#"
		"#.......#...#.#.....#..........#"
		"#.......#####.#####.#####......#"
		"#..............................#"
		"#.....#####.#####.#####..##....#"
		"#.........#.#...#.....#.#.#....#"
		"#.....#####.#...#.#####...#....#"
		"#.....#.....#...#.#.......#....#"
		"#.....#####.#####.#####.#####..#"
		"#..............................#"
		"#..............................#"
		"#..#.#..........#....#.........#"
		"#..#.#..........#....#.........#"
		"#..#.#.......#####.#######.....#"
		"#..#.#..........#....#.........#"
		"#..#.#.............###.#.#.....#"
		"#..#.##########................#"
		"#..#..........#....#.#.#.#.....#"
		"#..#.####.###.#................#"
		"#..#.#......#.#................#"
		"#..#.#.####.#.#....###..###....#"
		"#..#.#......#.#....#......#....#"
		"#..#.########.#....#......#....#"
		"#..#..........#....#......#....#"
		"#..############....#......#....#"
		"#..................########....#"
		"#..............................#"
		"#..............................#"
		"################################";

	olc::vi2d vWorldSize = { 32, 32 };

	bool bFollowObject = false;

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

		// Create "Tiled World", where each tile is 32x32 screen pixels. Coordinates
		// for drawing will exist in unit-tile space from now on...
		tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 32, 32 });
		object.vPos = { 3.0f, 3.0f };

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

		std::string sPGEMobile = "Pixel Game Engine Mobile Beta 2.0.8";
		vecMessages.push_back(sPGEMobile);

		std::string sFps = sAppName + " - FPS: " + std::to_string(nFrameCount);
		vecMessages.push_back(sFps);

		vecMessages.push_back(sLineBreak);


		// Control of Player Object
		object.vVel = { 0.0f, 0.0f };
		if (GetKey(olc::Key::W).bHeld) object.vVel += { 0.0f, -1.0f };
		if (GetKey(olc::Key::S).bHeld) object.vVel += { 0.0f, +1.0f };
		if (GetKey(olc::Key::A).bHeld) object.vVel += { -1.0f, 0.0f };
		if (GetKey(olc::Key::D).bHeld) object.vVel += { +1.0f, 0.0f };

		if (object.vVel.mag2() > 0)
			object.vVel = object.vVel.norm() * (GetKey(olc::Key::SHIFT).bHeld ? 5.0f : 2.0f);

		if (GetKey(olc::Key::SPACE).bReleased) bFollowObject = !bFollowObject;


		// Where will object be worst case?
		olc::vf2d vPotentialPosition = object.vPos + object.vVel * fElapsedTime;

		// Extract region of world cells that could have collision this frame
		olc::vi2d vCurrentCell = object.vPos.floor();
		olc::vi2d vTargetCell = vPotentialPosition;
		olc::vi2d vAreaTL = (vCurrentCell.min(vTargetCell) - olc::vi2d(1, 1)).max({ 0,0 });
		olc::vi2d vAreaBR = (vCurrentCell.max(vTargetCell) + olc::vi2d(1, 1)).min(vWorldSize);

		olc::vf2d vRayToNearest;

		// Iterate through each cell in test area
		olc::vi2d vCell;
		for (vCell.y = vAreaTL.y; vCell.y <= vAreaBR.y; vCell.y++)
		{
			for (vCell.x = vAreaTL.x; vCell.x <= vAreaBR.x; vCell.x++)
			{
				// Check if the cell is actually solid...
				if (sWorldMap[vCell.y * vWorldSize.x + vCell.x] == '#')
				{
					// ...it is! So work out nearest point to future player position, around perimeter
					// of cell rectangle. We can test the distance to this point to see if we have
					// collided. 

					olc::vf2d vNearestPoint;
					vNearestPoint.x = std::max(float(vCell.x), std::min(vPotentialPosition.x, float(vCell.x + 1)));
					vNearestPoint.y = std::max(float(vCell.y), std::min(vPotentialPosition.y, float(vCell.y + 1)));

					olc::vf2d vRayToNearest = vNearestPoint - vPotentialPosition;
					float fOverlap = object.fRadius - vRayToNearest.mag();
					if (std::isnan(fOverlap)) fOverlap = 0;

					// If overlap is positive, then a collision has occurred, so we displace backwards by the 
					// overlap amount. The potential position is then tested against other tiles in the area
					// therefore "statically" resolving the collision
					if (fOverlap > 0)
					{
						// Statically resolve the collision
						vPotentialPosition = vPotentialPosition - vRayToNearest.norm() * fOverlap;
					}
				}
			}
		}

		// Set the objects new position to the allowed potential position
		object.vPos = vPotentialPosition;


		// Clear World
		Clear(olc::VERY_DARK_BLUE);

		if (bFollowObject)
		{
			tv.SetWorldOffset(object.vPos - tv.ScaleToWorld(olc::vf2d(ScreenWidth() / 2.0f, ScreenHeight() / 2.0f)));
			DrawString({ 10,10 }, "Following Object");
		}

		// Handle Pan & Zoom
		/*if (GetMouse(2).bPressed) tv.StartPan(GetMousePos());
		if (GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
		if (GetMouse(2).bReleased) tv.EndPan(GetMousePos());
		if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(2.0f, GetMousePos());
		if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.5f, GetMousePos());*/

		tv.HandlePanAndZoom(2, 10.0f * fElapsedTime, true, true);

		//********* REPLACE CODE -->
		// Handle Pan touch controls
		//if (GetTouch().bReleased && GetTouch(1).bPressed) return true; // Edge case, stops the screen from jumping	
		//if (GetTouch().bHeld && GetTouch(1).bPressed) tv.StartPan(GetTouchPos());
		//if (GetTouch().bHeld && GetTouch(1).bHeld) tv.UpdatePan(GetTouchPos());
		//if (GetTouch().bReleased || GetTouch(1).bReleased) tv.EndPan();

		// As zooming requires a little maths this is now intergrated to olcPGE_TransformView.h
		// You just need to enable it
		//tv.SetTouchMinDistance(30.0f); // you need to play with this
		//tv.HandlePanAndZoomTouch(0.1f, false, true);
		//<-- END REPLACE CODE

		// finall you can replace all the above code from REPLACE CODE --> to <-- END REPLACE CODE with
		tv.SetTouchMinDistance(30.0f); // This should be in the OnUserCreate, but it is handly here so you can adjust as needed
		tv.HandlePanAndZoomTouch(10.0f * fElapsedTime, true, true);


		// Draw World
		olc::vi2d vTL = tv.GetTopLeftTile().max({ 0,0 });
		olc::vi2d vBR = tv.GetBottomRightTile().min(vWorldSize);
		olc::vi2d vTile;
		for (vTile.y = vTL.y; vTile.y < vBR.y; vTile.y++)
			for (vTile.x = vTL.x; vTile.x < vBR.x; vTile.x++)
			{
				if (sWorldMap[vTile.y * vWorldSize.x + vTile.x] == '#')
				{
					tv.DrawRect(vTile, { 1.0f, 1.0f }, olc::WHITE);
					tv.DrawLine(vTile, vTile + olc::vf2d(1.0f, 1.0f), olc::WHITE);
					tv.DrawLine(vTile + olc::vf2d(0.0f, 1.0f), vTile + olc::vf2d(1.0f, 0.0f), olc::WHITE);
				}
			}

		tv.FillRectDecal(vAreaTL, vAreaBR - vAreaTL + olc::vi2d(1, 1), olc::Pixel(0, 255, 255, 32));

		// Draw Boundary
		tv.DrawCircle(object.vPos, object.fRadius, olc::WHITE);

		// Draw Velocity
		if (object.vVel.mag2() > 0)
		{
			tv.DrawLine(object.vPos, object.vPos + object.vVel.norm() * object.fRadius, olc::MAGENTA);
		}

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
	demo.Construct(1280, 720, 4, 4, true, false, false);

	demo.Start(); // Lets get the party started


}


