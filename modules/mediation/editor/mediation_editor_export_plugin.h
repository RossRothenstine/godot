#pragma once
#ifndef _MEDIATION_EDITOR_EXPORT_PLUGIN_H
#define _MEDIATION_EDITOR_EXPORT_PLUGIN_H

#if TOOLS_ENABLED

#include "editor/export/editor_export_plugin.h"
#include "core/object/class_db.h"

class MediationEditorExportPlugin : public EditorExportPlugin {
    GDCLASS(MediationEditorExportPlugin, EditorExportPlugin);
public:
    MediationEditorExportPlugin();
    String get_name() const override { return "Mediation"; }
    bool supports_platform(const Ref<EditorExportPlatform>& platform) const override;
    String get_android_manifest_application_element_contents(const Ref<EditorExportPlatform>& platform, bool) const override;
    void _get_export_options(const Ref<EditorExportPlatform> &p_export_platform, List<EditorExportPlatform::ExportOption> *r_options) const override;

    PackedStringArray get_android_dependencies(const Ref<EditorExportPlatform> &p_export_platform,
                                               bool p_debug) const override;
};

#endif

#endif // _MEDIATION_EDITOR_EXPORT_PLUGIN_H
