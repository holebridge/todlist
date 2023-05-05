#pragma
#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <QDialog>
#include <QPoint>
#include <QCursor>
#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QMouseEvent>
#include <QApplication>
#include <QListView>
#include <QAbstractListModel>
#include <QStandardItem>
#include "../model/model.hpp"
#include "todo_item.hpp"
#include "edit_dialog.hpp"

namespace holebridge {
namespace todolist {

class TodoListModel : public QAbstractListModel {
    std::vector<TodoItem> todo_list;
    DbClient& db_client;
public:
    TodoListModel(DbClient& client) : db_client(client) {
        refresh();
    }
    ~TodoListModel() {}
    void refresh() {
        std::vector<TodoItem> lists =  this->db_client.get_all<TodoItem>();
        this->todo_list = lists;
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const {
        return todo_list.size();
    }

    QVariant data(const QModelIndex &index, int role) const {
        if (!index.isValid()) {
            return QVariant();
        }
    
        int nRow = index.row();
        if (nRow >= rowCount() || nRow < 0) {
            return QVariant();
        }
        /*
        switch (role) {
        case Qt::DisplayRole:
            QVariant var;
            var.setValue(todo_list[nRow]);
            return var;
        }
        */
        QVariant var;
        var.setValue(todo_list[nRow]);
        return var;
    }
    bool setData(const QModelIndex &index, const QVariant &value, int role  = Qt::EditRole) {
        if (!index.isValid()) {
            return false;
        }
        int row = index.row();
        if (row >= rowCount() || row < 0) {
            return false;
        }

        TodoItem item = value.value<TodoItem>();

        switch (role) {
        case Qt::EditRole:
            if(item.id != todo_list[row].id) {
                return false;
            }
            todo_list[row].name = item.name;
            todo_list[row].start_at = item.start_at;
            todo_list[row].total_work = item.total_work;
            todo_list[row].progress = item.progress;
            break;
        default:
            return false;
        }
    
        emit dataChanged(index, index);
 
        return true;
    }
};

class TodoListWidget : public QListView {
    TodoListModel* model;
    DbClient& db_client;
public:
    TodoListWidget(DbClient& client, QWidget* parent = nullptr) : QListView(parent), db_client(client) {

        this->setMinimumHeight(0);
        model = new TodoListModel(client);
        this->setModel(model);
        this->setItemAlignment(Qt::AlignLeft);
        TodoItemDelegate* delegate = new TodoItemDelegate(this);
        this->setItemDelegate(delegate);
        QObject::connect(this, &QListView::clicked, [this](const QModelIndex& index) {
            if (!index.isValid()) {
                return;
            }
            int row = index.row();
            int rowCnt = this->model->rowCount();
            if (row >= rowCnt || row < 0) {
                return;
            }

            QMenu* menu = new QMenu(this);

            QAction* up = new QAction("上移"); 
            menu->addAction(up);
            QObject::connect(up, &QAction::triggered, [&, this]() {
                if (rowCnt > 1 && row > 0) {
                }
            });

            QAction* down = new QAction("下移"); 
            menu->addAction(down);
            QObject::connect(down, &QAction::triggered, [&, this]() {
                if (rowCnt > 1 && row < rowCnt - 1) {

                }
            });

            QAction* del = new QAction("删除"); 
            menu->addAction(del);
            QObject::connect(del, &QAction::triggered, [&, this]() {
                this->db_client.remove<TodoItem>(this->model->data(index, Qt::UserRole+1).value<TodoItem>().id);
                this->model->refresh();
            });

            QAction* quit = new QAction("取消"); 
            menu->addAction(quit);

            menu->exec(QCursor::pos());

        });
        QObject::connect(this, &QListView::doubleClicked, [this](const QModelIndex& index) {
            TodoItem item = index.data().value<TodoItem>();
            if(qApp->mouseButtons() == Qt::LeftButton) {
                item.id = 0;
            }
            EditDialog dialog(item, this);
            QObject::connect(&dialog, &EditDialog::saveTodoItem, [this](TodoItem item) {
                this->db_client.update<TodoItem>(item);
                this->reset();
            });
            dialog.exec();
        });
    }
    void reset() {
        this->model->refresh();
    }
};


}
}