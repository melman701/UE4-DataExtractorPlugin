// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DataExtractorPluginBPLibrary.h"
#include "DataExtractorPlugin.h"


DEFINE_LOG_CATEGORY(DataExtractorPlugin)



UDataExtractorPluginBPLibrary::UDataExtractorPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UDataExtractorPluginBPLibrary::StartSession(EOutputTypeEnum type, const FOutputSettings& settings)
{
    UE_LOG(DataExtractorPlugin, Log, TEXT("Start session"));
//    m_dwSptr = FDataWriterFactory::CreateDataWriter(type, settings);
}

void UDataExtractorPluginBPLibrary::StopSession()
{
    UE_LOG(DataExtractorPlugin, Log, TEXT("Stop session"));
    m_dwSptr.Reset();
}
