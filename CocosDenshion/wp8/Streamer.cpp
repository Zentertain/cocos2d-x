#include "Streamer.h"
#include "OggStreamer.h"
#include "MediaStreamer.h"
#include <iterator>
#include <algorithm>

StreamerFactory& StreamerFactory::getInstance()
{
	static StreamerFactory factory;
	return factory;
}

StreamerFactory::StreamerFactory()
{
	registerDecoder("ogg", ref new OggStreamer());
	registerDecoder("wav", ref new MediaStreamer());
}

void StreamerFactory::registerDecoder(const std::string &format, Streamer^ decoder)
{
	std::string lowerFormat(format);
	std::transform(format.begin(), format.end(), lowerFormat.begin(), ::tolower);
	m_decoderMap[lowerFormat] = decoder;
}

Streamer^ StreamerFactory::getDecoder(const std::string &format)
{
	std::string lowerFormat(format);
	std::transform(format.begin(), format.end(), lowerFormat.begin(), ::tolower);
	auto it = m_decoderMap.find(lowerFormat);
	if (m_decoderMap.end() == it)
	{
		it = m_decoderMap.find("wav");
	}
	return it->second->Clone();
}