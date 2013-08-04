// **********************************************************************
//
// Copyright (c) 2003-2011 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.4.2
//
// <auto-generated>
//
// Generated from file `WorldModel.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef ____WorldModel_h__
#define ____WorldModel_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 304
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 2
#       error Ice patch level mismatch!
#   endif
#endif

namespace RoboCompWorldModel
{

typedef ::std::map< ::std::string, ::std::string> StringDictionary;
void __writeStringDictionary(::IceInternal::BasicStream*, const StringDictionary&);
void __readStringDictionary(::IceInternal::BasicStream*, StringDictionary&);

enum BehaviorResultType
{
    InitialWorld,
    BehaviorBasedModification,
    BehaviorBasedNumericUpdate,
    StatusFailTimeout,
    StatusFailOther,
    StatusActive,
    StatusIdle
};

void __write(::IceInternal::BasicStream*, BehaviorResultType);
void __read(::IceInternal::BasicStream*, BehaviorResultType&);

struct GualzruWorldNode
{
    ::std::string nodeType;
    ::Ice::Int nodeIdentifier;
    ::RoboCompWorldModel::StringDictionary attributes;

    bool operator==(const GualzruWorldNode& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(nodeType != __rhs.nodeType)
        {
            return false;
        }
        if(nodeIdentifier != __rhs.nodeIdentifier)
        {
            return false;
        }
        if(attributes != __rhs.attributes)
        {
            return false;
        }
        return true;
    }

    bool operator<(const GualzruWorldNode& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(nodeType < __rhs.nodeType)
        {
            return true;
        }
        else if(__rhs.nodeType < nodeType)
        {
            return false;
        }
        if(nodeIdentifier < __rhs.nodeIdentifier)
        {
            return true;
        }
        else if(__rhs.nodeIdentifier < nodeIdentifier)
        {
            return false;
        }
        if(attributes < __rhs.attributes)
        {
            return true;
        }
        else if(__rhs.attributes < attributes)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const GualzruWorldNode& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const GualzruWorldNode& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const GualzruWorldNode& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const GualzruWorldNode& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::RoboCompWorldModel::GualzruWorldNode> NodeSequence;
void __writeNodeSequence(::IceInternal::BasicStream*, const ::RoboCompWorldModel::GualzruWorldNode*, const ::RoboCompWorldModel::GualzruWorldNode*);
void __readNodeSequence(::IceInternal::BasicStream*, NodeSequence&);

struct GualzruWorldEdge
{
    ::Ice::Int a;
    ::Ice::Int b;
    ::std::string edgeType;

    bool operator==(const GualzruWorldEdge& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(a != __rhs.a)
        {
            return false;
        }
        if(b != __rhs.b)
        {
            return false;
        }
        if(edgeType != __rhs.edgeType)
        {
            return false;
        }
        return true;
    }

    bool operator<(const GualzruWorldEdge& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(a < __rhs.a)
        {
            return true;
        }
        else if(__rhs.a < a)
        {
            return false;
        }
        if(b < __rhs.b)
        {
            return true;
        }
        else if(__rhs.b < b)
        {
            return false;
        }
        if(edgeType < __rhs.edgeType)
        {
            return true;
        }
        else if(__rhs.edgeType < edgeType)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const GualzruWorldEdge& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const GualzruWorldEdge& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const GualzruWorldEdge& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const GualzruWorldEdge& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::RoboCompWorldModel::GualzruWorldEdge> EdgeSequence;
void __writeEdgeSequence(::IceInternal::BasicStream*, const ::RoboCompWorldModel::GualzruWorldEdge*, const ::RoboCompWorldModel::GualzruWorldEdge*);
void __readEdgeSequence(::IceInternal::BasicStream*, EdgeSequence&);

struct GualzruWorld
{
    ::RoboCompWorldModel::NodeSequence nodes;
    ::RoboCompWorldModel::EdgeSequence edges;

    bool operator==(const GualzruWorld& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(nodes != __rhs.nodes)
        {
            return false;
        }
        if(edges != __rhs.edges)
        {
            return false;
        }
        return true;
    }

    bool operator<(const GualzruWorld& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(nodes < __rhs.nodes)
        {
            return true;
        }
        else if(__rhs.nodes < nodes)
        {
            return false;
        }
        if(edges < __rhs.edges)
        {
            return true;
        }
        else if(__rhs.edges < edges)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const GualzruWorld& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const GualzruWorld& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const GualzruWorld& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const GualzruWorld& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct ModelEvent
{
    ::std::string sender;
    ::RoboCompWorldModel::BehaviorResultType why;
    ::RoboCompWorldModel::GualzruWorld backModel;
    ::RoboCompWorldModel::GualzruWorld newModel;

    bool operator==(const ModelEvent& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(sender != __rhs.sender)
        {
            return false;
        }
        if(why != __rhs.why)
        {
            return false;
        }
        if(backModel != __rhs.backModel)
        {
            return false;
        }
        if(newModel != __rhs.newModel)
        {
            return false;
        }
        return true;
    }

    bool operator<(const ModelEvent& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(sender < __rhs.sender)
        {
            return true;
        }
        else if(__rhs.sender < sender)
        {
            return false;
        }
        if(why < __rhs.why)
        {
            return true;
        }
        else if(__rhs.why < why)
        {
            return false;
        }
        if(backModel < __rhs.backModel)
        {
            return true;
        }
        else if(__rhs.backModel < backModel)
        {
            return false;
        }
        if(newModel < __rhs.newModel)
        {
            return true;
        }
        else if(__rhs.newModel < newModel)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const ModelEvent& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ModelEvent& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ModelEvent& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ModelEvent& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

}

#endif