#include "Controller.h"
#include "StringOP.h"


CController::CController()
{
	params.resize(10);
	value = 0;
}


CController::~CController()
{
}

CController::CController(const CController &M)
{
	name = M.name;
	params = M.params;
	type = M.type;
	sensor_id = M.sensor_id;
	value = M.value;
	interval = M.interval;
	min_val = M.min_val;
	max_val = M.max_val;
	output = M.output;
}

CController& CController::operator=(const CController &M)
{
	params = M.params;
	name = M.name;
	type = M.type;
	sensor_id = M.sensor_id;
	value = M.value;
	interval = M.interval;
	min_val = M.min_val;
	max_val = M.max_val;
	output = M.output;
	return *this;

}

double CController::calc_value(double t, double dt, int experiment_id)
{
	value += dt*(params[0] * P(t, experiment_id) + params[1] * I(t, experiment_id) + params[2] * D(t, experiment_id));
	value = min(value, max_val);
	value = max(value, min_val);
	append(t, value);
	return value;
}


void CController::append(double t, double C)
{
	for (int i = output.n - 1; i >= 0; i--)
	{
		if (output.t[i] == t) output.C[i] = C;
	}
	output.append(t, C);
	return;

}

double CController::P(double t, int experiment_id)
{
	if (tolower(type) == "pid")
		return (Sensor->output[experiment_id].interpol(t) - params[3]);

}
double CController::I(double t, int experiment_id)
{
	if (tolower(type) == "pid")
		return (Sensor->output[experiment_id].integrate(t) - params[3]*(t-Sensor->output[experiment_id].t[0]));

}
double CController::D(double t, int experiment_id)
{
	if (tolower(type) == "pid")
		if (Sensor->output[experiment_id].n > 1)
			return (Sensor->output[experiment_id].slope(t));
		else
			return 0;


}

void CController::set_val(string S, double val)
{
	if ((tolower(S) == "kp") || (tolower(S) == "k_p")) params[0] = val;
	if ((tolower(S) == "ki") || (tolower(S) == "k_i")) params[1] = val;
	if ((tolower(S) == "kd") || (tolower(S) == "k_d")) params[2] = val;
	if (tolower(S) == "interval") interval = val;
	if ((tolower(S) == "set_point") || (tolower(S)=="setpoint")) params[3] = val;

}