/* Auto-generated from villager_trade_predictor.py */
#include "villager_trade.h"
#include <string.h>

/* ====== Tradeable Enchantments (40) ====== */
#define NUM_TRADEABLE_ENCHANTMENTS 40
static const char* TRADEABLE_ENCHANT_NAMES[] = {
    "protection",
    "fire_protection",
    "feather_falling",
    "blast_protection",
    "projectile_protection",
    "respiration",
    "aqua_affinity",
    "thorns",
    "depth_strider",
    "sharpness",
    "smite",
    "bane_of_arthropods",
    "knockback",
    "fire_aspect",
    "looting",
    "sweeping_edge",
    "efficiency",
    "silk_touch",
    "unbreaking",
    "fortune",
    "power",
    "punch",
    "flame",
    "infinity",
    "luck_of_the_sea",
    "lure",
    "loyalty",
    "impaling",
    "riptide",
    "channeling",
    "multishot",
    "quick_charge",
    "piercing",
    "density",
    "breach",
    "lunge",
    "binding_curse",
    "vanishing_curse",
    "frost_walker",
    "mending",
};
static const int TRADEABLE_ENCHANT_MAX[] = {
    4,
    4,
    4,
    4,
    4,
    3,
    1,
    3,
    3,
    5,
    5,
    5,
    2,
    2,
    3,
    3,
    5,
    1,
    3,
    3,
    5,
    2,
    1,
    1,
    3,
    3,
    3,
    5,
    3,
    1,
    1,
    3,
    4,
    5,
    4,
    3,
    1,
    1,
    2,
    1,
};

static int is_treasure_enchant(const char* name) {
    if (strcmp(name, "swift_sneak") == 0) return 1;
    if (strcmp(name, "soul_speed") == 0) return 1;
    if (strcmp(name, "frost_walker") == 0) return 1;
    if (strcmp(name, "binding_curse") == 0) return 1;
    if (strcmp(name, "vanishing_curse") == 0) return 1;
    if (strcmp(name, "mending") == 0) return 1;
    if (strcmp(name, "wind_burst") == 0) return 1;
    return 0;
}

const char* PROFESSION_NAMES[] = {
    "armorer",
    "butcher",
    "cartographer",
    "cleric",
    "farmer",
    "fisherman",
    "fletcher",
    "leatherworker",
    "librarian",
    "mason",
    "shepherd",
    "toolsmith",
    "weaponsmith",
};

/* Pool entries per profession/level */
typedef struct { const char* entry; } TradeEntry;

static const char* pool_armorer_L1[] = {
    "minecraft:smith/1/coal_emerald",
    "minecraft:armorer/1/emerald_iron_leggings",
    "minecraft:armorer/1/emerald_iron_boots",
    "minecraft:armorer/1/emerald_iron_helmet",
    "minecraft:armorer/1/emerald_iron_chestplate",
};
#define POOL_SIZE_armorer_L1 5

static const char* pool_armorer_L2[] = {
    "minecraft:smith/2/iron_ingot_emerald",
    "minecraft:armorer/2/emerald_bell",
    "minecraft:armorer/2/emerald_chainmail_boots",
    "minecraft:armorer/2/emerald_chainmail_leggings",
};
#define POOL_SIZE_armorer_L2 4

static const char* pool_armorer_L3[] = {
    "minecraft:armorer/3/lava_bucket_emerald",
    "minecraft:armorer/3/emerald_chainmail_helmet",
    "minecraft:armorer/3/emerald_chainmail_chestplate",
    "minecraft:armorer/3/emerald_shield",
    "minecraft:armorer/3/diamond_emerald",
};
#define POOL_SIZE_armorer_L3 5

static const char* pool_armorer_L4[] = {
    "minecraft:armorer/4/emerald_enchanted_diamond_leggings",
    "minecraft:armorer/4/emerald_enchanted_diamond_boots",
};
#define POOL_SIZE_armorer_L4 2

static const char* pool_armorer_L5[] = {
    "minecraft:armorer/5/emerald_enchanted_diamond_helmet",
    "minecraft:armorer/5/emerald_enchanted_diamond_chestplate",
};
#define POOL_SIZE_armorer_L5 2

static const char* pool_butcher_L1[] = {
    "minecraft:butcher/1/chicken_emerald",
    "minecraft:butcher/1/porkchop_emerald",
    "minecraft:butcher/1/rabbit_emerald",
    "minecraft:butcher/1/emerald_rabbit_stew",
};
#define POOL_SIZE_butcher_L1 4

static const char* pool_butcher_L2[] = {
    "minecraft:butcher/2/coal_emerald",
    "minecraft:butcher/2/emerald_cooked_porkchop",
    "minecraft:butcher/2/emerald_cooked_chicken",
};
#define POOL_SIZE_butcher_L2 3

static const char* pool_butcher_L3[] = {
    "minecraft:butcher/3/mutton_emerald",
    "minecraft:butcher/3/beef_emerald",
};
#define POOL_SIZE_butcher_L3 2

static const char* pool_butcher_L4[] = {
    "minecraft:butcher/4/dried_kelp_block_emerald",
};
#define POOL_SIZE_butcher_L4 1

static const char* pool_butcher_L5[] = {
    "minecraft:butcher/5/sweet_berries_emerald",
};
#define POOL_SIZE_butcher_L5 1

static const char* pool_cartographer_L1[] = {
    "minecraft:cartographer/1/paper_emerald",
    "minecraft:cartographer/1/emerald_map",
};
#define POOL_SIZE_cartographer_L1 2

static const char* pool_cartographer_L2[] = {
    "minecraft:cartographer/2/glass_pane_emerald",
    "minecraft:cartographer/2/emerald_and_compass_village_taiga_map",
    "minecraft:cartographer/2/emerald_and_compass_explorer_swamp_map",
    "minecraft:cartographer/2/emerald_and_compass_village_snowy_map",
    "minecraft:cartographer/2/emerald_and_compass_village_savanna_map",
    "minecraft:cartographer/2/emerald_and_compass_village_plains_map",
    "minecraft:cartographer/2/emerald_and_compass_explorer_jungle_map",
    "minecraft:cartographer/2/emerald_and_compass_village_desert_map",
};
#define POOL_SIZE_cartographer_L2 8

static const char* pool_cartographer_L3[] = {
    "minecraft:cartographer/3/compass_emerald",
    "minecraft:cartographer/3/emerald_and_compass_ocean_explorer_map",
    "minecraft:cartographer/3/emerald_and_compass_trial_chamber_map",
};
#define POOL_SIZE_cartographer_L3 3

static const char* pool_cartographer_L4[] = {
    "minecraft:cartographer/4/emerald_item_frame",
    "minecraft:cartographer/4/emerald_white_banner",
    "minecraft:cartographer/4/emerald_orange_banner",
    "minecraft:cartographer/4/emerald_magenta_banner",
    "minecraft:cartographer/4/emerald_blue_banner",
    "minecraft:cartographer/4/emerald_light_blue_banner",
    "minecraft:cartographer/4/emerald_yellow_banner",
    "minecraft:cartographer/4/emerald_lime_banner",
    "minecraft:cartographer/4/emerald_pink_banner",
    "minecraft:cartographer/4/emerald_gray_banner",
    "minecraft:cartographer/4/emerald_cyan_banner",
    "minecraft:cartographer/4/emerald_purple_banner",
    "minecraft:cartographer/4/emerald_brown_banner",
    "minecraft:cartographer/4/emerald_green_banner",
    "minecraft:cartographer/4/emerald_red_banner",
    "minecraft:cartographer/4/emerald_black_banner",
};
#define POOL_SIZE_cartographer_L4 16

static const char* pool_cartographer_L5[] = {
    "minecraft:cartographer/5/emerald_globe_banner_pattern",
    "minecraft:cartographer/5/emerald_and_compass_woodland_mansion_map",
};
#define POOL_SIZE_cartographer_L5 2

static const char* pool_cleric_L1[] = {
    "minecraft:cleric/1/rotten_flesh_emerald",
    "minecraft:cleric/1/emerald_redstone",
};
#define POOL_SIZE_cleric_L1 2

static const char* pool_cleric_L2[] = {
    "minecraft:cleric/2/gold_ingot_emerald",
    "minecraft:cleric/2/emerald_lapis_lazuli",
};
#define POOL_SIZE_cleric_L2 2

static const char* pool_cleric_L3[] = {
    "minecraft:cleric/3/rabbit_foot_emerald",
    "minecraft:cleric/3/emerald_glowstone",
};
#define POOL_SIZE_cleric_L3 2

static const char* pool_cleric_L4[] = {
    "minecraft:cleric/4/turtle_scute_emerald",
    "minecraft:cleric/4/glass_bottle_emerald",
    "minecraft:cleric/4/emerald_ender_pearl",
};
#define POOL_SIZE_cleric_L4 3

static const char* pool_cleric_L5[] = {
    "minecraft:cleric/5/nether_wart_emerald",
    "minecraft:cleric/5/emerald_experience_bottle",
};
#define POOL_SIZE_cleric_L5 2

static const char* pool_farmer_L1[] = {
    "minecraft:farmer/1/wheat_emerald",
    "minecraft:farmer/1/potato_emerald",
    "minecraft:farmer/1/carrot_emerald",
    "minecraft:farmer/1/beetroot_emerald",
    "minecraft:farmer/1/emerald_bread",
};
#define POOL_SIZE_farmer_L1 5

static const char* pool_farmer_L2[] = {
    "minecraft:farmer/2/pumpkin_emerald",
    "minecraft:farmer/2/emerald_pumpkin_pie",
    "minecraft:farmer/2/emerald_apple",
};
#define POOL_SIZE_farmer_L2 3

static const char* pool_farmer_L3[] = {
    "minecraft:farmer/3/emerald_cookie",
    "minecraft:farmer/3/melon_emerald",
};
#define POOL_SIZE_farmer_L3 2

static const char* pool_farmer_L4[] = {
    "minecraft:farmer/4/emerald_cake",
    "minecraft:farmer/4/emerald_suspicious_stew",
};
#define POOL_SIZE_farmer_L4 2

static const char* pool_farmer_L5[] = {
    "minecraft:farmer/5/emerald_golden_carrot",
    "minecraft:farmer/5/emerald_glistening_melon_slice",
};
#define POOL_SIZE_farmer_L5 2

static const char* pool_fisherman_L1[] = {
    "minecraft:fisherman/1/string_emerald",
    "minecraft:fisherman/1/coal_emerald",
    "minecraft:fisherman/1/raw_cod_and_emerald_cooked_cod",
    "minecraft:fisherman/1/emerald_cod_bucket",
};
#define POOL_SIZE_fisherman_L1 4

static const char* pool_fisherman_L2[] = {
    "minecraft:fisherman/2/cod_emerald",
    "minecraft:fisherman/2/salmon_and_emerald_cooked_salmon",
    "minecraft:fisherman/2/emerald_campfire",
};
#define POOL_SIZE_fisherman_L2 3

static const char* pool_fisherman_L3[] = {
    "minecraft:fisherman/3/salmon_emerald",
    "minecraft:fisherman/3/emerald_enchanted_fishing_rod",
};
#define POOL_SIZE_fisherman_L3 2

static const char* pool_fisherman_L4[] = {
    "minecraft:fisherman/4/tropical_fish_emerald",
};
#define POOL_SIZE_fisherman_L4 1

static const char* pool_fisherman_L5[] = {
    "minecraft:fisherman/5/pufferfish_emerald",
    "minecraft:fisherman/5/oak_boat_emerald",
    "minecraft:fisherman/5/spruce_boat_emerald",
    "minecraft:fisherman/5/jungle_boat_emerald",
    "minecraft:fisherman/5/acacia_boat_emerald",
    "minecraft:fisherman/5/dark_oak_boat_emerald",
};
#define POOL_SIZE_fisherman_L5 6

static const char* pool_fletcher_L1[] = {
    "minecraft:fletcher/1/stick_emerald",
    "minecraft:fletcher/1/emerald_arrow",
    "minecraft:fletcher/1/gravel_and_emerald_flint",
};
#define POOL_SIZE_fletcher_L1 3

static const char* pool_fletcher_L2[] = {
    "minecraft:fletcher/2/flint_emerald",
    "minecraft:fletcher/2/emerald_bow",
};
#define POOL_SIZE_fletcher_L2 2

static const char* pool_fletcher_L3[] = {
    "minecraft:fletcher/3/string_emerald",
    "minecraft:fletcher/3/emerald_crossbow",
};
#define POOL_SIZE_fletcher_L3 2

static const char* pool_fletcher_L4[] = {
    "minecraft:fletcher/4/feather_emerald",
    "minecraft:fletcher/4/emerald_enchanted_bow",
};
#define POOL_SIZE_fletcher_L4 2

static const char* pool_fletcher_L5[] = {
    "minecraft:fletcher/5/tripwire_hook_emerald",
    "minecraft:fletcher/5/emerald_enchanted_crossbow",
    "minecraft:fletcher/5/arrow_and_emerald_tipped_arrow",
};
#define POOL_SIZE_fletcher_L5 3

static const char* pool_leatherworker_L1[] = {
    "minecraft:leatherworker/1/leather_emerald",
    "minecraft:leatherworker/1/emerald_dyed_leather_leggings",
    "minecraft:leatherworker/1/emerald_dyed_leather_chestplate",
};
#define POOL_SIZE_leatherworker_L1 3

static const char* pool_leatherworker_L2[] = {
    "minecraft:leatherworker/2/flint_emerald",
    "minecraft:leatherworker/2/emerald_dyed_leather_helmet",
    "minecraft:leatherworker/2/emerald_dyed_leather_boots",
};
#define POOL_SIZE_leatherworker_L2 3

static const char* pool_leatherworker_L3[] = {
    "minecraft:leatherworker/3/rabbit_hide_emerald",
    "minecraft:leatherworker/3/emerald_dyed_leather_chestplate",
};
#define POOL_SIZE_leatherworker_L3 2

static const char* pool_leatherworker_L4[] = {
    "minecraft:leatherworker/4/turtle_scute_emerald",
    "minecraft:leatherworker/4/emerald_dyed_leather_horse_armor",
};
#define POOL_SIZE_leatherworker_L4 2

static const char* pool_leatherworker_L5[] = {
    "minecraft:leatherworker/5/emerald_saddle",
    "minecraft:leatherworker/5/emerald_dyed_leather_helmet",
};
#define POOL_SIZE_leatherworker_L5 2

static const char* pool_librarian_L1[] = {
    "minecraft:librarian/1/paper_emerald",
    "minecraft:librarian/1/emerald_and_book_enchanted_book",
    "minecraft:librarian/1/emerald_bookshelf",
};
#define POOL_SIZE_librarian_L1 3

static const char* pool_librarian_L2[] = {
    "minecraft:librarian/2/book_emerald",
    "minecraft:librarian/2/emerald_and_book_enchanted_book",
    "minecraft:librarian/2/emerald_lantern",
};
#define POOL_SIZE_librarian_L2 3

static const char* pool_librarian_L3[] = {
    "minecraft:librarian/3/ink_sac_emerald",
    "minecraft:librarian/3/emerald_and_book_enchanted_book",
    "minecraft:librarian/3/emerald_glass",
};
#define POOL_SIZE_librarian_L3 3

static const char* pool_librarian_L4[] = {
    "minecraft:librarian/4/writable_book_emerald",
    "minecraft:librarian/4/emerald_book_and_enchanted_book",
    "minecraft:librarian/4/emerald_clock",
    "minecraft:librarian/4/emerald_compass",
};
#define POOL_SIZE_librarian_L4 4

static const char* pool_librarian_L5[] = {
    "minecraft:librarian/5/emerald_yellow_candle",
    "minecraft:librarian/5/emerald_red_candle",
};
#define POOL_SIZE_librarian_L5 2

static const char* pool_mason_L1[] = {
    "minecraft:mason/1/clay_ball_emerald",
    "minecraft:mason/1/emerald_brick",
};
#define POOL_SIZE_mason_L1 2

static const char* pool_mason_L2[] = {
    "minecraft:mason/2/stone_emerald",
    "minecraft:mason/2/emerald_chiseled_stone_bricks",
};
#define POOL_SIZE_mason_L2 2

static const char* pool_mason_L3[] = {
    "minecraft:mason/3/granite_emerald",
    "minecraft:mason/3/andesite_emerald",
    "minecraft:mason/3/diorite_emerald",
    "minecraft:mason/3/emerald_dripstone_block",
    "minecraft:mason/3/emerald_polished_andesite",
    "minecraft:mason/3/emerald_polished_diorite",
    "minecraft:mason/3/emerald_polished_granite",
};
#define POOL_SIZE_mason_L3 7

static const char* pool_mason_L4[] = {
    "minecraft:mason/4/quartz_emerald",
    "minecraft:mason/4/emerald_orange_terracotta",
    "minecraft:mason/4/emerald_white_terracotta",
    "minecraft:mason/4/emerald_blue_terracotta",
    "minecraft:mason/4/emerald_light_blue_terracotta",
    "minecraft:mason/4/emerald_gray_terracotta",
    "minecraft:mason/4/emerald_light_gray_terracotta",
    "minecraft:mason/4/emerald_black_terracotta",
    "minecraft:mason/4/emerald_red_terracotta",
    "minecraft:mason/4/emerald_pink_terracotta",
    "minecraft:mason/4/emerald_magenta_terracotta",
    "minecraft:mason/4/emerald_lime_terracotta",
    "minecraft:mason/4/emerald_green_terracotta",
    "minecraft:mason/4/emerald_cyan_terracotta",
    "minecraft:mason/4/emerald_purple_terracotta",
    "minecraft:mason/4/emerald_yellow_terracotta",
    "minecraft:mason/4/emerald_brown_terracotta",
    "minecraft:mason/4/emerald_orange_glazed_terracotta",
    "minecraft:mason/4/emerald_white_glazed_terracotta",
    "minecraft:mason/4/emerald_blue_glazed_terracotta",
    "minecraft:mason/4/emerald_light_blue_glazed_terracotta",
    "minecraft:mason/4/emerald_gray_glazed_terracotta",
    "minecraft:mason/4/emerald_light_gray_glazed_terracotta",
    "minecraft:mason/4/emerald_black_glazed_terracotta",
    "minecraft:mason/4/emerald_red_glazed_terracotta",
    "minecraft:mason/4/emerald_pink_glazed_terracotta",
    "minecraft:mason/4/emerald_magenta_glazed_terracotta",
    "minecraft:mason/4/emerald_lime_glazed_terracotta",
    "minecraft:mason/4/emerald_green_glazed_terracotta",
    "minecraft:mason/4/emerald_cyan_glazed_terracotta",
    "minecraft:mason/4/emerald_purple_glazed_terracotta",
    "minecraft:mason/4/emerald_yellow_glazed_terracotta",
    "minecraft:mason/4/emerald_brown_glazed_terracotta",
};
#define POOL_SIZE_mason_L4 33

static const char* pool_mason_L5[] = {
    "minecraft:mason/5/emerald_quartz_pillar",
    "minecraft:mason/5/emerald_quartz_block",
};
#define POOL_SIZE_mason_L5 2

static const char* pool_shepherd_L1[] = {
    "minecraft:shepherd/1/white_wool_emerald",
    "minecraft:shepherd/1/brown_wool_emerald",
    "minecraft:shepherd/1/gray_wool_emerald",
    "minecraft:shepherd/1/black_wool_emerald",
    "minecraft:shepherd/1/emerald_shears",
};
#define POOL_SIZE_shepherd_L1 5

static const char* pool_shepherd_L2[] = {
    "minecraft:shepherd/2/white_dye_emerald",
    "minecraft:shepherd/2/gray_dye_emerald",
    "minecraft:shepherd/2/black_dye_emerald",
    "minecraft:shepherd/2/light_blue_dye_emerald",
    "minecraft:shepherd/2/lime_dye_emerald",
    "minecraft:shepherd/2/emerald_white_wool",
    "minecraft:shepherd/2/emerald_orange_wool",
    "minecraft:shepherd/2/emerald_magenta_wool",
    "minecraft:shepherd/2/emerald_blue_wool",
    "minecraft:shepherd/2/emerald_light_blue_wool",
    "minecraft:shepherd/2/emerald_yellow_wool",
    "minecraft:shepherd/2/emerald_lime_wool",
    "minecraft:shepherd/2/emerald_pink_wool",
    "minecraft:shepherd/2/emerald_gray_wool",
    "minecraft:shepherd/2/emerald_light_gray_wool",
    "minecraft:shepherd/2/emerald_cyan_wool",
    "minecraft:shepherd/2/emerald_purple_wool",
    "minecraft:shepherd/2/emerald_brown_wool",
    "minecraft:shepherd/2/emerald_green_wool",
    "minecraft:shepherd/2/emerald_red_wool",
    "minecraft:shepherd/2/emerald_black_wool",
    "minecraft:shepherd/2/emerald_white_carpet",
    "minecraft:shepherd/2/emerald_orange_carpet",
    "minecraft:shepherd/2/emerald_magenta_carpet",
    "minecraft:shepherd/2/emerald_blue_carpet",
    "minecraft:shepherd/2/emerald_light_blue_carpet",
    "minecraft:shepherd/2/emerald_yellow_carpet",
    "minecraft:shepherd/2/emerald_lime_carpet",
    "minecraft:shepherd/2/emerald_pink_carpet",
    "minecraft:shepherd/2/emerald_gray_carpet",
    "minecraft:shepherd/2/emerald_light_gray_carpet",
    "minecraft:shepherd/2/emerald_cyan_carpet",
    "minecraft:shepherd/2/emerald_purple_carpet",
    "minecraft:shepherd/2/emerald_brown_carpet",
    "minecraft:shepherd/2/emerald_green_carpet",
    "minecraft:shepherd/2/emerald_red_carpet",
    "minecraft:shepherd/2/emerald_black_carpet",
};
#define POOL_SIZE_shepherd_L2 37

static const char* pool_shepherd_L3[] = {
    "minecraft:shepherd/3/yellow_dye_emerald",
    "minecraft:shepherd/3/light_gray_dye_emerald",
    "minecraft:shepherd/3/orange_dye_emerald",
    "minecraft:shepherd/3/red_dye_emerald",
    "minecraft:shepherd/3/pink_dye_emerald",
    "minecraft:shepherd/3/emerald_white_bed",
    "minecraft:shepherd/3/emerald_orange_bed",
    "minecraft:shepherd/3/emerald_magenta_bed",
    "minecraft:shepherd/3/emerald_blue_bed",
    "minecraft:shepherd/3/emerald_light_blue_bed",
    "minecraft:shepherd/3/emerald_yellow_bed",
    "minecraft:shepherd/3/emerald_lime_bed",
    "minecraft:shepherd/3/emerald_pink_bed",
    "minecraft:shepherd/3/emerald_gray_bed",
    "minecraft:shepherd/3/emerald_light_gray_bed",
    "minecraft:shepherd/3/emerald_cyan_bed",
    "minecraft:shepherd/3/emerald_purple_bed",
    "minecraft:shepherd/3/emerald_brown_bed",
    "minecraft:shepherd/3/emerald_green_bed",
    "minecraft:shepherd/3/emerald_red_bed",
    "minecraft:shepherd/3/emerald_black_bed",
};
#define POOL_SIZE_shepherd_L3 21

static const char* pool_shepherd_L4[] = {
    "minecraft:shepherd/4/brown_dye_emerald",
    "minecraft:shepherd/4/purple_dye_emerald",
    "minecraft:shepherd/4/blue_dye_emerald",
    "minecraft:shepherd/4/green_dye_emerald",
    "minecraft:shepherd/4/magenta_dye_emerald",
    "minecraft:shepherd/4/cyan_dye_emerald",
    "minecraft:shepherd/4/emerald_white_banner",
    "minecraft:shepherd/4/emerald_orange_banner",
    "minecraft:shepherd/4/emerald_magenta_banner",
    "minecraft:shepherd/4/emerald_blue_banner",
    "minecraft:shepherd/4/emerald_light_blue_banner",
    "minecraft:shepherd/4/emerald_yellow_banner",
    "minecraft:shepherd/4/emerald_lime_banner",
    "minecraft:shepherd/4/emerald_pink_banner",
    "minecraft:shepherd/4/emerald_gray_banner",
    "minecraft:shepherd/4/emerald_light_gray_banner",
    "minecraft:shepherd/4/emerald_cyan_banner",
    "minecraft:shepherd/4/emerald_purple_banner",
    "minecraft:shepherd/4/emerald_brown_banner",
    "minecraft:shepherd/4/emerald_green_banner",
    "minecraft:shepherd/4/emerald_red_banner",
    "minecraft:shepherd/4/emerald_black_banner",
};
#define POOL_SIZE_shepherd_L4 22

static const char* pool_shepherd_L5[] = {
    "minecraft:shepherd/5/emerald_painting",
};
#define POOL_SIZE_shepherd_L5 1

static const char* pool_toolsmith_L1[] = {
    "minecraft:smith/1/coal_emerald",
    "minecraft:toolsmith/1/emerald_stone_axe",
    "minecraft:toolsmith/1/emerald_stone_shovel",
    "minecraft:toolsmith/1/emerald_stone_pickaxe",
    "minecraft:toolsmith/1/emerald_stone_hoe",
};
#define POOL_SIZE_toolsmith_L1 5

static const char* pool_toolsmith_L2[] = {
    "minecraft:smith/2/iron_ingot_emerald",
    "minecraft:smith/2/emerald_bell",
};
#define POOL_SIZE_toolsmith_L2 2

static const char* pool_toolsmith_L3[] = {
    "minecraft:toolsmith/3/flint_emerald",
    "minecraft:toolsmith/3/emerald_enchanted_iron_axe",
    "minecraft:toolsmith/3/emerald_enchanted_iron_shovel",
    "minecraft:toolsmith/3/emerald_enchanted_iron_pickaxe",
    "minecraft:toolsmith/3/emerald_diamond_hoe",
};
#define POOL_SIZE_toolsmith_L3 5

static const char* pool_toolsmith_L4[] = {
    "minecraft:toolsmith/4/emerald_enchanted_diamond_axe",
    "minecraft:toolsmith/4/emerald_enchanted_diamond_shovel",
    "minecraft:toolsmith/4/diamond_emerald",
};
#define POOL_SIZE_toolsmith_L4 3

static const char* pool_toolsmith_L5[] = {
    "minecraft:toolsmith/5/emerald_enchanted_diamond_pickaxe",
};
#define POOL_SIZE_toolsmith_L5 1

static const char* pool_weaponsmith_L1[] = {
    "minecraft:smith/1/coal_emerald",
    "minecraft:weaponsmith/1/emerald_iron_axe",
    "minecraft:weaponsmith/1/emerald_enchanted_iron_sword",
};
#define POOL_SIZE_weaponsmith_L1 3

static const char* pool_weaponsmith_L2[] = {
    "minecraft:smith/2/iron_ingot_emerald",
    "minecraft:smith/2/emerald_bell",
};
#define POOL_SIZE_weaponsmith_L2 2

static const char* pool_weaponsmith_L3[] = {
    "minecraft:weaponsmith/3/flint_emerald",
};
#define POOL_SIZE_weaponsmith_L3 1

static const char* pool_weaponsmith_L4[] = {
    "minecraft:weaponsmith/4/emerald_enchanted_diamond_axe",
    "minecraft:weaponsmith/4/diamond_emerald",
};
#define POOL_SIZE_weaponsmith_L4 2

static const char* pool_weaponsmith_L5[] = {
    "minecraft:weaponsmith/5/emerald_enchanted_diamond_sword",
};
#define POOL_SIZE_weaponsmith_L5 1

typedef struct {
    const char** pool;
    int pool_size;
    int amount;
    int ench_book_indices[4];
    int ench_equip_indices[4];
} LevelData;

static LevelData levels_armorer[] = {
    {pool_armorer_L1, POOL_SIZE_armorer_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_armorer_L2, POOL_SIZE_armorer_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_armorer_L3, POOL_SIZE_armorer_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_armorer_L4, POOL_SIZE_armorer_L4, 2, {-1,-1,-1,-1}, {0,1,-1,-1}},
    {pool_armorer_L5, POOL_SIZE_armorer_L5, 2, {-1,-1,-1,-1}, {0,1,-1,-1}},
};

static LevelData levels_butcher[] = {
    {pool_butcher_L1, POOL_SIZE_butcher_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_butcher_L2, POOL_SIZE_butcher_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_butcher_L3, POOL_SIZE_butcher_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_butcher_L4, POOL_SIZE_butcher_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_butcher_L5, POOL_SIZE_butcher_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_cartographer[] = {
    {pool_cartographer_L1, POOL_SIZE_cartographer_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cartographer_L2, POOL_SIZE_cartographer_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cartographer_L3, POOL_SIZE_cartographer_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cartographer_L4, POOL_SIZE_cartographer_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cartographer_L5, POOL_SIZE_cartographer_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_cleric[] = {
    {pool_cleric_L1, POOL_SIZE_cleric_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cleric_L2, POOL_SIZE_cleric_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cleric_L3, POOL_SIZE_cleric_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cleric_L4, POOL_SIZE_cleric_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_cleric_L5, POOL_SIZE_cleric_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_farmer[] = {
    {pool_farmer_L1, POOL_SIZE_farmer_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_farmer_L2, POOL_SIZE_farmer_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_farmer_L3, POOL_SIZE_farmer_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_farmer_L4, POOL_SIZE_farmer_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_farmer_L5, POOL_SIZE_farmer_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_fisherman[] = {
    {pool_fisherman_L1, POOL_SIZE_fisherman_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_fisherman_L2, POOL_SIZE_fisherman_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_fisherman_L3, POOL_SIZE_fisherman_L3, 2, {-1,-1,-1,-1}, {1,-1,-1,-1}},
    {pool_fisherman_L4, POOL_SIZE_fisherman_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_fisherman_L5, POOL_SIZE_fisherman_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_fletcher[] = {
    {pool_fletcher_L1, POOL_SIZE_fletcher_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_fletcher_L2, POOL_SIZE_fletcher_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_fletcher_L3, POOL_SIZE_fletcher_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_fletcher_L4, POOL_SIZE_fletcher_L4, 2, {-1,-1,-1,-1}, {1,-1,-1,-1}},
    {pool_fletcher_L5, POOL_SIZE_fletcher_L5, 2, {-1,-1,-1,-1}, {1,-1,-1,-1}},
};

static LevelData levels_leatherworker[] = {
    {pool_leatherworker_L1, POOL_SIZE_leatherworker_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_leatherworker_L2, POOL_SIZE_leatherworker_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_leatherworker_L3, POOL_SIZE_leatherworker_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_leatherworker_L4, POOL_SIZE_leatherworker_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_leatherworker_L5, POOL_SIZE_leatherworker_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_librarian[] = {
    {pool_librarian_L1, POOL_SIZE_librarian_L1, 2, {1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_librarian_L2, POOL_SIZE_librarian_L2, 2, {1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_librarian_L3, POOL_SIZE_librarian_L3, 2, {1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_librarian_L4, POOL_SIZE_librarian_L4, 2, {1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_librarian_L5, POOL_SIZE_librarian_L5, 3, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_mason[] = {
    {pool_mason_L1, POOL_SIZE_mason_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_mason_L2, POOL_SIZE_mason_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_mason_L3, POOL_SIZE_mason_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_mason_L4, POOL_SIZE_mason_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_mason_L5, POOL_SIZE_mason_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_shepherd[] = {
    {pool_shepherd_L1, POOL_SIZE_shepherd_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_shepherd_L2, POOL_SIZE_shepherd_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_shepherd_L3, POOL_SIZE_shepherd_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_shepherd_L4, POOL_SIZE_shepherd_L4, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_shepherd_L5, POOL_SIZE_shepherd_L5, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
};

static LevelData levels_toolsmith[] = {
    {pool_toolsmith_L1, POOL_SIZE_toolsmith_L1, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_toolsmith_L2, POOL_SIZE_toolsmith_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_toolsmith_L3, POOL_SIZE_toolsmith_L3, 2, {-1,-1,-1,-1}, {1,2,3,-1}},
    {pool_toolsmith_L4, POOL_SIZE_toolsmith_L4, 2, {-1,-1,-1,-1}, {0,1,-1,-1}},
    {pool_toolsmith_L5, POOL_SIZE_toolsmith_L5, 2, {-1,-1,-1,-1}, {0,-1,-1,-1}},
};

static LevelData levels_weaponsmith[] = {
    {pool_weaponsmith_L1, POOL_SIZE_weaponsmith_L1, 2, {-1,-1,-1,-1}, {2,-1,-1,-1}},
    {pool_weaponsmith_L2, POOL_SIZE_weaponsmith_L2, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_weaponsmith_L3, POOL_SIZE_weaponsmith_L3, 2, {-1,-1,-1,-1}, {-1,-1,-1,-1}},
    {pool_weaponsmith_L4, POOL_SIZE_weaponsmith_L4, 2, {-1,-1,-1,-1}, {0,-1,-1,-1}},
    {pool_weaponsmith_L5, POOL_SIZE_weaponsmith_L5, 2, {-1,-1,-1,-1}, {0,-1,-1,-1}},
};

LevelData* ALL_LEVEL_DATA[13] = {
    levels_armorer,
    levels_butcher,
    levels_cartographer,
    levels_cleric,
    levels_farmer,
    levels_fisherman,
    levels_fletcher,
    levels_leatherworker,
    levels_librarian,
    levels_mason,
    levels_shepherd,
    levels_toolsmith,
    levels_weaponsmith,
};

/* Enchanted equipment parameters: {item, level_min, level_max} */
typedef struct { const char* entry; const char* item; int level_min; int level_max; } EquipParam;
EquipParam EQUIP_PARAMS[] = {
    {"minecraft:armorer/4/emerald_enchanted_diamond_leggings", "minecraft:diamond_leggings", 5, 19},
    {"minecraft:armorer/4/emerald_enchanted_diamond_boots", "minecraft:diamond_boots", 5, 19},
    {"minecraft:armorer/5/emerald_enchanted_diamond_helmet", "minecraft:diamond_helmet", 5, 19},
    {"minecraft:armorer/5/emerald_enchanted_diamond_chestplate", "minecraft:diamond_chestplate", 5, 19},
    {"minecraft:fisherman/3/emerald_enchanted_fishing_rod", "minecraft:fishing_rod", 5, 19},
    {"minecraft:fletcher/4/emerald_enchanted_bow", "minecraft:bow", 5, 19},
    {"minecraft:fletcher/5/emerald_enchanted_crossbow", "minecraft:crossbow", 5, 19},
    {"minecraft:toolsmith/3/emerald_enchanted_iron_axe", "minecraft:iron_axe", 5, 19},
    {"minecraft:toolsmith/3/emerald_enchanted_iron_shovel", "minecraft:iron_shovel", 5, 19},
    {"minecraft:toolsmith/3/emerald_enchanted_iron_pickaxe", "minecraft:iron_pickaxe", 5, 19},
    {"minecraft:toolsmith/4/emerald_enchanted_diamond_axe", "minecraft:diamond_axe", 5, 19},
    {"minecraft:toolsmith/4/emerald_enchanted_diamond_shovel", "minecraft:diamond_shovel", 5, 19},
    {"minecraft:toolsmith/5/emerald_enchanted_diamond_pickaxe", "minecraft:diamond_pickaxe", 5, 19},
    {"minecraft:weaponsmith/1/emerald_enchanted_iron_sword", "minecraft:iron_sword", 5, 19},
    {"minecraft:weaponsmith/4/emerald_enchanted_diamond_axe", "minecraft:diamond_axe", 5, 19},
    {"minecraft:weaponsmith/5/emerald_enchanted_diamond_sword", "minecraft:diamond_sword", 5, 19},
    {NULL, NULL, 0, 0}
};

static int get_item_enchantability(const char* item) {
    if (strcmp(item, "minecraft:iron_axe") == 0) return 14;
    if (strcmp(item, "minecraft:iron_shovel") == 0) return 14;
    if (strcmp(item, "minecraft:iron_pickaxe") == 0) return 14;
    if (strcmp(item, "minecraft:iron_sword") == 0) return 14;
    if (strcmp(item, "minecraft:iron_hoe") == 0) return 14;
    if (strcmp(item, "minecraft:diamond_axe") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_shovel") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_pickaxe") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_sword") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_hoe") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_helmet") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_chestplate") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_leggings") == 0) return 10;
    if (strcmp(item, "minecraft:diamond_boots") == 0) return 10;
    if (strcmp(item, "minecraft:iron_helmet") == 0) return 9;
    if (strcmp(item, "minecraft:iron_chestplate") == 0) return 9;
    if (strcmp(item, "minecraft:iron_leggings") == 0) return 9;
    if (strcmp(item, "minecraft:iron_boots") == 0) return 9;
    if (strcmp(item, "minecraft:fishing_rod") == 0) return 1;
    if (strcmp(item, "minecraft:bow") == 0) return 1;
    if (strcmp(item, "minecraft:crossbow") == 0) return 1;
    if (strcmp(item, "minecraft:leather_helmet") == 0) return 15;
    if (strcmp(item, "minecraft:leather_chestplate") == 0) return 15;
    if (strcmp(item, "minecraft:leather_leggings") == 0) return 15;
    if (strcmp(item, "minecraft:leather_boots") == 0) return 15;
    return 10;
}

static int get_enchant_weight(const char* name) {
    if (strcmp(name, "protection") == 0) return 10;
    if (strcmp(name, "fire_protection") == 0) return 5;
    if (strcmp(name, "feather_falling") == 0) return 5;
    if (strcmp(name, "blast_protection") == 0) return 2;
    if (strcmp(name, "projectile_protection") == 0) return 5;
    if (strcmp(name, "respiration") == 0) return 2;
    if (strcmp(name, "aqua_affinity") == 0) return 2;
    if (strcmp(name, "thorns") == 0) return 1;
    if (strcmp(name, "depth_strider") == 0) return 2;
    if (strcmp(name, "sharpness") == 0) return 10;
    if (strcmp(name, "smite") == 0) return 5;
    if (strcmp(name, "bane_of_arthropods") == 0) return 5;
    if (strcmp(name, "knockback") == 0) return 5;
    if (strcmp(name, "fire_aspect") == 0) return 2;
    if (strcmp(name, "looting") == 0) return 2;
    if (strcmp(name, "sweeping_edge") == 0) return 2;
    if (strcmp(name, "efficiency") == 0) return 10;
    if (strcmp(name, "silk_touch") == 0) return 1;
    if (strcmp(name, "unbreaking") == 0) return 5;
    if (strcmp(name, "fortune") == 0) return 2;
    if (strcmp(name, "power") == 0) return 10;
    if (strcmp(name, "punch") == 0) return 2;
    if (strcmp(name, "flame") == 0) return 2;
    if (strcmp(name, "infinity") == 0) return 1;
    if (strcmp(name, "luck_of_the_sea") == 0) return 2;
    if (strcmp(name, "lure") == 0) return 2;
    if (strcmp(name, "loyalty") == 0) return 5;
    if (strcmp(name, "impaling") == 0) return 2;
    if (strcmp(name, "riptide") == 0) return 2;
    if (strcmp(name, "channeling") == 0) return 1;
    if (strcmp(name, "multishot") == 0) return 2;
    if (strcmp(name, "quick_charge") == 0) return 5;
    if (strcmp(name, "piercing") == 0) return 10;
    if (strcmp(name, "density") == 0) return 5;
    if (strcmp(name, "breach") == 0) return 2;
    if (strcmp(name, "lunge") == 0) return 2;
    return 1;
}

static int get_equip_ench_max(const char* name) {
    if (strcmp(name, "protection") == 0) return 4;
    if (strcmp(name, "fire_protection") == 0) return 4;
    if (strcmp(name, "feather_falling") == 0) return 4;
    if (strcmp(name, "blast_protection") == 0) return 4;
    if (strcmp(name, "projectile_protection") == 0) return 4;
    if (strcmp(name, "thorns") == 0) return 3;
    if (strcmp(name, "sharpness") == 0) return 5;
    if (strcmp(name, "smite") == 0) return 5;
    if (strcmp(name, "bane_of_arthropods") == 0) return 5;
    if (strcmp(name, "knockback") == 0) return 2;
    if (strcmp(name, "fire_aspect") == 0) return 2;
    if (strcmp(name, "looting") == 0) return 3;
    if (strcmp(name, "efficiency") == 0) return 5;
    if (strcmp(name, "silk_touch") == 0) return 1;
    if (strcmp(name, "unbreaking") == 0) return 3;
    if (strcmp(name, "fortune") == 0) return 3;
    if (strcmp(name, "power") == 0) return 5;
    if (strcmp(name, "punch") == 0) return 2;
    if (strcmp(name, "flame") == 0) return 1;
    if (strcmp(name, "infinity") == 0) return 1;
    if (strcmp(name, "loyalty") == 0) return 3;
    if (strcmp(name, "impaling") == 0) return 5;
    if (strcmp(name, "riptide") == 0) return 3;
    if (strcmp(name, "channeling") == 0) return 1;
    if (strcmp(name, "multishot") == 0) return 1;
    if (strcmp(name, "quick_charge") == 0) return 3;
    if (strcmp(name, "piercing") == 0) return 4;
    if (strcmp(name, "density") == 0) return 5;
    if (strcmp(name, "breach") == 0) return 4;
    if (strcmp(name, "lunge") == 0) return 3;
    if (strcmp(name, "sweeping_edge") == 0) return 3;
    if (strcmp(name, "depth_strider") == 0) return 3;
    return 1;
}

static int is_ench_compatible_with_item(const char* ench, const char* item) {
    if (strcmp(item, "minecraft:iron_sword") == 0) {
        if (strcmp(ench, "looting") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "bane_of_arthropods") == 0) return 1;
        if (strcmp(ench, "knockback") == 0) return 1;
        if (strcmp(ench, "fire_aspect") == 0) return 1;
        if (strcmp(ench, "sharpness") == 0) return 1;
        if (strcmp(ench, "smite") == 0) return 1;
        if (strcmp(ench, "sweeping_edge") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_sword") == 0) {
        if (strcmp(ench, "looting") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "bane_of_arthropods") == 0) return 1;
        if (strcmp(ench, "knockback") == 0) return 1;
        if (strcmp(ench, "fire_aspect") == 0) return 1;
        if (strcmp(ench, "sharpness") == 0) return 1;
        if (strcmp(ench, "smite") == 0) return 1;
        if (strcmp(ench, "sweeping_edge") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:iron_axe") == 0) {
        if (strcmp(ench, "sharpness") == 0) return 1;
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "smite") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "bane_of_arthropods") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_axe") == 0) {
        if (strcmp(ench, "sharpness") == 0) return 1;
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "smite") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "bane_of_arthropods") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:stone_axe") == 0) {
        if (strcmp(ench, "sharpness") == 0) return 1;
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "smite") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "bane_of_arthropods") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:iron_pickaxe") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_pickaxe") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:stone_pickaxe") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:iron_shovel") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_shovel") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:stone_shovel") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:stone_hoe") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_hoe") == 0) {
        if (strcmp(ench, "silk_touch") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "fortune") == 0) return 1;
        if (strcmp(ench, "efficiency") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_helmet") == 0) {
        if (strcmp(ench, "protection") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "blast_protection") == 0) return 1;
        if (strcmp(ench, "aqua_affinity") == 0) return 1;
        if (strcmp(ench, "thorns") == 0) return 1;
        if (strcmp(ench, "fire_protection") == 0) return 1;
        if (strcmp(ench, "projectile_protection") == 0) return 1;
        if (strcmp(ench, "respiration") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_chestplate") == 0) {
        if (strcmp(ench, "protection") == 0) return 1;
        if (strcmp(ench, "thorns") == 0) return 1;
        if (strcmp(ench, "fire_protection") == 0) return 1;
        if (strcmp(ench, "projectile_protection") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "blast_protection") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_leggings") == 0) {
        if (strcmp(ench, "protection") == 0) return 1;
        if (strcmp(ench, "thorns") == 0) return 1;
        if (strcmp(ench, "fire_protection") == 0) return 1;
        if (strcmp(ench, "projectile_protection") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "blast_protection") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:diamond_boots") == 0) {
        if (strcmp(ench, "protection") == 0) return 1;
        if (strcmp(ench, "depth_strider") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        if (strcmp(ench, "blast_protection") == 0) return 1;
        if (strcmp(ench, "thorns") == 0) return 1;
        if (strcmp(ench, "feather_falling") == 0) return 1;
        if (strcmp(ench, "fire_protection") == 0) return 1;
        if (strcmp(ench, "projectile_protection") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:bow") == 0) {
        if (strcmp(ench, "power") == 0) return 1;
        if (strcmp(ench, "flame") == 0) return 1;
        if (strcmp(ench, "punch") == 0) return 1;
        if (strcmp(ench, "infinity") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:crossbow") == 0) {
        if (strcmp(ench, "piercing") == 0) return 1;
        if (strcmp(ench, "quick_charge") == 0) return 1;
        if (strcmp(ench, "multishot") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        return 0;
    }
    if (strcmp(item, "minecraft:fishing_rod") == 0) {
        if (strcmp(ench, "luck_of_the_sea") == 0) return 1;
        if (strcmp(ench, "lure") == 0) return 1;
        if (strcmp(ench, "unbreaking") == 0) return 1;
        return 0;
    }
    return 0;
}

static int are_enchants_incompatible(const char* a, const char* b) {
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "j") == 0) ||
        (strcmp(a, "j") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "j") == 0) ||
        (strcmp(a, "j") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "j") == 0) ||
        (strcmp(a, "j") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "j") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "j") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "m") == 0) ||
        (strcmp(a, "m") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "f") == 0) ||
        (strcmp(a, "f") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "b") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "b") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "f") == 0) ||
        (strcmp(a, "f") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "f") == 0) ||
        (strcmp(a, "f") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "f") == 0) ||
        (strcmp(a, "f") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "f") == 0) ||
        (strcmp(a, "f") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "f") == 0) ||
        (strcmp(a, "f") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "w") == 0) ||
        (strcmp(a, "w") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "f") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "f") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "w") == 0) ||
        (strcmp(a, "w") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "w") == 0) ||
        (strcmp(a, "w") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "w") == 0) ||
        (strcmp(a, "w") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "_") == 0) ||
        (strcmp(a, "_") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "w") == 0) ||
        (strcmp(a, "w") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "w") == 0) ||
        (strcmp(a, "w") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "_") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "_") == 0)) return 1;
    if ((strcmp(a, "w") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "w") == 0)) return 1;
    if ((strcmp(a, "w") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "w") == 0)) return 1;
    if ((strcmp(a, "w") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "w") == 0)) return 1;
    if ((strcmp(a, "w") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "w") == 0)) return 1;
    if ((strcmp(a, "w") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "w") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "k") == 0) ||
        (strcmp(a, "k") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "k") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "k") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "u") == 0) ||
        (strcmp(a, "u") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "m") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "m") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "u") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "u") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "s") == 0) ||
        (strcmp(a, "s") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "s") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "s") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "r") == 0) ||
        (strcmp(a, "r") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "c") == 0) ||
        (strcmp(a, "c") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "r") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "r") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "p") == 0) ||
        (strcmp(a, "p") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "p") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "p") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "d") == 0) ||
        (strcmp(a, "d") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "d") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "d") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "o") == 0) ||
        (strcmp(a, "o") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "o") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "o") == 0)) return 1;
    if ((strcmp(a, "y") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "y") == 0)) return 1;
    if ((strcmp(a, "y") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "y") == 0)) return 1;
    if ((strcmp(a, "y") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "y") == 0)) return 1;
    if ((strcmp(a, "y") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "y") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "t") == 0) ||
        (strcmp(a, "t") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "t") == 0 && strcmp(b, "y") == 0) ||
        (strcmp(a, "y") == 0 && strcmp(b, "t") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "h") == 0) ||
        (strcmp(a, "h") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "c") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "c") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "a") == 0) ||
        (strcmp(a, "a") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "h") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "h") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "a") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "a") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "e") == 0) ||
        (strcmp(a, "e") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "n") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "l") == 0) ||
        (strcmp(a, "l") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "e") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "e") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "i") == 0) ||
        (strcmp(a, "i") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "l") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "l") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "n") == 0) ||
        (strcmp(a, "n") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "i") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "i") == 0)) return 1;
    if ((strcmp(a, "n") == 0 && strcmp(b, "g") == 0) ||
        (strcmp(a, "g") == 0 && strcmp(b, "n") == 0)) return 1;
    return 0;
}

static const char* STEW_EFFECTS[] = {
    "night_vision",
    "jump_boost",
    "weakness",
    "blindness",
    "poison",
    "saturation",
};
static const int STEW_DURATIONS[] = {200, 200, 180, 180, 200, 6};
#define NUM_STEW_EFFECTS 6

static const char* TRADEABLE_POTION_LIST[] = {
    "wind_charged",
    "oozing",
    "infested",
    "weaving",
    "night_vision",
    "long_night_vision",
    "invisibility",
    "long_invisibility",
    "fire_resistance",
    "long_fire_resistance",
    "leaping",
    "long_leaping",
    "strong_leaping",
    "slowness",
    "long_slowness",
    "strong_slowness",
    "turtle_master",
    "long_turtle_master",
    "strong_turtle_master",
    "swiftness",
    "long_swiftness",
    "strong_swiftness",
    "water_breathing",
    "long_water_breathing",
    "healing",
    "strong_healing",
    "harming",
    "strong_harming",
    "poison",
    "long_poison",
    "strong_poison",
    "regeneration",
    "long_regeneration",
    "strong_regeneration",
    "strength",
    "long_strength",
    "strong_strength",
    "weakness",
    "long_weakness",
    "slow_falling",
    "long_slow_falling",
};
#define NUM_TRADEABLE_POTIONS 41
