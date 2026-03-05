#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <string>

namespace Botcraft::Renderer
{
    class RenderingManager;

    class Settings
    {
    public:
        static bool IsEnabled();

        /// @brief Set the renderer enabled state the for next client
        /// @param enable If true, next Client will try to create a renderer
        static void Enable(const bool enable = true);
        /// @brief Disable the rendering for all future clients
        static void Disable();
        /// @brief Make the renderer headless (hide the display window).
        /// @param headless If true, the window will be hidden (headless mode).
        /// Note that you still need *some* display device available to create the rendering context
        static void Headless(const bool headless = true);
        /// @brief Show/hide the rendering window
        /// @param show If true, the window will be shown, will be hidden otherwise (headless mode).
        /// Note that you still need *some* display device available to create the rendering context
        static void ShowWindow(const bool show = true);
        /// @brief Hide the rendering window
        static void HideWindow();
        /// @brief Try to change the resolution of the rendering window. This can be limited by specific OS constraints or a user resizing the window.
        static void SetResolution(const int width, const int height);
        /// @brief Get the current resolution of the renderer
        /// @return A pair of int, { width, height }
        static std::pair<int, int> GetResolution();
        /// @brief Render and save the next rendered frame
        /// @param path Path to save the PNG image to
        static void TakeScreenshot(const std::string& path);
        /// @brief Render the next image and pass the raw pixels to the given callback. Pixels are in HWC order
        /// @param callback Function to call with the frame raw pixels. Params are pixels, height, width
        static void TakeScreenshot(const std::function<void(const std::vector<unsigned char>& pixels, const int height, const int width)>& callback);
        /// @brief Enable/disable the vsync for the rendering loop
        /// @param enable If true, vsync will be enabled
        static void EnableVsync(const bool enable = true);
        /// @brief Disable the vsync for the rendering loop
        static void DisableVsync();
        /// @brief Set the max framerate for the rendering loop. Set to 0 for no limit
        static void SetMaxFramerate(const double fps);

        friend class Botcraft::Renderer::RenderingManager;

    private:
        static std::atomic<bool> enabled;
        static std::atomic<int> height;
        static std::atomic<int> width;
        static std::atomic<bool> headless;
        static std::atomic<bool> vsync;
        static std::atomic<double> target_fps;
        static std::mutex screenshot_mutex;
        static std::string screenhsot_path;
        static std::function<void(const std::vector<unsigned char>& pixels, const int height, const int width)> screenshot_callback;
    };
}
