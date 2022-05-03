#include <iostream>
#include <jni.h>

#include "APKKiller.h"

extern jint Whale_OnLoad(JavaVM *vm, void *reserved);

int RegisterFunctions(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {"Start", "(Landroid/content/Context;)V", (void *) APKKill},
            {"processInvoke", "(Ljava/lang/reflect/Method;[Ljava/lang/Object;)Ljava/lang/Object;", (void *) processInvoke}
    };

    jclass clazz = env->FindClass("com/kuro/APKKiller");
    if (!clazz)
        return -1;

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return -1;

    return 0;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    if (RegisterFunctions(env) != 0) {
        return -1;
    }

    return Whale_OnLoad(vm, reserved);
}