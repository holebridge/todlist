#pragma once

#include <ctime>
#include <optional>
#include <sqlite_orm/sqlite_orm.h>


namespace holebridge {
namespace todolist {
/*
    int id;
    std::string name;
    int total_work;
    time_t start_at;
    int progress;
    time_t create_at;
    int priority;
    bool deleted;
*/
struct TodoItem {
    int id;
    std::string name;
    int total_work;
    time_t start_at;
    int progress;
    int priority;
    time_t create_at;
    bool deleted;
};

struct CustomConfig {
    int id;
    int opacity;
    bool auto_folder;
};

using DbClient = decltype(sqlite_orm::make_storage("",
    sqlite_orm::make_table("TodoList",
        sqlite_orm::make_column("id", &TodoItem::id, sqlite_orm::primary_key(), sqlite_orm::autoincrement()),
        sqlite_orm::make_column("name", &TodoItem::name),
        sqlite_orm::make_column("total_work", &TodoItem::total_work),
        sqlite_orm::make_column("start_at", &TodoItem::start_at),
        sqlite_orm::make_column("progress", &TodoItem::progress),
        sqlite_orm::make_column("create_at", &TodoItem::create_at),
        sqlite_orm::make_column("priority", &TodoItem::priority),
        sqlite_orm::make_column("deleted", &TodoItem::deleted)
    ),
    sqlite_orm::make_table("CustomConfig",
        sqlite_orm::make_column("id", &CustomConfig::id, sqlite_orm::primary_key()),
        sqlite_orm::make_column("opacity", &CustomConfig::opacity),
        sqlite_orm::make_column("auto_folder", &CustomConfig::auto_folder)
    )
));

inline DbClient InitDbClient(const std::string& path) {
    auto storage = sqlite_orm::make_storage(path,
        sqlite_orm::make_table("TodoList",
            sqlite_orm::make_column("id", &TodoItem::id, sqlite_orm::primary_key(), sqlite_orm::autoincrement()),
            sqlite_orm::make_column("name", &TodoItem::name),
            sqlite_orm::make_column("total_work", &TodoItem::total_work),
            sqlite_orm::make_column("start_at", &TodoItem::start_at),
            sqlite_orm::make_column("progress", &TodoItem::progress),
            sqlite_orm::make_column("create_at", &TodoItem::create_at),
            sqlite_orm::make_column("priority", &TodoItem::priority),
            sqlite_orm::make_column("deleted", &TodoItem::deleted)
        ),
        sqlite_orm::make_table("CustomConfig",
            sqlite_orm::make_column("id", &CustomConfig::id, sqlite_orm::primary_key()),
            sqlite_orm::make_column("opacity", &CustomConfig::opacity),
            sqlite_orm::make_column("auto_folder", &CustomConfig::auto_folder)
        )
    );
    if(!path.empty())  {
        storage.sync_schema();
    }
    return storage;
}

}
}


