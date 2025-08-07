#include "ScreenBase.h"

#include <qcoreapplication.h>
#include <QFile>


ScreenBase::ScreenBase() {
    QFile file("../style/button_style.qss");
    file.open(QFile::ReadOnly);
    m_style = QLatin1String(file.readAll());
}

void ScreenBase::onExitButtonPressed() {
    QCoreApplication::exit(0);
}
