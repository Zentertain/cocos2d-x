#include "pch.h"
#include "OggStreamer.h"
#include "Util.h"
#include "DirectXHelper.h"
#include <algorithm>
#include <wchar.h>
#include <string.h>

using namespace Windows::ApplicationModel;

OggStreamer::OggStreamer() : m_offset(0), m_maxStreamLengthInBytes(0), m_data(nullptr)
{
	memset(&m_waveFormat, 0, sizeof(WAVEFORMATEX));

	m_location = Package::Current->InstalledLocation;
	m_locationPath = Platform::String::Concat(m_location->Path, "\\Assets\\Resources\\");
}

OggStreamer::~OggStreamer()
{
	if (nullptr != m_data)
	{
		delete []m_data;
	}
}

void OggStreamer::Initialize(const wchar_t *url) 
{
	WCHAR filePath[MAX_PATH] = {0};
	if ((wcslen(url) > 1 && url[1] == ':'))
	{
		// path start with "x:", is absolute path
		wcscat_s(filePath, url);
	}
	else if (wcslen(url) > 0 && (L'/' == url[0] || L'\\' == url[0]))
	{
		// path start with '/' or '\', is absolute path without driver name
		wcscat_s(filePath, m_locationPath->Data());
		// remove '/' or '\\'
		wcscat_s(filePath, (const WCHAR*)url[1]);
	}
	else
	{
		wcscat_s(filePath, m_locationPath->Data());
		wcscat_s(filePath, url);
	}
	//now, we get the correct file path
	std::string oggFilePath = CocosDenshion::CCUnicodeToUtf8(filePath);
	FILE *oggFile = nullptr;
	fopen_s(&oggFile, oggFilePath.c_str(), "rb");
	if (nullptr == oggFile)
	{
		DX::ThrowIfFailed(-1);
	}
	DX::ThrowIfFailed(ov_open_callbacks(oggFile, &m_oggFile, NULL, 0, OV_CALLBACKS_DEFAULT));
	vorbis_info *vInfo = ov_info(&m_oggFile, -1);

	m_waveFormat.cbSize			 = sizeof(WAVEFORMATEX);
	m_waveFormat.nChannels       = static_cast<int16_t>(vInfo->channels);
	m_waveFormat.wBitsPerSample  = 16;                    //Ogg vorbis is always 16 bit
	m_waveFormat.nSamplesPerSec  = vInfo->rate;
	m_waveFormat.nAvgBytesPerSec = m_waveFormat.nSamplesPerSec * m_waveFormat.nChannels * 2;
	m_waveFormat.nBlockAlign     = 2 * m_waveFormat.nChannels;
	m_waveFormat.wFormatTag      = 1;

	m_maxStreamLengthInBytes = static_cast<uint32_t>(ov_pcm_total(&m_oggFile, -1) * vInfo->channels * sizeof(int16_t));
	m_data = new uint8_t[m_maxStreamLengthInBytes];

	int section = 0;
	uint32_t readSize = 0;
	while (readSize < m_maxStreamLengthInBytes)
	{
		long result = ov_read(&m_oggFile, (char*)m_data + readSize, m_maxStreamLengthInBytes - readSize, 0, 2, 1, &section);
		if (result > 0)
		{
			readSize += result;
		}
		else if (result < 0)
		{
			DX::ThrowIfFailed(result);
		}
		else
		{
			break;
		}
	}
	ov_clear(&m_oggFile);
	fclose(oggFile);
}

uint32_t OggStreamer::GetMaxStreamLengthInBytes()
{
	return m_maxStreamLengthInBytes;
}

WAVEFORMATEX& OggStreamer::GetOutputWaveFormatEx()
{
	return m_waveFormat;
}

#pragma warning(disable:4996)

void OggStreamer::ReadAll(uint8_t* buffer, uint32_t maxBufferSize, uint32_t* bufferLength)
{
	uint32_t toCopy = m_maxStreamLengthInBytes - m_offset;
	if (toCopy > maxBufferSize) 
	{
		toCopy = maxBufferSize;
	}
	std::copy(m_data + m_offset, m_data + m_maxStreamLengthInBytes, buffer);
	*bufferLength = toCopy;

	m_offset += toCopy;
	if (m_offset > m_maxStreamLengthInBytes)
		m_offset = m_maxStreamLengthInBytes;
}

Streamer^ OggStreamer::Clone()
{
	return ref new OggStreamer();
}