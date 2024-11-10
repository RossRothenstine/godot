#pragma once
#ifndef _MEDIATION_SERVICE_ANDROID_H_
#define _MEDIATION_SERVICE_ANDROID_H_

#include "servers/mediation_server.h"
#include <jni.h>

class MediationServerAndroid : public MediationServer {
public:
    static MediationServerAndroid* get_singleton();

    MediationServerAndroid();
    ~MediationServerAndroid();

    void initialize() override;
private:
    static MediationServerAndroid *singleton;
};


#endif // _MEDIATION_SERVICE_ANDROID_H_
