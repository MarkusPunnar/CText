#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QString>
#include "QTabWidget"
#include "QTabBar"
#include "tab.h"
#include "mainwindow.h"

#include "vector"

class WritingWidget;
class QMenu;
class Tab;
class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void saveFileToDisk();
        void saveAsFileToDisk();
        void openFileFromDisk();
        void openNewFile();
        void closeTab(int index);
        void changeFontToBold();
        void changeFontToItalic();
        void changeFontToRed();
        void changeFontToBlue();
        void changeFontToGreen();
        void changeFontToBlack();
        void changeFontToArial();
        void changeFontToTimes();
        void changeFontToCalibri();
        void changeFontSize8();
        void changeFontSize10();
        void changeFontSize12();
        void changeFontSize14();
        void changeFontSize16();
        void changeFontSize18();
        void changeFontSize20();
        void onTextChanged();
        void changeTab(int index);

    protected:
        void initWidgets();
        void initMenus();
        QString changeTitleFile();

        QTabWidget *m_tab;
        WritingWidget *m_writingWidget;

        std::vector<Tab*> openTabs;

        QMenu *m_fileMenu;
            QAction *m_newAction;
            QAction *m_openAction;
            QAction *m_saveAction;
            QAction *m_saveAsAction;
            QAction *m_quitAction;
        QMenu *m_helpMenu;
        QMenu *m_stylingMenu;
            QAction *m_boldFontAction;
            QAction *m_italicFontAction;
        QMenu *m_fontMenu;
            QAction *m_arialFontAction;
            QAction *m_timesFontAction;
            QAction *m_calibriFontAction;
        QMenu *m_colourMenu;
            QAction *m_redFontAction;
            QAction *m_blueFontAction;
            QAction *m_greenFontAction;
            QAction *m_blackFontAction;
        QMenu *m_sizeMenu;
            QAction *m_8FontAction;
            QAction *m_10FontAction;
            QAction *m_12FontAction;
            QAction *m_14FontAction;
            QAction *m_16FontAction;
            QAction *m_18FontAction;
            QAction *m_20FontAction;
};

#endif // MAINWINDOW_H
