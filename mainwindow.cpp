#include "mainwindow.h"
#include "writingwidget.h"

#include "QPalette"
#include "QMenu"
#include "QString"
#include "QAction"
#include "QMenuBar"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    this->setFixedSize(800,600);
    initWidgets();
    initMenus();
}

MainWindow::~MainWindow() {
}

void MainWindow::initWidgets() {
    setWindowTitle(QString("CText"));
    m_writingWidget = new WritingWidget(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    m_writingWidget->setAutoFillBackground(true);
    m_writingWidget->setPalette(pal);
    this->setCentralWidget(m_writingWidget);
}

void MainWindow::initMenus() {

    m_fileMenu = new QMenu(this);
    m_fileMenu->setTitle(QString("&File"));
    menuBar()->addMenu(m_fileMenu);

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
