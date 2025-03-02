from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def layout(self):
        self.folders.generators = "_conan"

    def requirements(self):
        self.requires("raylib/5.5")

    def build_requirements(self):
        pass

    def layout(self):
        cmake_layout(self)