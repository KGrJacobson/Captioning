#ifndef UI_TAB
#define UI_TAB
#include <list>

#include "SDL.h"

#include "CaptionContainer.h"
#include "ContextMenu.h"
#include "MouseHandler.h"
#include "UIButton.h"

class UITab {
public:
	enum IO_Tab_Return_Values 
	{
		NO_RETURN_VALUE,
		CLOSE_TAB,
		SELECT_TAB
	};

	UITab(SDL_Rect tabarea, std::string text, int tabnumber);
	~UITab();
	MouseHandler *CheckMouseEvents();
	int ShowTab();
	void SetTabArea(SDL_Rect newarea);
	void SetTabNumber(int tabnumber);
	int GetTabNumber();
	ContextMenu *GetContextMenu();
private:
	int tabnumber_;
	SDL_Rect tabarea_;
	UIButton *tabbutton_;
	UIButton *closebutton_;
	ContextMenu *contextmenu_;
};

#endif //UI_TAB