#pragma once
#ifndef _NET_INCLUDED_
#define _NET_INCLUDED_

#include <UdpSocket.hpp>
#include <TcpClient.hpp>

using cat_network::TcpClient;

int FindServer(TcpClient* client, Address* serverAddress);

#endif
