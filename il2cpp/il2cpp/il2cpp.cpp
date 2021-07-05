#include "il2cpp.hpp"

#include <TlHelp32.h>
#include <ranges>

std::uintptr_t il2cpp::types::il2cpp_t::get_module(const char* const module_name) const
{
    if (const auto process_snapshot = managed_t<HANDLE, CloseHandle>{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id) }; process_snapshot.get() != INVALID_HANDLE_VALUE)
    {
        auto module_entry = MODULEENTRY32{ sizeof(MODULEENTRY32) };

        do
        {
            if (!std::strcmp(module_entry.szModule, module_name))
                return reinterpret_cast<std::uintptr_t>(module_entry.modBaseAddr);
        } while (Module32Next(process_snapshot.get(), &module_entry));
    }

    return 0;
}

std::string il2cpp::types::il2cpp_t::read_string(std::uintptr_t address) const
{
    std::string buffer;

    do
        buffer.push_back(read<char>(address++));
    while (read<char>(address) != '\0');

    return buffer;
}

const il2cpp::types::il2cpp_t::images_t& il2cpp::types::il2cpp_t::get_images() const
{
    return images;
}

std::optional<std::reference_wrapper<const il2cpp::types::il2cpp_image_t>> il2cpp::types::il2cpp_t::get_image(const std::string& image_name) const
{
    const auto images_iterator = std::ranges::find(images, image_name, &std::pair<std::string, il2cpp_image_t>::first);

    return images_iterator == images.cend() ? std::nullopt : std::make_optional(std::ref(images_iterator->second));
}

il2cpp::types::il2cpp_t::il2cpp_t(const char* const window_name)
{
    const auto process_window = FindWindowA(nullptr, window_name);

    GetWindowThreadProcessId(process_window, &process_id);

    process_handle = managed_t<HANDLE, CloseHandle>{ OpenProcess(PROCESS_ALL_ACCESS, false, process_id) };

    game_assembly = get_module("GameAssembly.dll");

    const auto assemblies_end = read<std::uintptr_t>(game_assembly + offsets::assembly::assemblies_end);

    for (auto current_assembly = read<std::uintptr_t>(game_assembly + offsets::assembly::assemblies_begin); current_assembly < assemblies_end; current_assembly += sizeof(std::uintptr_t))
        images.emplace_back(read_string(read<std::uintptr_t>(read<std::uintptr_t>(current_assembly) + 0x18)), il2cpp_image_t{ read<std::uintptr_t>(read<std::uintptr_t>(current_assembly)), *this });
}