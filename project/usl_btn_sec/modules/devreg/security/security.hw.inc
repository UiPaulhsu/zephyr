#include "security.hw.target.sim.inc"
#include "security.hw.target.GM81xx.inc"
#include "security.hw.target.IPQ40xx.inc"
#include "security.hw.target.ARxxxx.inc"
#include "security.hw.target.RTL838x.inc"
#include "security.hw.target.CN50xx.inc"
#include "security.hw.target.MT7621.inc"
#include "security.hw.target.MT7623.inc"
#include "security.hw.target.AM18xx.inc"
#include "security.hw.target.AM3xxx.inc"
#include "security.hw.target.A5S.inc"
#include "security.hw.target.S2.inc"
#include "security.hw.target.S2L.inc"
#include "security.hw.target.S2LM.inc"
#include "security.hw.target.S5L.inc"
#include "security.hw.target.S5LM.inc"
#include "security.hw.target.BCM4706.inc"
#include "security.hw.target.QCA851x.inc"
#include "security.hw.target.BCM5334x.inc"
#include "security.hw.target.BCM5341x.inc"
#include "security.hw.target.VSC7514.inc"
#include "security.hw.target.BCM5616x.inc"
#include "security.hw.target.BCM111xx.inc"
#include "security.hw.target.NVRx64.inc"
#include "security.hw.target.MT8117.inc"
#include "security.hw.target.STM32F30x.inc"
#include "security.hw.target.IPQ806x.inc"
#include "security.hw.target.APQ8053.inc"
#include "security.hw.target.AL324.inc"
#include "security.hw.target.IPQ807x.inc"
#include "security.hw.target.EFR32xG13.inc"
#include "security.hw.target.ST50H.inc"

#if SECURITY_IS_TARGET_BUILD

#if UBNT_LINUX
#if !defined( __KERNEL__) && defined(SECURITY_IS_TARGET_BUILD)
	__FS_FUNCTION_PREFER_INLINE void fs_read_mac_address_hw(u_int8_t* dest, const char* ifname) {
		int fd = -1;
		struct ifreq ifr;

		memset( dest, 0xff, MAC_ADDRESS_SIZE );
		memset(&ifr,0,sizeof(ifr));

		if (fs_strnlen(ifname, sizeof ifr.ifr_name) >= sizeof ifr.ifr_name) {
			fs_low_level_failure(FS_FAILURE_fs_read_mac_address_hw_2);
		}
		strncpy( ifr.ifr_name, (char*)ifname, sizeof ifr.ifr_name);
		memset( &ifr.ifr_hwaddr.sa_data, 0xff, MAC_ADDRESS_SIZE);
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(fd == -1) {
			fs_low_level_failure(FS_FAILURE_fs_read_mac_address_hw_1);
		} else {
			if (ioctl (fd, SIOCGIFHWADDR, &ifr) < 0) {
				memset( dest, 0xff, MAC_ADDRESS_SIZE );
			}
			memcpy(dest, &ifr.ifr_hwaddr.sa_data, MAC_ADDRESS_SIZE);
			close(fd);
			fd = -1;
		}
	}
#endif // #if !defined( __KERNEL__) && defined(SECURITY_IS_TARGET_BUILD)

#if defined (__KERNEL__)
#if defined(UBNT_ARM) || (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,22))
    extern struct net init_net;
    __FS_FUNCTION_PREFER_INLINE struct net_device* fs_dev_get_by_name(const char* ifname) {
        return dev_get_by_name(&init_net,ifname);
    }
#else // #ifdef UBNT_ARM or LINUX_VERSION_CODE > KERNEL_VERSION(2,6,22)
    __FS_FUNCTION_PREFER_INLINE struct net_device* fs_dev_get_by_name(const char* ifname) {
	    return dev_get_by_name(ifname);
    }
#endif // #ifdef UBNT_ARM or LINUX_VERSION_CODE > KERNEL_VERSION(2,6,22)
    __FS_FUNCTION_PREFER_INLINE void fs_read_mac_address_hw(u_int8_t* dest, const char* ifname) {
            struct net_device* fsv_t1 = fs_dev_get_by_name(ifname);
            if(NULL != fsv_t1) {
                memcpy((char*)dest, (char*)fsv_t1->dev_addr, MAC_ADDRESS_SIZE);
                dev_put(fsv_t1);
                fsv_t1 = NULL;
            } else {
                memset((char*)dest, 0xff, MAC_ADDRESS_SIZE);
            }
    }
#endif // #if defined (__KERNEL__)
#endif // #if UBNT_LINUX

#if SECURITY_ENABLE_MAC_ADDRESS_SUPPORT
#if SECURITY_ENABLE_SIMULATION

	__FS_FUNCTION_PREFER_INLINE void fs_read_eth0_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "ETH0_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_ETH0_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}
	__FS_FUNCTION_PREFER_INLINE void fs_read_eth1_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "ETH1_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_ETH1_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}
	__FS_FUNCTION_PREFER_INLINE void fs_read_airfiber_air0_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "ETH1_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_ETH1_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}
	__FS_FUNCTION_PREFER_INLINE void fs_read_wifi_radio1_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "WIFI_RADIO1_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_WIFI_RADIO1_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}
	__FS_FUNCTION_PREFER_INLINE void fs_read_wifi_radio2_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "WIFI_RADIO2_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_WIFI_RADIO2_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}
	__FS_FUNCTION_PREFER_INLINE void fs_read_BCM4706_wifi_radio1_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "BCM4706_RADIO1_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_BCMWIFI_RADIO1_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}
	__FS_FUNCTION_PREFER_INLINE void fs_read_BCM4706_wifi_radio2_mac_address_hw(u_int8_t* dest, size_t dest_len) {
		BEGIN_SUSPEND_FAILURES
		if( MAC_ADDRESS_SIZE != fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "BCM4706_RADIO2_MAC_ADDRESS", MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 0)) {
			fs_read_config(dest, dest_len, FLASH_SECURITY_OFFSET_BCMWIFI_RADIO2_MAC_ADDRESS, MAC_ADDRESS_SIZE);
		}
		END_SUSPEND_FAILURES
	}

#else // #if SECURITY_ENABLE_SIMULATION
	__FS_FUNCTION_PREFER_INLINE void fs_read_eth0_mac_address_hw           (u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_eth0());  }
	__FS_FUNCTION_PREFER_INLINE void fs_read_eth1_mac_address_hw           (u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_eth1());  }
    __FS_FUNCTION_PREFER_INLINE void fs_read_eth2_mac_address_hw               (u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_eth2());  }
#ifdef UBNT_SUPPORT_CLASS_AIRFIBER
	__FS_FUNCTION_PREFER_INLINE void fs_read_airfiber_air0_mac_address_hw(u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_air0());  }
#endif // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER
#if defined(UBNT_MIPS_ARxxxx) || defined(UBNT_ARM_IPQ40xx)
	__FS_FUNCTION_PREFER_INLINE void fs_read_wifi_radio1_mac_address_hw(u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_wifi0()); }
	__FS_FUNCTION_PREFER_INLINE void fs_read_wifi_radio2_mac_address_hw(u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_wifi1()); }
#endif // #ifdef UBNT_MIPS_ARxxxx
#ifdef UBNT_MIPS_BCM4706
	__FS_FUNCTION_PREFER_INLINE void fs_read_BCM4706_wifi_radio1_mac_address_hw (u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_eth1());  }
	__FS_FUNCTION_PREFER_INLINE void fs_read_BCM4706_wifi_radio2_mac_address_hw (u_int8_t* dest, size_t UNUSED(dest_len))    { fs_read_mac_address_hw(dest,fs_get_ifname_eth2());  }
#endif // #ifdef UBNT_MIPS_BCM4706
#endif // #if SECURITY_ENABLE_SIMULATION
#endif // SECURITY_ENABLE_MAC_ADDRESS_SUPPORT

#elif !defined(SECURITY_ENABLE_SIMULATION)
#error devreg was unable to identify the hardware platform.
#endif // #if SECURITY_IS_TARGET_BUILD
