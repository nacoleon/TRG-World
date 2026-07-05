# Vertical Slice — Build Plan

Turns `GAME_DESIGN.md` §8 into an ordered, buildable checklist. The vertical
slice is the smallest playable thing that proves the loop:
**explore a cave → mine crystals → fight a monster → beat a boss → exit unlocks.**

## Definition of done (acceptance)

- [ ] A single small cave level loads and is traversable in third-person.
- [ ] **Touch controls** work: on-screen joystick (move) + Jump / Mine / Attack
      buttons. Keyboard/mouse still work for fast PC testing.
- [ ] Walking to a **crystal node** and mining it awards crystals (on-screen count).
- [ ] One **monster** chases the player and can be killed; it can damage/kill the player.
- [ ] A **boss** at the end takes more effort to defeat.
- [ ] Beating the boss **unlocks an exit** that "completes" the region.
- [ ] The build **packages and runs on a real iPhone/iPad** at ~30–60 FPS.

## Architecture decision — C++ systems, Blueprint tuning, UMG touch UI

Put gameplay **systems in C++**, expose tunables to Blueprint, keep the existing
`BP_ThirdPersonCharacter` for wiring. Rationale:

- **Mobile performance** — component logic in C++ is cheaper than heavy BP graphs.
- **Git-friendliness** — this repo is git + LFS, and binary `.uasset`/Blueprints
  **cannot be merged**. C++ (`.cpp/.h`) is text: diffable, mergeable, reviewable.
  Keep logic in code; keep Blueprints thin (tuning values, asset refs, UI).
- Unavoidable binary assets: the cave `.umap`, the UMG touch widget, materials.

## Step 0 — Mobile-first project setup  ⚠ do this first

The hardware target is already **Mobile / Scalable**, but the renderer is still
full desktop. Align `Config/DefaultEngine.ini` with `GAME_DESIGN.md` §1a:

| Setting | Now | Target (mobile) |
|---|---|---|
| `r.Nanite.ProjectEnabled` | `True` | `False` |
| `r.DynamicGlobalIlluminationMethod` (Lumen GI) | `1` | `0` |
| `r.ReflectionMethod` (Lumen reflections) | `1` | `0` (or `2` = SSR) |
| `r.Lumen.HardwareRayTracing` | `True` | `False` |
| `r.RayTracing` | `True` | `False` |
| `r.AllowStaticLighting` | `False` | `True` (baked lighting) |

Also: enable the **iOS** platform (Project Settings → Platforms → iOS), and use
the in-editor **Mobile preview** shading so PC previews match the device.

> Best done via in-editor Project Settings (writes the companion keys correctly
> and triggers the shader recompile) or carefully by hand in the `.ini`. This
> changes how the whole game renders, so it's a deliberate first task, not a
> silent edit. Re-light the sample level after switching to static lighting.

## Steps 1–7

Each step: **what** · **how (build method)** · **done when**.

1. **Cave level (Region 1 prototype)**
   · New `.umap`, greybox with the `LevelPrototyping` meshes already in Content;
   static lighting; one player start, one boss arena at the end.
   · *In-editor / MCP-driven.* · Done when: loads, traversable, has a clear
   start→arena path.

2. **Touch controls**
   · Enhanced Input actions `IA_Mine`, `IA_Attack` (reuse `IA_Move/Look/Jump`).
   UMG widget `WBP_TouchControls`: virtual joystick + Jump/Mine/Attack buttons,
   inside a **Safe Zone**. Feed the same input actions so PC keys still work.
   · *UMG + BP wiring.* · Done when: playable one-handed in Mobile preview.

3. **Crystal nodes** · `ACrystalNode` (C++) + `UMiningResourceComponent` on the
   player. Overlap/interact → deplete node, `AddCrystals(n)`, update HUD count.
   · *C++ + thin BP + HUD text.* · Done when: mining raises the on-screen count.

4. **Monster** · `ATRGMonster` (Character) + `UHealthComponent`; `AIController`
   with a simple chase (MoveTo player) + melee on contact. Dies at 0 HP.
   · *C++ + Behavior Tree/nav.* · Done when: it chases, hits the player, and dies.

5. **Boss** · `ATRGBoss` (extends `ATRGMonster`): more HP, bigger, one telegraphed
   attack. On death broadcasts `OnBossDefeated`.
   · *C++.* · Done when: takes sustained effort; death fires the region event.

6. **Exit / region complete** · `ARegionExit` (C++): starts locked; listens for
   `OnBossDefeated` → unlocks; player overlap → `ATRGGameMode` marks region
   complete (win screen / reload for the slice).
   · *C++ + trigger volume.* · Done when: boss death → exit → completion.

7. **iOS packaging test** · Package Development for iOS (needs a Mac + Xcode +
   Apple Developer account — see §1a), install via TestFlight, check ~30–60 FPS.
   · Done when: it runs on a real device at target framerate.

## C++ classes to create (in `Source/TRGWorld/`)

- `UHealthComponent` — HP, `ApplyDamage()`, `OnDeath` delegate. (player, monster, boss)
- `UMiningResourceComponent` — crystal/rune counters, `AddCrystals()`, `ConvertToRunes()`.
- `ACrystalNode` — mineable actor; interact → award + deplete.
- `ATRGCharacter` — C++ base for the player (mine/attack); reparent `BP_ThirdPersonCharacter` to it.
- `ATRGMonster` — chasing enemy pawn using `UHealthComponent`.
- `ATRGBoss` — tougher monster; broadcasts `OnBossDefeated`.
- `ARegionExit` — boss-gated completion trigger.
- `ATRGGameMode` — tracks boss defeat + region completion + respawn.

## What we can do now vs. what's blocked

- **Now (no editor/MCP):** Step 0 `.ini` edits; write + compile the C++ classes
  above (requires the editor **closed** so the build can write the module DLL).
- **Needs the editor open + MCP connected:** the cave `.umap`, touch UMG widget,
  placing actors, Behavior Trees, reparenting the BP, lighting builds.
- **Needs a Mac:** Step 7 iOS packaging.

## Open design questions (from §9 — answers unblock content)

- Combat: **melee, ranged, or both?** (affects `ATRGCharacter` + monster design)
- Canonical **art / palette / monster + boss identities** from the TRG IP.
- How many regions for the first release?
