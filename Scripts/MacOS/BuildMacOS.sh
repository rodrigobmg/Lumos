PATH="/usr/local/bin:$PATH"
xcodebuild -project Runtime.xcodeproj -configuration Release -parallelizeTargets -jobs 4 -sdk macosx -arch x86_64 | xcpretty
echo "Build Finished!"