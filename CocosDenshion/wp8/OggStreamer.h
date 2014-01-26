#pragma once
#include "Streamer.h"
#include "vorbis/codec.h"
#include <vorbis/vorbisfile.h>

ref class OggStreamer : public Streamer
{
internal:
	OggStreamer();
public:
	virtual ~OggStreamer();
internal:
	virtual void Initialize(__in const wchar_t *url) override;
	virtual uint32_t GetMaxStreamLengthInBytes() override;
	virtual WAVEFORMATEX& GetOutputWaveFormatEx() override;
	virtual void ReadAll(uint8_t* buffer, uint32_t maxBufferSize, uint32_t* bufferLength) override;
	virtual Streamer^ Clone() override;
private:
	OggVorbis_File m_oggFile;
	WAVEFORMATEX	m_waveFormat;

	uint32_t		m_offset;
	uint32_t	    m_maxStreamLengthInBytes;
	uint8_t*		m_data;

	Windows::Storage::StorageFolder^ m_location;
	Platform::String^ m_locationPath;				//Resources path of wp8 app
};
