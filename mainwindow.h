#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QString>
#include "QTabWidget"
#include "QTabBar"

#include "vector"

class WritingWidget;
class QMenu;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        QString currentOpenFile;

    public slots:
        void saveFileToDisk();
        void saveAsFileToDisk();
        void openFileFromDisk();
        void openNewFile();
        void closeTab(int index);
        void changeFontToBold();
        void changeFontToItalic();

    protected:
        void initWidgets();
        void initMenus();
        QString changeTitleFile();

        QTabWidget *m_tab;
        WritingWidget *m_writingWidget;

        std::vector<QTextEdit*> openFileVector;

        QMenu *m_fileMenu;
            QAction *m_newAction;
            QAction *m_openAction;
            QAction *m_saveAction;
            QAction *m_saveAsAction;
            QAction *m_quitAction;
        QMenu *m_helpMenu;
        QAction *m_boldFontAction;
        QAction *m_italicFontAction;
};

#endif // MAINWINDOW_H
