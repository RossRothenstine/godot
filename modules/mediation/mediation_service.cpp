#include "mediation_service.h"
#include "core/object/object.h"

void MediationService::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize"), &MediationService::initialize);
    ADD_SIGNAL(MethodInfo("initialized"));
}