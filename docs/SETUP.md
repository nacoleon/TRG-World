# Development Environment Setup (Windows)

A step-by-step guide to get everything ready to build **TRG-World** with
Unreal Engine 5 and AI assistance via the Unreal MCP.

> **How the pieces fit together.** The AI drives the Unreal Editor through a
> local bridge:
>
> ```
> Claude Desktop  ──►  Unreal MCP server (Python)  ──►  Unreal plugin (socket)  ──►  Unreal Editor
> ```
>
> All of these run on **your own machine**. A cloud/web AI session cannot reach
> your local editor — so the MCP-driven part happens locally.

---

## Step 1 — Epic Games Launcher  ✅

1. Download from <https://www.unrealengine.com/en-US/download>.
2. Create a free Epic Games account and sign in.

## Step 2 — Install Unreal Engine 5

1. In the Epic Games Launcher, open the **Unreal Engine** tab (left side).
2. Go to the **Library** sub-tab → click the **+** next to ENGINE VERSIONS.
3. Pick the **latest stable 5.x** release and click **Install**.
   - Default install location is fine.
   - Under **Options**, you can uncheck target platforms you don't need
     (e.g. Android, iOS) to save disk space. Keep **Starter Content** and
     **Editor symbols** unchecked unless you want them.
4. Wait for the download (large — tens of GB). ☕

## Step 3 — Install Visual Studio 2022

Required for C++ and for compiling MCP/editor plugins.

1. Download **Visual Studio 2022 Community** (free):
   <https://visualstudio.microsoft.com/vs/community/>
2. In the installer, select these **Workloads**:
   - ✅ **Game development with C++** (installs the Unreal Engine integration)
   - ✅ **Desktop development with C++**
3. In the **Individual components** tab, confirm these are checked (usually pulled
   in automatically):
   - MSVC v143 build tools
   - Windows 10/11 SDK (latest)
   - .NET desktop development / .NET SDK (Unreal tooling uses it)
4. Install, then reboot if prompted.

## Step 4 — Create your first project

1. Launch Unreal Engine from the Epic Launcher.
2. In the Project Browser choose **Games** → a template
   (**Third Person** is a great, well-documented starting point).
3. Settings:
   - **C++** or **Blueprint**: start with **Blueprint** if you're brand new;
     choose **C++** if you want to write code (you can add C++ later either way).
   - **Starter Content**: On (gives you sample assets to play with).
   - **Project name**: use `TRGWorld` (no spaces) and save it **inside this
     repository folder** so git tracks it.
4. Click **Create**.

## Step 5 — Enable Python in the Editor

Most Unreal MCP servers control the editor through Python.

1. In the editor: **Edit → Plugins**.
2. Search for and enable:
   - ✅ **Python Editor Script Plugin**
   - ✅ **Editor Scripting Utilities**
3. Restart the editor when prompted.

## Step 6 — Install the Unreal MCP

**Chosen project: [`chongdashu/unreal-mcp`](https://github.com/chongdashu/unreal-mcp)**
— free, fully local, uses a C++ plugin built with Visual Studio.

> Requirements: **Unreal Engine 5.5+**, **Python 3.12+**, Visual Studio 2022
> with *Game development with C++*. Always cross-check the project's own README,
> since steps can change.

### 6a. Install Python 3.12+ and `uv`

1. Install **Python 3.12+** from <https://www.python.org/downloads/> —
   during install, tick **"Add python.exe to PATH"**.
2. Install **uv** (fast Python package manager):
   ```powershell
   pip install uv
   ```

### 6b. Get the MCP project

- Download the repo as a ZIP from
  <https://github.com/chongdashu/unreal-mcp> (green **Code** button →
  **Download ZIP**) and unzip it somewhere memorable, e.g.
  `C:\Dev\unreal-mcp\`. *(Or `git clone` it if you have Git.)*

### 6c. Add the UnrealMCP plugin to your project

1. Copy the folder `unreal-mcp\MCPGameProject\Plugins\UnrealMCP` into your
   project's `TRGWorld\Plugins\` folder (create `Plugins` if it doesn't exist).
2. **Close the Unreal Editor.**

### 6d. Build the plugin (turns the project into a C++ project)

1. In `TRGWorld\`, **right-click `TRGWorld.uproject` → Generate Visual Studio
   project files**. (If you don't see that option, see Troubleshooting.)
2. Double-click the generated **`TRGWorld.sln`** to open Visual Studio 2022.
3. Set the config dropdown to **Development Editor** / **Win64**.
4. **Build → Build Solution** (or press **F7**). Wait for "Build succeeded".

### 6e. Enable the plugin

1. Reopen the project (double-click `TRGWorld.uproject`).
2. **Edit → Plugins**, search **UnrealMCP**, tick ✅ **enable**, restart.

### 6f. Set up the Python MCP server

1. Open a terminal in the project's **`Python`** folder
   (`unreal-mcp\Python\`).
2. Install deps (see that folder's `README.md`), typically:
   ```powershell
   uv sync
   ```
3. This is the server Claude Desktop will launch (next step).

## Step 7 — Install & configure Claude Desktop

1. Install **Claude Desktop** from <https://claude.ai/download>.
2. Open **Settings → Developer → Edit Config** (this opens
   `claude_desktop_config.json`).
3. Add the MCP server entry (point `--directory` at your unzipped
   `unreal-mcp\Python` folder, using **double backslashes**):

   ```json
   {
     "mcpServers": {
       "unrealMCP": {
         "command": "uv",
         "args": ["--directory", "C:\\Dev\\unreal-mcp\\Python", "run", "unreal_mcp_server.py"]
       }
     }
   }
   ```

   *(Adjust the path to wherever you unzipped it.)*
4. Fully quit and reopen Claude Desktop. The `unreal` tools should now appear.

## Step 8 — Test the connection

1. Open your project in the Unreal Editor (plugin enabled, MCP server running).
2. In Claude Desktop, ask it to **spawn a cube in the level** (or list actors).
3. If a cube appears in your viewport — 🎉 the whole chain works.

---

## Troubleshooting

- **Tools don't show in Claude Desktop** → fully quit (system tray too) and
  relaunch; re-check the JSON for typos / wrong paths (use double backslashes
  on Windows).
- **MCP server can't connect to Unreal** → make sure the editor is open, the
  plugin is enabled, and no firewall is blocking the local port.
- **C++ build errors on open** → confirm Visual Studio 2022 with the
  *Game development with C++* workload is installed, then right-click the
  `.uproject` → **Generate Visual Studio project files**.
