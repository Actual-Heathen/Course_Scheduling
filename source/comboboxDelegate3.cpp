#include "../Course_Scheduling/header/comboboxDelegate3.h"
#include <QComboBox>

ComboBoxDelegate3::ComboBoxDelegate3(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


ComboBoxDelegate3::~ComboBoxDelegate3()
{
}


QWidget *ComboBoxDelegate3::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);

    cb->addItem("8:00 AM");

    cb->addItem("9:40 AM");

    cb->addItem("11:20 AM");

    cb->addItem("1:00 PM");

    cb->addItem("2:40 PM");

    cb->addItem("4:20 PM");

    cb->addItem("6:00 PM");

    return cb;

}


void ComboBoxDelegate3::setEditorData(QWidget *editor, const QModelIndex &index) const
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


void ComboBoxDelegate3::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);

    Q_ASSERT(cb);

    model->setData(index, cb->currentText(), Qt::EditRole);

}
