#pragma once

class Resource
{
public:
	Resource(const std::string& name);
	virtual ~Resource() = default;

	std::string GetName() const { return m_Name; };
	void Rename(const std::string& name) { m_Name = name; };
	int GetIdx() const { return m_Idx; };

private:
	std::string m_Name;
	int m_Idx;

	static int m_ResourceCounter;
};

