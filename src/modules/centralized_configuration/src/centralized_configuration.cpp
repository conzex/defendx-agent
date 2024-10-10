#include <centralized_configuration.hpp>

#include <module_command/command_entry.hpp>

#include <nlohmann/json.hpp>

namespace centralized_configuration
{
    void CentralizedConfiguration::Start() const
    {
    }

    void CentralizedConfiguration::Setup(const configuration::ConfigurationParser&) const
    {
    }

    void CentralizedConfiguration::Stop() const
    {
    }

    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    Co_CommandExecutionResult CentralizedConfiguration::ExecuteCommand(const std::string command)
    {
        const auto commnandAsJson = nlohmann::json::parse(command);

        if (commnandAsJson["command"] == "set-group")
        {
            if (m_setGroupIdFunction)
            {
                std::vector<std::string> groupIds;

                m_setGroupIdFunction(groupIds);

                co_return module_command::CommandExecutionResult{
                    module_command::Status::SUCCESS,
                    "CentralizedConfiguration group set"
                };
            }
            else
            {
                co_return module_command::CommandExecutionResult{
                    module_command::Status::FAILURE,
                    "CentralizedConfiguration group set failed, no function set"
                };
            }
        }
        else if (commnandAsJson["command"] == "update-group")
        {
            co_return module_command::CommandExecutionResult{
                module_command::Status::SUCCESS,
                "CentralizedConfiguration group updated"
            };
        }

        co_return module_command::CommandExecutionResult{
            module_command::Status::FAILURE,
            "CentralizedConfiguration command not recognized"
        };
    }

    std::string CentralizedConfiguration::Name() const
    {
        return "CentralizedConfiguration";
    }

    void CentralizedConfiguration::SetGroupIdFunction(std::function<void(const std::vector<std::string>&)> setGroupIdFunction)
    {
        m_setGroupIdFunction = std::move(setGroupIdFunction);
    }
} // namespace centralized_configuration
