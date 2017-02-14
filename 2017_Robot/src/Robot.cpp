#include <iostream>
#include <memory>
#include <string>
//mjj005
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include "RobotMap.h"
#include "TankDrive.h"
#include "Pickup.h"
#include "BoilerVision.h"
#include "GearManipulator.h"
#include "Shooter.h"
#include "Autonomous.h"
using frc::SmartDashboard;
using namespace std;
using namespace frc;
class Robot: public frc::IterativeRobot {
	grip::BoilerVision m_boilerVision;
	frc::Solenoid m_gearShift;
	CANTalon m_leftMotor1;
	CANTalon m_leftMotor2;
	CANTalon m_rightMotor1;
	CANTalon m_rightMotor2;

	TankDrive m_tank;

	Autonomous *m_autonomous;

    Shooter m_shooter;
	CANTalon m_shootWheel1;
	CANTalon m_shootWheel2;
	CANTalon m_indexMotor;
	DigitalOutput m_aimLight;
	grip::BoilerVision Vision;
	CameraServer *cameraServer = nullptr;
	cs::CvSource m_outputStream;
	cs::UsbCamera camera;
	GearManipulator m_gearManipulator;
	Pickup m_pickup;
	Joystick m_leftStick, m_rightStick;

	frc::Talon m_intakeMotor;
	// Hopper Motor pushs into Hopper
	frc::Talon m_hopperMotor;

	frc::Servo m_leftGearServo;
	frc::Servo m_rightGearServo;


public:
	Robot()
		:
		m_leftStick(LEFTSTICK) //todo:mjj use config constant instead of literal number
		,m_rightStick(RIGHTSTICK) //todo:mjj use config constant instead of literal number
		,m_gearShift(GEAR_SHIFT)
		,m_leftMotor1(LEFT_DRIVE1)
		,m_leftMotor2(LEFT_DRIVE2)
		,m_rightMotor1(RIGHT_DRIVE1)
		,m_rightMotor2(RIGHT_DRIVE2)
		, m_intakeMotor(PICKUP_INTAKE)
		, m_hopperMotor(PICKUP_HOPPER)
		,m_tank(
			m_leftStick
			, m_rightStick
			, m_gearShift
			, m_leftMotor1
			, m_leftMotor2
			, m_rightMotor1
			, m_rightMotor2
		)
		, m_aimLight(AIM_LIGHT)
		, m_shootWheel1(0)
		, m_shootWheel2(1)
		, m_indexMotor(2)
		, m_pickup(
			m_leftStick
			, PICKUP
			, m_intakeMotor
			, m_hopperMotor
		)
		, m_shooter(
			m_rightStick
			, m_shootWheel1 //todo:mjj change values to constant.
			, m_shootWheel2
			, m_indexMotor
			, m_leftStick
			, m_aimLight
		)

		, m_leftGearServo(LEFT_GEAR_SERVO)
		, m_rightGearServo(RIGHT_GEAR_SERVO)
		, m_gearManipulator(
			m_rightStick
			, GEAR_RELEASE
			, m_leftGearServo
			, m_rightGearServo
		)


	{

	}

	void RobotInit() {
		SmartDashboard::PutNumber("Exposure", 1);
		if(!Preferences::GetInstance()->ContainsKey("Exposure")) {
			Preferences::GetInstance()->PutFloat("Exposure", 1);
		}

		cameraServer = CameraServer::GetInstance();
		m_autonomous = new Autonomous(cameraServer, m_outputStream, camera);
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		//m_gearManipulator.Release(m_leftStick.GetRawButton(LStickMap::GEAR_RELEASE));
		m_gearManipulator.TeleopPeriodic();
		m_tank.TeleopPeriodic();
		m_pickup.TeleopPeriodic();
		m_shooter.TeleopPeriodic();
	}

	void AutonomousInit() override {
	    m_autonomous->AutonomousInit();
	}

	void AutonomousPeriodic() {
		m_autonomous->AutonomousPeriodic();

	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)

