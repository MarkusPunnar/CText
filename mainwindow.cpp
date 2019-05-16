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
#include "QActionEvent"
#include "QMessageBox"

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
    connect(editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    openFileVector.push_back(editor);
    m_tab = new QTabWidget(this);
    m_tab->setTabsClosable(true);
    m_tab->insertTab(0, editor, "Untitled");
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
    menuBar()->addAction(m_boldFontAction);
    connect(m_boldFontAction, &QAction::triggered,
            this, &MainWindow::changeFontToBold);

    m_italicFontAction= new QAction(this);
    m_italicFontAction->setIcon(QIcon(":/images/italic.png"));
    menuBar()->addAction(m_italicFontAction);
    connect(m_italicFontAction, &QAction::triggered,
            this, &MainWindow::changeFontToItalic);

    m_colourMenu = new QMenu(this);
    m_colourMenu->setTitle(QString("&Text colour"));
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
    QString savePath;
    if (currentOpenFile == currentDir.absolutePath() + "/Untitled") {
        QFileDialog *dialog = new QFileDialog(this);
        if (dialog->exec()) {
            QStringList fileList = dialog->selectedFiles();
            if (fileList.size() == 0) {
                return;
            }
            savePath = fileList.at(0);
        }
    } else {
        savePath = currentOpenFile;
    }
    m_writingWidget->saveFile(savePath, openFileVector.at(m_tab->currentIndex())->toPlainText());
    currentOpenFile = savePath;
    lastSavedState = openFileVector.at(m_tab->currentIndex())->toPlainText();
    m_tab->setTabIcon(m_tab->currentIndex(), QIcon());
    QString newName = this->changeTitleFile();
    m_tab->setTabText(m_tab->currentIndex(), newName);
}

void MainWindow::saveAsFileToDisk() {
    QString savePath;
    QFileDialog *dialog = new QFileDialog(this);
    if (dialog->exec()) {
        QStringList fileList = dialog->selectedFiles();
        if (fileList.size() == 0) {
            return;
        }
        savePath = fileList.at(0);
    }
    m_writingWidget->saveFile(savePath, openFileVector.at(m_tab->currentIndex())->toPlainText());
    currentOpenFile = savePath;
    lastSavedState = openFileVector.at(m_tab->currentIndex())->toPlainText();
    m_tab->setTabIcon(m_tab->currentIndex(), QIcon());
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
    if (lastSavedState != openFileVector.at(m_tab->currentIndex())->toPlainText()) {
        QMessageBox::StandardButton confirm;
        confirm = QMessageBox::question(this, "Confirmation",
                                        "You have unsaved changes. Are you sure you want to close this tab?",
                                        QMessageBox::Yes | QMessageBox::No);
        if (confirm == QMessageBox::Yes) {
            openFileVector.erase(openFileVector.begin()+index);
            m_tab->removeTab(index);
            if (openFileVector.size() == 0) {
                this->close();
            }
        }
    } else {
        openFileVector.erase(openFileVector.begin()+index);
        m_tab->removeTab(index);
        if (openFileVector.size() == 0) {
            this->close();
        }
    }
}

void MainWindow::changeFontToBold() {
    if (openFileVector.at(m_tab->currentIndex())->fontWeight() > 50) {
        openFileVector.at(m_tab->currentIndex())->setFontWeight(QFont::Normal);
    } else {
     openFileVector.at(m_tab->currentIndex())->setFontWeight(QFont::Bold);
    }
}


void MainWindow::changeFontToItalic() {
    if (openFileVector.at(m_tab->currentIndex())->fontItalic()) {
        openFileVector.at(m_tab->currentIndex())->setFontItalic(false);
    } else {
        openFileVector.at(m_tab->currentIndex())->setFontItalic(true);
    }
}

void MainWindow::changeFontToRed() {
        openFileVector.at(m_tab->currentIndex())->setTextColor(QColor(255,0,0));
}

void MainWindow::changeFontToBlue() {
        openFileVector.at(m_tab->currentIndex())->setTextColor(QColor(0,0,255));
}

void MainWindow::changeFontToGreen() {
        openFileVector.at(m_tab->currentIndex())->setTextColor(QColor(0,255,0));
}

void MainWindow::changeFontToBlack() {
        openFileVector.at(m_tab->currentIndex())->setTextColor(QColor(0,0,0));
}

void MainWindow::onTextChanged() {
    QString newText = openFileVector.at(m_tab->currentIndex())->toPlainText();
    if ((newText != lastSavedState) & (m_tab->tabIcon(m_tab->currentIndex()).isNull())) {
        m_tab->setTabIcon(m_tab->currentIndex(), QIcon(":/images/save.png"));
    }
    if ((newText == lastSavedState) & (!m_tab->tabIcon(m_tab->currentIndex()).isNull())) {
        m_tab->setTabIcon(m_tab->currentIndex(), QIcon());
    }
}

void MainWindow::changeTab(int index) {
    lastSavedState = openFileVector.at(index)->toPlainText();
}
