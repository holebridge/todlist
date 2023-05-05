#include "model/model.hpp"
#include "view/main_window.hpp"

#include <iostream>
#include <chrono>
#include <QApplication>

using namespace holebridge::todolist;

int main(int argc, char** argv) {
    DbClient db_client = InitDbClient("todolist.db");
    QApplication app(argc, argv);
    MainWindow w(db_client);
    w.show();
    app.exec();
}
