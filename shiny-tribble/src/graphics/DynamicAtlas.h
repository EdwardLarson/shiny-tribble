#pragma once

#ifndef DYNAMICATLAS_H
#define DYNAMICATLAS_H

#include <iostream>
#include <list>
#include <SDL.h>
#include "../utility/datastructures/PooledList.h"

namespace graphics{

class DynamicAtlas {
private:
	typedef SDL_Rect RectangleType;
	typedef utility::datastructures::PooledList<RectangleType> RectangleContainer;
	//typedef std::list<RectangleType> RectangleContainer;

public:
	DynamicAtlas(unsigned int width, unsigned int height, unsigned int max_rectangles);
	virtual ~DynamicAtlas();

	RectangleType addRectangle(int width, int height);
	bool removeRectangle(unsigned int x, unsigned int y, int width, int height);
	void clear();

	//output
	//void print() const;
	//void printLabeled() const;
	//void printInverseLabeled() const;
protected:
private:

	RectangleContainer openRectangles;
	RectangleContainer filledRectangles;
	unsigned int totalWidth;
	unsigned int totalHeight;

	RectangleContainer::iterator findFittingRectangle(int width, int height);
	void breakUpRectangle(RectangleContainer::iterator oldRect, unsigned int subRectW, unsigned int subRectH);
	void addFilledRectangle(const RectangleType& rect);
	void addOpenRectangle(const RectangleType& rect);
	void reAddRectangles();
	static inline RectangleType emptyRectangle();
	static inline unsigned int getVolume(const RectangleType& rect);
	static inline bool equal(const RectangleType& left, const RectangleType& right);
};

}

#endif