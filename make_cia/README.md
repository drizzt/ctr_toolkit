#### CTR_Toolkit - make_cia - Generates CIA files ####
#### Version: 6.4 2013 (C) 3DSGuy ####



### Usage ###

Usage: make_cia <options>
OPTIONS                 Possible Values       Explanation
 -h, --help                                   Print this help.
 -v, --verbose                                Enable verbose output.
 -p, --info                                   Print Info.
 -k, --showkeys                               Show the keys being used.
 -e, --encrypt                                Globally Encrypt CIA Contents
 -o, --out=             File-out              CIA Output
CONTENT OPTIONS
 --contentX=            File-in               Content X path
 --id_X=                Value                 Content X ID
 --index_X=             Value                 Content X Index
 --crypt_X                                    Encrypt Content X
 --optional_X                                 Flag Content X as 'Optional'
 --shared_X                                   Flag Content X as 'Shared'
EXTRA OPTIONS
 -0, --savesize=        Value                 Savedata Size in KB
 -1, --tikID=           Value                 Ticket ID
 -2, --titleID=         Value                 Title ID
 -3, --major=           Value                 TMD Version Major
 -4, --minor=           Value                 TMD Version Minor
 -5, --micro=           Value                 TMD Version Micro
 -6, --tikmajor=        Value                 TIK Version Major
 -7, --tikminor=        Value                 TIK Version Minor
 -8, --tikmicro=        Value                 TIK Version Micro
CRYPTOGRAPHY OPTIONS
 --ckey=                Value                 Common Key
 --ckeyID=              Value                 Common Key ID
 --cxikey=              Value                 CXI Key
 --forcecxikey                                Overide Fixed CXI keyslots with user CXI Key
 --titlekey=            Value                 Title Key
 --rand                                       Use a Random Title Key
 --tmdkey=              File-in               TMD RSA Keyfile
 --tikkey=              File-in               TIK RSA Keyfile
 --certs=               File-in               Certificate Chain File
SPECIAL BUILD OPTIONS
 --srl=                 File-in               Specify a SRL for content0.
 --rom=                 File-in               Convert ROM to CIA.

### Examples ###

make_cia --srl=test.nds -o test.cia
make_cia --rom=test.cci -o test.cia
make_cia --content0=test.cxi -o test.cia
 
NOTE: The nature of this program lets you have a larger "input" into the CIA creation process(in contrast to ctr_makecia32), so a wide variety of titles(and some not yet created at time of writing) can still be packaged with this program. However this also means that incorrect input can lead to invalid CIAs, so be careful.

### Credits ###
A big thanks to neimod, as the API for the polarssl crypto lib is based on his implementation in ctrtool. And special thanks to Jl12 and yellows8.

### Change Log ###

Version 6.4:
* Allowances have been made for ECC signature handling, when it becomes part of polarssl
* Can now be compiled on Mac OS X

Version 6.3:
* Polarssl library updated, and more modules included (SHA1 being a noteworthy inclusion)
* RSA functions have been unified and made simpler, plus more features
* TicketID is now generated in the same way ctr_makecia32 does

Version 6.2:
* Instances of strtol were replaced with strtoul when user could provide acceptable input which strtol cannot convert.
* Code for calculating the Context index in the CIA header has been re-written, it now supports any and all index values a given content may have(0-65535).
* Prevents user from creating CIA files where contents have conflicting index/id values

Version 6.1:
* Updated TMD Struct, and code surrounding it

Version 6.0:
* Removed redundant YAML code
* Meta 'core version' is now retrieved properly
* Useless data in structs have been removed
* Not specifying -o or --output=, makes make_cia generate an output name in the same way as ctr_makecia32.
* Unspecified ContentIDs are now random.
* File handling is done when a function requires it and is closed in the same function. File pointers are no longer globally available via the main context. 
* direct use of free(); has been replaced with _free();, which sets the pointer to NULL after freeing, preventing any errors which might occur from attempting to free an invalid pointer.
* NCSD(ROM) sanity check now present.
* 99% of malloc'd buffers are verfified to prevent accidents
* The '-v' and '--verbose' functionality has changed (old functionality has been moved to '-p' and '--info')
* More General functions moved to utils.c/.h
* Properly Distributed various typedefs into .h files that made sense, instead of shoving them all into ctx.h
* dev_keys.h renamed to ctr_keydata.h
* CIA_CONTEXT, more appropriately renamed to USER_CONTEXT
* AES keys are handled slightly differently:
	> make_cia can now detect when a fixed CXI AES key is used, and which one it is
	> to address this there a three keyslots for cxikey, zerosfixed, systemfixed and secure(user defined as CXIKey '--cxikey=').
	> Fixed keyslots are hardcoded into make_cia at compile time, but can be overidden with by secure key with --forcecxikey.
	

Version 5.1:
* Changed argument strings to prevent make_cia from confusing various commands with other ones
* Small bug fixes

Version 5.0:
* Re-written to remove the need for a configuration file.
* Can be compiled to include keys much like with version 4, but without the mess. make_cia will load keys from dev_keys.h, but will allow the user to include/overwrite any keys at command line.
* 'proper' version generation
* Code should be easier to read
* Overwriting the Cert chain has been simplified to specifying the complete certchain from at command line

Version 4.0:
* Code made "cleaner"
* "NTR" Platform removed. It is not possible to generated 'Valid' CIA files from NTR content.
* Many bugs, were fixed namely
  - Content Settings in config file, could be mistakenly read (fixed)
  - Multiple Content error, preventing successful install for CIAs with multiple contents
* Method order for generating CIA was made more versatile. This however sacrifices the memory efficency of version 3, and may cause low ram computers to freeze with large content.
* Experimental ROM(CCI/CSU) to CIA conversion
  - Maintains NCCH order/index from ROM
  - Content is encrypted
* Integration with CTR_SDK made easier.
  - make_cia can be compiled two ways, depending if "_DEBUG_KEY_BUILD_" is defined or not
  - CTR_SDK users can simply import the CTR_SDK data to dev_keys.h, and uncomment "#define _DEBUG_KEY_BUILD_", this fixes the certchain, commonkey/rsa keys, and the TMD/Ticket "Issuers"
  - Otherwise leaving "#define _DEBUG_KEY_BUILD_" commented, in dev_keys.h, make_cia will function with v3 input, to obatain/generate data.
* "GenerateMeta" option removed.
  - Savedata size, and title version is obtained from a CXI ExHeader(which can be encrypted), in addition the meta data. As a result make_cia, will attempt decryption to obtain prior mention data, but will only notify the user if decryption was not possible.
  - "SaveDataSize" (in KB) can now be manually specified under "BuildSettings"

Version 3.0:
* Initial Public release
* Supports generating valid CIA files
* Supports generating CIA files for CTR 