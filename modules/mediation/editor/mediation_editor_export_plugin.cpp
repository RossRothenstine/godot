#include <editor/export/editor_export.h>
#include "mediation_editor_export_plugin.h"

#include "editor/export/editor_export_platform.h"
#include "platform/android/export/export_plugin.h"

constexpr const char* PROP_MEDIATION_APPLICATION_ID = "mediation/application_id";
constexpr const char* PROP_MEDIATION_APPLICATION_ID_DEFAULT = "ca-app-pub-3940256099942544~3347511713";

MediationEditorExportPlugin::MediationEditorExportPlugin() {
}

bool MediationEditorExportPlugin::supports_platform(const Ref<EditorExportPlatform> &platform) const {
    Ref<EditorExportPlatformAndroid> android_platform = platform;
    if (android_platform.is_valid()) {
        return true;
    }
    return false;
}

String MediationEditorExportPlugin::get_android_manifest_application_element_contents(const Ref<EditorExportPlatform> &platform, bool debug) const {
    auto preset = get_export_preset();
    return vformat("<meta-data android:name=\"com.google.android.gms.ads.APPLICATION_ID\" android:value=\"%s\" />", preset->get(PROP_MEDIATION_APPLICATION_ID));
}

void MediationEditorExportPlugin::_get_export_options(const Ref<EditorExportPlatform> &p_export_platform,
                                                 List<EditorExportPlatform::ExportOption> *r_options) const {

    EditorExportPlatform::ExportOption application_id;
    PropertyInfo application_id_info;
    application_id_info.name = PROP_MEDIATION_APPLICATION_ID;
    application_id_info.type = Variant::STRING;
    application_id.option = application_id_info;
    application_id.default_value = PROP_MEDIATION_APPLICATION_ID_DEFAULT;
    r_options->push_back(application_id);
}

PackedStringArray MediationEditorExportPlugin::get_android_dependencies(
        const Ref<EditorExportPlatform> &p_export_platform, bool p_debug) const {
    PackedStringArray dependencies;
    dependencies.push_back("com.google.android.gms:play-services-ads:23.3.0");
    return dependencies;
}
