#pragma once

#include <xaudio2.h>
#include <stdint.h>
#include <map>
#include <string>

ref class Streamer abstract
{
internal:
	Streamer() {};
public:	
	virtual ~Streamer() {};
internal:
	virtual void Initialize(_In_ const wchar_t *filePath) = 0;
	virtual uint32_t GetMaxStreamLengthInBytes() = 0;
	virtual WAVEFORMATEX& GetOutputWaveFormatEx() = 0;
	virtual void ReadAll(uint8_t* buffer, uint32_t maxBufferSize, uint32_t* bufferLength) = 0;
	virtual Streamer^ Clone() = 0;
};

class StreamerFactory
{
public:
	static StreamerFactory& getInstance();
	~StreamerFactory() {}
	void registerDecoder(const std::string &format, Streamer^ decoder);
	Streamer^ getDecoder(const std::string &format);
private:
	StreamerFactory();
private:
	std::map<std::string, Streamer^> m_decoderMap;
};
