
//////////////////////////////////////////////////////////////////
// Pixel Game Engine Mobile Release 2.2.7,                      //
// John Galvin aka Johnngy63: 03-Jun-2024                       //
// iOS Sensor NOT supported, coming soon                        //
// Please report all bugs to https://discord.com/invite/WhwHUMV //
// Or on Github: https://github.com/Johnnyg63					//
//////////////////////////////////////////////////////////////////

#import "AppDelegate.h"
#import "GameViewController.h"
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import "../../OLCPGEMobile/$ext_projectname$.Shared/main.cpp"
#import <memory>

#define MAX_TOUCHES 5

@interface GameViewController () {}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;
- (void)RemoveDuplicates;

@end

@implementation GameViewController
{
    //std::weak_ptr<IOSNativeApp> wp;
    //auto pTest;
    std::unique_ptr<PGE_Mobile> mPGEMobile;
    // GPU preferred frames per secound: iOS 30 <-> 60fps
    int8_t nGPUPreferredFPS;
    
    UITouch *savedTouches[MAX_TOUCHES];
    
    float fScaleFactor;
    
    int32_t nTouchScalerX;
    int32_t nTouchScalerY;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Setup Multitouch
    self.view.multipleTouchEnabled = YES;
    
    for (UIGestureRecognizer *gr in self.view.gestureRecognizers)
    {
      [self.view removeGestureRecognizer:gr];
    }
    
    for (int i=0; i<MAX_TOUCHES; i++)
    {
        savedTouches[i] = NULL;

    }
    
    
    //
    // Lets get our setting setup
    //
    // Get the path to the file within your app bundle
    // NSString *filePath = [[NSBundle mainBundle] pathForResource:@"images/body3d" ofType:@"png"];
    NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
       
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = paths[0];
    
    NSArray *morepaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = morepaths[0];
    
    
    
    // Allocate a context for us to draw in using OPENGLES2
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    // Get Scaler factor
    fScaleFactor = [[UIScreen mainScreen] scale];
    CGRect screen = [[UIScreen mainScreen] bounds];
    float widthInPixel = screen.size.width * fScaleFactor;
    float heightInPixel = screen.size.height * fScaleFactor;
    
    
    // OK lets call the ios_main, to get the engine started
    AppDelegate *app = (AppDelegate *)[[UIApplication sharedApplication]delegate];
    ios_main([app pIOSNativeApp]);
    
    if(mPGEMobile == nullptr)
    {
        mPGEMobile.reset(new PGE_Mobile);
    }
    
    
    // Setup up our OSEngine
    auto pConstruct = (IOSNativeApp::PGEConstruction)[app pIOSNativeApp]->structPGEConstruction;
    mPGEMobile->pOsEngine.screenWidth = (int32_t)widthInPixel;
    mPGEMobile->pOsEngine.screenHeight = (int32_t)heightInPixel;
    mPGEMobile->pOsEngine.bMaintainAspectRatio = pConstruct.bMaintainAspectRatio;
    mPGEMobile->pOsEngine.strInternalAppStorage = [bundlePath UTF8String];
    mPGEMobile->pOsEngine.strExternalAppStorage = [libraryDirectory UTF8String];
    mPGEMobile->pOsEngine.strPublicAppStorage = [documentDirectory UTF8String];

    mPGEMobile->Construct(pConstruct.nScreen_width, pConstruct.nScreen_height, pConstruct.nPixel_width, pConstruct.nPixel_height, pConstruct.bUseFullScreen, pConstruct.bUseVSYNC, pConstruct.bCohesion);
   
    // Set our content scale factor for when full screen is enabled
    if(mPGEMobile->pOsEngine.bFullScreen == true)
    {
        float customScale = mPGEMobile->pOsEngine.fScaleFactor; //[UIScreen mainScreen].scale / [UIScreen mainScreen].scale;
        customScale = [UIScreen mainScreen].scale * customScale;
        self.view.contentScaleFactor = customScale;
    }
    
    auto piOSApp = (IOSNativeApp::iOSApp)[app pIOSNativeApp]->structiOSApp;
    
    nTouchScalerX = piOSApp.nTouchScalerX;
    nTouchScalerY = piOSApp.nTouchScalerY;
    
    
    
    // Set our perferred GPU frame rate
    nGPUPreferredFPS = 60;
    self.preferredFramesPerSecond = nGPUPreferredFPS;

    // 4: Setup out View, this where we will draw your game
    // Cast the standard UIView to GLKview, we need this later
    GLKView *view = (GLKView *)self.view;
    
    // Context linkage, we want OpenGLES 2.0/3.0
    view.context = self.context;
    
    // Set our Depth format, recommend: 16 for 2D games, 24 for 3D
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    // Set out colour format to RGBA, so we can use APHLA (Transpartency .PNG for example)
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    
    // Set up our OpenGLES
    [self setupGL];
    
    // Lets start up or PGE Engine!!!
    mPGEMobile->Start();
    
    
    
}

- (void)dealloc
{
    [self tearDownGL];

    if(mPGEMobile != nullptr)
    {
        mPGEMobile.release();
    }
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;

        [self tearDownGL];

        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];

    // Log the OpenGLES Version
    NSLog(@"%s %s", glGetString(GL_RENDERER), glGetString(GL_VERSION));
    
    // OK lets get our OpenGLES Setup
    
    // Prepare our Engine:
    mPGEMobile->olc_PrepareEngine();
    mPGEMobile->pOsEngine.animating = 0;
    mPGEMobile->pOsEngine.StartPGE = false;
    

}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];

    mPGEMobile->pOsEngine.animating = 0;
    mPGEMobile->pOsEngine.StartPGE = false;
    mPGEMobile.reset();
}

#pragma mark - GLKView and GLKViewController delegate methods


- (void)update
{
    // Ok lets set that we are running
    mPGEMobile->pOsEngine.animating = 1;
    mPGEMobile->pOsEngine.StartPGE = true;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    [EAGLContext setCurrentContext:self.context];
    mPGEMobile->olc_CoreUpdate();
    
}

// Touch events

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    //
    // Fires when a touch is just began (OLC GetTouch(?).bPressed)
    //
    
    // Get an ordered array of all touchs on the screen
    NSArray *allTouches = [touches allObjects];
    
    // Let process them
    for (int i=0; i<[allTouches count]; i++)
    {
        UITouch *touch = allTouches[i];
        CGPoint currentPoint = [touch locationInView:self.view];
        
        // We cannot support unlimited number of touch points, hence we use MAX_TOUCHES vs [allTouches count]
        for(int j=0; j<MAX_TOUCHES; j++)
        {
            if(savedTouches[j] == NULL)
            {
                savedTouches[j] = touch;
                mPGEMobile->olc_UpdateTouchState(j, true);
                mPGEMobile->olc_UpdateTouch(currentPoint.x * fScaleFactor / nTouchScalerX, currentPoint.y * fScaleFactor / nTouchScalerY, j);
                break;
            }
        }
       
    }
    
    // iOS had a bad habit of sending in dupicates and race conditions when the user is hitting
    // the screen fast we need to remove these duplicates
    [self RemoveDuplicates];
    
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    
    //
    // Fires when a touch is moving (OLC GetTouch(?).bHeld)
    //
    // Get an ordered array of all touchs on the screen
    NSArray *allTouches = [touches allObjects];
    
    // Let process them
    for (int i=0; i<[allTouches count]; i++)
    {
        UITouch *touch = allTouches[i];
        CGPoint currentPoint = [touch locationInView:self.view];
        
        // We cannot support unlimited number of touch points, hence we use MAX_TOUCHES vs [allTouches count]
        for(int j = 0; j < MAX_TOUCHES; j++)
        {
            if(savedTouches[j]==touch)
            {
                mPGEMobile->olc_UpdateTouchState(j, true);
                mPGEMobile->olc_UpdateTouch(currentPoint.x * fScaleFactor / nTouchScalerX, currentPoint.y * fScaleFactor / nTouchScalerY, j);
                break;
            }
        }


    }
    
    // iOS had a bad habit of sending in dupicates and race conditions when the user is hitting
    // the screen fast we need to remove these duplicates
    [self RemoveDuplicates];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    //
    // Fires when a touch is released (OLC GetTouch(?).bReleased
    //
    
    NSArray *allTouches = [touches allObjects];
    for (int i=0; i<[allTouches count]; i++) {
        UITouch *touch = allTouches[i];

        for (int j=0; j<MAX_TOUCHES; j++) {
            if (touch == savedTouches[j]) {
                mPGEMobile->olc_UpdateTouchState(j, false);
                savedTouches[j] = NULL;
                for (int k = j; k < (MAX_TOUCHES -1); k++)
                {
                    savedTouches[k] = savedTouches[k+1];
                }
                break;
            }
        }
    }

    // iOS had a bad habit of sending in dupicates and race conditions when the user is hitting
    // the screen fast we need to remove these duplicates
    [self RemoveDuplicates];
}

-(void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    // We usually get a cancel event when there are too many touchs
    for(int i=0; i < MAX_TOUCHES; i++)
    {
        savedTouches[i] = NULL;
    }
    mPGEMobile->ClearTouchPoints();
    
    // iOS had a bad habit of sending in dupicates and race conditions when the user is hitting
    // the screen fast we need to remove these duplicates
    [self RemoveDuplicates];
    
    NSLog(@"Too many touches iOS is resetting all touch points");
}

-(void)RemoveDuplicates
{
    // iOS had a bad habit of sending in dupicates and race conditions when the user is hitting
    // the screen fast we need to remove these duplicates
    
   // Let use good old C for this
    int j = 0;
    int n = MAX_TOUCHES;
    
    for (int i=0; i < n; i++){
        for(j=i+1;j<n;)
        {
            if(savedTouches[i]==savedTouches[j])
            {
                for(int k=j;k<n-1;++k)
                    savedTouches[k]=savedTouches[k+1];

                --n;
            }
            else
            {
                ++j;
            }
                
        }
    }
    
    
    for(int i=n; i<MAX_TOUCHES; i++)
    {
        mPGEMobile->olc_UpdateTouchState(j, false);
        savedTouches[i] = NULL;
    }
    
}

//
//  Keyboard handler
//

-(void)pressesBegan:(NSSet<UIPress *> *)presses withEvent:(UIPressesEvent *)event
{
    for(UIPress *press in presses)
    {
        mPGEMobile->olc_UpdateKeyState((int32_t)press.key.keyCode, true);

    }
}

-(void)pressesChanged:(NSSet<UIPress *> *)presses withEvent:(UIPressesEvent *)event
{
    for(UIPress *press in presses)
    {
        mPGEMobile->olc_UpdateKeyState((int32_t)press.key.keyCode, true);

    }
}

-(void)pressesEnded:(NSSet<UIPress *> *)presses withEvent:(UIPressesEvent *)event
{
    for(UIPress *press in presses)
    {
        mPGEMobile->olc_UpdateKeyState((int32_t)press.key.keyCode, false);

    }
}

-(void)pressesCancelled:(NSSet<UIPress *> *)presses withEvent:(UIPressesEvent *)event
{
    for(UIPress *press in presses)
    {
        mPGEMobile->olc_UpdateKeyState((int32_t)press.key.keyCode, false);

    }
}

// Sensor Events... Coming soon I promise....

@end
