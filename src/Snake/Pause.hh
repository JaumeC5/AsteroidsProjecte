#pragma once

#include "InputManager.hh"

#define P Pause::Instance()

bool pause = false;

class Pause {
private:
	
	bool once = false;
	bool once2 = false;
	bool shot = false;

public:

	inline static Pause &Instance() {
		static Pause p;
		return p;
	}

	bool getPause() {
		if (IM.getEscape()) {
			if (!pause && !once) {
				cout << "Paused" << endl;
				pause = true;
				once = true;

			}
			else if (pause && !once) {
				cout << "Unpaused" << endl;
				pause = false;
				once = true;
			}
			once = false;
			return pause;
		}
	}
};