

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <cstdlib>

typedef uint8_t BYTE;
typedef uint16_t WORD;
//typedef uint32_t DWORD;
typedef uint64_t QWORD;

#define QSV_SIZE_ENCRYPTED 0x400

#define TS_SIZE_PACKET 0xBC
#define FLV_SIZE_HEADER 0x9
#define FLV_SIZE_PREVIOUSTAGSIZE 0x4
#define FLV_UI24(x) (DWORD)(((*(x)) << 16) + ((*(x + 1)) << 8) + (*(x + 2)))

#pragma pack(1)

typedef struct {
	BYTE signature[0xA];
	DWORD version;
	BYTE vid[0x10];
	DWORD _unknown1;
	BYTE _unknown2[0x20];
	DWORD _unknown3;
	DWORD _unknown4;
	QWORD xml_offset;
	DWORD xml_size;
	DWORD nb_indices;
} QsvHeader;

typedef struct {
	BYTE _codetable[0x10];
	QWORD segment_offset;
	DWORD segment_size;
} QsvIndex;

#pragma pack()

// decryption algorithm for some segments in qsv version 0x1
void decrypt_1(BYTE* buffer, DWORD size);

// decryption algorithm for some segments in qsv version 0x2
void decrypt_2(BYTE* buffer, DWORD size);

#pragma pack(1)

typedef struct {
	BYTE tag_type;
	BYTE tag_data_size[3];
	BYTE timestamp[3];
	BYTE timestamp_extended;
	BYTE stream_id[3];
} FlvTagHeader;

#pragma pack()

void write_flv_segment(FILE* fp, BYTE* buffer, DWORD size, DWORD is_first);

void write_ts_segment(FILE* fp, BYTE* buffer, DWORD size, DWORD is_first);

DWORD get_media_type(BYTE* buffer);
void extract_media(const char* input_file, const char* output_file);

void help();

