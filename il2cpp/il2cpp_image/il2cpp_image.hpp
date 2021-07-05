#pragma once

#include <vector>
#include <optional>
#include "../il2cpp_class/il2cpp_class.hpp"

namespace il2cpp::types
{
	class il2cpp_t;

	class il2cpp_image_t
	{
		const std::uintptr_t instance;

		using classes_t = std::vector<std::pair<std::string, il2cpp_class_t>>;
		classes_t classes;

	public:

		std::uintptr_t get_instance() const;

		const classes_t& get_classes() const;

		std::optional<std::reference_wrapper<const il2cpp_class_t>> get_class(const std::string& class_name) const;

		il2cpp_image_t(il2cpp_image_t&&) = default;

		explicit il2cpp_image_t(const std::uintptr_t instance, const il2cpp_t& il2cpp);
	};
}