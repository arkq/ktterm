/*
 * ktterm - ktutils.h
 * Copyright (c) 2013-2016 Arkadiusz Bokowy
 *
 * This file is a part of a ktterm.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#ifndef KTTERM_KTUTILS_H_
#define KTTERM_KTUTILS_H_

#include <gtk/gtk.h>
#include <vte/vte.h>


/* Kindle mouse gesture (button) definitions. With every button action
 * an appropriate coordinations are associated. "Tap" and "Hold" actions
 * are obvious - action point. For "Double Tap" the coordinations of the
 * first "Tap" is returned, and for pinching and stretching actions the
 * coordinations of an average (in between) point is returned. */
#define KT_TOUCH_TAP 1
#define KT_TOUCH_TAP_DOUBLE 2
#define KT_TOUCH_PINCH 7
#define KT_TOUCH_STRETCH 8
#define KT_TOUCH_HOLD 9

/* Kindle window manager framework supports few layers for placing windows.
 * Each layer is dedicated for a specific type of applications. In the most
 * common situations the application layer should be used. */
#define KT_WINDOW_LAYER_APPLICATION "A"
#define KT_WINDOW_LAYER_CHROME "C"
#define KT_WINDOW_LAYER_DIALOG "D"
#define KT_WINDOW_LAYER_KEYBOARD "KB"
#define KT_WINDOW_LAYER_SCREENSAVER "SS"

/* Kindle applications may support extra orientations (with the addition to
 * the standard upward orientation). One can use bitwise OR operator to set
 * allowed orientations while placing a window. */
#define KT_WINDOW_ORIENTATION_UP 0x01
#define KT_WINDOW_ORIENTATION_DOWN 0x02
#define KT_WINDOW_ORIENTATION_LEFT 0x04
#define KT_WINDOW_ORIENTATION_RIGHT 0x08

typedef enum {
	/* place window in the application zone */
	KT_WINDOW_PLACEMENT_APPLICATION,
	/* place window in the chrome zone */
	KT_WINDOW_PLACEMENT_MAXIMIZED,
	/* fill-in the whole screen area */
	KT_WINDOW_PLACEMENT_FULLSCREEN,
} kt_window_placement;


void kt_window_set_placement(GtkWindow *window, const gchar *layer,
		kt_window_placement placement, guchar orientation, const gchar *name,
		const gchar *id);

void kt_terminal_set_colors(VteTerminal *terminal, gboolean reversed);
gint kt_terminal_get_font_size(VteTerminal *terminal);
void kt_terminal_set_font_size(VteTerminal *terminal, gint size);

#endif  /* KTTERM_KTUTILS_H_ */
