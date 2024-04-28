#ifndef TIME_MANAGER_HEADER
#define TIME_MANAGER_HEADER

#include <memory>
#include <string>
#include <unordered_map>

class TimeManager {
public:
	TimeManager(TimeManager&) = delete;
	void operator=(const TimeManager&) = delete;

	static TimeManager* get_instance() {
		if (!m_time_manager) m_time_manager = std::unique_ptr<TimeManager>(new TimeManager());
		return m_time_manager.get();
	}

	void update_tracks(float delta_time_as_seconds) { 
		for (auto& [job_name, record] : m_job_names_to_records) { 
			record.current_time -= delta_time_as_seconds;
			if (record.current_time <= 0) record.current_time = 0;
		}
	}

	void track_job(const std::string job_name, float total_time) { 
		if (total_time <= 0) throw("Can't track a job that doesn't take time");
		m_job_names_to_records.insert({job_name, TimeJobRecord(total_time, total_time)});
	}

	float get_time_left(const std::string job_name) {
		if (!m_job_names_to_records.contains(job_name)) return 0;
		auto record = m_job_names_to_records.at(job_name);
		if (record.current_time == 0) m_job_names_to_records.erase(job_name);
		return record.current_time;
	}

	bool is_job_done(const std::string job_name) {
		if (!m_job_names_to_records.contains(job_name)) return true;
		bool job_is_done = m_job_names_to_records.at(job_name).current_time == 0;
		if (job_is_done) m_job_names_to_records.erase(job_name);
		return job_is_done;
	}

protected:
	TimeManager() {}
	inline static std::unique_ptr<TimeManager> m_time_manager;

	struct TimeJobRecord {
		float current_time;
		float total_time;
	};

private:
	std::unordered_map<std::string, TimeJobRecord> m_job_names_to_records;
	
};


#endif