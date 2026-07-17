"""
村民交易导出工具 - 数据与工具模块 (versions/src)

封装中文对照表、交易池解析、交易翻译、CSV行生成、配置读写、附魔选择弹窗。
本模块可被同目录下的 trade_export_gui.py 导入，也可独立使用。
"""
import os
import sys
import tkinter as tk
from tkinter import ttk
import json

from villager_trade_predictor import (
    ALL_TRADE_DATA,
    TRADEABLE_ENCHANTMENTS, DOUBLE_PRICE_SET,
    is_enchanted_book_entry, is_enchanted_equipment_entry,
    is_suspicious_stew_entry, is_tipped_arrow_entry,
    is_dyed_equipment_entry, ENCHANTED_EQUIPMENT_PARAMS,
    ITEM_ENCHANTMENT_COMPAT, ON_TRADED_EQUIPMENT_ENCHANTMENTS,
)

# ============================================================
# 配置文件路径
# ============================================================
CONFIG_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "export_trades_config.json")

# ============================================================
# 中文对照
# ============================================================
PROFESSION_CN = {
    "armorer": "盔甲匠", "butcher": "屠夫", "cartographer": "制图师",
    "cleric": "牧师", "farmer": "农民", "fisherman": "渔夫",
    "fletcher": "制箭师", "leatherworker": "皮匠", "librarian": "图书管理员",
    "mason": "石匠", "shepherd": "牧羊人", "toolsmith": "工具匠",
    "weaponsmith": "武器匠",
}
PROFESSION_EN = {v: k for k, v in PROFESSION_CN.items()}

ENCHANTMENT_CN = {
    "protection": "保护", "fire_protection": "火焰保护", "feather_falling": "摔落保护",
    "blast_protection": "爆炸保护", "projectile_protection": "弹射物保护",
    "respiration": "水下呼吸", "aqua_affinity": "水下速掘", "thorns": "荆棘",
    "depth_strider": "深海探索者", "sharpness": "锋利", "smite": "亡灵杀手",
    "bane_of_arthropods": "节肢杀手", "knockback": "击退", "fire_aspect": "火焰附加",
    "looting": "抢夺", "sweeping_edge": "横扫之刃", "efficiency": "效率",
    "silk_touch": "精准采集", "unbreaking": "耐久", "fortune": "时运",
    "power": "力量", "punch": "冲击", "flame": "火矢", "infinity": "无限",
    "luck_of_the_sea": "海之眷顾", "lure": "饵钓", "loyalty": "忠诚",
    "impaling": "穿刺", "riptide": "激流", "channeling": "引雷",
    "multishot": "多重射击", "quick_charge": "快速装填", "piercing": "穿透",
    "density": "致密", "breach": "破甲", "lunge": "突进",
    "binding_curse": "绑定诅咒", "vanishing_curse": "消失诅咒",
    "swift_sneak": "迅捷潜行", "soul_speed": "灵魂疾行",
    "frost_walker": "冰霜行者", "mending": "经验修补", "wind_burst": "风爆",
}
ENCHANTMENT_EN = {v: k for k, v in ENCHANTMENT_CN.items()}

LEVEL_NAMES = {1: "新手", 2: "学徒", 3: "老手", 4: "专家", 5: "大师"}

STEW_CN = {
    "night_vision": "夜视", "jump_boost": "跳跃提升", "weakness": "虚弱",
    "blindness": "失明", "poison": "中毒", "saturation": "饱和",
}
STEW_EN = {v: k for k, v in STEW_CN.items()}

POTION_CN = {
    "wind_charged": "风弹", "oozing": "渗浆", "infested": "虫蚀", "weaving": "织网",
    "night_vision": "夜视", "long_night_vision": "夜视(延长)",
    "invisibility": "隐身", "long_invisibility": "隐身(延长)",
    "fire_resistance": "抗火", "long_fire_resistance": "抗火(延长)",
    "leaping": "跳跃", "long_leaping": "跳跃(延长)", "strong_leaping": "跳跃II",
    "slowness": "迟缓", "long_slowness": "迟缓(延长)", "strong_slowness": "迟缓IV",
    "turtle_master": "神龟", "long_turtle_master": "神龟(延长)", "strong_turtle_master": "神龟II",
    "swiftness": "迅捷", "long_swiftness": "迅捷(延长)", "strong_swiftness": "迅捷II",
    "water_breathing": "水肺", "long_water_breathing": "水肺(延长)",
    "healing": "治疗", "strong_healing": "治疗II",
    "harming": "伤害", "strong_harming": "伤害II",
    "long_poison": "剧毒(延长)", "strong_poison": "剧毒II",
    "regeneration": "再生", "long_regeneration": "再生(延长)", "strong_regeneration": "再生II",
    "strength": "力量", "long_strength": "力量(延长)", "strong_strength": "力量II",
    "weakness": "虚弱", "long_weakness": "虚弱(延长)",
    "slow_falling": "缓降", "long_slow_falling": "缓降(延长)",
}
POTION_EN = {v: k for k, v in POTION_CN.items()}

DYE_CN = {
    "white": "白", "orange": "橙", "magenta": "品红", "light_blue": "淡蓝",
    "yellow": "黄", "lime": "黄绿", "pink": "粉", "gray": "灰",
    "light_gray": "淡灰", "cyan": "青", "purple": "紫", "blue": "蓝",
    "brown": "棕", "green": "绿", "red": "红", "black": "黑",
}

TRADE_TYPE_CN = ["附魔书", "附魔装备", "迷之炖菜", "药箭", "染色装备", "普通交易"]


# ============================================================
# 交易池条目解析
# ============================================================
def parse_pool_entry(entry: str) -> dict:
    """将池中条目解析为 {label, type, type_cn, data}。"""
    suffix = entry.rsplit("/", 1)[-1]

    if is_enchanted_book_entry(entry):
        return {"label": "附魔书", "type": "enchanted_book", "type_cn": "附魔书",
                "data": {"entry": entry}}
    elif is_enchanted_equipment_entry(entry):
        params = ENCHANTED_EQUIPMENT_PARAMS.get(entry)
        if params:
            item_name = params[0].replace("minecraft:", "")
            return {"label": f"附魔装备 ({item_name})", "type": "enchanted_equipment",
                    "type_cn": "附魔装备", "data": {"entry": entry, "item": params[0]}}
        return {"label": f"附魔装备 ({suffix})", "type": "enchanted_equipment",
                "type_cn": "附魔装备", "data": {"entry": entry}}
    elif is_suspicious_stew_entry(entry):
        return {"label": "迷之炖菜", "type": "suspicious_stew", "type_cn": "迷之炖菜",
                "data": {"entry": entry}}
    elif is_tipped_arrow_entry(entry):
        return {"label": "药箭", "type": "tipped_arrow", "type_cn": "药箭",
                "data": {"entry": entry}}
    elif is_dyed_equipment_entry(entry):
        item_hint = "leather_horse_armor" if "horse" in suffix else "leather_armor"
        return {"label": f"染色装备 ({item_hint})", "type": "dyed_equipment",
                "type_cn": "染色装备", "data": {"entry": entry}}
    else:
        return {"label": suffix, "type": "other", "type_cn": "普通交易",
                "data": {"entry": entry}}


def get_pool_entry_list(prof: str, level: int, variant: str | None = None) -> list[dict]:
    """获取某职业等级的池条目列表（含类型信息）。"""
    data = ALL_TRADE_DATA.get(prof, {}).get(level, {})
    if not data or "pool" not in data:
        return []

    pool = data["pool"]
    # 应用variant过滤（制图师、牧羊人、皮匠）
    for pname in ("cartographer", "shepherd", "leatherworker"):
        if prof == pname and "variants" in data:
            vk = variant or "plains"
            vdata = data["variants"].get(vk)
            if vdata:
                pool = [pool[i] for i in vdata.get("indices", range(len(pool)))]
            break

    return [parse_pool_entry(e) for e in pool]


# ============================================================
# 配置读写
# ============================================================
def load_config():
    if os.path.exists(CONFIG_FILE):
        try:
            with open(CONFIG_FILE, "r", encoding="utf-8") as f:
                return json.load(f)
        except Exception:
            pass
    return {"last_seed": "", "history": [], "last_prof": "图书管理员", "last_level": "1-新手"}


def save_config(config):
    try:
        with open(CONFIG_FILE, "w", encoding="utf-8") as f:
            json.dump(config, f, indent=2, ensure_ascii=False)
    except Exception:
        pass


# ============================================================
# 交易翻译
# ============================================================
def translate_trade(t: dict) -> str:
    """将单条交易dict转为可读的中文字符串。"""
    tp = t.get("type", "other")
    if tp == "enchanted_book":
        ench_cn = ENCHANTMENT_CN.get(t["enchantment"], t["enchantment"])
        treasure = " [宝藏]" if t.get("is_treasure") else ""
        return f"附魔书: {ench_cn} {t['level']} ({t['final_cost']}E){treasure}"
    elif tp == "enchanted_equipment":
        item = t.get("item", "?").replace("minecraft:", "")
        enchs = ", ".join(f"{ENCHANTMENT_CN.get(n, n)} {lv}"
                          for n, lv in t.get("enchantments", []))
        return f"附魔装备: {item} [{enchs}] ({t.get('final_cost', '?')}E)"
    elif tp == "suspicious_stew":
        eff = STEW_CN.get(t.get("effect", "?"), t.get("effect", "?"))
        dur = t.get("duration_ticks", 0) / 20
        return f"迷之炖菜: {eff} ({dur:.0f}秒)"
    elif tp == "tipped_arrow":
        pot = POTION_CN.get(t.get("potion", "?"), t.get("potion", "?"))
        return f"药箭: {pot}"
    elif tp == "dyed_equipment":
        dyes = ", ".join(DYE_CN.get(d, d) for d in t.get("dyes", []))
        return f"染色装备: {dyes}"
    else:
        return t.get("entry", "?").rsplit("/", 1)[-1].replace("_", " ")


def trade_to_csv_row(t: dict, offset: int, level: int) -> list:
    """将单条交易dict转为CSV行（9列）。"""
    tp = t.get("type", "other")
    if tp == "enchanted_book":
        return [
            offset, level,
            t.get("entry", "").rsplit("/", 1)[-1],
            "附魔书", ENCHANTMENT_CN.get(t["enchantment"], t["enchantment"]),
            t["enchantment"], t["level"], t["final_cost"],
            "是" if t.get("is_treasure") else "否",
        ]
    elif tp == "enchanted_equipment":
        item = t.get("item", "?").replace("minecraft:", "")
        enchs = "; ".join(f"{ENCHANTMENT_CN.get(n, n)} {lv}"
                          for n, lv in t.get("enchantments", []))
        return [
            offset, level,
            t.get("entry", "").rsplit("/", 1)[-1],
            "附魔装备", item, enchs, "", t.get("final_cost", ""),
            "",
        ]
    elif tp == "suspicious_stew":
        eff = STEW_CN.get(t.get("effect", "?"), t.get("effect", "?"))
        return [
            offset, level,
            t.get("entry", "").rsplit("/", 1)[-1],
            "迷之炖菜", eff, str(t.get("duration_ticks", 0) / 20) + "秒",
            "", "", "",
        ]
    elif tp == "tipped_arrow":
        pot = POTION_CN.get(t.get("potion", "?"), t.get("potion", "?"))
        return [
            offset, level,
            t.get("entry", "").rsplit("/", 1)[-1],
            "药箭", pot, "", "", "", "",
        ]
    elif tp == "dyed_equipment":
        dyes = "/".join(DYE_CN.get(d, d) for d in t.get("dyes", []))
        return [
            offset, level,
            t.get("entry", "").rsplit("/", 1)[-1],
            "染色装备", dyes, str(t.get("dye_count", "")),
            "", "", "",
        ]
    else:
        return [
            offset, level,
            t.get("entry", "").rsplit("/", 1)[-1],
            "普通", "", "", "", "", "",
        ]


# ============================================================
# 附魔选择弹窗
# ============================================================
class EnchantmentSelector(tk.Toplevel):
    """附魔选择弹窗：搜索、等级选择、价格预览。"""

    def __init__(self, parent, title="选择附魔"):
        super().__init__(parent)
        self.title(title)
        self.geometry("420x480")
        self.resizable(False, False)
        self.result = None
        self.transient(parent)
        self.grab_set()

        ttk.Label(self, text="搜索:").pack(padx=5, pady=(10, 0))
        self.search_var = tk.StringVar()
        self.search_var.trace_add("write", lambda *a: self._filter())
        ttk.Entry(self, textvariable=self.search_var, width=40).pack(padx=5)

        list_frame = ttk.Frame(self)
        list_frame.pack(fill="both", expand=True, padx=5, pady=5)
        self.listbox = tk.Listbox(list_frame, height=14, font=("Microsoft YaHei", 10))
        scrollbar = ttk.Scrollbar(list_frame, orient="vertical", command=self.listbox.yview)
        self.listbox.configure(yscrollcommand=scrollbar.set)
        self.listbox.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")
        self.listbox.bind("<Double-Button-1>", lambda e: self._confirm())

        level_frame = ttk.Frame(self)
        level_frame.pack(fill="x", padx=5, pady=5)
        ttk.Label(level_frame, text="等级:").pack(side="left")
        self.level_var = tk.StringVar()
        self.level_combo = ttk.Combobox(level_frame, textvariable=self.level_var,
                                        width=6, state="readonly")
        self.level_combo.pack(side="left", padx=5)
        self.level_combo.bind("<<ComboboxSelected>>", self._on_level)

        self.price_label = ttk.Label(level_frame, text="")
        self.price_label.pack(side="left", padx=10)

        btn_frame = ttk.Frame(self)
        btn_frame.pack(fill="x", pady=10)
        ttk.Button(btn_frame, text="确定", command=self._confirm).pack(side="right", padx=10)
        ttk.Button(btn_frame, text="取消", command=self._cancel).pack(side="right")

        self._populate()

    def _populate(self):
        self.all_data = []
        for name, max_lv in TRADEABLE_ENCHANTMENTS:
            cn = ENCHANTMENT_CN.get(name, name)
            treasure = " [宝藏]" if name in DOUBLE_PRICE_SET else ""
            self.all_data.append((name, max_lv, cn, treasure))
        self._filter()

    def _filter(self):
        s = self.search_var.get().lower().strip()
        self.listbox.delete(0, "end")
        self.listbox._idx_map = {}
        for name, max_lv, cn, treasure in self.all_data:
            if s in cn or s in name:
                idx = self.listbox.size()
                self.listbox.insert("end", f"{cn} (1-{max_lv}){treasure}")
                self.listbox._idx_map[idx] = (name, max_lv)

    def _on_level(self, event=None):
        sel = self.listbox.curselection()
        if not sel:
            return
        data = self.listbox._idx_map.get(sel[0])
        if not data:
            return
        name, _max_lv = data
        try:
            lv = int(self.level_var.get())
        except ValueError:
            return
        is_treasure = name in DOUBLE_PRICE_SET
        base_min = 2 + 3 * lv
        base_max = 6 + 13 * lv
        if is_treasure:
            base_min *= 2
            base_max *= 2
        self.price_label.config(text=f"价格: {base_min}~{base_max}")

    def _confirm(self):
        sel = self.listbox.curselection()
        if not sel:
            return
        data = self.listbox._idx_map.get(sel[0])
        if not data:
            return
        try:
            lv = int(self.level_var.get())
        except ValueError:
            return
        self.result = (data[0], lv)
        self.destroy()

    def _cancel(self):
        self.result = None
        self.destroy()


# ============================================================
# 附魔装备选择弹窗（穿梭框）
# ============================================================
class EquipmentEnchantSelector(tk.Toplevel):
    """附魔装备专用的附魔选择弹窗，左侧可用附魔、右侧已选附魔，穿梭框交互。"""
    def __init__(self, parent, equipment_item: str, title="选择装备附魔"):
        super().__init__(parent)
        self.title(title)
        self.geometry("560x480")
        self.resizable(False, False)
        self.result = None          # list of (enchantment_name, level) tuples
        self.transient(parent)
        self.grab_set()

        self.equipment_item = equipment_item
        compat_set = ITEM_ENCHANTMENT_COMPAT.get(equipment_item, set())
        # Build level map from ON_TRADED_EQUIPMENT_ENCHANTMENTS
        self._max_level_map = {name: max_lv for name, max_lv in ON_TRADED_EQUIPMENT_ENCHANTMENTS}

        # Filter: only compatible enchants that are in ON_TRADED_EQUIPMENT_ENCHANTMENTS
        self._available_enchants = []
        for name, max_lv in ON_TRADED_EQUIPMENT_ENCHANTMENTS:
            if name in compat_set:
                cn = ENCHANTMENT_CN.get(name, name)
                self._available_enchants.append((name, max_lv, cn))

        # — 提示标签 —
        ttk.Label(self, text=f"装备: {equipment_item.replace('minecraft:', '')}",
                  font=("", 9, "bold")).pack(pady=(8, 2))
        ttk.Label(self, text="从左侧可用附魔中选择并移动到右侧已选区",
                  foreground="gray", font=("", 8)).pack()

        # — 穿梭区域 —
        shuttle_frame = ttk.Frame(self)
        shuttle_frame.pack(fill="both", expand=True, padx=10, pady=5)

        # 左侧：可用附魔
        left_frame = ttk.LabelFrame(shuttle_frame, text="可用附魔", padding=3)
        left_frame.pack(side="left", fill="both", expand=True)
        self.avail_listbox = tk.Listbox(left_frame, font=("Microsoft YaHei", 10),
                                        selectmode="extended")
        self.avail_listbox.pack(fill="both", expand=True)
        self._populate_avail()

        # 中键：>  <
        btn_frame = ttk.Frame(shuttle_frame)
        btn_frame.pack(side="left", padx=8)
        ttk.Button(btn_frame, text=">", width=4,
                   command=self._move_to_selected).pack(pady=2)
        ttk.Button(btn_frame, text="<", width=4,
                   command=self._move_to_avail).pack(pady=2)

        # 右侧：已选附魔
        self._right_frame = ttk.LabelFrame(shuttle_frame, text="已选附魔", padding=3)
        self._right_frame.pack(side="right", fill="both", expand=True)

        # 右侧内容用 Canvas + Scrollbar（因为每个附魔有 Combobox）
        self._sel_canvas = tk.Canvas(self._right_frame, width=200)
        self._sel_scrollbar = ttk.Scrollbar(self._right_frame, orient="vertical",
                                            command=self._sel_canvas.yview)
        self._sel_inner = ttk.Frame(self._sel_canvas)
        self._sel_inner.bind("<Configure>",
                             lambda e: self._sel_canvas.configure(scrollregion=self._sel_canvas.bbox("all")))
        self._sel_window = self._sel_canvas.create_window((0, 0), window=self._sel_inner, anchor="nw")
        self._sel_canvas.configure(yscrollcommand=self._sel_scrollbar.set)
        self._sel_canvas.pack(side="left", fill="both", expand=True)
        self._sel_scrollbar.pack(side="right", fill="y")
        # Make inner frame width follow canvas
        self._sel_canvas.bind("<Configure>", lambda e: self._sel_canvas.itemconfig(
            self._sel_window, width=e.width))

        # 存储已选附魔的行控件: {enchant_name: (frame, level_var)}
        self._selected_widgets = {}

        # — 底部按钮 —
        btn_frame2 = ttk.Frame(self)
        btn_frame2.pack(fill="x", pady=10)
        ttk.Button(btn_frame2, text="确定", command=self._confirm).pack(side="right", padx=10)
        ttk.Button(btn_frame2, text="取消", command=self._cancel).pack(side="right")

    def _populate_avail(self):
        self.avail_listbox.delete(0, "end")
        for name, max_lv, cn in self._available_enchants:
            if name not in self._selected_widgets:
                self.avail_listbox.insert("end", f"{cn} (1-{max_lv})")

    def _move_to_selected(self):
        sel = self.avail_listbox.curselection()
        if not sel:
            return
        for idx in reversed(sel):
            text = self.avail_listbox.get(idx)
            # Find matching enchant entry
            matched = None
            for name, max_lv, cn in self._available_enchants:
                if f"{cn} (1-{max_lv})" == text:
                    matched = (name, max_lv, cn)
                    break
            if matched is None:
                continue
            name, max_lv, cn = matched
            if name in self._selected_widgets:
                continue
            # Create row in right panel
            row = ttk.Frame(self._sel_inner)
            row.pack(fill="x", pady=1)
            ttk.Label(row, text=cn, width=10).pack(side="left")
            lv_var = tk.StringVar(value="1")
            cb = ttk.Combobox(row, textvariable=lv_var,
                              values=[str(i) for i in range(1, max_lv + 1)],
                              width=3, state="readonly")
            cb.pack(side="left", padx=3)
            self._selected_widgets[name] = (row, lv_var)
        self._populate_avail()

    def _move_to_avail(self):
        # Since can't easily select from right panel, remove all selected
        names = list(self._selected_widgets.keys())
        if not names:
            return
        # Remove the last added
        name = names[-1]
        row, _ = self._selected_widgets.pop(name)
        row.destroy()
        self._populate_avail()

    def _confirm(self):
        self.result = []
        for name, (row, lv_var) in self._selected_widgets.items():
            try:
                lv = int(lv_var.get())
            except ValueError:
                lv = 1
            self.result.append((name, lv))
        self.destroy()

    def _cancel(self):
        self.result = None
        self.destroy()
