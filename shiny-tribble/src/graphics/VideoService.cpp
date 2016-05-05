#include "VideoService.h"

using namespace graphics;

VideoService::~VideoService(){
}

//NullVideoService
//========================================

NullVideoService::NullVideoService() {
}

NullVideoService::~NullVideoService() {
}

void NullVideoService::render(const std::string& texturePath, int x, int y) {

}

void NullVideoService::loadTexture(const std::string& filename) {

}

//DefaultVideoService
//========================================

DefaultVideoService::DefaultVideoService() {

}

DefaultVideoService::~DefaultVideoService() {

}

void DefaultVideoService::render(const std::string& texturePath, int x, int y) {

}

void DefaultVideoService::loadTexture(const std::string& filename) {

}