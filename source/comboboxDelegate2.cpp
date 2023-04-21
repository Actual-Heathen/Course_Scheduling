#include "../Course_Scheduling/header/comboboxDelegate2.h"
#include <QComboBox>

ComboBoxDelegate2::ComboBoxDelegate2(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


ComboBoxDelegate2::~ComboBoxDelegate2()
{
}


QWidget *ComboBoxDelegate2::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);

    cb->addItem("MW");

    cb->addItem("TR");

    cb->addItem("TBA");

    return cb;

}


void ComboBoxDelegate2::setEditorData(QWidget *editor, const QModelIndex &index) const
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


void ComboBoxDelegate2::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);

    Q_ASSERT(cb);

    model->setData(index, cb->currentText(), Qt::EditRole);

}
