#include "mainwindow.h"
#include "writingwidget.h"
#include "tab.h"

#include "QPalette"
#include "QMenu"
#include "QString"
#include "QAction"
#include "QMenuBar"
#include "QDir"
#include "QFileDialog"
#include "QStringList"
#include "QActionEvent"
#include "QMessageBox"
#include "QResource"
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    initWidgets();
    initMenus();
}

MainWindow::~MainWindow() {
}

void MainWindow::initWidgets() {
    setWindowTitle(QString("CText - Untitled"));
    m_writingWidget = new WritingWidget(this);
    QDir currentDir = QDir::currentPath();
    Tab* newTab = new Tab(currentDir.absolutePath() + "/Untitled", this);
    connect(newTab, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    openTabs.push_back(newTab);
    m_tab = new QTabWidget(this);
    m_tab->setTabsClosable(true);
    m_tab->insertTab(0, newTab, "Untitled");
    this->setCentralWidget(m_tab);
    connect(m_tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(m_tab, SIGNAL(tabBarClicked(int)), this, SLOT(changeTab(int)));
    m_tab->show();
}

void MainWindow::initMenus() {

    m_fileMenu = new QMenu(this);
    m_fileMenu->setTitle(QString("&File"));
    menuBar()->addMenu(m_fileMenu);

    m_newAction = new QAction(this);
    m_newAction->setText(QString("&New"));
    m_newAction->setShortcut(QKeySequence(tr("Ctrl+n")));
    m_fileMenu->addAction(m_newAction);
    connect(m_newAction, &QAction::triggered, this, &MainWindow::openNewFile);

    m_openAction = new QAction(this);
    m_openAction->setText(QString("&Open"));
    m_fileMenu->addAction(m_openAction);
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openFileFromDisk);

    m_saveAction = new QAction(this);
    m_saveAction->setText(QString("&Save"));
    m_saveAction->setShortcut(QKeySequence(tr("Ctrl+s")));
    m_fileMenu->addAction(m_saveAction);
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveFileToDisk);

    m_saveAsAction = new QAction(this);
    m_saveAsAction->setText("&Save as...");
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

    m_boldFontAction = new QAction(this);
    m_boldFontAction->setIcon(QIcon(":/images/bold.png"));
    m_boldFontAction->setShortcut(QKeySequence(tr("Ctrl+b")));
    menuBar()->addAction(m_boldFontAction);
    connect(m_boldFontAction, &QAction::triggered,
            this, &MainWindow::changeFontToBold);

    m_italicFontAction= new QAction(this);
    m_italicFontAction->setIcon(QIcon(":/images/italic.png"));
    m_italicFontAction->setShortcut(QKeySequence(tr("Ctrl+i")));
    menuBar()->addAction(m_italicFontAction);
    connect(m_italicFontAction, &QAction::triggered,
            this, &MainWindow::changeFontToItalic);

    m_colourMenu = new QMenu(this);
    m_colourMenu->setTitle(QString("&Colour"));
    menuBar()->addMenu(m_colourMenu);

    m_redFontAction = new QAction(this);
    m_redFontAction->setText(QString("&Red"));
    m_redFontAction->setIcon(QIcon(":/images/red.png"));
    m_colourMenu->addAction(m_redFontAction);
    connect(m_redFontAction, &QAction::triggered, this, &MainWindow::changeFontToRed);

    m_blueFontAction = new QAction(this);
    m_blueFontAction->setText(QString("&Blue"));
    m_blueFontAction->setIcon(QIcon(":/images/blue.png"));
    m_colourMenu->addAction(m_blueFontAction);
    connect(m_blueFontAction, &QAction::triggered, this, &MainWindow::changeFontToBlue);

    m_greenFontAction = new QAction(this);
    m_greenFontAction->setText(QString("&Green"));
    m_greenFontAction->setIcon(QIcon(":/images/green.png"));
    m_colourMenu->addAction(m_greenFontAction);
    connect(m_greenFontAction, &QAction::triggered, this, &MainWindow::changeFontToGreen);

    m_blackFontAction = new QAction(this);
    m_blackFontAction->setText("&Black");
    m_blackFontAction->setIcon(QIcon(":/images/black.jpeg"));
    m_colourMenu->addAction(m_blackFontAction);
    connect(m_blackFontAction, &QAction::triggered, this, &MainWindow::changeFontToBlack);


}

void MainWindow::saveFileToDisk() {
    QDir currentDir = QDir::currentPath();
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QString savePath = currentTab->openFile;
    if (savePath == currentDir.absolutePath() + "/Untitled") {
        QFileDialog *dialog = new QFileDialog(this);
        if (dialog->exec()) {
            QStringList fileList = dialog->selectedFiles();
            if (fileList.size() == 0) {
                return;
            }
            savePath = fileList.at(0);
            currentTab->openFile = savePath;
        }
    }
    QString fileContent = currentTab->toPlainText();
    m_writingWidget->saveFile(savePath, fileContent);
    currentTab->savedState = fileContent;
    m_tab->setTabIcon(m_tab->currentIndex(), QIcon());
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::saveAsFileToDisk() {
    QString savePath;
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFileDialog *dialog = new QFileDialog(this);
    if (dialog->exec()) {
        QStringList fileList = dialog->selectedFiles();
        if (fileList.size() == 0) {
            return;
        }
        savePath = fileList.at(0);
    }
    QString fileContent = currentTab->toPlainText();
    m_writingWidget->saveFile(savePath, fileContent);
    currentTab->openFile = savePath;
    currentTab->savedState = fileContent;
    m_tab->setTabIcon(m_tab->currentIndex(), QIcon());
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::openFileFromDisk() {
    QFileDialog *dialog = new QFileDialog(this);
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QString filePath;
    if (dialog->exec()) {
        filePath = dialog->selectedFiles().at(0);
    }
    QString fileContent = m_writingWidget->openFile(filePath);
    currentTab->setPlainText(fileContent);
    currentTab->savedState = fileContent;
    emit onTextChanged();
    currentTab->openFile = filePath;
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::openNewFile() {
    Tab* newTab = new Tab(QDir::currentPath() + "/Untitled", this);
    connect(newTab, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    m_tab->insertTab(openTabs.size(), newTab, "Untitled");
    openTabs.push_back(newTab);
    m_tab->setCurrentIndex(openTabs.size() - 1);
    this->changeTab(m_tab->currentIndex());
    newTab->show();
}

QString MainWindow::changeTitleFile() {
    QStringList splitPath = openTabs.at(m_tab->currentIndex())->openFile.split('/', QString::SkipEmptyParts);
    setWindowTitle("CText - " + splitPath.at(splitPath.size() - 1));
    return splitPath.at(splitPath.size() - 1);
}

void MainWindow::closeTab(int index) {
    if (index == -1) {
        return;
    }
    if (openTabs.at(index)->savedState != openTabs.at(index)->toPlainText()) {
        QMessageBox::StandardButton confirm;
        confirm = QMessageBox::question(this, "Confirmation",
                                        "You have unsaved changes. Are you sure you want to close this tab?",
                                        QMessageBox::Yes | QMessageBox::No);
        if (confirm == QMessageBox::Yes) {
            openTabs.erase(openTabs.begin() + index);
            m_tab->removeTab(index);
            if (openTabs.size() == 0) {
                this->close();
            }
        }
    } else {
        openTabs.erase(openTabs.begin() + index);
        m_tab->removeTab(index);
        if (openTabs.size() == 0) {
            this->close();
        }
    }
}

void MainWindow::changeFontToBold() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    if (currentTab->fontWeight() > 50) {
        currentTab->setFontWeight(QFont::Normal);
    } else {
     currentTab->setFontWeight(QFont::Bold);
    }
}


void MainWindow::changeFontToItalic() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    currentTab->setFontItalic(!currentTab->fontItalic());
}

void MainWindow::changeFontToRed() {
        openTabs.at(m_tab->currentIndex())->setTextColor(QColor(255,0,0));
}

void MainWindow::changeFontToBlue() {
        openTabs.at(m_tab->currentIndex())->setTextColor(QColor(0,0,255));
}

void MainWindow::changeFontToGreen() {
        openTabs.at(m_tab->currentIndex())->setTextColor(QColor(0,255,0));
}

void MainWindow::changeFontToBlack() {
        openTabs.at(m_tab->currentIndex())->setTextColor(QColor(0,0,0));
}

void MainWindow::onTextChanged() {
    Tab *currentTab = openTabs.at(m_tab->currentIndex());
    QString newText = currentTab->toPlainText();
    if ((newText != openTabs.at(m_tab->currentIndex())->savedState) & (m_tab->tabIcon(m_tab->currentIndex()).isNull())) {
        m_tab->setTabIcon(m_tab->currentIndex(), QIcon(":/images/save.png"));
    }
    if ((newText == openTabs.at(m_tab->currentIndex())->savedState) & (!m_tab->tabIcon(m_tab->currentIndex()).isNull())) {
        m_tab->setTabIcon(m_tab->currentIndex(), QIcon());
    }
}

void MainWindow::changeTab(int index) {
    QString tabText = m_tab->tabText(index);
    if (tabText.at(0) == '&') {
        this->setWindowTitle(QString("CText - ").append(QStringRef(&tabText, 1, tabText.length() - 1)));
    } else {
        this->setWindowTitle("CText - " + tabText);
    }
}
