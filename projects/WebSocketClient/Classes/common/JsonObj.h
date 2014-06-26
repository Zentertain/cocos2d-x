//
//  JsonObj.h
//  WebSocketClient
//
//  Created by Alanmars on 14-6-25.
//
//

#ifndef __WebSocketClient__JsonObj__
#define __WebSocketClient__JsonObj__

#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include <string>

class JsonStream;

class JsonObj
{
public:
    virtual ~JsonObj() {}
    virtual void encode(JsonStream &stream) const = 0;
    virtual void decode(const JsonStream &stream) = 0;
};

class JsonStream
{
public:
    JsonStream()
    {
        _jsonDoc.SetObject();
    }
    explicit JsonStream(const std::string &jsonStr)
    {
        _jsonDoc.Parse<0>(jsonStr.c_str());
    }
    JsonStream& push(const std::string &key, int8_t val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetInt(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, uint8_t val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetInt(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, int32_t val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetInt(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, uint32_t val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetUint(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, int64_t val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetInt64(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, uint64_t val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetUint64(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, float val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetDouble(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, double val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetDouble(val);
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    JsonStream& push(const std::string &key, const std::string &val)
    {
        rapidjson::Value jsonValue;
        jsonValue.SetString(val.c_str());
        _jsonDoc.AddMember(key.c_str(), jsonValue, _jsonDoc.GetAllocator());
        return *this;
    }
    template <typename T1, typename T2>
    JsonStream& push(const std::string &key, const std::string &val)
    {
        
    }
    std::string toString() const
    {
        rapidjson::StringBuffer strBuff;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strBuff);
        _jsonDoc.Accept(writer);
        return strBuff.GetString();
    }
private:
    rapidjson::Document _jsonDoc;
};

#endif /* defined(__WebSocketClient__JsonObj__) */
