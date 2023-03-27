#pragma once

namespace lpa
{
	using uint = unsigned;

	template <typename T>
	using Ref = std::reference_wrapper<T>;

	template <typename T>
	using UPtr = std::unique_ptr<T>;
}

