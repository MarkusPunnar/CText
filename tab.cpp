#include "tab.h"
#include "mainwindow.h"

Tab::Tab(QString file, MainWindow* window) : QTextEdit(window) {
    openFile = file;
    savedState = "";
    currentFont = QFont("Times New Roman", 12);
    fontSize = 12;
}

Tab::~Tab() {

}
