#include "FontButton.h"

#include <stdlib.h>

#include <config.h>
#include <glib/gi18n-lib.h>

FontButton::FontButton(ActionHandler * handler, GladeGui * gui, String id, ActionType type, String description,
		GtkWidget * menuitem) :
	AbstractToolItem(id, handler, type, menuitem) {
	XOJ_INIT_TYPE(FontButton);

	this->gui = gui;
	this->description = description;
	this->fontButton = NULL;
}

FontButton::~FontButton() {
	XOJ_RELEASE_TYPE(FontButton);
}

void FontButton::activated(GdkEvent *event, GtkMenuItem *menuitem, GtkToolButton *toolbutton) {
	XOJ_CHECK_TYPE(FontButton);

	GtkFontButton * button = GTK_FONT_BUTTON(fontButton);

	String name = gtk_font_button_get_font_name(button);

	int pos = name.lastIndexOf(" ");
	this->font.setName(name.substring(0, pos));
	this->font.setSize(atof(name.substring(pos + 1).c_str()));

	handler->actionPerformed(ACTION_FONT_BUTTON_CHANGED, GROUP_NOGROUP, event, menuitem, NULL, true);
}

void FontButton::setFont(XojFont & font) {
	XOJ_CHECK_TYPE(FontButton);

	this->font = font;
	if (this->fontButton == NULL) {
		return;
	}

	GtkFontButton * button = GTK_FONT_BUTTON(fontButton);

	String txt = font.getName();
	txt += " ";
	txt += font.getSize();

	gtk_font_button_set_font_name(button, txt.c_str());
}

XojFont FontButton::getFont() {
	XOJ_CHECK_TYPE(FontButton);

	return font;
}

String FontButton::getToolDisplayName() {
	XOJ_CHECK_TYPE(FontButton);

	return _("Font");
}

GtkWidget * FontButton::getNewToolIcon() {
	XOJ_CHECK_TYPE(FontButton);

	return gtk_image_new_from_stock(GTK_STOCK_SELECT_FONT, GTK_ICON_SIZE_SMALL_TOOLBAR);
}

GtkToolItem * FontButton::createItem(bool horizontal) {
	XOJ_CHECK_TYPE(FontButton);

	if (this->item) {
		return this->item;
	}

	this->item = newItem();
	g_object_ref(this->item);
	gtk_tool_item_set_homogeneous(GTK_TOOL_ITEM(this->item), false);
	g_signal_connect(fontButton, "font_set", G_CALLBACK(&toolButtonCallback), this);
	return this->item;
}

GtkToolItem * FontButton::createTmpItem(bool horizontal) {
	GtkToolItem * item = newItem();
	gtk_tool_item_set_homogeneous(GTK_TOOL_ITEM(item), false);

	gtk_widget_show_all(GTK_WIDGET(item));
	return item;
}

void FontButton::showFontDialog() {
	XOJ_CHECK_TYPE(FontButton);

	if (this->fontButton == NULL) {
		newItem();
	}

	gtk_button_clicked(GTK_BUTTON(this->fontButton));
}

GtkToolItem * FontButton::newItem() {
	XOJ_CHECK_TYPE(FontButton);

	if (this->fontButton) {
		g_object_unref(this->fontButton);
	}
	GtkToolItem * it;

	it = gtk_tool_item_new();

	this->fontButton = gtk_font_button_new();
	gtk_widget_show(this->fontButton);
	gtk_container_add(GTK_CONTAINER(it), this->fontButton);
	gtk_font_button_set_use_font(GTK_FONT_BUTTON(this->fontButton), TRUE);
	gtk_button_set_focus_on_click(GTK_BUTTON(this->fontButton), FALSE);

	gtk_tool_item_set_tooltip_text(it, this->description.c_str());

	if (!this->font.getName().isEmpty()) {
		setFont(this->font);
	}

	return it;
}

