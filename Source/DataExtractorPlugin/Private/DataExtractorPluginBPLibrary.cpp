// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DataExtractorPluginBPLibrary.h"
#include "DataExtractorPlugin.h"


DEFINE_LOG_CATEGORY(DataExtractorPlugin)


TSharedPtr<IDataWriter> UDataExtractorPluginBPLibrary::m_dwSptr = nullptr;


UDataExtractorPluginBPLibrary::UDataExtractorPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UDataExtractorPluginBPLibrary::StartSession(EOutputTypeEnum type, const FOutputSettings& settings)
{
    UE_LOG(DataExtractorPlugin, Log, TEXT("Start session"));
    m_dwSptr = FDataWriterFactory::CreateDataWriter(type, settings);
}

void UDataExtractorPluginBPLibrary::WriteData(const TMap<FString, FString>& dataMap)
{
    UE_LOG(DataExtractorPlugin, Log, TEXT("Write data"));
    if (m_dwSptr.IsValid())
    {
        if (!m_dwSptr->WriteData(dataMap))
        {
            UE_LOG(DataExtractorPlugin, Error, TEXT("Failed to write data"));
        }
    }
    else
    {
        UE_LOG(DataExtractorPlugin, Error, TEXT("Session not started"));
    }
}

void UDataExtractorPluginBPLibrary::StopSession()
{
    UE_LOG(DataExtractorPlugin, Log, TEXT("Stop session"));
    if (m_dwSptr.IsValid())
        m_dwSptr.Reset();
}

