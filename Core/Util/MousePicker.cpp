#include "MousePicker.h"

MousePicker::MousePicker(float clickSpeed) :
m_clickSpeed{clickSpeed}
{

}

MousePicker::~MousePicker()
{

}

void MousePicker::getMouseRay(Window* win, glm::mat4 projection, glm::mat4 view)
{
	glm::mat4 inverseProjection = glm::inverse(projection);
	glm::mat4 inverseView = glm::inverse(view);

	double mouseX;
	double mouseY; 
	glfwGetCursorPos(*win->getContext(), &mouseX, &mouseY);

	float x = ((mouseX / win->getWidth()) - 0.5f) * 2.0f;
	float y = -((mouseY / win->getHeight()) - 0.5f) * 2.0f;

	//convert to NDC
	glm::vec4 rayStartNDC{x, y, -1.0f, 1.0f};
	glm::vec4 rayEndNDC{x, y, 0.0f, 1.0f};

	//convert from NDC to eye space
	glm::vec4 rayStartEye = inverseProjection * rayStartNDC;
	rayStartEye /= rayStartEye.w;
	glm::vec4 rayEndEye = inverseProjection * rayEndNDC;
	rayEndEye /= rayEndEye.w;

	//convert from eye space to world space
	glm::vec4 rayStartWorld = inverseView * rayStartEye;
	rayStartWorld /= rayStartWorld.w;
	glm::vec4 rayEndWorld = inverseView * rayEndEye;
	rayEndWorld /= rayEndWorld.w;

	m_rayDir = glm::normalize(glm::vec3{rayEndWorld - rayStartWorld});
	m_rayOrigin = glm::vec3{rayStartWorld};
}

bool MousePicker::rayIntersectCube(glm::mat4 transform, glm::vec3 min, glm::vec3 max)
{
	float tMin = -std::numeric_limits<float>::infinity();
	float tMax = std::numeric_limits<float>::infinity();

	glm::vec3 obb(transform[3].x, transform[3].y, transform[3].z);

	glm::vec3 delta = obb - m_rayOrigin;

	//check intersection with Y and Z axis
	glm::vec3 xAxis{transform[0].x, transform[0].y, transform[0].z};
	if(!perpPlaneIntersect(xAxis, delta, m_rayDir, min, max, tMin, tMax))
	{
		return false;
	}

	//check intersection with X and Z
	glm::vec3 yAxis(transform[1].x, transform[1].y, transform[1].z);
	if(!perpPlaneIntersect(yAxis, delta, m_rayDir, min, max, tMin, tMax))
	{
		return false;
	}

	//check intersection with Y and X
	glm::vec3 zAxis(transform[2].x, transform[2].y, transform[2].z);
	if(!perpPlaneIntersect(zAxis, delta, m_rayDir, min, max, tMin, tMax))
	{
		return false;
	}
	
	return true;
}

bool MousePicker::perpPlaneIntersect(glm::vec3 axis, glm::vec3 delta, glm::vec3 rayDir, glm::vec3 min, glm::vec3 max, float& tMin, float& tMax)
{
	float e = glm::dot(axis, delta);
	float f = glm::dot(rayDir, axis);

	if ( fabs(f) > 0.001f )
	{

		float tNear = (e+min.x)/f;
		float tFar = (e+max.x)/f;

		if (tNear > tFar)
		{
			float temp = tFar;
			tFar = tNear;
			tNear = temp;
		}

		if (tFar < tMax)
		{
			tMax = tFar;
		}

		if (tNear > tMin )
		{
			tMin = tNear;
		}


		if (tMax < tMin )
		{
			return false;
		}

	}else
	{ 
		if(-e+min.x > 0.0f || -e+max.x < 0.0f)
		{
			return false;
		}
	}

	return true;
}

float MousePicker::getClickSpeed()
{
	return m_clickSpeed;
}