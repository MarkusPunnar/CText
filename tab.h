#ifndef TAB_H
#define TAB_H

#include "QString"
#include "QFont"
#include "QTextEdit"

class MainWindow;
class Tab : public QTextEdit {
    Q_OBJECT
public:

    QString openFile;
    QString savedState;
    QFont currentFont;
    unsigned int fontSize;

    ~Tab();

    Tab(QString file, MainWindow* window);
};

#endif // TAB_H
