include(LiriAuroraClientMacros.cmake)

liri_add_module(AuroraClient
    DESCRIPTION
        "Wayland client library for Qt applications"
    SOURCES
        liricolorpickerv1.cpp liricolorpickerv1.h liricolorpickerv1_p.h
        lirilockscreenv1.cpp lirilockscreenv1_p.h lirilockscreenv1.h
        lirimodalv1.cpp lirimodalv1.h lirimodalv1_p.h
        lirishellv1.cpp lirishellv1.h lirishellv1_p.h
        utils_p.h
        wlrexportdmabufv1.cpp wlrexportdmabufv1.h wlrexportdmabufv1_p.h
        wlrforeigntoplevelmanagementv1.cpp wlrforeigntoplevelmanagementv1.h wlrforeigntoplevelmanagementv1_p.h
        wlrlayersurfacev1.cpp wlrlayersurfacev1.h wlrlayersurfacev1_p.h
        wlroutputmanagementv1.cpp wlroutputmanagementv1.h wlroutputmanagementv1_p.h
        wlrscreencopyv1.cpp wlrscreencopyv1.h wlrscreencopyv1_p.h
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::WaylandClient
    LIBRARIES
        Qt::GuiPrivate
    PKGCONFIG_DEPENDENCIES
        Qt${QT_DEFAULT_MAJOR_VERSION}Core
        Qt${QT_DEFAULT_MAJOR_VERSION}Gui
        Qt${QT_DEFAULT_MAJOR_VERSION}WaylandClient
)

liri_generate_wayland_protocol_client_sources(AuroraClient
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/liri-color-picker-unstable-v1.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/liri-lockscreen-unstable-v1.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/liri-shell-unstable-v1.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-export-dmabuf-unstable-v1.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-foreign-toplevel-management-unstable-v1.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-output-management-unstable-v1.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-screencopy-unstable-v1.xml
)

liri_finalize_module(AuroraClient)
