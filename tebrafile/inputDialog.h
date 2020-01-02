#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>


#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QDebug>


class InputDialog : public QDialog {
    Q_OBJECT
public:
    //explicit InputDialog(QWidget* parent = nullptr, QString label = QString());
    template<typename... Args>
    InputDialog(QWidget* parent = nullptr, Args... labels);
    QStringList getStrings(bool* ok = nullptr);
private:
    QList<QLineEdit*> fields;
    QStringList labelNames;
    QFormLayout* lyMain = new QFormLayout(this);

    void addLabelsAndLines(QString& label)
    {
        QLabel* tLabel = new QLabel(label);
        QLineEdit* tLine = new QLineEdit(this);
        lyMain->addRow(tLabel, tLine);
        fields << tLine;
    }

    template<typename... Args>
    void addLabelsAndLines(QString& label, Args... labels)
    {
        addLabelsAndLines(label);
        addLabelsAndLines(labels...);
    }
};





template<typename... Args>
inline InputDialog::InputDialog(QWidget* parent, Args... labels)
    :QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    addLabelsAndLines(labels...);

    QDialogButtonBox *buttonBox = new QDialogButtonBox
                  ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                    Qt::Horizontal, this );
    lyMain->addWidget(buttonBox);

    bool conn = QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::accept);
    Q_ASSERT(conn);

    conn = QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &InputDialog::reject);
    Q_ASSERT(conn);

    setLayout(lyMain);
    setWindowTitle(tr("Credentials"));
}


#endif
