"""Generate trade_data.h from villager_trade_predictor.py"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
from villager_trade_predictor import ALL_TRADE_DATA, TRADEABLE_ENCHANTMENTS, DOUBLE_PRICE_SET
from villager_trade_predictor import ENCHANTED_EQUIPMENT_PARAMS, ITEM_ENCHANTMENT_COMPAT
from villager_trade_predictor import ENCHANTMENT_WEIGHTS, ENCHANTMENT_INCOMPATIBLE
from villager_trade_predictor import ITEM_ENCHANTABILITY, ON_TRADED_EQUIPMENT_ENCHANTMENTS

lines = []
lines.append("/* Auto-generated from villager_trade_predictor.py */")
lines.append('#include "villager_trade.h"')
lines.append("")
lines.append("/* ====== Tradeable Enchantments (40) ====== */")
lines.append(f"#define NUM_TRADEABLE_ENCHANTMENTS {len(TRADEABLE_ENCHANTMENTS)}")
lines.append("static const char* TRADEABLE_ENCHANT_NAMES[] = {")
for name, max_lv in TRADEABLE_ENCHANTMENTS:
    lines.append(f'    "{name}",')
lines.append("};")
lines.append("static const int TRADEABLE_ENCHANT_MAX[] = {")
for name, max_lv in TRADEABLE_ENCHANTMENTS:
    lines.append(f"    {max_lv},")
lines.append("};")
lines.append("")

# Double price set
lines.append("static int is_treasure_enchant(const char* name) {")
for ename in DOUBLE_PRICE_SET:
    lines.append(f'    if (strcmp(name, "{ename}") == 0) return 1;')
lines.append("    return 0;")
lines.append("}")
lines.append("")

# Professions
prof_keys = ["armorer","butcher","cartographer","cleric","farmer","fisherman",
             "fletcher","leatherworker","librarian","mason","shepherd","toolsmith","weaponsmith"]

lines.append("const char* PROFESSION_NAMES[] = {")
for p in prof_keys:
    lines.append(f'    "{p}",')
lines.append("};")
lines.append("")

lines.append("/* Pool entries per profession/level */")
lines.append("typedef struct { const char* entry; } TradeEntry;")
lines.append("")

# Generate pool data per profession/level
all_pools = {}
for pi, prof in enumerate(prof_keys):
    prof_data = ALL_TRADE_DATA.get(prof, {})
    for level in range(1, 6):
        data = prof_data.get(level, {})
        pool = data.get("pool", [])
        if pool:
            var_name = f"pool_{prof}_L{level}"
            all_pools[(pi, level)] = var_name
            lines.append(f"static const char* {var_name}[] = {{")
            for entry in pool:
                lines.append(f'    "{entry}",')
            lines.append("};")
            lines.append(f"#define POOL_SIZE_{prof}_L{level} {len(pool)}")
            lines.append("")

# Level data
lines.append("typedef struct {")
lines.append("    const char** pool;")
lines.append("    int pool_size;")
lines.append("    int amount;")
lines.append("    int ench_book_indices[4];")
lines.append("    int ench_equip_indices[4];")
lines.append("} LevelData;")
lines.append("")

# Build level data arrays per profession
for pi, prof in enumerate(prof_keys):
    prof_data = ALL_TRADE_DATA.get(prof, {})
    lines.append(f"static LevelData levels_{prof}[] = {{")
    for level in range(1, 6):
        data = prof_data.get(level, {})
        pool = data.get("pool", [])
        if not pool:
            lines.append("    {NULL, 0, 0, {-1,-1,-1,-1}, {-1,-1,-1,-1}},")
            continue
        var = all_pools[(pi, level)]
        amount = data.get("amount", 2)
        eb_idx = data.get("enchanted_book_indices", [-1,-1,-1,-1])
        eq_idx = data.get("enchanted_equipment_indices", [-1,-1,-1,-1])
        lines.append(f"    {{{var}, POOL_SIZE_{prof}_L{level}, {amount}, {{{eb_idx[0]},{eb_idx[1] if len(eb_idx)>1 else -1},{eb_idx[2] if len(eb_idx)>2 else -1},{eb_idx[3] if len(eb_idx)>3 else -1}}}, {{{eq_idx[0]},{eq_idx[1] if len(eq_idx)>1 else -1},{eq_idx[2] if len(eq_idx)>2 else -1},{eq_idx[3] if len(eq_idx)>3 else -1}}}}},")
    lines.append("};")
    lines.append("")

lines.append("LevelData* ALL_LEVEL_DATA[13] = {")
for pi, prof in enumerate(prof_keys):
    lines.append(f"    levels_{prof},")
lines.append("};")
lines.append("")

# Enchanted equipment parameters
lines.append("/* Enchanted equipment parameters: {item, level_min, level_max} */")
lines.append("typedef struct { const char* entry; const char* item; int level_min; int level_max; } EquipParam;")
lines.append(f"static EquipParam EQUIP_PARAMS[] = {{")
for entry, params in ENCHANTED_EQUIPMENT_PARAMS.items():
    lines.append(f'    {{"{entry}", "{params[0]}", {params[1]}, {params[2]}}},')
lines.append("    {NULL, NULL, 0, 0}")
lines.append("};")
lines.append("")

# Item enchantability
lines.append("static int get_item_enchantability(const char* item) {")
for item, value in ITEM_ENCHANTABILITY.items():
    lines.append(f'    if (strcmp(item, "{item}") == 0) return {value};')
lines.append("    return 10;")
lines.append("}")
lines.append("")

# Enchantment weights
lines.append("static int get_enchant_weight(const char* name) {")
for name, weight in ENCHANTMENT_WEIGHTS.items():
    lines.append(f'    if (strcmp(name, "{name}") == 0) return {weight};')
lines.append("    return 1;")
lines.append("}")
lines.append("")

# Equipment enchantments (max levels)
lines.append("static int get_equip_ench_max(const char* name) {")
for name, max_lv in ON_TRADED_EQUIPMENT_ENCHANTMENTS:
    lines.append(f'    if (strcmp(name, "{name}") == 0) return {max_lv};')
lines.append("    return 1;")
lines.append("}")
lines.append("")

# Item enchantment compatibility
lines.append("static int is_ench_compatible_with_item(const char* ench, const char* item) {")
for item, enchs in ITEM_ENCHANTMENT_COMPAT.items():
    lines.append(f'    if (strcmp(item, "{item}") == 0) {{')
    for ench in enchs:
        lines.append(f'        if (strcmp(ench, "{ench}") == 0) return 1;')
    lines.append("        return 0;")
    lines.append("    }")
lines.append("    return 0;")
lines.append("}")
lines.append("")

# Incompatibility
lines.append("static int are_enchants_incompatible(const char* a, const char* b) {")
for group in ENCHANTMENT_INCOMPATIBLE:
    for i, e1 in enumerate(group):
        for e2 in group[i+1:]:
            lines.append(f'    if ((strcmp(a, "{e1}") == 0 && strcmp(b, "{e2}") == 0) ||')
            lines.append(f'        (strcmp(a, "{e2}") == 0 && strcmp(b, "{e1}") == 0)) return 1;')
lines.append("    return 0;")
lines.append("}")
lines.append("")

# Stew effects
lines.append("static const char* STEW_EFFECTS[] = {")
effects = ["night_vision","jump_boost","weakness","blindness","poison","saturation"]
for e in effects:
    lines.append(f'    "{e}",')
lines.append("};")
lines.append("static const int STEW_DURATIONS[] = {200, 200, 180, 180, 200, 6};")
lines.append("#define NUM_STEW_EFFECTS 6")
lines.append("")

# Tradeable potions
from villager_trade_predictor import TRADEABLE_POTIONS
lines.append(f"static const char* TRADEABLE_POTION_LIST[] = {{")
for p in TRADEABLE_POTIONS:
    lines.append(f'    "{p}",')
lines.append("};")
lines.append(f"#define NUM_TRADEABLE_POTIONS {len(TRADEABLE_POTIONS)}")
lines.append("")

out_path = os.path.join(os.path.dirname(__file__), "trade_data.h")
with open(out_path, "w", encoding="utf-8") as f:
    f.write("\n".join(lines))
print(f"Generated {out_path} ({len(lines)} lines)")
