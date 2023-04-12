#include "../Course_Scheduling/header/comboboxDelegate4.h"
#include <QComboBox>

ComboBoxDelegate4::ComboBoxDelegate4(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


ComboBoxDelegate4::~ComboBoxDelegate4()
{
}


QWidget *ComboBoxDelegate4::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);

    cb->addItem("9:20 AM");

    cb->addItem("11:00 AM");

    cb->addItem("12:40 PM");

    cb->addItem("2:20 PM");

    cb->addItem("4:00 PM");

    cb->addItem("5:40 PM");

    cb->addItem("7:20 PM");

    return cb;

}


void ComboBoxDelegate4::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);

    Q_ASSERT(cb);

    // get the index of the text in the combobox that matches the current value of the item
    const QString currentText = index.data(Qt::EditRole).toString();

    const int cbIndex = cb->findText(currentText);

    // if it is valid, adjust the combobox
    if (cbIndex >= 0)
       cb->setCurrentIndex(cbIndex);

}


void ComboBoxDelegate4::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);

    Q_ASSERT(cb);

    model->setData(index, cb->currentText(), Qt::EditRole);

}
