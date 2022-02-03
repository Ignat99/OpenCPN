#-------------------------------------------------
#
# Project created by QtCreator 2014-03-27T23:08:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencpn

TEMPLATE = app


# Qt target
wxQt_Base=/home/ignat99/Projects/wxqt/wxWidgets
wxQt_Build=build_android

# OCPN target
OCPN_Base=/home/ignat99/Projects/OpenCPN
OCPN_Build=build_android


INCLUDEPATH += $${wxQt_Base}/include/

INCLUDEPATH += $${OCPN_Base}/include/
INCLUDEPATH += $${OCPN_Base}/src/nmea0183

LIBS += $${OCPN_Base}/$${OCPN_Build}/libopencpn.a
LIBS += $${OCPN_Base}/$${OCPN_Build}/libGARMINHOST.a
LIBS += $${OCPN_Base}/$${OCPN_Build}/libNMEA0183.a
#LIBS += $${OCPN_Base}/$${OCPN_Build}/libS57ENC.a
LIBS += $${OCPN_Base}/$${OCPN_Build}/libSYMBOLS.a


LIBS += -L$${wxQt_Base}/$${wxQt_Build}/lib
INCLUDEPATH += $${wxQt_Base}/$${wxQt_Build}/lib/wx/include/arm-linux-androideabi-qt-unicode-static-3.1

LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_qtu_html-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_baseu_xml-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_qtu_qa-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_qtu_adv-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_qtu_core-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_baseu-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwx_qtu_aui-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwxexpat-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwxregexu-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwxjpeg-3.1-arm-linux-androideabi.a
LIBS += $${wxQt_Base}/$${wxQt_Build}/lib/libwxpng-3.1-arm-linux-androideabi.a


DEFINES += __WXQT__

SOURCES += $$PWD/../buildandroid/ocpn_wrapper.cpp


CONFIG += mobility
CONFIG += debug
MOBILITY =

ANDROID_EXTRA_LIBS = $$PWD/../buildandroid/libassetbridge.so
#ANDROID_EXTRA_LIBS += /home/ignat99/Projects/OpenCPN/build_android/plugins/dashboard_pi/libdashboard_pi.so


# To execute the assetbridge runtime code, we make a custom modification to the android Activity method.
# so we include the sources for this patched version here

ANDROID_PACKAGE_SOURCE_DIR = $${OCPN_Base}/buildandroid/android
OTHER_FILES += $${OCPN_Base}/buildandroid/android/AndroidManifest.xml

ui_deployment.files += $$PWD/../data/s57data/chartsymbols.xml
ui_deployment.files += $$PWD/../src/bitmaps/styles.xml
ui_deployment.files += $$PWD/../src/bitmaps/toolicons_traditional.png
ui_deployment.files += $$PWD/../src/bitmaps/toolicons_journeyman.png
ui_deployment.files += $$PWD/../src/bitmaps/toolicons_journeyman_flat.png
ui_deployment.path = /assets/uidata
INSTALLS += ui_deployment

gshhs_deployment.files += $$PWD/../data/gshhs/wdb_borders_c.b
gshhs_deployment.files += $$PWD/../data/gshhs/wdb_rivers_c.b
gshhs_deployment.files += $$PWD/../data/gshhs/poly-c-1.dat
gshhs_deployment.path = /assets/gshhs
INSTALLS += gshhs_deployment

# Dashboard------------------
#library
so_dashboard_plugin_deployment.files += $${OCPN_Base}/$${OCPN_Build}/plugins/dashboard_pi/libdashboard_pi.so
so_dashboard_plugin_deployment.path = /assets
INSTALLS += so_dashboard_plugin_deployment

#SVG
svg_dashboard_plugin_deployment.files += $$PWD/../plugins/dashboard_pi/data/Dashboard.svg
svg_dashboard_plugin_deployment.files += $$PWD/../plugins/dashboard_pi/data/Dashboard_toggled.svg
svg_dashboard_plugin_deployment.files += $$PWD/../plugins/dashboard_pi/data/plus.svg
svg_dashboard_plugin_deployment.files += $$PWD/../plugins/dashboard_pi/data/minus.svg
svg_dashboard_plugin_deployment.files += $$PWD/../plugins/dashboard_pi/data/dial.svg
svg_dashboard_plugin_deployment.files += $$PWD/../plugins/dashboard_pi/data/instrument.svg
svg_dashboard_plugin_deployment.path = /assets/dashboard_pi
INSTALLS += svg_dashboard_plugin_deployment

