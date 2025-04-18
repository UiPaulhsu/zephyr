#ifdef UBNT_SUPPORT_CLASS_ROUTER

/*
int main(int argc, char** argv) {
    u_int32_t ssid= 0;
    for (ssid = 0; ssid < 0x10000; ssid++) 
        if(IS_MEDIATEK_ROUTER_SSID(ssid))
            printf("%08x = MediaTek\n", ssid);
}
*/

__FS_FUNCTION_PREFER_INLINE void _fs_check_router_vpd_sec_vs_fbd(void) {
    if (fs_read_security_data_revision_sec() >= 2 && IS_MEDIATEK_ROUTER_SSID(fs_read_subsystem_id_sec())) {
        __FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t1;
        __FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t2;

        fsv_t1 = (u_int8_t *)fs_zalloc(ROUTER_VPD_SIZE);
        fsv_t2 = (u_int8_t*)fs_zalloc(ROUTER_VPD_SIZE);
        fs_read_router_vpd_sec(fsv_t1,ROUTER_VPD_SIZE);
        fs_read_router_vpd_fbd(fsv_t2,ROUTER_VPD_SIZE);
        if(memcmp(fsv_t1, fsv_t2, ROUTER_VPD_SIZE) != 0) {
            fs_safe_shred_and_free(&fsv_t1, ROUTER_VPD_SIZE);
            fs_safe_shred_and_free(&fsv_t2, ROUTER_VPD_SIZE);
            fs_failure(FS_FAILURE_fs_check_router_vpd_sec_vs_fbd_1);
        }
        fs_safe_shred_and_free(&fsv_t1, ROUTER_VPD_SIZE);
        fs_safe_shred_and_free(&fsv_t2, ROUTER_VPD_SIZE);
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_router_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)         { __fs_check_generic_sec_vs_bi(u_int32_t,router_cpu_rev_id,cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_router_eth0_mac_address_sec_vs_hw(void)                { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_router_eth0_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,router_eth0_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_router(void) {
    if(fs_has_cpu_rev_id_bi()) {
            _fs_check_router_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_router(void) {
    _fs_check_router_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_router(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_router(void) {
    _fs_check_router_eth0_mac_address_sec_vs_fbd();
    // NB: sec has FFFFFFFFFFFF - eth1 is NOT used - _fs_check_router_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
    _fs_check_router_vpd_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_ROUTER

#undef _fs_check_sec_vs_bi__class_router
#undef _fs_check_sec_vs_hw_no_pci__class_router
#undef _fs_check_sec_vs_hw__class_router
#undef _fs_check_sec_vs_fbd__class_router
#undef _fs_check_sec_vs_fbd__class_router_rev2

#define _fs_check_sec_vs_bi__class_router()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_router() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_router()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_router()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)
#define _fs_check_sec_vs_fbd__class_router_rev2()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_ROUTER
