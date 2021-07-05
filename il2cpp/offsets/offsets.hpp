#pragma once

#include <cstdint>

namespace il2cpp::offsets::classes
{
	constexpr auto class_table = 0x2F44AD0; // 90 48 8B 05 ?? ?? ?? ?? 48 83 3C 03 00 75 -> mov rax, CLASS_TABLE
}

namespace il2cpp::offsets::assembly
{
	constexpr auto assemblies_begin = 0x2F44FE8; // il2cpp_domain_get_assemblies -> into first call -> lea rax, ASSEMBLIES_BEGIN

	constexpr auto assemblies_end = assemblies_begin + sizeof(std::uintptr_t);
}