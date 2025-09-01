//
// Created by Mark Ragaee on 25/08/2025.
//
#pragma once

#include <app/AttributePathParams.h>
#include <app/ConcreteEventPath.h>

/** @brief Reporting Attribute Change
 *
 * This function is called by the framework when an attribute managed by the
 * framework changes.  The application should call this function when an
 * externally-managed attribute changes.  This function triggers attribute
 * reports for subscriptions as needed.
 */
void PhotonReportingAttributeChangeCallback(const chip::app::AttributePathParams & path);
void PhotonReportingNewEventGenerated(chip::app::ConcreteEventPath & aPath, uint8_t fabricIndex, uint8_t priority, uint64_t timestamp
, uint8_t * buf, uint32_t aBytesConsumed);

