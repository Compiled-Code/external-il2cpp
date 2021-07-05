#pragma once

#include <Windows.h>
#include <memory>
#include <stdexcept>
#include "../il2cpp_image/il2cpp_image.hpp"

namespace il2cpp::types
{
	class il2cpp_t
	{
		DWORD process_id;

		template <class type_t, auto deleter_t>
		using managed_t = std::unique_ptr<std::remove_pointer_t<type_t>, std::integral_constant<decltype(deleter_t), deleter_t>>;
		
		managed_t<HANDLE, CloseHandle> process_handle;

		using images_t = std::vector<std::pair<std::string, il2cpp_image_t>>;
		images_t images;

		std::uintptr_t get_module(const char* const module_name) const;

	public:

		std::uintptr_t game_assembly;

		template <class buffer_t>
		buffer_t read(const std::uintptr_t address) const
		{
			buffer_t buffer;

			if (!ReadProcessMemory(process_handle.get(), reinterpret_cast<const void*>(address), &buffer, sizeof(buffer_t), nullptr))
				throw std::runtime_error{ "fail read memory" };

			return buffer;
		}

		std::string read_string(std::uintptr_t address) const;

		const images_t& get_images() const;

		std::optional<std::reference_wrapper<const il2cpp_image_t>> get_image(const std::string& image_name) const;

		explicit il2cpp_t(const char* const window_name);
	};
}