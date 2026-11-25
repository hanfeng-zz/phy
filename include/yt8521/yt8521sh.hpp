/*
 * Copyright (C) 2025-09-24  zheng zhao
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License v3.0 or later.
 * See <https://www.gnu.org/licenses/>.
 */
#pragma once

#include "mdioc++.h"
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#define YT8521_PER_STEP_PS  150

enum yt8521WorkMode {
    YT8521_WM_UTP_TO_RGMII,
    YT8521_WM_FIBER_TO_RGMII,
    YT8521_WM_UTP_FIBER_TO_RGMII,
    YT8521_WM_UTP_TO_SGMII,
    YT8521_WM_SGPHY_TO_RGMAC,
    YT8521_WM_SGMAC_TO_RGPHY,
    YT8521_WM_UTP_TO_FIBER_AUTO,
    YT8521_WM_UTP_TO_FIBER_FORCE
};

enum yt8521Register : uint16_t {
    //common register
    YT8521_REG_EXT_SMI_SDS_PHY                                          = 0xA000,
    YT8521_REG_EXT_CHIP_CONFIG                                          = 0xA001,
    YT8521_REG_EXT_SDS_CONFIG                                           = 0xA002,
    YT8521_REG_EXT_RGMII_CONFIG1                                        = 0xA003,
    YT8521_REG_EXT_RGMII_CONFIG2                                        = 0xA004,
    YT8521_REG_EXT_MDIO_CFG_AND_RGMII_OOB_MON                           = 0xA005,
    YT8521_REG_EXT_MISC_CONFIG                                          = 0xA006,
    YT8521_REG_EXT_MAC_ADDR_CFG1                                        = 0xA007,
    YT8521_REG_EXT_MAC_ADDR_CFG2                                        = 0xA008,
    YT8521_REG_EXT_MAC_ADDR_CFG3                                        = 0xA009,
    YT8521_REG_EXT_WOL_CFG                                              = 0xA00A,
    YT8521_REG_EXT_LED_GENERAL_CFG                                      = 0xA00B,
    YT8521_REG_EXT_LED0_CFG                                             = 0xA00C,
    YT8521_REG_EXT_LED1_CFG                                             = 0xA00D,
    YT8521_REG_EXT_LED2_CFG                                             = 0xA00E,
    YT8521_REG_EXT_LED_BLINK_CFG                                        = 0xA00F,
    YT8521_REG_EXT_PAD_DRIVE_STRENGTH_CFG                               = 0xA010,
    YT8521_REG_EXT_SYNCE_CFG                                            = 0xA012,

    //utp mii register
    YT8521_REG_BASIC_CONTROL_REG                                        = 0x0000,
    YT8521_REG_BASIC_CONTROL_STATUS                                     = 0x0001,
    YT8521_REG_PHY_IDENTIFICATION_REG1                                  = 0x0002,
    YT8521_REG_PHY_IDENTIFICATION_REG2                                  = 0x0003,
    YT8521_REG_AUTO_NEGOTIATION_ADVERTISEMENT                           = 0x0004,
    YT8521_REG_AUTO_NEGOTIATION_LINK_PARTNER_ABILITY                    = 0x0005,
    YT8521_REG_AUTO_NEGOTIATION_EXPANSION_REG                           = 0x0006,
    YT8521_REG_AUTO_NEGOTIATION_NEXT_PAGE_REG                           = 0x0007,
    YT8521_REG_AUTO_NEGOTIATION_LINK_PARTNER_RECEIVED_NEXT_PAGE_REG     = 0x0008,
    YT8521_REG_MASTER_SLAVE_CONTROL_REG                                 = 0x0009,
    YT8521_REG_MASTER_SLAVE_STATUS_REG                                  = 0x000A,

    YT8521_REG_MMD_ACCESS_CONTROL_REG                                   = 0x000D,
    YT8521_REG_MMD_ACCESS_DATA_REG                                      = 0x000E,
    YT8521_REG_EXTENDED_STATUS_REG                                      = 0x000F,
    YT8521_REG_PHY_SPECIFIC_FUNCTION_CONTROL_REG                        = 0x0010,
    YT8521_REG_PHY_SPECIFIC_FUNCTION_STATUS_REG                         = 0x0011,
    YT8521_REG_INTERRUPT_MASK_REG                                       = 0x0012,
    YT8521_REG_INTERRUPT_STATUS_REG                                     = 0x0013,
    YT8521_REG_SPEED_AUTO_DOWNGRADE_CONTROL_REG                         = 0x0014,
    YT8521_REG_RX_ERROR_COUNTER_REG                                     = 0x0015,

    YT8521_REG_EXTENDED_REG_ADDR_OFFSET_REG                             = 0x001E,
    YT8521_REG_EXTENDED_REG_DATA_REG                                    = 0x001F,

    //utp mmd reg
    YT8521_REG_UTP_MMD_PCS_CONTROL1_REG                                 = 0x0000,
    YT8521_REG_UTP_MMD_PCS_STATUS1_REG                                  = 0x0001,
    YT8521_REG_UTP_MMD_EEE_CONTROL_AND_CAPAILITY_REG                    = 0x0014,
    YT8521_REG_UTP_MMD_EEE_WAKE_ERROR_COUNTER                           = 0x0016,
    YT8521_REG_UTP_MMD_LOCAL_DEVICE_EEE_ABILITY                         = 0x003C,
    YT8521_REG_UTP_MMD_LINK_PARTNER_EEE_ABILITY                         = 0x003D,
    //utp lds
    YT8521_REG_UTP_LDS_LRE_CONTROL                                      = 0x0000,
    YT8521_REG_UTP_LDS_LRE_STATUS                                       = 0x0001,
    YT8521_REG_UTP_LDS_PHYID_REG1                                       = 0x0002,
    YT8521_REG_UTP_LDS_PHYID_REG2                                       = 0x0003,
    YT8521_REG_UTP_LDS_AUTO_NEGOTIATION_ADVERTISED_ABILITY              = 0x0004,
    YT8521_REG_UTP_LDS_LINK_PARTNER_ABILITY                             = 0x0007,
    YT8521_REG_UTP_LDS_EXPANSION                                        = 0x000A,
    YT8521_REG_UTP_LDS_RESULTS                                          = 0x000B,
    //utp ext
    YT8521_REG_UTP_EXT_PKGEN_CFG1                                       = 0x0038,
    YT8521_REG_UTP_EXT_PKGEN_CFG3                                       = 0x003A,
    YT8521_REG_UTP_EXT_PKGEN_CFG0                                       = 0x00A0,
    YT8521_REG_UTP_EXT_PKGEN_CFG2                                       = 0x00A1,
    YT8521_REG_UTP_EXT_PKG_RX_VALID0                                    = 0x00A3,
    YT8521_REG_UTP_EXT_PKG_RX_VALID1                                    = 0x00A4,
    YT8521_REG_UTP_EXT_PKG_RX_OS0                                       = 0x00A5,
    YT8521_REG_UTP_EXT_PKG_RX_OS1                                       = 0x00A6,
    YT8521_REG_UTP_EXT_PKG_RX_US0                                       = 0x00A7,
    YT8521_REG_UTP_EXT_PKG_RX_US1                                       = 0x00A8,
    YT8521_REG_UTP_EXT_PKG_RX_ERR                                       = 0x00A9,
    YT8521_REG_UTP_EXT_PKG_RX_OS_BAD                                    = 0x00AA,
    YT8521_REG_UTP_EXT_PKG_RX_FRAGMENT                                  = 0x00AB,
    YT8521_REG_UTP_EXT_PKG_RX_NOSFD                                     = 0x00AC,
    YT8521_REG_UTP_EXT_PKG_TX_VALID0                                    = 0x00AD,
    YT8521_REG_UTP_EXT_PKG_TX_VALID1                                    = 0x00AE,
    YT8521_REG_UTP_EXT_PKG_TX_OS0                                       = 0x00AF,
    YT8521_REG_UTP_EXT_PKG_TX_OS1                                       = 0x00B0,
    YT8521_REG_UTP_EXT_PKG_TX_US0                                       = 0x00B1,
    YT8521_REG_UTP_EXT_PKG_TX_US1                                       = 0x00B2,
    YT8521_REG_UTP_EXT_PKG_TX_ERR                                       = 0x00B3,
    YT8521_REG_UTP_EXT_PKG_TX_OS_BAD                                    = 0x00B4,
    YT8521_REG_UTP_EXT_PKG_TX_FRAGMENT                                  = 0x00B5,
    YT8521_REG_UTP_EXT_PKG_TX_NOSFD                                     = 0x00B6,
    //sds mii
//    YT8521_REG_SDS_MII_BASIC_CONTROL_REG                                = 0x0000, //see udp mii reg
//    YT8521_REG_SDS_MII_BASIC_STATUS_REG                                 = 0x0001,
//    YT8521_REG_SDS_MII_SDS_IDENTIFICATION_REG1                          = 0x0002,
//    YT8521_REG_SDS_MII_SDS_IDENTIFICATION_REG2                          = 0x0003,
//    YT8521_REG_SDS_MII_AUTO_NEGO_ADVERTISEMENT                          = 0x0004,
//    YT8521_REG_SDS_MII_AUTO_NEGO_LINK_PARTNER_ABILITY                   = 0x0005,
//    YT8521_REG_SDS_MII_AUTO_NEGO_EXPANSION_REG                          = 0x0006,
//    YT8521_REG_SDS_MII_AUTO_NEGO_NEXT_PAGE_REG                          = 0x0007,
//    YT8521_REG_SDS_MII_AUTO_NEGO_LINK_OARTNER_RECV_NEXT_PAGE_REG        = 0x0008,
    YT8521_REG_SDS_MII_EXTENDED_STATUS_REG                              = 0x000F,
    YT8521_REG_SDS_MII_SDS_SPEC_STATUS_REG                              = 0x0011,
    YT8521_REG_SDS_MII_100BASE_FX_CFG                                   = 0x0014,
    YT8521_REG_SDS_MII_ERR_CNT                                          = 0x0015,
    YT8521_REG_SDS_MII_LINKFAIL_CNT                                     = 0x0016,
    //sds ext
    YT8521_REG_SDS_EXT_PKGEN_CFG1                                       = 0x0038,
    YT8521_REG_SDS_EXT_PKGEN_CFG3                                       = 0x003A,
    YT8521_REG_SDS_EXT_PKGEN_CFG0                                       = 0x01A0,
    YT8521_REG_SDS_EXT_PKGEN_CFG2                                       = 0x01A1,
    YT8521_REG_SDS_EXT_PKG_RX_VALID0                                    = 0x01A3,
    YT8521_REG_SDS_EXT_PKG_RX_VALID1                                    = 0x01A4,
    YT8521_REG_SDS_EXT_PKG_RX_OS0                                       = 0x01A5,
    YT8521_REG_SDS_EXT_PKG_RX_OS1                                       = 0x01A6,
    YT8521_REG_SDS_EXT_PKG_RX_US0                                       = 0x01A7,
    YT8521_REG_SDS_EXT_PKG_RX_US1                                       = 0x01A8,
    YT8521_REG_SDS_EXT_PKG_RX_ERR                                       = 0x01A9,
    YT8521_REG_SDS_EXT_PKG_RX_OS_BAD                                    = 0x01AA,
    YT8521_REG_SDS_EXT_PKG_RX_FRAGMENT                                  = 0x01AB,
    YT8521_REG_SDS_EXT_PKG_RX_NOSFD                                     = 0x01AC,
    YT8521_REG_SDS_EXT_PKG_TX_VALID0                                    = 0x01AD,
    YT8521_REG_SDS_EXT_PKG_TX_VALID1                                    = 0x01AE,
    YT8521_REG_SDS_EXT_PKG_TX_OS0                                       = 0x01AF,
    YT8521_REG_SDS_EXT_PKG_TX_OS1                                       = 0x01B0,
    YT8521_REG_SDS_EXT_PKG_TX_US0                                       = 0x01B1,
    YT8521_REG_SDS_EXT_PKG_TX_US1                                       = 0x01B2,
    YT8521_REG_SDS_EXT_PKG_TX_ERR                                       = 0x01B3,
    YT8521_REG_SDS_EXT_PKG_TX_OS_BAD                                    = 0x01B4,
    YT8521_REG_SDS_EXT_PKG_TX_FRAGMENT                                  = 0x01B5,
    YT8521_REG_SDS_EXT_PKG_TX_NOSFD                                     = 0x01B6,
};

enum yt8521Bits {
    //0xA001
    YT8521_BITS_SW_RST                                                  = 1 << 15,
    YT8521_BITS_RGMII_CLK_DELAY_ENABLE                                  = 1 << 8,
    YT8521_BITS_ENABLE_IDO                                              = 1 << 6,
    //0xA002
    //see https://en.wikipedia.org/wiki/Media-independent_interface
    /* 功能说明
    正常情况下：
    当 MAC 在发送数据时检测到某种错误（如 FIFO underflow、编码错误等），会在 TX_EN 高电平时把 TX_ER 拉高，告诉 PHY：当前传输数据出错。
    开启 SUPPRESS_TX_ER 时：
    会 禁止/抑制 MAC 向 PHY 发送 TX_ER 信号。
    也就是说，即使 MAC 侧产生了发送错误，TX_ER 也不会传递给 PHY。
    PHY 只会看到 TX_EN + TXD，不会因为 TX_ER 而中止或标记帧错误。
    使用场景
    某些 MAC/PHY 不需要 TX_ER：SGMII、RGMII、RMII 等精简接口里，有时根本没有 TX_ER 线，为了兼容就提供这个控制。
    调试/特殊应用：
    如果上层软件希望错误帧也发出去（例如做测试），可以 suppress TX_ER。
在链路层或协议栈自己处理错误，而不是交给 PHY 时，会用到这个功能。*/
    YT8521_BITS_ENABLE_SURPPRESS_TXER                                   = 1 << 12,
    //0xA003
    YT8521_BITS_RGMII_CFG1_RGMAC_CFG_MODE                               = 1 << 15,
    YT8521_BITS_RGMII_CFG1_TX_CLK_SEL                                   = 1 << 14,
    //0xA004
    YT8521_BITS_RGMII_CFG2_DUPLEX_RGPHY                                 = 1 << 13,
    YT8521_BITS_RGMII_CFG2_LINK_UP_RGPHY                                = 1 << 12,
    YT8521_BITS_RGMII_CFG2_DUPLEX_RGMAC                                 = 1 << 5,
    YT8521_BITS_RGMII_CFG2_LINK_UP_RGMAC                                = 1 << 4,
    //0xA005
    YT8521_BITS_DUPLEX_RGMAC_OB                                         = 1 << 13,
    YT8521_BITS_LINKUP_RGMAC_OB                                         = 1 << 12,
    /*
     * 0xA006
     *  | Bit   | Symbol                | Default | Description / 作用解释
        | ----- | --------------------- | ------- | --------------------------------------------------------
        | 15:12 | `Clk_out_sel`         | 0x0     | 选择调试时钟输出到 `RX_CLK` 引脚，用于观察时钟信号。
        | 11    | `En_dbg_data_todac`   | 0x0     | 将 ADC 数据输出到 DAC 以便调试（一般用于芯片内部信号分析）。
        | 10    | `En_output_clk`       | 0x0     | 使能调试时钟输出到 `RX_CLK`，与 `Clk_out_sel` 配合使用。
        | 9     | `Reserved`            | 0x0     | 保留位，无功能。
        | 8     | `Fiber_high_pri_cmb`  | 0x0     | 在 UTP\_FIBER\_TO\_RGMII 模式下，fiber 链路优先级更高；否则 UTP 优先。
        | 7     | `Jumbo_enable`        | 0x0     | 使能 Jumbo Frame（大于 1500 字节以太网帧）。
        | 6     | `Rem_lpblk_sds`       | 0x0     | 为 **SDS（串行差分接口 / SerDes）** 设置远端环回（remote loopback）。
        | 5     | `Rem_lpblk_phy`       | 0x0     | 为 **UTP PHY** 设置远端环回。
        | 4     | `Uldata_rloopback`    | 0x0     | 当设置了远端环回（Rem\_lpblk）时，是否保留上传数据；1=保留。
        | 3     | `Bp_gmii_fatal_rst`   | 0x1     | 绕过 GMII FIFO overflow/underflow 的复位（bypass fatal reset）。
        | 2:1   | `Comb_wait_timer_sel` | 0x2     | 当次优先链路建立后，选择等待第一优先链路的时间：<br>00=1s, 01=5s, 10=15s, 11=25s
        | 0     | `Fib_speed_sel`       | 0x1     | 当自动感应关闭时，选择 fiber 速度：1=1000BX, 0=100FX
    */

};

class yt8521Driver {
public:
    yt8521Driver(const yt8521Driver &) = delete;

    yt8521Driver &operator=(const yt8521Driver&) = delete;

    yt8521Driver(const yt8521Driver &&) = delete;

    yt8521Driver &operator=(const yt8521Driver&&) = delete;

    yt8521Driver() {
        _mdio = std::make_shared<MdioDriver>();
    };

    virtual ~yt8521Driver() = default;

    int open(const std::string &interface, const uint16_t &id) {
        return _mdio->open(interface, id);
    }
/*
 * register type:
 * - mii register: 0x00 ~ 0x1f
 *      - read()
 *      - write()
 * - extended register: access via 0x1e,0x1f
 *      - read_ext()
 *      - write_ext()
 * - mmd register: access via 0xd,0xe
 *      - read_mmd() //todo: TBD
 *      - write_mmd() //todo: TBD
 *
 * */
    int read(const uint16_t &addr, uint16_t &val) {
        return _mdio->read(addr, val);
    }

    int write(const uint16_t &addr, const uint16_t &val) {
        return _mdio->write(addr, val);
    }

    int read_ext(const uint16_t &addr, uint16_t &val) {
        if (addr <= YT8521_REG_EXTENDED_REG_DATA_REG) {
            return MDIO_OVER_LIMIT;
        }

        int rc = write(YT8521_REG_EXTENDED_REG_ADDR_OFFSET_REG, addr);
        if (rc) {
            return rc;
        }

        return read(YT8521_REG_EXTENDED_REG_DATA_REG, val);
    }

    int write_ext(const uint16_t &addr, uint16_t &val) {
        if (addr <= YT8521_REG_EXTENDED_REG_DATA_REG) {
            return MDIO_OVER_LIMIT;
        }

        int rc = write(YT8521_REG_EXTENDED_REG_ADDR_OFFSET_REG, addr);
        if (rc) {
            return rc;
        }

        return write(YT8521_REG_EXTENDED_REG_DATA_REG, val);
    }

    int reset_software() {
        uint16_t val;

        int rc = read_ext(YT8521_REG_EXT_CHIP_CONFIG, val);
        if (rc) {
            return rc;
        }

        val &= (~YT8521_BITS_SW_RST);

        return write_ext(YT8521_REG_EXT_CHIP_CONFIG, val);
    }

    // 根据 work mode 选择 UTP/SDS packet checker，周期读取报文计数。
    //
    // UTP page:
    //   0xA0 Pkg Cfg0, 0xA3/0xA4 Rx Valid, 0xA9 Rx Err,
    //   0xAD/0xAE Tx Valid, 0xB3 Tx Err
    // SDS page:
    //   0x1A0/0x1A3/0x1A4/0x1A9/0x1AD/0x1AE/0x1B3
    //
    // Pkg Cfg0 bit15 Pkg_chk_en 必须先置 1；计数寄存器为 read-clear。
    int probePacketCounters(uint32_t periodSeconds, uint32_t count) {
        if ((0U == periodSeconds) || (0U == count)) {
            return -1;
        }

        uint16_t chipConfig = 0;
        if (read_ext(YT8521_REG_EXT_CHIP_CONFIG, chipConfig) != 0) {
            return -1;
        }
        const auto workmode = getWorkMode(chipConfig);
        bool useUtp = false;
        bool useSds = false;
        switch (workmode) {
            case YT8521_WM_UTP_TO_RGMII:
                useUtp = true;
                break;
            case YT8521_WM_FIBER_TO_RGMII:
            case YT8521_WM_SGPHY_TO_RGMAC:
            case YT8521_WM_SGMAC_TO_RGPHY:
                useSds = true;
                break;
            case YT8521_WM_UTP_FIBER_TO_RGMII:
            case YT8521_WM_UTP_TO_SGMII:
            case YT8521_WM_UTP_TO_FIBER_AUTO:
            case YT8521_WM_UTP_TO_FIBER_FORCE:
                useUtp = true;
                useSds = true;
                break;
            default:
                return -1;
        }

        struct packet_page {
            bool sds;
            uint16_t base;
            uint16_t originalConfig;
            bool enabledByProbe;
        };
        packet_page pages[2] = {};
        uint32_t page_count = 0;
        if (useUtp) {
            pages[page_count].sds = false;
            pages[page_count].base = 0x00A0U;
            page_count++;
        }
        if (useSds) {
            pages[page_count].sds = true;
            pages[page_count].base = 0x01A0U;
            page_count++;
        }

        uint16_t originalAccess = 0;
        if (read_ext(YT8521_REG_EXT_SMI_SDS_PHY, originalAccess) != 0) {
            return -1;
        }

        auto selectPage = [&](bool sds) -> int {
            uint16_t access = static_cast<uint16_t>(originalAccess & ~0x0002U);
            if (sds) {
                access = static_cast<uint16_t>(access | 0x0002U);
            }
            return write_ext(YT8521_REG_EXT_SMI_SDS_PHY, access);
        };

        for (uint32_t pageIndex = 0; pageIndex < page_count; pageIndex++) {
            packet_page& page = pages[pageIndex];
            if (selectPage(page.sds) != 0 ||
                read_ext(page.base, page.originalConfig) != 0) {
                return -1;
            }
            page.enabledByProbe = ((page.originalConfig & 0x8000U) == 0U);
            if (page.enabledByProbe) {
                uint16_t config = static_cast<uint16_t>(page.originalConfig | 0x8000U);
                if (write_ext(page.base, config) != 0) {
                    return -1;
                }
            }
        }

        uint32_t totalRx[2] = {};
        uint32_t totalTx[2] = {};
        uint32_t totalRxErr[2] = {};
        uint32_t totalTxErr[2] = {};

        int result = 0;
        for (uint32_t sample = 0; sample < count; sample++) {
            for (uint32_t pageIndex = 0; pageIndex < page_count; pageIndex++) {
                const packet_page& page = pages[pageIndex];
                if (selectPage(page.sds) != 0) {
                    result = -1;
                    break;
                }

                uint16_t rxHigh = 0;
                uint16_t rxLow = 0;
                uint16_t txHigh = 0;
                uint16_t txLow = 0;
                uint16_t rxErr = 0;
                uint16_t txErr = 0;
                if (read_ext(static_cast<uint16_t>(page.base + 0x03U), rxHigh) != 0 ||
                    read_ext(static_cast<uint16_t>(page.base + 0x04U), rxLow) != 0 ||
                    read_ext(static_cast<uint16_t>(page.base + 0x0DU), txHigh) != 0 ||
                    read_ext(static_cast<uint16_t>(page.base + 0x0EU), txLow) != 0 ||
                    read_ext(static_cast<uint16_t>(page.base + 0x09U), rxErr) != 0 ||
                    read_ext(static_cast<uint16_t>(page.base + 0x13U), txErr) != 0) {
                    result = -1;
                    break;
                }

                const uint32_t rxPackets = (static_cast<uint32_t>(rxHigh) << 16U) | rxLow;
                const uint32_t txPackets = (static_cast<uint32_t>(txHigh) << 16U) | txLow;
                totalRx[pageIndex] += rxPackets;
                totalTx[pageIndex] += txPackets;
                totalRxErr[pageIndex] += rxErr;
                totalTxErr[pageIndex] += txErr;

                std::cout << "packet:" << (sample + 1U) << "/" << count
                          << " page:" << (page.sds ? "SDS" : "UTP")
                          << " rxPackets:" << rxPackets
                          << " txPackets:" << txPackets
                          << " rxErr:" << rxErr
                          << " txErr:" << txErr
                          << " totalRx:" << totalRx[pageIndex]
                          << " totalTx:" << totalTx[pageIndex]
                          << " totalRxErr:" << totalRxErr[pageIndex]
                          << " totalTxErr:" << totalTxErr[pageIndex]
                          << std::endl;
            }
            if (result != 0) {
                break;
            }
            if ((sample + 1U) < count) {
                std::this_thread::sleep_for(std::chrono::seconds(periodSeconds));
            }
        }

        for (uint32_t pageIndex = 0; pageIndex < page_count; pageIndex++) {
            const packet_page& page = pages[pageIndex];
            if (selectPage(page.sds) != 0) {
                result = -1;
                continue;
            }
            if (page.enabledByProbe) {
                uint16_t config = page.originalConfig;
                if (write_ext(page.base, config) != 0) {
                    result = -1;
                }
            }
        }
        uint16_t restoreAccess = originalAccess;
        if (write_ext(YT8521_REG_EXT_SMI_SDS_PHY, restoreAccess) != 0) {
            result = -1;
        }

        return result;
    }

    int detect() {
        uint16_t id1 = 0;
        uint16_t id2 = 0;
        if ((read(YT8521_REG_PHY_IDENTIFICATION_REG1, id1) != 0) ||
            (read(YT8521_REG_PHY_IDENTIFICATION_REG2, id2) != 0)) {
            std::cout << "read PHY identification failed" << std::endl;
            return -1;
        }
        std::cout << "phy id1:0x" << std::hex << id1 << " id2:0x" << id2 << std::dec << std::endl;

        uint16_t access = 0;
        uint16_t chipConfig = 0;
        uint16_t sdsConfig = 0;
        uint16_t rgmiiConfig1 = 0;
        uint16_t rgmiiConfig2 = 0;
        uint16_t mdioConfig = 0;
        uint16_t miscConfig = 0;
        uint16_t oobStatus = 0;
        uint16_t basicControl = 0;
        uint16_t basicStatus = 0;
        uint16_t phyStatus = 0;
        uint16_t sdsStatus = 0;
        uint16_t rxError = 0;

        if (read_ext(YT8521_REG_EXT_SMI_SDS_PHY, access) != 0) {
            std::cout << "read 0xA000 failed!" << std::endl;
            return -1;
        }
        const bool sds = ((access & 0x2U) != 0U);
        std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_SMI_SDS_PHY
                  << " val:0x" << access << std::dec
                  << " ---> space:" << getAccessSpace(access) << std::endl;

        if (read(YT8521_REG_BASIC_CONTROL_REG, basicControl) != 0) {
            std::cout << "read Basic Control failed!" << std::endl;
            return -1;
        }
        if (read(YT8521_REG_BASIC_CONTROL_STATUS, basicStatus) != 0) {
            std::cout << "read Basic Status failed!" << std::endl;
            return -1;
        }
        if (sds) {
            if (read(YT8521_REG_SDS_MII_SDS_SPEC_STATUS_REG, sdsStatus) != 0) {
                std::cout << "read SDS Specific Status failed!" << std::endl;
                return -1;
            }
        } else if (read(YT8521_REG_PHY_SPECIFIC_FUNCTION_STATUS_REG, phyStatus) != 0) {
            std::cout << "read PHY Specific Status failed!" << std::endl;
            return -1;
        }
        if (read(YT8521_REG_RX_ERROR_COUNTER_REG, rxError) != 0) {
            std::cout << "read RX Error Counter failed!" << std::endl;
            return -1;
        }

        if (read_ext(YT8521_REG_EXT_CHIP_CONFIG, chipConfig) != 0) {
            std::cout << "read 0xA001 failed!" << std::endl;
            return -1;
        }
        const auto workmode = getWorkMode(chipConfig);
        const bool hasSerdes = (workmode == YT8521_WM_FIBER_TO_RGMII) ||
                               (workmode == YT8521_WM_UTP_FIBER_TO_RGMII) ||
                               (workmode == YT8521_WM_UTP_TO_SGMII) ||
                               (workmode == YT8521_WM_SGPHY_TO_RGMAC) ||
                               (workmode == YT8521_WM_SGMAC_TO_RGPHY) ||
                               (workmode == YT8521_WM_UTP_TO_FIBER_AUTO) ||
                               (workmode == YT8521_WM_UTP_TO_FIBER_FORCE);
        const bool hasRgmii = (workmode == YT8521_WM_UTP_TO_RGMII) ||
                              (workmode == YT8521_WM_FIBER_TO_RGMII) ||
                              (workmode == YT8521_WM_UTP_FIBER_TO_RGMII) ||
                              (workmode == YT8521_WM_SGPHY_TO_RGMAC) ||
                              (workmode == YT8521_WM_SGMAC_TO_RGPHY);
        const bool rgmiiIsPhy = (workmode == YT8521_WM_UTP_TO_RGMII) ||
                                (workmode == YT8521_WM_FIBER_TO_RGMII) ||
                                (workmode == YT8521_WM_UTP_FIBER_TO_RGMII) ||
                                (workmode == YT8521_WM_SGMAC_TO_RGPHY);
        const bool rgmiiIsMac = (workmode == YT8521_WM_SGPHY_TO_RGMAC);

        std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_CHIP_CONFIG
                  << " val:0x" << chipConfig << std::dec << std::endl;
        std::cout << "work mode:" << getChipMode(chipConfig) << std::endl;
        const uint16_t configuredSpeed = ((basicControl & 0x0040U) ? 2U : 0U) |
                                         ((basicControl & 0x2000U) ? 1U : 0U);
        std::cout << "config: autoNeg:" << ((basicControl & 0x1000U) ? "on" : "off")
                  << " speed:" << speedName(configuredSpeed)
                  << " duplex:" << ((basicControl & 0x0100U) ? "full" : "half")
                  << " loopback:" << ((basicControl & 0x4000U) ? "on" : "off")
                  << " powerDown:" << ((basicControl & 0x0800U) ? "on" : "off")
                  << " isolate:" << ((basicControl & 0x0400U) ? "on" : "off")
                  << " reset:" << ((basicControl & 0x8000U) ? "yes" : "no") << std::endl;
        if (read_ext(YT8521_REG_EXT_MISC_CONFIG, miscConfig) != 0) {
            std::cout << "read 0xA006 failed!" << std::endl;
            return -1;
        }
        std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_MISC_CONFIG
                  << " val:0x" << miscConfig << std::dec << std::endl;
        std::cout << "misc config: fiberHighPriority:" << ((miscConfig & 0x0100U) ? "yes" : "no")
                  << " jumbo:" << ((miscConfig & 0x0080U) ? "enable" : "disable")
                  << " sdsRemoteLoopback:" << ((miscConfig & 0x0040U) ? "enable" : "disable")
                  << " phyRemoteLoopback:" << ((miscConfig & 0x0020U) ? "enable" : "disable")
                  << std::endl;

        if (hasSerdes) {
            if (read_ext(YT8521_REG_EXT_SDS_CONFIG, sdsConfig) != 0) {
                std::cout << "read 0xA002 failed!" << std::endl;
                return -1;
            }
            std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_SDS_CONFIG
                      << " val:0x" << sdsConfig << std::dec << std::endl;
            std::cout << "suppress TXER:"
                      << ((sdsConfig & YT8521_BITS_ENABLE_SURPPRESS_TXER) ? "enable" : "disable")
                      << std::endl;
        }

        if (hasRgmii) {
            std::cout << "RGMII LDO:" << ((chipConfig & YT8521_BITS_ENABLE_IDO) ? "enable" : "disable") << std::endl;
            std::cout << "RGMII LDO voltage:" << getChipCfgIdo(chipConfig) << std::endl;
            std::cout << "RGMII 2ns clock delay:"
                      << ((chipConfig & YT8521_BITS_RGMII_CLK_DELAY_ENABLE) ? "enable" : "disable")
                      << std::endl;
        }

        if (read_ext(YT8521_REG_EXT_MDIO_CFG_AND_RGMII_OOB_MON, mdioConfig) != 0) {
            std::cout << "read 0xA005 failed!" << std::endl;
            return -1;
        }
        std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_MDIO_CFG_AND_RGMII_OOB_MON
                  << " val:0x" << mdioConfig << std::dec << std::endl;
        std::cout << "MDIO config: watchdogBypass:" << ((mdioConfig & 0x0400U) ? "yes" : "no")
                  << " phyAddr0:" << ((mdioConfig & 0x0040U) ? "yes" : "no")
                  << " broadcast:" << ((mdioConfig & 0x0020U) ? "yes" : "no")
                  << " broadcastAddr:" << (mdioConfig & 0x001FU) << std::endl;

        const uint16_t status = sds ? sdsStatus : phyStatus;
        const uint16_t speedBits = (status >> 14U) & 0x3U;
        const bool linkUp = ((status & 0x0400U) != 0U);
        const bool duplexFull = ((status & 0x2000U) != 0U);
        const bool autoNegEnabled = ((basicControl & 0x1000U) != 0U);
        const bool autoNegDone = ((basicStatus & 0x0020U) != 0U) || ((status & 0x0800U) != 0U);
        const bool remoteFault = ((basicStatus & 0x0010U) != 0U);

        std::cout << "media:" << (sds ? "SDS" : "UTP")
                  << " status:0x" << std::hex << status << std::dec
                  << " link:" << (linkUp ? "up" : "down")
                  << " speed:" << speedName(speedBits)
                  << " duplexBit:" << (duplexFull ? 1 : 0)
                  << " autoNeg:" << (!autoNegEnabled ? "off" : (autoNegDone ? "done" : "busy"))
                  << " remoteFault:" << (remoteFault ? "yes" : "no") << std::endl;

        if (hasRgmii) {
            if (read_ext(YT8521_REG_EXT_RGMII_CONFIG1, rgmiiConfig1) != 0) {
                std::cout << "read 0xA003 failed!" << std::endl;
                return -1;
            }
            if (read_ext(YT8521_REG_EXT_RGMII_CONFIG2, rgmiiConfig2) != 0) {
                std::cout << "read 0xA004 failed!" << std::endl;
                return -1;
            }

            std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_RGMII_CONFIG1
                      << " val:0x" << rgmiiConfig1 << std::dec << std::endl;
            std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_RGMII_CONFIG2
                      << " val:0x" << rgmiiConfig2 << std::dec << std::endl;
            std::cout << "RGMII config: txClkSel:"
                      << ((rgmiiConfig1 & YT8521_BITS_RGMII_CFG1_TX_CLK_SEL) ? "inverted" : "normal")
                      << " crs:" << ((rgmiiConfig1 & 0x0100U) ? "enable" : "disable")
                      << " fdCrs:" << ((rgmiiConfig1 & 0x0200U) ? "enable" : "disable");
            if (rgmiiIsMac) {
                std::cout << " rgmacCfgMode:"
                          << ((rgmiiConfig1 & YT8521_BITS_RGMII_CFG1_RGMAC_CFG_MODE) ? "register" : "oob");
            }
            std::cout << std::endl;

            if (rgmiiIsPhy) {
                std::cout << "RGMII PHY: speed:" << speedName(getSpeedRgPhy(rgmiiConfig2))
                          << " duplexBit:"
                          << ((rgmiiConfig2 & YT8521_BITS_RGMII_CFG2_DUPLEX_RGPHY) ? 1 : 0)
                          << " link:"
                          << ((rgmiiConfig2 & YT8521_BITS_RGMII_CFG2_LINK_UP_RGPHY) ? "up" : "down")
                          << std::endl;
            }

            if (rgmiiIsMac) {
                if (rgmiiConfig1 & YT8521_BITS_RGMII_CFG1_RGMAC_CFG_MODE) {
                    std::cout << "RGMII MAC: speed:" << speedName(getSpeedRgMac(rgmiiConfig2))
                              << " duplexBit:"
                              << ((rgmiiConfig2 & YT8521_BITS_RGMII_CFG2_DUPLEX_RGMAC) ? 1 : 0)
                              << " link:"
                              << ((rgmiiConfig2 & YT8521_BITS_RGMII_CFG2_LINK_UP_RGMAC) ? "up" : "down")
                              << std::endl;
                } else {
                    if (read_ext(YT8521_REG_EXT_MDIO_CFG_AND_RGMII_OOB_MON, oobStatus) != 0) {
                        std::cout << "read 0xA005 failed!" << std::endl;
                        return -1;
                    }
                    std::cout << "reg:0x" << std::hex << YT8521_REG_EXT_MDIO_CFG_AND_RGMII_OOB_MON
                              << " val:0x" << oobStatus << std::dec << std::endl;
                    std::cout << "RGMII MAC OOB: speed:" << speedName((oobStatus >> 14U) & 0x3U)
                              << " duplexBit:"
                              << ((oobStatus & YT8521_BITS_DUPLEX_RGMAC_OB) ? 1 : 0)
                              << " link:"
                              << ((oobStatus & YT8521_BITS_LINKUP_RGMAC_OB) ? "up" : "down")
                              << " watchdogBypass:" << ((oobStatus & 0x0400U) ? "yes" : "no")
                              << " phyAddr0:" << ((oobStatus & 0x0040U) ? "yes" : "no")
                              << " broadcast:" << ((oobStatus & 0x0020U) ? "yes" : "no")
                              << std::endl;
                }
            }

            std::cout << "RGMII RX clock delay(ps):" << getRgmiiRxDelay(rgmiiConfig1) << std::endl;
            std::cout << "RGMII TX clock FE delay(ps):" << getRgmiiTxDelayFe(rgmiiConfig1) << std::endl;
            std::cout << "RGMII TX clock delay(ps):" << getRgmiiTxDelay(rgmiiConfig1) << std::endl;
        }

        std::cout << "RX error counter:0x" << std::hex << rxError << std::dec << std::endl;
        return 0;
    }
    //note: MdioDriver auto close
protected:
/*-------------------------0xA000-----start-----------------------------*/
    std::string getAccessSpace(const uint16_t &val) {
        std::vector<std::string> str_space {
            "UTP_SPACE",
            "SDS_SPACE"
        };
        return str_space.at((val >> 1) & 0x1);
    };
/*-------------------------0xA000-----end-----------------------------*/
/*-------------------------0xA001-----start-----------------------------*/
    enum yt8521WorkMode getWorkMode(const uint16_t &val) {
        return yt8521WorkMode(val & 0x7);
    }

    std::string getChipMode(const uint16_t &val) {
        std::vector<std::string> str_workmode {
                "YT8521_WM_UTP_TO_RGMII",
                "YT8521_WM_FIBER_TO_RGMII",
                "YT8521_WM_UTP_FIBER_TO_RGMII",
                "YT8521_WM_UTP_TO_SGMII",
                "YT8521_WM_SGPHY_TO_RGMAC",
                "YT8521_WM_SGMAC_TO_RGPHY",
                "YT8521_WM_UTP_TO_FIBER_AUTO",
                "YT8521_WM_UTP_TO_FIBER_FORCE"
        };
        return str_workmode.at(val & 0x7);
    }

    std::string getChipCfgIdo(const uint16_t &val) {
        std::vector<std::string> str_ido {
                "3.3v",
                "2.5v",
                "1.8v",
                "1.8v",
        };
        return str_ido.at((val >> 4) & 0x3);
    };
/*-------------------------0xA001-----end-----------------------------*/

/*-------------------------0xA003-----start-----------------------------*/
    int getRgmiiRxDelay(const uint16_t &val) {
        return ((val >> 10) & 0xF) * YT8521_PER_STEP_PS; // step * 150ps
    }
    //for 100M or 10M
    int getRgmiiTxDelayFe(const uint16_t &val) {
        return ((val >> 4) & 0xF) * YT8521_PER_STEP_PS; // step * 150ps
    }
    //for 1000M
    int getRgmiiTxDelay(const uint16_t &val) {
        return (val & 0xF) * YT8521_PER_STEP_PS; // step * 150ps
    }
/*-------------------------0xA003-----end-----------------------------*/

/*-------------------------0xA004-----start-----------------------------*/
    static const char *speedName(uint16_t speed) {
        switch (speed & 0x3U) {
            case 0U: return "10M";
            case 1U: return "100M";
            case 2U: return "1000M";
            default: return "reserved";
        }
    }

    uint16_t getSpeedRgPhy(uint16_t val) {
        return (val >> 14) & 0x3;
    }
    uint16_t getSpeedRgMac(uint16_t val) {
        return (val >> 6) & 0x3;
    }
/*-------------------------0xA004-----end-----------------------------*/
private:
    std::shared_ptr<MdioDriver> _mdio = nullptr;
};