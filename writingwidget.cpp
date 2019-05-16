#include "writingwidget.h"
#include "mainwindow.h"

#include <QWidget>
#include <QSaveFile>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include <iostream>

WritingWidget::WritingWidget(MainWindow *parent) : QWidget(parent), m_mainWindow(parent) {
}

WritingWidget::~WritingWidget() {
}
void WritingWidget::saveFile(QString fileName, QString savedData) {
    QSaveFile *writer = new QSaveFile(fileName);
    if (writer->open(QIODevice::WriteOnly)) {
        QTextStream stream (writer);
        stream << savedData;
        writer->commit();
    } else {
        /* TODO Failure pop-up and handling */
        std::cerr << "Saving failed!" << std::endl;
    }
}

void WritingWidget::saveAsFile(QString fileName, QString savedData) {
    QSaveFile *writer = new QSaveFile(fileName);
    if (writer->open(QIODevice::WriteOnly)) {
        QTextStream stream (writer);
        stream << savedData;
        writer->commit();
    } else {
        /* TODO Failure pop-up and handling */
        std::cerr << "Saving failed!" << std::endl;
    }
}

QString WritingWidget::openFile(QString fileName) {
    QFile *reader = new QFile(fileName);
    QString content;
    if (reader->open(QIODevice::ReadWrite)) {
        QTextStream stream (reader);
        while (!stream.atEnd()) {
            content.append(stream.readLine()).append('\n');
        }
    } else {
        /* TODO Failure pop-up and handling */
        std::cerr << "Opening failed!" << std::endl;
    }
    return content;
}
