#include "register_types.h"

#include "core/os/memory.h"
#include "mediation_service.h"

#include "core/object/class_db.h"
#include "editor/export/editor_export.h"
#include "editor/export/editor_export_plugin.h"
#include "modules/register_module_types.h"

#if ANDROID_ENABLED
#include "android/android_mediation_service.h"
#endif

#if TOOLS_ENABLED
#include "editor/editor_node.h"
#include "editor/mediation_editor_plugin.h"
#include "editor/mediation_editor_export_plugin.h"
#include "editor/mediation_editor_service.h"
#endif

static MediationService* mediation_service;

#if TOOLS_ENABLED
static Ref<MediationEditorExportPlugin> mediation_export_plugin;
#endif

#if TOOLS_ENABLED
static void _editor_init() {
    mediation_export_plugin.instantiate();
    EditorExport::get_singleton()->add_export_plugin(mediation_export_plugin);
}
#endif

void initialize_mediation_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        #if TOOLS_ENABLED
        mediation_service = memnew(MediationEditorService);
        #elif ANDROID_ENABLED
        mediation_service = memnew(AndroidMediationService);
        #else
        mediation_service = memnew(NullMediationService);
        #endif
        GDREGISTER_ABSTRACT_CLASS(MediationService);
        Engine::get_singleton()->add_singleton(Engine::Singleton("MediationService", mediation_service));
    }

    #if TOOLS_ENABLED
    if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
        EditorNode::add_init_callback(_editor_init);
    }
    #endif
}

void uninitialize_mediation_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        memdelete(mediation_service);
        mediation_service = nullptr;
    }
}
