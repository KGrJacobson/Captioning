#ifndef UI_TAB
#define UI_TAB
#include <list>

#include "SDL.h"

#include "CaptionContainer.h"
#include "ContextMenu.h"
#include "MouseHandler.h"
#include "TextInput.h"
#include "UIButton.h"

class UITab {
public:
	enum UI_Tab_Return_Values
	{
		NO_RETURN_VALUE,
		CLOSE_TAB,
		SELECT_TAB,
		MOVE_TAB,
		OPEN_CONTEXT_MENU,
		CHECK_CONTEXT_MENU
	};

	UITab(SDL_Rect tabarea, std::string text, int tabnumber, ContextMenu *contextmenu);
	~UITab();
	MouseHandler *CheckMouseEvents();
	int ShowTab(bool isselected);
	void SetTabArea(SDL_Rect newarea);
	void SetContextMenu(ContextMenu *newmenu);
	void SetTabNumber(int tabnumber);
	int GetTabNumber();
	TextInput *GetTabText();
	int GetContextMenuAction();
private:
	int tabnumber_;
	SDL_Rect tabarea_;
	UIButton *tabbutton_;
	UIButton *closebutton_;
	ContextMenu *contextmenu_;
};

#endif //UI_TAB