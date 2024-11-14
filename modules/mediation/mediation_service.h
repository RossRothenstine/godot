#pragma once
#ifndef _MEDIATION_SERVICE_H
#define _MEDIATION_SERVICE_H

#include "core/object/class_db.h"

class MediationService : public Object {
    GDCLASS(MediationService, Object);
public:
    static void _bind_methods();

    virtual ~MediationService() = default;
    virtual void initialize() = 0;
};

class NullMediationService : public MediationService {
    GDCLASS(NullMediationService, MediationService);
public:
    void initialize() override {}
};

#endif // _MEDIATION_SERVICE_H