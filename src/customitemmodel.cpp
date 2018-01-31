#include "customitemmodel.h" 

CustomItemModel::CustomItemModel(const QVector<int>& colsAlignLeft, QObject* parent)
	: CustomItemModel(colsAlignLeft, QVector<int>(), QVector<int>(), parent){
	
}

CustomItemModel::CustomItemModel(const QVector<int>& colsAlignLeft, 
	const QVector<int>& colsAlignCenter, QObject* parent)
	: CustomItemModel(colsAlignLeft, colsAlignCenter, QVector<int>(), parent){

} 

CustomItemModel::CustomItemModel(const QVector<int>& colsAlignLeft, const QVector<int>& colsAlignCenter,
	const QVector<int>& colsAlignRight, QObject* parent):
	QStandardItemModel(parent),
	mColsAlignLeft(colsAlignCenter),
	mColsAlignCenter(colsAlignCenter),
	mColsAlignRight(colsAlignRight){

}
/*
 * Since the text alignment defaults to Qt::AlignLeft, we only need to reimplement the other
 * two alignments.
 */
QVariant CustomItemModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::TextAlignmentRole) {
		if (mColsAlignCenter.contains(index.column())) {
			return Qt::AlignCenter;
		}
		if (mColsAlignRight.contains(index.column())) {
			return Qt::AlignRight;
		}
		if (mColsAlignLeft.contains(index.column())) {
			return Qt::AlignLeft;
		}
	}

	return QStandardItemModel::data(index, role);
}

