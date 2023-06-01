#pragma once


namespace emb {

namespace gpio {

enum class ActiveState {
	low = 0,
	high = 1
};


enum class State {
	inactive = 0,
	active = 1
};


class InputInterface {
public:
	InputInterface() = default;
	virtual ~InputInterface()  = default;
	virtual State read() const = 0;
	virtual int read_level() const = 0;
};


class OutputInterface {
public:
	OutputInterface() = default;
	virtual ~OutputInterface() = default;

	virtual State read() const = 0;
	virtual void set(State state = State::active) = 0;
	virtual void reset() = 0;
	virtual void toggle() = 0;
	virtual int read_level() const = 0;
    virtual void set_level(int level) = 0;
};

} // namespace gpio

} // namespace emb

