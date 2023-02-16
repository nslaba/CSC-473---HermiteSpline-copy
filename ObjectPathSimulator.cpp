#include "ObjectPathSimulator.h"

ObjectPathSimulator::ObjectPathSimulator(const std::string& name, HermiteSpline* targetPath, ThreeDModel* targetObject) :
	BaseSimulator(name),
	splinePath(targetPath),
	m_threeDmodel(targetObject)
{
}	// ObjectPathSimulator

ObjectPathSimulator::~ObjectPathSimulator()
{
}	// ObjectPathSimulator::~ObjectPathSimulator

int ObjectPathSimulator::step(double time)
{
	/* STEP 1: Get the full length of the path*/
	double fullPathLength = splinePath->getFullLength();

	/* STEP 2: Calculate position based on P(u(s(t)))*/
	
	/*STEP 2. a) Calculate distance travelled by object assuming innitial velocity is fixed for now*/

	float distanceTravelled = time * m_speed;
	//if distanceTravelled is greater than or equal to the length of the spine then make it equal to full length
	if (distanceTravelled >= fullPathLength) distanceTravelled = fullPathLength;
	
	//TEST BEFORE MOVING ON
	/*animTcl::OutputMessage("distanceTravelled in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));*/

	/* STEP 2. b) get parameter U based on distance travelled by threeDModel*/
	// make distance travelled a LookUpTableEntry
	LookUpTableEntry tempEntry = LookUpTableEntry();
	tempEntry.arcLength = distanceTravelled;
	double u = splinePath->getU(tempEntry);

	//TEST BEFORE MOVING ON
	/*animTcl::OutputMessage("u in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(u).c_str()));*/

	/* STEP 2. c) get POSITION of m_threeDmodel based on U--> use first and last points on the spline*/
		// Right now I am interpolating between first and last point. But I have to find the position along the spline
	m_threeDmodel->position = splinePath->getPointAtU(u).point;

	/*animTcl::OutputMessage("x position in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(m_threeDmodel->position.x).c_str()));*/

	
	// Once I have position calculate first and second derrivatives in order to solve for u,v, w of the object
	

	return 0;

}	// ObjectPathSimulator::step