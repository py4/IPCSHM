#ifndef VALIDATOR_H_
#define VALIDATOR_H_

class SharedMem;

class Validator {
	public:
		Validator();
		~Validator();
		void monitor();

	private:
		void validate(int i);
		SharedMem* sm;
};

#endif
