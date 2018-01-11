#pragma once

#include "Paths.h"
#include "SharedPointer.h"
#include "LogMacros.h"
#include "LogVerbosity.h"

#include "IDataWriter.h"

#include "DataWriterFactory.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(DataWriterFactory, Log, All)


UENUM(BlueprintType)
enum class EOutputTypeEnum : uint8
{
    OTE_CSV             UMETA(DisplayName="CSV")
};

USTRUCT(BlueprintType)
struct FOutputSettings
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output Settings")
    FString OutputDirectory = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output Settings")
    FString OutputFileName = "output.csv";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output Settings")
    FString CsvDelimiter = "\t";
};


class FDataWriterFactory
{
public:
    static TSharedPtr<IDataWriter> CreateDataWriter(EOutputTypeEnum type, const FOutputSettings& settings);
};
