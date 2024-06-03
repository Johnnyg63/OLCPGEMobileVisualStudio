
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.6,                      //
// John Galvin aka Johnngy63: 03-Jun-2024                       //
// iOS Sensor NOT supported, coming soon                        //
// Asteroids Demo                                               //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////


/*
OneLoneCoder.com - Code-It-Yourself! Asteroids at the command prompt (quick and simple c++)
"This one just kept growing..." - @Javidx9

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
I needed a quick video to keep up with my upload schedule, and thought "oh asteroids
must be simple", and indeed it was, but it was a bit rubbish, and didn't really
offer anything educational, until I made the decision to ditch sprites and use
vector models like the original game. This made the game considerably more sophisticated,
has opened up new possibilities for the game engine, and just goes to show, jus 'cos
it's old, doesn't mean it's irrelevant.

I ended up with a demonstration of physics, wireframe graphics, 2D matrix transformations,
toroidal space mapping and vector manipulation.

Controls
~~~~~~~~
Left and Right arrow keys steer the ship. Up arrow is thrust. There is no reverse thrust.
Space bar fires bullets. Get the highest score by surviving waves of asteroids.

Author
~~~~~~
Twitter: @javidx9
Blog: www.onelonecoder.com
YouTube: www.youtube.com/javidx9

Video:
~~~~~~
https://youtu.be/QgDR8LrRZhk

Last Updated: 30/08/2017
*/


/* Addition Joseph21 - 20220715
 *   - removed "using namespace std" and added explicit scope resolution operator where needed
 */


#include <iostream>
#include <string>
#include <algorithm>
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
		sAppName = "Asteroids Demo";
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

	struct sSpaceObject
	{
		int nSize;
		float x;
		float y;
		float dx;
		float dy;
		float angle;
	};

	std::vector<sSpaceObject> vecAsteroids;
	std::vector<sSpaceObject> vecBullets;
	sSpaceObject player;
	bool bDead = false;
	int nScore = 0;

	float nCount = 0.0f;

	float fSelectedAngle = 0.0f;

	std::vector<std::pair<float, float>> vecModelShip;
	std::vector<std::pair<float, float>> vecModelAsteroid;



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

		vecModelShip =
		{
			{ 0.0f, -5.0f},
			{-2.5f, +2.5f},
			{+2.5f, +2.5f}
		}; // A simple Isoceles Triangle

		// Create a "jagged" circle for the asteroid. It's important it remains
		// mostly circular, as we do a simple collision check against a perfect
		// circle.
		int verts = 20;
		for (int i = 0; i < verts; i++)
		{
			float noise = (float)rand() / (float)RAND_MAX * 0.4f + 0.8f;
			vecModelAsteroid.push_back(std::make_pair(noise * sinf(((float)i / (float)verts) * 6.28318f),
				noise * cosf(((float)i / (float)verts) * 6.28318f)));
		}

		ResetGame();

		return true;
	}

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
		//FillTriangle(vCenterPoint, { vCenterPoint.x - 50, vCenterPoint.y + 50 }, { vCenterPoint.x + 50, vCenterPoint.y + 50 }, p);
		FillCircle(vCenterPoint, nCircleRadus, p);
		DrawLine(vCenterPoint, { vCenterPoint.x, vCenterPoint.y + nLineLenght }, p);
		DrawLine(vCenterPoint, { vCenterPoint.x, vCenterPoint.y - nLineLenght }, p);
		DrawLine(vCenterPoint, { vCenterPoint.x + nLineLenght, vCenterPoint.y }, p);
		DrawLine(vCenterPoint, { vCenterPoint.x - nLineLenght, vCenterPoint.y }, p);

	}


	void ResetGame()
	{
		// Initialise Player Position
		player.x = ScreenWidth() / 2.0f;
		player.y = ScreenHeight() / 2.0f;
		player.dx = 0.0f;
		player.dy = 0.0f;
		player.angle = 0.0f;

		vecBullets.clear();
		vecAsteroids.clear();

		// Put in two asteroids
		vecAsteroids.push_back({ (int)16, 20.0f, 20.0f, 8.0f, -6.0f, 0.0f });
		vecAsteroids.push_back({ (int)16, 100.0f, 20.0f, -5.0f, 3.0f, 0.0f });

		// Reset game
		bDead = false;
		nScore = false;
	}

	// Implements "wrap around" for various in-game systems
	void WrapCoordinates(float ix, float iy, float& ox, float& oy)
	{
		ox = ix;
		oy = iy;
		if (ix < 0.0f)	ox = ix + (float)ScreenWidth();
		if (ix >= (float)ScreenWidth())	ox = ix - (float)ScreenWidth();
		if (iy < 0.0f)	oy = iy + (float)ScreenHeight();
		if (iy >= (float)ScreenHeight()) oy = iy - (float)ScreenHeight();
	}

	// Overridden to handle toroidal drawing routines
	virtual bool Draw(int x, int y, olc::Pixel col = olc::WHITE)
	{
		float fx, fy;
		WrapCoordinates(x, y, fx, fy);
		olc::PixelGameEngine::Draw(fx, fy, col);
		return true;
	}

	bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y)
	{
		return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
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

		if (bDead)
			ResetGame();

		// Clear Screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		// Steer Ship
		if (GetKey(olc::Key::LEFT).bHeld)
			player.angle -= 5.0f * fElapsedTime;
		if (GetKey(olc::Key::RIGHT).bHeld)
			player.angle += 5.0f * fElapsedTime;



		// VELOCITY changes POSITION (with respect to time)
		player.x += player.dx * fElapsedTime;
		player.y += player.dy * fElapsedTime;

		// Keep ship in game space
		WrapCoordinates(player.x, player.y, player.x, player.y);

		// Create a vector to the mouse/touch point
		olc::vi2d pointPos = { 0,0 };
		olc::vi2d playerPos = { (int)player.x, (int)player.y };

		if (GetTouch().bHeld) pointPos = GetTouchPos();
		if (GetMouse(0).bHeld) pointPos = GetMousePos();
		if (GetTouch().bHeld || GetMouse(0).bHeld)
		{
			/*DrawLine(playerPos, pointPos, olc::GREEN, 0xF0F0F0F0);
			DrawTargetPointer(pointPos, 20, 5, olc::GREEN);*/

			// Thrust? Apply ACCELERATION
			// ACCELERATION changes VELOCITY (with respect to time)
			player.dx += sin(player.angle) * 20.0f * fElapsedTime;
			player.dy += -cos(player.angle) * 20.0f * fElapsedTime;

			fSelectedAngle = get_angleRadians_2points(playerPos.x, playerPos.y, pointPos.x, pointPos.y);

			player.angle = fSelectedAngle;

		}


		// Check ship collision with asteroids
		for (auto& a : vecAsteroids)
			if (IsPointInsideCircle(a.x, a.y, a.nSize, player.x, player.y))
				bDead = true; // Uh oh...

		// Fire Bullet in direction of player
		if (GetTouch().bPressed || GetMouse(0).bPressed)
		{
			vecBullets.push_back({ 0, player.x, player.y, 50.0f * sinf(player.angle), -50.0f * cosf(player.angle), 100.0f });
		}


		// Update and draw asteroids
		for (auto& a : vecAsteroids)
		{
			// VELOCITY changes POSITION (with respect to time)
			a.x += a.dx * fElapsedTime;
			a.y += a.dy * fElapsedTime;
			a.angle += 0.5f * fElapsedTime; // Add swanky rotation :)

			// Asteroid coordinates are kept in game space (toroidal mapping)
			WrapCoordinates(a.x, a.y, a.x, a.y);

			// Draw Asteroids
			DrawWireFrameModel(vecModelAsteroid, a.x, a.y, a.angle, (float)a.nSize, olc::YELLOW);
		}

		// Any new asteroids created after collision detection are stored
		// in a temporary vector, so we don't interfere with the asteroids
		// vector iterator in the for(auto)
		std::vector<sSpaceObject> newAsteroids;

		// Update Bullets
		for (auto& b : vecBullets)
		{
			b.x += b.dx * fElapsedTime;
			b.y += b.dy * fElapsedTime;
			WrapCoordinates(b.x, b.y, b.x, b.y);
			b.angle -= 1.0f * fElapsedTime;

			// Check collision with asteroids
			for (auto& a : vecAsteroids)
			{
				//if (IsPointInsideRectangle(a.x, a.y, a.x + a.nSize, a.y + a.nSize, b.x, b.y))
				if (IsPointInsideCircle(a.x, a.y, a.nSize, b.x, b.y))
				{
					// Asteroid Hit - Remove bullet
					// We've already updated the bullets, so force bullet to be offscreen
					// so it is cleaned up by the removal algorithm.
					b.x = -100;

					// Create child asteroids
					if (a.nSize > 4)
					{
						float angle1 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
						float angle2 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
						newAsteroids.push_back({ (int)a.nSize >> 1 ,a.x, a.y, 10.0f * sinf(angle1), 10.0f * cosf(angle1), 0.0f });
						newAsteroids.push_back({ (int)a.nSize >> 1 ,a.x, a.y, 10.0f * sinf(angle2), 10.0f * cosf(angle2), 0.0f });
					}

					// Remove asteroid - Same approach as bullets
					a.x = -100;
					nScore += 100; // Small score increase for hitting asteroid
				}
			}
		}

		// Append new asteroids to existing vector
		for (auto a : newAsteroids)
			vecAsteroids.push_back(a);

		// Clear up dead objects - They are out of game space

		// Remove asteroids that have been blown up
		if (vecAsteroids.size() > 0)
		{
			auto i = remove_if(vecAsteroids.begin(), vecAsteroids.end(), [&](sSpaceObject o) { return (o.x < 0); });
			if (i != vecAsteroids.end())
				vecAsteroids.erase(i);
		}

		if (vecAsteroids.empty()) // If no asteroids, level complete! :) - you win MORE asteroids!
		{
			// Level Clear
			nScore += 1000; // Large score for level progression
			vecAsteroids.clear();
			vecBullets.clear();

			// Add two new asteroids, but in a place where the player is not, we'll simply
			// add them 90 degrees left and right to the player, their coordinates will
			// be wrapped by the next asteroid update
			vecAsteroids.push_back({ (int)16, 30.0f * sinf(player.angle - 3.14159f / 2.0f) + player.x,
											  30.0f * cosf(player.angle - 3.14159f / 2.0f) + player.y,
											  10.0f * sinf(player.angle), 10.0f * cosf(player.angle), 0.0f });

			vecAsteroids.push_back({ (int)16, 30.0f * sinf(player.angle + 3.14159f / 2.0f) + player.x,
											  30.0f * cosf(player.angle + 3.14159f / 2.0f) + player.y,
											  10.0f * sinf(-player.angle), 10.0f * cosf(-player.angle), 0.0f });
		}

		// Remove bullets that have gone off screen
		if (vecBullets.size() > 0)
		{
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return (o.x < 1 || o.y < 1 || o.x >= ScreenWidth() - 1 || o.y >= ScreenHeight() - 1); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}

		// Draw Bullets
		for (auto b : vecBullets)
			Draw(b.x, b.y);

		// Draw Ship
		DrawWireFrameModel(vecModelShip, player.x, player.y, player.angle);

		// Draw Score
		std::string sScore = "SCORE: " + std::to_string(nScore);
		vecMessages.push_back(sScore);


		nStep = 10;
		for (auto& s : vecMessages)
		{
			DrawString(20, nStep, s);
			nStep += 10;
		}
		vecMessages.clear();

		return true;
	}

	void DrawWireFrameModel(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, olc::Pixel col = olc::WHITE)
	{
		// pair.first = x coordinate
		// pair.second = y coordinate

		// Create translated model vector of coordinate pairs
		std::vector<std::pair<float, float>> vecTransformedCoordinates;
		int verts = vecModelCoordinates.size();
		vecTransformedCoordinates.resize(verts);

		// Rotate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
			vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
		}

		// Scale
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
		}

		// Translate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++)
		{
			int j = (i + 1);
			DrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
				vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second, col);
		}
	}

	/// <summary>
	/// Takes 2 Window coords(points), turns them into vectors using the origin and calculates the angle around the xaxis between them.
	/// I couldn't explain it better, please see: https://stackoverflow.com/questions/2339487/calculate-angle-of-2-points
	/// </summary>
	/// <param name="p1x"></param>
	/// <param name="p1y"></param>
	/// <param name="p2x"></param>
	/// <param name="p2y"></param>
	/// <returns></returns>
	float get_angle_2points(int p1x, int p1y, int p2x, int p2y)
	{
		//Make point1 the origin, make point2 relative to the origin so we do point1 - point1, and point2-point1,
		//since we don't need point1 for the equation to work, the equation works correctly with the origin 0,0.
		int deltaY = p2y - p1y;
		int deltaX = p2x - p1x; //Vector 2 is now relative to origin, the angle is the same, we have just transformed it to use the origin.

		float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.141;

		angleInDegrees *= -1; // Y axis is inverted in computer windows, Y goes down, so invert the angle.

		//Angle returned as:
		//                      90
		//            135                45
		//
		//       180          Origin           0
		//
		//           -135                -45
		//
		//                     -90


		// returned angle can now be used in the c++ window function used in text angle alignment. ie plf->lfEscapement = angle*10;
		return angleInDegrees;
	}

	float get_angleRadians_2points(int p1x, int p1y, int p2x, int p2y)
	{
		//Make point1 the origin, make point2 relative to the origin so we do point1 - point1, and point2-point1,
		//since we don't need point1 for the equation to work, the equation works correctly with the origin 0,0.
		int deltaY = p2y - p1y;
		int deltaX = p2x - p1x; //Vector 2 is now relative to origin, the angle is the same, we have just transformed it to use the origin.

		float angleInRadians = atan2(deltaY, deltaX); // *180 / 3.141;
		angleInRadians += (3.14159f * 2) + (3.14159f / 2);
		return angleInRadians;
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


