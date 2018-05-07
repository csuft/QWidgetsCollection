#ifndef _CUSTOM_ITEM_MODEL_H
#define _CUSTOM_ITEM_MODEL_H

#include <QStandardItemModel>

class CustomItemModel : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit CustomItemModel(QObject *parent = Q_NULLPTR){}
	CustomItemModel(const QVector<int>& colsAlignLeft, QObject* parent = Q_NULLPTR);
	CustomItemModel(const QVector<int>& colsAlignLeft, const QVector<int>& colsAlignCenter,
		QObject* parent = Q_NULLPTR); 
	CustomItemModel(const QVector<int>& colsAlignLeft, const QVector<int>& colsAlignCenter, 
		const QVector<int>& colsAlignRight, QObject* parent = Q_NULLPTR);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	~CustomItemModel(){}

private:
	QVector<int> mColsAlignRight;
	QVector<int> mColsAlignCenter;
	QVector<int> mColsAlignLeft;
};

#endif // _CUSTOM_ITEM_MODEL_H
