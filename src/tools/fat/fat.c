#include <stdio.h>

struct {
    uint8_t BootJumpInstruction[3];
    uint8_t OemIdentifier[8];
bdb_oem							db 'MSWIN4.1'			; 8 bytes
bdb_bytes_per_sector: 			dw 512
bdb_sectors_per_cluster: 		db 1
bdb_reserved_sectors: 			dw 1
bdb_fat_count: 					db 2
bdb_dir_entries_count: 			dw 0E0h
bdb_total_sectors: 				dw 2880					; 2880 * 512 = 1.44 MB
bdb_media_descriptor_type: 		db 0F0h					; F0 = 3.5" floppy disk
bdb_sectors_per_fat: 			dw 9
bdb_sectors_per_track:			dw 18
bdb_heads: 						dw 2
bdb_hidden_sectors: 			dd 0
bdb_large_sector_count:			dd 0

; extended boot record
ebr_drive_number: 				db 0					; 0x00 = floppy, 0x80 = hdd, useless
								db 0					; reserved 
ebr_signature:					db 29h
ebr_volume_id: 					db 12h, 34h, 56h, 78h 	; serial number, value doesn't matter
ebr_volume_label:				db 'GWNX OS    '		; 11 bytes, padded with spaces
ebr_system_id:					db 'FAT 12  '			; 8 bytes
} BootSector;

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Syntax: %s <disk image> <file name>\n", argv[0]);
        return -1;
    }

    FILE* disk = fopen(argv[1], "rb");
}
