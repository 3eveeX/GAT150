#pragma once

namespace whermst{
	template <typename T>
	class Singleton
	{
	public:

		Singleton(const Singleton&) = delete; // Disable copy constructor
		Singleton& operator=(const Singleton&) = delete; // Disable copy assignment

		static T& Instance()
		{
			static T instance;
			return instance;
		}
	protected:
		Singleton() = default;
	};
}