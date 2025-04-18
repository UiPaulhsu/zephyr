/*
NB: The tool used to create encrypted strings here is bdtest. 
It can be built from AirOS 11n source tree, packages-other/ubntbox/src/board.  Make bdtest. 
Then bdtest -c 'text' (it's symmetrical) 
*/

__FS_LOCAL_STATIC_OPTION const char fsv_u1[] = "\x81\x93\xe0\xc4"; \

#define FS_DESCRAMBLER(__functionname, __constant) \
	const char* __functionname(void) { \
		static char fsv_t3[] = __constant; \
		static int fsv_t4 = 0; \
		if(!fsv_t4) { \
			__FS_LOCAL_STATIC_OPTION size_t i; \
			for (i = 0; i < sizeof(fsv_t3); ++i) { \
				if (fsv_t3[i] == 0x00) \
					break; \
				fsv_t3[i] ^= fsv_u1[ i % 4 ]; \
			} \
			fsv_t4 = 1; \
		} \
		return fsv_t3; \
	} \
    static inline size_t __functionname ## _size(void) { return sizeof(__constant); } \
    /* Subtact 2 from size.  One is for string literal's automatic NULL and one is for encode having generated an extra escaped NULL character in the output (which we really don't need unless encoded string is inline with something else) */ \
    static inline size_t __functionname ## _len(void)  { return sizeof(__constant) - 2; } 
    

#if SECURITY_ENABLE_FILE_IO_SUPPORT
// "board.cpu_rev_id"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__board_cpu_rev_id, "\xe3\xfc\x81\xb6\xe5\xbd\x83\xb4\xf4\xe1\x85\xb2\xe8\xe0\x89\xab\xef\x00")
// "board.sysid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__board_sysid, "\xe3\xfc\x81\xb6\xe5\xbd\x93\xbd\xf2\xfa\x84\x00")
// "board.hwaddr"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__board_hwaddr, "\xe3\xfc\x81\xb6\xe5\xbd\x88\xb3\xe0\xf7\x84\xb6\x00")
// "board.vendid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__board_vendid, "\xe3\xfc\x81\xb6\xe5\xbd\x96\xa1\xef\xf7\x89\xa0\x00")
// "eth.0.mac_address"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__eth0_mac_address, "\xe4\xe7\x88\xea\xb1\xbd\x8d\xa5\xe2\xcc\x81\xa0\xe5\xe1\x85\xb7\xf2\x00")
// "eth.1.mac_address"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__eth1_mac_address, "\xe4\xe7\x88\xea\xb0\xbd\x8d\xa5\xe2\xcc\x81\xa0\xe5\xe1\x85\xb7\xf2\x00")

#if defined(UBNT_SUPPORT_CLASS_WIFI) || defined(UBNT_SUPPORT_CLASS_BCMWIFI)
// "radio.1.mac_address"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio1_mac_address, "\xf3\xf2\x84\xad\xee\xbd\xd1\xea\xec\xf2\x83\x9b\xe0\xf7\x84\xb6\xe4\xe0\x93\x00")
// "radio.2.mac_address"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio2_mac_address, "\xf3\xf2\x84\xad\xee\xbd\xd2\xea\xec\xf2\x83\x9b\xe0\xf7\x84\xb6\xe4\xe0\x93\x00")
// "radio.1.id"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_1_id, "\xf3\xf2\x84\xad\xee\xbd\xd1\xea\xe8\xf7\x00")
// "radio.2.id"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_2_id, "\xf3\xf2\x84\xad\xee\xbd\xd2\xea\xe8\xf7\x00")
// "radio.1.deviceid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_1_deviceid, "\xf3\xf2\x84\xad\xee\xbd\xd1\xea\xe5\xf6\x96\xad\xe2\xf6\x89\xa0\x00")
// "radio.2.deviceid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_2_deviceid, "\xf3\xf2\x84\xad\xee\xbd\xd2\xea\xe5\xf6\x96\xad\xe2\xf6\x89\xa0\x00")
// "radio.1.vendorid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_1_vendorid, "\xf3\xf2\x84\xad\xee\xbd\xd1\xea\xf7\xf6\x8e\xa0\xee\xe1\x89\xa0\x00")
// "radio.2.vendorid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_2_vendorid, "\xf3\xf2\x84\xad\xee\xbd\xd2\xea\xf7\xf6\x8e\xa0\xee\xe1\x89\xa0\x00")
// "radio.1.subsystemid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_1_subsystemid, "\xf3\xf2\x84\xad\xee\xbd\xd1\xea\xf2\xe6\x82\xb7\xf8\xe0\x94\xa1\xec\xfa\x84\x00")
// "radio.2.subsystemid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_2_subsystemid, "\xf3\xf2\x84\xad\xee\xbd\xd2\xea\xf2\xe6\x82\xb7\xf8\xe0\x94\xa1\xec\xfa\x84\x00")
// "radio.1.subvendorid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_1_subvendorid, "\xf3\xf2\x84\xad\xee\xbd\xd1\xea\xf2\xe6\x82\xb2\xe4\xfd\x84\xab\xf3\xfa\x84\x00")
// "radio.2.subvendorid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_key__wifi_radio_2_subvendorid, "\xf3\xf2\x84\xad\xee\xbd\xd2\xea\xf2\xe6\x82\xb2\xe4\xfd\x84\xab\xf3\xfa\x84\x00")
#endif // #if defined(UBNT_SUPPORT_CLASS_WIFI) || defined(UBNT_SUPPORT_CLASS_BCMWIFI)

// "/dev/mem"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_dev_mem,"\xae\xf7\x85\xb2\xae\xfe\x85\xa9\x00")

#ifdef UBNT_ARM_AM3xxx
	// "/dev/block/mtdblock"
	__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_dev_mtdblock, "\xae\xf7\x85\xb2\xae\xf1\x8c\xab\xe2\xf8\xcf\xa9\xf5\xf7\x82\xa8\xee\xf0\x8b\x00")
#elif defined(UBNT_ARM_BCM111xx)
	// "/dev/block/mmcblk0p"
	__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_dev_mtdblock, "\xae\xf7\x85\xb2\xae\xf1\x8c\xab\xe2\xf8\xcf\xa9\xec\xf0\x82\xa8\xea\xa3\x90\x00")
#elif defined(UBNT_ARM_MT8117)
	// "/dev/block/mmcblk0p"
	__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_dev_mtdblock, "\xae\xf7\x85\xb2\xae\xf1\x8c\xab\xe2\xf8\xcf\xa9\xec\xf0\x82\xa8\xea\xa3\x90\x00")
#else // #ifdef UBNT_ARM_AM3xxx
	// "/dev/mtdblock"
	__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_dev_mtdblock, "\xae\xf7\x85\xb2\xae\xfe\x94\xa0\xe3\xff\x8f\xa7\xea\x00")
#endif // #ifdef UBNT_ARM_AM3xxx
// "/proc/mtd"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_proc_mtd, "\xae\xe3\x92\xab\xe2\xbc\x8d\xb0\xe5\x00")
// "\"eeprom\""
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_eeprom_quoted, "\xa3\xf6\x85\xb4\xf3\xfc\x8d\xe6\x00");
// "mtd"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_mtd, "\xec\xe7\x84\x00")
// "/proc/bus/pci/devices"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_proc_bus_pci_devices, "\xae\xe3\x92\xab\xe2\xbc\x82\xb1\xf2\xbc\x90\xa7\xe8\xbc\x84\xa1\xf7\xfa\x83\xa1\xf2\x00");
#endif // #if SECURITY_ENABLE_FILE_IO_SUPPORT

#if SECURITY_ENABLE_MAC_ADDRESS_SUPPORT
#if defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x)
// "dtl0"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_eth0, "\xe5\xe7\x8c\xf4\x00");
#else // #if defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x)
// "eth0"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_eth0, "\xe4\xe7\x88\xf4\x00");
#endif // #if defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x)
#ifdef UBNT_ARM_AM18xx
// "air0"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_eth1, "\xe0\xfa\x92\xf4\x00");
#else
// "eth1"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_eth1, "\xe4\xe7\x88\xf5\x00");
#endif // #ifdef UBNT_ARM_AM18xx
#define fs_get_ifname_air0 fs_get_ifname_eth1
// "eth2"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_eth2, "\xe4\xe7\x88\xf6\x00");

#ifdef UBNT_SUPPORT_CLASS_WIFI
// "wifi0"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_wifi0, "\xf6\xfa\x86\xad\xb1\x00");
// "wifi1"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ifname_wifi1, "\xf6\xfa\x86\xad\xb0\x00");
#endif // #ifdef UBNT_SUPPORT_CLASS_WIFI
#endif // #if SECURITY_ENABLE_MAC_ADDRESS_SUPPORT

#if SECURITY_ENABLE_FILE_IO_SUPPORT

// "/tmp/tmp.YfvXa7Q2QO"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_tmp_tag, "\xae\xe7\x8d\xb4\xae\xe7\x8d\xb4\xaf\xca\x86\xb2\xd9\xf2\xd7\x95\xb3\xc2\xaf\x00");
// "/etc/passwd" - prevent login.
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_etc_passwd, "\xae\xf6\x94\xa7\xae\xe3\x81\xb7\xf2\xe4\x84\x00");
// "/var/etc/dropbear/authorized_keys"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_db_ssh_authorized_keys, "\xae\xe5\x81\xb6\xae\xf6\x94\xa7\xae\xf7\x92\xab\xf1\xf1\x85\xa5\xf3\xbc\x81\xb1\xf5\xfb\x8f\xb6\xe8\xe9\x85\xa0\xde\xf8\x85\xbd\xf2\x00");
// "/var/etc/persistent/mcuser/.ssh/authorized_keys"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_mcuser_ssh_authorized_keys,  "\xae\xe5\x81\xb6\xae\xf6\x94\xa7\xae\xe3\x85\xb6\xf2\xfa\x93\xb0\xe4\xfd\x94\xeb\xec\xf0\x95\xb7\xe4\xe1\xcf\xea\xf2\xe0\x88\xeb\xe0\xe6\x94\xac\xee\xe1\x89\xbe\xe4\xf7\xbf\xaf\xe4\xea\x93\x00");
// "/var/etc/persistent/.ssh/authorized_keys"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_ssh_authorized_keys, "\xae\xe5\x81\xb6\xae\xf6\x94\xa7\xae\xe3\x85\xb6\xf2\xfa\x93\xb0\xe4\xfd\x94\xeb\xaf\xe0\x93\xac\xae\xf2\x95\xb0\xe9\xfc\x92\xad\xfb\xf6\x84\x9b\xea\xf6\x99\xb7\x00");
// "/etc/version" - add an astersick
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_etc_version, "\xae\xf6\x94\xa7\xae\xe5\x85\xb6\xf2\xfa\x8f\xaa\x00");
// "[Error-A12]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_counterfeit_label, "\xda\xd6\x92\xb6\xee\xe1\xcd\x85\xb0\xa1\xbd\x00");
// "/etc/Error-A12"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_counterfeit_tag1, "\xae\xf6\x94\xa7\xae\xd6\x92\xb6\xee\xe1\xcd\x85\xb0\xa1\x00");
// "/etc/persistent/Error-A12"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_counterfeit_tag2,  "\xae\xf6\x94\xa7\xae\xe3\x85\xb6\xf2\xfa\x93\xb0\xe4\xfd\x94\xeb\xc4\xe1\x92\xab\xf3\xbe\xa1\xf5\xb3\x00");
// "/proc/sys/kernel/hostname"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_proc_sys_kernel_hostname, "\xae\xe3\x92\xab\xe2\xbc\x93\xbd\xf2\xbc\x8b\xa1\xf3\xfd\x85\xa8\xae\xfb\x8f\xb7\xf5\xfd\x81\xa9\xe4\x00");
// "/proc/sys/kernel/domainname"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_proc_sys_kernel_domainname, "\xae\xe3\x92\xab\xe2\xbc\x93\xbd\xf2\xbc\x8b\xa1\xf3\xfd\x85\xa8\xae\xf7\x8f\xa9\xe0\xfa\x8e\xaa\xe0\xfe\x85\x00");
// "Error-A12"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_counterfeit, "\xc4\xe1\x92\xab\xf3\xbe\xa1\xf5\xb3\x00");
// "/proc/sys/kernel/printk_ratelimit"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_proc_sys_kernel_printk_ratelimit, "\xae\xe3\x92\xab\xe2\xbc\x93\xbd\xf2\xbc\x8b\xa1\xf3\xfd\x85\xa8\xae\xe3\x92\xad\xef\xe7\x8b\x9b\xf3\xf2\x94\xa1\xed\xfa\x8d\xad\xf5\x00");
// "/proc/sys/net/ipv4/conf/all/forwarding"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_proc_sys_net_ipv4_conf_all_forwarding,"\xae\xe3\x92\xab\xe2\xbc\x93\xbd\xf2\xbc\x8e\xa1\xf5\xbc\x89\xb4\xf7\xa7\xcf\xa7\xee\xfd\x86\xeb\xe0\xff\x8c\xeb\xe7\xfc\x92\xb3\xe0\xe1\x84\xad\xef\xf4\x00");
// "/proc/sys/net/ipv4/ip_forward"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_proc_sys_net_ipv4_ip_forward,"\xae\xe3\x92\xab\xe2\xbc\x93\xbd\xf2\xbc\x8e\xa1\xf5\xbc\x89\xb4\xf7\xa7\xcf\xad\xf1\xcc\x86\xab\xf3\xe4\x81\xb6\xe5\x00");
// "/sys/devices/system/cpu/cpu0/cpuid"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_sys_devices_system_cpu_cpu0_cpuid,"\xae\xe0\x99\xb7\xae\xf7\x85\xb2\xe8\xf0\x85\xb7\xae\xe0\x99\xb7\xf5\xf6\x8d\xeb\xe2\xe3\x95\xeb\xe2\xe3\x95\xf4\xae\xf0\x90\xb1\xe8\xf7\x00");
#endif // #if SECURITY_ENABLE_FILE_IO_SUPPORT

#ifdef UBNT_SUPPORT_CLASS_WIFI
// "[Unrecognized]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_unknown, "\xda\xc6\x8e\xb6\xe4\xf0\x8f\xa3\xef\xfa\x9a\xa1\xe5\xce\x00")
// "[AR7240 (Hydra)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_hydra, "\xda\xd2\xb2\xf3\xb3\xa7\xd0\xe4\xa9\xdb\x99\xa0\xf3\xf2\xc9\x99\x00")
// "[AR7241 (Old Viran)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_virian_old, "\xda\xd2\xb2\xf3\xb3\xa7\xd1\xe4\xa9\xdc\x8c\xa0\xa1\xc5\x89\xb6\xe0\xfd\xc9\x99\x00")
// "[AR7242 (Viran)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_virian, "\xda\xd2\xb2\xf3\xb3\xa7\xd2\xe4\xa9\xc5\x89\xb6\xe0\xfd\xc9\x99\x00")
// "[AR933x (Hornet)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_hornet, "\xda\xd2\xb2\xfd\xb2\xa0\x98\xe4\xa9\xdb\x8f\xb6\xef\xf6\x94\xed\xdc\x00")
// "[AR934x (Wasp)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_wasp, "\xda\xd2\xb2\xfd\xb2\xa7\x98\xe4\xa9\xc4\x81\xb7\xf1\xba\xbd\x00")
// "[QCA955x (Scorpion)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_scorpion, "\xda\xc2\xa3\x85\xb8\xa6\xd5\xbc\xa1\xbb\xb3\xa7\xee\xe1\x90\xad\xee\xfd\xc9\x99\x00")
// "[QCA956x (Dragonfly)]"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_dragonfly, "\xda\xc2\xa3\x85\xb8\xa6\xd6\xbc\xa1\xbb\xa4\xb6\xe0\xf4\x8f\xaa\xe7\xff\x99\xed\xdc\x00")
// "[IPQ4xx] (Dakota)"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_decoded_family_dakota, "\xda\xda\xb0\x95\xb5\xeb\x98\x99\xa1\xbb\xa4\xa5\xea\xfc\x94\xa5\xa8\x00")

#endif // #ifdef UBNT_SUPPORT_CLASS_WIFI

#if !SECURITY_ENABLE_SIMULATION
#if SECURITY_ENABLE_INI_SUPPORT
// "/etc/board.info"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_boardinfo_pathname, "\xae\xf6\x94\xa7\xae\xf1\x8f\xa5\xf3\xf7\xce\xad\xef\xf5\x8f\x00")
#endif // #if SECURITY_ENABLE_INI_SUPPORT
#endif // #if !SECURITY_ENABLE_SIMULATION
#if SECURITY_ENABLE_FILE_IO_SUPPORT
#if defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
// "/var/lock"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_security_lockfile_name, "\xae\xe5\x81\xb6\xae\xff\x8f\xa7\xea\x00")
#else // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
// "/var/lock/security"
__FS_FUNCTION_PREFER_INLINE FS_DESCRAMBLER(fs_get_security_lockfile_name, "\xae\xe5\x81\xb6\xae\xff\x8f\xa7\xea\xbc\x93\xa1\xe2\xe6\x92\xad\xf5\xea\x00")
#endif // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
#endif // #if SECURITY_ENABLE_FILE_IO_SUPPORT

