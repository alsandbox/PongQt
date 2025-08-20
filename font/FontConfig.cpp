#include "FontConfig.h"
#include <QFontDatabase>
#include <QDebug>

QFont FontConfig::font;

void FontConfig::init() {
    static bool initialized = false;
    if (initialized) return;

    int id = QFontDatabase::addApplicationFont(":/font/bit5x3.ttf");
    if (id != -1) {
        const QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        font = QFont(family, 14, QFont::Bold);
    } else {
        qWarning() << "Font load failed.";
    }

    initialized = true;
}