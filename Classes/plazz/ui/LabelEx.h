#ifndef _LabelEx_H_
#define _LabelEx_H_

#include "cocos2d.h"
USING_NS_CC;

class LabelEx : public Node
{
public:
	static LabelEx* create(const std::string& text, const std::string& font, float fontSzie);
	static LabelEx* create(const std::string& text, const std::string& font, float fontSzie, const Size& size, TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::CENTER);

public:
	LabelEx();
	~LabelEx();

	bool init(const std::string&, const std::string& font, float fontSzie);
	bool init(const std::string&, const std::string& font, float fontSzie, const Size& size, TextHAlignment hAlignment, TextVAlignment vAlignment);

	void setStrokeColor(const Color3B& col, float size = 1);
	void setColor(const Color3B& col);
	void setString(const std::string& text);
	virtual void setAnchorPoint(const Point& anchorPoint);
	virtual const Point& getAnchorPoint();
private:
	Label* mROutLine;
	Label* mText;

};
#endif // _LabelEx_H_