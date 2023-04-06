#ifndef COMBOBOXDELEGATE3_H
#define COMBOBOXDELEGATE3_H

#include <QStyledItemDelegate>

class ComboBoxDelegate3 : public QStyledItemDelegate
{
    Q_OBJECT

public:

    ComboBoxDelegate3(QObject *parent = nullptr);

    ~ComboBoxDelegate3();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

#endif // COMBOBOXDELEGATE3_H
