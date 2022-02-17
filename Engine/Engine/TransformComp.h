#pragma once
#include "Component.h"
#include "glm\detail\type_vec3.hpp"

class TransformComp : public Component
{
public:
	TransformComp() :Component{} {};
	~TransformComp() = default;
	TransformComp(const TransformComp& other) = delete;
	TransformComp(TransformComp&& other) = delete;
	TransformComp& operator=(const TransformComp& other) = delete;
	TransformComp& operator=(TransformComp&& other) = delete;

	glm::vec3 GetPos() const;
	void SetPos(const glm::vec3& pos) { m_Position = pos; };
	glm::vec3 GetScale() const;
	void SetScale(const glm::vec3& scale) { m_Scale = scale; };
	glm::vec3 GetRotation() const;
	void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; };

private:
	glm::vec3 m_Position{ 0,0,0 };
	glm::vec3 m_Scale{ 1,1,1 };
	glm::vec3 m_Rotation{ 0,0,0 };	//in radiants

};

