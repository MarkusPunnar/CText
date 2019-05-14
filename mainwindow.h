#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class WritingWidget;
class QMenu;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initWidgets();
    void initMenus();

    WritingWidget *m_writingWidget;
        QTextEdit *m_editor;

    QMenu *m_fileMenu;
        QAction *m_newAction;
        QAction *m_openAction;
        QAction *m_saveAction;
        QAction *m_quitAction;
    QMenu *m_helpMenu;
};

#endif // MAINWINDOW_H
