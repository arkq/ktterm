/*
 * ktterm - ktutils.c
 * Copyright (c) 2013-2016 Arkadiusz Bokowy
 *
 * This file is a part of a ktterm.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#include "ktutils.h"


/* Set window placement within the Kindle window manager framework. The
 * given GTK window should be a top-level one. */
void kt_window_set_placement(GtkWindow *window, const gchar *layer,
		kt_window_placement placement, guchar orientation, const gchar *name,
		const gchar *id) {

	gchar *title;
	gchar *tmp;

	title = g_strdup_printf("L:%s_N:%s", layer, name);

	if (id != NULL) {
		tmp = g_strdup_printf("%s_ID:%s", title, id);
		g_free(title);
		title = tmp;
	}

	switch (placement) {
	case KT_WINDOW_PLACEMENT_FULLSCREEN:
		tmp = g_strdup_printf("%s_PC:N", title);
		g_free(title);
		title = tmp;
		break;
	case KT_WINDOW_PLACEMENT_APPLICATION:
		tmp = g_strdup_printf("%s_PC:TS", title);
		g_free(title);
		title = tmp;
		break;
	case KT_WINDOW_PLACEMENT_MAXIMIZED:
		break;
	}

	/* construct orientation string based on the supplied mask */
	if (orientation) {

		struct {
			guchar flag;
			gchar orientation;
		} flags[] = {
			{ KT_WINDOW_ORIENTATION_UP, 'U' },
			{ KT_WINDOW_ORIENTATION_DOWN, 'D' },
			{ KT_WINDOW_ORIENTATION_RIGHT, 'R' },
			{ KT_WINDOW_ORIENTATION_LEFT, 'L' },
		};

		gchar buffer[5];
		int i;

		tmp = buffer;
		for (i = 0; i < 4; i++)
			if (orientation & flags[i].flag) {
				*tmp = flags[i].orientation;
				tmp++;
			}
		*tmp = '\0';

		tmp = g_strdup_printf("%s_O:%s", title, buffer);
		g_free(title);
		title = tmp;
	}

	gtk_window_set_title(window, title);
	g_free(title);
}

/* Set terminal color in the standard fashion (black font on white background)
 * or reversed one. Other color combinations are not required, because Kindle
 * Touch has an E-Ink display which supports gray scale only. */
void kt_terminal_set_colors(VteTerminal *terminal, gboolean reversed) {

	GdkColor color_white = { 0, 0xffff, 0xffff, 0xffff };
	GdkColor color_black = { 0, 0x0000, 0x0000, 0x0000 };

	if (reversed)
		vte_terminal_set_colors(terminal, &color_white, &color_black, NULL, 0);
	else
		vte_terminal_set_colors(terminal, &color_black, &color_white, NULL, 0);
}

/* Get current font size. */
gint kt_terminal_get_font_size(VteTerminal *terminal) {

	PangoFontDescription *font;
	gint size;

	font = (PangoFontDescription *)vte_terminal_get_font(terminal);
	size = pango_font_description_get_size(font);

	if (!pango_font_description_get_size_is_absolute(font))
		size /= PANGO_SCALE;

	return size;
}

/* Set terminal fort size. */
void kt_terminal_set_font_size(VteTerminal *terminal, gint size) {

	PangoFontDescription *font;

	font = (PangoFontDescription *)vte_terminal_get_font(terminal);
	pango_font_description_set_size(font, size * PANGO_SCALE);
	vte_terminal_set_font(terminal, font);
}
