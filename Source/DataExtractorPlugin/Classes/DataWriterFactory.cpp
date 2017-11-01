#include "DataWriterFactory.h"
#include "CsvWriter.h"


DEFINE_LOG_CATEGORY(DataWriterFactory)


TSharedPtr<IDataWriter> FDataWriterFactory::CreateDataWriter(EOutputTypeEnum type, const FOutputSettings& settings)
{
    UE_LOG(DataWriterFactory, Log, TEXT("Create data writer"));
    UE_LOG(DataWriterFactory, Verbose, TEXT("Type: %d"), static_cast<uint8>(type));
    UE_LOG(DataWriterFactory, Verbose, TEXT("SETTINGS"));
    UE_LOG(DataWriterFactory, Verbose, TEXT("OutputDirectory: %s"), *settings.OutputDirectory);
    UE_LOG(DataWriterFactory, Verbose, TEXT("OutputFileName: %s"), *settings.OutputFileName);
    
    TSharedPtr<IDataWriter> sptr;
    
    switch (type)
    {
        case EOutputTypeEnum::OTE_CSV:
            sptr = TSharedPtr<IDataWriter>(new FCsvWriter(settings.OutputDirectory, settings.OutputFileName));
            break;
        default:
            break;
    }
    
    return sptr;
}