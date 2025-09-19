/* Copyright 2018 Paul Stoffregen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <Arduino.h>
#include "Ethernet.h"
#include "Dns.h"
#include "utility/w5100.h"


int EthernetTCP::connect(IPAddress ip, uint16_t port)
{
	if (_sockindex < MAX_SOCK_NUM) {
        if (Ethernet.socketStatus(_sockindex) != SnSR::CLOSED) {
			Ethernet.socketDisconnect(_sockindex); // TODO: should we call stop()?
		}
		_sockindex = MAX_SOCK_NUM;
	}
#if defined(ESP8266) || defined(ESP32)
	if (ip == IPAddress((uint32_t)0) || ip == IPAddress(0xFFFFFFFFul)) return 0;
    #else
	if (ip == IPAddress((uint32_t)0ul) || ip == IPAddress(0xFFFFFFFFul)) return 0;
#endif
	_sockindex = Ethernet.socketBegin(SnMR::TCP, 0);
	if (_sockindex >= MAX_SOCK_NUM) return 0;
	Ethernet.socketConnect(_sockindex, rawIPAddress(ip), port);

	return 1;
}

int EthernetTCP::connect(const char * host, uint16_t port)
{
    DNSClient dns; // Look up the host first
    IPAddress remote_addr;

    if (_sockindex < MAX_SOCK_NUM) {
        if (Ethernet.socketStatus(_sockindex) != SnSR::CLOSED) {
            Ethernet.socketDisconnect(_sockindex); // TODO: should we call stop()?
        }
        _sockindex = MAX_SOCK_NUM;
    }
    dns.begin(Ethernet.dnsServerIP());
    if (!dns.getHostByName(host, remote_addr, _timeout)) return 0; // TODO: use _timeout
    return connect(remote_addr, port);
}


size_t EthernetTCP::writeWithTimeout(const uint8_t *buf, size_t size, uint16_t timeout)
{
	if (_sockindex >= MAX_SOCK_NUM) return 0;
	if (Ethernet.socketSend(_sockindex, buf, size, timeout)) return size;
	setWriteError();
	return 0;
}

void EthernetTCP::disconnect()
{
	if (_sockindex >= MAX_SOCK_NUM) return;

	// attempt to close the connection gracefully (send a FIN to other side)
	Ethernet.socketDisconnect(_sockindex);
}

void EthernetTCP::close()
{
	if (_sockindex >= MAX_SOCK_NUM) return;
    
    if (Ethernet.socketStatus(_sockindex) == SnSR::CLOSED)
    {
        _sockindex = MAX_SOCK_NUM;
        return; // exit without issuing another close command
    }
    
	// if it isn't closed already, close it forcefully
	Ethernet.socketClose(_sockindex);
	_sockindex = MAX_SOCK_NUM;
}
