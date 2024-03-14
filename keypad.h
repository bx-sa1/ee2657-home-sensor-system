#ifndef KEYPAD_H
#define KEYPAD_H

void keypad_scan();
int keypad_read(uint8_t *value, char *char_value);

#endif
