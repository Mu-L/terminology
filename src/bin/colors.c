#include "private.h"
#include <assert.h>
#include <Elementary.h>
#include "config.h"
#include "colors.h"

#define COLORSCHEMES_FILENAME "colorschemes.eet"
#define COLORSCHEMES_VERSION  1

#define CS(R,G,B) {.r = R, .g = G, .b = B, .a = 255}
static Color_Scheme default_colorscheme =
{
   .version = COLORSCHEMES_VERSION,
   .md = {
        .version = 1,
        .name = "default",
        .author = gettext_noop("Terminology's developers"),
        .website = "https://www.enlightenment.org/about-terminology",
        .license = "BSD-2-Clause",
   },
   .def = CS(170, 170, 170), /* #aaaaaa */
   .bg = CS(32, 32, 32), /* #202020 */
   .fg = CS(170, 170, 170), /* #aaaaaa */
   .main = CS(53, 153, 255), /* #3599ff */
   .hl = CS(255,255,255), /* #ffffff */
   .end_sel = CS(255,51,0), /* #ff3300 */
   .tab_missed_1 = CS(255,153,51), /* #ff9933 */
   .tab_missed_2 = CS(255,51,0), /* #ff3300 */
   .tab_missed_3 = CS(255,0,0), /* #ff0000 */
   .tab_missed_over_1 = CS(255,255,64), /* #ffff40 */
   .tab_missed_over_2 = CS(255,153,51), /* #ff9933 */
   .tab_missed_over_3 = CS(255,0,0), /* #ff0000 */
   .tab_title_2 = CS(0,0,0), /* #000000 */
   .ansi[0]  = CS(  0,   0,   0), /* #000000 */
   .ansi[1]  = CS(204,  51,  51), /* #cc3333 */
   .ansi[2]  = CS( 51, 204,  51), /* #33cc33 */
   .ansi[3]  = CS(204, 136,  51), /* #cc8833 */
   .ansi[4]  = CS( 51,  51, 204), /* #3333cc */
   .ansi[5]  = CS(204,  51, 204), /* #cc33cc */
   .ansi[6]  = CS( 51, 204, 204), /* #33cccc */
   .ansi[7]  = CS(204, 204, 204), /* #cccccc */
   .ansi[8]  = CS(102, 102, 102), /* #666666 */
   .ansi[9]  = CS(255, 102, 102), /* #ff6666 */
   .ansi[10] = CS(102, 255, 102), /* #66ff66 */
   .ansi[11] = CS(255, 255, 102), /* #ffff66 */
   .ansi[12] = CS(102, 102, 255), /* #6666ff */
   .ansi[13] = CS(255, 102, 255), /* #ff66ff */
   .ansi[14] = CS(102, 255, 255), /* #66ffff */
   .ansi[15] = CS(255, 255, 255), /* #ffffff */
};
#undef CS

static const Color default_colors[2][2][12] =
{
   { // normal
        { // normal
             { 0xaa, 0xaa, 0xaa, 0xff }, // COL_DEF
             { 0x00, 0x00, 0x00, 0xff }, // COL_BLACK
             { 0xc0, 0x00, 0x00, 0xff }, // COL_RED
             { 0x00, 0xc0, 0x00, 0xff }, // COL_GREEN
             { 0xc0, 0xc0, 0x00, 0xff }, // COL_YELLOW
             { 0x00, 0x00, 0xc0, 0xff }, // COL_BLUE
             { 0xc0, 0x00, 0xc0, 0xff }, // COL_MAGENTA
             { 0x00, 0xc0, 0xc0, 0xff }, // COL_CYAN
             { 0xc0, 0xc0, 0xc0, 0xff }, // COL_WHITE
             { 0x00, 0x00, 0x00, 0x00 }, // COL_INVIS
             { 0x22, 0x22, 0x22, 0xff }, // COL_INVERSE
             { 0xaa, 0xaa, 0xaa, 0xff }, // COL_INVERSEBG
        },
        { // bright/bold
             { 0xee, 0xee, 0xee, 0xff }, // COL_DEF
             { 0xcc, 0xcc, 0xcc, 0xff }, // COL_BLACK
             { 0xcc, 0x88, 0x88, 0xff }, // COL_RED
             { 0x88, 0xcc, 0x88, 0xff }, // COL_GREEN
             { 0xcc, 0xaa, 0x88, 0xff }, // COL_YELLOW
             { 0x88, 0x88, 0xcc, 0xff }, // COL_BLUE
             { 0xcc, 0x88, 0xcc, 0xff }, // COL_MAGENTA
             { 0x88, 0xcc, 0xcc, 0xff }, // COL_CYAN
             { 0xcc, 0xcc, 0xcc, 0xff }, // COL_WHITE
             { 0x00, 0x00, 0x00, 0x00 }, // COL_INVIS
             { 0x11, 0x11, 0x11, 0xff }, // COL_INVERSE
             { 0xee, 0xee, 0xee, 0xff }, // COL_INVERSEBG
        },
   },
   { // intense
        { // normal
             { 0xdd, 0xdd, 0xdd, 0xff }, // COL_DEF
             { 0x80, 0x80, 0x80, 0xff }, // COL_BLACK
             { 0xff, 0x80, 0x80, 0xff }, // COL_RED
             { 0x80, 0xff, 0x80, 0xff }, // COL_GREEN
             { 0xff, 0xff, 0x80, 0xff }, // COL_YELLOW
             { 0x80, 0x80, 0xff, 0xff }, // COL_BLUE
             { 0xff, 0x80, 0xff, 0xff }, // COL_MAGENTA
             { 0x80, 0xff, 0xff, 0xff }, // COL_CYAN
             { 0xff, 0xff, 0xff, 0xff }, // COL_WHITE
             { 0x00, 0x00, 0x00, 0x00 }, // COL_INVIS
             { 0x11, 0x11, 0x11, 0xff }, // COL_INVERSE
             { 0xcc, 0xcc, 0xcc, 0xff }, // COL_INVERSEBG
        },
        { // bright/bold
             { 0xff, 0xff, 0xff, 0xff }, // COL_DEF
             { 0xcc, 0xcc, 0xcc, 0xff }, // COL_BLACK
             { 0xff, 0xcc, 0xcc, 0xff }, // COL_RED
             { 0xcc, 0xff, 0xcc, 0xff }, // COL_GREEN
             { 0xff, 0xff, 0xcc, 0xff }, // COL_YELLOW
             { 0xcc, 0xcc, 0xff, 0xff }, // COL_BLUE
             { 0xff, 0xcc, 0xff, 0xff }, // COL_MAGENTA
             { 0xcc, 0xff, 0xff, 0xff }, // COL_CYAN
             { 0xff, 0xff, 0xff, 0xff }, // COL_WHITE
             { 0x00, 0x00, 0x00, 0x00 }, // COL_INVIS
             { 0x00, 0x00, 0x00, 0xff }, // COL_INVERSE
             { 0xff, 0xff, 0xff, 0xff }, // COL_INVERSEBG
        }
   }
};

static const Color default_colors256[256] =
{
   // basic 16 repeated
   { 0x00, 0x00, 0x00, 0xff }, // COL_BLACK
   { 0xc0, 0x00, 0x00, 0xff }, // COL_RED
   { 0x00, 0xc0, 0x00, 0xff }, // COL_GREEN
   { 0xc0, 0xc0, 0x00, 0xff }, // COL_YELLOW
   { 0x00, 0x00, 0xc0, 0xff }, // COL_BLUE
   { 0xc0, 0x00, 0xc0, 0xff }, // COL_MAGENTA
   { 0x00, 0xc0, 0xc0, 0xff }, // COL_CYAN
   { 0xc0, 0xc0, 0xc0, 0xff }, // COL_WHITE

   { 0x80, 0x80, 0x80, 0xff }, // COL_BLACK
   { 0xff, 0x80, 0x80, 0xff }, // COL_RED
   { 0x80, 0xff, 0x80, 0xff }, // COL_GREEN
   { 0xff, 0xff, 0x80, 0xff }, // COL_YELLOW
   { 0x80, 0x80, 0xff, 0xff }, // COL_BLUE
   { 0xff, 0x80, 0xff, 0xff }, // COL_MAGENTA
   { 0x80, 0xff, 0xff, 0xff }, // COL_CYAN
   { 0xff, 0xff, 0xff, 0xff }, // COL_WHITE

   // pure 6x6x6 colorcube
   { 0x00, 0x00, 0x00, 0xff },
   { 0x00, 0x00, 0x5f, 0xff },
   { 0x00, 0x00, 0x87, 0xff },
   { 0x00, 0x00, 0xaf, 0xff },
   { 0x00, 0x00, 0xd7, 0xff },
   { 0x00, 0x00, 0xff, 0xff },

   { 0x00, 0x5f, 0x00, 0xff },
   { 0x00, 0x5f, 0x5f, 0xff },
   { 0x00, 0x5f, 0x87, 0xff },
   { 0x00, 0x5f, 0xaf, 0xff },
   { 0x00, 0x5f, 0xd7, 0xff },
   { 0x00, 0x5f, 0xff, 0xff },

   { 0x00, 0x87, 0x00, 0xff },
   { 0x00, 0x87, 0x5f, 0xff },
   { 0x00, 0x87, 0x87, 0xff },
   { 0x00, 0x87, 0xaf, 0xff },
   { 0x00, 0x87, 0xd7, 0xff },
   { 0x00, 0x87, 0xff, 0xff },

   { 0x00, 0xaf, 0x00, 0xff },
   { 0x00, 0xaf, 0x5f, 0xff },
   { 0x00, 0xaf, 0x87, 0xff },
   { 0x00, 0xaf, 0xaf, 0xff },
   { 0x00, 0xaf, 0xd7, 0xff },
   { 0x00, 0xaf, 0xff, 0xff },

   { 0x00, 0xd7, 0x00, 0xff },
   { 0x00, 0xd7, 0x5f, 0xff },
   { 0x00, 0xd7, 0x87, 0xff },
   { 0x00, 0xd7, 0xaf, 0xff },
   { 0x00, 0xd7, 0xd7, 0xff },
   { 0x00, 0xd7, 0xff, 0xff },

   { 0x00, 0xff, 0x00, 0xff },
   { 0x00, 0xff, 0x5f, 0xff },
   { 0x00, 0xff, 0x87, 0xff },
   { 0x00, 0xff, 0xaf, 0xff },
   { 0x00, 0xff, 0xd7, 0xff },
   { 0x00, 0xff, 0xff, 0xff },

   { 0x5f, 0x00, 0x00, 0xff },
   { 0x5f, 0x00, 0x5f, 0xff },
   { 0x5f, 0x00, 0x87, 0xff },
   { 0x5f, 0x00, 0xaf, 0xff },
   { 0x5f, 0x00, 0xd7, 0xff },
   { 0x5f, 0x00, 0xff, 0xff },

   { 0x5f, 0x5f, 0x00, 0xff },
   { 0x5f, 0x5f, 0x5f, 0xff },
   { 0x5f, 0x5f, 0x87, 0xff },
   { 0x5f, 0x5f, 0xaf, 0xff },
   { 0x5f, 0x5f, 0xd7, 0xff },
   { 0x5f, 0x5f, 0xff, 0xff },

   { 0x5f, 0x87, 0x00, 0xff },
   { 0x5f, 0x87, 0x5f, 0xff },
   { 0x5f, 0x87, 0x87, 0xff },
   { 0x5f, 0x87, 0xaf, 0xff },
   { 0x5f, 0x87, 0xd7, 0xff },
   { 0x5f, 0x87, 0xff, 0xff },

   { 0x5f, 0xaf, 0x00, 0xff },
   { 0x5f, 0xaf, 0x5f, 0xff },
   { 0x5f, 0xaf, 0x87, 0xff },
   { 0x5f, 0xaf, 0xaf, 0xff },
   { 0x5f, 0xaf, 0xd7, 0xff },
   { 0x5f, 0xaf, 0xff, 0xff },

   { 0x5f, 0xd7, 0x00, 0xff },
   { 0x5f, 0xd7, 0x5f, 0xff },
   { 0x5f, 0xd7, 0x87, 0xff },
   { 0x5f, 0xd7, 0xaf, 0xff },
   { 0x5f, 0xd7, 0xd7, 0xff },
   { 0x5f, 0xd7, 0xff, 0xff },

   { 0x5f, 0xff, 0x00, 0xff },
   { 0x5f, 0xff, 0x5f, 0xff },
   { 0x5f, 0xff, 0x87, 0xff },
   { 0x5f, 0xff, 0xaf, 0xff },
   { 0x5f, 0xff, 0xd7, 0xff },
   { 0x5f, 0xff, 0xff, 0xff },

   { 0x87, 0x00, 0x00, 0xff },
   { 0x87, 0x00, 0x5f, 0xff },
   { 0x87, 0x00, 0x87, 0xff },
   { 0x87, 0x00, 0xaf, 0xff },
   { 0x87, 0x00, 0xd7, 0xff },
   { 0x87, 0x00, 0xff, 0xff },

   { 0x87, 0x5f, 0x00, 0xff },
   { 0x87, 0x5f, 0x5f, 0xff },
   { 0x87, 0x5f, 0x87, 0xff },
   { 0x87, 0x5f, 0xaf, 0xff },
   { 0x87, 0x5f, 0xd7, 0xff },
   { 0x87, 0x5f, 0xff, 0xff },

   { 0x87, 0x87, 0x00, 0xff },
   { 0x87, 0x87, 0x5f, 0xff },
   { 0x87, 0x87, 0x87, 0xff },
   { 0x87, 0x87, 0xaf, 0xff },
   { 0x87, 0x87, 0xd7, 0xff },
   { 0x87, 0x87, 0xff, 0xff },

   { 0x87, 0xaf, 0x00, 0xff },
   { 0x87, 0xaf, 0x5f, 0xff },
   { 0x87, 0xaf, 0x87, 0xff },
   { 0x87, 0xaf, 0xaf, 0xff },
   { 0x87, 0xaf, 0xd7, 0xff },
   { 0x87, 0xaf, 0xff, 0xff },

   { 0x87, 0xd7, 0x00, 0xff },
   { 0x87, 0xd7, 0x5f, 0xff },
   { 0x87, 0xd7, 0x87, 0xff },
   { 0x87, 0xd7, 0xaf, 0xff },
   { 0x87, 0xd7, 0xd7, 0xff },
   { 0x87, 0xd7, 0xff, 0xff },

   { 0x87, 0xff, 0x00, 0xff },
   { 0x87, 0xff, 0x5f, 0xff },
   { 0x87, 0xff, 0x87, 0xff },
   { 0x87, 0xff, 0xaf, 0xff },
   { 0x87, 0xff, 0xd7, 0xff },
   { 0x87, 0xff, 0xff, 0xff },

   { 0xaf, 0x00, 0x00, 0xff },
   { 0xaf, 0x00, 0x5f, 0xff },
   { 0xaf, 0x00, 0x87, 0xff },
   { 0xaf, 0x00, 0xaf, 0xff },
   { 0xaf, 0x00, 0xd7, 0xff },
   { 0xaf, 0x00, 0xff, 0xff },

   { 0xaf, 0x5f, 0x00, 0xff },
   { 0xaf, 0x5f, 0x5f, 0xff },
   { 0xaf, 0x5f, 0x87, 0xff },
   { 0xaf, 0x5f, 0xaf, 0xff },
   { 0xaf, 0x5f, 0xd7, 0xff },
   { 0xaf, 0x5f, 0xff, 0xff },

   { 0xaf, 0x87, 0x00, 0xff },
   { 0xaf, 0x87, 0x5f, 0xff },
   { 0xaf, 0x87, 0x87, 0xff },
   { 0xaf, 0x87, 0xaf, 0xff },
   { 0xaf, 0x87, 0xd7, 0xff },
   { 0xaf, 0x87, 0xff, 0xff },

   { 0xaf, 0xaf, 0x00, 0xff },
   { 0xaf, 0xaf, 0x5f, 0xff },
   { 0xaf, 0xaf, 0x87, 0xff },
   { 0xaf, 0xaf, 0xaf, 0xff },
   { 0xaf, 0xaf, 0xd7, 0xff },
   { 0xaf, 0xaf, 0xff, 0xff },

   { 0xaf, 0xd7, 0x00, 0xff },
   { 0xaf, 0xd7, 0x5f, 0xff },
   { 0xaf, 0xd7, 0x87, 0xff },
   { 0xaf, 0xd7, 0xaf, 0xff },
   { 0xaf, 0xd7, 0xd7, 0xff },
   { 0xaf, 0xd7, 0xff, 0xff },

   { 0xaf, 0xff, 0x00, 0xff },
   { 0xaf, 0xff, 0x5f, 0xff },
   { 0xaf, 0xff, 0x87, 0xff },
   { 0xaf, 0xff, 0xaf, 0xff },
   { 0xaf, 0xff, 0xd7, 0xff },
   { 0xaf, 0xff, 0xff, 0xff },

   { 0xd7, 0x00, 0x00, 0xff },
   { 0xd7, 0x00, 0x5f, 0xff },
   { 0xd7, 0x00, 0x87, 0xff },
   { 0xd7, 0x00, 0xaf, 0xff },
   { 0xd7, 0x00, 0xd7, 0xff },
   { 0xd7, 0x00, 0xff, 0xff },

   { 0xd7, 0x5f, 0x00, 0xff },
   { 0xd7, 0x5f, 0x5f, 0xff },
   { 0xd7, 0x5f, 0x87, 0xff },
   { 0xd7, 0x5f, 0xaf, 0xff },
   { 0xd7, 0x5f, 0xd7, 0xff },
   { 0xd7, 0x5f, 0xff, 0xff },

   { 0xd7, 0x87, 0x00, 0xff },
   { 0xd7, 0x87, 0x5f, 0xff },
   { 0xd7, 0x87, 0x87, 0xff },
   { 0xd7, 0x87, 0xaf, 0xff },
   { 0xd7, 0x87, 0xd7, 0xff },
   { 0xd7, 0x87, 0xff, 0xff },

   { 0xd7, 0xaf, 0x00, 0xff },
   { 0xd7, 0xaf, 0x5f, 0xff },
   { 0xd7, 0xaf, 0x87, 0xff },
   { 0xd7, 0xaf, 0xaf, 0xff },
   { 0xd7, 0xaf, 0xd7, 0xff },
   { 0xd7, 0xaf, 0xff, 0xff },

   { 0xd7, 0xd7, 0x00, 0xff },
   { 0xd7, 0xd7, 0x5f, 0xff },
   { 0xd7, 0xd7, 0x87, 0xff },
   { 0xd7, 0xd7, 0xaf, 0xff },
   { 0xd7, 0xd7, 0xd7, 0xff },
   { 0xd7, 0xd7, 0xff, 0xff },

   { 0xd7, 0xff, 0x00, 0xff },
   { 0xd7, 0xff, 0x5f, 0xff },
   { 0xd7, 0xff, 0x87, 0xff },
   { 0xd7, 0xff, 0xaf, 0xff },
   { 0xd7, 0xff, 0xd7, 0xff },
   { 0xd7, 0xff, 0xff, 0xff },


   { 0xff, 0x00, 0x00, 0xff },
   { 0xff, 0x00, 0x5f, 0xff },
   { 0xff, 0x00, 0x87, 0xff },
   { 0xff, 0x00, 0xaf, 0xff },
   { 0xff, 0x00, 0xd7, 0xff },
   { 0xff, 0x00, 0xff, 0xff },

   { 0xff, 0x5f, 0x00, 0xff },
   { 0xff, 0x5f, 0x5f, 0xff },
   { 0xff, 0x5f, 0x87, 0xff },
   { 0xff, 0x5f, 0xaf, 0xff },
   { 0xff, 0x5f, 0xd7, 0xff },
   { 0xff, 0x5f, 0xff, 0xff },

   { 0xff, 0x87, 0x00, 0xff },
   { 0xff, 0x87, 0x5f, 0xff },
   { 0xff, 0x87, 0x87, 0xff },
   { 0xff, 0x87, 0xaf, 0xff },
   { 0xff, 0x87, 0xd7, 0xff },
   { 0xff, 0x87, 0xff, 0xff },

   { 0xff, 0xaf, 0x00, 0xff },
   { 0xff, 0xaf, 0x5f, 0xff },
   { 0xff, 0xaf, 0x87, 0xff },
   { 0xff, 0xaf, 0xaf, 0xff },
   { 0xff, 0xaf, 0xd7, 0xff },
   { 0xff, 0xaf, 0xff, 0xff },

   { 0xff, 0xd7, 0x00, 0xff },
   { 0xff, 0xd7, 0x5f, 0xff },
   { 0xff, 0xd7, 0x87, 0xff },
   { 0xff, 0xd7, 0xaf, 0xff },
   { 0xff, 0xd7, 0xd7, 0xff },
   { 0xff, 0xd7, 0xff, 0xff },

   { 0xff, 0xff, 0x00, 0xff },
   { 0xff, 0xff, 0x5f, 0xff },
   { 0xff, 0xff, 0x87, 0xff },
   { 0xff, 0xff, 0xaf, 0xff },
   { 0xff, 0xff, 0xd7, 0xff },
   { 0xff, 0xff, 0xff, 0xff },

   // greyscale ramp (24 not including black and white, so 26 if included)
   { 0x08, 0x08, 0x08, 0xff },
   { 0x12, 0x12, 0x12, 0xff },
   { 0x1c, 0x1c, 0x1c, 0xff },
   { 0x26, 0x26, 0x26, 0xff },
   { 0x30, 0x30, 0x30, 0xff },
   { 0x3a, 0x3a, 0x3a, 0xff },
   { 0x44, 0x44, 0x44, 0xff },
   { 0x4e, 0x4e, 0x4e, 0xff },
   { 0x58, 0x58, 0x58, 0xff },
   { 0x62, 0x62, 0x62, 0xff },
   { 0x6c, 0x6c, 0x6c, 0xff },
   { 0x76, 0x76, 0x76, 0xff },
   { 0x80, 0x80, 0x80, 0xff },
   { 0x8a, 0x8a, 0x8a, 0xff },
   { 0x94, 0x94, 0x94, 0xff },
   { 0x9e, 0x9e, 0x9e, 0xff },
   { 0xa8, 0xa8, 0xa8, 0xff },
   { 0xb2, 0xb2, 0xb2, 0xff },
   { 0xbc, 0xbc, 0xbc, 0xff },
   { 0xc6, 0xc6, 0xc6, 0xff },
   { 0xd0, 0xd0, 0xd0, 0xff },
   { 0xda, 0xda, 0xda, 0xff },
   { 0xe4, 0xe4, 0xe4, 0xff },
   { 0xee, 0xee, 0xee, 0xff },
};

static Eet_Data_Descriptor *edd_cs = NULL;
static Eet_Data_Descriptor *edd_color = NULL;

void
colors_term_init(Evas_Object *textgrid,
                 const Evas_Object *bg,
                 const Config *config)
{
   int c;
   char buf[32];
   int r, g , b, a;
   const Color *color;

   for (c = 0; c < (4 * 12); c++)
     {
        int n = c + (24 * (c / 24));
        if (config->colors_use)
          {
             r = config->colors[c].r;
             g = config->colors[c].g;
             b = config->colors[c].b;
             a = config->colors[c].a;
          }
        else
          {
             snprintf(buf, sizeof(buf) - 1, "c%i", c);
             if (!edje_object_color_class_get(bg, buf,
                                              &r,
                                              &g,
                                              &b,
                                              &a,
                                              NULL, NULL, NULL, NULL,
                                              NULL, NULL, NULL, NULL))
               {
                  color = &default_colors[c / 24][(c % 24) / 12][c % 12];
                  r = color->r;
                  g = color->g;
                  b = color->b;
                  a = color->a;
               }
          }
        /* normal */
        evas_object_textgrid_palette_set(
           textgrid, EVAS_TEXTGRID_PALETTE_STANDARD, n,
           r, g, b, a);

        /* faint */
        evas_object_textgrid_palette_set(
           textgrid, EVAS_TEXTGRID_PALETTE_STANDARD, n + 24,
           r / 2, g / 2, b / 2, a / 2);
     }
   for (c = 48; c < 72; c++)
     {
        if (!config->colors_use)
          {
             snprintf(buf, sizeof(buf) - 1, "c%i", c);
             if (edje_object_color_class_get(bg, buf,
                                             &r,
                                             &g,
                                             &b,
                                             &a,
                                             NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL))
               {
                   /* faint */
                   evas_object_textgrid_palette_set(
                       textgrid, EVAS_TEXTGRID_PALETTE_STANDARD, c,
                       r, g, b, a);
               }
          }
     }
   for (c = 72; c < 96; c++)
     {
        if (!config->colors_use)
          {
             snprintf(buf, sizeof(buf) - 1, "c%i", c);
             if (edje_object_color_class_get(bg, buf,
                                             &r,
                                             &g,
                                             &b,
                                             &a,
                                             NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL))
               {
                   /* faint */
                   evas_object_textgrid_palette_set(
                       textgrid, EVAS_TEXTGRID_PALETTE_STANDARD, c - 48,
                       r, g, b, a);
               }
          }
     }
   for (c = 0; c < 256; c++)
     {
        snprintf(buf, sizeof(buf) - 1, "C%i", c);

        if (!edje_object_color_class_get(bg, buf,
                                         &r,
                                         &g,
                                         &b,
                                         &a,
                                         NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL, NULL))
          {
             color = &default_colors256[c];
             r = color->r;
             g = color->g;
             b = color->b;
             a = color->a;
          }
        evas_object_textgrid_palette_set(
           textgrid, EVAS_TEXTGRID_PALETTE_EXTENDED, c,
           r, g, b, a);
     }
}

void
colors_standard_get(int set, int col,
                    unsigned char *r,
                    unsigned char *g,
                    unsigned char *b,
                    unsigned char *a)
{
   int s1, s2;
   assert((set >= 0) && (set < 4));

   s1 = set / 2;
   s2 = set % 2;
   *r = default_colors[s1][s2][col].r;
   *g = default_colors[s1][s2][col].g;
   *b = default_colors[s1][s2][col].b;
   *a = default_colors[s1][s2][col].a;
}

void
colors_256_get(int col,
               unsigned char *r,
               unsigned char *g,
               unsigned char *b,
               unsigned char *a)
{
   assert(col < 256);
   *r = default_colors256[col].r;
   *g = default_colors256[col].g;
   *b = default_colors256[col].b;
   *a = default_colors256[col].a;
}

void
color_scheme_apply(Evas_Object *edje,
                   const Config *config)
{
   if (!eina_str_has_suffix(config->theme, "/nord.edj"))
     return;
#define CS_BG       46,   52,  64, 255
#define CS_FG       216, 222, 233, 255
#define CS_MAIN     137, 152, 161, 255
#define CS_HL       255, 255, 255, 255
#define CS_RAGE     255,  51,   0, 255
#define CS_RED      255,   0,   0, 255
#define CS_ORANGE   255, 153,  51, 255
#define CS_BLACK      0,   0,   0, 255
#define CS_DARK      64,  64,  64, 255
#define CS_YELLOW   255, 255,  64, 255
   edje_object_color_class_set(edje, "BG", CS_BG, CS_BG, CS_BG);
   edje_object_color_class_set(edje, "FG", CS_BG, CS_BG, CS_BG);
   edje_object_color_class_set(edje, "CURSOR", CS_MAIN, CS_MAIN, CS_MAIN);
   edje_object_color_class_set(edje, "CURSOR_HIGHLIGHT", CS_HL, CS_HL, CS_HL);
   edje_object_color_class_set(edje, "GLOW", CS_MAIN, CS_MAIN, CS_MAIN);
   edje_object_color_class_set(edje, "GLOW_HIGHLIGHT", CS_HL, CS_HL, CS_HL);
   edje_object_color_class_set(edje, "GLOW_TXT", CS_MAIN, CS_MAIN, CS_MAIN);
   edje_object_color_class_set(edje, "GLOW_HIGHLIGHT", CS_HL, CS_MAIN, CS_MAIN);
   edje_object_color_class_set(edje, "END_SELECTION", CS_RAGE, CS_RAGE, CS_RAGE);
   edje_object_color_class_set(edje, "TAB_MISSED", CS_ORANGE, CS_RAGE, CS_RED);
   edje_object_color_class_set(edje, "TAB_MISSED_OVER", CS_YELLOW, CS_ORANGE, CS_RED);
   edje_object_color_class_set(edje, "TAB_TITLE", CS_FG, CS_BLACK, CS_BG);
   edje_object_color_class_set(edje, "BG_SENDFILE", CS_DARK, CS_DARK, CS_DARK);
   edje_object_color_class_set(edje, "SHINE", CS_HL, CS_HL, CS_HL);

#define CS_SET(K, C) \
   edje_object_color_class_set(edje, K, C, C, C)

#define CS_DEF       216, 222, 233, 255 /* #D8DEE9 */
#define CS_ANSI00     59,  66,  82, 255 /* #3B4252 */
#define CS_ANSI01    191,  97, 106, 255 /* #BF616A */
#define CS_ANSI02    163, 190, 140, 255 /* #A3BE8C */
#define CS_ANSI03    235, 203, 139, 255 /* #EBCB8B */
#define CS_ANSI04    129, 161, 193, 255 /* #81A1C1 */
#define CS_ANSI05    180, 142, 173, 255 /* #B38EAD */
#define CS_ANSI06    136, 192, 208, 255 /* #88C0D0 */
#define CS_ANSI07    229, 233, 248, 255 /* #E5E9F0 */
#define CS_ANSI08     76,  86, 106, 255 /* #4C566A */
#define CS_ANSI09    191,  97, 106, 255 /* #BF616A */
#define CS_ANSI10    163, 190, 140, 255 /* #A3BE8C */
#define CS_ANSI11    235, 203, 139, 255 /* #EBCB8B */
#define CS_ANSI12    129, 161, 193, 255 /* #81A1C1 */
#define CS_ANSI13    180, 142, 173, 255 /* #B38EAD */
#define CS_ANSI14    143, 188, 187, 255 /* #8FBCBB */
#define CS_ANSI15    236, 239, 244, 255 /* #ECEFF4 */

   CS_SET("C0",  CS_ANSI00);
   CS_SET("C1",  CS_ANSI01);
   CS_SET("C2",  CS_ANSI02);
   CS_SET("C3",  CS_ANSI03);
   CS_SET("C4",  CS_ANSI04);
   CS_SET("C5",  CS_ANSI05);
   CS_SET("C6",  CS_ANSI06);
   CS_SET("C7",  CS_ANSI07);

   CS_SET("C8",  CS_ANSI08);
   CS_SET("C9",  CS_ANSI09);
   CS_SET("C10", CS_ANSI10);
   CS_SET("C11", CS_ANSI11);
   CS_SET("C12", CS_ANSI12);
   CS_SET("C13", CS_ANSI13);
   CS_SET("C14", CS_ANSI14);
   CS_SET("C14", CS_ANSI15);

   CS_SET("c0", CS_DEF);
   CS_SET("c1", CS_ANSI00);
   CS_SET("c2", CS_ANSI01);
   CS_SET("c3", CS_ANSI02);
   CS_SET("c4", CS_ANSI03);
   CS_SET("c5", CS_ANSI04);
   CS_SET("c6", CS_ANSI05);
   CS_SET("c7", CS_ANSI06);
   CS_SET("c8", CS_ANSI07);

   CS_SET("c11", CS_DEF);

   CS_SET("c12", CS_ANSI15);
   CS_SET("c13", CS_ANSI08);
   CS_SET("c14", CS_ANSI09);
   CS_SET("c15", CS_ANSI10);
   CS_SET("c16", CS_ANSI11);
   CS_SET("c17", CS_ANSI12);
   CS_SET("c18", CS_ANSI13);
   CS_SET("c19", CS_ANSI14);
   CS_SET("c20", CS_ANSI15);

   CS_SET("c25", CS_ANSI08);
   CS_SET("c26", CS_ANSI09);
   CS_SET("c27", CS_ANSI10);
   CS_SET("c28", CS_ANSI11);
   CS_SET("c29", CS_ANSI12);
   CS_SET("c30", CS_ANSI13);
   CS_SET("c31", CS_ANSI14);
   CS_SET("c32", CS_ANSI15);

   CS_SET("c37", CS_ANSI08);
   CS_SET("c38", CS_ANSI09);
   CS_SET("c39", CS_ANSI10);
   CS_SET("c40", CS_ANSI11);
   CS_SET("c41", CS_ANSI12);
   CS_SET("c42", CS_ANSI13);
   CS_SET("c43", CS_ANSI14);
   CS_SET("c44", CS_ANSI15);

#undef CS_DEF
#undef CS_ANSI00
#undef CS_ANSI01
#undef CS_ANSI02
#undef CS_ANSI03
#undef CS_ANSI04
#undef CS_ANSI05
#undef CS_ANSI06
#undef CS_ANSI07
#undef CS_ANSI08
#undef CS_ANSI09
#undef CS_ANSI10
#undef CS_ANSI11
#undef CS_ANSI12
#undef CS_ANSI13
#undef CS_ANSI14
#undef CS_ANSI15

#undef CS_BG
#undef CS_FG
#undef CS_MAIN
#undef CS_HL
#undef CS_RAGE
#undef CS_RED
#undef CS_ORANGE
#undef CS_BLACK
#undef CS_DARK
#undef CS_YELLOW
#undef CS_SET
}

Color_Scheme *
_color_scheme_from_file(const char *path, const char *name)
{
   Eet_File *ef;
   Color_Scheme *cs;

   ef = eet_open(path, EET_FILE_MODE_READ);
   if (!ef)
     return NULL;

   cs = eet_data_read(ef, edd_cs, name);
   eet_close(ef);

   return cs;
}

Color_Scheme *
color_scheme_get(const char *name)
{
   static char path_user[PATH_MAX] = "";
   static char path_app[PATH_MAX] = "";
   Color_Scheme *cs_user;
   Color_Scheme *cs_app;

   snprintf(path_user, sizeof(path_user) - 1,
            "%s/terminology/" COLORSCHEMES_FILENAME,
            efreet_config_home_get());

   snprintf(path_app, sizeof(path_app) - 1,
            "%s/" COLORSCHEMES_FILENAME,
            elm_app_data_dir_get());


   cs_user = _color_scheme_from_file(path_user, name);
   cs_app = _color_scheme_from_file(path_app, name);

   if (cs_user && cs_app)
     {
        /* Prefer user file */
        if (cs_user->md.version >= cs_app->md.version)
          return cs_user;
        else
          return cs_app;
     }
   else if (cs_user)
     return cs_user;
   else if (cs_app)
     return cs_app;
   else
     return NULL;
}

void
colors_init(void)
{
   Eet_Data_Descriptor_Class eddc;

   eet_eina_stream_data_descriptor_class_set
     (&eddc, sizeof(eddc), "Color", sizeof(Color));
   edd_color = eet_data_descriptor_stream_new(&eddc);

   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_color, Color, "r", r, EET_T_UCHAR);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_color, Color, "g", g, EET_T_UCHAR);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_color, Color, "b", b, EET_T_UCHAR);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_color, Color, "a", a, EET_T_UCHAR);

   eet_eina_stream_data_descriptor_class_set
     (&eddc, sizeof(eddc), "Color_Scheme", sizeof(Color_Scheme));
   edd_cs = eet_data_descriptor_stream_new(&eddc);

   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_cs, Color_Scheme, "version", version, EET_T_INT);

   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_cs, Color_Scheme, "md.version", md.version, EET_T_INT);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_cs, Color_Scheme, "md.name", md.name, EET_T_STRING);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_cs, Color_Scheme, "md.author", md.author, EET_T_STRING);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_cs, Color_Scheme, "md.website", md.website, EET_T_STRING);
   EET_DATA_DESCRIPTOR_ADD_BASIC
     (edd_cs, Color_Scheme, "md.license", md.license, EET_T_STRING);

   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "def", def, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "bg", bg, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "fg", fg, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "main", main, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "hl", hl, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "end_sel", end_sel, edd_color);

   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_missed_1", tab_missed_1, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_missed_2", tab_missed_2, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_missed_3", tab_missed_3, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_missed_over_1", tab_missed_over_1, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_missed_over_2", tab_missed_over_2, edd_color);
   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_missed_over_3", tab_missed_over_3, edd_color);

   EET_DATA_DESCRIPTOR_ADD_SUB_NESTED
      (edd_cs, Color_Scheme, "tab_title_2", tab_title_2, edd_color);

   EET_DATA_DESCRIPTOR_ADD_ARRAY
     (edd_cs, Color_Scheme, "ansi", ansi, edd_color);

#if ENABLE_NLS
   default_colorscheme.md.author = gettext(default_colorscheme.md.author);
#endif
}

void
colors_shutdown(void)
{
   eet_data_descriptor_free(edd_cs);
   edd_cs = NULL;

   eet_data_descriptor_free(edd_color);
   edd_color = NULL;
}
