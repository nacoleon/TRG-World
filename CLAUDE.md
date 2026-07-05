# CLAUDE.md — TRG-World project context

> Read this first. It orients any Claude Code session on what this project is,
> what's installed, decisions made, and what's next. Fuller detail lives in
> `docs/` (GAME_DESIGN.md, SETUP.md).

## What we're building

A **3D cave-crawler game in Unreal Engine 5**, based on **The Rune Guardians**
IP (https://theruneguardians.com). Rune Guardian miners explore caves across
multiple regions, mine crystals, battle cave monsters, and defeat a region
**boss** to unlock the exit and move on. See `docs/GAME_DESIGN.md` for the full
design doc.

## Key decisions (locked)

- **Mobile-first**: primary target is **iPhone / iPad (iOS)**. Touch controls,
  Mobile renderer, Nanite/Lumen/RT OFF, baked lighting, 30–60 FPS budget.
  (Shipping to iOS eventually needs a Mac + Apple Developer account — dev/test
  happens on the Windows PC.)
- **Economy is simulated in-game for v1** — crystals/TRG Runes are just in-game
  counters. No blockchain / real TRG token integration yet.
- **Camera**: third-person (starting from the UE Third Person template).
- **AI tooling**: use the **official Epic "Unreal MCP" plugin** (built into
  UE 5.8), driven by **Claude Code**. We migrated OFF the community
  `chongdashu/unreal-mcp` plugin (see history below).

## Tech stack & environment (Windows PC)

| Thing | Version / value |
|-------|-----------------|
| Unreal Engine | **5.8** (installed at `C:\Program Files\Epic Games\UE_5.8`) |
| Visual Studio | 2022 Community, "Game development with C++" workload |
| Python (system) | 3.14.6 |
| Python (pinned for tools) | 3.13 (via `uv python pin`) |
| uv | 0.11.26 (`C:\Users\nacoleon\.local\bin\uv.exe`) |

## Important local paths (this machine)

- **Unreal project**: `C:\Users\nacoleon\Documents\Unreal Projects\TRG-World\TRGWorld\`
  (contains `TRGWorld.uproject`, now a **C++** project)
- **This git repo** (`nacoleon/trg-world`): currently holds docs/scripts only —
  see "Repo vs. project location" below.
- Old community MCP (being retired): `C:\Users\nacoleon\Dev\unreal-mcp-main\`

## MCP setup (official Epic plugin)

- Enable **Edit → Plugins → "Unreal MCP" (Experimental, Epic Games)**; it pulls
  in the **Toolset Registry** plugin. Restart the editor.
- The server auto-starts inside the running editor at
  **`http://127.0.0.1:8000/mcp`** (localhost only, no auth — that's expected).
- Connect Claude Code (run with the editor open):
  ```powershell
  claude mcp add --transport http --scope user unreal http://127.0.0.1:8000/mcp
  claude mcp list      # expect: unreal ... ✓ Connected
  ```
- In a `claude` session: "Use the unreal server to list the actors in my level."
  Tools include spawn actors, lighting, materials, UI inspection, automation.
- **The editor must be open** for the MCP server to be reachable.

## Current status

**Environment is set up; finishing the MCP switch.**

- [x] UE 5.8, Visual Studio 2022, Python, uv installed
- [x] TRGWorld project created (Third Person, Blueprint → converted to C++)
- [x] Repo scaffolded: `.gitignore`, README, `docs/`, `scripts/`
- [x] Game Design Doc drafted; mobile-first + simulated-economy decisions locked
- [~] **Switching to the official Epic Unreal MCP plugin + Claude Code** (in progress)
- [ ] Confirm MCP end-to-end (list actors / spawn a cube)
- [ ] Set project to Mobile/Scalable + add touch controls
- [ ] Build the **vertical slice**: 1 cave, mineable crystal, 1 monster, a boss,
      an exit (see GAME_DESIGN.md §8)

## Repo vs. project location (needs reconciling)

Right now the **git repo** and the **actual Unreal project** are in two
different folders. To get the game under version control, consolidate them —
recommended approach when starting in VS Code:

1. Clone this repo, OR point git at the UE project folder.
2. Make the folder containing `TRGWorld.uproject` the repo root (move the
   `.gitignore`, `README.md`, `docs/`, `scripts/`, `CLAUDE.md` in, or move the
   project files into the clone).
3. Commit the project (the `.gitignore` already excludes Binaries/Intermediate/
   Saved/DerivedDataCache so only real source/content is tracked).

## History / gotchas already solved

- `.uproject` opened in Visual Studio instead of Unreal → open via the **Epic
  Games Launcher** (no UnrealVersionSelector on 5.8).
- **Python 3.14 too new** for some tooling → pin **3.13** with `uv python pin 3.13`.
- Blueprint-only projects can't compile C++ plugins → added an empty **C++
  class** to convert TRGWorld to a C++ project.
- The old community plugin didn't build on 5.8 (`ANY_PACKAGE` removed,
  `BufferSize` C4459) → patched via `scripts/patch-mcp-ue58.ps1`. This is why we
  moved to Epic's official plugin, which needs no patching.

## How to build the project from source (if needed)

```powershell
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" `
  TRGWorldEditor Win64 Development `
  "-project=C:\Users\nacoleon\Documents\Unreal Projects\TRG-World\TRGWorld\TRGWorld.uproject" -waitmutex
```
