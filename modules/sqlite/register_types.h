#ifndef SQLITE_REGISTER_TYPES_H
#define SQLITE_REGISTER_TYPES_H

#include "modules/register_module_types.h"

void initialize_sqlite_module(ModuleInitializationLevel p_level);
void uninitialize_sqlite_module(ModuleInitializationLevel p_level);

#endif // SQLITE_REGISTER_TYPES_H