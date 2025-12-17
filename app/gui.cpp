#include "gui.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

Gui::Gui() {}

Q_INVOKABLE void Gui::calculate(QString expression) {
    try {
        std::string expr = expression.toStdString();
        double result = calculator.calculate(expr);
        emit newResult(QString::number(result));
        get_history();
    } catch (const std::runtime_error& e) {
        emit error(QString(e.what()));
    }
}

Q_INVOKABLE void Gui::get_history() {
    std::vector<std::string> vector_history = calculator.get_history();
    std::string history;
    for (size_t i = 0; i < vector_history.size(); ++i)
        history += vector_history[i] + '\n';
    emit newHistory(QString::fromStdString(history));
}
