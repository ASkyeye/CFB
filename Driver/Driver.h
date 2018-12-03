#pragma once

#include "Common.h"
#include "../Common/common.h"

#include "IoctlCodes.h"
#include "Utils.h"
#include "HookedDrivers.h"
#include "InterceptedIrpHandler.h"
#include "Queue.h"

#include "IoAddDriver.h"
#include "IoRemoveDriver.h"
#include "IoGetDriverInfo.h"
#include "IoEnableDisableMonitoring.h"




NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);
NTSTATUS DriverReadRoutine( PDEVICE_OBJECT DeviceObject, PIRP Irp );
VOID DriverUnloadRoutine(PDRIVER_OBJECT DriverObject);
NTSTATUS DriverCreateRoutine(PDEVICE_OBJECT pObject, PIRP Irp);
NTSTATUS DriverCloseRoutine(PDEVICE_OBJECT pObject, PIRP Irp);
NTSTATUS DriverDeviceControlRoutine(PDEVICE_OBJECT pObject, PIRP Irp);
NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR Information);
NTSTATUS IrpNotImplementedHandler( PDEVICE_OBJECT DeviceObject, PIRP Irp );


//
// See https://lylone.wordpress.com/2007/05/08/obreferenceobjectbynameundocumented/
//
extern POBJECT_TYPE* IoDriverObjectType;
extern POBJECT_TYPE* IoDeviceObjectType;

extern NTSYSAPI NTSTATUS NTAPI ObReferenceObjectByName(
	IN PUNICODE_STRING ObjectPath,
	IN ULONG Attributes,
	IN PACCESS_STATE PassedAccessState OPTIONAL,
	IN ACCESS_MASK DesiredAccess OPTIONAL,
	IN POBJECT_TYPE ObjectType,
	IN KPROCESSOR_MODE AccessMode,
	IN OUT PVOID ParseContext OPTIONAL,
	OUT PVOID *ObjectPtr
);

/*
NTSTATUS InterceptedDeviceControlRoutine( PDEVICE_OBJECT DeviceObject, PIRP Irp );
NTSTATUS InterceptedReadRoutine( PDEVICE_OBJECT DeviceObject, PIRP Irp );
NTSTATUS InterceptedWriteRoutine( PDEVICE_OBJECT DeviceObject, PIRP Irp );
*/
NTSTATUS InterceptGenericRoutine(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS EnableMonitoring();
NTSTATUS DisableMonitoring();
BOOLEAN IsMonitoringEnabled();
