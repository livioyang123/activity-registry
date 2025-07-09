#include <iostream>
#include <QApplication>
#include "gui/ActivityWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ActivityWindow window;
    window.show();

    return app.exec();

}
