// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	AutomationTestSettings.h: Declares the UAutomationTestSettings class.
=============================================================================*/

#pragma once

#include "AutomationTestSettings.generated.h"


/**
 * Structure for asset opening test
 */
USTRUCT()
struct FOpenTestAsset
{
	GENERATED_USTRUCT_BODY()

	/**
	 * Asset reference
	 */
	UPROPERTY(EditAnywhere, Category=Automation)
	FFilePath	AssetToOpen;

	/** Perform only when attend **/
	UPROPERTY(EditAnywhere, Category=Automation)
	bool		bSkipTestWhenUnAttended;
};

/**
 * Structure for defining an external tool
 */
USTRUCT()
struct FExternalToolDefinition
{
	GENERATED_USTRUCT_BODY()

	/* The name of the tool / test. */
	UPROPERTY(config, EditAnywhere, Category=ExternalTools)
	FString ToolName;

	/* The executable to run. */
	UPROPERTY(config, EditAnywhere, Category=ExternalTools, meta=(FilePathFilter = "*"))
	FFilePath ExecutablePath;

	/* The command line options to pass to the executable. */
	UPROPERTY(config, EditAnywhere, Category=ExternalTools)
	FString CommandLineOptions;

	/* The working directory for the new process. */
	UPROPERTY(config, EditAnywhere, Category=ExternalTools, meta=(RelativePath))
	FDirectoryPath WorkingDirectory;

	/* If set, look for scripts with this extension. */
	UPROPERTY(config, EditAnywhere, Category=ExternalTools)
	FString ScriptExtension;

	/* If the ScriptExtension is set, look here for the script files. */
	UPROPERTY(config, EditAnywhere, Category=ExternalTools, meta=(RelativePath))
	FDirectoryPath ScriptDirectory;
};

/**
 * Holds UProperty names and values to customize factory settings
 */
USTRUCT()
struct FImportFactorySettingValues
{
	GENERATED_USTRUCT_BODY()

	/* The name of the UProperty to change */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (ToolTip = "Name of the property to change.  Nested settings can be modified using \"Outer.Property\""))
	FString SettingName;

	/* The value to apply to the UProperty */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (ToolTip = "Value to import for the specified property."))
	FString Value;
};


/**
 * Holds settings for the asset import / export automation test
 */
USTRUCT()
struct FEditorImportExportTestDefinition
{
	GENERATED_USTRUCT_BODY()

	/* The file to import */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "*"))
	FFilePath ImportFilePath;

	/* The file extension to use when exporting */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (ToolTip = "The file extension to use when exporting this asset.  Used to find a supporting exporter"))
	FString ExportFileExtension;

	/* If true, the export step will be skipped */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	bool bSkipExport;

	/* Settings for the import factory */
	UPROPERTY(config, EditAnywhere, Category=Automation)
	TArray<FImportFactorySettingValues> FactorySettings;
};

/**
* Holds settings for the asset import workflow test
*/
USTRUCT()
struct FEditorImportWorkflowDefinition
{
	GENERATED_USTRUCT_BODY()

	/* The file to import */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "*"))
	FFilePath ImportFilePath;

	/* Settings for the import factory */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	TArray<FImportFactorySettingValues> FactorySettings;
};

/**
* Holds settings for the import workflow stage of the build promotion test
*/
USTRUCT()
struct FBuildPromotionImportWorkflowSettings
{
	GENERATED_USTRUCT_BODY()

	/* Import settings for the Diffuse texture */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition Diffuse;

	/* Import settings for the Normalmap texture */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition Normal;

	/* Import settings for the static mesh */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition StaticMesh;

	/* Import settings for the static mesh to re-import */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition ReimportStaticMesh;

	/* Import settings for the blend shape */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition BlendShapeMesh;

	/* Import settings for the morph mesh */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition MorphMesh;

	/* Import settings for the skeletal mesh */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition SkeletalMesh;

	/* Import settings for the animation asset.  (Will automatically use the skeleton of the skeletal mesh above) */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition Animation;

	/* Import settings for the sound */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition Sound;

	/* Import settings for the surround sound (Select any of the channels.  It will auto import the rest)*/
	UPROPERTY(config, EditAnywhere, Category = Automation)
	FEditorImportWorkflowDefinition SurroundSound;

	/* Import settings for any other assets you may want to import */
	UPROPERTY(config, EditAnywhere, Category = Automation)
	TArray<FEditorImportWorkflowDefinition> OtherAssetsToImport;
};

/**
* Holds settings for the open assets stage of the build promotion test
*/
USTRUCT()
struct FBuildPromotionOpenAssetSettings
{
	GENERATED_USTRUCT_BODY()

	/* The blueprint asset to open */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath BlueprintAsset;

	/* The material asset to open */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath MaterialAsset;
	
	/* The particle system asset to open */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath ParticleSystemAsset;
	
	/* The skeletal mesh asset to open */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath SkeletalMeshAsset;
	
	/* The static mesh asset to open */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath StaticMeshAsset;
	
	/* The texture asset to open */
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath TextureAsset;
};

/**
* Holds settings for the blueprint stage of the build promotion test
*/
USTRUCT()
struct FBuildPromotionBlueprintSettings
{
	GENERATED_USTRUCT_BODY()

	/** The starting mesh for the blueprint **/
	UPROPERTY(EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath FirstMeshPath;

	/** The mesh to set on the blueprint after the delay **/
	UPROPERTY(EditAnywhere, Category = Automation, meta = (FilePathFilter = "uasset"))
	FFilePath SecondMeshPath;
};

/**
* Holds settings for the new project stage of the build promotion test
*/
USTRUCT()
struct FBuildPromotionNewProjectSettings
{
	GENERATED_USTRUCT_BODY()

	/** The path for the new project */
	UPROPERTY(EditAnywhere, Category = Automation)
	FDirectoryPath NewProjectFolderOverride;

	/** The name of the project **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FString NewProjectNameOverride;
};

/**
* Holds settings for the editor build promotion test
*/
USTRUCT()
struct FBuildPromotionTestSettings
{
	GENERATED_USTRUCT_BODY()

	/** Default static mesh asset to apply materials to **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FFilePath DefaultStaticMeshAsset;

	/** Import workflow settings **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FBuildPromotionImportWorkflowSettings	ImportWorkflow;

	/** Open assets settings **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FBuildPromotionOpenAssetSettings	OpenAssets;

	/** Blueprint settings **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FBuildPromotionBlueprintSettings	BlueprintSettings;

	/** New project settings **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FBuildPromotionNewProjectSettings NewProjectSettings;

	/** Material to modify for the content browser step **/
	UPROPERTY(EditAnywhere, Category = Automation)
	FFilePath	SourceControlMaterial;
};

/**
* Holds settings for the asset import / export automation test
*/
USTRUCT()
struct FEditorMapPerformanceTestDefinition
{
	GENERATED_USTRUCT_BODY()
	
	/** Map to be used for the Performance Capture **/
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "umap"))
	FFilePath PerformanceTestmap;

	/** How long is this test expected to run before stopping **/
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (ToolTip = "This is the length of time in seconds that this test will run for before stopping."))
	int32 TestTimer;
};

/**
* Holds settings for the editor Launch On With Map Iterations test.
*/
USTRUCT()
struct FLaunchOnTestSettings
{
	GENERATED_USTRUCT_BODY()

	/** Map to be used for the Launch On test **/
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "umap"))
	FFilePath LaunchOnTestmap;

	/** Device to be used **/
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (ToolTip = "This is the device to be used for launch on. Example: WindowsNoEditor, Android, IOS, Linux"))
	FString DeviceID;
};

/**
 * Implements the Editor's user settings.
 */
UCLASS(config=Engine)
class ENGINE_API UAutomationTestSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	 * The automation test map to be used for several of the automation tests.
	 */
	UPROPERTY(config, EditAnywhere, Category=Automation, meta=(FilePathFilter = "umap"))
	FFilePath AutomationTestmap;

	/**
	* The map to be used for the editor performance capture tool.
	*/
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "umap"))
	TArray<FEditorMapPerformanceTestDefinition> EditorPerformanceTestMaps;

	/**
	* Editor build promotion test settings
	*/
	UPROPERTY(EditAnywhere, config, Category = Automation)
	FBuildPromotionTestSettings BuildPromotionTest;

	/**
	* Modules to load that have engine tests
	*/
	UPROPERTY(EditAnywhere, config, Category = MiscAutomationSetups)
	TArray<FString> EngineTestModules;

	/**
	* Modules to load that have editor tests
	*/
	UPROPERTY(EditAnywhere, config, Category = MiscAutomationSetups)
	TArray<FString> EditorTestModules;

	/**
	* Folders containing levels to exclude from automated tests
	*/
	UPROPERTY(EditAnywhere, config, Category = MiscAutomationSetups)
	TArray<FString> TestLevelFolders;

	/**
	 * Asset to test for open in automation process
	 */
	UPROPERTY(EditAnywhere, config, Category=Automation)
	TArray<FOpenTestAsset> TestAssetsToOpen;
	
	/**
	 * External executables and scripts to run as part of automation.
	 */
	UPROPERTY(EditAnywhere, config, Category=ExternalTools)
	TArray<FExternalToolDefinition> ExternalTools;

	/**
	 * Asset import / Export test settings
	 */
	UPROPERTY(EditAnywhere, config, Category = Automation)
	TArray<FEditorImportExportTestDefinition> ImportExportTestDefinitions;

	/**
	* The map and device type to be used for the editor Launch On With Map Iterations test.
	*/
	UPROPERTY(config, EditAnywhere, Category = Automation, meta = (FilePathFilter = "umap"))
	TArray<FLaunchOnTestSettings> LaunchOnSettings;

};
