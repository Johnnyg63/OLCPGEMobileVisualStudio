#pragma once

//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.6,                      //
// John Galvin aka Johnngy63: 03-Jun-2024                       //
// iOS Sensor NOT supported, coming soon                        //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

/*
 * Copyright (C) 2024 JohnGalvin.net APPLE NATIVE GLUE
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
 * John Galvin Test1
 */

 /*
 *   IOS Native GLUE
 *   This header file allows for the ios Objecive C code to commuciate with the C/C++ PGE Mobile Code
 *   What is a GLUE Adapther: See: https://en.wikipedia.org/wiki/Glue_code
 *   In computer programming, glue code is executable code (often source code) that serves solely to "adapt" different parts
 *   of code that would otherwise be incompatible.
 *   Glue code does not contribute any functionality towards meeting program requirements.
 */

#if defined (__APPLE__)

#ifndef _IOS_NATIVE_APP_GLUE_H
#define _IOS_NATIVE_APP_GLUE_H

#include <string.h>

#include <unistd.h>
#include <cstdint>


class IOSNativeApp
{
public:
    IOSNativeApp();
    ~IOSNativeApp();


    enum DIRECT_EVENTS
    {
        FINISHED_LAUNCH = 0,   // Override point for customization after application launch.
        RESIGN_ACTIVE,          // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        ENTERED_BACKGROUND,     // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        ENTERED_FOREGROUND,     // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
        BECOME_ACTIVE,          // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
        TERMINATE               // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.

    };


    void IOSDirectEvent(DIRECT_EVENTS eventId);
    void IOSInputEvent(int32_t cmd);

    // Sets the PGE Construction Values
    void SetPGEConstruct(const int32_t screen_w = 0, const int32_t screen_h = 0, const int32_t pixel_w = 1, const int32_t pixel_h = 1, const bool full_screen = true, const bool vsync = false, const bool cohesion = false, const bool maintain_aspect_ratio = false);

    struct PGEConstruction
    {
        int32_t nScreen_width = 0;          // Stores the requested Screen width, Default: 0 (AutoSize)
        int32_t nScreen_height = 0;         // Stores the requsted Screen Height, Default: 0 (AutoSize)
        int32_t nPixel_width = 1;           // Stores the requested Pixel Width,  Default: 1
        int32_t nPixel_height = 1;          // Stores the requested Pixel Height, Default: 1 (AutoSize)
        bool bUseFullScreen = true;         // Enable Full Screen, Default: true
        bool bUseVSYNC = false;             // Enable VSYNC, Default: false
        bool bCohesion = false;             // CURRENT NOT SUPPORTED:Enable Cohesion
        bool bMaintainAspectRatio = false;  // Maintain Aspect Radio, Default: false


    }structPGEConstruction;

    struct iOSApp
    {
        int32_t nScreen_width = 0;          // Stores the iOS Screen width,
        int32_t nScreen_height = 0;         // Stores the iOS Screen Height,
        int32_t nScreen_width_pixels = 0;   // Stores the requested Screen width in pixels
        int32_t nScreen_height_pixels = 0;  // Stores the requsted Screen Height in pixels
        float nPixel_width_pixels = 1.0f;   // Stores the requested Pixel Width,  Default: 1.0f
        float nPixel_height_pixels = 1.0f;  // Stores the requested Pixel Height, Default: 1.0f
        float nTouchScalerX = 1.0f;         // Stores the offset scaler X for touch.x
        float nTouchScalerY = 1.0f;         // Stores the offset scaler Y for touch.y

    }structiOSApp;

};

#endif /* definded(_IOS_NATIVE_APP_GLUE_H)*/

#endif