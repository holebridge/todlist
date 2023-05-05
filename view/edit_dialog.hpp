#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTime>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "../model/model.hpp"

namespace holebridge {
namespace todolist {

class EditDialog : public QDialog {
    Q_OBJECT
public:
    EditDialog(TodoItem& item, QWidget* parent = nullptr) : QDialog(parent) {

        if(item.id == 0) {
            this->setWindowTitle("添加待办事项");
        } else {
            this->setWindowTitle("编辑待办事项");
        }

        QLineEdit* name_edit = new QLineEdit(this);
        name_edit->setText(item.name.c_str());

        QVBoxLayout*layout = new QVBoxLayout(this);
        layout->addWidget(name_edit);

        QDate start_date = QDateTime::fromSecsSinceEpoch(item.start_at).date();
        QLabel* start_date_label = new QLabel("起始日期：");
        QDateEdit* start_date_edit  = new QDateEdit(this);
        if (item.id == 0) {
            start_date_edit->setDate(QDate::currentDate());
        }
        else {
            start_date_edit->setDate(start_date);
        }

        QLabel* total_work_label =  new QLabel("计划工期:");
        QSpinBox* total_work_edit = new QSpinBox(this);
        total_work_edit->setValue(item.total_work);
        QLabel* progress_label = new QLabel("当前进度：");
        QSpinBox* progress_edit = new QSpinBox(this);
        progress_edit->setValue(item.progress);
        QPushButton* save_btn = new QPushButton("保存", this);

        QGridLayout* grid =  new QGridLayout(this);

        grid->addWidget(start_date_label, 0,  0);
        grid->addWidget(start_date_edit, 0, 1);
        grid->addWidget(total_work_label, 1, 0);
        grid->addWidget(total_work_edit, 1, 1);
        grid->addWidget(progress_label, 2, 0);
        grid->addWidget(progress_edit, 2, 1);
        grid->addWidget(save_btn, 3, 1, Qt::AlignRight);

        layout->addLayout(grid);
        this->setLayout(layout);

        QObject::connect(save_btn, &QPushButton::clicked, [=]() {
            TodoItem new_item{
                .id = item.id,
                .name = name_edit->text().toStdString(),
                .total_work = total_work_edit->value(),
                .start_at = start_date_edit->dateTime().toSecsSinceEpoch(),
                .progress = progress_edit->value(),
                .create_at = item.create_at,
            };
            emit saveTodoItem(new_item);
            this->close();
        });
    }
signals:
    void saveTodoItem(TodoItem item);
};

}
}