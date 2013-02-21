/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.			      */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "DoubleSolenoid.h"
#include "NetworkCommunication/UsageReporting.h"
#include "WPIErrors.h"
#include <string.h>
#include "LiveWindow/LiveWindow.h"

/**
 * Common function to implement constructor behavior.
 */
void BugfixDoubleSolenoid::InitSolenoid()
{
    char buf[64];
    if (!CheckSolenoidModule(m_moduleNumber))
    {
	snprintf(buf, 64, "Solenoid Module %d", m_moduleNumber);
	wpi_setWPIErrorWithContext(ModuleIndexOutOfRange, buf);
	return;
    }
    if (!CheckSolenoidChannel(m_forwardChannel))
    {
	snprintf(buf, 64, "Solenoid Channel %d", m_forwardChannel);
	wpi_setWPIErrorWithContext(ChannelIndexOutOfRange, buf);
	return;
    }
    if (!CheckSolenoidChannel(m_reverseChannel))
    {
	snprintf(buf, 64, "Solenoid Channel %d", m_reverseChannel);
	wpi_setWPIErrorWithContext(ChannelIndexOutOfRange, buf);
	return;
    }
    Resource::CreateResourceObject(&m_allocated, tSolenoid::kNumDO7_0Elements * kSolenoidChannels);

    snprintf(buf, 64, "Solenoid %d (Module %d)", m_forwardChannel, m_moduleNumber);
    if (m_allocated->Allocate((m_moduleNumber - 1) * kSolenoidChannels + m_forwardChannel - 1, buf) == ~0ul)
    {
	CloneError(m_allocated);
	return;
    }
    snprintf(buf, 64, "Solenoid %d (Module %d)", m_reverseChannel, m_moduleNumber);
    if (m_allocated->Allocate((m_moduleNumber - 1) * kSolenoidChannels + m_reverseChannel - 1, buf) == ~0ul)
    {
	CloneError(m_allocated);
	return;
    }
    m_forwardMask = 1 << (m_forwardChannel - 1);
    m_reverseMask = 1 << (m_reverseChannel - 1);

    nUsageReporting::report(nUsageReporting::kResourceType_Solenoid, m_forwardChannel, m_moduleNumber - 1);
    nUsageReporting::report(nUsageReporting::kResourceType_Solenoid, m_reverseChannel, m_moduleNumber - 1);

    LiveWindow::GetInstance()->AddActuator("BugfixDoubleSolenoid", m_moduleNumber, m_forwardChannel, this);
}

/**
 * Constructor.
 * 
 * @param forwardChannel The forward channel on the module to control.
 * @param reverseChannel The reverse channel on the module to control.
 */
BugfixDoubleSolenoid::BugfixDoubleSolenoid(UINT32 forwardChannel, UINT32 reverseChannel)
    : SolenoidBase (GetDefaultSolenoidModule())
    , m_forwardChannel (forwardChannel)
    , m_reverseChannel (reverseChannel)
{
    InitSolenoid();
}

/**
 * Constructor.
 * 
 * @param moduleNumber The solenoid module (1 or 2).
 * @param forwardChannel The forward channel on the module to control.
 * @param reverseChannel The reverse channel on the module to control.
 */
BugfixDoubleSolenoid::BugfixDoubleSolenoid(UINT8 moduleNumber, UINT32 forwardChannel, UINT32 reverseChannel)
    : SolenoidBase (moduleNumber)
    , m_forwardChannel (forwardChannel)
    , m_reverseChannel (reverseChannel)
{
    InitSolenoid();
}

/**
 * Destructor.
 */
BugfixDoubleSolenoid::~BugfixDoubleSolenoid()
{
    if (CheckSolenoidModule(m_moduleNumber))
    {
	m_allocated->Free((m_moduleNumber - 1) * kSolenoidChannels + m_forwardChannel - 1);
	m_allocated->Free((m_moduleNumber - 1) * kSolenoidChannels + m_reverseChannel - 1);
    }
}

/**
 * Set the value of a solenoid.
 * 
 * @param value Move the solenoid to forward, reverse, or don't move it.
 */
void BugfixDoubleSolenoid::Set(Value value)
{
    if (StatusIsFatal()) return;

    Value oldValue = Get();

    UINT8 rawValue = 0x00;
    switch(value)
    {
    case kOff:
	rawValue = 0x00;
	break;
    case kForward:
	rawValue = m_forwardMask;
	break;
    case kReverse:
	rawValue = m_reverseMask;
	break;
    }

    if (value != oldValue) {
 	SolenoidBase::Set(rawValue, m_forwardMask | m_reverseMask);
    }
}

/**
 * Read the current value of the solenoid.
 * 
 * @return The current value of the solenoid.
 */
BugfixDoubleSolenoid::Value BugfixDoubleSolenoid::Get()
{
    if (StatusIsFatal()) {
	printf("BugfixDoubleSolenoid[%d][%d-%d]::Get"
		" status is FATAL, returning kOff\n",
		(int)m_moduleNumber, (int)m_forwardChannel,
		(int)m_reverseChannel);
	return kOff;
    }

    UINT8 value = GetAll();
    if (value & m_forwardMask) return kForward;
    if (value & m_reverseMask) return kReverse;
    return kOff;
}

void BugfixDoubleSolenoid::ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew)
{
    std::string *val = (std::string *) value.ptr;
    if (*val == "Off") Set(BugfixDoubleSolenoid::kOff);
    else if (*val == "Forward") Set(BugfixDoubleSolenoid::kForward);
    else if (*val == "Reverse") Set(BugfixDoubleSolenoid::kReverse);
    else printf("BugfixDoubleSolenoid[%d][%d-%d]::ValueChanged"
    		" value [%s] not valid\n", (int)m_moduleNumber,
		(int)m_forwardChannel, (int)m_reverseChannel, val->c_str());
}

void BugfixDoubleSolenoid::UpdateTable()
{
    if (m_table != NULL) {
	Value lvalue = Get();
	m_table->PutString("Value", (lvalue == kForward ? "Forward" : (lvalue == kReverse ? "Reverse" : "Off")));
    }
}

void BugfixDoubleSolenoid::StartLiveWindowMode()
{
    Set(kOff);
    m_table->AddTableListener("Value", this, true);
}

void BugfixDoubleSolenoid::StopLiveWindowMode() {
    Set(kOff);
    m_table->RemoveTableListener(this);
}

std::string BugfixDoubleSolenoid::GetSmartDashboardType() {
    return "Double Solenoid";
}

void BugfixDoubleSolenoid::InitTable(ITable *subTable) {
    m_table = subTable;
    UpdateTable();
}

ITable * BugfixDoubleSolenoid::GetTable() {
    return m_table;
}

