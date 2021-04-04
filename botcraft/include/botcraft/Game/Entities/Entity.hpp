#pragma once

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
	class Entity
	{
	public:
		Entity();

		const int GetEID() const;
		const Vector3<double>& GetPosition() const;
		const float GetYaw() const;
		const float GetPitch() const;
		const Vector3<double>& GetSpeed() const;
		const bool GetOnGround() const;


		void SetEID(const int eid_);
		virtual void SetPosition(const Vector3<double>& pos);
		virtual void SetX(const double x);
		virtual void SetY(const double y);
		virtual void SetZ(const double z);
		virtual void SetYaw(const float yaw_);
		virtual void SetPitch(const float pitch_);
		void SetSpeed(const Vector3<double>& speed_);
		void SetSpeedX(const double speed_x);
		void SetSpeedY(const double speed_y);
		void SetSpeedZ(const double speed_z);
		void SetOnGround(const bool on_ground_);

	protected:
		int eid;
		Vector3<double> position;
		float yaw;
		float pitch;
		Vector3<double> speed;

		bool on_ground;
	};
} // Botcraft