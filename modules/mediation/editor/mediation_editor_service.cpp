#include "mediation_editor_service.h"
#include "core/object/callable_method_pointer.h"

MediationEditorService* MediationEditorService::singleton = nullptr;

MediationEditorService::MediationEditorService()
    : _initialization_result(false)
{
    singleton = this;
}

MediationEditorService::~MediationEditorService() {
    singleton = nullptr;
}

MediationEditorService* MediationEditorService::get_singleton() {
    return singleton;
}

void MediationEditorService::initialize() {
    callable_mp(this, &MediationEditorService::on_initialized).call_deferred();
}

void MediationEditorService::set_initialization_result(bool initialization_result) {
    _initialization_result = initialization_result;
}

void MediationEditorService::on_initialized() {
    emit_signal("initialized");
}