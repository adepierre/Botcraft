#include "botcraft/Renderer/Settings.hpp"
#include "botcraft/Utilities/Logger.hpp"

#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

namespace Botcraft::Renderer
{
#if !USE_GUI
        static bool settings_first_time = true;
#define CHECK_GUI if (settings_first_time) { LOG_WARNING("Botcraft compiled without UI support. Rendering function call ignored. Recompile with BOTCRAFT_USE_GUI to enable GUI support."); } settings_first_time = false
#else
    #define CHECK_GUI static_assert(true, "requires ; after call")
#endif

    std::atomic<bool> Settings::enabled = false;
    std::atomic<int> Settings::width = 800;
    std::atomic<int> Settings::height = 600;
    std::atomic<bool> Settings::headless = false;
    std::atomic<bool> Settings::vsync = true;
    std::atomic<double> Settings::target_fps = 60.0;

    std::mutex Settings::screenshot_mutex;
    std::string Settings::screenhsot_path = "";
    std::function<void(const std::vector<unsigned char>& pixels, const int height, const int width)> Settings::screenshot_callback = nullptr;

    bool Settings::IsEnabled()
    {
        CHECK_GUI;
#if !USE_GUI
        return false;
#else
        return enabled.load(std::memory_order_relaxed);
#endif
    }

    void Settings::Enable(const bool enable)
    {
        CHECK_GUI;
#if USE_GUI
        enabled = enable;
#endif
    }

    void Settings::Disable()
    {
        CHECK_GUI;
        enabled = false;
    }

    void Settings::Headless(const bool headless)
    {
        CHECK_GUI;
        Settings::headless = headless;
    }

    void Settings::ShowWindow(const bool show)
    {
        CHECK_GUI;
        headless = !show;
    }

    void Settings::HideWindow()
    {
        CHECK_GUI;
        headless = true;
    }

    void Settings::SetResolution(const int width, const int height)
    {
        CHECK_GUI;
        Settings::width = width;
        Settings::height = height;
    }

    std::pair<int, int> Settings::GetResolution()
    {
        return { width, height };
    }

    void Settings::TakeScreenshot(const std::string& path)
    {
        CHECK_GUI;
        std::scoped_lock<std::mutex> lock(screenshot_mutex);
        screenhsot_path = path;
    }

    void Settings::TakeScreenshot(const std::function<void(const std::vector<unsigned char>&, const int, const int)>& callback)
    {
        CHECK_GUI;
        std::scoped_lock<std::mutex> lock(screenshot_mutex);
        screenshot_callback = callback;
    }

    void Settings::EnableVsync(const bool enable)
    {
        CHECK_GUI;
        vsync = enable;
    }

    void Settings::DisableVsync()
    {
        CHECK_GUI;
        vsync = false;
    }

    void Settings::SetMaxFramerate(const double fps)
    {
        CHECK_GUI;
        target_fps = fps;
    }
}
