#include "villager_trade.h"
#include "trade_data.h"
#include "xoroshiro128pp.h"
#include "md5.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== Seed Derivation ====== */
#define SILVER_RATIO_64 0x6A09E667F3BCC909ULL
#define GOLDEN_RATIO_64 0x9E3779B97F4A7C15ULL
#define STAFFORD_MUL1  0xBF58476D1CE4E5B9ULL
#define STAFFORD_MUL2  0x94D049BB133111EBULL

static uint64_t mix_stafford13(uint64_t x) {
    x = (x ^ (x >> 30)) * STAFFORD_MUL1;
    x = (x ^ (x >> 27)) * STAFFORD_MUL2;
    x = x ^ (x >> 31);
    return x;
}

static void upgrade_seed_to_128bit_unmixed(int64_t seed, Seed128* out) {
    uint64_t lo = (uint64_t)seed ^ SILVER_RATIO_64;
    out->lo = lo;
    out->hi = lo + GOLDEN_RATIO_64;
}

static Seed128 create_random_sequence_seed(
    int64_t world_seed, const char* identifier
) {
    int64_t effective = world_seed;
    Seed128 seed128;
    upgrade_seed_to_128bit_unmixed(effective, &seed128);

    /* XOR with hash of identifier (Guava-style big-endian MD5) */
    Seed128 hash = seed_from_hash(identifier);
    seed128.lo ^= hash.lo;
    seed128.hi ^= hash.hi;

    /* Stafford mix both halves */
    seed128.lo = mix_stafford13(seed128.lo);
    seed128.hi = mix_stafford13(seed128.hi);
    return seed128;
}

/* ====== Entry Detection ====== */
static int is_enchanted_book_entry(const char* entry) {
    return strstr(entry, "enchanted_book") != NULL;
}

static int is_enchanted_equipment_entry(const char* entry) {
    return strstr(entry, "enchanted_iron_") != NULL ||
           strstr(entry, "enchanted_diamond_") != NULL ||
           strstr(entry, "enchanted_fishing_rod") != NULL ||
           strstr(entry, "enchanted_bow") != NULL ||
           strstr(entry, "enchanted_crossbow") != NULL;
}

static int is_suspicious_stew_entry(const char* entry) {
    return strstr(entry, "suspicious_stew") != NULL;
}

static int is_tipped_arrow_entry(const char* entry) {
    return strstr(entry, "tipped_arrow") != NULL;
}

static int is_dyed_equipment_entry(const char* entry) {
    return strstr(entry, "dyed_leather") != NULL ||
           strstr(entry, "dyed_horse") != NULL;
}

/* ====== Equip param lookup ====== */
extern EquipParam EQUIP_PARAMS[];
#define NUM_EQUIP_PARAMS 17

static void get_equip_params(const char* entry, const char** item, int* level_min, int* level_max) {
    for (int i = 0; EQUIP_PARAMS[i].entry; i++) {
        if (strcmp(EQUIP_PARAMS[i].entry, entry) == 0) {
            *item = EQUIP_PARAMS[i].item;
            *level_min = EQUIP_PARAMS[i].level_min;
            *level_max = EQUIP_PARAMS[i].level_max;
            return;
        }
    }
    *item = "minecraft:iron_sword";
    *level_min = 5;
    *level_max = 19;
}

/* ====== Trade Simulation ====== */

static void simulate_enchanted_book(Xoroshiro128PlusPlus* rng, Trade* t) {
    int idx = xoroshiro_next_int(rng, 40);
    
    const char* ench_name = TRADEABLE_ENCHANT_NAMES[idx];
    int min_lv = 1;
    int max_lv = TRADEABLE_ENCHANT_MAX[idx];
    int level;
    if (max_lv > min_lv) {
        level = min_lv + xoroshiro_next_int(rng, max_lv - min_lv + 1);
    } else {
        level = min_lv;
    }

    int cost = 2 + xoroshiro_next_int(rng, 5 + level * 10) + 3 * level;
    int treasure = is_treasure_enchant(ench_name);
    if (treasure) cost *= 2;
    if (cost < 1) cost = 1;
    if (cost > 64) cost = 64;

    t->type = TRADE_TYPE_ENCHANT_BOOK;
    t->enchantment = ench_name;
    t->ench_level = level;
    t->is_treasure = treasure;
    t->final_cost = cost;
}

static void simulate_enchanted_equipment(Xoroshiro128PlusPlus* rng, Trade* t, const char* entry) {
    const char* item; int lm, lx;
    get_equip_params(entry, &item, &lm, &lx);

    int level = lm + xoroshiro_next_int(rng, lx - lm + 1);
    int ench = get_item_enchantability(item);
    int modified_level = level + 1 + xoroshiro_next_int(rng, ench / 4 + 1)
                         + xoroshiro_next_int(rng, ench / 4 + 1);
    double f = (double)(xoroshiro_next_long(rng) & 0x7FFFFFFFFFFFFFFFLL)
               / 9.223372036854776E18;
    modified_level = (int)((double)modified_level * (f + f + 1.0) * 0.85 + 0.5);
    if (modified_level < 1) modified_level = 1;

    /* Build weighted list of available enchantments for this item */
    const char* available[40];
    int weights[40];
    int total_w = 0, navail = 0;

    for (int i = 0; i < 40; i++) {
        const char* ename = TRADEABLE_ENCHANT_NAMES[i];
        int emax = get_equip_ench_max(ename);
        if (emax <= 0) continue;
        if (!is_ench_compatible_with_item(ename, item)) continue;
        int w = get_enchant_weight(ename);
        int can_apply = 0;
        for (int lv = emax; lv >= 1; lv--) {
            int range_low = (lv - 1) * 10 + 1;
            int range_high = lv * 10;
            if (modified_level >= range_low) {
                int needed = range_low > range_high ? range_low : range_high;
                int delta = needed - modified_level;
                if (delta <= emax * 5) { can_apply = 1; break; }
            }
        }
        if (!can_apply) continue;
        available[navail] = ename;
        weights[navail] = w;
        total_w += w;
        navail++;
    }

    t->type = TRADE_TYPE_ENCHANT_EQUIP;
    t->item = item;
    t->num_enchants = 0;
    t->final_cost = 0;

    if (navail == 0) return;

    /* Pick first enchantment */
    int roll = xoroshiro_next_int(rng, total_w);
    int chosen = -1, acc = 0;
    for (int i = 0; i < navail; i++) {
        acc += weights[i];
        if (roll < acc) { chosen = i; break; }
    }
    if (chosen < 0) chosen = navail - 1;

    const char* first = available[chosen];
    int first_max = get_equip_ench_max(first);
    int first_lv = first_max;
    for (int lv = first_max; lv >= 1; lv--) {
        if (modified_level >= (lv - 1) * 10 + 1) { first_lv = lv; break; }
    }

    t->enchantments[t->num_enchants] = first;
    t->enchant_levels[t->num_enchants] = first_lv;
    t->num_enchants++;

    /* Additional enchantments */
    while (xoroshiro_next_int(rng, 50) <= modified_level && t->num_enchants < 4) {
        modified_level /= 2;
        /* Rebuild weighted list filtering incompatible */
        total_w = 0;
        int ai2 = 0;
        const char* avail2[40];
        int w2[40];
        for (int i = 0; i < navail; i++) {
            const char* en = available[i];
            int emax2 = get_equip_ench_max(en);
            int compat = 1;
            for (int j = 0; j < t->num_enchants; j++) {
                if (are_enchants_incompatible(en, t->enchantments[j])) { compat = 0; break; }
            }
            if (!compat) continue;
            int can_apply = 0;
            for (int lv2 = emax2; lv2 >= 1; lv2--) {
                if (modified_level >= (lv2 - 1) * 10 + 1) { can_apply = 1; break; }
            }
            if (!can_apply) continue;
            avail2[ai2] = en;
            w2[ai2] = get_enchant_weight(en);
            total_w += w2[ai2];
            ai2++;
        }
        if (ai2 == 0 || total_w == 0) break;

        roll = xoroshiro_next_int(rng, total_w);
        acc = 0; chosen = -1;
        for (int i = 0; i < ai2; i++) {
            acc += w2[i];
            if (roll < acc) { chosen = i; break; }
        }
        if (chosen < 0) break;

        int em = get_equip_ench_max(avail2[chosen]);
        int lvp = em;
        for (int lv2 = em; lv2 >= 1; lv2--) {
            if (modified_level >= (lv2 - 1) * 10 + 1) { lvp = lv2; break; }
        }
        t->enchantments[t->num_enchants] = avail2[chosen];
        t->enchant_levels[t->num_enchants] = lvp;
        t->num_enchants++;
    }
}

static void simulate_stew_effect(Xoroshiro128PlusPlus* rng, Trade* t) {
    int idx = xoroshiro_next_int(rng, 6);
    t->type = TRADE_TYPE_STEW;
    t->effect = STEW_EFFECTS[idx];
    t->duration_ticks = STEW_DURATIONS[idx];
}

static void simulate_random_potion(Xoroshiro128PlusPlus* rng, Trade* t) {
    int idx = xoroshiro_next_int(rng, NUM_TRADEABLE_POTIONS);
    t->type = TRADE_TYPE_TIPPED_ARROW;
    t->potion = TRADEABLE_POTION_LIST[idx];
}

static void simulate_random_dyes(Xoroshiro128PlusPlus* rng, Trade* t) {
    /* Binomial(n=2, p=0.75) → dye count 1+successes */
    int successes = 0;
    for (int i = 0; i < 2; i++)
        if (xoroshiro_next_int(rng, 4) < 3) successes++;
    int count = 1 + successes;
    if (count > 3) count = 3;

    static const char* dye_names[] = {
        "white","orange","magenta","light_blue","yellow","lime",
        "pink","gray","light_gray","cyan","purple","blue",
        "brown","green","red","black"
    };
    t->type = TRADE_TYPE_DYED_EQUIP;
    t->dye_count = count;
    for (int i = 0; i < count; i++)
        t->dyes[i] = dye_names[xoroshiro_next_int(rng, 16)];
}

static void generate_offer(Xoroshiro128PlusPlus* rng, Trade* t, const char* entry) {
    memset(t, 0, sizeof(Trade));
    if (is_enchanted_book_entry(entry)) {
        simulate_enchanted_book(rng, t);
        t->entry = entry;
    } else if (is_enchanted_equipment_entry(entry)) {
        simulate_enchanted_equipment(rng, t, entry);
        t->entry = entry;
    } else if (is_suspicious_stew_entry(entry)) {
        simulate_stew_effect(rng, t);
        t->entry = entry;
    } else if (is_tipped_arrow_entry(entry)) {
        simulate_random_potion(rng, t);
        t->entry = entry;
    } else if (is_dyed_equipment_entry(entry)) {
        simulate_random_dyes(rng, t);
        t->entry = entry;
    } else {
        t->type = TRADE_TYPE_OTHER;
        t->entry = entry;
    }
}

/* ====== Pool access ====== */
#define MAX_POOL_ENTRIES 40

static LevelData* get_level_data(int profession, int level) {
    extern LevelData* ALL_LEVEL_DATA[];
    static LevelData empty = {NULL, 0, 0, {-1,-1,-1,-1}, {-1,-1,-1,-1}};
    LevelData* arr = ALL_LEVEL_DATA[profession];
    LevelData* ld = &arr[level - 1];
    if (ld->pool == NULL) return &empty;
    return ld;
}

static int filter_pool_cartographer(int level, const char* variant,
                                     const char** pool, int pool_size,
                                     const char** out, int* out_size) {
    *out_size = 0;
    if (variant && (level == 2 || level == 4)) {
        /* Filter cartographer trades by variant biome */
        for (int i = 0; i < pool_size; i++) {
            const char* e = pool[i];
            int keep = 1;
            const char* suffix = strrchr(e, '/');
            if (suffix) suffix++; else suffix = e;

            if (strcmp(variant, "desert") == 0) {
                if (strstr(suffix, "savanna") || strstr(suffix, "plains") ||
                    strstr(suffix, "snow") || strstr(suffix, "jungle") ||
                    strstr(suffix, "swamp") || strstr(suffix, "taiga")) keep = 0;
            } else if (strcmp(variant, "jungle") == 0) {
                if (strstr(suffix, "savanna") || strstr(suffix, "plains") ||
                    strstr(suffix, "snow") || strstr(suffix, "desert") ||
                    strstr(suffix, "swamp") || strstr(suffix, "taiga")) keep = 0;
            } else if (strcmp(variant, "plains") == 0) {
                if (strstr(suffix, "savanna") || strstr(suffix, "desert") ||
                    strstr(suffix, "snow") || strstr(suffix, "jungle") ||
                    strstr(suffix, "swamp") || strstr(suffix, "taiga")) keep = 0;
            } else if (strcmp(variant, "savanna") == 0) {
                if (strstr(suffix, "plains") || strstr(suffix, "desert") ||
                    strstr(suffix, "snow") || strstr(suffix, "jungle") ||
                    strstr(suffix, "swamp") || strstr(suffix, "taiga")) keep = 0;
            } else if (strcmp(variant, "snow") == 0) {
                if (strstr(suffix, "savanna") || strstr(suffix, "plains") ||
                    strstr(suffix, "desert") || strstr(suffix, "jungle") ||
                    strstr(suffix, "swamp") || strstr(suffix, "taiga")) keep = 0;
            } else if (strcmp(variant, "swamp") == 0) {
                if (strstr(suffix, "savanna") || strstr(suffix, "plains") ||
                    strstr(suffix, "snow") || strstr(suffix, "jungle") ||
                    strstr(suffix, "desert") || strstr(suffix, "taiga")) keep = 0;
            } else if (strcmp(variant, "taiga") == 0) {
                if (strstr(suffix, "savanna") || strstr(suffix, "plains") ||
                    strstr(suffix, "snow") || strstr(suffix, "jungle") ||
                    strstr(suffix, "swamp") || strstr(suffix, "desert")) keep = 0;
            }
            if (keep) out[(*out_size)++] = e;
        }
        return 1;
    }
    return 0;
}

/* Fisherman L5: boat type depends on villager biome variant
   plains→oak, taiga/snow→spruce, desert/jungle→jungle,
   savanna→acacia, swamp→dark_oak */
static int filter_pool_fisherman(int level, const char* variant,
                                  const char** pool, int pool_size,
                                  const char** out, int* out_size) {
    *out_size = 0;
    if (variant && level == 5) {
        const char* boat_suffix;
        if (strcmp(variant, "plains") == 0)
            boat_suffix = "5/oak_boat_emerald";
        else if (strcmp(variant, "taiga") == 0 || strcmp(variant, "snow") == 0)
            boat_suffix = "5/spruce_boat_emerald";
        else if (strcmp(variant, "desert") == 0 || strcmp(variant, "jungle") == 0)
            boat_suffix = "5/jungle_boat_emerald";
        else if (strcmp(variant, "savanna") == 0)
            boat_suffix = "5/acacia_boat_emerald";
        else if (strcmp(variant, "swamp") == 0)
            boat_suffix = "5/dark_oak_boat_emerald";
        else
            return 0;

        for (int i = 0; i < pool_size; i++) {
            const char* e = pool[i];
            if (strstr(e, "5/pufferfish_emerald") || strstr(e, boat_suffix))
                out[(*out_size)++] = e;
        }
        return 1;
    }
    return 0;
}

static void get_filtered_pool(int profession, int level, const char* variant,
                              const char** out, int* out_size, int* amount) {
    LevelData* ld = get_level_data(profession, level);
    *amount = ld->amount;

    if (ld->pool == NULL) { *out_size = 0; *amount = 0; return; }

    /* Copy original pool */
    const char** pool = ld->pool;
    int pool_size = ld->pool_size;

    /* Apply cartographer variant filter */
    if (profession == PROF_CARTOGRAPHER) {
        if (filter_pool_cartographer(level, variant, pool, pool_size, out, out_size))
            goto done;
    }

    /* Apply fisherman boat variant filter (level 5) */
    if (profession == PROF_FISHERMAN) {
        if (filter_pool_fisherman(level, variant, pool, pool_size, out, out_size))
            goto done;
    }

    /* Shepherd and leatherworker: no filtering in current data */
    /* Shepherds: painting entry filtered by shepherd variant (level 5) */

    /* Default: copy all */
    for (int i = 0; i < pool_size; i++)
        out[i] = pool[i];
    *out_size = pool_size;
done:
    ;
}

/* ====== Main simulation ====== */
void simulate_trades(int profession, int level, const char* variant,
                     Xoroshiro128PlusPlus* rng, TradeResult* result) {
    const char* pool[MAX_POOL_ENTRIES];
    int pool_size, amount;
    get_filtered_pool(profession, level, variant, pool, &pool_size, &amount);
    result->count = 0;

    if (pool_size == 0 || amount == 0) return;

    /* Make mutable copy */
    const char* remaining[MAX_POOL_ENTRIES];
    int n = pool_size;
    for (int i = 0; i < n; i++) remaining[i] = pool[i];

    for (int found = 0; found < amount && n > 0; found++) {
        /* 100% probability case: if only n entries remain and we need n more */
        int idx;
        if (n <= amount - found) {
            idx = 0; /* unconditional pick */
        } else {
            idx = xoroshiro_next_int(rng, n);
        }

        const char* picked = remaining[idx];
        /* Remove from remaining */
        for (int i = idx; i < n - 1; i++) remaining[i] = remaining[i + 1];
        n--;

        Trade* t = &result->trades[result->count];
        generate_offer(rng, t, picked);
        result->count++;
    }
}

void consume_trade_generation(int profession, int level, const char* variant,
                              Xoroshiro128PlusPlus* rng) {
    const char* pool[MAX_POOL_ENTRIES];
    int pool_size, amount;
    get_filtered_pool(profession, level, variant, pool, &pool_size, &amount);

    if (pool_size == 0 || amount == 0) return;

    const char* remaining[MAX_POOL_ENTRIES];
    int n = pool_size;
    for (int i = 0; i < n; i++) remaining[i] = pool[i];

    for (int found = 0; found < amount && n > 0; found++) {
        int idx;
        Trade dummy;
        if (n <= amount - found) {
            idx = 0;
        } else {
            idx = xoroshiro_next_int(rng, n);
        }
        const char* picked = remaining[idx];
        for (int i = idx; i < n - 1; i++) remaining[i] = remaining[i + 1];
        n--;
        generate_offer(rng, &dummy, picked);
    }
}

void create_rng_for(int64_t world_seed, int profession, int level,
                    Xoroshiro128PlusPlus* rng) {
    char id[64];
    snprintf(id, sizeof(id), "%s;%lld", PROFESSION_NAMES[profession],
             (long long)world_seed);
    Seed128 s = create_random_sequence_seed(world_seed, id);
    xoroshiro_init(rng, (int64_t)s.lo, (int64_t)s.hi);
}

void predictor_predict_at_offset(
    int64_t world_seed, int profession, int level, int offset,
    const char* variant, TradeResult* result
) {
    Xoroshiro128PlusPlus rng;
    create_rng_for(world_seed, profession, level, &rng);

    for (int i = 0; i < offset; i++)
        consume_trade_generation(profession, level, variant, &rng);

    simulate_trades(profession, level, variant, &rng, result);
}

/* ====== String helpers ====== */

/* Chinese enchantment names */
static const char* ENCH_CN[] = {
    "protection","fire_protection","feather_falling","blast_protection",
    "projectile_protection","respiration","aqua_affinity","thorns",
    "depth_strider","sharpness","smite","bane_of_arthropods",
    "knockback","fire_aspect","looting","sweeping_edge",
    "efficiency","silk_touch","unbreaking","fortune",
    "power","punch","flame","infinity","luck_of_the_sea","lure",
    "loyalty","impaling","riptide","channeling","multishot",
    "quick_charge","piercing","density","breach","lunge",
    "binding_curse","vanishing_curse","swift_sneak","soul_speed",
    "frost_walker","mending","wind_burst"
};
static const char* ENCH_NAME_CN[] = {
    "\344\277\235\346\212\244","\347\201\253\347\204\260\344\277\235\346\212\244",
    "\346\221\224\350\220\275\344\277\235\346\212\244","\347\210\206\347\202\270\344\277\235\346\212\244",
    "\345\274\271\345\260\204\347\211\251\344\277\235\346\212\244","\346\260\264\344\270\213\345\221\274\345\220\270",
    "\346\260\264\344\270\213\351\200\237\346\216\230","\350\215\206\346\243\230",
    "\346\267\261\346\265\267\346\216\242\347\264\242\350\200\205","\351\224\213\345\210\251",
    "\344\272\241\347\201\265\346\235\200\346\211\213","\350\212\202\350\202\242\346\235\200\346\211\213",
    "\345\207\273\351\200\200","\347\201\253\347\204\260\351\231\204\345\212\240",
    "\346\212\242\345\244\272","\346\250\252\346\211\253\344\271\213\345\210\203",
    "\346\225\210\347\216\207","\347\262\276\345\207\206\351\207\207\351\233\206",
    "\350\200\220\344\271\205","\346\227\266\350\277\220","\345\212\233\351\207\217",
    "\345\206\262\345\207\273","\347\201\253\347\237\242","\346\227\240\351\231\220",
    "\346\265\267\344\271\213\347\234\267\351\241\276","\351\245\265\351\222\223",
    "\345\277\240\350\257\232","\347\251\277\345\210\272","\346\277\200\346\265\201",
    "\345\274\225\351\233\267","\345\244\232\351\207\215\345\260\204\345\207\273",
    "\345\277\253\351\200\237\350\243\205\345\241\253","\347\251\277\351\200\217",
    "\350\207\264\345\257\206","\347\240\264\347\224\262","\347\252\201\350\277\233",
    "\347\273\221\345\256\232\350\257\205\345\222\222","\346\266\210\345\244\261\350\257\205\345\222\222",
    "\350\277\205\346\215\267\346\275\234\350\241\214","\347\201\265\351\255\202\347\226\276\350\241\214",
    "\345\206\260\351\234\234\350\241\214\350\200\205","\347\273\217\351\252\214\344\277\256\350\241\245",
    "\351\243\216\347\210\206"
};

const char* get_ench_cn(const char* en) {
    static const char* en_keys[] = {
        "protection","fire_protection","feather_falling","blast_protection",
        "projectile_protection","respiration","aqua_affinity","thorns",
        "depth_strider","sharpness","smite","bane_of_arthropods",
        "knockback","fire_aspect","looting","sweeping_edge",
        "efficiency","silk_touch","unbreaking","fortune",
        "power","punch","flame","infinity","luck_of_the_sea","lure",
        "loyalty","impaling","riptide","channeling","multishot",
        "quick_charge","piercing","density","breach","lunge",
        "binding_curse","vanishing_curse","swift_sneak","soul_speed",
        "frost_walker","mending","wind_burst",NULL
    };
    for (int i = 0; en_keys[i]; i++)
        if (strcmp(en, en_keys[i]) == 0) return ENCH_NAME_CN[i];
    return en;
}

void trade_to_string(const Trade* t, int level, char* buf, int bufsize) {
    (void)level;
    switch (t->type) {
    case TRADE_TYPE_ENCHANT_BOOK:
        snprintf(buf, bufsize, "%s %d (%dE)%s",
                 get_ench_cn(t->enchantment), t->ench_level,
                 t->final_cost, t->is_treasure ? " [\345\256\235\350\227\217]" : "");
        break;
    case TRADE_TYPE_ENCHANT_EQUIP: {
        char enc_part[256] = "";
        for (int i = 0; i < t->num_enchants; i++) {
            char tmp[64];
            snprintf(tmp, sizeof(tmp), "%s%s %d",
                     i > 0 ? ", " : "",
                     get_ench_cn(t->enchantments[i]), t->enchant_levels[i]);
            strcat(enc_part, tmp);
        }
        const char* item_name = t->item ? t->item : "?";
        snprintf(buf, bufsize, "%s [%s] (%dE)", item_name, enc_part, t->final_cost);
        break;
    }
    case TRADE_TYPE_STEW: {
        static const char* stew_cn[] = {
            "\345\244\234\350\247\206","\350\267\263\350\267\203\346\217\220\345\215\207",
            "\350\231\232\345\274\261","\345\244\261\346\230\216","\344\270\255\346\257\222",
            "\351\245\261\345\222\214"
        };
        const char* eff = t->effect;
        for (int i = 0; i < 6; i++)
            if (strcmp(eff, STEW_EFFECTS[i]) == 0) { eff = stew_cn[i]; break; }
        snprintf(buf, bufsize, "\350\277\267\344\271\213\347\202\226\350\217\234: %s (%.0f\347\247\222)",
                 eff, t->duration_ticks / 20.0);
        break;
    }
    case TRADE_TYPE_TIPPED_ARROW: {
        static const char* pot_cn_keys[] = {"wind_charged","oozing","infested","weaving",
            "night_vision","invisibility","fire_resistance","leaping","slowness",
            "turtle_master","swiftness","water_breathing","healing","harming",
            "poison","regeneration","strength","weakness","slow_falling",NULL};
        static const char* pot_cn_vals[] = {
            "\351\243\216\345\274\271","\346\270\227\346\265\206","\350\231\253\350\232\200",
            "\347\273\207\347\275\221","\345\244\234\350\247\206","\351\232\220\350\272\253",
            "\346\212\227\347\201\253","\350\267\263\350\267\203","\347\274\223\346\205\242",
            "\347\245\236\351\276\237","\350\277\205\346\215\267","\346\260\264\350\202\272",
            "\346\262\273\347\226\227","\344\274\244\345\256\263","\345\211\247\346\257\222",
            "\345\206\215\347\224\237","\345\212\233\351\207\217","\350\231\232\345\274\261",
            "\347\274\223\351\231\215"
        };
        const char* pot = t->potion;
        for (int i = 0; pot_cn_keys[i]; i++) {
            if (strstr(t->potion, pot_cn_keys[i]) == t->potion) {
                const char* rest = t->potion + strlen(pot_cn_keys[i]);
                if (strcmp(rest, "") == 0 || strcmp(rest, "_long") == 0 || strcmp(rest, "_strong") == 0) {
                    char full[64];
                    if (*rest) {
                        const char* suffix = strcmp(rest, "_long") == 0 ?
                            (strcmp(pot_cn_keys[i],"turtle_master")==0 ? "(\345\273\266\351\225\277)" : "(\345\273\266\351\225\277)") :
                            (strcmp(pot_cn_keys[i],"turtle_master")==0 ? "II" : (strcmp(pot_cn_keys[i],"leaping")==0 ? "II" :
                             strcmp(pot_cn_keys[i],"swiftness")==0 ? "II" : "II"));
                        snprintf(full, sizeof(full), "%s%s", pot_cn_vals[i], suffix);
                    } else {
                        snprintf(full, sizeof(full), "%s", pot_cn_vals[i]);
                    }
                    snprintf(buf, bufsize, "\350\215\257\347\256\255: %s", full);
                    return;
                }
            }
        }
        snprintf(buf, bufsize, "\350\215\257\347\256\255: %s", t->potion);
        break;
    }
    case TRADE_TYPE_DYED_EQUIP: {
        char dyes[128] = "";
        for (int i = 0; i < t->dye_count; i++) {
            if (i > 0) strcat(dyes, ", ");
            strcat(dyes, t->dyes[i]);
        }
        snprintf(buf, bufsize, "\346\237\223\350\211\262\350\243\205\345\244\207: %s", dyes);
        break;
    }
    default:
        if (t->entry) {
            const char* name = strrchr(t->entry, '/');
            snprintf(buf, bufsize, "%s", name ? name + 1 : t->entry);
        } else {
            snprintf(buf, bufsize, "?");
        }
        break;
    }
}

void trade_to_csv_row(const Trade* t, int offset, int level, char* buf, int bufsize) {
    char detail1[128] = "", detail2[128] = "", ench_lv[16] = "", price[16] = "", treasure[8] = "";
    const char* type_str = "\346\231\256\351\200\232";
    const char* entry_name = t->entry ? (strrchr(t->entry, '/') ? strrchr(t->entry, '/') + 1 : t->entry) : "";

    switch (t->type) {
    case TRADE_TYPE_ENCHANT_BOOK:
        type_str = "\351\231\204\351\255\224\344\271\246";
        snprintf(detail1, sizeof(detail1), "%s", get_ench_cn(t->enchantment));
        snprintf(detail2, sizeof(detail2), "%s", t->enchantment);
        snprintf(ench_lv, sizeof(ench_lv), "%d", t->ench_level);
        snprintf(price, sizeof(price), "%d", t->final_cost);
        snprintf(treasure, sizeof(treasure), "%s", t->is_treasure ? "\346\230\257" : "\345\220\246");
        break;
    case TRADE_TYPE_ENCHANT_EQUIP: {
        type_str = "\351\231\204\351\255\224\350\243\205\345\244\207";
        const char* iname = t->item ? t->item : "?";
        if (strncmp(iname, "minecraft:", 10) == 0) iname += 10;
        snprintf(detail1, sizeof(detail1), "%s", iname);
        char encs[256] = "";
        for (int i = 0; i < t->num_enchants; i++) {
            char tmp[64];
            snprintf(tmp, sizeof(tmp), "%s%s %d", i > 0 ? "; " : "",
                     get_ench_cn(t->enchantments[i]), t->enchant_levels[i]);
            strcat(encs, tmp);
        }
        snprintf(detail2, sizeof(detail2), "%s", encs);
        snprintf(price, sizeof(price), "%d", t->final_cost);
        break;
    }
    case TRADE_TYPE_STEW:
        type_str = "\350\277\267\344\271\213\347\202\226\350\217\234";
        snprintf(detail1, sizeof(detail1), "%s", t->effect);
        snprintf(detail2, sizeof(detail2), "%.0f\347\247\222", t->duration_ticks / 20.0);
        break;
    case TRADE_TYPE_TIPPED_ARROW:
        type_str = "\350\215\257\347\256\255";
        snprintf(detail1, sizeof(detail1), "%s", t->potion);
        break;
    case TRADE_TYPE_DYED_EQUIP:
        type_str = "\346\237\223\350\211\262\350\243\205\345\244\207";
        {
            char dyes[128] = "";
            for (int i = 0; i < t->dye_count; i++) {
                if (i > 0) strcat(dyes, "/");
                strcat(dyes, t->dyes[i]);
            }
            snprintf(detail1, sizeof(detail1), "%s", dyes);
            snprintf(detail2, sizeof(detail2), "%d", t->dye_count);
        }
        break;
    default:
        break;
    }

    snprintf(buf, bufsize, "%d,%d,%s,%s,%s,%s,%s,%s,%s",
             offset, level, entry_name, type_str,
             detail1, detail2, ench_lv, price, treasure);
}
