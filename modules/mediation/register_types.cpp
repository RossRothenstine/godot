#include "register_types.h"

#include "core/object/class_db.h"
#include "editor/export/editor_export.h"
#include "editor/export/editor_export_plugin.h"
#include "modules/register_module_types.h"

#if TOOLS_ENABLED
#include "editor/mediation_editor_plugin.h"
#include "editor/mediation_editor_export_plugin.h"
#endif

#if TOOLS_ENABLED
static Ref<EditorExportPlugin> mediation_export_plugin;
#endif

void initialize_mediation_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
    }

    #if TOOLS_ENABLED
    if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
        mediation_export_plugin = memnew(MediationEditorExportPlugin);
		EditorExport::get_singleton()->add_export_plugin(mediation_export_plugin);
    }
    #endif
}

void uninitialize_mediation_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    #if TOOLS_ENABLED
    if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
        EditorExport::get_singleton()->remove_export_plugin(mediation_export_plugin);
        mediation_export_plugin = nullptr;
    }
    #endif
}