# OLC Pixel Game Engine Mobile Android Project 2.2.4

<p>For Android Studio (Windows/Linux/MAC) Use this project: <a href="https://github.com/Johnnyg63/OLCPGEMobileAndroidStudio">OLC Pixel Game Engine Mobile 2.2.4 for Android Studio</a></i></p>

<hr/>
<p><b><i>!!! NOW WITH iOS SUPPORT!!!</i></b></p>
<p><b><i>Anything you develop for PGE Mobile Android will work on the iOS</i></b></p>

<p><i>Visual Studio Android & iOS template project coming soon.</i></p>
<p><i>Apple xCode template project coming soon.</i></p>
<p>NOTE: iOS Beta 2.2.4 does not yet support sensors</p>
<hr/>


<p><b><i>WE NEED YOUR FEEDBACK PLEASE</i></b></p>

<hr/>
<p><i><b>Thank you for cloning the OLC Pixel Game Engine 2.0 Mobile.</b><br/><br/>
	A tremendous amount of work went into getting this engine to work smoothy with Android and iOS plus keep it simple so you can create amazing games.<br/>
 	We can see that this repro gets an <b>unbelievable number of unique clones</b>, therefore we want to hear from you!<br/>
  	Please come visit me and all the volunteers at One Lone Coder and join our community.
   	<ul>
		<li>Discord: <a href="https://discord.com/invite/WhwHUMV">One Lone Coder</a></li>
		<li>YouTube: <a href="https://www.youtube.com/c/javidx9">One Lone Coder</a> </li>
		<li>Twitch: <a href="https://www.twitch.tv/javidx9">One Lone Coder</a></li>
		<li>Website: <a href="https://community.onelonecoder.com/">www.onelonecoder.com</a></li>
	</ul>
 <br/>
 Kind regards<br/>
 <br/>
 John (aka Johnnyg63)
</i></p>
<hr/>


<p><b>Now with iOS Support</b></p>
<p><b>Supports olcPGEX_MiniAudio.h</b><br/><a href="https://github.com/Moros1138/olcPGEX_MiniAudio/">https://github.com/Moros1138/olcPGEX_MiniAudio/</a> thanks @Moros1138</p>
<p><b>Supports the latest Android Phones and GPUs</b><br/> SDK 23 --> 33 and beyond</p>
<p>For Android we needed to split the renderer into Renderer_OGLES10 and Renderer_OGLES20. Although most of the code is pretty much the same
	there maybe updates in the future to support newer & newer Android GPUs coming to the market and I didn't want to end up in a mess of conditional
	statements... well not yet anyway.</p>
	<p>The olc_ConfigureSystem() manages this:<br/>
	<b>Renderer_OGLES10:</b> Support for SDK 23 - 29 This code better supports ARM devices, however ARM64 will work just fine with it.<br/>
	<b>Renderer_OGLES20:</b> Support for SDK 30 - 33 and beyond. This code is really for ARM64 and the latest GPUs on the market, also for iOS support.<br/>
	You can adjust the SDK value in olc_ConfigureSystem() as you require </p>

<p><i>The Below steps are for Visual Studio on Windows, <br/>
		For Android Studio (Windows/Linux/MAC) project can be found here: <a href="https://github.com/Johnnyg63/OLCPGEMobileAndroidStudio">OLC Pixel Game Engine Mobile 2.2.3 for Android Studio</a></i></p>
<p><b>Please follow this steps folks:<br/></p>
<p>1: Launch Visual Studio 2022 Installer</p> <!--Thanks @Pirate Voxel -->
<p>2: Click Modify</p>
<p>3: Install Mobile Development with C++ </p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/5812774f-54fa-4875-90ec-4f2e2d7a9899' />
</p>
<p>5: Install Java 17: https://www.oracle.com/java/technologies/downloads/#java17</p>
<p>6: Open Command Prompt in Administrator Mode, enter: setx -m JAVA_HOME "C:\Program Files\Java\jdk-17"</p>
<p>7: Open Visual Studio -->Tools-->Options-->Cross Platform. Update your SDK, NDK and Java Path as shown</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/77f70549-0d99-4f1e-9415-42fda6a99b20' /></p>
<p>8: Copy the <a href="https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectRelease221/blob/master/OLCPGEMobileAndroidProjectRelease224.zip">OLCPGEMobileAndroidProjectRelease223.zip</a> to your Projects Templates folder. Example: C:\Users\<i>your username</i>\OneDrive\Documents\Visual Studio 2022\Templates\ProjectTemplates</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileVisualStudio/assets/96908304/91d4505a-8ce5-4312-ae21-1867ee8c27b5' /></p>
<p>9: Put your Android phone into Development Mode: https://developer.android.com/studio/debug/dev-options</p> <!--Thanks @Pirate Voxel -->
<p>10: Run Visual Studio 2022 in Admin Mode</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/daa5e9a6-309c-4b48-be44-c897ff54b6b2' /></p>
<p>11: Select Create Project</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/c720f822-4e62-417c-8322-b38f8f102059' /></p>
<p>12: Select OLC Pixel Game Engine Mobile 2.2.4 for Android</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileVisualStudio/assets/96908304/791bf229-3670-4bce-91eb-5cfbd1e3ce94' /></p>
<p>13: Give your game a cool name. <b>NO SPACES</b> Do not start your project with a number: i.e. 3DShapes, 4Runner</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileVisualStudio/assets/96908304/b0e7ac50-9b8d-4c58-b2e0-8ea7a35daac9' /></p>
<p>14: Connect your phone and rebuild the solution, enjoy OLC Pixel Game Engine Mobile 2.0!</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/b5e9e72e-73cf-4fe1-ba66-7df31790fce9' /></p>

<p><b>Release 2.2.3 Support Details</b></p>
<p>
<ul>
  <li>2.01: BETA Port code from olcPixelGameEngine.h to olcPixelGameEngine_mobile.h. Thanks @Javidx9</li>
  <li>2.02: Corrected support for X86</li>
  <li>2.03: Update EventManager to handle, Touch, Mouse and Keyboard events</li>
  <li>2.04: Corrected Touch offset, added 1 touch point, unlinked Mouse & Touch Events</li>
  <li>2.05: Sensors Support added</li>
  <li>2.06: Multi Touch Support</li>
  <li>2.06a: Added basic mouse support for Android Emulator</li>
  <li>2.07: Updated SIMD_SSE for Intel Atom devices, Updated GetTouch() to default to touch point zero</li>
  <li>2.07a: Corrected two small bugs in main.cpp</li>
  <li>2.08: Added ClearTouchPoints(int8_t startIndex = 0) for clearing of touch points at index x, some bug fixes too<br/> <i>Added Demos folder with some demos. Just Copy and Paste the code into main.cpp</i></li>
  <li>2.09: Added Demos folder with some demos</i>
	<br/> Added: FileManager: for gaining acccess to the Android Assets APK and iOS Zip Packages
				<br/> app_LoadFileFromAssets()
				<br/> app_ExtractFileFromAssets()
				<br/> app_GetInternalAppStorage()
				<br/> app_GetExternalAppStorage()
				<br/> app_GetPublicAppStorage()
				<br/> SmartPtr filehandler
				<br/> LoadFileFromAssets()
				<br/> ExtractFileFromAssets()
				<br/> GetInternalAppStorage()
				<br/> GetExternalAppStorage()
				<br/> GetPublicAppStorage()
  </li>
  <li>2.10: Removed ASensor_getHandle() as it only supports SDK 29 and higher. Updated project to support SDK 21 to SDK32, Thank you @VasCoder</li>
  <li>2.11: Corrected offset error bug in Drawline,<br/> Added release config to build.gradle.template. Please see: <a href="https://developer.android.com/studio/publish/app-signing">https://developer.android.com/studio/publish/app-signing"</a> and<br/> Please see: <a href="https://developer.android.com/studio/publish/app-signing">https://stackoverflow.com/questions/9081877/how-do-i-debug-an-apk-that-is-signed-for-release</a> for more info<br/><b>NOTE: You cannot debug or deploy a release app unless you have a signing key (Android Developer Account)</b></i>
  <li>2.20 <b>Pre-Release!</b> Can now be used in Production Environment, have fun! <br/> Android Keyboard mapping completed for GetKey() <br/>Note if using a MacOS, Linux or Windows for debugging, some keys may not map correctly, directionally keys will be out of sync as Android is mapped to a Direction Pad by default</i>
  <li>2.21 <b>Full Production Release</b> </i>
  <li>2.22 Better support for the latest Android phones<br/>
			The Engine will now detect the correct OpenGLES setting for your Android phone and apply the correct settings			</i>
  <li>2.23 Now with Sound, supports olcPGE_MiniAudio <a href="https://github.com/Moros1138/olcPGEX_MiniAudio/">https://github.com/Moros1138/olcPGEX_MiniAudio/</a> thanks @Moros1138
		   <br/>Updated EventManager::HandleInput to ensure Volume UP/Down/Mute, Camera and Power Buttons are released back to the OS after execution
  </i>
  <li>2.24 iOS Beta support. Sensors not supported. Anything you develop for Android will work on the iOS</i>
</ul>
	
</p>
<p>
	<b>iOS port completed. xCode and new Visual Studio Template projects coming sooh. For the moment get developing on Android, as anything you develop for Android will work on the iOS</b>
</p>
