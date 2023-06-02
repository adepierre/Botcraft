#include "protocolCraft/Utilities/Plugins/PluginLoader.hpp"
#include "protocolCraft/Utilities/Plugins/PluginObject.hpp"

#include <filesystem>
#include <functional>
#include <unordered_map>
#include <string_view>

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace ProtocolCraft
{
	namespace Internal
	{
		/// @brief Folder in which the protocolCraft plugins will be searched for
		constexpr std::string_view plugins_folder = "protocolcraft_plugins";

		// These are the expected signatures to load from the plugins.
		// We assume they are exposed with these names and signatures.
		PluginObject* (*GetPluginObject)(const char* identifier) = 0;
		void (*DestroyPluginObject)(PluginObject* object) = 0;

		template<typename F>
#ifdef _WIN32
		F GetKnownProcAddressImpl(HMODULE hmod, const char* module_name, const char* name, F)
#else
		F GetKnownProcAddressImpl(void* hmod, const char* module_name, const char* name, F)
#endif
		{
#ifdef _WIN32
			auto proc = GetProcAddress(hmod, name);
#else
			auto proc = dlsym(hmod, name);
#endif
			if (proc == NULL)
			{
				throw std::runtime_error(std::string("Couldn't load function ") + name + " from " + module_name);
			}
			return reinterpret_cast<F>(proc);
		}
#define GetKnownProcAddress(plugins_map, plugin_name, func) GetKnownProcAddressImpl(plugins_map[plugin_name], plugin_name.c_str(), #func, func);

		class PluginLoader
		{
		public:
			PluginLoader()
			{
				if (std::filesystem::exists(plugins_folder))
				{
					for (const auto& f : std::filesystem::directory_iterator(plugins_folder))
					{
						const std::string path_str = f.path().string();
#ifdef _WIN32
						plugins[path_str] = LoadLibraryA(path_str.c_str());
#else
						plugins[path_str] = dlopen(path_str.c_str(), RTLD_NOW);
#endif
						if (plugins[path_str] == NULL)
						{
							throw std::runtime_error("Couldn't load plugin at " + path_str);
						}

						GetPluginObject_funcs[path_str] = GetKnownProcAddress(plugins, path_str, GetPluginObject);
						DestroyPluginObject_funcs[path_str] = GetKnownProcAddress(plugins, path_str, DestroyPluginObject);
					}
				}
			}

			~PluginLoader()
			{
				GetPluginObject_funcs.clear();
				DestroyPluginObject_funcs.clear();
				cached_identifier_to_plugin.clear();

				for (auto& [k, v] : plugins)
				{
#ifdef _WIN32
					FreeLibrary(v);
#else
					dlclose(v);
#endif
				}
			}

			std::shared_ptr<PluginObject> CreatePluginObject(const char* identifier)
			{
				const auto it = cached_identifier_to_plugin.find(identifier);
				// First time we encounter this identifier
				if (it == cached_identifier_to_plugin.end())
				{
					for (const auto& [k, v] : GetPluginObject_funcs)
					{
						PluginObject* ptr = v(identifier);
						if (ptr != nullptr)
						{
							cached_identifier_to_plugin[identifier] = k;
							return std::shared_ptr<PluginObject>(ptr, DestroyPluginObject_funcs[k]);
						}
					}
					// No plugin for this identifier
					cached_identifier_to_plugin[identifier] = "";
				}
				// We know this identifier exists in a known plugin
				else if (!it->second.empty())
				{
					PluginObject* raw_ptr = GetPluginObject_funcs[it->second](identifier);
					if (raw_ptr != nullptr)
					{
						return std::shared_ptr<PluginObject>(raw_ptr, DestroyPluginObject_funcs[it->second]);
					}
				}
				// If we reach this, we know there is no plugin with this identifier
				return nullptr;
			}

		private:
#if _WIN32
			std::unordered_map<std::string, HMODULE> plugins;
#else
			std::unordered_map<std::string, void*> plugins;
#endif
			std::unordered_map<std::string, std::function<PluginObject* (const char*)>> GetPluginObject_funcs;
			std::unordered_map<std::string, std::function<void(PluginObject*)>> DestroyPluginObject_funcs;

			std::unordered_map<std::string, std::string> cached_identifier_to_plugin;
		};
	}

	std::shared_ptr<PluginObject> CreateObjectFromPlugin(const char* identifier)
	{
		static Internal::PluginLoader loader;
		return loader.CreatePluginObject(identifier);
	}
}
