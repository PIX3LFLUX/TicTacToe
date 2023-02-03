#ifndef BOARD_H
#define BOARD_H

#include <string.h>
#include <NeoPixelBus.h>

/** Board layout front view 11 x 11 matrix
 * 
 * Pixel position ( x, y ) - Direction
 * 
 * (0|0)    (1|0)     (2|0)    (3|0)    (4|0)    (5|0)    (6|0)    (7|0)    (8|0)    (9|0)    (10|0)
 * (0|1)    (1|1)     (2|1)    (3|1)    (4|1)    (5|1)    (6|1)    (7|1)    (8|1)    (9|1)    (10|1)
 * (0|2)    (1|2)     (2|2)    (3|2)    (4|2)    (5|2)    (6|2)    (7|2)    (8|2)    (9|2)    (10|2)
 * (0|3)    (1|3)     (2|3)    (3|3)    (4|3)    (5|3)    (6|3)    (7|3)    (8|3)    (9|3)    (10|3)
 * (0|4)    (1|4)     (2|4)    (3|4)    (4|4)    (5|4)    (6|4)    (7|4)    (8|4)    (9|4)    (10|4)
 * (0|5)    (1|5)     (2|5)    (3|5)    (4|5)    (5|5)    (6|5)    (7|5)    (8|5)    (9|5)    (10|5)
 * (0|6)    (1|6)     (2|6)    (3|6)    (4|6)    (5|6)    (6|6)    (7|6)    (8|6)    (9|6)    (10|6)
 * (0|7)    (1|7)     (2|7)    (3|7)    (4|7)    (5|7)    (6|7)    (7|7)    (8|7)    (9|7)    (10|7)
 * (0|8)    (1|8)     (2|8)    (3|8)    (4|8)    (5|8)    (6|8)    (7|8)    (8|8)    (9|8)    (10|8)
 * (0|9)    (1|9)     (2|9)    (3|9)    (4|9)    (5|9)    (6|9)    (7|9)    (8|9)    (9|9)    (10|9)
 * (0|10)   (1|10)    (2|10)   (3|10)   (4|10)   (5|10)   (6|10)   (7|10)   (8|10)   (9|10)   (10|10)
 */

#define BOARD_WIDTH 11
#define BOARD_HEIGHT 11
#define PIXEL_COUNT 121

typedef struct board_colors
{
    HtmlColor grid_color;
    HtmlColor text_color;
    HtmlColor x_color;
    HtmlColor o_color;
    HtmlColor black;
    //HtmlColor white;
}BOARD_COLORS;

typedef struct
{
    char character;
    uint8_t array_size;
    unsigned char *char_array;
}CHARACTER;

typedef struct text_array
{
    int rotate_index;    // required for rotating text through the board
    int array_size;
    unsigned char *text_array;
}TEXT_ARRAY;

void initialize_board();
void set_color_x(uint32_t color);
void set_color_o(uint32_t color);
void set_color_grid(uint32_t color);
void set_color_text(uint32_t color);
int set_pixel_text( TEXT_ARRAY *text_array );


/**
 * @brief Only A - Z, 0 - 9, ' ', ':', '.'
 * 
 * @param text 
 * @return TEXT_ARRAY* 
 */
TEXT_ARRAY *build_text_array( const char *text );
void set_grid();
void set_board_to_0();
void show_board();

/* Fields:
    | 0 | 1 | 2 |
    | 3 | 4 | 5 |
    | 6 | 7 | 8 |
*/

/**
 * @brief Number of the field to set
 * 
 * @param number Counts from 0 - 8
 */
void set_x( uint8_t number );    // 0 - 8

/**
 * @brief Number of the field to set
 * 
 * @param number Counts from 0 - 8
 */
void set_o( uint8_t number );    // 0 - 8


#endif