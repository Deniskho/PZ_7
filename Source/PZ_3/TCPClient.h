// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h" 
#include "SocketSubsystem.h" 
#include "Sockets.h" 
#include "IPv4Address.h"

/**
 * 
 */
class PZ_3_API TCPClient
{
	bool Connected; 
	FSocket * Socket; 
	int32 BytesSent;

public:
	TCPClient();
	~TCPClient();
	bool Connect(FIPv4Address IP, int32 Port, int32 Timeout = 5);
	bool Close();
	int32 Write(unsigned char * Data, int32 Size);
	TArray<unsigned char> Read(int32 Size, int32 Timeout = 5);
	bool IsConnected();

private:
	void RecreateSocket();

};
