#pragma once

#include <string>
#include <optional>
#include "../offsets/offsets.hpp"

namespace il2cpp::types
{
	class il2cpp_t;

	class il2cpp_class_t
	{
		const std::uintptr_t instance, fields_table, static_fields_table;

		std::uint16_t fields_size;

		const il2cpp_t& il2cpp;

		std::optional<std::uint32_t> get_field_key(const std::string& field_name) const;

	public:

		std::uintptr_t get_instance() const;
		
		std::uintptr_t get_static_field(const std::string& field_name) const;

		std::uintptr_t get_field(const std::string& field_name) const;

		il2cpp_class_t(il2cpp_class_t&&) = default;

		explicit il2cpp_class_t(const std::uintptr_t instance, const il2cpp_t& il2cpp);
	};
}