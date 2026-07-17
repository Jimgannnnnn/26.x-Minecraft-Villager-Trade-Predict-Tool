# Villager Trade Predictor

A seed-based villager trade prediction tool for Minecraft 26.1+.

## Features

### Trade Prediction

- Predict all trades for any villager profession and level given a world seed
- Supports all 13 villager professions (armorer, butcher, cartographer, cleric, farmer, fisherman, fletcher, leatherworker, librarian, mason, shepherd, toolsmith, weaponsmith)
- Simulates the full seed derivation chain: world seed → Xoroshiro128++ PRNG with Guava's big-endian MD5 hash
- Stream-based RNG progression matching in-game trade generation order

### Trade Types

- **Enchanted Books**: Random enchantment from the full 40-enchantment tradeable pool, with accurate level calculation and treasure enchantment double-cost pricing
- **Enchanted Equipment**: Enchantment selection weighted by item enchantability, with up to 4 enchantments per item and proper incompatibility filtering
- **Suspicious Stew**: Random effect with correct duration
- **Tipped Arrows**: Random potion from tradeable pool
- **Dyed Equipment**: Random dye combinations with binomial distribution
- **Standard Trades**: All non-special trades including cartographer biome-specific maps and fisherman boat variants

### GUI (Python)

- Preview trades in a sortable table with CSV export
- **Node Positioning**: Backtrack offset by observing known trades — enter observed trades and the tool finds all matching offsets
- **Rule-based Filtering**: Combine multiple filter rules with AND/OR/NOT logic
  - Filter by trade type, enchantment, level, and price range
  - Enchantment filter uses a checkbox popup with the full 40-enchantment list (not limited to preview data)
  - Price filter supports percentage-based thresholds
- **Enchantment Conflict Detection**: Incompatible enchantments (e.g., Fortune + Silk Touch, Protection variants, Riptide + Channeling/Loyalty) are mutually exclusive in the selector

## Supported Versions

| Version | Status    |
|---------|-----------|
| 26.x    | Supported |

> Note: This tool predicts trades for the default (non-rebalanced) villager trade tables. Master-level librarians in this version sell candles and do not offer enchanted books at level 5.

## Requirements

- Python 3.10+
- tkinter (included with standard Python distributions)

## Installation

### Pre-built Executables

Standalone executables are available in each version's `dist/` directory after building:

- `versions/py/src/dist/村民交易预测工具.exe`
- `versions/c/dist/村民交易预测工具.exe`

### Build from Source

**Python:**

```bash
cd versions/py
build_exe.bat
```

## Project Structure

```
versions/
└── py/
    ├── build_exe.bat
    └── src/
        ├── trade_export_gui.py        # GUI application
        ├── villager_trade_predictor.py # Core prediction engine
        └── trade_export_data.py       # Trade data definitions
```

## License

[MIT](LICENSE)
