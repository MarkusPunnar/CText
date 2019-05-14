#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    QMenu *m_fileMenu;
        QAction *m_quitAction;
    QMenu *m_helpMenu;
};

#endif // MAINWINDOW_H
