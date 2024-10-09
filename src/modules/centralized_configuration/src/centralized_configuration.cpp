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
            co_return module_command::CommandExecutionResult{
                module_command::Status::SUCCESS,
                "CentralizedConfiguration group set"
            };
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
} // namespace centralized_configuration
