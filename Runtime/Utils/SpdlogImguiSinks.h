#pragma once

#include <spdlog/common.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/details/synchronous_factory.h>
#include <spdlog/sinks/base_sink.h>
#include <array>

#include <IMGUI_GLFW_OPENGL3.hpp>
#include <Global.hpp>

namespace spdlog
{
	namespace sinks
	{
		template <typename Mutex>
		class imgui_sink : public base_sink<Mutex>
		{
		public:
			imgui_sink(){ }
			~imgui_sink(){ }

		protected:
			void sink_it_(const details::log_msg& msg) override
			{
				memory_buf_t formatted;
				base_sink<Mutex>::formatter_->format(msg, formatted);
				const string_view_t str = string_view_t(formatted.data(), formatted.size());
				Spore::g_terminal_output.append(str.data());
			}

			void flush_() override { }

		private:
			std::string m_msg = "";
		};

	#include <spdlog/details/null_mutex.h>
	#include <mutex>

		using imgui_sink_mt = imgui_sink<std::mutex>;
		using imgui_sink_st = imgui_sink<details::null_mutex>;

		template<typename Factory = spdlog::synchronous_factory>
		inline std::shared_ptr<logger> imgui_logger_mt(const std::string& logger_name
													   )
		{
			return Factory::template create<sinks::imgui_sink_mt>(logger_name);
		}

		template<typename Factory = spdlog::synchronous_factory>
		inline std::shared_ptr<logger> imgui_logger_st(const std::string& logger_name)
		{
			return Factory::template create<sinks::imgui_sink_st>(logger_name);
		}
	}
}