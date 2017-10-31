#include "CsvWriter.h"
#include "PlatformFilemanager.h"
#include <exception>
#include <stdexcept>


DEFINE_LOG_CATEGORY(CSVWriter)


FCsvWriter::FCsvWriter(FString fileDir, FString fileName)
    : m_platformFile(FPlatformFileManager::Get().GetPlatformFile())
    , m_fileHandle(nullptr)
{
    UE_LOG(CSVWriter, Log, TEXT("Constructor"));
    
    if (!m_platformFile.DirectoryExists(*fileDir))
    {
        UE_LOG(CSVWriter, Warning, TEXT("Output directory(%s) doesn't exists"), *fileDir);
        try
        {
            if (!m_platformFile.CreateDirectoryTree(*fileDir))
            {
                UE_LOG(CSVWriter, Error, TEXT("Failed to create output directory"));
                throw std::runtime_error("Failed to create output directory");
            }
        }
        catch (std::exception& e)
        {
            UE_LOG(CSVWriter, Error, TEXT("Output directory creation failed with exception: %s"), e.what());
            throw;
        }
    }
    
    m_fileHandle = m_platformFile.OpenWrite(*fileName);
    if (!m_fileHandle)
    {
        UE_LOG(CSVWriter, Error, TEXT("Failed to open output file(%s)"), *fileName);
        throw std::runtime_error("Failed to open output file");
    }
}

FCsvWriter::~FCsvWriter()
{
    UE_LOG(CSVWriter, Log, TEXT("End session"));
    if (m_fileHandle)
    {
        m_fileHandle->Flush();
    }
}

bool FCsvWriter::WriteData(const TMap<FString, FString>& dataMap)
{
    UE_LOG(CSVWriter, Log, TEXT("Write data"));
    for (auto& row : dataMap)
    {
        UE_LOG(CSVWriter, VeryVerbose, TEXT("%s: %s"), *row.Key, *row.Value);
    }
    
    return true;
}


