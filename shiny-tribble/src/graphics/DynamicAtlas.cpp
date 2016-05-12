#include "DynamicAtlas.h"

using namespace graphics;

DynamicAtlas::DynamicAtlas(unsigned int width, unsigned int height, unsigned int max_rectangles)
	: openRectangles(max_rectangles), filledRectangles(max_rectangles), totalWidth(width), totalHeight(height){
	//atlas starts out empty, therefore:
	//initialize the list of open rectangles with a rectangle representing the whole atlas
	RectangleType initialRect = {0, 0, totalWidth, totalHeight};
	openRectangles.push_back(initialRect);
}

DynamicAtlas::~DynamicAtlas() {

}

//adds a rectangle to the DynamicAtlas of the given width and height
//if successful, returns the rectangle with the position it was added at and the given dimensions
//returns a rectangle with position (0, 0) and dimensions 0 by 0 if there was no space
DynamicAtlas::RectangleType DynamicAtlas::addRectangle(unsigned int width, unsigned int height) {
	//first see if there is enough space in the whole atlas
	if (width > totalWidth || height > totalHeight) return emptyRectangle();

	//now walk through the list to find the smallest rectangle which will fit
	RectangleContainer::iterator iter = findFittingRectangle(width, height);

	//now break up that rectangle, filling in some of it and breaking up the rest into more rectangles
	if (iter != openRectangles.end()) {
		RectangleType nowFilled = { iter->x, iter->y, width, height };
		breakUpRectangle(iter, width, height);
		addFilledRectangle(nowFilled);
		return nowFilled;
	}
	else {
		//no appropriately sized rectangle
		return emptyRectangle();
	}
}

//remove a rectangle from the DynamicAtlas
bool DynamicAtlas::removeRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	RectangleType rect = { x, y, width, height };

	//see if a rectangle matches this one
	RectangleContainer::iterator iter;
	for (iter = filledRectangles.begin(); iter != filledRectangles.end(); ++iter) {
		if (equal(rect, *iter)) break;
	}

	//if the rectangle is contained, remove it and return it
	if (iter != filledRectangles.end()) {
		addOpenRectangle(rect);
		filledRectangles.erase(iter);
		//reAddRectangleTypes();
		return true;
	}

	return false;
}

//find the first open rectangle that can fit the given rectangle
DynamicAtlas::RectangleContainer::iterator DynamicAtlas::findFittingRectangle(unsigned int width, unsigned int height) {
	RectangleContainer::iterator iter;
	for (iter = openRectangles.begin(); iter != openRectangles.end(); ++iter) {
		if (iter->w >= width && iter->h >= height) break;
	}

	return iter;
}

//Fill a portion of an open rectangle with a new rectangle
//Break up the original open rectangle into the two new rectangles representing open space
void DynamicAtlas::breakUpRectangle(RectangleContainer::iterator oldRect, unsigned int subRectW, unsigned int subRectH) {
	//for safety
	if (oldRect == openRectangles.end()) return;

	//get the remaining width and height after filling in the rectangle
	unsigned int remainingW = oldRect->w - subRectW;
	unsigned int remainingH = oldRect->h - subRectH;

	//rectangles representing the new open spaces below and to the right of the filled portion
	//e.g.
	//   X-----------------X
	//   |f f f f . . . . .|
	//   |f f f f . . . . .|
	//   |f f f f . . . . .|
	//   |f f f f . . . . .|
	//   |f f f f . . . . .|
	//   |, , , , . . . . .|
	//   |, , , , . . . . .|
	//   |, , , , . . . . .|
	//   X-----------------X
	// 'f' = filled by the new rectangle; ',' = below; '.' = right

	RectangleType below;
	RectangleType right;

	if (subRectH > subRectW) {
		//below becomes the rectangle below, right becomes big rectangle to the right
		below.x = oldRect->x;
		below.y = oldRect->y + subRectH;
		below.w = subRectW;
		below.h = remainingH;

		right.x = oldRect->x + subRectW;
		right.y = oldRect->y;
		right.w = remainingW;
		right.h = oldRect->h;
	}
	else {
		//below becomes the big rectangle below, right becomes rectangle to the right
		below.x = oldRect->x;
		below.y = oldRect->y + subRectH;
		below.w = oldRect->w;
		below.h = remainingH;

		right.x = oldRect->x + subRectW;
		right.y = oldRect->y;
		right.w = remainingW;
		right.h = subRectH;
	}

	//erase the old open rectangle and add the new smaller open rectangles
	openRectangles.erase(oldRect);

	if (below.w != 0 && below.h != 0) addOpenRectangle(below);
	if (right.w != 0 && right.h != 0) addOpenRectangle(right);
}

//Add a filled rectangle to the list of filled rectangles
//Sorted in descending order
void DynamicAtlas::addFilledRectangle(const RectangleType& rect) {
	RectangleContainer::iterator iter;
	for (iter = filledRectangles.begin(); iter != filledRectangles.end(); ++iter) {
		if (getVolume(rect) > getVolume(*iter)) break;
	}

	filledRectangles.insert(iter, rect);
}

//Add an open rectangle to the list of filled rectangles
//Sorted in ascending order
void DynamicAtlas::addOpenRectangle(const RectangleType& rect) {
	RectangleContainer::iterator iter;
	for (iter = openRectangles.begin(); iter != openRectangles.end(); ++iter) {
		if (getVolume(rect) < getVolume(*iter)) break;
	}

	openRectangles.insert(iter, rect);
}

//Reverts whole thing and re-adds each of the rectangles one by one, in order of largest volume to smallest
void DynamicAtlas::reAddRectangles() {
	openRectangles.clear();
	RectangleType initialRect = { 0, 0, totalWidth, totalHeight };
	openRectangles.push_back(initialRect);

	for (RectangleContainer::iterator iter = filledRectangles.begin(); iter != filledRectangles.end(); ++iter) {
		breakUpRectangle(findFittingRectangle(iter->w, iter->h), iter->w, iter->h);
	}
}

DynamicAtlas::RectangleType DynamicAtlas::emptyRectangle() {
	RectangleType output = { 0, 0, 0, 0 };
	return output;
}

unsigned int DynamicAtlas::getVolume(const RectangleType& rect) {
	return rect.w * rect.h;
}

bool DynamicAtlas::equal(const RectangleType& left, const RectangleType& right) {
	return (left.h == right.h) && (left.w == right.w) && (left.x == right.x) && (left.y == right.y);
}

//OUTPUT
/*
void DynamicAtlas::print() const {
	std::cout << "Printing a dynamic atlas with " << openRectangles.size() << " open rectangles" << std::endl;
	//first create temporary array:
	bool atlasRep[totalWidth * totalHeight];
	//point at x, y = atlasRep(x * totalHeight + y)

	for (unsigned int x = 0; x < totalWidth; x++) {
		for (unsigned int y = 0; y < totalHeight; y++) {
			atlasRep[(x * totalHeight) + y] = true;
		}
	}

	//now fill in where all of the open rectangles are
	for (RectangleContainer::const_iterator iter = openRectangles.begin(); iter != openRectangles.end(); ++iter) {
		for (unsigned int x = iter->x; x < iter->x + iter->w; ++x) {
			for (unsigned int y = iter->y; y < iter->y + iter->h; ++y) {
				atlasRep[(x * totalHeight) + y] = false;
			}
		}
	}

	//finally, print the atlas
	for (unsigned int x = 0; x < totalWidth; x++) {
		for (unsigned int y = 0; y < totalHeight; y++) {
			std::cout << (atlasRep[(x * totalHeight) + y] ? 'O' : '-') << ' ';
		}
		std::cout << std::endl;
	}
}

void DynamicAtlas::printLabeled() const {
	std::cout << "Printing a dynamic atlas with " << openRectangles.size() << " open rectangles" << std::endl;
	//first create temporary array:
	char atlasRep[totalWidth * totalHeight];
	//point at x, y = atlasRep(x * totalHeight + y)

	for (unsigned int x = 0; x < totalWidth; x++) {
		for (unsigned int y = 0; y < totalHeight; y++) {
			atlasRep[(x * totalHeight) + y] = 'O';
		}
	}

	//now fill in where all of the open rectangles are
	char rectChar = 'a';
	for (RectangleContainer::const_iterator iter = openRectangles.begin(); iter != openRectangles.end(); ++iter) {
		for (unsigned int x = iter->x; x < iter->x + iter->w; ++x) {
			for (unsigned int y = iter->y; y < iter->y + iter->h; ++y) {
				atlasRep[(x * totalHeight) + y] = rectChar;
			}
		}

		++rectChar;
	}

	//finally, print the atlas
	for (unsigned int x = 0; x < totalWidth; x++) {
		for (unsigned int y = 0; y < totalHeight; y++) {
			std::cout << atlasRep[(x * totalHeight) + y] << ' ';
		}
		std::cout << std::endl;
	}
}

void DynamicAtlas::printInverseLabeled() const {
	std::cout << "Printing a dynamic atlas with " << filledRectangles.size() << " filled rectangles" << std::endl;
	//first create temporary array:
	char atlasRep[totalWidth * totalHeight];
	//point at x, y = atlasRep(x * totalHeight + y)

	for (unsigned int x = 0; x < totalWidth; x++) {
		for (unsigned int y = 0; y < totalHeight; y++) {
			atlasRep[(x * totalHeight) + y] = '-';
		}
	}

	//now fill in where all of the open rectangles are
	char rectChar = 'a';
	for (RectangleContainer::const_iterator iter = filledRectangles.begin(); iter != filledRectangles.end(); ++iter) {
		for (unsigned int x = iter->x; x < iter->x + iter->w; ++x) {
			for (unsigned int y = iter->y; y < iter->y + iter->h; ++y) {
				atlasRep[(x * totalHeight) + y] = rectChar;
			}
		}

		++rectChar;
	}

	//finally, print the atlas
	for (unsigned int x = 0; x < totalWidth; x++) {
		for (unsigned int y = 0; y < totalHeight; y++) {
			std::cout << atlasRep[(x * totalHeight) + y] << ' ';
		}
		std::cout << std::endl;
	}
}
*/