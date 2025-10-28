{
  description = "Structura engine dev env";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          # Compiler and build tools
          gcc
          cmake
          ninja
          pkg-config

          # SDL3
          sdl3
          sdl3-image
          sdl3-ttf

          #OpenGL
          mesa
          libGLU
          libGL

          # Useful dev tools
          gdb
          valgrind
          clang-tools # for clangd LSP
        ];

        shellHook = ''
          echo "Structura engine dev environment loaded!"
          echo "Compiler: $(gcc --version | head -n1)"
          echo "CMake: $(cmake --version | head -n1)"
        '';

        # Set up environment variables
        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
          pkgs.libGL
          pkgs.libGLU
        ];
      };
    };
}
