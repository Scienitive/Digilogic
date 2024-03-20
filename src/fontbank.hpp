#ifndef FONTBANK_HPP
#define FONTBANK_HPP

#include <cstddef>
#include <list>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <utility>

struct PairHash {
	size_t operator()(const std::pair<std::string, float> &p) const;
};

struct FontEntry {
	std::pair<std::string, float> font_key;
	Font font;

	FontEntry(std::pair<std::string, float>, Font);
};

class FontBank {
	std::list<FontEntry> font_list;
	std::unordered_map<std::pair<std::string, float>, std::list<FontEntry>::iterator, PairHash> font_map;

	const size_t MAX_SIZE = 30;

public:
	static FontBank &get();
	~FontBank();
	FontBank(const FontBank &other) = delete;
	FontBank &operator=(const FontBank &other) = delete;

	Font get_font(std::string font_name, float font_size);

private:
	FontBank();
};

#endif
