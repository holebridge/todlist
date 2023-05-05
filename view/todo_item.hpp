#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QStyledItemDelegate>
#include "../model/model.hpp"

namespace holebridge {
namespace todolist {

class TodoItemDelegate : public QStyledItemDelegate {
public:
    TodoItemDelegate(QListView* parent = nullptr) : QStyledItemDelegate(parent) {

    }
    void paint(QPainter* painter,
        const QStyleOptionViewItem& option,
        const QModelIndex& index)const {
        if (index.isValid()) {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->setFont(QFont("Microsoft YaHei"));
            QVariant var = index.data(Qt::UserRole + 1);
            TodoItem itemData = var.value<TodoItem>();
    
            //item rect area
            QRectF rect;
            rect.setX(option.rect.x());
            rect.setY(option.rect.y());
            rect.setWidth(option.rect.width());
            rect.setHeight(option.rect.height());
            
            QPainterPath painter_path;
            painter_path.moveTo(rect.topRight());
            painter_path.lineTo(rect.topLeft());
            painter_path.quadTo(rect.topLeft(), rect.topLeft());
            painter_path.lineTo(rect.bottomLeft());
            painter_path.quadTo(rect.bottomLeft(), rect.bottomLeft());
            painter_path.lineTo(rect.bottomRight());
            painter_path.quadTo(rect.bottomRight(), rect.bottomRight());
            painter_path.lineTo(rect.topRight());
            painter_path.quadTo(rect.topRight(), rect.topRight());
    
            painter->setPen(QPen(QColor(Qt::white)));
            painter->setBrush(QColor(Qt::white));
            painter->drawPath(painter_path);

            QRectF total_days_rect(rect.left(), rect.top(), rect.width(), 4);
            painter->setBrush(QBrush(QColor("#16a951")));
            painter->drawRect(total_days_rect);
            float used_ratio = 1.0;
            auto now = time(nullptr);
            time_t total_seconds = (time_t)itemData.total_work * 86400;
            if(now - itemData.start_at <  total_seconds) {
                used_ratio = 1.0 * (now - itemData.start_at) / total_seconds;
            }
            QRectF left_days_rect(rect.left(), rect.top(), rect.width() * used_ratio, 4);
            painter->setBrush(QBrush(Qt::red));
            painter->drawRect(left_days_rect);

            QRectF circle_progress_rect (rect.left() + 10, rect.top() + 10, 30, 30);
            int radius = 15;
            int startAngle = 90 * 16;
            int spanAngle = - itemData.progress / 100.0 * 360 * 16;
            painter->setBrush(QBrush(QColor("#EDEDED"))); 
            painter->drawEllipse(circle_progress_rect);
            painter->setBrush(QBrush(QColor("#16a951")));
            painter->drawPie(circle_progress_rect, startAngle, spanAngle);
            
            QRectF name_rect(rect.left() + 50, rect.top() + 15, rect.width() - 50 , 20);
            painter->setPen(QPen(QColor("#505050")));
            painter->setFont(QFont("Microsoft YaHei", 12));
            painter->drawText(name_rect, itemData.name.c_str());

            QRectF days_ratio_rect(rect.left() + rect.width() - 70, rect.bottom() - 15, 70, 15);
            painter->setPen(QPen(QColor("#505050")));
            painter->setFont(QFont("Microsoft YaHei", 8));

            int used_days = (now - itemData.start_at) / 86400;
            std::string left_text = "剩余" + std::to_string(itemData.total_work - used_days) + "/" + std::to_string(itemData.total_work) + "天";
            painter->drawText(days_ratio_rect,  Qt::AlignRight, left_text.c_str());


        }
    }
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
        Q_UNUSED(index)
        return QSize(option.rect.width(), 50);
    }
};

}
}