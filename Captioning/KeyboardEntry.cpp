#include <string>

#include "SDL.h"

#include "DebugText.h"
#include "KeyboardEntry.h"
#include "TextInput.h"

KeyboardEntry::KeyboardEntry()
{
	isshift_ = false;
	isctrl_ = false;
	currentime_ = ENGLISH;
	currenttext_ = "";
	tempstring_ = "";
	nexttempchar_ = "";
}

KeyboardEntry::~KeyboardEntry()
{
	if (currenttexttexture_ != NULL)
	{
		FinalizeCurrentText();
		currenttexttexture_ = NULL;
	}

	currenttext_ = "";
	tempstring_ = "";
	nexttempchar_ = "";
}

void KeyboardEntry::InsertCharacter(char character)
{
	if (character >= 'a' && character <= 'z' && isshift_ == true)
	{
		currenttext_ = currenttext_ + static_cast<char>(character - 32);
	}
	else
	{
		if (isshift_ == true)
		{
			switch (character)
			{
			case '0':
				currenttext_ = currenttext_ + ')';
				break;
			case '1':
				currenttext_ = currenttext_ + '!';
				break;
			case '2':
				currenttext_ = currenttext_ + '@';
				break;
			case '3':
				currenttext_ = currenttext_ + '#';
				break;
			case '4':
				currenttext_ = currenttext_ + '$';
				break;
			case '5':
				currenttext_ = currenttext_ + '%';
				break;
			case '6':
				currenttext_ = currenttext_ + '^';
				break;
			case '7':
				currenttext_ = currenttext_ + '&';
				break;
			case '8':
				currenttext_ = currenttext_ + '*';
				break;
			case '9':
				currenttext_ = currenttext_ + '(';
				break;
			case '/':
				currenttext_ = currenttext_ + '?';
				break;
			}
		}
		else
		{
			currenttext_ = currenttext_ + character;
		}
	}

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

void KeyboardEntry::InsertString(std::string string)
{
	currenttext_ = currenttext_ + string;

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

void KeyboardEntry::DeleteCharacter()
{
	if (currenttext_ != "")
	{
		currenttext_.pop_back();
	}

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

void KeyboardEntry::SetTexture(TextInput *text)
{
	FinalizeCurrentText();

	currenttexttexture_ = text;
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateQuickTextureFromText("|");
}

void KeyboardEntry::SetShift(bool isdown)
{
	isshift_ = isdown;
}

void KeyboardEntry::SetCTRL(bool isdown)
{
	isctrl_ = isdown;
}

void KeyboardEntry::FinalizeCurrentText()
{
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateTextureFromText(currenttext_);

	currenttext_ = "";
	tempstring_ = "";
}

int KeyboardEntry::KeyDownInput(const SDL_Event &e)
{
	char chartoadd = 0;

	if (isctrl_ != true)
	{
		switch (currentime_)
		{
		case ENGLISH:
			chartoadd = KeyDownInputEnglish(e);

			if (chartoadd != 0)
				InsertCharacter(chartoadd);
			break;
		case JAPANESE:
			KeyDownInputJapanese(e);

			if (currenttexttexture_ != NULL)
				if (tempstring_ == "" && nexttempchar_ == "")
					currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
				else
					currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
			break;
		}

		switch (e.key.keysym.sym)
		{
		case SDLK_PERIOD:
			InsertCharacter('.');
			break;
		case SDLK_SLASH:
			InsertCharacter('/');
			break;
		case SDLK_0:
			InsertCharacter('0');
			break;
		case SDLK_1:
			InsertCharacter('1');
			break;
		case SDLK_2:
			InsertCharacter('2');
			break;
		case SDLK_3:
			InsertCharacter('3');
			break;
		case SDLK_4:
			InsertCharacter('4');
			break;
		case SDLK_5:
			InsertCharacter('5');
			break;
		case SDLK_6:
			InsertCharacter('6');
			break;
		case SDLK_7:
			InsertCharacter('7');
			break;
		case SDLK_8:
			InsertCharacter('8');
			break;
		case SDLK_9:
			InsertCharacter('9');
			break;
		case SDLK_LSHIFT:
			SetShift(true);
			break;
		case SDLK_RSHIFT:
			SetShift(true);
			break;
		case SDLK_LCTRL:
			SetCTRL(true);
			break;
		case SDLK_RCTRL:
			SetCTRL(true);
			break;
		}
	}
	else
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			return DELETE_CAPTIONS;
			break;
		case SDLK_e:
			currentime_ = ENGLISH;
			tempstring_ = "";
			return SET_TEXT_ENGLISH;
			break;
		case SDLK_j:
			currentime_ = JAPANESE;
			return SET_TEXT_JAPANESE;
			break;
		case SDLK_v:
			currenttext_ = currenttext_ + SDL_GetClipboardText();
			if (currenttexttexture_ != NULL)
				currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
			break;
		case SDLK_RETURN:
			FinalizeCurrentText();
			break;
		case SDLK_KP_ENTER:
			FinalizeCurrentText();
			break;
		}
	}

	return NO_MACRO;
}

char KeyboardEntry::KeyDownInputEnglish(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_SPACE:
		InsertCharacter(' ');
		break;
	case SDLK_BACKSPACE:
		DeleteCharacter();
		return 0;
	case SDLK_a:
		return 'a';
	case SDLK_b:
		return 'b';
	case SDLK_c:
		return 'c';
	case SDLK_d:
		return 'd';
	case SDLK_e:
		return 'e';
	case SDLK_f:
		return 'f';
	case SDLK_g:
		return 'g';
	case SDLK_h:
		return 'h';
	case SDLK_i:
		return 'i';
	case SDLK_j:
		return 'j';
	case SDLK_k:
		return 'k';
		break;
	case SDLK_l:
		return 'l';
	case SDLK_m:
		return 'm';
	case SDLK_n:
		return 'n';
	case SDLK_o:
		return 'o';
	case SDLK_p:
		return 'p';
	case SDLK_q:
		return 'q';
	case SDLK_r:
		return 'r';
	case SDLK_s:
		return 's';
	case SDLK_t:
		return 't';
	case SDLK_u:
		return 'u';
	case SDLK_v:
		return 'v';
	case SDLK_w:
		return 'w';
	case SDLK_x:
		return 'x';
	case SDLK_y:
		return 'y';
	case SDLK_z:
		return 'z';
	}

	return 0;
}

void KeyboardEntry::KeyDownInputJapanese(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_a:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ÇÒy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"ÇµÇ·";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"ÇøÇ·";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"Ç≥";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ÇÕ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ÇŒ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"Çæ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"Ç™";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"Ç∂Ç·";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"Ç©";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"Ç‹";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"Çœ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ÇÁ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"ÇΩ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"ÇÌ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"Ç‚";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"Ç¥";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ÇÒ")
																			{
																				tempstring_ = tempstring_ + u8"Ç»";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"Ç–Ç·";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"Ç´Ç·";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"Ç›Ç·";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"ÇËÇ·";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"ÇÒy")
																								{
																									tempstring_ = tempstring_ + u8"Ç…Ç·";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"Ç¨Ç·";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"Ç—Ç·";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"Ç“Ç·";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"Ç†";
			nexttempchar_ = "";
		}
		break;
	case SDLK_b:
		if (std::string("b").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "b";
			}
			else
			{
				if (nexttempchar_ == "b")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "b";
		}
		break;
	case SDLK_c:
		if (std::string("c").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "c";
			}
			else
			{
				if (nexttempchar_ == "c")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "c";
		}
		break;
	case SDLK_d:
		if (std::string("d").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "d";
			}
			else
			{
				if (nexttempchar_ == "d")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "d";
		}
		break;
	case SDLK_e:
		if ((std::string("s h b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ÇÒy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "s")
			{
				tempstring_ = tempstring_ + u8"Çπ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"Ç÷";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"Ç◊";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"Ç≈";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"Ç∞";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"ÇØ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"Çﬂ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"Çÿ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"ÇÍ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"Çƒ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ÇÔ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"Ç∫";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ÇÒ")
															{
																tempstring_ = tempstring_ + u8"ÇÀ";
																nexttempchar_ = "";
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"Ç¶";
			nexttempchar_ = "";
		}
		break;
	case SDLK_f:
		if (std::string("f").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "f";
			}
			else
			{
				if (nexttempchar_ == "f")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "f";
		}
		break;
	case SDLK_g:
		if (std::string("g").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "g";
			}
			else
			{
				if (nexttempchar_ == "g")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "g";
		}
		break;
	case SDLK_h:
		if (std::string("csh").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "h";
			}
			else
			{
				if (nexttempchar_ == "s")
				{
					nexttempchar_ = "sh";
				}
				else
				{
					if (nexttempchar_ == "c")
					{
						nexttempchar_ = "ch";
					}
					else
					{
						if (nexttempchar_ == "h" && nexttempchar_ != "sh" && nexttempchar_ != "ch")
						{
							tempstring_ = tempstring_ + u8"Ç¡";
						}
					}
				}
			}
		}
		break;
	case SDLK_i:
		if ((std::string("sh ch b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ÇÒy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"Çµ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"Ç–";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"Ç—";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"Ç¿";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"Ç¨";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"Ç´";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"Ç›";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"Ç“";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"ÇË";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"Çø";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ÇÓ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"Ç∂";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ÇÒ")
															{
																tempstring_ = tempstring_ + u8"Ç…";
																nexttempchar_ = "";
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"Ç¢";
			nexttempchar_ = "";
		}
		break;
	case SDLK_j:
		if (std::string("j").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "j";
			}
			else
			{
				if (nexttempchar_ == "j")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "j";
		}
		break;
	case SDLK_k:
		if (std::string("k").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "k";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "k";
		}
		break;
	case SDLK_m:
		if (std::string("m").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "m";
			}
			else
			{
				if (nexttempchar_ == "m")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "m";
		}
		break;
	case SDLK_n:
		if (std::string(u8"ÇÒ").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = u8"ÇÒ";
			}
			else
			{
				if (nexttempchar_ == u8"ÇÒ")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = u8"ÇÒ";
		}
		break;
	case SDLK_o:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ÇÒy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"ÇµÇÂ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"ÇøÇÂ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"Çª";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ÇŸ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"Ç⁄";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"Ç«";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"Ç≤";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"Ç∂ÇÂ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"Ç±";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"Ç‡";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"Ç€";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ÇÎ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"Ç∆";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"Ç";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"ÇÊ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"Çº";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ÇÒ")
																			{
																				tempstring_ = tempstring_ + u8"ÇÃ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"Ç–ÇÂ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"Ç´ÇÂ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"Ç›ÇÂ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"ÇËÇÂ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"ÇÒy")
																								{
																									tempstring_ = tempstring_ + u8"Ç…ÇÂ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"Ç¨ÇÂ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"Ç—ÇÂ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"Ç“ÇÂ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"Ç®";
			nexttempchar_ = "";
		}
		break;
	case SDLK_p:
		if (std::string("p").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "p";
			}
			else
			{
				if (nexttempchar_ == "p")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "p";
		}
		break;
	case SDLK_r:
		if (std::string("r").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "r";
			}
			else
			{
				if (nexttempchar_ == "r")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "r";
		}
		break;
	case SDLK_s:
		if (std::string("ts").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "s";
			}
			else
			{
				if (nexttempchar_ == "s" && nexttempchar_ != "ts")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
				else
				{
					if (nexttempchar_ == "t")
					{
						nexttempchar_ = "ts";
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "s";
		}
		break;
	case SDLK_t:
		if (std::string("t").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "t";
			}
			else
			{
				if (nexttempchar_ == "t")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "t";
		}
		break;
	case SDLK_u:
		if ((std::string("sh ch hy by d gy j ky my py ry ts w z f").find(nexttempchar_) != std::string::npos || std::string(u8"ÇÒy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"ÇµÇ„";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"ÇøÇ„";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"Ç∑";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "f")
						{
							tempstring_ = tempstring_ + u8"Ç”";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"Ç‘";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"Ç√";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ÇÆ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"Ç∂Ç„";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"Ç≠";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"Çﬁ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"Ç’";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ÇÈ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "ts")
															{
																tempstring_ = tempstring_ + u8"Ç¬";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "y")
																{
																	tempstring_ = tempstring_ + u8"Ç‰";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "z")
																	{
																		tempstring_ = tempstring_ + u8"Ç∏";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == u8"ÇÒ")
																		{
																			tempstring_ = tempstring_ + u8"Ç ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == "hy")
																			{
																				tempstring_ = tempstring_ + u8"Ç–Ç„";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "ky")
																				{
																					tempstring_ = tempstring_ + u8"Ç´Ç„";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "my")
																					{
																						tempstring_ = tempstring_ + u8"Ç›Ç„";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "ry")
																						{
																							tempstring_ = tempstring_ + u8"ÇËÇ„";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == u8"ÇÒy")
																							{
																								tempstring_ = tempstring_ + u8"Ç…Ç„";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == "gy")
																								{
																									tempstring_ = tempstring_ + u8"Ç¨Ç„";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "by")
																									{
																										tempstring_ = tempstring_ + u8"Ç—Ç„";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "py")
																										{
																											tempstring_ = tempstring_ + u8"Ç“Ç„";
																											nexttempchar_ = "";
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"Ç§";
			nexttempchar_ = "";
		}
		break;
	case SDLK_w:
		if (std::string("w").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "w";
			}
			else
			{
				if (nexttempchar_ == "w")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "w";
		}
		break;
	case SDLK_y:
		if (std::string("k h m r g b p").find(nexttempchar_) != std::string::npos || std::string(u8"ÇÒ").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "y";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					nexttempchar_ = "ky";
				}
				else
				{
					if (nexttempchar_ == u8"ÇÒ")
					{
						nexttempchar_ = u8"ÇÒy";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							nexttempchar_ = "hy";
						}
						else
						{
							if (nexttempchar_ == "m")
							{
								nexttempchar_ = "my";
							}
							else
							{
								if (nexttempchar_ == "m")
								{
									nexttempchar_ = "my";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										nexttempchar_ = "gy";
									}
									else
									{
										if (nexttempchar_ == "b")
										{
											nexttempchar_ = "by";
										}
										else
										{
											if (nexttempchar_ == "p")
											{
												nexttempchar_ = "py";
											}
											else
											{
												if (nexttempchar_ == "r")
												{
													nexttempchar_ = "ry";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "y";
		}
		break;
	case SDLK_z:
		if (std::string("z").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "z";
			}
			else
			{
				if (nexttempchar_ == "z")
				{
					tempstring_ = tempstring_ + u8"Ç¡";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "z";
		}
		break;
	case SDLK_MINUS:
		tempstring_ = tempstring_ + nexttempchar_ + u8"Å[";
		nexttempchar_ = "";
		break;
	case SDLK_BACKSPACE:
		if (nexttempchar_ != "")
		{
				nexttempchar_.pop_back();
		}
		else
		{
			if (tempstring_ != "")
			{
				tempstring_.pop_back();
			}
			else
			{
				DeleteCharacter();
			}
		}
		break;
	case SDLK_RETURN:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	case SDLK_KP_ENTER:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	}
}

void KeyboardEntry::KeyUpInput(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LSHIFT:
		SetShift(false);
		break;
	case SDLK_RSHIFT:
		SetShift(false);
		break;
	case SDLK_LCTRL:
		SetCTRL(false);
		break;
	case SDLK_RCTRL:
		SetCTRL(false);
		break;
	}
}

TextInput *KeyboardEntry::GetTexture()
{
	return currenttexttexture_;
}
