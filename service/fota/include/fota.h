/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/**
  @brief FOTA API of IoTivity-constrained for firmware update.
  @file
*/

#ifndef FOTA_H
#define FOTA_H

#include "fota_types.h"

typedef int (*fota_cmd_cb_t)(fota_cmd_t cmd);

int fota_init(fota_cmd_cb_t cb);
void fota_deinit(void);

int fota_set_state(fota_state_t state);
int fota_set_fw_info(const char *ver, const char *uri);
int fota_set_result(fota_result_t result);

#endif /* FOTA_H */