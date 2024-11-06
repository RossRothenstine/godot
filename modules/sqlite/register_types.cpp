#include "register_types.h"

#include <sqlite3/sqlite3.h>

#include "core/object/class_db.h"
#include "sqlite_db.h"

void initialize_sqlite_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_CLASS(SQLiteDB);
    GDREGISTER_CLASS(SQLiteDBStatement);
}

void uninitialize_sqlite_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}