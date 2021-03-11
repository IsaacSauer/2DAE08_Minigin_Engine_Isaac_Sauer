#pragma once
#include <fstream>
#include <thread>
#include <mutex>
#include "Singleton.h"

//drag the json file to chrome://tracing to visualize

namespace dae
{
	class Session : public Singleton<Session>
	{
	private:
		std::ofstream m_OutputStream;
		bool m_first{true};

		std::mutex m_SaveMutex;
	public:

		void BeginSession(const std::string& filepath = "measurements.json") {
			m_OutputStream.open(filepath);
			m_OutputStream << "{\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void EndSession() {
			m_OutputStream << "]}";
			m_OutputStream.flush();
			m_OutputStream.close();
			m_first = true;
		}

		void SaveMeasurement(const std::string& Name, int64_t Start, int64_t End, const std::thread::id& ThreadID)
		{
			std::lock_guard<std::mutex> guard(m_SaveMutex);
			
			if (m_first)
				m_first = false;
			else
				m_OutputStream << ",";

			m_OutputStream << "{" << "\"cat\":\"function\",\"dur\":" << (End - Start) << ",\"name\":\"" << Name << "\",";
			m_OutputStream << "\"ph\":\"X\",\"pid\":0," << "\"tid\":" << ThreadID << "," << "\"ts\":" << Start << "}";

			m_OutputStream.flush();
		}
	};
}