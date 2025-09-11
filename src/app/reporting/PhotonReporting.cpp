//
// Created by Mark Ragaee on 25/08/2025.
//

#include <app/AttributePathParams.h>
#include <app/ConcreteEventPath.h>

void  __attribute__((weak)) PhotonReportingAttributeChangeCallback(const chip::app::AttributePathParams & path) {}
void __attribute__((weak)) PhotonReportingNewEventGenerated(chip::app::ConcreteEventPath & aPath, uint8_t fabricIndex, uint8_t priority, uint64_t timestamp
, uint8_t * buf, uint32_t aBytesConsumed) {}
