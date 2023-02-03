#include "panel.h"

NeoPixelBus<NeoRgbFeature, NeoWs2811Method> strip( PIXEL_COUNT );   // Global pixel strip of 121 pixels
NeoTopology<ColumnMajorAlternating270Layout> topo( BOARD_HEIGHT, BOARD_WIDTH ); // Array of 11 x 11 pixels
BOARD_COLORS s_panel;   // Global struct of html pixel colors for x, o, grid and text

void initialize_colors();
static void parse_character( CHARACTER * );
TEXT_ARRAY *build_text_array( const char * );
int set_pixel_text( TEXT_ARRAY *text_array );




void initialize_board(){

    initialize_colors();
    strip.Begin();          // this resets all the neopixels to an off state
    strip.Show();
}

void initialize_colors()
{
    s_panel.grid_color.Color = 0;
    s_panel.text_color.Color = 0;
    s_panel.x_color.Color = 0;
    s_panel.o_color.Color = 0;
    s_panel.black.Color = 0;
}

void show_board()
{
    strip.Show();
}

void set_color_grid( uint32_t color)
{
    s_panel.grid_color.Color = color;
}

void set_color_text( uint32_t color)
{
    s_panel.text_color.Color = color;
}

void set_color_x( uint32_t color)
{
    s_panel.x_color.Color = color;
}

void set_color_o( uint32_t color)
{
    s_panel.o_color.Color = color;
}

void set_grid(){

    int x, y;

    for( x = 3; x < BOARD_WIDTH; x = x + 4){    // Set grid lines in x direction
        for( y = 0; y < BOARD_HEIGHT; y++){
            strip.SetPixelColor( topo.Map( x, y ), s_panel.grid_color );
        }
    }

    for( y = 3; y < BOARD_HEIGHT; y = y + 4){   // Set grid lines in y direction
        for( x = 0; x < BOARD_WIDTH; x++){
            strip.SetPixelColor( topo.Map( x, y ), s_panel.grid_color );
        }
    }
}

void set_x( const uint8_t number )
{
    /* 
        | 0 | 1 | 2 |
        | 3 | 4 | 5 |
        | 6 | 7 | 8 |
    */
    switch (number)
    {
        case 0:
            strip.SetPixelColor( topo.Map( 0, 0), s_panel.x_color );    // topo.Map(x, y)
            strip.SetPixelColor( topo.Map( 2, 0), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 1, 1), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 0, 2), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 2, 2), s_panel.x_color );
            break;

        case 1:
            strip.SetPixelColor( topo.Map( 4, 0), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 6, 0), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 5, 1), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 4, 2), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 6, 2), s_panel.x_color );
            break;

        case 2:
            strip.SetPixelColor( topo.Map( 8, 0), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 10, 0), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 9, 1), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 8, 2), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 10, 2), s_panel.x_color );
            break;

        case 3:
            strip.SetPixelColor( topo.Map( 0, 4), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 2, 4), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 1, 5), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 0, 6), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 2, 6), s_panel.x_color );
            break;

        case 4:
            strip.SetPixelColor( topo.Map( 4, 4), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 6, 4), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 5, 5), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 4, 6), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 6, 6), s_panel.x_color );
            break;

        case 5:
            strip.SetPixelColor( topo.Map( 8, 4), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 10, 4), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 9, 5), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 8, 6), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 10, 6), s_panel.x_color );
            break;

        case 6:
            strip.SetPixelColor( topo.Map( 0, 8), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 2, 8), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 1, 9), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 0, 10), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 2, 10), s_panel.x_color );
            break;

        case 7:
            strip.SetPixelColor( topo.Map( 4, 8), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 6, 8), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 5, 9), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 4, 10), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 6, 10), s_panel.x_color );
            break;

        case 8:
            strip.SetPixelColor( topo.Map( 8, 8), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 10, 8), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 9, 9), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 8, 10), s_panel.x_color );
            strip.SetPixelColor( topo.Map( 10, 10), s_panel.x_color );
            break;

        default:
            // Should not happen
            break;
    }
}

void set_o( const uint8_t number )
{
    /* 
        | 0 | 1 | 2 |
        | 3 | 4 | 5 |
        | 6 | 7 | 8 |
    */
    switch (number)
    {
        case 0:
            strip.SetPixelColor( topo.Map( 0, 1), s_panel.o_color );    // topo.Map(x, y)
            strip.SetPixelColor( topo.Map( 1, 0), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 1, 2), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 2, 1), s_panel.o_color );
            break;

        case 1:
            strip.SetPixelColor( topo.Map( 4, 1), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 5, 0), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 5, 2), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 6, 1), s_panel.o_color );
            break;

        case 2:
            strip.SetPixelColor( topo.Map( 8, 1), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 9, 0), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 9, 2), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 10, 1), s_panel.o_color );
            break;

        case 3:
            strip.SetPixelColor( topo.Map( 0, 5), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 1, 4), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 1, 6), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 2, 5), s_panel.o_color );
            break;

        case 4:
            strip.SetPixelColor( topo.Map( 4, 5), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 5, 4), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 5, 6), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 6, 5), s_panel.o_color );
            break;

        case 5:
            strip.SetPixelColor( topo.Map( 8, 5), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 9, 4), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 9, 6), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 10, 5), s_panel.o_color );
            break;

        case 6:
            strip.SetPixelColor( topo.Map( 0, 9), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 1, 8), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 1, 10), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 2, 9), s_panel.o_color );
            break;

        case 7:
            strip.SetPixelColor( topo.Map( 4, 9), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 5, 8), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 5, 10), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 6, 9), s_panel.o_color );
            break;

        case 8:
            strip.SetPixelColor( topo.Map( 8, 9), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 9, 8), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 9, 10), s_panel.o_color );
            strip.SetPixelColor( topo.Map( 10, 9), s_panel.o_color );
            break;

        default:
            // Should not happen
            break;
    }
}

void set_board_to_0()
{
    strip.ClearTo(0); // Set every pixel to black
}

int set_pixel_text( TEXT_ARRAY *text_array )
{
    int x, y;
    unsigned char bit_mask = 1;

    if( ( text_array == NULL ) || ( text_array->text_array == NULL ) )
    {
        return -1;
    }

    for( x = 0; x < BOARD_WIDTH; x++ )  // Rotate text
    {
        for( y = 0; y < 7; y++ )    // Height of text is 7 pixel
        {
            if( text_array->text_array[ ( text_array->rotate_index + x) % ( text_array->array_size ) ] & bit_mask )
            {
                strip.SetPixelColor( topo.Map( x, 8 - y), s_panel.text_color );
            }
            else
            {
                strip.SetPixelColor( topo.Map( x, 8 - y), s_panel.black );
            }
            bit_mask <<= 1; // Shifts between bit 0 and 7 of text_array[x]
        }
        bit_mask = 1;   // Reset bit_mask for next iteration in x-direction
    }
    text_array->rotate_index = (text_array->rotate_index + 1) % (text_array->array_size);   // Increase rotate_index by 1 and save this value for the next function call
    
    return 0;
}

TEXT_ARRAY *build_text_array( const char *text )
{
    int i, tmp = 0;
    int oldSize = 0;
    CHARACTER *character_struct;
    TEXT_ARRAY *text_array;

    if( text != NULL )
    {
        tmp = strlen( text );
        character_struct = ( CHARACTER * )calloc( 1, sizeof( CHARACTER ) );
        if( character_struct == NULL )
        {
            return NULL;
        }

        text_array = ( TEXT_ARRAY *)calloc( 1, sizeof( TEXT_ARRAY ) );
        if( text_array == NULL )
        {
            return NULL;
        }


        for( i = 0; i < tmp; i++ )
        {
            if( ( text[i] >= '0' && text[i] <= '9' ) || ( text[i] >= 'A' && text[i] <= 'Z') || ( text[i] == ':' ) || ( text[i] == '.' ) || ( text[i] == ' '))
            {
                character_struct->array_size = 0;
                character_struct->character = text[i];

                parse_character( character_struct );
                
                if( character_struct->array_size == 0 )
                {
                    if( oldSize != 0 )                      // text_array->text_array is not initialized at this point when oldSize == 0
                    {
                        free( text_array->text_array );
                    }
                    free( text_array );

                    return NULL;
                }
                else
                {
                    oldSize = text_array->array_size;
                    text_array->array_size = text_array->array_size + character_struct->array_size + 1;

                    text_array->text_array = ( unsigned char * )realloc( text_array->text_array, text_array->array_size );
                    memcpy( text_array->text_array + oldSize, character_struct->char_array, character_struct->array_size );
                    text_array->text_array[ text_array->array_size - 1] = 0x00; // Space between characters
                    free( character_struct->char_array );
                }
            }
        }
    }
    else
    {
        return NULL;
    }
    free( character_struct );

    return text_array;
}

static void parse_character( CHARACTER *character_struct )
{
    switch ( character_struct->character )
    {
        case 'A':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3F;  // 0 0 1 1 1 1 1 1
            character_struct->char_array[3] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[2] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[1] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[0] = 0x3F;  // 0 0 1 1 1 1 1 1
            break;
        }

        case 'B':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x36;  // 0 0 1 1 0 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }
        case 'C':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[3] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[1] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[0] = 0x3E;  // 0 0 1 1 1 1 1 0 
            break;
        }

        case 'D':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3E;  // 0 0 1 1 1 1 1 0
            character_struct->char_array[3] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[1] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'E':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'F':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[3] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[2] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[1] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'G':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x0E;  // 0 0 0 0 1 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[1] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[0] = 0x3E;  // 0 0 1 1 1 1 1 0
            break;
        }

        case 'H':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[3] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[2] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[1] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'I':
        {
            character_struct->char_array = (unsigned char *) calloc( 1, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 1;

            *(character_struct->char_array) = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'J':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7E;  // 0 1 1 1 1 1 1 0
            character_struct->char_array[3] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[1] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[0] = 0x02;  // 0 0 0 0 0 0 1 0
            break;
        }

        case 'K':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[3] = 0x22;  // 0 0 1 0 0 0 1 0
            character_struct->char_array[2] = 0x14;  // 0 0 0 1 0 1 0 0
            character_struct->char_array[1] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'L':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[3] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[2] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[1] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'M':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[3] = 0x20;  // 0 0 1 0 0 0 0 0
            character_struct->char_array[2] = 0x10;  // 0 0 0 1 0 0 0 0
            character_struct->char_array[1] = 0x20;  // 0 0 1 0 0 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'N':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[3] = 0x04;  // 0 0 0 0 0 1 0 0
            character_struct->char_array[2] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[1] = 0x10;  // 0 0 0 1 0 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'O':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3E;  // 0 0 1 1 1 1 1 0
            character_struct->char_array[3] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[1] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[0] = 0x3E;  // 0 0 1 1 1 1 1 0
            break;
        }

        case 'P':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x30;  // 0 0 1 1 0 0 0 0
            character_struct->char_array[3] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[2] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[1] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'Q':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3E;  // 0 0 1 1 1 1 0 1
            character_struct->char_array[3] = 0x41;  // 0 1 0 0 0 0 1 0
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[1] = 0x41;  // 0 1 0 0 0 0 0 1
            character_struct->char_array[0] = 0x3E;  // 0 0 1 1 1 1 1 0
            break;
        }

        case 'R':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x37;  // 0 0 1 1 0 1 1 1
            character_struct->char_array[3] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[2] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[1] = 0x48;  // 0 1 0 0 1 0 0 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'S':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x46;  // 0 1 0 0 0 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x31;  // 0 0 1 1 0 0 0 1
            break;
        }

        case 'T':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x40;  // 0 1 0 0 0 0 0 0
            character_struct->char_array[3] = 0x40;  // 0 1 0 0 0 0 0 0
            character_struct->char_array[2] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[1] = 0x40;  // 0 1 0 0 0 0 0 0
            character_struct->char_array[0] = 0x40;  // 0 1 0 0 0 0 0 0
            break;
        }

        case 'U':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7E;  // 0 1 1 1 1 1 1 0
            character_struct->char_array[3] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[2] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[1] = 0x01;  // 0 0 0 0 0 0 0 1
            character_struct->char_array[0] = 0x7E;  // 0 1 1 1 1 1 1 0
            break;
        }

        case 'V':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x70;  // 0 1 1 1 0 0 0 0
            character_struct->char_array[3] = 0x0C;  // 0 0 0 0 1 1 0 0
            character_struct->char_array[2] = 0x03;  // 0 0 0 0 0 0 1 1
            character_struct->char_array[1] = 0x0C;  // 0 0 0 0 1 1 0 0
            character_struct->char_array[0] = 0x70;  // 0 1 1 1 0 0 0 0
            break;
        }

        case 'W':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[3] = 0x02;  // 0 0 0 0 0 0 1 0
            character_struct->char_array[2] = 0x1C;  // 0 0 0 1 1 1 0 0
            character_struct->char_array[1] = 0x02;  // 0 0 0 0 0 0 1 0
            character_struct->char_array[0] = 0x7F;  // 0 1 1 1 1 1 1 1
            break;
        }

        case 'X':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x63;  // 0 1 1 0 0 0 1 1
            character_struct->char_array[3] = 0x14;  // 0 0 0 1 0 1 0 0
            character_struct->char_array[2] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[1] = 0x14;  // 0 0 0 1 0 1 0 0
            character_struct->char_array[0] = 0x63;  // 0 1 1 0 0 0 1 1
            break;
        }

        case 'Y':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x60;  // 0 1 1 0 0 0 0 0
            character_struct->char_array[3] = 0x10;  // 0 0 0 1 0 0 0 0
            character_struct->char_array[2] = 0x0F;  // 0 0 0 0 1 1 1 1
            character_struct->char_array[1] = 0x10;  // 0 0 0 1 0 0 0 0
            character_struct->char_array[0] = 0x60;  // 0 1 1 0 0 0 0 0
            break;
        }

        case 'Z':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x61;  // 0 1 1 0 0 0 0 1
            character_struct->char_array[3] = 0x51;  // 0 1 0 1 0 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x45;  // 0 1 0 0 0 1 0 1
            character_struct->char_array[0] = 0x43;  // 0 1 0 0 0 0 1 1
            break;
        }

        case '0':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3E;  // 0 0 1 1 1 1 1 0
            character_struct->char_array[3] = 0x51;  // 0 1 0 1 0 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x45;  // 0 1 0 0 0 1 0 1
            character_struct->char_array[0] = 0x3E;  // 0 0 1 1 1 1 1 0
            break;
        }

        case '1':
        {
            character_struct->char_array = (unsigned char *) calloc( 2, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 2;

            character_struct->char_array[1] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[0] = 0x20;  // 0 0 1 0 0 0 0 0
            break;
        }

        case '2':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x31;  // 0 0 1 1 0 0 0 1
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x45;  // 0 1 0 0 0 1 0 1
            character_struct->char_array[1] = 0x43;  // 0 1 0 0 0 0 1 1
            character_struct->char_array[0] = 0x41;  // 0 1 0 0 0 0 0 1
            break;
        }

        case '3':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x36;  // 0 0 1 1 0 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x49;  // 0 1 0 0 1 0 0 1
            break;
        }

        case '4':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x7F;  // 0 1 1 1 1 1 1 1
            character_struct->char_array[3] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[2] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[1] = 0x08;  // 0 0 0 0 1 0 0 0
            character_struct->char_array[0] = 0x78;  // 0 1 1 1 1 0 0 0
            break;
        }

        case '5':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x46;  // 0 1 0 0 0 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x79;  // 0 1 1 1 1 0 0 1
            break;
        }

        case '6':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x06;  // 0 0 0 0 0 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x3E;  // 0 0 1 1 1 1 1 0
            break;
        }

        case '7':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3E;  // 0 1 1 1 0 0 0 0
            character_struct->char_array[3] = 0x41;  // 0 1 0 0 1 1 0 0
            character_struct->char_array[2] = 0x41;  // 0 1 0 0 0 0 1 1
            character_struct->char_array[1] = 0x41;  // 0 1 0 0 0 0 0 0
            character_struct->char_array[0] = 0x3E;  // 0 1 0 0 0 0 0 0
            break;
        }

        case '8':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x36;  // 0 0 1 1 0 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x36;  // 0 0 1 1 0 1 1 0
            break;
        }

        case '9':
        {
            character_struct->char_array = (unsigned char *) calloc( 5, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 5;

            character_struct->char_array[4] = 0x3E;  // 0 0 1 1 1 1 1 0
            character_struct->char_array[3] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[2] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[1] = 0x49;  // 0 1 0 0 1 0 0 1
            character_struct->char_array[0] = 0x30;  // 0 0 1 1 0 0 0 0
            break;
        }

        case ':':
        {
            character_struct->char_array = (unsigned char *) calloc( 1, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 1;

            *(character_struct->char_array) = 0x11;  // 0 0 0 1 0 0 0 1
            break;
        }

        case '.':
        {
            character_struct->char_array = (unsigned char *) calloc( 1, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 1;

            *(character_struct->char_array) = 0x01;  // 0 0 0 0 0 0 0 1
            break;
        }

        case ' ':
        {
            character_struct->char_array = (unsigned char *) calloc( 1, 1 );
            if(character_struct->char_array == NULL )
            {
                break;
            }
            character_struct->array_size = 1;

            *(character_struct->char_array) = 0x00;  // 0 0 0 0 0 0 0 0
            break;
        }

        default:
            break;
    }
    return;
}