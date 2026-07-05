<#
    patch-mcp-ue58.ps1 — patch chongdashu/unreal-mcp's UnrealMCP plugin so it
    compiles on Unreal Engine 5.8 (it was written for 5.5/5.6).

    Fixes:
      1. ANY_PACKAGE was removed in UE5 -> use FindFirstObject<T>(...).
      2. C4459 'BufferSize hides global declaration' (warning-as-error) ->
         rename the plugin's file-scope BufferSize to MCPBufferSize.

    USAGE:
      .\patch-mcp-ue58.ps1
      .\patch-mcp-ue58.ps1 -PluginSource "C:\path\to\Plugins\UnrealMCP\Source"
#>

param(
    [string]$PluginSource = "C:\Users\nacoleon\Documents\Unreal Projects\TRG-World\TRGWorld\Plugins\UnrealMCP\Source"
)

if (-not (Test-Path $PluginSource)) {
    Write-Host "Plugin source not found: $PluginSource" -ForegroundColor Yellow
    Write-Host "Re-run with -PluginSource pointing at ...\Plugins\UnrealMCP\Source" -ForegroundColor Yellow
    exit 1
}

# Fix 1 — ANY_PACKAGE -> FindFirstObject (across every source file)
Get-ChildItem $PluginSource -Recurse -Include *.cpp, *.h | ForEach-Object {
    $p = $_.FullName
    $t = [System.IO.File]::ReadAllText($p)
    $orig = $t
    $t = [regex]::Replace($t, 'FindObject(<[^>]+>)\s*\(\s*ANY_PACKAGE\s*,\s*', 'FindFirstObject$1(')
    if ($t -ne $orig) {
        [System.IO.File]::WriteAllText($p, $t)
        Write-Host "[OK] Patched ANY_PACKAGE in $($_.Name)" -ForegroundColor Green
    }
}

# Fix 2 — rename file-scope BufferSize in MCPServerRunnable.cpp
$f = Join-Path $PluginSource "UnrealMCP\Private\MCPServerRunnable.cpp"
if (Test-Path $f) {
    $t = [System.IO.File]::ReadAllText($f)
    $t = [regex]::Replace($t, '\bBufferSize\b', 'MCPBufferSize')
    [System.IO.File]::WriteAllText($f, $t)
    Write-Host "[OK] Renamed BufferSize -> MCPBufferSize in MCPServerRunnable.cpp" -ForegroundColor Green
}

Write-Host "`nDone. Now rebuild the project (Build.bat TRGWorldEditor ...)." -ForegroundColor Cyan
