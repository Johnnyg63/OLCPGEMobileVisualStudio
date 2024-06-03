
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.6,                      //
// John Galvin aka Johnngy63: 03-Jun-2024                       //
// iOS Sensor NOT supported, coming soon                        //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

#import <UIKit/UIKit.h>
#import "ios_native_app_glue.h"
#import <memory>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property(strong, nonatomic) UIWindow* window;

@property(nonatomic, assign) IOSNativeApp* pIOSNativeApp;

@end
