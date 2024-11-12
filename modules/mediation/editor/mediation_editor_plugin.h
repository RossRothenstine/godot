#pragma once
#ifndef _MEDIATION_EDITOR_PLUGIN_H
#define _MEDIATION_EDITOR_PLUGIN_H

#if TOOLS_ENABLED

#include "editor/plugins/editor_plugin.h"
#include "core/object/class_db.h"

class MediationEditorPlugin : public EditorPlugin {
    GDCLASS(MediationEditorPlugin, EditorPlugin);
};

#endif

#endif // _MEDIATION_EDITOR_PLUGIN_H