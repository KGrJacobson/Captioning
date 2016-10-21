#ifndef STORED_CAPTION_SCREEN
#define STORED_CAPTION_SCREEN
#include <vector>
#include <unordered_map>

#include "SDL.h"

#include "KWindow\MouseHandler.h"
#include "StoredCaptionContainer.h"
#include "KWindow\Subscreen.h"
#include "KWindow\UIMenu.h"

struct dialoguestruct
{
	std::string name;
	StoredCaptionContainer *container;
};

//Contains captions loaded from a given file to be sent to the Demo Screen when selected.
class StoredCaptionScreen : public Subscreen
{
public:
	enum Stored_Caption_Screen_Return_Codes
	{
		NO_RETURN_CODE,
		GET_NEW_CAPTION_LIST,
		GET_NEW_SINGLE_CAPTION
	};

	enum Stored_Caption_Screen_Context_Menu
	{
		SAVE_FILE,
		ADD_NEW_CAPTION_LIST
	};

	enum File_In_Flags
	{

	};

	StoredCaptionScreen(SDL_Rect setscreenarea);
	~StoredCaptionScreen();
	int Show();
	StoredCaptionContainer *GetNewContainer(int captionid);
	std::vector<StoredCaptionContainer*> *GetCaptionList();
	RelativeRect GetCaptionContainer(int containerindex);
	void OpenFile(std::string filename);

	dialoguestruct* GetCurrentDialogue(int index);
	void increaseindex();
	void decreaseindex();
	void setcaptionindex(int index);
	int getcurrentindex();
private:
	SDL_Rect screenarea_;
	std::vector<StoredCaptionContainer*> captionpreview_;
	std::vector<std::vector<StoredCaptionContainer*>> captions_;
	UIMenu *contextmenu_;
	MouseHandler *mousefunction_;
	std::string currentfile_;
	int currentcaptionlistindex_;
	int currentcaptionindex_;
	StoredCaptionContainer *currentcaptionlist_;
	StoredCaptionContainer *currentcaption_;
	std::vector<StoredCaptionContainer*> *returnlist_;
	std::vector<RelativeRect> captioncontainers_;

	int startonthisindex_;
	std::unordered_map<std::string, std::string> tempname_;
	std::vector<dialoguestruct*> dialoguelist_;
};

#endif //STORED_CAPTION_SCREEN