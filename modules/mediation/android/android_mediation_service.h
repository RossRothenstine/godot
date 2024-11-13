#pragma once
#ifndef _ANDROID_MEDIATION_SERVICE_H_
#define _ANDROID_MEDIATION_SERVICE_H_

#include "modules/mediation/mediation_service.h"

class AndroidMediationService : public MediationService {
public:
    void initialize() override;
};

#endif
