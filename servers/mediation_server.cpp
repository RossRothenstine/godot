#include "mediation_server.h"
#include "core/error/error_macros.h"

MediationServer *MediationServer::singleton = nullptr;

const StringName RewardedVideo::SIGNAL_LOADED = "loaded";
const StringName RewardedVideo::SIGNAL_LOAD_FAILED = "load_failed";

void RewardedVideo::_bind_methods() {
    ClassDB::bind_method(D_METHOD("load"), &RewardedVideo::load);
    ClassDB::bind_method(D_METHOD("show"), &RewardedVideo::show);
    ClassDB::bind_method(D_METHOD("is_loaded"), &RewardedVideo::is_loaded);
    ADD_SIGNAL(MethodInfo(SIGNAL_LOADED));
    ADD_SIGNAL(MethodInfo(SIGNAL_LOAD_FAILED));
}

const StringName MediationServer::SIGNAL_INITIALIZED = "initialized";

MediationServer::MediationServer() {
    ERR_FAIL_COND_MSG(singleton != nullptr, "MediationServer singleton already exists.");
    singleton = this;
}

MediationServer::~MediationServer() {
    ERR_FAIL_COND_MSG(singleton == nullptr, "MediationServer singleton does not exist.");
    singleton = nullptr;
}

MediationServer *MediationServer::get_singleton() {
    ERR_FAIL_COND_V_MSG(singleton == nullptr, nullptr, "MediationServer singleton does not exist.");
    return singleton;
}

void MediationServer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize"), &MediationServer::initialize);
    ADD_SIGNAL(MethodInfo(SIGNAL_INITIALIZED));
}

#ifdef TOOLS_ENABLED

MediationServerEditor *MediationServerEditor::singleton = nullptr;

MediationServerEditor::MediationServerEditor() {
    ERR_FAIL_COND_MSG(singleton != nullptr, "MediationServerEditor singleton already exists.");
    singleton = this;
}

MediationServerEditor::~MediationServerEditor() {
    ERR_FAIL_COND_MSG(singleton == nullptr, "MediationServerEditor singleton does not exist.");
    singleton = nullptr;
}

MediationServerEditor *MediationServerEditor::get_singleton() {
    ERR_FAIL_COND_V_MSG(singleton == nullptr, nullptr, "MediationServerEditor singleton does not exist.");
    return singleton;
}

void MediationServerEditor::initialize() {
    print_line("MediationServerEditor::initialize()");
}

#endif