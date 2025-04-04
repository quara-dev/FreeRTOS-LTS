/*
* Percepio Trace Recorder for Tracealyzer v4.10.3
* Copyright 2023 Percepio AB
* www.percepio.com
*
* SPDX-License-Identifier: Apache-2.0
*
* The common types.
*/

#ifndef TRC_TYPES_H
#define TRC_TYPES_H

#include <stdint.h>
#include <trcConfig.h>
#include <trcHardwarePort.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRC_BASE_TYPE
#define TRC_BASE_TYPE int32_t
#endif

#ifndef TRC_UNSIGNED_BASE_TYPE
#define TRC_UNSIGNED_BASE_TYPE uint32_t
#endif

typedef TRC_UNSIGNED_BASE_TYPE TraceUnsignedBaseType_t;

typedef TRC_BASE_TYPE TraceBaseType_t;

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
typedef void* TraceHandleBaseType_t;
#else
typedef TraceUnsignedBaseType_t TraceHandleBaseType_t;
#endif

typedef TraceUnsignedBaseType_t traceResult;

typedef TraceHandleBaseType_t TraceEventHandle_t;

typedef TraceHandleBaseType_t TraceISRHandle_t;

typedef TraceHandleBaseType_t TraceEntryHandle_t;

typedef TraceHandleBaseType_t TraceTaskHandle_t;

typedef TraceHandleBaseType_t TraceObjectHandle_t;

typedef TraceHandleBaseType_t TraceExtensionHandle_t;

typedef TraceHandleBaseType_t TraceHeapHandle_t;

typedef TraceHandleBaseType_t TraceIntervalChannelSetHandle_t;

typedef TraceHandleBaseType_t TraceIntervalChannelHandle_t;

typedef TraceHandleBaseType_t TraceIntervalInstanceHandle_t;

typedef TraceHandleBaseType_t TraceStateMachineHandle_t;

typedef TraceHandleBaseType_t TraceStateMachineStateHandle_t;

typedef TraceHandleBaseType_t TraceStringHandle_t;

typedef TraceHandleBaseType_t TraceCounterHandle_t;

typedef TraceHandleBaseType_t TraceRunnableHandle_t;

typedef TraceHandleBaseType_t TraceRunnableStaticSetHandle_t;

typedef TraceHandleBaseType_t TraceProcessHandle_t;

typedef TraceHandleBaseType_t TraceThreadHandle_t;

typedef void (*TraceCounterCallback_t)(TraceCounterHandle_t xCounterHandle);

/* DEPRECATED. Backwards compatibility */
typedef TraceStringHandle_t traceString;

#ifdef __cplusplus
}
#endif

#endif /* TRC_TYPES_H */
