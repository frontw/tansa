#ifndef TANSA_JOCSPLAYER_H
#define TANSA_JOCSPLAYER_H

#include <tansa/core.h>
#include <tansa/control.h>


#include "tansa/jocsParser.h"
#include "tansa/config.h"

namespace tansa {
	class JocsPlayer {
	public:
		JocsPlayer(const std::vector<Vehicle *> &vehicles, const std::vector<unsigned> &jocsActiveIds);

		// Get ready to fly (arm and takeoff to home point)
		void prepare();

		// Start flying
		void play();

		void pause();

		// Lands and disarms all drones (Must already be paused)
		void stop();

		void step();
		void rewind(int steps);
		void reset();
		void loadJocs(Jocs *j);

		// TODO: Instead we should use isRunning which checks if any states are not StateInit
		//bool isPlaying() { return this->playing; }
		std::vector<Point> getHomes();
		std::vector<std::vector<Action*>> getActions();
		void initControllers();
		void cleanup();
	private:
		std::vector<Vehicle *> vehicles;
		std::vector<unsigned> jocsActiveIds;

		std::vector<Breakpoint> breakpoints;
		Jocs* currentJocs;
		std::vector<std::vector<Action*>> actions;
		std::vector<Point> homes;
		std::vector<HoverController *> hovers;
		std::vector<PositionController *> posctls;
		std::vector<Trajectory *> takeoffs;
		std::vector<Point> holdpoints;
		std::vector<PlayerVehicleState> states;
		std::vector<int> plans;

		//bool playing = false;


		bool pauseRequested = false;
		bool resetMode = false;
		bool initialized = false;
		Time start = Time(0,0);
		int stepTick = 0;

		double getNextBreakpointTime(double lastTime);
		double getBreakpointTime(unsigned breakpointNumber);
		double getBreakpointTime(std::string breakpointName);
		unsigned getBreakpointNumber(double startTime);
		Point getDroneLocationAtTime(double startTime, unsigned droneId);
	};
}
#endif //TANSA_JOCSPLAYER_H