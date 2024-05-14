#pragma once

#include <string>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

#include <iostream>
#include <vector>
#include <Types.hpp>

typedef unsigned int uint32;

const uint32 c_iInvalidMonoRefID = 0;

class ScriptDetail
{
public:
    /// constructor
    ScriptDetail()
        : m_iMonoRefID(c_iInvalidMonoRefID)
    {
    }
    ~ScriptDetail()
    {
        if (c_iInvalidMonoRefID != m_iMonoRefID)
        {
            m_iMonoRefID = c_iInvalidMonoRefID;
        }
    }

    void SetMonoObject(MonoObject* pObj)
    {
        if (NULL != pObj)
        {
            if (m_iMonoRefID != c_iInvalidMonoRefID)
            {
                mono_gchandle_free(m_iMonoRefID);
                m_iMonoRefID = c_iInvalidMonoRefID;
            }

            // - the second param should be 0, means this handle will not resurrection when invkoing finalisers.
            m_iMonoRefID = mono_gchandle_new_weakref(pObj, 0);
        }
        else
        {
            // - must be set before
            std::cout << "ScriptDetail::SetMonoObject,Deadly error!this prarm can't be null!\n" << std::endl;
        }
    }
    /// Get m_pScriptObj
    MonoObject* GetMonoObject(void);
    /// to see if this cpp object is binding a mono object
    bool IsBindMonoObject(void);
private:
    // - do not allow copy
    ScriptDetail(const ScriptDetail&);
    ScriptDetail& operator=(const ScriptDetail&);
    // - private data 
    uint32 m_iMonoRefID;
};

// - inline function implement ---
//------------------------------------------------------------------------
inline MonoObject* ScriptDetail::GetMonoObject(void)
{
    return mono_gchandle_get_target(m_iMonoRefID);
}
inline bool ScriptDetail::IsBindMonoObject(void)
{
    return (NULL != mono_gchandle_get_target(m_iMonoRefID));
}

// - bind
#define __ScriptBind \
public:\
    void setMonoObject( MonoObject* pObj )  { this->m_ScriptDetail.SetMonoObject( pObj );  }\
    MonoObject* getMonoObject( void )       { return this->m_ScriptDetail.GetMonoObject(); }\
    bool isBindMonoObject( void )           { return this->m_ScriptDetail.IsBindMonoObject(); }\
private:\
    ScriptDetail m_ScriptDetail;


class ClassB;
class ClassC;
class ClassD;

enum Direction
{
    right, front, left, back
};

using namespace Spore;

class TransformC
{
    __ScriptBind;
public:
    void SetPosition(vec3f pos)
    {
        this->position = pos;
    }
    vec3f GetPosition()
    {
        return this->position;
    }
private:
    vec3f position;
};

class ClassA
{
    __ScriptBind;
public:
    void setInt(int intValue)
    {
        this->intValue = intValue;
    }

    int getInt()
    {
        return intValue;
    }

    void setFloat(float floatValue)
    {
        this->floatValue = floatValue;
    }

    float getFloat()
    {
        return floatValue;
    }

    void setString(std::string stringValue)
    {
        this->stringValue = stringValue;
    }

    std::string getString()
    {
        return stringValue;
    }

    void setDirection(Direction dir)
    {
        this->dir = dir;
    }

    Direction getDirection()
    {
        return dir;
    }

    std::vector<ClassB*> getData()
    {
        return data;
    }

    void setData(std::vector<ClassB*> data)
    {
        this->data = data;
    }
private:
    int intValue;
    float floatValue;
    std::string stringValue;
    Direction dir;

    std::vector<ClassB*> data;
};

class ClassB
{
    __ScriptBind
public:
    int getValue()
    {
        return value;
    }
    void setValue(int value)
    {
        this->value = value;
    }
private:
    int value;
};

class ClassC : public ClassB
{
public:
    float getFloat()
    {
        return Float;
    }

    void setFloat(float value)
    {
        this->Float = value;
    }

private:
    float Float;
};

class ClassD : public ClassB
{
public:
    float getFF()
    {
        return ff;
    }

    void setFF(float ff)
    {
        this->ff = ff;
    }
private:
    float ff;
};
