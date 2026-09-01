if(BUILD_TESTING)
    # only with this definition will the KONQ_TESTS_EXPORT macro do something
    add_definitions(-DBUILD_TESTING)

    add_subdirectory( tests )
endif()

add_definitions(-DTRANSLATION_DOMAIN=\"hybrid-fm\")



########### libhybridfmprivate, shared with unit tests and sidebar modules ###############

set(hybridfmprivate_SRCS
   hfmhistorymanager.cpp # for unit tests
   hfmpixmapprovider.cpp # needed ?!?

   # for the sidebar history module
   hfmhistorymodel.cpp
   ksortfilterproxymodel.cpp
   hfmhistoryproxymodel.cpp
   hfmhistoryview.cpp
   hfmhistorysettings.cpp
   hfmurl.cpp
)

ecm_qt_declare_logging_category(hybridfmprivate_SRCS HEADER hfmdebug.h IDENTIFIER KONQUEROR_LOG CATEGORY_NAME hybridfm)

add_library(hybridfmprivate SHARED ${hybridfmprivate_SRCS})
target_link_libraries(hybridfmprivate
   KF5::I18n
   KF5::IconThemes
   KF5::Konq
   KF5::Parts
   KF5::KIOGui
)

if(KONQ_HAVE_X11)
  target_link_libraries(hybridfmprivate Qt5::X11Extras)
endif()


set_target_properties(hybridfmprivate PROPERTIES VERSION ${HYBRIDFM_LIB_VERSION} SOVERSION "5" )
install(TARGETS hybridfmprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

generate_export_header(hybridfmprivate BASE_NAME hybridfmprivate EXPORT_FILE_NAME hybridfmprivate_export.h)

########### hybrid-fm ###############

set(hybridfm_KDEINIT_SRCS
   hfmapplication.cpp
   hfmdebug.cpp
   hfmguiclients.cpp
   hfmbookmarkmenu.cpp
   hfmview.cpp
   hfmviewmanager.cpp
   hfmmouseeventfilter.cpp
   hfmmisc.cpp
   hfmdraggablelabel.cpp
   hfmframe.cpp
   hfmframevisitor.cpp
   hfmframestatusbar.cpp
   hfmframecontainer.cpp
   ktabbar.cpp
   ktabwidget.cpp
   hfmtabs.cpp
   hfmactions.cpp
   hfmsessiondlg.cpp
   hfmfactory.cpp
   hfmcombo.cpp
   delayedinitializer.cpp
   hfmanimatedlogo.cpp
   hfmmainwindow.cpp
   hfmmainwindowfactory.cpp
   hfmextensionmanager.cpp
   hfmbookmarkbar.cpp
   KonquerorAdaptor.cpp
   KonqMainWindowAdaptor.cpp
   KonqViewAdaptor.cpp
   hfmundomanager.cpp
   hfmclosedwindowsmanager.cpp
   hfmsessionmanager.cpp
   hfmcloseditem.cpp
   hfmhistorydialog.cpp
   hfmstatusbarmessagelabel.cpp
   hfmurl.cpp
   hfmbrowserinterface.cpp
   urlloader.cpp
   hfmsettings.cpp
   pluginmetadatautils.cpp
)

kconfig_add_kcfg_files(hybridfm_KDEINIT_SRCS hfmsettingsxt.kcfgc)
ki18n_wrap_ui(hybridfm_KDEINIT_SRCS hfm_sessiondlg_base.ui)
ki18n_wrap_ui(hybridfm_KDEINIT_SRCS hfm_newsessiondlg_base.ui)
qt5_add_resources(hybridfm_KDEINIT_SRCS hybrid-fm.qrc)

qt5_add_dbus_interface(hybridfm_KDEINIT_SRCS org.kde.Konqueror.Main.xml konqueror_interface)
qt5_add_dbus_adaptor(hybridfm_KDEINIT_SRCS org.kde.Konqueror.UndoManager.xml hfmclosedwindowsmanager.h KonqClosedWindowsManager konqclosedwindowsmanageradaptor KonqClosedWindowsManagerAdaptor)
qt5_add_dbus_interface(hybridfm_KDEINIT_SRCS org.kde.Konqueror.UndoManager.xml konqclosedwindowsmanager_interface)
qt5_add_dbus_adaptor(hybridfm_KDEINIT_SRCS org.kde.Konqueror.SessionManager.xml hfmsessionmanager.h KonqSessionManager konqsessionmanageradaptor KonqSessionManagerAdaptor)
qt5_add_dbus_interface(hybridfm_KDEINIT_SRCS org.kde.Konqueror.SessionManager.xml konqsessionmanager_interface)

# file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../pics/*-apps-hybrid-fm.png")
# ecm_add_app_icon(hybridfm_KDEINIT_SRCS ICONS ${ICONS_SRCS})
kf5_add_kdeinit_executable(hybrid-fm ${hybridfm_KDEINIT_SRCS} hfmmain.cpp)
target_link_libraries(kdeinit_hybrid-fm
   hybridfmprivate
   KF5::Archive
   KF5::KCMUtils
   KF5::Konq
   KF5::Parts
   KF5::DBusAddons
   KF5::Crash
   KF5::WindowSystem
   KF5::SonnetUi
)

if (KActivities_FOUND)
  target_link_libraries(kdeinit_hybrid-fm KF5::Activities)
endif (KActivities_FOUND)

if (NOT WIN32)
    install(TARGETS kdeinit_hybrid-fm  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
endif (NOT WIN32)
install(TARGETS hybrid-fm ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############
install( FILES hybrid-fm.kcfg  DESTINATION  ${KDE_INSTALL_KCFGDIR} )
install( FILES org.kde.Konqueror.Main.xml org.kde.Konqueror.MainWindow.xml DESTINATION ${KDE_INSTALL_DBUSINTERFACEDIR} )
