#include "CVK_AS_HermiteSpline.h"

#define ONE_THIRD (1.0f / 3.0f)

CVK::HermiteSpline::HermiteSpline()
{
}

CVK::HermiteSpline::~HermiteSpline()
{
}

void CVK::HermiteSpline::generateRenderVertices(){
	std::vector<HermiteSplineControlPoint*>::iterator cpIt = mControlPoints.begin();
	while(cpIt != mControlPoints.end() - 1){
		sampleHermiteSpline(*cpIt, *(cpIt + 1), 100);
		cpIt++;
	}
}

void CVK::HermiteSpline::sampleHermiteSpline(HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, int numVerts)
{
	// TODO
	for(int i = 0; i < numVerts; i++)
	{
		glm::vec3 position, tangent;
		evaluateHermiteSpline((float) i/(numVerts-1),c0, c1, position, tangent);
		mVertices.push_back(position);
		mTangents.push_back(tangent);
	}
}

void CVK::HermiteSpline::evaluateHermiteSpline(float t, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, glm::vec3 &point, glm::vec3 &tangent)
{
	// TODO
	std::vector<glm::vec3> bp;
	bp.push_back(c0->getPosition());
	bp.push_back(c0->getPosition() + ONE_THIRD * c0->getDirection());
	bp.push_back(c1->getPosition() - ONE_THIRD * c1->getDirection());
	bp.push_back(c1->getPosition());
	deCasteljau(t, bp, point, tangent);

}

void CVK::HermiteSpline::deCasteljau(float t, std::vector<glm::vec3> &cp, glm::vec3 &point, glm::vec3 &tangent)
{
	//TODO
	if(cp.size() == 2)
	{
		point = (1-t) * cp.at(0) + t * cp.at(1);
		tangent = cp.at(0) - cp.at(1);
		tangent = glm::normalize(tangent);
	}
	else
	{
	std::vector<glm::vec3> ncp;
	std::vector<glm::vec3>::iterator it = cp.begin();
	while( it != cp.end()-1)
	{
		ncp.push_back((1-t) * (*it) + t * (*(it+1)));
		it ++;
	}
	deCasteljau(t, ncp, point, tangent);
	}
}
