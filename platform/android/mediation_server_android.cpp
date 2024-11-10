#include "mediation_server_android.h"

MediationServerAndroid *MediationServerAndroid::singleton = nullptr;

MediationServerAndroid::MediationServerAndroid() {
    ERR_FAIL_COND_MSG(singleton != nullptr, "MediationServerAndroid singleton already exists.");
    singleton = this;
}

MediationServerAndroid::~MediationServerAndroid() {
    ERR_FAIL_COND_MSG(singleton == nullptr, "MediationServerAndroid singleton does not exist.");
    singleton = nullptr;
}

MediationServerAndroid *MediationServerAndroid::get_singleton() {
    ERR_FAIL_COND_V_MSG(singleton == nullptr, nullptr, "MediationServerAndroid singleton does not exist.");
    return singleton;
}

void MediationServerAndroid::initialize() {
    print_line("MediationServerAndroid::initialize()");
}