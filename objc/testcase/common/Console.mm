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

#import "Console.h"
#import "TestCaseLog.h"
#import <WCDB/SQLite.h>
#import <WCDB/WCDB.h>

ssize_t illPwrite(int, const void *, size_t, off_t)
{
    return -1;
}

@implementation Console

+ (void)initialize
{
    if (self.class == Console.class
        && [NSThread currentThread].isMainThread) {
        pthread_setname_np("com.Tencent.WCDB.Queue.Main");
    }
}

+ (void)enableSQLTrace
{
    [WCTDatabase globalTraceSQL:^(NSString *sql) {
        NSThread *currentThread = [NSThread currentThread];
        NSString *threadName = currentThread.name;
        if (threadName.length == 0) {
            threadName = [NSString stringWithFormat:@"%p", currentThread];
        }
        TestCaseLog(@"%@ Thread %@: %@", currentThread.isMainThread ? @"*" : @"-", threadName, sql);
    }];
}

+ (void)disableSQLTrace
{
    [WCTDatabase globalTraceSQL:nil];
}

+ (void)enableSQLiteWrite
{
    sqlite3_vfs *vfs = sqlite3_vfs_find(nullptr);
    vfs->xSetSystemCall(vfs, "pwrite", (sqlite3_syscall_ptr) pwrite);
}

+ (void)disableSQLiteWrite
{
    sqlite3_vfs *vfs = sqlite3_vfs_find(nullptr);
    vfs->xSetSystemCall(vfs, "pwrite", (sqlite3_syscall_ptr) illPwrite);
}

@end