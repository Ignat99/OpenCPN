#!/bin/sh

export PKG_CONFIG_PATH=/opt/Qt5.5.1/5.5/android_armv7/lib/pkgconfig
export QT_CUSTOM_DIR=/opt/Qt5.5.1/5.5/android_armv7
export CPPFLAGS=-D__ANDROID__
export PATH=/opt/android_toolchain/bin:$PATH
export CC=arm-linux-androideabi-gcc
export CXX=arm-linux-androideabi-g++

# wxWidget

cd /home/ignat99/Projects/wxqt/wxWidgets/build_android/
../configure --with-qt --build=x86_64-unknown-linux-gnu --host=arm-linux-androideabi --enable-compat28 --disable-shared --disable-arttango --enable-image --disable-dragimage --disable-sockets --with-libtiff=no --without-opengl --disable-baseevtloop --disable-xrc --disable-xrc --enable-cmdline --disable-miniframe --disable-mdi --enable-debug --disable-stc --disable-ribbon --disable-propgrid --disable-timepick --disable-datepick --disable-xlocale --disable-intl
make clean
make

# libassetbridge

/buildandroid/assetbridge/
export NDK_PROJECT_PATH=/home/ignat99/Projects/OpenCPN/buildandroid/assetbridge/
/home/ignat99/Projects/android-ndk/android-ndk-r10e/ndk-build
cp ./libs/armeabi/libassetbridge.so ..

#export ANDROID_NDK_ROOT=/home/ignat99/Projects/android-ndk/android-ndk-r10e
#export ANDROID_SDK_ROOT=/home/ignat99/android-sdk-linux

# OpenCPN

cd /home/ignat99/Projects/OpenCPN/build_android
export CMAKE_TOOLCHAIN_FILE=../buildandroid/build_android.cmake 
cmake -D_wx_selected_config=androideabi-qt -DCMAKE_TOOLCHAIN_FILE=../buildandroid/build_android.cmake ..
make clean
make

# Android APK

export ANDROID_NDK_ROOT=/home/ignat99/Projects/android-ndk/android-ndk-r10e
export ANDROID_SDK_ROOT=/home/ignat99/android-sdk-linux
/opt/Qt5.5.1/5.5/android_armv7/bin/qmake -makefile ../buildandroid/opencpn.pro -o Makefile.android -r -spec android-g++ CONFIG+=debug
make -f Makefile.android 
make -f Makefile.android install INSTALL_ROOT=./apk_build
/opt/Qt5.5.1/5.5/android_armv7/bin/androiddeployqt --input ./android-libopencpn.so-deployment-settings.json --output ./apk_build --android-platform android-19 --deployment bundled
cd apk_build/bin/
/home/ignat99/android-sdk-linux/platform-tools/adb devices
/home/ignat99/android-sdk-linux/platform-tools/adb kill-server
/home/ignat99/android-sdk-linux/platform-tools/adb start-server
/home/ignat99/android-sdk-linux/platform-tools/adb devices
/home/ignat99/android-sdk-linux/platform-tools/adb uninstall org.opencpn.opencpn
/home/ignat99/android-sdk-linux/platform-tools/adb -s 3100b1dba6505400 install ./QtApp-debug.apk 
