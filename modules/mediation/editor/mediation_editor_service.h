#pragma once
#ifndef _MEDIATION_EDITOR_SERVICE_H_
#define _MEDIATION_EDITOR_SERVICE_H_

#include "modules/mediation/mediation_service.h"

class MediationEditorService : public MediationService {
public:
    static MediationEditorService *get_singleton();

    MediationEditorService();
    ~MediationEditorService();

    void initialize() override;

    void set_initialization_result(bool initialization_result);
private:
    void on_initialized();

    static MediationEditorService* singleton;
    bool _initialization_result;
};

#endif