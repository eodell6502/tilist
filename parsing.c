#include "parsing.h"

/*

@IMAGE: h, w, #bgcolor, bgimage
@DIRECTIONS: N, E, S, W     // which translates to 1, 2, 3, 4 (zero is reserved)
@TILE: [...]
@VERTEX: order, x, y, N:n1;E:n2;W:n3;S:n4, tiletype:orientation

*/

//==============================================================================
//==============================================================================

bool parse_image_line(char *line, int line_number) {
    char *token;

    line = beginning_of_data(line);

    token = strtok(line, ", ");
    if(!token) {
        printf("Invalid @IMAGE entry on line %d.\n", line_number);
        return false;
    }
    config.image_width = atoi(token);
    if(config.image_width < 1) {
        printf("Invalid @IMAGE width parameter on line %d.\n", line_number);
        return false;
    }

    token = strtok(NULL, ", ");
    if(!token) {
        printf("Missing or invalid @IMAGE height entry on line %d.\n", line_number);
        return false;
    }
    config.image_height = atoi(token);
    if(config.image_height < 1) {
        printf("Invalid @IMAGE height parameter on line %d.\n", line_number);
        return false;
    }

    return true;
}


//==============================================================================
//==============================================================================

bool parse_directions_line(char *line, int line_number) {

    line = beginning_of_data(line);

    return true;
}


//==============================================================================
//==============================================================================

bool parse_tile_line(char *line, int line_number) {

    line = beginning_of_data(line);

    return true;
}


//==============================================================================
//==============================================================================

bool parse_vertex_line(char *line, int line_number) {

    line = beginning_of_data(line);

    return true;
}



//==============================================================================
// Given an RGB string in the form "#xxxxxx" and a pointer to a Pixel struct,
// convert the former to the latter. Returns true on success and false
// on failure.
//==============================================================================

bool parse_rgb_hex(char *rgb, Pixel *pixel) {
    char *p;
    char octet[3] = "\0\0\0";

    if(*rgb != '#' || (strlen(rgb) != 4 && strlen(rgb) != 7))
        return false;

    for(p = rgb + 1; *p; p++) {
        if(*p > 96 && *p < 103)
            *p = *p - 32;
        if(!isxdigit(*p))
            return false;
    }

    p = rgb + 1; octet[0] = *p; octet[1] = *(p + 1); pixel->r = (uint8_t)strtol(octet, NULL, 16);
    p += 2;      octet[0] = *p; octet[1] = *(p + 1); pixel->g = (uint8_t)strtol(octet, NULL, 16);
    p += 2;      octet[0] = *p; octet[1] = *(p + 1); pixel->b = (uint8_t)strtol(octet, NULL, 16);
    pixel->a = 0;

    return true;
}


//==============================================================================
// Given a line beginning with a prefix ending in ':', return a pointer to the
// first non-whitespace character.
//==============================================================================

char *beginning_of_data(char *line) {
    char *p;

    for(p = line; *p != ':'; p++);
    p++;
    while(isspace(*p))
        p++;

    return p;
}


//==============================================================================
// Takes an input line and removes any comments, then trims trailing whitespace.
//==============================================================================

void clean_line(char *line) {
    char *p;

    // Remove comments ---------------------------------------------------------

    p = line;
    while(*p) {
        if(*p == '#') {
            *p = '\0';
            break;
        }
        p++;
    }

    // Trim trailing whitespace ------------------------------------------------

    for(--p; p >= line && isspace(*p); p--);
    if(isspace(*p))
        *p = '\0';
    else
        *(p+1) = '\0';

    return;
}


//==============================================================================
// Returns a boolean indicating whether all of the line was read into the
// buffer or not, i.e., it ends in a newline.
//==============================================================================

bool partial_line(char *line) {
    char *p;
    for(p = line; *p; p++);
    return p[-1] == '\n' ? false : true;
}


//==============================================================================
// Returns a boolean indicating whether the two strings supplied are identical.
//==============================================================================

bool streq(char *a, char *b) {
    return strcmp(a, b) ? false : true;
}


//==============================================================================
// Returns a boolean indicating whether the two strings supplied are identical
// up to the first n bytes. If either string terminates before the nth
// character, the result is false.
//==============================================================================

bool streqn(char *a, char *b, int n) {
    int i;

    for(i = 0; i < n; i++) {
        if(a[i] == '\0' || b[i] == '\0' || a[i] != b[i])
            return false;
    }
    return true;
}
