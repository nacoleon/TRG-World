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
- **Economy:** Crystals → TRG Runes → upgrades/cosmetics. **[TODO]** scope for v1.
- **[TODO]** Any blockchain / real TRG integration, or purely in-game for now?

## 8. First milestone — the "vertical slice"

Smallest playable thing that proves the loop, built on the **Third Person**
template:

1. A single small cave level (Region 1 prototype).
2. Crystal nodes the player can walk up to and **mine** (spawns/awards a crystal).
3. One monster type that chases and can be defeated.
4. A simple **boss** at the end.
5. An **exit** that "completes" the region when the boss is down.

Everything after that (extra regions, real art, economy, UI polish) builds on
this proven core.

## 9. Open questions for the creator

- Canonical **art style & palette** — can you share reference images/models?
- Is combat **melee, ranged, or both**?
- **First-person or third-person** camera? (Currently planning third-person.)
- Should v1 wire into the **real TRG token economy**, or simulate it in-game?
- How many **regions** for the first release?
