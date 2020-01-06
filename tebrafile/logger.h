#ifndef MESSAGES_H
#define MESSAGES_H
#include <QString>
#include <QMessageBox>
#include <QTextEdit>

class Logger {
public:
    Logger(QTextEdit* textEdit)
        :_textEdit(QSharedPointer<QTextEdit>(textEdit)) {}
    static void showMessageBox(const QString& title, const QString& content, QMessageBox::Icon);
    void consoleLog(const QString& msg);
private:
    QSharedPointer<QTextEdit> _textEdit;
};

#endif // MESSAGES_H
