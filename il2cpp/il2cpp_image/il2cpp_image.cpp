#include "il2cpp_image.hpp"

#include "../il2cpp/il2cpp.hpp"

std::uintptr_t il2cpp::types::il2cpp_image_t::get_instance() const
{
	return instance;
}

const il2cpp::types::il2cpp_image_t::classes_t& il2cpp::types::il2cpp_image_t::get_classes() const
{
    return classes;
}

std::optional<std::reference_wrapper<const il2cpp::types::il2cpp_class_t>> il2cpp::types::il2cpp_image_t::get_class(const std::string& class_name) const
{
    const auto classes_iterator = std::ranges::find(classes, class_name, &std::pair<std::string, il2cpp_class_t>::first);

    return classes_iterator == classes.cend() ? std::nullopt : std::make_optional(std::ref(classes_iterator->second));
}

il2cpp::types::il2cpp_image_t::il2cpp_image_t(const std::uintptr_t instance, const il2cpp_t& il2cpp) : instance{ instance }
{
    const auto classes_table = il2cpp.read<std::uintptr_t>(il2cpp.game_assembly + offsets::classes::class_table);

    const auto classes_size = il2cpp.read<std::uint32_t>(instance + 0x1C);

    const auto classes_index_start = il2cpp.read<std::uint32_t>(instance + 0x18);

    for (auto i = 0u; i < classes_size; ++i)
    {
        const auto current_class = il2cpp.read<std::uintptr_t>(classes_table + ((i + classes_index_start) * sizeof(std::uintptr_t)));

        classes.emplace_back(il2cpp.read_string(il2cpp.read<std::uintptr_t>(current_class + 0x10)), il2cpp_class_t{ current_class, il2cpp });
    }
}