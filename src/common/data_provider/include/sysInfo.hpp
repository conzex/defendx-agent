/*
 * Wazuh SysInfo
 * Copyright (C) 2015, Wazuh Inc.
 * October 8, 2020.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation.
 */

#ifndef _SYS_INFO_HPP
#define _SYS_INFO_HPP

#include "sysInfoInterface.hpp"

constexpr auto KByte
{
    1024
};

class SysInfo: public ISysInfo
{
    public:
        SysInfo() = default;
        // LCOV_EXCL_START
        virtual ~SysInfo() = default;
        // LCOV_EXCL_STOP
        nlohmann::json hardware();
        nlohmann::json packages();
        nlohmann::json os();
        nlohmann::json processes();
        nlohmann::json networks();
        nlohmann::json ports();
        void packages(std::function<void(nlohmann::json&)>);
        void processes(std::function<void(nlohmann::json&)>);
        nlohmann::json hotfixes();
    private:
        virtual nlohmann::json getHardware() const;
        virtual nlohmann::json getPackages() const;
        virtual nlohmann::json getOsInfo() const;
        virtual nlohmann::json getProcessesInfo() const;
        virtual nlohmann::json getNetworks() const;
        virtual nlohmann::json getPorts() const;
        virtual nlohmann::json getHotfixes() const;
        virtual void getPackages(std::function<void(nlohmann::json&)>) const;
        virtual void getProcessesInfo(std::function<void(nlohmann::json&)>) const;
};

#endif //_SYS_INFO_HPP
