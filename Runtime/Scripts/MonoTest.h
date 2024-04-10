//#pragma once
//
//#include <string>
//
//#include <mono/jit/jit.h>
//#include <mono/metadata/assembly.h>
//#include <mono/metadata/class.h>
//#include <mono/metadata/debug-helpers.h>
//#include <mono/metadata/mono-config.h>
//
//#include <iostream>
//#include <vector>
//
//typedef unsigned int uint32;
//
//const uint32 c_iInvalidMonoRefID = 0;
//
//class ScriptDetail
//{
//public:
//	ScriptDetail() : m_iMonoRefID(c_iInvalidMonoRefID){ }
//	~ScriptDetail()
//	{
//		if (c_iInvalidMonoRefID != m_iMonoRefID)
//		{
//			m_iMonoRefID = c_iInvalidMonoRefID;
//		}
//	}
//	
//	void SetMonoObject(MonoObject* pObj)
//	{
//		if (NULL != pObj)
//		{
//			if (m_iMonoRefID != c_iInvalidMonoRefID)
//			{
//				mono_gchandle_free(m_iMonoRefID);
//				m_iMonoRefID = c_iInvalidMonoRefID;
//			}
//
//			m_iMonoRefID = mono_gchandle_new_weakref(pObj, 0);
//		}
//		else
//		{
//			std::cout << "ScriptDetail::SetMonoObject, Deadly error! this prarm can't be null!\n" << std::endl;
//		}
//	}
//
//	MonoObject* GetMonoObject(void);
//	bool IsBindMonoObject(void);
//
//private:
//	ScriptDetail(const ScriptDetail&);
//	ScriptDetail& operator=(const ScriptDetail&);
//
//	uint32 m_iMonoRefID;
//};
//
//inline MonoObject* ScriptDetail::GetMonoObject(void)
//{
//	return mono_gchandle_get_target(m_iMonoRefID);
//}
//inline bool ScriptDetail::IsBindMonoObject(void)
//{
//	return (NULL != mono_gchandle_get_target(m_iMonoRefID));
//}
//
//#define __ScriptBind \
//public: \
//	void setMonoObject(MonoObject* pObj) { this->m_ScriptDetail.SetMonoObject(pObj); } \
//	MonoObject* getMonoObject(void) { return this->m_ScriptDetail.GetMonoObject(); } \
//	bool isBindMonoObject(void) { return this->m_ScriptDetail.IsBindMonoObject(); } \
//private: \
//	ScriptDetail m_ScriptDetail;
//
//class ClassB;
//class ClassC;
//class ClassD;
//
//enum Direction
//{
//	right, front, left, back
//};
//
//class ClassA
//{
//	__ScriptBind;
//public:
//	void setInt(int intValue)
//	{
//		this->intValue = intValue;
//	}
//	int getInt()
//	{
//		return intValue;
//	}
//	void setFloat(float floatValue)
//	{
//		this->floatValue = floatValue;
//	}
//	float getFloat()
//	{
//		return floatValue;
//	}
//	void setString(std::string stringValue)
//	{
//		this->stringValue = stringValue;
//	}
//	std::string getString()
//	{
//		return stringValue;
//	}
//	void setDirection(Direction dir)
//	{
//		this->dir = dir;
//	}
//	Direction getDirection()
//	{
//		return dir;
//	}
//	void setData(std::vector<ClassB*> data)
//	{
//		this->data = data;
//	}
//	std::vector<ClassB*> getData()
//	{
//		return data;
//	}
//private:
//	int intValue;
//	float floatValue;
//	std::string stringValue;
//	Direction dir;
//
//	std::vector<ClassB*> data;
//};
//
//class ClassB
//{
//	__ScriptBind;
//public:
//	int setValue(int value)
//	{
//		this->value = value;
//	}
//	int getValue()
//	{
//		return value;
//	}
//private:
//	int value;
//};
//
//class ClassC : public ClassB
//{
//public:
//	void setFloat(float value)
//	{
//		this->Float = value;
//	}
//	float getFloat()
//	{
//		return Float;
//	}
//private:
//	float Float;
//};
//
//class ClassD : public ClassB
//{
//public:
//	void setFF(float ff)
//	{
//		this->ff = ff;
//	}
//	float getFF()
//	{
//		return ff;
//	}
//private:
//	float ff;
//};