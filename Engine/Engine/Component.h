#pragma once
#include "Observer.h"
#include "document.h"

class GameObject;

class Component : public Observer<Component*>
{
public:
	Component(const std::string& compName);
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Initialize() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
#ifdef _DEBUG
	virtual void RenderGui() {};
#endif // _DEBUG

	virtual void Notify(Component*, Event) override {};

	int GetIdx() const { return m_Idx; };
	std::string GetCompName() const { return m_CompName; };

	void SetGameObj(GameObject* pGameObj) { m_pGameObj = pGameObj; };
	GameObject* GetGameObj() const;
;
	//static function to create comp from json
	template<typename T>
	static Component* CreateCompFromJson(const rapidjson::Value& args)
	{
		return T::CreateComp(args);
	}

protected:
	GameObject* m_pGameObj{ nullptr };

private:
	std::string SimplifyCompTypeName(const std::string& compTypeName);

	static int m_IdxCount;
	int m_Idx{};
	std::string m_CompName{};
	static std::vector<std::string> m_ComponentTypes;
};

