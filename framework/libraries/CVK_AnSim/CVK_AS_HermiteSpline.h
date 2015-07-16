#ifndef __CVK_AS_HERMITE_SPLINE_H
#define __CVK_AS_HERMITE_SPLINE_H

#include "CVK_AS_HermiteSplineControlPoint.h"
#include "glm/glm.hpp"
#include <vector>

namespace CVK
{

class HermiteSpline
{
public:
	HermiteSpline();
	virtual ~HermiteSpline();
	void evaluateHermiteSpline(float u, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, glm::vec3 &point, glm::vec3 &tangent);

	inline void addControlPoint(HermiteSplineControlPoint* c){ mControlPoints.push_back(c); }
	void generateRenderVertices();
	std::vector<HermiteSplineControlPoint*>* getControlPointsPtr(){ return &mControlPoints; }
	std::vector<glm::vec3>* getVerticesPtr(){ return &mVertices; }
	std::vector<glm::vec3>* getTangentsPtr(){ return &mTangents; }

private:
	std::vector<HermiteSplineControlPoint*> mControlPoints;
	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mTangents;

	void deCasteljau(float t, std::vector<glm::vec3> &cp, glm::vec3 &point, glm::vec3 &tangent);
	void sampleHermiteSpline(HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, int numVerts);
};

};
#endif //__CVK_AS_HERMITE_SPLINE_H
