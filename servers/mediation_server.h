#pragma once
#include "core/object/ref_counted.h"
#ifndef _MEDIATION_SERVER_H
#define _MEDIATION_SERVER_H

#include "core/object/class_db.h"
#include "core/object/object.h"

/**
 * \brief RewardedVideo is a class that represents a rewarded video ad object.
 */
class RewardedVideo : public RefCounted
{
    GDCLASS(RewardedVideo, RefCounted);
public:
    virtual void load() = 0;
    virtual void show() = 0;
    virtual bool is_loaded() = 0;

    static const StringName SIGNAL_LOADED;
    static const StringName SIGNAL_LOAD_FAILED;
protected:
    static void _bind_methods();
};

/**
 * \brief MediationServer is a singleton object that controls mediation of ad objects.
 */
class MediationServer : public Object
{
    GDCLASS(MediationServer, Object);
public:
    MediationServer();
    virtual ~MediationServer();
    /**
     * \brief Get the singleton instance of the mediation server.
     * \return The singleton instance of the mediation server.
     */
    static MediationServer* get_singleton();
    /**
     * \brief Initialize the mediation server.
     */
    virtual void initialize() = 0;

    static const StringName SIGNAL_INITIALIZED;
protected:
    static void _bind_methods();

    static MediationServer* singleton;
};

#ifdef TOOLS_ENABLED
/**
 * \brief MediationServerEditor is a singleton object that controls testing mediation within the editor.
 */
class MediationServerEditor : public MediationServer
{
    GDCLASS(MediationServerEditor, Object);
public:
    MediationServerEditor();
    virtual ~MediationServerEditor();
    /**
     * \brief Get the singleton instance of the mediation server editor.
     * \return The singleton instance of the mediation server editor.
     */
    static MediationServerEditor* get_singleton();
    /**
     * \brief Initialize the mediation server editor.
     */
    virtual void initialize() override;
private:
    static MediationServerEditor *singleton;
};

#endif // TOOLS_ENABLED

#endif // _MEDIATION_SERVER_H