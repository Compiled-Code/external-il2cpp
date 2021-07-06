#include "il2cpp/il2cpp/il2cpp.hpp"

int main()
{
	auto il2cpp = il2cpp::types::il2cpp_t{ "Rust" };

	if (const auto assembly_csharp = il2cpp.get_image("Assembly-CSharp"))
	{
		std::printf("[il2cpp-external] assembly_csharp => 0x%p\n", assembly_csharp->get().get_instance());

		if (const auto base_networkable = assembly_csharp->get().get_class("BaseNetworkable"))
		{
			std::printf("[il2cpp-external] base_networkable => 0x%p\n", base_networkable->get().get_instance());

			const auto client_entities = il2cpp.read<std::uintptr_t>(base_networkable->get().get_static_field("clientEntities"));

			std::printf("[il2cpp-external] client_entities => 0x%p\n", client_entities);
		}
	}

	return 1;
}
