#include "fontbank.hpp"
#include <cmath>
#include <iostream>
#include <raylib.h>

size_t PairHash::operator()(const std::pair<std::string, float> &p) const {
	auto hash1 = std::hash<std::string>{}(p.first);
	auto hash2 = std::hash<float>{}(p.second);
	return hash1 ^ (hash2 << 1);
}

FontEntry::FontEntry(std::pair<std::string, float> key, Font font) : font_key(key), font(font) {}

FontBank::FontBank() {}

FontBank::~FontBank() {
	for (auto &pair : this->font_map) {
		UnloadFont(pair.second->font);
	}
}

Font FontBank::get_font(std::string font_name, float font_size) {
	std::cout << this->font_list.size() << std::endl;
	font_size = std::round(font_size);
	std::pair<std::string, float> pair = {font_name, font_size};
	const auto &map_entry = this->font_map.find(pair);
	if (map_entry != this->font_map.end()) {
		this->font_list.splice(font_list.begin(), font_list, font_map[pair]);
		return map_entry->second->font;
	} else {
		auto it = this->font_list.insert(this->font_list.begin(),
										 FontEntry(pair, LoadFontEx(font_name.c_str(), font_size, NULL, 0)));
		this->font_map[pair] = it;

		if (this->font_list.size() > this->MAX_SIZE) {
			auto least_recently_used = this->font_list.back();
			UnloadFont(least_recently_used.font);
			this->font_list.pop_back();
			this->font_map.erase(least_recently_used.font_key);
		}

		return it->font;
	}
}
