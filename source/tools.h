#ifndef TOOLS_H
#define TOOLS_H

// ---------------------------------------------------------------------------
//                       FUNCTIONS!
// ---------------------------------------------------------------------------
#define UNUSED(param) ((void)((param)))

// ---------------------------------------------------------------------------
//                       MODE3 MACROS
// ---------------------------------------------------------------------------
#define OFFSET(row, col, width) ((col)+(width)*(row))

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31, 31, 31)
#define RED COLOR(31, 0, 0)
#define GREEN COLOR(0, 31, 0)
#define BLUE COLOR(0, 0, 31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK COLOR(0, 0, 0)
#define GRAY COLOR(5, 5, 5)

// The size of the GBA Screen
#define TOP_WIDTH 800
#define TOP_HEIGHT 240
#define BOT_WIDTH 400
#define BOT_HEIGHT 240

#endif
