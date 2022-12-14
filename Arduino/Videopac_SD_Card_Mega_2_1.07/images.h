PROGMEM const unsigned char selectgame[77] = {
    0x3e, 0x7f, 0x03, 0x7f, 0x3e, 0x3f, 0x00, 0x1f, 0x8e, 0xb1, 0x3f, 
    0x63, 0x03, 0x03, 0x03, 0x43, 0x0c, 0x80, 0x31, 0x9b, 0xbb, 0x01, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x0c, 0x80, 0x81, 0xb1, 0xbf, 0x01, 
    0x3e, 0x1f, 0x03, 0x0f, 0x03, 0x0c, 0x80, 0x81, 0xb1, 0xb5, 0x0f, 
    0x60, 0x03, 0x03, 0x03, 0x03, 0x0c, 0x80, 0xb9, 0xbf, 0xb1, 0x01, 
    0x63, 0x03, 0x03, 0x03, 0x43, 0x0c, 0x80, 0xb1, 0xb1, 0xb1, 0x01, 
    0x3e, 0x7f, 0x7f, 0x7f, 0x3e, 0x0c, 0x00, 0xbf, 0xb1, 0xb1, 0x3f
};


#define LOGO_width 128
#define LOGO_height 64
static const unsigned char LOGO[] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0xbd, 0xf7, 0x81, 0xf7, 0x83,
   0x3f, 0xf0, 0x1e, 0x10, 0x00, 0xdc, 0x01, 0x00, 0x00, 0x3e, 0xf8, 0xbc,
   0xf7, 0x83, 0xf7, 0xc3, 0x7f, 0xf0, 0x3e, 0x38, 0x00, 0xde, 0x03, 0x00,
   0x00, 0x3c, 0xf8, 0xbc, 0xf7, 0x87, 0xf7, 0xe3, 0xff, 0xf0, 0x7e, 0x38,
   0x00, 0xdf, 0x07, 0x00, 0x00, 0x7c, 0x7c, 0xbc, 0xf7, 0x8f, 0xf7, 0xf3,
   0xff, 0xf1, 0x7e, 0x7c, 0x80, 0xdf, 0x0f, 0x00, 0x00, 0x78, 0x3c, 0xbc,
   0x87, 0x9f, 0x07, 0xf8, 0xf1, 0xf3, 0xf8, 0x7c, 0xc0, 0x8f, 0x03, 0x00,
   0x00, 0xf8, 0x3e, 0xbc, 0x07, 0x9f, 0xf7, 0xfb, 0xe0, 0xf3, 0x7e, 0xfa,
   0xc0, 0x07, 0x01, 0x00, 0x00, 0xf0, 0x1f, 0xbc, 0x07, 0x9e, 0xf7, 0x7b,
   0xc0, 0xf3, 0x7e, 0xfe, 0xc0, 0x03, 0x00, 0x00, 0x00, 0xf0, 0x1d, 0xbc,
   0x07, 0x9e, 0xf7, 0x03, 0x00, 0xf0, 0x7e, 0xf7, 0xc1, 0x03, 0x00, 0x00,
   0x00, 0xe0, 0x0f, 0xbc, 0x07, 0x9e, 0xf7, 0x7b, 0xc0, 0xf3, 0x3e, 0xef,
   0xc1, 0x03, 0x00, 0x00, 0x00, 0xe0, 0x0b, 0xbc, 0x07, 0x9f, 0xf7, 0xfb,
   0xe0, 0xf3, 0x8e, 0xef, 0xc3, 0x07, 0x01, 0x00, 0x00, 0xc0, 0x07, 0xbc,
   0x87, 0x9f, 0x07, 0xf8, 0xf1, 0xf3, 0x80, 0xf7, 0xc3, 0x8f, 0x03, 0x00,
   0x00, 0xc0, 0x07, 0xbc, 0xf7, 0x8f, 0xf7, 0xf3, 0xff, 0xf1, 0xc0, 0xff,
   0x87, 0xdf, 0x0f, 0x00, 0x00, 0x80, 0x03, 0xbc, 0xf7, 0x87, 0xf7, 0xe3,
   0xff, 0xf0, 0xc0, 0xfb, 0x0f, 0xdf, 0x07, 0x00, 0x00, 0x80, 0x03, 0xbc,
   0xf7, 0x83, 0xf7, 0xc3, 0x7f, 0xf0, 0xe0, 0xff, 0x0f, 0xde, 0x03, 0x00,
   0x00, 0x00, 0x01, 0xbc, 0xf7, 0x81, 0xf7, 0x83, 0x3f, 0xf0, 0xf0, 0x01,
   0x1f, 0xdc, 0x01, 0x00, 0x60, 0x18, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0x7f, 0xf3, 0x78, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f, 0xfb, 0xf9, 0x3e, 0xe0, 0xff, 0x3f,
   0xfc, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x77, 0x8f, 0xd9,
   0x63, 0xfc, 0xff, 0x3f, 0xfe, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xb8, 0x77, 0x0f, 0xf8, 0x63, 0x3f, 0x00, 0x00, 0x00, 0x36, 0x1e, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xb8, 0x77, 0x8f, 0x79, 0x63, 0x3f, 0x00, 0x00,
   0x00, 0xc9, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x77, 0xfb, 0x79,
   0x3e, 0x7f, 0x00, 0x00, 0x00, 0xf2, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xb8, 0x77, 0xf3, 0xd8, 0x1c, 0xfe, 0x01, 0x00, 0x00, 0xfc, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xb8, 0x77, 0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00,
   0x00, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x77, 0x00, 0x00,
   0x00, 0xf0, 0xff, 0x00, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xb8, 0x77, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x03, 0xe0, 0xff, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03,
   0xfe, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0xc3, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xfe, 0xc3, 0xff, 0xff, 0x1f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xc3,
   0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xff, 0xe3, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xf1, 0xff, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x7f, 0xf0,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x3b, 0x00, 0x04, 0xf0, 0x1e, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x7b, 0x00, 0x0e, 0xf0, 0x3e, 0xfe, 0x03,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfb, 0x00, 0x0e,
   0xf0, 0x7e, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf0, 0xfb, 0x01, 0x1f, 0xf0, 0x7e, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x71, 0x00, 0x1f, 0xf0, 0xf8, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x20, 0x80, 0x3e,
   0xf0, 0x7e, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x78, 0x00, 0x80, 0x3f, 0xf0, 0x7e, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xc0, 0x7d, 0xf0, 0x7e, 0xf8, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xc0, 0x7b,
   0xf0, 0x3e, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0x20, 0xe0, 0xfb, 0xf0, 0x0e, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x71, 0xe0, 0xfd, 0xf0, 0x3e, 0xf8, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfb, 0xf1, 0xff,
   0xf1, 0x3c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0xfb, 0xf0, 0xfe, 0xf3, 0x3c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x7b, 0xf8, 0xff, 0xf3, 0x78, 0xf8, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3b, 0x7c, 0xc0,
   0xf7, 0x78, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x82, 0xe7, 0x78, 0x0e, 0x22,
   0x4a, 0xe0, 0xf1, 0x78, 0x8e, 0xe3, 0x00, 0x00, 0x00, 0x80, 0x84, 0x02,
   0x24, 0x41, 0x12, 0x62, 0x4a, 0x10, 0x0a, 0x41, 0x92, 0x14, 0x01, 0x00,
   0x00, 0x80, 0x04, 0x04, 0x14, 0x41, 0x11, 0x54, 0x4a, 0x10, 0x08, 0x41,
   0x51, 0x14, 0x01, 0x00, 0x00, 0x80, 0x04, 0x04, 0x12, 0x21, 0x11, 0x54,
   0x49, 0x10, 0x04, 0x21, 0x51, 0x24, 0x01, 0x00, 0x00, 0x80, 0x04, 0x04,
   0x11, 0x11, 0x11, 0x94, 0x49, 0x10, 0x08, 0x11, 0x51, 0xc4, 0x01, 0x00,
   0x00, 0x80, 0xc4, 0x84, 0x20, 0x09, 0x12, 0x8c, 0x49, 0x10, 0x0b, 0x09,
   0x92, 0x04, 0x01, 0x00, 0x00, 0x80, 0x78, 0xc4, 0xe7, 0x7c, 0x0e, 0x88,
   0xc8, 0xe3, 0xf1, 0x7c, 0x8e, 0xe3, 0x00, 0x00, 0x00, 0x80, 0x00, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

#define ATARI_LOGO_width 128
#define ATARI_LOGO_height 64
static const unsigned char ATARI_LOGO[] PROGMEM = {
   0x00, 0x00, 0x78, 0x3e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x3e, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x3e,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x78, 0x3e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x3e, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x80, 0xff, 0xff, 0xf0, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x3e,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xf8, 0x23, 0x03, 0x00,
   0x00, 0x00, 0x78, 0x3e, 0x0f, 0xc3, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00,
   0x00, 0xd8, 0x78, 0x00, 0x00, 0x00, 0x78, 0x3e, 0x8f, 0xff, 0x99, 0xc7,
   0xe3, 0xfc, 0x00, 0x00, 0x00, 0x24, 0xff, 0x00, 0x00, 0x00, 0x78, 0x3e,
   0xcf, 0xff, 0xdb, 0xcf, 0xf7, 0xfd, 0x01, 0x00, 0x00, 0xc8, 0xff, 0x00,
   0x00, 0x00, 0x78, 0x3e, 0xcf, 0xff, 0x7b, 0xcc, 0x1e, 0xfb, 0x07, 0x00,
   0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 0x78, 0x3e, 0xcf, 0xbd, 0x7b, 0xc0,
   0x1f, 0xfb, 0x7f, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 0x78, 0x3e,
   0xcf, 0xbd, 0x7b, 0xcc, 0x1b, 0xc3, 0xff, 0x03, 0x00, 0xfe, 0xff, 0x01,
   0x00, 0x00, 0x78, 0x3e, 0xcf, 0xbd, 0xdb, 0xcf, 0xf3, 0x01, 0xff, 0x0f,
   0x80, 0xff, 0xff, 0x01, 0x00, 0x00, 0x78, 0x3e, 0xcf, 0xbd, 0x9b, 0xc7,
   0xe6, 0x00, 0xfc, 0x0f, 0xf8, 0xff, 0xff, 0x00, 0x00, 0x00, 0x78, 0x3e,
   0xcf, 0xbd, 0x03, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0x00,
   0x00, 0x00, 0x7c, 0x3e, 0xdf, 0xbd, 0x03, 0x00, 0xc0, 0x00, 0xf8, 0x0f,
   0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0xdf, 0xbd, 0x03, 0x00,
   0xc0, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x7c, 0x3e,
   0xdf, 0xbd, 0x03, 0x00, 0xe0, 0xff, 0xff, 0x8f, 0xff, 0xff, 0x01, 0x00,
   0x00, 0x00, 0x7c, 0x3e, 0x3f, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xc7,
   0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0x3f, 0x00, 0x00, 0x00,
   0xe0, 0xff, 0xff, 0xc1, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x3e, 0x3e, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3e, 0x7e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1f, 0x3e,
   0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x80, 0x1f, 0x3e, 0xfe, 0x00, 0x00, 0x00, 0xe0, 0x0e, 0x00, 0x01,
   0xbc, 0x87, 0xff, 0x00, 0x00, 0xc0, 0x1f, 0x3e, 0xfe, 0x00, 0x00, 0x00,
   0xf0, 0x1e, 0x80, 0x03, 0xbc, 0x8f, 0xff, 0x00, 0x00, 0xe0, 0x1f, 0x7e,
   0xfc, 0x01, 0x00, 0x00, 0xf8, 0x3e, 0x80, 0x03, 0xbc, 0x9f, 0xff, 0x00,
   0x00, 0xe0, 0x0f, 0x7e, 0xfc, 0x01, 0x00, 0x00, 0xfc, 0x7e, 0xc0, 0x07,
   0xbc, 0x9f, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x7e, 0xf8, 0x07, 0x00, 0x00,
   0x7e, 0x1c, 0xc0, 0x07, 0x3c, 0x3e, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x7e,
   0xf8, 0x0f, 0x00, 0x00, 0x3e, 0x08, 0xa0, 0x0f, 0xbc, 0x1f, 0x3e, 0x00,
   0x00, 0xfc, 0x07, 0x7e, 0xf8, 0x1f, 0x00, 0x00, 0x1e, 0x00, 0xe0, 0x0f,
   0xbc, 0x1f, 0x3e, 0x00, 0x00, 0xfe, 0x07, 0x7e, 0xf0, 0x1f, 0x00, 0x00,
   0x1e, 0x00, 0x70, 0x1f, 0xbc, 0x1f, 0x3e, 0x00, 0x80, 0xff, 0x07, 0x7f,
   0xf0, 0x7f, 0x00, 0x00, 0x1e, 0x00, 0xf0, 0x1e, 0xbc, 0x0f, 0x3e, 0x00,
   0xc0, 0xff, 0x07, 0x7f, 0xe0, 0xff, 0x00, 0x00, 0x3e, 0x08, 0xf8, 0x3e,
   0xbc, 0x03, 0x3e, 0x00, 0xe0, 0xff, 0x03, 0x7f, 0xe0, 0xff, 0x03, 0x00,
   0x7e, 0x1c, 0x78, 0x3f, 0xbc, 0x0f, 0x3e, 0x00, 0xff, 0xff, 0x01, 0xff,
   0xc0, 0xff, 0x7f, 0x00, 0xfc, 0x7e, 0xfc, 0x7f, 0x3c, 0x0f, 0x3e, 0x00,
   0xff, 0xff, 0x00, 0xff, 0x80, 0xff, 0x7f, 0x00, 0xf8, 0x3e, 0xbc, 0xff,
   0x3c, 0x0f, 0x3e, 0x00, 0xff, 0xff, 0x00, 0xff, 0x80, 0xff, 0x7f, 0x00,
   0xf0, 0x1e, 0xfe, 0xff, 0x3c, 0x1e, 0x3e, 0x00, 0xff, 0x7f, 0x80, 0xff,
   0x80, 0xff, 0x7f, 0x00, 0xe0, 0x0e, 0x1f, 0xf0, 0x3d, 0x1e, 0x3e, 0x00,
   0xff, 0x3f, 0x80, 0xff, 0x00, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xff, 0x1f, 0x80, 0xff, 0x00, 0xfe, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0f, 0xc0, 0xff,
   0x00, 0xf8, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xff, 0x07, 0xc0, 0xff, 0x01, 0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0xc0, 0xff, 0x01, 0xe0, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0xe0, 0xff,
   0x01, 0xc0, 0x7f, 0x00, 0x00, 0xf2, 0x04, 0xcf, 0xf1, 0x1c, 0x00, 0x00,
   0x7f, 0x00, 0xe0, 0xff, 0x03, 0x80, 0x7f, 0x00, 0x00, 0x09, 0x05, 0x48,
   0x82, 0x24, 0x00, 0x00, 0x3f, 0x00, 0xf0, 0xff, 0x03, 0x00, 0x7e, 0x00,
   0x00, 0x09, 0x08, 0x28, 0x82, 0x22, 0x00, 0x00, 0x0f, 0x00, 0xf0, 0xff,
   0x07, 0x00, 0x78, 0x00, 0x00, 0x09, 0x08, 0x24, 0x42, 0x22, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x08, 0x22,
   0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x89, 0x09, 0x41, 0x12, 0x24, 0x00, 0x00, 0xe0, 0xf0, 0xff, 0x78,
   0x80, 0x7f, 0x70, 0x00, 0x00, 0xf1, 0x88, 0xcf, 0xf9, 0x1c, 0x00, 0x00,
   0xe0, 0xf1, 0xff, 0xf8, 0x80, 0xff, 0x70, 0x00, 0x00, 0x01, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0xff, 0xfc, 0x80, 0xff, 0x71, 0x00,
   0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x07, 0xfc,
   0x80, 0xe1, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xb8, 0x03, 0x07, 0xdc, 0x80, 0xc1, 0x71, 0x00, 0x44, 0x94, 0xc0, 0xe3,
   0xf1, 0x1c, 0xc7, 0x01, 0xb8, 0x07, 0x07, 0xdc, 0x81, 0xe1, 0x71, 0x00,
   0xc4, 0x94, 0x20, 0x14, 0x82, 0x24, 0x29, 0x02, 0xbc, 0x07, 0x07, 0xce,
   0x81, 0xf1, 0x70, 0x00, 0xa8, 0x94, 0x20, 0x10, 0x82, 0xa2, 0x28, 0x02,
   0x3c, 0x0f, 0x07, 0x8e, 0x83, 0x79, 0x70, 0x00, 0xa8, 0x92, 0x20, 0x08,
   0x42, 0xa2, 0x48, 0x02, 0xfe, 0x0f, 0x07, 0xfe, 0x83, 0x39, 0x70, 0x00,
   0x28, 0x93, 0x20, 0x10, 0x22, 0xa2, 0x88, 0x03, 0xfe, 0x0f, 0x07, 0xff,
   0x87, 0x39, 0x70, 0x00, 0x18, 0x93, 0x20, 0x16, 0x12, 0x24, 0x09, 0x02,
   0xfe, 0x1f, 0x07, 0xff, 0x87, 0x79, 0x70, 0x00, 0x10, 0x91, 0xc7, 0xe3,
   0xf9, 0x1c, 0xc7, 0x01, 0x0f, 0x1c, 0x87, 0x03, 0x8f, 0xe1, 0x71, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c, 0x87, 0x03,
   0x8f, 0xe1, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x07, 0x1c, 0xc7, 0x03, 0x8f, 0xc1, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

static const unsigned char PROGMEM car_img[] U8X8_PROGMEM = {
    0b00111100, 
    0b01111110, 
    0b01111110, 
    0b00111100, 
    0b00100100, 
    0b11100111, 
    0b11111111, 
    0b01111110
};

static const unsigned char PROGMEM explosion_img[] U8X8_PROGMEM = {
    0b01101100, 
    0b11011000, 
    0b10110110, 
    0b01100110, 
    0b11001100, 
    0b11111011, 
    0b01100111, 
    0b00001110
};
