#ifndef WRITINGWIDGET_H
#define WRITINGWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QString>

class MainWindow;

class WritingWidget: public QWidget {
    Q_OBJECT
    public:
        WritingWidget(MainWindow *parent = 0);
        ~WritingWidget();
        void saveFile(QString fileName, QString savedData);
        QString openFile(QString fileName);

    protected:
        MainWindow *m_mainWindow;
};

#endif // WRITINGWIDGET_H
