/*
 * Xournal++
 *
 * Part of the customizable toolbars
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "ToolButton.h"
#include "gui/GladeGui.h"

#include <XournalType.h>

class ToolMenuHandler;

class ToolDrawCombocontrol : public ToolButton
{
public:
	ToolDrawCombocontrol(ToolMenuHandler* th, ActionHandler* handler, GladeGui* gui, string id);
	virtual ~ToolDrawCombocontrol();

public:
	virtual void selected(ActionGroup group, ActionType action);

protected:
	virtual GtkToolItem* newItem();

private:
	XOJ_TYPE_ATTRIB;

	GtkWidget* iconWidget;
	GtkWidget* labelWidget;

	GdkPixbuf* iconDrawRect;
	GdkPixbuf* iconDrawCirc;
	GdkPixbuf* iconDrawArr;
	GdkPixbuf* iconDrawLine;
	GdkPixbuf* iconAutoDrawLine;
};
