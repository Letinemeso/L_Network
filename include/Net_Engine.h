#pragma once

#include <string>


namespace LNet
{

    class Net_Engine
    {
    private:
        std::string m_log_level_name = "L_Network";

    private:
        Net_Engine();
        ~Net_Engine();

        Net_Engine(const Net_Engine&) = delete;
        Net_Engine(Net_Engine&&) = delete;
        void operator=(const Net_Engine&) = delete;
        void operator=(Net_Engine&&) = delete;

    public:
        inline static Net_Engine& instance() { static Net_Engine s_instance; return s_instance; }

        inline const std::string& log_level() const { return m_log_level_name; }

    };

}
