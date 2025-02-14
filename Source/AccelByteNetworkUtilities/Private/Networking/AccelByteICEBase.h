﻿// Copyright (c) 2021 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "AccelByteNetworkingStatus.h"
#include "Dom/JsonObject.h"
#include "Models/AccelByteTurnModels.h"

using namespace AccelByte::NetworkUtilities;

class AccelByteSignalingBase;

/**
 * AccelByteICEBase is the base interface for ICE connection
 */

class AccelByteICEBase
{
public:
	/**
	 * @brief Delegate when ICE data channel is connected
	 *
	 * @param The remote peer id that connected
	 * @param P2P connection type (host, srflx, prflx, relay)
	 */
	DECLARE_DELEGATE_TwoParams(OnICEDataChannelConnected, const FString&, const EP2PConnectionType&);

	/**
	* @brief Delegate when ICE data channel has error connection
	*
	* @param Peer id of the target
	* @param Status of the connection
	*/
	DECLARE_DELEGATE_TwoParams(OnICEDataChannelConnectionError, const FString&, const EAccelByteP2PConnectionStatus&);

	/**
	* @brief Delegate when ICE data channel is closed
	*
	* @param The remote peer id that close the connection
	*/
	DECLARE_DELEGATE_OneParam(OnICEDataChannelClosed, const FString&);

	/**
	* @brief Delegate when any ICE data available
	*
	* @param The remote peer id
	* @param Data array
	* @param Length of the data array
	*/
	DECLARE_DELEGATE_ThreeParams(OnICEDataReady, const FString&, const uint8*, int32);

	AccelByteICEBase()
	{
	}

	AccelByteICEBase(const FString &PeerId): PeerId(PeerId)
	{
	}

	virtual ~AccelByteICEBase()
	{
	}

	/**
	* @brief Process signaling message
	*
	* @param Message from signaling service (AccelByte Lobby)
	*/
	virtual void OnSignalingMessage(const FString& Message) = 0;

	/**
	* @brief Request connect to PeerId
	*/
	virtual bool RequestConnect(const FString &ServerUrl, int ServerPort, const FString &Username, const FString &Password) = 0;

	/**
	* @brief Send data to connected peer data channel
	*
	* @param Data to sent
	* @param Count of the data to be sent
	* @param BytesSent notify byte sent.
	*
	* @return true when success
	*/
	virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) = 0;

	/**
	* @brief Disconnect peer connection
	*
	*/
	virtual void ClosePeerConnection() = 0;

	/**
	* @brief Set delegate for ICE Connected
	*
	* @param Delegate
	*/
	void SetOnICEDataChannelConnectedDelegate(OnICEDataChannelConnected Delegate)
	{
		OnICEDataChannelConnectedDelegate = Delegate;
	}

	/**
	* @brief Set delegate for ICE error connection
	*
	* @param Delegate
	*/
	void SetOnICEDataChannelConnectionErrorDelegate(OnICEDataChannelConnectionError Delegate)
	{
		OnICEDataChannelConnectionErrorDelegate = Delegate;
	}

	/**
	* @brief Set delegate for ICE connection Closed
	*
	* @param Delegate
	*/
	void SetOnICEDataChannelClosedDelegate(OnICEDataChannelClosed Delegate)
	{
		OnICEDataChannelClosedDelegate = Delegate;
	}

	/**
	* @brief Set delegate for ICE data ready to read
	*
	* @param Delegate
	*/
	void SetOnICEDataReadyDelegate(OnICEDataReady Delegate)
	{
		OnICEDataReadyDelegate = Delegate;
	}

	/**
	* @brief Set AccelByteSignalingBase instance
	*
	* @param Value
	*/
	void SetSignaling(AccelByteSignalingBase *Value)
	{
		Signaling = Value;
	}

	/**
	 * @brief Check if connected
	 *
	 * @return true if connected
	 */
	bool IsConnected() const
	{
		return bIsConnected;
	}

	/**
	 * @brief Check if peer instance requirement met
	 *
	 * @return true if requirement met
	 */
	virtual bool IsPeerReady() const = 0;

protected:
	/*
	 * Handle all signaling message for exchange information about ICE candidates, ICE description
	 * with other remote peer that want to connect
	 */
	AccelByteSignalingBase *Signaling = nullptr;

	// True if this instance is the initiator of a connection request to the peer
	bool bIsInitiator = false;

	bool bIsConnected = false;

	// AccelByte user ID of the remote peer
	FString PeerId;

	OnICEDataChannelConnected OnICEDataChannelConnectedDelegate;
	OnICEDataChannelConnectionError OnICEDataChannelConnectionErrorDelegate;
	OnICEDataChannelClosed OnICEDataChannelClosedDelegate;
	OnICEDataReady OnICEDataReadyDelegate;

	static void JsonToString(FString& Out, TSharedRef<FJsonObject> JsonObject);
	static TSharedPtr<FJsonObject> StringToJson(const FString& JsonString);
};

/*
 * Dummy just for dummy implementation of AccelByteICEBase, used when platform not supported yet
 */
class AccelByteNullICEConnection : public AccelByteICEBase
{
public:
	AccelByteNullICEConnection()
	{
	}

	AccelByteNullICEConnection(const FString &PeerId)
	{
	}

	virtual ~AccelByteNullICEConnection()
	{
	}

	virtual void OnSignalingMessage(const FString& Message) override
	{
	}

	virtual bool RequestConnect(const FString &ServerUrl, int ServerPort, const FString &Username, const FString &Password) override
	{
		return true;
	}

	virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override
	{
		return true;
	}

	virtual void ClosePeerConnection() override
	{
	}

	virtual bool IsPeerReady() const override
	{
		return true;
	}
};