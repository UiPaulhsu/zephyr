#if SECURITY_IS_TARGET_BUILD

__FS_FUNCTION_PREFER_INLINE void      fs_read_eth0_mac_address_fbd(u_int8_t* dest, size_t dest_len)               { fs_read_config(dest, dest_len, 0x00, MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_eth1_mac_address_fbd(u_int8_t* dest, size_t dest_len)               { memset(dest, 0xff, dest_len); if(fs_get_config_size() == BLOCK_64K) { fs_read_config(dest, dest_len, 0x06, MAC_ADDRESS_SIZE); }}
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_subsystem_id_fbd(void)                                              { return fs_read_config_be16toh(0x0c); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_subvendor_id_fbd(void)                                              { return fs_read_config_be16toh(0x0e); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_subsystem_id_fbd(void)                                               { return fs_read_subsystem_id_fbd() != 0xFFFF && fs_read_subsystem_id_fbd() != 0x0000; }
__FS_FUNCTION_PREFER_INLINE int       fs_has_subvendor_id_fbd(void)                                               { return fs_read_subvendor_id_fbd() != 0xFFFF && fs_read_subvendor_id_fbd() != 0x0000; }

// NB: WARNING: This function will only return a value if the current security data format has a value for this field.  
//     This is our indicator of whether or not to expect flash board data to be populated with PCBA field, and keeps us
//     from trying to use garbage in comparisons.
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_pcba_fbd(void) {
    if(fs_get_config_offset_pcba_sec()) {
        return fs_read_config_be32toh(FLASH_BOARD_DATA_OFFSET_PCBA); 
    }
    return 0xFFFFFFFF;
}

#include "security.fbd.class.airfiber.inc"
#include "security.fbd.class.bcmwifi.inc"
#include "security.fbd.class.camera.inc"
#include "security.fbd.class.camera2.inc"
#include "security.fbd.class.nvr.inc"
#include "security.fbd.class.qcaswitch.inc"
#include "security.fbd.class.router.inc"
#include "security.fbd.class.solargateway.inc"
#include "security.fbd.class.switch.inc"
#include "security.fbd.class.basic.inc"
#include "security.fbd.class.basic4k.inc"
#include "security.fbd.class.univox.inc"
#include "security.fbd.class.wifi.inc"
#include "security.fbd.class.bcmswitch.inc"
#include "security.fbd.class.cloudkey.inc"
#include "security.fbd.class.inverter.inc"

#endif // #if SECURITY_IS_TARGET_BUILD
