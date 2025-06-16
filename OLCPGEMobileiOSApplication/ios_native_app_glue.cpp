//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile All In One Release 2.2.9            //
// John Galvin aka Johnngy63: 16-Jun-2025                       //
// Now with 3D Lightweight support, iOS Sensor NOT supported    //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////


//
// This file is used by the template to render a basic scene using GL.
//

#include "../../OLCPGEMobile/$ext_projectname$.Shared/olcPixelGameEngine_Mobile.h"
#include "ios_native_app_glue.h"

IOSNativeApp::IOSNativeApp()
{
    // Set the default PGE Constructions
    this->SetPGEConstruct(-1, -1, 1, 1, true, false, false);

}

IOSNativeApp::~IOSNativeApp()
{
    // tba, clean up
}

void IOSNativeApp::IOSDirectEvent(DIRECT_EVENTS eventId)
{
       olc::EventManager::getInstance().HandleCommand((int8_t)eventId);

}

void IOSNativeApp::IOSInputEvent(int32_t cmd)
{
    olc::EventManager::getInstance().HandleInput(cmd);
}


void IOSNativeApp::SetPGEConstruct(const int32_t screen_w, const int32_t screen_h, const int32_t pixel_w, const int32_t pixel_h, const bool full_screen, const bool vsync, const bool cohesion, const bool maintain_aspect_ratio)
{
    this->structPGEConstruction.bCohesion = cohesion;
    this->structPGEConstruction.bUseFullScreen = full_screen;
    this->structPGEConstruction.bUseVSYNC = vsync;
    this->structPGEConstruction.nPixel_height = pixel_h;
    this->structPGEConstruction.nPixel_width = pixel_w;
    this->structPGEConstruction.nScreen_height = screen_h;
    this->structPGEConstruction.nScreen_width = screen_w;
    this->structPGEConstruction.bMaintainAspectRatio = maintain_aspect_ratio;
    
    this->structiOSApp.nTouchScalerX = pixel_w;
    this->structiOSApp.nTouchScalerY = pixel_h;
    
}

