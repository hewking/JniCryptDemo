LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := object_jni
LOCAL_SRC_FILES := jniObject.c
include $(BUILD_SHARED_LIBRARY)