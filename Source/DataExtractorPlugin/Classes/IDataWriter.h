#pragma once


class IDataWriter
{
public:
    virtual bool WriteData(const TMap<FString, FString>& dataMap) = 0;
    
    virtual ~IDataWriter() { }
};