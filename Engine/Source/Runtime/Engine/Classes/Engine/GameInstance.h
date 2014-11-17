// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

//=============================================================================
// GameInstance: High-level manager object for a instance of the running game.
// Spawned at game creation and not destroyed until game instance is shut down.
// Running as a standalone game, there will be one of these.  Running in PIE
// will generate one of these per PIE instance.
//=============================================================================

#pragma once
#include "GameInstance.generated.h"


// 
// 	EWelcomeScreen, 	//initial screen.  Used for platforms where we may not have a signed in user yet.
// 	EMessageScreen, 	//message screen.  Used to display a message - EG unable to connect to game.
// 	EMainMenu,		//Main frontend state of the game.  No gameplay, just user/session management and UI.	
// 	EPlaying,		//Game should be playable, or loading into a playable state.
// 	EShutdown,		//Game is shutting down.
// 	EUnknown,		//unknown state. mostly for some initializing game-logic objects.

/** Possible state of the current match, where a match is all the gameplay that happens on a single map */
namespace GameInstanceState
{
	extern ENGINE_API const FName Playing;			// We are playing the game
}


UCLASS(config=Game, transient, BlueprintType, Blueprintable)
class ENGINE_API UGameInstance : public UObject, public FExec
{
	GENERATED_UCLASS_BODY()

protected:
	struct FWorldContext* WorldContext;

	// @todo jcf list of logged-in players?

	virtual bool HandleOpenCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld);

	UPROPERTY()
	TArray<ULocalPlayer*> LocalPlayers;		// List of locally participating players in this game instance
public:


	FString PIEMapName;

	// Begin FExec Interface
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) override;
	// End FExec Interface

	// Begin UObject Interface
	virtual class UWorld* GetWorld() const override;
	// End UObject Interface

	/** Gives GameInstance an opportunity to set up what it needs */
	virtual void Init();

#if WITH_EDITOR
	virtual bool InitPIE(bool bAnyBlueprintErrors, int32 PIEInstance);

	bool StartPIEGameInstance(ULocalPlayer* LocalPlayer, bool bInSimulateInEditor, bool bAnyBlueprintErrors, bool bStartInSpectatorMode);
#endif

	class UEngine* GetEngine() const;

	struct FWorldContext* GetWorldContext() const { return WorldContext; };
	class UGameViewportClient* GetGameViewportClient() const;

	/** Starts the GameInstance state machine running */
	virtual void StartGameInstance();

	/** Local player access */

	/**
	 * Debug console command to create a player.
	 * @param ControllerId - The controller ID the player should accept input from.
	 */
	UFUNCTION(exec)
	virtual void			DebugCreatePlayer(int32 ControllerId);

	/**
	 * Debug console command to remove the player with a given controller ID.
	 * @param ControllerId - The controller ID to search for.
	 */
	UFUNCTION(exec)
	virtual void			DebugRemovePlayer(int32 ControllerId);

	virtual ULocalPlayer*	CreateInitialPlayer(FString& OutError);

	/**
	 * Adds a new player.
	 * @param ControllerId - The controller ID the player should accept input from.
	 * @param OutError - If no player is returned, OutError will contain a string describing the reason.
	 * @param SpawnActor - True if an actor should be spawned for the new player.
	 * @return The player which was created.
	 */
	class ULocalPlayer*		CreateLocalPlayer(int32 ControllerId, FString& OutError, bool bSpawnActor);

	/**
	 * Adds a LocalPlayer to the local and global list of Players.
	 *
	 * @param	NewPlayer	the player to add
	 * @param	ControllerId id of the controller associated with the player
	 */
	int32					AddLocalPlayer(ULocalPlayer * NewPlayer, int32 ControllerId);


	/**
	 * Removes a player.
	 * @param Player - The player to remove.
	 * @return whether the player was successfully removed. Removal is not allowed while connected to a server.
	 */
	bool					RemoveLocalPlayer(ULocalPlayer * ExistingPlayer);

	int32					GetNumLocalPlayers() const;
	ULocalPlayer*			GetLocalPlayerByIndex(const int32 Index) const;
	APlayerController*		GetFirstLocalPlayerController() const;
	ULocalPlayer*			FindLocalPlayerFromControllerId(int32 ControllerId) const;
	ULocalPlayer*			FindLocalPlayerFromUniqueNetId(TSharedPtr< FUniqueNetId > UniqueNetId) const;
	ULocalPlayer*			GetFirstGamePlayer() const;

	void					CleanupGameViewport();

	TArray<class ULocalPlayer*>::TConstIterator	GetLocalPlayerIterator();
	const TArray<class ULocalPlayer*> &			GetLocalPlayers();

	static void				AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);
};