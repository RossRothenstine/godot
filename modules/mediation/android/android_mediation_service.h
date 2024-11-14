#pragma once
#ifndef _ANDROID_MEDIATION_SERVICE_H_
#define _ANDROID_MEDIATION_SERVICE_H_

#include <jni.h>

#include "modules/mediation/mediation_service.h"

class AndroidMediationService : public MediationService {
public:
    AndroidMediationService();
    ~AndroidMediationService();

    void initialize() override;

    void onInitialized();
private:

    JNIEnv* _env;
    jclass _mediationServiceClass;
    jobject _activity;
    jobject _mediationService;
    jmethodID _initializeMethod;
    jmethodID _mediationServiceConstructor;
};

#endif
