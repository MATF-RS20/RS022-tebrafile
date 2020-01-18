#include "inputDialog.h"

#include <iostream>
QStringList InputDialog::getStrings(InputDialog* diag, [[maybe_unused]]bool* ok)
{
    QStringList list;
    foreach (auto field, diag->fields) {
        list << field->text();
    }

    return list;
}
