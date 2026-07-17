#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <string.h>
#include "villager_trade.h"

/* ====== Unicode UTF-8 for Chinese strings ====== */
#define LSTR(s) (s) /* our source is UTF-8, but Win32 API needs wchar */

/* Convert UTF-8 to wide char for Win32 API */
static WCHAR* to_wchar(const char* u8, WCHAR* buf, int maxlen) {
    MultiByteToWideChar(CP_UTF8, 0, u8, -1, buf, maxlen);
    return buf;
}

static WCHAR* alloc_wchar(const char* u8) {
    int len = MultiByteToWideChar(CP_UTF8, 0, u8, -1, NULL, 0);
    WCHAR* w = (WCHAR*)malloc(len * sizeof(WCHAR));
    MultiByteToWideChar(CP_UTF8, 0, u8, -1, w, len);
    return w;
}

static char* from_wchar(const WCHAR* w) {
    int len = WideCharToMultiByte(CP_UTF8, 0, w, -1, NULL, 0, NULL, NULL);
    char* u8 = (char*)malloc(len);
    WideCharToMultiByte(CP_UTF8, 0, w, -1, u8, len, NULL, NULL);
    return u8;
}

/* ====== Control IDs ====== */
#define ID_SEED         100
#define ID_PROF         101
#define ID_LEVEL        102
#define ID_OFFSET       103
#define ID_COUNT        104
#define ID_PREVIEW      105
#define ID_EXPORT       106
#define ID_FILELTER     107
#define ID_FKW          108
#define ID_FPMIN        109
#define ID_FPMAX        110
#define ID_FAPPLY       111
#define ID_FCLEAR       112
#define ID_LIST         200
#define ID_STATUSBAR    201
#define ID_PROF_LABEL   301
#define ID_LEVEL_LABEL  302
#define ID_FSTATUS      303

/* Node positioning panel */
#define ID_NODE_TOGGLE   310
#define ID_NODE_PANEL    311
#define ID_NODE_ADDOBS   312
#define ID_NODE_START    313
#define ID_NODE_LISTBOX  314

/* Type filter dialog */
#define ID_FILTER_CHK_ALL      1200
#define ID_FILTER_CHK_ENCHANT  1201
#define ID_FILTER_CHK_EQUIP    1202
#define ID_FILTER_CHK_STEW     1203
#define ID_FILTER_CHK_ARROW    1204
#define ID_FILTER_CHK_DYED     1205
#define ID_FILTER_CHK_NORMAL   1206
#define ID_FILTER_DLG_OK       1207
#define ID_FILTER_DLG_CANCEL   1208

/* Price filter dialog */
#define ID_PFILTER_CHK_MIN     1300
#define ID_PFILTER_CHK_125     1301
#define ID_PFILTER_EDIT_MIN    1302
#define ID_PFILTER_EDIT_MAX    1303
#define ID_PFILTER_DLG_OK      1304
#define ID_PFILTER_DLG_CANCEL  1305

/* ====== Globals ====== */
static HWND hSeedEdit, hProfCombo, hLevelCombo, hOffsetEdit, hCountEdit;
static HWND hPreviewBtn, hExportBtn, hFilterType, hFilterKW, hFilterPMin, hFilterPMax;
static HWND hApplyFilter, hClearFilter, hFilterStatus, hStatusBar;
static HWND hListView;
static int64_t g_seed = 0;
static int g_prof = 8; /* librarian */
static int g_level = 1;
static int g_offset = 0;
static int g_count = 100;
static WCHAR g_csv_header[9][64];
static int g_total_rows = 0;
static int g_filtered_rows = 0;
static int g_sort_col = 0;
static int g_sort_desc = 0;

static HWND hNodeToggle, hNodePanel, hNodeAddObs, hNodeStart, hNodeListBox;
static int g_node_panel_visible = 0;

/* Filter dialog state */
static int g_type_visible[7] = {1,1,1,1,1,1,1};
static int g_price_filter_min_only = 0;
static int g_price_filter_125pct = 0;
static int g_price_filter_min_val = 0;
static int g_price_filter_max_val = 9999;

/* ====== Profession & Level names (Chinese) ====== */
static const char* PROF_NAMES_CN[] = {
    "\347\233\224\347\224\262\345\214\240", /* armorer */
    "\345\261\240\345\244\253",
    "\345\210\266\345\233\276\345\270\210",
    "\347\211\247\345\270\210",
    "\345\206\234\346\260\221",
    "\346\270\224\345\244\253",
    "\345\210\266\347\256\255\345\270\210",
    "\347\232\256\345\214\240",
    "\345\233\276\344\271\246\347\256\241\347\220\206\345\221\230",
    "\347\237\263\345\214\240",
    "\347\211\247\347\276\212\344\272\272",
    "\345\267\245\345\205\267\345\214\240",
    "\346\255\246\345\231\250\345\214\240",
};
static const char* LEVEL_NAMES[] = {"\346\226\260\346\211\213","\345\255\246\345\276\222","\350\200\201\346\211\213","\344\270\223\345\256\266","\345\244\247\345\270\210"};

/* ====== ListView helpers ====== */
static void lv_insert_column(int idx, const char* text, int width) {
    LVCOLUMNW lvc = {0};
    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.cx = width;
    WCHAR w[64];
    to_wchar(text, w, 64);
    lvc.pszText = w;
    lvc.iSubItem = idx;
    SendMessageW(hListView, LVM_INSERTCOLUMNW, idx, (LPARAM)&lvc);
}

static void lv_set_item(int row, int col, const char* text) {
    WCHAR w[256];
    to_wchar(text, w, 256);

    if (col == 0) {
        LVITEMW lvi = {0};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = row;
        lvi.pszText = w;
        SendMessageW(hListView, LVM_INSERTITEMW, 0, (LPARAM)&lvi);
    } else {
        LVITEMW lvi = {0};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = row;
        lvi.iSubItem = col;
        lvi.pszText = w;
        SendMessageW(hListView, LVM_SETITEMW, 0, (LPARAM)&lvi);
    }
}

static void lv_clear(void) {
    SendMessageW(hListView, LVM_DELETEALLITEMS, 0, 0);
    g_total_rows = 0;
    g_filtered_rows = 0;
}

/* ====== Trade data storage ====== */
#define MAX_DATA_ROWS 100000

typedef struct {
    int offset, level;
    char entry[128], type[32], detail1[128], detail2[128];
    char ench_level[16], price[16], treasure[8];
    int price_val;
} DataRow;

static DataRow* g_data = NULL;
static int g_data_count = 0;

static void free_data(void) {
    free(g_data);
    g_data = NULL;
    g_data_count = 0;
}

static void populate_listview(void) {
    SendMessageW(hListView, WM_SETREDRAW, FALSE, 0);
    lv_clear();

    g_total_rows = g_data_count;
    g_filtered_rows = g_data_count;

    for (int i = 0; i < g_data_count; i++) {
        char off[16], lv[8];
        snprintf(off, sizeof(off), "%d", g_data[i].offset);
        snprintf(lv, sizeof(lv), "%d", g_data[i].level);
        lv_set_item(i, 0, off);
        lv_set_item(i, 1, lv);
        lv_set_item(i, 2, g_data[i].entry);
        lv_set_item(i, 3, g_data[i].type);
        lv_set_item(i, 4, g_data[i].detail1);
        lv_set_item(i, 5, g_data[i].detail2);
        lv_set_item(i, 6, g_data[i].ench_level);
        lv_set_item(i, 7, g_data[i].price);
        lv_set_item(i, 8, g_data[i].treasure);
    }
    SendMessageW(hListView, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(hListView, NULL, TRUE);

    WCHAR st[128];
    swprintf(st, 128, L"\346\230\276\347\244\272 %d \346\235\241", g_data_count);
    SetWindowTextW(hFilterStatus, st);
}

/* ====== Preview / Generate ====== */
static void on_preview(void) {
    WCHAR buf[256];
    GetWindowTextW(hSeedEdit, buf, 256);
    char* seed_str = from_wchar(buf);
    g_seed = _atoi64(seed_str);
    free(seed_str);

    GetWindowTextW(hOffsetEdit, buf, 256);
    seed_str = from_wchar(buf);
    g_offset = atoi(seed_str);
    free(seed_str);

    GetWindowTextW(hCountEdit, buf, 256);
    seed_str = from_wchar(buf);
    g_count = atoi(seed_str);
    free(seed_str);

    if (g_count > MAX_DATA_ROWS) g_count = MAX_DATA_ROWS;
    if (g_count <= 0) g_count = 100;

    g_prof = (int)SendMessageW(hProfCombo, CB_GETCURSEL, 0, 0);
    g_level = (int)SendMessageW(hLevelCombo, CB_GETCURSEL, 0, 0) + 1;

    free_data();
    g_data = (DataRow*)malloc(g_count * sizeof(DataRow));
    g_data_count = 0;

    /* 流式推进 RNG：创建一次，跳过起始偏移，顺序生成 */
    Xoroshiro128PlusPlus rng;
    create_rng_for(g_seed, g_prof, g_level, &rng);
    for (int i = 0; i < g_offset; i++)
        consume_trade_generation(g_prof, g_level, NULL, &rng);

    for (int off = g_offset; off < g_offset + g_count && g_data_count < MAX_DATA_ROWS; off++) {
        TradeResult result;
        simulate_trades(g_prof, g_level, NULL, &rng, &result);
        for (int j = 0; j < result.count; j++) {
            Trade* t = &result.trades[j];
            DataRow* r = &g_data[g_data_count++];

            r->offset = off;
            r->level = g_level;

            const char* ename = t->entry ? strrchr(t->entry, '/') : NULL;
            snprintf(r->entry, sizeof(r->entry), "%s", ename ? ename + 1 : (t->entry ? t->entry : ""));

            /* Type & details */
            switch (t->type) {
            case TRADE_TYPE_ENCHANT_BOOK:
                snprintf(r->type, sizeof(r->type), "\351\231\204\351\255\224\344\271\246");
                snprintf(r->detail1, sizeof(r->detail1), "%s", get_ench_cn(t->enchantment));
                snprintf(r->detail2, sizeof(r->detail2), "%s", t->enchantment);
                snprintf(r->ench_level, sizeof(r->ench_level), "%d", t->ench_level);
                snprintf(r->price, sizeof(r->price), "%d", t->final_cost);
                r->price_val = t->final_cost;
                snprintf(r->treasure, sizeof(r->treasure), "%s", t->is_treasure ? "\346\230\257" : "\345\220\246");
                break;
            case TRADE_TYPE_ENCHANT_EQUIP: {
                snprintf(r->type, sizeof(r->type), "\351\231\204\351\255\224\350\243\205\345\244\207");
                const char* iname = t->item ? t->item : "?";
                if (strncmp(iname, "minecraft:", 10) == 0) iname += 10;
                snprintf(r->detail1, sizeof(r->detail1), "%s", iname);
                char encs[256] = "";
                for (int i = 0; i < t->num_enchants; i++) {
                    char tmp[64];
                    snprintf(tmp, sizeof(tmp), "%s%s %d", i > 0 ? "; " : "",
                             get_ench_cn(t->enchantments[i]), t->enchant_levels[i]);
                    strcat(encs, tmp);
                }
                snprintf(r->detail2, sizeof(r->detail2), "%s", encs);
                snprintf(r->price, sizeof(r->price), "%d", t->final_cost);
                r->price_val = t->final_cost;
                r->ench_level[0] = '\0';
                r->treasure[0] = '\0';
                break;
            }
            case TRADE_TYPE_STEW:
                snprintf(r->type, sizeof(r->type), "\350\277\267\344\271\213\347\202\226\350\217\234");
                snprintf(r->detail1, sizeof(r->detail1), "%s", t->effect);
                snprintf(r->detail2, sizeof(r->detail2), "%.0f\347\247\222", t->duration_ticks / 20.0);
                r->ench_level[0] = '\0';
                r->price[0] = '\0';
                r->price_val = -1;
                r->treasure[0] = '\0';
                break;
            case TRADE_TYPE_TIPPED_ARROW:
                snprintf(r->type, sizeof(r->type), "\350\215\257\347\256\255");
                snprintf(r->detail1, sizeof(r->detail1), "%s", t->potion);
                r->detail2[0] = '\0';
                r->ench_level[0] = '\0';
                r->price[0] = '\0';
                r->price_val = -1;
                r->treasure[0] = '\0';
                break;
            case TRADE_TYPE_DYED_EQUIP:
                snprintf(r->type, sizeof(r->type), "\346\237\223\350\211\262\350\243\205\345\244\207");
                {
                    char dyes[128] = "";
                    for (int i = 0; i < t->dye_count; i++) {
                        if (i > 0) strcat(dyes, "/");
                        strcat(dyes, t->dyes[i]);
                    }
                    snprintf(r->detail1, sizeof(r->detail1), "%s", dyes);
                    snprintf(r->detail2, sizeof(r->detail2), "%d", t->dye_count);
                }
                r->ench_level[0] = '\0';
                r->price[0] = '\0';
                r->price_val = -1;
                r->treasure[0] = '\0';
                break;
            default:
                snprintf(r->type, sizeof(r->type), "\346\231\256\351\200\232");
                r->detail1[0] = '\0';
                r->detail2[0] = '\0';
                r->ench_level[0] = '\0';
                r->price[0] = '\0';
                r->price_val = -1;
                r->treasure[0] = '\0';
                break;
            }
        }
        consume_trade_generation(g_prof, g_level, NULL, &rng);
    }

    populate_listview();
}

/* ====== Filter ====== */
static void apply_filter(void) {
    if (!g_data || g_data_count == 0) return;

    WCHAR wbuf[256];
    char type_filter[64] = "", kw[128] = "";
    int pmin = -1, pmax = -1;

    GetWindowTextW(hFilterType, wbuf, 256);
    char* s = from_wchar(wbuf);
    strncpy(type_filter, s, 63); free(s);

    GetWindowTextW(hFilterKW, wbuf, 256);
    s = from_wchar(wbuf);
    strncpy(kw, s, 127); free(s);

    GetWindowTextW(hFilterPMin, wbuf, 256);
    s = from_wchar(wbuf);
    if (strlen(s) > 0) pmin = atoi(s); free(s);

    GetWindowTextW(hFilterPMax, wbuf, 256);
    s = from_wchar(wbuf);
    if (strlen(s) > 0) pmax = atoi(s); free(s);

    int has_tf = strcmp(type_filter, "\345\205\250\351\203\250") != 0;
    int has_kw = strlen(kw) > 0;

    int visible[MAX_DATA_ROWS];
    int vis_count = 0;
    for (int i = 0; i < g_data_count; i++) {
        DataRow* r = &g_data[i];
        if (has_tf && strcmp(r->type, type_filter) != 0) continue;
        if (has_kw) {
            if (!strstr(r->detail1, kw) && !strstr(r->detail2, kw)) continue;
        }
        if (pmin >= 0 && r->price_val >= 0 && r->price_val < pmin) continue;
        if (pmax >= 0 && r->price_val >= 0 && r->price_val > pmax) continue;
        visible[vis_count++] = i;
    }

    /* Redisplay with only visible rows */
    SendMessageW(hListView, WM_SETREDRAW, FALSE, 0);
    SendMessageW(hListView, LVM_DELETEALLITEMS, 0, 0);
    for (int i = 0; i < vis_count; i++) {
        DataRow* r = &g_data[visible[i]];
        char off_str[16], lv_str[8];
        snprintf(off_str, sizeof(off_str), "%d", r->offset);
        snprintf(lv_str, sizeof(lv_str), "%d", r->level);
        lv_set_item(i, 0, off_str);
        lv_set_item(i, 1, lv_str);
        lv_set_item(i, 2, r->entry);
        lv_set_item(i, 3, r->type);
        lv_set_item(i, 4, r->detail1);
        lv_set_item(i, 5, r->detail2);
        lv_set_item(i, 6, r->ench_level);
        lv_set_item(i, 7, r->price);
        lv_set_item(i, 8, r->treasure);
    }
    g_filtered_rows = vis_count;
    SendMessageW(hListView, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(hListView, NULL, TRUE);

    swprintf(wbuf, 128, L"\346\230\276\347\244\272 %d / %d \346\235\241", vis_count, g_data_count);
    SetWindowTextW(hFilterStatus, wbuf);
}

static void clear_filter(void) {
    SetWindowTextW(hFilterType, L"\345\205\250\351\203\250");
    SetWindowTextW(hFilterKW, L"");
    SetWindowTextW(hFilterPMin, L"");
    SetWindowTextW(hFilterPMax, L"");
    if (g_data && g_data_count > 0)
        populate_listview();
}

/* ====== CSV Export ====== */
static void on_export(void) {
    if (!g_data || g_data_count == 0) {
        MessageBoxW(NULL, L"\350\257\267\345\205\210\351\242\204\350\247\210\344\272\244\346\230\223",
                    L"\346\217\220\347\244\272", MB_OK | MB_ICONINFORMATION);
        return;
    }

    OPENFILENAMEW ofn = {0};
    WCHAR filepath[MAX_PATH] = L"trade_export.csv";
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = L"CSV\346\226\207\344\273\266 (*.csv)\0*.csv\0\346\211\200\346\234\211\346\226\207\344\273\266\0*.*\0";
    ofn.lpstrFile = filepath;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

    if (!GetSaveFileNameW(&ofn)) return;

    FILE* f = _wfopen(filepath, L"w,ccs=UTF-8");
    if (!f) {
        MessageBoxW(NULL, L"\346\227\240\346\263\225\345\210\233\345\273\272\346\226\207\344\273\266",
                    L"\351\224\231\350\257\257", MB_OK | MB_ICONERROR);
        return;
    }

    fwprintf(f, L"\xFEFF"); /* BOM */
    fwprintf(f, L"\345\201\217\347\247\273,\347\255\211\347\272\247,\344\272\244\346\230\223\346\235\241\347\233\256,"
                L"\347\261\273\345\236\213,\350\257\246\346\203\2051,\350\257\246\346\203\2052,"
                L"\351\231\204\351\255\224\347\255\211\347\272\247,\344\273\267\346\240\274(E),\345\256\235\350\227\217\n");

    fwprintf(f, L"\347\247\215\345\255\220: %lld,,"
                L"\350\201\214\344\270\232: %S(L%d-%S),,"
                L"\345\257\274\345\207\272\346\235\241\346\225\260: %d\n\n",
             g_seed, PROF_NAMES_CN[g_prof], g_level, LEVEL_NAMES[g_level - 1], g_total_rows);

    fwprintf(f, L"\345\201\217\347\247\273,\347\255\211\347\272\247,\344\272\244\346\230\223\346\235\241\347\233\256,"
                L"\347\261\273\345\236\213,\350\257\246\346\203\2051,\350\257\246\346\203\2052,"
                L"\351\231\204\351\255\224\347\255\211\347\272\247,\344\273\267\346\240\274(E),\345\256\235\350\227\217\n");

    for (int i = 0; i < g_data_count; i++) {
        fwprintf(f, L"%d,%d,%S,%S,%S,%S,%S,%S,%S\n",
                 g_data[i].offset, g_data[i].level,
                 g_data[i].entry, g_data[i].type,
                 g_data[i].detail1, g_data[i].detail2,
                 g_data[i].ench_level, g_data[i].price, g_data[i].treasure);
    }
    fclose(f);

    MessageBoxW(NULL, L"CSV\346\226\207\344\273\266\345\257\274\345\207\272\346\210\220\345\212\237!",
                L"\346\217\220\347\244\272", MB_OK | MB_ICONINFORMATION);
}

/* ====== Sort ====== */
static void on_sort(int col) {
    if (col == 0) {
        if (g_sort_col == 0) g_sort_desc = !g_sort_desc;
        else { g_sort_col = 0; g_sort_desc = 0; }
    } else if (col == 7) {
        if (g_sort_col == 7) g_sort_desc = !g_sort_desc;
        else { g_sort_col = 7; g_sort_desc = 0; }
    } else return;

    /* Bubble sort (OK for preview sizes) */
    for (int i = 0; i < g_data_count - 1; i++) {
        for (int j = 0; j < g_data_count - 1 - i; j++) {
            int cmp;
            if (g_sort_col == 0) {
                cmp = g_data[j].offset - g_data[j + 1].offset;
            } else {
                cmp = g_data[j].price_val - g_data[j + 1].price_val;
            }
            if (g_sort_desc) cmp = -cmp;
            if (cmp > 0) {
                DataRow tmp = g_data[j];
                g_data[j] = g_data[j + 1];
                g_data[j + 1] = tmp;
            }
        }
    }
    populate_listview();
}

/* ====== Filter Dialog Procedures ====== */

static const WCHAR FILTER_DLG_CLASS[] = L"TradeFilterPopup";

/* Helper: run modal message loop for a popup window */
static void modal_loop(HWND hParent, HWND hDlg) {
    EnableWindow(hParent, FALSE);
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        if (!IsWindow(hDlg)) break;
        if (!IsDialogMessageW(hDlg, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    EnableWindow(hParent, TRUE);
    SetForegroundWindow(hParent);
}

/* Apply type filter from g_type_visible[] */
static void apply_type_filter(void) {
    if (!g_data || g_data_count == 0) return;
    static const char* type_keys[] = {
        "", /* index 0 unused for type_keys[1..6] */
        "\351\231\204\351\255\224\344\271\246",
        "\351\231\204\351\255\224\350\243\205\345\244\207",
        "\350\277\267\344\271\213\347\202\226\350\217\234",
        "\350\215\257\347\256\255",
        "\346\237\223\350\211\262\350\243\205\345\244\207",
        "\346\231\256\351\200\232"
    };
    int any_off = 1;
    for (int i = 1; i < 7; i++) { if (!g_type_visible[i]) any_off = 0; }
    if (any_off && g_type_visible[0]) { populate_listview(); return; }

    int visible[MAX_DATA_ROWS], vis_count = 0;
    for (int i = 0; i < g_data_count; i++) {
        int show = g_type_visible[0];
        for (int t = 1; t < 7; t++) {
            if (g_type_visible[t] && strcmp(g_data[i].type, type_keys[t]) == 0) { show = 1; break; }
        }
        if (show) visible[vis_count++] = i;
    }

    SendMessageW(hListView, WM_SETREDRAW, FALSE, 0);
    SendMessageW(hListView, LVM_DELETEALLITEMS, 0, 0);
    for (int i = 0; i < vis_count; i++) {
        DataRow* r = &g_data[visible[i]];
        char off_str[16], lv_str[8];
        snprintf(off_str, sizeof(off_str), "%d", r->offset);
        snprintf(lv_str, sizeof(lv_str), "%d", r->level);
        lv_set_item(i, 0, off_str);
        lv_set_item(i, 1, lv_str);
        lv_set_item(i, 2, r->entry);
        lv_set_item(i, 3, r->type);
        lv_set_item(i, 4, r->detail1);
        lv_set_item(i, 5, r->detail2);
        lv_set_item(i, 6, r->ench_level);
        lv_set_item(i, 7, r->price);
        lv_set_item(i, 8, r->treasure);
    }
    g_filtered_rows = vis_count;
    SendMessageW(hListView, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(hListView, NULL, TRUE);

    WCHAR wbuf[128];
    swprintf(wbuf, 128, L"\346\230\276\347\244\272 %d / %d \346\235\241", vis_count, g_data_count);
    SetWindowTextW(hFilterStatus, wbuf);
}

/* Apply price filter */
static void apply_price_filter(void) {
    if (!g_data || g_data_count == 0) return;
    if (!g_price_filter_min_only && !g_price_filter_125pct
        && g_price_filter_min_val == 0 && g_price_filter_max_val == 9999) {
        populate_listview(); return;
    }

    int visible[MAX_DATA_ROWS], vis_count = 0;
    for (int i = 0; i < g_data_count; i++) {
        DataRow* r = &g_data[i];
        if (r->price_val < 0) continue;
        if (r->price_val < g_price_filter_min_val) continue;
        if (r->price_val > g_price_filter_max_val) continue;
        visible[vis_count++] = i;
    }

    SendMessageW(hListView, WM_SETREDRAW, FALSE, 0);
    SendMessageW(hListView, LVM_DELETEALLITEMS, 0, 0);
    for (int i = 0; i < vis_count; i++) {
        DataRow* r = &g_data[visible[i]];
        char off_str[16], lv_str[8];
        snprintf(off_str, sizeof(off_str), "%d", r->offset);
        snprintf(lv_str, sizeof(lv_str), "%d", r->level);
        lv_set_item(i, 0, off_str);
        lv_set_item(i, 1, lv_str);
        lv_set_item(i, 2, r->entry);
        lv_set_item(i, 3, r->type);
        lv_set_item(i, 4, r->detail1);
        lv_set_item(i, 5, r->detail2);
        lv_set_item(i, 6, r->ench_level);
        lv_set_item(i, 7, r->price);
        lv_set_item(i, 8, r->treasure);
    }
    g_filtered_rows = vis_count;
    SendMessageW(hListView, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(hListView, NULL, TRUE);

    WCHAR wbuf[128];
    swprintf(wbuf, 128, L"\346\230\276\347\244\272 %d / %d \346\235\241", vis_count, g_data_count);
    SetWindowTextW(hFilterStatus, wbuf);
}

/* Type filter dialog procedure (no WM_CREATE — controls built in show func) */
static LRESULT CALLBACK TypeFilterDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wp) == ID_FILTER_DLG_OK) {
            g_type_visible[0] = (SendMessageW(GetDlgItem(hwnd, ID_FILTER_CHK_ALL), BM_GETCHECK, 0, 0) == BST_CHECKED);
            static const int ids[] = { ID_FILTER_CHK_ENCHANT, ID_FILTER_CHK_EQUIP, ID_FILTER_CHK_STEW,
                                       ID_FILTER_CHK_ARROW, ID_FILTER_CHK_DYED, ID_FILTER_CHK_NORMAL };
            for (int i = 0; i < 6; i++)
                g_type_visible[i+1] = (SendMessageW(GetDlgItem(hwnd, ids[i]), BM_GETCHECK, 0, 0) == BST_CHECKED);
            DestroyWindow(hwnd);
            apply_type_filter();
            return 0;
        }
        if (LOWORD(wp) == ID_FILTER_DLG_CANCEL) {
            DestroyWindow(hwnd);
            return 0;
        }
        if (LOWORD(wp) == ID_FILTER_CHK_ALL) {
            int checked = (SendMessageW(GetDlgItem(hwnd, ID_FILTER_CHK_ALL), BM_GETCHECK, 0, 0) == BST_CHECKED);
            static const int ids[] = { ID_FILTER_CHK_ENCHANT, ID_FILTER_CHK_EQUIP, ID_FILTER_CHK_STEW,
                                       ID_FILTER_CHK_ARROW, ID_FILTER_CHK_DYED, ID_FILTER_CHK_NORMAL };
            for (int i = 0; i < 6; i++)
                SendMessageW(GetDlgItem(hwnd, ids[i]), BM_SETCHECK,
                             checked ? BST_CHECKED : BST_UNCHECKED, 0);
            return 0;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

/* Show type filter dialog */
static void show_type_filter_dlg(HWND hParent, HINSTANCE hInst) {
    HWND hDlg = CreateWindowExW(0, FILTER_DLG_CLASS,
        L"\347\261\273\345\236\213\347\255\233\351\200\211",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        100, 100, 260, 250, hParent, NULL, hInst, NULL);
    if (!hDlg) return;

    SetWindowLongPtrW(hDlg, GWLP_WNDPROC, (LONG_PTR)TypeFilterDlgProc);
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    HWND hAll = CreateWindowW(L"BUTTON", L"\345\205\250\351\203\250",
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        15, 10, 200, 22, hDlg, (HMENU)ID_FILTER_CHK_ALL, hInst, NULL);
    SendMessageW(hAll, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessageW(hAll, BM_SETCHECK, g_type_visible[0] ? BST_CHECKED : BST_UNCHECKED, 0);

    static const WCHAR* type_names[] = {
        L"\351\231\204\351\255\224\344\271\246",
        L"\351\231\204\351\255\224\350\243\205\345\244\207",
        L"\350\277\267\344\271\213\347\202\226\350\217\234",
        L"\350\215\257\347\256\255",
        L"\346\237\223\350\211\262\350\243\205\345\244\207",
        L"\346\231\256\351\200\232\344\272\244\346\230\223"
    };
    static const int type_ids[] = {
        ID_FILTER_CHK_ENCHANT, ID_FILTER_CHK_EQUIP, ID_FILTER_CHK_STEW,
        ID_FILTER_CHK_ARROW, ID_FILTER_CHK_DYED, ID_FILTER_CHK_NORMAL
    };
    for (int i = 0; i < 6; i++) {
        HWND hCB = CreateWindowW(L"BUTTON", type_names[i],
            WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
            30, 40 + i * 22, 200, 22, hDlg, (HMENU)type_ids[i], hInst, NULL);
        SendMessageW(hCB, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessageW(hCB, BM_SETCHECK, g_type_visible[i+1] ? BST_CHECKED : BST_UNCHECKED, 0);
    }

    CreateWindowW(L"BUTTON", L"\347\241\256\345\256\232",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        65, 180, 75, 26, hDlg, (HMENU)ID_FILTER_DLG_OK, hInst, NULL);
    CreateWindowW(L"BUTTON", L"\345\217\226\346\266\210",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        150, 180, 75, 26, hDlg, (HMENU)ID_FILTER_DLG_CANCEL, hInst, NULL);

    modal_loop(hParent, hDlg);
}

/* Price filter dialog procedure (no WM_CREATE — controls built in show func) */
static LRESULT CALLBACK PriceFilterDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wp) == ID_PFILTER_DLG_OK) {
            g_price_filter_min_only = (SendMessageW(GetDlgItem(hwnd, ID_PFILTER_CHK_MIN), BM_GETCHECK, 0, 0) == BST_CHECKED);
            g_price_filter_125pct = (SendMessageW(GetDlgItem(hwnd, ID_PFILTER_CHK_125), BM_GETCHECK, 0, 0) == BST_CHECKED);
            WCHAR buf[32];
            GetWindowTextW(GetDlgItem(hwnd, ID_PFILTER_EDIT_MIN), buf, 32);
            g_price_filter_min_val = (buf[0] != 0) ? _wtoi(buf) : 0;
            GetWindowTextW(GetDlgItem(hwnd, ID_PFILTER_EDIT_MAX), buf, 32);
            g_price_filter_max_val = (buf[0] != 0) ? _wtoi(buf) : 9999;
            DestroyWindow(hwnd);
            apply_price_filter();
            return 0;
        }
        if (LOWORD(wp) == ID_PFILTER_DLG_CANCEL) {
            DestroyWindow(hwnd);
            return 0;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

/* Show price filter dialog */
static void show_price_filter_dlg(HWND hParent, HINSTANCE hInst) {
    HWND hDlg = CreateWindowExW(0, FILTER_DLG_CLASS,
        L"\344\273\267\346\240\274\347\255\233\351\200\211",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        100, 100, 230, 210, hParent, NULL, hInst, NULL);
    if (!hDlg) return;

    SetWindowLongPtrW(hDlg, GWLP_WNDPROC, (LONG_PTR)PriceFilterDlgProc);
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    HWND hChk1 = CreateWindowW(L"BUTTON", L"\344\273\205\346\234\200\344\275\216\344\273\267",
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        15, 10, 200, 22, hDlg, (HMENU)ID_PFILTER_CHK_MIN, hInst, NULL);
    SendMessageW(hChk1, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessageW(hChk1, BM_SETCHECK, g_price_filter_min_only ? BST_CHECKED : BST_UNCHECKED, 0);

    HWND hChk2 = CreateWindowW(L"BUTTON", L"\346\234\200\344\275\216\344\273\267 \303\227 125%",
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        15, 38, 200, 22, hDlg, (HMENU)ID_PFILTER_CHK_125, hInst, NULL);
    SendMessageW(hChk2, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessageW(hChk2, BM_SETCHECK, g_price_filter_125pct ? BST_CHECKED : BST_UNCHECKED, 0);

    CreateWindowW(L"STATIC", L"\346\234\200\344\275\216\344\273\267\346\240\274(E):",
        WS_CHILD | WS_VISIBLE, 15, 72, 80, 22, hDlg, NULL, hInst, NULL);
    HWND hMin = CreateWindowW(L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        100, 70, 60, 22, hDlg, (HMENU)ID_PFILTER_EDIT_MIN, hInst, NULL);
    SendMessageW(hMin, WM_SETFONT, (WPARAM)hFont, TRUE);

    CreateWindowW(L"STATIC", L"\346\234\200\345\244\247\344\273\267\346\240\274(E):",
        WS_CHILD | WS_VISIBLE, 15, 100, 80, 22, hDlg, NULL, hInst, NULL);
    HWND hMax = CreateWindowW(L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        100, 98, 60, 22, hDlg, (HMENU)ID_PFILTER_EDIT_MAX, hInst, NULL);
    SendMessageW(hMax, WM_SETFONT, (WPARAM)hFont, TRUE);

    CreateWindowW(L"BUTTON", L"\347\241\256\345\256\232",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        50, 140, 75, 26, hDlg, (HMENU)ID_PFILTER_DLG_OK, hInst, NULL);
    CreateWindowW(L"BUTTON", L"\345\217\226\346\266\210",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        140, 140, 75, 26, hDlg, (HMENU)ID_PFILTER_DLG_CANCEL, hInst, NULL);

    modal_loop(hParent, hDlg);
}

/* ====== Window Procedure ====== */
static WNDPROC g_oldListViewProc = NULL;

static LRESULT CALLBACK ListViewSubclassProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NOTIFY) {
        NMHDR* nm = (NMHDR*)lp;
        if (nm->code == LVN_COLUMNCLICK) {
            NMLISTVIEW* lv = (NMLISTVIEW*)lp;
            int col = lv->iSubItem;
            HWND hParent = GetParent(hwnd);
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hParent, GWLP_HINSTANCE);

            if (col == 3) {
                show_type_filter_dlg(hParent, hInst);
            } else if (col == 7) {
                show_price_filter_dlg(hParent, hInst);
            } else if (col == 0) {
                on_sort(col);
            } else {
                MessageBoxW(hParent,
                    L"\346\255\244\345\210\227\347\255\233\351\200\211\345\260\232\346\234\252\345\256\236\347\216\260",
                    L"\346\217\220\347\244\272", MB_OK | MB_ICONINFORMATION);
            }
            return 0;
        }
    }
    return CallWindowProcW(g_oldListViewProc, hwnd, msg, wp, lp);
}

static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE: {
        HINSTANCE hInst = ((LPCREATESTRUCT)lp)->hInstance;

        /* Seed row */
        CreateWindowW(L"STATIC", L"    \344\270\226\347\225\214\347\247\215\345\255\220: ",
                      WS_CHILD | WS_VISIBLE, 10, 12, 100, 23, hwnd, NULL, hInst, NULL);
        hSeedEdit = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            110, 10, 190, 23, hwnd, (HMENU)ID_SEED, hInst, NULL);

        CreateWindowW(L"STATIC", L" \350\201\214\344\270\232: ",
                      WS_CHILD | WS_VISIBLE, 310, 12, 55, 23, hwnd, NULL, hInst, NULL);
        hProfCombo = CreateWindowW(L"COMBOBOX", L"",
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            365, 10, 140, 200, hwnd, (HMENU)ID_PROF, hInst, NULL);
        for (int i = 0; i < 13; i++) {
            WCHAR w[32];
            to_wchar(PROF_NAMES_CN[i], w, 32);
            SendMessageW(hProfCombo, CB_ADDSTRING, 0, (LPARAM)w);
        }
        SendMessageW(hProfCombo, CB_SETCURSEL, g_prof, 0);

        CreateWindowW(L"STATIC", L" \347\255\211\347\272\247: ",
                      WS_CHILD | WS_VISIBLE, 515, 12, 55, 23, hwnd, NULL, hInst, NULL);
        hLevelCombo = CreateWindowW(L"COMBOBOX", L"",
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            570, 10, 80, 200, hwnd, (HMENU)ID_LEVEL, hInst, NULL);
        for (int i = 0; i < 5; i++) {
            WCHAR w[16];
            swprintf(w, 16, L"%d-%S", i + 1, LEVEL_NAMES[i]);
            SendMessageW(hLevelCombo, CB_ADDSTRING, 0, (LPARAM)w);
        }
        SendMessageW(hLevelCombo, CB_SETCURSEL, g_level - 1, 0);

        /* Offset/Count row */
        CreateWindowW(L"STATIC", L"    \350\265\267\345\247\213\345\201\217\347\247\273: ",
                      WS_CHILD | WS_VISIBLE, 10, 42, 100, 23, hwnd, NULL, hInst, NULL);
        hOffsetEdit = CreateWindowW(L"EDIT", L"0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            110, 40, 80, 23, hwnd, (HMENU)ID_OFFSET, hInst, NULL);

        CreateWindowW(L"STATIC", L" \345\257\274\345\207\272\346\225\260\351\207\217: ",
                      WS_CHILD | WS_VISIBLE, 200, 42, 80, 23, hwnd, NULL, hInst, NULL);
        hCountEdit = CreateWindowW(L"EDIT", L"100",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            280, 40, 80, 23, hwnd, (HMENU)ID_COUNT, hInst, NULL);

        /* Buttons */
        hPreviewBtn = CreateWindowW(L"BUTTON", L"\351\242\204\350\247\210\344\272\244\346\230\223",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            380, 38, 90, 26, hwnd, (HMENU)ID_PREVIEW, hInst, NULL);
        hExportBtn = CreateWindowW(L"BUTTON", L"\345\257\274\345\207\272CSV",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            480, 38, 90, 26, hwnd, (HMENU)ID_EXPORT, hInst, NULL);

        /* Filter row */
        CreateWindowW(L"STATIC", L"    \347\261\273\345\236\213:",
                      WS_CHILD | WS_VISIBLE, 10, 72, 55, 23, hwnd, NULL, hInst, NULL);
        hFilterType = CreateWindowW(L"COMBOBOX", L"\345\205\250\351\203\250",
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            60, 70, 90, 200, hwnd, (HMENU)ID_FILELTER, hInst, NULL);
        {
            WCHAR types[][16] = { L"\345\205\250\351\203\250", L"\351\231\204\351\255\224\344\271\246",
                L"\351\231\204\351\255\224\350\243\205\345\244\207", L"\350\277\267\344\271\213\347\202\226\350\217\234",
                L"\350\215\257\347\256\255", L"\346\237\223\350\211\262\350\243\205\345\244\207", L"\346\231\256\351\200\232" };
            for (int i = 0; i < 7; i++)
                SendMessageW(hFilterType, CB_ADDSTRING, 0, (LPARAM)types[i]);
            SendMessageW(hFilterType, CB_SETCURSEL, 0, 0);
        }

        CreateWindowW(L"STATIC", L" \345\205\263\351\224\256\350\257\215:",
                      WS_CHILD | WS_VISIBLE, 160, 72, 55, 23, hwnd, NULL, hInst, NULL);
        hFilterKW = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            215, 70, 130, 23, hwnd, (HMENU)ID_FKW, hInst, NULL);

        CreateWindowW(L"STATIC", L" \344\273\267\346\240\274:",
                      WS_CHILD | WS_VISIBLE, 355, 72, 40, 23, hwnd, NULL, hInst, NULL);
        hFilterPMin = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            395, 70, 50, 23, hwnd, (HMENU)ID_FPMIN, hInst, NULL);
        CreateWindowW(L"STATIC", L"~", WS_CHILD | WS_VISIBLE,
                      447, 72, 15, 23, hwnd, NULL, hInst, NULL);
        hFilterPMax = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            462, 70, 50, 23, hwnd, (HMENU)ID_FPMAX, hInst, NULL);

        hApplyFilter = CreateWindowW(L"BUTTON", L"\345\272\224\347\224\250\347\255\233\351\200\211",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            520, 68, 75, 26, hwnd, (HMENU)ID_FAPPLY, hInst, NULL);
        hClearFilter = CreateWindowW(L"BUTTON", L"\346\270\205\351\231\244",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            600, 68, 55, 26, hwnd, (HMENU)ID_FCLEAR, hInst, NULL);

        hFilterStatus = CreateWindowW(L"STATIC", L"",
            WS_CHILD | WS_VISIBLE, 10, 100, 200, 20, hwnd, (HMENU)ID_FSTATUS, hInst, NULL);

        /* Node positioning toggle button */
        hNodeToggle = CreateWindowW(L"BUTTON", L"\342\226\274 \350\212\202\347\202\271\345\256\232\344\275\215",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            590, 98, 70, 22, hwnd, (HMENU)ID_NODE_TOGGLE, hInst, NULL);

        /* Node positioning panel (initially hidden) */
        hNodePanel = CreateWindowW(L"BUTTON", L"", /* groupbox */
            WS_CHILD | BS_GROUPBOX,
            10, 125, 650, 150, hwnd, (HMENU)ID_NODE_PANEL, hInst, NULL);

        /* Observation list inside panel */
        hNodeListBox = CreateWindowW(L"LISTBOX", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
            20, 140, 400, 110, hNodePanel, (HMENU)ID_NODE_LISTBOX, hInst, NULL);

        /* Buttons inside panel */
        hNodeAddObs = CreateWindowW(L"BUTTON", L"\346\267\273\345\212\240\350\247\202\346\265\213",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            430, 140, 100, 26, hNodePanel, (HMENU)ID_NODE_ADDOBS, hInst, NULL);
        hNodeStart = CreateWindowW(L"BUTTON", L"\345\274\200\345\247\213\345\256\232\344\275\215",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            430, 175, 100, 26, hNodePanel, (HMENU)ID_NODE_START, hInst, NULL);

        /* Hide panel initially */
        ShowWindow(hNodePanel, SW_HIDE);
        ShowWindow(hNodeListBox, SW_HIDE);
        ShowWindow(hNodeAddObs, SW_HIDE);
        ShowWindow(hNodeStart, SW_HIDE);

        /* ListView */
        hListView = CreateWindowW(WC_LISTVIEWW, L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
            10, 120, 670, 450, hwnd, (HMENU)ID_LIST, hInst, NULL);

        /* Subclass for column click */
        g_oldListViewProc = (WNDPROC)SetWindowLongPtrW(hListView, GWLP_WNDPROC,
                                                       (LONG_PTR)ListViewSubclassProc);

        ListView_SetExtendedListViewStyle(hListView,
            LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);

        lv_insert_column(0, "\345\201\217\347\247\273", 60);
        lv_insert_column(1, "\347\255\211\347\272\247", 45);
        lv_insert_column(2, "\344\272\244\346\230\223\346\235\241\347\233\256", 180);
        lv_insert_column(3, "\347\261\273\345\236\213", 80);
        lv_insert_column(4, "\350\257\246\346\203\2051", 100);
        lv_insert_column(5, "\350\257\246\346\203\2052", 80);
        lv_insert_column(6, "\351\231\204\351\255\224\347\255\211\347\272\247", 65);
        lv_insert_column(7, "\344\273\267\346\240\274(E)", 60);
        lv_insert_column(8, "\345\256\235\350\227\217", 45);

        /* Status bar */
        hStatusBar = CreateWindowW(STATUSCLASSNAMEW, L"\345\207\206\345\244\207\345\260\261\347\273\252",
            WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)ID_STATUSBAR, hInst, NULL);

        /* Font */
        HFONT hFont = CreateFontW(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Microsoft YaHei");
        SendMessageW(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
        EnumChildWindows(hwnd, (WNDENUMPROC)EnumChildProc, (LPARAM)hFont);
        return 0;
    }

    case WM_CTLCOLORSTATIC:
        if ((HWND)lp == hFilterStatus) {
            SetTextColor((HDC)wp, RGB(0, 100, 200));
            SetBkMode((HDC)wp, TRANSPARENT);
            return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
        }
        return DefWindowProcW(hwnd, msg, wp, lp);

    case WM_COMMAND:
        if (LOWORD(wp) == ID_PREVIEW) { on_preview(); return 0; }
        if (LOWORD(wp) == ID_EXPORT) { on_export(); return 0; }
        if (LOWORD(wp) == ID_FAPPLY) { apply_filter(); return 0; }
        if (LOWORD(wp) == ID_FCLEAR) { clear_filter(); return 0; }
        if (LOWORD(wp) == ID_NODE_TOGGLE) {
            g_node_panel_visible = !g_node_panel_visible;
            int sw = g_node_panel_visible ? SW_SHOW : SW_HIDE;
            ShowWindow(hNodePanel, sw);
            ShowWindow(hNodeListBox, sw);
            ShowWindow(hNodeAddObs, sw);
            ShowWindow(hNodeStart, sw);
            /* Update toggle button text */
            SetWindowTextW(hNodeToggle,
                g_node_panel_visible
                ? L"\342\226\262 \350\212\202\347\202\271\345\256\232\344\275\215"
                : L"\342\226\274 \350\212\202\347\202\271\345\256\232\344\275\215");
            /* Trigger relayout */
            RECT rc;
            GetClientRect(hwnd, &rc);
            SendMessageW(hwnd, WM_SIZE, 0, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));
            return 0;
        }
        break;

    case WM_SIZE: {
        RECT rc;
        GetClientRect(hwnd, &rc);
        int w = rc.right - rc.left;
        int h = rc.bottom - rc.top;

        SendMessageW(hStatusBar, WM_SIZE, 0, 0);
        RECT sbRect;
        GetClientRect(hStatusBar, &sbRect);

        int panel_h = g_node_panel_visible ? 160 : 0;
        int lv_y = 120 + panel_h;
        SetWindowPos(hListView, NULL, 10, lv_y, w - 20, h - lv_y - sbRect.bottom - 5, SWP_NOZORDER);
        return 0;
    }

    case WM_DESTROY:
        free_data();
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
    SendMessageW(hwnd, WM_SETFONT, (WPARAM)lParam, TRUE);
    return TRUE;
}

/* ====== Entry ====== */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;

    /* Init Common Controls */
    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icc);

    /* Window Class */
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"TradeExportWindow";
    RegisterClassExW(&wc);

    /* Register filter popup dialog class */
    WNDCLASSEXW fwc = {0};
    fwc.cbSize = sizeof(fwc);
    fwc.lpfnWndProc = DefWindowProcW;
    fwc.hInstance = hInstance;
    fwc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    fwc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    fwc.lpszClassName = FILTER_DLG_CLASS;
    RegisterClassExW(&fwc);

    HWND hwnd = CreateWindowExW(
        0, L"TradeExportWindow",
        L"\346\235\221\346\260\221\344\272\244\346\230\223\345\257\274\345\207\272\345\267\245\345\205\267 - MC 26.1",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 650,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}
