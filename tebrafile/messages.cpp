#include "messages.h"


void showMessageBox(const QString& title, const QString& content, QMessageBox::Icon icon)
{
    QMessageBox errBox;
    errBox.setWindowTitle(title);
    errBox.setText(content);
    errBox.setIcon(icon);
    errBox.exec();
}
