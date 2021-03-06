/*
 *  Copyright (c) 2010,
 *  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
 *
 *  This file is part of crtmpserver.
 *  crtmpserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  crtmpserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "protocolfactory.h"
#include "protocols/baseprotocol.h"
#include "localdefines.h"
#include "streamingstatusprotocol.h"
using namespace app_streamingstatus;

ProtocolFactory::ProtocolFactory() {

}

ProtocolFactory::~ProtocolFactory() {
}

vector<uint64_t> ProtocolFactory::HandledProtocols() {
	vector<uint64_t> result;
	ADD_VECTOR_END(result, PT_STREAMING_STATUS_PROTOCOL);
	return result;
}

vector<string> ProtocolFactory::HandledProtocolChains() {
	vector<string> result;
	ADD_VECTOR_END(result, "streamingStatusProtocol");
	return result;
}

vector<uint64_t> ProtocolFactory::ResolveProtocolChain(string name) {
	vector<uint64_t> result;
	ADD_VECTOR_END(result, PT_TCP);
	ADD_VECTOR_END(result, PT_INBOUND_HTTP);
	ADD_VECTOR_END(result, PT_STREAMING_STATUS_PROTOCOL);
	return result;
}

BaseProtocol *ProtocolFactory::SpawnProtocol(uint64_t type, Variant &parameters) {
	BaseProtocol *pResult = NULL;

	switch (type) {
		case PT_STREAMING_STATUS_PROTOCOL:
			pResult = new StreamingStatusProtocol();
			break;
		default:
			FATAL("Spawning protocol %s not yet implemented",
					STR(tagToString(type)));
			break;
	}

	if (pResult != NULL) {
		if (!pResult->Initialize(parameters)) {
			FATAL("Unable to initialize protocol %s",
					STR(tagToString(type)));
			delete pResult;
			pResult = NULL;
		}
	}

	return pResult;
}

