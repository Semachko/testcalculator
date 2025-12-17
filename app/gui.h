#pragma once

#include "calculator.h"
#include <QObject>

class Gui : public QObject {
        Q_OBJECT

    public:
        Gui();
        Q_INVOKABLE void calculate(QString);
        Q_INVOKABLE void get_history();
    signals:
        void newResult(QString);
        void newHistory(QString);
        void error(QString);

    private:
        Calculator calculator;
};
