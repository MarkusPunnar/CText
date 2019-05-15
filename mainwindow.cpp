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
    QTextEdit *editor = new QTextEdit(this);
    openFileVector.push_back(editor);
    m_tab = new QTabWidget(this);
    m_tab->setTabsClosable(true);
    m_tab->insertTab(0, editor, "Untitled");
    this->setCentralWidget(m_tab);
    connect(m_tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    m_tab->show();
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
    m_writingWidget->saveFile(savePath, openFileVector.at(m_tab->currentIndex())->toPlainText());
    currentOpenFile = savePath;
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::saveAsFileToDisk() {
    QString savePath;
    QFileDialog *dialog = new QFileDialog(this);
    if (dialog->exec()) {
        savePath = dialog->selectedFiles().at(0);
    }
    m_writingWidget->saveFile(savePath, openFileVector.at(m_tab->currentIndex())->toPlainText());
    currentOpenFile = savePath;
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::openFileFromDisk() {
    QFileDialog *dialog = new QFileDialog(this);
    QString filePath;
    if (dialog->exec()) {
        filePath = dialog->selectedFiles().at(0);
    }
    QString fileContent = m_writingWidget->openFile(filePath);
    openFileVector.at(m_tab->currentIndex())->setPlainText(fileContent);
    currentOpenFile = filePath;
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::openNewFile() {
    QTextEdit *newTab = new QTextEdit(this);
    m_tab->insertTab(openFileVector.size(), newTab, "Untitled");
    openFileVector.push_back(newTab);
    newTab->show();
}

QString MainWindow::changeTitleFile() {
    QStringList splitPath = currentOpenFile.split('/', QString::SkipEmptyParts);
    setWindowTitle("CText - " + splitPath.at(splitPath.size() - 1));
    return splitPath.at(splitPath.size() - 1);
}

void MainWindow::closeTab(int index) {
    if (index == -1) {
        return;
    }
    openFileVector.erase(openFileVector.begin()+index);
    m_tab->removeTab(index);
    if (openFileVector.size() == 0) {
        this->close();
    }
}
