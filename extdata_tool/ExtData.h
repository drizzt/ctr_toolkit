/**Copyright 2013 3DSGuyThis file is part of extdata_tool.extdata_tool is free software: you can redistribute it and/or modifyit under the terms of the GNU General Public License as published bythe Free Software Foundation, either version 3 of the License, or(at your option) any later version.extdata_tool is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See theGNU General Public License for more details.You should have received a copy of the GNU General Public Licensealong with extdata_tool. If not, see <http://www.gnu.org/licenses/>.**/typedef enum{	DIFF_MAGIC_0 = 0x44494646,	DIFF_MAGIC_1 = 0x300,	DISA_MAGIC = 0x41534944,} DIFF_data;typedef enum{	DIFI_MAGIC_0 = 0x44494649,	DIFI_MAGIC_1 = 0x100,} DIFI_data;typedef enum{	IVFC_MAGIC_0 = 0x49564643,	IVFC_MAGIC_1 = 0x200,} IVFC_data;typedef enum{	DPFS_MAGIC_0 = 0x44504653,	DPFS_MAGIC_1 = 0x100,} DPFS_data;typedef enum{	Primary = 0,	Secondary,} Partition;typedef enum{	NOT_EXTDATA = 10,	DIFI_CORRUPT = 11,	IVFC_CORRUPT = 12,	DPFS_CORRUPT = 13,	UNRECOGNISED_FLAGS = 14,} ExtdataErrors;typedef enum{	level1 = 0,	level2,	level3,	level4,} ivfc_level_index;typedef enum{	table1 = 0,	table2,	tableivfc,} dpfs_index;typedef enum{	RawIVFC = 0,	DataPartition,} ExtdataTypes;typedef struct{	u64 offset;	u64 size;} ExtdataFileSectionData;typedef struct{	u16 Count;	ExtdataFileSectionData *Data;} ExtdataFileSections;typedef struct{	u8 magic_0[4];	u8 magic_1[4];	u8 secondary_partition_offset[8];	u8 primary_partition_offset[8];	u8 partition_table_length[8];	u8 file_base_offset[8];	u8 file_base_size[8];	u8 active_partition[0x4];	u8 active_partition_hash[0x20];	u8 extdata_unique_id[8];	u8 reserved_1[0xA4];} DIFF_STRUCT;typedef struct{	u8 magic_0[4];	u8 magic_1[4];	u8 ivfc_blob_offset[8];	u8 ivfc_blob_size[8];	u8 dpfs_blob_offset[8];	u8 dpfs_blob_size[8];	u8 hash_blob_offset[8];	u8 hash_blob_size[8];	u8 flags[4];	u8 data_partition_offset[8];} DIFI_STRUCT;typedef struct{	u8 relative_offset[8];	u8 size[8];	u8 block_size[8];} IVFC_HASH_LEVEL;typedef struct{	u8 magic_0[4];	u8 magic_1[4];	u8 master_hash_size[8];	IVFC_HASH_LEVEL level[4];	u8 unknown_0[8];} IVFC_STRUCT;typedef struct{	u8 offset[8];	u8 size[8];	u8 block_size[8];} DPFS_TABLE;typedef struct{	u8 magic_0[4];	u8 magic_1[4];	DPFS_TABLE table[3];} DPFS_STRUCT;typedef struct{	DIFI_STRUCT DIFI;	IVFC_STRUCT IVFC;	DPFS_STRUCT DPFS;} DIFI_PARTITION;typedef struct{	u8 TrustChain;	u8 MACValid;	u8 ActivePartitionValid;	u8 IVFC_Level_Validity[4];	//u8 AES_MAC_HASH[0x20];	} ExtdataHashTable;typedef struct{	u8 *extdata;	u64 Size;		u32 ActivePartition;	u64 DIFIPartitions[2];	u64 DIFIPartitionSize;	u64 FileBaseOffset;	u64 FileBaseSize;		u8 IsDATA;	u64 DataOffset;		u64 IVFC_Master_Hash_Blob_Offset;	u64 IVFC_Master_Hash_Blob_Size;		u64 IVFC_Offset;		u64 IVFC_Lvl_Offset[4];	u64 IVFC_Lvl_Size[4];	u64 IVFC_Lvl_BLK_Size[4];		u64 DPFS_Table_Offset[4];	u64 DPFS_Table_Size[4];	u64 DPFS_Table_BLK_Size[4];} ExtdataWorkingCTX;typedef enum{	BUILD_DATA = 1,	BUILD_FS,	BUILD_DB,} ExtDataBuild_Types;typedef struct{	u64 TotalSize;		u64 AbsoluteFileOffset;		///DIFF DATA	u64 FB_OFFSET;	u64 FB_SIZE;	u32 ActiveDIFI;	u64 PARTITION_OFFSET[2];	u64 PARTITION_SIZE;	u8 UniqueExtdataID[8];		///DIFI DATA	u8 ExtdataType;	u64 DATA_OFFSET;		//IVFC	u64 IVFC_OFFSET[4];	u64 IVFC_SIZE[4];	u64 IVFC_BLK_SIZE[4];		// DPFS	u64 TableOffset[3];	u64 TableSize[3];	u64 TableBLKSize[3];		u8 ActiveDIFIHash[0x20];	COMPONENT_STRUCT IVFC_MASTER_HASH;} CreateExtdataCTX;typedef struct{	COMPONENT_STRUCT extdata;		// Allows comparing the unique VSXE Extdata ID	u8 VSXE_Extdata_ID[8];	u8 VSXE_Extdata_ID_Match;		// Force Reading from a specific DIFI partition	u8 OverrideActiveDIFI;	u32 DIFIPartition; // 0 = Primary, 1 = Secondary		u8 Verbose;	u8 TrustChain;	u8 ExtdataType;	ExtdataFileSections Files;} ExtdataContext;int GetExtdataContext(ExtdataContext *ctx);void InitaliseExtdataContext(ExtdataContext *ctx);void FreeExtdataContext(ExtdataContext *ctx);//int UpdateExtdataHashTree(ExtdataContext *ctx);int CreateExtdata(COMPONENT_STRUCT *out, COMPONENT_STRUCT *in, int type, u32 active_difi, u8 unique_extdata_id[8]);