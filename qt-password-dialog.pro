# =============================================================================
# Parts of Qt
# =============================================================================

QT += widgets  # required to #include <QApplication>

# =============================================================================
# Overall configuration
# =============================================================================

CONFIG += mobility
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


# =============================================================================
# Compiler and linker flags
# =============================================================================

gcc {
    QMAKE_CXXFLAGS += -Werror  # warnings become errors
}

linux-gcc {
    QMAKE_CXXFLAGS += -Wno-deprecated-copy
}

gcc {
    QMAKE_CXXFLAGS += -fvisibility=hidden
}

# =============================================================================
# Build targets
# =============================================================================

TARGET = qt-password-dialog
TEMPLATE = app

# -----------------------------------------------------------------------------
# Architecture
# -----------------------------------------------------------------------------

linux : {
    CONFIG += static
}

# =============================================================================
# Source files
# =============================================================================

SOURCES += \
    main.cpp
