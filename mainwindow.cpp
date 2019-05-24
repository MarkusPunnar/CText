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
#include <QFontDatabase>
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
    newTab->setFont(QFont("Arial",12));
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

    m_stylingMenu = new QMenu(this);
    m_stylingMenu->setTitle(QString("&Styling"));
    menuBar()->addMenu(m_stylingMenu);

    m_boldFontAction = new QAction(this);
    m_boldFontAction->setIcon(QIcon(":/images/bold.png"));
    m_boldFontAction->setText(QString("Bold"));
    m_boldFontAction->setShortcut(QKeySequence(tr("Ctrl+b")));
    m_stylingMenu->addAction(m_boldFontAction);
    connect(m_boldFontAction, &QAction::triggered,
            this, &MainWindow::changeFontToBold);

    m_italicFontAction= new QAction(this);
    m_italicFontAction->setIcon(QIcon(":/images/italic.png"));
    m_italicFontAction->setText(QString("Italic"));
    m_italicFontAction->setShortcut(QKeySequence(tr("Ctrl+i")));
    m_stylingMenu->addAction(m_italicFontAction);
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

    m_fontMenu = new QMenu(this);
    m_fontMenu->setTitle(QString("&Font"));
    menuBar()->addMenu(m_fontMenu);

    m_arialFontAction = new QAction(this);
    m_arialFontAction->setText("&Arial");
    m_fontMenu->addAction(m_arialFontAction);
    connect(m_arialFontAction, &QAction::triggered, this, &MainWindow::changeFontToArial);

    m_timesFontAction = new QAction(this);
    m_timesFontAction->setText("&Times New Roman");
    m_fontMenu->addAction(m_timesFontAction);
    connect(m_timesFontAction, &QAction::triggered, this, &MainWindow::changeFontToTimes);

    m_calibriFontAction = new QAction(this);
    m_calibriFontAction->setText("&Calibri");
    m_fontMenu->addAction(m_calibriFontAction);
    connect(m_calibriFontAction, &QAction::triggered, this, &MainWindow::changeFontToCalibri);

    m_sizeMenu = new QMenu(this);
    m_sizeMenu->setTitle(QString("&Size"));
    menuBar()->addMenu(m_sizeMenu);

    m_8FontAction = new QAction(this);
    m_8FontAction->setText("&8");
    m_sizeMenu->addAction(m_8FontAction);
    connect(m_8FontAction, &QAction::triggered, this, &MainWindow::changeFontSize8);

    m_10FontAction = new QAction(this);
    m_10FontAction->setText("&10");
    m_sizeMenu->addAction(m_10FontAction);
    connect(m_10FontAction, &QAction::triggered, this, &MainWindow::changeFontSize10);

    m_12FontAction = new QAction(this);
    m_12FontAction->setText("&12");
    m_sizeMenu->addAction(m_12FontAction);
    connect(m_12FontAction, &QAction::triggered, this, &MainWindow::changeFontSize12);

    m_14FontAction = new QAction(this);
    m_14FontAction->setText("&14");
    m_sizeMenu->addAction(m_14FontAction);
    connect(m_14FontAction, &QAction::triggered, this, &MainWindow::changeFontSize14);

    m_16FontAction = new QAction(this);
    m_16FontAction->setText("&16");
    m_sizeMenu->addAction(m_16FontAction);
    connect(m_16FontAction, &QAction::triggered, this, &MainWindow::changeFontSize16);

    m_18FontAction = new QAction(this);
    m_18FontAction->setText("&18");
    m_sizeMenu->addAction(m_18FontAction);
    connect(m_18FontAction, &QAction::triggered, this, &MainWindow::changeFontSize18);

    m_20FontAction = new QAction(this);
    m_20FontAction->setText("&20");
    m_sizeMenu->addAction(m_20FontAction);
    connect(m_20FontAction, &QAction::triggered, this, &MainWindow::changeFontSize20);

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

void MainWindow::changeFontToArial() {
    QFont font("Arial");
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    if (currentTab->fontWeight() > 50) {
        font.setWeight(QFont::Bold);
    }
    font.setItalic(currentTab->fontItalic());
    font.setPixelSize(currentTab->fontSize);

    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontToTimes() {
    QFont font("Times [Adobe]");
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    if (currentTab->fontWeight() > 50) {
        font.setWeight(QFont::Bold);
    }
    font.setItalic(currentTab->fontItalic());
    font.setPixelSize(currentTab->fontSize);

    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontToCalibri() {
    QFont font("Calibri");
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    if (currentTab->fontWeight() > 50) {
        font.setWeight(QFont::Bold);
    }
    font.setItalic(currentTab->fontItalic());
    font.setPixelSize(currentTab->fontSize);

    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize8() {
     Tab* currentTab = openTabs.at(m_tab->currentIndex());
     QFont font(currentTab->font());
     font.setPixelSize(12);
     currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize10() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFont font(currentTab->font());
    font.setPixelSize(14);
    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize12() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFont font(currentTab->font());
    font.setPixelSize(16);
    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize14() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFont font(currentTab->font());
    font.setPixelSize(18);
    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize16() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFont font(currentTab->font());
    font.setPixelSize(20);
    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize18() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFont font(currentTab->font());
    font.setPixelSize(22);
    currentTab->setCurrentFont(font);
}

void MainWindow::changeFontSize20() {
    Tab* currentTab = openTabs.at(m_tab->currentIndex());
    QFont font(currentTab->font());
    font.setPixelSize(24);
    currentTab->setCurrentFont(font);
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
