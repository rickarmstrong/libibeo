#pragma once


#include <vector>

namespace ibeo
{


const uint32_t MagicWordValue = 0xAFFEC0C2;



// type definitions for the wire

#pragma pack(push)
#pragma pack(1)
struct MessageHeader
{
    // these are transferred in network byte order
    uint32_t            MagicWord;
    uint32_t            PreviousMessagesSize;
    uint32_t            MessageSize;
    uint8_t             Reserved;
    uint8_t             DeviceID;
    uint16_t            DataType;
    uint64_t            NTPTime;
};

struct StatusMessage
{
    uint16_t            FirmwareVersion;
    uint16_t            FPGAVersion;
    uint16_t            ScannerStatus;
    uint32_t            Reserved1;
    uint16_t            Temperature;
    uint16_t            SerialNumber0;
    uint16_t            SerialNumber1;
    uint16_t            Reserved2;
    uint16_t            FPGATimeStamp[3];
    uint16_t            DSPTimeStamp[3];
};

struct Parameter
{
    uint16_t            Index;
    uint32_t            Value;
};

struct ScanDataHeader
{
    // these are transferred in little endian byte order
    uint16_t            ScanNumber;
    uint16_t            ScannerStatus;
    uint16_t            SyncPhaseOffset;
    uint64_t            NTPScanStartTime;
    uint64_t            NTPScanEndTime;
    uint16_t            AngleTicksPerRotation;
    int16_t             StartAngle;
    int16_t             EndAngle;
    uint16_t            ScanPointCount;
    int16_t             MountPositionYaw;
    int16_t             MountPositionPitch;
    int16_t             MountPositionRoll;
    int16_t             MountPositionX;
    int16_t             MountPositionY;
    int16_t             MountPositionZ;
    uint16_t            Flags;
};

struct ScanPoint
{
    // these are transferred in little endian byte order
    uint8_t             LayerEcho;
    uint8_t             Flags;
    int16_t             HorizontalAngle;
    uint16_t            RadialDistance;
    uint16_t            EchoPulseWidth;
    uint16_t            Reserved;
};

struct ObjectDataHeader
{
    uint64_t            ScanStartTimestamp;
    uint16_t            ObjectCount;
};

struct Point2D
{
    int16_t             X;
    int16_t             Y;
};

struct Size2D
{
    uint16_t            Width;
    uint16_t            Length; // referred to as Length in the docs, so it will here too.
};

struct Object
{
    uint16_t            ObjectID;
    uint16_t            ObjectAge;
    uint16_t            ObjectPreductionAge;
    uint16_t            RelativeTimestampMS;
    Point2D             ReferencePoint;
    Point2D             ReferencePointSigma;
    Point2D             ClosestPoint;
    Point2D             BoundingBoxCenter;
    uint16_t            BoundingBoxWidth;
    uint16_t            BoundingBoxLength;
    Point2D             ObjectBoxCenter;
    Size2D              ObjectBoxSize;
    int16_t             ObjectBoxOrientation;
    Point2D             AbsoluteVelocity;
    Size2D              AbsoluteVelocitySigma;
    Point2D             RelativeVelocity;
    uint16_t            Classification;
    uint16_t            ClassificationAge;
    uint16_t            ClassificationCertainty;
    uint16_t            ContourPointCount;
};

struct ErrorWarning
{
    uint16_t            ErrorRegister1;
    uint16_t            ErrorRegister2;
    uint16_t            WarningRegister1;
    uint16_t            WarningRegister2;
    uint16_t            Reserved[4];
};

#pragma pack(pop)


// these are the external data types of interest
struct ScanDataPoints
{
    ScanDataHeader Header;
    std::vector<ScanPoint> Points;
};

struct ScanDataObject
{
    Object Obj;
    std::vector<Point2D> Contour;
};

struct ScanDataObjects
{
    ObjectDataHeader Header;
    std::vector<ScanDataObject> Objects;
};


enum DataType
{
    CommandData =       0x2010,
    ReplyData =         0x2020,
    ScanData =          0x2202,
    ObjectData =        0x2221,
    VehicleData =       0x2805,
    ErrorWarningData =  0x2030
};


enum Command
{
    Reset =                     0x0000,
    GetStatus =                 0x0001,
    SaveConfig =                0x0004,
    SetParameter =              0x0010,
    GetParameter =              0x0011,
    ResetDefaultParameters =    0x001A,
    StartMeasure =              0x0020,
    StopMeasure =               0x0021,

    // high 4 bytes are seconds since 1.1.1900,
    // low 4 bytes are fractional seconds, resolution "2-32" seconds (?)
    SetNTPTimestampSync =       0x0034
};


enum ParameterIndex
{
    IPAddress =                     0x1000,
    TCPPort =                       0x1001,
    SubnetMask =                    0x1002,
    Gateway =                       0x1003,
    CustomerProcessingSwitch0 =     0x1004,
    CANBaseID =                     0x1010,
    CANBaudRate =                   0x1011,
    DataOutputFlag =                0x1012,
    MaxObjectsViaCAN =              0x1013,
    ContourPointDensity =           0x1014,
    ObjectPriorizationCriterion =   0x1015,
    CANObjectDataOptions =          0x1016,
    MinimumObjectAge =              0x1017,
    MaximumPreductionAge =          0x1018,
    InterfaceFlags =                0x1019,
    StartAngle =                    0x1100,
    EndAngle =                      0x1101,
    ScanFrequency =                 0x1102,
    SyncAngleOffset =               0x1103,
    AngularResolutionType =         0x1104,
    AngleTicksPerRotation =         0x1105,
    SensorMountingX =               0x1200,
    SensorMountingY =               0x1201,
    SensorMountingZ =               0x1202,
    SensorMountingYaw =             0x1203,
    SensorMountingPitch =           0x1204,
    SensorMountingRoll =            0x1205,
    VehicleFrontToFrontAxle =       0x1206,
    FrontAxleToRearAxle =           0x1207,
    RearAxleToVehicleRear =         0x1208,
    VehicleWidth =                  0x1209,
    SteerRatioType =                0x120A,
    SteerRatioPoly0 =               0x120C,
    SteerRatioPoly1 =               0x120D,
    SteerRatioPoly2 =               0x120E,
    SteerRatioPoly3 =               0x120F,
    VehicleMotionDataFlags =        0x1210,
    DeviceType =                    0x3301
};



}

