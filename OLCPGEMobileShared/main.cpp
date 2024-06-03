
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.6,                      //
// John Galvin aka Johnngy63: 03-Jun-2024                       //
// iOS Sensor NOT supported, coming soon                        //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

//
// Base Project
//


// Set up headers for the different platforms
#if defined (__ANDROID__)

#include "../PGEMobileAllInOne.Android/pch.h"

#endif

#if defined (__APPLE__)

#include "ios_native_app_glue.h"
#include <memory>

#endif

//#define STBI_NO_SIMD // Removes SIMD Support
// SIMD greatly improves the speed of your game
#if defined(__arm__)||(__aarch64__)

// Use Advance SIMD NEON when loading images for STB Default is SSE2 (x86)
#define STBI_NEON

#endif

#define OLC_PGE_APPLICATION
#define OLC_IMAGE_STB
#include "olcPixelGameEngine_Mobile.h"

#define OLC_PGEX_MINIAUDIO
#include "olcPGEX_MiniAudio.h"  // Checkout https://github.com/Moros1138/olcPGEX_MiniAudio Thanks Moros1138

#include <fstream> // Used for saving the savestate to a file

/// <summary>
/// To ensure proper cross platform support keep the class name as PGE_Mobile
/// This will ensure the iOS can launch the engine correctly
/// If you change it make the required changes in GameViewController.mm in the iOS app to suit
/// </summary>
class PGE_Mobile : public olc::PixelGameEngine {

public:

    PGE_Mobile() {
        sAppName = "Android/iOS Demo";
    }

    /* Vectors */
    std::vector<std::string> vecMessages;
    /* END Vectors*/

    int nFrameCount = 0;
    int nStep = 20;

    /* Sprites */
    olc::Sprite* sprTouchTester = nullptr;
    olc::Sprite* sprOLCPGEMobLogo = nullptr;
    /* END Sprites*/

    /* Decals */
    olc::Decal* decTouchTester = nullptr;
    olc::Decal* decOLCPGEMobLogo = nullptr;
    /* End Decals */


    /* Sensors */
    std::vector<olc::SensorInformation> vecSensorInfos;
    /*End Sensors*/

    // To keep track of our sample ID
    // Ensure that all sound IDs are set to -1 stop memory leak when Android/iOS takes
    // the app out of focus
    int32_t song1 = -1;

    // For demonstration controls, with sensible default values
    float pan = 0.0f;
    float pitch = 1.0f;
    float seek = 0.0f;
    float volume = 1.0f;

    // The instance of the audio engine, no fancy config required.
    olc::MiniAudio ma;


public:
    //Example Save State Struct and Vector for when your app is paused
    struct MySaveState {
        std::string key;
        int value;
    };

    std::vector<MySaveState> vecLastState;

    std::string sampleAFullPath; // Holds the full path to sampleA.wav

public:
    bool OnUserCreate() override {
        //NOTE: To access the features with your phone device use:
#if defined(__ANDROID__)
        // Access android directly
        //android_app* pMyAndroid = this->pOsEngine.app;

        // USE OF SOUND olcPGE_MiniAudio
        /*
         * For Android you cannot play the sounds directly from the assets as you would
         * on a Windows/Mac/Linux system. Android compress your assets in a compress file to
         * save on valuable phone storage. AndroidAudio (AAudio), miniAudio, and most others need
         * to be able to stream the music data, in short they are not very good at streaming for
         * a compress file.
         * Therefore you will need to extract these sound files to internal storage so the sounds
         * can be played.
         *
         * In short, as I know you didn't read the above, you cannot stream from an asset in Android
         *
         */

        std::string songFullPath = (std::string)app_GetInternalAppStorage() + "/sounds/song1.mp3";
        olc::rcode fileRes = olc::filehandler->ExtractFileFromAssets("sounds/song1.mp3", songFullPath);

        switch (fileRes) {

        case olc::rcode::NO_FILE:
        { break; }
        case olc::rcode::FAIL:
        { break; }
        case olc::rcode::OK:
        {
            // only load the song if it is not already loaded
            song1 = ma.LoadSound(songFullPath);

            break;
        }
        }

        sampleAFullPath = (std::string)app_GetInternalAppStorage() + "/sounds/SampleA.wav";
        olc::filehandler->ExtractFileFromAssets("sounds/SampleA.wav", sampleAFullPath);


#endif

#if defined(__APPLE__)
        // Access iOS directly
        //apple_app* pMyApple = this->pOsEngine.app;

        // USE OF SOUND olcPGE_MiniAudio

        std::string songFullPath = (std::string)app_GetInternalAppStorage() + "/sounds/song1.mp3";
        olc::rcode fileRes = olc::filehandler->ExtractFileFromAssets("sounds/song1.mp3", songFullPath);

        switch (fileRes) {

        case olc::rcode::NO_FILE:
        { break; }
        case olc::rcode::FAIL:
        { break; }
        case olc::rcode::OK:
        {
            if (song1 < 0)
            {
                song1 = ma.LoadSound(songFullPath);
            }

            break;
        }
        }

        sampleAFullPath = (std::string)app_GetInternalAppStorage() + "/sounds/SampleA.wav";
        olc::filehandler->ExtractFileFromAssets("sounds/SampleA.wav", sampleAFullPath);

#endif

        sprTouchTester = new olc::Sprite("images/north_south_east_west_logo.png");
        decTouchTester = new olc::Decal(sprTouchTester);

        sprOLCPGEMobLogo = new olc::Sprite("images/olcpgemobilelogo.png");
        decOLCPGEMobLogo = new olc::Decal(sprOLCPGEMobLogo);


        return true;
    }

    // <summary>
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

    bool OnUserUpdate(float fElapsedTime) override {

        SetDrawTarget(nullptr);

        Clear(olc::BLUE);

        nFrameCount = GetFPS();

        std::string sLineBreak = "-------------------------";

        std::string sMessage = "OneLoneCoder.com";
        vecMessages.push_back(sMessage);

        sMessage = "PGE Mobile Release 2.2.6";
        vecMessages.push_back(sMessage);

        sMessage = "Now With iOS Support";
        vecMessages.push_back(sMessage);

        sMessage = "NOTE: Android FPS = CPU FPS, iOS = GPU FPS";
        vecMessages.push_back(sMessage);

        sMessage = sAppName + " - FPS: " + std::to_string(nFrameCount);
        vecMessages.push_back(sMessage);

        sMessage = "---";
        vecMessages.push_back(sMessage);


        sMessage = "Volume <" + std::to_string(volume) + "> Btn Up, Btn Down";
        vecMessages.push_back(sMessage);

        if (ma.IsPlaying(song1))
        {
            sMessage = "Touch Screen: Pause";
            vecMessages.push_back(sMessage);
        }
        else
        {
            sMessage = "Touch Screen: Play";
            vecMessages.push_back(sMessage);
        }

        sMessage = "---";
        vecMessages.push_back(sMessage);

        sMessage = "Music: Joy Ride [Full version] by MusicLFiles";
        vecMessages.push_back(sMessage);
        sMessage = "Free download:";
        vecMessages.push_back(sMessage);
        sMessage = "https://filmmusic.io/song/11627-joy-ride-full-version";
        vecMessages.push_back(sMessage);
        sMessage = "Licensed under CC BY 4.0:";
        vecMessages.push_back(sMessage);
        sMessage = "https://filmmusic.io/standard-license";
        vecMessages.push_back(sMessage);
        vecMessages.push_back(sLineBreak);

        std::string sTouchScreen = "Touch the screen with two fingers";
        vecMessages.push_back(sTouchScreen);

        vecMessages.push_back(sLineBreak);

        olc::vi2d centreScreenPos = GetScreenSize();
        centreScreenPos.x = centreScreenPos.x / 2;
        centreScreenPos.y = centreScreenPos.y / 2;
        DrawTargetPointer(centreScreenPos, 50, 10);

        // Get the default touch point
        // This is alway Index 0 and first touch piont
        olc::vi2d defautTouchPos = GetTouchPos();
        std::string defautTouch = "Default Touch 0:  X: " + std::to_string(defautTouchPos.x) + " Y: " + std::to_string(defautTouchPos.y);
        vecMessages.push_back(defautTouch);

        if (GetTouch().bHeld)
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
        for (int i = 1; i < 5; i++)
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
        // Uncomment me if you dare
        /*for (int x = 0; x < ScreenWidth(); x++)
            for (int y = 0; y < ScreenHeight(); y++)
                Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
        */

        nStep = 10;
        for (auto& s : vecMessages)
        {
            DrawString(20, nStep, s);
            nStep += 10;
        }
        vecMessages.clear();




        if (GetTouch(0).bPressed) {
            // Toggle takes a sample ID (int) and either starts playback or pauses playback
            // depending on whether the sample is currently playing, or not.
            ma.Toggle(song1);
        }

        if (GetTouch(1).bPressed) {
            ma.Play(sampleAFullPath);
        }

        if (GetKey(olc::A).bHeld)
        {
            volume += 1.0f * fElapsedTime;
            if (volume > 1.0f) volume = 1.0f;
        }

        if (GetKey(olc::B).bHeld)
        {
            volume -= 1.0f * fElapsedTime;
            if (volume < 0.0f) volume = 0.0f;
        }

        if (GetKey(olc::VOLUME_DOWN).bHeld) {
            // NOTE: Android volume buttons can be read but cannot be captured
            // NOTE: iOS volume buttons cannot be read and cannot be captured
            volume -= 1.0f * fElapsedTime;
            if (volume < 0.0f) volume = 0.0f;
        }

        if (GetKey(olc::VOLUME_UP).bHeld) {
            // NOTE: Android volume buttons can be read but cannot be captured
            // NOTE: iOS volume buttons cannot be read and cannot be captured
            volume += 1.0f * fElapsedTime;
            if (volume > 1.0f) volume = 1.0f;
        }

        // Set volume, takes a sample ID (int), and a float
        // 0.0 to 1.0 where 1.0 is full volume
        ma.SetVolume(song1, volume);

        // Gets the current playback position in the provided sample ID (int),
        // returns float 0.0 to 1.0, nearer 1.0 is near the end
        seek = ma.GetCursorFloat(song1);


        // Draw Logo
        DrawDecal({ 5.0f, (float)ScreenHeight() - 100 }, decOLCPGEMobLogo, { 0.5f, 0.5f });

        // Draw The Playback Cursor (aka the position in the sound file)
        FillRect({ 0, ScreenHeight() - 10 }, { (int)(ScreenWidth() * seek), 10 }, olc::YELLOW);

        return true;
    }

    bool OnUserDestroy() override {
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

#if defined(__ANDROID__)
        // You can save files in the android Internal app storage
        const char* internalPath = app_GetInternalAppStorage(); //Android protected storage
#endif
#if defined(__APPLE__)
        // For iOS the internal app storage is read only, therefore we use External App Storage
        const char* internalPath = app_GetExternalAppStorage(); // iOS protected storage AKA /Library
#endif

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

#if defined(__ANDROID__)
        // You can save files in the android Internal app storage
        const char* internalPath = app_GetInternalAppStorage(); //Android protected storage
#endif
#if defined(__APPLE__)
        // For iOS the internal app storage is read only, therefore we use External App Storage
        const char* internalPath = app_GetExternalAppStorage(); // iOS protected storage AKA /Library
#endif

        std::string dataPath(internalPath);
        std::string lastStateFile = dataPath + "/lastStateFile.bin";

        vecLastState.clear();

        std::ifstream file(lastStateFile, std::ios::in | std::ios::binary);

        MySaveState saveState;

        if (file)
        {
            float fVecSize = 0.0f;
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


#if defined (__ANDROID__)
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

#endif

#if defined(__APPLE__)

/*
* The is the calling point from the iOS Objective C, called during the startup of your application
* Use the objects definded in IOSNativeApp to pass data to the Objective C
* By Default you must at minmum pass the game construct vars, pIOSNatvieApp->SetPGEConstruct
*
* iOS runs in its own threads, with its own
* event loop for receiving input events and doing other things.
* This is now what drives the engine, the thread is controlled from the OS
*/
int ios_main(IOSNativeApp* pIOSNatvieApp)
{
    // The iOS will instance your app differnetly to how Android does it
    // In the iOS it will automatically create the required classes and pointers
    // to get the PGE up and running successfull.

    // IMPORTANT: You must set your class name to PGE_Mobile (see above) always for iOS
    // Don't worry it will not conflict with any other apps that use the same base class name of PGE_Mobile
    // I got your back

    // Finally just like the Android you can access any avialble OS options using pIOSNatvieApp
    // Please note options will NOT be the same across both platforms
    // It is best to use the build in functions for File handling, Mouse/Touch events, Key events, Joypad etc

    //
    // To access the iOS directly in your code
    // auto* pMyApple = this->pOsEngine.app;
    //

    /*
        Note it is best to use HD(1280, 720, ? X ? pixel, Fullscreen = true) the engine can scale this best for all screen sizes,
        without affecting performance... well it will have a very small affect, it will depend on your pixel size
        Note: cohesion is currently not working
        Note: It is best to set maintain_aspect_ratio to false, Fullscreen to true and use the olcPGEX_TransformView.h to manage your world-view
        in short iOS does not want to play nice, the screen ratios and renta displays make maintaining a full screen with aspect radio a pain to manage
    */
    pIOSNatvieApp->SetPGEConstruct(1280, 720, 2, 2, true, true, false);


    // We now need to return SUCCESS or FAILURE to get the party stated!!!!
    return EXIT_SUCCESS;
}

#endif


