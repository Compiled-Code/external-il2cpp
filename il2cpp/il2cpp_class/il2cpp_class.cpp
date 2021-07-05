#include "il2cpp_class.hpp"

#include "../il2cpp/il2cpp.hpp"

std::uintptr_t il2cpp::types::il2cpp_class_t::get_instance() const
{
	return instance;
}

std::optional<std::uint32_t> il2cpp::types::il2cpp_class_t::get_field_key(const std::string& field_name) const
{
	for (auto current_field = fields_table; current_field < fields_table + (fields_size * 0x20); current_field += 0x20)
	{
		const auto current_field_name = il2cpp.read_string(il2cpp.read<std::uintptr_t>(current_field));

		if (current_field_name == field_name)
			return il2cpp.read<std::uint32_t>(current_field + 0x18);
	}

	return std::nullopt;
}

std::uintptr_t il2cpp::types::il2cpp_class_t::get_static_field(const std::string& field_name) const
{
	if (const auto current_field_key = get_field_key(field_name))
	{
		const auto current_field_value = static_fields_table + current_field_key.value();

		return current_field_value;
	}

	return 0;
}

std::uintptr_t il2cpp::types::il2cpp_class_t::get_field(const std::string& field_name) const
{
	if (const auto current_field_key = get_field_key(field_name); current_field_key.has_value())
	{
		const auto current_field_value = instance + current_field_key.value();

		return current_field_value;
	}

	return 0;
}

il2cpp::types::il2cpp_class_t::il2cpp_class_t(const std::uintptr_t instance, const il2cpp_t& il2cpp)
:
	instance{ instance },
	il2cpp{ il2cpp },

	fields_size{ il2cpp.read<std::uint16_t>(instance + 0x11C) },
	fields_table{ il2cpp.read<std::uintptr_t>(instance + 0x80) },
	static_fields_table{ il2cpp.read<std::uintptr_t>(instance + 0xB8) }
{}