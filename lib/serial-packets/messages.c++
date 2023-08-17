#include "messages.h"
#include "serialize.h"
#include <sstream>

Test_Inbound::Test_Inbound(const Packet& p) {
	std::tie(
		field_1, field_2
	) = deserialize<
		float, float
	>(p.data());
}

Packet Test_Outbound::pack() {
	return Packet(
		Test_Outbound::id,
		serialize<
			float, float, float
		>(std::make_tuple(
			field_1, field_2, field_3
		))
	);
}

Position::Position(const Packet& p) {
	std::tie(
		x_trans, y_trans, z_trans,
		x_rot, y_rot, z_rot,
		w,
		frame_number
	) = deserialize<
		float, float, float,
		float, float, float,
		float,
		int32_t
	>(p.data());
}

Simple_Move::Simple_Move(const Packet& p) {
	std::tie(
		distance, curvature, velocity, trans_id
	) = deserialize<
		float, float, float, int32_t
	>(p.data());
}

Packet Move_Feedback::pack() {
	return Packet(
		Move_Feedback::id,
		serialize<
			float, float, float, int32_t
		>(std::make_tuple(
			distance, curvature, velocity, trans_id
		))
	);
}

Twist::Twist(){

}

Twist::Twist(const Packet& p){
	std::tie(linear, angular) = deserialize<float, float>(p.data());
}

Packet Twist::pack(){
		return Packet(
		Twist::id,
		serialize<
			float, float
		>(std::make_tuple(
			linear,angular
		))
	);
	}

std::string Twist::repr()
{
	std::stringstream ss;
	ss << "Twist<linear: " << linear << " angular: " << angular << ">\n";
	return ss.str();
}

Sensor_Data::Sensor_Data() {

}

Sensor_Data::Sensor_Data(const Packet& p) {
	std::tie(time, potval, dist, wz, left, right, theta) = 
	deserialize<int32_t, int32_t, int32_t, float, int32_t, int32_t, float>(p.data());
}

Packet Sensor_Data::pack() {
	return Packet(
		Sensor_Data::id,
		serialize<
		int32_t, int32_t, int32_t, float, int32_t, int32_t, float
		>(std::make_tuple(
			time, potval, dist, wz, left, right, theta
		))
	);
}

std::string Sensor_Data::repr() {
	std::stringstream ss;
	ss << "Sensor_Data<time: " << time << " potval: " << potval << " dist: " << dist <<
	" wz: " << wz << " left: " << left << " right: " << right << " theta: " << theta << '\n';
	return ss.str();
}

Motor_Power::Motor_Power(){

}

Motor_Power::Motor_Power(const Packet& p){
	std::tie(lpower, rpower) = deserialize<int32_t, int32_t>(p.data());
}

Packet Motor_Power::pack(){
		return Packet(
		Motor_Power::id,
		serialize<
			int32_t, int32_t
		>(std::make_tuple(
			lpower,rpower
		))
	);
	}

std::string Motor_Power::repr()
{
	std::stringstream ss;
	ss << "Motor_Power<lpower: " << lpower << " rpower: " << rpower << ">\n";
	return ss.str();
}

Increase_Power::Increase_Power(){

}

Increase_Power::Increase_Power(const Packet& p){
	std::tie(lpower, rpower) = deserialize<int32_t, int32_t>(p.data());
}

Packet Increase_Power::pack(){
		return Packet(
		Increase_Power::id,
		serialize<
			int32_t, int32_t
		>(std::make_tuple(
			lpower,rpower
		))
	);
	}

std::string Increase_Power::repr()
{
	std::stringstream ss;
	ss << "Increase_Power<lpower: " << lpower << " rpower: " << rpower << ">\n";
	return ss.str();
}

Turn_90::Turn_90(){

}

Turn_90::Turn_90(const Packet& p){
	std::tie(lpower, rpower, deg) = deserialize<int32_t, int32_t, float>(p.data());
}

Packet Turn_90::pack(){
		return Packet(
		Turn_90::id,
		serialize<
			int32_t, int32_t, float
		>(std::make_tuple(
			lpower,rpower, deg
		))
	);
	}

std::string Turn_90::repr()
{
	std::stringstream ss;
	ss << "Turn_90<lpower: " << lpower << " rpower: " << rpower << " deg: " << deg << ">\n";
	return ss.str();
}

Lidar_Sweep::Lidar_Sweep(){

}

Lidar_Sweep::Lidar_Sweep(const Packet& p){
	std::tie(lidarOn) = deserialize<int32_t>(p.data());
}

Packet Lidar_Sweep::pack(){
		return Packet(
		Lidar_Sweep::id,
		serialize<
			int32_t
		>(std::make_tuple(
			lidarOn
		))
	);
	}

std::string Lidar_Sweep::repr()
{
	std::stringstream ss;
	ss << "Lidar_Sweep<lidarOn: " << lidarOn << ">\n";
	return ss.str();
}

