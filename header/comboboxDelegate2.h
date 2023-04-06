#ifndef COMBOBOXDELEGATE2_H
#define COMBOBOXDELEGATE2_H

#include <QStyledItemDelegate>

class ComboBoxDelegate2 : public QStyledItemDelegate
{
    Q_OBJECT

public:

    ComboBoxDelegate2(QObject *parent = nullptr);

    ~ComboBoxDelegate2();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

#endif // COMBOBOXDELEGATE2_H
