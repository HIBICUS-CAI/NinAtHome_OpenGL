#pragma once

#include <string>

unsigned int LoadTexture(std::string fileName);

void UnloadTexture(unsigned int texture);

void SetTexture(unsigned int texture);
