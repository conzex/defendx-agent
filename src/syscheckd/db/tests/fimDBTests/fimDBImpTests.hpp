#ifndef _FIMDB_IMP_TEST_H
#define _FIMDB_IMP_TEST_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "fimDB.hpp"
#include "dbItem.hpp"
#include "syscheck-config.h"
#include "fimCommonDefs.h"

class MockDBSyncHandler: public DBSync
{

    public:
        MockDBSyncHandler(const HostType hostType,
                          const DbEngineType dbType,
                          const std::string& path,
                          const std::string& sqlStatement): DBSync(hostType, dbType, path, sqlStatement) {};
        ~MockDBSyncHandler() {};
        MOCK_METHOD(void, setTableMaxRow, (const std::string&, const unsigned long long), (override));
        MOCK_METHOD(void, insertData, (const nlohmann::json&), (override));
        MOCK_METHOD(void, deleteRows, (const nlohmann::json&), (override));
        MOCK_METHOD(void, syncRow, (const nlohmann::json&, ResultCallbackData), (override));
        MOCK_METHOD(void, selectRows, (const nlohmann::json&, ResultCallbackData), (override));
};

class MockRSyncHandler: public RemoteSync
{

    public:
        MockRSyncHandler() {};
        ~MockRSyncHandler() {};
        MOCK_METHOD(void, registerSyncID, (const std::string&, const DBSYNC_HANDLE, const nlohmann::json&, SyncCallbackData), (override));
        MOCK_METHOD(void, startSync, (const DBSYNC_HANDLE, const nlohmann::json&, SyncCallbackData), (override));
};

class MockFIMDB: public FIMDB
{
    public:
        MockFIMDB() {};
        ~MockFIMDB() {};

        void setFileLimit()
        {
            FIMDB::setFileLimit();
        }

        void setRegistryLimit()
        {
            FIMDB::setRegistryLimit();
        }

        void setValueLimit()
        {
            FIMDB::setValueLimit();
        }

        void stopSync()
        {
            FIMDB::stopSync();
        }
};

class MockLoggingCall
{
    public:
        MOCK_METHOD(void, loggingFunction, (const modules_log_level_t, const std::string&), ());
};

class MockSyncMsg
{
    public:
        MOCK_METHOD(void, syncMsg, (const char*, const char*), ());
};

#endif //_FIMDB_IMP_TEST_H
