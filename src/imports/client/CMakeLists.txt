liri_add_qml_plugin(AuroraClientQmlPlugin
    MODULE_PATH
        "Aurora/Client"
    VERSION
        "1.0"
    OUTPUT_NAME
        auroraclientplugin
    SOURCES
        lirishortcutqml.cpp lirishortcutqml.h
        plugin.cpp
        wlrlayersurfacev1qml.cpp wlrlayersurfacev1qml.h
    QML_FILES
        qmldir
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
    PUBLIC_LIBRARIES
        Qt::Qml
        Qt::Quick
        Liri::AuroraClient
)

liri_finalize_qml_plugin(AuroraClientQmlPlugin)
