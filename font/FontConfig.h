#ifndef FONTCONFIG_H
#define FONTCONFIG_H

#include <QFontDatabase>


struct FontConfig {
    static QFont font;
    static void init();
};



#endif //FONTCONFIG_H
