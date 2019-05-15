#include "mainwindow.h"
#include "writingwidget.h"

#include "QPalette"
#include "QMenu"
#include "QString"
#include "QAction"
#include "QMenuBar"
#include "QDir"
#include "QFileDialog"
#include "QStringList"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    QDir currentDir = QDir::currentPath();
    currentOpenFile = currentDir.absolutePath() + "/Untitled";
    initWidgets();
    initMenus();
}

MainWindow::~MainWindow() {
}

void MainWindow::initWidgets() {
    setWindowTitle(QString("CText - Untitled"));
    m_writingWidget = new WritingWidget(this);
    m_editor = new QTextEdit(this);
    this->setCentralWidget(m_editor);
}

void MainWindow::initMenus() {

    m_fileMenu = new QMenu(this);
    m_fileMenu->setTitle(QString("&File"));
    menuBar()->addMenu(m_fileMenu);

    m_newAction = new QAction(this);
    m_newAction->setText(QString("&New"));
    m_fileMenu->addAction(m_newAction);
    connect(m_newAction, &QAction::triggered, this, &MainWindow::openNewFile);

    m_openAction = new QAction(this);
    m_openAction->setText(QString("&Open"));
    m_fileMenu->addAction(m_openAction);
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openFileFromDisk);

    m_saveAction = new QAction(this);
    m_saveAction->setText(QString("&Save"));
    m_fileMenu->addAction(m_saveAction);
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveFileToDisk);

    m_saveAsAction = new QAction(this);
    m_saveAsAction->setText(QString("&Save as..."));
    m_fileMenu->addAction(m_saveAsAction);
    connect(m_saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFileToDisk);

    m_quitAction = new QAction(this);
    m_quitAction->setMenuRole(QAction::QuitRole);
    m_quitAction->setText(QString("&Quit"));
    m_fileMenu->addAction(m_quitAction);
    connect(m_quitAction, SIGNAL(triggered()),
            this, SLOT(close()));


    m_helpMenu = new QMenu(this);
    m_helpMenu->setTitle(QString("&Help"));
    menuBar()->addMenu(m_helpMenu);
}

void MainWindow::saveFileToDisk() {
    QDir currentDir = QDir::currentPath();
    QString savePath;
    if (currentOpenFile == currentDir.absolutePath() + "/Untitled") {
        QFileDialog *dialog = new QFileDialog(this);
        if (dialog->exec()) {
            savePath = dialog->selectedFiles().at(0);
        }
    } else {
        savePath = currentOpenFile;
    }
    m_writingWidget->saveFile(savePath, m_editor->toPlainText());
    currentOpenFile = savePath;
    this->changeTitleFile();
}

void MainWindow::saveAsFileToDisk() {
    QString savePath;

        QFileDialog *dialog = new QFileDialog(this);
        if (dialog->exec()) {
            savePath = dialog->selectedFiles().at(0);
        }
    m_writingWidget->saveFile(savePath, m_editor->toPlainText());
    currentOpenFile = savePath;
    this->changeTitleFile();
}

void MainWindow::openFileFromDisk() {
    QFileDialog *dialog = new QFileDialog(this);
    QString filePath;
    if (dialog->exec()) {
        filePath = dialog->selectedFiles().at(0);
    }
    QString fileContent = m_writingWidget->openFile(filePath);
    m_editor->setPlainText(fileContent);
    currentOpenFile = filePath;
    this->changeTitleFile();
}

void MainWindow::openNewFile() {
    /* TODO */
}

void MainWindow::changeTitleFile() {
    QStringList splitPath = currentOpenFile.split('/', QString::SkipEmptyParts);
    setWindowTitle("CText - " + splitPath.at(splitPath.size() - 1));
}
