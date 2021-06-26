from cdtx.mcp2200.api import SimpleIOClass

dev = SimpleIOClass()
dev.InitMCP2200(0x04d8, 0x00df)
assert dev.GetNoOfDevices() == 1

# Set GPIO 0 as output and set it
dev.SelectDevice(0)
assert dev.IsConnected() == True

# Set all pins as outputs
dev.ConfigureIO(0x00)
dev.SetPin(0)
assert dev.ReadPinValue(0) == 1

dev.fnSetBaudRate(9600)
