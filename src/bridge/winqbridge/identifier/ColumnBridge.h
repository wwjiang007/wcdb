//
// Created by qiuwenchen on 2022/5/26.
//

/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "WinqBridge.h"

WCDB_EXTERN_C_BEGIN

CPPColumn WCDBColumnCreateAll();
CPPColumn WCDBColumnCreateRowId();
CPPColumn WCDBColumnCreateWithName(const char* _Nullable name, const void* _Nullable binding);
CPPColumn WCDBColumnCreateWithName2(const char* _Nullable name, const void* _Nullable binding);
CPPColumn WCDBColumnCopy(CPPColumn column);
void WCDBColumnInTable(CPPColumn column, const char* _Nullable table);
void WCDBColumnOfSchema(CPPColumn column, CPPSchema schema);
void WCDBColumnOfSchema2(CPPColumn column, CPPCommonValue schema);
CPPResultColumn WCDBColumnConfigAlias(CPPColumn column, const char* _Nullable alias);
CPPExpression WCDBColumnAsExpressionOperand(CPPColumn column);

WCDB_EXTERN_C_END
