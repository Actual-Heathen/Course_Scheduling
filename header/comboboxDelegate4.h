#ifndef COMBOBOXDELEGATE4_H
#define COMBOBOXDELEGATE4_H

#include <QStyledItemDelegate>

class ComboBoxDelegate4 : public QStyledItemDelegate
{
    Q_OBJECT

public:

    ComboBoxDelegate4(QObject *parent = nullptr);

    ~ComboBoxDelegate4();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

#endif // COMBOBOXDELEGATE4_H
