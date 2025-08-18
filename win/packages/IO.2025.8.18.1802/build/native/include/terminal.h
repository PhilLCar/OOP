#ifndef TERMINAL_H
#define TERMINAL_H

// C
#include <stdio.h>
#include <string.h>

// CUT
#include "export.h"

#ifdef WIN
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#define TEXT_RED     "\x1b[31m"
#define TEXT_GREEN   "\x1b[32m"
#define TEXT_YELLOW  "\x1b[33m"
#define TEXT_BLUE    "\x1b[34m"
#define TEXT_MAGENTA "\x1b[35m"
#define TEXT_CYAN    "\x1b[36m"
#define TEXT_WHITE   "\x1b[37m"

#define BG_RED       "\x1b[41m"
#define BG_GREEN     "\x1b[42m"
#define BG_YELLOW    "\x1b[43m"
#define BG_BLUE      "\x1b[44m"
#define BG_MAGENTA   "\x1b[45m"
#define BG_CYAN      "\x1b[46m"
#define BG_WHITE     "\x1b[47m"

#define FONT_RESET   "\x1b[0m"
#define FONT_BOLD    "\x1b[1m"
#define FONT_ULINE   "\x1b[4m"

#define LINE_H              "─"
#define LINE_H_BOLD         "━"
#define LINE_H_DOUBLE       "═"
#define LINE_H_2DOT         "╌"
#define LINE_H_BOLD_2DOT    "╍"
#define LINE_H_3DOT         "┄"
#define LINE_H_BOLD_3DOT    "┅"
#define LINE_H_4DOT         "┈"
#define LINE_H_BOLD_4DOT    "┉"
#define LINE_V              "│"
#define LINE_V_BOLD         "┃"
#define LINE_V_DOUBLE       "║"
#define LINE_V_2DOT         "╎"
#define LINE_V_BOLD_2DOT    "╏"
#define LINE_V_3DOT         "┆"
#define LINE_V_BOLD_3DOT    "┇"
#define LINE_V_4DOT         "┊"
#define LINE_V_BOLD_4DOT    "┋"
#define CORNER_TL           "┌"
#define CORNER_TL_BOLD_T    "┍"
#define CORNER_TL_BOLD_L    "┎"
#define CORNER_TL_BOLD      "┏"
#define CORNER_TL_DOUBLE_T  "╒"
#define CORNER_TL_DOUBLE_L  "╓"
#define CORNER_TL_DOUBLE    "╔"
#define CORNER_TL_ROUND     "╭"
#define CORNER_TR           "┐"
#define CORNER_TR_BOLD_T    "┑"
#define CORNER_TR_BOLD_R    "┒"
#define CORNER_TR_BOLD      "┓"
#define CORNER_TR_DOUBLE_T  "╕"
#define CORNER_TR_DOUBLE_R  "╖"
#define CORNER_TR_DOUBLE    "╗"
#define CORNER_TR_ROUND     "╮"
#define CORNER_BL           "└"
#define CORNER_BL_BOLD_B    "┕"
#define CORNER_BL_BOLD_L    "┖"
#define CORNER_BL_BOLD      "┗"
#define CORNER_BL_DOUBLE_B  "╘"
#define CORNER_BL_DOUBLE_L  "╙"
#define CORNER_BL_DOUBLE    "╚"
#define CORNER_BL_ROUND     "╰"
#define CORNER_BR           "┘"
#define CORNER_BR_BOLD_B    "┙"
#define CORNER_BR_BOLD_R    "┚"
#define CORNER_BR_BOLD      "┛"
#define CORNER_BR_DOUBLE_B  "╛"
#define CORNER_BR_DOUBLE_R  "╜"
#define CORNER_BR_DOUBLE    "╝"
#define CORNER_BR_ROUND     "╯"
#define TEE_T               "┬"
#define TEE_T_BOLD_L        "┭"
#define TEE_T_BOLD_R        "┮"
#define TEE_T_BOLD_LR       "┯"
#define TEE_T_BOLD_B        "┰"
#define TEE_T_BOLD_BL       "┱"
#define TEE_T_BOLD_BR       "┲"
#define TEE_T_BOLD          "┳"
#define TEE_T_DOUBLE_LR     "╤"
#define TEE_T_DOUBLE_B      "╥"
#define TEE_T_DOUBLE        "╦"
#define TEE_B               "┴"
#define TEE_B_BOLD_L        "┵"
#define TEE_B_BOLD_R        "┶"
#define TEE_B_BOLD_LR       "┷"
#define TEE_B_BOLD_T        "┸"
#define TEE_B_BOLD_TL       "┹"
#define TEE_B_BOLD_TR       "┺"
#define TEE_B_BOLD          "┻"
#define TEE_B_DOUBLE_LR     "╧"
#define TEE_B_DOUBLE_T      "╨"
#define TEE_B_DOUBLE        "╩"
#define TEE_L               "├"
#define TEE_L_BOLD_R        "┝"
#define TEE_L_BOLD_T        "┞"
#define TEE_L_BOLD_B        "┟"
#define TEE_L_BOLD_TB       "┠"
#define TEE_L_BOLD_TR       "┡"
#define TEE_L_BOLD_BR       "┢"
#define TEE_L_BOLD          "┣"
#define TEE_L_DOUBLE_R      "╞"
#define TEE_L_DOUBLE_TB     "╟"
#define TEE_L_DOUBLE        "╠"
#define TEE_R               "┤"
#define TEE_R_BOLD_L        "┥"
#define TEE_R_BOLD_T        "┦"
#define TEE_R_BOLD_B        "┧"
#define TEE_R_BOLD_TB       "┨"
#define TEE_R_BOLD_TL       "┩"
#define TEE_R_BOLD_BR       "┪"
#define TEE_R_BOLD          "┫"
#define TEE_R_DOUBLE_L      "╡"
#define TEE_R_DOUBLE_TB     "╢"
#define TEE_R_DOUBLE        "╣"
#define CROSS               "┼"
#define CROSS_BOLD_L        "┽"
#define CROSS_BOLD_R        "┾"
#define CROSS_BOLD_LR       "┿"
#define CROSS_BOLD_T        "╀"
#define CROSS_BOLD_B        "╁"
#define CROSS_BOLD_TB       "╂"
#define CROSS_BOLD_TL       "╃"
#define CROSS_BOLD_TR       "╄"
#define CROSS_BOLD_BL       "╅"
#define CROSS_BOLD_BR       "╆"
#define CROSS_BOLD_TLR      "╇"
#define CROSS_BOLD_BLR      "╈"
#define CROSS_BOLD_TBL      "╉"
#define CROSS_BOLD_TBR      "╊"
#define CROSS_BOLD          "╋"
#define CROSS_DOUBLE_LR     "╪"
#define CROSS_DOUBLE_TB     "╫"
#define CROSS_DOUBLE        "╬"

// X, Y coordinates for location on screen
typedef struct coordinate {
  int x;
  int y;
} Coordinate;


PUBLIC Coordinate gettermsize();
PUBLIC void       clearterm();
PUBLIC void       placecursor(int x, int y);
PUBLIC void       movecursor(int x, int y);
PUBLIC void       pushcursor();
PUBLIC void       popcursor();
PUBLIC void       ljust(const char *str, char *buffer, int size);
PUBLIC void       rjust(const char *str, char *buffer, int size);
PUBLIC void       cjust(const char *str, char *buffer, int size);

#endif
