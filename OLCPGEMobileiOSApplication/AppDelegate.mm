
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile All In One Release 2.2.9            //
// John Galvin aka Johnngy63: 16-Jun-2025                       //
// Now with 3D Lightweight support, iOS Sensor NOT supported    //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

#import "AppDelegate.h"

@interface AppDelegate ()
//- (void)setIOSNativeGlue:(IOSNativeApp*)mIOSNativeApp;
@end

@implementation AppDelegate
{
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    if(self.pIOSNativeApp == nullptr)
    {
        self.pIOSNativeApp = new IOSNativeApp;
    }
    self.pIOSNativeApp->IOSDirectEvent(IOSNativeApp::FINISHED_LAUNCH);
    // Remove gestures, you will thank me later
    for (UIGestureRecognizer *gr in self.window.gestureRecognizers)
    {
      [self.window removeGestureRecognizer:gr];
    }
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    self.pIOSNativeApp->IOSDirectEvent(IOSNativeApp::RESIGN_ACTIVE);

}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    self.pIOSNativeApp->IOSDirectEvent(IOSNativeApp::ENTERED_BACKGROUND);
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    self.pIOSNativeApp->IOSDirectEvent(IOSNativeApp::ENTERED_FOREGROUND);
    
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    self.pIOSNativeApp->IOSDirectEvent(IOSNativeApp::BECOME_ACTIVE);
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    
    self.pIOSNativeApp->IOSDirectEvent(IOSNativeApp::TERMINATE);
    
    // I created a standard pointer to the IOSNativeApp as I was having WAY TO MUCH headache using a smartpointer
    // well done apple lol, therefore we need to delete the pointer and clear any memory
    delete self.pIOSNativeApp;
    
}

@end
