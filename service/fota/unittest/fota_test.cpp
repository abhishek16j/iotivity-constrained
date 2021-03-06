/******************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#include <gtest/gtest.h>

extern "C" {
  #include "fota.h"
  #include "oc_ri.h"
}

static int
fota_cmd_handler(fota_cmd_t cmd)
{
  (void)cmd;
  return 0;
}

class TestFota: public testing::Test
{
  protected:
    virtual void SetUp()
    {
      fota_init(fota_cmd_handler);
    }

    virtual void TearDown()
    {
      fota_deinit();
    }
};

TEST(TestFotaInit, fota_init_p)
{
  // When
  int ret = fota_init(fota_cmd_handler);

  // Then
  EXPECT_EQ(0, ret);

  fota_deinit();
}

TEST(TestFotaInit, fota_init_f)
{
  // When
  int ret = fota_init(NULL);

  // Then
  EXPECT_EQ(-1, ret);
}

TEST(TestFotaInit, fota_deinit_p)
{
  // Given
  fota_init(fota_cmd_handler);

  // When
  fota_deinit();
  char uri[10] = "/firmware";
  oc_resource_t *resource = oc_ri_get_app_resource_by_uri(uri, strlen(uri), 0);

  // Then
  EXPECT_EQ(NULL, resource);
}

TEST_F(TestFota, fota_set_state_p)
{
  // When
  int ret = fota_set_state(FOTA_STATE_DOWNLOADING);

  // Then
  EXPECT_EQ(0, ret);
}

TEST_F(TestFota, fota_set_state_f)
{
  // When
  int ret = fota_set_state(FOTA_STATE_IDLE);

  // Then
  EXPECT_EQ(-1, ret);
}

TEST_F(TestFota, fota_set_fw_info_p)
{
  // Given
  char ver[4] = "1.0";
  char uri[23] = "http://www.samsung.com";

  // When
  int ret = fota_set_fw_info(ver, uri);

  // Then
  EXPECT_EQ(0, ret);
}

TEST_F(TestFota, fota_set_fw_info_f)
{
  // When
  int ret = fota_set_fw_info(NULL, NULL);

  // Then
  EXPECT_EQ(-1, ret);
}

TEST_F(TestFota, fota_set_result_p)
{
  // When
  int ret = fota_set_result(FOTA_RESULT_SUCCESS);

  // Then
  EXPECT_EQ(0, ret);
}
