// Copyright (c) Acconeer AB, 2019
// All rights reserved

#ifndef ACC_LOG_INTEGRATION_H_
#define ACC_LOG_INTEGRATION_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "acc_definitions.h"

extern void acc_log_integration(acc_log_level_t level, const char *module, const char *buffer);

#ifdef __cplusplus
}
#endif


#endif
