#pragma once
class Engine;

class KeyBoard
{
	Engine* engine_;
public:
	bool key_w = false;
	bool key_s = false;
	bool key_a = false;
	bool key_d = false;
	bool key_e = false;
	bool key_q = false;
	bool key_space = false;
	bool key_shift = false;

	KeyBoard(Engine* engine)
	{
		engine_ = engine;
	}

	void KeyEvent(int key, int action);
};
