
#Toolchain and options definition file for OPenCPN Android build


#  Locations of the cross-compiler tools
# this one is important
SET(CMAKE_SYSTEM_NAME Generic)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /opt/android_toolchain/bin/arm-linux-androideabi-gcc)
SET(CMAKE_CXX_COMPILER   /opt/android_toolchain/bin/arm-linux-androideabi-g++)

# Location of the generic wxWidgets base
SET(wxQt_Base /home/ignat99/Projects/wxqt/wxWidgets)

#Location of the specific wxWidgets build (for Qt_Androidd)
SET(wxQt_Build build_android)

#Location of the root of the Qt installation
SET(Qt_Base /opt/Qt5.5.1/5.5/android_armv7)