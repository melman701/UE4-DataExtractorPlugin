#include "CsvWriter.h"
#include "PlatformFilemanager.h"
#include <exception>
#include <stdexcept>


DEFINE_LOG_CATEGORY(CSVWriter)


FCsvWriter::FCsvWriter(FString fileDir, FString fileName, FString delimiter)
    : m_platformFile(FPlatformFileManager::Get().GetPlatformFile())
    , m_fileHandle(nullptr)
    , m_bHeaderWritten(false)
    , m_delimiter(delimiter)
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
    
    m_fileHandle = m_platformFile.OpenWrite(*(fileDir + fileName), true);
    if (!m_fileHandle)
    {
        UE_LOG(CSVWriter, Error, TEXT("Failed to open output file(%s)"), *(fileDir + fileName));
    }
    else
    {
        if (m_fileHandle.Size() > 0)
            m_bHeaderWritten = true;
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
    
    FString s = "";
    if (!m_bHeaderWritten)
    {
        UE_LOG(CSVWriter, Log, TEXT("Write header"));
        for (auto& row : dataMap)
        {
            UE_LOG(CSVWriter, VeryVerbose, TEXT("%s"), *row.Key);
            uint32 size = row.Key.Len();
            if (s != "")
                m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*s)), 1);
            else
                s = m_delimiter;
            
            FTCHARToUTF8 EchoStrUtf8(*row.Key);
            size = EchoStrUtf8.Length();
            
            m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*row.Key)), size);
        }
        s = "\n";
        m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*s)), 1);
        m_bHeaderWritten = true;
        s = "";
    }
    
    for (auto& row : dataMap)
    {
        UE_LOG(CSVWriter, VeryVerbose, TEXT("%s: %s"), *row.Key, *row.Value);
        if (s != "")
            m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*s)), 1);
        else
            s = m_delimiter;
        uint32 size = row.Value.Len();
        
        FTCHARToUTF8 EchoStrUtf8(*row.Value);
        size = EchoStrUtf8.Length();
        
        m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*row.Value)), size);
    }
    
    s = "\n";
    m_fileHandle->Write(reinterpret_cast<uint8_t*>(TCHAR_TO_UTF8(*s)), 1);
    
    m_fileHandle->Flush();
    
    return true;
}


