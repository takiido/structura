{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "structura-engine-dev";

  buildInputs = with pkgs; [
    cmake
    gcc
    gdb
    ninja
    pkg-config

    # SDL3
    glew
    glfw
    glm
    libGL
    libGLU
    libdrm
    libffi
    libxkbcommon
    mesa
    pulseaudio
    wayland
    wayland-protocols
    wayland-scanner
    xorg.libX11
    xorg.libXScrnSaver
    xorg.libXcursor
    xorg.libXext
    xorg.libXi
    xorg.libXinerama
    xorg.libXrandr
    xorg.xinput

    # UI Library
    imgui
    freetype
  ];

  shellHook = ''
    export SDL_VIDEODRIVER=wayland
    export SDL_VIDEODRIVER_X11=x11
    export SDL_AUDIODRIVER=pulseaudio
    export CMAKE_GENERATOR=Ninja

    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${pkgs.libGL.dev}/lib/pkgconfig:${pkgs.libxkbcommon.dev}/lib/pkgconfig:${pkgs.libffi.dev}/lib/pkgconfig

    export SDL3_DIR=${pkgs.sdl3.dev}/lib/cmake/SDL3

    if command -v zeditor &>/dev/null; then
      zeditor .
    else
      echo "Tip: zeditor not found, skipping."
    fi
  '';
}
