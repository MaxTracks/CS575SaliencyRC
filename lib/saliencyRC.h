#ifndef SMOOTH_COLORS_H
#define SMOOTH_COLORS_H

#include <map>
#include <vector>
#include "seg.h"


std::multimap<double, PixelRegion*> regionSaliency(std::vector<PixelRegion*> regions);
void maskBySaliency(std::multimap<double, PixelRegion*> salMap);


#endif // SMOOTH_COLORS_H
