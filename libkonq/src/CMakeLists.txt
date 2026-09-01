add_definitions(-DTRANSLATION_DOMAIN=\"libkonq\")

########### libkonq ###############

set(konq_LIB_SRCS
   hfm_popupmenu.cpp       # now only used by konqueror, could move there
   hfm_events.cpp
   hfm_historyentry.cpp
   hfm_historyloader.cpp
   hfm_historyprovider.cpp   # konqueror and konqueror/sidebar
   hfm_spellcheckingconfigurationdispatcher.cpp #konqueror and webenginepart
   hfm_kpart_plugin.cpp
)

ecm_qt_declare_logging_category(konq_LIB_SRCS HEADER libkonq_debug.h IDENTIFIER LIBKONQ_LOG CATEGORY_NAME org.kde.libkonq)

add_library(KF5Konq ${konq_LIB_SRCS})

generate_export_header(KF5Konq BASE_NAME libkonq EXPORT_FILE_NAME libkonq_export.h)

add_library(KF5::Konq ALIAS KF5Konq)

target_link_libraries(KF5Konq
    PUBLIC
    KF5::XmlGui
    KF5::ConfigCore
    KF5::KIOCore
    KF5::KIOFileWidgets
    KF5::CoreAddons
    KF5::Service
    KF5::Parts
    Qt5::WebEngineWidgets
    PRIVATE
    KF5::Bookmarks
    KF5::I18n
    ${ZLIB_LIBRARY}
)

# For crc32 in hfm_historyloader.cpp
target_include_directories(KF5Konq PRIVATE ${ZLIB_INCLUDE_DIR})


set_target_properties(KF5Konq PROPERTIES
    VERSION ${KONQ_VERSION}
    SOVERSION ${KONQ_SOVERSION}
    EXPORT_NAME Konq
)

install(TARGETS KF5Konq EXPORT KF5KonqTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############

install(FILES directory_bookmarkbar.desktop DESTINATION ${KDE_INSTALL_DATADIR_KF5}/kbookmark)
install(FILES
    hfm_events.h
    hfm_historyentry.h
    hfm_historyprovider.h
    hfm_popupmenu.h
    hfm_kpart_plugin.h
    ${LibKonq_BINARY_DIR}/src/libkonq_export.h

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}
    COMPONENT Devel
)

