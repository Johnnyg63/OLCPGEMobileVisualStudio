
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile All In One Release 2.2.9            //
// John Galvin aka Johnngy63: 16-Jun-2025                       //
// Now with 3D Lightweight support, iOS Sensor NOT supported    //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

#import <UIKit/UIKit.h>
#import "ios_native_app_glue.h"
#import <memory>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic, assign) IOSNativeApp* pIOSNativeApp;

@end
