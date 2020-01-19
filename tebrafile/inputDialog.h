#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>


#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QDebug>


#include <iostream>


//Nadogradnja klase QDialog koja podržava n ulaza
//
//
class InputDialog : public QDialog {
    Q_OBJECT
public:
    template<typename... Args>
    InputDialog(QWidget* parent = nullptr, Args... labels);
    static QStringList getStrings(InputDialog* diag, bool* ok = nullptr);

public slots:
    void ok_clicked()
    {
        emit credentialsCaptured(this);
    }

signals:
    void credentialsCaptured(InputDialog* diag);
private:
    QList<QLineEdit*> fields;
    QStringList labelNames;
    QFormLayout* lyMain = new QFormLayout(this);

    void addLabelsAndLines(QString& label)
    {

        QLabel* tLabel = new QLabel(label);
        QLineEdit* tLine = new QLineEdit(this);
        if (label.compare(QString("password")) == 0)
            tLine->setEchoMode(QLineEdit::Password);
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

    bool conn = QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::ok_clicked);
    Q_ASSERT(conn);
    conn = QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::accept);
    Q_ASSERT(conn);
    conn = QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &InputDialog::reject);
    Q_ASSERT(conn);

    setLayout(lyMain);
    setWindowTitle(tr("Credentials"));
}


#endif
