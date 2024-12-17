# Unreal MPV

## Implementation of mpv media player into Unreal Engine 5

![Logo of Unreal MPV](Unreal-MPV_Logo.png)

## Documentation

### Build mpv for unreal using MSYS2 (Clang)
*This process take reference from the compile windows page on mpv github repo.*

### Getting mpv
1. Navigate to "Plugins/unreal_mpv/Dependencies/"
2. Clone mpv repository
``` bash
git clone git@github.com:mpv-player/mpv.git
```

### Installing MSYS2

1. Follow the installation steps from [MSYS2](https://www.msys2.org/).
2. Initiate one of the [Environments](https://www.msys2.org/docs/environments/),
   with the CLANG64 (``clang64.exe``) being the recommended option.
   **Note:** This environment is distinct from the MSYS2 shell that opens
   automatically after the final installation dialog. You must close that
   initial shell and open a new one for the appropriate environment.

### Updating MSYS2

For guidance on updating MSYS2, please refer to the official documentation:
[Updating MSYS2](https://www.msys2.org/docs/updating/).

### Installing mpv Dependencies

``` bash
# Install pacboy and git
pacman -S pactoys git

# Install MSYS2 build dependencies and a MinGW-w64 compiler
pacboy -S python pkgconf cc meson

# Install key dependencies. libass and lcms2 are also included as dependencies
# of ffmpeg.
pacboy -S ffmpeg libjpeg-turbo libplacebo luajit vulkan-headers
```

### Building mpv for unreal

Since unreal doesn't work with static libraries we need to configure meson to get a shared library (.lib), we'll interface mpv on unreal using libmpv.
``` bash
meson configure build -Dlibmpv=true -Ddefault_library=shared
```

To compile and install mpv, execute the following commands.
The binaries will be installed in the directory ``/$MSYSTEM_PREFIX/bin``.

```bash
# Set up the build directory with the desired configuration
meson setup build -Dlibmpv=true --prefix=$MSYSTEM_PREFIX

# Compile
meson compile -C build
```

The compilation will provide us a dll file, we now need to generate the .lib

```bash
# get the .def file
gendef libmpv.dll

# generate .lib file
lib /def:libmpv.def /out:libmpv.lib /MACHINE:X64
```

Place the newly generated "libmpv-2.dll" at (Plugins/unreal_mpv/Binaries/Win64/)

### Add mpv dependencies to project
In order to get a clean plugin build in unreal, we need to provide unreal with a list of libraries needed by mpv.

You can find the library previously installed using pacman in (C:\msys64\clang64\bin\)

Thoses libraries need to be placed in (Plugins/unreal_mpv/Binaries/ThirdParty/UnrealMpvLib/Win64/)

```
# Required libraries

"libiconv-2.dll",
"libfribidi-0.dll",
"zlib1.dll",
"libbz2-1.dll",
"libpng16-16.dll",
"libbrotlicommon.dll",
"libbrotlidec.dll",
"libglib-2.0-0.dll",
"libintl-8.dll",
"libc++.dll",
"libgraphite2.dll",
"USP10.dll",
"libfreetype-6.dll",
"libharfbuzz-0.dll",
"libunibreak-6.dll",
"libfontconfig-1.dll",
"libass-9.dll",
"avcodec-60.dll",
"avfilter-9.dll",
"avformat-60.dll",
"avutil-58.dll",
"libplacebo-349.dll",
"swresample-4.dll",
"swscale-7.dll",
"AVRT.dll",
"liblcms2-2.dll",
"avdevice-60.dll",
"libbluray-2.dll",
"lua51.dll",
"libzimg-2.dll",
"libcaca-0.dll",
"libjpeg-8.dll",
"libshaderc_shared.dll",
"libspirv-cross-c-shared.dll",
"vulkan-1.dll",
"libva_win32.dll",
"libva.dll"
```

Now you can build the unreal project via visual studio.

*At the time of updating this documentation, theres a circular dependency issue coming from harfbuzz <-> freetype, this need fixing*
