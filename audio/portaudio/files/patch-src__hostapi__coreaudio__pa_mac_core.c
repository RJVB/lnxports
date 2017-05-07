diff --git src/hostapi/coreaudio/pa_mac_core.c src/hostapi/coreaudio/pa_mac_core.c
index 257e9dedc3f66248b1108537d63bae7128c5e87f..2f778acef72fc7d5a25318d04aecb6939616ece1 100644
--- src/hostapi/coreaudio/pa_mac_core.c
+++ src/hostapi/coreaudio/pa_mac_core.c
@@ -1173,8 +1173,8 @@ static PaError OpenAndSetupOneAudioUnit(
                                    const double sampleRate,
                                    void *refCon )
 {
-    ComponentDescription desc;
-    Component comp;
+    AudioComponentDescription desc;
+    AudioComponent comp;
     /*An Apple TN suggests using CAStreamBasicDescription, but that is C++*/
     AudioStreamBasicDescription desiredFormat;
     OSStatus result = noErr;
@@ -1245,7 +1245,7 @@ static PaError OpenAndSetupOneAudioUnit(
     desc.componentFlags        = 0;
     desc.componentFlagsMask    = 0;
     /* -- find the component -- */
-    comp = FindNextComponent( NULL, &desc );
+    comp = AudioComponentFindNext( NULL, &desc );
     if( !comp )
     {
        DBUG( ( "AUHAL component not found." ) );
@@ -1254,7 +1254,7 @@ static PaError OpenAndSetupOneAudioUnit(
        return paUnanticipatedHostError;
     }
     /* -- open it -- */
-    result = OpenAComponent( comp, audioUnit );
+    result = AudioComponentInstanceNew( comp, audioUnit );
     if( result )
     {
        DBUG( ( "Failed to open AUHAL component." ) );
@@ -1607,7 +1607,7 @@ static PaError OpenAndSetupOneAudioUnit(
 #undef ERR_WRAP
 
     error:
-       CloseComponent( *audioUnit );
+       AudioComponentInstanceDispose( *audioUnit );
        *audioUnit = NULL;
        if( result )
           return PaMacCore_SetError( result, line, 1 );
@@ -2645,13 +2645,13 @@ static PaError CloseStream( PaStream* s )
        }
        if( stream->outputUnit && stream->outputUnit != stream->inputUnit ) {
           AudioUnitUninitialize( stream->outputUnit );
-          CloseComponent( stream->outputUnit );
+          AudioComponentInstanceDispose( stream->outputUnit );
        }
        stream->outputUnit = NULL;
        if( stream->inputUnit )
        {
           AudioUnitUninitialize( stream->inputUnit );
-          CloseComponent( stream->inputUnit );
+          AudioComponentInstanceDispose( stream->inputUnit );
           stream->inputUnit = NULL;
        }
        if( stream->inputRingBuffer.buffer )
@@ -2711,12 +2711,12 @@ static PaError StartStream( PaStream *s )
 
 // it's not clear from appl's docs that this really waits
 // until all data is flushed.
-static ComponentResult BlockWhileAudioUnitIsRunning( AudioUnit audioUnit, AudioUnitElement element )
+static OSStatus BlockWhileAudioUnitIsRunning( AudioUnit audioUnit, AudioUnitElement element )
 {
     Boolean isRunning = 1;
     while( isRunning ) {
        UInt32 s = sizeof( isRunning );
-       ComponentResult err = AudioUnitGetProperty( audioUnit, kAudioOutputUnitProperty_IsRunning, kAudioUnitScope_Global, element,  &isRunning, &s );
+       OSStatus err = AudioUnitGetProperty( audioUnit, kAudioOutputUnitProperty_IsRunning, kAudioUnitScope_Global, element,  &isRunning, &s );
        if( err )
           return err;
        Pa_Sleep( 100 );
