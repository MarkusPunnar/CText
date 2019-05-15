#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    QDesktopWidget desktop;
    window.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window.size(), application.desktop()->availableGeometry()));
    window.resize(800, 600);
    window.show();
    return application.exec();
}
