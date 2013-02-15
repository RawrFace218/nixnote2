#include "nnotebookviewdelegate.h"
#include <QPainter>
#include "nnotebookviewitem.h"
#include "nnotebookview.h"

NNotebookViewDelegate::NNotebookViewDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}



void NNotebookViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItemV4 options = option;
    initStyleOption(&options, index);

    painter->save();

    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    qint32 lid = index.data(Qt::UserRole).toInt();
    if (lid > 0) {

        NNotebookView  *tree = (NNotebookView*)options.widget;
        NNotebookViewItem *item = tree->dataStore[lid];
        qint32 count = item->count;
        QString countString = QString("(")+QString::number(count) + QString(")");

        // shift text right to make icon visible
        QSize iconSize = options.icon.actualSize(options.rect.size());
        painter->translate(options.rect.left()+iconSize.width(), options.rect.top());
        QRect clip(0, 0, options.rect.width()+iconSize.width(), options.rect.height());

        painter->setClipRect(clip);
        QFontMetrics fm = options.fontMetrics;
        painter->setPen(Qt::darkGray);
        painter->drawText(fm.width(index.data().toString()+QString("  ")),fm.height()-fm.descent()-1,countString);

    }
    painter->restore();
}
