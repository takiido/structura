# Structura engine
## Description
This is simple game engine i am developing in my free time as a hobby. It is build with **E**ntity **C**omponent **S**ystem (ECS) architecture principles in mind. Its main purpose is to help me learn game engines architecture(ECS specifically) and improve my C++ skills.

---

## Project structure
The engine is divided into three parts:
1. **Engine** - "API", the reusable part - the "game engine" itself.
2. **Editor** - tool, basically my "Unity Editor".
3. **Runtime** - game build - player runs this.

---

## Build
### Build from source
> [!TIP]
> If you are using nixos run
> ```bash
> nix-shell
> ```
> from project root - this will drop you into a fully configured dev environment with all dependencies installed.

#### To build:
```bash
chmod +x ./build.sh
./build.sh
```
#### To build and run:
```bash
chmod +x ./build_and_run.sh
./build_and_run.sh
```

---

## Roadmap

---

## Dependencies
The project depends on the following libraries:
- **CMake** - build system
- **Ninja** - fast incremental builds
- **GLM** - math library
- **GLEW** - OpenGL extension wrapper
- **SDL 3** - windowing, input, and rendering
- **Dear ImGui** - for editor
> [!NOTE]
> If you're using NixOS, all of these are pulled automatically by the provided `shell.nix`
