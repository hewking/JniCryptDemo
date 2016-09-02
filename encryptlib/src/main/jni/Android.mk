LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := ClientCrypt
LOCAL_SRC_FILES := libClientCrypt.a
include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE    := encrypt
LOCAL_STATIC_LIBRARIES := ClientCrypt
LOCAL_SRC_FILES := encrypt.cpp
include $(BUILD_SHARED_LIBRARY)