
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.1,                      //
// John Galvin aka Johnngy63: 21-Oct-2023                       //
// Full production release                                      //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

//
// pch.h
// Header for standard system include files.
//
// Used by the build system to generate the precompiled header. Note that no
// pch.cpp is needed and the pch.h is automatically included in all cpp files
// that are part of the project
//

#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

// OpenGLES Headers
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>

// NOTE: Do not depend on this header for using Sensors
// This will change in future beta releases
#include <android/sensor.h> 


#include <android/log.h>

// This header is used to activate your application
#include "android_native_app_glue.h"



