#pragma once
#ifndef _MEDIATION_EDITOR_EXPORT_PLUGIN_H
#define _MEDIATION_EDITOR_EXPORT_PLUGIN_H

#if TOOLS_ENABLED

#include "editor/export/editor_export_plugin.h"
#include "core/object/class_db.h"

class MediationEditorExportPlugin : public EditorExportPlugin {
    GDCLASS(MediationEditorExportPlugin, EditorExportPlugin);
public:
};

#endif

#endif // _MEDIATION_EDITOR_EXPORT_PLUGIN_H