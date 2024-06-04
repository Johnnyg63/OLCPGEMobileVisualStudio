#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>
#import "../../$ext_projectname$.Shared/SimpleRenderer.h"

#import <memory>

@interface GameViewController () {}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation GameViewController
{
    std::unique_ptr<SimpleRenderer> mCubeRenderer;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];

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

	if (mCubeRenderer == nullptr)
	{
		mCubeRenderer.reset(new SimpleRenderer());
		mCubeRenderer->UpdateWindowSize(self.view.bounds.size.width, self.view.bounds.size.height);
	}
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];

	mCubeRenderer.reset();
}

#pragma mark - GLKView and GLKViewController delegate methods

extern float _rotation;

- (void)update
{
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	mCubeRenderer->Draw();
}

@end
