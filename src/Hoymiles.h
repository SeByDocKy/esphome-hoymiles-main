// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#ifdef HMS_INVERTER
  #include "HoymilesRadio_CMT.h"
#endif
#ifdef HM_INVERTER
  #include "HoymilesRadio_NRF.h"
#endif
#include "inverters/InverterAbstract.h"
#include "types.h"
#include <Print.h>
#include <SPI.h>
#include <memory>
#include <vector>

#define HOY_SYSTEM_CONFIG_PARA_POLL_INTERVAL (2 * 60 * 1000) // 2 minutes
#define HOY_SYSTEM_CONFIG_PARA_POLL_MIN_DURATION (4 * 60 * 1000) // at least 4 minutes between sending limit command and read request. Otherwise eventlog entry

class HoymilesClass {
public:
    void init();
#ifdef HM_INVERTER
    void initNRF(SPIClass* initialisedSpiBus, const uint8_t pinCE, const uint8_t pinIRQ);
#endif
#ifdef HMS_INVERTER
    void initCMT(const int8_t pin_sdio, const int8_t pin_clk, const int8_t pin_cs, const int8_t pin_fcs, const int8_t pin_gpio2, const int8_t pin_gpio3);
#endif
    void loop();

    void setMessageOutput(Print* output);
    Print* getMessageOutput();

    std::shared_ptr<InverterAbstract> addInverter(const char* name, const uint64_t serial);
    std::shared_ptr<InverterAbstract> getInverterByPos(const uint8_t pos);
    std::shared_ptr<InverterAbstract> getInverterBySerial(const uint64_t serial);
    std::shared_ptr<InverterAbstract> getInverterByFragment(const fragment_t& fragment);

    // std::unique_ptr<InverterAbstract> addInverter(const char* name, const uint64_t serial);
    // std::unique_ptr<InverterAbstract> getInverterByPos(const uint8_t pos);
    // std::unique_ptr<InverterAbstract> getInverterBySerial(const uint64_t serial);
    // std::unique_ptr<InverterAbstract> getInverterByFragment(const fragment_t& fragment);


    void removeInverterBySerial(const uint64_t serial);
    size_t getNumInverters() const;
#ifdef HM_INVERTER
    HoymilesRadio_NRF* getRadioNrf();
#endif
#ifdef HMS_INVERTER
    HoymilesRadio_CMT* getRadioCmt();
#endif
    uint32_t PollInterval() const;
    void setPollInterval(const uint32_t interval);

    bool isAllRadioIdle() const;

private:
    // std::vector<std::unique_ptr<InverterAbstract>> _inverters;
    std::vector<std::shared_ptr<InverterAbstract>> _inverters;
// #ifdef HM_INVERTER
    std::unique_ptr<HoymilesRadio_NRF> _radioNrf;
// #endif
// #ifdef HMS_INVERTER
    std::unique_ptr<HoymilesRadio_CMT> _radioCmt;
// #endif
    std::mutex _mutex;

    uint32_t _pollInterval = 0;
    uint32_t _lastPoll = 0;

    Print* _messageOutput = &Serial;
};

extern HoymilesClass Hoymiles;
