# OLC Pixel Game Engine Mobile Android Project Pre-Release 2.2.0
<p><b>Pre-Release!!!</b> Can now be used in Production Environment, have fun!</p>
<p>Please follow this steps folks:</p>
<p>1: Launch Visual Studio 2022 Installer</p> <!--Thanks @Pirate Voxel -->
<p>2: Click Modify</p>
<p>3: Install Mobile Development with C++ </p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/5812774f-54fa-4875-90ec-4f2e2d7a9899' />
</p>
<p>5: Install Java 17: https://www.oracle.com/java/technologies/downloads/#java17</p>
<p>6: Open Command Prompt in Administrator Mode, enter: setx -m JAVA_HOME "C:\Program Files\Java\jdk-17"</p>
<p>7: Open Visual Studio -->Tools-->Options-->Cross Platform. Update your SDK, NDK and Java Path as shown</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/77f70549-0d99-4f1e-9415-42fda6a99b20' /></p>
<p>8: Copy the <a href="https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/files/12837824/OLCPGEMobileAndroidProjectPreRelease220.zip">OLCPGEMobileAndroidProjectPreRelease220.zip</a> to your Projects Templates folder. Example: C:\Users\<i>your username</i>\OneDrive\Documents\Visual Studio 2022\Templates\ProjectTemplates</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/d1711b56-cddf-400f-8a26-daa9464722ce' /></p>
<p>9: Put your Android phone into Development Mode: https://developer.android.com/studio/debug/dev-options</p> <!--Thanks @Pirate Voxel -->
<p>10: Run Visual Studio 2022 in Admin Mode</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/daa5e9a6-309c-4b48-be44-c897ff54b6b2' /></p>
<p>11: Select Create Project</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/c720f822-4e62-417c-8322-b38f8f102059' /></p>
<p>12: Select OLC Pixel Game Engine Mobile Pre Release 2.2.0 for Android</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/12960c7a-e9c9-48ce-916b-26d3a45ed19f' /></p>
<p>13: Give your game a cool name. <b>NO SPACES</b> Do not start your project with a number: i.e. 3DShapes, 4Runner</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/53ec2875-a63c-4d4c-a10d-233b5e250b0c' /></p>
<p>14: Connect your phone and rebuild the solution, enjoy OLC Pixel Game Engine Mobile 2.0!</p>
<p><img src='https://github.com/Johnnyg63/OLCPGEMobileAndroidProjectBeta20/assets/96908304/b5e9e72e-73cf-4fe1-ba66-7df31790fce9' /></p>

<p><b>Beta Support Details</b></p>
<p>
<ul>
  <li>2.01: BETA Port code from olcPixelGameEngine.h to olcPixelGameEngine_mobile.h</li>
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
	<br/> Added: FileManager: for gaining acccess to the Andriod Assets APK and iOS Zip Packages
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
  <li>2.20 <b>Pre-Release!</b> Can now be used in Production Environment, have fun! <br/> Android Keyboard mapping completed for GetKey() <br/>Note if using a MacOS, Linux or Windows for debuging, some keys may not map correctly, directionaly keys will be out of sync as Andriod is mapped to a Direction Pad by default</i>
</ul>
	
</p>
<p>
	<b>Apple Platforms will not see these updates immediately</b><br/>
	<b>iOS port in progress. Beta release due soon</b>
</p>
