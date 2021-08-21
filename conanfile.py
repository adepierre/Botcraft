from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration


class BotcraftConan(ConanFile):
    name = "botcraft"
    version = "0.1"
    license = "GPL-3.0-or-later"
    author = "adepierre"
    url = "https://github.com/adepierre/Botcraft"
    description = "Botcraft is a cross-platform C++ library to connect and interact with Minecraft servers with (optional) integrated OpenGL renderer."
    topics = ("minecraft", "bot", "opengl")
    settings = "os", "compiler", "build_type", "arch"
    options = {"use_opengl": [True, False], "compression": [
        True, False], "encryption": [True, False], "use_imgui": [True, False], "game_version": "ANY", "build_examples": [True, False], "install_assets": [True, False],
        "fPIC": [True, False]}
    default_options = {"use_opengl": False, "use_imgui": False,
                       "compression": True, "encryption": True, "game_version": "latest",
                       "build_examples": True, "install_assets": True, "fPIC": True}
    generators = "cmake"

    exports_sources = "botcraft/*", "protocolCraft/*", "CMakeLists.txt", "3rdparty/*", "Assets/*", "Examples/*"
    _cmake = None

    @property
    def _source_subfolder(self):
        return "source_subfolder"

    def _supports_cpp17(self):
        supported_compilers = [
            ("gcc", "7"), ("clang", "5"), ("apple-clang", "10"), ("Visual Studio", "15.7")]
        compiler = self.settings.compiler
        version = tools.Version(compiler.version)
        return any(compiler == sc[0] and version >= sc[1] for sc in supported_compilers)

    def configure(self):
        if self.settings.compiler.get_safe("cppstd"):
            tools.check_min_cppstd(self, "17")
        elif not self._supports_cpp17():
            raise ConanInvalidConfiguration("Botcraft requires C++17 support")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
        if not self.options.use_opengl:
            del self.options.use_imgui

    def requirements(self):
        self.requires("asio/1.18.2")
        self.requires("nlohmann_json/3.9.1")
        if self.options.compression:
            self.requires("zlib/1.2.11")
        if self.options.encryption:
            self.requires("openssl/1.1.1k")
        if self.options.use_opengl:
            self.requires("glad/0.1.34")
            self.requires("glfw/3.3.4")
            self.requires("glm/0.9.9.8")
            self.requires("rectpack2D/cci.20210710")
            self.requires("stb/20200203")
            if self.options.use_imgui:
                self.requires("imgui/1.74")

    def _configure_cmake(self):
        if self._cmake:
            return self._cmake
        self._cmake = CMake(self)

        self._cmake.definitions["BOTCRAFT_USE_OPENGL_GUI"] = self.options.use_opengl
        if self.options.use_opengl:
            self._cmake.definitions["BOTCRAFT_USE_IMGUI"] = self.options.use_imgui
        self._cmake.definitions["BOTCRAFT_COMPRESSION"] = self.options.compression
        self._cmake.definitions["BOTCRAFT_ENCRYPTION"] = self.options.encryption
        self._cmake.definitions["BOTCRAFT_BUILD_EXAMPLES"] = self.options.build_examples
        self._cmake.definitions["BOTCRAFT_INSTALL_ASSETS"] = self.options.install_assets
        self._cmake.configure()
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        self.copy("LICENSE", dst="licenses", src=self._source_subfolder)
        cmake = self._configure_cmake()
        cmake.install()
        # self.copy("*.h", dst="include", src="src")
        # self.copy("*.lib", dst="lib", keep_path=False)
        # self.copy("*.dll", dst="bin", keep_path=False)
        # self.copy("*.dylib*", dst="lib", keep_path=False)
        # self.copy("*.so", dst="lib", keep_path=False)
        # self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["botcraft"]
