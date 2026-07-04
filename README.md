# TRG-World

An Unreal Engine 5 game — work in progress. 🎮

> First-time game dev project. Built with UE5 and driven partly by an AI
> assistant through the [Unreal MCP](#ai-assisted-development-unreal-mcp).

## Requirements

- **Unreal Engine 5** (latest stable 5.x)
- **Visual Studio 2022** (Community) with the *Game development with C++* workload — Windows
- **Git** for version control

## Getting started

1. Clone this repository.
2. Right-click the `.uproject` file → **Generate Visual Studio project files**
   (only needed for C++ projects).
3. Double-click the `.uproject` to open it in the Unreal Editor.
4. If prompted to rebuild missing modules, click **Yes**.

## Project structure

| Path | Purpose |
|------|---------|
| `Config/`   | Project & engine settings (`.ini` files) — **committed** |
| `Content/`  | Assets, Blueprints, levels, materials — **committed** |
| `Source/`   | C++ source code — **committed** |
| `Plugins/`  | Plugin source (build output ignored) — **committed** |
| `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/` | Generated — **ignored** |

## AI-assisted development (Unreal MCP)

Part of this project is built with an AI assistant driving the Unreal Editor
via a local MCP (Model Context Protocol) server. That toolchain runs **locally**
alongside the editor. See `docs/SETUP.md` for the full setup walkthrough.

## Status

🚧 Setting up the development environment.
