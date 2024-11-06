#pragma once
#ifndef SQLITE_SQLITE_DB_H
#define SQLITE_SQLITE_DB_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"

class SQLiteDB;
class SQLiteDBStatement : public RefCounted {
    GDCLASS(SQLiteDBStatement, RefCounted);
    friend SQLiteDB;
protected:
    static void _bind_methods();

    // This is a pointer to the SQLite database object.
    Ref<SQLiteDB> db;
};

class SQLiteDB : public RefCounted {
    GDCLASS(SQLiteDB, RefCounted);
public:
    Ref<SQLiteDBStatement> prepare(const String &p_query);

protected:
	static void _bind_methods();
};

#endif // SQLITE_SQLITE_DB_H