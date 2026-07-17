#ifndef VILLAGER_TRADE_H
#define VILLAGER_TRADE_H

#include <stdint.h>

#include "xoroshiro128pp.h"

/* Maximum number of trades per profession/level */
#define MAX_TRADES_PER_LEVEL 4
/* Maximum trade entries in CSV row */
#define CSV_COLS 9

/* Trade type codes */
#define TRADE_TYPE_OTHER          0
#define TRADE_TYPE_ENCHANT_BOOK   1
#define TRADE_TYPE_ENCHANT_EQUIP  2
#define TRADE_TYPE_STEW           3
#define TRADE_TYPE_TIPPED_ARROW   4
#define TRADE_TYPE_DYED_EQUIP     5

/* Single generated trade */
typedef struct {
    int type;               /* TRADE_TYPE_* */
    int final_cost;         /* emerald price */
    /* enchanted book */
    const char* enchantment;
    int ench_level;
    int is_treasure;
    /* enchanted equipment */
    const char* item;
    const char* enchantments[4];
    int enchant_levels[4];
    int num_enchants;
    /* stew */
    const char* effect;
    int duration_ticks;
    /* tipped arrow */
    const char* potion;
    /* dyed equipment */
    const char* dyes[3];
    int dye_count;
    /* other */
    const char* entry;
} Trade;

/* Trade result for one offset */
typedef struct {
    Trade trades[MAX_TRADES_PER_LEVEL];
    int count;
} TradeResult;

/* Profession constants */
#define PROF_ARMORER      0
#define PROF_BUTCHER       1
#define PROF_CARTOGRAPHER  2
#define PROF_CLERIC        3
#define PROF_FARMER        4
#define PROF_FISHERMAN     5
#define PROF_FLETCHER      6
#define PROF_LEATHERWORKER 7
#define PROF_LIBRARIAN     8
#define PROF_MASON         9
#define PROF_SHEPHERD      10
#define PROF_TOOLSMITH     11
#define PROF_WEAPONSMITH   12

extern const char* PROFESSION_NAMES[];

/* Main API */
void create_rng_for(int64_t world_seed, int profession, int level,
                    Xoroshiro128PlusPlus* rng);
void simulate_trades(int profession, int level, const char* variant,
                     Xoroshiro128PlusPlus* rng, TradeResult* result);
void consume_trade_generation(int profession, int level, const char* variant,
                              Xoroshiro128PlusPlus* rng);
void predictor_predict_at_offset(
    int64_t world_seed, int profession, int level, int offset,
    const char* variant, TradeResult* result);

void trade_to_string(const Trade* t, int level, char* buf, int bufsize);
void trade_to_csv_row(const Trade* t, int offset, int level, char* buf, int bufsize);
const char* get_ench_cn(const char* en);

#endif
