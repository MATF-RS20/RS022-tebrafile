#include "logger.h"

#include<QDate>


void Logger::showMessageBox(const QString& title, const QString& content, QMessageBox::Icon icon)
{
    QMessageBox errBox;
    errBox.setWindowTitle(title);
    errBox.setText(content);
    errBox.setIcon(icon);
    errBox.exec();
}


void Logger::consoleLog(const QString& msg)
{
    _textEdit->moveCursor(QTextCursor::End);
    _textEdit->insertPlainText("[" + QDate::currentDate().toString(Qt::ISODateWithMs) + "] " + msg + "\r\n\r\n");
    _textEdit->moveCursor(QTextCursor::End);
}
