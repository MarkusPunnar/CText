#include "writingwidget.h"
#include "mainwindow.h"

#include <QWidget>
#include <QSaveFile>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>

#include <iostream>

WritingWidget::WritingWidget(MainWindow *parent) : QWidget(parent), m_mainWindow(parent) {
}

WritingWidget::~WritingWidget() {
}

bool WritingWidget::saveFile(QString fileName, QString savedData) {
    QSaveFile *writer = new QSaveFile(fileName);
    if (writer->open(QIODevice::WriteOnly)) {
        QTextStream stream (writer);
        stream << savedData;
        writer->commit();
        return true;
    } else {
        QMessageBox* message = new QMessageBox(this);
        message->setWindowTitle("Warning");
        message->setText("Saving the file failed!");
        message->open();
        return false;
    }
}

bool WritingWidget::saveAsFile(QString fileName, QString savedData) {
    QSaveFile *writer = new QSaveFile(fileName);
    if (writer->open(QIODevice::WriteOnly)) {
        QTextStream stream (writer);
        stream << savedData;
        writer->commit();
        return true;
    } else {
        QMessageBox* message = new QMessageBox(this);
        message->setWindowTitle("Warning");
        message->setText("Saving the file failed!");
        message->open();
        return false;
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
        QMessageBox* message = new QMessageBox(this);
        message->setWindowTitle("Warning");
        message->setText("Opening the file failed!");
        message->open();
    }
    return content;
}
