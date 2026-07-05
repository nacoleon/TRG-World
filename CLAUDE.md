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
- **This git repo** (`nacoleon/trg-world`): the project folder above **is** the
  repo root (consolidated 2026-07-04; Git LFS enabled for binary assets).
- Removed community MCP plugin (parked, reversible):
  `C:\Users\nacoleon\Documents\Unreal Projects\TRG-World\_removed-plugins\UnrealMCP\`

## MCP setup (official Epic plugin)

- Already enabled in `TRGWorld.uproject` (`ModelContextProtocol`); it pulls in
  the **Toolset Registry** + **Engine Asset Definitions** plugins. To toggle by
  hand instead: **Edit → Plugins → "Unreal MCP" (Experimental, Epic Games)**,
  then restart the editor.
- Auto-start is enabled (`Config/DefaultEditorPerProjectUserSettings.ini` →
  `bAutoStartServer=True`), so the server comes up inside the running editor at
  **`http://127.0.0.1:8000/mcp`** (localhost only, no auth — that's expected).
- Claude Code is wired via the committed project-scoped **`.mcp.json`** at the
  repo root (server name `unreal-mcp`). Reload Claude Code with the editor open,
  and approve the server on first use. Alternative user-scope registration:
  ```powershell
  claude mcp add --transport http --scope user unreal http://127.0.0.1:8000/mcp
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
- [x] **Switched to the official Epic Unreal MCP plugin** — community plugin
      removed, `ModelContextProtocol` enabled, `.mcp.json` + auto-start configured
- [x] Repo consolidated: the project folder is now the repo root, Git LFS enabled
- [ ] Confirm MCP end-to-end (list actors / spawn a cube) — needs editor restart + Claude Code reload
- [ ] Set project to Mobile/Scalable + add touch controls
- [ ] Build the **vertical slice**: 1 cave, mineable crystal, 1 monster, a boss,
      an exit (see GAME_DESIGN.md §8)

## Repo vs. project location (RESOLVED 2026-07-04)

Done. The folder containing `TRGWorld.uproject` **is** the git repo root now.
The docs/scripts were merged into it (unrelated-histories merge) and the game
(source + content) committed on top. **Git LFS** was added (`.gitattributes`) so
`.uasset`/`.umap` and source art are stored out-of-band; the `.gitignore` keeps
Binaries/Intermediate/Saved/DerivedDataCache out.

Note: if this becomes a team where several people edit content simultaneously,
the professional move is to migrate to **Perforce** (exclusive checkout / file
locking) — git cannot merge binary `.uasset`/`.umap` files.

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
