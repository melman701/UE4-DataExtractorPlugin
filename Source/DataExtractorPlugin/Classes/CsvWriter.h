#pragma once

#include "GenericPlatformFile.h"
#include "LogMacros.h"
#include "LogVerbosity.h"

#include "IDataWriter.h"


DECLARE_LOG_CATEGORY_EXTERN(CSVWriter, Log, All)


class FCsvWriter : public IDataWriter
{
public:
    FCsvWriter(FString fileDir, FString fileName);
    virtual ~FCsvWriter();
    
    virtual bool WriteData(const TMap<FString, FString>& dataMap);
    
    
private:
    IPlatformFile& m_platformFile;
    IFileHandle* m_fileHandle;
    bool m_bHeaderWritten;
};