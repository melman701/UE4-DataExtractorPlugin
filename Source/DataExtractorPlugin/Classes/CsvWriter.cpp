#include "CsvWriter.h"
#include "PlatformFilemanager.h"
#include <exception>
#include <stdexcept>


DEFINE_LOG_CATEGORY(CSVWriter)


FCsvWriter::FCsvWriter(FString fileDir, FString fileName)
    : m_platformFile(FPlatformFileManager::Get().GetPlatformFile())
    , m_fileHandle(nullptr)
    , m_bHeaderWritten(false)
{
    UE_LOG(CSVWriter, Log, TEXT("Constructor"));
    
    if (!m_platformFile.DirectoryExists(*fileDir))
    {
        UE_LOG(CSVWriter, Warning, TEXT("Output directory(%s) doesn't exists"), *fileDir);
        if (!m_platformFile.CreateDirectoryTree(*fileDir))
        {
            UE_LOG(CSVWriter, Error, TEXT("Failed to create output directory"));
        }
    }
    
    m_fileHandle = m_platformFile.OpenWrite(*(fileDir + fileName));
    if (!m_fileHandle)
    {
        UE_LOG(CSVWriter, Error, TEXT("Failed to open output file(%s)"), *(fileDir + fileName));
    }
}

FCsvWriter::~FCsvWriter()
{
    UE_LOG(CSVWriter, Log, TEXT("End session"));
    if (m_fileHandle)
    {
        m_fileHandle->Flush();
        delete m_fileHandle;
    }
}

bool FCsvWriter::WriteData(const TMap<FString, FString>& dataMap)
{
    UE_LOG(CSVWriter, Log, TEXT("Write data"));
    
    verify(m_fileHandle != nullptr);
    
    uint8_t b = 0;
    if (!m_bHeaderWritten)
    {
        UE_LOG(CSVWriter, Log, TEXT("Write header"));
        for (auto& row : dataMap)
        {
            UE_LOG(CSVWriter, VeryVerbose, TEXT("%s"), *row.Key);
            uint32 size = row.Key.Len();
            if (b != 0)
                m_fileHandle->Write(&b, 1);
            else
                b = ',';
            m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*row.Key)), size);
        }
        b = '\n';
        m_fileHandle->Write(&b, 1);
        m_bHeaderWritten = true;
        b = 0;
    }
    
    for (auto& row : dataMap)
    {
        UE_LOG(CSVWriter, VeryVerbose, TEXT("%s: %s"), *row.Key, *row.Value);
        if (b != 0)
            m_fileHandle->Write(&b, 1);
        else
            b = ',';
        uint32 size = row.Value.Len();
        m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*row.Value)), size);
    }
    
    b = '\n';
    m_fileHandle->Write(&b, 1);
    
    m_fileHandle->Flush();
    
    return true;
}


