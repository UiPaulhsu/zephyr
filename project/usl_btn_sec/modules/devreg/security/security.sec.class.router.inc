#ifdef UBNT_SUPPORT_CLASS_ROUTER

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_router_cpu_rev_id_sec(void) {
    return fs_read_config_be32toh(fs_get_config_offset_cpu_rev_id_sec()); 
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_read_router_vpd_sec(uint8_t* dest, size_t dest_len) {
    if(fs_read_security_data_revision_sec() >= 2 && IS_MEDIATEK_ROUTER_SSID(fs_read_subsystem_id_sec())) {
        fs_read_config(dest, dest_len, fs_get_config_offset_vpd_sec(), ROUTER_VPD_SIZE);
        return 1;
    } else {
        memset(dest, 0xff, dest_len);
        return 0;
    }
}

#endif // #ifdef UBNT_SUPPORT_CLASS_ROUTER

