<#
    setup-mcp.ps1 — one-shot helper to install the Unreal MCP into TRGWorld.

    What it does (all safe, nothing destructive):
      1. Downloads the chongdashu/unreal-mcp project.
      2. Copies its UnrealMCP plugin into your project's Plugins folder.
      3. Sets up the Python MCP server dependencies with uv.
      4. Prints the exact Claude Desktop config for you to paste.

    USAGE (in PowerShell):
      # If your project is in the default Unreal Projects location, just run:
      .\setup-mcp.ps1

      # Or point it at your project folder explicitly:
      .\setup-mcp.ps1 -ProjectPath "C:\path\to\TRGWorld"

    After it finishes, you still do two manual steps it can't automate:
      - Build the plugin in Visual Studio (Generate VS project files -> build).
      - Paste the printed config into Claude Desktop.
#>

param(
    [string]$ProjectPath = "",
    [string]$WorkDir = "$env:USERPROFILE\Dev"
)

$ErrorActionPreference = "Stop"
function Info($m) { Write-Host "==> $m" -ForegroundColor Cyan }
function Ok($m)   { Write-Host "[OK] $m"  -ForegroundColor Green }
function Warn($m) { Write-Host "[!!] $m"  -ForegroundColor Yellow }

# --- 1. Locate the TRGWorld project ------------------------------------------
if (-not $ProjectPath) {
    Info "No -ProjectPath given; searching common locations for TRGWorld.uproject..."
    $candidates = @(
        "$env:USERPROFILE\Documents\Unreal Projects\TRGWorld",
        "$env:USERPROFILE\Documents\Unreal Projects\TRGWorld\TRGWorld",
        "$PSScriptRoot\..\TRGWorld"
    )
    $found = Get-ChildItem -Path @("$env:USERPROFILE\Documents\Unreal Projects", "$PSScriptRoot\..") `
        -Recurse -Filter "TRGWorld.uproject" -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($found) { $ProjectPath = $found.Directory.FullName }
    elseif ($c = $candidates | Where-Object { Test-Path (Join-Path $_ "TRGWorld.uproject") } | Select-Object -First 1) {
        $ProjectPath = $c
    }
}

if (-not $ProjectPath -or -not (Test-Path (Join-Path $ProjectPath "TRGWorld.uproject"))) {
    Warn "Could not find TRGWorld.uproject."
    Warn "Re-run with the folder that contains it, e.g.:"
    Warn "   .\setup-mcp.ps1 -ProjectPath `"C:\Users\you\Documents\Unreal Projects\TRGWorld`""
    exit 1
}
Ok "Found project: $ProjectPath"

# --- 2. Download the MCP project ---------------------------------------------
New-Item -ItemType Directory -Force -Path $WorkDir | Out-Null
$zip     = Join-Path $WorkDir "unreal-mcp.zip"
$extract = Join-Path $WorkDir "unreal-mcp-main"
$url     = "https://github.com/chongdashu/unreal-mcp/archive/refs/heads/main.zip"

Info "Downloading Unreal MCP from $url ..."
Invoke-WebRequest -Uri $url -OutFile $zip
if (Test-Path $extract) { Remove-Item $extract -Recurse -Force }
Info "Extracting..."
Expand-Archive -Path $zip -DestinationPath $WorkDir -Force
Ok "Extracted to $extract"

# --- 3. Copy the UnrealMCP plugin into the project ---------------------------
$pluginSrc = Join-Path $extract "MCPGameProject\Plugins\UnrealMCP"
if (-not (Test-Path $pluginSrc)) {
    Warn "Plugin folder not found at expected path: $pluginSrc"
    Warn "The repo layout may have changed — open $extract and look for a 'UnrealMCP' plugin folder."
    exit 1
}
$pluginDst = Join-Path $ProjectPath "Plugins\UnrealMCP"
New-Item -ItemType Directory -Force -Path (Join-Path $ProjectPath "Plugins") | Out-Null
if (Test-Path $pluginDst) { Remove-Item $pluginDst -Recurse -Force }
Copy-Item $pluginSrc $pluginDst -Recurse -Force
Ok "Copied UnrealMCP plugin -> $pluginDst"

# --- 4. Set up the Python MCP server -----------------------------------------
$pyDir = Join-Path $extract "Python"
if (Test-Path $pyDir) {
    Info "Installing Python server dependencies with uv (this may take a minute)..."
    Push-Location $pyDir
    try { uv sync; Ok "Python server ready in $pyDir" }
    catch { Warn "uv sync failed: $_. You can retry manually in $pyDir." }
    Pop-Location
} else {
    Warn "Python folder not found at $pyDir — check the repo layout."
}

# --- 5. Print the Claude Desktop config --------------------------------------
$pyDirEscaped = $pyDir -replace '\\', '\\'
Write-Host ""
Ok "ALMOST DONE. Two manual steps remain:"
Write-Host ""
Write-Host "  1) Build the plugin:" -ForegroundColor White
Write-Host "     - Right-click '$ProjectPath\TRGWorld.uproject' -> Generate Visual Studio project files"
Write-Host "     - Open TRGWorld.sln, set 'Development Editor', Build -> Build Solution (F7)"
Write-Host "     - Reopen the project, Edit > Plugins, enable 'UnrealMCP', restart."
Write-Host ""
Write-Host "  2) Add this to Claude Desktop (Settings > Developer > Edit Config):" -ForegroundColor White
Write-Host ""
Write-Host "{"
Write-Host "  `"mcpServers`": {"
Write-Host "    `"unrealMCP`": {"
Write-Host "      `"command`": `"uv`","
Write-Host "      `"args`": [`"--directory`", `"$pyDirEscaped`", `"run`", `"unreal_mcp_server.py`"]"
Write-Host "    }"
Write-Host "  }"
Write-Host "}"
Write-Host ""
Ok "When both are done, restart Claude Desktop and ask it to spawn a cube!"
