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

#import <WCDB/String.hpp>
#import <WCDB/WCTCoding.h>
#import <WCDB/WCTColumnBinding.h>
#import <WCDB/WCTCommon.h>
#import <WCDB/WCTProperty.h>
#import <map>

class WCTBinding final {
#pragma mark - Binding
public:
    static const WCTBinding &bindingWithClass(Class cls);

    static void checkInheritance(Class left, Class right);

private:
    WCTBinding(Class cls);
    void initialize();
    Class m_cls;

#pragma mark - Property
public:
    template<typename T>
    void addProperty(const WCDB::String &propertyName, const WCDB::String &columnName)
    {
        WCTColumnBinding columnBinding(m_cls, propertyName, columnName, (T *) nullptr);
        addProperty(columnName, std::move(columnBinding));
    }

    const WCTProperty &getProperty(const WCDB::String &propertyName) const;

    const WCTProperties &getAllProperties() const;

    const std::map<WCDB::String, WCTColumnBinding, WCDB::String::CaseInsensiveComparator> &
    getColumnBindings() const;

    WCDB::ColumnDef &getColumnDef(const WCTProperty &property);

private:
    void addProperty(const WCDB::String &columnName, const WCTColumnBinding &columnBinding);

    //TODO refactor using OrderedUniqueList. Note that column order should be tested.
    WCTProperties m_properties;
    // property name -> property iterator
    std::map<WCDB::String, WCTProperties::iterator> m_mappedProperties;

    // column name -> column binding
    std::map<WCDB::String, WCTColumnBinding, WCDB::String::CaseInsensiveComparator> m_columnBindings;

#pragma mark - Table
public:
    WCDB::StatementCreateVirtualTable statementVirtualTable;

    WCDB::StatementCreateTable
    generateCreateTableStatement(const WCDB::String &tableName) const;

    WCDB::StatementCreateVirtualTable
    generateVirtualCreateTableStatement(const WCDB::String &tableName) const;

#pragma mark - Table Constraint
public:
    WCDB::TableConstraint &getOrCreateTableConstraint(const WCDB::String &subfix);

private:
    std::map<WCDB::String, WCDB::TableConstraint> m_constraints;

#pragma mark - Index
public:
    WCDB::StatementCreateIndex &getOrCreateIndex(const WCDB::String &subfix);

    std::list<WCDB::StatementCreateIndex>
    generateCreateIndexStatements(const WCDB::String &tableName) const;

private:
    std::map<WCDB::String, WCDB::StatementCreateIndex> m_indexes;
};