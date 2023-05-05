#pragma once 
#include <ctime>
#include <QWidget>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
#include "opacity_slider.hpp"
#include "todo_list.hpp"
#include "edit_dialog.hpp"
#include "../model/model.hpp"

namespace holebridge {
namespace todolist {

class MainWindow : public QWidget {
    DbClient& db_client;
    TodoListWidget* list_widget;
public:
    MainWindow(DbClient& client, QWidget* parent = nullptr) : QWidget(parent), db_client(client) {
        
        // 设置窗口标题
        this->setWindowTitle("土豆茄");

        // 设置窗口置顶
        this->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
        
        // 设置大小和位置
        auto size = QGuiApplication::primaryScreen()->size();
        this->setGeometry(size.width() - 350, (size.height() - 500) / 2, 350, 600);

        // 设置主布局
        QVBoxLayout* layout = new QVBoxLayout(this);
        this->setLayout(layout);

        // 透明度调节尺
        OpacitySlider* slider = new OpacitySlider(this);
        QObject::connect(slider, &QSlider::valueChanged, [this](int value) {
            if(value > 10) {
                this->setWindowOpacity(value / 100.0);
            }
        });

        layout->addWidget(slider);
        layout->addSpacing(2);

        // 待办列表
        list_widget = new TodoListWidget(client, this);
        layout->addWidget(list_widget);
        
        // 添加待办
        QPushButton*  add_btn = new QPushButton("添加", this);
        layout->addWidget(add_btn);
        layout->setSpacing(0);

        QObject::connect(add_btn, &QPushButton::clicked, [this]() {
            TodoItem item{.id = 0, .create_at = time(nullptr)};
            EditDialog dialog(item, this);
            connect(&dialog, &EditDialog::saveTodoItem, [this](TodoItem item) {
                this->db_client.insert<TodoItem>(item);
                this->list_widget->reset();
            });
            dialog.exec();
        });
        // 添加弹簧
        layout->addStretch();
    }
};


}
}