#include "OpenALDecoder.h"
#include <sys/mman.h>
#include <sys/stat.h>

#include <vorbis/vorbisfile.h>


namespace CocosDenshion {

static int checkALError(const char *funcName)
{
    int err = alGetError();

    if (err != AL_NO_ERROR)
    {
        switch (err)
        {
            case AL_INVALID_NAME:
                fprintf(stderr, "AL_INVALID_NAME in %s\n", funcName);
                break;

            case AL_INVALID_ENUM:
                fprintf(stderr, "AL_INVALID_ENUM in %s\n", funcName);
                break;

            case AL_INVALID_VALUE:
                fprintf(stderr, "AL_INVALID_VALUE in %s\n", funcName);
                break;

            case AL_INVALID_OPERATION:
                fprintf(stderr, "AL_INVALID_OPERATION in %s\n", funcName);
                break;

            case AL_OUT_OF_MEMORY:
                fprintf(stderr, "AL_OUT_OF_MEMORY in %s\n", funcName);
                break;
        }
    }

    return err;
}

class DataRaii
{
public:
    char *data;
    size_t size;

    DataRaii() : data(0), size(0) {}
    ~DataRaii() { delete [] data; }
};

class VorbisDecoder : public OpenALDecoder
{
    class OggRaii
    {
    public:
        OggVorbis_File file;

        ~OggRaii() { ov_clear(&file); }
    };

public:
    bool decode(OpenALFile &file, ALuint &result)
    {
        OggRaii ogg;
        int status = ov_test(file.file, &ogg.file, 0, 0);
        if (status != 0) {
            ov_clear(&ogg.file);
            return false;
        }
        status = ov_test_open(&ogg.file);
        if (status != 0) {
            fprintf(stderr, "Could not open OGG file '%s'\n", file.debugName.c_str());
            return false;
        }
        // As vorbis documentation says, we should not fclose() file
        // after successful opening by vorbis functions.
        file.file = NULL;
        vorbis_info *info = ov_info(&ogg.file, -1);
        ALenum  format = (info->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        DataRaii pcm;
        pcm.size = ov_pcm_total(&ogg.file, -1) * info->channels * 2;
        pcm.data = new char[pcm.size];

        size_t size = 0;
        int section = 0;
        while (size < pcm.size) {
            status = ov_read(&ogg.file, pcm.data + size, pcm.size - size, 0, 2, 1, &section);
            if (status > 0) {
                size += status;
            } else if (status < 0) {
                fprintf(stderr, "OGG file decoding stopped, file '%s'\n", file.debugName.c_str());
                return false;
            } else {
                break;
            }
        }
        if (size == 0) {
            fprintf(stderr, "Unable to read OGG data from '%s'\n", file.debugName.c_str());
			return false;
        }
        return initALBuffer(result, format, pcm.data, pcm.size, info->rate);
    }

    bool acceptsFormat(Format format) const
    {
        return Vorbis == format;
    }
};

std::vector<OpenALDecoder *> OpenALDecoder::_decoders;

void OpenALDecoder::installDecoders()
{
    addDecoder(new VorbisDecoder());
}

void OpenALDecoder::addDecoder(OpenALDecoder *decoder)
{
    if (decoder)
        _decoders.push_back(decoder);
}

bool OpenALDecoder::initALBuffer(ALuint &result, ALenum format,
                                 const ALvoid *data, ALsizei size, ALsizei freq)
{
    // Load audio data into a buffer.
    alGenBuffers(1, &result);

    if (checkALError("initALBuffer:alGenBuffers") != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate OpenAL buffer\n");
        return false;
    }

    alBufferData(result, format, data, size, freq);
    checkALError("initALBuffer:alBufferData");
    return true;
}

const std::vector<OpenALDecoder *> &OpenALDecoder::getDecoders()
{
    return _decoders;
}

void OpenALFile::clear()
{
    if (mappedFile) {
        ::munmap(mappedFile, fileSize);
        mappedFile = 0;
        fileSize = 0;
    }
    if (file) {
        fclose(file);
        file = 0;
    }
}

bool OpenALFile::mapToMemory()
{
    if (!file)
        return false;
    if (mappedFile != NULL)
        return true;

    const int fd = fileno(file);
    struct stat fileStats;
    if (0 != fstat(fd, &fileStats))
        return false;
    fileSize = fileStats.st_size;
    mappedFile = ::mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mappedFile != MAP_FAILED)
        return true;
    mappedFile = NULL;
    return false;
}

} // namespace CocosDenshion
