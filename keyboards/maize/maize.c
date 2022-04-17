/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "maize.h"

/*
    ws2812_init();
    palSetLineMode(RGB_DI_PIN, WS2812_OUTPUT_MODE);
     ws2812_setleds(LED_TYPE* ledarray, uint16_t leds)
*/

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    {  19,  18,  13,  12,   5,   4 },
    {  20,  17,  14,  11,   6,   3 },
    {  21,  16,  15,  10,   7,   2 },
    { 255, 255, 155,   9,   8,   1 },   // NO_LED = 255
    {  40,  39,  34,  33,  26,  25 },
    {  41,  38,  35,  32,  27,  24 },
    {  42,  37,  36,  31,  28,  23 },
    { 255, 255, 255,  30,  29,  21 }
}, {
    {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 },
    {  85,  39 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  68,  37 }, {  80,  58 },
    {  60,  55 }, {  50,  35 }, {  50,  13 }, {  50,   0 }, {  33,   3 }, {  33,  20 }, {  33,  37 },
    {  16,  42 }, {  16,  24 }, {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 }, { 139,  16 },
    { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 }, { 129,  63 }, { 139,  39 },
    { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 }, { 156,  37 }, { 144,  58 }, { 164,  55 },
    { 174,  35 }, { 174,  13 }, { 174,   0 }, { 191,   3 }, { 191,  20 }, { 191,  37 }, { 208,  42 },
    { 208,  24 }, { 208,   7 }, { 224,   7 }, { 224,  24 }, { 224,  41 }
}, {
    4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4, 4,
} };

#endif

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 19 18 13 12 05 04   0
  //    __    __    __
  // 20 17 14 11 06 03   1
  //    __    __    __
  // 21 16 15 10 07 02   2
  //
  //          09 08 01   3
  //
  // Right
  // 0  1  2  3  4  5
  //                   ROWS
  // 19 18 13 12 05 04   4
  //    __    __    __
  // 20 17 14 11 06 03   5
  //    __    __    __
  // 21 16 15 10 07 02   6
  //
  //          09 08 01   7
  //
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 19 18 13 12 05 04       04 05 12 13 18 19  0
  //    __    __    __       __    __    __
  // 20 17 14 11 06 03       03 06 11 14 17 20  1
  //    __                               __
  // 21 16 15 10 07 02       02 07 10 15 16 21  2
  //          __    __       __    __
  //           09 08 01     01 08 09            3
