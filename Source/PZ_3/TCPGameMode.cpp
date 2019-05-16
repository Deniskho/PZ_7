// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPGameMode.h"
#include "TCPClient.h" 
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"

void ATCPGameMode::BeginPlay() 
{

}

void ATCPGameMode::SavePlayerResult(FString PlayerName, int32 Scores) 
{
	if (!client)
		client = new TCPClient();

	if (client) 
	{
		constexpr int32 SaveRequestID = 1;

		if (!client->IsConnected())
		{
			FIPv4Address Address;
			FIPv4Address::Parse("127.0.0.1", Address);
			client->Connect(Address, 65432);
		}
		if (PlayerName.Len() == 5 && Scores > 0)
		{
			WriteInt(SaveRequestID);
			WriteString(PlayerName);
			WriteInt(Scores);
			client->Write(Buff.GetData(), Buff.Num());
			Buff.Empty();
		}
	}
}

TArray<FUserData> ATCPGameMode::GetUserData()
{
	TArray<FUserData> Data;

	if (!client)
		client = new TCPClient();

	if (client)
	{
		constexpr int32 SaveRequestID = 2;

		if (!client->IsConnected())
		{
			FIPv4Address Address;
			FIPv4Address::Parse("127.0.0.1", Address);
			client->Connect(Address, 65432);
		}

		WriteInt(SaveRequestID);

		client->Write(Buff.GetData(), Buff.Num());
		Buff.Empty();

		auto Result = client->Read(4);
		int32 Entries = ReadInt(Result);
		for (int32 i = 0; i < Entries; i++)
		{
			FUserData UserData;

			auto ScoresEntry = client->Read(4);
			UserData.Scores = ReadInt(ScoresEntry);

			auto NameEntry = client->Read(5);
			UserData.Name = ReadString(NameEntry);

			Data.Add(UserData);
		}
	}
	return Data;
}

int32 ATCPGameMode::ReadInt(TArray<uint8> Data)
{
	int32 result = 0;
	unsigned char * bits = (unsigned char *)Data.GetData();
	/*read little endian*/
	for (int32 n = 3; n >= 0; n--)
	{
		result = (result << 8) + bits[n];
	}
	return result;
}

FString ATCPGameMode::ReadString(TArray<uint8> Data)
{
	Data.Add(0);
	FString Result = FString(UTF8_TO_TCHAR(Data.GetData()));
	return Result;
}

bool ATCPGameMode::WriteInt(int32 Value)
{
	unsigned char * CValue = (unsigned char *)(&Value);
	for (int32 i = 0; i < sizeof(Value); i++)
	{
		Buff.Push(CValue[i]);
	}
	return true;
}

bool ATCPGameMode::WriteBytes(unsigned char * Data, int32 Size)
{
	if (Data == nullptr || Size <= 0) return false;
	for (int32 i = 0; i < Size; i++)
	{
		Buff.Push(Data[i]);
	}
	return true;
}

bool ATCPGameMode::WriteString(FString Value)
{
	FString Test(Value);
	auto UTF8Value = TCHAR_TO_UTF8(*Value);
	return WriteBytes((unsigned char *)UTF8Value, strlen(UTF8Value));
}

ATCPGameMode::~ATCPGameMode()
{
	delete client;
}