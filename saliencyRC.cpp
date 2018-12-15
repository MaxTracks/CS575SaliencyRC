#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include "EasyBMP_BMP.h"
#include "EasyBMP.h"
#include "EasyBMP_DataStructures.h"
#include "seg.h"
#include "saliencyRC.h"

#define SIGMA_SQRD 0.4
#define MAX_COLOR 256
#define FREQ_THRESHOLD 5

union PixelColor {
	RGBApixel rgba;
	int colorint;
};


static double colorDist(PixelColor a, PixelColor b) {
	// Formula taken from https://stackoverflow.com/questions/4754506/color-similarity-distance-in-rgba-color-space
	RGBApixel p1 = a.rgba;
	RGBApixel p2 = b.rgba;

	// Multiply the alphas
	double r1 = p1.Red * p1.Alpha;
	double r2 = p2.Red * p2.Alpha;
	double g1 = p1.Green * p1.Alpha;
	double g2 = p2.Green * p2.Alpha;
	double b1 = p1.Blue * p1.Alpha;
	double b2 = p2.Blue * p2.Alpha;

	double rdiff = std::max(pow(r1 - r2,2), pow(r1 - r2 - p1.Alpha + p2.Alpha, 2));	
	
	double gdiff = std::max(pow(g1 -g2 ,2), pow(g1 - g2 - p1.Alpha + p2.Alpha,2));	
	
	double bdiff = std::max(pow(b1 - b2, 2), pow(b1 - b2 - p1.Alpha + p2.Alpha,2));

	return rdiff + gdiff + bdiff;
}
	
static double colorDistPixelRegion(std::map<int, double> salA, std::map<int, double> salB)
{
	int i,j;
	PixelColor a;
	PixelColor b; 

	double dist = 0;
	for(const auto& elemA : salA) {
		for(const auto& elemB : salB) {
			a.colorint = elemA.first;
			b.colorint = elemB.first;
			dist += elemA.second * elemB.second * colorDist(a, b);
		}
	}
	return dist;
}



static std::map<int, double> colorSaliency(PixelRegion * r) {
	int i,j;
	std::map<int, int> colorFreq;
	int numColors;
	PixelColor clr;
	std::multimap<double, int> freqSalMap;
	std::map<int, double> salMap;
	std::vector<Pixel*> pxls = r->getPixels();

	// Get the frequncy of all of the colors
	for(i = 0; i < pxls.size(); i++) {
		clr.rgba.Red = pxls[i]->gred();
		clr.rgba.Green = pxls[i]->ggreen();
		clr.rgba.Blue = pxls[i]->gblue();
		clr.rgba.Alpha = pxls[i]->galpha();

		//std::map<int, int>::iterator iter = colorFreq.find(clr.colorint);
		if(colorFreq.find(clr.colorint) == colorFreq.end())
			colorFreq[clr.colorint] = 1;
		else
			colorFreq[clr.colorint]++;
	}

	numColors = colorFreq.size();
	for(auto const &elem : colorFreq) {
		freqSalMap.insert(std::pair<int, double>(elem.first, ((double) elem.second)/((double) numColors)));
	}

	for(auto const &elem : freqSalMap) {
		if(elem.first > FREQ_THRESHOLD)
			salMap[elem.second] = elem.first;
		else
			break;
	}
	
	return salMap;
}

double spaceDistPixelRegion(PixelRegion* a, PixelRegion* b) {
	double deltaX = 5.6;
	double deltaY = 7.3;	

	return sqrt(pow(deltaX,2) + pow(deltaY,2));
}

std::multimap<double, PixelRegion*> regionSaliency(std::vector<PixelRegion*> regions) {
	int i,j;
	std::multimap<double, PixelRegion*> salMap;
	std::vector<double> regSal;

	for(const auto& r : regions) {
		regSal.push_back(0);
	}
	for(i = 0; i < regions.size(); i++) {
		for(j = 0; j < regions.size(); j++) {
			if(i == j) 
				continue;
	//		regSal[i] += exp(-(spaceDistPixelRegion(regions[i], regions[j]))/SIGMA_SQRD) * regions[i].size() * 
	//			colorDistPixelRegion(colorSaliency(regions[i]), colorSaliency(regions[j]));
			regSal[i] += regions[i]->size() * colorDistPixelRegion(colorSaliency(regions[i]), colorSaliency(regions[j]));
		}
	}

	for(i = 0; i < regions.size(); i++) {
		salMap.insert(std::pair<double, PixelRegion*>(regSal[i], regions[i]));
	}
	return salMap;
}

void maskBySaliency(std::multimap<double, PixelRegion*> salMap) {
	unsigned int step = MAX_COLOR / salMap.size();
	unsigned int clrVal = 0;

	for(auto& elem : salMap) {
		elem.second->change(clrVal, clrVal, clrVal, clrVal);
		clrVal += step;
	}
}

