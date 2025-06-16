
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile All In One Release 2.2.9            //
// John Galvin aka Johnngy63: 16-Jun-2025                       //
// Now with 3D Lightweight support, iOS Sensor NOT supported    //
// Quick GUI Demo                                               //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

/*
	Example file for olcPGEX_QuickGUI.h

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2022 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com

	Author
	~~~~~~
	David Barr, aka javidx9, �OneLoneCoder 2019, 2020, 2021, 2022

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

// PGEX Require the presence of olc::PixelGameEngine
#define OLC_PGEX_QUICKGUI
#include "olcPGEX_QuickGUI.h"

class PGE_Mobile : public olc::PixelGameEngine
{

public:
	PGE_Mobile()
	{
		sAppName = "Quick GUI Demo";
	}

	/* Vectors */
	std::vector<std::string> vecMessages;
	/* END Vectors*/

	int nFrameCount = 0;
	int nStep = 20;

protected:
	olc::QuickGUI::Manager guiManager;

	olc::QuickGUI::Slider* guiSlider1 = nullptr;
	olc::QuickGUI::Slider* guiSlider2 = nullptr;
	olc::QuickGUI::Slider* guiSlider3 = nullptr;

	olc::QuickGUI::Button* guiButton1 = nullptr;
	olc::QuickGUI::Button* guiButton2 = nullptr;
	olc::QuickGUI::Button* guiButton3 = nullptr;

	olc::QuickGUI::Slider* guiThemeColourR = nullptr;
	olc::QuickGUI::Slider* guiThemeColourG = nullptr;
	olc::QuickGUI::Slider* guiThemeColourB = nullptr;

	olc::QuickGUI::Label* guiLabelR = nullptr;
	olc::QuickGUI::Label* guiLabelG = nullptr;
	olc::QuickGUI::Label* guiLabelB = nullptr;

	olc::QuickGUI::CheckBox* guiCheckBox1 = nullptr;

	olc::QuickGUI::TextBox* guiTextBox1 = nullptr;
	olc::QuickGUI::TextBox* guiTextBox2 = nullptr;


	std::vector<std::string> listExample;
	olc::QuickGUI::ListBox* guiListBox = nullptr;


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

		// As we are using Android lets enable touch, this will disable Mouse input
		guiManager.EnableTouch();

		// NOTE: If you are using the Emulator set EnableTouch(false) to allow you to use the mouse
		// guiManager.EnableTouch(false);
#endif

#if defined(__APPLE__)
		// Access iOS directly
		//apple_app* pMyApple = this->pOsEngine.app;
#endif

// Horizontal Slider
		guiSlider1 = new olc::QuickGUI::Slider(guiManager,
			{ 30.0f, 10.0f }, { 246.0f, 10.0f }, 0, 100, 50);
		// Diagonal Slider!
		guiSlider2 = new olc::QuickGUI::Slider(guiManager,
			{ 20.0f, 20.0f }, { 120.0f, 120.0f }, 0, 100, 50);
		// Vertical Slider
		guiSlider3 = new olc::QuickGUI::Slider(guiManager,
			{ 10.0f, 30.0f }, { 10.0f, 230.0f }, 0, 100, 50);

		// Theme colour slider - Red
		guiThemeColourR = new olc::QuickGUI::Slider(guiManager,
			{ 150.0f, 30.0f }, { 246.0f, 30.0f }, 0, 255, 0);
		// Theme colour slider - Green
		guiThemeColourG = new olc::QuickGUI::Slider(guiManager,
			{ 150.0f, 50.0f }, { 246.0f, 50.0f }, 0, 255, 0);
		// Theme colour slider - Blue
		guiThemeColourB = new olc::QuickGUI::Slider(guiManager,
			{ 150.0f, 70.0f }, { 246.0f, 70.0f }, 0, 255, 128);

		// Labels for theme colour sliders
		guiLabelR = new olc::QuickGUI::Label(guiManager,
			"Red:", { 80.0f, 22.0f }, { 50.0f, 16.0f });
		guiLabelG = new olc::QuickGUI::Label(guiManager,
			"Green:", { 80.0f, 42.0f }, { 50.0f, 16.0f });
		guiLabelB = new olc::QuickGUI::Label(guiManager,
			"Blue:", { 80.0f, 62.0f }, { 50.0f, 16.0f });

		// Customize how the labels look
		guiLabelB->nAlign = olc::QuickGUI::Label::Alignment::Right;
		guiLabelG->nAlign = olc::QuickGUI::Label::Alignment::Right;
		guiLabelG->bHasBorder = true;
		guiLabelR->nAlign = olc::QuickGUI::Label::Alignment::Right;
		guiLabelR->bHasBorder = true;
		guiLabelR->bHasBackground = true;

		// Some Buttons, 1 is just a thing, 2 has its text updated and 3 resets the theme
		guiButton1 = new olc::QuickGUI::Button(guiManager,
			"Button 1", { 30.0f, 150.0f }, { 100.0f, 16.0f });
		guiButton2 = new olc::QuickGUI::Button(guiManager,
			"Button 2", { 30.0f, 170.0f }, { 100.0f, 16.0f });
		guiButton3 = new olc::QuickGUI::Button(guiManager,
			"Reset Theme", { 30.0f, 190.0f }, { 100.0f, 16.0f });

		// A CheckBox, switches between sprite or decal drawing
		guiCheckBox1 = new olc::QuickGUI::CheckBox(guiManager,
			"Use Decals", false, { 30.0f, 210.0f }, { 100.0f, 16.0f });

		// TextBox, allows basic text entry
		guiTextBox1 = new olc::QuickGUI::TextBox(guiManager,
			"", { 150.0f, 140.0f }, { 100.0f, 16.0f });
		guiTextBox2 = new olc::QuickGUI::TextBox(guiManager,
			"0.04", { 150.0f, 160.0f }, { 100.0f, 16.0f });

		listExample.push_back("Item 1");
		listExample.push_back("Item 2");
		listExample.push_back("Item 3");
		listExample.push_back("Item 4");
		listExample.push_back("Item 5");
		listExample.push_back("Item 6");

		guiListBox = new olc::QuickGUI::ListBox(guiManager,
			listExample, { 150.0f, 180.0f }, { 100.0f, 54.0f });

		// but but but.... waaaaaaaaahaaaaaaaa.... where do I delete these horrible
		// pointers??? I just can't accept that addressable memory exists and it makes
		// me feel really insecure!
		//
		// By default olc::QuickGUI::Manager will delete any Controls added to it, so you
		// dont have to. If you must obfuscate your program with smart pointers, or require
		// that you are in rage-control of your memory at all times, construct the Manager
		// with false as the argument - then its all up to you buddy.

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		SetDrawTarget(nullptr);
		nFrameCount = GetFPS();

		// We must update the manager at some point each frame. Values of controls
		// are only valid AFTER this call to update()
		guiManager.Update(this);

		// Some silly examples...

		// 001) The "theme colour" can be set from slider values
		guiManager.colNormal = olc::Pixel(
			uint8_t(guiThemeColourR->fValue),
			uint8_t(guiThemeColourG->fValue),
			uint8_t(guiThemeColourB->fValue));

		// 002) Display Slider 1 value on Button 2
		guiButton2->sText = "Button " + std::to_string(int32_t(guiSlider1->fValue));

		// 003) Check if "Reset Theme" button is pressed, if it is, well, err...
		if (guiButton3->bPressed)
		{
			// ...reset the theme! (which also updates the sliders)
			guiThemeColourR->fValue = 0.0f;
			guiThemeColourG->fValue = 0.0f;
			guiThemeColourB->fValue = 128.0f;
		}

		// 004) Link Slider 2 and Slider 3 together
		if (guiSlider2->bHeld)
			guiSlider3->fValue = 100.0f - guiSlider2->fValue;
		if (guiSlider3->bHeld)
			guiSlider2->fValue = 100.0f - guiSlider3->fValue;


		// Draw Stuff!
		Clear(olc::BLACK);

		// 005) Use checkbox to determine rendering mode
		if (guiCheckBox1->bChecked)
			guiManager.DrawDecal(this);
		else
			guiManager.Draw(this);

		//006) Update text box
		if (IsTextEntryEnabled()) UpdateTextEntry();

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
	demo.Construct(1280, 720, 3, 3, true, false, false);

	demo.Start(); // Lets get the party started


}


