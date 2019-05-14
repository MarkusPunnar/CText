#ifndef WRITINGWIDGET_H
#define WRITINGWIDGET_H

#include <QWidget>

class MainWindow;

class WritingWidget: public QWidget {
    Q_OBJECT
    public:
        WritingWidget(MainWindow *parent = 0);
        ~WritingWidget();

    protected:
        MainWindow *m_mainWindow;
};

#endif // WRITINGWIDGET_H
