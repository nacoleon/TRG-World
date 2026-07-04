# TRG-World — Game Design Document (Draft)

> Working design doc for the 3D Unreal Engine 5 game based on
> **The Rune Guardians** IP (<https://theruneguardians.com>). This is a living
> draft — sections marked **[TODO]** need the creator's canonical details.

## 1. High-concept

A 3D cave-crawler set in the Rune Guardians universe. Players control a
**Rune Guardian miner** who explores caves across multiple regions: mining
crystals, battling cave monsters, and defeating a region **boss** to unlock
the exit and progress to the next region.

**One-liner:** *Mine crystals, fight through the caves, beat the boss, escape —
one region at a time.*

## 1a. Target platforms — MOBILE-FIRST (iOS/iPadOS)

**Primary target: iPhone and iPad.** This is a core constraint, not an
afterthought — it shapes controls, art, and performance from day one.

- **Controls:** touch only — on-screen virtual joystick (move) + buttons
  (jump / mine / attack). No keyboard or mouse on the device. We add an
  on-screen touch UI and keep desktop keys only for fast PC testing.
- **Rendering:** use UE5's **Mobile renderer**. Avoid the heavy desktop
  features that tank mobile framerate: **Nanite off, Lumen off, hardware
  ray tracing off**. Prefer **baked/static lighting**, low draw calls, and
  modest poly/texture budgets.
- **Project settings (set early):** target hardware = **Mobile / Scalable**;
  enable iOS as a platform; test with the **Mobile preview** rendering level
  in-editor so PC previews match phone/tablet reality.
- **UI:** design for a range of screen sizes and aspect ratios; respect
  **safe areas** (notch / Dynamic Island / home indicator).
- **Performance budget:** aim for a smooth **30–60 FPS** on a mid-range iPhone.
  Test on real hardware regularly — the editor lies about mobile perf.

### Shipping to iOS (the hard requirements)

- A **Mac** is required to compile and package iOS builds (Xcode).
- An **Apple Developer Program** membership (~$99/yr) to install on devices
  and publish to **TestFlight** / the **App Store**.
- Workflow: prototype on PC with the MCP → periodically package for iOS →
  test on a real iPhone/iPad via TestFlight.

## 2. Source IP (from public info — confirm & expand)

- **The Rune Guardians (TRG):** 10k PFP NFT collection on Bitcoin / Runes.
- **Miners / "Hashlings":** collect **Crystals** by mining.
- **Crystals → TRG Runes:** crystals periodically convert into TRG Runes,
  the primary in-game currency.
- **Lore:** protectors of mystical runes; Guardian Masters of the Ordinal
  Universe.
- **[TODO]** Canonical character roster, faction/region names, art bible,
  color palette, monster designs, boss identities.

## 3. Core gameplay loop

```
Enter region cave  →  Explore  →  Mine crystals  →  Battle monsters
        ↑                                                   │
        └──────  Next region  ←  Exit unlocks  ←  Defeat region boss
```

1. **Explore** a cave (third-person traversal, light platforming).
2. **Mine** crystal nodes for resources (→ TRG Runes / upgrades).
3. **Battle** cave monsters (melee and/or ranged).
4. **Boss fight** at the end of the region.
5. **Exit unlocks** on boss defeat → travel to the next region.

## 4. Pillars

- **Mining is core, not filler** — crystals fuel progression and tie to the
  TRG economy.
- **Risk vs. reward** — deeper caves = better crystals + tougher monsters.
- **Region variety** — each region has a distinct look, monster set, and boss.
- **Faithful to the IP** — characters, tone, and currency match Rune Guardians.

## 5. Regions (each = a level/world)

| Region | Theme | Monsters | Boss | Status |
|--------|-------|----------|------|--------|
| Region 1 | **[TODO]** (starting caves) | [TODO] | [TODO] | Prototype target |
| Region 2 | [TODO] | [TODO] | [TODO] | Planned |
| Region 3+ | [TODO] | [TODO] | [TODO] | Planned |

## 6. Player character — the miner

- **[TODO]** Model / look (pull from Rune Guardians art).
- Abilities: move, jump, **mine** (interact with crystal nodes), **attack**.
- Stats: health, and possibly stamina/energy for mining.

## 7. Systems

- **Mining:** interact with crystal nodes → collect crystals → convert to Runes.
- **Combat:** monster AI, player attacks, damage/health, death & respawn.
- **Progression:** boss gate per region; unlock next region on victory.
- **Economy:** Crystals → TRG Runes → upgrades/cosmetics.
  **v1 decision: fully simulated in-game** — no blockchain / real TRG token
  integration yet. Crystals and Runes are just in-game counters for now; real
  TRG economy integration is a possible later phase.

## 8. First milestone — the "vertical slice"

Smallest playable thing that proves the loop, built on the **Third Person**
template:

1. A single small cave level (Region 1 prototype).
2. **Touch controls** — on-screen joystick + jump/mine/attack buttons, so it's
   playable on a phone/tablet from the start (keyboard kept only for PC testing).
3. Crystal nodes the player can walk up to and **mine** (spawns/awards a crystal).
4. One monster type that chases and can be defeated.
5. A simple **boss** at the end.
6. An **exit** that "completes" the region when the boss is down.
7. Verify it **packages and runs on a real iPhone/iPad** at an acceptable framerate.

Everything after that (extra regions, real art, economy, UI polish) builds on
this proven core.

## 9. Open questions for the creator

- Canonical **art style & palette** — can you share reference images/models?
- Is combat **melee, ranged, or both**?
- **First-person or third-person** camera? (Currently planning third-person.)
- How many **regions** for the first release?

**Resolved:** Economy is **simulated in-game** for v1 (no blockchain yet).
