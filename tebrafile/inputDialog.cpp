#include "inputDialog.h"


QStringList InputDialog::getStrings(bool* ok)
{
    QStringList list;
    const int ret_val = this->exec();
    if (ok)
        *ok = ret_val;

    if (ret_val) {
        foreach (auto field, this->fields) {
           list << field->text();
        }
    }
    return list;
}
