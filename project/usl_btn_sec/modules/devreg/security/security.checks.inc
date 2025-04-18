#if SECURITY_IS_TARGET_BUILD

// Common stuff
#include "security.checks.common.begin.inc"

// Then platform-specific stuff next
#include "security.checks.target.AMBA.inc"
#include "security.checks.target.AM18xx.inc"
#include "security.checks.target.ARxxxx.inc"
#include "security.checks.target.BCM111xx.inc"
#include "security.checks.target.BCM4706.inc"
#include "security.checks.target.BCM5334x.inc"
#include "security.checks.target.VSC7514.inc"
#include "security.checks.target.BCM5341x.inc"
#include "security.checks.target.BCM5616x.inc"
#include "security.checks.target.CN50xx.inc"
#include "security.checks.target.MT7621.inc"
#include "security.checks.target.MT7623.inc"
#include "security.checks.target.GM81xx.inc"
#include "security.checks.target.NVRx64.inc"
#include "security.checks.target.QCA851x.inc"
#include "security.checks.target.MT8117.inc"
#include "security.checks.target.STM32F30x.inc"
#include "security.checks.target.IPQ40xx.inc"
#include "security.checks.target.IPQ806x.inc"
#include "security.checks.target.APQ8053.inc"
#include "security.checks.target.AL324.inc"
#include "security.checks.target.IPQ807x.inc"
#include "security.checks.target.RTL838x.inc"
#include "security.checks.target.EFR32xG13.inc"
#include "security.checks.target.ST50H.inc"


// Class-specific stuff first
#include "security.checks.class.airfiber.inc"
#include "security.checks.class.bcmwifi.inc"
#include "security.checks.class.camera.inc"
#include "security.checks.class.camera2.inc"
#include "security.checks.class.nvr.inc"
#include "security.checks.class.qcaswitch.inc"
#include "security.checks.class.bcmswitch.inc"
#include "security.checks.class.cloudkey.inc"
#include "security.checks.class.router.inc"
#include "security.checks.class.solargateway.inc"
#include "security.checks.class.switch.inc"
#include "security.checks.class.basic.inc"
#include "security.checks.class.basic4k.inc"
#include "security.checks.class.univox.inc"
#include "security.checks.class.wifi.inc"
#include "security.checks.class.inverter.inc"
// Common stuff
#include "security.checks.common.end.inc"

#endif // #if SECURITY_IS_TARGET_BUILD
