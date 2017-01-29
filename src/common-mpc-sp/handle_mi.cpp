#include "handle_mi.h"

#include <cstring> //memcpy
#include <iostream> //cout
#include <sstream>

#include "../impl-headers/sprite.h"
#include "../impl-headers/video.h"
#include "../impl-headers/wall.h"

namespace Freeworld { namespace Common {

void* raw; //temporary variable

MiParser::MiParser() {
}

MiParser::~MiParser() {
	for (auto iterator = sprites.begin(); iterator != sprites.end(); iterator++) {
		Sprite* sprite = iterator->second;
		if (sprite != NULL)
			delete sprite;
	}
	if (current_data_length)
		delete current_data;
}

void* MiParser::read(int length) {
	if (current_data_length < current_data_read + length) {
		//not enough data remaining to read
		return NULL;
	}
	void* result = current_data + current_data_read;
	current_data_read += length;
	return result;
}

void MiParser::read_reset() {
	current_data_read = current_data_read_reset;
}

void MiParser::read_reset_set() {
	current_data_read_reset = current_data_read;
}

//helper macros

#define READ_I32_OR_RESET(i) \
	raw = read(sizeof(int32_t)); \
	if (raw == NULL) { \
		 read_reset(); \
		 return; \
	} \
	int32_t i = * (int32_t*) raw;

#define READ_U8_OR_RESET(u) \
	raw = read(sizeof(uint8_t)); \
	if (raw == NULL) { \
		 read_reset(); \
		 return; \
	} \
	uint8_t u = * (uint8_t*) raw;

#define DECODE_F(i) ((float)i)/65536.f

#define READ_F32_OR_RESET(f) \
	raw = read(sizeof(int32_t)); \
	if (raw == NULL) { \
		 read_reset(); \
		 return; \
	} \
	float f = DECODE_F( * (int32_t*) raw );

void MiParser::parse_mi (int length, uint8_t* data) {
	if (length == 0) {
		return;
	}
	current_data_read = 0;
	if (current_data_length) {
		//a previous transmission was incomplete,
		//hence append new data and try again
		uint8_t* new_data = new uint8_t[current_data_length + length];
		memcpy(new_data, current_data, current_data_length);
		memcpy(new_data + current_data_length, data, length);
		delete current_data;
		current_data = new_data;
		current_data_length += length;
	}
	else {
		//first transmission or last one was completed
		current_data = data;
		current_data_length = length;
	}
	while (current_data_read < current_data_length) {
		read_reset_set();
		READ_I32_OR_RESET(type_i)
		Mi type = (Mi)type_i;
		if (type == Mi::SET_RESOLUTION) {
			READ_I32_OR_RESET(w)
			READ_I32_OR_RESET(h)
			Freeworld::Impl::set_resolution(w, h);
		}
		else if (type == Mi::FRAME_COMPLETED) {
			Freeworld::Impl::frame_completed();
		}
		else if (type == Mi::FILL_RECT) {
			READ_I32_OR_RESET(x)
			READ_I32_OR_RESET(y)
			READ_I32_OR_RESET(w)
			READ_I32_OR_RESET(h)
			READ_U8_OR_RESET(r)
			READ_U8_OR_RESET(g)
			READ_U8_OR_RESET(b)
			Freeworld::Impl::fill_rect(x,y,w,h, r,g,b);
		}
		else if (type == Mi::SPRITE) {
			READ_I32_OR_RESET(id)
			READ_I32_OR_RESET(x)
			READ_I32_OR_RESET(y)
			Sprite* sprite = sprites[id];
			if (sprite == NULL)
				sprite = (sprites[id] = new Sprite(id));
			sprite->draw(x, y);
		}
		else if (type == Mi::WALL) {
			READ_I32_OR_RESET(id)
			READ_I32_OR_RESET(x)
			READ_I32_OR_RESET(y)
			READ_I32_OR_RESET(w)
			READ_I32_OR_RESET(h)
			READ_I32_OR_RESET(offset_x)
			READ_I32_OR_RESET(offset_y)
			Wall* wall = walls[id];
			if (wall == NULL)
				wall = (walls[id] = new Wall(id));
			wall->draw(x, y, w, h, offset_x, offset_y);
		}
		else if (type == Mi::BACKGROUND) {
		}
		else if (type == Mi::BACKGROUND_COLOR) {
		}
		else if (type == Mi::SOUND) {
		}
		else if (type == Mi::MUSIC) {
		}
		else {
			std::cout << "Unknown MI type " << (int)type << std::endl;
			break;
		}
	}
	//not returned, hence all current data has been read
	//or unknown MI type
	delete current_data;
	current_data_length = 0;
}

} } //end of namespace Freeworld::Common
