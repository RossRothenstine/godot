#include <thread_jandroid.h>
#include <os_android.h>
#include <java_godot_wrapper.h>

#include "android_mediation_service.h"
#include "core/string/print_string.h"

constexpr const char* MEDIATION_SERVICE_CLASS = "games/tateyama/godot/services/mediation/MediationService";

AndroidMediationService::AndroidMediationService() {
    _env = get_jni_env();
    _mediationServiceClass = _env->FindClass(MEDIATION_SERVICE_CLASS);
    _mediationServiceClass = static_cast<jclass>(_env->NewGlobalRef(_mediationServiceClass));
    _mediationServiceConstructor = _env->GetMethodID(_mediationServiceClass, "<init>", "(Landroid/content/Context;J)V");
    _initializeMethod = _env->GetMethodID(_mediationServiceClass, "initialize", "()V");

    _activity = static_cast<OS_Android *>(OS::get_singleton())->get_godot_java()->get_activity();
    _activity = _env->NewGlobalRef(_activity);

    _mediationService = _env->NewObject(_mediationServiceClass, _mediationServiceConstructor, _activity, reinterpret_cast<jlong>(this));
    _mediationService = _env->NewGlobalRef(_mediationService);
}

AndroidMediationService::~AndroidMediationService() {
    _env->DeleteGlobalRef(_mediationService);
    _env->DeleteGlobalRef(_activity);
    _env->DeleteGlobalRef(_mediationServiceClass);
}

void AndroidMediationService::initialize() {
    print_line("AndroidMediationService::initialize()");
    _env->CallVoidMethod(_mediationService, _initializeMethod);
}

void AndroidMediationService::onInitialized() {
    print_line("AndroidMediationService::onInitialized()");
    emit_signal("initialized");
}

extern "C" {

JNIEXPORT void JNICALL Java_games_tateyama_godot_services_mediation_MediationService_nativeInitialized(JNIEnv *env, jclass clazz, jlong ptr) {
    AndroidMediationService *service = reinterpret_cast<AndroidMediationService *>(ptr);
    service->onInitialized();
}

}
