# Generated from minimal.pro.

#####################################################################
## QAmigaIntegrationPlugin Plugin:
#####################################################################

# qt_find_package(WrapFREETYPE PROVIDED_TARGETS WrapFREETYPE::WrapFREETYPE) # special case

qt_internal_add_plugin(QAmigaIntegrationPlugin
    OUTPUT_NAME amiga
    PLUGIN_TYPE platforms
    DEFAULT_IF ${QT_QPA_DEFAULT_PLATFORM} MATCHES amiga # special case
    SOURCES
        main.cpp
        qamigacommon.h qamigacommon.cpp
        qamigaeventdispatcher.h qamigaeventdispatcher.cpp
        qamigaglbackingstore.cpp qamigaglbackingstore.h
        qamigaglcontext.cpp qamigaglcontext.h
        # qamigaglwindow.cpp qamigaglwindow.h
        qamigaintegration.cpp qamigaintegration.h
        qamigaoffscreensurface.h qamigaoffscreensurface.cpp
        qamigawindow.cpp qamigawindow.h
    DEFINES
        QT_NO_FOREACH
    LIBRARIES
        Qt::Core
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        Qt::OpenGL
        Qt::OpenGLPrivate
)

#### Keys ignored in scope 1:.:.:minimal.pro:<TRUE>:
# OTHER_FILES = "minimal.json"

## Scopes:
#####################################################################

# qt_internal_extend_target(QAmigaIntegrationPlugin CONDITION QT_FEATURE_freetype
#     LIBRARIES
#         WrapFREETYPE::WrapFREETYPE
# )

#### Keys ignored in scope 3:.:.:minimal.pro:NOT TARGET___equals____ss_QT_DEFAULT_QPA_PLUGIN:
# PLUGIN_EXTENDS = "-"
