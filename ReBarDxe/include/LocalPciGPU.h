#if !defined(REBAR_UEFI_LOCAL_PCI_GPU_H)
#define REBAR_UEFI_LOCAL_PCI_GPU_H

// Hard-coded values that must match the local system

#include <stdint.h>

enum BARSizeSelect
{
    _256M = 0u,
    _512M = 1u,
      _1G = 2u,
      _2G = 3u,
      _4G = 4u,
      _8G = 5u,
     _16G = 6u,
     _32G = 7u
};

// Update these values to match the output from CPU-Z .txt report
// for your GPU and for the associated PCI-to-PCI bridge

#define TARGET_GPU_PCI_VENDOR_ID        0x10DEu
#define TARGET_GPU_PCI_DEVICE_ID        0x1E07u

#define TARGET_GPU_PCI_BUS              0x41u
#define TARGET_GPU_PCI_DEVICE           0x00u
#define TARGET_GPU_PCI_FUNCTION         0x00u
#define TARGET_GPU_BAR0_ADDRESS         UINT32_C(0x8200'0000)               // Should fall within memory range mapped by the bridge 

#define TARGET_GPU_BAR1_SIZE_SELECTOR   _16G                                // Desired size for GPU BAR1, should cover the VRAM size

// Secondary bus of the bridge must match the GPU bus
// Check the output form CPU-Z .txt report

#define TARGET_BRIDGE_PCI_VENDOR_ID     0x1022u
#define TARGET_BRIDGE_PCI_DEVICE_ID     0x1453u

#define TARGET_BRIDGE_PCI_BUS           0x40u
#define TARGET_BRIDGE_PCI_DEVICE        0x03u
#define TARGET_BRIDGE_PCI_FUNCTION      0x01u

// Memory range and I/O port range (base + limit) mapped to bridge
// from CPU-Z .txt report of the bridge and GPU
#define TARGET_BRIDGE_MEM_BASE_LIMIT  UINT32_C(0x8300'8200)             // Should cover the GPU BAR0
#define TARGET_BRIDGE_IO_BASE_LIMIT   0x8181u

static_assert((TARGET_GPU_BAR0_ADDRESS & UINT32_C(0x0000'0001)) == 0u, "Unexpected GPU BAR0 in the I/O port range");
static_assert((TARGET_GPU_BAR0_ADDRESS & UINT32_C(0x0000'0006)) == 0u, "Unexpected GPU BAR0 in the 64-bit memory address space");

#endif          // !defined(REBAR_UEFI_LOCAL_PCI_GPU_H)