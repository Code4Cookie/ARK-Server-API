#pragma once

#include <functional>
#include <utility>

#include "API/Base.h"

namespace API
{
	class Requests
	{
	public:
		ARK_API static Requests& Get();

		Requests(const Requests&) = delete;
		Requests(Requests&&) = delete;
		Requests& operator=(const Requests&) = delete;
		Requests& operator=(Requests&&) = delete;

		ARK_API bool CreateGetRequest(const std::string& url, const std::function<void(bool, std::string)>& callback);

		ARK_API bool CreatePostRequest(const std::string& url, const std::function<void(bool, std::string)>& callback,
		                               const std::string& post_data);

	private:
		using CURLM = void;
		using CURL = void;

		struct Request
		{
			explicit Request(std::function<void(bool, std::string)> callback)
				: callback(std::move(callback))
			{
			}

			std::function<void(bool, std::string)> callback;
			std::string read_buffer;
		};

		Requests();
		~Requests();

		static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
		void Update(float);

		CURLM* curl_;
		int handles_count_{};
		std::unordered_map<CURL*, std::unique_ptr<Request>> requests_;
	};
} // namespace API
