{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "structura-engine-dev";

  buildInputs = with pkgs; [
    cmake
    gcc
    gdb
    ninja
    pkg-config

    # Graphics / input
    glew
    glm
    mesa
    libGL
    libGLU
    libdrm
    libffi
    libxkbcommon
    wayland
    wayland-protocols
    xorg.libX11
    xorg.libXext
    xorg.libXrandr
    xorg.libXcursor
    xorg.libXi
    xorg.libXinerama
    xorg.libXScrnSaver
    xorg.xinput
    pulseaudio
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
